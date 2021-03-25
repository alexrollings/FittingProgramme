#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import os, re, subprocess, sys, argparse
from string import Template
import subprocess as sp
from shutil import copyfile
from distutils.dir_util import copy_tree
import math


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
  args = parser.parse_args()

  input_dir = args.input_dir
  output_dir = args.output_dir
  n_jobs = args.n_jobs

  if not os.path.exists(output_dir):
    os.mkdir(output_dir)
    os.mkdir(output_dir + '/results/')

  datasets = []
  for f in os.listdir(input_dir):
    m = re.search('DataFile_[A-Za-z0-9]+\.root', f)
    if m:
      datasets.append(os.path.join(input_dir, f))

  n_ds = len(datasets)
  n_ds_per_job = int(math.ceil(n_ds / n_jobs))

  neutral = 'gamma'
  var = 'buDelta'
  flines = [
      l.rstrip('\n') for l in open('/home/rollings/Bu2Dst0h_2d/FittingProgramme/shell_scripts/box_effs/' +
                                   neutral + '_' + var + '_box_limits.txt')
  ]
  lines = [l.split(':') for l in flines]
  box_limits = []
  for _, box in lines:
    box_limits.append(box)
  split = [l.split(' ') for l in box_limits]
  for box in split:
    bu_low = box[0]
    bu_high = box[1]
    delta_low = box[2]
    delta_high = box[3]

    home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/'
    for i in range(0, n_jobs):
      if i != (n_jobs-1):
        ds_arr = datasets[i*n_ds_per_job:(i+1)*n_ds_per_job]
      else:
        ds_arr = datasets[i*n_ds_per_job:]
      ds_list = ','.join(ds_arr)
      templatePath = home_path + 'shell_scripts/fit.sh.tmpl'
      scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/fit_' + delta_low + '_' + delta_high + '_' + bu_low + '_' + bu_high + '_' + str(i) + '.sh'
      substitutions = {
          'nJob': i,
          'DATASETS': ds_list,
          'PATH': output_dir,
          'DL': delta_low,
          'DH': delta_high,
          'BL': bu_low,
          'BH': bu_high,
      }
      make_shell_script(templatePath, scriptPath, substitutions)
      run_process(['chmod', '+x', scriptPath])
      submitTemplate = home_path + 'shell_scripts/fit_submit.sh.tmpl'
      submitScript = '/data/lhcb/users/rollings/fitting_scripts/tmp/fit_' + delta_low + '_' + delta_high + '_' + bu_low + '_' + bu_high + '_' + str(
          i) + '.submit'
      submitSubs = {
          'nJob': i,
          'DL': delta_low,
          'DH': delta_high,
          'BL': bu_low,
          'BH': bu_high,
          'CLUSTERID': '$(ClusterId)'
      }
      make_shell_script(submitTemplate, submitScript, submitSubs)
      run_process(['condor_submit', submitScript])
