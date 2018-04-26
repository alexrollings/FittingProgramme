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
#include "NeutralBachelorDaughtersVars.h"

class PdfBase {
 public:
  void AddToSimultaneousPdf(RooSimultaneous &) const;

  Bachelor bachelor() const { return bachelor_; }
  Neutral neutral() const { return neutral_; }
  Daughters daughters() const { return daughters_; }
  Charge charge() const { return charge_; }

  RooRealVar &lambdaDeltaComb() { return lambdaDeltaComb_; }
  RooRealVar &a0LambdaBuComb() { return a0LambdaBuComb_; }
  RooPolyVar &lambdaBuComb() { return lambdaBuComb_; }
  RooExponential &pdfBuComb() { return pdfBuComb_; }
  RooExponential &pdfDeltaComb() { return pdfDeltaComb_; }
  RooProdPdf &pdfComb() { return pdfComb_; }
  RooAbsReal &yieldSignal() { return *yieldSignal_; }
  RooRealVar &yieldComb() { return yieldComb_; }
  RooArgList &yields() { return yields_; }
  RooArgList &functions() { return functions_; }

  virtual RooProdPdf &pdfSignal() const = 0;
  virtual RooGaussian &pdfDeltaSignal() const = 0;
  virtual RooGaussian &pdfBuSignal() const = 0;

 protected:
  PdfBase(Neutral neutral, Bachelor bachelor, Daughters daughters, Charge charge);
  virtual ~PdfBase() {}

  Neutral neutral_;
  Bachelor bachelor_;
  Daughters daughters_;
  Charge charge_;

  RooRealVar lambdaDeltaComb_;
  RooRealVar a0LambdaBuComb_;
  RooPolyVar lambdaBuComb_;
  RooExponential pdfBuComb_;
  RooExponential pdfDeltaComb_;
  RooProdPdf pdfComb_;
  std::unique_ptr<RooAbsReal> yieldSignal_;
  RooRealVar yieldComb_;
  RooArgList yields_;
  RooArgList functions_;
  std::unique_ptr<RooAddPdf> addPdf_;
};

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters, Charge _charge>
class Pdf : public PdfBase {
 public:
  static Pdf<_neutral, _bachelor, _daughters, _charge> &Get() {
    static Pdf<_neutral, _bachelor, _daughters, _charge> singleton;
    return singleton;
  }

  void AssignMissIdYields();
  void CreateRooAddPdf();

  // pdfSignal made in another class, but we only deal with PDF in the
  // executable. Give PDF functions to retrieve them
  virtual RooProdPdf &pdfSignal() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().pdfSignal();
  }
  virtual RooGaussian &pdfDeltaSignal() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().pdfDeltaSignal();
  }
  virtual RooGaussian &pdfBuSignal() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get().pdfBuSignal();
  }

 private:
  Pdf();
  virtual ~Pdf() {}

  // Declaring a function inside a class of const will not change any of the
  // variables inside of the object
};

// PdfBase is supposed to be general, so the template variables are not known at
// compile time. Any variables requiring a template in the constructor must
// therefore be initialised in Pdf.
// We initialise the variables in the text of the constructor as a pointer
// because otherwise we get the error of RooFit crashing we re-assigning a
// variable
// We have to do it in the text of the constructor because it's a field of
// PDFBase, not PDF
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters, Charge _charge>
Pdf<_neutral, _bachelor, _daughters, _charge>::Pdf()
    : PdfBase(_neutral, _bachelor, _daughters, _charge) {
  if (_charge == Charge::minus) {
    yieldSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yieldSignal_" + ComposeName(_neutral, _bachelor, _daughters, _charge))
            .c_str(),
        ("Signal Yield " +
         ComposeName(_neutral, _bachelor, _daughters, _charge))
            .c_str(),
        "(@0/2)*(@1+1)",
        RooArgList(
            NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get()
                .N_Dst0h(),
            NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get()
                .Asym())));
  } else {
    yieldSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yieldSignal_" + ComposeName(_neutral, _bachelor, _daughters, _charge))
            .c_str(),
        ("Signal Yield " +
         ComposeName(_neutral, _bachelor, _daughters, _charge))
            .c_str(),
        "(@0/2)*(1-@1)",
        RooArgList(
            NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get()
                .N_Dst0h(),
            NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get()
                .Asym())));
  }
  CreateRooAddPdf();
}

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters, Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::CreateRooAddPdf() {
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get().pdfSignal());
  PdfBase::functions_.add(PdfBase::pdfComb());

  PdfBase::yields_.add(*PdfBase::yieldSignal_);
  PdfBase::yields_.add(PdfBase::yieldComb_);

  PdfBase::addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeName(_neutral, _bachelor, _daughters, _charge)).c_str(),
      ("pdf_" + ComposeName(_neutral, _bachelor, _daughters, _charge)).c_str(),
      PdfBase::functions_, PdfBase::yields_));
}
