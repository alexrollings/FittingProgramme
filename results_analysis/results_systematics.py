import math, re, os, sys
from ROOT import TFile, RooFitResult
import root_numpy as r_np
import numpy as np
import argparse
from useful_functions import return_label
from useful_functions import return_group

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
  parser.add_argument(
      '-e',
      '--error_file',
      type=str,
      help=
      'File where systematics from error correction are stored',
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
  error_file = args.error_file

  # Observables we are interested have this stem (match with regex)
  observables = [
      'N_tot_Bu2Dst0h', 'R_ADS_Bu2Dst0h', 'R_CP_Bu2Dst0h',
      'R_Dst0KDst0pi_Bu2Dst0h', 'A_Bu2Dst0h'
  ]
  # Dict to hold fit result and calculated errors of observables
  value_errs = {}
  # Dict to store values of observables from each systematic category
  syst_fit_results = {}
  # Dict to store systematic errors for grouped categories
  grouped_errs = {}

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
              if obs == 'R_ADS_Bu2Dst0h' or obs == 'R_CP_Bu2Dst0h' or obs == 'A_Bu2Dst0h':
                value = 0
              else:
                value = p.getVal()
              value_errs[par_name[:-2]] = {
                  'Value': value,
                  'Statistical Error': p.getError()
              }
              syst_fit_results[par_name[:-2]] = {}
              grouped_errs[par_name[:-2]] = {}
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

  syst_errs = {}

  # Syst error from error correction: read in from file
  g_err_corr = 'Stat. Error Correction'
  if os.path.exists(error_file):
    with open(error_file) as f:
      error_dict = dict(line.strip().split(',') for line in f)
    # print(error_dict)
    for p, v in grouped_errs.items():
      syst_errs[p] = {}
      if p in error_dict:
        v[g_err_corr] = float(error_dict[p]) * value_errs[p]['Statistical Error']
        syst_errs[p][g_err_corr] = float(error_dict[p]) * value_errs[p]['Statistical Error']
      else:
        v[g_err_corr] = 0.
        syst_errs[p][g_err_corr] = 0.
  else:
    print('No error file: calculating systematics with error correction')

  # Calculate individual systematic errors from std dev of arrays on syst_fit results
  # Calculate total systematic error on an observable by taking the sum in quadrature of all std devs
  n_params = {'N' : 0, 'R': 0, 'A': 0}
  for p, s_arr in syst_fit_results.items():
    key = p[0]
    n_params[key] += 1
    n_syst = len(s_arr)
    tot_syst = 0
    for s, arr in s_arr.items():
      np_arr = np.asarray(arr, dtype=np.float32)
      std = np.std(np_arr)
      syst_errs[p][s] = std
      tot_syst += std**2
      # Grouping errors
      group = return_group(s)
      if group in grouped_errs[p]:
        grouped_errs[p][group] += std**2
      else:
        grouped_errs[p][group] = std**2
    tot_syst += grouped_errs[p][g_err_corr]**2
    value_errs[p]['Systematic Error'] = tot_syst**0.5
    for k, v in grouped_errs[p].items():
      if k != g_err_corr:
        grouped_errs[p][k] = v**0.5

  title_str = { 'N' : "", 'R' : "" , 'A': ""}
  row_arr = { 'N' : [], 'R' : [], 'A': []}
  i = { 'N': 0, 'R': 0, 'A': 0}
  for par, syst in syst_errs.items():
    key = par[0]
    title_str[key] = title_str[key] + ' & ' + return_label(par)
    j = { 'N': 0, 'R': 0, 'A': 0}
    for s_label in sorted(syst):
      if i[key] == 0:
        row_arr[key].append(s_label)
      err = syst[s_label]
      err_str = f' & ${err:.4g}$'
      row_arr[key][j[key]] = row_arr[key][j[key]] + err_str
      if i[key] == (n_params[key] - 1):
        row_arr[key][j[key]] = row_arr[key][j[key]] + ' \\\\\n'
      j[key] += 1
    if i[key] == 0:
      row_arr[key].append('\\hline\n')
      row_arr[key].append('$\\sigma(Syst.)$')
      row_arr[key].append('$\\frac{\\sigma(Syst.)}{\\sigma(Stat.)}$')
    syst_err = value_errs[par]['Systematic Error']
    stat_err = value_errs[par]['Statistical Error']
    frac = syst_err / stat_err
    tot_str = f' & ${syst_err:.4g}$'
    frac_str = f' & ${frac:.4g}$'
    row_arr[key][j[key]+1] = row_arr[key][j[key]+1] + tot_str
    row_arr[key][j[key]+2] = row_arr[key][j[key]+2] + frac_str
    if i[key] == (n_params[key] - 1):
      row_arr[key][j[key]+1] = row_arr[key][j[key]+1] + ' \\\\ \\hline\n'
      row_arr[key][j[key]+2] = row_arr[key][j[key]+2] + ' \\\\ \\hline\\hline\n'
    i[key] += 1

  title_str['N'] = title_str['N'] + ' \\\\ \\hline\n'
  title_str['R'] = title_str['R'] + ' \\\\ \\hline\n'
  title_str['A'] = title_str['A'] + ' \\\\ \\hline\n'

  tex_file = open(
      f"/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex/Sytematics_{neutral}.tex",
      "w")
  tex_file.write("\\documentclass[12pt, portrait]{article}\n")
  tex_file.write("\\usepackage[landscape, margin=0.1in]{geometry}\n")
  tex_file.write("\\usepackage{float}\n")
  tex_file.write("\\restylefloat{table}\n")
  tex_file.write("\\begin{document}\n")
  # tex_file.write("\\begin{table}[t]\n")
  # tex_file.write("\\centering\n")
  # tex_file.write("\\begin{tabular}{" + "l"*(n_params['N']+2) + "}\n")
  # tex_file.write("\\hline\\hline\n")
  # tex_file.write(title_str['N'])
  # for row in row_arr['N']:
  #   tex_file.write(row)
  # tex_file.write("\\end{tabular}\n")
  # tex_file.write("\\end{table}\n")
  if n_params['R'] > 0:
    tex_file.write("\\begin{table}[t]\n")
    tex_file.write("\\centering\n")
    tex_file.write("\\small\n")
    tex_file.write("\\begin{tabular}{" + "l"*(n_params['R']+2) + "}\n")
    tex_file.write("\\hline\\hline\n")
    tex_file.write(title_str['R'])
    for row in row_arr['R']:
      tex_file.write(row)
    tex_file.write("\\end{tabular}\n")
    tex_file.write("\\end{table}\n")
  if n_params['A'] > 0:
    tex_file.write("\\begin{table}[t]\n")
    tex_file.write("\\centering\n")
    tex_file.write("\\small\n")
    tex_file.write("\\begin{tabular}{" + "l"*(n_params['A']+2) + "}\n")
    tex_file.write("\\hline\\hline\n")
    tex_file.write(title_str['A'])
    for row in row_arr['A']:
      tex_file.write(row)
    tex_file.write("\\end{tabular}\n")
    tex_file.write("\\end{table}\n")

  letter = ['R', 'A']
  for l in letter:
    title_str = ''
    row_arr = []
    i = 0
    for par, g_err in grouped_errs.items():
      if par[0] == l:
        title_str = title_str + ' & ' + return_label(par)
        j = 0
        for g in sorted(g_err):
          if i == 0:
            row_arr.append(g)
          err = g_err[g]
          err_str = f' & ${err:.4g}$'
          row_arr[j] = row_arr[j] + err_str
          if i == (n_params[l] - 1):
            row_arr[j] = row_arr[j] + ' \\\\\n'
          j += 1
        if i == 0:
          row_arr.append('\\hline\n')
          row_arr.append('$\\sigma(Syst.)$')
          row_arr.append('$\\frac{\\sigma(Syst.)}{\\sigma(Stat.)}$')
        syst_err = value_errs[par]['Systematic Error']
        stat_err = value_errs[par]['Statistical Error']
        frac = syst_err / stat_err
        tot_str = f' & ${syst_err:.4g}$'
        frac_str = f' & ${frac:.4g}$'
        row_arr[j+1] = row_arr[j+1] + tot_str
        row_arr[j+2] = row_arr[j+2] + frac_str
        if i == (n_params[l] - 1):
          row_arr[j+1] = row_arr[j+1] + ' \\\\ \\hline\n'
          row_arr[j+2] = row_arr[j+2] + ' \\\\ \\hline\\hline\n'
        i += 1

    title_str = title_str + ' \\\\ \\hline\n'

    if n_params[l] > 0:
      tex_file.write("\\begin{table}[t]\n")
      tex_file.write("\\centering\n")
      tex_file.write("\\begin{tabular}{" + "l"*(n_params[l]+2) + "}\n")
      tex_file.write("\\hline\\hline\n")
      tex_file.write(title_str)
      for row in row_arr:
        tex_file.write(row)
      tex_file.write("\\end{tabular}\n")
      tex_file.write("\\end{table}\n")

  row_arr = []
  for par, val_errs in value_errs.items():
    val = val_errs['Value']
    stat = val_errs['Statistical Error']
    syst = val_errs['Systematic Error']
    if val == 0:
      results_str = f' & X & {stat:.4g} & {syst:.4g} \\\\\n'
    else:
      if par[0] == 'N':
        results_str = f' & {val:.4g} & {stat:.4g} & - \\\\\n'
      else:
        results_str = f' & {val:.4g} & {stat:.4g} & {syst:.4g} \\\\\n'
    row_arr.append(return_label(par) + results_str)

  tex_file.write("\\begin{table}[t]\n")
  tex_file.write("\\centering\n")
  tex_file.write("\\begin{tabular}{l l l l}\n")
  tex_file.write("\\hline\\hline\n")
  tex_file.write(' & Value & Statistical Error & Systematic Error \\\\ \\hline\n')
  for row in row_arr:
    tex_file.write(row)
  tex_file.write("\\hline\\hline\n")
  tex_file.write("\\end{tabular}\n")
  tex_file.write("\\end{table}\n")
  tex_file.write("\\end{document}")
  tex_file.close()

