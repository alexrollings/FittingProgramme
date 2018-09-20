#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : a0SigmaBu_Bu2Dst0h_Dst02D0gamma_(
          ("a0SigmaBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a0 of sigma of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // 100, 0, 150),
          // -6.1, -100, 100),
          15, -100, 100),
      a1SigmaBu_Bu2Dst0h_Dst02D0gamma_(
          ("a1SigmaBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a1 of sigma of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          0.09, -10, 10),
      // -0.36, -10, 10),
      a2SigmaBu_Bu2Dst0h_Dst02D0gamma_(
          ("a2SigmaBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a2 of sigma of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          0.0036, -0.01, 0.01),
      sigmaBu_Bu2Dst0h_Dst02D0gamma_(new RooPolyVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              a0SigmaBu_Bu2Dst0h_Dst02D0gamma_,
              a1SigmaBu_Bu2Dst0h_Dst02D0gamma_ /* ,
              a2SigmaBu_Bu2Dst0h_Dst02D0gamma_ */))),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaBu_Bu2Dst0h_Dst02D0gamma_),
      // sigmaRBu_Bu2Dst0h_Dst02D0gamma_(new RooPolyVar(
      //     ("sigmaRBu_Bu2Dst0h_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     ("SigmaR of Bu2Dst0h_Dst02D0gamma Gaussian " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().deltaMass(),
      //     RooArgList(
      //         a0SigmaBu_Bu2Dst0h_Dst02D0gamma_, a1SigmaBu_Bu2Dst0h_Dst02D0gamma_ #<{(| , a2SigmaBu_Bu2Dst0h_Dst02D0gamma_ |)}>#))),
      // sigmaLBu_Bu2Dst0h_Dst02D0gamma_(
      //     ("sigmaLBu_Bu2Dst0h_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     ("SigmaL of Bu2Dst0h_Dst02D0gamma " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgSet(*sigmaRBu_Bu2Dst0h_Dst02D0gamma_,
      //               NeutralVars<Neutral::gamma>::Get(uniqueId)
      //                   .fracSigmaBu_Bu2Dst0h_Dst02D0gamma())),
      // pdfBu_Bu2Dst0h_Dst02D0gamma_(
      //     ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     ("Bu2Dst0h_Dst02D0gamma Bu PDF " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .meanBu_Bu2Dst0h_Dst02D0gamma(),
      //     sigmaLBu_Bu2Dst0h_Dst02D0gamma_, *sigmaRBu_Bu2Dst0h_Dst02D0gamma_,
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .aLBu_Bu2Dst0h_Dst02D0gamma(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .aRBu_Bu2Dst0h_Dst02D0gamma()),
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
      a0SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          32, -100, 100),  // 8
      a1SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a1SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a1 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          0.09, -10, 10),
      a2SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a2SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a2 of mean of _Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          0.0036, -0.01, 0.01),
      sigmaBu_Bu2Dst0h_Dst02D0pi0_(new RooPolyVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              a0SigmaBu_Bu2Dst0h_Dst02D0pi0_, a1SigmaBu_Bu2Dst0h_Dst02D0pi0_
              /*, a2SigmaBu_Bu2Dst0h_Dst02D0pi0_ */))),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaBu_Bu2Dst0h_Dst02D0pi0_),
      // sigmaRBu_Bu2Dst0h_Dst02D0pi0_(new RooPolyVar(
      //     ("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     ("SigmaR of Bu2Dst0h_Dst02D0pi0 Gaussian " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().deltaMass(),
      //     RooArgList(
      //         a0SigmaBu_Bu2Dst0h_Dst02D0pi0_, a1SigmaBu_Bu2Dst0h_Dst02D0pi0_ #<{(| , a2SigmaBu_Bu2Dst0h_Dst02D0pi0_ |)}>#))),
      // sigmaLBu_Bu2Dst0h_Dst02D0pi0_(
      //     ("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     ("SigmaL of Bu2Dst0h_Dst02D0pi0 " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgSet(*sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
      //               NeutralVars<Neutral::gamma>::Get(uniqueId)
      //                   .fracSigmaBu_Bu2Dst0h_Dst02D0pi0())),
      // pdfBu_Bu2Dst0h_Dst02D0pi0_(
      //     ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .meanBu_Bu2Dst0h_Dst02D0pi0(),
      //     sigmaLBu_Bu2Dst0h_Dst02D0pi0_, *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
      //     NeutralVars<Neutral::gamma>::Get(uniqueId).aLBu_Bu2Dst0h_Dst02D0pi0(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .aRBu_Bu2Dst0h_Dst02D0pi0()),
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
      sigmaBu_overRec_(
          new RooRealVar(("sigmaBu_overRec_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("Sigma of overRec Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         40, 30, 50)),
      pdfBu_overRec_(
          ("pdfBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanBu_overRec(),
          *sigmaBu_overRec_),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("overRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // ------------------- PARTIALLY RECONSTRUCTED BKG ------------------- //
      a0SigmaBu_partialRec_(
          ("a0SigmaBu_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a0 of sigma of partialRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // 40, 30, 50),
          25, -100, 100),
      a1SigmaBu_partialRec_(
          ("a1SigmaBu_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a1 of sigma of partialRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          0.09, -10, 10),
      a2SigmaBu_partialRec_(
          ("a2SigmaBu_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a2 of sigma of partialRec m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          0.0036, -0.01, 0.01),
      sigmaBu_partialRec_(new RooPolyVar(
          ("sigmaBu_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma of partialRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0SigmaBu_partialRec_,
                     a1SigmaBu_partialRec_ /*, a2SigmaBu_partialRec_ */))),
      pdfBu_partialRec_(
          ("pdfBu_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("partialRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanBu_partialRec(),
          *sigmaBu_partialRec_),
      pdf_partialRec_(
          ("pdf_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("partialRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_partialRec(),
          RooFit::Conditional(pdfBu_partialRec_,
                              Configuration::Get().buMass())),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      sigmaBu_misRec_(("sigmaBu_misRec_" +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                          .c_str(),
                      ("Sigma of misRec Gaussian " +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                          .c_str(),
                      40, 30, 50),
      pdfBu_misRec_(("pdfBu_misRec_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    ("misRec Bu PDF " +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    Configuration::Get().buMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).meanBu_misRec(),
                    sigmaBu_misRec_),
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
    : a0SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      sigmaBu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaBu_Bu2Dst0h_Dst02D0gamma_),
      // sigmaRBu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
      //     ("sigmaRBu_Bu2Dst0h_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("SigmaR of Bu2Dst0h_Dst02D0gamma Gaussian " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgList(
      //         NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
      //             .sigmaRBu_Bu2Dst0h_Dst02D0gamma(),
      //         NeutralVars<Neutral::gamma>::Get(uniqueId)
      //             .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      // sigmaLBu_Bu2Dst0h_Dst02D0gamma_(
      //     ("sigmaLBu_Bu2Dst0h_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("SigmaL of Bu2Dst0h_Dst02D0gamma " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgSet(*sigmaRBu_Bu2Dst0h_Dst02D0gamma_,
      //               NeutralVars<Neutral::gamma>::Get(uniqueId)
      //                   .fracSigmaBu_Bu2Dst0h_Dst02D0gamma())),
      // pdfBu_Bu2Dst0h_Dst02D0gamma_(
      //     ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0h_Dst02D0gamma Bu PDF " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .meanBu_Bu2Dst0h_Dst02D0gamma(),
      //     sigmaLBu_Bu2Dst0h_Dst02D0gamma_, *sigmaRBu_Bu2Dst0h_Dst02D0gamma_,
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .aLBu_Bu2Dst0h_Dst02D0gamma(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .aRBu_Bu2Dst0h_Dst02D0gamma()),
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
      a0SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      sigmaBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaBu_Bu2Dst0h_Dst02D0pi0_),
      // sigmaRBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
      //     ("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("SigmaR of Bu2Dst0h_Dst02D0pi0 Gaussian " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgList(
      //         NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
      //             .sigmaRBu_Bu2Dst0h_Dst02D0pi0(),
      //         NeutralVars<Neutral::gamma>::Get(uniqueId)
      //             .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      // sigmaLBu_Bu2Dst0h_Dst02D0pi0_(
      //     ("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("SigmaL of Bu2Dst0h_Dst02D0pi0 " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgSet(*sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
      //               NeutralVars<Neutral::gamma>::Get(uniqueId)
      //                   .fracSigmaBu_Bu2Dst0h_Dst02D0pi0())),
      // pdfBu_Bu2Dst0h_Dst02D0pi0_(
      //     ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .meanBu_Bu2Dst0h_Dst02D0pi0(),
      //     sigmaLBu_Bu2Dst0h_Dst02D0pi0_, *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .aLBu_Bu2Dst0h_Dst02D0pi0(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .aRBu_Bu2Dst0h_Dst02D0pi0()),
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
      sigmaBu_overRec_(new RooFormulaVar(
          ("sigmaBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_overRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_overRec()))),
      pdfBu_overRec_(
          ("pdfBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanBu_overRec(),
          *sigmaBu_overRec_),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // ------------------ PARTIALLY RECONSTRUCTED BKG ------------------ //
      a0SigmaBu_partialRec_(),
      a1SigmaBu_partialRec_(),
      a2SigmaBu_partialRec_(),
      sigmaBu_partialRec_(new RooFormulaVar(
          ("sigmaBu_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of partialRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_partialRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_partialRec()))),
      pdfBu_partialRec_(
          ("pdfBu_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("partialRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanBu_partialRec(),
          *sigmaBu_partialRec_),
      pdf_partialRec_(
          ("pdf_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("partialRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_partialRec(),
          RooFit::Conditional(pdfBu_partialRec_,
                              Configuration::Get().buMass())),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      sigmaBu_misRec_(("sigmaBu_misRec_" +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                          .c_str(),
                      ("Sigma of misRec Gaussian " +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                          .c_str(),
                      40, 30, 50),
      pdfBu_misRec_(
          ("pdfBu_misRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanBu_misRec(),
          sigmaBu_misRec_),
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
    : a0SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("a0 of sigma of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          10, -100, 100),
      a1SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a1SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("a1 of sigma of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          0.07, -10, 10),
      a2SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a2SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("a2 of sigma of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          0.0036, -0.01, 0.01),
      // sigmaBu_Bu2Dst0h_Dst02D0pi0_(
      //     new RooRealVar(("sigmaBu_Bu2Dst0h_Dst02D0pi0_" +
      //                     ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //                        .c_str(),
      //                    ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
      //                     ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //                        .c_str(),
      //                    100, 0, 150)),
      sigmaBu_Bu2Dst0h_Dst02D0pi0_(new RooPolyVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              a0SigmaBu_Bu2Dst0h_Dst02D0pi0_, a1SigmaBu_Bu2Dst0h_Dst02D0pi0_
              /* , a2SigmaBu_Bu2Dst0h_Dst02D0pi0_ */))),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaBu_Bu2Dst0h_Dst02D0pi0_),
      // sigmaRBu_Bu2Dst0h_Dst02D0pi0_(new RooPolyVar(
      //     ("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     ("SigmaR of Bu2Dst0h_Dst02D0pi0 Gaussian " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().deltaMass(),
      //     RooArgList(
      //         a0SigmaBu_Bu2Dst0h_Dst02D0pi0_, a1SigmaBu_Bu2Dst0h_Dst02D0pi0_ #<{(| , a2SigmaBu_Bu2Dst0h_Dst02D0pi0_ |)}>#))),
      // sigmaLBu_Bu2Dst0h_Dst02D0pi0_(
      //     ("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     ("SigmaL of Bu2Dst0h_Dst02D0pi0 " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgSet(*sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
      //               NeutralVars<Neutral::pi0>::Get(uniqueId)
      //                   .fracSigmaBu_Bu2Dst0h_Dst02D0pi0())),
      // pdfBu_Bu2Dst0h_Dst02D0pi0_(
      //     ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_Bu2Dst0h_Dst02D0pi0(),
      //     sigmaLBu_Bu2Dst0h_Dst02D0pi0_, *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).aLBu_Bu2Dst0h_Dst02D0pi0(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).aRBu_Bu2Dst0h_Dst02D0pi0()),
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
      a0SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      sigmaBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      // sigmaRBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      // sigmaLBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(),
      pdf_Bu2Dst0h_Dst02D0gamma_(),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      sigmaBu_overRec_(
          new RooRealVar(("sigmaBu_overRec_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("Sigma of overRec Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         100, 50, 150)),
      pdfBu_overRec_(
          ("pdfBu_overRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_overRec(),
          *sigmaBu_overRec_),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("overRec 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // -------------------- PARTIALLY RECONSTRUCTED BKG --------------------
      a0SigmaBu_partialRec_(("a0SigmaBu_partialRec_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            ("a0 of sigma of partialRec m[Bu] PDF " +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            // 40, 30, 50),
                            70, -100, 100),
      a1SigmaBu_partialRec_(("a1SigmaBu_partialRec_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            ("a1 of sigma of partialRec m[Bu] PDF " +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            0.07, -10, 10),
      a2SigmaBu_partialRec_(("a2SigmaBu_partialRec_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            ("a2 of sigma of partialRec m[Bu] PDF " +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            0.0036, -0.01, 0.01),
      sigmaBu_partialRec_(new RooPolyVar(
          ("sigmaBu_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma of partialRec Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0SigmaBu_partialRec_,
                     a1SigmaBu_partialRec_ /*, a2SigmaBu_partialRec_ */))),
      pdfBu_partialRec_(
          ("pdfBu_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("partialRec Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_partialRec(),
          *sigmaBu_partialRec_),
      pdf_partialRec_(
          ("pdf_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("partialRec 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_partialRec(),
          RooFit::Conditional(pdfBu_partialRec_,
                              Configuration::Get().buMass())),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      sigmaBu_misRec_(("sigmaBu_misRec_" +
                       ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                          .c_str(),
                      ("Sigma of misRec Gaussian " +
                       ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                          .c_str(),
                      60, 40, 80),
      pdfBu_misRec_(
          ("pdfBu_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("misRec Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_misRec(),
          sigmaBu_misRec_),
      pdf_misRec_(
          ("pdf_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("misRec 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_misRec(),
          RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : a0SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      sigmaBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaBu_Bu2Dst0h_Dst02D0pi0_),
      // sigmaRBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
      //     ("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
      //         .c_str(),
      //     ("SigmaR of Bu2Dst0h_Dst02D0pi0 Gaussian " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgList(
      //         NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
      //             .sigmaRBu_Bu2Dst0h_Dst02D0pi0(),
      //         NeutralVars<Neutral::pi0>::Get(uniqueId)
      //             .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      // sigmaLBu_Bu2Dst0h_Dst02D0pi0_(
      //     ("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
      //         .c_str(),
      //     ("SigmaL of Bu2Dst0h_Dst02D0pi0 " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgSet(*sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
      //               NeutralVars<Neutral::pi0>::Get(uniqueId)
      //                   .fracSigmaBu_Bu2Dst0h_Dst02D0pi0())),
      // pdfBu_Bu2Dst0h_Dst02D0pi0_(
      //     ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId)
      //         .meanBu_Bu2Dst0h_Dst02D0pi0(),
      //     sigmaLBu_Bu2Dst0h_Dst02D0pi0_, *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
      //     NeutralVars<Neutral::pi0>::Get(uniqueId)
      //         .aLBu_Bu2Dst0h_Dst02D0pi0(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId)
      //         .aRBu_Bu2Dst0h_Dst02D0pi0()),
      pdf_Bu2Dst0h_Dst02D0pi0_(
          ("pdf_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .pdfDelta_Bu2Dst0h_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // ------------------ NO CROSS FEED BECAUSE OF VETO ------------------ //
      a0SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      sigmaBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      // sigmaRBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      // sigmaLBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(),
      pdf_Bu2Dst0h_Dst02D0gamma_(),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      sigmaBu_overRec_(new RooFormulaVar(
          ("sigmaBu_overRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_overRec(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_overRec()))),
      pdfBu_overRec_(
          ("pdfBu_overRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_overRec(),
          *sigmaBu_overRec_),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("overRec 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // ------------------- PARTIALLY RECONSTRUCTED BKG ------------------- //
      a0SigmaBu_partialRec_(),
      a1SigmaBu_partialRec_(),
      a2SigmaBu_partialRec_(),
      sigmaBu_partialRec_(new RooFormulaVar(
          ("sigmaBu_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of partialRec Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_partialRec(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_partialRec()))),
      pdfBu_partialRec_(
          ("pdfBu_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("partialRec Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_partialRec(),
          *sigmaBu_partialRec_),
      pdf_partialRec_(
          ("pdf_partialRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("partialRec 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_partialRec(),
          RooFit::Conditional(pdfBu_partialRec_,
                              Configuration::Get().buMass())),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      sigmaBu_misRec_(
          ("sigmaBu_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of misRec Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          60, 40, 80),
      pdfBu_misRec_(
          ("pdfBu_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_misRec(),
          sigmaBu_misRec_),
      pdf_misRec_(
          ("pdf_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("misRec 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_misRec(),
          RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}
