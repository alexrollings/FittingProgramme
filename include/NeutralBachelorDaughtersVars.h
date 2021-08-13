#pragma once
#include "Configuration.h"
#include "BachelorChargeVars.h"
#include "BachelorVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "DaughtersVars.h"
#include "Params.h"
#include "RooUnblindUniform.h"
// Templated classes/functions mean that the compiler will automatically create
// a copy
// of the entire class for you for every permutation of template arguments it is
// called
// with. This is handy because often a lot of the code is identical except for a
// few
// details.
// However, everything the compiler needs to do so must be provided in the .h
// file,
// because otherwise it won't actually know how to cater to external callers to
// your
// class/function (unless you explicitly specialize, see below).
//
template <Neutral neutral, Daughters daughters>
RooFormulaVar *Make_N_tot_k_kpi(int uniqueId, const char *name,
                                RooAbsReal &N_tot_pi, RooAbsReal &ratio,
                                RooAbsReal &mcEffPi, RooAbsReal &mcEffK,
                                RooAbsReal &orEffPi, RooAbsReal &orEffK) {
  std::cout << name << std::endl;
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, Bachelor::k, daughters)).c_str(),
      "", "@0*@1*(@2/@3)*(@4/@5)",
      // "", "@0*@1*(@2/@3)",
      RooArgSet(N_tot_pi, ratio, mcEffK, mcEffPi, orEffK, orEffPi));
      // RooArgSet(N_tot_pi, ratio, mcEffK, mcEffPi));
}

// DON'T need to multiple CP K yields by MC effs as ratio defined in terms of
// R_CP and FAV R(D*K/D*π)
template <Neutral neutral, Daughters daughters>
RooFormulaVar *Make_N_tot_k_CP(int uniqueId, const char *name,
                               RooAbsReal &N_tot_pi, RooAbsReal &ratio) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, Bachelor::k, daughters)).c_str(),
      "", "@0*@1", RooArgSet(N_tot_pi, ratio));
}

// FAVasSUP always pik daughter only
template <Neutral neutral, Bachelor bachelor>
RooFormulaVar *Make_N_tot_FAVasSUP(int uniqueId, const char *name,
                                   RooAbsReal &N_tot_FAV) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, bachelor, Daughters::pik)).c_str(),
      "", "@0*@1",
      RooArgSet(N_tot_FAV, GlobalVars::Get(uniqueId).crossFeedRate()));
}

//Overloaded fn for π0 mode, where Bu2Dst0h_WN yield is sum of Dg and Dπ
template <Neutral neutral, Bachelor bachelor>
RooFormulaVar *Make_N_tot_FAVasSUP(int uniqueId, const char *name,
                                   RooAbsReal &N_tot_FAV, RooAbsReal &frac_D0pi0) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, bachelor, Daughters::pik)).c_str(),
      "", "@0*@1*@2",
      RooArgSet(N_tot_FAV, frac_D0pi0,
                GlobalVars::Get(uniqueId).crossFeedRate()));
}

// CP yield for Bs background = πk yield * BR (D->CP/D->kπ)
template <Neutral neutral, Bachelor bachelor, Daughters daughters>
RooFormulaVar *Make_N_tot_Bs_CP(int uniqueId, const char *name,
                                RooAbsReal &N_tot_Bs_pik) {
  if (daughters == Daughters::kk) {
    return new RooFormulaVar(
        (name + ComposeName(uniqueId, neutral, bachelor, daughters)).c_str(),
        "", "@0*(@1/@2)",
        RooArgSet(N_tot_Bs_pik, GlobalVars::Get(uniqueId).kBF_D02kk(),
                  GlobalVars::Get(uniqueId).kBF_D02kpi()));
  } else if (daughters == Daughters::pipi) {
    return new RooFormulaVar(
        (name + ComposeName(uniqueId, neutral, bachelor, daughters)).c_str(),
        "", "@0*(@1/@2)",
        RooArgSet(N_tot_Bs_pik, GlobalVars::Get(uniqueId).kBF_D02pipi(),
                  GlobalVars::Get(uniqueId).kBF_D02kpi()));
  } else {
    throw std::runtime_error("Make_N_tot_Bs_CP only for KK and ππ daughters");
  }
}

