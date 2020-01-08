#pragma once
#include "Configuration.h"
#include "GlobalVars.h"

template <Neutral neutral, Daughters daughters>
class NeutralDaughtersVars {
 public:
  NeutralDaughtersVars(int uniqueId_);
  ~NeutralDaughtersVars() {}

  using This_t = NeutralDaughtersVars<neutral, daughters>;

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
  RooRealVar &R_Dst0KDst0pi_Bu2Dst0h_D0gamma() {
    return R_Dst0KDst0pi_Bu2Dst0h_D0gamma_;
  }
  RooRealVar &R_Dst0KDst0pi_Bu2Dst0h_D0pi0() {
    return R_Dst0KDst0pi_Bu2Dst0h_D0pi0_;
  }

 private:
  int uniqueId_;
  RooRealVar R_Dst0KDst0pi_Bu2Dst0h_D0gamma_;
  RooRealVar R_Dst0KDst0pi_Bu2Dst0h_D0pi0_;
};

template <Neutral neutral, Daughters daughters>
NeutralDaughtersVars<neutral, daughters>::NeutralDaughtersVars(int uniqueId)
    : R_Dst0KDst0pi_Bu2Dst0h_D0gamma_(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0gamma_" +
           ComposeName(uniqueId, neutral, daughters))
              .c_str(),
          "", 0.07930, -1, 1),
      R_Dst0KDst0pi_Bu2Dst0h_D0pi0_(
          ("R_Dst0KDst0pi_Bu2Dst0h_D0pi0_" +
           ComposeName(uniqueId, neutral, daughters))
              .c_str(),
          "", 0.07930, -1, 1) {}
