#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooCruijff.h"
#include "RooFormulaVar.h"
#include "RooProdPdf.h"

// Bachelor

template <Neutral neutral, Bachelor bachelor>
class NeutralBachelorVars {
 public:
  NeutralBachelorVars(int uniqueId_);
  ~NeutralBachelorVars() {}

  using This_t = NeutralBachelorVars<neutral, bachelor>;

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

  int uniqueId() { return uniqueId_; }
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooAbsReal &Bu2Dst0h_D0gamma_sigmaBu() { return *Bu2Dst0h_D0gamma_sigmaBu_; }
  RooCBShape &pdf1Bu_Bu2Dst0h_D0gamma() { return pdf1Bu_Bu2Dst0h_D0gamma_; }
  RooCBShape &pdf2Bu_Bu2Dst0h_D0gamma() { return pdf2Bu_Bu2Dst0h_D0gamma_; }
  RooAddPdf &pdfBu_Bu2Dst0h_D0gamma() { return pdfBu_Bu2Dst0h_D0gamma_; }
  RooRealVar &N_tot_Bu2Dst0h_D0gamma() { return N_tot_Bu2Dst0h_D0gamma_; }
  RooConstVar &pidEff_Bu2Dst0h_D0gamma() { return pidEff_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &N_Bu2Dst0h_D0gamma() { return N_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0gamma() {
    return N_Delta_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_Bu_Bu2Dst0h_D0gamma() { return *N_Bu_Bu2Dst0h_D0gamma_; }
  // -------------------- Mis-ID ------------------- //
  RooRealVar &misId_Bu2Dst0h_D0gamma_meanBu() {
    return misId_Bu2Dst0h_D0gamma_meanBu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_sigma1Bu() {
    return misId_Bu2Dst0h_D0gamma_sigma1Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_sigma2Bu() {
    return misId_Bu2Dst0h_D0gamma_sigma2Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_a1Bu() {
    return misId_Bu2Dst0h_D0gamma_a1Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_a2Bu() {
    return misId_Bu2Dst0h_D0gamma_a2Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_n1Bu() {
    return misId_Bu2Dst0h_D0gamma_n1Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_n2Bu() {
    return misId_Bu2Dst0h_D0gamma_n2Bu_;
  }
  RooCBShape &pdf1Bu_misId_Bu2Dst0h_D0gamma() {
    return pdf1Bu_misId_Bu2Dst0h_D0gamma_;
  }
  RooCBShape &pdf2Bu_misId_Bu2Dst0h_D0gamma() {
    return pdf2Bu_misId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &misId_Bu2Dst0h_D0gamma_frac1PdfBu() {
    return misId_Bu2Dst0h_D0gamma_frac1PdfBu_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() {
    return *pdfBu_misId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &orEffMisId_Bu2Dst0h_D0gamma() {
    return orEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &boxEffMisId_Bu2Dst0h_D0gamma() {
    return boxEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &buDeltaCutEffMisId_Bu2Dst0h_D0gamma() {
    return buDeltaCutEffMisId_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &deltaCutEffMisId_Bu2Dst0h_D0gamma() {
    return deltaCutEffMisId_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar &Bu2Dst0h_D0pi0_sigmaBu() { return Bu2Dst0h_D0pi0_sigmaBu_; }
  RooCBShape &pdfBu_Bu2Dst0h_D0pi0() { return pdfBu_Bu2Dst0h_D0pi0_; }
  RooRealVar &N_tot_Bu2Dst0h_D0pi0() { return N_tot_Bu2Dst0h_D0pi0_; }
  RooConstVar &pidEff_Bu2Dst0h_D0pi0() { return pidEff_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Bu2Dst0h_D0pi0() { return N_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0pi0() { return N_Delta_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_Bu_Bu2Dst0h_D0pi0() { return *N_Bu_Bu2Dst0h_D0pi0_; }
  // -------------------- Mis-ID ------------------- //
  RooRealVar &misId_Bu2Dst0h_D0pi0_meanBu() {
    return misId_Bu2Dst0h_D0pi0_meanBu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_sigma1Bu() {
    return misId_Bu2Dst0h_D0pi0_sigma1Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_sigma2Bu() {
    return misId_Bu2Dst0h_D0pi0_sigma2Bu_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_a1Bu() { return misId_Bu2Dst0h_D0pi0_a1Bu_; }
  RooRealVar &misId_Bu2Dst0h_D0pi0_a2Bu() { return misId_Bu2Dst0h_D0pi0_a2Bu_; }
  RooRealVar &misId_Bu2Dst0h_D0pi0_n1Bu() { return misId_Bu2Dst0h_D0pi0_n1Bu_; }
  RooRealVar &misId_Bu2Dst0h_D0pi0_n2Bu() { return misId_Bu2Dst0h_D0pi0_n2Bu_; }
  RooCBShape &pdf1Bu_misId_Bu2Dst0h_D0pi0() {
    return pdf1Bu_misId_Bu2Dst0h_D0pi0_;
  }
  RooCBShape &pdf2Bu_misId_Bu2Dst0h_D0pi0() {
    return pdf2Bu_misId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &misId_Bu2Dst0h_D0pi0_frac1PdfBu() {
    return misId_Bu2Dst0h_D0pi0_frac1PdfBu_;
  }
  RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() {
    return *pdfBu_misId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &orEffMisId_Bu2Dst0h_D0pi0() { return orEffMisId_Bu2Dst0h_D0pi0_; }
  RooRealVar &boxEffMisId_Bu2Dst0h_D0pi0() {
    return boxEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &buDeltaCutEffMisId_Bu2Dst0h_D0pi0() {
    return buDeltaCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  RooRealVar &deltaCutEffMisId_Bu2Dst0h_D0pi0() {
    return deltaCutEffMisId_Bu2Dst0h_D0pi0_;
  }
  // -------------------- MIS-REC -------------------- //
  RooRealVar &MisRec_sigmaBu() { return MisRec_sigmaBu_; }
  RooCBShape &pdfBu_MisRec() { return pdfBu_MisRec_; }
  RooRealVar &N_MisRec() { return N_MisRec_; }
  RooFormulaVar &N_Delta_MisRec() { return N_Delta_MisRec_; }
  RooAbsReal &N_Bu_MisRec() { return *N_Bu_MisRec_; }
  double &pidEff_Bu2Dst0h_D0gamma_WN() { return pidEff_Bu2Dst0h_D0gamma_WN_; }
  double &pidEff_Bu2Dst0h_D0pi0_WN() { return pidEff_Bu2Dst0h_D0pi0_WN_; }
  double &pidEff_Bu2D0hst() { return pidEff_Bu2D0hst_; }
  double &pidEff_Bd2Dsth() { return pidEff_Bd2Dsth_; }
  RooConstVar &pidEff_MisRec() { return pidEff_MisRec_; }
  // -------------------- Mis-ID ------------------- //
  RooRealVar &orEffMisId_MisRec() { return orEffMisId_MisRec_; }
  RooRealVar &boxEffMisId_MisRec() { return boxEffMisId_MisRec_; }
  RooRealVar &buDeltaCutEffMisId_MisRec() { return buDeltaCutEffMisId_MisRec_; }
  RooRealVar &deltaCutEffMisId_MisRec() { return deltaCutEffMisId_MisRec_; }
  // -------------------- Bu2D0h -------------------- //
  RooAbsReal &Bu2D0h_sigmaLBu() { return *Bu2D0h_sigmaLBu_; }
  RooAbsReal &Bu2D0h_sigmaRBu() { return *Bu2D0h_sigmaRBu_; }
  RooCruijff &pdfBu_Bu2D0h() { return pdfBu_Bu2D0h_; }
  RooRealVar &N_tot_Bu2D0h() { return N_tot_Bu2D0h_; }
  RooConstVar &pidEff_Bu2D0h() { return pidEff_Bu2D0h_; }
  RooFormulaVar &N_Bu2D0h() { return N_Bu2D0h_; }
  RooFormulaVar &N_Delta_Bu2D0h() { return N_Delta_Bu2D0h_; }
  RooAbsReal &N_Bu_Bu2D0h() { return *N_Bu_Bu2D0h_; }
  // -------------------- Mis-ID ------------------- //
  RooRealVar &misId_Bu2D0h_meanBu() { return misId_Bu2D0h_meanBu_; }
  RooRealVar &misId_Bu2D0h_sigmaLBu() { return misId_Bu2D0h_sigmaLBu_; }
  RooRealVar &misId_Bu2D0h_sigmaRBu() { return misId_Bu2D0h_sigmaRBu_; }
  RooRealVar &misId_Bu2D0h_aLBu() { return misId_Bu2D0h_aLBu_; }
  RooRealVar &misId_Bu2D0h_aRBu() { return misId_Bu2D0h_aRBu_; }
  RooCruijff &pdfBu_misId_Bu2D0h() { return pdfBu_misId_Bu2D0h_; }
  RooRealVar &orEffMisId_Bu2D0h() { return orEffMisId_Bu2D0h_; }
  RooRealVar &boxEffMisId_Bu2D0h() { return boxEffMisId_Bu2D0h_; }
  RooRealVar &buDeltaCutEffMisId_Bu2D0h() { return buDeltaCutEffMisId_Bu2D0h_; }
  RooRealVar &deltaCutEffMisId_Bu2D0h() { return deltaCutEffMisId_Bu2D0h_; }

  void SetMisIdEfficiencies(Mode mode, RooRealVar &orEff, RooRealVar &boxEff,
                            RooRealVar &buDeltaCutEff, RooRealVar &deltaCutEff);

 private:
  int uniqueId_;
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::unique_ptr<RooAbsReal> Bu2Dst0h_D0gamma_sigmaBu_;
  RooCBShape pdf1Bu_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Bu_Bu2Dst0h_D0gamma_;
  RooAddPdf pdfBu_Bu2Dst0h_D0gamma_;
  RooRealVar N_tot_Bu2Dst0h_D0gamma_;
  RooConstVar pidEff_Bu2Dst0h_D0gamma_;
  RooFormulaVar N_Bu2Dst0h_D0gamma_;
  RooFormulaVar N_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  // 1 = L, 2 = R for RooCruijff
  RooRealVar misId_Bu2Dst0h_D0gamma_meanBu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_sigma1Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_sigma2Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_a2Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_a1Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_n2Bu_;
  RooRealVar misId_Bu2Dst0h_D0gamma_n1Bu_;
  RooCBShape pdf1Bu_misId_Bu2Dst0h_D0gamma_;
  RooCBShape pdf2Bu_misId_Bu2Dst0h_D0gamma_;
  RooRealVar misId_Bu2Dst0h_D0gamma_frac1PdfBu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0gamma_;
  RooRealVar orEffMisId_Bu2Dst0h_D0gamma_;
  RooRealVar boxEffMisId_Bu2Dst0h_D0gamma_;
  RooRealVar buDeltaCutEffMisId_Bu2Dst0h_D0gamma_;
  RooRealVar deltaCutEffMisId_Bu2Dst0h_D0gamma_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar Bu2Dst0h_D0pi0_sigmaBu_;
  RooCBShape pdfBu_Bu2Dst0h_D0pi0_;
  RooRealVar N_tot_Bu2Dst0h_D0pi0_;
  RooConstVar pidEff_Bu2Dst0h_D0pi0_;
  RooFormulaVar N_Bu2Dst0h_D0pi0_;
  RooFormulaVar N_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  // 1 = L, 2 = R for RooCruijff
  RooRealVar misId_Bu2Dst0h_D0pi0_meanBu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_sigma1Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_sigma2Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_a2Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_a1Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_n2Bu_;
  RooRealVar misId_Bu2Dst0h_D0pi0_n1Bu_;
  RooCBShape pdf1Bu_misId_Bu2Dst0h_D0pi0_;
  RooCBShape pdf2Bu_misId_Bu2Dst0h_D0pi0_;
  RooRealVar misId_Bu2Dst0h_D0pi0_frac1PdfBu_;
  std::unique_ptr<RooAbsPdf> pdfBu_misId_Bu2Dst0h_D0pi0_;
  RooRealVar orEffMisId_Bu2Dst0h_D0pi0_;
  RooRealVar boxEffMisId_Bu2Dst0h_D0pi0_;
  RooRealVar buDeltaCutEffMisId_Bu2Dst0h_D0pi0_;
  RooRealVar deltaCutEffMisId_Bu2Dst0h_D0pi0_;
  // -------------------- MIS-REC -------------------- //
  RooRealVar MisRec_sigmaBu_;
  RooCBShape pdfBu_MisRec_;
  RooRealVar N_MisRec_;
  RooFormulaVar N_Delta_MisRec_;
  std::unique_ptr<RooAbsReal> N_Bu_MisRec_;
  double pidEff_Bu2Dst0h_D0gamma_WN_;
  double pidEff_Bu2Dst0h_D0pi0_WN_;
  double pidEff_Bu2D0hst_;
  double pidEff_Bd2Dsth_;
  RooConstVar pidEff_MisRec_;
  // -------------------- Mis-ID ------------------- //
  RooRealVar orEffMisId_MisRec_;
  RooRealVar boxEffMisId_MisRec_;
  RooRealVar buDeltaCutEffMisId_MisRec_;
  RooRealVar deltaCutEffMisId_MisRec_;
  // -------------------- Bu2D0h -------------------- //
  std::unique_ptr<RooAbsReal> Bu2D0h_sigmaLBu_;
  std::unique_ptr<RooAbsReal> Bu2D0h_sigmaRBu_;
  RooCruijff pdfBu_Bu2D0h_;
  RooRealVar N_tot_Bu2D0h_;
  RooConstVar pidEff_Bu2D0h_;
  RooFormulaVar N_Bu2D0h_;
  RooFormulaVar N_Delta_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2D0h_;
  // -------------------- Mis-ID ------------------- //
  RooRealVar misId_Bu2D0h_meanBu_;
  RooRealVar misId_Bu2D0h_sigmaLBu_;
  RooRealVar misId_Bu2D0h_sigmaRBu_;
  RooRealVar misId_Bu2D0h_aLBu_;
  RooRealVar misId_Bu2D0h_aRBu_;
  RooCruijff pdfBu_misId_Bu2D0h_;
  RooRealVar orEffMisId_Bu2D0h_;
  RooRealVar boxEffMisId_Bu2D0h_;
  RooRealVar buDeltaCutEffMisId_Bu2D0h_;
  RooRealVar deltaCutEffMisId_Bu2D0h_;
};

template <Neutral neutral, Bachelor bachelor>
void NeutralBachelorVars<neutral, bachelor>::SetMisIdEfficiencies(
    Mode mode, RooRealVar &orEff, RooRealVar &boxEff, RooRealVar &buDeltaCutEff,
    RooRealVar &deltaCutEff) {
  std::string dlString = std::to_string(Configuration::Get().deltaLow());
  std::string dhString = std::to_string(Configuration::Get().deltaHigh());
  std::string blString = std::to_string(Configuration::Get().buDeltaLow());
  std::string bhString = std::to_string(Configuration::Get().buDeltaHigh());
  std::string txtFileName = "txt_efficiencies/" + EnumToString(neutral) +
                            "_misId_" + EnumToString(mode) + "_as_" +
                            EnumToString(bachelor) + "_" + dlString + "_" +
                            dhString + "_" + blString + "_" + bhString + ".txt";
  std::string modeString = EnumToString(mode);

  // Check if txt file containing efficiencies for particular mode and box dimns
  // exists, if not, calculate eff and save in txt file
  if (!file_exists(txtFileName)) {
    std::string dirString;
    // std::cout << txtFileName
    //           << " doesn't exist:\n\tCalculating and setting efficiencies
    //           for"
    //           << modeString << "...\n";
    if (mode == Mode::Bu2Dst0pi_D0gamma_WN ||
        mode == Mode::Bu2Dst0pi_D0pi0_WN) {
      // To remove _WN for directory
      dirString = modeString.substr(0, modeString.size() - 3);
    } else {
      dirString = modeString;
    }

    std::string path;
    switch (neutral) {
      case Neutral::gamma:
        switch (bachelor) {
          case Bachelor::pi:
            path =
                "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
                "cross_feed_removed/";
            break;
          case Bachelor::k:
            path =
                "gamma/bach_K/tmva_stage1/tmva_stage2_loose/to_fit/"
                "cross_feed_removed/";
            break;
        }
        break;
      case Neutral::pi0:
        switch (bachelor) {
          case Bachelor::pi:
            path = "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/";
            break;
          case Bachelor::k:
            path = "gamma/bach_K/tmva_stage1/tmva_stage2_loose/to_fit/";
            break;
        }
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

    if (mode == Mode::Bu2D0rho || mode == Mode::Bd2Dstpi ||
        mode == Mode::Bu2D0pi) {
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

    std::string cutString;

    switch (neutral) {
      case Neutral::gamma:
        cutString = Configuration::Get().gammaCutString();
        break;
      case Neutral::pi0:
        cutString = Configuration::Get().pi0CutString();
        break;
    }
    // For now, stats too low to calculate eff with PID cut: get weighted distn?
    // switch (neutral) {
    //   case Neutral::gamma:
    //     switch (bachelor) {
    //       case Bachelor::pi:
    //         cutString = Configuration::Get().gammaCutString() +
    //         "&&bach_PIDK<12"; break;
    //       case Bachelor::k:
    //         cutString = Configuration::Get().gammaCutString() +
    //         "&&bach_PIDK>12"; break;
    //     }
    //     break;
    //   case Neutral::pi0:
    //     switch (bachelor) {
    //       case Bachelor::pi:
    //         cutString = Configuration::Get().pi0CutString() +
    //         "&&bach_PIDK<12"; break;
    //       case Bachelor::k:
    //         cutString = Configuration::Get().pi0CutString() +
    //         "&&bach_PIDK>12"; break;
    //     }
    //     break;
    // }

    double nInitial =
        chain.GetEntries(Configuration::Get().gammaCutString().c_str());
    double nDeltaCut = chain.GetEntries(
        (cutString + "&&Delta_M>" + dlString + "&&Delta_M<" + dhString)
            .c_str());
    double nBuCut = chain.GetEntries(
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

    double orEffVal = nOr / nInitial;
    double boxEffVal = nBox / nInitial;
    double deltaCutEffVal = nDeltaCut / nInitial;
    double buDeltaCutEffVal = nBuCut / nInitial;

    std::ofstream outFile;
    outFile.open(txtFileName);
    outFile << "orEff " + std::to_string(orEffVal) + "\n";
    outFile << "boxEff " + std::to_string(boxEffVal) + "\n";
    outFile << "deltaCutEff " + std::to_string(deltaCutEffVal) + "\n";
    outFile << "buDeltaCutEff " + std::to_string(buDeltaCutEffVal) + "\n";
    outFile.close();

    boxEff.setVal(boxEffVal);
    deltaCutEff.setVal(deltaCutEffVal);
    buDeltaCutEff.setVal(buDeltaCutEffVal);
    if (Configuration::Get().fit1D() == false) {
      orEff.setVal(orEffVal);
    } else {
      orEff.setVal(deltaCutEffVal);
    }
  } else {
    // If exists, read in from txt file
    // std::cout << txtFileName << " exists:\n\tReading efficiencies for "
    //           << modeString << "...\n";
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
    deltaCutEff.setVal(effMap.at("deltaCutEff"));
    buDeltaCutEff.setVal(effMap.at("buDeltaCutEff"));
    if (Configuration::Get().fit1D() == false) {
      orEff.setVal(effMap.at("orEff"));
    } else {
      orEff.setVal(effMap.at("deltaCutEff"));
    }
  }
  // std::cout << "\t orEff = " << orEff.getVal() << "\n"
  //           << "\t boxEff = " << boxEff.getVal() << "\n"
  //           << "\t buDeltaCutEff = " << buDeltaCutEff.getVal() << "\n"
  //           << "\t deltaCutEff = " << deltaCutEff.getVal() << "\n";
}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId);
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId);
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId);
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId);
