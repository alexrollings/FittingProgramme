import os

def neutral_label(n_str):
  if n_str == "gamma":
    return "\\gamma"
  else:
    return "\\pi^{0}"

def return_label(observable_string):
  labels = {
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kpi':
          '$N_{(D^{0*}\\rightarrow \\left[K\\pi\\right]_{D^{0}}\\gamma)\\pi}$',
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kk':
          '$N_{(D^{0*}\\rightarrow \\left[KK\\right]_{D^{0}}\\gamma)\\pi}$',
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_pipi':
          '$N_{(D^{0*}\\rightarrow \\left[\\pi\\pi\\right]_{D^{0}}\\gamma)\\pi}$',
      'R_Dst0KDst0pi_Bu2Dst0h_D0gamma_gamma_kpi':
          '$R^{D^{0*}K/D^{0*}\\pi}_{D\\gamma}$',
      'R_CP_Bu2Dst0h_D0gamma_Blind_gamma_kk':
          '$R^{CP}_{D\\gamma}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_pi_pik_total':
          '$R^{\\pm}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\gamma)\\pi}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_k_pik_total':
          '$R^{\\pm}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\gamma)K}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_pi_pik_plus':
          '$R^{+}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\gamma)\\pi}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_k_pik_plus':
          '$R^{+}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\gamma)K}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_pi_pik_minus':
          '$R^{-}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\gamma)\\pi}$',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_k_pik_minus':
          '$R^{-}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\gamma)K}$',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kpi':
          '$N_{(D^{0*}\\rightarrow \\left[K\\pi\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kk':
          '$N_{(D^{0*}\\rightarrow \\left[KK\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_pipi':
          '$N_{(D^{0*}\\rightarrow \\left[\\pi\\pi\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_gamma_kpi':
          '$R^{D^{0*}K/D^{0*}\\pi}_{D\\pi^{0}}$',
      'R_CP_Bu2Dst0h_D0pi0_Blind_gamma_kk':
          '$R^{CP}_{D\\pi^{0}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_total':
          '$R^{\\pm}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_total':
          '$R^{\\pm}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})K}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_plus':
          '$R^{+}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_plus':
          '$R^{+}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})K}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_minus':
          '$R^{-}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_minus':
          '$R^{-}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})K}$',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kpi':
          '$N_{(D^{0*}\\rightarrow \\left[K\\pi\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kk':
          '$N_{(D^{0*}\\rightarrow \\left[KK\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_pipi':
          '$N_{(D^{0*}\\rightarrow \\left[\\pi\\pi\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_pi0_kpi':
          '$R^{D^{0*}K/D^{0*}\\pi}_{D\\pi^{0}}$',
      'R_CP_Bu2Dst0h_D0pi0_Blind_pi0_kk':
          '$R^{CP}_{D\\pi^{0}}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_total':
          '$R^{\\pm}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_total':
          '$R^{\\pm}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})K}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_plus':
          '$R^{+}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_plus':
          '$R^{+}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})K}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_minus':
          '$R^{-}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})\\pi}$',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_minus':
          '$R^{-}_{(D^{0*}\\rightarrow \\left[\\pi K\\right]_{D^{0}}\\pi^{0})K}$'
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
