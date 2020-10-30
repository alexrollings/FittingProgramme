#pragma once
#include "Configuration.h"
#include "Efficiencies.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "BachelorChargeVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooCruijff.h"
#include "RooGaussian.h"
#include "RooFormulaVar.h"
#include "RooProdPdf.h"

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
  RooAbsReal &Bu2Dst0h_D0gamma_sigmaDelta() { return *Bu2Dst0h_D0gamma_sigmaDelta_; }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma() { return pdfDelta_Bu2Dst0h_D0gamma_; }
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
  RooAbsReal &Bu2Dst0h_D0pi0_sigma1Bu() { return *Bu2Dst0h_D0pi0_sigma1Bu_; }
  RooFormulaVar &Bu2Dst0h_D0pi0_sigma2Bu() { return Bu2Dst0h_D0pi0_sigma2Bu_; }
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
  RooDstD0BG &pdfDelta_Bu2Dst0h_D0pi0_WN() {
    return pdfDelta_Bu2Dst0h_D0pi0_WN_;
  }
  RooAbsReal &Bu2Dst0h_D0pi0_WN_sigma1Bu() {
    return *Bu2Dst0h_D0pi0_WN_sigma1Bu_;
  }
  RooAbsReal &Bu2Dst0h_D0pi0_WN_sigma2Bu() {
    return *Bu2Dst0h_D0pi0_WN_sigma2Bu_;
  }
  RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0_WN() {
    return *pdfBu_Bu2Dst0h_D0pi0_WN_;
  }
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
  std::shared_ptr<RooAbsPdf> &pdfBu_Bu2D0hst_GetPointer() {
    return pdfBu_Bu2D0hst_;
  }
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
  RooAbsReal &Bu2Dst0hst_D0gamma_sigmaBuPartial() {
    return *Bu2Dst0hst_D0gamma_sigmaBuPartial_;
  }
  RooGaussian &pdfBuPartial_Bu2Dst0hst_D0gamma() {
    return pdfBuPartial_Bu2Dst0hst_D0gamma_;
  }
  // -------------------- Mis-ID ------------------- //
  RooAbsPdf &pdfDelta_misId_Bu2Dst0hst_D0gamma() {
    return *pdfDelta_misId_Bu2Dst0hst_D0gamma_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0hst_D0gamma() {
    return *pdfBu_misId_Bu2Dst0hst_D0gamma_;
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
  // -------------------- Bs2Dst0Kpi -------------------- //
  RooAddPdf &pdfDelta_Bs2Dst0Kpi() {
    return pdfDelta_Bs2Dst0Kpi_;
  }
  // -------------------- Correct ID BOX EFFs -------------------- //
  RooRealVar &orEffBu2Dst0h_D0gamma() {
    return *orEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &orEffBu2Dst0h_D0pi0() {
    return *orEffBu2Dst0h_D0pi0_;
  }
  RooRealVar &orEffBu2Dst0h_D0gamma_WN() {
    return *orEffBu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &orEffBu2Dst0h_D0pi0_WN() {
    return *orEffBu2Dst0h_D0pi0_WN_;
  }
  RooRealVar &orEffBd2Dsth() {
    return *orEffBd2Dsth_;
  }
  RooRealVar &orEffBu2D0hst() {
    return *orEffBu2D0hst_;
  }
  RooRealVar &orEffBu2Dst0hst_D0gamma() {
    return *orEffBu2Dst0hst_D0gamma_;
  }
  RooRealVar &orEffBu2Dst0hst_D0pi0() {
    return *orEffBu2Dst0hst_D0pi0_;
  }
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
  RooRealVar &orEffMisId_Bu2Dst0h_D0gamma() {
    return *orEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &orEffMisId_Bu2Dst0h_D0pi0() {
    return *orEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &orEffMisId_Bu2Dst0h_D0gamma_WN() {
    return *orEffMisId_Bu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &orEffMisId_Bu2Dst0h_D0pi0_WN() {
    return *orEffMisId_Bu2Dst0h_D0pi0_WN_;
  }
  RooRealVar &orEffMisId_Bd2Dsth() {
    return *orEffMisId_Bd2Dsth_;
  }
  RooRealVar &orEffMisId_Bu2D0hst() {
    return *orEffMisId_Bu2D0hst_;
  }
  RooRealVar &orEffMisId_Bu2Dst0hst_D0gamma() {
    return *orEffMisId_Bu2Dst0hst_D0gamma_;
  }
  RooRealVar &orEffMisId_Bu2Dst0hst_D0pi0() {
    return *orEffMisId_Bu2Dst0hst_D0pi0_;
  }
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

  // -------------------- MC Efficiencies -------------------- //
  RooRealVar &mcEff_Bu2Dst0h_D0gamma() { return *mcEff_Bu2Dst0h_D0gamma_; }
  RooRealVar &mcEff_Bu2Dst0h_D0pi0() { return *mcEff_Bu2Dst0h_D0pi0_; }
  RooRealVar &mcEff_Bu2Dst0h_D0gamma_WN() { return *mcEff_Bu2Dst0h_D0gamma_WN_; }
  RooRealVar &mcEff_Bu2Dst0h_D0pi0_WN() { return *mcEff_Bu2Dst0h_D0pi0_WN_; }
  RooRealVar &mcEff_Bd2Dsth() { return *mcEff_Bd2Dsth_; }
  RooRealVar &mcEff_Bu2D0hst() { return *mcEff_Bu2D0hst_; }
  RooRealVar &mcEff_Bu2Dst0hst_D0gamma() { return *mcEff_Bu2Dst0hst_D0gamma_; }
  RooRealVar &mcEff_Bu2Dst0hst_D0pi0() { return *mcEff_Bu2Dst0hst_D0pi0_; }

  // -------------------- MC misId Efficiencies -------------------- //
  RooRealVar &mcEffMisId_Bu2Dst0h_D0gamma() { return *mcEffMisId_Bu2Dst0h_D0gamma_; }
  RooRealVar &mcEffMisId_Bu2Dst0h_D0pi0() { return *mcEffMisId_Bu2Dst0h_D0pi0_; }
  RooRealVar &mcEffMisId_Bu2Dst0h_D0gamma_WN() { return *mcEffMisId_Bu2Dst0h_D0gamma_WN_; }
  RooRealVar &mcEffMisId_Bu2Dst0h_D0pi0_WN() { return *mcEffMisId_Bu2Dst0h_D0pi0_WN_; }
  RooRealVar &mcEffMisId_Bd2Dsth() { return *mcEffMisId_Bd2Dsth_; }
  RooRealVar &mcEffMisId_Bu2D0hst() { return *mcEffMisId_Bu2D0hst_; }
  RooRealVar &mcEffMisId_Bu2Dst0hst_D0gamma() { return *mcEffMisId_Bu2Dst0hst_D0gamma_; }
  RooRealVar &mcEffMisId_Bu2Dst0hst_D0pi0() { return *mcEffMisId_Bu2Dst0hst_D0pi0_; }

  // -------------------- Bkg Fractions -------------------- //
  RooAbsReal &bkgFrac_Bu2Dst0h_D0pi0_WN() {
    return *bkgFrac_Bu2Dst0h_D0pi0_WN_;
  }
  RooAbsReal &bkgFrac_Bu2Dst0h_D0gamma_WN() {
    return *bkgFrac_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &bkgFrac_Bu2Dst0h_WN() {
    return bkgFrac_Bu2Dst0h_WN_;
  }
  RooFormulaVar &bkgFrac_Bu2Dst0hst() {
    return bkgFrac_Bu2Dst0hst_;
  }

  // -------------------- Bu2Dst0h_WN -------------------- //
  RooFormulaVar &Bu2Dst0h_WN_fracD0pi0() {
    return Bu2Dst0h_WN_fracD0pi0_;
  }
  RooAddPdf &pdfBu_Bu2Dst0h_WN() {
    return pdfBu_Bu2Dst0h_WN_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_WN() {
    return pdfDelta_Bu2Dst0h_WN_;
  }
  RooFormulaVar &orEffBu2Dst0h_WN() {
    return orEffBu2Dst0h_WN_;
  }
  RooFormulaVar &buEffBu2Dst0h_WN() {
    return buEffBu2Dst0h_WN_;
  }
  RooFormulaVar &deltaEffBu2Dst0h_WN() {
    return deltaEffBu2Dst0h_WN_;
  }
  RooFormulaVar &mcEff_Bu2Dst0h_WN() {
    return mcEff_Bu2Dst0h_WN_;
  }
  RooAddPdf &pdfBu_misId_Bu2Dst0h_WN() {
    return pdfBu_misId_Bu2Dst0h_WN_;
  }
  RooAddPdf &pdfDelta_misId_Bu2Dst0h_WN() {
    return pdfDelta_misId_Bu2Dst0h_WN_;
  }
  RooFormulaVar &orEffMisId_Bu2Dst0h_WN() {
    return orEffMisId_Bu2Dst0h_WN_;
  }
  RooFormulaVar &buEffMisId_Bu2Dst0h_WN() {
    return buEffMisId_Bu2Dst0h_WN_;
  }
  RooFormulaVar &deltaEffMisId_Bu2Dst0h_WN() {
    return deltaEffMisId_Bu2Dst0h_WN_;
  }
  RooFormulaVar &mcEffMisId_Bu2Dst0h_WN() {
    return mcEffMisId_Bu2Dst0h_WN_;
  }
  // -------------------- Bu2Dst0hst -------------------- //
  RooFormulaVar &Bu2Dst0hst_fracD0pi0_Bu() { return Bu2Dst0hst_fracD0pi0_Bu_; }
  RooAbsPdf &pdfBu_Bu2Dst0hst() { return *pdfBu_Bu2Dst0hst_; }
  std::shared_ptr<RooAbsPdf> &pdfBu_Bu2Dst0hst_GetPointer() {
    return pdfBu_Bu2Dst0hst_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0hst() {
    return pdfDelta_Bu2Dst0hst_;
  }
  RooAddPdf &pdfBuPartial_Bu2Dst0hst() {
    return pdfBuPartial_Bu2Dst0hst_;
  }
  RooFormulaVar &orEffBu2Dst0hst() {
    return orEffBu2Dst0hst_;
  }
  RooFormulaVar &buEffBu2Dst0hst() {
    return buEffBu2Dst0hst_;
  }
  RooFormulaVar &deltaEffBu2Dst0hst() {
    return deltaEffBu2Dst0hst_;
  }
  RooFormulaVar &buPartialEffBu2Dst0hst() {
    return buPartialEffBu2Dst0hst_;
  }
  RooFormulaVar &mcEff_Bu2Dst0hst() {
    return mcEff_Bu2Dst0hst_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0hst() {
    return *pdfBu_misId_Bu2Dst0hst_;
  }
  RooAddPdf &pdfDelta_misId_Bu2Dst0hst() {
    return pdfDelta_misId_Bu2Dst0hst_;
  }
  RooAddPdf &pdfBuPartial_misId_Bu2Dst0hst() {
    return pdfBuPartial_misId_Bu2Dst0hst_;
  }
  RooFormulaVar &orEffMisId_Bu2Dst0hst() {
    return orEffMisId_Bu2Dst0hst_;
  }
  RooFormulaVar &buEffMisId_Bu2Dst0hst() {
    return buEffMisId_Bu2Dst0hst_;
  }
  RooFormulaVar &deltaEffMisId_Bu2Dst0hst() {
    return deltaEffMisId_Bu2Dst0hst_;
  }
  RooFormulaVar &buPartialEffMisId_Bu2Dst0hst() {
    return buPartialEffMisId_Bu2Dst0hst_;
  }
  RooFormulaVar &mcEffMisId_Bu2Dst0hst() {
    return mcEffMisId_Bu2Dst0hst_;
  }

 private:
  int uniqueId_;
  // -------------------- PDF SHAPES -------------------- //
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0gamma_sigmaDelta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0gamma_;
  RooAddPdf pdfDelta_Bu2Dst0h_D0gamma_;
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
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigma1Bu_;
  RooFormulaVar Bu2Dst0h_D0pi0_sigma2Bu_;
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
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_aDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_bDelta_;
  RooDstD0BG pdfDelta_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0pi0_WN_sigma1Bu_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0pi0_WN_sigma2Bu_;
  RooCBShape pdf1Bu_Bu2Dst0h_D0pi0_WN_;
  RooCBShape pdf2Bu_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0h_D0pi0_WN_;
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
  std::shared_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0pi0_WN_;
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
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2D0hst_;
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
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_meanDelta_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_sigmaDelta_;
  RooCBShape pdf1Delta_misId_Bu2Dst0hst_D0gamma_;
  RooCBShape pdf2Delta_misId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_fracPdf1Delta_;
  RooAddPdf pdfPeakDelta_misId_Bu2Dst0hst_D0gamma_;
  RooDstD0BG pdfFlatDelta_misId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0hst_D0gamma_fracPdfPeakDelta_;
  std::unique_ptr<RooAbsPdf> pdfDelta_misId_Bu2Dst0hst_D0gamma_;
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
  // -------------------- Bs2Dst0Kpi -------------------- //
  RooCBShape pdfPeakGamma1Delta_Bs2Dst0Kpi_;
  RooCBShape pdfPeakGamma2Delta_Bs2Dst0Kpi_;
  RooAddPdf pdfPeakGammaDelta_Bs2Dst0Kpi_;
  RooCBShape pdfPeakPi01Delta_Bs2Dst0Kpi_;
  RooCBShape pdfPeakPi02Delta_Bs2Dst0Kpi_;
  RooAddPdf pdfPeakPi0Delta_Bs2Dst0Kpi_;
  RooAddPdf pdfDelta_Bs2Dst0Kpi_;
  // -------------------- Correct ID BOX EFFs -------------------- //
  std::shared_ptr<RooRealVar> orEffBu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> orEffBu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> orEffBu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> orEffBu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> orEffBd2Dsth_;
  std::shared_ptr<RooRealVar> orEffBu2D0hst_;
  std::shared_ptr<RooRealVar> orEffBu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> orEffBu2Dst0hst_D0pi0_;
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
  std::shared_ptr<RooRealVar> orEffMisId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> orEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> orEffMisId_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> orEffMisId_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> orEffMisId_Bd2Dsth_;
  std::shared_ptr<RooRealVar> orEffMisId_Bu2D0hst_;
  std::shared_ptr<RooRealVar> orEffMisId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> orEffMisId_Bu2Dst0hst_D0pi0_;
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
  // -------------------- MC misId Efficiencies -------------------- //
  std::shared_ptr<RooRealVar> mcEffMisId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> mcEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> mcEffMisId_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> mcEffMisId_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> mcEffMisId_Bd2Dsth_;
  std::shared_ptr<RooRealVar> mcEffMisId_Bu2D0hst_;
  std::shared_ptr<RooRealVar> mcEffMisId_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> mcEffMisId_Bu2Dst0hst_D0pi0_;
  // -------------------- Bkg Fractions -------------------- //
  std::shared_ptr<RooAbsReal> bkgFrac_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> bkgFrac_Bu2Dst0h_D0gamma_WN_;
  RooFormulaVar bkgFrac_Bu2Dst0h_WN_;
  RooFormulaVar bkgFrac_Bu2Dst0hst_;
  // -------------------- Bu2Dst0h_WN -------------------- //
  RooFormulaVar Bu2Dst0h_WN_fracD0pi0_;
  RooFormulaVar Bu2Dst0h_WN_fracD0pi0_Bu_;
  RooFormulaVar Bu2Dst0h_WN_fracD0pi0_Delta_;
  RooAddPdf pdfBu_Bu2Dst0h_WN_;
  RooAddPdf pdfDelta_Bu2Dst0h_WN_;
  RooFormulaVar orEffBu2Dst0h_WN_;
  RooFormulaVar buEffBu2Dst0h_WN_;
  RooFormulaVar deltaEffBu2Dst0h_WN_;
  RooFormulaVar mcEff_Bu2Dst0h_WN_;
  RooFormulaVar Bu2Dst0h_WN_misId_fracD0pi0_;
  RooFormulaVar Bu2Dst0h_WN_misId_fracD0pi0_Bu_;
  RooFormulaVar Bu2Dst0h_WN_misId_fracD0pi0_Delta_;
  RooAddPdf pdfBu_misId_Bu2Dst0h_WN_;
  RooAddPdf pdfDelta_misId_Bu2Dst0h_WN_;
  RooFormulaVar orEffMisId_Bu2Dst0h_WN_;
  RooFormulaVar buEffMisId_Bu2Dst0h_WN_;
  RooFormulaVar deltaEffMisId_Bu2Dst0h_WN_;
  RooFormulaVar mcEffMisId_Bu2Dst0h_WN_;
  // -------------------- Bu2Dst0hst -------------------- //
  RooFormulaVar Bu2Dst0hst_fracD0pi0_;
  RooFormulaVar Bu2Dst0hst_fracD0pi0_Bu_;
  RooFormulaVar Bu2Dst0hst_fracD0pi0_Delta_;
  RooFormulaVar Bu2Dst0hst_fracD0pi0_BuPartial_;
  std::shared_ptr<RooAbsPdf> pdfBu_Bu2Dst0hst_;
  RooAddPdf pdfDelta_Bu2Dst0hst_;
  RooAddPdf pdfBuPartial_Bu2Dst0hst_;
  RooFormulaVar orEffBu2Dst0hst_;
  RooFormulaVar buEffBu2Dst0hst_;
  RooFormulaVar deltaEffBu2Dst0hst_;
  RooFormulaVar buPartialEffBu2Dst0hst_;
  RooFormulaVar mcEff_Bu2Dst0hst_;
  RooFormulaVar Bu2Dst0hst_misId_fracD0pi0_;
  RooFormulaVar Bu2Dst0hst_misId_fracD0pi0_Bu_;
  RooFormulaVar Bu2Dst0hst_misId_fracD0pi0_Delta_;
  RooFormulaVar Bu2Dst0hst_misId_fracD0pi0_BuPartial_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0hst_;
  RooAddPdf pdfDelta_misId_Bu2Dst0hst_;
  RooAddPdf pdfBuPartial_misId_Bu2Dst0hst_;
  RooFormulaVar orEffMisId_Bu2Dst0hst_;
  RooFormulaVar buEffMisId_Bu2Dst0hst_;
  RooFormulaVar deltaEffMisId_Bu2Dst0hst_;
  RooFormulaVar buPartialEffMisId_Bu2Dst0hst_;
  RooFormulaVar mcEffMisId_Bu2Dst0hst_;
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
