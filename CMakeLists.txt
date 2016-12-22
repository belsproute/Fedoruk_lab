cmake_minimum_required(VERSION 3.6)
project(lab4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lpng")
set(SOURCE_FILES main.cpp WTANeuron.h NPoint.h NeuralNet.h Zipped.h AllData.h pngimage.h Test.h Gnuplot.h)
add_executable(lab4 ${SOURCE_FILES})