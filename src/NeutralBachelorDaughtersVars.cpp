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
RooFormulaVar *Make_N_BkgFrac(int uniqueId, const char *nameStr,
                              RooAbsReal &N_rel, RooAbsReal &bkgFrac) {
  return new RooFormulaVar(
      (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters)).c_str(),
      "@0*@1", RooArgList(N_rel, bkgFrac));
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
RooFormulaVar *Make_N_WN(int uniqueId, const char *nameStr, RooAbsReal &N_sig,
                         RooAbsReal &globalFrac) {
  return new RooFormulaVar(
      (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters)).c_str(),
      "@0*@1*@2",
      RooArgList(N_sig, globalFrac,
                 NeutralVars<neutral>::Get(uniqueId).bkgFracGlobal_WN()));
}

template <Neutral neutral>
std::shared_ptr<RooRealVar> Make_N_Bu2Dst0pi_D0gamma_D02kpi(int uniqueId) {
  switch (neutral) {
    case Neutral::gamma:
      return Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0gamma", uniqueId, Neutral::gamma, Bachelor::pi,
          Daughters::kpi, 82000, -1000000, 1000000);
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
          Daughters::kpi, 26000, -1000000, 1000000);
      break;
    case Neutral::gamma:
      return Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0pi0", uniqueId, Neutral::gamma, Bachelor::pi,
          Daughters::kpi,
          N_gamma.getVal() *
              (GlobalVars::Get(uniqueId).kBF_Dst02D0pi0().getVal() /
               GlobalVars::Get(uniqueId).kBF_Dst02D0gamma().getVal()) *
              ((NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                    .mcEff_Bu2Dst0h_D0pi0()
                    .getVal() *
                NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                    .orEffBu2Dst0h_D0pi0()
                    .getVal()) /
               (NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                    .mcEff_Bu2Dst0h_D0gamma()
                    .getVal() *
                NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                    .orEffBu2Dst0h_D0gamma()
                    .getVal())),
          -1000000, 1000000);
      break;
  }
}

