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
  parser.add_argument(
      '-i',
      '--input_dir',
      type=str,
      help='Path to RDS of data: required to generate toys from data PDF',
      required=False)
  args = parser.parse_args()

  output_dir = args.output_dir
  input_dir = args.input_dir

  if not os.path.exists(output_dir):
    os.mkdir(output_dir)
    os.mkdir(output_dir + '/results/')
    os.mkdir(output_dir + '/plots/')

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/'
  templatePath = home_path + 'shell_scripts/plot_box_scan_pulls.sh.tmpl'

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

    scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/plot_box_scan_pulls_' +  delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + ".sh"
    substitutions = {
        "INPUT": input_dir,
        "OUTPUT": output_dir,
        "DL": delta_low,
        "DH": delta_high,
        "BL": bu_low,
        "BH": bu_high
    }
    make_shell_script(templatePath, scriptPath, substitutions)
    # run_process(["sh", scriptPath])
    run_process(["chmod", "+x", scriptPath])
    submitTemplate = home_path + '/shell_scripts/plot_box_scan_pulls_submit.sh.tmpl'
    submitScript = "/data/lhcb/users/rollings/fitting_scripts/tmp/plot_box_scan_pulls_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + ".submit"
    submitSubs = {
        "DL": delta_low,
        "DH": delta_high,
        "BL": bu_low,
        "BH": bu_high,
        "CLUSTERID": '$(ClusterId)'
    }
    make_shell_script(submitTemplate, submitScript, submitSubs)
    run_process(["condor_submit", submitScript])
