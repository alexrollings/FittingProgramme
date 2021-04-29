## Overview

This repository stores the fitting code for the ADS/GLW analysis of fully reconstructed $`B^{\pm}\rightarrow D^{(*)}h^{\pm}`$ decays $`(h\in{\pi,K})`$ using 
the 2-body final states $`D \rightarrow K\pi, KK, \pi\pi, \pi K`$.

## EOS storage

All necessary inputs to the fit are stored at the following EOS location:

~~
/eos/lhcb/wg/b2oc/AD-SGLW_Bu2Dst0h_FullReco_Run12
~~

which houses the following sub-directories:

- `data_tuples` - contains the analysis nTuples with offline selections applied (apart from those specified in the fitting code). The root files are labelled by year, polarity and decay and mode.
- `roodatasets` - contains roodatasets of the above nTuples, split by $`B`$ charge, to be read into the fit.
- `mc_roofit_results` - contains RooFit results of fits to MC, from which the value and error of fixed PDF parameters are read in.
- `efficiencies` - contains text files of MC selection efficiencies used to correct raw yields, and box efficiencies used to split the total yield for each component into each mass sample.
- `fixed_rates` - containt text files of fixed background rates (values and errors).

## Generating roodatasets

Navigate into the `src` directory, and source a Python environment (Python 2.7+). Run the following command:
~~
python LoopOverFiles.py <filename/directory>
~~
If a single root file is passed as an argument to the script, this will be converted into roodatasets split by $`B`$ charge. If a directory is passed, all files 
in the directory will be converted. The directory/files that should be passed are stored at the EOS location as described above.
