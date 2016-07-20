#pragma once
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "NeutralVars.h" 
#include "Configuration.h" 


// Bachelor

template <Neutral neutral, Bachelor bachelor> class BachelorVars {

public:
  static BachelorVars<neutral, bachelor> &Get() {
    static BachelorVars<neutral, bachelor> singleton;
    return singleton;
  }

  RooRealVar &sigmaBu2Dst0H_D0pi0() { return sigmaBu2Dst0H_D0pi0_; }
  RooRealVar &sigmaBu2Dst0H_D0gamma_1() { return sigmaBu2Dst0H_D0gamma_1_; }
  RooRealVar &sigmaBu2Dst0H_D0gamma_2() { return sigmaBu2Dst0H_D0gamma_2_; }
  RooRealVar &sigmaNonTmSignal_1() { return sigmaNonTmSignal_1_; }
  RooRealVar &sigmaNonTmSignal_2() { return sigmaNonTmSignal_2_; }
  RooRealVar &sigmaBu2D0H_1() { return sigmaBu2D0H_1_; }
  RooRealVar &sigmaBu2D0H_2() { return sigmaBu2D0H_2_; }
  RooRealVar &sigmaBu2D0Hst() { return sigmaBu2D0Hst_; }
  RooRealVar &sigmaBd2DstH() { return sigmaBd2DstH_; }
  RooRealVar &meanBu2Dst0Hst_D0pi0() { return meanBu2Dst0Hst_D0pi0_; }
  RooRealVar &sigmaBu2Dst0Hst_D0pi0() { return sigmaBu2Dst0Hst_D0pi0_; }
  RooRealVar &aBu2Dst0Hst_D0pi0() { return aBu2Dst0Hst_D0pi0_; }
  RooRealVar &nBu2Dst0Hst_D0pi0() { return nBu2Dst0Hst_D0pi0_; }
  RooRealVar &meanBu2Dst0Hst_D0gamma() { return meanBu2Dst0Hst_D0gamma_; }
  RooRealVar &sigmaBu2Dst0Hst_D0gamma() { return sigmaBu2Dst0Hst_D0gamma_; }
  RooRealVar &aBu2Dst0Hst_D0gamma() {
    return aBu2Dst0Hst_D0gamma_;
  } // Not gamma, K
  RooRealVar &nBu2Dst0Hst_D0gamma() {
    return nBu2Dst0Hst_D0gamma_;
  } // Not gamma, K
  RooRealVar &meanMissId1() { return meanMissId1_; }
  RooRealVar &sigmaMissId1() { return sigmaMissId1_; }
  RooRealVar &aMissId1() { return aMissId1_; }
  RooRealVar &nMissId1() { return nMissId1_; }
  RooRealVar &fracMissId1() { return fracMissId1_; }
  RooRealVar &meanMissId2() { return meanMissId2_; } // K
  RooRealVar &sigmaMissId2() { return sigmaMissId2_; }
  RooRealVar &aMissId2() { return aMissId2_; }
  RooRealVar &nMissId2() { return nMissId2_; }
  std::unique_ptr<RooAbsPdf> &bu2Dst0H_D0pi0() { return bu2Dst0H_D0pi0_; }
  std::unique_ptr<RooAbsPdf> &bu2Dst0H_D0gamma() { return bu2Dst0H_D0gamma_; }
  std::unique_ptr<RooAbsPdf> &nonTmSignal_1() { return nonTmSignal_1_; }
  std::unique_ptr<RooAbsPdf> &nonTmSignal_2() { return nonTmSignal_2_; }
  std::unique_ptr<RooAbsPdf> &nonTmSignal() { return nonTmSignal_; }
  std::unique_ptr<RooAbsPdf> &bu2Dst0Hst_D0pi0() { return bu2Dst0Hst_D0pi0_; }
  std::unique_ptr<RooAbsPdf> &bu2Dst0Hst_D0gamma() {
    return bu2Dst0Hst_D0gamma_;
  }
  std::unique_ptr<RooAbsPdf> &bu2D0H() { return bu2D0H_; }
  std::unique_ptr<RooAbsPdf> &bu2D0Hst() { return bu2D0Hst_; }
  std::unique_ptr<RooAbsPdf> &bd2DstH() { return bd2DstH_; }
  std::unique_ptr<RooAbsPdf> &missId1() { return missId1_; }
  std::unique_ptr<RooAbsPdf> &missId2() { return missId2_; }
  std::unique_ptr<RooAbsPdf> &missId() { return missId_; }

private:
  BachelorVars();
  ~BachelorVars() {}

  RooRealVar sigmaBu2Dst0H_D0pi0_;
  RooRealVar sigmaBu2Dst0H_D0gamma_1_;
  RooRealVar sigmaBu2Dst0H_D0gamma_2_; // gamma
  RooRealVar sigmaNonTmSignal_1_;
  RooRealVar sigmaNonTmSignal_2_; // gamma
  RooRealVar sigmaBu2D0H_1_;
  RooRealVar sigmaBu2D0H_2_;
  RooRealVar sigmaBu2D0Hst_;
  RooRealVar sigmaBd2DstH_;
  RooRealVar meanBu2Dst0Hst_D0pi0_;
  RooRealVar sigmaBu2Dst0Hst_D0pi0_;
  RooRealVar aBu2Dst0Hst_D0pi0_; // Not gamma, K
  RooRealVar nBu2Dst0Hst_D0pi0_; // Not gamma, K
  RooRealVar meanBu2Dst0Hst_D0gamma_;
  RooRealVar sigmaBu2Dst0Hst_D0gamma_;
  RooRealVar aBu2Dst0Hst_D0gamma_;
  RooRealVar nBu2Dst0Hst_D0gamma_;
  RooRealVar meanMissId1_;
  RooRealVar sigmaMissId1_;
  RooRealVar aMissId1_;
  RooRealVar nMissId1_;
  RooRealVar fracMissId1_;
  RooRealVar meanMissId2_; // K
  RooRealVar sigmaMissId2_;
  RooRealVar aMissId2_;
  RooRealVar nMissId2_;

  // By declaring the pointer to be a RooAbsPdf, we can then specialise the type
  // later (base class)
  std::unique_ptr<RooAbsPdf> bu2Dst0H_D0pi0_;
  std::unique_ptr<RooAbsPdf> bu2Dst0H_D0gamma_;
  std::unique_ptr<RooAbsPdf> nonTmSignal_1_; // gamma
  std::unique_ptr<RooAbsPdf> nonTmSignal_2_; // gamma
  std::unique_ptr<RooAbsPdf> nonTmSignal_;
  std::unique_ptr<RooAbsPdf> bu2Dst0Hst_D0pi0_;
  std::unique_ptr<RooAbsPdf> bu2Dst0Hst_D0gamma_;
  std::unique_ptr<RooAbsPdf> bu2D0H_;
  std::unique_ptr<RooAbsPdf> bu2D0Hst_;
  std::unique_ptr<RooAbsPdf> bd2DstH_;
  std::unique_ptr<RooAbsPdf> missId1_;
  std::unique_ptr<RooAbsPdf> missId2_;
  std::unique_ptr<RooAbsPdf> missId_;
};

template <> BachelorVars<Neutral::gamma, Bachelor::pi>::BachelorVars();
template <> BachelorVars<Neutral::gamma, Bachelor::k>::BachelorVars();
template <> BachelorVars<Neutral::pi0, Bachelor::pi>::BachelorVars();
template <> BachelorVars<Neutral::pi0, Bachelor::k>::BachelorVars();


