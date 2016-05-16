#pragma once
#include <RooCategory.h>
#include <RooRealVar.h>
#include <string>

enum class Polarity { up, down };
enum class Daughter { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015 };
enum class Neutral { pi0, gamma };
enum class Charge { plus, minus };

class Configuration {
public:
  RooRealVar const &buMass() const { return buMass_; }
  RooRealVar const &buPdgId() const { return buPdgId_; }
  Configuration(Neutral neutral);
  Configuration(Configuration const&) = delete;
  Configuration(Configuration &&) = delete;
  Configuration& operator=(Configuration const&) = delete;
  Configuration& operator=(Configuration &&) = delete;
private:
  RooRealVar buMass_;
  RooRealVar buPdgId_;  
};

struct Categories {
  RooCategory polarity;
  RooCategory charge;
  RooCategory daughter;
  RooCategory bachelor;
  RooCategory neutral;
  RooCategory year;
  Categories();
  Categories(Categories const &) = delete;
  Categories(Categories &&) = delete;
  Categories& operator=(Categories const&) = delete;
  Categories& operator=(Categories &&) = delete;
};

class Configuration {
public:
  RooRealVar &buMass() { return buMass_; }
  RooRealVar &buPdgId() { return buPdgId_; }
  RooArgSet &variableArgSet() { return variableArgSet_; }
  RooArgSet &categoryArgSet() { return categoryArgSet_; }
  RooArgSet &fullArgSet() { return fullArgSet_; }
  Configuration(Neutral neutral);
private:
  RooRealVar buMass_;
  RooRealVar buPdgId_;  
  RooArgSet variableArgSet_;
  RooArgSet categoryArgSet_;
  RooArgSet fullArgSet_;
};

template <typename Enum>
Enum StringToEnum(std::string const &);

std::string EnumToString(Polarity);
std::string EnumToString(Daughter);
std::string EnumToString(Bachelor);
std::string EnumToString(Year);
std::string EnumToString(Neutral);
std::string EnumToString(Charge);

std::string ComposeFilename(Year year, Polarity polarity, Bachelor bachelor,
                            Neutral neutral, Daughter daughter, Charge charge);
