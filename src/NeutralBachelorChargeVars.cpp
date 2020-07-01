#include "NeutralBachelorChargeVars.h"

template <Neutral neutral, Bachelor bachelor, Charge charge>
NeutralBachelorChargeVars<neutral, bachelor, charge>
    &NeutralBachelorChargeVars<neutral, bachelor, charge>::Get(int uniqueId) {
  static std::map<int, std::shared_ptr<This_t>> singletons;
  // An iterator to a map is a std::pair<key, value>, so we need to call
  // i->second to get the value
  auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
  if (it == singletons.end()) {
    // If it doesn't, create it as a new shared_ptr by calling emplace, which
    // will forward the pointer to the constructor of std::unique_ptr
    it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId)).first;
  }
  return *it->second;
}

void InstantiateNeutralBachelorChargeVars() {
  NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi, Charge::plus>::Get(-1);
  NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi, Charge::minus>::Get(-1);
  NeutralBachelorChargeVars<Neutral::pi0, Bachelor::pi, Charge::total>::Get(-1);
  NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k, Charge::plus>::Get(-1);
  NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k, Charge::minus>::Get(-1);
  NeutralBachelorChargeVars<Neutral::pi0, Bachelor::k, Charge::total>::Get(-1);
  NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi, Charge::plus>::Get(
      -1);
  NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi, Charge::minus>::Get(
      -1);
  NeutralBachelorChargeVars<Neutral::gamma, Bachelor::pi, Charge::total>::Get(
      -1);
  NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k, Charge::plus>::Get(-1);
  NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k, Charge::minus>::Get(
      -1);
  NeutralBachelorChargeVars<Neutral::gamma, Bachelor::k, Charge::total>::Get(
      -1);
}