// Only for pik
template <Neutral neutral, Bachelor bachelor>
RooFormulaVar *Make_A_ADS(int uniqueId, const char *name,
                          RooAbsReal &R_piK_minus, RooAbsReal &R_piK_plus) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, bachelor, Daughters::pik)).c_str(),
      "", "(@0-@1)/(@0+@1)", RooArgSet(R_piK_minus, R_piK_plus));
}

// In pik, N_tot = N_tot_kpi * R_ADS
template <Neutral neutral, Bachelor bachelor>
RooFormulaVar *Make_N_tot_pik(int uniqueId, const char *name,
                              RooAbsReal &N_tot_kpi, RooAbsReal &R_ADS) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, bachelor, Daughters::pik)).c_str(),
      "", "@0*@1", RooArgSet(N_tot_kpi, R_ADS));
}

// CP mode asymmetries: shifted by Delta_A_CP
template <Neutral neutral, Bachelor bachelor, Daughters daughters>
RooFormulaVar *Make_A_D2CP(int uniqueId, const char *name, RooAbsReal &A_CP) {
  switch (daughters) {
    case Daughters::kk:
      return new RooFormulaVar(
          (name + ComposeName(uniqueId, neutral, bachelor, daughters)).c_str(),
          "", "@0+0.5*@1",
          RooArgList(A_CP, GlobalVars::Get(uniqueId).Delta_A_CP()));
      break;
    case Daughters::pipi:
      return new RooFormulaVar(
          (name + ComposeName(uniqueId, neutral, bachelor, daughters)).c_str(),
          "", "@0-0.5*@1",
          RooArgList(A_CP, GlobalVars::Get(uniqueId).Delta_A_CP()));
      break;
  }
}

