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
  parser.add_argument('-bh',
                      '--bu_high',
                      type=str,
                      help='Upper bu mass range',
                      required=True)
  args = parser.parse_args()

  output_dir = args.output_dir
  n_toys = args.n_toys
  n_jobs = args.n_jobs
  delta_low = args.delta_low
  delta_high = args.delta_high
  bu_low = args.bu_low
  bu_high = args.bu_high

  if not os.path.exists(output_dir):
    os.mkdir(output_dir)

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/error_studies/'
  for i in range(0, n_jobs):
    templatePath = home_path + 'shell_scripts/run_toys.sh.tmpl'
    scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_toys_' + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_" + str(i) + ".sh"
    substitutions = {
        "nJob": i,
        "PATH": output_dir,
        "NTOYS": n_toys,
        "DL": delta_low,
        "DH": delta_high,
        "BL": bu_low,
        "BH": bu_high,
    }
    make_shell_script(templatePath, scriptPath, substitutions)
    run_process(["chmod", "+x", scriptPath])
    submitTemplate = home_path + 'shell_scripts/run_toys_submit.sh.tmpl'
    submitScript = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_toys_' + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_" + str(
        i) + ".submit"
    submitSubs = {
        "nJob": i,
        "NTOYS": n_toys,
        "DL": delta_low,
        "DH": delta_high,
        "BL": bu_low,
        "BH": bu_high,
        "CLUSTERID": '$(ClusterId)'
    }
    make_shell_script(submitTemplate, submitScript, submitSubs)
    run_process(["condor_submit", submitScript])
