#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralVars.h"
#include "RooAbsReal.h"
#include "RooFormulaVar.h"
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

namespace {  // Anonymous namespace

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl;

template <Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<Neutral::gamma, Bachelor::pi,
                                        daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooRealVar> N_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> N_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> N_overRec_;
  std::unique_ptr<RooRealVar> N_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> N_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> N_misRec_;
  // std::unique_ptr<RooRealVar> N_Comb_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_overRec_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0hst_Dst02D0gamma_;
};

template <Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<Neutral::gamma, Bachelor::k,
                                        daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooFormulaVar> N_overRec_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooFormulaVar> N_misRec_;
  // std::unique_ptr<RooRealVar> N_Comb_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_overRec_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0hst_Dst02D0gamma_;
};

template <Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<Neutral::pi0, Bachelor::pi, daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooRealVar> N_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> N_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> N_overRec_;
  std::unique_ptr<RooRealVar> N_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> N_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> N_misRec_;
  std::unique_ptr<RooRealVar> N_Comb_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_overRec_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0hst_Dst02D0gamma_;
};

template <Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<Neutral::pi0, Bachelor::k, daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooFormulaVar> N_overRec_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooFormulaVar> N_misRec_;
  std::unique_ptr<RooRealVar> N_Comb_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_overRec_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0hst_Dst02D0gamma_;
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
  NeutralBachelorDaughtersVars(int uniqueId_) : impl_(uniqueId_) {}
  ~NeutralBachelorDaughtersVars() {}

  using This_t = NeutralBachelorDaughtersVars<neutral, bachelor, daughters>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId_) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId_);  // Check if uniqueId_ already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId_, std::make_shared<This_t>(uniqueId_))
               .first;
    }
    return *it->second;
  }

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  RooAbsReal &N_Bu2Dst0h_Dst02D0gamma() {
    return *impl_.N_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAbsReal &N_Bu2Dst0h_Dst02D0pi0() { return *impl_.N_Bu2Dst0h_Dst02D0pi0_; }
  RooAbsReal &N_overRec() { return *impl_.N_overRec_; }
  RooAbsReal &N_Bu2Dst0hst_Dst02D0pi0() {
    return *impl_.N_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooAbsReal &N_Bu2Dst0hst_Dst02D0gamma() {
    return *impl_.N_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooAbsReal &N_misRec() { return *impl_.N_misRec_; }
  RooAbsReal &N_Comb() { return *impl_.N_Comb_; }
  RooRealVar &asym_Bu2Dst0h_Dst02D0gamma() {
    return *impl_.asym_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &asym_Bu2Dst0h_Dst02D0pi0() {
    return *impl_.asym_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &asym_overRec() { return *impl_.asym_overRec_; }
  RooRealVar &asym_Bu2Dst0hst_Dst02D0pi0() {
    return *impl_.asym_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &asym_Bu2Dst0hst_Dst02D0gamma() {
    return *impl_.asym_Bu2Dst0hst_Dst02D0gamma_;
  }

 private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...

  // Indicate if only used by one daughters
  int uniqueId_;

  // N_Dpi is the total Bu2Dst0pi_D0neut events = signal + SCF + CF + missID
  NeutralBachelorDaughtersVarsImpl<neutral, bachelor, daughters> impl_;
};

// Now we just need to define the constructors separately so the values are
// different

template <Daughters daughters>
NeutralBachelorDaughtersVarsImpl<Neutral::gamma, Bachelor::pi, daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : asym_Bu2Dst0h_Dst02D0gamma_(new RooRealVar(
          ("asym_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0h_Dst02D0pi0_(new RooRealVar(
          ("asym_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_overRec_(new RooRealVar(
          ("asym_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable overRec " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0hst_Dst02D0pi0_(new RooRealVar(
          ("asym_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0hst_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0hst_Dst02D0gamma_(new RooRealVar(
          ("asym_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0hst_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      N_Bu2Dst0h_Dst02D0gamma_(new RooRealVar(
          ("N_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0gamma-like events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          7250, 0, 20000)),
      N_Bu2Dst0h_Dst02D0pi0_(new RooRealVar(
          ("N_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0pi0-like events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          // 6572)),
          5750, 0, 20000)),
      N_overRec_(new RooRealVar(
          ("N_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of overRec-like events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          4750, 0, 20000)),
      N_Bu2Dst0hst_Dst02D0pi0_(new RooRealVar(
          ("N_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0hst_Dst02D0pi0 reconstructed events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          1075, 0, 20000)),
      N_Bu2Dst0hst_Dst02D0gamma_(new RooRealVar(
          ("N_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0hst_Dst02D0gamma reconstructed events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          1200, 0, 20000)),
      N_misRec_(new RooRealVar(
          ("N_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of misRec-like events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          4500, 0, 50000)) {}

template <Daughters daughters>
NeutralBachelorDaughtersVarsImpl<Neutral::gamma, Bachelor::k, daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : asym_Bu2Dst0h_Dst02D0gamma_(new RooRealVar(
          ("asym_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0h_Dst02D0pi0_(new RooRealVar(
          ("asym_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_overRec_(new RooRealVar(
          ("asym_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable overRec " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0hst_Dst02D0pi0_(new RooRealVar(
          ("asym_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0hst_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0hst_Dst02D0gamma_(new RooRealVar(
          ("asym_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0hst_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      N_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("N_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0gamma-like events, for " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0h_Dst02D0gamma(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma(),
                     Configuration::Get().pidEff()))),
      N_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("N_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0pi0-like events, for " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0h_Dst02D0pi0(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0(),
                     Configuration::Get().pidEff()))),
      N_overRec_(new RooFormulaVar(
          ("N_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of overRec-like events, for " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_overRec(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_overRec(),
                     Configuration::Get().pidEff()))),
      N_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("N_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0hst_Dst02D0pi0 reconstructed events, for " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0hst_Dst02D0pi0(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0(),
                     Configuration::Get().pidEff()))),
      N_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("N_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0hst_Dst02D0gamma reconstructed events, "
           "for " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0hst_Dst02D0gamma(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma(),
                     Configuration::Get().pidEff()))),
      N_misRec_(new RooFormulaVar(
          ("N_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of misRec reconstructed events, "
           "for " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_misRec(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_misRec(),
                     Configuration::Get().pidEff()))) {}

template <Daughters daughters>
NeutralBachelorDaughtersVarsImpl<Neutral::pi0, Bachelor::pi, daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : asym_Bu2Dst0h_Dst02D0gamma_(new RooRealVar(
          ("asym_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0h_Dst02D0pi0_(new RooRealVar(
          ("asym_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_overRec_(new RooRealVar(
          ("asym_overRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable overRec " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0hst_Dst02D0pi0_(new RooRealVar(
          ("asym_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0hst_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0hst_Dst02D0gamma_(new RooRealVar(
          ("asym_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0hst_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      N_Bu2Dst0h_Dst02D0gamma_(new RooRealVar(
          ("N_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0gamma-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          300, 0, 20000)),
      N_Bu2Dst0h_Dst02D0pi0_(new RooRealVar(
          ("N_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0pi0-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          1140, 0, 20000)),
      N_overRec_(new RooRealVar(
          ("N_overRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of overRec-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          875, 0, 20000)),
      N_Bu2Dst0hst_Dst02D0pi0_(new RooRealVar(
          ("N_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0hst_Dst02D0pi0 reconstructed events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          1500, 0, 20000)),
      N_Bu2Dst0hst_Dst02D0gamma_(new RooRealVar(
          ("N_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0hst_Dst02D0gamma reconstructed events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          600, 0, 20000)),
      N_misRec_(new RooRealVar(
          ("N_misRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of misRec-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          1400, 0, 20000)),
      N_Comb_(new RooRealVar(
          ("N_Comb_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of comb-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          1000, 0, 50000)) {}

template <Daughters daughters>
NeutralBachelorDaughtersVarsImpl<Neutral::pi0, Bachelor::k, daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : asym_Bu2Dst0h_Dst02D0gamma_(new RooRealVar(
          ("asym_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0h_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0h_Dst02D0pi0_(new RooRealVar(
          ("asym_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0h_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_overRec_(new RooRealVar(
          ("asym_overRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable overRec " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0hst_Dst02D0pi0_(new RooRealVar(
          ("asym_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0hst_Dst02D0pi0 " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      asym_Bu2Dst0hst_Dst02D0gamma_(new RooRealVar(
          ("asym_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable Bu2Dst0hst_Dst02D0gamma " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      N_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("N_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0gamma-like events, for " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0h_Dst02D0gamma(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma(),
                     Configuration::Get().pidEff()))),
      N_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("N_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0pi0-like events, for " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0h_Dst02D0pi0(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0(),
                     Configuration::Get().pidEff()))),
      N_overRec_(new RooFormulaVar(
          ("N_overRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of overRec-like events, for " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_overRec(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .ratioDst0KDst0pi_overRec(),
                     Configuration::Get().pidEff()))),
      N_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("N_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0hst_Dst02D0pi0 reconstructed events, for " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0hst_Dst02D0pi0(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0(),
                     Configuration::Get().pidEff()))),
      N_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("N_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0hst_Dst02D0gamma reconstructed events, "
           "for " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0hst_Dst02D0gamma(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma(),
                     Configuration::Get().pidEff()))),
      N_misRec_(new RooFormulaVar(
          ("N_misRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of misRec reconstructed events, "
           "for " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          "@0*@1*@2",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_misRec(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .ratioDst0KDst0pi_misRec(),
                     Configuration::Get().pidEff()))),
      N_Comb_(new RooRealVar(
          ("N_Comb_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of comb-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          100, 0, 5000)) {}
