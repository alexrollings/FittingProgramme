import math
from uncertainties import ufloat
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

phi3_av_err = (4.6 + 5.3)*0.5
phi3_val_err = ufloat(math.radians(71.1),math.radians(phi3_av_err))
phi3 = np.random.normal(phi3_val_err.n, phi3_val_err.s, 10000)

# FAV: D0 -> K-π+
rD_val = np.sqrt(0.00344)
rD_err = rD_val * 2 * (2e-5/0.00344)
rD_val_err = ufloat(rD_val,rD_err)
rD = np.random.normal(rD_val_err.n, rD_val_err.s, 10000)

dD_av_err = (8.6 + 10.2)*0.5
dD_val_err = ufloat(math.radians(192.1),math.radians(dD_av_err))
dD = np.random.normal(dD_val_err.n, dD_val_err.s, 10000)

# B- -> D*0 π-
rB_Dpi = np.random.uniform(0.0, 0.02, 10000)
dB_Dpi = np.random.uniform(math.radians(0.0), math.radians(180.0), 10000)

# B- -> D*0 K-
rB_DK = np.random.uniform(0.0, 0.2, 10000)
dB_DK_av_err = (18 + 10)*0.5
dB_DK_val_err = ufloat(math.radians(314.0),math.radians(dB_DK_av_err))
dB_DK = np.random.normal(dB_DK_val_err.n, dB_DK_val_err.s, 10000)

BF_B2Dstpi = np.random.normal(4.90e-03, 0.17e-03, 10000)
BF_B2DstK_av_err = (0.31e-04 + 0.28e-04)*0.5
BF_B2DstK = np.random.normal(3.97e-04, BF_B2DstK_av_err, 10000)

R_DstKDstpi = BF_B2DstK / BF_B2Dstpi

pi0_Dpi_kpi_plus = 1 + rD**2 * rB_Dpi**2 + 2 * rD * rB_Dpi * np.cos(dB_Dpi - dD + phi3)
pi0_Dpi_kpi_minus = 1 + rD**2 * rB_Dpi**2 + 2 * rD * rB_Dpi * np.cos(dB_Dpi - dD - phi3)
gamma_Dpi_kpi_plus = 1 + rD**2 * rB_Dpi**2 - 2 * rD * rB_Dpi * np.cos(dB_Dpi - dD + phi3)
gamma_Dpi_kpi_minus = 1 + rD**2 * rB_Dpi**2 - 2 * rD * rB_Dpi * np.cos(dB_Dpi - dD - phi3)

pi0_Dpi_hh_plus = 1 + rB_Dpi**2 + 2 * rB_Dpi * np.cos(dB_Dpi + phi3)
pi0_Dpi_hh_minus = 1 + rB_Dpi**2 + 2 * rB_Dpi * np.cos(dB_Dpi - phi3)
gamma_Dpi_hh_plus = 1 + rB_Dpi**2 - 2 * rB_Dpi * np.cos(dB_Dpi + phi3)
gamma_Dpi_hh_minus = 1 + rB_Dpi**2 - 2 * rB_Dpi * np.cos(dB_Dpi - phi3)

pi0_Dpi_pik_plus = rB_Dpi**2 + rD**2 + 2 * rB_Dpi * rD * np.cos(dB_Dpi + dD + phi3)
pi0_Dpi_pik_minus = rB_Dpi**2 + rD**2 + 2 * rB_Dpi * rD * np.cos(dB_Dpi + dD - phi3)
gamma_Dpi_pik_plus = rB_Dpi**2 + rD**2 - 2 * rB_Dpi * rD * np.cos(dB_Dpi + dD + phi3)
gamma_Dpi_pik_minus = rB_Dpi**2 + rD**2 - 2 * rB_Dpi * rD * np.cos(dB_Dpi + dD - phi3)

pi0_DK_kpi_plus = 1 + rD**2 * rB_DK**2 + 2 * rD * rB_DK * np.cos(dB_DK - dD + phi3)
pi0_DK_kpi_minus = 1 + rD**2 * rB_DK**2 + 2 * rD * rB_DK * np.cos(dB_DK - dD - phi3)
gamma_DK_kpi_plus = 1 + rD**2 * rB_DK**2 - 2 * rD * rB_DK * np.cos(dB_DK - dD + phi3)
gamma_DK_kpi_minus = 1 + rD**2 * rB_DK**2 - 2 * rD * rB_DK * np.cos(dB_DK - dD - phi3)

