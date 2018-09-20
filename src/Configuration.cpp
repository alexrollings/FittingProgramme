#include "Configuration.h"

Configuration::Configuration()
    : buMass_("", "", 0, 0, ""),
      deltaMass_("", "", 0, 0, ""),
      pi0Mass_("", "", 0, 0, ""),
      d0hMass_("", "", 0, 0, ""),
      buPdgId_("", "", 0, 0, ""),
      bachPID_("", "", 0, 0, ""),
      piPID_("", "", 0, 0, ""),
      kPID_("", "", 0, 0, ""),
      BDT1_("", "", 0, 0, ""),
      BDT2_("", "", 0, 0, ""),
      hAngle_("", "", 0, 0, ""),
      buFitMin_(5000),
      buFitMax_(5800),
      buFitBins_(160),
      deltaFitMin_(0),
      deltaFitMax_(250),
      deltaFitBins_(125) {
// constexpr means they're known at compile time and immutable (unchangable)
  constexpr const char *kMassUnit = "MeV/c^{2}";
  constexpr const char *kMomentumUnit = "MeV/c";
  constexpr const char *kNoUnit = "";

  buMass_.SetName("Bu_M_DTF");
  buMass_.SetTitle("m[Bu]");
  // FOR MAKING THE ROODATASETS
  // buMass_.setMax(6000);
  // buMass_.setMin(4000);
  // buMass_.setBins(400);
  // FOR FITTING THE ROODATASETS
  buMass_.setMax(5805);
  buMass_.setMin(4995);
  buMass_.setBins(162);
  buMass_.setUnit(kMassUnit);

  deltaMass_.SetName("Delta_M");
  deltaMass_.SetTitle("m[D^{*0} - m[D^{0}]");
  deltaMass_.setMax(250);
  deltaMass_.setMin(50);
  deltaMass_.setBins(100);
  deltaMass_.setUnit(kMassUnit);

  pi0Mass_.SetName("Pi0_M");
  pi0Mass_.SetTitle("m[#pi^{0}]");
  pi0Mass_.setMax(185);
  pi0Mass_.setMin(110);
  pi0Mass_.setBins(75);
  pi0Mass_.setUnit(kMassUnit);

  d0hMass_.SetName("D0h_M");
  d0hMass_.SetTitle("m[D^{0}h]");
  d0hMass_.setMax(5800);
  d0hMass_.setMin(4600);
  d0hMass_.setBins(240);
  d0hMass_.setUnit(kMassUnit);

  buPdgId_.SetName("Bu_ID");
  buPdgId_.SetTitle("Bu PDG ID");
  buPdgId_.setMax(550);
  buPdgId_.setMin(-550);
  buPdgId_.setUnit(kNoUnit);

  bachPID_.SetName("bach_PIDK");
  bachPID_.SetTitle("Bachelor PIDK");
  bachPID_.setMax(150);
  bachPID_.setMin(-150);
  bachPID_.setUnit(kNoUnit);

  piPID_.SetName("pi_D_PIDK");
  piPID_.SetTitle("pi D0 daughter PIDK");
  piPID_.setMax(150);
  piPID_.setMin(-150);
  piPID_.setUnit(kNoUnit);

  kPID_.SetName("K_D_PIDK");
  kPID_.SetTitle("K D0 daughter PIDK");
  kPID_.setMax(150);
  kPID_.setMin(-150);
  kPID_.setUnit(kNoUnit);

  BDT1_.SetName("BDT1");
  BDT1_.SetTitle("BDT1");
  BDT1_.setMax(0.5);
  BDT1_.setMin(-0.2);
  BDT1_.setUnit(kNoUnit);

  BDT2_.SetName("BDT2");
  BDT2_.SetTitle("BDT2");
  BDT2_.setMax(0.4);
  BDT2_.setMin(-0.3);
  BDT2_.setUnit(kNoUnit);

  hAngle_.SetName("DstNeut_Dst0_hAngle");
  hAngle_.SetTitle("Helicity Angle of neutral in D^{*0} rest frame");
  hAngle_.setMax(1);
  hAngle_.setMin(-1);
  hAngle_.setUnit(kNoUnit);

  variableArgSet_.add(buMass_);
  variableArgSet_.add(deltaMass_);
  variableArgSet_.add(pi0Mass_);
  variableArgSet_.add(d0hMass_);
  variableArgSet_.add(buPdgId_);
  variableArgSet_.add(bachPID_);
  variableArgSet_.add(piPID_);
  variableArgSet_.add(kPID_);
  variableArgSet_.add(BDT1_);
  variableArgSet_.add(BDT2_);
  variableArgSet_.add(hAngle_);

  categoryArgSet_.add(categories().fitting);
  categoryArgSet_.add(categories().charge);

  fullArgSet_.add(variableArgSet_);
  fullArgSet_.add(categoryArgSet_);

  fittingArgSet_.add(buMass_);
  fittingArgSet_.add(deltaMass_);
}
// Categories is a class within a class !!!
Configuration::Categories::Categories()
    : fitting("fitting", "fitting"),
      charge("charge", "charge") {

  charge.defineType("plus");
  charge.defineType("minus");
  charge.defineType("total");

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
          return "K^{#pm}#pi^{#mp}";
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
