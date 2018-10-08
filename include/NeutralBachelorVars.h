#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"

// Bachelor

template <Neutral neutral, Bachelor bachelor>
class NeutralBachelorVars {
 public:
  NeutralBachelorVars(int uniqueId_);
  ~NeutralBachelorVars() {}

  using This_t = NeutralBachelorVars<neutral, bachelor>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId_) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId_);  // Check if uniqueId_ already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId_, std::make_shared<This_t>(uniqueId_))
               .first;
    }
    return *it->second;
  }

  int uniqueId() { return uniqueId_; }
  RooAbsReal &sigmaLBu_Bu2Dst0h_Dst02D0pi0() {
    return *sigmaLBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooAbsReal &sigmaRBu_Bu2Dst0h_Dst02D0pi0() {
    return *sigmaRBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooCBShape &pdfLBu_Bu2Dst0h_Dst02D0pi0() {
    return pdfLBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooCBShape &pdfRBu_Bu2Dst0h_Dst02D0pi0() {
    return pdfRBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooAddPdf &pdfBu_Bu2Dst0h_Dst02D0pi0() { return pdfBu_Bu2Dst0h_Dst02D0pi0_; }
  RooProdPdf &pdf_Bu2Dst0h_Dst02D0pi0() { return pdf_Bu2Dst0h_Dst02D0pi0_; }
  RooAbsReal &sigmaLBu_Bu2Dst0h_Dst02D0gamma() {
    return *sigmaLBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAbsReal &sigmaRBu_Bu2Dst0h_Dst02D0gamma() {
    return *sigmaRBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooCBShape &pdfLBu_Bu2Dst0h_Dst02D0gamma() {
    return pdfLBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooCBShape &pdfRBu_Bu2Dst0h_Dst02D0gamma() {
    return pdfRBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAddPdf &pdfLRBu_Bu2Dst0h_Dst02D0gamma() {
    return pdfLRBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAbsReal &sigmaWideBu_Bu2Dst0h_Dst02D0gamma() {
    return *sigmaWideBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooGaussian &pdfWideBu_Bu2Dst0h_Dst02D0gamma() {
    return pdfWideBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAddPdf &pdfBu_Bu2Dst0h_Dst02D0gamma() {
    return pdfBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooProdPdf &pdf_Bu2Dst0h_Dst02D0gamma() { return pdf_Bu2Dst0h_Dst02D0gamma_; }
  RooAbsReal &sigmaLBu_overRec() { return *sigmaLBu_overRec_; }
  RooAbsReal &sigmaRBu_overRec() { return *sigmaRBu_overRec_; }
  RooCBShape &pdfLBu_overRec() { return pdfLBu_overRec_; }
  RooCBShape &pdfRBu_overRec() { return pdfRBu_overRec_; }
  RooAddPdf &pdfBu_overRec() { return pdfBu_overRec_; }
  RooProdPdf &pdf_overRec() { return pdf_overRec_; }
  RooAbsReal &sigmaLBu_Bu2Dst0hst_Dst02D0pi0() {
    return *sigmaLBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooAbsReal &sigmaRBu_Bu2Dst0hst_Dst02D0pi0() {
    return *sigmaRBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooCBShape &pdfLBu_Bu2Dst0hst_Dst02D0pi0() {
    return pdfLBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooCBShape &pdfRBu_Bu2Dst0hst_Dst02D0pi0() {
    return pdfRBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooAddPdf &pdfBu_Bu2Dst0hst_Dst02D0pi0() {
    return pdfBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooProdPdf &pdf_Bu2Dst0hst_Dst02D0pi0() { return pdf_Bu2Dst0hst_Dst02D0pi0_; }
  RooAbsReal &sigmaLBu_Bu2Dst0hst_Dst02D0gamma() {
    return *sigmaLBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooAbsReal &sigmaRBu_Bu2Dst0hst_Dst02D0gamma() {
    return *sigmaRBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooCBShape &pdfLBu_Bu2Dst0hst_Dst02D0gamma() {
    return pdfLBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooCBShape &pdfRBu_Bu2Dst0hst_Dst02D0gamma() {
    return pdfRBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooAddPdf &pdfBu_Bu2Dst0hst_Dst02D0gamma() {
    return pdfBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooProdPdf &pdf_Bu2Dst0hst_Dst02D0gamma() {
    return pdf_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooAbsReal &sigma1Bu_misRec() { return *sigma1Bu_misRec_; }
  RooAbsReal &sigma2Bu_misRec() { return *sigma2Bu_misRec_; }
  RooAbsReal &sigma3Bu_misRec() { return *sigma3Bu_misRec_; }
  RooGaussian &pdf1Bu_misRec() { return pdf1Bu_misRec_; }
  RooGaussian &pdf2Bu_misRec() { return pdf2Bu_misRec_; }
  RooGaussian &pdf3Bu_misRec() { return pdf3Bu_misRec_; }
  RooAddPdf &pdfBu_misRec() { return pdfBu_misRec_; }
  RooProdPdf &pdf_misRec() { return pdf_misRec_; }

 private:
  int uniqueId_;
  std::unique_ptr<RooAbsReal> sigmaLBu_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> sigmaRBu_Bu2Dst0h_Dst02D0pi0_;
  RooCBShape pdfLBu_Bu2Dst0h_Dst02D0pi0_;
  RooCBShape pdfRBu_Bu2Dst0h_Dst02D0pi0_;
  RooAddPdf pdfBu_Bu2Dst0h_Dst02D0pi0_;
  RooProdPdf pdf_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> sigmaLBu_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> sigmaRBu_Bu2Dst0h_Dst02D0gamma_;
  RooCBShape pdfLBu_Bu2Dst0h_Dst02D0gamma_;
  RooCBShape pdfRBu_Bu2Dst0h_Dst02D0gamma_;
  RooAddPdf pdfLRBu_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> sigmaWideBu_Bu2Dst0h_Dst02D0gamma_;
  RooGaussian pdfWideBu_Bu2Dst0h_Dst02D0gamma_;
  RooAddPdf pdfBu_Bu2Dst0h_Dst02D0gamma_;
  RooProdPdf pdf_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> sigmaLBu_overRec_;
  std::unique_ptr<RooAbsReal> sigmaRBu_overRec_;
  RooCBShape pdfLBu_overRec_;
  RooCBShape pdfRBu_overRec_;
  RooAddPdf pdfBu_overRec_;
  RooProdPdf pdf_overRec_;
  std::unique_ptr<RooAbsReal> sigmaLBu_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> sigmaRBu_Bu2Dst0hst_Dst02D0pi0_;
  RooCBShape pdfLBu_Bu2Dst0hst_Dst02D0pi0_;
  RooCBShape pdfRBu_Bu2Dst0hst_Dst02D0pi0_;
  RooAddPdf pdfBu_Bu2Dst0hst_Dst02D0pi0_;
  RooProdPdf pdf_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> sigmaLBu_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> sigmaRBu_Bu2Dst0hst_Dst02D0gamma_;
  RooCBShape pdfLBu_Bu2Dst0hst_Dst02D0gamma_;
  RooCBShape pdfRBu_Bu2Dst0hst_Dst02D0gamma_;
  RooAddPdf pdfBu_Bu2Dst0hst_Dst02D0gamma_;
  RooProdPdf pdf_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> sigma1Bu_misRec_;
  std::unique_ptr<RooAbsReal> sigma2Bu_misRec_;
  std::unique_ptr<RooAbsReal> sigma3Bu_misRec_;
  RooGaussian pdf1Bu_misRec_;
  RooGaussian pdf2Bu_misRec_;
  RooGaussian pdf3Bu_misRec_;
  RooAddPdf pdfBu_misRec_;
  RooProdPdf pdf_misRec_;
};

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId);
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId);
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId);
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId);
