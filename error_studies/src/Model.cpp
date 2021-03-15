#include "Model.h"

Model::Model(Configuration &config, int _uniqueId)
    : uniqueId(_uniqueId),
      buMean(("buMean_" + std::to_string(uniqueId)).c_str(), "", 5.2819e+03,
             5250, 5290),
      buSigma(("buSigma_" + std::to_string(uniqueId)).c_str(), "", 20, 10, 50),
      buA1(("buA1_" + std::to_string(uniqueId)).c_str(), "", 1, 0, 5),
      buN1(("buN1_" + std::to_string(uniqueId)).c_str(), "", 10),
      buA2(("buA2_" + std::to_string(uniqueId)).c_str(), "", -1, -5, -0.00001),
      buN2(("buN2_" + std::to_string(uniqueId)).c_str(), "", 10),
      buFrac(("buFrac_" + std::to_string(uniqueId)).c_str(), "", 2.0967e-01, 0,
             1),
      buPdf1(("buPdf1_" + std::to_string(uniqueId)).c_str(), "", config.buMass,
             buMean, buSigma, buA1, buN1),
      buPdf2(("buPdf2_" + std::to_string(uniqueId)).c_str(), "", config.buMass,
             buMean, buSigma, buA2, buN2),
      buPdf(("buPdf_" + std::to_string(uniqueId)).c_str(), "",
            RooArgSet(buPdf1, buPdf2), buFrac),
      deltaMean(("deltaMean_" + std::to_string(uniqueId)).c_str(), "", 143, 136,
                160),
      deltaSigma(("deltaSigma_" + std::to_string(uniqueId)).c_str(), "", 2, 0,
                 10),
      deltaA1(("deltaA1_" + std::to_string(uniqueId)).c_str(), "", 1, 0, 5),
      deltaN1(("deltaN1_" + std::to_string(uniqueId)).c_str(), "", 10),
      deltaA2(("deltaA2_" + std::to_string(uniqueId)).c_str(), "", -1, -5,
              -0.00001),
      deltaN2(("deltaN2_" + std::to_string(uniqueId)).c_str(), "", 10),
      deltaFrac(("deltaFrac_" + std::to_string(uniqueId)).c_str(), "", 0.5, 0,
                1),
      deltaPdf1(("deltaPdf1_" + std::to_string(uniqueId)).c_str(), "",
                config.deltaMass, deltaMean, deltaSigma, deltaA1, deltaN1),
      deltaPdf2(("deltaPdf2_" + std::to_string(uniqueId)).c_str(), "",
                config.deltaMass, deltaMean, deltaSigma, deltaA2, deltaN2),
      deltaPdf(("deltaPdf_" + std::to_string(uniqueId)).c_str(), "",
               RooArgSet(deltaPdf1, deltaPdf2), deltaFrac),
      N_tot(("N_tot_" + std::to_string(uniqueId)).c_str(), "", 10000, 0, 50000),
      eff_Bu(("eff_Bu_" + std::to_string(uniqueId)).c_str(), "",
             ReturnBoxEff(Mode::Bu2Dst0pi_D0pi0, config, Efficiency::buEff)),
      eff_Delta(
          ("eff_Delta_" + std::to_string(uniqueId)).c_str(), "",
          ReturnBoxEff(Mode::Bu2Dst0pi_D0pi0, config, Efficiency::deltaEff)),
      N_Bu(nullptr),
      N_Delta(("N_Delta_" + std::to_string(uniqueId)).c_str(), "@0*@1",
              RooArgList(N_tot, eff_Delta)),
      buLambda(("buLambda_" + std::to_string(uniqueId)).c_str(), "", -0.005, -1,
               1),
      buBkgPdf(("buBkgPdf_" + std::to_string(uniqueId)).c_str(), "",
               config.buMass, buLambda),
      deltaLambda(("deltaLambda_" + std::to_string(uniqueId)).c_str(), "", 0.05,
                  -1, 1),
      deltaBkgPdf(("deltaBkgPdf_" + std::to_string(uniqueId)).c_str(), "",
                  config.deltaMass, deltaLambda),
      bkgPdf(("bkgPdf_" + std::to_string(uniqueId)).c_str(), "",
             RooArgSet(buBkgPdf, deltaBkgPdf)),
      N_Bkg(5000),
      N_Bu_Bkg(("N_Bu_Bkg_" + std::to_string(uniqueId)).c_str(), "",
                           N_Bkg, 0, 50000),
      N_Delta_Bkg(("N_Delta_Bkg_" + std::to_string(uniqueId)).c_str(), "",
                  N_Bkg, 0, 50000),
      buFunctions(("buFunctions_" + std::to_string(uniqueId)).c_str()),
      buYields(("buYields_" + std::to_string(uniqueId)).c_str()),
      deltaFunctions(("deltaFunctions_" + std::to_string(uniqueId)).c_str()),
      deltaYields(("deltaYields_" + std::to_string(uniqueId)).c_str()),
      buAddPdf(nullptr),
      deltaAddPdf(nullptr),
      simPdf(nullptr) {
  if (config.fit1D == false) {
    N_Bu = std::unique_ptr<RooFormulaVar>(
        new RooFormulaVar(("N_Bu_" + std::to_string(uniqueId)).c_str(), "@0*@1",
                          RooArgList(N_tot, eff_Bu)));
  } else {
    N_Bu = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Bu_" + std::to_string(uniqueId)).c_str(), "", 10000, 0, 50000));
  }
  buFunctions.add(buPdf);
  deltaFunctions.add(deltaPdf);
  if (config.signalOnly == false) {
    buFunctions.add(buBkgPdf);
    deltaFunctions.add(deltaBkgPdf);
  }

  buYields.add(*N_Bu);
  deltaYields.add(N_Delta);
  if (config.signalOnly == false) {
    buYields.add(N_Bu_Bkg);
    deltaYields.add(N_Delta_Bkg);
  }

  buAddPdf = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("buAddPdf_" + std::to_string(uniqueId)).c_str(), "", buFunctions, buYields));
  deltaAddPdf = std::unique_ptr<RooAddPdf>(
      new RooAddPdf(("deltaAddPdf_" + std::to_string(uniqueId)).c_str(), "",
                    deltaFunctions, deltaYields));

  if (config.fit1D == false) {
    simPdf = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
        ("simPdf_" + std::to_string(uniqueId)).c_str(), "", config.fitting));
    simPdf->addPdf(*buAddPdf, EnumToString(Mass::bu).c_str());
    simPdf->addPdf(*deltaAddPdf, EnumToString(Mass::delta).c_str());
  }
}

