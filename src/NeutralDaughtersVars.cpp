#include "NeutralDaughtersVars.h"
#include "RooUnblindUniform.h"

template <Neutral neutral, Daughters daughters>
RooRealVar *Make_R_Dst0KDst0pi(int uniqueId, const char *name, double val) {
  return new RooRealVar(
      (name + ComposeName(uniqueId, neutral, daughters)).c_str(), "", val, -2,
      2);
}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::kpi>(
              uniqueId, "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_", 0.07930)),
      R_Dst0KDst0pi_MisRec_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::kpi>(
              uniqueId, "R_Dst0KDst0pi_MisRec_", 0.06)),
      R_Dst0KDst0pi_Bu2D0h_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::kpi>(
              uniqueId, "R_Dst0KDst0pi_Bu2D0h_", 0.07930)),
      R_Dst0KDst0pi_PartRec_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::kpi>(
              uniqueId, "R_Dst0KDst0pi_PartRec_", 0.02)) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::kk>(
              uniqueId, "R_Dst0KDst0pi_MisRec_", 0.06)),
      R_Dst0KDst0pi_Bu2D0h_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::kk>(
              uniqueId, "R_Dst0KDst0pi_Bu2D0h_", 0.07930)),
      R_Dst0KDst0pi_PartRec_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::kk>(
              uniqueId, "R_Dst0KDst0pi_PartRec_", 0.02)) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        new RooRealVar(("R_CP_Bu2Dst0h_D0pi0_Blind_" +
                        ComposeName(uniqueId, Neutral::pi0, Daughters::kk))
                           .c_str(),
                       "", 1.138, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("R_CP_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, Daughters::kk))
                .c_str(),
            "Blind",
            ("R_CP_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, Neutral::pi0, Bachelor::pi, Daughters::kk))
                .c_str(),
            0.5, *R_CP_Bu2Dst0h_D0pi0_Blind_));
  } else {
    R_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(
        new RooRealVar(("R_CP_Bu2Dst0h_D0pi0_" +
                        ComposeName(uniqueId, Neutral::pi0, Daughters::kk))
                           .c_str(),
                       "", 1.138, -2, 2));
  }
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::pi0, Daughters::kk))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId)
                  .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
              *R_CP_Bu2Dst0h_D0pi0_)));
}

// R_CP = R_kk = R_ππ
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::pipi>(
              uniqueId, "R_Dst0KDst0pi_MisRec_", 0.06)),
      R_Dst0KDst0pi_Bu2D0h_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::pipi>(
              uniqueId, "R_Dst0KDst0pi_Bu2D0h_", 0.07930)),
      R_Dst0KDst0pi_PartRec_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::pipi>(
              uniqueId, "R_Dst0KDst0pi_PartRec_", 0.02)) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0pi0_Blind_ =
        NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId)
            .R_CP_Bu2Dst0h_D0pi0_Blind_GetPointer();
  }
  R_CP_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId)
          .R_CP_Bu2Dst0h_D0pi0_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId)
          .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer();
}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::pik>(
              uniqueId, "R_Dst0KDst0pi_MisRec_", 0.06)),
      R_Dst0KDst0pi_Bu2D0h_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::pik>(
              uniqueId, "R_Dst0KDst0pi_Bu2D0h_", 0.07930)),
      R_Dst0KDst0pi_PartRec_(
          Make_R_Dst0KDst0pi<Neutral::pi0, Daughters::pik>(
              uniqueId, "R_Dst0KDst0pi_PartRec_", 0.02)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::kpi>(
              uniqueId, "R_Dst0KDst0pi_Bu2Dst0h_D0gamma_", 0.07930)),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::kpi>(
              uniqueId, "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_", 0.07930)),
      R_Dst0KDst0pi_MisRec_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::kpi>(
              uniqueId, "R_Dst0KDst0pi_MisRec_", 0.06)),
      R_Dst0KDst0pi_Bu2D0h_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::kpi>(
              uniqueId, "R_Dst0KDst0pi_Bu2D0h_", 0.07930)),
      R_Dst0KDst0pi_PartRec_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::kpi>(
              uniqueId, "R_Dst0KDst0pi_PartRec_", 0.02)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::kk>(
              uniqueId, "R_Dst0KDst0pi_MisRec_", 0.06)),
      R_Dst0KDst0pi_Bu2D0h_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::kk>(
              uniqueId, "R_Dst0KDst0pi_Bu2D0h_", 0.07930)),
      R_Dst0KDst0pi_PartRec_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::kk>(
              uniqueId, "R_Dst0KDst0pi_PartRec_", 0.02)) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(
        new RooRealVar(("R_CP_Bu2Dst0h_D0gamma_Blind_" +
                        ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
                           .c_str(),
                       "", 0.902, -2, 2));
    R_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("R_CP_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, Daughters::kk))
                .c_str(),
            "Blind",
            ("R_CP_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, Daughters::kk))
                .c_str(),
            0.5, *R_CP_Bu2Dst0h_D0gamma_Blind_));
    R_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        new RooRealVar(("R_CP_Bu2Dst0h_D0pi0_Blind_" +
                        ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
                           .c_str(),
                       "", 1.138, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("R_CP_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, Daughters::kk))
                .c_str(),
            "Blind",
            ("R_CP_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId, Neutral::gamma, Bachelor::pi, Daughters::kk))
                .c_str(),
            0.5, *R_CP_Bu2Dst0h_D0pi0_Blind_));
  } else {
    R_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(
        new RooRealVar(("R_CP_Bu2Dst0h_D0gamma_" +
                        ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
                           .c_str(),
                       "", 0.902, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(
        new RooRealVar(("R_CP_Bu2Dst0h_D0pi0_" +
                        ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
                           .c_str(),
                       "", 1.138, -2, 2));
  }
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(
                         uniqueId)
                         .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
                     *R_CP_Bu2Dst0h_D0gamma_)));
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, Neutral::gamma, Daughters::kk))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(
                         uniqueId)
                         .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
                     *R_CP_Bu2Dst0h_D0pi0_)));
}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::pipi>(
              uniqueId, "R_Dst0KDst0pi_MisRec_", 0.06)),
      R_Dst0KDst0pi_Bu2D0h_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::pipi>(
              uniqueId, "R_Dst0KDst0pi_Bu2D0h_", 0.07930)),
      R_Dst0KDst0pi_PartRec_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::pipi>(
              uniqueId, "R_Dst0KDst0pi_PartRec_", 0.02)) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0gamma_Blind_ =
        NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId)
            .R_CP_Bu2Dst0h_D0gamma_Blind_GetPointer();
    R_CP_Bu2Dst0h_D0pi0_Blind_ =
        NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId)
            .R_CP_Bu2Dst0h_D0pi0_Blind_GetPointer();
  }
  R_CP_Bu2Dst0h_D0gamma_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId)
          .R_CP_Bu2Dst0h_D0gamma_GetPointer();
  R_CP_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId)
          .R_CP_Bu2Dst0h_D0pi0_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId)
          .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId)
          .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer();
}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::pik>(
              uniqueId, "R_Dst0KDst0pi_MisRec_", 0.06)),
      R_Dst0KDst0pi_Bu2D0h_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::pik>(
              uniqueId, "R_Dst0KDst0pi_Bu2D0h_", 0.07930)),
      R_Dst0KDst0pi_PartRec_(
          Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::pik>(
              uniqueId, "R_Dst0KDst0pi_PartRec_", 0.02)) {}
