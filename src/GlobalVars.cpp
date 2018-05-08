#include "GlobalVars.h"

GlobalVars::GlobalVars(int uniqueId)
    : relativeWidth_("relativeWidth", "Relative Width of k w.r.t. pi modes",
                     0.95),
      R_Dst0K_vs_Dst0pi_predicted_(0.081),
      R_Dst0K_vs_Dst0pi_("R_Dst0K_vs_Dst0pi",
                         "Ratio of Dst0K yield w.r.t. Dst0pi",
                         R_Dst0K_vs_Dst0pi_predicted_, 0, 1) {}

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
