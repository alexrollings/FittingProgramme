from uncertainties import unumpy, ufloat
import math


def Calc_Av_KK_pipi(ufloat_KK, ufloat_pipi):
  val_KK = ufloat_KK.nominal_value
  err_KK = ufloat_KK.std_dev
  val_pipi = ufloat_pipi.nominal_value
  err_pipi = ufloat_pipi.std_dev
  weight_KK = 1 / (pow(err_KK, 2))
  weight_pipi = 1 / (pow(err_pipi, 2))
  val_CP = (1 / (weight_KK + weight_pipi)) * (val_KK * weight_KK +
                                              val_pipi * weight_pipi)
  err_CP = pow(math.sqrt(weight_KK + weight_pipi), -1)
  return ufloat(val_CP, err_CP)

# rB larger in Bd - take this into account? Should be K BF
def Calc_Av_Bu_Bd(ufloat_Bu, ufloat_Bd):
  BF_Bu = ufloat(5.3e-04, 0.4e-04)
  BF_Bd = ufloat(4.5e-05, 0.6e-05)
  return (ufloat_Bu * BF_Bu + ufloat_Bd * BF_Bd) / (BF_Bu + BF_Bd)


if __name__ == '__main__':

  # B0 -> D0 K*0
  R_KK = ufloat(1.05, 0.21)
  R_pipi = ufloat(1.21, 0.33)
  R_CP_Bd = Calc_Av_KK_pipi(R_KK, R_pipi)

  A_KK = ufloat(-0.20, 0.17)
  A_pipi = ufloat(-0.09, 0.24)
  A_CP_Bd = Calc_Av_KK_pipi(A_KK, A_pipi)

  R_plus = ufloat(0.06, 0.04)
  R_minus = ufloat(0.06, 0.04)
  R_ADS_Bd = (R_plus + R_minus) / 2
  A_ADS_Bd = (R_minus - R_plus) / (R_minus + R_plus)

  A_Kpi_Bd = ufloat(-0.03, 0.06)

  # B+ -> D0 K*+
  R_CP_Bu = ufloat(1.22, 0.07)
  A_CP_Bu = ufloat(0.08, 0.06)
  R_ADS_Bu = ufloat(0.012, 0.004)
  A_ADS_Bu = ufloat(-0.75, 0.16)
  A_Kpi_Bu = ufloat(-0.004, 0.031)

  R_CP = Calc_Av_Bu_Bd(R_CP_Bu, R_CP_Bd)
  print("R_CP = " + str(R_CP))
  A_CP = Calc_Av_Bu_Bd(A_CP_Bu, A_CP_Bd)
  print("A_CP = " + str(A_CP))
  R_ADS = Calc_Av_Bu_Bd(R_ADS_Bu, R_ADS_Bd)
  print("R_ADS = " + str(R_ADS))
  A_ADS = Calc_Av_Bu_Bd(A_ADS_Bu, A_ADS_Bd)
  print("A_ADS = " + str(A_ADS))
  A_Kpi = Calc_Av_Bu_Bd(A_Kpi_Bu, A_Kpi_Bd)
  print("A_Kpi = " + str(A_Kpi))

  BF_DKst_Bu = ufloat(0.00053, 0.00004)
  BF_Drho_Bu = ufloat(0.0134, 0.0018)
  R_DstK_Dstpi_Bu = BF_DKst_Bu / BF_Drho_Bu
  BF_DKst_Bd = ufloat(0.000045, 0.000006)
  BF_Drho_Bd = ufloat(0.000321, 0.000021)
  R_DstK_Dstpi_Bd = BF_DKst_Bd / BF_Drho_Bd
  R_DstK_Dstpi = Calc_Av_Bu_Bd(R_DstK_Dstpi_Bu, R_DstK_Dstpi_Bd)
  print("R_DstK_Dstpi = " + str(R_DstK_Dstpi))
