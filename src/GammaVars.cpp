#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : Bu2Dst0h_D0gamma_meanDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0gamma_meanDelta", uniqueId,
                                       Neutral::gamma, 1.4278e+02, 130, 150)),
      Bu2Dst0h_D0gamma_sigmaDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0gamma_sigmaDelta", uniqueId,
                                       Neutral::gamma, 8.4695e+00, 2, 15)),
      Bu2Dst0h_D0gamma_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Delta", uniqueId, Neutral::gamma, 1.8071e+00,
          5.56e-02, Systematic::gammaDeltaTails, Sign::positive)),
      Bu2Dst0h_D0gamma_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Delta", uniqueId, Neutral::gamma, -8.2414e-01,
          1.45e-02, Systematic::gammaDeltaTails, Sign::negative)),
      Bu2Dst0h_D0gamma_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n1Delta", uniqueId, Neutral::gamma, 6.5004e-01,
          1.74e-01, Systematic::gammaDeltaTails, Sign::positive)),
      Bu2Dst0h_D0gamma_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n2Delta", uniqueId, Neutral::gamma, 8.8324e+00,
          2.10e+00, Systematic::gammaDeltaTails, Sign::positive)),
      pdf1Delta_Bu2Dst0h_D0gamma_(
          ("pdf1Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_sigmaDelta_, *Bu2Dst0h_D0gamma_a1Delta_,
          *Bu2Dst0h_D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0gamma_(
          ("pdf2Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0gamma_meanDelta_,
          *Bu2Dst0h_D0gamma_sigmaDelta_, *Bu2Dst0h_D0gamma_a2Delta_,
          *Bu2Dst0h_D0gamma_n2Delta_),
      Bu2Dst0h_D0gamma_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_fracPdf1Delta", uniqueId, Neutral::gamma,
          1.6339e-01, 2.75e-02, Systematic::gammaDeltaFrac, Sign::positive)),
      Bu2Dst0h_D0gamma_thresholdDelta_(nullptr),
      Bu2Dst0h_D0gamma_aDelta_(nullptr),
      Bu2Dst0h_D0gamma_bDelta_(nullptr),
      Bu2Dst0h_D0gamma_cDelta_(nullptr),
      pdfDelta_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfDelta_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          *Bu2Dst0h_D0gamma_fracPdf1Delta_)),
      pdfDelta_misId_Bu2Dst0h_D0gamma_(new RooAddPdf(
          ("pdfDelta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_D0gamma_, pdf2Delta_Bu2Dst0h_D0gamma_),
          *Bu2Dst0h_D0gamma_fracPdf1Delta_)),
      Bu2Dst0h_D0gamma_meanBu_(
          Params::Get().CreateFloating("Bu2Dst0h_D0gamma_meanBu", uniqueId,
                                       Neutral::gamma, 5.2814e+03, 5275, 5285)),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(
          Params::Get().CreateFloating("Bu2Dst0h_D0gamma_KpiSigmaBu", uniqueId,
                                       Neutral::gamma, 0.95, 0.5, 1.5)),
      Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Bu", uniqueId, Neutral::gamma, 1.5214e+00,
          3.08e-02, Systematic::gammaBuTails, Sign::positive)),
      Bu2Dst0h_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Bu", uniqueId, Neutral::gamma, -1.9560e+00,
          7.54e-02, Systematic::gammaBuTails, Sign::negative)),
      Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_n1Bu", uniqueId, Neutral::gamma, 8.6469e+00, 1e-01,
          Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0gamma_n2Bu_(
          Params::Get().CreateFixed("Bu2Dst0h_D0gamma_n2Bu", uniqueId,
                                    Neutral::gamma, 10, 1e-01, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0gamma_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_fracPdf1Bu", uniqueId, Neutral::gamma, 6.2860e-01,
          8.13e-02, Systematic::gammaBuFrac, Sign::positive)),
      Bu2Dst0h_D0gamma_meanBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_meanBuPartial", uniqueId, Neutral::gamma,
          5.2602e+03, 3.68e+00, Systematic::crossFeedBuPartialPdf, Sign::positive)),
      Bu2Dst0h_D0gamma_aBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_aBuPartial", uniqueId, Neutral::gamma, 2.5968e+00,
          3.45e-01, Systematic::crossFeedBuPartialPdf, Sign::none)),
      Bu2Dst0h_D0gamma_nBuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_nBuPartial", uniqueId, Neutral::gamma, 1.8178e-06,
          6.90e-02, Systematic::crossFeedBuPartialPdf, Sign::positive)),
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
      initYieldFAVBu2Dst0h_D0gamma_(Configuration::Get().initYieldFAVSignal()),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_meanDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0pi0_meanDelta", uniqueId,
                                       Neutral::gamma, 8.6503e+01, 70, 100)),
      Bu2Dst0h_D0pi0_sigmaDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0pi0_sigmaDelta", uniqueId,
                                       Neutral::gamma, 9.3347e+00, 5, 15)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId, Neutral::gamma, 2.9929e-01,
          3.34e-02, Systematic::pi0DeltaTails, Sign::positive)),
      Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Delta", uniqueId, Neutral::gamma, -8.4795e-01,
          2.28e-02, Systematic::pi0DeltaTails, Sign::negative)),
      // RANGE??
      Bu2Dst0h_D0pi0_n1Delta_(
          Params::Get().CreateFixed("Bu2Dst0h_D0pi0_n1Delta", uniqueId,
                                    Neutral::gamma, 10, 1e-01, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Delta", uniqueId, Neutral::gamma, 6.1823e+00,
          1.26e+00, Systematic::pi0DeltaTails, Sign::positive)),
      pdf1Delta_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_sigmaDelta_, *Bu2Dst0h_D0pi0_a1Delta_,
          *Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_sigmaDelta_, *Bu2Dst0h_D0pi0_a2Delta_,
          *Bu2Dst0h_D0pi0_n2Delta_),
      Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId, Neutral::gamma, 3.1420e-01,
          1.29e-02, Systematic::pi0DeltaFrac, Sign::positive)),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(
          ("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_meanBu", uniqueId, Neutral::gamma, 5.3423e+03,
          1.03e+00, Systematic::crossFeedBuPdf, Sign::positive)),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(nullptr),
      Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Bu", uniqueId, Neutral::gamma, 8.2132e-01, 2.77e-02,
          Systematic::crossFeedBuPdf, Sign::positive)),
      Bu2Dst0h_D0pi0_a2Bu_(nullptr),
      Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Bu", uniqueId, Neutral::gamma, 1.0000e+01, 1e+00,
          Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_n2Bu_(nullptr),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(nullptr),
      Bu2Dst0h_D0pi0_meanCbBuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanCbBuPartial", uniqueId, Neutral::gamma,
          5.2848e+03, 5280, 5290)),
      Bu2Dst0h_D0pi0_meanOffsetGausBuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanOffsetGausBuPartial", uniqueId, Neutral::gamma,
          2.8656e+01, 10, 50)),
      Bu2Dst0h_D0pi0_meanGausBuPartial_(
          ("Bu2Dst0h_D0pi0_meanGausBuPartial_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "@0+@1",
          RooArgSet(*Bu2Dst0h_D0pi0_meanCbBuPartial_,
                    *Bu2Dst0h_D0pi0_meanOffsetGausBuPartial_)),
      Bu2Dst0h_D0pi0_21SigmaBuPartial_(
          Params::Get().CreateFloating("Bu2Dst0h_D0pi0_21SigmaBuPartial",
                                       uniqueId, Neutral::gamma, 1.8328, 1, 5)),
      Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_KpiSigmaBuPartial", uniqueId, Neutral::gamma, 0.95,
          0.5, 1.5)),
      Bu2Dst0h_D0pi0_a1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1BuPartial", uniqueId, Neutral::gamma, 1.2671e+00,
          1e+00, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_a2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2BuPartial", uniqueId, Neutral::gamma, -1.7645e+00,
          3.36e-02, Systematic::pi0BuPartialTails, Sign::negative)),
      Bu2Dst0h_D0pi0_n1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1BuPartial", uniqueId, Neutral::gamma, 1.0000e+01,
          1e+00, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_n2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2BuPartial", uniqueId, Neutral::gamma, 2.5168e+00,
          2.42e-01, Systematic::pi0BuPartialTails, Sign::positive)),
      Bu2Dst0h_D0pi0_fracPdfCb1BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdfCb1BuPartial", uniqueId, Neutral::gamma,
          4.2962e-01, 2.33e-02, Systematic::pi0BuPartialFrac, Sign::positive)),
      Bu2Dst0h_D0pi0_fracPdfCb2BuPartial_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdfCb2BuPartial", uniqueId, Neutral::gamma,
          4.4431e-01, 1.56e-02, Systematic::pi0BuPartialFrac, Sign::positive)),
      buDeltaCutEffBu2Dst0h_D0pi0_(("buDeltaCutEffBu2Dst0h_D0pi0_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 1),
      deltaCutEffBu2Dst0h_D0pi0_(
          ("deltaCutEffBu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      deltaPartialCutEffBu2Dst0h_D0pi0_(("deltaPartialCutEffBu2Dst0h_D0pi0_" +
                                         ComposeName(uniqueId, Neutral::gamma))
                                            .c_str(),
                                        "", 1),
      fracBu2Dst0h_D0pi0_(0.871),
      initYieldFAVBu2Dst0h_D0pi0_(Configuration::Get().initYieldFAVSignal() *
                                  fracBu2Dst0h_D0pi0_),
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(Params::Get().CreateFixed(
          "MisRec_thresholdDelta", uniqueId, Neutral::gamma, 4.9426e+01,
          7.76e-01, Systematic::misRecDeltaPdf, Sign::positive)),
      MisRec_aDelta_(Params::Get().CreateFloating(
          "MisRec_aDelta", uniqueId, Neutral::gamma, 1.1334e+00, -5, 5)),
      MisRec_bDelta_(Params::Get().CreateFixed(
          "MisRec_bDelta", uniqueId, Neutral::gamma, -1.5029e+00, 2.56e-03,
          Systematic::misRecDeltaPdf, Sign::none)),
      MisRec_cDelta_(Params::Get().CreateFixed(
          "MisRec_cDelta", uniqueId, Neutral::gamma, 3.4954e+01, 2.08e-01,
          Systematic::misRecDeltaPdf, Sign::positive)),
      pdfDelta_MisRec_(
          ("pdfDelta_MisRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      pdfDelta_misId_MisRec_(
          ("pdfDelta_misId_MisRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      MisRec_meanBu_(Params::Get().CreateFixed(
          "MisRec_meanBu", uniqueId, Neutral::gamma, 5.3155e+03, 6.48e-01,
          Systematic::misRecBuPdf, Sign::positive)),
      MisRec_aLBu_(Params::Get().CreateFixed(
          "MisRec_aLBu", uniqueId, Neutral::gamma, 1.5419e-02, 1.27e-02,
          Systematic::misRecBuPdf, Sign::positive)),
      MisRec_aRBu_(Params::Get().CreateFixed(
          "MisRec_aRBu", uniqueId, Neutral::gamma, 3.1182e-02, 7.38e-03,
          Systematic::misRecBuPdf, Sign::positive)),
      MisRec_meanBuPartial_(Params::Get().CreateFixed(
          "MisRec_meanBuPartial", uniqueId, Neutral::gamma, 5.3344e+03,
          7.06e-01, Systematic::misRecBuPartialPdf, Sign::positive)),
      MisRec_aLBuPartial_(Params::Get().CreateFixed(
          "MisRec_aLBuPartial", uniqueId, Neutral::gamma, 1.6586e-07, 1.10e-03,
          Systematic::misRecBuPartialPdf, Sign::positive)),
      MisRec_aRBuPartial_(Params::Get().CreateFixed(
          "MisRec_aRBuPartial", uniqueId, Neutral::gamma, 1.1570e-08, 2.81e-03,
          Systematic::misRecBuPartialPdf, Sign::positive)),
      buDeltaCutEffMisRec_(
          ("buDeltaCutEffMisRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),  //, -1, 1),
      deltaCutEffMisRec_(
          ("deltaCutEffMisRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),  // -1, 1),
      deltaPartialCutEffMisRec_(
          ("deltaPartialCutEffMisRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),  //, -1, 1),
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
      Bu2D0h_thresholdDelta_(
          ("Bu2D0h_thresholdDelta_" + ComposeName(uniqueId, Neutral::gamma))
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
      pdfDelta_misId_Bu2D0h_(
          ("pdfDelta_misId_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      Bu2D0h_meanBu_(
          ("Bu2D0h_meanBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          // "", 5.5269e+03, 5450, 5600),
          // Fixed from data
          "", 5.5403e+03),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          // 5.4892e-09, 0, 5),
          // Fixed from data
          5.0307e-07),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId, Neutral::gamma)).c_str(), "",
          // 5.3835e-12, 0, 5),
          // Fixed from data
          3.1175e-09),
      Bu2D0h_meanBuPartial_(
          ("Bu2D0h_meanBuPartial_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // "", 5.5319e+03, 5450, 5580),
          // Fixed from data
          "", 5.5429e+03),
      Bu2D0h_aLBuPartial_(
          ("Bu2D0h_aLBuPartial_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1.0264e-01),
      Bu2D0h_aRBuPartial_(
          ("Bu2D0h_aRBuPartial_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 2.6929e-02),
      buDeltaCutEffBu2D0h_(
          ("buDeltaCutEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      deltaCutEffBu2D0h_(
          ("deltaCutEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      deltaPartialCutEffBu2D0h_(
          ("deltaPartialCutEffBu2D0h_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1, -1, 1),
      fracBu2D0h_(1.936),
      initYieldFAVBu2D0h_(),
      // -------------------- PART-REC -------------------- //
      PartRec_thresholdDelta_(Params::Get().CreateFixed(
          "PartRec_thresholdDelta", uniqueId, Neutral::gamma, 6.5000e+01,
          1.42e+00, Systematic::partRecDeltaPdf, Sign::positive)),
      PartRec_aDelta_(Params::Get().CreateFixed(
          "PartRec_aDelta", uniqueId, Neutral::gamma, 5.7789e-01, 6.95e-03,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_bDelta_(Params::Get().CreateFixed(
          "PartRec_bDelta", uniqueId, Neutral::gamma, -6.7459e-01, 8.51e-03,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_cDelta_(Params::Get().CreateFixed(
          "PartRec_cDelta", uniqueId, Neutral::gamma, 9.9939e+01, 5.48e+00,
          Systematic::partRecDeltaPdf, Sign::positive)),
      pdfDelta_PartRec_(
          ("pdfDelta_PartRec_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          "", Configuration::Get().deltaMass(), *PartRec_thresholdDelta_,
          *PartRec_cDelta_, *PartRec_aDelta_, *PartRec_bDelta_),
      pdfDelta_misId_PartRec_(
          ("pdfDelta_misId_PartRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", Configuration::Get().deltaMass(), *PartRec_thresholdDelta_,
          *PartRec_cDelta_, *PartRec_aDelta_, *PartRec_bDelta_),
      PartRec_D0pi0_meanBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_meanBu", uniqueId, Neutral::gamma, 5.1473e+03,
          3.68e+00, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0pi0_aLBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aLBu", uniqueId, Neutral::gamma, 6.1807e-08, 1.45e-02,
          Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0pi0_aRBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aRBu", uniqueId, Neutral::gamma, 4.8226e-07, 8.40e-03,
          Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0gamma_meanBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_meanBu", uniqueId, Neutral::gamma, 5.1068e+03,
          4.67e+00, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0gamma_aLBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_aLBu", uniqueId, Neutral::gamma, 8.6670e-02,
          3.96e-02, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0gamma_aRBu_(Params::Get().CreateFixed(
          "PartRec_D0gamma_aRBu", uniqueId, Neutral::gamma, 1.9464e-01,
          1.57e-02, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_frac_D0pi0_(Params::Get().CreateFixed(
          "PartRec_frac_D0pi0", uniqueId, Neutral::gamma, 3.8179e-01, 1.34e-02,
          Systematic::partRecBuPdf, Sign::positive)),
      PartRec_meanBuPartial_(Params::Get().CreateFixed(
          "PartRec_meanBuPartial", uniqueId, Neutral::gamma, 5.1640e+03,
          2.20e+00, Systematic::partRecBuPartialPdf, Sign::positive)),
      PartRec_aLBuPartial_(Params::Get().CreateFixed(
          "PartRec_aLBuPartial", uniqueId, Neutral::gamma, 4.6600e-02, 1.90e-02,
          Systematic::partRecBuPartialPdf, Sign::positive)),
      PartRec_aRBuPartial_(Params::Get().CreateFixed(
          "PartRec_aRBuPartial", uniqueId, Neutral::gamma, 1.3962e-01, 6.78e-03,
          Systematic::partRecBuPartialPdf, Sign::positive)),
      buDeltaCutEffPartRec_(
          ("buDeltaCutEffPartRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      deltaCutEffPartRec_(
          ("deltaCutEffPartRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      deltaPartialCutEffPartRec_(
          ("deltaPartialCutEffPartRec_" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      fracPartRec_Bu2Dst0hst_D0gamma_(0.141),
      fracPartRec_Bu2Dst0hst_D0pi0_(0.162),
      fracPartRec_(fracPartRec_Bu2Dst0hst_D0gamma_ +
                   fracPartRec_Bu2Dst0hst_D0pi0_),
      initYieldFAVPartRec_() {
  if (Configuration::Get().splitByCharge() == true) {
    initYieldFAVMisRec_ =
        (Configuration::Get().initYieldFAVSignal() * fracMisRec_) / 4;
    initYieldFAVBu2D0h_ =
        (Configuration::Get().initYieldFAVSignal() * fracBu2D0h_) / 2;
    initYieldFAVPartRec_ =
        (Configuration::Get().initYieldFAVSignal() * fracPartRec_) / 2;
  } else {
    initYieldFAVMisRec_ =
        Configuration::Get().initYieldFAVSignal() * fracMisRec_ / 2;
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

  double buDeltaCutEffMisRecVal = 0.0;
  double deltaCutEffMisRecVal = 0.0;

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

  double buDeltaCutEffPartRecVal = 0.0;
  double deltaCutEffPartRecVal = 0.0;

  if (Configuration::Get().fitBuPartial() == true) {
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0pi_D0gamma, Bachelor::pi, buDeltaCutEffBu2Dst0h_D0gamma_,
        deltaCutEffBu2Dst0h_D0gamma_, deltaPartialCutEffBu2Dst0h_D0gamma_,
        false);
    Configuration::Get().SetEfficiencies(
        Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, buDeltaCutEffBu2Dst0h_D0pi0_,
        deltaCutEffBu2Dst0h_D0pi0_, deltaPartialCutEffBu2Dst0h_D0pi0_, false);
    double deltaPartialCutEffMisRecVal = 0.0;
    RooRealVar deltaPartialCutEffTemp(
        ("deltaPartialCutEffTemp" + ComposeName(uniqueId, Neutral::gamma))
            .c_str(),
        "", 1);
    for (auto &m : misRecModesMap) {
      Configuration::Get().SetEfficiencies(m.first, Bachelor::pi,
                                           buDeltaCutEffTemp, deltaCutEffTemp,
                                           deltaPartialCutEffTemp, false);

      buDeltaCutEffMisRecVal += buDeltaCutEffTemp.getVal() * m.second;
      deltaCutEffMisRecVal += deltaCutEffTemp.getVal() * m.second;
      deltaPartialCutEffMisRecVal += deltaPartialCutEffTemp.getVal() * m.second;
    }
    deltaPartialCutEffMisRec_.setVal(deltaPartialCutEffMisRecVal);
    Configuration::Get().SetEfficiencies(
        Mode::Bu2D0pi, Bachelor::pi, buDeltaCutEffBu2D0h_, deltaCutEffBu2D0h_,
        deltaPartialCutEffBu2D0h_, false);
    double deltaPartialCutEffPartRecVal = 0.0;
    for (auto &m : partRecModesMap) {
      Configuration::Get().SetEfficiencies(m.first, Bachelor::pi,
                                           buDeltaCutEffTemp, deltaCutEffTemp,
                                           deltaPartialCutEffTemp, false);
      buDeltaCutEffPartRecVal += buDeltaCutEffTemp.getVal() * m.second;
      deltaCutEffPartRecVal += deltaCutEffTemp.getVal() * m.second;
      deltaPartialCutEffPartRecVal +=
          deltaPartialCutEffTemp.getVal() * m.second;
    }
    deltaPartialCutEffPartRec_.setVal(deltaPartialCutEffPartRecVal);
  } else {
    Configuration::Get().SetEfficiencies(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                                         buDeltaCutEffBu2Dst0h_D0gamma_,
                                         deltaCutEffBu2Dst0h_D0gamma_, false);
    Configuration::Get().SetEfficiencies(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                                         buDeltaCutEffBu2Dst0h_D0pi0_,
                                         deltaCutEffBu2Dst0h_D0pi0_, false);
    for (auto &m : misRecModesMap) {
      Configuration::Get().SetEfficiencies(
          m.first, Bachelor::pi, buDeltaCutEffTemp, deltaCutEffTemp, false);

      buDeltaCutEffMisRecVal += buDeltaCutEffTemp.getVal() * m.second;
      deltaCutEffMisRecVal += deltaCutEffTemp.getVal() * m.second;
    }
    Configuration::Get().SetEfficiencies(Mode::Bu2D0pi, Bachelor::pi,
                                         buDeltaCutEffBu2D0h_,
                                         deltaCutEffBu2D0h_, false);
    for (auto &m : partRecModesMap) {
      Configuration::Get().SetEfficiencies(
          m.first, Bachelor::pi, buDeltaCutEffTemp, deltaCutEffTemp, false);

      buDeltaCutEffPartRecVal += buDeltaCutEffTemp.getVal() * m.second;
      deltaCutEffPartRecVal += deltaCutEffTemp.getVal() * m.second;
    }
  }
  buDeltaCutEffMisRec_.setVal(buDeltaCutEffMisRecVal);
  deltaCutEffMisRec_.setVal(deltaCutEffMisRecVal);
  buDeltaCutEffPartRec_.setVal(buDeltaCutEffPartRecVal);
  deltaCutEffPartRec_.setVal(deltaCutEffPartRecVal);

  // std::cout << "\t buDeltaCutEffBu2Dst0h_D0gamma = "
  //           << buDeltaCutEffBu2Dst0h_D0gamma_.getVal() << "\n"
  //           << "\t deltaCutEffBu2Dst0h_D0gamma = "
  //           << deltaCutEffBu2Dst0h_D0gamma_.getVal() << "\n"
  //           << "\t deltaPartialCutEffBu2Dst0h_D0gamma = "
  //           << deltaPartialCutEffBu2Dst0h_D0gamma_.getVal() << "\n";
  //
  // std::cout << "\t buDeltaCutEffBu2Dst0h_D0pi0 = "
  //           << buDeltaCutEffBu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t deltaCutEffBu2Dst0h_D0pi0 = "
  //           << deltaCutEffBu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t deltaPartialCutEffBu2Dst0h_D0pi0 = "
  //           << deltaPartialCutEffBu2Dst0h_D0pi0_.getVal() << "\n";
  //
  // std::cout << "\t buDeltaCutEffMisRec = " << buDeltaCutEffMisRec_.getVal()
  //           << "\n"
  //           << "\t deltaCutEffMisRec = " << deltaCutEffMisRec_.getVal() <<
  //           "\n";
  //
  // std::cout << "\t buDeltaCutEffBu2D0h = " << buDeltaCutEffBu2D0h_.getVal()
  //           << "\n"
  //           << "\t deltaCutEffBu2D0h = " << deltaCutEffBu2D0h_.getVal()
  //           << "\n";
  //
  // std::cout << "\t buDeltaCutEffPartRec = "
  //           << buDeltaCutEffPartRec_.getVal() << "\n"
  //           << "\t deltaCutEffPartRec = "
  //           << deltaCutEffPartRec_.getVal() << "\n";
}
