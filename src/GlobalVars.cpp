#include "GlobalVars.h"

GlobalVars::GlobalVars(int uniqueId)
    : relativeWidth_(
          ("relativeWidth" + std::to_string(uniqueId)).c_str(),
          ("Relative Width of k w.r.t. pi modes " + std::to_string(uniqueId))
              .c_str(),
          0.95),
      ratioDst0KDst0pi_(
          ("ratioDst0KDst0pi_" + std::to_string(uniqueId)).c_str(),
          ("Ratio of Dst0K yield w.r.t. Dst0pi " + std::to_string(uniqueId))
              .c_str(), 0.081, 0.0, 0.1) {}

std::string ComposeName(int uniqueId, Neutral neutral, Bachelor bachelor,
                        Daughters daughters, Charge charge) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
         EnumToString(daughters) + "_" + EnumToString(charge) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral, Bachelor bachelor,
                        Daughters daughters) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
         EnumToString(daughters) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral, Bachelor bachelor) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral, Daughters daughters) {
  return EnumToString(neutral) + "_" + EnumToString(daughters) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral) {
  return EnumToString(neutral) + "_" + std::to_string(uniqueId);
}
