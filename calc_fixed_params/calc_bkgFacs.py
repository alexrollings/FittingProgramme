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

  effs_dict = {'Bd2Dstpi' : None, 'Bu2D0rho' : None, 'Bu2Dst0rho_D0pi0' : None, 'Bu2Dst0rho_D0gamma' : None}

  for mode in effs_dict:
    f_effs = open(f'/home/rollings/Bu2Dst0h_scripts/mc_efficiencies/txt_new/effs_{mode}.txt', 'r')
    for line in f_effs:
      arr = line.rstrip('\n').split(' ')
      if arr[0] == neutral and arr[1] == 'pi':
        effs_dict[mode] = ufloat(float(arr[2]), float(arr[3]))

  kBF_Bd2Dstpi = ufloat(2.74e-03, 0.13e-03)
  kBF_Dst2D0pi = ufloat(0.677, 0.005)
  kBF_Bu2D0rho = ufloat(1.34e-02, 0.18e-02)
  kBF_Bd2D0rho0 = ufloat(3.21e-04, 0.21e-04)
  kBF_Bu2Dst0rho = ufloat(9.8e-03, 1.7e-03)
  kBF_Dst02D0pi0 = ufloat(64.7e-02, 0.9e-02)
  kBF_Dst02D0gamma = ufloat(35.3e-02, 0.9e-02)

  frac_dict = {'Bu2D0rho' : None, 'Bu2Dst0rho_D0pi0' : None, 'Bu2Dst0rho_D0gamma' : None}

  frac_dict['Bu2D0rho'] = ((kBF_Bu2D0rho + kBF_Bd2D0rho0) /
                   (kBF_Bd2Dstpi * kBF_Dst2D0pi)) * (effs_dict['Bu2D0rho'] /
                                                     effs_dict['Bd2Dstpi'])
  if neutral == 'pi0':
    frac_dict['Bu2Dst0rho_D0pi0'] = (
        (kBF_Bu2Dst0rho * kBF_Dst02D0pi0) /
        (kBF_Bd2Dstpi * kBF_Dst2D0pi)) * (effs_dict['Bu2Dst0rho_D0pi0'] /
                                          effs_dict['Bd2Dstpi'])
    frac_dict['Bu2Dst0rho_D0gamma'] = (
        (kBF_Dst02D0gamma / kBF_Dst02D0pi0) *
        (effs_dict['Bu2Dst0rho_D0gamma'] / effs_dict['Bu2Dst0rho_D0pi0']))
  else:
    frac_dict['Bu2Dst0rho_D0gamma'] = (
        (kBF_Bu2Dst0rho * kBF_Dst02D0gamma) /
        (kBF_Bd2Dstpi * kBF_Dst2D0pi)) * (effs_dict['Bu2Dst0rho_D0gamma'] /
                                          effs_dict['Bd2Dstpi'])
    frac_dict['Bu2Dst0rho_D0pi0'] = (
        (kBF_Dst02D0pi0 / kBF_Dst02D0gamma) *
        (effs_dict['Bu2Dst0rho_D0pi0'] / effs_dict['Bu2Dst0rho_D0gamma']))

  f_out = open(f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/calc_fixed_params/bkgFracs_{neutral}.txt', 'w+')
  for mode, frac in frac_dict.items():
    f_out.write(f'{mode} {frac.nominal_value} {frac.std_dev}\n')

