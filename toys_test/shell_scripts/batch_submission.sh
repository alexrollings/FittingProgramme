#!/bin/bash
#PBS -l cput=01:59:59 
#PBS -N TOYS 

export GCCROOT=/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GCCROOT/lib:$GCCROOT/lib64
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/
export CXX=$GCCROOT/bin/gcc

source /home/rollings/.zshrc.local
source /data/lhcb/sw/scripts/lbsetup-cvmfs.sh

source /cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/ROOT/6.08.06/x86_64-slc6-gcc49-opt/bin/thisroot.sh

cd /home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/
./ManySimToys /home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/toys_22_5505eef 1 plot
