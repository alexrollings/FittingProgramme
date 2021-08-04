#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "BachelorChargeVars.h"

// Split by charge; only for pik
template <Bachelor bachelor>
RooFormulaVar *Make_R_ADS(int uniqueId, const char *name,
                          RooAbsReal &R_piK_minus, RooAbsReal &R_piK_plus) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, bachelor, Daughters::pik)).c_str(), "",
      "(@0+@1)/2", RooArgSet(R_piK_minus, R_piK_plus));
}

// Summed over charge; only for pik
template <Bachelor bachelor>
RooFormulaVar *Make_R_ADS(int uniqueId, const char *name,
                          RooAbsReal &R_piK_total) {
  return new RooFormulaVar(
      (name + ComposeName(uniqueId, bachelor, Daughters::pik)).c_str(), "",
      "@0", RooArgSet(R_piK_total));
}

template <Bachelor bachelor>
class BachelorVars {
 public:
  BachelorVars(int uniqueId);
  ~BachelorVars() {}

  using This_t = BachelorVars<bachelor>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  int uniqueId() { return uniqueId_; }
  // -------------------- CP Observables -------------------- //
  RooAbsReal &A_CP_Bu2Dst0h_D0gamma_Blind() {
    return *A_CP_Bu2Dst0h_D0gamma_Blind_;
  }
  RooAbsReal &A_CP_Bu2Dst0h_D0pi0_Blind() {
    return *A_CP_Bu2Dst0h_D0pi0_Blind_;
  }
  RooAbsReal &A_CP_Bu2Dst0h_D0gamma() { return *A_CP_Bu2Dst0h_D0gamma_; }
  RooAbsReal &A_CP_Bu2Dst0h_D0pi0() { return *A_CP_Bu2Dst0h_D0pi0_; }
  RooAbsReal &A_CP_Bu2Dst0h_WN() { return *A_CP_Bu2Dst0h_WN_; }
  RooAbsReal &A_CP_Bd2Dsth() { return *A_CP_Bd2Dsth_; }
  RooAbsReal &A_CP_Bu2D0hst() { return *A_CP_Bu2D0hst_; }
  RooGaussian &A_CP_Bu2D0hst_gaus() { return *A_CP_Bu2D0hst_gaus; }
  RooAbsReal &A_CP_Bu2Dst0hst() { return *A_CP_Bu2Dst0hst_; }
  RooAbsReal &A_CP_Lb2Omegach_Lcpi0() { return *A_CP_Lb2Omegach_Lcpi0_; }
  RooFormulaVar &R_ADS_Bu2Dst0h_D0gamma() { return *R_ADS_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &R_ADS_Bu2Dst0h_D0pi0() { return *R_ADS_Bu2Dst0h_D0pi0_; }
  RooAbsReal &R_ADS_Bu2Dst0h_WN() { return *R_ADS_Bu2Dst0h_WN_; }
  RooAbsReal &R_ADS_Bd2Dsth() { return *R_ADS_Bd2Dsth_; }
  RooAbsReal &R_ADS_Bu2D0hst() { return *R_ADS_Bu2D0hst_; }
  RooAbsReal &R_ADS_Bu2Dst0hst() { return *R_ADS_Bu2Dst0hst_; }


 private:
  int uniqueId_;
  // -------------------- CP Observables -------------------- //
  std::shared_ptr<RooRealVar> A_CP_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> A_CP_Bu2Dst0h_D0pi0_Blind_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> A_CP_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2D0hst_;
  std::unique_ptr<RooGaussian> A_CP_Bu2D0hst_gaus_;
  std::shared_ptr<RooAbsReal> A_CP_Bu2Dst0hst_;
  std::shared_ptr<RooAbsReal> A_CP_Lb2Omegach_Lcpi0_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooFormulaVar> R_ADS_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> R_ADS_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> R_ADS_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> R_ADS_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> R_ADS_Bu2Dst0hst_;
};
