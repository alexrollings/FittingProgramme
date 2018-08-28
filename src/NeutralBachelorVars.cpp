#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaDelta_Bu2Dst0h_Dst02D0gamma_(
          new RooRealVar(("sigmaDelta_Bu2Dst0h_Dst02D0gamma_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("Sigma of Bu2Dst0h_Dst02D0gamma Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         // 20, 0, 40)),
                         5, 0, 10)),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(
          ("pdfDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanDelta_Bu2Dst0h_Dst02D0gamma(),
          *sigmaDelta_Bu2Dst0h_Dst02D0gamma_),
      a0SigmaBu_Bu2Dst0h_Dst02D0gamma_(
          ("a0SigmaBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a0 of sigma of Bu2Dst0h_Dst02D0gamma m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          // 100, 0, 150),
          // -6.1, -100, 100),
          5, -100, 100),
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
      // sigmaBu_Bu2Dst0h_Dst02D0gamma_(
      //     new RooRealVar(("sigmaBu_Bu2Dst0h_Dst02D0gamma_" +
      //                     ComposeName(uniqueId, Neutral::gamma,
      //                     Bachelor::pi))
      //                        .c_str(),
      //                    ("Sigma of Bu2Dst0h_Dst02D0gamma Gaussian " +
      //                     ComposeName(uniqueId, Neutral::gamma,
      //                     Bachelor::pi))
      //                        .c_str(),
      //                    100, 0, 150)),
      sigmaBu_Bu2Dst0h_Dst02D0gamma_(new RooPolyVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              a0SigmaBu_Bu2Dst0h_Dst02D0gamma_, a1SigmaBu_Bu2Dst0h_Dst02D0gamma_ /* , a2SigmaBu_Bu2Dst0h_Dst02D0gamma_ */))),
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
      pdf_Bu2Dst0h_Dst02D0gamma_(
          ("pdf_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          pdfDelta_Bu2Dst0h_Dst02D0gamma_,
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0gamma_,
                              Configuration::Get().buMass())),
      // -------------------- PARTIAL PI0 -------------------- //
      sigmaDelta_Bu2Dst0h_Dst02D0pi0_(
          new RooRealVar(("sigmaDelta_Bu2Dst0h_Dst02D0pi0_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         8, 0, 10)),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanDelta_Bu2Dst0h_Dst02D0pi0(),
          *sigmaDelta_Bu2Dst0h_Dst02D0pi0_),
      a0SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("a0 of mean of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          5, -100, 100),
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
              a0SigmaBu_Bu2Dst0h_Dst02D0pi0_, a1SigmaBu_Bu2Dst0h_Dst02D0pi0_ /*, a2SigmaBu_Bu2Dst0h_Dst02D0pi0_ */))),
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
      pdf_Bu2Dst0h_Dst02D0pi0_(
          ("pdf_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          pdfDelta_Bu2Dst0h_Dst02D0pi0_,
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- BU2D0H BKG -------------------- //
      sigmaBu_Bu2D0h_(
          new RooRealVar(("sigmaBu_Bu2D0h_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("Sigma of Bu2D0h Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         40, 30, 50)),
      pdfBu_Bu2D0h_(("pdfBu_Bu2D0h_" +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    ("Bu2D0h Bu PDF " +
                     ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                        .c_str(),
                    Configuration::Get().buMass(),
                    NeutralVars<Neutral::gamma>::Get(uniqueId).meanBu_Bu2D0h(),
                    *sigmaBu_Bu2D0h_),
      pdf_Bu2D0h_(
          ("pdf_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Bu2D0h 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_Bu2D0h(),
          RooFit::Conditional(pdfBu_Bu2D0h_, Configuration::Get().buMass())),
      // -------------------- PARTIALLY RECONSTRUCTED BKG --------------------
      sigmaDelta_partialRec_(
          new RooRealVar(("sigmaDelta_partialRec_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("Sigma of partialRec Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         5, 0, 10)),
      pdfDelta_partialRec_(("pdfDelta_partialRec_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                               .c_str(),
                           ("partialRec Delta PDF " +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                               .c_str(),
                           Configuration::Get().deltaMass(),
                           NeutralVars<Neutral::gamma>::Get(uniqueId)
                               .meanDelta_Bu2Dst0h_Dst02D0gamma(),
                           *sigmaDelta_partialRec_),
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
      pdf_partialRec_(("pdf_partialRec_" +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                          .c_str(),
                      ("partialRec 2D PDF " +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                          .c_str(),
                      pdfDelta_partialRec_,
                      RooFit::Conditional(pdfBu_partialRec_,
                                          Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaDelta_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaDelta_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeWidth_Bu2Dst0h_Dst02D0gamma()))),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(
          ("pdfDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanDelta_Bu2Dst0h_Dst02D0gamma(),
          *sigmaDelta_Bu2Dst0h_Dst02D0gamma_),
      a0SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      sigmaBu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeWidth_Bu2Dst0h_Dst02D0gamma()))),
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
      pdf_Bu2Dst0h_Dst02D0gamma_(
          ("pdf_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          pdfDelta_Bu2Dst0h_Dst02D0gamma_,
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0gamma_,
                              Configuration::Get().buMass())),
      // -------------------- PARTIAL PI0 -------------------- //
      sigmaDelta_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaDelta_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeWidth_Bu2Dst0h_Dst02D0pi0()))),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanDelta_Bu2Dst0h_Dst02D0pi0(),
          *sigmaDelta_Bu2Dst0h_Dst02D0pi0_),
      a0SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      sigmaBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeWidth_Bu2Dst0h_Dst02D0pi0()))),
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
      pdf_Bu2Dst0h_Dst02D0pi0_(
          ("pdf_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          pdfDelta_Bu2Dst0h_Dst02D0pi0_,
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- BU2D0H BKG -------------------- //
      sigmaBu_Bu2D0h_(new RooFormulaVar(
          ("sigmaBu_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2D0h Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2D0h(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeWidth_Bu2D0h()))),
      pdfBu_Bu2D0h_(
          ("pdfBu_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2D0h Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanBu_Bu2D0h(),
          *sigmaBu_Bu2D0h_),
      pdf_Bu2D0h_(
          ("pdf_Bu2D0h_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2D0h 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_Bu2D0h(),
          RooFit::Conditional(pdfBu_Bu2D0h_, Configuration::Get().buMass())),
      // -------------------- PARTIALLY RECONSTRUCTED BKG --------------------
      // //
      sigmaDelta_partialRec_(new RooFormulaVar(
          ("sigmaDelta_partialRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of partialRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaDelta_partialRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeWidth_Bu2D0h()))),
      pdfDelta_partialRec_(("pdfDelta_partialRec_" +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           ("partialRec Delta PDF " +
                            ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                               .c_str(),
                           Configuration::Get().deltaMass(),
                           NeutralVars<Neutral::gamma>::Get(uniqueId)
                               .meanDelta_Bu2Dst0h_Dst02D0gamma(),
                           *sigmaDelta_partialRec_),
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
                  .relativeWidth_partialRec()))),
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
      pdf_partialRec_(("pdf_partialRec_" +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                          .c_str(),
                      ("partialRec 2D PDF " +
                       ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
                          .c_str(),
                      pdfDelta_partialRec_,
                      RooFit::Conditional(pdfBu_partialRec_,
                                          Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaDelta_Bu2Dst0h_Dst02D0pi0_(
          new RooRealVar(("sigmaDelta_Bu2Dst0h_Dst02D0pi0_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         // 20, 0, 40)),
                         2, 0, 5)),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .meanDelta_Bu2Dst0h_Dst02D0pi0(),
          *sigmaDelta_Bu2Dst0h_Dst02D0pi0_),
      a0SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a0SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("a0 of sigma of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          // 100, 0, 150),
          // -6.1, -100, 100),
          5, -100, 100),
      // 25, -100, 100),
      // 150, -200, 200),
      a1SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a1SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("a1 of sigma of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          0.07, -10, 10),
      // -0.36, -10, 10),
      // -2.4, -10, 10),
      a2SigmaBu_Bu2Dst0h_Dst02D0pi0_(
          ("a2SigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("a2 of sigma of Bu2Dst0h_Dst02D0pi0 m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          0.0036, -0.01, 0.01),
      // 0.0099, -0.02, 0.02),
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
              a0SigmaBu_Bu2Dst0h_Dst02D0pi0_, a1SigmaBu_Bu2Dst0h_Dst02D0pi0_ /* , a2SigmaBu_Bu2Dst0h_Dst02D0pi0_ */))),
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
      pdf_Bu2Dst0h_Dst02D0pi0_(
          ("pdf_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          pdfDelta_Bu2Dst0h_Dst02D0pi0_,
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- NO CROSS FEED BECAUSE OF VETO --------------------
      // //
      sigmaDelta_Bu2Dst0h_Dst02D0gamma_(nullptr),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(),
      a0SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      sigmaBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(),
      pdf_Bu2Dst0h_Dst02D0gamma_(),
      // -------------------- BU2D0H BKG -------------------- //
      sigmaBu_Bu2D0h_(
          new RooRealVar(("sigmaBu_Bu2D0h_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("Sigma of Bu2D0h Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         40, 30, 50)),
      pdfBu_Bu2D0h_(
          ("pdfBu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2D0h Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_Bu2D0h(),
          *sigmaBu_Bu2D0h_),
      pdf_Bu2D0h_(
          ("pdf_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2D0h 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_Bu2D0h(),
          RooFit::Conditional(pdfBu_Bu2D0h_, Configuration::Get().buMass())),
      // -------------------- PARTIALLY RECONSTRUCTED BKG --------------------
      sigmaDelta_partialRec_(
          new RooRealVar(("sigmaDelta_partialRec_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("Sigma of partialRec Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         2, 0, 5)),
      pdfDelta_partialRec_(("pdfDelta_partialRec_" +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                               .c_str(),
                           ("partialRec Delta PDF " +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                               .c_str(),
                           Configuration::Get().deltaMass(),
                           NeutralVars<Neutral::pi0>::Get(uniqueId)
                               .meanDelta_Bu2Dst0h_Dst02D0pi0(),
                           *sigmaDelta_partialRec_),
      a0SigmaBu_partialRec_(("a0SigmaBu_partialRec_" +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            ("a0 of sigma of partialRec m[Bu] PDF " +
                             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                                .c_str(),
                            // 40, 30, 50),
                            25, -100, 100),
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
      pdf_partialRec_(("pdf_partialRec_" +
                       ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                          .c_str(),
                      ("partialRec 2D PDF " +
                       ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                          .c_str(),
                      pdfDelta_partialRec_,
                      RooFit::Conditional(pdfBu_partialRec_,
                                          Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaDelta_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaDelta_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeWidth_Bu2Dst0h_Dst02D0pi0()))),
      pdfDelta_Bu2Dst0h_Dst02D0pi0_(
          ("pdfDelta_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Delta PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .meanDelta_Bu2Dst0h_Dst02D0pi0(),
          *sigmaDelta_Bu2Dst0h_Dst02D0pi0_),
      a0SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0pi0_(),
      sigmaBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeWidth_Bu2Dst0h_Dst02D0pi0()))),
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
      pdf_Bu2Dst0h_Dst02D0pi0_(
          ("pdf_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          pdfDelta_Bu2Dst0h_Dst02D0pi0_,
          RooFit::Conditional(pdfBu_Bu2Dst0h_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- NO CROSS FEED BECAUSE OF VETO --------------------
      // //
      sigmaDelta_Bu2Dst0h_Dst02D0gamma_(nullptr),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(),
      a0SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a1SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      a2SigmaBu_Bu2Dst0h_Dst02D0gamma_(),
      sigmaBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(),
      pdf_Bu2Dst0h_Dst02D0gamma_(),
      // -------------------- BU2D0H BKG -------------------- //
      sigmaBu_Bu2D0h_(new RooFormulaVar(
          ("sigmaBu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of Bu2D0h Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaBu_Bu2D0h(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeWidth_Bu2D0h()))),
      pdfBu_Bu2D0h_(
          ("pdfBu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2D0h Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_Bu2D0h(),
          *sigmaBu_Bu2D0h_),
      pdf_Bu2D0h_(
          ("pdf_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2D0h 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_Bu2D0h(),
          RooFit::Conditional(pdfBu_Bu2D0h_, Configuration::Get().buMass())),
      // -------------------- PARTIALLY RECONSTRUCTED BKG --------------------
      // //
      sigmaDelta_partialRec_(new RooFormulaVar(
          ("sigmaDelta_partialRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of partialRec Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaDelta_partialRec(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeWidth_partialRec()))),
      pdfDelta_partialRec_(("pdfDelta_partialRec_" +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           ("partialRec Delta PDF " +
                            ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                               .c_str(),
                           Configuration::Get().deltaMass(),
                           NeutralVars<Neutral::pi0>::Get(uniqueId)
                               .meanDelta_Bu2Dst0h_Dst02D0pi0(),
                           *sigmaDelta_partialRec_),
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
                  .relativeWidth_partialRec()))),
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
          pdfDelta_partialRec_,
          RooFit::Conditional(pdfBu_partialRec_,
                              Configuration::Get().buMass())) {}
