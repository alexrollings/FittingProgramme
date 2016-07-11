#pragma once
#include <RooCategory.h>
#include <RooRealVar.h>
#include <string>

enum class Polarity { up, down };
enum class Daughters { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015 };
enum class Neutral { pi0, gamma };
enum class Charge { plus, minus };

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

class Configuration {

public:
  Configuration(Neutral neutral, Categories const &categories);
  Configuration(Configuration const &) = delete;
  Configuration(Configuration &&) = delete;
  Configuration &operator=(Configuration const &) = delete;
  Configuration &operator=(Configuration &&) = delete;

  RooRealVar &buMass() { return buMass_; }
  RooRealVar &buPdgId() { return buPdgId_; }
  RooArgSet &variableArgSet() { return variableArgSet_; }
  RooArgSet &categoryArgSet() { return categoryArgSet_; }
  RooArgSet &fullArgSet() { return fullArgSet_; }

private:
  RooRealVar buMass_;
  RooRealVar buPdgId_;
  RooArgSet variableArgSet_;
  RooArgSet categoryArgSet_;
  RooArgSet fullArgSet_;
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

std::string ComposeFittingCategoryName(Bachelor bachelor, Daughters daughters);
