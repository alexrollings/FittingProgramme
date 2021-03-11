#pragma once
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooSimultaneous.h"
#include "Yields.h"

class PdfBase {
 public:
  void AddToSimultaneousPdf(RooSimultaneous &) const;

  inline int uniqueId() const { return uniqueId_; }
  inline Bachelor bachelor() const { return bachelor_; }
  inline Neutral neutral() const { return neutral_; }
  inline Daughters daughters() const { return daughters_; }
  inline Charge charge() const { return charge_; }

  inline RooArgList &yieldsBu() { return yieldsBu_; }
  inline RooArgList &yieldsBuPartial() { return yieldsBuPartial_; }
  inline RooArgList &yieldsDelta() { return yieldsDelta_; }
  inline RooArgList &functionsBu() { return functionsBu_; }
  inline RooArgList &functionsBuPartial() { return functionsBuPartial_; }
  inline RooArgList &functionsDelta() { return functionsDelta_; }
  inline RooAddPdf &addPdfBu() { return *addPdfBu_; }
  inline RooAddPdf &addPdfBuPartial() { return *addPdfBuPartial_; }
  inline RooAddPdf &addPdfDelta() { return *addPdfDelta_; }
  // inline RooProdPdf &prodPdfBu() { return *prodPdfBu_; }
  // inline RooProdPdf &prodPdfBuPartial() { return *prodPdfBuPartial_; }
  // inline RooProdPdf &prodPdfDelta() { return *prodPdfDelta_; }

  virtual RooRealVar &bkgFracGlobal_WN() const = 0;
  virtual RooFormulaVar &Bs2Dst0Kst0_fracD0pi0_Delta() const = 0;

  virtual RooAbsReal &N_tot_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooAbsReal &N_tot_Bu2Dst0h_WN() const = 0;
  virtual RooAbsReal &N_tot_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_tot_Bu2Dst0h_D0pi0_D02pik() const = 0;
  virtual RooFormulaVar &N_tot_Bu2Dst0h_D0gamma_D02pik() const = 0;
  virtual RooFormulaVar &N_tot_Bu2Dst0h_D0pi0_WN_D02pik() const = 0;
  virtual RooFormulaVar &N_tot_Bu2Dst0h_D0gamma_WN_D02pik() const = 0;

  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0hst() const = 0;
  virtual RooFormulaVar &N_trueId_Lb2Omegach_Lcpi0() const = 0;
  virtual RooFormulaVar &N_trueId_Bs2Dst0Kst0() const = 0;
  virtual RooFormulaVar &N_trueId_Bs2D0Kst0() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_WN_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_WN_D02pik() const = 0;

  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0h_WN() const = 0;
  virtual RooFormulaVar &N_misId_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_misId_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0hst() const = 0;

  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0hst() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Lb2Omegach_Lcpi0() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bs2Dst0Kst0() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bs2D0Kst0() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik() const = 0;

  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0gamma() const = 0;
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_WN() const = 0;
  virtual RooFormulaVar &N_misId_Bu_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_misId_Bu_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0hst() const = 0;

  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0hst() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Lb2Omegach_Lcpi0() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bs2Dst0Kst0() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bs2D0Kst0() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik() const = 0;

  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0gamma() const = 0;
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_WN() const = 0;
  virtual RooFormulaVar &N_misId_Delta_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_misId_Delta_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0hst() const = 0;

  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0gamma() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0hst() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Lb2Omegach_Lcpi0() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bs2Dst0Kst0() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bs2D0Kst0() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik() const = 0;
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik()
      const = 0;

  virtual RooFormulaVar &N_misId_BuPartial_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_misId_BuPartial_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_misId_BuPartial_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_misId_BuPartial_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_misId_BuPartial_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_misId_BuPartial_Bu2Dst0hst() const = 0;

  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooDstD0BG &pdfDelta_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_WN() const = 0;
  virtual RooDstD0BG &pdfDelta_Bd2Dsth() const = 0;
  virtual RooDstD0BG &pdfDelta_Bu2D0hst() const = 0;
  virtual RooAbsPdf &pdfDelta_Bu2Dst0hst() const = 0;
  virtual RooDstD0BG &pdfDelta_Lb2Omegach_Lcpi0() const = 0;
  virtual RooDstD0BG &pdfDelta_Bs2D0Kst0() const = 0;
  virtual RooAddPdf &pdfDelta_Bs2Dst0Kst0() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0_D02pik() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_D02pik() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik() const = 0;

  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0h_WN() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_Bd2Dsth() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_Bu2D0hst() const = 0;
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0hst() const = 0;

  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooAddPdf &pdfBu_Bu2Dst0h_WN() const = 0;
  virtual RooAbsPdf &pdfBu_Bd2Dsth() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2D0hst() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2Dst0hst() const = 0;
  virtual RooCBShape &pdfBu_Lb2Omegach_Lcpi0() const = 0;
  virtual RooCBShape &pdfBu_Bs2D0Kst0() const = 0;
  virtual RooAddPdf &pdfBu_Bs2Dst0Kst0() const = 0;
  virtual RooGaussian &pdfBu_Bu2Dst0h_D0pi0_D02pik() const = 0;
  virtual RooGaussian &pdfBu_Bu2Dst0h_D0gamma_D02pik() const = 0;
  virtual RooGaussian &pdfBu_Bu2Dst0h_D0pi0_WN_D02pik() const = 0;
  virtual RooGaussian &pdfBu_Bu2Dst0h_D0gamma_WN_D02pik() const = 0;

  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooAddPdf &pdfBu_misId_Bu2Dst0h_WN() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bd2Dsth() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2D0hst() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0hst() const = 0;

  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfBuPartial_Bu2Dst0h_D0pi0() const = 0;
  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooAbsPdf &pdfBuPartial_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooAddPdf &pdfBuPartial_Bd2Dsth() const = 0;
  virtual RooGaussian &pdfBuPartial_Bu2D0hst() const = 0;
  virtual RooAddPdf &pdfBuPartial_Bu2Dst0hst() const = 0;
  virtual RooCBShape &pdfBuPartial_Lb2Omegach_Lcpi0() const = 0;
  virtual RooAddPdf &pdfBuPartial_Bs2D0Kst0() const = 0;
  virtual RooAddPdf &pdfBuPartial_Bs2Dst0Kst0() const = 0;

