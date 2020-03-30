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
  n = []
  syst = []
  if os.path.isdir(input_dir):
    for f in os.listdir(input_dir):
      m = re.search('ParameterInfo((?:_[A-Za-z]+)+).csv', f)
      if m:
        syst_labels = re.findall('([A-Za-z]+)', m.group(1))
        s = ' '.join(syst_labels)
        if s not in syst:
          syst.append(s)
        for line in open(input_dir + '/' + f, 'r'):
          name = line.strip().split(',')[0]
          neutral = line.strip().split(',')[1]
          if neutral not in n:
            n.append(neutral)
          bachelor = line.strip().split(',')[2]
          d[neutral + ':' + s + ':' + name + ':' + bachelor] = {
              'Value': line.strip().split(',')[3],
              'Range': line.strip().split(',')[4]
          }

  for neutral in n:
    print(neutral + ":")
    for s in syst:
      print("\t" + s + ":")
      for k, v in d.items():
        if neutral == k.split(':')[0]:
          if s == k.split(':')[1]:
            name = k.split(':')[2]
            bachelor = k.split(':')[3]
            if bachelor != "":
              print('\t\t' + name + " " + bachelor + '\t' + v['Value'] + '\t' + v['Range'])
            else:
              print('\t\t' + name + '\t\t' + v['Value'] + '\t' + v['Range'])
