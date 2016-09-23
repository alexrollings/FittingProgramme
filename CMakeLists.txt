cmake_minimum_required(VERSION 2.8)
project(Fitting CXX)

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
set(FITTING_LIBS ${ROOT_LIBRARIES} RooFitCore RooFit Minuit Foam TreePlayer)
#Removed MathMore

#Define source code. Add list of files
set(FITTING_SRC src/ParseArguments.cpp src/Configuration.cpp src/LoopOverFiles.py src/NeutralVars.cpp  src/RooCruijff src/NeutralBachelorVars.cpp src/DaughtersVars.cpp src/NeutralDaughtersVars.cpp src/Pdf.cpp)
add_library(fittingsrc ${FITTING_SRC})
set(FITTING_LIBS ${FITTING_LIBS} fittingsrc)

#${variable} expands variable
add_executable(SaveRooDataSet src/SaveRooDataSet.cpp)
add_executable(Fitting src/Fitting.cpp)
add_executable(ToysTest src/ToysTest.cpp)

#Find all external code programme needs to run (ROOT normally finds itself)
#First argument = target
target_link_libraries(SaveRooDataSet ${FITTING_LIBS})
target_link_libraries(Fitting ${FITTING_LIBS})
target_link_libraries(ToysTest ${FITTING_LIBS})

