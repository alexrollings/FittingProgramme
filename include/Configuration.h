#pragma once
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include <string>

enum class Polarity { up, down };
enum class Daughters { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015, y2016 };
enum class Neutral { pi0, gamma };
enum class Charge { plus, minus };
enum class RunType { normal, noRelations };

// There is only a single instance of categories therefore we do not have to pass it around any more
class Configuration {

public:
  static Configuration &Get() {
    static Configuration singleton;
    return singleton;
  }

  struct Categories {
    RooCategory polarity;
    RooCategory charge;
    RooCategory daughters;
    RooCategory bachelor;
    RooCategory neutral;
    RooCategory year;
    RooCategory fitting;
    Categories();
    Categories(Categories const &) = delete;
    Categories(Categories &&) = delete;
    Categories &operator=(Categories const &) = delete;
    Categories &operator=(Categories &&) = delete;
  };

  RooRealVar &buMass() { return buMass_; }
  RooRealVar &buPdgId() { return buPdgId_; }
  RooArgSet &variableArgSet() { return variableArgSet_; }
  RooArgSet &categoryArgSet() { return categoryArgSet_; }
  RooArgSet &fullArgSet() { return fullArgSet_; }
  Categories &categories() { return categories_; }
  RooConstVar &relativeWidth() { return relativeWidth_; }
  RooConstVar &R_Dk_vs_Dpi_Bd2DstH() { return R_Dk_vs_Dpi_Bd2DstH_; }

private:
  Configuration();
  Configuration(Configuration const &) = delete;
  Configuration(Configuration &&) = delete;
  Configuration &operator=(Configuration const &) = delete;
  Configuration &operator=(Configuration &&) = delete;

  Categories categories_;
  RooRealVar buMass_;
  RooRealVar buPdgId_;
  RooArgSet variableArgSet_;
  RooArgSet categoryArgSet_;
  RooArgSet fullArgSet_;
  RooConstVar relativeWidth_;
  RooConstVar R_Dk_vs_Dpi_Bd2DstH_;
};


template <typename Enum> Enum StringToEnum(std::string const &);

std::string EnumToString(Polarity);
std::string EnumToString(Daughters);
std::string EnumToString(Bachelor);
std::string EnumToString(Year);
std::string EnumToString(Neutral);
std::string EnumToString(Charge);

std::string EnumToLabel(std::vector<Charge> chargeVec);
std::string EnumToLabel(Daughters, std::vector<Charge> chargeVec);
std::string EnumToLabel(Bachelor);
std::string EnumToLabel(Neutral);
std::string MissIdLabel(Bachelor);
std::string CrossFeedLabel(Neutral);
std::string HstLabel(Bachelor);

std::string ComposeFilename(Year year, Polarity polarity, Bachelor bachelor,
                            Neutral neutral, Daughters daughters,
                            Charge charge);

std::string ComposeName(Neutral neutral, Bachelor bachelor, Daughters daughters);

std::string ComposeName(Neutral neutral, Daughters daughters);

template <Neutral neutral>
constexpr Neutral SwapNeutral();

template <>
constexpr Neutral SwapNeutral<Neutral::gamma>() {
  return Neutral::pi0; 
}

template <>
constexpr Neutral SwapNeutral<Neutral::pi0>() {
  return Neutral::gamma;
}

template <Bachelor bachelor>
constexpr Bachelor SwapBachelor();

template <>
constexpr Bachelor SwapBachelor<Bachelor::k>() {
  return Bachelor::pi; 
}

template <>
constexpr Bachelor SwapBachelor<Bachelor::pi>() {
  return Bachelor::k;
}
