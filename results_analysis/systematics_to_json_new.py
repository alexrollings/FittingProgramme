import math, re, os, sys
from ROOT import TFile, RooFitResult
import root_numpy as r_np
import argparse
import json, csv
from shutil import copyfile


def SaveToJson(fname, json_dict):
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

  # Read in as json first to make sure every entry is unique!
  if os.path.isdir(input_dir):
    if not os.path.isdir(os.path.join(input_dir, 'format')):
      os.mkdir(os.path.join(input_dir, 'format'))
    json_fname = f'{input_dir}/format/systematics_{neutral}.json'
    # If json file exists, load existing dict
    if os.path.exists(json_fname):
      with open(json_fname, 'r') as json_file:
        json_dict = json.load(json_file)
    # If not, create empty dict
    else:
      json_dict = {}
  else:
    sys.exit(input_dir + ' does not exist.')

  results_dir = os.path.join(input_dir, 'results')
  if os.path.isdir(results_dir):
    save_count = 0
    file_count = 0
    files = os.listdir(results_dir)
    n_files = len(files)
    for f in files:
      file_count = file_count + 1
      m = re.search(
          f'SystResult_{box_str}((?:_[0-9A-Za-z]+)+)_([a-z0-9]+).root', f)
      if m:
        syst_label = m.group(1)[1:]
        seed = m.group(2)
        syst_file = TFile(os.path.join(results_dir, f))
        syst_result = syst_file.Get('SystResult')
        if isinstance(syst_result, RooFitResult):
          save_count = save_count + 1
          for p in syst_result.floatParsFinal():
            for obs in observables:
              par_name = p.GetName()
              m1 = re.match(obs + '(_\S+)_[0-9]+', par_name)
              if m1:
                # Results labelled with different numbers
                end = m1.group(1).replace('_Blind', '')
                par_name = obs + end
                if par_name not in json_dict:
                  json_dict[par_name] = {}
                # Label each result with syst label and seed
                if syst_label not in json_dict[par_name]:
                  json_dict[par_name][syst_label] = {}
                if seed not in json_dict[par_name][syst_label]:
                  # Save covariance matrix quality and fit status
                  json_dict[par_name][syst_label][seed] = {
                      'covQual': syst_result.covQual(),
                      'fitStatus': syst_result.status(),
                      'value': p.getVal()
                  }
          syst_file.Close()
          # Dump to json every 100 files
          if save_count % 100 == 0:
            SaveToJson(json_fname, json_dict)
            print(f'Saved result {file_count} out of {n_files}')
            if save_count == 200:
              break
        else:
          print(f'SystResult not found in {f}')
    print(f'Saved result final {file_count} out of {n_files}')
    SaveToJson(json_fname, json_dict)
    csv_fname = f'{input_dir}/format/systematics_{neutral}.csv'
    with open(csv_fname, 'w', newline='') as csv_file:
      csv_writer = csv.writer(csv_file)
      # writerow takes an iterable argument - would split up string into chars. Create own iterable using split()
      csv_writer.writerow("par,label,seed,val,cov,status".split(','))
      for par_key, par_val in json_dict.items():
        for label_key, label_val in par_val.items():
          for seed_key, seed_val in label_val.items():
            csv_writer.writerow(f"{par_key},{label_key},{seed_key},{seed_val['value']},{seed_val['covQual']},{seed_val['fitStatus']}".split(','))
    print('Formatted to csv.')
  else:
    sys.exit(input_dir + ' does not exist.')
