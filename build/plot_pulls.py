import os, re, subprocess, sys, argparse
#re = regular expressions

def pass_filename(filename, file_list, delta_low, delta_high, bu_low, bu_high):
    m = re.search("Result_0\.[0-9]+_" + delta_low + '_' + delta_high + '_' +
                  bu_low + '_' + bu_high + "\.root", filename)
    if m:
        file_list.append(filename)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-i',
        '--input_dir',
        type=str,
        help='Directory where results are stored',
        required=True)
    parser.add_argument(
        '-o',
        '--output_dir',
        type=str,
        help='Directory where folder for PDFs and results should be created',
        required=True)
    parser.add_argument(
        '-dl',
        '--delta_low',
        type=str,
        help='Lower delta mass range',
        required=True)
    parser.add_argument(
        '-dh',
        '--delta_high',
        type=str,
        help='Upper delta mass range',
        required=True)
    parser.add_argument(
        '-bl',
        '--bu_low',
        type=str,
        help='Lower bu mass range',
        required=True)
    parser.add_argument(
        '-bh',
        '--bu_high',
        type=str,
        help='Upper bu mass range',
        required=True)
    args = parser.parse_args()

    input_dir = args.input_dir
    output_dir = args.output_dir
    delta_low = args.delta_low
    delta_high = args.delta_high
    bu_low = args.bu_low
    bu_high = args.bu_high

    if not os.path.isdir(input_dir):
        sys.exit(input_dir + ' is not a directory')
    file_list = []
    for filename in os.listdir(input_dir):
        pass_filename(input_dir + "/" + filename, file_list, delta_low, delta_high, bu_low, bu_high)
        # pass_filename(input_dir + "/" + filename, file_list)
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    # results_dir = output_dir + '/results'
    # if not os.path.exists(results_dir):
    #     os.mkdir(results_dir)
    plots_dir = output_dir + '/plots'
    if not os.path.exists(plots_dir):
        os.mkdir(plots_dir)
    # print("./PlotToys " + ",".join(file_list))
    # print(file_list)
    subprocess.call([
        "./PlotToys", ",".join(file_list), output_dir
    ])
