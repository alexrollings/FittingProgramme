import glob, os, sys
import pandas as pd
import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt
from matplotlib import rc
import random
import math
import json
from useful_functions import return_label
from uncertainties import ufloat
import matplotlib
matplotlib.use('Agg')
from scipy.stats import mode

rc('font',**{'family': 'serif','serif': ['Roman']})
rc('text', usetex=True)

def WeightedAverage(uf_arr):
  sum_w = 0
  tot = 0
  for uf in uf_arr:
    w = 1 / (uf.s**2)
    sum_w += w
    tot += uf.n * w
  av = tot / sum_w
  err = 1 / math.sqrt(sum_w)
  return [av, err]

def CalculateChi2(FR_val, FR_err, PR_val, PR_err):
  chi2 = (FR_val - PR_val)**2 / (FR_err**2 + PR_err**2)
  return chi2

def CalculateSigma(FR_val, FR_err, PR_val, PR_err):
  sigma = (FR_val - PR_val) / math.sqrt(FR_err**2 + PR_err**2)
  return abs(sigma)

if __name__ == '__main__':
  # Fit results saved in json
  path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/'

  csv_fname_result_pi0 = f'{path}tex_unblind/result_split_pi0.csv'
  if os.path.exists(csv_fname_result_pi0):
    result_pi0 = pd.read_csv(csv_fname_result_pi0)

  csv_fname_result_gamma = f'{path}tex_unblind/result_split_gamma.csv'
  if os.path.exists(csv_fname_result_gamma):
    result_gamma = pd.read_csv(csv_fname_result_gamma)

