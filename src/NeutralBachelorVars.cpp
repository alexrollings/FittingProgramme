#include "NeutralBachelorVars.h"
#include "Configuration.h"
#include "NeutralVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars()
  : sigmaDeltaSignal_(new RooRealVar(("sigmaDeltaSignal_" +
                                      ComposeName(Neutral::gamma, Bachelor::pi))
                                         .c_str(),
                                     ("Sigma of signal Gaussian " +
                                      ComposeName(Neutral::gamma, Bachelor::pi))
                                         .c_str(),
                                     50, 0, 80)),
    pdfDeltaSignal_(
        ("pdfDeltaSignal_" + ComposeName(Neutral::gamma, Bachelor::pi)).c_str(),
        ("Signal Delta PDF " + ComposeName(Neutral::gamma, Bachelor::pi))
            .c_str(),
        Configuration::Get().deltaMass(),
        NeutralVars<Neutral::gamma>::Get().meanDeltaSignal(),
        *sigmaDeltaSignal_),
    sigmaBuSignal_(new RooRealVar(
        ("sigmaBuSignal_" + ComposeName(Neutral::gamma, Bachelor::pi)).c_str(),
        ("Sigma of signal Gaussian " +
         ComposeName(Neutral::gamma, Bachelor::pi))
            .c_str(),
        100, 0, 150)),
    pdfBuSignal_(
        ("pdfBuSignal_" + ComposeName(Neutral::gamma, Bachelor::pi)).c_str(),
        ("Signal Bu PDF " + ComposeName(Neutral::gamma, Bachelor::pi)).c_str(),
        Configuration::Get().buMass(),
        NeutralVars<Neutral::gamma>::Get().meanBuSignal(), *sigmaBuSignal_),
    pdfSignal_(
        ("pdfSignal_" + ComposeName(Neutral::gamma, Bachelor::pi)).c_str(),
        ("Signal 2D PDF " + ComposeName(Neutral::gamma, Bachelor::pi)).c_str(),
        pdfDeltaSignal_,
        RooFit::Conditional(pdfBuSignal_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars()
    : sigmaDeltaSignal_(new RooFormulaVar(
          ("sigmaDeltaSignal_" + ComposeName(Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaDeltaSignal(),
                     Configuration::Get().relativeWidth()))),
      pdfDeltaSignal_(
          ("pdfDeltaSignal_" + ComposeName(Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Signal Delta PDF " + ComposeName(Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::gamma>::Get().meanDeltaSignal(),
          *sigmaDeltaSignal_),
      sigmaBuSignal_(new RooFormulaVar(
          ("sigmaBuSignal_" + ComposeName(Neutral::gamma, Bachelor::k)).c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaBuSignal(),
                     Configuration::Get().relativeWidth()))),
      pdfBuSignal_(
          ("pdfBuSignal_" + ComposeName(Neutral::gamma, Bachelor::k)).c_str(),
          ("Signal Bu PDF " + ComposeName(Neutral::gamma, Bachelor::k)).c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanBuSignal(), *sigmaBuSignal_),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(Neutral::gamma, Bachelor::k)).c_str(),
          ("Signal 2D PDF " + ComposeName(Neutral::gamma, Bachelor::k)).c_str(),
          pdfDeltaSignal_,
          RooFit::Conditional(pdfBuSignal_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars()
    : sigmaDeltaSignal_(new RooRealVar(
          ("sigmaDeltaSignal_" + ComposeName(Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(Neutral::pi0, Bachelor::pi))
              .c_str(),
          30, 0, 50)),
      pdfDeltaSignal_(
          ("pdfDeltaSignal_" + ComposeName(Neutral::pi0, Bachelor::pi)).c_str(),
          ("Signal Delta PDF " + ComposeName(Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::pi0>::Get().meanDeltaSignal(),
          *sigmaDeltaSignal_),
      sigmaBuSignal_(new RooRealVar(
          ("sigmaBuSignal_" + ComposeName(Neutral::pi0, Bachelor::pi)).c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(Neutral::pi0, Bachelor::pi))
              .c_str(),
          50, 0, 100)),
      pdfBuSignal_(
          ("pdfBuSignal_" + ComposeName(Neutral::pi0, Bachelor::pi)).c_str(),
          ("Signal Bu PDF " + ComposeName(Neutral::pi0, Bachelor::pi)).c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanBuSignal(), *sigmaBuSignal_),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(Neutral::pi0, Bachelor::pi)).c_str(),
          ("Signal 2D PDF " + ComposeName(Neutral::pi0, Bachelor::pi)).c_str(),
          pdfDeltaSignal_,
          RooFit::Conditional(pdfBuSignal_, Configuration::Get().buMass())) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars()
    : sigmaDeltaSignal_(new RooFormulaVar(
          ("sigmaDeltaSignal_" + ComposeName(Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma of signal Gaussian " + ComposeName(Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get()
                         .sigmaDeltaSignal(),
                     Configuration::Get().relativeWidth()))),
      pdfDeltaSignal_(
          ("pdfDeltaSignal_" + ComposeName(Neutral::pi0, Bachelor::k)).c_str(),
          ("Signal Delta PDF " + ComposeName(Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().deltaMass(),
          NeutralVars<Neutral::pi0>::Get().meanDeltaSignal(),
          *sigmaDeltaSignal_),
      sigmaBuSignal_(new RooFormulaVar(
          ("sigmaBuSignal_" + ComposeName(Neutral::pi0, Bachelor::k)).c_str(),
          ("Sigma of signal Gaussian " + ComposeName(Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get()
                         .sigmaBuSignal(),
                     Configuration::Get().relativeWidth()))),
      pdfBuSignal_(
          ("pdfBuSignal_" + ComposeName(Neutral::pi0, Bachelor::k)).c_str(),
          ("Signal Bu PDF " + ComposeName(Neutral::pi0, Bachelor::k)).c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanBuSignal(), *sigmaBuSignal_),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(Neutral::pi0, Bachelor::k)).c_str(),
          ("Signal 2D PDF " + ComposeName(Neutral::pi0, Bachelor::k)).c_str(),
          pdfDeltaSignal_,
          RooFit::Conditional(pdfBuSignal_, Configuration::Get().buMass())) {}
