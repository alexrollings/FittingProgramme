import math
from uncertainties import ufloat
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

phi3_av_err = (4.6 + 5.3)*0.5
phi3_val_err = ufloat(math.radians(71.1),math.radians(phi3_av_err))
phi3 = np.random.normal(phi3_val_err.n, phi3_val_err.s, 10000)

rB = np.random.uniform(0.0, 0.2, 10000)
dB = np.random.uniform(0.0, 180.0, 10000)

rD_val = np.sqrt(0.00344)
rD_err = rD_val * 2 * (2e-5/0.00344)
rD_val_err = ufloat(rD_val,rD_err)
rD = np.random.normal(rD_val_err.n, rD_val_err.s, 10000)

dD_av_err = (8.6 + 10.2)*0.5
dD_val_err = ufloat(math.radians(192.1),math.radians(dD_av_err))
dD = np.random.normal(dD_val_err.n, dD_val_err.s, 10000)

A_Kπ_π0 = (2 * rB * np.sin(dB + dD) * np.sin(phi3)) / (
    1 + (rB**2) * (rD**2) + 2 * rB * rD * np.cos(dB + dD) * np.cos(phi3))
A_Kπ_gamma = (2 * rB * np.sin(dB + dD) * np.sin(phi3)) / (
    1 + (rB**2) * (rD**2) - 2 * rB * rD * np.cos(dB + dD) * np.cos(phi3))

# rB = ufloat(0.076, 0.020)
# deltaB = ufloat(98.2, 37)
# K = ufloat(0.95, 0.06)
#
# A_CP_DKst = (2*K*rB*sin(deltaB)*sin(phi3))/(1+pow(rB,2)+2*K*rB*cos(deltaB)*cos(phi3))

fig = plt.hist(phi3, 100, density=True)
plt.savefig('plots/phi3.png')
plt.clf()
fig = plt.hist(rB, 100, density=True)
plt.savefig('plots/rB.png')
plt.clf()
fig = plt.hist(A_Kπ_π0, 100, density=True)
plt.savefig('plots/A_Kπ_π0.png')
plt.clf()
fig = plt.hist(A_Kπ_gamma, 100, density=True)
plt.savefig('plots/A_Kπ_gamma.png')
