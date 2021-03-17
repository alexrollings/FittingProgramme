#include "Model.h"

Model::Model(Configuration &config, int _uniqueId)
    : uniqueId(_uniqueId),
      buMean(("buMean_" + std::to_string(uniqueId)).c_str(), "", 5.2819e+03,
             5250, 5290),
      buSigma(("buSigma_" + std::to_string(uniqueId)).c_str(), "", 20, 10, 50),
      // buA1(("buA1_" + std::to_string(uniqueId)).c_str(), "", 1, 0, 5),
      buN1(("buN1_" + std::to_string(uniqueId)).c_str(), "", 10),
      // buA2(("buA2_" + std::to_string(uniqueId)).c_str(), "", -1, -5,
      // -0.00001),
      buN2(("buN2_" + std::to_string(uniqueId)).c_str(), "", 10),
      buFrac(("buFrac_" + std::to_string(uniqueId)).c_str(), "", 2.0967e-01, 0,
             1),
      // m(B): 5230 - 5300
      buA1(("buA1_" + std::to_string(uniqueId)).c_str(), "", 9.8052e-01),
      buA2(("buA2_" + std::to_string(uniqueId)).c_str(), "", -2.2181e+00),
      // m(B): 5170 - 5370
      // buMean(("buMean_" + std::to_string(uniqueId)).c_str(), "", 5.2728e+03),
      // buSigma(("buSigma_" + std::to_string(uniqueId)).c_str(),
      // "", 2.2420e+01), buA1(("buA1_" + std::to_string(uniqueId)).c_str(),
      // "", 4.3526e+00), buN1(("buN1_" + std::to_string(uniqueId)).c_str(), "",
      // 10), buA2(("buA2_" + std::to_string(uniqueId)).c_str(), "",
      // -1.6871e+00), buN2(("buN2_" + std::to_string(uniqueId)).c_str(), "",
      // 10), buFrac(("buFrac_" + std::to_string(uniqueId)).c_str(),
      // "", 7.6254e-01), m(B): 5170 - 5220 buMean(("buMean_" +
      // std::to_string(uniqueId)).c_str(), "", 5.2728e+03), buSigma(("buSigma_"
      // + std::to_string(uniqueId)).c_str(),
      // "", 2.2356e+01), buA1(("buA1_" + std::to_string(uniqueId)).c_str(),
      // "", 4.3526e+00), buN1(("buN1_" + std::to_string(uniqueId)).c_str(), "",
      // 10), buA2(("buA2_" + std::to_string(uniqueId)).c_str(), "",
      // -1.6871e+00), buN2(("buN2_" + std::to_string(uniqueId)).c_str(), "",
      // 10), buFrac(("buFrac_" + std::to_string(uniqueId)).c_str(),
      // "", 8.3599e-01),
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
      // deltaA1(("deltaA1_" + std::to_string(uniqueId)).c_str(), "", 1, 0, 5),
      deltaN1(("deltaN1_" + std::to_string(uniqueId)).c_str(), "", 10),
      // deltaA2(("deltaA2_" + std::to_string(uniqueId)).c_str(), "", -1, -5,
      //         -0.00001),
      deltaN2(("deltaN2_" + std::to_string(uniqueId)).c_str(), "", 10),
      deltaFrac(("deltaFrac_" + std::to_string(uniqueId)).c_str(), "", 0.5, 0,
                1),
      // m(B): 5230 - 5300
      deltaA1(("deltaA1_" + std::to_string(uniqueId)).c_str(), "", 8.4308e-01),
      deltaA2(("deltaA2_" + std::to_string(uniqueId)).c_str(), "", -6.5446e-01),
      // m(B): 5170 - 5370
      // deltaMean(("deltaMean_" + std::to_string(uniqueId)).c_str(), "",
      //           1.4239e+02),
      // deltaSigma(("deltaSigma_" + std::to_string(uniqueId)).c_str(), "",
      //            1.6248e+00),
      // deltaA1(("deltaA1_" + std::to_string(uniqueId)).c_str(),
      // "", 9.2873e-01), deltaN1(("deltaN1_" +
      // std::to_string(uniqueId)).c_str(), "", 10), deltaA2(("deltaA2_" +
      // std::to_string(uniqueId)).c_str(), "", -6.5084e-01),
      // deltaN2(("deltaN2_" + std::to_string(uniqueId)).c_str(), "", 10),
      // deltaFrac(("deltaFrac_" + std::to_string(uniqueId)).c_str(), "",
      //           1.7763e-01),
      // m(B): 5170 - 5220
      // deltaMean(("deltaMean_" + std::to_string(uniqueId)).c_str(),
      // "", 1.4248e+02), deltaSigma(("deltaSigma_" +
      // std::to_string(uniqueId)).c_str(), "", 2.7309e+00), deltaA1(("deltaA1_"
      // + std::to_string(uniqueId)).c_str(), "", 3.4291e+00),
      // deltaN1(("deltaN1_" + std::to_string(uniqueId)).c_str(), "", 10),
      // deltaA2(("deltaA2_" + std::to_string(uniqueId)).c_str(), "",
      // -4.5894e+00), deltaN2(("deltaN2_" + std::to_string(uniqueId)).c_str(),
      // "", 10), deltaFrac(("deltaFrac_" + std::to_string(uniqueId)).c_str(),
      // "", 9.7755e-01),
      deltaPdf1(("deltaPdf1_" + std::to_string(uniqueId)).c_str(), "",
                config.deltaMass, deltaMean, deltaSigma, deltaA1, deltaN1),
      deltaPdf2(("deltaPdf2_" + std::to_string(uniqueId)).c_str(), "",
                config.deltaMass, deltaMean, deltaSigma, deltaA2, deltaN2),
      deltaPdf(("deltaPdf_" + std::to_string(uniqueId)).c_str(), "",
               RooArgSet(deltaPdf1, deltaPdf2), deltaFrac),
      // N_Sig(15000),
      N_Sig(40000),
      N_tot(("N_tot_" + std::to_string(uniqueId)).c_str(), "", N_Sig, 0, 50000),
      eff_Bu(("eff_Bu_" + std::to_string(uniqueId)).c_str(), "",
             ReturnBoxEff(Mode::Bu2Dst0pi_D0pi0, config, Efficiency::buEff)),
      eff_Delta(
          ("eff_Delta_" + std::to_string(uniqueId)).c_str(), "",
          ReturnBoxEff(Mode::Bu2Dst0pi_D0pi0, config, Efficiency::deltaEff)),
      N_Bu(nullptr),
      N_Delta(("N_Delta_" + std::to_string(uniqueId)).c_str(), "@0*@1",
              RooArgList(N_tot, eff_Delta)),
      // buLambda(("buLambda_" + std::to_string(uniqueId)).c_str(), "", -0.005,
      // -1,
      //          1),
      // buBkgPdf(("buBkgPdf_" + std::to_string(uniqueId)).c_str(), "",
      //          config.buMass, buLambda),
      // deltaLambda(("deltaLambda_" + std::to_string(uniqueId)).c_str(), "",
      // 0.05,
      //             -1, 1),
      // deltaBkgPdf(("deltaBkgPdf_" + std::to_string(uniqueId)).c_str(), "",
      //             config.deltaMass, deltaLambda),
      buBkgMean(("buBkgMean_" + std::to_string(uniqueId)).c_str(), "",
                5.2445e+03, 5235, 5255),
      buBkgSigma(("buBkgSigma_" + std::to_string(uniqueId)).c_str(), "",
                 8.5073e+01, 60, 95),
      // m(B) 5170 - 5370
      // buBkgMean(("buBkgMean_" + std::to_string(uniqueId)).c_str(), "",
      //           5.2466e+03),
      // buBkgSigma(("buBkgSigma_" + std::to_string(uniqueId)).c_str(), "",
      //            8.1571e+01),
      // m(B): 5170 - 5220
      // buBkgMean(("buBkgMean_" + std::to_string(uniqueId)).c_str(),
      // "", 5.2474e+03), buBkgSigma(("buBkgSigma_" +
      // std::to_string(uniqueId)).c_str(), "", 8.0989e+01),
      buBkgPdf(("buBkgPdf_" + std::to_string(uniqueId)).c_str(), "",
               config.buMass, buBkgMean, buBkgSigma),
      deltaBkgThreshold(
          ("deltaBkgThreshold_" + std::to_string(uniqueId)).c_str(), "",
          1.3406e+02),
      deltaBkgC(("deltaBkgC_" + std::to_string(uniqueId)).c_str(), "",
                1.0052e+01),
      // deltaBkgA(("deltaBkgA_" + std::to_string(uniqueId)).c_str(), "",
      //           -2.4211e+00, -5, 5),
      // m(B): 5170 - 5370
      // deltaBkgA(("deltaBkgA_" + std::to_string(uniqueId)).c_str(), "",
      //           -4.6769e+00),
      // 5170 - 5220
      // deltaBkgA(("deltaBkgA_" + std::to_string(uniqueId)).c_str(), "",
      // -3.2607e+00),
      // 5230 - 5300
      deltaBkgA(("deltaBkgA_" + std::to_string(uniqueId)).c_str(), "",
                2.0868e+00),
      deltaBkgB(("deltaBkgB_" + std::to_string(uniqueId)).c_str(), "",
                2.6138e-01),
      deltaBkgPdf(("deltaBkgPdf_" + std::to_string(uniqueId)).c_str(), "",
                  config.deltaMass, deltaBkgThreshold, deltaBkgC, deltaBkgA,
                  deltaBkgB),
      // N_Bkg(8000),
      N_Bkg(20000),
      N_Bu_Bkg(("N_Bu_Bkg_" + std::to_string(uniqueId)).c_str(), "", N_Bkg, 0,
               50000),
      N_Delta_Bkg(("N_Delta_Bkg_" + std::to_string(uniqueId)).c_str(), "",
                  N_Bkg, 0, 50000),
      buFunctions(("buFunctions_" + std::to_string(uniqueId)).c_str()),
      buYields(("buYields_" + std::to_string(uniqueId)).c_str()),
      deltaFunctions(("deltaFunctions_" + std::to_string(uniqueId)).c_str()),
      deltaYields(("deltaYields_" + std::to_string(uniqueId)).c_str()),
      buAddPdf(nullptr),
      deltaAddPdf(nullptr),
      simPdf(nullptr),
      sigPdf2D(("sigPdf2D_" + std::to_string(uniqueId)).c_str(), "",
               RooArgSet(buPdf, deltaPdf)),
      N_Sig2D(("N_Sig2D_" + std::to_string(uniqueId)).c_str(), "", N_Sig, 0,
              50000),
      bkgPdf2D(("bkgPdf2D_" + std::to_string(uniqueId)).c_str(), "",
               RooArgSet(buBkgPdf, deltaBkgPdf)),
      N_Bkg2D(("N_Bkg2D_" + std::to_string(uniqueId)).c_str(), "", N_Bkg, 0,
              50000),
      functions2D(("functions2D_" + std::to_string(uniqueId)).c_str()),
      yields2D(("yields2D_" + std::to_string(uniqueId)).c_str()),
      pdf2D(nullptr) {
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

  buAddPdf = std::unique_ptr<RooAddPdf>(
      new RooAddPdf(("buAddPdf_" + std::to_string(uniqueId)).c_str(), "",
                    buFunctions, buYields));

  if (config.fit1D == false) {
    deltaAddPdf = std::unique_ptr<RooAddPdf>(
        new RooAddPdf(("deltaAddPdf_" + std::to_string(uniqueId)).c_str(), "",
                      deltaFunctions, deltaYields));
    simPdf = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
        ("simPdf_" + std::to_string(uniqueId)).c_str(), "", config.fitting));
    simPdf->addPdf(*buAddPdf, EnumToString(Mass::bu).c_str());
    simPdf->addPdf(*deltaAddPdf, EnumToString(Mass::delta).c_str());
  }

  functions2D.add(sigPdf2D);
  functions2D.add(bkgPdf2D);
  yields2D.add(N_Sig2D);
  yields2D.add(N_Bkg2D);
  pdf2D = std::unique_ptr<RooAddPdf>(
      new RooAddPdf(("pdf2D_" + std::to_string(uniqueId)).c_str(), "",
                    functions2D, yields2D));
}
