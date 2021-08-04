#include "Params.h"
#include <random>

Params::Params()
    : fixed_parameters_(),
      floating_parameters_(),
      group_map_{
          {Group::Pdfs,
           std::vector<Systematic>{
               Systematic::Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi,
               Systematic::Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi,
               Systematic::Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi,
               Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails,
               Systematic::Bu2Dst0h_D0pi0_PdfDelta_Frac,
               Systematic::Bu2Dst0h_D0pi0_PdfBu_SigmaRatioKpi,
               Systematic::Bu2Dst0h_D0pi0_PdfBu_Tails,
               Systematic::Bu2Dst0h_D0pi0_PdfBu_Frac,
               Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_MeanOffset,
               Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatioKpi,
               Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatio,
               Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Tails,
               Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Frac,
               Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Sigma1,
               Systematic::Bu2Dst0h_D0pi0_PdfBu,
               Systematic::Bu2Dst0h_D0gamma_PdfBuPartial,
               Systematic::Bu2Dst0h_D0gamma_PdfDelta_SigmaRatioKpi,
               Systematic::Bu2Dst0h_D0gamma_PdfDelta_Tails,
               Systematic::Bu2Dst0h_D0gamma_PdfDelta_Frac,
               Systematic::Bu2Dst0h_D0gamma_PdfBu_SigmaRatioKpi,
               Systematic::Bu2Dst0h_D0gamma_PdfBu_Tails,
               Systematic::Bu2Dst0h_D0gamma_PdfBu_Frac,
               Systematic::Bu2Dst0h_D0pi0_WN_PdfDelta,
               Systematic::Bu2Dst0h_D0pi0_WN_PdfBu,
               Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial,
               Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta,
               Systematic::Bu2Dst0h_D0gamma_WN_PdfBu,
               Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial,
               Systematic::Bd2Dsth_PdfDelta,
               Systematic::Bd2Dsth_PdfBu,
               Systematic::Bd2Dsth_PdfBuPartial,
               Systematic::Bu2D0hst_PdfDelta,
               Systematic::Bu2D0hst_PdfDelta_D02pik,
               Systematic::Bu2D0hst_PdfBu,
               Systematic::Bu2D0hst_PdfBu_D02pik,
               Systematic::Bu2D0hst_PdfBuPartial,
               Systematic::Bu2Dst0hst_D0gamma_PdfDelta,
               Systematic::Bu2Dst0hst_D0gamma_PdfBu,
               Systematic::Bu2Dst0hst_D0gamma_PdfBuPartial,
               Systematic::Bu2Dst0hst_D0pi0_PdfDelta,
               Systematic::Bu2Dst0hst_D0pi0_PdfBu,
               Systematic::Bu2Dst0hst_D0pi0_PdfBuPartial,
               Systematic::Bu2Dst0hst_PdfBu_D02pik,
               Systematic::Bu2Dst0hst_Frac,
               Systematic::Lb2Omegach_Lcpi0_PdfDelta,
               Systematic::Lb2Omegach_Lcpi0_PdfBu,
               Systematic::Lb2Omegach_Lcpi0_PdfBuPartial,
               Systematic::Bs2Dst0Kst0_Frac,
               Systematic::Bs2Dst0Kst0_PdfDelta,
               Systematic::Bs2Dst0Kst0,
               Systematic::Bs2Dst0Kst0_WN,
               Systematic::Bs2D0Kst0_PdfDelta,
               Systematic::Bs2D0Kst0_PdfBu,
               Systematic::Bs2D0Kst0_PdfBuPartial,
               Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs,
               Systematic::Bu2Dst0pi_D0pi0_asK_Pdfs,
               Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs,
               Systematic::Bu2Dst0pi_D0gamma_asK_Pdfs,
               Systematic::Bu2Dst0h_WN_misId_Pdfs,
               Systematic::Bkg_misId_Pdfs,
               Systematic::D02pik_Pdfs}},
          {Group::Pdfs,
           std::vector<Systematic>{
               Systematic::boxEffs_Bu2Dst0h_D0pi0,
               Systematic::boxEffs_Bu2Dst0h_D0gamma, Systematic::boxEffs_Bkg,
               Systematic::boxEffs_D02pik,
               Systematic::boxEffs_Bu2Dst0h_D0pi0_misId,
               Systematic::boxEffs_Bu2Dst0h_D0gamma_misId,
               Systematic::boxEffs_Bkg_misId, Systematic::mcEffs_Bu2Dst0h_D0pi0,
               Systematic::mcEffs_Bu2Dst0h_D0gamma, Systematic::mcEffs_Bkg,
               Systematic::mcEffs_Bu2Dst0h_D0pi0_misId,
               Systematic::mcEffs_Bu2Dst0h_D0gamma_misId,
               Systematic::mcEffs_Bkg_misId, Systematic::pidEffPi,
               Systematic::pidEffK}},
          {Group::Rates,
           std::vector<Systematic>{
               Systematic::Bu2D0hst_BkgFrac, Systematic::Bu2Dst0hst_BkgFrac,
               Systematic::crossFeedRate, Systematic::kBF_D02kpi,
               Systematic::kBF_D02kk, Systematic::kBF_D02pipi}},
          {Group::Asyms,
           std::vector<Systematic>{Systematic::A_Kpi, Systematic::A_pi,
                                   Systematic::Delta_A_CP}},
          {Group::CPPars,
           std::vector<Systematic>{
               Systematic::A_pi_Kpi_Bu2Dst0h_D0pi0,
               Systematic::A_pi_Kpi_Bu2Dst0h_D0gamma,
               Systematic::A_pi_Kpi_Bu2Dst0hst, Systematic::A_K_Kpi_Bu2Dst0hst,
               Systematic::A_K_piK_Bu2D0hst, Systematic::R_CP_Bu2D0hst,
               Systematic::R_ADS_Bu2D0hst, Systematic::R_Dst0KDst0pi_Bd2Dsth,
               Systematic::R_Dst0KDst0pi_Lb2Omegach_Lcpi0,
               Systematic::R_CP_Bu2Dst0h_D0gamma,
               Systematic::A_CP_pi_Bu2Dst0h_D0gamma,
               Systematic::A_CP_K_Bu2Dst0h_D0gamma,
               Systematic::R_piK_Bu2Dst0h_D0gamma,
               Systematic::A_K_Kpi_Bu2Dst0h_D0gamma,
               Systematic::R_ADS_Bu2Dst0hst, Systematic::A_K_piK_Bu2Dst0hst,
               Systematic::A_CP_K_Lb2Omegach_Lcpi0}}} {}

