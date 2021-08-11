#include <algorithm>
#include <cmath>
#include <experimental/filesystem>
#include <iomanip>
#include <regex>
#include <sstream>

#include "Configuration.h"

Configuration::Configuration()
    : neutral_(),
      fitting("fitting", "fitting"),
      dataLabel("dataLabel", "dataLabel"),
      buMass_("", "", 0, 0, ""),
      buDeltaMass_("", "", 0, 0, ""),
      deltaMass_("", "", 0, 0, ""),
      pi0Mass_("", "", 0, 0, ""),
      d0hMass_("", "", 0, 0, ""),
      buPdgId_("", "", 0, 0, ""),
      bachPID_("", "", 0, 0, ""),
      h1ID_("", "", 0, 0, ""),
      h2ID_("", "", 0, 0, ""),
      h1PID_("", "", 0, 0, ""),
      h2PID_("", "", 0, 0, ""),
      BDT1_("", "", 0, 0, ""),
      BDT2_("", "", 0, 0, ""),
      hAngle_("", "", 0, 0, ""),
      d0FdSig_("", "", 0, 0, ""),
      d0Mass_("", "", 0, 0, ""),
      d0MassSwap_("", "", 0, 0, ""),
      buDeltaLow_(5240.0),
      buDeltaHigh_(5330.0),
      deltaLow_(125.0),
      deltaHigh_(170.0),
      deltaPartialLow_(60.0),
      deltaPartialHigh_(105.0),
      gammaCutString_(
          "Bu_Delta_M>5050&&Bu_Delta_M<5500&&Delta_M>60&&Delta_M<190&&BDT1>0."
          "05&&BDT2>0.05&&D0h_M>4900&&D0_FD_ZSIG>2&&D0h_M<5200"),
      pi0CutString_(
          "Bu_Delta_M>5050&&Bu_Delta_M<5450&&Delta_M>60&&Delta_M<190&&BDT1>0."
          "05&&BDT2>0&&Pi0_M<165&&Pi0_M>125&&D0h_M>4900&&D0_FD_ZSIG>2&&D0h_"
          "M<5200"),
      inputDir(""),
      fit1D_(false),
      runToy_(false),
      splitByCharge_(false),
      noFit_(false),
      fitBuPartial_(false),
      blindFit_(true),
      runSystematics_(false),
      runADS_(false),
      plotToys_(false),
      simpleFit_(false),
      nCPU_(4),
      runBsSystematic_(false),
      runCombSystematic_(false),
      fracKst0_(0.8),
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
               Systematic::D02pik_Pdfs,
               Systematic::Combinatorial}},
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
               Systematic::A_CP_K_Lb2Omegach_Lcpi0}}} {
  // k_A_CP_Bu2Dst0K_D0pi0_D02kpi(),
  // k_A_CP_Bu2Dst0K_D0gamma_D02kpi(),
  // k_A_CP_Bu2Dst0K_D0pi0_D02hh(),
  // k_A_CP_Bu2Dst0K_D0gamma_D02hh(),
  // k_R_CP_Bu2Dst0pi_D0pi0(),
  // k_R_CP_Bu2Dst0pi_D0gamma(),
  // k_R_CP_Bu2Dst0K_D0pi0(),
  // k_R_CP_Bu2Dst0K_D0gamma(),
  // k_R_piK_Bu2Dst0pi_D0pi0(),
  // k_R_piK_Bu2Dst0pi_D0gamma(),
  // k_R_piK_Bu2Dst0K_D0pi0(),
  // k_R_piK_Bu2Dst0K_D0gamma() {
  // constexpr means they're known at compile time and immutable (unchangable)
  constexpr const char *kMassUnit = "MeV/c^{2}";
  constexpr const char *kMomentumUnit = "MeV/c";
  constexpr const char *kNoUnit = "";

  buMass_.SetName("Bu_M_DTF");
  buMass_.SetTitle("m(B)");
  buMass_.setMax(5800);
  buMass_.setMin(4900);
  buMass_.setBins(75);
  // buMass_.setMax(6000);
  // buMass_.setMin(4000);
  // buMass_.setBins(400);
  buMass_.setUnit(kMassUnit);

  buDeltaMass_.SetName("Bu_Delta_M");
  buDeltaMass_.SetTitle("m(D^{*}h)");
  buDeltaMass_.setMax(5500);
  // buDeltaMass_.setMax(5600);
  buDeltaMass_.setMin(5050);
  buDeltaMass_.setBins(45);
  // buDeltaMass_.setBins(55);
  // buDeltaMass_.setMax(6000);
  // buDeltaMass_.setMin(4000);
  // buDeltaMass_.setBins(400);
  buDeltaMass_.setUnit(kMassUnit);

  deltaMass_.SetName("Delta_M");
  deltaMass_.SetTitle("m(D^{*0}) - m(D^{0})");
  deltaMass_.setMax(190);
  deltaMass_.setMin(60);
  deltaMass_.setBins(65);
  // deltaMass_.setMax(250);
  // deltaMass_.setMin(0);
  // deltaMass_.setBins(125);
  deltaMass_.setUnit(kMassUnit);

  pi0Mass_.SetName("Pi0_M");
  pi0Mass_.SetTitle("m(#pi^{0})");
  pi0Mass_.setMax(185);
  pi0Mass_.setMin(110);
  pi0Mass_.setUnit(kMassUnit);

  d0hMass_.SetName("D0h_M");
  d0hMass_.SetTitle("m(D^{0}h)");
  d0hMass_.setMax(6000);
  d0hMass_.setMin(4000);
  d0hMass_.setBins(400);
  d0hMass_.setUnit(kMassUnit);

  buPdgId_.SetName("Bu_ID");
  buPdgId_.SetTitle("Bu PDG ID");
  buPdgId_.setMax(550);
  buPdgId_.setMin(-550);
  buPdgId_.setUnit(kNoUnit);

  bachPID_.SetName("bach_PIDK");
  bachPID_.SetTitle("Bachelor PIDK");
  bachPID_.setMax(150);
  bachPID_.setMin(-150);
  bachPID_.setUnit(kNoUnit);

  h1ID_.SetName("h1_D_ID");
  h1ID_.SetTitle("h1 D0 daughter ID");

  buPdgId_.SetName("Bu_ID");
  buPdgId_.SetTitle("Bu PDG ID");
  buPdgId_.setMax(550);
  buPdgId_.setMin(-550);
  buPdgId_.setUnit(kNoUnit);

  bachPID_.SetName("bach_PIDK");
  bachPID_.SetTitle("Bachelor PIDK");
  bachPID_.setMax(150);
  bachPID_.setMin(-150);
  bachPID_.setUnit(kNoUnit);

  h1ID_.SetName("h1_D_ID");
  h1ID_.SetTitle("h1 D0 daughter ID");
  h1ID_.setMax(550);
  h1ID_.setMin(-550);
  h1ID_.setUnit(kNoUnit);

  h2ID_.SetName("h2_D_ID");
  h2ID_.SetTitle("h2 D0 daughter ID");
  h2ID_.setMax(550);
  h2ID_.setMin(-550);
  h2ID_.setUnit(kNoUnit);

  h1PID_.SetName("h1_D_PIDK");
  h1PID_.SetTitle("h1 D0 daughter PIDK");
  h1PID_.setMax(150);
  h1PID_.setMin(-150);
  h1PID_.setUnit(kNoUnit);

  h2PID_.SetName("h2_D_PIDK");
  h2PID_.SetTitle("h2 D0 daughter PIDK");
  h2PID_.setMax(150);
  h2PID_.setMin(-150);
  h2PID_.setUnit(kNoUnit);

  BDT1_.SetName("BDT1");
  BDT1_.SetTitle("BDT1");
  BDT1_.setMax(0.5);
  BDT1_.setMin(-0.2);
  BDT1_.setUnit(kNoUnit);

  BDT2_.SetName("BDT2");
  BDT2_.SetTitle("BDT2");
  BDT2_.setMax(0.4);
  BDT2_.setMin(-0.3);
  BDT2_.setUnit(kNoUnit);

  hAngle_.SetName("DstNeut_Dst0_hAngle");
  hAngle_.SetTitle("Helicity Angle of neutral in D^{*0} rest frame");
  hAngle_.setMax(1);
  hAngle_.setMin(-1);

  d0FdSig_.setUnit(kNoUnit);
  d0FdSig_.SetName("D0_FD_ZSIG");
  d0FdSig_.SetTitle("D0 z-axis flight distance significance");
  d0FdSig_.setMax(300);
  d0FdSig_.setMin(-100);
  d0FdSig_.setUnit(kNoUnit);

  d0Mass_.setUnit(kMassUnit);
  d0Mass_.SetName("D0_M");
  d0Mass_.SetTitle("");
  d0Mass_.setMax(3000);
  d0Mass_.setMin(1000);
  d0Mass_.setUnit(kNoUnit);

  d0MassSwap_.setUnit(kMassUnit);
  d0MassSwap_.SetName("D0_M_DOUBLESW_KP");
  d0MassSwap_.SetTitle("");
  d0MassSwap_.setMax(3000);
  d0MassSwap_.setMin(1000);
  d0MassSwap_.setUnit(kNoUnit);

  variableArgSet_.add(buMass_);
  variableArgSet_.add(buDeltaMass_);
  variableArgSet_.add(deltaMass_);
  variableArgSet_.add(pi0Mass_);
  variableArgSet_.add(d0hMass_);
  variableArgSet_.add(buPdgId_);
  variableArgSet_.add(bachPID_);
  variableArgSet_.add(h1ID_);
  variableArgSet_.add(h2ID_);
  variableArgSet_.add(h1PID_);
  variableArgSet_.add(h2PID_);
  variableArgSet_.add(BDT1_);
  variableArgSet_.add(BDT2_);
  variableArgSet_.add(hAngle_);
  variableArgSet_.add(d0FdSig_);

  fullArgSet_.add(variableArgSet_);

  fittingArgSet_.add(buDeltaMass_);
  fittingArgSet_.add(deltaMass_);
}

