#include "NeutralDaughtersVars.h"
#include "NeutralVars.h"
#include "Params.h"

template <Neutral neutral, Daughters daughters>
RooFormulaVar *Make_R_Dst0KDst0pi_CP(int uniqueId, const char *name,
                                     RooAbsReal &R_Dst0KDst0pi_FAV,
                                     RooAbsReal &R_CP) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, neutral, daughters)).c_str(), "@0*@1",
      RooArgList(R_Dst0KDst0pi_FAV, R_CP));
}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0,
          Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      // Fix for gamma WN in π0 mode (systenatic taken care of in BF error)
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId_, Neutral::pi0, Daughters::kpi))
              .c_str(),
          "@0/@1",
          RooArgSet(GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K(),
                    GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi()))),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::pi0,
          Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      // R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
      //     "R_Dst0KDst0pi_Bu2Dst0h_D0pi0", uniqueId_, Neutral::pi0,
      //     Daughters::kpi, 0.0810, 0, Systematic::NA, Sign::positive)),
      R_Dst0KDst0pi_Bd2Dsth_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::pi0, Daughters::kpi))
              .c_str(),
          "@0/@1",
          RooArgSet(GlobalVars::Get(uniqueId_).kBF_Bd2DstK(),
                    GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi()))),
      R_Dst0KDst0pi_Bu2D0hst_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::pi0, Daughters::kpi))
              .c_str(),
          "@0/@1",
          RooArgSet(GlobalVars::Get(uniqueId_).kBF_Bu2D0Kst(),
                    GlobalVars::Get(uniqueId_).kBF_Bu2D0rho()))),
      R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0hst_D0pi0", uniqueId_, Neutral::pi0,
          Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0Kst().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal(),
          -5, 5)),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId_, Neutral::pi0, Daughters::kpi, 0.06,
          -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId_, Neutral::pi0, Daughters::kpi,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId_, Neutral::pi0, Daughters::kpi,
          0.02, -2, 2)) {}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_Dst0KDst0pi_Bd2Dsth_(nullptr),
      R_Dst0KDst0pi_Bu2D0hst_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId_, Neutral::pi0, Daughters::kk, 0.06,
          -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId_, Neutral::pi0, Daughters::kk,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId_, Neutral::pi0, Daughters::kk, 0.02,
          -2, 2)) {
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::pi0, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_",
          NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).R_CP_Bu2Dst0h_D0pi0()));
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::pi0, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_",
          NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_)
              .R_CP_Bu2Dst0h_D0gamma_WN()));
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::pi0, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_",
          NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).R_CP_Bu2Dst0h_D0pi0_WN()));
  R_Dst0KDst0pi_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::pi0, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bd2Dsth_",
          NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bd2Dsth(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).R_CP_Bd2Dsth()));
  R_Dst0KDst0pi_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::pi0, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2D0hst_",
          NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2D0hst(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).R_CP_Bu2D0hst()));
  R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::pi0, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_",
          NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0pi0(),
          NeutralVars<Neutral::pi0>::Get(uniqueId_).R_CP_Bu2Dst0hst_D0pi0()));
}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_Dst0KDst0pi_Bd2Dsth_(nullptr),
      R_Dst0KDst0pi_Bu2D0hst_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_MisRec_GetPointer()),
      R_Dst0KDst0pi_Bu2D0h_(
          NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2D0h_GetPointer()),
      R_Dst0KDst0pi_PartRec_(
          NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_PartRec_GetPointer()) {
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_GetPointer();
  R_Dst0KDst0pi_Bd2Dsth_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bd2Dsth_GetPointer();
  R_Dst0KDst0pi_Bu2D0hst_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2D0hst_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_ =
      NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_GetPointer();
}

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId_, Neutral::pi0, Daughters::pik, 0.06,
          -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId_, Neutral::pi0, Daughters::pik,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId_, Neutral::pi0, Daughters::pik,
          0.02, -2, 2)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
          Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      // R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
      //     "R_Dst0KDst0pi_Bu2Dst0h_D0gamma", uniqueId_, Neutral::gamma,
      //     Daughters::kpi, 0.0810, 0, Systematic::NA, Sign::positive)),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
          Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN", uniqueId_, Neutral::gamma,
          Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN", uniqueId_, Neutral::gamma,
          Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      // R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
      //     "R_Dst0KDst0pi_Bu2Dst0h_D0pi0", uniqueId_, Neutral::gamma,
      //     Daughters::kpi, 0.0810, 0, Systematic::NA, Sign::positive)),
      R_Dst0KDst0pi_Bd2Dsth_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bd2Dsth_" +
           ComposeName(uniqueId_, Neutral::gamma, Daughters::kpi))
              .c_str(),
          "@0/@1",
          RooArgSet(GlobalVars::Get(uniqueId_).kBF_Bd2DstK(),
                    GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi()))),
      R_Dst0KDst0pi_Bu2D0hst_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2D0hst_" +
           ComposeName(uniqueId_, Neutral::gamma, Daughters::kpi))
              .c_str(),
          "@0/@1",
          RooArgSet(GlobalVars::Get(uniqueId_).kBF_Bu2D0Kst(),
                    GlobalVars::Get(uniqueId_).kBF_Bu2D0rho()))),
      R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0hst_D0gamma", uniqueId_, Neutral::gamma,
          Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0Kst().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal(),
          -5, 5)),
      // Ratio of K/π for part rec should be same for Dgamma and Dπ0
      R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_(R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId_, Neutral::gamma, Daughters::kpi,
          0.06, -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId_, Neutral::gamma, Daughters::kpi,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId_, Neutral::gamma, Daughters::kpi,
          0.02, -2, 2)) {}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_Dst0KDst0pi_Bd2Dsth_(nullptr),
      R_Dst0KDst0pi_Bu2D0hst_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_(nullptr),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId_, Neutral::gamma, Daughters::kk,
          0.06, -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId_, Neutral::gamma, Daughters::kk,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId_, Neutral::gamma, Daughters::kk,
          0.02, -2, 2)) {
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::gamma, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0gamma_",
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).R_CP_Bu2Dst0h_D0gamma()));
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::gamma, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_",
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).R_CP_Bu2Dst0h_D0pi0()));
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::gamma, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_",
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .R_CP_Bu2Dst0h_D0gamma_WN()));
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::gamma, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_",
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_)
              .R_CP_Bu2Dst0h_D0pi0_WN()));
  R_Dst0KDst0pi_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::gamma, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bd2Dsth_",
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bd2Dsth(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).R_CP_Bd2Dsth()));
  R_Dst0KDst0pi_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::gamma, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2D0hst_",
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2D0hst(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).R_CP_Bu2D0hst()));
  R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::gamma, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_",
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0gamma(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).R_CP_Bu2Dst0hst_D0gamma()));
  R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooFormulaVar>(
      Make_R_Dst0KDst0pi_CP<Neutral::gamma, Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_",
          NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0pi0(),
          NeutralVars<Neutral::gamma>::Get(uniqueId_).R_CP_Bu2Dst0hst_D0pi0()));
}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_Dst0KDst0pi_MisRec_(
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_MisRec_GetPointer()),
      R_Dst0KDst0pi_Bu2D0h_(
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2D0h_GetPointer()),
      R_Dst0KDst0pi_PartRec_(
          NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_PartRec_GetPointer()) {
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_GetPointer();
  R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_ =
      NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(uniqueId_)
          .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_GetPointer();
}

