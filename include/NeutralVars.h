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
  RooRealVar &Bu2Dst0h_Dst02D0gamma_meanDelta() {
    return Bu2Dst0h_Dst02D0gamma_meanDelta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_sigma1Delta() {
    return Bu2Dst0h_Dst02D0gamma_sigma1Delta_;
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

 private:
  // Indicate if only used by one neutral

  int uniqueId_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_meanDelta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_sigmaDelta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a2Delta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a1Delta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n2Delta_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n1Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_Dst02D0gamma_;
  RooCBShape pdf2Delta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_;
  RooAddPdf pdfDelta_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_meanBu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_frac1PdfBu_;
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
