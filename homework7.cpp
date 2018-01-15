// Copyright mullencr 2017

#include <omp.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


#include "PNG.h"

using MatchList = std::vector<int>;
using Buffer = std::vector<unsigned char>;

int getPixInd(const size_t row, const size_t col, const int width);
bool checkMask(const int row, const int col,  int perPixMatch, int pixTol, 
        const PNG& img, const PNG& mask);
void checkPixels(const int a_red, const int a_green, const int a_blue, 
        const int row, const int col, const Buffer& mask_buff, 
        const Buffer& img_buff, const PNG& img, const PNG& mask, int& netMatch, 
        const int pixTol);
bool pMatch(int pixTol, int average, int pixel);
bool noOverlaps(const int row, const int col, const PNG& img, const PNG& mask,
        const MatchList& matches);
void searchImg(const PNG& img, const PNG& mask, const int perPixMatch, 
        const int pixTol, MatchList& matches);
void doOutput(const std::string& out_file, const PNG& img, const PNG& mask,
        MatchList& matches);
std::string getIndexCoordinates(const int index, const int width);
void getAverages(int& a_red, int& a_green, int& a_blue, 
        const int row, const int col, const Buffer& img_buff,
        const Buffer& mask_buff, const PNG& img, const PNG& mask);
bool containsRec(int row, int col, int target_row, int target_col, 
        int width, int height);
void printResults(const PNG& img, const PNG& mask, const MatchList& matches);
void drawBox(PNG& png, int row, int col, int width, int height);
void doBoxes(PNG& out, const PNG& img, const PNG& mask, 
        const MatchList& matches);

int main(int argc, char** argv) {
    int perPixMatch = 75;
    int pixTol = 32;
    // Check command line list: If it's only three, set defaults
    // If it's less than three, complain and exit
    if (argc < 4) {
        std::cout << "Please enter three arguments:\n"
                << "The image to be searched, the sub-mask,"
                << " and the output image path\n";
        exit(2);
    }
    if (argc == 6)
        perPixMatch = std::stoi(argv[5]);
    if (argc == 7)
        pixTol = std::stoi(argv[6]);
    // First, we have to read in the arguments and assign them
    // Next, we need to create the image for the primary image
    PNG img;
    img.load(argv[1]);
    // Then, we create the image for the mask
    PNG mask;
    mask.load(argv[2]);
    // Create a list of matches:
    MatchList matches;
    // Execute the searching
    searchImg(img, mask, perPixMatch, pixTol, matches);
    // Do the output
    doOutput(argv[3], img, mask, matches);
    return 0;
}

// Methods implementation: 
void searchImg(const PNG& img, const PNG& mask, const int perPixMatch, 
        const int pixTol, MatchList& matches) {
    // Next, we need to loop through each location (rowxrow, colxcol)
#pragma omp parallel for schedule(static)
    for (int row = 0; row < (img.getHeight() - mask.getHeight()); row++) {
        for (int col = 0; col < (img.getWidth() - mask.getWidth()); col++) {
            // Check for a match. If there's a match, check for overlaps.
            if (checkMask(row, col, perPixMatch, pixTol, img, mask) && 
                noOverlaps(row, col, img, mask, matches)) {
                int start_ind = getPixInd(row, col, img.getWidth());
#pragma omp critical(matches)
                {
                matches.push_back(start_ind);
                }
            }
        }
    }
}

bool checkMask(const int row, const int col, int perPixMatch, int pixTol,
                    const PNG& img, const PNG& mask) {
    // For each location in the mask, compute the average background-color.
    int a_red = 0, a_green = 0, a_blue = 0, netMatch = 0;
    // Get the buffers:
    const Buffer& img_buff = img.getBuffer();
    const Buffer& mask_buff = mask.getBuffer();
    getAverages(a_red, a_green, a_blue, row, col, 
            img_buff, mask_buff, img, mask);
    checkPixels(a_red, a_green, a_blue, row, col, 
            img_buff, mask_buff, img, mask, netMatch, pixTol);
    // Use net match formula to figure out if its a net match for this location.
    return (netMatch > mask.getWidth()*mask.getHeight()*perPixMatch/100);
}

void checkPixels(const int a_red, const int a_green, const int a_blue, 
        const int row, const int col, const Buffer& ib, 
        const Buffer& mb, const PNG& img, const PNG& mask, int& netMatch, 
        const int pixTol) {
    int matchCount = 0, mismatchCount = 0;    
    // Loop through every pixel in the mask.
    for (int m_row = 0; m_row < (mask.getHeight()); m_row++) {
        for (int m_col = 0; m_col < (mask.getWidth()); m_col++) {
            // Next check if each pixel that should matches the background
            // Use the pix color tolerance value
            // Do the math to get the index of this pixel
            const int m = getPixInd(m_row, m_col, mask.getWidth());
            // Get img index:
            const int i = getPixInd((row+m_row), (col+m_col), img.getWidth());
            bool match = true;
            // See if pixel matches background color
            if (!pMatch(pixTol, a_red, ib[i]) || 
                !pMatch(pixTol, a_green, ib[i+1]) || 
                !pMatch(pixTol, a_blue, ib[i+2]))
                match = false;
            // We know if we have a match.
            // if the sub is black, a match to background is a matched pixel.
            // if sub is not black, a match to background is a mismatch.
            if (mb[m]+mb[m+1]+mb[m+2] != 0)
                match = !match;
            if (match)
                matchCount++;
            else
                mismatchCount++;
        }
    }
    netMatch = matchCount - mismatchCount;
}

