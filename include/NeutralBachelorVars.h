#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooCruijff.h"
#include "RooGaussian.h"
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
  RooAbsReal &Bu2Dst0h_D0gamma_sigma1Bu() { return *Bu2Dst0h_D0gamma_sigma1Bu_; }
  RooAbsReal &Bu2Dst0h_D0gamma_sigma2Bu() { return *Bu2Dst0h_D0gamma_sigma2Bu_; }
  RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma() { return *pdfBu_Bu2Dst0h_D0gamma_; }
  RooRealVar &Bu2Dst0h_D0gamma_sigmaBuPartial() { return *Bu2Dst0h_D0gamma_sigmaBuPartial_; }
  RooCBShape &pdfBuPartial_Bu2Dst0h_D0gamma() { return pdfBuPartial_Bu2Dst0h_D0gamma_; }
  RooRealVar &mcEff_Bu2Dst0h_D0gamma() {
    return *mcEff_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Mis-ID ------------------- //
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() {
    return *pdfBu_misId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &buDeltaCutEffMisId_Bu2Dst0h_D0gamma() {
    return *buDeltaCutEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaCutEffMisId_Bu2Dst0h_D0gamma() {
    return *deltaCutEffMisId_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
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
  RooRealVar &mcEff_Bu2Dst0h_D0pi0() {
    return *mcEff_Bu2Dst0h_D0pi0_;
  }
  // -------------------- Mis-ID ------------------- //
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() {
    return *pdfBu_misId_Bu2Dst0h_D0pi0_;
  }
  RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0pi0() {
    return *pdfBuPartial_misId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &buDeltaCutEffMisId_Bu2Dst0h_D0pi0() {
    return *buDeltaCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaCutEffMisId_Bu2Dst0h_D0pi0() {
    return *deltaCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaPartialCutEffMisId_Bu2Dst0h_D0pi0() {
    return *deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  // -------------------- MIS-REC -------------------- //
  RooCruijff &pdfBu_MisRec() { return pdfBu_MisRec_; }
  RooCruijff &pdfBuPartial_MisRec() { return pdfBuPartial_MisRec_; }
  // -------------------- Mis-ID ------------------- //
  RooAbsPdf &pdfBu_misId_MisRec() {
    return *pdfBu_misId_MisRec_;
  }
  RooCruijff &pdfBuPartial_misId_MisRec() { return pdfBuPartial_misId_MisRec_; }
  RooRealVar &buDeltaCutEffMisId_MisRec() { return *buDeltaCutEffMisId_MisRec_; }
  RooRealVar &deltaCutEffMisId_MisRec() { return *deltaCutEffMisId_MisRec_; }
  RooRealVar &deltaPartialCutEffMisId_MisRec() {
    return *deltaPartialCutEffMisId_MisRec_;
  }
  // -------------------- Bu2D0h -------------------- //
  RooCruijff &pdfBu_Bu2D0h() { return pdfBu_Bu2D0h_; }
  RooCruijff &pdfBuPartial_Bu2D0h() { return pdfBuPartial_Bu2D0h_; }
  // -------------------- Mis-ID ------------------- //
  RooCruijff &pdfBu_misId_Bu2D0h() { return pdfBu_misId_Bu2D0h_; }
  RooCruijff &pdfBuPartial_misId_Bu2D0h() { return pdfBuPartial_misId_Bu2D0h_; }
  RooRealVar &buDeltaCutEffMisId_Bu2D0h() { return *buDeltaCutEffMisId_Bu2D0h_; }
  RooRealVar &deltaCutEffMisId_Bu2D0h() { return *deltaCutEffMisId_Bu2D0h_; }
  RooRealVar &deltaPartialCutEffMisId_Bu2D0h() {
    return *deltaPartialCutEffMisId_Bu2D0h_;
  }
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
  RooRealVar &buDeltaCutEffMisId_PartRec() { return *buDeltaCutEffMisId_PartRec_; }
  RooRealVar &deltaCutEffMisId_PartRec() { return *deltaCutEffMisId_PartRec_; }
  RooRealVar &deltaPartialCutEffMisId_PartRec() {
    return *deltaPartialCutEffMisId_PartRec_;
  }
  // -------------------- Bs2Dst0Kpi -------------------- //
  RooAddPdf &pdfDelta_Bs2Dst0Kpi() { return pdfDelta_Bs2Dst0Kpi_; }
  RooAbsPdf &pdfBu_Bs2Dst0Kpi() { return *pdfBu_Bs2Dst0Kpi_; }
  RooCruijff &pdfBuPartial_Bs2Dst0Kpi() { return pdfBuPartial_Bs2Dst0Kpi_; }
  RooRealVar &buDeltaCutEffBs2Dst0Kpi() {
    return *buDeltaCutEffBs2Dst0Kpi_;
  }
  RooRealVar &deltaCutEffBs2Dst0Kpi() {
    return *deltaCutEffBs2Dst0Kpi_;
  }
  RooRealVar &deltaPartialCutEffBs2Dst0Kpi() {
    return *deltaPartialCutEffBs2Dst0Kpi_;
  }
  // -------------------- Bs2D0Kpi -------------------- //
  RooDstD0BG &pdfDelta_Bs2D0Kpi() { return pdfDelta_Bs2D0Kpi_; }
  RooAbsPdf &pdfBu_Bs2D0Kpi() { return *pdfBu_Bs2D0Kpi_; }
  RooCruijff &pdfBuPartial_Bs2D0Kpi() { return pdfBuPartial_Bs2D0Kpi_; }
  RooRealVar &buDeltaCutEffBs2D0Kpi() {
    return *buDeltaCutEffBs2D0Kpi_;
  }
  RooRealVar &deltaCutEffBs2D0Kpi() {
    return *deltaCutEffBs2D0Kpi_;
  }
  RooRealVar &deltaPartialCutEffBs2D0Kpi() {
    return *deltaPartialCutEffBs2D0Kpi_;
  }

 private:
  int uniqueId_;
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0gamma_sigma1Bu_;
  std::shared_ptr<RooAbsReal> Bu2Dst0h_D0gamma_sigma2Bu_;
  RooCBShape pdf1Bu_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_sigmaBuPartial_;
  RooCBShape pdfBuPartial_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> mcEff_Bu2Dst0h_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_meanBu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_sigma1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_sigma2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_a2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_n2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_n1Bu_;
  RooCBShape pdf1Bu_misId_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Bu_misId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_Bu2Dst0h_D0gamma_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
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
  std::shared_ptr<RooRealVar> mcEff_Bu2Dst0h_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_meanBu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_sigma1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_sigma2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_a2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_a1Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_n2Bu_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_n1Bu_;
  RooCBShape pdf1Bu_misId_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Bu_misId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> misId_Bu2Dst0h_D0pi0_meanBuPartial_;
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
  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_;
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
  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_MisRec_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_MisRec_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffMisId_MisRec_;
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
  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_Bu2D0h_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_Bu2D0h_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffMisId_Bu2D0h_;
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
  std::shared_ptr<RooRealVar> buDeltaCutEffMisId_PartRec_;
  std::shared_ptr<RooRealVar> deltaCutEffMisId_PartRec_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffMisId_PartRec_;
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
  std::shared_ptr<RooRealVar> buDeltaCutEffBs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> deltaCutEffBs2Dst0Kpi_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffBs2Dst0Kpi_;
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
  std::shared_ptr<RooRealVar> buDeltaCutEffBs2D0Kpi_;
  std::shared_ptr<RooRealVar> deltaCutEffBs2D0Kpi_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffBs2D0Kpi_;
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
