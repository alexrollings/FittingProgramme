#pragma once
#include "RooFormulaVar.h"

#include "Configuration.h"
#include "Efficiencies.h"
#include "Params.h"

#include <string>

// There is only a single instance of categories therefore we do not have to
// pass it around any more
class GlobalVars {
 public:
  GlobalVars(int uniqueId);

  using This_t = GlobalVars;

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

  std::map<std::string, std::shared_ptr<RooAbsReal> > &pidEffMap() { return pidEffMap_; }
  RooRealVar &crossFeedRate() { return *crossFeedRate_; }
  RooRealVar &Delta_A_CP() { return *Delta_A_CP_; }
  RooRealVar &A_Prod() { return *A_Prod_; }
  RooRealVar &A_pi() { return *A_pi_; }
  RooFormulaVar &a_Prod() { return *a_Prod_; }
  RooFormulaVar &a_pi() { return *a_pi_; }

  RooRealVar &kBF_Bu2Dst0pi() { return *kBF_Bu2Dst0pi_; }
  RooRealVar &kBF_Bu2Dst0K() { return *kBF_Bu2Dst0K_; }
  RooRealVar &kBF_Dst02D0pi0() { return *kBF_Dst02D0pi0_; }
  RooRealVar &kBF_Dst02D0gamma() { return *kBF_Dst02D0gamma_; }
  RooRealVar &kBF_D02kpi() { return *kBF_D02kpi_; }
  RooRealVar &kBF_D02kk() { return *kBF_D02kk_; }
  RooRealVar &kBF_D02pipi() { return *kBF_D02pipi_; }
  RooRealVar &kBF_D02pik() { return *kBF_D02pik_; }
  // RooRealVar &kBF_Bd2Dstpi() { return *kBF_Bd2Dstpi_; }
  // RooRealVar &kBF_Bd2DstK() { return *kBF_Bd2DstK_; }
  // RooRealVar &kBF_Dst2D0pi() { return *kBF_Dst2D0pi_; }
  // RooRealVar &kBF_Bu2D0rho() { return *kBF_Bu2D0rho_; }
  // RooRealVar &kBF_Bu2D0Kst() { return *kBF_Bu2D0Kst_; }
  // RooRealVar &kBF_Bd2D0rho0() { return *kBF_Bd2D0rho0_; }
  // RooRealVar &kBF_Bd2D0Kst0() { return *kBF_Bd2D0Kst0_; }
  RooRealVar &kBF_Bu2Dst0rho() { return *kBF_Bu2Dst0rho_; }
  RooRealVar &kBF_Bu2Dst0Kst() { return *kBF_Bu2Dst0Kst_; }

  RooArgSet &constraints_argSet() { return *constraints_argSet_; }

  // -------------------- CP Observables -------------------- //
  RooAbsReal &R_CP_Bu2Dst0h_D0gamma_Blind() {
    return *R_CP_Bu2Dst0h_D0gamma_Blind_;
  }
  RooAbsReal &R_CP_Bu2Dst0h_D0pi0_Blind() {
    return *R_CP_Bu2Dst0h_D0pi0_Blind_;
  }
  RooAbsReal &R_CP_Bu2Dst0h_D0gamma() { return *R_CP_Bu2Dst0h_D0gamma_; }
  RooAbsReal &R_CP_Bu2Dst0h_D0pi0() { return *R_CP_Bu2Dst0h_D0pi0_; }
  RooAbsReal &R_CP_Bu2Dst0h_WN() { return *R_CP_Bu2Dst0h_WN_; }
  RooAbsReal &R_CP_Bd2Dsth() { return *R_CP_Bd2Dsth_; }
  RooAbsReal &R_CP_Bu2D0hst() { return *R_CP_Bu2D0hst_; }
  RooAbsReal &R_CP_Bu2Dst0hst() { return *R_CP_Bu2Dst0hst_; }

 private:
  GlobalVars(GlobalVars const &) = delete;
  GlobalVars(GlobalVars &&) = delete;
  GlobalVars &operator=(GlobalVars const &) = delete;
  GlobalVars &operator=(GlobalVars &&) = delete;

  int uniqueId_;

  std::map<std::string, std::shared_ptr<RooAbsReal> > pidEffMap_;
  std::shared_ptr<RooRealVar> crossFeedRate_;
  std::shared_ptr<RooRealVar> Delta_A_CP_;
  std::shared_ptr<RooRealVar> A_Prod_;
  std::shared_ptr<RooRealVar> A_pi_;
  std::unique_ptr<RooFormulaVar> a_Prod_;
  std::unique_ptr<RooFormulaVar> a_pi_;

  std::shared_ptr<RooRealVar> kBF_Bu2Dst0pi_;
  std::shared_ptr<RooRealVar> kBF_Bu2Dst0K_;
  std::shared_ptr<RooRealVar> kBF_Dst02D0pi0_;
  std::shared_ptr<RooRealVar> kBF_Dst02D0gamma_;
  std::shared_ptr<RooRealVar> kBF_D02kpi_;
  std::shared_ptr<RooRealVar> kBF_D02kk_;
  std::shared_ptr<RooRealVar> kBF_D02pipi_;
  std::shared_ptr<RooRealVar> kBF_D02pik_;
  // std::shared_ptr<RooRealVar> kBF_Bd2Dstpi_;
  // std::shared_ptr<RooRealVar> kBF_Bd2DstK_;
  // std::shared_ptr<RooRealVar> kBF_Dst2D0pi_;
  // std::shared_ptr<RooRealVar> kBF_Bu2D0rho_;
  // std::shared_ptr<RooRealVar> kBF_Bu2D0Kst_;
  // std::shared_ptr<RooRealVar> kBF_Bd2D0rho0_;
  // std::shared_ptr<RooRealVar> kBF_Bd2D0Kst0_;
  std::shared_ptr<RooRealVar> kBF_Bu2Dst0rho_;
  std::shared_ptr<RooRealVar> kBF_Bu2Dst0Kst_;

  std::shared_ptr<RooArgSet> constraints_argSet_;

  // -------------------- CP Observables -------------------- //
  std::shared_ptr<RooRealVar> R_CP_Bu2Dst0h_D0gamma_Blind_;
  std::shared_ptr<RooRealVar> R_CP_Bu2Dst0h_D0pi0_Blind_;
  // Include blinded R_CP for WN: should measure signal R_CP - just make
  // blinding string the same for both (in MakeBlind)
  std::shared_ptr<RooAbsReal> R_CP_Bu2Dst0h_D0gamma_;
  std::shared_ptr<RooAbsReal> R_CP_Bu2Dst0h_D0pi0_;
  std::shared_ptr<RooAbsReal> R_CP_Bu2Dst0h_WN_;
  std::shared_ptr<RooAbsReal> R_CP_Bd2Dsth_;
  std::shared_ptr<RooAbsReal> R_CP_Bu2D0hst_;
  std::shared_ptr<RooAbsReal> R_CP_Bu2Dst0hst_;
};

std::string MakePidKey(Bachelor bachelor, Charge charge);
