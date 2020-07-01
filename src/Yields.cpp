#include "Yields.h"

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
Yields<neutral, bachelor, daughters, charge>
    &Yields<neutral, bachelor, daughters, charge>::Get(int uniqueId) {
  static std::map<int, std::shared_ptr<This_t>> singletons;
  // An iterator to a map is a std::pair<key, value>, so we need to call
  // i->second to get the value
  auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
  if (it == singletons.end()) {
    // If it doesn't, create it as a new unique_ptr by calling emplace, which
    // will forward the pointer to the constructor of std::unique_ptr
    it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId)).first;
  }
  return *it->second;
}

void InstantiateYields() {
  Yields<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::plus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::minus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::total>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::plus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::minus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::total>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::plus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::minus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::total>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::plus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::minus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::total>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::plus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::minus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::total>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::plus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::minus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::total>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::plus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::minus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::total>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::plus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::minus>::Get(-1);
  Yields<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::total>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::plus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::minus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::total>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::plus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::minus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::total>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::pipi, Charge::plus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::pipi, Charge::minus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::pipi, Charge::total>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::plus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::minus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::total>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::plus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::minus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::total>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::plus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::minus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::total>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::plus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::minus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::total>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::plus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::minus>::Get(-1);
  Yields<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::total>::Get(-1);
}
