#pragma once
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooArgSet.h"
#include "RooUnblindUniform.h"
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
  Bd2DstK,
  Bu2D0pi,
  Bu2D0K,
  Bu2D0rho,
  Bu2D0Kst,
  Bu2Dst0rho_D0gamma,
  Bu2Dst0rho_D0pi0,
  Bu2Dst0Kst_D0gamma,
  Bu2Dst0Kst_D0pi0,
  Bu2Dst0pi_D0gamma,
  Bu2Dst0K_D0gamma,
  Bu2Dst0pi_D0gamma_D02pik,
  Bu2Dst0K_D0gamma_D02pik,
  Bu2Dst0pi_D0gamma_WN,
  Bu2Dst0K_D0gamma_WN,
  Bu2Dst0pi_D0pi0,
  Bu2Dst0K_D0pi0,
  Bu2Dst0pi_D0pi0_D02pik,
  Bu2Dst0K_D0pi0_D02pik,
  Bu2Dst0pi_D0pi0_WN,
  Bu2Dst0K_D0pi0_WN,
  Lb2Omegacpi_Lcpi0
};
// Gamma only: BuPartial, crossFeedBu, gamma
// Pi0 only: pi0Bu (crossFeed not added)
enum class Systematic {
  NA,
  pi0DeltaWidthRatio,
  pi0DeltaTails,
  pi0DeltaFrac,
  pi0BuWidthRatio,
  pi0BuTails,
  pi0BuFrac,
  pi0BuPartialWidthRatio,
  pi0BuPartialTails,
  pi0BuPartialFrac,
  pi0BuPartialSigma1,
  crossFeedBuPdf,
  crossFeedBuPartialPdf,
  crossFeedDeltaPdf,
  gammaDeltaWidthRatio,
  gammaDeltaTails,
  gammaDeltaFrac,
  gammaBuWidthRatio,
  gammaBuTails,
  gammaBuFrac,
  pi0WNDeltaPdf,
  pi0WNBuPdf,
  pi0WNBuPartialPdf,
  gammaWNDeltaPdf,
  gammaWNBuPdf,
  gammaWNBuPartialPdf,
  Bd2DsthDeltaPdf,
  Bd2DsthBuPdf,
  Bd2DsthBuPartialPdf,
  Bu2D0hstDeltaPdf,
  Bu2D0hstBuPdf,
  Bu2D0hstBuPartialPdf,
  Bu2Dst0hst_D0gammaDeltaPdf,
  Bu2Dst0hst_D0gammaBuPdf,
  Bu2Dst0hst_D0gammaBuPartialPdf,
  Bu2Dst0hst_D0pi0DeltaPdf,
  Bu2Dst0hst_D0pi0BuPdf,
  Bu2Dst0hst_D0pi0BuPartialPdf,
  misRecDeltaPdf,
  misRecBuPdf,
  misRecBuPartialPdf,
  partRecDeltaPdf,
  partRecBuPdf,
  partRecBuPartialPdf,
  Bs2Dst0KpiDeltaPdf,
  Bs2Dst0KpiBuPdf,
  Bs2Dst0KpiBuPartialPdf,
  Bs2D0KpiDeltaPdf,
  Bs2D0KpiBuPdf,
  Bs2D0KpiBuPartialPdf,
  misIdPi0PiPdfBu,
  misIdPi0KPdfBu,
  misIdPi0PiPdfDelta,
  misIdPi0KPdfDelta,
  misIdPi0PiPdfBuPartial,
  misIdPi0KPdfBuPartial,
  misIdPi0WNPiPdfBu,
  misIdPi0WNKPdfBu,
  misIdPi0WNPiPdfDelta,
  misIdPi0WNKPdfDelta,
  misIdPi0WNPiPdfBuPartial,
  misIdPi0WNKPdfBuPartial,
  misIdGammaPiPdfBu,
  misIdGammaKPdfBu,
  misIdGammaPiPdfDelta,
  misIdGammaKPdfDelta,
  misIdGammaWNPiPdfBu,
  misIdGammaWNKPdfBu,
  misIdGammaWNPiPdfDelta,
  misIdGammaWNKPdfDelta,
  misIdGammaWNPiPdfBuPartial,
  misIdGammaWNKPdfBuPartial,
  misIdBd2DsthKPdfBu,
  misIdBd2DsthKPdfDelta,
  misIdBd2DsthKPdfBuPartial,
  misIdBu2D0hstKPdfBu,
  misIdBu2D0hstKPdfDelta,
  misIdBu2D0hstKPdfBuPartial,
  misIdBu2Dst0hst_D0gammaKPdfBu,
  misIdBu2Dst0hst_D0gammaKPdfDelta,
  misIdBu2Dst0hst_D0gammaKPdfBuPartial,
  misIdBu2Dst0hst_D0pi0KPdfBu,
  misIdBu2Dst0hst_D0pi0KPdfDelta,
  misIdBu2Dst0hst_D0pi0KPdfBuPartial,
  misIdMisRecKPdfBu,
  misIdMisRecKPdfBuPartial,
  misIdPartRecKPdfBu,
  misIdPartRecKPdfBuPartial,
  gammaFAVasSUPDeltaPdf,
  gammaFAVasSUPBuPdf,
  pi0FAVasSUPDeltaPdf,
  pi0FAVasSUPBuPdf,
  pi0FAVasSUPBuPartialPdf,
  buDeltaCutEffs,
  deltaCutEffs,
  deltaPartialCutEffs,
  buDeltaMisIdCutEffs,
  deltaMisIdCutEffs,
  deltaPartialMisIdCutEffs,
  pidEffPi,
  pidEffK,
  crossFeedRate,
  A_FAV_Pi0,
  A_FAV_Gamma,
  A_Kpi,
  A_pi,
  Delta_A_CP,
  mcEffs,
  kBF_Bu2Dst0pi,
  kBF_Bu2Dst0K,
  kBF_Dst02D0pi0,
  kBF_Dst02D0gamma,
  kBF_D02kpi,
  kBF_D02kk,
  kBF_D02pipi,
  kBF_D02pik,
  kBF_Bd2Dstpi,
  kBF_Bd2DstK,
  kBF_Dst2D0pi,
  kBF_Bu2D0rho,
  kBF_Bu2D0Kst,
  kBF_Bd2D0rho0,
  kBF_Bd2D0Kst0,
  kBF_Bu2Dst0rho,
  kBF_Bu2Dst0Kst
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

