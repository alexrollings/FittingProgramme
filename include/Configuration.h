#pragma once
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooArgSet.h"
#include "TChain.h" 
#include <string>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

enum class Polarity { up, down };
enum class Daughters { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015, y2016, y2017, y2018 };
enum class Neutral { pi0, gamma };
enum class Charge { plus, minus, total };
enum class Mass { buDelta, delta, buDeltaPartial };
enum class Mode {
  Bs2Dst0Kpi,
  Bs2D0Kpi,
  Bd2Dstpi,
  Bu2D0pi,
  Bu2D0rho,
  Bu2Dst0rho_D0gamma,
  Bu2Dst0rho_D0pi0,
  Bu2Dst0pi_D0gamma,
  Bu2Dst0K_D0gamma,
  Bu2Dst0pi_D0gamma_WN,
  Bu2Dst0pi_D0pi0,
  Bu2Dst0K_D0pi0,
  Bu2Dst0pi_D0pi0_WN
};
// Gamma only: BuPartial, crossFeedBu, gamma
// Pi0 only: pi0Bu (crossFeed not added)
enum class Systematic {
  NA,
  pi0DeltaTails,
  pi0DeltaFrac,
  pi0BuTails,
  pi0BuPartialTails,
  pi0BuPartialFrac,
  pi0BuPartialSigma1,
  crossFeedBuPdf,
  crossFeedBuPartialPdf,
  crossFeedDeltaPdf,
  gammaDeltaTails,
  gammaDeltaFrac,
  gammaBuTails,
  gammaBuFrac,
  misRecDeltaPdf,
  misRecBuPdf,
  misRecBuPartialPdf,
  partRecDeltaPdf,
  partRecBuPdf,
  partRecBuPartialPdf,
  misIdPi0PiPdfBu,
  misIdPi0KPdfBu,
  misIdPi0PiPdfBuPartial,
  misIdPi0KPdfBuPartial,
  misIdGammaPiPdfBu,
  misIdGammaKPdfBu,
  misIdMisRecKPdfBu,
  misIdMisRecKPdfBuPartial,
  misIdPartRecKPdfBu,
  misIdPartRecKPdfBuPartial,
  boxEffs,
  pidEffPi,
  pidEffK
};

// There is only a single instance of categories therefore we do not have to
// pass it around any more
class Configuration {
 public:
  static Configuration &Get() {
    static Configuration singleton;
    return singleton;
  }
  
  RooCategory fitting;
  RooCategory dataLabel;
  void DefineCategories(void);

  Neutral &neutral() { return neutral_; }
  void SetNeutral(Neutral neut) { neutral() = neut; }

  RooRealVar &buMass() { return buMass_; }
  RooRealVar &buDeltaMass() { return buDeltaMass_; }
  RooRealVar &deltaMass() { return deltaMass_; }
  RooRealVar &pi0Mass() { return pi0Mass_; }
  RooRealVar &d0hMass() { return d0hMass_; }
  RooRealVar &buPdgId() { return buPdgId_; }
  RooRealVar &bachPID() { return bachPID_; }
  RooRealVar &h1PID() { return h1PID_; }
  RooRealVar &h2PID() { return h2PID_; }
  RooRealVar &h1ID() { return h1ID_; }
  RooRealVar &h2ID() { return h2ID_; }
  RooRealVar &BDT1() { return BDT1_; }
  RooRealVar &BDT2() { return BDT2_; }
  RooRealVar &hAngle() { return hAngle_; }
  RooRealVar &d0FdSig() { return d0FdSig_; }
  RooArgSet &variableArgSet() { return variableArgSet_; }
  RooArgSet &fittingArgSet() { return fittingArgSet_; }
  RooArgSet &fullArgSet() { return fullArgSet_; }
  double &buFitMin() { return buFitMin_; }
  double &buFitMax() { return buFitMax_; }
  double &buFitBins() { return buFitBins_; }
  double &deltaFitMin() { return deltaFitMin_; }
  double &deltaFitMax() { return deltaFitMax_; }

  float &buDeltaLow() { return buDeltaLow_; }
  float &buDeltaHigh() { return buDeltaHigh_; }
  float &deltaLow() { return deltaLow_; }
  float &deltaHigh() { return deltaHigh_; }
  float &deltaPartialLow() { return deltaPartialLow_; }
  float &deltaPartialHigh() { return deltaPartialHigh_; }

