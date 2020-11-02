import os, re

def return_group(syst):
  re_group_dict = {
      'Bu2Dst0h_D0pi0_Pdf\S+': '$D\\pi^{0}$ signal PDFs',
      'Bu2Dst0h_D0gamma_Pdf\S+': '$D\\gamma$ signal PDFs',
      'Bu2Dst0h_D0pi0_WN\S+': 'Mis-reconstructed signal PDFs',
      'Bu2Dst0h_D0gamma_WN\S+': 'Mis-reconstructed signal PDFs',
      'Bd2Dsth_Pdf\S+': 'Mis-reconstructed background PDFs',
      'Bu2D0hst_Pdf\S+': 'Mis-reconstructed background PDFs',
      'Lb2Omegach_Lcpi0_Pdf\S+': 'Mis-reconstructed background PDFs',
      'D02pik_Pdfs': 'Mis-reconstructed background PDFs',
      'Bu2Dst0hst_D0gamma_Pdf\S+': 'Partially reconstructed PDFs',
      'Bu2Dst0hst_D0pi0_Pdf\S+': 'Partially reconstructed PDFs',
      'Bu2Dst0hst_Pdf\S+': 'Partially reconstructed PDFs',
      'Bu2Dst0hst_Frac\S+': 'Partially reconstructed PDFs',
      'Bs2D0Kpi_Pdf\S+': '$B_{s}$ PDFs',
      'Bs2Dst0Kpi_Pdf\S+': '$B_{s}$ PDFs',
      'Bu2Dst0\S+_D0\S+_as\S+_Pdfs': 'Mis-ID\'d signal PDFs',
      '\S+_misId_Pdfs': 'Mis-ID\'d background PDFs',
      '\S+_BkgFrac': 'Background Fractions',
      'boxEffs_\S+': '$\\epsilon_{BOX}$',
      'mcEffs_\S+': '$\\epsilon_{sel}$',
      'pidEffK': '$\\epsilon^{K}_{PIDK}$',
      'pidEffPi': '$\\epsilon^{\\pi}_{PIDK}$',
      'crossFeedRate': 'Rate of FAV as SUP',
      'A_pi': 'Detector Asymmetries',
      'A_Kpi': 'Detector Asymmetries',
      'Delta_A_CP': 'Detector Asymmetries',
      'A_pi_Kpi_Bu2Dst0h_D0pi0': 'FAV mode signal asymmetry',
      '\S+_Bu2Dst0h_WN': 'Background Physics parameters',
      '\S+_Bu2D0hst': 'Background Physics parameters',
      '\S+_Bu2Dst0hst': 'Background Physics parameters',
      '\S+_Bd2Dstpi': 'Background Physics parameters',
      '\S+_Lb2Omegach_Lcpi0': 'Background Physics parameters',
      'kBF_D0\S+': 'Background Physics parameters'
  }
  match = False
  for k, v in re_group_dict.items():
    m = re.search(k, syst)
    if m:
      match = True
      return v
  if match == False:
    print('No regex match in return_group for ' + syst)

def neutral_label(n_str):
  if n_str == "gamma":
    return "\\gamma"
  else:
    return "\\pi^{0}"

