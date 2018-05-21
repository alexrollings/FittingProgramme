#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    : sigmaDeltaSignal_(
          new RooRealVar(("sigmaDeltaSignal_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("Sigma of signal Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         20, 0, 40)),
      pdfDeltaSignal_(
          ("pdfDeltaSignal_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          ("Signal Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanDeltaSignal(),
          *sigmaDeltaSignal_),
      a0SigmaBuSignal_(("a0SigmaBuSignal" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       ("a0 of mean of Signal m[Bu] PDF " +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       // 20, 0, 40),
                       // -6.1, -300, 300),
                       117, -300, 300),
      a1SigmaBuSignal_(("a1SigmaBuSignal" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       ("a1 of mean of Signal m[Bu] PDF " +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       // -0.16, -10, 10),
                       -1.5, -10, 10),
      a2SigmaBuSignal_(("a2SigmaBuSignal" +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       ("a2 of mean of Signal m[Bu] PDF " +
                        ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                           .c_str(),
                       0.005, -0.02, 0.02),
      sigmaBuSignal_(
          new RooRealVar(("sigmaBuSignal_" +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         ("Sigma of signal Gaussian " +
                          ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
                             .c_str(),
                         100, 0, 150)),
// sigmaBuSignal_(new RooPolyVar(
//     ("sigmaBuSignal_" +
//      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
//         .c_str(),
//     ("Sigma of signal Gaussian " +
//      ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
//         .c_str(),
//     Configuration::Get().deltaMass(),
//     RooArgList(a0SigmaBuSignal_, a1SigmaBuSignal_, a2SigmaBuSignal_))),
pdfBuSignal_(
    ("pdfBuSignal_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
        .c_str(),
    ("Signal Bu PDF " + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
        .c_str(),
    Configuration::Get().buMass(),
    NeutralVars<Neutral::gamma>::Get(uniqueId).meanBuSignal(), *sigmaBuSignal_),
    pdfSignal_(
        ("pdfSignal_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        ("Signal 2D PDF " + ComposeName(uniqueId, Neutral::gamma, Bachelor::pi))
            .c_str(),
        pdfDeltaSignal_,
        RooFit::Conditional(pdfBuSignal_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    : sigmaDeltaSignal_(new RooFormulaVar(
          ("sigmaDeltaSignal_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaDeltaSignal(),
              GlobalVars::Get(uniqueId).relativeWidth()))),
      pdfDeltaSignal_(
          ("pdfDeltaSignal_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Signal Delta PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanDeltaSignal(),
          *sigmaDeltaSignal_),
      a0SigmaBuSignal_(),
      a1SigmaBuSignal_(),
      a2SigmaBuSignal_(),
      sigmaBuSignal_(new RooFormulaVar(
          ("sigmaBuSignal_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaBuSignal(),
              GlobalVars::Get(uniqueId).relativeWidth()))),
      pdfBuSignal_(
          ("pdfBuSignal_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Signal Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).meanBuSignal(),
          *sigmaBuSignal_),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Signal 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          pdfDeltaSignal_,
          RooFit::Conditional(pdfBuSignal_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    : sigmaDeltaSignal_(
          new RooRealVar(("sigmaDeltaSignal_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("Sigma of signal Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         20, 0, 40)),
      pdfDeltaSignal_(
          ("pdfDeltaSignal_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Signal Delta PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanDeltaSignal(),
          *sigmaDeltaSignal_),
      a0SigmaBuSignal_(("a0SigmaBuSignal" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       ("a0 of mean of Signal m[Bu] PDF " +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       // 20, 0, 40),
                       // -6.1, -300, 300),
                       117, -300, 300),
      a1SigmaBuSignal_(("a1SigmaBuSignal" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       ("a1 of mean of Signal m[Bu] PDF " +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       // 0.16, -10, 10),
                       -1.5, -10, 10),
      a2SigmaBuSignal_(("a2SigmaBuSignal" +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       ("a2 of mean of Signal m[Bu] PDF " +
                        ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                           .c_str(),
                       0.005, -0.02, 0.02),
      sigmaBuSignal_(
          new RooRealVar(("sigmaBuSignal_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("Sigma of signal Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         100, 0, 150)),
      // sigmaBuSignal_(new RooPolyVar(
      //     ("sigmaBuSignal_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     ("Sigma of signal Gaussian " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().deltaMass(),
      //     RooArgList(a0SigmaBuSignal_, a1SigmaBuSignal_, a2SigmaBuSignal_))),
      pdfBuSignal_(
          ("pdfBuSignal_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Signal Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBuSignal(),
          *sigmaBuSignal_),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Signal 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          pdfDeltaSignal_,
          RooFit::Conditional(pdfBuSignal_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    : sigmaDeltaSignal_(new RooFormulaVar(
          ("sigmaDeltaSignal_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaDeltaSignal(),
              GlobalVars::Get(uniqueId).relativeWidth()))),
      pdfDeltaSignal_(
          ("pdfDeltaSignal_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Signal Delta PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanDeltaSignal(),
          *sigmaDeltaSignal_),
      a0SigmaBuSignal_(),
      a1SigmaBuSignal_(),
      a2SigmaBuSignal_(),
      sigmaBuSignal_(new RooFormulaVar(
          ("sigmaBuSignal_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .sigmaBuSignal(),
              GlobalVars::Get(uniqueId).relativeWidth()))),
      pdfBuSignal_(
          ("pdfBuSignal_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Signal Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).meanBuSignal(),
          *sigmaBuSignal_),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Signal 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          pdfDeltaSignal_,
          RooFit::Conditional(pdfBuSignal_, Configuration::Get().buMass())) {}
