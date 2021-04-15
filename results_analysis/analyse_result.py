import math, re, os, sys
from ROOT import TFile, RooFitResult
import numpy as np
import root_numpy as r_np
from scipy import stats
import argparse
from useful_functions import return_label
from useful_functions import return_group_breakdown, return_final_group
import json
import operator
from uncertainties import ufloat
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt


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
  parser.add_argument('-r',
                      '--result',
                      type=str,
                      help='Data fit result',
                      required=True)
  parser.add_argument('-p',
                      '--pull_fname',
                      type=str,
                      help='Pull results from 2D toys',
                      required=True)
  parser.add_argument('-s',
                      '--syst_dir',
                      type=str,
                      help='Directory where json systematic is stored',
                      required=False)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral: pi0/gamma',
                      required=True)
  parser.add_argument('-c',
                      '--charge',
                      type=str,
                      help='Charge: split/total',
                      required=True)
  parser.add_argument('--blind',
                      dest='blind',
                      action='store_true',
                      required=False)
  parser.add_argument('--remake',
                      dest='remake',
                      action='store_true',
                      required=False)
  args = parser.parse_args()
  result = args.result
  syst_dir = args.syst_dir
  pull_fname = args.pull_fname
  neutral = args.neutral
  charge = args.charge
  blind = args.blind
  remake = args.remake

  if blind == True:
    blindStr = '_Blind'
  else:
    blindStr = ''

  if neutral == 'pi0':
    box_str = '138_148_5220_5330'
  else:
    box_str = '60_105_125_170_5240_5320'

  # Observables we are interested have this stem (match with regex)
  # Include BR in order to calc gamma π0 FAV yield
  observables = [
      'N_tot_Bu2Dst0h', 'R_piK_Bu2Dst0h', 'R_CP_Bu2Dst0h',
      'R_Dst0KDst0pi_Bu2Dst0h', 'A_Bu2Dst0h', 'A_CP_Bu2Dst0h', 'BR_pi02gamma_eff'
  ]

  # Dict to hold fit result and calculated errors of observables
  fit_result = {}
  # Dict to store values of observables from each systematic category
  syst_dict = {}
  # Dict to store systematic errors for grouped categories
  group_dict = {'final' : {}, 'breakdown' : {}}

  eval_systs = False
  if charge != 'total' and syst_dir != None:
    if not os.path.exists(syst_dir):
      sys.exit(f'{syst_dir} does not exist')
    eval_systs = True

  n_params = {'N': 0, 'R': 0, 'A': 0}
  # Extract data fit result (make not of box dimn for 2d toy pulls)
  # Extract value and fit error of each observable of interest
  if not os.path.isfile(result):
    sys.exit(f'{result} does not exist')
  data_file = TFile(result)
  data_result = data_file.Get('DataFitResult')
  if data_result == None:
    sys.exit(f'{data_file} does not contain DataFitResult')
  edm_fname = f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex_new/EDM_{charge}_{neutral}.tex'
  with open(edm_fname, 'w') as f_edm:
    edm_val = data_result.edm()
    edm_str = f'{edm_val:.2e}'
    edm_num = edm_str[:-4]
    edm_pow = str(int(edm_str[-2:]))
    f_edm.write('$' + edm_num + ' \\times 10^{-' + edm_pow + '}$')
  for obs in observables:
    for p in data_result.floatParsFinal():
      par_name = p.GetName()
      m0 = re.match(obs + '(_[A-Za-z0-9]+)+', par_name)
      if m0:
        # m1 = re.match('\S+Blind\S+', par_name)
        # if m1:
        #   value = 0
        # else:
        value = p.getVal()
        fit_result[par_name[:-2]] = {
            'Value': value,
            'Statistical Error': p.getError()
        }
        if par_name[0] != 'B':
          n_params[par_name[0]] += 1
        # No systematics for yields
        if obs != 'N_tot_Bu2Dst0h' and obs != 'BR_pi02gamma_eff':
          syst_dict[par_name[:-2]] = {}
          for g in group_dict:
            group_dict[g][par_name[:-2]] = {}

  raw_file = open(
      f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex_new/Result_raw_{charge}_{neutral}.tex',
      'w')
  row_arr = []
  sorted_pars = sorted(fit_result.keys(), key=lambda x: x.lower())
  if 'BR_pi02gamma_eff_gamma' in sorted_pars:
    sorted_pars.remove('BR_pi02gamma_eff_gamma')
  for par in sorted_pars:
    val = fit_result[par]['Value']
    stat = fit_result[par]['Statistical Error']
    if par[0] == 'N':
      continue
      # results_str = f' & {val:.0f} & {stat:.0f} & - \\\\\n'
    m1 = re.match('\S+Blind(\S+|$)', par)
    if m1:
      val_str = ''
      extra = ''
    else:
      if val > 0:
        extra = '\\textcolor{white}{-}'
      else:
        extra = ''
      val_str = f'{val:.4f}'
    results_str = f' &= {extra}{val_str} &&\\pm {stat:.4f} \\\\ \n'
    # Need to remove $$ at either end of string as going into align env
    row_arr.append(return_label(par)[1:-1] + results_str)

  for row in row_arr:
    raw_file.write(row)
  raw_file.close()

  # File where 2D pull results are stored
  pull_file = TFile(pull_fname)
  pull_widths = {}
  # Extract pull result for vars stored in fit_result dict and correct stat error with pull width
  for k, v in fit_result.items():
    pull_result = pull_file.Get(f'Result_Pull_{k}')
    if pull_result == None:
      m = re.match('(\S+_Bu2Dst0h_D0(pi0|gamma))(_\S+|$)', k)
      if m:
        blind_par = m.group(1) + '_Blind' + m.group(3)
        pull_result = pull_file.Get(f'Result_Pull_{blind_par}')
        if pull_result == None:
          print(
              f'Could not extract  Result_Pull_{k} or Result_Pull_{blind_par} from {pull_fname}'
          )
          continue
      else:
        continue
    pull_pars = pull_result.floatParsFinal()
    pull_width = pull_pars[1].getVal()
    v['Statistical Error'] = v['Statistical Error'] * pull_width
    m = re.match('\S+_D0(pi0|gamma)(_\S+|$)', k)
    if m:
      n = [m.group(1)]
    elif k == 'R_Dst0KDst0pi_Bu2Dst0h_kpi':
      if neutral == 'gamma':
        n = ['pi0', 'gamma']
      else:
        n = ['pi0']
    elif k == 'BR_pi02gamma_eff_gamma':
      n = ['pi0']
    else:
      sys.exit(k + ' doesn\'t match neutral regex')
    for neut in n:
      if neut not in pull_widths:
        pull_widths[neut] = [pull_width]
      else:
        pull_widths[neut].append(pull_width)

  # Systematic on error correction = RMS of all pull widths
  total_syst_dict = {}
  g_err_corr = 'Statistical Error Correction'
  for n, arr in pull_widths.items():
    np_widths = np.array(arr)
    rms = np.std(np_widths)
    print(rms)
    for g in group_dict:
      for p, v in group_dict[g].items():
        if p == 'R_Dst0KDst0pi_Bu2Dst0h_kpi' and neutral == 'gamma' and n == 'pi0':
          continue
        m = re.match(f'\S+_D0({n})(_\S+|$)', p)
        if m or p == 'R_Dst0KDst0pi_Bu2Dst0h_kpi' or (p == 'BR_pi02gamma_eff_gamma' and n == 'pi0'):
          v[g_err_corr] = rms * fit_result[p]['Statistical Error']
          total_syst_dict[p] = {}
          total_syst_dict[p][
              g_err_corr] = rms * fit_result[p]['Statistical Error']


  if eval_systs == True:
    # If json already exists for formatted systs, load this
    json_fname_format = f'{syst_dir}/systematics_{neutral}_format.json'
    if os.path.exists(json_fname_format) and remake == False:
      with open(json_fname_format, 'r') as json_file_format:
        syst_dict = json.load(json_file_format)
        status_fname = f'{syst_dir}/systematics_{neutral}_status.json'
        if os.path.exists(status_fname):
          with open(status_fname, 'r') as status_file:
            fit_status = json.load(status_file)
            # PrintFitStatus(fit_status)
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
        if syst_label == 'R_Dst0KDst0pi_Lb2Omegach_Lcpi0':
          continue
        fit_status[syst_label] = {
            'Total': 0,
            'Converged': 0,
            'MINOS': 0,
            'FPD': 0,
            'Unconverged': 0
        }
        for seed in json_dict[syst_label]:
          covQual = json_dict[syst_label][seed]['covQual']
          fitStatus = json_dict[syst_label][seed]['fitStatus']
          if covQual < 2:
            fit_status[syst_label]['Unconverged'] += 1
            # if syst_label == 'Bs2D0Kst0_PdfBu':
            # print(seed)
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
                  syst_dict[par][syst_label] = [[val, seed]]
                else:
                  syst_dict[par][syst_label].append([val, seed])
              else:
                sys.exit(f'{par} not in json_dict')
          else:
            print(
                f'Unknown fit status:\nCovariance matrix quality = {covQual}\tFit status = {fitStatus}'
            )
          fit_status[syst_label]['Total'] += 1
      # Save formatted systs and fot results to file
      with open(json_fname_format, 'w') as json_file_format:
        json.dump(syst_dict, json_file_format)
      status_fname = f'{syst_dir}/systematics_{neutral}_status.json'
      with open(status_fname, 'w') as status_file:
        json.dump(fit_status, status_file)
      PrintFitStatus(fit_status)

    # Calculate individual systematic errors from std dev of arrays in syst_dict
    # Calculate total systematic error on an observable by taking the sum in quadrature of all std devs
    # Dict to store dominant syst labels
    final_groups = []
    max_systs = {}
    for par, syst_arr in syst_dict.items():
      max_systs[par] = {'label': None, 'group': None}
      n_syst = len(syst_arr)
      tot_syst = 0
      for syst_label, arr in syst_arr.items():
        arr2d = np.array(arr)
        np_arr = np.asarray(arr2d[0:, 0], dtype=np.float32)
        seed_arr = arr2d[0:, 1]
        val = fit_result[par]['Value']
        stat = fit_result[par]['Statistical Error']
        init = len(np_arr)
        up = val + 3 * stat
        down = val - 3 * stat
        idxs_down = np.where(np_arr < down)
        idxs_up = np.where(np_arr > up)
        np_arr = np_arr[np_arr > down]
        np_arr = np_arr[np_arr < up]
        final = len(np_arr)
        # if syst_label == 'Bu2D0hst_PdfBu':
        if syst_label == 'Bs2D0Kst0_PdfDelta':
          t_df, t_m, t_s = stats.t.fit(np_arr)
          # print(par + ' v=' + str(t_df) + ' m=' + str(t_m) + ' s=' + str(t_s))
          # print(par + ' val=' + str(val) + ' std=' + str(stat))
          # print(par + ' ' + str((val-t_m)*100/val) + ' ' + str((t_s-stat)*100/stat))
          # init = len(np_arr)
          # up = t_m + 5 * t_s
          # down = t_m - 5 * t_s
          # np_arr = np_arr[np_arr > down]
          # np_arr = np_arr[np_arr < up]
          # final = len(np_arr)
          # print(par)
          # print((init - final)*100 / init)
          fig, ax = plt.subplots()
          ax.axes.get_yaxis().set_visible(False)
          # b = 10
          plt.hist(np_arr, bins='auto', density=True)
          # ax.axes.set_xlim([up, down])
          up, down = ax.axes.get_xlim()
          x = np.linspace(down, up, 50)
          t_distn = stats.t.pdf(x, t_df, t_m, t_s)
          plt.plot(x, t_distn)
          plt.xlabel(' ')
          plt.title(return_label(par))
          plt.savefig(syst_dir + '/histograms/' + par + '_' + syst_label +
                      '.png',
                      format='png')
          plt.clf()
        # if syst_label == 'Bs2D0Kst0_PdfDelta' and par == 'R_piK_Bu2Dst0h_D0gamma_Blind_k_minus':
        #   print(idxs_up)
        #   for idx in idxs_up:
        #     print(seed_arr[idx])
        #   print(par)
        #   print((init - final)*100 / init)
        std = np.std(np_arr)
        total_syst_dict[par][syst_label] = std
        tot_syst += std**2
        # Grouping errors
        group = {'final': return_final_group(syst_label), 'breakdown': return_group_breakdown(syst_label)}
        for g in group_dict:
          if group[g] in group_dict[g][par]:
            group_dict[g][par][group[g]] += std**2
          else:
            group_dict[g][par][group[g]] = std**2
        if group['final'] not in final_groups:
          final_groups.append(group['final'])
      # Could calculate final syst from either group
      tot_syst += group_dict['final'][par][g_err_corr]**2
      fit_result[par]['Systematic Error'] = tot_syst**0.5
      max_systs[par]['label'] = max(total_syst_dict[par].items(),
                                    key=operator.itemgetter(1))[0]
      for g in group_dict:
        for k, v in group_dict[g][par].items():
          if k != g_err_corr:
            # Sqrt sum in quadrature of individual errs
            group_dict[g][par][k] = v**0.5
      # Calculate max systs in breakdown
      max_systs[par]['group'] = max(group_dict['breakdown'][par].items(),
                                    key=operator.itemgetter(1))[0]

    # Separate tables for yields, ratios and asymmetries
    title_str = {'N': '', 'R': '', 'A': ''}
    row_arr = {'N': [], 'R': [], 'A': []}
    i = {'N': 0, 'R': 0, 'A': 0}
    for par, syst in total_syst_dict.items():
      key = par[0]
      title_str[key] = title_str[key] + ' & ' + return_label(par)
      j = {'N': 0, 'R': 0, 'A': 0}
      for s_label in sorted(syst):
        if i[key] == 0:
          # Replace _ with \_ in LaTeX
          row_arr[key].append(s_label.replace('_', '\\_'))
        err = syst[s_label]
        if max_systs[par]['label'] == s_label:
          err_str = ' & \\cellcolor{pink} '
        else:
          err_str = ' & '
        err_str += f'${err:.4f}$'
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
      tot_str = f' & ${syst_err:.4f}$'
      frac_str = f' & ${frac:.4f}$'
      row_arr[key][j[key] + 1] = row_arr[key][j[key] + 1] + tot_str
      row_arr[key][j[key] + 2] = row_arr[key][j[key] + 2] + frac_str
      if i[key] == (n_params[key] - 1):
        row_arr[key][j[key] + 1] = row_arr[key][j[key] + 1] + ' \\\\ \\hline\n'
        row_arr[key][j[key] +
                     2] = row_arr[key][j[key] + 2] + ' \\\\ \\hline\\hline\n'
      i[key] += 1

    title_str['N'] = title_str['N'] + ' \\\\ \\hline\n'
    title_str['R'] = title_str['R'] + ' \\\\ \\hline\n'
    title_str['A'] = title_str['A'] + ' \\\\ \\hline\n'

    tex_file = open(
        f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex_new/Systematics_{neutral}_new.tex',
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
      tex_file.write(
          '\\begin{adjustbox}{totalheight=\\textheight-2\\baselineskip}\n')
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
      tex_file.write(
          '\\begin{adjustbox}{totalheight=\\textheight-2\\baselineskip}\n')
      tex_file.write('\\begin{tabular}{' + 'l' * (n_params['A'] + 2) + '}\n')
      tex_file.write('\\hline\\hline\n')
      tex_file.write(title_str['A'])
      for row in row_arr['A']:
        tex_file.write(row)
      tex_file.write('\\end{tabular}\n')
      tex_file.write('\\end{adjustbox}\n')
      tex_file.write('\\end{table}\n')

    tex_file.write('\\end{document}')
    tex_file.close()

    letter = ['R', 'A']
    for l in letter:
      title_str = ''
      row_arr = []
      i = 0
      for par, g_err in group_dict['breakdown'].items():
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
            err_str += f'${err:.4f}$'
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
          tot_str = f' & ${syst_err:.4f}$'
          frac_str = f' & ${frac:.4f}$'
          row_arr[j + 1] = row_arr[j + 1] + tot_str
          row_arr[j + 2] = row_arr[j + 2] + frac_str
          if i == (n_params[l] - 1):
            row_arr[j + 1] = row_arr[j + 1] + ' \\\\ \\hline\n'
            row_arr[j + 2] = row_arr[j + 2] + ' \\\\ \\hline\\hline\n'
          i += 1

      title_str = title_str + ' \\\\ \\hline\n'

      if n_params[l] > 0:
        syst_file_1 = open(
            f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex_new/Systematics_breakdown_{l}_{neutral}.tex',
            'w')
        # syst_file_1.write('\\usepackage{tabularx}\n')
        # syst_file_1.write('\\begin{table}[t]\n')
        # syst_file_1.write('\\centering\n')
        # syst_file_1.write('\\small\n')
        if (neutral == 'pi0' and l == 'R') or (neutral == 'gamma' and l == 'A'):
          syst_file_1.write('\\begin{tabularx}{\\textwidth}{X' + 'l' * (n_params[l]) + '}\n')
        elif neutral == 'gamma' and l == 'R':
          syst_file_1.write('\\resizebox{.82\\paperheight}{!}{\n')
          syst_file_1.write('\\begin{tabular}{' + 'l' * (n_params[l] + 1) + '}\n')
        else:
          syst_file_1.write('\\begin{tabular}{' + 'l' * (n_params[l] + 1) + '}\n')
        syst_file_1.write('\\hline\\hline\n')
        syst_file_1.write(title_str)
        for row in row_arr:
          syst_file_1.write(row)
        if (neutral == 'pi0' and l == 'R') or (neutral == 'gamma' and l == 'A'):
          syst_file_1.write('\\end{tabularx}\n')
        elif neutral == 'gamma' and l == 'R':
          syst_file_1.write('\\end{tabular}\n')
          syst_file_1.write('}\n')
        else:
          syst_file_1.write('\\end{tabular}\n')
        # syst_file_1.write('\\end{table}\n')
        syst_file_1.close()

    title_str = 'Observable'
    for group in sorted(final_groups):
      title_str = title_str + ' & {' + group + '}'
    title_str = title_str + ' & {' + return_final_group(g_err_corr) + '} & {Total} \\\\ \\hline\n'
    row_arr = []
    i = 0
    for par, g_err in group_dict['final'].items():
      stat_err = fit_result[par]['Statistical Error']
      row_arr.append(return_label(par))
      for group in sorted(final_groups):
        err = (g_err[group]/stat_err)*100
        err_str = f' & {err:.2f}'
        row_arr[i] = row_arr[i] + err_str
      err = (g_err[g_err_corr]/stat_err)*100
      err_str = f' & {err:.2f}'
      row_arr[i] = row_arr[i] + err_str
      syst_err = fit_result[par]['Systematic Error']
      err = (syst_err/stat_err)*100
      err_str = f' & {err:.2f}'
      row_arr[i] = row_arr[i] + err_str + ' \\\\\n'
      i = i + 1

    syst_file_2 = open(
        f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex_new/Systematics_summary_{neutral}.tex',
        'w')
    # syst_file_2.write('\\begin{table}[t]\n')
    # syst_file_2.write('\\centering\n')
    # syst_file_2.write('\\small\n')
    # syst_file_2.write('\\begin{adjustbox}{max width=\\textwidth}\n')
    syst_file_2.write('\\begin{tabular}{l *{' + str(len(final_groups) + 2) + '}{S[table-format=2.2]}}\n')
    syst_file_2.write('\\hline\\hline\n')
    syst_file_2.write(title_str)
    for row in row_arr:
      syst_file_2.write(row)
    syst_file_2.write('\\hline\\hline\n')
    syst_file_2.write('\\end{tabular}\n')
    # syst_file_2.write('\\end{adjustbox}\n')
    # syst_file_2.write('\\end{table}\n')
    syst_file_2.close()

  result_file = open(
      f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex_new/Result_{charge}_{neutral}.tex',
      'w')
  row_arr = []
  sorted_pars = sorted(fit_result.keys(), key=lambda x: x.lower())
  if 'BR_pi02gamma_eff_gamma' in sorted_pars:
    sorted_pars.remove('BR_pi02gamma_eff_gamma')
  for par in sorted_pars:
    val = fit_result[par]['Value']
    stat = fit_result[par]['Statistical Error']
    if par[0] == 'N':
      continue
      # results_str = f' & {val:.0f} & {stat:.0f} & - \\\\\n'
    if eval_systs == True:
      syst = fit_result[par]['Systematic Error']
      syst_str = f'& &\\pm {syst:.4f} \\\\\n'
    else:
      syst_str = '\\\\\n'
    m1 = re.match('\S+Blind(\S+|$)', par)
    if m1:
      val_str = ''
      extra = ''
    else:
      if val > 0:
        extra = '\\textcolor{white}{-}'
      else:
        extra = ''
      val_str = f'{val:.4f}'
    results_str = f' &= {extra}{val_str} &&\\pm {stat:.4f} {syst_str}'
    # Need to remove $$ at either end of string as going into align env
    row_arr.append(return_label(par)[1:-1] + results_str)

  for row in row_arr:
    result_file.write(row)

  yields_file = open(
      f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex_new/Yields_{charge}_{neutral}.tex',
      'w')
  yields_file.write('\\begin{tabular}{lll}\n')
  yields_file.write('Decay & \\D mode & Yield \\\\ \n')
  yields_file.write('\\hline\n')
  yield_dict = {}

  if neutral == 'pi0':
    true_neutral = ['pi0']
  else:
    true_neutral = ['gamma', 'pi0']

  for n in true_neutral:
    yield_dict[n] = {'pi' : {}, 'k' : {} }
    daughters = ['kpi', 'kk', 'pipi']
    b = 'pi'

    if n == 'pi0' and neutral == 'gamma':
      N_gamma_name = f'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kpi'
      N_gamma = ufloat(fit_result[N_gamma_name]['Value'],
                       fit_result[N_gamma_name]['Statistical Error'])
      BR_name = 'BR_pi02gamma_eff_gamma'
      BR = ufloat(fit_result[BR_name]['Value'],
                  fit_result[BR_name]['Statistical Error'])
      branch_names = [
          'orEff_Bu2Dst0pi_D0pi0', 'orEffErr_Bu2Dst0pi_D0pi0',
          'boxEff_Bu2Dst0pi_D0pi0', 'boxEffErr_Bu2Dst0pi_D0pi0',
          'buEff_Bu2Dst0pi_D0pi0', 'buEffErr_Bu2Dst0pi_D0pi0',
          'deltaEff_Bu2Dst0pi_D0pi0', 'deltaEffErr_Bu2Dst0pi_D0pi0',
          'buPartialEff_Bu2Dst0pi_D0pi0', 'buPartialEffErr_Bu2Dst0pi_D0pi0',
          'orEff_Bu2Dst0pi_D0gamma', 'orEffErr_Bu2Dst0pi_D0gamma',
          'boxEff_Bu2Dst0pi_D0gamma', 'boxEffErr_Bu2Dst0pi_D0gamma',
          'buEff_Bu2Dst0pi_D0gamma', 'buEffErr_Bu2Dst0pi_D0gamma',
          'deltaEff_Bu2Dst0pi_D0gamma', 'deltaEffErr_Bu2Dst0pi_D0gamma',
          'buPartialEff_Bu2Dst0pi_D0gamma', 'buPartialEffErr_Bu2Dst0pi_D0gamma',
          'N_tot_Bu2Dst0pi_D0pi0_D02kpi_val', 'N_tot_Bu2Dst0pi_D0pi0_D02kpi_err'
      ]
      tree = r_np.root2array(result, 'tree', branch_names)
      pull_result = pull_file.Get(f'Result_Pull_{BR_name}')
      if pull_result == None:
        print(
            f'Could not extract  Result_Pull_{BR_name}'
        )
        pull_width = 1
      else:
        pull_pars = pull_result.floatParsFinal()
        pull_width = pull_pars[1].getVal()
      N_pi0 = ufloat(tree[0][20], tree[0][21] * pull_width)
      fit_result['N_tot_Bu2Dst0h_D0pi0_gamma_pi_kpi'] = {
          'Value': N_pi0.n,
          'Statistical Error': N_pi0.s
      }

    for d in daughters:
      N_pi = f'N_tot_Bu2Dst0h_D0{n}_{neutral}_{b}_{d}'
      val = fit_result[N_pi]['Value']
      stat = fit_result[N_pi]['Statistical Error']
      exp = math.sqrt(val)
      daughters_label = return_label(d)
      if d == 'kpi':
        decay_label = '\\multirow{4}{*}{' + return_label(f'Bu2Dst0{b}_D0{n}') + '}'
      else:
        decay_label = ''
      # yield_dict[n][b][d] = f'{decay_label} & {daughters_label} & ${val:.0f} \\pm {stat:.0f} ({exp:.0f})$ \\\\\n'
      yield_dict[n][b][d] = f'{decay_label} & {daughters_label} & ${val:.0f} \\pm {stat:.0f}$ \\\\\n'

    b = 'k'
    R_K_pi_name = f'R_Dst0KDst0pi_Bu2Dst0h_kpi'
    R_K_pi = ufloat(fit_result[R_K_pi_name]['Value'], fit_result[R_K_pi_name]['Statistical Error'])
    for d in daughters:
      N_pi_name = f'N_tot_Bu2Dst0h_D0{n}_{neutral}_pi_{d}'
      N_pi = ufloat(fit_result[N_pi_name]['Value'], fit_result[N_pi_name]['Statistical Error'])
      if d == 'kpi':
        decay_label = '\\multirow{4}{*}{' + return_label(f'Bu2Dst0{b}_D0{n}') + '}'
        R = R_K_pi
      else:
        decay_label = ''
        R_CP_name = f'R_CP_Bu2Dst0h_D0{n}{blindStr}'
        R_CP = ufloat(fit_result[R_CP_name]['Value'], fit_result[R_CP_name]['Statistical Error'])
        R = R_K_pi * R_CP
      N_K = N_pi * R
      val = N_K.n
      stat = N_K.s
      exp = math.sqrt(val)
      if d == 'kpi':
        N_K_kpi = ufloat(val, stat)
      if blind == True and d != 'kpi':
        valStr = 'X'
      else:
        valStr = f'{val:.0f}'
      daughters_label = return_label(d)
      # yield_dict[n][b][d] = f'{decay_label} & {daughters_label} & ${valStr} \\pm {stat:.0f} ({exp:.0f})$ \\\\\n'
      yield_dict[n][b][d] = f'{decay_label} & {daughters_label} & ${valStr} \\pm {stat:.0f}$ \\\\\n'

    bachelor = ['pi', 'k']
    for b in bachelor:
      if charge == 'total':
        R_piK_name = f'R_piK_Bu2Dst0h_D0{n}{blindStr}_{b}_total'
        R_piK = ufloat(fit_result[R_piK_name]['Value'], fit_result[R_piK_name]['Statistical Error'])
      else:
        R_piK_plus_name = f'R_piK_Bu2Dst0h_D0{n}{blindStr}_{b}_plus'
        R_piK_plus = ufloat(fit_result[R_piK_plus_name]['Value'], fit_result[R_piK_plus_name]['Statistical Error'])
        R_piK_minus_name = f'R_piK_Bu2Dst0h_D0{n}{blindStr}_{b}_minus'
        R_piK_minus = ufloat(fit_result[R_piK_minus_name]['Value'], fit_result[R_piK_minus_name]['Statistical Error'])
        R_piK = (R_piK_plus + R_piK_minus) / 2
      if b == 'pi':
        N_kpi_name = f'N_tot_Bu2Dst0h_D0{n}_{neutral}_{b}_kpi'
        N_kpi = ufloat(fit_result[N_kpi_name]['Value'], fit_result[N_kpi_name]['Statistical Error'])
      else:
        N_kpi = N_K_kpi
      N_pik = N_kpi * R_piK
      val = N_pik.n
      stat = N_pik.s
      exp = math.sqrt(val)
      if blind == True:
        valStr = 'X'
      else:
        valStr = f'{val:.0f}'
      daughters_label = return_label('pik')
      if n == 'pi0' and b == 'k':
        # yield_dict[n][b]['pik'] = f' & {daughters_label} & ${valStr} \\pm {stat:.0f} ({exp:.0f})$ \\\\\n'
        yield_dict[n][b]['pik'] = f' & {daughters_label} & ${valStr} \\pm {stat:.0f}$ \\\\\n'
      else:
        # yield_dict[n][b]['pik'] = f' & {daughters_label} & ${valStr} \\pm {stat:.0f} ({exp:.0f})$ \\\\ \\hline\n'
        yield_dict[n][b]['pik'] = f' & {daughters_label} & ${valStr} \\pm {stat:.0f}$ \\\\ \\hline\n'

  for n in true_neutral:
    for b in ['pi', 'k']:
      for d in ['kpi', 'kk', 'pipi', 'pik']:
        yields_file.write(yield_dict[n][b][d])
  yields_file.write('\\end{tabular}\n')


  if charge == 'split':
    json_fname_result = f'json/result_{neutral}.json'
    with open(json_fname_result, 'w') as json_file_result:
      json.dump(fit_result, json_file_result)
