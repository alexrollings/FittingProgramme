#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
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
  RooAbsReal &sigmaDelta_Bu2Dst0h_Dst02D0gamma() {
    return *sigmaDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a0SigmaBu_Bu2Dst0h_Dst02D0gamma() {
    return a0SigmaBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a1SigmaBu_Bu2Dst0h_Dst02D0gamma() {
    return a1SigmaBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a2SigmaBu_Bu2Dst0h_Dst02D0gamma() {
    return a2SigmaBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooGaussian &pdfDelta_Bu2Dst0h_Dst02D0gamma() {
    return pdfDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAbsReal &sigmaBu_Bu2Dst0h_Dst02D0gamma() {
    return *sigmaBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooGaussian &pdfBu_Bu2Dst0h_Dst02D0gamma() {
    return pdfBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooProdPdf &pdf_Bu2Dst0h_Dst02D0gamma() { return pdf_Bu2Dst0h_Dst02D0gamma_; }
  RooAbsReal &sigmaDelta_Bu2Dst0h_Dst02D0pi0() {
    return *sigmaDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a0SigmaBu_Bu2Dst0h_Dst02D0pi0() {
    return a0SigmaBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a1SigmaBu_Bu2Dst0h_Dst02D0pi0() {
    return a1SigmaBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a2SigmaBu_Bu2Dst0h_Dst02D0pi0() {
    return a2SigmaBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooGaussian &pdfDelta_Bu2Dst0h_Dst02D0pi0() {
    return pdfDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooAbsReal &sigmaBu_Bu2Dst0h_Dst02D0pi0() {
    return *sigmaBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooGaussian &pdfBu_Bu2Dst0h_Dst02D0pi0() {
    return pdfBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooProdPdf &pdf_Bu2Dst0h_Dst02D0pi0() { return pdf_Bu2Dst0h_Dst02D0pi0_; }
  RooAbsReal &sigmaBu_Bu2D0h() { return *sigmaBu_Bu2D0h_; }
  RooGaussian &pdfBu_Bu2D0h() { return pdfBu_Bu2D0h_; }
  RooProdPdf &pdf_Bu2D0h() { return pdf_Bu2D0h_; }
  RooAbsReal &sigmaDelta_partialRec() { return *sigmaDelta_partialRec_; }
  RooRealVar &a0SigmaBu_partialRec() { return a0SigmaBu_partialRec_; }
  RooRealVar &a1SigmaBu_partialRec() { return a1SigmaBu_partialRec_; }
  RooRealVar &a2SigmaBu_partialRec() { return a2SigmaBu_partialRec_; }
  RooGaussian &pdfDelta_partialRec() { return pdfDelta_partialRec_; }
  RooAbsReal &sigmaBu_partialRec() { return *sigmaBu_partialRec_; }
  RooGaussian &pdfBu_partialRec() { return pdfBu_partialRec_; }
  RooProdPdf &pdf_partialRec() { return pdf_partialRec_; }

 private:
  int uniqueId_;
  std::unique_ptr<RooAbsReal> sigmaDelta_Bu2Dst0h_Dst02D0gamma_;
  RooGaussian pdfDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a0SigmaBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a1SigmaBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a2SigmaBu_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> sigmaBu_Bu2Dst0h_Dst02D0gamma_;
  RooGaussian pdfBu_Bu2Dst0h_Dst02D0gamma_;
  RooProdPdf pdf_Bu2Dst0h_Dst02D0gamma_;
  std::unique_ptr<RooAbsReal> sigmaDelta_Bu2Dst0h_Dst02D0pi0_;
  RooGaussian pdfDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a0SigmaBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a1SigmaBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a2SigmaBu_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> sigmaBu_Bu2Dst0h_Dst02D0pi0_;
  RooGaussian pdfBu_Bu2Dst0h_Dst02D0pi0_;
  RooProdPdf pdf_Bu2Dst0h_Dst02D0pi0_;
  std::unique_ptr<RooAbsReal> sigmaBu_Bu2D0h_;
  RooGaussian pdfBu_Bu2D0h_;
  RooProdPdf pdf_Bu2D0h_;
  std::unique_ptr<RooAbsReal> sigmaDelta_partialRec_;
  RooGaussian pdfDelta_partialRec_;
  RooRealVar a0SigmaBu_partialRec_;
  RooRealVar a1SigmaBu_partialRec_;
  RooRealVar a2SigmaBu_partialRec_;
  std::unique_ptr<RooAbsReal> sigmaBu_partialRec_;
  RooGaussian pdfBu_partialRec_;
  RooProdPdf pdf_partialRec_;
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
