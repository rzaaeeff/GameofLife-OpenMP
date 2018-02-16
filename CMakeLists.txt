# follow comments and edit file
cmake_minimum_required(VERSION 3.9)
project(OpenMP_Game_Of_Life_master)

# go ahead and change compile folder
# your compiler should contain openmp
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++-7)
set(CMAKE_C_COMPILER /usr/local/bin/gcc-7)

# add openmp flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

# uncomment file that you want to compile and run
# by default it's RandomFileMaker
add_executable(OpenMP_Game_Of_Life_master
        #GoLParallel.cpp
        #GoLSerial.cpp
        RandomFileMaker.cpp
        )
