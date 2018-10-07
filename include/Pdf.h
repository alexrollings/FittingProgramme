#pragma once
#include <map>
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
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

  inline RooAbsReal &yield_Bu2Dst0h_Dst02D0pi0() {
    return *yield_Bu2Dst0h_Dst02D0pi0_;
  }
  inline RooAbsReal &yield_Bu2Dst0h_Dst02D0gamma() {
    return *yield_Bu2Dst0h_Dst02D0gamma_;
  }
  inline RooAbsReal &yield_overRec() { return *yield_overRec_; }
  inline RooAbsReal &yield_Bu2Dst0hst_Dst02D0pi0() { return *yield_Bu2Dst0hst_Dst02D0pi0_; }
  inline RooAbsReal &yield_Bu2Dst0hst_Dst02D0gamma() { return *yield_Bu2Dst0hst_Dst02D0gamma_; }
  inline RooAbsReal &yield_misRec() { return *yield_misRec_; }
  inline RooRealVar &yield_Comb() { return yield_Comb_; }
  inline RooArgList &yields() { return yields_; }
  inline RooArgList &functions() { return functions_; }
  inline RooAddPdf &addPdf() { return *addPdf_; }

  // std::unique_ptr<RooAddPdf> addPdf_;

  virtual RooProdPdf &pdf_Bu2Dst0h_Dst02D0pi0() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_Dst02D0pi0() const = 0;
  virtual RooAddPdf &pdfBu_Bu2Dst0h_Dst02D0pi0() const = 0;
  virtual RooProdPdf &pdf_Bu2Dst0h_Dst02D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_Dst02D0gamma() const = 0;
  virtual RooAddPdf &pdfBu_Bu2Dst0h_Dst02D0gamma() const = 0;
  virtual RooProdPdf &pdf_overRec() const = 0;
  virtual RooDstD0BG &pdfDelta_overRec() const = 0;
  virtual RooAddPdf &pdfBu_overRec() const = 0;
  virtual RooProdPdf &pdf_Bu2Dst0hst_Dst02D0pi0() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0hst_Dst02D0pi0() const = 0;
  virtual RooGaussian &pdfBu_Bu2Dst0hst_Dst02D0pi0() const = 0;
  virtual RooProdPdf &pdf_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooRealVar &meanDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooRealVar &a0MeanBu_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooRealVar &sigmaLDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooRealVar &sigmaRDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooRealVar &aLDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooRealVar &aRDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooRealVar &nLDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooRealVar &nRDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooCBShape &pdfLDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooCBShape &pdfRDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  // virtual RooGaussian &pdfDelta_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooAddPdf &pdfBu_Bu2Dst0hst_Dst02D0gamma() const = 0;
  // virtual RooGaussian &pdfBu_Bu2Dst0hst_Dst02D0gamma() const = 0;
  virtual RooProdPdf &pdf_misRec() const = 0;
  virtual RooDstD0BG &pdfDelta_misRec() const = 0;
  virtual RooAddPdf &pdfBu_misRec() const = 0;
  virtual RooExponential &pdfBu_Comb() const = 0;
  virtual RooDstD0BG &pdfDelta_Comb() const = 0;

  // If a function or a method is defined in the header file, and the class is
  // not a template, it should be inline because otherwise the linker might fail
  // as the function will be present in multiple compiltation unit
  // function needs to be const when you don't change the object when the
  // function is called
  inline std::string CategoryName() const {
    return ComposeFittingName(neutral_, bachelor_, daughters_, charge_);
  }

 protected:  // Can be accessed by deriving classes
  PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge);
  virtual ~PdfBase() {}

  int uniqueId_;
  Neutral neutral_;
  Bachelor bachelor_;
  Daughters daughters_;
  Charge charge_;

  std::unique_ptr<RooAbsReal> yield_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> yield_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> yield_overRec_;
  std::unique_ptr<RooAbsReal> yield_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> yield_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> yield_misRec_;
  RooRealVar yield_Comb_;
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
      it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId))
               .first;
    }
    return *it->second;
  }

  void AssignMissIdYields();
  void CreateRooAddPdf();

  // pdf_Bu2Dst0h_Dst02D0neut are made in another class, but we only deal with
  // PDF in the
  // executable. Give PDF functions to retrieve them
  // It shouldn't be private, it sould be protected then it can be accessed by
  // inheriting classes
  virtual RooProdPdf &pdf_Bu2Dst0h_Dst02D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdf_Bu2Dst0h_Dst02D0pi0();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_Dst02D0pi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_Dst02D0pi0();
  }
  virtual RooAddPdf &pdfBu_Bu2Dst0h_Dst02D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_Dst02D0pi0();
  }
  virtual RooProdPdf &pdf_Bu2Dst0h_Dst02D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdf_Bu2Dst0h_Dst02D0gamma();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_Dst02D0gamma();
  }
  virtual RooAddPdf &pdfBu_Bu2Dst0h_Dst02D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_Dst02D0gamma();
  }
  virtual RooProdPdf &pdf_overRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdf_overRec();
  }
  virtual RooDstD0BG &pdfDelta_overRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_overRec();
  }
  virtual RooAddPdf &pdfBu_overRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_overRec();
  }
  virtual RooProdPdf &pdf_Bu2Dst0hst_Dst02D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdf_Bu2Dst0hst_Dst02D0pi0();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0hst_Dst02D0pi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0hst_Dst02D0pi0();
  }
  virtual RooGaussian &pdfBu_Bu2Dst0hst_Dst02D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0hst_Dst02D0pi0();
  }
  virtual RooProdPdf &pdf_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdf_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooRealVar &meanDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .meanDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooRealVar &a0MeanBu_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .a0MeanBu_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooRealVar &sigmaLDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .sigmaLDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooRealVar &sigmaRDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .sigmaRDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooRealVar &aLDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .aLDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooRealVar &aRDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .aRDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooRealVar &nLDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .nLDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooRealVar &nRDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .nRDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooCBShape &pdfLDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfLDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  virtual RooCBShape &pdfRDelta_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfRDelta_Bu2Dst0hst_Dst02D0gamma();
  }
  // virtual RooGaussian &pdfDelta_Bu2Dst0hst_Dst02D0gamma() const {
  //   return NeutralVars<_neutral>::Get(uniqueId_)
  //       .pdfDelta_Bu2Dst0hst_Dst02D0gamma();
  // }
  virtual RooAddPdf &pdfBu_Bu2Dst0hst_Dst02D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0hst_Dst02D0gamma();
  }
  // virtual RooGaussian &pdfBu_Bu2Dst0hst_Dst02D0gamma() const {
  //   return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
  //       .pdfBu_Bu2Dst0hst_Dst02D0gamma();
  // }
  virtual RooProdPdf &pdf_misRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdf_misRec();
  }
  virtual RooDstD0BG &pdfDelta_misRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_misRec();
  }
  virtual RooAddPdf &pdfBu_misRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misRec();
  }
  virtual RooExponential &pdfBu_Comb() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfBu_Comb();
  }
  virtual RooDstD0BG &pdfDelta_Comb() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Comb();
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
  yield_misRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("yield_misRec_" +
       ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
          .c_str(),
      ("misRec Yield " +
       ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
          .c_str(),
      "@0",
      RooArgList(
          NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
              uniqueId)
              .N_misRec())));
  switch (_charge) {
    case (Charge::minus): {
      yield_overRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("yield_overRec_" +
           ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
              .c_str(),
          ("overRec Yield " +
           ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
              .c_str(),
          "(@0/2)*(@1+1)",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                  _daughters>::Get(uniqueId)
                         .N_overRec(),
                     NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                  _daughters>::Get(uniqueId)
                         .asym_overRec())));
      yield_Bu2Dst0hst_Dst02D0pi0_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("yield_Bu2Dst0hst_Dst02D0pi0_" +
               ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
                  .c_str(),
              ("Bu2Dst0hst_Dst02D0pi0 Yield " +
               ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
                  .c_str(),
              "(@0/2)*(@1+1)",
              RooArgList(NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                      _daughters>::Get(uniqueId)
                             .N_Bu2Dst0hst_Dst02D0pi0(),
                         NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                      _daughters>::Get(uniqueId)
                             .asym_Bu2Dst0hst_Dst02D0pi0())));
      switch (_neutral) {
        case (Neutral::pi0): {
          yield_Bu2Dst0h_Dst02D0pi0_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0h_Dst02D0pi0_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0pi0 Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "(@0/2)*(@1+1)",
                  RooArgList(
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .N_Bu2Dst0h_Dst02D0pi0(),
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .asym_Bu2Dst0h_Dst02D0pi0())));
          yield_Bu2Dst0h_Dst02D0gamma_ = nullptr;
          yield_Bu2Dst0hst_Dst02D0gamma_ = nullptr;
          break;
        }
        case (Neutral::gamma): {
          yield_Bu2Dst0h_Dst02D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0h_Dst02D0gamma_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0gamma Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "(@0/2)*(@1+1)",
                  RooArgList(
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .N_Bu2Dst0h_Dst02D0gamma(),
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .asym_Bu2Dst0h_Dst02D0gamma())));
          yield_Bu2Dst0h_Dst02D0pi0_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0h_Dst02D0pi0_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0pi0 Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "(@0/2)*(@1+1)",
                  RooArgList(
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .N_Bu2Dst0h_Dst02D0pi0(),
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .asym_Bu2Dst0h_Dst02D0pi0())));
          yield_Bu2Dst0hst_Dst02D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0hst_Dst02D0gamma_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0hst_Dst02D0gamma Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "(@0/2)*(@1+1)",
                  RooArgList(
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .N_Bu2Dst0hst_Dst02D0gamma(),
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .asym_Bu2Dst0hst_Dst02D0gamma())));
          break;
        }
      }
      break;
    }
    case (Charge::plus): {
      yield_overRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("yield_overRec_" +
           ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
              .c_str(),
          ("overRec Yield " +
           ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
              .c_str(),
          "(@0/2)*(1-@1)",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                  _daughters>::Get(uniqueId)
                         .N_overRec(),
                     NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                  _daughters>::Get(uniqueId)
                         .asym_overRec())));
      yield_Bu2Dst0hst_Dst02D0pi0_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("yield_Bu2Dst0hst_Dst02D0pi0_" +
               ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
                  .c_str(),
              ("Bu2Dst0hst_Dst02D0pi0 Yield " +
               ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
                  .c_str(),
              "(@0/2)*(1-@1)",
              RooArgList(NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                      _daughters>::Get(uniqueId)
                             .N_Bu2Dst0hst_Dst02D0pi0(),
                         NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                      _daughters>::Get(uniqueId)
                             .asym_Bu2Dst0hst_Dst02D0pi0())));
      switch (_neutral) {
        case (Neutral::pi0): {
          yield_Bu2Dst0h_Dst02D0pi0_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0h_Dst02D0pi0_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0pi0 Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "(@0/2)*(1-@1)",
                  RooArgList(
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .N_Bu2Dst0h_Dst02D0pi0(),
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .asym_Bu2Dst0h_Dst02D0pi0())));
          yield_Bu2Dst0h_Dst02D0gamma_ = nullptr;
          yield_Bu2Dst0hst_Dst02D0gamma_ = nullptr;
          break;
        }
        case (Neutral::gamma): {
          yield_Bu2Dst0h_Dst02D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0h_Dst02D0gamma_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0gamma Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "(@0/2)*(1-@1)",
                  RooArgList(
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .N_Bu2Dst0h_Dst02D0gamma(),
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .asym_Bu2Dst0h_Dst02D0gamma())));
          yield_Bu2Dst0h_Dst02D0pi0_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0h_Dst02D0pi0_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0pi0 Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "(@0/2)*(1-@1)",
                  RooArgList(
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .N_Bu2Dst0h_Dst02D0pi0(),
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .asym_Bu2Dst0h_Dst02D0pi0())));
          yield_Bu2Dst0hst_Dst02D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0hst_Dst02D0gamma_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0hst_Dst02D0gamma Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "(@0/2)*(1-@1)",
                  RooArgList(
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .N_Bu2Dst0hst_Dst02D0gamma(),
                      NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                   _daughters>::Get(uniqueId)
                          .asym_Bu2Dst0hst_Dst02D0gamma())));
          break;
        }
      }
      break;
    }
    case (Charge::total): {
      yield_overRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("yield_overRec_" +
           ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
              .c_str(),
          ("overRec Yield " +
           ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
              .c_str(),
          "@0",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                  _daughters>::Get(uniqueId)
                         .N_overRec())));
      yield_Bu2Dst0hst_Dst02D0pi0_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("yield_Bu2Dst0hst_Dst02D0pi0_" +
               ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
                  .c_str(),
              ("Bu2Dst0hst_Dst02D0pi0 Yield " +
               ComposeName(uniqueId, _neutral, _bachelor, _daughters, _charge))
                  .c_str(),
              "@0",
              RooArgList(NeutralBachelorDaughtersVars<_neutral, _bachelor,
                                                      _daughters>::Get(uniqueId)
                             .N_Bu2Dst0hst_Dst02D0pi0())));
      switch (_neutral) {
        case (Neutral::pi0): {
          yield_Bu2Dst0h_Dst02D0pi0_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0h_Dst02D0pi0_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0pi0 Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "@0",
                  RooArgList(NeutralBachelorDaughtersVars<
                                 _neutral, _bachelor, _daughters>::Get(uniqueId)
                                 .N_Bu2Dst0h_Dst02D0pi0())));
          yield_Bu2Dst0h_Dst02D0gamma_ = nullptr;
          yield_Bu2Dst0hst_Dst02D0gamma_ = nullptr;
          break;
        }
        case (Neutral::gamma): {
          yield_Bu2Dst0h_Dst02D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0h_Dst02D0gamma_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0gamma Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "@0",
                  RooArgList(NeutralBachelorDaughtersVars<
                                 _neutral, _bachelor, _daughters>::Get(uniqueId)
                                 .N_Bu2Dst0h_Dst02D0gamma())));
          yield_Bu2Dst0h_Dst02D0pi0_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0h_Dst02D0pi0_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0pi0 Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "@0",
                  RooArgList(NeutralBachelorDaughtersVars<
                                 _neutral, _bachelor, _daughters>::Get(uniqueId)
                                 .N_Bu2Dst0h_Dst02D0pi0())));
          yield_Bu2Dst0hst_Dst02D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("yield_Bu2Dst0hst_Dst02D0gamma_" +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  ("Bu2Dst0hst_Dst02D0gamma Yield " +
                   ComposeName(uniqueId, _neutral, _bachelor, _daughters,
                               _charge))
                      .c_str(),
                  "@0",
                  RooArgList(NeutralBachelorDaughtersVars<
                                 _neutral, _bachelor, _daughters>::Get(uniqueId)
                                 .N_Bu2Dst0hst_Dst02D0gamma())));
          break;
        }
      }
      break;
    }
  }
  CreateRooAddPdf();
}

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::CreateRooAddPdf() {
  std::cout << "\n\nSignal:";
  NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
      .pdf_Bu2Dst0h_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec 2D";
  NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
      .pdf_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec Delta:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .pdfDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec a0 mean Bu:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .a0MeanBu_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec mean:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .meanDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec sigma left:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .sigmaLDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec sigma right:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .sigmaRDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec a left:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .aLDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec a right:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .aRDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec n left:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .nLDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec n right:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .nRDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec left Delta:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .pdfLDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\nPartial rec right Delta:";
  NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      .pdfRDelta_Bu2Dst0hst_Dst02D0gamma()
      .Print();
  std::cout << "\n\n";
  if (_neutral == Neutral::gamma) {
    PdfBase::functions_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdf_Bu2Dst0h_Dst02D0gamma());
    PdfBase::yields_.add(*PdfBase::yield_Bu2Dst0h_Dst02D0gamma_);
    PdfBase::functions_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdf_Bu2Dst0hst_Dst02D0gamma());
    PdfBase::yields_.add(*PdfBase::yield_Bu2Dst0hst_Dst02D0gamma_);
  }
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdf_Bu2Dst0h_Dst02D0pi0());
  PdfBase::yields_.add(*PdfBase::yield_Bu2Dst0h_Dst02D0pi0_);
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdf_overRec());
  PdfBase::yields_.add(*PdfBase::yield_overRec_);
  // PdfBase::functions_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdf_Bu2Dst0hst_Dst02D0pi0());
  // PdfBase::yields_.add(*PdfBase::yield_Bu2Dst0hst_Dst02D0pi0_);
  PdfBase::functions_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdf_misRec());
  PdfBase::yields_.add(*PdfBase::yield_misRec_);
  // PdfBase::functions_.add(
  //     NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdf_Comb());
  // PdfBase::yields_.add(PdfBase::yield_Comb_);

  PdfBase::addPdf_ = std::unique_ptr<RooAddPdf>(
      new RooAddPdf(("pdf_" + ComposeName(PdfBase::uniqueId_, _neutral,
                                          _bachelor, _daughters, _charge))
                        .c_str(),
                    ("pdf_" + ComposeName(PdfBase::uniqueId_, _neutral,
                                          _bachelor, _daughters, _charge))
                        .c_str(),
                    PdfBase::functions_, PdfBase::yields_));
}
