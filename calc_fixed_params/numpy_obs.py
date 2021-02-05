import math
from uncertainties import ufloat
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

phi3_av_err = (4.6 + 5.3)*0.5
phi3_val_err = ufloat(math.radians(71.1),math.radians(phi3_av_err))
phi3 = np.random.normal(phi3_val_err.n, phi3_val_err.s, 10000)

# # B- -> D*0 π-
# # We assume nothing about rB and dB, and that it what makes the final asymmetried non Gaussian
# rB = np.random.uniform(0.0, 0.02, 10000)
# # rB = np.random.normal(0.01, 0.002, 10000)
# dB = np.random.uniform(0.0, math.radians(180.0), 10000)
# # dB = np.random.normal(math.radians(90.0), math.radians(15.0), 10000)

# B- -> D0 K*-
rB_val_err = ufloat(0.076,0.020)
rB = np.random.normal(rB_val_err.n, rB_val_err.s, 10000)

dB_av_err = (18 + 37)*0.5
dB_val_err = ufloat(math.radians(98),math.radians(dB_av_err))
dB = np.random.normal(dB_val_err.n, dB_val_err.s, 10000)


# # For B->Drho / B ->D*rho, we can assume nothing about dB
# dB = np.random.uniform(0.0, math.radians(360.0), 10000)

# FAV: D0 -> K-π+
rD_val = np.sqrt(0.00344)
rD_err = rD_val * 2 * (2e-5/0.00344)
rD_val_err = ufloat(rD_val,rD_err)
rD = np.random.normal(rD_val_err.n, rD_val_err.s, 10000)

dD_av_err = (8.6 + 10.2)*0.5
dD_val_err = ufloat(math.radians(192.1),math.radians(dD_av_err))
dD = np.random.normal(dD_val_err.n, dD_val_err.s, 10000)

pi0_kpi_plus = 1 + rD**2 * rB**2 + 2 * rD * rB * np.cos(dB - dD + phi3)
pi0_kpi_minus = 1 + rD**2 * rB**2 + 2 * rD * rB * np.cos(dB - dD - phi3)
gamma_kpi_plus = 1 + rD**2 * rB**2 - 2 * rD * rB * np.cos(dB - dD + phi3)
gamma_kpi_minus = 1 + rD**2 * rB**2 - 2 * rD * rB * np.cos(dB - dD - phi3)

A_pi0_kpi = (pi0_kpi_minus - pi0_kpi_plus)/(pi0_kpi_minus + pi0_kpi_plus)
A_gamma_kpi = (gamma_kpi_minus - gamma_kpi_plus)/(gamma_kpi_minus + gamma_kpi_plus)

print(np.mean(A_pi0_kpi))

# A_pi0_kpi = (2 * rB * rD * np.sin(dB - dD) * np.sin(phi3)) / (
#     1 + (rB**2) * (rD**2) + 2 * rB * rD * np.cos(dB - dD) * np.cos(phi3))
# A_gamma_kpi = (- 2 * rB * rD * np.sin(dB - dD) * np.sin(phi3)) / (
#     1 + (rB**2) * (rD**2) - 2 * rB * rD * np.cos(dB - dD) * np.cos(phi3))

# # B- -> D0 rho-
# rB = np.random.uniform(0.0, 0.02, 10000)
# dB = np.random.uniform(0.0, math.radians(360.0), 10000)

# B-(0) -> D0 rho-(0)
# rB = np.random.uniform(0.0, 0.02, 10000)
# dB = np.random.uniform(0.0, math.radians(360.0), 10000)
K = np.random.normal(0.95, 0.06, 10000)

# # B- -> D0 K*-
# rB_err = (0.018 + 0.033)*0.5
# rB_val_err = ufloat(0.092,rB_err)
# rB = np.random.normal(rB_val_err.n, rB_val_err.s, 10000)
#
# dB = np.random.uniform(math.radians(40.0-20.0), math.radians(40.0+92.0), 10000)

# # B0 -> D0 K*0
rB_err = (0.044 + 0.047)*0.5
rB_val_err = ufloat(0.221,rB_err)
rB = np.random.normal(rB_val_err.n, rB_val_err.s, 10000)

dB_err = (23 + 20)*0.5
dB_val_err = ufloat(math.radians(187),math.radians(dB_err))
dB = np.random.normal(dB_val_err.n, dB_val_err.s, 10000)

Bu2D0hst_CP_plus = 1 + rB**2 + 2 * K * rB * np.cos(dB + phi3)
Bu2D0hst_CP_minus = 1 + rB**2 + 2 * K * rB * np.cos(dB - phi3)

