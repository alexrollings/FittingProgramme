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
    p = sp.Popen(["sh", script], stdout=sp.PIPE, stderr=sp.PIPE)
    stdout, stderr = p.communicate()
    with open(os.path.splitext(os.path.basename(script))[0] + '.out', 'w') as out_file:
        out_file.write(stdout)
    with open(os.path.splitext(os.path.basename(script))[0] + '.err', 'w') as err_file:
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
    parser.add_argument(
        '-o',
        '--output_dir',
        type=str,
        help='Directory where results should be stored',
        required=True)
    parser.add_argument(
        '-t',
        '--n_toys',
        type=int,
        help='Number of toy datasets to generate per job',
        required=True)
    parser.add_argument(
        '-j',
        '--n_jobs',
        type=int,
        help='Number of jobs to run on batch',
        required=True)
    parser.add_argument(
        '-i',
        '--input_dir',
        type=str,
        help='Path to RDS of data: required to generate toys from data PDF',
        required=False)
    args = parser.parse_args()

    output_dir = args.output_dir
    n_toys = args.n_toys
    n_jobs = args.n_jobs
    input_dir = args.input_dir

    if n_jobs > 10:
      sys.exit("Can't use more than 10 cores.")

    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

    scriptList = []
    for i in range(0, n_jobs):
        if input_dir == None:
            print("Generating toys from MC PDF")
            templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/shell_scripts/generate_from_mc.sh.tmpl"
            scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/tmp/generate_from_mc_" + str(i) + ".sh.tmpl"
            substitutions = {
                "nJob":
                i,
                "GCCROOT":
                "/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6",
                "LD_LIBRARY_PATH":
                "/home/rollings/Software/install/lib64:/home/rollings/Software/install/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib:/home/rollings/Software/install/lib:64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib::/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/",
                "PATH":
                output_dir,
                "NTOYS":
                n_toys
            }
            make_shell_script(templatePath, scriptPath, substitutions)
            scriptList.append(scriptPath)
        else:
            print("Generating toys from data PDF")
            templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/shell_scripts/generate_from_data.sh.tmpl"
            scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/tmp/generate_from_data_" + str(i) + ".sh.tmpl"
            substitutions = {
                "nJob":
                i,
                "GCCROOT":
                "/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6",
                "LD_LIBRARY_PATH":
                "/home/rollings/Software/install/lib64:/home/rollings/Software/install/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib:/home/rollings/Software/install/lib:64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib::/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/",
                "PATH":
                output_dir,
                "NTOYS":
                n_toys,
                "INPUT":
                input_dir
            }
            make_shell_script(templatePath, scriptPath, substitutions)
            scriptList.append(scriptPath)
    p = mp.Pool(n_jobs)
    p.map(run_process, scriptList)
