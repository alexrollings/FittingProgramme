#include "Configuration.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include "Params.h"

Configuration::Configuration()
    : neutral_(),
      fitting("fitting", "fitting"),
      dataLabel("dataLabel", "dataLabel"),
      buMass_("", "", 0, 0, ""),
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
      buDeltaLow_(5240.0),
      buDeltaHigh_(5330.0),
      deltaLow_(125.0),
      deltaHigh_(170.0),
      deltaPartialLow_(60.0),
      deltaPartialHigh_(105.0),
      initYieldFAVSignal_(60000),
      pidEffK_(Params::Get().CreateFixed("pidEffK", 0.98 * 6.8493e-01, 2e-02,
                                         Systematic::pidEffK, Sign::positive)),
      pidEffPi_(Params::Get().CreateFixed(
          "pidEffPi", 0.996, 3e-03, Systematic::pidEffPi, Sign::positive)),
      // pidEffPi_(Params::Get().CreateFloating("pidEffPi", 0.996, 0.5, 1.5)),
      gammaCutString_(
          "Bu_Delta_M>4900&&Bu_Delta_M<5800&&Delta_M>60&&Delta_M<190&&BDT1>0."
          "05&&BDT2>0.05&&D0h_M>4900&&D0_FD_ZSIG>2&&D0h_M<5200"),
      pi0CutString_(
          "Bu_Delta_M>4900&&Bu_Delta_M<5800&&Delta_M>60&&Delta_M<190&&BDT1>0."
          "05&&BDT2>0.05&&Pi0_M<165&&Pi0_M>125&&D0h_M>4900&&D0_FD_ZSIG>2&&D0h_"
          "M<5200"),
      fit1D_(false),
      runToy_(false),
      splitByCharge_(false),
      noFit_(false),
      fitBuPartial_(false),
      blindFit_(true),
      runSystematics_(false),
      runADS_(false),
      plotToys_(false),
      nCPU_(4) {
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
  buDeltaMass_.setMax(5500);
  buDeltaMass_.setMin(5050);
  buDeltaMass_.setBins(45);
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

// Function returns delta mass string if 1D fit, full box dimns if D1D fit
std::string Configuration::ReturnBoxString() {
  std::ostringstream out;
  if (fitBuPartial_ == true) {
    if (fit1D_ == true) {
      out << deltaPartialLow_ << "_"
          << deltaPartialHigh_ << "_" << deltaLow_ << "_" << deltaHigh_;
    } else {
      out << deltaPartialLow_ << "_"
          << deltaPartialHigh_ << "_" << deltaLow_ << "_" << deltaHigh_ << "_"
          << buDeltaLow_ << "_" << buDeltaHigh_;
    }
  } else {
    if (fit1D_ == true) {
      out << deltaLow_ << "_" << deltaHigh_;
    } else {
      out << deltaLow_ << "_" << deltaHigh_ << "_"
          << buDeltaLow_ << "_" << buDeltaHigh_;
    }
  }
  return out.str();
}

// Need a template for this as each enum option is a different 'type'
template <>
Systematic StringToEnum<Systematic>(std::string const &systematic) {
  if (systematic == "pi0DeltaTails") {
    return Systematic::pi0DeltaTails;
  } else if (systematic == "pi0DeltaFrac") {
    return Systematic::pi0DeltaFrac;
  } else if (systematic == "pi0BuTails") {
    return Systematic::pi0BuTails;
  } else if (systematic == "pi0BuPartialTails") {
    return Systematic::pi0BuPartialTails;
  } else if (systematic == "pi0BuPartialFrac") {
    return Systematic::pi0BuPartialFrac;
  } else if (systematic == "pi0BuPartialSigma1") {
    return Systematic::pi0BuPartialSigma1;
  } else if (systematic == "crossFeedBuPdf") {
    return Systematic::crossFeedBuPdf;
  } else if (systematic == "crossFeedBuPartialPdf") {
    return Systematic::crossFeedBuPartialPdf;
  } else if (systematic == "crossFeedDeltaPdf") {
    return Systematic::crossFeedDeltaPdf;
  } else if (systematic == "gammaDeltaTails") {
    return Systematic::gammaDeltaTails;
  } else if (systematic == "gammaDeltaFrac") {
    return Systematic::gammaDeltaFrac;
  } else if (systematic == "gammaBuTails") {
    return Systematic::gammaBuTails;
  } else if (systematic == "gammaBuFrac") {
    return Systematic::gammaBuFrac;
  } else if (systematic == "misRecDeltaPdf") {
    return Systematic::misRecDeltaPdf;
  } else if (systematic == "misRecBuPdf") {
    return Systematic::misRecBuPdf;
  } else if (systematic == "misRecBuPartialPdf") {
    return Systematic::misRecBuPartialPdf;
  } else if (systematic == "partRecDeltaPdf") {
    return Systematic::partRecDeltaPdf;
  } else if (systematic == "partRecBuPdf") {
    return Systematic::partRecBuPdf;
  } else if (systematic == "partRecBuPartialPdf") {
    return Systematic::partRecBuPartialPdf;
  } else if (systematic == "Bs2Dst0KpiDeltaPdf") {
    return Systematic::Bs2Dst0KpiDeltaPdf;
  } else if (systematic == "Bs2Dst0KpiBuPdf") {
    return Systematic::Bs2Dst0KpiBuPdf;
  } else if (systematic == "Bs2Dst0KpiBuPartialPdf") {
    return Systematic::Bs2Dst0KpiBuPartialPdf;
  } else if (systematic == "Bs2D0KpiDeltaPdf") {
    return Systematic::Bs2D0KpiDeltaPdf;
  } else if (systematic == "Bs2D0KpiBuPdf") {
    return Systematic::Bs2D0KpiBuPdf;
  } else if (systematic == "Bs2D0KpiBuPartialPdf") {
    return Systematic::Bs2D0KpiBuPartialPdf;
  } else if (systematic == "misIdPi0PiPdfBu") {
    return Systematic::misIdPi0PiPdfBu;
  } else if (systematic == "misIdPi0KPdfBu") {
    return Systematic::misIdPi0KPdfBu;
  } else if (systematic == "misIdPi0PiPdfBuPartial") {
    return Systematic::misIdPi0PiPdfBuPartial;
  } else if (systematic == "misIdPi0KPdfBuPartial") {
    return Systematic::misIdPi0KPdfBuPartial;
  } else if (systematic == "misIdGammaPiPdfBu") {
    return Systematic::misIdGammaPiPdfBu;
  } else if (systematic == "misIdGammaKPdfBu") {
    return Systematic::misIdGammaKPdfBu;
  } else if (systematic == "misIdMisRecKPdfBu") {
    return Systematic::misIdMisRecKPdfBu;
  } else if (systematic == "misIdMisRecKPdfBuPartial") {
    return Systematic::misIdMisRecKPdfBuPartial;
  } else if (systematic == "misIdPartRecKPdfBu") {
    return Systematic::misIdPartRecKPdfBu;
  } else if (systematic == "misIdPartRecKPdfBuPartial") {
    return Systematic::misIdPartRecKPdfBuPartial;
  } else if (systematic == "buDeltaCutEffs") {
    return Systematic::buDeltaCutEffs;
  } else if (systematic == "deltaCutEffs") {
    return Systematic::deltaCutEffs;
  } else if (systematic == "deltaPartialCutEffs") {
    return Systematic::deltaPartialCutEffs;
  } else if (systematic == "buDeltaMisIdCutEffs") {
    return Systematic::buDeltaMisIdCutEffs;
  } else if (systematic == "deltaMisIdCutEffs") {
    return Systematic::deltaMisIdCutEffs;
  } else if (systematic == "deltaPartialMisIdCutEffs") {
    return Systematic::deltaPartialMisIdCutEffs;
  } else if (systematic == "pidEffPi") {
    return Systematic::pidEffPi;
  } else if (systematic == "pidEffK") {
    return Systematic::pidEffK;
  }
  throw std::invalid_argument(
      "Systematic must take a value in "
      "[pi0DeltaTails/pi0DeltaFrac/pi0BuTails/pi0BuPartialTails/"
      "pi0BuPartialFrac/pi0BuPartialSigma1/"
      "crossFeedBuPdf/crossFeedBuPartialPdf/crossFeedDeltaPdf/gammaDeltaTails/"
      "gammaDeltaFrac/gammaBuTails/gammaBuFrac/misRecDeltaPdf/misRecBuPdf/"
      "misRecBuPartialPdf/partRecDeltaPdf/partRecBuPdf/"
      "partRecBuPartialPdf/Bs2Dst0KpiDeltaPdf/Bs2Dst0KpiBuPdf/"
      "Bs2Dst0KpiBuPartialPdf/Bs2D0KpiDeltaPdf/Bs2D0KpiBuPdf/"
      "Bs2D0KpiBuPartialPdf/misIdPi0PiPdfBu/misIdPi0KPdfBu/"
      "misIdPi0PiPdfBuPartial/misIdPi0KPdfBuPartial/misIdGammaPiPdfBu/"
      "misIdGammaKPdfBu/misIdMisRecKPdfBu/misIdMisRecKPdfBuPartial/"
      "misIdPartRecKPdfBu/misIdPartRecKPdfBuPartial/buDeltaCutEffs/"
      "deltaCutEffs/deltaPartialCutEffs/"
      "deltaMisIdCutEffs/deltaPartialMisIdCutEffs/pidEffPi/pidEffK]");
}


std::string EnumToString(Systematic systematic) {
  switch (systematic) {
    case Systematic::pi0DeltaTails:
      return "pi0DeltaTails";
    case Systematic::pi0DeltaFrac:
      return "pi0DeltaFrac";
    case Systematic::pi0BuTails:
      return "pi0BuTails";
    case Systematic::pi0BuPartialTails:
      return "pi0BuPartialTails";
    case Systematic::pi0BuPartialFrac:
      return "pi0BuPartialFrac";
    case Systematic::pi0BuPartialSigma1:
      return "pi0BuPartialSigma1";
    case Systematic::crossFeedBuPdf:
      return "crossFeedBuPdf";
    case Systematic::crossFeedBuPartialPdf:
      return "crossFeedBuPartialPdf";
    case Systematic::crossFeedDeltaPdf:
      return "crossFeedDeltaPdf";
    case Systematic::gammaDeltaTails:
      return "gammaDeltaTails";
    case Systematic::gammaDeltaFrac:
      return "gammaDeltaFrac";
    case Systematic::gammaBuTails:
      return "gammaBuTails";
    case Systematic::gammaBuFrac:
      return "gammaBuFrac";
    case Systematic::misRecDeltaPdf:
      return "misRecDeltaPdf";
    case Systematic::misRecBuPdf:
      return "misRecBuPdf";
    case Systematic::misRecBuPartialPdf:
      return "misRecBuPartialPdf";
    case Systematic::partRecDeltaPdf:
      return "partRecDeltaPdf";
    case Systematic::partRecBuPdf:
      return "partRecBuPdf";
    case Systematic::partRecBuPartialPdf:
      return "partRecBuPartialPdf";
    case Systematic::Bs2Dst0KpiDeltaPdf:
      return "Bs2Dst0KpiDeltaPdf";
    case Systematic::Bs2Dst0KpiBuPdf:
      return "Bs2Dst0KpiBuPdf";
    case Systematic::Bs2Dst0KpiBuPartialPdf:
      return "Bs2Dst0KpiBuPartialPdf";
    case Systematic::Bs2D0KpiDeltaPdf:
      return "Bs2D0KpiDeltaPdf";
    case Systematic::Bs2D0KpiBuPdf:
      return "Bs2D0KpiBuPdf";
    case Systematic::Bs2D0KpiBuPartialPdf:
      return "Bs2D0KpiBuPartialPdf";
    case Systematic::misIdPi0PiPdfBu:
      return "misIdPi0PiPdfBu";
    case Systematic::misIdPi0KPdfBu:
      return "misIdPi0KPdfBu";
    case Systematic::misIdPi0PiPdfBuPartial:
      return "misIdPi0PiPdfBuPartial";
    case Systematic::misIdPi0KPdfBuPartial:
      return "misIdPi0KPdfBuPartial";
    case Systematic::misIdGammaPiPdfBu:
      return "misIdGammaPiPdfBu";
    case Systematic::misIdGammaKPdfBu:
      return "misIdGammaKPdfBu";
    case Systematic::misIdMisRecKPdfBu:
      return "misIdMisRecKPdfBu";
    case Systematic::misIdMisRecKPdfBuPartial:
      return "misIdMisRecKPdfBuPartial";
    case Systematic::misIdPartRecKPdfBu:
      return "misIdPartRecKPdfBu";
    case Systematic::misIdPartRecKPdfBuPartial:
      return "misIdPartRecKPdfBuPartial";
    case Systematic::buDeltaCutEffs:
      return "buDeltaCutEffs";
    case Systematic::deltaCutEffs:
      return "deltaCutEffs";
    case Systematic::deltaPartialCutEffs:
      return "deltaPartialCutEffs";
    case Systematic::buDeltaMisIdCutEffs:
      return "buDeltaMisIdCutEffs";
    case Systematic::deltaMisIdCutEffs:
      return "deltaMisIdCutEffs";
    case Systematic::deltaPartialMisIdCutEffs:
      return "deltaPartialMisIdCutEffs";
    case Systematic::pidEffPi:
      return "pidEffPi";
    case Systematic::pidEffK:
      return "pidEffK";
  }
}

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
    case Mass::buDeltaPartial:
      return "buDeltaPartial";
    case Mass::delta:
      return "delta";
  }
}

