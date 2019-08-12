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

def pass_filename_pi(path, filename, file_list):
    m = re.search("[0-9]+_[a-z]+_pi_gamma_kpi_total.root",
                  filename)
    if m:
        file_list.append(path + "/" + filename)

def pass_filename_K(path, filename, file_list):
    m = re.search("[0-9]+_[a-z]+_k_gamma_kpi_total.root",
                  filename)
    if m:
        file_list.append(path + "/" + filename)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-d',
        '--dim',
        type=str,
        help='Dimension = 1/2',
        required=True)
    parser.add_argument(
        '-o',
        '--output_dir',
        type=str,
        help='Directory where datsets should be stored',
        required=True)
    parser.add_argument(
        '-i',
        '--input_dir',
        type=str,
        help='Directory where datasets should be stored',
        required=False)
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

    dim = args.dim
    output_dir = args.output_dir
    input_dir = args.input_dir
    n_toys = args.n_toys
    n_jobs = args.n_jobs
    delta_low = args.delta_low
    delta_high = args.delta_high
    bu_low = args.bu_low
    bu_high = args.bu_high
    file_list_pi = []
    file_list_K = []

    if dim == "1" :
        print("Generating 1D datasets.")
        if delta_low == "" or delta_high == "" or bu_low == "" or bu_high == "":
            sys.exit("For 1D generation, have to give box dimensions")
    elif dim == "2":
        print("Generating 2D datasets.")
        if input_dir == "":
            sys.exit("For 2D generation, have to give directory where data rds are stored.")
        else:
            for filename in os.listdir(input_dir):
                pass_filename_pi(input_dir, filename, file_list_pi)
                pass_filename_K(input_dir, filename, file_list_K)
            if len(file_list_pi) != len(file_list_K):
                sys.exit("Different number of datasets for π and K")
    else:
        sys.exit("-dim=1/2")

    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

    templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/shell_scripts/generate_" + dim + "d.sh.tmpl"
    scriptList = []
    for i in range(0, n_jobs):
        if dim == "1":
            scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/tmp/generate_1d_" + str(
                i
            ) + "_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + ".sh"
            substitutions = {
                "nJob":
                i,
                "GCCROOT":
                "/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6",
                "LD_LIBRARY_PATH":
                "/home/rollings/Software/install/lib64:/home/rollings/Software/install/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib:/home/rollings/Software/install/lib:64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib::/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/",
                "PATH":
                output_dir,
                "DELTALOW":
                delta_low,
                "DELTAHIGH":
                delta_high,
                "BULOW":
                bu_low,
                "BUHIGH":
                bu_high,
                "NTOYS":
                n_toys
            }
        else:
            scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/tmp/generate_2d_" + str(
                i
            ) + ".sh"
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
                "FILESPi":
                ",".join(file_list_pi),
                "FILESK":
                ",".join(file_list_K)
                }
        make_shell_script(templatePath, scriptPath, substitutions)
        scriptList.append(scriptPath)
        # submit_to_batch(["qsub", scriptPath])
        # submit_to_batch(["nohup", "sh", scriptPath, "> nohup_" + str(i) + ".out"])
        # submit_to_batch(["qsub", "-q", "testing", scriptPath])
    p = mp.Pool(n_jobs)
    p.map(run_process, scriptList)
