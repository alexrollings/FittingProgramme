#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import os, re, subprocess, sys, argparse
from string import Template
import subprocess as sp


def run_process(command):
  p = sp.Popen(command)
  p.wait()
  return p.returncode


def make_shell_script(templatePath, scriptPath, substitutions):
  with open(templatePath, 'r') as templateFile:
    scriptTemplate = Template(templateFile.read())
    # Define each variable required by the template
    # Substitute into the string
    scriptString = scriptTemplate.substitute(substitutions)
    # Write to an output file
    with open(scriptPath, 'w') as scriptFile:
      scriptFile.write(scriptString)


if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-q',
                      '--queue',
                      type=str,
                      help='queue = batch/condor',
                      required=True)
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
  # parser.add_argument('-o',
  #                     '--output_dir',
  #                     type=str,
  #                     help='Directory where results should be stored',
  #                     required=True)
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
  parser.add_argument('-g',
                      '--gen',
                      type=str,
                      help='-d=pdfD1D, pdf2D, data2D, data1D',
                      required=True)
  parser.add_argument(
      '-i',
      '--input_dir',
      type=str,
      help='Path to RDS of data: required to generate toys from data PDF',
      required=False)
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
  parser.add_argument('-com',
                      '--commit',
                      type=str,
                      help='git commit label',
                      required=True)
  args = parser.parse_args()

  queue = args.queue
  commit = args.commit
  neutral = args.neutral
  daughters = args.daughters
  charge = args.charge
  # output_dir = args.output_dir
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

  if queue == 'batch':
    print('Running toys on batch')
  elif queue == 'condor':
    print('Running toys on condor')
  else:
    sys.exit('--queue=batch/condor')

  if charge == 'total':
    print('Running toys summed over charge')
    c_str = ''
  elif charge == 'plus,minus':
    print('Running toys split by charge')
    c_str = '_split'
  else:
    sys.exit('--charge=total/plus,minus')

  if gen == 'pdfD1D':
    print('Running toys generated from D1D PDF')
    g_str = 'd1d_pdf'
  elif gen == 'pdf2D':
    print('Running toys generated from 2D PDF')
    g_str = '2d_pdf'
  elif gen == 'data2D':
    print('Running toys generated from 2D data')
    g_str = '2d_data'
  elif gen == 'data1D':
    print('Running toys generated from 1D data')
    g_str = '1d_data'
  else:
    sys.exit('-gen=pdfD1D/pdf2D/data2D/data1D')

  if neutral != 'pi0' and neutral != 'gamma':
    sys.exit('Specify neutral: -n=pi0/gamma')

  if daughters != 'kpi' and daughters != 'kpi,kk' and daughters != 'kpi,kk,pipi' and daughters != 'kpi,kk,pipi,pik':
    sys.exit('Specify daughters: -d=kpi/kpi,kk/kpi,kk,pipi/kpi,kk,pipi,pik')
  d_arr = daughters.split(',')
  d_str = d_arr[-1]

  path = '/data/lhcb/users/rollings/roofit_results_new/'
  sub_dirs = [
      g_str, g_str + '/' + commit, g_str + '/' + commit + '/' + d_str + c_str,
      g_str + '/' + commit + '/' + d_str + c_str + '/' + neutral,
      g_str + '/' + commit + '/' + d_str + c_str + '/' + neutral + '/results/'
  ]
  for d in sub_dirs:
    new_dir = os.path.join(path, d)
    if not os.path.exists(new_dir):
      os.mkdir(new_dir)

  output_dir = path + '/' + g_str + '/' + commit + '/' + d_str + c_str + '/' + neutral
  results_dir = os.path.join(output_dir, 'results')
  for filename in os.listdir(results_dir):
    os.remove(os.path.join(results_dir, filename))

  if neutral == 'pi0':
    if delta_low == None:
      delta_low = '138'
    if delta_high == None:
      delta_high = '148'
    if bu_low == None:
      bu_low = '5220'
    if bu_high == None:
      bu_high = '5330'
    if delta_partial_low == None:
      delta_partial_low = '0'
    if delta_partial_high == None:
      delta_partial_high = '0'
  elif neutral == 'gamma':
    if delta_low == None:
      delta_low = '125'
    if delta_high == None:
      delta_high = '170'
    if bu_low == None:
      bu_low = '5240'
    if bu_high == None:
      bu_high = '5320'
    if delta_partial_low == None:
      delta_partial_low = '60'
    if delta_partial_high == None:
      delta_partial_high = '105'

  home_path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/'
  for i in range(0, n_jobs):
    templatePath = home_path + 'shell_scripts/run_toys.sh.tmpl'
    scriptPath = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_toys_' + commit + '_' + gen + '_' + neutral + '_' + daughters + '_' + charge + '_' + delta_low + '_' + delta_high + '_' + delta_partial_low + '_' + delta_partial_high + '_' + bu_low + '_' + bu_high + '_' + str(
        i) + '.sh'
    substitutions = {
        'nJob': i,
        'INPUT': input_dir,
        'PATH': output_dir,
        'COMMIT': commit,
        'GEN': gen,
        'NEUTRAL': neutral,
        'DAUGHTERS': daughters,
        'CHARGE': charge,
        'NTOYS': n_toys,
        'DL': delta_low,
        'DH': delta_high,
        'DPL': delta_partial_low,
        'DPH': delta_partial_high,
        'BL': bu_low,
        'BH': bu_high,
    }
    make_shell_script(templatePath, scriptPath, substitutions)
    if queue == 'batch':
      run_process(['qsub', scriptPath])
    else:
      run_process(['chmod', '+x', scriptPath])
      submitTemplate = home_path + 'shell_scripts/run_toys_submit.sh.tmpl'
      submitScript = '/data/lhcb/users/rollings/fitting_scripts/tmp/run_toys_' + commit + '_' + gen + '_' + neutral + '_' + daughters + '_' + charge + '_' + delta_low + '_' + delta_high + '_' + delta_partial_low + '_' + delta_partial_high + '_' + bu_low + '_' + bu_high + '_' + str(
          i) + '.submit'
      submitSubs = {
          'nJob': i,
          'GEN': gen,
          'COMMIT': commit,
          'NEUTRAL': neutral,
          'DAUGHTERS': daughters,
          'CHARGE': charge,
          'NTOYS': n_toys,
          'DL': delta_low,
          'DH': delta_high,
          'DPL': delta_partial_low,
          'DPH': delta_partial_high,
          'BL': bu_low,
          'BH': bu_high,
          'CLUSTERID': '$(ClusterId)'
      }
      make_shell_script(submitTemplate, submitScript, submitSubs)
      run_process(['condor_submit', submitScript])
