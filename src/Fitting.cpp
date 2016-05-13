#include "RooAbsBinning.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
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
#include "TH1F.h"
#include "TTree.h"

#include <iostream>
#include <map>
#include <vector>

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

  const double buPdgMass = 5279;
  const double buMassMeanMin = 5275;
  const double buMassMeanMax = 5275;
  const double buMassSigmaExp = 18;
  const double buMassSigmaMin = 15;
  const double buMassSigmaMax = 23;

  // Strings will hold the labels for the decay options
  // Signal gaussian parameters
  std::map<std::string, RooRealVar *> buMassMean;
  std::map<std::string, RooRealVar *> buMassSigma;
  // Combinatorial background shape
  std::map<std::string, RooRealVar *> lambdaCombinatorial;
  // pdfs unique for each decay mode
  std::map<std::string, RooGaussian *> signalGaussian;
  std::map<std::string, RooExponential *> combinatorialExponential;
  // RooArgList to store all pdfs and yields for each mode
  std::map<std::string, RooArgList *> functions;
  std::map<std::string, RooArgList *> yields;
  // Yields
  std::map<std::string, RooRealVar *> signalYield;
  std::map<std::string, RooRealVar *> combinatorialYield;
  std::map<std::string, RooRealVar *> bu2Dst0HstYield;
  std::map<std::string, RooRealVar *> crossFeedYield;
  std::map<std::string, RooRealVar *> bu2D0HYield;
  std::map<std::string, RooRealVar *> bu2D0HstYield;
  std::map<std::string, RooRealVar *> bd2DstHYield;
  // Final pdfs stored
  std::map<std::string, RooAddPdf *> pdfs;
  // Set yield parameters for control: vary for each mode. Define for all years,
  // all polarities, all charges, pi favoured mode and scale accordingly
  const double yieldMin = 0;
  double yieldMaxControl = 20000;
  double signalYieldExpControl = 10000;
  double combinatorialYieldExpControl = 1000;
  double bu2Dst0HstYieldExpControl = 5000;
  double crossFeedYieldExpControl = 1000;
  double bu2D0HYieldExpControl = 3000;
  double bu2D0HstYieldExpControl = 2500;
  double bd2DstHYieldExpControl = 1000;

  // Scale factors (for yield inputs)
  const double kBachelorScaleFactor = 0.000420 / 0.00518;

  // Change this to enums and use EnumToString when integrating with Main.cpp
  std::vector<std::string> bachelorVec;
  bachelorVec.push_back("pi");
  bachelorVec.push_back("k");

  RooCategory bachelor("bachelor", "bachelor");
  bachelor.defineType("pi");
  bachelor.defineType("k");

  RooSimultaneous simPdf("simPdf", "Simultaneous PDF", bachelor);

  // Add to simultaneous PDF
  for (unsigned int bCounter = 0; bCounter < bachelorVec.size(); bCounter++) {

    // Set Shape parameters that vary between decays
    std::string buMassMeanName, buMassSigmaName, lambdaCombinatorialName;
    buMassMeanName = "m[Bu]_Mean_bachelor=" + bachelorVec[bCounter];
    buMassSigmaName = "m[Bu]_Sigma_bachelor=" + bachelorVec[bCounter];
    lambdaCombinatorialName =
        "lambda_Compinatorial_bachelor=" + bachelorVec[bCounter];

    buMassMean[bachelorVec[bCounter]] =
        new RooRealVar(buMassMeanName.c_str(), "m[Bu] signal mean", buPdgMass,
                       buMassMeanMin, buMassMeanMax);
    buMassSigma[bachelorVec[bCounter]] =
        new RooRealVar(buMassSigmaName.c_str(), "m[Bu] signal sigma",
                       buMassSigmaExp, buMassSigmaMin, buMassSigmaMax);
    lambdaCombinatorial[bachelorVec[bCounter]] = new RooRealVar(
        lambdaCombinatorialName.c_str(), "Combinatorial lambda", 0, -0.1, 0.1);

    // Declare pdfs that vary between decays
    std::string signalGaussianName, combinatorialExponentialName;
    signalGaussianName = "Signal_Gaussian_bachelor=" + bachelorVec[bCounter];
    combinatorialExponentialName =
        "Combinatorial_Exponential_bachelor=" + bachelorVec[bCounter];

    signalGaussian[bachelorVec[bCounter]] =
        new RooGaussian(signalGaussianName.c_str(), "Signal gaussian pdf",
                        varToFit, *buMassMean[bachelorVec[bCounter]],
                        *buMassSigma[bachelorVec[bCounter]]);
    combinatorialExponential[bachelorVec[bCounter]] = new RooExponential(
        combinatorialExponentialName.c_str(), "Combinatorial exponential pdf",
        varToFit, *lambdaCombinatorial[bachelorVec[bCounter]]);

    functions[bachelorVec[bCounter]] = new RooArgList();
    // Add all functions to RooArgList
    functions[bachelorVec[bCounter]]->add(
        *signalGaussian[bachelorVec[bCounter]]);
    functions[bachelorVec[bCounter]]->add(
        *combinatorialExponential[bachelorVec[bCounter]]);
    functions[bachelorVec[bCounter]]->add(bu2Dst0HstGaussian);
    functions[bachelorVec[bCounter]]->add(crossFeedGaussian);
    functions[bachelorVec[bCounter]]->add(bu2D0HGaussian);
    functions[bachelorVec[bCounter]]->add(bu2D0HstGaussian);
    functions[bachelorVec[bCounter]]->add(bd2DstHGaussian);

    // Yields are unique to each mode
    std::string signalYieldName, combinatorialYieldName, bu2Dst0HstYieldName,
        crossFeedYieldName, bu2D0HYieldName, bu2D0HstYieldName,
        bd2DstHYieldName;
    signalYieldName = "signal_yield_bachelor=" + bachelorVec[bCounter];
    combinatorialYieldName =
        "combinatorial_yield_bachelor=" + bachelorVec[bCounter];
    bu2Dst0HstYieldName = "bu2Dst0Hst_yield_bachelor=" + bachelorVec[bCounter];
    crossFeedYieldName = "crossFeed_yield_bachelor=" + bachelorVec[bCounter];
    bu2D0HYieldName = "bu2D0H_yield_bachelor=" + bachelorVec[bCounter];
    bu2D0HstYieldName = "bu2D0Hst_yield_bachelor=" + bachelorVec[bCounter];
    bd2DstHYieldName = "bd2DstH_yield_bachelor=" + bachelorVec[bCounter];

    // Scale yield inputs if needed
    if (bachelorVec[bCounter] == "k") {
      yieldMaxControl *= kBachelorScaleFactor;
      signalYieldExpControl *= kBachelorScaleFactor;
      combinatorialYieldExpControl *= kBachelorScaleFactor;
      bu2Dst0HstYieldExpControl *= kBachelorScaleFactor;
      crossFeedYieldExpControl *= kBachelorScaleFactor;
      bu2D0HYieldExpControl *= kBachelorScaleFactor;
      bu2D0HstYieldExpControl *= kBachelorScaleFactor;
      bd2DstHYieldExpControl *= kBachelorScaleFactor;
    }

    signalYield[bachelorVec[bCounter]] =
        new RooRealVar(signalYieldName.c_str(), "m[Bu] signal yield",
                       signalYieldExpControl, yieldMin, yieldMaxControl);
    combinatorialYield[bachelorVec[bCounter]] =
        new RooRealVar(combinatorialYieldName.c_str(), "m[Bu] signal yield",
                       combinatorialYieldExpControl, yieldMin, yieldMaxControl);
    bu2Dst0HstYield[bachelorVec[bCounter]] =
        new RooRealVar(bu2Dst0HstYieldName.c_str(), "m[Bu] signal yield",
                       bu2Dst0HstYieldExpControl, yieldMin, yieldMaxControl);
    crossFeedYield[bachelorVec[bCounter]] =
        new RooRealVar(crossFeedYieldName.c_str(), "m[Bu] signal yield",
                       crossFeedYieldExpControl, yieldMin, yieldMaxControl);
    bu2D0HYield[bachelorVec[bCounter]] =
        new RooRealVar(bu2D0HYieldName.c_str(), "m[Bu] signal yield",
                       bu2D0HYieldExpControl, yieldMin, yieldMaxControl);
    bu2D0HstYield[bachelorVec[bCounter]] =
        new RooRealVar(bu2D0HstYieldName.c_str(), "m[Bu] signal yield",
                       bu2D0HstYieldExpControl, yieldMin, yieldMaxControl);
    bd2DstHYield[bachelorVec[bCounter]] =
        new RooRealVar(bd2DstHYieldName.c_str(), "m[Bu] signal yield",
                       bd2DstHYieldExpControl, yieldMin, yieldMaxControl);

    yields[bachelorVec[bCounter]] = new RooArgList();

    yields[bachelorVec[bCounter]]->add(*signalYield[bachelorVec[bCounter]]);
    yields[bachelorVec[bCounter]]->add(
        *combinatorialYield[bachelorVec[bCounter]]);
    yields[bachelorVec[bCounter]]->add(*bu2Dst0HstYield[bachelorVec[bCounter]]);
    yields[bachelorVec[bCounter]]->add(*crossFeedYield[bachelorVec[bCounter]]);
    yields[bachelorVec[bCounter]]->add(*bu2D0HYield[bachelorVec[bCounter]]);
    yields[bachelorVec[bCounter]]->add(*bu2D0HstYield[bachelorVec[bCounter]]);
    yields[bachelorVec[bCounter]]->add(*bd2DstHYield[bachelorVec[bCounter]]);

    std::string pdfsName;
    pdfsName = "PDF_" + bachelorVec[bCounter];

    pdfs[bachelorVec[bCounter]] = new RooAddPdf(
        pdfsName.c_str(), "PDF", *functions[bachelorVec[bCounter]],
        *yields[bachelorVec[bCounter]]);

    simPdf.addPdf(*pdfs[bachelorVec[bCounter]], bachelorVec[bCounter].c_str());
  }

  // Won't need to combine data here: outs is already combined
  RooDataSet combinedDataSet(
      "combinedDataSet", "combinedDataSet", varToFit, RooFit::Index(bachelor),
      RooFit::Import("pi", piDataSet), RooFit::Import("k", kDataSet));

  std::map<std::string, RooPlot *> frames;
  std::map<std::string, TCanvas *> canvas;
  // Plot data to frames
  for (unsigned int bCounter = 0; bCounter < bachelorVec.size(); bCounter++) {
    // RooFitResult* myFR = sum.fitTo(inputDataSet, Save());

    // Canvases to plots on
    std::string canvasName;
    canvasName = "RooPlot_" + bachelorVec[bCounter];
    canvas[bachelorVec[bCounter]] =
        new TCanvas(canvasName.c_str(), "m[Bu] DTF Constrained", 1000, 1000);

    frames[bachelorVec[bCounter]] = new RooPlot();
    
    std::string frameTitle;
    frameTitle = "Bu2Dst0" + bachelorVec[bCounter];
    frames[bachelorVec[bCounter]] =
        varToFit.frame(RooFit::Title(frameTitle.c_str()));

    // std::string cutString;
    // cutString = "bachelor==bachelor::" + bachelorVec[bCounter];
    // combinedDataSet.plotOn(frames[bachelorVec[bCounter]],
    //                        RooFit::Cut(cutString.c_str()));

    if(bachelorVec[bCounter] == "pi"){
      combinedDataSet.plotOn(frames[bachelorVec[bCounter]],
                             RooFit::Cut("bachelor==bachelor::pi"));
                             } else if(bachelorVec[bCounter] == "k"){
      combinedDataSet.plotOn(frames[bachelorVec[bCounter]],
                             RooFit::Cut("bachelor==bachelor::k"));
                             }

    std::cout << "Bachelor = " << bachelorVec[bCounter] <<  "\n";
    
    simPdf.plotOn(frames[bachelorVec[bCounter]],
                  RooFit::Slice(bachelor, bachelorVec[bCounter].c_str()),
                  RooFit::ProjWData(bachelor, combinedDataSet),
                  RooFit::LineColor(kBlue));
    simPdf.plotOn(frames[bachelorVec[bCounter]],
                  RooFit::Slice(bachelor, bachelorVec[bCounter].c_str()),
                  RooFit::ProjWData(bachelor, combinedDataSet),
                  RooFit::Components(*signalGaussian[bachelorVec[bCounter]]),
                  RooFit::LineStyle(kDashed));
    simPdf.plotOn(
        frames[bachelorVec[bCounter]],
        RooFit::Slice(bachelor, bachelorVec[bCounter].c_str()),
        RooFit::Components(*combinatorialExponential[bachelorVec[bCounter]]),
        RooFit::ProjWData(bachelor, combinedDataSet),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kViolet));
    simPdf.plotOn(frames[bachelorVec[bCounter]],
                  RooFit::Slice(bachelor, bachelorVec[bCounter].c_str()),
                  RooFit::ProjWData(bachelor, combinedDataSet),
                  RooFit::Components(bu2Dst0HstGaussian),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
    simPdf.plotOn(frames[bachelorVec[bCounter]],
                  RooFit::Slice(bachelor, bachelorVec[bCounter].c_str()),
                  RooFit::ProjWData(bachelor, combinedDataSet),
                  RooFit::Components(crossFeedGaussian),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen));
    simPdf.plotOn(frames[bachelorVec[bCounter]],
                  RooFit::Slice(bachelor, bachelorVec[bCounter].c_str()),
                  RooFit::ProjWData(bachelor, combinedDataSet),
                  RooFit::Components(bu2D0HGaussian),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kOrange));
    simPdf.plotOn(frames[bachelorVec[bCounter]],
                  RooFit::Slice(bachelor, bachelorVec[bCounter].c_str()),
                  RooFit::ProjWData(bachelor, combinedDataSet),
                  RooFit::Components(bu2D0HstGaussian),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kTeal));
    simPdf.plotOn(frames[bachelorVec[bCounter]],
                  RooFit::Slice(bachelor, bachelorVec[bCounter].c_str()),
                  RooFit::ProjWData(bachelor, combinedDataSet),
                  RooFit::Components(bd2DstHGaussian),
                  RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta));
    // sum.paramOn(myFrame, Layout(0.52,0.89,0.89));
    std::string canvasFileName;
    canvasFileName = "RooPlot_" + bachelorVec[bCounter] + ".pdf";

    canvas[bachelorVec[bCounter]]->cd();
    canvas[bachelorVec[bCounter]]->Draw();
    canvas[bachelorVec[bCounter]]->SaveAs(canvasFileName.c_str());
  }
}

int main(int argc, char **argv) {

  // We will actually just have 1 data set as input, then cut it down by
  // selecting certain categories in the fit. This is just as a toy example.
  TString inputfile1("/data/lhcb/users/rollings/ButoDst0X_DATA_NEW/2012_MagDown/RenamedTriggers/temp/2012_MagDown_ButDst0pi_Dst0tD0pi0_D0tkpi.root");
  TString inputfile2("/data/lhcb/users/rollings/ButoDst0X_DATA_NEW/2012_MagDown/RenamedTriggers/temp/2012_MagDown_ButDst0K_Dst0tD0pi0_D0tkpi.root");

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
