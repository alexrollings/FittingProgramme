#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "Params.h"

template <Neutral neutral, Charge charge>

class NeutralChargeVars {
 public:
  NeutralChargeVars(int uniqueId);
  ~NeutralChargeVars() {}

  using This_t = NeutralChargeVars<neutral, charge>;

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
  double ReturnPidEffs(bool returnEff);

  RooRealVar &GetPidEff(Bachelor bachelor) {
    if (bachelor == Bachelor::pi) {
      return GlobalVars::Get(uniqueId_).pidEffPi();
    } else {
      return *pidEffK_;
    }
  }

 private:
  int uniqueId_;
  std::shared_ptr<RooRealVar> pidEffK_;
};

template <Neutral neutral, Charge charge>
double NeutralChargeVars<neutral, charge>::ReturnPidEffs(bool returnEff) {
  std::string txtFileName =
      "/home/rollings/Bu2Dst0h_scripts/pid_corr/output/PID_effs_" +
      EnumToString(neutral) + ".txt";
  if (!fexists(txtFileName)) {
    throw std::logic_error("ReturnPidEffs: " + txtFileName + " doesn't exist.");
  }
  std::ifstream inFile(txtFileName);
  std::string line;
  // Loop over lines in txt file
  while (std::getline(inFile, line)) {
    // Separate label and value (white space)
    std::vector<std::string> lineVec = SplitLine(line);
    if (lineVec[0] == EnumToString(charge)) {
      if (returnEff == true) {
        return std::stod(lineVec[1]);
      } else {
        return std::stod(lineVec[2]);
      }
    }
  }
};

template <Neutral neutral, Charge charge>
NeutralChargeVars<neutral, charge>::NeutralChargeVars(int uniqueId)
    : uniqueId_(uniqueId),
      pidEffK_(Params::Get().CreateFixed(
          "pidEffK", uniqueId_, neutral, charge, ReturnPidEffs(true),
          ReturnPidEffs(false), Systematic::pidEffK, Sign::positive)) {}
