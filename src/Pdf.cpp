#include "Pdf.h"
#include "Configuration.h"

PdfBase::PdfBase(Neutral neutral, Bachelor bachelor, Daughters daughters)
    : neutral_(neutral), bachelor_(bachelor), daughters_(daughters),
      addPdf_(nullptr), signalYield_(nullptr), crossFeedYield_(nullptr),
      nonTmSignalYield_(nullptr), bu2Dst0Hst_D0pi0Yield_(nullptr),
      bu2Dst0Hst_D0gammaYield_(nullptr), bu2D0HYield_(nullptr),
      bu2D0HstYield_(nullptr), bd2DstHYield_(nullptr), missIdYield_(nullptr),
      combinatorialConstant_(
          ("combinatorialConstant_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "Combinatorial parameter", 0, -0.00001, 0.00001),
      combinatorial_(new RooExponential(
          ("combinatorial_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "combinatorial exponential", Configuration::Get().buMass(),
          combinatorialConstant_)),
      combinatorialYield_(
          ("combinatorialYield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "combinatorial yield", 10000, 0, 30000),
      yields_(
          ("yields_" + ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str()),
      functions_(("functions_" +
                  ComposeFittingCategoryName(neutral, bachelor, daughters))
                     .c_str()) {}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(
      *addPdf_,
      ComposeFittingCategoryName(neutral_, bachelor_, daughters_).c_str());
}

template <>
Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Pdf()
    : PdfBase(Neutral::pi0, Bachelor::pi, Daughters::kpi) {
  std::cout << "Instantiated specific template Pdf<Neutral::pi0, Bachelor::pi, "
               "Daughters::kpi>::Pdf()"
            << "\n";
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_pi0_pi_kpi", "Signal Yield pi0, pi, kpi", "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_pi0_pi_kpi", "non TM Signal Yield pi0, pi, kpi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_pi0_pi_kpi", "Cross Feed Yield pi0, pi, kpi", "@0*@1*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_pi0_pi_kpi", "bu2Dst0Hst_D0pi0 Yield pi0, pi, kpi",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_pi0_pi_kpi",
      "bu2Dst0Hst_D0gamma Yield pi0, pi, kpi",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_pi0_pi_kpi", "bu2D0H Yield pi0, pi, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_pi0_pi_kpi", "bu2D0Hst Yield pi0, pi, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_pi0_pi_kpi", "bd2DstH Yield pi0, pi, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "missIdYield_pi0_pi_kpi", "missId yield pi0, pi, kpi",
      "@0*(1-@1)*@2",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get()
              .N_Dh(),
          NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi>::Pdf()
    : PdfBase(Neutral::pi0, Bachelor::k, Daughters::kpi) {
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_pi0_k_kpi", "Signal Yield pi0, k, kpi", "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_pi0_k_kpi", "non TM Signal Yield pi0, k, kpi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_pi0_k_kpi"
      "Cross Feed Yield pi0, k, kpi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_pi0_k_kpi", "bu2Dst0Hst_D0pi0 Yield pi0, k, kpi",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_pi0_k_kpi",
      "bu2Dst0Hst_D0gamma Yield pi0, k, kpi",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_pi0_k_kpi", "bu2D0H Yield pi0, k, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_pi0_k_kpi", "bu2D0Hst Yield pi0, k, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_pi0_k_kpi", "bd2DstH Yield pi0, k, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooRealVar>(
      new RooRealVar("missIdYield_pi0_k_kpi", "missId yield k, pi, kpi",
                     20 * DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  // "@0*(1-@1)*@2",
  //    RooArgList(
  //        SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get()
  //            .N_Dh(),
  //        NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().crossFeedRate(),
  //        NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Pdf()
    : PdfBase(Neutral::gamma, Bachelor::pi, Daughters::kpi) {
  std::cout << "Instantiated specific template Pdf<Neutral::gamma, "
               "Bachelor::pi, Daughters::kpi>::Pdf()"
            << "\n";
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_gamma_pi_kpi", "Signal Yield gamma, pi, kpi",
      "@0*(1-@1-@2)*@3",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().selfCrossFeedRate(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_gamma_pi_kpi", "non TM Signal Yield gamma, pi, kpi",
      "@0*@1*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().selfCrossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_gamma_pi_kpi", "Cross Feed Yield gamma, pi, kpi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_gamma_pi_kpi",
      "bu2Dst0Hst_D0pi0 Yield gamma, pi, kpi",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_gamma_pi_kpi",
      "bu2Dst0Hst_D0gamma Yield gamma, pi, kpi",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_gamma_pi_kpi", "bu2D0H Yield gamma, pi, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_gamma_pi_kpi", "bu2D0Hst Yield gamma, pi, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_gamma_pi_kpi", "bd2DstH Yield gamma, pi, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "missIdYield_gamma_pi_kpi", "missId yield gamma, pi, kpi",
      "@0*(1-@1)*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get()
              .N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Pdf()
    : PdfBase(Neutral::gamma, Bachelor::k, Daughters::kpi) {
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_gamma_k_kpi", "Signal Yield gamma, k, kpi",
      "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_gamma_k_kpi", "non TM Signal Yield gamma, k, kpi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_gamma_k_kpi", "Cross Feed Yield gamma, k, kpi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_gamma_k_kpi",
      "bu2Dst0Hst_D0pi0 Yield gamma, k, kpi",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_gamma_k_kpi",
      "bu2Dst0Hst_D0gamma Yield gamma, k, kpi",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::kpi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_gamma_k_kpi", "bu2D0H Yield gamma, k, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_gamma_k_kpi", "bu2D0Hst Yield gamma, k, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_gamma_k_kpi", "bd2DstH Yield gamma, k, kpi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kpi>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooRealVar>(
      new RooRealVar("missIdYield_gamma_k_kpi", "missId yield gamma, k, kpi",
                     20 * DaughtersVars<Daughters::kpi>::Get().daughtersSF()));
  // "@0*(1-@1)*@2",
  // RooArgList(
  //     SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Get()
  //         .N_Dh(),
  //     NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get().crossFeedRate(),
  //     NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk>::Pdf()
    : PdfBase(Neutral::pi0, Bachelor::pi, Daughters::kk) {
  std::cout << "Instantiated specific template Pdf<Neutral::pi0, Bachelor::pi, "
               "Daughters::kk>::Pdf()"
            << "\n";
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_pi0_pi_kk", "Signal Yield pi0, pi, kk", "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_pi0_pi_kk", "non TM Signal Yield pi0, pi, kk",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_pi0_pi_kk", "Cross Feed Yield pi0, pi, kk", "@0*@1*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_pi0_pi_kk", "bu2Dst0Hst_D0pi0 Yield pi0, pi, kk",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::kk>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_pi0_pi_kk",
      "bu2Dst0Hst_D0gamma Yield pi0, pi, kk",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::kk>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_pi0_pi_kk", "bu2D0H Yield pi0, pi, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_pi0_pi_kk", "bu2D0Hst Yield pi0, pi, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_pi0_pi_kk", "bd2DstH Yield pi0, pi, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "missIdYield_pi0_pi_kk", "missId yield pi0, pi, kk",
      "@0*(1-@1)*@2",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::Get()
              .N_Dh(),
          NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::pi0, Bachelor::k, Daughters::kk>::Pdf()
    : PdfBase(Neutral::pi0, Bachelor::k, Daughters::kk) {
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_pi0_k_kk", "Signal Yield pi0, k, kk", "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_pi0_k_kk", "non TM Signal Yield pi0, k, kk",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_pi0_k_kk"
      "Cross Feed Yield pi0, k, kk",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_pi0_k_kk", "bu2Dst0Hst_D0pi0 Yield pi0, k, kk",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::kk>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_pi0_k_kk",
      "bu2Dst0Hst_D0gamma Yield pi0, k, kk",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::kk>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_pi0_k_kk", "bu2D0H Yield pi0, k, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_pi0_k_kk", "bu2D0Hst Yield pi0, k, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_pi0_k_kk", "bd2DstH Yield pi0, k, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooRealVar>(
      new RooRealVar("missIdYield_pi0_k_kk", "missId yield k, pi, kk",
                     20 * DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  // "@0*(1-@1)*@2",
  //    RooArgList(
  //        SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get()
  //            .N_Dh(),
  //        NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().crossFeedRate(),
  //        NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk>::Pdf()
    : PdfBase(Neutral::gamma, Bachelor::pi, Daughters::kk) {
  std::cout << "Instantiated specific template Pdf<Neutral::gamma, "
               "Bachelor::pi, Daughters::kk>::Pdf()"
            << "\n";
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_gamma_pi_kk", "Signal Yield gamma, pi, kk",
      "@0*(1-@1-@2)*@3",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().selfCrossFeedRate(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_gamma_pi_kk", "non TM Signal Yield gamma, pi, kk",
      "@0*@1*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().selfCrossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_gamma_pi_kk", "Cross Feed Yield gamma, pi, kk",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_gamma_pi_kk",
      "bu2Dst0Hst_D0pi0 Yield gamma, pi, kk",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::kk>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_gamma_pi_kk",
      "bu2Dst0Hst_D0gamma Yield gamma, pi, kk",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::kk>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_gamma_pi_kk", "bu2D0H Yield gamma, pi, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_gamma_pi_kk", "bu2D0Hst Yield gamma, pi, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_gamma_pi_kk", "bd2DstH Yield gamma, pi, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "missIdYield_gamma_pi_kk", "missId yield gamma, pi, kk",
      "@0*(1-@1)*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::Get()
              .N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::gamma, Bachelor::k, Daughters::kk>::Pdf()
    : PdfBase(Neutral::gamma, Bachelor::k, Daughters::kk) {
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_gamma_k_kk", "Signal Yield gamma, k, kk",
      "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_gamma_k_kk", "non TM Signal Yield gamma, k, kk",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_gamma_k_kk", "Cross Feed Yield gamma, k, kk",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::kk>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_gamma_k_kk",
      "bu2Dst0Hst_D0pi0 Yield gamma, k, kk",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::kk>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_gamma_k_kk",
      "bu2Dst0Hst_D0gamma Yield gamma, k, kk",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::kk>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_gamma_k_kk", "bu2D0H Yield gamma, k, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_gamma_k_kk", "bu2D0Hst Yield gamma, k, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_gamma_k_kk", "bd2DstH Yield gamma, k, kk", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::kk>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooRealVar>(
      new RooRealVar("missIdYield_gamma_k_kk", "missId yield gamma, k, kk",
                     20 * DaughtersVars<Daughters::kk>::Get().daughtersSF()));
  // "@0*(1-@1)*@2",
  // RooArgList(
  //     SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::kk>::Get()
  //         .N_Dh(),
  //     NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get().crossFeedRate(),
  //     NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Pdf()
    : PdfBase(Neutral::pi0, Bachelor::pi, Daughters::pipi) {
  std::cout << "Instantiated specific template Pdf<Neutral::pi0, Bachelor::pi, "
               "Daughters::pipi>::Pdf()"
            << "\n";
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_pi0_pi_pipi", "Signal Yield pi0, pi, pipi", "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_pi0_pi_pipi", "non TM Signal Yield pi0, pi, pipi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_pi0_pi_pipi", "Cross Feed Yield pi0, pi, pipi", "@0*@1*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_pi0_pi_pipi", "bu2Dst0Hst_D0pi0 Yield pi0, pi, pipi",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_pi0_pi_pipi",
      "bu2Dst0Hst_D0gamma Yield pi0, pi, pipi",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_pi0_pi_pipi", "bu2D0H Yield pi0, pi, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_pi0_pi_pipi", "bu2D0Hst Yield pi0, pi, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_pi0_pi_pipi", "bd2DstH Yield pi0, pi, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "missIdYield_pi0_pi_pipi", "missId yield pi0, pi, pipi",
      "@0*(1-@1)*@2",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get()
              .N_Dh(),
          NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi>::Pdf()
    : PdfBase(Neutral::pi0, Bachelor::k, Daughters::pipi) {
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_pi0_k_pipi", "Signal Yield pi0, k, pipi", "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_pi0_k_pipi", "non TM Signal Yield pi0, k, pipi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_pi0_k_pipi"
      "Cross Feed Yield pi0, k, pipi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_pi0_k_pipi", "bu2Dst0Hst_D0pi0 Yield pi0, k, pipi",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_pi0_k_pipi",
      "bu2Dst0Hst_D0gamma Yield pi0, k, pipi",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_pi0_k_pipi", "bu2D0H Yield pi0, k, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_pi0_k_pipi", "bu2D0Hst Yield pi0, k, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_pi0_k_pipi", "bd2DstH Yield pi0, k, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooRealVar>(
      new RooRealVar("missIdYield_pi0_k_pipi", "missId yield k, pi, pipi",
                     20 * DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  // "@0*(1-@1)*@2",
  //    RooArgList(
  //        SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get()
  //            .N_Dh(),
  //        NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().crossFeedRate(),
  //        NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Pdf()
    : PdfBase(Neutral::gamma, Bachelor::pi, Daughters::pipi) {
  std::cout << "Instantiated specific template Pdf<Neutral::gamma, "
               "Bachelor::pi, Daughters::pipi>::Pdf()"
            << "\n";
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_gamma_pi_pipi", "Signal Yield gamma, pi, pipi",
      "@0*(1-@1-@2)*@3",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().selfCrossFeedRate(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_gamma_pi_pipi", "non TM Signal Yield gamma, pi, pipi",
      "@0*@1*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().selfCrossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_gamma_pi_pipi", "Cross Feed Yield gamma, pi, pipi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_gamma_pi_pipi",
      "bu2Dst0Hst_D0pi0 Yield gamma, pi, pipi",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_gamma_pi_pipi",
      "bu2Dst0Hst_D0gamma Yield gamma, pi, pipi",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_gamma_pi_pipi", "bu2D0H Yield gamma, pi, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_gamma_pi_pipi", "bu2D0Hst Yield gamma, pi, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_gamma_pi_pipi", "bd2DstH Yield gamma, pi, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "missIdYield_gamma_pi_pipi", "missId yield gamma, pi, pipi",
      "@0*(1-@1)*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get()
              .N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi>::Pdf()
    : PdfBase(Neutral::gamma, Bachelor::k, Daughters::pipi) {
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_gamma_k_pipi", "Signal Yield gamma, k, pipi",
      "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_gamma_k_pipi", "non TM Signal Yield gamma, k, pipi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_gamma_k_pipi", "Cross Feed Yield gamma, k, pipi",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_gamma_k_pipi",
      "bu2Dst0Hst_D0pi0 Yield gamma, k, pipi",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_gamma_k_pipi",
      "bu2Dst0Hst_D0gamma Yield gamma, k, pipi",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::pipi>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_gamma_k_pipi", "bu2D0H Yield gamma, k, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_gamma_k_pipi", "bu2D0Hst Yield gamma, k, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_gamma_k_pipi", "bd2DstH Yield gamma, k, pipi", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pipi>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooRealVar>(
      new RooRealVar("missIdYield_gamma_k_pipi", "missId yield gamma, k, pipi",
                     20 * DaughtersVars<Daughters::pipi>::Get().daughtersSF()));
  // "@0*(1-@1)*@2",
  // RooArgList(
  //     SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Get()
  //         .N_Dh(),
  //     NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get().crossFeedRate(),
  //     NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik>::Pdf()
    : PdfBase(Neutral::pi0, Bachelor::pi, Daughters::pik) {
  std::cout << "Instantiated specific template Pdf<Neutral::pi0, Bachelor::pi, "
               "Daughters::pik>::Pdf()"
            << "\n";
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_pi0_pi_pik", "Signal Yield pi0, pi, pik", "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_pi0_pi_pik", "non TM Signal Yield pi0, pi, pik",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_pi0_pi_pik", "Cross Feed Yield pi0, pi, pik", "@0*@1*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_pi0_pi_pik", "bu2Dst0Hst_D0pi0 Yield pi0, pi, pik",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::pik>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_pi0_pi_pik",
      "bu2Dst0Hst_D0gamma Yield pi0, pi, pik",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::pik>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_pi0_pi_pik", "bu2D0H Yield pi0, pi, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_pi0_pi_pik", "bu2D0Hst Yield pi0, pi, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_pi0_pi_pik", "bd2DstH Yield pi0, pi, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "missIdYield_pi0_pi_pik", "missId yield pi0, pi, pik",
      "@0*(1-@1)*@2",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::Get()
              .N_Dh(),
          NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::pi0, Bachelor::k, Daughters::pik>::Pdf()
    : PdfBase(Neutral::pi0, Bachelor::k, Daughters::pik) {
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_pi0_k_pik", "Signal Yield pi0, k, pik", "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_pi0_k_pik", "non TM Signal Yield pi0, k, pik",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_pi0_k_pik"
      "Cross Feed Yield pi0, k, pik",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_pi0_k_pik", "bu2Dst0Hst_D0pi0 Yield pi0, k, pik",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::pik>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_pi0_k_pik",
      "bu2Dst0Hst_D0gamma Yield pi0, k, pik",
      NeutralVars<Neutral::pi0>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::pik>::Get().daughtersSF(),
      0, NeutralVars<Neutral::pi0>::Get().maxYield() *
             NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_pi0_k_pik", "bu2D0H Yield pi0, k, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_pi0_k_pik", "bu2D0Hst Yield pi0, k, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_pi0_k_pik", "bd2DstH Yield pi0, k, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooRealVar>(
      new RooRealVar("missIdYield_pi0_k_pik", "missId yield k, pi, pik",
                     20 * DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  // "@0*(1-@1)*@2",
  //    RooArgList(
  //        SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get()
  //            .N_Dh(),
  //        NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().crossFeedRate(),
  //        NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik>::Pdf()
    : PdfBase(Neutral::gamma, Bachelor::pi, Daughters::pik) {
  std::cout << "Instantiated specific template Pdf<Neutral::gamma, "
               "Bachelor::pi, Daughters::pik>::Pdf()"
            << "\n";
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_gamma_pi_pik", "Signal Yield gamma, pi, pik",
      "@0*(1-@1-@2)*@3",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().selfCrossFeedRate(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_gamma_pi_pik", "non TM Signal Yield gamma, pi, pik",
      "@0*@1*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get().N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().selfCrossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_gamma_pi_pik", "Cross Feed Yield gamma, pi, pik",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_gamma_pi_pik",
      "bu2Dst0Hst_D0pi0 Yield gamma, pi, pik",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::pik>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_gamma_pi_pik",
      "bu2Dst0Hst_D0gamma Yield gamma, pi, pik",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
          DaughtersVars<Daughters::pik>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachelorSF() *
             DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_gamma_pi_pik", "bu2D0H Yield gamma, pi, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_gamma_pi_pik", "bu2D0Hst Yield gamma, pi, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_gamma_pi_pik", "bd2DstH Yield gamma, pi, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "missIdYield_gamma_pi_pik", "missId yield gamma, pi, pik",
      "@0*(1-@1)*@2",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::Get()
              .N_Dh(),
          NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().crossFeedRate(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get().missIdRate())));

  CreateRooAddPdf();
}

template <>
Pdf<Neutral::gamma, Bachelor::k, Daughters::pik>::Pdf()
    : PdfBase(Neutral::gamma, Bachelor::k, Daughters::pik) {
  signalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "signalYield_gamma_k_pik", "Signal Yield gamma, k, pik",
      "@0*(1-@1-@2)*@3",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().selfCrossFeedRate(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  nonTmSignalYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "nonTmSignalYield_gamma_k_pik", "non TM Signal Yield gamma, k, pik",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().selfCrossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  crossFeedYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "crossFeedYield_gamma_k_pik", "Cross Feed Yield gamma, k, pik",
      "@0*@1*@2",
      RooArgList(SpecialisedVars<Neutral::pi0, Bachelor::k, Daughters::pik>::Get().N_Dh(),
                 NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get().crossFeedRate(),
                 NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bu2Dst0Hst_D0pi0Yield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0pi0Yield_gamma_k_pik",
      "bu2Dst0Hst_D0pi0 Yield gamma, k, pik",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0pi0Expected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::pik>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  bu2Dst0Hst_D0gammaYield_ = std::unique_ptr<RooRealVar>(new RooRealVar(
      "bu2Dst0Hst_D0gammaYield_gamma_k_pik",
      "bu2Dst0Hst_D0gamma Yield gamma, k, pik",
      NeutralVars<Neutral::gamma>::Get().bu2Dst0Hst_D0gammaExpected() *
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
          DaughtersVars<Daughters::pik>::Get().daughtersSF(),
      0, NeutralVars<Neutral::gamma>::Get().maxYield() *
             NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachelorSF() *
             DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  bu2D0HYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HYield_gamma_k_pik", "bu2D0H Yield gamma, k, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::Get()
              .N_Dh_Bu2D0H(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bu2D0HstYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bu2D0HstYield_gamma_k_pik", "bu2D0Hst Yield gamma, k, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::Get()
              .N_Dh_Bu2D0Hst(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  bd2DstHYield_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      "bd2DstHYield_gamma_k_pik", "bd2DstH Yield gamma, k, pik", "@0*@1",
      RooArgList(
          SpecialisedVars<Neutral::gamma, Bachelor::k, Daughters::pik>::Get()
              .N_Dh_Bd2DstH(),
          NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().bachEff())));
  missIdYield_ = std::unique_ptr<RooRealVar>(
      new RooRealVar("missIdYield_gamma_k_pik", "missId yield gamma, k, pik",
                     20 * DaughtersVars<Daughters::pik>::Get().daughtersSF()));
  // "@0*(1-@1)*@2",
  // RooArgList(
  //     SpecialisedVars<Neutral::gamma, Bachelor::pi, Daughters::pik>::Get()
  //         .N_Dh(),
  //     NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get().crossFeedRate(),
  //     NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get().missIdRate())));

  CreateRooAddPdf();
}