// Function returns delta mass string if 1D fit, full box dimns if D1D fit
std::string Configuration::ReturnBoxString() {
  std::ostringstream out;
  if (fitBuPartial_ == true) {
    if (fit1D_ == true) {
      out << deltaPartialLow_ << "_" << deltaPartialHigh_ << "_" << deltaLow_
          << "_" << deltaHigh_;
    } else {
      out << deltaPartialLow_ << "_" << deltaPartialHigh_ << "_" << deltaLow_
          << "_" << deltaHigh_ << "_" << buDeltaLow_ << "_" << buDeltaHigh_;
    }
  } else {
    if (fit1D_ == true) {
      out << deltaLow_ << "_" << deltaHigh_;
    } else {
      out << deltaLow_ << "_" << deltaHigh_ << "_" << buDeltaLow_ << "_"
          << buDeltaHigh_;
    }
  }
  return out.str();
}

std::string to_string_with_precision(double value, int precision) {
  std::ostringstream out;
  out << std::fixed << std::setprecision(precision) << value;
  return out.str();
}

bool fexists(const std::string &name) {
  std::ifstream infile(name);
  return infile.good();
}

std::vector<std::string> SplitLine(std::string const &str) {
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


void ReadFromFile(ReturnType returnType, std::string const &paramName,
                  double &returnVal, std::string const &txtFileName,
                  std::string const &errorStr) {
  if (!fexists(txtFileName)) {
    std::cerr << "\n!!!!!!!!!!ReadFromFile: " << txtFileName
              << " doesn't exist: setting frac to 1.0 and error to "
                 "0.0.!!!!!!!!!!\n\n";
    if (returnType == ReturnType::val) {
      returnVal = 1.0;
    } else {
      returnVal = 0.0;
    }
  }
  std::ifstream inFile(txtFileName);
  std::string line;
  // Loop over lines in txt file
  while (std::getline(inFile, line)) {
    // Separate label and value (white space)
    std::vector<std::string> lineVec = SplitLine(line);
    if (lineVec[0] == paramName) {
      if (returnType == ReturnType::val) {
        returnVal = std::stod(lineVec[1]);
      } else if (returnType == ReturnType::std) {
        returnVal = std::stod(lineVec[2]);
      } else if (returnType == ReturnType::stdL) {
        returnVal = std::stod(lineVec[2]);
      } else if (returnType == ReturnType::stdH) {
        returnVal = std::stod(lineVec[3]);
      } else {
        throw std::runtime_error(errorStr);
      }
    }
  }
}

double ReadGammaObs(const char *paramName, ReturnType returnType) {
  std::string txtFileName =
      Configuration::Get().inputDir + "/fixed_rates/gamma_obs.txt";
  double returnVal;
  std::string errorStr =
      "ReadGammaObs: return type = val/stdL/stdH (asymmetric errors)\n";
  ReadFromFile(returnType, paramName, returnVal, txtFileName, errorStr);
  return returnVal;
}

template <>
Mode StringToEnum<Mode>(std::string const &mode) {
  if (mode == "Bs2Dst0Kst0") {
    return Mode::Bs2Dst0Kst0;
  } else if (mode == "Bs2Dst0Kst0_D0pi0") {
    return Mode::Bs2Dst0Kst0_D0pi0;
  } else if (mode == "Bs2Dst0Kst0_D0gamma") {
    return Mode::Bs2Dst0Kst0_D0gamma;
  } else if (mode == "Bs2Dst0Kst0_D0pi0_WN") {
    return Mode::Bs2Dst0Kst0_D0pi0_WN;
  } else if (mode == "Bs2Dst0Kst0_D0gamma_WN") {
    return Mode::Bs2Dst0Kst0_D0gamma_WN;
  } else if (mode == "Bs2Dst0Kpi") {
    return Mode::Bs2Dst0Kpi;
  } else if (mode == "Bs2Dst0Kpi_D0pi0") {
    return Mode::Bs2Dst0Kpi_D0pi0;
  } else if (mode == "Bs2Dst0Kpi_D0gamma") {
    return Mode::Bs2Dst0Kpi_D0gamma;
  } else if (mode == "Bs2Dst0Kpi_D0pi0_WN") {
    return Mode::Bs2Dst0Kpi_D0pi0_WN;
  } else if (mode == "Bs2Dst0Kpi_D0gamma_WN") {
    return Mode::Bs2Dst0Kpi_D0gamma_WN;
  } else if (mode == "Bs2D0Kst0") {
    return Mode::Bs2D0Kst0;
  } else if (mode == "Bd2Dstpi") {
    return Mode::Bd2Dstpi;
  } else if (mode == "Bd2DstK") {
    return Mode::Bd2DstK;
  } else if (mode == "Bu2D0pi") {
    return Mode::Bu2D0pi;
  } else if (mode == "Bu2D0K") {
    return Mode::Bu2D0K;
  } else if (mode == "Bu2D0rho") {
    return Mode::Bu2D0rho;
  } else if (mode == "Bu2D0Kst") {
    return Mode::Bu2D0Kst;
  } else if (mode == "Bu2Dst0rho_D0gamma") {
    return Mode::Bu2Dst0rho_D0gamma;
  } else if (mode == "Bu2Dst0rho_D0pi0") {
    return Mode::Bu2Dst0rho_D0pi0;
  } else if (mode == "Bu2Dst0rho") {
    return Mode::Bu2Dst0rho;
  } else if (mode == "Bu2Dst0Kst_D0gamma") {
    return Mode::Bu2Dst0Kst_D0gamma;
  } else if (mode == "Bu2Dst0Kst_D0pi0") {
    return Mode::Bu2Dst0Kst_D0pi0;
  } else if (mode == "Bu2Dst0Kst") {
    return Mode::Bu2Dst0Kst;
  } else if (mode == "Bu2Dst0pi_D0gamma") {
    return Mode::Bu2Dst0pi_D0gamma;
  } else if (mode == "Bu2Dst0pi_D0pi0") {
    return Mode::Bu2Dst0pi_D0pi0;
  } else if (mode == "Bu2Dst0K_D0gamma") {
    return Mode::Bu2Dst0K_D0gamma;
  } else if (mode == "Bu2Dst0K_D0pi0") {
    return Mode::Bu2Dst0K_D0pi0;
  } else if (mode == "Bu2Dst0pi_D0gamma_WN") {
    return Mode::Bu2Dst0pi_D0gamma_WN;
  } else if (mode == "Bu2Dst0pi_D0pi0_WN") {
    return Mode::Bu2Dst0pi_D0pi0_WN;
  } else if (mode == "Bu2Dst0K_D0gamma_WN") {
    return Mode::Bu2Dst0K_D0gamma_WN;
  } else if (mode == "Bu2Dst0K_D0pi0_WN") {
    return Mode::Bu2Dst0K_D0pi0_WN;
  } else if (mode == "Bu2Dst0pi_D0gamma_D02pik") {
    return Mode::Bu2Dst0pi_D0gamma_D02pik;
  } else if (mode == "Bu2Dst0pi_D0pi0_D02pik") {
    return Mode::Bu2Dst0pi_D0pi0_D02pik;
  } else if (mode == "Bu2Dst0K_D0gamma_D02pik") {
    return Mode::Bu2Dst0K_D0gamma_D02pik;
  } else if (mode == "Bu2Dst0K_D0pi0_D02pik") {
    return Mode::Bu2Dst0K_D0pi0_D02pik;
  } else if (mode == "Bu2Dst0pi_D0gamma_WN_D02pik") {
    return Mode::Bu2Dst0pi_D0gamma_WN_D02pik;
  } else if (mode == "Bu2Dst0pi_D0pi0_WN_D02pik") {
    return Mode::Bu2Dst0pi_D0pi0_WN_D02pik;
  } else if (mode == "Bu2Dst0K_D0gamma_WN_D02pik") {
    return Mode::Bu2Dst0K_D0gamma_WN_D02pik;
  } else if (mode == "Bu2Dst0K_D0pi0_WN_D02pik") {
    return Mode::Bu2Dst0K_D0pi0_WN_D02pik;
  } else if (mode == "Bu2Dst0pi_WN") {
    return Mode::Bu2Dst0pi_WN;
  } else if (mode == "Bu2Dst0K_WN") {
    return Mode::Bu2Dst0K_WN;
  } else if (mode == "Lb2Omegacpi_Lcpi0") {
    return Mode::Lb2Omegacpi_Lcpi0;
  } else if (mode == "Lb2OmegacK_Lcpi0") {
    return Mode::Lb2OmegacK_Lcpi0;
  }
  throw std::invalid_argument("Invalid mode passed to StringToEnum");
}

template <>
Group StringToEnum<Group>(std::string const &group) {
  if (group == "Pdfs") {
    return Group::Pdfs;
  } else if (group == "Effs") {
    return Group::Effs;
  } else if (group == "Rates") {
    return Group::Rates;
  } else if (group == "Asyms") {
    return Group::Asyms;
  } else if (group == "CPPars") {
    return Group::CPPars;
  }
  throw std::invalid_argument("Invalid Group passed to StringToEnum");
}

// Need a template for this as each enum option is a different 'type'
template <>
Systematic StringToEnum<Systematic>(std::string const &systematic) {
  if (systematic == "Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi") {
    return Systematic::Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfDelta_Tails") {
    return Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfDelta_Frac") {
    return Systematic::Bu2Dst0h_D0pi0_PdfDelta_Frac;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBu_SigmaRatioKpi") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBu_SigmaRatioKpi;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBu_Tails") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBu_Tails;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBu_Frac") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBu_Frac;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBuPartial_MeanOffset") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_MeanOffset;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatioKpi") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatioKpi;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatio") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatio;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBuPartial_Tails") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Tails;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBuPartial_Frac") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Frac;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBuPartial_Sigma1") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Sigma1;
  } else if (systematic == "Bu2Dst0h_D0pi0_PdfBu") {
    return Systematic::Bu2Dst0h_D0pi0_PdfBu;
  } else if (systematic == "Bu2Dst0h_D0gamma_PdfBuPartial") {
    return Systematic::Bu2Dst0h_D0gamma_PdfBuPartial;
  } else if (systematic == "Bu2Dst0h_D0gamma_PdfDelta_SigmaRatioKpi") {
    return Systematic::Bu2Dst0h_D0gamma_PdfDelta_SigmaRatioKpi;
  } else if (systematic == "Bu2Dst0h_D0gamma_PdfDelta_Tails") {
    return Systematic::Bu2Dst0h_D0gamma_PdfDelta_Tails;
  } else if (systematic == "Bu2Dst0h_D0gamma_PdfDelta_Frac") {
    return Systematic::Bu2Dst0h_D0gamma_PdfDelta_Frac;
  } else if (systematic == "Bu2Dst0h_D0gamma_PdfBu_SigmaRatioKpi") {
    return Systematic::Bu2Dst0h_D0gamma_PdfBu_SigmaRatioKpi;
  } else if (systematic == "Bu2Dst0h_D0gamma_PdfBu_Tails") {
    return Systematic::Bu2Dst0h_D0gamma_PdfBu_Tails;
  } else if (systematic == "Bu2Dst0h_D0gamma_PdfBu_Frac") {
    return Systematic::Bu2Dst0h_D0gamma_PdfBu_Frac;
  } else if (systematic == "Bu2Dst0h_D0pi0_WN_PdfDelta") {
    return Systematic::Bu2Dst0h_D0pi0_WN_PdfDelta;
  } else if (systematic == "Bu2Dst0h_D0pi0_WN_PdfBu") {
    return Systematic::Bu2Dst0h_D0pi0_WN_PdfBu;
  } else if (systematic == "Bu2Dst0h_D0pi0_WN_PdfBuPartial") {
    return Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial;
  } else if (systematic == "Bu2Dst0h_D0gamma_WN_PdfDelta") {
    return Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta;
  } else if (systematic == "Bu2Dst0h_D0gamma_WN_PdfBu") {
    return Systematic::Bu2Dst0h_D0gamma_WN_PdfBu;
  } else if (systematic == "Bu2Dst0h_D0gamma_WN_PdfBuPartial") {
    return Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial;
  } else if (systematic == "Bd2Dsth_PdfDelta") {
    return Systematic::Bd2Dsth_PdfDelta;
  } else if (systematic == "Bd2Dsth_PdfBu") {
    return Systematic::Bd2Dsth_PdfBu;
  } else if (systematic == "Bd2Dsth_PdfBuPartial") {
    return Systematic::Bd2Dsth_PdfBuPartial;
  } else if (systematic == "Bu2D0hst_PdfDelta") {
    return Systematic::Bu2D0hst_PdfDelta;
  } else if (systematic == "Bu2D0hst_PdfDelta_D02pik") {
    return Systematic::Bu2D0hst_PdfDelta_D02pik;
  } else if (systematic == "Bu2D0hst_PdfBu") {
    return Systematic::Bu2D0hst_PdfBu;
  } else if (systematic == "Bu2D0hst_PdfBu_D02pik") {
    return Systematic::Bu2D0hst_PdfBu_D02pik;
  } else if (systematic == "Bu2D0hst_PdfBuPartial") {
    return Systematic::Bu2D0hst_PdfBuPartial;
  } else if (systematic == "Bu2Dst0hst_D0gamma_PdfBu") {
    return Systematic::Bu2Dst0hst_D0gamma_PdfBu;
  } else if (systematic == "Bu2Dst0hst_D0gamma_PdfDelta") {
    return Systematic::Bu2Dst0hst_D0gamma_PdfDelta;
  } else if (systematic == "Bu2Dst0hst_D0gamma_PdfBuPartial") {
    return Systematic::Bu2Dst0hst_D0gamma_PdfBuPartial;
  } else if (systematic == "Bu2Dst0hst_D0pi0_PdfDelta") {
    return Systematic::Bu2Dst0hst_D0pi0_PdfDelta;
  } else if (systematic == "Bu2Dst0hst_D0pi0_PdfBu") {
    return Systematic::Bu2Dst0hst_D0pi0_PdfBu;
  } else if (systematic == "Bu2Dst0hst_D0pi0_PdfBuPartial") {
    return Systematic::Bu2Dst0hst_D0pi0_PdfBuPartial;
  } else if (systematic == "Bu2Dst0hst_PdfBu_D02pik") {
    return Systematic::Bu2Dst0hst_PdfBu_D02pik;
  } else if (systematic == "Bu2Dst0hst_Frac") {
    return Systematic::Bu2Dst0hst_Frac;
  } else if (systematic == "Lb2Omegach_Lcpi0_PdfDelta") {
    return Systematic::Lb2Omegach_Lcpi0_PdfDelta;
  } else if (systematic == "Lb2Omegach_Lcpi0_PdfBu") {
    return Systematic::Lb2Omegach_Lcpi0_PdfBu;
  } else if (systematic == "Lb2Omegach_Lcpi0_PdfBuPartial") {
    return Systematic::Lb2Omegach_Lcpi0_PdfBuPartial;
  } else if (systematic == "Bs2Dst0Kst0_Frac") {
    return Systematic::Bs2Dst0Kst0_Frac;
  } else if (systematic == "Bs2Dst0Kst0_PdfDelta") {
    return Systematic::Bs2Dst0Kst0_PdfDelta;
  } else if (systematic == "Bs2Dst0Kst0") {
    return Systematic::Bs2Dst0Kst0;
  } else if (systematic == "Bs2Dst0Kst0_WN") {
    return Systematic::Bs2Dst0Kst0_WN;
  } else if (systematic == "Bs2D0Kst0_PdfDelta") {
    return Systematic::Bs2D0Kst0_PdfDelta;
  } else if (systematic == "Bs2D0Kst0_PdfBu") {
    return Systematic::Bs2D0Kst0_PdfBu;
  } else if (systematic == "Bs2D0Kst0_PdfBuPartial") {
    return Systematic::Bs2D0Kst0_PdfBuPartial;
  } else if (systematic == "Bu2Dst0K_D0pi0_asPi_Pdfs") {
    return Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs;
  } else if (systematic == "Bu2Dst0pi_D0pi0_asK_Pdfs") {
    return Systematic::Bu2Dst0pi_D0pi0_asK_Pdfs;
  } else if (systematic == "Bu2Dst0K_D0gamma_asPi_Pdfs") {
    return Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs;
  } else if (systematic == "Bu2Dst0pi_D0gamma_asK_Pdfs") {
    return Systematic::Bu2Dst0pi_D0gamma_asK_Pdfs;
  } else if (systematic == "Bu2Dst0h_WN_misId_Pdfs") {
    return Systematic::Bu2Dst0h_WN_misId_Pdfs;
  } else if (systematic == "Bkg_misId_Pdfs") {
    return Systematic::Bkg_misId_Pdfs;
  } else if (systematic == "D02pik_Pdfs") {
    return Systematic::D02pik_Pdfs;
  } else if (systematic == "Combinatorial") {
    return Systematic::Combinatorial;
  } else if (systematic == "boxEffs_Bu2Dst0h_D0pi0") {
    return Systematic::boxEffs_Bu2Dst0h_D0pi0;
  } else if (systematic == "boxEffs_Bu2Dst0h_D0gamma") {
    return Systematic::boxEffs_Bu2Dst0h_D0gamma;
  } else if (systematic == "boxEffs_Bkg") {
    return Systematic::boxEffs_Bkg;
  } else if (systematic == "boxEffs_WN") {
    return Systematic::boxEffs_WN;
  } else if (systematic == "boxEffs_Bd2Dsth") {
    return Systematic::boxEffs_Bd2Dsth;
  } else if (systematic == "boxEffs_Bu2D0hst") {
    return Systematic::boxEffs_Bu2D0hst;
  } else if (systematic == "boxEffs_Bu2Dst0hst") {
    return Systematic::boxEffs_Bu2Dst0hst;
  } else if (systematic == "boxEffs_D02pik") {
    return Systematic::boxEffs_D02pik;
  } else if (systematic == "boxEffs_Bu2Dst0h_D0pi0_misId") {
    return Systematic::boxEffs_Bu2Dst0h_D0pi0_misId;
  } else if (systematic == "boxEffs_Bu2Dst0h_D0gamma_misId") {
    return Systematic::boxEffs_Bu2Dst0h_D0gamma_misId;
  } else if (systematic == "boxEffs_Bkg_misId") {
    return Systematic::boxEffs_Bkg_misId;
  } else if (systematic == "mcEffs_Bu2Dst0h_D0pi0") {
    return Systematic::mcEffs_Bu2Dst0h_D0pi0;
  } else if (systematic == "mcEffs_Bu2Dst0h_D0gamma") {
    return Systematic::mcEffs_Bu2Dst0h_D0gamma;
  } else if (systematic == "mcEffs_Bkg") {
    return Systematic::mcEffs_Bkg;
  } else if (systematic == "mcEffs_Bu2Dst0h_D0pi0_misId") {
    return Systematic::mcEffs_Bu2Dst0h_D0pi0_misId;
  } else if (systematic == "mcEffs_Bu2Dst0h_D0gamma_misId") {
    return Systematic::mcEffs_Bu2Dst0h_D0gamma_misId;
  } else if (systematic == "mcEffs_Bkg_misId") {
    return Systematic::mcEffs_Bkg_misId;
  } else if (systematic == "Bu2D0hst_BkgFrac") {
    return Systematic::Bu2D0hst_BkgFrac;
  } else if (systematic == "Bu2Dst0hst_BkgFrac") {
    return Systematic::Bu2Dst0hst_BkgFrac;
  } else if (systematic == "Bs2D0Kst0_BkgFrac") {
    return Systematic::Bs2D0Kst0_BkgFrac;
  } else if (systematic == "pidEffPi") {
    return Systematic::pidEffPi;
  } else if (systematic == "pidEffK") {
    return Systematic::pidEffK;
  } else if (systematic == "crossFeedRate") {
    return Systematic::crossFeedRate;
  } else if (systematic == "A_pi_Kpi_Bu2Dst0h_D0pi0") {
    return Systematic::A_pi_Kpi_Bu2Dst0h_D0pi0;
  } else if (systematic == "A_pi_Kpi_Bu2Dst0h_D0gamma") {
    return Systematic::A_pi_Kpi_Bu2Dst0h_D0gamma;
  } else if (systematic == "A_pi_Kpi_Bu2Dst0h_WN") {
    return Systematic::A_pi_Kpi_Bu2Dst0h_WN;
  } else if (systematic == "A_pi_Kpi_Bu2D0hst") {
    return Systematic::A_pi_Kpi_Bu2D0hst;
  } else if (systematic == "A_pi_Kpi_Bu2Dst0hst") {
    return Systematic::A_pi_Kpi_Bu2Dst0hst;
  } else if (systematic == "A_K_Kpi_Bu2Dst0h_WN") {
    return Systematic::A_K_Kpi_Bu2Dst0h_WN;
  } else if (systematic == "A_K_Kpi_Bu2D0hst") {
    return Systematic::A_K_Kpi_Bu2D0hst;
  } else if (systematic == "A_K_Kpi_Bu2Dst0hst") {
    return Systematic::A_K_Kpi_Bu2Dst0hst;
  } else if (systematic == "A_K_piK_Bu2D0hst") {
    return Systematic::A_K_piK_Bu2D0hst;
  } else if (systematic == "A_Kpi") {
    return Systematic::A_Kpi;
  } else if (systematic == "A_pi") {
    return Systematic::A_pi;
  } else if (systematic == "Delta_A_CP") {
    return Systematic::Delta_A_CP;
  } else if (systematic == "R_CP_Bu2D0hst") {
    return Systematic::R_CP_Bu2D0hst;
  } else if (systematic == "R_ADS_Bu2D0hst") {
    return Systematic::R_ADS_Bu2D0hst;
  } else if (systematic == "A_CP_pi_Bu2D0hst") {
    return Systematic::A_CP_pi_Bu2D0hst;
  } else if (systematic == "A_CP_K_Bu2D0hst") {
    return Systematic::A_CP_K_Bu2D0hst;
  } else if (systematic == "A_CP_K_Lb2Omegach_Lcpi0") {
    return Systematic::A_CP_K_Lb2Omegach_Lcpi0;
  } else if (systematic == "R_Dst0KDst0pi_Bd2Dsth") {
    return Systematic::R_Dst0KDst0pi_Bd2Dsth;
  } else if (systematic == "R_Dst0KDst0pi_Lb2Omegach_Lcpi0") {
    return Systematic::R_Dst0KDst0pi_Lb2Omegach_Lcpi0;
  } else if (systematic == "kBF_Bu2Dst0pi") {
    return Systematic::kBF_Bu2Dst0pi;
  } else if (systematic == "kBF_Bu2Dst0K") {
    return Systematic::kBF_Bu2Dst0K;
  } else if (systematic == "kBF_Dst02D0pi0") {
    return Systematic::kBF_Dst02D0pi0;
  } else if (systematic == "kBF_Dst02D0gamma") {
    return Systematic::kBF_Dst02D0gamma;
  } else if (systematic == "kBF_D02kpi") {
    return Systematic::kBF_D02kpi;
  } else if (systematic == "kBF_D02kk") {
    return Systematic::kBF_D02kk;
  } else if (systematic == "kBF_D02pipi") {
    return Systematic::kBF_D02pipi;
  } else if (systematic == "kBF_D02pik") {
    return Systematic::kBF_D02pik;
  } else if (systematic == "kBF_Bu2Dst0rho") {
    return Systematic::kBF_Bu2Dst0rho;
  } else if (systematic == "kBF_Bu2Dst0Kst") {
    return Systematic::kBF_Bu2Dst0Kst;
  } else if (systematic == "R_CP_Bu2Dst0h_D0gamma") {
    return Systematic::R_CP_Bu2Dst0h_D0gamma;
  } else if (systematic == "A_CP_pi_Bu2Dst0h_D0gamma") {
    return Systematic::A_CP_pi_Bu2Dst0h_D0gamma;
  } else if (systematic == "A_CP_K_Bu2Dst0h_D0gamma") {
    return Systematic::A_CP_K_Bu2Dst0h_D0gamma;
  } else if (systematic == "R_piK_Bu2Dst0h_D0gamma") {
    return Systematic::R_piK_Bu2Dst0h_D0gamma;
  } else if (systematic == "A_K_Kpi_Bu2Dst0h_D0gamma") {
    return Systematic::A_K_Kpi_Bu2Dst0h_D0gamma;
  } else if (systematic == "R_ADS_Bu2Dst0hst") {
    return Systematic::R_ADS_Bu2Dst0hst;
  } else if (systematic == "A_K_piK_Bu2Dst0hst") {
    return Systematic::A_K_piK_Bu2Dst0hst;
  }
  throw std::invalid_argument("Invalid systematic passed to StringToEnum");
}

