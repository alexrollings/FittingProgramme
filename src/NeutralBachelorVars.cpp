#include "NeutralBachelorVars.h"
#include "Configuration.h"
#include "NeutralVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars()
    : sigmaSignal_(new RooRealVar("sigmaSignal_gamma_pi",
                                  "Sigma of signal Gaussian: gamma pi", 100, 0,
                                  150)),
      pdfSignal_(
          "pdfSignal_gamma_pi", "Signal PDF", Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanSignal(), *sigmaSignal_) {}

template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars()
    : sigmaSignal_(new RooFormulaVar(
          "sigmaSignal_gamma_k", "Sigma of signal Gaussian: gamma k", "@0*@1",
          RooArgList(NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get()
                         .sigmaSignal(),
                     Configuration::Get().relativeWidth()))),
      pdfSignal_(
          "pdfSignal_gamma_k", "Signal PDF", Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get().meanSignal(), *sigmaSignal_) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars()
    : sigmaSignal_(new RooRealVar("sigmaSignal_pi0_pi",
                                  "Sigma of signal Gaussian: pi0 pi", 50, 0,
                                  100)),
      pdfSignal_("pdfSignal_pi0_pi", "Signal PDF",
                 Configuration::Get().buMass(),
                 NeutralVars<Neutral::pi0>::Get().meanSignal(), *sigmaSignal_) {}

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars()
    : sigmaSignal_(new RooFormulaVar(
          "sigmaSignal_pi0_k", "Sigma of signal Gaussian: pi0 k", "@0*@1",
          RooArgList(NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get()
                         .sigmaSignal(),
                     Configuration::Get().relativeWidth()))),
      pdfSignal_("pdfSignal_pi0_k", "Signal PDF", Configuration::Get().buMass(),
                 NeutralVars<Neutral::pi0>::Get().meanSignal(), *sigmaSignal_) {}
