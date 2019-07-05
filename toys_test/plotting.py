import math, re, os, sys, glob
from ROOT import TFile, RooFitResult, RooGaussian, RooDataSet
import root_numpy as r_np
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from matplotlib import rc
from scipy import stats
from uncertainties import ufloat

path = sys.argv[1]

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
signal_yield_pull_widths = np.zeros(len(file_list))
# Array to store mean total signal yield and std dev
signal_yield = np.zeros(len(file_list))

# Name of branches in tree (box and or effs)
branch_names = ['orEffSignal', 'boxEffSignal']
# Array to store efficiencies in
box_eff = np.zeros(len(file_list))
or_eff = np.zeros(len(file_list))
# n_mc needed to calculate error on efficiencies
n_mc_events = 14508

# Loop over files and extract result of interest
for i in range(0,len(file_list)):
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
  signal_yield_pull_widths[i] = ufloat(pars_yield_pull_widths[1].getVal(), pars_yield_pull_widths[1].getError())
  signal_yield_pull_widths[i] = ufloat(pars_yield[0].getVal(), pars_yield_err[0].getVal())

  # 2D array with row element eff_tree[0] - orEff = first column, boxEff = second
  eff_tree = r_np.root2array(file_list[i], "tree", branch_names)
  # Error on boxEff and orEff are binomial = 1/N(sqrt(Np(1-p))) = 1/N_mcsqrt(N_mc*eff(1-eff))
  or_eff[i] = ufloat(eff_tree[0][0], math.sqrt(n_mc_events*eff_tree[0][0]*(1-eff_tree[0][0]))/n_mc_events)
  box_eff[i] = ufloat(eff_tree[0][1], math.sqrt(n_mc_events*eff_tree[0][1]*(1-eff_tree[0][1]))/n_mc_events)

print(signal_yield_pull_widths)
print(signal_yield)
print(box_eff)
print(or_eff)
# shared_yield = np.divide(np.multiply(signal_yield[0], box_eff), or_eff)

# Combine with error on total yield (uncertainties package)
# Overlay with function for error correction, with same x axis, multiplied by starting pull width (as < 1)
# Propagate uncertainties with uncertainties package

# fig = plt.figure()
# plt.errorbar(shared_yield, signal_yield_pull_widths[0], yerr=signal_yield_pull_widths[1])
# plt.title('Total Signal Yield')
# plt.xlabel('Number of Double-Counted Events')
# plt.ylabel('Pull Width')
# plt.show()


# total_yield = 40000
# x = shared yield
# x = np.arange(0, total_yield, 2000)
# xerr = np.sqrt(x)
# y = error correction (corrected error / fit error)
# y = pull width of total signal yield
# y = x*(math.sqrt(2)/total_yield) + (total_yield - x)/total_yield
# Overlay with function:
# f(x) = x*(math.sqrt(2)/total_yield) + (total_yield - x)/total_yield
# Propagate uncertainties

# plt.errorbar(x, y, xerr=xerr)
# Double events in box yield or single?
# plt.xlabel('Box yield')
# plt.ylabel('Pull width')
# plt.show()

