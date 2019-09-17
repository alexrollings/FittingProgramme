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
                                "", 1.4242e+02),
      Bu2Dst0h_D0pi0_sigmaDelta_(("Bu2Dst0h_D0pi0_sigmaDelta_" +
                                  ComposeName(uniqueId, Neutral::pi0))
                                     .c_str(),
                                 "", 1.6342e+00),
      Bu2Dst0h_D0pi0_a1Delta_(("Bu2Dst0h_D0pi0_a1Delta_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", 1.3383e+00),
      Bu2Dst0h_D0pi0_a2Delta_(("Bu2Dst0h_D0pi0_a2Delta_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", -6.0072e-01),
      Bu2Dst0h_D0pi0_n1Delta_(("Bu2Dst0h_D0pi0_n1Delta_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", 9.8320e-01),
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
      Bu2Dst0h_D0pi0_frac1PdfDelta_(("Bu2Dst0h_D0pi0_frac1PdfDelta_" +
                                     ComposeName(uniqueId, Neutral::pi0))
                                        .c_str(),
                                    "", 2.9077e-01),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          Bu2Dst0h_D0pi0_frac1PdfDelta_),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_,
                                                    pdf2Delta_Bu2Dst0h_D0pi0_),
                                     Bu2Dst0h_D0pi0_frac1PdfDelta_),
      Bu2Dst0h_D0pi0_meanBu_(("Bu2Dst0h_D0pi0_meanBu_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 5.2719e+03),
      relativeBuWidth1_Bu2Dst0h_D0pi0_(("relativeBuWidth1_Bu2Dst0h_D0pi0Bu_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", 0.95),
      relativeBuWidth2_Bu2Dst0h_D0pi0_(("relativeBuWidth2_Bu2Dst0h_D0pi0Bu_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", 0.95),
      Bu2Dst0h_D0pi0_a1Bu_(("Bu2Dst0h_D0pi0_a1Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 9.7637e-02),
      Bu2Dst0h_D0pi0_a2Bu_(("Bu2Dst0h_D0pi0_a2Bu_" +
                            ComposeName(uniqueId, Neutral::pi0))
                               .c_str(),
                           "", 6.6662e-02),
      Bu2Dst0h_D0pi0_nBu_(),
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
      Bu2Dst0h_D0gamma_frac1PdfDelta_(),
      Bu2Dst0h_D0gamma_thresholdDelta_(("Bu2Dst0h_D0gamma_thresholdDelta_" +
                                        ComposeName(uniqueId, Neutral::pi0))
                                           .c_str(),
                                       "", 1.5593e+02),
      Bu2Dst0h_D0gamma_aDelta_(("Bu2Dst0h_D0gamma_aDelta_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", 8.9498e-02),
      Bu2Dst0h_D0gamma_bDelta_(("Bu2Dst0h_D0gamma_bDelta_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", -4.7042e-01),
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
      Bu2Dst0h_D0gamma_meanBu_(("Bu2Dst0h_D0gamma_meanBu_" +
                                ComposeName(uniqueId, Neutral::pi0))
                                   .c_str(),
                               "", 5.2871e+03),
      relativeBuWidth1_Bu2Dst0h_D0gamma_(
          ("relativeBuWidth1_Bu2Dst0h_D0gammaBu_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 0.95),
      relativeBuWidth2_Bu2Dst0h_D0gamma_(
          ("relativeBuWidth2_Bu2Dst0h_D0gammaBu_" +
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
      Bu2Dst0h_D0gamma_frac1PdfBu_(),
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
      initYieldFAVBu2Dst0h_D0gamma_(
          Configuration::Get().initYieldFAVSignal() * fracBu2Dst0h_D0gamma_),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_thresholdDelta_(("Bu2D0h_thresholdDelta_" +
                              ComposeName(uniqueId, Neutral::pi0))
                                 .c_str(),
                             "", 1.3362e+02),
      Bu2D0h_aDelta_(
          ("Bu2D0h_aDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", -6.1787e-01),
      Bu2D0h_bDelta_(
          ("Bu2D0h_bDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", 9.9982e-01),
      Bu2D0h_cDelta_(
          ("Bu2D0h_cDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", 3.3662e+00),
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
          ("Bu2D0h_meanBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", 5.5263e+03),
      relativeBuWidth_Bu2D0h_(("relativeBuWidth_Bu2D0hBu_" +
                               ComposeName(uniqueId, Neutral::pi0))
                                  .c_str(),
                              "", 0.95),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          3.1698e-02),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          8.2540e-04),
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
      deltaCutEffBu2D0h_(("deltaCutEffBu2D0h_" +
                          ComposeName(uniqueId, Neutral::pi0))
                             .c_str(),
                         "", 1),
      fracBu2D0h_(1.37),
      initYieldFAVBu2D0h_(Configuration::Get().initYieldFAVSignal() *
                          fracBu2D0h_) {
  SetEfficiencies(Mode::Bu2Dst0pi_D0pi0, orEffBu2Dst0h_D0pi0_,
                  boxEffBu2Dst0h_D0pi0_, buDeltaCutEffBu2Dst0h_D0pi0_,
                  deltaCutEffBu2Dst0h_D0pi0_);
  SetEfficiencies(Mode::Bu2Dst0pi_D0gamma, orEffBu2Dst0h_D0gamma_,
                  boxEffBu2Dst0h_D0gamma_, buDeltaCutEffBu2Dst0h_D0gamma_,
                  deltaCutEffBu2Dst0h_D0gamma_);
  SetEfficiencies(Mode::Bu2D0pi, orEffBu2D0h_,
                  boxEffBu2D0h_, buDeltaCutEffBu2D0h_,
                  deltaCutEffBu2D0h_);
}
