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
  NeutralVars(int uniqueId_);
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

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooRealVar &Bu2Dst0h_D0gamma_a1Delta() { return Bu2Dst0h_D0gamma_a1Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_a2Delta() { return Bu2Dst0h_D0gamma_a2Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_n1Delta() { return Bu2Dst0h_D0gamma_n1Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_n2Delta() { return Bu2Dst0h_D0gamma_n2Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_fracPdf1Delta() {
    return Bu2Dst0h_D0gamma_fracPdf1Delta_;
  }
  RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma() { return *pdfDelta_Bu2Dst0h_D0gamma_; }
  RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() {
    return *pdfDelta_misId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_meanBu() { return Bu2Dst0h_D0gamma_meanBu_; }
  RooRealVar &Bu2Dst0h_D0gamma_KpiSigmaBu() {
    return Bu2Dst0h_D0gamma_KpiSigmaBu_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_a1Bu() { return Bu2Dst0h_D0gamma_a1Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_a2Bu() { return Bu2Dst0h_D0gamma_a2Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_n1Bu() { return Bu2Dst0h_D0gamma_n1Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_n2Bu() { return Bu2Dst0h_D0gamma_n2Bu_; }
  RooRealVar &Bu2Dst0h_D0gamma_fracPdf1Bu() {
    return Bu2Dst0h_D0gamma_fracPdf1Bu_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_meanBuPartial() {
    return Bu2Dst0h_D0gamma_meanBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_aBuPartial() {
    return Bu2Dst0h_D0gamma_aBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_nBuPartial() {
    return Bu2Dst0h_D0gamma_nBuPartial_;
  }
  RooRealVar &buDeltaCutEffBu2Dst0h_D0gamma() {
    return buDeltaCutEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaCutEffBu2Dst0h_D0gamma() {
    return deltaCutEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaPartialCutEffBu2Dst0h_D0gamma() {
    return deltaPartialCutEffBu2Dst0h_D0gamma_;
  }
  double &initYieldFAVBu2Dst0h_D0gamma() {
    return initYieldFAVBu2Dst0h_D0gamma_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar &Bu2Dst0h_D0pi0_a1Delta() { return *Bu2Dst0h_D0pi0_a1Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_a2Delta() { return Bu2Dst0h_D0pi0_a2Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_n1Delta() { return Bu2Dst0h_D0pi0_n1Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_n2Delta() { return Bu2Dst0h_D0pi0_n2Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdf1Delta() {
    return Bu2Dst0h_D0pi0_fracPdf1Delta_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() { return pdfDelta_Bu2Dst0h_D0pi0_; }
  RooAddPdf &pdfDelta_misId_Bu2Dst0h_D0pi0() {
    return pdfDelta_misId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_meanBu() { return Bu2Dst0h_D0pi0_meanBu_; }
  RooRealVar &Bu2Dst0h_D0pi0_KpiSigmaBu() { return Bu2Dst0h_D0pi0_KpiSigmaBu_; }
  RooRealVar &Bu2Dst0h_D0pi0_a1Bu() { return Bu2Dst0h_D0pi0_a1Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_a2Bu() { return Bu2Dst0h_D0pi0_a2Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_n1Bu() { return Bu2Dst0h_D0pi0_n1Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_n2Bu() { return Bu2Dst0h_D0pi0_n2Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdf1Bu() { return Bu2Dst0h_D0pi0_fracPdf1Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_meanCbBuPartial() {
    return Bu2Dst0h_D0pi0_meanCbBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_meanOffsetGausBuPartial() {
    return Bu2Dst0h_D0pi0_meanOffsetGausBuPartial_;
  }
  RooFormulaVar &Bu2Dst0h_D0pi0_meanGausBuPartial() {
    return Bu2Dst0h_D0pi0_meanGausBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_21SigmaBuPartial() {
    return Bu2Dst0h_D0pi0_21SigmaBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_KpiSigmaBuPartial() {
    return Bu2Dst0h_D0pi0_KpiSigmaBuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_a1BuPartial() {
    return Bu2Dst0h_D0pi0_a1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_a2BuPartial() {
    return Bu2Dst0h_D0pi0_a2BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_n1BuPartial() {
    return Bu2Dst0h_D0pi0_n1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_n2BuPartial() {
    return Bu2Dst0h_D0pi0_n2BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdfCb1BuPartial() {
    return Bu2Dst0h_D0pi0_fracPdfCb1BuPartial_;
  }
  RooRealVar &Bu2Dst0h_D0pi0_fracPdfCb2BuPartial() {
    return Bu2Dst0h_D0pi0_fracPdfCb2BuPartial_;
  }
  RooRealVar &buDeltaCutEffBu2Dst0h_D0pi0() {
    return buDeltaCutEffBu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaCutEffBu2Dst0h_D0pi0() { return deltaCutEffBu2Dst0h_D0pi0_; }
  RooRealVar &deltaPartialCutEffBu2Dst0h_D0pi0() {
    return deltaPartialCutEffBu2Dst0h_D0pi0_;
  }
  double &initYieldFAVBu2Dst0h_D0pi0() { return initYieldFAVBu2Dst0h_D0pi0_; }
  // -------------------- MIS-REC -------------------- //
  RooDstD0BG &pdfDelta_MisRec() { return pdfDelta_MisRec_; }
  RooDstD0BG &pdfDelta_misId_MisRec() { return pdfDelta_misId_MisRec_; }
  RooRealVar &MisRec_meanBu() { return MisRec_meanBu_; }
  RooRealVar &MisRec_aLBu() { return MisRec_aLBu_; }
  RooRealVar &MisRec_aRBu() { return MisRec_aRBu_; }
  RooRealVar &MisRec_meanBuPartial() { return MisRec_meanBuPartial_; }
  RooRealVar &MisRec_aLBuPartial() { return MisRec_aLBuPartial_; }
  RooRealVar &MisRec_aRBuPartial() { return MisRec_aRBuPartial_; }
  RooRealVar &buDeltaCutEffMisRec() { return buDeltaCutEffMisRec_; }
  RooRealVar &deltaCutEffMisRec() { return deltaCutEffMisRec_; }
  RooRealVar &deltaPartialCutEffMisRec() { return deltaPartialCutEffMisRec_; }
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
  // -------------------- Bu2D0h -------------------- //
  RooDstD0BG &pdfDelta_Bu2D0h() { return pdfDelta_Bu2D0h_; }
  RooDstD0BG &pdfDelta_misId_Bu2D0h() { return pdfDelta_misId_Bu2D0h_; }
  RooRealVar &Bu2D0h_meanBu() { return Bu2D0h_meanBu_; }
  RooRealVar &Bu2D0h_aLBu() { return Bu2D0h_aLBu_; }
  RooRealVar &Bu2D0h_aRBu() { return Bu2D0h_aRBu_; }
  RooRealVar &Bu2D0h_meanBuPartial() { return Bu2D0h_meanBuPartial_; }
  RooRealVar &Bu2D0h_aLBuPartial() { return Bu2D0h_aLBuPartial_; }
  RooRealVar &Bu2D0h_aRBuPartial() { return Bu2D0h_aRBuPartial_; }
  RooRealVar &buDeltaCutEffBu2D0h() { return buDeltaCutEffBu2D0h_; }
  RooRealVar &deltaCutEffBu2D0h() { return deltaCutEffBu2D0h_; }
  RooRealVar &deltaPartialCutEffBu2D0h() { return deltaPartialCutEffBu2D0h_; }
  double &initYieldFAVBu2D0h() { return initYieldFAVBu2D0h_; }
  // -------------------- PART REC -------------------- //
  RooDstD0BG &pdfDelta_PartRec() { return pdfDelta_PartRec_; }
  RooDstD0BG &pdfDelta_misId_PartRec() { return pdfDelta_misId_PartRec_; }
  RooRealVar &partRec_D0pi0_meanBu() { return partRec_D0pi0_meanBu_; }
  RooRealVar &partRec_D0pi0_aLBu() { return partRec_D0pi0_aLBu_; }
  RooRealVar &partRec_D0pi0_aRBu() { return partRec_D0pi0_aRBu_; }
  RooRealVar &partRec_D0gamma_meanBu() { return partRec_D0gamma_meanBu_; }
  RooRealVar &partRec_D0gamma_aLBu() { return partRec_D0gamma_aLBu_; }
  RooRealVar &partRec_D0gamma_aRBu() { return partRec_D0gamma_aRBu_; }
  RooRealVar &partRec_frac_D0pi0() { return partRec_frac_D0pi0_; }
  RooRealVar &partRec_meanBuPartial() { return partRec_meanBuPartial_; }
  RooRealVar &partRec_aLBuPartial() { return partRec_aLBuPartial_; }
  RooRealVar &partRec_aRBuPartial() { return partRec_aRBuPartial_; }
  RooRealVar &buDeltaCutEffPartRec() { return buDeltaCutEffPartRec_; }
  RooRealVar &deltaCutEffPartRec() { return deltaCutEffPartRec_; }
  RooRealVar &deltaPartialCutEffPartRec() { return deltaPartialCutEffPartRec_; }
  double &fracPartRec_Bu2Dst0hst_D0pi0() {
    return fracPartRec_Bu2Dst0hst_D0pi0_;
  }
  double &fracPartRec_Bu2Dst0hst_D0gamma() {
    return fracPartRec_Bu2Dst0hst_D0gamma_;
  }
  double &fracPartRec() { return fracPartRec_; }
  double &initYieldFAVPartRec() { return initYieldFAVPartRec_; }

 private:
  // Indicate if only used by one neutral

  int uniqueId_;
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_meanDelta_;
  RooRealVar Bu2Dst0h_D0gamma_sigmaDelta_;
  RooRealVar Bu2Dst0h_D0gamma_a2Delta_;
  RooRealVar Bu2Dst0h_D0gamma_a1Delta_;
  RooRealVar Bu2Dst0h_D0gamma_n2Delta_;
  RooRealVar Bu2Dst0h_D0gamma_n1Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0gamma_;
  RooRealVar Bu2Dst0h_D0gamma_fracPdf1Delta_;
  RooRealVar Bu2Dst0h_D0gamma_thresholdDelta_;
  RooRealVar Bu2Dst0h_D0gamma_aDelta_;
  RooRealVar Bu2Dst0h_D0gamma_bDelta_;
  RooRealVar Bu2Dst0h_D0gamma_cDelta_;
  std::unique_ptr<RooAbsPdf> pdfDelta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsPdf> pdfDelta_misId_Bu2Dst0h_D0gamma_;
  RooRealVar Bu2Dst0h_D0gamma_meanBu_;
  RooRealVar Bu2Dst0h_D0gamma_KpiSigmaBu_;
  RooRealVar Bu2Dst0h_D0gamma_a1Bu_;
  RooRealVar Bu2Dst0h_D0gamma_a2Bu_;
  RooRealVar Bu2Dst0h_D0gamma_n1Bu_;
  RooRealVar Bu2Dst0h_D0gamma_n2Bu_;
  RooRealVar Bu2Dst0h_D0gamma_fracPdf1Bu_;
  RooRealVar Bu2Dst0h_D0gamma_meanBuPartial_;
  RooRealVar Bu2Dst0h_D0gamma_aBuPartial_;
  RooRealVar Bu2Dst0h_D0gamma_nBuPartial_;
  RooRealVar buDeltaCutEffBu2Dst0h_D0gamma_;
  RooRealVar deltaCutEffBu2Dst0h_D0gamma_;
  RooRealVar deltaPartialCutEffBu2Dst0h_D0gamma_;
  double fracBu2Dst0h_D0gamma_;
  double initYieldFAVBu2Dst0h_D0gamma_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_meanDelta_;
  RooRealVar Bu2Dst0h_D0pi0_sigmaDelta_;
  RooRealVar Bu2Dst0h_D0pi0_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a1Delta_;
  RooRealVar Bu2Dst0h_D0pi0_n2Delta_;
  RooRealVar Bu2Dst0h_D0pi0_n1Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0pi0_;
  RooRealVar Bu2Dst0h_D0pi0_fracPdf1Delta_;
  RooAddPdf pdfDelta_Bu2Dst0h_D0pi0_;
  RooAddPdf pdfDelta_misId_Bu2Dst0h_D0pi0_;
  RooRealVar Bu2Dst0h_D0pi0_meanBu_;
  RooRealVar Bu2Dst0h_D0pi0_KpiSigmaBu_;
  RooRealVar Bu2Dst0h_D0pi0_a1Bu_;
  RooRealVar Bu2Dst0h_D0pi0_a2Bu_;
  RooRealVar Bu2Dst0h_D0pi0_n1Bu_;
  RooRealVar Bu2Dst0h_D0pi0_n2Bu_;
  RooRealVar Bu2Dst0h_D0pi0_fracPdf1Bu_;
  RooRealVar Bu2Dst0h_D0pi0_meanCbBuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_meanOffsetGausBuPartial_;
  RooFormulaVar Bu2Dst0h_D0pi0_meanGausBuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_21SigmaBuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_KpiSigmaBuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_a1BuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_a2BuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_n1BuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_n2BuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_fracPdfCb1BuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_fracPdfCb2BuPartial_;
  RooRealVar buDeltaCutEffBu2Dst0h_D0pi0_;
  RooRealVar deltaCutEffBu2Dst0h_D0pi0_;
  RooRealVar deltaPartialCutEffBu2Dst0h_D0pi0_;
  double fracBu2Dst0h_D0pi0_;
  double initYieldFAVBu2Dst0h_D0pi0_;
  // -------------------- MIS-REC -------------------- //
  RooRealVar MisRec_thresholdDelta_;
  RooRealVar MisRec_aDelta_;
  RooRealVar MisRec_bDelta_;
  RooRealVar MisRec_cDelta_;
  RooDstD0BG pdfDelta_MisRec_;
  RooDstD0BG pdfDelta_misId_MisRec_;
  RooRealVar MisRec_meanBu_;
  RooRealVar MisRec_aLBu_;
  RooRealVar MisRec_aRBu_;
  RooRealVar MisRec_meanBuPartial_;
  RooRealVar MisRec_aLBuPartial_;
  RooRealVar MisRec_aRBuPartial_;
  RooRealVar buDeltaCutEffMisRec_;
  RooRealVar deltaCutEffMisRec_;
  RooRealVar deltaPartialCutEffMisRec_;
  double fracMisRec_Bu2Dst0h_D0gamma_;
  double fracMisRec_Bu2Dst0h_D0gamma_WN_;
  double fracMisRec_Bu2Dst0h_D0pi0_WN_;
  double fracMisRec_Bu2D0hst_;
  double fracMisRec_Bd2Dsth_;
  const double fracMisRec_;
  double initYieldFAVMisRec_;
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
  RooRealVar buDeltaCutEffBu2D0h_;
  RooRealVar deltaCutEffBu2D0h_;
  RooRealVar deltaPartialCutEffBu2D0h_;
  double fracBu2D0h_;
  double initYieldFAVBu2D0h_;
  // -------------------- PART REC -------------------- //
  RooRealVar partRec_thresholdDelta_;
  RooRealVar partRec_aDelta_;
  RooRealVar partRec_bDelta_;
  RooRealVar partRec_cDelta_;
  RooDstD0BG pdfDelta_PartRec_;
  RooDstD0BG pdfDelta_misId_PartRec_;
  RooRealVar partRec_D0pi0_meanBu_;
  RooRealVar partRec_D0pi0_aLBu_;
  RooRealVar partRec_D0pi0_aRBu_;
  RooRealVar partRec_D0gamma_meanBu_;
  RooRealVar partRec_D0gamma_aLBu_;
  RooRealVar partRec_D0gamma_aRBu_;
  RooRealVar partRec_frac_D0pi0_;
  RooRealVar partRec_meanBuPartial_;
  RooRealVar partRec_aLBuPartial_;
  RooRealVar partRec_aRBuPartial_;
  RooRealVar buDeltaCutEffPartRec_;
  RooRealVar deltaCutEffPartRec_;
  RooRealVar deltaPartialCutEffPartRec_;
  double fracPartRec_Bu2Dst0hst_D0pi0_;
  double fracPartRec_Bu2Dst0hst_D0gamma_;
  double fracPartRec_;
  double initYieldFAVPartRec_;
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
