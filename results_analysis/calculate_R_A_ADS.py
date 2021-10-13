import numpy as np
import uncertainties as u
import json, csv, os, math
import pandas as pd
from useful_functions import neutral_label, bachelor_label

neutral = ['pi0', 'gamma']

path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/'

result_dict = {}

df_result = pd.DataFrame(columns=['neutral', 'par', 'val', 'stat', 'syst'])
df_syst = pd.DataFrame(columns=['neutral', 'par', 'corr'])
df_stat = pd.DataFrame(columns=['neutral', 'par', 'corr'])
for n in neutral:
  csv_result_fname = f'{path}/tex_unblind/result_split_{n}.csv'
  if os.path.exists(csv_result_fname):
    df_result_tmp = pd.read_csv(csv_result_fname)
  else:
    sys.exit(f'{csv_result_fname} does not exist')
  df_result_tmp.drop(['syst/stat'], axis=1, inplace=True)
  if n == 'pi0':
    df_result_tmp['par'].replace({'A_Bu2Dst0h_D0pi0_pi0_k_kpi' : 'A_Bu2Dst0h_D0pi0_k_kpi'}, inplace=True)
  else:
    df_result_tmp['par'].replace({'A_Bu2Dst0h_D0pi0_gamma_k_kpi' : 'A_Bu2Dst0h_D0pi0_k_kpi'}, inplace=True)
  df_result_tmp['neutral'] = n
  df_result = df_result.append(df_result_tmp)

  json_fname_syst = f'{path}/json/syst_{n}.json'
  if os.path.exists(json_fname_syst):
    with open(json_fname_syst, 'r') as syst_file:
      syst_dict = json.load(syst_file)
  else:
    sys.exit(f'{json_fname_syst} does not exist')
  df_syst_tmp = pd.json_normalize(syst_dict)
  df_syst_tmp = df_syst_tmp.melt(var_name='par', value_name='corr', ignore_index=True)
  if n == 'pi0':
    df_syst_tmp['par'].replace({'A_Bu2Dst0h_D0pi0_pi0_k_kpi' : 'A_Bu2Dst0h_D0pi0_k_kpi'}, inplace=True)
  else:
    df_syst_tmp['par'].replace({'A_Bu2Dst0h_D0pi0_gamma_k_kpi' : 'A_Bu2Dst0h_D0pi0_k_kpi'}, inplace=True)
  df_syst_tmp['neutral'] = n
  df_syst = df_syst.append(df_syst_tmp)

  json_fname_stat = f'{path}/json/stat_{n}.json'
  if os.path.exists(json_fname_stat):
    with open(json_fname_stat, 'r') as stat_file:
      stat_dict = json.load(stat_file)
  else:
    sys.exit(f'{json_fname_stat} does not exist')
  df_stat_tmp = pd.json_normalize(stat_dict)
  df_stat_tmp = df_stat_tmp.melt(var_name='par', value_name='corr', ignore_index=True)
  if n == 'pi0':
    df_stat_tmp['par'].replace({'A_Bu2Dst0h_D0pi0_pi0_k_kpi' : 'A_Bu2Dst0h_D0pi0_k_kpi'}, inplace=True)
  else:
    df_stat_tmp['par'].replace({'A_Bu2Dst0h_D0pi0_gamma_k_kpi' : 'A_Bu2Dst0h_D0pi0_k_kpi'}, inplace=True)
  df_stat_tmp['neutral'] = n
  df_stat = df_stat.append(df_stat_tmp)

json_fname_syst_pi0 = f'{path}/json/syst_pi0_results.json'
if os.path.exists(json_fname_syst_pi0):
  with open(json_fname_syst_pi0, 'r') as syst_pi0_file:
    syst_pi0_dict = json.load(syst_pi0_file)
else:
  sys.exit(f'{json_fname_syst_pi0} does not exist')
df_syst_pi0 = pd.json_normalize(syst_pi0_dict)
df_syst_pi0 = df_syst_pi0.melt(var_name='par', value_name='corr', ignore_index=True)