std::string EnumToString(Mode mode) {
  switch (mode) {
    case Mode::Bs2D0Kpi:
      return "Bs2D0Kpi";
      break;
    case Mode::Bs2Dst0Kpi:
      return "Bs2Dst0Kpi";
      break;
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
  return EnumToString(mass) + "_" + EnumToString(neutral) + "_" +
         EnumToString(bachelor) + "_" + EnumToString(daughters) + "_" +
         EnumToString(charge);
}

std::string ComposeDataLabelName(Neutral neutral, Bachelor bachelor,
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

void Configuration::DefineCategories() {
  switch (neutral()) {
    case Neutral::pi0:
      if (splitByCharge() == false) {
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kk,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pik,
                                              Charge::total)
                               .c_str());

        if (fit1D() == false) {
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kk,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pik,
                                                Charge::total)
                                 .c_str());
        }

        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kpi, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kpi, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kk, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kk, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pipi,
                                                  Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pipi,
                                                  Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pik, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pik, Charge::total)
                                 .c_str());
      } else {
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kk,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pik,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::kk,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::pi0,
                                              Bachelor::k, Daughters::pik,
                                              Charge::minus)
                               .c_str());
        if (fit1D() == false) {
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kk,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pik,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::kk,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::pi0,
                                                Bachelor::k, Daughters::pik,
                                                Charge::minus)
                                 .c_str());
        }

        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kpi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kpi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kk, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kk, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pipi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pipi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pik, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pik, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kpi, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kpi, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::kk, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::kk, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pipi,
                                                  Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pipi,
                                                  Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::pi,
                                                  Daughters::pik, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::pi0, Bachelor::k,
                                                  Daughters::pik, Charge::minus)
                                 .c_str());
      }
      break;
    case Neutral::gamma:
      if (splitByCharge() == false) {
        if (fit1D() == false) {
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kk,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::total)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pik,
                                                Charge::total)
                                 .c_str());
        }
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kk,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pik,
                                              Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kpi, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kpi, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kk, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kk, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pipi, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pipi, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pik, Charge::total)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pik, Charge::total)
                               .c_str());

        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kpi, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kpi, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kk, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kk, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pipi,
                                                  Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pipi,
                                                  Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pik, Charge::total)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pik, Charge::total)
                                 .c_str());
      } else {
        if (fit1D() == false) {
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kk,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pik,
                                                Charge::plus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kpi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kpi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::kk,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::kk,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pipi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pipi,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::pi, Daughters::pik,
                                                Charge::minus)
                                 .c_str());
          fitting.defineType(ComposeFittingName(Mass::delta, Neutral::gamma,
                                                Bachelor::k, Daughters::pik,
                                                Charge::minus)
                                 .c_str());
        }
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kk,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pik,
                                              Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kpi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kpi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::kk,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::kk,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pipi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pipi,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::pi, Daughters::pik,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDelta, Neutral::gamma,
                                              Bachelor::k, Daughters::pik,
                                              Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kpi, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kpi, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kk, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kk, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pipi, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pipi, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pik, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pik, Charge::plus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kpi, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kpi, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::kk, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::kk, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pipi, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pipi, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::pi,
                                              Daughters::pik, Charge::minus)
                               .c_str());
        fitting.defineType(ComposeFittingName(Mass::buDeltaPartial,
                                              Neutral::gamma, Bachelor::k,
                                              Daughters::pik, Charge::minus)
                               .c_str());

        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kpi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kpi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kk, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kk, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pipi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pipi, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pik, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pik, Charge::plus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kpi, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kpi, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::kk, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::kk, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pipi,
                                                  Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pipi,
                                                  Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::pi,
                                                  Daughters::pik, Charge::minus)
                                 .c_str());
        dataLabel.defineType(ComposeDataLabelName(Neutral::gamma, Bachelor::k,
                                                  Daughters::pik, Charge::minus)
                                 .c_str());
      }
      break;
  }
}

