import os, re, subprocess, sys
import argparse
# import numpy as np

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-mc',
        '--mc',
        action="store_true",
        help='Specify mc if input is Monte Carlo',
        default=False)
    parser.add_argument(
        '-f',
        '--input_file',
        type=str,
        help='Specify input file containing roodataset if running toy',
        required=True)
    parser.add_argument(
        '-o',
        '--output',
        type=str,
        help='Specify output directory',
        required=True)
    args = parser.parse_args()

    output_dir = args.output
    mc = args.mc
    if not mc:
        input_file = args.input_file

    if not mc:
        if not os.path.isfile(input_file):
            sys.exit(input_file + " does not exist.")
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
# if not os.path.exists(output_dir + "/1d_plots"):
#     os.mkdir(output_dir + "/1d_plots")

# 15 bins in each dimension
# delta_low = np.arrange(115, 130, 1)
# delta_high = np.arrange(200, 155, -3)
# bu_low = np.arrange(5200, 5260, 4)
# bu_high = np.arrange(5360, 5300, -4)

# delta_low = [
#     115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
#     129, 130
# ]
# delta_high = [
#     200, 197, 194, 191, 188, 185, 182, 179, 176, 173, 170, 167, 164, 161,
#     158, 155
# ]
    delta_low = [121, 122, 123, 124, 125, 126, 127, 128, 129, 130]
    delta_high = [182, 179, 176, 173, 170, 167, 164, 161, 158, 155]
    bu_low = [
        5200, 5204, 5208, 5212, 5216, 5220, 5224, 5228, 5232, 5236, 5240, 5244,
        5248, 5252, 5256, 5260
    ]
    bu_high = [
        5360, 5356, 5352, 5348, 5344, 5340, 5336, 5332, 5328, 5324, 5320, 5316,
        5312, 5308, 5304, 5300
    ]
    # delta_low = [115, 118, 120, 123, 125, 128, 130, 133, 135, 138, 140]
    # delta_high = [195, 190, 185, 180, 175, 170, 165, 160, 155, 150, 145]
    # bu_low = [5200, 5205, 5210, 5215, 5220, 5225, 5230, 5235, 5240, 5245, 5250, 5255, 5260, 5265, 5270];
    # bu_high = [5360, 5355, 5350, 5345, 5340, 5335, 5330, 5325, 5320, 5315, 5310, 5305, 5300, 5295, 5290];

    if len(delta_low) != len(delta_high):
        sys.exit("delta_low and delta_high are of different lengths")
    if len(bu_low) != len(bu_high):
        sys.exit("bu_low and bu_high are of different lengths")

    i = 0
    while i < len(delta_low):
        j = 0
        while j < len(bu_low):
            if mc:
                subprocess.call([
                    "./SimToy1D_ReadMC", input_file, output_dir,
                    str(delta_low[i]),
                    str(delta_high[i]),
                    str(bu_low[j]),
                    str(bu_high[j])
                ])
            else:
                subprocess.call([
                    "./SimToy1D_ReadDataSet", input_file, output_dir,
                    str(delta_low[i]),
                    str(delta_high[i]),
                    str(bu_low[j]),
                    str(bu_high[j])
                ])
            # print(
            #     "./SimToy1D_ReadDataSet" + " " + input_file + " " + output_dir
            #     + " " + str(delta_low[i]) + " " + str(delta_high[i]) + " " +
            #     str(bu_low[j]) + " " + str(bu_high[j]))
            j += 1
        i += 1