for b in ['pi', 'k']:
  minus_str = f'R_piK_Bu2Dst0h_D0gamma_{b}_minus'
  plus_str = f'R_piK_Bu2Dst0h_D0gamma_{b}_plus'
  vals = np.array([
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == minus_str)]['val'].values[0],
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == plus_str)]['val'].values[0]
  ])

  stat_err = np.array([
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == minus_str)]['stat'].values[0],
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == plus_str)]['stat'].values[0]
  ])
  stat_corr = np.array([[
      df_stat[(df_stat.neutral == 'gamma')
              & (df_stat.par == f'{minus_str},{minus_str}')]['corr'].values[0],
      df_stat[(df_stat.neutral == 'gamma')
              & (df_stat.par == f'{minus_str},{plus_str}')]['corr'].values[0]
  ],
                        [
                            df_stat[(df_stat.neutral == 'gamma')
                                    & (df_stat.par == f'{minus_str},{plus_str}'
                                       )]['corr'].values[0],
                            df_stat[(df_stat.neutral == 'gamma')
                                    & (df_stat.par == f'{plus_str},{plus_str}'
                                       )]['corr'].values[0]
                        ]])
  err_matrix = np.outer(stat_err, stat_err)
  stat_cov = np.multiply(err_matrix, stat_corr)
  #
  syst_err = np.array([
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == minus_str)]['syst'].values[0],
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == plus_str)]['syst'].values[0]
  ])
  syst_corr = np.array([[
      df_syst[(df_syst.neutral == 'gamma')
              & (df_syst.par == f'{minus_str},{minus_str}')]['corr'].values[0],
      df_syst[(df_syst.neutral == 'gamma')
              & (df_syst.par == f'{minus_str},{plus_str}')]['corr'].values[0]
  ],
                        [
                            df_syst[(df_syst.neutral == 'gamma')
                                    & (df_syst.par == f'{minus_str},{plus_str}'
                                       )]['corr'].values[0],
                            df_syst[(df_syst.neutral == 'gamma')
                                    & (df_syst.par == f'{plus_str},{plus_str}'
                                       )]['corr'].values[0]
                        ]])
  err_matrix = np.outer(syst_err, syst_err)
  syst_cov = np.multiply(err_matrix, syst_corr)

  total_cov = stat_cov + syst_cov

  (r_minus, r_plus) = np.asarray(u.correlated_values(vals, total_cov))
  r_ads = (r_minus + r_plus)/2.
  a_ads = (r_minus - r_plus)/(r_minus + r_plus)
  result_dict[f'R_gamma_{b}'] = r_ads
  result_dict[f'A_gamma_{b}'] = a_ads

