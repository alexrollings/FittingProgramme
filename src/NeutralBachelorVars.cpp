#include "NeutralBachelorVars.h"
#include "Configuration.h"
#include "NeutralVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars()
    : sigmaSignal_(new RooRealVar(
          ("sigmaSignal_" + ComposeName(Neutral::gamma, Bachelor::pi)).c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(Neutral::gamma, Bachelor::pi))
              .c_str(),
          100, 0, 150)),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(Neutral::gamma, Bachelor::pi)).c_str(),
          ("Signal PDF " + ComposeName(Neutral::gamma, Bachelor::pi)).c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanSignal(), *sigmaSignal_) {}

template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars()
    : sigmaSignal_(new RooFormulaVar(
          ("sigmaSignal_" + ComposeName(Neutral::gamma, Bachelor::k)).c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaSignal(),
                     Configuration::Get().relativeWidth()))),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(Neutral::gamma, Bachelor::k)).c_str(),
          ("Signal PDF " + ComposeName(Neutral::gamma, Bachelor::k)).c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanSignal(), *sigmaSignal_) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars()
    : sigmaSignal_(new RooRealVar(
          ("sigmaSignal_" + ComposeName(Neutral::pi0, Bachelor::pi)).c_str(),
          ("Sigma of signal Gaussian " +
           ComposeName(Neutral::pi0, Bachelor::pi))
              .c_str(),
          50, 0, 100)),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(Neutral::pi0, Bachelor::pi)).c_str(),
          ("Signal PDF " + ComposeName(Neutral::pi0, Bachelor::pi)).c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanSignal(), *sigmaSignal_) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars()
    : sigmaSignal_(new RooFormulaVar(
          ("sigmaSignal_" + ComposeName(Neutral::pi0, Bachelor::k)).c_str(),
          ("Sigma of signal Gaussian " + ComposeName(Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get()
                         .sigmaSignal(),
                     Configuration::Get().relativeWidth()))),
      pdfSignal_(
          ("pdfSignal_" + ComposeName(Neutral::pi0, Bachelor::k)).c_str(),
          ("Signal PDF " + ComposeName(Neutral::pi0, Bachelor::k)).c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get().meanSignal(), *sigmaSignal_) {}
