#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooExponential.h"
#include "RooSimultaneous.h"
#include <map>

class PdfBase {
 public:
  void AddToSimultaneousPdf(RooSimultaneous &) const;

  inline int uniqueId() const { return uniqueId_; }
  inline Bachelor bachelor() const { return bachelor_; }
  inline Neutral neutral() const { return neutral_; }
  inline Daughters daughters() const { return daughters_; }
  inline Charge charge() const { return charge_; }

  inline RooRealVar &lambdaDeltaComb() { return lambdaDeltaComb_; }
  inline RooRealVar &a0LambdaBuComb() { return a0LambdaBuComb_; }
  inline RooPolyVar &lambdaBuComb() { return lambdaBuComb_; }
  inline RooExponential &pdfBuComb() { return pdfBuComb_; }
  inline RooExponential &pdfDeltaComb() { return pdfDeltaComb_; }
  inline RooProdPdf &pdfComb() { return pdfComb_; }
  inline RooAbsReal &yieldSignal() { return *yieldSignal_; }
  inline RooRealVar &yieldComb() { return yieldComb_; }
  inline RooArgList &yields() { return yields_; }
  inline RooArgList &functions() { return functions_; }
  inline RooAddPdf &addPdf() { return *addPdf_; }

  // std::unique_ptr<RooAddPdf> addPdf_;

  virtual RooProdPdf &pdfSignal() const = 0;
  virtual RooGaussian &pdfDeltaSignal() const = 0;
  virtual RooGaussian &pdfBuSignal() const = 0;

  // If a function or a method is defined in the header file, and the class is
  // not a template, it should be inline because otherwise the linker might fail
  // as the function will be present in multiple compiltation unit
  // function needs to be const when you don't change the object when the
  // function is called
  inline std::string CategoryName() const {
    return ComposeFittingName(neutral_, bachelor_, daughters_, charge_);
  }

 protected: // Can be accessed by deriving classes
  PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge);
  virtual ~PdfBase() {}

  int uniqueId_;
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

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
class Pdf : public PdfBase {
  using This_t = Pdf<_neutral, _bachelor, _daughters, _charge>;

 public:
  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId)).first;
    }
    return *it->second;
  }

  void AssignMissIdYields();
  void CreateRooAddPdf();

  // pdfSignal made in another class, but we only deal with PDF in the
  // executable. Give PDF functions to retrieve them
  virtual RooProdPdf &pdfSignal() const { 
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_).pdfSignal();
    // It shouldn't be private, it sould be protected then it can be accessed by inheriting classes
  }
  virtual RooGaussian &pdfDeltaSignal() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_).pdfDeltaSignal();
  }
  virtual RooGaussian &pdfBuSignal() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_).pdfBuSignal();
  }

  // Map of PDF objects with a unique ID for each identical PDF (PDF + ID =
  // singleton)
  // This is just a parameter/argument, you can call it anything you want
  Pdf(int whateverId);
  virtual ~Pdf() {}

 private:

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
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
// How does it know it's the same unique ID when one is uniqueId_ and the other
// uniqueId?
Pdf<_neutral, _bachelor, _daughters, _charge>::Pdf(int uniqueId)
    : PdfBase(uniqueId, _neutral, _bachelor, _daughters, _charge) {
  if (_charge == Charge::minus) {
    yieldSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yieldSignal_" + ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
            .c_str(),
        ("Signal Yield " +
         ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
            .c_str(),
        "(@0/2)*(@1+1)",
        RooArgList(
            NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(uniqueId)
                .N_Dst0h(),
            NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(uniqueId)
                .Asym())));
  } else {
    yieldSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yieldSignal_" + ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
            .c_str(),
        ("Signal Yield " +
         ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
            .c_str(),
        "(@0/2)*(1-@1)",
        RooArgList(
            NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(uniqueId)
                .N_Dst0h(),
            NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(uniqueId)
                .Asym())));
  }
  CreateRooAddPdf();
}

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::CreateRooAddPdf() {
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_).pdfSignal());
  PdfBase::functions_.add(PdfBase::pdfComb_);

  PdfBase::yields_.add(*PdfBase::yieldSignal_);
  PdfBase::yields_.add(PdfBase::yieldComb_);

  PdfBase::addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor, _daughters, _charge)).c_str(),
      ("pdf_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor, _daughters, _charge)).c_str(),
      PdfBase::functions_, PdfBase::yields_));
}