bool pMatch(int pixTol, int average, int pixel) {
    return (average - pixTol < pixel ) && (pixel < average + pixTol);
}

void getAverages(int& a_red, int& a_green, int& a_blue, 
        const int row, const int col, const Buffer& img_buff,
        const Buffer& mask_buff, const PNG& img, const PNG& mask) { 
    int sum = 0;
    // Loop through every pixel in the mask. 
    for (int m_row = 0; m_row < (mask.getHeight()); m_row++) {
        for (int m_col = 0; m_col < (mask.getWidth()); m_col++) {
            // Do the math to get the index of this pixel
            const int mask_index = getPixInd(m_row, m_col, mask.getWidth());
            // Grab colors from the mask.
            if (mask_buff[mask_index] + mask_buff[mask_index + 1] 
                    + mask_buff[mask_index + 2] == 0) {
                // Get img index:
                const int img_index = getPixInd((row+m_row), (col+m_col), 
                        img.getWidth());
                // If mask is black, grab three from the image
                // add image to the average color computation.
                a_red += img_buff[img_index];
                a_green += img_buff[img_index + 1];
                a_blue += img_buff[img_index + 2];
                sum++;
            }
        }
    }
    // Divide the totals and get the averages.
    a_red /= sum;
    a_green /= sum;
    a_blue /= sum;
}

bool noOverlaps(const int row, const int col, const PNG& img, const PNG& mask,
        const MatchList& matches) {
    bool clear = true;
    int m_width = mask.getWidth();
    int m_height = mask.getHeight();
#pragma omp critical(matches)
    {
    for (int matchStart : matches) {
        // Get row and col for match corner.
        std::string coor = getIndexCoordinates(matchStart, img.getWidth());
        int tmp = coor.find(":");
        int m_row = std::stoi(coor.substr(0, tmp));
        int m_col = std::stoi(coor.substr(tmp+1));
        // Check all four corners of one match against the other.
        if (containsRec(m_row, m_col, row, col, m_width, m_height) 
            || containsRec(m_row, m_col, row+m_height, col, m_width, m_height)
            || containsRec(m_row, m_col, row, col+m_width, m_width, m_height)
            || containsRec(m_row, m_col, row+m_height, col+m_width, 
                m_width, m_height)) {
            clear = false;
            break;
        }
    }
    }
    return clear;
}

bool containsRec(int row, int col, int target_row, int target_col, 
        int width, int height) {
    return (row <= target_row) && (target_row <= row+height) &&
           (col <= target_col) && (target_col <= col+width);
}

void doOutput(const std::string& out_file, const PNG& img, const PNG& mask,
        MatchList& matches) {
    // Sort the list of matches (based on row, and then by column)
    // This is as simple as storing the indeces in row major form
    // in a single buffer.
    std::sort(matches.begin(), matches.end());
    printResults(img, mask, matches);
    PNG out(img);
    // Then print the matched regions and do the red box drawing
    doBoxes(out, img, mask, matches);
    // Write the box out using the supplied methods.
    out.write(out_file);
}

void doBoxes(PNG& out, const PNG& img, const PNG& mask, 
        const MatchList& matches) {
    for (int matchStart : matches) {
        // Get row and col for match corner.
        std::string coor = getIndexCoordinates(matchStart, img.getWidth());
        int tmp = coor.find(":");
        int m_row = std::stoi(coor.substr(0, tmp));
        int m_col = std::stoi(coor.substr(tmp+1));
        drawBox(out, m_row, m_col, mask.getWidth(), mask.getHeight());
    }
}

void drawBox(PNG& png, int row, int col, int width, int height) {     
    // Draw horizontal lines     
    for (int i = 0; (i < width); i++) {         
        png.setRed(row, col + i);         
        png.setRed(row + height, col + i);     
    }     
    // Draw vertical lines     
    for (int i = 0; (i < height); i++) {         
        png.setRed(row + i, col);         
        png.setRed(row + i, col + width);     
    }
}

void printResults(const PNG& img, const PNG& mask, const MatchList& matches) {
    for (size_t i = 0; i < matches.size(); i++) {
        // Get row and col for match corner.
        std::string coor = getIndexCoordinates(matches[i], img.getWidth());
        int tmp = coor.find(":");
        int m_row = std::stoi(coor.substr(0, tmp));
        int m_col = std::stoi(coor.substr(tmp+1));
        std::cout << "sub-image matched at: "
                << m_row << ", " << m_col << ", "
                << m_row + mask.getHeight() << ", "
                << m_col + mask.getWidth() << std::endl;
    }
    std::cout << "Number of matches: " << matches.size() << std::endl;
}

int getPixInd(const size_t row, const size_t col, const int width) {
        return ((row * width) + col) * 4;
}

// Return the x and y coordinates of a single index, in string format "x:y"
std::string getIndexCoordinates(const int index, const int width) {
        std::string str;
        str += std::to_string(index/(width*4));
        str += ":";
        str += std::to_string((index%(width*4))/4);
        return str;
}
