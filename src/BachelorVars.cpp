#include "BachelorVars.h"
#include "GlobalVars.h"
#include "Params.h"

template <>
BachelorVars<Bachelor::pi>::BachelorVars(int uniqueId)
    : uniqueId_(uniqueId),
      // -------------------- CP Observables -------------------- //
      A_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_WN_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_WN_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_WN_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_WN_(nullptr),
      A_CP_Bd2Dsth_(nullptr),
      A_CP_Bu2D0hst_(nullptr),
      A_CP_Bu2Dst0hst_D0gamma_(nullptr),
      A_CP_Bu2Dst0hst_D0pi0_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_ADS_Bd2Dsth_(nullptr),
      R_ADS_Bu2D0hst_(nullptr),
      R_ADS_Bu2Dst0hst_D0gamma_(nullptr),
      R_ADS_Bu2Dst0hst_D0pi0_(nullptr) {
  if (Configuration::Get().blindFit() == true) {
    A_CP_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0gamma_Blind", uniqueId_,
                                     Bachelor::pi, -0.003, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_,
                                     Bachelor::pi, 0.025, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0gamma_WN_Blind",
                                     uniqueId_, Bachelor::pi, -0.003, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_WN_Blind", uniqueId_,
                                     Bachelor::pi, 0.025, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("A_CP_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId_, Bachelor::pi))
            .c_str(),
        0.03, *A_CP_Bu2Dst0h_D0gamma_Blind_));
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("A_CP_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Bachelor::pi)).c_str(),
        0.03, *A_CP_Bu2Dst0h_D0pi0_Blind_));
    A_CP_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("A_CP_Bu2Dst0h_D0gamma_WN_" + ComposeName(uniqueId_, Bachelor::pi))
            .c_str(),
        0.03, *A_CP_Bu2Dst0h_D0gamma_WN_Blind_));
    A_CP_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("A_CP_Bu2Dst0h_D0pi0_WN_" + ComposeName(uniqueId_, Bachelor::pi))
            .c_str(),
        0.03, *A_CP_Bu2Dst0h_D0pi0_WN_Blind_));
  } else {
    A_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma", uniqueId_, Bachelor::pi, -0.003, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0", uniqueId_, Bachelor::pi, 0.025, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0gamma_WN", uniqueId_,
                                     Bachelor::pi, -0.003, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0_WN", uniqueId_, Bachelor::pi, 0.025, -1, 1));
  }
  A_CP_Bd2Dsth_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFixed("A_CP_Bd2Dsth", uniqueId_, Bachelor::pi, 0.0,
                                0.02, Systematic::NA, Sign::none));
  // Get number from Donal
  A_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
      "A_CP_Bu2D0hst", uniqueId_, Bachelor::pi, 0, -1, 1));
  // No measured params for B->D*h* modes
  A_CP_Bu2Dst0hst_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "A_CP_Bu2Dst0hst_D0gamma", uniqueId_, Bachelor::pi, 0, -1, 1));
  A_CP_Bu2Dst0hst_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "A_CP_Bu2Dst0hst_D0pi0", uniqueId_, Bachelor::pi, 0, -1, 1));
  if (Configuration::Get().splitByCharge() == true) {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            BachelorChargeVars<Bachelor::pi, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma(),
            BachelorChargeVars<Bachelor::pi, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            BachelorChargeVars<Bachelor::pi, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            BachelorChargeVars<Bachelor::pi, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            BachelorChargeVars<Bachelor::pi, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN(),
            BachelorChargeVars<Bachelor::pi, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            BachelorChargeVars<Bachelor::pi, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN(),
            BachelorChargeVars<Bachelor::pi, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  } else {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            BachelorChargeVars<Bachelor::pi, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            BachelorChargeVars<Bachelor::pi, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            BachelorChargeVars<Bachelor::pi, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::pi>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            BachelorChargeVars<Bachelor::pi, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  }
  // Fix to D BR
  R_ADS_Bd2Dsth_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFixed("R_ADS_Bd2Dsth", uniqueId_, Bachelor::pi, 1.0,
                                0.02, Systematic::NA, Sign::none));
  // Float to allow B->Dππ to fall in this PDF (only in ADS mode)
  R_ADS_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
      "R_ADS_Bu2D0hst", uniqueId_, Bachelor::pi, 1, -5, 5));
  // No measured params for B->D*h* modes: just let float
  R_ADS_Bu2Dst0hst_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "R_ADS_Bu2Dst0hst_D0gamma", uniqueId_, Bachelor::pi, 1, -5, 5));
  R_ADS_Bu2Dst0hst_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "R_ADS_Bu2Dst0hst_D0pi0", uniqueId_, Bachelor::pi, 1, -5, 5));
}