template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_Dst0KDst0pi_MisRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_MisRec", uniqueId_, Neutral::gamma, Daughters::pik,
          0.06, -2, 2)),
      R_Dst0KDst0pi_Bu2D0h_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0h", uniqueId_, Neutral::gamma, Daughters::pik,
          0.07930, -2, 2)),
      R_Dst0KDst0pi_PartRec_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_PartRec", uniqueId_, Neutral::gamma, Daughters::pik,
          0.02, -2, 2)) {}

template <Neutral neutral, Daughters daughters>
NeutralDaughtersVars<neutral, daughters>
    &NeutralDaughtersVars<neutral, daughters>::Get(int uniqueId) {
  static std::map<int, std::shared_ptr<This_t>> singletons;
  // An iterator to a map is a std::pair<key, value>, so we need to call
  // i->second to get the value
  auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
  if (it == singletons.end()) {
    // If it doesn't, create it as a new shared_ptr by calling emplace, which
    // will forward the pointer to the constructor of std::shared_ptr
    it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId)).first;
  }
  return *it->second;
}

void InstantiateNeutralDaughtersVars() {
  NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::Get(-1);
  NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::Get(-1);
  NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::Get(-1);
  NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::Get(-1);
  NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::Get(-1);
  NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::Get(-1);
  NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::Get(-1);
  NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::Get(-1);
}
