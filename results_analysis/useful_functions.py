import os, re

def return_group_breakdown(syst):
  re_group_dict = {
      'Bu2Dst0h_D0pi0_Pdf\S+': '$B^{\\pm}\\rightarrow (D^{*}\\rightarrow D\\pi^{0})h^{\\pm}$ PDFs',
      'Bu2Dst0h_D0gamma_Pdf\S+': '$B^{\\pm}\\rightarrow (D^{*}\\rightarrow D\\gamma)h^{\\pm}$ PDFs',
      'Bu2Dst0h_D0pi0_WN\S+': 'Mis-reco. $B^{\\pm}\\rightarrow D^{*}h^{\\pm}$ PDFs',
      'Bu2Dst0h_D0gamma_WN\S+': 'Mis-reco. $B^{\\pm}\\rightarrow D^{*}h^{\\pm}$ PDFs',
      'Bd2Dsth_Pdf\S+': '$B^{0}\\rightarrow D^{*\\mp}h^{\\pm}$ PDFs',
      'Bu2D0hst_Pdf\S+': '$B^{\\pm}\\rightarrow Dh^{\\pm}\\pi$ PDFs',
      'Bu2Dst0hst_D0gamma_Pdf\S+': '$B^{\\pm}\\rightarrow D^{*}h^{\\pm}\\pi$ PDFs',
      'Bu2Dst0hst_D0pi0_Pdf\S+': '$B^{\\pm}\\rightarrow D^{*}h^{\\pm}\\pi$ PDFs',
      'Bu2Dst0hst_Pdf\S+': '$B^{\\pm}\\rightarrow D^{*}h^{\\pm}\\pi$ PDFs',
      'Bu2Dst0hst_Fra\S+': 'Branching fractions',
      'Lb2Omegach_Lcpi0_Pdf\S+': '$\\Lambda^{0}_{b}\\rightarrow \\Sigma_{c}^{\\pm}h^{\\mp}$ PDFs',
      'Bs2D0Kst0_Pdf\S+': '$B^{0}_{s}\\rightarrow D^{(*)}K^{\\mp}\\pi^{\\pm}$ PDFs',
      'Bs2Dst0Kst0_Pdf\S+': '$B^{0}_{s}\\rightarrow D^{(*)}K^{\\mp}\\pi^{\\pm}$ PDFs',
      'D02pik_Pdfs': 'Favoured to ADS crossfeed PDFs',
      'Bu2Dst0\S+_D0\S+_as\S+_Pdfs': 'Signal mis-ID PDFs',
      '\S+_misId_Pdfs': 'Background mis-ID PDFs',
      '\S+_BkgFrac': 'Branching fractions',
      'boxEffs_\S+': 'Box efficiencies',
      'mcEffs_\S+': 'Selection efficiencies',
      'pidEffK': 'PID efficiencies',
      'pidEffPi': 'PID efficiencies',
      'crossFeedRate': 'Rate of favoured to ADS crossfeed',
      'A_pi': 'Detector Asymmetries',
      'A_Kpi': 'Detector Asymmetries',
      'Delta_A_CP': 'Fixed $CP$ parameters',
      'A_pi_Kpi_Bu2Dst0h_D0\S+': 'Fixed $CP$ parameters',
      '\S+_Bu2Dst0h_WN': 'Fixed $CP$ parameters',
      '\S+_Bu2D0hst': 'Fixed $CP$ parameters',
      '\S+_Bu2Dst0hst': 'Fixed $CP$ parameters',
      '\S+_Bd2Dsth': 'Fixed $CP$ parameters',
      '\S+_Bu2Dst0h_D0gamma': 'Fixed $CP$ parameters',
      # '\S+_Lb2Omegach_Lcpi0': 'Fixed $CP$ parameters',
      'R_Dst0KDst0pi_Lb2Omegach_Lcpi0': 'Branching fractions',
      'kBF_D0\S+': 'Branching fractions',
      'Bs Systematic': '$B^{0}_{s}\\rightarrow D^{(*)}K^{\\mp}\\pi^{\\pm}$ box efficiencies and $m(B)$ PDFs'
  }
  match = False
  for k, v in re_group_dict.items():
    m = re.search(k, syst)
    if m:
      match = True
      return v
  if match == False:
    print('No regex match in return_group_breakdown for ' + syst)

