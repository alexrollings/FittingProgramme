#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorChargeVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"

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
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
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
                             GlobalVars::Get(uniqueId).a_Kpi(),
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
                             GlobalVars::Get(uniqueId).a_Kpi(),
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
                             GlobalVars::Get(uniqueId).a_Kpi(),
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
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
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
                             GlobalVars::Get(uniqueId).a_Kpi(),
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
                             GlobalVars::Get(uniqueId).a_Kpi(),
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
                             GlobalVars::Get(uniqueId).a_Kpi(),
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
      RooArgList(N_split, *GlobalVars::Get(uniqueId)
                         .pidEffMap()[MakePidKey(bachelor, Charge::total)]));
}

// To calculate 1D yields, for D1D fit, multiply total events by corresponding
// cut efficiency, and PID eff
template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *Make_N_1D(int uniqueId, const char *nameStr, RooAbsReal &N,
                         RooAbsReal &cutEff) {
  if (Configuration::Get().fit1D() == true &&
      Configuration::Get().fitBuPartial() == false) {
    // 1D fit doesn't get multiplied by any efficiency
    return new RooFormulaVar(
        (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "@0*@1",
        RooArgList(N, *GlobalVars::Get(uniqueId)
                           .pidEffMap()[MakePidKey(bachelor, Charge::total)]));
  } else {
    return new RooFormulaVar(
        (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "@0*@1*@2",
        RooArgList(N, cutEff,
                   *GlobalVars::Get(uniqueId)
                        .pidEffMap()[MakePidKey(bachelor, Charge::total)]));
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
  static This_t &Get(int uniqueId) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId))
               .first;
    }
    return *it->second;
  }

  int uniqueId() { return uniqueId_; }

  RooFormulaVar &N_split_Bu2Dst0h_D0gamma() {
    return *N_split_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_split_Bu2Dst0h_D0gamma_FAVasSUP() {
    return *N_split_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooFormulaVar &N_split_Bu2Dst0h_D0pi0() { return *N_split_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_split_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *N_split_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooFormulaVar &N_split_MisRec() { return *N_split_MisRec_; }
  RooFormulaVar &N_split_Bu2D0h() { return *N_split_Bu2D0h_; }
  RooFormulaVar &N_split_PartRec() { return *N_split_PartRec_; }
  RooFormulaVar &N_split_Bs2Dst0Kpi() { return *N_split_Bs2Dst0Kpi_; }
  RooFormulaVar &N_split_Bs2D0Kpi() { return *N_split_Bs2D0Kpi_; }

  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma() {
    return *N_trueId_Delta_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP() {
    return *N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0() {
    return *N_trueId_Delta_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooFormulaVar &N_trueId_Delta_MisRec() { return *N_trueId_Delta_MisRec_; }
  RooFormulaVar &N_trueId_Delta_Bu2D0h() { return *N_trueId_Delta_Bu2D0h_; }
  RooFormulaVar &N_trueId_Delta_PartRec() { return *N_trueId_Delta_PartRec_; }
  RooFormulaVar &N_trueId_Delta_Bs2Dst0Kpi() {
    return *N_trueId_Delta_Bs2Dst0Kpi_;
  }
  RooFormulaVar &N_trueId_Delta_Bs2D0Kpi() { return *N_trueId_Delta_Bs2D0Kpi_; }

  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma() {
    return *N_trueId_Bu_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP() {
    return *N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0() {
    return *N_trueId_Bu_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooFormulaVar &N_trueId_Bu_MisRec() { return *N_trueId_Bu_MisRec_; }
  RooFormulaVar &N_trueId_Bu_Bu2D0h() { return *N_trueId_Bu_Bu2D0h_; }
  RooFormulaVar &N_trueId_Bu_PartRec() { return *N_trueId_Bu_PartRec_; }
  RooFormulaVar &N_trueId_Bu_Bs2Dst0Kpi() { return *N_trueId_Bu_Bs2Dst0Kpi_; }
  RooFormulaVar &N_trueId_Bu_Bs2D0Kpi() { return *N_trueId_Bu_Bs2D0Kpi_; }

  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0gamma() {
    return *N_trueId_BuPartial_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0() {
    return *N_trueId_BuPartial_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooFormulaVar &N_trueId_BuPartial_MisRec() {
    return *N_trueId_BuPartial_MisRec_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bu2D0h() {
    return *N_trueId_BuPartial_Bu2D0h_;
  }
  RooFormulaVar &N_trueId_BuPartial_PartRec() {
    return *N_trueId_BuPartial_PartRec_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bs2Dst0Kpi() {
    return *N_trueId_BuPartial_Bs2Dst0Kpi_;
  }
  RooFormulaVar &N_trueId_BuPartial_Bs2D0Kpi() {
    return *N_trueId_BuPartial_Bs2D0Kpi_;
  }

 private:
  int uniqueId_;

  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_split_MisRec_;
  std::unique_ptr<RooFormulaVar> N_split_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_split_PartRec_;
  std::unique_ptr<RooFormulaVar> N_split_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> N_split_Bs2D0Kpi_;

  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_trueId_MisRec_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_trueId_PartRec_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bs2D0Kpi_;

  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_MisRec_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_PartRec_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> N_trueId_Delta_Bs2D0Kpi_;

  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_MisRec_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_PartRec_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> N_trueId_Bu_Bs2D0Kpi_;

  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_MisRec_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_PartRec_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> N_trueId_BuPartial_Bs2D0Kpi_;
};

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
Yields<neutral, bachelor, daughters, charge>::Yields(int uniqueId)
    : uniqueId_(uniqueId),
      N_split_Bu2Dst0h_D0gamma_(nullptr),
      N_split_Bu2Dst0h_D0pi0_(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0pi0_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0pi0(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .a_Bu2Dst0h_D0pi0())),
      N_split_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_split_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_split_MisRec_(Make_N_split<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_split_MisRec_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .N_tot_MisRec(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .a_MisRec())),
      N_split_Bu2D0h_(Make_N_split<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_split_Bu2D0h_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .N_tot_Bu2D0h(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .a_Bu2D0h())),
      N_split_PartRec_(Make_N_split<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_split_PartRec_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .N_tot_PartRec(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .a_PartRec())),
      N_split_Bs2Dst0Kpi_(nullptr),
      N_split_Bs2D0Kpi_(nullptr),
      N_trueId_Bu2Dst0h_D0gamma_(nullptr),
      N_trueId_Bu2Dst0h_D0pi0_(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0pi0_", *N_split_Bu2Dst0h_D0pi0_)),
      N_trueId_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_trueId_MisRec_(Make_N_trueId<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_MisRec_", *N_split_MisRec_)),
      N_trueId_Bu2D0h_(Make_N_trueId<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu2D0h_", *N_split_Bu2D0h_)),
      N_trueId_PartRec_(Make_N_trueId<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_PartRec_", *N_split_PartRec_)),
      N_trueId_Bs2Dst0Kpi_(nullptr),
      N_trueId_Bs2D0Kpi_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0gamma_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0pi0_(Make_N_1D<neutral, bachelor, daughters,
                                               charge>(
          uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0pi0_", *N_split_Bu2Dst0h_D0pi0_,
          NeutralVars<neutral>::Get(uniqueId_).buDeltaCutEffBu2Dst0h_D0pi0())),
      N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_trueId_Delta_MisRec_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Delta_MisRec_", *N_split_MisRec_,
          NeutralVars<neutral>::Get(uniqueId_).buDeltaCutEffMisRec())),
      N_trueId_Delta_Bu2D0h_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Delta_Bu2D0h_", *N_split_Bu2D0h_,
          NeutralVars<neutral>::Get(uniqueId_).buDeltaCutEffBu2D0h())),
      N_trueId_Delta_PartRec_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Delta_PartRec_", *N_split_PartRec_,
          NeutralVars<neutral>::Get(uniqueId_).buDeltaCutEffPartRec())),
      N_trueId_Delta_Bs2Dst0Kpi_(nullptr),
      N_trueId_Delta_Bs2D0Kpi_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0gamma_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0pi0_(nullptr),
      N_trueId_Bu_MisRec_(nullptr),
      N_trueId_Bu_Bu2D0h_(nullptr),
      N_trueId_Bu_PartRec_(nullptr),
      N_trueId_Bu_Bs2Dst0Kpi_(nullptr),
      N_trueId_Bu_Bs2D0Kpi_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0gamma_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_trueId_BuPartial_MisRec_(nullptr),
      N_trueId_BuPartial_Bu2D0h_(nullptr),
      N_trueId_BuPartial_PartRec_(nullptr),
      N_trueId_BuPartial_Bs2Dst0Kpi_(nullptr),
      N_trueId_BuPartial_Bs2D0Kpi_(nullptr) {
  if (neutral == Neutral::gamma) {
    N_split_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bu2Dst0h_D0gamma()));
    N_trueId_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu2Dst0h_D0gamma_",
            *N_split_Bu2Dst0h_D0gamma_));
    N_trueId_Delta_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0gamma_",
            *N_split_Bu2Dst0h_D0gamma_,
            NeutralVars<neutral>::Get(uniqueId_)
                .buDeltaCutEffBu2Dst0h_D0gamma()));
  }
  if (daughters == Daughters::pik) {
    N_split_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bu2Dst0h_D0pi0_FAVasSUP_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bu2Dst0h_D0pi0_FAVasSUP(),
            NeutralBachelorDaughtersVars<neutral, bachelor,
                                         Daughters::kpi>::Get(uniqueId_)
                .a_Bu2Dst0h_D0pi0()));
    N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_",
            *N_split_Bu2Dst0h_D0pi0_FAVasSUP_));
    N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP_",
            *N_split_Bu2Dst0h_D0pi0_FAVasSUP_,
            NeutralVars<neutral>::Get(uniqueId_)
                .buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP()));
    if (neutral == Neutral::gamma) {
      N_split_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0gamma_FAVasSUP_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0gamma_FAVasSUP(),
              NeutralBachelorDaughtersVars<neutral, bachelor,
                                           Daughters::kpi>::Get(uniqueId_)
                  .a_Bu2Dst0h_D0gamma()));
      N_trueId_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0gamma_FAVasSUP_",
              *N_split_Bu2Dst0h_D0gamma_FAVasSUP_));
      N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP_ =
          std::unique_ptr<RooFormulaVar>(
              Make_N_1D<neutral, bachelor, daughters, charge>(
                  uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP_",
                  *N_split_Bu2Dst0h_D0gamma_FAVasSUP_,
                  NeutralVars<neutral>::Get(uniqueId_)
                      .buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP()));
    }
  }
  if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
      daughters != Daughters::kpi) {
    N_split_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bs2Dst0Kpi_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bs2Dst0Kpi(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bs2Dst0Kpi()));
    N_trueId_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bs2Dst0Kpi_", *N_split_Bs2Dst0Kpi_));
    N_split_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bs2D0Kpi_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bs2D0Kpi(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bs2D0Kpi()));
    N_trueId_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bs2D0Kpi_", *N_split_Bs2D0Kpi_));
    N_trueId_Delta_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bs2Dst0Kpi_", *N_split_Bs2Dst0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buDeltaCutEffBs2Dst0Kpi()));
    N_trueId_Delta_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bs2D0Kpi_", *N_split_Bs2D0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buDeltaCutEffBs2D0Kpi()));
  }
  if (neutral == Neutral::gamma) {
    N_trueId_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0gamma_",
            *N_split_Bu2Dst0h_D0gamma_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaCutEffBu2Dst0h_D0gamma()));
  }
  N_trueId_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0pi0_", *N_split_Bu2Dst0h_D0pi0_,
          NeutralVars<neutral>::Get(uniqueId_).deltaCutEffBu2Dst0h_D0pi0()));
  N_trueId_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_MisRec_", *N_split_MisRec_,
          NeutralVars<neutral>::Get(uniqueId_).deltaCutEffMisRec()));
  N_trueId_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_Bu2D0h_", *N_split_Bu2D0h_,
          NeutralVars<neutral>::Get(uniqueId_).deltaCutEffBu2D0h()));
  N_trueId_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_PartRec_", *N_split_PartRec_,
          NeutralVars<neutral>::Get(uniqueId_).deltaCutEffPartRec()));
  if (daughters == Daughters::pik) {
    N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP_",
            *N_split_Bu2Dst0h_D0pi0_FAVasSUP_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaCutEffBu2Dst0h_D0pi0_FAVasSUP()));
    if (neutral == Neutral::gamma) {
      N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP_",
              *N_split_Bu2Dst0h_D0gamma_FAVasSUP_,
              NeutralVars<neutral>::Get(uniqueId_)
                  .deltaCutEffBu2Dst0h_D0gamma_FAVasSUP()));
    }
  }
  if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
      daughters != Daughters::kpi) {
    N_trueId_Bu_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bs2Dst0Kpi_", *N_split_Bs2Dst0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .deltaCutEffBs2Dst0Kpi()));
    N_trueId_Bu_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bs2D0Kpi_", *N_split_Bs2D0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .deltaCutEffBs2D0Kpi()));
  }
  if (Configuration::Get().fitBuPartial() == true) {
    N_trueId_BuPartial_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0gamma_",
            *N_split_Bu2Dst0h_D0gamma_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaPartialCutEffBu2Dst0h_D0gamma()));
    N_trueId_BuPartial_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0pi0_",
            *N_split_Bu2Dst0h_D0pi0_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaPartialCutEffBu2Dst0h_D0pi0()));
    N_trueId_BuPartial_MisRec_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_MisRec_", *N_split_MisRec_,
            NeutralVars<neutral>::Get(uniqueId_).deltaPartialCutEffMisRec()));
    N_trueId_BuPartial_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2D0h_", *N_split_Bu2D0h_,
            NeutralVars<neutral>::Get(uniqueId_).deltaPartialCutEffBu2D0h()));
    N_trueId_BuPartial_PartRec_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_PartRec_", *N_split_PartRec_,
            NeutralVars<neutral>::Get(uniqueId_).deltaPartialCutEffPartRec()));
    if (daughters == Daughters::pik) {
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_ =
          std::unique_ptr<RooFormulaVar>(
              Make_N_1D<neutral, bachelor, daughters, charge>(
                  uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_",
                  *N_split_Bu2Dst0h_D0pi0_FAVasSUP_,
                  NeutralVars<neutral>::Get(uniqueId_)
                      .deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP()));
    }
    if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
        daughters != Daughters::kpi) {
      N_trueId_BuPartial_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_BuPartial_Bs2Dst0Kpi_", *N_split_Bs2Dst0Kpi_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .deltaPartialCutEffBs2Dst0Kpi()));
      N_trueId_BuPartial_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_BuPartial_Bs2D0Kpi_", *N_split_Bs2D0Kpi_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .deltaPartialCutEffBs2D0Kpi()));
    }
  }
}
