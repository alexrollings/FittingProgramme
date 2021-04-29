## Overview

This repository stores the fitting code for the ADS/GLW analysis of fully reconstructed $`B^{\pm}\rightarrow D^{(*)}h^{\pm}`$ decays $`(h\in{\pi,K})`$ using 
the 2-body final states $`D \rightarrow K\pi, KK, \pi\pi, \pi K`$.

## EOS storage

All necessary inputs to the fit are stored at the following EOS location:

~~~
/eos/lhcb/wg/b2oc/AD-SGLW_Bu2Dst0h_FullReco_Run12
~~~

which houses the following sub-directories:

- `data_tuples` - contains the analysis nTuples with offline selections applied (apart from those specified in the fitting code). The root files are labelled by year, polarity and decay and mode.
- `roodatasets` - contains roodatasets of the above nTuples, split by $`B`$ charge, to be read into the fit.
- `mc_roofit_results` - contains RooFit results of fits to MC, from which the value and error of fixed PDF parameters are read in.
- `efficiencies` - contains text files of MC selection efficiencies used to correct raw yields, and box efficiencies used to split the total yield for each component into each mass sample.
- `fixed_rates` - containt text files of fixed background rates (values and errors).

## Compiling executables 

Source the CERN ROOT environment: 
~~~
source /cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/ROOT/6.08.06/x86_64-slc6-gcc62-opt/bin/thisroot.sh
~~~
Make a `build` directory and navigate into it. Run the commands:
~~~
cmake ../
make (optional -j)
~~~
You should then have the following executables in the `build` directory:
~~~
SaveRooDataSets
Fitting
PlotToys
~~~

## Generating roodatasets

Navigate into the `src` directory and run the following command (requires Python v2.7+):
~~~
python LoopOverFiles.py <nTuple directory/filename> <output roodataset directory>
~~~
If a single root file is passed as an argument to the script, this will be converted into roodatasets split by $`B`$ charge. If a directory is passed, all files 
in the directory will be converted. The directories that should be passed are stored at the EOS location as described above.

## Fit options 

Navigate into the `build` directory. The options to the fit are as follows (execute `./Fitting -help` in the command line 
to display this in the shell): 
~~~
-inputDir=<input directory name (where roodatasets, efficiencies, mc fit results are stored)>
-outputDir=<output directory (where the plots are saved in the `plots` sub-directory and results in the `results` sub-directory, therefore these should also be created)>
Pass box dimensions. Working points for $`D^{*}\rightarrow D\gamma`$ ($`D^{*}\rightarrow D\pi^{0}`$) mode given below:
  -dl=125(138) 
  -dh=170(148)
  -bl=5240(5220)
  -bh=5320(5330)
The $`D\gamma`$ mode has a second $`B`$ mass slice:
  -dpl=60
  -dph=105
Followed by the possible options (to specify multiple choices per option, pass them separated by commas):
  -1D, to only git to $`B`$ mass: default fit is double 1D
  -noFit, default is to fit PDF to data
  -simple, to plot all mis-reconstructed components as one color
  -unblind, default is blinded
  -year=<choice {2011,2012,2015,2016,2017,2018} default: 2011,2012,2015,2016,2017,2018>
  -polarity=<choice {up,down} default: up,down>
  -neutral=<choice {pi0/gamma} default: gamma>
  -daughters=<choice {kpi,kk,pipi,pik} default: kpi,kk,pipi,pik>
  -charge=<choice {plus,minus/total} default: total>
  -toys=<# of toys to run>
  -pdfD1D, to run D1D toys generated from D1D PDF
  -pdf2D, to run 2D toys generated from 2D PDF
  -data2D, to run 2D toys generated from RooHistPdf of data
  -data1D, to run independent 1D toys generated from RooHistPdf of data.
  -systematic=<choice of category, default: None>
  -nSyst=<# data fits to run for systematic studies>
~~~
## Running the fit to data 
To run the split by charge blinded fit to the full $`D^{*}\rightarrow D\pi^{0}`$ dataset, execute:
~~~ 
./Fitting -inputDir=/eos/lhcb/wg/b2oc/AD-SGLW_Bu2Dst0h_FullReco_Run12/roodatasets/ -outputDir=<output path> -daughters=kpi,kk,pipi,pik -neutral=pi0 -charge=plus,minus -bl=5220 -bh=5330 -dl=138 -dh=148
~~~
To run the split by charge blinded fit to the full $`D^{*}\rightarrow D\gamma`$ dataset, execute:
~~~ 
./Fitting -inputDir=/eos/lhcb/wg/b2oc/AD-SGLW_Bu2Dst0h_FullReco_Run12/roodatasets/ -outputDir=<output path> -daughters=kpi,kk,pipi,pik -neutral=gamma -charge=plus,minus -bl=5240 -bh=5320 -dl=125 -dh=170 -dpl=60 -dph=105
~~~
