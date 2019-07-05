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

if os.path.isdir(path):
  for filename in os.listdir(path):
    m = re.search("Result_[0-9]+_[0-9]+_[0-9]+_([0-9]+).root", filename)
    if m:
        bu_high.append(m.group(1))
        file_list.append(filename)

cwd = os.getcwd()
os.chdir(path)
pars_fit = []

for f in file_list:
  tf = TFile(filename)
  result = tf.Get("Result_Pull_yieldTotSignal")
  pars_fit = result.floatParsFinal()
  print(pars_fit)

# fig = plt.figure()
# total_yield = 40000
# # x = shared yield
# x = np.arange(0, total_yield, 2000)
# # print(x)
# xerr = np.sqrt(x)
# # print(xerr)
# # y = error correction (corrected error / fit error)
# # y = pull width of total signal yield
# y = x*(math.sqrt(2)/total_yield) + (total_yield - x)/total_yield
# # print(y)
# # Overlay with function:
# # f(x) = x*(math.sqrt(2)/total_yield) + (total_yield - x)/total_yield
# # Propagate uncertainties
#
# plt.errorbar(x, y, xerr=xerr)
# # Double events in box yield or single?
# plt.xlabel('Box yield')
# plt.ylabel('Pull width')
# plt.show()

