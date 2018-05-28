#include "Configuration.h"

Configuration::Configuration()
    : buMass_("", "", 0, 0, ""),
      buPdgId_("", "", 0, 0, ""),
      deltaMass_("", "", 0, 0, "") {
// constexpr means they're known at compile time and immutable (unchangable)
  constexpr const char *kMassUnit = "MeV/c^{2}";
  constexpr const char *kMomentumUnit = "MeV/c";
  constexpr const char *kNoUnit = "";

  buMass_.SetName("Bu_M_DTF_D0Pi0");
  buMass_.SetTitle("m[Bu]");
  buMass_.setMax(5805);
  buMass_.setMin(5045);
  buMass_.setBins(76);
  buMass_.setUnit(kMassUnit);

  buPdgId_.SetName("Bu_ID");
  buPdgId_.SetTitle("Bu PDG ID");
  buPdgId_.setMax(550);
  buPdgId_.setMin(-550);
  buPdgId_.setUnit(kNoUnit);

  deltaMass_.SetName("Delta_M");
  deltaMass_.SetTitle("m[D^{*0} - m[D^{0}]");
  deltaMass_.setMax(240);
  deltaMass_.setMin(80);
  deltaMass_.setBins(80);
  deltaMass_.setUnit(kMassUnit);

  variableArgSet_.add(buMass_);
  variableArgSet_.add(buPdgId_);
  variableArgSet_.add(deltaMass_);

  categoryArgSet_.add(categories().polarity);
  categoryArgSet_.add(categories().charge);
  categoryArgSet_.add(categories().daughters);
  categoryArgSet_.add(categories().bachelor);
  categoryArgSet_.add(categories().year);
  categoryArgSet_.add(categories().neutral);
  categoryArgSet_.add(categories().fitting);

  fullArgSet_.add(buMass_);
  fullArgSet_.add(deltaMass_);
  fullArgSet_.add(categoryArgSet_);
}
// Categories is a class within a class !!!
Configuration::Categories::Categories()
    : polarity("polarity", "polarity"),
      charge("charge", "charge"),
      daughters("daughters", "daughters"),
      bachelor("bachelor", "bachelor"),
      neutral("neutral", "neutral"),
      year("year", "year"),
      fitting("fitting", "fitting") {
  polarity.defineType(EnumToString(Polarity::up).c_str());
  polarity.defineType(EnumToString(Polarity::down).c_str());

  charge.defineType(EnumToString(Charge::plus).c_str());
  charge.defineType(EnumToString(Charge::minus).c_str());
  charge.defineType(EnumToString(Charge::total).c_str());

  daughters.defineType(EnumToString(Daughters::kpi).c_str());
  daughters.defineType(EnumToString(Daughters::kk).c_str());
  daughters.defineType(EnumToString(Daughters::pipi).c_str());
  daughters.defineType(EnumToString(Daughters::pik).c_str());

  bachelor.defineType(EnumToString(Bachelor::pi).c_str());
  bachelor.defineType(EnumToString(Bachelor::k).c_str());

  year.defineType(EnumToString(Year::y2011).c_str());
  year.defineType(EnumToString(Year::y2012).c_str());
  year.defineType(EnumToString(Year::y2015).c_str());
  year.defineType(EnumToString(Year::y2016).c_str());

  neutral.defineType(EnumToString(Neutral::pi0).c_str());
  neutral.defineType(EnumToString(Neutral::gamma).c_str());

  // PlotOn only takes one category as an option therefore we need to encompass
  // both bachelor and daughters in the same category
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::pi,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(
      ComposeFittingName(Neutral::pi0, Bachelor::k, Daughters::kk, Charge::plus)
          .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::pi0, Bachelor::k,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::pi,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Neutral::gamma, Bachelor::k,
                                        Daughters::pik, Charge::total)
                         .c_str());
}

// Need a template for this as each enum option is a different 'type'
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
Daughters StringToEnum<Daughters>(std::string const &daughters) {
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
  } else if (year == "2016") {
    return Year::y2016;
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
      return "2015";
    case Year::y2016:
      return "2016";
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
  } else if (charge == "total") {
    return Charge::total;
  } else {
    throw std::invalid_argument("Charge must take a value in [plus/minus]");
  }
}

std::string EnumToString(Charge charge) {
  switch (charge) {
    case Charge::plus:
      return "plus";
    case Charge::minus:
      return "minus";
    case Charge::total:
      return "total";
  }
}

std::string ComposeFilename(Year year, Polarity polarity, Bachelor bachelor,
                            Neutral neutral, Daughters daughters,
                            Charge charge) {
  return EnumToString(year) + "_" + EnumToString(polarity) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(neutral) + "_" +
         EnumToString(daughters) + "_" + EnumToString(charge);
}

std::string ComposeFittingName(Neutral neutral, Bachelor bachelor,
                        Daughters daughters, Charge charge) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
         EnumToString(daughters) + "_" + EnumToString(charge);
}

std::string EnumToLabel(Charge charge) {
  switch (charge) {
    case Charge::minus:
      return "-";
    case Charge::plus:
      return "+";
    case Charge::total:
      return "#pm";
  }
}

std::string EnumToLabel(Daughters daughters, Charge charge) {
  switch (daughters) {
    case Daughters::kpi:
      switch (charge) {
        case Charge::minus:
          return "K^{-}#pi^{+}";
        case Charge::plus:
          return "K^{+}#pi^{-}";
        case Charge::total:
          return "K^{pm}#pi^{mp}";
      }
    case Daughters::kk:
      return "K^{+}K^{-}";
    case Daughters::pipi:
      return "#pi^{+}#pi^{-}";
    case Daughters::pik:
      switch (charge) {
        case Charge::minus:
          return "#pi^{-}K^{+}";
        case Charge::plus:
          return "#pi^{+}K^{-}";
        case Charge::total:
          return "#pi^{#pm}K^{#mp}";
      }
  }
}

std::string EnumToLabel(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "#pi";
    case Bachelor::k:
      return "K";
  }
}

std::string EnumToLabel(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "#pi^{0}";
    case Neutral::gamma:
      return "#gamma";
  }
}

std::string MissIdLabel(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "K";
    case Bachelor::k:
      return "#pi";
  }
}

std::string HstLabel(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "#rho";
    case Bachelor::k:
      return "K^{*}";
  }
}

std::string CrossFeedLabel(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "#gamma";
    case Neutral::gamma:
      return "#pi^{0}";
  }
}
