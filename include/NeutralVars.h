#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooCruijff.h"
#include "RooDstD0BG.h"
#include "RooExponential.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"

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
  RooRealVar &Bu2Dst0h_Dst02D0pi0_meanDelta() {
    return Bu2Dst0h_Dst02D0pi0_meanDelta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_sigmaLDelta() {
    return Bu2Dst0h_Dst02D0pi0_sigmaLDelta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_sigmaRDelta() {
    return Bu2Dst0h_Dst02D0pi0_sigmaRDelta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_aLDelta() {
    return Bu2Dst0h_Dst02D0pi0_aLDelta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_aRDelta() {
    return Bu2Dst0h_Dst02D0pi0_aRDelta_;
  }
  RooRealVar &nLDelta_Bu2Dst0h_Dst02D0pi0() {
    return nLDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_nRDelta() {
    return Bu2Dst0h_Dst02D0pi0_nRDelta_;
  }
  RooCBShape &pdfLDelta_Bu2Dst0h_Dst02D0pi0() {
    return pdfLDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooCBShape &pdfRDelta_Bu2Dst0h_Dst02D0pi0() {
    return pdfRDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &fracLRDelta_Bu2Dst0h_Dst02D0pi0() {
    return fracLRDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_Dst02D0pi0() {
    return pdfDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a0Mean1Bu_Bu2Dst0h_Dst02D0pi0() {
    return a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a1Mean1Bu_Bu2Dst0h_Dst02D0pi0() {
    return a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a2Mean1Bu_Bu2Dst0h_Dst02D0pi0() {
    return a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooPolyVar &mean1Bu_Bu2Dst0h_Dst02D0pi0() {
    return mean1Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a0Mean2Bu_Bu2Dst0h_Dst02D0pi0() {
    return a0Mean2Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a1Mean2Bu_Bu2Dst0h_Dst02D0pi0() {
    return a1Mean2Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a2Mean2Bu_Bu2Dst0h_Dst02D0pi0() {
    return a2Mean2Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooPolyVar &mean2Bu_Bu2Dst0h_Dst02D0pi0() {
    return mean2Bu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a0SigmaLBu_Bu2Dst0h_Dst02D0pi0() {
    return a0SigmaLBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a1SigmaLBu_Bu2Dst0h_Dst02D0pi0() {
    return a1SigmaLBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a2SigmaLBu_Bu2Dst0h_Dst02D0pi0() {
    return a2SigmaLBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a0SigmaRBu_Bu2Dst0h_Dst02D0pi0() {
    return a0SigmaRBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a1SigmaRBu_Bu2Dst0h_Dst02D0pi0() {
    return a1SigmaRBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a2SigmaRBu_Bu2Dst0h_Dst02D0pi0() {
    return a2SigmaRBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &aLBu_Bu2Dst0h_Dst02D0pi0() { return aLBu_Bu2Dst0h_Dst02D0pi0_; }
  RooRealVar &aRBu_Bu2Dst0h_Dst02D0pi0() { return aRBu_Bu2Dst0h_Dst02D0pi0_; }
  RooRealVar &nLBu_Bu2Dst0h_Dst02D0pi0() { return nLBu_Bu2Dst0h_Dst02D0pi0_; }
  RooRealVar &nRBu_Bu2Dst0h_Dst02D0pi0() { return nRBu_Bu2Dst0h_Dst02D0pi0_; }
  RooRealVar &fracLRPdfBu_Bu2Dst0h_Dst02D0pi0() {
    return fracLRPdfBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0() {
    return ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &relativeBuWidth_Bu2Dst0h_Dst02D0pi0() {
    return relativeBuWidth_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &meanDelta_Bu2Dst0h_Dst02D0gamma() {
    return meanDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &sigmaLDelta_Bu2Dst0h_Dst02D0gamma() {
    return sigmaLDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &sigmaRDelta_Bu2Dst0h_Dst02D0gamma() {
    return sigmaRDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &aLDelta_Bu2Dst0h_Dst02D0gamma() {
    return aLDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &aRDelta_Bu2Dst0h_Dst02D0gamma() {
    return aRDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &nLDelta_Bu2Dst0h_Dst02D0gamma() {
    return nLDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &nRDelta_Bu2Dst0h_Dst02D0gamma() {
    return nRDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooCBShape &pdfLDelta_Bu2Dst0h_Dst02D0gamma() {
    return pdfLDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooCBShape &pdfRDelta_Bu2Dst0h_Dst02D0gamma() {
    return pdfRDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &fracLRDelta_Bu2Dst0h_Dst02D0gamma() {
    return fracLRDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_Dst02D0gamma() {
    return pdfDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a0Mean1Bu_Bu2Dst0h_Dst02D0gamma() {
    return a0Mean1Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a1Mean1Bu_Bu2Dst0h_Dst02D0gamma() {
    return a1Mean1Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a2Mean1Bu_Bu2Dst0h_Dst02D0gamma() {
    return a2Mean1Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooPolyVar &mean1Bu_Bu2Dst0h_Dst02D0gamma() {
    return mean1Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a0Mean2Bu_Bu2Dst0h_Dst02D0gamma() {
    return a0Mean2Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a1Mean2Bu_Bu2Dst0h_Dst02D0gamma() {
    return a1Mean2Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a2Mean2Bu_Bu2Dst0h_Dst02D0gamma() {
    return a2Mean2Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooPolyVar &mean2Bu_Bu2Dst0h_Dst02D0gamma() {
    return mean2Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a0SigmaLBu_Bu2Dst0h_Dst02D0gamma() {
    return a0SigmaLBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a1SigmaLBu_Bu2Dst0h_Dst02D0gamma() {
    return a1SigmaLBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a2SigmaLBu_Bu2Dst0h_Dst02D0gamma() {
    return a2SigmaLBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a0SigmaRBu_Bu2Dst0h_Dst02D0gamma() {
    return a0SigmaRBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a1SigmaRBu_Bu2Dst0h_Dst02D0gamma() {
    return a1SigmaRBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a2SigmaRBu_Bu2Dst0h_Dst02D0gamma() {
    return a2SigmaRBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &aLBu_Bu2Dst0h_Dst02D0gamma() {
    return aLBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &aRBu_Bu2Dst0h_Dst02D0gamma() {
    return aRBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &nLBu_Bu2Dst0h_Dst02D0gamma() {
    return nLBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &nRBu_Bu2Dst0h_Dst02D0gamma() {
    return nRBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &fracLRPdfBu_Bu2Dst0h_Dst02D0gamma() {
    return fracLRPdfBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &fracWidePdfBu_Bu2Dst0h_Dst02D0gamma() {
    return fracWidePdfBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma() {
    return ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &relativeBuWidth_Bu2Dst0h_Dst02D0gamma() {
    return relativeBuWidth_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &thresholdDelta_bkg() { return thresholdDelta_bkg_; }
  RooRealVar &aDelta_bkg() { return aDelta_bkg_; }
  RooRealVar &bDelta_bkg() { return bDelta_bkg_; }
  RooRealVar &cDelta_bkg() { return cDelta_bkg_; }
  RooDstD0BG &pdfDelta_overRec() { return pdfDelta_overRec_; }
  // RooRealVar &a0MeanBu_overRec() { return a0MeanBu_overRec_; }
  // RooPolyVar &meanBu_overRec() { return meanBu_overRec_; }
  RooRealVar &a0Mean1Bu_overRec() { return a0Mean1Bu_overRec_; }
  RooRealVar &a1Mean1Bu_overRec() { return a1Mean1Bu_overRec_; }
  RooRealVar &a2Mean1Bu_overRec() { return a2Mean1Bu_overRec_; }
  RooPolyVar &mean1Bu_overRec() { return mean1Bu_overRec_; }
  RooRealVar &a0Mean2Bu_overRec() { return a0Mean2Bu_overRec_; }
  RooRealVar &a1Mean2Bu_overRec() { return a1Mean2Bu_overRec_; }
  RooRealVar &a2Mean2Bu_overRec() { return a2Mean2Bu_overRec_; }
  RooPolyVar &mean2Bu_overRec() { return mean2Bu_overRec_; }
  RooRealVar &a0SigmaLBu_overRec() { return a0SigmaLBu_overRec_; }
  RooRealVar &a1SigmaLBu_overRec() { return a1SigmaLBu_overRec_; }
  RooRealVar &a2SigmaLBu_overRec() { return a2SigmaLBu_overRec_; }
  RooRealVar &a0SigmaRBu_overRec() { return a0SigmaRBu_overRec_; }
  RooRealVar &a1SigmaRBu_overRec() { return a1SigmaRBu_overRec_; }
  RooRealVar &a2SigmaRBu_overRec() { return a2SigmaRBu_overRec_; }
  RooRealVar &aLBu_overRec() { return aLBu_overRec_; }
  RooRealVar &aRBu_overRec() { return aRBu_overRec_; }
  RooRealVar &nLBu_overRec() { return nLBu_overRec_; }
  RooRealVar &nRBu_overRec() { return nRBu_overRec_; }
  RooRealVar &fracLRPdfBu_overRec() { return fracLRPdfBu_overRec_; }
  RooRealVar &ratioDst0KDst0pi_overRec() { return ratioDst0KDst0pi_overRec_; }
  RooRealVar &relativeBuWidth_overRec() { return relativeBuWidth_overRec_; }
  RooRealVar &meanDelta_Bu2Dst0hst_Dst02D0pi0() {
    return meanDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &sigmaLDelta_Bu2Dst0hst_Dst02D0pi0() {
    return sigmaLDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &sigmaRDelta_Bu2Dst0hst_Dst02D0pi0() {
    return sigmaRDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &aLDelta_Bu2Dst0hst_Dst02D0pi0() {
    return aLDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &aRDelta_Bu2Dst0hst_Dst02D0pi0() {
    return aRDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &nLDelta_Bu2Dst0hst_Dst02D0pi0() {
    return nLDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &nRDelta_Bu2Dst0hst_Dst02D0pi0() {
    return nRDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooCBShape &pdfLDelta_Bu2Dst0hst_Dst02D0pi0() {
    return pdfLDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooCBShape &pdfRDelta_Bu2Dst0hst_Dst02D0pi0() {
    return pdfRDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &fracLRDelta_Bu2Dst0hst_Dst02D0pi0() {
    return fracLRDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooAddPdf &pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0() {
    return pdfDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooDstD0BG &pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0() {
    return pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &fracPdfFlatDelta_Bu2Dst0hst_Dst02D0pi0() {
    return fracPdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0hst_Dst02D0pi0() {
    return pdfDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &a0MeanBu_Bu2Dst0hst_Dst02D0pi0() {
    return a0MeanBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &a1MeanBu_Bu2Dst0hst_Dst02D0pi0() {
    return a1MeanBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &a2MeanBu_Bu2Dst0hst_Dst02D0pi0() {
    return a2MeanBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &a0SigmaLBu_Bu2Dst0hst_Dst02D0pi0() {
    return a0SigmaLBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &a1SigmaLBu_Bu2Dst0hst_Dst02D0pi0() {
    return a1SigmaLBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &a2SigmaLBu_Bu2Dst0hst_Dst02D0pi0() {
    return a2SigmaLBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &a0SigmaRBu_Bu2Dst0hst_Dst02D0pi0() {
    return a0SigmaRBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &a1SigmaRBu_Bu2Dst0hst_Dst02D0pi0() {
    return a1SigmaRBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &a2SigmaRBu_Bu2Dst0hst_Dst02D0pi0() {
    return a2SigmaRBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &aLBu_Bu2Dst0hst_Dst02D0pi0() {
    return aLBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &aRBu_Bu2Dst0hst_Dst02D0pi0() {
    return aRBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &nLBu_Bu2Dst0hst_Dst02D0pi0() {
    return nLBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &nRBu_Bu2Dst0hst_Dst02D0pi0() {
    return nRBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &fracLRPdfBu_Bu2Dst0hst_Dst02D0pi0() {
    return fracLRPdfBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooPolyVar &meanBu_Bu2Dst0hst_Dst02D0pi0() {
    return meanBu_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0() {
    return ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &relativeBuWidth_Bu2Dst0hst_Dst02D0pi0() {
    return relativeBuWidth_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_meanDelta() {
    return Bu2Dst0hst_Dst02D0gamma_meanDelta_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_sigmaLDelta() {
    return Bu2Dst0hst_Dst02D0gamma_sigmaLDelta_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_sigmaRDelta() {
    return Bu2Dst0hst_Dst02D0gamma_sigmaRDelta_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_aLDelta() {
    return Bu2Dst0hst_Dst02D0gamma_aLDelta_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_aRDelta() {
    return Bu2Dst0hst_Dst02D0gamma_aRDelta_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_nLDelta() {
    return Bu2Dst0hst_Dst02D0gamma_nLDelta_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_nRDelta() {
    return Bu2Dst0hst_Dst02D0gamma_nRDelta_;
  }
  RooCBShape &pdfLDelta_Bu2Dst0hst_Dst02D0gamma() {
    return pdfLDelta_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooCBShape &pdfRDelta_Bu2Dst0hst_Dst02D0gamma() {
    return pdfRDelta_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &fracLRDelta_Bu2Dst0hst_Dst02D0gamma() {
    return fracLRDelta_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0hst_Dst02D0gamma() {
    return pdfDelta_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &a0MeanBu_Bu2Dst0hst_Dst02D0gamma() {
    return a0MeanBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &a1MeanBu_Bu2Dst0hst_Dst02D0gamma() {
    return a1MeanBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &a2MeanBu_Bu2Dst0hst_Dst02D0gamma() {
    return a2MeanBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooPolyVar &meanBu_Bu2Dst0hst_Dst02D0gamma() {
    return meanBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &a0SigmaLBu_Bu2Dst0hst_Dst02D0gamma() {
    return a0SigmaLBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &a1SigmaLBu_Bu2Dst0hst_Dst02D0gamma() {
    return a1SigmaLBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &a2SigmaLBu_Bu2Dst0hst_Dst02D0gamma() {
    return a2SigmaLBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &a0SigmaRBu_Bu2Dst0hst_Dst02D0gamma() {
    return a0SigmaRBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &a1SigmaRBu_Bu2Dst0hst_Dst02D0gamma() {
    return a1SigmaRBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &a2SigmaRBu_Bu2Dst0hst_Dst02D0gamma() {
    return a2SigmaRBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &aLBu_Bu2Dst0hst_Dst02D0gamma() {
    return aLBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &aRBu_Bu2Dst0hst_Dst02D0gamma() {
    return aRBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &nLBu_Bu2Dst0hst_Dst02D0gamma() {
    return nLBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &nRBu_Bu2Dst0hst_Dst02D0gamma() {
    return nRBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &fracLRPdfBu_Bu2Dst0hst_Dst02D0gamma() {
    return fracLRPdfBu_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma() {
    return ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &relativeBuWidth_Bu2Dst0hst_Dst02D0gamma() {
    return relativeBuWidth_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooDstD0BG &pdfDelta_misRec() { return pdfDelta_misRec_; }
  RooRealVar &a0Mean1Bu_misRec() { return a0Mean1Bu_misRec_; }
  RooRealVar &a1Mean1Bu_misRec() { return a1Mean1Bu_misRec_; }
  RooRealVar &a2Mean1Bu_misRec() { return a2Mean1Bu_misRec_; }
  RooPolyVar &mean1Bu_misRec() { return mean1Bu_misRec_; }
  RooRealVar &a0Mean2Bu_misRec() { return a0Mean2Bu_misRec_; }
  RooRealVar &a1Mean2Bu_misRec() { return a1Mean2Bu_misRec_; }
  RooRealVar &a2Mean2Bu_misRec() { return a2Mean2Bu_misRec_; }
  RooPolyVar &mean2Bu_misRec() { return mean2Bu_misRec_; }
  RooRealVar &a0Mean3Bu_misRec() { return a0Mean3Bu_misRec_; }
  RooRealVar &a1Mean3Bu_misRec() { return a1Mean3Bu_misRec_; }
  RooRealVar &a2Mean3Bu_misRec() { return a2Mean3Bu_misRec_; }
  RooPolyVar &mean3Bu_misRec() { return mean3Bu_misRec_; }
  RooRealVar &a0Sigma1Bu_misRec() { return a0Sigma1Bu_misRec_; }
  RooRealVar &a1Sigma1Bu_misRec() { return a1Sigma1Bu_misRec_; }
  RooRealVar &a2Sigma1Bu_misRec() { return a2Sigma1Bu_misRec_; }
  RooRealVar &a0Sigma2Bu_misRec() { return a0Sigma2Bu_misRec_; }
  RooRealVar &a1Sigma2Bu_misRec() { return a1Sigma2Bu_misRec_; }
  RooRealVar &a2Sigma2Bu_misRec() { return a2Sigma2Bu_misRec_; }
  RooRealVar &a0Sigma3Bu_misRec() { return a0Sigma3Bu_misRec_; }
  RooRealVar &a1Sigma3Bu_misRec() { return a1Sigma3Bu_misRec_; }
  RooRealVar &a2Sigma3Bu_misRec() { return a2Sigma3Bu_misRec_; }
  RooRealVar &frac1PdfBu_misRec() { return frac1PdfBu_misRec_; }
  RooRealVar &frac2PdfBu_misRec() { return frac2PdfBu_misRec_; }
  RooFormulaVar &frac3PdfBu_misRec() { return frac3PdfBu_misRec_; }
  RooRealVar &ratioDst0KDst0pi_misRec() { return ratioDst0KDst0pi_misRec_; }
  RooRealVar &relativeBuWidth_misRec() { return relativeBuWidth_misRec_; }
  RooDstD0BG &pdfDelta_Comb() { return pdfDelta_Comb_; }
  RooRealVar &a0LambdaBu_Comb() { return a0LambdaBu_Comb_; }
  RooPolyVar &lambdaBu_Comb() { return lambdaBu_Comb_; }
  RooExponential &pdfBu_Comb() { return pdfBu_Comb_; }
  RooProdPdf &pdf_Comb() { return pdf_Comb_; }

 private:
  // Indicate if only used by one neutral

  int uniqueId_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_meanDelta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_sigmaLDelta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_sigmaRDelta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_aRDelta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_aLDelta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_nRDelta_;
  RooRealVar nLDelta_Bu2Dst0h_Dst02D0pi0_;
  RooCBShape pdfLDelta_Bu2Dst0h_Dst02D0pi0_;
  RooCBShape pdfRDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar fracLRDelta_Bu2Dst0h_Dst02D0pi0_;
  RooAddPdf pdfDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a0Mean1Bu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a1Mean1Bu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a2Mean1Bu_Bu2Dst0h_Dst02D0pi0_;
  RooPolyVar mean1Bu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a0Mean2Bu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a1Mean2Bu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a2Mean2Bu_Bu2Dst0h_Dst02D0pi0_;
  RooPolyVar mean2Bu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a0SigmaLBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a1SigmaLBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a2SigmaLBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a0SigmaRBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a1SigmaRBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a2SigmaRBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar aLBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar aRBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar nLBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar nRBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar fracLRPdfBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar relativeBuWidth_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar meanDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar sigmaLDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar sigmaRDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar aRDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar aLDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar nRDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar nLDelta_Bu2Dst0h_Dst02D0gamma_;
  RooCBShape pdfLDelta_Bu2Dst0h_Dst02D0gamma_;
  RooCBShape pdfRDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar fracLRDelta_Bu2Dst0h_Dst02D0gamma_;
  RooAddPdf pdfDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a0Mean1Bu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a1Mean1Bu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a2Mean1Bu_Bu2Dst0h_Dst02D0gamma_;
  RooPolyVar mean1Bu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a0Mean2Bu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a1Mean2Bu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a2Mean2Bu_Bu2Dst0h_Dst02D0gamma_;
  RooPolyVar mean2Bu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a0SigmaLBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a1SigmaLBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a2SigmaLBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a0SigmaRBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a1SigmaRBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a2SigmaRBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar aLBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar aRBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar nLBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar nRBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar fracLRPdfBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar fracWidePdfBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar relativeBuWidth_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar thresholdDelta_bkg_;
  RooRealVar aDelta_bkg_;
  RooRealVar bDelta_bkg_;
  RooRealVar cDelta_bkg_;
  RooDstD0BG pdfDelta_overRec_;
  RooRealVar a0Mean1Bu_overRec_;
  RooRealVar a1Mean1Bu_overRec_;
  RooRealVar a2Mean1Bu_overRec_;
  RooPolyVar mean1Bu_overRec_;
  RooRealVar a0Mean2Bu_overRec_;
  RooRealVar a1Mean2Bu_overRec_;
  RooRealVar a2Mean2Bu_overRec_;
  RooPolyVar mean2Bu_overRec_;
  RooRealVar a0SigmaLBu_overRec_;
  RooRealVar a1SigmaLBu_overRec_;
  RooRealVar a2SigmaLBu_overRec_;
  RooRealVar a0SigmaRBu_overRec_;
  RooRealVar a1SigmaRBu_overRec_;
  RooRealVar a2SigmaRBu_overRec_;
  RooRealVar aLBu_overRec_;
  RooRealVar aRBu_overRec_;
  RooRealVar nLBu_overRec_;
  RooRealVar nRBu_overRec_;
  RooRealVar fracLRPdfBu_overRec_;
  RooRealVar ratioDst0KDst0pi_overRec_;
  RooRealVar relativeBuWidth_overRec_;
  RooRealVar meanDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar sigmaLDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar sigmaRDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar aRDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar aLDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar nRDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar nLDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooCBShape pdfLDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooCBShape pdfRDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar fracLRDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooAddPdf pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooDstD0BG pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar fracPdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooAddPdf pdfDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar a0MeanBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar a1MeanBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar a2MeanBu_Bu2Dst0hst_Dst02D0pi0_;
  RooPolyVar meanBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar a0SigmaLBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar a1SigmaLBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar a2SigmaLBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar a0SigmaRBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar a1SigmaRBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar a2SigmaRBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar aLBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar aRBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar nLBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar nRBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar fracLRPdfBu_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar relativeBuWidth_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_meanDelta_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_sigmaLDelta_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_sigmaRDelta_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_aRDelta_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_aLDelta_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_nRDelta_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_nLDelta_;
  RooCBShape pdfLDelta_Bu2Dst0hst_Dst02D0gamma_;
  RooCBShape pdfRDelta_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar fracLRDelta_Bu2Dst0hst_Dst02D0gamma_;
  RooAddPdf pdfDelta_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar a0MeanBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar a1MeanBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar a2MeanBu_Bu2Dst0hst_Dst02D0gamma_;
  RooPolyVar meanBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar a0SigmaLBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar a1SigmaLBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar a2SigmaLBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar a0SigmaRBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar a1SigmaRBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar a2SigmaRBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar aLBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar aRBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar nLBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar nRBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar fracLRPdfBu_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar relativeBuWidth_Bu2Dst0hst_Dst02D0gamma_;
  RooDstD0BG pdfDelta_misRec_;
  RooRealVar a0Mean1Bu_misRec_;
  RooRealVar a1Mean1Bu_misRec_;
  RooRealVar a2Mean1Bu_misRec_;
  RooPolyVar mean1Bu_misRec_;
  RooRealVar a0Mean2Bu_misRec_;
  RooRealVar a1Mean2Bu_misRec_;
  RooRealVar a2Mean2Bu_misRec_;
  RooPolyVar mean2Bu_misRec_;
  RooRealVar a0Mean3Bu_misRec_;
  RooRealVar a1Mean3Bu_misRec_;
  RooRealVar a2Mean3Bu_misRec_;
  RooPolyVar mean3Bu_misRec_;
  RooRealVar a0Sigma1Bu_misRec_;
  RooRealVar a1Sigma1Bu_misRec_;
  RooRealVar a2Sigma1Bu_misRec_;
  RooRealVar a0Sigma2Bu_misRec_;
  RooRealVar a1Sigma2Bu_misRec_;
  RooRealVar a2Sigma2Bu_misRec_;
  RooRealVar a0Sigma3Bu_misRec_;
  RooRealVar a1Sigma3Bu_misRec_;
  RooRealVar a2Sigma3Bu_misRec_;
  RooRealVar frac1PdfBu_misRec_;
  RooRealVar frac2PdfBu_misRec_;
  RooFormulaVar frac3PdfBu_misRec_;
  RooRealVar ratioDst0KDst0pi_misRec_;
  RooRealVar relativeBuWidth_misRec_;
  RooDstD0BG pdfDelta_Comb_;
  RooRealVar a0LambdaBu_Comb_;
  RooPolyVar lambdaBu_Comb_;
  RooExponential pdfBu_Comb_;
  RooProdPdf pdf_Comb_;
};

// When we DO need to specialize certain cases, we can still do that (see
// below)...
// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId);
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId);
// Then we can safely put these in the .cpp-file somewhere to be linked later.
