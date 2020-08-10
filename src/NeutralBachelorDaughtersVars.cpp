#include "NeutralBachelorDaughtersVars.h"

// Now we just need to define the constructors separately so the values are
// different

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
NeutralBachelorDaughtersVars<neutral, bachelor, daughters> &
NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(int uniqueId) {
  static std::map<int, std::shared_ptr<This_t>> singletons;
  // An iterator to a map is a std::pair<key, value>, so we need to call
  // i->second to get the value
  auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
  if (it == singletons.end()) {
    // If it doesn't, create it as a new unique_ptr by calling emplace, which
    // will forward the pointer to the constructor of std::unique_ptr
    it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId)).first;
  }
  return *it->second;
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
RooFormulaVar *Make_N_GlobalFrac(int uniqueId, const char *nameStr,
                                 RooAbsReal &N_sig, RooAbsReal &globalFrac) {
  return new RooFormulaVar(
      (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters)).c_str(),
      "@0*@1", RooArgList(N_sig, globalFrac));
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
RooFormulaVar *Make_N_Frac(int uniqueId, const char *nameStr,
                           RooAbsReal &N_tot_rel, RooAbsReal &kBF,
                           RooAbsReal &kBF_rel, RooAbsReal &mcEff,
                           RooAbsReal &mcEff_rel) {
  return new RooFormulaVar(
      (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters)).c_str(),
      "@0*(@1/@2)*(@3/@4)",
      RooArgList(N_tot_rel, kBF, kBF_rel, mcEff, mcEff_rel));
}

template <Neutral neutral>
std::shared_ptr<RooRealVar> Make_N_Bu2Dst0pi_D0gamma_D02kpi(int uniqueId) {
  switch (neutral) {
    case Neutral::gamma:
      return Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0gamma", uniqueId, Neutral::gamma, Bachelor::pi,
          Daughters::kpi, 70000, -1000000, 1000000);
      break;
    case Neutral::pi0:
      return Params::Get().CreateFixed(
          "N_tot_Bu2Dst0h_D0gamma", uniqueId, Neutral::pi0, Bachelor::pi,
          Daughters::kpi, 0., 0., Systematic::NA, Sign::none);
      break;
  }
}

// double Return_N_Initial(RooRealVar

