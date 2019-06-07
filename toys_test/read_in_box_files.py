import os, re, subprocess, sys

#re = regular expressions


def pass_info(filename, delta_low, delta_high, bu_low, bu_high):
    m = re.search("Result_([0-9]+)_([0-9]+)_([0-9]+)_([0-9]+).root", filename)
    if m:
        delta_low.add(int(m.group(1)))
        delta_high.add(int(m.group(2)))
        bu_low.add(int(m.group(3)))
        bu_high.add(int(m.group(4)))


path = sys.argv[1]
if os.path.isdir(path + "/1d_results"):
    output_dir = path
    # Unique box dimensions: unordered set
    delta_low = set()
    delta_high = set()
    bu_low = set()
    bu_high = set()
    for filename in os.listdir(path + "/1d_results"):
        pass_info(path + "/" + filename, delta_low, delta_high, bu_low,
                  bu_high)
    # Re-order limits so that when they are plotted, axes go from small -> big window
    new_delta_low = sorted(delta_low, reverse=True)
    new_delta_high = sorted(delta_high)
    delta_low_high = []
    for d in range(0, len(new_delta_low)):
        delta_low_high.append(
            str(new_delta_low[d]) + "_" + str(new_delta_high[d]))
    new_bu_low = sorted(bu_low, reverse=True)
    new_bu_high = sorted(bu_high)
    bu_low_high = []
    for d in range(0, len(new_bu_low)):
        bu_low_high.append(str(new_bu_low[d]) + "_" + str(new_bu_high[d]))
    subprocess.call([
        "./BoxCutProfiles", path, ",".join(delta_low_high),
        ",".join(bu_low_high)
    ])
    # print("./BoxCutProfiles " + path + " " + ",".join(delta_low_high) + " " +
    #       ",".join(bu_low_high))
else:
    print(path + "/1d_results is not a directory")
