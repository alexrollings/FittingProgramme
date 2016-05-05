cmake_minimum_required(VERSION 2.8)
project(Fitting CXX)

#ROOT specific - to help CMake find FindROOT.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

#Set compiler flags - ROOT 6 requires C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Sets ROOT_INCLUDE_DIR and ROOT_LIBRARIES to the local path on system
find_package(ROOT REQUIRED)
if (NOT ROOT_FOUND)
  message(FATAL_ERROR "ROOT not found.")
endif()

#Find header files
include_directories(${ROOT_INCLUDE_DIR} include)
set(FITTING_LIBS ${ROOT_LIBRARIES} RooFitCore RooFit Minuit Foam MathMore TreePlayer)

#Define source code. Add list of files
set(FITTING_SRC src/ParseArguments.cpp src/Configuration.cpp src/LoopOverFiles.py)

#${variable} expands variable
add_executable(Main src/Main.cpp ${FITTING_SRC})
add_executable(SaveRooDataSet src/SaveRooDataSet.cpp ${FITTING_SRC})

#Find all external code programme needs to run (ROOT normally finds itself)
#First argument = target
target_link_libraries(Main ${FITTING_LIBS})
target_link_libraries(SaveRooDataSet ${FITTING_LIBS})