namespace {  // Anonymous namespace

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl;

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::kpi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> A_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> A_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kst0_;
  std::shared_ptr<RooAbsReal> A_comb_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> a_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> a_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> a_comb_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooAbsReal> N_tot_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kst0_;
  std::shared_ptr<RooAbsReal> N_tot_comb_;
  std::shared_ptr<RooRealVar> Bu2D0hst_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_sigma1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_sigma2Bu_;
  std::shared_ptr<RooCBShape> pdf1Bu_Bu2D0hst_;
  std::shared_ptr<RooGaussian> pdf2Bu_Bu2D0hst_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_D0gamma_mean2Bu_;
  std::unique_ptr<RooCBShape> pdf1Bu_Bu2Dst0hst_D0gamma_;
  std::unique_ptr<RooCBShape> pdf2Bu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_;
  std::shared_ptr<RooRealVar> Bu2D0hst_aDelta_;
  std::shared_ptr<RooDstD0BG> pdfDelta_Bu2D0hst_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::kk> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> A_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> A_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kst0_;
  std::shared_ptr<RooAbsReal> A_comb_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> a_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> a_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> a_comb_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooAbsReal> N_tot_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> fracComb_;
  std::shared_ptr<RooAbsReal> N_tot_comb_;
  std::shared_ptr<RooRealVar> Bu2D0hst_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_sigma1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_sigma2Bu_;
  std::shared_ptr<RooCBShape> pdf1Bu_Bu2D0hst_;
  std::shared_ptr<RooGaussian> pdf2Bu_Bu2D0hst_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_D0gamma_mean2Bu_;
  std::unique_ptr<RooCBShape> pdf1Bu_Bu2Dst0hst_D0gamma_;
  std::unique_ptr<RooCBShape> pdf2Bu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_;
  std::shared_ptr<RooRealVar> Bu2D0hst_aDelta_;
  std::shared_ptr<RooDstD0BG> pdfDelta_Bu2D0hst_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::pipi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> A_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> A_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kst0_;
  std::shared_ptr<RooAbsReal> A_comb_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> a_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> a_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> a_comb_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooAbsReal> N_tot_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> fracComb_;
  std::shared_ptr<RooAbsReal> N_tot_comb_;
  std::shared_ptr<RooRealVar> Bu2D0hst_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_sigma1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_sigma2Bu_;
  std::shared_ptr<RooCBShape> pdf1Bu_Bu2D0hst_;
  std::shared_ptr<RooGaussian> pdf2Bu_Bu2D0hst_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_D0gamma_mean2Bu_;
  std::unique_ptr<RooCBShape> pdf1Bu_Bu2Dst0hst_D0gamma_;
  std::unique_ptr<RooCBShape> pdf2Bu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_;
  std::shared_ptr<RooRealVar> Bu2D0hst_aDelta_;
  std::shared_ptr<RooDstD0BG> pdfDelta_Bu2D0hst_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::pik> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> A_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> A_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kst0_;
  std::shared_ptr<RooAbsReal> A_comb_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> a_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> a_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> a_comb_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooAbsReal> N_tot_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> fracComb_;
  std::shared_ptr<RooAbsReal> N_tot_comb_;
  std::shared_ptr<RooRealVar> Bu2D0hst_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_sigma1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_sigma2Bu_;
  std::shared_ptr<RooCBShape> pdf1Bu_Bu2D0hst_;
  std::shared_ptr<RooGaussian> pdf2Bu_Bu2D0hst_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_D0gamma_mean2Bu_;
  std::unique_ptr<RooCBShape> pdf1Bu_Bu2Dst0hst_D0gamma_;
  std::unique_ptr<RooCBShape> pdf2Bu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_;
  std::shared_ptr<RooRealVar> Bu2D0hst_aDelta_;
  std::shared_ptr<RooDstD0BG> pdfDelta_Bu2D0hst_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::kpi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> A_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_Bu2D0hst_;
  std::shared_ptr<RooGaussian> A_Bu2D0hst_gaus_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> A_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kst0_;
  std::shared_ptr<RooAbsReal> A_comb_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> a_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> a_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> a_comb_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooAbsReal> N_tot_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> fracComb_;
  std::shared_ptr<RooAbsReal> N_tot_comb_;
  std::shared_ptr<RooRealVar> Bu2D0hst_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_sigma1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_sigma2Bu_;
  std::shared_ptr<RooCBShape> pdf1Bu_Bu2D0hst_;
  std::shared_ptr<RooGaussian> pdf2Bu_Bu2D0hst_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_D0gamma_mean2Bu_;
  std::unique_ptr<RooCBShape> pdf1Bu_Bu2Dst0hst_D0gamma_;
  std::unique_ptr<RooCBShape> pdf2Bu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_;
  std::shared_ptr<RooRealVar> Bu2D0hst_aDelta_;
  std::shared_ptr<RooDstD0BG> pdfDelta_Bu2D0hst_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::kk> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> A_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> A_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kst0_;
  std::shared_ptr<RooAbsReal> A_comb_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> a_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> a_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> a_comb_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooAbsReal> N_tot_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> fracComb_;
  std::shared_ptr<RooAbsReal> N_tot_comb_;
  std::shared_ptr<RooRealVar> Bu2D0hst_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_sigma1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_sigma2Bu_;
  std::shared_ptr<RooCBShape> pdf1Bu_Bu2D0hst_;
  std::shared_ptr<RooGaussian> pdf2Bu_Bu2D0hst_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_D0gamma_mean2Bu_;
  std::unique_ptr<RooCBShape> pdf1Bu_Bu2Dst0hst_D0gamma_;
  std::unique_ptr<RooCBShape> pdf2Bu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_;
  std::shared_ptr<RooRealVar> Bu2D0hst_aDelta_;
  std::shared_ptr<RooDstD0BG> pdfDelta_Bu2D0hst_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::pipi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> A_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> A_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kst0_;
  std::shared_ptr<RooAbsReal> A_comb_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> a_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> a_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> a_comb_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooAbsReal> N_tot_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> fracComb_;
  std::shared_ptr<RooAbsReal> N_tot_comb_;
  std::shared_ptr<RooRealVar> Bu2D0hst_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_sigma1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_sigma2Bu_;
  std::shared_ptr<RooCBShape> pdf1Bu_Bu2D0hst_;
  std::shared_ptr<RooGaussian> pdf2Bu_Bu2D0hst_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_D0gamma_mean2Bu_;
  std::unique_ptr<RooCBShape> pdf1Bu_Bu2Dst0hst_D0gamma_;
  std::unique_ptr<RooCBShape> pdf2Bu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_;
  std::shared_ptr<RooRealVar> Bu2D0hst_aDelta_;
  std::shared_ptr<RooDstD0BG> pdfDelta_Bu2D0hst_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::pik> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> A_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> A_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kst0_;
  std::shared_ptr<RooAbsReal> A_comb_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> a_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> a_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> a_comb_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> N_tot_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooAbsReal> N_tot_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kst0_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> fracComb_;
  std::shared_ptr<RooAbsReal> N_tot_comb_;
  std::shared_ptr<RooRealVar> Bu2D0hst_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_sigma1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2D0hst_sigma2Bu_;
  std::shared_ptr<RooCBShape> pdf1Bu_Bu2D0hst_;
  std::shared_ptr<RooGaussian> pdf2Bu_Bu2D0hst_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_D0gamma_mean2Bu_;
  std::unique_ptr<RooCBShape> pdf1Bu_Bu2Dst0hst_D0gamma_;
  std::unique_ptr<RooCBShape> pdf2Bu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooFormulaVar> Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_;
  std::shared_ptr<RooRealVar> Bu2D0hst_aDelta_;
  std::shared_ptr<RooDstD0BG> pdfDelta_Bu2D0hst_;
};

}  // namespace

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
class NeutralBachelorDaughtersVars {
  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   DaughtersVars<Daughters::gamma>::Get()
  //   DaughtersVars<Daughters::pi0>::Get()
  // All happens automatically :-)

