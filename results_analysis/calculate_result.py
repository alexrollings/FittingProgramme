import pandas as pd
import math, re, os, sys
from ROOT import TFile, RooFitResult
import argparse
import json

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
        end = m0.group(1).replace('_Blind', '')
        par_name = obs + end
        value = p.getVal()
        dict_result[par_name] = {
            'Value': value,
            'Statistical Error': p.getError()
        }
        # No systematics for yields
        if obs != 'N_tot_Bu2Dst0h' and obs != 'BR_pi02gamma_eff':
          dict_result[par_name]['Systematic Error'] = 0

  df_result = pd.DataFrame.from_dict(dict_result, orient='index')
  print(df_result)


