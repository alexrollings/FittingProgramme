import os, json

json_fname = '/data/lhcb/users/rollings/systematics/9bf362c/gamma/systematics_gamma.json'
if os.path.exists(json_fname):
  with open(json_fname, 'r') as json_file:
    json_dict = json.load(json_file)
    key = 'Bs2D0Kst0_PdfDelta'
    if key in json_dict:
      json_dict.pop(key, None)
      json_tmp = '/data/lhcb/users/rollings/systematics/9bf362c/gamma/systematics_gamma.json.tmp'
      with open(json_tmp, 'w') as tmp:
        json.dump(json_dict, tmp)
      os.rename(json_tmp, json_fname)
    else:
      print(f'{key} not in {json_fname} dict')
