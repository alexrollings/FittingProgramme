import os

def return_label(observable_string):
  labels = {
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kpi':
          'N_{\\left(D^{*}\\rightarrow \\left[K\\pi\\right]_{D}\\gamma\\right)π}',
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_kk':
          'N_{\\left(D^{*}\\rightarrow \\left[KK\\right]_{D}\\gamma\\right)π}',
      'N_tot_Bu2Dst0h_D0gamma_gamma_pi_pipi':
          'N_{\\left(D^{*}\\rightarrow \\left[\\pi\\pi\\right]_{D}\\gamma\\right)π}',
      'R_Dst0KDst0pi_Bu2Dst0h_D0gamma_gamma_kpi':
          'R^{D^{*}K/D^{*}\\pi}_{D\\gamma}',
      'R_CP_Bu2Dst0h_D0gamma_Blind_gamma_kk':
          'R^{CP}_{D\\gamma}',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_pi_pik_total':
          'R^{\\pm}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\gamma\\right)π}',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_k_pik_total':
          'R^{\\pm}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\gamma\\right)K}',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_pi_pik_plus':
          'R^{+}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\gamma\\right)π}',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_k_pik_plus':
          'R^{+}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\gamma\\right)K}',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_pi_pik_minus':
          'R^{-}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\gamma\\right)π}',
      'R_ADS_Bu2Dst0h_D0gamma_Blind_gamma_k_pik_minus':
          'R^{-}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\gamma\\right)K}',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kpi':
          'N_{\\left(D^{*}\\rightarrow \\left[K\\pi\\right]_{D}\\pi^{0}\\right)π}',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_kk':
          'N_{\\left(D^{*}\\rightarrow \\left[KK\\right]_{D}\\pi^{0}\\right)π}',
      'N_tot_Bu2Dst0h_D0pi0_gamma_pi_pipi':
          'N_{\\left(D^{*}\\rightarrow \\left[\\pi\\pi\\right]_{D}\\pi^{0}\\right)π}',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_gamma_kpi':
          'R^{D^{*}K/D^{*}\\pi}_{D\\pi^{0}}',
      'R_CP_Bu2Dst0h_D0pi0_Blind_gamma_kk':
          'R^{CP}_{D\\pi^{0}}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_total':
          'R^{\\pm}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)π}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_total':
          'R^{\\pm}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)K}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_plus':
          'R^{+}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)π}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_plus':
          'R^{+}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)K}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_pi_pik_minus':
          'R^{-}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)π}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_gamma_k_pik_minus':
          'R^{-}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)K}',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kpi':
          'N_{\\left(D^{*}\\rightarrow \\left[K\\pi\\right]_{D}\\pi^{0}\\right)π}',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_kk':
          'N_{\\left(D^{*}\\rightarrow \\left[KK\\right]_{D}\\pi^{0}\\right)π}',
      'N_tot_Bu2Dst0h_D0pi0_pi0_pi_pipi':
          'N_{\\left(D^{*}\\rightarrow \\left[\\pi\\pi\\right]_{D}\\pi^{0}\\right)π}',
      'R_Dst0KDst0pi_Bu2Dst0h_D0pi0_pi0_kpi':
          'R^{D^{*}K/D^{*}\\pi}_{D\\pi^{0}}',
      'R_CP_Bu2Dst0h_D0pi0_Blind_pi0_kk':
          'R^{CP}_{D\\pi^{0}}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_total':
          'R^{\\pm}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)π}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_total':
          'R^{\\pm}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)K}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_plus':
          'R^{+}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)π}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_plus':
          'R^{+}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)K}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_pi_pik_minus':
          'R^{-}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)π}',
      'R_ADS_Bu2Dst0h_D0pi0_Blind_pi0_k_pik_minus':
          'R^{-}_\\left(D^{*}\\rightarrow \\left[\\pi K\\right]_{D}\\pi^{0}\\right)K}'
  }
  if observable_string in labels:
    l = labels[observable_string]
    return l
  else:
    print("ERROR: label does noe exist for " + observable_string)
    return observable_string

