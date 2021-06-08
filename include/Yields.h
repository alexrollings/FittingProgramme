#pragma once
#include "Configuration.h"
#include "NeutralBachelorDaughtersVars.h"

// Return yield with correct asymmetry definition
template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *Make_N_split(int uniqueId, const char *nameStr,
                            RooAbsReal &N_tot, RooFormulaVar &a_RAW) {
  switch (charge) {
    case Charge::plus:
      switch (daughters) {
        case Daughters::kpi:
          // Want to do all the NAMING with the reconstructed bachelor (category
          // mis ID ends up in), but the physics formulae for the asymmetry
          // depend on the TRUE bachelor of the mode
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3*@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::kk:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::pipi:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::pik:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2/@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
      }
      break;
    case Charge::minus:
      switch (daughters) {
        case Daughters::kpi:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3*@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::kk:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::pipi:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::pik:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2/@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             NeutralVars<neutral>::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
      }
      break;
    case Charge::total:
      return new RooFormulaVar(
          (nameStr +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "@0", RooArgList(N_tot));
      break;
  }
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *Make_N_trueId(int uniqueId, const char *nameStr,
                             RooAbsReal &N_split) {
  return new RooFormulaVar(
      (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
          .c_str(),
      "@0*@1",
      RooArgList(N_split, *GlobalVars::Get(uniqueId).pidEffMap()[MakePidKey(
                              bachelor, Charge::total)]));
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *Make_N_misId(int uniqueId, const char *nameStr,
                            RooAbsReal &N_split, RooAbsReal &mcEff_misId,
                            RooAbsReal &mcEff_trueId, RooAbsReal &orEff_misId,
                            RooAbsReal &orEff_trueId) {
  switch (bachelor) {
    case Bachelor::pi:
      return new RooFormulaVar(
          (nameStr +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              // misID components are generally shifted out of the box region,
              // so the yields need to be corrected by the or efficiencies
              .c_str(),
          "(@0*(1-@5))*(@1/@2)*(@3/@4)",
          RooArgList(
              N_split, mcEff_misId, mcEff_trueId, orEff_misId, orEff_trueId,
              *GlobalVars::Get(uniqueId)
                   .pidEffMap()[MakePidKey(Bachelor::k, Charge::total)]));
      break;
    case Bachelor::k:
      return new RooFormulaVar(
          (nameStr +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "(@0*(1-@5))*(@1/@2)*(@3/@4)",
          RooArgList(
              N_split, mcEff_misId, mcEff_trueId, orEff_misId, orEff_trueId,
              *GlobalVars::Get(uniqueId)
                   .pidEffMap()[MakePidKey(Bachelor::pi, Charge::total)]));
      break;
  }
}

// To calculate 1D yields, for D1D fit, multiply total events by corresponding
// cut efficiency, and PID eff
template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *Make_N_1D(int uniqueId, const char *nameStr, RooAbsReal &N_id,
                         RooAbsReal &cutEff) {
  if (Configuration::Get().fit1D() == true &&
      Configuration::Get().fitBuPartial() == false) {
    // 1D fit doesn't get multiplied by any efficiency
    return new RooFormulaVar(
        (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "@0", RooArgList(N_id));
  } else {
    return new RooFormulaVar(
        (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "@0*@1", RooArgList(N_id, cutEff));
  }
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>

class Yields {
 public:
  Yields(int uniqueId);
  ~Yields() {}

  using This_t = Yields<neutral, bachelor, daughters, charge>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  int uniqueId() { return uniqueId_; }

  RooFormulaVar &N_split_Bu2Dst0h_D0gamma() {
    return *N_split_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_split_Bu2Dst0h_D0pi0() { return *N_split_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_split_Bu2Dst0h_D0gamma_WN() {
    return *N_split_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &N_split_Bu2Dst0h_D0pi0_WN() {
    return *N_split_Bu2Dst0h_D0pi0_WN_;
  }
  RooFormulaVar &N_split_Bu2Dst0h_WN() { return *N_split_Bu2Dst0h_WN_; }
  RooFormulaVar &N_split_Bd2Dsth() { return *N_split_Bd2Dsth_; }
  RooFormulaVar &N_split_Bu2D0hst() { return *N_split_Bu2D0hst_; }
  RooFormulaVar &N_split_Bu2Dst0hst() { return *N_split_Bu2Dst0hst_; }
  RooFormulaVar &N_split_Lb2Omegach_Lcpi0() {
    return *N_split_Lb2Omegach_Lcpi0_;
  }
  RooFormulaVar &N_split_Bs2Dst0Kst0() { return *N_split_Bs2Dst0Kst0_; }
  RooFormulaVar &N_split_Bs2D0Kst0() { return *N_split_Bs2D0Kst0_; }
  RooFormulaVar &N_split_Bu2Dst0h_D0pi0_D02pik() {
    return *N_split_Bu2Dst0h_D0pi0_D02pik_;
  }
  RooFormulaVar &N_split_Bu2Dst0h_D0gamma_D02pik() {
    return *N_split_Bu2Dst0h_D0gamma_D02pik_;
  }
  RooFormulaVar &N_split_Bu2Dst0h_D0pi0_WN_D02pik() {
    return *N_split_Bu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooFormulaVar &N_split_Bu2Dst0h_D0gamma_WN_D02pik() {
    return *N_split_Bu2Dst0h_D0gamma_WN_D02pik_;
  }

  RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma() {
    return *N_trueId_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0() { return *N_trueId_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_WN() {
    return *N_trueId_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_WN() {
    return *N_trueId_Bu2Dst0h_D0pi0_WN_;
  }
  RooFormulaVar &N_trueId_Bu2Dst0h_WN() { return *N_trueId_Bu2Dst0h_WN_; }
  RooFormulaVar &N_trueId_Bd2Dsth() { return *N_trueId_Bd2Dsth_; }
  RooFormulaVar &N_trueId_Bu2D0hst() { return *N_trueId_Bu2D0hst_; }
  RooFormulaVar &N_trueId_Bu2Dst0hst() { return *N_trueId_Bu2Dst0hst_; }
  RooFormulaVar &N_trueId_Lb2Omegach_Lcpi0() {
    return *N_trueId_Lb2Omegach_Lcpi0_;
  }
  RooFormulaVar &N_trueId_Bs2Dst0Kst0() { return *N_trueId_Bs2Dst0Kst0_; }
  RooFormulaVar &N_trueId_Bs2D0Kst0() { return *N_trueId_Bs2D0Kst0_; }
  RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_D02pik() {
    return *N_trueId_Bu2Dst0h_D0pi0_D02pik_;
  }
  RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_D02pik() {
    return *N_trueId_Bu2Dst0h_D0gamma_D02pik_;
  }
  RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_WN_D02pik() {
    return *N_trueId_Bu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_WN_D02pik() {
    return *N_trueId_Bu2Dst0h_D0gamma_WN_D02pik_;
  }
  RooRealVar &N_trueId_comb() {
    return N_trueId_comb_;
  }

  RooFormulaVar &N_misId_Bu2Dst0h_D0gamma() {
    return *N_misId_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_misId_Bu2Dst0h_D0pi0() { return *N_misId_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_misId_Bu2Dst0h_D0gamma_WN() {
    return *N_misId_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &N_misId_Bu2Dst0h_D0pi0_WN() {
    return *N_misId_Bu2Dst0h_D0pi0_WN_;
  }
  RooFormulaVar &N_misId_Bu2Dst0h_WN() { return *N_misId_Bu2Dst0h_WN_; }
  RooFormulaVar &N_misId_Bd2Dsth() { return *N_misId_Bd2Dsth_; }
  RooFormulaVar &N_misId_Bu2D0hst() { return *N_misId_Bu2D0hst_; }
  RooFormulaVar &N_misId_Bu2Dst0hst() { return *N_misId_Bu2Dst0hst_; }

  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma() {
    return *N_trueId_Delta_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0() {
    return *N_trueId_Delta_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_WN() {
    return *N_trueId_Delta_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_WN() {
    return *N_trueId_Delta_Bu2Dst0h_D0pi0_WN_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_WN() {
    return *N_trueId_Delta_Bu2Dst0h_WN_;
  }
  RooFormulaVar &N_trueId_Delta_Bd2Dsth() { return *N_trueId_Delta_Bd2Dsth_; }
  RooFormulaVar &N_trueId_Delta_Bu2D0hst() { return *N_trueId_Delta_Bu2D0hst_; }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0hst() {
    return *N_trueId_Delta_Bu2Dst0hst_;
  }
  RooFormulaVar &N_trueId_Delta_Lb2Omegach_Lcpi0() {
    return *N_trueId_Delta_Lb2Omegach_Lcpi0_;
  }
  RooFormulaVar &N_trueId_Delta_Bs2Dst0Kst0() {
    return *N_trueId_Delta_Bs2Dst0Kst0_;
  }
  RooFormulaVar &N_trueId_Delta_Bs2D0Kst0() {
    return *N_trueId_Delta_Bs2D0Kst0_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik() {
    return *N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik() {
    return *N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik() {
    return *N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik() {
    return *N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik_;
  }
  RooFormulaVar &N_trueId_Delta_comb() {
    return *N_trueId_Delta_comb_;
  }

  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma() {
    return *N_trueId_Bu_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0() {
    return *N_trueId_Bu_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_WN() {
    return *N_trueId_Bu_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_WN() {
    return *N_trueId_Bu_Bu2Dst0h_D0pi0_WN_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_WN() { return *N_trueId_Bu_Bu2Dst0h_WN_; }
  RooFormulaVar &N_trueId_Bu_Bd2Dsth() { return *N_trueId_Bu_Bd2Dsth_; }
  RooFormulaVar &N_trueId_Bu_Bu2D0hst() { return *N_trueId_Bu_Bu2D0hst_; }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0hst() { return *N_trueId_Bu_Bu2Dst0hst_; }
  RooFormulaVar &N_trueId_Bu_Lb2Omegach_Lcpi0() {
    return *N_trueId_Bu_Lb2Omegach_Lcpi0_;
  }
  RooFormulaVar &N_trueId_Bu_Bs2Dst0Kst0() { return *N_trueId_Bu_Bs2Dst0Kst0_; }
  RooFormulaVar &N_trueId_Bu_Bs2D0Kst0() { return *N_trueId_Bu_Bs2D0Kst0_; }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik() {
    return *N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik() {
    return *N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik() {
    return *N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik() {
    return *N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik_;
  }
  RooFormulaVar &N_trueId_Bu_comb() {
    return *N_trueId_Bu_comb_;
  }

  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0gamma() {
    return *N_trueId_BuPartial_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0() {
    return *N_trueId_BuPartial_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN() {
    return *N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN() {
    return *N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bd2Dsth() {
    return *N_trueId_BuPartial_Bd2Dsth_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2D0hst() {
    return *N_trueId_BuPartial_Bu2D0hst_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0hst() {
    return *N_trueId_BuPartial_Bu2Dst0hst_;
  }
  RooFormulaVar &N_trueId_BuPartial_Lb2Omegach_Lcpi0() {
    return *N_trueId_BuPartial_Lb2Omegach_Lcpi0_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bs2Dst0Kst0() {
    return *N_trueId_BuPartial_Bs2Dst0Kst0_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bs2D0Kst0() {
    return *N_trueId_BuPartial_Bs2D0Kst0_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik() {
    return *N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik() {
    return *N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik_;
  }
  RooFormulaVar &N_trueId_BuPartial_comb() {
    return *N_trueId_BuPartial_comb_;
  }

  RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0gamma() {
    return *N_misId_Delta_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0pi0() {
    return *N_misId_Delta_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0gamma_WN() {
    return *N_misId_Delta_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &N_misId_Delta_Bu2Dst0h_D0pi0_WN() {
    return *N_misId_Delta_Bu2Dst0h_D0pi0_WN_;
  }
  RooFormulaVar &N_misId_Delta_Bu2Dst0h_WN() {
    return *N_misId_Delta_Bu2Dst0h_WN_;
  }
  RooFormulaVar &N_misId_Delta_Bd2Dsth() { return *N_misId_Delta_Bd2Dsth_; }
  RooFormulaVar &N_misId_Delta_Bu2D0hst() { return *N_misId_Delta_Bu2D0hst_; }
  RooFormulaVar &N_misId_Delta_Bu2Dst0hst() {
    return *N_misId_Delta_Bu2Dst0hst_;
  }

  RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0pi0() {
    return *N_misId_Bu_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0gamma_WN() {
    return *N_misId_Bu_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0pi0_WN() {
    return *N_misId_Bu_Bu2Dst0h_D0pi0_WN_;
  }
  RooFormulaVar &N_misId_Bu_Bu2Dst0h_WN() { return *N_misId_Bu_Bu2Dst0h_WN_; }
  RooFormulaVar &N_misId_Bu_Bd2Dsth() { return *N_misId_Bu_Bd2Dsth_; }
  RooFormulaVar &N_misId_Bu_Bu2D0hst() { return *N_misId_Bu_Bu2D0hst_; }
  RooFormulaVar &N_misId_Bu_Bu2Dst0hst() { return *N_misId_Bu_Bu2Dst0hst_; }
  RooFormulaVar &N_misId_Bu_Bu2Dst0h_D0gamma() {
    return *N_misId_Bu_Bu2Dst0h_D0gamma_;
  }

  RooFormulaVar &N_misId_BuPartial_Bu2Dst0h_D0pi0() {
    return *N_misId_BuPartial_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_misId_BuPartial_Bu2Dst0h_D0gamma_WN() {
    return *N_misId_BuPartial_Bu2Dst0h_D0gamma_WN_;
  }
  RooFormulaVar &N_misId_BuPartial_Bu2Dst0h_D0pi0_WN() {
    return *N_misId_BuPartial_Bu2Dst0h_D0pi0_WN_;
  }
  RooFormulaVar &N_misId_BuPartial_Bd2Dsth() {
    return *N_misId_BuPartial_Bd2Dsth_;
  }
  RooFormulaVar &N_misId_BuPartial_Bu2D0hst() {
    return *N_misId_BuPartial_Bu2D0hst_;
  }
  RooFormulaVar &N_misId_BuPartial_Bu2Dst0hst() {
    return *N_misId_BuPartial_Bu2Dst0hst_;
  }

  void AssignMisIdYields();

 private:
  int uniqueId_;

  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> N_split_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_split_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> N_split_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> N_split_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0gamma_WN_D02pik_;

  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_trueId_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0gamma_WN_D02pik_;
  RooRealVar N_trueId_comb_;

  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_comb_;

  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_comb_;

  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0hst_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Lb2Omegach_Lcpi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bs2Dst0Kst0_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bs2D0Kst0_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_comb_;

  std::unique_ptr<RooFormulaVar> N_misId_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu2Dst0hst_;

  std::unique_ptr<RooFormulaVar> N_misId_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_misId_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_misId_Delta_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_Delta_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_Delta_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_Delta_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> N_misId_Delta_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> N_misId_Delta_Bu2Dst0hst_;

  std::unique_ptr<RooFormulaVar> N_misId_Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu_Bu2Dst0h_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> N_misId_Bu_Bu2Dst0hst_;

  std::unique_ptr<RooFormulaVar> N_misId_BuPartial_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_misId_BuPartial_Bu2Dst0h_D0gamma_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_BuPartial_Bu2Dst0h_D0pi0_WN_;
  std::unique_ptr<RooFormulaVar> N_misId_BuPartial_Bd2Dsth_;
  std::unique_ptr<RooFormulaVar> N_misId_BuPartial_Bu2D0hst_;
  std::unique_ptr<RooFormulaVar> N_misId_BuPartial_Bu2Dst0hst_;
};

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
Yields<neutral, bachelor, daughters, charge>::Yields(int uniqueId)
    : uniqueId_(uniqueId),
      N_split_Bu2Dst0h_D0gamma_(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0gamma_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0gamma(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .a_Bu2Dst0h_D0gamma())),
      N_split_Bu2Dst0h_D0pi0_(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0pi0_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0pi0(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .a_Bu2Dst0h_D0pi0())),
      N_split_Bu2Dst0h_D0gamma_WN_(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0gamma_WN_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0gamma_WN(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .a_Bu2Dst0h_D0gamma())),
      N_split_Bu2Dst0h_D0pi0_WN_(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0pi0_WN_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0pi0_WN(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .a_Bu2Dst0h_D0pi0())),
      N_split_Bu2Dst0h_WN_(nullptr),
      N_split_Bd2Dsth_(Make_N_split<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_split_Bd2Dsth_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .N_tot_Bd2Dsth(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .a_Bd2Dsth())),
      N_split_Bu2D0hst_(Make_N_split<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_split_Bu2D0hst_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .N_tot_Bu2D0hst(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .a_Bu2D0hst())),
      N_split_Bu2Dst0hst_(Make_N_split<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_split_Bu2Dst0hst_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .N_tot_Bu2Dst0hst(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .a_Bu2Dst0hst())),
      N_split_Lb2Omegach_Lcpi0_(nullptr),
      N_split_Bs2Dst0Kst0_(nullptr),
      N_split_Bs2D0Kst0_(nullptr),
      N_split_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_split_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_split_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_split_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_trueId_Bu2Dst0h_D0gamma_(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0gamma_",
              *N_split_Bu2Dst0h_D0gamma_)),
      N_trueId_Bu2Dst0h_D0pi0_(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0pi0_", *N_split_Bu2Dst0h_D0pi0_)),
      N_trueId_Bu2Dst0h_D0gamma_WN_(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0gamma_WN_",
              *N_split_Bu2Dst0h_D0gamma_WN_)),
      N_trueId_Bu2Dst0h_D0pi0_WN_(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0pi0_WN_",
              *N_split_Bu2Dst0h_D0pi0_WN_)),
      N_trueId_Bu2Dst0h_WN_(nullptr),
      N_trueId_Bd2Dsth_(Make_N_trueId<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bd2Dsth_", *N_split_Bd2Dsth_)),
      N_trueId_Bu2D0hst_(Make_N_trueId<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu2D0hst_", *N_split_Bu2D0hst_)),
      N_trueId_Bu2Dst0hst_(Make_N_trueId<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu2Dst0hst_", *N_split_Bu2Dst0hst_)),
      N_trueId_Lb2Omegach_Lcpi0_(nullptr),
      N_trueId_Bs2Dst0Kst0_(nullptr),
      N_trueId_Bs2D0Kst0_(nullptr),
      N_trueId_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_trueId_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_trueId_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_trueId_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_trueId_comb_(
          ("N_trueId_comb_" +
           ComposeName(uniqueId_, neutral, bachelor, daughters, charge))
              .c_str(),
          "", 100, -1000, 1000),
      N_trueId_Delta_Bu2Dst0h_D0gamma_(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0gamma_",
              *N_trueId_Bu2Dst0h_D0gamma_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .deltaEffBu2Dst0h_D0gamma())),
      N_trueId_Delta_Bu2Dst0h_D0pi0_(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0pi0_",
              *N_trueId_Bu2Dst0h_D0pi0_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .deltaEffBu2Dst0h_D0pi0())),
      N_trueId_Delta_Bu2Dst0h_D0gamma_WN_(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0gamma_WN_",
              *N_trueId_Bu2Dst0h_D0gamma_WN_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .deltaEffBu2Dst0h_D0gamma_WN())),
      N_trueId_Delta_Bu2Dst0h_D0pi0_WN_(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0pi0_WN_",
              *N_trueId_Bu2Dst0h_D0pi0_WN_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .deltaEffBu2Dst0h_D0pi0_WN())),
      N_trueId_Delta_Bu2Dst0h_WN_(nullptr),
      N_trueId_Delta_Bd2Dsth_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Delta_Bd2Dsth_", *N_trueId_Bd2Dsth_,
          NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
              .deltaEffBd2Dsth())),
      N_trueId_Delta_Bu2D0hst_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Delta_Bu2D0hst_", *N_trueId_Bu2D0hst_,
          NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
              .deltaEffBu2D0hst())),
      N_trueId_Delta_Bu2Dst0hst_(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Delta_Bu2Dst0hst_", *N_trueId_Bu2Dst0hst_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .deltaEffBu2Dst0hst())),
      N_trueId_Delta_Lb2Omegach_Lcpi0_(nullptr),
      N_trueId_Delta_Bs2Dst0Kst0_(nullptr),
      N_trueId_Delta_Bs2D0Kst0_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_trueId_Delta_comb_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Delta_comb_", N_trueId_comb_,
          NeutralVars<neutral>::Get(uniqueId_).deltaEff_comb())),
      N_trueId_Bu_Bu2Dst0h_D0gamma_(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0gamma_",
              *N_trueId_Bu2Dst0h_D0gamma_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .buEffBu2Dst0h_D0gamma())),
      N_trueId_Bu_Bu2Dst0h_D0pi0_(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0pi0_",
              *N_trueId_Bu2Dst0h_D0pi0_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .buEffBu2Dst0h_D0pi0())),
      N_trueId_Bu_Bu2Dst0h_D0gamma_WN_(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0gamma_WN_",
              *N_trueId_Bu2Dst0h_D0gamma_WN_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .buEffBu2Dst0h_D0gamma_WN())),
      N_trueId_Bu_Bu2Dst0h_D0pi0_WN_(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0pi0_WN_",
              *N_trueId_Bu2Dst0h_D0pi0_WN_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .buEffBu2Dst0h_D0pi0_WN())),
      N_trueId_Bu_Bu2Dst0h_WN_(nullptr),
      N_trueId_Bu_Bd2Dsth_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_Bd2Dsth_", *N_trueId_Bd2Dsth_,
          NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
              .buEffBd2Dsth())),
      N_trueId_Bu_Bu2D0hst_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_Bu2D0hst_", *N_trueId_Bu2D0hst_,
          NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
              .buEffBu2D0hst())),
      N_trueId_Bu_Bu2Dst0hst_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_Bu2Dst0hst_", *N_trueId_Bu2Dst0hst_,
          NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
              .buEffBu2Dst0hst())),
      N_trueId_Bu_Lb2Omegach_Lcpi0_(nullptr),
      N_trueId_Bu_Bs2Dst0Kst0_(nullptr),
      N_trueId_Bu_Bs2D0Kst0_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik_(nullptr),
      N_trueId_Bu_comb_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_comb_", N_trueId_comb_,
          NeutralVars<neutral>::Get(uniqueId_).buEff_comb())),
      N_trueId_BuPartial_Bu2Dst0h_D0gamma_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_(nullptr),
      N_trueId_BuPartial_Bd2Dsth_(nullptr),
      N_trueId_BuPartial_Bu2D0hst_(nullptr),
      N_trueId_BuPartial_Bu2Dst0hst_(nullptr),
      N_trueId_BuPartial_Lb2Omegach_Lcpi0_(nullptr),
      N_trueId_BuPartial_Bs2Dst0Kst0_(nullptr),
      N_trueId_BuPartial_Bs2D0Kst0_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik_(nullptr),
      N_trueId_BuPartial_comb_(nullptr),
      N_misId_Bu2Dst0h_D0gamma_(nullptr),
      N_misId_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_misId_Bu2Dst0h_D0pi0_WN_(nullptr),
      N_misId_Bu2Dst0h_WN_(nullptr),
      N_misId_Bd2Dsth_(nullptr),
      N_misId_Bu2D0hst_(nullptr),
      N_misId_Bu2Dst0hst_(nullptr),
      N_misId_Delta_Bu2Dst0h_D0gamma_(nullptr),
      N_misId_Delta_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_Delta_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_misId_Delta_Bu2Dst0h_D0pi0_WN_(nullptr),
      N_misId_Delta_Bu2Dst0h_WN_(nullptr),
      N_misId_Delta_Bd2Dsth_(nullptr),
      N_misId_Delta_Bu2D0hst_(nullptr),
      N_misId_Delta_Bu2Dst0hst_(nullptr),
      N_misId_Bu_Bu2Dst0h_D0gamma_(nullptr),
      N_misId_Bu_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_Bu_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_misId_Bu_Bu2Dst0h_D0pi0_WN_(nullptr),
      N_misId_Bu_Bu2Dst0h_WN_(nullptr),
      N_misId_Bu_Bd2Dsth_(nullptr),
      N_misId_Bu_Bu2D0hst_(nullptr),
      N_misId_Bu_Bu2Dst0hst_(nullptr),
      N_misId_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_BuPartial_Bu2Dst0h_D0gamma_WN_(nullptr),
      N_misId_BuPartial_Bu2Dst0h_D0pi0_WN_(nullptr),
      N_misId_BuPartial_Bd2Dsth_(nullptr),
      N_misId_BuPartial_Bu2D0hst_(nullptr),
      N_misId_BuPartial_Bu2Dst0hst_(nullptr) {
  if (neutral == Neutral::pi0) {
    N_split_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bu2Dst0h_WN_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bu2Dst0h_WN(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bu2Dst0h_WN()));
    N_trueId_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu2Dst0h_WN_", *N_split_Bu2Dst0h_WN_));
    N_trueId_Bu_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bu2Dst0h_WN_", *N_trueId_Bu2Dst0h_WN_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buEffBu2Dst0h_WN()));
    N_trueId_Delta_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bu2Dst0h_WN_", *N_trueId_Bu2Dst0h_WN_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .deltaEffBu2Dst0h_WN()));
  }
  if (daughters == Daughters::kk) {
    N_split_Lb2Omegach_Lcpi0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Lb2Omegach_Lcpi0_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Lb2Omegach_Lcpi0(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Lb2Omegach_Lcpi0()));
    N_trueId_Lb2Omegach_Lcpi0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Lb2Omegach_Lcpi0_",
            *N_split_Lb2Omegach_Lcpi0_));
    N_trueId_Delta_Lb2Omegach_Lcpi0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Lb2Omegach_Lcpi0_",
            *N_trueId_Lb2Omegach_Lcpi0_,
            NeutralVars<neutral>::Get(uniqueId_).deltaEffLb2Omegach_Lcpi0()));
    N_trueId_Bu_Lb2Omegach_Lcpi0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Lb2Omegach_Lcpi0_",
            *N_trueId_Lb2Omegach_Lcpi0_,
            NeutralVars<neutral>::Get(uniqueId_).buEffLb2Omegach_Lcpi0()));
  }
  if (daughters == Daughters::pik) {
    N_split_Bu2Dst0h_D0pi0_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bu2Dst0h_D0pi0_D02pik_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bu2Dst0h_D0pi0_D02pik(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bu2Dst0h_D0pi0()));
    N_trueId_Bu2Dst0h_D0pi0_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu2Dst0h_D0pi0_D02pik_",
            *N_split_Bu2Dst0h_D0pi0_D02pik_));
    N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik_",
            *N_trueId_Bu2Dst0h_D0pi0_D02pik_,
            NeutralVars<neutral>::Get(uniqueId_).buEffBu2Dst0h_D0pi0_D02pik()));
    N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0pi0_D02pik_",
            *N_trueId_Bu2Dst0h_D0pi0_D02pik_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaEffBu2Dst0h_D0pi0_D02pik()));
    N_split_Bu2Dst0h_D0pi0_WN_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bu2Dst0h_D0pi0_WN_D02pik_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bu2Dst0h_D0pi0_WN_D02pik(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bu2Dst0h_D0pi0()));
    N_trueId_Bu2Dst0h_D0pi0_WN_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu2Dst0h_D0pi0_WN_D02pik_",
            *N_split_Bu2Dst0h_D0pi0_WN_D02pik_));
    N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik_",
            *N_trueId_Bu2Dst0h_D0pi0_WN_D02pik_,
            NeutralVars<neutral>::Get(uniqueId_)
                .buEffBu2Dst0h_D0pi0_WN_D02pik()));
    N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0pi0_WN_D02pik_",
            *N_trueId_Bu2Dst0h_D0pi0_WN_D02pik_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaEffBu2Dst0h_D0pi0_WN_D02pik()));
    if (neutral == Neutral::gamma) {
      N_split_Bu2Dst0h_D0gamma_D02pik_ = std::unique_ptr<RooFormulaVar>(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0gamma_D02pik_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0gamma_D02pik(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .a_Bu2Dst0h_D0gamma()));
      N_trueId_Bu2Dst0h_D0gamma_D02pik_ = std::unique_ptr<RooFormulaVar>(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0gamma_D02pik_",
              *N_split_Bu2Dst0h_D0gamma_D02pik_));
      N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0gamma_D02pik_",
              *N_trueId_Bu2Dst0h_D0gamma_D02pik_,
              NeutralVars<neutral>::Get(uniqueId_)
                  .buEffBu2Dst0h_D0gamma_D02pik()));
      N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0gamma_D02pik_",
              *N_trueId_Bu2Dst0h_D0gamma_D02pik_,
              NeutralVars<neutral>::Get(uniqueId_)
                  .deltaEffBu2Dst0h_D0gamma_D02pik()));
      N_split_Bu2Dst0h_D0gamma_WN_D02pik_ = std::unique_ptr<RooFormulaVar>(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0gamma_WN_D02pik_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0gamma_WN_D02pik(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .a_Bu2Dst0h_D0gamma()));
      N_trueId_Bu2Dst0h_D0gamma_WN_D02pik_ = std::unique_ptr<RooFormulaVar>(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0gamma_WN_D02pik_",
              *N_split_Bu2Dst0h_D0gamma_WN_D02pik_));
      N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0gamma_WN_D02pik_",
              *N_trueId_Bu2Dst0h_D0gamma_WN_D02pik_,
              NeutralVars<neutral>::Get(uniqueId_)
                  .buEffBu2Dst0h_D0gamma_WN_D02pik()));
      N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik_ =
          std::unique_ptr<RooFormulaVar>(
              Make_N_1D<neutral, bachelor, daughters, charge>(
                  uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0gamma_WN_D02pik_",
                  *N_trueId_Bu2Dst0h_D0gamma_WN_D02pik_,
                  NeutralVars<neutral>::Get(uniqueId_)
                      .deltaEffBu2Dst0h_D0gamma_WN_D02pik()));
    }
  }
  if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
      daughters != Daughters::kpi) {
    N_split_Bs2D0Kst0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bs2D0Kst0_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bs2D0Kst0(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bs2D0Kst0()));
    N_split_Bs2Dst0Kst0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bs2Dst0Kst0_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bs2Dst0Kst0(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bs2Dst0Kst0()));
    N_trueId_Bs2D0Kst0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bs2D0Kst0_", *N_split_Bs2D0Kst0_));
    N_trueId_Bs2Dst0Kst0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bs2Dst0Kst0_", *N_split_Bs2Dst0Kst0_));
    N_trueId_Delta_Bs2Dst0Kst0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bs2Dst0Kst0_", *N_trueId_Bs2Dst0Kst0_,
            NeutralVars<neutral>::Get(uniqueId_).deltaEffBs2Dst0Kst0()));
    N_trueId_Delta_Bs2D0Kst0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bs2D0Kst0_", *N_trueId_Bs2D0Kst0_,
            NeutralVars<neutral>::Get(uniqueId_).deltaEffBs2D0Kst0()));
    N_trueId_Bu_Bs2Dst0Kst0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bs2Dst0Kst0_", *N_trueId_Bs2Dst0Kst0_,
            NeutralVars<neutral>::Get(uniqueId_).buEffBs2Dst0Kst0()));
    N_trueId_Bu_Bs2D0Kst0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bs2D0Kst0_", *N_trueId_Bs2D0Kst0_,
            NeutralVars<neutral>::Get(uniqueId_).buEffBs2D0Kst0()));
  }
  if (Configuration::Get().fitBuPartial() == true) {
    N_trueId_BuPartial_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0gamma_",
            *N_trueId_Bu2Dst0h_D0gamma_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buPartialEffBu2Dst0h_D0gamma()));
    N_trueId_BuPartial_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0pi0_",
            *N_trueId_Bu2Dst0h_D0pi0_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buPartialEffBu2Dst0h_D0pi0()));
    N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN_",
            *N_trueId_Bu2Dst0h_D0gamma_WN_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buPartialEffBu2Dst0h_D0gamma_WN()));
    N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_",
            *N_trueId_Bu2Dst0h_D0pi0_WN_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buPartialEffBu2Dst0h_D0pi0_WN()));
    N_trueId_BuPartial_Bd2Dsth_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bd2Dsth_", *N_trueId_Bd2Dsth_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buPartialEffBd2Dsth()));
    N_trueId_BuPartial_Bu2D0hst_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2D0hst_", *N_trueId_Bu2D0hst_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buPartialEffBu2D0hst()));
    N_trueId_BuPartial_Bu2Dst0hst_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2Dst0hst_", *N_trueId_Bu2Dst0hst_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buPartialEffBu2Dst0hst()));
    N_trueId_BuPartial_comb_ = std::unique_ptr<RooFormulaVar>(
        (Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_comb_", N_trueId_comb_,
            NeutralVars<neutral>::Get(uniqueId_).buEff_comb())));
    if (daughters == Daughters::kk) {
      N_trueId_BuPartial_Lb2Omegach_Lcpi0_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_buPartial_Lb2Omegach_Lcpi0_",
              *N_trueId_Lb2Omegach_Lcpi0_,
              NeutralVars<neutral>::Get(uniqueId_)
                  .buPartialEffLb2Omegach_Lcpi0()));
    }
    if (daughters == Daughters::pik) {
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik_ =
          std::unique_ptr<RooFormulaVar>(
              Make_N_1D<neutral, bachelor, daughters, charge>(
                  uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik_",
                  *N_trueId_Bu2Dst0h_D0pi0_D02pik_,
                  NeutralVars<neutral>::Get(uniqueId_)
                      .buPartialEffBu2Dst0h_D0pi0_D02pik()));
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik_ =
          std::unique_ptr<RooFormulaVar>(
              Make_N_1D<neutral, bachelor, daughters, charge>(
                  uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik_",
                  *N_trueId_Bu2Dst0h_D0pi0_WN_D02pik_,
                  NeutralVars<neutral>::Get(uniqueId_)
                      .buPartialEffBu2Dst0h_D0pi0_WN_D02pik()));
    }
    if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
        daughters != Daughters::kpi) {
      N_trueId_BuPartial_Bs2Dst0Kst0_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_BuPartial_Bs2Dst0Kst0_",
              *N_trueId_Bs2Dst0Kst0_,
              NeutralVars<neutral>::Get(uniqueId_).buPartialEffBs2Dst0Kst0()));
      N_trueId_BuPartial_Bs2D0Kst0_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_BuPartial_Bs2D0Kst0_", *N_trueId_Bs2D0Kst0_,
              NeutralVars<neutral>::Get(uniqueId_).buPartialEffBs2D0Kst0()));
    }
  }
}

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Yields<_neutral, _bachelor, _daughters, _charge>::AssignMisIdYields() {
  std::cout << "Assigning misId yields for " << EnumToString(_neutral) << " "
            << EnumToString(_bachelor) << " " << EnumToString(_daughters) << " "
            << EnumToString(_charge) << "\n";
  switch (_bachelor) {
    case Bachelor::pi: {
      // For misId yields, need to scale split yield of TRUE bachelor by PID
      // efficiency
      constexpr Bachelor trueBachelor = Bachelor::k;
      N_misId_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2Dst0h_D0gamma_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2Dst0h_D0gamma(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2Dst0h_D0gamma(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2Dst0h_D0gamma(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2Dst0h_D0gamma(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2Dst0h_D0gamma()));
      N_misId_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2Dst0h_D0pi0_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2Dst0h_D0pi0(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2Dst0h_D0pi0(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2Dst0h_D0pi0(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2Dst0h_D0pi0(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2Dst0h_D0pi0()));
      N_misId_Bu2Dst0h_D0pi0_WN_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2Dst0h_D0pi0_WN_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2Dst0h_D0pi0_WN(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2Dst0h_D0pi0_WN(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2Dst0h_D0pi0_WN(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2Dst0h_D0pi0_WN(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2Dst0h_D0pi0_WN()));
      if (_neutral == Neutral::gamma) {
        N_misId_Bu2Dst0h_D0gamma_WN_ = std::unique_ptr<RooFormulaVar>(
            Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
                uniqueId_, "N_misId_Bu2Dst0h_D0gamma_WN_",
                Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                    uniqueId_)
                    .N_split_Bu2Dst0h_D0gamma_WN(),
                NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                    .mcEffMisId_Bu2Dst0h_D0gamma_WN(),
                NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                    .mcEff_Bu2Dst0h_D0gamma_WN(),
                NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                    .orEffMisId_Bu2Dst0h_D0gamma_WN(),
                NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                    .orEffBu2Dst0h_D0gamma_WN()));
      } else {
        N_misId_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(
            Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
                uniqueId_, "N_misId_Bu2Dst0h_WN_",
                Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                    uniqueId_)
                    .N_split_Bu2Dst0h_WN(),
                NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                    .mcEffMisId_Bu2Dst0h_WN(),
                NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                    .mcEff_Bu2Dst0h_WN(),
                NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                    .orEffMisId_Bu2Dst0h_WN(),
                NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                    .orEffBu2Dst0h_WN()));
      }
      N_misId_Bd2Dsth_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bd2Dsth_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bd2Dsth(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bd2Dsth(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bd2Dsth(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bd2Dsth(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBd2Dsth()));
      N_misId_Bu2D0hst_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2D0hst_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2D0hst(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2D0hst(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2D0hst(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2D0hst(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2D0hst()));
      break;
    }
    case Bachelor::k: {
      constexpr Bachelor trueBachelor = Bachelor::pi;
      N_misId_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2Dst0h_D0gamma_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2Dst0h_D0gamma(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2Dst0h_D0gamma(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2Dst0h_D0gamma(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2Dst0h_D0gamma(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2Dst0h_D0gamma()));
      N_misId_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2Dst0h_D0pi0_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2Dst0h_D0pi0(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2Dst0h_D0pi0(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2Dst0h_D0pi0(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2Dst0h_D0pi0(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2Dst0h_D0pi0()));
      N_misId_Bu2Dst0h_D0gamma_WN_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2Dst0h_D0gamma_WN_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2Dst0h_D0gamma_WN(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2Dst0h_D0gamma_WN(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2Dst0h_D0gamma_WN(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2Dst0h_D0gamma_WN(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2Dst0h_D0gamma_WN()));
      N_misId_Bu2Dst0h_D0pi0_WN_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2Dst0h_D0pi0_WN_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2Dst0h_D0pi0_WN(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2Dst0h_D0pi0_WN(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2Dst0h_D0pi0_WN(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2Dst0h_D0pi0_WN(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2Dst0h_D0pi0_WN()));
      if (_neutral == Neutral::pi0) {
        N_misId_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(
            Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
                uniqueId_, "N_misId_Bu2Dst0h_WN_",
                Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                    uniqueId_)
                    .N_split_Bu2Dst0h_WN(),
                NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                    .mcEffMisId_Bu2Dst0h_WN(),
                NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                    .mcEff_Bu2Dst0h_WN(),
                NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                    .orEffMisId_Bu2Dst0h_WN(),
                NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                    .orEffBu2Dst0h_WN()));
      }
      N_misId_Bd2Dsth_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bd2Dsth_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bd2Dsth(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bd2Dsth(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bd2Dsth(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bd2Dsth(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBd2Dsth()));
      N_misId_Bu2D0hst_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2D0hst_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2D0hst(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2D0hst(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2D0hst(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2D0hst(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2D0hst()));
      N_misId_Bu2Dst0hst_ = std::unique_ptr<RooFormulaVar>(
          Make_N_misId<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_Bu2Dst0hst_",
              Yields<_neutral, trueBachelor, _daughters, _charge>::Get(
                  uniqueId_)
                  .N_split_Bu2Dst0hst(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .mcEffMisId_Bu2Dst0hst(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .mcEff_Bu2Dst0hst(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .orEffMisId_Bu2Dst0hst(),
              NeutralBachelorVars<_neutral, trueBachelor>::Get(uniqueId_)
                  .orEffBu2Dst0hst()));
      break;
    }
  }
  N_misId_Delta_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Delta_Bu2Dst0h_D0gamma_",
          *N_misId_Bu2Dst0h_D0gamma_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .deltaEffMisId_Bu2Dst0h_D0gamma()));
  N_misId_Delta_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Delta_Bu2Dst0h_D0pi0_", *N_misId_Bu2Dst0h_D0pi0_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .deltaEffMisId_Bu2Dst0h_D0pi0()));
  N_misId_Delta_Bu2Dst0h_D0pi0_WN_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Delta_Bu2Dst0h_D0pi0_WN_",
          *N_misId_Bu2Dst0h_D0pi0_WN_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .deltaEffMisId_Bu2Dst0h_D0pi0_WN()));
  if (_neutral == Neutral::gamma ||
      (_neutral == Neutral::pi0 && _bachelor == Bachelor::k)) {
    N_misId_Delta_Bu2Dst0h_D0gamma_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_Delta_Bu2Dst0h_D0gamma_WN_",
            *N_misId_Bu2Dst0h_D0gamma_WN_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .deltaEffMisId_Bu2Dst0h_D0gamma_WN()));
  }
  if (_neutral == Neutral::pi0) {
    N_misId_Delta_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_Delta_Bu2Dst0h_WN_", *N_misId_Bu2Dst0h_WN_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .deltaEffMisId_Bu2Dst0h_WN()));
  }
  if (_bachelor == Bachelor::k) {
    N_misId_Delta_Bu2Dst0hst_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_Delta_Bu2Dst0hst_", *N_misId_Bu2Dst0hst_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .deltaEffMisId_Bu2Dst0hst()));
  }
  N_misId_Delta_Bd2Dsth_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Delta_Bd2Dsth_", *N_misId_Bd2Dsth_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .deltaEffMisId_Bd2Dsth()));
  N_misId_Delta_Bu2D0hst_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Delta_Bu2D0hst_", *N_misId_Bu2D0hst_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .deltaEffMisId_Bu2D0hst()));
  N_misId_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Bu_Bu2Dst0h_D0gamma_", *N_misId_Bu2Dst0h_D0gamma_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .buEffMisId_Bu2Dst0h_D0gamma()));
  N_misId_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Bu_Bu2Dst0h_D0pi0_", *N_misId_Bu2Dst0h_D0pi0_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .buEffMisId_Bu2Dst0h_D0pi0()));
  N_misId_Bu_Bu2Dst0h_D0pi0_WN_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Bu_Bu2Dst0h_D0pi0_WN_",
          *N_misId_Bu2Dst0h_D0pi0_WN_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .buEffMisId_Bu2Dst0h_D0pi0_WN()));
  if (_neutral == Neutral::gamma ||
      (_neutral == Neutral::pi0 && _bachelor == Bachelor::k)) {
    N_misId_Bu_Bu2Dst0h_D0gamma_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_Bu_Bu2Dst0h_D0gamma_WN_",
            *N_misId_Bu2Dst0h_D0gamma_WN_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .buEffMisId_Bu2Dst0h_D0gamma_WN()));
  }
  if (_neutral == Neutral::pi0) {
    N_misId_Bu_Bu2Dst0h_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_Bu_Bu2Dst0h_WN_", *N_misId_Bu2Dst0h_WN_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .buEffMisId_Bu2Dst0h_WN()));
  }
  N_misId_Bu_Bd2Dsth_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Bu_Bd2Dsth_", *N_misId_Bd2Dsth_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .buEffMisId_Bd2Dsth()));
  N_misId_Bu_Bu2D0hst_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
          uniqueId_, "N_misId_Bu_Bu2D0hst_", *N_misId_Bu2D0hst_,
          NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
              .buEffMisId_Bu2D0hst()));
  if (_bachelor == Bachelor::k) {
    N_misId_Bu_Bu2Dst0hst_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_Bu_Bu2Dst0hst_", *N_misId_Bu2Dst0hst_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .buEffMisId_Bu2Dst0hst()));
  }
  if (Configuration::Get().fitBuPartial() == true) {
    N_misId_BuPartial_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_BuPartial_Bu2Dst0h_D0pi0_",
            *N_misId_Bu2Dst0h_D0pi0_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .buPartialEffMisId_Bu2Dst0h_D0pi0()));
    N_misId_BuPartial_Bu2Dst0h_D0gamma_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_BuPartial_Bu2Dst0h_D0gamma_WN_",
            *N_misId_Bu2Dst0h_D0gamma_WN_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .buPartialEffMisId_Bu2Dst0h_D0gamma_WN()));
    N_misId_BuPartial_Bu2Dst0h_D0pi0_WN_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_BuPartial_Bu2Dst0h_D0pi0_WN_",
            *N_misId_Bu2Dst0h_D0pi0_WN_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .buPartialEffMisId_Bu2Dst0h_D0pi0_WN()));
    N_misId_BuPartial_Bd2Dsth_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_BuPartial_Bd2Dsth_", *N_misId_Bd2Dsth_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .buPartialEffMisId_Bd2Dsth()));
    N_misId_BuPartial_Bu2D0hst_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
            uniqueId_, "N_misId_BuPartial_Bu2D0hst_", *N_misId_Bu2D0hst_,
            NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                .buPartialEffMisId_Bu2D0hst()));
    if (_bachelor == Bachelor::k) {
      N_misId_BuPartial_Bu2Dst0hst_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<_neutral, _bachelor, _daughters, _charge>(
              uniqueId_, "N_misId_BuPartial_Bu2Dst0hst_", *N_misId_Bu2Dst0hst_,
              NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
                  .buPartialEffMisId_Bu2Dst0hst()));
    }
  }
}
