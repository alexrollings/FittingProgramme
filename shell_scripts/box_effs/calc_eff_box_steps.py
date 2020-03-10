import os, argparse
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
  parser.add_argument('-l',
                      '--low',
                      type=str,
                      help='Fixed var lower box',
                      required=True)
  parser.add_argument('-u',
                      '--up',
                      type=str,
                      help='Fixed var upper box',
                      required=True)
  parser.add_argument('-s',
                      '--n_steps',
                      type=int,
                      help='Number of steps',
                      required=True)
  parser.add_argument('-i',
                      '--init_eff',
                      type=float,
                      help='Initial efficiency of scan',
                      required=True)
  parser.add_argument('-f',
                      '--final_eff',
                      type=float,
                      help='Final efficiency of scan',
                      required=True)
  args = parser.parse_args()
  neutral = args.neutral
  var = args.var
  low = args.low
  up = args.up
  n_steps = args.n_steps
  init_eff = args.init_eff
  final_eff = args.final_eff

  # Dict for top and bottom eff scans to store key: eff, value: box dimns
  eff_box_dict = {'top': {}, 'bottom': {}}
  # Dict for top and bottom eff scans to store array of effs as floats, and the eff of their product
  effs_dict = {'top': [], 'bottom': []}
  for k, _ in eff_box_dict.items():
    # Create array, where every row is an array of box dimensions and efficiency strings
    lines = [l.rstrip('\n') for l in open(neutral + '_' + var + '_' + k + '_effs.txt')]
    lines = [l.split(':') for l in lines]

    for box_limits, eff in lines:
      effs_dict[k].append(float(eff))
      if eff not in eff_box_dict[k].keys():
        eff_box_dict[k][eff] = box_limits
    lines.clear()

  # Array of efficiency steps desired by user
  # Eff .txt files store effiency of events rejected above and below box
  # To get desired effs, need to find box limits for 1 - that
  steps = np.linspace(start = 1 - init_eff, stop = 1 - final_eff, num = n_steps)
  # Divide desires eff by 2 (of 50% effhalf each side)
  steps = steps * 0.5

  # Dict to store array of desired effs
  chosen_effs_dict = {'top': [], 'bottom': []}
  for k, _ in chosen_effs_dict.items():
    for s in steps:
      # Index of value closest of eff in array closest to desired eff
      idx = (np.abs(effs_dict[k] - s)).argmin()
      # desired eff (to 6 sf to match dict key)
      eff_6sf = str.format('{0:.6f}', effs_dict[k][idx])
      chosen_effs_dict[k].append(eff_6sf)

  # Array to store strings of 'eff: box limits'
  step_list = []
  for i in range(0, len(steps)):
    if var == 'buDelta':
      bl = eff_box_dict['bottom'][chosen_effs_dict['bottom'][i]]
      bh = eff_box_dict['top'][chosen_effs_dict['top'][i]]
      dl = low
      dh = up
    else:
      bl = low
      bh = up
      dl = eff_box_dict['bottom'][chosen_effs_dict['bottom'][i]]
      dh = eff_box_dict['top'][chosen_effs_dict['top'][i]]
    # Desired eff (to 6 sf) is sum of top and bottom effs
    eff_label = str.format(
        '{0:.6f}',
        1.0 - (float(chosen_effs_dict['top'][i]) + float(chosen_effs_dict['bottom'][i])))
    # save eff and corresponding box label using dict key
    step_list.append(eff_label + ":" + bl + " " + bh + " " + dl + " " + dh + "\n")

  # In case of duplicate boxes (don't want to run the same thing more than once)
  unique_steps = sorted(set(step_list))

  # File to store box limits for desired effs
  tex_filename = neutral + '_' + var + '_full_scan.txt'
  if os.path.exists(tex_filename):
      os.remove(tex_filename)

  # Write each entry of unique array to line of file
  outfile = open(tex_filename, 'w+')
  for l in unique_steps:
    outfile.write(l)

