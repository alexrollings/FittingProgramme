import pandas as pd
import root_numpy as r_np
import numpy as np
import math, re, os, sys
from ROOT import TFile, RooFitResult
import argparse
import json, csv
from useful_functions import return_label, return_group, return_final_group
from uncertainties import ufloat


def PrintFitStatus(df_syst, arr_syst_pars, arr_labels):
  par_name = arr_syst_pars[0]
  df_labels = df_syst[df_syst.par == par_name].drop(['par'], axis=1)
  for l in arr_labels:
    df_status = df_labels[df_labels.label == l]
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
  parser.add_argument(
      '-r',
      '--result_dir',
      type=str,
      help=
      'Directory where data fit result and Bs systematic are stored (if running systematics)',
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
  parser.add_argument(
      '-s',
      '--syst_dir',
      type=str,
      help=
      'Directory where json systematic is stored: comma separated if more than one (will store output in first directory passed: considered main)',
      required=False)
  parser.add_argument('--breakdown',
                      dest='breakdown',
                      action='store_true',
                      required=False)
  parser.add_argument('--remake',
                      dest='remake',
                      action='store_true',
                      required=False)
  args = parser.parse_args()
  result_dir = args.result_dir
  neutral = args.neutral
  charge = args.charge
  pull_fname = args.pull_fname
  syst_dir = args.syst_dir
  breakdown = args.breakdown
  remake = args.remake

  tex_path = os.path.join(os.getcwd(), 'tex_NEW/')
  if not os.path.exists(tex_path):
    os.mkdir(tex_path)

  if neutral == 'pi0':
    box_str = '138_148_5220_5330'
  else:
    box_str = '60_105_125_170_5240_5320'
  result = f'{result_dir}/DataResult_{box_str}.root'

  csv_result_fname = f'{tex_path}/result_{neutral}.csv'

  eval_systs = False
  if charge != 'total' and syst_dir != None:
    # Fir dir passed = main dir: store formatted csvs there
    syst_dirs = syst_dir.split(',')
    syst_dir = syst_dirs[0]
    if not os.path.exists(syst_dir):
      sys.exit(f'{syst_dir} does not exist')
    eval_systs = True
    csv_totals_fname = f'{syst_dir}/format/systematics_totals_{neutral}.csv'
    csv_groups_fname = f'{syst_dir}/format/systematics_groups_{neutral}.csv'
  fname_pars_blind = f'{tex_path}/blinded_pars_{neutral}.txt'

  if remake == True:

    # Observables we are interested have this stem (match with regex)
    # Include BR in order to calc gamma π0 FAV yield
    observables = [
        'N_tot_Bu2Dst0h', 'R_piK_Bu2Dst0h', 'R_CP_Bu2Dst0h',
        'R_Dst0KDst0pi_Bu2Dst0h', 'A_Bu2Dst0h', 'A_CP_Bu2Dst0h',
        'BR_pi02gamma_eff'
    ]

    blinded_pars = []
    dict_list_result = []
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
          blind = False
          if 'Blind' in par_name:
            blind = True
          end = m0.group(1).replace('_Blind', '')
          par_name = obs + end
          if blind == True:
            blinded_pars.append(par_name)
          # No systematics for yields
          if eval_systs == True and (obs != 'N_tot_Bu2Dst0h'
                                     and obs != 'BR_pi02gamma_eff'):
            syst_error = 0.
          else:
            syst_error = np.nan
          dict_list_result.append({
              'par': par_name,
              'val': value,
              'stat': p.getError(),
              'syst': syst_error
          })

    df_result = pd.json_normalize(dict_list_result)
    print(df_result)

    with open(fname_pars_blind, 'w') as f:
      f.write(','.join(blinded_pars))

    # Save raw result to tex file
    raw_file = open(f'{tex_path}/Result_raw_{charge}_{neutral}.tex', 'w')
    row_arr = []
    arr_pars = df_result['par'].unique().tolist()
    if 'BR_pi02gamma_eff_gamma' in arr_pars:
      arr_pars.remove('BR_pi02gamma_eff_gamma')
    for par_name in arr_pars:
      # To access value of DF - turn into 1x1 np array, then access first value
      val = df_result[(df_result.par == par_name)]['val'].values[0]
      stat = df_result[(df_result.par == par_name)]['stat'].values[0]
      if par_name[0] == 'N' or par_name[0] == 'B':
        continue
      if par_name in blinded_pars:
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
      row_arr.append(return_label(par_name)[1:-1] + results_str)

    for row in row_arr:
      raw_file.write(row)
    raw_file.close()

    # File where 2D pull results are stored
    pull_file = TFile(pull_fname)
    # Save pulls to dict labelled by neutral to calculate rms for syst on stat correction
    pull_widths = {}
    arr_syst_pars = [p for p in arr_pars if "N_tot" not in p]
    # Extract pull results for params and correct stat error with pull width
    for par_name in arr_pars:
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
      # at allows you to access given element, but needs row, column location therefore first find index (row) for given par_name
      par_idx = df_result.index[(
          df_result.par == par_name) == True].tolist()[0]
      df_result.at[par_idx, 'stat'] = df_result[
          (df_result.par == par_name)]['stat'].values[0] * pull_width
      if eval_systs == True:
        if par_name in arr_syst_pars:
          m0 = re.match('\S+_D0(pi0|gamma)(_\S+|$)', par_name)
          if m0:
            n = m0.group(1)
          else:
            print(f'{par_name} doesn\'t match neutral regex')
            continue
          if n not in pull_widths:
            pull_widths[n] = [pull_width]
          else:
            pull_widths[n].append(pull_width)

    # print(df_result)

    if eval_systs == True:
      dict_list_totals = []

      # Systematic error on stat. correction is RMS of pull withs from 2D toys
      for n, pulls in pull_widths.items():
        np_pulls = np.array(pulls)
        rms = np.std(np_pulls)
        # Add syst for parameter based on D*0 decay
        for par_name in arr_syst_pars:
          m = re.match(f'\S+_D0{n}(_\S+|$)', par_name)
          if m:
            stat = df_result[(df_result.par == par_name)]['stat'].values[0]
            # Multiply by stat error to get absolute systematic
            error = rms * stat
            dict_list_totals.append({
                'par':
                    par_name,
                'label':
                    'Statistical Error Correction',
                'std':
                    error,
                'group_label':
                    return_final_group('Statistical Error Correction'),
                'group_rms':
                    np.nan,
                # 'total_syst':
                #     np.nan
            })

      # Load in systematics from json
      csv_fname = f'{syst_dir}/format/systematics_{neutral}.csv'
      if os.path.exists(csv_fname):
        df_syst_1 = pd.read_csv(csv_fname)
        # Remove any Bu2Dst0hst observables
        patternKeep = "Bu2Dst0h_"
        filter = df_syst_1['par'].str.contains(patternKeep)
        df_syst_1 = df_syst_1[filter]
        # Remove blind string
        df_syst_1.par.replace({"_Blind": ""}, regex=True, inplace=True)
        # # Remove boxEffs_Bkg label
        # remove = "boxEffs_Bkg"
        # df_syst_1 = df_syst_1[~(df_syst_1.label == remove)]
      else:
        sys.exit(f'{csv_fname} does not exist')

      if len(syst_dirs) > 1:
        for path in syst_dirs:
          csv_fname_tmp = f'{path}/format/systematics_{neutral}.csv'
          if os.path.exists(csv_fname_tmp):
            df_syst_2 = pd.read_csv(csv_fname_tmp)
            # Remove any Bu2Dst0hst observables
            patternKeep = "Bu2Dst0h_"
            filter = df_syst_2['par'].str.contains(patternKeep)
            df_syst_2 = df_syst_2[filter]
            # Remove blind string
            df_syst_2.par.replace({"_Blind": ""}, regex=True, inplace=True)
            df_syst = pd.concat([df_syst_1, df_syst_2], ignore_index=True)
            # df_syst = df_syst_1.append(df_syst_2, ignore_index=True)
          else:
            sys.exit(f'{csv_fname_tmp} does not exist')
      else:
        df_syst = df_syst_1

      arr_labels = df_syst['label'].unique().tolist()
      # PrintFitStatus(df_syst, arr_syst_pars, arr_labels)
      df_syst = df_syst.query('cov > 2 & status == 0')
      df_syst.drop(['cov', 'status'], axis=1, inplace=True)

      # Old group comparison
      # group_labels = ['Pdfs', 'CPPars', 'Asyms', 'Effs', 'Rates']
      # dict_list_groups = []
      # Calculate individual systematic errors from std dev
      # Calculate total systematic error on an observable by taking the sum in quadrature of all std devs
      for par_name in arr_syst_pars:
        for label in arr_labels:
          df_tmp = df_syst[(df_syst.par == par_name)
                           & (df_syst.label == label)].drop(['par', 'label'],
                                                            axis=1)
          n_init = len(df_tmp)
          val = df_result[(df_result.par == par_name)]['val'].values[0]
          stat = df_result[(df_result.par == par_name)]['stat'].values[0]
          df_tmp.query(f'val > {val-3*stat} & val < {val+3*stat}',
                       inplace=True)
          n_final = len(df_tmp)
          if n_final == 0:
            print(
                f'WARNING: Z-score removed all events for {par_name}, {label}')
            continue
          elif n_init / n_final < 0.8:
            print(
                f'WARNING: Z-score removed {n_init/n_final*100}% of events for {par_name}, {label}'
            )
          std = df_tmp['val'].std()
          # Add columns for group labels and values
          if breakdown == True:
            # if label not in group_labels:
            dict_list_totals.append({
                'par': par_name,
                'label': label,
                'std': std,
                'group_label': return_final_group(label),
                'group_rms': np.nan,
                # 'total_syst': np.nan
            })
          else:
            dict_list_totals.append({
                'par': par_name,
                'label': label,
                'std': std,
                'group_label': return_final_group(label),
                'group_rms': np.nan,
                # 'total_syst': np.nan
            })
          #   # Save grouped systematic (varied together) to different dict and df for comparison
          #   dict_list_groups.append({
          #       'par': par_name,
          #       'label': label,
          #       'std': std,
          #   })

      # df_groups = pd.json_normalize(dict_list_groups)

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
            if par_name in arr_syst_pars:
              par_Bs = par.getVal()
              # Error is difference between central value of fit with Bs bkg change and default fit
              val = df_result[(df_result.par == par_name)]['val'].values[0]
              error = abs(par_Bs - val)
              # Take largest error to be symmetric error
              if par_name in dict_Bs_syst:
                if error > dict_Bs_syst[par_name]:
                  dict_Bs_syst[par_name] = error
              else:
                dict_Bs_syst[par_name] = error

      # print(dict_list_totals)
      if eval_Bs_syst == True:
        for par_name in arr_syst_pars:
          if par_name in dict_Bs_syst:
            dict_list_totals.append({
                'par': par_name,
                'label': 'Bs phase space',
                'std': dict_Bs_syst[par_name],
                'group_label': return_final_group('Bs phase space'),
                'group_total': np.nan,
                # 'total_syst': np.nan
            })

      # # Read in combinatorial systematic and add to dict_list_totals
      # dict_comb_syst = {}
      # eval_comb_syst = False
      # fname_comb = f'{result_dir}/SystResult_{box_str}_combinatorial.root'
      # if not os.path.isfile(fname_comb):
      #   print(f'{fname_comb} does not exist')
      # else:
      #   comb_file = TFile(fname_comb)
      #   comb_result = comb_file.Get('SystResult')
      #   if ReturnResultQuality(comb_result, fname_comb):
      #     eval_comb_syst = True
      #   if eval_comb_syst == True:
      #     for par in comb_result.floatParsFinal():
      #       par_name = par.GetName()[:-2]
      #       par_name = par_name.replace('_Blind', '')
      #       if par_name in arr_syst_pars:
      #         par_comb = par.getVal()
      #         val = df_result[(df_result.par == par_name)]['val'].values[0]
      #         # Error is difference between central value of combinatorial fit and that of default fit
      #         error = abs(par_comb - val)
      #         dict_comb_syst[par_name] = error
      #
      # if eval_comb_syst == True:
      #   for par_name in arr_syst_pars:
      #     if par_name in dict_comb_syst:
      #       dict_list_totals.append({
      #           'par': par_name,
      #           'label': 'Combinatorial',
      #           'std': dict_comb_syst[par_name],
      #           'group_label': return_final_group('Combinatorial'),
      #           'group_total': np.nan,
      #           # 'total_syst': np.nan
      #       })

      df_totals = pd.json_normalize(dict_list_totals)

      arr_group = df_totals['group_label'].unique().tolist()
      for par_name in arr_syst_pars:
        for g in arr_group:
          df_tmp = df_totals[(df_totals.par == par_name)
                             & (df_totals.group_label == g)]
          total = math.sqrt(df_tmp['std'].pow(2).sum())
          df_totals.loc[(df_totals.group_label == g)
                        & (df_totals.par == par_name), 'group_total'] = total

      for par_name in arr_syst_pars:
        df_tmp = df_totals[(df_totals.par == par_name)]
        total = math.sqrt(df_tmp['std'].pow(2).sum())
        df_result.loc[(df_result.par == par_name), 'syst'] = total

      df_result['syst/stat'] = np.where(df_result['syst'] != np.nan,
                                        df_result['syst'] / df_result['stat'],
                                        np.nan)

      df_totals.to_csv(csv_totals_fname, index=False)
      # if df_groups.empty == False:
      #   df_groups.to_csv(csv_groups_fname, index=False)
      #   tabulate_groups =True
      # else:
      #   tabulate_groups = False

    df_result.to_csv(csv_result_fname, index=False)

  ########## Tables ##########

  if remake == False:
    if os.path.exists(csv_result_fname):
      df_result = pd.read_csv(csv_result_fname)
    else:
      sys.exit(f'{csv_result_fname} does not exist')
  print(df_result)

  if eval_systs == True:
    if remake == False:
      if os.path.exists(csv_totals_fname):
        df_totals = pd.read_csv(csv_totals_fname)
      else:
        sys.exit(f'{csv_totals_fname} does not exist')

    arr_pars = df_result['par'].unique().tolist()
    arr_syst_pars = [
        p for p in arr_pars if ("N_tot" not in p) and ("BR" not in p)
    ]

    if breakdown == False:
      # CHECK THIS: COMBINE BsPDFs and Bs phase space into one group for ANA breakdown
      for par_name in arr_syst_pars:
        par_idx = df_totals.index[(
            (df_totals.par == par_name)
            & (df_totals.label == 'BsPdfs')) == True].tolist()[0]
        combined_syst = math.sqrt(df_totals[(df_totals.par == par_name) & (
            df_totals.label == 'BsPdfs')]['std'].values[0]**2 + df_totals[
                (df_totals.par == par_name)
                & (df_totals.label == 'Bs phase space')]['std'].values[0]**2)
        df_totals.at[par_idx, 'std'] = combined_syst
      df_totals = df_totals[~df_totals.label.str.contains('Bs phase space')]

    # First row of table is parameter names
    arr_labels = df_totals['label'].unique().tolist()
    row_arr = {'R': [], 'A': []}
    # Recorder number of ratios and asymmetries s.t. know when to line break in table
    n_params = {'R': 0, 'A': 0}
    max_labels = {}
    for par_name in arr_syst_pars:
      key = par_name[0]
      n_params[key] += 1
      if len(row_arr[key]) == 0:
        row_arr[key].append(' & ' + return_label(par_name))
      else:
        row_arr[key][0] += ' & ' + return_label(par_name)
      # Save maximum systematic label for each parameter: to be highlighted in table
      max_labels[par_name] = df_totals.iloc[df_totals[(
          df_totals.par == par_name)]['std'].idxmax()]['label']
    # New line and horizontal line after column titles
    row_arr['R'][0] += ' \\\\ \\hline\n'
    row_arr['A'][0] += ' \\\\ \\hline\n'

    # Then fill subsequent rows with systematic values for every label
    row_idx = {'R': 0, 'A': 0}
    for label in arr_labels:
      row_idx['R'] = row_idx['R'] + 1
      row_idx['A'] = row_idx['A'] + 1
      # Start new row with systematics label
      # Replace _ with \_ in LaTeX
      if breakdown == True:
        row_arr['R'].append(label.replace('_', '\\_'))
        row_arr['A'].append(label.replace('_', '\\_'))
      else:
        row_arr['R'].append(return_group(label))
        row_arr['A'].append(return_group(label))
      col_idx = {'R': 0, 'A': 0}
      for par_name in arr_syst_pars:
        key = par_name[0]
        col_idx[key] = col_idx[key] + 1
        err = df_totals[(df_totals.par == par_name)
                        & (df_totals.label == label)]['std'].values[0]
        stat = df_result[(df_result.par == par_name)]['stat'].values[0]
        frac = err / stat
        if max_labels[par_name] == label:
          err_str = ' & \\cellcolor{pink} '
        else:
          err_str = ' & '
        err_str += f'${frac:.4f}$'
        # Add formatted error for each parameter
        row_arr[key][row_idx[key]] += err_str
        # When reach last parameter of row: line break
        if col_idx[key] == n_params[key]:
          row_arr[key][row_idx[key]] += ' \\\\\n'

    # Last rows: total systematic and syst/stat fraction
    for key in row_arr:
      row_arr[key].append('\\hline\n')
      row_idx[key] = row_idx[key] + 1
      row_arr[key].append('$\\sigma(Syst.)$')
      row_idx[key] = row_idx[key] + 1
      row_arr[key].append('$\\frac{\\sigma(Syst.)}{\\sigma(Stat.)}$')
      row_idx[key] = row_idx[key] + 1

    col_idx = {'R': 0, 'A': 0}
    for par_name in arr_syst_pars:
      key = par_name[0]
      col_idx[key] = col_idx[key] + 1
      syst = df_result[(df_result.par == par_name)]['syst'].values[0]
      # To allign with Systematic row (above)
      row_arr[key][row_idx[key] - 1] += f' & ${syst:.4f}$'
      stat = df_result[(df_result.par == par_name)]['stat'].values[0]
      frac = syst / stat
      row_arr[key][row_idx[key]] += f' & ${frac:.4f}$'
      if col_idx[key] == n_params[key]:
        row_arr[key][row_idx[key] - 1] += ' \\\\ \\hline\n'
        row_arr[key][row_idx[key]] += ' \\\\ \\hline\\hline\n'

    # Write to tex file with LaTeX formatting
    if breakdown == True:
      tex_file = open(f'{tex_path}/Systematics_breakdown_{neutral}.tex', 'w')
      tex_file.write('\\documentclass[12pt, portrait]{article}\n')
      tex_file.write('\\usepackage[margin=0.1in]{geometry}\n')
      tex_file.write('\\usepackage{graphicx}\n')
      tex_file.write('\\usepackage{adjustbox}\n')
      tex_file.write('\\usepackage[table]{xcolor}\n')
      tex_file.write('\\usepackage{float}\n')
      tex_file.write('\\restylefloat{table}\n')
      tex_file.write('\\begin{document}\n')
    for key in row_arr:
      if n_params[key] > 0:
        if breakdown == False:
          tex_file = open(f'{tex_path}/Systematics_{key}_{neutral}.tex', 'w')
          if (neutral == 'pi0' and key == 'R') or (neutral == 'gamma'
                                                   and key == 'A'):
            tex_file.write('\\begin{tabularx}{\\textwidth}{X' + 'l' *
                              (n_params[key]) + '}\n')
          elif neutral == 'gamma' and key == 'R':
            tex_file.write('\\resizebox{.82\\paperheight}{!}{\n')
            tex_file.write('\\begin{tabular}{' + 'l' * (n_params[key] + 1) +
                              '}\n')
          else:
            tex_file.write('\\begin{tabular}{' + 'l' * (n_params[key] + 1) +
                              '}\n')
        else:
          tex_file.write('\\begin{table}[t]\n')
          tex_file.write('\\centering\n')
          tex_file.write('\\footnotesize\n')
          # tex_file.write(
          #     '\\begin{adjustbox}{totalheight=\\textheight-2\\baselineskip}\n')
          tex_file.write('\\begin{tabular}{' + 'l' * (n_params[key] + 2) +
                         '}\n')
        tex_file.write('\\hline\\hline\n')
        for row in row_arr[key]:
          tex_file.write(row)
        if breakdown == False:
          if (neutral == 'pi0' and key == 'R') or (neutral == 'gamma'
                                                   and key == 'A'):
            tex_file.write('\\end{tabularx}\n')
          elif neutral == 'gamma' and key == 'R':
            tex_file.write('\\end{tabular}\n')
            tex_file.write('}\n')
          else:
            tex_file.write('\\end{tabular}\n')
        else:
          tex_file.write('\\end{tabular}\n')
          # tex_file.write('\\end{adjustbox}\n')
          tex_file.write('\\end{table}\n')
    if breakdown == True:
      tex_file.write('\\end{document}')

    if breakdown == False:
      # Summary table
      arr_labels = df_totals['group_label'].unique().tolist()
      # First row of table is parameter names
      row_arr = []
      # Recorder number of ratios and asymmetries s.t. know when to line break in table
      n_params = 0

      for label in arr_labels:
        if len(row_arr) == 0:
          row_arr.append('Observable & {' + label + '}')
        else:
          row_arr[0] += ' & {' + label + '}'
      # New line and horizontal line after column titles
      row_arr[0] += ' & {Total} \\\\ \\hline\n'

      row_idx = 0
      for par_name in arr_syst_pars:
        n_params += 1
        row_arr.append(return_label(par_name))
        row_idx += 1
        stat = df_result[(df_result.par == par_name)]['stat'].values[0]
        for label in arr_labels:
          err = df_totals[(df_totals.par == par_name) & (
              df_totals.group_label == label)]['group_total'].values[0]
          frac = 100 * err / stat
          row_arr[row_idx] += f'& {frac:.2f}'
        syst = df_result[(df_result.par == par_name)]['syst'].values[0]
        total_frac = 100 * syst / stat
        row_arr[row_idx] += f'& {total_frac:.2f} \\\\\n'

      # Write to tex file with LaTeX formatting
      tex_file = open(f'{tex_path}/Systematics_summary_{neutral}.tex', 'w')
      tex_file.write('\\begin{tabular}{l *{' + str(len(arr_labels) + 1) +
                     '}{S[table-format=2.2]}}\n')
      tex_file.write('\\hline \\hline\n')
      for row in row_arr:
        tex_file.write(row)
      tex_file.write('\\hline \\hline\n')
      tex_file.write('\\end{tabular}\n')
      tex_file.close()

  if breakdown == False:
    with open(fname_pars_blind, 'r') as f:
      blinded_pars = ','.strip(f.read())
    # Save result to tex file
    result_file = open(f'{tex_path}/Result_{charge}_{neutral}.tex', 'w')
    row_arr = []
    for par_name in arr_pars:
      if par_name[0] == 'N' or par_name[0] == 'B':
        continue
      # To access value of DF - turn into 1x1 np array, then access first value
      val = df_result[(df_result.par == par_name)]['val'].values[0]
      stat = df_result[(df_result.par == par_name)]['stat'].values[0]
      if eval_systs == True:
        syst = df_result[(df_result.par == par_name)]['syst'].values[0]
        syst_str = f'& &\\pm {syst:.4f} \\\\\n'
      else:
        syst_str = '\\\\\n'
      if par_name in blinded_pars:
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
      row_arr.append(return_label(par_name)[1:-1] + results_str)

    for row in row_arr:
      result_file.write(row)
    result_file.close()

    # Make yields table

    yields_file = open(f'{tex_path}/Yields_{charge}_{neutral}.tex', 'w')
    yields_file.write('\\begin{tabular}{lll}\n')
    yields_file.write('Decay & \\D mode & Yield \\\\ \n')
    yields_file.write('\\hline\n')
    yield_dict = {}

    if neutral == 'pi0':
      true_neutral = ['pi0']
    else:
      true_neutral = ['gamma', 'pi0']

    for n in true_neutral:
      yield_dict[n] = {'pi': {}, 'k': {}}
      daughters = ['kpi', 'kk', 'pipi']
      b = 'pi'

      if n == 'pi0' and neutral == 'gamma':
        N_gamma_name = f'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kpi'
        N_gamma = ufloat(
            df_result[(df_result.par == N_gamma_name)]['val'].values[0],
            df_result[(df_result.par == N_gamma_name)]['stat'].values[0])
        BR_name = 'BR_pi02gamma_eff_gamma'
        BR = ufloat(df_result[(df_result.par == BR_name)]['val'].values[0],
                    df_result[(df_result.par == BR_name)]['stat'].values[0])
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
            'buPartialEff_Bu2Dst0pi_D0gamma',
            'buPartialEffErr_Bu2Dst0pi_D0gamma',
            'N_tot_Bu2Dst0pi_D0pi0_D02kpi_val',
            'N_tot_Bu2Dst0pi_D0pi0_D02kpi_err'
        ]
        tree = r_np.root2array(result, 'tree', branch_names)
        pull_file = TFile(pull_fname)
        pull_result = pull_file.Get(f'Result_Pull_{BR_name}')
        if pull_result == None:
          print(f'Could not extract  Result_Pull_{BR_name}')
          pull_width = 1
        else:
          pull_pars = pull_result.floatParsFinal()
          pull_width = pull_pars[1].getVal()
        N_pi0 = ufloat(tree[0][20], tree[0][21] * pull_width)
        dict_list_tmp = [{
            'par': 'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kpi',
            'val': N_pi0.n,
            'stat': N_pi0.s,
            'syst': np.nan
        }]
        df_tmp = pd.json_normalize(dict_list_tmp)
        df_result = df_result.append(df_tmp, ignore_index=True)

      for d in daughters:
        N_pi = f'N_tot_Bu2Dst0h_D0{n}_{neutral}_{b}_{d}'
        val = df_result[(df_result.par == N_pi)]['val'].values[0]
        stat = df_result[(df_result.par == N_pi)]['stat'].values[0]
        exp = math.sqrt(val)
        daughters_label = return_label(d)
        if d == 'kpi':
          decay_label = '\\multirow{4}{*}{' + return_label(
              f'Bu2Dst0{b}_D0{n}') + '}'
        else:
          decay_label = ''
        yield_dict[n][b][
            d] = f'{decay_label} & {daughters_label} & ${val:.0f} \\pm {stat:.0f}$ \\\\\n'

      b = 'k'
      R_K_pi_name = f'R_Dst0KDst0pi_Bu2Dst0h_D0{n}_kpi'
      R_K_pi = ufloat(
          df_result[(df_result.par == R_K_pi_name)]['val'].values[0],
          df_result[(df_result.par == R_K_pi_name)]['stat'].values[0])
      for d in daughters:
        N_pi_name = f'N_tot_Bu2Dst0h_D0{n}_{neutral}_pi_{d}'
        N_pi = ufloat(df_result[(df_result.par == N_pi_name)]['val'].values[0],
                      df_result[(df_result.par == N_pi_name)]['stat'].values[0])
        if d == 'kpi':
          decay_label = '\\multirow{4}{*}{' + return_label(
              f'Bu2Dst0{b}_D0{n}') + '}'
          R = R_K_pi
        else:
          decay_label = ''
          R_CP_name = f'R_CP_Bu2Dst0h_D0{n}'
          R_CP = ufloat(
              df_result[(df_result.par == R_CP_name)]['val'].values[0],
              df_result[(df_result.par == R_CP_name)]['stat'].values[0])
          R = R_K_pi * R_CP
        N_K = N_pi * R
        val = N_K.n
        stat = N_K.s
        exp = math.sqrt(val)
        if d == 'kpi':
          N_K_kpi = ufloat(val, stat)
        if par_name in blinded_pars and d != 'kpi':
          val_str = ''
        else:
          valStr = f'{val:.0f}'
        daughters_label = return_label(d)
        yield_dict[n][b][
            d] = f'{decay_label} & {daughters_label} & ${valStr} \\pm {stat:.0f}$ \\\\\n'

      bachelor = ['pi', 'k']
      for b in bachelor:
        if charge == 'total':
          R_piK_name = f'R_piK_Bu2Dst0h_D0{n}_{b}_total'
          R_piK = ufloat(
              df_result[(df_result.par == R_piK_name)]['val'].values[0],
              df_result[(df_result.par == R_piK_name)]['stat'].values[0])
        else:
          R_piK_plus_name = f'R_piK_Bu2Dst0h_D0{n}_{b}_plus'
          R_piK_plus = ufloat(
              df_result[(df_result.par == R_piK_plus_name)]['val'].values[0],
              df_result[(df_result.par == R_piK_plus_name)]['stat'].values[0])
          R_piK_minus_name = f'R_piK_Bu2Dst0h_D0{n}_{b}_minus'
          R_piK_minus = ufloat(
              df_result[(df_result.par == R_piK_minus_name)]['val'].values[0],
              df_result[(df_result.par == R_piK_minus_name)]['stat'].values[0])
          R_piK = (R_piK_plus + R_piK_minus) / 2
        if b == 'pi':
          N_kpi_name = f'N_tot_Bu2Dst0h_D0{n}_{neutral}_{b}_kpi'
          N_kpi = ufloat(
              df_result[(df_result.par == N_kpi_name)]['val'].values[0],
              df_result[(df_result.par == N_kpi_name)]['stat'].values[0])
        else:
          N_kpi = N_K_kpi
        N_pik = N_kpi * R_piK
        val = N_pik.n
        stat = N_pik.s
        exp = math.sqrt(val)
        if par_name in blinded_pars and d != 'kpi':
          val_str = ''
        else:
          valStr = f'{val:.0f}'
        daughters_label = return_label('pik')
        if n == 'pi0' and b == 'k':
          yield_dict[n][b][
              'pik'] = f' & {daughters_label} & ${valStr} \\pm {stat:.0f}$ \\\\\n'
        else:
          yield_dict[n][b][
              'pik'] = f' & {daughters_label} & ${valStr} \\pm {stat:.0f}$ \\\\ \\hline\n'

    for n in true_neutral:
      for b in ['pi', 'k']:
        for d in ['kpi', 'kk', 'pipi', 'pik']:
          yields_file.write(yield_dict[n][b][d])
    yields_file.write('\\end{tabular}\n')