std::string EnumToString(Group group) {
  if (group == Group::Pdfs) {
    return "Pdfs";
  } else if (group == Group::Effs) {
    return "Effs";
  } else if (group == Group::Rates) {
    return "Rates";
  } else if (group == Group::Asyms) {
    return "Asyms";
  } else if (group == Group::CPPars) {
    return "CPPars";
  }
  throw std::invalid_argument(
      "Group must take string: Pdfs, Effs, Rates, Asyms or CPPars");
}

std::string EnumToString(Systematic systematic) {
  switch (systematic) {
    case Systematic::Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi:
      return "Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi";
    case Systematic::Bu2Dst0h_D0pi0_PdfDelta_Tails:
      return "Bu2Dst0h_D0pi0_PdfDelta_Tails";
    case Systematic::Bu2Dst0h_D0pi0_PdfDelta_Frac:
      return "Bu2Dst0h_D0pi0_PdfDelta_Frac";
    case Systematic::Bu2Dst0h_D0pi0_PdfBu_SigmaRatioKpi:
      return "Bu2Dst0h_D0pi0_PdfBu_SigmaRatioKpi";
    case Systematic::Bu2Dst0h_D0pi0_PdfBu_Tails:
      return "Bu2Dst0h_D0pi0_PdfBu_Tails";
    case Systematic::Bu2Dst0h_D0pi0_PdfBu_Frac:
      return "Bu2Dst0h_D0pi0_PdfBu_Frac";
    case Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_MeanOffset:
      return "Bu2Dst0h_D0pi0_PdfBuPartial_MeanOffset";
    case Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatioKpi:
      return "Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatioKpi";
    case Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatio:
      return "Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatio";
    case Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Tails:
      return "Bu2Dst0h_D0pi0_PdfBuPartial_Tails";
    case Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Frac:
      return "Bu2Dst0h_D0pi0_PdfBuPartial_Frac";
    case Systematic::Bu2Dst0h_D0pi0_PdfBuPartial_Sigma1:
      return "Bu2Dst0h_D0pi0_PdfBuPartial_Sigma1";
    case Systematic::Bu2Dst0h_D0pi0_PdfBu:
      return "Bu2Dst0h_D0pi0_PdfBu";
    case Systematic::Bu2Dst0h_D0gamma_PdfBuPartial:
      return "Bu2Dst0h_D0gamma_PdfBuPartial";
    case Systematic::Bu2Dst0h_D0gamma_PdfDelta_SigmaRatioKpi:
      return "Bu2Dst0h_D0gamma_PdfDelta_SigmaRatioKpi";
    case Systematic::Bu2Dst0h_D0gamma_PdfDelta_Tails:
      return "Bu2Dst0h_D0gamma_PdfDelta_Tails";
    case Systematic::Bu2Dst0h_D0gamma_PdfDelta_Frac:
      return "Bu2Dst0h_D0gamma_PdfDelta_Frac";
    case Systematic::Bu2Dst0h_D0gamma_PdfBu_SigmaRatioKpi:
      return "Bu2Dst0h_D0gamma_PdfBu_SigmaRatioKpi";
    case Systematic::Bu2Dst0h_D0gamma_PdfBu_Tails:
      return "Bu2Dst0h_D0gamma_PdfBu_Tails";
    case Systematic::Bu2Dst0h_D0gamma_PdfBu_Frac:
      return "Bu2Dst0h_D0gamma_PdfBu_Frac";
    case Systematic::Bu2Dst0h_D0pi0_WN_PdfDelta:
      return "Bu2Dst0h_D0pi0_WN_PdfDelta";
    case Systematic::Bu2Dst0h_D0pi0_WN_PdfBu:
      return "Bu2Dst0h_D0pi0_WN_PdfBu";
    case Systematic::Bu2Dst0h_D0pi0_WN_PdfBuPartial:
      return "Bu2Dst0h_D0pi0_WN_PdfBuPartial";
    case Systematic::Bu2Dst0h_D0gamma_WN_PdfDelta:
      return "Bu2Dst0h_D0gamma_WN_PdfDelta";
    case Systematic::Bu2Dst0h_D0gamma_WN_PdfBu:
      return "Bu2Dst0h_D0gamma_WN_PdfBu";
    case Systematic::Bu2Dst0h_D0gamma_WN_PdfBuPartial:
      return "Bu2Dst0h_D0gamma_WN_PdfBuPartial";
    // case Systematic::Bu2Dst0h_WN_Frac:
    //   return "Bu2Dst0h_WN_Frac";
    case Systematic::Bd2Dsth_PdfDelta:
      return "Bd2Dsth_PdfDelta";
    case Systematic::Bd2Dsth_PdfBu:
      return "Bd2Dsth_PdfBu";
    case Systematic::Bd2Dsth_PdfBuPartial:
      return "Bd2Dsth_PdfBuPartial";
    case Systematic::Bu2D0hst_PdfDelta:
      return "Bu2D0hst_PdfDelta";
    case Systematic::Bu2D0hst_PdfDelta_D02pik:
      return "Bu2D0hst_PdfDelta_D02pik";
    case Systematic::Bu2D0hst_PdfBu:
      return "Bu2D0hst_PdfBu";
    case Systematic::Bu2D0hst_PdfBu_D02pik:
      return "Bu2D0hst_PdfBu_D02pik";
    case Systematic::Bu2D0hst_PdfBuPartial:
      return "Bu2D0hst_PdfBuPartial";
    case Systematic::Bu2Dst0hst_D0gamma_PdfBu:
      return "Bu2Dst0hst_D0gamma_PdfBu";
    case Systematic::Bu2Dst0hst_D0gamma_PdfDelta:
      return "Bu2Dst0hst_D0gamma_PdfDelta";
    case Systematic::Bu2Dst0hst_D0gamma_PdfBuPartial:
      return "Bu2Dst0hst_D0gamma_PdfBuPartial";
    case Systematic::Bu2Dst0hst_D0pi0_PdfDelta:
      return "Bu2Dst0hst_D0pi0_PdfDelta";
    case Systematic::Bu2Dst0hst_D0pi0_PdfBu:
      return "Bu2Dst0hst_D0pi0_PdfBu";
    case Systematic::Bu2Dst0hst_D0pi0_PdfBuPartial:
      return "Bu2Dst0hst_D0pi0_PdfBuPartial";
    case Systematic::Bu2Dst0hst_PdfBu_D02pik:
      return "Bu2Dst0hst_PdfBu_D02pik";
    case Systematic::Bu2Dst0hst_Frac:
      return "Bu2Dst0hst_Frac";
    case Systematic::Lb2Omegach_Lcpi0_PdfDelta:
      return "Lb2Omegach_Lcpi0_PdfDelta";
    case Systematic::Lb2Omegach_Lcpi0_PdfBu:
      return "Lb2Omegach_Lcpi0_PdfBu";
    case Systematic::Lb2Omegach_Lcpi0_PdfBuPartial:
      return "Lb2Omegach_Lcpi0_PdfBuPartial";
    case Systematic::Bs2Dst0Kst0_Frac:
      return "Bs2Dst0Kst0_Frac";
    case Systematic::Bs2Dst0Kst0_PdfDelta:
      return "Bs2Dst0Kst0_PdfDelta";
    case Systematic::Bs2Dst0Kst0:
      return "Bs2Dst0Kst0";
    case Systematic::Bs2Dst0Kst0_WN:
      return "Bs2Dst0Kst0_WN";
    case Systematic::Bs2D0Kst0_PdfDelta:
      return "Bs2D0Kst0_PdfDelta";
    case Systematic::Bs2D0Kst0_PdfBu:
      return "Bs2D0Kst0_PdfBu";
    case Systematic::Bs2D0Kst0_PdfBuPartial:
      return "Bs2D0Kst0_PdfBuPartial";
    case Systematic::Bu2Dst0K_D0pi0_asPi_Pdfs:
      return "Bu2Dst0K_D0pi0_asPi_Pdfs";
    case Systematic::Bu2Dst0pi_D0pi0_asK_Pdfs:
      return "Bu2Dst0pi_D0pi0_asK_Pdfs";
    case Systematic::Bu2Dst0K_D0gamma_asPi_Pdfs:
      return "Bu2Dst0K_D0gamma_asPi_Pdfs";
    case Systematic::Bu2Dst0pi_D0gamma_asK_Pdfs:
      return "Bu2Dst0pi_D0gamma_asK_Pdfs";
    case Systematic::Bu2Dst0h_WN_misId_Pdfs:
      return "Bu2Dst0h_WN_misId_Pdfs";
    case Systematic::Bkg_misId_Pdfs:
      return "Bkg_misId_Pdfs";
    case Systematic::D02pik_Pdfs:
      return "D02pik_Pdfs";
    case Systematic::Combinatorial:
      return "Combinatorial";
    case Systematic::boxEffs_Bu2Dst0h_D0pi0:
      return "boxEffs_Bu2Dst0h_D0pi0";
    case Systematic::boxEffs_Bu2Dst0h_D0gamma:
      return "boxEffs_Bu2Dst0h_D0gamma";
    case Systematic::boxEffs_Bkg:
      return "boxEffs_Bkg";
    case Systematic::boxEffs_WN:
      return "boxEffs_WN";
    case Systematic::boxEffs_Bd2Dsth:
      return "boxEffs_Bd2Dsth";
    case Systematic::boxEffs_Bu2D0hst:
      return "boxEffs_Bu2D0hst";
    case Systematic::boxEffs_Bu2Dst0hst:
      return "boxEffs_Bu2Dst0hst";
    case Systematic::boxEffs_D02pik:
      return "boxEffs_D02pik";
    case Systematic::boxEffs_Bu2Dst0h_D0pi0_misId:
      return "boxEffs_Bu2Dst0h_D0pi0_misId";
    case Systematic::boxEffs_Bu2Dst0h_D0gamma_misId:
      return "boxEffs_Bu2Dst0h_D0gamma_misId";
    case Systematic::boxEffs_Bkg_misId:
      return "boxEffs_Bkg_misId";
    case Systematic::mcEffs_Bu2Dst0h_D0pi0:
      return "mcEffs_Bu2Dst0h_D0pi0";
    case Systematic::mcEffs_Bu2Dst0h_D0gamma:
      return "mcEffs_Bu2Dst0h_D0gamma";
    case Systematic::mcEffs_Bkg:
      return "mcEffs_Bkg";
    case Systematic::mcEffs_Bu2Dst0h_D0pi0_misId:
      return "mcEffs_Bu2Dst0h_D0pi0_misId";
    case Systematic::mcEffs_Bu2Dst0h_D0gamma_misId:
      return "mcEffs_Bu2Dst0h_D0gamma_misId";
    case Systematic::mcEffs_Bkg_misId:
      return "mcEffs_Bkg_misId";
    case Systematic::Bu2D0hst_BkgFrac:
      return "Bu2D0hst_BkgFrac";
    case Systematic::Bu2Dst0hst_BkgFrac:
      return "Bu2Dst0hst_BkgFrac";
    case Systematic::Bs2D0Kst0_BkgFrac:
      return "Bs2D0Kst0_BkgFrac";
    case Systematic::pidEffPi:
      return "pidEffPi";
    case Systematic::pidEffK:
      return "pidEffK";
    case Systematic::crossFeedRate:
      return "crossFeedRate";
    case Systematic::A_pi_Kpi_Bu2Dst0h_D0pi0:
      return "A_pi_Kpi_Bu2Dst0h_D0pi0";
    case Systematic::A_pi_Kpi_Bu2Dst0h_D0gamma:
      return "A_pi_Kpi_Bu2Dst0h_D0gamma";
    case Systematic::A_pi_Kpi_Bu2Dst0h_WN:
      return "A_pi_Kpi_Bu2Dst0h_WN";
    case Systematic::A_pi_Kpi_Bu2D0hst:
      return "A_pi_Kpi_Bu2D0hst";
    case Systematic::A_pi_Kpi_Bu2Dst0hst:
      return "A_pi_Kpi_Bu2Dst0hst";
    case Systematic::A_K_Kpi_Bu2Dst0h_WN:
      return "A_K_Kpi_Bu2Dst0h_WN";
    case Systematic::A_K_Kpi_Bu2D0hst:
      return "A_K_Kpi_Bu2D0hst";
    case Systematic::A_K_Kpi_Bu2Dst0hst:
      return "A_K_Kpi_Bu2Dst0hst";
    case Systematic::A_K_piK_Bu2D0hst:
      return "A_K_Kpi_Bu2D0hst";
    case Systematic::A_Kpi:
      return "A_Kpi";
    case Systematic::A_pi:
      return "A_pi";
    case Systematic::Delta_A_CP:
      return "Delta_A_CP";
    case Systematic::R_CP_Bu2D0hst:
      return "R_CP_Bu2D0hst";
    case Systematic::R_ADS_Bu2D0hst:
      return "R_ADS_Bu2D0hst";
    case Systematic::A_CP_pi_Bu2D0hst:
      return "A_CP_pi_Bu2D0hst";
    case Systematic::A_CP_K_Bu2D0hst:
      return "A_CP_K_Bu2D0hst";
    case Systematic::A_CP_K_Lb2Omegach_Lcpi0:
      return "A_CP_K_Lb2Omegach_Lcpi0";
    case Systematic::R_Dst0KDst0pi_Bd2Dsth:
      return "R_Dst0KDst0pi_Bd2Dsth";
    case Systematic::R_Dst0KDst0pi_Lb2Omegach_Lcpi0:
      return "R_Dst0KDst0pi_Lb2Omegach_Lcpi0";
    case Systematic::kBF_Bu2Dst0pi:
      return "kBF_Bu2Dst0pi";
    case Systematic::kBF_Bu2Dst0K:
      return "kBF_Bu2Dst0K";
    case Systematic::kBF_Dst02D0pi0:
      return "kBF_Dst02D0pi0";
    case Systematic::kBF_Dst02D0gamma:
      return "kBF_Dst02D0gamma";
    case Systematic::kBF_D02kpi:
      return "kBF_D02kpi";
    case Systematic::kBF_D02kk:
      return "kBF_D02kk";
    case Systematic::kBF_D02pipi:
      return "kBF_D02pipi";
    case Systematic::kBF_D02pik:
      return "kBF_D02pik";
    case Systematic::kBF_Bu2Dst0rho:
      return "kBF_Bu2Dst0rho";
    case Systematic::kBF_Bu2Dst0Kst:
      return "kBF_Bu2Dst0Kst";
    case Systematic::R_CP_Bu2Dst0h_D0gamma:
      return "R_CP_Bu2Dst0h_D0gamma";
    case Systematic::A_CP_pi_Bu2Dst0h_D0gamma:
      return "A_CP_pi_Bu2Dst0h_D0gamma";
    case Systematic::A_CP_K_Bu2Dst0h_D0gamma:
      return "A_CP_K_Bu2Dst0h_D0gamma";
    case Systematic::R_piK_Bu2Dst0h_D0gamma:
      return "R_piK_Bu2Dst0h_D0gamma";
    case Systematic::A_K_Kpi_Bu2Dst0h_D0gamma:
      return "A_K_Kpi_Bu2Dst0h_D0gamma";
    case Systematic::R_ADS_Bu2Dst0hst:
      return "R_ADS_Bu2Dst0hst";
    case Systematic::A_K_piK_Bu2Dst0hst:
      return "A_K_piK_Bu2Dst0hst";
  }
}

