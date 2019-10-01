#include "Configuration.h"

Configuration::Configuration()
    : buMass_("", "", 0, 0, ""),
      buDeltaMass_("", "", 0, 0, ""),
      deltaMass_("", "", 0, 0, ""),
      pi0Mass_("", "", 0, 0, ""),
      d0hMass_("", "", 0, 0, ""),
      buPdgId_("", "", 0, 0, ""),
      bachPID_("", "", 0, 0, ""),
      h1ID_("", "", 0, 0, ""),
      h2ID_("", "", 0, 0, ""),
      h1PID_("", "", 0, 0, ""),
      h2PID_("", "", 0, 0, ""),
      BDT1_("", "", 0, 0, ""),
      BDT2_("", "", 0, 0, ""),
      hAngle_("", "", 0, 0, ""),
      d0FdSig_("", "", 0, 0, ""),
      deltaLow_(125),
      deltaHigh_(170),
      buDeltaLow_(5240),
      buDeltaHigh_(5330),
      initYieldFAVSignal_(6.7315e+04),
      gammaCutString_(
          "Bu_Delta_M>4900&&Bu_Delta_M<5800&&Delta_M>60&&Delta_M<190&&BDT1>0."
          "05&&BDT2>0.05&&D0h_M>4900&&D0_FD_ZSIG>2"),
      pi0CutString_(
          "Bu_Delta_M>4900&&Bu_Delta_M<5800&&Delta_M>60&&Delta_M<190&&BDT1>0."
          "05&&BDT2>0.05&&Pi0_M<165&&Pi0_M>125&&D0h_M>4900&&D0_FD_ZSIG>2"),
      fit1D_(false) {
  // constexpr means they're known at compile time and immutable (unchangable)
  constexpr const char *kMassUnit = "MeV/c^{2}";
  constexpr const char *kMomentumUnit = "MeV/c";
  constexpr const char *kNoUnit = "";

  buMass_.SetName("Bu_M_DTF");
  buMass_.SetTitle("m[Bu]");
  buMass_.setMax(5800);
  buMass_.setMin(4900);
  buMass_.setBins(75);
  // buMass_.setMax(6000);
  // buMass_.setMin(4000);
  // buMass_.setBins(400);
  buMass_.setUnit(kMassUnit);

  buDeltaMass_.SetName("Bu_Delta_M");
  buDeltaMass_.SetTitle("m[Bu] - m[D^{*0}] + m[D^{*0}]_{PDG}");
  buDeltaMass_.setMax(5800);
  buDeltaMass_.setMin(4900);
  buDeltaMass_.setBins(75);
  // buDeltaMass_.setMax(6000);
  // buDeltaMass_.setMin(4000);
  // buDeltaMass_.setBins(400);
  buDeltaMass_.setUnit(kMassUnit);

  deltaMass_.SetName("Delta_M");
  deltaMass_.SetTitle("m[D^{*0}] - m[D^{0}]");
  deltaMass_.setMax(190);
  deltaMass_.setMin(60);
  deltaMass_.setBins(65);
  // deltaMass_.setMax(250);
  // deltaMass_.setMin(0);
  // deltaMass_.setBins(125);
  deltaMass_.setUnit(kMassUnit);

  pi0Mass_.SetName("Pi0_M");
  pi0Mass_.SetTitle("m[#pi^{0}]");
  pi0Mass_.setMax(185);
  pi0Mass_.setMin(110);
  pi0Mass_.setUnit(kMassUnit);

  d0hMass_.SetName("D0h_M");
  d0hMass_.SetTitle("m[D^{0}h]");
  d0hMass_.setMax(6000);
  d0hMass_.setMin(4000);
  d0hMass_.setBins(400);
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

  h1ID_.SetName("h1_D_ID");
  h1ID_.SetTitle("h1 D0 daughter ID");
  h1ID_.setMax(550);
  h1ID_.setMin(-550);
  h1ID_.setUnit(kNoUnit);

  h2ID_.SetName("h2_D_ID");
  h2ID_.SetTitle("h2 D0 daughter ID");
  h2ID_.setMax(550);
  h2ID_.setMin(-550);
  h2ID_.setUnit(kNoUnit);

  h1PID_.SetName("h1_D_PIDK");
  h1PID_.SetTitle("h1 D0 daughter PIDK");
  h1PID_.setMax(150);
  h1PID_.setMin(-150);
  h1PID_.setUnit(kNoUnit);

  h2PID_.SetName("h2_D_PIDK");
  h2PID_.SetTitle("h2 D0 daughter PIDK");
  h2PID_.setMax(150);
  h2PID_.setMin(-150);
  h2PID_.setUnit(kNoUnit);

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

  d0FdSig_.setUnit(kNoUnit);
  d0FdSig_.SetName("D0_FD_ZSIG");
  d0FdSig_.SetTitle("D0 z-axis flight distance significance");
  d0FdSig_.setMax(300);
  d0FdSig_.setMin(-100);
  d0FdSig_.setUnit(kNoUnit);

  variableArgSet_.add(buMass_);
  variableArgSet_.add(buDeltaMass_);
  variableArgSet_.add(deltaMass_);
  variableArgSet_.add(pi0Mass_);
  variableArgSet_.add(d0hMass_);
  variableArgSet_.add(buPdgId_);
  variableArgSet_.add(bachPID_);
  variableArgSet_.add(h1ID_);
  variableArgSet_.add(h2ID_);
  variableArgSet_.add(h1PID_);
  variableArgSet_.add(h2PID_);
  variableArgSet_.add(BDT1_);
  variableArgSet_.add(BDT2_);
  variableArgSet_.add(hAngle_);
  variableArgSet_.add(d0FdSig_);

  fullArgSet_.add(variableArgSet_);

  fittingArgSet_.add(buDeltaMass_);
  fittingArgSet_.add(deltaMass_);
}
// Categories is a class within a class !!!
Configuration::Categories::Categories()
    : fitting("fitting", "fitting") {

  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::kpi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::kk, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::pipi, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::pik, Charge::total)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::kpi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::kk, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::pipi, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::pik, Charge::plus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::kpi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::kk, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::pipi, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::pi,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0, Bachelor::k,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0, Bachelor::k,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::pi,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma, Bachelor::k,
                                        Daughters::pik, Charge::minus)
                         .c_str());
  fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma, Bachelor::k,
                                        Daughters::pik, Charge::minus)
                         .c_str());
}

