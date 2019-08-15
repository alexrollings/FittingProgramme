#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_sigmaBu_(
          new RooRealVar(("Bu2Dst0h_Dst02D0gamma_sigmaBu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 2.0051e+01)),
      pdf1Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf1Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf2Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          "",
          RooArgSet(pdf1Bu_Bu2Dst0h_Dst02D0gamma_,
                    pdf2Bu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_frac1PdfBu()),
      N_Delta_Bu2Dst0h_Dst02D0gamma_(
          new RooRealVar(("N_Delta_Bu2Dst0h_Dst02D0gamma_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 50000, -1000000, 1000000)),
      N_Bu_Bu2Dst0h_Dst02D0gamma_(
          new RooRealVar(("N_Bu_Bu2Dst0h_Dst02D0gamma_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         "", 40000, -1000000, 1000000)) {}
