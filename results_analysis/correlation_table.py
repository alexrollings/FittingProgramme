import os, argparse
from ROOT import TFile, RooFitResult

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-p',
                      '--path',
                      type=str,
                      help='Directory where result is stored',
                      required=True)
  parser.add_argument('-f',
                      '--f_name',
                      type=str,
                      help='Result filename (if non standard)',
                      required=False)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral',
                      required=True)
  args = parser.parse_args()

  path = args.path
  neutral = args.neutral
  f_name = args.f_name

  if f_name is None:
    if neutral == 'pi0':
      f_input = path + '/DataResult_138_148_5220_5330.root'
    else:
      f_input = path + '/DataResult_60_105_125_170_5240_5320.root'
  else:
    f_input = path + '/' + f_name

  tf = TFile(f_input)
  result = tf.Get("DataFitResult")
  pars = result.floatParsFinal()
  f_tex = open(f'{path}/stat_correlations_{neutral}.tex', 'w+')
  f_tex.write('\\documentclass[12pt, landscape]{article}\n')
  f_tex.write('\\usepackage[margin=0.1in]{geometry}\n')
  f_tex.write('\\usepackage{mathtools}\n')
  f_tex.write('\\usepackage{float}\n')
  f_tex.write('\\usepackage{xcolor}\n')
  f_tex.write('\\restylefloat{table}\n')
  f_tex.write('\\begin{document}\n')
  f_tex.write('\\begin{table}[t]\n')
  f_tex.write('\t\\centering\n')
  f_tex.write('\t\\footnotesize\n')
  f_tex.write('\\resizebox{\\textwidth}{!}{%\n')
  format_str = 'c|' + 'c' * len(pars)
  f_tex.write('\t\\begin{tabular}{' + format_str + '}\n')
  f_tex.write('\t\t')
  for idx in range(0, len(pars)):
    f_tex.write(' & ' + pars[idx].GetName()[:-2].replace(
        '_' + neutral, '').replace('_', '\\_'))
  f_tex.write(' \\\\ \hline \n')
  for idx1 in range(0, len(pars)):
    p1 = pars[idx1]
    f_tex.write(p1.GetName()[:-2].replace('_' + neutral,
                                          '').replace('_', '\\_'))
    for idx2 in range(0, len(pars)):
      p2 = pars[idx2]
      corr = result.correlation(p1, p2)
      if corr > 0.9 or corr < -0.9:
        f_tex.write(' & \\colorbox{pink}{$%.3f$} ' % corr)
      else:
        f_tex.write(' & $%.3f$ ' % corr)
    f_tex.write('\\\\ \n')
  f_tex.write('\t\\end{tabular}\n')
  f_tex.write('}\n')
  f_tex.write('\\end{table}\n')
  f_tex.write('\\end{document}\n')