def return_label(observable_string):
  labels = {
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kpi':
          '$N_{(D^{*}\\rightarrow \\left[K\\pi\\right]_{D}\\gamma)\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kk':
          '$N_{(D^{*}\\rightarrow \\left[KK\\right]_{D}\\gamma)\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_pipi':
          '$N_{(D^{*}\\rightarrow \\left[\\pi\\pi\\right]_{D}\\gamma)\\pi^{\\pm}}$',
      'R_Dst0KDst0pi_Bu2Dst0h_D0gamma_kpi':
          '$R^{D^{*}K/D^{*}\\pi}_{D\\gamma}$',
      'R_CP_Bu2Dst0h_D0gamma_Blind':
          '$R^{CP}_{D\\gamma}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_pi_total':
          '$R^{\\pm}_{(D\\gamma)\\pi^{\\pm}}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_k_total':
          '$R^{\\pm}_{(D\\gamma)K^{\\pm}}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_pi_plus':
          '$R^{+}_{(D\\gamma)\\pi^{+}}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_k_plus':
          '$R^{+}_{(D\\gamma)K^{+}}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_pi_minus':
          '$R^{-}_{(D\\gamma)\\pi^{-}}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_k_minus':
          '$R^{-}_{(D\\gamma)K^{-}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_pi_pik_total':
          '$R^{\\pm}_{(D\\gamma)\\pi^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_k_pik_total':
          '$R^{\\pm}_{(D\\gamma)K^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_pi_pik_plus':
          '$R^{+}_{(D\\gamma)\\pi^{+}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_k_pik_plus':
          '$R^{+}_{(D\\gamma)K^{+}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_pi_pik_minus':
          '$R^{-}_{(D\\gamma)\\pi^{-}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_k_pik_minus':
          '$R^{-}_{(D\\gamma)K^{-}}$',
      'A_Bu2Dst0h_D0gamma_gamma_k_kpi':
          '$A^{K\\pi}_{(D\\gamma)K^{\\pm}}$',
      'A_Bu2Dst0h_D0pi0_gamma_k_kpi':
          '$A^{K\\pi}_{(D\\pi^{0})K^{\\pm}}$',
      'A_CP_Bu2Dst0h_D0gamma_Blind_pi':
          '$A^{CP}_{(D\\gamma)\\pi^{\\pm}}$',
      'A_CP_Bu2Dst0h_D0gamma_Blind_k':
          '$A^{CP}_{(D\\gamma)K^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kpi':
          '$N_{(D^{*}\\rightarrow \\left[K\\pi\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kk':
          '$N_{(D^{*}\\rightarrow \\left[KK\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_pipi':
          '$N_{(D^{*}\\rightarrow \\left[\\pi\\pi\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kpi':
          '$N_{(D^{*}\\rightarrow \\left[K\\pi\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kk':
          '$N_{(D^{*}\\rightarrow \\left[KK\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_pipi':
          '$N_{(D^{*}\\rightarrow \\left[\\pi\\pi\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_kpi':
          '$R^{D^{*}K/D^{*}\\pi}_{D\\pi^{0}}$',
      'R_CP_Bu2Dst0h_D0pi0_Blind':
          '$R^{CP}_{D\\pi^{0}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_pi_total':
          '$R^{\\pm}_{(D\\pi^{0})\\pi^{\\pm}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_k_total':
          '$R^{\\pm}_{(D\\pi^{0})K^{\\pm}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_pi_plus':
          '$R^{+}_{(D\\pi^{0})\\pi^{+}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_k_plus':
          '$R^{+}_{(D\\pi^{0})K^{+}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_pi_minus':
          '$R^{-}_{(D\\pi^{0})\\pi^{-}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_k_minus':
          '$R^{-}_{(D\\pi^{0})K^{-}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi_pik_total':
          '$R^{\\pm}_{(D\\pi^{0})\\pi^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_k_pik_total':
          '$R^{\\pm}_{(D\\pi^{0})K^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi_pik_plus':
          '$R^{+}_{(D\\pi^{0})\\pi^{+}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_k_pik_plus':
          '$R^{+}_{(D\\pi^{0})K^{+}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi_pik_minus':
          '$R^{-}_{(D\\pi^{0})\\pi^{-}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_k_pik_minus':
          '$R^{-}_{(D\\pi^{0})K^{-}}$',
      'A_Bu2Dst0h_D0pi0_pi0_k_kpi':
          '$A^{K\\pi}_{(D\\pi^{0})K^{\\pm}}$',
      'A_CP_Bu2Dst0h_D0pi0_Blind_pi':
          '$A^{CP}_{(D\\pi^{0})\\pi^{\\pm}}$',
      'A_CP_Bu2Dst0h_D0pi0_Blind_k':
          '$A^{CP}_{(D\\pi^{0})K^{\\pm}}$'
  }
  if observable_string in labels:
    l = labels[observable_string]
    return l
  else:
    print("ERROR: label does not exist for " + observable_string)
    return observable_string

# def get_systematic_label(s_str):
#   d = {'pi0DeltaTails' : '$\\pi^{0}$ signal PDF: $\\delta_{M}$ tails',
#       'pi0DeltaFrac' : '$\\pi^{0}$ signal PDF: fraction of CB1',
#       'pi0BuTails' : '$\\pi^{0}$ signal PDF: $m_{B}$ tails',
#       'pi0BuPartialTails' : 'Partial-$\\pi^{0}$ signal PDF: $m_{B}$ tails',
#       'pi0BuPartialFrac' : 'Partial-$\\pi^{0}$ signal PDF: $m_{B}$ fraction of CB1',
#       'pi0BuPartialSigma1' : 'Partial-$\\pi^{0}$ signal PDF: $m_{B}$ narrow width',
#       'crossFeedBuPdf' : '$m_{B}$ PDF of cross feed',
#
#   crossFeedBuPdf,
#   crossFeedBuPartialPdf,
#   crossFeedDeltaPdf,
#   gammaDeltaTails,
#   gammaDeltaFrac,
#   gammaBuTails,
#   gammaBuFrac,
#   misRecDeltaPdf,
#   misRecBuPdf,
#   misRecBuPartialPdf,
#   partRecDeltaPdf,
#   partRecBuPdf,
#   partRecBuPartialPdf,
