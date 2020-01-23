import os, sys
os.environ[
    "ROOT_INCLUDE_PATH"] = os.pathsep + "/home/rollings/MeerkatHEPForge/Meerkat/inc/"

from ROOT import gSystem, gStyle, TChain, TTree, TH2F, TH1F, TCanvas, TFile

gSystem.Load("/home/rollings/MeerkatHEPForge/Meerkat/lib/libMeerkat.so")

from ROOT import OneDimPhaseSpace, CombinedPhaseSpace, BinnedKernelDensity

import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from uncertainties import unumpy, ufloat
import argparse

if __name__ == "__main__":
  # May need to comment out bu delta_partial stuff (for older box scans)
  parser = argparse.ArgumentParser()
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral',
                      required=True)
  parser.add_argument('-b',
                      '--bachelor',
                      type=str,
                      help='Bachelor',
                      required=True)
  parser.add_argument('-d',
                      '--daughters',
                      type=str,
                      help='Daughters',
                      required=True)
  args = parser.parse_args()
  neutral = args.neutral
  bachelor = args.bachelor
  daughters = args.daughters

  if neutral != 'pi0' and neutral != 'gamma':
    sys.exit('-n=pi0/gamma')
  if bachelor != 'pi' and bachelor != 'K':
    sys.exit('-b=pi/K')
  if daughters != 'kpi' and daughters != 'kk' and daughters != 'pipi':
    sys.exit('-d=kpi/kk/pipi')

  variables = [
      'Bu_Delta_M', 'Delta_M', 'BDT1', 'BDT2', 'D0h_M', 'D0_FD_ZSIG', 'Pi0_M',
      'bach_PIDK', 'h1_D_PIDK', 'h2_D_PIDK'
  ]

  bu_mass = 'Bu_Delta_M'
  delta_mass = 'Delta_M'

  tree = TChain("BtoDstar0h3_h1h2pi0RTuple")
  years = ['2011', '2012', '2015', '2016', '2017', '2018']
  polarities = ['Up', 'Down']
  for y in years:
    for p in polarities:
      tree.Add('/data/lhcb/users/rollings/Bu2Dst0h_data_new_2/' + y + '_Mag' +
               p + '/' + neutral + '/tmva_stage1/tmva_stage2_loose/to_fit/' +
               y + '_Mag' + p + '_Bu2Dst0' + bachelor + '_Dst02D0' + neutral +
               '_D02' + daughters + '_BDT1_BDT2_MERemoved.root')

  tree.SetBranchStatus("*", 0)

  for var in variables:
    tree.SetBranchStatus(var, 1)

  bu_low = 5050.
  bu_high = 5550.
  bu_nbins = 45.0
  # Kernel width ~ twice bin width
  bu_kwidth = 1. * float((bu_high - bu_low) / bu_nbins)
  delta_low = 136.
  delta_high = 190.
  delta_nbins = 54.0
  delta_kwidth = 0.5
  delta_kwidth = 1. * float((delta_high - delta_low) / delta_nbins)

  data_hist = TH2F("data", "Histogram storing data", int(bu_nbins), bu_low,
                   bu_high, int(delta_nbins), delta_low, delta_high)

  tree_file = TFile('tree_file.root', 'recreate')
  new_tree = tree.CloneTree(0)
  new_tree.GetEntry(0)

  for i in range(0, tree.GetEntries()):
    tree.GetEntry(i)
    m_bu = getattr(tree, bu_mass)
    m_delta = getattr(tree, delta_mass)
    bdt1 = getattr(tree, 'BDT1')
    bdt2 = getattr(tree, 'BDT2')
    fd_zsig = getattr(tree, 'D0_FD_ZSIG')
    m_dh = getattr(tree, 'D0h_M')
    m_pi0 = getattr(tree, 'Pi0_M')
    if m_bu > bu_low and m_bu < bu_high and m_delta > delta_low and m_delta < bu_high:
      if bdt1 > 0.05 and bdt2 > 0.05 and m_dh > 4900 and m_dh < 5200 and fd_zsig > 2:
        if neutral == 'gamma':
          data_hist.Fill(m_bu, m_delta)
          new_tree.Fill()
        elif m_pi0 < 165 and m_pi0 > 125:
          data_hist.Fill(m_bu, m_delta)
          new_tree.Fill()

