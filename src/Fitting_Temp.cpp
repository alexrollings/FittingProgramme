#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooBifurGauss.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooArgList.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooDataHist.h"
#include "RooAbsBinning.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"

#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>


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

  RooRealVar buMassMean_pi("m[Bu]_Mean_bachelor=pi", "m[Bu] signal mean", 5279, 5275, 5285);
  RooRealVar buMassSigma_pi("m[Bu]_Sigma_bachelor=pi", "m[Bu] signal sigma", 18, 15, 23);
  RooRealVar lambdaCombinatorial_pi("lambda_Compinatorial_bachelor=pi", "Combinatorial lambda", 0, -0.1, 0.1);

  //Non shared PDFs
  RooGaussian signalGaussian_pi("Signal_Gaussian_bachelor=pi", "Signal gaussian pdf", varToFit, buMassMean_pi, buMassSigma_pi);
  RooExponential combinatorialExponential_pi("Combinatorial_Exponential_bachelor=pi", "Combinatorial exponential pdf", varToFit, lambdaCombinatorial_pi);

  // Background pdfs common to both modes
  RooGaussian bu2Dst0HstGaussian_pi("bu2Dst0HstGaussian_pi", "Bu2Dst0Hst gaussian",
                                 varToFit, meanBu2Dst0Hst, sigmaBu2Dst0Hst);
  RooGaussian crossFeedGaussian_pi("crossFeedGaussian_pi",
                                "Neutral cross feed gaussian", varToFit,
                                meanCrossFeed, sigmaCrossFeed);
  RooGaussian bu2D0HGaussian_pi("bu2D0HGaussian_pi", "Bu2D0H gaussian", varToFit,
                             meanBu2D0H, sigmaBu2D0H);
  RooGaussian bu2D0HstGaussian_pi("bu2D0HstGaussian_pi", "Bu2D0Hst gaussian",
                               varToFit, meanBu2D0Hst, sigmaBu2D0Hst);
  RooGaussian bd2DstHGaussian_pi("bd2DstHGaussian_pi", "Bd2DstH gaussian", varToFit,
                              meanBd2DstH, sigmaBd2DstH);

  RooArgList functions_pi;
  functions_pi.add(signalGaussian_pi);
  functions_pi.add(combinatorialExponential_pi);
  functions_pi.add(bu2Dst0HstGaussian_pi);
  functions_pi.add(crossFeedGaussian_pi);
  functions_pi.add(bu2D0HGaussian_pi);
  functions_pi.add(bu2D0HstGaussian_pi);
  functions_pi.add(bd2DstHGaussian_pi);

  RooRealVar signalYield_pi("signal_yield_bachelor=pi", "m[Bu] signal yield", 10000, 0, 20000);
  RooRealVar combinatorialYield_pi("combinatorial_yield_bachelor=pi", "m[Bu] combinatorial yield",1000, 0, 20000); 
  RooRealVar bu2Dst0HstYield_pi("bu2Dst0Hst_yield_bachelor=pi", "m[Bu] bu2Dst0Hst yield", 5000, 0, 20000); 
  RooRealVar crossFeedYield_pi("crossFeed_yield_bachelor=pi", "m[Bu] crossFeed yield", 1000, 0, 20000); 
  RooRealVar bu2D0HYield_pi("bu2D0H_yield_bachelor=pi", "m[Bu] bu2D0H yield", 3000, 0, 20000); 
  RooRealVar bu2D0HstYield_pi("bu2D0Hst_yield_bachelor=pi", "m[Bu] bu2D0Hst yield", 2500, 0, 20000);
  RooRealVar bd2DstHYield_pi("bd2DstH_yield_bachelor=pi", "m[Bu] bd2DstH yield", 1000, 0, 20000); 
  
  RooArgList yields_pi;
  yields_pi.add(signalYield_pi);
  yields_pi.add(combinatorialYield_pi);
  yields_pi.add(bu2Dst0HstYield_pi);
  yields_pi.add(crossFeedYield_pi);
  yields_pi.add(bu2D0HYield_pi);
  yields_pi.add(bu2D0HstYield_pi);
  yields_pi.add(bd2DstHYield_pi);

  RooAddPdf pdf_pi("pdf_pi", "pdf_pi", functions_pi, yields_pi);
  
  RooRealVar buMassMean_k("m[Bu]_Mean_bachelor=k", "m[Bu] signal mean", 5279, 5275, 5285);
  RooRealVar buMassSigma_k("m[Bu]_Sigma_bachelor=k", "m[Bu] signal sigma", 18, 15, 23);
  RooRealVar lambdaCombinatorial_k("lambda_Compinatorial_bachelor=k", "Combinatorial lambda", 0, -0.1, 0.1);
  
  RooGaussian signalGaussian_k("Signal_Gaussian_bachelor=k", "Signal gaussian pdf", varToFit, buMassMean_k, buMassSigma_k);
  RooExponential combinatorialExponential_k("Combinatorial_Exponential_bachelor=k", "Combinatorial exponential pdf", varToFit, lambdaCombinatorial_k); 

  // Background pdfs common to both modes
  RooGaussian bu2Dst0HstGaussian_k("bu2Dst0HstGaussian_k", "Bu2Dst0Hst gaussian",
                                 varToFit, meanBu2Dst0Hst, sigmaBu2Dst0Hst);
  RooGaussian crossFeedGaussian_k("crossFeedGaussian_k",
                                "Neutral cross feed gaussian", varToFit,
                                meanCrossFeed, sigmaCrossFeed);
  RooGaussian bu2D0HGaussian_k("bu2D0HGaussian_k", "Bu2D0H gaussian", varToFit,
                             meanBu2D0H, sigmaBu2D0H);
  RooGaussian bu2D0HstGaussian_k("bu2D0HstGaussian_k", "Bu2D0Hst gaussian",
                               varToFit, meanBu2D0Hst, sigmaBu2D0Hst);
  RooGaussian bd2DstHGaussian_k("bd2DstHGaussian_k", "Bd2DstH gaussian", varToFit,
                              meanBd2DstH, sigmaBd2DstH);
  
  RooArgList functions_k;
  functions_k.add(signalGaussian_k);
  functions_k.add(combinatorialExponential_k);
  functions_k.add(bu2Dst0HstGaussian_k);
  functions_k.add(crossFeedGaussian_k);
  functions_k.add(bu2D0HGaussian_k);
  functions_k.add(bu2D0HstGaussian_k);
  functions_k.add(bd2DstHGaussian_k);


  RooRealVar signalYield_k("signal_yield_bachelor=k", "m[Bu] signal yield", 1000, 0, 2000); 
  RooRealVar combinatorialYield_k("combinatorial_yield_bachelor=k", "m[Bu] combinatorial yield", 100, 0, 2000);
  RooRealVar bu2Dst0HstYield_k("bu2Dst0Hst_yield_bachelor=k", "m[Bu] bu2Dst0Hst yield", 500, 0, 2000); 
  RooRealVar crossFeedYield_k("crossFeed_yield_bachelor=k", "m[Bu] crossFeed yield", 100, 0, 2000);
  RooRealVar bu2D0HYield_k("bu2D0H_yield_bachelor=k", "m[Bu] bu2D0H yield", 300, 0, 2000);
  RooRealVar bu2D0HstYield_k("bu2D0Hst_yield_bachelor=k", "m[Bu] bu2D0Hst yield", 250, 0, 2000);
  RooRealVar bd2DstHYield_k("bd2DstH_yield_bachelor=k", "m[Bu] bd2DstH yield", 100, 0, 2000); 

  RooArgList yields_k;
  yields_k.add(signalYield_k);
  yields_k.add(combinatorialYield_k);
  yields_k.add(bu2Dst0HstYield_k);
  yields_k.add(crossFeedYield_k);
  yields_k.add(bu2D0HYield_k);
  yields_k.add(bu2D0HstYield_k);
  yields_k.add(bd2DstHYield_k);

  RooAddPdf pdf_k("pdf_k", "pdf_k", functions_k, yields_k);

  //DEFINE CATEGORIES

  RooCategory bachelor("bachelor", "bachelor");
  bachelor.defineType("pi");
  bachelor.defineType("k");

  //CONSTRUCT COMBINED DATA SET

  RooDataSet combinedDataSet(
      "combinedDataSet", "combinedDataSet", varToFit, RooFit::Index(bachelor),
      RooFit::Import("pi", piDataSet), RooFit::Import("k", kDataSet));

  //CONSTRUCT SIM PDF

  RooSimultaneous simPdf("simPdf", "simPdf", bachelor);
  simPdf.addPdf(pdf_pi, "pi");
  simPdf.addPdf(pdf_k, "k");

  simPdf.fitTo(combinedDataSet);
 
  //FIT SIM PDF TO COMB DATA

  // RooFitResult* myFR = simPdf.fitTo(combinedDataSet, Save());

  //PLOT DECAY MODES ON SAME CANVAS
 
  RooPlot* frame_pi = varToFit.frame(RooFit::Title("Dst0pi_D0pi0_kpi"));
  
  combinedDataSet.plotOn(frame_pi,RooFit::Cut("bachelor==bachelor::pi"));

  //Plot on components
  simPdf.plotOn(frame_pi,
                RooFit::Slice(bachelor, "pi"),
                RooFit::ProjWData(bachelor, combinedDataSet),
                RooFit::LineColor(kBlue));
 
  RooPlot* frame_k = varToFit.frame(RooFit::Title("Dst0k_D0pi0_kpi"));
  
  combinedDataSet.plotOn(frame_k,RooFit::Cut("bachelor==bachelor::k"));

  //Plot on components
  simPdf.plotOn(frame_k,
                RooFit::Slice(bachelor, "k"),
                RooFit::ProjWData(bachelor, combinedDataSet),
                RooFit::LineColor(kBlue));

  TCanvas canvas("simPdf", "simPdf", 1000, 1000);

  canvas.Divide(1,2);
  canvas.cd(1);
  frame_pi->Draw();
  canvas.cd(2);
  frame_k->Draw();
  
  canvas.SaveAs("Result.pdf");


}
int main(int argc, char **argv) {

  // We will actually just have 1 data set as input, then cut it down by
  // selecting certain categories in the fit. This is just as a toy example.
  TString inputfile1("~/Desktop/FittingProgramme/src/2012_MagDown_ButDst0pi_Dst0tD0pi0_D0tkpi.root");
  TString inputfile2("~/Desktop/FittingProgramme/src/2012_MagDown_ButDst0K_Dst0tD0pi0_D0tkpi.root");

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
