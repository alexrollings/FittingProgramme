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
    scriptPath = "/home/rollings/Bu2Dst0h_2d/batch_submission.sh"
    for i in range (0, 200):
      run_process(["qsub", scriptPath])

    # args = argparse.ArgumentParser()
    # args.add_argument("path")
    # args = vars(args.parse_args())
    #
    # path = args["path"]
    #
    # templatePath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/shell_scripts/batch_submission.sh.tmpl"
    # scriptPath = "/home/rollings/Bu2Dst0h_2d/FittingProgramme/build/shell_scripts/batch_submission_" + path + ".sh"
    # substitutions = { "PATH": path }
    # make_shell_script(templatePath, scriptPath, substitutions)
    # for i in range (0, 100):
    #   run_process(["qsub", scriptPath])

