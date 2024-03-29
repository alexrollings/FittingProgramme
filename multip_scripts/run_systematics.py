#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import os, re, subprocess, sys, argparse
from string import Template
import subprocess as sp
import multiprocessing as mp

def run_process(script):
  p = sp.Popen(["zsh", script], stdout=sp.PIPE, stderr=sp.PIPE)
  stdout, stderr = p.communicate()
  with open(
      '/data/lhcb/users/rollings/multi_process/tmp/' +
      os.path.splitext(os.path.basename(script))[0] + '.out', 'w') as out_file:
    out_file.write(stdout)
  with open(
      '/data/lhcb/users/rollings/multi_process/tmp/' +
      os.path.splitext(os.path.basename(script))[0] + '.err', 'w') as err_file:
    err_file.write(stderr)
  return p.returncode

def make_shell_script(templatePath, scriptPath, substitutions):
  with open(templatePath, "r") as templateFile:
    scriptTemplate = Template(templateFile.read())
    # Define each variable required by the template
    # Substitute into the string
    scriptString = scriptTemplate.substitute(substitutions)
    # Write to an output file
    with open(scriptPath, "w") as scriptFile:
      scriptFile.write(scriptString)

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral = pi0/gamma',
                      required=True)
  parser.add_argument('-d',
                      '--daughters',
                      type=str,
                      help='Daughters = kpi/kpi,kk/kpi,kk,pipi',
                      required=True)
  parser.add_argument('-c',
                      '--charge',
                      type=str,
                      help='charge = total/plus,minus',
                      required=True)
  parser.add_argument('-o',
                      '--output_dir',
                      type=str,
                      help='Directory where results should be stored',
                      required=True)
  parser.add_argument('-f',
                      '--n_fits',
                      type=int,
                      help='Number of fits to run per job',
                      required=True)
  parser.add_argument('-j',
                      '--n_jobs',
                      type=int,
                      help='Number of jobs to run on batch',
                      required=True)
  parser.add_argument('-i',
                      '--input_dir',
                      type=str,
                      help='Path to RDS of data',
                      required=True)
  parser.add_argument('-s',
                      '--systematic',
                      type=str,
                      help='Path to RDS of data',
                      required=True)
  parser.add_argument('-dl',
                      '--delta_low',
                      type=str,
                      help='Lower delta mass range',
                      required=False)
  parser.add_argument('-dh',
                      '--delta_high',
                      type=str,
                      help='Upper delta mass range',
                      required=False)
  parser.add_argument('-dpl',
                      '--delta_partial_low',
                      type=str,
                      help='Lower delta_partial mass range',
                      required=False)
  parser.add_argument('-dph',
                      '--delta_partial_high',
                      type=str,
                      help='Upper delta_partial mass range',
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

  neutral = args.neutral
  daughters = args.daughters
  charge = args.charge
  systematic = args.systematic
  output_dir = args.output_dir
  n_fits = args.n_fits
  n_jobs = args.n_jobs
  input_dir = args.input_dir
  delta_low = args.delta_low
  delta_high = args.delta_high
  delta_partial_low = args.delta_partial_low
  delta_partial_high = args.delta_partial_high
  bu_low = args.bu_low
  bu_high = args.bu_high

  if charge == "total":
    print("Running fits summed over charge")
  elif charge == "plus,minus":
    print("Running fits split by charge")
  else:
    sys.exit("--charge=total/plus,minus")

  if neutral == "pi0":
    if delta_low == None:
      delta_low = "138"
    if delta_high == None:
      delta_high = "148"
    if bu_low == None:
      bu_low = "5220"
    if bu_high == None:
      bu_high = "5330"
    systematics = [
        'Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi',
        'Bu2Dst0h_D0pi0_PdfDelta_Tails', 'Bu2Dst0h_D0pi0_PdfDelta_Frac',
        'Bu2Dst0h_D0pi0_PdfBu_SigmaRatioKpi', 'Bu2Dst0h_D0pi0_PdfBu_Tails',
        'Bu2Dst0h_D0pi0_PdfBu_Frac', 'Bu2Dst0h_D0pi0_WN_PdfDelta',
        'Bu2Dst0h_D0pi0_WN_PdfBu', 'Bu2Dst0h_D0gamma_WN_PdfDelta',
        'Bu2Dst0h_D0gamma_WN_PdfBu', 'Bd2Dsth_PdfDelta', 'Bd2Dsth_PdfBu',
        'Bu2D0hst_PdfDelta', 'Bu2D0hst_PdfDelta_D02pik', 'Bu2D0hst_PdfBu',
        'Bu2D0hst_PdfBu_D02pik', 'Bu2Dst0hst_D0pi0_PdfDelta',
        'Bu2Dst0hst_D0pi0_PdfBu', 'Bu2Dst0hst_PdfBu_D02pik',
        'Lb2Omegach_Lcpi0_PdfDelta', 'Lb2Omegach_Lcpi0_PdfBu',
        'Bs2Dst0Kpi_PdfDelta', 'Bs2Dst0Kpi_PdfBu', 'Bs2D0Kpi_PdfDelta',
        'Bs2D0Kpi_PdfBu', 'Bu2Dst0K_D0pi0_asPi_PdfBu',
        'Bu2Dst0pi_D0pi0_asK_Pdfs', 'Bu2Dst0pi_D0pi0_asPi_Pdfs',
        'Bu2Dst0h_WN_misId_Pdfs', 'Bkg_misId_Pdfs', 'D02pik_Pdfs',
        'boxEffs_Bu2Dst0h_D0pi0', 'boxEffs_Bu2Dst0h_D0gamma', 'boxEffs_Bkg',
        'boxEffs_Bs2Dst0Kpi', 'boxEffs_Bs2D0Kpi', 'boxEffs_D02pik',
        'boxEffs_Bu2Dst0h_D0pi0_misId', 'boxEffs_Bu2Dst0h_D0gamma_misId',
        'boxEffs_Bkg_misId', 'mcEffs_Bu2Dst0h_D0pi0',
        'mcEffs_Bu2Dst0h_D0gamma', 'mcEffs_Bkg', 'mcEffs_Bu2Dst0h_D0pi0_misId',
        'mcEffs_Bu2Dst0h_D0gamma_misId', 'mcEffs_Bkg_misId',
        'Bu2D0hst_BkgFrac', 'Bu2Dst0hst_BkgFrac', 'Bs2D0Kpi_BkgFrac',
        'pidEffPi', 'pidEffK', 'crossFeedRate', 'A_pi_Kpi_Bu2Dst0h_D0pi0',
        'A_pi_Kpi_Bu2Dst0h_D0gamma', 'A_pi_Kpi_Bu2Dst0h_WN',
        'A_pi_Kpi_Bu2D0hst', 'A_pi_Kpi_Bu2Dst0hst', 'A_K_Kpi_Bu2Dst0h_WN',
        'A_K_Kpi_Bu2D0hst', 'A_K_Kpi_Bu2Dst0hst', 'A_K_piK_Bu2D0hst', 'A_Kpi',
        'A_pi', 'Delta_A_CP', 'R_CP_Bu2D0hst', 'R_ADS_Bu2D0hst',
        'A_CP_pi_Bu2D0hst', 'A_CP_K_Bu2D0hst', 'R_Dst0KDst0pi_Bd2Dsth',
        'R_Dst0KDst0pi_Lb2Omegach_Lcpi0', 'kBF_D02kpi', 'kBF_D02kk',
        'kBF_D02pipi'
    ]
  elif neutral == "gamma":
    if delta_low == None:
      delta_low = "125"
    if delta_high == None:
      delta_high = "170"
    if bu_low == None:
      bu_low = "5240"
    if bu_high == None:
      bu_high = "5320"
    if delta_partial_low == None:
      delta_partial_low = "60"
    if delta_partial_high == None:
      delta_partial_high = "105"
    systematics = [
        'Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi',
        'Bu2Dst0h_D0pi0_PdfDelta_Tails', 'Bu2Dst0h_D0pi0_PdfDelta_Frac',
        'Bu2Dst0h_D0pi0_PdfBuPartial_MeanOffset',
        'Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatioKpi',
        'Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatio',
        'Bu2Dst0h_D0pi0_PdfBuPartial_Tails',
        'Bu2Dst0h_D0pi0_PdfBuPartial_Frac',
        'Bu2Dst0h_D0pi0_PdfBuPartial_Sigma1', 'Bu2Dst0h_D0pi0_PdfBu',
        'Bu2Dst0h_D0gamma_PdfBuPartial',
        'Bu2Dst0h_D0gamma_PdfDelta_SigmaRatioKpi',
        'Bu2Dst0h_D0gamma_PdfDelta_Tails', 'Bu2Dst0h_D0gamma_PdfDelta_Frac',
        'Bu2Dst0h_D0gamma_PdfBu_SigmaRatioKpi', 'Bu2Dst0h_D0gamma_PdfBu_Tails',
        'Bu2Dst0h_D0gamma_PdfBu_Frac', 'Bu2Dst0h_D0pi0_WN_PdfDelta',
        'Bu2Dst0h_D0pi0_WN_PdfBu', 'Bu2Dst0h_D0pi0_WN_PdfBuPartial',
        'Bu2Dst0h_D0gamma_WN_PdfDelta', 'Bu2Dst0h_D0gamma_WN_PdfBu',
        'Bu2Dst0h_D0gamma_WN_PdfBuPartial', 'Bd2Dsth_PdfDelta',
        'Bd2Dsth_PdfBu', 'Bd2Dsth_PdfBuPartial', 'Bu2D0hst_PdfDelta',
        'Bu2D0hst_PdfDelta_D02pik', 'Bu2D0hst_PdfBu', 'Bu2D0hst_PdfBu_D02pik',
        'Bu2D0hst_PdfBuPartial', 'Bu2Dst0hst_D0gamma_PdfDelta',
        'Bu2Dst0hst_D0gamma_PdfBu', 'Bu2Dst0hst_D0gamma_PdfBuPartial',
        'Bu2Dst0hst_D0pi0_PdfDelta', 'Bu2Dst0hst_D0pi0_PdfBu',
        'Bu2Dst0hst_D0pi0_PdfBuPartial', 'Bu2Dst0hst_PdfBu_D02pik',
        'Bu2Dst0hst_Frac', 'Lb2Omegach_Lcpi0_PdfDelta',
        'Lb2Omegach_Lcpi0_PdfBu', 'Lb2Omegach_Lcpi0_PdfBuPartial',
        'Bs2Dst0Kpi_PdfDelta', 'Bs2Dst0Kpi_PdfBu', 'Bs2Dst0Kpi_PdfBuPartial',
        'Bs2D0Kpi_PdfDelta', 'Bs2D0Kpi_PdfBu', 'Bs2D0Kpi_PdfBuPartial',
        'Bu2Dst0pi_D0pi0_asK_Pdfs', 'Bu2Dst0pi_D0pi0_asPi_Pdfs',
        'Bu2Dst0pi_D0gamma_asK_Pdfs', 'Bu2Dst0pi_D0gamma_asPi_Pdfs',
        'Bu2Dst0h_WN_misId_Pdfs', 'Bkg_misId_Pdfs', 'D02pik_Pdfs',
        'boxEffs_Bu2Dst0h_D0pi0', 'boxEffs_Bu2Dst0h_D0gamma', 'boxEffs_Bkg',
        'boxEffs_Bs2Dst0Kpi', 'boxEffs_Bs2D0Kpi', 'boxEffs_D02pik',
        'boxEffs_Bu2Dst0h_D0pi0_misId', 'boxEffs_Bu2Dst0h_D0gamma_misId',
        'boxEffs_Bkg_misId', 'mcEffs_Bu2Dst0h_D0pi0',
        'mcEffs_Bu2Dst0h_D0gamma', 'mcEffs_Bkg', 'mcEffs_Bu2Dst0h_D0pi0_misId',
        'mcEffs_Bu2Dst0h_D0gamma_misId', 'mcEffs_Bkg_misId',
        'Bu2D0hst_BkgFrac', 'Bu2Dst0hst_BkgFrac', 'Bs2D0Kpi_BkgFrac',
        'pidEffPi', 'pidEffK', 'crossFeedRate', 'A_pi_Kpi_Bu2Dst0h_D0pi0',
        'A_pi_Kpi_Bu2Dst0h_D0gamma', 'A_pi_Kpi_Bu2Dst0h_WN',
        'A_pi_Kpi_Bu2D0hst', 'A_pi_Kpi_Bu2Dst0hst', 'A_K_Kpi_Bu2Dst0h_WN',
        'A_K_Kpi_Bu2D0hst', 'A_K_Kpi_Bu2Dst0hst', 'A_K_piK_Bu2D0hst', 'A_Kpi',
        'A_pi', 'Delta_A_CP', 'R_CP_Bu2D0hst', 'R_ADS_Bu2D0hst',
        'A_CP_pi_Bu2D0hst', 'A_CP_K_Bu2D0hst', 'R_Dst0KDst0pi_Bd2Dsth',
        'R_Dst0KDst0pi_Lb2Omegach_Lcpi0', 'kBF_D02kpi', 'kBF_D02kk',
        'kBF_D02pipi'
    ]
  else:
    sys.exit("Specify neutral: -n=pi0/gamma")

  if systematic not in systematics:
    sys.exit(systematic + " not valid.")

  if daughters != "kpi" and daughters != "kpi,kk" and daughters != "kpi,kk,pipi" and daughters != "kpi,kk,pipi,pik":
    sys.exit("Specify daughters: -d=kpi/kpi,kk/kpi,kk,pipi/kpi,kk,pipi,pik")

  if not os.path.exists(output_dir):
    os.mkdir(output_dir)

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/'
  scriptList = []
  for i in range(0, n_jobs):
    templatePath = home_path + 'shell_scripts/run_systematics.sh.tmpl'
    scriptPath = '/data/lhcb/users/rollings/multi_processing/tmp/run_systematics_' + neutral + "_" + daughters + "_" + charge + "_" + systematic + "_" + str(
        i) + ".sh"
    substitutions = {
        "nJob": i,
        "INPUT": input_dir,
        "PATH": output_dir,
        "NEUTRAL": neutral,
        "DAUGHTERS": daughters,
        "CHARGE": charge,
        "SYST": systematic,
        "NFITS": n_fits,
        "DL": delta_low,
        "DH": delta_high,
        "DPL": delta_partial_low,
        "DPH": delta_partial_high,
        "BL": bu_low,
        "BH": bu_high,
    }
    make_shell_script(templatePath, scriptPath, substitutions)
    scriptList.append(scriptPath)
  p = mp.Pool(n_jobs)
  p.map(run_process, scriptList)
