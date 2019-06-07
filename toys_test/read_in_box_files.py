import os, re, subprocess, sys
#re = regular expressions

def pass_info(filename, file_list, delta_low, delta_high, bu_low, bu_high):
    m = re.search("Result_([0-9]+)_([0-9]+)_([0-9]+)_([0-9]+).root", filename)
    if m:
        file_list.append(filename)
        delta_low.append(m.group(1))
        delta_high.append(m.group(2))
        bu_low.append(m.group(3))
        bu_high.append(m.group(4))

if os.path.isdir(sys.argv[1] + "/1d_results"):
    output_dir = sys.argv[1]
    file_list = []
    delta_low = []
    delta_high = []
    bu_low = []
    bu_high = []
    for filename in os.listdir(sys.argv[1] + "/1d_results"):
        pass_info(sys.argv[1] + "/" + filename, file_list, delta_low,
                      delta_high, bu_low, bu_high)
    subprocess.call([
        "./BoxCutProfiles", ",".join(file_list), output_dir,
        ",".join(delta_low), ",".join(delta_high), ",".join(bu_low),
        ",".join(bu_high)
    ])
    # print("./BoxCutProfiles" + " " + ",".join(file_list) + " " + output_dir +
    #       " " + ",".join(delta_low) + " " + ",".join(delta_high) + " " +
    #       ",".join(bu_low) + " " + ",".join(bu_high))
else:
    print(sys.argv[1] + "/1d_results is not a directory")
