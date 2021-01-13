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
      'Bu2Dst0pi_D0pi0': { 'pi': None, 'k' : None },
      'Bd2Dstpi': { 'pi': None, 'k' : None },
      'Bu2Dst0rho_D0pi0': { 'pi': None, 'k' : None },
      'Bu2Dst0rho_D0gamma': { 'pi': None, 'k' : None },
      'Bu2Dst0Kst_D0pi0': { 'pi': None, 'k' : None },
      'Bu2Dst0Kst_D0gamma': { 'pi': None, 'k' : None },
      'Bs2Dst0Kst0_D0pi0': { 'k' : None },
      'Bs2Dst0Kst0_D0gamma': { 'k' : None },
      'Bs2Dst0Kst0_D0pi0_WN': { 'k' : None },
      'Bs2Dst0Kst0_D0gamma_WN': { 'k' : None },
  }

  for mode in mc_effs_dict:
    f_effs = open(f'/home/rollings/Bu2Dst0h_scripts/mc_efficiencies/txt_new/effs_{mode}.txt', 'r')
    for line in f_effs:
      arr = line.rstrip('\n').split(' ')
      if arr[0] == neutral:
        for bachelor in mc_effs_dict[mode]:
          if arr[1] == bachelor:
            mc_effs_dict[mode][bachelor] = ufloat(float(arr[2]), float(arr[3]))
          if arr[1] == bachelor:
            mc_effs_dict[mode][bachelor] = ufloat(float(arr[2]), float(arr[3]))

  box_effs_dict = {
      'Bu2Dst0rho_D0pi0': {
          'pi': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          },
          'k': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          }
      },
      'Bu2Dst0rho_D0gamma': {
          'pi': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          },
          'k': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          }
      },
      'Bu2Dst0Kst_D0pi0': {
          'pi': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          },
          'k': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          }
      },
      'Bu2Dst0Kst_D0gamma': {
          'pi': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          },
          'k': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          }
      },
      'Bs2Dst0Kst0_D0pi0': {
          'k': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          }
      },
      'Bs2Dst0Kst0_D0gamma': {
          'k': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          }
      },
      'Bs2Dst0Kst0_D0pi0_WN': {
          'k': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          }
      },
      'Bs2Dst0Kst0_D0gamma_WN': {
          'k': {
              'or': None,
              'buCut': None,
              'deltaCut': None,
              'deltaPartialCut': None
          }
      },
  }

  for mode in box_effs_dict:
    for bachelor in box_effs_dict[mode]:
      if (bachelor == 'k' and 'K' in mode) or (bachelor == 'pi' and 'K' not in mode):
        if neutral == 'gamma':
          f_effs = open(
              f'/data/lhcb/users/rollings/txt_efficiencies/gamma_{mode}_60_105_125_170_5240_5320.txt',
              'r')
        else:
          f_effs = open(
              f'/data/lhcb/users/rollings/txt_efficiencies/pi0_{mode}_138_148_5220_5330.txt',
              'r')
      else:
        if neutral == 'gamma':
          f_effs = open(
              f'/data/lhcb/users/rollings/txt_efficiencies/gamma_misId_{mode}_as_{bachelor}_60_105_125_170_5240_5320.txt',
              'r')
        else:
          f_effs = open(
              f'/data/lhcb/users/rollings/txt_efficiencies/pi0_misId_{mode}_as_{bachelor}_138_148_5220_5330.txt',
              'r')
      line_arr = []
      for line in f_effs:
        line_arr.append(line.rstrip('\n').split(' '))
      for box_eff in box_effs_dict[mode][bachelor]:
        for arr in line_arr:
          if arr[0] == f'{box_eff}Eff':
            val = float(arr[1])
          if arr[0] == f'{box_eff}EffErr':
            err = float(arr[1])
        box_effs_dict[mode][bachelor][box_eff] = ufloat(float(val), float(err))


  kBF_Bu2Dst0rho = ufloat(9.8e-03, 1.7e-03)
  kBF_Bd2Dstrho = ufloat(6.8e-03, 0.9e-03)
  kBF_Dst2D0pi = ufloat(0.677, 0.005)
  kBF_Dst02D0pi0 = ufloat(64.7e-02, 0.9e-02)
  kBF_Dst02D0gamma = ufloat(35.3e-02, 0.9e-02)

  frac_dict = {}

  frac_dict['Bs2Dst0Kst0_fracD0pi0_k'] = (
      kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0']['k'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['or']) / (
          kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['or'] +
          kBF_Dst02D0gamma * mc_effs_dict['Bs2Dst0Kst0_D0gamma']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma']['k']['or'])

  frac_dict['Bs2Dst0Kst0_fracD0pi0_Bu_k'] = (
      kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0']['k'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['or'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['deltaCut']) / (
          kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['or'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['deltaCut'] +
          kBF_Dst02D0gamma * mc_effs_dict['Bs2Dst0Kst0_D0gamma']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma']['k']['or'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma']['k']['deltaCut'])

  frac_dict['Bs2Dst0Kst0_fracD0pi0_Delta_k'] = (
      kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0']['k'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['or'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['buCut']) / (
          kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['or'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['buCut'] +
          kBF_Dst02D0gamma * mc_effs_dict['Bs2Dst0Kst0_D0gamma']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma']['k']['or'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma']['k']['buCut'])

  frac_dict['Bs2Dst0Kst0_fracD0pi0_WN_k'] = (
      kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['or']) / (
          kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['or'] +
          kBF_Dst02D0gamma * mc_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k']['or'])

  frac_dict['Bs2Dst0Kst0_fracD0pi0_WN_Bu_k'] = (
      kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['or'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['deltaCut']) / (
          kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['or'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['deltaCut'] +
          kBF_Dst02D0gamma * mc_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k']['or'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k']['deltaCut'])

  frac_dict['Bs2Dst0Kst0_fracD0pi0_WN_Delta_k'] = (
      kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['or'] *
      box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['buCut']) / (
          kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['or'] *
          box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['buCut'] +
          kBF_Dst02D0gamma * mc_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k']['or'] *
          box_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k']['buCut'])

  if neutral == 'gamma':
    frac_dict['Bs2Dst0Kst0_fracD0pi0_BuPartial_k'] = (
        kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0']['k'] *
        box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['or'] *
        box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['deltaPartialCut']) / (
            kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0']['k'] *
            box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['or'] *
            box_effs_dict['Bs2Dst0Kst0_D0pi0']['k']['deltaPartialCut'] +
            kBF_Dst02D0gamma * mc_effs_dict['Bs2Dst0Kst0_D0gamma']['k'] *
            box_effs_dict['Bs2Dst0Kst0_D0gamma']['k']['or'] *
            box_effs_dict['Bs2Dst0Kst0_D0gamma']['k']['deltaPartialCut'])

    frac_dict['Bs2Dst0Kst0_fracD0pi0_WN_BuPartial_k'] = (
        kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k'] *
        box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['or'] *
        box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['deltaPartialCut']) / (
            kBF_Dst02D0pi0 * mc_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k'] *
            box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['or'] *
            box_effs_dict['Bs2Dst0Kst0_D0pi0_WN']['k']['deltaPartialCut'] +
            kBF_Dst02D0gamma * mc_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k'] *
            box_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k']['or'] *
            box_effs_dict['Bs2Dst0Kst0_D0gamma_WN']['k']['deltaPartialCut'])

    # Fraction of D0π0 PDF in Bu2Dst0rho total PDF
    frac_dict['Bu2Dst0hst_fracD0pi0_pi'] = (
        (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['pi'] /
         mc_effs_dict['Bu2Dst0pi_D0pi0']['pi'] + kBF_Bu2Dst0rho * kBF_Dst02D0pi0)
        * mc_effs_dict['Bu2Dst0rho_D0pi0']['pi'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['or']) / (
            (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['pi'] /
             mc_effs_dict['Bu2Dst0pi_D0pi0']['pi'] + kBF_Bu2Dst0rho *
             kBF_Dst02D0pi0) * mc_effs_dict['Bu2Dst0rho_D0pi0']['pi'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['or'] +
            (kBF_Bu2Dst0rho * kBF_Dst02D0gamma *
             mc_effs_dict['Bu2Dst0rho_D0gamma']['pi'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['pi']['or']))

    frac_dict['Bu2Dst0hst_fracD0pi0_Bu_pi'] = (
        (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['pi'] /
         mc_effs_dict['Bu2Dst0pi_D0pi0']['pi'] + kBF_Bu2Dst0rho * kBF_Dst02D0pi0)
        * mc_effs_dict['Bu2Dst0rho_D0pi0']['pi'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['deltaCut'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['or']) / (
            (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['pi'] /
             mc_effs_dict['Bu2Dst0pi_D0pi0']['pi'] + kBF_Bu2Dst0rho *
             kBF_Dst02D0pi0) * mc_effs_dict['Bu2Dst0rho_D0pi0']['pi'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['deltaCut'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['or'] +
            (kBF_Bu2Dst0rho * kBF_Dst02D0gamma *
             mc_effs_dict['Bu2Dst0rho_D0gamma']['pi'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['pi']['deltaCut'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['pi']['or']))

    frac_dict['Bu2Dst0hst_fracD0pi0_Delta_pi'] = (
        (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['pi'] /
         mc_effs_dict['Bu2Dst0pi_D0pi0']['pi'] + kBF_Bu2Dst0rho * kBF_Dst02D0pi0)
        * mc_effs_dict['Bu2Dst0rho_D0pi0']['pi'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['buCut'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['or']) / (
            (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['pi'] /
             mc_effs_dict['Bu2Dst0pi_D0pi0']['pi'] + kBF_Bu2Dst0rho *
             kBF_Dst02D0pi0) * mc_effs_dict['Bu2Dst0rho_D0pi0']['pi'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['buCut'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['or'] +
            (kBF_Bu2Dst0rho * kBF_Dst02D0gamma *
             mc_effs_dict['Bu2Dst0rho_D0gamma']['pi'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['pi']['buCut'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['pi']['or']))

    frac_dict['Bu2Dst0hst_fracD0pi0_BuPartial_pi'] = (
        (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['pi'] /
         mc_effs_dict['Bu2Dst0pi_D0pi0']['pi'] + kBF_Bu2Dst0rho * kBF_Dst02D0pi0)
        * mc_effs_dict['Bu2Dst0rho_D0pi0']['pi'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['deltaPartialCut'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['or']) / (
            (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['pi'] /
             mc_effs_dict['Bu2Dst0pi_D0pi0']['pi'] + kBF_Bu2Dst0rho *
             kBF_Dst02D0pi0) * mc_effs_dict['Bu2Dst0rho_D0pi0']['pi'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['deltaPartialCut'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['pi']['or'] +
            (kBF_Bu2Dst0rho * kBF_Dst02D0gamma *
             mc_effs_dict['Bu2Dst0rho_D0gamma']['pi'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['pi']['deltaPartialCut'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['pi']['or']))

    frac_dict['Bu2Dst0hst_misId_fracD0pi0_k'] = (
        (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['k'] /
         mc_effs_dict['Bu2Dst0pi_D0pi0']['k'] + kBF_Bu2Dst0rho * kBF_Dst02D0pi0)
        * mc_effs_dict['Bu2Dst0rho_D0pi0']['k'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['k']['or']) / (
            (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['k'] /
             mc_effs_dict['Bu2Dst0pi_D0pi0']['k'] + kBF_Bu2Dst0rho *
             kBF_Dst02D0pi0) * mc_effs_dict['Bu2Dst0rho_D0pi0']['k'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['k']['or'] +
            (kBF_Bu2Dst0rho * kBF_Dst02D0gamma *
             mc_effs_dict['Bu2Dst0rho_D0gamma']['k'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['k']['or']))

    frac_dict['Bu2Dst0hst_misId_fracD0pi0_Bu_k'] = (
        (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['k'] /
         mc_effs_dict['Bu2Dst0pi_D0pi0']['k'] + kBF_Bu2Dst0rho * kBF_Dst02D0pi0)
        * mc_effs_dict['Bu2Dst0rho_D0pi0']['k'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['k']['deltaCut'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['k']['or']) / (
            (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['k'] /
             mc_effs_dict['Bu2Dst0pi_D0pi0']['k'] + kBF_Bu2Dst0rho *
             kBF_Dst02D0pi0) * mc_effs_dict['Bu2Dst0rho_D0pi0']['k'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['k']['deltaCut'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['k']['or'] +
            (kBF_Bu2Dst0rho * kBF_Dst02D0gamma *
             mc_effs_dict['Bu2Dst0rho_D0gamma']['k'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['k']['deltaCut'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['k']['or']))

    frac_dict['Bu2Dst0hst_misId_fracD0pi0_Delta_k'] = (
        (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['k'] /
         mc_effs_dict['Bu2Dst0pi_D0pi0']['k'] + kBF_Bu2Dst0rho * kBF_Dst02D0pi0)
        * mc_effs_dict['Bu2Dst0rho_D0pi0']['k'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['k']['buCut'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['k']['or']) / (
            (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['k'] /
             mc_effs_dict['Bu2Dst0pi_D0pi0']['k'] + kBF_Bu2Dst0rho *
             kBF_Dst02D0pi0) * mc_effs_dict['Bu2Dst0rho_D0pi0']['k'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['k']['buCut'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['k']['or'] +
            (kBF_Bu2Dst0rho * kBF_Dst02D0gamma *
             mc_effs_dict['Bu2Dst0rho_D0gamma']['k'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['k']['buCut'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['k']['or']))

    frac_dict['Bu2Dst0hst_misId_fracD0pi0_BuPartial_k'] = (
        (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['k'] /
         mc_effs_dict['Bu2Dst0pi_D0pi0']['k'] + kBF_Bu2Dst0rho * kBF_Dst02D0pi0)
        * mc_effs_dict['Bu2Dst0rho_D0pi0']['k'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['k']['deltaPartialCut'] *
        box_effs_dict['Bu2Dst0rho_D0pi0']['k']['or']) / (
            (kBF_Bd2Dstrho * kBF_Dst2D0pi * mc_effs_dict['Bd2Dstpi']['k'] /
             mc_effs_dict['Bu2Dst0pi_D0pi0']['k'] + kBF_Bu2Dst0rho *
             kBF_Dst02D0pi0) * mc_effs_dict['Bu2Dst0rho_D0pi0']['k'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['k']['deltaPartialCut'] *
            box_effs_dict['Bu2Dst0rho_D0pi0']['k']['or'] +
            (kBF_Bu2Dst0rho * kBF_Dst02D0gamma *
             mc_effs_dict['Bu2Dst0rho_D0gamma']['k'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['k']['deltaPartialCut'] *
             box_effs_dict['Bu2Dst0rho_D0gamma']['k']['or']))

    # Fraction of D0π0 PDF in Bu2Dst0Kst total PDF - B0 -> D*-(K*+ -> K0 π+) i.e. doesn't contribute to D*K
    frac_dict['Bu2Dst0hst_fracD0pi0_k'] = (
        kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['k'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['or']
    ) / (kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['k']
         * box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['or'] + kBF_Bu2Dst0rho *
         kBF_Dst02D0gamma * mc_effs_dict['Bu2Dst0Kst_D0gamma']['k'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['k']['or'])

    frac_dict['Bu2Dst0hst_fracD0pi0_Bu_k'] = (
        kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['k'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['deltaCut'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['or']
    ) / (kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['k']
         * box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['deltaCut'] *
         box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['or'] + kBF_Bu2Dst0rho *
         kBF_Dst02D0gamma * mc_effs_dict['Bu2Dst0Kst_D0gamma']['k'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['k']['deltaCut'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['k']['or'])

    frac_dict['Bu2Dst0hst_fracD0pi0_Delta_k'] = (
        kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['k'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['buCut'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['or']
    ) / (kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['k']
         * box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['buCut'] *
         box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['or'] + kBF_Bu2Dst0rho *
         kBF_Dst02D0gamma * mc_effs_dict['Bu2Dst0Kst_D0gamma']['k'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['k']['buCut'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['k']['or'])

    frac_dict['Bu2Dst0hst_fracD0pi0_BuPartial_k'] = (
        kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['k'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['deltaPartialCut'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['or']
    ) / (kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['k']
         * box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['deltaPartialCut'] *
         box_effs_dict['Bu2Dst0Kst_D0pi0']['k']['or'] + kBF_Bu2Dst0rho *
         kBF_Dst02D0gamma * mc_effs_dict['Bu2Dst0Kst_D0gamma']['k'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['k']['deltaPartialCut'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['k']['or'])

    frac_dict['Bu2Dst0hst_misId_fracD0pi0_pi'] = (
        kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['pi'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['or']
    ) / (kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['pi']
         * box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['or'] + kBF_Bu2Dst0rho *
         kBF_Dst02D0gamma * mc_effs_dict['Bu2Dst0Kst_D0gamma']['pi'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['pi']['or'])

    frac_dict['Bu2Dst0hst_misId_fracD0pi0_Bu_pi'] = (
        kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['pi'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['deltaCut'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['or']
    ) / (kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['pi']
         * box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['deltaCut'] *
         box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['or'] + kBF_Bu2Dst0rho *
         kBF_Dst02D0gamma * mc_effs_dict['Bu2Dst0Kst_D0gamma']['pi'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['pi']['deltaCut'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['pi']['or'])

    frac_dict['Bu2Dst0hst_misId_fracD0pi0_Delta_pi'] = (
        kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['pi'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['buCut'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['or']
    ) / (kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['pi']
         * box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['buCut'] *
         box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['or'] + kBF_Bu2Dst0rho *
         kBF_Dst02D0gamma * mc_effs_dict['Bu2Dst0Kst_D0gamma']['pi'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['pi']['buCut'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['pi']['or'])

    frac_dict['Bu2Dst0hst_misId_fracD0pi0_BuPartial_pi'] = (
        kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['pi'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['deltaPartialCut'] *
        box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['or']
    ) / (kBF_Bu2Dst0rho * kBF_Dst02D0pi0 * mc_effs_dict['Bu2Dst0Kst_D0pi0']['pi']
         * box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['deltaPartialCut'] *
         box_effs_dict['Bu2Dst0Kst_D0pi0']['pi']['or'] + kBF_Bu2Dst0rho *
         kBF_Dst02D0gamma * mc_effs_dict['Bu2Dst0Kst_D0gamma']['pi'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['pi']['deltaPartialCut'] *
         box_effs_dict['Bu2Dst0Kst_D0gamma']['pi']['or'])

  f_out = open(f'/home/rollings/Bu2Dst0h_2d/FittingProgramme/calc_fixed_params/pdf_fracs_{neutral}.txt', 'w+')
  for name, frac in frac_dict.items():
    f_out.write(f'{name} {frac.nominal_value} {frac.std_dev}\n')
