import math, re, os, sys, glob
from ROOT import TFile, RooFitResult
import argparse

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument('-d',
                      '--data_dir',
                      type=str,
                      help='Directory where data result is stored',
                      required=True)
  parser.add_argument('-p',
                      '--pull_dir',
                      type=str,
                      help='Directory where pull result is stored',
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

  data_dir = args.data_dir
  pull_dir = args.pull_dir
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

  fit_file = data_dir + "/DataResult_" + box_string + ".root"
  tf_fit = TFile(fit_file)
  fit_result = tf_fit.Get("DataFitResult")
  if fit_result == None:
    sys.exit("Could not extract DataFitResult from " + fit_file)

  pull_file = pull_dir + "/Result_" + box_string + ".root"
  tf_pull = TFile(pull_file)

  #Dict to add the values and errors of the observables into
  obs = {}
  #Floating fit parameters
  pars = fit_result.floatParsFinal()
  fit_result.Print('v')
  for i in range(0, len(pars)):
    p = pars[i]
    p_name = p.GetName()
    # if (p_name in yields):
    # In python, tuples () are immutable - can't change value: convert to tuple after calculating corrected error
    pull_result = tf_pull.Get("Result_Pull_" + p_name[:-2])
    if pull_result == None:
      print("Could not extract Result_Pull_" + p_name[:-2] + " from " +
               pull_file)
    else:
      pull_pars = pull_result.floatParsFinal()
      pull_mean = pull_pars[0].getVal()
      pull_width = pull_pars[1].getVal()
      obs[p_name] = [
          p.getVal() - pull_mean * p.getError(),
          p.getError() * pull_width
      ]

  for k, v in obs.items():
    print(k, ":")
    print(v[0], " ± ", v[1])
    print(v[0], " ± ", (v[1] / v[0]) * 100, " %")
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
