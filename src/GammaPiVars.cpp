#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_sigmaLBu_(new RooPolyVar(
          ("Bu2Dst0h_Dst02D0gamma_sigmaLBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("SigmaL of Bu PDF of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .Bu2Dst0h_Dst02D0gamma_a0SigmaLBu(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .Bu2Dst0h_Dst02D0gamma_a1SigmaLBu(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .Bu2Dst0h_Dst02D0gamma_a2SigmaLBu()))),
      Bu2Dst0h_Dst02D0gamma_sigmaRBu_(
          new RooPolyVar(("Bu2Dst0h_Dst02D0gamma_sigmaRBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0h_Dst02D0gamma " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0gamma_a0SigmaRBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0gamma_a1SigmaRBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0gamma_a2SigmaRBu()))),
      pdfLBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_mean1Bu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaLBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_nLBu()),
      pdfRBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_mean1Bu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_aRBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_nRBu()),
      pdfLRBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfLRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma of 2 CBs in Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0gamma_,
                    pdfRBu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_fracLRPdfBu()),
      sigmaWideBu_Bu2Dst0h_Dst02D0gamma_(new RooRealVar(
          ("sigmaWideBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("SigmaWide of Bu PDF of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          200)),
      pdfWideBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfWideBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF wide gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_mean1Bu(),
          *sigmaWideBu_Bu2Dst0h_Dst02D0gamma_),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma of 2 CBs in Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfWideBu_Bu2Dst0h_Dst02D0gamma_,
                    pdfLRBu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_fracWidePdfBu()),
      pdf_Bu2Dst0h_Dst02D0gamma_(
          ("pdf_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0h_Dst02D0gamma(),
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0gamma_,
                              Configuration::Get().buMass())),
      // -------------------- PARTIAL PI0 -------------------- //
      Bu2Dst0h_Dst02D0pi0_sigmaLBu_(
          new RooPolyVar(("Bu2Dst0h_Dst02D0pi0_sigmaLBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaL of Bu PDF of Bu2Dst0h_Dst02D0pi0 Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a0SigmaLBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a1SigmaLBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a2SigmaLBu()))),
      Bu2Dst0h_Dst02D0pi0_sigmaRBu_(
          new RooPolyVar(("Bu2Dst0h_Dst02D0pi0_sigmaRBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0h_Dst02D0pi0 " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a0SigmaRBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a1SigmaRBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a2SigmaRBu()))),
      pdfLBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_mean1Bu(),
          *Bu2Dst0h_Dst02D0pi0_sigmaLBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_nLBu()),
      pdfRBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_mean2Bu(),
          *Bu2Dst0h_Dst02D0pi0_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_aRBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_nRBu()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0pi0_, pdfRBu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_fracLRPdfBu()),
      pdf_Bu2Dst0h_Dst02D0pi0_(
          ("pdf_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0h_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      overRec_sigmaLBu_(new RooPolyVar(
          ("overRec_sigmaLBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("SigmaL of Bu PDF of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_a0SigmaLBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_a1SigmaLBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .overRec_a2SigmaLBu()))),
      overRec_sigmaRBu_(new RooPolyVar(
          ("overRec_sigmaRBu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("SigmaR of Bu PDF of overRec " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_a0SigmaRBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_a1SigmaRBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .overRec_a2SigmaRBu()))),
      pdfLBu_overRec_(
          ("pdfLBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_mean1Bu(),
          *overRec_sigmaLBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_nLBu()),
      pdfRBu_overRec_(
          ("pdfRBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_mean2Bu(),
          *overRec_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_aRBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_nRBu()),
      pdfBu_overRec_(
          ("pdfBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_overRec_, pdfRBu_overRec_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_fracLRPdfBu()),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // ------------------- Pi0 PART RECONSTRUCTED BKG ------------------- //
      Bu2Dst0hst_Dst02D0pi0_sigmaLBu_(
          new RooPolyVar(("Bu2Dst0hst_Dst02D0pi0_sigmaLBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaL of Bu PDF of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0pi0_a0SigmaLBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0pi0_a1SigmaLBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0pi0_a2SigmaLBu()))),
      Bu2Dst0hst_Dst02D0pi0_sigmaRBu_(
          new RooPolyVar(("Bu2Dst0hst_Dst02D0pi0_sigmaRBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0hst_Dst02D0pi0 " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0pi0_a0SigmaRBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0pi0_a1SigmaRBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0pi0_a2SigmaRBu()))),
      pdfLBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0pi0_meanBu(),
          *Bu2Dst0hst_Dst02D0pi0_sigmaLBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_Dst02D0pi0_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_Dst02D0pi0_nLBu()),
      pdfRBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0pi0_meanBu(),
          *Bu2Dst0hst_Dst02D0pi0_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_Dst02D0pi0_aRBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_Dst02D0pi0_nRBu()),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0hst_Dst02D0pi0_, pdfRBu_Bu2Dst0hst_Dst02D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0pi0_fracLRPdfBu()),
      pdf_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_Bu2Dst0hst_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0hst_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- Gamma PART RECONSTRUCTED BKG --------------------
      Bu2Dst0hst_Dst02D0gamma_sigmaLBu_(
          new RooPolyVar(("Bu2Dst0hst_Dst02D0gamma_sigmaLBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaL of Bu PDF of Bu2Dst0hst_Dst02D0gamma Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0gamma_a0SigmaLBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0gamma_a1SigmaLBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0gamma_a2SigmaLBu()))),
      Bu2Dst0hst_Dst02D0gamma_sigmaRBu_(
          new RooPolyVar(("Bu2Dst0hst_Dst02D0gamma_sigmaRBu_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0hst_Dst02D0gamma " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0gamma_a0SigmaRBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0gamma_a1SigmaRBu(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .Bu2Dst0hst_Dst02D0gamma_a2SigmaRBu()))),
      pdfLBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfLBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0gamma_meanBu(),
          *Bu2Dst0hst_Dst02D0gamma_sigmaLBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_Dst02D0gamma_aLBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_Dst02D0gamma_nLBu()),
      pdfRBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfRBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0gamma_meanBu(),
          *Bu2Dst0hst_Dst02D0gamma_sigmaRBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_Dst02D0gamma_aRBu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0hst_Dst02D0gamma_nRBu()),
      pdfBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0hst_Dst02D0gamma_, pdfRBu_Bu2Dst0hst_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0gamma_fracLRPdfBu()),
      pdf_Bu2Dst0hst_Dst02D0gamma_(
          ("pdf_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0hst_Dst02D0gamma(),
          RooFit::Conditional(pdfBu_Bu2Dst0hst_Dst02D0gamma_,
                              Configuration::Get().buMass())),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      sigma1Bu_misRec_(new RooPolyVar(
          ("sigma1Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma1 of Bu PDF of misRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_a0Sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_a1Sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_a2Sigma1Bu()))),
      sigma2Bu_misRec_(new RooPolyVar(
          ("sigma2Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma2 of Bu PDF of misRec " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_a0Sigma2Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_a1Sigma2Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_a2Sigma2Bu()))),
      sigma3Bu_misRec_(new RooPolyVar(
          ("sigma3Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma3 of Bu PDF of misRec " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_a0Sigma3Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_a1Sigma3Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_a2Sigma3Bu()))),
      pdf1Bu_misRec_(
          ("pdf1Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("misRec Bu PDF 1 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_mean1Bu(),
          *sigma1Bu_misRec_),
      pdf2Bu_misRec_(
          ("pdf2Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("misRec Bu PDF 2 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_mean2Bu(),
          *sigma2Bu_misRec_),
      pdf3Bu_misRec_(
          ("pdf3Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("misRec Bu PDF 3 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_mean3Bu(),
          *sigma3Bu_misRec_),
      pdfBu_misRec_(
          ("pdfBu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("misRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdf1Bu_misRec_, pdf2Bu_misRec_, pdf3Bu_misRec_),
          RooArgSet(
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_frac1PdfBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_frac2PdfBu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_frac3PdfBu())),
      pdf_misRec_(
          ("pdf_misRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("misRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_misRec(),
          RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}