  virtual RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooCBShape &pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooCBShape &pdfBuPartial_misId_Bd2Dsth() const = 0;
  virtual RooCBShape &pdfBuPartial_misId_Bu2D0hst() const = 0;
  virtual RooAddPdf &pdfBuPartial_misId_Bu2Dst0hst() const = 0;
  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0pi0_D02pik() const = 0;
  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik() const = 0;

  virtual RooRealVar &orEffBu2Dst0h_D0gamma() const = 0;
  virtual RooRealVar &orEffBu2Dst0h_D0pi0() const = 0;
  virtual RooRealVar &orEffBu2Dst0h_D0gamma_WN() const = 0;
  virtual RooRealVar &orEffBu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &orEffBu2Dst0h_WN() const = 0;
  virtual RooRealVar &orEffBd2Dsth() const = 0;
  virtual RooRealVar &orEffBu2D0hst() const = 0;
  virtual RooRealVar &orEffBu2Dst0hst_D0pi0() const = 0;
  virtual RooRealVar &orEffBu2Dst0hst_D0gamma() const = 0;
  virtual RooFormulaVar &orEffBu2Dst0hst() const = 0;
  virtual RooRealVar &orEffLb2Omegach_Lcpi0() const = 0;
  virtual RooFormulaVar &orEffBs2Dst0Kst0() const = 0;
  virtual RooRealVar &orEffBs2D0Kst0() const = 0;

  virtual RooRealVar &orEffMisId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooRealVar &orEffMisId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooRealVar &orEffMisId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooRealVar &orEffMisId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &orEffMisId_Bu2Dst0h_WN() const = 0;
  virtual RooRealVar &orEffMisId_Bd2Dsth() const = 0;
  virtual RooRealVar &orEffMisId_Bu2D0hst() const = 0;
  virtual RooRealVar &orEffMisId_Bu2Dst0hst_D0pi0() const = 0;
  virtual RooRealVar &orEffMisId_Bu2Dst0hst_D0gamma() const = 0;
  virtual RooFormulaVar &orEffMisId_Bu2Dst0hst() const = 0;

  virtual RooRealVar &buEffBu2Dst0h_D0gamma() const = 0;
  virtual RooRealVar &buEffBu2Dst0h_D0pi0() const = 0;
  virtual RooRealVar &buEffBu2Dst0h_D0gamma_WN() const = 0;
  virtual RooRealVar &buEffBu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &buEffBu2Dst0h_WN() const = 0;
  virtual RooRealVar &buEffBd2Dsth() const = 0;
  virtual RooRealVar &buEffBu2D0hst() const = 0;
  virtual RooRealVar &buEffBu2Dst0hst_D0pi0() const = 0;
  virtual RooRealVar &buEffBu2Dst0hst_D0gamma() const = 0;
  virtual RooFormulaVar &buEffBu2Dst0hst() const = 0;
  virtual RooRealVar &buEffLb2Omegach_Lcpi0() const = 0;

  virtual RooRealVar &deltaEffBu2Dst0h_D0gamma() const = 0;
  virtual RooRealVar &deltaEffBu2Dst0h_D0pi0() const = 0;
  virtual RooRealVar &deltaEffBu2Dst0h_D0gamma_WN() const = 0;
  virtual RooRealVar &deltaEffBu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &deltaEffBu2Dst0h_WN() const = 0;
  virtual RooRealVar &deltaEffBd2Dsth() const = 0;
  virtual RooRealVar &deltaEffBu2D0hst() const = 0;
  virtual RooRealVar &deltaEffBu2Dst0hst_D0pi0() const = 0;
  virtual RooRealVar &deltaEffBu2Dst0hst_D0gamma() const = 0;
  virtual RooFormulaVar &deltaEffBu2Dst0hst() const = 0;
  virtual RooRealVar &deltaEffLb2Omegach_Lcpi0() const = 0;

