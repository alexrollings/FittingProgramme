#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0pi0 -------------------- //
    : Bu2Dst0h_D0pi0_sigma1Bu_(
          new RooRealVar(("Bu2Dst0h_D0pi0_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 2.2704e+01)),
                         // "", 2.2704e+01, 20, 25)),
      pdf1Bu_Bu2Dst0h_D0pi0_(
          ("pdf1Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0pi0_(
          ("pdf2Bu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          *Bu2Dst0h_D0pi0_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_D0pi0_(new RooAddPdf(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0pi0_, pdf2Bu_Bu2Dst0h_D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_D0pi0_fracPdf1Bu())),
      Bu2Dst0h_D0pi0_sigma1BuPartial_(),
      Bu2Dst0h_D0pi0_sigma2BuPartial_(),
      pdf1BuPartial_Bu2Dst0h_D0pi0_(),
      pdf2BuPartial_Bu2Dst0h_D0pi0_(),
      pdfBuPartial_Bu2Dst0h_D0pi0_(),
      N_tot_initVal_Bu2Dst0h_D0pi0_(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .initYieldFAVBu2Dst0h_D0pi0() *
                                      NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .orEffBu2Dst0h_D0pi0()
                                          .getVal()),
      pidEff_Bu2Dst0h_D0pi0_(("pidEff_Bu2Dst0h_D0pi0_" +
                              ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                 .c_str(),
                             "", 0.996436),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0pi0_meanBu_(("misId_Bu2Dst0h_D0pi0_meanBu_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", 5.2120e+03),
      misId_Bu2Dst0h_D0pi0_sigma1Bu_(("misId_Bu2Dst0h_D0pi0_sigma1Bu_" +
                                      ComposeName(uniqueId, Neutral::pi0,
                                                  Bachelor::pi))
                                         .c_str(),
                                     "", 3.5925e+01),
      misId_Bu2Dst0h_D0pi0_sigma2Bu_(("misId_Bu2Dst0h_D0pi0_sigma2Bu_" +
                                      ComposeName(uniqueId, Neutral::pi0,
                                                  Bachelor::pi))
                                         .c_str(),
                                     "", 2.5289e+01),
      misId_Bu2Dst0h_D0pi0_a1Bu_(("misId_Bu2Dst0h_D0pi0_a1Bu_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::pi))
                                     .c_str(),
                                 "", 3.9062e-02),
      misId_Bu2Dst0h_D0pi0_a2Bu_(("misId_Bu2Dst0h_D0pi0_a2Bu_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::pi))
                                     .c_str(),
                                 "", 1.0825e-01),
      misId_Bu2Dst0h_D0pi0_n1Bu_(),
      misId_Bu2Dst0h_D0pi0_n2Bu_(),
      pdf1Bu_misId_Bu2Dst0h_D0pi0_(),
      pdf2Bu_misId_Bu2Dst0h_D0pi0_(),
      misId_Bu2Dst0h_D0pi0_fracPdf1Bu_(),
      pdfBu_misId_Bu2Dst0h_D0pi0_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(), misId_Bu2Dst0h_D0pi0_meanBu_,
          misId_Bu2Dst0h_D0pi0_sigma1Bu_, misId_Bu2Dst0h_D0pi0_sigma2Bu_,
          misId_Bu2Dst0h_D0pi0_a1Bu_, misId_Bu2Dst0h_D0pi0_a2Bu_)),
      orEffMisId_Bu2Dst0h_D0pi0_(("orEffMisId_Bu2Dst0h_D0pi0_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::pi))
                                     .c_str(),
                                 "", 1),
      boxEffMisId_Bu2Dst0h_D0pi0_(("boxEffMisId_Bu2Dst0h_D0pi0_" +
                                   ComposeName(uniqueId, Neutral::pi0,
                                               Bachelor::pi))
                                      .c_str(),
                                  "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0pi0_(("buDeltaCutEffMisId_Bu2Dst0h_D0pi0_" +
                                          ComposeName(uniqueId, Neutral::pi0,
                                                      Bachelor::pi))
                                             .c_str(),
                                         "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0pi0_(("deltaCutEffMisId_Bu2Dst0h_D0pi0_" +
                                        ComposeName(uniqueId, Neutral::pi0,
                                                    Bachelor::pi))
                                           .c_str(),
                                       "", 1),
      // -------------------- Bu2Dst0h_D0gamma -------------------- //
      Bu2Dst0h_D0gamma_sigma1Bu_(
          new RooRealVar(("Bu2Dst0h_D0gamma_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 3.9828e+01)),
      Bu2Dst0h_D0gamma_sigma2Bu_(
          new RooRealVar(("Bu2Dst0h_D0gamma_sigma2Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 4.5331e+01)),
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
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_a2Bu())),
      Bu2Dst0h_D0gamma_sigmaBuPartial_(),
      pdfBuPartial_Bu2Dst0h_D0gamma_(),
      N_tot_initVal_Bu2Dst0h_D0gamma_(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .initYieldFAVBu2Dst0h_D0gamma() *
                                      NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .orEffBu2Dst0h_D0gamma()
                                          .getVal()),
      pidEff_Bu2Dst0h_D0gamma_(("pidEff_Bu2Dst0h_D0gamma_" +
                                ComposeName(uniqueId, Neutral::pi0,
                                            Bachelor::pi))
                                   .c_str(),
                               "", 0.993136),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(("misId_Bu2Dst0h_D0gamma_meanBu_" +
                                      ComposeName(uniqueId, Neutral::pi0,
                                                  Bachelor::pi))
                                         .c_str(),
                                     "", 5.2254e+03),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(("misId_Bu2Dst0h_D0gamma_sigma1Bu_" +
                                        ComposeName(uniqueId, Neutral::pi0,
                                                    Bachelor::pi))
                                           .c_str(),
                                       "", 7.0076e+01),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(("misId_Bu2Dst0h_D0gamma_sigma2Bu_" +
                                        ComposeName(uniqueId, Neutral::pi0,
                                                    Bachelor::pi))
                                           .c_str(),
                                       "", 5.7724e+01),
      misId_Bu2Dst0h_D0gamma_a1Bu_(("misId_Bu2Dst0h_D0gamma_a1Bu_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", 3.6424e-10),
      misId_Bu2Dst0h_D0gamma_a2Bu_(("misId_Bu2Dst0h_D0gamma_a2Bu_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", 2.2371e-10),
      misId_Bu2Dst0h_D0gamma_n1Bu_(),
      misId_Bu2Dst0h_D0gamma_n2Bu_(),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(),
      misId_Bu2Dst0h_D0gamma_fracPdf1Bu_(),
      pdfBu_misId_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0h_D0gamma_meanBu_, misId_Bu2Dst0h_D0gamma_sigma1Bu_,
          misId_Bu2Dst0h_D0gamma_sigma2Bu_, misId_Bu2Dst0h_D0gamma_a1Bu_,
          misId_Bu2Dst0h_D0gamma_a2Bu_)),
      orEffMisId_Bu2Dst0h_D0gamma_(("orEffMisId_Bu2Dst0h_D0gamma_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", 1),
      boxEffMisId_Bu2Dst0h_D0gamma_(("boxEffMisId_Bu2Dst0h_D0gamma_" +
                                     ComposeName(uniqueId, Neutral::pi0,
                                                 Bachelor::pi))
                                        .c_str(),
                                    "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(("deltaCutEffMisId_Bu2Dst0h_D0gamma_" +
                                          ComposeName(uniqueId, Neutral::pi0,
                                                      Bachelor::pi))
                                             .c_str(),
                                         "", 1),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaLBu_(("MisRec_sigmaLBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       "", 6.5198e+01),//, 20, 100),
      MisRec_sigmaRBu_(("MisRec_sigmaRBu_" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       "", 4.7849e+01),//, 20, 100),
      pdfBu_MisRec_(("pdfBu_MisRec_" +
                     ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_meanBu(),
                    MisRec_sigmaLBu_, MisRec_sigmaRBu_,
                    NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_aLBu(),
                    NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_aRBu()),
      MisRec_sigmaLBuPartial_(),
      MisRec_sigmaRBuPartial_(),
      pdfBuPartial_MisRec_(),
      N_tot_initVal_MisRec_(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .initYieldFAVMisRec() *
                                      NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .orEffMisRec()
                                          .getVal()),
      pidEff_Bu2Dst0h_D0gamma_WN_(0.995902),
      pidEff_Bu2Dst0h_D0pi0_WN_(0.996474),
      pidEff_Bu2D0hst_(0.995474),
      pidEff_Bd2Dsth_(0.994767),
      pidEff_MisRec_(
          ("pidEff_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "",
          (pidEff_Bu2Dst0h_D0gamma_.getVal() *
               NeutralVars<Neutral::pi0>::Get(uniqueId)
                   .fracMisRec_Bu2Dst0h_D0gamma() +
           pidEff_Bu2Dst0h_D0gamma_WN_ *
               NeutralVars<Neutral::pi0>::Get(uniqueId)
                   .fracMisRec_Bu2Dst0h_D0gamma_WN() +
           pidEff_Bu2Dst0h_D0pi0_WN_ *
               NeutralVars<Neutral::pi0>::Get(uniqueId)
                   .fracMisRec_Bu2Dst0h_D0pi0_WN() +
           pidEff_Bu2D0hst_ *
               NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec_Bu2D0hst() +
           pidEff_Bd2Dsth_ *
               NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec_Bd2Dsth()) /
              NeutralVars<Neutral::pi0>::Get(uniqueId).fracMisRec()),
      // -------------------- Mis-ID ------------------- //
      misId_MisRec_mean1Bu_(),
      misId_MisRec_mean2Bu_(),
      misId_MisRec_sigma1Bu_(),
      misId_MisRec_sigma2Bu_(),
      misId_MisRec_a2Bu_(),
      misId_MisRec_a1Bu_(),
      misId_MisRec_n2Bu_(),
      misId_MisRec_n1Bu_(),
      pdf1Bu_misId_MisRec_(),
      pdf2Bu_misId_MisRec_(),
      misId_MisRec_fracPdf1Bu_(),
      pdfBu_misId_MisRec_(nullptr),
      orEffMisId_MisRec_(),
      boxEffMisId_MisRec_(),
      buDeltaCutEffMisId_MisRec_(),
      deltaCutEffMisId_MisRec_(),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(("Bu2D0h_sigmaLBu_" +
                                       ComposeName(uniqueId, Neutral::pi0,
                                                   Bachelor::pi))
                                          .c_str(),
                                      // "", 3.3137e+01),
                                      "", 5.2446e+01),
                                      // "", 3.3137e+01, 10, 100),
      Bu2D0h_sigmaRBu_(("Bu2D0h_sigmaRBu_" +
                                       ComposeName(uniqueId, Neutral::pi0,
                                                   Bachelor::pi))
                                          .c_str(),
                                      // "", 4.0080e+01),
                                      "", 7.4012e+01),
                                      // "", 4.0080e+01, 10, 80),
      pdfBu_Bu2D0h_(("pdfBu_Bu2D0h_" +
                     ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                        .c_str(),
                    "", Configuration::Get().buDeltaMass(),
                    NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_meanBu(),
                    Bu2D0h_sigmaLBu_, Bu2D0h_sigmaRBu_,
                    NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aLBu(),
                    NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aRBu()),
      Bu2D0h_sigmaLBuPartial_(),
      Bu2D0h_sigmaRBuPartial_(),
      pdfBuPartial_Bu2D0h_(),
      N_tot_initVal_Bu2D0h_(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .initYieldFAVBu2D0h() *
                                      NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .orEffBu2D0h()
                                          .getVal()),
      pidEff_Bu2D0h_(("pidEff_Bu2D0h_" +
                      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                         .c_str(),
                     "", 0.995567),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2D0h_meanBu_(),
      misId_Bu2D0h_sigmaLBu_(),
      misId_Bu2D0h_sigmaRBu_(),
      misId_Bu2D0h_aLBu_(),
      misId_Bu2D0h_aRBu_(),
      pdfBu_misId_Bu2D0h_(),
      orEffMisId_Bu2D0h_(),
      boxEffMisId_Bu2D0h_(),
      buDeltaCutEffMisId_Bu2D0h_(),
      deltaCutEffMisId_Bu2D0h_(),
      // -------------------- PART REC -------------------- //
      partRec_D0pi0_sigmaLBu_(("partRec_D0pi0_sigmaLBu_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::pi))
                                       .c_str(),
                                   // "", 3.4464e+01),
                                   "", 4.9847e+01),
                                   // "", 3.4464e+01, 10, 50),
      partRec_D0pi0_sigmaRBu_(("partRec_D0pi0_sigmaRBu_" +
                                    ComposeName(uniqueId, Neutral::pi0,
                                                Bachelor::pi))
                                       .c_str(),
                                   "", 4.4688e+01),
      pdfBu_PartRec_D0pi0_(),
      partRec_D0gamma_sigmaLBu_(),
      partRec_D0gamma_sigmaRBu_(),
      pdfBu_PartRec_D0gamma_(),
      pdfBu_PartRec_(new RooCruijff(
          ("pdfBu_PartRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).partRec_D0pi0_meanBu(),
          partRec_D0pi0_sigmaLBu_, partRec_D0pi0_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).partRec_D0pi0_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).partRec_D0pi0_aRBu())),
      partRec_sigmaLBuPartial_(),
      partRec_sigmaRBuPartial_(),
      pdfBuPartial_PartRec_(),
      N_tot_initVal_PartRec_(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .initYieldFAVPartRec() *
                                      NeutralVars<Neutral::pi0>::Get(uniqueId)
                                          .orEffPartRec()
                                          .getVal()),
      pidEff_Bu2Dst0hst_D0pi0_(),
      pidEff_Bu2Dst0hst_D0gamma_(),
      pidEff_PartRec_(("pidEff_PartRec_" +
                                  ComposeName(uniqueId, Neutral::pi0,
                                              Bachelor::pi))
                                     .c_str(),
                                 "", 0.995881),
      // -------------------- Mis-ID ------------------- //
      misId_PartRec_meanBu_(),
      misId_PartRec_sigmaLBu_(),
      misId_PartRec_sigmaRBu_(),
      misId_PartRec_aLBu_(),
      misId_PartRec_aRBu_(),
      pdfBu_misId_PartRec_(),
      orEffMisId_PartRec_(),
      boxEffMisId_PartRec_(),
      buDeltaCutEffMisId_PartRec_(),
      deltaCutEffMisId_PartRec_() {
  SetMisIdEfficiencies(Mode::Bu2Dst0K_D0pi0, orEffMisId_Bu2Dst0h_D0pi0_,
                       boxEffMisId_Bu2Dst0h_D0pi0_,
                       buDeltaCutEffMisId_Bu2Dst0h_D0pi0_,
                       deltaCutEffMisId_Bu2Dst0h_D0pi0_);
  SetMisIdEfficiencies(Mode::Bu2Dst0K_D0gamma, orEffMisId_Bu2Dst0h_D0gamma_,
                       boxEffMisId_Bu2Dst0h_D0gamma_,
                       buDeltaCutEffMisId_Bu2Dst0h_D0gamma_,
                       deltaCutEffMisId_Bu2Dst0h_D0gamma_);
}