A_Bu2D0hst_CP = (Bu2D0hst_CP_minus - Bu2D0hst_CP_plus)/(Bu2D0hst_CP_minus + Bu2D0hst_CP_plus)
R_Bu2D0hst_CP = 1 + rB**2 + 2 * K * rB * np.cos(dB) * np.cos(phi3)

rB = np.random.uniform(0.0, 0.3, 10000)
# rB = np.random.normal(0.1, 0.05, 10000)
dB = np.random.uniform(0.0, math.radians(360.0), 10000)

pi0_kpi_plus = 1 + rD**2 * rB**2 + 2 * rD * rB * np.cos(dB - dD + phi3)
pi0_kpi_minus = 1 + rD**2 * rB**2 + 2 * rD * rB * np.cos(dB - dD - phi3)
gamma_kpi_plus = 1 + rD**2 * rB**2 - 2 * rD * rB * np.cos(dB - dD + phi3)
gamma_kpi_minus = 1 + rD**2 * rB**2 - 2 * rD * rB * np.cos(dB - dD - phi3)

pi0_pik_plus = rB**2 + rD**2 + 2 * rB * rD * np.cos(dB + dD + phi3)
pi0_pik_minus = rB**2 + rD**2 + 2 * rB * rD * np.cos(dB + dD - phi3)
gamma_pik_plus = rB**2 + rD**2 - 2 * rB * rD * np.cos(dB + dD + phi3)
gamma_pik_minus = rB**2 + rD**2 - 2 * rB * rD * np.cos(dB + dD - phi3)

R_pi0_pik_minus = pi0_pik_minus / pi0_kpi_minus
R_pi0_pik_plus = pi0_pik_plus / pi0_kpi_plus
R_gamma_pik_minus = gamma_pik_minus / gamma_kpi_minus
R_gamma_pik_plus = gamma_pik_plus / gamma_kpi_plus

R_pi0_pik = (R_pi0_pik_minus + R_pi0_pik_plus) / 2
A_pi0_pik = (R_pi0_pik_minus - R_pi0_pik_plus) / (R_pi0_pik_minus + R_pi0_pik_plus)
R_gamma_pik = (R_gamma_pik_minus + R_gamma_pik_plus) / 2
A_gamma_pik = (R_gamma_pik_minus - R_gamma_pik_plus) / (R_gamma_pik_minus + R_gamma_pik_plus)

fig = plt.hist(phi3, 100, density=True)
plt.savefig('plots/phi3.png')
plt.clf()
fig = plt.hist(rB, 100, density=True)
plt.savefig('plots/rB.png')
plt.clf()
fig = plt.hist(dB, 100, density=True)
plt.savefig('plots/dB.png')
plt.clf()
fig = plt.hist(rD, 100, density=True)
plt.savefig('plots/rD.png')
plt.clf()
fig = plt.hist(dD, 100, density=True)
plt.savefig('plots/dD.png')
plt.clf()
fig = plt.hist(A_pi0_kpi, 100, density=True)
plt.savefig('plots/A_pi0_kpi.png')
plt.clf()
fig = plt.hist(A_gamma_kpi, 100, density=True)
plt.savefig('plots/A_gamma_kpi.png')
plt.clf()
fig = plt.hist(A_Bu2D0hst_CP, 100, density=True)
plt.savefig('plots/A_Bu2D0hst_CP.png')
plt.clf()
fig = plt.hist(R_Bu2D0hst_CP, 100, density=True)
plt.savefig('plots/R_Bu2D0hst_CP.png')
plt.clf()
fig = plt.hist(R_pi0_pik_minus, 100, density=True)
plt.savefig('plots/R_pi0_pik_minus.png')
plt.clf()
fig = plt.hist(R_pi0_pik_plus, 100, density=True)
plt.savefig('plots/R_pi0_pik_plus.png')
plt.clf()
fig = plt.hist(R_gamma_pik_minus, 100, density=True)
plt.savefig('plots/R_gamma_pik_minus.png')
plt.clf()
fig = plt.hist(R_gamma_pik_plus, 100, density=True)
plt.savefig('plots/R_gamma_pik_plus.png')
plt.clf()
fig = plt.hist(R_pi0_pik, 100, density=True)
plt.savefig('plots/R_pi0_pik.png')
plt.clf()
fig = plt.hist(A_pi0_pik, 100, density=True)
plt.savefig('plots/A_pi0_pik.png')
plt.clf()
fig = plt.hist(R_gamma_pik, 100, density=True)
plt.savefig('plots/R_gamma_pik.png')
plt.clf()
fig = plt.hist(A_gamma_pik, 100, density=True)
plt.savefig('plots/A_gamma_pik.png')
