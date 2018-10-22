#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_Dst02D0gamma_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma1 of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_Dst02D0gamma_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      Bu2Dst0h_Dst02D0gamma_sigma2Bu_(new RooFormulaVar(
          ("Bu2Dst0h_Dst02D0gamma_sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma2 of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_Dst02D0gamma_sigma2Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      pdf1Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf1Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_Dst02D0gamma_(
          ("pdf2Bu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF of 2 CBs " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdf1Bu_Bu2Dst0h_Dst02D0gamma_,
                    pdf2Bu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_frac1PdfBu()),
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
      Bu2Dst0h_Dst02D0pi0_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0h_Dst02D0pi0_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma1 of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_Dst02D0pi0_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      Bu2Dst0h_Dst02D0pi0_sigma2Bu_(new RooFormulaVar(
          ("Bu2Dst0h_Dst02D0pi0_sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma2 of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_Dst02D0pi0_sigma2Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      pdf1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("pdf1Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_meanBu(),
          *Bu2Dst0h_Dst02D0pi0_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_Dst02D0pi0_(
          ("pdf2Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_meanBu(),
          *Bu2Dst0h_Dst02D0pi0_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_n2Bu()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdf1Bu_Bu2Dst0h_Dst02D0pi0_, pdf2Bu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_frac1PdfBu()),
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
      overRec_sigma1Bu_(new RooFormulaVar(
          ("overRec_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma1 of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .overRec_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_overRec()))),
      overRec_sigma2Bu_(new RooFormulaVar(
          ("overRec_sigma2Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma2 of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .overRec_sigma2Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_overRec()))),
      pdf1Bu_overRec_(
          ("pdf1Bu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_mean1Bu(),
          *overRec_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_n1Bu()),
      pdf2Bu_overRec_(
          ("pdf2Bu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_mean2Bu(),
          *overRec_sigma2Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_a2Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_n2Bu()),
      pdfBu_overRec_(
          ("pdfBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdf1Bu_overRec_, pdf2Bu_overRec_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).overRec_frac1PdfBu()),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // ------------------ Pi0 PART RECONSTRUCTED BKG ------------------ //
      Bu2Dst0hst_Dst02D0pi0_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0hst_Dst02D0pi0_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma1 of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0hst_Dst02D0pi0_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0pi0()))),
      Bu2Dst0hst_Dst02D0pi0_sigma2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_Dst02D0pi0_(),
      pdf2Bu_Bu2Dst0hst_Dst02D0pi0_(),
      // Bu2Dst0hst_Dst02D0pi0_sigma2Bu_(new RooFormulaVar(
      //     ("Bu2Dst0hst_Dst02D0pi0_sigma2Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Sigma2 of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgList(
      //         NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
      //             .Bu2Dst0hst_Dst02D0pi0_sigma2Bu(),
      //         NeutralVars<Neutral::gamma>::Get(uniqueId)
      //             .relativeBuWidth_Bu2Dst0hst_Dst02D0pi0()))),
      // pdf1Bu_Bu2Dst0hst_Dst02D0pi0_(
      //     ("pdf1Bu_Bu2Dst0hst_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0hst_Dst02D0pi0 Bu PDF L " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0pi0_meanBu(),
      //     *Bu2Dst0hst_Dst02D0pi0_sigma1Bu_,
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0pi0_a1Bu(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0pi0_n1Bu()),
      // pdf2Bu_Bu2Dst0hst_Dst02D0pi0_(
      //     ("pdf2Bu_Bu2Dst0hst_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0hst_Dst02D0pi0 Bu PDF R " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0pi0_meanBu(),
      //     *Bu2Dst0hst_Dst02D0pi0_sigma2Bu_,
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0pi0_a2Bu(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0pi0_n2Bu()),
      // pdfBu_Bu2Dst0hst_Dst02D0pi0_(
      //     ("pdfBu_Bu2Dst0hst_Dst02D0pi0_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0hst_Dst02D0pi0 Bu PDF " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     RooArgSet(pdf1Bu_Bu2Dst0hst_Dst02D0pi0_,
      //     pdf2Bu_Bu2Dst0hst_Dst02D0pi0_),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0pi0_frac1PdfBu()),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(new RooCBShape(
          ("pdfBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0pi0_meanBu(),
          *Bu2Dst0hst_Dst02D0pi0_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0pi0_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0pi0_n1Bu())),
      pdf_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0hst_Dst02D0pi0(),
          RooFit::Conditional(*pdfBu_Bu2Dst0hst_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // ------------------ Gamma PART RECONSTRUCTED BKG ------------------ //
      Bu2Dst0hst_Dst02D0gamma_sigma1Bu_(new RooFormulaVar(
          ("Bu2Dst0hst_Dst02D0gamma_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma1 of Bu2Dst0hst_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0hst_Dst02D0gamma_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0gamma()))),
      // Bu2Dst0hst_Dst02D0gamma_sigma2Bu_(new RooFormulaVar(
      //     ("Bu2Dst0hst_Dst02D0gamma_sigma2Bu_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Sigma2 of Bu2Dst0hst_Dst02D0gamma Gaussian " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     "@0*@1",
      //     RooArgList(
      //         NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
      //             .Bu2Dst0hst_Dst02D0gamma_sigma2Bu(),
      //         NeutralVars<Neutral::gamma>::Get(uniqueId)
      //             .relativeBuWidth_Bu2Dst0hst_Dst02D0gamma()))),
      // pdf1Bu_Bu2Dst0hst_Dst02D0gamma_(
      //     ("pdf1Bu_Bu2Dst0hst_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0hst_Dst02D0gamma Bu PDF L " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0gamma_meanBu(),
      //     *Bu2Dst0hst_Dst02D0gamma_sigma1Bu_,
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0gamma_a1Bu(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0gamma_n1Bu()),
      // pdf2Bu_Bu2Dst0hst_Dst02D0gamma_(
      //     ("pdf2Bu_Bu2Dst0hst_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0hst_Dst02D0gamma Bu PDF R " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0gamma_meanBu(),
      //     *Bu2Dst0hst_Dst02D0gamma_sigma2Bu_,
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0gamma_a2Bu(),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0gamma_n2Bu()),
      // pdfBu_Bu2Dst0hst_Dst02D0gamma_(
      //     ("pdfBu_Bu2Dst0hst_Dst02D0gamma_" +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     ("Bu2Dst0hst_Dst02D0gamma Bu PDF " +
      //      ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
      //         .c_str(),
      //     RooArgSet(pdf1Bu_Bu2Dst0hst_Dst02D0gamma_,
      //     pdf2Bu_Bu2Dst0hst_Dst02D0gamma_),
      //     NeutralVars<Neutral::gamma>::Get(uniqueId)
      //         .Bu2Dst0hst_Dst02D0gamma_frac1PdfBu()),
      pdfBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0gamma_meanBu(),
          *Bu2Dst0hst_Dst02D0gamma_sigma1Bu_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0gamma_a1Bu(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0gamma_n1Bu()),
      pdf_Bu2Dst0hst_Dst02D0gamma_(
          ("pdf_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0hst_Dst02D0gamma(),
          RooFit::Conditional(pdfBu_Bu2Dst0hst_Dst02D0gamma_,
                              Configuration::Get().buMass())),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      misRec_sigma1Bu_(new RooFormulaVar(
          ("misRec_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma1 of Bu PDF of misRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .misRec_sigma1Bu(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_misRec()))),
      misRec_sigma2Bu_(nullptr),
      pdf1Bu_misRec_(),
      pdf2Bu_misRec_(),
      pdfBu_misRec_(new RooGaussian(
          ("pdfBu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF  " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).misRec_mean1Bu(),
          *misRec_sigma1Bu_)),
      pdf_misRec_(
          ("pdf_misRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_misRec(),
          RooFit::Conditional(*pdfBu_misRec_, Configuration::Get().buMass())) {}
