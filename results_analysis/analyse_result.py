import math, re, os, sys
from ROOT import TFile, RooFitResult
import numpy as np
import argparse
from useful_functions import return_label
from useful_functions import return_group
import json
import operator

def PrintFitStatus(fit_status):
  for syst_label, status in fit_status.items():
    print(f'{syst_label}:\n')
    for status_label, tally in status.items():
      if status_label == 'Total':
        print(f'\t{status_label} : {tally}')
      else:
        perc = (tally / status['Total']) * 100
        print(f'\t{status_label} : {perc} %')
    print('\n')


if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '-s',
      '--syst_dir',
      type=str,
      help='Directory where json systematic is stored',
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
      required=False)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral: pi0/gamma',
                      required=True)
  args = parser.parse_args()
  syst_dir = args.syst_dir
  pull_dir = args.pull_dir
  neutral = args.neutral
  error_file = args.error_file

  if neutral == 'pi0':
    box_str = '138_148_5220_5330'
  else:
    box_str = '60_105_125_170_5240_5320'

  # Observables we are interested have this stem (match with regex)
  observables = [
      'N_tot_Bu2Dst0h', 'R_piK_Bu2Dst0h', 'R_CP_Bu2Dst0h',
      'R_Dst0KDst0pi_Bu2Dst0h', 'A_Bu2Dst0h', 'A_CP_Bu2Dst0h'
  ]

  # Dict to hold fit result and calculated errors of observables
  fit_result = {}
  # Dict to store values of observables from each systematic category
  syst_dict = {}
  # Dict to store systematic errors for grouped categories
  group_dict = {}

  # Extract data fit result (make not of box dimn for 2d toy pulls)
  # Extract value and fit error of each observable of interest
  if os.path.isdir(syst_dir):
    data_fname = f'{syst_dir}/results/DataResult_{box_str}.root'
    if not os.path.isfile(data_fname):
      sys.exit(f'{data_fname} does not exist')
    data_file = TFile(data_fname)
    data_result = data_file.Get('DataFitResult')
    for obs in observables:
      for p in data_result.floatParsFinal():
        par_name = p.GetName()
        m0 = re.match(obs + '(_[A-Za-z][0-9])+', par_name)
        if m0:
          m1 = re.match('\S+Blind\S+', par_name)
          if m1:
            value = 0
          else:
            value = p.getVal()
          fit_result[par_name[:-2]] = {
              'Value': value,
              'Statistical Error': p.getError()
          }
          syst_dict[par_name[:-2]] = {}
          group_dict[par_name[:-2]] = {}
  else:
    sys.exit(f'{syst_dir} does not exist')

  # File where 2D pull results are stored
  pull_fname = f'{pull_dir}/Result_{box_str}.root'
  pull_file = TFile(pull_fname)
  # Extract pull result for vars stored in fit_result dict and correct stat error with pull width
  for k, v in fit_result.items():
    pull_result = pull_file.Get(f'Result_Pull_{k}')
    if pull_result == None:
      print(f'Could not extract Result_Pull_{k} from {pull_fname}')
    else:
      pull_pars = pull_result.floatParsFinal()
      pull_width = pull_pars[1].getVal()
      v['Statistical Error'] = v['Statistical Error'] * pull_width

  # If json already exists for formatted systs, load this
  json_fname_format = f'{syst_dir}/systematics_{neutral}_format.json'
  if os.path.exists(json_fname_format):
    with open(json_fname_format, 'r') as json_file_format:
      syst_dict = json.load(json_file_format)
      status_fname = f'{syst_dir}/systematics_{neutral}_status.json'
      if os.path.exists(status_fname):
        with open(status_fname, 'r') as status_file:
          fit_status = json.load(status_file)
          PrintFitStatus(fit_status)
      else:
        sys.err(
            f'{status_fname} does not exist - cannot report on fit status')
  else:
    # Load in systematics from json
    json_fname = f'{syst_dir}/systematics_{neutral}.json'
    if os.path.exists(json_fname):
      with open(json_fname, 'r') as json_file:
        json_dict = json.load(json_file)
    else:
      sys.exit(f'{json_fname} does not exist')
    # Loop over json dict and sum up fit quality for each syst label
    fit_status = {}
    for syst_label in json_dict:
      fit_status[syst_label] = {'Total': 0, 'Converged' : 0, 'MINOS' : 0, 'FPD' : 0, 'Unconverged' : 0}
      for seed in json_dict[syst_label]:
        covQual = json_dict[syst_label][seed]['covQual']
        fitStatus = json_dict[syst_label][seed]['fitStatus']
        if covQual < 2:
          fit_status[syst_label]['Unconverged'] += 1
        elif covQual < 3:
          fit_status[syst_label]['FPD'] += 1
        elif fitStatus != 0:
          fit_status[syst_label]['MINOS'] += 1
        elif (covQual >= 3 and fitStatus == 0):
          fit_status[syst_label]['Converged'] += 1
          # If fit has good quality, save systematic results in syst_dict
          for par in syst_dict:
            if par in json_dict[syst_label][seed]:
              val = json_dict[syst_label][seed][par]
              if syst_label not in syst_dict[par]:
                syst_dict[par][syst_label] = [val]
              else:
                syst_dict[par][syst_label].append(val)
            else:
              sys.exit(f'{par} not in json_dict')
        else:
          print(f'Unknown fit status:\nCovariance matrix quality = {covQual}\tFit status = {fitStatus}')
        fit_status[syst_label]['Total'] += 1
    # Save formatted systs and fot results to file
    with open(json_fname_format, 'w') as json_file_format:
      json.dump(syst_dict, json_file_format)
    status_fname = f'{syst_dir}/systematics_{neutral}_status.json'
    with open(status_fname, 'w') as status_file:
      json.dump(fit_status, status_file)
    PrintFitStatus(fit_status)

  total_syst_dict = {}
  g_err_corr = 'Stat. Error Correction'
  # # Syst error from error correction: read in from file
  # if error_file != None:
  #   if os.path.exists(error_file):
  #     with open(error_file) as f:
  #       error_dict = dict(line.strip().split(',') for line in f)
  #     # print(error_dict)
  #     for p, v in group_dict.items():
  #       total_syst_dict[p] = {}
  #       if p in error_dict:
  #         v[g_err_corr] = float(error_dict[p]) * fit_result[p]['Statistical Error']
  #         total_syst_dict[p][g_err_corr] = float(error_dict[p]) * fit_result[p]['Statistical Error']
  #       else:
  #         v[g_err_corr] = 0.015 * fit_result[p]['Statistical Error']
  #         total_syst_dict[p][g_err_corr] = 0.015 * fit_result[p]['Statistical Error']
  #   else:
  #     print('No error file: calculating systematics with error correction')
  # If don't have box scan results yet, use 0.015 as placeholder (average RMS)
  # else:
  # Use average RMS as systematic for stat error correction
  for p, v in group_dict.items():
    v[g_err_corr] = 0.015 * fit_result[p]['Statistical Error']
    total_syst_dict[p] = {}
    total_syst_dict[p][g_err_corr] = 0.015 * fit_result[p]['Statistical Error']

  # Calculate individual systematic errors from std dev of arrays in syst_dict
  # Calculate total systematic error on an observable by taking the sum in quadrature of all std devs
  n_params = {'N' : 0, 'R': 0, 'A': 0}
  # Dict to store dominant syst labels
  max_systs = {}
  for par, syst_arr in syst_dict.items():
    max_systs[par] = {'label' : None, 'group' : None }
    n_params[par[0]] += 1
    n_syst = len(syst_arr)
    tot_syst = 0
    for syst_label, arr in syst_arr.items():
      np_arr = np.asarray(arr, dtype=np.float32)
      std = np.std(np_arr)
      total_syst_dict[par][syst_label] = std
      tot_syst += std**2
      # Grouping errors
      group = return_group(syst_label)
      if group in group_dict[par]:
        group_dict[par][group] += std**2
      else:
        group_dict[par][group] = std**2
    tot_syst += group_dict[par][g_err_corr]**2
    fit_result[par]['Systematic Error'] = tot_syst**0.5
    max_systs[par]['label'] = max(total_syst_dict[par].items(),
                                  key=operator.itemgetter(1))[0]
    for k, v in group_dict[par].items():
      if k != g_err_corr:
        # Sqrt sum in quadrature of individual errs
        group_dict[par][k] = v**0.5
    max_systs[par]['group'] = max(group_dict[par].items(),
                                  key=operator.itemgetter(1))[0]

  # Separate tables for yields, ratios and asymmetries
  title_str = { 'N' : '', 'R' : '' , 'A': ''}
  row_arr = { 'N' : [], 'R' : [], 'A': []}
  i = { 'N': 0, 'R': 0, 'A': 0}
  for par, syst in total_syst_dict.items():
    key = par[0]
    title_str[key] = title_str[key] + ' & ' + return_label(par)
    j = { 'N': 0, 'R': 0, 'A': 0}
    for s_label in sorted(syst):
      if i[key] == 0:
        # Replace _ with \_ in LaTeX
        row_arr[key].append(s_label.replace('_', '\\_'))
      err = syst[s_label]
      if max_systs[par]['label'] == s_label:
        err_str = ' & \\cellcolor{pink} '
      else:
        err_str = ' & '
      err_str += f'${err:.4g}$'
      row_arr[key][j[key]] = row_arr[key][j[key]] + err_str
      if i[key] == (n_params[key] - 1):
        row_arr[key][j[key]] = row_arr[key][j[key]] + ' \\\\\n'
      j[key] += 1
    if i[key] == 0:
      row_arr[key].append('\\hline\n')
      row_arr[key].append('$\\sigma(Syst.)$')
      row_arr[key].append('$\\frac{\\sigma(Syst.)}{\\sigma(Stat.)}$')
    syst_err = fit_result[par]['Systematic Error']
    stat_err = fit_result[par]['Statistical Error']
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
      f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex_new/Sytematics_{neutral}.tex',
      'w')
  tex_file.write('\\documentclass[12pt, portrait]{article}\n')
  tex_file.write('\\usepackage[margin=0.1in]{geometry}\n')
  tex_file.write('\\usepackage{graphicx}\n')
  tex_file.write('\\usepackage{adjustbox}\n')
  tex_file.write('\\usepackage[table]{xcolor}\n')
  tex_file.write('\\usepackage{float}\n')
  tex_file.write('\\restylefloat{table}\n')
  tex_file.write('\\begin{document}\n')
  # tex_file.write('\\begin{table}[t]\n')
  # tex_file.write('\\centering\n')
  # tex_file.write('\\begin{tabular}{' + 'l'*(n_params['N']+2) + '}\n')
  # tex_file.write('\\hline\\hline\n')
  # tex_file.write(title_str['N'])
  # for row in row_arr['N']:
  #   tex_file.write(row)
  # tex_file.write('\\end{tabular}\n')
  # tex_file.write('\\end{table}\n')
  if n_params['R'] > 0:
    tex_file.write('\\begin{table}[t]\n')
    tex_file.write('\\centering\n')
    tex_file.write('\\footnotesize\n')
    tex_file.write('\\begin{adjustbox}{totalheight=\\textheight-2\\baselineskip}\n')
    tex_file.write('\\begin{tabular}{' + 'l' * (n_params['R'] + 2) + '}\n')
    tex_file.write('\\hline\\hline\n')
    tex_file.write(title_str['R'])
    for row in row_arr['R']:
      tex_file.write(row)
    tex_file.write('\\end{tabular}\n')
    tex_file.write('\\end{adjustbox}\n')
    tex_file.write('\\end{table}\n')
  if n_params['A'] > 0:
    tex_file.write('\\begin{table}[t]\n')
    tex_file.write('\\centering\n')
    tex_file.write('\\footnotesize\n')
    tex_file.write('\\begin{adjustbox}{totalheight=\\textheight-2\\baselineskip}\n')
    tex_file.write('\\begin{tabular}{' + 'l' * (n_params['A'] + 2) + '}\n')
    tex_file.write('\\hline\\hline\n')
    tex_file.write(title_str['A'])
    for row in row_arr['A']:
      tex_file.write(row)
    tex_file.write('\\end{tabular}\n')
    tex_file.write('\\end{adjustbox}\n')
    tex_file.write('\\end{table}\n')

  letter = ['R', 'A']
  for l in letter:
    title_str = ''
    row_arr = []
    i = 0
    for par, g_err in group_dict.items():
      if par[0] == l:
        title_str = title_str + ' & ' + return_label(par)
        j = 0
        for g in sorted(g_err):
          if i == 0:
            row_arr.append(g)
          err = g_err[g]
          if max_systs[par]['group'] == g:
            err_str = ' & \\cellcolor{pink} '
          else:
            err_str = ' & '
          err_str += f'${err:.4g}$'
          row_arr[j] = row_arr[j] + err_str
          if i == (n_params[l] - 1):
            row_arr[j] = row_arr[j] + ' \\\\\n'
          j += 1
        if i == 0:
          row_arr.append('\\hline\n')
          row_arr.append('$\\sigma(Syst.)$')
          row_arr.append('$\\frac{\\sigma(Syst.)}{\\sigma(Stat.)}$')
        syst_err = fit_result[par]['Systematic Error']
        stat_err = fit_result[par]['Statistical Error']
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
      tex_file.write('\\begin{table}[t]\n')
      tex_file.write('\\centering\n')
      tex_file.write('\\small\n')
      tex_file.write('\\begin{adjustbox}{max width=\\textwidth}\n')
      tex_file.write('\\begin{tabular}{' + 'l'*(n_params[l]+2) + '}\n')
      tex_file.write('\\hline\\hline\n')
      tex_file.write(title_str)
      for row in row_arr:
        tex_file.write(row)
      tex_file.write('\\end{tabular}\n')
      tex_file.write('\\end{adjustbox}\n')
      tex_file.write('\\end{table}\n')

  row_arr = []
  for par, val_errs in fit_result.items():
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

  tex_file.write('\\begin{table}[t]\n')
  tex_file.write('\\centering\n')
  tex_file.write('\\begin{tabular}{l l l l}\n')
  tex_file.write('\\hline\\hline\n')
  tex_file.write(' & Value & Statistical Error & Systematic Error \\\\ \\hline\n')
  for row in row_arr:
    tex_file.write(row)
  tex_file.write('\\hline\\hline\n')
  tex_file.write('\\end{tabular}\n')
  tex_file.write('\\end{table}\n')
  tex_file.write('\\end{document}')
  tex_file.close()