template <>
Polarity StringToEnum<Polarity>(std::string const &polarity) {
  if (polarity == "up") {
    return Polarity::up;
  } else if (polarity == "down") {
    return Polarity::down;
    // } else if (polarity == "both") {
    //   return Polarity::both;
  }
  throw std::invalid_argument("Polarity must take a value in [up/down]");
}

std::string EnumToString(Polarity polarity) {
  switch (polarity) {
    case Polarity::up:
      return "up";
    case Polarity::down:
      return "down";
      // case Polarity::both:
      // default:
      //   return "both";
  }
}

template <>
Daughters StringToEnum<Daughters>(std::string const &daughters) {
  if (daughters == "kpi") {
    return Daughters::kpi;
  } else if (daughters == "kk") {
    return Daughters::kk;
  } else if (daughters == "pipi") {
    return Daughters::pipi;
  } else if (daughters == "pik") {
    return Daughters::pik;
  }
  throw std::invalid_argument(
      "Daughters must take a value in [kpi/kk/pipi/pik]");
}

std::string EnumToString(Daughters daughters) {
  switch (daughters) {
    case Daughters::kpi:
      return "kpi";
    case Daughters::kk:
      return "kk";
    case Daughters::pipi:
      return "pipi";
    case Daughters::pik:
      // default:
      return "pik";
  }
}

