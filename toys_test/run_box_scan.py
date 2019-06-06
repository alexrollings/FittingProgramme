import os, re, subprocess, sys
# import numpy as np


path = sys.argv[1]
if os.path.isfile(path + "/DataFile.root"):
    output_dir = path + "/1d_results"
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)

    # 15 bins in each dimension
    # delta_low = np.arrange(115, 130, 1)
    # delta_high = np.arrange(200, 155, -3)
    # bu_low = np.arrange(5200, 5260, 4)
    # bu_high = np.arrange(5360, 5300, -4)

    delta_low = [
        115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
        129, 130
    ]
    delta_high = [
        200, 197, 194, 191, 188, 185, 182, 179, 176, 173, 170, 167, 164, 161,
        158, 155
    ]
    bu_low = [
        5200, 5204, 5208, 5212, 5216, 5220, 5224, 5228, 5232, 5236, 5240, 5244,
        5248, 5252, 5256, 5260
    ]
    bu_high = [
        5360, 5356, 5352, 5348, 5344, 5340, 5336, 5332, 5328, 5324, 5320, 5316,
        5312, 5308, 5304, 5300
    ]

    if len(delta_low) != len(delta_high):
        sys.exit("delta_low and delta_high are of different lengths")
    if len(bu_low) != len(bu_high):
        sys.exit("bu_low and bu_high are of different lengths")

    i = 0
    while i < len(delta_low):
        j = 0
        while j < len(bu_low):
            # subprocess.call([
            #     "./SimToy1D_ReadDataSet", path, str(delta_low[i]), str(delta_high[i]),
            #     str(bu_low[j]), str(bu_high[j])
            # ])
            print("./SimToy1D_ReadDataSet" + " " + path + " " +
                  str(delta_low[i]) + " " + str(delta_high[i]) + " " +
                  str(bu_low[j]) + " " + str(bu_high[j]))
            j += 1
        i += 1
else:
    print(path + "/DataFile.root does not exist")
