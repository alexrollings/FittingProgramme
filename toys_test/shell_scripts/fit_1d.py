#!/usr/bin/env python2
import os, re, subprocess, sys, argparse
from string import Template
import subprocess as sp


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

def pass_filename(filename, file_list):
  m = re.search("DataFile_0.[0-9]+.root", filename)
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
        '-bl',
        '--bu_low',
        type=str,
        help='Lower bu mass range',
        required=True)
    parser.add_argument(
        '-bh',
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

    if not os.path.isdir(input_dir):
        sys.exit(input_dir + " is not a directory")
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    file_list = []
    for filename in os.listdir(input_dir):
      pass_filename(input_dir+"/"+filename, file_list)

    # rounds down: check if any left at the end
    n_fits_per_job = len(file_list) / n_jobs
    n_remainder = len(file_list) - (n_fits_per_job * n_jobs)

    templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/shell_scripts/fit_1d.sh.tmpl"
    for i in range(0, n_jobs+1):
        if i == n_jobs:
            if n_remainder:
                files = ",".join(file_list[len(file_list)-n_remainder:])
            else:
                continue
        else:
            files = ",".join(file_list[i*n_fits_per_job:(i+1)*n_fits_per_job])
        scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/tmp/fit_1d_" + str(
            i) + ".sh"
        substitutions = {
            "nJob":
            i,
            "GCCROOT":
            "/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6",
            "LD_LIBRARY_PATH":
            "/home/rollings/Software/install/lib64:/home/rollings/Software/install/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib:/home/rollings/Software/install/lib:64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib::/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/",
            "FILES":
            files,
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
        run_process(["qsub", scriptPath])
