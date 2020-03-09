#pragma once
#include "Configuration.h"
#include "NeutralVars.h"
#include "NeutralBachelorVars.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooAddPdf.h"
#include "RooSimultaneous.h"

class PdfMC {
  
 public:
  PdfMC(int uniqueId_);
  ~PdfMC() {}

  using This_t = PdfMC;

  static This_t &Get(int uniqueId_) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    auto it = singletons.find(uniqueId_);
    if (it == singletons.end()) {
      it = singletons.emplace(uniqueId_, std::make_shared<This_t>(uniqueId_))
               .first;
    }
    return *it->second;
  }

  int uniqueId() { return uniqueId_; }
  RooRealVar &boxEff() { return boxEff_; }
  RooRealVar &orEff() { return orEff_; }
  RooRealVar &deltaCutEff() { return deltaCutEff_; }
  RooRealVar &buDeltaCutEff() { return buDeltaCutEff_; }
  RooRealVar &yieldSignal() { return *yieldSignal_; }
  RooFormulaVar &yieldBuDeltaSignal() { return *yieldBuDeltaSignal_; }
  RooFormulaVar &yieldDeltaSignal() { return *yieldDeltaSignal_; }

  void AddToSimultaneousPdf(RooSimultaneous &) const;

private:

  int uniqueId_;
  int initSig_;
  RooRealVar boxEff_;
  RooRealVar orEff_;
  RooRealVar deltaCutEff_;
  RooRealVar buDeltaCutEff_;
  std::unique_ptr<RooRealVar> yieldSignal_;
  std::unique_ptr<RooFormulaVar> yieldBuDeltaSignal_;
  std::unique_ptr<RooFormulaVar> yieldDeltaSignal_;
  std::unique_ptr<RooAddPdf> pdfBuDelta_;
  std::unique_ptr<RooAddPdf> pdfDelta_;
};

