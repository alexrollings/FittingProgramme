#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "RooUnblindUniform.h"

template <Neutral neutral, Bachelor bachelor, Charge charge>
class NeutralBachelorChargeVars {
 public:
  NeutralBachelorChargeVars(int uniqueId_);
  ~NeutralBachelorChargeVars() {}

  using This_t = NeutralBachelorChargeVars<neutral, bachelor, charge>;

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
  RooFormulaVar &N_Delta_Bu2Dst0h_D0gamma() {
    return *N_Delta_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_Bu_Bu2Dst0h_D0gamma() { return *N_Bu_Bu2Dst0h_D0gamma_; }
  RooAbsReal &N_BuPartial_Bu2Dst0h_D0gamma() {
    return *N_BuPartial_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooFormulaVar &N_Delta_Bu2Dst0h_D0pi0() { return *N_Delta_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_Bu_Bu2Dst0h_D0pi0() { return *N_Bu_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_BuPartial_Bu2Dst0h_D0pi0() {
    return *N_BuPartial_Bu2Dst0h_D0pi0_;
  }
  // -------------------- Mis-ID ------------------- //
  // -------------------- MIS-REC -------------------- //
  RooRealVar &N_MisRec() { return *N_MisRec_; }
  RooFormulaVar &N_Delta_MisRec() { return *N_Delta_MisRec_; }
  RooAbsReal &N_Bu_MisRec() { return *N_Bu_MisRec_; }
  RooAbsReal &N_BuPartial_MisRec() { return *N_BuPartial_MisRec_; }
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2D0h -------------------- //
  RooAbsReal &N_Bu2D0h() { return *N_Bu2D0h_; }
  RooAbsReal &N_Bu2D0h_Blind() { return *N_Bu2D0h_Blind_; }
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
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- MIS-REC -------------------- //
  std::unique_ptr<RooRealVar> N_MisRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_MisRec_;
  std::unique_ptr<RooAbsReal> N_Bu_MisRec_;
  std::unique_ptr<RooAbsReal> N_BuPartial_MisRec_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2D0h -------------------- //
  std::unique_ptr<RooAbsReal> N_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_Bu2D0h_Blind_;
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

template <Neutral neutral, Bachelor bachelor, Charge charge>
NeutralBachelorChargeVars<neutral, bachelor, charge>::NeutralBachelorChargeVars(
    int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : N_Delta_Bu2Dst0h_D0gamma_(new RooFormulaVar(
          ("N_Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, neutral, bachelor, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(
              NeutralVars<neutral>::Get(uniqueId)
                  .buDeltaCutEffBu2Dst0h_D0gamma(),
              NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
              NeutralBachelorDaughtersVars<neutral, bachelor,
                                           Daughters::kpi>::Get(uniqueId)
                  .N_Bu2Dst0h_D0gamma(),
              Configuration::Get().GetPidEff(bachelor)))),
      N_Bu_Bu2Dst0h_D0gamma_(nullptr),
      N_BuPartial_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      N_Delta_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, neutral, bachelor, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(
              NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffBu2Dst0h_D0pi0(),
              NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
              NeutralBachelorDaughtersVars<neutral, bachelor,
                                           Daughters::kpi>::Get(uniqueId)
                  .N_Bu2Dst0h_D0pi0(),
              Configuration::Get().GetPidEff(bachelor)))),
      N_Bu_Bu2Dst0h_D0pi0_(nullptr),
      N_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- MisRec -------------------- //
      N_MisRec_(new RooRealVar(
          ("N_MisRec_" + ComposeName(uniqueId, neutral, bachelor, charge))
              .c_str(),
          "",
          NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
              .N_tot_initVal_MisRec(),
          0, 1000000)),
      N_Delta_MisRec_(new RooFormulaVar(
          ("N_Delta_MisRec_" + ComposeName(uniqueId, neutral, bachelor, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffMisRec(),
                     NeutralVars<neutral>::Get(uniqueId).orEffMisRec(),
                     *N_MisRec_, Configuration::Get().GetPidEff(bachelor)))),
      N_Bu_MisRec_(nullptr),
      N_BuPartial_MisRec_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      // N_Bu2D0h_(new RooRealVar(
      //     ("N_Bu2D0h_" +
      //      ComposeName(uniqueId, neutral, bachelor, charge))
      //         .c_str(),
      //     "", NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
      //             .N_tot_initVal_Bu2D0h(),
      //     0, 1000000)),
      // N_Delta_Bu2D0h_(new RooFormulaVar(
      //     ("N_Delta_Bu2D0h_" +
      //      ComposeName(uniqueId, neutral, bachelor, charge))
      //         .c_str(),
      //     "(@0/@1)*@2*@3",
      //     RooArgList(NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffBu2D0h(),
      //                NeutralVars<neutral>::Get(uniqueId).orEffBu2D0h(),
      //                *N_Bu2D0h_,
      //                Configuration::Get().GetPidEff(bachelor)))),
      N_Bu2D0h_(nullptr),
      N_Bu2D0h_Blind_(nullptr),
      N_Delta_Bu2D0h_(nullptr),
      N_Bu_Bu2D0h_(nullptr),
      N_BuPartial_Bu2D0h_(nullptr),
      // -------------------- PartRec -------------------- //
      N_PartRec_(new RooRealVar(
          ("N_PartRec_" + ComposeName(uniqueId, neutral, bachelor, charge))
              .c_str(),
          "",
          NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
              .N_tot_initVal_PartRec(),
          0, 1000000)),
      N_Delta_PartRec_(new RooFormulaVar(
          ("N_Delta_PartRec_" +
           ComposeName(uniqueId, neutral, bachelor, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffPartRec(),
                     NeutralVars<neutral>::Get(uniqueId).orEffPartRec(),
                     *N_PartRec_, Configuration::Get().GetPidEff(bachelor)))),
      N_Bu_PartRec_(nullptr),
      N_BuPartial_PartRec_(nullptr) {
  if (Configuration::Get().blindFit() == true) {
    N_Bu2D0h_Blind_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Bu2D0h_Blind_" + ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "",
        NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
            .N_tot_initVal_Bu2D0h(),
        0, 1000000));
    // Scale = scale of offset, ~5% expected value
    int blindScale = 150;
    if (bachelor == Bachelor::k) {
      int blindScale = 12;
    }
    N_Bu2D0h_ = std::unique_ptr<RooUnblindUniform>(new RooUnblindUniform(
        ("N_Bu2D0h_" + ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "Blind", "Blind", blindScale, *N_Bu2D0h_Blind_));
  } else {
    N_Bu2D0h_ = std::unique_ptr<RooRealVar>(new RooRealVar(
        ("N_Bu2D0h_" + ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "",
        NeutralBachelorVars<neutral, bachelor>::Get(uniqueId)
            .N_tot_initVal_Bu2D0h(),
        0, 1000000));
  }
  N_Delta_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("N_Delta_Bu2D0h_" + ComposeName(uniqueId, neutral, bachelor, charge))
          .c_str(),
      "(@0/@1)*@2*@3",
      RooArgList(NeutralVars<neutral>::Get(uniqueId).buDeltaCutEffBu2D0h(),
                 NeutralVars<neutral>::Get(uniqueId).orEffBu2D0h(), *N_Bu2D0h_,
                 Configuration::Get().GetPidEff(bachelor))));
  // If fit only in 1D but also fit in buPartial dimn, still need to calculare
  // Bu and BuPartial as a fn of N_
  if (Configuration::Get().fit1D() == false ||
      Configuration::Get().fitBuPartial() == true) {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "(@0/@1)*@2*@3",
        RooArgList(
            NeutralVars<neutral>::Get(uniqueId).deltaCutEffBu2Dst0h_D0gamma(),
            NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
            NeutralBachelorDaughtersVars<neutral, bachelor,
                                         Daughters::kpi>::Get(uniqueId)
                .N_Bu2Dst0h_D0gamma(),
            Configuration::Get().GetPidEff(bachelor))));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "(@0/@1)*@2*@3",
        RooArgList(
            NeutralVars<neutral>::Get(uniqueId).deltaCutEffBu2Dst0h_D0pi0(),
            NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
            NeutralBachelorDaughtersVars<neutral, bachelor,
                                         Daughters::kpi>::Get(uniqueId)
                .N_Bu2Dst0h_D0pi0(),
            Configuration::Get().GetPidEff(bachelor))));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "(@0/@1)*@2*@3",
        RooArgList(NeutralVars<neutral>::Get(uniqueId).deltaCutEffMisRec(),
                   NeutralVars<neutral>::Get(uniqueId).orEffMisRec(),
                   *N_MisRec_, Configuration::Get().GetPidEff(bachelor))));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "(@0/@1)*@2*@3",
        RooArgList(NeutralVars<neutral>::Get(uniqueId).deltaCutEffBu2D0h(),
                   NeutralVars<neutral>::Get(uniqueId).orEffBu2D0h(),
                   *N_Bu2D0h_, Configuration::Get().GetPidEff(bachelor))));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" + ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "(@0/@1)*@2*@3",
        RooArgList(NeutralVars<neutral>::Get(uniqueId).deltaCutEffPartRec(),
                   NeutralVars<neutral>::Get(uniqueId).orEffPartRec(),
                   *N_PartRec_, Configuration::Get().GetPidEff(bachelor))));
    if (Configuration::Get().fitBuPartial() == true) {
      N_BuPartial_Bu2Dst0h_D0gamma_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_BuPartial_Bu2Dst0h_D0gamma_" +
               ComposeName(uniqueId, neutral, bachelor, charge))
                  .c_str(),
              "(@0/@1)*@2*@3",
              RooArgList(
                  NeutralVars<neutral>::Get(uniqueId)
                      .deltaPartialCutEffBu2Dst0h_D0gamma(),
                  NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
                  NeutralBachelorDaughtersVars<neutral, bachelor,
                                               Daughters::kpi>::Get(uniqueId)
                      .N_Bu2Dst0h_D0gamma(),
                  Configuration::Get().GetPidEff(bachelor))));
      N_BuPartial_Bu2Dst0h_D0pi0_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_BuPartial_Bu2Dst0h_D0pi0_" +
               ComposeName(uniqueId, neutral, bachelor, charge))
                  .c_str(),
              "(@0/@1)*@2*@3",
              RooArgList(
                  NeutralVars<neutral>::Get(uniqueId)
                      .deltaPartialCutEffBu2Dst0h_D0pi0(),
                  NeutralVars<neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
                  NeutralBachelorDaughtersVars<neutral, bachelor,
                                               Daughters::kpi>::Get(uniqueId)
                      .N_Bu2Dst0h_D0pi0(),
                  Configuration::Get().GetPidEff(bachelor))));
      N_BuPartial_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_BuPartial_MisRec_" +
           ComposeName(uniqueId, neutral, bachelor, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(
              NeutralVars<neutral>::Get(uniqueId).deltaPartialCutEffMisRec(),
              NeutralVars<neutral>::Get(uniqueId).orEffMisRec(), *N_MisRec_,
              Configuration::Get().GetPidEff(bachelor))));
      N_BuPartial_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_BuPartial_Bu2D0h_" +
           ComposeName(uniqueId, neutral, bachelor, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(
              NeutralVars<neutral>::Get(uniqueId).deltaPartialCutEffBu2D0h(),
              NeutralVars<neutral>::Get(uniqueId).orEffBu2D0h(), *N_Bu2D0h_,
              Configuration::Get().GetPidEff(bachelor))));
      N_BuPartial_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_BuPartial_PartRec_" +
           ComposeName(uniqueId, neutral, bachelor, charge))
              .c_str(),
          "(@0/@1)*@2*@3",
          RooArgList(
              NeutralVars<neutral>::Get(uniqueId).deltaPartialCutEffPartRec(),
              NeutralVars<neutral>::Get(uniqueId).orEffPartRec(), *N_PartRec_,
              Configuration::Get().GetPidEff(bachelor))));
    }
  } else {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "@0*@1",
        RooArgList(NeutralBachelorDaughtersVars<neutral, bachelor,
                                                Daughters::kpi>::Get(uniqueId)
                       .N_Bu2Dst0h_D0gamma(),
                   Configuration::Get().GetPidEff(bachelor))));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "@0*@1",
        RooArgList(NeutralBachelorDaughtersVars<neutral, bachelor,
                                                Daughters::kpi>::Get(uniqueId)
                       .N_Bu2Dst0h_D0pi0(),
                   Configuration::Get().GetPidEff(bachelor))));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_MisRec_, Configuration::Get().GetPidEff(bachelor))));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_Bu2D0h_, Configuration::Get().GetPidEff(bachelor))));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" + ComposeName(uniqueId, neutral, bachelor, charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_PartRec_, Configuration::Get().GetPidEff(bachelor))));
  }
}
