 #include "GlobalVars.h"

GlobalVars::GlobalVars(int uniqueId)
    : uniqueId_(uniqueId),
      // pidEffPi_(Params::Get().CreateFixed(
      //     "pidEffPi", 0.996, 3e-03, Systematic::pidEffPi, Sign::positive)),
      pidEffPi_(
          Params::Get().CreateFloating("pidEffPi", uniqueId_, 0.996, 0.5, 1.5)),
      // Run 1 = 5.34 +/- 0.27 e-05, Run2 = 10.16 +/- 0.37 e-05
      crossFeedRate_(nullptr),
      A_FAV_(Params::Get().CreateFixed("A_FAV", uniqueId_, 0, 0.05,
                                       Systematic::A_FAV, Sign::none)),
      A_Kpi_(Params::Get().CreateFixed("A_Kpi", uniqueId_, -1.13e-02, 1.5e-03,
                                       Systematic::A_Kpi, Sign::none)),
      A_pi_(Params::Get().CreateFixed("A_pi", uniqueId_, -6.45e-04, 1.84e-04,
                                      Systematic::A_pi, Sign::none)),
      Delta_A_CP_(Params::Get().CreateFixed("Delta_A_CP", uniqueId_, -1.54e-03,
                                            2.9e-04, Systematic::Delta_A_CP,
                                            Sign::none)) {
  std::vector<Year> yVec = {Year::y2011, Year::y2012, Year::y2015,
                            Year::y2016, Year::y2017, Year::y2018};
  double wRun1 = 0;
  double wRun2 = 0;
  double lumi = 0;
  for (auto &y : yVec) {
    if (y == Year::y2011) {
      wRun1 += 0.98;
      lumi += 0.98;
    } else if (y == Year::y2012) {
      wRun1 += 1.99;
      lumi += 1.99;
    } else if (y == Year::y2015) {
      wRun2 += 0.28;
      lumi += 0.28;
    } else if (y == Year::y2016) {
      wRun2 += 1.65;
      lumi += 1.65;
    } else if (y == Year::y2017) {
      wRun2 += 1.7;
      lumi += 1.7;
    } else if (y == Year::y2018) {
      wRun2 += 2.19;
      lumi += 2.19;
    }
  }
  double cfRun1 = 5.34e-05;
  double cfRun1Err = 0.27e-05;
  double cfRun2 = 10.16e-05;
  double cfRun2Err = 0.37e-05;
  // Weighted mean: sum (w * x) / sum(w)
  double cfAv = (cfRun1 * wRun1 + cfRun2 * wRun2) / lumi;
  // Weighted av: sqrt ( 1 / sum(err^-2) )
  double cfErr = std::sqrt(1 / (pow(cfRun1Err, -2) + pow(cfRun2Err, -2)));
  crossFeedRate_ = std::shared_ptr<RooRealVar>(
      Params::Get().CreateFixed("crossFeedRate", uniqueId_, cfAv, cfErr,
                                Systematic::crossFeedRate, Sign::positive));
}
