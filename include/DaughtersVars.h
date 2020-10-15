#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "RooFormulaVar.h"

template <Daughters daughters>
class DaughtersVars {
 public:
  DaughtersVars(int uniqueId);
  ~DaughtersVars() {}

  using This_t = DaughtersVars<daughters>;

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
  RooAbsReal &R_Dst0KDst0pi_Bu2Dst0h_WN() {
    return *R_Dst0KDst0pi_Bu2Dst0h_WN_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bd2Dsth() {
    return *R_Dst0KDst0pi_Bd2Dsth_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bu2D0hst() {
    return *R_Dst0KDst0pi_Bu2D0hst_;
  }
  RooAbsReal &R_Dst0KDst0pi_Bu2Dst0hst() {
    return *R_Dst0KDst0pi_Bu2Dst0hst_;
  }
  RooAbsReal &R_Dst0KDst0pi_Lb2Omegach_Lcpi0() {
    return *R_Dst0KDst0pi_Lb2Omegach_Lcpi0_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0h_D0gamma_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0h_D0gamma_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0h_D0pi0_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0h_D0pi0_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0h_WN_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0h_WN_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bd2Dsth_GetPointer() {
    return R_Dst0KDst0pi_Bd2Dsth_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2D0hst_GetPointer() {
    return R_Dst0KDst0pi_Bu2D0hst_;
  }
  std::shared_ptr<RooAbsReal> &R_Dst0KDst0pi_Bu2Dst0hst_GetPointer() {
    return R_Dst0KDst0pi_Bu2Dst0hst_;
  }

 private:
  int uniqueId_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> R_Dst0KDst0pi_Lb2Omegach_Lcpi0_;
};

template <>
DaughtersVars<Daughters::kpi>::DaughtersVars(
    int uniqueId);
template <>
DaughtersVars<Daughters::kk>::DaughtersVars(
    int uniqueId);
template <>
DaughtersVars<Daughters::pipi>::DaughtersVars(
    int uniqueId);
template <>
DaughtersVars<Daughters::pik>::DaughtersVars(
    int uniqueId);
