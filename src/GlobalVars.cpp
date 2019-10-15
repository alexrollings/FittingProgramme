#include "GlobalVars.h"

GlobalVars::GlobalVars(int uniqueId) {}

std::string ComposeName(int uniqueId, Mass mass, Neutral neutral,
                        Bachelor bachelor, Daughters daughters, Charge charge) {
  return EnumToString(mass) + "_" + EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(daughters) + "_" +
         EnumToString(charge) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor, Daughters daughters, Charge charge) {
  return EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(daughters) + "_" +
         EnumToString(charge) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor, Daughters daughters) {
  return EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(daughters) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor) {
  return EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral, Bachelor bachelor,
                        Charge charge) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
         std::to_string(charge) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral,
                        Daughters daughters) {
  return EnumToString(neutral) + "_" +
         EnumToString(daughters) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral) {
  return EnumToString(neutral) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Daughters daughters) {
  return EnumToString(daughters) + "_" +
         std::to_string(uniqueId);
}
