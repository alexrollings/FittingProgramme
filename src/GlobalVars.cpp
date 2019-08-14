#include "GlobalVars.h"

GlobalVars::GlobalVars(int uniqueId) {}

std::string ComposeName(int uniqueId, Variable variable, Neutral neutral,
                        Bachelor bachelor, Daughters daughters, Charge charge) {
  return EnumToString(variable) + "_" + EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(daughters) + "_" +
         EnumToString(charge) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Variable variable, Neutral neutral,
                        Bachelor bachelor, Daughters daughters) {
  return EnumToString(variable) + "_" + EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(daughters) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Variable variable, Neutral neutral,
                        Bachelor bachelor) {
  return EnumToString(variable) + "_" + EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Variable variable, Neutral neutral,
                        Daughters daughters) {
  return EnumToString(variable) + "_" + EnumToString(neutral) + "_" +
         EnumToString(daughters) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Variable variable, Neutral neutral) {
  return EnumToString(variable) + "_" + EnumToString(neutral) + "_" +
         std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Neutral neutral) {
  return EnumToString(neutral) + "_" + std::to_string(uniqueId);
}

std::string ComposeName(int uniqueId, Variable variable, Daughters daughters) {
  return EnumToString(variable) + "_" + EnumToString(daughters) + "_" +
         std::to_string(uniqueId);
}
