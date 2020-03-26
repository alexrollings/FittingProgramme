import math, re, os, sys
from ROOT import TFile, RooFitResult
import root_numpy as r_np
import numpy as np
import argparse


if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-i',
                      '--input_dir',
                      type=str,
                      help='Input: systematic results',
                      required=True)
  args = parser.parse_args()
  input_dir = args.input_dir

  observables = ['N_tot_Bu2Dst0h', 'R_ADS_Bu2Dst0h', 'R_CP_Bu2Dst0h', 'R_Dst0KDst0pi_Bu2Dst0h']
  value_errs = {}
  syst_fit_results = {}

  if os.path.isdir(input_dir):
    os.chdir(input_dir)
    for f in os.listdir(input_dir):
      m = re.search('DataResult(?:_[0-9]+){4,6}.root', f)
      if m:
        data_file = TFile(f)
        data_result = data_file.Get('DataFitResult')
        data_result.Print()
        for p in data_result.floatParsFinal():
          for obs in observables:
            par_name = p.GetName()
            m0 = re.search(obs + '(_[A-Za-z][0-9])+', par_name)
            if m0:
              value_errs[par_name[:-2]] = { 'Value' : p.getVal(), 'Statstical Error': p.getError() }
              syst_fit_results[par_name[:-2]] = {}
  else:
    sys.exit(input_dir + ' does not exist.')

  if data_file == None:
    sys.exit('Data file does not exist.')

  if os.path.isdir(input_dir):
    for f in os.listdir(input_dir):
      m = re.search('SystResult(?:_[0-9]+){4,6}((?:_[A-Za-z]+)+)_0.[0-9]+.root', f)
      if m:
        syst_file = TFile(f)
        syst_result = syst_file.Get('SystResult')
        syst_label = m.group(1)[1:]
        for p in syst_result.floatParsFinal():
          for obs, v in syst_fit_results.items():
            if obs == p.GetName()[:-2]:
              if syst_label in v:
                v[syst_label].append(p.getVal())
              else:
                v[syst_label] = [p.getVal()]

  syst_fit_results[obs][syst_label] = np.asarray(syst_fit_results[obs][syst_label], dtype=np.float32)
  syst_errs = {}
  for obs, v in syst_fit_results.items():
    tot_syst = 0
    for syst, arr in v.items():
      std = np.std(arr)
      syst_errs[obs] = { syst : std }
      tot_syst += std**2
    tot_syst = tot_syst**0.5
    value_errs[obs]['Systematic Error'] = tot_syst

  print(syst_errs)
  print()
  print(value_errs)

