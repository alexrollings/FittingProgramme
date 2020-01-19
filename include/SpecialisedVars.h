#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
class SpecialisedVars {
 public:
  SpecialisedVars(int uniqueId_);
  ~SpecialisedVars() {}

  using This_t = SpecialisedVars<neutral, bachelor, daughters, charge>;

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
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooFormulaVar &N_Bu2Dst0h_D0pi0() { return *N_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0pi0() { return *N_Delta_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_Bu_Bu2Dst0h_D0pi0() { return *N_Bu_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_BuPartial_Bu2Dst0h_D0pi0() {
    return *N_BuPartial_Bu2Dst0h_D0pi0_;
  }
  // -------------------- Mis-ID ------------------- //
  // -------------------- MIS-REC -------------------- //
  // RooRealVar &N_MisRec() { return *N_MisRec_; }
  RooAbsReal &N_MisRec() { return *N_MisRec_; }
  RooFormulaVar &N_Delta_MisRec() { return *N_Delta_MisRec_; }
  RooAbsReal &N_Bu_MisRec() { return *N_Bu_MisRec_; }
  RooAbsReal &N_BuPartial_MisRec() { return *N_BuPartial_MisRec_; }
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2D0h -------------------- //
  RooRealVar &N_Bu2D0h() { return *N_Bu2D0h_; }
  RooFormulaVar &N_Delta_Bu2D0h() { return *N_Delta_Bu2D0h_; }
  RooAbsReal &N_Bu_Bu2D0h() { return *N_Bu_Bu2D0h_; }
  RooAbsReal &N_BuPartial_Bu2D0h() { return *N_BuPartial_Bu2D0h_; }
  // -------------------- Mis-ID ------------------- //
  // -------------------- PART REC -------------------- //
  RooRealVar &N_PartRec() { return *N_PartRec_; }
  RooFormulaVar &N_Delta_PartRec() { return *N_Delta_PartRec_; }
  RooAbsReal &N_Bu_PartRec() { return *N_Bu_PartRec_; }
  RooAbsReal &N_BuPartial_PartRec() { return *N_BuPartial_PartRec_; }

 private:
  int uniqueId_;
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- MIS-REC -------------------- //
  // std::unique_ptr<RooRealVar> N_MisRec_;
  std::unique_ptr<RooAbsReal> N_MisRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_MisRec_;
  std::unique_ptr<RooAbsReal> N_Bu_MisRec_;
  std::unique_ptr<RooAbsReal> N_BuPartial_MisRec_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2D0h -------------------- //
  std::unique_ptr<RooRealVar> N_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2D0h_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- PART REC -------------------- //
  std::unique_ptr<RooRealVar> N_PartRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_PartRec_;
  std::unique_ptr<RooAbsReal> N_Bu_PartRec_;
  std::unique_ptr<RooAbsReal> N_BuPartial_PartRec_;
};

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
SpecialisedVars<neutral, bachelor, daughters, charge>::SpecialisedVars(
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
      N_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- MisRec -------------------- //
      // N_MisRec_(new RooRealVar(
      //     ("N_MisRec_" +
      //      ComposeName(uniqueId, neutral, bachelor, daughters, charge))
      //         .c_str(),
      //     "",
      //     NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
      //             .N_initVal_MisRec() *
      //         DaughtersVars<daughters>::Get(uniqueId).daughtersSF(),
      //      -1000000, 1000000)),
      // N_Delta_MisRec_(new RooFormulaVar(
      //     ("N_Delta_MisRec_" +
      //      ComposeName(uniqueId, neutral, bachelor, daughters, charge))
      //         .c_str(),
      //     "(@0/@1)*@2*@3",
      //     RooArgList(NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffMisRec(),
      //                NeutralVars<neutral>::Get(uniqueId).orEffMisRec(),
      //                *N_MisRec_, Configuration::Get().GetPidEff(bachelor)))),
      N_MisRec_(nullptr),
      N_Delta_MisRec_(nullptr),
      N_Bu_MisRec_(nullptr),
      N_BuPartial_MisRec_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      N_Bu2D0h_(new RooRealVar(
          ("N_Bu2D0h_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "",
          NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
                  .N_initVal_Bu2D0h() *
              DaughtersVars<daughters>::Get(uniqueId).daughtersSF(),
          -1000000, 1000000)),
      N_Delta_Bu2D0h_(new RooFormulaVar(
          ("N_Delta_Bu2D0h_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffBu2D0h(),
                     NeutralVars<neutral>::Get(uniqueId).orEffBu2D0h(),
                     *N_Bu2D0h_, Configuration::Get().GetPidEff(bachelor)))),
      N_Bu_Bu2D0h_(nullptr),
      N_BuPartial_Bu2D0h_(nullptr),
      // -------------------- PartRec -------------------- //
      N_PartRec_(new RooRealVar(
          ("N_PartRec_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "",
          NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
                  .N_initVal_PartRec() *
              DaughtersVars<daughters>::Get(uniqueId).daughtersSF(),
          -1000000, 1000000)),
      N_Delta_PartRec_(new RooFormulaVar(
          ("N_Delta_PartRec_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffPartRec(),
                     NeutralVars<neutral>::Get(uniqueId).orEffPartRec(),
                     *N_PartRec_, Configuration::Get().GetPidEff(bachelor)))),
      N_Bu_PartRec_(nullptr),
      N_BuPartial_PartRec_(nullptr) {
  double misRecYield;
  if (neutral == Neutral::pi0) {
    if (bachelor == Bachelor::pi) {
      if (daughters == Daughters::kpi) {
        misRecYield = 2.0735e+04;
      } else if (daughters == Daughters::kk) {
        misRecYield = 2.8971e+03;
      } else {
        misRecYield = 8.2089e+02;
      }
    } else {
      if (daughters == Daughters::kpi) {
        misRecYield = 1.6088e+03;
      } else if (daughters == Daughters::kk) {
        misRecYield = 2.1535e+02;
      } else {
        misRecYield = 8.4610e+01;
      }
    }
  } else {
    if (bachelor == Bachelor::pi) {
      if (daughters == Daughters::kpi) {
        misRecYield = 1.0452e+05;
      } else if (daughters == Daughters::kk) {
        misRecYield = 1.5522e+04;
      } else {
        misRecYield = 4.3455e+03;
      }
    } else {
      if (daughters == Daughters::kpi) {
        misRecYield = 6.3835e+03;
      } else if (daughters == Daughters::kk) {
        misRecYield = 1.1562e+03;
      } else {
        misRecYield = 4.7371e+02;
      }
    }
  }
  // if (bachelor == Bachelor::pi) {
    N_MisRec_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_MisRec_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
                .N_initVal_MisRec() *
            DaughtersVars<daughters>::Get(uniqueId).daughtersSF(),
        -1000000, 1000000));
  // } else {
    // N_MisRec_ = std::unique_ptr<RooConstVar>(new RooConstVar(
    //     ("N_MisRec_" +
    //      ComposeName(uniqueId, neutral, bachelor, daughters, charge))
    //         .c_str(),
    //     "", misRecYield));
  // }
  N_Delta_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("N_Delta_MisRec_" +
       ComposeName(uniqueId, neutral, bachelor, daughters, charge))
          .c_str(),
      "(@0/@1)*@2*@3",
      RooArgList(NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffMisRec(),
                 NeutralVars<neutral>::Get(uniqueId).orEffMisRec(), *N_MisRec_,
                 Configuration::Get().GetPidEff(bachelor))));
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
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "(@0/@1)*@2*@3",
        RooArgList(NeutralVars<neutral>::Get(uniqueId).deltaCutEffMisRec(),
                   NeutralVars<neutral>::Get(uniqueId).orEffMisRec(),
                   *N_MisRec_, Configuration::Get().GetPidEff(bachelor))));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "(@0/@1)*@2*@3",
        RooArgList(NeutralVars<neutral>::Get(uniqueId).deltaCutEffBu2D0h(),
                   NeutralVars<neutral>::Get(uniqueId).orEffBu2D0h(),
                   *N_Bu2D0h_, Configuration::Get().GetPidEff(bachelor))));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "(@0/@1)*@2*@3",
        RooArgList(NeutralVars<neutral>::Get(uniqueId).deltaCutEffPartRec(),
                   NeutralVars<neutral>::Get(uniqueId).orEffPartRec(),
                   *N_PartRec_, Configuration::Get().GetPidEff(bachelor))));
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
      N_BuPartial_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_BuPartial_MisRec_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(
              NeutralVars<neutral>::Get(uniqueId).deltaPartialCutEffMisRec(),
              NeutralVars<neutral>::Get(uniqueId).orEffMisRec(), *N_MisRec_,
              Configuration::Get().GetPidEff(bachelor))));
      N_BuPartial_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_BuPartial_Bu2D0h_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(
              NeutralVars<neutral>::Get(uniqueId).deltaPartialCutEffBu2D0h(),
              NeutralVars<neutral>::Get(uniqueId).orEffBu2D0h(), *N_Bu2D0h_,
              Configuration::Get().GetPidEff(bachelor))));
      N_BuPartial_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_BuPartial_PartRec_" +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(
              NeutralVars<neutral>::Get(uniqueId).deltaPartialCutEffPartRec(),
              NeutralVars<neutral>::Get(uniqueId).orEffPartRec(), *N_PartRec_,
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
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_MisRec_, Configuration::Get().GetPidEff(bachelor))));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_Bu2D0h_, Configuration::Get().GetPidEff(bachelor))));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" +
         ComposeName(uniqueId, neutral, bachelor, daughters, charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_PartRec_, Configuration::Get().GetPidEff(bachelor))));
  }
}
