from uncertainties import ufloat
from math import sqrt as sq

N_pi_kpi = ufloat(50000, sq(50000))
N_pi_kk = ufloat(N_pi_kpi.n*0.1, sq(N_pi_kpi.n*0.1))
N_pi_pipi = ufloat(N_pi_kpi.n*0.04, sq(N_pi_kpi.n*0.04))
N_pi_pik = ufloat(N_pi_kpi.n*3.8e-04, sq(N_pi_kpi.n*3.8e-04))
N_k_kpi = ufloat(N_pi_kpi.n*0.08, sq(N_pi_kpi.n*0.08))
N_k_kk = ufloat(N_pi_kk.n*0.08, sq(N_pi_kk.n*0.08))
N_k_pipi = ufloat(N_pi_pipi.n*0.08, sq(N_pi_pipi.n*0.08))
N_k_pik = ufloat(N_k_kpi.n*0.015, sq(N_k_kpi.n*0.015))

R_DK_Dpi = N_k_kpi / N_pi_kpi
print(R_DK_Dpi)
R_CP = (N_k_kk / N_pi_kk) * (1 / R_DK_Dpi)
print(R_CP)
R_pi_piK = N_pi_pik / N_pi_kpi
print(R_pi_piK)
R_k_piK = N_k_pik / N_k_kpi
print(R_k_piK)

N_pi_kpi = ufloat(50000, sq(50000)/sq(2))
N_pi_kk = ufloat(N_pi_kpi.n*0.1, sq(N_pi_kpi.n*0.1)/sq(2))
N_pi_pipi = ufloat(N_pi_kpi.n*0.04, sq(N_pi_kpi.n*0.04)/sq(2))
N_pi_pik = ufloat(N_pi_kpi.n*3.8e-04, sq(N_pi_kpi.n*3.8e-04)/sq(2))
N_k_kpi = ufloat(N_pi_kpi.n*0.08, sq(N_pi_kpi.n*0.08)/sq(2))
N_k_kk = ufloat(N_pi_kk.n*0.08, sq(N_pi_kk.n*0.08)/sq(2))
N_k_pipi = ufloat(N_pi_pipi.n*0.08, sq(N_pi_pipi.n*0.08)/sq(2))
N_k_pik = ufloat(N_k_kpi.n*0.015, sq(N_k_kpi.n*0.015)/sq(2))

R_DK_Dpi_corr = N_k_kpi / N_pi_kpi
print(R_DK_Dpi)
R_CP_corr = (N_k_kk / N_pi_kk) * (1 / R_DK_Dpi)
print(R_CP)
R_pi_piK_corr = N_pi_pik / N_pi_kpi
print(R_pi_piK)
R_k_piK_corr = N_k_pik / N_k_kpi
print(R_k_piK)

print()
print(R_DK_Dpi.s / R_DK_Dpi_corr.s)
print(R_CP.s / R_CP_corr.s)
print(R_pi_piK.s / R_pi_piK_corr.s)
print(R_k_piK.s / R_k_piK_corr.s)
print()

N_pi_kpi_plus = ufloat(23000, sq(23000))
N_pi_kpi_minus = ufloat(27000, sq(27000))

A_pi_kpi = (N_pi_kpi_minus - N_pi_kpi_plus) / (N_pi_kpi_minus + N_pi_kpi_plus)
print(A_pi_kpi)

N_pi_kpi_plus = ufloat(23000, sq(23000)/sq(2))
N_pi_kpi_minus = ufloat(27000, sq(27000)/sq(2))

A_pi_kpi_corr = (N_pi_kpi_minus - N_pi_kpi_plus) / (N_pi_kpi_minus + N_pi_kpi_plus)
print(A_pi_kpi_corr)

print(A_pi_kpi.s / A_pi_kpi_corr.s)
