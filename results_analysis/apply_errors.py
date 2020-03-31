import math, re, os, sys
from ROOT import TFile, RooFitResult
import root_numpy as r_np
import numpy as np
import argparse

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '-i',
      '--input_dir',
      type=str,
      help='Directory where data and systematic results are stored',
      required=True)
  parser.add_argument(
      '-p',
      '--pull_dir',
      type=str,
      help=
      'Directory where results of pull distributions from 2D toys are stored',
      required=True)
  args = parser.parse_args()
  input_dir = args.input_dir
  pull_dir = args.pull_dir

  # Observables we are interested have this stem (match with regex)
  observables = [
      'N_tot_Bu2Dst0h', 'R_ADS_Bu2Dst0h', 'R_CP_Bu2Dst0h',
      'R_Dst0KDst0pi_Bu2Dst0h'
  ]
  # Dict to hold fit result and calculated errors of observables
  value_errs = {}
  # Dict to store values of observables from each systematic category
  syst_fit_results = {}

  # Extract data fit result (make not of box dimn for 2d toy pulls)
  # Extract value and fit error of each observable of interest
  if os.path.isdir(input_dir):
    os.chdir(input_dir)
    for f in os.listdir(input_dir):
      m = re.search('DataResult((?:_[0-9]+){4,6}).root', f)
      if m:
        box_string = group(1)
        data_file = TFile(f)
        data_result = data_file.Get('DataFitResult')
        for p in data_result.floatParsFinal():
          for obs in observables:
            par_name = p.GetName()
            m0 = re.search(obs + '(_[A-Za-z][0-9])+', par_name)
            if m0:
              value_errs[par_name[:-2]] = {
                  'Value': p.getVal(),
                  'Statstical Error': p.getError()
              }
              syst_fit_results[par_name[:-2]] = {}
  else:
    sys.exit(input_dir + ' does not exist.')

  if data_file == None:
    sys.exit('Data file does not exist.')

  # File where 2D pull results are stored
  pull_file = pull_dir + "/Result_" + box_string + ".root"
  tf_pull = TFile(pull_file)
  # Extract pull result for vars stored in value_errs dict and correct stat error with pull width
  for k, v in value_errs.items():
    pull_result = tf_pull.Get("Result_Pull_" + k)
    if pull_result == None:
      print("Could not extract Result_Pull_" + k + " from " + pull_file)
    else:
      pull_pars = pull_result.floatParsFinal()
      pull_width = pull_pars[1].getVal()
      v['Statistical Error'] = v['Statistical Error'] * pull_width

  # Loop over file storing results of systematically varied fits, and save observable final values in those that converged
  fits_status = {}
  if os.path.isdir(input_dir):
    for f in os.listdir(input_dir):
      m = re.search(
          'SystResult(?:_[0-9]+){4,6}((?:_[0-9A-Za-z]+)+)_0.[0-9]+.root', f)
      if m:
        syst_file = TFile(f)
        syst_result = syst_file.Get('SystResult')
        syst_label = m.group(1)[1:]
        if syst_label not in fits_status:
          fits_status[syst_label] = {'Failed': 0, 'Converged': 0}
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

  for s, f_c in fits_status.items():
    print("For " + s + ":\n\t Converged fits:\t" + str(f_c['Converged']) +
          "\t Failed fits:\t" + str(f_c['Failed']))

  # Calculate individual systematic errors from std dev of arrays on syst_fit results
  # Calculate total systematic error on an observable by taking the sum in quadrature of all std devs
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
  for par, val_errs in value_errs.items():
    print(par + " =\t" + str(val_errs['Value']) + " ± " +
          str(val_errs['Statstical Error']) + " ± " +
          str(val_errs['Systematic Error']))

  # file = open("../results/Yields_%s.tex" % years, "w")
  # file.write("\\begin{table}[t]\n")
  # file.write("\\centering\n")
  # file.write("\\begin{tabular}{l l l}\n")
  # file.write("\\hline\n")
  # file.write("Mode & Yield (full Dalitz) & Yield ($K^*(892)^\\pm$ region) \\\\ \\hline\n")
  # file.write("$N_{SS}^{D\\pipm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dpi_SS_N"],obs["n_dpi_SS_Y"]))
  # file.write("$N_{OS}^{D\\pipm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dpi_OS_N"],obs["n_dpi_OS_Y"]))
  # file.write("$N_{SS}^{D\\Kpm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dk_SS_N"],obs["n_dk_SS_Y"]))
  # file.write("$N_{OS}^{D\\Kpm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dk_OS_N"],obs["n_dk_OS_Y"]))
  # file.write("\\end{tabular}\n")
  # file.write("\\caption{Total signal yields measured in the full Dalitz and restricted $K^*(892)^\\pm$ region invariant mass fits.}\n")
  # file.write("\\label{tab:yields}\n")
  # file.write("\\end{table}")
  # file.close()
