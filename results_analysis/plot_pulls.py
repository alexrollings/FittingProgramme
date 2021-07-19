import os, re, subprocess, sys, argparse

#re = regular expressions


def pass_filename(root_file,
                  list_file,
                  dim,
                  delta_low,
                  delta_high,
                  bu_low=None,
                  bu_high=None):
  if bu_low != None and bu_high != None:
    m = re.search(
        'Result' + dim + '_' + delta_low + '_' + delta_high + '_' + bu_low +
        '_' + bu_high + '_[a-z0-9]+\.root', root_file)
  else:
    m = re.search(
        'Result' + dim + '_' + delta_low + '_' + delta_high +
        '_[a-z0-9]+\.root', root_file)
  if m:
    list_file.write(root_file + '\n')
    # print(root_file)
  # else:
    # print('Result' + dim + '_' + delta_low + '_' + delta_high + '_' + bu_low +
    #     '_' + bu_high + '_0\.[0-9]+\.root')
    # print(root_file)


def pass_filename_bu_partial(root_file,
                             list_file,
                             dim,
                             delta_low,
                             delta_high,
                             delta_partial_low,
                             delta_partial_high,
                             bu_low=None,
                             bu_high=None):
  if bu_low != None and bu_high != None:
    m = re.search(
        'Result' + dim + '_' + delta_partial_low + '_' + delta_partial_high +
        '_' + delta_low + '_' + delta_high + '_' + bu_low + '_' + bu_high +
        '_[a-z0-9]+\.root', root_file)
  else:
    m = re.search(
        'Result' + dim + '_' + delta_partial_low + '_' + delta_partial_high +
        '_' + delta_low + '_' + delta_high + '_[a-z0-9]+\.root', root_file)
  if m:
    list_file.write(root_file + '\n')


