from uncertainties import ufloat
from uncertainties.umath import *

rB = ufloat(0.140, 0.019)
deltaB = ufloat(319.2, 8.7)
deltaD = ufloat(15.2, 10)
rD = sqrt(ufloat(1.50e-04, 0.07e-04))/sqrt(ufloat(3.950e-02, 0.031e-02))
phi3 = ufloat(71.1, 5.3)

A_Kπ_π0 = (2*rB*sin(deltaB+deltaD)*sin(phi3))/(1+pow(rB,2)*pow(rD,2)+2*rB*rD*cos(deltaB+deltaD)*cos(phi3))
A_Kπ_gamma = (2*rB*sin(deltaB+deltaD)*sin(phi3))/(1+pow(rB,2)*pow(rD,2)-2*rB*rD*cos(deltaB+deltaD)*cos(phi3))

print(A_Kπ_π0)
print(A_Kπ_gamma)

rB = ufloat(0.076, 0.020)
deltaB = ufloat(98.2, 37)
phi3 = ufloat(71.1, 5.3)
K = ufloat(0.95, 0.06)

A_CP_DKst = (2*K*rB*sin(deltaB)*sin(phi3))/(1+pow(rB,2)+2*K*rB*cos(deltaB)*cos(phi3))

print(A_CP_DKst)