template <>
BachelorVars<Bachelor::k>::BachelorVars(int uniqueId)
    : uniqueId_(uniqueId),
      // -------------------- CP Observables -------------------- //
      A_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_WN_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_WN_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_WN_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_WN_(nullptr),
      A_CP_Bd2Dsth_(nullptr),
      A_CP_Bu2D0hst_(nullptr),
      A_CP_Bu2Dst0hst_D0gamma_(nullptr),
      A_CP_Bu2Dst0hst_D0pi0_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_WN_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_WN_(nullptr),
      R_ADS_Bd2Dsth_(nullptr),
      R_ADS_Bu2D0hst_(nullptr),
      R_ADS_Bu2Dst0hst_D0gamma_(nullptr),
      R_ADS_Bu2Dst0hst_D0pi0_(nullptr) {
  if (Configuration::Get().blindFit() == true) {
    A_CP_Bu2Dst0h_D0gamma_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0gamma_Blind", uniqueId_,
                                     Bachelor::k, 0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_,
                                     Bachelor::k, -0.151, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0gamma_WN_Blind",
                                     uniqueId_, Bachelor::k, 0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_WN_Blind", uniqueId_,
                                     Bachelor::k, -0.151, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("A_CP_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId_, Bachelor::k))
            .c_str(),
        0.03, *A_CP_Bu2Dst0h_D0gamma_Blind_));
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("A_CP_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, Bachelor::k)).c_str(),
        0.03, *A_CP_Bu2Dst0h_D0pi0_Blind_));
    A_CP_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("A_CP_Bu2Dst0h_D0gamma_WN_" + ComposeName(uniqueId_, Bachelor::k))
            .c_str(),
        0.03, *A_CP_Bu2Dst0h_D0gamma_WN_Blind_));
    A_CP_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("A_CP_Bu2Dst0h_D0pi0_WN_" + ComposeName(uniqueId_, Bachelor::k))
            .c_str(),
        0.03, *A_CP_Bu2Dst0h_D0pi0_WN_Blind_));
  } else {
    A_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma", uniqueId_, Bachelor::k, 0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0", uniqueId_, Bachelor::k, -0.151, -1, 1));
    A_CP_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0gamma_WN", uniqueId_, Bachelor::k, 0.276, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Bu2Dst0h_D0pi0_WN", uniqueId_, Bachelor::k, -0.151, -1, 1));
  }
  A_CP_Bd2Dsth_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFixed("A_CP_Bd2Dsth", uniqueId_, Bachelor::k, 0.0,
                                0.02, Systematic::NA, Sign::none));
  // Fixed from HFLAV: A_CP+
  A_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFixed("A_CP_Bu2D0hst", uniqueId_, Bachelor::k, -0.142,
                                0.032, Systematic::NA, Sign::none));
  // No measured params for B->D*h* modes: just initialise same as signal
  A_CP_Bu2Dst0hst_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "A_CP_Bu2Dst0hst_D0gamma", uniqueId_, Bachelor::k, 0.276, -1, 1));
  A_CP_Bu2Dst0hst_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "A_CP_Bu2Dst0hst_D0pi0", uniqueId_, Bachelor::k, -0.151, -1, 1));
  if (Configuration::Get().splitByCharge() == true) {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            BachelorChargeVars<Bachelor::k, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma(),
            BachelorChargeVars<Bachelor::k, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            BachelorChargeVars<Bachelor::k, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            BachelorChargeVars<Bachelor::k, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            BachelorChargeVars<Bachelor::k, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN(),
            BachelorChargeVars<Bachelor::k, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            BachelorChargeVars<Bachelor::k, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN(),
            BachelorChargeVars<Bachelor::k, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  } else {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            BachelorChargeVars<Bachelor::k, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            BachelorChargeVars<Bachelor::k, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_WN_",
            BachelorChargeVars<Bachelor::k, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    R_ADS_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<Bachelor::k>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_WN_",
            BachelorChargeVars<Bachelor::k, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
  }
  R_ADS_Bd2Dsth_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFixed("R_ADS_Bd2Dsth", uniqueId_, Bachelor::k, 1.0,
                                0.02, Systematic::NA, Sign::none));
  // Float to allow B->Dππ to fall in this PDF (only in ADS mode)
  R_ADS_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
      "R_ADS_Bu2D0hst", uniqueId_, Bachelor::k, 1, -5, 5));
  // No measured params for B->D*h* modes: just let float
  R_ADS_Bu2Dst0hst_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "R_ADS_Bu2Dst0hst_D0gamma", uniqueId_, Bachelor::k, 1, -5, 5));
  R_ADS_Bu2Dst0hst_D0pi0_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "R_ADS_Bu2Dst0hst_D0pi0", uniqueId_, Bachelor::k, 1, -5, 5));
}

template <Bachelor bachelor>
BachelorVars<bachelor> &BachelorVars<bachelor>::Get(int uniqueId) {
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

void InstantiateBachelorVars() {
  BachelorVars<Bachelor::pi>::Get(-1);
  BachelorVars<Bachelor::k>::Get(-1);
}
