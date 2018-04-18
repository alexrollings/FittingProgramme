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

  RooRealVar &lambdaComb() { return lambdaComb_; }
  RooExponential &pdfComb() { return pdfComb_; }
  RooRealVar &yieldSignal() { return yieldSignal_; }
  RooRealVar &yieldComb() { return yieldComb_; }
  RooArgList &yields() { return yields_; }
  RooArgList &functions() { return functions_; }

  virtual RooAbsPdf &pdfSignal() const = 0;

 protected:
  PdfBase(Neutral neutral, Bachelor bachelor, Daughters daughters);
  virtual ~PdfBase() {}

  Neutral neutral_;
  Bachelor bachelor_;
  Daughters daughters_;

  RooRealVar lambdaComb_;
  RooExponential pdfComb_;
  RooRealVar yieldSignal_;
  RooRealVar yieldComb_;
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

  // pdfSignal made in another class, but we only deal with PDF in the
  // executable. Give PDF functions to retrieve them
  virtual RooAbsPdf &pdfSignal() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().pdfSignal();
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

  CreateRooAddPdf();
}

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters>
void Pdf<_neutral, _bachelor, _daughters>::CreateRooAddPdf() {
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().pdfSignal());
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().pdfComb());

  PdfBase::yields_.add(PdfBase::yieldSignal_);
  PdfBase::yields_.add(PdfBase::yieldComb_);

  PdfBase::addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeName(_neutral, _bachelor, _daughters)).c_str(),
      ("pdf_" + ComposeName(_neutral, _bachelor, _daughters)).c_str(),
      PdfBase::functions_, PdfBase::yields_));
}