// Function returns delta mass string if 1D fit, full box dimns if D1D fit
std::string Configuration::ReturnBoxString() {
  if (fit1D_ == true) {
    return std::to_string(deltaLow_) + "_" + std::to_string(deltaHigh_);
  } else {
    return std::to_string(deltaLow_) + "_" + std::to_string(deltaHigh_) + "_" +
           std::to_string(buDeltaLow_) + "_" + std::to_string(buDeltaHigh_);
  }
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
  } else if (year == "2017") {
    return Year::y2017;
  } else if (year == "2018") {
    return Year::y2018;
  }
  throw std::invalid_argument(
      "Year must take a value in [2011/2012/2015/2016/2017/2018]");
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
    case Year::y2017:
      return "2017";
    case Year::y2018:
      return "2018";
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

std::string EnumToString(Mass mass) {
  switch (mass) {
    case Mass::buDelta:
      return "buDelta";
    case Mass::delta:
      return "delta";
  }
}

std::string EnumToString(Mode mode) {
  switch (mode) {
    case Mode::Bd2Dstpi:
      return "Bd2Dstpi";
      break;
    case Mode::Bu2D0pi:
      return "Bu2D0pi";
      break;
    case Mode::Bu2D0rho:
      return "Bu2D0rho";
      break;
    case Mode::Bu2Dst0rho_D0gamma:
      return "Bu2Dst0rho_D0gamma";
      break;
    case Mode::Bu2Dst0rho_D0pi0:
      return "Bu2Dst0rho_D0pi0";
      break;
    case Mode::Bu2Dst0pi_D0gamma:
      return "Bu2Dst0pi_D0gamma";
      break;
    case Mode::Bu2Dst0K_D0gamma:
      return "Bu2Dst0K_D0gamma";
      break;
    case Mode::Bu2Dst0pi_D0gamma_WN:
      return "Bu2Dst0pi_D0gamma_WN";
      break;
    case Mode::Bu2Dst0pi_D0pi0:
      return "Bu2Dst0pi_D0pi0";
      break;
    case Mode::Bu2Dst0K_D0pi0:
      return "Bu2Dst0K_D0pi0";
      break;
    case Mode::Bu2Dst0pi_D0pi0_WN:
      return "Bu2Dst0pi_D0pi0_WN";
      break;
  }
}

std::string ComposeFilename(Year year, Polarity polarity, Bachelor bachelor,
                            Neutral neutral, Daughters daughters,
                            Charge charge) {
  return EnumToString(year) + "_" + EnumToString(polarity) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(neutral) + "_" +
         EnumToString(daughters) + "_" + EnumToString(charge);
}

std::string ComposeFittingName(Mass mass, Neutral neutral, Bachelor bachelor,
                        Daughters daughters, Charge charge) {
  return EnumToString(mass) + "_" + EnumToString(neutral) + "_" + EnumToString(bachelor) + "_" +
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

std::string MisIdLabel(Bachelor bachelor) {
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

std::string MisIdHstLabel(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "K^{*}";
    case Bachelor::k:
      return "#rho";
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
