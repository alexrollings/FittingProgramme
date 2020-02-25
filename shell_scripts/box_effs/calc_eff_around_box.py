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
  parser.add_argument('-r',
                      '--eff_range',
                      type=float,
                      help='Range of efficiencies to scan over',
                      required=True)
  parser.add_argument('-dl', '--delta_low', type=int, required=True)
  parser.add_argument('-dh', '--delta_high', type=int, required=True)
  parser.add_argument('-bl', '--bu_low', type=int, required=True)
  parser.add_argument('-bh', '--bu_high', type=int, required=True)

  args = parser.parse_args()
  neutral = args.neutral
  var = args.var
  n_steps = args.n_steps
  eff_range = args.eff_range

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

  # Create array, where every row is an array of box dimensions and efficiency strings
  lines = [
      l.rstrip('\n')
      for l in open(neutral + '_' + var + '_boxEffs.txt')
  ]
  lines = [l.split(':') for l in lines]

  # Dict to store key: eff, value: box dimns
  eff_box_dict = {}
  # Array of effs as floats
  all_effs = []

  for box_limits, eff in lines:
    if box_limits == (str(low) + " " + str(high)):
      chosen_eff = eff
    all_effs.append(float(eff))
    if eff not in eff_box_dict.keys():
      eff_box_dict[eff] = box_limits

  # Array of efficiency steps desired by user
  steps = np.linspace(start=float(chosen_eff) - eff_range,
                      stop=float(chosen_eff) + eff_range,
                      num=n_steps)

  # Array of desired effs
  effs = []
  for s in steps:
    # Index of value closest of eff in array closest to desired eff
    idx = (np.abs(all_effs - s)).argmin()
    # desired eff (to 6 sf to match dict key)
    eff_6sf = str.format('{0:.6f}', all_effs[idx])
    effs.append(eff_6sf)

  # Array to store strings of 'eff: box limits'
  step_list = []
  if var == 'buDelta':
    box_string = str(low) + " " + str(high) + " " + str(fixed_low) + " " + str(fixed_high)
  else:
    box_string = str(fixed_low) + " " + str(fixed_high) + " " + str(low) + " " + str(high)
  step_list.append(chosen_eff + ":" + box_string + "\n")
  for i in range(0, len(steps)):
    # Extract correct box limits using regex
    match = re.search("([0-9].+) ([0-9].+)", eff_box_dict[effs[i]])
    if var == 'buDelta':
      bl = match.group(1)
      bh = match.group(2)
      dl = str(fixed_low)
      dh = str(fixed_high)
    else:
      dl = match.group(1)
      dh = match.group(2)
      bl = str(fixed_low)
      bh = str(fixed_high)
    # Desired eff (to 6 sf) is sum of top and bottom effs
    # save eff and corresponding box label using dict key
    step_list.append(effs[i] + ":" + bl + " " + bh + " " + dl + " " + dh +
                     "\n")

  # In case of duplicate boxes (don't want to run the same thing more than once)
  unique_steps = sorted(set(step_list))

  # File to store box limits for desired effs
  tex_filename = neutral + '_' + var + '_box_limits_new.txt'
  if os.path.exists(tex_filename):
    os.remove(tex_filename)

  # Write each entry of unique array to line of file
  outfile = open(tex_filename, 'w+')
  for l in unique_steps:
    outfile.write(l)
