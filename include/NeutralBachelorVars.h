#pragma once
#include "Configuration.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"

// Bachelor

template <Neutral neutral, Bachelor bachelor>
class NeutralBachelorVars {
 public:
  static NeutralBachelorVars<neutral, bachelor> &Get() {
    static NeutralBachelorVars<neutral, bachelor> singleton;
    return singleton;
  }

  RooAbsReal &sigmaDeltaSignal() { return *sigmaDeltaSignal_; }
  RooGaussian &pdfDeltaSignal() { return pdfDeltaSignal_; }
  RooAbsReal &sigmaBuSignal() { return *sigmaBuSignal_; }
  RooGaussian &pdfBuSignal() { return pdfBuSignal_; }
  RooProdPdf &pdfSignal() { return pdfSignal_; }

 private:
  NeutralBachelorVars();
  ~NeutralBachelorVars() {}

  std::unique_ptr<RooAbsReal> sigmaDeltaSignal_;
  RooGaussian pdfDeltaSignal_;
  std::unique_ptr<RooAbsReal> sigmaBuSignal_;
  RooGaussian pdfBuSignal_;
  RooProdPdf pdfSignal_;
};

template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars();
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars();
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars();
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars();
