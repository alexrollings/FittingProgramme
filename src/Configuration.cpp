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
  buMass_.setMax(5701);
  buMass_.setMin(4979);
  buMass_.setUnit(kMassUnit);

  buPdgId_.SetName(buPdgIdVar.c_str());
  buPdgId_.SetTitle("Bu PDG ID");
  buPdgId_.setMax(550);
  buPdgId_.setMin(-550);
  buPdgId_.setUnit(kNoUnit);
}

Categories::Categories()
    : polarity("polarity", "polarity"), charge("charge", "charge"),
      daughter("daughter", "daughter"), bachelor("bachelor", "bachelor"),
      neutral("neutral", "neutral"), year("year", "year") {

  polarity.defineType(EnumToString(Polarity::up).c_str());
  polarity.defineType(EnumToString(Polarity::down).c_str());

  charge.defineType(EnumToString(Charge::plus).c_str());
  charge.defineType(EnumToString(Charge::minus).c_str());

  daughter.defineType(EnumToString(Daughter::kpi).c_str());
  daughter.defineType(EnumToString(Daughter::kk).c_str());
  daughter.defineType(EnumToString(Daughter::pipi).c_str());
  daughter.defineType(EnumToString(Daughter::pik).c_str());

  bachelor.defineType(EnumToString(Bachelor::pi).c_str());
  bachelor.defineType(EnumToString(Bachelor::k).c_str());

  year.defineType(EnumToString(Year::y2011).c_str());
  year.defineType(EnumToString(Year::y2012).c_str());
  year.defineType(EnumToString(Year::y2015).c_str());

  neutral.defineType(EnumToString(Neutral::pi0).c_str());
  neutral.defineType(EnumToString(Neutral::gamma).c_str());
}

//Need a template for this as each enum option is a different 'type'
template <>
Polarity StringToEnum<Polarity>(std::string const &polarity) {
  if (polarity == "up") {
    return Polarity::up;
  } else if (polarity == "down") {
    return Polarity::down;
  // } else if (polarity == "both") {
  //   return Polarity::both;
   }
  throw std::invalid_argument("Polarity must take a value in [up/down]");
}

std::string EnumToString(Polarity polarity) {
  switch (polarity) {
    case Polarity::up:
      return "up";
    case Polarity::down:
      return "down";
    // case Polarity::both:
    // default:
    //   return "both";
  }
}

template <>
Daughter StringToEnum<Daughter>(std::string const &daughter) {
  if (daughter == "kpi") {
    return Daughter::kpi;
  } else if (daughter == "kk") {
    return Daughter::kk;
  } else if (daughter == "pipi") {
    return Daughter::pipi;
  } else if (daughter == "pik") {
    return Daughter::pik;
  }
  throw std::invalid_argument(
      "Daughter must take a value in [kpi/kk/pipi/pik]");
}

std::string EnumToString(Daughter daughter) {
  switch (daughter) {
    case Daughter::kpi:
      return "kpi";
    case Daughter::kk:
      return "kk";
    case Daughter::pipi:
      return "pipi";
    case Daughter::pik:
    // default:
      return "pik";
  }
}

template <>
Bachelor StringToEnum<Bachelor>(std::string const &bachelor) {
  if (bachelor == "pi") {
    return Bachelor::pi;
  } else if (bachelor == "k") {
    return Bachelor::k;
  }
  throw std::invalid_argument("Bachelor must take a value in [pi/k]");
}

std::string EnumToString(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "pi";
    case Bachelor::k:
    // default:
      return "k";
  }
}

template <>
Year StringToEnum<Year>(std::string const &year) {
  if (year == "2011") {
    return Year::y2011;
  } else if (year == "2012") {
    return Year::y2012;
  } else if (year == "2015") {
    return Year::y2015;
  }
  throw std::invalid_argument("Year must take a value in [2011/2012/2015]");
}

std::string EnumToString(Year year) {
  switch (year) {
    case Year::y2011:
      return "2011";
    case Year::y2012:
      return "2012";
    case Year::y2015:
    // default:
      return "2015";
  }
}

template <>
Neutral StringToEnum<Neutral>(std::string const &neutral) {
  if (neutral == "pi0") {
    return Neutral::pi0;
  } else if (neutral == "gamma") {
    return Neutral::gamma;
  }
  throw std::invalid_argument("Neutral must take a value in [pi0/gamma]");
}

std::string EnumToString(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "pi0";
    case Neutral::gamma:
    // default:
      return "gamma";
  }
}

template <>
Charge StringToEnum<Charge>(std::string const &charge) {
  if (charge == "plus") {
    return Charge::plus;
  } else if (charge == "minus") {
    return Charge::minus;
  }
  throw std::invalid_argument("Charge must take a value in [plus/minus]");
}

std::string EnumToString(Charge charge) {
  switch (charge) {
    case Charge::plus:
      return "plus";
    case Charge::minus:
    // default:
      return "minus";
  }
}

std::string ComposeFilename(Year year, Polarity polarity, Bachelor bachelor,
                            Neutral neutral, Daughter daughter, Charge charge) {
  return EnumToString(year) + "_" + EnumToString(polarity) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(neutral) + "_" +
         EnumToString(daughter) + "_" + EnumToString(charge);
}
