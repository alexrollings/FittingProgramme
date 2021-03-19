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
  parser.add_argument('-g',
                      '--gen',
                      type=str,
                      help='Generate from pdf/MC -g=pdf/mc',
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
  args = parser.parse_args()

  output_dir = args.output_dir
  gen = args.gen
  n_toys = args.n_toys
  n_jobs = args.n_jobs

  if gen == 'pdf':
    print('Generating datasets from 2D PDF')
  elif gen == 'mc':
    print('Generating datasets from MC')
  else:
    sys.exit('--gen = pdf/mc')

  if not os.path.exists(output_dir):
    os.mkdir(output_dir)

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/new_toys/'
  for i in range(0, n_jobs):
    templatePath = home_path + 'shell_scripts/generate.sh.tmpl'
    scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/generate_' + str(i) + ".sh"
    substitutions = {
        "nJob": i,
        "GEN": gen,
        "PATH": output_dir,
        "NTOYS": n_toys
    }
    make_shell_script(templatePath, scriptPath, substitutions)
    run_process(["chmod", "+x", scriptPath])
    submitTemplate = home_path + 'shell_scripts/generate_submit.sh.tmpl'
    submitScript = '/data/lhcb/users/rollings/fitting_scripts/tmp/generate_' + str(
        i) + ".submit"
    submitSubs = {
        "nJob": i,
        "CLUSTERID": '$(ClusterId)'
    }
    make_shell_script(submitTemplate, submitScript, submitSubs)
    run_process(["condor_submit", submitScript])
