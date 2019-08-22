import math, re, os, sys, glob
from ROOT import TFile, RooFitResult
import root_numpy as r_np
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
from uncertainties import unumpy, ufloat
from uncertainties.umath import *
import uncertainties as u
import argparse

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '-p',
      '--path',
      type=str,
      help='Directory where results are stored and PDFs will be saved',
      required=True)
  parser.add_argument(
      '-dl',
      '--delta_low',
      type=str,
      help='Lower delta mass range',
      required=True)
  parser.add_argument(
      '-dh',
      '--delta_high',
      type=str,
      help='Upper delta mass range',
      required=True)
  parser.add_argument(
      '-bl',
      '--bu_low',
      type=str,
      help='Lower bu mass range',
      required=True)
  parser.add_argument(
      '-bh',
      '--bu_high',
      type=str,
      help='Upper bu mass range',
      required=True)
  args = parser.parse_args()

  path = args.path
  delta_low = args.delta_low
  delta_high = args.delta_high
  bu_low = args.bu_low
  bu_high = args.bu_high

  filename = path + "/DataResult_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + ".root"

  tf = TFile(filename)
  result = tf.Get("fitresult_simPdf_0_fullDataHist")
  if result == None:
    sys.exit("Could not extract result from " + filename)
  #Floating fit parameters
  pars = result.floatParsFinal()

  branch_names = ['orEffSignal_gamma', 'boxEffSignal_gamma']
  n_mc_events = 14508
  eff_tree = r_np.root2array(filename, "tree", branch_names)
  #Efficiencies stoted in uncertainties array with binomial error
  or_eff = ufloat(eff_tree[0][0], math.sqrt(n_mc_events*eff_tree[0][0]*(1-eff_tree[0][0]))/n_mc_events)
  box_eff = ufloat(eff_tree[0][1], math.sqrt(n_mc_events*eff_tree[0][1]*(1-eff_tree[0][1]))/n_mc_events)

  #List of params we want, with their value and error
  #Use these to calculate all the other yields
  variables = ["N_Bu2Dst0h_D0gamma_gamma_pi_0", "N_Bu2Dst0h_D0gamma_gamma_k_0"]
  #Dict to add the values and errors of the observables into
  obs = {}
  #Correlation matrix
  corr = np.ones((len(variables),len(variables)))

  for i in range(0,len(pars)):
    p = pars[i]
    p_name = p.GetName()
    if(p_name in variables):
      # In python, tuples () are immutable - can't change value: convert to tuple after calculating corrected error
      obs[p_name] = [p.getVal(),p.getError()]

  yield_tot_pi = ufloat(obs["N_Bu2Dst0h_D0gamma_gamma_pi_0"][0], obs["N_Bu2Dst0h_D0gamma_gamma_pi_0"][1])
  yield_box_pi = np.divide(np.multiply(yield_tot_pi, box_eff), or_eff)
  obs["N_Bu2Dst0h_D0gamma_gamma_pi_0"][1] = ((unumpy.nominal_values(yield_box_pi)/unumpy.nominal_values(yield_tot_pi)*math.sqrt(2))+(1-unumpy.nominal_values(yield_tot_pi)/unumpy.nominal_values(yield_box_pi)))*unumpy.std_devs(yield_tot_pi)

  yield_tot_k = ufloat(obs["N_Bu2Dst0h_D0gamma_gamma_k_0"][0], obs["N_Bu2Dst0h_D0gamma_gamma_k_0"][1])
  yield_box_k = np.divide(np.multiply(yield_tot_k, box_eff), or_eff)
  obs["N_Bu2Dst0h_D0gamma_gamma_k_0"][1] = ((unumpy.nominal_values(yield_box_k)/unumpy.nominal_values(yield_tot_k)*math.sqrt(2))+(1-unumpy.nominal_values(yield_tot_k)/unumpy.nominal_values(yield_box_k)))*unumpy.std_devs(yield_tot_k)

  # Convert dict values from lists to tuples to make them immutable (easier to debug)
  obs = {key:tuple(lst) for key, lst in obs.items()}

  #Fill correlation matrix - double counting doesn't effect this
  for a in range(0,len(variables)):
    for b in range(0,len(variables)):
      corr[a,b] = result.correlation(variables[a],variables[b])

  # Returns numbers with the correct uncertainties and correlations, given the covariance matric
  (obs["N_Bu2Dst0h_D0gamma_gamma_pi_0_corr"], obs["N_Bu2Dst0h_D0gamma_gamma_k_0_corr"]) = u.correlated_values_norm([obs["N_Bu2Dst0h_D0gamma_gamma_pi_0"], obs["N_Bu2Dst0h_D0gamma_gamma_k_0"]], corr)

  #Ratio D*K/D*π
  obs["ratioKpi_Bu2Dst0h_D0gamma_gamma"] = obs["N_Bu2Dst0h_D0gamma_gamma_k_0_corr"] / obs["N_Bu2Dst0h_D0gamma_gamma_pi_0_corr"]
  print("N_Bu2Dst0h_D0gamma_gamma_pi_0_corr = " + str(obs["N_Bu2Dst0h_D0gamma_gamma_pi_0_corr"]))
  print("N_Bu2Dst0h_D0gamma_gamma_k_0_corr = " + str(obs["N_Bu2Dst0h_D0gamma_gamma_k_0_corr"]))
  print("ratioKpi_Bu2Dst0h_D0gamma_gamma = " + str(obs["ratioKpi_Bu2Dst0h_D0gamma_gamma"]))

  # file = open("../results/Yields_%s.tex" % years, "w")
  # file.write("\\begin{table}[t]\n")
  # file.write("\\centering\n")
  # file.write("\\begin{tabular}{l l l}\n")
  # file.write("\\hline\n")
  # file.write("Mode & Yield (full Dalitz) & Yield ($K^*(892)^\\pm$ region) \\\\ \\hline\n")
  # file.write("$N_{SS}^{D\\pipm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dpi_SS_N"],obs["n_dpi_SS_Y"]))
  # file.write("$N_{OS}^{D\\pipm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dpi_OS_N"],obs["n_dpi_OS_Y"]))
  # file.write("$N_{SS}^{D\\Kpm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dk_SS_N"],obs["n_dk_SS_Y"]))
  # file.write("$N_{OS}^{D\\Kpm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dk_OS_N"],obs["n_dk_OS_Y"]))
  # file.write("\\end{tabular}\n")
  # file.write("\\caption{Total signal yields measured in the full Dalitz and restricted $K^*(892)^\\pm$ region invariant mass fits.}\n")
  # file.write("\\label{tab:yields}\n")
  # file.write("\\end{table}")
  # file.close()
