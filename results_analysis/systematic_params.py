import re, os, sys, io
import argparse

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-i',
                      '--input_dir',
                      type=str,
                      help='Input: systematic results',
                      required=True)
  args = parser.parse_args()
  input_dir = args.input_dir

  d = {}
  if os.path.isdir(input_dir):
    for f in os.listdir(input_dir):
      m = re.search('ParameterInfo((?:_[A-Za-z]+)+).csv', f)
      if m:
        syst_labels = re.findall('([A-Za-z]+)', m.group(1))
        print(' '.join(syst_labels) + ':')
        for line in open(input_dir + '/' + f, 'r'):
          name = line.strip().split(',')[0]
          d[name] = {
              'Value': line.strip().split(',')[1],
              'Range': line.strip().split(',')[2]
          }

  for par, val_range in d.items():
    print('\t' + par + ':\t' + val_range['Value'] + '\t' + val_range['Range'])
