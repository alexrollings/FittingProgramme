#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
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
  RooRealVar &Bu2Dst0h_D0gamma_meanDelta() {
    return Bu2Dst0h_D0gamma_meanDelta_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_sigmaDelta() {
    return Bu2Dst0h_D0gamma_sigmaDelta_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_a1Delta() { return Bu2Dst0h_D0gamma_a1Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_a2Delta() { return Bu2Dst0h_D0gamma_a2Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_n1Delta() { return Bu2Dst0h_D0gamma_n1Delta_; }
  RooRealVar &Bu2Dst0h_D0gamma_n2Delta() { return Bu2Dst0h_D0gamma_n2Delta_; }
  RooCBShape &pdf1Delta_Bu2Dst0h_D0gamma() {
    return pdf1Delta_Bu2Dst0h_D0gamma_;
  }
  RooCBShape &pdf2Delta_Bu2Dst0h_D0gamma() {
    return pdf2Delta_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_fracPdf1Delta() {
    return Bu2Dst0h_D0gamma_fracPdf1Delta_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_thresholdDelta() {
    return Bu2Dst0h_D0gamma_thresholdDelta_;
  }
  RooRealVar &Bu2Dst0h_D0gamma_aDelta() { return Bu2Dst0h_D0gamma_aDelta_; }
  RooRealVar &Bu2Dst0h_D0gamma_bDelta() { return Bu2Dst0h_D0gamma_bDelta_; }
  RooRealVar &Bu2Dst0h_D0gamma_cDelta() { return Bu2Dst0h_D0gamma_cDelta_; }
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
  RooRealVar &orEffBu2Dst0h_D0gamma() { return orEffBu2Dst0h_D0gamma_; }
  RooRealVar &boxEffBu2Dst0h_D0gamma() { return boxEffBu2Dst0h_D0gamma_; }
  RooRealVar &buDeltaCutEffBu2Dst0h_D0gamma() {
    return buDeltaCutEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaCutEffBu2Dst0h_D0gamma() {
    return deltaCutEffBu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaPartialCutEffBu2Dst0h_D0gamma() {
    return deltaPartialCutEffBu2Dst0h_D0gamma_;
  }
  double &fracBu2Dst0h_D0gamma() { return fracBu2Dst0h_D0gamma_; }
  double &initYieldFAVBu2Dst0h_D0gamma() {
    return initYieldFAVBu2Dst0h_D0gamma_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar &Bu2Dst0h_D0pi0_meanDelta() { return Bu2Dst0h_D0pi0_meanDelta_; }
  RooRealVar &Bu2Dst0h_D0pi0_sigmaDelta() { return Bu2Dst0h_D0pi0_sigmaDelta_; }
  RooRealVar &Bu2Dst0h_D0pi0_a1Delta() { return Bu2Dst0h_D0pi0_a1Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_a2Delta() { return Bu2Dst0h_D0pi0_a2Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_n1Delta() { return Bu2Dst0h_D0pi0_n1Delta_; }
  RooRealVar &Bu2Dst0h_D0pi0_n2Delta() { return Bu2Dst0h_D0pi0_n2Delta_; }
  RooCBShape &pdf1Delta_Bu2Dst0h_D0pi0() { return pdf1Delta_Bu2Dst0h_D0pi0_; }
  RooCBShape &pdf2Delta_Bu2Dst0h_D0pi0() { return pdf2Delta_Bu2Dst0h_D0pi0_; }
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
  RooRealVar &Bu2Dst0h_D0pi0_meanBuPartial() {
    return Bu2Dst0h_D0pi0_meanBuPartial_;
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
  RooRealVar &Bu2Dst0h_D0pi0_fracPdf1BuPartial() {
    return Bu2Dst0h_D0pi0_fracPdf1BuPartial_;
  }
  RooRealVar &orEffBu2Dst0h_D0pi0() { return orEffBu2Dst0h_D0pi0_; }
  RooRealVar &boxEffBu2Dst0h_D0pi0() { return boxEffBu2Dst0h_D0pi0_; }
  RooRealVar &buDeltaCutEffBu2Dst0h_D0pi0() {
    return buDeltaCutEffBu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaCutEffBu2Dst0h_D0pi0() { return deltaCutEffBu2Dst0h_D0pi0_; }
  RooRealVar &deltaPartialCutEffBu2Dst0h_D0pi0() {
    return deltaPartialCutEffBu2Dst0h_D0pi0_;
  }
  double &fracBu2Dst0h_D0pi0() { return fracBu2Dst0h_D0pi0_; }
  double &initYieldFAVBu2Dst0h_D0pi0() { return initYieldFAVBu2Dst0h_D0pi0_; }
  // -------------------- MIS-REC -------------------- //
  RooRealVar &MisRec_thresholdDelta() { return MisRec_thresholdDelta_; }
  RooRealVar &MisRec_aDelta() { return MisRec_aDelta_; }
  RooRealVar &MisRec_bDelta() { return MisRec_bDelta_; }
  RooRealVar &MisRec_cDelta() { return MisRec_cDelta_; }
  RooDstD0BG &pdfDelta_MisRec() { return pdfDelta_MisRec_; }
  RooDstD0BG &pdfDelta_misId_MisRec() { return pdfDelta_misId_MisRec_; }
  RooRealVar &MisRec_meanBu() { return MisRec_meanBu_; }
  RooRealVar &MisRec_aLBu() { return MisRec_aLBu_; }
  RooRealVar &MisRec_aRBu() { return MisRec_aRBu_; }
  RooRealVar &MisRec_meanBuPartial() { return MisRec_meanBuPartial_; }
  RooRealVar &MisRec_aLBuPartial() { return MisRec_aLBuPartial_; }
  RooRealVar &MisRec_aRBuPartial() { return MisRec_aRBuPartial_; }
  RooRealVar &orEffMisRec() { return orEffMisRec_; }
  RooRealVar &boxEffMisRec() { return boxEffMisRec_; }
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
  double &fracMisRec() { return fracMisRec_; }
  double &initYieldFAVMisRec() { return initYieldFAVMisRec_; }
  // -------------------- Bu2D0h -------------------- //
  RooRealVar &Bu2D0h_thresholdDelta() { return Bu2D0h_thresholdDelta_; }
  RooRealVar &Bu2D0h_aDelta() { return Bu2D0h_aDelta_; }
  RooRealVar &Bu2D0h_bDelta() { return Bu2D0h_bDelta_; }
  RooRealVar &Bu2D0h_cDelta() { return Bu2D0h_cDelta_; }
  RooDstD0BG &pdfDelta_Bu2D0h() { return pdfDelta_Bu2D0h_; }
  RooDstD0BG &pdfDelta_misId_Bu2D0h() { return pdfDelta_misId_Bu2D0h_; }
  RooRealVar &Bu2D0h_meanBu() { return Bu2D0h_meanBu_; }
  RooRealVar &Bu2D0h_aLBu() { return Bu2D0h_aLBu_; }
  RooRealVar &Bu2D0h_aRBu() { return Bu2D0h_aRBu_; }
  RooRealVar &Bu2D0h_meanBuPartial() { return Bu2D0h_meanBuPartial_; }
  RooRealVar &Bu2D0h_aLBuPartial() { return Bu2D0h_aLBuPartial_; }
  RooRealVar &Bu2D0h_aRBuPartial() { return Bu2D0h_aRBuPartial_; }
  RooRealVar &orEffBu2D0h() { return orEffBu2D0h_; }
  RooRealVar &boxEffBu2D0h() { return boxEffBu2D0h_; }
  RooRealVar &buDeltaCutEffBu2D0h() { return buDeltaCutEffBu2D0h_; }
  RooRealVar &deltaCutEffBu2D0h() { return deltaCutEffBu2D0h_; }
  RooRealVar &deltaPartialCutEffBu2D0h() { return deltaPartialCutEffBu2D0h_; }
  double &fracBu2D0h() { return fracBu2D0h_; }
  double &initYieldFAVBu2D0h() { return initYieldFAVBu2D0h_; }
  // -------------------- PART REC -------------------- //
  RooRealVar &partRec_thresholdDelta() { return partRec_thresholdDelta_; }
  RooRealVar &partRec_aDelta() { return partRec_aDelta_; }
  RooRealVar &partRec_bDelta() { return partRec_bDelta_; }
  RooRealVar &partRec_cDelta() { return partRec_cDelta_; }
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
  RooRealVar &orEffPartRec() { return orEffPartRec_; }
  RooRealVar &boxEffPartRec() { return boxEffPartRec_; }
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

  void ExtractChain(Mode mode, TChain &chain);
  void SetEfficiencies(Mode mode, RooRealVar &orEff, RooRealVar &boxEff,
                       RooRealVar &buDeltaCutEff, RooRealVar &deltaCutEff,
                       RooRealVar &deltaPartialCutEff);

 private:
  // Indicate if only used by one neutral

  int uniqueId_;
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooRealVar Bu2Dst0h_D0gamma_meanDelta_;
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
  RooRealVar orEffBu2Dst0h_D0gamma_;
  RooRealVar boxEffBu2Dst0h_D0gamma_;
  RooRealVar buDeltaCutEffBu2Dst0h_D0gamma_;
  RooRealVar deltaCutEffBu2Dst0h_D0gamma_;
  RooRealVar deltaPartialCutEffBu2Dst0h_D0gamma_;
  double fracBu2Dst0h_D0gamma_;
  double initYieldFAVBu2Dst0h_D0gamma_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar Bu2Dst0h_D0pi0_meanDelta_;
  RooRealVar Bu2Dst0h_D0pi0_sigmaDelta_;
  RooRealVar Bu2Dst0h_D0pi0_a2Delta_;
  RooRealVar Bu2Dst0h_D0pi0_a1Delta_;
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
  RooRealVar Bu2Dst0h_D0pi0_meanBuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_KpiSigmaBuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_a1BuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_a2BuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_n1BuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_n2BuPartial_;
  RooRealVar Bu2Dst0h_D0pi0_fracPdf1BuPartial_;
  RooRealVar orEffBu2Dst0h_D0pi0_;
  RooRealVar boxEffBu2Dst0h_D0pi0_;
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
  RooRealVar orEffMisRec_;
  RooRealVar boxEffMisRec_;
  RooRealVar buDeltaCutEffMisRec_;
  RooRealVar deltaCutEffMisRec_;
  RooRealVar deltaPartialCutEffMisRec_;
  double fracMisRec_Bu2Dst0h_D0gamma_;
  double fracMisRec_Bu2Dst0h_D0gamma_WN_;
  double fracMisRec_Bu2Dst0h_D0pi0_WN_;
  double fracMisRec_Bu2D0hst_;
  double fracMisRec_Bd2Dsth_;
  double fracMisRec_;
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
  RooRealVar orEffBu2D0h_;
  RooRealVar boxEffBu2D0h_;
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
  RooRealVar orEffPartRec_;
  RooRealVar boxEffPartRec_;
  RooRealVar buDeltaCutEffPartRec_;
  RooRealVar deltaCutEffPartRec_;
  RooRealVar deltaPartialCutEffPartRec_;
  double fracPartRec_Bu2Dst0hst_D0pi0_;
  double fracPartRec_Bu2Dst0hst_D0gamma_;
  double fracPartRec_;
  double initYieldFAVPartRec_;
};

// inline allows a function to be defined multiple times. Templated functions
// are implicitly inline
inline bool file_exists(const std::string &name) {
  std::ifstream infile(name);
  return infile.good();
}

inline std::vector<std::string> SplitLine(std::string const &str) {
  std::stringstream ss;
  ss.str(str);
  std::string tempString;
  std::vector<std::string> stringVector;
  // '' = char
  while (std::getline(ss, tempString, ' ')) {
    stringVector.emplace_back(tempString);
  }
  return stringVector;
}

template <Neutral neutral>
void NeutralVars<neutral>::ExtractChain(Mode mode, TChain &chain) {
  std::string modeString = EnumToString(mode);
  std::string dirString;
  // std::cout << txtFileName
  //           << " doesn't exist:\n\tCalculating and setting efficiencies
  //           for"
  //           << modeString << "...\n";
  if (mode == Mode::Bu2Dst0pi_D0gamma_WN || mode == Mode::Bu2Dst0pi_D0pi0_WN) {
    // To remove _WN for directory
    dirString = modeString.substr(0, modeString.size() - 3);
  } else {
    dirString = modeString;
  }

  std::string path;
  switch (neutral) {
    case Neutral::gamma:
      path =
          "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
          "cross_feed_removed/";
      break;
    case Neutral::pi0:
      path = "pi0/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/";
      break;
  }

  std::string inputfile_1("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2011_MagUp/" + path + modeString +
                          "_2011_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_2("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2011_MagDown/" + path + modeString +
                          "_2011_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_3("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2012_MagUp/" + path + modeString +
                          "_2012_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_4("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2012_MagDown/" + path + modeString +
                          "_2012_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_5("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2015_MagUp/" + path + modeString +
                          "_2015_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_6("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2015_MagDown/" + path + modeString +
                          "_2015_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_7("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2016_MagUp/" + path + modeString +
                          "_2016_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_8("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2016_MagDown/" + path + modeString +
                          "_2016_MagDown_BDT1_BDT2_PID_TM.root");

  chain.Add(inputfile_1.c_str());
  chain.Add(inputfile_2.c_str());
  chain.Add(inputfile_3.c_str());
  chain.Add(inputfile_4.c_str());
  chain.Add(inputfile_5.c_str());
  chain.Add(inputfile_6.c_str());
  chain.Add(inputfile_7.c_str());
  chain.Add(inputfile_8.c_str());

  if (mode != Mode::Bu2Dst0pi_D0pi0 && mode != Mode::Bu2Dst0pi_D0gamma &&
      mode != Mode::Bu2Dst0pi_D0pi0_WN && mode != Mode::Bu2Dst0pi_D0gamma_WN) {
    std::string inputfile_9("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                            dirString + "_2015_MagUp/" + path + modeString +
                            "_2015_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_10("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                             dirString + "_ReDecay_2015_MagDown/" + path +
                             modeString +
                             "_ReDecay_2015_MagDown_BDT1_BDT2_PID_TM.root");
    std::string inputfile_11("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                             dirString + "_ReDecay_2016_MagUp/" + path +
                             modeString +
                             "_ReDecay_2016_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_12("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                             dirString + "_ReDecay_2016_MagDown/" + path +
                             modeString +
                             "_ReDecay_2016_MagDown_BDT1_BDT2_PID_TM.root");
    chain.Add(inputfile_9.c_str());
    chain.Add(inputfile_10.c_str());
    chain.Add(inputfile_11.c_str());
    chain.Add(inputfile_12.c_str());
  }
}

// Function to be called in constructor of NVars, in order to construct
// efficiency RCVars
// Anything defined outside the class definition needs the scope :: operator
template <Neutral neutral>
void NeutralVars<neutral>::SetEfficiencies(Mode mode, RooRealVar &orEff,
                                           RooRealVar &boxEff,
                                           RooRealVar &buDeltaCutEff,
                                           RooRealVar &deltaCutEff,
                                           RooRealVar &deltaPartialCutEff) {
  std::string dlString = std::to_string(Configuration::Get().deltaLow());
  std::string dhString = std::to_string(Configuration::Get().deltaHigh());
  std::string blString = std::to_string(Configuration::Get().buDeltaLow());
  std::string bhString = std::to_string(Configuration::Get().buDeltaHigh());
  std::string dlPartialString;
  std::string dhPartialString;
  std::string txtFileName = "txt_efficiencies/" + EnumToString(neutral) + "_" +
                            EnumToString(mode) + "_" +
                            Configuration::Get().ReturnBoxString() + ".txt";

  if (Configuration::Get().fitBuPartial() == true) {
    dlPartialString = std::to_string(Configuration::Get().deltaPartialLow());
    dhPartialString = std::to_string(Configuration::Get().deltaPartialHigh());
  }

  // Check if txt file containing efficiencies for particular mode and box dimns
  // exists, if not, calculate eff and save in txt file
  if (!file_exists(txtFileName)) {
    std::string cutString, ttree;

    switch (neutral) {
      case Neutral::gamma:
        cutString = Configuration::Get().gammaCutString();
        ttree = "BtoDstar0h3_h1h2gammaTuple";
        break;
      case Neutral::pi0:
        cutString = Configuration::Get().pi0CutString();
        ttree = "BtoDstar0h3_h1h2Pi0RTuple";
        break;
    }

    TChain chain(ttree.c_str());
    ExtractChain(mode, chain);

    double nInitial =
        chain.GetEntries(Configuration::Get().gammaCutString().c_str());
    double nBox = chain.GetEntries((cutString + "&&Delta_M>" + dlString +
                                    "&&Delta_M<" + dhString + "&&Bu_Delta_M>" +
                                    blString + "&&Bu_Delta_M<" + bhString)
                                       .c_str());
    double nOr;
    if (Configuration::Get().fitBuPartial() == true) {
      if (Configuration::Get().fit1D() == false) {
        nOr = chain.GetEntries((cutString + "&&((Delta_M>" + dlString +
                                "&&Delta_M<" + dhString + ")||(Bu_Delta_M>" +
                                blString + "&&Bu_Delta_M<" + bhString +
                                ")||(Delta_M>" + dlPartialString +
                                "&&Delta_M<" + dhPartialString + "))")
                                   .c_str());
      } else {
        nOr = chain.GetEntries((cutString + "&&((Delta_M>" + dlString +
                                "&&Delta_M<" + dhString + ")||(Delta_M>" +
                                dlPartialString + "&&Delta_M<" +
                                dhPartialString + "))")
                                   .c_str());
      }
    } else {
      if (Configuration::Get().fit1D() == false) {
        nOr = chain.GetEntries((cutString + "&&((Delta_M>" + dlString +
                                "&&Delta_M<" + dhString + ")||(Bu_Delta_M>" +
                                blString + "&&Bu_Delta_M<" + bhString + "))")
                                   .c_str());
      } else {
        nOr = chain.GetEntries(
            (cutString + "&&Delta_M>" + dlString + "&&Delta_M<" + dhString)
                .c_str());
      }
    }
    double nBuCut = chain.GetEntries(
        (cutString + "&&Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString)
            .c_str());
    double nDeltaCut = chain.GetEntries(
        (cutString + "&&Delta_M>" + dlString + "&&Delta_M<" + dhString)
            .c_str());

    double orEffVal = nOr / nInitial;
    double boxEffVal = nBox / nInitial;
    double buDeltaCutEffVal = nBuCut / nInitial;
    double deltaCutEffVal = nDeltaCut / nInitial;

    std::ofstream outFile;
    outFile.open(txtFileName);
    outFile << "orEff " + std::to_string(orEffVal) + "\n";
    outFile << "boxEff " + std::to_string(boxEffVal) + "\n";
    outFile << "buDeltaCutEff " + std::to_string(buDeltaCutEffVal) + "\n";
    outFile << "deltaCutEff " + std::to_string(deltaCutEffVal) + "\n";

    boxEff.setVal(boxEffVal);
    buDeltaCutEff.setVal(buDeltaCutEffVal);
    deltaCutEff.setVal(deltaCutEffVal);
    orEff.setVal(orEffVal);

    if (Configuration::Get().fitBuPartial() == true) {
      double nDeltaPartialCut =
          chain.GetEntries((cutString + "&&Delta_M>" + dlPartialString +
                            "&&Delta_M<" + dhPartialString)
                               .c_str());
      double deltaPartialCutEffVal = nDeltaPartialCut / nInitial;
      outFile << "deltaPartialCutEff " + std::to_string(deltaPartialCutEffVal) +
                     "\n";
      deltaPartialCutEff.setVal(deltaPartialCutEffVal);
    }
    outFile.close();
  } else {
    //   // If exists, read in from txt file
    // std::cout << txtFileName << " exists:\n\tReading efficiencies for "
    //           << EnumToString(mode) << "...\n";
    std::ifstream inFile(txtFileName);
    // Create map to store efficiency string (label) and eff value
    std::unordered_map<std::string, double> effMap;
    std::string line;
    // Loop over lines in txt file
    while (std::getline(inFile, line)) {
      // Separate label and value (white space)
      std::vector<std::string> lineVec = SplitLine(line);
      // Add to map
      effMap.insert(
          std::pair<std::string, double>(lineVec[0], std::stod(lineVec[1])));
    }
    // Use map key to set correct efficiency values
    boxEff.setVal(effMap.at("boxEff"));
    buDeltaCutEff.setVal(effMap.at("buDeltaCutEff"));
    deltaCutEff.setVal(effMap.at("deltaCutEff"));
    orEff.setVal(effMap.at("orEff"));
    if (Configuration::Get().fitBuPartial() == true) {
      deltaPartialCutEff.setVal(effMap.at("deltaPartialCutEff"));
    }
  }
  // std::cout << "\t orEff = " << orEff.getVal() << "\n"
  //           << "\t boxEff = " << boxEff.getVal() << "\n"
  //           << "\t buDeltaCutEff = " << buDeltaCutEff.getVal() << "\n"
  //           << "\t deltaCutEff = " << deltaCutEff.getVal() << "\n"
  //           << "\t deltaPartialCutEff = " << deltaPartialCutEff.getVal() <<
  //           "\n";
}

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
