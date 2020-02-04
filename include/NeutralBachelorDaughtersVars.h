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

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::kpi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::kk> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi,
                                        Daughters::pipi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::pi, Daughters::pik> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::kpi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::kk> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooConstVar> A_Bs2Dst0Kpi_;
  std::unique_ptr<RooConstVar> A_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::pipi> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooConstVar> A_Bs2Dst0Kpi_;
  std::unique_ptr<RooConstVar> A_Bs2D0Kpi_;
};

template <Neutral neutral>
struct NeutralBachelorDaughtersVarsImpl<neutral, Bachelor::k, Daughters::pik> {
  NeutralBachelorDaughtersVarsImpl(int uniqueId);
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_Blind_;
  std::unique_ptr<RooAbsReal> N_tot_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooConstVar> A_Bs2Dst0Kpi_;
  std::unique_ptr<RooConstVar> A_Bs2D0Kpi_;
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
  RooAbsReal &N_tot_Bu2Dst0h_D0gamma_Blind() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_Blind_;
  }
  RooAbsReal &N_tot_Bu2Dst0h_D0gamma() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_tot_Bu2Dst0h_D0pi0_Blind() {
    return *impl_.N_tot_Bu2Dst0h_D0pi0_Blind_;
  }
  RooAbsReal &N_tot_Bu2Dst0h_D0pi0() { return *impl_.N_tot_Bu2Dst0h_D0pi0_; }

  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0gamma_Blind_GetPointer() {
    return impl_.A_Bu2Dst0h_D0gamma_Blind_;
  }
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0gamma_GetPointer() {
    return impl_.A_Bu2Dst0h_D0gamma_;
  }
  std::shared_ptr<RooRealVar> A_Bu2Dst0h_D0pi0_Blind_GetPointer() {
    return impl_.A_Bu2Dst0h_D0pi0_Blind_;
  }
  std::shared_ptr<RooAbsReal> A_Bu2Dst0h_D0pi0_GetPointer() {
    return impl_.A_Bu2Dst0h_D0pi0_;
  }

  RooConstVar &A_Bs2Dst0Kpi() { return *impl_.A_Bs2Dst0Kpi_; }
  RooConstVar &A_Bs2D0Kpi() { return *impl_.A_Bs2D0Kpi_; }

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

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::kpi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          "",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0() *
              DaughtersVars<Daughters::kpi>::Get(uniqueId).daughtersSF(),
          0, 1000000)) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
            .c_str(),
        "",
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .N_tot_initVal_Bu2Dst0h_D0gamma() *
            DaughtersVars<Daughters::kpi>::Get(uniqueId).daughtersSF(),
        0, 1000000));
  }
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
            .c_str(),
        "", 0.001, -1, 1));
    A_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
            .c_str(),
        "", 0.001, -1, 1));
    A_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
                .c_str(),
            0.001, *A_Bu2Dst0h_D0gamma_Blind_));
    A_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
                .c_str(),
            0.001, *A_Bu2Dst0h_D0pi0_Blind_));
  } else {
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
            .c_str(),
        "", 0.001, -1, 1));
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
            .c_str(),
        "", 0.001, -1, 1));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_Blind_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_Blind_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0() *
              DaughtersVars<Daughters::pik>::Get(uniqueId).daughtersSF(),
          0, 1000000)),
      N_tot_Bu2Dst0h_D0pi0_(new RooUnblindUniform(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "Blind",
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0() *
              DaughtersVars<Daughters::pik>::Get(uniqueId).daughtersSF() * 0.05,
          *N_tot_Bu2Dst0h_D0pi0_Blind_)) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_Blind_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "",
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .N_tot_initVal_Bu2Dst0h_D0gamma() *
            DaughtersVars<Daughters::pik>::Get(uniqueId).daughtersSF(),
        0, 1000000));
    N_tot_Bu2Dst0h_D0gamma_ =
        std::unique_ptr<RooUnblindUniform>((new RooUnblindUniform(
            ("N_tot_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
                .c_str(),
            "Blind",
            ("N_tot_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
                .c_str(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                    .N_tot_initVal_Bu2Dst0h_D0gamma() *
                DaughtersVars<Daughters::pik>::Get(uniqueId).daughtersSF() *
                0.05,
            *N_tot_Bu2Dst0h_D0gamma_Blind_)));
  }
}


template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0() *
              DaughtersVars<Daughters::kk>::Get(uniqueId).daughtersSF(),
          0, 1000000)) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        "",
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .N_tot_initVal_Bu2Dst0h_D0gamma() *
            DaughtersVars<Daughters::kk>::Get(uniqueId).daughtersSF(),
        0, 1000000));
  }
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
            .A_CP_init(),
        -1, 1));
    A_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
            .A_CP_init(),
        -1, 1));
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
        "",
        NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
            .A_CP_init(),
        -1, 1));
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
            .A_CP_init(),
        -1, 1));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          "",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0() *
              DaughtersVars<Daughters::pipi>::Get(uniqueId).daughtersSF(),
          0, 1000000)) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
            .c_str(),
        "",
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .N_tot_initVal_Bu2Dst0h_D0gamma() *
            DaughtersVars<Daughters::pipi>::Get(uniqueId).daughtersSF(),
        0, 1000000));
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
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                           Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0pi0(),
              NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
                  .R_Dst0KDst0pi_Bu2Dst0h_D0pi0()))) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        "", "@0*@1",
        RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                Daughters::kpi>::Get(uniqueId)
                       .N_tot_Bu2Dst0h_D0gamma(),
                   NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
                       .R_Dst0KDst0pi_Bu2Dst0h_D0gamma())));
  }
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get(uniqueId)
            .A_CP_init(),
        -1, 1));
    A_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get(uniqueId)
            .A_CP_init(),
        -1, 1));
    A_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
                .c_str(),
            0.3, *A_Bu2Dst0h_D0gamma_Blind_));
    A_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
                .c_str(),
            0.3, *A_Bu2Dst0h_D0pi0_Blind_));
  } else {
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get(uniqueId)
            .A_CP_init(),
        -1, 1));
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get(uniqueId)
            .A_CP_init(),
        -1, 1));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_Blind_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_Blind_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0() *
              DaughtersVars<Daughters::pik>::Get(uniqueId).daughtersSF(),
          0, 1000000)),
      N_tot_Bu2Dst0h_D0pi0_(new RooUnblindUniform(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "Blind",
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0() *
              DaughtersVars<Daughters::pik>::Get(uniqueId).daughtersSF() * 0.05,
          *N_tot_Bu2Dst0h_D0pi0_Blind_)),
      A_Bs2Dst0Kpi_(new RooConstVar(
          ("A_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "", 0)),
      A_Bs2D0Kpi_(new RooConstVar(
          ("A_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "", 0)) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_Blind_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_tot_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        "",
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .N_tot_initVal_Bu2Dst0h_D0gamma() *
            0.01,
        0, 1000000));
    N_tot_Bu2Dst0h_D0gamma_ =
        std::unique_ptr<RooUnblindUniform>((new RooUnblindUniform(
            ("N_tot_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
                .c_str(),
            "Blind",
            ("N_tot_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
                .c_str(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                    .N_tot_initVal_Bu2Dst0h_D0gamma() *
                0.01 * 0.05,
            *N_tot_Bu2Dst0h_D0gamma_Blind_)));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                           Daughters::kk>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0pi0(),
              NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
                  .R_Dst0KDst0pi_Bu2Dst0h_D0pi0()))),
      A_Bs2Dst0Kpi_(new RooConstVar(
          ("A_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          "", 0)),
      A_Bs2D0Kpi_(new RooConstVar(
          ("A_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          "", 0)) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", "@0*@1",
        RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                Daughters::kk>::Get(uniqueId)
                       .N_tot_Bu2Dst0h_D0gamma(),
                   NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
                       .R_Dst0KDst0pi_Bu2Dst0h_D0gamma())));
  }
  if (Configuration::Get().blindFit() == true) {
    A_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", 0.01, -1, 1));
    A_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_Blind_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", 0.01, -1, 1));
    A_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
                .c_str(),
            0.01, *A_Bu2Dst0h_D0gamma_Blind_));
    A_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
                .c_str(),
            "Blind",
            ("A_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
                .c_str(),
            0.01, *A_Bu2Dst0h_D0pi0_Blind_));
  } else {
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", 0.01, -1, 1));
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(new RooRealVar(
        ("A_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        "", 0.01, -1, 1));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_Blind_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                           Daughters::pipi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0pi0(),
              NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
                  .R_Dst0KDst0pi_Bu2Dst0h_D0pi0()))),
      A_Bs2Dst0Kpi_(new RooConstVar(
          ("A_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          "", 0)),
      A_Bs2D0Kpi_(new RooConstVar(
          ("A_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          "", 0)) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_tot_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
            .c_str(),
        "", "@0*@1",
        RooArgList(
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma())));
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

