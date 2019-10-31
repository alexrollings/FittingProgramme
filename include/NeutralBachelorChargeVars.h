#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooCruijff.h"
#include "RooFormulaVar.h"
#include "RooProdPdf.h"

namespace {  // Anonymous namespace

template <Neutral neutral, Bachelor bachelor, Charge charge>
struct NeutralBachelorChargeVarsImpl;

template <Neutral neutral, Charge charge>
struct NeutralBachelorChargeVarsImpl<neutral, Bachelor::pi, charge> {
  NeutralBachelorChargeVarsImpl(int uniqueId);
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- MIS-REC -------------------- //
  std::unique_ptr<RooRealVar> N_tot_MisRec_;
  std::unique_ptr<RooFormulaVar> N_MisRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_MisRec_;
  std::unique_ptr<RooAbsReal> N_Bu_MisRec_;
  std::unique_ptr<RooAbsReal> N_BuPartial_MisRec_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2D0h -------------------- //
  std::unique_ptr<RooRealVar> N_tot_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2D0h_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- PART REC -------------------- //
  std::unique_ptr<RooRealVar> N_tot_PartRec_;
  std::unique_ptr<RooFormulaVar> N_PartRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_PartRec_;
  std::unique_ptr<RooAbsReal> N_Bu_PartRec_;
  // -------------------- Mis-ID ------------------- //
};

template <Neutral neutral, Charge charge>
struct NeutralBachelorChargeVarsImpl<neutral, Bachelor::k, charge> {
  NeutralBachelorChargeVarsImpl(int uniqueId);
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  std::unique_ptr<RooRealVar> N_tot_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_BuPartial_Bu2Dst0h_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- MIS-REC -------------------- //
  std::unique_ptr<RooRealVar> N_tot_MisRec_;
  std::unique_ptr<RooFormulaVar> N_MisRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_MisRec_;
  std::unique_ptr<RooAbsReal> N_Bu_MisRec_;
  std::unique_ptr<RooAbsReal> N_BuPartial_MisRec_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2D0h -------------------- //
  std::unique_ptr<RooRealVar> N_tot_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_Delta_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2D0h_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- PART REC -------------------- //
  std::unique_ptr<RooRealVar> N_tot_PartRec_;
  std::unique_ptr<RooFormulaVar> N_PartRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_PartRec_;
  std::unique_ptr<RooAbsReal> N_Bu_PartRec_;
  // -------------------- Mis-ID ------------------- //
};
}  // namespace

