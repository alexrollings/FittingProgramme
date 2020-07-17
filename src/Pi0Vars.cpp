#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    // -------------------- PDF SHAPES -------------------- //
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : uniqueId_(uniqueId),
      Bu2Dst0h_D0pi0_meanDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, 138, 146)),
      Bu2Dst0h_D0pi0_sigmaDelta_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaDelta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, 0.1, 3)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::positive)),
      Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::same)),
      Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaTails, Sign::positive)),
      pdf1Delta_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_sigmaDelta_, *Bu2Dst0h_D0pi0_a1Delta_,
          *Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_sigmaDelta_, *Bu2Dst0h_D0pi0_a2Delta_,
          *Bu2Dst0h_D0pi0_n2Delta_),
      Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0DeltaFrac, Sign::positive)),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_meanBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_meanBu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, 5270, 5280)),
      Bu2Dst0h_D0pi0_sigmaBu_(nullptr),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(
          Params::Get().CreateFloating("Bu2Dst0h_D0pi0_KpiSigmaBu", uniqueId_,
                                       Neutral::pi0, 0.95, 0.5, 1.5)),
      Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Bu", uniqueId_, Neutral::pi0, Mode::Bu2Dst0pi_D0pi0,
          Systematic::pi0BuTails, Sign::same)),
      Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Bu", uniqueId_, Neutral::pi0, Mode::Bu2Dst0pi_D0pi0,
          Systematic::pi0BuTails, Sign::positive)),
      Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Bu", uniqueId_, Neutral::pi0, Mode::Bu2Dst0pi_D0pi0,
          Systematic::pi0BuTails, Sign::same)),
      Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Bu", uniqueId_, Neutral::pi0, Mode::Bu2Dst0pi_D0pi0,
          Systematic::pi0BuTails, Sign::positive)),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId_, Neutral::pi0,
          Mode::Bu2Dst0pi_D0pi0, Systematic::pi0BuFrac, Sign::positive)),
      Bu2Dst0h_D0pi0_mean1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_meanOffset31BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_mean3BuPartial_(),
      Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigmaRatio21BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigmaRatio31BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_a1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_a2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_n1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_n2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_fracPdf1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_fracPdf2BuPartial_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0_FAVasSUP -------------------- //
      Bu2Dst0h_D0pi0_FAVasSUP_meanDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_meanDelta", uniqueId_, Neutral::pi0,
          1.4274e+02, 2.38e-01, Systematic::pi0FAVasSUPDeltaPdf,
          Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta", uniqueId_, Neutral::pi0,
          2.7445e+00, 1.00, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigma2Delta_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1Delta", uniqueId_, Neutral::pi0,
          -1.0183e+00, 1.00, Systematic::NA, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_a2Delta_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1Delta", uniqueId_, Neutral::pi0,
          1.1431e+00, 1.00, Systematic::NA, Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_n2Delta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0pi0_FAVasSUP_(),
      pdf2Delta_Bu2Dst0h_D0pi0_FAVasSUP_(),
      Bu2Dst0h_D0pi0_FAVasSUP_fracPdf1Delta_(nullptr),
      pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP_(
          new RooCBShape(("pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP_" +
                          ComposeName(uniqueId_, Neutral::pi0))
                             .c_str(),
                         "", Configuration::Get().deltaMass(),
                         *Bu2Dst0h_D0pi0_FAVasSUP_meanDelta_,
                         *Bu2Dst0h_D0pi0_FAVasSUP_sigma1Delta_,
                         *Bu2Dst0h_D0pi0_FAVasSUP_a1Delta_,
                         *Bu2Dst0h_D0pi0_FAVasSUP_n1Delta_)),
      Bu2Dst0h_D0pi0_FAVasSUP_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_meanBu", uniqueId_, Neutral::pi0, 5.2723e+03,
          5.12e+00, Systematic::pi0FAVasSUPBuPdf, Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu", uniqueId_, Neutral::pi0,
          9.1079e+01, 4.14e+00, Systematic::pi0FAVasSUPBuPdf, Sign::positive)),
      Bu2Dst0h_D0pi0_FAVasSUP_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_a1Bu", uniqueId_, Neutral::pi0, 1.7278e+00,
          4.38e-01, Systematic::pi0FAVasSUPBuPdf, Sign::none)),
      Bu2Dst0h_D0pi0_FAVasSUP_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_FAVasSUP_n1Bu", uniqueId_, Neutral::pi0, 1.0000e+01,
          1.00, Systematic::NA, Sign::positive)),
      pdfBu_Bu2Dst0h_D0pi0_FAVasSUP_(
          ("pdfBu_Bu2Dst0h_D0pi0_FAVasSUP_" +
           ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0pi0_FAVasSUP_meanBu_, *Bu2Dst0h_D0pi0_FAVasSUP_sigmaBu_,
          *Bu2Dst0h_D0pi0_FAVasSUP_a1Bu_, *Bu2Dst0h_D0pi0_FAVasSUP_n1Bu_),
      Bu2Dst0h_D0pi0_FAVasSUP_meanBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_sigmaBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_a1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_FAVasSUP_n1BuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP_(),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      // All gamma signal reconstructed in mis-reconstructed PDF
      Bu2Dst0h_D0gamma_meanDelta_(nullptr),
      Bu2Dst0h_D0gamma_sigmaDelta_(nullptr),
      Bu2Dst0h_D0gamma_a1Delta_(nullptr),
      Bu2Dst0h_D0gamma_a2Delta_(nullptr),
      Bu2Dst0h_D0gamma_n1Delta_(nullptr),
      Bu2Dst0h_D0gamma_n2Delta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0gamma_(),
      pdf2Delta_Bu2Dst0h_D0gamma_(),
      Bu2Dst0h_D0gamma_fracPdf1Delta_(nullptr),
      Bu2Dst0h_D0gamma_thresholdDelta_(nullptr),
      Bu2Dst0h_D0gamma_aDelta_(nullptr),
      Bu2Dst0h_D0gamma_bDelta_(nullptr),
      Bu2Dst0h_D0gamma_cDelta_(nullptr),
      pdfDelta_Bu2Dst0h_D0gamma_(nullptr),
      Bu2Dst0h_D0gamma_meanBu_(nullptr),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(nullptr),
      Bu2Dst0h_D0gamma_a1Bu_(nullptr),
      Bu2Dst0h_D0gamma_a2Bu_(nullptr),
      Bu2Dst0h_D0gamma_n1Bu_(nullptr),
      Bu2Dst0h_D0gamma_n2Bu_(nullptr),
      Bu2Dst0h_D0gamma_fracPdf1Bu_(nullptr),
      Bu2Dst0h_D0gamma_meanBuPartial_(nullptr),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(nullptr),
      // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
      Bu2Dst0h_D0gamma_FAVasSUP_meanDelta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_sigmaDelta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_a1Delta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_a2Delta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_n1Delta_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_n2Delta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0gamma_FAVasSUP_(),
      pdf2Delta_Bu2Dst0h_D0gamma_FAVasSUP_(),
      Bu2Dst0h_D0gamma_FAVasSUP_fracPdf1Delta_(nullptr),
      pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP_(),
      Bu2Dst0h_D0gamma_FAVasSUP_meanBu_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_sigmaBu_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_a1Bu_(nullptr),
      Bu2Dst0h_D0gamma_FAVasSUP_n1Bu_(nullptr),
      pdfBu_Bu2Dst0h_D0gamma_FAVasSUP_(),
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(Params::Get().CreateFixed(
          "MisRec_thresholdDelta", uniqueId_, Neutral::pi0, 1.3549e+02, 1e-01,
          Systematic::NA, Sign::positive)),
      MisRec_aDelta_(Params::Get().CreateFloating(
          "MisRec_aDelta", uniqueId_, Neutral::pi0, -1.5314e+00, -5, 5)),
      MisRec_bDelta_(Params::Get().CreateFixed(
          "MisRec_bDelta", uniqueId_, Neutral::pi0, -7.4912e-03, 7.87e-02,
          Systematic::misRecDeltaPdf, Sign::none)),
      MisRec_cDelta_(Params::Get().CreateFixed(
          "MisRec_cDelta", uniqueId_, Neutral::pi0, 2.1012e+00, 8.82e-02,
          Systematic::misRecDeltaPdf, Sign::positive)),
      pdfDelta_MisRec_(
          ("pdfDelta_MisRec_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      pdfDelta_misId_MisRec_(
          ("pdfDelta_misId_MisRec_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      MisRec_meanBu_(Params::Get().CreateFixed(
          "MisRec_meanBu", uniqueId_, Neutral::pi0, 5.2759e+03, 1.04e+00,
          Systematic::misRecBuPdf, Sign::positive)),
      // MisRec_meanBu_(Params::Get().CreateFloating(
      //     "MisRec_meanBu", uniqueId_, Neutral::pi0, 5.2759e+03, 5250, 5290)),
      MisRec_aLBu_(Params::Get().CreateFixed(
          "MisRec_aLBu", uniqueId_, Neutral::pi0, 8.7522e-06, 2.86e-02,
          Systematic::misRecBuPdf, Sign::positive)),
      // MisRec_aLBu_(Params::Get().CreateFloating(
      //     "MisRec_aLBu", uniqueId_, Neutral::pi0, 8.7522e-06, 0, 5)),
      MisRec_aRBu_(Params::Get().CreateFixed(
          "MisRec_aRBu", uniqueId_, Neutral::pi0, 1.6777e-07, 5.25e-03,
          Systematic::misRecBuPdf, Sign::positive)),
      // MisRec_aRBu_(Params::Get().CreateFloating(
      //     "MisRec_aRBu", uniqueId_, Neutral::pi0, 1.6777e-07, 0, 5)),
      MisRec_meanBuPartial_(nullptr),
      MisRec_aLBuPartial_(nullptr),
      MisRec_aRBuPartial_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_thresholdDelta_(
          ("Bu2D0h_thresholdDelta_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", 1.3362e+02),
      Bu2D0h_aDelta_(
          ("Bu2D0h_aDelta_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          -6.1787e-01),
      Bu2D0h_bDelta_(
          ("Bu2D0h_bDelta_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          9.9982e-01),
      Bu2D0h_cDelta_(
          ("Bu2D0h_cDelta_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          3.3662e+00),
      pdfDelta_Bu2D0h_(
          ("pdfDelta_Bu2D0h_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      pdfDelta_misId_Bu2D0h_(
          ("pdfDelta_misId_Bu2D0h_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      Bu2D0h_meanBu_(
          ("Bu2D0h_meanBu_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          // 5.4893e+03, 5450, 5500),
          // Fixed from data
          // 5.4875e+03),
          // Fixed from data
          5500),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          1.3673e-01),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(), "",
          // 5.0076e-08, 0, 5),
          // Fixed from data
          // 1.3901e-01),
          // Fixed from data
          1.5969e-01),
      Bu2D0h_meanBuPartial_(),
      Bu2D0h_aLBuPartial_(),
      Bu2D0h_aRBuPartial_(),
      // -------------------- PART REC -------------------- //
      PartRec_thresholdDelta_(Params::Get().CreateFixed(
          "PartRec_thresholdDelta", uniqueId_, Neutral::pi0, 1.3596e+02,
          7.15e-01, Systematic::partRecDeltaPdf, Sign::positive)),
      PartRec_aDelta_(Params::Get().CreateFixed(
          "PartRec_aDelta", uniqueId_, Neutral::pi0, -4.1649e-01, 2.85e-01,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_bDelta_(Params::Get().CreateFixed(
          "PartRec_bDelta", uniqueId_, Neutral::pi0, -9.9944e-01, 1.22e+00,
          Systematic::partRecDeltaPdf, Sign::none)),
      PartRec_cDelta_(Params::Get().CreateFixed(
          "PartRec_cDelta", uniqueId_, Neutral::pi0, 2.1081e+00, 1.39e+00,
          Systematic::partRecDeltaPdf, Sign::positive)),
      pdfDelta_PartRec_(
          ("pdfDelta_PartRec_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *PartRec_thresholdDelta_,
          *PartRec_cDelta_, *PartRec_aDelta_, *PartRec_bDelta_),
      pdfDelta_misId_PartRec_(
          ("pdfDelta_misId_PartRec_" + ComposeName(uniqueId_, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *PartRec_thresholdDelta_,
          *PartRec_cDelta_, *PartRec_aDelta_, *PartRec_bDelta_),
      PartRec_D0pi0_meanBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_meanBu", uniqueId_, Neutral::pi0, 5.1332e+03, 1.91e+00,
          Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0pi0_aLBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aLBu", uniqueId_, Neutral::pi0, 4.7967e-07, 7.49e-02,
          Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0pi0_aRBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_aRBu", uniqueId_, Neutral::pi0, 1.7013e-07, 3.08e+00,
          Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0gamma_meanBu_(nullptr),
      PartRec_D0gamma_aLBu_(nullptr),
      PartRec_D0gamma_aRBu_(nullptr),
      PartRec_meanBuPartial_(nullptr),
      PartRec_aLBuPartial_(nullptr),
      PartRec_aRBuPartial_(nullptr),
      // -------------------- Correct ID BOX EFFs -------------------- //
      buDeltaCutEffBu2Dst0h_D0pi0_(nullptr),
      buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      buDeltaCutEffBu2Dst0h_D0gamma_(nullptr),
      buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      buDeltaCutEffMisRec_(nullptr),
      buDeltaCutEffBu2D0h_(nullptr),
      buDeltaCutEffPartRec_(nullptr),
      deltaCutEffBu2Dst0h_D0pi0_(nullptr),
      deltaCutEffBu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      deltaCutEffBu2Dst0h_D0gamma_(nullptr),
      deltaCutEffBu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      deltaCutEffMisRec_(nullptr),
      deltaCutEffBu2D0h_(nullptr),
      deltaCutEffPartRec_(nullptr),
      deltaPartialCutEffBu2Dst0h_D0pi0_(nullptr),
      deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      deltaPartialCutEffBu2Dst0h_D0gamma_(nullptr),
      deltaPartialCutEffMisRec_(nullptr),
      deltaPartialCutEffBu2D0h_(nullptr),
      deltaPartialCutEffPartRec_(nullptr),
      // ------------- Expected yields and relative fractions w.r.t. sig
      // -------------//
      fracBu2Dst0h_D0pi0_(),
      initYieldFAVBu2Dst0h_D0pi0_(
          initYieldFAVBu2Dst0h_D0pi0_ =
              Configuration::Get().initYieldFAVSignal()),
      fracBu2Dst0h_D0gamma_(0.213),
      initYieldFAVBu2Dst0h_D0gamma_(Configuration::Get().initYieldFAVSignal() *
                                    fracBu2Dst0h_D0gamma_),
      fracMisRec_Bu2Dst0h_D0gamma_(0.213),
      fracMisRec_Bu2Dst0h_D0gamma_WN_(0.481),
      fracMisRec_Bu2Dst0h_D0pi0_WN_(2.722),
      fracMisRec_Bu2D0hst_(1.083),
      fracMisRec_Bd2Dsth_(0.491),
      fracMisRec_(fracMisRec_Bu2Dst0h_D0gamma_WN_ +
                  fracMisRec_Bu2Dst0h_D0pi0_WN_ + fracMisRec_Bu2D0hst_ +
                  fracMisRec_Bd2Dsth_ + fracMisRec_Bu2Dst0h_D0gamma_),
      initYieldFAVMisRec_(Configuration::Get().initYieldFAVSignal() *
                          fracMisRec_ / 2),
      fracBu2D0h_(1.363),
      initYieldFAVBu2D0h_(Configuration::Get().initYieldFAVSignal() *
                          fracBu2D0h_),
      fracPartRec_Bu2Dst0hst_D0pi0_(),
      fracPartRec_Bu2Dst0hst_D0gamma_(),
      fracPartRec_(0.290),
      initYieldFAVPartRec_(Configuration::Get().initYieldFAVSignal() *
                           fracPartRec_),
      // -------------------- CP Observables -------------------- //
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_,
                                     Neutral::pi0, 1.138, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("R_CP_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::pi0)).c_str(),
        0.3, *R_CP_Bu2Dst0h_D0pi0_Blind_));
  } else {
    R_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0, 1.138, -2, 2));
  }

  std::map<std::string, double> mapBu2Dst0h_D0pi0;
  std::map<std::string, double> mapBu2Dst0h_D0pi0_FAVasSUP;
  std::map<std::string, double> mapBu2Dst0h_D0gamma;
  std::map<std::string, double> mapBu2D0h;
  std::map<std::string, double> mapPartRec;

  ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                                     mapBu2Dst0h_D0pi0, false);
  ReturnBoxEffs(Mode::Bu2Dst0pi_D0pi0_D02pik,
                                     Bachelor::pi, mapBu2Dst0h_D0pi0_FAVasSUP,
                                     false);
  ReturnBoxEffs(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                                     mapBu2Dst0h_D0gamma, false);
  ReturnBoxEffs(Mode::Bu2D0pi, Bachelor::pi, mapBu2D0h,
                                     false);
  ReturnBoxEffs(Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
                                     mapPartRec, false);

  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN, fracMisRec_Bu2Dst0h_D0pi0_WN_ / fracMisRec_},
      {Mode::Bu2Dst0pi_D0gamma, fracMisRec_Bu2Dst0h_D0gamma_ / fracMisRec_},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       fracMisRec_Bu2Dst0h_D0gamma_WN_ / fracMisRec_},
      {Mode::Bu2D0rho, fracMisRec_Bu2D0hst_ / fracMisRec_},
      {Mode::Bd2Dstpi, fracMisRec_Bd2Dsth_ / fracMisRec_}};

  std::map<std::string, double> mapMisRec;
  unsigned int it = 0;
  for (auto &m : misRecModesMap) {
    std::map<std::string, double> mapMisRecTmp;
    ReturnBoxEffs(m.first, Bachelor::pi, mapMisRecTmp,
                                       false);
    if (it == 0) {
      mapMisRec.insert(std::pair<std::string, double>(
          "buDeltaCutEff", mapMisRecTmp["buDeltaCutEff"] * m.second));
      mapMisRec.insert(std::pair<std::string, double>(
          "deltaCutEff", mapMisRecTmp["deltaCutEff"] * m.second));
    } else {
      mapMisRec["buDeltaCutEff"] += mapMisRecTmp["buDeltaCutEff"] * m.second;
      mapMisRec["deltaCutEff"] += mapMisRecTmp["deltaCutEff"] * m.second;
    }
    ++it;
  }

  buDeltaCutEffBu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0pi0", uniqueId_, Neutral::pi0,
          mapBu2Dst0h_D0pi0["buDeltaCutEff"],
          mapBu2Dst0h_D0pi0["buDeltaCutEffErr"], Systematic::buDeltaCutEffs,
          Sign::positive));
  buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP", uniqueId_, Neutral::pi0,
          mapBu2Dst0h_D0pi0_FAVasSUP["buDeltaCutEff"],
          mapBu2Dst0h_D0pi0_FAVasSUP["buDeltaCutEffErr"],
          Systematic::buDeltaCutEffs, Sign::positive));
  buDeltaCutEffBu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "buDeltaCutEffBu2Dst0h_D0gamma", uniqueId_, Neutral::pi0,
          mapBu2Dst0h_D0gamma["buDeltaCutEff"],
          mapBu2Dst0h_D0gamma["buDeltaCutEffErr"], Systematic::NA,
          Sign::positive));
  buDeltaCutEffMisRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "buDeltaCutEffMisRec", uniqueId_, Neutral::pi0, mapMisRec["buDeltaCutEff"],
      mapMisRec["buDeltaCutEffErr"], Systematic::buDeltaCutEffs,
      Sign::positive));
  buDeltaCutEffBu2D0h_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "buDeltaCutEffBu2D0h", uniqueId_, Neutral::pi0, mapBu2D0h["buDeltaCutEff"],
      mapBu2D0h["buDeltaCutEffErr"], Systematic::NA, Sign::positive));
  buDeltaCutEffPartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "buDeltaCutEffPartRec", uniqueId_, Neutral::pi0,
      mapPartRec["buDeltaCutEff"], mapPartRec["buDeltaCutEffErr"],
      Systematic::buDeltaCutEffs, Sign::positive));

  deltaCutEffBu2Dst0h_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0pi0", uniqueId_, Neutral::pi0,
          mapBu2Dst0h_D0pi0["deltaCutEff"], mapBu2Dst0h_D0pi0["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::positive));
  deltaCutEffBu2Dst0h_D0pi0_FAVasSUP_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0pi0_FAVasSUP", uniqueId_, Neutral::pi0,
          mapBu2Dst0h_D0pi0_FAVasSUP["deltaCutEff"],
          mapBu2Dst0h_D0pi0_FAVasSUP["deltaCutEffErr"],
          Systematic::deltaCutEffs, Sign::positive));
  deltaCutEffBu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "deltaCutEffBu2Dst0h_D0gamma", uniqueId_, Neutral::pi0,
          mapBu2Dst0h_D0gamma["deltaCutEff"],
          mapBu2Dst0h_D0gamma["deltaCutEffErr"], Systematic::NA,
          Sign::positive));
  deltaCutEffMisRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffMisRec", uniqueId_, Neutral::pi0, mapMisRec["deltaCutEff"],
      mapMisRec["deltaCutEffErr"], Systematic::deltaCutEffs, Sign::positive));
  deltaCutEffBu2D0h_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffBu2D0h", uniqueId_, Neutral::pi0, mapBu2D0h["deltaCutEff"],
      mapBu2D0h["deltaCutEffErr"], Systematic::NA, Sign::positive));
  deltaCutEffPartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "deltaCutEffPartRec", uniqueId_, Neutral::pi0, mapPartRec["deltaCutEff"],
      mapPartRec["deltaCutEffErr"], Systematic::deltaCutEffs, Sign::positive));
}
