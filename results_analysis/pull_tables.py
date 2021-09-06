import math, re, os, sys
from ROOT import TFile, RooFitResult
import argparse
from uncertainties import ufloat
from useful_functions import return_label

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '-p',
      '--pull_fname',
      type=str,
      help=
      'Pull result file',
      required=True)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral: pi0/gamma',
                      required=True)
  parser.add_argument('-g',
                      '--gen',
                      type=str,
                      help='Generated: 2D/D1D',
                      required=True)
  parser.add_argument('-c',
                      '--charge',
                      type=str,
                      help='Charge: split/total',
                      required=True)
  args = parser.parse_args()
  pull_fname = args.pull_fname
  neutral = args.neutral
  charge = args.charge
  gen = args.gen

  # Observables we are interested have this stem (match with regex)
  observables = [
      'R_piK_Bu2Dst0h', 'R_CP_Bu2Dst0h',
      'R_Dst0KDst0pi_Bu2Dst0h', 'A_Bu2Dst0h', 'A_CP_Bu2Dst0h'
  ]
  # if gen == '2D':
  #   observables.append('N_tot_Bu2Dst0h')

  pull_file = TFile(pull_fname)
  pull_dict = {}

  keys = pull_file.GetListOfKeys()
  for k in keys:
    result_name = k.GetName()
    for obs in observables:
      m = re.match('Result_Pull_(' + obs + '(_[A-Za-z0-9]+)+)', result_name)
      if m:
        result = pull_file.Get(result_name)
        if result == None:
          print(f'Could not extract Result_Pull_{k} from {fname}')
        else:
          pars = result.floatParsFinal()
          mean = ufloat(pars[0].getVal(), pars[0].getError())
          sigma = ufloat(pars[1].getVal(), pars[1].getError())
          pull_dict[m.group(1)] = { 'mean' : mean, 'sigma' : sigma }

  fname = f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex_NEW/pulls_{gen}_{neutral}_{charge}.tex'
  with open(fname, 'w') as f:
    # f.write('\\documentclass[12pt, portrait]{article}\n')
    # f.write('\\usepackage[margin=0.1in]{geometry}\n')
    # f.write('\\usepackage{mathtools}\n')
    # f.write('\\usepackage{float}\n')
    # f.write('\\restylefloat{table}\n')
    # f.write('\\begin{document}\n')
    # f.write('\\begin{table}[t]\n')
    # f.write('\t\\centering\n')
    if gen == 'D1D':
      f.write('\\begin{tabular}{lcc} \n')
      f.write('Observable & Pull $\\mu$ & Pull $\\sigma$ \\\\ \\hline \n')
    else:
      f.write('\\begin{tabular}{lc} \n')
      f.write('Observable & Pull $\\sigma$ \\\\ \\hline \n')
    for k, v in pull_dict.items():
      par = return_label(k)
      sigma = pull_dict[k]['sigma']
      mean = pull_dict[k]['mean']
      if mean.n > 0:
        extra = '\\textcolor{white}{-}'
      else:
        extra = ''
      if gen == 'D1D':
        f.write(f'{par} & ${extra}{mean.n:.2f} \\pm {mean.s:.2f}$ & ${sigma.n:.2f} \\pm {sigma.s:.2f}$ \\\\ \n')
      else:
        f.write(f'{par} & ${sigma.n:.2f} \\pm {sigma.s:.2f}$ \\\\ \n')
    f.write('\\end{tabular} \n')
    # f.write('\\end{table}\n')
    # f.write('\\end{document}\n')



