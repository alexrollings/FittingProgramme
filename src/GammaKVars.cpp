#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : sigmaLBu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaL of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      sigmaRBu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      pdfLBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfLBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaLBu_Bu2Dst0h_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aLBu_Bu2Dst0h_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nLBu_Bu2Dst0h_Dst02D0gamma()),
      pdfRBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaRBu_Bu2Dst0h_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aRBu_Bu2Dst0h_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nRBu_Bu2Dst0h_Dst02D0gamma()),
      pdfLRBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfLRBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF of 2 CBs " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0gamma_,
                    pdfRBu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0h_Dst02D0gamma()),
      sigmaWideBu_Bu2Dst0h_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaWideBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaWide of Bu2Dst0h_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaWideBu_Bu2Dst0h_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0gamma()))),
      pdfWideBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfWideBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF wide gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0gamma(),
          *sigmaWideBu_Bu2Dst0h_Dst02D0gamma_),
      pdfBu_Bu2Dst0h_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0gamma Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfWideBu_Bu2Dst0h_Dst02D0gamma_,
                    pdfLRBu_Bu2Dst0h_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracWidePdfBu_Bu2Dst0h_Dst02D0gamma()),
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
      sigmaLBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaL of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      sigmaRBu_Bu2Dst0h_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0h_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_Bu2Dst0h_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_Dst02D0pi0()))),
      pdfLBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean1Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaLBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aLBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nLBu_Bu2Dst0h_Dst02D0pi0()),
      pdfRBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .mean2Bu_Bu2Dst0h_Dst02D0pi0(),
          *sigmaRBu_Bu2Dst0h_Dst02D0pi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aRBu_Bu2Dst0h_Dst02D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nRBu_Bu2Dst0h_Dst02D0pi0()),
      pdfBu_Bu2Dst0h_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0h_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0h_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0h_Dst02D0pi0_, pdfRBu_Bu2Dst0h_Dst02D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0h_Dst02D0pi0()),
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
      sigmaLBu_overRec_(new RooFormulaVar(
          ("sigmaLBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaL of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_overRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_overRec()))),
      sigmaRBu_overRec_(new RooFormulaVar(
          ("sigmaRBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of overRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_overRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_overRec()))),
      pdfLBu_overRec_(
          ("pdfLBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean1Bu_overRec(),
          *sigmaLBu_overRec_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aLBu_overRec(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).nLBu_overRec()),
      pdfRBu_overRec_(
          ("pdfRBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean2Bu_overRec(),
          *sigmaRBu_overRec_,
          NeutralVars<Neutral::gamma>::Get(uniqueId).aRBu_overRec(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).nRBu_overRec()),
      pdfBu_overRec_(
          ("pdfBu_overRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_overRec_, pdfRBu_overRec_),
          NeutralVars<Neutral::gamma>::Get(uniqueId).fracLRPdfBu_overRec()),
      pdf_overRec_(
          ("pdf_overRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("overRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_overRec(),
          RooFit::Conditional(pdfBu_overRec_, Configuration::Get().buMass())),
      // ------------------ Pi0 PART RECONSTRUCTED BKG ------------------ //
      sigmaLBu_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaLBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaL of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_Bu2Dst0hst_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0pi0()))),
      sigmaRBu_Bu2Dst0hst_Dst02D0pi0_(new RooFormulaVar(
          ("sigmaRBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0hst_Dst02D0pi0 Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_Bu2Dst0hst_Dst02D0pi0(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0pi0()))),
      pdfLBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfLBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0hst_Dst02D0pi0(),
          *sigmaLBu_Bu2Dst0hst_Dst02D0pi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aLBu_Bu2Dst0hst_Dst02D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nLBu_Bu2Dst0hst_Dst02D0pi0()),
      pdfRBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfRBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0hst_Dst02D0pi0(),
          *sigmaRBu_Bu2Dst0hst_Dst02D0pi0_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aRBu_Bu2Dst0hst_Dst02D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nRBu_Bu2Dst0hst_Dst02D0pi0()),
      pdfBu_Bu2Dst0hst_Dst02D0pi0_(
          ("pdfBu_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0hst_Dst02D0pi0_,
          pdfRBu_Bu2Dst0hst_Dst02D0pi0_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0hst_Dst02D0pi0()),
      pdf_Bu2Dst0hst_Dst02D0pi0_(
          ("pdf_Bu2Dst0hst_Dst02D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0pi0 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .pdfDelta_Bu2Dst0hst_Dst02D0pi0(),
          RooFit::Conditional(pdfBu_Bu2Dst0hst_Dst02D0pi0_,
                              Configuration::Get().buMass())),
      // ------------------ Gamma PART RECONSTRUCTED BKG ------------------ //
      sigmaLBu_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaLBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaL of Bu2Dst0hst_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaLBu_Bu2Dst0hst_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0gamma()))),
      sigmaRBu_Bu2Dst0hst_Dst02D0gamma_(new RooFormulaVar(
          ("sigmaRBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("SigmaR of Bu2Dst0hst_Dst02D0gamma Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigmaRBu_Bu2Dst0hst_Dst02D0gamma(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0hst_Dst02D0gamma()))),
      pdfLBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfLBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF L " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0hst_Dst02D0gamma(),
          *sigmaLBu_Bu2Dst0hst_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aLBu_Bu2Dst0hst_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nLBu_Bu2Dst0hst_Dst02D0gamma()),
      pdfRBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfRBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF R " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .meanBu_Bu2Dst0hst_Dst02D0gamma(),
          *sigmaRBu_Bu2Dst0hst_Dst02D0gamma_,
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .aRBu_Bu2Dst0hst_Dst02D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .nRBu_Bu2Dst0hst_Dst02D0gamma()),
      pdfBu_Bu2Dst0hst_Dst02D0gamma_(
          ("pdfBu_Bu2Dst0hst_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Bu2Dst0hst_Dst02D0gamma Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdfLBu_Bu2Dst0hst_Dst02D0gamma_,
          pdfRBu_Bu2Dst0hst_Dst02D0gamma_),
          NeutralVars<Neutral::gamma>::Get(uniqueId)
              .fracLRPdfBu_Bu2Dst0hst_Dst02D0gamma()),
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
      sigma1Bu_misRec_(new RooFormulaVar(
          ("sigma1Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma1 of Bu PDF of misRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigma1Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_misRec()))),
      sigma2Bu_misRec_(new RooFormulaVar(
          ("sigma2Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma2 of Bu PDF of misRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigma2Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_misRec()))),
      sigma3Bu_misRec_(new RooFormulaVar(
          ("sigma3Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("Sigma3 of Bu PDF of misRec Gaussian " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                  .sigma3Bu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId)
                  .relativeBuWidth_misRec()))),
      pdf1Bu_misRec_(
          ("pdf1Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF 1 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean1Bu_misRec(),
          *sigma1Bu_misRec_),
      pdf2Bu_misRec_(
          ("pdf2Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF 2 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean2Bu_misRec(),
          *sigma2Bu_misRec_),
      pdf3Bu_misRec_(
          ("pdf3Bu_misRec_" +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF 3 " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          Configuration::Get().buMass(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).mean3Bu_misRec(),
          *sigma3Bu_misRec_),
      pdfBu_misRec_(
          ("pdfBu_misRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec Bu PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          RooArgSet(pdf1Bu_misRec_, pdf2Bu_misRec_, pdf3Bu_misRec_),
          RooArgSet(
              NeutralVars<Neutral::gamma>::Get(uniqueId).frac1PdfBu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).frac2PdfBu_misRec(),
              NeutralVars<Neutral::gamma>::Get(uniqueId).frac3PdfBu_misRec())),
      pdf_misRec_(
          ("pdf_misRec_" + ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          ("misRec 2D PDF " +
           ComposeName(uniqueId, Neutral::gamma, Bachelor::k))
              .c_str(),
          NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_misRec(),
          RooFit::Conditional(pdfBu_misRec_, Configuration::Get().buMass())) {}
