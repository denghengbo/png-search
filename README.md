# png-search
High Performance Computing: Multithreaded approach to searching through a PNG for a match to a submask image. The image was scanned pixel by pixel, using average color calculation to compare with a silhouette-like mask specified via command-line. Once a match is found, a pre-written method to label the image is called and the image is edited. Results of my search can be found in the results folders. Note that the image search of Marcum Center was not successful due to an unknown bug.

The program uses the Open MP multithreading library to process the entire image in considerably less time than a serial approach would take. The job was run on Miami University's supercomputing cluster, using the PBS (Portable Batch System) job scheduler. The system was run using 1, 4, and 8 threads, and the outputs of reach run were the same. 

PNG.cpp and PNG.h are classes provided by my professor, but all other code contained in the project is my own. Most of the processing is done in the file homework7.cpp