def return_final_group(syst):
  re_group_dict = {
      'Bu2Dst0h_D0pi0_Pdf\S+': '$PDFs$',
      'Bu2Dst0h_D0gamma_Pdf\S+': '$PDFs$',
      'Bu2Dst0h_D0pi0_WN\S+': '$PDFs$',
      'Bu2Dst0h_D0gamma_WN\S+': '$PDFs$',
      'Bd2Dsth_Pdf\S+': '$PDFs$',
      'Bu2D0hst_Pdf\S+': '$PDFs$',
      'Bu2Dst0hst_D0gamma_Pdf\S+': '$PDFs$',
      'Bu2Dst0hst_D0pi0_Pdf\S+': '$PDFs$',
      'Bu2Dst0hst_Pdf\S+': '$PDFs$',
      'Bu2Dst0hst_Fra\S+': '$Rates$',
      'Lb2Omegach_Lcpi0_Pdf\S+': '$PDFs$',
      'Bs2D0Kst0_Pdf\S+': '$PDFs$',
      'Bs2Dst0Kst0_Pdf\S+': '$PDFs$',
      'D02pik_Pdfs': '$PDFs$',
      'Bu2Dst0\S+_D0\S+_as\S+_Pdfs': '$PDFs$',
      '\S+_misId_Pdfs': '$PDFs$',
      '\S+_BkgFrac': '$Rates$',
      'boxEffs_\S+': '$\\epsilon_{BOX}$',
      'mcEffs_\S+': '$\\epsilon_{sel}$',
      'pidEffK': '$\\epsilon_{PID}$',
      'pidEffPi': '$\\epsilon_{PID}$',
      'crossFeedRate': '$Rates$',
      'A_pi': '$Asyms$',
      'A_Kpi': '$Asyms$',
      'Delta_A_CP': '$CP$ $Pars$',
      'A_pi_Kpi_Bu2Dst0h_D0\S+': '$CP$ $Pars$',
      '\S+_Bu2Dst0h_WN': '$CP$ $Pars$',
      '\S+_Bu2D0hst': '$CP$ $Pars$',
      '\S+_Bu2Dst0hst': '$CP$ $Pars$',
      '\S+_Bd2Dsth': '$CP$ $Pars$',
      '\S+_Bu2Dst0h_D0gamma': '$CP$ $Pars$',
      # '\S+_Lb2Omegach_Lcpi0': 'Fixed $CP$ parameters',
      'R_Dst0KDst0pi_Lb2Omegach_Lcpi0': '$Rates$',
      'kBF_D0\S+': '$Rates$',
      'Statistical Error Correction': '$Corr$',
      'Bs Systematic': '$PDFs$'
  }
  match = False
  for k, v in re_group_dict.items():
    m = re.search(k, syst)
    if m:
      match = True
      return v
  if match == False:
    print('No regex match in return_final_group for ' + syst)

def neutral_label(n_str):
  if n_str == "gamma":
    return "\\gamma"
  else:
    return "\\pi^{0}"

