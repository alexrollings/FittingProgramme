#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
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
  RooAbsReal &sigmaDeltaSignal() { return *sigmaDeltaSignal_; }
  RooRealVar &a0SigmaBuSignal() { return a0SigmaBuSignal_; }
  RooRealVar &a1SigmaBuSignal() { return a1SigmaBuSignal_; }
  RooRealVar &a2SigmaBuSignal() { return a2SigmaBuSignal_; }
  RooGaussian &pdfDeltaSignal() { return pdfDeltaSignal_; }
  RooAbsReal &sigmaBuSignal() { return *sigmaBuSignal_; }
  RooGaussian &pdfBuSignal() { return pdfBuSignal_; }
  RooProdPdf &pdfSignal() { return pdfSignal_; }

 private:
  int uniqueId_;
  std::unique_ptr<RooAbsReal> sigmaDeltaSignal_;
  RooGaussian pdfDeltaSignal_;
  RooRealVar a0SigmaBuSignal_;
  RooRealVar a1SigmaBuSignal_;
  RooRealVar a2SigmaBuSignal_;
  std::unique_ptr<RooAbsReal> sigmaBuSignal_;
  RooGaussian pdfBuSignal_;
  RooProdPdf pdfSignal_;
};

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(int uniqueId);
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(int uniqueId);
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(int uniqueId);
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(int uniqueId);