RooUnblindUniform *MakeBlind(const char *uniqueName, double range,
                             RooAbsReal &paramToBlind) {
  // convert const char to string
  std::string blindStr(uniqueName);
  std::string s("_WN");
  // std::cout << "Blinding parameter " << blindStr << "\n";
  if (blindStr.find(s) != std::string::npos) {
    // std::cout << "String contains " << s <<  "\n";
    // find returns starting position of string. Erase removes number of symbols
    // fromthis position
    blindStr.erase(blindStr.find(s), 3);
  } 
  // std::cout << "String to blind with = " << blindStr << "\n";
  return new RooUnblindUniform(uniqueName, "Blind", blindStr.c_str(), range,
                               paramToBlind);
}
RooFormulaVar *MakeLittleAsym(const char *name, RooAbsReal &bigAsym) {
  return new RooFormulaVar(name, "", "(1+@0)/(1-@0)", RooArgSet(bigAsym));
}

void FixedParameter::AdjustBoxEffErr() {
  // Efficiencies have symmetric errors
  std::smatch effMatch;
  static const std::regex effRgx("(or|delta|bu|buPartial)Eff\\S+");
  if (std::regex_match(name_, effMatch, effRgx)) {
    double std_tmp = std_pos_;
    double abs_err = 0.03;
    std::smatch modeMatch;
    static const std::regex modeRgx(
        "deltaEff(Bu2D0hst|Bu2Dst0hst)\\S+");
    if (std::regex_match(name_, modeMatch, modeRgx)) {
      abs_err = 0.1;
    }
    std::cout << mean_ << "\n";
    if (std_tmp < abs_err) {
      std_tmp = abs_err;
    }
    std_pos_ = std_tmp;
    std_neg_ = std_tmp;
  }
}

void FixedParameter::Randomise(TRandom3 &random) {
  std::cout << "\n\n--------------------------------------------------------------\n";
  std::cout << "FixedParameter::Randomise\n";
  double shifted_value, std;
  std::smatch match;
  static const std::regex pattern("\\S+Eff\\S+");
  if (std::regex_match(name_, match, pattern)) {
    std::cout << "0 < Efficiency < 1\n";
    AdjustBoxEffErr();
    if (std_pos_ == std_neg_) {
      std = std_pos_;
      std::cout << "std = " << std << "\n";
    } else {
      throw std::runtime_error(
          "Params.cpp FixedParameter::Randomise: no implementation for "
          "asymmetric errors of "
          "efficiencies");
    }
    shifted_value = random.Gaus(mean_, std);
    std::cout << "First choice: " << shifted_value << "\n";
    while (shifted_value > 1 || shifted_value < 0) {
      std::random_device rd;
      std::default_random_engine rng(rd());
      std::uniform_int_distribution<UInt_t> dist;
      UInt_t seed = dist(rng);
      // UInt_t seed = 0xbabe652;
      RooRandom::randomGenerator()->SetSeed(seed);
      TRandom3 random(seed);
      shifted_value = random.Gaus(mean_, std);
      std::cout << "Try again: " << shifted_value << "\n";
    }
  } else {
    // Randomly choose +ve/-ve shift
    int shift_dir;
    double tmp = random.Gaus(0, 1);
    std::cout << "std_pos_ = " << std_pos_ << "\n";
    std::cout << "std_neg_ = " << std_neg_ << "\n";
    if (tmp < 0) {
      // If std_pos_ = std_neg_, doesn't matter. If not, choosed correct one
      shift_dir = -1;
      std = std_neg_;
    } else {
      shift_dir = 1;
      std = std_pos_;
    }
    std::cout << "shift dir (+1/-1) = " << shift_dir << "\n";
    std::cout << "std = " << std << "\n";
    shifted_value = random.Gaus(mean_, std);
    // If shift_dir > 0, mean < shifted_value
    // If shift_dir < 0, mean > shifted_value
    std::cout << "First choice: " << shifted_value << "\n";
    while ((sym_ == false && ((mean_ - shifted_value) * shift_dir > 0)) ||
           (sign_ == Sign::same && (mean_ * shifted_value < 0))) {
      std::random_device rd;
      std::default_random_engine rng(rd());
      std::uniform_int_distribution<UInt_t> dist;
      UInt_t seed = dist(rng);
      // UInt_t seed = 0xbabe652;
      RooRandom::randomGenerator()->SetSeed(seed);
      TRandom3 random(seed);
      shifted_value = random.Gaus(mean_, std);
      std::cout << "Try again: " << shifted_value << "\n";
    }
  }
  std::cout << "\t" << name_ << ": " << mean_ << " --> " << shifted_value
            << "\n";
  std::cout << "--------------------------------------------------------------\n\n";
  roo_variable_->setVal(shifted_value);
}