  virtual RooRealVar &buPartialEffBu2Dst0h_D0gamma() const = 0;
  virtual RooRealVar &buPartialEffBu2Dst0h_D0pi0() const = 0;
  virtual RooRealVar &buPartialEffBu2Dst0h_D0gamma_WN() const = 0;
  virtual RooRealVar &buPartialEffBu2Dst0h_D0pi0_WN() const = 0;
  virtual RooRealVar &buPartialEffBd2Dsth() const = 0;
  virtual RooRealVar &buPartialEffBu2D0hst() const = 0;
  virtual RooRealVar &buPartialEffBu2Dst0hst_D0pi0() const = 0;
  virtual RooRealVar &buPartialEffBu2Dst0hst_D0gamma() const = 0;
  virtual RooFormulaVar &buPartialEffBu2Dst0hst() const = 0;
  virtual RooRealVar &buPartialEffLb2Omegach_Lcpi0() const = 0;

  // If a function or a method is defined in the header file, and the class is
  // not a template, it should be inline because otherwise the linker might fail
  // as the function will be present in multiple compiltation unit
  // function needs to be const when you don't change the object when the
  // function is called
  inline std::string CategoryName(Mass mass) const {
    return ComposeFittingName(mass, neutral_, bachelor_, daughters_, charge_);
  }

 protected:  // Can be accessed by deriving classes
  PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge);
  virtual ~PdfBase() {}

  int uniqueId_;
  Neutral neutral_;
  Bachelor bachelor_;
  Daughters daughters_;
  Charge charge_;

  RooArgList yieldsBu_;
  RooArgList yieldsBuPartial_;
  RooArgList yieldsDelta_;
  RooArgList functionsBu_;
  RooArgList functionsBuPartial_;
  RooArgList functionsDelta_;
  std::unique_ptr<RooAddPdf> addPdfBu_;
  std::unique_ptr<RooAddPdf> addPdfBuPartial_;
  std::unique_ptr<RooAddPdf> addPdfDelta_;
  // std::unique_ptr<RooProdPdf> prodPdfBu_;
  // std::unique_ptr<RooProdPdf> prodPdfBuPartial_;
  // std::unique_ptr<RooProdPdf> prodPdfDelta_;
};

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
class Pdf : public PdfBase {
  using This_t = Pdf<_neutral, _bachelor, _daughters, _charge>;

 public:
  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  void CreateBuAddPdf();
  void CreateBuPartialAddPdf();
  void CreateDeltaAddPdf();

  // pdf_Bu2Dst0h_Dst02D0neut are made in another class, but we only deal with
  // PDF in the
  // executable. Give PDF functions to retrieve them
  // It shouldn't be private, it sould be protected then it can be accessed by
  // inheriting classes

  virtual void AssignMisIdYields() {
    Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .AssignMisIdYields();
  }

  virtual RooRealVar &bkgFracGlobal_WN() const {
    return NeutralVars<_neutral>::Get(uniqueId_).bkgFracGlobal_WN();
  }

  virtual RooFormulaVar &Bs2Dst0Kst0_fracD0pi0_Delta() const {
    return NeutralVars<_neutral>::Get(uniqueId_).Bs2Dst0Kst0_fracD0pi0_Delta();
  }