for b in ['pi', 'k']:
  minus_str = f'R_piK_Bu2Dst0h_D0pi0_{b}_minus'
  plus_str = f'R_piK_Bu2Dst0h_D0pi0_{b}_plus'
  vals = np.array([
      df_result[(df_result.neutral == 'pi0')
                & (df_result.par == minus_str)]['val'].values[0],
      df_result[(df_result.neutral == 'pi0')
                & (df_result.par == plus_str)]['val'].values[0],
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == minus_str)]['val'].values[0],
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == plus_str)]['val'].values[0]
  ])

  stat_err = np.array([
      df_result[(df_result.neutral == 'pi0')
                & (df_result.par == minus_str)]['stat'].values[0],
      df_result[(df_result.neutral == 'pi0')
                & (df_result.par == plus_str)]['stat'].values[0],
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == minus_str)]['stat'].values[0],
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == plus_str)]['stat'].values[0]
  ])

  stat_corr = np.array(
      [[
          df_stat[(df_stat.neutral == 'pi0')
                  & (df_stat.par == f'{minus_str},{minus_str}')]
          ['corr'].values[0], df_stat[
              (df_stat.neutral == 'pi0')
              & (df_stat.par == f'{minus_str},{plus_str}')]['corr'].values[0],
          0, 0
      ],
       [
           df_stat[(df_stat.neutral == 'pi0')
                   & (df_stat.par == f'{minus_str},{plus_str}')]
           ['corr'].values[0], df_stat[
               (df_stat.neutral == 'pi0')
               & (df_stat.par == f'{plus_str},{plus_str}')]['corr'].values[0],
           0, 0
       ],
       [
           0, 0, df_stat[(df_stat.neutral == 'gamma')
                         & (df_stat.par == f'{minus_str},{minus_str}')]
           ['corr'].values[0], df_stat[
               (df_stat.neutral == 'gamma')
               & (df_stat.par == f'{minus_str},{plus_str}')]['corr'].values[0]
       ],
       [
           0, 0, df_stat[(df_stat.neutral == 'gamma')
                         & (df_stat.par == f'{minus_str},{plus_str}')]
           ['corr'].values[0], df_stat[
               (df_stat.neutral == 'gamma')
               & (df_stat.par == f'{plus_str},{plus_str}')]['corr'].values[0]
       ]])
  err_matrix = np.outer(stat_err, stat_err)
  stat_cov = np.multiply(err_matrix, stat_corr)

  syst_err = np.array([
      df_result[(df_result.neutral == 'pi0')
                & (df_result.par == minus_str)]['syst'].values[0],
      df_result[(df_result.neutral == 'pi0')
                & (df_result.par == plus_str)]['syst'].values[0],
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == minus_str)]['syst'].values[0],
      df_result[(df_result.neutral == 'gamma')
                & (df_result.par == plus_str)]['syst'].values[0]
  ])
  syst_corr = np.array(
      [[
          df_syst[(df_syst.neutral == 'pi0')
                  & (df_syst.par == f'{minus_str},{minus_str}')]
          ['corr'].values[0], df_syst[
              (df_syst.neutral == 'pi0')
              & (df_syst.par == f'{minus_str},{plus_str}')]['corr'].values[0],
          df_syst_pi0[(df_syst_pi0.par == f'{minus_str}_gamma,{minus_str}_pi0'
                       )]['corr'].values[0],
          df_syst_pi0[(df_syst_pi0.par == f'{minus_str}_gamma,{plus_str}_pi0'
                       )]['corr'].values[0]
      ],
       [
           df_syst[(df_syst.neutral == 'pi0')
                   & (df_syst.par == f'{minus_str},{plus_str}')]
           ['corr'].values[0], df_syst[
               (df_syst.neutral == 'pi0')
               & (df_syst.par == f'{plus_str},{plus_str}')]['corr'].values[0],
           df_syst_pi0[(df_syst_pi0.par == f'{minus_str}_gamma,{plus_str}_pi0'
                        )]['corr'].values[0],
           df_syst_pi0[(df_syst_pi0.par == f'{plus_str}_gamma,{plus_str}_pi0'
                        )]['corr'].values[0]
       ],
       [
           df_syst_pi0[(df_syst_pi0.par == f'{minus_str}_gamma,{minus_str}_pi0'
                        )]['corr'].values[0],
           df_syst_pi0[(df_syst_pi0.par == f'{minus_str}_gamma,{plus_str}_pi0'
                        )]['corr'].values[0],
           df_syst[(df_syst.neutral == 'gamma')
                   & (df_syst.par == f'{minus_str},{minus_str}')]
           ['corr'].values[0], df_syst[
               (df_syst.neutral == 'gamma')
               & (df_syst.par == f'{minus_str},{plus_str}')]['corr'].values[0]
       ],
       [
           df_syst_pi0[(df_syst_pi0.par == f'{minus_str}_gamma,{plus_str}_pi0'
                        )]['corr'].values[0],
           df_syst_pi0[(df_syst_pi0.par == f'{plus_str}_gamma,{plus_str}_pi0'
                        )]['corr'].values[0],
           df_syst[(df_syst.neutral == 'gamma')
                   & (df_syst.par == f'{minus_str},{plus_str}')]
           ['corr'].values[0], df_syst[
               (df_syst.neutral == 'gamma')
               & (df_syst.par == f'{plus_str},{plus_str}')]['corr'].values[0]
       ]])
  err_matrix = np.outer(syst_err, syst_err)
  syst_cov = np.multiply(err_matrix, syst_corr)

  total_cov = stat_cov + syst_cov

  (r_f_minus, r_f_plus, r_p_minus, r_p_plus) = np.asarray(u.correlated_values(vals, total_cov))
  r_f_ads = (r_f_minus + r_f_plus)/2.
  a_f_ads = (r_f_minus - r_f_plus)/(r_f_minus + r_f_plus)
  r_p_ads = (r_p_minus + r_p_plus)/2.
  a_p_ads = (r_p_minus - r_p_plus)/(r_p_minus + r_p_plus)
  r_ads = u.ufloat(
      (r_f_ads.n / r_f_ads.s**2 + r_p_ads.n / r_p_ads.s**2) /
      (1 / r_f_ads.s**2 + 1 / r_p_ads.s**2),
      math.sqrt((1 / r_f_ads.s**2 + 1 / r_p_ads.s**2)**(-1)))
  a_ads = u.ufloat(
      (a_f_ads.n / a_f_ads.s**2 + a_p_ads.n / a_p_ads.s**2) /
      (1 / a_f_ads.s**2 + 1 / a_p_ads.s**2),
      math.sqrt((1 / a_f_ads.s**2 + 1 / a_p_ads.s**2)**(-1)))
  result_dict[f'R_pi0_{b}'] = r_ads
  result_dict[f'A_pi0_{b}'] = a_ads

