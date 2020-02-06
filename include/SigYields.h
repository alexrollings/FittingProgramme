#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
class SigYields {
 public:
  SigYields(int uniqueId_);
  ~SigYields() {}

  using This_t = SigYields<neutral, bachelor, daughters, charge>;

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
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooFormulaVar &N_Bu2Dst0h_D0pi0() { return *N_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0pi0() { return *N_Delta_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_Bu_Bu2Dst0h_D0pi0() { return *N_Bu_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_BuPartial_Bu2Dst0h_D0pi0() {
    return *N_BuPartial_Bu2Dst0h_D0pi0_;
  }

 private:
  int uniqueId_;
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0gamma_;
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0pi0_;
};

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
SigYields<neutral, bachelor, daughters, charge>::SigYields(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : N_Bu2Dst0h_D0gamma_(nullptr),
      N_Delta_Bu2Dst0h_D0gamma_(nullptr),
      N_Bu_Bu2Dst0h_D0gamma_(nullptr),
      N_BuPartial_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      N_Bu2Dst0h_D0pi0_(nullptr),
      N_Delta_Bu2Dst0h_D0pi0_(nullptr),
      N_Bu_Bu2Dst0h_D0pi0_(nullptr),
      N_BuPartial_Bu2Dst0h_D0pi0_(nullptr) {
  if (charge == Charge::plus) {
    if (neutral == Neutral::gamma) {
      N_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "(@0/2)*(1-@1)",
          RooArgList(
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId)
                  .A_Bu2Dst0h_D0gamma())));
    }
    N_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "(@0/2)*(1-@1)",
        RooArgList(
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .N_tot_Bu2Dst0h_D0pi0(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .A_Bu2Dst0h_D0pi0())));
  } else if (charge == Charge::minus) {
    if (neutral == Neutral::gamma) {
      N_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "(@0/2)*(1+@1)",
          RooArgList(
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId)
                  .A_Bu2Dst0h_D0gamma())));
    }
    N_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "(@0/2)*(1+@1)",
        RooArgList(
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .N_tot_Bu2Dst0h_D0pi0(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .A_Bu2Dst0h_D0pi0())));
  } else {
    if (neutral == Neutral::gamma) {
      N_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "@0",
          RooArgList(
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId)
                  .N_tot_Bu2Dst0h_D0gamma())));
    }
    N_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "@0",
        RooArgList(
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId)
                .N_tot_Bu2Dst0h_D0pi0())));
  }
  if (neutral == Neutral::gamma) {
    N_Delta_Bu2Dst0h_D0gamma_ =
        std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
            ("N_Delta_Bu2Dst0h_D0gamma_" +
             ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                .c_str(),
            "(@0/@1)*@2*@3",
            RooArgList(
                NeutralVars<neutral>::Get(uniqueId)
                    .buDeltaCutEffBu2Dst0h_D0gamma(),
                NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
                *N_Bu2Dst0h_D0gamma_,
                Configuration::Get().GetPidEff(bachelor))));
  }
  N_Delta_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("N_Delta_Bu2Dst0h_D0pi0_" +
       ComposeName(uniqueId, neutral, bachelor, daughters, charge))
          .c_str(),
      "(@0/@1)*@2*@3",
      RooArgList(
          NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffBu2Dst0h_D0pi0(),
          NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
          *N_Bu2Dst0h_D0pi0_, Configuration::Get().GetPidEff(bachelor))));

  // If fit only in 1D but also fit in buPartial dimn, still need to calculare
  // Bu and BuPartial as a fn of N_
  if (Configuration::Get().fit1D() == false ||
      Configuration::Get().fitBuPartial() == true) {
    if (neutral == Neutral::gamma) {
      N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(
              NeutralVars<neutral>::Get(uniqueId).deltaCutEffBu2Dst0h_D0gamma(),
              NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
              *N_Bu2Dst0h_D0gamma_, Configuration::Get().GetPidEff(bachelor))));
    }
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "(@0/@1)*@2*@3",
        RooArgList(
            NeutralVars<neutral>::Get(uniqueId).deltaCutEffBu2Dst0h_D0pi0(),
            NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
            *N_Bu2Dst0h_D0pi0_, Configuration::Get().GetPidEff(bachelor))));
    if (Configuration::Get().fitBuPartial() == true) {
      N_BuPartial_Bu2Dst0h_D0gamma_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_BuPartial_Bu2Dst0h_D0gamma_" +
               ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                  .c_str(),
              "(@0/@1)*@2*@3",
              RooArgList(
                  NeutralVars<neutral>::Get(uniqueId)
                      .deltaPartialCutEffBu2Dst0h_D0gamma(),
                  NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
                  *N_Bu2Dst0h_D0gamma_,
                  Configuration::Get().GetPidEff(bachelor))));
      N_BuPartial_Bu2Dst0h_D0pi0_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_BuPartial_Bu2Dst0h_D0pi0_" +
               ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                  .c_str(),
              "(@0/@1)*@2*@3",
              RooArgList(
                  NeutralVars<neutral>::Get(uniqueId)
                      .deltaPartialCutEffBu2Dst0h_D0pi0(),
                  NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
                  *N_Bu2Dst0h_D0pi0_,
                  Configuration::Get().GetPidEff(bachelor))));
    }
  } else {
    if (neutral == Neutral::gamma) {
      N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_Bu_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "@0*@1",
          RooArgList(*N_Bu2Dst0h_D0gamma_,
                     Configuration::Get().GetPidEff(bachelor))));
    }
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_Bu2Dst0h_D0pi0_,
                   Configuration::Get().GetPidEff(bachelor))));
  }
}
