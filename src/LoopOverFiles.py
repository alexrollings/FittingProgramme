#!/usr/bin/python

import os, re, subprocess, sys
#re = regular expressions

year = None
polarity = None
bachelor = None
neutral = None
daughters = None

if os.path.isdir(sys.argv[1]):
  for filename in os.listdir(sys.argv[1]):

    m2011 = re.search('2011.*\.root', filename)
    m2012 = re.search('2012.*\.root', filename)
    m2015 = re.search('2015.*\.root', filename)
    if m2011:
      year = 'y2011'
    elif m2012:
      year = 'y2012'
    elif m2015:
      year = 'y2015'
    else:
      sys.exit('Year must be 2011, 2012 or 2015')

    mUp = re.search('[0-9]+_MagUp.*\.root', filename)
    mDown = re.search('[0-9]+_MagDown.*\.root', filename)
    if mUp:
      polarity = 'up'
    elif mDown:
      polarity = 'down'
    else:
      sys.exit('Polarity must be: MagUp or MagDown')

    mK = re.search('.*ButDst0K.*\.root', filename)
    mPi = re.search('.*ButDst0pi.*\.root', filename)
    if mK:
      bachelor = 'k'
    elif mPi:
      bachelor = 'pi'
    else:
      sys.exit('Bachelor must be: pi or K')

    mPi0 = re.search('.*Dst0tD0pi0.*\.root', filename)
    mGamma = re.search('.*Dst0tD0gamma.*\.root', filename)
    if mPi0:
      neutral = 'pi0'
    elif mGamma:
      neutral = 'gamma'
    else:
      sys.exit('Neutral must be: pi0 or gamma')

    mKPi = re.search('.*D0tkpi.*\.root', filename)
    mKK = re.search('.*D0tkk.*\.root', filename)
    mPiPi = re.search('.*D0tpipi.*\.root', filename)
    mPiK = re.search('.*D0tpik.*\.root', filename)
    if mKPi:
      daughters = 'kpi'
    elif mKK:
      daughters = 'kk'
    elif mPiPi:
      daughters = 'pipi'
    elif mPiK:
      daughters = 'pik'
    else:
      sys.exit('D0 Daughters must be: kpi, kk, pipi or pik')

    # print  year
    # print  polarity
    # print  bachelor
    # print  neutral
    # print  daughters

    subprocess.call(["./SaveRooDataSet", sys.argv[1], filename, year, polarity, bachelor, neutral, daughters])
