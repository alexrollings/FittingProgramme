import pandas as pd
import numpy as np
import math, re, os, sys
from ROOT import TFile, RooFitResult
import argparse
import json, csv
from useful_functions import return_label
from useful_functions import return_group_breakdown, return_final_group

def PrintFitStatus(df_syst, syst_pars, arr_labels):
  par_name = syst_pars[0]
  df_labels = df_syst[df_syst.par == par_name].drop(['par'], axis=1)
  for l in arr_labels:
    df_status = df_labels[df_labels.label==l]
    n_Total = len(df_status)
    n_unConverged = len(df_status.query('cov < 2'))
    n_FPD = len(df_status.query('cov == 2'))
    n_MINOS = len(df_status.query('cov > 2 & status != 0'))
    n_Converged = len(df_status.query('cov > 2 & status == 0'))
    print(
        f'{l}:\n\tTotal:\t\t{n_Total}\n\tConverged:\t{n_Converged/n_Total*100}%\n\tUnconverged:\t{n_unConverged/n_Total*100}%\n\tFPD:\t\t{n_FPD/n_Total*100}%\n\tMINOS Errors:\t{n_MINOS/n_Total*100}\n'
    )

def ReturnResultQuality(result, fname):
  if result == None:
    print(f'{fname} does not contain SystResult')
  covQual = result.covQual()
  fitStatus = result.status()
  if covQual < 2:
    print(f'{fname} SystResult unconverged')
    return False
  elif covQual < 3:
    print(f'{fname} SystResult FPD')
    return False
  elif fitStatus != 0:
    print(f'{fname} SystResult has MINOS errors')
    return False
  elif (covQual >= 3 and fitStatus == 0):
    return True

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-r',
                      '--result_dir',
                      type=str,
                      help='Directory where data fit result and Bs and combinatorial systematics are stored (if running systematics)',
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
  args = parser.parse_args()
  result_dir = args.result_dir
  neutral = args.neutral
  charge = args.charge
  pull_fname = args.pull_fname
  syst_dir = args.syst_dir

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
  if not ReturnResultQuality(data_result, result):
    sys.exit(f'{data_file} does not contain converged result')
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
          dict_result[par_name]['Systematic Error'] = np.nan

  df_result = pd.DataFrame.from_dict(dict_result)
  # print(df_result)

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

  eval_systs = False
  if charge != 'total' and syst_dir != None:
    if not os.path.exists(syst_dir):
      sys.exit(f'{syst_dir} does not exist')
    eval_systs = True

  if eval_systs == True:
    # Load in systematics from json
    csv_fname = f'{syst_dir}/format/systematics_{neutral}.csv'
    if os.path.exists(csv_fname):
      df_syst = pd.read_csv(csv_fname)
    else:
      sys.exit(f'{csv_fname} does not exist')

    arr_labels = df_syst['label'].unique()
    syst_pars = [p for p in sorted_pars if "N_tot" not in p]
    dict_list_totals = []
    # PrintFitStatus(df_syst, syst_pars, arr_labels)

    df_syst = df_syst.query('cov > 2 & status == 0')
    df_syst.drop(['cov', 'status'], axis=1, inplace=True)

    # Calculate individual systematic errors from std dev
    # Calculate total systematic error on an observable by taking the sum in quadrature of all std devs
    for par_name in syst_pars:
      for label in arr_labels:
        df_tmp = df_syst[(df_syst.par == par_name) & (df_syst.label == label)].drop(['par', 'label'], axis=1)
        n_init = len(df_tmp)
        central_value = df_result[par_name]['Value']
        stat_error = df_result[par_name]['Statistical Error']
        df_tmp.query(
            f'val > {central_value-3*stat_error} & val < {central_value+3*stat_error}',
            inplace=True)
        n_final = len(df_tmp)
        if n_final == 0:
          # print(f'WARNING: Z-score removed all events for {par_name}, {label}')
          continue
        # elif n_init/n_final < 0.8:
        #   print(f'WARNING: Z-score removed {n_init/n_final*100}% of events for {par_name}, {label}')
        std = df_tmp['val'].std()
        # Add columns for group and breakdown labels and values
        dict_list_totals.append({
            'par': par_name,
            'label': label,
            'std': std,
            'breakdown_label': return_group_breakdown(label),
            'breakdown_rms': np.nan,
            'group_label': return_final_group(label),
            'group_rms': np.nan,
            'total_syst': np.nan
        })

    # # Systematic error on stat. correction is RMS of pull withs from 2D toys
    # for n, pulls in pull_widths.items():
    #   np_pulls = np.array(pulls)
    #   rms = np.std(np_pulls)
    #   print(rms)

    # Read in Bs systematic and add to dict_list_totals
    dict_Bs_syst = {}
    eval_Bs_syst = False
    fracs = ['0.7', '0.9']
    for frac in fracs:
      fname_Bs = f'{result_dir}/SystResult_{box_str}_Bs2Dst0Kst0_{frac}.root'
      if not os.path.isfile(fname_Bs):
        print(f'{fname_Bs} does not exist')
        continue
      Bs_file = TFile(fname_Bs)
      Bs_result = Bs_file.Get('SystResult')
      if ReturnResultQuality(Bs_result, fname_Bs):
        eval_Bs_syst = True
      else:
        continue
      if eval_Bs_syst == True:
        for par in Bs_result.floatParsFinal():
          par_name = par.GetName()[:-2]
          par_name = par_name.replace('_Blind', '')
          if par_name in df_result:
            par_Bs = par.getVal()
            par_og = df_result[par_name]['Value']
            error = abs(par_Bs - par_og)
            if par_name in dict_Bs_syst:
              if error > dict_Bs_syst[par_name]:
                dict_Bs_syst[par_name] = error
            else:
              dict_Bs_syst[par_name] = error

    if eval_Bs_syst == True:
      for par_name in syst_pars:
        if par_name in dict_Bs_syst:
          dict_list_totals.append({
              'par': par_name,
              'label': 'Bs phase space',
              'std': dict_Bs_syst[par_name],
              'breakdown_label': return_group_breakdown('Bs phase space'),
              'breakdown_rms': np.nan,
              'group_label': return_final_group('Bs phase space'),
              'group_rms': np.nan,
              'total_syst': np.nan
          })

    # Read in combinatorial systematic and add to dict_list_totals
    dict_comb_syst = {}
    eval_comb_syst = False
    fname_comb = f'{result_dir}/SystResult_{box_str}_combinatorial.root'
    if not os.path.isfile(fname_comb):
      print(f'{fname_comb} does not exist')
    else:
      comb_file = TFile(fname_comb)
      comb_result = comb_file.Get('SystResult')
      if ReturnResultQuality(comb_result, fname_comb):
        eval_comb_syst = True
      if eval_comb_syst == True:
        for par in comb_result.floatParsFinal():
          par_name = par.GetName()[:-2]
          par_name = par_name.replace('_Blind', '')
          if par_name in df_result:
            par_comb = par.getVal()
            par_og = df_result[par_name]['Value']
            error = abs(par_comb - par_og)
            dict_comb_syst[par_name] = error

    if eval_comb_syst == True:
      for par_name in syst_pars:
        if par_name in dict_comb_syst:
          dict_list_totals.append({
              'par': par_name,
              'label': 'Combinatorial',
              'std': dict_comb_syst[par_name],
              'breakdown_label': return_group_breakdown('Combinatorial'),
              'breakdown_rms': np.nan,
              'group_label': return_final_group('Combinatorial'),
              'group_rms': np.nan,
              'total_syst': np.nan
          })

    df_totals = pd.json_normalize(dict_list_totals)

    arr_breakdown = df_totals['breakdown_label'].unique()
    for par_name in syst_pars:
      for b in arr_breakdown:
        df_tmp = df_totals[(df_totals.par == par_name) & (df_totals.breakdown_label == b)]
        n_categories = len(df_tmp)
        rms = math.sqrt(df_tmp['std'].pow(2).sum() / n_categories)
        df_totals.loc[(df_totals.breakdown_label == b)
                      & (df_totals.par == par_name), 'breakdown_rms'] = rms

    arr_group = df_totals['group_label'].unique()
    for par_name in syst_pars:
      for g in arr_group:
        df_tmp = df_totals[(df_totals.par == par_name) & (df_totals.group_label == g)]
        n_categories = len(df_tmp)
        rms = math.sqrt(df_tmp['std'].pow(2).sum() / n_categories)
        df_totals.loc[(df_totals.group_label == g)
                      & (df_totals.par == par_name), 'group_rms'] = rms

    for par_name in syst_pars:
      df_tmp = df_totals[(df_totals.par == par_name)]
      n_categories = len(df_tmp)
      rms = math.sqrt(df_tmp['std'].pow(2).sum() / n_categories)
      df_totals.loc[(df_totals.par == par_name), 'total_syst'] = rms

    print(df_totals)

