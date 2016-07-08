#include "Configuration.h"

Configuration::Configuration(Neutral neutral, Categories const &categories)
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
  buMass_.setMax(5805);
  buMass_.setMin(5040);
  buMass_.setBins(152);
  buMass_.setUnit(kMassUnit);

  buPdgId_.SetName(buPdgIdVar.c_str());
  buPdgId_.SetTitle("Bu PDG ID");
  buPdgId_.setMax(550);
  buPdgId_.setMin(-550);
  buPdgId_.setUnit(kNoUnit);

  variableArgSet_.add(buMass_);
  variableArgSet_.add(buPdgId_);

  categoryArgSet_.add(categories.polarity);
  categoryArgSet_.add(categories.charge);
  categoryArgSet_.add(categories.daughters);
  categoryArgSet_.add(categories.bachelor);
  categoryArgSet_.add(categories.year);
  categoryArgSet_.add(categories.neutral);
  categoryArgSet_.add(categories.fitting);

  fullArgSet_.add(variableArgSet_);
  fullArgSet_.add(categoryArgSet_);
}
// Categories is a class within a class !!!
Categories::Categories()
    : polarity("polarity", "polarity"), charge("charge", "charge"),
      daughters("daughters", "daughters"), bachelor("bachelor", "bachelor"),
      neutral("neutral", "neutral"), year("year", "year"),
      fitting("fitting", "fitting") {

  polarity.defineType(EnumToString(Polarity::up).c_str());
  polarity.defineType(EnumToString(Polarity::down).c_str());

  charge.defineType(EnumToString(Charge::plus).c_str());
  charge.defineType(EnumToString(Charge::minus).c_str());

  daughters.defineType(EnumToString(Daughters::kpi).c_str());
  daughters.defineType(EnumToString(Daughters::kk).c_str());
  daughters.defineType(EnumToString(Daughters::pipi).c_str());
  daughters.defineType(EnumToString(Daughters::pik).c_str());

  bachelor.defineType(EnumToString(Bachelor::pi).c_str());
  bachelor.defineType(EnumToString(Bachelor::k).c_str());

  year.defineType(EnumToString(Year::y2011).c_str());
  year.defineType(EnumToString(Year::y2012).c_str());
  year.defineType(EnumToString(Year::y2015).c_str());

  neutral.defineType(EnumToString(Neutral::pi0).c_str());
  neutral.defineType(EnumToString(Neutral::gamma).c_str());

  // PlotOn only takes one category as an option therefore we need to encompass
  // both bachelor and daughters in the same category
  fitting.defineType(
      (EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::kpi))
          .c_str());
  fitting.defineType(
      (EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::kk)).c_str());
  fitting.defineType(
      (EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::pipi))
          .c_str());
  fitting.defineType(
      (EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::pik))
          .c_str());
  fitting.defineType(
      (EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::kpi)).c_str());
  fitting.defineType(
      (EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::kk)).c_str());
  fitting.defineType(
      (EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::pipi))
          .c_str());
  fitting.defineType(
      (EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::pik)).c_str());
}

// Need a template for this as each enum option is a different 'type'
template <> Polarity StringToEnum<Polarity>(std::string const &polarity) {
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

template <> Daughters StringToEnum<Daughters>(std::string const &daughters) {
  if (daughters == "kpi") {
    return Daughters::kpi;
  } else if (daughters == "kk") {
    return Daughters::kk;
  } else if (daughters == "pipi") {
    return Daughters::pipi;
  } else if (daughters == "pik") {
    return Daughters::pik;
  }
  throw std::invalid_argument(
      "Daughters must take a value in [kpi/kk/pipi/pik]");
}

std::string EnumToString(Daughters daughters) {
  switch (daughters) {
  case Daughters::kpi:
    return "kpi";
  case Daughters::kk:
    return "kk";
  case Daughters::pipi:
    return "pipi";
  case Daughters::pik:
    // default:
    return "pik";
  }
}

template <> Bachelor StringToEnum<Bachelor>(std::string const &bachelor) {
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

template <> Year StringToEnum<Year>(std::string const &year) {
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

template <> Neutral StringToEnum<Neutral>(std::string const &neutral) {
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

template <> Charge StringToEnum<Charge>(std::string const &charge) {
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
                            Neutral neutral, Daughters daughters,
                            Charge charge) {
  return EnumToString(year) + "_" + EnumToString(polarity) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(neutral) + "_" +
         EnumToString(daughters) + "_" + EnumToString(charge);
}

std::string ComposeFittingCategoryName(Bachelor bachelor, Daughters daughters) {
  return EnumToString(bachelor) + "_" + EnumToString(daughters);
}

std::string MakePdfTitle(Bachelor bachelor, Daughters daughters,
                         Neutral neutral, std::vector<Charge> chargeVec) {

  std::string firstDaughter;
  std::string secondDaughter;
  std::string bachelorString;
  std::string neutralString;

  if (bachelor == Bachelor::pi) {
    bachelorString = "#pi";
  } else {
    bachelorString = "K";
  }

  if (daughters == Daughters::kpi) {
    firstDaughter = "K";
    secondDaughter = "#pi";
  } else if (daughters == Daughters::kk) {
    firstDaughter = "K";
    secondDaughter = "K";
  } else if (daughters == Daughters::pipi) {
    firstDaughter = "#pi";
    secondDaughter = "#pi";
  } else {
    firstDaughter = "#pi";
    secondDaughter = "K";
  }

  if(neutral == Neutral::pi0){
    neutralString = "#pi^{0}";
  } else {
    neutralString = "#gamma";
  }

  if (chargeVec.size() == 2) {
    return "B^{-}#rightarrow#font[132]{[}#font[132]{[}" + firstDaughter +
           "^{-}" + secondDaughter + "^{+}#font[132]{]}_{D}" +
           neutralString + "#font[132]{]}_{D^{*}}" + bachelorString + "^{-}";
  } else if (chargeVec[0] == Charge::plus) {
    return "B^{+}#rightarrow#font[132]{[}#font[132]{[}" + firstDaughter +
           "^{+}" + secondDaughter + "^{-}#font[132]{]}_{D}" +
           neutralString + "#font[132]{]}_{D^{*}}" + bachelorString + "^{+}";
  } else {
    return "B^{-}#rightarrow#font[132]{[}#font[132]{[}" + firstDaughter +
           "^{-}" + secondDaughter + "^{+}#font[132]{]}_{D}" +
           neutralString + "#font[132]{]}_{D^{*}}" + bachelorString + "^{-}";
  }
}