template <>
Bachelor StringToEnum<Bachelor>(std::string const &bachelor) {
  if (bachelor == "pi") {
    return Bachelor::pi;
  } else if (bachelor == "k") {
    return Bachelor::k;
  }
  throw std::invalid_argument("Bachelor must take a value in [pi/k]");
}

std::string EnumToString(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "pi";
    case Bachelor::k:
      // default:
      return "k";
  }
}

template <>
Year StringToEnum<Year>(std::string const &year) {
  if (year == "2011") {
    return Year::y2011;
  } else if (year == "2012") {
    return Year::y2012;
  } else if (year == "2015") {
    return Year::y2015;
  } else if (year == "2016") {
    return Year::y2016;
  } else if (year == "2017") {
    return Year::y2017;
  } else if (year == "2018") {
    return Year::y2018;
  }
  throw std::invalid_argument(
      "Year must take a value in [2011/2012/2015/2016/2017/2018]");
}

std::string EnumToString(Year year) {
  switch (year) {
    case Year::y2011:
      return "2011";
    case Year::y2012:
      return "2012";
    case Year::y2015:
      return "2015";
    case Year::y2016:
      return "2016";
    case Year::y2017:
      return "2017";
    case Year::y2018:
      return "2018";
  }
}

template <>
Neutral StringToEnum<Neutral>(std::string const &neutral) {
  if (neutral == "pi0") {
    return Neutral::pi0;
  } else if (neutral == "gamma") {
    return Neutral::gamma;
  }
  throw std::invalid_argument("Neutral must take a value in [pi0/gamma]");
}

