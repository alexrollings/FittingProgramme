#!/usr/bin/env python2
import argparse
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


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-p',
        '--path',
        type=str,
        help='Path to where results should be stored',
        required=True)
    parser.add_argument(
        '-t',
        '--n_toys',
        type=int,
        help='Number of toys per job',
        required=True)
    parser.add_argument(
        '-j',
        '--n_jobs',
        type=int,
        help='Number of jobs to submit',
        required=True)
    args = parser.parse_args()

    path = args.path
    n_toys = args.n_toys
    n_jobs = args.n_jobs

    templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/shell_scripts/batch_submission.sh.tmpl"
    for i in range(0, n_jobs):
        scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/tmp/batch_submission_" + str(
            i) + ".sh"
        substitutions = {
            "PATH":
            path,
            "nToys":
            n_toys,
            "nJob":
            i,
            "GCCROOT":
            "/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6",
            "LD_LIBRARY_PATH":
            "/home/rollings/Software/install/lib64:/home/rollings/Software/install/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib:/home/rollings/Software/install/lib:64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/gcc/4.9.3/x86_64-slc6/lib::/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_88/GSL/2.1/x86_64-slc6-gcc49-opt/lib/"
        }
        make_shell_script(templatePath, scriptPath, substitutions)
        run_process(["qsub", scriptPath])
        # run_process(["qsub", "-q", "testing", scriptPath])
