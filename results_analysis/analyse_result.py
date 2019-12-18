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
        '-i',
        '--input_dir',
        type=str,
        help='Directory where results are stored',
        required=True)
    parser.add_argument('-n',
                        '--neutral',
                        type=str,
                        help='Neutral = pi0/gamma',
                        required=True)
    parser.add_argument('-c',
                        '--charge',
                        type=str,
                        help='Charge = total/plus,minus',
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
    parser.add_argument('-dpl',
                        '--delta_partial_low',
                        type=str,
                        help='Lower delta mass range',
                        required=False)
    parser.add_argument('-dph',
                        '--delta_partial_high',
                        type=str,
                        help='Upper delta mass range',
                        required=False)
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

    input_dir = args.input_dir
    neutral = args.neutral
    charge = args.charge.split(",")
    delta_low = args.delta_low
    delta_high = args.delta_high
    delta_partial_low = args.delta_partial_low
    delta_partial_high = args.delta_partial_high
    bu_low = args.bu_low
    bu_high = args.bu_high

    if neutral != "gamma" and neutral != "pi0":
        sys.exit("Neutral = pi0/gamma only")

    if delta_partial_low == None or delta_partial_high == None:
        if bu_low == None or bu_high == None:
            box_string = delta_low + "_" + delta_high
        else:
            box_string = delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high
    else:
        if bu_low == None or bu_high == None:
            box_string = delta_partial_low + "_" + delta_partial_high + "_" + delta_low + "_" + delta_high
        else:
            box_string = delta_partial_low + "_" + delta_partial_high + "_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high

    fit_file = input_dir + "/data_results/DataResult_" + box_string + ".root"
    tf_fit = TFile(fit_file)
    fit_result = tf_fit.Get("DataFitResult")
    if fit_result == None:
        sys.exit("Could not extract DataFitResult from " + fit_file)

    pull_file = input_dir + "/pull_results/Result_" + box_string + ".root"
    tf_pull = TFile(pull_file)

    #yields we want to correct
    decays = [
        "Bu2Dst0h_D0pi0",
        "Bu2D0h",
        "MisRec",
        "PartRec",
    ]
    if neutral == "gamma":
        decays.append("Bu2Dst0h_D0gamma")
    # yields = []
    # for d in decays:
    #     for c in charge:
    #         yields.append("N_tot_" + d + "_" + neutral + "_pi_" + c + "_0")
    #         yields.append("N_tot_" + d + "_" + neutral + "_k_" + c + "_0")

    #Dict to add the values and errors of the observables into
    obs = {}
    #Floating fit parameters
    pars = fit_result.floatParsFinal()
    fit_result.Print()
    for i in range(0, len(pars)):
        p = pars[i]
        p_name = p.GetName()
        # if (p_name in yields):
        # In python, tuples () are immutable - can't change value: convert to tuple after calculating corrected error
        pull_result = tf_pull.Get("Result_Pull_" + p_name[:-2])
        if pull_result == None:
            sys.exit("Could not extract Result_Pull_" + p_name[:-2] + " from " + pull_file)
        pull_pars = pull_result.floatParsFinal()
        pull_mean = pull_pars[0].getVal()
        pull_width = pull_pars[1].getVal()
        obs[p_name] = [p.getVal() - pull_mean*p.getError(), p.getError()*pull_width]


    # Convert dict values from lists to tuples to make them immutable (easier to debug)
    obs = {key: tuple(lst) for key, lst in obs.items()}

    for d in decays:
        for c in charge:
            # Correlation matrix for yeilds (need to account for correlations between π and k yields when propagating uncertainties through to ratio)
            bachelor = ["pi", "k"]
            corr = np.ones((len(bachelor), len(bachelor)))
            for a in range(0, len(bachelor)):
                for b in range(0, len(bachelor)):
                    corr[a, b] = fit_result.correlation("N_tot_" + d + "_" + neutral + "_" + bachelor[a] + "_" + c + "_0", "N_tot_" + d + "_" + neutral + "_" + bachelor[b] + "_" + c + "_0")
            # Returns numbers with the correct uncertainties and correlations, given the covariance matrix
            (obs["N_tot_" + d + "_" + neutral + "_pi_" + c + "_0_corr"], obs["N_tot_" + d + "_" + neutral + "_k_" + c + "_0_corr"]) = u.correlated_values_norm([obs["N_tot_" + d + "_" + neutral + "_pi_" + c + "_0"], obs["N_tot_" + d + "_" + neutral + "_k_" + c + "_0"]], corr)
            obs["R_Kpi_" + d + "_" + neutral + "_" + c] = obs["N_tot_" + d + "_" + neutral + "_k_" + c + "_0_corr"] / obs["N_tot_" + d + "_" + neutral + "_pi_" + c + "_0_corr"]

    for k, v in obs.items():
        # if isinstance(v, tuple):
        #     print(k, " = ", v[0], " ± ", v[1])
        if isinstance(v, u.UFloat):
            print(k, ":")
            print(v.nominal_value, " ± ", v.std_dev)
            print(v.nominal_value, " ± ", (v.std_dev/v.nominal_value)*100, " %")
            print(" ")

        # else:
        #     print("Do not recognise type of object in obs for key ", k)

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
