#pragma once
#include "RooAbsPdf.h"
#include "RooFormulaVar.h"
#include "RooAddPdf.h"
#include "NeutralVars.h" 
#include "Configuration.h" 
#include "RooConstVar.h"

// Bachelor

template <Neutral neutral, Bachelor bachelor> class NeutralBachelorVars {

public:
  static NeutralBachelorVars<neutral, bachelor> &Get() {
    static NeutralBachelorVars<neutral, bachelor> singleton;
    return singleton;
  }

  RooAbsReal &sigmaSignal_1() { return *sigmaSignal_1_; }
  RooAbsReal &sigmaSignal_2() { return *sigmaSignal_2_; }
  RooAbsReal &sigmaCrossFeed_1() { return *sigmaCrossFeed_1_; }
  RooAbsReal &sigmaCrossFeed_2() { return *sigmaCrossFeed_2_; }
  RooAbsReal &sigmaNonTmSignal_1() { return *sigmaNonTmSignal_1_; }
  RooAbsReal &sigmaNonTmSignal_2() { return *sigmaNonTmSignal_2_; }
  RooAbsReal &sigmaBu2D0H_1() { return *sigmaBu2D0H_1_; }
  RooAbsReal &sigmaBu2D0H_2() { return *sigmaBu2D0H_2_; }
  RooAbsReal &sigmaBu2D0Hst() { return *sigmaBu2D0Hst_; }
  RooAbsReal &sigmaBd2DstH_1() { return *sigmaBd2DstH_1_; }
  RooAbsReal &sigmaBd2DstH_2() { return *sigmaBd2DstH_2_; }
  RooConstVar &meanBu2Dst0Hst_D0pi0() { return meanBu2Dst0Hst_D0pi0_; }
  RooConstVar &sigmaBu2Dst0Hst_D0pi0() { return sigmaBu2Dst0Hst_D0pi0_; }
  RooConstVar &aBu2Dst0Hst_D0pi0() { return aBu2Dst0Hst_D0pi0_; }
  RooConstVar &nBu2Dst0Hst_D0pi0() { return nBu2Dst0Hst_D0pi0_; }
  RooConstVar &meanBu2Dst0Hst_D0gamma() { return meanBu2Dst0Hst_D0gamma_; }
  RooConstVar &sigmaBu2Dst0Hst_D0gamma() { return sigmaBu2Dst0Hst_D0gamma_; }
  RooConstVar &aBu2Dst0Hst_D0gamma() {
    return aBu2Dst0Hst_D0gamma_;
  } // Not gamma, K
  RooConstVar &nBu2Dst0Hst_D0gamma() {
    return nBu2Dst0Hst_D0gamma_;
  } // Not gamma, K
  RooConstVar &meanMissId() { return meanMissId_; }
  RooConstVar &sigmaMissId1() { return sigmaMissId1_; }
  RooConstVar &sigmaMissId2() { return sigmaMissId2_; }
  RooConstVar &aMissId1() { return aMissId1_; }
  RooConstVar &aMissId2() { return aMissId2_; }
  RooConstVar &meanBu2D0HMissId() { return meanBu2D0HMissId_; }
  RooConstVar &sigmaBu2D0HMissId1() { return sigmaBu2D0HMissId1_; }
  RooConstVar &sigmaBu2D0HMissId2() { return sigmaBu2D0HMissId2_; }
  RooConstVar &aBu2D0HMissId1() { return aBu2D0HMissId1_; }
  RooConstVar &aBu2D0HMissId2() { return aBu2D0HMissId2_; }
  RooAbsPdf &signal() { return *signal_; }
  RooAbsPdf &crossFeed() { return *crossFeed_; }
  RooAbsPdf &nonTmSignal() { return *nonTmSignal_; }
  RooAbsPdf &bu2Dst0Hst_D0pi0() { return *bu2Dst0Hst_D0pi0_; }
  RooAbsPdf &bu2Dst0Hst_D0gamma() {
    return *bu2Dst0Hst_D0gamma_;
  }
  RooAbsPdf &bu2D0H_2() { return *bu2D0H_1_; }
  RooAbsPdf &bu2D0H_1() { return *bu2D0H_2_; }
  RooAbsPdf &bu2D0H() { return *bu2D0H_; }
  RooAbsPdf &bu2D0Hst() { return *bu2D0Hst_; }
  RooAbsPdf &bd2DstH() { return *bd2DstH_; }
  RooAbsPdf &missId() { return *missId_; }
  RooAbsPdf &bu2D0HMissId() { return *bu2D0HMissId_; }
  RooConstVar &missIdRate() { return missIdRate_; }
  RooConstVar &bachEff() { return bachEff_; }
  double &bachelorSF() { return bachelorSF_; }

private:
  NeutralBachelorVars();
  ~NeutralBachelorVars() {}

  std::unique_ptr<RooAbsReal> sigmaSignal_1_;
  std::unique_ptr<RooAbsReal> sigmaSignal_2_;
  std::unique_ptr<RooAbsReal> sigmaCrossFeed_1_;
  std::unique_ptr<RooAbsReal> sigmaCrossFeed_2_;
  std::unique_ptr<RooAbsReal> sigmaNonTmSignal_1_;
  std::unique_ptr<RooAbsReal> sigmaNonTmSignal_2_; 
  std::unique_ptr<RooAbsReal> sigmaBu2D0H_1_;
  std::unique_ptr<RooAbsReal> sigmaBu2D0H_2_;
  std::unique_ptr<RooAbsReal> sigmaBu2D0Hst_;
  std::unique_ptr<RooAbsReal> sigmaBd2DstH_1_;
  std::unique_ptr<RooAbsReal> sigmaBd2DstH_2_;
  RooConstVar meanBu2Dst0Hst_D0pi0_;
  RooConstVar sigmaBu2Dst0Hst_D0pi0_;
  RooConstVar aBu2Dst0Hst_D0pi0_;
  RooConstVar nBu2Dst0Hst_D0pi0_;
  RooConstVar meanBu2Dst0Hst_D0gamma_;
  RooConstVar sigmaBu2Dst0Hst_D0gamma_;
  RooConstVar aBu2Dst0Hst_D0gamma_;
  RooConstVar nBu2Dst0Hst_D0gamma_;
  RooConstVar meanMissId_;
  RooConstVar sigmaMissId1_;
  RooConstVar sigmaMissId2_;
  RooConstVar aMissId1_;
  RooConstVar aMissId2_;
  RooConstVar meanBu2D0HMissId_;
  RooConstVar sigmaBu2D0HMissId1_;
  RooConstVar sigmaBu2D0HMissId2_;
  RooConstVar aBu2D0HMissId1_;
  RooConstVar aBu2D0HMissId2_;

  RooConstVar missIdRate_;
  RooConstVar bachEff_;
  // By declaring the pointer to be a RooAbsPdf, we can then specialise the type
  // later (base class)
  std::unique_ptr<RooAbsPdf> signal_;
  std::unique_ptr<RooAbsPdf> crossFeed_;
  std::unique_ptr<RooAbsPdf> nonTmSignal_;
  std::unique_ptr<RooAbsPdf> bu2Dst0Hst_D0pi0_;
  std::unique_ptr<RooAbsPdf> bu2Dst0Hst_D0gamma_;
  std::unique_ptr<RooAbsPdf> bu2D0H_1_;
  std::unique_ptr<RooAbsPdf> bu2D0H_2_;
  std::unique_ptr<RooAbsPdf> bu2D0H_;
  std::unique_ptr<RooAbsPdf> bu2D0Hst_;
  std::unique_ptr<RooAbsPdf> bd2DstH_;
  std::unique_ptr<RooAbsPdf> missId_;
  std::unique_ptr<RooAbsPdf> bu2D0HMissId_;
  
  double bachelorSF_;
};

template <> NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars();
template <> NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars();
template <> NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars();
template <> NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars();