  void SetBuDeltaLow(float val) { buDeltaLow() = val; }
  void SetBuDeltaHigh(float val) { buDeltaHigh() = val; }
  void SetDeltaLow(float val) { deltaLow() = val; }
  void SetDeltaHigh(float val) { deltaHigh() = val; }
  void SetDeltaPartialLow(float val) { deltaPartialLow() = val; }
  void SetDeltaPartialHigh(float val) { deltaPartialHigh() = val; }

  // Have to declare this in Config as gamma depends on pi0 and pi0 depends on
  // gamma in different neutral cases: always need to delcare signal yield first
  double &initYieldFAVSignal() { return initYieldFAVSignal_; }

  RooRealVar &GetPidEff(Bachelor bachelor) {
    if (bachelor == Bachelor::pi) {
      return *pidEffPi_;
    } else {
      return *pidEffK_;
    }
  }

  std::string ReturnBoxString();

  std::string &gammaCutString() { return gammaCutString_; }
  std::string &pi0CutString() { return pi0CutString_; }

  bool &fit1D() { return fit1D_; }
  bool &runToy() { return runToy_; }
  bool &splitByCharge() { return splitByCharge_; }
  bool &noFit() { return noFit_; }
  bool &fitBuPartial() { return fitBuPartial_; }
  bool &blindFit() { return blindFit_; }
  bool &runSystematics() { return runSystematics_; }

  void ExtractChain(Mode mode, Bachelor bachelor, TChain &chain);
  void SetEfficiencies(Mode mode, Bachelor bachelor, RooRealVar &buDeltaCutEff,
                       RooRealVar &deltaCutEff, bool misId);
  void SetEfficiencies(Mode mode, Bachelor bachelor, RooRealVar &buDeltaCutEff,
                       RooRealVar &deltaCutEff, RooRealVar &deltaPartialCutEff,
                       bool misId);
  double ReturnACPInit(Neutral neutral, Bachelor bachelor); 

 private:
  Configuration();
  Configuration(Configuration const &) = delete;
  Configuration(Configuration &&) = delete;
  Configuration &operator=(Configuration const &) = delete;
  Configuration &operator=(Configuration &&) = delete;

  Neutral neutral_;

  RooRealVar buMass_;
  RooRealVar buDeltaMass_;
  RooRealVar deltaMass_;
  RooRealVar pi0Mass_;
  RooRealVar d0hMass_;
  RooRealVar buPdgId_;
  RooRealVar bachPID_;
  RooRealVar h1PID_;
  RooRealVar h2PID_;
  RooRealVar h1ID_;
  RooRealVar h2ID_;
  RooRealVar BDT1_;
  RooRealVar BDT2_;
  RooRealVar hAngle_;
  RooRealVar d0FdSig_;
  RooArgSet variableArgSet_;
  RooArgSet fittingArgSet_;
  RooArgSet fullArgSet_;
  double buFitMin_;
  double buFitMax_;
  double buFitBins_;
  double deltaFitMin_;
  double deltaFitMax_;
  double deltaFitBins_;
  float buDeltaLow_;
  float buDeltaHigh_;
  float deltaLow_;
  float deltaHigh_;
  float deltaPartialLow_;
  float deltaPartialHigh_;
  double initYieldFAVSignal_;
  std::shared_ptr<RooRealVar> pidEffK_;
  std::shared_ptr<RooRealVar> pidEffPi_;
  std::string gammaCutString_;
  std::string pi0CutString_;
  bool fit1D_;
  bool runToy_;
  bool splitByCharge_;
  bool noFit_;
  bool fitBuPartial_;
  bool blindFit_;
  bool runSystematics_;
};

template <typename Enum> Enum StringToEnum(std::string const &);

std::string EnumToString(Systematic);
std::string EnumToString(Polarity);
std::string EnumToString(Daughters);
std::string EnumToString(Bachelor);
std::string EnumToString(Year);
std::string EnumToString(Neutral);
std::string EnumToString(Charge);
std::string EnumToString(Mass);
std::string EnumToString(Mode);

std::string EnumToLabel(Charge);
std::string EnumToLabel(Daughters, Charge);
std::string EnumToLabel(Bachelor);
std::string EnumToLabel(Neutral);

std::string ComposeFilename(Year year, Polarity polarity,
                            Bachelor bachelor, Neutral neutral,
                            Daughters daughters, Charge charge);

std::string ComposeFittingName(Mass mass, Neutral neutral, Bachelor bachelor, Daughters daughters, Charge charge);
std::string ComposeDataLabelName(Neutral neutral, Bachelor bachelor, Daughters daughters, Charge charge);
