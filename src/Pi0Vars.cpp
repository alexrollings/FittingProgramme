#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : Bu2Dst0h_D0pi0_meanDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0pi0_meanDelta", uniqueId,
                                       Neutral::pi0, 1.4243e+02, 138, 146)),
      Bu2Dst0h_D0pi0_sigmaDelta_(
          Params::Get().CreateFloating("Bu2Dst0h_D0pi0_sigmaDelta", uniqueId,
                                       Neutral::pi0, 1.6683e+00, 0.1, 3)),
      Bu2Dst0h_D0pi0_a1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Delta", uniqueId, Neutral::pi0, 1.2605e+00,
          5.67e-02, Systematic::pi0DeltaTails)),
      Bu2Dst0h_D0pi0_a2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Delta", uniqueId, Neutral::pi0, -7.4403e-01,
          2.00e-02, Systematic::pi0DeltaTails)),
      Bu2Dst0h_D0pi0_n1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Delta", uniqueId, Neutral::pi0, 9.1634e-01,
          2.73e-01, Systematic::pi0DeltaTails)),
      Bu2Dst0h_D0pi0_n2Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Delta", uniqueId, Neutral::pi0, 6.2119e+00,
          1.16e+00, Systematic::pi0DeltaTails)),
      pdf1Delta_Bu2Dst0h_D0pi0_(
          ("pdf1Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_sigmaDelta_, *Bu2Dst0h_D0pi0_a1Delta_,
          *Bu2Dst0h_D0pi0_n1Delta_),
      pdf2Delta_Bu2Dst0h_D0pi0_(
          ("pdf2Delta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *Bu2Dst0h_D0pi0_meanDelta_,
          *Bu2Dst0h_D0pi0_sigmaDelta_, *Bu2Dst0h_D0pi0_a2Delta_,
          *Bu2Dst0h_D0pi0_n2Delta_),
      Bu2Dst0h_D0pi0_fracPdf1Delta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Delta", uniqueId, Neutral::pi0, 2.2702e-01,
          2.13e-02, Systematic::pi0DeltaFrac)),
      pdfDelta_Bu2Dst0h_D0pi0_(
          ("pdfDelta_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      pdfDelta_misId_Bu2Dst0h_D0pi0_(
          ("pdfDelta_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_D0pi0_, pdf2Delta_Bu2Dst0h_D0pi0_),
          *Bu2Dst0h_D0pi0_fracPdf1Delta_),
      Bu2Dst0h_D0pi0_meanBu_(
          Params::Get().CreateFloating("Bu2Dst0h_D0pi0_meanBu", uniqueId,
                                       Neutral::pi0, 5.2735e+03, 5270, 5275)),
      Bu2Dst0h_D0pi0_KpiSigmaBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_KpiSigmaBu", uniqueId, Neutral::pi0, 0.95, 0.5, 1.5)),
      Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a1Bu", uniqueId, Neutral::pi0, 1.4278e+00, 2.89e-01,
          Systematic::pi0BuTails)),
      Bu2Dst0h_D0pi0_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_a2Bu", uniqueId, Neutral::pi0, -1.8126e+00, 1.11e-01,
          Systematic::pi0BuTails)),
      Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n1Bu", uniqueId, Neutral::pi0, 2.6674e+00, 1.85e+00,
          Systematic::pi0BuTails)),
      Bu2Dst0h_D0pi0_n2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_n2Bu", uniqueId, Neutral::pi0, 1.0000e+01, 1e+00,
          Systematic::NA)),
      Bu2Dst0h_D0pi0_fracPdf1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0pi0_fracPdf1Bu", uniqueId, Neutral::pi0, 2.0967e-01,
          1e+00, Systematic::NA)),
      Bu2Dst0h_D0pi0_meanCbBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_meanOffsetGausBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_meanGausBuPartial_(),
      Bu2Dst0h_D0pi0_21SigmaBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_KpiSigmaBuPartial_(nullptr),
      Bu2Dst0h_D0pi0_a1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_a2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_n1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_n2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_fracPdfCb1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_fracPdfCb2BuPartial_(nullptr),
      buDeltaCutEffBu2Dst0h_D0pi0_(
          ("buDeltaCutEffBu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 1),
      deltaCutEffBu2Dst0h_D0pi0_(
          ("deltaCutEffBu2Dst0h_D0pi0_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 1),
      deltaPartialCutEffBu2Dst0h_D0pi0_(),
      fracBu2Dst0h_D0pi0_(),
      initYieldFAVBu2Dst0h_D0pi0_(
          initYieldFAVBu2Dst0h_D0pi0_ =
              Configuration::Get().initYieldFAVSignal()),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_meanDelta_(nullptr),
      Bu2Dst0h_D0gamma_sigmaDelta_(nullptr),
      Bu2Dst0h_D0gamma_a1Delta_(nullptr),
      Bu2Dst0h_D0gamma_a2Delta_(nullptr),
      Bu2Dst0h_D0gamma_n1Delta_(nullptr),
      Bu2Dst0h_D0gamma_n2Delta_(nullptr),
      pdf1Delta_Bu2Dst0h_D0gamma_(),
      pdf2Delta_Bu2Dst0h_D0gamma_(),
      Bu2Dst0h_D0gamma_fracPdf1Delta_(nullptr),
      Bu2Dst0h_D0gamma_thresholdDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_thresholdDelta", uniqueId, Neutral::pi0, 1.5483e+02,
          2.08e-01, Systematic::crossFeedDeltaPdf)),
      Bu2Dst0h_D0gamma_aDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_aDelta", uniqueId, Neutral::pi0, 2.1635e-01,
          1.62e-01, Systematic::crossFeedDeltaPdf)),
      Bu2Dst0h_D0gamma_bDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_bDelta", uniqueId, Neutral::pi0, -9.9922e-01,
          1.45e+00, Systematic::crossFeedDeltaPdf)),
      Bu2Dst0h_D0gamma_cDelta_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_cDelta", uniqueId, Neutral::pi0, 1.3164e+01, 1e+00,
          Systematic::NA)),
      pdfDelta_Bu2Dst0h_D0gamma_(new RooDstD0BG(
          ("pdfDelta_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0gamma_thresholdDelta_, *Bu2Dst0h_D0gamma_cDelta_,
          *Bu2Dst0h_D0gamma_aDelta_, *Bu2Dst0h_D0gamma_bDelta_)),
      pdfDelta_misId_Bu2Dst0h_D0gamma_(new RooDstD0BG(
          ("pdfDelta_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          *Bu2Dst0h_D0gamma_thresholdDelta_, *Bu2Dst0h_D0gamma_cDelta_,
          *Bu2Dst0h_D0gamma_aDelta_, *Bu2Dst0h_D0gamma_bDelta_)),
      Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_meanBu", uniqueId, Neutral::pi0, 5.2930e+03,
          1.32e+00, Systematic::crossFeedBuPdf)),
      Bu2Dst0h_D0gamma_KpiSigmaBu_(),
      Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a1Bu", uniqueId, Neutral::pi0, 9.8865e-02, 5.73e-03,
          Systematic::crossFeedBuPdf)),
      Bu2Dst0h_D0gamma_a2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_a2Bu", uniqueId, Neutral::pi0, 3.2558e-02, 1.07e-02,
          Systematic::crossFeedBuPdf)),
      Bu2Dst0h_D0gamma_n1Bu_(nullptr),
      Bu2Dst0h_D0gamma_n2Bu_(nullptr),
      Bu2Dst0h_D0gamma_fracPdf1Bu_(nullptr),
      Bu2Dst0h_D0gamma_meanBuPartial_(nullptr),
      Bu2Dst0h_D0gamma_aBuPartial_(nullptr),
      Bu2Dst0h_D0gamma_nBuPartial_(nullptr),
      buDeltaCutEffBu2Dst0h_D0gamma_(("buDeltaCutEffBu2Dst0h_D0gamma_" +
                                      ComposeName(uniqueId, Neutral::pi0))
                                         .c_str(),
                                     "", 1),
      deltaCutEffBu2Dst0h_D0gamma_(
          ("deltaCutEffBu2Dst0h_D0gamma_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 1),
      deltaPartialCutEffBu2Dst0h_D0gamma_(),
      fracBu2Dst0h_D0gamma_(0.213),
      initYieldFAVBu2Dst0h_D0gamma_(Configuration::Get().initYieldFAVSignal() *
                                    fracBu2Dst0h_D0gamma_),
      // -------------------- MIS-REC -------------------- //
      MisRec_thresholdDelta_(Params::Get().CreateFixed(
          "MisRec_thresholdDelta", uniqueId, Neutral::pi0, 1.3549e+02, 1e-01,
          Systematic::NA)),
      MisRec_aDelta_(Params::Get().CreateFloating(
          "MisRec_aDelta", uniqueId, Neutral::pi0, -1.5314e+00, -5, 5)),
      MisRec_bDelta_(Params::Get().CreateFixed(
          "MisRec_bDelta", uniqueId, Neutral::pi0, -7.4912e-03, 7.87e-02,
          Systematic::misRecDeltaPdf)),
      MisRec_cDelta_(Params::Get().CreateFixed(
          "MisRec_cDelta", uniqueId, Neutral::pi0, 2.1012e+00, 8.82e-02,
          Systematic::misRecDeltaPdf)),
      pdfDelta_MisRec_(
          ("pdfDelta_MisRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      pdfDelta_misId_MisRec_(
          ("pdfDelta_misId_MisRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), *MisRec_thresholdDelta_,
          *MisRec_cDelta_, *MisRec_aDelta_, *MisRec_bDelta_),
      MisRec_meanBu_(Params::Get().CreateFixed(
          "MisRec_meanBu", uniqueId, Neutral::pi0, 5.2759e+03, 1.04e+00,
          Systematic::misRecBuPdf)),
      MisRec_aLBu_(Params::Get().CreateFixed(
          "MisRec_aLBu", uniqueId, Neutral::pi0, 8.7522e-06, 2.86e-02,
          Systematic::misRecBuPdf)),
      MisRec_aRBu_(Params::Get().CreateFixed(
          "MisRec_aRBu", uniqueId, Neutral::pi0, 1.6777e-07, 5.25e-03,
          Systematic::misRecBuPdf)),
      MisRec_meanBuPartial_(nullptr),
      MisRec_aLBuPartial_(nullptr),
      MisRec_aRBuPartial_(nullptr),
      buDeltaCutEffMisRec_(
          ("buDeltaCutEffMisRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 1),  //, -1, 1),
      deltaCutEffMisRec_(
          ("deltaCutEffMisRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", 1),
      deltaPartialCutEffMisRec_(),
      fracMisRec_Bu2Dst0h_D0gamma_(0.213),
      fracMisRec_Bu2Dst0h_D0gamma_WN_(0.481),
      fracMisRec_Bu2Dst0h_D0pi0_WN_(2.722),
      fracMisRec_Bu2D0hst_(1.083),
      fracMisRec_Bd2Dsth_(0.491),
      fracMisRec_(fracMisRec_Bu2Dst0h_D0gamma_WN_ +
                  fracMisRec_Bu2Dst0h_D0pi0_WN_ + fracMisRec_Bu2D0hst_ +
                  fracMisRec_Bd2Dsth_ + fracMisRec_Bu2Dst0h_D0gamma_),
      initYieldFAVMisRec_(),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_thresholdDelta_(
          ("Bu2D0h_thresholdDelta_" + ComposeName(uniqueId, Neutral::pi0))
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
      pdfDelta_misId_Bu2D0h_(
          ("pdfDelta_misId_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), Bu2D0h_thresholdDelta_,
          Bu2D0h_cDelta_, Bu2D0h_aDelta_, Bu2D0h_bDelta_),
      Bu2D0h_meanBu_(
          ("Bu2D0h_meanBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          // 5.4893e+03, 5450, 5500),
          // Fixed from data
          // 5.4875e+03),
          // Fixed from data
          5500),
      Bu2D0h_aLBu_(
          ("Bu2D0h_aLBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          1.3673e-01),
      Bu2D0h_aRBu_(
          ("Bu2D0h_aRBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          // 5.0076e-08, 0, 5),
          // Fixed from data
          // 1.3901e-01),
          // Fixed from data
          1.5969e-01),
      Bu2D0h_meanBuPartial_(),
      Bu2D0h_aLBuPartial_(),
      Bu2D0h_aRBuPartial_(),
      buDeltaCutEffBu2D0h_(
          ("buDeltaCutEffBu2D0h_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 1),
      deltaCutEffBu2D0h_(
          ("deltaCutEffBu2D0h_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", 1),
      deltaPartialCutEffBu2D0h_(),
      fracBu2D0h_(1.363),
      initYieldFAVBu2D0h_(),
      // -------------------- PART REC -------------------- //
      partRec_thresholdDelta_(
          ("partRec_thresholdDelta_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 1.3596e+02),
      partRec_aDelta_(
          ("partRec_aDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          -4.1649e-01),
      partRec_bDelta_(
          ("partRec_bDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          -9.9944e-01),
      partRec_cDelta_(
          ("partRec_cDelta_" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
          2.1081e+00),
      pdfDelta_PartRec_(
          ("pdfDelta_PartRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", Configuration::Get().deltaMass(), partRec_thresholdDelta_,
          partRec_cDelta_, partRec_aDelta_, partRec_bDelta_),
      pdfDelta_misId_PartRec_(
          ("pdfDelta_misId_PartRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(), partRec_thresholdDelta_,
          partRec_cDelta_, partRec_aDelta_, partRec_bDelta_),
      partRec_D0pi0_meanBu_(
          ("partRec_D0pi0_meanBu_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // "", 5.1162e+03, 5090, 5140),
          // Fixed from data at 4900
          "", 5.1323e+03),
      partRec_D0pi0_aLBu_(
          ("partRec_D0pi0_aLBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", 4.7967e-07),
      partRec_D0pi0_aRBu_(
          ("partRec_D0pi0_aRBu_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", 1.7013e-07),
      partRec_D0gamma_meanBu_(),
      partRec_D0gamma_aLBu_(),
      partRec_D0gamma_aRBu_(),
      partRec_meanBuPartial_(),
      partRec_aLBuPartial_(),
      partRec_aRBuPartial_(),
      buDeltaCutEffPartRec_(
          ("buDeltaCutEffPartRec_" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          "", 1),
      deltaCutEffPartRec_(
          ("deltaCutEffPartRec_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          "", 1),
      deltaPartialCutEffPartRec_(),
      fracPartRec_Bu2Dst0hst_D0pi0_(),
      fracPartRec_Bu2Dst0hst_D0gamma_(),
      fracPartRec_(0.290),
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

  // Pass empty RRV for deltaPartialCutEff in π0 mode
  Configuration::Get().SetEfficiencies(
      Mode::Bu2Dst0pi_D0pi0, Bachelor::pi, 
      buDeltaCutEffBu2Dst0h_D0pi0_,
      deltaCutEffBu2Dst0h_D0pi0_, false);
  // std::cout << buDeltaCutEffBu2Dst0h_D0pi0_.getVal() << "\n"
  //           << "\t deltaCutEffBu2Dst0h_D0pi0 = "
  //           << deltaCutEffBu2Dst0h_D0pi0_.getVal() << "\n";
  //
  std::map<Mode, double> misRecModesMap = {
      {Mode::Bu2Dst0pi_D0pi0_WN, fracMisRec_Bu2Dst0h_D0pi0_WN_ / fracMisRec_},
      {Mode::Bu2Dst0pi_D0gamma, fracMisRec_Bu2Dst0h_D0gamma_ / fracMisRec_},
      {Mode::Bu2Dst0pi_D0gamma_WN,
       fracMisRec_Bu2Dst0h_D0gamma_WN_ / fracMisRec_},
      {Mode::Bu2D0rho, fracMisRec_Bu2D0hst_ / fracMisRec_},
      {Mode::Bd2Dstpi, fracMisRec_Bd2Dsth_ / fracMisRec_}};

  double buDeltaCutEffMisRecVal = 0.0;
  double deltaCutEffMisRecVal = 0.0;

  for (auto &m : misRecModesMap) {
    RooRealVar buDeltaCutEffTemp(
        ("buDeltaCutEffTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
        1);
    RooRealVar deltaCutEffTemp(
        ("deltaCutEffTemp" + ComposeName(uniqueId, Neutral::pi0)).c_str(), "",
        1);

    Configuration::Get().SetEfficiencies(m.first, Bachelor::pi, buDeltaCutEffTemp,
                                         deltaCutEffTemp, false);

    buDeltaCutEffMisRecVal += buDeltaCutEffTemp.getVal() * m.second;
    deltaCutEffMisRecVal += deltaCutEffTemp.getVal() * m.second;
  }
  buDeltaCutEffMisRec_.setVal(buDeltaCutEffMisRecVal);
  deltaCutEffMisRec_.setVal(deltaCutEffMisRecVal);
  // std::cout << "\t buDeltaCutEffMisRec = " << buDeltaCutEffMisRec_.getVal()
  //           << "\n"
  //           << "\t deltaCutEffMisRec = " << deltaCutEffMisRec_.getVal() <<
  //           "\n";

  Configuration::Get().SetEfficiencies(
      Mode::Bu2D0pi, Bachelor::pi,
      buDeltaCutEffBu2D0h_, deltaCutEffBu2D0h_, false);
  // std::cout << "\t buDeltaCutEffBu2D0h = " << buDeltaCutEffBu2D0h_.getVal()
  //           << "\n"
  //           << "\t deltaCutEffBu2D0h = " << deltaCutEffBu2D0h_.getVal()
  //           << "\n";
  Configuration::Get().SetEfficiencies(
      Mode::Bu2Dst0rho_D0pi0, Bachelor::pi,
      buDeltaCutEffPartRec_, deltaCutEffPartRec_, false);
  // std::cout << "\t buDeltaCutEffPartRec = "
  //           << buDeltaCutEffPartRec_.getVal() << "\n"
  //           << "\t deltaCutEffPartRec = "
  //           << deltaCutEffPartRec_.getVal() << "\n";
}
