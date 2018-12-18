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
  RooAbsReal &Bu2Dst0h_Dst02D0pi0_sigma1Bu() {
    return *Bu2Dst0h_Dst02D0pi0_sigma1Bu_;
  }
  RooAbsReal &Bu2Dst0h_Dst02D0pi0_sigma2Bu() {
    return *Bu2Dst0h_Dst02D0pi0_sigma2Bu_;
  }
  RooCBShape &pdf1Bu_Bu2Dst0h_Dst02D0pi0() {
    return pdf1Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooAbsReal &pdf2Bu_Bu2Dst0h_Dst02D0pi0() {
    return *pdf2Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooAddPdf &pdfBu_Bu2Dst0h_Dst02D0pi0() { return pdfBu_Bu2Dst0h_Dst02D0pi0_; }
  RooProdPdf &pdf_Bu2Dst0h_Dst02D0pi0() { return pdf_Bu2Dst0h_Dst02D0pi0_; }
  RooAbsReal &Bu2Dst0h_Dst02D0gamma_sigma1Bu() {
    return *Bu2Dst0h_Dst02D0gamma_sigma1Bu_;
  }
  RooAbsReal &Bu2Dst0h_Dst02D0gamma_sigma2Bu() {
    return *Bu2Dst0h_Dst02D0gamma_sigma2Bu_;
  }
  RooCBShape &pdf1Bu_Bu2Dst0h_Dst02D0gamma() {
    return pdf1Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooCBShape &pdf2Bu_Bu2Dst0h_Dst02D0gamma() {
    return pdf2Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAbsPdf &pdfBu_Bu2Dst0h_Dst02D0gamma() {
    return *pdfBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooProdPdf &pdf_Bu2Dst0h_Dst02D0gamma() { return pdf_Bu2Dst0h_Dst02D0gamma_; }
  RooAbsReal &overRec_sigma1Bu() { return *overRec_sigma1Bu_; }
  RooAbsReal &overRec_sigma2Bu() { return *overRec_sigma2Bu_; }
  RooCBShape &pdf1Bu_overRec() { return pdf1Bu_overRec_; }
  RooAbsPdf &pdf2Bu_overRec() { return *pdf2Bu_overRec_; }
  RooAddPdf &pdfBu_overRec() { return pdfBu_overRec_; }
  RooProdPdf &pdf_overRec() { return pdf_overRec_; }
  RooAbsReal &Bu2Dst0hst_Dst02D0pi0_sigma1Bu() {
    return *Bu2Dst0hst_Dst02D0pi0_sigma1Bu_;
  }
  RooAbsPdf &pdfBu_Bu2Dst0hst_Dst02D0pi0() {
    return *pdfBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooProdPdf &pdf_Bu2Dst0hst_Dst02D0pi0() { return pdf_Bu2Dst0hst_Dst02D0pi0_; }
  RooAbsReal &Bu2Dst0hst_Dst02D0gamma_sigma1Bu() {
    return *Bu2Dst0hst_Dst02D0gamma_sigma1Bu_;
  }
  // RooAbsReal &Bu2Dst0hst_Dst02D0gamma_sigma2Bu() {
  //   return *Bu2Dst0hst_Dst02D0gamma_sigma2Bu_;
  // }
  // RooCBShape &pdf1Bu_Bu2Dst0hst_Dst02D0gamma() {
  //   return pdf1Bu_Bu2Dst0hst_Dst02D0gamma_;
  // }
  // RooCBShape &pdf2Bu_Bu2Dst0hst_Dst02D0gamma() {
  //   return pdf2Bu_Bu2Dst0hst_Dst02D0gamma_;
  // }
  // RooAddPdf &pdfBu_Bu2Dst0hst_Dst02D0gamma() {
  //   return pdfBu_Bu2Dst0hst_Dst02D0gamma_;
  // }
  RooAbsPdf &pdfBu_Bu2Dst0hst_Dst02D0gamma() {
    return *pdfBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooProdPdf &pdf_Bu2Dst0hst_Dst02D0gamma() {
    return pdf_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooAbsReal &Bu2D0hst_sigma1Bu() {
    return *Bu2D0hst_sigma1Bu_;
  }
  RooAbsReal &Bu2D0hst_sigma2Bu() {
    return *Bu2D0hst_sigma2Bu_;
  }
  RooAbsPdf &pdfBu_Bu2D0hst() {
    return *pdfBu_Bu2D0hst_;
  }
  RooProdPdf &pdf_Bu2D0hst() { return pdf_Bu2D0hst_; }

 private:
  int uniqueId_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_Dst02D0pi0_sigma1Bu_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_Dst02D0pi0_sigma2Bu_;
  RooCBShape pdf1Bu_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> pdf2Bu_Bu2Dst0h_Dst02D0pi0_;
  RooAddPdf pdfBu_Bu2Dst0h_Dst02D0pi0_;
  RooProdPdf pdf_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_Dst02D0gamma_sigma1Bu_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_Dst02D0gamma_sigma2Bu_;
  RooCBShape pdf1Bu_Bu2Dst0h_Dst02D0gamma_;
  RooCBShape pdf2Bu_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0h_Dst02D0gamma_;
  RooProdPdf pdf_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> overRec_sigma1Bu_;
  std::unique_ptr<RooAbsReal> overRec_sigma2Bu_;
  RooCBShape pdf1Bu_overRec_;
  std::unique_ptr<RooAbsPdf> pdf2Bu_overRec_;
  RooAddPdf pdfBu_overRec_;
  RooProdPdf pdf_overRec_;
  std::unique_ptr<RooAbsReal> Bu2Dst0hst_Dst02D0pi0_sigma1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_Dst02D0pi0_;
  RooProdPdf pdf_Bu2Dst0hst_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> Bu2Dst0hst_Dst02D0gamma_sigma1Bu_;
  // std::unique_ptr<RooAbsReal> Bu2Dst0hst_Dst02D0gamma_sigma2Bu_;
  // RooCBShape pdf1Bu_Bu2Dst0hst_Dst02D0gamma_;
  // RooCBShape pdf2Bu_Bu2Dst0hst_Dst02D0gamma_;
  // RooAddPdf pdfBu_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_Dst02D0gamma_;
  RooProdPdf pdf_Bu2Dst0hst_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> Bu2D0hst_sigma1Bu_;
  std::unique_ptr<RooAbsReal> Bu2D0hst_sigma2Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  RooProdPdf pdf_Bu2D0hst_;
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
