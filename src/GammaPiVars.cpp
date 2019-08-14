#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_sigmaBu_(new RooRealVar(
          ("Bu2Dst0h_Dst02D0gamma_sigma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::gamma, Bachelor::pi))
              .c_str(), "", 2.0051e+01)),
      pdf1Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf1_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::gamma, Bachelor::pi))
              .c_str(), "",
          Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf2_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::gamma, Bachelor::pi))
              .c_str(), "",
          Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::gamma, Bachelor::pi))
              .c_str(), "",
          RooArgSet(pdf1Bu_Bu2Dst0h_Dst02D0gamma_,
                    pdf2Bu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_frac1PdfBu()) {}