std::string EnumToString(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "pi0";
    case Neutral::gamma:
      // default:
      return "gamma";
  }
}

template <>
Charge StringToEnum<Charge>(std::string const &charge) {
  if (charge == "plus") {
    return Charge::plus;
  } else if (charge == "minus") {
    return Charge::minus;
  } else if (charge == "total") {
    return Charge::total;
  } else {
    throw std::invalid_argument("Charge must take a value in [plus/minus]");
  }
}

std::string EnumToString(Charge charge) {
  switch (charge) {
    case Charge::plus:
      return "plus";
    case Charge::minus:
      return "minus";
    case Charge::total:
      return "total";
  }
}

std::string EnumToString(Mass mass) {
  switch (mass) {
    case Mass::buDelta:
      return "buDelta";
    case Mass::buDeltaPartial:
      return "buDeltaPartial";
    case Mass::delta:
      return "delta";
  }
}

std::string EnumToString(Mode mode) {
  switch (mode) {
    case Mode::Bs2D0Kst0:
      return "Bs2D0Kst0";
      break;
    case Mode::Bs2Dst0Kst0:
      return "Bs2Dst0Kst0";
      break;
    case Mode::Bs2Dst0Kst0_D0gamma:
      return "Bs2Dst0Kst0_D0gamma";
      break;
    case Mode::Bs2Dst0Kst0_D0pi0:
      return "Bs2Dst0Kst0_D0pi0";
      break;
    case Mode::Bs2Dst0Kst0_D0gamma_WN:
      return "Bs2Dst0Kst0_D0gamma_WN";
      break;
    case Mode::Bs2Dst0Kst0_D0pi0_WN:
      return "Bs2Dst0Kst0_D0pi0_WN";
      break;
    case Mode::Bs2Dst0Kpi:
      return "Bs2Dst0Kpi";
      break;
    case Mode::Bs2Dst0Kpi_D0gamma:
      return "Bs2Dst0Kpi_D0gamma";
      break;
    case Mode::Bs2Dst0Kpi_D0pi0:
      return "Bs2Dst0Kpi_D0pi0";
      break;
    case Mode::Bs2Dst0Kpi_D0gamma_WN:
      return "Bs2Dst0Kpi_D0gamma_WN";
      break;
    case Mode::Bs2Dst0Kpi_D0pi0_WN:
      return "Bs2Dst0Kpi_D0pi0_WN";
      break;
    case Mode::Bd2Dstpi:
      return "Bd2Dstpi";
      break;
    case Mode::Bd2DstK:
      return "Bd2DstK";
      break;
    case Mode::Bu2D0pi:
      return "Bu2D0pi";
      break;
    case Mode::Bu2D0K:
      return "Bu2D0K";
      break;
    case Mode::Bu2D0rho:
      return "Bu2D0rho";
      break;
    case Mode::Bu2D0Kst:
      return "Bu2D0Kst";
      break;
    case Mode::Bu2Dst0rho_D0gamma:
      return "Bu2Dst0rho_D0gamma";
      break;
    case Mode::Bu2Dst0rho_D0pi0:
      return "Bu2Dst0rho_D0pi0";
      break;
    case Mode::Bu2Dst0rho:
      return "Bu2Dst0rho";
      break;
    case Mode::Bu2Dst0Kst_D0gamma:
      return "Bu2Dst0Kst_D0gamma";
      break;
    case Mode::Bu2Dst0Kst_D0pi0:
      return "Bu2Dst0Kst_D0pi0";
      break;
    case Mode::Bu2Dst0pi_D0gamma:
      return "Bu2Dst0pi_D0gamma";
      break;
    case Mode::Bu2Dst0Kst:
      return "Bu2Dst0Kst";
      break;
    case Mode::Bu2Dst0K_D0gamma:
      return "Bu2Dst0K_D0gamma";
      break;
    case Mode::Bu2Dst0pi_D0gamma_D02pik:
      return "Bu2Dst0pi_D0gamma_D02pik";
      break;
    case Mode::Bu2Dst0K_D0gamma_D02pik:
      return "Bu2Dst0K_D0gamma_D02pik";
      break;
    case Mode::Bu2Dst0pi_D0gamma_WN_D02pik:
      return "Bu2Dst0pi_D0gamma_WN_D02pik";
      break;
    case Mode::Bu2Dst0K_D0gamma_WN_D02pik:
      return "Bu2Dst0K_D0gamma_WN_D02pik";
      break;
    case Mode::Bu2Dst0pi_D0gamma_WN:
      return "Bu2Dst0pi_D0gamma_WN";
      break;
    case Mode::Bu2Dst0K_D0gamma_WN:
      return "Bu2Dst0K_D0gamma_WN";
      break;
    case Mode::Bu2Dst0pi_D0pi0:
      return "Bu2Dst0pi_D0pi0";
      break;
    case Mode::Bu2Dst0K_D0pi0:
      return "Bu2Dst0K_D0pi0";
      break;
    case Mode::Bu2Dst0pi_D0pi0_D02pik:
      return "Bu2Dst0pi_D0pi0_D02pik";
      break;
    case Mode::Bu2Dst0K_D0pi0_D02pik:
      return "Bu2Dst0K_D0pi0_D02pik";
      break;
    case Mode::Bu2Dst0pi_D0pi0_WN_D02pik:
      return "Bu2Dst0pi_D0pi0_WN_D02pik";
      break;
    case Mode::Bu2Dst0K_D0pi0_WN_D02pik:
      return "Bu2Dst0K_D0pi0_WN_D02pik";
      break;
    case Mode::Bu2Dst0pi_D0pi0_WN:
      return "Bu2Dst0pi_D0pi0_WN";
      break;
    case Mode::Bu2Dst0K_D0pi0_WN:
      return "Bu2Dst0K_D0pi0_WN";
      break;
    case Mode::Lb2Omegacpi_Lcpi0:
      return "Lb2Omegacpi_Lcpi0";
      break;
  }
}

std::string ComposeFilename(Year year, Polarity polarity, Bachelor bachelor,
                            Neutral neutral, Daughters daughters,
                            Charge charge) {
  return EnumToString(year) + "_" + EnumToString(polarity) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(neutral) + "_" +
         EnumToString(daughters) + "_" + EnumToString(charge);
}

std::string ComposeFittingName(Mass mass, Neutral neutral, Bachelor bachelor,
                               Daughters daughters, Charge charge) {
  return EnumToString(mass) + "_" + EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(daughters) + "_" +
         EnumToString(charge);
}

std::string ComposeDataLabelName(Neutral neutral, Bachelor bachelor,
                                 Daughters daughters, Charge charge) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
         EnumToString(daughters) + "_" + EnumToString(charge);
}

std::string EnumToLabel(Charge charge) {
  switch (charge) {
    case Charge::minus:
      return "-";
    case Charge::plus:
      return "+";
    case Charge::total:
      return "#pm";
  }
}

