#include "NeutralBachelorVars.h"
#include "Params.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : Bu2Dst0h_D0pi0_sigmaBu_(Params::Get().CreateFloating(
          "Bu2Dst0h_D0pi0_sigmaBu", uniqueId, Neutral::pi0, Bachelor::pi,
          2.2704e+01, 20, 25)),
      pdf1Bu_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_, pdf2Bu_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_fracPdf1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(nullptr),
      Bu2Dst0h_D0pi0_sigma3BuPartial_(nullptr),
      pdf1BuPartial_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_Bu2Dst0h_D0pi0_(),
      pdf3BuPartial_Bu2Dst0h_D0pi0_(),
      pdfBuPartial_Bu2Dst0h_D0pi0_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_meanBu", uniqueId, Neutral::pi0, Bachelor::pi,
          5.2120e+03, 4.05e+00, Systematic::misIdPi0PiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma1Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          3.5925e+01, 3.93e+00, Systematic::misIdPi0PiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_sigma2Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          2.5289e+01, 2.87e+00, Systematic::misIdPi0PiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_a1Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          3.9062e-02, 3.83e-02, Systematic::misIdPi0PiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0pi0_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0pi0_n1Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          1.0825e-01, 2.45e-02, Systematic::misIdPi0PiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0pi0_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0pi0_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bu2Dst0h_D0pi0_meanBu_,
          *misId_Bu2Dst0h_D0pi0_sigma1Bu_, *misId_Bu2Dst0h_D0pi0_sigma2Bu_,
          *misId_Bu2Dst0h_D0pi0_a1Bu_, *misId_Bu2Dst0h_D0pi0_n1Bu_)),
      misId_Bu2Dst0h_D0pi0_meanBuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_sigma1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_sigma2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_a2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_a1BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_n2BuPartial_(nullptr),
      misId_Bu2Dst0h_D0pi0_n1BuPartial_(nullptr),
      pdf1BuPartial_misId_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1BuPartial_(nullptr),
      pdfBuPartial_misId_Bu2Dst0h_D0pi0_(nullptr),
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(
          ("deltaCutEffMisId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", 1),
      deltaPartialCutEffMisId_Bu2Dst0h_D0pi0_(),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_sigma1Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          3.3594e+01, 9.76e-01, Systematic::crossFeedBuPdf, Sign::positive)),
      Bu2Dst0h_D0gamma_sigma2Bu_(Params::Get().CreateFixed(
          "Bu2Dst0h_D0gamma_sigma2Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          3.9267e+01, 1.22e+00, Systematic::crossFeedBuPdf, Sign::positive)),
      pdf1Bu_Bu2Dst0h_D0gamma_(),
      pdf2Bu_Bu2Dst0h_D0gamma_(),
      pdfBu_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigma1Bu_, *Bu2Dst0h_D0gamma_sigma2Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_n1Bu())),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(nullptr),
      pdfBuPartial_Bu2Dst0h_D0gamma_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_meanBu", uniqueId, Neutral::pi0, Bachelor::pi,
          5.2148e+03, 4.77e+00, Systematic::misIdGammaPiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigma1Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          5.3863e+01, 3.00e+00, Systematic::misIdGammaPiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_sigma2Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          6.2958e+01, 3.34e+00, Systematic::misIdGammaPiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_a1Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          9.3301e-10, 1.18e-02, Systematic::misIdGammaPiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_a2Bu_(nullptr),
      misId_Bu2Dst0h_D0gamma_n1Bu_(Params::Get().CreateFixed(
          "misId_Bu2Dst0h_D0gamma_n1Bu", uniqueId, Neutral::pi0, Bachelor::pi,
          3.8778e-08, 3.17e-02, Systematic::misIdGammaPiPdfBu, Sign::positive)),
      misId_Bu2Dst0h_D0gamma_n2Bu_(nullptr),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_misId_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), *misId_Bu2Dst0h_D0gamma_meanBu_,
          *misId_Bu2Dst0h_D0gamma_sigma1Bu_, *misId_Bu2Dst0h_D0gamma_sigma2Bu_,
          *misId_Bu2Dst0h_D0gamma_a1Bu_, *misId_Bu2Dst0h_D0gamma_n1Bu_)),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("deltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", 1),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(Params::Get().CreateFixed(
          "MisRec_sigmaLBu", uniqueId, Neutral::pi0, Bachelor::pi, 5.6386e+01,
          1.67e+00, Systematic::misRecBuPdf, Sign::positive)),
      MisRec_sigmaRBu_(Params::Get().CreateFixed(
          "MisRec_sigmaRBu", uniqueId, Neutral::pi0, Bachelor::pi, 5.7104e+01,
          7.42e-01, Systematic::misRecBuPdf, Sign::positive)),
      pdfBu_MisRec_(
          ("pdfBu_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_meanBu(),
          *MisRec_sigmaLBu_, *MisRec_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(nullptr),
      MisRec_sigmaRBuPartial_(nullptr),
      pdfBuPartial_MisRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_MisRec_mean1Bu_(nullptr),
      misId_MisRec_mean2Bu_(nullptr),
      misId_MisRec_sigma1Bu_(nullptr),
      misId_MisRec_sigma2Bu_(nullptr),
      misId_MisRec_a2Bu_(nullptr),
      misId_MisRec_a1Bu_(nullptr),
      misId_MisRec_n2Bu_(nullptr),
      misId_MisRec_n1Bu_(nullptr),
      pdf1Bu_misId_MisRec_(),
      pdf2Bu_misId_MisRec_(),
      misId_MisRec_fracPdf1Bu_(nullptr),
      pdfBu_misId_MisRec_(nullptr),
      misId_MisRec_meanBuPartial_(nullptr),
      misId_MisRec_sigmaLBuPartial_(nullptr),
      misId_MisRec_sigmaRBuPartial_(nullptr),
      misId_MisRec_aLBuPartial_(nullptr),
      misId_MisRec_aRBuPartial_(nullptr),
      pdfBuPartial_misId_MisRec_(),
      buDeltaCutEffMisId_MisRec_(),
      deltaCutEffMisId_MisRec_(),
      deltaPartialCutEffMisId_MisRec_(),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       // "", 3.3137e+01, 10, 100),
                       // Fixed from data
                       // "", 4.7982e+01),
                       // Fixed from data
                       "", 4.0526e+01),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       // "", 4.0080e+01, 10, 80),
                       // Fixed from data
                       // "", 4.1667e+01),
                       // Fixed from data
                       "", 3.2923e+01),
      pdfBu_Bu2D0h_(
          ("pdfBu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_meanBu(),
          Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(),
      Bu2D0h_sigmaRBuPartial_(),
      pdfBuPartial_Bu2D0h_(),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0h_meanBu_(),
      misId_Bu2D0h_sigmaLBu_(),
      misId_Bu2D0h_sigmaRBu_(),
      misId_Bu2D0h_aLBu_(),
      misId_Bu2D0h_aRBu_(),
      pdfBu_misId_Bu2D0h_(),
      misId_Bu2D0h_meanBuPartial_(),
      misId_Bu2D0h_sigmaLBuPartial_(),
      misId_Bu2D0h_sigmaRBuPartial_(),
      misId_Bu2D0h_aLBuPartial_(),
      misId_Bu2D0h_aRBuPartial_(),
      pdfBuPartial_misId_Bu2D0h_(),
      buDeltaCutEffMisId_Bu2D0h_(),
      deltaCutEffMisId_Bu2D0h_(),
      deltaPartialCutEffMisId_Bu2D0h_(),
      // -------------------- PART REC -------------------- //
      PartRec_D0pi0_sigmaLBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_sigmaLBu", uniqueId, Neutral::pi0, Bachelor::pi,
          4.6660e+01, 1.94e+00, Systematic::partRecBuPdf, Sign::positive)),
      PartRec_D0pi0_sigmaRBu_(Params::Get().CreateFixed(
          "PartRec_D0pi0_sigmaRBu", uniqueId, Neutral::pi0, Bachelor::pi,
          4.4688e+01, 6.17e+00, Systematic::partRecBuPdf, Sign::positive)),
      pdfBu_PartRec_D0pi0_(),
      PartRec_D0gamma_sigmaLBu_(nullptr),
      PartRec_D0gamma_sigmaRBu_(nullptr),
      pdfBu_PartRec_D0gamma_(),
      pdfBu_PartRec_(new RooCruijff(
          ("pdfBu_PartRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).PartRec_D0pi0_meanBu(),
          *PartRec_D0pi0_sigmaLBu_, *PartRec_D0pi0_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).PartRec_D0pi0_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).PartRec_D0pi0_aRBu())),
      PartRec_sigmaLBuPartial_(nullptr),
      PartRec_sigmaRBuPartial_(nullptr),
      pdfBuPartial_PartRec_(),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(nullptr),
      misId_PartRec_sigmaLBu_(nullptr),
      misId_PartRec_sigmaRBu_(nullptr),
      misId_PartRec_aLBu_(nullptr),
      misId_PartRec_aRBu_(nullptr),
      pdfBu_misId_PartRec_(),
      misId_PartRec_meanBuPartial_(nullptr),
      misId_PartRec_sigmaLBuPartial_(nullptr),
      misId_PartRec_sigmaRBuPartial_(nullptr),
      misId_PartRec_aLBuPartial_(nullptr),
      misId_PartRec_aRBuPartial_(nullptr),
      pdfBuPartial_misId_PartRec_(),
      buDeltaCutEffMisId_PartRec_(),
      deltaCutEffMisId_PartRec_(),
      deltaPartialCutEffMisId_PartRec_() {
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0pi0;
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0K_D0pi0, Bachelor::pi,
                                       mapMisId_Bu2Dst0h_D0pi0, true);
  buDeltaCutEffMisId_Bu2Dst0h_D0pi0_.setVal(mapMisId_Bu2Dst0h_D0pi0["buDeltaCutEff"]);
  deltaCutEffMisId_Bu2Dst0h_D0pi0_.setVal(mapMisId_Bu2Dst0h_D0pi0["deltaCutEff"]);
  std::map<std::string, double> mapMisId_Bu2Dst0h_D0gamma;
  Configuration::Get().ReturnBoxEffs(Mode::Bu2Dst0K_D0gamma, Bachelor::pi,
                                       mapMisId_Bu2Dst0h_D0gamma, true);
  buDeltaCutEffMisId_Bu2Dst0h_D0gamma_.setVal(mapMisId_Bu2Dst0h_D0gamma["buDeltaCutEff"]);
  deltaCutEffMisId_Bu2Dst0h_D0gamma_.setVal(mapMisId_Bu2Dst0h_D0gamma["deltaCutEff"]);
}
