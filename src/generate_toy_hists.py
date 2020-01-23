import os, sys
os.environ[
    "ROOT_INCLUDE_PATH"] = os.pathsep + "/home/rollings/MeerkatHEPForge/Meerkat/inc/"

from ROOT import gSystem, gStyle, TChain, TH2F, TH1F, TCanvas, TFile

gSystem.Load("/home/rollings/MeerkatHEPForge/Meerkat/lib/libMeerkat.so")

from ROOT import OneDimPhaseSpace, CombinedPhaseSpace, BinnedKernelDensity

import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from uncertainties import unumpy, ufloat

variables = [
    'Bu_Delta_M', 'Delta_M', 'BDT1', 'BDT2', 'D0h_M', 'D0_FD_ZSIG', 'Pi0_M',
    'bach_PIDK', 'h1_D_PIDK', 'h2_D_PIDK'
]

bu_mass = 'Bu_Delta_M'
delta_mass = 'Delta_M'

tree = TChain("BtoDstar0h3_h1h2pi0RTuple")
years = ['2011']
# years = ['2011', '2012', '2015', '2016', '2017', '2018']
polarities = ['Up', 'Down']
for y in years:
  for p in polarities:
    tree.Add('/data/lhcb/users/rollings/Bu2Dst0h_data_new_2/' + y + '_Mag' +
             p + '/pi0/tmva_stage1/tmva_stage2_loose/to_fit/' + y + '_Mag' +
             p + '_Bu2Dst0pi_Dst02D0pi0_D02kpi_BDT1_BDT2_MERemoved.root')

tree.SetBranchStatus("*", 0)

for var in variables:
  tree.SetBranchStatus(var, 1)

bu_low = 5050.
bu_high = 5550.
bu_nbins = 45.0
# Kernel width ~ twice bin width
bu_kwidth = 2.*float((bu_high - bu_low)/bu_nbins)
delta_low = 136.
delta_high = 190.
delta_nbins = 54.0
delta_kwidth = 0.5
delta_kwidth = 2.*float((delta_high - delta_low)/delta_nbins)


data_hist = TH2F("data", "Histogram storing data",
                                           int(bu_nbins), bu_low, bu_high,
                                           int(delta_nbins), delta_low, delta_high)

for i in range(0, tree.GetEntries()):
  tree.GetEntry(i)
  m_bu = getattr(tree, bu_mass)
  m_delta = getattr(tree, delta_mass)
  if m_bu > bu_low and m_bu < bu_high and m_delta > delta_low and m_delta < bu_high:
    data_hist.Fill(m_bu, m_delta)

# Define 1D phase spaces for each of the two variables
phsp_bu = OneDimPhaseSpace("phsp_bu", bu_low, bu_high)
phsp_delta = OneDimPhaseSpace("phsp_delta", delta_low, delta_high)

# Define combined phase space for the two variables (AKA direct product)
phsp = CombinedPhaseSpace("phsp", phsp_bu, phsp_delta)

kde = BinnedKernelDensity("KernelPDF",
                        phsp,                     # Phase space
                        tree,                     # Input ntuple
                        bu_mass, delta_mass,      # Variables to use
                        int(bu_nbins), int(delta_nbins),    # Number of bins
                        bu_kwidth, delta_kwidth,  # Kernel widths
                        0,                        # Approximation PDF (0 for flat approximation)
                        100000                    # Sample size for MC convolution (0 for binned convolution)
                       )

# That's it. Now fill some histograms and show the results.
kernel_hist = TH2F("kernel", "Kernel PDF with flat approximation",
                                           int(bu_nbins), bu_low, bu_high,
                                           int(delta_nbins), delta_low, delta_high)
# Fill histogram with the result of kernel density estimation
kde.project(kernel_hist)
kernel_hist.Sumw2()
# kernel_hist.Write()

# Project to get 1D distributions; first bin = 0, last = -1
kernel_hist_bu = kernel_hist.ProjectionX("kernel_bu", 0, -1)
kernel_hist_delta = kernel_hist.ProjectionY("kernel_delta", 0, -1)
data_hist_bu = data_hist.ProjectionX("data_bu", 0, -1)
data_hist_delta = data_hist.ProjectionY("data_delta", 0, -1)

gStyle.SetOptStat(0)

bu_label = "$m_{B} - m_{D^*} + m_{D^*}^{PDG} \left[MeV/c^2\\right]$"
delta_label = "$m_{D^*} - m_{D} - m_{\pi^{0}} + m_{\pi^{0}}^{PDG} \left[MeV/c^2\\right]$"