template <Neutral neutral, Daughters daughters>
RooFormulaVar *Make_N_scaled_kpi(int uniqueId, const char *nameStr,
                                 RooAbsReal &N_kpi) {
  if (daughters == Daughters::kk) {
    return new RooFormulaVar(
        (nameStr + ComposeName(uniqueId, neutral, Bachelor::pi, daughters))
            .c_str(),
        "@0*@1/@2",
        RooArgList(N_kpi, GlobalVars::Get(uniqueId).kBF_D02kk(),
                   GlobalVars::Get(uniqueId).kBF_D02kpi()));
  } else if (daughters == Daughters::pipi) {
    return new RooFormulaVar(
        (nameStr + ComposeName(uniqueId, neutral, Bachelor::pi, daughters))
            .c_str(),
        "@0*@1/@2",
        RooArgList(N_kpi, GlobalVars::Get(uniqueId).kBF_D02pipi(),
                   GlobalVars::Get(uniqueId).kBF_D02kpi()));
  } else {
    throw std::runtime_error("Cannot scale yield to Kπ or πK mode");
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::kpi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi,
          Daughters::kpi, 0, 0.0008, 0.0003,
          Systematic::A_pi_Kpi_Bu2Dst0h_D0gamma, Sign::none)),
      A_Bu2Dst0h_D0pi0_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_D0pi0", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
          0, 0.0003, 0.0008, Systematic::A_pi_Kpi_Bu2Dst0h_D0pi0, Sign::none)),
      A_Bu2Dst0h_WN_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_WN", uniqueId, _neutral, Bachelor::pi, Daughters::kpi, 0,
          0.0008, Systematic::A_pi_Kpi_Bu2Dst0h_WN, Sign::none)),
      A_Bd2Dsth_(Params::Get().CreateFixed("A_Bd2Dsth", uniqueId, _neutral,
                                           Bachelor::pi, Daughters::kpi, 0, 0.0,
                                           Systematic::NA, Sign::none)),
      // A_Bu2D0hst_(Params::Get().CreateFixed(
      //     "A_Bu2D0hst", uniqueId, _neutral, Bachelor::pi, Daughters::kpi, 0,
      //     0.0008, Systematic::A_pi_Kpi_Bu2D0hst, Sign::none)),
      A_Bu2D0hst_(Params::Get().CreateFloating("A_Bu2D0hst", uniqueId, _neutral,
                                               Bachelor::pi, Daughters::kpi, 0,
                                               -1, 1)),
      A_Bu2Dst0hst_(Params::Get().CreateFixed(
          "A_Bu2Dst0hst", uniqueId, _neutral, Bachelor::pi, Daughters::kpi, 0,
          0.001, Systematic::A_pi_Kpi_Bu2Dst0hst, Sign::none)),
      // A_Bu2Dst0hst_(Params::Get().CreateFloating(
      //     "A_Bu2Dst0hst", uniqueId, _neutral, Bachelor::pi, Daughters::kpi,
      //     0, -1, 1)),
      A_Lb2Omegach_Lcpi0_(nullptr),
      A_Bs2Dst0Kst0_(nullptr),
      A_Bs2D0Kst0_(nullptr),
      A_comb_(Params::Get().CreateFixed("A_comb", uniqueId, _neutral,
                                        Bachelor::pi, Daughters::kpi, 0, 0.1,
                                        Systematic::Combinatorial, Sign::none)),
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
      a_Bu2Dst0h_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_WN_)),
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
      a_Bu2Dst0hst_(MakeLittleAsym(
          ("a_Bu2Dst0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0hst_)),
      a_Lb2Omegach_Lcpi0_(nullptr),
      a_Bs2Dst0Kst0_(nullptr),
      a_Bs2D0Kst0_(nullptr),
      a_comb_(MakeLittleAsym(
          ("a_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
              .c_str(),
          *A_comb_)),
      N_tot_Bu2Dst0h_D0gamma_(
          Make_N_Bu2Dst0pi_D0gamma_D02kpi<_neutral>(uniqueId)),
      // N_tot_Bu2Dst0h_D0pi0_(Make_N_Bu2Dst0pi_D0pi0_D02kpi<_neutral>(
      //     uniqueId, *N_tot_Bu2Dst0h_D0gamma_)),
      N_tot_Bu2Dst0h_D0pi0_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_(nullptr),
      N_tot_Bu2Dst0h_WN_(nullptr),
      N_tot_Bd2Dsth_(nullptr),
      N_tot_Bu2D0hst_(nullptr),
      N_tot_Bu2Dst0hst_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_tot_Lb2Omegach_Lcpi0_(nullptr),
      N_tot_Bs2Dst0Kst0_(nullptr),
      N_tot_Bs2D0Kst0_(nullptr),
      N_tot_comb_(Params::Get().CreateFloating("N_tot_comb", uniqueId, _neutral,
                                               Bachelor::pi, Daughters::kpi,
                                               100, -1000, 1000)),
      Bu2D0hst_mean1Bu_(nullptr),
      Bu2D0hst_mean2Bu_(nullptr),
      Bu2D0hst_sigma1Bu_(nullptr),
      Bu2D0hst_sigma2Bu_(nullptr),
      pdf1Bu_Bu2D0hst_(nullptr),
      pdf2Bu_Bu2D0hst_(nullptr),
      pdfBu_Bu2D0hst_(nullptr),
      Bu2D0hst_aDelta_(nullptr),
      pdfDelta_Bu2D0hst_(nullptr),
      Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_D0gamma_(nullptr),
      pdf2Bu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_(nullptr),
      Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_(nullptr),
      pdfBu_Bu2Dst0hst_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0pi0_ = std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_tot_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
            .c_str(),
        "@0*@1*(@2*@3)/(@4*@5)",
        RooArgList(*N_tot_Bu2Dst0h_D0gamma_,
                   NeutralVars<_neutral>::Get(uniqueId).BR_pi02gamma_eff(),
                   NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                       .mcEff_Bu2Dst0h_D0pi0(),
                   NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                       .orEffBu2Dst0h_D0pi0(),
                   NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                       .mcEff_Bu2Dst0h_D0gamma(),
                   NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                       .orEffBu2Dst0h_D0gamma())));
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_WN<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .bkgFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bd2Dsth()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  } else {
    N_tot_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "N_tot_Bu2Dst0h_D0pi0", uniqueId, Neutral::pi0, Bachelor::pi,
            Daughters::kpi, 22000, -1000000, 1000000));
    N_tot_Bu2Dst0h_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_WN<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_WN_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .bkgFrac_Bu2Dst0h_WN()));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bd2Dsth()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  }
  N_tot_Bu2Dst0h_D0pi0_WN_ = std::shared_ptr<RooFormulaVar>(
      Make_N_WN<_neutral, Bachelor::pi, Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .bkgFrac_Bu2Dst0h_D0pi0_WN()));
  if (_neutral == Neutral::pi0) {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
            ("N_tot_Bu2Dst0h_D0gamma_WN_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kpi))
                .c_str(),
            "@0*@1*@2",
            RooArgList(
                *N_tot_Bu2Dst0h_D0pi0_WN_,
                NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                    .bkgFrac_Bu2Dst0h_D0gamma_WN(),
                NeutralVars<_neutral>::Get(uniqueId)
                    .bkgFloatingFrac_Bu2Dst0h_D0gamma_WN())));
  }
  // Fixed relative to Bd2Dsth
  N_tot_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
      Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::kpi>(
          uniqueId, "N_tot_Bu2D0hst_", *N_tot_Bd2Dsth_,
          NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bu2D0hst()));
  N_tot_Bu2Dst0hst_ = std::shared_ptr<RooFormulaVar>(
      Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0hst_", *N_tot_Bd2Dsth_,
          NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bu2Dst0hst()));
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      A_Bu2Dst0h_WN_(nullptr),
      A_Bd2Dsth_(Params::Get().CreateFixed("A_Bd2Dsth", uniqueId, _neutral,
                                           Bachelor::pi, Daughters::pik, 0, 0.0,
                                           Systematic::NA, Sign::none)),
      // Float due to presence of B->Dππ in D*π mode
      A_Bu2D0hst_(nullptr),
      A_Bu2Dst0hst_(nullptr),
      // A_Bu2Dst0hst_(Params::Get().CreateFixed(
      //     "A_Bu2Dst0hst", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
      //     0, 0.001, Systematic::A_pi_Kpi_Bu2Dst0hst, Sign::none)),
      A_Bs2Dst0Kst0_(nullptr),
      A_Bs2D0Kst0_(nullptr),
      A_comb_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                           Daughters::kpi>::Get(uniqueId)
                  .A_comb_GetPointer()),
      // A_comb_(Params::Get().CreateFloating("A_comb", uniqueId, _neutral,
      //                                      Bachelor::pi, Daughters::pik, 0,
      //                                      -1, 1)),
      A_Lb2Omegach_Lcpi0_(nullptr),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(nullptr),
      a_Bu2Dst0h_WN_(nullptr),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(nullptr),
      a_Bu2Dst0hst_(nullptr),
      // a_Bu2Dst0hst_(MakeLittleAsym(
      //     ("a_Bu2Dst0hst_" +
      //      ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
      //         .c_str(),
      //     *A_Bu2Dst0hst_)),
      a_Lb2Omegach_Lcpi0_(nullptr),
      a_Bs2Dst0Kst0_(nullptr),
      a_Bs2D0Kst0_(nullptr),
      a_comb_(MakeLittleAsym(
          ("a_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          *A_comb_)),
      N_tot_Bu2Dst0h_D0gamma_(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0gamma(),
          BachelorVars<Bachelor::pi>::Get(uniqueId).R_ADS_Bu2Dst0h_D0gamma())),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          BachelorVars<Bachelor::pi>::Get(uniqueId).R_ADS_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_(
          Make_N_WN<_neutral, Bachelor::pi, Daughters::pik>(
              uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
              NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .bkgFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_WN_(nullptr),
      N_tot_Bd2Dsth_(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          BachelorVars<Bachelor::pi>::Get(uniqueId).R_ADS_Bd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          BachelorVars<Bachelor::pi>::Get(uniqueId).R_ADS_Bu2D0hst())),
      N_tot_Bu2Dst0hst_(Make_N_tot_pik<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bu2Dst0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0hst(),
          BachelorVars<Bachelor::pi>::Get(uniqueId).R_ADS_Bu2Dst0hst())),
      N_tot_Bu2Dst0h_D0gamma_D02pik_(
          Make_N_tot_FAVasSUP<_neutral, Bachelor::pi>(
              uniqueId, "N_tot_Bu2Dst0h_D0gamma_D02pik_",
              NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                           Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma())),
      N_tot_Bu2Dst0h_D0pi0_D02pik_(Make_N_tot_FAVasSUP<_neutral, Bachelor::pi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_D02pik_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0pi0_WN_D02pik_(
          Make_N_tot_FAVasSUP<_neutral, Bachelor::pi>(
              uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_D02pik_",
              NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                           Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_tot_Lb2Omegach_Lcpi0_(nullptr),
      N_tot_Bs2Dst0Kst0_(nullptr),
      N_tot_Bs2D0Kst0_(nullptr),
      // N_tot_comb_(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
      //                                          Daughters::kpi>::Get(uniqueId)
      //                 .N_tot_comb_GetPointer()),
      fracComb_(Params::Get().CreateFixed(
          "fracComb", uniqueId, _neutral, Bachelor::pi, Daughters::pik, 1.45,
          0.10, Systematic::Combinatorial, Sign::same)),
      N_tot_comb_(new RooFormulaVar(
          ("N_tot_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
              .c_str(),
          "", "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                  Daughters::kpi>::Get(uniqueId)
                         .N_tot_comb(),
                     *fracComb_))),
      // N_tot_comb_(Params::Get().CreateFloating("N_tot_comb", uniqueId,
      //                                          _neutral, Bachelor::pi,
      //                                          Daughters::pik, 100, 0,
      //                                          10000)),
      Bu2D0hst_mean1Bu_(nullptr),
      Bu2D0hst_mean2Bu_(nullptr),
      Bu2D0hst_sigma1Bu_(nullptr),
      Bu2D0hst_sigma2Bu_(nullptr),
      pdf1Bu_Bu2D0hst_(nullptr),
      pdf2Bu_Bu2D0hst_(nullptr),
      pdfBu_Bu2D0hst_(nullptr),
      Bu2D0hst_aDelta_(nullptr),
      pdfDelta_Bu2D0hst_(nullptr),
      Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_D0gamma_(nullptr),
      pdf2Bu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_(nullptr),
      Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_(nullptr),
      pdfBu_Bu2Dst0hst_(nullptr) {
  if (Configuration::Get().splitByCharge() == true) {
    A_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::pi>(
            uniqueId, "A_ADS_Bu2Dst0h_D0pi0_",
            BachelorChargeVars<Bachelor::pi, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            BachelorChargeVars<Bachelor::pi, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    A_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::pi>(
            uniqueId, "A_ADS_Bu2Dst0h_D0gamma_",
            BachelorChargeVars<Bachelor::pi, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma(),
            BachelorChargeVars<Bachelor::pi, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    A_Bu2Dst0h_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::pi>(
            uniqueId, "A_ADS_Bu2Dst0h_WN_",
            BachelorChargeVars<Bachelor::pi, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_WN(),
            BachelorChargeVars<Bachelor::pi, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_WN()));
    // A_Bu2Dst0h_WN_ = std::shared_ptr<RooRealVar>(
    //     Params::Get().CreateFloating("A_Bu2Dst0h_WN", uniqueId, _neutral,
    //                                  Bachelor::pi, Daughters::pik, 0, -2,
    //                                  2));
    a_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0pi0_));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    a_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_WN_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_WN_));
    if (_neutral == Neutral::gamma) {
      A_Bu2D0hst_ =
          std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::pi>(
              uniqueId, "A_ADS_Bu2D0hst_",
              BachelorChargeVars<Bachelor::pi, Charge::minus>::Get(uniqueId)
                  .R_piK_Bu2D0hst(),
              BachelorChargeVars<Bachelor::pi, Charge::plus>::Get(uniqueId)
                  .R_piK_Bu2D0hst()));
      A_Bu2Dst0hst_ =
          std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::pi>(
              uniqueId, "A_ADS_Bu2Dst0hst_",
              BachelorChargeVars<Bachelor::pi, Charge::minus>::Get(uniqueId)
                  .R_piK_Bu2Dst0hst(),
              BachelorChargeVars<Bachelor::pi, Charge::plus>::Get(uniqueId)
                  .R_piK_Bu2Dst0hst()));
    } else {
      // A_Bu2D0hst_ = std::shared_ptr<RooRealVar>(
      //     Params::Get().CreateFloating("A_Bu2D0hst", uniqueId, _neutral,
      //                                  Bachelor::pi, Daughters::pik, 0, -1,
      //                                  1));
      A_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "A_Bu2D0hst", uniqueId, _neutral, Bachelor::pi, Daughters::pik, 0,
          0.0008, Systematic::A_pi_Kpi_Bu2D0hst, Sign::none));
      // A_Bu2Dst0hst_ = std::shared_ptr<RooRealVar>(
      //     Params::Get().CreateFloating("A_Bu2Dst0hst", uniqueId, _neutral,
      //                                  Bachelor::pi, Daughters::pik, 0, -1,
      //                                  1));
      A_Bu2Dst0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
          "A_Bu2Dst0hst", uniqueId, _neutral, Bachelor::pi, Daughters::pik, 0,
          0.001, Systematic::A_pi_Kpi_Bu2Dst0hst, Sign::none));
    }
    a_Bu2D0hst_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2D0hst_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        *A_Bu2D0hst_));
    a_Bu2Dst0hst_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0hst_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0hst_));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_WN<_neutral, Bachelor::pi, Daughters::pik>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .bkgFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bu2Dst0h_D0gamma_WN_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_tot_FAVasSUP<_neutral, Bachelor::pi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_D02pik_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN()));
    Bu2D0hst_mean1Bu_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "Bu2D0hst_mean1Bu", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
        5.2144e+03, 4.53e+00, Systematic::Bu2D0hst_PdfBu_D02pik, Sign::same));
    // Bu2D0hst_mean1Bu_ =
    //     std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
    //         "Bu2D0hst_mean1Bu", uniqueId, _neutral, Bachelor::pi,
    //         Daughters::pik, Mode::Bu2D0rho, 5150, 5250));
    Bu2D0hst_mean2Bu_ = std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
        ("Bu2D0hst_mean2Bu_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "", "@0+@1",
        RooArgSet(
            *Bu2D0hst_mean1Bu_,
            NeutralVars<_neutral>::Get(uniqueId).Bu2D0hst_meanOffset21Bu())));
    Bu2D0hst_sigma1Bu_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "Bu2D0hst_sigma1Bu", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
        9.6078e+01, 4.72e+00, Systematic::Bu2D0hst_PdfBu_D02pik, Sign::same));
    // Bu2D0hst_sigma1Bu_ =
    //     std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
    //         "Bu2D0hst_sigma1Bu", uniqueId, _neutral, Bachelor::pi,
    //         Daughters::pik, Mode::Bu2D0rho, 55, 120));
    Bu2D0hst_sigma2Bu_ = std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
        ("Bu2D0hst_sigma2Bu_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "@0*@1",
        RooArgSet(
            *Bu2D0hst_sigma1Bu_,
            NeutralVars<_neutral>::Get(uniqueId).Bu2D0hst_sigmaRatio21Bu())));
    pdf1Bu_Bu2D0hst_ = std::shared_ptr<RooCBShape>(new RooCBShape(
        ("pdf1Bu_Bu2D0hst_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "", Configuration::Get().buDeltaMass(), *Bu2D0hst_mean1Bu_,
        *Bu2D0hst_sigma1Bu_,
        NeutralVars<_neutral>::Get(uniqueId).Bu2D0hst_a1Bu(),
        NeutralVars<_neutral>::Get(uniqueId).Bu2D0hst_n1Bu()));
    pdf2Bu_Bu2D0hst_ = std::shared_ptr<RooGaussian>(new RooGaussian(
        ("pdf2Bu_Bu2D0hst_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "", Configuration::Get().buDeltaMass(), *Bu2D0hst_mean2Bu_,
        *Bu2D0hst_sigma2Bu_));
    pdfBu_Bu2D0hst_ = std::shared_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfBu_Bu2D0hst_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "", RooArgSet(*pdf1Bu_Bu2D0hst_, *pdf2Bu_Bu2D0hst_),
        NeutralVars<_neutral>::Get(uniqueId).Bu2D0hst_fracPdf1Bu()));
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    Bu2Dst0hst_D0gamma_mean1Bu_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "Bu2Dst0hst_D0gamma_mean1Bu", uniqueId, _neutral, Bachelor::pi,
            Daughters::pik, 5.1115e+03, 4.27e+00,
            Systematic::Bu2Dst0hst_PdfBu_D02pik, Sign::same));
    // Bu2Dst0hst_D0gamma_mean1Bu_ =
    // std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
    //     "Bu2Dst0hst_D0gamma_mean1Bu", uniqueId, _neutral, Bachelor::pi,
    //     Daughters::pik, Mode::Bu2Dst0rho_D0gamma, 5070, 5170));
    Bu2Dst0hst_D0gamma_mean2Bu_ =
        std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
            ("Bu2Dst0hst_D0gamma_mean2Bu_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
                .c_str(),
            "", "@0+@1",
            RooArgSet(*Bu2Dst0hst_D0gamma_mean1Bu_,
                      NeutralVars<_neutral>::Get(uniqueId)
                          .Bu2Dst0hst_D0gamma_meanOffset21Bu())));
    // Bu2Dst0hst_D0gamma_fracPdf1Bu_ =
    //     std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
    //         "Bu2Dst0hst_D0gamma_fracPdf1Bu", uniqueId, _neutral,
    //         Bachelor::pi, Daughters::pik, Mode::Bu2Dst0rho_D0gamma, 0, 1));
    Bu2Dst0hst_D0gamma_fracPdf1Bu_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "Bu2Dst0hst_D0gamma_fracPdf1Bu", uniqueId, _neutral, Bachelor::pi,
            Daughters::pik, 7.2478e-01, 8.70e-02,
            Systematic::Bu2Dst0hst_PdfBu_D02pik, Sign::same));
    pdf1Bu_Bu2Dst0hst_D0gamma_ = std::unique_ptr<RooCBShape>(new RooCBShape(
        ("pdf1Bu_Bu2Dst0hst_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "", Configuration::Get().buDeltaMass(), *Bu2Dst0hst_D0gamma_mean1Bu_,
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
            .Bu2Dst0hst_D0gamma_sigma1Bu(),
        NeutralVars<_neutral>::Get(uniqueId).Bu2Dst0hst_D0gamma_a1Bu(),
        NeutralVars<_neutral>::Get(uniqueId).Bu2Dst0hst_D0gamma_n1Bu()));
    pdf2Bu_Bu2Dst0hst_D0gamma_ = std::unique_ptr<RooCBShape>(new RooCBShape(
        ("pdf2Bu_Bu2Dst0hst_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "", Configuration::Get().buDeltaMass(), *Bu2Dst0hst_D0gamma_mean2Bu_,
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
            .Bu2Dst0hst_D0gamma_sigma2Bu(),
        NeutralVars<_neutral>::Get(uniqueId).Bu2Dst0hst_D0gamma_a2Bu(),
        NeutralVars<_neutral>::Get(uniqueId).Bu2Dst0hst_D0gamma_n2Bu()));
    pdfBu_Bu2Dst0hst_D0gamma_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfBu_Bu2Dst0hst_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "", RooArgSet(*pdf1Bu_Bu2Dst0hst_D0gamma_, *pdf2Bu_Bu2Dst0hst_D0gamma_),
        *Bu2Dst0hst_D0gamma_fracPdf1Bu_));
    Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
            "Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_", uniqueId, _neutral,
            Bachelor::pi, Daughters::pik, 0.183008, 0.468965,
            Systematic::Bu2Dst0hst_PdfBu_D02pik, Sign::same));
    Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_ =
        std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
            ("Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
                .c_str(),
            "@0*@1",
            RooArgSet(*Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_,
                      NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                          .Bu2Dst0hst_fracD0pi0_Bu())));
    pdfBu_Bu2Dst0hst_ = std::shared_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfBu_Bu2Dst0hst_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "",
        RooArgSet(NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                      .pdfBu_Bu2Dst0hst_D0pi0(),
                  *pdfBu_Bu2Dst0hst_D0gamma_),
        *Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_));
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::unique_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::pi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            BachelorVars<Bachelor::pi>::Get(uniqueId)
                .R_ADS_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_WN_ =
        std::unique_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::pi>(
            uniqueId, "N_tot_Bu2Dst0h_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_WN(),
            BachelorVars<Bachelor::pi>::Get(uniqueId).R_ADS_Bu2Dst0h_WN()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    Bu2D0hst_aDelta_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "Bu2D0hst_aDelta", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
        -2.6826e+00, 9.18e-01, Systematic::Bu2D0hst_PdfDelta_D02pik,
        Sign::none));
    // Bu2D0hst_aDelta_ =
    // std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
    //     "Bu2D0hst_aDelta", uniqueId, _neutral, Bachelor::pi, Daughters::pik,
    //     Mode::Bu2D0rho, -5, 5));
    pdfDelta_Bu2D0hst_ = std::shared_ptr<RooDstD0BG>(new RooDstD0BG(
        ("pdfDelta_Bu2D0hst_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pik))
            .c_str(),
        "", Configuration::Get().deltaMass(),
        NeutralVars<_neutral>::Get(uniqueId).Bu2D0hst_thresholdDelta(),
        NeutralVars<_neutral>::Get(uniqueId).Bu2D0hst_cDelta(),
        *Bu2D0hst_aDelta_,
        NeutralVars<_neutral>::Get(uniqueId).Bu2D0hst_bDelta()));
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0gamma_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2Dst0h_D0gamma())),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2Dst0h_D0pi0())),
      A_Bu2Dst0h_WN_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_WN_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2Dst0h_WN())),
      A_Bd2Dsth_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bd2Dsth_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bd2Dsth())),
      A_Bu2D0hst_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2D0hst_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2D0hst())),
      A_Bu2Dst0hst_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Bu2Dst0hst_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2Dst0hst())),
      A_Lb2Omegach_Lcpi0_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "A_Lb2Omegach_Lcpi0_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Lb2Omegach_Lcpi0())),
      A_Bs2Dst0Kst0_(nullptr),
      A_Bs2D0Kst0_(nullptr),
      A_comb_(Params::Get().CreateFixed("A_comb", uniqueId, _neutral,
                                        Bachelor::pi, Daughters::kk, 0, 0.1,
                                        Systematic::Combinatorial, Sign::none)),
      a_Bu2Dst0h_D0gamma_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_)),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_WN_)),
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
      a_Bu2Dst0hst_(MakeLittleAsym(
          ("a_Bu2Dst0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0hst_)),
      a_Lb2Omegach_Lcpi0_(MakeLittleAsym(
          ("a_Lb2Omegach_Lcpi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_Lb2Omegach_Lcpi0_)),
      a_Bs2Dst0Kst0_(nullptr),
      a_Bs2D0Kst0_(nullptr),
      a_comb_(MakeLittleAsym(
          ("a_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          *A_comb_)),
      N_tot_Bu2Dst0h_D0gamma_(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi,
          Daughters::kk,
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma()
                  .getVal() *
              GlobalVars::Get(uniqueId).kBF_D02kk().getVal() /
              GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
          -1000000, 1000000)),
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
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_WN<_neutral, Bachelor::pi, Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .bkgFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_WN_(nullptr),
      // NO CPV
      N_tot_Bd2Dsth_(nullptr),
      // N_tot_Bu2D0hst_(nullptr),
      N_tot_Bu2D0hst_(new RooFormulaVar(
          ("N_tot_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "@0*@1*@2/@3",
          RooArgSet(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                 Daughters::kpi>::Get(uniqueId)
                        .N_tot_Bu2D0hst(),
                    NeutralVars<_neutral>::Get(uniqueId).cpFrac_Bu2D0hst(),
                    GlobalVars::Get(uniqueId).kBF_D02kk(),
                    GlobalVars::Get(uniqueId).kBF_D02kpi()))),
      // N_tot_Bu2D0hst_(Params::Get().CreateFloating(
      //     "N_tot_Bu2D0hst", uniqueId, _neutral, Bachelor::pi, Daughters::kk,
      //     NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
      //                                  Daughters::kpi>::Get(uniqueId)
      //             .N_tot_Bu2D0hst()
      //             .getVal() *
      //         GlobalVars::Get(uniqueId).kBF_D02kk().getVal() /
      //         GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
      //     -1000000, 1000000)),
      // N_tot_Bu2Dst0hst_(Make_N_scaled_kpi<_neutral, Daughters::kk>(
      //     uniqueId, "N_tot_Bu2Dst0hst_",
      //     NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
      //                                  Daughters::kpi>::Get(uniqueId)
      //         .N_tot_Bu2Dst0hst())),
      N_tot_Bu2Dst0hst_(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0hst", uniqueId, _neutral, Bachelor::pi, Daughters::kk,
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0hst()
                  .getVal() *
              GlobalVars::Get(uniqueId).kBF_D02kk().getVal() /
              GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_tot_Lb2Omegach_Lcpi0_(nullptr),
      N_tot_Bs2Dst0Kst0_(nullptr),
      N_tot_Bs2D0Kst0_(nullptr),
      fracComb_(Params::Get().CreateFixed(
          "fracComb", uniqueId, _neutral, Bachelor::pi, Daughters::kk, 0.66,
          0.06, Systematic::Combinatorial, Sign::same)),
      // fracComb_(Params::Get().CreateFloating("fracComb", uniqueId, _neutral,
      //                                     Bachelor::pi, Daughters::kk, 0.66,
      //                                     -10, 10)),
      N_tot_comb_(new RooFormulaVar(
          ("N_tot_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
              .c_str(),
          "", "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                  Daughters::kpi>::Get(uniqueId)
                         .N_tot_comb(),
                     *fracComb_))),
      // N_tot_comb_(Params::Get().CreateFloating("N_tot_comb", uniqueId,
      //                                          _neutral, Bachelor::pi,
      //                                          Daughters::kk, 100, -1000,
      //                                          1000)),
      Bu2D0hst_mean1Bu_(nullptr),
      Bu2D0hst_mean2Bu_(nullptr),
      Bu2D0hst_sigma1Bu_(nullptr),
      Bu2D0hst_sigma2Bu_(nullptr),
      pdf1Bu_Bu2D0hst_(nullptr),
      pdf2Bu_Bu2D0hst_(nullptr),
      pdfBu_Bu2D0hst_(nullptr),
      Bu2D0hst_aDelta_(nullptr),
      pdfDelta_Bu2D0hst_(nullptr),
      Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_D0gamma_(nullptr),
      pdf2Bu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_(nullptr),
      Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_(nullptr),
      pdfBu_Bu2Dst0hst_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_WN<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .bkgFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bd2Dsth()));
    N_tot_Lb2Omegach_Lcpi0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Lb2Omegach_Lcpi0_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracKK_Lb2Omegach_Lcpi0()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
            ("N_tot_Bu2Dst0h_D0gamma_WN_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::kk))
                .c_str(),
            "@0*@1*@2",
            RooArgList(
                *N_tot_Bu2Dst0h_D0pi0_WN_,
                NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                    .bkgFrac_Bu2Dst0h_D0gamma_WN(),
                NeutralVars<_neutral>::Get(uniqueId)
                    .bkgFloatingFrac_Bu2Dst0h_D0gamma_WN())));
    N_tot_Bu2Dst0h_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "N_tot_Bu2Dst0h_WN", uniqueId, _neutral, Bachelor::pi,
            Daughters::kk,
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                    .N_tot_Bu2Dst0h_WN()
                    .getVal() *
                GlobalVars::Get(uniqueId).kBF_D02kk().getVal() /
                GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
            -1000000, 1000000));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::kk>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bd2Dsth()));
    N_tot_Lb2Omegach_Lcpi0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::kpi>(
            uniqueId, "N_tot_Lb2Omegach_Lcpi0_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracKK_Lb2Omegach_Lcpi0()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  }
  // N_tot_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
  //     Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::kk>(
  //         uniqueId, "N_tot_Bu2D0hst_", *N_tot_Bd2Dsth_,
  //         NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bu2D0hst()));
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::pi, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0gamma_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2Dst0h_D0gamma())),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2Dst0h_D0pi0())),
      A_Bu2Dst0h_WN_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_WN_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2Dst0h_WN())),
      A_Bd2Dsth_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bd2Dsth_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bd2Dsth())),
      A_Bu2D0hst_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2D0hst_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2D0hst())),
      A_Bu2Dst0hst_(Make_A_D2CP<_neutral, Bachelor::pi, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0hst_",
          BachelorVars<Bachelor::pi>::Get(uniqueId).A_CP_Bu2Dst0hst())),
      A_Lb2Omegach_Lcpi0_(nullptr),
      A_Bs2Dst0Kst0_(nullptr),
      A_Bs2D0Kst0_(nullptr),
      A_comb_(Params::Get().CreateFixed("A_comb", uniqueId, _neutral,
                                        Bachelor::pi, Daughters::pipi, 0, 0.1,
                                        Systematic::Combinatorial, Sign::none)),
      a_Bu2Dst0h_D0gamma_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_)),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_WN_)),
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
      a_Bu2Dst0hst_(MakeLittleAsym(
          ("a_Bu2Dst0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0hst_)),
      a_Lb2Omegach_Lcpi0_(nullptr),
      a_Bs2Dst0Kst0_(nullptr),
      a_Bs2D0Kst0_(nullptr),
      a_comb_(MakeLittleAsym(
          ("a_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          *A_comb_)),
      N_tot_Bu2Dst0h_D0gamma_(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::pi,
          Daughters::pipi,
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma()
                  .getVal() *
              GlobalVars::Get(uniqueId).kBF_D02pipi().getVal() /
              GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
          -1000000, 1000000)),
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
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_(
          Make_N_WN<_neutral, Bachelor::pi, Daughters::pipi>(
              uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
              NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .bkgFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_WN_(nullptr),
      N_tot_Bd2Dsth_(nullptr),
      // N_tot_Bu2D0hst_(nullptr),
      N_tot_Bu2D0hst_(new RooFormulaVar(
          ("N_tot_Bu2D0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          "@0*@1*@2/@3",
          RooArgSet(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                 Daughters::kpi>::Get(uniqueId)
                        .N_tot_Bu2D0hst(),
                    NeutralVars<_neutral>::Get(uniqueId).cpFrac_Bu2D0hst(),
                    GlobalVars::Get(uniqueId).kBF_D02pipi(),
                    GlobalVars::Get(uniqueId).kBF_D02kpi()))),
      // N_tot_Bu2D0hst_(Params::Get().CreateFloating(
      //     "N_tot_Bu2D0hst", uniqueId, _neutral, Bachelor::pi,
      //     Daughters::pipi,
      //     NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
      //                                  Daughters::kpi>::Get(uniqueId)
      //             .N_tot_Bu2D0hst()
      //             .getVal() *
      //         GlobalVars::Get(uniqueId).kBF_D02pipi().getVal() /
      //         GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
      //     -1000000, 1000000)),
      // N_tot_Bu2Dst0hst_(Make_N_scaled_kpi<_neutral, Daughters::pipi>(
      //     uniqueId, "N_tot_Bu2Dst0hst_",
      //     NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
      //                                  Daughters::kpi>::Get(uniqueId)
      //         .N_tot_Bu2Dst0hst())),
      N_tot_Bu2Dst0hst_(Params::Get().CreateFloating(
          "N_tot_Bu2Dst0hst", uniqueId, _neutral, Bachelor::pi, Daughters::pipi,
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0hst()
                  .getVal() *
              GlobalVars::Get(uniqueId).kBF_D02pipi().getVal() /
              GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
          -1000000, 1000000)),
      N_tot_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_tot_Lb2Omegach_Lcpi0_(nullptr),
      N_tot_Bs2Dst0Kst0_(nullptr),
      N_tot_Bs2D0Kst0_(nullptr),
      fracComb_(Params::Get().CreateFixed("fracComb", uniqueId, _neutral,
                                          Bachelor::pi, Daughters::pipi, 0.86,
                                          0.07, Systematic::NA, Sign::same)),
      // fracComb_(Params::Get().CreateFloating("fracComb", uniqueId, _neutral,
      //                                     Bachelor::pi, Daughters::pipi,
      //                                     0.86, -10, 10)),
      N_tot_comb_(new RooFormulaVar(
          ("N_tot_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
              .c_str(),
          "", "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                  Daughters::kpi>::Get(uniqueId)
                         .N_tot_comb(),
                     *fracComb_))),
      // N_tot_comb_(Params::Get().CreateFloating("N_tot_comb", uniqueId,
      //                                          _neutral, Bachelor::pi,
      //                                          Daughters::pipi, 100, -1000,
      //                                          1000)),
      Bu2D0hst_mean1Bu_(nullptr),
      Bu2D0hst_mean2Bu_(nullptr),
      Bu2D0hst_sigma1Bu_(nullptr),
      Bu2D0hst_sigma2Bu_(nullptr),
      pdf1Bu_Bu2D0hst_(nullptr),
      pdf2Bu_Bu2D0hst_(nullptr),
      pdfBu_Bu2D0hst_(nullptr),
      Bu2D0hst_aDelta_(nullptr),
      pdfDelta_Bu2D0hst_(nullptr),
      Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_D0gamma_(nullptr),
      pdf2Bu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_(nullptr),
      Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_(nullptr),
      pdfBu_Bu2Dst0hst_(nullptr) {
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_WN<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .bkgFrac_Bu2Dst0h_D0gamma_WN()));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bd2Dsth()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(new RooFormulaVar(
            ("N_tot_Bu2Dst0h_D0gamma_WN_" +
             ComposeName(uniqueId, _neutral, Bachelor::pi, Daughters::pipi))
                .c_str(),
            "@0*@1*@2",
            RooArgList(
                *N_tot_Bu2Dst0h_D0pi0_WN_,
                NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                    .bkgFrac_Bu2Dst0h_D0gamma_WN(),
                NeutralVars<_neutral>::Get(uniqueId)
                    .bkgFloatingFrac_Bu2Dst0h_D0gamma_WN())));
    N_tot_Bu2Dst0h_WN_ =
        std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
            "N_tot_Bu2Dst0h_WN", uniqueId, _neutral, Bachelor::pi,
            Daughters::pipi,
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                    .N_tot_Bu2Dst0h_WN()
                    .getVal() *
                GlobalVars::Get(uniqueId).kBF_D02pipi().getVal() /
                GlobalVars::Get(uniqueId).kBF_D02kpi().getVal(),
            -1000000, 1000000));
    N_tot_Bd2Dsth_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::pipi>(
            uniqueId, "N_tot_Bd2Dsth_", *N_tot_Bu2Dst0h_D0pi0_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bd2Dsth()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  }
  // N_tot_Bu2D0hst_ = std::shared_ptr<RooFormulaVar>(
  //     Make_N_BkgFrac<_neutral, Bachelor::pi, Daughters::pipi>(
  //         uniqueId, "N_tot_Bu2D0hst_", *N_tot_Bd2Dsth_,
  //         NeutralVars<_neutral>::Get(uniqueId).bkgFracFAV_Bu2D0hst()));
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::kpi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(
          Params::Get().CreateFloating("A_Bu2Dst0h_D0pi0", uniqueId, _neutral,
                                       Bachelor::k, Daughters::kpi, 0, -1, 1)),
      A_Bu2Dst0h_WN_(Params::Get().CreateFixed(
          "A_Bu2Dst0h_WN", uniqueId, _neutral, Bachelor::k, Daughters::kpi, 0.,
          0.02, Systematic::A_K_Kpi_Bu2Dst0h_WN, Sign::none)),
      // Remove these -- share with signal?
      A_Bd2Dsth_(Params::Get().CreateFixed("A_Bd2Dsth", uniqueId, _neutral,
                                           Bachelor::k, Daughters::kpi, 0.0,
                                           0.0, Systematic::NA, Sign::none)),
      A_Bu2D0hst_(nullptr),
      A_Bu2D0hst_gaus_(nullptr),
      // A_Bu2D0hst_(Params::Get().CreateFixed(
      //     "A_Bu2D0hst", uniqueId, _neutral, Bachelor::k, Daughters::kpi, 0.0,
      //     0.009, Systematic::A_K_Kpi_Bu2D0hst, Sign::none)),
      // A_Bu2D0hst_(Params::Get().CreateFloating(
      //     "A_Bu2D0hst", uniqueId, _neutral, Bachelor::k, Daughters::kpi, 0.0,
      //     -1, 1)),
      A_Bu2Dst0hst_(nullptr),
      // A_Bu2Dst0hst_(Params::Get().CreateFixed(
      //     "A_Bu2Dst0hst", uniqueId, _neutral, Bachelor::k, Daughters::kpi, 0.0,
      //     0.02, Systematic::A_K_Kpi_Bu2Dst0hst, Sign::none)),
      // A_Bu2Dst0hst_(Params::Get().CreateFloating(
      //     "A_Bu2Dst0hst", uniqueId, _neutral, Bachelor::k, Daughters::kpi,
      //     0.0, -1, 1)),
      A_Lb2Omegach_Lcpi0_(nullptr),
      A_Bs2Dst0Kst0_(nullptr),
      A_Bs2D0Kst0_(nullptr),
      A_comb_(Params::Get().CreateFixed("A_comb", uniqueId, _neutral,
                                        Bachelor::k, Daughters::kpi, 0, 0.1,
                                        Systematic::Combinatorial, Sign::none)),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bu2Dst0h_WN_)),
      a_Bd2Dsth_(MakeLittleAsym(
          ("a_Bd2Dsth_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_Bd2Dsth_)),
      a_Bu2D0hst_(nullptr),
      a_Bu2Dst0hst_(nullptr),
      a_Lb2Omegach_Lcpi0_(nullptr),
      a_Bs2Dst0Kst0_(nullptr),
      a_Bs2D0Kst0_(nullptr),
      a_comb_(MakeLittleAsym(
          ("a_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          *A_comb_)),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          DaughtersVars<Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .orEffBu2Dst0h_D0pi0(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .orEffBu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0gamma(),
          DaughtersVars<Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0gamma(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0h_D0gamma(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .orEffBu2Dst0h_D0gamma(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .orEffBu2Dst0h_D0gamma())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_WN<_neutral, Bachelor::k, Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .bkgFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_WN_(nullptr),
      N_tot_Bd2Dsth_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          DaughtersVars<Daughters::kpi>::Get(uniqueId).R_Dst0KDst0pi_Bd2Dsth(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bd2Dsth(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bd2Dsth(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .orEffBd2Dsth(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .orEffBd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          DaughtersVars<Daughters::kpi>::Get(uniqueId).R_Dst0KDst0pi_Bu2D0hst(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2D0hst(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2D0hst(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .orEffBu2D0hst(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .orEffBu2D0hst())),
      N_tot_Bu2Dst0hst_(Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
          uniqueId, "N_tot_Bu2Dst0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0hst(),
          DaughtersVars<Daughters::kpi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0hst(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .mcEff_Bu2Dst0hst(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .mcEff_Bu2Dst0hst(),
          NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
              .orEffBu2Dst0hst(),
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .orEffBu2Dst0hst())),
      N_tot_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_tot_Lb2Omegach_Lcpi0_(nullptr),
      N_tot_Bs2Dst0Kst0_(nullptr),
      N_tot_Bs2D0Kst0_(nullptr),
      fracComb_(Params::Get().CreateFixed(
          "fracComb", uniqueId, _neutral, Bachelor::k, Daughters::kpi, 0.31,
          0.04, Systematic::Combinatorial, Sign::same)),
      // fracComb_(Params::Get().CreateFloating("fracComb", uniqueId, _neutral,
      //                                     Bachelor::k, Daughters::kpi, 0.31,
      //                                     -5, 5)),
      N_tot_comb_(new RooFormulaVar(
          ("N_tot_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
              .c_str(),
          "", "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                                  Daughters::kpi>::Get(uniqueId)
                         .N_tot_comb(),
                     *fracComb_))),
      // N_tot_comb_(Params::Get().CreateFloating("N_tot_comb", uniqueId,
      //                                          _neutral, Bachelor::k,
      //                                          Daughters::kpi, 100, -1000,
      //                                          10000)),
      Bu2D0hst_mean1Bu_(nullptr),
      Bu2D0hst_mean2Bu_(nullptr),
      Bu2D0hst_sigma1Bu_(nullptr),
      Bu2D0hst_sigma2Bu_(nullptr),
      pdf1Bu_Bu2D0hst_(nullptr),
      pdf2Bu_Bu2D0hst_(nullptr),
      pdfBu_Bu2D0hst_(nullptr),
      Bu2D0hst_aDelta_(nullptr),
      pdfDelta_Bu2D0hst_(nullptr),
      Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_D0gamma_(nullptr),
      pdf2Bu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_(nullptr),
      Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_(nullptr),
      pdfBu_Bu2Dst0hst_(nullptr) {
  if (_neutral == Neutral::gamma) {
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_Bu2Dst0h_D0gamma", uniqueId, _neutral,
                                     Bachelor::k, Daughters::kpi, 0, -1, 1));
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_WN<_neutral, Bachelor::k, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .bkgFrac_Bu2Dst0h_D0gamma_WN()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
    A_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "A_Bu2D0hst", uniqueId, _neutral, Bachelor::k, Daughters::kpi, 0.0,
        0.009, Systematic::A_K_Kpi_Bu2D0hst, Sign::none));
    A_Bu2Dst0hst_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_Bu2Dst0hst", uniqueId, _neutral,
                                     Bachelor::k, Daughters::kpi, 0, -1, 1));
  } else {
    A_Bu2Dst0h_D0gamma_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "A_Bu2Dst0h_D0gamma", uniqueId, _neutral, Bachelor::k, Daughters::kpi,
        ReadGammaObs(("A_Bu2Dst0h_D0gamma_" + EnumToString(Bachelor::k) + "_" +
                      EnumToString(Daughters::kpi))
                         .c_str(),
                     ReturnType::val),
        ReadGammaObs(("A_Bu2Dst0h_D0gamma_" + EnumToString(Bachelor::k) + "_" +
                      EnumToString(Daughters::kpi))
                         .c_str(),
                     ReturnType::stdL),
        ReadGammaObs(("A_Bu2Dst0h_D0gamma_" + EnumToString(Bachelor::k) + "_" +
                      EnumToString(Daughters::kpi))
                         .c_str(),
                     ReturnType::stdH),
        Systematic::A_K_Kpi_Bu2Dst0h_D0gamma, Sign::same));
    A_Bu2D0hst_ = std::shared_ptr<RooRealVar>(
        Params::Get().CreateFloating("A_Bu2D0hst", uniqueId, _neutral,
                                     Bachelor::k, Daughters::kpi, 0, -1, 1));
    // A_Bu2D0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
    //     "A_Bu2D0hst", uniqueId, _neutral, Bachelor::k, Daughters::kpi, 0.0,
    //     0.009, Systematic::A_K_Kpi_Bu2D0hst, Sign::none));
    // A_Bu2D0hst_gaus_ = std::shared_ptr<RooGaussian>(new RooGaussian(
    //     ("A_Bu2D0hst_gaus_" +
    //      ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
    //         .c_str(),
    //     "", *A_Bu2D0hst_, RooFit::RooConst(0.0), RooFit::RooConst(0.009)));
    // GlobalVars::Get(uniqueId).constraints_argSet().add(*A_Bu2D0hst_gaus_);
    A_Bu2Dst0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "A_Bu2Dst0hst", uniqueId, _neutral, Bachelor::k, Daughters::kpi, 0.0,
        0.02, Systematic::A_K_Kpi_Bu2Dst0hst, Sign::none));
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            DaughtersVars<Daughters::kpi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_D0gamma_WN(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .orEffBu2Dst0h_D0gamma_WN(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .orEffBu2Dst0h_D0gamma_WN()));
    N_tot_Bu2Dst0h_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_kpi<_neutral, Daughters::kpi>(
            uniqueId, "N_tot_Bu2Dst0h_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_WN(),
            DaughtersVars<Daughters::kpi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_WN(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .mcEff_Bu2Dst0h_WN(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .mcEff_Bu2Dst0h_WN(),
            NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                .orEffBu2Dst0h_WN(),
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .orEffBu2Dst0h_WN()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  }
  a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
      ("a_Bu2Dst0h_D0gamma_" +
       ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
          .c_str(),
      *A_Bu2Dst0h_D0gamma_));
  a_Bu2D0hst_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
      ("a_Bu2D0hst_" +
       ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
          .c_str(),
      *A_Bu2D0hst_));
  a_Bu2Dst0hst_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
      ("a_Bu2Dst0hst_" +
       ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kpi))
          .c_str(),
      *A_Bu2Dst0hst_));
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pik>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(nullptr),
      A_Bu2Dst0h_D0pi0_(nullptr),
      A_Bu2Dst0h_WN_(nullptr),
      // A_Bu2Dst0h_WN_(Params::Get().CreateFloating("A_Bu2Dst0h_WN", uniqueId,
      //                                             _neutral, Bachelor::k,
      //                                             Daughters::pik, 0, -1, 1)),
      A_Bd2Dsth_(Params::Get().CreateFixed("A_Bd2Dsth", uniqueId, _neutral,
                                           Bachelor::k, Daughters::pik, 0.0,
                                           0.0, Systematic::NA, Sign::none)),
      // HFLAV: A_ADS+, BF average of B+ and B0
      // 50% extra uncertainty for non-K* contributions
      A_Bu2D0hst_(Params::Get().CreateFixed(
          "A_Bu2D0hst", uniqueId, _neutral, Bachelor::k, Daughters::pik, -0.69,
          0.50, Systematic::A_K_piK_Bu2D0hst, Sign::none)),
      A_Bu2Dst0hst_(nullptr),
      A_Lb2Omegach_Lcpi0_(nullptr),
      A_Bs2Dst0Kst0_(Params::Get().CreateFixed(
          "A_Bs2Dst0Kst0", uniqueId, _neutral, Bachelor::k, Daughters::pik, 0,
          0, Systematic::NA, Sign::none)),
      A_Bs2D0Kst0_(Params::Get().CreateFixed("A_Bs2D0Kst0", uniqueId, _neutral,
                                             Bachelor::k, Daughters::pik, 0, 0,
                                             Systematic::NA, Sign::none)),
      A_comb_(Params::Get().CreateFixed("A_comb", uniqueId, _neutral,
                                        Bachelor::k, Daughters::pik, 0, 0.1,
                                        Systematic::Combinatorial, Sign::none)),
      a_Bu2Dst0h_D0gamma_(nullptr),
      a_Bu2Dst0h_D0pi0_(nullptr),
      a_Bu2Dst0h_WN_(nullptr),
      // a_Bu2Dst0h_WN_(MakeLittleAsym(
      //     ("a_Bu2Dst0h_WN_" +
      //      ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
      //         .c_str(),
      //     *A_Bu2Dst0h_WN_)),
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
      a_Bu2Dst0hst_(nullptr),
      a_Lb2Omegach_Lcpi0_(nullptr),
      a_Bs2Dst0Kst0_(MakeLittleAsym(
          ("a_Bs2Dst0Kst0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bs2Dst0Kst0_)),
      a_Bs2D0Kst0_(MakeLittleAsym(
          ("a_Bs2D0Kst0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_Bs2D0Kst0_)),
      a_comb_(MakeLittleAsym(
          ("a_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          *A_comb_)),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          BachelorVars<Bachelor::k>::Get(uniqueId).R_ADS_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0gamma(),
          BachelorVars<Bachelor::k>::Get(uniqueId).R_ADS_Bu2Dst0h_D0gamma())),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_WN<_neutral, Bachelor::k, Daughters::pik>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .bkgFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_tot_Bu2Dst0h_WN_(nullptr),
      N_tot_Bd2Dsth_(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          BachelorVars<Bachelor::k>::Get(uniqueId).R_ADS_Bd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          BachelorVars<Bachelor::k>::Get(uniqueId).R_ADS_Bu2D0hst())),
      N_tot_Bu2Dst0hst_(Make_N_tot_pik<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0hst(),
          BachelorVars<Bachelor::k>::Get(uniqueId).R_ADS_Bu2Dst0hst())),
      N_tot_Bu2Dst0h_D0gamma_D02pik_(Make_N_tot_FAVasSUP<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0h_D0gamma_D02pik_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0gamma())),
      N_tot_Bu2Dst0h_D0pi0_D02pik_(Make_N_tot_FAVasSUP<_neutral, Bachelor::k>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_D02pik_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                       Daughters::kpi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0pi0_WN_D02pik_(
          Make_N_tot_FAVasSUP<_neutral, Bachelor::k>(
              uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_D02pik_",
              NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                           Daughters::kpi>::Get(uniqueId)
                  .N_tot_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_tot_Lb2Omegach_Lcpi0_(nullptr),
      N_tot_Bs2Dst0Kst0_(nullptr),
      N_tot_Bs2D0Kst0_(nullptr),
      fracComb_(Params::Get().CreateFixed(
          "fracComb", uniqueId, _neutral, Bachelor::k, Daughters::pik, 2.00,
          0.22, Systematic::Combinatorial, Sign::same)),
      N_tot_comb_(new RooFormulaVar(
          ("N_tot_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
              .c_str(),
          "", "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                  Daughters::kpi>::Get(uniqueId)
                         .N_tot_comb(),
                     *fracComb_))),
      // N_tot_comb_(Params::Get().CreateFloating("N_tot_comb", uniqueId,
      // _neutral,
      //                                          Bachelor::k, Daughters::pik,
      //                                          100, 0, 10000)),
      Bu2D0hst_mean1Bu_(nullptr),
      Bu2D0hst_mean2Bu_(nullptr),
      Bu2D0hst_sigma1Bu_(nullptr),
      Bu2D0hst_sigma2Bu_(nullptr),
      pdf1Bu_Bu2D0hst_(nullptr),
      pdf2Bu_Bu2D0hst_(nullptr),
      pdfBu_Bu2D0hst_(nullptr),
      Bu2D0hst_aDelta_(nullptr),
      pdfDelta_Bu2D0hst_(nullptr),
      Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_D0gamma_(nullptr),
      pdf2Bu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_(nullptr),
      Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_(nullptr),
      pdfBu_Bu2Dst0hst_(nullptr) {
  if (Configuration::Get().splitByCharge() == true) {
    A_Bu2Dst0h_D0pi0_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
            uniqueId, "A_ADS_Bu2Dst0h_D0pi0_",
            BachelorChargeVars<Bachelor::k, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0(),
            BachelorChargeVars<Bachelor::k, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0pi0()));
    A_Bu2Dst0h_D0gamma_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
            uniqueId, "A_ADS_Bu2Dst0h_D0gamma_",
            BachelorChargeVars<Bachelor::k, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma(),
            BachelorChargeVars<Bachelor::k, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_D0gamma()));
    A_Bu2Dst0h_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
            uniqueId, "A_ADS_Bu2Dst0h_WN_",
            BachelorChargeVars<Bachelor::k, Charge::minus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_WN(),
            BachelorChargeVars<Bachelor::k, Charge::plus>::Get(uniqueId)
                .R_piK_Bu2Dst0h_WN()));
    // A_Bu2Dst0h_WN_ = std::shared_ptr<RooRealVar>(
    //     Params::Get().CreateFloating("A_Bu2Dst0h_WN", uniqueId, _neutral,
    //                                  Bachelor::k, Daughters::pik, 0, -1, 1));
    a_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0pi0_));
    a_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_D0gamma_));
    a_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0h_WN_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0h_WN_));
    // if (_neutral == Neutral::gamma) {
    // A_Bu2Dst0hst_ =
    //     std::shared_ptr<RooFormulaVar>(Make_A_ADS<_neutral, Bachelor::k>(
    //         uniqueId, "A_ADS_Bu2Dst0hst_",
    //         BachelorChargeVars<Bachelor::k, Charge::minus>::Get(uniqueId)
    //             .R_piK_Bu2Dst0hst(),
    //         BachelorChargeVars<Bachelor::k, Charge::plus>::Get(uniqueId)
    //             .R_piK_Bu2Dst0hst()));
    // } else {
    //   A_Bu2Dst0hst_ =
    //   std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
    //       "A_Bu2Dst0hst", uniqueId, _neutral, Bachelor::k, Daughters::pik,
    //       0.4, -1, 1));
    // }
    A_Bu2Dst0hst_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFixed(
        "A_ADS_Bu2Dst0hst", uniqueId, _neutral, Bachelor::k, Daughters::pik,
        0.0, 0.5, Systematic::A_K_piK_Bu2Dst0hst, Sign::none));
    a_Bu2Dst0hst_ = std::unique_ptr<RooFormulaVar>(MakeLittleAsym(
        ("a_Bu2Dst0hst_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pik))
            .c_str(),
        *A_Bu2Dst0hst_));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_WN<_neutral, Bachelor::k, Daughters::pik>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .bkgFrac_Bu2Dst0h_D0gamma_WN()));
    // N_tot_Bs2D0Kst0_ = std::shared_ptr<RooFormulaVar>(
    //     Make_N_BkgFrac<_neutral, Bachelor::k, Daughters::pik>(
    //         uniqueId, "N_tot_Bs2D0Kst0_", *N_tot_Bu2Dst0h_D0gamma_,
    //         NeutralVars<_neutral>::Get(uniqueId).bkgFracADS_Bs2D0Kst0()));
    N_tot_Bs2D0Kst0_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_Bs2D0Kst0", uniqueId, _neutral, Bachelor::k, Daughters::pik, 667,
        -1000, 10000));
    N_tot_Bs2Dst0Kst0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::k, Daughters::pik>(
            uniqueId, "N_tot_Bs2Dst0Kst0_", *N_tot_Bs2D0Kst0_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracADS_Bs2Dst0Kst0()));
    N_tot_Bu2Dst0h_D0gamma_WN_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_tot_FAVasSUP<_neutral, Bachelor::k>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_D02pik_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::k>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            BachelorVars<Bachelor::k>::Get(uniqueId).R_ADS_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_pik<_neutral, Bachelor::k>(
            uniqueId, "N_tot_Bu2Dst0h_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::kpi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_WN(),
            BachelorVars<Bachelor::k>::Get(uniqueId).R_ADS_Bu2Dst0h_WN()));
    // N_tot_Bs2D0Kst0_ = std::shared_ptr<RooFormulaVar>(
    //     Make_N_BkgFrac<_neutral, Bachelor::k, Daughters::pik>(
    //         uniqueId, "N_tot_Bs2D0Kst0_", *N_tot_Bu2Dst0h_D0pi0_,
    //         NeutralVars<_neutral>::Get(uniqueId).bkgFracADS_Bs2D0Kst0()));
    N_tot_Bs2D0Kst0_ = std::shared_ptr<RooRealVar>(Params::Get().CreateFloating(
        "N_tot_Bs2D0Kst0", uniqueId, _neutral, Bachelor::k, Daughters::pik, 80,
        -1000, 10000));
    N_tot_Bs2Dst0Kst0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_BkgFrac<_neutral, Bachelor::k, Daughters::pik>(
            uniqueId, "N_tot_Bs2Dst0Kst0_", *N_tot_Bs2D0Kst0_,
            NeutralVars<_neutral>::Get(uniqueId).bkgFracADS_Bs2Dst0Kst0()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::kk>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0gamma_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2Dst0h_D0gamma())),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2Dst0h_D0pi0())),
      A_Bu2Dst0h_WN_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2Dst0h_WN_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2Dst0h_WN())),
      A_Bd2Dsth_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bd2Dsth_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bd2Dsth())),
      A_Bu2D0hst_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2D0hst_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2D0hst())),
      A_Bu2Dst0hst_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Bu2Dst0hst_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2Dst0hst())),
      A_Lb2Omegach_Lcpi0_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "A_Lb2Omegach_Lcpi0_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Lb2Omegach_Lcpi0())),
      A_Bs2Dst0Kst0_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                  Daughters::pik>::Get(uniqueId)
                         .A_Bs2Dst0Kst0_GetPointer()),
      A_Bs2D0Kst0_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                Daughters::pik>::Get(uniqueId)
                       .A_Bs2D0Kst0_GetPointer()),
      A_comb_(Params::Get().CreateFixed("A_comb", uniqueId, _neutral,
                                        Bachelor::k, Daughters::kk, 0, 0.1,
                                        Systematic::Combinatorial, Sign::none)),
      a_Bu2Dst0h_D0gamma_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_)),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0h_WN_)),
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
      a_Bu2Dst0hst_(MakeLittleAsym(
          ("a_Bu2Dst0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bu2Dst0hst_)),
      a_Lb2Omegach_Lcpi0_(MakeLittleAsym(
          ("a_Lb2Omegach_Lcpi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Lb2Omegach_Lcpi0_)),
      a_Bs2Dst0Kst0_(MakeLittleAsym(
          ("a_Bs2Dst0Kst0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bs2Dst0Kst0_)),
      a_Bs2D0Kst0_(MakeLittleAsym(
          ("a_Bs2D0Kst0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_Bs2D0Kst0_)),
      a_comb_(MakeLittleAsym(
          ("a_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          *A_comb_)),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          DaughtersVars<Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0gamma(),
          DaughtersVars<Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma())),
      N_tot_Bu2Dst0h_D0pi0_WN_(Make_N_WN<_neutral, Bachelor::k, Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
          NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
              .bkgFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_tot_Bu2Dst0h_WN_(nullptr),
      N_tot_Bd2Dsth_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          DaughtersVars<Daughters::kk>::Get(uniqueId).R_Dst0KDst0pi_Bd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          DaughtersVars<Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0hst())),
      N_tot_Bu2Dst0hst_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Bu2Dst0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Bu2Dst0hst(),
          DaughtersVars<Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0hst())),
      N_tot_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_tot_Lb2Omegach_Lcpi0_(Make_N_tot_k_CP<_neutral, Daughters::kk>(
          uniqueId, "N_tot_Lb2Omegach_Lcpi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::kk>::Get(uniqueId)
              .N_tot_Lb2Omegach_Lcpi0(),
          DaughtersVars<Daughters::kk>::Get(uniqueId)
              .R_Dst0KDst0pi_Lb2Omegach_Lcpi0())),
      N_tot_Bs2Dst0Kst0_(nullptr),
      N_tot_Bs2D0Kst0_(nullptr),
      fracComb_(Params::Get().CreateFixed(
          "fracComb", uniqueId, _neutral, Bachelor::k, Daughters::kk, 1.27,
          0.21, Systematic::Combinatorial, Sign::same)),
      // fracComb_(Params::Get().CreateFloating("fracComb", uniqueId, _neutral,
      //                                     Bachelor::k, Daughters::kk, 1.27,
      //                                     -5, 5)),
      N_tot_comb_(new RooFormulaVar(
          ("N_tot_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::kk))
              .c_str(),
          "", "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                  Daughters::kpi>::Get(uniqueId)
                         .N_tot_comb(),
                     *fracComb_))),
      // N_tot_comb_(Params::Get().CreateFloating("N_tot_comb", uniqueId,
      //                                          _neutral, Bachelor::k,
      //                                          Daughters::kk, 100, -1000,
      //                                          1000)),
      Bu2D0hst_mean1Bu_(nullptr),
      Bu2D0hst_mean2Bu_(nullptr),
      Bu2D0hst_sigma1Bu_(nullptr),
      Bu2D0hst_sigma2Bu_(nullptr),
      pdf1Bu_Bu2D0hst_(nullptr),
      pdf2Bu_Bu2D0hst_(nullptr),
      pdfBu_Bu2D0hst_(nullptr),
      Bu2D0hst_aDelta_(nullptr),
      pdfDelta_Bu2D0hst_(nullptr),
      Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_D0gamma_(nullptr),
      pdf2Bu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_(nullptr),
      Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_(nullptr),
      pdfBu_Bu2Dst0hst_(nullptr) {
  if (Configuration::Get().runADS() == true) {
    N_tot_Bs2Dst0Kst0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "N_tot_Bs2Dst0Kst0_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2Dst0Kst0()));
    N_tot_Bs2D0Kst0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "N_tot_Bs2D0Kst0_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2D0Kst0()));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_WN<_neutral, Bachelor::k, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .bkgFrac_Bu2Dst0h_D0gamma_WN()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_k_CP<_neutral, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kk>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            DaughtersVars<Daughters::kk>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_WN_ =
        std::shared_ptr<RooFormulaVar>(Make_N_tot_k_CP<_neutral, Daughters::kk>(
            uniqueId, "N_tot_Bu2Dst0h_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::kk>::Get(uniqueId)
                .N_tot_Bu2Dst0h_WN(),
            DaughtersVars<Daughters::kk>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_WN()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  }
}

template <Neutral _neutral>
NeutralBachelorDaughtersVarsImpl<_neutral, Bachelor::k, Daughters::pipi>::
    NeutralBachelorDaughtersVarsImpl(int uniqueId)
    : A_Bu2Dst0h_D0gamma_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0gamma_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2Dst0h_D0gamma())),
      A_Bu2Dst0h_D0pi0_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_D0pi0_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2Dst0h_D0pi0())),
      A_Bu2Dst0h_WN_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0h_WN_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2Dst0h_WN())),
      A_Bd2Dsth_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bd2Dsth_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bd2Dsth())),
      A_Bu2D0hst_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2D0hst_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2D0hst())),
      A_Bu2Dst0hst_(Make_A_D2CP<_neutral, Bachelor::k, Daughters::pipi>(
          uniqueId, "A_Bu2Dst0hst_",
          BachelorVars<Bachelor::k>::Get(uniqueId).A_CP_Bu2Dst0hst())),
      A_Lb2Omegach_Lcpi0_(nullptr),
      A_Bs2Dst0Kst0_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                  Daughters::pik>::Get(uniqueId)
                         .A_Bs2Dst0Kst0_GetPointer()),
      A_Bs2D0Kst0_(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                Daughters::pik>::Get(uniqueId)
                       .A_Bs2D0Kst0_GetPointer()),
      A_comb_(Params::Get().CreateFixed("A_comb", uniqueId, _neutral,
                                        Bachelor::k, Daughters::pipi, 0, 0.1,
                                        Systematic::Combinatorial, Sign::none)),
      a_Bu2Dst0h_D0gamma_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0gamma_)),
      a_Bu2Dst0h_D0pi0_(MakeLittleAsym(
          ("a_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_D0pi0_)),
      a_Bu2Dst0h_WN_(MakeLittleAsym(
          ("a_Bu2Dst0h_WN_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0h_WN_)),
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
      a_Bu2Dst0hst_(MakeLittleAsym(
          ("a_Bu2Dst0hst_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bu2Dst0hst_)),
      a_Lb2Omegach_Lcpi0_(nullptr),
      a_Bs2Dst0Kst0_(MakeLittleAsym(
          ("a_Bs2Dst0Kst0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bs2Dst0Kst0_)),
      a_Bs2D0Kst0_(MakeLittleAsym(
          ("a_Bs2D0Kst0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_Bs2D0Kst0_)),
      a_comb_(MakeLittleAsym(
          ("a_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          *A_comb_)),
      N_tot_Bu2Dst0h_D0pi0_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          DaughtersVars<Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0pi0())),
      N_tot_Bu2Dst0h_D0gamma_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2Dst0h_D0gamma_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2Dst0h_D0gamma(),
          DaughtersVars<Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0h_D0gamma())),
      N_tot_Bu2Dst0h_D0pi0_WN_(
          Make_N_WN<_neutral, Bachelor::k, Daughters::pipi>(
              uniqueId, "N_tot_Bu2Dst0h_D0pi0_WN_", *N_tot_Bu2Dst0h_D0pi0_,
              NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .bkgFrac_Bu2Dst0h_D0pi0_WN())),
      N_tot_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_tot_Bu2Dst0h_WN_(nullptr),
      N_tot_Bd2Dsth_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bd2Dsth_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bd2Dsth(),
          DaughtersVars<Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bd2Dsth())),
      N_tot_Bu2D0hst_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2D0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2D0hst(),
          DaughtersVars<Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2D0hst())),
      N_tot_Bu2Dst0hst_(Make_N_tot_k_CP<_neutral, Daughters::pipi>(
          uniqueId, "N_tot_Bu2Dst0hst_",
          NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                       Daughters::pipi>::Get(uniqueId)
              .N_tot_Bu2Dst0hst(),
          DaughtersVars<Daughters::pipi>::Get(uniqueId)
              .R_Dst0KDst0pi_Bu2Dst0hst())),
      N_tot_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_tot_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_tot_Lb2Omegach_Lcpi0_(nullptr),
      N_tot_Bs2Dst0Kst0_(nullptr),
      N_tot_Bs2D0Kst0_(nullptr),
      fracComb_(Params::Get().CreateFixed(
          "fracComb", uniqueId, _neutral, Bachelor::k, Daughters::pipi, 0.95,
          0.11, Systematic::Combinatorial, Sign::same)),
      // fracComb_(Params::Get().CreateFloating("fracComb", uniqueId, _neutral,
      //                                     Bachelor::k, Daughters::pipi, 0.95,
      //                                     -5, 5)),
      N_tot_comb_(new RooFormulaVar(
          ("N_tot_comb_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, Daughters::pipi))
              .c_str(),
          "", "@0*@1",
          RooArgList(NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                                  Daughters::kpi>::Get(uniqueId)
                         .N_tot_comb(),
                     *fracComb_))),
      // N_tot_comb_(Params::Get().CreateFloating("N_tot_comb", uniqueId,
      //                                          _neutral, Bachelor::k,
      //                                          Daughters::pipi, 50, -1000,
      //                                          1000)),
      Bu2D0hst_mean1Bu_(nullptr),
      Bu2D0hst_mean2Bu_(nullptr),
      Bu2D0hst_sigma1Bu_(nullptr),
      Bu2D0hst_sigma2Bu_(nullptr),
      pdf1Bu_Bu2D0hst_(nullptr),
      pdf2Bu_Bu2D0hst_(nullptr),
      pdfBu_Bu2D0hst_(nullptr),
      Bu2D0hst_aDelta_(nullptr),
      pdfDelta_Bu2D0hst_(nullptr),
      Bu2Dst0hst_D0gamma_mean1Bu_(nullptr),
      Bu2Dst0hst_D0gamma_mean2Bu_(nullptr),
      pdf1Bu_Bu2Dst0hst_D0gamma_(nullptr),
      pdf2Bu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_D0gamma_fracPdf1Bu_(nullptr),
      pdfBu_Bu2Dst0hst_D0gamma_(nullptr),
      Bu2Dst0hst_floatingFracD0pi0_Bu_FAV_ADS_(nullptr),
      Bu2Dst0hst_fracD0pi0_Bu_FAV_ADS_(nullptr),
      pdfBu_Bu2Dst0hst_(nullptr) {
  if (Configuration::Get().runADS() == true) {
    N_tot_Bs2Dst0Kst0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "N_tot_Bs2Dst0Kst0_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2Dst0Kst0()));
    N_tot_Bs2D0Kst0_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_Bs_CP<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "N_tot_Bs2D0Kst0_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::k,
                                         Daughters::pik>::Get(uniqueId)
                .N_tot_Bs2D0Kst0()));
  }
  if (_neutral == Neutral::gamma) {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_WN<_neutral, Bachelor::k, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_", *N_tot_Bu2Dst0h_D0gamma_,
            NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                .bkgFrac_Bu2Dst0h_D0gamma_WN()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
  } else {
    N_tot_Bu2Dst0h_D0gamma_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_CP<_neutral, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_D0gamma_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_D0gamma_WN(),
            DaughtersVars<Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_D0gamma()));
    N_tot_Bu2Dst0h_WN_ = std::shared_ptr<RooFormulaVar>(
        Make_N_tot_k_CP<_neutral, Daughters::pipi>(
            uniqueId, "N_tot_Bu2Dst0h_WN_",
            NeutralBachelorDaughtersVars<_neutral, Bachelor::pi,
                                         Daughters::pipi>::Get(uniqueId)
                .N_tot_Bu2Dst0h_WN(),
            DaughtersVars<Daughters::pipi>::Get(uniqueId)
                .R_Dst0KDst0pi_Bu2Dst0h_WN()));
    pdfBu_Bu2D0hst_ = NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                          .pdfBu_Bu2D0hst_GetPointer();
    pdfDelta_Bu2D0hst_ =
        NeutralVars<_neutral>::Get(uniqueId).pdfDelta_Bu2D0hst_GetPointer();
    pdfBu_Bu2Dst0hst_ =
        NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
            .pdfBu_Bu2Dst0hst_GetPointer();
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