print(result_dict)

tex_path = os.path.join(os.getcwd(), 'tex_unblind/')
if not os.path.exists(tex_path):
  os.mkdir(tex_path)
f_tex = open(f'{tex_path}/R_ADS_A_ADS.tex', 'w+')
f_tex.write(
    f"R^{{\\piK,\\piz}}_{{K}} &= \\textcolor{{white}}{{-}}{result_dict['R_pi0_k'].n:.4f} &&\\pm {result_dict['R_pi0_k'].s:.4f} \\\\ \n"
)
f_tex.write(
    f"R^{{\\piK,\\g}}_{{K}} &= \\textcolor{{white}}{{-}}{result_dict['R_gamma_k'].n:.4f} &&\\pm {result_dict['R_gamma_k'].s:.4f} \\\\ \n"
)
f_tex.write(
    f"R^{{\\piK,\\piz}}_{{\\pi}} &= \\textcolor{{white}}{{-}}{result_dict['R_pi0_pi'].n:.4f} &&\\pm {result_dict['R_pi0_pi'].s:.4f} \\\\ \n"
)
f_tex.write(
    f"R^{{\\piK,\\g}}_{{\\pi}} &= \\textcolor{{white}}{{-}}{result_dict['R_gamma_pi'].n:.4f} &&\\pm {result_dict['R_gamma_pi'].s:.4f} \\\\ \n"
)
f_tex.write(
    f"A^{{\\piK,\\piz}}_{{K}} &= \\textcolor{{white}}{{-}}{result_dict['A_pi0_k'].n:.3f} &&\\pm {result_dict['A_pi0_k'].s:.3f} \\\\ \n"
)
f_tex.write(
    f"A^{{\\piK,\\g}}_{{K}} &= {result_dict['A_gamma_k'].n:.3f} &&\\pm {result_dict['A_gamma_k'].s:.3f} \\\\ \n"
)
f_tex.write(
    f"A^{{\\piK,\\piz}}_{{\\pi}} &= {result_dict['A_pi0_pi'].n:.3f} &&\\pm {result_dict['A_pi0_pi'].s:.3f} \\\\ \n"
)
f_tex.write(
    f"A^{{\\piK,\\g}}_{{\\pi}} &= \\textcolor{{white}}{{-}}{result_dict['A_gamma_pi'].n:.3f} &&\\pm {result_dict['A_gamma_pi'].s:.3f} \\\\ \n"
)