template <Neutral neutral>
std::shared_ptr<RooRealVar> Make_N_Bu2Dst0pi_D0pi0_D02kpi(int uniqueId,
                                                          RooAbsReal &N_gamma) {
  switch (neutral) {
    case Neutral::pi0:
      return Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0pi0", uniqueId, Neutral::pi0, Bachelor::pi,
          Daughters::kpi, 22000, -1000000, 1000000);
      break;
    case Neutral::gamma:
      return Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0pi0", uniqueId, Neutral::gamma, Bachelor::pi,
          Daughters::kpi,
          N_gamma.getVal() *
              (GlobalVars::Get(uniqueId).kBF_Dst02D0pi0().getVal() /
               GlobalVars::Get(uniqueId).kBF_Dst02D0gamma().getVal()) *
              (NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                   .mcEff_Bu2Dst0h_D0pi0()
                   .getVal() /
               NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                   .mcEff_Bu2Dst0h_D0gamma()
                   .getVal()),
          -1000000, 1000000);
      break;
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::kpi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi,
          Daughters::kpi, 0, 0.0005, Systematic::A_FAV_Gamma, Sign::none)),
      A_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
          0, 0.0005, Systematic::A_FAV_Pi0, Sign::none)),
      A_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_D0gamma_WN", uniqueId, _neutral, Bachelor::pi,
          Daughters::kpi, 0, 0.0005, Systematic::A_FAV_Gamma, Sign::none)),
      A_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_D0pi0_WN", uniqueId, _neutral, Bachelor::pi,
          Daughters::kpi, 0, 0.0005, Systematic::A_FAV_Pi0, Sign::none)),
      A_Bd2Dsth_(Params::Get().CreateFixed("A_Bd2Dsth", uniqueId, _neutral,
                                           Bachelor::pi, Daughters::kpi, 0, 0.0,
                                           Systematic::NA, Sign::none)),
      A_Bu2D0hst_(Params::Get().CreateFixed("A_Bu2D0hst", uniqueId, _neutral,
                                            Bachelor::pi, Daughters::kpi, 0,
                                            0.02, Systematic::NA, Sign::none)),
      A_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "A_Bu2Dst0hst_D0pi0", uniqueId, _neutral, Bachelor::pi,
          Daughters::kpi, 0, 0.02, Systematic::NA, Sign::none)),
      A_Bu2Dst0hst_D0gamma_(Params::Get().CreateFixed(
          "A_Bu2Dst0hst_D0gamma", uniqueId, _neutral, Bachelor::pi,
          Daughters::kpi, 0, 0.02, Systematic::NA, Sign::none)),
      // A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
      //                                        Bachelor::pi, Daughters::kpi, 0,
      //                                        -5, 5)),
      A_MisRec_(Params::Get().CreateFixed("A_MisRec", uniqueId, _neutral,
                                          Bachelor::pi, Daughters::kpi, 0, 0.02,
                                          Systematic::NA, Sign::none)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::kpi, 0,
                                             -5, 5)),
      // A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId,
      // _neutral,
      //                                         Bachelor::pi, Daughters::kpi,
      //                                         0, -5, 5)),
      A_PartRec_(Params::Get().CreateFixed("A_PartRec", uniqueId, _neutral,
                                           Bachelor::pi, Daughters::kpi, 0,
                                           0.02, Systematic::NA, Sign::none)),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_)),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_D0gamma_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_WN_)),
      a_Bu2Dst0h_D0pi0_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_WN_)),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(MakeLittleAsym(
          ("a_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2D0hst_)),
      a_Bu2Dst0hst_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0hst_D0pi0_)),
      a_Bu2Dst0hst_D0gamma_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0hst_D0gamma_)),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(
          Make_N_Bu2Dst0pi_D0gamma_D02kpi<_neutral>(uniqueId)),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_Bu2Dst0pi_D0pi0_D02kpi<_neutral>(
          uniqueId, *N_tot_Bu2Dst0h_D0gamma_)),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_GlobalFrac<_neutral, Bachelor::pi,
                                                 Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bd2Dsth_(nullptr),
      N_tot_Bu2D0hst_(nullptr),
      N_tot_Bu2Dst0hst_D0pi0_(nullptr),
      N_tot_Bu2Dst0hst_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Params::Get().CreateFloating(
          "N_tot_MisRec", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2D0h_(Params::Get().CreateFloating(
          "N_tot_Bu2D0h", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_PartRec_(Params::Get().CreateFloating(
          "N_tot_PartRec", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          0, 1000000)),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bd2Dsth()));
    N_tot_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bu2D0hst_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2D0hst()));
    N_tot_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0hst_D0pi0_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0hst_D0pi0()));
    N_tot_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooFormulaVar>(
        Make_N_Frac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0hst_D0gamma_", *N_tot_Bu2Dst0hst_D0pi0_,
            GlobalVars::Get(uniqueId).kBF_Dst02D0gamma(),
            GlobalVars::Get(uniqueId).kBF_Dst02D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0hst_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0hst_D0pi0()));
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "N_tot_Bu2Dst0h_D0gamma_WN", uniqueId, _neutral, Bachelor::pi,
            Daughters::kpi,
            N_tot_Bu2Dst0h_D0pi0_->getVal() *
                NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                    .mcEff_Bu2Dst0h_D0gamma_WN()
                    .getVal() /
                NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                    .mcEff_Bu2Dst0h_D0pi0()
                    .getVal(),
            -1000000, 1000000));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bd2Dsth()));
    N_tot_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bu2D0hst_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2D0hst()));
    N_tot_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0hst_D0pi0_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0hst_D0pi0()));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      A_Bu2Dst0h_D0gamma_WN_(nullptr),
      A_Bu2Dst0h_D0pi0_WN_(nullptr),
      A_Bd2Dsth_(Params::Get().CreateFixed("A_Bd2Dsth", uniqueId, _neutral,
                                           Bachelor::pi, Daughters::pik, 0, 0.0,
                                           Systematic::NA, Sign::none)),
      // FIX THIS when we know what it is (A_ADS in Dπ)
      A_Bu2D0hst_(Params::Get().CreateFloating("A_Bu2D0hst", uniqueId, _neutral,
                                               Bachelor::pi, Daughters::pik, 0,
                                               -5, 5)),
      // A_Bu2D0hst_(Params::Get().CreateFixed("A_Bu2D0hst", uniqueId, _neutral,
      //                                      Bachelor::pi, Daughters::pik, 0,
      //                                      0.0, Systematic::NA, Sign::none)),
      A_Bu2Dst0hst_D0pi0_(
          Params::Get().CreateFloating("A_Bu2Dst0hst_D0pi0", uniqueId, _neutral,
                                       Bachelor::pi, Daughters::pik, 0, -5, 5)),
      A_Bu2Dst0hst_D0gamma_(Params::Get().CreateFloating(
          "A_Bu2Dst0hst_D0gamma", uniqueId, _neutral, Bachelor::pi,
          Daughters::pik, 0, -5, 5)),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::pik, 0,
                                             -5, 5)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::pik, 0,
                                             -5, 5)),
      A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                              Bachelor::pi, Daughters::pik, 0,
                                              -5, 5)),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(nullptr),
      a_Bu2Dst0h_D0gamma_WN_(nullptr),
      a_Bu2Dst0h_D0pi0_WN_(nullptr),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(MakeLittleAsym(
          ("a_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_Bu2D0hst_)),
      a_Bu2Dst0hst_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_Bu2Dst0hst_D0pi0_)),
      a_Bu2Dst0hst_D0gamma_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_Bu2Dst0hst_D0gamma_)),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .R_ADS_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      // N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_tot_pik<_neutral, Bachelor::pi>(
      //     uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_",
      //     NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
      //                                  Daughters::kpi>::Get(uniqueId)
      //         .N_tot_Bu2Dst0h_D0pi0_WN(),
      //     NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
      //         .R_ADS_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_GlobalFrac<_neutral, Bachelor::pi,
                                                 Daughters::pik>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bd2Dsth_(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .R_ADS_Bd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .R_ADS_Bu2D0hst())),
      N_tot_Bu2Dst0hst_D0pi0_(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bu2Dst0hst_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0hst_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .R_ADS_Bu2Dst0hst_D0pi0())),
      N_tot_Bu2Dst0hst_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(
          Make_N_tot_FAVasSUP<_neutral, Bachelor::pi>(
              uniqueId, "N_tot_Bu2Dst0h_D0gamma_FAVasSUP_",
              NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                           Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma())),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(
          Make_N_tot_FAVasSUP<_neutral, Bachelor::pi>(
              uniqueId, "N_tot_Bu2Dst0h_D0pi0_FAVasSUP_",
              NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                           Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0pi0())),
      N_tot_MisRec_(Params::Get().CreateFloating(
          "N_tot_MisRec", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2D0h_(Params::Get().CreateFloating(
          "N_tot_Bu2D0h", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_PartRec_(Params::Get().CreateFloating(
          "N_tot_PartRec", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          0, 1000000)),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().splitByCharge() == true) {
    A_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral,
                                                                  Bachelor::pi>(
        uniqueId, "A_ADS_Bu2Dst0h_D0pi0_",
        NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::minus>::Get(
            uniqueId)
            .R_piK_Bu2Dst0h_D0pi0(),
        NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::plus>::Get(
            uniqueId)
            .R_piK_Bu2Dst0h_D0pi0()));
    A_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<
        RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::pi>(
        uniqueId, "A_ADS_Bu2Dst0h_D0gamma_WN_",
        NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::minus>::Get(
            uniqueId)
            .R_piK_Bu2Dst0h_D0gamma_WN(),
        NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::plus>::Get(
            uniqueId)
            .R_piK_Bu2Dst0h_D0gamma_WN()));
    A_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<
        RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::pi>(
        uniqueId, "A_ADS_Bu2Dst0h_D0pi0_WN_",
        NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::minus>::Get(
            uniqueId)
            .R_piK_Bu2Dst0h_D0pi0_WN(),
        NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::plus>::Get(
            uniqueId)
            .R_piK_Bu2Dst0h_D0pi0_WN()));
    a_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0pi0_));
    a_Bu2Dst0h_D0gamma_WN_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_WN_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_WN_));
    a_Bu2Dst0h_D0pi0_WN_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0pi0_WN_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0pi0_WN_));
    if (_neutral == Neutral::gamma) {
      A_Bu2Dst0h_D0gamma_ = std::shared_ptr<
          RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::pi>(
          uniqueId, "A_ADS_Bu2Dst0h_D0gamma_",
          NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::minus>::Get(
              uniqueId)
              .R_piK_Bu2Dst0h_D0gamma(),
          NeutralBachelorChargeVars<_neutral, Bachelor::pi, Charge::plus>::Get(
              uniqueId)
              .R_piK_Bu2Dst0h_D0gamma()));
      a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_));
    }
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::pi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .R_ADS_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::pik>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bu2Dst0hst_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::pi>(
            uniqueId, "N_tot_Bu2Dst0hst_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0hst_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .R_ADS_Bu2Dst0hst_D0gamma()));
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::pi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .R_ADS_Bu2Dst0h_D0gamma_WN()));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0())),
      A_Bu2Dst0h_D0gamma_WN_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0gamma_WN_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0gamma_WN())),
      A_Bu2Dst0h_D0pi0_WN_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0pi0_WN_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0_WN())),
      A_Bd2Dsth_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bd2Dsth_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bd2Dsth())),
      A_Bu2D0hst_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2D0hst_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2D0hst())),
      A_Bu2Dst0hst_D0pi0_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2Dst0hst_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2Dst0hst_D0pi0())),
      A_Bu2Dst0hst_D0gamma_(nullptr),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::kk, 0, -5,
                                             5)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::pi, Daughters::kk, 0, -5,
                                             5)),
      A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                              Bachelor::pi, Daughters::kk, 0,
                                              -5, 5)),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_D0gamma_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_WN_)),
      a_Bu2Dst0h_D0pi0_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_WN_)),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(MakeLittleAsym(
          ("a_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2D0hst_)),
      a_Bu2Dst0hst_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0hst_D0pi0_)),
      a_Bu2Dst0hst_D0gamma_(nullptr),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::pi,
          Daughters::kk,
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0pi0()
                  .getVal() *
              GlobalVars::Get(uniqueId).kBF_D02kk().getVal() /
              GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_GlobalFrac<_neutral, Bachelor::pi,
                                                 Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bd2Dsth_(nullptr),
      N_tot_Bu2D0hst_(nullptr),
      N_tot_Bu2Dst0hst_D0pi0_(nullptr),
      N_tot_Bu2Dst0hst_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Params::Get().CreateFloating(
          "N_tot_MisRec", uniqueId, _neutral, Bachelor::pi, Daughters::kk,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2D0h_(Params::Get().CreateFloating(
          "N_tot_Bu2D0h", uniqueId, _neutral, Bachelor::pi, Daughters::kk,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_PartRec_(Params::Get().CreateFloating(
          "N_tot_PartRec", uniqueId, _neutral, Bachelor::pi, Daughters::kk,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(uniqueId)
                  .kBR()
                  .getVal(),
          0, 1000000)),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  N_tot_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi,
          Daughters::kk,
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma()
                  .getVal() *
              GlobalVars::Get(uniqueId).kBF_D02kk().getVal() /
              GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
          -1000000, 1000000));
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bd2Dsth()));
    N_tot_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bu2D0hst_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2D0hst()));
    N_tot_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0hst_D0pi0_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0hst_D0pi0()));
    N_tot_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooFormulaVar>(
        Make_N_Frac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0hst_D0gamma_", *N_tot_Bu2Dst0hst_D0pi0_,
            GlobalVars::Get(uniqueId).kBF_Dst02D0gamma(),
            GlobalVars::Get(uniqueId).kBF_Dst02D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0hst_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0hst_D0pi0()));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "A_Bu2Dst0h_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .A_CP_Bu2Dst0h_D0gamma()));
    A_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "A_Bu2Dst0hst_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .A_CP_Bu2Dst0hst_D0gamma()));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    a_Bu2Dst0hst_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0hst_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
            .c_str(),
        *A_Bu2Dst0hst_D0gamma_));
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "N_tot_Bu2Dst0h_D0gamma_WN", uniqueId, _neutral, Bachelor::pi,
            Daughters::kk,
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                    .N_tot_Bu2Dst0h_D0gamma_WN()
                    .getVal() *
                GlobalVars::Get(uniqueId).kBF_D02kk().getVal() /
                GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
            -1000000, 1000000));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bd2Dsth()));
    N_tot_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bu2D0hst_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2D0hst()));
    N_tot_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0hst_D0pi0_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0hst_D0pi0()));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0())),
      A_Bu2Dst0h_D0gamma_WN_(
          Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
              uniqueId, "A_Bu2Dst0h_D0gamma_WN_",
              NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .A_CP_Bu2Dst0h_D0gamma_WN())),
      A_Bu2Dst0h_D0pi0_WN_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0pi0_WN_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0_WN())),
      A_Bd2Dsth_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bd2Dsth_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bd2Dsth())),
      A_Bu2D0hst_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2D0hst_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2D0hst())),
      A_Bu2Dst0hst_D0pi0_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0hst_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .A_CP_Bu2Dst0hst_D0pi0())),
      A_Bu2Dst0hst_D0gamma_(nullptr),
      A_MisRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                             Daughters::kk>::Get(uniqueId)
                    .A_MisRec_GetPointer()),
      A_Bu2D0h_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                             Daughters::kk>::Get(uniqueId)
                    .A_Bu2D0h_GetPointer()),
      A_PartRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                              Daughters::kk>::Get(uniqueId)
                     .A_PartRec_GetPointer()),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_D0gamma_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_WN_)),
      a_Bu2Dst0h_D0pi0_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_WN_)),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(MakeLittleAsym(
          ("a_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2D0hst_)),
      a_Bu2Dst0hst_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0hst_D0pi0_)),
      a_Bu2Dst0hst_D0gamma_(nullptr),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::pi,
          Daughters::pipi,
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0pi0()
                  .getVal() *
              GlobalVars::Get(uniqueId).kBF_D02pipi().getVal() /
              GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_GlobalFrac<_neutral, Bachelor::pi,
                                                 Daughters::pipi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bd2Dsth_(nullptr),
      N_tot_Bu2D0hst_(nullptr),
      N_tot_Bu2Dst0hst_D0pi0_(nullptr),
      N_tot_Bu2Dst0hst_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Params::Get().CreateFloating(
          "N_tot_MisRec", uniqueId, _neutral, Bachelor::pi, Daughters::pipi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVMisRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_Bu2D0h_(Params::Get().CreateFloating(
          "N_tot_Bu2D0h", uniqueId, _neutral, Bachelor::pi, Daughters::pipi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVBu2D0h() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          -1000000, 1000000)),
      N_tot_PartRec_(Params::Get().CreateFloating(
          "N_tot_PartRec", uniqueId, _neutral, Bachelor::pi, Daughters::pipi,
          NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
              BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(
                  uniqueId)
                  .kBR()
                  .getVal(),
          0, 1000000)),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  N_tot_Bu2Dst0h_D0gamma_ =
      std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi,
          Daughters::pipi,
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma()
                  .getVal() *
              GlobalVars::Get(uniqueId).kBF_D02pipi().getVal() /
              GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
          -1000000, 1000000));
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bd2Dsth()));
    N_tot_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bu2D0hst_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2D0hst()));
    N_tot_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0hst_D0pi0_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0hst_D0pi0()));
    N_tot_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooFormulaVar>(
        Make_N_Frac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0hst_D0gamma_", *N_tot_Bu2Dst0hst_D0pi0_,
            GlobalVars::Get(uniqueId).kBF_Dst02D0gamma(),
            GlobalVars::Get(uniqueId).kBF_Dst02D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0hst_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0hst_D0pi0()));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "A_Bu2Dst0h_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .A_CP_Bu2Dst0h_D0gamma()));
    A_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "A_Bu2Dst0hst_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .A_CP_Bu2Dst0hst_D0gamma()));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    a_Bu2Dst0hst_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0hst_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
            .c_str(),
        *A_Bu2Dst0hst_D0gamma_));
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "N_tot_Bu2Dst0h_D0gamma_WN", uniqueId, _neutral, Bachelor::pi,
            Daughters::pipi,
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                    .N_tot_Bu2Dst0h_D0gamma_WN()
                    .getVal() *
                GlobalVars::Get(uniqueId).kBF_D02pipi().getVal() /
                GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
            -1000000, 1000000));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bd2Dsth()));
    N_tot_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bu2D0hst_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2D0hst()));
    N_tot_Bu2Dst0hst_D0pi0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0hst_D0pi0_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0hst_D0pi0()));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::kpi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(
          Params::Get().CreateFloating("A_Bu2Dst0h_D0pi0", uniqueId,
          _neutral,
                                       Bachelor::k, Daughters::kpi, 0, -1,
                                       1)),
      // A_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
      //     "A_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::k, Daughters::kpi,
      //     0., 0., Systematic::NA, Sign::none)),
      A_Bu2Dst0h_D0gamma_WN_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_D0gamma_WN", uniqueId, _neutral, Bachelor::k,
          Daughters::kpi, 0.0, 0.02, Systematic::NA, Sign::none)),
      A_Bu2Dst0h_D0pi0_WN_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_D0pi0_WN", uniqueId, _neutral, Bachelor::k,
          Daughters::kpi, 0.0, 0.02, Systematic::NA, Sign::none)),
      A_Bd2Dsth_(Params::Get().CreateFixed("A_Bd2Dsth", uniqueId, _neutral,
                                           Bachelor::k, Daughters::kpi, 0.0,
                                           0.0, Systematic::NA, Sign::none)),
      A_Bu2D0hst_(Params::Get().CreateFixed("A_Bu2D0hst", uniqueId, _neutral,
                                            Bachelor::k, Daughters::kpi, 0.0,
                                            0.02, Systematic::NA, Sign::none)),
      A_Bu2Dst0hst_D0pi0_(Params::Get().CreateFixed(
          "A_Bu2Dst0hst_D0pi0", uniqueId, _neutral, Bachelor::k, Daughters::kpi,
          0.0, 0.02, Systematic::NA, Sign::none)),
      A_Bu2Dst0hst_D0gamma_(nullptr),
      A_MisRec_(Params::Get().CreateFixed("A_MisRec", uniqueId, _neutral,
                                          Bachelor::k, Daughters::kpi, 0, 0.02,
                                          Systematic::NA, Sign::none)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::k, Daughters::kpi, 0, -1,
                                             1)),
      A_PartRec_(Params::Get().CreateFixed("A_PartRec", uniqueId, _neutral,
                                           Bachelor::k, Daughters::kpi, 0, 0.02,
                                           Systematic::NA, Sign::none)),
      A_Bs2Dst0Kpi_(nullptr),
      A_Bs2D0Kpi_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_D0gamma_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_WN_)),
      a_Bu2Dst0h_D0pi0_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_WN_)),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(MakeLittleAsym(
          ("a_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2D0hst_)),
      a_Bu2Dst0hst_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0hst_D0pi0_)),
      a_Bu2Dst0hst_D0gamma_(nullptr),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(nullptr),
      a_Bs2D0Kpi_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      // N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
      //     uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_",
      //     NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
      //                                  Daughters::kpi>::Get(uniqueId)
      //         .N_tot_Bu2Dst0h_D0pi0_WN(),
      //     NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
      //         .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN(),
      //     NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
      //         .mcEff_Bu2Dst0h_D0pi0_WN(),
      //     NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
      //         .mcEff_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_GlobalFrac<_neutral, Bachelor::k,
                                                 Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bd2Dsth_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bd2Dsth(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bd2Dsth(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0hst(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0hst(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0hst())),
      N_tot_Bu2Dst0hst_D0pi0_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0hst_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0hst_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0hst_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0hst_D0pi0())),
      N_tot_Bu2Dst0hst_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_MisRec_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_MisRec_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_MisRec(),
          NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_MisRec(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2D0h_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2D0h_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2D0h(),
          NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0h())),
      N_tot_PartRec_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::k, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0hst_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0hst_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0hst_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0hst_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0hst_D0gamma()));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_Bu2Dst0h_D0gamma", uniqueId, _neutral,
                                     Bachelor::k, Daughters::kpi, 0, -1, 1));
    // A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
    //     "A_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::k, Daughters::kpi,
    //     0., 0., Systematic::NA, Sign::none));
    A_Bu2Dst0hst_D0gamma_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "A_Bu2Dst0hst_D0gamma", uniqueId, _neutral, Bachelor::k,
            Daughters::kpi, 0.0, 0.02, Systematic::NA, Sign::none));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    a_Bu2Dst0hst_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0hst_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
            .c_str(),
        *A_Bu2Dst0hst_D0gamma_));
    // Add systematic
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_PartRec", uniqueId, _neutral, Bachelor::k, Daughters::kpi,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::kpi>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0gamma_WN()));
    N_tot_PartRec_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
            uniqueId, "N_tot_PartRec_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_PartRec(),
            NeutralDaughtersVars<_neutral, Daughters::kpi>::Get(uniqueId)
                .R_Dst0KDst0pi_PartRec(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0()));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      A_Bu2Dst0h_D0gamma_WN_(nullptr),
      A_Bu2Dst0h_D0pi0_WN_(nullptr),
      A_Bd2Dsth_(Params::Get().CreateFixed("A_Bd2Dsth", uniqueId, _neutral,
                                           Bachelor::k, Daughters::pik, 0.0,
                                           0.0, Systematic::NA, Sign::none)),
      A_Bu2D0hst_(Params::Get().CreateFixed("A_Bu2D0hst", uniqueId, _neutral,
                                            Bachelor::k, Daughters::pik, -0.75,
                                            0.16, Systematic::NA, Sign::none)),
      A_Bu2Dst0hst_D0pi0_(
          Params::Get().CreateFloating("A_Bu2Dst0hst_D0pi0", uniqueId, _neutral,
                                       Bachelor::k, Daughters::pik, 0, -1, 1)),
      A_Bu2Dst0hst_D0gamma_(nullptr),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::k, Daughters::pik, 0, -1,
                                             1)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::k, Daughters::pik, 0, -1,
                                             1)),
      A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                              Bachelor::k, Daughters::pik, 0,
                                              -1, 1)),
      // Add systematic?
      A_Bs2Dst0Kpi_(Params::Get().CreateFixed(
          "A_Bs2Dst0Kpi", uniqueId, _neutral, Bachelor::k, Daughters::pik, 0, 0,
          Systematic::NA, Sign::none)),
      A_Bs2D0Kpi_(Params::Get().CreateFixed("A_Bs2D0Kpi", uniqueId, _neutral,
                                            Bachelor::k, Daughters::pik, 0, 0,
                                            Systematic::NA, Sign::none)),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(nullptr),
      a_Bu2Dst0h_D0gamma_WN_(nullptr),
      a_Bu2Dst0h_D0pi0_WN_(nullptr),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(MakeLittleAsym(
          ("a_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bu2D0hst_)),
      a_Bu2Dst0hst_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bu2Dst0hst_D0pi0_)),
      a_Bu2Dst0hst_D0gamma_(nullptr),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(MakeLittleAsym(
          ("a_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bs2Dst0Kpi_)),
      a_Bs2D0Kpi_(MakeLittleAsym(
          ("a_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bs2D0Kpi_)),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .R_ADS_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      // N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_tot_pik<_neutral, Bachelor::k>(
      //     uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_",
      //     NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
      //                                  Daughters::kpi>::Get(uniqueId)
      //         .N_tot_Bu2Dst0h_D0pi0_WN(),
      //     NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
      //         .R_ADS_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_GlobalFrac<_neutral, Bachelor::k,
                                                 Daughters::pik>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bd2Dsth_(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .R_ADS_Bd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .R_ADS_Bu2D0hst())),
      N_tot_Bu2Dst0hst_D0pi0_(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0hst_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0hst_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .R_ADS_Bu2Dst0hst_D0pi0())),
      N_tot_Bu2Dst0hst_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(Make_N_tot_FAVasSUP<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_FAVasSUP_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0())),
      N_tot_MisRec_(Make_N_tot_k_kpi<_neutral, Daughters::pik>(
          uniqueId, "N_tot_MisRec_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pik>::Get(uniqueId)
              .N_tot_MisRec(),
          NeutralDaughtersVars<_neutral, Daughters::pik>::Get(uniqueId)
              .R_Dst0KDst0pi_MisRec(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2D0h_(Make_N_tot_k_kpi<_neutral, Daughters::pik>(
          uniqueId, "N_tot_Bu2D0h_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pik>::Get(uniqueId)
              .N_tot_Bu2D0h(),
          NeutralDaughtersVars<_neutral, Daughters::pik>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0h())),
      N_tot_PartRec_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().splitByCharge() == true) {
    A_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
            uniqueId, "A_ADS_Bu2Dst0h_D0pi0_",
            NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::plus>::Get(
                uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    A_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
            uniqueId, "A_ADS_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::plus>::Get(
                uniqueId)
                .R_piK_Bu2Dst0h_D0gamma_WN()));
    A_Bu2Dst0h_D0pi0_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
            uniqueId, "A_ADS_Bu2Dst0h_D0pi0_WN_",
            NeutralBachelorChargeVars<_neutral, Bachelor::k,
                                      Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN(),
            NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::plus>::Get(
                uniqueId)
                .R_piK_Bu2Dst0h_D0pi0_WN()));
    a_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0pi0_));
    a_Bu2Dst0h_D0gamma_WN_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_WN_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_WN_));
    a_Bu2Dst0h_D0pi0_WN_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0pi0_WN_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0pi0_WN_));
    if (_neutral == Neutral::gamma) {
      A_Bu2Dst0h_D0gamma_ = std::shared_ptr<
          RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
          uniqueId, "A_ADS_Bu2Dst0h_D0gamma_",
          NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::minus>::Get(
              uniqueId)
              .R_piK_Bu2Dst0h_D0gamma(),
          NeutralBachelorChargeVars<_neutral, Bachelor::k, Charge::plus>::Get(
              uniqueId)
              .R_piK_Bu2Dst0h_D0gamma()));
      A_Bu2Dst0hst_D0gamma_ =
          std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
              "A_Bu2Dst0hst_D0gamma", uniqueId, _neutral, Bachelor::k,
              Daughters::pik, 0, -1, 1));
      a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_));
      a_Bu2Dst0hst_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bu2Dst0hst_D0gamma_));
    }
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::k>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .R_ADS_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::k, Daughters::pik>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_tot_FAVasSUP<_neutral, Bachelor::k>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_FAVasSUP_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0hst_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::k>(
            uniqueId, "N_tot_Bu2Dst0hst_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0hst_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .R_ADS_Bu2Dst0hst_D0gamma()));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_PartRec", uniqueId, _neutral, Bachelor::k, Daughters::pik,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::k>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .R_ADS_Bu2Dst0h_D0gamma_WN()));
    N_tot_PartRec_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::pik>(
            uniqueId, "N_tot_PartRec_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_PartRec(),
            NeutralDaughtersVars<_neutral, Daughters::pik>::Get(uniqueId)
                .R_Dst0KDst0pi_PartRec(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0()));
  }
  N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
      "N_tot_Bs2Dst0Kpi", uniqueId, _neutral, Bachelor::k, Daughters::pik,
      Configuration::Get().initYieldFAVSignal() *
          BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
              .kBR()
              .getVal(),
      -1000, 1000));
  N_tot_Bs2D0Kpi_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
      "N_tot_Bs2D0Kpi", uniqueId, _neutral, Bachelor::k, Daughters::pik,
      Configuration::Get().initYieldFAVSignal() *
          BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(uniqueId)
              .kBR()
              .getVal(),
      -1000, 1000));
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0())),
      A_Bu2Dst0h_D0gamma_WN_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0gamma_WN_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0gamma_WN())),
      A_Bu2Dst0h_D0pi0_WN_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0pi0_WN_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0_WN())),
      A_Bd2Dsth_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bd2Dsth_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bd2Dsth())),
      A_Bu2D0hst_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2D0hst_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2D0hst())),
      A_Bu2Dst0hst_D0pi0_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2Dst0hst_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2Dst0hst_D0pi0())),
      A_Bu2Dst0hst_D0gamma_(nullptr),
      A_MisRec_(Params::Get().CreateFloating("A_MisRec", uniqueId, _neutral,
                                             Bachelor::k, Daughters::kk, 0, -5,
                                             5)),
      A_Bu2D0h_(Params::Get().CreateFloating("A_Bu2D0h", uniqueId, _neutral,
                                             Bachelor::k, Daughters::kk, 0, -5,
                                             5)),
      A_PartRec_(Params::Get().CreateFloating("A_PartRec", uniqueId, _neutral,
                                              Bachelor::k, Daughters::kk, 0, -5,
                                              5)),
      A_Bs2Dst0Kpi_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                 Daughters::pik>::Get(uniqueId)
                        .A_Bs2Dst0Kpi_GetPointer()),
      A_Bs2D0Kpi_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                               Daughters::pik>::Get(uniqueId)
                      .A_Bs2D0Kpi_GetPointer()),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_D0gamma_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_WN_)),
      a_Bu2Dst0h_D0pi0_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_WN_)),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(MakeLittleAsym(
          ("a_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2D0hst_)),
      a_Bu2Dst0hst_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0hst_D0pi0_)),
      a_Bu2Dst0hst_D0gamma_(nullptr),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(MakeLittleAsym(
          ("a_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bs2Dst0Kpi_)),
      a_Bs2D0Kpi_(MakeLittleAsym(
          ("a_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bs2D0Kpi_)),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      // N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
      //     uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_",
      //     NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
      //                                  Daughters::kk>::Get(uniqueId)
      //         .N_tot_Bu2Dst0h_D0pi0_WN(),
      //     NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
      //         .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_GlobalFrac<_neutral, Bachelor::k,
                                                 Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bd2Dsth_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0hst())),
      N_tot_Bu2Dst0hst_D0pi0_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0hst_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2Dst0hst_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0pi0())),
      N_tot_Bu2Dst0hst_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Make_N_tot_k_kpi<_neutral, Daughters::kk>(
          uniqueId, "N_tot_MisRec_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_MisRec(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_MisRec(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2D0h_(Make_N_tot_k_kpi<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2D0h_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2D0h(),
          NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0h())),
      N_tot_PartRec_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().runADS() == true) {
    N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "N_tot_Bs2Dst0Kpi_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2Dst0Kpi()));
    N_tot_Bs2D0Kpi_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "N_tot_Bs2D0Kpi_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2D0Kpi()));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_k_CP<_neutral, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kk>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bu2Dst0hst_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_k_CP<_neutral, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0hst_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kk>::Get(uniqueId)
                .N_tot_Bu2Dst0hst_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0hst_D0gamma()));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "A_Bu2Dst0h_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .A_CP_Bu2Dst0h_D0gamma()));
    A_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "A_Bu2Dst0hst_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .A_CP_Bu2Dst0hst_D0gamma()));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    a_Bu2Dst0hst_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0hst_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
            .c_str(),
        *A_Bu2Dst0hst_D0gamma_));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_PartRec", uniqueId, _neutral, Bachelor::k, Daughters::kk,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::kk>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_k_CP<_neutral, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kk>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN()));
    N_tot_PartRec_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kk>(
            uniqueId, "N_tot_PartRec_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kk>::Get(uniqueId)
                .N_tot_PartRec(),
            NeutralDaughtersVars<_neutral, Daughters::kk>::Get(uniqueId)
                .R_Dst0KDst0pi_PartRec(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0()));
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0())),
      A_Bu2Dst0h_D0gamma_WN_(
          Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
              uniqueId, "A_Bu2Dst0h_D0gamma_WN_",
              NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .A_CP_Bu2Dst0h_D0gamma_WN())),
      A_Bu2Dst0h_D0pi0_WN_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0pi0_WN_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2Dst0h_D0pi0_WN())),
      A_Bd2Dsth_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bd2Dsth_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bd2Dsth())),
      A_Bu2D0hst_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2D0hst_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2D0hst())),
      A_Bu2Dst0hst_D0pi0_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0hst_D0pi0_",
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .A_CP_Bu2Dst0hst_D0pi0())),
      A_Bu2Dst0hst_D0gamma_(nullptr),
      A_MisRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                             Daughters::kk>::Get(uniqueId)
                    .A_MisRec_GetPointer()),
      A_Bu2D0h_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                             Daughters::kk>::Get(uniqueId)
                    .A_Bu2D0h_GetPointer()),
      A_PartRec_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                              Daughters::kk>::Get(uniqueId)
                     .A_PartRec_GetPointer()),
      A_Bs2Dst0Kpi_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                 Daughters::pik>::Get(uniqueId)
                        .A_Bs2Dst0Kpi_GetPointer()),
      A_Bs2D0Kpi_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                               Daughters::pik>::Get(uniqueId)
                      .A_Bs2D0Kpi_GetPointer()),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_D0gamma_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_WN_)),
      a_Bu2Dst0h_D0pi0_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_WN_)),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(MakeLittleAsym(
          ("a_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2D0hst_)),
      a_Bu2Dst0hst_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0hst_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0hst_D0pi0_)),
      a_Bu2Dst0hst_D0gamma_(nullptr),
      a_MisRec_(MakeLittleAsym(
          ("a_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_MisRec_)),
      a_Bu2D0h_(MakeLittleAsym(
          ("a_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2D0h_)),
      a_PartRec_(MakeLittleAsym(
          ("a_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_PartRec_)),
      a_Bs2Dst0Kpi_(MakeLittleAsym(
          ("a_Bs2Dst0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bs2Dst0Kpi_)),
      a_Bs2D0Kpi_(MakeLittleAsym(
          ("a_Bs2D0Kpi_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bs2D0Kpi_)),
      N_tot_Bu2Dst0h_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      // N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
      //     uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_",
      //     NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
      //                                  Daughters::pipi>::Get(uniqueId)
      //         .N_tot_Bu2Dst0h_D0pi0_WN(),
      //     NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
      //         .R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_GlobalFrac<_neutral, Bachelor::k,
                                                 Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralVars<_neutral>::Get(uniqueId).globalFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bd2Dsth_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0hst())),
      N_tot_Bu2Dst0hst_D0pi0_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2Dst0hst_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2Dst0hst_D0pi0(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0hst_D0pi0())),
      N_tot_Bu2Dst0hst_D0gamma_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_tot_MisRec_(Make_N_tot_k_kpi<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_MisRec_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_MisRec(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_MisRec(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0())),
      N_tot_Bu2D0h_(Make_N_tot_k_kpi<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2D0h_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2D0h(),
          NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0h(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0h())),
      N_tot_PartRec_(nullptr),
      N_tot_Bs2Dst0Kpi_(nullptr),
      N_tot_Bs2D0Kpi_(nullptr) {
  if (Configuration::Get().runADS() == true) {
    N_tot_Bs2Dst0Kpi_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "N_tot_Bs2Dst0Kpi_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2Dst0Kpi()));
    N_tot_Bs2D0Kpi_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "N_tot_Bs2D0Kpi_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2D0Kpi()));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_CP<_neutral, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_GlobalFrac<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId)
                .globalFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_CP<_neutral, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0hst_D0gamma_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_Bu2Dst0hst_D0gamma(),
            NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0hst_D0gamma()));
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "A_Bu2Dst0h_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .A_CP_Bu2Dst0h_D0gamma()));
    A_Bu2Dst0hst_D0gamma_ = std::shared_ptr<RooAbsReal>(
        Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "A_Bu2Dst0hst_D0gamma_",
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .A_CP_Bu2Dst0hst_D0gamma()));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    a_Bu2Dst0hst_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0hst_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
            .c_str(),
        *A_Bu2Dst0hst_D0gamma_));
    N_tot_PartRec_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_PartRec", uniqueId, _neutral, Bachelor::k, Daughters::pipi,
        NeutralVars<_neutral>::Get(uniqueId).initYieldFAVPartRec() *
            BachelorDaughtersVars<Bachelor::k, Daughters::pipi>::Get(uniqueId)
                .kBR()
                .getVal(),
        0, 1000000));
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_CP<_neutral, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN()));
    N_tot_PartRec_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::pipi>(
            uniqueId, "N_tot_PartRec_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_PartRec(),
            NeutralDaughtersVars<_neutral, Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_PartRec(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0pi0()));
  }
}

void InstantiateNeutralBachelorDaughtersVars() {
  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Get(
      -1);
  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi, Daughters::kk>::Get(
      -1);
  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                               Daughters::pipi>::Get(-1);
  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi, Daughters::pik>::Get(
      -1);
  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k, Daughters::kpi>::Get(
      -1);
  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k, Daughters::kk>::Get(
      -1);
  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k, Daughters::pipi>::Get(
      -1);
  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k, Daughters::pik>::Get(
      -1);
  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                               Daughters::kpi>::Get(-1);
  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                               Daughters::kk>::Get(-1);
  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                               Daughters::pipi>::Get(-1);
  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                               Daughters::pik>::Get(-1);
  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                               Daughters::kpi>::Get(-1);
  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k, Daughters::kk>::Get(
      -1);
  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                               Daughters::pipi>::Get(-1);
  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                               Daughters::pik>::Get(-1);
}
