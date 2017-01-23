#pragma once
#include "Configuration.h"
#include "DaughtersVars.h"
#include "NeutralDaughtersVars.h"
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

namespace { // Anonymous namespace

template <Neutral neutral, Bachelor bachelor, Daughters daughters, RunType runType>
struct SpecialisedVarsImpl;

template <Neutral neutral, Daughters daughters, RunType runType>
struct SpecialisedVarsImpl<neutral, Bachelor::pi, daughters, runType> {
  SpecialisedVarsImpl();
  std::unique_ptr<RooRealVar> N_Dh_;
  std::unique_ptr<RooAbsReal> N_Dh_Bu2D0H_;
  std::unique_ptr<RooAbsReal> N_Dh_Bu2D0Hst_;
  std::unique_ptr<RooAbsReal> N_Dh_Bd2DstH_;
  std::unique_ptr<RooAbsReal> N_Dh_Bu2Dst0Hst_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Dh_Bu2Dst0Hst_D0gamma_;
};

template <Neutral neutral, Daughters daughters, RunType runType>
struct SpecialisedVarsImpl<neutral, Bachelor::k, daughters, runType> {
  SpecialisedVarsImpl();
  std::unique_ptr<RooFormulaVar> N_Dh_;
  std::unique_ptr<RooFormulaVar> N_Dh_Bu2D0H_;
  std::unique_ptr<RooFormulaVar> N_Dh_Bu2D0Hst_;
  std::unique_ptr<RooFormulaVar> N_Dh_Bd2DstH_;
  std::unique_ptr<RooFormulaVar> N_Dh_Bu2Dst0Hst_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Dh_Bu2Dst0Hst_D0gamma_;
};
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters, RunType runType>
class SpecialisedVars {

  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   DaughtersVars<Daughters::gamma>::Get()
  //   DaughtersVars<Daughters::pi0>::Get()
  // All happens automatically :-)

public:
  static SpecialisedVars<neutral, bachelor, daughters, runType> &Get() {
    static SpecialisedVars<neutral, bachelor, daughters, runType> singleton;
    return singleton;
  }

  // If RooShit wasn't so shit we would pass a const reference
  RooAbsReal &N_Dh() { return *impl_.N_Dh_; }
  RooAbsReal &N_Dh_Bu2D0H() { return *impl_.N_Dh_Bu2D0H_; }
  RooAbsReal &N_Dh_Bu2D0Hst() { return *impl_.N_Dh_Bu2D0Hst_; }
  RooAbsReal &N_Dh_Bd2DstH() { return *impl_.N_Dh_Bd2DstH_; }
  RooAbsReal &N_Dh_Bu2Dst0Hst_D0pi0() { return *impl_.N_Dh_Bu2Dst0Hst_D0pi0_; }
  RooAbsReal &N_Dh_Bu2Dst0Hst_D0gamma() {
    return *impl_.N_Dh_Bu2Dst0Hst_D0gamma_;
  }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...
  SpecialisedVars() {}
  ~SpecialisedVars() {}

  // Indicate if only used by one daughters

