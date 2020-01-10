#pragma once
#include "Configuration.h"
#include "DaughtersVars.h"
#include "GlobalVars.h"
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

namespace {  // Anonymous namespace

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl;

template <Neutral neutral, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_;
};

template <Neutral neutral, Daughters daughters>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, daughters> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::unique_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_tot_Bu2Dst0h_D0pi0_;
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
  // Don't want to be able to access the blinded results
  RooAbsReal &A_Bu2Dst0h_D0gamma() { return *impl_.A_Bu2Dst0h_D0gamma_; }
  RooAbsReal &A_Bu2Dst0h_D0pi0() { return *impl_.A_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_tot_Bu2Dst0h_D0gamma() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_tot_Bu2Dst0h_D0pi0() { return *impl_.N_tot_Bu2Dst0h_D0pi0_; }

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

template <Neutral _neutral, Daughters _daughters>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, _daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
              .c_str(),
          "",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0() *
              DaughtersVars<_daughters>::Get(uniqueId).daughtersSF(),
          0, 1000000)) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
            .c_str(),
        "",
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .N_tot_initVal_Bu2Dst0h_D0gamma() *
            DaughtersVars<_daughters>::Get(uniqueId).daughtersSF(),
        0, 1000000));
  }
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
            .c_str(),
        "", 0.01, -1, 1));
    A_Bu2Dst0h_D0pi0_Blind_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
            .c_str(),
        "", 0.01, -1, 1));
    A_Bu2Dst0h_D0gamma_ =
        std::unique_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
                .c_str(),
            0.01, *A_Bu2Dst0h_D0gamma_Blind_));
    A_Bu2Dst0h_D0pi0_ =
        std::unique_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
                .c_str(),
            0.01, *A_Bu2Dst0h_D0pi0_Blind_));
  } else {
    A_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
            .c_str(),
        "", 0.01, -1, 1));
    A_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _daughters))
            .c_str(),
        "", 0.01, -1, 1));
  }
}

template <Neutral _neutral, Daughters _daughters>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, _daughters>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
              .c_str(),
          "", "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                  _daughters>::Get(uniqueId)
                         .N_tot_Bu2Dst0h_D0pi0(),
                     NeutralDaughtersVars<_neutral, _daughters>::Get(uniqueId)
                         .R_Dst0KDst0pi_Bu2Dst0h_D0pi0()))) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
            .c_str(),
        "", "@0*@1",
        RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                _daughters>::Get(uniqueId)
                       .N_tot_Bu2Dst0h_D0gamma(),
                   NeutralDaughtersVars<_neutral, _daughters>::Get(uniqueId)
                       .R_Dst0KDst0pi_Bu2Dst0h_D0gamma())));
  }
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
            .c_str(),
        "", 0.01, -1, 1));
    A_Bu2Dst0h_D0pi0_Blind_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
            .c_str(),
        "", 0.01, -1, 1));
    A_Bu2Dst0h_D0gamma_ =
        std::unique_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
                .c_str(),
            0.01, *A_Bu2Dst0h_D0gamma_Blind_));
    A_Bu2Dst0h_D0pi0_ =
        std::unique_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
                .c_str(),
            0.01, *A_Bu2Dst0h_D0pi0_Blind_));
  } else {
    A_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
            .c_str(),
        "", 0.01, -1, 1));
    A_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _daughters))
            .c_str(),
        "", 0.01, -1, 1));
  }
}
