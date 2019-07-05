import math, re, os, sys, glob
from ROOT import TFile, RooFitResult, RooGaussian, RooDataSet
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from matplotlib import rc
from scipy import stats

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

cwd = os.getcwd()
os.chdir(path)
pars_fit = []

# Array to store pull widths and error on width
signal_yield_pull_widths = [[None]*len(file_list),[None]*len(file_list)]
print(signal_yield_pull_widths)
print(signal_yield_pull_widths[0])

# Loop over files and extract result of interest
for i in range(0,len(file_list)):
  tf = TFile(file_list[i])
  # In result, params are stored in order mean [0], std dev [1]
  result = tf.Get("Result_Pull_yieldTotSignal")
  # Final values of fit to pulls
  pars_fit = result.floatParsFinal()
  # Save value and error of width for each box dimn
  signal_yield_pull_widths[0][i] = pars_fit[1].getVal()
  signal_yield_pull_widths[1][i] = pars_fit[1].getError()

print(signal_yield_pull_widths)

fig = plt.figure()
plt.errorbar(bu_high, signal_yield_pull_widths[0], yerr=signal_yield_pull_widths[1])
# Double events in box yield or single?
plt.xlabel('Box Dimn')
plt.ylabel('Pull width')
plt.show()


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

