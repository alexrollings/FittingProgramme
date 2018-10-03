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
  std::unique_ptr<RooRealVar> N_partialRec_;
  std::unique_ptr<RooRealVar> N_misRec_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_overRec_;
  std::unique_ptr<RooRealVar> asym_partialRec_;
};

template <Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<Neutral::gamma, Bachelor::k,
                                        daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooFormulaVar> N_overRec_;
  std::unique_ptr<RooFormulaVar> N_partialRec_;
  std::unique_ptr<RooRealVar> N_misRec_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_overRec_;
  std::unique_ptr<RooRealVar> asym_partialRec_;
};

template <Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<Neutral::pi0, Bachelor::pi, daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooRealVar> N_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> N_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> N_overRec_;
  std::unique_ptr<RooRealVar> N_partialRec_;
  std::unique_ptr<RooRealVar> N_misRec_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_overRec_;
  std::unique_ptr<RooRealVar> asym_partialRec_;
};

template <Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<Neutral::pi0, Bachelor::k, daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooFormulaVar> N_overRec_;
  std::unique_ptr<RooFormulaVar> N_partialRec_;
  std::unique_ptr<RooRealVar> N_misRec_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooRealVar> asym_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooRealVar> asym_overRec_;
  std::unique_ptr<RooRealVar> asym_partialRec_;
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
  RooAbsReal &N_partialRec() { return *impl_.N_partialRec_; }
  RooAbsReal &N_misRec() { return *impl_.N_misRec_; }
  RooRealVar &asym_Bu2Dst0h_Dst02D0gamma() {
    return *impl_.asym_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &asym_Bu2Dst0h_Dst02D0pi0() {
    return *impl_.asym_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &asym_overRec() { return *impl_.asym_overRec_; }
  RooRealVar &asym_partialRec() { return *impl_.asym_partialRec_; }

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
      asym_partialRec_(new RooRealVar(
          ("asym_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable partialRec " +
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
          30000, 0, 100000)),
      N_Bu2Dst0h_Dst02D0pi0_(new RooRealVar(
          ("N_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0pi0-like events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          24000, 0, 100000)),
      N_overRec_(new RooRealVar(
          ("N_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of overRec-like events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          20000, 0, 100000)),
      N_partialRec_(new RooRealVar(
          ("N_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of partially reconstructed events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          9000, 0, 100000)),
      N_misRec_(new RooRealVar(
          ("N_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of misRec-like events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, daughters))
              .c_str(),
          5000, 0, 100000)) {}

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
      asym_partialRec_(new RooRealVar(
          ("asym_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable partialRec " +
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
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0h_Dst02D0gamma(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma()))),
      N_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("N_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0pi0-like events, for " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0h_Dst02D0pi0(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0()))),
      N_overRec_(new RooFormulaVar(
          ("N_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of overRec-like events, for " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_overRec(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_overRec()))),
      N_partialRec_(new RooFormulaVar(
          ("N_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of partially reconstructed events, for " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_partialRec(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .ratioDst0KDst0pi_partialRec()))),
      N_misRec_(new RooRealVar(
          ("N_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          ("Total number of misRec-like events " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k, daughters))
              .c_str(),
          1600, 0, 4000)) {}

template <Daughters daughters>
NeutralBachelorDaughtersVarsImpl<Neutral::pi0, Bachelor::pi, daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : asym_Bu2Dst0h_Dst02D0gamma_(nullptr),
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
      asym_partialRec_(new RooRealVar(
          ("asym_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("asymmetry variable partialRec " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      N_Bu2Dst0h_Dst02D0gamma_(nullptr),
      N_Bu2Dst0h_Dst02D0pi0_(new RooRealVar(
          ("N_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0pi0-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          6000, 0, 10000)),
      N_overRec_(new RooRealVar(
          ("N_overRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of overRec-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          2500, 0, 10000)),
      N_partialRec_(new RooRealVar(
          ("N_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of partially reconstructed events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          2500, 0, 10000)),
      N_misRec_(new RooRealVar(
          ("N_misRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          ("Total number of misRec-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, daughters))
              .c_str(),
          2500, 0, 10000)) {}


template <Daughters daughters>
NeutralBachelorDaughtersVarsImpl<Neutral::pi0, Bachelor::k, daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : asym_Bu2Dst0h_Dst02D0gamma_(nullptr),
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
      asym_partialRec_(new RooRealVar(
          ("asym_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("asymmetry variable partialRec " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          0.001, -1.0, 1.0)),
      N_Bu2Dst0h_Dst02D0gamma_(),
      N_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("N_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of Bu2Dst0h_Dst02D0pi0-like events, for " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_Bu2Dst0h_Dst02D0pi0(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0()))),
      N_overRec_(new RooFormulaVar(
          ("N_overRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of overRec-like events, for " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_overRec(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .ratioDst0KDst0pi_overRec()))),
      N_partialRec_(new RooFormulaVar(
          ("N_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of partially reconstructed events, for " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                  daughters>::Get(uniqueId)
                         .N_partialRec(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .ratioDst0KDst0pi_partialRec()))),
      N_misRec_(new RooRealVar(
          ("N_misRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          ("Total number of misRec-like events " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k, daughters))
              .c_str(),
          200, 0, 1000)) {}
