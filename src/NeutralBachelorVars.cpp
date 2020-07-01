#include "NeutralBachelorVars.h"

template <Neutral neutral, Bachelor bachelor>
NeutralBachelorVars<neutral, bachelor>
    &NeutralBachelorVars<neutral, bachelor>::Get(int uniqueId) {
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

void InstantiateNeutralBachelorVars() {
  NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(-1);
  NeutralBachelorVars<Neutral::pi0, Bachelor::k>::Get(-1);
  NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(-1);
  NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get(-1);
}
