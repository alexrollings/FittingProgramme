#include "DaughtersVars.h"
#include "GlobalVars.h"
#include "Params.h"

template <Daughters daughters>
RooFormulaVar *Make_R_Dst0KDst0pi_CP(int uniqueId, const char *name,
                                     RooAbsReal &R_Dst0KDst0pi_FAV,
                                     RooAbsReal &R_CP) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, daughters)).c_str(), "@0*@1",
      RooArgList(R_Dst0KDst0pi_FAV, R_CP));
}

template <>
DaughtersVars<Daughters::kpi>::DaughtersVars(int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0gamma", uniqueId_, Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      // R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
      //     "R_Dst0KDst0pi_Bu2Dst0h_D0gamma", uniqueId_,
      //     Daughters::kpi, 0.0810, 0, Systematic::NA, Sign::positive)),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0pi0", uniqueId_, Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN", uniqueId_, Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN", uniqueId_, Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          -2, 2)),
      // R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
      //     "R_Dst0KDst0pi_Bu2Dst0h_D0pi0", uniqueId_,
      //     Daughters::kpi, 0.0810, 0, Systematic::NA, Sign::positive)),
      R_Dst0KDst0pi_Bd2Dsth_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bd2Dsth_" + ComposeName(uniqueId_, Daughters::kpi))
              .c_str(),
          "@0/@1",
          RooArgSet(GlobalVars::Get(uniqueId_).kBF_Bd2DstK(),
                    GlobalVars::Get(uniqueId_).kBF_Bd2Dstpi()))),
      R_Dst0KDst0pi_Bu2D0hst_(new RooFormulaVar(
          ("R_Dst0KDst0pi_Bu2D0hst_" + ComposeName(uniqueId_, Daughters::kpi))
              .c_str(),
          "@0/@1",
          RooArgSet(GlobalVars::Get(uniqueId_).kBF_Bu2D0Kst(),
                    GlobalVars::Get(uniqueId_).kBF_Bu2D0rho()))),
      R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0hst_", uniqueId_, Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0Kst().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal(),
          -5, 5)),
      // Ratio of K/π for part rec should be same for Dgamma and Dπ0
      R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_(R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_) {}

template <>
DaughtersVars<Daughters::kk>::DaughtersVars(int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0gamma_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2Dst0h_D0gamma())),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2Dst0h_D0pi0())),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2Dst0h_D0gamma_WN())),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2Dst0h_D0pi0_WN())),
      R_Dst0KDst0pi_Bd2Dsth_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bd2Dsth_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_).R_Dst0KDst0pi_Bd2Dsth(),
          GlobalVars::Get(uniqueId_).R_CP_Bd2Dsth())),
      R_Dst0KDst0pi_Bu2D0hst_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2D0hst_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2D0hst(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2D0hst())),
      R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0gamma(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2Dst0hst_D0gamma())),
      R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0pi0(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2Dst0hst_D0pi0())) {}

template <>
DaughtersVars<Daughters::pipi>::DaughtersVars(int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_GetPointer()),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer()),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_GetPointer()),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_GetPointer()),
      R_Dst0KDst0pi_Bd2Dsth_(DaughtersVars<Daughters::kk>::Get(uniqueId_)
                                 .R_Dst0KDst0pi_Bd2Dsth_GetPointer()),
      R_Dst0KDst0pi_Bu2D0hst_(DaughtersVars<Daughters::kk>::Get(uniqueId_)
                                  .R_Dst0KDst0pi_Bu2D0hst_GetPointer()),
      R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_GetPointer()),
      R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_GetPointer()) {}

template <>
DaughtersVars<Daughters::pik>::DaughtersVars(int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_Dst0KDst0pi_Bd2Dsth_(nullptr),
      R_Dst0KDst0pi_Bu2D0hst_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_(nullptr) {}

template <Daughters daughters>
DaughtersVars<daughters> &DaughtersVars<daughters>::Get(
    int uniqueId) {
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

void InstantiateDaughtersVars() {
  DaughtersVars<Daughters::kpi>::Get(-1);
  DaughtersVars<Daughters::kk>::Get(-1);
  DaughtersVars<Daughters::pipi>::Get(-1);
  DaughtersVars<Daughters::pik>::Get(-1);
}
