import os, subprocess, sys
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-i',
        '--input_dir',
        type=str,
        help='Specify input directory',
        required=True)
    parser.add_argument(
        '-o',
        '--output_dir',
        type=str,
        help='Specify output directory',
        required=True)
    parser.add_argument(
        '-n',
        '--n_jobs',
        type=str,
        help='Number of jobs to run on batch for each box',
        required=True)
    args = parser.parse_args()

    input_dir = args.input_dir
    output_dir = args.output_dir
    n_jobs = args.n_jobs

    if not os.path.exists(input_dir):
        sys.exit(input_dir + " does not exist.")
    if not os.path.exists(output_dir):
        print(output_dir + " does not exist.")
        os.mkdir(output_dir)

    delta_low = 110
    delta_high = 210
    bu_low = 5150
    bu_high = [5310, 5300, 5290, 5280, 5270, 5260, 5250, 5240, 5230, 5220, 5210]
    # bu_high = [5360, 5350, 5340, 5330, 5320, 5310, 5300, 5290, 5280, 5270, 5260, 5250, 5240, 5230, 5220, 5210]

    os.chdir('/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/tmp')
    i = 0
    while i < len(bu_high):
        subprocess.call([
            "./../shell_scripts/fit_1d.py", '-i=' + input_dir,
            '-o=' + output_dir, '-n=' + n_jobs, '-dl=' + str(delta_low),
            '-dh=' + str(delta_high), '-bl=' + str(bu_low),
            '-bh=' + str(bu_high[i])
        ])
        # print(
        #     './../shell_scripts/fit_1d.py -i=' + input_dir + '-o=' +
        #     output_dir + '-n=' + n_jobs + '-dl=' + str(delta_low) + '-dh=' +
        #     str(delta_high) + '-bl=' + str(bu_low) + '-bh=' + str(bu_high[i]))
        i += 1
