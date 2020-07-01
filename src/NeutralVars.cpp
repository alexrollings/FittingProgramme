#include "NeutralVars.h"

template <Neutral neutral>
NeutralVars<neutral> &NeutralVars<neutral>::Get(int uniqueId) {
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

void InstantiateNeutralVars() {
  NeutralVars<Neutral::pi0>::Get(-1);
  NeutralVars<Neutral::gamma>::Get(-1);
}
