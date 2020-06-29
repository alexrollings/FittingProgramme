#pragma once
#include "BachelorDaughtersVars.h"
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorChargeVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralDaughtersVars.h"
#include "NeutralVars.h"
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
RooFormulaVar *MakeYieldKFAV(int uniqueId, const char *name,
                             RooAbsReal &yieldPi, RooAbsReal &ratio,
                             RooAbsReal &mcEffPi, RooAbsReal &mcEffK) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, Bachelor::k, daughters)).c_str(),
      "", "@0*@1*(@2/@3)", RooArgSet(yieldPi, ratio, mcEffPi, mcEffK));
}

// DON'T need to multiple CP K yields by MC effs as ratio defined in terms of
// R_CP and FAV R(D*K/D*π)
template <Neutral neutral, Daughters daughters>
RooFormulaVar *MakeYieldKCP(int uniqueId, const char *name, RooAbsReal &yieldPi,
                            RooAbsReal &ratio) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, Bachelor::k, daughters)).c_str(),
      "", "@0*@1", RooArgSet(yieldPi, ratio));
}

namespace {  // Anonymous namespace

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl;

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::kpi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::kk> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
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
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::pik> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::kpi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::pik> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::kk> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooAbsReal> N_tot_MisRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2D0h_;
  std::shared_ptr<RooAbsReal> N_tot_PartRec_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> N_tot_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::pipi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> A_MisRec_;
  std::shared_ptr<RooRealVar> A_Bu2D0h_;
  std::shared_ptr<RooRealVar> A_PartRec_;
  std::shared_ptr<RooAbsReal> A_Bs2Dst0Kpi_;
  std::shared_ptr<RooAbsReal> A_Bs2D0Kpi_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_FAVasSUP_;
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
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_GetPointer() {
    return impl_.A_Bu2Dst0h_D0gamma_Blind_;
  }
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_GetPointer() {
    return impl_.A_Bu2Dst0h_D0pi0_Blind_;
  }
  RooAbsReal &A_Bu2Dst0h_D0gamma() { return *impl_.A_Bu2Dst0h_D0gamma_; }
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_GetPointer() {
    return impl_.A_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &A_Bu2Dst0h_D0pi0() { return *impl_.A_Bu2Dst0h_D0pi0_; }
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_GetPointer() {
    return impl_.A_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &A_MisRec() { return *impl_.A_MisRec_; }
  std::shared_ptr<RooRealVar> A_MisRec_GetPointer() { return impl_.A_MisRec_; }
  RooRealVar &A_Bu2D0h() { return *impl_.A_Bu2D0h_; }
  std::shared_ptr<RooRealVar> A_Bu2D0h_GetPointer() { return impl_.A_Bu2D0h_; }
  RooRealVar &A_PartRec() { return *impl_.A_PartRec_; }
  std::shared_ptr<RooRealVar> A_PartRec_GetPointer() {
    return impl_.A_PartRec_;
  }
  RooAbsReal &A_Bs2Dst0Kpi() { return *impl_.A_Bs2Dst0Kpi_; }
  RooAbsReal &A_Bs2D0Kpi() { return *impl_.A_Bs2D0Kpi_; }

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

  RooFormulaVar &R_ADS_Bu2Dst0h_D0gamma() {
    return *impl_.R_ADS_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &R_ADS_Bu2Dst0h_D0pi0() { return *impl_.R_ADS_Bu2Dst0h_D0pi0_; }

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
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "A_Prod", uniqueId, _neutral, Bachelor::pi, Daughters::kpi, 0.001,
          -1, 1)),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0pi0() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(new RooRealVar(
          ("A_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_MisRec_(new RooRealVar(
          ("N_tot_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_Bu2D0h_(new RooRealVar(
          ("A_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_Bu2D0h_(new RooRealVar(
          ("N_tot_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_PartRec_(new RooRealVar(
          ("A_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_PartRec_(new RooRealVar(
          ("N_tot_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0gamma() *
            BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000000, 1000000));
    // Set A_Prod to be the same for the partial π0/gamma modes - doesn't make
    // sense to have 2
    A_Bu2Dst0h_D0gamma_ = A_Bu2Dst0h_D0pi0_;
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(new RooFormulaVar(
          ("N_tot_Bu2Dst0h_D0pi0_FAVasSUP_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                  Daughters::kpi>::Get(uniqueId)
                         .N_tot_Bu2Dst0h_D0pi0(),
                     Configuration::Get().crossFeedRate()))),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(new RooRealVar(
          ("A_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_MisRec_(new RooRealVar(
          ("N_tot_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_Bu2D0h_(new RooRealVar(
          ("A_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_Bu2D0h_(new RooRealVar(
          ("N_tot_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_PartRec_(new RooRealVar(
          ("A_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_PartRec_(new RooRealVar(
          ("N_tot_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().splitByCharge() == true) {
    R_ADS_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
        ("R_ADS_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "(@0+@1)/2",
        RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                             Charge::minus>::Get(uniqueId)
                       .R_piK_Bu2Dst0h_D0pi0(),
                   NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                             Charge::plus>::Get(uniqueId)
                       .R_piK_Bu2Dst0h_D0pi0()))));
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "(@0-@1)/(@0+@1)",
        RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                             Charge::minus>::Get(uniqueId)
                       .R_piK_Bu2Dst0h_D0pi0(),
                   NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                             Charge::plus>::Get(uniqueId)
                       .R_piK_Bu2Dst0h_D0pi0()))));
    if (_neutral == Neutral::gamma) {
      R_ADS_Bu2Dst0h_D0gamma_ =
          std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
              ("R_ADS_Bu2Dst0h_D0gamma_" +
               ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
                  .c_str(),
              "(@0+@1)/2",
              RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                                   Charge::minus>::Get(uniqueId)
                             .R_piK_Bu2Dst0h_D0gamma(),
                         NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                                   Charge::plus>::Get(uniqueId)
                             .R_piK_Bu2Dst0h_D0gamma()))));
      A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
          ("A_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          "(@0-@1)/(@0+@1)",
          RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                               Charge::minus>::Get(uniqueId)
                         .R_piK_Bu2Dst0h_D0gamma(),
                     NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                               Charge::plus>::Get(uniqueId)
                         .R_piK_Bu2Dst0h_D0gamma()))));
    }
  } else {
    R_ADS_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
        ("R_ADS_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "@0",
        RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                             Charge::total>::Get(uniqueId)
                       .R_piK_Bu2Dst0h_D0pi0()))));
    if (_neutral == Neutral::gamma) {
      R_ADS_Bu2Dst0h_D0gamma_ =
          std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
              ("R_ADS_Bu2Dst0h_D0gamma_" +
               ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
                  .c_str(),
              "@0",
              RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::pi,
                                                   Charge::total>::Get(uniqueId)
                             .R_piK_Bu2Dst0h_D0gamma()))));
    }
  }
  N_tot_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
      ("N_tot_Bu2Dst0h_D0pi0_" +
       ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
          .c_str(),
      "@0*@1",
      RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                              Daughters::kpi>::Get(uniqueId)
                     .N_tot_Bu2Dst0h_D0pi0(),
                 *R_ADS_Bu2Dst0h_D0pi0_))));
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "@0*@1",
        RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                Daughters::kpi>::Get(uniqueId)
                       .N_tot_Bu2Dst0h_D0gamma(),
                   *R_ADS_Bu2Dst0h_D0gamma_))));
    N_tot_Bu2Dst0h_D0gamma_FAVasSUP_ =
        std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
            ("N_tot_Bu2Dst0h_D0gamma_FAVasSUP_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
                .c_str(),
            "@0*@1",
            RooArgList(
                NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                             Daughters::kpi>::Get(uniqueId)
                    .N_tot_Bu2Dst0h_D0gamma(),
                Configuration::Get().crossFeedRate()))));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0pi0() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(new RooRealVar(
          ("A_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_MisRec_(new RooRealVar(
          ("N_tot_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_Bu2D0h_(new RooRealVar(
          ("A_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_Bu2D0h_(new RooRealVar(
          ("N_tot_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_PartRec_(new RooRealVar(
          ("A_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_PartRec_(new RooRealVar(
          ("N_tot_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0gamma() *
            BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000000, 1000000));
  }
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        "", Configuration::Get().ReturnACPInit(Neutral::gamma, Bachelor::pi),
        -1, 1));
    A_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        "", Configuration::Get().ReturnACPInit(Neutral::pi0, Bachelor::pi), -1,
        1));
    A_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
                .c_str(),
            0.03, *A_Bu2Dst0h_D0gamma_Blind_));
    A_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
                .c_str(),
            0.03, *A_Bu2Dst0h_D0pi0_Blind_));
  } else {
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        "", Configuration::Get().ReturnACPInit(Neutral::gamma, Bachelor::pi),
        -1, 1));
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        "", Configuration::Get().ReturnACPInit(Neutral::pi0, Bachelor::pi), -1,
        1));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0pi0() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                             Daughters::kk>::Get(uniqueId)
                    .A_MisRec_GetPointer()),
      N_tot_MisRec_(new RooRealVar(
          ("N_tot_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_Bu2D0h_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                             Daughters::kk>::Get(uniqueId)
                    .A_Bu2D0h_GetPointer()),
      N_tot_Bu2D0h_(new RooRealVar(
          ("N_tot_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_PartRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                              Daughters::kk>::Get(uniqueId)
                     .A_PartRec_GetPointer()),
      N_tot_PartRec_(new RooRealVar(
          ("N_tot_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          "",
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      A_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0gamma() *
            BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000000, 1000000));
  }
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ =
        NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                     Daughters::kk>::Get(uniqueId)
            .A_Bu2Dst0h_D0gamma_Blind_GetPointer();
    A_Bu2Dst0h_D0pi0_Blind_ =
        NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                     Daughters::kk>::Get(uniqueId)
            .A_Bu2Dst0h_D0pi0_Blind_GetPointer();
  }
  A_Bu2Dst0h_D0gamma_ =
      NeutralBachelorDaughtersVars<_neutral, Bachelor::pi, Daughters::kk>::Get(
          uniqueId)
          .A_Bu2Dst0h_D0gamma_GetPointer();
  A_Bu2Dst0h_D0pi0_ =
      NeutralBachelorDaughtersVars<_neutral, Bachelor::pi, Daughters::kk>::Get(
          uniqueId)
          .A_Bu2Dst0h_D0pi0_GetPointer();
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::kpi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("A_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          "", 0.01, -1, 1)),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(MakeYieldKFAV<_neutral, Daughters::kpi>(
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
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(new RooRealVar(
          ("A_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_MisRec_(MakeYieldKFAV<_neutral, Daughters::kpi>(
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
      A_Bu2D0h_(new RooRealVar(
          ("A_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_Bu2D0h_(MakeYieldKFAV<_neutral, Daughters::kpi>(
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
      A_PartRec_(nullptr),
      N_tot_PartRec_(nullptr),
      A_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(MakeYieldKFAV<_neutral, Daughters::kpi>(
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
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        "", 0.01, -1, 1));
    // FOR NOW fix asym to 0 as such small yield: change when improving
    // stability (otherwise add as systematic)
    A_PartRec_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        "", 0));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::kpi>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    A_PartRec_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        "", 0.01, -5, 5));
    N_tot_PartRec_ =
        std::shared_ptr<RooFormulaVar>(MakeYieldKFAV<_neutral, Daughters::kpi>(
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
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(new RooFormulaVar(
          ("N_tot_Bu2Dst0h_D0pi0_FAVasSUP_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                  Daughters::kpi>::Get(uniqueId)
                         .N_tot_Bu2Dst0h_D0pi0(),
                     Configuration::Get().crossFeedRate()))),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(new RooRealVar(
          ("A_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_MisRec_(MakeYieldKFAV<_neutral, Daughters::pik>(
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
      A_Bu2D0h_(new RooRealVar(
          ("A_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_Bu2D0h_(MakeYieldKFAV<_neutral, Daughters::pik>(
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
      A_PartRec_(new RooRealVar(
          ("A_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_PartRec_(nullptr),
      A_Bs2Dst0Kpi_(new RooConstVar(
          ("A_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "", 0)),
      N_tot_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(new RooConstVar(
          ("A_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "", 0)),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().splitByCharge() == true) {
    R_ADS_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
        ("R_ADS_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "(@0+@1)/2",
        RooArgList(
            NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::plus>::Get(
                uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()))));
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "(@0-@1)/(@0+@1)",
        RooArgList(
            NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::plus>::Get(
                uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()))));
    if (_neutral == Neutral::gamma) {
      R_ADS_Bu2Dst0h_D0gamma_ =
          std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
              ("R_ADS_Bu2Dst0h_D0gamma_" +
               ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
                  .c_str(),
              "(@0+@1)/2",
              RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                                   Charge::minus>::Get(uniqueId)
                             .R_piK_Bu2Dst0h_D0gamma(),
                         NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                                   Charge::plus>::Get(uniqueId)
                             .R_piK_Bu2Dst0h_D0gamma()))));
      A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
          ("A_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "(@0-@1)/(@0+@1)",
          RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                               Charge::minus>::Get(uniqueId)
                         .R_piK_Bu2Dst0h_D0gamma(),
                     NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                               Charge::plus>::Get(uniqueId)
                         .R_piK_Bu2Dst0h_D0gamma()))));
    }
  } else {
    R_ADS_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
        ("R_ADS_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "@0",
        RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                             Charge::total>::Get(uniqueId)
                       .R_piK_Bu2Dst0h_D0pi0()))));
    if (_neutral == Neutral::gamma) {
      R_ADS_Bu2Dst0h_D0gamma_ =
          std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
              ("R_ADS_Bu2Dst0h_D0gamma_" +
               ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
                  .c_str(),
              "@0",
              RooArgList(NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                                   Charge::total>::Get(uniqueId)
                             .R_piK_Bu2Dst0h_D0gamma()))));
    }
  }
  N_tot_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
      ("N_tot_Bu2Dst0h_D0pi0_" +
       ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
          .c_str(),
      "@0*@1",
      RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                              Daughters::kpi>::Get(uniqueId)
                     .N_tot_Bu2Dst0h_D0pi0(),
                 *R_ADS_Bu2Dst0h_D0pi0_))));
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "@0*@1",
        RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                Daughters::kpi>::Get(uniqueId)
                       .N_tot_Bu2Dst0h_D0gamma(),
                   *R_ADS_Bu2Dst0h_D0gamma_))));
    N_tot_Bu2Dst0h_D0gamma_FAVasSUP_ =
        std::shared_ptr<RooFormulaVar>((new RooFormulaVar(
            ("N_tot_Bu2Dst0h_D0gamma_FAVasSUP_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
                .c_str(),
            "@0*@1",
            RooArgList(NeutralBachelorDaughtersVars<
                           _neutral, Bachelor::k, Daughters::kpi>::Get(uniqueId)
                           .N_tot_Bu2Dst0h_D0gamma(),
                       Configuration::Get().crossFeedRate()))));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
    N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bs2Dst0Kpi_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0gamma() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000, 1000));
    N_tot_Bs2D0Kpi_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bs2D0Kpi_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0gamma() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000, 1000));
  } else {
    N_tot_PartRec_ =
        std::shared_ptr<RooFormulaVar>(MakeYieldKFAV<_neutral, Daughters::pik>(
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
    N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bs2Dst0Kpi_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0pi0() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000, 1000));
    N_tot_Bs2D0Kpi_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bs2D0Kpi_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2Dst0h_D0pi0() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
                .kBR()
                .getVal(),
        -1000, 1000));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(MakeYieldKCP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(new RooRealVar(
          ("A_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_MisRec_(MakeYieldKFAV<_neutral, Daughters::kk>(
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
      A_Bu2D0h_(new RooRealVar(
          ("A_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_Bu2D0h_(MakeYieldKFAV<_neutral, Daughters::kk>(
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
      A_PartRec_(new RooRealVar(
          ("A_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          "", 0.01, -5, 5)),
      N_tot_PartRec_(nullptr),
      A_Bs2Dst0Kpi_(new RooConstVar(
          ("A_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          "", 0)),
      // kk yield for Bs background = πk yield * BR (D->kk/D->kπ)
      N_tot_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(new RooConstVar(
          ("A_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          "", 0)),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().runADS() == true) {
    N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_tot_Bs2Dst0Kpi_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", "@0*(@1/@2)",
        RooArgSet(
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2Dst0Kpi(),
            BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                .kBR(),
            BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                .kBR())));
    N_tot_Bs2D0Kpi_ = std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_tot_Bs2D0Kpi_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", "@0*(@1/@2)",
        RooArgSet(
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2D0Kpi(),
            BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                .kBR(),
            BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                .kBR())));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(MakeYieldKCP<_neutral, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kk>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma()));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::kk>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    N_tot_PartRec_ =
        std::shared_ptr<RooFormulaVar>(MakeYieldKFAV<_neutral, Daughters::kk>(
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
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", Configuration::Get().ReturnACPInit(Neutral::gamma, Bachelor::k), -1,
        1));
    A_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", Configuration::Get().ReturnACPInit(Neutral::pi0, Bachelor::k), -1,
        1));
    A_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
                .c_str(),
            0.3, *A_Bu2Dst0h_D0gamma_Blind_));
    A_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
                .c_str(),
            0.3, *A_Bu2Dst0h_D0pi0_Blind_));
  } else {
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", Configuration::Get().ReturnACPInit(Neutral::gamma, Bachelor::k), -1,
        1));
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", Configuration::Get().ReturnACPInit(Neutral::pi0, Bachelor::k), -1,
        1));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(MakeYieldKCP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      A_MisRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                             Daughters::kk>::Get(uniqueId)
                    .A_MisRec_GetPointer()),
      N_tot_MisRec_(MakeYieldKFAV<_neutral, Daughters::pipi>(
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
      A_Bu2D0h_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                             Daughters::kk>::Get(uniqueId)
                    .A_Bu2D0h_GetPointer()),
      N_tot_Bu2D0h_(MakeYieldKFAV<_neutral, Daughters::pipi>(
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
      A_PartRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                              Daughters::kk>::Get(uniqueId)
                     .A_PartRec_GetPointer()),
      N_tot_PartRec_(nullptr),
      A_Bs2Dst0Kpi_(new RooConstVar(
          ("A_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          "", 0)),
      // ππ yield for Bs background = πk yield * BR (D->ππ/D->kπ)
      N_tot_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(new RooConstVar(
          ("A_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          "", 0)),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().runADS() == true) {
    N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_tot_Bs2Dst0Kpi_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
            .c_str(),
        "", "@0*(@1/@2)",
        RooArgSet(
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2Dst0Kpi(),
            BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(uniqueId)
                .kBR(),
            BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                .kBR())));
    N_tot_Bs2D0Kpi_ = std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_tot_Bs2D0Kpi_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
            .c_str(),
        "", "@0*(@1/@2)",
        RooArgSet(
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2D0Kpi(),
            BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(uniqueId)
                .kBR(),
            BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                .kBR())));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(MakeYieldKCP<_neutral, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma()));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
            .c_str(),
        "",
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pipi>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    N_tot_PartRec_ =
        std::shared_ptr<RooFormulaVar>(MakeYieldKFAV<_neutral, Daughters::pipi>(
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
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ =
        NeutralBachelorDaughtersVars<_neutral, Bachelor::k, Daughters::kk>::Get(
            uniqueId)
            .A_Bu2Dst0h_D0gamma_Blind_GetPointer();
    A_Bu2Dst0h_D0pi0_Blind_ =
        NeutralBachelorDaughtersVars<_neutral, Bachelor::k, Daughters::kk>::Get(
            uniqueId)
            .A_Bu2Dst0h_D0pi0_Blind_GetPointer();
  }
  A_Bu2Dst0h_D0gamma_ =
      NeutralBachelorDaughtersVars<_neutral, Bachelor::k, Daughters::kk>::Get(
          uniqueId)
          .A_Bu2Dst0h_D0gamma_GetPointer();
  A_Bu2Dst0h_D0pi0_ =
      NeutralBachelorDaughtersVars<_neutral, Bachelor::k, Daughters::kk>::Get(
          uniqueId)
          .A_Bu2Dst0h_D0pi0_GetPointer();
}
