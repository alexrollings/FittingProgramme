#include "GlobalVars.h"
#include "NeutralVars.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : Bu2Dst0h_D0pi0_meanDelta_(("Bu2Dst0h_D0pi0_meanDelta_" +
                                 ComposeName(uniqueId, Neutral::pi0))
                                    .c_str(),
                                "", 1.4243e+02),
      Bu2Dst0h_D0pi0_sigmaDelta_(("Bu2Dst0h_D0pi0_sigmaDelta_" +
                                  ComposeName(uniqueId, Neutral::pi0))
                                     .c_str(),
                                 "", 1.6683e+00),
      Bu2Dst0h_D0pi0_a1Delta_(("Bu2Dst0h_D0pi0_a1Delta_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", 1.3221e+00),
      Bu2Dst0h_D0pi0_a2Delta_(("Bu2Dst0h_D0pi0_a2Delta_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", -6.7992e-01),
      Bu2Dst0h_D0pi0_n1Delta_(("Bu2Dst0h_D0pi0_n1Delta_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", 7.8134e-01),
      Bu2Dst0h_D0pi0_n2Delta_(("Bu2Dst0h_D0pi0_n2Delta_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", 1.0000e+01),
      pdf1Delta_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2Dst0h_D0pi0_meanDelta_,
          Bu2Dst0h_D0pi0_sigmaDelta_, Bu2Dst0h_D0pi0_a1Delta_,
          Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2Dst0h_D0pi0_meanDelta_,
          Bu2Dst0h_D0pi0_sigmaDelta_, Bu2Dst0h_D0pi0_a2Delta_,
          Bu2Dst0h_D0pi0_n2Delta_),
      Bu2Dst0h_D0pi0_fracPdf1Delta_(("Bu2Dst0h_D0pi0_fracPdf1Delta_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    "", 2.1715e-01),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          Bu2Dst0h_D0pi0_fracPdf1Delta_),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_,
                                                    pdf2Delta_Bu2Dst0h_D0pi0_),
                                     Bu2Dst0h_D0pi0_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_meanBu_(("Bu2Dst0h_D0pi0_meanBu_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 5.2735e+03),
      relativeBuWidth_Bu2Dst0h_D0pi0_(("relativeBuWidth_Bu2Dst0h_D0pi0Bu_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      "", 0.95),
      Bu2Dst0h_D0pi0_a1Bu_(("Bu2Dst0h_D0pi0_a1Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 1.5497e+00),
      Bu2Dst0h_D0pi0_a2Bu_(("Bu2Dst0h_D0pi0_a2Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", -1.9542e+00),
      Bu2Dst0h_D0pi0_n1Bu_(("Bu2Dst0h_D0pi0_n1Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 2.8327e+00),
      Bu2Dst0h_D0pi0_n2Bu_(("Bu2Dst0h_D0pi0_n2Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 1.0000e+01),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(("Bu2Dst0h_D0pi0_fracPdf1Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 2.0967e-01),
      orEffBu2Dst0h_D0pi0_(("orEffBu2Dst0h_D0pi0_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 1),
      boxEffBu2Dst0h_D0pi0_(("boxEffBu2Dst0h_D0pi0_" +
                             ComposeName(uniqueId, Neutral::pi0))
                                .c_str(),
                            "", 1),
      buDeltaCutEffBu2Dst0h_D0pi0_(("buDeltaCutEffBu2Dst0h_D0pi0_" +
                                    ComposeName(uniqueId, Neutral::pi0))
                                       .c_str(),
                                   "", 1),
      deltaCutEffBu2Dst0h_D0pi0_(("deltaCutEffBu2Dst0h_D0pi0_" +
                                  ComposeName(uniqueId, Neutral::pi0))
                                     .c_str(),
                                 "", 1),
      fracBu2Dst0h_D0pi0_(),
      initYieldFAVBu2Dst0h_D0pi0_(Configuration::Get().initYieldFAVSignal()),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_meanDelta_(),
      Bu2Dst0h_D0gamma_sigmaDelta_(),
      Bu2Dst0h_D0gamma_a1Delta_(),
      Bu2Dst0h_D0gamma_a2Delta_(),
      Bu2Dst0h_D0gamma_n1Delta_(),
      Bu2Dst0h_D0gamma_n2Delta_(),
      pdf1Delta_Bu2Dst0h_D0gamma_(),
      pdf2Delta_Bu2Dst0h_D0gamma_(),
      Bu2Dst0h_D0gamma_fracPdf1Delta_(),
      Bu2Dst0h_D0gamma_thresholdDelta_(("Bu2Dst0h_D0gamma_thresholdDelta_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", 1.5483e+02),
      Bu2Dst0h_D0gamma_aDelta_(("Bu2Dst0h_D0gamma_aDelta_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", 1.8432e-01),
      Bu2Dst0h_D0gamma_bDelta_(("Bu2Dst0h_D0gamma_bDelta_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", -9.9920e-01),
      Bu2Dst0h_D0gamma_cDelta_(("Bu2Dst0h_D0gamma_cDelta_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", 1.3164e+01),
      pdfDelta_Bu2Dst0h_D0gamma_(new RooDstD0BG(
          ("pdfDelta_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          Bu2Dst0h_D0gamma_thresholdDelta_, Bu2Dst0h_D0gamma_cDelta_,
          Bu2Dst0h_D0gamma_aDelta_, Bu2Dst0h_D0gamma_bDelta_)),
      pdfDelta_misId_Bu2Dst0h_D0gamma_(new RooDstD0BG(
          ("pdfDelta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          Bu2Dst0h_D0gamma_thresholdDelta_, Bu2Dst0h_D0gamma_cDelta_,
          Bu2Dst0h_D0gamma_aDelta_, Bu2Dst0h_D0gamma_bDelta_)),
      Bu2Dst0h_D0gamma_meanBu_(("Bu2Dst0h_D0gamma_meanBu_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", 5.2871e+03),
      relativeBuWidth1_Bu2Dst0h_D0gamma_(
          ("relativeBuWidth1_Bu2Dst0h_D0gammaBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 0.95),
      Bu2Dst0h_D0gamma_a1Bu_(("Bu2Dst0h_D0gamma_a1Bu_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 5.5196e-02),
      Bu2Dst0h_D0gamma_a2Bu_(("Bu2Dst0h_D0gamma_a2Bu_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 6.7200e-03),
      Bu2Dst0h_D0gamma_n1Bu_(),
      Bu2Dst0h_D0gamma_n2Bu_(),
      Bu2Dst0h_D0gamma_fracPdf1Bu_(),
      orEffBu2Dst0h_D0gamma_(("orEffBu2Dst0h_D0gamma_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 1),
      boxEffBu2Dst0h_D0gamma_(("boxEffBu2Dst0h_D0gamma_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", 1),
      buDeltaCutEffBu2Dst0h_D0gamma_(("buDeltaCutEffBu2Dst0h_D0gamma_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     "", 1),
      deltaCutEffBu2Dst0h_D0gamma_(("deltaCutEffBu2Dst0h_D0gamma_" +
                                    ComposeName(uniqueId, Neutral::pi0))
                                       .c_str(),
                                   "", 1),
      fracBu2Dst0h_D0gamma_(0.207),
      initYieldFAVBu2Dst0h_D0gamma_(Configuration::Get().initYieldFAVSignal() *
                                    fracBu2Dst0h_D0gamma_),
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(("MisRec_thresholdDelta_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", 1.3549e+02),
      MisRec_aDelta_(
          ("MisRec_aDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", -3.0172e+00),  //-1.9133e+00),
      MisRec_bDelta_(
          ("MisRec_bDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 1.3412e-01),  // 2.2134e-01),
      MisRec_cDelta_(
          ("MisRec_cDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 2.0952e+00),  // 2.0917e+00),
      pdfDelta_MisRec_(
          ("pdfDelta_MisRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", Configuration::Get().deltaMass(), MisRec_thresholdDelta_,
          MisRec_cDelta_, MisRec_aDelta_, MisRec_bDelta_),
      pdfDelta_misId_MisRec_(("pdfDelta_misId_MisRec_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", Configuration::Get().deltaMass(),
                             MisRec_thresholdDelta_, MisRec_cDelta_,
                             MisRec_aDelta_, MisRec_bDelta_),
      MisRec_meanBu_(
          ("MisRec_meanBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 5.2752e+03, 5250, 5280), //5.2706e+03),
      MisRec_aLBu_(
          ("MisRec_aLBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          2.7833e-12, 0, 5),  // 1.7996e-02),
      MisRec_aRBu_(
          ("MisRec_aRBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          9.9877e-03),  // 7.1729e-02),
      orEffMisRec_(
          ("orEffMisRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      boxEffMisRec_(
          ("boxEffMisRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      buDeltaCutEffMisRec_(("buDeltaCutEffMisRec_" +
                            ComposeName(uniqueId, Neutral::gamma))
                               .c_str(),
                           "", 1),
      deltaCutEffMisRec_(("deltaCutEffMisRec_" +
                          ComposeName(uniqueId, Neutral::gamma))
                             .c_str(),
                         "", 1),
      fracMisRec_Bu2Dst0h_D0gamma_WN_(0.461),
      fracMisRec_Bu2Dst0h_D0pi0_WN_(2.71),
      fracMisRec_Bu2D0hst_(0.944),
      fracMisRec_Bd2Dsth_(0.486),
      fracMisRec_(fracMisRec_Bu2Dst0h_D0gamma_WN_ +
                  fracMisRec_Bu2Dst0h_D0pi0_WN_ + fracMisRec_Bu2D0hst_ +
                  fracMisRec_Bd2Dsth_),
      initYieldFAVMisRec_(Configuration::Get().initYieldFAVSignal() *
                          fracMisRec_),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_thresholdDelta_(("Bu2D0h_thresholdDelta_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 1.3362e+02),
      Bu2D0h_aDelta_(
          ("Bu2D0h_aDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          -6.1787e-01),
      Bu2D0h_bDelta_(
          ("Bu2D0h_bDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          9.9982e-01),
      Bu2D0h_cDelta_(
          ("Bu2D0h_cDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          3.3662e+00),
      pdfDelta_Bu2D0h_(
          ("pdfDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      pdfDelta_misId_Bu2D0h_(("pdfDelta_misId_Bu2D0h_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", Configuration::Get().deltaMass(),
                             Bu2D0h_thresholdDelta_, Bu2D0h_cDelta_,
                             Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      Bu2D0h_meanBu_(
          ("Bu2D0h_meanBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          5.4893e+03),  // 5.5263e+03),
      relativeBuWidth_Bu2D0h_(("relativeBuWidth_Bu2D0hBu_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", 0.95),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          1.3673e-01),  // 3.1698e-02),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          5.0076e-08),  // 8.2540e-04),
      orEffBu2D0h_(
          ("orEffBu2D0h_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          1),
      boxEffBu2D0h_(
          ("boxEffBu2D0h_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          1),
      buDeltaCutEffBu2D0h_(("buDeltaCutEffBu2D0h_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 1),
      deltaCutEffBu2D0h_(
          ("deltaCutEffBu2D0h_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", 1),
      fracBu2D0h_(1.37),
      initYieldFAVBu2D0h_(Configuration::Get().initYieldFAVSignal() *
                          fracBu2D0h_) {
  SetEfficiencies(Mode::Bu2Dst0pi_D0gamma, orEffBu2Dst0h_D0gamma_,
                  boxEffBu2Dst0h_D0gamma_, buDeltaCutEffBu2Dst0h_D0gamma_,
                  deltaCutEffBu2Dst0h_D0gamma_);
  // std::cout << "\t orEffBu2Dst0h_D0gamma = "
  //           << orEffBu2Dst0h_D0gamma_.getVal() << "\n"
  //           << "\t boxEffBu2Dst0h_D0gamma = "
  //           << boxEffBu2Dst0h_D0gamma_.getVal() << "\n"
  //           << "\t buDeltaCutEffBu2Dst0h_D0gamma = "
  //           << buDeltaCutEffBu2Dst0h_D0gamma_.getVal() << "\n"
  //           << "\t deltaCutEffBu2Dst0h_D0gamma = "
  //           << deltaCutEffBu2Dst0h_D0gamma_.getVal() << "\n";

  SetEfficiencies(Mode::Bu2Dst0pi_D0pi0, orEffBu2Dst0h_D0pi0_,
                  boxEffBu2Dst0h_D0pi0_, buDeltaCutEffBu2Dst0h_D0pi0_,
                  deltaCutEffBu2Dst0h_D0pi0_);
  // std::cout << "\t orEffBu2Dst0h_D0pi0 = "
  //           << orEffBu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t boxEffBu2Dst0h_D0pi0 = "
  //           << boxEffBu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t buDeltaCutEffBu2Dst0h_D0pi0 = "
  //           << buDeltaCutEffBu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t deltaCutEffBu2Dst0h_D0pi0 = "
  //           << deltaCutEffBu2Dst0h_D0pi0_.getVal() << "\n";
  //
  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN, fracMisRec_Bu2Dst0h_D0pi0_WN_ / fracMisRec_},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       fracMisRec_Bu2Dst0h_D0gamma_WN_ / fracMisRec_},
      {Mode::Bu2D0rho, fracMisRec_Bu2D0hst_ / fracMisRec_},
      {Mode::Bd2Dstpi, fracMisRec_Bd2Dsth_ / fracMisRec_}};

  double orEffMisRecVal = 0.0;
  double boxEffMisRecVal = 0.0;
  double buDeltaCutEffMisRecVal = 0.0;
  double deltaCutEffMisRecVal = 0.0;

  for (auto &m : misRecModesMap) {
    RooRealVar orEffTemp(
        ("orEffTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "", 1);
    RooRealVar boxEffTemp(
        ("boxEffTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "", 1);
    RooRealVar buDeltaCutEffTemp(
        ("buDeltaCutEffTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
        1);
    RooRealVar deltaCutEffTemp(
        ("deltaCutEffTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
        1);

    SetEfficiencies(m.first, orEffTemp, boxEffTemp, buDeltaCutEffTemp,
                    deltaCutEffTemp);

    orEffMisRecVal += orEffTemp.getVal() * m.second;
    boxEffMisRecVal += boxEffTemp.getVal() * m.second;
    buDeltaCutEffMisRecVal += buDeltaCutEffTemp.getVal() * m.second;
    deltaCutEffMisRecVal += deltaCutEffTemp.getVal() * m.second;
  }
  orEffMisRec_.setVal(orEffMisRecVal);
  boxEffMisRec_.setVal(boxEffMisRecVal);
  buDeltaCutEffMisRec_.setVal(buDeltaCutEffMisRecVal);
  deltaCutEffMisRec_.setVal(deltaCutEffMisRecVal);
  // std::cout << "\t orEffMisRec = " << orEffMisRec_.getVal() << "\n"
  //           << "\t boxEffMisRec = " << boxEffMisRec_.getVal() << "\n"
  //           << "\t buDeltaCutEffMisRec = " << buDeltaCutEffMisRec_.getVal()
  //           << "\n"
  //           << "\t deltaCutEffMisRec = " << deltaCutEffMisRec_.getVal() <<
  //           "\n";

  SetEfficiencies(Mode::Bu2D0pi, orEffBu2D0h_, boxEffBu2D0h_,
                  buDeltaCutEffBu2D0h_, deltaCutEffBu2D0h_);
  // std::cout << "\t orEffBu2D0h = " << orEffBu2D0h_.getVal() << "\n"
  //           << "\t boxEffBu2D0h = " << boxEffBu2D0h_.getVal() << "\n"
  //           << "\t buDeltaCutEffBu2D0h = " << buDeltaCutEffBu2D0h_.getVal()
  //           << "\n"
  //           << "\t deltaCutEffBu2D0h = " << deltaCutEffBu2D0h_.getVal()
  //           << "\n";
}