 public:
  // Need to construct the Impl field here (don't HAVE to do this if imple_
  // doesn't take an argument, as it happens implicitly.
  NeutralBachelorDaughtersVars(int uniqueId)
      : uniqueId_(uniqueId), impl_(uniqueId_) {}
  ~NeutralBachelorDaughtersVars() {}

  using This_t = NeutralBachelorDaughtersVars<neutral, bachelor, daughters>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  // Don't want to be able to access the blinded results
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kst0_GetPointer() {
    return impl_.A_Bs2Dst0Kst0_;
  }
  std::shared_ptr<RooAbsReal> A_Bs2D0Kst0_GetPointer() {
    return impl_.A_Bs2D0Kst0_;
  }
  std::shared_ptr<RooAbsReal> A_comb_GetPointer() {
    return impl_.A_comb_;
  }

  RooAbsReal &A_Bu2Dst0h_D0gamma() { return *impl_.A_Bu2Dst0h_D0gamma_; }
  RooAbsReal &A_Bu2Dst0h_D0pi0() { return *impl_.A_Bu2Dst0h_D0pi0_; }
  RooAbsReal &A_Bu2Dst0h_WN() { return *impl_.A_Bu2Dst0h_WN_; }
  RooAbsReal &A_Bd2Dsth() { return *impl_.A_Bd2Dsth_; }
  RooAbsReal &A_Bu2D0hst() { return *impl_.A_Bu2D0hst_; }
  RooAbsReal &A_Bu2Dst0hst() { return *impl_.A_Bu2Dst0hst_; }
  RooAbsReal &A_Lb2Omegach_Lcpi0() { return *impl_.A_Lb2Omegach_Lcpi0_; }
  RooAbsReal &A_Bs2Dst0Kst0() { return *impl_.A_Bs2Dst0Kst0_; }
  RooAbsReal &A_Bs2D0Kst0() { return *impl_.A_Bs2D0Kst0_; }
  RooAbsReal &A_comb() { return *impl_.A_comb_; }