double Params::ReturnValErr(Mode mode, Neutral neutral, Bachelor bachelor,
                   std::string const &parName, Param param) {
  // For Delta PDF of Bs2Dst0Kst0 modes, use signal values (but still retain own
  // parameter name for systematics)
  std::string parNameToRead = parName;
  std::smatch match;
  static const std::regex pattern("(Bs2Dst0Kst0_D0(pi0|gamma))_(\\S+)");
  if (std::regex_match(parName, match, pattern)) {
    std::smatch m;
    static const std::regex re("Bu2Dst0(pi|K)_(\\S+)");
    std::string modeStr = EnumToString(mode);
    if (std::regex_match(modeStr, m, re)) {
      std::stringstream ss_par;
      ss_par << "Bu2Dst0h_D0" << match[2] << "_" << match[3];
      parNameToRead = ss_par.str();
    }
  }
  std::string bachStr = EnumToString(bachelor);
  if (bachelor == Bachelor::k) {
    bachStr = "K";
  }
  std::string fname;
  if (mode == Mode::Bs2Dst0Kst0_D0pi0 || mode == Mode::Bs2Dst0Kst0_D0gamma) {
    fname = Configuration::Get().inputDir + "/mc_roofit_results/MC_" +
            EnumToString(neutral) + "_" + EnumToString(mode) + "_" + bachStr +
            "_" + to_string_with_precision(Configuration::Get().fracKst0(), 1);
  } else {
    fname = Configuration::Get().inputDir + "/mc_roofit_results/MC_" +
            EnumToString(neutral) + "_" + EnumToString(mode) + "_" + bachStr;
  }
  if ((mode == Mode::Bu2D0rho && bachelor == Bachelor::pi) ||
      (mode == Mode::Bu2D0Kst && bachelor == Bachelor::k) ||
      (mode == Mode::Bs2D0Kst0 && bachelor == Bachelor::k)) {
  //     (mode == Mode::Bu2D0Kst && bachelor == Bachelor::k)) {
  // if (mode == Mode::Bs2D0Kst0 && bachelor == Bachelor::k) {
    fname += "_weights";
  }
  fname += ".root";
  auto file = std::unique_ptr<TFile>(TFile::Open(fname.c_str()));
  if (file == nullptr) {
    throw std::runtime_error(fname + " does not exist\n");
  }
  auto fitResult = std::unique_ptr<RooFitResult>(
      dynamic_cast<RooFitResult *>(file->FindObjectAny("FitResult")));
  RooArgList constPars = fitResult->constPars();
  RooArgList floatPars = fitResult->floatParsFinal();
  RooAbsArg *absArg = nullptr;
  absArg = constPars.find(parNameToRead.c_str());
  if (absArg == nullptr) {
    absArg = floatPars.find(parNameToRead.c_str());
    if (absArg == nullptr) {
      // std::cout << fname << "\n";
      // fitResult->Print();
      throw std::runtime_error("Cannot find parameter " + parNameToRead +
                               " in fit result: " +
                               fname);
    } 
  }
  RooRealVar *realVar = dynamic_cast<RooRealVar *>(absArg);
  if (realVar == nullptr) {
    throw std::runtime_error("Canot cast AbsArg to AbsReal for " + parNameToRead);
  }
  // std::cout << parNameToRead << "," << realVar->getVal() << "," << realVar->getError()
  //           << "\n";
  if (param == Param::val) {
    return realVar->getVal();
  } else {
    return realVar->getError();
  }
}
