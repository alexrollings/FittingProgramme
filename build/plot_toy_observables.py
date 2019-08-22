import math
import re
import os
import sys
import glob
from ROOT import TFile, RooFitResult
import root_numpy as r_np
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
from uncertainties import unumpy, ufloat
from uncertainties.umath import *
import uncertainties as u
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-p',
        '--path',
        type=str,
        help='Directory where results are stored and PDFs will be saved',
        required=True)
    parser.add_argument('-dl',
                        '--delta_low',
                        type=str,
                        help='Lower delta mass range',
                        required=True)
    parser.add_argument('-dh',
                        '--delta_high',
                        type=str,
                        help='Upper delta mass range',
                        required=True)
    parser.add_argument('-bl',
                        '--bu_low',
                        type=str,
                        help='Lower bu mass range',
                        required=True)
    args = parser.parse_args()

    path = args.path
    delta_low = args.delta_low
    delta_high = args.delta_high
    bu_low = args.bu_low

    bu_high = []

    # Loop over files in directory and append to list those that match regex
    if os.path.isdir(path):
        for root_file in os.listdir(path):
            m = re.search(
                "DataResult_" + delta_low + "_" + delta_high + "_" + bu_low +
                "_([0-9]+).root", root_file)
            if m:
                # Save upper bu dimn for each result
                bu_high.append(m.group(1))

    # Want to plot in ascending order
    bu_high.sort()
    os.chdir(path)

    box_dims = []
    for b in bu_high:
        box_dims.append(delta_low + "_" + delta_high + "_" + bu_low + "_" + b)

    # List of params we want
    variables = [
        "N_Bu2Dst0h_D0gamma_gamma_pi_0", "N_Bu2Dst0h_D0gamma_gamma_k_0"
    ]
    # Dict to add the values and errors of the observables into
    obs = {}

    branch_names = ['orEffSignal_gamma', 'boxEffSignal_gamma']
    n_mc_events = 14508

    result = {}
    eff_tree = {}
    or_eff = {}
    box_eff = {}
    corr = {key: np.ones((len(variables), len(variables))) for key in box_dims}

    for dim in box_dims:
        filename = "DataResult_" + dim + ".root"
        tf = TFile(filename)
        result[dim] = tf.Get("fitresult_simPdf_0_fullDataHist")
        if result[dim] == None:
            sys.exit("Could not extract result from " + filename)

        eff_tree[dim] = r_np.root2array(filename, "tree", branch_names)
        # Efficiencies stoted in uncertainties array with binomial error
        or_eff[dim] = ufloat(
            eff_tree[dim][0][0],
            math.sqrt(n_mc_events * eff_tree[dim][0][0] *
                      (1 - eff_tree[dim][0][0])) / n_mc_events)
        box_eff[dim] = ufloat(
            eff_tree[dim][0][1],
            math.sqrt(n_mc_events * eff_tree[dim][0][1] *
                      (1 - eff_tree[dim][0][1])) / n_mc_events)

        # Floating fit parameters
        pars = result[dim].floatParsFinal()
        for i in range(0, len(pars)):
            p = pars[i]
            p_name = p.GetName()
            if (p_name in variables):
                # In python, tuples () are immutable - can't change value: convert to tuple after calculating corrected error
                obs[dim + "_" + p_name] = (p.getVal(), p.getError())
                # Save pi and k yield in own objects s.t. later we can access
                # these values in order to make corrected error dict element
                if p_name == "N_Bu2Dst0h_D0gamma_gamma_pi_0":
                    pi_yield = p.getVal()
                elif p_name == "N_Bu2Dst0h_D0gamma_gamma_k_0":
                    k_yield = p.getVal()

        print(dim)
        print("Total yield initital = " +
              str(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0"]))

        yield_tot_pi = ufloat(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0"][0],
                              obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0"][1])

        print("Total yield extracted = " + str(yield_tot_pi))

        yield_box_pi = np.divide(np.multiply(yield_tot_pi, box_eff[dim]),
                                 or_eff[dim])

        print("Box yield = " + str(yield_box_pi))

        # Corrected error = ((N_BOX/N_T * sqrt(2)) + (1-(N_BOX/N_T))) * N_T fit error
        yield_tot_pi_err = (
            (unumpy.nominal_values(yield_box_pi) /
             unumpy.nominal_values(yield_tot_pi) * math.sqrt(2)) +
            (1 - unumpy.nominal_values(yield_box_pi) /
             unumpy.nominal_values(yield_tot_pi))
        ) * unumpy.std_devs(yield_tot_pi)
        obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_new"] = (pi_yield,
                                                           yield_tot_pi_err)

        print("Total yield finally = " +
              str(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0"]) + "\n\n")

        yield_tot_k = ufloat(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0"][0],
                             obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0"][1])
        yield_box_k = np.divide(np.multiply(yield_tot_k, box_eff[dim]),
                                or_eff[dim])

        yield_tot_k_err = (
            (unumpy.nominal_values(yield_box_k) /
             unumpy.nominal_values(yield_tot_k) * math.sqrt(2)) +
            (1 - unumpy.nominal_values(yield_box_k) /
             unumpy.nominal_values(yield_tot_k))
        ) * unumpy.std_devs(yield_tot_k)
        obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0_new"] = (k_yield,
                                                          yield_tot_k_err)

        #Fill correlation matrix - double counting doesn't effect this
        for a in range(0, len(variables)):
            for b in range(0, len(variables)):
                corr[dim][a, b] = result[dim].correlation(
                    variables[a], variables[b])

    # Returns numbers with the correct uncertainties and correlations, given the covariance matric
        (obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_corr"],
         obs[dim +
             "_N_Bu2Dst0h_D0gamma_gamma_k_0_corr"]) = u.correlated_values_norm(
                 [
                     obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0"],
                     obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0"]
                 ], corr[dim])

        (obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_new_corr"],
         obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0_new_corr"]
         ) = u.correlated_values_norm([
             obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_new"],
             obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0_new"]
         ], corr[dim])

        # Ratio D*K/D*π
        obs[dim + "_ratioKpi_Bu2Dst0h_D0gamma_gamma"] = obs[
            dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0_corr"] / obs[
                dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_corr"]
        obs[dim + "_ratioKpi_Bu2Dst0h_D0gamma_gamma_new"] = obs[
            dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0_new_corr"] / obs[
                dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_new_corr"]

        # Box yields and fraction of yield in box w.r.t. total yield
        obs[dim + "_N_box_Bu2Dst0h_D0gamma_gamma_pi_0_new"] = yield_box_pi
        obs[dim + "_N_frac_box_Bu2Dst0h_D0gamma_gamma_pi_0_new"] = obs[
            dim + "_N_box_Bu2Dst0h_D0gamma_gamma_pi_0_new"] / obs[
                dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_new_corr"]
        obs[dim + "_N_box_Bu2Dst0h_D0gamma_gamma_k_0_new"] = yield_box_k
        obs[dim + "_N_frac_box_Bu2Dst0h_D0gamma_gamma_k_0_new"] = obs[
            dim + "_N_box_Bu2Dst0h_D0gamma_gamma_k_0_new"] / obs[
                dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0_new_corr"]

    yields_pi = []
    yields_k = []
    yields_old_pi = []
    yields_old_k = []
    frac_yields_pi = []
    frac_yields_k = []
    ratio = []
    ratio_old = []

    for dim in box_dims:
        yields_old_pi.append(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_corr"])
        yields_old_k.append(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0_corr"])
        yields_pi.append(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_new_corr"])
        yields_k.append(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0_new_corr"])
        frac_yields_pi.append(
            obs[dim + "_N_frac_box_Bu2Dst0h_D0gamma_gamma_pi_0_new"])
        frac_yields_k.append(obs[dim +
                                 "_N_frac_box_Bu2Dst0h_D0gamma_gamma_k_0_new"])
        ratio.append(obs[dim + "_ratioKpi_Bu2Dst0h_D0gamma_gamma_new"])
        ratio_old.append(obs[dim + "_ratioKpi_Bu2Dst0h_D0gamma_gamma"])

    # Stat error function = sqrt( N_T / (N_BOX/N_T) +1 ): 2 when N_BOX = N_T, 1 when N_BOX = 0
    yields_pi_stat_err = unumpy.sqrt(
        np.divide(yields_pi, (frac_yields_pi + np.ones(len(box_dims)))))
    yields_pi_stat_perc_err = np.divide(yields_pi_stat_err, yields_pi) * 100
    yields_k_stat_err = unumpy.sqrt(
        np.divide(yields_k, (frac_yields_k + np.ones(len(box_dims)))))
    yields_k_stat_perc_err = np.divide(yields_k_stat_err, yields_k) * 100

    # To calculate ratio stat error, need to put in form of yields ± error again
    yields_pi_stat = unumpy.uarray(unumpy.nominal_values(yields_pi),
    unumpy.nominal_values(yields_pi_stat_err))
    yields_k_stat = unumpy.uarray(unumpy.nominal_values(yields_k),
    unumpy.nominal_values(yields_k_stat_err))
    ratio_stat = np.divide(yields_k_stat, yields_pi_stat)
    # print(ratio)
    # print(ratio_old)
    # print(ratio_stat)

    fig = plt.figure()
    plt.errorbar(unumpy.nominal_values(frac_yields_pi),
                 np.divide(unumpy.std_devs(yields_pi),
                           unumpy.nominal_values(yields_pi)) * 100,
                 xerr=unumpy.std_devs(frac_yields_pi),
                 label='Corrected error')
    plt.errorbar(unumpy.nominal_values(frac_yields_pi),
                 np.divide(unumpy.std_devs(yields_old_pi),
                           unumpy.nominal_values(yields_old_pi)) * 100,
                 xerr=unumpy.std_devs(frac_yields_pi),
                 label='Fit error')
    plt.errorbar(unumpy.nominal_values(frac_yields_pi),
                 unumpy.nominal_values(yields_pi_stat_perc_err),
                 xerr=unumpy.std_devs(frac_yields_pi),
                 yerr=unumpy.std_devs(yields_pi_stat_perc_err),
                 label='Stat Error')
    plt.legend(loc='best')
    plt.xlabel('$N_{Box}/N_{T}$')
    plt.ylabel('$\%$ Error')
    plt.title('$N_{D^{*}\pi^{\\pm}}$')
    fig.savefig("box_yields_vs_signal_yields_pi_err.pdf")

    fig = plt.figure()
    plt.errorbar(
        unumpy.nominal_values(frac_yields_k),
        np.divide(unumpy.std_devs(yields_k), unumpy.nominal_values(yields_k)) *
        100,
        xerr=unumpy.std_devs(frac_yields_k),
        label='Corrected error')
    plt.errorbar(unumpy.nominal_values(frac_yields_k),
                 np.divide(unumpy.std_devs(yields_old_k),
                           unumpy.nominal_values(yields_old_k)) * 100,
                 xerr=unumpy.std_devs(frac_yields_k),
                 label='Fit error')
    plt.errorbar(unumpy.nominal_values(frac_yields_k),
                 unumpy.nominal_values(yields_k_stat_perc_err),
                 xerr=unumpy.std_devs(frac_yields_k),
                 yerr=unumpy.std_devs(yields_k_stat_perc_err),
                 label='Stat Error')
    plt.legend(loc='best')
    plt.xlabel('$N_{Box}/N_{T}$')
    plt.ylabel('$\%$ Error')
    plt.title('$N_{D^{*}K^{\\pm}}$')
    fig.savefig("box_yields_vs_signal_yields_k_err.pdf")

    fig = plt.figure()
    plt.errorbar(unumpy.nominal_values(frac_yields_pi),
                 np.divide(unumpy.std_devs(ratio),
                           unumpy.nominal_values(ratio)) * 100,
                 xerr=unumpy.std_devs(frac_yields_pi),
                 label='Corrected error')
    plt.errorbar(unumpy.nominal_values(frac_yields_pi),
                 np.divide(unumpy.std_devs(ratio_old),
                           unumpy.nominal_values(ratio_old)) * 100,
                 xerr=unumpy.std_devs(frac_yields_pi),
                 label='Fit error')
    plt.errorbar(unumpy.nominal_values(frac_yields_pi),
                 np.divide(unumpy.std_devs(ratio_stat),
                 unumpy.nominal_values(ratio))*100,
                 xerr=unumpy.std_devs(frac_yields_pi),
                 label='Stat Error')
    plt.legend(loc='best')
    plt.xlabel('$N_{Box}/N_{T}$')
    plt.ylabel('$\%$ Error')
    plt.title('$N_{D^{*}K^{\\pm}} / N_{D^{*}\pi^{\\pm}}$')
    fig.savefig("box_yields_vs_ratio_err.pdf")
