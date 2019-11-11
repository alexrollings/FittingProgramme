import os, re, subprocess, sys, argparse

#re = regular expressions


def pass_filename(filename,
                      file_list,
                      dim,
                      delta_low,
                      delta_high,
                      bu_low=None,
                      bu_high=None):
    if bu_low != None and bu_high != None:
        m = re.search('Result' + dim + '_' + delta_low + '_' + delta_high +
                      '_' + bu_low + '_' + bu_high + '_0\.[0-9]+\.root',
                      filename)
    else:
        m = re.search('Result' + dim + '_' + delta_low + '_' + delta_high +
                      '_0\.[0-9]+\.root', filename)
    if m:
        file_list.append(filename)


def pass_filename_bu_partial(filename,
                        file_list,
                        dim,
                        delta_low,
                        delta_high,
                        delta_partial_low,
                        delta_partial_high,
                        bu_low=None,
                        bu_high=None):
    if bu_low != None and bu_high != None:
        m = re.search('Result' + dim + '_' + delta_partial_low + '_' +
                      delta_partial_high + '_' + delta_low + '_' + delta_high +
                      '_' + bu_low + '_' + bu_high + '_0\.[0-9]+\.root',
                      filename)
    else:
        m = re.search(
            'Result' + dim + '_' + delta_partial_low + '_' + delta_partial_high
            + '_' + delta_low + '_' + delta_high + '_0\.[0-9]+\.root',
            filename)
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
        '-d', '--dim', type=str, help='Dimension', required=True)
    parser.add_argument(
        '-n', '--neutral', type=str, help='Neutral', required=True)
    parser.add_argument(
        '-t',
        '--toy_init',
        type=str,
        help='Toy initiated from model or data values',
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
        '-dpl',
        '--delta_partial_low',
        type=str,
        help='Lower delta_partial mass range',
        required=False)
    parser.add_argument(
        '-dph',
        '--delta_partial_high',
        type=str,
        help='Upper delta_partial mass range',
        required=False)
    parser.add_argument(
        '-bl',
        '--bu_low',
        type=str,
        help='Lower bu mass range',
        required=False)
    parser.add_argument(
        '-bh',
        '--bu_high',
        type=str,
        help='Upper bu mass range',
        required=False)
    args = parser.parse_args()

    input_dir = args.input_dir
    output_dir = args.output_dir
    neutral = args.neutral
    toy_init = args.toy_init
    delta_low = args.delta_low
    delta_high = args.delta_high
    delta_partial_low = args.delta_partial_low
    delta_partial_high = args.delta_partial_high
    bu_low = args.bu_low
    bu_high = args.bu_high
    dim = args.dim

    if dim == "D1D":
        print("Analysing results from D1D toys")
        if bu_low == None or bu_high == None:
            sys.exit("Specify -bl= and -bh=")
    elif dim == "2D":
        print("Analysing results from 2D toys")
        if bu_low == None or bu_high == None:
            sys.exit("Specify -bl= and -bh=")
    elif dim == "1D":
        print("Analysing results from 1D toys")
    else:
        sys.exit("Set -d=1D/D1D/2D")

    if toy_init == "data":
        print("Initial param values taken from final data fit")
    elif toy_init == "model":
        print("Initial param values taken from model")
    else:
        sys.exit(
            "Initial toy parameters taken from model/data fit: -t=model/data")

    if neutral != "pi0" and neutral != "gamma":
        sys.exit("Specify neutral: -n=pi0/gamma")

    fit_bu_partial = False;
    if neutral == "gamma" and delta_partial_low != None and delta_partial_high != None:
        fit_bu_partial = True;

    if not os.path.isdir(input_dir):
        sys.exit(input_dir + ' is not a directory')
    file_list = []
    for filename in os.listdir(input_dir):
        if dim == "1D":
            if fit_bu_partial == False:
                pass_filename(input_dir + "/" + filename, file_list, dim,
                                  delta_low, delta_high)
            else:
                pass_filename_bu_partial(input_dir + "/" + filename, file_list, dim,
                                    delta_low, delta_high, delta_partial_low,
                                    delta_partial_high)
        else:
            if fit_bu_partial == False:
                pass_filename(input_dir + "/" + filename, file_list, dim,
                                  delta_low, delta_high, bu_low, bu_high)
            else:
                pass_filename_bu_partial(input_dir + "/" + filename, file_list, dim,
                                    delta_low, delta_high, delta_partial_low,
                                    delta_partial_high, bu_low, bu_high)
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
    if len(file_list) != 0:
        if dim == "1D":
            if fit_bu_partial == False:
                subprocess.call([
                    "./PlotToys", "-neutral=" + neutral,
                    "-files=" + (",".join(file_list)), "-outputDir=" + output_dir,
                    "-1D", "-toyInit=" + toy_init
                ])
            else:
                subprocess.call([
                    "./PlotToys", "-neutral=" + neutral,
                    "-files=" + (",".join(file_list)), "-outputDir=" + output_dir,
                    "-1D", "-toyInit=" + toy_init, "-buPartial"
                ])
        else:
            if fit_bu_partial == False:
                subprocess.call([
                    "./PlotToys", "-neutral=" + neutral,
                    "-files=" + (",".join(file_list)), "-outputDir=" + output_dir,
                    "-toyInit=" + toy_init
                ])
            else:
                subprocess.call([
                    "./PlotToys", "-neutral=" + neutral,
                    "-files=" + (",".join(file_list)), "-outputDir=" + output_dir,
                    "-toyInit=" + toy_init, "-buPartial"
                ])
    else:
        sys.exit("File list empty")
