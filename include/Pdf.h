#pragma once
#include <map>
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooSimultaneous.h"

class PdfBase {
 public:
  void AddToSimultaneousPdf(RooSimultaneous &) const;

  inline int uniqueId() const { return uniqueId_; }
  inline Mass mass() const { return mass_; }
  inline Bachelor bachelor() const { return bachelor_; }
  inline Neutral neutral() const { return neutral_; }
  inline Daughters daughters() const { return daughters_; }
  inline Charge charge() const { return charge_; }

  inline RooArgList &yields() { return yields_; }
  inline RooArgList &functions() { return functions_; }
  inline RooAddPdf &addPdf() { return *addPdf_; }

  // std::unique_ptr<RooAddPdf> addPdf_;

  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfBu_Bu2Dst0h_D0gamma() const = 0;
  virtual RooDstD0BG &pdfDelta_MisRec() const = 0;
  virtual RooCBShape &pdfBu_MisRec() const = 0;

  // If a function or a method is defined in the header file, and the class is
  // not a template, it should be inline because otherwise the linker might fail
  // as the function will be present in multiple compiltation unit
  // function needs to be const when you don't change the object when the
  // function is called
  inline std::string CategoryName() const {
    return ComposeFittingName(mass_, neutral_, bachelor_, daughters_,
                              charge_);
  }

 protected:  // Can be accessed by deriving classes
  PdfBase(int uniqueId, Mass mass, Neutral neutral, Bachelor bachelor,
          Daughters daughters, Charge charge);
  virtual ~PdfBase() {}

  int uniqueId_;
  Mass mass_;
  Neutral neutral_;
  Bachelor bachelor_;
  Daughters daughters_;
  Charge charge_;

  RooArgList yields_;
  RooArgList functions_;
  std::unique_ptr<RooAddPdf> addPdf_;
};

template <Mass _mass, Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
class Pdf : public PdfBase {
  using This_t = Pdf<_mass, _neutral, _bachelor, _daughters, _charge>;

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
      it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId))
               .first;
    }
    return *it->second;
  }

  void CreateRooAddPdf();

  // pdf_Bu2Dst0h_Dst02D0neut are made in another class, but we only deal with
  // PDF in the
  // executable. Give PDF functions to retrieve them
  // It shouldn't be private, it sould be protected then it can be accessed by
  // inheriting classes
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfBu_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma();
  }
  virtual RooDstD0BG &pdfDelta_MisRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_MisRec();
  }
  virtual RooCBShape &pdfBu_MisRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_MisRec();
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
// Can't make a list of different types. Pdfs have different types because of
// the templating. They all inheret from PDFBase, so we can make a list of
// PDFBase objects
template <Mass _mass, Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
// How does it know it's the same unique ID when one is uniqueId_ and the other
// uniqueId?
Pdf<_mass, _neutral, _bachelor, _daughters, _charge>::Pdf(int uniqueId)
    : PdfBase(uniqueId, _mass, _neutral, _bachelor, _daughters, _charge) {
  CreateRooAddPdf();
}

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Mass _mass, Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
void Pdf<_mass, _neutral, _bachelor, _daughters,
         _charge>::CreateRooAddPdf() {
  if (_mass == Mass::delta) {
    PdfBase::functions_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_Bu2Dst0h_D0gamma());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_Bu2Dst0h_D0gamma());
    PdfBase::functions_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_MisRec());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_MisRec());
  } else {
    PdfBase::functions_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_Bu2Dst0h_D0gamma());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_BuDelta_Bu2Dst0h_D0gamma());
    PdfBase::functions_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_MisRec());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_BuDelta_MisRec());
  }

  PdfBase::addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                            _daughters, _charge))
          .c_str(),
      ("pdf_" + ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                            _daughters, _charge))
          .c_str(),
      PdfBase::functions_, PdfBase::yields_));
}

// addPdf - put in own class (e.g. MassVars)