template <Neutral neutral, Bachelor bachelor, Charge charge>
class NeutralBachelorChargeVars {
 public:
  NeutralBachelorChargeVars(int uniqueId_) : impl_(uniqueId_) {}
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
  RooRealVar &N_tot_Bu2Dst0h_D0gamma() {
    return *impl_.N_tot_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_Bu2Dst0h_D0gamma() { return *impl_.N_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0gamma() {
    return *impl_.N_Delta_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_Bu_Bu2Dst0h_D0gamma() { return *impl_.N_Bu_Bu2Dst0h_D0gamma_; }
  RooAbsReal &N_BuPartial_Bu2Dst0h_D0gamma() {
    return *impl_.N_BuPartial_Bu2Dst0h_D0gamma_;
  }
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar &N_tot_Bu2Dst0h_D0pi0() { return *impl_.N_tot_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Bu2Dst0h_D0pi0() { return *impl_.N_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0pi0() {
    return *impl_.N_Delta_Bu2Dst0h_D0pi0_;
  }
  RooAbsReal &N_Bu_Bu2Dst0h_D0pi0() { return *impl_.N_Bu_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_BuPartial_Bu2Dst0h_D0pi0() {
    return *impl_.N_BuPartial_Bu2Dst0h_D0pi0_;
  }
  // -------------------- Mis-ID ------------------- //
  // -------------------- MIS-REC -------------------- //
  RooRealVar &N_tot_MisRec() { return *impl_.N_tot_MisRec_; }
  RooFormulaVar &N_MisRec() { return *impl_.N_MisRec_; }
  RooFormulaVar &N_Delta_MisRec() { return *impl_.N_Delta_MisRec_; }
  RooAbsReal &N_Bu_MisRec() { return *impl_.N_Bu_MisRec_; }
  RooAbsReal &N_BuPartial_MisRec() { return *impl_.N_BuPartial_MisRec_; }
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2D0h -------------------- //
  RooRealVar &N_tot_Bu2D0h() { return *impl_.N_tot_Bu2D0h_; }
  RooFormulaVar &N_Bu2D0h() { return *impl_.N_Bu2D0h_; }
  RooFormulaVar &N_Delta_Bu2D0h() { return *impl_.N_Delta_Bu2D0h_; }
  RooAbsReal &N_Bu_Bu2D0h() { return *impl_.N_Bu_Bu2D0h_; }
  // -------------------- Mis-ID ------------------- //
  // -------------------- PART REC -------------------- //
  RooRealVar &N_tot_PartRec() { return *impl_.N_tot_PartRec_; }
  RooFormulaVar &N_PartRec() { return *impl_.N_PartRec_; }
  RooFormulaVar &N_Delta_PartRec() { return *impl_.N_Delta_PartRec_; }
  RooAbsReal &N_Bu_PartRec() { return *impl_.N_Bu_PartRec_; }

 private:
  int uniqueId_;
  NeutralBachelorChargeVarsImpl<neutral, bachelor, charge> impl_;
};

template <Neutral _neutral, Charge _charge>
NeutralBachelorChargeVarsImpl<_neutral, Bachelor::pi, _charge>::
    NeutralBachelorChargeVarsImpl(int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : N_tot_Bu2Dst0h_D0gamma_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0gamma(),
          0, 1000000)),
      N_Bu2Dst0h_D0gamma_(new RooFormulaVar(
          ("N_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "@0*@1",
          RooArgList(*N_tot_Bu2Dst0h_D0gamma_,
                     NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                         .pidEff_Bu2Dst0h_D0gamma()))),
      N_Delta_Bu2Dst0h_D0gamma_(new RooFormulaVar(
          ("N_Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<_neutral>::Get(uniqueId)
                                       .buDeltaCutEffBu2Dst0h_D0gamma(),
                                   NeutralVars<_neutral>::Get(uniqueId)
                                       .orEffBu2Dst0h_D0gamma(),
                                   *N_Bu2Dst0h_D0gamma_))),
      N_Bu_Bu2Dst0h_D0gamma_(nullptr),
      N_BuPartial_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      N_tot_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0(),
          0, 1000000)),
      N_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "@0*@1",
          RooArgList(*N_tot_Bu2Dst0h_D0pi0_,
                     NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                         .pidEff_Bu2Dst0h_D0pi0()))),
      N_Delta_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(NeutralVars<_neutral>::Get(uniqueId)
                         .buDeltaCutEffBu2Dst0h_D0pi0(),
                     NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
                     *N_Bu2Dst0h_D0pi0_))),
      N_Bu_Bu2Dst0h_D0pi0_(nullptr),
      N_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- MisRec -------------------- //
      N_tot_MisRec_(new RooRealVar(
          ("N_tot_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .N_tot_initVal_MisRec(),
          0, 1000000)),
      N_MisRec_(new RooFormulaVar(
          ("N_MisRec_" + ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "@0*@1",
          RooArgList(*N_tot_MisRec_,
                     NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                         .pidEff_MisRec()))),
      N_Delta_MisRec_(new RooFormulaVar(
          ("N_Delta_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(NeutralVars<_neutral>::Get(uniqueId).buDeltaCutEffMisRec(),
                     NeutralVars<_neutral>::Get(uniqueId).orEffMisRec(),
                     *N_MisRec_))),
      N_Bu_MisRec_(nullptr),
      N_BuPartial_MisRec_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      N_tot_Bu2D0h_(new RooRealVar(
          ("N_tot_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .N_tot_initVal_Bu2D0h(),
          0, 1000000)),
      N_Bu2D0h_(new RooFormulaVar(
          ("N_Bu2D0h_" + ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "@0*@1",
          RooArgList(*N_tot_Bu2D0h_,
                     NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                         .pidEff_Bu2D0h()))),
      N_Delta_Bu2D0h_(new RooFormulaVar(
          ("N_Delta_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(NeutralVars<_neutral>::Get(uniqueId).buDeltaCutEffBu2D0h(),
                     NeutralVars<_neutral>::Get(uniqueId).orEffBu2D0h(),
                     *N_Bu2D0h_))),
      N_Bu_Bu2D0h_(nullptr),
      // -------------------- PartRec -------------------- //
      N_tot_PartRec_(new RooRealVar(
          ("N_tot_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                  .N_tot_initVal_PartRec(),
          0, 1000000)),
      N_PartRec_(new RooFormulaVar(
          ("N_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "@0*@1",
          RooArgList(*N_tot_PartRec_,
                     NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                         .pidEff_PartRec()))),
      N_Delta_PartRec_(new RooFormulaVar(
          ("N_Delta_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<_neutral>::Get(uniqueId).buDeltaCutEffPartRec(),
              NeutralVars<_neutral>::Get(uniqueId).orEffPartRec(),
              *N_PartRec_))),
      N_Bu_PartRec_(nullptr) {
  if (Configuration::Get().fit1D() == false) {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<_neutral>::Get(uniqueId).deltaCutEffBu2Dst0h_D0gamma(),
            NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
            *N_Bu2Dst0h_D0gamma_)));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<_neutral>::Get(uniqueId).deltaCutEffBu2Dst0h_D0pi0(),
            NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
            *N_Bu2Dst0h_D0pi0_)));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(NeutralVars<_neutral>::Get(uniqueId).deltaCutEffMisRec(),
                   NeutralVars<_neutral>::Get(uniqueId).orEffMisRec(),
                   *N_MisRec_)));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(NeutralVars<_neutral>::Get(uniqueId).deltaCutEffBu2D0h(),
                   NeutralVars<_neutral>::Get(uniqueId).orEffBu2D0h(),
                   *N_Bu2D0h_)));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(NeutralVars<_neutral>::Get(uniqueId).deltaCutEffPartRec(),
                   NeutralVars<_neutral>::Get(uniqueId).orEffPartRec(),
                   *N_PartRec_)));
    if (_neutral == Neutral::gamma) {
      N_BuPartial_Bu2Dst0h_D0gamma_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_BuPartial_Bu2Dst0h_D0gamma_" +
               ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
                  .c_str(),
              "(@0/@1)*@2",
              RooArgList(
                  NeutralVars<_neutral>::Get(uniqueId)
                      .deltaPartialCutEffBu2Dst0h_D0gamma(),
                  NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
                  *N_Bu2Dst0h_D0gamma_)));
      N_BuPartial_Bu2Dst0h_D0pi0_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_BuPartial_Bu2Dst0h_D0pi0_" +
               ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
                  .c_str(),
              "(@0/@1)*@2",
              RooArgList(
                  NeutralVars<_neutral>::Get(uniqueId)
                      .deltaPartialCutEffBu2Dst0h_D0pi0(),
                  NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
                  *N_Bu2Dst0h_D0pi0_)));
      N_BuPartial_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_BuPartial_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<_neutral>::Get(uniqueId).deltaPartialCutEffMisRec(),
              NeutralVars<_neutral>::Get(uniqueId).orEffMisRec(), *N_MisRec_)));
    }
  } else {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_Bu2Dst0h_D0gamma_,
                   NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                       .pidEff_Bu2Dst0h_D0gamma())));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_Bu2Dst0h_D0pi0_,
                   NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                       .pidEff_Bu2Dst0h_D0pi0())));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_MisRec_,
                   NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                       .pidEff_MisRec())));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_Bu2D0h_,
                   NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                       .pidEff_Bu2D0h())));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::pi, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_PartRec_,
                   NeutralBachelorVars<_neutral, Bachelor::pi>::Get(uniqueId)
                       .pidEff_PartRec())));
  }
}

