import os
import numpy as np
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-n',
                        '--neutral',
                        type=str,
                        help='Neutral=pi0/gamma',
                        required=True)
    parser.add_argument('-v',
                        '--var',
                        type=str,
                        help='Variable=buDelta/delta',
                        required=True)
    args = parser.parse_args()
    neutral = args.neutral
    var = args.var

    lines = [l.rstrip('\n') for l in open(neutral + '_' + var + '_effs.txt')]
    lines = [l.split(':') for l in lines]

    eff_box_dict = {}
    effs = np.zeros(len(lines))
    it = 0
    for box_limits, eff in lines:
        effs[it] = float(eff)
        if eff not in eff_box_dict.keys():
            eff_box_dict[eff] = box_limits
        it = it + 1

    steps = np.linspace(start = 1, stop = 0, num = 20)

    tex_filename = neutral + '_' + var + '_box_limits.txt'
    if os.path.exists(tex_filename):
        os.remove(tex_filename)
    outfile = open(tex_filename, 'w+')

    for s in steps:
      idx = (np.abs(effs - s)).argmin()
      eff_6sf = str.format('{0:.6f}', effs[idx])
      outfile.write(eff_6sf + ":" + eff_box_dict[eff_6sf] + "\n")

