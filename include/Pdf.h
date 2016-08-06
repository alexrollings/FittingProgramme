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

  // Declaring a function inside a class of const will not change any of the
  // variables inside of the object
  void CreateRooAddPdf();
};

template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Pdf();
template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk>::Pdf();
template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Pdf();
template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik>::Pdf();
template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi>::Pdf();
template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::kk>::Pdf();
template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi>::Pdf();
template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::pik>::Pdf();
template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Pdf();
template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk>::Pdf();
template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Pdf();
template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik>::Pdf();
template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Pdf();
template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::kk>::Pdf();
template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi>::Pdf();
template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::pik>::Pdf();


// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters>
void Pdf<_neutral, _bachelor, _daughters>::CreateRooAddPdf() {

  PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().signal());
  PdfBase::functions_.add(BachelorVars<_neutral, _bachelor>::Get().crossFeed());
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

