#include "RooAbsBinning.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooBifurGauss.h"
#include "RooCBShape.h"
#include "RooCategory.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include <iostream>
#include <memory>

#include "Configuration.h"

class Pdf {
public:
  Pdf(Bachelor bachelor, RooRealVar &fitVariable,
      RooArgList const &commonFunctions)
      : bachelorString_(EnumToString(bachelor)),
        buMassMean_(("m[Bu]_Mean_bachelor=" + bachelorString_).c_str(),
                    "m[Bu] signal mean", 5279, 5275, 5285),
        buMassSigma_(("m[Bu]_Sigma_bachelor=" + bachelorString_).c_str(),
                     "m[Bu] signal sigma", 18, 15, 23),
        lambdaCombinatorial_(
            ("lambda_Combinatorial_bachelor=" + bachelorString_).c_str(),
            "Combinatorial lambda", 0, -0.1, 0.1),
        signalGaussian_(("Signal_Gaussian_bachelor=" + bachelorString_).c_str(),
                        "Signal gaussian pdf", fitVariable, buMassMean_,
                        buMassSigma_),
        combinatorialExponential_(
            ("Combinatorial_Exponential_bachelor=" + bachelorString_).c_str(),
            "Combinatorial exponential pdf", fitVariable, lambdaCombinatorial_),
        functions_(commonFunctions),
        signalYield_(("signal_yield_bachelor=" + bachelorString_).c_str(),
                     "m[Bu] signal yield", 0, 0, 0, ""),
        combinatorialYield_(
            ("combinatorial_yield_bachelor=" + bachelorString_).c_str(),
            "m[Bu] combinatorial yield", 0, 0, 0, ""),
        bu2Dst0HstYield_(
            ("bu2Dst0Hst_yield_bachelor=" + bachelorString_).c_str(),
            "m[Bu] bu2Dst0Hst yield", 0, 0, 0, ""),
        crossFeedYield_(("crossFeed_yield_bachelor=" + bachelorString_).c_str(),
                        "m[Bu] crossFeed yield", 0, 0, 0, ""),
        bu2D0HYield_(("bu2D0H_yield_bachelor=" + bachelorString_).c_str(),
                     "m[Bu] bu2D0H yield", 0, 0, 0, ""),
        bu2D0HstYield_(("bu2D0Hst_yield_bachelor=" + bachelorString_).c_str(),
                       "m[Bu] bu2D0Hst yield", 0, 0, 0, ""),
        bd2DstHYield_(("bd2DstH_yield_bachelor=" + bachelorString_).c_str(),
                      "m[Bu] bd2DstH yield", 0, 0, 0, ""),
        yields_(), addPdf_(nullptr) {

    if (bachelor == Bachelor::pi) {
      scaleFactor = 1;
    } else if (bachelor == Bachelor::k) {
      // Scale factor given by ratio of BR's
      scaleFactor = 0.000420 / 0.00518;
    }

    signalYield_.setMax(20000 * scaleFactor);
    signalYield_.setVal(10000 * scaleFactor);
    combinatorialYield_.setMax(20000 * scaleFactor);
    combinatorialYield_.setVal(1000 * scaleFactor);
    bu2Dst0HstYield_.setMax(20000 * scaleFactor);
    bu2Dst0HstYield_.setVal(5000 * scaleFactor);
    crossFeedYield_.setMax(20000 * scaleFactor);
    crossFeedYield_.setVal(1000 * scaleFactor);
    bu2D0HYield_.setMax(20000 * scaleFactor);
    bu2D0HYield_.setVal(3000 * scaleFactor);
    bu2D0HstYield_.setMax(20000 * scaleFactor);
    bu2D0HstYield_.setVal(2500 * scaleFactor);
    bd2DstHYield_.setMax(20000 * scaleFactor);
    bd2DstHYield_.setVal(1000 * scaleFactor);

    functions_.add(signalGaussian_);
    functions_.add(combinatorialExponential_);
    yields_.add(signalYield_);
    yields_.add(combinatorialYield_);
    yields_.add(bu2Dst0HstYield_);
    yields_.add(crossFeedYield_);
    yields_.add(bu2D0HYield_);
    yields_.add(bu2D0HstYield_);
    yields_.add(bd2DstHYield_);
    addPdf_ = std::unique_ptr<RooAddPdf>(
        new RooAddPdf(("pdf_" + bachelorString_).c_str(),
                      ("pdf_" + bachelorString_).c_str(), functions_, yields_));
  }

  RooAddPdf &addPdf() { return *addPdf_; }