template <Neutral _neutral, Charge _charge>
NeutralBachelorChargeVarsImpl<
    _neutral, Bachelor::k, _charge>::NeutralBachelorChargeVarsImpl(int uniqueId)
    // -------------------- Bu2Dst0h_D0gamma -------------------- //
    : N_tot_Bu2Dst0h_D0gamma_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0gamma(),
          0, 1000000)),
      N_Bu2Dst0h_D0gamma_(new RooFormulaVar(
          ("N_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "@0*@1",
          RooArgList(*N_tot_Bu2Dst0h_D0gamma_,
                     NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                         .pidEff_Bu2Dst0h_D0gamma()))),
      N_Delta_Bu2Dst0h_D0gamma_(new RooFormulaVar(
          ("N_Delta_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "(@0/@1)*@2", RooArgList(NeutralVars<_neutral>::Get(uniqueId)
                                       .buDeltaCutEffBu2Dst0h_D0gamma(),
                                   NeutralVars<_neutral>::Get(uniqueId)
                                       .orEffBu2Dst0h_D0gamma(),
                                   *N_Bu2Dst0h_D0gamma_))),
      N_Bu_Bu2Dst0h_D0gamma_(nullptr),
      // -------------------- Bu2Dst0h_D0pi0 -------------------- //
      N_tot_Bu2Dst0h_D0pi0_(new RooRealVar(
          ("N_tot_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .N_tot_initVal_Bu2Dst0h_D0pi0(),
          0, 1000000)),
      N_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "@0*@1",
          RooArgList(*N_tot_Bu2Dst0h_D0pi0_,
                     NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                         .pidEff_Bu2Dst0h_D0pi0()))),
      N_Delta_Bu2Dst0h_D0pi0_(new RooFormulaVar(
          ("N_Delta_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(NeutralVars<_neutral>::Get(uniqueId)
                         .buDeltaCutEffBu2Dst0h_D0pi0(),
                     NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
                     *N_Bu2Dst0h_D0pi0_))),
      N_Bu_Bu2Dst0h_D0pi0_(nullptr),
      // -------------------- MisRec -------------------- //
      N_tot_MisRec_(new RooRealVar(
          ("N_tot_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .N_tot_initVal_MisRec(),
          0, 1000000)),
      N_MisRec_(new RooFormulaVar(
          ("N_MisRec_" + ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "@0", RooArgList(*N_tot_MisRec_))),
      N_Delta_MisRec_(new RooFormulaVar(
          ("N_Delta_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(NeutralVars<_neutral>::Get(uniqueId).buDeltaCutEffMisRec(),
                     NeutralVars<_neutral>::Get(uniqueId).orEffMisRec(),
                     *N_MisRec_))),
      N_Bu_MisRec_(nullptr),
      N_BuPartial_MisRec_(nullptr),
      // -------------------- Bu2D0h -------------------- //
      N_tot_Bu2D0h_(new RooRealVar(
          ("N_tot_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .N_tot_initVal_Bu2D0h(),
          0, 1000000)),
      N_Bu2D0h_(new RooFormulaVar(
          ("N_Bu2D0h_" + ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "@0", RooArgList(*N_tot_Bu2D0h_))),
      N_Delta_Bu2D0h_(new RooFormulaVar(
          ("N_Delta_Bu2D0h_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(NeutralVars<_neutral>::Get(uniqueId).buDeltaCutEffBu2D0h(),
                     NeutralVars<_neutral>::Get(uniqueId).orEffBu2D0h(),
                     *N_Bu2D0h_))),
      N_Bu_Bu2D0h_(nullptr),
      // -------------------- PartRec -------------------- //
      N_tot_PartRec_(new RooRealVar(
          ("N_tot_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "", NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                  .N_tot_initVal_PartRec(),
          0, 1000000)),
      N_PartRec_(new RooFormulaVar(
          ("N_PartRec_" + ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "@0",
          RooArgList(*N_tot_PartRec_,
                     NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                         .pidEff_PartRec()))),
      N_Delta_PartRec_(new RooFormulaVar(
          ("N_Delta_PartRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<_neutral>::Get(uniqueId).buDeltaCutEffPartRec(),
              NeutralVars<_neutral>::Get(uniqueId).orEffPartRec(),
              *N_PartRec_))),
      N_Bu_PartRec_(nullptr) {
  if (Configuration::Get().fit1D() == false) {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<_neutral>::Get(uniqueId).deltaCutEffBu2Dst0h_D0gamma(),
            NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
            *N_Bu2Dst0h_D0gamma_)));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(
            NeutralVars<_neutral>::Get(uniqueId).deltaCutEffBu2Dst0h_D0pi0(),
            NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
            *N_Bu2Dst0h_D0pi0_)));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(NeutralVars<_neutral>::Get(uniqueId).deltaCutEffMisRec(),
                   NeutralVars<_neutral>::Get(uniqueId).orEffMisRec(),
                   *N_MisRec_)));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(NeutralVars<_neutral>::Get(uniqueId).deltaCutEffBu2D0h(),
                   NeutralVars<_neutral>::Get(uniqueId).orEffBu2D0h(),
                   *N_Bu2D0h_)));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "(@0/@1)*@2",
        RooArgList(NeutralVars<_neutral>::Get(uniqueId).deltaCutEffPartRec(),
                   NeutralVars<_neutral>::Get(uniqueId).orEffPartRec(),
                   *N_PartRec_)));
    if (_neutral == Neutral::gamma) {
      N_BuPartial_Bu2Dst0h_D0gamma_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_BuPartial_Bu2Dst0h_D0gamma_" +
               ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
                  .c_str(),
              "(@0/@1)*@2",
              RooArgList(
                  NeutralVars<_neutral>::Get(uniqueId)
                      .deltaPartialCutEffBu2Dst0h_D0gamma(),
                  NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0gamma(),
                  *N_Bu2Dst0h_D0gamma_)));
      N_BuPartial_Bu2Dst0h_D0pi0_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_BuPartial_Bu2Dst0h_D0pi0_" +
               ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
                  .c_str(),
              "(@0/@1)*@2",
              RooArgList(
                  NeutralVars<_neutral>::Get(uniqueId)
                      .deltaPartialCutEffBu2Dst0h_D0pi0(),
                  NeutralVars<_neutral>::Get(uniqueId).orEffBu2Dst0h_D0pi0(),
                  *N_Bu2Dst0h_D0pi0_)));
      N_BuPartial_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_BuPartial_MisRec_" +
           ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralVars<_neutral>::Get(uniqueId).deltaPartialCutEffMisRec(),
              NeutralVars<_neutral>::Get(uniqueId).orEffMisRec(), *N_MisRec_)));
    }
  } else {
    N_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0gamma_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_Bu2Dst0h_D0gamma_,
                   NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                       .pidEff_Bu2Dst0h_D0gamma())));
    N_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2Dst0h_D0pi0_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_Bu2Dst0h_D0pi0_,
                   NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                       .pidEff_Bu2Dst0h_D0pi0())));
    N_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_MisRec_" + ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_MisRec_,
                   NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                       .pidEff_MisRec())));
    N_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_Bu2D0h_" + ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_Bu2D0h_,
                   NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                       .pidEff_Bu2D0h())));
    N_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("N_Bu_PartRec_" +
         ComposeName(uniqueId, _neutral, Bachelor::k, _charge))
            .c_str(),
        "@0*@1",
        RooArgList(*N_tot_PartRec_,
                   NeutralBachelorVars<_neutral, Bachelor::k>::Get(uniqueId)
                       .pidEff_PartRec())));
  }
}
