cmake_minimum_required(VERSION 2.8)
project(FITMC CXX)

#ROOT specific - to help CMake find FindROOT.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

#Set compiler flags - ROOT 6 requires C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#Sets ROOT_INCLUDE_DIR and ROOT_LIBRARIES to the local path on system
find_package(ROOT REQUIRED)
if (NOT ROOT_FOUND)
  message(FATAL_ERROR "ROOT not found.")
endif()

#Find header files
include_directories(${ROOT_INCLUDE_DIR} include)
set(FITMC_LIBS ${ROOT_LIBRARIES} RooFitCore RooFit MathMore Minuit Foam TreePlayer)
#Removed MathMore

#Define source code. Add list of files
set(FITMC_SRC src/ParseArguments.cpp src/Configuration.cpp src/CommonFunctions.cpp src/ToyFunctions)
add_library(runsrc ${FITMC_SRC})
set(FITMC_LIBS ${FITMC_LIBS} runsrc)

#${variable} expands variable
add_executable(ToyD1D src/ToyD1D.cpp)
# add_executable(SimpleToy src/SimpleToy.cpp)

#Find all external code programme needs to run (ROOT normally finds itself)
#First argument = target
target_link_libraries(ToyD1D ${FITMC_LIBS} stdc++fs)
# target_link_libraries(SimpleToy ${FITMC_LIBS} stdc++fs)
