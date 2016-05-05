#include "Configuration.h"

Configuration::Configuration(Neutral neutral)
    : buMass_("", "", 0, 0, ""), buPdgId_("", "", 0, 0, "") {

  constexpr const char *kMassUnit = "Mev/c^2";
  constexpr const char *kMomentumUnit = "Mev/c";
  constexpr const char *kNoUnit = "";

  std::string buMassVar, buPdgIdVar;
  if (neutral == Neutral::pi0) {
    buMassVar = "Pi0_Bu_M_DTF_D0Pi0";
    buPdgIdVar = "Pi0_Bu_ID";
  } else {
    buMassVar = "Gamma_Bu_M_DTF_D0";
    buPdgIdVar = "Gamma_Bu_ID";
  }

  buMass_.SetName(buMassVar.c_str());
  buMass_.SetTitle("Bu Mass DTF Constrained");
  buMass_.setMin(4979);
  buMass_.setMax(5701);
  buMass_.setUnit(kMassUnit);

  buPdgId_.SetName(buPdgIdVar.c_str());
  buPdgId_.SetTitle("Bu PDG ID");
  buPdgId_.setMin(-550);
  buPdgId_.setMax(550);
  buPdgId_.setUnit(kNoUnit);
}

Categories::Categories()
    : polarity("polarity", "polarity"), charge("charge", "charge"),
      daughter("daughter", "daughter"), bachelor("bachelor", "bachelor"),
      neutral("neutral", "neutral"), year("year", "year") {

  polarity.defineType("up");
  polarity.defineType("down");
  polarity.defineType("both");

  charge.defineType("minus");
  charge.defineType("plus");

  daughter.defineType("kpi");
  daughter.defineType("kk");
  daughter.defineType("pipi");
  daughter.defineType("pik");

  bachelor.defineType("pi");
  bachelor.defineType("k");

  year.defineType("2011");
  year.defineType("2012");
  year.defineType("2015");

  neutral.defineType("pi0");
  neutral.defineType("gamma");
}

