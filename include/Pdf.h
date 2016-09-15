#pragma once
#include "Configuration.h"
#include "DaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralDaughtersVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooExponential.h"
#include "RooSimultaneous.h"
#include "SpecialisedVars.h"

class PdfBase {

public:
  void AddToSimultaneousPdf(RooSimultaneous &) const;

  Bachelor bachelor() const { return bachelor_; }
  Neutral neutral() const { return neutral_; }
  Daughters daughters() const { return daughters_; }

  RooAbsReal &signalYield() { return *signalYield_; }
  RooAbsReal &crossFeedYield() { return *crossFeedYield_; }
  RooAbsReal &bu2D0HYield() { return *bu2D0HYield_; }
  RooAbsReal &bd2DstHYield() { return *bd2DstHYield_; }
  RooAbsReal &nonTmSignalYield() { return *nonTmSignalYield_; }
  RooAbsReal &missIdYield() { return *missIdYield_; }
  RooAbsReal &bu2D0HstYield() { return *bu2D0HstYield_; }
  RooAbsReal &bu2Dst0Hst_D0pi0Yield() { return *bu2Dst0Hst_D0pi0Yield_; }
  RooAbsReal &bu2Dst0Hst_D0gammaYield() { return *bu2Dst0Hst_D0gammaYield_; }
  RooRealVar &combinatorialYield() { return combinatorialYield_; }
  RooRealVar &combinatorialConstant() { return combinatorialConstant_; }
  RooAbsPdf &combinatorial() { return *combinatorial_; }
  RooArgList &yields() { return yields_; }
  RooArgList &functions() { return functions_; }

  virtual RooAbsPdf &nonTmSignal() const = 0;
  virtual RooAbsPdf &signal() const = 0;
  virtual RooAbsPdf &crossFeed() const = 0;
  virtual RooAbsPdf &bu2Dst0Hst_D0pi0() const = 0;
  virtual RooAbsPdf &bu2Dst0Hst_D0gamma() const = 0;
  virtual RooAbsPdf &bu2D0H() const = 0;
  virtual RooAbsPdf &bu2D0Hst() const = 0;
  virtual RooAbsPdf &bd2DstH() const = 0;
  virtual RooAbsPdf &missId() const = 0;

protected:
  PdfBase(Neutral neutral, Bachelor bachelor, Daughters daughters);
  virtual ~PdfBase() {}

  Neutral neutral_;
  Bachelor bachelor_;
  Daughters daughters_;

  RooRealVar combinatorialConstant_;
  std::unique_ptr<RooAbsPdf> combinatorial_;

  std::unique_ptr<RooAbsReal> signalYield_;
  std::unique_ptr<RooAbsReal> crossFeedYield_;
  std::unique_ptr<RooAbsReal> bu2D0HYield_;
  std::unique_ptr<RooAbsReal> bd2DstHYield_;
  std::unique_ptr<RooAbsReal> nonTmSignalYield_;
  std::unique_ptr<RooAbsReal> missIdYield_;
  std::unique_ptr<RooAbsReal> bu2Dst0Hst_D0pi0Yield_;
  std::unique_ptr<RooAbsReal> bu2Dst0Hst_D0gammaYield_;
  std::unique_ptr<RooAbsReal> bu2D0HstYield_;
  RooRealVar combinatorialYield_;
  RooArgList yields_;
  RooArgList functions_;
  std::unique_ptr<RooAddPdf> addPdf_;
};

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters>
class Pdf : public PdfBase {

public:
  static Pdf<_neutral, _bachelor, _daughters> &Get() {
    static Pdf<_neutral, _bachelor, _daughters> singleton;
    return singleton;
  }

  void AssignMissIdYields();
  void CreateRooAddPdf();

  virtual RooAbsPdf &nonTmSignal() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().nonTmSignal();
  }

  virtual RooAbsPdf &signal() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().signal();
  }

  virtual RooAbsPdf &crossFeed() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().crossFeed();
  }

  virtual RooAbsPdf &bu2Dst0Hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0pi0();
  }

  virtual RooAbsPdf &bu2Dst0Hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0gamma();
  }

  virtual RooAbsPdf &bu2D0H() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().bu2D0H();
  }

  virtual RooAbsPdf &bu2D0Hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().bu2D0Hst();
  }

  virtual RooAbsPdf &bd2DstH() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().bd2DstH();
  }

  virtual RooAbsPdf &missId() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().missId();
  }

