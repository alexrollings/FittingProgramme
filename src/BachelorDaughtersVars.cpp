#include "BachelorDaughtersVars.h"
#include "Configuration.h"
#include "GlobalVars.h"

template <>
BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::pi, Daughters::kpi))
               .c_str(),
           "", 1.0) {}

template <>
BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(
          ("kBR_" + ComposeName(uniqueId, Bachelor::pi, Daughters::kk)).c_str(),
          "", 0.00408 / 0.0395) {}

template <>
BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::pi, Daughters::pipi))
               .c_str(),
           "", 0.001455 / 0.0395) {}

template <>
BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::pi, Daughters::pik))
               .c_str(),
           "", 0.0001364 / 0.0395) {}

template <>
BachelorDaughtersVars<Bachelor::k, Daughters::kpi>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(
          ("kBR_" + ComposeName(uniqueId, Bachelor::k, Daughters::kpi)).c_str(),
          "", 1.0 * (0.000397 / 0.00490)) {}

template <>
BachelorDaughtersVars<Bachelor::k, Daughters::kk>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::k, Daughters::kk)).c_str(),
           "", (0.00408 / 0.0395) * (0.000397 / 0.00490)) {}

template <>
BachelorDaughtersVars<Bachelor::k, Daughters::pipi>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(("kBR_" + ComposeName(uniqueId, Bachelor::k, Daughters::pipi))
               .c_str(),
           "", (0.001455 / 0.0395) * (0.000397 / 0.00490)) {}

// Including R ADS
template <>
BachelorDaughtersVars<Bachelor::k, Daughters::pik>::BachelorDaughtersVars(
    int uniqueId)
    : kBR_(
          ("kBR_" + ComposeName(uniqueId, Bachelor::k, Daughters::pik)).c_str(),
          "", 0.0015) {}

template <Bachelor bachelor, Daughters daughters>
BachelorDaughtersVars<bachelor, daughters>
    &BachelorDaughtersVars<bachelor, daughters>::Get(int uniqueId_) {
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

void InstantiateBachelorDaughtersVars() {
  BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::Get(-1);
  BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::Get(-1);
  BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::Get(-1);
  BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::Get(-1);
  BachelorDaughtersVars<Bachelor::k, Daughters::kpi>::Get(-1);
  BachelorDaughtersVars<Bachelor::k, Daughters::kk>::Get(-1);
  BachelorDaughtersVars<Bachelor::k, Daughters::pipi>::Get(-1);
  BachelorDaughtersVars<Bachelor::k, Daughters::pik>::Get(-1);
}
