#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooCruijff.h"
#include "RooFormulaVar.h"
#include "RooProdPdf.h"

// Bachelor

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
  RooRealVar &N_tot_Bu2Dst0h_D0gamma() { return N_tot_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &N_Bu2Dst0h_D0gamma() { return N_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0gamma() {
    return N_Delta_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_Bu_Bu2Dst0h_D0gamma() { return *N_Bu_Bu2Dst0h_D0gamma_; }
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar &N_tot_Bu2Dst0h_D0pi0() { return N_tot_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Bu2Dst0h_D0pi0() { return N_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Delta_Bu2Dst0h_D0pi0() { return N_Delta_Bu2Dst0h_D0pi0_; }
  RooAbsReal &N_Bu_Bu2Dst0h_D0pi0() { return *N_Bu_Bu2Dst0h_D0pi0_; }
  // -------------------- Mis-ID ------------------- //
  // -------------------- MIS-REC -------------------- //
  RooRealVar &N_tot_MisRec() { return N_tot_MisRec_; }
  RooFormulaVar &N_MisRec() { return N_MisRec_; }
  RooFormulaVar &N_Delta_MisRec() { return N_Delta_MisRec_; }
  RooAbsReal &N_Bu_MisRec() { return *N_Bu_MisRec_; }
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2D0h -------------------- //
  RooRealVar &N_tot_Bu2D0h() { return N_tot_Bu2D0h_; }
  RooFormulaVar &N_Bu2D0h() { return N_Bu2D0h_; }
  RooFormulaVar &N_Delta_Bu2D0h() { return N_Delta_Bu2D0h_; }
  RooAbsReal &N_Bu_Bu2D0h() { return *N_Bu_Bu2D0h_; }
  // -------------------- Mis-ID ------------------- //
  // -------------------- PART REC -------------------- //
  RooRealVar &N_tot_PartRec() { return N_tot_PartRec_; }
  RooFormulaVar &N_PartRec() { return N_PartRec_; }
  RooFormulaVar &N_Delta_PartRec() {
    return N_Delta_PartRec_;
  }
  RooAbsReal &N_Bu_PartRec() { return *N_Bu_PartRec_; }
  // -------------------- Mis-ID ------------------- //

  void SetMisIdEfficiencies(Mode mode, RooRealVar &orEff, RooRealVar &boxEff,
                            RooRealVar &buDeltaCutEff, RooRealVar &deltaCutEff);

 private:
  int uniqueId_;
  // -------------------- Bu2Dst0h_D0gamma -------------------- //
  RooRealVar N_tot_Bu2Dst0h_D0gamma_;
  RooFormulaVar N_Bu2Dst0h_D0gamma_;
  RooFormulaVar N_Delta_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0gamma_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2Dst0h_D0pi0 -------------------- //
  RooRealVar N_tot_Bu2Dst0h_D0pi0_;
  RooFormulaVar N_Bu2Dst0h_D0pi0_;
  RooFormulaVar N_Delta_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2Dst0h_D0pi0_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- MIS-REC -------------------- //
  RooRealVar N_tot_MisRec_;
  RooFormulaVar N_MisRec_;
  RooFormulaVar N_Delta_MisRec_;
  std::unique_ptr<RooAbsReal> N_Bu_MisRec_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- Bu2D0h -------------------- //
  RooRealVar N_tot_Bu2D0h_;
  RooFormulaVar N_Bu2D0h_;
  RooFormulaVar N_Delta_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_Bu_Bu2D0h_;
  // -------------------- Mis-ID ------------------- //
  // -------------------- PART REC -------------------- //
  RooRealVar N_tot_PartRec_;
  RooFormulaVar N_PartRec_;
  RooFormulaVar N_Delta_PartRec_;
  std::unique_ptr<RooAbsReal> N_Bu_PartRec_;
  // -------------------- Mis-ID ------------------- //
};

template <>
NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi, Charge::total>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k, Charge::total>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi, Charge::total>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k, Charge::total>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi, Charge::plus>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k, Charge::plus>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi, Charge::plus>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k, Charge::plus>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi, Charge::minus>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k, Charge::minus>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi, Charge::minus>::
    NeutralBachelorChargeVars(int uniqueId);
template <>
NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k, Charge::minus>::
    NeutralBachelorChargeVars(int uniqueId);
