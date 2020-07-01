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
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
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
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
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
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
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
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
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
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
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
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
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
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
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
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> a_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> a_MisRec_;
  std::unique_ptr<RooFormulaVar> a_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> a_PartRec_;
  std::unique_ptr<RooFormulaVar> a_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> a_Bs2D0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
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
  static This_t &Get(int uniqueId) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId))
               .first;
    }
    return *it->second;
  }

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
  RooRealVar &A_MisRec() { return *impl_.A_MisRec_; }
  RooRealVar &A_Bu2D0h() { return *impl_.A_Bu2D0h_; }
  RooRealVar &A_PartRec() { return *impl_.A_PartRec_; }
  RooAbsReal &A_Bs2Dst0Kpi() { return *impl_.A_Bs2Dst0Kpi_; }
  RooAbsReal &A_Bs2D0Kpi() { return *impl_.A_Bs2D0Kpi_; }

  RooFormulaVar &a_Bu2Dst0h_D0gamma() { return *impl_.a_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &a_Bu2Dst0h_D0pi0() { return *impl_.a_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &a_MisRec() { return *impl_.a_MisRec_; }
  RooFormulaVar &a_Bu2D0h() { return *impl_.a_Bu2D0h_; }
  RooFormulaVar &a_PartRec() { return *impl_.a_PartRec_; }
  RooFormulaVar &a_Bs2Dst0Kpi() { return *impl_.a_Bs2Dst0Kpi_; }
  RooFormulaVar &a_Bs2D0Kpi() { return *impl_.a_Bs2D0Kpi_; }

  RooAbsReal &N_tot_Bu2Dst0h_D0gamma() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_tot_Bu2Dst0h_D0pi0() { return *impl_.N_tot_Bu2Dst0h_D0pi0_; }
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

// Now we just need to define the constructors separately so the values are
// different

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::kpi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
          0, 0.0005, Systematic::A_FAV_Pi0, Sign::none)),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::kpi, 0,
                                             -5, 5)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::kpi, 0,
                                             -5, 5)),
      A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                              Bachelor::pi, Daughters::kpi, 0,
                                              -5, 5)),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::pi,
          Daughters::kpi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0pi0() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Params::Get().CreateFloating(
          "N_tot_MisRec", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2D0h_(Params::Get().CreateFloating(
          "N_tot_Bu2D0h", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_PartRec_(Params::Get().CreateFloating(
          "N_tot_PartRec", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          0, 1000000)),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<
        RooRealVar>(Params::Get().CreateFloating(
        "N_tot_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi,
        Daughters::kpi,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0gamma() *
            BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000000, 1000000));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "A_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
        0, 0.0005, Systematic::A_FAV_Gamma, Sign::none));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::pik, 0,
                                             -5, 5)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::pik, 0,
                                             -5, 5)),
      A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                              Bachelor::pi, Daughters::pik, 0,
                                              -5, 5)),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(nullptr),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(
          Make_N_tot_FAVasSUP<_neutral, Bachelor::pi>(
              uniqueId, "N_tot_Bu2Dst0h_D0pi0_FAVasSUP_",
              NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                           Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0pi0())),
      N_tot_MisRec_(Params::Get().CreateFloating(
          "N_tot_MisRec", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2D0h_(Params::Get().CreateFloating(
          "N_tot_Bu2D0h", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_PartRec_(Params::Get().CreateFloating(
          "N_tot_PartRec", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          0, 1000000)),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().splitByCharge() == true) {
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral,
                                                                  Bachelor::pi>(
        uniqueId, "A_ADS_Bu2Dst0h_D0pi0_",
        NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::minus>::Get(
            uniqueId)
            .R_piK_Bu2Dst0h_D0pi0(),
        NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::plus>::Get(
            uniqueId)
            .R_piK_Bu2Dst0h_D0pi0()));
    a_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0pi0_));
    if (_neutral == Neutral::gamma) {
      A_Bu2Dst0h_D0gamma_ = std::shared_ptr<
          RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::pi>(
          uniqueId, "A_ADS_Bu2Dst0h_D0gamma_",
          NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::minus>::Get(
              uniqueId)
              .R_piK_Bu2Dst0h_D0gamma(),
          NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::plus>::Get(
              uniqueId)
              .R_piK_Bu2Dst0h_D0gamma()));
      a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_));
    }
  }
  N_tot_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .R_ADS_Bu2Dst0h_D0pi0()));
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::pi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .R_ADS_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_tot_FAVasSUP<_neutral, Bachelor::pi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_FAVasSUP_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma()));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0())),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::kk, 0, -5,
                                             5)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::kk, 0, -5,
                                             5)),
      A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                              Bachelor::pi, Daughters::kk, 0,
                                              -5, 5)),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::pi,
          Daughters::kk,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0pi0() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Params::Get().CreateFloating(
          "N_tot_MisRec", uniqueId, _neutral, Bachelor::pi, Daughters::kk,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2D0h_(Params::Get().CreateFloating(
          "N_tot_Bu2D0h", uniqueId, _neutral, Bachelor::pi, Daughters::kk,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_PartRec_(Params::Get().CreateFloating(
          "N_tot_PartRec", uniqueId, _neutral, Bachelor::pi, Daughters::kk,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          0, 1000000)),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<
        RooRealVar>(Params::Get().CreateFloating(
        "N_tot_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi,
        Daughters::kk,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0gamma() *
            BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000000, 1000000));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "A_Bu2Dst0h_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .A_CP_Bu2Dst0h_D0gamma()));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0())),
      A_MisRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                             Daughters::kk>::Get(uniqueId)
                    .A_MisRec_GetPointer()),
      A_Bu2D0h_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                             Daughters::kk>::Get(uniqueId)
                    .A_Bu2D0h_GetPointer()),
      A_PartRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                              Daughters::kk>::Get(uniqueId)
                     .A_PartRec_GetPointer()),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::pi,
          Daughters::pipi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0pi0() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Params::Get().CreateFloating(
          "N_tot_MisRec", uniqueId, _neutral, Bachelor::pi, Daughters::pipi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2D0h_(Params::Get().CreateFloating(
          "N_tot_Bu2D0h", uniqueId, _neutral, Bachelor::pi, Daughters::pipi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_PartRec_(Params::Get().CreateFloating(
          "N_tot_PartRec", uniqueId, _neutral, Bachelor::pi, Daughters::pipi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          0, 1000000)),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<
        RooRealVar>(Params::Get().CreateFloating(
        "N_tot_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi,
        Daughters::pipi,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0gamma() *
            BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000000, 1000000));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "A_Bu2Dst0h_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .A_CP_Bu2Dst0h_D0gamma()));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::kpi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "A_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::k, Daughters::kpi,
          0.01, -1, 1)),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::k, Daughters::kpi, 0, -1,
                                             1)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::k, Daughters::kpi, 0, -1,
                                             1)),
      A_PartRec_(nullptr),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(nullptr),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_MisRec_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_MisRec(),
          NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_MisRec(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2D0h_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2D0h_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2D0h(),
          NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0h())),
      N_tot_PartRec_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0gamma()));
    A_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::k,
            Daughters::kpi, -0.01, -1, 1));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    // Add systematic
    A_PartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "A_PartRec", uniqueId, _neutral, Bachelor::k, Daughters::kpi, 0, 0,
        Systematic::NA, Sign::none));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_PartRec", uniqueId, _neutral, Bachelor::k, Daughters::kpi,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::kpi>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    A_PartRec_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                     Bachelor::k, Daughters::kpi, 0, -5, 5));
    N_tot_PartRec_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
            uniqueId, "N_tot_PartRec_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_PartRec(),
            NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
                .R_Dst0KDst0pi_PartRec(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0()));
  }
  a_PartRec_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
      ("a_PartRec_" +
       ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
          .c_str(),
      *A_PartRec_));
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::k, Daughters::pik, 0, -1,
                                             1)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::k, Daughters::pik, 0, -1,
                                             1)),
      A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                              Bachelor::k, Daughters::pik, 0,
                                              -1, 1)),
      // Add systematic?
      A_Bs2Dst0Kpi_(Params::Get().CreateFixed(
          "A_Bs2Dst0Kpi", uniqueId, _neutral, Bachelor::k, Daughters::pik, 0, 0,
          Systematic::NA, Sign::none)),
      A_Bs2D0Kpi_(Params::Get().CreateFixed("A_Bs2D0Kpi", uniqueId, _neutral,
                                            Bachelor::k, Daughters::pik, 0, 0,
                                            Systematic::NA, Sign::none)),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(nullptr),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(MakeLittleAsym(
          ("a_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bs2Dst0Kpi_)),
      a_Bs2D0Kpi_(MakeLittleAsym(
          ("a_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bs2D0Kpi_)),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(Make_N_tot_FAVasSUP<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_FAVasSUP_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0())),
      N_tot_MisRec_(Make_N_tot_k_kpi<_neutral, Daughters::pik>(
          uniqueId, "N_tot_MisRec_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pik>::Get(uniqueId)
              .N_tot_MisRec(),
          NeutralDaughtersVars<_neutral, Daughters::pik>::Get(uniqueId)
              .R_Dst0KDst0pi_MisRec(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2D0h_(Make_N_tot_k_kpi<_neutral, Daughters::pik>(
          uniqueId, "N_tot_Bu2D0h_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pik>::Get(uniqueId)
              .N_tot_Bu2D0h(),
          NeutralDaughtersVars<_neutral, Daughters::pik>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0h())),
      N_tot_PartRec_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().splitByCharge() == true) {
    A_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
            uniqueId, "A_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::plus>::Get(
                uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    a_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0pi0_));
    if (_neutral == Neutral::gamma) {
      A_Bu2Dst0h_D0gamma_ = std::shared_ptr<
          RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
          uniqueId, "A_ADS_Bu2Dst0h_D0gamma_",
          NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::minus>::Get(
              uniqueId)
              .R_piK_Bu2Dst0h_D0gamma(),
          NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::plus>::Get(
              uniqueId)
              .R_piK_Bu2Dst0h_D0gamma()));
      a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_));
    }
  }
  N_tot_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .R_ADS_Bu2Dst0h_D0pi0()));
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::k>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .R_ADS_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_tot_FAVasSUP<_neutral, Bachelor::k>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_FAVasSUP_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma()));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_PartRec", uniqueId, _neutral, Bachelor::k, Daughters::pik,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    N_tot_PartRec_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::pik>(
            uniqueId, "N_tot_PartRec_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_PartRec(),
            NeutralDaughtersVars<_neutral, Daughters::pik>::Get(uniqueId)
                .R_Dst0KDst0pi_PartRec(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0()));
  }
  N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
      "N_tot_Bs2Dst0Kpi", uniqueId, _neutral, Bachelor::k, Daughters::pik,
      Configuration::Get().initYieldFAVSignal() *
          BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
              .kBR()
              .getVal(),
      -1000, 1000));
  N_tot_Bs2D0Kpi_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
      "N_tot_Bs2D0Kpi", uniqueId, _neutral, Bachelor::k, Daughters::pik,
      Configuration::Get().initYieldFAVSignal() *
          BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
              .kBR()
              .getVal(),
      -1000, 1000));
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0())),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::k, Daughters::kk, 0, -5,
                                             5)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::k, Daughters::kk, 0, -5,
                                             5)),
      A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                              Bachelor::k, Daughters::kk, 0, -5,
                                              5)),
      A_Bs2Dst0Kpi_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                 Daughters::pik>::Get(uniqueId)
                        .A_Bs2Dst0Kpi_GetPointer()),
      A_Bs2D0Kpi_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                               Daughters::pik>::Get(uniqueId)
                      .A_Bs2D0Kpi_GetPointer()),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(MakeLittleAsym(
          ("a_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bs2Dst0Kpi_)),
      a_Bs2D0Kpi_(MakeLittleAsym(
          ("a_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bs2D0Kpi_)),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Make_N_tot_k_kpi<_neutral, Daughters::kk>(
          uniqueId, "N_tot_MisRec_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_MisRec(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_MisRec(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2D0h_(Make_N_tot_k_kpi<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2D0h_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2D0h(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0h())),
      N_tot_PartRec_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().runADS() == true) {
    N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "N_tot_Bs2Dst0Kpi_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2Dst0Kpi()));
    N_tot_Bs2D0Kpi_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "N_tot_Bs2D0Kpi_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2D0Kpi()));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_k_CP<_neutral, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kk>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma()));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "A_Bu2Dst0h_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .A_CP_Bu2Dst0h_D0gamma()));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_PartRec", uniqueId, _neutral, Bachelor::k, Daughters::kk,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::kk>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    N_tot_PartRec_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kk>(
            uniqueId, "N_tot_PartRec_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kk>::Get(uniqueId)
                .N_tot_PartRec(),
            NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
                .R_Dst0KDst0pi_PartRec(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0()));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0())),
      A_MisRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                             Daughters::kk>::Get(uniqueId)
                    .A_MisRec_GetPointer()),
      A_Bu2D0h_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                             Daughters::kk>::Get(uniqueId)
                    .A_Bu2D0h_GetPointer()),
      A_PartRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                              Daughters::kk>::Get(uniqueId)
                     .A_PartRec_GetPointer()),
      A_Bs2Dst0Kpi_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                 Daughters::pik>::Get(uniqueId)
                        .A_Bs2Dst0Kpi_GetPointer()),
      A_Bs2D0Kpi_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                               Daughters::pik>::Get(uniqueId)
                      .A_Bs2D0Kpi_GetPointer()),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(MakeLittleAsym(
          ("a_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bs2Dst0Kpi_)),
      a_Bs2D0Kpi_(MakeLittleAsym(
          ("a_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bs2D0Kpi_)),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Make_N_tot_k_kpi<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_MisRec_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_MisRec(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_MisRec(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2D0h_(Make_N_tot_k_kpi<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2D0h_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2D0h(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0h())),
      N_tot_PartRec_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().runADS() == true) {
    N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "N_tot_Bs2Dst0Kpi_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2Dst0Kpi()));
    N_tot_Bs2D0Kpi_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "N_tot_Bs2D0Kpi_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2D0Kpi()));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_CP<_neutral, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma()));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "A_Bu2Dst0h_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .A_CP_Bu2Dst0h_D0gamma()));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_PartRec", uniqueId, _neutral, Bachelor::k, Daughters::pipi,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pipi>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    N_tot_PartRec_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::pipi>(
            uniqueId, "N_tot_PartRec_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_PartRec(),
            NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_PartRec(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0()));
  }
}
