#include "BachelorVars.h"
#include "GlobalVars.h"
#include "Params.h"

template <Bachelor _bachelor>
BachelorVars<_bachelor>::BachelorVars(int uniqueId)
    : uniqueId_(uniqueId),
      // -------------------- CP Observables -------------------- //
      A_CP_Bu2Dst0h_D0gamma_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_Blind_(nullptr),
      A_CP_Bu2Dst0h_D0gamma_(nullptr),
      A_CP_Bu2Dst0h_D0pi0_(nullptr),
      A_CP_Bu2Dst0h_WN_(nullptr),
      A_CP_Bd2Dsth_(nullptr),
      A_CP_Bu2D0hst_(nullptr),
      A_CP_Bu2Dst0hst_(nullptr),
      A_CP_Lb2Omegach_Lcpi0_(nullptr),
      R_ADS_Bu2Dst0h_D0gamma_(nullptr),
      R_ADS_Bu2Dst0h_D0pi0_(nullptr),
      R_ADS_Bu2Dst0h_WN_(nullptr),
      R_ADS_Bd2Dsth_(nullptr),
      R_ADS_Bu2D0hst_(nullptr),
      R_ADS_Bu2Dst0hst_(nullptr) {
  double k_A_CP_Bu2Dst0h_D0gamma_, k_A_CP_Bu2Dst0h_D0pi0_;
  if (_bachelor == Bachelor::pi) {
    k_A_CP_Bu2Dst0h_D0gamma_ = -0.003;
    k_A_CP_Bu2Dst0h_D0pi0_ = 0.025;
  } else {
    k_A_CP_Bu2Dst0h_D0gamma_ = 0.276;
    k_A_CP_Bu2Dst0h_D0pi0_ = -0.151;
  }
  if (Configuration::Get().blindFit() == true) {
    if (Configuration::Get().neutral() == Neutral::gamma) {
      A_CP_Bu2Dst0h_D0gamma_Blind_ =
          std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
              "A_CP_Bu2Dst0h_D0gamma_Blind", uniqueId_, _bachelor,
              k_A_CP_Bu2Dst0h_D0gamma_, -1, 1));
      A_CP_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
          ("A_CP_Bu2Dst0h_D0gamma_" + ComposeName(uniqueId_, _bachelor))
              .c_str(),
          0.03, *A_CP_Bu2Dst0h_D0gamma_Blind_));
    }
    A_CP_Bu2Dst0h_D0pi0_Blind_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0_Blind", uniqueId_,
                                     _bachelor, k_A_CP_Bu2Dst0h_D0pi0_, -1, 1));
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooUnblindUniform>(MakeBlind(
        ("A_CP_Bu2Dst0h_D0pi0_" + ComposeName(uniqueId_, _bachelor)).c_str(),
        0.03, *A_CP_Bu2Dst0h_D0pi0_Blind_));
  } else {
    if (Configuration::Get().neutral() == Neutral::gamma) {
      A_CP_Bu2Dst0h_D0gamma_ =
          std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
              "A_CP_Bu2Dst0h_D0gamma", uniqueId_, _bachelor,
              k_A_CP_Bu2Dst0h_D0gamma_, -1, 1));
    }
    A_CP_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_CP_Bu2Dst0h_D0pi0", uniqueId_,
                                     _bachelor, k_A_CP_Bu2Dst0h_D0pi0_, -1, 1));
  }
  if (Configuration::Get().neutral() == Neutral::pi0) {
    Systematic systematic;
    if (_bachelor == Bachelor::pi) {
      systematic = Systematic::A_CP_pi_Bu2Dst0h_D0gamma;
    } else {
      systematic = Systematic::A_CP_K_Bu2Dst0h_D0gamma;
    }
    A_CP_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "A_CP_Bu2Dst0h_D0gamma", uniqueId_, _bachelor,
            ReadGammaObs(
                ("A_CP_Bu2Dst0h_D0gamma_" + EnumToString(_bachelor)).c_str(),
                ReturnType::val),
            ReadGammaObs(
                ("A_CP_Bu2Dst0h_D0gamma_" + EnumToString(_bachelor)).c_str(),
                ReturnType::stdL),
            ReadGammaObs(
                ("A_CP_Bu2Dst0h_D0gamma_" + EnumToString(_bachelor)).c_str(),
                ReturnType::stdH),
            systematic, Sign::same));
  }
  A_CP_Bu2Dst0h_WN_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
      "A_CP_Bu2Dst0h_WN", uniqueId_, _bachelor, 0, -1, 1));

  if (Configuration::Get().splitByCharge() == true) {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            BachelorChargeVars<_bachelor, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma(),
            BachelorChargeVars<_bachelor, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            BachelorChargeVars<_bachelor, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            BachelorChargeVars<_bachelor, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
            uniqueId, "R_ADS_Bu2Dst0h_WN_",
            BachelorChargeVars<_bachelor, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_WN(),
            BachelorChargeVars<_bachelor, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_WN()));
    if (Configuration::Get().neutral() == Neutral::gamma) {
      if (_bachelor == Bachelor::pi) {
        // Float to allow B->Dππ to fall in this PDF (only in ADS mode)
        R_ADS_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
            uniqueId, "R_ADS_Bu2D0hst_",
            BachelorChargeVars<_bachelor, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2D0hst(),
            BachelorChargeVars<_bachelor, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2D0hst()));
      R_ADS_Bu2Dst0hst_ = std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
          uniqueId, "R_ADS_Bu2Dst0hst_",
          BachelorChargeVars<_bachelor, Charge::minus>::Get(uniqueId)
              .R_piK_Bu2Dst0hst(),
          BachelorChargeVars<_bachelor, Charge::plus>::Get(uniqueId)
              .R_piK_Bu2Dst0hst()));
      }
    }
  } else {
    R_ADS_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
            uniqueId, "R_ADS_Bu2Dst0h_D0gamma_",
            BachelorChargeVars<_bachelor, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    R_ADS_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
            uniqueId, "R_ADS_Bu2Dst0h_D0pi0_",
            BachelorChargeVars<_bachelor, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    R_ADS_Bu2Dst0h_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
            uniqueId, "R_ADS_Bu2Dst0h_WN_",
            BachelorChargeVars<_bachelor, Charge::total>::Get(uniqueId)
                .R_piK_Bu2Dst0h_WN()));
    if (Configuration::Get().neutral() == Neutral::gamma) {
      if (_bachelor == Bachelor::pi) {
        // Float to allow B->Dππ to fall in this PDF (only in ADS mode)
        R_ADS_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
            uniqueId, "R_ADS_Bu2D0hst_",
            BachelorChargeVars<_bachelor, Charge::total>::Get(uniqueId)
                .R_piK_Bu2D0hst()));
      R_ADS_Bu2Dst0hst_ = std::shared_ptr<RooFormulaVar>(Make_R_ADS<_bachelor>(
          uniqueId, "R_ADS_Bu2Dst0hst_",
          BachelorChargeVars<_bachelor, Charge::total>::Get(uniqueId)
              .R_piK_Bu2Dst0hst()));
      }
    }
  }
  if (_bachelor == Bachelor::k) {
    // HFLAV: R_ADS+, BF average of B+ and B0
    // 50% extra uncertainty for non-K* contributions
    R_ADS_Bu2D0hst_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFixed("R_ADS_Bu2D0hst", uniqueId_, _bachelor,
                                  0.016, 0.012, Systematic::R_ADS_Bu2D0hst, Sign::same));
  }
  R_ADS_Bd2Dsth_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      "R_ADS_Bd2Dsth", uniqueId_, _bachelor,
      GlobalVars::Get(uniqueId_).kBF_D02pik().getVal() /
          GlobalVars::Get(uniqueId_).kBF_D02kpi().getVal(),
      0, Systematic::NA, Sign::none));
  // R_ADS_Bu2Dst0h_WN_ =
  // std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
  //     "R_ADS_Bu2Dst0h_WN", uniqueId_, _bachelor,
  //     GlobalVars::Get(uniqueId_).kBF_D02pik().getVal() /
  //         GlobalVars::Get(uniqueId_).kBF_D02kpi().getVal(),
  //     -1, 1));
  if (Configuration::Get().neutral() == Neutral::pi0) {
    double start = GlobalVars::Get(uniqueId_).kBF_D02pik().getVal() /
                   GlobalVars::Get(uniqueId_).kBF_D02kpi().getVal();
    if (_bachelor == Bachelor::pi) {
      R_ADS_Bu2D0hst_ =
          std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
              "R_ADS_Bu2D0hst", uniqueId_, _bachelor, start, -5, 5));
      R_ADS_Bu2Dst0hst_ =
          std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
              "R_ADS_Bu2Dst0hst", uniqueId_, _bachelor, start, 0, 5));
    }
    // if (_bachelor == Bachelor::k) {
    //   start = 0.5;
    // }
    // R_ADS_Bu2Dst0hst_ =
    //     std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
    //         "R_ADS_Bu2Dst0hst", uniqueId_, _bachelor, start, 0, 5));
  }
  if (_bachelor == Bachelor::k) {
    R_ADS_Bu2Dst0hst_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFixed("R_ADS_Bu2Dst0hst", uniqueId_, _bachelor,
                                  0.015, 0.010, Systematic::R_ADS_Bu2Dst0hst, Sign::same));
  }

  A_CP_Bd2Dsth_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFixed("A_CP_Bd2Dsth", uniqueId_, _bachelor, 0.0, 0,
                                Systematic::NA, Sign::none));
  if (Configuration::Get().neutral() == Neutral::pi0) {
    // if (_bachelor == Bachelor::pi) {
      A_CP_Bu2Dst0hst_ =
          std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
              "A_CP_Bu2Dst0hst", uniqueId_, _bachelor, 0, -1, 1));
      // Could fix this
      // } else {
      //   A_CP_Bu2Dst0hst_ = std::shared_ptr<RooRealVar>(
      //       Params::Get().CreateFixed("A_CP_Bu2Dst0hst", uniqueId_,
      //       _bachelor,
      //                                 0.0, 0.2, Systematic::A_CP_pi_Bu2Dst0hst,
      //                                 Sign::none));
      // }
      // if (_bachelor == Bachelor::pi) {
      //   A_CP_Lb2Omegach_Lcpi0_ =
      //       std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      //           "A_CP_Lb2Omegach_Lcpi0", uniqueId_, _bachelor, 0.0, 0.02,
      //           Systematic::A_CP_pi_Lb2Omegach_Lcpi0, Sign::none));
      // } else {
      //   A_CP_Lb2Omegach_Lcpi0_ =
      //       std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
      //           "A_CP_Lb2Omegach_Lcpi0", uniqueId_, _bachelor, 0.0, 0.2,
      //           Systematic::A_CP_K_Lb2Omegach_Lcpi0, Sign::none));
      // }
  } else {
    A_CP_Bu2Dst0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "A_CP_Bu2Dst0hst", uniqueId_, _bachelor, 0, -2, 2));
  }
  if (Configuration::Get().neutral() == Neutral::gamma && _bachelor == Bachelor::k) {
    A_CP_Lb2Omegach_Lcpi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "A_CP_Lb2Omegach_Lcpi0", uniqueId_, _bachelor, 0.0, 0.2,
            // Systematic::A_CP_K_Lb2Omegach_Lcpi0, Sign::none));
            Systematic::NA, Sign::none));
  } else {
    A_CP_Lb2Omegach_Lcpi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "A_CP_Lb2Omegach_Lcpi0", uniqueId_, _bachelor, 0, -1, 1));
  }
  // if (_bachelor == Bachelor::pi) {
  //   A_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
  //       "A_CP_Bu2D0hst", uniqueId_, _bachelor, 0.0, 0.02,
  //       Systematic::A_CP_pi_Bu2D0hst, Sign::none));
  // } else {
  //   // HFLAV: A_CP+, BF average of B+ and B0
  //   A_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
  //       "A_CP_Bu2D0hst", uniqueId_, _bachelor, 0.06, 0.09,
  //       // "A_CP_Bu2D0hst", uniqueId_, _bachelor, 0.06, 0.06,
  //       Systematic::A_CP_K_Bu2D0hst, Sign::none));
  // }
  if (Configuration::Get().neutral() == Neutral::gamma &&
      _bachelor == Bachelor::k) {
    A_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "A_CP_Bu2D0hst", uniqueId_, _bachelor, 0.06, 0.09,
        // "A_CP_Bu2D0hst", uniqueId_, _bachelor, 0.06, 0.06,
        Systematic::A_CP_K_Bu2D0hst, Sign::none));
  } else {
    A_CP_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "A_CP_Bu2D0hst", uniqueId_, _bachelor, 0, -1, 1));
  }
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
