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
  gen = args.gen
  input_dir = args.input_dir
  # dim = args.dim
  delta_low = args.delta_low
  delta_high = args.delta_high
  delta_partial_low = args.delta_partial_low
  delta_partial_high = args.delta_partial_high
  bu_low = args.bu_low
  bu_high = args.bu_high

  if charge == "total":
    print("Running toys summed over charge")
  elif charge == "plus,minus":
    print("Running toys split by charge")
  else:
    sys.exit("--charge=total/plus,minus")

  if gen == "data":
    if input_dir == None:
      sys.exit(
          "If generating toys from 2D datasets, specify --input_dir=<path>")
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
    delta_partial_low = "60"
  if delta_partial_high == None:
    delta_partial_high = "105"

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/'
  for i in range(0, n_jobs):
    # j_dir = '/data/lhcb/users/rollings/fitting_scripts/job_' + neutral + '_' + delta_low + '_' + delta_high + '_' + bu_low + '_' + bu_high + '_'  + str(i) + '/'
    # os.mkdir(j_dir)
    # copyfile(home_path + 'CMakeMacroParseArguments.cmake', j_dir + 'CMakeMacroParseArguments.cmake')
    # copyfile(home_path + 'FindROOT.cmake', j_dir + 'FindROOT.cmake')
    # copyfile(home_path + 'CMakeLists.txt', j_dir + 'CMakeLists.txt')
    # os.mkdir(j_dir + 'src/')
    # copy_tree(home_path + 'src/', j_dir + 'src/')
    # os.mkdir(j_dir + 'include/')
    # copy_tree(home_path + 'include/', j_dir + 'include/')
    # os.mkdir(j_dir + 'build/')

    templatePath = home_path + 'shell_scripts/run_toys_' + gen + '.sh.tmpl'
    if neutral == "pi0":
      scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_toys_' + gen + '_' + neutral + "_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_" + charge + "_" + daughters + "_" + str(
          i) + ".sh"
    else:
      scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_toys_' + gen + '_' + neutral + "_" + delta_low + "_" + delta_high + "_" + delta_partial_low + "_" + delta_partial_high + "_" + bu_low + "_" + bu_high + "_" + charge + "_" + daughters + "_" + str(
          i) + ".sh"
    substitutions = {
        "nJob":
            i,
        "GCCROOT":
            "/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6",
        "LD_LIBRARY_PATH":
            "/home/rollings/Software/install/lib64:/home/rollings/Software/install/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib:/home/rollings/Software/install/lib:64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib::/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/",
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
    if gen == 'data':
      substitutions["INPUT"] = input_dir
    make_shell_script(templatePath, scriptPath, substitutions)
    # run_process(["sh", scriptPath])
    run_process(["qsub", scriptPath])
