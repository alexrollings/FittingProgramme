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

enum class ReturnType { val, std };

template <Neutral neutral>
double ReadBkgFracs(Mode mode, ReturnType returnType) {
  std::string txtFileName =
      "/home/rollings/Bu2Dst0h_2d/FittingProgramme/calc_fixed_params/bkgFracs_" +
      EnumToString(neutral) + ".txt";
  if (!fexists(txtFileName)) {
    std::cerr
        << "!!!!!!!!!!\nReadBkgFracs: " << txtFileName
        << " doesn't exist: setting frac to 1.0 and error to 0.0.\n!!!!!!!!!!";
    if (returnType == ReturnType::val) {
      return 1.0;
    } else if (returnType == ReturnType::std) {
      return 0.0;
    } else {
      throw std::runtime_error(
          "ReadBkgFracs: return type = val/std\n");
    }
  }
  std::ifstream inFile(txtFileName);
  std::string line;
  // Loop over lines in txt file
  while (std::getline(inFile, line)) {
    // Separate label and value (white space)
    std::vector<std::string> lineVec = SplitLine(line);
    if (lineVec[0] == EnumToString(mode)) {
      if (returnType == ReturnType::val) {
        return std::stod(lineVec[1]);
      } else if (returnType == ReturnType::std) {
        return std::stod(lineVec[2]);
      } else {
        throw std::runtime_error(
            "ReadBkgFracs: return type = val/std\n");
      }
    }
  }
}

