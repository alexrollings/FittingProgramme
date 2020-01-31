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
  // -------------------- A CP initial value -------------------- //
  const double &A_CP_init() {
    return A_CP_init_;
  }
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooAbsReal &Bu2Dst0h_D0gamma_sigma1Bu() { return *Bu2Dst0h_D0gamma_sigma1Bu_; }
  RooAbsReal &Bu2Dst0h_D0gamma_sigma2Bu() { return *Bu2Dst0h_D0gamma_sigma2Bu_; }
  RooCBShape &pdf1Bu_Bu2Dst0h_D0gamma() { return pdf1Bu_Bu2Dst0h_D0gamma_; }
  RooCBShape &pdf2Bu_Bu2Dst0h_D0gamma() { return pdf2Bu_Bu2Dst0h_D0gamma_; }
  RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma() { return *pdfBu_Bu2Dst0h_D0gamma_; }
  RooRealVar &Bu2Dst0h_D0gamma_sigmaBuPartial() { return Bu2Dst0h_D0gamma_sigmaBuPartial_; }
  RooCBShape &pdfBuPartial_Bu2Dst0h_D0gamma() { return pdfBuPartial_Bu2Dst0h_D0gamma_; }
  double &N_tot_initVal_Bu2Dst0h_D0gamma() {
    return N_tot_initVal_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Mis-ID ------------------- //
  RooRealVar &misId_Bu2Dst0h_D0gamma_meanBu() {
    return misId_Bu2Dst0h_D0gamma_meanBu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_sigma1Bu() {
    return misId_Bu2Dst0h_D0gamma_sigma1Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_sigma2Bu() {
    return misId_Bu2Dst0h_D0gamma_sigma2Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_a1Bu() {
    return misId_Bu2Dst0h_D0gamma_a1Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_a2Bu() {
    return misId_Bu2Dst0h_D0gamma_a2Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_n1Bu() {
    return misId_Bu2Dst0h_D0gamma_n1Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_n2Bu() {
    return misId_Bu2Dst0h_D0gamma_n2Bu_;
  }
  RooCBShape &pdf1Bu_misId_Bu2Dst0h_D0gamma() {
    return pdf1Bu_misId_Bu2Dst0h_D0gamma_;
  }
  RooCBShape &pdf2Bu_misId_Bu2Dst0h_D0gamma() {
    return pdf2Bu_misId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_fracPdf1Bu() {
    return misId_Bu2Dst0h_D0gamma_fracPdf1Bu_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() {
    return *pdfBu_misId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &orEffMisId_Bu2Dst0h_D0gamma() {
    return orEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &boxEffMisId_Bu2Dst0h_D0gamma() {
    return boxEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &buDeltaCutEffMisId_Bu2Dst0h_D0gamma() {
    return buDeltaCutEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaCutEffMisId_Bu2Dst0h_D0gamma() {
    return deltaCutEffMisId_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooAbsReal &Bu2Dst0h_D0pi0_sigma1Bu() { return *Bu2Dst0h_D0pi0_sigma1Bu_; }
  RooCBShape &pdf1Bu_Bu2Dst0h_D0pi0() { return pdf1Bu_Bu2Dst0h_D0pi0_; }
  RooCBShape &pdf2Bu_Bu2Dst0h_D0pi0() { return pdf2Bu_Bu2Dst0h_D0pi0_; }
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
  RooCBShape &pdf1BuPartial_Bu2Dst0h_D0pi0() {
    return pdf1BuPartial_Bu2Dst0h_D0pi0_;
  }
  RooCBShape &pdf2BuPartial_Bu2Dst0h_D0pi0() {
    return pdf2BuPartial_Bu2Dst0h_D0pi0_;
  }
  RooGaussian &pdf3BuPartial_Bu2Dst0h_D0pi0() {
    return pdf3BuPartial_Bu2Dst0h_D0pi0_;
  }
  RooAddPdf &pdfBuPartial_Bu2Dst0h_D0pi0() {
    return pdfBuPartial_Bu2Dst0h_D0pi0_;
  }
  double &N_tot_initVal_Bu2Dst0h_D0pi0() {
    return N_tot_initVal_Bu2Dst0h_D0pi0_;
  }
  // -------------------- Mis-ID ------------------- //
  RooRealVar &misId_Bu2Dst0h_D0pi0_meanBu() {
    return misId_Bu2Dst0h_D0pi0_meanBu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_sigma1Bu() {
    return misId_Bu2Dst0h_D0pi0_sigma1Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_sigma2Bu() {
    return misId_Bu2Dst0h_D0pi0_sigma2Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_a1Bu() { return misId_Bu2Dst0h_D0pi0_a1Bu_; }
  RooRealVar &misId_Bu2Dst0h_D0pi0_a2Bu() { return misId_Bu2Dst0h_D0pi0_a2Bu_; }
  RooRealVar &misId_Bu2Dst0h_D0pi0_n1Bu() { return misId_Bu2Dst0h_D0pi0_n1Bu_; }
  RooRealVar &misId_Bu2Dst0h_D0pi0_n2Bu() { return misId_Bu2Dst0h_D0pi0_n2Bu_; }
  RooCBShape &pdf1Bu_misId_Bu2Dst0h_D0pi0() {
    return pdf1Bu_misId_Bu2Dst0h_D0pi0_;
  }
  RooCBShape &pdf2Bu_misId_Bu2Dst0h_D0pi0() {
    return pdf2Bu_misId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_fracPdf1Bu() {
    return misId_Bu2Dst0h_D0pi0_fracPdf1Bu_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() {
    return *pdfBu_misId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_meanBuPartial() {
    return misId_Bu2Dst0h_D0pi0_meanBuPartial_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_sigma1BuPartial() {
    return misId_Bu2Dst0h_D0pi0_sigma1BuPartial_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_sigma2BuPartial() {
    return misId_Bu2Dst0h_D0pi0_sigma2BuPartial_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_a1BuPartial() {
    return misId_Bu2Dst0h_D0pi0_a1BuPartial_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_a2BuPartial() {
    return misId_Bu2Dst0h_D0pi0_a2BuPartial_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_n1BuPartial() {
    return misId_Bu2Dst0h_D0pi0_n1BuPartial_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_n2BuPartial() {
    return misId_Bu2Dst0h_D0pi0_n2BuPartial_;
  }
  RooCBShape &pdf1BuPartial_misId_Bu2Dst0h_D0pi0() {
    return pdf1BuPartial_misId_Bu2Dst0h_D0pi0_;
  }
  RooCBShape &pdf2BuPartial_misId_Bu2Dst0h_D0pi0() {
    return pdf2BuPartial_misId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial() {
    return misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_;
  }
  RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0pi0() {
    return *pdfBuPartial_misId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &orEffMisId_Bu2Dst0h_D0pi0() { return orEffMisId_Bu2Dst0h_D0pi0_; }
  RooRealVar &boxEffMisId_Bu2Dst0h_D0pi0() {
    return boxEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &boxPartialEffMisId_Bu2Dst0h_D0pi0() {
    return boxPartialEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &buDeltaCutEffMisId_Bu2Dst0h_D0pi0() {
    return buDeltaCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaCutEffMisId_Bu2Dst0h_D0pi0() {
    return deltaCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaPartialCutEffMisId_Bu2Dst0h_D0pi0() {
    return deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  // -------------------- MIS-REC -------------------- //
  RooRealVar &MisRec_sigmaLBu() { return MisRec_sigmaLBu_; }
  RooRealVar &MisRec_sigmaRBu() { return MisRec_sigmaRBu_; }
  RooCruijff &pdfBu_MisRec() { return pdfBu_MisRec_; }
  RooRealVar &MisRec_sigmaLBuPartial() { return MisRec_sigmaLBuPartial_; }
  RooRealVar &MisRec_sigmaRBuPartial() { return MisRec_sigmaRBuPartial_; }
  RooCruijff &pdfBuPartial_MisRec() { return pdfBuPartial_MisRec_; }
  const double &N_initVal_MisRec() {
    return N_initVal_MisRec_;
  }
  // -------------------- Mis-ID ------------------- //
  RooRealVar &misId_MisRec_mean1Bu() {
    return misId_MisRec_mean1Bu_;
  }
  RooRealVar &misId_MisRec_mean2Bu() {
    return misId_MisRec_mean2Bu_;
  }
  RooRealVar &misId_MisRec_sigma1Bu() {
    return misId_MisRec_sigma1Bu_;
  }
  RooRealVar &misId_MisRec_sigma2Bu() {
    return misId_MisRec_sigma2Bu_;
  }
  RooRealVar &misId_MisRec_a1Bu() {
    return misId_MisRec_a1Bu_;
  }
  RooRealVar &misId_MisRec_a2Bu() {
    return misId_MisRec_a2Bu_;
  }
  RooRealVar &misId_MisRec_n1Bu() {
    return misId_MisRec_n1Bu_;
  }
  RooRealVar &misId_MisRec_n2Bu() {
    return misId_MisRec_n2Bu_;
  }
  RooCBShape &pdf1Bu_misId_MisRec() {
    return pdf1Bu_misId_MisRec_;
  }
  RooCBShape &pdf2Bu_misId_MisRec() {
    return pdf2Bu_misId_MisRec_;
  }
  RooRealVar &misId_MisRec_fracPdf1Bu() {
    return misId_MisRec_fracPdf1Bu_;
  }
  RooAbsPdf &pdfBu_misId_MisRec() {
    return *pdfBu_misId_MisRec_;
  }
  RooRealVar &misId_MisRec_meanBuPartial() {
    return misId_MisRec_meanBuPartial_;
  }
  RooRealVar &misId_MisRec_sigmaLBuPartial() {
    return misId_MisRec_sigmaLBuPartial_;
  }
  RooRealVar &misId_MisRec_sigmaRBuPartial() {
    return misId_MisRec_sigmaRBuPartial_;
  }
  RooRealVar &misId_MisRec_aLBuPartial() { return misId_MisRec_aLBuPartial_; }
  RooRealVar &misId_MisRec_aRBuPartial() { return misId_MisRec_aRBuPartial_; }
  RooCruijff &pdfBuPartial_misId_MisRec() { return pdfBuPartial_misId_MisRec_; }
  RooRealVar &orEffMisId_MisRec() { return orEffMisId_MisRec_; }
  RooRealVar &boxEffMisId_MisRec() { return boxEffMisId_MisRec_; }
  RooRealVar &boxPartialEffMisId_MisRec() { return boxPartialEffMisId_MisRec_; }
  RooRealVar &buDeltaCutEffMisId_MisRec() { return buDeltaCutEffMisId_MisRec_; }
  RooRealVar &deltaCutEffMisId_MisRec() { return deltaCutEffMisId_MisRec_; }
  RooRealVar &deltaPartialCutEffMisId_MisRec() {
    return deltaPartialCutEffMisId_MisRec_;
  }
  // -------------------- Bu2D0h -------------------- //
  RooRealVar &Bu2D0h_sigmaLBu() { return Bu2D0h_sigmaLBu_; }
  RooRealVar &Bu2D0h_sigmaRBu() { return Bu2D0h_sigmaRBu_; }
  RooCruijff &pdfBu_Bu2D0h() { return pdfBu_Bu2D0h_; }
  RooRealVar &Bu2D0h_sigmaLBuPartial() { return Bu2D0h_sigmaLBuPartial_; }
  RooRealVar &Bu2D0h_sigmaRBuPartial() { return Bu2D0h_sigmaRBuPartial_; }
  RooCruijff &pdfBuPartial_Bu2D0h() { return pdfBuPartial_Bu2D0h_; }
  double &N_initVal_Bu2D0h() {
    return N_initVal_Bu2D0h_;
  }
  // -------------------- Mis-ID ------------------- //
  RooRealVar &misId_Bu2D0h_meanBu() { return misId_Bu2D0h_meanBu_; }
  RooRealVar &misId_Bu2D0h_sigmaLBu() { return misId_Bu2D0h_sigmaLBu_; }
  RooRealVar &misId_Bu2D0h_sigmaRBu() { return misId_Bu2D0h_sigmaRBu_; }
  RooRealVar &misId_Bu2D0h_aLBu() { return misId_Bu2D0h_aLBu_; }
  RooRealVar &misId_Bu2D0h_aRBu() { return misId_Bu2D0h_aRBu_; }
  RooCruijff &pdfBu_misId_Bu2D0h() { return pdfBu_misId_Bu2D0h_; }
  RooRealVar &misId_Bu2D0h_meanBuPartial() {
    return misId_Bu2D0h_meanBuPartial_;
  }
  RooRealVar &misId_Bu2D0h_sigmaLBuPartial() {
    return misId_Bu2D0h_sigmaLBuPartial_;
  }
  RooRealVar &misId_Bu2D0h_sigmaRBuPartial() {
    return misId_Bu2D0h_sigmaRBuPartial_;
  }
  RooRealVar &misId_Bu2D0h_aLBuPartial() { return misId_Bu2D0h_aLBuPartial_; }
  RooRealVar &misId_Bu2D0h_aRBuPartial() { return misId_Bu2D0h_aRBuPartial_; }
  RooCruijff &pdfBuPartial_misId_Bu2D0h() { return pdfBuPartial_misId_Bu2D0h_; }
  RooRealVar &orEffMisId_Bu2D0h() { return orEffMisId_Bu2D0h_; }
  RooRealVar &boxEffMisId_Bu2D0h() { return boxEffMisId_Bu2D0h_; }
  RooRealVar &boxPartialEffMisId_Bu2D0h() { return boxPartialEffMisId_Bu2D0h_; }
  RooRealVar &buDeltaCutEffMisId_Bu2D0h() { return buDeltaCutEffMisId_Bu2D0h_; }
  RooRealVar &deltaCutEffMisId_Bu2D0h() { return deltaCutEffMisId_Bu2D0h_; }
  RooRealVar &deltaPartialCutEffMisId_Bu2D0h() {
    return deltaPartialCutEffMisId_Bu2D0h_;
  }
  // -------------------- PART REC -------------------- //
  RooRealVar &partRec_D0pi0_sigmaLBu() {
    return partRec_D0pi0_sigmaLBu_;
  }
  RooRealVar &partRec_D0pi0_sigmaRBu() {
    return partRec_D0pi0_sigmaRBu_;
  }
  RooCruijff &pdfBu_PartRec_D0pi0() { return pdfBu_PartRec_D0pi0_; }
  RooRealVar &partRec_D0gamma_sigmaLBu() {
    return partRec_D0gamma_sigmaLBu_;
  }
  RooRealVar &partRec_D0gamma_sigmaRBu() {
    return partRec_D0gamma_sigmaRBu_;
  }
  RooCruijff &pdfBu_PartRec_D0gamma() { return pdfBu_PartRec_D0gamma_; }
  RooAbsPdf &pdfBu_PartRec() { return *pdfBu_PartRec_; }
  RooRealVar &partRec_sigmaLBuPartial() {
    return partRec_sigmaLBuPartial_;
  }
  RooRealVar &partRec_sigmaRBuPartial() {
    return partRec_sigmaRBuPartial_;
  }
  RooCruijff &pdfBuPartial_PartRec() { return pdfBuPartial_PartRec_; }
  double &N_initVal_PartRec() {
    return N_initVal_PartRec_;
  }
  // -------------------- Mis-ID ------------------- //
  RooRealVar &misId_PartRec_meanBu() {
    return misId_PartRec_meanBu_;
  }
  RooRealVar &misId_PartRec_sigmaLBu() {
    return misId_PartRec_sigmaLBu_;
  }
  RooRealVar &misId_PartRec_sigmaRBu() {
    return misId_PartRec_sigmaRBu_;
  }
  RooRealVar &misId_PartRec_aLBu() {
    return misId_PartRec_aLBu_;
  }
  RooRealVar &misId_PartRec_aRBu() {
    return misId_PartRec_aRBu_;
  }
  RooCruijff &pdfBu_misId_PartRec() {
    return pdfBu_misId_PartRec_;
  }
  RooRealVar &misId_PartRec_meanBuPartial() {
    return misId_PartRec_meanBuPartial_;
  }
  RooRealVar &misId_PartRec_sigmaLBuPartial() {
    return misId_PartRec_sigmaLBuPartial_;
  }
  RooRealVar &misId_PartRec_sigmaRBuPartial() {
    return misId_PartRec_sigmaRBuPartial_;
  }
  RooRealVar &misId_PartRec_aLBuPartial() { return misId_PartRec_aLBuPartial_; }
  RooRealVar &misId_PartRec_aRBuPartial() { return misId_PartRec_aRBuPartial_; }
  RooCruijff &pdfBuPartial_misId_PartRec() { return pdfBuPartial_misId_PartRec_; }
  RooRealVar &orEffMisId_PartRec() { return orEffMisId_PartRec_; }
  RooRealVar &boxEffMisId_PartRec() { return boxEffMisId_PartRec_; }
  RooRealVar &boxPartialEffMisId_PartRec() { return boxPartialEffMisId_PartRec_; }
  RooRealVar &buDeltaCutEffMisId_PartRec() { return buDeltaCutEffMisId_PartRec_; }
  RooRealVar &deltaCutEffMisId_PartRec() { return deltaCutEffMisId_PartRec_; }
  RooRealVar &deltaPartialCutEffMisId_PartRec() {
    return deltaPartialCutEffMisId_PartRec_;
  }
  // -------------------- Bs2Dst0Kpi -------------------- //
  RooRealVar &Bs2Dst0Kpi_thresholdDelta() { return Bs2Dst0Kpi_thresholdDelta_; }
  RooRealVar &Bs2Dst0Kpi_aDelta() { return Bs2Dst0Kpi_aDelta_; }
  RooRealVar &Bs2Dst0Kpi_bDelta() { return Bs2Dst0Kpi_bDelta_; }
  RooRealVar &Bs2Dst0Kpi_cDelta() { return Bs2Dst0Kpi_cDelta_; }
  RooDstD0BG &pdfFlatDelta_Bs2Dst0Kpi() { return pdfFlatDelta_Bs2Dst0Kpi_; }
  RooRealVar &Bs2Dst0Kpi_meanDelta() { return Bs2Dst0Kpi_meanDelta_; }
  RooRealVar &Bs2Dst0Kpi_sigmaDelta() { return Bs2Dst0Kpi_sigmaDelta_; }
  RooCBShape &pdfPeak1Delta_Bs2Dst0Kpi() { return pdfPeak1Delta_Bs2Dst0Kpi_; }
  RooCBShape &pdfPeak2Delta_Bs2Dst0Kpi() { return pdfPeak2Delta_Bs2Dst0Kpi_; }
  RooAddPdf &pdfPeakDelta_Bs2Dst0Kpi() { return pdfPeakDelta_Bs2Dst0Kpi_; }
  RooRealVar &Bs2Dst0Kpi_fracPeakDelta() { return Bs2Dst0Kpi_fracPeakDelta_; }
  RooAddPdf &pdfDelta_Bs2Dst0Kpi() { return pdfDelta_Bs2Dst0Kpi_; }
  RooRealVar &Bs2Dst0Kpi_meanBu() { return Bs2Dst0Kpi_meanBu_; }
  RooRealVar &Bs2Dst0Kpi_sigmaLBu() { return Bs2Dst0Kpi_sigmaLBu_; }
  RooRealVar &Bs2Dst0Kpi_sigmaRBu() { return Bs2Dst0Kpi_sigmaRBu_; }
  RooRealVar &Bs2Dst0Kpi_aLBu() { return Bs2Dst0Kpi_aLBu_; }
  RooRealVar &Bs2Dst0Kpi_aRBu() { return Bs2Dst0Kpi_aRBu_; }
  RooCruijff &pdfBu_Bs2Dst0Kpi() { return pdfBu_Bs2Dst0Kpi_; }
  // -------------------- Bs2D0Kpi -------------------- //
  RooDstD0BG &pdfDelta_Bs2D0Kpi() { return pdfDelta_Bs2D0Kpi_; }
  RooRealVar &Bs2D0Kpi_meanBu() { return Bs2D0Kpi_meanBu_; }
  RooRealVar &Bs2D0Kpi_sigmaBu() { return Bs2D0Kpi_sigmaBu_; }
  RooGaussian &pdfBu_Bs2D0Kpi() { return pdfBu_Bs2D0Kpi_; }

 private:
  int uniqueId_;
  // -------------------- A CP initial value -------------------- //
  const double A_CP_init_;
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0gamma_sigma1Bu_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0gamma_sigma2Bu_;
  RooCBShape pdf1Bu_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0h_D0gamma_;
  RooRealVar Bu2Dst0h_D0gamma_sigmaBuPartial_;
  RooCBShape pdfBuPartial_Bu2Dst0h_D0gamma_;
  double N_tot_initVal_Bu2Dst0h_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  // 1 = L, 2 = R for RooCruijff
  RooRealVar misId_Bu2Dst0h_D0gamma_meanBu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_sigma1Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_sigma2Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_a2Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_a1Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_n2Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_n1Bu_;
  RooCBShape pdf1Bu_misId_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Bu_misId_Bu2Dst0h_D0gamma_;
  RooRealVar misId_Bu2Dst0h_D0gamma_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0gamma_;
  RooRealVar orEffMisId_Bu2Dst0h_D0gamma_;
  RooRealVar boxEffMisId_Bu2Dst0h_D0gamma_;
  RooRealVar buDeltaCutEffMisId_Bu2Dst0h_D0gamma_;
  RooRealVar deltaCutEffMisId_Bu2Dst0h_D0gamma_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigma1Bu_;
  RooCBShape pdf1Bu_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsPdf> pdfBu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigma1BuPartial_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigma2BuPartial_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0pi0_sigma3BuPartial_;
  RooCBShape pdf1BuPartial_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2BuPartial_Bu2Dst0h_D0pi0_;
  RooGaussian pdf3BuPartial_Bu2Dst0h_D0pi0_;
  RooAddPdf pdfBuPartial_Bu2Dst0h_D0pi0_;
  double N_tot_initVal_Bu2Dst0h_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  // 1 = L, 2 = R for RooCruijff
  RooRealVar misId_Bu2Dst0h_D0pi0_meanBu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_sigma1Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_sigma2Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_a2Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_a1Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_n2Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_n1Bu_;
  RooCBShape pdf1Bu_misId_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Bu_misId_Bu2Dst0h_D0pi0_;
  RooRealVar misId_Bu2Dst0h_D0pi0_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0pi0_;
  RooRealVar misId_Bu2Dst0h_D0pi0_meanBuPartial_;
  RooRealVar misId_Bu2Dst0h_D0pi0_sigma1BuPartial_;
  RooRealVar misId_Bu2Dst0h_D0pi0_sigma2BuPartial_;
  RooRealVar misId_Bu2Dst0h_D0pi0_a2BuPartial_;
  RooRealVar misId_Bu2Dst0h_D0pi0_a1BuPartial_;
  RooRealVar misId_Bu2Dst0h_D0pi0_n2BuPartial_;
  RooRealVar misId_Bu2Dst0h_D0pi0_n1BuPartial_;
  RooCBShape pdf1BuPartial_misId_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2BuPartial_misId_Bu2Dst0h_D0pi0_;
  RooRealVar misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_;
  std::unique_ptr<RooAbsPdf> pdfBuPartial_misId_Bu2Dst0h_D0pi0_;
  RooRealVar orEffMisId_Bu2Dst0h_D0pi0_;
  RooRealVar boxEffMisId_Bu2Dst0h_D0pi0_;
  RooRealVar boxPartialEffMisId_Bu2Dst0h_D0pi0_;
  RooRealVar buDeltaCutEffMisId_Bu2Dst0h_D0pi0_;
  RooRealVar deltaCutEffMisId_Bu2Dst0h_D0pi0_;
  RooRealVar deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_;
  // -------------------- MIS-REC -------------------- //
  RooRealVar MisRec_sigmaLBu_;
  RooRealVar MisRec_sigmaRBu_;
  RooCruijff pdfBu_MisRec_;
  RooRealVar MisRec_sigmaLBuPartial_;
  RooRealVar MisRec_sigmaRBuPartial_;
  RooCruijff pdfBuPartial_MisRec_;
  const double N_initVal_MisRec_;
  // -------------------- Mis-ID ------------------- //
  RooRealVar misId_MisRec_mean1Bu_;
  RooRealVar misId_MisRec_mean2Bu_;
  RooRealVar misId_MisRec_sigma1Bu_;
  RooRealVar misId_MisRec_sigma2Bu_;
  RooRealVar misId_MisRec_a2Bu_;
  RooRealVar misId_MisRec_a1Bu_;
  RooRealVar misId_MisRec_n2Bu_;
  RooRealVar misId_MisRec_n1Bu_;
  RooCBShape pdf1Bu_misId_MisRec_;
  RooCBShape pdf2Bu_misId_MisRec_;
  RooRealVar misId_MisRec_fracPdf1Bu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_MisRec_;
  RooRealVar misId_MisRec_meanBuPartial_;
  RooRealVar misId_MisRec_sigmaLBuPartial_;
  RooRealVar misId_MisRec_sigmaRBuPartial_;
  RooRealVar misId_MisRec_aLBuPartial_;
  RooRealVar misId_MisRec_aRBuPartial_;
  RooCruijff pdfBuPartial_misId_MisRec_;
  RooRealVar orEffMisId_MisRec_;
  RooRealVar boxEffMisId_MisRec_;
  RooRealVar boxPartialEffMisId_MisRec_;
  RooRealVar buDeltaCutEffMisId_MisRec_;
  RooRealVar deltaCutEffMisId_MisRec_;
  RooRealVar deltaPartialCutEffMisId_MisRec_;
  // -------------------- Bu2D0h -------------------- //
  RooRealVar Bu2D0h_sigmaLBu_;
  RooRealVar Bu2D0h_sigmaRBu_;
  RooCruijff pdfBu_Bu2D0h_;
  RooRealVar Bu2D0h_sigmaLBuPartial_;
  RooRealVar Bu2D0h_sigmaRBuPartial_;
  RooCruijff pdfBuPartial_Bu2D0h_;
  double N_initVal_Bu2D0h_;
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
  RooRealVar orEffMisId_Bu2D0h_;
  RooRealVar boxEffMisId_Bu2D0h_;
  RooRealVar boxPartialEffMisId_Bu2D0h_;
  RooRealVar buDeltaCutEffMisId_Bu2D0h_;
  RooRealVar deltaCutEffMisId_Bu2D0h_;
  RooRealVar deltaPartialCutEffMisId_Bu2D0h_;
  // -------------------- PART REC -------------------- //
  RooRealVar partRec_D0pi0_sigmaLBu_;
  RooRealVar partRec_D0pi0_sigmaRBu_;
  RooCruijff pdfBu_PartRec_D0pi0_;
  RooRealVar partRec_D0gamma_sigmaLBu_;
  RooRealVar partRec_D0gamma_sigmaRBu_;
  RooCruijff pdfBu_PartRec_D0gamma_;
  RooRealVar partRec_sigmaLBuPartial_;
  RooRealVar partRec_sigmaRBuPartial_;
  RooCruijff pdfBuPartial_PartRec_;
  std::unique_ptr<RooAbsPdf> pdfBu_PartRec_;
  double N_initVal_PartRec_;
  // -------------------- Mis-ID ------------------- //
  RooRealVar misId_PartRec_meanBu_;
  RooRealVar misId_PartRec_sigmaLBu_;
  RooRealVar misId_PartRec_sigmaRBu_;
  RooRealVar misId_PartRec_aLBu_;
  RooRealVar misId_PartRec_aRBu_;
  RooCruijff pdfBu_misId_PartRec_;
  RooRealVar misId_PartRec_meanBuPartial_;
  RooRealVar misId_PartRec_sigmaLBuPartial_;
  RooRealVar misId_PartRec_sigmaRBuPartial_;
  RooRealVar misId_PartRec_aLBuPartial_;
  RooRealVar misId_PartRec_aRBuPartial_;
  RooCruijff pdfBuPartial_misId_PartRec_;
  RooRealVar orEffMisId_PartRec_;
  RooRealVar boxEffMisId_PartRec_;
  RooRealVar boxPartialEffMisId_PartRec_;
  RooRealVar buDeltaCutEffMisId_PartRec_;
  RooRealVar deltaCutEffMisId_PartRec_;
  RooRealVar deltaPartialCutEffMisId_PartRec_;
  // -------------------- Bs2Dst0Kpi -------------------- //
  RooRealVar Bs2Dst0Kpi_thresholdDelta_;
  RooRealVar Bs2Dst0Kpi_aDelta_;
  RooRealVar Bs2Dst0Kpi_bDelta_;
  RooRealVar Bs2Dst0Kpi_cDelta_;
  RooDstD0BG pdfFlatDelta_Bs2Dst0Kpi_;
  RooRealVar Bs2Dst0Kpi_meanDelta_;
  RooRealVar Bs2Dst0Kpi_sigmaDelta_;
  RooCBShape pdfPeak1Delta_Bs2Dst0Kpi_;
  RooCBShape pdfPeak2Delta_Bs2Dst0Kpi_;
  RooAddPdf pdfPeakDelta_Bs2Dst0Kpi_;
  RooRealVar Bs2Dst0Kpi_fracPeakDelta_;
  RooAddPdf pdfDelta_Bs2Dst0Kpi_;
  RooRealVar Bs2Dst0Kpi_meanBu_;
  RooRealVar Bs2Dst0Kpi_sigmaLBu_;
  RooRealVar Bs2Dst0Kpi_sigmaRBu_;
  RooRealVar Bs2Dst0Kpi_aLBu_;
  RooRealVar Bs2Dst0Kpi_aRBu_;
  RooCruijff pdfBu_Bs2Dst0Kpi_;
  // -------------------- Bs2D0Kpi -------------------- //
  RooDstD0BG pdfDelta_Bs2D0Kpi_;
  RooRealVar Bs2D0Kpi_meanBu_;
  RooRealVar Bs2D0Kpi_sigmaBu_;
  RooGaussian pdfBu_Bs2D0Kpi_;
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
