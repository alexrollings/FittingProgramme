#pragma once
#include "BachelorDaughtersVars.h"
#include "Configuration.h"
#include "NeutralBachelorChargeVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralDaughtersVars.h"
#include "NeutralVars.h"
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
                                RooAbsReal &mcEffPi, RooAbsReal &mcEffK) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, Bachelor::k, daughters)).c_str(),
      "", "@0*@1*(@2/@3)", RooArgSet(N_tot_pi, ratio, mcEffPi, mcEffK));
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

// CP yield for Bs background = πk yield * BR (D->CP/D->kπ)
template <Neutral neutral, Bachelor bachelor, Daughters daughters>
RooFormulaVar *Make_N_tot_Bs_CP(int uniqueId, const char *name,
                                RooAbsReal &N_tot_Bs_pik) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, bachelor, daughters)).c_str(), "",
      "@0*(@1/@2)",
      RooArgSet(
          N_tot_Bs_pik,
          BachelorDaughtersVars<Bachelor::pi, daughters>::Get(uniqueId).kBR(),
          BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
              .kBR()));
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
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::kk> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi,
                                        Daughters::pipi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::pik> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::kpi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::pik> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::kk> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::pipi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
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
  std::shared_ptr<RooRealVar> A_MisRec_GetPointer() { return impl_.A_MisRec_; }
  std::shared_ptr<RooRealVar> A_Bu2D0h_GetPointer() { return impl_.A_Bu2D0h_; }
  std::shared_ptr<RooRealVar> A_PartRec_GetPointer() {
    return impl_.A_PartRec_;
  }
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_GetPointer() {
    return impl_.A_Bs2Dst0Kpi_;
  }
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_GetPointer() {
    return impl_.A_Bs2D0Kpi_;
  }

  RooAbsReal &A_Bu2Dst0h_D0gamma() { return *impl_.A_Bu2Dst0h_D0gamma_; }
  RooAbsReal &A_Bu2Dst0h_D0pi0() { return *impl_.A_Bu2Dst0h_D0pi0_; }
  RooAbsReal &A_Bu2Dst0h_D0pi0_WN() { return *impl_.A_Bu2Dst0h_D0pi0_WN_; }
  RooRealVar &A_MisRec() { return *impl_.A_MisRec_; }
  RooRealVar &A_Bu2D0h() { return *impl_.A_Bu2D0h_; }
  RooRealVar &A_PartRec() { return *impl_.A_PartRec_; }
  RooAbsReal &A_Bs2Dst0Kpi() { return *impl_.A_Bs2Dst0Kpi_; }
  RooAbsReal &A_Bs2D0Kpi() { return *impl_.A_Bs2D0Kpi_; }

  RooFormulaVar &a_Bu2Dst0h_D0gamma() { return *impl_.a_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &a_Bu2Dst0h_D0pi0() { return *impl_.a_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &a_Bu2Dst0h_D0pi0_WN() { return *impl_.a_Bu2Dst0h_D0pi0_WN_; }
  RooFormulaVar &a_MisRec() { return *impl_.a_MisRec_; }
  RooFormulaVar &a_Bu2D0h() { return *impl_.a_Bu2D0h_; }
  RooFormulaVar &a_PartRec() { return *impl_.a_PartRec_; }
  RooFormulaVar &a_Bs2Dst0Kpi() { return *impl_.a_Bs2Dst0Kpi_; }
  RooFormulaVar &a_Bs2D0Kpi() { return *impl_.a_Bs2D0Kpi_; }

  RooAbsReal &N_tot_Bu2Dst0h_D0gamma() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_tot_Bu2Dst0h_D0pi0() { return *impl_.N_tot_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_tot_Bu2Dst0h_D0pi0_WN() { return *impl_.N_tot_Bu2Dst0h_D0pi0_WN_; }
  RooFormulaVar &N_tot_Bu2Dst0h_D0gamma_FAVasSUP() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooFormulaVar &N_tot_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *impl_.N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooAbsReal &N_tot_MisRec() { return *impl_.N_tot_MisRec_; }
  RooAbsReal &N_tot_Bu2D0h() { return *impl_.N_tot_Bu2D0h_; }
  RooAbsReal &N_tot_PartRec() { return *impl_.N_tot_PartRec_; }
  RooAbsReal &N_tot_Bs2Dst0Kpi() { return *impl_.N_tot_Bs2Dst0Kpi_; }
  RooAbsReal &N_tot_Bs2D0Kpi() { return *impl_.N_tot_Bs2D0Kpi_; }

 private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...

  // Indicate if only used by one daughters
  int uniqueId_;

  NeutralBachelorDaughtersVarsImpl<neutral, bachelor, daughters> impl_;
};

