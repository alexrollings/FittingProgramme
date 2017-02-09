#!/usr/bin/python
# m = re.search("([^_]+)_([^_]+)_([^_]+)_([^_]+)_([^_]+).root", filename)
# year, polarity, bachelor, neutral, daughters = m.groups()
# assigns variables to list of groups from regex (excluding 0th group)
# python will assign variables correspondently if you pass the list to the correct number of variables

#Script to loop over files in a directory and pass names and arguments to SaveRooDataSet or pass a single file

import os, re, subprocess, sys
#re = regular expressions

def pass_filename(filename):

  # m = re.search("/([^_/]+)_([^_/]+)_([^_/]+)_([^_/]+)_([^_/]+)_[a-zA-Z0-9_]+_[a-zA-Z0-9_]+_[a-zA-Z0-9_]+_[a-zA-Z0-9_]+.root", filename)
  #regex says if not an "_" or a "/", it is a group
  m = re.search("/([^_/]+)_([^_/]+)_([^_/]+)_([^_/]+)_([^_/]+)_[a-zA-Z0-9_]+_[a-zA-Z0-9_]+_[a-zA-Z0-9_]+.root", filename)

  if m:

    if not m.group(1) in ["2011", "2012", "2015", "2016"]:
      sys.exit("Year must be 2011, 2012, 2015 or 2016")
    year = m.group(1)
    #variables declared in python still exist out of scope

    if m.group(2) == "MagUp":
      polarity = "up"
    elif m.group(2) == "MagDown":
      polarity = "down"
    else:
      sys.exit("Polarity must be: MagUp or MagDown")

    if m.group(3) == "ButDst0K":
      bachelor = "k"
    elif m.group(3) == "ButDst0pi":
      bachelor = "pi"
    else:
      sys.exit("Bachelor must be: pi or K")

    if m.group(4) == "Dst0tD0pi0":
      neutral = "pi0"
    elif m.group(4) == "Dst0tD0gamma":
      neutral = "gamma"
    else:
      sys.exit("Neutral must be: pi0 or gamma")

    if m.group(5) == "D0tkpi":
      daughters = "kpi"
    elif m.group(5) == "D0tkk":
      daughters = "kk"
    elif m.group(5) == "D0tpipi":
      daughters = "pipi"
    elif m.group(5) == "D0tpik":
      daughters = "pik"
    else:
      sys.exit("D0 Daughters must be: kpi, kk, pipi or pik")

    # print(filename, year, polarity, bachelor, neutral, daughters)
    subprocess.call(["../build/./SaveRooDataSet", filename, year, polarity, bachelor, neutral, daughters])

if os.path.isdir(sys.argv[1]):
  for filename in os.listdir(sys.argv[1]):
    pass_filename(sys.argv[1]+"/"+filename)
else:
  pass_filename(sys.argv[1])
