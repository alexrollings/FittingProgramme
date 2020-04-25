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
    systematics = [
        'pi0DeltaTails', 'pi0DeltaFrac', 'pi0BuTails', 'misRecDeltaPdf',
        'misRecBuPdf', 'partRecDeltaPdf', 'partRecBuPdf', 'Bs2Dst0KpiDeltaPdf',
        'Bs2Dst0KpiBuPdf', 'Bs2D0KpiDeltaPdf', 'Bs2D0KpiBuPdf',
        'misIdPi0PiPdfBu', 'misIdPi0KPdfBu', 'misIdGammaPiPdfBu',
        'misIdGammaKPdfBu', 'misIdMisRecKPdfBu', 'misIdPartRecKPdfBu',
        'buDeltaCutEffs', 'deltaCutEffs', 'buDeltaMisIdCutEffs',
        'deltaMisIdCutEffs', 'pidEffK'
    ]
    if delta_low == None:
      delta_low = "138"
    if delta_high == None:
      delta_high = "148"
    if bu_low == None:
      bu_low = "5220"
    if bu_high == None:
      bu_high = "5330"
  elif neutral == "gamma":
    systematics = [
        'pi0DeltaTails', 'pi0DeltaFrac', 'pi0BuPartialTails',
        'pi0BuPartialFrac', 'pi0BuPartialSigma1', 'crossFeedBuPdf',
        'crossFeedBuPartialPdf', 'gammaDeltaTails', 'gammaDeltaFrac',
        'gammaBuTails', 'gammaBuFrac', 'misRecDeltaPdf', 'misRecBuPdf',
        'misRecBuPartialPdf', 'partRecDeltaPdf', 'partRecBuPdf',
        'partRecBuPartialPdf', 'Bs2Dst0KpiDeltaPdf', 'Bs2Dst0KpiBuPdf',
        'Bs2Dst0KpiBuPartialPdf', 'Bs2D0KpiDeltaPdf', 'Bs2D0KpiBuPdf',
        'Bs2D0KpiBuPartialPdf', 'misIdPi0PiPdfBu', 'misIdPi0KPdfBu',
        'misIdPi0PiPdfBuPartial', 'misIdPi0KPdfBuPartial', 'misIdGammaPiPdfBu',
        'misIdGammaKPdfBu', 'misIdMisRecKPdfBu', 'misIdMisRecKPdfBuPartial',
        'misIdPartRecKPdfBu', 'misIdPartRecKPdfBuPartial', 'buDeltaCutEffs',
        'deltaCutEffs', 'deltaPartialCutEffs', 'buDeltaMisIdCutEffs',
        'deltaMisIdCutEffs', 'deltaPartialMisIdCutEffs', 'pidEffK'
    ]

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
  else:
    sys.exit("Specify neutral: -n=pi0/gamma")

  if daughters != "kpi" and daughters != "kpi,kk" and daughters != "kpi,kk,pipi" and daughters != "kpi,kk,pipi,pik":
    sys.exit("Specify daughters: -d=kpi/kpi,kk/kpi,kk,pipi/kpi,kk,pipi,pik")

  if not os.path.exists(output_dir):
    os.mkdir(output_dir)

  if n_jobs > 10:
    sys.exit("Can't use more than 10 cores.")

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/'
  scriptList = []
  for s in systematics:
    for i in range(0, n_jobs):
      templatePath = home_path + 'shell_scripts/run_systematics.sh.tmpl'
      scriptPath = '/data/lhcb/users/rollings/multi_processing/tmp/run_systematics_' + neutral + "_" + daughters + "_" + charge + "_" + s + "_" + str(
          i) + ".sh"
      substitutions = {
          "nJob": i,
          "INPUT": input_dir,
          "PATH": output_dir,
          "NEUTRAL": neutral,
          "DAUGHTERS": daughters,
          "CHARGE": charge,
          "SYST": s,
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
