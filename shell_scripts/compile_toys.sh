#!/bin/zsh
#PBS -l cput=01:59:59 
#PBS -N COMPILE_TOYS 

source /home/rollings/.zshrc
source_root

mkdir /data/lhcb/users/rollings/fitting_scripts/compile
cd /data/lhcb/users/rollings/fitting_scripts/compile

cp /home/rollings/Bu2Dst0h_2d/FittingProgramme/CMakeMacroParseArguments.cmake /data/lhcb/users/rollings/fitting_scripts/compile/CMakeMacroParseArguments.cmake 
cp /home/rollings/Bu2Dst0h_2d/FittingProgramme/FindROOT.cmake /data/lhcb/users/rollings/fitting_scripts/compile/FindROOT.cmake 
cp /home/rollings/Bu2Dst0h_2d/FittingProgramme/CMakeLists.txt /data/lhcb/users/rollings/fitting_scripts/compile/CMakeLists.txt 

mkdir src
cp /home/rollings/Bu2Dst0h_2d/FittingProgramme/src/*.cpp src/
mkdir include
cp /home/rollings/Bu2Dst0h_2d/FittingProgramme/include/* include/

mkdir build
cd build
cmake ../
make -j

cd /data/lhcb/users/rollings/fitting_scripts/
rm -rf /data/lhcb/users/rollings/fitting_scripts/compile
