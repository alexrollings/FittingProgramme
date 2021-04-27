import glob, os, sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import random
import math
import json
from useful_functions import return_label
from uncertainties import ufloat
import matplotlib
matplotlib.use('Agg')

rc('font',**{'family': 'serif','serif': ['Roman']})
rc('text', usetex=True)

# Fit results saved in json
path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/'
json_fname_result_pi0 = f'{path}json/result_total_pi0.json'
if os.path.exists(json_fname_result_pi0):
  with open(json_fname_result_pi0, 'r') as json_file_result_pi0:
    result_pi0 = json.load(json_file_result_pi0)

json_fname_result_gamma = f'{path}json/result_total_gamma.json'
if os.path.exists(json_fname_result_gamma):
  with open(json_fname_result_gamma, 'r') as json_file_result_gamma:
    result_gamma = json.load(json_file_result_gamma)

# LHCb combination
# phi3_av_err = (4.6 + 5.3)*0.5
# phi3_val_err = ufloat(math.radians(71.1),math.radians(phi3_av_err))
phi3_val_err = ufloat(math.radians(67),math.radians(4))
phi3 = np.random.normal(phi3_val_err.n, phi3_val_err.s, 10000)

# No assumptions in D*π mode
# B- -> D*0 π-
rB_Dpi = np.random.uniform(0.0, 0.02, 10000)
dB_Dpi = np.random.uniform(math.radians(0.0), math.radians(180.0), 10000)

# B- -> D*0 K-
# rB_DK = np.random.uniform(0.0, 0.2, 10000)
# dB_DK_av_err = (18 + 10)*0.5
# dB_DK_val_err = ufloat(math.radians(314.0),math.radians(dB_DK_av_err))
# dB_DK = np.random.normal(dB_DK_val_err.n, dB_DK_val_err.s, 10000)

# B factory GGSZ
rB_DK = np.random.normal(0.135, 0.034, 10000)
dB_DK = np.random.normal(304, 17, 10000)

# FAV: D0 -> K-π+
rD_val = np.sqrt(0.00344)
rD_err = rD_val * 2 * (2e-5/0.00344)
rD_val_err = ufloat(rD_val,rD_err)
rD = np.random.normal(rD_val_err.n, rD_val_err.s, 10000)

dD_av_err = (8.6 + 10.2)*0.5
dD_val_err = ufloat(math.radians(192.1),math.radians(dD_av_err))
dD = np.random.normal(dD_val_err.n, dD_val_err.s, 10000)

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

pi0_DK_pik_plus = rB_DK**2 + rD**2 + 2 * rB_DK * rD * np.cos(dB_DK + dD + phi3)
pi0_DK_pik_minus = rB_DK**2 + rD**2 + 2 * rB_DK * rD * np.cos(dB_DK + dD - phi3)
gamma_DK_pik_plus = rB_DK**2 + rD**2 - 2 * rB_DK * rD * np.cos(dB_DK + dD + phi3)
gamma_DK_pik_minus = rB_DK**2 + rD**2 - 2 * rB_DK * rD * np.cos(dB_DK + dD - phi3)

R_pi0_DK_pik_minus = pi0_DK_pik_minus / pi0_DK_kpi_minus
R_pi0_DK_pik_plus = pi0_DK_pik_plus / pi0_DK_kpi_plus
R_gamma_DK_pik_minus = gamma_DK_pik_minus / gamma_DK_kpi_minus
R_gamma_DK_pik_plus = gamma_DK_pik_plus / gamma_DK_kpi_plus

#Observables
exp = {}
exp['R_CP_Bu2Dst0h_D0pi0']  = ((pi0_DK_hh_minus + pi0_DK_hh_plus)/(pi0_Dpi_hh_minus + pi0_Dpi_hh_plus))
exp['R_CP_Bu2Dst0h_D0gamma'] = ((gamma_DK_hh_minus + gamma_DK_hh_plus)/(gamma_Dpi_hh_minus + gamma_Dpi_hh_plus))

exp['R_piK_Bu2Dst0h_D0pi0_k_total'] = (R_pi0_DK_pik_minus + R_pi0_DK_pik_plus) / 2
exp['R_piK_Bu2Dst0h_D0gamma_k_total'] = (R_gamma_DK_pik_minus + R_gamma_DK_pik_plus) / 2

# Part-reco results
part_reco = {}
part_reco['R_CP_Bu2Dst0h_D0pi0']  = {'Value' : 1.051, 'Error' : 0.036}
part_reco['R_CP_Bu2Dst0h_D0gamma']  = {'Value' : 0.952, 'Error' : 0.090}
part_reco['R_piK_Bu2Dst0h_D0pi0_k_total'] = {'Value' : 0.0118, 'Error' : 0.0035}
part_reco['R_piK_Bu2Dst0h_D0gamma_k_total'] = {'Value' : 0.0163, 'Error' : 0.0373}

# Results from GLW/ADS B->D*h from B-factories
# babar = {}
# babar['R_CP_Bu2Dst0h_D0pi0']  = ufloat(1.31, 0.13)
# babar['R_CP_Bu2Dst0h_D0gamma']  = ufloat(1.09, 0.13)
# babar['R_piK_Bu2Dst0h_D0pi0_k_total'] = ufloat(0.013, 0.016)
# babar['R_piK_Bu2Dst0h_D0gamma_k_total'] = ufloat(0.018, 0.010)
#
# belle = {}
# belle['R_CP_Bu2Dst0h_D0pi0']  = ufloat(1.41, 0.25)
# belle['R_CP_Bu2Dst0h_D0gamma']  = ufloat(1.15, 0.33)
#
# b_factory = {}
# for p in ['R_CP_Bu2Dst0h_D0pi0', 'R_CP_Bu2Dst0h_D0gamma']:
#   b_factory[p] = ufloat(
#       (babar[p].n / babar[p].s**2 + belle[p].n / belle[p].s**2) /
#       (1 / babar[p].s**2 + 1 / belle[p].s**2),
#       math.sqrt((1 / babar[p].s**2 + 1 / belle[p].s**2)**(-1)))
# b_factory['R_piK_Bu2Dst0h_D0pi0_k_total'] = babar['R_piK_Bu2Dst0h_D0pi0_k_total']
# b_factory['R_piK_Bu2Dst0h_D0gamma_k_total'] = babar['R_piK_Bu2Dst0h_D0gamma_k_total']
#
# print(b_factory)

