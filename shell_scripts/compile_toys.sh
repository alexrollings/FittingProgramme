#!/bin/zsh
#PBS -l cput=01:59:59 
#PBS -N COMPILE_TOYS 

source /home/rollings/.zshrc
source_root

mkdir /data/lhcb/users/rollings/fitting_scripts/compile
cd /data/lhcb/users/rollings/fitting_scripts/compile

cp /home/rollings/Bu2Dst0hd/FittingProgramme/CMakeMacroParseArguments.cmake /data/lhcb/users/rollings/fitting_scripts/compile/CMakeMacroParseArguments.cmake 
cp /home/rollings/Bu2Dst0hd/FittingProgramme/FindROOT.cmake /data/lhcb/users/rollings/fitting_scripts/compile/FindROOT.cmake 
cp /home/rollings/Bu2Dst0hd/FittingProgramme/CMakeLists.txt /data/lhcb/users/rollings/fitting_scripts/compile/CMakeLists.txt 

mkdir src
cp /home/rollings/Bu2Dst0hd/FittingProgramme/src/*.cpp src/
mkdir include
cp /home/rollings/Bu2Dst0hd/FittingProgramme/include/* include/

mkdir build
cd build
cmake ../
make -j

# cd /data/lhcb/users/rollings/fitting_scripts/
# rm -rf /data/lhcb/users/rollings/fitting_scripts/compile
