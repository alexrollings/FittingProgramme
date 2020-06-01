#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorChargeVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "NeutralChargeVars.h"

// Return yield with correct asymmetry definition
template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *MakeYield(int uniqueId, const char *nameStr, RooAbsReal &N_tot,
                         RooAbsReal &A_RAW) {
  switch (charge) {
    case Charge::plus:
      switch (daughters) {
        case Daughters::kpi:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "(@0/2)*(1-(@1-@2-@3-@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "(@0/2)*(1-(@1-@2-2*@3-@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
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
                  "(@0/2)*(1-(@1-@2-@3))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "(@0/2)*(1-(@1-@2-@3-@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
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
                  "(@0/2)*(1-(@1-@2-@3))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "(@0/2)*(1-(@1-@2-@3-@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
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
                  "(@0/2)*(1-(@1-@2+@3-@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "(@0/2)*(1-(@1-@2-@3))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_pi()));
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
                  "(@0/2)*(1+(@1+@2+@3+@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "(@0/2)*(1+(@1+@2+2*@3+@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
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
                  "(@0/2)*(1+(@1+@2+@3))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "(@0/2)*(1+(@1+@2+@3+@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
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
                  "(@0/2)*(1+(@1+@2+@3))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "(@0/2)*(1+(@1+@2+@3+@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
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
                  "(@0/2)*(1+(@1+@2-@3+@4))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_Kpi(),
                             Configuration::Get().A_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "(@0/2)*(1+(@1+@2+@3))",
                  RooArgList(N_tot, A_RAW, Configuration::Get().A_Prod(),
                             Configuration::Get().A_pi()));
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

// To calculate 1D yields, for D1D fit, multiply total events by corresponding
// cut efficiency, and PID eff
template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *MakeYield1D(int uniqueId, const char *nameStr, RooAbsReal &N,
                           RooAbsReal &cutEff) {
  if (Configuration::Get().fit1D() == true &&
      Configuration::Get().fitBuPartial() == false) {
    throw std::logic_error(
        "Cannot multiply yield by cut eff for 1D fit with no buPartial dimn");
  }
  return new RooFormulaVar(
      (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
          .c_str(),
      "@0*@1*@2",
      RooArgList(N, cutEff,
                 NeutralChargeVars<neutral, charge>::Get(uniqueId).GetPidEff(
                     bachelor)));
}

// To calculate 1D yields, for 1D fit, multiply total events by PID eff only
template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *MakeYield1D(int uniqueId, const char *nameStr, RooAbsReal &N) {
  if (!(Configuration::Get().fit1D() == true &&
        Configuration::Get().fitBuPartial() == false)) {
    throw std::logic_error(
        "Must multiply total yield for charge by cut eff for D1D fit or fit "
        "with buPartial");
  }
  return new RooFormulaVar(
      (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
          .c_str(),
      "@0*@1",
      RooArgList(N, NeutralChargeVars<neutral, charge>::Get(uniqueId).GetPidEff(
                        bachelor)));
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>

class Yields {
 public:
  Yields(int uniqueId_);
  ~Yields() {}

  using This_t = Yields<neutral, bachelor, daughters, charge>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId_) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId_);  // Check if uniqueId_ already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId_, std::make_shared<This_t>(uniqueId_))
               .first;
    }
    return *it->second;
  }

  int uniqueId() { return uniqueId_; }
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooFormulaVar &N_Bu2Dst0h_D0gamma() { return *N_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0gamma() {
    return *N_Delta_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_Bu_Bu2Dst0h_D0gamma() { return *N_Bu_Bu2Dst0h_D0gamma_; }
  RooAbsReal &N_BuPartial_Bu2Dst0h_D0gamma() {
    return *N_BuPartial_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
  RooFormulaVar &N_Bu2Dst0h_D0gamma_FAVasSUP() {
    return *N_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0gamma_FAVasSUP() {
    return *N_Delta_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  RooAbsReal &N_Bu_Bu2Dst0h_D0gamma_FAVasSUP() {
    return *N_Bu_Bu2Dst0h_D0gamma_FAVasSUP_;
  }
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooFormulaVar &N_Bu2Dst0h_D0pi0() { return *N_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0pi0() { return *N_Delta_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_Bu_Bu2Dst0h_D0pi0() { return *N_Bu_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_BuPartial_Bu2Dst0h_D0pi0() {
    return *N_BuPartial_Bu2Dst0h_D0pi0_;
  }
  // -------------------- Bu2Dst0h_D0pi0_FAVasSUP -------------------- //
  RooFormulaVar &N_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *N_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *N_Delta_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooAbsReal &N_Bu_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *N_Bu_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  RooAbsReal &N_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP() {
    return *N_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_;
  }
  // -------------------- MIS-REC -------------------- //
  RooFormulaVar &N_MisRec() { return *N_MisRec_; }
  RooFormulaVar &N_Delta_MisRec() { return *N_Delta_MisRec_; }
  RooAbsReal &N_Bu_MisRec() { return *N_Bu_MisRec_; }
  RooAbsReal &N_BuPartial_MisRec() { return *N_BuPartial_MisRec_; }
  // -------------------- Bu2D0h -------------------- //
  RooFormulaVar &N_Bu2D0h() { return *N_Bu2D0h_; }
  RooFormulaVar &N_Delta_Bu2D0h() { return *N_Delta_Bu2D0h_; }
  RooAbsReal &N_Bu_Bu2D0h() { return *N_Bu_Bu2D0h_; }
  RooAbsReal &N_BuPartial_Bu2D0h() { return *N_BuPartial_Bu2D0h_; }
  // -------------------- PART REC -------------------- //
  RooFormulaVar &N_PartRec() { return *N_PartRec_; }
  RooFormulaVar &N_Delta_PartRec() { return *N_Delta_PartRec_; }
  RooAbsReal &N_Bu_PartRec() { return *N_Bu_PartRec_; }
  RooAbsReal &N_BuPartial_PartRec() { return *N_BuPartial_PartRec_; }
  // -------------------- Bs2Dst0Kpi -------------------- //
  RooFormulaVar &N_Bs2Dst0Kpi() { return *N_Bs2Dst0Kpi_; }
  RooFormulaVar &N_Delta_Bs2Dst0Kpi() { return *N_Delta_Bs2Dst0Kpi_; }
  RooAbsReal &N_Bu_Bs2Dst0Kpi() { return *N_Bu_Bs2Dst0Kpi_; }
  RooAbsReal &N_BuPartial_Bs2Dst0Kpi() { return *N_BuPartial_Bs2Dst0Kpi_; }
  // -------------------- Bs2D0Kpi -------------------- //
  RooFormulaVar &N_Bs2D0Kpi() { return *N_Bs2D0Kpi_; }
  RooFormulaVar &N_Delta_Bs2D0Kpi() { return *N_Delta_Bs2D0Kpi_; }
  RooAbsReal &N_Bu_Bs2D0Kpi() { return *N_Bu_Bs2D0Kpi_; }
  RooAbsReal &N_BuPartial_Bs2D0Kpi() { return *N_BuPartial_Bs2D0Kpi_; }

 private:
  int uniqueId_;

  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0gamma_;
  // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0gamma_FAVasSUP_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0gamma_FAVasSUP_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0pi0_;
  // -------------------- Bu2Dst0h_D0pi0_FAVasSUP -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0pi0_FAVasSUP_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_;
  // -------------------- MIS-REC -------------------- //
  std::unique_ptr<RooFormulaVar> N_MisRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_MisRec_;
  std::unique_ptr<RooAbsReal> N_Bu_MisRec_;
  std::unique_ptr<RooAbsReal> N_BuPartial_MisRec_;
  // -------------------- Bu2D0h -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2D0h_;
  // -------------------- PART REC -------------------- //
  std::unique_ptr<RooFormulaVar> N_PartRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_PartRec_;
  std::unique_ptr<RooAbsReal> N_Bu_PartRec_;
  std::unique_ptr<RooAbsReal> N_BuPartial_PartRec_;
  // -------------------- Bs2Dst0Kpi -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bs2Dst0Kpi_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bs2Dst0Kpi_;
  std::unique_ptr<RooAbsReal> N_Bu_Bs2Dst0Kpi_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bs2Dst0Kpi_;
  // -------------------- Bs2D0Kpi -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bs2D0Kpi_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bs2D0Kpi_;
  std::unique_ptr<RooAbsReal> N_Bu_Bs2D0Kpi_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bs2D0Kpi_;
};

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
Yields<neutral, bachelor, daughters, charge>::Yields(int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : N_Bu2Dst0h_D0gamma_(nullptr),
      N_Delta_Bu2Dst0h_D0gamma_(nullptr),
      N_Bu_Bu2Dst0h_D0gamma_(nullptr),
      N_BuPartial_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Bu2Dst0h_D0gamma_FAVasSUP -------------------- //
      N_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_Delta_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_Bu_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      N_Bu2Dst0h_D0pi0_(MakeYield<neutral, bachelor, daughters, charge>(
          uniqueId, "N_Bu2Dst0h_D0pi0_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId)
              .N_tot_Bu2Dst0h_D0pi0(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId)
              .A_Bu2Dst0h_D0pi0())),
      N_Delta_Bu2Dst0h_D0pi0_(MakeYield1D<neutral, bachelor, daughters, charge>(
          uniqueId, "N_Delta_Bu2Dst0h_D0pi0_", *N_Bu2Dst0h_D0pi0_,
          NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffBu2Dst0h_D0pi0())),
      N_Bu_Bu2Dst0h_D0pi0_(nullptr),
      N_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0_FAVasSUP -------------------- //
      N_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_Delta_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_Bu_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      // -------------------- MisRec -------------------- //
      N_MisRec_(MakeYield<neutral, bachelor, daughters, charge>(
          uniqueId, "N_MisRec_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId)
              .N_tot_MisRec(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId)
              .A_MisRec())),
      N_Delta_MisRec_(MakeYield1D<neutral, bachelor, daughters, charge>(
          uniqueId, "N_Delta_MisRec_", *N_MisRec_,
          NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffMisRec())),
      N_Bu_MisRec_(nullptr),
      N_BuPartial_MisRec_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      N_Bu2D0h_(MakeYield<neutral, bachelor, daughters, charge>(
          uniqueId, "N_Bu2D0h_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId)
              .N_tot_Bu2D0h(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId)
              .A_Bu2D0h())),
      N_Delta_Bu2D0h_(MakeYield1D<neutral, bachelor, daughters, charge>(
          uniqueId, "N_Delta_Bu2D0h_", *N_Bu2D0h_,
          NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffBu2D0h())),
      N_Bu_Bu2D0h_(nullptr),
      N_BuPartial_Bu2D0h_(nullptr),
      // -------------------- PartRec -------------------- //
      N_PartRec_(MakeYield<neutral, bachelor, daughters, charge>(
          uniqueId, "N_PartRec_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId)
              .N_tot_PartRec(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId)
              .A_PartRec())),
      N_Delta_PartRec_(MakeYield1D<neutral, bachelor, daughters, charge>(
          uniqueId, "N_Delta_PartRec_", *N_PartRec_,
          NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffPartRec())),
      N_Bu_PartRec_(nullptr),
      N_BuPartial_PartRec_(nullptr),
      // -------------------- Bs2Dst0Kpi -------------------- //
      N_Bs2Dst0Kpi_(nullptr),
      N_Delta_Bs2Dst0Kpi_(nullptr),
      N_Bu_Bs2Dst0Kpi_(nullptr),
      N_BuPartial_Bs2Dst0Kpi_(nullptr),
      // -------------------- Bs2D0Kpi -------------------- //
      N_Bs2D0Kpi_(nullptr),
      N_Delta_Bs2D0Kpi_(nullptr),
      N_Bu_Bs2D0Kpi_(nullptr),
      N_BuPartial_Bs2D0Kpi_(nullptr) {
  if (daughters == Daughters::pik) {
    N_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        MakeYield<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu2Dst0h_D0pi0_FAVasSUP_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .N_tot_Bu2Dst0h_D0pi0_FAVasSUP(),
            NeutralBachelorDaughtersVars<neutral, bachelor,
                                         Daughters::kpi>::Get(uniqueId)
                .A_Bu2Dst0h_D0pi0()));
    N_Delta_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Delta_Bu2Dst0h_D0pi0_FAVasSUP_",
            *N_Bu2Dst0h_D0pi0_FAVasSUP_,
            NeutralVars<neutral>::Get(uniqueId)
                .buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP()));
    if (neutral == Neutral::gamma) {
      N_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          MakeYield<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Bu2Dst0h_D0gamma_FAVasSUP_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma_FAVasSUP(),
              NeutralBachelorDaughtersVars<neutral, bachelor,
                                           Daughters::kpi>::Get(uniqueId)
                  .A_Bu2Dst0h_D0gamma()));
      N_Delta_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Delta_Bu2Dst0h_D0gamma_FAVasSUP_",
              *N_Bu2Dst0h_D0gamma_FAVasSUP_,
              NeutralVars<neutral>::Get(uniqueId)
                  .buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP()));
    }
  }
  if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
      daughters != Daughters::kpi) {
    N_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        MakeYield<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bs2Dst0Kpi_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .N_tot_Bs2Dst0Kpi(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .A_Bs2Dst0Kpi()));
    N_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        MakeYield<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bs2D0Kpi_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .N_tot_Bs2D0Kpi(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .A_Bs2D0Kpi()));
    N_Delta_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Delta_Bs2Dst0Kpi_", *N_Bs2Dst0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
                .buDeltaCutEffBs2Dst0Kpi()));
    N_Delta_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Delta_Bs2D0Kpi_", *N_Bs2D0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
                .buDeltaCutEffBs2D0Kpi()));
  }
  if (neutral == Neutral::gamma) {
    N_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        MakeYield<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .A_Bu2Dst0h_D0gamma()));
    N_Delta_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Delta_Bu2Dst0h_D0gamma_", *N_Bu2Dst0h_D0gamma_,
            NeutralVars<neutral>::Get(uniqueId)
                .buDeltaCutEffBu2Dst0h_D0gamma()));
  }
  // If fit only in 1D but also fit in buPartial dimn, still need to calculare
  // Bu and BuPartial as a fn of N_
  if (Configuration::Get().fit1D() == false ||
      Configuration::Get().fitBuPartial() == true) {
    if (neutral == Neutral::gamma) {
      N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Bu_Bu2Dst0h_D0gamma_", *N_Bu2Dst0h_D0gamma_,
              NeutralVars<neutral>::Get(uniqueId)
                  .deltaCutEffBu2Dst0h_D0gamma()));
    }
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu_Bu2Dst0h_D0pi0_", *N_Bu2Dst0h_D0pi0_,
            NeutralVars<neutral>::Get(uniqueId).deltaCutEffBu2Dst0h_D0pi0()));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu_MisRec_", *N_MisRec_,
            NeutralVars<neutral>::Get(uniqueId).deltaCutEffMisRec()));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu_Bu2D0h_", *N_Bu2D0h_,
            NeutralVars<neutral>::Get(uniqueId).deltaCutEffBu2D0h()));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu_PartRec_", *N_PartRec_,
            NeutralVars<neutral>::Get(uniqueId).deltaCutEffPartRec()));
    if (daughters == Daughters::pik) {
      N_Bu_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Bu_Bu2Dst0h_D0pi0_FAVasSUP_",
              *N_Bu2Dst0h_D0pi0_FAVasSUP_,
              NeutralVars<neutral>::Get(uniqueId)
                  .deltaCutEffBu2Dst0h_D0pi0_FAVasSUP()));
      if (neutral == Neutral::gamma) {
        N_Bu_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
            MakeYield1D<neutral, bachelor, daughters, charge>(
                uniqueId, "N_Bu_Bu2Dst0h_D0gamma_FAVasSUP_",
                *N_Bu2Dst0h_D0gamma_FAVasSUP_,
                NeutralVars<neutral>::Get(uniqueId)
                    .deltaCutEffBu2Dst0h_D0gamma_FAVasSUP()));
      }
    }
    if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
        daughters != Daughters::kpi) {
      N_Bu_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Bu_Bs2Dst0Kpi_", *N_Bs2Dst0Kpi_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
                  .deltaCutEffBs2Dst0Kpi()));
      N_Bu_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Bu_Bs2D0Kpi_", *N_Bs2D0Kpi_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
                  .deltaCutEffBs2D0Kpi()));
    }
    if (Configuration::Get().fitBuPartial() == true) {
      N_BuPartial_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_BuPartial_Bu2Dst0h_D0gamma_", *N_Bu2Dst0h_D0gamma_,
              NeutralVars<neutral>::Get(uniqueId)
                  .deltaPartialCutEffBu2Dst0h_D0gamma()));
      N_BuPartial_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_BuPartial_Bu2Dst0h_D0pi0_", *N_Bu2Dst0h_D0pi0_,
              NeutralVars<neutral>::Get(uniqueId)
                  .deltaPartialCutEffBu2Dst0h_D0pi0()));
      N_BuPartial_MisRec_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_BuPartial_MisRec_", *N_MisRec_,
              NeutralVars<neutral>::Get(uniqueId).deltaPartialCutEffMisRec()));
      N_BuPartial_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_BuPartial_Bu2D0h_", *N_Bu2D0h_,
              NeutralVars<neutral>::Get(uniqueId).deltaPartialCutEffBu2D0h()));
      N_BuPartial_PartRec_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_BuPartial_PartRec_", *N_PartRec_,
              NeutralVars<neutral>::Get(uniqueId).deltaPartialCutEffPartRec()));
      if (daughters == Daughters::pik) {
        N_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
            MakeYield1D<neutral, bachelor, daughters, charge>(
                uniqueId, "N_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_",
                *N_Bu2Dst0h_D0pi0_FAVasSUP_,
                NeutralVars<neutral>::Get(uniqueId)
                    .deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP()));
      }
      if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
          daughters != Daughters::kpi) {
        N_BuPartial_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
            MakeYield1D<neutral, bachelor, daughters, charge>(
                uniqueId, "N_BuPartial_Bs2Dst0Kpi_", *N_Bs2Dst0Kpi_,
                NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
                    .deltaPartialCutEffBs2Dst0Kpi()));
        N_BuPartial_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
            MakeYield1D<neutral, bachelor, daughters, charge>(
                uniqueId, "N_BuPartial_Bs2D0Kpi_", *N_Bs2D0Kpi_,
                NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
                    .deltaPartialCutEffBs2D0Kpi()));
      }
    }
  } else {
    if (neutral == Neutral::gamma) {
      N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Bu_Bu2Dst0h_D0gamma_", *N_Bu2Dst0h_D0gamma_));
    }
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu_Bu2Dst0h_D0pi0_", *N_Bu2Dst0h_D0pi0_));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu_MisRec_", *N_MisRec_));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu_Bu2D0h_", *N_Bu2D0h_));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(
        MakeYield1D<neutral, bachelor, daughters, charge>(
            uniqueId, "N_Bu_PartRec_", *N_PartRec_));
    if (daughters == Daughters::pik) {
      N_Bu_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Bu_Bu2Dst0h_D0pi0_FAVasSUP_",
              *N_Bu2Dst0h_D0pi0_FAVasSUP_));
      if (neutral == Neutral::gamma) {
        N_Bu_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
            MakeYield1D<neutral, bachelor, daughters, charge>(
                uniqueId, "N_Bu_Bu2Dst0h_D0gamma_FAVasSUP_",
                *N_Bu2Dst0h_D0gamma_FAVasSUP_));
      }
    }
    if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
        daughters != Daughters::kpi) {
      N_Bu_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Bu_Bs2Dst0Kpi_", *N_Bs2Dst0Kpi_));
      N_Bu_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
          MakeYield1D<neutral, bachelor, daughters, charge>(
              uniqueId, "N_Bu_Bs2D0Kpi_", *N_Bs2D0Kpi_));
    }
  }
}
