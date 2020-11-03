import math, re, os, sys
from ROOT import TFile, RooFitResult
import root_numpy as r_np
import argparse
import json
from shutil import copyfile

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '-i',
      '--input_dir',
      type=str,
      help='Directory where data and systematic results are stored',
      required=True)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral: pi0/gamma',
                      required=True)
  args = parser.parse_args()
  input_dir = args.input_dir
  neutral = args.neutral

  if neutral == 'pi0':
    box_str = '138_148_5220_5330'
  else:
    box_str = '60_105_125_170_5240_5320'

  # obs_match we are interested have this stem (match with regex)
  observables = [
      'N_tot_Bu2Dst0h', 'R_piK_Bu2Dst0h', 'R_CP_Bu2Dst0h',
      'R_Dst0KDst0pi_Bu2Dst0h', 'A_Bu2Dst0h', 'A_CP_Bu2Dst0h'
  ]

  if os.path.isdir(input_dir):
    json_fname = f'{input_dir}/systematics_{neutral}.json'
    # If json file exists, load existing dict
    if os.path.exists(json_fname):
      with open(json_fname) as json_file:
        json_dict = json.load(json_file)
      json_file.close()
    # If not, create empty dict
    else:
        json_dict = {}
  else:
    sys.exit(input_dir + ' does not exist.')

  input_dir = input_dir + '/results/'
  with open(json_fname, 'w') as json_file:
    if os.path.isdir(input_dir):
      count = 0
      for f in os.listdir(input_dir):
        m = re.search(
            'SystResult_' + box_str + '((?:_[0-9A-Za-z]+)+)_([a-z0-9]+).root', f)
            # 'SystResult(?:_[0-9]+){4,6}((?:_[0-9A-Za-z]+)+)_[a-z0-9]+.root', f)
        if m:
          syst_label = m.group(1)[1:]
          seed = m.group(2)
          if syst_label not in json_dict:
            json_dict[syst_label] = {}
          if seed not in json_dict[syst_label]:
            count = count + 1
            syst_file = TFile(os.path.join(input_dir, f))
            syst_result = syst_file.Get('SystResult')
            # Label each result with syst label and seed
            # Save covariance matrix quality and fit status
            json_dict[syst_label][seed] = {'covQual' : syst_result.covQual(), 'fitStatus' : syst_result.status()}
            # Save obs names and values
            for p in syst_result.floatParsFinal():
              for obs in observables:
                par_name = p.GetName()[:-2]
                m = re.match(obs + '(_[A-Za-z][0-9])+', par_name)
                if m:
                  json_dict[syst_label][seed][par_name] = p.getVal()
            # Dump to json every 100 files
            if count == 100:
              print('Saving to json')
              json.dump(json_dict, json_file)
              # Make back up file before overwriting again
              copyfile(json_fname, json_fname + '.bak')
              count = 0
    else:
      sys.exit(input_dir + ' does not exist.')


