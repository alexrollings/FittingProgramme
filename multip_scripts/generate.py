#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import os, re, subprocess, sys, argparse
from string import Template
import subprocess as sp
import multiprocessing as mp


def submit_to_batch(command):
  p = sp.Popen(command)
  p.wait()
  return p.returncode


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
  # mp.process.current_process()._config['tempdir'] =  '/data/lhcb/users/rollings/multi_process/tmp/'
  parser = argparse.ArgumentParser()
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral = pi0/gamma',
                      required=True)
  parser.add_argument('-d',
                      '--daughters',
                      type=str,
                      help='Daughters = kpi/kpi,kk/kpi,kk,pipi/kpi,kk,pipi,pik',
                      required=False)
  parser.add_argument('-c',
                      '--charge',
                      type=str,
                      help='Charge = total/plus,minus',
                      required=False)
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
                      help='Number of jobs to run',
                      required=True)
  parser.add_argument(
      '-i',
      '--input_dir',
      type=str,
      help='Path to RDS of data: required to generate toys from data PDF',
      required=False)
  parser.add_argument(
      '-g',
      '--gen',
      type=str,
      help='-d=pdfD1D, pdf2D,data2D',
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
  n_toys = args.n_toys
  n_jobs = args.n_jobs
  input_dir = args.input_dir
  gen = args.gen
  delta_low = args.delta_low
  delta_high = args.delta_high
  delta_partial_low = args.delta_partial_low
  delta_partial_high = args.delta_partial_high
  bu_low = args.bu_low
  bu_high = args.bu_high

  if neutral != "pi0" and neutral != "gamma":
    sys.exit("Specify neutral: -n=pi0/gamma")

  if charge == "total":
    print("Running toys summed over charge")
  elif charge == "plus,minus":
    print("Running toys split by charge")
  else:
    charge = "total"
    print("Running toys summed over charge")

  if daughters != "kpi" and daughters != "kpi,kk" and daughters != "kpi,kk,pipi" and daughters != "kpi,kk,pipi,pik":
    daughters = "kpi"
    print("Running toys for daughters=kpi")

  # if dim == "1":
  #   print("Performing 1D toys to BuDelta mass")
  #   dim = "-1D"

  if n_jobs > 20:
    sys.exit("Can't use more than 20 cores.")

  if not os.path.exists(output_dir):
    os.mkdir(output_dir)

  if neutral == "gamma":
    if delta_low == None:
      delta_low = "125"
    if delta_high == None:
      delta_high = "170"
    if delta_partial_low == None:
      delta_partial_low = "60"
    if delta_partial_high == None:
      delta_partial_high = "105"
    if bu_low == None:
      bu_low = "5240"
    if bu_high == None:
      bu_high = "5320"
  else:
    if delta_low == None:
      delta_low = "138"
    if delta_high == None:
      delta_high = "148"
    if bu_low == None:
      bu_low = "5220"
    if bu_high == None:
      bu_high = "5330"

  if input_dir == None:
    sys.exit("Must specify data dir")

  scriptList = []
  for i in range(0, n_jobs):
    templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/multip_scripts/generate.sh.tmpl"
    if neutral == "pi0":
      scriptPath = '/data/lhcb/users/rollings/multi_process/tmp/generate_' + neutral + "_" + gen + "_" + daughters + "_" + charge + "_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_" + str(
          i) + ".sh"
    else:
      scriptPath = '/data/lhcb/users/rollings/multi_process/tmp/generate_' + neutral + "_" + gen + "_" + daughters + "_" + charge + "_" + delta_low + "_" + delta_high + "_" + delta_partial_low + "_" + delta_partial_high + "_" + bu_low + "_" + bu_high + "_" + str(
          i) + ".sh"
    substitutions = {
        "nJob": i,
        "PATH": output_dir,
        "NEUTRAL": neutral,
        "DAUGHTERS": daughters,
        "CHARGE": charge,
        "NTOYS": n_toys,
        "INPUT": input_dir,
        "GEN": gen,
        "DL": delta_low,
        "DH": delta_high,
        "DPL": delta_partial_low,
        "DPH": delta_partial_high,
        "BL": bu_low,
        "BH": bu_high
    }
    make_shell_script(templatePath, scriptPath, substitutions)
    scriptList.append(scriptPath)
  p = mp.Pool(n_jobs)
  p.map(run_process, scriptList)