  RooAddPdf const &addPdf() const { return *addPdf_; }

private:
  std::string bachelorString_;
  RooRealVar buMassMean_;
  RooRealVar buMassSigma_;
  RooRealVar lambdaCombinatorial_;
  RooGaussian signalGaussian_;
  RooExponential combinatorialExponential_;
  RooArgList functions_;
  RooRealVar signalYield_;
  RooRealVar combinatorialYield_;
  RooRealVar bu2Dst0HstYield_;
  RooRealVar crossFeedYield_;
  RooRealVar bu2D0HYield_;
  RooRealVar bu2D0HstYield_;
  RooRealVar bd2DstHYield_;
  RooArgList yields_;
  double scaleFactor;
  std::unique_ptr<RooAddPdf> addPdf_;
};

void Plotting(RooRealVar varToFit, Bachelor bachelor,
              RooDataSet fullDataSet, RooSimultaneous simultaneousPdf) {

  Categories categories;

  std::string bachelorString(EnumToString(bachelor));
  std::string title = "Bu2Dst0" + bachelorString + "_Dst02D0pi0_D02kpi";

  // --------------- create frame ---------------------
  
  RooPlot* frame = varToFit.frame(RooFit::Title(title.c_str()));

  // --------------- plot data and pdfs onto frame ---------------------
  
  fullDataSet.plotOn(frame, RooFit::Cut(("bachelor==bachelor::"+bachelorString).c_str()));
  simultaneousPdf.plotOn(frame, RooFit::Slice(categories.bachelor/* , bachelorString.c_str() */),
                        RooFit::ProjWData(categories.bachelor, fullDataSet),
                        RooFit::LineColor(kBlue));

  // --------------- plot onto canvas ---------------------
  
  TCanvas canvas(("canvas_"+bachelorString).c_str(), (title+"_canvas").c_str(), 1000, 1000);
  frame->Draw();
  canvas.SaveAs((title+".pdf").c_str());
  delete frame;
}

