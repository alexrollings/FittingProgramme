import root_numpy as r_np
import numpy as np
import math, re, os, sys
from ROOT import TFile, RooFitResult
import argparse
import json, csv
from uncertainties import ufloat
import scipy.stats as stats
from useful_functions import return_label

def CalculateChi2(val1, err1, val2, err2):
  chi2 = (val1 - val2)**2 / (err1**2 + err2**2)
  return chi2

def CalculateSigma(val1, err1, val2, err2):
  sigma = (val1 - val2) / math.sqrt(err1**2 + err2**2)
  return abs(sigma)

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '-n',
      '--neutral',
      type=str,
      help=
      'Neutral',
      required=True)
  parser.add_argument(
      '-d',
      '--default_file',
      type=str,
      help=
      'Result of defalt data fit',
      required=True)
  parser.add_argument(
      '-m',
      '--muon_file',
      type=str,
      help=
      'Result of isMuon==0 data fit',
      required=True)
  args = parser.parse_args()

  neutral = args.neutral
  default_file = args.default_file
  muon_file = args.muon_file

  observables = [
      'R_piK_Bu2Dst0h_', 'R_CP_Bu2Dst0h_',
      'A_Bu2Dst0h_', 'A_CP_Bu2Dst0h_',
      # 'R_Dst0KDst0pi_Bu2Dst0h_'
  ]

  if not os.path.isfile(default_file):
    sys.exit(f'{default_file} does not exist')
  default_tf = TFile(default_file)
  default_result = default_tf.Get('DataFitResult')

  if not os.path.isfile(muon_file):
    sys.exit(f'{muon_file} does not exist')
  muon_tf = TFile(muon_file)
  muon_result = muon_tf.Get('DataFitResult')


  chi2_dict = {}
  sigma_dict = {}
  for obs in observables:
    for p in default_result.floatParsFinal():
      p_name = p.GetName()
      m0 = re.match(obs + '(\S+)_[0-9]+', p_name)
      if m0:
        default_val = p.getVal()
        default_err = p.getError()
        for mp in muon_result.floatParsFinal():
          mp_name = mp.GetName()
          if mp_name == p_name:
            muon_val = mp.getVal()
            muon_err = mp.getError()
        chi2_dict[p_name] = {
            'sigma':
                CalculateSigma(default_val, default_err, muon_val, muon_err),
            'chi2':
                CalculateChi2(default_val, default_err, muon_val, muon_err)
        }
        sigma_dict[p_name] = abs(default_val - muon_val) / muon_err

  n_pars = 0
  chi2_tot = 0
  sigma_tot = 0
  tex_file = open(f'isMuon_comparison/isMuon_table_{neutral}.tex', 'w')
  tex_file.write('\\begin{tabular}{cc}\n')
  tex_file.write('Observable & Agreement ($\\sigma$) \\\\ \n')
  tex_file.write('\\hline\n')
  for par, d in chi2_dict.items():
    chi2_tot += d['chi2']
    n_pars += 1
    s = sigma_dict[par]
    sigma_tot += s
    p_str = return_label(par[:-2])
    tex_file.write(f"{p_str} & {s:.2f} \\\\ \n")
    if "CP" in par and par[:-2] != "A_CP_Bu2Dst0h_D0gamma_pi":
      print(f"{par[:-2]}\t\t\t{sigma_dict[par]:.4f}")
    elif "Dst0KDst0pi" in par:
      print(f"{par[:-2]}\t{sigma_dict[par]:.4f}")
    else:
      print(f"{par[:-2]}\t\t{sigma_dict[par]:.4f}")
  # chi2_ndf = chi2_tot/n_pars
  # print(f'chi2/ndf = {chi2_ndf}')
  # p_value = stats.distributions.chi2.sf(chi2_ndf, 1)
  # print(f'p value = {p_value}')
  # sigma = stats.norm.ppf(1-p_value/2)
  # print(f'sigma = {sigma}')
  mean_sigma = sigma_tot/n_pars
  tex_file.write('\\hline\n')
  tex_file.write(f'Mean shift in $\\sigma$ & {mean_sigma:.2f} \\\\ \n')
  tex_file.write('\\end{tabular}\n')
  print(f'\nmean sigma = {mean_sigma:.4f}\n')
