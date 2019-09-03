#include "NeutralBachelorVars.h"

// Bachelor specializations

// NEEED A COMPOSE NAME FOR EVERY CLASS: Move to Configuration and make
// overloaded functions.
// Use pointers where we need DIFFERENT PDFs depending on the template
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : Bu2Dst0h_D0gamma_sigmaBu_(new RooFormulaVar(
          ("Bu2Dst0h_D0gamma_sigmaBu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2Dst0h_D0gamma_sigmaBu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2Dst0h_D0gamma()))),
      pdf1Bu_Bu2Dst0h_D0gamma_(
          ("pdf1Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_a1Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_n1Bu()),
      pdf2Bu_Bu2Dst0h_D0gamma_(
          ("pdf2Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_meanBu(),
          *Bu2Dst0h_D0gamma_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_a2Bu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0gamma_n2Bu()),
      pdfBu_Bu2Dst0h_D0gamma_(
          ("pdfBu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", RooArgSet(pdf1Bu_Bu2Dst0h_D0gamma_, pdf2Bu_Bu2Dst0h_D0gamma_),
          NeutralVars<Neutral::pi0>::Get(uniqueId)
              .Bu2Dst0h_D0gamma_frac1PdfBu()),
      N_tot_Bu2Dst0h_D0gamma_(
          ("N_tot_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "",
          NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .initYieldFAVBu2Dst0pi_D0gamma() *
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .orEffBu2Dst0h_D0gamma()
                  .getVal() *
              0.07930,
          -1000000, 1000000),
      pidEff_Bu2Dst0h_D0gamma_(
          ("pidEff_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 0.703381),
      N_Bu2Dst0h_D0gamma_(
          ("N_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "@0*@1",
          RooArgList(N_tot_Bu2Dst0h_D0gamma_, pidEff_Bu2Dst0h_D0gamma_)),
      N_Delta_Bu2Dst0h_D0gamma_(
          ("N_Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .buDeltaCutEffBu2Dst0h_D0gamma(),
                     NeutralVars<Neutral::pi0>::Get(uniqueId)
                         .orEffBu2Dst0h_D0gamma(),
                     N_Bu2Dst0h_D0gamma_)),
      N_Bu_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Mis-ID ------------------- //
      misId_Bu2Dst0h_D0gamma_meanBu_(
          ("misId_Bu2Dst0h_D0gamma_meanBu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 5.2313e+03),
      misId_Bu2Dst0h_D0gamma_sigma1Bu_(
          ("misId_Bu2Dst0h_D0gamma_sigma1Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 3.4880e+01),
      misId_Bu2Dst0h_D0gamma_sigma2Bu_(
          ("misId_Bu2Dst0h_D0gamma_sigma2Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1.9927e+01),
      misId_Bu2Dst0h_D0gamma_a1Bu_(
          ("misId_Bu2Dst0h_D0gamma_a1Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1.0462e-01),
      misId_Bu2Dst0h_D0gamma_a2Bu_(
          ("misId_Bu2Dst0h_D0gamma_a2Bu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 7.0839e-02),
      misId_Bu2Dst0h_D0gamma_n1Bu_(),
      misId_Bu2Dst0h_D0gamma_n2Bu_(),
      pdf1Bu_misId_Bu2Dst0h_D0gamma_(),
      pdf2Bu_misId_Bu2Dst0h_D0gamma_(),
      misId_Bu2Dst0h_D0gamma_frac1PdfBu_(),
      pdfBu_misId_Bu2Dst0h_D0gamma_(new RooCruijff(
          ("pdfBu_misId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          misId_Bu2Dst0h_D0gamma_meanBu_, misId_Bu2Dst0h_D0gamma_sigma1Bu_,
          misId_Bu2Dst0h_D0gamma_sigma2Bu_, misId_Bu2Dst0h_D0gamma_a1Bu_,
          misId_Bu2Dst0h_D0gamma_a2Bu_)),
      orEffMisId_Bu2Dst0h_D0gamma_(
          ("orEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      boxEffMisId_Bu2Dst0h_D0gamma_(
          ("boxEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      buDeltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("buDeltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      deltaCutEffMisId_Bu2Dst0h_D0gamma_(
          ("deltaCutEffMisId_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 1),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      Bu2Dst0h_D0pi0_sigmaBu_(
          ("Bu2Dst0h_D0pi0_sigmaBu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", 4.6911e+01),
      pdfBu_Bu2Dst0h_D0pi0_(
          ("pdfBu_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_meanBu(),
          Bu2Dst0h_D0pi0_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_aBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2Dst0h_D0pi0_nBu()),
      N_Bu2Dst0h_D0pi0_(("N_Bu2Dst0h_D0pi0_" +
                         ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                            .c_str(),
                        "",
                        NeutralVars<Neutral::pi0>::Get(uniqueId)
                                .initYieldFAVBu2Dst0pi_D0pi0() *
                            NeutralVars<Neutral::pi0>::Get(uniqueId)
                                .orEffBu2Dst0h_D0pi0()
                                .getVal() *
                            0.07930,
                        -1000000, 1000000),
      N_Delta_Bu2Dst0h_D0pi0_(
          ("N_Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .buDeltaCutEffBu2Dst0h_D0pi0(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
              N_Bu2Dst0h_D0pi0_)),
      N_Bu_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- MIS-REC -------------------- //
      MisRec_sigmaBu_(("MisRec_sigmaBu_" +
                       ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
                          .c_str(),
                      "", 9.4812e+01),
      pdfBu_MisRec_(
          ("pdfBu_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_meanBu(),
          MisRec_sigmaBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_aBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).MisRec_nBu()),
      N_MisRec_(
          ("N_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "",
          NeutralVars<Neutral::pi0>::Get(uniqueId).initYieldFAVMisRec() *
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .orEffMisRec()
                  .getVal() *
              0.06,
          -1000000, 1000000),
      N_Delta_MisRec_(
          ("N_Delta_MisRec_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId).buDeltaCutEffMisRec(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).orEffMisRec(),
              N_MisRec_)),
      N_Bu_MisRec_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      Bu2D0h_sigmaLBu_(new RooFormulaVar(
          ("Bu2D0h_sigmaLBu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2D0h_sigmaLBu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2D0h()))),
      Bu2D0h_sigmaRBu_(new RooFormulaVar(
          ("Bu2D0h_sigmaRBu_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", "@0*@1",
          RooArgList(
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                  .Bu2D0h_sigmaRBu(),
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .relativeBuWidth_Bu2D0h()))),
      pdfBu_Bu2D0h_(
          ("pdfBu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "", Configuration::Get().buDeltaMass(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_meanBu(),
          *Bu2D0h_sigmaLBu_, *Bu2D0h_sigmaRBu_,
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aLBu(),
          NeutralVars<Neutral::pi0>::Get(uniqueId).Bu2D0h_aRBu()),
      N_Bu2D0h_(
          ("N_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "",
          NeutralVars<Neutral::pi0>::Get(uniqueId).initYieldFAVBu2D0pi() *
              NeutralVars<Neutral::pi0>::Get(uniqueId)
                  .orEffBu2D0h()
                  .getVal() *
              0.07768,
          -1000000, 1000000),
      N_Delta_Bu2D0h_(
          ("N_Delta_Bu2D0h_" +
           ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<Neutral::pi0>::Get(uniqueId).buDeltaCutEffBu2D0h(),
              NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2D0h(),
              N_Bu2D0h_)),
      N_Bu_Bu2D0h_(nullptr) {
  SetMisIdEfficiencies(Mode::Bu2Dst0pi_D0gamma, orEffMisId_Bu2Dst0h_D0gamma_,
                       boxEffMisId_Bu2Dst0h_D0gamma_,
                       buDeltaCutEffMisId_Bu2Dst0h_D0gamma_,
                       deltaCutEffMisId_Bu2Dst0h_D0gamma_);

  if (Configuration::Get().fit1D() == false) {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::pi0>::Get(uniqueId)
                .deltaCutEffBu2Dst0h_D0gamma(),
            NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
            N_Bu2Dst0h_D0gamma_)));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::pi0>::Get(uniqueId)
                .deltaCutEffBu2Dst0h_D0pi0(),
            NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
            N_Bu2Dst0h_D0pi0_)));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::pi0>::Get(uniqueId).deltaCutEffMisRec(),
            NeutralVars<Neutral::pi0>::Get(uniqueId).orEffMisRec(),
            N_MisRec_)));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<Neutral::pi0>::Get(uniqueId).deltaCutEffBu2D0h(),
            NeutralVars<Neutral::pi0>::Get(uniqueId).orEffBu2D0h(),
            N_Bu2D0h_)));
  } else {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
            .c_str(),
        "@0*@1",
        RooArgList(N_tot_Bu2Dst0h_D0gamma_, pidEff_Bu2Dst0h_D0gamma_)));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                .N_Bu_Bu2Dst0h_D0pi0()
                .getVal() *
            0.07930,
        -1000000, 1000000));
    N_Bu_MisRec_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                .N_Bu_MisRec()
                .getVal() *
            0.06,
        -1000000, 1000000));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, Neutral::pi0, Bachelor::k))
            .c_str(),
        "",
        NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                .N_Bu_MisRec()
                .getVal() *
            0.07768,
        -1000000, 1000000));
  }
      }
