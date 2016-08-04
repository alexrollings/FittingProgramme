#pragma once
#include "BachelorVars.h"
#include "Configuration.h"
#include "DaughtersVars.h"
#include "NeutralDaughtersSharedVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooExponential.h"
#include "RooSimultaneous.h"

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
  RooFormulaVar &nonTmSignalYield() { return *nonTmSignalYield_; }
  RooFormulaVar &missIdYield() { return *missIdYield_; }
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
  std::unique_ptr<RooFormulaVar> nonTmSignalYield_;
  std::unique_ptr<RooFormulaVar> missIdYield_;
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

  virtual RooAbsPdf &nonTmSignal() const {
    return BachelorVars<_neutral, _bachelor>::Get().nonTmSignal();
  }

  virtual RooAbsPdf &signal() const {
    return BachelorVars<_neutral, _bachelor>::Get().signal();
  }

  virtual RooAbsPdf &crossFeed() const {
    return BachelorVars<_neutral, _bachelor>::Get().crossFeed();
  }

  virtual RooAbsPdf &bu2Dst0Hst_D0pi0() const {
    return BachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0pi0();
  }

  virtual RooAbsPdf &bu2Dst0Hst_D0gamma() const {
    return BachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0gamma();
  }

  virtual RooAbsPdf &bu2D0H() const {
    return BachelorVars<_neutral, _bachelor>::Get().bu2D0H();
  }

  virtual RooAbsPdf &bu2D0Hst() const {
    return BachelorVars<_neutral, _bachelor>::Get().bu2D0Hst();
  }

  virtual RooAbsPdf &bd2DstH() const {
    return BachelorVars<_neutral, _bachelor>::Get().bd2DstH();
  }

  virtual RooAbsPdf &missId() const {
    return BachelorVars<_neutral, _bachelor>::Get().missId();
  }

