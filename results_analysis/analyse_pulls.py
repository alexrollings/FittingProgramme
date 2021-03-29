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
  remake_parser = parser.add_mutually_exclusive_group(required=False)
  remake_parser.add_argument('--remake', dest='remake', action='store_true')
  remake_parser.add_argument('--no-remake', dest='remake', action='store_false')
  args = parser.parse_args()

  input_dir = args.input_dir
  param = args.param
  var = args.var
  neutral = args.neutral
  box_fit = args.box_fit
  if neutral == 'pi0' or neutral == 'gamma':
    parser.set_defaults(remake=True)
  elif neutral == 'partial':
    parser.set_defaults(remake=False)
  else:
    sys.exit('Specify neutral: -n=pi0,gamma,partial')
  remake = args.remake

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/'
  if neutral == 'pi0':
    txt_fname = f'{home_path}results_analysis/box_scans_new/syst_pi0.txt'
  else:
    txt_fname = f'{home_path}results_analysis/box_scans_new/syst_gamma.txt'

  if remake is True and os.path.exists(txt_fname):
    os.remove(txt_fname)

  file_list = []

  n = neutral
  if neutral == 'partial' and var == 'buDelta':
    neutral = 'gamma'
  limits_fname = home_path + 'shell_scripts/box_effs/' + neutral + '_' + var + '_box_limits_new.txt'
  lines = [
      l.rstrip('\n') for l in open(limits_fname)
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
  neutral = n

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


  if neutral == 'pi0':
    # Name of branches in tree (box and or effs)
    branch_names = [
        'orEff_Bu2Dst0pi_D0pi0', 'orEffErr_Bu2Dst0pi_D0pi0',
        'boxEff_Bu2Dst0pi_D0pi0', 'boxEffErr_Bu2Dst0pi_D0pi0',
        'buEff_Bu2Dst0pi_D0pi0', 'buEffErr_Bu2Dst0pi_D0pi0',
        'deltaEff_Bu2Dst0pi_D0pi0', 'deltaEffErr_Bu2Dst0pi_D0pi0',
    ]
    observables = [
        'R_CP_Bu2Dst0h_D0pi0_Blind',
        'R_Dst0KDst0pi_Bu2Dst0h_kpi',
        'A_Bu2Dst0h_D0pi0_pi0_pi_kpi',
        'A_Bu2Dst0h_D0pi0_pi0_k_kpi',
        'A_CP_Bu2Dst0h_D0pi0_Blind_pi',
        'A_CP_Bu2Dst0h_D0pi0_Blind_k',
        'R_piK_Bu2Dst0h_D0pi0_Blind_pi_total',
        'R_piK_Bu2Dst0h_D0pi0_Blind_pi_plus',
        'R_piK_Bu2Dst0h_D0pi0_Blind_pi_minus',
        'R_piK_Bu2Dst0h_D0pi0_Blind_k_total',
        'R_piK_Bu2Dst0h_D0pi0_Blind_k_plus',
        'R_piK_Bu2Dst0h_D0pi0_Blind_k_minus'
    ]
  else:
    branch_names = [
        'orEff_Bu2Dst0pi_D0pi0', 'orEffErr_Bu2Dst0pi_D0pi0',
        'boxEff_Bu2Dst0pi_D0pi0', 'boxEffErr_Bu2Dst0pi_D0pi0',
        'buEff_Bu2Dst0pi_D0pi0', 'buEffErr_Bu2Dst0pi_D0pi0',
        'deltaEff_Bu2Dst0pi_D0pi0', 'deltaEffErr_Bu2Dst0pi_D0pi0',
        'buPartialEff_Bu2Dst0pi_D0pi0', 'buPartialEffErr_Bu2Dst0pi_D0pi0',
        'orEff_Bu2Dst0pi_D0gamma', 'orEffErr_Bu2Dst0pi_D0gamma',
        'boxEff_Bu2Dst0pi_D0gamma', 'boxEffErr_Bu2Dst0pi_D0gamma',
        'buEff_Bu2Dst0pi_D0gamma', 'buEffErr_Bu2Dst0pi_D0gamma',
        'deltaEff_Bu2Dst0pi_D0gamma', 'deltaEffErr_Bu2Dst0pi_D0gamma',
        'buPartialEff_Bu2Dst0pi_D0gamma', 'buPartialEffErr_Bu2Dst0pi_D0gamma',
    ]
    if neutral == 'partial':
      observables = [
          'R_CP_Bu2Dst0h_D0pi0_Blind',
          'R_Dst0KDst0pi_Bu2Dst0h_kpi',
          'A_Bu2Dst0h_D0pi0_gamma_pi_kpi',
          'A_Bu2Dst0h_D0pi0_gamma_k_kpi',
          'A_CP_Bu2Dst0h_D0pi0_Blind_pi',
          'A_CP_Bu2Dst0h_D0pi0_Blind_k',
          'R_piK_Bu2Dst0h_D0pi0_Blind_pi_total',
          'R_piK_Bu2Dst0h_D0pi0_Blind_pi_plus',
          'R_piK_Bu2Dst0h_D0pi0_Blind_pi_minus',
          'R_piK_Bu2Dst0h_D0pi0_Blind_k_total',
          'R_piK_Bu2Dst0h_D0pi0_Blind_k_plus',
          'R_piK_Bu2Dst0h_D0pi0_Blind_k_minus'
          ]
    else:
      observables = [
          'R_CP_Bu2Dst0h_D0gamma_Blind',
          'R_Dst0KDst0pi_Bu2Dst0h_kpi',
          'A_Bu2Dst0h_D0gamma_gamma_pi_kpi',
          'A_Bu2Dst0h_D0gamma_gamma_k_kpi',
          'A_CP_Bu2Dst0h_D0gamma_Blind_pi',
          'A_CP_Bu2Dst0h_D0gamma_Blind_k',
          'R_piK_Bu2Dst0h_D0gamma_Blind_pi_total',
          'R_piK_Bu2Dst0h_D0gamma_Blind_pi_plus',
          'R_piK_Bu2Dst0h_D0gamma_Blind_pi_minus',
          'R_piK_Bu2Dst0h_D0gamma_Blind_k_total',
          'R_piK_Bu2Dst0h_D0gamma_Blind_k_plus',
          'R_piK_Bu2Dst0h_D0gamma_Blind_k_minus'
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
    # signal_yield_arr = []

    # Array to store efficiencies in
    box_eff = []
    or_eff = []

    # Loop over files and extract result of interest
    for f in file_list:
      # print(f)
      tf = TFile(f)
      # In result, params are stored in order mean [0], std dev [1]
      result_par_pull_widths = tf.Get('Result_Pull_' + obs)
      if isinstance(result_par_pull_widths, RooFitResult):
        result_par_val = tf.Get('Result_Val_' + obs)
        result_par_err = tf.Get('Result_Err_' + obs)
        # result_signal_yield = tf.Get('Result_Val_N_tot_' + sig_decay)
        # result_signal_yield_err = tf.Get('Result_Err_N_tot_' +
        #                                  sig_decay)
        # Final values of fit to pulls
        par_pull_widths = result_par_pull_widths.floatParsFinal()
        par_val = result_par_val.floatParsFinal()
        par_err = result_par_err.floatParsFinal()
        # signal_yield = result_signal_yield.floatParsFinal()
        # signal_yield_err = result_signal_yield_err.floatParsFinal()
        # Save value and error of width for each box dimn
        par_pull_widths_arr.append(
            ufloat(par_pull_widths[1].getVal(), par_pull_widths[1].getError()))
        par_val_arr.append(ufloat(par_val[0].getVal(), par_err[0].getVal()))
        par_err_arr.append(ufloat(par_err[0].getVal(), par_err[1].getVal()))
        # signal_yield_arr.append(
        #     ufloat(signal_yield[0].getVal(), signal_yield_err[0].getVal()))

        # 2D array with row element eff_tree[0] - orEff = first column, boxEff = second
        eff_tree = r_np.root2array(f, 'tree', branch_names)
        if neutral == 'pi0':
          or_eff.append(
              ufloat(
                  eff_tree[0][0], eff_tree[0][1]))
          box_eff.append(
              ufloat(
                  eff_tree[0][2], eff_tree[0][3]))
        elif neutral == 'gamma':
          or_eff.append(
              ufloat(
                  eff_tree[0][10], eff_tree[0][11]))
          box_eff.append(
              ufloat(
                  eff_tree[0][12], eff_tree[0][13]))
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
            fit_pull_width = par_pull_widths[1].getVal()
            if neutral == 'pi0':
              fit_box_eff = eff_tree[0][2]
            elif neutral == 'gamma':
              fit_box_eff = eff_tree[0][12]
            else:
              fit_box_eff = eff_tree[0][2]

      else:
        # print(f'Skipping {obs} as not contained in {f}')
        continue

    if len(par_pull_widths_arr) == 0:
      continue

    #Calculate systematic as RMS of pull width for 2% around WP box efficiency
    #RMS = sqrt(sum((y0-y)**2)/n)
    #Difference between with of pull at data point and fit
    pull_diff = []
    for i in range(0, len(box_eff)):
      eff = box_eff[i].nominal_value
      if abs(eff - fit_box_eff) <= 0.02:
        pull_diff.append(par_pull_widths_arr[i].nominal_value - fit_pull_width)
        # pulls_2perc.append(par_pull_widths_arr[i].nominal_value)

    # range
    # np_pulls_2perc = np.array(pulls_2perc)
    # r = np.ptp(np_pulls_2perc, axis=0)

    np_pull_diff = np.array(pull_diff)
    #Square differences
    np_pull_sqdiff = np.square(np_pull_diff)
    # print(np_pull_diff)
    # print(np_pull_sqdiff)
    #Sum squares, average and square root
    # print(np.sum(np_pull_sqdiff))
    # print(np.sum(np_pull_sqdiff)/len(np_pull_diff))
    rms = sqrt(np.sum(np_pull_sqdiff)/len(np_pull_diff))
    # print(rms)
    if os.path.exists(txt_fname):
      txt_file = open(txt_fname, 'a')
    else:
      txt_file = open(txt_fname, 'w')
    txt_file.write(f'{obs},{rms:.6g}\n')

    #Draw vertical line at 2% region on plots
    min_eff = fit_box_eff - 0.02
    max_eff = fit_box_eff + 0.02

    # shared_yield = np.array(np.divide(
    #     np.multiply(signal_yield_arr[0], box_eff), or_eff),
    #                         dtype=object)
    # frac_shared_yield = np.divide(shared_yield, signal_yield_arr)

    perc_err_arr = np.divide(par_err_arr, par_val_arr)*100

    # fig = plt.figure()
    fig, ax = plt.subplots()
    ax.tick_params(axis='both', which='major', labelsize=13)
    plt.errorbar(unumpy.nominal_values(box_eff),
                 unumpy.nominal_values(par_pull_widths_arr),
                 xerr=unumpy.std_devs(box_eff),
                 yerr=unumpy.std_devs(par_pull_widths_arr),
                 color='black', ecolor='lightgray',
                 label='Pseudo-experiments')
    if box_fit != None:
      plt.axvline(x=fit_box_eff, color='tab:red', linestyle='dotted')
      # plt.axvline(x=min_eff, color='tab:purple', linestyle='dotted')
      # plt.axvline(x=max_eff, color='tab:purple', linestyle='dotted')
    plt.xlabel('$\epsilon_{Box}$', fontsize=15)
    plt.ylim(1.0, 1.5)
    plt.ylabel('Pull $\sigma$', fontsize=15)
    plt.title(return_label(obs), fontsize=15)
    fig.savefig(
        '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/box_scans_new/'
        + neutral + '_box_yield_vs_' + obs + '_pull_width_' + var + '.png')
    plt.clf()
    plt.errorbar(unumpy.nominal_values(box_eff),
                 unumpy.nominal_values(perc_err_arr),
                 xerr=unumpy.std_devs(box_eff),
                 yerr=unumpy.std_devs(perc_err_arr),
                 color='black',
                 ecolor='lightgray',
                 label='Pseudo-experiments')
    if box_fit != None:
      plt.axvline(x=fit_box_eff, color='r', linestyle='dotted')
    plt.xlabel('$\epsilon_{Box}$', fontsize=15)
    plt.ylabel('% Error', fontsize=15)
    plt.title(return_label(obs), fontsize=15)
    fig.savefig(
        '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/box_scans_new/'
        + neutral + '_box_yield_vs_' + obs + '_err_' + var + '.png')
    plt.close()

  txt_file.close()