  // N_Dpi is the total Bu2Dst0pi_D0neut events = signal + SCF + CF + missID
  SpecialisedVarsImpl<neutral, bachelor, daughters, runType> impl_;
};

// Now we just need to define the constructors separately so the values are
// different

template <Neutral neutral, Daughters daughters, RunType runType>
SpecialisedVarsImpl<neutral, Bachelor::pi, daughters, runType>::SpecialisedVarsImpl()
    : N_Dh_(new RooRealVar(("N_Dpi_" + ComposeName(neutral, daughters)).c_str(),
                           ("Total number of Bu2Dst0pi-like events " +
                            ComposeName(neutral, daughters))
                               .c_str(),
                           (NeutralVars<neutral>::Get().signalExpected() +
                            NeutralVars<neutral>::Get().nonTmSignalExpected() +
                            NeutralVars<neutral>::Get().crossFeedExpected()) *
                               DaughtersVars<daughters>::Get().daughtersSF(),
                           0,
                           NeutralVars<neutral>::Get().maxYield() *
                               DaughtersVars<daughters>::Get().daughtersSF())),
      N_Dh_Bu2D0H_(nullptr), N_Dh_Bu2D0Hst_(nullptr), N_Dh_Bd2DstH_(nullptr),
      N_Dh_Bu2Dst0Hst_D0pi0_(nullptr), N_Dh_Bu2Dst0Hst_D0gamma_(nullptr) {

  if (neutral == Neutral::pi0) {
    N_Dh_Bu2Dst0Hst_D0pi0_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Dpi_Bu2Dst0Hst_D0pi0_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bu2Dst0rho D0pi0 -like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        NeutralVars<neutral>::Get().bu2Dst0Hst_D0pi0Expected() *
            DaughtersVars<daughters>::Get().daughtersSF(),
        0, NeutralVars<neutral>::Get().maxYield() *
               DaughtersVars<daughters>::Get().daughtersSF()));
    N_Dh_Bu2Dst0Hst_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Dpi_Bu2Dst0Hst_D0gamma_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bu2Dst0rho D0gamma -like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        "@0*@1/(1-@1)",
        RooArgList(
            *N_Dh_Bu2Dst0Hst_D0pi0_,
            NeutralVars<SwapNeutral<neutral>()>::Get().crossFeedRate())));
  } else {
    N_Dh_Bu2Dst0Hst_D0gamma_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Dpi_Bu2Dst0Hst_D0gamma_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bu2Dst0Kst D0gamma -like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        NeutralVars<neutral>::Get().bu2Dst0Hst_D0gammaExpected() *
            DaughtersVars<daughters>::Get().daughtersSF(),
        0, NeutralVars<neutral>::Get().maxYield() *
               DaughtersVars<daughters>::Get().daughtersSF()));
    N_Dh_Bu2Dst0Hst_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Dpi_Bu2Dst0Hst_D0pi0_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bu2Dst0Kst D0pi0 -like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        "@0*@1/(1-@1)",
        RooArgList(
            *N_Dh_Bu2Dst0Hst_D0gamma_,
            NeutralVars<SwapNeutral<neutral>()>::Get().crossFeedRate())));
  }

  if (daughters == Daughters::kpi && runType == RunType::normal) {
    N_Dh_Bu2D0H_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Dpi_Bu2D0H_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bu2D0pi-like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        "@0*@1",
        RooArgList(*N_Dh_, NeutralVars<neutral>::Get().relativeBu2D0HYield())));
    N_Dh_Bu2D0Hst_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Dpi_Bu2D0Hst_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bu2D0rho-like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        "@0*@1",
        RooArgList(*N_Dh_,
                   NeutralVars<neutral>::Get().relativeBu2D0HstYield())));
    N_Dh_Bd2DstH_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Dpi_Bd2DstH_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bd2Dstpi-like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        "@0*@1",
        RooArgList(*N_Dh_,
                   NeutralVars<neutral>::Get().relativeBd2DstHYield())));
    // N_Dh_Bu2Dst0Hst_D0pi0_ = std::unique_ptr<RooFormulaVar>(new
    // RooFormulaVar(
    //     ("N_Dpi_Bu2Dst0Hst_D0pi0_" + ComposeName(neutral,
    //     daughters)).c_str(),
    //     ("Total number of Bu2Dst0rho D0pi0-like events " +
    //      ComposeName(neutral, daughters))
    //         .c_str(),
    //     "@0*@1",
    //     RooArgList(*N_Dh_,
    //                NeutralVars<neutral>::Get().relativeBu2Dst0Hst_D0pi0Yield())));
    // N_Dh_Bu2Dst0Hst_D0gamma_ = std::unique_ptr<RooFormulaVar>(new
    // RooFormulaVar(
    //     ("N_Dpi_Bu2Dst0Hst_D0gamma_" + ComposeName(neutral,
    //     daughters)).c_str(),
    //     ("Total number of Bu2Dst0rho D0gamma-like events " +
    //      ComposeName(neutral, daughters))
    //         .c_str(),
    //     "@0*@1",
    //     RooArgList(*N_Dh_,
    //                NeutralVars<neutral>::Get().relativeBu2Dst0Hst_D0gammaYield())));
  } else {
    N_Dh_Bu2D0H_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Dpi_Bu2D0H_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bu2D0pi-like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        NeutralVars<neutral>::Get().bu2D0HExpected() *
            DaughtersVars<daughters>::Get().daughtersSF(),
        0, NeutralVars<neutral>::Get().maxYield() *
               DaughtersVars<daughters>::Get().daughtersSF()));
    N_Dh_Bu2D0Hst_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Dpi_Bu2D0Hst_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bu2D0pi-like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        NeutralVars<neutral>::Get().bu2D0HstExpected() *
            DaughtersVars<daughters>::Get().daughtersSF(),
        0, NeutralVars<neutral>::Get().maxYield() *
               DaughtersVars<daughters>::Get().daughtersSF()));
    N_Dh_Bd2DstH_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Dpi_Bd2DstH_" + ComposeName(neutral, daughters)).c_str(),
        ("Total number of Bu2D0pi-like events " +
         ComposeName(neutral, daughters))
            .c_str(),
        NeutralVars<neutral>::Get().bd2DstHExpected() *
            DaughtersVars<daughters>::Get().daughtersSF(),
        0, NeutralVars<neutral>::Get().maxYield() *
               DaughtersVars<daughters>::Get().daughtersSF()));
  }
}

