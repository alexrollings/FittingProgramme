#include "NeutralDaughtersVars.h"
#include "Params.h"
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
    : uniqueId_(uniqueId),
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0pi0", uniqueId, Neutral::pi0,
          Daughters::kpi, 0.07930, -2, 2)),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId, Neutral::pi0, Daughters::kpi, 0.06,
          -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId, Neutral::pi0, Daughters::kpi,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId, Neutral::pi0, Daughters::kpi, 0.02,
          -2, 2)) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId, Neutral::pi0, Daughters::kk, 0.06,
          -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId, Neutral::pi0, Daughters::kk,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId, Neutral::pi0, Daughters::kk, 0.02,
          -2, 2)) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0pi0_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0pi0_Blind", uniqueId, Neutral::pi0, Daughters::kk,
            1.138, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("R_CP_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi, Daughters::kk))
                .c_str(),
            "Blind",
            ("R_CP_Bu2Dst0h_D0pi0_" +
             ComposeName(uniqueId_, Neutral::pi0, Bachelor::pi, Daughters::kk))
                .c_str(),
            0.5, *R_CP_Bu2Dst0h_D0pi0_Blind_));
  } else {
    R_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0pi0", uniqueId, Neutral::pi0, Daughters::kk, 1.138,
            -2, 2));
  }
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::pi0, Daughters::kk))
              .c_str(),
          "@0*@1",
          RooArgList(
              NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId_)
                  .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
              *R_CP_Bu2Dst0h_D0pi0_)));
}

// R_CP = R_kk = R_ππ
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_MisRec_GetPointer()),
      R_Dst0KDst0pi_Bu2D0h_(
          NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2D0h_GetPointer()),
      R_Dst0KDst0pi_PartRec_(
          NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_PartRec_GetPointer()) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0pi0_Blind_ =
        NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
            .R_CP_Bu2Dst0h_D0pi0_Blind_GetPointer();
  }
  R_CP_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
          .R_CP_Bu2Dst0h_D0pi0_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer();
}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId, Neutral::pi0, Daughters::pik, 0.06,
          -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId, Neutral::pi0, Daughters::pik,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId, Neutral::pi0, Daughters::pik, 0.02,
          -2, 2)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0gamma", uniqueId, Neutral::gamma,
          Daughters::kpi, 0.07930, -2, 2)),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0pi0", uniqueId, Neutral::gamma,
          Daughters::kpi, 0.07930, -2, 2)),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId, Neutral::gamma, Daughters::kpi,
          0.06, -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId, Neutral::gamma, Daughters::kpi,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId, Neutral::gamma, Daughters::kpi,
          0.02, -2, 2)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId, Neutral::gamma, Daughters::kk, 0.06,
          -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId, Neutral::gamma, Daughters::kk,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId, Neutral::gamma, Daughters::kk,
          0.02, -2, 2)) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0gamma_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0gamma_Blind", uniqueId, Neutral::gamma,
            Daughters::kk, 0.902, -2, 2));
    R_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(
        new RooUnblindUniform(("R_CP_Bu2Dst0h_D0gamma_" +
                               ComposeName(uniqueId_, Neutral::gamma,
                                           Bachelor::pi, Daughters::kk))
                                  .c_str(),
                              "Blind",
                              ("R_CP_Bu2Dst0h_D0gamma_" +
                               ComposeName(uniqueId_, Neutral::gamma,
                                           Bachelor::pi, Daughters::kk))
                                  .c_str(),
                              0.5, *R_CP_Bu2Dst0h_D0gamma_Blind_));
    R_CP_Bu2Dst0h_D0pi0_Blind_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0pi0_Blind", uniqueId, Neutral::gamma,
            Daughters::kk, 1.138, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooUnblindUniform>(new RooUnblindUniform(
            ("R_CP_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::gamma,
                                                  Bachelor::pi, Daughters::kk))
                .c_str(),
            "Blind",
            ("R_CP_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Neutral::gamma,
                                                  Bachelor::pi, Daughters::kk))
                .c_str(),
            0.5, *R_CP_Bu2Dst0h_D0pi0_Blind_));
  } else {
    R_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0gamma", uniqueId, Neutral::gamma, Daughters::kk,
            0.902, -2, 2));
    R_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "R_CP_Bu2Dst0h_D0pi0", uniqueId, Neutral::gamma, Daughters::kk,
            1.138, -2, 2));
  }
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId_, Neutral::gamma, Daughters::kk))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(
                         uniqueId_)
                         .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
                     *R_CP_Bu2Dst0h_D0gamma_)));
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId_, Neutral::gamma, Daughters::kk))
              .c_str(),
          "@0*@1",
          RooArgList(NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(
                         uniqueId_)
                         .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
                     *R_CP_Bu2Dst0h_D0pi0_)));
}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_MisRec_GetPointer()),
      R_Dst0KDst0pi_Bu2D0h_(
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2D0h_GetPointer()),
      R_Dst0KDst0pi_PartRec_(
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_PartRec_GetPointer()) {
  if (Configuration::Get().blindFit() == true) {
    R_CP_Bu2Dst0h_D0gamma_Blind_ =
        NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
            .R_CP_Bu2Dst0h_D0gamma_Blind_GetPointer();
    R_CP_Bu2Dst0h_D0pi0_Blind_ =
        NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
            .R_CP_Bu2Dst0h_D0pi0_Blind_GetPointer();
  }
  R_CP_Bu2Dst0h_D0gamma_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
          .R_CP_Bu2Dst0h_D0gamma_GetPointer();
  R_CP_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
          .R_CP_Bu2Dst0h_D0pi0_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer();
}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      R_CP_Bu2Dst0h_D0gamma_(nullptr),
      R_CP_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::pik>(
          uniqueId_, "R_Dst0KDst0pi_MisRec_", 0.06)),
      R_Dst0KDst0pi_Bu2D0h_(Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::pik>(
          uniqueId_, "R_Dst0KDst0pi_Bu2D0h_", 0.07930)),
      R_Dst0KDst0pi_PartRec_(Make_R_Dst0KDst0pi<Neutral::gamma, Daughters::pik>(
          uniqueId_, "R_Dst0KDst0pi_PartRec_", 0.02)) {}
