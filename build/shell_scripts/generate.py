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
    parser.add_argument(
        '-d',
        '--dim',
        type=str,
        help='Specify -d=1D if want to perform toys from 1D fit to BuDelta mass',
        required=False)
    parser.add_argument(
        '-dl',
        '--delta_low',
        type=str,
        help='Lower delta mass range',
        required=False)
    parser.add_argument(
        '-dh',
        '--delta_high',
        type=str,
        help='Upper delta mass range',
        required=False)
    parser.add_argument(
        '-bl', '--bu_low', type=str, help='Lower bu mass range', required=False)
    parser.add_argument(
        '-bh',
        '--bu_high',
        type=str,
        help='Upper bu mass range',
        required=False)
    args = parser.parse_args()

    output_dir = args.output_dir
    n_toys = args.n_toys
    n_jobs = args.n_jobs
    input_dir = args.input_dir
    dim = args.dim
    delta_low = args.delta_low
    delta_high = args.delta_high
    bu_low = args.bu_low
    bu_high = args.bu_high

    if dim == None:
        print("Set dim="": performing D1D toys")
        dim = ""
    elif dim == "1":
        print("Performing 1D toys to BuDelta mass")
        dim = "-1D"
    else:
        sys.exit("Set -d=1 or nothing")

    if n_jobs > 10:
        sys.exit("Can't use more than 10 cores.")

    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

    if delta_low == None:
        delta_low = 125
    if delta_high == None:
        delta_high = 170
    if bu_low == None:
        bu_low = 5240
    if bu_high == None:
        bu_high = 5330

    scriptList = []
    for i in range(0, n_jobs):
        if input_dir == None:
            print("Generating toys from MC PDF")
            templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/shell_scripts/generate_from_mc.sh.tmpl"
            scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/tmp/generate_from_mc_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_" + str(
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
                "NTOYS":
                n_toys,
                "DL":
                delta_low,
                "DH":
                delta_high,
                "BL":
                bu_low,
                "BH":
                bu_high,
                "DIM":
                dim
            }
            make_shell_script(templatePath, scriptPath, substitutions)
            scriptList.append(scriptPath)
        else:
            print("Generating toys from data PDF")
            templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/shell_scripts/generate_from_data.sh.tmpl"
            scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/tmp/generate_from_data_"+ delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_"  + str(i) + ".sh"
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
                input_dir,
                "DL":
                delta_low,
                "DH":
                delta_high,
                "BL":
                bu_low,
                "BH":
                bu_high,
                "DIM":
                dim
            }
            make_shell_script(templatePath, scriptPath, substitutions)
            scriptList.append(scriptPath)
    p = mp.Pool(n_jobs)
    p.map(run_process, scriptList)