pars = ['R_CP_Bu2Dst0h_D0pi0', 'R_CP_Bu2Dst0h_D0gamma', 'R_piK_Bu2Dst0h_D0pi0_k_total', 'R_piK_Bu2Dst0h_D0gamma_k_total']

# Scale stat error to include syst
syst = {
    'R_CP': {
        'gamma': 1.05,
        'partial': 1.08,
        'pi0': 1.02
    },
    'R_piK': {
        'gamma': 1.05,
        'partial': 1.05,
        'pi0': 1.03
    }
}

for p in pars:
  fig, ax = plt.subplots(figsize=(8,6))

  part_reco_val = part_reco[p]['Value']
  part_reco_err = part_reco[p]['Error']
  plt.errorbar(part_reco_val,2.0,xerr=part_reco_err,fmt='o',yerr=None,capsize=5,linewidth=1,linestyle='-',color='k')

  p_gamma = False
  #Fit result
  if p in result_gamma:
    # plt.errorbar(result_gamma[p]['Value'],1.0,xerr=np.sqrt(result_gamma[p]['Statistical Error']**2 + result_gamma[p]['Systematic Error']**2),fmt='o',yerr=None,capsize=5,linewidth=1,linestyle='--',color='red')
    syst_corr = 1
    for k in syst:
      if k in p:
        if 'pi0' in p:
          syst_corr = syst[k]['partial']
        else:
          syst_corr = syst[k]['gamma']
    gamma_val = result_gamma[p]['Value']
    gamma_err = result_gamma[p]['Statistical Error'] * syst_corr
    plt.errorbar(gamma_val,4.0,xerr=gamma_err,fmt='o',yerr=None,capsize=5,linewidth=1,linestyle='-',color='k')
  if p in result_pi0:
    # plt.errorbar(result_pi0[p]['Value'],1.0,xerr=np.sqrt(result_pi0[p]['Statistical Error']**2 + result_pi0[p]['Systematic Error']**2),fmt='o',yerr=None,capsize=5,linewidth=1,linestyle='--',color='red')
    syst_corr = 1
    for k in syst:
      if k in p:
        syst_corr = syst[k]['pi0']
    pi0_val = result_pi0[p]['Value']
    pi0_err = result_pi0[p]['Statistical Error'] * syst_corr
    plt.errorbar(pi0_val,6.0,xerr=pi0_err,fmt='o',yerr=None,capsize=5,linewidth=1,linestyle='-',color='k')
  else:
    p_gamma = True

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

  plt.axvline(x=exp_mu,color='black',linestyle='--',label='Expected')
  plt.axvspan(low, high, color='#4575b4',label='68\% C.L.')
  plt.axvspan(high, high2, color='#91bfdb')
  plt.axvspan(low2, low, color='#91bfdb',label='95\% C.L.')

  plt.tick_params(axis='both', which='major', labelsize=18)

  span = high6 - low6
  plt.xlim(low6,high6 + span/2)

  plt.text(high5,2.4,"PR Analysis",fontsize=18)
  if 'R_CP' in p:
    plt.text(high5,2.0,f"{part_reco_val:.3f} $\\pm$ {part_reco_err:.3f}",fontsize=18)
  else:
    plt.text(high5,2.0,f"{part_reco_val:.4f} $\\pm$ {part_reco_err:.4f}",fontsize=18)
  plt.text(high5,1.5,f"[LHCb-PAPER-2020-036]",fontsize=18)
  if p in result_gamma:
    if 'pi0' in p:
      plt.text(high5,4.2,"$D^{*}\\rightarrow D[\\gamma]_{\\pi^{0}}$",fontsize=18)
    else:
      plt.text(high5,4.2,"$D^{*}\\rightarrow D\\gamma$",fontsize=18)
    if 'R_CP' in p:
      plt.text(high5,3.8,f"{gamma_val:.3f} $\\pm$ {gamma_err:.3f}",fontsize=18)
    else:
      plt.text(high5,3.8,f"{gamma_val:.4f} $\\pm$ {gamma_err:.4f}",fontsize=18)
  if p in result_pi0:
    plt.text(high5,6.2,"$D^{*}\\rightarrow D\\pi^{0}$",fontsize=18)
    if 'R_CP' in p:
      plt.text(high5,5.8,f"{pi0_val:.3f} $\\pm$ {pi0_err:.3f}",fontsize=18)
    else:
      plt.text(high5,5.8,f"{pi0_val:.4f} $\\pm$ {pi0_err:.4f}",fontsize=18)


  if p_gamma == True:
    plt.text(high5, 7.2,'$B$-factories GGSZ analyses:',fontsize=18)
    plt.legend(loc=(0.6, 0.65), fontsize=18,frameon=False)

  plt.ylim(0.0,8.0)
  plt.xlabel(return_label(p),fontsize=25,labelpad=10)
  plt.gca().axes.get_yaxis().set_visible(False)
  plt.tight_layout()

  fig.savefig('result_comparisons/Exp_vs_Obs_%s.pdf' % p)
  fig.savefig('result_comparisons/Exp_vs_Obs_%s.eps' % p, format='eps')