bu_xaxis = np.linspace(bu_low, bu_high, bu_nbins)
kernel_vec_bu = []
data_vec_bu = []
for b in range(0, int(bu_nbins)):
  kernel_vec_bu.append(
      ufloat(kernel_hist_bu.GetBinContent(b), kernel_hist_bu.GetBinError(b)))
  data_vec_bu.append(
      ufloat(data_hist_bu.GetBinContent(b), data_hist_bu.GetBinError(b)))

kernel_vec_bu = np.divide(kernel_vec_bu,
                          kernel_hist_bu.GetEntries() * np.ones(int(bu_nbins)))
data_vec_bu = np.divide(data_vec_bu,
                        data_hist_bu.GetEntries() * np.ones(int(bu_nbins)))

fig = plt.plot()
plt.errorbar(bu_xaxis, unumpy.nominal_values(kernel_vec_bu),
             yerr=unumpy.std_devs(kernel_vec_bu),
             label='KDE')
plt.errorbar(bu_xaxis, unumpy.nominal_values(data_vec_bu),
             yerr=unumpy.std_devs(data_vec_bu),
             label='Data')
plt.xlim(bu_low, bu_high)
plt.ylim(bottom = 0.0)
plt.xlabel(bu_label)
plt.savefig('kde_plots/BuMass.png')
plt.clf()

delta_xaxis = np.linspace(delta_low, delta_high, delta_nbins)
kernel_vec_delta = []
data_vec_delta = []
for b in range(0, int(delta_nbins)):
  kernel_vec_delta.append(
      ufloat(kernel_hist_delta.GetBinContent(b), kernel_hist_delta.GetBinError(b)))
  data_vec_delta.append(
      ufloat(data_hist_delta.GetBinContent(b), data_hist_delta.GetBinError(b)))

kernel_vec_delta = np.divide(kernel_vec_delta,
                          kernel_hist_delta.GetEntries() * np.ones(int(delta_nbins)))
data_vec_delta = np.divide(data_vec_delta,
                        data_hist_delta.GetEntries() * np.ones(int(delta_nbins)))

fig = plt.plot()
plt.errorbar(delta_xaxis, unumpy.nominal_values(kernel_vec_delta),
             yerr=unumpy.std_devs(kernel_vec_delta),
             label='KDE')
plt.errorbar(delta_xaxis, unumpy.nominal_values(data_vec_delta),
             yerr=unumpy.std_devs(data_vec_delta),
             label='Data')
plt.xlim(delta_low, delta_high)
plt.ylim(bottom = 0.0)
plt.xlabel(delta_label)
plt.savefig('kde_plots/DeltaMass.png')
plt.clf()

fig = plt.plot()
plt.hist(unumpy.nominal_values(kernel_vec_bu),
         int(bu_nbins),
         range=(bu_low, bu_high),
         density=True,
         histtype='step', linestyle='dashed',
         label='KDE')
plt.hist(unumpy.nominal_values(data_vec_bu),
         int(bu_nbins),
         range=(bu_low, bu_high),
         density=True,
         histtype='step', linestyle='dashed',
         label='Data')
plt.xlim(bu_low, bu_high)
plt.ylim(bottom = 0.0)
plt.xlabel(bu_label)
plt.savefig('kde_plots/BuMassHist.png')
plt.clf()

# fig = plt.plot()
# plt.hist(unumpy.nominal_values(kernel_vec_delta),
#          int(delta_nbins),
#          range=(delta_low, delta_high),
#          density=True,
#          histtype='step', linestyle='dashed',
#          label='KDE')
# plt.hist(unumpy.nominal_values(data_vec_delta),
#          int(delta_nbins),
#          range=(delta_low, delta_high),
#          density=True,
#          histtype='step', linestyle='dashed',
#          label='Data')
# plt.xlim(delta_low, delta_high)
# plt.ylim(bottom = 0.0)
# plt.xlabel(delta_label)
# plt.savefig('kde_plots/DeltaMassHist.png')
# plt.clf()

# canvas = TCanvas("canvas", "Kernel canvas", 1000, 500)
# canvas.Divide(2,1)
# canvas.cd(1)
# kernel_hist.SetTitle(" ")
# kernel_hist.SetXTitle(bu_label)
# kernel_hist.SetYTitle(delta_label)
# kernel_hist.Draw("zcol")
# canvas.cd(2)
# data_hist.SetTitle(" ")
# data_hist.SetXTitle(bu_label)
# data_hist.SetYTitle(delta_label)
# data_hist.Draw("zcol")
# canvas.Print("kde_plots/2DPlots.png")
