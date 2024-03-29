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

def find_nearest(array, value):
  array = np.asarray(array)
  idx = (np.abs(array - value)).argmin()
  return idx

# path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/68a3b7e/results/'
# path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/2c4acd4/results/'
# path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/1b7aea2/results/'
# path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/42f42b3/results/'
# path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/box_scan/results/'
paths = []
paths.append('/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/box_scan/results/')
paths.append('/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/independent_scan/results/')

# bu_low = 5150
# bu_high = []
# delta_low = 110
# delta_high = 210

bu_low = 5180
bu_high = []
delta_low = 105
delta_high = 190

widths_dict = {}
err_dict = {}

for p in paths:
  file_list = []

# Loop over files in directory and append to list those that match regex
  if os.path.isdir(p):
    for filename in os.listdir(p):
      m = re.search("Result_[0-9]+_[0-9]+_[0-9]+_([0-9]+).root", filename)
      if m:
        # Save upper bu dimn for each result
        bu_high.append(m.group(1))
        file_list.append(filename)

# Want to plot in ascending order
  bu_high.sort()
  file_list.sort()

  cwd = os.getcwd()
  os.chdir(p)

# Array to store pull widths and error on width
  signal_yield_pull_widths = []
  signal_yield_err = []
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
  box_eff_vals = []
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
    signal_yield_err.append(
        ufloat(pars_yield_err[0].getVal(),
               pars_yield_err[1].getVal()))
    signal_yield.append(
        ufloat(pars_yield[0].getVal(), pars_yield_err[0].getVal()))

    # 2D array with row element eff_tree[0] - orEff = first column, boxEff = second
    eff_tree = r_np.root2array(file_list[i], "tree", branch_names)
    # Error on boxEff and orEff are binomial = 1/N(sqrt(Np(1-p))) = 1/N_mcsqrt(N_mc*eff(1-eff))
    or_eff.append(ufloat(eff_tree[0][0], eff_tree[0][1]))
    box_eff.append(ufloat(eff_tree[0][2], eff_tree[0][3]))
    box_eff_vals.append(eff_tree[0][2])

  halfway_idx = find_nearest(box_eff_vals, 0.5)
  halfway_pull = signal_yield_pull_widths[halfway_idx]

  shared_yield = np.array(np.divide(np.multiply(signal_yield[0], box_eff),
                                    or_eff),
                          dtype=object)

  halfway_fn = (math.sqrt(2) /
                   signal_yield[halfway_idx].n) * shared_yield[halfway_idx].n + (
                       signal_yield[halfway_idx].n -
                       shared_yield[halfway_idx].n) / signal_yield[halfway_idx].n

# align linear fn with pulls at mid-point
  align_shift = halfway_pull - halfway_fn

  linear_err_fn = (np.multiply(
      np.divide(np.ones(len(file_list)) * math.sqrt(2), signal_yield),
      shared_yield) + np.divide(
          (signal_yield - shared_yield), signal_yield)) + align_shift

  widths_dict[p] = signal_yield_pull_widths
  err_dict[p] = signal_yield_err

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
# plt.errorbar(
#     unumpy.nominal_values(box_eff),
#     unumpy.nominal_values(linear_err_fn),
#     xerr=unumpy.std_devs(box_eff),
#     yerr=unumpy.std_devs(linear_err_fn),
#     label=
#     '$\\frac{\sigma_{N_{T}}}{\sigma_{fit}}=\\frac{N_{Box}\sqrt{2}}{N_{T}}+\\frac{N_{T}-N_{Box}}{N_{T}}$'
# )
for p in paths:
  plt.errorbar(unumpy.nominal_values(box_eff),
               unumpy.nominal_values(widths_dict[p]),
               xerr=unumpy.std_devs(box_eff),
               yerr=unumpy.std_devs(widths_dict[p])),
             # label='Pseudo-experiments')
# plt.legend(loc='upper left')
plt.xlabel('$\\epsilon_{Box}$')
plt.ylabel('$\\sigma_{\\mathcal{P}}$')
fig.savefig("/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/box_scan.pdf")

plt.clf()
for p in paths:
  plt.errorbar(unumpy.nominal_values(box_eff),
               unumpy.nominal_values(err_dict[p]),
               xerr=unumpy.std_devs(box_eff),
               yerr=unumpy.std_devs(err_dict[p]))
plt.xlabel('$\\epsilon_{Box}$')
plt.ylabel('$\\sigma_{N_{T}}$')
fig.savefig("/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/pulls/error_scan.pdf")
