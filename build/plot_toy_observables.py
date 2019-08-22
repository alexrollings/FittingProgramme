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
    parser.add_argument(
        '-dl',
        '--delta_low',
        type=str,
        help='Lower delta mass range',
        required=True)
    parser.add_argument(
        '-dh',
        '--delta_high',
        type=str,
        help='Upper delta mass range',
        required=True)
    parser.add_argument(
        '-bl',
        '--bu_low',
        type=str,
        help='Lower bu mass range',
        required=True)
    args = parser.parse_args()

    path = args.path
    delta_low = args.delta_low
    delta_high = args.delta_high
    bu_low = args.bu_low

    file_list = []
    bu_high = []

    # Loop over files in directory and append to list those that match regex
    if os.path.isdir(path):
        for filename in os.listdir(path):
            m = re.search("DataResult_" + delta_low + "_" +
                          delta_high + "_" + bu_low + "_([0-9]+).root", filename)
            if m:
                # Save upper bu dimn for each result
                bu_high.append(m.group(1))

    # Want to plot in ascending order
    bu_high.sort()
    file_list.sort()
    os.chdir(path)

    box_dims = []
    for b in bu_high:
      box_dims.append(delta_low + "_" + delta_high + "_" + bu_low + "_" + b)

    # List of params we want
    variables = ["N_Bu2Dst0h_D0gamma_gamma_pi_0",
                 "N_Bu2Dst0h_D0gamma_gamma_k_0"]
    # Dict to add the values and errors of the observables into
    obs = {}

    branch_names = ['orEffSignal_gamma', 'boxEffSignal_gamma']
    n_mc_events = 14508

    for dim in box_dims:
        tf = TFile("DataResult_" + dim + ".root")
        result = tf.Get("fitresult_simPdf_0_fullDataHist")
        if result == None:
            sys.exit("Could not extract result from DataResult_" + dim + ".root")

        eff_tree = r_np.root2array(filename, "tree", branch_names)
        # Efficiencies stoted in uncertainties array with binomial error
        or_eff = ufloat(eff_tree[0][0], math.sqrt(
            n_mc_events*eff_tree[0][0]*(1-eff_tree[0][0]))/n_mc_events)
        box_eff = ufloat(eff_tree[0][1], math.sqrt(
            n_mc_events*eff_tree[0][1]*(1-eff_tree[0][1]))/n_mc_events)

        # Floating fit parameters
        pars = result.floatParsFinal()
        for i in range(0, len(pars)):
            p = pars[i]
            p_name = p.GetName()
            if(p_name in variables):
                # In python, tuples () are immutable - can't change value: convert to tuple after calculating corrected error
                obs[dim + "_" + p_name] = [p.getVal(), p.getError()]

        yield_tot_pi = ufloat(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0"]
                              [0], obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0"][1])
        yield_box_pi = np.divide(np.multiply(
            yield_tot_pi, box_eff), or_eff)
        obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0"][1] = ((unumpy.nominal_values(yield_box_pi)/unumpy.nominal_values(yield_tot_pi)*math.sqrt(
            2))+(1-unumpy.nominal_values(yield_tot_pi)/unumpy.nominal_values(yield_box_pi)))*unumpy.std_devs(yield_tot_pi)

        yield_tot_k = ufloat(obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0"]
                             [0], obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0"][1])
        yield_box_k = np.divide(np.multiply(
            yield_tot_k, box_eff), or_eff)
        obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0"][1] = ((unumpy.nominal_values(yield_box_k)/unumpy.nominal_values(yield_tot_k)*math.sqrt(
            2))+(1-unumpy.nominal_values(yield_tot_k)/unumpy.nominal_values(yield_box_k)))*unumpy.std_devs(yield_tot_k)

        #Fill correlation matrix - double counting doesn't effect this
        corr = np.ones((len(variables),len(variables)))
        for a in range(0,len(variables)):
          for b in range(0,len(variables)):
            corr[a,b] = result.correlation(variables[a],variables[b])

    # Returns numbers with the correct uncertainties and correlations, given the covariance matric
        (obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_corr"], obs[dim +
        "_N_Bu2Dst0h_D0gamma_gamma_k_0_corr"]) = u.correlated_values_norm([obs[dim +
        "_N_Bu2Dst0h_D0gamma_gamma_pi_0"], obs[dim +
        "_N_Bu2Dst0h_D0gamma_gamma_k_0"]], corr)

        # Ratio D*K/D*π
        obs[dim + "_ratioKpi_Bu2Dst0h_D0gamma_gamma"] = obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_k_0_corr"] / obs[dim + "_N_Bu2Dst0h_D0gamma_gamma_pi_0_corr"]

        # Box yields and fraction of yield in box w.r.t. total yield
        obs[dim + "_N_box_Bu2Dst0h_D0gamma_gamma_pi_0"] = yield_box_pi
        obs[dim + "_N_frac_box_Bu2Dst0h_D0gamma_gamma_pi_0"] = obs[dim +
        "_N_box_Bu2Dst0h_D0gamma_gamma_pi_0"] / obs[dim +
        "_N_Bu2Dst0h_D0gamma_gamma_pi_0_corr"]
        obs[dim + "_N_box_Bu2Dst0h_D0gamma_gamma_k_0"] = yield_box_k
        obs[dim + "_N_frac_box_Bu2Dst0h_D0gamma_gamma_k_0"] = obs[dim +
        "_N_box_Bu2Dst0h_D0gamma_gamma_k_0"] / obs[dim +
        "_N_Bu2Dst0h_D0gamma_gamma_k_0_corr"]

    print(obs)

    # fig = plt.figure()
    # plt.errorbar(unumpy.nominal_values(frac_shared_yield), unumpy.nominal_values(ideal_perc_err_fn), xerr=unumpy.std_devs(frac_shared_yield), yerr=unumpy.std_devs(ideal_perc_err_fn), label='Stat Error')
    # plt.errorbar(unumpy.nominal_values(frac_shared_yield), unumpy.nominal_values(corrected_perc_err), xerr=unumpy.std_devs(frac_shared_yield), yerr=unumpy.std_devs(corrected_perc_err), label='Corrected Error')
    # # plt.errorbar(unumpy.nominal_values(frac_shared_yield), corrected_perc_err_fn, xerr=unumpy.std_devs(frac_shared_yield), label='Corrected Error Convolution')
    # plt.errorbar(unumpy.nominal_values(frac_shared_yield), unumpy.nominal_values(signal_yield_perc_err), xerr=unumpy.std_devs(frac_shared_yield), yerr=unumpy.std_devs(signal_yield_perc_err), label='Pseudo-experiments')
    # plt.legend(loc='best')
    # plt.xlabel('$N_{Box}/N_{T}$')
    # plt.ylabel('$\%$ Error')
    # plt.title('$N_{D^{*}\pi^{\\pm}}$')
    # fig.savefig("box_yield_vs_signal_yield_err.pdf")
    #


