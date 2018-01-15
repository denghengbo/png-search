#!/bin/bash

#PBS -N image_search
#PBS -l walltime=10:00:00
#PBS -l mem=1GB
#PBS -l nodes=1:ppn=8
#PBS -S /bin/bash
#PBS -j oe

# Change to directory from where PBS job was submitted
cd $PBS_O_WORKDIR
echo "---------------------[ Threads: 1 ]-------------------"
export OMP_NUM_THREADS=1
echo "---------------------[ Mammogram ]---------------------" 
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo1.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo1.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo1.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo1.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo1.png true 75 32
echo "---------------------[ TestImage ]---------------------"
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test1.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test1.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test1.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test1.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test1.png true 75 16
echo "---------------------[ Marcum ]---------------------"
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum1.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum1.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum1.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum1.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum1.png true 50 64
echo "---------------------[ Threads: 4 ]---------------------"
export OMP_NUM_THREADS=4
echo "---------------------[ Mammogram ]---------------------" 
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo4.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo4.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo4.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo4.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo4.png true 75 32
echo "---------------------[ TestImage ]---------------------"
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test4.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test4.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test4.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test4.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test4.png true 75 16
echo "---------------------[ Marcum ]---------------------"
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum4.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum4.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum4.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum4.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum4.png true 50 64
echo "---------------------[ Threads: 8 ]---------------------"
export OMP_NUM_THREADS=8
echo "---------------------[ Mammogram ]---------------------" 
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo8.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo8.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo8.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo8.png true 75 32
/usr/bin/time -v ./homework7 ./png/Mammogram.png ./png/Cancer_mask.png ./png/results_2/mammo8.png true 75 32
echo "---------------------[ TestImage ]---------------------"
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test8.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test8.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test8.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test8.png true 75 16
/usr/bin/time -v ./homework7 ./png/TestImage.png ./png/and_mask.png ./png/results_2/test8.png true 75 16
echo "---------------------[ Marcum ]---------------------"
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum8.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum8.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum8.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum8.png true 50 64
/usr/bin/time -v ./homework7 ./png/MiamiMarcumCenter.png ./png/WindowPane_mask.png ./png/results_2/marcum8.png true 50 64

#end of script
