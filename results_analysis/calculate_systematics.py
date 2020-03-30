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
  # Dict needs key of par name + ; syst label (separate after) --> needs to be unique !!
  # d = { obs_name : { syst_label : [] }
  if os.path.isdir(input_dir):
    os.chdir(input_dir)
    for f in os.listdir(input_dir):
      m = re.search('DataResult(?:_[0-9]+){4,6}.root', f)
      if m:
        data_file = TFile(f)
        data_result = data_file.Get('DataFitResult')
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


  fits_status = {}
  if os.path.isdir(input_dir):
    for f in os.listdir(input_dir):
      m = re.search('SystResult(?:_[0-9]+){4,6}((?:_[0-9A-Za-z]+)+)_0.[0-9]+.root', f)
      if m:
        syst_file = TFile(f)
        syst_result = syst_file.Get('SystResult')
        syst_label = m.group(1)[1:]
        if syst_label not in fits_status:
          fits_status[syst_label] = { 'Failed': 0, 'Converged': 0}
        if syst_result.covQual() == 3 and syst_result.status() == 0:
          fits_status[syst_label]['Converged'] += 1
          for p in syst_result.floatParsFinal():
            par_name = p.GetName()[:-2]
            if par_name in syst_fit_results:
              if syst_label in syst_fit_results[par_name]:
                syst_fit_results[par_name][syst_label].append(p.getVal())
              else:
                syst_fit_results[par_name][syst_label] = [p.getVal()]
        else:
          fits_status[syst_label]['Failed'] += 1

  syst_errs = {}
  for p, s_arr in syst_fit_results.items():
    tot_syst = 0
    syst_errs[p] = {}
    for s, arr in s_arr.items():
      np_arr = np.asarray(arr, dtype=np.float32)
      std = np.std(np_arr)
      syst_errs[p][s] = std
      tot_syst += std**2
    value_errs[p]['Systematic Error'] = tot_syst**0.5

  print()
  for par, syst in syst_errs.items():
    print(par + ":")
    for label, err in syst.items():
      print("\t" + label + ":\t" + str(err))
  print()

  print()
  print()

  for par, val_errs in value_errs.items():
    print(par + " =\t" + str(val_errs['Value']) + " ± " +
          str(val_errs['Statstical Error']) + " ± " + str(val_errs['Systematic Error']))

  print()
  print()

  for s, f_c in fits_status.items():
    print("For " + s + ":\n\t Converged fits:\t" + str(f_c['Converged']) + "\t Failed fits:\t" + str(f_c['Failed']))
