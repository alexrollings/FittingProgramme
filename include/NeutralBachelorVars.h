#pragma once
#include "RooAbsPdf.h"
#include "RooFormulaVar.h"
#include "RooAddPdf.h"
#include "NeutralVars.h" 
#include "Configuration.h" 
#include "RooConstVar.h"

// Bachelor

template <Neutral neutral, Bachelor bachelor> class NeutralBachelorVars {

public:
  static NeutralBachelorVars<neutral, bachelor> &Get() {
    static NeutralBachelorVars<neutral, bachelor> singleton;
    return singleton;
  }

  RooAbsReal &sigmaSignal() { return *sigmaSignal1_; }
  RooGaussian &pdfSignal() { return pdfSignal_; }

private:
  NeutralBachelorVars();
  ~NeutralBachelorVars() {}

  std::unique_ptr<RooAbsReal> sigmaSignal_;
  RooGaussian pdfSignal_;
};

template <> NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars();
template <> NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars();
template <> NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars();
template <> NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars();