  virtual RooAbsReal &N_tot_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooAbsReal &N_tot_Bu2Dst0h_WN() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2Dst0h_WN();
  }
  virtual RooAbsReal &N_tot_Bu2D0hst() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2D0hst();
  }
  virtual RooFormulaVar &N_tot_Bu2Dst0h_D0pi0_D02pik() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2Dst0h_D0pi0_D02pik();
  }
  virtual RooFormulaVar &N_tot_Bu2Dst0h_D0gamma_D02pik() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2Dst0h_D0gamma_D02pik();
  }
  virtual RooFormulaVar &N_tot_Bu2Dst0h_D0pi0_WN_D02pik() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2Dst0h_D0pi0_WN_D02pik();
  }
  virtual RooFormulaVar &N_tot_Bu2Dst0h_D0gamma_WN_D02pik() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .N_tot_Bu2Dst0h_D0gamma_WN_D02pik();
  }

  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0gamma();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_WN();
  }
  virtual RooFormulaVar &N_trueId_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bd2Dsth();
  }
  virtual RooFormulaVar &N_trueId_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2D0hst();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0hst();
  }
  virtual RooFormulaVar &N_trueId_Lb2Omegach_Lcpi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Lb2Omegach_Lcpi0();
  }
  virtual RooFormulaVar &N_trueId_Bs2Dst0Kst0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bs2Dst0Kst0();
  }
  virtual RooFormulaVar &N_trueId_Bs2D0Kst0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bs2D0Kst0();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0pi0_D02pik();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0gamma_D02pik();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_WN_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0pi0_WN_D02pik();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_WN_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0gamma_WN_D02pik();
  }

  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0h_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0h_WN();
  }
  virtual RooFormulaVar &N_misId_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bd2Dsth();
  }
  virtual RooFormulaVar &N_misId_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2D0hst();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0hst();
  }

  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0h_D0gamma();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0h_WN();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bd2Dsth();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2D0hst();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0hst();
  }
  virtual RooFormulaVar &N_trueId_Bu_Lb2Omegach_Lcpi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Lb2Omegach_Lcpi0();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bs2Dst0Kst0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bs2Dst0Kst0();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bs2D0Kst0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bs2D0Kst0();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik();
  }
  virtual RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik();
  }

  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu_Bu2Dst0h_D0gamma();
  }
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0h_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu_Bu2Dst0h_WN();
  }
  virtual RooFormulaVar &N_misId_Bu_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu_Bd2Dsth();
  }
  virtual RooFormulaVar &N_misId_Bu_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu_Bu2D0hst();
  }
  virtual RooFormulaVar &N_misId_Bu_Bu2Dst0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu_Bu2Dst0hst();
  }

  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0h_D0gamma();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0h_WN();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bd2Dsth();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2D0hst();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0hst();
  }
  virtual RooFormulaVar &N_trueId_Delta_Lb2Omegach_Lcpi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Lb2Omegach_Lcpi0();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bs2Dst0Kst0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bs2Dst0Kst0();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bs2D0Kst0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bs2D0Kst0();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik();
  }
  virtual RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik();
  }

  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Delta_Bu2Dst0h_D0gamma();
  }
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Delta_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Delta_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Delta_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0h_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Delta_Bu2Dst0h_WN();
  }
  virtual RooFormulaVar &N_misId_Delta_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Delta_Bd2Dsth();
  }
  virtual RooFormulaVar &N_misId_Delta_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Delta_Bu2D0hst();
  }
  virtual RooFormulaVar &N_misId_Delta_Bu2Dst0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Delta_Bu2Dst0hst();
  }

  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bu2Dst0h_D0gamma();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bd2Dsth();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bu2D0hst();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bu2Dst0hst();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Lb2Omegach_Lcpi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Lb2Omegach_Lcpi0();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bs2Dst0Kst0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bs2Dst0Kst0();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bs2D0Kst0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bs2D0Kst0();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik();
  }
  virtual RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik();
  }

  virtual RooFormulaVar &N_misId_BuPartial_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_BuPartial_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_misId_BuPartial_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_BuPartial_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_misId_BuPartial_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_BuPartial_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_misId_BuPartial_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_BuPartial_Bd2Dsth();
  }
  virtual RooFormulaVar &N_misId_BuPartial_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_BuPartial_Bu2D0hst();
  }
  virtual RooFormulaVar &N_misId_BuPartial_Bu2Dst0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_BuPartial_Bu2Dst0hst();
  }

  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma_WN() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooDstD0BG &pdfDelta_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_WN();
  }
  virtual RooDstD0BG &pdfDelta_Bd2Dsth() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bd2Dsth();
  }
  virtual RooDstD0BG &pdfDelta_Bu2D0hst() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .pdfDelta_Bu2D0hst();
  }
  virtual RooAbsPdf &pdfDelta_Bu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0hst();
  }
  virtual RooDstD0BG &pdfDelta_Lb2Omegach_Lcpi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Lb2Omegach_Lcpi0();
  }
  virtual RooDstD0BG &pdfDelta_Bs2D0Kst0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bs2D0Kst0();
  }
  virtual RooAddPdf &pdfDelta_Bs2Dst0Kst0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_Bs2Dst0Kst0();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0pi0_D02pik();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0gamma_D02pik();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik();
  }

  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooDstD0BG &pdfDelta_misId_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0h_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_WN();
  }
  virtual RooDstD0BG &pdfDelta_misId_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bd2Dsth();
  }
  virtual RooDstD0BG &pdfDelta_misId_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2D0hst();
  }
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0hst();
  }

  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooAddPdf &pdfBu_Bu2Dst0h_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_WN();
  }
  virtual RooAbsPdf &pdfBu_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bd2Dsth();
  }
  virtual RooAbsPdf &pdfBu_Bu2D0hst() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .pdfBu_Bu2D0hst();
  }
  virtual RooAbsPdf &pdfBu_Bu2Dst0hst() const {
    return NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
               uniqueId_)
        .pdfBu_Bu2Dst0hst();
  }
  virtual RooCBShape &pdfBu_Lb2Omegach_Lcpi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfBu_Lb2Omegach_Lcpi0();
  }
  virtual RooCBShape &pdfBu_Bs2D0Kst0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfBu_Bs2D0Kst0();
  }
  virtual RooAddPdf &pdfBu_Bs2Dst0Kst0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfBu_Bs2Dst0Kst0();
  }
  virtual RooGaussian &pdfBu_Bu2Dst0h_D0pi0_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfBu_Bu2Dst0h_D0pi0_D02pik();
  }
  virtual RooGaussian &pdfBu_Bu2Dst0h_D0gamma_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma_D02pik();
  }
  virtual RooGaussian &pdfBu_Bu2Dst0h_D0pi0_WN_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0pi0_WN_D02pik();
  }
  virtual RooGaussian &pdfBu_Bu2Dst0h_D0gamma_WN_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma_WN_D02pik();
  }

  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooAddPdf &pdfBu_misId_Bu2Dst0h_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_WN();
  }
  virtual RooAbsPdf &pdfBu_misId_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bd2Dsth();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2D0hst();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0hst();
  }

  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfBuPartial_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0pi0();
  }
  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooAbsPdf &pdfBuPartial_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooAddPdf &pdfBuPartial_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bd2Dsth();
  }
  virtual RooGaussian &pdfBuPartial_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2D0hst();
  }
  virtual RooAddPdf &pdfBuPartial_Bu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0hst();
  }
  virtual RooCBShape &pdfBuPartial_Lb2Omegach_Lcpi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfBuPartial_Lb2Omegach_Lcpi0();
  }
  virtual RooAddPdf &pdfBuPartial_Bs2D0Kst0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfBuPartial_Bs2D0Kst0();
  }
  virtual RooAddPdf &pdfBuPartial_Bs2Dst0Kst0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfBuPartial_Bs2Dst0Kst0();
  }
  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0pi0_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0pi0_D02pik();
  }
  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik();
  }

  virtual RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooCBShape &pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooCBShape &pdfBuPartial_misId_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bd2Dsth();
  }
  virtual RooCBShape &pdfBuPartial_misId_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2D0hst();
  }
  virtual RooAddPdf &pdfBuPartial_misId_Bu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2Dst0hst();
  }

  virtual RooRealVar &orEffBu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBu2Dst0h_D0gamma();
  }
  virtual RooRealVar &orEffBu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBu2Dst0h_D0pi0();
  }
  virtual RooRealVar &orEffBu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBu2Dst0h_D0gamma_WN();
  }
  virtual RooRealVar &orEffBu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &orEffBu2Dst0h_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBu2Dst0h_WN();
  }
  virtual RooRealVar &orEffBd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBd2Dsth();
  }
  virtual RooRealVar &orEffBu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBu2D0hst();
  }
  virtual RooRealVar &orEffBu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBu2Dst0hst_D0gamma();
  }
  virtual RooRealVar &orEffBu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBu2Dst0hst_D0pi0();
  }
  virtual RooFormulaVar &orEffBu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffBu2Dst0hst();
  }
  virtual RooRealVar &orEffLb2Omegach_Lcpi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).orEffLb2Omegach_Lcpi0();
  }
  virtual RooFormulaVar &orEffBs2Dst0Kst0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).orEffBs2Dst0Kst0();
  }
  virtual RooRealVar &orEffBs2D0Kst0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).orEffBs2D0Kst0();
  }

  virtual RooRealVar &orEffMisId_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bu2Dst0h_D0gamma();
  }
  virtual RooRealVar &orEffMisId_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bu2Dst0h_D0pi0();
  }
  virtual RooRealVar &orEffMisId_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooRealVar &orEffMisId_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &orEffMisId_Bu2Dst0h_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bu2Dst0h_WN();
  }
  virtual RooRealVar &orEffMisId_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bd2Dsth();
  }
  virtual RooRealVar &orEffMisId_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bu2D0hst();
  }
  virtual RooRealVar &orEffMisId_Bu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bu2Dst0hst_D0gamma();
  }
  virtual RooRealVar &orEffMisId_Bu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bu2Dst0hst_D0pi0();
  }
  virtual RooFormulaVar &orEffMisId_Bu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .orEffMisId_Bu2Dst0hst();
  }

  virtual RooRealVar &buEffBu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBu2Dst0h_D0gamma();
  }
  virtual RooRealVar &buEffBu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBu2Dst0h_D0pi0();
  }
  virtual RooRealVar &buEffBu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBu2Dst0h_D0gamma_WN();
  }
  virtual RooRealVar &buEffBu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &buEffBu2Dst0h_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBu2Dst0h_WN();
  }
  virtual RooRealVar &buEffBd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBd2Dsth();
  }
  virtual RooRealVar &buEffBu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBu2D0hst();
  }
  virtual RooRealVar &buEffBu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBu2Dst0hst_D0gamma();
  }
  virtual RooRealVar &buEffBu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBu2Dst0hst_D0pi0();
  }
  virtual RooFormulaVar &buEffBu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buEffBu2Dst0hst();
  }
  virtual RooRealVar &buEffLb2Omegach_Lcpi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).buEffLb2Omegach_Lcpi0();
  }

  virtual RooRealVar &deltaEffBu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBu2Dst0h_D0gamma();
  }
  virtual RooRealVar &deltaEffBu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBu2Dst0h_D0pi0();
  }
  virtual RooRealVar &deltaEffBu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBu2Dst0h_D0gamma_WN();
  }
  virtual RooRealVar &deltaEffBu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &deltaEffBu2Dst0h_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBu2Dst0h_WN();
  }
  virtual RooRealVar &deltaEffBd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBd2Dsth();
  }
  virtual RooRealVar &deltaEffBu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBu2D0hst();
  }
  virtual RooRealVar &deltaEffBu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBu2Dst0hst_D0gamma();
  }
  virtual RooRealVar &deltaEffBu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBu2Dst0hst_D0pi0();
  }
  virtual RooFormulaVar &deltaEffBu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .deltaEffBu2Dst0hst();
  }
  virtual RooRealVar &deltaEffLb2Omegach_Lcpi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).deltaEffLb2Omegach_Lcpi0();
  }

  virtual RooRealVar &buPartialEffBu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buPartialEffBu2Dst0h_D0gamma();
  }
  virtual RooRealVar &buPartialEffBu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buPartialEffBu2Dst0h_D0pi0();
  }
  virtual RooRealVar &buPartialEffBu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buPartialEffBu2Dst0h_D0gamma_WN();
  }
  virtual RooRealVar &buPartialEffBu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buPartialEffBu2Dst0h_D0pi0_WN();
  }
  virtual RooRealVar &buPartialEffBd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buPartialEffBd2Dsth();
  }
  virtual RooRealVar &buPartialEffBu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buPartialEffBu2D0hst();
  }
  virtual RooRealVar &buPartialEffBu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buPartialEffBu2Dst0hst_D0gamma();
  }
  virtual RooRealVar &buPartialEffBu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buPartialEffBu2Dst0hst_D0pi0();
  }
  virtual RooFormulaVar &buPartialEffBu2Dst0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .buPartialEffBu2Dst0hst();
  }
  virtual RooRealVar &buPartialEffLb2Omegach_Lcpi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).buPartialEffLb2Omegach_Lcpi0();
  }

  // Map of PDF objects with a unique ID for each identical PDF (PDF + ID =
  // singleton)
  // This is just a parameter/argument, you can call it anything you want
  Pdf(int whateverId);
  virtual ~Pdf() {}

 private:
  // Declaring a function inside a class of const will not change any of the
  // variables inside of the object
};

