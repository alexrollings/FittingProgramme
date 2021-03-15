#include "Configuration.h"

Configuration::Configuration(int _deltaBoxLow, int _deltaBoxHigh, int _buBoxLow, int _buBoxHigh)
    : fit1D(false),
      signalOnly(false),
      buBoxLow(_buBoxLow),
      buBoxHigh(_buBoxHigh),
      deltaBoxLow(_deltaBoxLow),
      deltaBoxHigh(_deltaBoxHigh),
      buRangeLow(5050),
      buRangeHigh(5450),
      buBins((buRangeHigh - buRangeLow) / 5),
      deltaRangeLow(136),
      deltaRangeHigh(190),
      deltaBins((deltaRangeHigh - deltaRangeLow) / 5),
      fitting("fitting", "fitting"),
      buMass("Bu_Delta_M", "m(B)", buRangeLow, buRangeHigh, "MeV/c^{2}"),
      deltaMass("Delta_M", "m(#Delta)", deltaRangeLow, deltaRangeHigh,
                "MeV/c^{2}"),
      fittingArgset(buMass, deltaMass, fitting),
      outputDir(),
      cutString() {

  fitting.defineType(EnumToString(Mass::bu).c_str());
  fitting.defineType(EnumToString(Mass::delta).c_str());

  // cutString = "((Bu_Delta_M>" + std::to_string(buBoxLow) + "&&Bu_Delta_M<" +
  //             std::to_string(buBoxHigh) + ")||(Delta_M>" +
  //             std::to_string(deltaBoxLow) + "&&Delta_M<" +
  //             std::to_string(deltaBoxHigh) + "))";
  if (fit1D == true) {
    cutString = "(Delta_M>" + std::to_string(deltaBoxLow) + "&&Delta_M<" +
                std::to_string(deltaBoxHigh) + "))";
  }
}

std::string Configuration::ReturnBoxStr() {
  std::stringstream ss;
  ss << deltaBoxLow << "_" << deltaBoxHigh;
  if (fit1D == false) {
  ss << "_" << buBoxLow << "_" << buBoxHigh;
  }
  return ss.str();
}

std::string EnumToString(Mass mass) {
  switch (mass) {
    case Mass::bu:
      return "bu";
      break;
    case Mass::delta:
      return "delta";
      break;
    default:
      return "";
  }
}

std::string EnumToString(Mode mode) {
  switch (mode) {
    case Mode::Bu2Dst0pi_D0pi0:
      return "Bu2Dst0pi_D0pi0";
      break;
  }
  throw std::runtime_error("EnumToString: no such Mode defined\n");
}

template <>
Mode StringToEnum<Mode>(std::string const &mode) {
    if (mode == "Bu2Dst0pi_D0pi0") {
          return Mode::Bu2Dst0pi_D0pi0;
    } else {
      throw std::runtime_error("StringToEnum: no such Mode defined\n");
    }
}
