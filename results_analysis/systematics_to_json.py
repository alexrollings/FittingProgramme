import math, re, os, sys
from ROOT import TFile, RooFitResult
import root_numpy as r_np
import argparse
import json
from shutil import copyfile

def SaveToFile(fname, json_dict):
  with open(fname, 'w') as json_file:
    json.dump(json_dict, json_file)
  # Make back up file before overwriting again
  copyfile(fname, fname + '.bak')

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
      'R_Dst0KDst0pi_Bu2Dst0h', 'A_Bu2Dst0h', 'A_CP_Bu2Dst0h',
      'BR_pi02gamma_eff'
  ]

  if os.path.isdir(input_dir):
    json_fname = f'{input_dir}/systematics_{neutral}.json'
    # If json file exists, load existing dict
    if os.path.exists(json_fname):
      with open(json_fname, 'r') as json_file:
        json_dict = json.load(json_file)
    # If not, create empty dict
    else:
      json_dict = {}
  else:
    sys.exit(input_dir + ' does not exist.')

  input_dir = input_dir + '/results/'
  if os.path.isdir(input_dir):
    save_count = 0
    file_count = 0
    files = os.listdir(input_dir)
    n_files = len(files)
    for f in files:
      file_count = file_count + 1
      m = re.search(
          f'SystResult_{box_str}((?:_[0-9A-Za-z]+)+)_([a-z0-9]+).root', f)
      # 'SystResult(?:_[0-9]+){4,6}((?:_[0-9A-Za-z]+)+)_[a-z0-9]+.root', f)
      if m:
        syst_label = m.group(1)[1:]
        seed = m.group(2)
        if syst_label not in json_dict:
          json_dict[syst_label] = {}
        if syst_label == 'R_Dst0KDst0pi_Lb2Omegach_Lcpi0':
          json_dict.pop(syst_label)
          continue
        if seed not in json_dict[syst_label]:
          syst_file = TFile(os.path.join(input_dir, f))
          syst_result = syst_file.Get('SystResult')
          if isinstance(syst_result, RooFitResult):
            save_count = save_count + 1
            # Label each result with syst label and seed
            # Save covariance matrix quality and fit status
            json_dict[syst_label][seed] = {'covQual' : syst_result.covQual(), 'fitStatus' : syst_result.status()}
            # Save obs names and values
            for p in syst_result.floatParsFinal():
              for obs in observables:
                par_name = p.GetName()
                m = re.match(obs + '(\S+)_[0-9]+', par_name)
                if m:
                  # Results labelled with different numbers
                  par_name = obs + m.group(1)
                  json_dict[syst_label][seed][par_name] = p.getVal()
            syst_file.Close()
            # Dump to json every 100 files
            if save_count % 100 == 0:
              SaveToFile(json_fname, json_dict)
              print(f'Saved result {file_count} out of {n_files}')
              # if save_count == 1000:
              #   sys.exit()
          else:
            print(f'SystResult not found in {f}')
    print(f'Saved result final {file_count} out of {n_files}')
    SaveToFile(json_fname, json_dict)
  else:
    sys.exit(input_dir + ' does not exist.')
