import os, json, argparse

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-f',
                      '--json_fname',
                      type=str,
                      help='Name of json file',
                      required=True)
  parser.add_argument('-k',
                      '--key',
                      type=str,
                      help='Key to remove (name of systematic label)',
                      required=True)
  args = parser.parse_args()
  json_fname = args.json_fname
  key = args.key

  if os.path.exists(json_fname):
    with open(json_fname, 'r') as json_file:
      json_dict = json.load(json_file)
      if key in json_dict:
        json_dict.pop(key, None)
        json_tmp = json_fname + '.tmp'
        with open(json_tmp, 'w') as tmp:
          json.dump(json_dict, tmp)
        os.rename(json_tmp, json_fname)
      else:
        print(f'{key} not in {json_fname} dict')
