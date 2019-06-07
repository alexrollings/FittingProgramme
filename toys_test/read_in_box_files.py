import os, re, subprocess, sys
#re = regular expressions


def pass_info(filename, delta_low_high, bu_low_high):
    m = re.search("Result_([0-9]+_[0-9]+)_([0-9]+_[0-9]+).root", filename)
    if m:
        delta_low_high.add(m.group(1))
        bu_low_high.add(m.group(2))


path = sys.argv[1]
if os.path.isdir(path + "/1d_results"):
    output_dir = path
    # Unique box dimensions: unordered set
    delta_low_high = set()
    bu_low_high = set()
    for filename in os.listdir(path + "/1d_results"):
        pass_info(path + "/" + filename, delta_low_high, bu_low_high)
    # subprocess.call([
    #     "./BoxCutProfiles", path, ",".join(delta_low_high),
    #     ",".join(bu_low_high)
    # ])
    print("./BoxCutProfiles " + path + " " + ",".join(delta_low_high) + " " +
          ",".join(bu_low_high))
else:
    print(path + "/1d_results is not a directory")