pi0_DK_hh_plus = 1 + rB_DK**2 + 2 * rB_DK * np.cos(dB_DK + phi3)
pi0_DK_hh_minus = 1 + rB_DK**2 + 2 * rB_DK * np.cos(dB_DK - phi3)
gamma_DK_hh_plus = 1 + rB_DK**2 - 2 * rB_DK * np.cos(dB_DK + phi3)
gamma_DK_hh_minus = 1 + rB_DK**2 - 2 * rB_DK * np.cos(dB_DK - phi3)

pi0_DK_pik_plus = rB_DK**2 + rD**2 + 2 * rB_DK * rD * np.cos(dB_DK + dD + phi3)
pi0_DK_pik_minus = rB_DK**2 + rD**2 + 2 * rB_DK * rD * np.cos(dB_DK + dD - phi3)
gamma_DK_pik_plus = rB_DK**2 + rD**2 - 2 * rB_DK * rD * np.cos(dB_DK + dD + phi3)
gamma_DK_pik_minus = rB_DK**2 + rD**2 - 2 * rB_DK * rD * np.cos(dB_DK + dD - phi3)

obs_dict = {}

A_pi0_Dpi_kpi = (pi0_Dpi_kpi_minus - pi0_Dpi_kpi_plus)/(pi0_Dpi_kpi_minus + pi0_Dpi_kpi_plus)
A_gamma_Dpi_kpi = (gamma_Dpi_kpi_minus - gamma_Dpi_kpi_plus)/(gamma_Dpi_kpi_minus + gamma_Dpi_kpi_plus)

A_pi0_DK_kpi = (pi0_DK_kpi_minus - pi0_DK_kpi_plus)/(pi0_DK_kpi_minus + pi0_DK_kpi_plus)
A_gamma_DK_kpi = (gamma_DK_kpi_minus - gamma_DK_kpi_plus)/(gamma_DK_kpi_minus + gamma_DK_kpi_plus)

A_pi0_Dpi_CP = (pi0_Dpi_hh_minus - pi0_Dpi_hh_plus)/(pi0_Dpi_hh_minus + pi0_Dpi_hh_plus)
A_gamma_Dpi_CP = (gamma_Dpi_hh_minus - gamma_Dpi_hh_plus)/(gamma_Dpi_hh_minus + gamma_Dpi_hh_plus)

A_pi0_DK_CP = (pi0_DK_hh_minus - pi0_DK_hh_plus)/(pi0_DK_hh_minus + pi0_DK_hh_plus)
A_gamma_DK_CP = (gamma_DK_hh_minus - gamma_DK_hh_plus)/(gamma_DK_hh_minus + gamma_DK_hh_plus)

# R_pi0_CP = ((pi0_DK_hh_minus + pi0_DK_hh_plus)/(pi0_Dpi_hh_minus + pi0_Dpi_hh_plus))*(1/R_DstKDstpi)
# R_gamma_CP = ((gamma_DK_hh_minus + gamma_DK_hh_plus)/(gamma_Dpi_hh_minus + gamma_Dpi_hh_plus))*(1/R_DstKDstpi)
R_pi0_CP = ((pi0_DK_hh_minus + pi0_DK_hh_plus)/(pi0_Dpi_hh_minus + pi0_Dpi_hh_plus))
R_gamma_CP = ((gamma_DK_hh_minus + gamma_DK_hh_plus)/(gamma_Dpi_hh_minus + gamma_Dpi_hh_plus))

R_pi0_Dpi_pik_minus = pi0_Dpi_pik_minus / pi0_Dpi_kpi_minus
R_pi0_Dpi_pik_plus = pi0_Dpi_pik_plus / pi0_Dpi_kpi_plus
R_gamma_Dpi_pik_minus = gamma_Dpi_pik_minus / gamma_Dpi_kpi_minus
R_gamma_Dpi_pik_plus = gamma_Dpi_pik_plus / gamma_Dpi_kpi_plus