// inline allows a function to be defined multiple times. Templated functions
// are implicitly inline
inline bool file_exists(const std::string &name) {
  std::ifstream infile(name);
  return infile.good();
}

inline std::vector<std::string> SplitLine(std::string const &str) {
  std::stringstream ss;
  ss.str(str);
  std::string tempString;
  std::vector<std::string> stringVector;
  // '' = char
  while (std::getline(ss, tempString, ' ')) {
    stringVector.emplace_back(tempString);
  }
  return stringVector;
}

// Function to be called in constructor of NVars, in order to construct
// efficiency RCVars
// Anything defined outside the class definition needs the scope :: operator
void Configuration::ExtractChain(Mode mode, Bachelor bachelor, TChain &chain) {
  std::string modeString = EnumToString(mode);
  std::string dirString;
  // std::cout << txtFileName
  //           << " doesn't exist:\n\tCalculating and setting efficiencies
  //           for"
  //           << modeString << "...\n";
  if (mode == Mode::Bu2Dst0pi_D0gamma_WN || mode == Mode::Bu2Dst0pi_D0pi0_WN) {
    // To remove _WN for directory
    dirString = modeString.substr(0, modeString.size() - 3);
  } else {
    dirString = modeString;
  }

  std::string path, ttree;
  switch (neutral()) {
    case Neutral::gamma:
      switch (bachelor) {
        case Bachelor::pi:
          path =
              "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
              "cross_feed_removed/";
          break;
        case Bachelor::k:
          path =
              "gamma/bach_K/tmva_stage1/tmva_stage2_loose/to_fit/"
              "cross_feed_removed/";
          break;
      }
      ttree = "BtoDstar0h3_h1h2gammaTuple";
      break;
    case Neutral::pi0:
      switch (bachelor) {
        case Bachelor::pi:
          path = "pi0/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/";
          break;
        case Bachelor::k:
          path = "pi0/bach_K/tmva_stage1/tmva_stage2_loose/to_fit/";
          break;
      }
      ttree = "BtoDstar0h3_h1h2pi0RTuple";
      break;
  }

  std::string inputfile_1("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2011_MagUp/" + path + modeString +
                          "_2011_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_2("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2011_MagDown/" + path + modeString +
                          "_2011_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_3("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2012_MagUp/" + path + modeString +
                          "_2012_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_4("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2012_MagDown/" + path + modeString +
                          "_2012_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_5("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2015_MagUp/" + path + modeString +
                          "_2015_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_6("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2015_MagDown/" + path + modeString +
                          "_2015_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_7("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2016_MagUp/" + path + modeString +
                          "_2016_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_8("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                          dirString + "_2016_MagDown/" + path + modeString +
                          "_2016_MagDown_BDT1_BDT2_PID_TM.root");

  chain.Add(inputfile_1.c_str());
  chain.Add(inputfile_2.c_str());
  chain.Add(inputfile_3.c_str());
  chain.Add(inputfile_4.c_str());
  chain.Add(inputfile_5.c_str());
  chain.Add(inputfile_6.c_str());
  chain.Add(inputfile_7.c_str());
  chain.Add(inputfile_8.c_str());

  if (mode != Mode::Bu2Dst0pi_D0pi0 && mode != Mode::Bu2Dst0pi_D0gamma &&
      mode != Mode::Bu2Dst0pi_D0pi0_WN && mode != Mode::Bu2Dst0pi_D0gamma_WN &&
      mode != Mode::Bu2Dst0K_D0pi0 && mode != Mode::Bu2Dst0K_D0gamma) {
    std::string inputfile_9("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                            dirString + "_2015_MagUp/" + path + modeString +
                            "_2015_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_10("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                             dirString + "_ReDecay_2015_MagDown/" + path +
                             modeString +
                             "_ReDecay_2015_MagDown_BDT1_BDT2_PID_TM.root");
    std::string inputfile_11("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                             dirString + "_ReDecay_2016_MagUp/" + path +
                             modeString +
                             "_ReDecay_2016_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_12("/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" +
                             dirString + "_ReDecay_2016_MagDown/" + path +
                             modeString +
                             "_ReDecay_2016_MagDown_BDT1_BDT2_PID_TM.root");
    chain.Add(inputfile_9.c_str());
    chain.Add(inputfile_10.c_str());
    chain.Add(inputfile_11.c_str());
    chain.Add(inputfile_12.c_str());
  }
}

