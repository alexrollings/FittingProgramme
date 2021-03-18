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

path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/68a3b7e/results/'

bu_low = 5150
bu_high = []
delta_low = 110
delta_high = 210

file_list = []

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

# Array to store pull widths and error on width
signal_yield_pull_widths = []
# Array to store mean total signal yield and std dev
signal_yield = []

# Name of branches in tree (box and or effs)
branch_names = [
    'orEff_Bu2Dst0pi_D0gamma', 'orEffErr_Bu2Dst0pi_D0gamma',
    'boxEff_Bu2Dst0pi_D0gamma', 'boxEffErr_Bu2Dst0pi_D0gamma',
    'buEff_Bu2Dst0pi_D0gamma', 'buEffErr_Bu2Dst0pi_D0gamma',
    'deltaEff_Bu2Dst0pi_D0gamma', 'deltaEffErr_Bu2Dst0pi_D0gamma'
]
# Array to store efficiencies in
box_eff = []
or_eff = []
# n_mc needed to calculate error on efficiencies

# Loop over files and extract result of interest
for i in range(0, len(file_list)):
  tf = TFile(file_list[i])
  # In result, params are stored in order mean [0], std dev [1]
  result_yield_pull_widths = tf.Get("Result_Pull_yieldTotSignal")
  result_yield = tf.Get("Result_Val_yieldTotSignal")
  result_yield_err = tf.Get("Result_Err_yieldTotSignal")
  # Final values of fit to pulls
  pars_yield_pull_widths = result_yield_pull_widths.floatParsFinal()
  pars_yield = result_yield.floatParsFinal()
  pars_yield_err = result_yield_err.floatParsFinal()
  # Save value and error of width for each box dimn
  if i == 0:
    initial_width = ufloat(pars_yield_pull_widths[1].getVal(),
                           pars_yield_pull_widths[1].getError())
  signal_yield_pull_widths.append(
      ufloat(pars_yield_pull_widths[1].getVal(),
             pars_yield_pull_widths[1].getError()))
  signal_yield.append(
      ufloat(pars_yield[0].getVal(), pars_yield_err[0].getVal()))

  # 2D array with row element eff_tree[0] - orEff = first column, boxEff = second
  eff_tree = r_np.root2array(file_list[i], "tree", branch_names)
  # Error on boxEff and orEff are binomial = 1/N(sqrt(Np(1-p))) = 1/N_mcsqrt(N_mc*eff(1-eff))
  or_eff.append(ufloat(eff_tree[0][0], eff_tree[0][1]))
  box_eff.append(ufloat(eff_tree[0][2], eff_tree[0][3]))

shared_yield = np.array(np.divide(np.multiply(signal_yield[0], box_eff),
                                  or_eff),
                        dtype=object)
frac_shared_yield = np.divide(shared_yield, signal_yield)

linear_err_fn = (np.multiply(
    np.divide(np.ones(len(file_list)) * math.sqrt(2), signal_yield),
    shared_yield) + np.divide(
        (signal_yield - shared_yield), signal_yield)) * initial_width
# # sqrt from unumpy as can handle uncertainty types
# quadratic_err_fn = unumpy.sqrt(
#     np.square(
#         np.multiply(
#             np.divide(np.ones(len(file_list)) *
#                       math.sqrt(2), signal_yield), shared_yield)) +
#     np.square(np.divide(
#         (signal_yield - shared_yield), signal_yield))) * initial_width

# signal_yield_pull_widths = np.divide(signal_yield_pull_widths, np.ones(len(file_list))*initial_width)

fig = plt.figure()
# plt.errorbar(unumpy.nominal_values(frac_shared_yield), unumpy.nominal_values(quadratic_err_fn), xerr=unumpy.std_devs(frac_shared_yield), yerr=unumpy.std_devs(quadratic_err_fn), label='$\\frac{\sigma_{N_{T}}}{\sigma_{fit}}=\sqrt{(\\frac{N_{Box}\sqrt{2}}{N_{T}})^{2}+(\\frac{N_{T}-N_{Box}}{N_{T}})^{2}}$')
plt.errorbar(
    unumpy.nominal_values(frac_shared_yield),
    unumpy.nominal_values(linear_err_fn),
    xerr=unumpy.std_devs(frac_shared_yield),
    yerr=unumpy.std_devs(linear_err_fn),
    label=
    '$\\frac{\sigma_{N_{T}}}{\sigma_{fit}}=\\frac{N_{Box}\sqrt{2}}{N_{T}}+\\frac{N_{T}-N_{Box}}{N_{T}}$'
)
plt.errorbar(unumpy.nominal_values(box_eff),
             unumpy.nominal_values(signal_yield_pull_widths),
             xerr=unumpy.std_devs(box_eff),
             yerr=unumpy.std_devs(signal_yield_pull_widths),
             label='Pseudo-experiments')
plt.legend(loc='upper left')
plt.xlabel('$\\epsilon_{Box}$')
plt.ylabel('$\\sigma_{\\mathcal{P}}$')
fig.savefig(path + "/box_scan.pdf")