# LHCb combination
  phi3_val_err = ufloat(math.radians(65.4),math.radians(4))
  phi3 = np.random.normal(phi3_val_err.n, phi3_val_err.s, 10000)

  # No assumptions in D*π mode
  # B- -> D*0 π-
  rB_Dpi = np.random.uniform(0.0, 0.02, 10000)
  # rB_Dpi = np.random.uniform(0.0, 0.01, 10000)
  dB_Dpi = np.random.uniform(math.radians(0.0), math.radians(180.0), 10000)
  # dB_Dpi = np.random.uniform(math.radians(0.0), math.radians(360.0), 10000)

  # B factory ADS/GLW
  rB_DK = np.random.normal(0.106, 0.028, 10000)
  dB_DK = np.random.normal(math.radians(294), math.radians(26), 10000)

  # FAV: D0 -> K-π+
  rD_val = np.sqrt(0.00344)
  rD_err = rD_val * 2 * (2e-5/0.00344)
  rD_val_err = ufloat(rD_val,rD_err)
  rD = np.random.normal(rD_val_err.n, rD_val_err.s, 10000)
  # rD = np.sqrt(0.00344)

  dD_av_err = (8.6 + 10.2)*0.5
  dD_val_err = ufloat(math.radians(192.1),math.radians(dD_av_err))
  dD = np.random.normal(dD_val_err.n, dD_val_err.s, 10000)
  # dD = math.radians(192.1)

  #Calculate observables
  #Rates
  pi0_DK_hh_plus = 1 + rB_DK**2 + 2 * rB_DK * np.cos(dB_DK + phi3)
  pi0_DK_hh_minus = 1 + rB_DK**2 + 2 * rB_DK * np.cos(dB_DK - phi3)
  gamma_DK_hh_plus = 1 + rB_DK**2 - 2 * rB_DK * np.cos(dB_DK + phi3)
  gamma_DK_hh_minus = 1 + rB_DK**2 - 2 * rB_DK * np.cos(dB_DK - phi3)

  pi0_Dpi_hh_plus = 1 + rB_Dpi**2 + 2 * rB_Dpi * np.cos(dB_Dpi + phi3)
  pi0_Dpi_hh_minus = 1 + rB_Dpi**2 + 2 * rB_Dpi * np.cos(dB_Dpi - phi3)
  gamma_Dpi_hh_plus = 1 + rB_Dpi**2 - 2 * rB_Dpi * np.cos(dB_Dpi + phi3)
  gamma_Dpi_hh_minus = 1 + rB_Dpi**2 - 2 * rB_Dpi * np.cos(dB_Dpi - phi3)

  pi0_DK_kpi_plus = 1 + rD**2 * rB_DK**2 + 2 * rD * rB_DK * np.cos(dB_DK - dD + phi3)
  pi0_DK_kpi_minus = 1 + rD**2 * rB_DK**2 + 2 * rD * rB_DK * np.cos(dB_DK - dD - phi3)
  gamma_DK_kpi_plus = 1 + rD**2 * rB_DK**2 - 2 * rD * rB_DK * np.cos(dB_DK - dD + phi3)
  gamma_DK_kpi_minus = 1 + rD**2 * rB_DK**2 - 2 * rD * rB_DK * np.cos(dB_DK - dD - phi3)

  pi0_Dpi_kpi_plus = 1 + rD**2 * rB_Dpi**2 + 2 * rD * rB_Dpi * np.cos(dB_Dpi - dD + phi3)
  pi0_Dpi_kpi_minus = 1 + rD**2 * rB_Dpi**2 + 2 * rD * rB_Dpi * np.cos(dB_Dpi - dD - phi3)
  gamma_Dpi_kpi_plus = 1 + rD**2 * rB_Dpi**2 - 2 * rD * rB_Dpi * np.cos(dB_Dpi - dD + phi3)
  gamma_Dpi_kpi_minus = 1 + rD**2 * rB_Dpi**2 - 2 * rD * rB_Dpi * np.cos(dB_Dpi - dD - phi3)

  pi0_DK_pik_plus = rB_DK**2 + rD**2 + 2 * rB_DK * rD * np.cos(dB_DK + dD + phi3)
  pi0_DK_pik_minus = rB_DK**2 + rD**2 + 2 * rB_DK * rD * np.cos(dB_DK + dD - phi3)
  gamma_DK_pik_plus = rB_DK**2 + rD**2 - 2 * rB_DK * rD * np.cos(dB_DK + dD + phi3)
  gamma_DK_pik_minus = rB_DK**2 + rD**2 - 2 * rB_DK * rD * np.cos(dB_DK + dD - phi3)

  pi0_Dpi_pik_plus = rB_Dpi**2 + rD**2 + 2 * rB_Dpi * rD * np.cos(dB_Dpi + dD + phi3)
  pi0_Dpi_pik_minus = rB_Dpi**2 + rD**2 + 2 * rB_Dpi * rD * np.cos(dB_Dpi + dD - phi3)
  gamma_Dpi_pik_plus = rB_Dpi**2 + rD**2 - 2 * rB_Dpi * rD * np.cos(dB_Dpi + dD + phi3)
  gamma_Dpi_pik_minus = rB_Dpi**2 + rD**2 - 2 * rB_Dpi * rD * np.cos(dB_Dpi + dD - phi3)

  R_pi0_DK_pik_minus = pi0_DK_pik_minus / pi0_DK_kpi_minus
  R_pi0_DK_pik_plus = pi0_DK_pik_plus / pi0_DK_kpi_plus
  R_gamma_DK_pik_minus = gamma_DK_pik_minus / gamma_DK_kpi_minus
  R_gamma_DK_pik_plus = gamma_DK_pik_plus / gamma_DK_kpi_plus

  R_pi0_Dpi_pik_minus = pi0_Dpi_pik_minus / pi0_Dpi_kpi_minus
  R_pi0_Dpi_pik_plus = pi0_Dpi_pik_plus / pi0_Dpi_kpi_plus
  R_gamma_Dpi_pik_minus = gamma_Dpi_pik_minus / gamma_Dpi_kpi_minus
  R_gamma_Dpi_pik_plus = gamma_Dpi_pik_plus / gamma_Dpi_kpi_plus

  #Observables
  exp = {}
  exp['A_Bu2Dst0h_D0pi0_k_kpi'] = ((pi0_DK_kpi_minus - pi0_DK_kpi_plus) /
                                    (pi0_DK_kpi_minus + pi0_DK_kpi_plus))
  exp['A_Bu2Dst0h_D0gamma_k_kpi'] = ((gamma_DK_kpi_minus - gamma_DK_kpi_plus) /
                                    (gamma_DK_kpi_minus + gamma_DK_kpi_plus))
  exp['R_CP_Bu2Dst0h_D0pi0'] = ((pi0_DK_hh_minus + pi0_DK_hh_plus) /
                                    (pi0_DK_kpi_minus + pi0_DK_kpi_plus))
  exp['A_CP_Bu2Dst0h_D0pi0_k'] = ((pi0_DK_hh_minus - pi0_DK_hh_plus) /
                                    (pi0_DK_kpi_minus + pi0_DK_kpi_plus))
  exp['A_CP_Bu2Dst0h_D0pi0_pi'] = ((pi0_Dpi_hh_minus - pi0_Dpi_hh_plus) /
                                    (pi0_Dpi_kpi_minus + pi0_Dpi_kpi_plus))
  exp['R_CP_Bu2Dst0h_D0gamma'] = ((gamma_DK_hh_minus + gamma_DK_hh_plus) /
                                    (gamma_DK_kpi_minus + gamma_DK_kpi_plus))
  exp['A_CP_Bu2Dst0h_D0gamma_k'] = ((gamma_DK_hh_minus - gamma_DK_hh_plus) /
                                    (gamma_DK_kpi_minus + gamma_DK_kpi_plus))
  exp['A_CP_Bu2Dst0h_D0gamma_pi'] = ((gamma_Dpi_hh_minus - gamma_Dpi_hh_plus) /
                                    (gamma_Dpi_kpi_minus + gamma_Dpi_kpi_plus))
  exp['R_piK_Bu2Dst0h_D0pi0_k_minus'] = R_pi0_DK_pik_minus
  exp['R_piK_Bu2Dst0h_D0pi0_k_plus'] = R_pi0_DK_pik_plus
  exp['R_piK_Bu2Dst0h_D0gamma_k_minus'] = R_gamma_DK_pik_minus
  exp['R_piK_Bu2Dst0h_D0gamma_k_plus'] = R_gamma_DK_pik_plus
  exp['R_piK_Bu2Dst0h_D0pi0_pi_minus'] = R_pi0_Dpi_pik_minus
  exp['R_piK_Bu2Dst0h_D0pi0_pi_plus'] = R_pi0_Dpi_pik_plus
  exp['R_piK_Bu2Dst0h_D0gamma_pi_minus'] = R_gamma_Dpi_pik_minus
  exp['R_piK_Bu2Dst0h_D0gamma_pi_plus'] = R_gamma_Dpi_pik_plus

  fig = plt.hist(exp['R_CP_Bu2Dst0h_D0pi0'], 100, density=True)
  plt.savefig('figs/R_CP_pi0.pdf')
  plt.clf()
  fig = plt.hist(exp['R_CP_Bu2Dst0h_D0gamma'], 100, density=True)
  plt.savefig('figs/R_CP_gamma.pdf')
  plt.clf()
  fig = plt.hist(exp['A_CP_Bu2Dst0h_D0pi0_k'], 100, density=True)
  plt.savefig('figs/A_CP_pi0_k.pdf')
  plt.clf()
  fig = plt.hist(exp['A_CP_Bu2Dst0h_D0gamma_k'], 100, density=True)
  plt.savefig('figs/A_CP_gamma_k.pdf')
  plt.clf()
  fig = plt.hist(exp['A_CP_Bu2Dst0h_D0pi0_pi'], 100, density=True)
  plt.savefig('figs/A_CP_pi0_pi.pdf')
  plt.clf()
  fig = plt.hist(exp['A_CP_Bu2Dst0h_D0gamma_pi'], 100, density=True)
  plt.savefig('figs/A_CP_gamma_pi.pdf')
  plt.clf()
  fig = plt.hist(exp['R_piK_Bu2Dst0h_D0pi0_k_plus'], 100, density=True)
  plt.savefig('figs/R_piK_k_plus_pi0.pdf')
  plt.clf()
  fig = plt.hist(exp['R_piK_Bu2Dst0h_D0gamma_k_plus'], 100, density=True)
  plt.savefig('figs/R_piK_k_plus_gamma.pdf')
  plt.clf()
  fig = plt.hist(exp['R_piK_Bu2Dst0h_D0pi0_k_minus'], 100, density=True)
  plt.savefig('figs/R_piK_k_minus_pi0.pdf')
  plt.clf()
  fig = plt.hist(exp['R_piK_Bu2Dst0h_D0gamma_k_minus'], 100, density=True)
  plt.savefig('figs/R_piK_k_minus_gamma.pdf')
  plt.clf()
  fig = plt.hist(exp['R_piK_Bu2Dst0h_D0pi0_pi_plus'], 100, density=True)
  plt.savefig('figs/R_piK_pi_plus_pi0.pdf')
  plt.clf()
  fig = plt.hist(exp['R_piK_Bu2Dst0h_D0gamma_pi_plus'], 100, density=True)
  plt.savefig('figs/R_piK_pi_plus_gamma.pdf')
  plt.clf()
  fig = plt.hist(exp['R_piK_Bu2Dst0h_D0pi0_pi_minus'], 100, density=True)
  plt.savefig('figs/R_piK_pi_minus_pi0.pdf')
  plt.clf()
  fig = plt.hist(exp['R_piK_Bu2Dst0h_D0gamma_pi_minus'], 100, density=True)
  plt.savefig('figs/R_piK_pi_minus_gamma.pdf')
  plt.clf()

  # Part-reco results
  part_reco = {}
  part_reco['A_Bu2Dst0h_D0pi0_k_kpi']  = {'val' : 0.020, 'stat' : 0.007, 'syst' : 0.003}
  part_reco['A_Bu2Dst0h_D0gamma_k_kpi']  = {'val' : -0.004, 'stat' : 0.014, 'syst' : 0.003}
  part_reco['R_CP_Bu2Dst0h_D0pi0']  = {'val' : 1.051, 'stat' : 0.022, 'syst' : 0.028}
  part_reco['R_CP_Bu2Dst0h_D0gamma']  = {'val' : 0.952, 'stat' : 0.062, 'syst': 0.065}
  part_reco['A_CP_Bu2Dst0h_D0pi0_k']  = {'val' : -0.115, 'stat' : 0.019, 'syst' : 0.009}
  part_reco['A_CP_Bu2Dst0h_D0gamma_k']  = {'val' : 0.123, 'stat' : 0.054, 'syst': 0.031}
  part_reco['A_CP_Bu2Dst0h_D0pi0_pi']  = {'val' : 0.013, 'stat' : 0.007, 'syst' : 0.003}
  part_reco['A_CP_Bu2Dst0h_D0gamma_pi']  = {'val' : 0.000, 'stat' : 0.014, 'syst': 0.006}
  part_reco['R_piK_Bu2Dst0h_D0pi0_k_minus'] = {
      'val': 0.0202,
      'stat': 0.0035,
      'syst': 0.0023
  }
  part_reco['R_piK_Bu2Dst0h_D0pi0_k_plus'] = {
      'val': 0.0033,
      'stat': 0.0035,
      'syst': 0.0022
  }
  part_reco['R_piK_Bu2Dst0h_D0gamma_k_minus'] = {
      'val': 0.0117,
      'stat': 0.0215,
      'syst': 0.0313
  }
  part_reco['R_piK_Bu2Dst0h_D0gamma_k_plus'] = {
      'val': 0.0292,
      'stat': 0.0214,
      'syst': 0.0312
  }
  part_reco['R_piK_Bu2Dst0h_D0pi0_pi_minus'] = {
      'val': 0.00405,
      'stat': 0.00056,
      'syst': 0.00059
  }
  part_reco['R_piK_Bu2Dst0h_D0pi0_pi_plus'] = {
      'val': 0.00536,
      'stat': 0.00056,
      'syst': 0.00058
  }
  part_reco['R_piK_Bu2Dst0h_D0gamma_pi_minus'] = {
      'val': 0.00472,
      'stat': 0.00092,
      'syst': 0.00118
  }
  part_reco['R_piK_Bu2Dst0h_D0gamma_pi_plus'] = {
      'val': 0.00403,
      'stat': 0.00091,
      'syst': 0.00114
  }
  part_reco['R_Dst0KDst0pi_Bu2Dst0h_kpi'] = {
      'val': 0.0851,
      'stat': 0.0012,
      'syst': 0.0048
  }

  pars = ['R_CP', 'R_piK', 'A_CP', 'A_Bu2Dst0h', 'R_Dst']
  result_pi0 = result_pi0[result_pi0.par.str.contains('|'.join(pars))]
  result_gamma = result_gamma[result_gamma.par.str.contains('|'.join(pars))]
  result_pi0.replace(to_replace='A_Bu2Dst0h_D0pi0_pi0_k_kpi',
                     value='A_Bu2Dst0h_D0pi0_k_kpi',
                     inplace=True)
  result_gamma.replace(to_replace='A_Bu2Dst0h_D0pi0_gamma_k_kpi',
                       value='A_Bu2Dst0h_D0pi0_k_kpi',
                       inplace=True)
  result_gamma.replace(to_replace='A_Bu2Dst0h_D0gamma_gamma_k_kpi',
                       value='A_Bu2Dst0h_D0gamma_k_kpi',
                       inplace=True)

  # for p in pars:
  #   exp_mu = np.mean(exp[p])
  #   exp_sigma = np.std(exp[p])
  #   print(f'{p}: {exp_mu:.4f} +/- {exp_sigma:.4f}')
  #
  pars = result_gamma['par'].unique().tolist()
  pars = [s for s in pars if "R_Dst" not in s]
  chi2_dict = {}

  part_reco_R_val = part_reco['R_Dst0KDst0pi_Bu2Dst0h_kpi']['val']
  part_reco_R_err = part_reco['R_Dst0KDst0pi_Bu2Dst0h_kpi']['stat']

  gamma_Rgamma_val = result_gamma[(result_gamma.par == 'R_Dst0KDst0pi_Bu2Dst0h_D0gamma_kpi')]['val'].values[0]
  gamma_Rgamma_err = result_gamma[(result_gamma.par == 'R_Dst0KDst0pi_Bu2Dst0h_D0gamma_kpi')]['stat'].values[0]

  gamma_Rpi0_val = result_gamma[(result_gamma.par == 'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_kpi')]['val'].values[0]
  gamma_Rpi0_err = result_gamma[(result_gamma.par == 'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_kpi')]['stat'].values[0]

  pi0_Rpi0_val = result_pi0[(result_pi0.par == 'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_kpi')]['val'].values[0]
  pi0_Rpi0_err = result_pi0[(result_pi0.par == 'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_kpi')]['stat'].values[0]

  uf_arr = [
      ufloat(pi0_Rpi0_val, pi0_Rpi0_err),
      ufloat(gamma_Rpi0_val, gamma_Rpi0_err),
      ufloat(gamma_Rgamma_val, gamma_Rgamma_err)
  ]
  FR_total = WeightedAverage(uf_arr)
  # chi2_dict['R_Dst0KDst0pi_Bu2Dst0h_kpi'] = {
  #     'sigma':
  #         CalculateSigma(FR_total[0], FR_total[1], part_reco_R_val,
  #                        part_reco_R_err),
  #     'chi2':
  #         CalculateChi2(FR_total[0], FR_total[1], part_reco_R_val,
  #                       part_reco_R_err)
  # }

  for p in pars:
    fig, ax = plt.subplots(figsize=(8,6))

    # Belle expectations
    exp_mu = np.mean(exp[p])
    exp_sigma = np.std(exp[p])
    # exp_mu = b_factory[p].n
    # exp_sigma = b_factory[p].s
    low = exp_mu - exp_sigma
    high = exp_mu + exp_sigma
    low2 = exp_mu - 2*exp_sigma
    high2 = exp_mu + 2*exp_sigma
    low5 = exp_mu - 5*exp_sigma
    high5 = exp_mu + 5*exp_sigma
    low6 = exp_mu - 6*exp_sigma
    high6 = exp_mu + 6*exp_sigma
    low14 = exp_mu - 14*exp_sigma
    high14 = exp_mu + 14*exp_sigma

    plt.axvline(x=exp_mu,color='black',linestyle='--',label='Expected')
    plt.axvspan(low, high, color='#4575b4',label='68\% C.L.')
    plt.axvspan(high, high2, color='#91bfdb')
    plt.axvspan(low2, low, color='#91bfdb',label='95\% C.L.')

    plt.tick_params(axis='both', which='major', labelsize=18)

    part_reco_val = part_reco[p]['val']
    part_reco_stat = part_reco[p]['stat']
    part_reco_err = math.sqrt(part_reco[p]['stat']**2 + part_reco[p]['syst']**2)
    part_reco_frac = part_reco[p]['stat'] / part_reco_err
    plt.errorbar(part_reco_val,2.0,xerr=part_reco_err,fmt='',yerr=None,capsize=5,linewidth=1,linestyle='-',color='tab:red')
    plt.errorbar(part_reco_val,2.0,xerr=part_reco_err*part_reco_frac,fmt='o',yerr=None,capsize=5,linewidth=1.5,linestyle='-',color='k')

    # print(p)
    # print(part_reco_err)
    # print(part_reco_frac)

    p_gamma = False
    #Fit result
    if result_gamma['par'].str.contains(p).any():
      gamma_val = result_gamma[(result_gamma.par == p)]['val'].values[0]
      gamma_stat = result_gamma[(result_gamma.par == p)]['stat'].values[0]
      gamma_err = math.sqrt(
          result_gamma[(result_gamma.par == p)]['stat'].values[0]**2 +
          result_gamma[(result_gamma.par == p)]['syst'].values[0]**2)
      gamma_frac = result_gamma[(result_gamma.par == p)]['stat'].values[0]/gamma_err
      # print(result_gamma[(result_gamma.par == p)])
      # print(gamma_err)
      # print(gamma_frac)
      plt.errorbar(gamma_val,4.0,xerr=gamma_err,fmt='',yerr=None,capsize=5,linewidth=1,linestyle='-',color='tab:red')
      plt.errorbar(gamma_val,4.0,xerr=gamma_err*gamma_frac,fmt='o',yerr=None,capsize=5,linewidth=1.5,linestyle='-',color='k')
    if result_pi0['par'].str.contains(p).any():
      pi0_val = result_pi0[(result_pi0.par == p)]['val'].values[0]
      pi0_stat = result_pi0[(result_pi0.par == p)]['stat'].values[0]
      pi0_err = math.sqrt(
          result_pi0[(result_pi0.par == p)]['stat'].values[0]**2 +
          result_pi0[(result_pi0.par == p)]['syst'].values[0]**2)
      pi0_frac = result_pi0[(result_pi0.par == p)]['stat'].values[0]/pi0_err
      plt.errorbar(pi0_val,6.0,xerr=pi0_err,fmt='',yerr=None,capsize=5,linewidth=1,linestyle='-',color='tab:red')
      plt.errorbar(pi0_val,6.0,xerr=pi0_err*pi0_frac,fmt='o',yerr=None,capsize=5,linewidth=1.5,linestyle='-',color='k')
    else:
      p_gamma = True

    if p_gamma == True:
      chi2_dict[p] = {
          'sigma':
              CalculateSigma(gamma_val, gamma_stat, part_reco_val,
                             part_reco_stat),
          'chi2':
              CalculateChi2(gamma_val, gamma_stat, part_reco_val, part_reco_stat)
      }

    else:
      uf_arr = [ufloat(pi0_val, pi0_stat), ufloat(gamma_val, gamma_stat)]
      pi0_total = WeightedAverage(uf_arr)
      # print(p)
      # print(pi0_total)
      chi2_dict[p] = {
          'sigma':
              CalculateSigma(pi0_total[0], pi0_total[1], part_reco_val,
                             part_reco_stat),
          'chi2':
              CalculateChi2(pi0_total[0], pi0_total[1], part_reco_val,
                            part_reco_stat)
      }


    if 'A_Bu2Dst0h' in p:
      left_text = exp_mu + 12*exp_sigma
      span = high14 - low14
      plt.xlim(low14,high14 + span/2)
    else:
      left_text = exp_mu + 5.3*exp_sigma
      span = high6 - low6
      plt.xlim(low6,high6 + span/2)


    plt.text(left_text,2.4,"PR Analysis",fontsize=18)
    if 'R_CP' in p:
      plt.text(left_text,2.0,f"{part_reco_val:.3f} $\\pm$ {part_reco_err:.3f}",fontsize=18)
    else:
      plt.text(left_text,2.0,f"{part_reco_val:.4f} $\\pm$ {part_reco_err:.4f}",fontsize=18)
    plt.text(left_text,1.5,f"[LHCb-PAPER-2020-036]",fontsize=18)
    if result_gamma['par'].str.contains(p).any():
      if 'pi0' in p:
        plt.text(left_text,4.2,"$D^{*}\\rightarrow D[\\gamma]_{\\pi^{0}}$",fontsize=18)
      else:
        plt.text(left_text,4.2,"$D^{*}\\rightarrow D\\gamma$",fontsize=18)
      if 'R_CP' in p:
        plt.text(left_text,3.8,f"{gamma_val:.3f} $\\pm$ {gamma_err:.3f}",fontsize=18)
      else:
        plt.text(left_text,3.8,f"{gamma_val:.4f} $\\pm$ {gamma_err:.4f}",fontsize=18)
    if result_pi0['par'].str.contains(p).any():
      plt.text(left_text,6.2,"$D^{*}\\rightarrow D\\pi^{0}$",fontsize=18)
      if 'R_CP' in p:
        plt.text(left_text,5.8,f"{pi0_val:.3f} $\\pm$ {pi0_err:.3f}",fontsize=18)
      else:
        plt.text(left_text,5.8,f"{pi0_val:.4f} $\\pm$ {pi0_err:.4f}",fontsize=18)

    Dpi_arr = ['R_piK_Bu2Dst0h_D0gamma_pi_plus', 'R_piK_Bu2Dst0h_D0pi0_pi_plus', 'R_piK_Bu2Dst0h_D0gamma_pi_minus', 'R_piK_Bu2Dst0h_D0pi0_pi_minus', 'A_CP_Bu2Dst0h_D0pi0_pi', 'A_CP_Bu2Dst0h_D0gamma_pi', 'A_Bu2Dst0h_D0pi0_k_kpi', 'A_Bu2Dst0h_D0gamma_k_kpi']

    if p_gamma == True:
      if p not in Dpi_arr:
        plt.text(left_text, 7.2,'$B$-factory measurements:',fontsize=18)
      plt.legend(loc=(0.62, 0.65), fontsize=18,frameon=False)

    plt.ylim(0.0,8.0)
    plt.xlabel(return_label(p),fontsize=25,labelpad=10)
    plt.gca().axes.get_yaxis().set_visible(False)
    plt.tight_layout()

    fig.savefig('result_comparisons/unblind/Exp_vs_Obs_%s.pdf' % p)
    fig.savefig('result_comparisons/unblind/Exp_vs_Obs_%s.eps' % p, format='eps')

  #chi2_arr = np.fromiter(chi2_dict.values(), dtype=float)
  #n_pars = len(chi2_arr)
  n_pars = 0
  chi2_tot = 0
  for par, d in chi2_dict.items():
    chi2_tot += d['chi2']
    n_pars += 1
  chi2_ndf = chi2_tot/n_pars
  print(f'chi2/ndf = {chi2_ndf}')
  p_value = stats.distributions.chi2.sf(chi2_ndf, 1)
  print(f'p value = {p_value}')
  sigma = stats.norm.ppf(1-p_value/2)
  print(f'sigma = {sigma}')

  tex_file = open(f'result_comparisons/unblind/chi2_comparison.tex', 'w')
  tex_file.write('\\begin{tabular}{ccc}\n')
  tex_file.write('Observable & Agreement ($\\sigma$) & $\\chi^2$ \\\\ \n')
  tex_file.write('\\hline\n')
  for par, d in chi2_dict.items():
    p_val = stats.distributions.chi2.sf(d['chi2'], 1)
    s = stats.norm.ppf(1-p_val/2)
    # print(f"{s}\t{d['sigma']}")
    p_str = return_label(par)
    tex_file.write(f"{p_str} & {s:.2f} & {d['chi2']:.2f} \\\\ \n")
  tex_file.write('\\hline\n')
  tex_file.write(f'$\\chi^2/\\text{{ndf}}$ & & ${chi2_tot:.2f}/{n_pars}={chi2_ndf:.2f}$ \\\\ \n')
  tex_file.write('\\end{tabular}\n')
