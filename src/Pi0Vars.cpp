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
                                // "", 1.4243e+02),
                                "", 1.4243e+02, 138, 146),
      Bu2Dst0h_D0pi0_sigmaDelta_(("Bu2Dst0h_D0pi0_sigmaDelta_" +
                                  ComposeName(uniqueId, Neutral::pi0))
                                     .c_str(),
                                 // "", 1.6683e+00),
                                 "", 1.6683e+00, 0.1, 3),
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
                             // "", 5.2735e+03, 5270, 5275),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(("Bu2Dst0h_D0pi0_KpiSigmaBu_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      "", 0.95),
                                      // "", 0.95, 0.5, 1.5),
      Bu2Dst0h_D0pi0_a1Bu_(("Bu2Dst0h_D0pi0_a1Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 7.9192e-01),
                           // "", 1.5497e+00),
                           // "", 1.5497e+00, 0, 5),
      Bu2Dst0h_D0pi0_a2Bu_(("Bu2Dst0h_D0pi0_a2Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", -1.9542e+00),
      Bu2Dst0h_D0pi0_n1Bu_(("Bu2Dst0h_D0pi0_n1Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 10),//2.8327e+00, 0, 10),
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
                               "", 5.2857e+03),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(
          ("Bu2Dst0h_D0gamma_KpiSigmaBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 0.95),
      Bu2Dst0h_D0gamma_a1Bu_(("Bu2Dst0h_D0gamma_a1Bu_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 1.0099e-01),
      Bu2Dst0h_D0gamma_a2Bu_(("Bu2Dst0h_D0gamma_a2Bu_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 1.5557e-02),
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
      fracBu2Dst0h_D0gamma_(0.213),
      initYieldFAVBu2Dst0h_D0gamma_(Configuration::Get().initYieldFAVSignal() *
                                    fracBu2Dst0h_D0gamma_),
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(("MisRec_thresholdDelta_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", 1.3549e+02),
      MisRec_aDelta_(
          ("MisRec_aDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", -1.5314e+00),
      MisRec_bDelta_(
          ("MisRec_bDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 4.3675e-03),
      MisRec_cDelta_(
          ("MisRec_cDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 2.1071e+00),
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
          "", 5.2811e+03),//, 5220, 5320),
      MisRec_aLBu_(
          ("MisRec_aLBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          4.4348e-02),
      MisRec_aRBu_(
          ("MisRec_aRBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          5.6521e-02),
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
      fracMisRec_Bu2Dst0h_D0gamma_(0.213),
      fracMisRec_Bu2Dst0h_D0gamma_WN_(0.481),
      fracMisRec_Bu2Dst0h_D0pi0_WN_(2.722),
      fracMisRec_Bu2D0hst_(1.083),
      fracMisRec_Bd2Dsth_(0.491),
      fracMisRec_(fracMisRec_Bu2Dst0h_D0gamma_WN_ +
                  fracMisRec_Bu2Dst0h_D0pi0_WN_ + fracMisRec_Bu2D0hst_ +
                  fracMisRec_Bd2Dsth_ + fracMisRec_Bu2Dst0h_D0gamma_),
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
          // 5.4893e+03),
          5.4633e+03),
          // 5.4893e+03, 5450, 5500),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          1.3673e-01),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          5.0076e-08),
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
      fracBu2D0h_(1.363),
      initYieldFAVBu2D0h_(Configuration::Get().initYieldFAVSignal() *
                          fracBu2D0h_),
      // -------------------- PART REC -------------------- //
      partRec_thresholdDelta_(("partRec_thresholdDelta_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", 1.3596e+02),
      partRec_aDelta_(("partRec_aDelta_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", -4.1649e-01),
      partRec_bDelta_(("partRec_bDelta_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", -9.9944e-01),
      partRec_cDelta_(("partRec_cDelta_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", 2.1081e+00),
      pdfDelta_PartRec_(
          ("pdfDelta_PartRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          partRec_thresholdDelta_, partRec_cDelta_,
          partRec_aDelta_, partRec_bDelta_),
      pdfDelta_misId_PartRec_(("pdfDelta_misId_PartRec_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       partRec_thresholdDelta_,
                                       partRec_cDelta_,
                                       partRec_aDelta_,
                                       partRec_bDelta_),
      partRec_D0pi0_meanBu_(("partRec_D0pi0_meanBu_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               // "", 5.1162e+03),
                               "", 5.1300e+03),
                               // "", 5.1162e+03, 5090, 5130),
      partRec_D0pi0_aLBu_(("partRec_D0pi0_aLBu_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 4.7967e-07),
      partRec_D0pi0_aRBu_(("partRec_D0pi0_aRBu_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 1.7013e-07),
      partRec_D0gamma_meanBu_(),
      partRec_D0gamma_aLBu_(),
      partRec_D0gamma_aRBu_(),
      orEffPartRec_(("orEffPartRec_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 1),
      boxEffPartRec_(("boxEffPartRec_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", 1),
      buDeltaCutEffPartRec_(("buDeltaCutEffPartRec_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     "", 1),
      deltaCutEffPartRec_(("deltaCutEffPartRec_" +
                                    ComposeName(uniqueId, Neutral::pi0))
                                       .c_str(),
                                   "", 1),
      fracPartRec_Bu2Dst0hst_D0pi0_(),
      fracPartRec_Bu2Dst0hst_D0gamma_(),
      fracPartRec_(0.290),
      initYieldFAVPartRec_(Configuration::Get().initYieldFAVSignal() *
                                    fracPartRec_) {

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
      {Mode::Bu2Dst0pi_D0gamma,
       fracMisRec_Bu2Dst0h_D0gamma_ / fracMisRec_},
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
  SetEfficiencies(Mode::Bu2Dst0rho_D0pi0, orEffPartRec_,
                  boxEffPartRec_, buDeltaCutEffPartRec_,
                  deltaCutEffPartRec_);
  // std::cout << "\t orEffPartRec = "
  //           << orEffPartRec_.getVal() << "\n"
  //           << "\t boxEffPartRec = "
  //           << boxEffPartRec_.getVal() << "\n"
  //           << "\t buDeltaCutEffPartRec = "
  //           << buDeltaCutEffPartRec_.getVal() << "\n"
  //           << "\t deltaCutEffPartRec = "
  //           << deltaCutEffPartRec_.getVal() << "\n";
}