void Fitting(RooDataSet piDataSet, RooDataSet kDataSet, RooRealVar varToFit) {

  // Shape parameters that are constant across each decay mode
  // Bu2Dst0Hst
  RooRealVar meanBu2Dst0Hst("meanBu2Dst0Hst", "Bu2Dst0Hst mean",
                            5057); //, 5050, 5056);
  RooRealVar sigmaBu2Dst0Hst("sigmaBu2Dst0Hst", "Bu2Dst0Hst sigma",
                             65); //, 63, 67);

  // ButoD0pi
  RooRealVar meanBu2D0H("meanBu2D0H", "Bu2D0H mean", 5508);  //, 5502, 5506);
  RooRealVar sigmaBu2D0H("sigmaBu2D0H", "Bu2D0H sigma", 43); //, 41, 45);

  // Bu2D0Hst
  RooRealVar meanBu2D0Hst("meanBu2D0Hst", "Bu2D0Hst mean",
                          5277); //, 5268, 5278);
  RooRealVar sigmaBu2D0Hst("sigmaBu2D0Hst", "Bu2D0Hst sigma", 66); //, 62, 70);

  // Bu2Dst0pi0_D0gamma
  RooRealVar meanCrossFeed("meanCrossFeed", "Neutral cross feed mean",
                           5294); //, 5286, 5294);
  RooRealVar sigmaCrossFeed("sigmaCrossFeed", "Neutral cross feed sigma",
                            90); //, 87, 93);

  // BdtoDstpi
  RooRealVar meanBd2DstH("meanBd2DstH", "Bd2DstH mean", 5277);  //, 5279, 5267);
  RooRealVar sigmaBd2DstH("sigmaBd2DstH", "Bd2DstH sigma", 66); //, 62, 70);

  // Background pdfs common to both modes
  RooGaussian bu2Dst0HstGaussian("bu2Dst0HstGaussian", "Bu2Dst0Hst gaussian",
                                 varToFit, meanBu2Dst0Hst, sigmaBu2Dst0Hst);
  RooGaussian crossFeedGaussian("crossFeedGaussian",
                                "Neutral cross feed gaussian", varToFit,
                                meanCrossFeed, sigmaCrossFeed);
  RooGaussian bu2D0HGaussian("bu2D0HGaussian", "Bu2D0H gaussian", varToFit,
                             meanBu2D0H, sigmaBu2D0H);
  RooGaussian bu2D0HstGaussian("bu2D0HstGaussian", "Bu2D0Hst gaussian",
                               varToFit, meanBu2D0Hst, sigmaBu2D0Hst);
  RooGaussian bd2DstHGaussian("bd2DstHGaussian", "Bd2DstH gaussian", varToFit,
                              meanBd2DstH, sigmaBd2DstH);

  RooArgList commonFunctions;
  commonFunctions.add(bu2Dst0HstGaussian);
  commonFunctions.add(crossFeedGaussian);
  commonFunctions.add(bu2D0HGaussian);
  commonFunctions.add(bu2D0HstGaussian);
  commonFunctions.add(bd2DstHGaussian);

  // --------------- pi mode ---------------------

  Pdf piPdf(Bachelor::pi, varToFit, commonFunctions);

  // --------------- k mode ---------------------

  Pdf kPdf(Bachelor::k, varToFit, commonFunctions);


  Categories categories;

  // --------------- combine data sets ---------------------

  RooDataSet combinedDataSet(
      "combinedDataSet", "combinedDataSet", varToFit, RooFit::Index(categories.bachelor),
      RooFit::Import("pi", piDataSet), RooFit::Import("k", kDataSet));

  // --------------- simultaneous pdf ---------------------

  RooSimultaneous simPdf("simPdf", "simPdf", categories.bachelor);
  simPdf.addPdf(piPdf.addPdf(), "pi");
  simPdf.addPdf(kPdf.addPdf(), "k");

  // --------------- fit  ---------------------

  simPdf.fitTo(combinedDataSet);

  // --------------- pi ---------------------

  Plotting(varToFit, Bachelor::pi, combinedDataSet, simPdf);

  // --------------- k ---------------------

  Plotting(varToFit, Bachelor::k, combinedDataSet, simPdf);

  // --------------- create frame ---------------------

  // RooPlot *frame_pi = varToFit.frame(RooFit::Title("Dst0pi_D0pi0_kpi"));
  // RooPlot *frame_k = varToFit.frame(RooFit::Title("Dst0k_D0pi0_kpi"));

  // combinedDataSet.plotOn(frame_pi, RooFit::Cut("bachelor==bachelor::pi"));

  // --------------- plot data and pdfs onto frame ---------------------

  // simPdf.plotOn(frame_pi, RooFit::Slice(bachelor, "pi"),
  //               RooFit::ProjWData(bachelor, combinedDataSet),
  //               RooFit::LineColor(kBlue));

  // --------------- k ---------------------

  // --------------- create frame ---------------------

  // combinedDataSet.plotOn(frame_k, RooFit::Cut("bachelor==bachelor::k"));

  // --------------- plot data and pdfs onto frame ---------------------
  // simPdf.plotOn(frame_k, RooFit::Slice(bachelor, "k"),
  //               RooFit::ProjWData(bachelor, combinedDataSet),
  //               RooFit::LineColor(kBlue));

  // --------------- plot onto canvas ---------------------

  // TCanvas canvas("simPdf", "simPdf", 1000, 1000);
  //
  // canvas.Divide(1, 2);
  // canvas.cd(1);
  // frame_pi->Draw();
  // canvas.cd(2);
  // frame_k->Draw();
  //
  // canvas.SaveAs("Result.pdf");
}
int main(int argc, char **argv) {

  // We will actually just have 1 data set as input, then cut it down by
  // selecting certain categories in the fit. This is just as a toy example.
  TString inputfile1("/data/lhcb/users/rollings/ButoDst0X_DATA_NEW/"
                     "2012_MagDown/RenamedTriggers/temp/"
                     "2012_MagDown_ButDst0pi_Dst0tD0pi0_D0tkpi.root");
  TString inputfile2("/data/lhcb/users/rollings/ButoDst0X_DATA_NEW/"
                     "2012_MagDown/RenamedTriggers/temp/"
                     "2012_MagDown_ButDst0K_Dst0tD0pi0_D0tkpi.root");

  TString ttree("BtoDstar0h3_h1h2pi0RTuple");
  TChain myChain1(ttree);
  TChain myChain2(ttree);

  myChain1.Add(inputfile1);
  myChain2.Add(inputfile2);

  RooRealVar buMass("Pi0_Bu_M_DTF_D0Pi0", "m[Bu]", 4929, 5631, "Mev/c^2");
  buMass.setBins(140);
  RooArgSet myAS(buMass);
  RooDataSet piDS("piDataSet", "piDataSet", &myChain1, myAS);
  RooDataSet kDS("kDataSet", "kDataSet", &myChain2, myAS);

  Fitting(piDS, kDS, buMass);

  return 0;
}
