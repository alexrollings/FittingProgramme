import math, re, os, sys, glob
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
    parser.add_argument('-n',
                        '--neutral',
                        type=str,
                        help='Neutral = pi0/gamma',
                        required=True)
    parser.add_argument('-f',
                        '--fit',
                        type=str,
                        help='Fit type = 1d/d1d',
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
                        required=False)
    parser.add_argument('-bh',
                        '--bu_high',
                        type=str,
                        help='Upper bu mass range',
                        required=False)
    args = parser.parse_args()

    path = args.path
    fit = args.fit
    neutral = args.neutral
    delta_low = args.delta_low
    delta_high = args.delta_high
    bu_low = args.bu_low
    bu_high = args.bu_high

    if neutral != "gamma" and neutral != "pi0":
        sys.exit("Neutral = pi0/gamma only")

    if fit == "d1d":
        if bu_low == None or bu_high == None:
            sys.exit("Must specify bu dimensions: -bl and -bh for d1d fit")

        filename = path + "/DataResult_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + ".root"

        tf = TFile(filename)
        result = tf.Get("fitresult_simPdf_0_fullDataHist")
        if result == None:
            sys.exit("Could not extract result from " + filename)
        #Floating fit parameters
        pars = result.floatParsFinal()

        branch_names = ['orEffSignal_' + neutral, 'boxEffSignal_' + neutral]
        n_mc_events = 14508
        eff_tree = r_np.root2array(filename, "tree", branch_names)
        #Efficiencies stoted in uncertainties array with binomial error
        or_eff = ufloat(
            eff_tree[0][0],
            math.sqrt(n_mc_events * eff_tree[0][0] * (1 - eff_tree[0][0])) /
            n_mc_events)
        box_eff = ufloat(
            eff_tree[0][1],
            math.sqrt(n_mc_events * eff_tree[0][1] * (1 - eff_tree[0][1])) /
            n_mc_events)

        #List of params we want, with their value and error
        #Use these to calculate all the other yields
        variables = [
            "N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0",
            "N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0"
        ]
        #Dict to add the values and errors of the observables into
        obs = {}
        #Correlation matrix
        corr = np.ones((len(variables), len(variables)))

        for i in range(0, len(pars)):
            p = pars[i]
            p_name = p.GetName()
            if (p_name in variables):
                # In python, tuples () are immutable - can't change value: convert to tuple after calculating corrected error
                obs[p_name] = [p.getVal(), p.getError()]

        yield_tot_pi = ufloat(
            obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0"][0],
            obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0"][1])
        yield_box_pi = np.divide(np.multiply(yield_tot_pi, box_eff), or_eff)
        obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0"][1] = (
            (unumpy.nominal_values(yield_box_pi) /
             unumpy.nominal_values(yield_tot_pi) * math.sqrt(2)) +
            (1 - unumpy.nominal_values(yield_tot_pi) /
             unumpy.nominal_values(yield_box_pi))
        ) * unumpy.std_devs(yield_tot_pi)

        yield_tot_k = ufloat(
            obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0"][0],
            obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0"][1])
        yield_box_k = np.divide(np.multiply(yield_tot_k, box_eff), or_eff)
        obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral +
            "_k_0"][1] = ((unumpy.nominal_values(yield_box_k) /
                           unumpy.nominal_values(yield_tot_k) * math.sqrt(2)) +
                          (1 - unumpy.nominal_values(yield_tot_k) /
                           unumpy.nominal_values(yield_box_k))
                          ) * unumpy.std_devs(yield_tot_k)

        # Convert dict values from lists to tuples to make them immutable (easier to debug)
        obs = {key: tuple(lst) for key, lst in obs.items()}

        #Fill correlation matrix - double counting doesn't effect this
        for a in range(0, len(variables)):
            for b in range(0, len(variables)):
                corr[a, b] = result.correlation(variables[a], variables[b])

        # Returns numbers with the correct uncertainties and correlations, given the covariance matric
        (obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0_corr"],
         obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral +
             "_k_0_corr"]) = u.correlated_values_norm([
                 obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0"],
                 obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0"]
             ], corr)

        #Ratio D*K/D*π
        obs["ratioKpi_Bu2Dst0h_D0" + neutral + "_" + neutral +
            ""] = obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral +
                      "_k_0_corr"] / obs["N_tot_Bu2Dst0h_D0" + neutral + "_" +
                                         neutral + "_pi_0_corr"]
        print("N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0_corr = " +
              str(obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral +
                      "_pi_0_corr"]))
        print("N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0_corr = " +
              str(obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral +
                      "_k_0_corr"]))
        print("ratioKpi_Bu2Dst0h_D0" + neutral + "_" + neutral + " = " +
              str(obs["ratioKpi_Bu2Dst0h_D0" + neutral + "_" + neutral + ""]))

        # file = open("../results/Yields_%s.tex" % years, "w")
        # file.write("\\begin{table}[t]\n")
        # file.write("\\centering\n")
        # file.write("\\begin{tabular}{l l l}\n")
        # file.write("\\hline\n")
        # file.write("Mode & Yield (full Dalitz) & Yield ($K^*(892)^\\pm$ region) \\\\ \\hline\n")
        # file.write("$N_{SS}^{D\\pipm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dpi_SS_N"],obs["n_dpi_SS_Y"]))
        # file.write("$N_{OS}^{D\\pipm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dpi_OS_N"],obs["n_dpi_OS_Y"]))
        # file.write("$N_{SS}^{D\\Kpm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dk_SS_N"],obs["n_dk_SS_Y"]))
        # file.write("$N_{OS}^{D\\Kpm}$ & "+"${:.0fL}$ & ${:.0fL}$ \\\\\n".format(obs["n_dk_OS_N"],obs["n_dk_OS_Y"]))
        # file.write("\\end{tabular}\n")
        # file.write("\\caption{Total signal yields measured in the full Dalitz and restricted $K^*(892)^\\pm$ region invariant mass fits.}\n")
        # file.write("\\label{tab:yields}\n")
        # file.write("\\end{table}")
        # file.close()
    elif fit == "1d":
        filename = path + "/DataResult_" + delta_low + "_" + delta_high + ".root"

        tf = TFile(filename)
        result = tf.Get("fitresult_simPdf_0_fullDataHist")
        if result == None:
            sys.exit("Could not extract result from " + filename)
        #Floating fit parameters
        pars = result.floatParsFinal()

        #List of params we want, with their value and error
        #Use these to calculate all the other yields
        variables = [
            "N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0",
            "N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0"
        ]
        #Dict to add the values and errors of the observables into
        obs = {}
        #Correlation matrix
        corr = np.ones((len(variables), len(variables)))

        for i in range(0, len(pars)):
            p = pars[i]
            p_name = p.GetName()
            if (p_name in variables):
                # In python, tuples () are immutable - can't change value: convert to tuple after calculating corrected error
                obs[p_name] = [p.getVal(), p.getError()]

        yield_tot_pi = ufloat(
            obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0"][0],
            obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0"][1])

        yield_tot_k = ufloat(
            obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0"][0],
            obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0"][1])

        # Convert dict values from lists to tuples to make them immutable (easier to debug)
        obs = {key: tuple(lst) for key, lst in obs.items()}

        #Fill correlation matrix - double counting doesn't effect this
        for a in range(0, len(variables)):
            for b in range(0, len(variables)):
                corr[a, b] = result.correlation(variables[a], variables[b])

        # Returns numbers with the correct uncertainties and correlations, given the covariance matric
        (obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0_corr"],
         obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral +
             "_k_0_corr"]) = u.correlated_values_norm([
                 obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0"],
                 obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0"]
             ], corr)

        #Ratio D*K/D*π
        obs["ratioKpi_Bu2Dst0h_D0" + neutral + "_" + neutral +
            ""] = obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral +
                      "_k_0_corr"] / obs["N_tot_Bu2Dst0h_D0" + neutral + "_" +
                                         neutral + "_pi_0_corr"]
        print("N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_pi_0_corr = " +
              str(obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral +
                      "_pi_0_corr"]) + "\t % error = " +
              str(
                  np.divide(
                      unumpy.std_devs(obs["N_tot_Bu2Dst0h_D0" + neutral + "_" +
                                          neutral + "_pi_0_corr"]),
                      unumpy.nominal_values(obs["N_tot_Bu2Dst0h_D0" + neutral +
                                                "_" + neutral +
                                                "_pi_0_corr"]) * 100)))
        print("N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral + "_k_0_corr = " +
              str(obs["N_tot_Bu2Dst0h_D0" + neutral + "_" + neutral +
                      "_k_0_corr"]) + "\t % error = " +
              str(
                  np.divide(
                      unumpy.std_devs(obs["N_tot_Bu2Dst0h_D0" + neutral + "_" +
                                          neutral + "_k_0_corr"]),
                      unumpy.nominal_values(obs["N_tot_Bu2Dst0h_D0" + neutral +
                                                "_" + neutral + "_k_0_corr"]) *
                      100)))
        print("ratioKpi_Bu2Dst0h_D0" + neutral + "_" + neutral + " = " +
              str(obs["ratioKpi_Bu2Dst0h_D0" + neutral + "_" + neutral + ""]) +
              "\t % error = " + str(
                  np.divide(
                      unumpy.std_devs(obs["ratioKpi_Bu2Dst0h_D0" + neutral +
                                          "_" + neutral + ""]),
                      unumpy.nominal_values(obs["ratioKpi_Bu2Dst0h_D0" +
                                                neutral + "_" + neutral +
                                                ""]) * 100)))
    else:
        sys.exit("-f/--fit = 1d/d1d")
