import os, sys, argparse, json, re
from collections import OrderedDict

def convert_param_names(neutral, par_name, blind):
  if blind == True:
    blind_str = '_Blind'
  else:
    blind_str = ''
  if neutral == 'gamma':
    init_n = ['gamma', 'pi0']
  else:
    init_n = ['pi0']
  for n in init_n:
    if neutral == 'gamma' and n == 'pi0':
      final_n = 'partpi0'
    else:
      final_n = n
    if n == 'gamma':
      cp_str = 'M'
    else:
      cp_str = 'P'
    if par_name == f'R_CP_Bu2Dst0h_D0{n}{blind_str}':
      return f'R_CP{cp_str}_b2dstark_{final_n}_d2hh'
    elif par_name == f'R_piK_Bu2Dst0h_D0{n}{blind_str}_pi_minus':
      return f'Rminus_b2dstarpi_{final_n}_d2pik'
    elif par_name == f'R_piK_Bu2Dst0h_D0{n}{blind_str}_pi_plus':
      return f'Rplus_b2dstarpi_{final_n}_d2pik'
    elif par_name == f'R_piK_Bu2Dst0h_D0{n}{blind_str}_k_minus':
      return f'Rminus_b2dstark_{final_n}_d2pik'
    elif par_name == f'R_piK_Bu2Dst0h_D0{n}{blind_str}_k_plus':
      return f'Rplus_b2dstark_{final_n}_d2pik'
    elif par_name == f'A_Bu2Dst0h_D0{n}_{neutral}_k_kpi':
      return f'A_FAV_b2dstark_{final_n}_d2kpi'
    elif par_name == f'A_Bu2Dst0h_D0{n}_{neutral}_k_kpi':
      return f'A_FAV_b2dstark_{final_n}_d2kpi'
    elif par_name == f'A_CP_Bu2Dst0h_D0{n}{blind_str}_pi':
      return f'A_CP{cp_str}_b2dstarpi_{final_n}_d2hh'
    elif par_name == f'A_CP_Bu2Dst0h_D0{n}{blind_str}_k':
      return f'A_CP{cp_str}_b2dstark_{final_n}_d2hh'
  sys.exit(f'{par_name} has no match in convert_param_names')


if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral: pi0/gamma',
                      required=True)
  parser.add_argument('--blind',
                      dest='blind',
                      action='store_true',
                      required=False)
  args = parser.parse_args()
  neutral = args.neutral
  blind = args.blind

  path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/'

  json_fname_result = f'{path}json/result_{split}_{neutral}.json'
  if os.path.exists(json_fname_result):
    with open(json_fname_result, 'r') as json_file_result:
      result = json.load(json_file_result)

  if blind == True:
    blind_str = '_Blind'
  if neutral == 'pi0':
    init_n = ['pi0']
  else:
    init_n = ['gamma', 'pi0']
  ordered_params = []
  bachelor = ['k', 'pi']
  for b in bachelor:
    for n in init_n:
      ordered_params.append(f'A_CP_Bu2Dst0h_D0{n}{blind_str}_{b}')
    if b == 'k':
      for n in init_n:
        ordered_params.append(f'A_Bu2Dst0h_D0{n}_{neutral}_{b}_kpi')
      for n in init_n:
        ordered_params.append(f'R_CP_Bu2Dst0h_D0{n}{blind_str}')
    for n in init_n:
      ordered_params.append(f'R_piK_Bu2Dst0h_D0{n}{blind_str}_{b}_minus')
    for n in init_n:
      ordered_params.append(f'R_piK_Bu2Dst0h_D0{n}{blind_str}_{b}_plus')

  json_fname_stat = f'{path}json/stat_{neutral}.json'
  if os.path.exists(json_fname_stat):
    with open(json_fname_stat, 'r') as json_file_stat:
      stat = json.load(json_file_stat)

  json_fname_syst = f'{path}json/syst_{neutral}.json'
  if os.path.exists(json_fname_syst):
    with open(json_fname_syst, 'r') as json_file_syst:
      syst = json.load(json_file_syst)


  f_tex = open(f'{path}/gammadini/gammadini_{neutral}.tex', 'w+')
  f_tex.write('// -------- Load the central values of the measurements and their covariance matrix ----------\n')
  for k in ['Value', 'Statistical Error', 'Systematic Error']:
    for p in ordered_params:
      label = convert_param_names(neutral, p, blind)
      num = result[p][k]
      if k == 'Value':
        f_tex.write(f'observedCentralValues(Index[\"{label}\"])\t={num:.4f};\n')
      elif k == 'Statistical Error':
        f_tex.write(f'statErrorValues(Index[\"{label}\"])\t={num:.1};\n')
      elif k == 'Systematic Error':
        f_tex.write(f'systErrorValues(Index[\"{label}\"])\t={num:.1};\n')
    f_tex.write('\n')

  f_tex.write('\n')

  f_tex.write('const double statCorrelations[64] = {\n')
  for p1 in ordered_params:
    for p2 in ordered_params:
      k1 = f'{p1},{p2}'
      if k1 in stat:
        k = k1
      k2 = f'{p2},{p1}'
      if k2 in stat:
        k = k2
      f_tex.write(f'{stat[k]:.4f}')
      if p1 != ordered_params[-1] or p2 != ordered_params[-1]:
        f_tex.write(', ')
    f_tex.write('\n')
  f_tex.write('};\n')
  f_tex.write('TMatrixDSym statCorr(_nmeasurements,statCorrelations);\n')

  f_tex.write('\n')

  f_tex.write('const double systCorrelations[64] = {\n')
  for p1 in ordered_params:
    for p2 in ordered_params:
      k1 = f'{p1},{p2}'
      if k1 in syst:
        k = k1
      k2 = f'{p2},{p1}'
      if k2 in syst:
        k = k2
      f_tex.write(f'{syst[k]:.4f}')
      if p1 != ordered_params[-1] or p2 != ordered_params[-1]:
        f_tex.write(', ')
    f_tex.write('\n')
  f_tex.write('};\n')
  f_tex.write('TMatrixDSym systCorr(_nmeasurements,systCorrelations);\n')
