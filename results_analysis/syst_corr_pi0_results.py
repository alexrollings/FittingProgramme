import os, argparse, re, json, csv, sys
import pandas as pd
import numpy as np
from ROOT import TFile, RooFitResult
from useful_functions import return_label, neutral_label
from scipy.stats.stats import pearsonr

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-c',
                      '--commit',
                      type=str,
                      help='Commit',
                      required=True)
  args = parser.parse_args()

  commit = args.commit
  neutrals = ['pi0', 'gamma']

  df_total = pd.DataFrame(columns=['par', 'label', 'std', 'neutral'])
  for neutral in neutrals:
    syst_dir = f'/data/lhcb/users/rollings/systematics/{commit}/pik_split/{neutral}/'
    csv_totals_fname = f'{syst_dir}/format/systematics_totals_{neutral}.csv'
    if os.path.exists(csv_totals_fname):
      df_tmp = pd.read_csv(csv_totals_fname)
    else:
      sys.exit(f'Run calculate_result.py first: {csv_totals_fname} does not exist')
    df_tmp.drop(['group_label', 'group_rms', 'group_total'], axis=1, inplace=True)
    df_tmp['neutral'] = neutral
    if neutral == 'pi0':
      df_tmp['par'].replace({'A_Bu2Dst0h_D0pi0_pi0_k_kpi' : 'A_Bu2Dst0h_D0pi0_k_kpi'}, inplace=True)
    else:
      df_tmp['par'].replace({'A_Bu2Dst0h_D0pi0_gamma_k_kpi' : 'A_Bu2Dst0h_D0pi0_k_kpi'}, inplace=True)
    df_total = df_total.append(df_tmp)

  arr_pars = df_total['par'].unique().tolist()
  pars = [
      p for p in arr_pars if ("R_Dst0KDst0pi" not in p) and (
          "N_tot" not in p) and ("BR" not in p) and ("D0pi0" in p)
  ]
  par_dict = {}
  for neutral in neutrals:
    par_dict[neutral] = {}
    for par in pars:
      par_dict[neutral][par] = df_total[(df_total.neutral == neutral) & (
          df_total.par == par)]['std'].to_numpy()

  tex_path = os.path.join(os.getcwd(), 'tex_unblind/')
  if not os.path.exists(tex_path):
    os.mkdir(tex_path)

  syst_dict = {}
  f_tex = open(f'{tex_path}/syst_correlations_pi0_results.tex', 'w+')
  # f_tex.write('\\documentclass[12pt, landscape]{article}\n')
  # f_tex.write('\\usepackage[margin=0.1in]{geometry}\n')
  # f_tex.write('\\usepackage{mathtools}\n')
  # f_tex.write('\\usepackage{float}\n')
  # f_tex.write('\\usepackage{xcolor}\n')
  # f_tex.write('\\restylefloat{table}\n')
  # f_tex.write('\\begin{document}\n')
  # f_tex.write('\\begin{table}[t]\n')
  # f_tex.write('\t\\centering\n')
  # f_tex.write('\t\\footnotesize\n')
  # f_tex.write('\\resizebox{\\textwidth}{!}{%\n')
  format_str = 'c|' + 'c' * len(pars)
  f_tex.write('\t\\begin{tabular}{' + format_str + '}\n')
  f_tex.write('\t\t')
  for p_p in pars:
    f_tex.write(' & ' + return_label(p_p) + ' ' + neutral_label('pi0'))
  f_tex.write(' \\\\ \hline \n')
  for p_g in pars:
    f_tex.write(return_label(p_g) + ' ' + neutral_label('gamma'))
    second_half = False
    for p_p in pars:
      if p_p == p_g:
        second_half = True
      if second_half == True:
        corr = pearsonr(par_dict['gamma'][p_g],par_dict['pi0'][p_p])[0]
        f_tex.write(' & $%.2f$ ' % corr)
        # print(p_g + ' vs.' + p_p + ':\t' + str(corr))
        syst_dict['{p_g}_gamma,{p_p}_pi0'] = corr
      else:
        f_tex.write(' &  ')
    f_tex.write('\\\\ \n')
  f_tex.write('\t\\end{tabular}\n')
  # f_tex.write('}\n')
  # f_tex.write('\\end{table}\n')
  # f_tex.write('\\end{document}\n')

  json_fname_syst = f'json/syst_pi0_results.json'
  with open(json_fname_syst, 'w') as json_file_syst:
    json.dump(syst_dict, json_file_syst)
