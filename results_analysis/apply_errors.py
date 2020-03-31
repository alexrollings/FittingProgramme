import math, re, os, sys
from ROOT import TFile, RooFitResult
import root_numpy as r_np
import numpy as np
import argparse
from useful_functions import return_label

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
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral: pi0/gamma',
                      required=True)
  args = parser.parse_args()
  input_dir = args.input_dir
  pull_dir = args.pull_dir
  neutral = args.neutral

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
        box_string = m.group(1)
        data_file = TFile(f)
        data_result = data_file.Get('DataFitResult')
        for p in data_result.floatParsFinal():
          for obs in observables:
            par_name = p.GetName()
            m0 = re.search(obs + '(_[A-Za-z][0-9])+', par_name)
            if m0:
              value_errs[par_name[:-2]] = {
                  'Value': p.getVal(),
                  'Statistical Error': p.getError()
              }
              syst_fit_results[par_name[:-2]] = {}
  else:
    sys.exit(input_dir + ' does not exist.')

  if data_file == None:
    sys.exit('Data file does not exist.')

  # File where 2D pull results are stored
  pull_file = pull_dir + "/Result" + box_string + ".root"
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
  if os.path.isdir(input_dir):
    for f in os.listdir(input_dir):
      m = re.search(
          'SystResult(?:_[0-9]+){4,6}((?:_[0-9A-Za-z]+)+)_0.[0-9]+.root', f)
      if m:
        syst_file = TFile(f)
        syst_result = syst_file.Get('SystResult')
        syst_label = m.group(1)[1:]
        if syst_result.covQual() == 3 and syst_result.status() == 0:
          for p in syst_result.floatParsFinal():
            par_name = p.GetName()[:-2]
            if par_name in syst_fit_results:
              if syst_label in syst_fit_results[par_name]:
                syst_fit_results[par_name][syst_label].append(p.getVal())
              else:
                syst_fit_results[par_name][syst_label] = [p.getVal()]

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

  # Print results in LaTeX table
  row_arr = []
  i = 0
  for par, val_errs in value_errs.items():
    val = val_errs['Value']
    stat = val_errs['Statistical Error']
    syst = val_errs['Systematic Error']
    results_str = f' & {val:.4f} & {stat:.4f} & {syst:.4f} \\\\\n'
    row_arr.append(return_label(par) + results_str)

  tex_file = open(
      f"/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex/Results_{neutral}.tex",
      "w")
  tex_file.write("\\documentclass[12pt, portrait]{article}\n")
  tex_file.write("\\usepackage[landscape, margin=0.1in]{geometry}\n")
  tex_file.write("\\usepackage{float}\n")
  tex_file.write("\\restylefloat{table}\n")
  tex_file.write("\\begin{document}\n")
  tex_file.write("\\begin{table}[t]\n")
  tex_file.write("\\centering\n")
  tex_file.write("\\begin{tabular}{l l l l}\n")
  tex_file.write("\\hline\n")
  tex_file.write(' & Value & Statistical Error & Systematic Error \\\\ \\hline\n')
  for row in row_arr:
    tex_file.write(row)
  tex_file.write("\\end{tabular}\n")
  tex_file.write("\\end{table}\n")
  tex_file.write("\\end{document}")
  tex_file.close()

