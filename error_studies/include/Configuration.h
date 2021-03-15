#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "RooArgSet.h"
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"

enum class Efficiency { buEff, deltaEff, orEff };
enum class Mass { bu, delta };
enum class Mode { Bu2Dst0pi_D0pi0 };

template <typename Enum>
Enum StringToEnum(std::string const &);
std::string EnumToString(Mass);
std::string EnumToString(Mode);

// Class to hold a bunch of variables that are passed around
class Configuration {
 public:
  Configuration(int, int, int, int);

  bool fit1D;
  bool signalOnly;
  int buBoxLow;
  int buBoxHigh;
  int deltaBins;
  int deltaBoxLow;
  int deltaBoxHigh;
  int buRangeLow;
  int buRangeHigh;
  int buBins;
  int deltaRangeLow;
  int deltaRangeHigh;
  RooCategory fitting;
  RooRealVar buMass;
  RooRealVar deltaMass;
  RooArgSet variableArgset;
  RooArgSet fittingArgset;
  std::string outputDir;
  std::string cutString;

  std::string ReturnBoxStr();
};
