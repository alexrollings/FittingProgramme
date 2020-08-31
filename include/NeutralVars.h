#pragma once
#include "Configuration.h"
#include "Efficiencies.h"
#include "GlobalVars.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooDstD0BG.h"
#include "RooGaussian.h"
#include "RooFormulaVar.h"
#include "RooRealVar.h"
#include "TChain.h"

// Templated classes/functions mean that the compiler will automatically create
// a copy
// of the entire class for you for every permutation of template arguments it is
// called
// with. This is handy because often a lot of the code is identical except for a
// few
// details.
// However, everything the compiler needs to do so must be provided in the .h
// file,
// because otherwise it won't actually know how to cater to external callers to
// your
// class/function (unless you explicitly specialize, see below).

template <Neutral neutral>
class NeutralVars {
  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   NeutralVars<Neutral::gamma>::Get()
  //   NeutralVars<Neutral::pi0>::Get()
  // All happens automatically :-)

 public:
  // Inline Constructor
  NeutralVars(int uniqueId);
  // Inline Destructor - can both be implemented externally too:
  ~NeutralVars() {}
  // Class Human
  // {
  // public:
  //  ~Human(); //Destructor declaration
  // };
  //:: is the scoping operator. Destructor definition/implementation
  // Human::~Human();
  // { // code }
  // Invoked when a class is deleted or goes out of scope: good place to reset
  // variables/release dynamically allocated memory