def return_label(string):
  labels = {
      'Bu2Dst0pi_D0pi0':
          '$\\Bpm\\rightarrow(\\D\\piz)_{\\Dstar}\\pipm$',
      'Bu2Dst0pi_D0gamma':
          '$\\Bpm\\rightarrow(\\D\\gamma)_{\\Dstar}\\pipm$',
      'Bu2Dst0k_D0pi0':
          '$\\Bpm\\rightarrow(\\D\\piz)_{\\Dstar}\\Kpm$',
      'Bu2Dst0k_D0gamma':
          '$\\Bpm\\rightarrow(\\D\\gamma)_{\\Dstar}\\Kpm$',
      'kpi':
          '$\\kaon\\pion$',
      'kk':
          '$\\kaon\\kaon$',
      'pipi':
          '$\\pion\\pion$',
      'pik':
          '$\\pion\\kaon$',
      'R_Dst0KDst0pi_Bu2Dst0h_kpi':
          '$R^{K\\pi}_{K/\\pi}$',
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kpi':
          '$N_{(D^{*}\\rightarrow \\left[K\\pi\\right]_{D}\\gamma)\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kk':
          '$N_{(D^{*}\\rightarrow \\left[KK\\right]_{D}\\gamma)\\pi^{\\pm}}$',
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_pipi':
          '$N_{(D^{*}\\rightarrow \\left[\\pi\\pi\\right]_{D}\\gamma)\\pi^{\\pm}}$',
      'R_CP_Bu2Dst0h_D0gamma_Blind':
          '$R^{CP,\\gamma}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_pi_total':
          '$R^{\\pi K,\\gamma}_{\\pi}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_k_total':
          '$R^{\\pi K,\\gamma}_{K}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_pi_plus':
          '$R^{\\pi K,\\gamma}_{\\pi^{+}}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_k_plus':
          '$R^{\\pi K,\\gamma}_{K^{+}}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_pi_minus':
          '$R^{\\pi K,\\gamma}_{\\pi^{-}}$',
      'R_piK_Bu2Dst0h_D0gamma_Blind_k_minus':
          '$R^{\\pi K,\\gamma}_{K^{-}}$',
      'R_CP_Bu2Dst0h_D0gamma':
          '$R^{CP,\\gamma}$',
      'R_piK_Bu2Dst0h_D0gamma_pi_total':
          '$R^{\\pi K,\\gamma}_{\\pi}$',
      'R_piK_Bu2Dst0h_D0gamma_k_total':
          '$R^{\\pi K,\\gamma}_{K}$',
      'R_piK_Bu2Dst0h_D0gamma_pi_plus':
          '$R^{\\pi K,\\gamma}_{\\pi^{+}}$',
      'R_piK_Bu2Dst0h_D0gamma_k_plus':
          '$R^{\\pi K,\\gamma}_{K^{+}}$',
      'R_piK_Bu2Dst0h_D0gamma_pi_minus':
          '$R^{\\pi K,\\gamma}_{\\pi^{-}}$',
      'R_piK_Bu2Dst0h_D0gamma_k_minus':
          '$R^{\\pi K,\\gamma}_{K^{-}}$',
      'A_Bu2Dst0h_D0gamma_gamma_k_kpi':
          '$A^{K\\pi,\\gamma}_{K}$',
      'A_Bu2Dst0h_D0pi0_gamma_k_kpi':
          '$A^{K\\pi,\\pi^{0}}_{K}$',
      'A_CP_Bu2Dst0h_D0gamma_Blind_pi':
          '$A^{CP,\\gamma}_{\\pi}$',
      'A_CP_Bu2Dst0h_D0gamma_Blind_k':
          '$A^{CP,\\gamma}_{K}$',
      'A_CP_Bu2Dst0h_D0gamma_pi':
          '$A^{CP,\\gamma}_{\\pi}$',
      'A_CP_Bu2Dst0h_D0gamma_k':
          '$A^{CP,\\gamma}_{K}$',
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
      'R_CP_Bu2Dst0h_D0pi0_Blind':
          '$R^{CP,\\pi^{0}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_pi_total':
          '$R^{\\pi K,\\pi^{0}}_{\\pi}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_k_total':
          '$R^{\\pi K,\\pi^{0}}_{K}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_pi_plus':
          '$R^{\\pi K,\\pi^{0}}_{\\pi^{+}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_k_plus':
          '$R^{\\pi K,\\pi^{0}}_{K^{+}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_pi_minus':
          '$R^{\\pi K,\\pi^{0}}_{\\pi^{-}}$',
      'R_piK_Bu2Dst0h_D0pi0_Blind_k_minus':
          '$R^{\\pi K,\\pi^{0}}_{K^{-}}$',
      'R_CP_Bu2Dst0h_D0pi0':
          '$R^{CP,\\pi^{0}}$',
      'R_piK_Bu2Dst0h_D0pi0_pi_total':
          '$R^{\\pi K,\\pi^{0}}_{\\pi}$',
      'R_piK_Bu2Dst0h_D0pi0_k_total':
          '$R^{\\pi K,\\pi^{0}}_{K}$',
      'R_piK_Bu2Dst0h_D0pi0_pi_plus':
          '$R^{\\pi K,\\pi^{0}}_{\\pi^{+}}$',
      'R_piK_Bu2Dst0h_D0pi0_k_plus':
          '$R^{\\pi K,\\pi^{0}}_{K^{+}}$',
      'R_piK_Bu2Dst0h_D0pi0_pi_minus':
          '$R^{\\pi K,\\pi^{0}}_{\\pi^{-}}$',
      'R_piK_Bu2Dst0h_D0pi0_k_minus':
          '$R^{\\pi K,\\pi^{0}}_{K^{-}}$',
      'A_Bu2Dst0h_D0pi0_pi0_k_kpi':
          '$A^{K\\pi,\\pi^{0}}_{K}$',
      'A_Bu2Dst0h_D0pi0_pi0_k_kpi':
          '$A^{K\\pi,\\pi^{0}}_{K}$',
      'A_CP_Bu2Dst0h_D0pi0_Blind_pi':
          '$A^{CP,\\pi^{0}}_{\\pi}$',
      'A_CP_Bu2Dst0h_D0pi0_Blind_k':
          '$A^{CP,\\pi^{0}}_{K}$',
      'A_CP_Bu2Dst0h_D0pi0_pi':
          '$A^{CP,\\pi^{0}}_{\\pi}$',
      'A_CP_Bu2Dst0h_D0pi0_k':
          '$A^{CP,\\pi^{0}}_{K}$',
  }
  if string in labels:
    l = labels[string]
    return l
  else:
    print("ERROR: label does not exist for " + string)
    return string

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
