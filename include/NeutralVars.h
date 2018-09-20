#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "RooDstD0BG.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooCruijff.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooFormulaVar.h"
#include "RooConstVar.h"

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
  RooRealVar &meanDelta_Bu2Dst0h_Dst02D0pi0() {
    return meanDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &sigmaRDelta_Bu2Dst0h_Dst02D0pi0() {
    return sigmaRDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &fracSigmaDelta_Bu2Dst0h_Dst02D0pi0() {
    return fracSigmaDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooFormulaVar &sigmaLDelta_Bu2Dst0h_Dst02D0pi0() {
    return sigmaLDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooConstVar &aLDelta_Bu2Dst0h_Dst02D0pi0() {
    return aLDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooConstVar &aRDelta_Bu2Dst0h_Dst02D0pi0() {
    return aRDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooCruijff &pdfDelta_Bu2Dst0h_Dst02D0pi0() {
    return pdfDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a0MeanBu_Bu2Dst0h_Dst02D0pi0() {
    return a0MeanBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a1MeanBu_Bu2Dst0h_Dst02D0pi0() {
    return a1MeanBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &a2MeanBu_Bu2Dst0h_Dst02D0pi0() {
    return a2MeanBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooPolyVar &meanBu_Bu2Dst0h_Dst02D0pi0() {
    return meanBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &fracSigmaBu_Bu2Dst0h_Dst02D0pi0() {
    return fracSigmaBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &aLBu_Bu2Dst0h_Dst02D0pi0() {
    return aLBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &aRBu_Bu2Dst0h_Dst02D0pi0() {
    return aRBu_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0() {
    return ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_;
  }
  RooConstVar &relativeBuWidth_Bu2Dst0h_Dst02D0pi0() {
    return relativeBuWidth_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &meanDelta_Bu2Dst0h_Dst02D0gamma() {
    return meanDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &sigmaRDelta_Bu2Dst0h_Dst02D0gamma() {
    return sigmaRDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &fracSigmaDelta_Bu2Dst0h_Dst02D0gamma() {
    return fracSigmaDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooFormulaVar &sigmaLDelta_Bu2Dst0h_Dst02D0gamma() {
    return sigmaLDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooConstVar &aLDelta_Bu2Dst0h_Dst02D0gamma() {
    return aLDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooConstVar &aRDelta_Bu2Dst0h_Dst02D0gamma() {
    return aRDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooCruijff &pdfDelta_Bu2Dst0h_Dst02D0gamma() {
    return pdfDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a0MeanBu_Bu2Dst0h_Dst02D0gamma() {
    return a0MeanBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a1MeanBu_Bu2Dst0h_Dst02D0gamma() {
    return a1MeanBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &a2MeanBu_Bu2Dst0h_Dst02D0gamma() {
    return a2MeanBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooPolyVar &meanBu_Bu2Dst0h_Dst02D0gamma() {
    return meanBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &fracSigmaBu_Bu2Dst0h_Dst02D0gamma() {
    return fracSigmaBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &aLBu_Bu2Dst0h_Dst02D0gamma() {
    return aLBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &aRBu_Bu2Dst0h_Dst02D0gamma() {
    return aRBu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma() {
    return ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_;
  }
  RooConstVar &relativeBuWidth_Bu2Dst0h_Dst02D0gamma() {
    return relativeBuWidth_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &thresholdDelta_bkg() { return thresholdDelta_bkg_; }
  RooRealVar &aDelta_bkg() { return aDelta_bkg_; }
  RooRealVar &bDelta_bkg() { return bDelta_bkg_; }
  RooRealVar &cDelta_bkg() { return cDelta_bkg_; }
  RooDstD0BG &pdfDelta_overRec() { return pdfDelta_overRec_; }
  RooRealVar &a0MeanBu_overRec() { return a0MeanBu_overRec_; }
  RooPolyVar &meanBu_overRec() { return meanBu_overRec_; }
  RooRealVar &ratioDst0KDst0pi_overRec() { return ratioDst0KDst0pi_overRec_; }
  RooConstVar &relativeBuWidth_overRec() { return relativeBuWidth_overRec_; }
  RooRealVar &sigmaDelta_partialRec() { return sigmaDelta_partialRec_; }
  RooRealVar &fracPdfDelta_partialRec() { return fracPdfDelta_partialRec_; }
  RooDstD0BG &pdfFlatDelta_partialRec() { return pdfFlatDelta_partialRec_; }
  RooGaussian &pdfPeakDelta_partialRec() { return pdfPeakDelta_partialRec_; }
  RooAddPdf &pdfDelta_partialRec() { return pdfDelta_partialRec_; }
  RooRealVar &a0MeanBu_partialRec() { return a0MeanBu_partialRec_; }
  RooRealVar &a1MeanBu_partialRec() { return a1MeanBu_partialRec_; }
  RooRealVar &a2MeanBu_partialRec() { return a2MeanBu_partialRec_; }
  RooPolyVar &meanBu_partialRec() { return meanBu_partialRec_; }
  RooRealVar &ratioDst0KDst0pi_partialRec() {
    return ratioDst0KDst0pi_partialRec_;
  }
  RooConstVar &relativeBuWidth_partialRec() { return relativeBuWidth_partialRec_; }
  RooDstD0BG &pdfDelta_misRec() { return pdfDelta_misRec_; }
  RooRealVar &a0MeanBu_misRec() { return a0MeanBu_misRec_; }
  RooPolyVar &meanBu_misRec() { return meanBu_misRec_; }
  RooDstD0BG &pdfDelta_Comb() { return pdfDelta_Comb_; }
  RooRealVar &a0LambdaBu_Comb() { return a0LambdaBu_Comb_; }
  RooPolyVar &lambdaBu_Comb() { return lambdaBu_Comb_; }
  RooExponential &pdfBu_Comb() { return pdfBu_Comb_; }
  RooProdPdf &pdf_Comb() { return pdf_Comb_; }


 private:
  // Indicate if only used by one neutral

  int uniqueId_;
  RooRealVar meanDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar sigmaRDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar fracSigmaDelta_Bu2Dst0h_Dst02D0pi0_;
  RooFormulaVar sigmaLDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar aRDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar aLDelta_Bu2Dst0h_Dst02D0pi0_;
  RooCruijff pdfDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a0MeanBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a1MeanBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar a2MeanBu_Bu2Dst0h_Dst02D0pi0_;
  RooPolyVar meanBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar fracSigmaBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar aRBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar aLBu_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_;
  RooConstVar relativeBuWidth_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar meanDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar sigmaRDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar fracSigmaDelta_Bu2Dst0h_Dst02D0gamma_;
  RooFormulaVar sigmaLDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar aRDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar aLDelta_Bu2Dst0h_Dst02D0gamma_;
  RooCruijff pdfDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a0MeanBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a1MeanBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar a2MeanBu_Bu2Dst0h_Dst02D0gamma_;
  RooPolyVar meanBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar fracSigmaBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar aRBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar aLBu_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_;
  RooConstVar relativeBuWidth_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar thresholdDelta_bkg_;
  RooRealVar aDelta_bkg_;
  RooRealVar bDelta_bkg_;
  RooRealVar cDelta_bkg_;
  RooDstD0BG pdfDelta_overRec_;
  RooRealVar a0MeanBu_overRec_;
  RooPolyVar meanBu_overRec_;
  RooRealVar ratioDst0KDst0pi_overRec_;
  RooConstVar relativeBuWidth_overRec_;
  RooRealVar sigmaDelta_partialRec_;
  RooRealVar fracPdfDelta_partialRec_; 
  RooDstD0BG pdfFlatDelta_partialRec_;
  RooGaussian pdfPeakDelta_partialRec_;
  RooAddPdf pdfDelta_partialRec_;
  RooRealVar a0MeanBu_partialRec_;
  RooRealVar a1MeanBu_partialRec_;
  RooRealVar a2MeanBu_partialRec_;
  RooPolyVar meanBu_partialRec_;
  RooRealVar ratioDst0KDst0pi_partialRec_;
  RooConstVar relativeBuWidth_partialRec_;
  RooDstD0BG pdfDelta_misRec_;
  RooRealVar a0MeanBu_misRec_;
  RooPolyVar meanBu_misRec_;
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