std::string EnumToLabel(Daughters daughters, Charge charge) {
  switch (daughters) {
    case Daughters::kpi:
      switch (charge) {
        case Charge::minus:
          return "K^{-}#pi^{+}";
        case Charge::plus:
          return "K^{+}#pi^{-}";
        case Charge::total:
          return "K^{#pm}#pi^{#mp}";
      }
    case Daughters::kk:
      return "K^{+}K^{-}";
    case Daughters::pipi:
      return "#pi^{+}#pi^{-}";
    case Daughters::pik:
      switch (charge) {
        case Charge::minus:
          return "#pi^{-}K^{+}";
        case Charge::plus:
          return "#pi^{+}K^{-}";
        case Charge::total:
          return "#pi^{#pm}K^{#mp}";
      }
  }
}

std::string EnumToLabel(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "#pi";
    case Bachelor::k:
      return "K";
  }
}

std::string EnumToLabel(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "#pi^{0}";
    case Neutral::gamma:
      return "#gamma";
  }
}

void Configuration::DefineCategories() {
  switch (neutral_) {
    case Neutral::pi0:
      if (splitByCharge() == false) {
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kk,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pik,
                                              Charge::total)
                               .c_str());

        if (fit1D() == false) {
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kk,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pik,
                                                Charge::total)
                                 .c_str());
        }

        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kpi, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kpi, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kk, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kk, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pipi,
                                                  Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pipi,
                                                  Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pik, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pik, Charge::total)
                                 .c_str());
      } else {
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kk,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pik,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kk,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pik,
                                              Charge::minus)
                               .c_str());
        if (fit1D() == false) {
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kk,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pik,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kk,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pik,
                                                Charge::minus)
                                 .c_str());
        }

        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kpi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kpi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kk, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kk, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pipi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pipi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pik, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pik, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kpi, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kpi, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kk, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kk, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pipi,
                                                  Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pipi,
                                                  Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pik, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pik, Charge::minus)
                                 .c_str());
      }
      break;
    case Neutral::gamma:
      if (splitByCharge() == false) {
        if (fit1D() == false) {
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kk,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pik,
                                                Charge::total)
                                 .c_str());
        }
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kk,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pik,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kpi, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kpi, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kk, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kk, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pipi, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pipi, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pik, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pik, Charge::total)
                               .c_str());

        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kpi, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kpi, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kk, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kk, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pipi,
                                                  Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pipi,
                                                  Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pik, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pik, Charge::total)
                                 .c_str());
      } else {
        if (fit1D() == false) {
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kk,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pik,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kk,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pik,
                                                Charge::minus)
                                 .c_str());
        }
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kk,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pik,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kk,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pik,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kpi, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kpi, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kk, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kk, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pipi, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pipi, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pik, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pik, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kpi, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kpi, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kk, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kk, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pipi, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pipi, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pik, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pik, Charge::minus)
                               .c_str());

        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kpi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kpi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kk, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kk, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pipi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pipi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pik, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pik, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kpi, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kpi, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kk, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kk, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pipi,
                                                  Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pipi,
                                                  Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pik, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pik, Charge::minus)
                                 .c_str());
      }
      break;
  }
}

std::string ComposeName(int uniqueId, Mass mass, Neutral neutral,
                        Bachelor bachelor, Daughters daughters, Charge charge) {
  return EnumToString(mass) + "_" + EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(daughters) + "_" +
         EnumToString(charge) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral, Bachelor bachelor,
                        Daughters daughters, Charge charge) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
         EnumToString(daughters) + "_" + EnumToString(charge) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral, Bachelor bachelor,
                        Daughters daughters) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
         EnumToString(daughters) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Bachelor bachelor) {
  return EnumToString(bachelor) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral, Bachelor bachelor) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Bachelor bachelor, Charge charge) {
  return EnumToString(bachelor) + "_" + EnumToString(charge) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Daughters daughters) {
  return EnumToString(daughters) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral) {
  return EnumToString(neutral) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral, Charge charge) {
  return EnumToString(neutral) + "_" + EnumToString(charge) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Bachelor bachelor, Daughters daughters) {
  return EnumToString(bachelor) + "_" + EnumToString(daughters) + "_" +
         std::to_string(uniqueId);
}

std::string ReturnLaTeXLabel(std::string paramStr) {
  if (paramStr == "R_Dst0KDst0pi_Bu2Dst0h_kpi") {
    return "#font[12]{R^{K#pi,#pi^{0}/#gamma}_{K/#pi}}";
  } else if (paramStr == "R_Dst0KDst0pi_Bu2Dst0h_D0gamma_kpi") {
    return "#font[12]{R^{K#pi,#gamma}_{K/#pi}}";
  } else if (paramStr == "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_kpi") {
    return "#font[12]{R^{K#pi,#pi^{0}}_{K/#pi}}";
  } else if (paramStr == "N_tot_Bu2Dst0h_D0gamma_gamma_pi_kpi") {
    return "#font[12]{N((D^{*}#rightarrow #left[K#pi#right]_{D}#gamma)#pi^{#pm}})";
  } else if (paramStr == "N_tot_Bu2Dst0h_D0gamma_gamma_pi_kk") {
          return "#font[12]{N((D^{*}#rightarrow #left[KK#right]_{D}#gamma)#pi^{#pm})}";
  } else if (paramStr == "N_tot_Bu2Dst0h_D0gamma_gamma_pi_pipi") {
          return "#font[12]{N((D^{*}#rightarrow #left[#pi#pi#right]_{D}#gamma)#pi^{#pm})}";
  } else if (paramStr == "R_CP_Bu2Dst0h_D0gamma_Blind") {
          return "#font[12]{R^{CP,#gamma}}";
  } else if (paramStr == "R_CP_Bu2Dst0h_D0gamma") {
          return "#font[12]{R^{CP,#gamma}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0gamma_Blind_pi_total") {
          return "#font[12]{R^{#pi K,#gamma}_{#pi^{#pm}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0gamma_Blind_k_total") {
          return "#font[12]{R^{#pi K,#gamma}_{K^{#pm}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0gamma_Blind_pi_plus") {
          return "#font[12]{R^{#pi K,#gamma}_{#pi^{+}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0gamma_Blind_k_plus") {
          return "#font[12]{R^{#pi K,#gamma}_{K^{+}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0gamma_Blind_pi_minus") {
          return "#font[12]{R^{#pi K,#gamma}_{#pi^{-}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0gamma_Blind_k_minus") {
          return "#font[12]{R^{#pi K,#gamma}_{K^{-}}}";
  } else if (paramStr == "A_Bu2Dst0h_D0gamma_gamma_k_kpi") {
          return "#font[12]{A^{K#pi,#gamma}_{K}}";
  } else if (paramStr == "A_Bu2Dst0h_D0pi0_gamma_k_kpi") {
          return "#font[12]{A^{K#pi,#pi^{0}}_{K}}";
  } else if (paramStr == "A_CP_Bu2Dst0h_D0gamma_Blind_pi") {
          return "#font[12]{A^{CP,#gamma}_{#pi}}";
  } else if (paramStr == "A_CP_Bu2Dst0h_D0gamma_Blind_k") {
          return "#font[12]{A^{CP,#gamma}_{K}}";
  } else if (paramStr == "N_tot_Bu2Dst0h_D0pi0_gamma_pi_kpi") {
          return "#font[12]{N((D^{*}#rightarrow #left[K#pi#right]_{D}#pi^{0})#pi^{#pm})}";
  } else if (paramStr == "N_tot_Bu2Dst0h_D0pi0_gamma_pi_kk") {
          return "#font[12]{N((D^{*}#rightarrow #left[KK#right]_{D}#pi^{0})#pi^{#pm})}";
  } else if (paramStr == "N_tot_Bu2Dst0h_D0pi0_gamma_pi_pipi") {
          return "#font[12]{N((D^{*}#rightarrow #left[#pi#pi#right]_{D}#pi^{0})#pi^{#pm})}";
  } else if (paramStr == "N_tot_Bu2Dst0h_D0pi0_pi0_pi_kpi") {
          return "#font[12]{N((D^{*}#rightarrow #left[K#pi#right]_{D}#pi^{0})#pi^{#pm})}";
  } else if (paramStr == "N_tot_Bu2Dst0h_D0pi0_pi0_pi_kk") {
          return "#font[12]{N((D^{*}#rightarrow #left[KK#right]_{D}#pi^{0})#pi^{#pm})}";
  } else if (paramStr == "N_tot_Bu2Dst0h_D0pi0_pi0_pi_pipi") {
          return "#font[12]{N((D^{*}#rightarrow #left[#pi#pi#right]_{D}#pi^{0})#pi^{#pm})}";
  } else if (paramStr == "R_CP_Bu2Dst0h_D0pi0_Blind") {
          return "#font[12]{R^{CP,#pi^{0}}}";
  } else if (paramStr == "R_CP_Bu2Dst0h_D0pi0") {
          return "#font[12]{R^{CP,#pi^{0}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0pi0_Blind_pi_total") {
          return "#font[12]{R^{#pi K,#pi^{0}}_{#pi^{#pm}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0pi0_Blind_k_total") {
          return "#font[12]{R^{#pi K,#pi^{0}}_{K^{#pm}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0pi0_Blind_pi_plus") {
          return "#font[12]{R^{#pi K,#pi^{0}}_{#pi^{+}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0pi0_Blind_k_plus") {
          return "#font[12]{R^{#pi K,#pi^{0}}_{K^{+}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0pi0_Blind_pi_minus") {
          return "#font[12]{R^{#pi K,#pi^{0}}_{#pi^{-}}}";
  } else if (paramStr == "R_piK_Bu2Dst0h_D0pi0_Blind_k_minus") {
          return "#font[12]{R^{#pi K,#pi^{0}}_{K^{-}}}";
  } else if (paramStr == "A_Bu2Dst0h_D0pi0_pi0_k_kpi") {
          return "#font[12]{A^{K#pi,#pi^{0}}_{K}}";
  } else if (paramStr == "A_CP_Bu2Dst0h_D0pi0_Blind_pi") {
          return "#font[12]{A^{CP,#pi^{0}}_{#pi}}";
  } else if (paramStr == "A_CP_Bu2Dst0h_D0pi0_Blind_k") {
          return "#font[12]{A^{CP,#pi^{0}}_{K}}";
  } else {
    std::cout << "No LaTeX label defined for " << paramStr << "\n";
    return paramStr;
  }
}

