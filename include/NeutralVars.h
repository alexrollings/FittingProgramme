#pragma once
#include <string>
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
  RooRealVar &Bu2Dst0h_Dst02D0gamma_meanDelta() {
    return Bu2Dst0h_Dst02D0gamma_meanDelta_;
  }
  RooRealVar &Bu2Dst0h_Dst02D0gamma_sigmaDelta() {
    return Bu2Dst0h_Dst02D0gamma_sigmaDelta_;
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
  RooRealVar &Bu2Dst0h_Dst02D0gamma_meanBu() {
    return Bu2Dst0h_Dst02D0gamma_meanBu_;
  }
  RooRealVar &relativeBuWidth_Bu2Dst0h_Dst02D0gamma() {
    return relativeBuWidth_Bu2Dst0h_Dst02D0gamma_;
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
  RooRealVar &ratioKpi_Bu2Dst0h_Dst02D0gamma() {
    return ratioKpi_Bu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &orEffBu2Dst0h_Dst02D0gamma() {
    return orEffBu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &boxEffBu2Dst0h_Dst02D0gamma() {
    return boxEffBu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &buDeltaCutEffBu2Dst0h_Dst02D0gamma() {
    return buDeltaCutEffBu2Dst0h_Dst02D0gamma_;
  }
  RooRealVar &deltaCutEffBu2Dst0h_Dst02D0gamma() {
    return deltaCutEffBu2Dst0h_Dst02D0gamma_;
  }

  void SetEfficiencies(Mode mode, RooRealVar &orEff, RooRealVar &boxEff,
                       RooRealVar &buDeltaCutEff, RooRealVar &deltaCutEff);

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
  RooRealVar relativeBuWidth_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_a1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n2Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_n1Bu_;
  RooRealVar Bu2Dst0h_Dst02D0gamma_frac1PdfBu_;
  RooRealVar ratioKpi_Bu2Dst0h_Dst02D0gamma_;
  RooRealVar orEffBu2Dst0h_Dst02D0gamma_;
  RooRealVar boxEffBu2Dst0h_Dst02D0gamma_;
  RooRealVar buDeltaCutEffBu2Dst0h_Dst02D0gamma_;
  RooRealVar deltaCutEffBu2Dst0h_Dst02D0gamma_;
};

// Function to be called in constructor of NVars, in order to construct
// efficiency RCVars
// Anything defined outside the class definition needs the scope :: operator
template <Neutral neutral>
void NeutralVars<neutral>::SetEfficiencies(Mode mode, RooRealVar &orEff,
                                           RooRealVar &boxEff,
                                           RooRealVar &buDeltaCutEff,
                                           RooRealVar &deltaCutEff) {
  std::string modeString = EnumToString(mode);
  std::string dirString;
  std::cout << "Calculating and setting efficiencies for " << modeString
            << ":\n";
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
  std::string ttree("BtoDstar0h3_h1h2gammaTuple");

  TChain chain(ttree.c_str());

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

  std::string dlString = std::to_string(Configuration::Get().deltaLow());
  std::string dhString = std::to_string(Configuration::Get().deltaHigh());
  std::string blString = std::to_string(Configuration::Get().buDeltaLow());
  std::string bhString = std::to_string(Configuration::Get().buDeltaHigh());
  std::string cutString;

  switch (neutral) {
    case Neutral::gamma:
      cutString = Configuration::Get().gammaCutString();
      break;
    case Neutral::pi0:
      cutString = Configuration::Get().pi0CutString();
      break;
  }

  double nInitial =
      chain.GetEntries(Configuration::Get().gammaCutString().c_str());
  double nDeltaCut = chain.GetEntries(
      (cutString + "&&Delta_M>" + dlString + "&&Delta_M<" + dhString).c_str());
  double nBuDeltaCut = chain.GetEntries(
      (cutString + "&&Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString)
          .c_str());
  double nBox = chain.GetEntries((cutString + "&&Delta_M>" + dlString +
                                  "&&Delta_M<" + dhString + "&&Bu_Delta_M>" +
                                  blString + "&&Bu_Delta_M<" + bhString)
                                     .c_str());
  double nOr = chain.GetEntries((cutString + "&&((Delta_M>" + dlString +
                                 "&&Delta_M<" + dhString + ")||(Bu_Delta_M>" +
                                 blString + "&&Bu_Delta_M<" + bhString + "))")
                                    .c_str());

  deltaCutEff.setVal(nDeltaCut / nInitial);
  buDeltaCutEff.setVal(nBuDeltaCut / nInitial);
  boxEff.setVal(nBox / nInitial);
  orEff.setVal(nOr / nInitial);

  std::cout << "\t orEff = " << orEff.getVal() << "\n"
            << "\t boxEff = " << boxEff.getVal() << "\n"
            << "\t buDeltaCutEff = " << buDeltaCutEff.getVal() << "\n"
            << "\t deltaCutEff = " << deltaCutEff.getVal() << "\n";
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
