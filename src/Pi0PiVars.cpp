#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaLBu_Bu2Dst0h_Dst02D0pi0_(
          new RooPolyVar(("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("SigmaL of Bu PDF of Bu2Dst0h_Dst02D0pi0 Gaussian " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a0SigmaLBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a1SigmaLBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a2SigmaLBu_Bu2Dst0h_Dst02D0pi0()))),
      sigmaRBu_Bu2Dst0h_Dst02D0pi0_(
          new RooPolyVar(("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         ("SigmaR of Bu PDF of Bu2Dst0h_Dst02D0pi0 " +
                          ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
                             .c_str(),
                         Configuration::Get().deltaMass(),
                         RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a0SigmaRBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a1SigmaRBu_Bu2Dst0h_Dst02D0pi0(),
                                    NeutralVars<Neutral::pi0>::Get(uniqueId)
                                        .a2SigmaRBu_Bu2Dst0h_Dst02D0pi0()))),
      pdfLBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaLBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).aLBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).nLBu_Bu2Dst0h_Dst02D0pi0()),
      pdfRBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).aRBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).nRBu_Bu2Dst0h_Dst02D0pi0()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0pi0_, pdfRBu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0h_Dst02D0pi0()),
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
      sigmaLBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
      sigmaRBu_Bu2Dst0h_Dst02D0gamma_(nullptr),
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
      //     NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_overRec(),
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
      sigmaLBu_overRec_(nullptr),
      sigmaRBu_overRec_(nullptr),
      pdfLBu_overRec_(),
      pdfRBu_overRec_(),
      pdfBu_overRec_(),
      pdf_overRec_(),
      // -------------------- Pi0 PART RECONSTRUCTED BKG --------------------
      sigmaLBu_Bu2Dst0hst_Dst02D0pi0_(nullptr),
      sigmaRBu_Bu2Dst0hst_Dst02D0pi0_(nullptr),
      pdfLBu_Bu2Dst0hst_Dst02D0pi0_(),
      pdfRBu_Bu2Dst0hst_Dst02D0pi0_(),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(),
      pdf_Bu2Dst0hst_Dst02D0pi0_(),
      // -------------------- Gamma PART RECONSTRUCTED BKG --------------------
      sigmaLBu_Bu2Dst0hst_Dst02D0gamma_(nullptr),
      sigmaRBu_Bu2Dst0hst_Dst02D0gamma_(nullptr),
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
//     NeutralVars<Neutral::pi0>::Get(uniqueId).meanBu_misRec(),
//     sigmaBu_misRec_),
// pdf_misRec_(
//     ("pdf_misRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     ("misRec 2D PDF " + ComposeName(uniqueId, Neutral::pi0, Bachelor::pi))
//         .c_str(),
//     NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_misRec(),
//     RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}
