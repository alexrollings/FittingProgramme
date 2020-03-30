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
              'Neutral': line.strip().split(',')[1],
              'Bachelor': line.strip().split(',')[2],
              'Value': line.strip().split(',')[3],
              'Range': line.strip().split(',')[4]
          }

  for k, v in d.items():
    if v['Neutral'] == 'pi0':
      if v['Bachelor'] != "":
        print('\t' + k + " " + v['Bachelor'] + ':\t' + v['Value'] + '\t' + v['Range'])
      else:
        print('\t' + k + ':\t\t' + v['Value'] + '\t' + v['Range'])
    else:
      if v['Bachelor'] != "":
        print('\t' + k + " " + v['Bachelor'] + ':\t' + v['Value'] + '\t' + v['Range'])
      else:
        print('\t' + k + ':\t\t' + v['Value'] + '\t' + v['Range'])
