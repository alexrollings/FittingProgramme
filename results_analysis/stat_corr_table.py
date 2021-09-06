import os, argparse, re, json
from ROOT import TFile, RooFitResult
from useful_functions import return_label

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-f',
                      '--fname',
                      type=str,
                      help='Result filename',
                      required=True)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral',
                      required=True)
  args = parser.parse_args()

  tex_path = os.path.join(os.getcwd(), 'tex_unblind/')
  if not os.path.exists(tex_path):
    os.mkdir(tex_path)

  neutral = args.neutral
  fname = args.fname

  observables = [
      'R_piK_Bu2Dst0h', 'R_CP_Bu2Dst0h',
      'A_Bu2Dst0h', 'A_CP_Bu2Dst0h'
  ]

  if not os.path.isfile(fname):
    sys.exit(f'{fname} does not exist')
  tf = TFile(fname)
  result = tf.Get("DataFitResult")
  all_pars = result.floatParsFinal()
  pars = []
  stat_dict = {}
  for idx in range(0, len(all_pars)):
    par_name = all_pars[idx].GetName()
    for obs in observables:
      m0 = re.match(obs + '(_[A-Za-z0-9]+)+', par_name)
      if m0:
        pars.append(all_pars[idx])
  f_tex = open(f'{tex_path}/stat_correlations_{neutral}.tex', 'w+')
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
  for idx in range(0, len(pars)):
    f_tex.write(' & ' + return_label(pars[idx].GetName()[:-2]))
  f_tex.write(' \\\\ \hline \n')
  for idx1 in range(0, len(pars)):
    p1 = pars[idx1]
    f_tex.write(return_label(p1.GetName()[:-2]))
    second_half = False
    for idx2 in range(0, len(pars)):
      p2 = pars[idx2]
      if p2.GetName() == p1.GetName():
        second_half = True
      if second_half == True:
        corr = result.correlation(p1, p2)
        # if corr > 0.9 or corr < -0.9:
        #   f_tex.write(' & \\colorbox{pink}{$%.3f$} ' % corr)
        # else:
        f_tex.write(' & $%.2f$ ' % corr)
        stat_dict[p1.GetName()[:-2] + ',' + p2.GetName()[:-2]] = corr
      else:
        f_tex.write(' &  ')
    f_tex.write('\\\\ \n')
  f_tex.write('\t\\end{tabular}\n')
  # f_tex.write('}\n')
  # f_tex.write('\\end{table}\n')
  # f_tex.write('\\end{document}\n')

  json_fname_stat = f'json/stat_{neutral}.json'
  with open(json_fname_stat, 'w') as json_file_stat:
    json.dump(stat_dict, json_file_stat)
