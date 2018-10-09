#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0pi0_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_Dst02D0pi0_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma1 of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_Dst02D0pi0_sigma1Bu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      Bu2Dst0h_Dst02D0pi0_sigma2Bu_(new RooFormulaVar(
          ("Bu2Dst0h_Dst02D0pi0_sigma2Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Sigma2 of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_Dst02D0pi0_sigma2Bu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      pdf1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("pdf1Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_mean1Bu(),
          *Bu2Dst0h_Dst02D0pi0_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_Dst02D0pi0_(
          ("pdf2Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_mean1Bu(),
          *Bu2Dst0h_Dst02D0pi0_sigma2Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          RooArgSet(pdf1Bu_Bu2Dst0h_Dst02D0pi0_, pdf2Bu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_frac1PdfBu()),
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
      Bu2Dst0h_Dst02D0gamma_sigma1Bu_(nullptr),
      Bu2Dst0h_Dst02D0gamma_sigma2Bu_(nullptr),
      pdf1Bu_Bu2Dst0h_Dst02D0gamma_(),
      pdf2Bu_Bu2Dst0h_Dst02D0gamma_(),
      pdf12Bu_Bu2Dst0h_Dst02D0gamma_(),
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
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_meanBu(),
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
      overRec_sigma1Bu_(nullptr),
      overRec_sigma2Bu_(nullptr),
      pdf1Bu_overRec_(),
      pdf2Bu_overRec_(),
      pdfBu_overRec_(),
      pdf_overRec_(),
      // ------------------- Pi0 PART RECONSTRUCTED BKG ------------------- //
      Bu2Dst0hst_Dst02D0pi0_sigma1Bu_(nullptr),
      Bu2Dst0hst_Dst02D0pi0_sigma2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_Dst02D0pi0_(),
      pdf2Bu_Bu2Dst0hst_Dst02D0pi0_(),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(),
      pdf_Bu2Dst0hst_Dst02D0pi0_(),
      // -------------------- Gamma PART RECONSTRUCTED BKG --------------------
      Bu2Dst0hst_Dst02D0gamma_sigma1Bu_(nullptr),
      Bu2Dst0hst_Dst02D0gamma_sigma2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_Dst02D0gamma_(),
      pdf2Bu_Bu2Dst0hst_Dst02D0gamma_(),
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
//     NeutralVars<Neutral::pi0>::Get(uniqueId).misRec_meanBu(),
//     sigmaBu_misRec_),
// pdf_misRec_(
//     ("pdf_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
//         .c_str(),
//     ("misRec 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
//         .c_str(),
//     NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_misRec(),
//     RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}
