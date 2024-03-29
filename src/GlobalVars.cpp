#include "GlobalVars.h"

std::string MakePidKey(Bachelor bachelor, Charge charge) {
  return EnumToString(bachelor) + "_" + EnumToString(charge);
}

double ReturnPidEffs(Bachelor bachelor, Charge charge, bool returnEff) {
  std::string txtFileName =
      Configuration::Get().inputDir + "/efficiencies/pidEffs_" +
      EnumToString(Configuration::Get().neutral()) + ".txt";
  if (!fexists(txtFileName)) {
    throw std::logic_error("ReturnPidEffs: " + txtFileName + " doesn't exist.");
  }
  std::ifstream inFile(txtFileName);
  std::string line;
  // Loop over lines in txt file
  while (std::getline(inFile, line)) {
    // Separate label and value (white space)
    std::vector<std::string> lineVec = SplitLine(line);
    if (lineVec[0] == EnumToString(bachelor) && lineVec[1] == EnumToString(charge)) {
      if (returnEff == true) {
        return std::stod(lineVec[2]);
      } else {
        return std::stod(lineVec[3]);
      }
    }
  }
}

GlobalVars::GlobalVars(int uniqueId)
    : uniqueId_(uniqueId),
      crossFeedRate_(nullptr),
      Delta_A_CP_(Params::Get().CreateFixed("Delta_A_CP", uniqueId_, -1.54e-03,
                                            2.9e-04, Systematic::Delta_A_CP,
                                            Sign::none)),
      A_Prod_(Params::Get().CreateFloating("A_Prod", uniqueId_, 0, -1, 1)),
      A_pi_(Params::Get().CreateFixed("A_pi", uniqueId_, -6.4e-04, 1.8e-04,
                                      Systematic::A_pi, Sign::none)),
      a_Prod_(MakeLittleAsym(("a_Prod_" + std::to_string(uniqueId_)).c_str(),
                             *A_Prod_)),
      a_pi_(MakeLittleAsym(("a_pi_" + std::to_string(uniqueId_)).c_str(),
                           *A_pi_)),
      kBF_Bu2Dst0pi_(Params::Get().CreateFixed(
          "kBF_Bu2Dst0pi", uniqueId_, 4.90e-03, 0.17e-03,
          Systematic::kBF_Bu2Dst0pi, Sign::same)),
      kBF_Bu2Dst0K_(Params::Get().CreateFixed(
          "kBF_Bu2Dst0K", uniqueId_, 3.97e-04, 0.31e-04,
          Systematic::kBF_Bu2Dst0K, Sign::same)),
      kBF_Dst02D0pi0_(Params::Get().CreateFixed(
          "kBF_Dst02D0pi0", uniqueId_, 64.7e-02, 0.9e-02,
          Systematic::kBF_Dst02D0pi0, Sign::same)),
      kBF_Dst02D0gamma_(Params::Get().CreateFixed(
          "kBF_Dst02D0gamma", uniqueId_, 35.3e-02, 0.9e-02,
          Systematic::kBF_Dst02D0gamma, Sign::same)),
      kBF_D02kpi_(Params::Get().CreateFixed("kBF_D02kpi", uniqueId_, 3.950e-02,
                                            0.031e-02, Systematic::kBF_D02kpi,
                                            Sign::same)),
      kBF_D02kk_(Params::Get().CreateFixed("kBF_D02kk", uniqueId_, 4.08e-03,
                                           0.06e-03, Systematic::kBF_D02kk,
                                           Sign::same)),
      kBF_D02pipi_(Params::Get().CreateFixed(
          "kBF_D02pipi", uniqueId_, 1.455e-03, 0.024e-03,
          Systematic::kBF_D02pipi, Sign::same)),
      kBF_D02pik_(Params::Get().CreateFixed("kBF_D02pik", uniqueId_, 1.50e-04,
                                            0.07e-04, Systematic::kBF_D02pik,
                                            Sign::same)),
      // kBF_Bd2Dstpi_(Params::Get().CreateFixed(
      //     "kBF_Bd2Dstpi", uniqueId_, 2.74e-03, 0.13e-03,
      //     Systematic::kBF_Bd2Dstpi, Sign::same)),
      // kBF_Bd2DstK_(Params::Get().CreateFixed("kBF_Bd2DstK",
      // uniqueId_, 2.12e-04,
      //                                        0.15e-04,
      //                                        Systematic::kBF_Bd2DstK,
      //                                        Sign::same)),
      // kBF_Dst2D0pi_(Params::Get().CreateFixed("kBF_Dst2D0pi", uniqueId_,
      // 0.677,
      //                                         0.005,
      //                                         Systematic::kBF_Dst2D0pi,
      //                                         Sign::same)),
      // kBF_Bu2D0rho_(Params::Get().CreateFixed(
      //     "kBF_Bu2D0rho", uniqueId_, 1.34e-02, 0.18e-02,
      //     Systematic::kBF_Bu2D0rho, Sign::same)),
      // kBF_Bu2D0Kst_(
      //     Params::Get().CreateFixed("kBF_Bu2D0Kst", uniqueId_, 5.3e-04,
      //     0.4e-04,
      //                               Systematic::kBF_Bu2D0Kst, Sign::same)),
      // kBF_Bd2D0rho0_(Params::Get().CreateFixed(
      //     "kBF_Bd2D0rho0", uniqueId_, 3.21e-04, 0.21e-04,
      //     Systematic::kBF_Bd2D0rho0, Sign::same)),
      // kBF_Bd2D0Kst0_(Params::Get().CreateFixed(
      //     "kBF_Bd2D0Kst0", uniqueId_, 4.5e-05, 0.6e-05,
      //     Systematic::kBF_Bu2D0Kst, Sign::same)),
      kBF_Bu2Dst0rho_(Params::Get().CreateFixed(
          "kBF_Bu2Dst0rho", uniqueId_, 9.8e-03, 1.7e-03,
          Systematic::kBF_Bu2Dst0rho, Sign::same)),
      kBF_Bu2Dst0Kst_(Params::Get().CreateFixed(
          "kBF_Bu2Dst0Kst", uniqueId_, 8.1e-04, 1.4e-04,
          Systematic::kBF_Bu2Dst0Kst, Sign::same)),
      pidEffMap_(),
      constraints_argSet_(new RooArgSet(
          ("constraints_argSet_" + std::to_string(uniqueId_)).c_str())),
      // -------------------- CP Observables -------------------- //
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_CP_Bu2Dst0h_WN_(nullptr),
      R_CP_Bd2Dsth_(nullptr),
      R_CP_Bu2D0hst_(nullptr),
      R_CP_Bu2Dst0hst_(nullptr) {
  // std::vector<Charge> chargeVec = {Charge::plus, Charge::minus};
  // for (auto &c : chargeVec) {
  //   pidEffMap_[MakePidKey(Bachelor::k, c)] = Params::Get().CreateFixed(
  //       "pidEffK", uniqueId_, Configuration::Get().neutral(), c,
  //       ReturnPidEffs(c, true), ReturnPidEffs(c, false), Systematic::pidEffK,
  //       Sign::same);
  // }
  // pidEffMap_[MakePidKey(Bachelor::k, Charge::total)] =
  //     std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
  //         ("pidEffK_" + ComposeName(uniqueId_,
  //         Configuration::Get().neutral(),
  //                                   Charge::total))
  //             .c_str(),
  //         "0.5*(@0+@1)",
  //         RooArgSet(*pidEffMap_[MakePidKey(Bachelor::k, Charge::plus)],
  //                    *pidEffMap_[MakePidKey(Bachelor::k, Charge::minus)])));
  // Total PID eff from MC effs, and systematic from gamma MC vs data difference
  // (higher stats)
  pidEffMap_[MakePidKey(Bachelor::k, Charge::total)] =
      Params::Get().CreateFixed(
          "pidEffK", uniqueId_, Configuration::Get().neutral(), Charge::total,
          ReturnPidEffs(Bachelor::k, Charge::total, true),
          ReturnPidEffs(Bachelor::k, Charge::total, false), Systematic::pidEffK, Sign::same);
  pidEffMap_[MakePidKey(Bachelor::k, Charge::plus)] =
      pidEffMap_[MakePidKey(Bachelor::k, Charge::total)];
  pidEffMap_[MakePidKey(Bachelor::k, Charge::minus)] =
      pidEffMap_[MakePidKey(Bachelor::k, Charge::total)];
  // pidEffMap_[MakePidKey(Bachelor::pi, Charge::total)] =
  //     Params::Get().CreateFixed(
  //         "pidEffPi", uniqueId_, Configuration::Get().neutral(), Charge::total,
  //         0.995, 0.002, Systematic::pidEffPi, Sign::same);
  pidEffMap_[MakePidKey(Bachelor::pi, Charge::total)] =
      Params::Get().CreateFixed(
          "pidEffPi", uniqueId_, Configuration::Get().neutral(), Charge::total,
          ReturnPidEffs(Bachelor::pi, Charge::total, true),
          ReturnPidEffs(Bachelor::pi, Charge::total, false), Systematic::pidEffPi, Sign::same);
  pidEffMap_[MakePidKey(Bachelor::pi, Charge::plus)] =
      pidEffMap_[MakePidKey(Bachelor::pi, Charge::total)];
  pidEffMap_[MakePidKey(Bachelor::pi, Charge::minus)] =
      pidEffMap_[MakePidKey(Bachelor::pi, Charge::total)];

  std::vector<Year> yVec = {Year::y2011, Year::y2012, Year::y2015,
                            Year::y2016, Year::y2017, Year::y2018};
  double wRun1 = 0;
  double wRun2 = 0;
  double lumi = 0;
  for (auto &y : yVec) {
    if (y == Year::y2011) {
      wRun1 += 0.98;
      lumi += 0.98;
    } else if (y == Year::y2012) {
      wRun1 += 1.99;
      lumi += 1.99;
    } else if (y == Year::y2015) {
      wRun2 += 0.28;
      lumi += 0.28;
    } else if (y == Year::y2016) {
      wRun2 += 1.65;
      lumi += 1.65;
    } else if (y == Year::y2017) {
      wRun2 += 1.7;
      lumi += 1.7;
    } else if (y == Year::y2018) {
      wRun2 += 2.19;
      lumi += 2.19;
    }
  }
  double cfRun1 = 5.34e-05;
  double cfRun1Err = 0.27e-05;
  double cfRun2 = 10.16e-05;
  double cfRun2Err = 0.37e-05;
  // Weighted mean: sum (w * x) / sum(w)
  double cfAv = (cfRun1 * wRun1 + cfRun2 * wRun2) / lumi;
  // Weighted av: sqrt ( 1 / sum(err^-2) )
  double cfErr = std::sqrt(1 / (pow(cfRun1Err, -2) + pow(cfRun2Err, -2)));
  crossFeedRate_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFixed("crossFeedRate", uniqueId_, cfAv, cfErr,
                                Systematic::crossFeedRate, Sign::same));

  double k_R_CP_Bu2Dst0h_D0gamma = 0.902;
  double k_R_CP_Bu2Dst0h_D0pi0 = 1.138;
  // if (Configuration::Get().blindFit() == true) {
  //   if (Configuration::Get().neutral() == Neutral::gamma) {
  //     R_CP_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(
  //         Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0gamma_Blind", uniqueId_,
  //                                      k_R_CP_Bu2Dst0h_D0gamma, -2, 2));
  //     R_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
  //         ("R_CP_Bu2Dst0h_D0gamma_" + std::to_string(uniqueId_)).c_str(), 0.3,
  //         *R_CP_Bu2Dst0h_D0gamma_Blind_));
  //   }
  //   R_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
  //       Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_,
  //                                    k_R_CP_Bu2Dst0h_D0pi0, -2, 2));
  //   R_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(
  //       MakeBlind(("R_CP_Bu2Dst0h_D0pi0_" + std::to_string(uniqueId_)).c_str(),
  //                 0.3, *R_CP_Bu2Dst0h_D0pi0_Blind_));
  // } else {
  if (Configuration::Get().neutral() == Neutral::gamma) {
    R_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0gamma", uniqueId_,
                                     k_R_CP_Bu2Dst0h_D0gamma, -2, 2));
  }
  R_CP_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "R_CP_Bu2Dst0h_D0pi0", uniqueId_, k_R_CP_Bu2Dst0h_D0pi0, -2, 2));
  // }

  if (Configuration::Get().neutral() == Neutral::pi0) {
    R_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "R_CP_Bu2Dst0h_D0gamma", uniqueId_,
            ReadGammaObs("R_CP_Bu2Dst0h_D0gamma", ReturnType::val),
            ReadGammaObs("R_CP_Bu2Dst0h_D0gamma", ReturnType::stdL),
            ReadGammaObs("R_CP_Bu2Dst0h_D0gamma", ReturnType::stdH),
            Systematic::R_CP_Bu2Dst0h_D0gamma, Sign::same));
    }
  R_CP_Bu2Dst0h_WN_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFloating("R_CP_Bu2Dst0h_WN", uniqueId_, 1, -2, 2));
  R_CP_Bd2Dsth_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "R_CP_Bd2Dsth", uniqueId_, 1.0, 0.0, Systematic::NA, Sign::none));
  // HFLAV: R_CP+, BF average of B+ and B0
  // R_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
  //     "R_CP_Bu2D0hst", uniqueId_, 1.21, 0.07, Systematic::R_CP_Bu2D0hst, Sign::same));
  // //     Donal's calculation from hadronic parameters - consistent within 3 sigma
  if (Configuration::Get().neutral() == Neutral::gamma) {
    R_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFixed("R_CP_Bu2D0hst", uniqueId_, 1.04, 0.06,
                                  Systematic::R_CP_Bu2D0hst, Sign::same));
  } else {
    R_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2D0hst", uniqueId_, 1, 0, 10));
    // R_CP_Bu2D0hst_gaus_ = std::shared_ptr<RooGaussian>(new RooGaussian(
    //     ("R_CP_Bu2D0hst_gaus_" + std::to_string(uniqueId_)).c_str(), "",
    //     *R_CP_Bu2D0hst_, RooFit::RooConst(1.04), RooFit::RooConst(0.06)));
    // constraints_argSet_->add(*R_CP_Bu2D0hst_gaus_);
  }
  double min = 0.;
  double max = 20.;
  // double max = 15.;
  double start = 4.5;
  if (Configuration::Get().neutral() == Neutral::pi0) {
    min = 0.;
    max = 10.;
    start = 2.7965e+00;
  }
  R_CP_Bu2Dst0hst_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "R_CP_Bu2Dst0hst", uniqueId_, start, min, max));
}
