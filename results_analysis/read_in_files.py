import os, re, subprocess, sys
#re = regular expressions

def pass_filename(filename, file_list):
  m = re.search("ResultFile0.[0-9]+.root", filename)
  if m:
    file_list.append(filename)

if os.path.isdir(sys.argv[1]):
  output_dir = sys.argv[1] + "/plots"
  if not os.path.exists(output_dir):
    os.mkdir(output_dir)
  file_list = []
  for filename in os.listdir(sys.argv[1]):
    pass_filename(sys.argv[1]+"/"+filename, file_list)
  subprocess.call([
      "./PlotToys", ",".join(file_list), output_dir
  ])
  # print("./FitManyToys " + ",".join(file_list))
else:
  print(sys.argv[1] + "is not a directory")