if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  # parser.add_argument('-i',
  #                     '--input_dir',
  #                     type=str,
  #                     help='Directory where results are stored',
  #                     required=True)
  # parser.add_argument(
  #     '-o',
  #     '--output_dir',
  #     type=str,
  #     help='Directory where folder for PDFs and results should be created',
  #     required=True)
  parser.add_argument('-com',
                      '--commit',
                      type=str,
                      help='git commit label',
                      required=True)
  parser.add_argument('-d', '--dim', type=str, help='Dimension', required=True)
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral',
                      required=True)
  parser.add_argument('-c',
                      '--charge',
                      type=str,
                      help='charge',
                      required=True)
  parser.add_argument('-d',
                      '--daughters',
                      type=str,
                      help='daughters',
                      required=True)
  parser.add_argument('-t',
                      '--toy_init',
                      type=str,
                      help='Toy initiated from model or data values',
                      required=True)
  parser.add_argument('-dl',
                      '--delta_low',
                      type=str,
                      help='Lower delta mass range',
                      required=False)
  parser.add_argument('-dh',
                      '--delta_high',
                      type=str,
                      help='Upper delta mass range',
                      required=False)
  parser.add_argument('-dpl',
                      '--delta_partial_low',
                      type=str,
                      help='Lower delta_partial mass range',
                      required=False)
  parser.add_argument('-dph',
                      '--delta_partial_high',
                      type=str,
                      help='Upper delta_partial mass range',
                      required=False)
  parser.add_argument('-bl',
                      '--bu_low',
                      type=str,
                      help='Lower bu mass range',
                      required=False)
  parser.add_argument('-bh',
                      '--bu_high',
                      type=str,
                      help='Upper bu mass range',
                      required=False)
  parser.add_argument('--remake',
                      dest='remake',
                      action='store_true',
                      required=False)
  args = parser.parse_args()

  # input_dir = args.input_dir
  # output_dir = args.output_dir
  commit = args.commit
  neutral = args.neutral
  charge = args.charge
  daughters = args.daughters
  toy_init = args.toy_init
  delta_low = args.delta_low
  delta_high = args.delta_high
  delta_partial_low = args.delta_partial_low
  delta_partial_high = args.delta_partial_high
  bu_low = args.bu_low
  bu_high = args.bu_high
  dim = args.dim
  remake = args.remake

  if charge == 'total':
    print('Running toys summed over charge')
    c_str = ''
  elif charge == 'plus,minus':
    print('Running toys split by charge')
    c_str = '_split'
  else:
    sys.exit('--charge=total/plus,minus')

  if dim == 'D1D':
    print('Analysing results from D1D toys')
    g_str = 'd1d_pdf'
  elif dim == '2D':
    print('Analysing results from 2D toys')
    g_str = '2d_data'
  elif dim == '1D':
    print('Analysing results from 1D toys')
    g_str = '1d_pdf'
  else:
    sys.exit('Set -d=1D/D1D/2D')

  if toy_init == 'data':
    print('Initial param values taken from final data fit')
  elif toy_init == 'model':
    print('Initial param values taken from model')
  else:
    sys.exit('Initial toy parameters taken from model/data fit: -t=model/data')

  if neutral != 'pi0' and neutral != 'gamma':
    sys.exit('Specify neutral: -n=pi0/gamma')

  if daughters != 'kpi' and daughters != 'kpi,kk' and daughters != 'kpi,kk,pipi' and daughters != 'kpi,kk,pipi,pik':
    sys.exit('Specify daughters: -d=kpi/kpi,kk/kpi,kk,pipi/kpi,kk,pipi,pik')
  d_arr = daughters.split(',')
  d_str = d_arr[-1]

  input_dir = path + '/' + g_str + '/' + commit + '/' + d_str + c_str + '/' + neutral + '/results/'
  path = '/home/rollings/Bu2Dst0h_2d/FittingProgramme/results/new_data/toys/'
  sub_dirs = [
      g_str, g_str + '/' + commit, g_str + '/' + commit + '/' + d_str + c_str,
      g_str + '/' + commit + '/' + d_str + c_str + '/' + neutral,
      g_str + '/' + commit + '/' + d_str + c_str + '/' + neutral + '/results/',
      g_str + '/' + commit + '/' + d_str + c_str + '/' + neutral + '/plots/'
  ]
  for d in sub_dirs:
    new_dir = os.path.join(path, d)
    if not os.path.exists(new_dir):
      os.mkdir(new_dir)
  output_dir = path + '/' + g_str + '/' + commit + '/' + d_str + c_str + '/' + neutral

  if neutral == "gamma":
    if delta_low == None:
      delta_low = "125"
    if delta_high == None:
      delta_high = "170"
    if delta_partial_low == None:
      delta_partial_low = "60"
    if delta_partial_high == None:
      delta_partial_high = "105"
    if bu_low == None:
      bu_low = "5240"
    if bu_high == None:
      bu_high = "5320"
  else:
    if delta_low == None:
      delta_low = "138"
    if delta_high == None:
      delta_high = "148"
    if bu_low == None:
      bu_low = "5220"
    if bu_high == None:
      bu_high = "5330"

  # current_dir = os.getcwd()
  fit_bu_partial = False
  filename = input_dir + '/list_file_' + neutral + '_' + delta_low + '_' + delta_high + '_' + bu_low + '_' + bu_high + '.txt'
  if neutral == 'gamma' and delta_partial_low != None and delta_partial_high != None:
    fit_bu_partial = True
    filename = input_dir + '/list_file_' + neutral + '_' + delta_partial_low + '_' + delta_partial_high + '_' + delta_low + '_' + delta_high + '_' + bu_low + '_' + bu_high + '.txt'

  if (os.path.isfile(filename) and remake == False):
    print('Reading from' + filename)
    list_file = open(filename, 'r')
  else:
    if not os.path.isdir(input_dir):
      sys.exit(input_dir + ' is not a directory')
    list_file = open(filename, 'w+')
    i = 0
    for root_file in os.listdir(input_dir):
      # if i > 100:
      #   break;
      if dim == '1D':
        if fit_bu_partial == False:
          pass_filename(input_dir + '/' + root_file, list_file, dim, delta_low,
                        delta_high)
        else:
          pass_filename_bu_partial(input_dir + '/' + root_file, list_file, dim,
                                   delta_low, delta_high, delta_partial_low,
                                   delta_partial_high)
      else:
        if fit_bu_partial == False:
          pass_filename(input_dir + '/' + root_file, list_file, dim, delta_low,
                        delta_high, bu_low, bu_high)
        else:
          pass_filename_bu_partial(input_dir + '/' + root_file, list_file, dim,
                                   delta_low, delta_high, delta_partial_low,
                                   delta_partial_high, bu_low, bu_high)
      i = i + 1
    # pass_filename(input_dir + '/' + root_file, list_file)
  if not os.path.exists(output_dir):
    os.mkdir(output_dir)
    os.mkdir(output_dir)
  results_dir = output_dir + '/results'
  if not os.path.exists(results_dir):
      os.mkdir(results_dir)
  plots_dir = output_dir + '/plots'
  if not os.path.exists(plots_dir):
    os.mkdir(plots_dir)
  # print('./PlotToys ' + ','.join(list_file))
  home_path = os.getcwd()
  os.chdir(home_path)
  os.chdir('../build')
  if list_file.read(1) != None:
    if dim == '1D':
      if fit_bu_partial == False:
        subprocess.call([
            './PlotToys', '-neutral=' + neutral, '-inputFile=' + filename,
            '-outputDir=' + output_dir, '-1D', '-toyInit=' + toy_init
        ])
      else:
        subprocess.call([
            './PlotToys', '-neutral=' + neutral, '-inputFile=' + filename,
            '-outputDir=' + output_dir, '-1D', '-toyInit=' + toy_init,
            '-buPartial'
        ])
    else:
      if dim == 'D1D':
        dim = ''
      elif dim == '2D':
        dim = '-2D'
      if fit_bu_partial == False:
        # print(filename)
        # print(output_dir)
        subprocess.call([
            './PlotToys', '-neutral=' + neutral, '-inputFile=' + filename,
            '-outputDir=' + output_dir, '-toyInit=' + toy_init, dim
        ])
      else:
        subprocess.call([
            './PlotToys', '-neutral=' + neutral, '-inputFile=' + filename,
            '-outputDir=' + output_dir, '-toyInit=' + toy_init, '-buPartial', dim
        ])
        # print(
        #     './PlotToys' + ' ' + '-neutral=' + neutral + ' ' +
        #     '-inputFile=' + filename + ' ' + '-outputDir=' + output_dir + ' ' +
        #     '-toyInit=' + toy_init + ' ' + '-buPartial')
  else:
    sys.exit('File list empty')
  # os.remove(filename)
