#include "GlobalVars.h"
#include "NeutralVars.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_meanDelta_(("Bu2Dst0h_Dst02D0gamma_meanDelta_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", 1.4233e+02, 135, 150),
      Bu2Dst0h_Dst02D0gamma_sigmaDelta_(("Bu2Dst0h_Dst02D0gamma_sigmaDelta_" +
                                         ComposeName(uniqueId, Neutral::pi0))
                                            .c_str(),
                                        "", 8.1675e+00, 2, 15),
      Bu2Dst0h_Dst02D0gamma_a1Delta_(("Bu2Dst0h_Dst02D0gamma_a1Delta_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     "", 1.5109e+00),
      Bu2Dst0h_Dst02D0gamma_a2Delta_(("Bu2Dst0h_Dst02D0gamma_a2Delta_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     "", -5.7023e-01),
      Bu2Dst0h_Dst02D0gamma_n1Delta_(("Bu2Dst0h_Dst02D0gamma_n1Delta_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     "", 6.0060e+00),
      Bu2Dst0h_Dst02D0gamma_n2Delta_(("Bu2Dst0h_Dst02D0gamma_n2Delta_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     "", 7.8408e+00),
      pdf1Delta_Bu2Dst0h_Dst02D0gamma_(("pdf1Delta_Bu2Dst0h_Dst02D0gamma_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       Bu2Dst0h_Dst02D0gamma_meanDelta_,
                                       Bu2Dst0h_Dst02D0gamma_sigmaDelta_,
                                       Bu2Dst0h_Dst02D0gamma_a1Delta_,
                                       Bu2Dst0h_Dst02D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_Dst02D0gamma_(("pdf2Delta_Bu2Dst0h_Dst02D0gamma_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       Bu2Dst0h_Dst02D0gamma_meanDelta_,
                                       Bu2Dst0h_Dst02D0gamma_sigmaDelta_,
                                       Bu2Dst0h_Dst02D0gamma_a2Delta_,
                                       Bu2Dst0h_Dst02D0gamma_n2Delta_),
      Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_(
          ("Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 2.6638e-01),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(
          ("pdfDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_Dst02D0gamma_,
                         pdf2Delta_Bu2Dst0h_Dst02D0gamma_),
          Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_),
      Bu2Dst0h_Dst02D0gamma_meanBu_(("Bu2Dst0h_Dst02D0gamma_meanBu_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    "", 5.2819e+03, 5270, 5290),
      relativeBuWidth_Bu2Dst0h_Dst02D0gamma_(
          ("relativeBuWidth_Bu2Dst0h_Dst02D0gammaBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 0.95),
      Bu2Dst0h_Dst02D0gamma_a1Bu_(("Bu2Dst0h_Dst02D0gamma_a1Bu_" +
                                   ComposeName(uniqueId, Neutral::pi0))
                                      .c_str(),
                                  "", 1.6184e+00),
      Bu2Dst0h_Dst02D0gamma_a2Bu_(("Bu2Dst0h_Dst02D0gamma_a2Bu_" +
                                   ComposeName(uniqueId, Neutral::pi0))
                                      .c_str(),
                                  "", -1.6623e+00),
      Bu2Dst0h_Dst02D0gamma_n1Bu_(("Bu2Dst0h_Dst02D0gamma_n1Bu_" +
                                   ComposeName(uniqueId, Neutral::pi0))
                                      .c_str(),
                                  "", 8.6469e+00),
      Bu2Dst0h_Dst02D0gamma_n2Bu_(("Bu2Dst0h_Dst02D0gamma_n2Bu_" +
                                   ComposeName(uniqueId, Neutral::pi0))
                                      .c_str(),
                                  "", 5.2563e+00),
      Bu2Dst0h_Dst02D0gamma_frac1PdfBu_(("Bu2Dst0h_Dst02D0gamma_frac1PdfBu_" +
                                         ComposeName(uniqueId, Neutral::pi0))
                                            .c_str(),
                                        "", 6.8457e-01),
      ratioKpi_Bu2Dst0h_Dst02D0gamma_(("ratioKpi_Bu2Dst0h_Dst02D0gamma_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      "", 0.07930, -1, 1),
      orEffBu2Dst0pi_Dst02D0gamma_(("orEffBu2Dst0pi_Dst02D0gamma_" +
                                    ComposeName(uniqueId, Neutral::pi0))
                                       .c_str(),
                                   "", 1),
      boxEffBu2Dst0pi_Dst02D0gamma_(("boxEffBu2Dst0pi_Dst02D0gamma_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    "", 1),
      buDeltaCutEffBu2Dst0pi_Dst02D0gamma_(
          ("buDeltaCutEffBu2Dst0pi_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 1),
      deltaCutEffBu2Dst0pi_Dst02D0gamma_(("deltaCutEffBu2Dst0pi_Dst02D0gamma_" +
                                          ComposeName(uniqueId, Neutral::pi0))
                                             .c_str(),
                                         "", 1),
      initYieldFAVSignal_(5.1958e+04),
      MisRec_thresholdDelta_(("MisRec_thresholdDelta_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      "", 5.7223e+01),
      MisRec_aDelta_(("MisRec_aDelta_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      "", 1.2396e+00),
      MisRec_bDelta_(("MisRec_bDelta_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      "", -1.7973e+00),
      MisRec_cDelta_(("MisRec_cDelta_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      "", 3.1867e+01),
      pdfDelta_MisRec_(("pdfDelta_MisRec_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       MisRec_thresholdDelta_,
                                       MisRec_cDelta_,
                                       MisRec_aDelta_,
                                       MisRec_bDelta_),
      MisRec_meanBu_(("MisRec_meanBu_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    "", 5.2991e+03),
      MisRec_aBu_(("MisRec_aBu_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    "", 2.6265e+00),
      MisRec_nBu_(("MisRec_nBu_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    "", 9.9921e-01),
      ratioKpi_MisRec_(("ratioKpi_MisRec_" +
                                       ComposeName(uniqueId, Neutral::pi0))
                                          .c_str(),
                                      "", 0.06, -1, 1),
      orEffMisRec_(("orEffMisRec_" +
                                    ComposeName(uniqueId, Neutral::pi0))
                                       .c_str(),
                                   "", 1),
      boxEffMisRec_(("boxEffMisRec_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    "", 1),
      buDeltaCutEffMisRec_(
          ("buDeltaCutEffMisRec_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 1),
      deltaCutEffMisRec_(("deltaCutEffMisRec_" +
                                          ComposeName(uniqueId, Neutral::pi0))
                                             .c_str(),
                                         "", 1),
      fracMisRec_Bu2Dst0pi_Dst02D0gamma_WN_(0.473),
      fracMisRec_Bu2Dst0pi_Dst02D0pi0_WN_(0.809),
      fracMisRec_Bu2D0rho_(0.809),
      fracMisRec_Bd2Dstpi_(0.643),
      fracMisRec_(fracMisRec_Bu2Dst0pi_Dst02D0gamma_WN_ +
                          fracMisRec_Bu2Dst0pi_Dst02D0pi0_WN_ +
                          fracMisRec_Bu2D0rho_ + fracMisRec_Bd2Dstpi_),
      initYieldFAVMisRec_(initYieldFAVSignal_*fracMisRec_) {
  SetEfficiencies(Mode::Bu2Dst0pi_D0gamma, orEffBu2Dst0pi_Dst02D0gamma_,
                  boxEffBu2Dst0pi_Dst02D0gamma_,
                  buDeltaCutEffBu2Dst0pi_Dst02D0gamma_,
                  deltaCutEffBu2Dst0pi_Dst02D0gamma_);
  std::cout << "\t orEffBu2Dst0pi_Dst02D0gamma = "
            << orEffBu2Dst0pi_Dst02D0gamma_.getVal() << "\n"
            << "\t boxEffBu2Dst0pi_Dst02D0gamma = "
            << boxEffBu2Dst0pi_Dst02D0gamma_.getVal() << "\n"
            << "\t buDeltaCutEffBu2Dst0pi_Dst02D0gamma = "
            << buDeltaCutEffBu2Dst0pi_Dst02D0gamma_.getVal() << "\n"
            << "\t deltaCutEffBu2Dst0pi_Dst02D0gamma = "
            << deltaCutEffBu2Dst0pi_Dst02D0gamma_.getVal() << "\n";

  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN,
       fracMisRec_Bu2Dst0pi_Dst02D0pi0_WN_ / fracMisRec_},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       fracMisRec_Bu2Dst0pi_Dst02D0gamma_WN_ / fracMisRec_},
      {Mode::Bu2D0rho, fracMisRec_Bu2D0rho_ / fracMisRec_},
      {Mode::Bd2Dstpi, fracMisRec_Bd2Dstpi_ / fracMisRec_}};

  double orEffMisRecVal = 0.0;
  double boxEffMisRecVal = 0.0;
  double buDeltaCutEffMisRecVal = 0.0;
  double deltaCutEffMisRecVal = 0.0;

  for (auto &m : misRecModesMap) {
    RooRealVar orEffTemp("orEffTemp", "", 1);
    RooRealVar boxEffTemp("boxEffTemp", "", 1);
    RooRealVar buDeltaCutEffTemp("buDeltaCutEffTemp", "", 1);
    RooRealVar deltaCutEffTemp("deltaCutEffTemp", "", 1);

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
  std::cout << "\t orEffMisRec = " << orEffMisRec_.getVal() << "\n"
            << "\t boxEffMisRec = " << boxEffMisRec_.getVal() << "\n"
            << "\t buDeltaCutEffMisRec = " << buDeltaCutEffMisRec_.getVal()
            << "\n"
            << "\t deltaCutEffMisRec = " << deltaCutEffMisRec_.getVal() << "\n";
}
