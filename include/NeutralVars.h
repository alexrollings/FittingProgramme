#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooDstD0BG.h"
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
  static This_t &Get(int uniqueId) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId))
               .first;
    }
    return *it->second;
  }

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  // -------------------- PDF SHAPES -------------------- //
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooRealVar &Bu2Dst0h_D0gamma_a1Delta() { return *Bu2Dst0h_D0gamma_a1Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_a2Delta() { return *Bu2Dst0h_D0gamma_a2Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_n1Delta() { return *Bu2Dst0h_D0gamma_n1Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_n2Delta() { return *Bu2Dst0h_D0gamma_n2Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_fracPdf1Delta() {
    return *Bu2Dst0h_D0gamma_fracPdf1Delta_;
  }
  RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma() { return *pdfDelta_Bu2Dst0h_D0gamma_; }
  RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() {
    return *pdfDelta_misId_Bu2Dst0h_D0gamma_;
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
  RooRealVar &Bu2Dst0h_D0gamma_aBuPartial() {
    return *Bu2Dst0h_D0gamma_aBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_nBuPartial() {
    return *Bu2Dst0h_D0gamma_nBuPartial_;
  }
  // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
  RooCBShape &pdfBu_Bu2Dst0h_D0gamma_FAVasSUP() {
    return pdfBu_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP() {
    return pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar &Bu2Dst0h_D0pi0_a1Delta() { return *Bu2Dst0h_D0pi0_a1Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_a2Delta() { return *Bu2Dst0h_D0pi0_a2Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_n1Delta() { return *Bu2Dst0h_D0pi0_n1Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_n2Delta() { return *Bu2Dst0h_D0pi0_n2Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdf1Delta() {
    return *Bu2Dst0h_D0pi0_fracPdf1Delta_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() { return pdfDelta_Bu2Dst0h_D0pi0_; }
  RooAddPdf &pdfDelta_misId_Bu2Dst0h_D0pi0() {
    return pdfDelta_misId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_meanBu() { return *Bu2Dst0h_D0pi0_meanBu_; }
  RooRealVar &Bu2Dst0h_D0pi0_KpiSigmaBu() { return *Bu2Dst0h_D0pi0_KpiSigmaBu_; }
  RooRealVar &Bu2Dst0h_D0pi0_a1Bu() { return *Bu2Dst0h_D0pi0_a1Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_a2Bu() { return *Bu2Dst0h_D0pi0_a2Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_n1Bu() { return *Bu2Dst0h_D0pi0_n1Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_n2Bu() { return *Bu2Dst0h_D0pi0_n2Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdf1Bu() { return *Bu2Dst0h_D0pi0_fracPdf1Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_meanCbBuPartial() {
    return *Bu2Dst0h_D0pi0_meanCbBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_meanOffsetGausBuPartial() {
    return *Bu2Dst0h_D0pi0_meanOffsetGausBuPartial_;
  }
  RooFormulaVar &Bu2Dst0h_D0pi0_meanGausBuPartial() {
    return Bu2Dst0h_D0pi0_meanGausBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_21SigmaBuPartial() {
    return *Bu2Dst0h_D0pi0_21SigmaBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_KpiSigmaBuPartial() {
    return *Bu2Dst0h_D0pi0_KpiSigmaBuPartial_;
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
  RooRealVar &Bu2Dst0h_D0pi0_fracPdfCb1BuPartial() {
    return *Bu2Dst0h_D0pi0_fracPdfCb1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdfCb2BuPartial() {
    return *Bu2Dst0h_D0pi0_fracPdfCb2BuPartial_;
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

  // -------------------- Correct ID BOX EFFs -------------------- //
  RooRealVar &buDeltaCutEffBu2Dst0h_D0gamma() {
    return *buDeltaCutEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP() {
    return *buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooRealVar &buDeltaCutEffBu2Dst0h_D0pi0() {
    return *buDeltaCutEffBu2Dst0h_D0pi0_;
  }
  RooRealVar &buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP() {
    return *buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooRealVar &buDeltaCutEffMisRec() { return *buDeltaCutEffMisRec_; }
  RooRealVar &buDeltaCutEffBu2D0h() { return *buDeltaCutEffBu2D0h_; }
  RooRealVar &buDeltaCutEffPartRec() { return *buDeltaCutEffPartRec_; }
  RooRealVar &deltaCutEffBu2Dst0h_D0gamma() {
    return *deltaCutEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaCutEffBu2Dst0h_D0gamma_FAVasSUP() {
    return *deltaCutEffBu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooRealVar &deltaCutEffBu2Dst0h_D0pi0() {
    return *deltaCutEffBu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaCutEffBu2Dst0h_D0pi0_FAVasSUP() {
    return *deltaCutEffBu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooRealVar &deltaCutEffMisRec() { return *deltaCutEffMisRec_; }
  RooRealVar &deltaCutEffBu2D0h() { return *deltaCutEffBu2D0h_; }
  RooRealVar &deltaCutEffPartRec() { return *deltaCutEffPartRec_; }
  RooRealVar &deltaPartialCutEffBu2Dst0h_D0gamma() {
    return *deltaPartialCutEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaPartialCutEffBu2Dst0h_D0pi0() {
    return *deltaPartialCutEffBu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP() {
    return *deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooRealVar &deltaPartialCutEffMisRec() { return *deltaPartialCutEffMisRec_; }
  RooRealVar &deltaPartialCutEffBu2D0h() { return *deltaPartialCutEffBu2D0h_; }
  RooRealVar &deltaPartialCutEffPartRec() {
    return *deltaPartialCutEffPartRec_;
  }

  // -------------Expected yields and relative fractions w.r.t. sig -------------//
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

  // -------------------- CP Observables -------------------- //
  RooAbsReal &R_CP_Bu2Dst0h_D0gamma_Blind() { return *R_CP_Bu2Dst0h_D0gamma_Blind_; }
  RooAbsReal &R_CP_Bu2Dst0h_D0pi0_Blind() { return *R_CP_Bu2Dst0h_D0pi0_Blind_; }
  RooAbsReal &R_CP_Bu2Dst0h_D0gamma() { return *R_CP_Bu2Dst0h_D0gamma_; }
  RooAbsReal &R_CP_Bu2Dst0h_D0pi0() { return *R_CP_Bu2Dst0h_D0pi0_; }

 private:
  // Indicate if only used by one neutral

  int uniqueId_;
  // -------------------- PDF SHAPES -------------------- //
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_meanDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_sigmaDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_a1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_n1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_n2Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_fracPdf1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_aDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_bDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_cDelta_;
  std::unique_ptr<RooAbsPdf> pdfDelta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsPdf> pdfDelta_misId_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_a2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_n1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_n2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_aBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_nBuPartial_;
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
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_sigmaDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n2Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_fracPdf1Delta_;
  RooAddPdf pdfDelta_Bu2Dst0h_D0pi0_;
  RooAddPdf pdfDelta_misId_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_KpiSigmaBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_fracPdf1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_meanCbBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_meanOffsetGausBuPartial_;
  RooFormulaVar Bu2Dst0h_D0pi0_meanGausBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_21SigmaBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_KpiSigmaBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a2BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n2BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_fracPdfCb1BuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_fracPdfCb2BuPartial_;
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
  // -------------------- Correct ID BOX EFFs -------------------- //
  std::shared_ptr<RooRealVar> buDeltaCutEffBu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooRealVar> buDeltaCutEffBu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooRealVar> buDeltaCutEffMisRec_;
  std::shared_ptr<RooRealVar> buDeltaCutEffBu2D0h_;
  std::shared_ptr<RooRealVar> buDeltaCutEffPartRec_;
  std::shared_ptr<RooRealVar> deltaCutEffBu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> deltaCutEffBu2Dst0h_D0gamma_FAVasSUP_;
  std::shared_ptr<RooRealVar> deltaCutEffBu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> deltaCutEffBu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooRealVar> deltaCutEffMisRec_;
  std::shared_ptr<RooRealVar> deltaCutEffBu2D0h_;
  std::shared_ptr<RooRealVar> deltaCutEffPartRec_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffBu2Dst0h_D0gamma_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffBu2Dst0h_D0pi0_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffMisRec_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffBu2D0h_;
  std::shared_ptr<RooRealVar> deltaPartialCutEffPartRec_;
  // -------------Expected yields and relative fractions w.r.t. sig -------------//
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
  // -------------------- CP Observables -------------------- //
  std::shared_ptr<RooRealVar> R_CP_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> R_CP_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> R_CP_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> R_CP_Bu2Dst0h_D0pi0_;

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