  std::string ReturnBoxString();

  std::string &ReturnCutString() {
    if (neutral_ == Neutral::gamma) {
      return gammaCutString_;
    } else if (neutral_ == Neutral::pi0) {
      return pi0CutString_;
    } else {
      throw std::runtime_error(
          "Cannot return cutString before neutral is defined\n");
    }
  }

  bool &fit1D() { return fit1D_; }
  bool &runToy() { return runToy_; }
  bool &splitByCharge() { return splitByCharge_; }
  bool &noFit() { return noFit_; }
  bool &fitBuPartial() { return fitBuPartial_; }
  bool &blindFit() { return blindFit_; }
  bool &runSystematics() { return runSystematics_; }
  bool &runADS() { return runADS_; }
  bool &plotToys() { return plotToys_; }
  int nCPU() { return nCPU_; }

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
  std::string gammaCutString_;
  std::string pi0CutString_;
  bool fit1D_;
  bool runToy_;
  bool splitByCharge_;
  bool noFit_;
  bool fitBuPartial_;
  bool blindFit_;
  bool runSystematics_;
  bool runADS_;
  bool plotToys_;
  int nCPU_;
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

std::string ComposeName(int uniqueId, Mass mass, Neutral neutral,
                        Bachelor bachelor, Daughters daughters, Charge charge);
std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor, Daughters daughters, Charge charge);
std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor, Daughters daughters);
std::string ComposeName(int uniqueId, Neutral neutral,
                        Bachelor bachelor);
std::string ComposeName(int uniqueId, Bachelor bachelor);
std::string ComposeName(int uniqueId, 
                        Bachelor bachelor, Charge charge);
std::string ComposeName(int uniqueId, Daughters daughters);
std::string ComposeName(int uniqueId, Neutral neutral);
std::string ComposeName(int uniqueId, Neutral neutral, Charge charge);
std::string ComposeName(int uniqueId, Bachelor bachelor, Daughters daughters);