std::string ReturnLaTeXLabel(Mode mode, Charge charge, bool isTex) {
  std::string oppCharge;
  if (charge == Charge::plus) {
    oppCharge = "-";
  } else if (charge == Charge::minus) {
    oppCharge = "+";
  } else {
    oppCharge = "#mp";
  }
  // std::string daughtersLabel = EnumToLabel(daughters, charge);
  std::string chargeLabel = EnumToLabel(charge);
  if (isTex == true) {
    // std::replace(daughtersLabel.begin(), daughtersLabel.end(), '#', '\\');
    std::replace(chargeLabel.begin(), chargeLabel.end(), '#', '\\');
    std::replace(oppCharge.begin(), oppCharge.end(), '#', '\\');
  }

  if (mode == Mode::Bu2Dst0h_D0gamma) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0} #rightarrow D^{0}#gamma) h^{" + chargeLabel +
             "}}";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\gamma) h^{" +
             chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0h_D0pi0) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0}#rightarrow D^{0}#pi^{0}) h^{" + chargeLabel +
             "}}";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\pi^{0}) h^{" +
             chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0h_D0gamma_WN) {
    if (isTex == false) {
      return "Mis-reconstructed #font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0} #rightarrow D^{0}#gamma) h^{" +
             chargeLabel + "}}";
    } else {
      return "Mis-reconstructed $B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\gamma) h^{" +
             chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0h_D0pi0_WN) {
    if (isTex == false) {
      return "Mis-reconstructed #font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0}#rightarrow D^{0}#pi^{0}) h^{" +
             chargeLabel + "}}";
    } else {
      return "Mis-reconstructed $B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\pi^{0}) h^{" +
             chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0h_WN) {
    if (isTex == false) {
      return "Mis-reconstructed #font[12]{B^{" + chargeLabel + "}#rightarrow D^{*0}h^{" +
             chargeLabel + "}}";
    } else {
      return "Mis-reconstructed $B^{" + chargeLabel + "}\\rightarrow D^{*0}h^{" + chargeLabel +
             "}$";
    }
  } else if (mode == Mode::Bu2D0hst) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel + "}#rightarrow D h^{" +
             chargeLabel + "}#pi}";
    } else {
      return "$B^{" + chargeLabel + "} \\rightarrow D h^{" + chargeLabel +
             "}\\pi$";
    }
  } else if (mode == Mode::Bd2Dsth) {
    if (isTex == false) {
      return "#font[12]{B^{0}#rightarrow D^{*" + oppCharge + "}h^{" +
             chargeLabel + "}}";
    } else {
      return "$B^{0}\\rightarrow D^{*" + oppCharge + "}h^{" + chargeLabel +
             "}$";
    }
  } else if (mode == Mode::Bu2Dst0hst) {
    if (isTex == false) {
      return "#font[12]{B #rightarrow D^{*}h^{" + chargeLabel + "}#pi}";
    } else {
      return "$B^{" + chargeLabel + "}\\rightarrow D^{*}h^{" + chargeLabel +
             "}\\pi$";
    }
  } else if (mode == Mode::Lb2Omegach_Lcpi0) {
    if (isTex == false) {
      return "#font[12]{#Lambda^{0}_{b}#rightarrow #Omega^{" + oppCharge +
             "}_{c}h^{" + chargeLabel + "}}";
    } else {
      return "$\\Lambda^{0}_{b}\\rightarrow \\Omega^{" + oppCharge +
             "}_{c}h^{" + chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0pi_D0gamma) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0} #rightarrow D^{0}#gamma) #pi^{" +
             chargeLabel + "}}";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\gamma) \\pi^{" +
             chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0K_D0gamma) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0} #rightarrow D^{0}#gamma) K^{" + chargeLabel +
             "}}";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\gamma) K^{" +
             chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0pi_D0pi0) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0}#rightarrow D^{0}#pi^{0}) #pi^{" +
             chargeLabel + "}}";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\pi^{0}) \\pi^{" +
             chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0K_D0pi0) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0}#rightarrow D^{0}#pi^{0}) K^{" + chargeLabel +
             "}}";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\pi^{0}) K^{" +
             chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0pi_D0gamma_WN) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0} #rightarrow D^{0}#gamma) #pi^{" +
             chargeLabel + "}} WN";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\gamma) \\pi^{" +
             chargeLabel + "}$ WN";
    }
  } else if (mode == Mode::Bu2Dst0K_D0gamma_WN) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0} #rightarrow D^{0}#gamma) K^{" + chargeLabel +
             "}} WN";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\gamma) K^{" +
             chargeLabel + "}$ WN";
    }
  } else if (mode == Mode::Bu2Dst0pi_D0pi0_WN) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0}#rightarrow D^{0}#pi^{0}) #pi^{" +
             chargeLabel + "}} WN";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\pi^{0}) \\pi^{" +
             chargeLabel + "}$ WN";
    }
  } else if (mode == Mode::Bu2Dst0K_D0pi0_WN) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel +
             "}#rightarrow (D^{*0}#rightarrow D^{0}#pi^{0}) K^{" + chargeLabel +
             "}} WN";
    } else {
      return "$B^{" + chargeLabel +
             "}\\rightarrow (D^{*0} \\rightarrow D^{0}\\pi^{0}) K^{" +
             chargeLabel + "}$ WN";
    }
  } else if (mode == Mode::Bu2Dst0pi_WN) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel + "}#rightarrow D^{*0}#pi^{" +
             chargeLabel + "}} WN";
    } else {
      return "$B^{" + chargeLabel + "}\\rightarrow D^{*0}\\pi^{" + chargeLabel +
             "}$ WN";
    }
  } else if (mode == Mode::Bu2Dst0K_WN) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel + "}#rightarrow D^{*0}K^{" +
             chargeLabel + "}} WN";
    } else {
      return "$B^{" + chargeLabel + "}\\rightarrow D^{*0}K^{" + chargeLabel +
             "}$ WN";
    }
  } else if (mode == Mode::Bu2D0rho) {
    if (isTex == false) {
      return "#font[12]{B #rightarrow D #rho}";
    } else {
      return "$B \\rightarrow D \\rho$";
    }
  } else if (mode == Mode::Bu2D0Kst) {
    if (isTex == false) {
      return "#font[12]{B #rightarrow D K^{*}}";
    } else {
      return "$B \\rightarrow D K^{*}$";
    }
  } else if (mode == Mode::Bd2Dstpi) {
    if (isTex == false) {
      return "#font[12]{B^{0}#rightarrow D^{*" + oppCharge + "}#pi^{" +
             chargeLabel + "}}";
    } else {
      return "$B^{0}\\rightarrow D^{*" + oppCharge + "}\\pi^{" + chargeLabel +
             "}$";
    }
  } else if (mode == Mode::Bd2DstK) {
    if (isTex == false) {
      return "#font[12]{B^{0}#rightarrow D^{*" + oppCharge + "}K^{" +
             chargeLabel + "}}";
    } else {
      return "$B^{0}\\rightarrow D^{*" + oppCharge + "}K^{" + chargeLabel +
             "}$";
    }
  } else if (mode == Mode::Bu2Dst0rho) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel + "}#rightarrow D^{*0}#rho^{" +
             chargeLabel + "}}";
    } else {
      return "$B^{" + chargeLabel + "}\\rightarrow D^{*0}\\rho^{" +
             chargeLabel + "}$";
    }
  } else if (mode == Mode::Bu2Dst0Kst) {
    if (isTex == false) {
      return "#font[12]{B^{" + chargeLabel + "}#rightarrow D^{*0}K^{*" +
             chargeLabel + "}}";
    } else {
      return "$B^{" + chargeLabel + "}\\rightarrow D^{*0}K^{*" + chargeLabel +
             "}$";
    }
  } else if (mode == Mode::Lb2Omegacpi_Lcpi0) {
    if (isTex == false) {
      return "#font[12]{#Lambda^{0}_{b}#rightarrow #Omega^{" + oppCharge +
             "}_{c}#pi^{" + chargeLabel + "}}";
    } else {
      return "$\\Lambda^{0}_{b}\\rightarrow \\Omega^{" + oppCharge +
             "}_{c}\\pi^{" + chargeLabel + "}$";
    }
  } else if (mode == Mode::Lb2OmegacK_Lcpi0) {
    if (isTex == false) {
      return "#font[12]{#Lambda^{0}_{b}#rightarrow #Omega^{" + oppCharge +
             "}_{c}K^{" + chargeLabel + "}}";
    } else {
      return "$\\Lambda^{0}_{b}\\rightarrow \\Omega^{" + oppCharge +
             "}_{c}}K^{" + chargeLabel + "}$";
    }
  } else if (mode == Mode::Bs2D0Kst0) {
    if (isTex == false) {
      return "#font[12]{B^{0}_{s}#rightarrow D^{0}K^{" + chargeLabel +
             "}#pi^{" + oppCharge + "}}";
    } else {
      return "B^{0}_{s}\\rightarrow D^{0}K^{" + chargeLabel + "}\\pi^{" +
             oppCharge + "}";
    }
  } else if (mode == Mode::Bs2Dst0Kst0) {
    if (isTex == false) {
      return "#font[12]{B^{0}_{s}#rightarrow D^{*0}K^{" + chargeLabel +
             "}#pi^{" + oppCharge + "}}";
    } else {
      return "B^{0}_{s}\\rightarrow D^{*0}K^{" + chargeLabel + "}\\pi^{" +
             oppCharge + "}";
    }
  } else {
    throw std::runtime_error("No label available for " + EnumToString(mode) +
                             "\n");
  }
}
