#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooCruijff.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
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
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooAbsReal &Bu2Dst0h_D0gamma_sigmaBu() {
    return *Bu2Dst0h_D0gamma_sigmaBu_;
  }
  RooCBShape &pdf1Bu_Bu2Dst0h_D0gamma() {
    return pdf1Bu_Bu2Dst0h_D0gamma_;
  }
  RooCBShape &pdf2Bu_Bu2Dst0h_D0gamma() {
    return pdf2Bu_Bu2Dst0h_D0gamma_;
  }
  RooAddPdf &pdfBu_Bu2Dst0h_D0gamma() {
    return pdfBu_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_Bu2Dst0h_D0gamma() {
    return *N_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0gamma() {
    return N_Delta_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_BuDelta_Bu2Dst0h_D0gamma() {
    return N_BuDelta_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar &Bu2Dst0h_D0pi0_sigmaBu() {
    return Bu2Dst0h_D0pi0_sigmaBu_;
  }
  RooCBShape &pdfBu_Bu2Dst0h_D0pi0() {
    return pdfBu_Bu2Dst0h_D0pi0_;
  }
  RooAbsReal &N_Bu2Dst0h_D0pi0() {
    return *N_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0pi0() {
    return N_Delta_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_BuDelta_Bu2Dst0h_D0pi0() {
    return N_BuDelta_Bu2Dst0h_D0pi0_;
  }
  // -------------------- MIS-REC -------------------- //
  RooRealVar &MisRec_sigmaBu() {
    return MisRec_sigmaBu_;
  }
  RooCBShape &pdfBu_MisRec() {
    return pdfBu_MisRec_;
  }
  RooAbsReal &N_MisRec() {
    return *N_MisRec_;
  }
  RooFormulaVar &N_Delta_MisRec() {
    return N_Delta_MisRec_;
  }
  RooFormulaVar &N_BuDelta_MisRec() {
    return N_BuDelta_MisRec_;
  }
  // -------------------- Bu2D0h -------------------- //
  RooAbsReal &Bu2D0h_sigmaLBu() {
    return *Bu2D0h_sigmaLBu_;
  }
  RooAbsReal &Bu2D0h_sigmaRBu() {
    return *Bu2D0h_sigmaRBu_;
  }
  RooCruijff &pdfBu_Bu2D0h() {
    return pdfBu_Bu2D0h_;
  }
  RooAbsReal &N_Bu2D0h() {
    return *N_Bu2D0h_;
  }
  RooFormulaVar &N_Delta_Bu2D0h() {
    return N_Delta_Bu2D0h_;
  }
  RooFormulaVar &N_BuDelta_Bu2D0h() {
    return N_BuDelta_Bu2D0h_;
  }

 private:
  int uniqueId_;
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0gamma_sigmaBu_;
  RooCBShape pdf1Bu_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Bu_Bu2Dst0h_D0gamma_;
  RooAddPdf pdfBu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_Bu2Dst0h_D0gamma_;
  RooFormulaVar N_Delta_Bu2Dst0h_D0gamma_;
  RooFormulaVar N_BuDelta_Bu2Dst0h_D0gamma_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar Bu2Dst0h_D0pi0_sigmaBu_;
  RooCBShape pdfBu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Bu2Dst0h_D0pi0_;
  RooFormulaVar N_Delta_Bu2Dst0h_D0pi0_;
  RooFormulaVar N_BuDelta_Bu2Dst0h_D0pi0_;
  // -------------------- MIS-REC -------------------- //
  RooRealVar MisRec_sigmaBu_;
  RooCBShape pdfBu_MisRec_;
  std::unique_ptr<RooAbsReal> N_MisRec_;
  RooFormulaVar N_Delta_MisRec_;
  RooFormulaVar N_BuDelta_MisRec_;
  // -------------------- Bu2D0h -------------------- //
  std::unique_ptr<RooAbsReal> Bu2D0h_sigmaLBu_;
  std::unique_ptr<RooAbsReal> Bu2D0h_sigmaRBu_;
  RooCruijff pdfBu_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_Bu2D0h_;
  RooFormulaVar N_Delta_Bu2D0h_;
  RooFormulaVar N_BuDelta_Bu2D0h_;
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
