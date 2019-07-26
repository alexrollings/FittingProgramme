#!/usr/bin/env python2
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
        help='Directory where datsets should be stored',
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
    args = parser.parse_args()

    output_dir = args.output_dir
    n_toys = args.n_toys
    n_jobs = args.n_jobs
    delta_low = args.delta_low
    delta_high = args.delta_high
    bu_low = args.bu_low
    bu_high = args.bu_high

    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

    templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/shell_scripts/generate_1d.sh.tmpl"
    scriptList = []
    for i in range(0, n_jobs):
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
        make_shell_script(templatePath, scriptPath, substitutions)
        scriptList.append(scriptPath)
        # submit_to_batch(["qsub", scriptPath])
        # submit_to_batch(["nohup", "sh", scriptPath, "> nohup_" + str(i) + ".out"])
        # submit_to_batch(["qsub", "-q", "testing", scriptPath])
    p = mp.Pool(n_jobs)
    p.map(run_process, scriptList)
