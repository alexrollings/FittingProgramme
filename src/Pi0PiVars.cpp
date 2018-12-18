#include "NeutralBachelorVars.h"
// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0pi0_sigma1Bu_(
          new RooPolyVar(("Bu2Dst0h_Dst02D0pi0_sigma1Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("Sigma1 of Bu PDF of Bu2Dst0h_Dst02D0pi0 Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a0Sigma1Bu(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a1Sigma1Bu()))),
      // NeutralVars<Neutral::pi0>::Get(uniqueId)
      //     .Bu2Dst0h_Dst02D0pi0_a2Sigma1Bu()))),
      Bu2Dst0h_Dst02D0pi0_sigma2Bu_(
          new RooPolyVar(("Bu2Dst0h_Dst02D0pi0_sigma2Bu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("Sigma2 of Bu PDF of Bu2Dst0h_Dst02D0pi0 " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a0Sigma2Bu(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a1Sigma2Bu()))),
      // NeutralVars<Neutral::pi0>::Get(uniqueId)
      //     .Bu2Dst0h_Dst02D0pi0_a2Sigma2Bu()))),
      pdf1Bu_Bu2Dst0h_Dst02D0pi0_(
          ("pdf1Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_mean1Bu(),
          *Bu2Dst0h_Dst02D0pi0_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_n1Bu()),
      pdf2Bu_Bu2Dst0h_Dst02D0pi0_(new RooCBShape(
          ("pdf2Bu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_mean1Bu(),
          *Bu2Dst0h_Dst02D0pi0_sigma2Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_n2Bu())),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          RooArgSet(pdf1Bu_Bu2Dst0h_Dst02D0pi0_, *pdf2Bu_Bu2Dst0h_Dst02D0pi0_),
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
      Bu2Dst0h_Dst02D0gamma_sigma1Bu_(new RooPolyVar(
          ("Bu2Dst0h_Dst02D0gamma_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma1 of Bu PDF of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .Bu2Dst0h_Dst02D0gamma_a0Sigma1Bu(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .Bu2Dst0h_Dst02D0gamma_a1Sigma1Bu(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .Bu2Dst0h_Dst02D0gamma_a2Sigma1Bu()))),
      Bu2Dst0h_Dst02D0gamma_sigma2Bu_(nullptr),
      pdf1Bu_Bu2Dst0h_Dst02D0gamma_(),
      pdf2Bu_Bu2Dst0h_Dst02D0gamma_(),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(new RooCBShape(
          ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_meanBu(),
          *Bu2Dst0h_Dst02D0gamma_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0gamma_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0gamma_n1Bu())),
      pdf_Bu2Dst0h_Dst02D0gamma_(
          ("pdf_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .pdfDelta_Bu2Dst0h_Dst02D0gamma(),
          RooFit::Conditional(*pdfBu_Bu2Dst0h_Dst02D0gamma_,
                              Configuration::Get().buMass())),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      overRec_sigma1Bu_(new RooPolyVar(
          ("overRec_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma1 of Bu PDF of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_a0Sigma1Bu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_a1Sigma1Bu()))),
      overRec_sigma2Bu_(new RooPolyVar(
          ("overRec_sigma2Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma2 of Bu PDF of overRec " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_a0Sigma2Bu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_a1Sigma2Bu()))),
      pdf1Bu_overRec_(
          ("pdf1Bu_overRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF L " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_mean1Bu(),
          *overRec_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_n1Bu()),
      pdf2Bu_overRec_(new RooCBShape(
          ("pdf2Bu_overRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF R " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_mean2Bu(),
          *overRec_sigma2Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_n2Bu())),
      pdfBu_overRec_(
          ("pdfBu_overRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("overRec Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          RooArgSet(pdf1Bu_overRec_, *pdf2Bu_overRec_),
          NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_frac1PdfBu()),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("overRec 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // -------------------- Pi0 PART RECONSTRUCTED BKG --------------------
      Bu2Dst0hst_Dst02D0pi0_sigma1Bu_(new RooPolyVar(
          ("Bu2Dst0hst_Dst02D0pi0_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma1 of Bu PDF of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .Bu2Dst0hst_Dst02D0pi0_a0Sigma1Bu(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .Bu2Dst0hst_Dst02D0pi0_a1Sigma1Bu()))),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(new RooCBShape(
          ("pdfBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0pi0_meanBu(),
          *Bu2Dst0hst_Dst02D0pi0_sigma1Bu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0hst_Dst02D0pi0_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0hst_Dst02D0pi0_n1Bu())),
      pdf_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .pdfDelta_Bu2Dst0hst_Dst02D0pi0(),
          RooFit::Conditional(*pdfBu_Bu2Dst0hst_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // -------------------- Gamma PART RECONSTRUCTED BKG --------------------
      Bu2Dst0hst_Dst02D0gamma_sigma1Bu_(new RooPolyVar(
          ("Bu2Dst0hst_Dst02D0gamma_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma1 of Bu PDF of Bu2Dst0hst_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .Bu2Dst0hst_Dst02D0gamma_a0Sigma1Bu(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .Bu2Dst0hst_Dst02D0gamma_a1Sigma1Bu(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .Bu2Dst0hst_Dst02D0gamma_a2Sigma1Bu()))),
      pdfBu_Bu2Dst0hst_Dst02D0gamma_(
          new RooGaussian(("pdfBu_Bu2Dst0hst_Dst02D0gamma_" +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                              .c_str(),
                          ("Bu2Dst0hst_Dst02D0gamma Bu PDF " +
                           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                              .c_str(),
                          Configuration::Get().buMass(),
                          NeutralVars<Neutral::pi0>::Get(uniqueId)
                              .Bu2Dst0hst_Dst02D0gamma_meanBu(),
                          *Bu2Dst0hst_Dst02D0gamma_sigma1Bu_)),
      pdf_Bu2Dst0hst_Dst02D0gamma_(
          ("pdf_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .pdfDelta_Bu2Dst0hst_Dst02D0gamma(),
          RooFit::Conditional(*pdfBu_Bu2Dst0hst_Dst02D0gamma_,
                              Configuration::Get().buMass())),
      // -------------------- MIS RECONSTRUCTED BKG -------------------- //
      // -------------------- Bu2D0hst COMPONENT -------------------- //
      Bu2D0hst_sigmaBu_(new RooPolyVar(
          ("Bu2D0hst_sigmaBu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma1 of Bu PDF of Bu2D0hst Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0hst_a0SigmaBu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0hst_a1SigmaBu()))),
      pdfBu_Bu2D0hst_(
          ("pdfBu_Bu2D0hst_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2D0hst of 2 CBs in Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0hst_meanBu(),
          *Bu2D0hst_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0hst_aBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0hst_nBu()),
      pdf_Bu2D0hst_(
          ("pdf_Bu2D0hst_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2D0hst 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_Bu2D0hst(),
          RooFit::Conditional(pdfBu_Bu2D0hst_, Configuration::Get().buMass())),
      // -------------------- Bd2Dsth COMPONENT -------------------- //
      Bd2Dsth_sigmaBu_(new RooPolyVar(
          ("Bd2Dsth_sigmaBu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Sigma1 of Bu PDF of Bd2Dsth Gaussian " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId).Bd2Dsth_a0SigmaBu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).Bd2Dsth_a1SigmaBu()))),
      pdfBu_Bd2Dsth_(
          ("pdfBu_Bd2Dsth_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bd2Dsth of 2 CBs in Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bd2Dsth_meanBu(),
          *Bd2Dsth_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bd2Dsth_aBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bd2Dsth_nBu()),
      pdf_Bd2Dsth_(
          ("pdf_Bd2Dsth_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bd2Dsth 2D PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_Bd2Dsth(),
          RooFit::Conditional(pdfBu_Bd2Dsth_, Configuration::Get().buMass())),
      // -------------------- MIS-REC PDF -------------------- //
      misRec_fracPdf_(("misRec_fracPdf_" +
                       ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                          .c_str(),
                      "", 3.093, 0, 5),
      pdf_misRec_(("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
                   ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                      .c_str(),
                  ("Bu2Dst0h_Dst02D0pi0 of 2 CBs in Bu PDF " +
                   ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                      .c_str(),
                  RooArgSet(pdf_Bu2D0hst_, pdf_Bd2Dsth_), misRec_fracPdf_) {}
