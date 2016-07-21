#pragma once
#include "BachelorVars.h"
#include "Configuration.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
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

  RooRealVar &combinatorialConstant() { return combinatorialConstant_; }
  RooAbsPdf &combinatorial() { return *combinatorial_; }
  RooRealVar &bu2Dst0H_D0pi0Yield() { return bu2Dst0H_D0pi0Yield_; }
  RooRealVar &bu2Dst0H_D0gammaYield() { return bu2Dst0H_D0gammaYield_; }
  RooRealVar &nonTmSignalYield() { return nonTmSignalYield_; }
  RooRealVar &bu2Dst0Hst_D0pi0Yield() { return bu2Dst0Hst_D0pi0Yield_; }
  RooRealVar &bu2Dst0Hst_D0gammaYield() { return bu2Dst0Hst_D0gammaYield_; }
  RooRealVar &bu2D0HYield() { return bu2D0HYield_; }
  RooRealVar &bu2D0HstYield() { return bu2D0HstYield_; }
  RooRealVar &bd2DstHYield() { return bd2DstHYield_; }
  RooRealVar &missIdYield() { return missIdYield_; }
  RooRealVar &combinatorialYield() { return combinatorialYield_; }
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

  RooRealVar bu2Dst0H_D0pi0Yield_;
  RooRealVar bu2Dst0H_D0gammaYield_;
  RooRealVar nonTmSignalYield_;
  RooRealVar bu2Dst0Hst_D0pi0Yield_;
  RooRealVar bu2Dst0Hst_D0gammaYield_;
  RooRealVar bu2D0HYield_;
  RooRealVar bu2D0HstYield_;
  RooRealVar bd2DstHYield_;
  RooRealVar missIdYield_;
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
  PdfBase::functions_.add(
      BachelorVars<_neutral, _bachelor>::Get().bu2D0Hst());
  PdfBase::functions_.add(
      BachelorVars<_neutral, _bachelor>::Get().bd2DstH());
  PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().missId());
  PdfBase::functions_.add(*PdfBase::combinatorial_);
  PdfBase::yields_.add(PdfBase::bu2Dst0H_D0pi0Yield_);
  PdfBase::yields_.add(PdfBase::bu2Dst0H_D0gammaYield_);
  PdfBase::yields_.add(PdfBase::nonTmSignalYield_);
  PdfBase::yields_.add(PdfBase::bu2Dst0Hst_D0pi0Yield_);
  PdfBase::yields_.add(PdfBase::bu2Dst0Hst_D0gammaYield_);
  PdfBase::yields_.add(PdfBase::bu2D0HYield_);
  PdfBase::yields_.add(PdfBase::bu2D0HstYield_);
  PdfBase::yields_.add(PdfBase::bd2DstHYield_);
  PdfBase::yields_.add(PdfBase::missIdYield_);
  PdfBase::yields_.add(PdfBase::combinatorialYield_);

  PdfBase::addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
          .c_str(),
      ("pdf_" + ComposeFittingCategoryName(_neutral, _bachelor, _daughters))
          .c_str(),
      PdfBase::functions_, PdfBase::yields_));
}

