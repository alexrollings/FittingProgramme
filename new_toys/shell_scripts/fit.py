#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import os, re, subprocess, sys, argparse
import math
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
  parser.add_argument('-i',
                      '--input_dir',
                      type=str,
                      help='path to roodatasets',
                      required=True)
  parser.add_argument('-o',
                      '--output_dir',
                      type=str,
                      help='Directory where results should be stored',
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

  input_dir = args.input_dir
  output_dir = args.output_dir
  n_jobs = args.n_jobs
  delta_low = args.delta_low
  delta_high = args.delta_high
  bu_low = args.bu_low
  bu_high = args.bu_high

  if not os.path.exists(output_dir):
    os.mkdir(output_dir)

  datasets = []
  for f in os.listdir(input_dir):
    m = re.search('DataFile_[A-Za-z0-9]+\.root', f)
    if m:
      datasets.append(os.path.join(input_dir, f))

  n_ds = len(datasets)
  n_ds_per_job = int(math.ceil(n_ds / n_jobs))

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/'
  for i in range(0, n_jobs):
    if i != (n_jobs-1):
      ds_arr = datasets[i*n_ds_per_job:(i+1)*n_ds_per_job]
    else:
      ds_arr = datasets[i*n_ds_per_job:]
    ds_list = ','.join(ds_arr)
    templatePath = home_path + 'shell_scripts/fit.sh.tmpl'
    scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/fit_' + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_" + str(i) + ".sh"
    substitutions = {
        "nJob": i,
        "DATASETS": ds_list,
        "PATH": output_dir,
        "DL": delta_low,
        "DH": delta_high,
        "BL": bu_low,
        "BH": bu_high,
    }
    make_shell_script(templatePath, scriptPath, substitutions)
    run_process(["chmod", "+x", scriptPath])
    submitTemplate = home_path + 'shell_scripts/fit_submit.sh.tmpl'
    submitScript = '/data/lhcb/users/rollings/fitting_scripts/tmp/fit_' + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_" + str(
        i) + ".submit"
    submitSubs = {
        "nJob": i,
        "DL": delta_low,
        "DH": delta_high,
        "BL": bu_low,
        "BH": bu_high,
        "CLUSTERID": '$(ClusterId)'
    }
    make_shell_script(submitTemplate, submitScript, submitSubs)
    run_process(["condor_submit", submitScript])
