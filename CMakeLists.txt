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
set(FITTING_SRC
    src/Configuration.cpp
    src/Efficiencies.cpp
    src/GammaVars.cpp
    src/GammaPiVars.cpp
    src/GammaKVars.cpp
    src/GlobalVars.cpp
    src/BachelorChargeVars.cpp
    src/BachelorVars.cpp
    src/NeutralBachelorDaughtersVars.cpp
    src/NeutralBachelorVars.cpp
    src/DaughtersVars.cpp
    src/NeutralVars.cpp
    src/Params.cpp
    src/ParseArguments.cpp
    src/Pdf.cpp
    src/Pdfs_GammaMinus.cpp
    src/Pdfs_GammaPlus.cpp
    src/Pdfs_GammaTotal.cpp
    src/Pdfs_Pi0Minus.cpp
    src/Pdfs_Pi0Plus.cpp
    src/Pdfs_Pi0Total.cpp
    src/Pi0KVars.cpp
    src/Pi0PiVars.cpp
    src/Pi0Vars.cpp
    src/RooCruijff.cpp
    src/Yields.cpp
    src/Plotting.cpp
    src/ToyFunctions.cpp)
add_library(fittingsrc ${FITTING_SRC})
set(FITTING_LIBS ${FITTING_LIBS} fittingsrc)

#${variable} expands variable
add_executable(Fitting src/Fitting.cpp)
# add_executable(PlotToys src/PlotToys.cpp)
# add_executable(SaveRooDataSets src/SaveRooDataSets.cpp)

#Find all external code programme needs to run (ROOT normally finds itself)
#First argument = target
target_link_libraries(Fitting ${FITTING_LIBS} stdc++fs)
# target_link_libraries(PlotToys ${FITTING_LIBS} stdc++fs)
# target_link_libraries(SaveRooDataSets ${FITTING_LIBS} stdc++fs)
