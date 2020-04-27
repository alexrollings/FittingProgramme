import os, re

def return_group(syst):
  re_group_dict = {
      'misId\S+PiPdf': 'MisId$_{K\\rightarrow \\pi}$',
      'misId\S+KPdf': 'MisId$_{\\pi\\rightarrow K}$',
      'partRec\S+': 'Part-reco PDFs',
      'Bs2Dst0\S+': 'Part-reco PDFs',
      'misRec\S+': 'Mis-reco PDFs',
      'Bs2D0\S+': 'Mis-reco PDFs',
      'crossFeed\S+': 'Mis-reco PDFs',
      '\S+CutEffs': '$\epsilon_{BOX}$',
      'pidEffK': '$\epsilon_{PIDK}$',
      'pidEffK': '$\epsilon_{PIDK}$',
      'pi0\S+': 'Signal PDFs',
      'gamma\S+': 'Signal PDFs',
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
      'R_Dst0KDst0pi_Bu2Dst0h_D0gamma_gamma_kpi':
          '$R^{D^{*}K/D^{*}\\pi}_{D\\gamma}$',
      'R_CP_Bu2Dst0h_D0gamma_Blind_gamma_kk':
          '$R^{CP}_{D\\gamma}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_pi_pik_total':
          '$R^{\\pm}_{(D\\gamma)\\pi^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_k_pik_total':
          '$R^{\\pm}_{(D\\gamma)K^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_pi_pik_plus':
          '$R^{+}_{(D\\gamma)\\pi^{+}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_k_pik_plus':
          '$R^{+}_{(D\\gamma)K^{+}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_pi_pik_minus':
          '$R^{-}_{(D\\gamma)\\pi^{-}}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_k_pik_minus':
          '$R^{-}_{(D\\gamma)K^{-}}$',
      'A_Bu2Dst0h_D0gamma_Blind_gamma_pi_kpi':
          '$A^{K\\pi}_{(D\\gamma)\\pi^{\\pm}}$',
      'A_Bu2Dst0h_D0gamma_Blind_gamma_pi_kk':
          '$A^{CP}_{(D\\gamma)\\pi^{\\pm}}$',
      'A_Bu2Dst0h_D0gamma_Blind_gamma_k_kpi':
          '$A^{K\\pi}_{(D\\gamma)K^{\\pm}}$',
      'A_Bu2Dst0h_D0gamma_Blind_gamma_k_kk':
          '$A^{CP}_{(D\\gamma)K^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kpi':
          '$N_{(D^{*}\\rightarrow \\left[K\\pi\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kk':
          '$N_{(D^{*}\\rightarrow \\left[KK\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_pipi':
          '$N_{(D^{*}\\rightarrow \\left[\\pi\\pi\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_gamma_kpi':
          '$R^{D^{*}K/D^{*}\\pi}_{D\\pi^{0}}$',
      'R_CP_Bu2Dst0h_D0pi0_Blind_gamma_kk':
          '$R^{CP}_{D\\pi^{0}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_total':
          '$R^{\\pm}_{(D\\pi^{0})\\pi^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_total':
          '$R^{\\pm}_{(D\\pi^{0})K^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_plus':
          '$R^{+}_{(D\\pi^{0})\\pi^{+}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_plus':
          '$R^{+}_{(D\\pi^{0})K^{+}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_minus':
          '$R^{-}_{(D\\pi^{0})\\pi^{-}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_minus':
          '$R^{-}_{(D\\pi^{0})K^{-}}$',
      'A_Bu2Dst0h_D0pi0_Blind_gamma_pi_kpi':
          '$A^{K\\pi}_{(D\\pi^{0})\\pi^{\\pm}}$',
      'A_Bu2Dst0h_D0pi0_Blind_gamma_pi_kk':
          '$A^{CP}_{(D\\pi^{0})\\pi^{\\pm}}$',
      'A_Bu2Dst0h_D0pi0_Blind_gamma_k_kpi':
          '$A^{K\\pi}_{(D\\pi^{0})K^{\\pm}}$',
      'A_Bu2Dst0h_D0pi0_Blind_gamma_k_kk':
          '$A^{CP}_{(D\\pi^{0})K^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kpi':
          '$N_{(D^{*}\\rightarrow \\left[K\\pi\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kk':
          '$N_{(D^{*}\\rightarrow \\left[KK\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_pipi':
          '$N_{(D^{*}\\rightarrow \\left[\\pi\\pi\\right]_{D}\\pi^{0})\\pi^{\\pm}}$',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_pi0_kpi':
          '$R^{D^{*}K/D^{*}\\pi}_{D\\pi^{0}}$',
      'R_CP_Bu2Dst0h_D0pi0_Blind_pi0_kk':
          '$R^{CP}_{D\\pi^{0}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_total':
          '$R^{\\pm}_{(D\\pi^{0})\\pi^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_total':
          '$R^{\\pm}_{(D\\pi^{0})K^{\\pm}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_plus':
          '$R^{+}_{(D\\pi^{0})\\pi^{+}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_plus':
          '$R^{+}_{(D\\pi^{0})K^{+}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_minus':
          '$R^{-}_{(D\\pi^{0})\\pi^{-}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_minus':
          '$R^{-}_{(D\\pi^{0})K^{-}}$',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_pi_kpi':
          '$A^{K\\pi}_{(D\\pi^{0})\\pi^{\\pm}}$',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_pi_kk':
          '$A^{CP}_{(D\\pi^{0})\\pi^{\\pm}}$',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_k_kpi':
          '$A^{K\\pi}_{(D\\pi^{0})K^{\\pm}}$',
      'A_Bu2Dst0h_D0pi0_Blind_pi0_k_kk':
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
