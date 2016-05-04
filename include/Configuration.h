#pragma once
#include <RooRealVar.h>
#include <string>

enum class Polarity { up, down, both };
enum class Daughter { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015 };
enum class Neutral { pi0, gamma };

class Configuration {
  std::string const &buMass() const { return buMass_; }
  std::string const &buPdgId() const { return buPdgId_; }
  Configuration(Neutral neutral);
private:
  std::string buMass_{};
  std::string buPdgId_{};  
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
