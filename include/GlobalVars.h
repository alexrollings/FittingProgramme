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
  RooRealVar &A_Kpi() { return *A_Kpi_; }
  RooRealVar &A_pi() { return *A_pi_; }
  RooFormulaVar &a_Prod() { return *a_Prod_; }
  RooFormulaVar &a_Kpi() { return *a_Kpi_; }
  RooFormulaVar &a_pi() { return *a_pi_; }

  RooRealVar &kBF_Bu2Dst0pi() { return *kBF_Bu2Dst0pi_; }
  RooRealVar &kBF_Bu2Dst0K() { return *kBF_Bu2Dst0K_; }
  RooRealVar &kBF_Dst02D0pi0() { return *kBF_Dst02D0pi0_; }
  RooRealVar &kBF_Dst02D0gamma() { return *kBF_Dst02D0gamma_; }
  RooRealVar &kBF_D02kpi() { return *kBF_D02kpi_; }
  RooRealVar &kBF_D02kk() { return *kBF_D02kk_; }
  RooRealVar &kBF_D02pipi() { return *kBF_D02pipi_; }
  RooRealVar &kBF_D02pik() { return *kBF_D02pik_; }

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
  std::shared_ptr<RooRealVar> A_Kpi_;
  std::shared_ptr<RooRealVar> A_pi_;
  std::unique_ptr<RooFormulaVar> a_Prod_;
  std::unique_ptr<RooFormulaVar> a_Kpi_;
  std::unique_ptr<RooFormulaVar> a_pi_;

  std::shared_ptr<RooRealVar> kBF_Bu2Dst0pi_;
  std::shared_ptr<RooRealVar> kBF_Bu2Dst0K_;
  std::shared_ptr<RooRealVar> kBF_Dst02D0pi0_;
  std::shared_ptr<RooRealVar> kBF_Dst02D0gamma_;
  std::shared_ptr<RooRealVar> kBF_D02kpi_;
  std::shared_ptr<RooRealVar> kBF_D02kk_;
  std::shared_ptr<RooRealVar> kBF_D02pipi_;
  std::shared_ptr<RooRealVar> kBF_D02pik_;
};

std::string MakePidKey(Bachelor bachelor, Charge charge);
