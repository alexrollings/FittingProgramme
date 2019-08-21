import math, re, os, sys, glob
from ROOT import TFile, RooFitResult
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

  m = re.search("Result(0.[0-9]+)_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + ".root", filename)
  if m:
    rndm = m.group(1)
  else:
    sys.exit("No file matching regex")

  tf = TFile(filename)
  result = tf.Get("Result_" + rndm)

  if result == None:
    sys.exit("Could not extract Result_" + rndm + " from " + filename)

  #List of params we want, with their value and error
  #Use these to calculate all the other yields
  vars = ["N_Bu2Dst0h_D0gamma_gamma_pi", "N_Bu2Dst0h_D0gamma_gamma_k"]

  #Dict to add the values and errors of the observables into
  obs = {}

  #Correlation matrix
  corr = np.ones((len(vars),len(vars)))

  pars = result.floatParsFinal()

  for i in range(0,len(pars)):

    p = pars[i]
    p_name = p.GetName()

    if(p_name in vars):

      obs[p_name] = (p.getVal(),p.getError())

  #Fill correlation matrix
  for a in range(0,len(vars)):
    for b in range(0,len(vars)):
      corr[a,b] = result.correlation(vars[a],vars[b])

  print(corr)


  # (obs["n_dpi_LL_%s_corr" % k], obs["n_dpi_DD_%s_corr" % k], obs["R_dk_vs_dpi_KPi_%s_corr" % k], obs["R_dk_vs_dpi_PiK_%s_corr" % k], obs["R_%s_corr" % k]) = u.correlated_values_norm([obs["n_dpi_LL_%s" % k], obs["n_dpi_DD_%s" % k], obs["R_dk_vs_dpi_KPi_%s" % k], obs["R_dk_vs_dpi_PiK_%s" % k], obs["R_%s" % k]] , corr[k])
  #
  # #Total Dpi yield
  # obs["n_dpi_%s" % k] = obs["n_dpi_DD_%s_corr" % k] + obs["n_dpi_LL_%s_corr" % k]
  # #print(obs["n_dpi_%s" % k])
  #
  # #Total Dpi SS yield
  # obs["n_dpi_SS_%s" % k] = (obs["R_%s_corr" % k]/(1.0 + obs["R_%s_corr" % k])) * obs["n_dpi_%s" % k]
  # print(obs["n_dpi_SS_%s" % k])
  #
  # obs["n_dpi_OS_%s" % k] = (1.0/(1.0 + obs["R_%s_corr" % k])) * obs["n_dpi_%s" % k]
  # print(obs["n_dpi_OS_%s" % k])
  #
  # obs["n_dk_SS_%s" % k] = obs["R_dk_vs_dpi_KPi_%s_corr" % k] * obs["n_dpi_SS_%s" % k]
  # print(obs["n_dk_SS_%s" % k])
  #
  # obs["n_dk_OS_%s" % k] = obs["R_dk_vs_dpi_PiK_%s_corr" % k] * obs["n_dpi_OS_%s" % k]
  # print(obs["n_dk_OS_%s" % k])
  #
  #
  #
  #
  #
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