  using This_t = NeutralVars<neutral>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  // -------------------- PDF SHAPES -------------------- //
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooRealVar &Bu2Dst0h_D0gamma_meanDelta() { return *Bu2Dst0h_D0gamma_meanDelta_; }
  RooRealVar &Bu2Dst0h_D0gamma_KpiSigmaDelta() { return *Bu2Dst0h_D0gamma_KpiSigmaDelta_; }
  RooRealVar &Bu2Dst0h_D0gamma_a1Delta() { return *Bu2Dst0h_D0gamma_a1Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_a2Delta() { return *Bu2Dst0h_D0gamma_a2Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_n1Delta() { return *Bu2Dst0h_D0gamma_n1Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_n2Delta() { return *Bu2Dst0h_D0gamma_n2Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_fracPdf1Delta() {
    return *Bu2Dst0h_D0gamma_fracPdf1Delta_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_meanBu() { return *Bu2Dst0h_D0gamma_meanBu_; }
  RooRealVar &Bu2Dst0h_D0gamma_KpiSigmaBu() {
    return *Bu2Dst0h_D0gamma_KpiSigmaBu_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_a1Bu() { return *Bu2Dst0h_D0gamma_a1Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_a2Bu() { return *Bu2Dst0h_D0gamma_a2Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_n1Bu() { return *Bu2Dst0h_D0gamma_n1Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_n2Bu() { return *Bu2Dst0h_D0gamma_n2Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_fracPdf1Bu() {
    return *Bu2Dst0h_D0gamma_fracPdf1Bu_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_meanBuPartial() {
    return *Bu2Dst0h_D0gamma_meanBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_sigmaBuPartial() {
    return *Bu2Dst0h_D0gamma_sigmaBuPartial_;
  }
  // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
  RooCBShape &pdfBu_Bu2Dst0h_D0gamma_FAVasSUP() {
    return pdfBu_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP() {
    return pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar &Bu2Dst0h_D0pi0_meanDelta() { return *Bu2Dst0h_D0pi0_meanDelta_; }
  RooRealVar &Bu2Dst0h_D0pi0_KpiSigmaDelta() { return *Bu2Dst0h_D0pi0_KpiSigmaDelta_; }
  RooRealVar &Bu2Dst0h_D0pi0_a1Delta() { return *Bu2Dst0h_D0pi0_a1Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_a2Delta() { return *Bu2Dst0h_D0pi0_a2Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_n1Delta() { return *Bu2Dst0h_D0pi0_n1Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_n2Delta() { return *Bu2Dst0h_D0pi0_n2Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdf1Delta() {
    return *Bu2Dst0h_D0pi0_fracPdf1Delta_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_meanBu() { return *Bu2Dst0h_D0pi0_meanBu_; }
  RooRealVar &Bu2Dst0h_D0pi0_sigmaBu() { return *Bu2Dst0h_D0pi0_sigmaBu_; }
  RooRealVar &Bu2Dst0h_D0pi0_KpiSigmaBu() {
    return *Bu2Dst0h_D0pi0_KpiSigmaBu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_a1Bu() { return *Bu2Dst0h_D0pi0_a1Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_a2Bu() { return *Bu2Dst0h_D0pi0_a2Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_n1Bu() { return *Bu2Dst0h_D0pi0_n1Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_n2Bu() { return *Bu2Dst0h_D0pi0_n2Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdf1Bu() {
    return *Bu2Dst0h_D0pi0_fracPdf1Bu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_mean1BuPartial() {
    return *Bu2Dst0h_D0pi0_mean1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_meanOffset31BuPartial() {
    return *Bu2Dst0h_D0pi0_meanOffset31BuPartial_;
  }
  RooFormulaVar &Bu2Dst0h_D0pi0_mean3BuPartial() {
    return Bu2Dst0h_D0pi0_mean3BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_KpiSigmaBuPartial() {
    return *Bu2Dst0h_D0pi0_KpiSigmaBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_sigmaRatio21BuPartial() {
    return *Bu2Dst0h_D0pi0_sigmaRatio21BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_sigmaRatio31BuPartial() {
    return *Bu2Dst0h_D0pi0_sigmaRatio31BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_a1BuPartial() {
    return *Bu2Dst0h_D0pi0_a1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_a2BuPartial() {
    return *Bu2Dst0h_D0pi0_a2BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_n1BuPartial() {
    return *Bu2Dst0h_D0pi0_n1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_n2BuPartial() {
    return *Bu2Dst0h_D0pi0_n2BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdf1BuPartial() {
    return *Bu2Dst0h_D0pi0_fracPdf1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdf2BuPartial() {
    return *Bu2Dst0h_D0pi0_fracPdf2BuPartial_;
  }
  // -------------------- Bu2Dst0h_D0pi0_FAVasSUP -------------------- //
  RooCBShape &pdfBu_Bu2Dst0h_D0pi0_FAVasSUP() {
    return pdfBu_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooAbsPdf &pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooCBShape &pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP() {
    return pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
  RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma_WN() {
    return *pdfDelta_Bu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_WN_mean1Bu() {
    return *Bu2Dst0h_D0gamma_WN_mean1Bu_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_WN_meanOffset21Bu() {
    return *Bu2Dst0h_D0gamma_WN_meanOffset21Bu_;
  }
  RooFormulaVar &Bu2Dst0h_D0gamma_WN_mean2Bu() {
    return Bu2Dst0h_D0gamma_WN_mean2Bu_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_WN_KpiSigmaBu() {
    return *Bu2Dst0h_D0gamma_WN_KpiSigmaBu_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu() {
    return *Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_WN_a1Bu() { return *Bu2Dst0h_D0gamma_WN_a1Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_WN_n1Bu() { return *Bu2Dst0h_D0gamma_WN_n1Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_WN_fracPdf1Bu() {
    return *Bu2Dst0h_D0gamma_WN_fracPdf1Bu_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_WN_meanBuPartial() {
    return *Bu2Dst0h_D0gamma_WN_meanBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial() {
    return *Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial_;
  }
  // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
  RooRealVar &Bu2Dst0h_D0pi0_WN_thresholdDelta() {
    return *Bu2Dst0h_D0pi0_WN_thresholdDelta_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_cDelta() {
    return *Bu2Dst0h_D0pi0_WN_cDelta_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_mean1Bu() {
    return *Bu2Dst0h_D0pi0_WN_mean1Bu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_meanOffset21Bu() {
    return *Bu2Dst0h_D0pi0_WN_meanOffset21Bu_;
  }
  RooFormulaVar &Bu2Dst0h_D0pi0_WN_mean2Bu() {
    return Bu2Dst0h_D0pi0_WN_mean2Bu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_KpiSigmaBu() {
    return *Bu2Dst0h_D0pi0_WN_KpiSigmaBu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu() {
    return *Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_a1Bu() {
    return *Bu2Dst0h_D0pi0_WN_a1Bu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_a2Bu() {
    return *Bu2Dst0h_D0pi0_WN_a2Bu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_n1Bu() {
    return *Bu2Dst0h_D0pi0_WN_n1Bu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_n2Bu() {
    return *Bu2Dst0h_D0pi0_WN_n2Bu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_fracPdf1Bu() {
    return *Bu2Dst0h_D0pi0_WN_fracPdf1Bu_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_mean1BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_mean1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial_;
  }
  RooFormulaVar &Bu2Dst0h_D0pi0_WN_mean3BuPartial() {
    return Bu2Dst0h_D0pi0_WN_mean3BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial() {
    return *Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_a1BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_a1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_a2BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_a2BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_n1BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_n1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_n2BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_n2BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial() {
    return *Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial_;
  }
  // -------------------- Bd2Dsth -------------------- //
  RooDstD0BG &pdfDelta_Bd2Dsth() {
    return pdfDelta_Bd2Dsth_;
  }
  RooRealVar &Bd2Dsth_mean1Bu() {
    return *Bd2Dsth_mean1Bu_;
  }
  RooRealVar &Bd2Dsth_meanOffset21Bu() {
    return *Bd2Dsth_meanOffset21Bu_;
  }
  RooFormulaVar &Bd2Dsth_mean2Bu() {
    return Bd2Dsth_mean2Bu_;
  }
  RooRealVar &Bd2Dsth_KpiSigmaBu() {
    return *Bd2Dsth_KpiSigmaBu_;
  }
  RooRealVar &Bd2Dsth_sigmaRatio21Bu() {
    return *Bd2Dsth_sigmaRatio21Bu_;
  }
  RooRealVar &Bd2Dsth_a1Bu() {
    return *Bd2Dsth_a1Bu_;
  }
  RooRealVar &Bd2Dsth_n1Bu() {
    return *Bd2Dsth_n1Bu_;
  }
  RooRealVar &Bd2Dsth_a2Bu() {
    return *Bd2Dsth_a2Bu_;
  }
  RooRealVar &Bd2Dsth_n2Bu() {
    return *Bd2Dsth_n2Bu_;
  }
  RooRealVar &Bd2Dsth_fracPdf1Bu() {
    return *Bd2Dsth_fracPdf1Bu_;
  }
  RooRealVar &Bd2Dsth_mean1BuPartial() {
    return *Bd2Dsth_mean1BuPartial_;
  }
  RooRealVar &Bd2Dsth_meanOffset21BuPartial() {
    return *Bd2Dsth_meanOffset21BuPartial_;
  }
  RooFormulaVar &Bd2Dsth_mean2BuPartial() {
    return Bd2Dsth_mean2BuPartial_;
  }
  RooRealVar &Bd2Dsth_KpiSigmaBuPartial() {
    return *Bd2Dsth_KpiSigmaBuPartial_;
  }
  RooRealVar &Bd2Dsth_sigmaRatio21BuPartial() {
    return *Bd2Dsth_sigmaRatio21BuPartial_;
  }
  RooRealVar &Bd2Dsth_a1BuPartial() {
    return *Bd2Dsth_a1BuPartial_;
  }
  RooRealVar &Bd2Dsth_n1BuPartial() {
    return *Bd2Dsth_n1BuPartial_;
  }
  RooRealVar &Bd2Dsth_a2BuPartial() {
    return *Bd2Dsth_a2BuPartial_;
  }
  RooRealVar &Bd2Dsth_n2BuPartial() {
    return *Bd2Dsth_n2BuPartial_;
  }
  RooRealVar &Bd2Dsth_fracPdf1BuPartial() {
    return *Bd2Dsth_fracPdf1BuPartial_;
  }
  // -------------------- Bu2D0hst -------------------- //
  RooDstD0BG &pdfDelta_Bu2D0hst() {
    return pdfDelta_Bu2D0hst_;
  }
  RooRealVar &Bu2D0hst_mean1Bu() {
    return *Bu2D0hst_mean1Bu_;
  }
  RooRealVar &Bu2D0hst_meanOffset21Bu() {
    return *Bu2D0hst_meanOffset21Bu_;
  }
  RooFormulaVar &Bu2D0hst_mean2Bu() {
    return Bu2D0hst_mean2Bu_;
  }
  RooRealVar &Bu2D0hst_KpiSigmaBu() {
    return *Bu2D0hst_KpiSigmaBu_;
  }
  RooRealVar &Bu2D0hst_sigmaRatio21Bu() {
    return *Bu2D0hst_sigmaRatio21Bu_;
  }
  RooRealVar &Bu2D0hst_a1Bu() {
    return *Bu2D0hst_a1Bu_;
  }
  RooRealVar &Bu2D0hst_n1Bu() {
    return *Bu2D0hst_n1Bu_;
  }
  RooRealVar &Bu2D0hst_fracPdf1Bu() {
    return *Bu2D0hst_fracPdf1Bu_;
  }
  RooRealVar &Bu2D0hst_meanBuPartial() {
    return *Bu2D0hst_meanBuPartial_;
  }
  RooRealVar &Bu2D0hst_KpiSigmaBuPartial() {
    return *Bu2D0hst_KpiSigmaBuPartial_;
  }
  // -------------------- Bu2Dst0hst_D0gamma -------------------- //
  RooGaussian &pdfDelta_Bu2Dst0hst_D0gamma() {
    return pdfDelta_Bu2Dst0hst_D0gamma_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_mean1Bu() {
    return *Bu2Dst0hst_D0gamma_mean1Bu_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_meanOffset21Bu() {
    return *Bu2Dst0hst_D0gamma_meanOffset21Bu_;
  }
  RooFormulaVar &Bu2Dst0hst_D0gamma_mean2Bu() {
    return Bu2Dst0hst_D0gamma_mean2Bu_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_KpiSigmaBu() {
    return *Bu2Dst0hst_D0gamma_KpiSigmaBu_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_sigmaRatio21Bu() {
    return *Bu2Dst0hst_D0gamma_sigmaRatio21Bu_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_a1Bu() {
    return *Bu2Dst0hst_D0gamma_a1Bu_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_n1Bu() {
    return *Bu2Dst0hst_D0gamma_n1Bu_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_a2Bu() {
    return *Bu2Dst0hst_D0gamma_a2Bu_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_n2Bu() {
    return *Bu2Dst0hst_D0gamma_n2Bu_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_fracPdf1Bu() {
    return *Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_meanBuPartial() {
    return *Bu2Dst0hst_D0gamma_meanBuPartial_;
  }
  RooRealVar &Bu2Dst0hst_D0gamma_KpiSigmaBuPartial() {
    return *Bu2Dst0hst_D0gamma_KpiSigmaBuPartial_;
  }
  // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
  RooGaussian &pdfDelta_Bu2Dst0hst_D0pi0() {
    return pdfDelta_Bu2Dst0hst_D0pi0_;
  }
  RooRealVar &Bu2Dst0hst_D0pi0_meanBu() {
    return *Bu2Dst0hst_D0pi0_meanBu_;
  }
  RooRealVar &Bu2Dst0hst_D0pi0_KpiSigmaBu() {
    return *Bu2Dst0hst_D0pi0_KpiSigmaBu_;
  }
  RooRealVar &Bu2Dst0hst_D0pi0_meanBuPartial() {
    return *Bu2Dst0hst_D0pi0_meanBuPartial_;
  }
  RooRealVar &Bu2Dst0hst_D0pi0_KpiSigmaBuPartial() {
    return *Bu2Dst0hst_D0pi0_KpiSigmaBuPartial_;
  }
  // -------------------- MIS-REC -------------------- //
  RooDstD0BG &pdfDelta_MisRec() { return pdfDelta_MisRec_; }
  RooDstD0BG &pdfDelta_misId_MisRec() { return pdfDelta_misId_MisRec_; }
  RooRealVar &MisRec_meanBu() { return *MisRec_meanBu_; }
  RooRealVar &MisRec_aLBu() { return *MisRec_aLBu_; }
  RooRealVar &MisRec_aRBu() { return *MisRec_aRBu_; }
  RooRealVar &MisRec_meanBuPartial() { return *MisRec_meanBuPartial_; }
  RooRealVar &MisRec_aLBuPartial() { return *MisRec_aLBuPartial_; }
  RooRealVar &MisRec_aRBuPartial() { return *MisRec_aRBuPartial_; }
  // -------------------- Bu2D0h -------------------- //
  RooDstD0BG &pdfDelta_Bu2D0h() { return pdfDelta_Bu2D0h_; }
  RooDstD0BG &pdfDelta_misId_Bu2D0h() { return pdfDelta_misId_Bu2D0h_; }
  RooRealVar &Bu2D0h_meanBu() { return Bu2D0h_meanBu_; }
  RooRealVar &Bu2D0h_aLBu() { return Bu2D0h_aLBu_; }
  RooRealVar &Bu2D0h_aRBu() { return Bu2D0h_aRBu_; }
  RooRealVar &Bu2D0h_meanBuPartial() { return Bu2D0h_meanBuPartial_; }
  RooRealVar &Bu2D0h_aLBuPartial() { return Bu2D0h_aLBuPartial_; }
  RooRealVar &Bu2D0h_aRBuPartial() { return Bu2D0h_aRBuPartial_; }
  // -------------------- PART REC -------------------- //
  RooDstD0BG &pdfDelta_PartRec() { return pdfDelta_PartRec_; }
  RooDstD0BG &pdfDelta_misId_PartRec() { return pdfDelta_misId_PartRec_; }
  RooRealVar &PartRec_D0pi0_meanBu() { return *PartRec_D0pi0_meanBu_; }
  RooRealVar &PartRec_D0pi0_aLBu() { return *PartRec_D0pi0_aLBu_; }
  RooRealVar &PartRec_D0pi0_aRBu() { return *PartRec_D0pi0_aRBu_; }
  RooRealVar &PartRec_D0gamma_meanBu() { return *PartRec_D0gamma_meanBu_; }
  RooRealVar &PartRec_D0gamma_aLBu() { return *PartRec_D0gamma_aLBu_; }
  RooRealVar &PartRec_D0gamma_aRBu() { return *PartRec_D0gamma_aRBu_; }
  RooRealVar &PartRec_frac_D0pi0() { return *PartRec_frac_D0pi0_; }
  RooRealVar &PartRec_meanBuPartial() { return *PartRec_meanBuPartial_; }
  RooRealVar &PartRec_aLBuPartial() { return *PartRec_aLBuPartial_; }
  RooRealVar &PartRec_aRBuPartial() { return *PartRec_aRBuPartial_; }

  // -------------Expected yields and relative fractions w.r.t. sig
  // -------------//
  double &initYieldFAVBu2Dst0h_D0gamma() {
    return initYieldFAVBu2Dst0h_D0gamma_;
  }
  double &initYieldFAVBu2Dst0h_D0pi0() { return initYieldFAVBu2Dst0h_D0pi0_; }
  double &fracMisRec_Bu2Dst0h_D0gamma() { return fracMisRec_Bu2Dst0h_D0gamma_; }
  double &fracMisRec_Bu2Dst0h_D0gamma_WN() {
    return fracMisRec_Bu2Dst0h_D0gamma_WN_;
  }
  double &fracMisRec_Bu2Dst0h_D0pi0_WN() {
    return fracMisRec_Bu2Dst0h_D0pi0_WN_;
  }
  double &fracMisRec_Bu2D0hst() { return fracMisRec_Bu2D0hst_; }
  double &fracMisRec_Bd2Dsth() { return fracMisRec_Bd2Dsth_; }
  const double &fracMisRec() { return fracMisRec_; }
  double &initYieldFAVMisRec() { return initYieldFAVMisRec_; }
  double &initYieldFAVBu2D0h() { return initYieldFAVBu2D0h_; }
  double &fracPartRec_Bu2Dst0hst_D0pi0() {
    return fracPartRec_Bu2Dst0hst_D0pi0_;
  }
  double &fracPartRec_Bu2Dst0hst_D0gamma() {
    return fracPartRec_Bu2Dst0hst_D0gamma_;
  }
  double &fracPartRec() { return fracPartRec_; }
  double &initYieldFAVPartRec() { return initYieldFAVPartRec_; }

  // -------------------- Bkg Fractions -------------------- //
  RooRealVar &bkgFracGlobal_Bu2Dst0h_D0pi0_WN() {
    return *bkgFracGlobal_Bu2Dst0h_D0pi0_WN_;
  }
  RooGaussian &constraint_bkgFracGlobal_Bu2Dst0h_D0pi0_WN() {
    return constraint_bkgFracGlobal_Bu2Dst0h_D0pi0_WN_;
  }
  RooRealVar &bkgFracGlobal_Bu2Dst0h_D0gamma_WN() {
    return *bkgFracGlobal_Bu2Dst0h_D0gamma_WN_;
  }
  RooRealVar &bkgFracFAV_Bd2Dsth() {
    return *bkgFracFAV_Bd2Dsth_;
  }
  RooRealVar &bkgFracFAV_Bu2D0hst() {
    return *bkgFracFAV_Bu2D0hst_;
  }
  RooAbsReal &bkgFracFAV_Bu2Dst0hst_D0pi0() {
    return *bkgFracFAV_Bu2Dst0hst_D0pi0_;
  }
  RooAbsReal &bkgFracFAV_Bu2Dst0hst_D0gamma() {
    return *bkgFracFAV_Bu2Dst0hst_D0gamma_;
  }


 private:
  // Indicate if only used by one neutral

  int uniqueId_;
  // -------------------- PDF SHAPES -------------------- //
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_meanDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_KpiSigmaDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_a1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_n1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_n2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_fracPdf1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_a2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_n1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_n2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_sigmaBuPartial_;
  // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_meanDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_sigmaDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_a1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_n1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_n2Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0gamma_FAVasSUP_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_fracPdf1Delta_;
  RooAddPdf pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_sigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_FAVasSUP_n1Bu_;
  RooCBShape pdfBu_Bu2Dst0h_D0gamma_FAVasSUP_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_meanDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_KpiSigmaDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_fracPdf1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_sigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_mean1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_meanOffset31BuPartial_;
  RooFormulaVar Bu2Dst0h_D0pi0_mean3BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_KpiSigmaBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_sigmaRatio21BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_sigmaRatio31BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a2BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n2BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_fracPdf1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_fracPdf2BuPartial_;
  // -------------------- Bu2Dst0h_D0gamma_WN -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_aDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_bDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_cDelta_;
  std::unique_ptr<RooAbsPdf> pdfDelta_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_mean1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_meanOffset21Bu_;
  RooFormulaVar Bu2Dst0h_D0gamma_WN_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_sigmaRatio21Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_n1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_KpiSigmaBuPartial_;
  // -------------------- Bu2Dst0h_D0pi0_WN -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_cDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_mean1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_meanOffset21Bu_;
  RooFormulaVar Bu2Dst0h_D0pi0_WN_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_sigmaRatio21Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_a2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_n1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_n2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_mean1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_meanOffset31BuPartial_;
  RooFormulaVar Bu2Dst0h_D0pi0_WN_mean3BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_KpiSigmaBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_sigmaRatio21BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_sigmaRatio31BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_a1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_a2BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_n1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_n2BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_fracPdf1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_fracPdf2BuPartial_;
  // -------------------- Bu2Dst0h_D0pi0_FAVasSUP -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_meanDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_sigma2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_a1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_n1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_n2Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0pi0_FAVasSUP_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_fracPdf1Delta_;
  std::unique_ptr<RooAbsPdf> pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_n1Bu_;
  RooCBShape pdfBu_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_sigmaBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_a1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_FAVasSUP_n1BuPartial_;
  RooCBShape pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP_;
  // -------------------- Bd2Dsth -------------------- //
  std::shared_ptr<RooRealVar> Bd2Dsth_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bd2Dsth_aDelta_;
  std::shared_ptr<RooRealVar> Bd2Dsth_bDelta_;
  std::shared_ptr<RooRealVar> Bd2Dsth_cDelta_;
  RooDstD0BG pdfDelta_Bd2Dsth_;
  std::shared_ptr<RooRealVar> Bd2Dsth_mean1Bu_;
  std::shared_ptr<RooRealVar> Bd2Dsth_meanOffset21Bu_;
  RooFormulaVar Bd2Dsth_mean2Bu_;
  std::shared_ptr<RooRealVar> Bd2Dsth_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bd2Dsth_sigmaRatio21Bu_;
  std::shared_ptr<RooRealVar> Bd2Dsth_a1Bu_;
  std::shared_ptr<RooRealVar> Bd2Dsth_n1Bu_;
  std::shared_ptr<RooRealVar> Bd2Dsth_a2Bu_;
  std::shared_ptr<RooRealVar> Bd2Dsth_n2Bu_;
  std::shared_ptr<RooRealVar> Bd2Dsth_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> Bd2Dsth_mean1BuPartial_;
  std::shared_ptr<RooRealVar> Bd2Dsth_meanOffset21BuPartial_;
  RooFormulaVar Bd2Dsth_mean2BuPartial_;
  std::shared_ptr<RooRealVar> Bd2Dsth_KpiSigmaBuPartial_;
  std::shared_ptr<RooRealVar> Bd2Dsth_sigmaRatio21BuPartial_;
  std::shared_ptr<RooRealVar> Bd2Dsth_a1BuPartial_;
  std::shared_ptr<RooRealVar> Bd2Dsth_n1BuPartial_;
  std::shared_ptr<RooRealVar> Bd2Dsth_a2BuPartial_;
  std::shared_ptr<RooRealVar> Bd2Dsth_n2BuPartial_;
  std::shared_ptr<RooRealVar> Bd2Dsth_fracPdf1BuPartial_;
  // -------------------- Bu2D0hst -------------------- //
  std::shared_ptr<RooRealVar> Bu2D0hst_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bu2D0hst_aDelta_;
  std::shared_ptr<RooRealVar> Bu2D0hst_bDelta_;
  std::shared_ptr<RooRealVar> Bu2D0hst_cDelta_;
  RooDstD0BG pdfDelta_Bu2D0hst_;
  std::shared_ptr<RooRealVar> Bu2D0hst_mean1Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_meanOffset21Bu_;
  RooFormulaVar Bu2D0hst_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_sigmaRatio21Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_n1Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> Bu2D0hst_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bu2D0hst_KpiSigmaBuPartial_;
  // -------------------- Bu2Dst0hst_D0gamma -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_meanDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_sigmaDelta_;
  RooGaussian pdfDelta_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_mean1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_meanOffset21Bu_;
  RooFormulaVar Bu2Dst0hst_D0gamma_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_sigmaRatio21Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_n1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_a2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_n2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0gamma_KpiSigmaBuPartial_;
  // -------------------- Bu2Dst0hst_D0pi0 -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0pi0_meanDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0pi0_sigmaDelta_;
  RooGaussian pdfDelta_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0pi0_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0pi0_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0pi0_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0hst_D0pi0_KpiSigmaBuPartial_;
  // -------------------- MIS-REC -------------------- //
  std::shared_ptr<RooRealVar> MisRec_thresholdDelta_;
  std::shared_ptr<RooRealVar> MisRec_aDelta_;
  std::shared_ptr<RooRealVar> MisRec_bDelta_;
  std::shared_ptr<RooRealVar> MisRec_cDelta_;
  RooDstD0BG pdfDelta_MisRec_;
  RooDstD0BG pdfDelta_misId_MisRec_;
  std::shared_ptr<RooRealVar> MisRec_meanBu_;
  std::shared_ptr<RooRealVar> MisRec_aLBu_;
  std::shared_ptr<RooRealVar> MisRec_aRBu_;
  std::shared_ptr<RooRealVar> MisRec_meanBuPartial_;
  std::shared_ptr<RooRealVar> MisRec_aLBuPartial_;
  std::shared_ptr<RooRealVar> MisRec_aRBuPartial_;
  // -------------------- Bu2D0h -------------------- //
  RooRealVar Bu2D0h_thresholdDelta_;
  RooRealVar Bu2D0h_aDelta_;
  RooRealVar Bu2D0h_bDelta_;
  RooRealVar Bu2D0h_cDelta_;
  RooDstD0BG pdfDelta_Bu2D0h_;
  RooDstD0BG pdfDelta_misId_Bu2D0h_;
  RooRealVar Bu2D0h_meanBu_;
  RooRealVar Bu2D0h_aLBu_;
  RooRealVar Bu2D0h_aRBu_;
  RooRealVar Bu2D0h_meanBuPartial_;
  RooRealVar Bu2D0h_aLBuPartial_;
  RooRealVar Bu2D0h_aRBuPartial_;
  // -------------------- PART REC -------------------- //
  std::shared_ptr<RooRealVar> PartRec_thresholdDelta_;
  std::shared_ptr<RooRealVar> PartRec_aDelta_;
  std::shared_ptr<RooRealVar> PartRec_bDelta_;
  std::shared_ptr<RooRealVar> PartRec_cDelta_;
  RooDstD0BG pdfDelta_PartRec_;
  RooDstD0BG pdfDelta_misId_PartRec_;
  std::shared_ptr<RooRealVar> PartRec_D0pi0_meanBu_;
  std::shared_ptr<RooRealVar> PartRec_D0pi0_aLBu_;
  std::shared_ptr<RooRealVar> PartRec_D0pi0_aRBu_;
  std::shared_ptr<RooRealVar> PartRec_D0gamma_meanBu_;
  std::shared_ptr<RooRealVar> PartRec_D0gamma_aLBu_;
  std::shared_ptr<RooRealVar> PartRec_D0gamma_aRBu_;
  std::shared_ptr<RooRealVar> PartRec_frac_D0pi0_;
  std::shared_ptr<RooRealVar> PartRec_meanBuPartial_;
  std::shared_ptr<RooRealVar> PartRec_aLBuPartial_;
  std::shared_ptr<RooRealVar> PartRec_aRBuPartial_;
  // -------------Expected yields and relative fractions w.r.t. sig
  // -------------//
  double fracBu2Dst0h_D0gamma_;
  double initYieldFAVBu2Dst0h_D0gamma_;
  double fracBu2Dst0h_D0pi0_;
  double initYieldFAVBu2Dst0h_D0pi0_;
  double fracMisRec_Bu2Dst0h_D0gamma_;
  double fracMisRec_Bu2Dst0h_D0gamma_WN_;
  double fracMisRec_Bu2Dst0h_D0pi0_WN_;
  double fracMisRec_Bu2D0hst_;
  double fracMisRec_Bd2Dsth_;
  const double fracMisRec_;
  double initYieldFAVMisRec_;
  double fracBu2D0h_;
  double initYieldFAVBu2D0h_;
  double fracPartRec_Bu2Dst0hst_D0pi0_;
  double fracPartRec_Bu2Dst0hst_D0gamma_;
  double fracPartRec_;
  double initYieldFAVPartRec_;
  // -------------------- Global Fractions: WN -------------------- //
  std::shared_ptr<RooRealVar> bkgFracGlobal_Bu2Dst0h_D0pi0_WN_;
  RooGaussian constraint_bkgFracGlobal_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooRealVar> bkgFracGlobal_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooRealVar> bkgFracFAV_Bd2Dsth_;
  std::shared_ptr<RooRealVar> bkgFracFAV_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> bkgFracFAV_Bu2Dst0hst_D0pi0_;
  std::shared_ptr<RooAbsReal> bkgFracFAV_Bu2Dst0hst_D0gamma_;
};

// When we DO need to specialize certain cases, we can still do that (see
// below)..g.
// Now we just need to define the constructors separately so the values are
// different
// ...by telling it exactly which specializations we are providing:
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId);
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId);
// Then we can safely put these in the .cpp-file somewhere to be linked later.