# Define 1D phase spaces for each of the two variables
  phsp_bu = OneDimPhaseSpace("phsp_bu", bu_low, bu_high)
  phsp_delta = OneDimPhaseSpace("phsp_delta", delta_low, delta_high)

  # Define combined phase space for the two variables (AKA direct product)
  phsp = CombinedPhaseSpace("phsp", phsp_bu, phsp_delta)

  kde = BinnedKernelDensity(
      "KernelPDF",
      phsp,  # Phase space
      new_tree,  # Input ntuple
      bu_mass,
      delta_mass,  # Variables to use
      int(bu_nbins),
      int(delta_nbins),  # Number of bins
      bu_kwidth,
      delta_kwidth,  # Kernel widths
      0,  # Approximation PDF (0 for flat approximation)
      100000  # Sample size for MC convolution (0 for binned convolution)
  )

  # That's it. Now fill some histograms and show the results.
  kernel_hist = TH2F("kernel", "Kernel PDF with flat approximation",
                     int(bu_nbins), bu_low, bu_high, int(delta_nbins),
                     delta_low, delta_high)
  # Fill histogram with the result of kernel density estimation
  # kde.normalise() Appears not to work
  kde.project(kernel_hist)
  kernel_hist.Sumw2()
  # kernel_hist.Write()

  # Project to get 1D distributions; first bin = 0, last = -1
  hist_dict = {
      'bu': {
          'kernel': kernel_hist.ProjectionX("kernel_bu", 0, -1),
          'data': data_hist.ProjectionX("data_bu", 0, -1)
      },
      'delta': {
          'kernel': kernel_hist.ProjectionY("kernel_delta", 0, -1),
          'data': data_hist.ProjectionY("data_delta", 0, -1)
      }
  }

  label_dict = {
      'bu':
          "$m_{B} - m_{D^*} + m_{D^*}^{PDG} \left[MeV/c^2\\right]$",
      'delta':
          "$m_{D^*} - m_{D} - m_{\pi^{0}} + m_{\pi^{0}}^{PDG} \left[MeV/c^2\\right]$"
  }

  xaxis_dict = {
      'bu': np.linspace(bu_low, bu_high, bu_nbins),
      'delta': np.linspace(delta_low, delta_high, delta_nbins)
  }

  u_dict = {
      'bu': {
          'kernel': [],
          'data': []
      },
      'delta': {
          'kernel': [],
          'data': []
      }
  }
  norm_dict = {
      'bu': {
          'kernel': [],
          'data': []
      },
      'delta': {
          'kernel': [],
          'data': []
      }
  }

  limits_dict = {
      'bu': {
          'min': bu_low,
          'max': bu_high,
          'bins': int(bu_nbins)
      },
      'delta': {
          'min': delta_low,
          'max': delta_high,
          'bins': int(delta_nbins)
      }
  }

  color_dict = {'kernel': 'C1', 'data': 'C0'}

  for mass, d in u_dict.items():
    for pdf, u in d.items():
      for b in range(0, limits_dict[mass]['bins']):
        u.append(
            ufloat(hist_dict[mass][pdf].GetBinContent(b),
                   hist_dict[mass][pdf].GetBinError(b)))
      norm_dict[mass][pdf] = np.divide(
          u, hist_dict[mass][pdf].GetEntries() *
          np.ones(limits_dict[mass]['bins']))
      fig = plt.plot()
      plt.errorbar(xaxis_dict[mass],
                   unumpy.nominal_values(norm_dict[mass][pdf]),
                   yerr=unumpy.std_devs(norm_dict[mass][pdf]),
                   color=color_dict[pdf])
      plt.xlim(limits_dict[mass]['min'], limits_dict[mass]['max'])
      plt.ylim(bottom=0.0)
      plt.xlabel(label_dict[mass])
      plt.savefig('kde_plots/' + neutral + '_' + bachelor + '_' + daughters +
                  '_' + mass + '_' + pdf + '.png')
      plt.clf()
    fig = plt.plot()
    plt.errorbar(xaxis_dict[mass],
                 unumpy.nominal_values(norm_dict[mass]['kernel']),
                 yerr=unumpy.std_devs(norm_dict[mass]['kernel']),
                 color=color_dict['kernel'],
                 label='KDE')
    plt.errorbar(xaxis_dict[mass],
                 unumpy.nominal_values(norm_dict[mass]['data']),
                 yerr=unumpy.std_devs(norm_dict[mass]['data']),
                 color=color_dict['data'],
                 label='Data')
    plt.xlim(limits_dict[mass]['min'], limits_dict[mass]['max'])
    plt.ylim(bottom=0.0)
    plt.xlabel(label_dict[mass])
    plt.legend(loc='upper right')
    plt.savefig('kde_plots/' + neutral + '_' + bachelor + '_' + daughters +
                '_' + mass + '_comb.png')
    plt.clf()

gStyle.SetOptStat(0)
canvas = TCanvas("canvas", "canvas", 1200, 500)
canvas.Divide(2, 1)
canvas.cd(1)
kernel_hist.SetTitle(" ")
kernel_hist.SetXTitle(label_dict['bu'])
kernel_hist.SetYTitle(label_dict['delta'])
kernel_hist.Draw("zcol")
canvas.cd(2)
data_hist.SetTitle(" ")
data_hist.SetXTitle(label_dict['bu'])
data_hist.SetYTitle(label_dict['delta'])
data_hist.Draw("zcol")
canvas.Print('kde_plots/' + neutral + '_' + bachelor + '_' + daughters + '_' +
             '2DPlots.png')