private:
  Pdf();
  virtual ~Pdf() {}

  // Declaring a function inside a class of const will not change any of the
  // variables inside of the object
};

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters>
Pdf<_neutral, _bachelor, _daughters>::Pdf()
    : PdfBase(_neutral, _bachelor, _daughters) {
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("signalYield_" +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("Signal Yield " +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      "@0*(1-@1-@2)*@3",
      RooArgList(
          SpecialisedVars<_neutral, _bachelor, _daughters>::Get().N_Dh(),
          NeutralDaughtersVars<_neutral, _daughters>::Get().selfCrossFeedRate(),
          NeutralDaughtersVars<_neutral, _daughters>::Get().crossFeedRate(),
          NeutralBachelorVars<_neutral, _bachelor>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("nonTmSignalYield_" +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("non TM Signal Yield " +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      "@0*@1*@2",
      RooArgList(
          SpecialisedVars<_neutral, _bachelor, _daughters>::Get().N_Dh(),
          NeutralDaughtersVars<_neutral, _daughters>::Get().selfCrossFeedRate(),
          NeutralBachelorVars<_neutral, _bachelor>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("crossFeedYield_" +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("Cross Feed Yield " +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      "@0*@1*@2",
      RooArgList(
          SpecialisedVars<SwapNeutral<_neutral>(), _bachelor, _daughters>::Get()
              .N_Dh(),
          NeutralDaughtersVars<SwapNeutral<_neutral>(), _daughters>::Get()
              .crossFeedRate(),
          NeutralBachelorVars<_neutral, _bachelor>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      ("bu2Dst0Hst_D0pi0Yield_" +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("bu2Dst0Hst_D0pi0 Yield " +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      NeutralVars<_neutral>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
          DaughtersVars<_daughters>::Get().daughtersSF(),
      0, NeutralVars<_neutral>::Get().maxYield() *
             NeutralBachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
             DaughtersVars<_daughters>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      ("bu2Dst0Hst_D0gammaYield_" +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("bu2Dst0Hst_D0gamma Yield " +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      NeutralVars<_neutral>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
          DaughtersVars<_daughters>::Get().daughtersSF(),
      0, NeutralVars<_neutral>::Get().maxYield() *
             NeutralBachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
             DaughtersVars<_daughters>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("bu2D0HYield_" +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("bu2D0H Yield " +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      "@0*@1",
      RooArgList(
          SpecialisedVars<_neutral, _bachelor, _daughters>::Get().N_Dh_Bu2D0H(),
          NeutralBachelorVars<_neutral, _bachelor>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("bu2D0HstYield_" +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("bu2D0Hst Yield " +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      "@0*@1",
      RooArgList(
          SpecialisedVars<_neutral, _bachelor, _daughters>::Get().N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<_neutral, _bachelor>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("bd2DstHYield_" +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("bd2DstH Yield " +
       ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      "@0*@1",
      RooArgList(
          SpecialisedVars<_neutral, _bachelor, _daughters>::Get().N_Dh_Bd2DstH(),
          NeutralBachelorVars<_neutral, _bachelor>::Get().bachEff())));
  // missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
  //       ("missIdYield_" +
  //        ComposeName(_neutral, _bachelor, _daughters))
  //           .c_str(),
  //       ("missId yield " +
  //        ComposeName(_neutral, _bachelor, _daughters))
  //           .c_str(),
  //       "@0*(1-@1)*@2",
  //       RooArgList(
  //           SpecialisedVars<_neutral, SwapBachelor<_bachelor>(),
  //                           _daughters>::Get()
  //               .N_Dh(),
  //           NeutralDaughtersVars<_neutral, _daughters>::Get().crossFeedRate(),
  //           NeutralBachelorVars<_neutral, _bachelor>::Get().missIdRate())));

  // CreateRooAddPdf();
}

// template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::kk>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::pik>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::kk>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::pik>::Pdf();

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters>
void Pdf<_neutral, _bachelor, _daughters>::CreateRooAddPdf() {

  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().signal());
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().crossFeed());
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().nonTmSignal());
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0pi0());
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0gamma());
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().bu2D0H());
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().bu2D0Hst());
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().bd2DstH());
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().missId());
  PdfBase::functions_.add(*PdfBase::combinatorial_);
  PdfBase::yields_.add(*PdfBase::signalYield_);
  PdfBase::yields_.add(*PdfBase::crossFeedYield_);
  PdfBase::yields_.add(*PdfBase::nonTmSignalYield_);
  PdfBase::yields_.add(*PdfBase::bu2Dst0Hst_D0pi0Yield_);
  PdfBase::yields_.add(*PdfBase::bu2Dst0Hst_D0gammaYield_);
  PdfBase::yields_.add(*PdfBase::bu2D0HYield_);
  PdfBase::yields_.add(*PdfBase::bu2D0HstYield_);
  PdfBase::yields_.add(*PdfBase::bd2DstHYield_);
  PdfBase::yields_.add(*PdfBase::missIdYield_);
  PdfBase::yields_.add(PdfBase::combinatorialYield_);

  PdfBase::addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("pdf_" + ComposeName(_neutral, _bachelor, _daughters))
          .c_str(),
      PdfBase::functions_, PdfBase::yields_));
}

// Assign miss-ID yields in a separate function after the PDF objects have been
// constructed to avoid cyclic dependancy (deadlock)
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters>
void Pdf<_neutral, _bachelor, _daughters>::AssignMissIdYields() {

  switch (_bachelor) {
  case Bachelor::pi:
    PdfBase::missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("missIdYield_" +
         ComposeName(_neutral, _bachelor, _daughters))
            .c_str(),
        ("missId yield " +
         ComposeName(_neutral, _bachelor, _daughters))
            .c_str(),
        "@0*(1-@1)*@2",
        RooArgList(
            SpecialisedVars<_neutral, SwapBachelor<_bachelor>(),
                            _daughters>::Get()
                .N_Dh(),
            NeutralDaughtersVars<_neutral, _daughters>::Get().crossFeedRate(),
            NeutralBachelorVars<_neutral, _bachelor>::Get().missIdRate())));
    break;
  case Bachelor::k:
    PdfBase::missIdYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("missIdYield_" +
         ComposeName(_neutral, _bachelor, _daughters))
            .c_str(),
        ("missId yield " +
         ComposeName(_neutral, _bachelor, _daughters))
            .c_str(),
        20 * DaughtersVars<_daughters>::Get().daughtersSF()));
    // PdfBase::missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
    //     ("missIdYield_" +
    //      ComposeName(_neutral, _bachelor, _daughters))
    //         .c_str(),
    //     "missId yield", "@0*(@1+@2)",
    //     RooArgList(NeutralBachelorVars<_neutral,
    //     _bachelor>::Get().missIdRate(),
    //                Pdf<_neutral, Bachelor::pi,
    //                _daughters>::Get().signalYield(),
    //                Pdf<_neutral, Bachelor::pi, _daughters>::Get()
    //                    .nonTmSignalYield())));
    break;
  }
}