void CalcBinomialErr(double eff, double nInit, double err) {
  err = std::sqrt((eff * (1 - eff)) / nInit);
};

void Configuration::ReturnBoxEffs(Mode mode, Bachelor bachelor,
                                  std::map<std::string, double> &map,
                                  bool misId) {
  // std::cout << EnumToString(mode) << std::endl;
  std::string dlString = std::to_string(deltaLow_);
  std::string dhString = std::to_string(deltaHigh_);
  std::string blString = std::to_string(buDeltaLow_);
  std::string bhString = std::to_string(buDeltaHigh_);
  std::string dplString, dphString;
  if (fitBuPartial_ == true) {
    dplString = std::to_string(deltaPartialLow_);
    dphString = std::to_string(deltaPartialHigh_);
  }
  std::string txtFileName;
  if (misId == true) {
    txtFileName = "/data/lhcb/users/rollings/txt_efficiencies/" +
                  EnumToString(neutral()) + "_misId_" + EnumToString(mode) +
                  "_as_" + EnumToString(bachelor) + "_" + ReturnBoxString() +
                  ".txt";
  } else {
    txtFileName = "/data/lhcb/users/rollings/txt_efficiencies/" +
                  EnumToString(neutral()) + "_" + EnumToString(mode) + "_" +
                  ReturnBoxString() + ".txt";
  }

  // Check if txt file containing efficiencies for particular mode and box dimns
  // exists, if not, calculate eff and save in txt file
  if (plotToys_ == true || !file_exists(txtFileName)) {
    std::string cutString, ttree;

    switch (neutral()) {
      case Neutral::gamma:
        cutString = gammaCutString_;
        ttree = "BtoDstar0h3_h1h2gammaTuple";
        break;
      case Neutral::pi0:
        cutString = pi0CutString_;
        ttree = "BtoDstar0h3_h1h2pi0RTuple";
        break;
    }

    TChain chain(ttree.c_str());
    ExtractChain(mode, bachelor, chain);

    std::string orString;
    if (fitBuPartial_ == false) {
      if (fit1D_ == false) {
        orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                   ")||(Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString +
                   "))";
      } else {
        orString = "(Delta_M>" + dlString + "&&Delta_M<" + dhString + ")";
      }
    } else {
      if (fit1D_ == false) {
        orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                   ")||(Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString +
                   ")||(Delta_M>" + dplString + "&&Delta_M<" + dphString + "))";
      } else {
        orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                   ")||(Delta_M>" + dplString + "&&Delta_M<" + dphString + "))";
      }
    }
    double nOr = chain.GetEntries((cutString + "&&" + orString).c_str());
    if (plotToys_ == true) {
      double nInitial = chain.GetEntries(cutString.c_str());
      double nBox;
      if (fit1D_ == false) {
        nBox = chain.GetEntries((cutString + "&&Delta_M>" + dlString +
                                 "&&Delta_M<" + dhString + "&&Bu_Delta_M>" +
                                 blString + "&&Bu_Delta_M<" + bhString)
                                    .c_str());
      } else {
        nBox = 0.;
      }
      double orEff = nOr / nInitial;
      double orEffErr;
      CalcBinomialErr(orEff, nInitial, orEffErr);
      double boxEff = nBox / nInitial;
      double boxEffErr;
      CalcBinomialErr(boxEff, nInitial, boxEffErr);
      map.insert(std::pair<std::string, double>("orEff", orEff));
      map.insert(std::pair<std::string, double>("orEffErr", orEffErr));
      map.insert(std::pair<std::string, double>("boxEff", boxEff));
      map.insert(std::pair<std::string, double>("boxEffErr", boxEffErr));
      if (fitBuPartial_ == true) {
        double nBoxPartial;
        if (fit1D_ == false) {
          nBoxPartial = chain.GetEntries(
              (cutString + "&&Delta_M>" + dplString + "&&Delta_M<" + dphString +
               "&&Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString)
                  .c_str());
        } else {
          nBoxPartial = 0.;
        }
        double boxPartialEff = nBox / nInitial;
        double boxPartialEffErr;
        CalcBinomialErr(boxPartialEff, nInitial, boxPartialEffErr);
        map.insert(
            std::pair<std::string, double>("boxPartialEff", boxPartialEff));
        map.insert(
            std::pair<std::string, double>("boxPartialEffErr", boxPartialEffErr));
      }
    } else {
      double nBuCut =
          chain.GetEntries((cutString + "&&" + orString + "&&Bu_Delta_M>" +
                            blString + "&&Bu_Delta_M<" + bhString)
                               .c_str());
      double nDeltaCut =
          chain.GetEntries((cutString + "&&" + orString + "&&Delta_M>" +
                            dlString + "&&Delta_M<" + dhString)
                               .c_str());
      double buDeltaCutEff = nBuCut / nOr;
      double deltaCutEff = nDeltaCut / nOr;
      // Binomial expectation value: efficienciy = N_success (binomal: err =
      // sqrt(pq) / N (poisson: err = sqrt(N)) Error: pq / N = sqrt(eff*(1-eff)
      // / N) by propagation or errors
      double buDeltaCutEffErr;
      CalcBinomialErr(buDeltaCutEff, nOr, buDeltaCutEffErr);
      double deltaCutEffErr;
      CalcBinomialErr(deltaCutEff, nOr, deltaCutEffErr);

      std::ofstream outFile;
      outFile.open(txtFileName);
      outFile << "buDeltaCutEff " + std::to_string(buDeltaCutEff) + "\n";
      outFile << "buDeltaCutEffErr " + std::to_string(buDeltaCutEffErr) + "\n";
      outFile << "deltaCutEff " + std::to_string(deltaCutEff) + "\n";
      outFile << "deltaCutEffErr " + std::to_string(deltaCutEffErr) + "\n";

      map.insert(
          std::pair<std::string, double>("buDeltaCutEff", buDeltaCutEff));
      map.insert(
          std::pair<std::string, double>("buDeltaCutEffErr", buDeltaCutEffErr));
      map.insert(std::pair<std::string, double>("deltaCutEff", deltaCutEff));
      map.insert(
          std::pair<std::string, double>("deltaCutEffErr", deltaCutEffErr));

      double nDeltaPartialCut, deltaPartialCutEff, deltaPartialCutEffErr;
      if (fitBuPartial_ == true) {
        double nDeltaPartialCut =
            chain.GetEntries((cutString + "&&" + orString + "&&Delta_M>" +
                              dplString + "&&Delta_M<" + dphString)
                                 .c_str());
        deltaPartialCutEff = nDeltaPartialCut / nOr;
        double deltaPartialCutEffErr;
        CalcBinomialErr(deltaPartialCutEff, nOr, deltaPartialCutEffErr);
        outFile << "deltaPartialCutEff " + std::to_string(deltaPartialCutEff) +
                       "\n";
        outFile << "deltaPartialCutEffErr " +
                       std::to_string(deltaPartialCutEffErr) + "\n";
        map.insert(std::pair<std::string, double>("deltaPartialCutEff",
                                                  deltaPartialCutEff));
        map.insert(std::pair<std::string, double>("deltaPartialCutEffErr",
                                                  deltaPartialCutEffErr));
      }

      outFile.close();
    }
  } else {
    //   // If exists, read in from txt file
    // std::cout << txtFileName << " exists:\n\tReading efficiencies for "
    //           << EnumToString(mode) << "...\n";
    std::ifstream inFile(txtFileName);
    // Create map to store efficiency string (label) and eff value
    std::unordered_map<std::string, double> effMap;
    std::string line;
    // Loop over lines in txt file
    while (std::getline(inFile, line)) {
      // Separate label and value (white space)
      std::vector<std::string> lineVec = SplitLine(line);
      // Add to map
      map.insert(
          std::pair<std::string, double>(lineVec[0], std::stod(lineVec[1])));
    }
  }
}

// Place function to return ACP in config s.t. don't have to instantiate all
// gamma templates when running π0 fit and vice versa
double Configuration::ReturnACPInit(Neutral neutral, Bachelor bachelor) {
  double ACPInit = 0;
  switch (neutral) {
    case Neutral::gamma:
      switch (bachelor) {
        case Bachelor::pi:
          ACPInit = -0.003;
          break;
        case Bachelor::k:
          ACPInit = 0.276;
          break;
      }
      break;
    case Neutral::pi0:
      switch (bachelor) {
        case Bachelor::pi:
          ACPInit = 0.025;
          break;
        case Bachelor::k:
          ACPInit = -0.151;
          break;
      }
      break;
  }
}
