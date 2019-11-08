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
        help='Number of jobs to run on batch for each box dimn',
        required=True)
    parser.add_argument(
        '-i',
        '--input_dir',
        type=str,
        help='Path to RDS of data: required to generate toys from data PDF',
        required=False)
    parser.add_argument(
        '-n',
        '--neutral',
        type=str,
        help='Neutral = pi0/gamma. Optional, otherwise both are set running',
        required=False)
    parser.add_argument('-v',
                        '--var',
                        type=str,
                        help='Variable=buDelta/delta',
                        required=True)
    args = parser.parse_args()

    neutral = args.neutral
    output_dir = args.output_dir
    n_toys = args.n_toys
    n_jobs = args.n_jobs
    input_dir = args.input_dir
    var = args.var

    neutrals = []
    if neutral == None:
        print('Running both neutral modes')
        neutrals.append('pi0')
        neutrals.append('gamma')
    else:
        if neutral != "pi0" and neutral != "gamma":
            sys.exit("Specify neutral: -n=pi0/gamma")
        else:
            neutrals.append(neutral)

    if var != "delta" and var != "buDelta":
        sys.exit("Specify var: -n=delta/buDelta")
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

    home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/'
    templatePath = home_path + 'shell_scripts/run_box_scan.sh.tmpl'

    for neutral in neutrals:
        lines = [l.rstrip('\n') for l in open(home_path + 'shell_scripts/box_effs/' + neutral + '_' + var + '_box_limits.txt')]
        lines = [l.split(':') for l in lines]
        box_limits = []
        for _, box in lines:
            box_limits.append(box)
        split = [l.split(' ') for l in box_limits]
        for box in split:
            bu_low = box[0]
            bu_high = box[1]
            delta_low = box[2]
            delta_high = box[3]

            for i in range(0, n_jobs):
                scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_box_scan_' + neutral + "_" + delta_low + "_" + delta_high + "_" + bu_low + "_" + bu_high + "_"  + str(i) + ".sh"
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
                    bu_high
                }
                make_shell_script(templatePath, scriptPath, substitutions)
                # run_process(["sh", scriptPath])
                run_process(["qsub", scriptPath])