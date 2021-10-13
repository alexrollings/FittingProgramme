import numpy as np
import uncertainties as u
import json, csv, os
import pandas as pd
from useful_functions import neutral_label, bachelor_label

neutral = ['pi0', 'gamma']

path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/'

a_dict = {}
r_dict = {}
for n in neutral:
  csv_result_fname = f'{path}/tex_unblind/result_split_{n}.csv'
  if os.path.exists(csv_result_fname):
    df_result = pd.read_csv(csv_result_fname)
  else:
    sys.exit(f'{csv_result_fname} does not exist')

  json_fname_syst = f'{path}/json/syst_{n}.json'
  if os.path.exists(json_fname_syst):
    with open(json_fname_syst, 'r') as syst_file:
      syst_dict = json.load(syst_file)
  else:
    sys.exit(f'{json_fname_syst} does not exist')

  json_fname_stat = f'{path}/json/stat_{n}.json'
  if os.path.exists(json_fname_stat):
    with open(json_fname_stat, 'r') as stat_file:
      stat_dict = json.load(stat_file)
  else:
    sys.exit(f'{json_fname_stat} does not exist')

  a_dict[n] = {}
  r_dict[n] = {}
  for true_n in neutral:
    if n == 'pi0' and true_n == 'gamma':
      continue
    for b in ['pi', 'k']:
      minus_str = f'R_piK_Bu2Dst0h_D0{true_n}_{b}_minus'
      plus_str = f'R_piK_Bu2Dst0h_D0{true_n}_{b}_plus'
      vals = np.array([
          df_result[(df_result.par == minus_str)]['val'].values[0],
          df_result[(df_result.par == plus_str)]['val'].values[0]
      ])

      stat_err = np.array([
          df_result[(df_result.par == minus_str)]['stat'].values[0],
          df_result[(df_result.par == plus_str)]['stat'].values[0]
      ])
      stat_corr = np.array([[
          stat_dict[f'{minus_str},{minus_str}'], stat_dict[f'{minus_str},{plus_str}']
      ], [stat_dict[f'{minus_str},{plus_str}'],
          stat_dict[f'{plus_str},{plus_str}']]])
      err_matrix = np.outer(stat_err, stat_err)
      stat_cov = np.multiply(err_matrix, stat_corr)

      syst_err = np.array([
          df_result[(df_result.par == minus_str)]['syst'].values[0],
          df_result[(df_result.par == plus_str)]['syst'].values[0]
      ])
      syst_corr = np.array([[
          syst_dict[f'{minus_str},{minus_str}'], syst_dict[f'{minus_str},{plus_str}']
      ], [syst_dict[f'{minus_str},{plus_str}'],
          syst_dict[f'{plus_str},{plus_str}']]])
      err_matrix = np.outer(syst_err, syst_err)
      syst_cov = np.multiply(err_matrix, syst_corr)

      total_cov = stat_cov + syst_cov

      (r_minus, r_plus) = np.asarray(u.correlated_values(vals, total_cov))
      r_ads = (r_minus + r_plus)/2.
      a_ads = (r_minus - r_plus)/(r_minus + r_plus)
      r_dict[n][f'{true_n}_{b}'] = r_ads
      a_dict[n][f'{true_n}_{b}'] = a_ads

print(r_dict)
print(a_dict)

stat_corr = np.array([[1., 0.], [0., 1.]])

tex_path = os.path.join(os.getcwd(), 'tex_unblind/')
if not os.path.exists(tex_path):
  os.mkdir(tex_path)

for n in r_dict:
  f_tex = open(f'{tex_path}/R_ADS_A_ADS_{n}.tex', 'w+')
  for true_n in neutral:
    if n == 'pi0' and true_n == 'gamma':
      continue
    for b in ['pi', 'k']:
      b_str = bachelor_label(b)
      n_str = neutral_label(true_n)
      r_ads = r_dict[n][f'{true_n}_{b}']
      a_ads = a_dict[n][f'{true_n}_{b}']
      f_tex.write(
          f'$R^{{\\piK,{n_str} }}_{{ {b_str} }} = {r_ads.n:.4f} \\pm {r_ads.s:.4f}$ \\\\ \n'
      )
      f_tex.write(
          f'$A^{{\\piK,{n_str} }}_{{ {b_str} }} = {a_ads.n:.3f} \\pm {a_ads.s:.3f}$ \\\\ \n'
      )
