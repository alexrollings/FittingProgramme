#include "GlobalVars.h"
#include "NeutralVars.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : Bu2Dst0h_D0gamma_meanDelta_(("Bu2Dst0h_D0gamma_meanDelta_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", 1.4233e+02, 135, 150),
      Bu2Dst0h_D0gamma_sigmaDelta_(("Bu2Dst0h_D0gamma_sigmaDelta_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 8.1675e+00, 2, 15),
      Bu2Dst0h_D0gamma_a1Delta_(
          ("Bu2Dst0h_D0gamma_a1Delta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1.5109e+00),
      Bu2Dst0h_D0gamma_a2Delta_(
          ("Bu2Dst0h_D0gamma_a2Delta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", -5.7023e-01),
      Bu2Dst0h_D0gamma_n1Delta_(
          ("Bu2Dst0h_D0gamma_n1Delta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 6.0060e+00),
      Bu2Dst0h_D0gamma_n2Delta_(
          ("Bu2Dst0h_D0gamma_n2Delta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 7.8408e+00),
      pdf1Delta_Bu2Dst0h_D0gamma_(
          ("pdf1Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2Dst0h_D0gamma_meanDelta_,
          Bu2Dst0h_D0gamma_sigmaDelta_, Bu2Dst0h_D0gamma_a1Delta_,
          Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0gamma_(
          ("pdf2Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2Dst0h_D0gamma_meanDelta_,
          Bu2Dst0h_D0gamma_sigmaDelta_, Bu2Dst0h_D0gamma_a2Delta_,
          Bu2Dst0h_D0gamma_n2Delta_),
      Bu2Dst0h_D0gamma_frac1PdfDelta_(("Bu2Dst0h_D0gamma_frac1PdfDelta_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      "", 2.6638e-01),
      pdfDelta_Bu2Dst0h_D0gamma_(
          ("pdfDelta_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          Bu2Dst0h_D0gamma_frac1PdfDelta_),
      pdfDelta_misId_Bu2Dst0h_D0gamma_(
          ("pdfDelta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          Bu2Dst0h_D0gamma_frac1PdfDelta_),
      Bu2Dst0h_D0gamma_meanBu_(
          ("Bu2Dst0h_D0gamma_meanBu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 5.2819e+03, 5275, 5290),
      relativeBuWidth_Bu2Dst0h_D0gamma_(("relativeBuWidth_Bu2Dst0h_D0gammaBu_" +
                                         ComposeName(uniqueId, Neutral::gamma))
                                            .c_str(),
                                        "", 0.95),
      Bu2Dst0h_D0gamma_a1Bu_(
          ("Bu2Dst0h_D0gamma_a1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1.6184e+00),
      Bu2Dst0h_D0gamma_a2Bu_(
          ("Bu2Dst0h_D0gamma_a2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", -1.6623e+00),
      Bu2Dst0h_D0gamma_n1Bu_(
          ("Bu2Dst0h_D0gamma_n1Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 8.6469e+00),
      Bu2Dst0h_D0gamma_n2Bu_(
          ("Bu2Dst0h_D0gamma_n2Bu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 5.2563e+00),
      Bu2Dst0h_D0gamma_frac1PdfBu_(("Bu2Dst0h_D0gamma_frac1PdfBu_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 6.8457e-01),
      orEffBu2Dst0h_D0gamma_(
          ("orEffBu2Dst0h_D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      boxEffBu2Dst0h_D0gamma_(
          ("boxEffBu2Dst0h_D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      buDeltaCutEffBu2Dst0h_D0gamma_(("buDeltaCutEffBu2Dst0h_D0gamma_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     "", 1),
      deltaCutEffBu2Dst0h_D0gamma_(("deltaCutEffBu2Dst0h_D0gamma_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 1),
      initYieldFAVBu2Dst0h_D0gamma_(5.1958e+04),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_meanDelta_(
          ("Bu2Dst0h_D0pi0_meanDelta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 8.6075e+01, 80, 90),
      Bu2Dst0h_D0pi0_sigmaDelta_(
          ("Bu2Dst0h_D0pi0_sigmaDelta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 9.2845e+00, 2, 15),
      Bu2Dst0h_D0pi0_a1Delta_(
          ("Bu2Dst0h_D0pi0_a1Delta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 4.2812e-01),
      Bu2Dst0h_D0pi0_a2Delta_(
          ("Bu2Dst0h_D0pi0_a2Delta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", -7.3982e-01),
      Bu2Dst0h_D0pi0_n1Delta_(
          ("Bu2Dst0h_D0pi0_n1Delta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 9.9912e+01),
      Bu2Dst0h_D0pi0_n2Delta_(
          ("Bu2Dst0h_D0pi0_n2Delta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 7.0288e+00),
      pdf1Delta_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2Dst0h_D0pi0_meanDelta_,
          Bu2Dst0h_D0pi0_sigmaDelta_, Bu2Dst0h_D0pi0_a1Delta_,
          Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2Dst0h_D0pi0_meanDelta_,
          Bu2Dst0h_D0pi0_sigmaDelta_, Bu2Dst0h_D0pi0_a2Delta_,
          Bu2Dst0h_D0pi0_n2Delta_),
      Bu2Dst0h_D0pi0_frac1PdfDelta_(("Bu2Dst0h_D0pi0_frac1PdfDelta_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    "", 2.9911e-01),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          Bu2Dst0h_D0pi0_frac1PdfDelta_),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(
          ("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          Bu2Dst0h_D0pi0_frac1PdfDelta_),
      Bu2Dst0h_D0pi0_meanBu_(
          ("Bu2Dst0h_D0pi0_meanBu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 5.3431e+03),
      Bu2Dst0h_D0pi0_aBu_(
          ("Bu2Dst0h_D0pi0_aBu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 9.8213e-01),
      Bu2Dst0h_D0pi0_nBu_(
          ("Bu2Dst0h_D0pi0_nBu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 10),
      orEffBu2Dst0h_D0pi0_(
          ("orEffBu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      boxEffBu2Dst0h_D0pi0_(
          ("boxEffBu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      buDeltaCutEffBu2Dst0h_D0pi0_(("buDeltaCutEffBu2Dst0h_D0pi0_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 1),
      deltaCutEffBu2Dst0h_D0pi0_(
          ("deltaCutEffBu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      fracBu2Dst0h_D0pi0_(0.916),
      initYieldFAVBu2Dst0h_D0pi0_(initYieldFAVBu2Dst0h_D0gamma_ *
                                   fracBu2Dst0h_D0pi0_),
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(
          ("MisRec_thresholdDelta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 5.7223e+01),
      MisRec_aDelta_(
          ("MisRec_aDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 1.2396e+00),
      MisRec_bDelta_(
          ("MisRec_bDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", -1.7973e+00, -2, 2),
      MisRec_cDelta_(
          ("MisRec_cDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 3.1867e+01),
      pdfDelta_MisRec_(
          ("pdfDelta_MisRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", Configuration::Get().deltaMass(), MisRec_thresholdDelta_,
          MisRec_cDelta_, MisRec_aDelta_, MisRec_bDelta_),
      pdfDelta_misId_MisRec_(
          ("pdfDelta_misId_MisRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), MisRec_thresholdDelta_,
          MisRec_cDelta_, MisRec_aDelta_, MisRec_bDelta_),
      MisRec_meanBu_(
          ("MisRec_meanBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 5.2991e+03, 5290, 5310),
      MisRec_aBu_(
          ("MisRec_aBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          2.6265e+00),
      MisRec_nBu_(
          ("MisRec_nBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          9.9921e-01),
      orEffMisRec_(
          ("orEffMisRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      boxEffMisRec_(
          ("boxEffMisRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      buDeltaCutEffMisRec_(
          ("buDeltaCutEffMisRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      deltaCutEffMisRec_(
          ("deltaCutEffMisRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      fracMisRec_Bu2Dst0h_D0gamma_WN_(0.473),
      fracMisRec_Bu2Dst0h_D0pi0_WN_(0.809),
      fracMisRec_Bu2D0hst_(0.809),
      fracMisRec_Bd2Dsth_(0.643),
      fracMisRec_(fracMisRec_Bu2Dst0h_D0gamma_WN_ +
                  fracMisRec_Bu2Dst0h_D0pi0_WN_ + fracMisRec_Bu2D0hst_ +
                  fracMisRec_Bd2Dsth_),
      initYieldFAVMisRec_(initYieldFAVBu2Dst0h_D0gamma_ * fracMisRec_),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_thresholdDelta_(
          ("Bu2D0h_thresholdDelta_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 6.7773e+01),
      Bu2D0h_aDelta_(
          ("Bu2D0h_aDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 5.8996e-01),
      Bu2D0h_bDelta_(
          ("Bu2D0h_bDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", -5.6691e-01),
      Bu2D0h_cDelta_(
          ("Bu2D0h_cDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 6.2156e+01),
      pdfDelta_Bu2D0h_(
          ("pdfDelta_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      pdfDelta_misId_Bu2D0h_(
          ("pdfDelta_misId_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      Bu2D0h_meanBu_(
          ("Bu2D0h_meanBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 5.5263e+03),
      relativeBuWidth_Bu2D0h_(
          ("relativeBuWidth_Bu2D0hBu_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 0.95),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          6.7243e-09),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          2.1226e-11),
      orEffBu2D0h_(
          ("orEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      boxEffBu2D0h_(
          ("boxEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      buDeltaCutEffBu2D0h_(
          ("buDeltaCutEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      deltaCutEffBu2D0h_(
          ("deltaCutEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      fracBu2D0pi_(1.54),
      initYieldFAVBu2D0pi_(initYieldFAVBu2Dst0h_D0gamma_ * fracBu2D0pi_) {
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
