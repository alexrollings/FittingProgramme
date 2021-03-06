#include "GlobalVars.h"

std::string MakePidKey(Bachelor bachelor, Charge charge) {
  return EnumToString(bachelor) + "_" + EnumToString(charge);
}

double ReturnPidEffs(Charge charge, bool returnEff) {
  std::string txtFileName =
      "/home/rollings/Bu2Dst0h_scripts/pid_corr/output/PID_effs_mc_" +
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
    if (lineVec[0] == EnumToString(charge)) {
      if (returnEff == true) {
        return std::stod(lineVec[1]);
      } else {
        return std::stod(lineVec[2]);
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
      A_Kpi_(Params::Get().CreateFixed("A_Kpi", uniqueId_, -1.13e-02, 1.5e-03,
                                       Systematic::A_Kpi, Sign::none)),
      A_pi_(Params::Get().CreateFixed("A_pi", uniqueId_, -6.45e-04, 1.84e-04,
                                      Systematic::A_pi, Sign::none)),
      a_Prod_(MakeLittleAsym(("a_Prod_" + std::to_string(uniqueId_)).c_str(),
                             *A_Prod_)),
      a_Kpi_(MakeLittleAsym(("a_Kpi_" + std::to_string(uniqueId_)).c_str(),
                            *A_Kpi_)),
      a_pi_(
          MakeLittleAsym(("a_pi_" + std::to_string(uniqueId_)).c_str(), *A_pi_)),
      pidEffMap_() {
  // std::vector<Charge> chargeVec = {Charge::plus, Charge::minus};
  // for (auto &c : chargeVec) {
  //   pidEffMap_[MakePidKey(Bachelor::k, c)] = Params::Get().CreateFixed(
  //       "pidEffK", uniqueId_, Configuration::Get().neutral(), c,
  //       ReturnPidEffs(c, true), ReturnPidEffs(c, false), Systematic::pidEffK,
  //       Sign::positive);
  // }
  // pidEffMap_[MakePidKey(Bachelor::k, Charge::total)] =
  //     std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
  //         ("pidEffK_" + ComposeName(uniqueId_, Configuration::Get().neutral(),
  //                                   Charge::total))
  //             .c_str(),
  //         "0.5*(@0+@1)",
  //         RooArgList(*pidEffMap_[MakePidKey(Bachelor::k, Charge::plus)],
  //                    *pidEffMap_[MakePidKey(Bachelor::k, Charge::minus)])));
  // Total PID eff from MC effs, and systematic from gamma MC vs data difference
  // (higher stats)
  pidEffMap_[MakePidKey(Bachelor::k, Charge::total)] =
      Params::Get().CreateFixed("pidEffK", uniqueId_,
                                Configuration::Get().neutral(), Charge::total,
                                ReturnPidEffs(Charge::total, true), 0.01,
                                Systematic::pidEffK, Sign::positive);
  pidEffMap_[MakePidKey(Bachelor::k, Charge::plus)] =
      pidEffMap_[MakePidKey(Bachelor::k, Charge::total)];
  pidEffMap_[MakePidKey(Bachelor::k, Charge::minus)] =
      pidEffMap_[MakePidKey(Bachelor::k, Charge::total)];
  pidEffMap_[MakePidKey(Bachelor::pi, Charge::total)] =
      // Params::Get().CreateFloating("pidEffPi", uniqueId_,
      //                              Configuration::Get().neutral(),
      //                              Charge::total, 0.996, 0.5, 1.5);
      Params::Get().CreateFixed(
          "pidEffPi", uniqueId_, Configuration::Get().neutral(), Charge::total,
          0.995, 0.002, Systematic::pidEffPi, Sign::positive);
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
                                Systematic::crossFeedRate, Sign::positive));
}
