#pragma once
#include "Configuration.h"
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include <string>

// There is only a single instance of categories therefore we do not have to pass it around any more
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

 private:
  GlobalVars(GlobalVars const &) = delete;
  GlobalVars(GlobalVars &&) = delete;
  GlobalVars &operator=(GlobalVars const &) = delete;
  GlobalVars &operator=(GlobalVars &&) = delete;

  int uniqueId_;
};

std::string ComposeName(int uniqueId, Mass mass, Neutral neutral,
                        Bachelor bachelor, Daughters daughters, Charge charge);
std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor, Daughters daughters, Charge charge);
std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor, Daughters daughters);
std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor);
std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor, Charge charge);
std::string ComposeName(int uniqueId, Neutral neutral,
                        Daughters daughters);
std::string ComposeName(int uniqueId, Neutral neutral);
std::string ComposeName(int uniqueId, Neutral neutral, Charge charge);
std::string ComposeName(int uniqueId, Bachelor bachelor, Daughters daughters);
