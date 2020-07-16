import os, re

path = '/data/lhcb/users/rollings/roofit_results/box_scan/buDelta/results/'
for filename in os.listdir(path):
    m = re.search(
        'Result2D_([0-9]+)\.000000_([0-9]+)\.000000_([0-9]+)\.000000_([0-9]+)\.000000_(0\.[0-9]+)\.root',
        filename)
    if m:
        new_name = 'Result2D_' + m.group(1) + '_' + m.group(2) + '_' + m.group(
            3) + '_' + m.group(4) + '_' + m.group(5) + '.root'
        os.rename(path + filename, path + new_name)
        # print(path + filename)
        # print(path + new_name)
