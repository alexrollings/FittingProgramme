#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "RooFormulaVar.h"

template <Neutral neutral, Daughters daughters>
class NeutralDaughtersVars {
 public:
  NeutralDaughtersVars(int uniqueId);
  ~NeutralDaughtersVars() {}

  using This_t = NeutralDaughtersVars<neutral, daughters>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  int uniqueId() { return uniqueId_; }
  RooAbsReal &R_Dst0KDst0pi_Bu2Dst0h_D0gamma() {
    return *R_Dst0KDst0pi_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bu2Dst0h_D0pi0() {
    return *R_Dst0KDst0pi_Bu2Dst0h_D0pi0_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN() {
    return *R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN() {
    return *R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bd2Dsth() {
    return *R_Dst0KDst0pi_Bd2Dsth_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bu2D0hst() {
    return *R_Dst0KDst0pi_Bu2D0hst_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bu2Dst0hst_D0gamma() {
    return *R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bu2Dst0hst_D0pi0() {
    return *R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0h_D0gamma_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0h_D0gamma_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0h_D0pi0_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bd2Dsth_GetPointer() {
    return R_Dst0KDst0pi_Bd2Dsth_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2D0hst_GetPointer() {
    return R_Dst0KDst0pi_Bu2D0hst_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_;
  }

 private:
  int uniqueId_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0h_D0gamma_WN_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0h_D0pi0_WN_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0hst_D0gamma_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0hst_D0pi0_;
};

template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId);
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId);
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId);
template <>
NeutralDaughtersVars<Neutral::pi0, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId);
template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kpi>::NeutralDaughtersVars(
    int uniqueId);
template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::kk>::NeutralDaughtersVars(
    int uniqueId);
template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pipi>::NeutralDaughtersVars(
    int uniqueId);
template <>
NeutralDaughtersVars<Neutral::gamma, Daughters::pik>::NeutralDaughtersVars(
    int uniqueId);
