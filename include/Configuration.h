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
  Bu2Dst0rho,
  Bu2Dst0Kst_D0gamma,
  Bu2Dst0Kst_D0pi0,
  Bu2Dst0Kst,
  Bu2Dst0pi_D0gamma,
  Bu2Dst0K_D0gamma,
  Bu2Dst0pi_D0gamma_D02pik,
  Bu2Dst0K_D0gamma_D02pik,
  Bu2Dst0pi_D0gamma_WN_D02pik,
  Bu2Dst0K_D0gamma_WN_D02pik,
  Bu2Dst0pi_D0gamma_WN,
  Bu2Dst0K_D0gamma_WN,
  Bu2Dst0pi_D0pi0,
  Bu2Dst0K_D0pi0,
  Bu2Dst0pi_D0pi0_D02pik,
  Bu2Dst0K_D0pi0_D02pik,
  Bu2Dst0pi_D0pi0_WN_D02pik,
  Bu2Dst0K_D0pi0_WN_D02pik,
  Bu2Dst0pi_D0pi0_WN,
  Bu2Dst0K_D0pi0_WN,
  Bu2Dst0pi_WN,
  Bu2Dst0K_WN,
  Lb2Omegacpi_Lcpi0,
  Lb2OmegacK_Lcpi0
};
// Gamma only: BuPartial, crossFeedBu, gamma
// Pi0 only: Bu2Dst0h_D0pi0_PdfBu_ (crossFeed not added)
enum class Systematic {
  NA,
  Bu2Dst0h_D0pi0_PdfDelta_SigmaRatioKpi,
  Bu2Dst0h_D0pi0_PdfDelta_Tails,
  Bu2Dst0h_D0pi0_PdfDelta_Frac,
  Bu2Dst0h_D0pi0_PdfBu_SigmaRatioKpi,
  Bu2Dst0h_D0pi0_PdfBu_Tails,
  Bu2Dst0h_D0pi0_PdfBu_Frac,
  Bu2Dst0h_D0pi0_PdfBuPartial_MeanOffset,
  Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatioKpi,
  Bu2Dst0h_D0pi0_PdfBuPartial_SigmaRatio,
  Bu2Dst0h_D0pi0_PdfBuPartial_Tails,
  Bu2Dst0h_D0pi0_PdfBuPartial_Frac,
  Bu2Dst0h_D0pi0_PdfBuPartial_Sigma1,
  Bu2Dst0h_D0pi0_PdfBu,
  Bu2Dst0h_D0gamma_PdfBuPartial,
  Bu2Dst0h_D0gamma_PdfDelta_SigmaRatioKpi,
  Bu2Dst0h_D0gamma_PdfDelta_Tails,
  Bu2Dst0h_D0gamma_PdfDelta_Frac,
  Bu2Dst0h_D0gamma_PdfBu_SigmaRatioKpi,
  Bu2Dst0h_D0gamma_PdfBu_Tails,
  Bu2Dst0h_D0gamma_PdfBu_Frac,
  Bu2Dst0h_D0pi0_WN_PdfDelta,
  Bu2Dst0h_D0pi0_WN_PdfBu,
  Bu2Dst0h_D0pi0_WN_PdfBuPartial,
  Bu2Dst0h_D0gamma_WN_PdfDelta,
  Bu2Dst0h_D0gamma_WN_PdfBu,
  Bu2Dst0h_D0gamma_WN_PdfBuPartial,
  // Bu2Dst0h_WN_Frac,
  Bd2Dsth_PdfDelta,
  Bd2Dsth_PdfBu,
  Bd2Dsth_PdfBuPartial,
  Bu2D0hst_PdfDelta,
  Bu2D0hst_PdfDelta_D02pik,
  Bu2D0hst_PdfBu,
  Bu2D0hst_PdfBu_D02pik,
  Bu2D0hst_PdfBuPartial,
  Bu2Dst0hst_D0gamma_PdfDelta,
  Bu2Dst0hst_D0gamma_PdfBu,
  Bu2Dst0hst_D0gamma_PdfBuPartial,
  Bu2Dst0hst_D0pi0_PdfDelta,
  Bu2Dst0hst_D0pi0_PdfBu,
  Bu2Dst0hst_D0pi0_PdfBuPartial,
  Bu2Dst0hst_PdfBu_D02pik,
  Bu2Dst0hst_Frac,
  Lb2Omegach_Lcpi0_PdfDelta,
  Lb2Omegach_Lcpi0_PdfBu,
  Lb2Omegach_Lcpi0_PdfBuPartial,
  Bs2Dst0Kpi_PdfDelta,
  Bs2Dst0Kpi_PdfBu,
  Bs2Dst0Kpi_PdfBuPartial,
  Bs2D0Kpi_PdfDelta,
  Bs2D0Kpi_PdfBu,
  Bs2D0Kpi_PdfBuPartial,
  Bu2Dst0K_D0pi0_asPi_PdfBu,
  Bu2Dst0pi_D0pi0_asK_PdfBu,
  Bu2Dst0K_D0pi0_asPi_PdfDelta,
  Bu2Dst0pi_D0pi0_asK_PdfDelta,
  Bu2Dst0K_D0pi0_asPi_PdfBuPartial,
  Bu2Dst0pi_D0pi0_asK_PdfBuPartial,
  Bu2Dst0K_D0pi0_WN_asPi_PdfBu,
  Bu2Dst0pi_D0pi0_WN_asK_PdfBu,
  Bu2Dst0K_D0pi0_WN_asPi_PdfDelta,
  Bu2Dst0pi_D0pi0_WN_asK_PdfDelta,
  Bu2Dst0K_D0pi0_WN_asPi_PdfBuPartial,
  Bu2Dst0pi_D0pi0_WN_asK_PdfBuPartial,
  Bu2Dst0K_D0gamma_asPi_PdfBu,
  Bu2Dst0pi_D0gamma_asK_PdfBu,
  Bu2Dst0K_D0gamma_asPi_PdfDelta,
  Bu2Dst0pi_D0gamma_asK_PdfDelta,
  Bu2Dst0K_D0gamma_WN_asPi_PdfBu,
  Bu2Dst0pi_D0gamma_WN_asK_PdfBu,
  Bu2Dst0K_D0gamma_WN_asPi_PdfDelta,
  Bu2Dst0pi_D0gamma_WN_asK_PdfDelta,
  Bu2Dst0K_D0gamma_WN_asPi_PdfBuPartial,
  Bu2Dst0pi_D0gamma_WN_asK_PdfBuPartial,
  Bd2Dstpi_asK_PdfBu,
  Bd2Dstpi_asK_PdfDelta,
  Bd2Dstpi_asK_PdfBuPartial,
  Bu2D0rho_asK_PdfBu,
  Bu2D0rho_asK_PdfDelta,
  Bu2D0rho_asK_PdfBuPartial,
  Bu2Dst0rho_D0gamma_asK_PdfBu,
  Bu2Dst0rho_D0gamma_asK_PdfDelta,
  Bu2Dst0rho_D0gamma_asK_PdfBuPartial,
  Bu2Dst0rho_D0pi0_asK_PdfBu,
  Bu2Dst0rho_D0pi0_asK_PdfDelta,
  Bu2Dst0rho_D0pi0_asK_PdfBuPartial,
  Bu2Dst0h_D0pi0_D02pik_Pdfs,
  Bu2Dst0h_D0pi0_WN_D02pik_Pdfs,
  Bu2Dst0h_D0gamma_D02pik_Pdfs,
  Bu2Dst0h_D0gamma_WN_D02pik_Pdfs,
  boxEffs_Bu2Dst0h_D0pi0,
  boxEffs_Bu2Dst0h_D0gamma,
  boxEffs_Bkg,
  boxEffs_Bs2Dst0Kpi,
  boxEffs_Bs2D0Kpi,
  boxEffs_D02pik,
  boxEffs_Bu2Dst0h_D0pi0_misId,
  boxEffs_Bu2Dst0h_D0gamma_misId,
  boxEffs_Bkg_misId,
  mcEffs_Bu2Dst0h_D0pi0,
  mcEffs_Bu2Dst0h_D0gamma,
  mcEffs_Bkg,
  mcEffs_Bu2Dst0h_D0pi0_misId,
  mcEffs_Bu2Dst0h_D0gamma_misId,
  mcEffs_Bkg_misId,
  Bu2D0hst_BkgFrac,
  Bu2Dst0hst_BkgFrac,
  Bs2D0Kpi_BkgFrac,
  pidEffPi,
  pidEffK,
  crossFeedRate,
  A_pi_Kpi_Bu2Dst0h_D0pi0,
  A_pi_Kpi_Bu2Dst0h_D0gamma,
  A_pi_Kpi_Bu2Dst0h_WN,
  A_pi_Kpi_Bu2D0hst,
  A_pi_Kpi_Bu2Dst0hst,
  A_K_Kpi_Bu2Dst0h_WN,
  A_K_Kpi_Bu2D0hst,
  A_K_Kpi_Bu2Dst0hst,
  A_K_piK_Bu2D0hst,
  A_Kpi,
  A_pi,
  Delta_A_CP,
  R_CP_Bu2D0hst,
  R_ADS_Bu2D0hst,
  A_CP_pi_Bu2D0hst,
  A_CP_K_Bu2D0hst,
  R_Dst0KDst0pi_Bd2Dsth,
  R_Dst0KDst0pi_Lb2Omegach_Lcpi0,
  kBF_D02kpi,
  kBF_D02kk,
  kBF_D02pipi,
  // DON'T RUN BELOW
  kBF_Bu2Dst0pi,
  kBF_Bu2Dst0K,
  kBF_Dst02D0pi0,
  kBF_Dst02D0gamma,
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
  RooRealVar &d0Mass() { return d0Mass_; }
  RooRealVar &d0MassSwap() { return d0MassSwap_; }
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
  bool &simpleFit() { return simpleFit_; }
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
  RooRealVar d0Mass_;
  RooRealVar d0MassSwap_;
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
  bool simpleFit_;
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


std::string ReturnLaTeXLabel(Mode, Daughters, Charge, bool);
