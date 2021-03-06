import math, re, os, sys, glob
from ROOT import TFile, RooFitResult, RooGaussian, RooDataSet
import root_numpy as r_np
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from matplotlib import rc
from scipy import stats
from uncertainties import unumpy, ufloat
from uncertainties.umath import *

path = sys.argv[1]
param = sys.argv[2]

file_list = []
bu_high = []

# Loop over files in directory and append to list those that match regex
if os.path.isdir(path):
  for filename in os.listdir(path):
    m = re.search("Result_[0-9]+_[0-9]+_[0-9]+_([0-9]+).root", filename)
    if m:
        # Save upper bu dimn for each result
        bu_high.append(m.group(1))
        file_list.append(filename)

# Want to plot in ascending order
bu_high.sort()
file_list.sort()

cwd = os.getcwd()
os.chdir(path)

# Array to store parameter pull widths and error on width
par_pull_widths_arr = []
# Array to store mean parameter value and std dev
par_val_arr = []
# Array to store mean parameter error and std dev
par_err_arr = []
# Array to store mean total signal yield and error
signal_yield_arr = []

# Name of branches in tree (box and or effs)
branch_names = ['orEffSignal', 'boxEffSignal']
# Array to store efficiencies in
box_eff = []
or_eff = []
# n_mc needed to calculate error on efficiencies (for gamma mode)
n_mc_events = 14508

# Loop over files and extract result of interest
for i in range(0,len(file_list)):
  tf = TFile(file_list[i])
  # In result, params are stored in order mean [0], std dev [1]
  result_par_pull_widths = tf.Get("Result_Pull_" + param)
  result_par_val = tf.Get("Result_Val_" + param)
  result_par_err = tf.Get("Result_Err_" + param)
  result_signal_yield = tf.Get("Result_Val_N_Bu2Dst0h_D0gamma_gamma_pi")
  result_signal_yield_err = tf.Get("Result_Err_N_Bu2Dst0h_D0gamma_gamma_pi")
  # Final values of fit to pulls
  par_pull_widths = result_par_pull_widths.floatParsFinal()
  par_val = result_par_val.floatParsFinal()
  par_err = result_par_err.floatParsFinal()
  signal_yield = result_signal_yield.floatParsFinal()
  signal_yield_err = result_signal_yield_err.floatParsFinal()
  # Save value and error of width for each box dimn
  if i == 0:
    initial_width = ufloat(par_pull_widths[1].getVal(), par_pull_widths[1].getError())
  par_pull_widths_arr.append(ufloat(par_pull_widths[1].getVal(), par_pull_widths[1].getError()))
  par_val_arr.append(ufloat(par_val[0].getVal(), par_err[0].getVal()))
  par_err_arr.append(ufloat(par_err[0].getVal(), par_err[1].getVal()))
  signal_yield_arr.append(ufloat(signal_yield[0].getVal(), signal_yield_err[0].getVal()))

  # 2D array with row element eff_tree[0] - orEff = first column, boxEff = second
  eff_tree = r_np.root2array(file_list[i], "tree", branch_names)
  # Error on boxEff and orEff are binomial = 1/N(sqrt(Np(1-p))) = 1/N_mcsqrt(N_mc*eff(1-eff))
  or_eff.append(ufloat(eff_tree[0][0], math.sqrt(n_mc_events*eff_tree[0][0]*(1-eff_tree[0][0]))/n_mc_events))
  box_eff.append(ufloat(eff_tree[0][1], math.sqrt(n_mc_events*eff_tree[0][1]*(1-eff_tree[0][1]))/n_mc_events))

shared_yield = np.array(np.divide(np.multiply(signal_yield_arr[0], box_eff), or_eff), dtype=object)
frac_shared_yield = np.divide(shared_yield, signal_yield_arr)

linear_err_fn = (np.multiply(np.divide(np.ones(len(file_list))*math.sqrt(2), signal_yield_arr), shared_yield) + np.divide((signal_yield_arr-shared_yield), signal_yield_arr))*initial_width
# sqrt from unumpy as can handle uncertainty types
quadratic_err_fn = unumpy.sqrt(np.square(np.multiply(np.divide(np.ones(len(file_list))*math.sqrt(2), signal_yield_arr), shared_yield)) + np.square(np.divide((signal_yield_arr-shared_yield), signal_yield_arr)))*initial_width

# par_pull_widths_arr = np.divide(par_pull_widths_arr, np.ones(len(file_list))*initial_width)
print(frac_shared_yield)
fig = plt.figure()
plt.errorbar(unumpy.nominal_values(frac_shared_yield), unumpy.nominal_values(par_err_arr), xerr=unumpy.std_devs(frac_shared_yield), yerr=unumpy.std_devs(par_err_arr), label='Pseudo-experiments')
plt.xlabel('$N_{Box}/N_{T}$')
plt.ylabel('Error')
plt.title(param)
fig.savefig("box_yield_vs_" + param + "_err.pdf")

fig = plt.figure()
plt.errorbar(unumpy.nominal_values(frac_shared_yield), unumpy.nominal_values(quadratic_err_fn), xerr=unumpy.std_devs(frac_shared_yield), yerr=unumpy.std_devs(quadratic_err_fn), label='$\\frac{\sigma_{N_{T}}}{\sigma_{fit}}=\sqrt{(\\frac{N_{Box}\sqrt{2}}{N_{T}})^{2}+(\\frac{N_{T}-N_{Box}}{N_{T}})^{2}}$')
plt.errorbar(unumpy.nominal_values(frac_shared_yield), unumpy.nominal_values(linear_err_fn), xerr=unumpy.std_devs(frac_shared_yield), yerr=unumpy.std_devs(linear_err_fn), label='$\\frac{\sigma_{N_{T}}}{\sigma_{fit}}=\\frac{N_{Box}\sqrt{2}}{N_{T}}+\\frac{N_{T}-N_{Box}}{N_{T}}$')
plt.errorbar(unumpy.nominal_values(frac_shared_yield), unumpy.nominal_values(par_pull_widths_arr), xerr=unumpy.std_devs(frac_shared_yield), yerr=unumpy.std_devs(par_pull_widths_arr), label='Pseudo-experiments')
plt.legend(loc='upper left')
plt.xlabel('$N_{Box}/N_{T}$')
plt.ylabel('Pull Width')
plt.title(param)
fig.savefig("box_yield_vs_" + param + "_pull_width.pdf")