R_pi0_Dpi_pik = (R_pi0_Dpi_pik_minus + R_pi0_Dpi_pik_plus) / 2
A_pi0_Dpi_pik = (R_pi0_Dpi_pik_minus - R_pi0_Dpi_pik_plus) / (R_pi0_Dpi_pik_minus + R_pi0_Dpi_pik_plus)
R_gamma_Dpi_pik = (R_gamma_Dpi_pik_minus + R_gamma_Dpi_pik_plus) / 2
A_gamma_Dpi_pik = (R_gamma_Dpi_pik_minus - R_gamma_Dpi_pik_plus) / (R_gamma_Dpi_pik_minus + R_gamma_Dpi_pik_plus)

R_pi0_DK_pik_minus = pi0_DK_pik_minus / pi0_DK_kpi_minus
R_pi0_DK_pik_plus = pi0_DK_pik_plus / pi0_DK_kpi_plus
R_gamma_DK_pik_minus = gamma_DK_pik_minus / gamma_DK_kpi_minus
R_gamma_DK_pik_plus = gamma_DK_pik_plus / gamma_DK_kpi_plus

R_pi0_DK_pik = (R_pi0_DK_pik_minus + R_pi0_DK_pik_plus) / 2
A_pi0_DK_pik = (R_pi0_DK_pik_minus - R_pi0_DK_pik_plus) / (R_pi0_DK_pik_minus + R_pi0_DK_pik_plus)
R_gamma_DK_pik = (R_gamma_DK_pik_minus + R_gamma_DK_pik_plus) / 2
A_gamma_DK_pik = (R_gamma_DK_pik_minus - R_gamma_DK_pik_plus) / (R_gamma_DK_pik_minus + R_gamma_DK_pik_plus)

