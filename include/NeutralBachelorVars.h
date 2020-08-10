#pragma once
#include "Configuration.h"
#include "Efficiencies.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "NeutralBachelorChargeVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooCruijff.h"
#include "RooGaussian.h"
#include "RooFormulaVar.h"
#include "RooProdPdf.h"

// Split by charge; only for pik
template <Neutral neutral, Bachelor bachelor>
RooFormulaVar *Make_R_ADS(int uniqueId, const char *name,
                          RooAbsReal &R_piK_minus, RooAbsReal &R_piK_plus) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, bachelor, Daughters::pik)).c_str(),
      "", "(@0+@1)/2", RooArgSet(R_piK_minus, R_piK_plus));
}

// Summed over charge; only for pik
template <Neutral neutral, Bachelor bachelor>
RooFormulaVar *Make_R_ADS(int uniqueId, const char *name,
                          RooAbsReal &R_piK_total) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, bachelor, Daughters::pik)).c_str(),
      "", "@0", RooArgSet(R_piK_total));
}

template <Neutral neutral, Bachelor bachelor>
class NeutralBachelorVars {
 public:
  NeutralBachelorVars(int uniqueId);
  ~NeutralBachelorVars() {}

  using This_t = NeutralBachelorVars<neutral, bachelor>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  int uniqueId() { return uniqueId_; }
  // -------------------- PDF SHAPES -------------------- //
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooAbsReal &Bu2Dst0h_D0gamma_sigmaBu() { return *Bu2Dst0h_D0gamma_sigmaBu_; }
  RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma() { return *pdfBu_Bu2Dst0h_D0gamma_; }
  RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma() { return pdfBuPartial_Bu2Dst0h_D0gamma_; }
  // -------------------- Mis-ID ------------------- //
  RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() {
    return *pdfDelta_misId_Bu2Dst0h_D0gamma_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() {
    return *pdfBu_misId_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooAbsReal &Bu2Dst0h_D0pi0_sigmaDelta() { return *Bu2Dst0h_D0pi0_sigmaDelta_; }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() { return pdfDelta_Bu2Dst0h_D0pi0_; }
  RooAbsReal &Bu2Dst0h_D0pi0_sigmaBu() { return *Bu2Dst0h_D0pi0_sigmaBu_; }
  RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0() { return *pdfBu_Bu2Dst0h_D0pi0_; }
  RooAbsReal &Bu2Dst0h_D0pi0_sigma1BuPartial() {
    return *Bu2Dst0h_D0pi0_sigma1BuPartial_;
  }
  RooAbsReal &Bu2Dst0h_D0pi0_sigma2BuPartial() {
    return *Bu2Dst0h_D0pi0_sigma2BuPartial_;
  }
  RooAbsReal &Bu2Dst0h_D0pi0_sigma3BuPartial() {
    return *Bu2Dst0h_D0pi0_sigma3BuPartial_;
  }
  RooAddPdf &pdfBuPartial_Bu2Dst0h_D0pi0() {
    return pdfBuPartial_Bu2Dst0h_D0pi0_;
  }
  // -------------------- Mis-ID ------------------- //
  RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0pi0() {
    return *pdfDelta_misId_Bu2Dst0h_D0pi0_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() {
    return *pdfBu_misId_Bu2Dst0h_D0pi0_;
  }
  RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0pi0() {
    return *pdfBuPartial_misId_Bu2Dst0h_D0pi0_;
  }
  // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
  RooAbsReal &Bu2Dst0h_D0gamma_WN_sigma1Bu() {
    return *Bu2Dst0h_D0gamma_WN_sigma1Bu_;
  }
  RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma_WN() { return *pdfBu_Bu2Dst0h_D0gamma_WN_; }
  RooAbsReal &Bu2Dst0h_D0gamma_WN_sigmaBuPartial() {
    return *Bu2Dst0h_D0gamma_WN_sigmaBuPartial_;
  }
  RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma_WN() {
    return pdfBuPartial_Bu2Dst0h_D0gamma_WN_;
  }
  // -------------------- Mis-ID ------------------- //
  RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma_WN() {
    return *pdfDelta_misId_Bu2Dst0h_D0gamma_WN_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma_WN() {
    return *pdfBu_misId_Bu2Dst0h_D0gamma_WN_;
  }
  RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN() {
    return *pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN_;
  }
  // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
  RooAbsReal &Bu2Dst0h_D0pi0_WN_sigmaBu() { return *Bu2Dst0h_D0pi0_WN_sigmaBu_; }
  RooCBShape &pdfBu_Bu2Dst0h_D0pi0_WN() { return pdfBu_Bu2Dst0h_D0pi0_WN_; }
  RooAbsReal &Bu2Dst0h_D0pi0_WN_sigma1BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_sigma1BuPartial_;
  }
  RooAbsReal &Bu2Dst0h_D0pi0_WN_sigma2BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_sigma2BuPartial_;
  }
  RooAbsReal &Bu2Dst0h_D0pi0_WN_sigma3BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_sigma3BuPartial_;
  }
  RooAddPdf &pdfBuPartial_Bu2Dst0h_D0pi0_WN() {
    return pdfBuPartial_Bu2Dst0h_D0pi0_WN_;
  }
  // -------------------- Mis-ID ------------------- //
  RooDstD0BG &pdfDelta_misId_Bu2Dst0h_D0pi0_WN() {
    return pdfDelta_misId_Bu2Dst0h_D0pi0_WN_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0_WN() {
    return *pdfBu_misId_Bu2Dst0h_D0pi0_WN_;
  }
  RooCBShape &pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN() {
    return pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN_;
  }
  // -------------------- Bd2Dsth -------------------- //
  RooAbsReal &Bd2Dsth_sigma1Bu() { return *Bd2Dsth_sigma1Bu_; }
  RooFormulaVar &Bd2Dsth_sigma2Bu() { return Bd2Dsth_sigma2Bu_; }
  RooCBShape &pdf1Bu_Bd2Dsth() { return pdf1Bu_Bd2Dsth_; }
  RooCBShape &pdf2Bu_Bd2Dsth() { return pdf2Bu_Bd2Dsth_; }
  RooAbsPdf &pdfBu_Bd2Dsth() { return *pdfBu_Bd2Dsth_; }
  RooAbsReal &Bd2Dsth_sigma1BuPartial() { return *Bd2Dsth_sigma1BuPartial_; }
  RooFormulaVar &Bd2Dsth_sigma2BuPartial() { return Bd2Dsth_sigma2BuPartial_; }
  RooCBShape &pdf1BuPartial_Bd2Dsth() { return pdf1BuPartial_Bd2Dsth_; }
  RooCBShape &pdf2BuPartial_Bd2Dsth() { return pdf2BuPartial_Bd2Dsth_; }
  RooAddPdf &pdfBuPartial_Bd2Dsth() { return pdfBuPartial_Bd2Dsth_; }
  // -------------------- Mis-ID ------------------- //
  RooDstD0BG &pdfDelta_misId_Bd2Dsth() {
    return pdfDelta_misId_Bd2Dsth_;
  }
  RooAbsPdf &pdfBu_misId_Bd2Dsth() {
    return *pdfBu_misId_Bd2Dsth_;
  }
  RooCBShape &pdfBuPartial_misId_Bd2Dsth() {
    return pdfBuPartial_misId_Bd2Dsth_;
  }
  // -------------------- Bu2D0hst -------------------- //
  RooAbsReal &Bu2D0hst_sigma1Bu() { return *Bu2D0hst_sigma1Bu_; }
  RooFormulaVar &Bu2D0hst_sigma2Bu() { return Bu2D0hst_sigma2Bu_; }
  RooCBShape &pdf1Bu_Bu2D0hst() { return pdf1Bu_Bu2D0hst_; }
  RooGaussian &pdf2Bu_Bu2D0hst() { return pdf2Bu_Bu2D0hst_; }
  RooAbsPdf &pdfBu_Bu2D0hst() { return *pdfBu_Bu2D0hst_; }
  RooAbsReal &Bu2D0hst_sigmaBuPartial() { return *Bu2D0hst_sigmaBuPartial_; }
  RooGaussian &pdfBuPartial_Bu2D0hst() { return pdfBuPartial_Bu2D0hst_; }
  // -------------------- Mis-ID ------------------- //
  RooDstD0BG &pdfDelta_misId_Bu2D0hst() {
    return pdfDelta_misId_Bu2D0hst_;
  }
  RooAbsPdf &pdfBu_misId_Bu2D0hst() {
    return *pdfBu_misId_Bu2D0hst_;
  }
  RooCBShape &pdfBuPartial_misId_Bu2D0hst() {
    return pdfBuPartial_misId_Bu2D0hst_;
  }
  // -------------------- Bu2Dst0hst_D0gamma -------------------- //
  RooAbsReal &Bu2Dst0hst_D0gamma_sigma1Bu() {
    return *Bu2Dst0hst_D0gamma_sigma1Bu_;
  }
  RooFormulaVar &Bu2Dst0hst_D0gamma_sigma2Bu() {
    return Bu2Dst0hst_D0gamma_sigma2Bu_;
  }
  RooCBShape &pdf1Bu_Bu2Dst0hst_D0gamma() { return pdf1Bu_Bu2Dst0hst_D0gamma_; }
  RooCBShape &pdf2Bu_Bu2Dst0hst_D0gamma() { return pdf2Bu_Bu2Dst0hst_D0gamma_; }
  RooAddPdf &pdfBu_Bu2Dst0hst_D0gamma() { return pdfBu_Bu2Dst0hst_D0gamma_; }
  RooAbsReal &Bu2Dst0hst_D0gamma_sigmaBuPartial() {
    return *Bu2Dst0hst_D0gamma_sigmaBuPartial_;
  }
  RooGaussian &pdfBuPartial_Bu2Dst0hst_D0gamma() {
    return pdfBuPartial_Bu2Dst0hst_D0gamma_;
  }
  // -------------------- Mis-ID ------------------- //
  RooAddPdf &pdfDelta_misId_Bu2Dst0hst_D0gamma() {
    return pdfDelta_misId_Bu2Dst0hst_D0gamma_;
  }
  RooAddPdf &pdfBu_misId_Bu2Dst0hst_D0gamma() {
    return pdfBu_misId_Bu2Dst0hst_D0gamma_;
  }
  RooGaussian &pdfBuPartial_misId_Bu2Dst0hst_D0gamma() {
    return pdfBuPartial_misId_Bu2Dst0hst_D0gamma_;
  }
  // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
  RooAbsReal &Bu2Dst0hst_D0pi0_sigmaBu() { return *Bu2Dst0hst_D0pi0_sigmaBu_; }
  RooGaussian &pdfBu_Bu2Dst0hst_D0pi0() { return pdfBu_Bu2Dst0hst_D0pi0_; }
  RooAbsReal &Bu2Dst0hst_D0pi0_sigmaBuPartial() {
    return *Bu2Dst0hst_D0pi0_sigmaBuPartial_;
  }
  RooGaussian &pdfBuPartial_Bu2Dst0hst_D0pi0() {
    return pdfBuPartial_Bu2Dst0hst_D0pi0_;
  }
  // -------------------- Mis-ID ------------------- //
  RooAddPdf &pdfDelta_misId_Bu2Dst0hst_D0pi0() {
    return pdfDelta_misId_Bu2Dst0hst_D0pi0_;
  }
  RooCBShape &pdfBu_misId_Bu2Dst0hst_D0pi0() {
    return pdfBu_misId_Bu2Dst0hst_D0pi0_;
  }
  RooAddPdf &pdfBuPartial_misId_Bu2Dst0hst_D0pi0() {
    return pdfBuPartial_misId_Bu2Dst0hst_D0pi0_;
  }
  // -------------------- MIS-REC -------------------- //
  RooCruijff &pdfBu_MisRec() { return pdfBu_MisRec_; }
  RooCruijff &pdfBuPartial_MisRec() { return pdfBuPartial_MisRec_; }
  // -------------------- Mis-ID ------------------- //
  RooAbsPdf &pdfBu_misId_MisRec() {
    return *pdfBu_misId_MisRec_;
  }
  RooCruijff &pdfBuPartial_misId_MisRec() { return pdfBuPartial_misId_MisRec_; }
  // -------------------- Bu2D0h -------------------- //
  RooCruijff &pdfBu_Bu2D0h() { return pdfBu_Bu2D0h_; }
  RooCruijff &pdfBuPartial_Bu2D0h() { return pdfBuPartial_Bu2D0h_; }
  // -------------------- Mis-ID ------------------- //
  RooCruijff &pdfBu_misId_Bu2D0h() { return pdfBu_misId_Bu2D0h_; }
  RooCruijff &pdfBuPartial_misId_Bu2D0h() { return pdfBuPartial_misId_Bu2D0h_; }
  // -------------------- PART REC -------------------- //
  RooRealVar &PartRec_D0pi0_sigmaLBu() { return *PartRec_D0pi0_sigmaLBu_; }
  RooRealVar &PartRec_D0pi0_sigmaRBu() { return *PartRec_D0pi0_sigmaRBu_; }
  RooRealVar &PartRec_D0gamma_sigmaLBu() { return *PartRec_D0gamma_sigmaLBu_; }
  RooRealVar &PartRec_D0gamma_sigmaRBu() { return *PartRec_D0gamma_sigmaRBu_; }
  RooAbsPdf &pdfBu_PartRec() { return *pdfBu_PartRec_; }
  RooRealVar &PartRec_sigmaLBuPartial() { return *PartRec_sigmaLBuPartial_; }
  RooRealVar &PartRec_sigmaRBuPartial() { return *PartRec_sigmaRBuPartial_; }
  RooCruijff &pdfBuPartial_PartRec() { return pdfBuPartial_PartRec_; }
  // -------------------- Mis-ID ------------------- //
  RooCruijff &pdfBu_misId_PartRec() {
    return pdfBu_misId_PartRec_;
  }
  RooCruijff &pdfBuPartial_misId_PartRec() { return pdfBuPartial_misId_PartRec_; }
  // -------------------- Bs2Dst0Kpi -------------------- //
  RooAddPdf &pdfDelta_Bs2Dst0Kpi() { return pdfDelta_Bs2Dst0Kpi_; }
  RooAbsPdf &pdfBu_Bs2Dst0Kpi() { return *pdfBu_Bs2Dst0Kpi_; }
  RooCruijff &pdfBuPartial_Bs2Dst0Kpi() { return pdfBuPartial_Bs2Dst0Kpi_; }
  // -------------------- Bs2D0Kpi -------------------- //
  RooDstD0BG &pdfDelta_Bs2D0Kpi() { return pdfDelta_Bs2D0Kpi_; }
  RooAbsPdf &pdfBu_Bs2D0Kpi() { return *pdfBu_Bs2D0Kpi_; }
  RooCruijff &pdfBuPartial_Bs2D0Kpi() { return pdfBuPartial_Bs2D0Kpi_; }
  // -------------------- Correct ID BOX EFFs -------------------- //
  RooRealVar &buEffBu2Dst0h_D0gamma() {
    return *buEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &buEffBu2Dst0h_D0pi0() {
    return *buEffBu2Dst0h_D0pi0_;
  }
  RooRealVar &buEffBu2Dst0h_D0gamma_WN() {
    return *buEffBu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &buEffBu2Dst0h_D0pi0_WN() {
    return *buEffBu2Dst0h_D0pi0_WN_;
  }
  RooRealVar &buEffBd2Dsth() {
    return *buEffBd2Dsth_;
  }
  RooRealVar &buEffBu2D0hst() {
    return *buEffBu2D0hst_;
  }
  RooRealVar &buEffBu2Dst0hst_D0gamma() {
    return *buEffBu2Dst0hst_D0gamma_;
  }
  RooRealVar &buEffBu2Dst0hst_D0pi0() {
    return *buEffBu2Dst0hst_D0pi0_;
  }
  RooRealVar &deltaEffBu2Dst0h_D0gamma() {
    return *deltaEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaEffBu2Dst0h_D0pi0() {
    return *deltaEffBu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaEffBu2Dst0h_D0gamma_WN() {
    return *deltaEffBu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &deltaEffBu2Dst0h_D0pi0_WN() {
    return *deltaEffBu2Dst0h_D0pi0_WN_;
  }
  RooRealVar &deltaEffBd2Dsth() {
    return *deltaEffBd2Dsth_;
  }
  RooRealVar &deltaEffBu2D0hst() {
    return *deltaEffBu2D0hst_;
  }
  RooRealVar &deltaEffBu2Dst0hst_D0gamma() {
    return *deltaEffBu2Dst0hst_D0gamma_;
  }
  RooRealVar &deltaEffBu2Dst0hst_D0pi0() {
    return *deltaEffBu2Dst0hst_D0pi0_;
  }
  RooRealVar &buPartialEffBu2Dst0h_D0gamma() {
    return *buPartialEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &buPartialEffBu2Dst0h_D0pi0() {
    return *buPartialEffBu2Dst0h_D0pi0_;
  }
  RooRealVar &buPartialEffBu2Dst0h_D0gamma_WN() {
    return *buPartialEffBu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &buPartialEffBu2Dst0h_D0pi0_WN() {
    return *buPartialEffBu2Dst0h_D0pi0_WN_;
  }
  RooRealVar &buPartialEffBd2Dsth() {
    return *buPartialEffBd2Dsth_;
  }
  RooRealVar &buPartialEffBu2D0hst() {
    return *buPartialEffBu2D0hst_;
  }
  RooRealVar &buPartialEffBu2Dst0hst_D0gamma() {
    return *buPartialEffBu2Dst0hst_D0gamma_;
  }
  RooRealVar &buPartialEffBu2Dst0hst_D0pi0() {
    return *buPartialEffBu2Dst0hst_D0pi0_;
  }
  // -------------------- Mis-ID BoxEffs ------------------- //
  RooRealVar &buEffMisId_Bu2Dst0h_D0gamma() {
    return *buEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &buEffMisId_Bu2Dst0h_D0pi0() {
    return *buEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &buEffMisId_Bu2Dst0h_D0gamma_WN() {
    return *buEffMisId_Bu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &buEffMisId_Bu2Dst0h_D0pi0_WN() {
    return *buEffMisId_Bu2Dst0h_D0pi0_WN_;
  }
  RooRealVar &buEffMisId_Bd2Dsth() {
    return *buEffMisId_Bd2Dsth_;
  }
  RooRealVar &buEffMisId_Bu2D0hst() {
    return *buEffMisId_Bu2D0hst_;
  }
  RooRealVar &buEffMisId_Bu2Dst0hst_D0gamma() {
    return *buEffMisId_Bu2Dst0hst_D0gamma_;
  }
  RooRealVar &buEffMisId_Bu2Dst0hst_D0pi0() {
    return *buEffMisId_Bu2Dst0hst_D0pi0_;
  }
  RooRealVar &deltaEffMisId_Bu2Dst0h_D0gamma() {
    return *deltaEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaEffMisId_Bu2Dst0h_D0pi0() {
    return *deltaEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaEffMisId_Bu2Dst0h_D0gamma_WN() {
    return *deltaEffMisId_Bu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &deltaEffMisId_Bu2Dst0h_D0pi0_WN() {
    return *deltaEffMisId_Bu2Dst0h_D0pi0_WN_;
  }
  RooRealVar &deltaEffMisId_Bd2Dsth() {
    return *deltaEffMisId_Bd2Dsth_;
  }
  RooRealVar &deltaEffMisId_Bu2D0hst() {
    return *deltaEffMisId_Bu2D0hst_;
  }
  RooRealVar &deltaEffMisId_Bu2Dst0hst_D0gamma() {
    return *deltaEffMisId_Bu2Dst0hst_D0gamma_;
  }
  RooRealVar &deltaEffMisId_Bu2Dst0hst_D0pi0() {
    return *deltaEffMisId_Bu2Dst0hst_D0pi0_;
  }
  RooRealVar &buPartialEffMisId_Bu2Dst0h_D0gamma() {
    return *buPartialEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &buPartialEffMisId_Bu2Dst0h_D0pi0() {
    return *buPartialEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &buPartialEffMisId_Bu2Dst0h_D0gamma_WN() {
    return *buPartialEffMisId_Bu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &buPartialEffMisId_Bu2Dst0h_D0pi0_WN() {
    return *buPartialEffMisId_Bu2Dst0h_D0pi0_WN_;
  }
  RooRealVar &buPartialEffMisId_Bd2Dsth() {
    return *buPartialEffMisId_Bd2Dsth_;
  }
  RooRealVar &buPartialEffMisId_Bu2D0hst() {
    return *buPartialEffMisId_Bu2D0hst_;
  }
  RooRealVar &buPartialEffMisId_Bu2Dst0hst_D0gamma() {
    return *buPartialEffMisId_Bu2Dst0hst_D0gamma_;
  }
  RooRealVar &buPartialEffMisId_Bu2Dst0hst_D0pi0() {
    return *buPartialEffMisId_Bu2Dst0hst_D0pi0_;
  }
  // -------------------- Mis-ID BoxEffs ------------------- //
  RooRealVar &buDeltaCutEffMisId_Bu2Dst0h_D0gamma() {
    return *buDeltaCutEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &buDeltaCutEffMisId_Bu2Dst0h_D0pi0() {
    return *buDeltaCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &buDeltaCutEffMisId_MisRec() {
    return *buDeltaCutEffMisId_MisRec_;
  }
  RooRealVar &buDeltaCutEffMisId_Bu2D0h() {
    return *buDeltaCutEffMisId_Bu2D0h_;
  }
  RooRealVar &buDeltaCutEffMisId_PartRec() {
    return *buDeltaCutEffMisId_PartRec_;
  }
  RooRealVar &deltaCutEffMisId_Bu2Dst0h_D0gamma() {
    return *deltaCutEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaCutEffMisId_Bu2Dst0h_D0pi0() {
    return *deltaCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaCutEffMisId_MisRec() { return *deltaCutEffMisId_MisRec_; }
  RooRealVar &deltaCutEffMisId_Bu2D0h() { return *deltaCutEffMisId_Bu2D0h_; }
  RooRealVar &deltaCutEffMisId_PartRec() { return *deltaCutEffMisId_PartRec_; }
  RooRealVar &deltaPartialCutEffMisId_Bu2Dst0h_D0pi0() {
    return *deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaPartialCutEffMisId_MisRec() {
    return *deltaPartialCutEffMisId_MisRec_;
  }
  RooRealVar &deltaPartialCutEffMisId_Bu2D0h() {
    return *deltaPartialCutEffMisId_Bu2D0h_;
  }
  RooRealVar &deltaPartialCutEffMisId_PartRec() {
    return *deltaPartialCutEffMisId_PartRec_;
  }

  // -------------------- Bs BoxEffs ------------------- //
  RooRealVar &buDeltaCutEffBs2Dst0Kpi() { return *buDeltaCutEffBs2Dst0Kpi_; }
  RooRealVar &buDeltaCutEffBs2D0Kpi() { return *buDeltaCutEffBs2D0Kpi_; }
  RooRealVar &deltaCutEffBs2Dst0Kpi() { return *deltaCutEffBs2Dst0Kpi_; }
  RooRealVar &deltaCutEffBs2D0Kpi() { return *deltaCutEffBs2D0Kpi_; }
  RooRealVar &deltaPartialCutEffBs2Dst0Kpi() {
    return *deltaPartialCutEffBs2Dst0Kpi_;
  }
  RooRealVar &deltaPartialCutEffBs2D0Kpi() {
    return *deltaPartialCutEffBs2D0Kpi_;
  }

  // -------------------- MC Efficiencies -------------------- //
  RooRealVar &mcEff_Bu2Dst0h_D0gamma() { return *mcEff_Bu2Dst0h_D0gamma_; }
  RooRealVar &mcEff_Bu2Dst0h_D0pi0() { return *mcEff_Bu2Dst0h_D0pi0_; }
  RooRealVar &mcEff_Bu2Dst0h_D0gamma_WN() { return *mcEff_Bu2Dst0h_D0gamma_WN_; }
  RooRealVar &mcEff_Bu2Dst0h_D0pi0_WN() { return *mcEff_Bu2Dst0h_D0pi0_WN_; }
  RooRealVar &mcEff_Bd2Dsth() { return *mcEff_Bd2Dsth_; }
  RooRealVar &mcEff_Bu2D0hst() { return *mcEff_Bu2D0hst_; }
  RooRealVar &mcEff_Bu2Dst0hst_D0gamma() { return *mcEff_Bu2Dst0hst_D0gamma_; }
  RooRealVar &mcEff_Bu2Dst0hst_D0pi0() { return *mcEff_Bu2Dst0hst_D0pi0_; }
  RooRealVar &mcEff_MisRec() { return *mcEff_MisRec_; }
  RooRealVar &mcEff_Bu2D0h() { return *mcEff_Bu2D0h_; }
  RooRealVar &mcEff_PartRec() { return *mcEff_PartRec_; }
  RooRealVar &mcEff_Bs2Dst0Kpi() { return *mcEff_Bs2Dst0Kpi_; }
  RooRealVar &mcEff_Bs2D0Kpi() { return *mcEff_Bs2D0Kpi_; }

  // -------------------- CP Observables -------------------- //
  RooAbsReal &A_CP_Bu2Dst0h_D0gamma_Blind() {
    return *A_CP_Bu2Dst0h_D0gamma_Blind_;
  }
  RooAbsReal &A_CP_Bu2Dst0h_D0pi0_Blind() {
    return *A_CP_Bu2Dst0h_D0pi0_Blind_;
  }
  RooAbsReal &A_CP_Bu2Dst0h_D0gamma_WN_Blind() {
    return *A_CP_Bu2Dst0h_D0gamma_WN_Blind_;
  }
  RooAbsReal &A_CP_Bu2Dst0h_D0pi0_WN_Blind() {
    return *A_CP_Bu2Dst0h_D0pi0_WN_Blind_;
  }
  RooAbsReal &A_CP_Bu2Dst0h_D0gamma() { return *A_CP_Bu2Dst0h_D0gamma_; }
  RooAbsReal &A_CP_Bu2Dst0h_D0pi0() { return *A_CP_Bu2Dst0h_D0pi0_; }
  RooAbsReal &A_CP_Bu2Dst0h_D0gamma_WN() { return *A_CP_Bu2Dst0h_D0gamma_WN_; }
  RooAbsReal &A_CP_Bu2Dst0h_D0pi0_WN() { return *A_CP_Bu2Dst0h_D0pi0_WN_; }
  RooAbsReal &A_CP_Bd2Dsth() { return *A_CP_Bd2Dsth_; }
  RooAbsReal &A_CP_Bu2D0hst() { return *A_CP_Bu2D0hst_; }
  RooAbsReal &A_CP_Bu2Dst0hst_D0gamma() { return *A_CP_Bu2Dst0hst_D0gamma_; }
  RooAbsReal &A_CP_Bu2Dst0hst_D0pi0() { return *A_CP_Bu2Dst0hst_D0pi0_; }
  RooFormulaVar &R_ADS_Bu2Dst0h_D0gamma() { return *R_ADS_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &R_ADS_Bu2Dst0h_D0pi0() { return *R_ADS_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &R_ADS_Bu2Dst0h_D0gamma_WN() { return *R_ADS_Bu2Dst0h_D0gamma_WN_; }
  RooFormulaVar &R_ADS_Bu2Dst0h_D0pi0_WN() { return *R_ADS_Bu2Dst0h_D0pi0_WN_; }
  RooAbsReal &R_ADS_Bd2Dsth() { return *R_ADS_Bd2Dsth_; }
  RooAbsReal &R_ADS_Bu2D0hst() { return *R_ADS_Bu2D0hst_; }
  RooAbsReal &R_ADS_Bu2Dst0hst_D0gamma() { return *R_ADS_Bu2Dst0hst_D0gamma_; }
  RooAbsReal &R_ADS_Bu2Dst0hst_D0pi0() { return *R_ADS_Bu2Dst0hst_D0pi0_; }

 private:
  int uniqueId_;
  // -------------------- PDF SHAPES -------------------- //
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0gamma_sigmaBu_;
  RooCBShape pdf1Bu_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0h_D0gamma_;
  RooGaussian pdfBuPartial_Bu2Dst0h_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_meanDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_sigmaDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_a2Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_a1Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_n2Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_n1Delta_;
  RooCBShape pdf1Delta_misId_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Delta_misId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_fracPdf1Delta_;
  std::unique_ptr<RooAbsPdf> pdfDelta_misId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_meanBu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_sigmaBu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_a2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_n2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_n1Bu_;
  RooCBShape pdf1Bu_misId_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Bu_misId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0gamma_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigmaDelta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0pi0_;
  RooAddPdf pdfDelta_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigmaBu_;
  RooCBShape pdf1Bu_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigma1BuPartial_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigma2BuPartial_;
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigma3BuPartial_;
  RooCBShape pdf1BuPartial_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2BuPartial_Bu2Dst0h_D0pi0_;
  RooGaussian pdf3BuPartial_Bu2Dst0h_D0pi0_;
  RooAddPdf pdfBuPartial_Bu2Dst0h_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_meanDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_sigmaDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_a2Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_a1Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_n2Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_n1Delta_;
  RooCBShape pdf1Delta_misId_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Delta_misId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_fracPdf1Delta_;
  std::unique_ptr<RooAbsPdf> pdfDelta_misId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_mean1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_mean2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_sigma1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_sigma2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_a2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_n2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_n1Bu_;
  std::unique_ptr<RooAbsPdf> pdf1Bu_misId_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Bu_misId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_mean1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_mean2BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_sigma1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_sigma2BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_a2BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_a1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_n2BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_n1BuPartial_;
  RooCBShape pdf1BuPartial_misId_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2BuPartial_misId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_;
  std::unique_ptr<RooAbsPdf> pdfBuPartial_misId_Bu2Dst0h_D0pi0_;
  // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0gamma_WN_sigma1Bu_;
  RooFormulaVar Bu2Dst0h_D0gamma_WN_sigma2Bu_;
  RooCBShape pdf1Bu_Bu2Dst0h_D0gamma_WN_;
  RooGaussian pdf2Bu_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0gamma_WN_sigmaBuPartial_;
  RooGaussian pdfBuPartial_Bu2Dst0h_D0gamma_WN_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_meanBu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_sigmaBu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_n1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_thresholdDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_aDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_bDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_cDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_meanDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_sigmaDelta_;
  std::unique_ptr<RooAbsPdf> pdfDelta_misId_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_meanBuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_sigmaBuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_a1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_WN_n1BuPartial_;
  std::unique_ptr<RooAbsPdf> pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN_;
  // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0pi0_WN_sigmaBu_;
  RooCBShape pdfBu_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0pi0_WN_sigma1BuPartial_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0pi0_WN_sigma2BuPartial_;
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0pi0_WN_sigma3BuPartial_;
  RooCBShape pdf1BuPartial_Bu2Dst0h_D0pi0_WN_;
  RooCBShape pdf2BuPartial_Bu2Dst0h_D0pi0_WN_;
  RooGaussian pdf3BuPartial_Bu2Dst0h_D0pi0_WN_;
  RooAddPdf pdfBuPartial_Bu2Dst0h_D0pi0_WN_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_mean1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_mean2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_mean3Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_sigma1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_sigma2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_sigma3Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_n1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_a2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_n2Bu_;
  RooCBShape pdf1Bu_misId_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooAbsPdf> pdf2Bu_misId_Bu2Dst0h_D0pi0_WN_;
  RooGaussian pdf3Bu_misId_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_fracPdf2Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_thresholdDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_aDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_bDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_cDelta_;
  RooDstD0BG pdfDelta_misId_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_meanBuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_sigmaBuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_a1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_WN_n1BuPartial_;
  RooCBShape pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN_;
  // -------------------- Bd2Dsth -------------------- //
  std::shared_ptr<RooAbsReal> Bd2Dsth_sigma1Bu_;
  RooFormulaVar Bd2Dsth_sigma2Bu_;
  RooCBShape pdf1Bu_Bd2Dsth_;
  RooCBShape pdf2Bu_Bd2Dsth_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> Bd2Dsth_sigma1BuPartial_;
  RooFormulaVar Bd2Dsth_sigma2BuPartial_;
  RooCBShape pdf1BuPartial_Bd2Dsth_;
  RooCBShape pdf2BuPartial_Bd2Dsth_;
  RooAddPdf pdfBuPartial_Bd2Dsth_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_meanBu_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_sigmaBu_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_n1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bd2Dsth_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_thresholdDelta_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_aDelta_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_bDelta_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_cDelta_;
  RooDstD0BG pdfDelta_misId_Bd2Dsth_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_meanBuPartial_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_sigmaBuPartial_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_a1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bd2Dsth_n1BuPartial_;
  RooCBShape pdfBuPartial_misId_Bd2Dsth_;
  // -------------------- Bu2D0hst -------------------- //
  std::shared_ptr<RooAbsReal> Bu2D0hst_sigma1Bu_;
  RooFormulaVar Bu2D0hst_sigma2Bu_;
  RooCBShape pdf1Bu_Bu2D0hst_;
  RooGaussian pdf2Bu_Bu2D0hst_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> Bu2D0hst_sigmaBuPartial_;
  RooGaussian pdfBuPartial_Bu2D0hst_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_meanBu_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_sigmaBu_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_n1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2D0hst_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_thresholdDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_aDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_bDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_cDelta_;
  RooDstD0BG pdfDelta_misId_Bu2D0hst_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_meanBuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_sigmaBuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_a1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2D0hst_n1BuPartial_;
  RooCBShape pdfBuPartial_misId_Bu2D0hst_;
  // -------------------- Bu2Dst0hst_D0gamma -------------------- //
  std::shared_ptr<RooAbsReal> Bu2Dst0hst_D0gamma_sigma1Bu_;
  RooFormulaVar Bu2Dst0hst_D0gamma_sigma2Bu_;
  RooCBShape pdf1Bu_Bu2Dst0hst_D0gamma_;
  RooCBShape pdf2Bu_Bu2Dst0hst_D0gamma_;
  RooAddPdf pdfBu_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooAbsReal> Bu2Dst0hst_D0gamma_sigmaBuPartial_;
  RooGaussian pdfBuPartial_Bu2Dst0hst_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_meanOffset21Bu_;
  RooFormulaVar misId_Bu2Dst0hst_D0gamma_mean2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_sigma1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_sigmaRatio21Bu_;
  RooFormulaVar misId_Bu2Dst0hst_D0gamma_sigma2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_n1Bu_;
  RooCBShape pdf1Bu_misId_Bu2Dst0hst_D0gamma_;
  RooGaussian pdf2Bu_misId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  RooAddPdf pdfBu_misId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_meanDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_sigmaDelta_;
  RooCBShape pdf1Delta_misId_Bu2Dst0hst_D0gamma_;
  RooCBShape pdf2Delta_misId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_fracPdf1Delta_;
  RooAddPdf pdfPeakDelta_misId_Bu2Dst0hst_D0gamma_;
  RooDstD0BG pdfFlatDelta_misId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_fracPdfPeakDelta_;
  RooAddPdf pdfDelta_misId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_meanBuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_sigmaBuPartial_;
  RooGaussian pdfBuPartial_misId_Bu2Dst0hst_D0gamma_;
  // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
  std::shared_ptr<RooAbsReal> Bu2Dst0hst_D0pi0_sigmaBu_;
  RooGaussian pdfBu_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooAbsReal> Bu2Dst0hst_D0pi0_sigmaBuPartial_;
  RooGaussian pdfBuPartial_Bu2Dst0hst_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_meanBu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_sigmaBu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_n1Bu_;
  RooCBShape pdfBu_misId_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_mean1Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_mean2Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_sigma1Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_sigma2Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_a1Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_n1Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_a2Delta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_n2Delta_;
  RooCBShape pdf1Delta_misId_Bu2Dst0hst_D0pi0_;
  RooCBShape pdf2Delta_misId_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_fracPdf1Delta_;
  RooAddPdf pdfPeakDelta_misId_Bu2Dst0hst_D0pi0_;
  RooDstD0BG pdfFlatDelta_misId_Bu2Dst0hst_D0pi0_;
  RooAddPdf pdfDelta_misId_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_mean1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_meanOffset21BuPartial_;
  RooFormulaVar misId_Bu2Dst0hst_D0pi0_mean2BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_sigma1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_sigmaRatio21BuPartial_;
  RooFormulaVar misId_Bu2Dst0hst_D0pi0_sigma2BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_a1BuPartial_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_n1BuPartial_;
  RooCBShape pdf1BuPartial_misId_Bu2Dst0hst_D0pi0_;
  RooGaussian pdf2BuPartial_misId_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0pi0_fracPdf1BuPartial_;
  RooAddPdf pdfBuPartial_misId_Bu2Dst0hst_D0pi0_;
  // -------------------- MIS-REC -------------------- //
  std::shared_ptr<RooRealVar> MisRec_sigmaLBu_;
  std::shared_ptr<RooRealVar> MisRec_sigmaRBu_;
  RooCruijff pdfBu_MisRec_;
  std::shared_ptr<RooRealVar> MisRec_sigmaLBuPartial_;
  std::shared_ptr<RooRealVar> MisRec_sigmaRBuPartial_;
  RooCruijff pdfBuPartial_MisRec_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_MisRec_mean1Bu_;
  std::shared_ptr<RooRealVar> misId_MisRec_mean2Bu_;
  std::shared_ptr<RooRealVar> misId_MisRec_sigma1Bu_;
  std::shared_ptr<RooRealVar> misId_MisRec_sigma2Bu_;
  std::shared_ptr<RooRealVar> misId_MisRec_a2Bu_;
  std::shared_ptr<RooRealVar> misId_MisRec_a1Bu_;
  std::shared_ptr<RooRealVar> misId_MisRec_n2Bu_;
  std::shared_ptr<RooRealVar> misId_MisRec_n1Bu_;
  RooCBShape pdf1Bu_misId_MisRec_;
  RooCBShape pdf2Bu_misId_MisRec_;
  std::shared_ptr<RooRealVar> misId_MisRec_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_MisRec_;
  std::shared_ptr<RooRealVar> misId_MisRec_meanBuPartial_;
  std::shared_ptr<RooRealVar> misId_MisRec_sigmaLBuPartial_;
  std::shared_ptr<RooRealVar> misId_MisRec_sigmaRBuPartial_;
  std::shared_ptr<RooRealVar> misId_MisRec_aLBuPartial_;
  std::shared_ptr<RooRealVar> misId_MisRec_aRBuPartial_;
  RooCruijff pdfBuPartial_misId_MisRec_;
  // -------------------- Bu2D0h -------------------- //
  RooRealVar Bu2D0h_sigmaLBu_;
  RooRealVar Bu2D0h_sigmaRBu_;
  RooCruijff pdfBu_Bu2D0h_;
  RooRealVar Bu2D0h_sigmaLBuPartial_;
  RooRealVar Bu2D0h_sigmaRBuPartial_;
  RooCruijff pdfBuPartial_Bu2D0h_;
  // -------------------- Mis-ID ------------------- //
  RooRealVar misId_Bu2D0h_meanBu_;
  RooRealVar misId_Bu2D0h_sigmaLBu_;
  RooRealVar misId_Bu2D0h_sigmaRBu_;
  RooRealVar misId_Bu2D0h_aLBu_;
  RooRealVar misId_Bu2D0h_aRBu_;
  RooCruijff pdfBu_misId_Bu2D0h_;
  RooRealVar misId_Bu2D0h_meanBuPartial_;
  RooRealVar misId_Bu2D0h_sigmaLBuPartial_;
  RooRealVar misId_Bu2D0h_sigmaRBuPartial_;
  RooRealVar misId_Bu2D0h_aLBuPartial_;
  RooRealVar misId_Bu2D0h_aRBuPartial_;
  RooCruijff pdfBuPartial_misId_Bu2D0h_;
  // -------------------- PART REC -------------------- //
  std::shared_ptr<RooRealVar> PartRec_D0pi0_sigmaLBu_;
  std::shared_ptr<RooRealVar> PartRec_D0pi0_sigmaRBu_;
  RooCruijff pdfBu_PartRec_D0pi0_;
  std::shared_ptr<RooRealVar> PartRec_D0gamma_sigmaLBu_;
  std::shared_ptr<RooRealVar> PartRec_D0gamma_sigmaRBu_;
  RooCruijff pdfBu_PartRec_D0gamma_;
  std::shared_ptr<RooRealVar> PartRec_sigmaLBuPartial_;
  std::shared_ptr<RooRealVar> PartRec_sigmaRBuPartial_;
  RooCruijff pdfBuPartial_PartRec_;
  std::unique_ptr<RooAbsPdf> pdfBu_PartRec_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_PartRec_meanBu_;
  std::shared_ptr<RooRealVar> misId_PartRec_sigmaLBu_;
  std::shared_ptr<RooRealVar> misId_PartRec_sigmaRBu_;
  std::shared_ptr<RooRealVar> misId_PartRec_aLBu_;
  std::shared_ptr<RooRealVar> misId_PartRec_aRBu_;
  RooCruijff pdfBu_misId_PartRec_;
  std::shared_ptr<RooRealVar> misId_PartRec_meanBuPartial_;
  std::shared_ptr<RooRealVar> misId_PartRec_sigmaLBuPartial_;
  std::shared_ptr<RooRealVar> misId_PartRec_sigmaRBuPartial_;
  std::shared_ptr<RooRealVar> misId_PartRec_aLBuPartial_;
  std::shared_ptr<RooRealVar> misId_PartRec_aRBuPartial_;
  RooCruijff pdfBuPartial_misId_PartRec_;
  // -------------------- Bs2Dst0Kpi -------------------- //
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_aDelta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_bDelta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_cDelta_;
  RooDstD0BG pdfFlatDelta_Bs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_meanDeltaGamma_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_sigmaDeltaGamma_;
  RooCBShape pdfPeak1DeltaGamma_Bs2Dst0Kpi_;
  RooCBShape pdfPeak2DeltaGamma_Bs2Dst0Kpi_;
  RooAddPdf pdfPeakDeltaGamma_Bs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_fracPeakDeltaGamma_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_meanDeltaPi0_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_sigmaDeltaPi0_;
  RooCBShape pdfPeak1DeltaPi0_Bs2Dst0Kpi_;
  RooCBShape pdfPeak2DeltaPi0_Bs2Dst0Kpi_;
  RooAddPdf pdfPeakDeltaPi0_Bs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_fracPeakDeltaPi0_;
  RooAddPdf pdfDelta_Bs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_mean1Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_mean2Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_sigma1Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_sigma2Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_aLBu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_aRBu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_a1Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_n1Bu_;
  RooCBShape pdf1Bu_Bs2Dst0Kpi_;
  RooGaussian pdf2Bu_Bs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_sigmaLBuPartial_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_sigmaRBuPartial_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_aLBuPartial_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kpi_aRBuPartial_;
  RooCruijff pdfBuPartial_Bs2Dst0Kpi_;
  // -------------------- Bs2D0Kpi -------------------- //
  std::shared_ptr<RooRealVar> Bs2D0Kpi_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_aDelta_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_bDelta_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_cDelta_;
  RooDstD0BG pdfDelta_Bs2D0Kpi_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_mean1Bu_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_mean2Bu_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_sigma1Bu_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_sigma2Bu_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_a1Bu_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_n1Bu_;
  RooCBShape pdf1Bu_Bs2D0Kpi_;
  RooGaussian pdf2Bu_Bs2D0Kpi_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bs2D0Kpi_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_sigmaLBuPartial_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_sigmaRBuPartial_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_aLBuPartial_;
  std::shared_ptr<RooRealVar> Bs2D0Kpi_aRBuPartial_;
  RooCruijff pdfBuPartial_Bs2D0Kpi_;
  // -------------------- Correct ID BOX EFFs -------------------- //
  std::shared_ptr<RooRealVar> buEffBu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> buEffBu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> buEffBu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> buEffBu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> buEffBd2Dsth_;
  std::shared_ptr<RooRealVar> buEffBu2D0hst_;
  std::shared_ptr<RooRealVar> buEffBu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> buEffBu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> deltaEffBd2Dsth_;
  std::shared_ptr<RooRealVar> deltaEffBu2D0hst_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> buPartialEffBd2Dsth_;
  std::shared_ptr<RooRealVar> buPartialEffBu2D0hst_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0hst_D0pi0_;
  // -------------------- Mis-ID BoxEffs ------------------- //
  std::shared_ptr<RooRealVar> buEffMisId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> buEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> buEffMisId_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> buEffMisId_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> buEffMisId_Bd2Dsth_;
  std::shared_ptr<RooRealVar> buEffMisId_Bu2D0hst_;
  std::shared_ptr<RooRealVar> buEffMisId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> buEffMisId_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> deltaEffMisId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> deltaEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> deltaEffMisId_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> deltaEffMisId_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> deltaEffMisId_Bd2Dsth_;
  std::shared_ptr<RooRealVar> deltaEffMisId_Bu2D0hst_;
  std::shared_ptr<RooRealVar> deltaEffMisId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> deltaEffMisId_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> buPartialEffMisId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> buPartialEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> buPartialEffMisId_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> buPartialEffMisId_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> buPartialEffMisId_Bd2Dsth_;
  std::shared_ptr<RooRealVar> buPartialEffMisId_Bu2D0hst_;
  std::shared_ptr<RooRealVar> buPartialEffMisId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> buPartialEffMisId_Bu2Dst0hst_D0pi0_;

  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_MisRec_;
  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_Bu2D0h_;
  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_PartRec_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_MisRec_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_Bu2D0h_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_PartRec_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffMisId_MisRec_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffMisId_Bu2D0h_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffMisId_PartRec_;
  // -------------------- Bs BoxEffs ------------------- //
  std::shared_ptr<RooRealVar> buDeltaCutEffBs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> deltaCutEffBs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffBs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> buDeltaCutEffBs2D0Kpi_;
  std::shared_ptr<RooRealVar> deltaCutEffBs2D0Kpi_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffBs2D0Kpi_;
  // -------------------- MC Efficiencies -------------------- //
  std::shared_ptr<RooRealVar> mcEff_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> mcEff_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> mcEff_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> mcEff_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> mcEff_Bd2Dsth_;
  std::shared_ptr<RooRealVar> mcEff_Bu2D0hst_;
  std::shared_ptr<RooRealVar> mcEff_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> mcEff_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> mcEff_MisRec_;
  std::shared_ptr<RooRealVar> mcEff_Bu2D0h_;
  std::shared_ptr<RooRealVar> mcEff_PartRec_;
  std::shared_ptr<RooRealVar> mcEff_Bs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> mcEff_Bs2D0Kpi_;
  // -------------------- CP Observables -------------------- //
  std::shared_ptr<RooRealVar> A_CP_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_CP_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooRealVar> A_CP_Bu2Dst0h_D0gamma_WN_Blind_;
  std::shared_ptr<RooRealVar> A_CP_Bu2Dst0h_D0pi0_WN_Blind_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> A_CP_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> R_ADS_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> R_ADS_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> R_ADS_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooAbsReal> R_ADS_Bu2Dst0hst_D0pi0_;
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
