#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import os, re, subprocess, sys, argparse
from string import Template
import subprocess as sp
from shutil import copyfile
from distutils.dir_util import copy_tree


def run_process(command):
  p = sp.Popen(command)
  p.wait()
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
  parser.add_argument('-q',
                      '--queue',
                      type=str,
                      help='queue = batch/condor',
                      required=True)
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
  parser.add_argument('-t',
                      '--n_toys',
                      type=int,
                      help='Number of toy datasets to generate per job',
                      required=True)
  parser.add_argument('-j',
                      '--n_jobs',
                      type=int,
                      help='Number of jobs to run on batch',
                      required=True)
  parser.add_argument(
      '-g',
      '--gen',
      type=str,
      help=
      '--gen=model/data: Toy dataset generated from D1D model or 2D dataset',
      required=True)
  parser.add_argument(
      '-i',
      '--input_dir',
      type=str,
      help='Path to RDS of data: required to generate toys from data PDF',
      required=False)
  # parser.add_argument(
  #     '-d',
  #     '--dim',
  #     type=str,
  #     help='Specify -d=1D if want to perform toys from 1D fit to BuDelta mass',
  #     required=False)
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

  queue = args.queue
  neutral = args.neutral
  daughters = args.daughters
  charge = args.charge
  output_dir = args.output_dir
  n_toys = args.n_toys
  n_jobs = args.n_jobs
  gen = args.gen
  input_dir = args.input_dir
  # dim = args.dim
  delta_low = args.delta_low
  delta_high = args.delta_high
  delta_partial_low = args.delta_partial_low
  delta_partial_high = args.delta_partial_high
  bu_low = args.bu_low
  bu_high = args.bu_high

  if queue == "batch":
    print("Running toys on batch")
  elif queue == "condor":
    print("Running toys on condor")
  else:
    sys.exit("--queue=batch/condor")

  if charge == "total":
    print("Running toys summed over charge")
  elif charge == "plus,minus":
    print("Running toys split by charge")
  else:
    sys.exit("--charge=total/plus,minus")

  if gen == "data":
    print("Generating toys from 2D datasets")
  elif gen == "model":
    print("Generating toys from D1D model")
  else:
    sys.exit("-gen=model/data")

  if neutral != "pi0" and neutral != "gamma":
    sys.exit("Specify neutral: -n=pi0/gamma")

  if daughters != "kpi" and daughters != "kpi,kk" and daughters != "kpi,kk,pipi":
    sys.exit("Specify daughters: -d=kpi/kpi,kk/kpi,kk,pipi")

  # if dim == "1":
  #   print("Performing 1D toys to BuDelta mass")
  #   dim = "-1D"

  if not os.path.exists(output_dir):
    os.mkdir(output_dir)

  if delta_low == None:
    delta_low = "125"
  if delta_high == None:
    delta_high = "170"
  if bu_low == None:
    bu_low = "5240"
  if bu_high == None:
    bu_high = "5330"
  if delta_partial_low == None:
    if neutral == "gamma":
      delta_partial_low = "60"
    else:
      delta_partial_low = "0"
  if delta_partial_high == None:
    if neutral == "gamma":
      delta_partial_high = "105"
    else:
      delta_partial_high = "0"

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/'
  for i in range(0, n_jobs):
    templatePath = home_path + 'shell_scripts/run_toys_' + gen + '.sh.tmpl'
    scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_toys_' + gen + '_' + neutral + "_" + delta_low + "_" + delta_high + "_" + delta_partial_low + "_" + delta_partial_high + "_" + bu_low + "_" + bu_high + "_" + charge + "_" + daughters + "_" + str(
        i) + ".sh"
    substitutions = {
        "nJob":
            i,
        "INPUT":
            input_dir,
        "PATH":
            output_dir,
        "NEUTRAL":
            neutral,
        "DAUGHTERS":
            daughters,
        "CHARGE":
            charge,
        "NTOYS":
            n_toys,
        "DL":
            delta_low,
        "DH":
            delta_high,
        "DPL":
            delta_partial_low,
        "DPH":
            delta_partial_high,
        "BL":
            bu_low,
        "BH":
            bu_high,
        # "DIM":
        #     dim
    }
    make_shell_script(templatePath, scriptPath, substitutions)
    if queue == 'batch':
      # run_process(["sh", scriptPath])
      run_process(["qsub", scriptPath])
    else:
      run_process(["chmod", "+x", scriptPath])
      submitTemplate = home_path + 'shell_scripts/run_toys_submit.sh.tmpl'
      submitScript = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_toys_' + gen + '_' + neutral + "_" + delta_low + "_" + delta_high + "_" + delta_partial_low + "_" + delta_partial_high + "_" + bu_low + "_" + bu_high + "_" + charge + "_" + daughters + "_" + str(
          i) + ".submit"
      submitSubs = {
          "nJob":
              i,
          "GEN":
              gen,
          "NEUTRAL":
              neutral,
          "DAUGHTERS":
              daughters,
          "CHARGE":
              charge,
          "NTOYS":
              n_toys,
          "DL":
              delta_low,
          "DH":
              delta_high,
          "DPL":
              delta_partial_low,
          "DPH":
              delta_partial_high,
          "BL":
              bu_low,
          "BH":
              bu_high,
          "CLUSTERID":
             '$(ClusterId)'
          # "DIM":
          #     dim
      }
      make_shell_script(submitTemplate, submitScript, submitSubs)
      run_process(["condor_submit", submitScript])
