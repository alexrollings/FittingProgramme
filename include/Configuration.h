#pragma once
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooArgSet.h"
#include <string>

enum class Polarity { up, down };
enum class Daughters { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015, y2016, y2017, y2018 };
enum class Neutral { pi0, gamma };
enum class Charge { plus, minus, total };

// There is only a single instance of categories therefore we do not have to pass it around any more
class Configuration {
 public:
  static Configuration &Get() {
    static Configuration singleton;
    return singleton;
  }
  // What about categories???
  struct Categories {
    RooCategory fitting;
    RooCategory charge;
    Categories();
    Categories(Categories const &) = delete;
    Categories(Categories &&) = delete;
    Categories &operator=(Categories const &) = delete;
    Categories &operator=(Categories &&) = delete;
  };
  
  Categories &categories() { return categories_; }
  RooRealVar &buMass() { return buMass_; }
  RooRealVar &buDeltaMass() { return buDeltaMass_; }
  RooRealVar &deltaMass() { return deltaMass_; }
  RooRealVar &pi0Mass() { return pi0Mass_; }
  RooRealVar &d0hMass() { return d0hMass_; }
  RooRealVar &buPdgId() { return buPdgId_; }
  RooRealVar &bachPID() { return bachPID_; }
  RooRealVar &h1PID() { return h1PID_; }
  RooRealVar &h2PID() { return h2PID_; }
  RooRealVar &h1ID() { return h1ID_; }
  RooRealVar &h2ID() { return h2ID_; }
  RooRealVar &BDT1() { return BDT1_; }
  RooRealVar &BDT2() { return BDT2_; }
  RooRealVar &hAngle() { return hAngle_; }
  RooRealVar &d0FdSig() { return d0FdSig_; }
  RooArgSet &variableArgSet() { return variableArgSet_; }
  RooArgSet &fittingArgSet() { return fittingArgSet_; }
  RooArgSet &categoryArgSet() { return categoryArgSet_; }
  RooArgSet &fullArgSet() { return fullArgSet_; }
  double &buFitMin() { return buFitMin_; }
  double &buFitMax() { return buFitMax_; }
  double &buFitBins() { return buFitBins_; }
  double &deltaFitMin() { return deltaFitMin_; }
  double &deltaFitMax() { return deltaFitMax_; }
  
  RooConstVar &pidEff() { return pidEff_; }

 private:
  Configuration();
  Configuration(Configuration const &) = delete;
  Configuration(Configuration &&) = delete;
  Configuration &operator=(Configuration const &) = delete;
  Configuration &operator=(Configuration &&) = delete;

  Categories categories_;
  RooRealVar buMass_;
  RooRealVar buDeltaMass_;
  RooRealVar deltaMass_;
  RooRealVar pi0Mass_;
  RooRealVar d0hMass_;
  RooRealVar buPdgId_;
  RooRealVar bachPID_;
  RooRealVar h1PID_;
  RooRealVar h2PID_;
  RooRealVar h1ID_;
  RooRealVar h2ID_;
  RooRealVar BDT1_;
  RooRealVar BDT2_;
  RooRealVar hAngle_;
  RooRealVar d0FdSig_;
  RooArgSet variableArgSet_;
  RooArgSet fittingArgSet_;
  RooArgSet categoryArgSet_;
  RooArgSet fullArgSet_;
  double buFitMin_;
  double buFitMax_;
  double buFitBins_;
  double deltaFitMin_;
  double deltaFitMax_;
  double deltaFitBins_;
  
  RooConstVar pidEff_;
};


template <typename Enum> Enum StringToEnum(std::string const &);

std::string EnumToString(Polarity);
std::string EnumToString(Daughters);
std::string EnumToString(Bachelor);
std::string EnumToString(Year);
std::string EnumToString(Neutral);
std::string EnumToString(Charge);

std::string EnumToLabel(Charge charge);
std::string EnumToLabel(Daughters, Charge charge);
std::string EnumToLabel(Bachelor);
std::string EnumToLabel(Neutral);
std::string MissIdLabel(Bachelor);
std::string CrossFeedLabel(Neutral);
std::string HstLabel(Bachelor);

std::string ComposeFilename(Year year, Polarity polarity, Bachelor bachelor,
                            Neutral neutral, Daughters daughters,
                            Charge charge);

std::string ComposeFittingName(Neutral neutral, Bachelor bachelor, Daughters daughters, Charge charge);

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
