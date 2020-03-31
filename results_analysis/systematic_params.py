import re, os, sys, io
import argparse

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-i',
                      '--input_dir',
                      type=str,
                      help='Input: systematic results',
                      required=True)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral: pi0/gamma',
                      required=True)
  args = parser.parse_args()
  input_dir = args.input_dir
  neutral = args.neutral

  d = {}
  systematics = []
  if os.path.isdir(input_dir):
    for f in os.listdir(input_dir):
      m = re.search('ParameterInfo((?:_[0-9A-Za-z]+)+).csv', f)
      if m:
        syst_labels = re.findall('([0-9A-Za-z]+)', m.group(1))
        syst = ' '.join(syst_labels)
        if syst not in systematics:
          systematics.append(syst)
        for line in open(input_dir + '/' + f, 'r'):
          name = line.strip().split(',')[0]
          bachelor = line.strip().split(',')[2]
          d[neutral + ':' + syst + ':' + name + ':' + bachelor] = {
              'Value': line.strip().split(',')[3],
              'Range': line.strip().split(',')[4]
          }

  tex_file = open(
      f"/home/rollings/Bu2Dst0h_2d/FittingProgramme/results_analysis/tex/Parameters_{neutral}.tex",
      "w")
  tex_file.write("\\documentclass[12pt, portrait]{article}\n")
  tex_file.write("\\usepackage[landscape, margin=0.1in]{geometry}\n")
  tex_file.write("\\usepackage{float}\n")
  tex_file.write("\\restylefloat{table}\n")
  tex_file.write("\\begin{document}\n")

  for syst in systematics:
    row_arr = []
    for k, v in d.items():
      if syst == k.split(':')[1]:
        name = k.split(':')[2].replace('_', '\\_')
        bachelor = k.split(':')[3]
        val = v['Value']
        std = v['Range']
        row_arr.append(f'{name} {bachelor} & {val} & {std} \\\\\n')

    tex_file.write("\\begin{table}[t]\n")
    tex_file.write("\\centering\n")
    tex_file.write("\\begin{tabular}{l l l}\n")
    tex_file.write("\\hline\n")
    tex_file.write(' Parameter & Starting Value & Range \\\\ \\hline\n')
    for row in row_arr:
      tex_file.write(row)
    tex_file.write("\\caption{Parameters for systematic group " + syst + ".}\n")
    tex_file.write("\\end{tabular}\n")
    tex_file.write("\\end{table}\n")

  tex_file.write("\\end{document}")
  tex_file.close()

