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
                                  "", 1.4278e+02, 130, 150),
      // Fixed from data
      // "", 1.4199e+02),
      Bu2Dst0h_D0gamma_sigmaDelta_(("Bu2Dst0h_D0gamma_sigmaDelta_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 8.4695e+00, 2, 15),
      // Fixed from data
      // "", 8.2647e+00),
      Bu2Dst0h_D0gamma_a1Delta_(("Bu2Dst0h_D0gamma_a1Delta_" +
                                 ComposeName(uniqueId, Neutral::gamma))
                                    .c_str(),
                                // "", 1.6945e+00, 0, 5),
                                // Fixed from data
                                "", 1.8330e+00),
      Bu2Dst0h_D0gamma_a2Delta_(("Bu2Dst0h_D0gamma_a2Delta_" +
                                 ComposeName(uniqueId, Neutral::gamma))
                                    .c_str(),
                                // "", -7.4455e-01, -5, -0.00001),
                                // Fixed from data
                                "", -8.2296e-01),
      Bu2Dst0h_D0gamma_n1Delta_(("Bu2Dst0h_D0gamma_n1Delta_" +
                                 ComposeName(uniqueId, Neutral::gamma))
                                    .c_str(),
                                // "", 1.9181e+00, 0, 10),
                                // Fixed from data
                                "", 7.0834e-01),
      Bu2Dst0h_D0gamma_n2Delta_(("Bu2Dst0h_D0gamma_n2Delta_" +
                                 ComposeName(uniqueId, Neutral::gamma))
                                    .c_str(),
                                // "", 4.3851e+00, 0, 10),
                                // Fixed from data
                                "", 7.6330e+00),
      pdf1Delta_Bu2Dst0h_D0gamma_(("pdf1Delta_Bu2Dst0h_D0gamma_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", Configuration::Get().deltaMass(),
                                  Bu2Dst0h_D0gamma_meanDelta_,
                                  Bu2Dst0h_D0gamma_sigmaDelta_,
                                  Bu2Dst0h_D0gamma_a1Delta_,
                                  Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0gamma_(("pdf2Delta_Bu2Dst0h_D0gamma_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", Configuration::Get().deltaMass(),
                                  Bu2Dst0h_D0gamma_meanDelta_,
                                  Bu2Dst0h_D0gamma_sigmaDelta_,
                                  Bu2Dst0h_D0gamma_a2Delta_,
                                  Bu2Dst0h_D0gamma_n2Delta_),
      Bu2Dst0h_D0gamma_fracPdf1Delta_(("Bu2Dst0h_D0gamma_fracPdf1Delta_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      "", 1.5408e-01),
      Bu2Dst0h_D0gamma_thresholdDelta_(),
      Bu2Dst0h_D0gamma_aDelta_(),
      Bu2Dst0h_D0gamma_bDelta_(),
      Bu2Dst0h_D0gamma_cDelta_(),
      pdfDelta_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfDelta_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          Bu2Dst0h_D0gamma_fracPdf1Delta_)),
      pdfDelta_misId_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfDelta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          Bu2Dst0h_D0gamma_fracPdf1Delta_)),
      Bu2Dst0h_D0gamma_meanBu_(("Bu2Dst0h_D0gamma_meanBu_" +
                                ComposeName(uniqueId, Neutral::gamma))
                                   .c_str(),
                               // "", 5.2814e+03, 5275, 5285),
                               // Fixed from data
                               // "", 5.2806e+03),
                               // Fixed for partial box scan
                               "", 5.2805e+03),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(("Bu2Dst0h_D0gamma_KpiSigmaBu_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   // "", 0.95, 0.5, 1.5),
                                   // Fixed from data
                                   // "", 9.7938e-01),
                                   // Fixed for partial box scan
                                   "", 9.8591e-01),
      Bu2Dst0h_D0gamma_a1Bu_(("Bu2Dst0h_D0gamma_a1Bu_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", 1.6184e+00),
      Bu2Dst0h_D0gamma_a2Bu_(("Bu2Dst0h_D0gamma_a2Bu_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", -1.6623e+00),
      Bu2Dst0h_D0gamma_n1Bu_(("Bu2Dst0h_D0gamma_n1Bu_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", 8.6469e+00),
      Bu2Dst0h_D0gamma_n2Bu_(("Bu2Dst0h_D0gamma_n2Bu_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             // 5.2563e+00, 0, 100),
                             // Fixed from data
                             "", 10),
      Bu2Dst0h_D0gamma_fracPdf1Bu_(("Bu2Dst0h_D0gamma_fracPdf1Bu_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 6.8457e-01),
      Bu2Dst0h_D0gamma_meanBuPartial_(("Bu2Dst0h_D0gamma_meanBuPartial_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      "", 5.2600e+03),
      Bu2Dst0h_D0gamma_aBuPartial_(("Bu2Dst0h_D0gamma_aBuPartial_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 2.5357e+00),
      Bu2Dst0h_D0gamma_nBuPartial_(("Bu2Dst0h_D0gamma_nBuPartial_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 6.4103e-08),
      orEffBu2Dst0h_D0gamma_(("orEffBu2Dst0h_D0gamma_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", 1),
      boxEffBu2Dst0h_D0gamma_(("boxEffBu2Dst0h_D0gamma_" +
                               ComposeName(uniqueId, Neutral::gamma))
                                  .c_str(),
                              "", 1),
      boxPartialEffBu2Dst0h_D0gamma_(("boxPartialEffBu2Dst0h_D0gamma_" +
                                      ComposeName(uniqueId, Neutral::gamma))
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
      deltaPartialCutEffBu2Dst0h_D0gamma_(
          ("deltaPartialCutEffBu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      fracBu2Dst0h_D0gamma_(),
      initYieldFAVBu2Dst0h_D0gamma_(),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_meanDelta_(("Bu2Dst0h_D0pi0_meanDelta_" +
                                 ComposeName(uniqueId, Neutral::gamma))
                                    .c_str(),
                                "", 8.6503e+01, 70, 100),
      // Fixed from data
      // "", 8.5749e+01),
      Bu2Dst0h_D0pi0_sigmaDelta_(("Bu2Dst0h_D0pi0_sigmaDelta_" +
                                  ComposeName(uniqueId, Neutral::gamma))
                                     .c_str(),
                                 "", 9.3347e+00, 5, 15),
      // Fixed from data
      // "", 9.3347e+00),
      Bu2Dst0h_D0pi0_a1Delta_(("Bu2Dst0h_D0pi0_a1Delta_" +
                               ComposeName(uniqueId, Neutral::gamma))
                                  .c_str(),
                              // "", 4.4112e-01, 0, 5),
                              // Fixed from data
                              "", 2.8893e-01),
      Bu2Dst0h_D0pi0_a2Delta_(("Bu2Dst0h_D0pi0_a2Delta_" +
                               ComposeName(uniqueId, Neutral::gamma))
                                  .c_str(),
                              // "", -7.3381e-01, -5, -0.0001),
                              // Fixed from data
                              "", -8.7949e-01),
      Bu2Dst0h_D0pi0_n1Delta_(("Bu2Dst0h_D0pi0_n1Delta_" +
                               ComposeName(uniqueId, Neutral::gamma))
                                  .c_str(),
                              "", 10),
      Bu2Dst0h_D0pi0_n2Delta_(("Bu2Dst0h_D0pi0_n2Delta_" +
                               ComposeName(uniqueId, Neutral::gamma))
                                  .c_str(),
                              // "", 7.1853e+00, 0, 10),
                              // Fixed from data
                              "", 7.5576e+00),
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
      Bu2Dst0h_D0pi0_fracPdf1Delta_(("Bu2Dst0h_D0pi0_fracPdf1Delta_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    "", 3.0618e-01),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          Bu2Dst0h_D0pi0_fracPdf1Delta_),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_,
                                                    pdf2Delta_Bu2Dst0h_D0pi0_),
                                     Bu2Dst0h_D0pi0_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_meanBu_(("Bu2Dst0h_D0pi0_meanBu_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", 5.3454e+03),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(),
      Bu2Dst0h_D0pi0_a1Bu_(("Bu2Dst0h_D0pi0_a1Bu_" +
                            ComposeName(uniqueId, Neutral::gamma))
                               .c_str(),
                           "", 8.2093e-01),
      Bu2Dst0h_D0pi0_a2Bu_(),
      Bu2Dst0h_D0pi0_n1Bu_(("Bu2Dst0h_D0pi0_n1Bu_" +
                            ComposeName(uniqueId, Neutral::gamma))
                               .c_str(),
                           "", 1.0000e+01),
      Bu2Dst0h_D0pi0_n2Bu_(),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(),
      Bu2Dst0h_D0pi0_meanBuPartial_(("Bu2Dst0h_D0pi0_meanBuPartial_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    // "", 5.2910e+03, 5285, 5295),
                                    // Fixed from data
                                    // "", 5.2913e+03),
                                    // Fixed for partial box scan
                                    "", 5.2948e+03),
      Bu2Dst0h_D0pi0_21SigmaBuPartial_(("Bu2Dst0h_D0pi0_21SigmaBuPartial_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       // "", 1.6728, 1, 5),
                                       // Fixed from data
                                       // "", 1.2627e+00),
                                       // Fixed for partial box scan
                                       "", 2.7157e+00),
      Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(("Bu2Dst0h_D0pi0_KpiSigmaBuPartial_" +
                                         ComposeName(uniqueId, Neutral::gamma))
                                            .c_str(),
                                        // "", 0.95, 0.5, 1.5),
                                        // Fixed from data
                                        // "", 9.8758e-01),
                                        // Fixed for partial box scan
                                        "", 8.9208e-01),
      Bu2Dst0h_D0pi0_a1BuPartial_(("Bu2Dst0h_D0pi0_a1BuPartial_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", 1.2671e+00),
      Bu2Dst0h_D0pi0_a2BuPartial_(("Bu2Dst0h_D0pi0_a2BuPartial_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  // "", -4.6116e+00, -5, -0.0001),
                                  // Fixed from data
                                  "", -1.5225e+00),
      Bu2Dst0h_D0pi0_n1BuPartial_(("Bu2Dst0h_D0pi0_n1BuPartial_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", 1.0000e+01),
      Bu2Dst0h_D0pi0_n2BuPartial_(("Bu2Dst0h_D0pi0_n2BuPartial_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  // "", 3.1306e+00, 0, 10),
                                  // Fixed from data
                                  "", 2.4622e+00),
      Bu2Dst0h_D0pi0_fracPdf1BuPartial_(("Bu2Dst0h_D0pi0_fracPdf1BuPartial_" +
                                         ComposeName(uniqueId, Neutral::gamma))
                                            .c_str(),
                                        "", 6.6392e-01),
      orEffBu2Dst0h_D0pi0_(("orEffBu2Dst0h_D0pi0_" +
                            ComposeName(uniqueId, Neutral::gamma))
                               .c_str(),
                           "", 1),
      boxEffBu2Dst0h_D0pi0_(("boxEffBu2Dst0h_D0pi0_" +
                             ComposeName(uniqueId, Neutral::gamma))
                                .c_str(),
                            "", 1),
      boxPartialEffBu2Dst0h_D0pi0_(("boxPartialEffBu2Dst0h_D0pi0_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 1),
      buDeltaCutEffBu2Dst0h_D0pi0_(("buDeltaCutEffBu2Dst0h_D0pi0_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 1),
      deltaCutEffBu2Dst0h_D0pi0_(("deltaCutEffBu2Dst0h_D0pi0_" +
                                  ComposeName(uniqueId, Neutral::gamma))
                                     .c_str(),
                                 "", 1),
      deltaPartialCutEffBu2Dst0h_D0pi0_(("deltaPartialCutEffBu2Dst0h_D0pi0_" +
                                         ComposeName(uniqueId, Neutral::gamma))
                                            .c_str(),
                                        "", 1),
      fracBu2Dst0h_D0pi0_(0.871),
      initYieldFAVBu2Dst0h_D0pi0_(),
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(("MisRec_thresholdDelta_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", 5.3513e+01),
      MisRec_aDelta_(
          ("MisRec_aDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 1.1287e+00, -2, 2),
      // Fixed from data
      // "", 1.1293e+00),
      MisRec_bDelta_(
          ("MisRec_bDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", -1.5111e+00),
      MisRec_cDelta_(
          ("MisRec_cDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 3.5419e+01),
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
          // "", 5.2952e+03, 5200, 5350),
          // Fixed from data
          "", 5.3033e+03),
      MisRec_aLBu_(
          ("MisRec_aLBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          // 6.1974e-10, 0, 5),
          // Fixed from data
          9.1323e-09),
      MisRec_aRBu_(
          ("MisRec_aRBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          // 5.0687e-12, 0, 5),
          // Fixed from data
          3.6955e-02),
      MisRec_meanBuPartial_(("MisRec_meanBuPartial_" +
                             ComposeName(uniqueId, Neutral::gamma))
                                .c_str(),
                            // "", 5.3077e+03, 5200, 5350),
      // Fixed from data
      "", 5.3114e+03),
      MisRec_aLBuPartial_(("MisRec_aLBuPartial_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          "", 2.5509e-08),
      MisRec_aRBuPartial_(("MisRec_aRBuPartial_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          "", 2.0406e-02),
      orEffMisRec_(
          ("orEffMisRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      boxEffMisRec_(
          ("boxEffMisRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      boxPartialEffMisRec_(("boxPartialEffMisRec_" +
                            ComposeName(uniqueId, Neutral::gamma))
                               .c_str(),
                           "", 1),
      buDeltaCutEffMisRec_(("buDeltaCutEffMisRec_" +
                            ComposeName(uniqueId, Neutral::gamma))
                               .c_str(),
                           "", 1),
      deltaCutEffMisRec_(("deltaCutEffMisRec_" +
                          ComposeName(uniqueId, Neutral::gamma))
                             .c_str(),
                         "", 1),
      deltaPartialCutEffMisRec_(("deltaPartialCutEffMisRec_" +
                                 ComposeName(uniqueId, Neutral::gamma))
                                    .c_str(),
                                "", 1),
      fracMisRec_Bu2Dst0h_D0gamma_(),
      fracMisRec_Bu2Dst0h_D0gamma_WN_(0.628),
      fracMisRec_Bu2Dst0h_D0pi0_WN_(1.137),
      fracMisRec_Bu2D0hst_(1.481),
      fracMisRec_Bd2Dsth_(0.814),
      fracMisRec_(fracMisRec_Bu2Dst0h_D0gamma_WN_ +
                  fracMisRec_Bu2Dst0h_D0pi0_WN_ + fracMisRec_Bu2D0hst_ +
                  fracMisRec_Bd2Dsth_),
      initYieldFAVMisRec_(),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_thresholdDelta_(("Bu2D0h_thresholdDelta_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", 6.7754e+01),
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
      pdfDelta_misId_Bu2D0h_(("pdfDelta_misId_Bu2D0h_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", Configuration::Get().deltaMass(),
                             Bu2D0h_thresholdDelta_, Bu2D0h_cDelta_,
                             Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      Bu2D0h_meanBu_(
          ("Bu2D0h_meanBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          // "", 5.5269e+03, 5450, 5600),
          // Fixed from data
          "", 5.5310e+03),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          5.4892e-09),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          5.3835e-12),
      Bu2D0h_meanBuPartial_(("Bu2D0h_meanBuPartial_" +
                             ComposeName(uniqueId, Neutral::gamma))
                                .c_str(),
                            "", 5.5319e+03, 5450, 5580),
                            // Fixed from data
                            // "", 5.5429e+03),
                              // Fixed for partial box scan
                              // "", 5.5429e+03),
      Bu2D0h_aLBuPartial_(("Bu2D0h_aLBuPartial_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          "", 1.0264e-01),
      Bu2D0h_aRBuPartial_(("Bu2D0h_aRBuPartial_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          "", 2.6929e-02),
      orEffBu2D0h_(
          ("orEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      boxEffBu2D0h_(
          ("boxEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      boxPartialEffBu2D0h_(
          ("boxEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      buDeltaCutEffBu2D0h_(("buDeltaCutEffBu2D0h_" +
                            ComposeName(uniqueId, Neutral::gamma))
                               .c_str(),
                           "", 1),
      deltaCutEffBu2D0h_(("deltaCutEffBu2D0h_" +
                          ComposeName(uniqueId, Neutral::gamma))
                             .c_str(),
                         "", 1),
      deltaPartialCutEffBu2D0h_(("deltaPartialCutEffBu2D0h_" +
                                 ComposeName(uniqueId, Neutral::gamma))
                                    .c_str(),
                                "", 1),
      fracBu2D0h_(1.936),
      initYieldFAVBu2D0h_(),
      // -------------------- PART-REC -------------------- //
      partRec_thresholdDelta_(("partRec_thresholdDelta_" +
                               ComposeName(uniqueId, Neutral::gamma))
                                  .c_str(),
                              "", 5.7781e+01),
      partRec_aDelta_(
          ("partRec_aDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 5.2820e-01),
      partRec_bDelta_(
          ("partRec_bDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", -5.7835e-01),
      partRec_cDelta_(
          ("partRec_cDelta_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 9.9996e+01),
      pdfDelta_PartRec_(
          ("pdfDelta_PartRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", Configuration::Get().deltaMass(), partRec_thresholdDelta_,
          partRec_cDelta_, partRec_aDelta_, partRec_bDelta_),
      pdfDelta_misId_PartRec_(("pdfDelta_misId_PartRec_" +
                               ComposeName(uniqueId, Neutral::gamma))
                                  .c_str(),
                              "", Configuration::Get().deltaMass(),
                              partRec_thresholdDelta_, partRec_cDelta_,
                              partRec_aDelta_, partRec_bDelta_),
      partRec_D0pi0_meanBu_(("partRec_D0pi0_meanBu_" +
                             ComposeName(uniqueId, Neutral::gamma))
                                .c_str(),
                            "", 5.2050e+03),
      partRec_D0pi0_aLBu_(("partRec_D0pi0_aLBu_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          "", 4.0469e-08),
      partRec_D0pi0_aRBu_(("partRec_D0pi0_aRBu_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          "", 7.4756e-09),
      partRec_D0gamma_meanBu_(("partRec_D0gamma_meanBu_" +
                               ComposeName(uniqueId, Neutral::gamma))
                                  .c_str(),
                              "", 5.1039e+03),
      partRec_D0gamma_aLBu_(("partRec_D0gamma_aLBu_" +
                             ComposeName(uniqueId, Neutral::gamma))
                                .c_str(),
                            "", 8.6604e-02),
      partRec_D0gamma_aRBu_(("partRec_D0gamma_aRBu_" +
                             ComposeName(uniqueId, Neutral::gamma))
                                .c_str(),
                            "", 1.9894e-01),
      partRec_frac_D0pi0_(("partRec_frac_D0pi0_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          "", 3.0263e-01),
      partRec_meanBuPartial_(("partRec_meanBuPartial_" +
                              ComposeName(uniqueId, Neutral::gamma))
                                 .c_str(),
                             "", 5.1659e+03),
      partRec_aLBuPartial_(("partRec_aLBuPartial_" +
                            ComposeName(uniqueId, Neutral::gamma))
                               .c_str(),
                           "", 4.5521e-02),
      partRec_aRBuPartial_(("partRec_aRBuPartial_" +
                            ComposeName(uniqueId, Neutral::gamma))
                               .c_str(),
                           "", 1.4654e-01),
      orEffPartRec_(
          ("orEffPartRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          1),
      boxEffPartRec_(
          ("boxEffPartRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", 1),
      boxPartialEffPartRec_(("boxPartialEffPartRec_" +
                             ComposeName(uniqueId, Neutral::gamma))
                                .c_str(),
                            "", 1),
      buDeltaCutEffPartRec_(("buDeltaCutEffPartRec_" +
                             ComposeName(uniqueId, Neutral::gamma))
                                .c_str(),
                            "", 1),
      deltaCutEffPartRec_(("deltaCutEffPartRec_" +
                           ComposeName(uniqueId, Neutral::gamma))
                              .c_str(),
                          "", 1),
      deltaPartialCutEffPartRec_(("deltaPartialCutEffPartRec_" +
                                  ComposeName(uniqueId, Neutral::gamma))
                                     .c_str(),
                                 "", 1),
      fracPartRec_Bu2Dst0hst_D0gamma_(0.141),
      fracPartRec_Bu2Dst0hst_D0pi0_(0.162),
      fracPartRec_(fracPartRec_Bu2Dst0hst_D0gamma_ +
                   fracPartRec_Bu2Dst0hst_D0pi0_),
      initYieldFAVPartRec_() {
  if (Configuration::Get().splitByCharge() == true) {
    initYieldFAVBu2Dst0h_D0gamma_ =
        Configuration::Get().initYieldFAVSignal() / 2;
    initYieldFAVBu2Dst0h_D0pi0_ =
        (Configuration::Get().initYieldFAVSignal() * fracBu2Dst0h_D0pi0_) / 2;
    initYieldFAVMisRec_ =
        (Configuration::Get().initYieldFAVSignal() * fracMisRec_) / 2;
    initYieldFAVBu2D0h_ =
        (Configuration::Get().initYieldFAVSignal() * fracBu2D0h_) / 2;
    initYieldFAVPartRec_ =
        (Configuration::Get().initYieldFAVSignal() * fracPartRec_) / 2;
  } else {
    initYieldFAVBu2Dst0h_D0gamma_ = Configuration::Get().initYieldFAVSignal();
    initYieldFAVBu2Dst0h_D0pi0_ =
        Configuration::Get().initYieldFAVSignal() * fracBu2Dst0h_D0pi0_;
    initYieldFAVMisRec_ =
        Configuration::Get().initYieldFAVSignal() * fracMisRec_;
    initYieldFAVBu2D0h_ =
        Configuration::Get().initYieldFAVSignal() * fracBu2D0h_;
    initYieldFAVPartRec_ =
        Configuration::Get().initYieldFAVSignal() * fracPartRec_;
  }

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

  RooRealVar orEffTemp(
      ("orEffTemp" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "", 1);
  RooRealVar boxEffTemp(
      ("boxEffTemp" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "", 1);
  RooRealVar buDeltaCutEffTemp(
      ("buDeltaCutEffTemp" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
      1);
  RooRealVar deltaCutEffTemp(
      ("deltaCutEffTemp" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
      1);

  std::map<Mode, double> partRecModesMap = {
      {Mode::Bu2Dst0rho_D0pi0, fracPartRec_Bu2Dst0hst_D0pi0_ / fracPartRec_},
      {Mode::Bu2Dst0rho_D0gamma,
       fracPartRec_Bu2Dst0hst_D0gamma_ / fracPartRec_}};

  double orEffPartRecVal = 0.0;
  double boxEffPartRecVal = 0.0;
  double buDeltaCutEffPartRecVal = 0.0;
  double deltaCutEffPartRecVal = 0.0;

  if (Configuration::Get().fitBuPartial() == true) {
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0pi_D0gamma, Bachelor::pi, orEffBu2Dst0h_D0gamma_,
        boxEffBu2Dst0h_D0gamma_, boxPartialEffBu2Dst0h_D0gamma_,
        buDeltaCutEffBu2Dst0h_D0gamma_, deltaCutEffBu2Dst0h_D0gamma_,
        deltaPartialCutEffBu2Dst0h_D0gamma_, false);
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, orEffBu2Dst0h_D0pi0_,
        boxEffBu2Dst0h_D0pi0_, boxPartialEffBu2Dst0h_D0pi0_,
        buDeltaCutEffBu2Dst0h_D0pi0_, deltaCutEffBu2Dst0h_D0pi0_,
        deltaPartialCutEffBu2Dst0h_D0pi0_, false);
    double boxPartialEffMisRecVal = 0.0;
    double deltaPartialCutEffMisRecVal = 0.0;
    RooRealVar boxPartialEffTemp(
        ("boxPartialEffTemp" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
        "", 1);
    RooRealVar deltaPartialCutEffTemp(
        ("deltaPartialCutEffTemp" + ComposeName(uniqueId, Neutral::gamma))
            .c_str(),
        "", 1);
    for (auto &m : misRecModesMap) {
      Configuration::Get().SetEfficiencies(
          m.first, Bachelor::pi, orEffTemp, boxEffTemp, boxPartialEffTemp,
          buDeltaCutEffTemp, deltaCutEffTemp, deltaPartialCutEffTemp, false);

      orEffMisRecVal += orEffTemp.getVal() * m.second;
      boxEffMisRecVal += boxEffTemp.getVal() * m.second;
      boxPartialEffMisRecVal += boxPartialEffTemp.getVal() * m.second;
      buDeltaCutEffMisRecVal += buDeltaCutEffTemp.getVal() * m.second;
      deltaCutEffMisRecVal += deltaCutEffTemp.getVal() * m.second;
      deltaPartialCutEffMisRecVal += deltaPartialCutEffTemp.getVal() * m.second;
    }
    boxPartialEffMisRec_.setVal(boxPartialEffMisRecVal);
    deltaPartialCutEffMisRec_.setVal(deltaPartialCutEffMisRecVal);
    Configuration::Get().SetEfficiencies(
        Mode::Bu2D0pi, Bachelor::pi, orEffBu2D0h_, boxEffBu2D0h_,
        boxPartialEffBu2D0h_, buDeltaCutEffBu2D0h_, deltaCutEffBu2D0h_,
        deltaPartialCutEffBu2D0h_, false);
    double boxPartialEffPartRecVal = 0.0;
    double deltaPartialCutEffPartRecVal = 0.0;
    for (auto &m : partRecModesMap) {
      Configuration::Get().SetEfficiencies(
          m.first, Bachelor::pi, orEffTemp, boxEffTemp, boxPartialEffTemp,
          buDeltaCutEffTemp, deltaCutEffTemp, deltaPartialCutEffTemp, false);

      orEffPartRecVal += orEffTemp.getVal() * m.second;
      boxEffPartRecVal += boxEffTemp.getVal() * m.second;
      boxPartialEffPartRecVal += boxPartialEffTemp.getVal() * m.second;
      buDeltaCutEffPartRecVal += buDeltaCutEffTemp.getVal() * m.second;
      deltaCutEffPartRecVal += deltaCutEffTemp.getVal() * m.second;
      deltaPartialCutEffPartRecVal +=
          deltaPartialCutEffTemp.getVal() * m.second;
    }
    boxPartialEffPartRec_.setVal(boxPartialEffPartRecVal);
    deltaPartialCutEffPartRec_.setVal(deltaPartialCutEffPartRecVal);
  } else {
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0pi_D0gamma, Bachelor::pi, orEffBu2Dst0h_D0gamma_,
        boxEffBu2Dst0h_D0gamma_, buDeltaCutEffBu2Dst0h_D0gamma_,
        deltaCutEffBu2Dst0h_D0gamma_, false);
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, orEffBu2Dst0h_D0pi0_,
        boxEffBu2Dst0h_D0pi0_, buDeltaCutEffBu2Dst0h_D0pi0_,
        deltaCutEffBu2Dst0h_D0pi0_, false);
    for (auto &m : misRecModesMap) {
      Configuration::Get().SetEfficiencies(m.first, Bachelor::pi, orEffTemp,
                                           boxEffTemp, buDeltaCutEffTemp,
                                           deltaCutEffTemp, false);

      orEffMisRecVal += orEffTemp.getVal() * m.second;
      boxEffMisRecVal += boxEffTemp.getVal() * m.second;
      buDeltaCutEffMisRecVal += buDeltaCutEffTemp.getVal() * m.second;
      deltaCutEffMisRecVal += deltaCutEffTemp.getVal() * m.second;
    }
    Configuration::Get().SetEfficiencies(
        Mode::Bu2D0pi, Bachelor::pi, orEffBu2D0h_, boxEffBu2D0h_,
        buDeltaCutEffBu2D0h_, deltaCutEffBu2D0h_, false);
    for (auto &m : partRecModesMap) {
      Configuration::Get().SetEfficiencies(m.first, Bachelor::pi, orEffTemp,
                                           boxEffTemp, buDeltaCutEffTemp,
                                           deltaCutEffTemp, false);

      orEffPartRecVal += orEffTemp.getVal() * m.second;
      boxEffPartRecVal += boxEffTemp.getVal() * m.second;
      buDeltaCutEffPartRecVal += buDeltaCutEffTemp.getVal() * m.second;
      deltaCutEffPartRecVal += deltaCutEffTemp.getVal() * m.second;
    }
  }
  orEffMisRec_.setVal(orEffMisRecVal);
  boxEffMisRec_.setVal(boxEffMisRecVal);
  buDeltaCutEffMisRec_.setVal(buDeltaCutEffMisRecVal);
  deltaCutEffMisRec_.setVal(deltaCutEffMisRecVal);
  orEffPartRec_.setVal(orEffPartRecVal);
  boxEffPartRec_.setVal(boxEffPartRecVal);
  buDeltaCutEffPartRec_.setVal(buDeltaCutEffPartRecVal);
  deltaCutEffPartRec_.setVal(deltaCutEffPartRecVal);

  // std::cout << "\t orEffBu2Dst0h_D0gamma = " <<
  // orEffBu2Dst0h_D0gamma_.getVal()
  //           << "\n"
  //           << "\t boxEffBu2Dst0h_D0gamma = "
  //           << boxEffBu2Dst0h_D0gamma_.getVal() << "\n"
  //           << "\t buDeltaCutEffBu2Dst0h_D0gamma = "
  //           << buDeltaCutEffBu2Dst0h_D0gamma_.getVal() << "\n"
  //           << "\t deltaCutEffBu2Dst0h_D0gamma = "
  //           << deltaCutEffBu2Dst0h_D0gamma_.getVal() << "\n"
  //           << "\t deltaPartialCutEffBu2Dst0h_D0gamma = "
  //           << deltaPartialCutEffBu2Dst0h_D0gamma_.getVal() << "\n";
  //
  // std::cout << "\t orEffBu2Dst0h_D0pi0 = " << orEffBu2Dst0h_D0pi0_.getVal()
  //           << "\n"
  //           << "\t boxEffBu2Dst0h_D0pi0 = " << boxEffBu2Dst0h_D0pi0_.getVal()
  //           << "\n"
  //           << "\t buDeltaCutEffBu2Dst0h_D0pi0 = "
  //           << buDeltaCutEffBu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t deltaCutEffBu2Dst0h_D0pi0 = "
  //           << deltaCutEffBu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t deltaPartialCutEffBu2Dst0h_D0pi0 = "
  //           << deltaPartialCutEffBu2Dst0h_D0pi0_.getVal() << "\n";
  //
  // std::cout << "\t orEffMisRec = " << orEffMisRec_.getVal() << "\n"
  //           << "\t boxEffMisRec = " << boxEffMisRec_.getVal() << "\n"
  //           << "\t buDeltaCutEffMisRec = " << buDeltaCutEffMisRec_.getVal()
  //           << "\n"
  //           << "\t deltaCutEffMisRec = " << deltaCutEffMisRec_.getVal() <<
  //           "\n";
  //
  // std::cout << "\t orEffBu2D0h = " << orEffBu2D0h_.getVal() << "\n"
  //           << "\t boxEffBu2D0h = " << boxEffBu2D0h_.getVal() << "\n"
  //           << "\t buDeltaCutEffBu2D0h = " << buDeltaCutEffBu2D0h_.getVal()
  //           << "\n"
  //           << "\t deltaCutEffBu2D0h = " << deltaCutEffBu2D0h_.getVal()
  //           << "\n";
  //
  // std::cout << "\t orEffPartRec = " << orEffPartRec_.getVal() <<
  // "\n"
  //           << "\t boxEffPartRec = " << boxEffPartRec_.getVal()
  //           << "\n"
  //           << "\t buDeltaCutEffPartRec = "
  //           << buDeltaCutEffPartRec_.getVal() << "\n"
  //           << "\t deltaCutEffPartRec = "
  //           << deltaCutEffPartRec_.getVal() << "\n";
}