  RooFormulaVar &a_Bu2Dst0h_D0gamma() { return *impl_.a_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &a_Bu2Dst0h_D0pi0() { return *impl_.a_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &a_Bu2Dst0h_WN() { return *impl_.a_Bu2Dst0h_WN_; }
  RooFormulaVar &a_Bd2Dsth() { return *impl_.a_Bd2Dsth_; }
  RooFormulaVar &a_Bu2D0hst() { return *impl_.a_Bu2D0hst_; }
  RooFormulaVar &a_Bu2Dst0hst() { return *impl_.a_Bu2Dst0hst_; }
  RooFormulaVar &a_Lb2Omegach_Lcpi0() { return *impl_.a_Lb2Omegach_Lcpi0_; }
  RooFormulaVar &a_Bs2Dst0Kst0() { return *impl_.a_Bs2Dst0Kst0_; }
  RooFormulaVar &a_Bs2D0Kst0() { return *impl_.a_Bs2D0Kst0_; }
  RooFormulaVar &a_comb() { return *impl_.a_comb_; }

  RooAbsReal &N_tot_Bu2Dst0h_D0pi0() { return *impl_.N_tot_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_tot_Bu2Dst0h_D0gamma() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_tot_Bu2Dst0h_D0pi0_WN() {
    return *impl_.N_tot_Bu2Dst0h_D0pi0_WN_;
  }
  RooAbsReal &N_tot_Bu2Dst0h_D0gamma_WN() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_WN_;
  }
  RooAbsReal &N_tot_Bu2Dst0h_WN() {
    return *impl_.N_tot_Bu2Dst0h_WN_;
  }
  RooAbsReal &N_tot_Bd2Dsth() { return *impl_.N_tot_Bd2Dsth_; }
  RooAbsReal &N_tot_Bu2D0hst() { return *impl_.N_tot_Bu2D0hst_; }
  RooAbsReal &N_tot_Bu2Dst0hst() {
    return *impl_.N_tot_Bu2Dst0hst_;
  }
  RooFormulaVar &N_tot_Bu2Dst0h_D0pi0_D02pik() {
    return *impl_.N_tot_Bu2Dst0h_D0pi0_D02pik_;
  }
  RooFormulaVar &N_tot_Bu2Dst0h_D0gamma_D02pik() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_D02pik_;
  }
  RooFormulaVar &N_tot_Bu2Dst0h_D0pi0_WN_D02pik() {
    return *impl_.N_tot_Bu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooFormulaVar &N_tot_Bu2Dst0h_D0gamma_WN_D02pik() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_WN_D02pik_;
  }
  RooAbsReal &N_tot_Lb2Omegach_Lcpi0() {
    return *impl_.N_tot_Lb2Omegach_Lcpi0_;
  }
  RooAbsReal &N_tot_Bs2Dst0Kst0() { return *impl_.N_tot_Bs2Dst0Kst0_; }
  RooAbsReal &N_tot_Bs2D0Kst0() { return *impl_.N_tot_Bs2D0Kst0_; }
  RooAbsReal &N_tot_comb() { return *impl_.N_tot_comb_; }
  std::shared_ptr<RooAbsReal> N_tot_comb_GetPointer() {
    return impl_.N_tot_comb_;
  }

  RooCBShape &pdf1Bu_Bu2D0hst() { return *impl_.pdf1Bu_Bu2D0hst_; }
  RooGaussian &pdf2Bu_Bu2D0hst() { return *impl_.pdf2Bu_Bu2D0hst_; }
  RooAbsPdf &pdfBu_Bu2D0hst() { return *impl_.pdfBu_Bu2D0hst_; }
  std::shared_ptr<RooRealVar> &Bu2Dst0hst_D0gamma_mean1Bu_GetPointer() {
    return impl_.Bu2Dst0hst_D0gamma_mean1Bu_;
  }
  std::shared_ptr<RooRealVar> &Bu2Dst0hst_D0gamma_fracPdf1Bu_GetPointer() {
    return impl_.Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  }
  RooAbsPdf &pdfBu_Bu2Dst0hst_D0gamma() {
    return *impl_.pdfBu_Bu2Dst0hst_D0gamma_;
  }
  RooAbsPdf &pdfBu_Bu2Dst0hst() { return *impl_.pdfBu_Bu2Dst0hst_; }
  RooDstD0BG &pdfDelta_Bu2D0hst() { return *impl_.pdfDelta_Bu2D0hst_; }

 private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...

  // Indicate if only used by one daughters
  int uniqueId_;

  NeutralBachelorDaughtersVarsImpl<neutral, bachelor, daughters> impl_;
};
