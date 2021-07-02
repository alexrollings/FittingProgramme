from uncertainties import unumpy, ufloat
import math
import argparse


if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-n',
                      '--neutral',
                      type=str,
                      help='Neutral',
                      required=True)
  args = parser.parse_args()
  neutral = args.neutral

  mc_effs_dict = {
      'Bu2Dst0pi_D0pi0': None,
      'Bu2Dst0pi_D0gamma': None,
      'Bd2Dstpi': None,
      'Bu2D0rho': None,
      'Bu2Dst0rho_D0pi0': None,
      'Bu2Dst0rho_D0gamma': None,
      'Bs2Dst0Kst0_D0pi0': None,
      'Bs2Dst0Kst0_D0gamma': None,
      'Bs2D0Kst0': None
  }

  for mode in mc_effs_dict:
    f_effs = open(f'/data/lhcb/users/rollings/data_fit/efficiencies/mcEffs_{mode}.txt', 'r')
    for line in f_effs:
      arr = line.rstrip('\n').split(' ')
      if arr[0] == neutral:
        if mode == 'Bs2D0Kst0' or mode == 'Bs2Dst0Kst0_D0pi0' or mode == 'Bs2Dst0Kst0_D0gamma':
          if arr[1] == 'k':
            mc_effs_dict[mode] = ufloat(float(arr[2]), float(arr[3]))
        else:
          if arr[1] == 'pi':
            mc_effs_dict[mode] = ufloat(float(arr[2]), float(arr[3]))

  or_effs_dict = {
      'Bu2Dst0pi_D0pi0': None,
      'Bu2Dst0pi_D0gamma': None,
      'Bd2Dstpi': None,
      'Bu2D0rho': None,
      'Bu2Dst0rho_D0pi0': None,
      'Bu2Dst0rho_D0gamma': None,
      'Bs2Dst0Kst0_D0pi0': None,
      'Bs2Dst0Kst0_D0gamma': None,
      'Bs2D0Kst0': None
  }

  for mode in or_effs_dict:
    if neutral == 'gamma':
      f_effs = open(f'/data/lhcb/users/rollings/data_fit/efficiencies/boxEffs_gamma_{mode}_60_105_125_170_5240_5320.txt', 'r')
    else:
      f_effs = open(f'/data/lhcb/users/rollings/data_fit/efficiencies/boxEffs_pi0_{mode}_138_148_5220_5330.txt', 'r')
    for line in f_effs:
      arr = line.rstrip('\n').split(' ')
      if arr[0] == 'orEff':
        val = float(arr[1])
      if arr[0] == 'orEffErr':
        err = float(arr[1])
    or_effs_dict[mode] = ufloat(float(val), float(err))

  kBF_Bu2Dst0pi = ufloat(4.90e-03, 0.17e-03)
  kBF_Bd2Dstpi = ufloat(2.74e-03, 0.13e-03)
  kBF_Dst2D0pi = ufloat(0.677, 0.005)
  kBF_Bu2D0rho = ufloat(1.34e-02, 0.18e-02)
  kBF_Bd2D0rho0 = ufloat(3.21e-04, 0.21e-04)
  kBF_Bu2Dst0rho = ufloat(9.8e-03, 1.7e-03)
  kBF_Bd2Dstrho = ufloat(6.8e-03, 0.9e-03)
  kBF_Dst02D0pi0 = ufloat(64.7e-02, 0.9e-02)
  kBF_Dst02D0gamma = ufloat(35.3e-02, 0.9e-02)
  kBF_Bs2D0Kst0 = ufloat(4.4e-04, 0.6e-04)
  kBF_D02kpi = ufloat(3.950e-02, 0.031e-02)
  kBF_D02pik = ufloat(1.50e-04, 0.07e-04)
  kBR_Bs = ufloat(1.0, 0.25)

  frac_dict = {}

  if neutral == 'pi0':
    frac_dict['Bd2Dstpi'] = (
        (kBF_Bd2Dstpi * kBF_Dst2D0pi) / (kBF_Bu2Dst0pi * kBF_Dst02D0pi0)) * (
            mc_effs_dict['Bd2Dstpi'] / mc_effs_dict['Bu2Dst0pi_D0pi0']) * (
                or_effs_dict['Bd2Dstpi'] / or_effs_dict['Bu2Dst0pi_D0pi0'])
    frac_dict['Bs2D0Kst0'] = (
        (kBF_Bs2D0Kst0 * kBF_D02kpi) /
        (kBF_Bu2Dst0pi * kBF_Dst02D0pi0 * kBF_D02pik)) * (
            mc_effs_dict['Bs2D0Kst0'] / mc_effs_dict['Bu2Dst0pi_D0pi0']) * (
                or_effs_dict['Bs2D0Kst0'] / or_effs_dict['Bu2Dst0pi_D0pi0'])
  else:
    frac_dict['Bd2Dstpi'] = (
        (kBF_Bd2Dstpi * kBF_Dst2D0pi) / (kBF_Bu2Dst0pi * kBF_Dst02D0gamma)) * (
            mc_effs_dict['Bd2Dstpi'] / mc_effs_dict['Bu2Dst0pi_D0gamma']) * (
                or_effs_dict['Bd2Dstpi'] / or_effs_dict['Bu2Dst0pi_D0gamma'])
    frac_dict['Bs2D0Kst0'] = (
        (kBF_Bs2D0Kst0 * kBF_D02kpi) /
        (kBF_Bu2Dst0pi * kBF_Dst02D0gamma * kBF_D02pik)) * (
            mc_effs_dict['Bs2D0Kst0'] / mc_effs_dict['Bu2Dst0pi_D0gamma']) * (
                or_effs_dict['Bs2D0Kst0'] / or_effs_dict['Bu2Dst0pi_D0gamma'])

  frac_dict['Bu2D0rho'] = (
      (kBF_Bu2D0rho + kBF_Bd2D0rho0) / (kBF_Bd2Dstpi * kBF_Dst2D0pi)) * (
          mc_effs_dict['Bu2D0rho'] * 0.3874 / mc_effs_dict['Bd2Dstpi']) * (
              or_effs_dict['Bu2D0rho'] / or_effs_dict['Bd2Dstpi'])

  frac_dict['Bu2Dst0rho'] = (
      ((kBF_Bu2Dst0rho * kBF_Dst02D0pi0) / (kBF_Bd2Dstpi * kBF_Dst2D0pi)) *
      (mc_effs_dict['Bu2Dst0rho_D0pi0'] / mc_effs_dict['Bd2Dstpi']) *
      (or_effs_dict['Bu2Dst0rho_D0pi0'] / or_effs_dict['Bd2Dstpi'])
  ) + (
      ((kBF_Bu2Dst0rho * kBF_Dst02D0gamma) / (kBF_Bd2Dstpi * kBF_Dst2D0pi)) *
      (mc_effs_dict['Bu2Dst0rho_D0gamma'] / mc_effs_dict['Bd2Dstpi']) *
      (or_effs_dict['Bu2Dst0rho_D0gamma'] / or_effs_dict['Bd2Dstpi'])
  ) + (
      # B0 -> D*- rho+
      (kBF_Bd2Dstrho / kBF_Bd2Dstpi) *
      # Same shape as Bu2Dst0rho_D0pi0, but adjust efficiency by ratio of D*- to D*0
      (mc_effs_dict['Bu2Dst0rho_D0pi0'] *
       (mc_effs_dict['Bd2Dstpi'] / mc_effs_dict['Bu2Dst0pi_D0pi0']) /
       mc_effs_dict['Bd2Dstpi']) *
      (or_effs_dict['Bu2Dst0rho_D0pi0'] / or_effs_dict['Bd2Dstpi']))

  frac_dict['Bs2Dst0Kst0'] = kBR_Bs * (
      kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0'] *
      or_effs_dict['Bs2Dst0Kst0_D0pi0'] + kBF_Dst02D0gamma *
      mc_effs_dict['Bs2Dst0Kst0_D0gamma'] * or_effs_dict['Bs2Dst0Kst0_D0gamma']
  ) / (mc_effs_dict['Bs2D0Kst0'] * or_effs_dict['Bs2D0Kst0'])


  f_out = open(f'/data/lhcb/users/rollings/data_fit/fixed_rates/bkgFracs_{neutral}.txt', 'w+')
  for mode, frac in frac_dict.items():
    f_out.write(f'{mode} {frac.nominal_value} {frac.std_dev}\n')
