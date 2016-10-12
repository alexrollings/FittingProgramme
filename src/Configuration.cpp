#include "Configuration.h"

Configuration::Configuration()
    : buMass_("", "", 0, 0, ""), buPdgId_("", "", 0, 0, ""),
      relativeWidth_("relatvieWidth", "Relative Width of k w.r.t. pi modes",
                     0.95),
      R_Dk_vs_Dpi_Bd2DstH_("R_Dk_vs_Dpi_Bd2DstH",
                            "Ratio of yields of Bd2DstH decay channel for K "
                            "w.r.t. pi bachelor",
                            0.078, 0, 0.1) {

  constexpr const char *kMassUnit = "MeV/c^{2}";
  constexpr const char *kMomentumUnit = "MeV/c";
  constexpr const char *kNoUnit = "";

  buMass_.SetName("Pi0_Bu_M_DTF_D0Pi0");
  buMass_.SetTitle("m[Bu]");
  buMass_.setMax(5805);
  buMass_.setMin(5045);
  buMass_.setBins(76);
  buMass_.setUnit(kMassUnit);

  buPdgId_.SetName("Pi0_Bu_ID");
  buPdgId_.SetTitle("Bu PDG ID");
  buPdgId_.setMax(550);
  buPdgId_.setMin(-550);
  buPdgId_.setUnit(kNoUnit);

  variableArgSet_.add(buMass_);
  variableArgSet_.add(buPdgId_);

  categoryArgSet_.add(categories().polarity);
  categoryArgSet_.add(categories().charge);
  categoryArgSet_.add(categories().daughters);
  categoryArgSet_.add(categories().bachelor);
  categoryArgSet_.add(categories().year);
  categoryArgSet_.add(categories().neutral);
  categoryArgSet_.add(categories().fitting);

  fullArgSet_.add(buMass_);
  fullArgSet_.add(categoryArgSet_);
}
// Categories is a class within a class !!!
Configuration::Categories::Categories()
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
      (EnumToString(Neutral::pi0) + "_" + EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::kpi))
          .c_str());
  fitting.defineType(
      (EnumToString(Neutral::pi0) + "_" + EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::kk)).c_str());
  fitting.defineType(
      (EnumToString(Neutral::pi0) + "_" + EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::pipi))
          .c_str());
  fitting.defineType(
      (EnumToString(Neutral::pi0) + "_" + EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::pik))
          .c_str());
  fitting.defineType(
      (EnumToString(Neutral::pi0) + "_" + EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::kpi)).c_str());
  fitting.defineType(
      (EnumToString(Neutral::pi0) + "_" + EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::kk)).c_str());
  fitting.defineType(
      (EnumToString(Neutral::pi0) + "_" + EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::pipi))
          .c_str());
  fitting.defineType(
      (EnumToString(Neutral::pi0) + "_" + EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::pik)).c_str());
  fitting.defineType(
      (EnumToString(Neutral::gamma) + "_" + EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::kpi))
          .c_str());
  fitting.defineType(
      (EnumToString(Neutral::gamma) + "_" + EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::kk)).c_str());
  fitting.defineType(
      (EnumToString(Neutral::gamma) + "_" + EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::pipi))
          .c_str());
  fitting.defineType(
      (EnumToString(Neutral::gamma) + "_" + EnumToString(Bachelor::pi) + "_" + EnumToString(Daughters::pik))
          .c_str());
  fitting.defineType(
      (EnumToString(Neutral::gamma) + "_" + EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::kpi)).c_str());
  fitting.defineType(
      (EnumToString(Neutral::gamma) + "_" + EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::kk)).c_str());
  fitting.defineType(
      (EnumToString(Neutral::gamma) + "_" + EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::pipi))
          .c_str());
  fitting.defineType(
      (EnumToString(Neutral::gamma) + "_" + EnumToString(Bachelor::k) + "_" + EnumToString(Daughters::pik)).c_str());
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

std::string ComposeName(Neutral neutral, Bachelor bachelor, Daughters daughters) {
  return EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" + EnumToString(daughters);
}

std::string ComposeName(Neutral neutral, Daughters daughters) {
  return EnumToString(neutral) + "_" + EnumToString(daughters);
}

std::string EnumToLabel(std::vector<Charge> chargeVec) {
  if (chargeVec.size() == 2 || chargeVec[0] == Charge::minus) {
    return "-";
  } else { 
      return "+";
  }
}

std::string EnumToLabel(Daughters daughters, std::vector<Charge> chargeVec) {
  switch (daughters) {
    case Daughters::kpi:
      if (chargeVec.size() == 2 || chargeVec[0] == Charge::minus) {    
        return "K^{-}#pi^{+}";
      } else {  
        return "K^{+}#pi^{-}";
      }
    case Daughters::kk:
      return "K^{+}K^{-}";
    case Daughters::pipi:
        return "#pi^{+}#pi^{-}";
    case Daughters::pik:
      if (chargeVec.size() == 2 || chargeVec[0] == Charge::minus) {    
        return "#pi^{-}K^{+}";
      } else {  
        return "#pi^{+}K^{-}";
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

