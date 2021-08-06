import pandas as pd
import numpy as np
import math, re, os, sys
from ROOT import TFile, RooFitResult
import argparse
import json
from useful_functions import return_label

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
                      '--result_dir',
                      type=str,
                      help='Directory where data fit result and Bs and combinatorial systematics are stored (if running systematics)',
                      required=True)
  parser.add_argument('-p',
                      '--pull_fname',
                      type=str,
                      help='Pull results from 2D toys',
                      required=True)
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
  args = parser.parse_args()
  result_dir = args.result_dir
  pull_fname = args.pull_fname
  neutral = args.neutral
  charge = args.charge

  tex_path = os.path.join(os.getcwd(), 'tex/')
  if not os.path.exists(tex_path):
    os.mkdir(tex_path)

  if neutral == 'pi0':
    box_str = '138_148_5220_5330'
  else:
    box_str = '60_105_125_170_5240_5320'
  result = f'{result_dir}/DataResult_{box_str}.root'

  # Observables we are interested have this stem (match with regex)
  # Include BR in order to calc gamma π0 FAV yield
  observables = [
      'N_tot_Bu2Dst0h', 'R_piK_Bu2Dst0h', 'R_CP_Bu2Dst0h',
      'R_Dst0KDst0pi_Bu2Dst0h', 'A_Bu2Dst0h', 'A_CP_Bu2Dst0h', 'BR_pi02gamma_eff'
  ]

  dict_result = {}
  # Extract data fit result (make not of box dimn for 2d toy pulls)
  # Extract value and fit error of each observable of interest
  if not os.path.isfile(result):
    sys.exit(f'{result} does not exist')
  data_file = TFile(result)
  data_result = data_file.Get('DataFitResult')
  if data_result == None:
    sys.exit(f'{data_file} does not contain DataFitResult')
  edm_fname = f'{tex_path}/EDM_{charge}_{neutral}.tex'
  with open(edm_fname, 'w') as f_edm:
    edm_val = data_result.edm()
    edm_str = f'{edm_val:.2e}'
    edm_num = edm_str[:-4]
    edm_pow = str(int(edm_str[-2:]))
    f_edm.write('${0} \\times 10^{{-{1} }}$'.format(edm_num, edm_pow))
  for obs in observables:
    for p in data_result.floatParsFinal():
      par_name = p.GetName()
      m0 = re.match(obs + '(_\S+)_[0-9]+', par_name)
      if m0:
        # Results labelled with different numbers
        value = p.getVal()
        if 'Blind' in par_name:
          value = 0
        end = m0.group(1).replace('_Blind', '')
        par_name = obs + end
        dict_result[par_name] = {
            'Value': value,
            'Statistical Error': p.getError()
        }
        # No systematics for yields
        if obs != 'N_tot_Bu2Dst0h' and obs != 'BR_pi02gamma_eff':
          dict_result[par_name]['Systematic Error'] = 0

  df_result = pd.DataFrame.from_dict(dict_result)
  print(df_result)

  # Save raw result to tex file
  raw_file = open(
      f'{tex_path}/Result_raw_{charge}_{neutral}.tex',
      'w')
  row_arr = []
  sorted_pars = sorted(dict_result.keys(), key=lambda x: x.lower())
  if 'BR_pi02gamma_eff_gamma' in sorted_pars:
    sorted_pars.remove('BR_pi02gamma_eff_gamma')
  for par in sorted_pars:
    val = df_result[par]['Value']
    stat = df_result[par]['Statistical Error']
    if par[0] == 'N':
      continue
    if val == 0:
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
  for par_name in sorted_pars:
    pull_result = pull_file.Get(f'Result_Pull_{par_name}')
    if pull_result == None:
      m = re.match('(\S+_Bu2Dst0h_D0(pi0|gamma))(_\S+|$)', par_name)
      if m:
        blind_par_name = m.group(1) + '_Blind' + m.group(3)
        pull_result = pull_file.Get(f'Result_Pull_{blind_par_name}')
        if pull_result == None:
          print(
              f'Could not extract  Result_Pull_{k} or Result_Pull_{blind_par_name} from {pull_fname}'
          )
          continue
      else:
        continue
    pull_pars = pull_result.floatParsFinal()
    pull_width = pull_pars[1].getVal()
    df_result[par]['Statistical Error'] = df_result[par]['Statistical Error'] * pull_width
    m0 = re.match('\S+_D0(pi0|gamma)(_\S+|$)', par_name)
    if m0:
      n_arr = [m0.group(1)]
    elif par_name == 'R_Dst0KDst0pi_Bu2Dst0h_kpi':
      if neutral == 'gamma':
        n_arr = ['pi0', 'gamma']
      else:
        n_arr = ['pi0']
    elif par_name == 'BR_pi02gamma_eff_gamma':
      n_arr = ['pi0']
    else:
      sys.exit(k + ' doesn\'t match neutral regex')
    for n in n_arr:
      if n not in pull_widths:
        pull_widths[n] = [pull_width]
      else:
        pull_widths[n].append(pull_width)

  # Systematic error on stat. correction is RMS of pull withs from 2D toys
  for n, pulls in pull_widths.items():
    np_pulls = np.array(pulls)
    rms = np.std(np_pulls)
    print(rms)
