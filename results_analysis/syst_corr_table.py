import os, argparse, re, json
import numpy as np
from ROOT import TFile, RooFitResult
from useful_functions import return_label
from scipy.stats.stats import pearsonr

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
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
  args = parser.parse_args()

  tex_path = os.path.join(os.getcwd(), 'tex/')
  if not os.path.exists(tex_path):
    os.mkdir(tex_path)

  neutral = args.neutral
  syst_dir = args.syst_dir

  json_fname_format = f'{syst_dir}/systematics_{neutral}_format.json'
  if os.path.exists(json_fname_format):
    with open(json_fname_format, 'r') as json_file_format:
      total_syst_dict = json.load(json_file_format)
  else:
    sys.exit(f'Run analyse_result.py first: {json_fname_format} does not exist')

  par_dict = {}
  pars = []
  syst_dict = {}
  for par, syst_arr in total_syst_dict.items():
    par_dict[par] = []
    pars.append(par)
    for syst_label, arr in syst_arr.items():
      arr2d = np.array(arr)
      np_arr = np.asarray(arr2d[0:, 0], dtype=np.float32)
      par_dict[par] = par_dict[par] + np_arr.tolist()

  f_tex = open(f'{tex_path}/syst_correlations_{neutral}.tex', 'w+')
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
  for p in pars:
    f_tex.write(' & ' + return_label(p))
  f_tex.write(' \\\\ \hline \n')
  for p1 in pars:
    f_tex.write(return_label(p1))
    second_half = False
    for p2 in pars:
      if p2 == p1:
        second_half = True
      if second_half == True:
        if p2 == p1:
          corr = 1.0
        else:
          corr = pearsonr(par_dict[p1],par_dict[p2])[0]
        f_tex.write(' & $%.2f$ ' % corr)
        print(p1 + ' vs.' + p2 + ':\t' + str(corr))
        syst_dict[p1 + ',' + p2] = corr
      else:
        f_tex.write(' &  ')
    f_tex.write('\\\\ \n')
  f_tex.write('\t\\end{tabular}\n')
  # f_tex.write('}\n')
  # f_tex.write('\\end{table}\n')
  # f_tex.write('\\end{document}\n')

  json_fname_syst = f'json/syst_{neutral}.json'
  with open(json_fname_syst, 'w') as json_file_syst:
    json.dump(syst_dict, json_file_syst)
