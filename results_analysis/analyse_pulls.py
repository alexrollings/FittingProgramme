import math, re, os, sys, glob
from ROOT import TFile, RooFitResult, RooGaussian, RooDataSet, TObject
import root_numpy as r_np
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from matplotlib import rc
from scipy import stats
from uncertainties import unumpy, ufloat
from uncertainties.umath import *
import argparse
from useful_functions import return_label

if __name__ == '__main__':
  # May need to comment out bu delta_partial stuff (for older box scans)
  parser = argparse.ArgumentParser()
  parser.add_argument('-i',
                      '--input_dir',
                      type=str,
                      help='Input: path to toy results',
                      required=True)
  parser.add_argument(
      '-p',
      '--param',
      type=str,
      help=
      'Parameter to analyse pulls from (sig = N_Bu2Dst0h_D0pi0_pi0_pi_total/N_Bu2Dst0h_D0gamma_gamma_pi_total/N_Bu2Dst0h_D0pi0_gamma_pi_total)',
      required=False)
  parser.add_argument('-v',
                      '--var',
                      type=str,
                      help='Box scan variable: delta/buDelta',
                      required=True)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral',
                      required=True)
  parser.add_argument('-b',
                      '--box_fit',
                      type=str,
                      help='String of box dimensions used in fit',
                      required=False)
  args = parser.parse_args()

  input_dir = args.input_dir
  param = args.param
  var = args.var
  neutral = args.neutral
  box_fit = args.box_fit

  file_list = []

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/'
  if neutral != 'pi0' and neutral != 'gamma' and neutral != 'partial':
    sys.exit('Specify neutral: -n=pi0,gamma,partial')
  else:
    lines = [
        l.rstrip('\n') for l in open(home_path + 'shell_scripts/box_effs/' +
                                     neutral + '_' + var + '_box_limits_new.txt')
    ]
  lines = [l.split(':') for l in lines]
  box_limits = []
  for _, box in lines:
    box_limits.append(box)
  split = [l.split(' ') for l in box_limits]
  for box in split:
    bu_low = box[0]
    bu_high = box[1]
    if neutral == 'partial':
      delta_partial_low = box[2]
      delta_partial_high = box[3]
      delta_low = '125'
      delta_high = '170'
    else:
      delta_low = box[2]
      delta_high = box[3]
      delta_partial_low = '60'
      delta_partial_high = '105'
    if neutral == 'pi0':
      box_string = delta_low + '_' + delta_high + '_' + bu_low + '_' + bu_high
    else:
      box_string = delta_partial_low + '_' + delta_partial_high + '_' + delta_low + '_' + delta_high + '_' + bu_low + '_' + bu_high

    # Loop over files in directory and append to list those that match regex
    if os.path.isdir(input_dir):
      for filename in os.listdir(input_dir):
        m = re.search(
            'Result_' + box_string + '.root', filename)
        if m:
          file_list.append(filename)

  if len(file_list) == 0:
    sys.exit('No files recognised')

  os.chdir(input_dir)

  if neutral == 'pi0':
    # mode = 'Bu2Dst0pi_D0pi0'
    sig_decay = 'Bu2Dst0h_D0pi0_pi0_pi_kpi'
  elif neutral == 'partial':
    # mode = 'Bu2Dst0pi_D0pi0'
    sig_decay = 'Bu2Dst0h_D0pi0_gamma_pi_kpi'
  else:
    # mode = 'Bu2Dst0pi_D0gamma'
    sig_decay = 'Bu2Dst0h_D0gamma_gamma_pi_kpi'

  # Name of branches in tree (box and or effs)
  if neutral == 'pi0':
    branch_names = [
        'orEff_Bu2Dst0pi_D0pi0', 'orEffErr_Bu2Dst0pi_D0pi0',
        'boxEff_Bu2Dst0pi_D0pi0', 'boxEffErr_Bu2Dst0pi_D0pi0'
    ]
  else:
    branch_names = [
        'orEff_Bu2Dst0pi_D0pi0', 'orEffErr_Bu2Dst0pi_D0pi0',
        'boxEff_Bu2Dst0pi_D0pi0', 'boxEffErr_Bu2Dst0pi_D0pi0',
        'boxPartialEff_Bu2Dst0pi_D0pi0', 'boxPartialEffErr_Bu2Dst0pi_D0pi0'
    ]

  observables = [
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kpi',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kk',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_pipi',
      'R_CP_Bu2Dst0h_D0pi0_Blind_pi0_kk',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_pi0_kpi',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_pi_kpi',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_k_kpi',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_pi_kk',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_k_kk',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_total',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_total'
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_minus',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_minus',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_plus',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_plus',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kpi',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kk',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_pipi',
      'R_CP_Bu2Dst0h_D0pi0_Blind_gamma_kk',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_gamma_kpi',
      'A_Bu2Dst0h_D0pi0_Blind_gamma_pi_kpi',
      'A_Bu2Dst0h_D0pi0_Blind_gamma_k_kpi',
      'A_Bu2Dst0h_D0pi0_Blind_gamma_pi_kk',
      'A_Bu2Dst0h_D0pi0_Blind_gamma_k_kk',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_total',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_total',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_minus',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_minus'
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_plus',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_plus',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kpi',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kk',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_pipi',
      'R_CP_Bu2Dst0h_D0pi0_Blind_pi0_kk',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_pi0_kpi',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_pi_kpi',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_k_kpi',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_pi_kk',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_k_kk',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_total',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_total',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_minus',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_minus',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_plus',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_plus'
  ]
  if param is not None:
    observables = [param]

  for obs in observables:

    # Array to store parameter pull widths and error on width
    par_pull_widths_arr = []
    # Array to store mean parameter value and std dev
    par_val_arr = []
    # Array to store mean parameter error and std dev
    par_err_arr = []
    # Array to store mean total signal yield and error
    signal_yield_arr = []

    # Array to store efficiencies in
    box_eff = []
    or_eff = []

    i = 0
    # Loop over files and extract result of interest
    for f in file_list:
      # print(f)
      tf = TFile(f)
      # Ib result, params are stored in order mean [0], std dev [1]
      result_par_pull_widths = tf.Get('Result_Pull_' + obs)
      if isinstance(result_par_pull_widths, RooFitResult):
        result_par_val = tf.Get('Result_Val_' + obs)
        result_par_err = tf.Get('Result_Err_' + obs)
        # result_signal_yield = tf.Get('Result_Val_N_Bu2Dst0h_D0gamma_gamma_pi')
        # result_signal_yield_err = tf.Get('Result_Err_N_Bu2Dst0h_D0gamma_gamma_pi')
        result_signal_yield = tf.Get('Result_Val_N_tot_' + sig_decay)
        result_signal_yield_err = tf.Get('Result_Err_N_tot_' +
                                         sig_decay)
        # Final values of fit to pulls
        par_pull_widths = result_par_pull_widths.floatParsFinal()
        par_val = result_par_val.floatParsFinal()
        par_err = result_par_err.floatParsFinal()
        signal_yield = result_signal_yield.floatParsFinal()
        signal_yield_err = result_signal_yield_err.floatParsFinal()
        # Save value and error of width for each box dimn
        if i == 0:
          initial_width = ufloat(par_pull_widths[1].getVal(),
                                 par_pull_widths[1].getError())
        par_pull_widths_arr.append(
            ufloat(par_pull_widths[1].getVal(), par_pull_widths[1].getError()))
        par_val_arr.append(ufloat(par_val[0].getVal(), par_err[0].getVal()))
        par_err_arr.append(ufloat(par_err[0].getVal(), par_err[1].getVal()))
        signal_yield_arr.append(
            ufloat(signal_yield[0].getVal(), signal_yield_err[0].getVal()))

        # 2D array with row element eff_tree[0] - orEff = first column, boxEff = second
        eff_tree = r_np.root2array(f, 'tree', branch_names)
        # Error on boxEff and orEff are binomial = 1/N(sqrt(Np(1-p))) = 1/N_mcsqrt(N_mc*eff(1-eff))
        if neutral == 'partial':
          or_eff.append(
              ufloat(
                  eff_tree[0][0], eff_tree[0][1]))
          box_eff.append(
              ufloat(
                  eff_tree[0][4], eff_tree[0][5]))
        else:
          or_eff.append(
              ufloat(
                  eff_tree[0][0], eff_tree[0][1]))
          box_eff.append(
              ufloat(
                  eff_tree[0][2], eff_tree[0][3]))

        if box_fit != None:
          m = re.search(
              'Result_' + box_fit + '.root', f)
          if m:
            if neutral == 'partial':
              fit_box_eff = eff_tree[0][4]
            else:
              fit_box_eff = eff_tree[0][2]

        i = i + 1
      else:
        print(f'Skipping {obs} as not contained in {f}')
        continue

    if len(par_pull_widths_arr) == 0:
      sys.exit('No parameters found')

    shared_yield = np.array(np.divide(
        np.multiply(signal_yield_arr[0], box_eff), or_eff),
                            dtype=object)
    frac_shared_yield = np.divide(shared_yield, signal_yield_arr)

    # for i in range(0, len(file_list)):
    #   print(file_list[i] + ' ' + str(box_eff[i]) + ' ' + str(or_eff[i]) + ' ' + str(frac_shared_yield[i]))

    linear_err_fn = (np.multiply(
        np.divide(np.ones(len(file_list)) * math.sqrt(2), signal_yield_arr),
        shared_yield) + np.divide((signal_yield_arr - shared_yield),
                                  signal_yield_arr)) * initial_width
    # sqrt from unumpy as can handle uncertainty types
    quadratic_err_fn = unumpy.sqrt(
        np.square(
            np.multiply(
                np.divide(
                    np.ones(len(file_list)) *
                    math.sqrt(2), signal_yield_arr), shared_yield)) + np.
        square(np.divide((signal_yield_arr -
                          shared_yield), signal_yield_arr))) * initial_width

    perc_err_arr = np.divide(par_err_arr, par_val_arr)*100

    # par_pull_widths_arr = np.divide(par_pull_widths_arr, np.ones(len(file_list))*initial_width)
    fig = plt.figure()
    # plt.errorbar(
    #     unumpy.nominal_values(frac_shared_yield),
    #     unumpy.nominal_values(quadratic_err_fn),
    #     xerr=unumpy.std_devs(frac_shared_yield),
    #     yerr=unumpy.std_devs(quadratic_err_fn),
    #     label=
    #     '$\\frac{\sigma_{N_{T}}}{\sigma_{fit}}=\sqrt{(\\frac{N_{Box}\sqrt{2}}{N_{T}})^{2}+(\\frac{N_{T}-N_{Box}}{N_{T}})^{2}}$'
    # )
    # plt.errorbar(
    #     unumpy.nominal_values(frac_shared_yield),
    #     unumpy.nominal_values(linear_err_fn),
    #     xerr=unumpy.std_devs(frac_shared_yield),
    #     yerr=unumpy.std_devs(linear_err_fn),
    #     label=
    #     '$\\frac{\sigma_{N_{T}}}{\sigma_{fit}}=\\frac{N_{Box}\sqrt{2}}{N_{T}}+\\frac{N_{T}-N_{Box}}{N_{T}}$'
    # )
    plt.errorbar(unumpy.nominal_values(box_eff),
                 # unumpy.nominal_values(frac_shared_yield),
                 unumpy.nominal_values(par_pull_widths_arr),
                 xerr=unumpy.std_devs(box_eff),
                 # xerr=unumpy.std_devs(frac_shared_yield),
                 yerr=unumpy.std_devs(par_pull_widths_arr),
                 color='black', ecolor='lightgray',
                 label='Pseudo-experiments')
    if box_fit != None:
      plt.axvline(x=fit_box_eff, color='r', linestyle='dotted')
    # plt.legend(loc='upper left')
    plt.xlabel('$\epsilon_{Box}$')
    # plt.xlabel('$N_{Box}/N_{T}$')
    plt.ylim(1.0, 1.4)
    plt.ylabel('Pull Width')
    plt.title(return_label(obs))
    fig.savefig(
        '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/box_scans/box_yield_vs_'
        + obs + '_pull_width_' + neutral + '_' + var + '.pdf')
    # print(frac_shared_yield)
    fig = plt.figure()
    plt.errorbar(
        unumpy.nominal_values(box_eff),
        # unumpy.nominal_values(frac_shared_yield),
        unumpy.nominal_values(perc_err_arr),
        xerr=unumpy.std_devs(box_eff),
        # xerr=unumpy.std_devs(frac_shared_yield),
        yerr=unumpy.std_devs(perc_err_arr),
        color='black',
        ecolor='lightgray',
        label='Pseudo-experiments')
    # plt.xlabel('$N_{Box}/N_{T}$')
    if box_fit != None:
      plt.axvline(x=fit_box_eff, color='r', linestyle='dotted')
    plt.xlabel('$\epsilon_{Box}$')
    plt.ylabel('% Error')
    plt.title(return_label(obs))
    fig.savefig(
        '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/box_scans/box_yield_vs_'
        + obs + '_err_' + neutral + '_' + var + '.pdf')