template <Neutral neutral, Daughters daughters, RunType runType>
SpecialisedVarsImpl<neutral, Bachelor::k, daughters, runType>::SpecialisedVarsImpl()
    : N_Dh_(new RooFormulaVar(
          ("N_Dk_" + ComposeName(neutral, daughters)).c_str(),
          ("Total number of Bu2Dst0K-like events, for " +
           ComposeName(neutral, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(
              SpecialisedVars<neutral, Bachelor::pi, daughters, runType>::Get().N_Dh(),
              NeutralDaughtersVars<neutral, daughters>::Get().R_Dk_vs_Dpi()))),
      N_Dh_Bu2D0H_(new RooFormulaVar(
          ("N_Dk_Bu2D0H_" + ComposeName(neutral, daughters)).c_str(),
          ("Total number of Bu2D0K-like events, for " +
           ComposeName(neutral, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(SpecialisedVars<neutral, Bachelor::pi, daughters, runType>::Get()
                         .N_Dh_Bu2D0H(),
                     DaughtersVars<daughters>::Get().R_Dk_vs_Dpi_Bu2D0H()))),
      N_Dh_Bu2D0Hst_(new RooFormulaVar(
          ("N_Dk_Bu2D0Hst_" + ComposeName(neutral, daughters)).c_str(),
          ("Total number of Bu2D0Kst-like events, for " +
           ComposeName(neutral, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(SpecialisedVars<neutral, Bachelor::pi, daughters, runType>::Get()
                         .N_Dh_Bu2D0Hst(),
                     DaughtersVars<daughters>::Get().R_Dk_vs_Dpi_Bu2D0Hst()))),
      N_Dh_Bd2DstH_(new RooFormulaVar(
          ("N_Dk_Bd2DstH_" + ComposeName(neutral, daughters)).c_str(),
          ("Total number of Bd2DstK-like events, for " +
           ComposeName(neutral, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(SpecialisedVars<neutral, Bachelor::pi, daughters, runType>::Get()
                         .N_Dh_Bd2DstH(),
                     Configuration::Get().R_Dk_vs_Dpi_Bd2DstH()))),
      N_Dh_Bu2Dst0Hst_D0pi0_(new RooFormulaVar(
          ("N_Dk_Bu2Dst0Hst_D0pi0_" + ComposeName(neutral, daughters)).c_str(),
          ("Total number of Bu2Dst0Kst-like events, for " +
           ComposeName(neutral, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(SpecialisedVars<neutral, Bachelor::pi, daughters, runType>::Get()
                         .N_Dh_Bu2Dst0Hst_D0pi0(),
                     NeutralDaughtersVars<neutral, daughters>::Get()
                         .R_Dk_vs_Dpi_Bu2Dst0Hst_D0pi0()))),
      N_Dh_Bu2Dst0Hst_D0gamma_(new RooFormulaVar(
          ("N_Dk_Bu2Dst0Hst_D0gamma_" + ComposeName(neutral, daughters))
              .c_str(),
          ("Total number of Bu2Dst0Kst-like events, for " +
           ComposeName(neutral, daughters))
              .c_str(),
          "@0*@1",
          RooArgList(SpecialisedVars<neutral, Bachelor::pi, daughters, runType>::Get()
                         .N_Dh_Bu2Dst0Hst_D0gamma(),
                     NeutralDaughtersVars<neutral, daughters>::Get()
                         .R_Dk_vs_Dpi_Bu2Dst0Hst_D0gamma()))) {}

