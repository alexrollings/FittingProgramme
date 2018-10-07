#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaLBu_Bu2Dst0h_Dst02D0gamma_(new RooPolyVar(
          ("sigmaLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("SigmaL of Bu PDF of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .a0SigmaLBu_Bu2Dst0h_Dst02D0gamma(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .a1SigmaLBu_Bu2Dst0h_Dst02D0gamma(),
                     NeutralVars<Neutral::gamma>::Get(uniqueId)
                         .a2SigmaLBu_Bu2Dst0h_Dst02D0gamma()))),
      sigmaRBu_Bu2Dst0h_Dst02D0gamma_(
          new RooPolyVar(("sigmaRBu_Bu2Dst0h_Dst02D0gamma_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0h_Dst02D0gamma " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a0SigmaRBu_Bu2Dst0h_Dst02D0gamma(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a1SigmaRBu_Bu2Dst0h_Dst02D0gamma(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a2SigmaRBu_Bu2Dst0h_Dst02D0gamma()))),
      pdfLBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaLBu_Bu2Dst0h_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aLBu_Bu2Dst0h_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nLBu_Bu2Dst0h_Dst02D0gamma()),
      pdfRBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaRBu_Bu2Dst0h_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aRBu_Bu2Dst0h_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nRBu_Bu2Dst0h_Dst02D0gamma()),
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
              .fracLRPdfBu_Bu2Dst0h_Dst02D0gamma()),
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
              .mean1Bu_Bu2Dst0h_Dst02D0gamma(),
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
              .fracWidePdfBu_Bu2Dst0h_Dst02D0gamma()),
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
      sigmaLBu_Bu2Dst0h_Dst02D0pi0_(
          new RooPolyVar(("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaL of Bu PDF of Bu2Dst0h_Dst02D0pi0 Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a0SigmaLBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a1SigmaLBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a2SigmaLBu_Bu2Dst0h_Dst02D0pi0()))),
      sigmaRBu_Bu2Dst0h_Dst02D0pi0_(
          new RooPolyVar(("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0h_Dst02D0pi0 " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a0SigmaRBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a1SigmaRBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a2SigmaRBu_Bu2Dst0h_Dst02D0pi0()))),
      pdfLBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaLBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aLBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nLBu_Bu2Dst0h_Dst02D0pi0()),
      pdfRBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean2Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aRBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nRBu_Bu2Dst0h_Dst02D0pi0()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0pi0_, pdfRBu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0h_Dst02D0pi0()),
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
      sigmaLBu_overRec_(new RooPolyVar(
          ("sigmaLBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("SigmaL of Bu PDF of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).a0SigmaLBu_overRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).a1SigmaLBu_overRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .a2SigmaLBu_overRec()))),
      sigmaRBu_overRec_(new RooPolyVar(
          ("sigmaRBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("SigmaR of Bu PDF of overRec " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).a0SigmaRBu_overRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).a1SigmaRBu_overRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .a2SigmaRBu_overRec()))),
      pdfLBu_overRec_(
          ("pdfLBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean1Bu_overRec(),
          *sigmaLBu_overRec_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aLBu_overRec(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).nLBu_overRec()),
      pdfRBu_overRec_(
          ("pdfRBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean2Bu_overRec(),
          *sigmaRBu_overRec_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aRBu_overRec(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).nRBu_overRec()),
      pdfBu_overRec_(
          ("pdfBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_overRec_, pdfRBu_overRec_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).fracLRPdfBu_overRec()),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // ------------------- Pi0 PART RECONSTRUCTED BKG ------------------- //
      a0SigmaBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a0SigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a0 of sigma of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // 40, 30, 50),
          25, -100, 100),
      a1SigmaBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a1SigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a1 of sigma of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          0.09, -10, 10),
      a2SigmaBu_Bu2Dst0hst_Dst02D0pi0_(
          ("a2SigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a2 of sigma of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          0.0036, -0.01, 0.01),
      sigmaBu_Bu2Dst0hst_Dst02D0pi0_(new RooPolyVar(
          ("sigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0SigmaBu_Bu2Dst0hst_Dst02D0pi0_,
                     a1SigmaBu_Bu2Dst0hst_Dst02D0pi0_ /*, a2SigmaBu_Bu2Dst0hst_Dst02D0pi0_ */))),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanBu_Bu2Dst0hst_Dst02D0pi0(),
          *sigmaBu_Bu2Dst0hst_Dst02D0pi0_),
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
      sigmaLBu_Bu2Dst0hst_Dst02D0gamma_(
          new RooPolyVar(("sigmaLBu_Bu2Dst0hst_Dst02D0gamma_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaL of Bu PDF of Bu2Dst0hst_Dst02D0gamma Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a0SigmaLBu_Bu2Dst0hst_Dst02D0gamma(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a1SigmaLBu_Bu2Dst0hst_Dst02D0gamma(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a2SigmaLBu_Bu2Dst0hst_Dst02D0gamma()))),
      // pdfBu_Bu2Dst0hst_Dst02D0gamma_(
      //     ("pdfBu_Bu2Dst0hst_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     ("Bu2Dst0hst_Dst02D0gamma Bu PDF " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .meanBu_Bu2Dst0hst_Dst02D0gamma(),
      //     *sigmaLBu_Bu2Dst0hst_Dst02D0gamma_),
      sigmaRBu_Bu2Dst0hst_Dst02D0gamma_(
          new RooPolyVar(("sigmaRBu_Bu2Dst0hst_Dst02D0gamma_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0hst_Dst02D0gamma " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a0SigmaRBu_Bu2Dst0hst_Dst02D0gamma(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a1SigmaRBu_Bu2Dst0hst_Dst02D0gamma(),
                                    NeutralVars<Neutral::gamma>::Get(uniqueId)
                                        .a2SigmaRBu_Bu2Dst0hst_Dst02D0gamma()))),
      pdfLBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfLBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0hst_Dst02D0gamma(),
          *sigmaLBu_Bu2Dst0hst_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aLBu_Bu2Dst0hst_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).nLBu_Bu2Dst0hst_Dst02D0gamma()),
      pdfRBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfRBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0hst_Dst02D0gamma(),
          *sigmaRBu_Bu2Dst0hst_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aRBu_Bu2Dst0hst_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).nRBu_Bu2Dst0hst_Dst02D0gamma()),
      pdfBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0hst_Dst02D0gamma_, pdfRBu_Bu2Dst0hst_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0hst_Dst02D0gamma()),
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
              NeutralVars<Neutral::gamma>::Get(uniqueId).a0Sigma1Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).a1Sigma1Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).a2Sigma1Bu_misRec()))),
      sigma2Bu_misRec_(new RooPolyVar(
          ("sigma2Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma2 of Bu PDF of misRec " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).a0Sigma2Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).a1Sigma2Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).a2Sigma2Bu_misRec()))),
      sigma3Bu_misRec_(new RooPolyVar(
          ("sigma3Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma3 of Bu PDF of misRec " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::gamma>::Get(uniqueId).a0Sigma3Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).a1Sigma3Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).a2Sigma3Bu_misRec()))),
      pdf1Bu_misRec_(
          ("pdf1Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("misRec Bu PDF 1 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean1Bu_misRec(),
          *sigma1Bu_misRec_),
      pdf2Bu_misRec_(
          ("pdf2Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("misRec Bu PDF 2 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean2Bu_misRec(),
          *sigma2Bu_misRec_),
      pdf3Bu_misRec_(
          ("pdf3Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("misRec Bu PDF 3 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean3Bu_misRec(),
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
              NeutralVars<Neutral::gamma>::Get(uniqueId).frac1PdfBu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).frac2PdfBu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).frac3PdfBu_misRec())),
      pdf_misRec_(
          ("pdf_misRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("misRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_misRec(),
          RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaLBu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaL of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      sigmaRBu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      pdfLBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaLBu_Bu2Dst0h_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aLBu_Bu2Dst0h_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nLBu_Bu2Dst0h_Dst02D0gamma()),
      pdfRBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaRBu_Bu2Dst0h_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aRBu_Bu2Dst0h_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nRBu_Bu2Dst0h_Dst02D0gamma()),
      pdfLRBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfLRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF of 2 CBs " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0gamma_,
                    pdfRBu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0h_Dst02D0gamma()),
      sigmaWideBu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaWideBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaWide of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaWideBu_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      pdfWideBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfWideBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF wide gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaWideBu_Bu2Dst0h_Dst02D0gamma_),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfWideBu_Bu2Dst0h_Dst02D0gamma_,
                    pdfLRBu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracWidePdfBu_Bu2Dst0h_Dst02D0gamma()),
      pdf_Bu2Dst0h_Dst02D0gamma_(
          ("pdf_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0h_Dst02D0gamma(),
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0gamma_,
                              Configuration::Get().buMass())),
      // -------------------- PARTIAL PI0 -------------------- //
      sigmaLBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaL of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      sigmaRBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      pdfLBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaLBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aLBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nLBu_Bu2Dst0h_Dst02D0pi0()),
      pdfRBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean2Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aRBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nRBu_Bu2Dst0h_Dst02D0pi0()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0pi0_, pdfRBu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0h_Dst02D0pi0()),
      pdf_Bu2Dst0h_Dst02D0pi0_(
          ("pdf_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0h_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      sigmaLBu_overRec_(new RooFormulaVar(
          ("sigmaLBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaL of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_overRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_overRec()))),
      sigmaRBu_overRec_(new RooFormulaVar(
          ("sigmaRBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_overRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_overRec()))),
      pdfLBu_overRec_(
          ("pdfLBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean1Bu_overRec(),
          *sigmaLBu_overRec_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aLBu_overRec(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).nLBu_overRec()),
      pdfRBu_overRec_(
          ("pdfRBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean2Bu_overRec(),
          *sigmaRBu_overRec_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aRBu_overRec(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).nRBu_overRec()),
      pdfBu_overRec_(
          ("pdfBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_overRec_, pdfRBu_overRec_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).fracLRPdfBu_overRec()),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // ------------------ Pi0 PART RECONSTRUCTED BKG ------------------ //
      a0SigmaBu_Bu2Dst0hst_Dst02D0pi0_(),
      a1SigmaBu_Bu2Dst0hst_Dst02D0pi0_(),
      a2SigmaBu_Bu2Dst0hst_Dst02D0pi0_(),
      sigmaBu_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2Dst0hst_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0pi0()))),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0hst_Dst02D0pi0(),
          *sigmaBu_Bu2Dst0hst_Dst02D0pi0_),
      pdf_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0hst_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0hst_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // ------------------ Gamma PART RECONSTRUCTED BKG ------------------ //
      sigmaLBu_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaLBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaL of Bu2Dst0hst_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_Bu2Dst0hst_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0gamma()))),
      // pdfBu_Bu2Dst0hst_Dst02D0gamma_(
      //     ("pdfBu_Bu2Dst0hst_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0hst_Dst02D0gamma Bu PDF " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .meanBu_Bu2Dst0hst_Dst02D0gamma(),
      //     *sigmaLBu_Bu2Dst0hst_Dst02D0gamma_),
      sigmaRBu_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaRBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0hst_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_Bu2Dst0hst_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0gamma()))),
      pdfLBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfLBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0hst_Dst02D0gamma(),
          *sigmaLBu_Bu2Dst0hst_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aLBu_Bu2Dst0hst_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nLBu_Bu2Dst0hst_Dst02D0gamma()),
      pdfRBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfRBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0hst_Dst02D0gamma(),
          *sigmaRBu_Bu2Dst0hst_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aRBu_Bu2Dst0hst_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nRBu_Bu2Dst0hst_Dst02D0gamma()),
      pdfBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0hst_Dst02D0gamma_,
          pdfRBu_Bu2Dst0hst_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0hst_Dst02D0gamma()),
      pdf_Bu2Dst0hst_Dst02D0gamma_(
          ("pdf_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0hst_Dst02D0gamma(),
          RooFit::Conditional(pdfBu_Bu2Dst0hst_Dst02D0gamma_,
                              Configuration::Get().buMass())),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      sigma1Bu_misRec_(new RooFormulaVar(
          ("sigma1Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma1 of Bu PDF of misRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigma1Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_misRec()))),
      sigma2Bu_misRec_(new RooFormulaVar(
          ("sigma2Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma2 of Bu PDF of misRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigma2Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_misRec()))),
      sigma3Bu_misRec_(new RooFormulaVar(
          ("sigma3Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma3 of Bu PDF of misRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigma3Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_misRec()))),
      pdf1Bu_misRec_(
          ("pdf1Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF 1 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean1Bu_misRec(),
          *sigma1Bu_misRec_),
      pdf2Bu_misRec_(
          ("pdf2Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF 2 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean2Bu_misRec(),
          *sigma2Bu_misRec_),
      pdf3Bu_misRec_(
          ("pdf3Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF 3 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean3Bu_misRec(),
          *sigma3Bu_misRec_),
      pdfBu_misRec_(
          ("pdfBu_misRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdf1Bu_misRec_, pdf2Bu_misRec_, pdf3Bu_misRec_),
          RooArgSet(
              NeutralVars<Neutral::gamma>::Get(uniqueId).frac1PdfBu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).frac2PdfBu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).frac3PdfBu_misRec())),
      pdf_misRec_(
          ("pdf_misRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_misRec(),
          RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaLBu_Bu2Dst0h_Dst02D0pi0_(
          new RooPolyVar(("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("SigmaL of Bu PDF of Bu2Dst0h_Dst02D0pi0 Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a0SigmaLBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a1SigmaLBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a2SigmaLBu_Bu2Dst0h_Dst02D0pi0()))),
      sigmaRBu_Bu2Dst0h_Dst02D0pi0_(
          new RooPolyVar(("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0h_Dst02D0pi0 " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a0SigmaRBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a1SigmaRBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a2SigmaRBu_Bu2Dst0h_Dst02D0pi0()))),
      pdfLBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaLBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).aLBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).nLBu_Bu2Dst0h_Dst02D0pi0()),
      pdfRBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).aRBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).nRBu_Bu2Dst0h_Dst02D0pi0()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0pi0_, pdfRBu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0h_Dst02D0pi0()),
      pdf_Bu2Dst0h_Dst02D0pi0_(
          ("pdf_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .pdfDelta_Bu2Dst0h_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // ------------------ NO CROSS FEED BECAUSE OF VETO ------------------ //
      sigmaLBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      sigmaRBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      pdfLBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfRBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfLRBu_Bu2Dst0h_Dst02D0gamma_(),
      sigmaWideBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      pdfWideBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(),
      pdf_Bu2Dst0h_Dst02D0gamma_(),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      // sigmaBu_overRec_(
      //     new RooRealVar(("sigmaBu_overRec_" +
      //                     ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //                        .c_str(),
      //                    ("Sigma of overRec Gaussian " +
      //                     ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //                        .c_str(),
      //                    100, 50, 150)),
      // pdfBu_overRec_(
      //     ("pdfBu_overRec_" + ComposeName(uniqueId, Neutral::pi0,
      //     Bachelor::pi))
      //         .c_str(),
      //     ("overRec Bu PDF " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_overRec(),
      //     *sigmaBu_overRec_),
      // pdf_overRec_(
      //     ("pdf_overRec_" + ComposeName(uniqueId, Neutral::pi0,
      //     Bachelor::pi))
      //         .c_str(),
      //     ("overRec 2D PDF " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_overRec(),
      //     RooFit::Conditional(pdfBu_overRec_,
      //     Configuration::Get().buMass())),
      sigmaLBu_overRec_(nullptr),
      sigmaRBu_overRec_(nullptr),
      pdfLBu_overRec_(),
      pdfRBu_overRec_(),
      pdfBu_overRec_(),
      pdf_overRec_(),
      // -------------------- Pi0 PART RECONSTRUCTED BKG --------------------
      a0SigmaBu_Bu2Dst0hst_Dst02D0pi0_(("a0SigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            ("a0 of sigma of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            // 40, 30, 50),
                            70, -100, 100),
      a1SigmaBu_Bu2Dst0hst_Dst02D0pi0_(("a1SigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            ("a1 of sigma of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            0.07, -10, 10),
      a2SigmaBu_Bu2Dst0hst_Dst02D0pi0_(("a2SigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            ("a2 of sigma of Bu2Dst0hst_Dst02D0pi0 m[Bu] PDF " +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            0.0036, -0.01, 0.01),
      sigmaBu_Bu2Dst0hst_Dst02D0pi0_(new RooPolyVar(
          ("sigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0SigmaBu_Bu2Dst0hst_Dst02D0pi0_,
                     a1SigmaBu_Bu2Dst0hst_Dst02D0pi0_ /*, a2SigmaBu_Bu2Dst0hst_Dst02D0pi0_ */))),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_Bu2Dst0hst_Dst02D0pi0(),
          *sigmaBu_Bu2Dst0hst_Dst02D0pi0_),
      pdf_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_Bu2Dst0hst_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0hst_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- Gamma PART RECONSTRUCTED BKG --------------------
      sigmaLBu_Bu2Dst0hst_Dst02D0gamma_(nullptr),
      sigmaRBu_Bu2Dst0hst_Dst02D0gamma_(nullptr),
      pdfLBu_Bu2Dst0hst_Dst02D0gamma_(),
      pdfRBu_Bu2Dst0hst_Dst02D0gamma_(),
      pdfBu_Bu2Dst0hst_Dst02D0gamma_(),
      pdf_Bu2Dst0hst_Dst02D0gamma_(),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      sigma1Bu_misRec_(nullptr),
      sigma2Bu_misRec_(nullptr),
      sigma3Bu_misRec_(nullptr),
      pdf1Bu_misRec_(),
      pdf2Bu_misRec_(),
      pdf3Bu_misRec_(),
      pdfBu_misRec_(),
      pdf_misRec_() {}
// sigmaBu_misRec_(("sigmaBu_misRec_" +
//                  ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//                     .c_str(),
//                 ("Sigma of misRec Gaussian " +
//                  ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//                     .c_str(),
//                 60, 40, 80),
// pdfBu_misRec_(
//     ("pdfBu_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     ("misRec Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     Configuration::Get().buMass(),
//     NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_misRec(),
//     sigmaBu_misRec_),
// pdf_misRec_(
//     ("pdf_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     ("misRec 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_misRec(),
//     RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaLBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("SigmaL of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      sigmaRBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      pdfLBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaLBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).aLBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).nLBu_Bu2Dst0h_Dst02D0pi0()),
      pdfRBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).aRBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).nRBu_Bu2Dst0h_Dst02D0pi0()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0pi0_, pdfRBu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0h_Dst02D0pi0()),
      pdf_Bu2Dst0h_Dst02D0pi0_(
          ("pdf_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .pdfDelta_Bu2Dst0h_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // ------------------ NO CROSS FEED BECAUSE OF VETO ------------------ //
      sigmaLBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      sigmaRBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      pdfLBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfRBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfLRBu_Bu2Dst0h_Dst02D0gamma_(),
      sigmaWideBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      pdfWideBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(),
      pdf_Bu2Dst0h_Dst02D0gamma_(),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      // sigmaBu_overRec_(new RooFormulaVar(
      //     ("sigmaBu_overRec_" +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
      //         .c_str(),
      //     ("Sigma of overRec Gaussian " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgList(
      //         NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
      //             .sigmaBu_overRec(),
      //         NeutralVars<Neutral::pi0>::Get(uniqueId)
      //             .relativeBuWidth_overRec()))),
      // pdfBu_overRec_(
      //     ("pdfBu_overRec_" + ComposeName(uniqueId, Neutral::pi0,
      //     Bachelor::k))
      //         .c_str(),
      //     ("overRec Bu PDF " + ComposeName(uniqueId, Neutral::pi0,
      //     Bachelor::k))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_overRec(),
      //     *sigmaBu_overRec_),
      // pdf_overRec_(
      //     ("pdf_overRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
      //         .c_str(),
      //     ("overRec 2D PDF " + ComposeName(uniqueId, Neutral::pi0,
      //     Bachelor::k))
      //         .c_str(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_overRec(),
      //     RooFit::Conditional(pdfBu_overRec_,
      //     Configuration::Get().buMass())),
      sigmaLBu_overRec_(nullptr),
      sigmaRBu_overRec_(nullptr),
      pdfLBu_overRec_(),
      pdfRBu_overRec_(),
      pdfBu_overRec_(),
      pdf_overRec_(),
      // ------------------- Pi0 PART RECONSTRUCTED BKG ------------------- //
      a0SigmaBu_Bu2Dst0hst_Dst02D0pi0_(),
      a1SigmaBu_Bu2Dst0hst_Dst02D0pi0_(),
      a2SigmaBu_Bu2Dst0hst_Dst02D0pi0_(),
      sigmaBu_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2Dst0hst_Dst02D0pi0(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0pi0()))),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_Bu2Dst0hst_Dst02D0pi0(),
          *sigmaBu_Bu2Dst0hst_Dst02D0pi0_),
      pdf_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf_Bu2Dst0hst_Dst02D0pi0_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_Bu2Dst0hst_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0hst_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- Gamma PART RECONSTRUCTED BKG --------------------
      sigmaLBu_Bu2Dst0hst_Dst02D0gamma_(nullptr),
      sigmaRBu_Bu2Dst0hst_Dst02D0gamma_(nullptr),
      pdfLBu_Bu2Dst0hst_Dst02D0gamma_(),
      pdfRBu_Bu2Dst0hst_Dst02D0gamma_(),
      pdfBu_Bu2Dst0hst_Dst02D0gamma_(),
      pdf_Bu2Dst0hst_Dst02D0gamma_(),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      sigma1Bu_misRec_(nullptr),
      sigma2Bu_misRec_(nullptr),
      sigma3Bu_misRec_(nullptr),
      pdf1Bu_misRec_(),
      pdf2Bu_misRec_(),
      pdf3Bu_misRec_(),
      pdfBu_misRec_(),
      pdf_misRec_() {}
// sigmaBu_misRec_(
//     ("sigmaBu_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
//         .c_str(),
//     ("Sigma of misRec Gaussian " +
//      ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
//         .c_str(),
//     60, 40, 80),
// pdfBu_misRec_(
//     ("pdfBu_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
//         .c_str(),
//     ("misRec Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
//         .c_str(),
//     Configuration::Get().buMass(),
//     NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_misRec(),
//     sigmaBu_misRec_),
// pdf_misRec_(
//     ("pdf_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
//         .c_str(),
//     ("misRec 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
//         .c_str(),
//     NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_misRec(),
//     RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}
