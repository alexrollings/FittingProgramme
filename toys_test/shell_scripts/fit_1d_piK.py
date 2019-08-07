#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import os, re, subprocess, sys, argparse
from string import Template
import subprocess as sp
import multiprocessing as mp


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


def pass_filename_pi(filename, file_list, dim, delta_low, delta_high, bu_low, bu_high):
    if dim == "1":
        m = re.search("DataFilePi" + dim + "D_" + delta_low + "_" + delta_high +
                      "_" + bu_low + "_" + bu_high + "_0.[0-9]+.root",
                      filename)
    elif dim == "2":
        m = re.search("DataFile" + dim + "D_0.[0-9]+.root", filename)
        # m = re.search("DataFile_0.[0-9]+.root", filename)
    else:
        sys.exit("Dimension = 1/2")
    if m:
        file_list.append(filename)

def pass_filename_K(filename, file_list, dim, delta_low, delta_high, bu_low, bu_high):
    if dim == "1":
        m = re.search("DataFileK" + dim + "D_" + delta_low + "_" + delta_high +
                      "_" + bu_low + "_" + bu_high + "_0.[0-9]+.root",
                      filename)
    elif dim == "2":
        m = re.search("DataFile" + dim + "D_0.[0-9]+.root", filename)
        # m = re.search("DataFile_0.[0-9]+.root", filename)
    else:
        sys.exit("Dimension = 1/2")
    if m:
        file_list.append(filename)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-i',
        '--input_dir',
        type=str,
        help='Directory where datasets should be stored',
        required=True)
    parser.add_argument(
        '-o',
        '--output_dir',
        type=str,
        help='Directory where results should be stored',
        required=True)
    parser.add_argument(
        '-n',
        '--n_jobs',
        type=int,
        help='Number of jobs to run on batch',
        required=True)
    parser.add_argument(
        '-dl',
        '--delta_low',
        type=str,
        help='Lower delta mass range',
        required=True)
    parser.add_argument(
        '-dh',
        '--delta_high',
        type=str,
        help='Upper delta mass range',
        required=True)
    parser.add_argument(
        '-bl', '--bu_low', type=str, help='Lower bu mass range', required=True)
    parser.add_argument(
        '-bh',
        '--bu_high',
        type=str,
        help='Upper bu mass range',
        required=True)
    parser.add_argument(
        '-d',
        '--dim',
        type=str,
        help='Dimension of dataset (1/2)',
        required=True)
    args = parser.parse_args()

    input_dir = args.input_dir
    output_dir = args.output_dir
    n_jobs = args.n_jobs
    delta_low = args.delta_low
    delta_high = args.delta_high
    bu_low = args.bu_low
    bu_high = args.bu_high
    dim = args.dim

    if not os.path.isdir(input_dir):
        sys.exit(input_dir + " is not a directory")
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    file_list_pi = []
    file_list_K = []
    for filename in os.listdir(input_dir):
        pass_filename_pi(input_dir + "/" + filename, file_list_pi,
                      dim, delta_low, delta_high, bu_low, bu_high)
        pass_filename_K(input_dir + "/" + filename, file_list_K,
                      dim, delta_low, delta_high, bu_low, bu_high)

    if len(file_list_pi) != len(file_list_K):
        sys.exit("Different number of toys for π and K")

    # rounds down: check if any left at the end
    n_fits_per_job = len(file_list_pi) / n_jobs
    n_remainder = len(file_list_pi) - (n_fits_per_job * n_jobs)

    templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/shell_scripts/fit_1d_piK.sh.tmpl"
    scriptList = []
    for i in range(0, n_jobs + 1):
        if i == n_jobs:
            if n_remainder:
                files_K = ",".join(file_list_K[len(file_list_K) - n_remainder:])
                files_K = ",".join(file_list_K[len(file_list_K) - n_remainder:])
            else:
                continue
        else:
            files_pi = ",".join(
                file_list_pi[i * n_fits_per_job:(i + 1) * n_fits_per_job])
            files_K = ",".join(
                file_list_K[i * n_fits_per_job:(i + 1) * n_fits_per_job])
        scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/tmp/fit_1d_piK_" + str(
            i
        ) + "_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + ".sh"
        substitutions = {
            "nJob":
            i,
            "GCCROOT":
            "/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6",
            "LD_LIBRARY_PATH":
            "/home/rollings/Software/install/lib64:/home/rollings/Software/install/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib:/home/rollings/Software/install/lib:64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib::/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/",
            "FILESPi":
            files_pi,
            "FILESK":
            files_K,
            "PATH":
            output_dir,
            "DELTALOW":
            delta_low,
            "DELTAHIGH":
            delta_high,
            "BULOW":
            bu_low,
            "BUHIGH":
            bu_high
        }
        make_shell_script(templatePath, scriptPath, substitutions)
        scriptList.append(scriptPath)
        # run_process(["qsub", scriptPath])
        # run_process(["nohup", "sh", scriptPath, "> nohup_" + str(i) + ".out"])
        # run_process(["qsub", "-q", "testing", scriptPath])
    if n_remainder == 0:
        n_processes = n_jobs
    else:
        n_processes = n_jobs + 1
    p = mp.Pool(n_processes)
    p.map(run_process, scriptList)
