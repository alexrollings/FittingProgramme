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
  inline Bachelor bachelor() const { return bachelor_; }
  inline Neutral neutral() const { return neutral_; }
  inline Daughters daughters() const { return daughters_; }
  inline Charge charge() const { return charge_; }

  inline RooArgList &yieldsBu() { return yieldsBu_; }
  inline RooArgList &yieldsDelta() { return yieldsDelta_; }
  inline RooArgList &functionsBu() { return functionsBu_; }
  inline RooArgList &functionsDelta() { return functionsDelta_; }
  inline RooAddPdf &addPdfBu() { return *addPdfBu_; }
  inline RooAddPdf &addPdfDelta() { return *addPdfDelta_; }

  // std::unique_ptr<RooAddPdf> addPdf_;

  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfBu_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const = 0;
  virtual RooCBShape &pdfBu_Bu2Dst0h_D0pi0() const = 0;
  virtual RooDstD0BG &pdfDelta_MisRec() const = 0;
  virtual RooCBShape &pdfBu_MisRec() const = 0;
  virtual RooDstD0BG &pdfDelta_Bu2D0h() const = 0;
  virtual RooCruijff &pdfBu_Bu2D0h() const = 0;

  // If a function or a method is defined in the header file, and the class is
  // not a template, it should be inline because otherwise the linker might fail
  // as the function will be present in multiple compiltation unit
  // function needs to be const when you don't change the object when the
  // function is called
  inline std::string CategoryName(Mass mass) const {
    return ComposeFittingName(mass, neutral_, bachelor_, daughters_,
                              charge_);
  }

 protected:  // Can be accessed by deriving classes
  PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor,
          Daughters daughters, Charge charge);
  virtual ~PdfBase() {}

  int uniqueId_;
  Neutral neutral_;
  Bachelor bachelor_;
  Daughters daughters_;
  Charge charge_;

  RooArgList yieldsBu_;
  RooArgList yieldsDelta_;
  RooArgList functionsBu_;
  RooArgList functionsDelta_;
  std::unique_ptr<RooAddPdf> addPdfBu_;
  std::unique_ptr<RooAddPdf> addPdfDelta_;
};

template <Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
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
      it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId))
               .first;
    }
    return *it->second;
  }

  void CreateBuAddPdf();
  void CreateDeltaAddPdf();
  // void AssignMissIdYields();

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
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0pi0();
  }
  virtual RooCBShape &pdfBu_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0pi0();
  }
  virtual RooDstD0BG &pdfDelta_MisRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_MisRec();
  }
  virtual RooCBShape &pdfBu_MisRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_MisRec();
  }
  virtual RooDstD0BG &pdfDelta_Bu2D0h() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2D0h();
  }
  virtual RooCruijff &pdfBu_Bu2D0h() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2D0h();
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
template <Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
// How does it know it's the same unique ID when one is uniqueId_ and the other
// uniqueId?
Pdf<_neutral, _bachelor, _daughters, _charge>::Pdf(int uniqueId)
    : PdfBase(uniqueId, _neutral, _bachelor, _daughters, _charge) {
  CreateBuAddPdf();
  if (Configuration::Get().fit1D() == false) {
    CreateDeltaAddPdf();
  }
}

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
void Pdf<_neutral, _bachelor, _daughters,
         _charge>::CreateBuAddPdf() {
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_Bu2Dst0h_D0gamma());
    PdfBase::yieldsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Bu_Bu2Dst0h_D0gamma());
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bu2Dst0h_D0gamma());
    PdfBase::yieldsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Bu_misId_Bu2Dst0h_D0gamma());
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_Bu2Dst0h_D0pi0());
    PdfBase::yieldsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Bu_Bu2Dst0h_D0pi0());
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_MisRec());
    PdfBase::yieldsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Bu_MisRec());
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_Bu2D0h());
    PdfBase::yieldsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Bu_Bu2D0h());

  PdfBase::addPdfBu_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("addPdfBu_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                            _daughters, _charge))
          .c_str(), "",
      PdfBase::functionsBu_, PdfBase::yieldsBu_));
}

template <Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
void Pdf<_neutral, _bachelor, _daughters,
         _charge>::CreateDeltaAddPdf() {
    PdfBase::functionsDelta_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_Bu2Dst0h_D0gamma());
    PdfBase::yieldsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_Bu2Dst0h_D0gamma());
    PdfBase::functionsDelta_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bu2Dst0h_D0gamma());
    PdfBase::yieldsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_misId_Bu2Dst0h_D0gamma());
    PdfBase::functionsDelta_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_Bu2Dst0h_D0pi0());
    PdfBase::yieldsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_Bu2Dst0h_D0pi0());
    PdfBase::functionsDelta_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_MisRec());
    PdfBase::yieldsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_MisRec());
    PdfBase::functionsDelta_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_Bu2D0h());
    PdfBase::yieldsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_Bu2D0h());

  PdfBase::addPdfDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("addPdfDelta_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                            _daughters, _charge))
          .c_str(), "",
      PdfBase::functionsDelta_, PdfBase::yieldsDelta_));
}


//
// Assign miss-ID yields in a separate function after the PDF objects have been
// constructed to avoid cyclic dependancy (deadlock)
// template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
//           RunType _runType>
// void Pdf<_neutral, _bachelor, _daughters, _runType>::AssignMissIdYields() {
//   switch (_bachelor) {
//     case Bachelor::pi:
//       PdfBase::missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
//           ("missIdYield_" + ComposeName(_neutral, _bachelor, _daughters))
//               .c_str(),
//           ("missId yield " + ComposeName(_neutral, _bachelor, _daughters))
//               .c_str(),
//           "@0*(1-@1)*@2",
//           RooArgList(
//               SpecialisedVars<_neutral, SwapBachelor<_bachelor>(), _daughters,
//                               _runType>::Get()
//                   .N_Dh(),
//               NeutralVars<_neutral>::Get().crossFeedRate(),
//               NeutralBachelorVars<_neutral, _bachelor>::Get().missIdRate())));
//       break;
//     case Bachelor::k:
//       PdfBase::missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
//           ("missIdYield_" + ComposeName(_neutral, _bachelor, _daughters))
//               .c_str(),
//           "missId yield", "@0*(@1+@2)",
//           RooArgList(
//               NeutralBachelorVars<_neutral, _bachelor>::Get().missIdRate(),
//               Pdf<_neutral, Bachelor::pi, _daughters, _runType>::Get()
//                   .signalYield(),
//               Pdf<_neutral, Bachelor::pi, _daughters, _runType>::Get()
//                   .nonTmSignalYield())));
//       break;
//   }
// }
