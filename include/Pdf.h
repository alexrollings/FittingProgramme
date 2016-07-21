#pragma once
#include "BachelorVars.h"
#include "Configuration.h"
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

  RooAbsReal &bu2Dst0H_D0pi0Yield() { return *bu2Dst0H_D0pi0Yield_; }
  RooAbsReal &bu2Dst0H_D0gammaYield() { return *bu2Dst0H_D0gammaYield_; }
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
  virtual RooAbsPdf &bu2Dst0H_D0pi0() const = 0;
  virtual RooAbsPdf &bu2Dst0H_D0gamma() const = 0;
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

  std::unique_ptr<RooAbsReal> bu2Dst0H_D0pi0Yield_;
  std::unique_ptr<RooAbsReal> bu2Dst0H_D0gammaYield_;
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

  virtual RooAbsPdf &bu2Dst0H_D0pi0() const {
    return BachelorVars<_neutral, _bachelor>::Get().bu2Dst0H_D0pi0();
  }

  virtual RooAbsPdf &bu2Dst0H_D0gamma() const {
    return BachelorVars<_neutral, _bachelor>::Get().bu2Dst0H_D0gamma();
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
    bu2D0HYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("bu2D0HYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2D0H Yield", 10000, 0, 30000));
    bd2DstHYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("bd2DstHYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bd2DstH Yield", 10000, 0, 30000));
    bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("bu2Dst0Hst_D0pi0Yield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2Dst0Hst_D0pi0 Yield", 10000, 0, 30000));
    bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("bu2Dst0Hst_D0gammaYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2Dst0Hst_D0gamma Yield", 10000, 0, 30000));
    bu2D0HstYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("bu2D0HstYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2D0Hst Yield", 10000, 0, 30000));
    break;
  case Bachelor::k:
    bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("bu2D0HYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2D0H Yield", "@0*@1",
        RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get().bu2D0HYield(),
                   Configuration::Get().relativeBachelorYields())));
    bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("bd2DstHYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bd2DstH Yield", "@0*@1",
        RooArgList(
            Pdf<_neutral, Bachelor::pi, _daughters>::Get().bd2DstHYield(),
            Configuration::Get().relativeBachelorYields())));
    bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("bu2Dst0Hst_D0pi0Yield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2Dst0Hst_D0pi0 Yield", "@0*@1",
        RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                       .bu2Dst0Hst_D0pi0Yield(),
                   Configuration::Get().relativeVectorYields())));
    bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("bu2Dst0Hst_D0gammaYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2Dst0Hst_D0gamma Yield", "@0*@1",
        RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                       .bu2Dst0Hst_D0gammaYield(),
                   Configuration::Get().relativeVectorYields())));
    bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("bu2D0HstYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "bu2D0Hst Yield", "@0*@1",
        RooArgList(
            Pdf<_neutral, Bachelor::pi, _daughters>::Get().bu2D0HstYield(),
            Configuration::Get().relativeVectorYields())));
    break;
  }

  switch (_neutral) {
  case Neutral::pi0:
    switch (_bachelor) {
    case Bachelor::pi:
      bu2Dst0H_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("bu2Dst0H_D0pi0Yield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2Dst0H_D0pi0 Yield", 10000, 0, 30000));
      bu2Dst0H_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("bu2Dst0H_D0gammaYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2Dst0H_D0gamma Yield", 10000, 0, 30000));
      nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "non TM Signal Yield", "@0*@1",
          RooArgList(PdfBase::bu2Dst0H_D0pi0Yield(),
                     NeutralVars<_neutral>::Get().nonTmRatio())));
      break;
    case Bachelor::k:
      bu2Dst0H_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("bu2Dst0H_D0pi0Yield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2Dst0H_D0pi0 Yield", 10000, 0, 30000));
      bu2Dst0H_D0gammaYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("bu2Dst0H_D0gammaYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2Dst0H_D0gamma Yield", "@0*@1",
          RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                         .bu2Dst0H_D0gammaYield(),
                     Configuration::Get().relativeBachelorYields())));
      nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "non TM Signal Yield", "@0*@1*@2",
          RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                         .bu2Dst0H_D0pi0Yield(),
                     NeutralVars<_neutral>::Get().nonTmRatio(),
                     Configuration::Get().relativeBachelorYields())));
      break;
    }
    missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("missIdYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "missId yield", "@0*@1*@2/@3/@4",
        RooArgList(PdfBase::bu2Dst0H_D0pi0Yield(),
                   BachelorVars<_neutral, _bachelor>::Get().bu2Dst0MissIdBR(),
                   BachelorVars<_neutral, _bachelor>::Get().missIdRate(),
                   BachelorVars<_neutral, _bachelor>::Get().bu2Dst0HBR(),
                   BachelorVars<_neutral, _bachelor>::Get().bachEff())));
    break;
  case Neutral::gamma:
    switch (_bachelor) {
    case Bachelor::pi:
      bu2Dst0H_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("bu2Dst0H_D0pi0Yield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2Dst0H_D0pi0 Yield", 10000, 0, 30000));
      bu2Dst0H_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("bu2Dst0H_D0gammaYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2Dst0H_D0gamma Yield", 10000, 0, 30000));
      nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "non TM Signal Yield", "@0*@1",
          RooArgList(PdfBase::bu2Dst0H_D0gammaYield(),
                     NeutralVars<_neutral>::Get().nonTmRatio())));
      break;
    case Bachelor::k:
      bu2Dst0H_D0pi0Yield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("bu2Dst0H_D0pi0Yield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2Dst0H_D0pi0 Yield", "@0*@1",
          RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                         .bu2Dst0H_D0pi0Yield(),
                     Configuration::Get().relativeBachelorYields())));
      bu2Dst0H_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
          ("bu2Dst0H_D0gammaYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "bu2Dst0H_D0gamma Yield", 10000, 0, 30000));
      nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
              .c_str(),
          "non TM Signal Yield", "@0*@1*@2",
          RooArgList(Pdf<_neutral, Bachelor::pi, _daughters>::Get()
                         .bu2Dst0H_D0gammaYield(),
                     NeutralVars<_neutral>::Get().nonTmRatio(),
                     Configuration::Get().relativeBachelorYields())));
      break;
    }
    missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("missIdYield_" +
         ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
            .c_str(),
        "missId yield", "@0*@1*@2/@3/@4",
        RooArgList(PdfBase::bu2Dst0H_D0gammaYield(),
                   BachelorVars<_neutral, _bachelor>::Get().bu2Dst0MissIdBR(),
                   BachelorVars<_neutral, _bachelor>::Get().missIdRate(),
                   BachelorVars<_neutral, _bachelor>::Get().bu2Dst0HBR(),
                   BachelorVars<_neutral, _bachelor>::Get().bachEff())));
    break;
  }

  PdfBase::functions_.add(
      BachelorVars<_neutral, _bachelor>::Get().bu2Dst0H_D0pi0());
  PdfBase::functions_.add(
      BachelorVars<_neutral, _bachelor>::Get().bu2Dst0H_D0gamma());
  PdfBase::functions_.add(
      BachelorVars<_neutral, _bachelor>::Get().nonTmSignal());
  PdfBase::functions_.add(
      BachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0pi0());
  PdfBase::functions_.add(
      BachelorVars<_neutral, _bachelor>::Get().bu2Dst0Hst_D0gamma());
  PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().bu2D0H());
  PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().bu2D0Hst());
  PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().bd2DstH());
  PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().missId());
  // PdfBase::functions_.add(*PdfBase::combinatorial_);
  PdfBase::yields_.add(*PdfBase::bu2Dst0H_D0pi0Yield_);
  PdfBase::yields_.add(*PdfBase::bu2Dst0H_D0gammaYield_);
  PdfBase::yields_.add(*PdfBase::nonTmSignalYield_);
  PdfBase::yields_.add(*PdfBase::bu2Dst0Hst_D0pi0Yield_);
  PdfBase::yields_.add(*PdfBase::bu2Dst0Hst_D0gammaYield_);
  PdfBase::yields_.add(*PdfBase::bu2D0HYield_);
  PdfBase::yields_.add(*PdfBase::bu2D0HstYield_);
  PdfBase::yields_.add(*PdfBase::bd2DstHYield_);
  PdfBase::yields_.add(*PdfBase::missIdYield_);
  // PdfBase::yields_.add(PdfBase::combinatorialYield_);

  PdfBase::addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("pdf_" + ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
          .c_str(),
      PdfBase::functions_, PdfBase::yields_));
}