template <Neutral neutral, Bachelor bachelor>
double ReadPdfFracs(const char* paramName, ReturnType returnType) {
  std::string txtFileName =
      "/home/rollings/Bu2Dst0h_2d/FittingProgramme/calc_fixed_params/pdf_fracs_" +
      EnumToString(neutral) + ".txt";
  std::stringstream paramLabel;
  paramLabel << paramName << "_" << EnumToString(bachelor);
  if (!fexists(txtFileName)) {
    std::cerr
        << "!!!!!!!!!!\nReadPdfFracs: " << txtFileName
        << " doesn't exist: setting frac to 1.0 and error to 0.0.\n!!!!!!!!!!";
    if (returnType == ReturnType::val) {
      return 1.0;
    } else {
      return 0.0;
    }
  }
  std::ifstream inFile(txtFileName);
  std::string line;
  // Loop over lines in txt file
  while (std::getline(inFile, line)) {
    // Separate label and value (white space)
    std::vector<std::string> lineVec = SplitLine(line);
    if (lineVec[0] == paramLabel.str()) {
      if (returnType == ReturnType::val) {
        return std::stod(lineVec[1]);
      } { 
        return std::stod(lineVec[2]);
      }
    }
  }
}

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
  RooRealVar &Bu2Dst0h_D0pi0_mean1Bu() { return *Bu2Dst0h_D0pi0_mean1Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_meanOffset21Bu() { return *Bu2Dst0h_D0pi0_meanOffset21Bu_; }
  RooFormulaVar &Bu2Dst0h_D0pi0_mean2Bu() { return Bu2Dst0h_D0pi0_mean2Bu_; }
  RooRealVar &Bu2Dst0h_D0pi0_sigmaRatio21Bu() { return *Bu2Dst0h_D0pi0_sigmaRatio21Bu_; }
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
  // -------------------- Bu2Dst0h_WN -------------------- //
  RooRealVar &Bu2Dst0h_WN_floatingFracD0pi0() {
    return *Bu2Dst0h_WN_floatingFracD0pi0_;
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
  RooRealVar &Bu2D0hst_thresholdDelta() { return *Bu2D0hst_thresholdDelta_; }
  RooRealVar &Bu2D0hst_bDelta() { return *Bu2D0hst_bDelta_; }
  RooRealVar &Bu2D0hst_cDelta() { return *Bu2D0hst_cDelta_; }
  RooDstD0BG &pdfDelta_Bu2D0hst() { return *pdfDelta_Bu2D0hst_; }
  std::shared_ptr<RooDstD0BG> &pdfDelta_Bu2D0hst_GetPointer() {
    return pdfDelta_Bu2D0hst_;
  }
  RooRealVar &Bu2D0hst_mean1Bu() { return *Bu2D0hst_mean1Bu_; }
  RooRealVar &Bu2D0hst_meanOffset21Bu() {
    return *Bu2D0hst_meanOffset21Bu_;
  }
  RooFormulaVar &Bu2D0hst_mean2Bu() { return Bu2D0hst_mean2Bu_; }
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
  RooRealVar &Bu2Dst0hst_D0pi0_meanDelta() {
    return *Bu2Dst0hst_D0pi0_meanDelta_;
  }
  RooRealVar &Bu2Dst0hst_D0pi0_sigmaDelta() {
    return *Bu2Dst0hst_D0pi0_sigmaDelta_;
  }
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
  // -------------------- Bu2Dst0hst -------------------- //
  // RooRealVar &Bu2Dst0hst_floatingFracD0pi0() {
  //   return *Bu2Dst0hst_floatingFracD0pi0_;
  // }
  // -------------------- Lb2Omegach_Lcpi0 -------------------- //
  RooDstD0BG &pdfDelta_Lb2Omegach_Lcpi0() {
    return pdfDelta_Lb2Omegach_Lcpi0_;
  }
  RooCBShape &pdfBu_Lb2Omegach_Lcpi0() {
    return pdfBu_Lb2Omegach_Lcpi0_;
  }
  RooCBShape &pdfBuPartial_Lb2Omegach_Lcpi0() {
    return pdfBuPartial_Lb2Omegach_Lcpi0_;
  }
  // Box effs for Lb --> no K MC, only π
  RooRealVar &orEffLb2Omegach_Lcpi0() {
    return *orEffLb2Omegach_Lcpi0_;
  }
  RooRealVar &deltaEffLb2Omegach_Lcpi0() {
    return *deltaEffLb2Omegach_Lcpi0_;
  }
  RooRealVar &buEffLb2Omegach_Lcpi0() {
    return *buEffLb2Omegach_Lcpi0_;
  }
  RooRealVar &buPartialEffLb2Omegach_Lcpi0() {
    return *buPartialEffLb2Omegach_Lcpi0_;
  }
  // -------------------- Bs2D0Kst0 -------------------- //
  RooDstD0BG &pdfDelta_Bs2D0Kst0() {
    return pdfDelta_Bs2D0Kst0_;
  }
  RooCBShape &pdfBu_Bs2D0Kst0() {
    return pdfBu_Bs2D0Kst0_;
  }
  RooCBShape &pdfBuPartial_Bs2D0Kst0() {
    return pdfBuPartial_Bs2D0Kst0_;
  }
  // Box effs for Bs --> no π MC, only K
  RooRealVar &orEffBs2D0Kst0() {
    return *orEffBs2D0Kst0_;
  }
  RooRealVar &deltaEffBs2D0Kst0() {
    return *deltaEffBs2D0Kst0_;
  }
  RooRealVar &buEffBs2D0Kst0() {
    return *buEffBs2D0Kst0_;
  }
  RooRealVar &buPartialEffBs2D0Kst0() {
    return *buPartialEffBs2D0Kst0_;
  }
  // -------------------- Bs2Dst0Kst0 -------------------- //
  RooRealVar &Bs2Dst0Kst0_D0gamma_a1Delta() { return *Bs2Dst0Kst0_D0gamma_a1Delta_; }
  RooRealVar &Bs2Dst0Kst0_D0gamma_a2Delta() { return *Bs2Dst0Kst0_D0gamma_a2Delta_; }
  RooRealVar &Bs2Dst0Kst0_D0gamma_n1Delta() { return *Bs2Dst0Kst0_D0gamma_n1Delta_; }
  RooRealVar &Bs2Dst0Kst0_D0gamma_n2Delta() { return *Bs2Dst0Kst0_D0gamma_n2Delta_; }
  RooRealVar &Bs2Dst0Kst0_D0gamma_fracPdf1Delta() {
    return *Bs2Dst0Kst0_D0gamma_fracPdf1Delta_;
  }
  RooDstD0BG &pdfDelta_Bs2Dst0Kst0_D0gamma_WN() {
    return pdfDelta_Bs2Dst0Kst0_D0gamma_WN_;
  }
  RooRealVar &Bs2Dst0Kst0_D0pi0_a1Delta() { return *Bs2Dst0Kst0_D0pi0_a1Delta_; }
  RooRealVar &Bs2Dst0Kst0_D0pi0_a2Delta() { return *Bs2Dst0Kst0_D0pi0_a2Delta_; }
  RooRealVar &Bs2Dst0Kst0_D0pi0_n1Delta() { return *Bs2Dst0Kst0_D0pi0_n1Delta_; }
  RooRealVar &Bs2Dst0Kst0_D0pi0_n2Delta() { return *Bs2Dst0Kst0_D0pi0_n2Delta_; }
  RooRealVar &Bs2Dst0Kst0_D0pi0_fracPdf1Delta() {
    return *Bs2Dst0Kst0_D0pi0_fracPdf1Delta_;
  }
  RooRealVar &Bs2Dst0Kst0_D0pi0_WN_thresholdDelta() {
    return *Bs2Dst0Kst0_D0pi0_WN_thresholdDelta_;
  }
  RooRealVar &Bs2Dst0Kst0_D0pi0_WN_cDelta() {
    return *Bs2Dst0Kst0_D0pi0_WN_cDelta_;
  }
  RooRealVar &Bs2Dst0Kst0_fracD0pi0_Delta() {
    return *Bs2Dst0Kst0_fracD0pi0_Delta_;
  }
  RooRealVar &Bs2Dst0Kst0_fracD0pi0_WN_Delta() {
    return *Bs2Dst0Kst0_fracD0pi0_WN_Delta_;
  }
  RooFormulaVar &Bs2Dst0Kst0_floatingFracWN_Delta() {
    return Bs2Dst0Kst0_floatingFracWN_Delta_;
  }
  RooAddPdf &pdfBu_Bs2Dst0Kst0() {
    return pdfBu_Bs2Dst0Kst0_;
  }
  RooAddPdf &pdfBuPartial_Bs2Dst0Kst0() {
    return pdfBuPartial_Bs2Dst0Kst0_;
  }
  // Box effs for Bs --> no π MC, only K
  RooFormulaVar &orEffBs2Dst0Kst0() {
    return orEffBs2Dst0Kst0_;
  }
  RooFormulaVar &deltaEffBs2Dst0Kst0() {
    return deltaEffBs2Dst0Kst0_;
  }
  RooFormulaVar &buEffBs2Dst0Kst0() {
    return buEffBs2Dst0Kst0_;
  }
  RooFormulaVar &buPartialEffBs2Dst0Kst0() {
    return buPartialEffBs2Dst0Kst0_;
  }
  // -------------------- Bu2Dst0h_D0pi0_D02pik -------------------- //
  RooGaussian &pdfBu_Bu2Dst0h_D0pi0_D02pik() {
    return pdfBu_Bu2Dst0h_D0pi0_D02pik_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0_D02pik() {
    return pdfDelta_Bu2Dst0h_D0pi0_D02pik_;
  }
  RooGaussian &pdfBuPartial_Bu2Dst0h_D0pi0_D02pik() {
    return pdfBuPartial_Bu2Dst0h_D0pi0_D02pik_;
  }
  RooRealVar &orEffBu2Dst0h_D0pi0_D02pik() {
    return *orEffBu2Dst0h_D0pi0_D02pik_;
  }
  RooRealVar &deltaEffBu2Dst0h_D0pi0_D02pik() {
    return *deltaEffBu2Dst0h_D0pi0_D02pik_;
  }
  RooRealVar &buEffBu2Dst0h_D0pi0_D02pik() {
    return *buEffBu2Dst0h_D0pi0_D02pik_;
  }
  RooRealVar &buPartialEffBu2Dst0h_D0pi0_D02pik() {
    return *buPartialEffBu2Dst0h_D0pi0_D02pik_;
  }
  // -------------------- Bu2Dst0h_D0gamma_D02pik -------------------- //
  RooGaussian &pdfBu_Bu2Dst0h_D0gamma_D02pik() {
    return pdfBu_Bu2Dst0h_D0gamma_D02pik_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_D02pik() {
    return pdfDelta_Bu2Dst0h_D0gamma_D02pik_;
  }
  RooRealVar &orEffBu2Dst0h_D0gamma_D02pik() {
    return *orEffBu2Dst0h_D0gamma_D02pik_;
  }
  RooRealVar &deltaEffBu2Dst0h_D0gamma_D02pik() {
    return *deltaEffBu2Dst0h_D0gamma_D02pik_;
  }
  RooRealVar &buEffBu2Dst0h_D0gamma_D02pik() {
    return *buEffBu2Dst0h_D0gamma_D02pik_;
  }
  RooRealVar &buPartialEffBu2Dst0h_D0gamma_D02pik() {
    return *buPartialEffBu2Dst0h_D0gamma_D02pik_;
  }
  // -------------------- Bu2Dst0h_D0pi0_WN_D02pik -------------------- //
  RooGaussian &pdfBu_Bu2Dst0h_D0pi0_WN_D02pik() {
    return pdfBu_Bu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik() {
    return pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooGaussian &pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik() {
    return pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooRealVar &orEffBu2Dst0h_D0pi0_WN_D02pik() {
    return *orEffBu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooRealVar &deltaEffBu2Dst0h_D0pi0_WN_D02pik() {
    return *deltaEffBu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooRealVar &buEffBu2Dst0h_D0pi0_WN_D02pik() {
    return *buEffBu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooRealVar &buPartialEffBu2Dst0h_D0pi0_WN_D02pik() {
    return *buPartialEffBu2Dst0h_D0pi0_WN_D02pik_;
  }
  // -------------------- Bu2Dst0h_D0gamma_WN_D02pik -------------------- //
  RooGaussian &pdfBu_Bu2Dst0h_D0gamma_WN_D02pik() {
    return pdfBu_Bu2Dst0h_D0gamma_WN_D02pik_;
  }
  RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik() {
    return pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik_;
  }
  RooRealVar &orEffBu2Dst0h_D0gamma_WN_D02pik() {
    return *orEffBu2Dst0h_D0gamma_WN_D02pik_;
  }
  RooRealVar &deltaEffBu2Dst0h_D0gamma_WN_D02pik() {
    return *deltaEffBu2Dst0h_D0gamma_WN_D02pik_;
  }
  RooRealVar &buEffBu2Dst0h_D0gamma_WN_D02pik() {
    return *buEffBu2Dst0h_D0gamma_WN_D02pik_;
  }
  RooRealVar &buPartialEffBu2Dst0h_D0gamma_WN_D02pik() {
    return *buPartialEffBu2Dst0h_D0gamma_WN_D02pik_;
  }
  // -------------------- Bkg Fractions -------------------- //
  RooRealVar &bkgFracGlobal_WN() {
    return *bkgFracGlobal_WN_;
  }
  RooRealVar &bkgFracFAV_Bd2Dsth() {
    return *bkgFracFAV_Bd2Dsth_;
  }
  RooRealVar &bkgFracFAV_Bu2D0hst() {
    return *bkgFracFAV_Bu2D0hst_;
  }
  RooAbsReal &bkgFracFAV_Bu2Dst0hst() {
    return *bkgFracFAV_Bu2Dst0hst_;
  }
  RooRealVar &bkgFracKK_Lb2Omegach_Lcpi0() {
    return *bkgFracKK_Lb2Omegach_Lcpi0_;
  }
  RooRealVar &bkgFracADS_Bs2D0Kst0() {
    return *bkgFracADS_Bs2D0Kst0_;
  }
  RooRealVar &bkgFracADS_Bs2Dst0Kst0() {
    return *bkgFracADS_Bs2Dst0Kst0_;
  }
  // RooGaussian &constraint_bkgFracGlobal_WN() {
  //   return constraint_bkgFracGlobal_WN_;
  // }
  // RooGaussian &constraint_bkgFracFAV_Bu2D0hst() {
  //   return constraint_bkgFracFAV_Bu2D0hst_;
  // }
  // RooArgSet &constraints_argSet() {
  //   return constraints_argSet_;
  // }


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
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_meanDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_KpiSigmaDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_n2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_fracPdf1Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_mean1Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_meanOffset21Bu_;
  RooFormulaVar Bu2Dst0h_D0pi0_mean2Bu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_sigmaRatio21Bu_;
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
  // -------------------- Bu2Dst0h_WN -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_WN_floatingFracD0pi0_;
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
  std::shared_ptr<RooDstD0BG> pdfDelta_Bu2D0hst_;
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
  // -------------------- Bu2Dst0hst -------------------- //
  // std::shared_ptr<RooRealVar> Bu2Dst0hst_floatingFracD0pi0_;
  // -------------------- Lb2Omegach_Lcpi0 -------------------- //
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_thresholdDelta_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_aDelta_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_bDelta_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_cDelta_;
  RooDstD0BG pdfDelta_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_meanBu_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_sigmaBu_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_a1Bu_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_n1Bu_;
  RooCBShape pdfBu_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_meanBuPartial_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_sigmaBuPartial_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_a1BuPartial_;
  std::shared_ptr<RooRealVar> Lb2Omegach_Lcpi0_n1BuPartial_;
  RooCBShape pdfBuPartial_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooRealVar> orEffLb2Omegach_Lcpi0_;
  std::shared_ptr<RooRealVar> deltaEffLb2Omegach_Lcpi0_;
  std::shared_ptr<RooRealVar> buEffLb2Omegach_Lcpi0_;
  std::shared_ptr<RooRealVar> buPartialEffLb2Omegach_Lcpi0_;
  // -------------------- Bs2D0Kst0 -------------------- //
  std::shared_ptr<RooRealVar> Bs2D0Kst0_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_aDelta_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_bDelta_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_cDelta_;
  RooDstD0BG pdfDelta_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_meanBu_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_sigmaBu_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_a1Bu_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_n1Bu_;
  RooCBShape pdfBu_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_sigmaBuPartial_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_a1BuPartial_;
  std::shared_ptr<RooRealVar> Bs2D0Kst0_n1BuPartial_;
  RooCBShape pdfBuPartial_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> orEffBs2D0Kst0_;
  std::shared_ptr<RooRealVar> deltaEffBs2D0Kst0_;
  std::shared_ptr<RooRealVar> buEffBs2D0Kst0_;
  std::shared_ptr<RooRealVar> buPartialEffBs2D0Kst0_;
  // -------------------- Bs2Dst0Kst0_D0pi0 -------------------- //
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_a1Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_n1Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_a2Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_n2Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_fracPdf1Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_mean1Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_meanOffset21Bu_;
  RooFormulaVar Bs2Dst0Kst0_D0pi0_mean2Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_sigma1Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_sigmaRatio21Bu_;
  RooFormulaVar Bs2Dst0Kst0_D0pi0_sigma2Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_a1Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_n1Bu_;
  RooCBShape pdf1Bu_Bs2Dst0Kst0_D0pi0_;
  RooGaussian pdf2Bu_Bs2Dst0Kst0_D0pi0_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_fracPdf1Bu_;
  RooAddPdf pdfBu_Bs2Dst0Kst0_D0pi0_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_sigmaBuPartial_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_a1BuPartial_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_n1BuPartial_;
  RooCBShape pdfBuPartial_Bs2Dst0Kst0_D0pi0_;
  std::shared_ptr<RooRealVar> orEffBs2Dst0Kst0_D0pi0_;
  std::shared_ptr<RooRealVar> deltaEffBs2Dst0Kst0_D0pi0_;
  std::shared_ptr<RooRealVar> buEffBs2Dst0Kst0_D0pi0_;
  std::shared_ptr<RooRealVar> buPartialEffBs2Dst0Kst0_D0pi0_;
  // -------------------- Bs2Dst0Kst0_D0gamma -------------------- //
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_a1Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_n1Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_a2Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_n2Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_fracPdf1Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_meanBu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_sigmaBu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_a1Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_n1Bu_;
  RooCBShape pdfBu_Bs2Dst0Kst0_D0gamma_;
  std::shared_ptr<RooRealVar> orEffBs2Dst0Kst0_D0gamma_;
  std::shared_ptr<RooRealVar> deltaEffBs2Dst0Kst0_D0gamma_;
  std::shared_ptr<RooRealVar> buEffBs2Dst0Kst0_D0gamma_;
  std::shared_ptr<RooRealVar> buPartialEffBs2Dst0Kst0_D0gamma_;
  // -------------------- Bs2Dst0Kst0_comb -------------------- //
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracD0pi0_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracD0pi0_Delta_;
  RooFormulaVar orEffBs2Dst0Kst0_comb_;
  RooFormulaVar deltaEffBs2Dst0Kst0_comb_;
  // -------------------- Bs2Dst0Kst0_D0pi0_WN -------------------- //
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_WN_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_WN_cDelta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_WN_meanBu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_WN_sigmaBu_;
  RooGaussian pdfBu_Bs2Dst0Kst0_D0pi0_WN_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_WN_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0pi0_WN_sigmaBuPartial_;
  RooGaussian pdfBuPartial_Bs2Dst0Kst0_D0pi0_WN_;
  std::shared_ptr<RooRealVar> orEffBs2Dst0Kst0_D0pi0_WN_;
  std::shared_ptr<RooRealVar> deltaEffBs2Dst0Kst0_D0pi0_WN_;
  std::shared_ptr<RooRealVar> buEffBs2Dst0Kst0_D0pi0_WN_;
  std::shared_ptr<RooRealVar> buPartialEffBs2Dst0Kst0_D0pi0_WN_;
  // -------------------- Bs2Dst0Kst0_D0gamma_WN -------------------- //
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_WN_thresholdDelta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_WN_aDelta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_WN_bDelta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_WN_cDelta_;
  RooDstD0BG pdfDelta_Bs2Dst0Kst0_D0gamma_WN_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_WN_meanBu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_WN_sigmaBu_;
  RooGaussian pdfBu_Bs2Dst0Kst0_D0gamma_WN_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_WN_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_D0gamma_WN_sigmaBuPartial_;
  RooGaussian pdfBuPartial_Bs2Dst0Kst0_D0gamma_WN_;
  std::shared_ptr<RooRealVar> orEffBs2Dst0Kst0_D0gamma_WN_;
  std::shared_ptr<RooRealVar> deltaEffBs2Dst0Kst0_D0gamma_WN_;
  std::shared_ptr<RooRealVar> buEffBs2Dst0Kst0_D0gamma_WN_;
  std::shared_ptr<RooRealVar> buPartialEffBs2Dst0Kst0_D0gamma_WN_;
  // -------------------- Bs2Dst0Kst0_WN -------------------- //
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracD0pi0_WN_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracD0pi0_WN_Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracD0pi0_WN_Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracD0pi0_WN_BuPartial_;
  RooAddPdf pdfBu_Bs2Dst0Kst0_WN_;
  RooAddPdf pdfBuPartial_Bs2Dst0Kst0_WN_;
  RooFormulaVar orEffBs2Dst0Kst0_WN_;
  RooFormulaVar buEffBs2Dst0Kst0_WN_;
  RooFormulaVar deltaEffBs2Dst0Kst0_WN_;
  RooFormulaVar buPartialEffBs2Dst0Kst0_WN_;
  // -------------------- Bu2Dst0h_D0pi0_D02pik -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_D02pik_sigmaDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_D02pik_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_D02pik_n2Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0pi0_D02pik_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0pi0_D02pik_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_D02pik_fracPdf1Delta_;
  RooAddPdf pdfDelta_Bu2Dst0h_D0pi0_D02pik_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_D02pik_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_D02pik_sigmaBu_;
  RooGaussian pdfBu_Bu2Dst0h_D0pi0_D02pik_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_D02pik_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_D02pik_sigmaBuPartial_;
  RooGaussian pdfBuPartial_Bu2Dst0h_D0pi0_D02pik_;
  std::shared_ptr<RooRealVar> orEffBu2Dst0h_D0pi0_D02pik_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0h_D0pi0_D02pik_;
  std::shared_ptr<RooRealVar> buEffBu2Dst0h_D0pi0_D02pik_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0h_D0pi0_D02pik_;
  // -------------------- Bu2Dst0h_D0gamma_D02pik -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_D02pik_sigmaDelta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0gamma_D02pik_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0gamma_D02pik_;
  RooAddPdf pdfDelta_Bu2Dst0h_D0gamma_D02pik_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_D02pik_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_D02pik_sigmaBu_;
  RooGaussian pdfBu_Bu2Dst0h_D0gamma_D02pik_;
  std::shared_ptr<RooRealVar> orEffBu2Dst0h_D0gamma_D02pik_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0h_D0gamma_D02pik_;
  std::shared_ptr<RooRealVar> buEffBu2Dst0h_D0gamma_D02pik_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0h_D0gamma_D02pik_;
  // -------------------- Bu2Dst0h_D0pi0_WN_D02pik -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_D02pik_sigmaDelta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_D02pik_a2Delta_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_D02pik_n2Delta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0pi0_WN_D02pik_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_D02pik_fracPdf1Delta_;
  RooAddPdf pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_D02pik_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_D02pik_sigmaBu_;
  RooGaussian pdfBu_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_D02pik_meanBuPartial_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0pi0_WN_D02pik_sigmaBuPartial_;
  RooGaussian pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::shared_ptr<RooRealVar> orEffBu2Dst0h_D0pi0_WN_D02pik_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0h_D0pi0_WN_D02pik_;
  std::shared_ptr<RooRealVar> buEffBu2Dst0h_D0pi0_WN_D02pik_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0h_D0pi0_WN_D02pik_;
  // -------------------- Bu2Dst0h_D0gamma_WN_D02pik -------------------- //
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_D02pik_sigmaDelta_;
  RooCBShape pdf1Delta_Bu2Dst0h_D0gamma_WN_D02pik_;
  RooCBShape pdf2Delta_Bu2Dst0h_D0gamma_WN_D02pik_;
  RooAddPdf pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_D02pik_meanBu_;
  std::shared_ptr<RooRealVar> Bu2Dst0h_D0gamma_WN_D02pik_sigmaBu_;
  RooGaussian pdfBu_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooRealVar> orEffBu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooRealVar> deltaEffBu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooRealVar> buEffBu2Dst0h_D0gamma_WN_D02pik_;
  std::shared_ptr<RooRealVar> buPartialEffBu2Dst0h_D0gamma_WN_D02pik_;
  // -------------------- Bkg Fractions -------------------- //
  std::shared_ptr<RooRealVar> bkgFracGlobal_WN_;
  std::shared_ptr<RooRealVar> bkgFracFAV_Bd2Dsth_;
  std::shared_ptr<RooRealVar> bkgFracFAV_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> bkgFracFAV_Bu2Dst0hst_;
  std::shared_ptr<RooRealVar> bkgFracKK_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooRealVar> bkgFracADS_Bs2D0Kst0_;
  std::shared_ptr<RooRealVar> bkgFracADS_Bs2Dst0Kst0_;
  // RooGaussian constraint_bkgFracGlobal_WN_;
  // RooGaussian constraint_bkgFracFAV_Bu2D0hst_;
  // RooArgSet constraints_argSet_;
  // -------------------- Bs2Dst0Kst0 -------------------- //
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracWN_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracWN_Bu_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracWN_Delta_;
  std::shared_ptr<RooRealVar> Bs2Dst0Kst0_fracWN_BuPartial_;
  RooFormulaVar Bs2Dst0Kst0_floatingFracWN_Bu_;
  RooFormulaVar Bs2Dst0Kst0_floatingFracWN_Delta_;
  RooFormulaVar Bs2Dst0Kst0_floatingFracWN_BuPartial_;
  RooAddPdf pdfBu_Bs2Dst0Kst0_;
  RooAddPdf pdfBuPartial_Bs2Dst0Kst0_;
  RooFormulaVar orEffBs2Dst0Kst0_;
  RooFormulaVar buEffBs2Dst0Kst0_;
  RooFormulaVar deltaEffBs2Dst0Kst0_;
  RooFormulaVar buPartialEffBs2Dst0Kst0_;
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