private:
  Pdf();
  virtual ~Pdf() {}
};

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters>
Pdf<_neutral, _bachelor, _daughters>::Pdf()
    : PdfBase(_neutral, _bachelor, _daughters) {

  // Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
  // TIME

  switch (_bachelor) {
  case Bachelor::pi:
    bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("bu2Dst0Hst_D0pi0Yield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2Dst0Hst_D0pi0 Yield",
        NeutralVars<_neutral>::Get().bu2Dst0Hst_D0pi0Expected() *
            BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
            DaughtersVars<_daughters>::Get().daughtersSF(),
        0, NeutralVars<_neutral>::Get().maxYield() *
               BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
               DaughtersVars<_daughters>::Get().daughtersSF()));
    bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("bu2Dst0Hst_D0gammaYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2Dst0Hst_D0gamma Yield",
        NeutralVars<_neutral>::Get().bu2Dst0Hst_D0gammaExpected() *
            BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
            DaughtersVars<_daughters>::Get().daughtersSF(),
        0, NeutralVars<_neutral>::Get().maxYield() *
               BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
               DaughtersVars<_daughters>::Get().daughtersSF()));
    switch (_neutral) {
    case Neutral::pi0:
      bu2D0HYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("bu2D0HYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2D0H Yield",
          NeutralVars<_neutral>::Get().bu2D0HExpected() *
              BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
              DaughtersVars<_daughters>::Get().daughtersSF(),
          0, NeutralVars<_neutral>::Get().maxYield() *
                 BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
                 DaughtersVars<_daughters>::Get().daughtersSF()));
      bd2DstHYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("bd2DstHYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bd2DstH Yield",
          NeutralVars<_neutral>::Get().bd2DstHExpected() *
              BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
              DaughtersVars<_daughters>::Get().daughtersSF(),
          0, NeutralVars<_neutral>::Get().maxYield() *
                 BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
                 DaughtersVars<_daughters>::Get().daughtersSF()));
      bu2D0HstYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("bu2D0HstYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2D0Hst Yield",
          NeutralVars<_neutral>::Get().bu2D0HstExpected() *
              BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
              DaughtersVars<_daughters>::Get().daughtersSF(),
          0, NeutralVars<_neutral>::Get().maxYield() *
                 BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
                 DaughtersVars<_daughters>::Get().daughtersSF()));
      break;
    case Neutral::gamma:
      bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("bu2D0HYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2D0H Yield", "@0*@1*@2",
          RooArgList(
              Pdf<Neutral::pi0, _bachelor, _daughters>::Get().bu2D0HYield(),
              Configuration::Get().relativeBu2D0HYield(),
              Configuration::Get().relativeNeutralAddition())));
      bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("bd2DstHYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bd2DstH Yield", "@0*@1*@2",
          RooArgList(
              Pdf<Neutral::pi0, _bachelor, _daughters>::Get().bd2DstHYield(),
              Configuration::Get().relativeBd2DstHYield(),
              Configuration::Get().relativeNeutralAddition())));
      bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("bu2D0HstYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2D0Hst Yield", "@0*@1*@2",
          RooArgList(
              Pdf<Neutral::pi0, _bachelor, _daughters>::Get().bu2D0HstYield(),
              Configuration::Get().relativeBu2D0HstYield(),
              Configuration::Get().relativeNeutralAddition())));
      break;
    }
    break;
  case Bachelor::k:
    bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("bu2D0HYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2D0H Yield", "@0*@1",
        RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get().bu2D0HYield(),
                   DaughtersVars<_daughters>::Get().bachelorRatio_Bu2D0H())));
    bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("bd2DstHYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bd2DstH Yield", "@0*@1",
        RooArgList(
            Pdf<_neutral, Bachelor::pi, _daughters>::Get().bd2DstHYield(),
            Configuration::Get().bachelorRatio_Bd2DstH())));
    bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("bu2Dst0Hst_D0pi0Yield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2Dst0Hst_D0pi0 Yield",
        NeutralVars<_neutral>::Get().bu2Dst0Hst_D0pi0Expected() *
            BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
            DaughtersVars<_daughters>::Get().daughtersSF(),
        0, NeutralVars<_neutral>::Get().maxYield() *
               BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
               DaughtersVars<_daughters>::Get().daughtersSF()));
    // "bu2Dst0Hst_D0pi0 Yield", "@0*@1",
    // RooArgList(
    //     Pdf<_neutral, Bachelor::pi, _daughters>::Get()
    //         .bu2Dst0Hst_D0pi0Yield(),
    //     NeutralDaughtersSharedVars<Neutral::pi0,
    //     _daughters>::Get().bachelorRatio_Bu2Dst0Hst())));
    bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("bu2Dst0Hst_D0gammaYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2Dst0Hst_D0gamma Yield",
        NeutralVars<_neutral>::Get().bu2Dst0Hst_D0gammaExpected() *
            BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
            DaughtersVars<_daughters>::Get().daughtersSF(),
        0, NeutralVars<_neutral>::Get().maxYield() *
               BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
               DaughtersVars<_daughters>::Get().daughtersSF()));
    // "bu2Dst0Hst_D0gamma Yield", "@0*@1",
    // RooArgList(
    //     Pdf<_neutral, Bachelor::pi, _daughters>::Get()
    //         .bu2Dst0Hst_D0gammaYield(),
    //     NeutralDaughtersSharedVars<Neutral::gamma,
    //     _daughters>::Get().bachelorRatio_Bu2Dst0Hst())));
    bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("bu2D0HstYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2D0Hst Yield", "@0*@1",
        RooArgList(
            Pdf<_neutral, Bachelor::pi, _daughters>::Get().bu2D0HstYield(),
            DaughtersVars<_daughters>::Get().bachelorRatio_Bu2D0Hst())));
    break;
  }

  switch (_neutral) {
  case Neutral::pi0:
    switch (_bachelor) {
    case Bachelor::pi:
      signalYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("signalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "Signal Yield",
          NeutralVars<_neutral>::Get().signalExpected() *
              BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
              DaughtersVars<_daughters>::Get().daughtersSF(),
          0, NeutralVars<_neutral>::Get().maxYield() *
                 BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
                 DaughtersVars<_daughters>::Get().daughtersSF()));
      crossFeedYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("crossFeedYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "Cross Feed Yield",
          NeutralVars<_neutral>::Get().crossFeedExpected() *
              BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
              DaughtersVars<_daughters>::Get().daughtersSF(),
          0, NeutralVars<_neutral>::Get().maxYield() *
                 BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
                 DaughtersVars<_daughters>::Get().daughtersSF()));
      nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "non TM Signal Yield", "@0*@1",
          RooArgList(PdfBase::signalYield(),
                     NeutralVars<_neutral>::Get().nonTmRatio())));
      break;
    case Bachelor::k:
      signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("signalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "Signal Yield", "@0*@1",
          RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                         .signalYield(),
                     NeutralDaughtersSharedVars<_neutral, _daughters>::Get()
                         .bachelorRatio_Bu2Dst0H()))),
      crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("crossFeedYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "CrossFeed Yield", "@0*@1",
          RooArgList(
              Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                  .crossFeedYield(),
              NeutralDaughtersSharedVars<Neutral::gamma, _daughters>::Get()
                  .bachelorRatio_Bu2Dst0H())));
      nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "non TM Signal Yield", "@0*@1*@2",
          RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                         .signalYield(),
                     NeutralVars<_neutral>::Get().nonTmRatio(),
                     NeutralDaughtersSharedVars<_neutral, _daughters>::Get()
                         .bachelorRatio_Bu2Dst0H())));
      break;
    }
    missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("missIdYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "missId yield", "(@0+@1)*@2*@3/(@4*@5)",
        RooArgList(PdfBase::signalYield(), PdfBase::nonTmSignalYield(),
                   BachelorVars<_neutral, _bachelor>::Get().bu2Dst0MissIdBR(),
                   BachelorVars<_neutral, _bachelor>::Get().missIdRate(),
                   BachelorVars<_neutral, _bachelor>::Get().bu2Dst0HBR(),
                   BachelorVars<_neutral, _bachelor>::Get().bachEff())));
    break;
  case Neutral::gamma:
    switch (_bachelor) {
    case Bachelor::pi:
      crossFeedYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("crossFeedYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "CrossFeed Yield",
          NeutralVars<_neutral>::Get().crossFeedExpected() *
              BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
              DaughtersVars<_daughters>::Get().daughtersSF(),
          0, NeutralVars<_neutral>::Get().maxYield() *
                 BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
                 DaughtersVars<_daughters>::Get().daughtersSF()));
      signalYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("signalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "Signal Yield",
          NeutralVars<_neutral>::Get().signalExpected() *
              BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
              DaughtersVars<_daughters>::Get().daughtersSF(),
          0, NeutralVars<_neutral>::Get().maxYield() *
                 BachelorVars<_neutral, _bachelor>::Get().bachelorSF() *
                 DaughtersVars<_daughters>::Get().daughtersSF()));
      nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "non TM Signal Yield", "@0*@1",
          RooArgList(Pdf<Neutral::pi0, _bachelor, _daughters>::Get()
                         .nonTmSignalYield(),
                     Configuration::Get().relativeNonTmYield(),
                     Configuration::Get().relativeNeutralAddition())));
      break;
    case Bachelor::k:
      crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("crossFeedYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "CrossFeed Yield", "@0*@1",
          RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                         .crossFeedYield(),
                     NeutralDaughtersSharedVars<Neutral::pi0, _daughters>::Get()
                         .bachelorRatio_Bu2Dst0H())));
      signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("signalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "Signal Yield", "@0*@1",
          RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                         .signalYield(),
                     NeutralDaughtersSharedVars<_neutral, _daughters>::Get()
                         .bachelorRatio_Bu2Dst0H())));
      nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "non TM Signal Yield", "@0*@1",
          RooArgList(
              Pdf<_neutral, Bachelor::pi, _daughters>::Get().nonTmSignalYield(),
              NeutralDaughtersSharedVars<_neutral, _daughters>::Get()
                  .bachelorRatio_Bu2Dst0H())));
      break;
    }
    missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("missIdYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "missId yield", "(@0+@1)*@2*@3/(@4*@5)",
        RooArgList(PdfBase::signalYield(),
                   PdfBase::nonTmSignalYield(),
                   BachelorVars<_neutral, _bachelor>::Get().bu2Dst0MissIdBR(),
                   BachelorVars<_neutral, _bachelor>::Get().missIdRate(),
                   BachelorVars<_neutral, _bachelor>::Get().bu2Dst0HBR(),
                   BachelorVars<_neutral, _bachelor>::Get().bachEff())));
    break;
  }

    PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().signal());
    PdfBase::functions_.add(
        BachelorVars<_neutral, _bachelor>::Get().crossFeed());
    PdfBase::functions_.add(
        BachelorVars<_neutral, _bachelor>::Get().nonTmSignal());
    PdfBase::functions_.add(
        BachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0pi0());
    PdfBase::functions_.add(
        BachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0gamma());
    PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().bu2D0H());
    PdfBase::functions_.add(
        BachelorVars<_neutral, _bachelor>::Get().bu2D0Hst());
    PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().bd2DstH());
    PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().missId());
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
      ("pdf_" + ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("pdf_" + ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
          .c_str(),
      PdfBase::functions_, PdfBase::yields_));
}