// PdfBase is supposed to be general, so the template variables are not known at
// compile time. Any variables requiring a template in the constructor must
// therefore be initialised in Pdf.
// We initialise the variables in the text of the constructor as a pointer
// because otherwise we get the error of RooFit crashing we re-assigning a
// variable
// We have to do it in the text of the constructor because it's a field of
// PDFBase, not PDF
// Can't make a list of different types. Pdfs have different types because of
// the templating. They all inheret from PDFBase, so we can make a list of
// PDFBase objects
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
Pdf<_neutral, _bachelor, _daughters, _charge>::Pdf(int uniqueId)
    : PdfBase(uniqueId, _neutral, _bachelor, _daughters, _charge) {}

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::CreateBuAddPdf() {
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bu2Dst0h_D0pi0());
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_misId_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_Bu_Bu2Dst0h_D0pi0());
  if (_neutral == Neutral::gamma) {
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_Bu2Dst0h_D0gamma());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_Bu_Bu2Dst0h_D0gamma());
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bu2Dst0h_D0gamma());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Bu_Bu2Dst0h_D0gamma());
    if (_daughters == Daughters::pik) {
      PdfBase::functionsBu_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                    .pdfBu_Bu2Dst0h_D0gamma_D02pik());
      PdfBase::yieldsBu_.add(
          Yields<_neutral, _bachelor, _daughters, _charge>::Get(
              PdfBase::uniqueId_)
              .N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik());
      // PdfBase::functionsBu_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      //                               .pdfBu_Bu2Dst0h_D0gamma_WN_D02pik());
      // PdfBase::yieldsBu_.add(
      //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
      //         PdfBase::uniqueId_)
      //         .N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik());
    }
  }
  // } else {
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_Bu2Dst0h_WN());
  //   PdfBase::yieldsBu_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_trueId_Bu_Bu2Dst0h_WN());
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_misId_Bu2Dst0h_WN());
  //   PdfBase::yieldsBu_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Bu_Bu2Dst0h_WN());
  // }
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bu2Dst0h_D0pi0_WN());
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_misId_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_Bu_Bu2Dst0h_D0pi0_WN());
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_Bu2Dst0h_D0gamma_WN());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bu2Dst0h_D0gamma_WN());
  if (_neutral == Neutral::gamma ||
      (_neutral == Neutral::pi0 && _bachelor == Bachelor::k)) {
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bu2Dst0h_D0gamma_WN());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Bu_Bu2Dst0h_D0gamma_WN());
  }
  if (_daughters == Daughters::pik) {
    PdfBase::functionsBu_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                  .pdfBu_Bu2Dst0h_D0pi0_D02pik());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik());
    // PdfBase::functionsBu_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
    //                               .pdfBu_Bu2Dst0h_D0pi0_WN_D02pik());
    // PdfBase::yieldsBu_.add(
    //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
    //         PdfBase::uniqueId_)
    //         .N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik());
  }
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_Bd2Dsth());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bd2Dsth());
  PdfBase::functionsBu_.add(
      NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
          PdfBase::uniqueId_)
          .pdfBu_Bu2D0hst());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bu2D0hst());
  PdfBase::functionsBu_.add(
      NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
          PdfBase::uniqueId_)
          .pdfBu_Bu2Dst0hst());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bu2Dst0hst());
  if (_daughters == Daughters::kk) {
    PdfBase::functionsBu_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                  .pdfBu_Lb2Omegach_Lcpi0());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_Bu_Lb2Omegach_Lcpi0());
  }
  if (_bachelor == Bachelor::k) {
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bd2Dsth());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Bu_Bd2Dsth());
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bu2D0hst());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Bu_Bu2D0hst());
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bu2Dst0hst());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Bu_Bu2Dst0hst());
  }
  if (_bachelor == Bachelor::k) {
    if (_daughters != Daughters::kpi && Configuration::Get().runADS() == true) {
      std::cout << "ADS mode: include BS\n";
      PdfBase::functionsBu_.add(
          NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfBu_Bs2D0Kst0());
      PdfBase::yieldsBu_.add(
          Yields<_neutral, _bachelor, _daughters, _charge>::Get(
              PdfBase::uniqueId_)
              .N_trueId_Bu_Bs2D0Kst0());
      PdfBase::functionsBu_.add(
          NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfBu_Bs2Dst0Kst0());
      PdfBase::yieldsBu_.add(
          Yields<_neutral, _bachelor, _daughters, _charge>::Get(
              PdfBase::uniqueId_)
              .N_trueId_Bu_Bs2Dst0Kst0());
    }
  }

  PdfBase::addPdfBu_ = std::unique_ptr<RooAddPdf>(
      new RooAddPdf(("addPdfBu_" + ComposeName(PdfBase::uniqueId_, _neutral,
                                               _bachelor, _daughters, _charge))
                        .c_str(),
                    "", PdfBase::functionsBu_, PdfBase::yieldsBu_));
  // Model with constraints
  // PdfBase::prodPdfBu_ = std::unique_ptr<RooProdPdf>(new RooProdPdf(
  //     ("prodPdfBu_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
  //                                 _daughters, _charge))
  //         .c_str(),
  //     "",
  //     RooArgSet(*addPdfBu_, NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                               .constraints_argSet())));
}

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::CreateBuPartialAddPdf() {
  if (_neutral != Neutral::gamma) {
    throw std::runtime_error("Cannt call CreateBuPartialPdf() for pi0 mode.");
  }
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0h_D0gamma());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2Dst0h_D0gamma());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2Dst0h_D0pi0());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_misId_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_BuPartial_Bu2Dst0h_D0pi0());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0h_D0gamma_WN());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_BuPartial_Bu2Dst0h_D0gamma_WN());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_BuPartial_Bu2Dst0h_D0pi0_WN());
  if (_daughters == Daughters::pik) {
    PdfBase::functionsBuPartial_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfBuPartial_Bu2Dst0h_D0pi0_D02pik());
    PdfBase::yieldsBuPartial_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik());
    // PdfBase::functionsBuPartial_.add(
    //     NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
    //         .pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik());
    // PdfBase::yieldsBuPartial_.add(
    //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
    //         PdfBase::uniqueId_)
    //         .N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik());
  }
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bd2Dsth());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bd2Dsth());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2D0hst());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2D0hst());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0hst());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2Dst0hst());
  if (_daughters == Daughters::kk) {
    PdfBase::functionsBuPartial_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfBuPartial_Lb2Omegach_Lcpi0());
    PdfBase::yieldsBuPartial_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_BuPartial_Lb2Omegach_Lcpi0());
  }
  if (_bachelor == Bachelor::k) {
    PdfBase::functionsBuPartial_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBuPartial_misId_Bd2Dsth());
    PdfBase::yieldsBuPartial_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_BuPartial_Bd2Dsth());
    PdfBase::functionsBuPartial_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBuPartial_misId_Bu2D0hst());
    PdfBase::yieldsBuPartial_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_BuPartial_Bu2D0hst());
    PdfBase::functionsBuPartial_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBuPartial_misId_Bu2Dst0hst());
    PdfBase::yieldsBuPartial_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_BuPartial_Bu2Dst0hst());
  }
  if (_bachelor == Bachelor::k) {
    if (_daughters != Daughters::kpi && Configuration::Get().runADS() == true) {
      std::cout << "ADS mode: include BS\n";
      PdfBase::functionsBuPartial_.add(
          NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
              .pdfBuPartial_Bs2D0Kst0());
      PdfBase::yieldsBuPartial_.add(
          Yields<_neutral, _bachelor, _daughters, _charge>::Get(
              PdfBase::uniqueId_)
              .N_trueId_BuPartial_Bs2D0Kst0());
      PdfBase::functionsBuPartial_.add(
          NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
              .pdfBuPartial_Bs2Dst0Kst0());
      PdfBase::yieldsBuPartial_.add(
          Yields<_neutral, _bachelor, _daughters, _charge>::Get(
              PdfBase::uniqueId_)
              .N_trueId_BuPartial_Bs2Dst0Kst0());
    }
  }

  PdfBase::addPdfBuPartial_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("addPdfBuPartial_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                                        _daughters, _charge))
          .c_str(),
      "", PdfBase::functionsBuPartial_, PdfBase::yieldsBuPartial_));
  // Model with constraints
  // PdfBase::prodPdfBuPartial_ = std::unique_ptr<RooProdPdf>(new RooProdPdf(
  //     ("prodPdfBuPartial_" + ComposeName(PdfBase::uniqueId_, _neutral,
  //                                        _bachelor, _daughters, _charge))
  //         .c_str(),
  //     "",
  //     RooArgSet(*addPdfBuPartial_,
  //               NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                   .constraints_argSet())));
}

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::CreateDeltaAddPdf() {
  PdfBase::functionsDelta_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfDelta_Bu2Dst0h_D0pi0());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bu2Dst0h_D0pi0());
  PdfBase::functionsDelta_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfDelta_misId_Bu2Dst0h_D0pi0());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_Delta_Bu2Dst0h_D0pi0());
  if (_neutral == Neutral::gamma) {
    PdfBase::functionsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfDelta_Bu2Dst0h_D0gamma());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_Delta_Bu2Dst0h_D0gamma());
    PdfBase::functionsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bu2Dst0h_D0gamma());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Delta_Bu2Dst0h_D0gamma());
    if (_daughters == Daughters::pik) {
      PdfBase::functionsDelta_.add(
          NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
              .pdfDelta_Bu2Dst0h_D0gamma_D02pik());
      PdfBase::yieldsDelta_.add(
          Yields<_neutral, _bachelor, _daughters, _charge>::Get(
              PdfBase::uniqueId_)
              .N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik());
      // PdfBase::functionsDelta_.add(
      //     NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
      //         .pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik());
      // PdfBase::yieldsDelta_.add(
      //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
      //         PdfBase::uniqueId_)
      //         .N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik());
    }
  }
  // } else {
  //   PdfBase::functionsDelta_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfDelta_Bu2Dst0h_WN());
  //   PdfBase::yieldsDelta_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_trueId_Delta_Bu2Dst0h_WN());
  //   PdfBase::functionsDelta_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfDelta_misId_Bu2Dst0h_WN());
  //   PdfBase::yieldsDelta_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Delta_Bu2Dst0h_WN());
  // }
  PdfBase::functionsDelta_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfDelta_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bu2Dst0h_D0pi0_WN());
  PdfBase::functionsDelta_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfDelta_misId_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_Delta_Bu2Dst0h_D0pi0_WN());
  PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                   .pdfDelta_Bu2Dst0h_D0gamma_WN());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bu2Dst0h_D0gamma_WN());
  if (_neutral == Neutral::gamma ||
      (_neutral == Neutral::pi0 && _bachelor == Bachelor::k)) {
    PdfBase::functionsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bu2Dst0h_D0gamma_WN());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Delta_Bu2Dst0h_D0gamma_WN());
  }
  if (_daughters == Daughters::pik) {
    PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                     .pdfDelta_Bu2Dst0h_D0pi0_D02pik());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik());
    // PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
    //                                  .pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik());
    // PdfBase::yieldsDelta_.add(
    //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
    //         PdfBase::uniqueId_)
    //         .N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik());
  }
  PdfBase::functionsDelta_.add(
      NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_Bd2Dsth());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bd2Dsth());
  PdfBase::functionsDelta_.add(
      NeutralBachelorDaughtersVars<_neutral, _bachelor, _daughters>::Get(
          PdfBase::uniqueId_)
          .pdfDelta_Bu2D0hst());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bu2D0hst());
  PdfBase::functionsDelta_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfDelta_Bu2Dst0hst());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bu2Dst0hst());
  if (_daughters == Daughters::kk) {
    PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                     .pdfDelta_Lb2Omegach_Lcpi0());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_Delta_Lb2Omegach_Lcpi0());
  }
  if (_bachelor == Bachelor::k) {
    PdfBase::functionsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bd2Dsth());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Delta_Bd2Dsth());
    PdfBase::functionsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bu2D0hst());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Delta_Bu2D0hst());
    PdfBase::functionsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bu2Dst0hst());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Delta_Bu2Dst0hst());
  }
  if (_bachelor == Bachelor::k) {
    if (_daughters != Daughters::kpi && Configuration::Get().runADS() == true) {
      std::cout << "ADS mode: include BS\n";
      PdfBase::functionsDelta_.add(
          NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_Bs2D0Kst0());
      PdfBase::yieldsDelta_.add(
          Yields<_neutral, _bachelor, _daughters, _charge>::Get(
              PdfBase::uniqueId_)
              .N_trueId_Delta_Bs2D0Kst0());
      PdfBase::functionsDelta_.add(
          NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
              .pdfDelta_Bs2Dst0Kst0());
      PdfBase::yieldsDelta_.add(
          Yields<_neutral, _bachelor, _daughters, _charge>::Get(
              PdfBase::uniqueId_)
              .N_trueId_Delta_Bs2Dst0Kst0());
    }
  }

  PdfBase::addPdfDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("addPdfDelta_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                                    _daughters, _charge))
          .c_str(),
      "", PdfBase::functionsDelta_, PdfBase::yieldsDelta_));
  // Model with constraints
  // PdfBase::prodPdfDelta_ = std::unique_ptr<RooProdPdf>(new RooProdPdf(
  //     ("prodPdfDelta_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
  //                                    _daughters, _charge))
  //         .c_str(),
  //     "",
  //     RooArgSet(*addPdfDelta_, NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                                  .constraints_argSet())));
}