// 136 160
// RooRealVar buMean("Bu2Dst0h_D0pi0_mean1Bu", "", 5.2730e+03);
// RooRealVar buSigma("Bu2Dst0h_D0pi0_sigma1Bu", "", 2.2931e+01);
// RooRealVar buA1("Bu2Dst0h_D0pi0_a1Bu", "", 9.1003e-01);
// RooRealVar buN1("Bu2Dst0h_D0pi0_n1Bu", "", 10);
// RooRealVar buA2("Bu2Dst0h_D0pi0_a2Bu", "", -2.2424e+00);
// RooRealVar buN2("Bu2Dst0h_D0pi0_n2Bu", "", 10);
// RooRealVar buFrac("Bu2Dst0h_D0pi0_fracPdf1Bu", "buFraction of component 1
// in bu PDF", 9.5717e-02);
//
// 5170 5370
// RooRealVar deltaMean("Bu2Dst0h_D0pi0_meanDelta", "", 1.4241e+02);
// RooRealVar deltaSigma("Bu2Dst0h_D0pi0_sigmaDelta", "", 1.6230e+00);
// RooRealVar deltaA1("Bu2Dst0h_D0pi0_a1Delta", "", 7.5392e-01);
// RooRealVar deltaN1("Bu2Dst0h_D0pi0_n1Delta", "", 10);
// RooRealVar deltaA2("Bu2Dst0h_D0pi0_a2Delta", "", -6.1887e-01);
// RooRealVar deltaN2("Bu2Dst0h_D0pi0_n2Delta", "", 10);
// RooRealVar deltaFrac("Bu2Dst0h_D0pi0_fracPdf1Delta", "deltaFraction of
// component 1 in delta PDF", 2.1771e-01);

// 5170 5220
// RooRealVar deltaMean("Bu2Dst0h_D0pi0_meanDelta", "", 1.4287e+02);
// RooRealVar deltaSigma("Bu2Dst0h_D0pi0_sigmaDelta", "", 2.1217e+00);
// RooRealVar deltaA1("Bu2Dst0h_D0pi0_a1Delta", "", 4.1785e+00);
// RooRealVar deltaN1("Bu2Dst0h_D0pi0_n1Delta", "", 10);
// RooRealVar deltaA2("Bu2Dst0h_D0pi0_a2Delta", "", -3.8947e+00);
// RooRealVar deltaN2("Bu2Dst0h_D0pi0_n2Delta", "", 10);
// RooRealVar deltaFrac("Bu2Dst0h_D0pi0_fracPdf1Delta", "deltaFraction of
// component 1 in delta PDF", 4.6238e-01);

// RooCBShape deltaPdf1("deltaPdf1", "", config.deltaMass, deltaMean,
// deltaSigma,
//                      deltaA1, deltaN1);
// RooCBShape deltaPdf2("deltaPdf2", "", config.deltaMass, deltaMean,
// deltaSigma,
//                      deltaA2, deltaN2);
// RooAddPdf deltaPdf("deltaPdf", "", RooArgSet(deltaPdf1, deltaPdf2),
//                    deltaFrac);
