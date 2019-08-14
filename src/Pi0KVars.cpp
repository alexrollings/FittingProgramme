#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_sigmaBu_(new RooFormulaVar(
          ("Bu2Dst0h_Dst02D0gamma_sigma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_Dst02D0gamma_sigmaBu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      pdf1Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf1_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0gamma_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf2_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0gamma_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0, Bachelor::k))
              .c_str(),
          "",
          RooArgSet(pdf1Bu_Bu2Dst0h_Dst02D0gamma_,
                    pdf2Bu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_frac1PdfBu()),
      N_Delta_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("N_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgSet(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .N_Delta_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .ratioKpi_Bu2Dst0h_Dst02D0gamma()))),
      N_Bu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("N_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgSet(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .N_Bu_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .ratioKpi_Bu2Dst0h_Dst02D0gamma()))) {}
