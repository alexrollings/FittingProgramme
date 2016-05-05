#pragma once
#include <RooCategory.h>
#include <RooRealVar.h>
#include <string>

enum class Polarity { up, down, both };
enum class Daughter { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015 };
enum class Neutral { pi0, gamma };

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
