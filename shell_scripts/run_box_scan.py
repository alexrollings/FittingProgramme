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
                      help='Number of jobs to run on batch for each box dimn',
                      required=True)
  parser.add_argument(
      '-i',
      '--input_dir',
      type=str,
      help='Path to RDS of data: required to generate toys from data PDF',
      required=False)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral = pi0,gamma,partial',
                      required=True)
  parser.add_argument('-v',
                      '--var',
                      type=str,
                      help='Variable=buDelta/delta',
                      required=True)
  args = parser.parse_args()

  neutrals = args.neutral.split(",")
  queue = args.queue
  output_dir = args.output_dir
  n_toys = args.n_toys
  n_jobs = args.n_jobs
  input_dir = args.input_dir
  var = args.var

  if queue == "batch":
    print("Running toys on batch")
  elif queue == "condor":
    print("Running toys on condor")
  else:
    sys.exit("--queue=batch/condor")

  if var != "delta" and var != "buDelta":
    sys.exit("Specify var: -n=delta/buDelta")
  if not os.path.exists(output_dir):
    os.mkdir(output_dir)

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/'
  templatePath = home_path + 'shell_scripts/run_box_scan.sh.tmpl'

  for neutral in neutrals:
    if neutral != "pi0" and neutral != "gamma" and neutral != "partial":
      sys.exit("Specify neutral: -n=pi0,gamma,partial")
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
      if neutral == "partial":
        delta_partial_low = box[2]
        delta_partial_high = box[3]
        delta_low = '125'
        delta_high = '170'
      else:
        delta_low = box[2]
        delta_high = box[3]
        delta_partial_low = '60'
        delta_partial_high = '105'

      for i in range(0, n_jobs):
        scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_box_scan_' + neutral + "_" + delta_partial_low + "_" + delta_partial_high + "_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_" + str(
            i) + ".sh"
        if neutral == "partial":
          n = "gamma"
        else:
          n = neutral
        substitutions = {
            "nJob":
                i,
            "PATH":
                output_dir,
            "NEUTRAL":
                neutral,
            "N":
                n,
            "NTOYS":
                n_toys,
            "INPUT":
                input_dir,
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
                bu_high
        }
        make_shell_script(templatePath, scriptPath, substitutions)
        # run_process(["sh", scriptPath])
        if queue == 'batch':
          # run_process(["sh", scriptPath])
          run_process(["qsub", scriptPath])
        else:
          run_process(["chmod", "+x", scriptPath])
          submitTemplate = home_path + 'shell_scripts/run_box_scan_submit.sh.tmpl'
          submitScript = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_box_scan_' + neutral + "_" + delta_partial_low + "_" + delta_partial_high + "_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_" + str(
            i) + ".submit"
          submitSubs = {
              "nJob":
                  i,
              "NEUTRAL":
                  neutral,
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
          }
          make_shell_script(submitTemplate, submitScript, submitSubs)
          run_process(["condor_submit", submitScript])
