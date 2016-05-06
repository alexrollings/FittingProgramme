#pragma once
#include <RooCategory.h>
#include <RooRealVar.h>
#include <string>

enum class Polarity { up, down, both };
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
