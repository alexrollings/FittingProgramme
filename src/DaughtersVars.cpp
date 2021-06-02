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
          "R_Dst0KDst0pi_Bu2Dst0h", uniqueId_, Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
          0, 2)),
      // R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
      //     "R_Dst0KDst0pi_Bu2Dst0h_D0gamma", uniqueId_, Daughters::kpi,
      //     8.1e-02, 0., Systematic::NA, Sign::same)),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(R_Dst0KDst0pi_Bu2Dst0h_D0gamma_),
      // R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
      //     "R_Dst0KDst0pi_Bu2Dst0h_D0pi0", uniqueId_, Daughters::kpi,
      //     GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
      //         GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
      //     0, 2)),
      // R_Dst0KDst0pi_Bu2Dst0h_WN_(Params::Get().CreateFloating(
      //     "R_Dst0KDst0pi_Bu2Dst0h_WN", uniqueId_, Daughters::kpi,
      //     GlobalVars::Get(uniqueId_).kBF_Bu2Dst0K().getVal() /
      //         GlobalVars::Get(uniqueId_).kBF_Bu2Dst0pi().getVal(),
      //     0, 2)),
      // R_Dst0KDst0pi_Bu2Dst0h_WN_(Params::Get().CreateFixed(
      //     "R_Dst0KDst0pi_Bu2Dst0h_WN", uniqueId_, Daughters::kpi, 0.08, 0,
      //     Systematic::NA, Sign::same)),
      R_Dst0KDst0pi_Bu2Dst0h_WN_(R_Dst0KDst0pi_Bu2Dst0h_D0gamma_),
      //  Calculated from BFs using python uncertainties
      R_Dst0KDst0pi_Bd2Dsth_(Params::Get().CreateFixed(
          "R_Dst0KDst0pi_Bd2Dsth", uniqueId_, Daughters::kpi, 0.0774, 0.0066,
          Systematic::R_Dst0KDst0pi_Bd2Dsth, Sign::same)),
      //  Calculated average from BFs of B+ -> D0rho+ and B0 -> D0 rho0
      R_Dst0KDst0pi_Bu2D0hst_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2D0hst", uniqueId_, Daughters::kpi, 0.02, 0, 2)),
      // R_Dst0KDst0pi_Bu2D0hst_(Params::Get().CreateFixed(
      //     "R_Dst0KDst0pi_Bu2D0hst", uniqueId_, Daughters::kpi, 0.02,
      //     5.34e-03, Systematic::NA, Sign::same)),
      // Float as only pick up on part of D*rho phase space - R slightly lower
      R_Dst0KDst0pi_Bu2Dst0hst_(Params::Get().CreateFloating(
          "R_Dst0KDst0pi_Bu2Dst0hst", uniqueId_, Daughters::kpi,
          GlobalVars::Get(uniqueId_).kBF_Bu2Dst0Kst().getVal() /
              GlobalVars::Get(uniqueId_).kBF_Bu2Dst0rho().getVal(),
          -1, 1)),
      // 1.7676e-02
      R_Dst0KDst0pi_Lb2Omegach_Lcpi0_(nullptr) {}

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
      R_Dst0KDst0pi_Bu2Dst0h_WN_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0h_WN_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_WN(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2Dst0h_WN())),
      R_Dst0KDst0pi_Bd2Dsth_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bd2Dsth_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_).R_Dst0KDst0pi_Bd2Dsth(),
          GlobalVars::Get(uniqueId_).R_CP_Bd2Dsth())),
      R_Dst0KDst0pi_Bu2D0hst_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2D0hst_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2D0hst(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2D0hst())),
      R_Dst0KDst0pi_Bu2Dst0hst_(Make_R_Dst0KDst0pi_CP<Daughters::kk>(
          uniqueId_, "R_Dst0KDst0pi_Bu2Dst0hst_",
          DaughtersVars<Daughters::kpi>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0hst(),
          GlobalVars::Get(uniqueId_).R_CP_Bu2Dst0hst())),
      // Increase uncertainty: from Lb -> Lc K / Lb -> Lc π
      // R_Dst0KDst0pi_Lb2Omegach_Lcpi0_(Params::Get().CreateFloating(
      //     "R_Dst0KDst0pi_Lb2Omegach_Lcpi0", uniqueId_, Daughters::kk, 0.073,
      //     0, 2)) {}
      R_Dst0KDst0pi_Lb2Omegach_Lcpi0_(nullptr) {
  if (Configuration::Get().neutral() == Neutral::pi0) {
    R_Dst0KDst0pi_Lb2Omegach_Lcpi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "R_Dst0KDst0pi_Lb2Omegach_Lcpi0", uniqueId_, Daughters::kk, 0.073,
            0.073 * 0.5, Systematic::R_Dst0KDst0pi_Lb2Omegach_Lcpi0,
            Sign::same));
  } else {
    R_Dst0KDst0pi_Lb2Omegach_Lcpi0_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("R_Dst0KDst0pi_Lb2Omegach_Lcpi0",
                                     uniqueId_, Daughters::kk, 0.073, -1, 1));
  }
}

template <>
DaughtersVars<Daughters::pipi>::DaughtersVars(int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_GetPointer()),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer()),
      R_Dst0KDst0pi_Bu2Dst0h_WN_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0h_WN_GetPointer()),
      R_Dst0KDst0pi_Bd2Dsth_(DaughtersVars<Daughters::kk>::Get(uniqueId_)
                                 .R_Dst0KDst0pi_Bd2Dsth_GetPointer()),
      R_Dst0KDst0pi_Bu2D0hst_(DaughtersVars<Daughters::kk>::Get(uniqueId_)
                                  .R_Dst0KDst0pi_Bu2D0hst_GetPointer()),
      R_Dst0KDst0pi_Bu2Dst0hst_(
          DaughtersVars<Daughters::kk>::Get(uniqueId_)
              .R_Dst0KDst0pi_Bu2Dst0hst_GetPointer()),
      R_Dst0KDst0pi_Lb2Omegach_Lcpi0_(nullptr) {}

template <>
DaughtersVars<Daughters::pik>::DaughtersVars(int uniqueId)
    : uniqueId_(uniqueId),
      R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0h_WN_(nullptr),
      R_Dst0KDst0pi_Bd2Dsth_(nullptr),
      R_Dst0KDst0pi_Bu2D0hst_(nullptr),
      R_Dst0KDst0pi_Bu2Dst0hst_(nullptr),
      R_Dst0KDst0pi_Lb2Omegach_Lcpi0_(nullptr) {}

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