n, bins, patces = plt.hist(phi3, 100, density=True)
plt.savefig('gamma_obs/phi3.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
median = np.median(phi3)
val = bins[max_index][0]
print('phi3 = '  + str(median) + '\tmin = ' + str(bins[0]) + '\tmax = ' + str(bins[len(bins)-1]))
plt.clf()
n, bins, patches = plt.hist(rD, 100, density=True)
plt.savefig('gamma_obs/rD.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
median = np.median(rD)
val = bins[max_index][0]
print('rD = '  + str(median) + '\tmin = ' + str(bins[0]) + '\tmax = ' + str(bins[len(bins)-1]))
plt.clf()
n, bins, patches = plt.hist(dD, 100, density=True)
plt.savefig('gamma_obs/dD.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
median = np.median(dD)
val = bins[max_index][0]
print('dD = '  + str(median) + '\tmin = ' + str(bins[0]) + '\tmax = ' + str(bins[len(bins)-1]))
plt.clf()
n, bins, patches = plt.hist(rB_Dpi, 100, density=True)
plt.savefig('gamma_obs/rB_Dpi.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
median = np.median(rB_Dpi)
val = bins[max_index][0]
print('rB_Dpi = '  + str(median) + '\tmin = ' + str(bins[0]) + '\tmax = ' + str(bins[len(bins)-1]))
plt.clf()
n, bins, patches = plt.hist(dB_Dpi, 100, density=True)
plt.savefig('gamma_obs/dB_Dpi.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
median = np.median(dB_Dpi)
val = bins[max_index][0]
print('dB_Dpi = '  + str(median) + '\tmin = ' + str(bins[0]) + '\tmax = ' + str(bins[len(bins)-1]))
plt.clf()
n, bins, patches = plt.hist(rB_DK, 100, density=True)
plt.savefig('gamma_obs/rB_DK.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
median = np.median(rB_DK)
val = bins[max_index][0]
print('rB_DK = '  + str(median) + '\tmin = ' + str(bins[0]) + '\tmax = ' + str(bins[len(bins)-1]))
plt.clf()
n, bins, patches = plt.hist(dB_DK, 100, density=True)
plt.savefig('gamma_obs/dB_DK.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
median = np.median(dB_DK)
val = bins[max_index][0]
print('dB_DK = '  + str(median) + '\tmin = ' + str(bins[0]) + '\tmax = ' + str(bins[len(bins)-1]))
plt.clf()
n, bins, patches = plt.hist(R_DstKDstpi, 100, density=True)
plt.savefig('gamma_obs/R_DstKDstpi.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
median = np.median(R_DstKDstpi)
val = bins[max_index][0]
print('R_DstKDstpi = '  + str(median) + '\tmin = ' + str(bins[0]) + '\tmax = ' + str(bins[len(bins)-1]))
plt.clf()
n, bins, patches = plt.hist(A_gamma_Dpi_kpi, 100, density=True)
plt.savefig('gamma_obs/A_gamma_Dpi_kpi.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
median = np.median(A_gamma_Dpi_kpi)
val = bins[max_index][0]
print('A_gamma_Dpi_kpi = '  + str(median) + '\tmin = ' + str(bins[0]) + '\tmax = ' + str(bins[len(bins)-1]))
plt.clf()
n, bins, patches = plt.hist(A_gamma_DK_kpi, 100, density=True)
plt.savefig('gamma_obs/A_gamma_DK_kpi.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(A_gamma_DK_kpi)
print('A_gamma_DK_kpi = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['A_Bu2Dst0h_D0gamma_k_kpi'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(A_gamma_Dpi_CP, 100, density=True)
plt.savefig('gamma_obs/A_gamma_Dpi_CP.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(A_gamma_Dpi_CP)
print('A_gamma_Dpi_CP = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['A_CP_Bu2Dst0h_D0gamma_pi'] = [0, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(A_gamma_DK_CP, 100, density=True)
plt.savefig('gamma_obs/A_gamma_DK_CP.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(A_gamma_DK_CP)
print('A_gamma_DK_CP = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['A_CP_Bu2Dst0h_D0gamma_k'] = [0, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(R_gamma_CP, 100, density=True)
plt.savefig('gamma_obs/R_gamma_CP.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(R_gamma_CP)
print('R_gamma_CP = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['R_CP_Bu2Dst0h_D0gamma'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(R_gamma_Dpi_pik_minus, 100, density=True)
plt.savefig('gamma_obs/R_gamma_Dpi_pik_minus.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(R_gamma_Dpi_pik_minus)
print('R_gamma_Dpi_pik_minus = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['R_piK_Bu2Dst0h_D0gamma_pi_minus'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(R_gamma_Dpi_pik_plus, 100, density=True)
plt.savefig('gamma_obs/R_gamma_Dpi_pik_plus.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(R_gamma_Dpi_pik_plus)
print('R_gamma_Dpi_pik_plus = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['R_piK_Bu2Dst0h_D0gamma_pi_plus'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(R_gamma_Dpi_pik, 100, density=True)
plt.savefig('gamma_obs/R_gamma_Dpi_pik.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(R_gamma_Dpi_pik)
print('R_gamma_Dpi_pik = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['R_ADS_Bu2Dst0h_D0gamma_pi'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(A_gamma_Dpi_pik, 100, density=True)
plt.savefig('gamma_obs/A_gamma_Dpi_pik.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(A_gamma_Dpi_pik)
print('A_gamma_Dpi_pik = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['A_Bu2Dst0h_D0gamma_pi_pik'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(R_gamma_DK_pik_minus, 100, density=True)
plt.savefig('gamma_obs/R_gamma_DK_pik_minus.png')
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(R_gamma_DK_pik_minus)
print('R_gamma_DK_pik_minus = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['R_piK_Bu2Dst0h_D0gamma_k_minus'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(R_gamma_DK_pik_plus, 100, density=True)
plt.savefig('gamma_obs/R_gamma_DK_pik_plus.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(R_gamma_DK_pik_plus)
print('R_gamma_DK_pik_plus = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['R_piK_Bu2Dst0h_D0gamma_k_plus'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(R_gamma_DK_pik, 100, density=True)
plt.savefig('gamma_obs/R_gamma_DK_pik.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(R_gamma_DK_pik)
print('R_gamma_DK_pik = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['R_ADS_Bu2Dst0h_D0gamma_k'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()
n, bins, patches = plt.hist(A_gamma_DK_pik, 100, density=True)
plt.savefig('gamma_obs/A_gamma_DK_pik.png')
max_index = np.where(np.array(n) == np.amax(np.array(n)))
val = bins[max_index][0]
min_bin = bins[0]
max_bin = bins[len(bins)-1]
median = np.median(A_gamma_DK_pik)
print('A_gamma_DK_pik = '  + str(median) + '\tmin = ' + str(min_bin) + '\tmax = ' + str(max_bin))
obs_dict['A_Bu2Dst0h_D0gamma_k_pik'] = [median, (median - min_bin)/3, (max_bin - median)/3]
plt.clf()

f_out = open(f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/calc_fixed_params/gamma_obs.txt', 'w+')
for par, arr in obs_dict.items():
  f_out.write(f'{par} {arr[0]} {arr[1]} {arr[2]}\n')
