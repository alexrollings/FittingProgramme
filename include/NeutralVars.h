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
  RooRealVar &Bu2Dst0h_Dst02D0pi0_sigma1Delta() {
    return Bu2Dst0h_Dst02D0pi0_sigma1Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_sigma2Delta() {
    return Bu2Dst0h_Dst02D0pi0_sigma2Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a1Delta() {
    return Bu2Dst0h_Dst02D0pi0_a1Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a2Delta() {
    return Bu2Dst0h_Dst02D0pi0_a2Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_n1Delta() {
    return Bu2Dst0h_Dst02D0pi0_n1Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_n2Delta() {
    return Bu2Dst0h_Dst02D0pi0_n2Delta_;
  }
  RooCBShape &pdf1Delta_Bu2Dst0h_Dst02D0pi0() {
    return pdf1Delta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooCBShape &pdf2Delta_Bu2Dst0h_Dst02D0pi0() {
    return pdf2Delta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_frac1PdfDelta() {
    return Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_Dst02D0pi0() {
    return pdfDelta_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a0Mean1Bu() {
    return Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a1Mean1Bu() {
    return Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a2Mean1Bu() {
    return Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_;
  }
  RooPolyVar &Bu2Dst0h_Dst02D0pi0_mean1Bu() {
    return Bu2Dst0h_Dst02D0pi0_mean1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a0Mean2Bu() {
    return Bu2Dst0h_Dst02D0pi0_a0Mean2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a1Mean2Bu() {
    return Bu2Dst0h_Dst02D0pi0_a1Mean2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a2Mean2Bu() {
    return Bu2Dst0h_Dst02D0pi0_a2Mean2Bu_;
  }
  RooPolyVar &Bu2Dst0h_Dst02D0pi0_mean2Bu() {
    return Bu2Dst0h_Dst02D0pi0_mean2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu() {
    return Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu() {
    return Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a2Sigma1Bu() {
    return Bu2Dst0h_Dst02D0pi0_a2Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu() {
    return Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu() {
    return Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a2Sigma2Bu() {
    return Bu2Dst0h_Dst02D0pi0_a2Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a1Bu() { return Bu2Dst0h_Dst02D0pi0_a1Bu_; }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_a2Bu() { return Bu2Dst0h_Dst02D0pi0_a2Bu_; }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_n1Bu() { return Bu2Dst0h_Dst02D0pi0_n1Bu_; }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_n2Bu() { return Bu2Dst0h_Dst02D0pi0_n2Bu_; }
  RooRealVar &Bu2Dst0h_Dst02D0pi0_frac1PdfBu() {
    return Bu2Dst0h_Dst02D0pi0_frac1PdfBu_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0() {
    return ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &relativeBuWidth_Bu2Dst0h_Dst02D0pi0() {
    return relativeBuWidth_Bu2Dst0h_Dst02D0pi0_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_meanDelta() {
    return Bu2Dst0h_Dst02D0gamma_meanDelta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_sigma1Delta() {
    return Bu2Dst0h_Dst02D0gamma_sigma1Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_sigma2Delta() {
    return Bu2Dst0h_Dst02D0gamma_sigma2Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a1Delta() {
    return Bu2Dst0h_Dst02D0gamma_a1Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a2Delta() {
    return Bu2Dst0h_Dst02D0gamma_a2Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_n1Delta() {
    return Bu2Dst0h_Dst02D0gamma_n1Delta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_n2Delta() {
    return Bu2Dst0h_Dst02D0gamma_n2Delta_;
  }
  RooCBShape &pdf1Delta_Bu2Dst0h_Dst02D0gamma() {
    return pdf1Delta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooCBShape &pdf2Delta_Bu2Dst0h_Dst02D0gamma() {
    return pdf2Delta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_frac1PdfDelta() {
    return Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_Dst02D0gamma() {
    return pdfDelta_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a0Mean1Bu() {
    return Bu2Dst0h_Dst02D0gamma_a0Mean1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a1Mean1Bu() {
    return Bu2Dst0h_Dst02D0gamma_a1Mean1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a2Mean1Bu() {
    return Bu2Dst0h_Dst02D0gamma_a2Mean1Bu_;
  }
  RooPolyVar &Bu2Dst0h_Dst02D0gamma_mean1Bu() {
    return Bu2Dst0h_Dst02D0gamma_mean1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a0Mean2Bu() {
    return Bu2Dst0h_Dst02D0gamma_a0Mean2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a1Mean2Bu() {
    return Bu2Dst0h_Dst02D0gamma_a1Mean2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a2Mean2Bu() {
    return Bu2Dst0h_Dst02D0gamma_a2Mean2Bu_;
  }
  RooPolyVar &Bu2Dst0h_Dst02D0gamma_mean2Bu() {
    return Bu2Dst0h_Dst02D0gamma_mean2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a0Sigma1Bu() {
    return Bu2Dst0h_Dst02D0gamma_a0Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a1Sigma1Bu() {
    return Bu2Dst0h_Dst02D0gamma_a1Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a2Sigma1Bu() {
    return Bu2Dst0h_Dst02D0gamma_a2Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a0Sigma2Bu() {
    return Bu2Dst0h_Dst02D0gamma_a0Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a1Sigma2Bu() {
    return Bu2Dst0h_Dst02D0gamma_a1Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a2Sigma2Bu() {
    return Bu2Dst0h_Dst02D0gamma_a2Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a1Bu() {
    return Bu2Dst0h_Dst02D0gamma_a1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_a2Bu() {
    return Bu2Dst0h_Dst02D0gamma_a2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_n1Bu() {
    return Bu2Dst0h_Dst02D0gamma_n1Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_n2Bu() {
    return Bu2Dst0h_Dst02D0gamma_n2Bu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_frac1PdfBu() {
    return Bu2Dst0h_Dst02D0gamma_frac1PdfBu_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_fracWidePdfBu() {
    return Bu2Dst0h_Dst02D0gamma_fracWidePdfBu_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma() {
    return ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &relativeBuWidth_Bu2Dst0h_Dst02D0gamma() {
    return relativeBuWidth_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &bkg_thresholdDelta() { return bkg_thresholdDelta_; }
  RooRealVar &bkg_aDelta() { return bkg_aDelta_; }
  RooRealVar &bkg_bDelta() { return bkg_bDelta_; }
  RooRealVar &bkg_cDelta() { return bkg_cDelta_; }
  RooDstD0BG &pdfDelta_overRec() { return pdfDelta_overRec_; }
  // RooRealVar &overRec_a0MeanBu() { return overRec_a0MeanBu_; }
  // RooPolyVar &overRec_meanBu() { return overRec_meanBu_; }
  RooRealVar &overRec_a0Mean1Bu() { return overRec_a0Mean1Bu_; }
  RooRealVar &overRec_a1Mean1Bu() { return overRec_a1Mean1Bu_; }
  RooRealVar &overRec_a2Mean1Bu() { return overRec_a2Mean1Bu_; }
  RooPolyVar &overRec_mean1Bu() { return overRec_mean1Bu_; }
  RooRealVar &overRec_a0Mean2Bu() { return overRec_a0Mean2Bu_; }
  RooRealVar &overRec_a1Mean2Bu() { return overRec_a1Mean2Bu_; }
  RooRealVar &overRec_a2Mean2Bu() { return overRec_a2Mean2Bu_; }
  RooPolyVar &overRec_mean2Bu() { return overRec_mean2Bu_; }
  RooRealVar &overRec_a0Sigma1Bu() { return overRec_a0Sigma1Bu_; }
  RooRealVar &overRec_a1Sigma1Bu() { return overRec_a1Sigma1Bu_; }
  RooRealVar &overRec_a2Sigma1Bu() { return overRec_a2Sigma1Bu_; }
  RooRealVar &overRec_a0Sigma2Bu() { return overRec_a0Sigma2Bu_; }
  RooRealVar &overRec_a1Sigma2Bu() { return overRec_a1Sigma2Bu_; }
  RooRealVar &overRec_a2Sigma2Bu() { return overRec_a2Sigma2Bu_; }
  RooRealVar &overRec_a1Bu() { return overRec_a1Bu_; }
  RooRealVar &overRec_a2Bu() { return overRec_a2Bu_; }
  RooRealVar &overRec_n1Bu() { return overRec_n1Bu_; }
  RooRealVar &overRec_n2Bu() { return overRec_n2Bu_; }
  RooRealVar &overRec_frac1PdfBu() { return overRec_frac1PdfBu_; }
  RooRealVar &ratioDst0KDst0pi_overRec() { return ratioDst0KDst0pi_overRec_; }
  RooRealVar &relativeBuWidth_overRec() { return relativeBuWidth_overRec_; }
  RooCBShape &pdf1Delta_Bu2Dst0hst_Dst02D0pi0() {
    return pdf1Delta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooCBShape &pdf2Delta_Bu2Dst0hst_Dst02D0pi0() {
    return pdf2Delta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_frac1PdfDelta() {
    return Bu2Dst0hst_Dst02D0pi0_frac1PdfDelta_;
  }
  RooAddPdf &pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0() {
    return pdfDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooDstD0BG &pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0() {
    return pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_fracPdfFlatDelta() {
    return Bu2Dst0hst_Dst02D0pi0_fracPdfFlatDelta_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0hst_Dst02D0pi0() {
    return pdfDelta_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a0MeanBu() {
    return Bu2Dst0hst_Dst02D0pi0_a0MeanBu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a1MeanBu() {
    return Bu2Dst0hst_Dst02D0pi0_a1MeanBu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a2MeanBu() {
    return Bu2Dst0hst_Dst02D0pi0_a2MeanBu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu() {
    return Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu() {
    return Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a2Sigma1Bu() {
    return Bu2Dst0hst_Dst02D0pi0_a2Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu() {
    return Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu() {
    return Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a2Sigma2Bu() {
    return Bu2Dst0hst_Dst02D0pi0_a2Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a1Bu() {
    return Bu2Dst0hst_Dst02D0pi0_a1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_a2Bu() {
    return Bu2Dst0hst_Dst02D0pi0_a2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_n1Bu() {
    return Bu2Dst0hst_Dst02D0pi0_n1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_n2Bu() {
    return Bu2Dst0hst_Dst02D0pi0_n2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0pi0_frac1PdfBu() {
    return Bu2Dst0hst_Dst02D0pi0_frac1PdfBu_;
  }
  RooPolyVar &Bu2Dst0hst_Dst02D0pi0_meanBu() {
    return Bu2Dst0hst_Dst02D0pi0_meanBu_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0() {
    return ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooRealVar &relativeBuWidth_Bu2Dst0hst_Dst02D0pi0() {
    return relativeBuWidth_Bu2Dst0hst_Dst02D0pi0_;
  }
  RooCBShape &pdf1Delta_Bu2Dst0hst_Dst02D0gamma() {
    return pdf1Delta_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooCBShape &pdf2Delta_Bu2Dst0hst_Dst02D0gamma() {
    return pdf2Delta_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_frac1PdfDelta() {
    return Bu2Dst0hst_Dst02D0gamma_frac1PdfDelta_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0hst_Dst02D0gamma() {
    return pdfDelta_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a0MeanBu() {
    return Bu2Dst0hst_Dst02D0gamma_a0MeanBu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a1MeanBu() {
    return Bu2Dst0hst_Dst02D0gamma_a1MeanBu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a2MeanBu() {
    return Bu2Dst0hst_Dst02D0gamma_a2MeanBu_;
  }
  RooPolyVar &Bu2Dst0hst_Dst02D0gamma_meanBu() {
    return Bu2Dst0hst_Dst02D0gamma_meanBu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a0Sigma1Bu() {
    return Bu2Dst0hst_Dst02D0gamma_a0Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a1Sigma1Bu() {
    return Bu2Dst0hst_Dst02D0gamma_a1Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a2Sigma1Bu() {
    return Bu2Dst0hst_Dst02D0gamma_a2Sigma1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a0Sigma2Bu() {
    return Bu2Dst0hst_Dst02D0gamma_a0Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a1Sigma2Bu() {
    return Bu2Dst0hst_Dst02D0gamma_a1Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a2Sigma2Bu() {
    return Bu2Dst0hst_Dst02D0gamma_a2Sigma2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a1Bu() {
    return Bu2Dst0hst_Dst02D0gamma_a1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_a2Bu() {
    return Bu2Dst0hst_Dst02D0gamma_a2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_n1Bu() {
    return Bu2Dst0hst_Dst02D0gamma_n1Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_n2Bu() {
    return Bu2Dst0hst_Dst02D0gamma_n2Bu_;
  }
  RooRealVar &Bu2Dst0hst_Dst02D0gamma_frac1PdfBu() {
    return Bu2Dst0hst_Dst02D0gamma_frac1PdfBu_;
  }
  RooRealVar &ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma() {
    return ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooRealVar &relativeBuWidth_Bu2Dst0hst_Dst02D0gamma() {
    return relativeBuWidth_Bu2Dst0hst_Dst02D0gamma_;
  }
  RooDstD0BG &pdfDelta_misRec() { return pdfDelta_misRec_; }
  RooRealVar &misRec_a0Mean1Bu() { return misRec_a0Mean1Bu_; }
  RooRealVar &misRec_a1Mean1Bu() { return misRec_a1Mean1Bu_; }
  RooRealVar &misRec_a2Mean1Bu() { return misRec_a2Mean1Bu_; }
  RooPolyVar &misRec_mean1Bu() { return misRec_mean1Bu_; }
  RooRealVar &misRec_a0Mean2Bu() { return misRec_a0Mean2Bu_; }
  RooRealVar &misRec_a1Mean2Bu() { return misRec_a1Mean2Bu_; }
  RooRealVar &misRec_a2Mean2Bu() { return misRec_a2Mean2Bu_; }
  RooPolyVar &misRec_mean2Bu() { return misRec_mean2Bu_; }
  RooRealVar &misRec_a0Mean3Bu() { return misRec_a0Mean3Bu_; }
  RooRealVar &misRec_a1Mean3Bu() { return misRec_a1Mean3Bu_; }
  RooRealVar &misRec_a2Mean3Bu() { return misRec_a2Mean3Bu_; }
  RooPolyVar &misRec_mean3Bu() { return misRec_mean3Bu_; }
  RooRealVar &misRec_a0Sigma1Bu() { return misRec_a0Sigma1Bu_; }
  RooRealVar &misRec_a1Sigma1Bu() { return misRec_a1Sigma1Bu_; }
  RooRealVar &misRec_a2Sigma1Bu() { return misRec_a2Sigma1Bu_; }
  RooRealVar &misRec_a0Sigma2Bu() { return misRec_a0Sigma2Bu_; }
  RooRealVar &misRec_a1Sigma2Bu() { return misRec_a1Sigma2Bu_; }
  RooRealVar &misRec_a2Sigma2Bu() { return misRec_a2Sigma2Bu_; }
  RooRealVar &misRec_a0Sigma3Bu() { return misRec_a0Sigma3Bu_; }
  RooRealVar &misRec_a1Sigma3Bu() { return misRec_a1Sigma3Bu_; }
  RooRealVar &misRec_a2Sigma3Bu() { return misRec_a2Sigma3Bu_; }
  RooRealVar &misRec_frac1PdfBu() { return misRec_frac1PdfBu_; }
  RooRealVar &misRec_frac2PdfBu() { return misRec_frac2PdfBu_; }
  RooFormulaVar &misRec_frac3PdfBu() { return misRec_frac3PdfBu_; }
  RooRealVar &ratioDst0KDst0pi_misRec() { return ratioDst0KDst0pi_misRec_; }
  RooRealVar &relativeBuWidth_misRec() { return relativeBuWidth_misRec_; }
  RooDstD0BG &pdfDelta_Comb() { return pdfDelta_Comb_; }
  RooRealVar &Comb_a0LambdaBu() { return Comb_a0LambdaBu_; }
  RooPolyVar &Comb_lambdaBu() { return Comb_lambdaBu_; }
  RooExponential &pdfBu_Comb() { return pdfBu_Comb_; }
  RooProdPdf &pdf_Comb() { return pdf_Comb_; }

 private:
  // Indicate if only used by one neutral

  int uniqueId_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_meanDelta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_sigma1Delta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_sigma2Delta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a2Delta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a1Delta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_n2Delta_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_n1Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_Dst02D0pi0_;
  RooCBShape pdf2Delta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_frac1PdfDelta_;
  RooAddPdf pdfDelta_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a0Mean1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a1Mean1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a2Mean1Bu_;
  RooPolyVar Bu2Dst0h_Dst02D0pi0_mean1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a0Mean2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a1Mean2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a2Mean2Bu_;
  RooPolyVar Bu2Dst0h_Dst02D0pi0_mean2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a2Sigma1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a2Sigma2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_a2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_n1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_n2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0pi0_frac1PdfBu_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar relativeBuWidth_Bu2Dst0h_Dst02D0pi0_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_meanDelta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_sigma1Delta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_sigma2Delta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a2Delta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a1Delta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n2Delta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n1Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_Dst02D0gamma_;
  RooCBShape pdf2Delta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_;
  RooAddPdf pdfDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a0Mean1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a1Mean1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a2Mean1Bu_;
  RooPolyVar Bu2Dst0h_Dst02D0gamma_mean1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a0Mean2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a1Mean2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a2Mean2Bu_;
  RooPolyVar Bu2Dst0h_Dst02D0gamma_mean2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a0Sigma1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a1Sigma1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a2Sigma1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a0Sigma2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a1Sigma2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a2Sigma2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_frac1PdfBu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_fracWidePdfBu_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar relativeBuWidth_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar bkg_thresholdDelta_;
  RooRealVar bkg_aDelta_;
  RooRealVar bkg_bDelta_;
  RooRealVar bkg_cDelta_;
  RooDstD0BG pdfDelta_overRec_;
  RooRealVar overRec_a0Mean1Bu_;
  RooRealVar overRec_a1Mean1Bu_;
  RooRealVar overRec_a2Mean1Bu_;
  RooPolyVar overRec_mean1Bu_;
  RooRealVar overRec_a0Mean2Bu_;
  RooRealVar overRec_a1Mean2Bu_;
  RooRealVar overRec_a2Mean2Bu_;
  RooPolyVar overRec_mean2Bu_;
  RooRealVar overRec_a0Sigma1Bu_;
  RooRealVar overRec_a1Sigma1Bu_;
  RooRealVar overRec_a2Sigma1Bu_;
  RooRealVar overRec_a0Sigma2Bu_;
  RooRealVar overRec_a1Sigma2Bu_;
  RooRealVar overRec_a2Sigma2Bu_;
  RooRealVar overRec_a1Bu_;
  RooRealVar overRec_a2Bu_;
  RooRealVar overRec_n1Bu_;
  RooRealVar overRec_n2Bu_;
  RooRealVar overRec_frac1PdfBu_;
  RooRealVar ratioDst0KDst0pi_overRec_;
  RooRealVar relativeBuWidth_overRec_;
  RooCBShape pdf1Delta_Bu2Dst0hst_Dst02D0pi0_;
  RooCBShape pdf2Delta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_frac1PdfDelta_;
  RooAddPdf pdfPeakDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooDstD0BG pdfFlatDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_fracPdfFlatDelta_;
  RooAddPdf pdfDelta_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a0MeanBu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a1MeanBu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a2MeanBu_;
  RooPolyVar Bu2Dst0hst_Dst02D0pi0_meanBu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a2Sigma1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a0Sigma2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a1Sigma2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a2Sigma2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_a2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_n1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_n2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0pi0_frac1PdfBu_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0pi0_;
  RooRealVar relativeBuWidth_Bu2Dst0hst_Dst02D0pi0_;
  RooCBShape pdf1Delta_Bu2Dst0hst_Dst02D0gamma_;
  RooCBShape pdf2Delta_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_frac1PdfDelta_;
  RooAddPdf pdfDelta_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a0MeanBu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a1MeanBu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a2MeanBu_;
  RooPolyVar Bu2Dst0hst_Dst02D0gamma_meanBu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a0Sigma1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a1Sigma1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a2Sigma1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a0Sigma2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a1Sigma2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a2Sigma2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_a2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_n1Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_n2Bu_;
  RooRealVar Bu2Dst0hst_Dst02D0gamma_frac1PdfBu_;
  RooRealVar ratioDst0KDst0pi_Bu2Dst0hst_Dst02D0gamma_;
  RooRealVar relativeBuWidth_Bu2Dst0hst_Dst02D0gamma_;
  RooDstD0BG pdfDelta_misRec_;
  RooRealVar misRec_a0Mean1Bu_;
  RooRealVar misRec_a1Mean1Bu_;
  RooRealVar misRec_a2Mean1Bu_;
  RooPolyVar misRec_mean1Bu_;
  RooRealVar misRec_a0Mean2Bu_;
  RooRealVar misRec_a1Mean2Bu_;
  RooRealVar misRec_a2Mean2Bu_;
  RooPolyVar misRec_mean2Bu_;
  RooRealVar misRec_a0Mean3Bu_;
  RooRealVar misRec_a1Mean3Bu_;
  RooRealVar misRec_a2Mean3Bu_;
  RooPolyVar misRec_mean3Bu_;
  RooRealVar misRec_a0Sigma1Bu_;
  RooRealVar misRec_a1Sigma1Bu_;
  RooRealVar misRec_a2Sigma1Bu_;
  RooRealVar misRec_a0Sigma2Bu_;
  RooRealVar misRec_a1Sigma2Bu_;
  RooRealVar misRec_a2Sigma2Bu_;
  RooRealVar misRec_a0Sigma3Bu_;
  RooRealVar misRec_a1Sigma3Bu_;
  RooRealVar misRec_a2Sigma3Bu_;
  RooRealVar misRec_frac1PdfBu_;
  RooRealVar misRec_frac2PdfBu_;
  RooFormulaVar misRec_frac3PdfBu_;
  RooRealVar ratioDst0KDst0pi_misRec_;
  RooRealVar relativeBuWidth_misRec_;
  RooDstD0BG pdfDelta_Comb_;
  RooRealVar Comb_a0LambdaBu_;
  RooPolyVar Comb_lambdaBu_;
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
