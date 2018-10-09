#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0pi0_sigmaLBu_(
          new RooPolyVar(("Bu2Dst0h_Dst02D0pi0_sigmaLBu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("SigmaL of Bu PDF of Bu2Dst0h_Dst02D0pi0 Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a0SigmaLBu(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a1SigmaLBu(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a2SigmaLBu()))),
      Bu2Dst0h_Dst02D0pi0_sigmaRBu_(
          new RooPolyVar(("Bu2Dst0h_Dst02D0pi0_sigmaRBu_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0h_Dst02D0pi0 " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a0SigmaRBu(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a1SigmaRBu(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .Bu2Dst0h_Dst02D0pi0_a2SigmaRBu()))),
      pdfLBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_mean1Bu(),
          *Bu2Dst0h_Dst02D0pi0_sigmaLBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_nLBu()),
      pdfRBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_mean1Bu(),
          *Bu2Dst0h_Dst02D0pi0_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_aRBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_Dst02D0pi0_nRBu()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0pi0_, pdfRBu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_Dst02D0pi0_fracLRPdfBu()),
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
      Bu2Dst0h_Dst02D0gamma_sigmaLBu_(nullptr),
      Bu2Dst0h_Dst02D0gamma_sigmaRBu_(nullptr),
      pdfLBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfRBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfLRBu_Bu2Dst0h_Dst02D0gamma_(),
      sigmaWideBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      pdfWideBu_Bu2Dst0h_Dst02D0gamma_(),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(),
      pdf_Bu2Dst0h_Dst02D0gamma_(),
      // -------------------- OVER RECONSTRUCTED BKG -------------------- //
      // sigmaBu_overRec_(
      //     new RooRealVar(("sigmaBu_overRec_" +
      //                     ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //                        .c_str(),
      //                    ("Sigma of overRec Gaussian " +
      //                     ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //                        .c_str(),
      //                    100, 50, 150)),
      // pdfBu_overRec_(
      //     ("pdfBu_overRec_" + ComposeName(uniqueId, Neutral::pi0,
      //     Bachelor::pi))
      //         .c_str(),
      //     ("overRec Bu PDF " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     Configuration::Get().buMass(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).overRec_meanBu(),
      //     *sigmaBu_overRec_),
      // pdf_overRec_(
      //     ("pdf_overRec_" + ComposeName(uniqueId, Neutral::pi0,
      //     Bachelor::pi))
      //         .c_str(),
      //     ("overRec 2D PDF " +
      //      ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
      //         .c_str(),
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_overRec(),
      //     RooFit::Conditional(pdfBu_overRec_,
      //     Configuration::Get().buMass())),
      overRec_sigmaLBu_(nullptr),
      overRec_sigmaRBu_(nullptr),
      pdfLBu_overRec_(),
      pdfRBu_overRec_(),
      pdfBu_overRec_(),
      pdf_overRec_(),
      // -------------------- Pi0 PART RECONSTRUCTED BKG --------------------
      Bu2Dst0hst_Dst02D0pi0_sigmaLBu_(nullptr),
      Bu2Dst0hst_Dst02D0pi0_sigmaRBu_(nullptr),
      pdfLBu_Bu2Dst0hst_Dst02D0pi0_(),
      pdfRBu_Bu2Dst0hst_Dst02D0pi0_(),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(),
      pdf_Bu2Dst0hst_Dst02D0pi0_(),
      // -------------------- Gamma PART RECONSTRUCTED BKG --------------------
      Bu2Dst0hst_Dst02D0gamma_sigmaLBu_(nullptr),
      Bu2Dst0hst_Dst02D0gamma_sigmaRBu_(nullptr),
      pdfLBu_Bu2Dst0hst_Dst02D0gamma_(),
      pdfRBu_Bu2Dst0hst_Dst02D0gamma_(),
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
// sigmaBu_misRec_(("sigmaBu_misRec_" +
//                  ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//                     .c_str(),
//                 ("Sigma of misRec Gaussian " +
//                  ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//                     .c_str(),
//                 60, 40, 80),
// pdfBu_misRec_(
//     ("pdfBu_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     ("misRec Bu PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     Configuration::Get().buMass(),
//     NeutralVars<Neutral::pi0>::Get(uniqueId).misRec_meanBu(),
//     sigmaBu_misRec_),
// pdf_misRec_(
//     ("pdf_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     ("misRec 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_misRec(),
//     RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}
