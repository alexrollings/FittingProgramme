import re, os, sys
import argparse

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '-p',
      '--path',
      type=str,
      help='Path to condor output files',
      required=True)
  args = parser.parse_args()
  path = args.path

  submit_fname = 'resubmit.sh'
  submit_file = open(os.path.join(path, submit_fname), 'w')
  path = path + '/log/'
  if os.path.isdir(path):
    for fname in os.listdir(path):
      f = open(os.path.join(path, fname), 'r')
      n_lines = len([line for line in f])
      if n_lines < 100:
        submit_file.write('condor_submit ' + fname[:-11] + 'submit\n')
        os.remove(os.path.join(path, fname))
  else:
    sys.exit(f'{path} does not exist')


