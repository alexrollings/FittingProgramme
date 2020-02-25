import os, re, argparse
import numpy as np

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral=pi0/gamma/partial',
                      required=True)
  parser.add_argument('-v',
                      '--var',
                      type=str,
                      help='Variable=buDelta/delta',
                      required=True)
  parser.add_argument('-s',
                      '--n_steps',
                      type=int,
                      help='Number of steps',
                      required=True)
  parser.add_argument('-dl',
                      '--delta_low',
                      type=int,
                      required=True)
  parser.add_argument('-dh',
                      '--delta_high',
                      type=int,
                      required=True)
  parser.add_argument('-bl',
                      '--bu_low',
                      type=int,
                      required=True)
  parser.add_argument('-bh',
                      '--bu_high',
                      type=int,
                      required=True)
  args = parser.parse_args()
  neutral = args.neutral
  var = args.var
  n_steps = args.n_steps

  if var == 'delta':
    low = args.delta_low
    high = args.delta_high
    fixed_low = args.bu_low
    fixed_high = args.bu_high
  elif var == 'buDelta':
    low = args.bu_low
    high = args.bu_high
    fixed_low = args.delta_low
    fixed_high = args.delta_high
  else:
    sys.exit('var=delta/buDelta')

  # Dict for top and bottom eff scans to store key: eff, value: box dimns
  cut_eff_dict = {'top': {}, 'bottom': {}}

  for k, v in cut_eff_dict.items():
    # Create array, where every row is an array of box dimensions and efficiency strings
    lines = [l.rstrip('\n') for l in open(neutral + '_' + var + '_' + k + '_effs.txt')]
    lines = [l.split(':') for l in lines]

    for cut, eff in lines:
      if cut not in v.keys():
        v[float(cut)] = float(eff)

  # Split dict: get lower values below 138, upper values above 148
  large_cut_dict = {'top': {}, 'bottom': {}}
  large_cut_dict['top'] = {key: value for key, value in cut_eff_dict['top'].items() if key > high}
  large_cut_dict['bottom'] = {key: value for key, value in cut_eff_dict['bottom'].items() if key < low}

  # Split dict: get lower values above 138, upper values below 148
  small_cut_dict = {'top': {}, 'bottom': {}}
  small_cut_dict['top'] = {key: value for key, value in cut_eff_dict['top'].items() if key < high}
  small_cut_dict['bottom'] = {key: value for key, value in cut_eff_dict['bottom'].items() if key > low}

  box_dict = {}

  # # Commented out: create dictionary with closest matches of efficiency in steps of top and bottom cuts
  # # loop over k, v in smallest dict
  # if len(large_cut_dict['bottom']) > len(large_cut_dict['top']):
  #   loop = 'top'
  #   scan = 'bottom'
  # else:
  #   loop = 'bottom'
  #   scan = 'top'
  #
  # for k, v in large_cut_dict[loop].items():
  #   closest_match = min(large_cut_dict[scan],
  #                       key=lambda x: abs(large_cut_dict[scan][x] - v))
  #   box_dict[str(k) + ' ' + str(closest_match)] = str.format(
  #       '{0:.6f}', 1 - (v + large_cut_dict[scan][closest_match]))
  #
  # if len(small_cut_dict['bottom']) > len(small_cut_dict['top']):
  #   loop = 'top'
  #   scan = 'bottom'
  # else:
  #   loop = 'bottom'
  #   scan = 'top'
  #
  # for k, v in small_cut_dict[loop].items():
  #   closest_match = min(small_cut_dict[scan],
  #                       key=lambda x: abs(small_cut_dict[scan][x] - v))
  #   box_dict[str(k) + ' ' + str(closest_match)] = str.format(
  #       '{0:.6f}', 1 - (v + small_cut_dict[scan][closest_match]))

  box_eff = 1.0 - (cut_eff_dict['bottom'][low] + cut_eff_dict['top'][high])

  if box_eff > 0.95:
    up_limit = 1.0
  else:
    up_limit = box_eff + 0.05
  down_limit = box_eff - 0.05

  # Create dictionary with every possible box within efficiency range we want
  effs = []
  for k1, v1 in large_cut_dict['bottom'].items():
    for k2, v2 in large_cut_dict['top'].items():
      tot_eff = 1 - (v1 + v2)
      if tot_eff <= up_limit and tot_eff >= down_limit:
        box_dict[str.format('{0:.6f}', tot_eff)] = str(k1) + ' ' + str(k2)
        effs.append(tot_eff)

  for k1, v1 in small_cut_dict['bottom'].items():
    for k2, v2 in small_cut_dict['top'].items():
      tot_eff = 1 - (v1 + v2)
      if tot_eff <= up_limit and tot_eff >= down_limit:
        box_dict[str.format('{0:.6f}', tot_eff)] = str(k1) + ' ' + str(k2)
        effs.append(tot_eff)

  steps = np.linspace(start = down_limit, stop = up_limit, num = n_steps)

  # Array to store strings of 'eff: box limits'
  step_list = []
  for s in steps:
    # Index of value closest of eff in array closest to desired eff
    idx = (np.abs(effs - s)).argmin()
    # desired eff (to 6 sf to match dict key)
    chosen_eff = str.format('{0:.6f}', effs[idx])
    step_list.append(chosen_eff + ":" + box_dict[chosen_eff] + "\n")

  # In case of duplicate boxes (don't want to run the same thing more than once)
  unique_steps = sorted(set(step_list))

  # File to store box limits for desired effs
  tex_filename = neutral + '_' + var + '_box_limits.txt'
  if os.path.exists(tex_filename):
      os.remove(tex_filename)

  # Write each entry of unique array to line of file
  outfile = open(tex_filename, 'w+')
  for l in unique_steps:
    outfile.write(l)
