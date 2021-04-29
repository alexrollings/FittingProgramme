## Overview

This repository stores the fitting code for the ADS/GLW analysis of fully reconstructed $`B^{\pm}\rightarrow D^{(*)}h^{\pm}`$ decays $`(h\in{\pi,K})`$ using 
the 2-body final states $`D \rightarrow K\pi, KK, \pi\pi, \pi K`$.

## EOS storage

All necessary inputs to the fit are stored at the following EOS location:

~~~
/eos/lhcb/wg/b2oc/AD-SGLW_Bu2Dst0h_FullReco_Run12
~~~

which houses the following sub-directories:

- `data_tuples` - contains the analysis nTuples with offline selections applied (apart from those specified in the fitting code). The root files are labelled by year, polarity and decay mode.
- `roodatasets` - contains roodatasets of the above nTuples, split by $`B`$ charge, to be read into the fit.
- `mc_roofit_results` - contains RooFit results of fits to MC, from which the value and error of fixed PDF parameters are read in.
- `efficiencies` - contains text files of MC selection efficiencies used to correct raw yields, and box efficiencies used to split the total yield for each component into each mass sample.
- `fixed_rates` - containt text files of fixed background rates (values and errors).

## Compiling executables 

Source the ROOT environment: 
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
This passes files to the SaveRooDataSets executablbe in `build`, whivh converts nTuple into roodatasets split by $`B`$ charge.
It is possible to pass a single root file or a directory containing multiple root diles, in which case all files 
in the directory will be converted. The directories that should be passed are stored at the EOS location as described above.

## Data fit

### Fit options 

Navigate into the `build` directory. The options to the fit are as follows (execute `./Fitting -help` in the command line 
to display this in the shell): 
~~~
-inputDir=<input directory name (where roodatasets, efficiencies, mc fit results are stored)>
-outputDir=<output directory (where the plots are saved in the `plots` sub-directory and results in the `results` sub-directory, therefore these should also be created)>
Pass box dimensions. Working points for Dgamma (Dπ0) mode given below:
  -dl=125(138) 
  -dh=170(148)
  -bl=5240(5220)
  -bh=5320(5330)
The Dgamma mode has a second B mass slice:
  -dpl=60
  -dph=105
Followed by the possible options (to specify multiple choices per option, pass them separated by commas):
  -1D: to only fit to B mass: default fit is double 1D
  -noFit: default is to fit PDF to data
  -simple: to plot all mis-reconstructed components as one color
  -unblind: default fit is blinded when split by charge 
  -year=<choice {2011,2012,2015,2016,2017,2018} default: 2011,2012,2015,2016,2017,2018>
  -polarity=<choice {up,down} default: up,down>
  -neutral=<choice {pi0/gamma} default: gamma>
  -daughters=<choice {kpi,kk,pipi,pik} default: kpi,kk,pipi,pik>
  -charge=<choice {plus,minus/total} default: total>
If running toys, the following argument must also be passed:
  -toys=<# of toys to run>
And a toy generation method specified:
  -pdfD1D: to run D1D toys generated from D1D PDF
  -data2D: to run 2D toys generated from RooHistPdf of data
If running systematics, the following arguments must also be passed:
  -systematic=<choice of category, default: None>
  -nSyst=<# of data fits to run for given category>
~~~

### Running the fit to data 

To run the split by charge blinded fit to the full $`D^{*}\rightarrow D\pi^{0}`$ dataset, execute:
~~~ 
./Fitting -inputDir=/eos/lhcb/wg/b2oc/AD-SGLW_Bu2Dst0h_FullReco_Run12/roodatasets/ -outputDir=<output path> -daughters=kpi,kk,pipi,pik -neutral=pi0 -charge=plus,minus -bl=5220 -bh=5330 -dl=138 -dh=148
~~~
To run the split by charge blinded fit to the full $`D^{*}\rightarrow D\gamma`$ dataset, execute:
~~~ 
./Fitting -inputDir=/eos/lhcb/wg/b2oc/AD-SGLW_Bu2Dst0h_FullReco_Run12/roodatasets/ -outputDir=<output path> -daughters=kpi,kk,pipi,pik -neutral=gamma -charge=plus,minus -bl=5240 -bh=5320 -dl=125 -dh=170 -dpl=60 -dph=105
~~~

### Running pseudo-experiments

In order to test fit bias and stability, pseudo-experiments should be run where the toy datasets are generated from 
the data fit model. To execute this, run the commands above as if running the fit to data, but add the options `-toys=<# to run> -pdfD1D`

In order to evaluate the statistical errors, corrected for double counting of events, pseudo-experiments must be run where 
toy datasets are generated from 2D RooHistPdfs of the data. The raw RooFit errors from the data fit are then multiplied by 
the widths of the 2D pull distributions. ~2500 experiments should be run to get reliable corrections. To execute this, 
run the commands above as if running the fit to data, but add the options `-toys=<# to run> -data2D`.

The `PlotToys` executable can be used fit to the pull distributions of all floating fit parameters to evaluate the 
means and widths. This can be called with the `plot_pulls.py` script in the `results_analysis` sub-directory. 
Example execution:
~~~
python plot_pulls.py -i=<directory where RooFitResults from pseudo-experiments are stored> -o=<directory where 
output plots and results should be created> -t=data -d=<2D/D1D> -n=<pi0/gamma>
~~~ 
The `-t=data` argument implies that the final result of the data fit should be used as the initial values of the 
observables in pull calculations. The dimension flag has options: `-d=2D/D1D`. The neutral flag has options: `-n=pi0/gamma`.

### Evaluating systematic uncertainties

In order to evaluate systematic uncertainties, run the command as if running the fit to data but with additional 
arguments `-systematic=<systematic category> -nSyst=<number of fits to run with systematic variation for given category>`.
Systematic categories that should be run for each data fit are listed in `shell_scripts/run_systematics.py`. 
This is a python script that generates submission scripts, from templates, to run systematic studies on the 
Oxford Particle Physics condor system. These should be edited for use on a different cluster.

### Final results

In order to calculate the final results, the `analyse_result.py` script in the `results_analysis` sub-directory can 
be used. To run, this requires Python v3 and the NumPy and Uncertainties packages:
~~~
python analyse_result.py -r=<file storing RooFitResult from the fit to data> -p=<file storing RooFitResults of 
fits to observable pull distributions from 2D toys> -s=<optional directory to systematics json file (see below)>
-n=<pi0/gamma> -c=<split/total> --blind
~~~
Where the inclusion of systematics and the specification of a blinded result are optional. This generates tex files 
containing tabulated results in LaTeX  format in the `tex` sub-directory.

If it is desired for systematics to be included, the results should be converted into json format before the above is 
carried out, by running the following script in the `results_analysis` sub-directory (Python v3 required):
~~~
python systematics_to_json.py -n=<pi0/gamma> -i=<input directory (identical to output directory passed when running the systematics fit)>
~~~

### Correlation matrices

The statistical correlation matrix for observables can be created in LaTeX format by running the following script 
in the `results_analysis` sub-directory:
~~~
python stat_corr_table.py -f=<file containing RooFitReuslt of fit to data> -n=<pi0/gamma>
~~~

The systematics correlation matrix for observables can be created in LaTeX format by running the following script 
in the `results_analysis` sub-directory:
~~~
python syst_corr_table.py -s=<directory where systematics json is stored> -n=<pi0/gamma>
~~~
