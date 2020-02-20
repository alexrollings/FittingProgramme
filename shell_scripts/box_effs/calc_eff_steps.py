import os
import numpy as np
import argparse

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
    args = parser.parse_args()
    neutral = args.neutral
    var = args.var
    n_steps = args.n_steps

    # Create array, where every row is an array of box dimensions and efficiency strings
    lines = [l.rstrip('\n') for l in open(neutral + '_' + var + '_effs.txt')]
    lines = [l.split(':') for l in lines]

    # Dict, key: eff, value: box dimns
    eff_box_dict = {}
    # Array to store effs as floats
    effs = np.zeros(len(lines))
    it = 0
    for box_limits, eff in lines:
        effs[it] = float(eff)
        if eff not in eff_box_dict.keys():
            eff_box_dict[eff] = box_limits
        it = it + 1

    # Array of efficiency steps desired by user
    steps = np.linspace(start = 1, stop = 0, num = n_steps)

    # File to store box limits for desired effs
    tex_filename = neutral + '_' + var + '_box_limits.txt'
    if os.path.exists(tex_filename):
        os.remove(tex_filename)

    # Array to store strings of 'eff: box limits'
    step_list = []
    for s in steps:
      # index of value closest of eff in array closest to desired eff
      idx = (np.abs(effs - s)).argmin()
      # desired eff (to 6 sf to match dict key)
      eff_6sf = str.format('{0:.6f}', effs[idx])
      # save eff and corresponding box label using dict key
      step_list.append(eff_6sf + ":" + eff_box_dict[eff_6sf] + "\n")

    # In case of duplicate boxes (don't want to run the same thing more than once)
    unique_steps = sorted(set(step_list))

    # Write each entry of unique array to line of file
    outfile = open(tex_filename, 'w+')
    for l in unique_steps:
      outfile.write(l)

