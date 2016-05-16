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
#include "TTree.h"
#include <iostream>

void Fitting(RooDataSet piDataSet, RooDataSet kDataSet, RooRealVar varToFit) {

  // --------------- pi mode ---------------------
  
  RooRealVar meanBu2Dst0Hst("meanBu2Dst0Hst", "Bu2Dst0Hst mean",
                               5057); //, 5050, 5056);
  RooRealVar sigmaBu2Dst0Hst("sigmaBu2Dst0Hst", "Bu2Dst0Hst sigma",
                                65); //, 63, 67);

  RooRealVar buMassMean_pi("m[Bu]_Mean_bachelor=pi", "m[Bu] signal mean pi", 5279,
                           5275, 5285);
  RooRealVar buMassSigma_pi("m[Bu]_Sigma_bachelor=pi", "m[Bu] signal sigma pi", 18,
                            15, 23);



  RooGaussian signalGaussian("Signal_Gaussian_bachelor=pi",
                                "Signal gaussian pdf pi", varToFit, buMassMean_pi,
                                buMassSigma_pi);

  RooGaussian bu2Dst0HstGaussian("bu2Dst0HstGaussian",
                                    "Bu2Dst0Hst gaussian", varToFit,
                                    meanBu2Dst0Hst, sigmaBu2Dst0Hst);



  RooArgList functions_pi;
  functions_pi.add(signalGaussian_pi);
  functions_pi.add(bu2Dst0HstGaussian);



  RooRealVar signalYield_pi("signal_yield_bachelor=pi", "m[Bu] signal yield pi",
                            10000, 0, 20000);
  RooRealVar bu2Dst0HstYield_pi("bu2Dst0Hst_yield_bachelor=pi",
                                "m[Bu] bu2Dst0Hst yield pi", 5000, 0, 20000);



  RooArgList yields_pi;
  yields_pi.add(signalYield_pi);
  yields_pi.add(bu2Dst0HstYield_pi);



  RooAddPdf pdf_pi("pdf_pi", "pdf_pi", functions_pi, yields_pi);


  // --------------- k mode ---------------------
  
  

  RooRealVar buMassMean_k("m[Bu]_Mean_bachelor=k", "m[Bu] signal mean k", 5279,
                          5275, 5285);
  RooRealVar buMassSigma_k("m[Bu]_Sigma_bachelor=k", "m[Bu] signal sigma k", 18,
                           15, 23);



  RooGaussian signalGaussian_k("Signal_Gaussian_bachelor=k",
                               "Signal gaussian pdf k", varToFit, buMassMean_k,
                               buMassSigma_k);



  RooArgList functions_k;
  functions_k.add(signalGaussian_k);
  functions_k.add(bu2Dst0HstGaussian);



  RooRealVar signalYield_k("signal_yield_bachelor=k", "m[Bu] signal yield k",
                           1000, 0, 2000);
  RooRealVar bu2Dst0HstYield_k("bu2Dst0Hst_yield_bachelor=k",
                               "m[Bu] bu2Dst0Hst yield k", 500, 0, 2000);



  RooArgList yields_k;
  yields_k.add(signalYield_k);
  yields_k.add(bu2Dst0HstYield_k);



  RooAddPdf pdf_k("pdf_k", "pdf_k", functions_k, yields_k);

  // --------------- define categories ---------------------
  

  RooCategory bachelor("bachelor", "bachelor");
  bachelor.defineType("pi");
  bachelor.defineType("k");


  // --------------- combine data sets ---------------------


  RooDataSet combinedDataSet(
      "combinedDataSet", "combinedDataSet", varToFit, RooFit::Index(bachelor),
      RooFit::Import("pi", piDataSet), RooFit::Import("k", kDataSet));

  // --------------- simultaneous pdf ---------------------


  RooSimultaneous simPdf("simPdf", "simPdf", bachelor);
  simPdf.addPdf(pdf_pi, "pi");
  simPdf.addPdf(pdf_k, "k");


  // --------------- fit  ---------------------
  
  simPdf.fitTo(combinedDataSet);

  // --------------- pi ---------------------
  
  // --------------- create frame ---------------------
  
  RooPlot *frame_pi = varToFit.frame(RooFit::Title("Dst0pi_D0pi0_kpi"));

  // --------------- plot data and pdfs onto frame ---------------------
 
  combinedDataSet.plotOn(frame_pi, RooFit::Cut("bachelor==bachelor::pi"));

  simPdf.plotOn(frame_pi, RooFit::Slice(bachelor, "pi"),
                RooFit::ProjWData(bachelor, combinedDataSet),
                RooFit::LineColor(kBlue));


  // --------------- k ---------------------
  
  // --------------- create frame ---------------------
  
  RooPlot *frame_k = varToFit.frame(RooFit::Title("Dst0k_D0pi0_kpi"));

  // --------------- plot data and pdfs onto frame ---------------------
  
  combinedDataSet.plotOn(frame_k, RooFit::Cut("bachelor==bachelor::k"));

  simPdf.plotOn(frame_k, RooFit::Slice(bachelor, "k"),
                RooFit::ProjWData(bachelor, combinedDataSet),
                RooFit::LineColor(kBlue));


  // --------------- plot onto canvas ---------------------
  
  TCanvas canvas("simPdf", "simPdf", 1000, 1000);

  canvas.Divide(1, 2);
  canvas.cd(1);
  frame_pi->Draw();
  canvas.cd(2);
  frame_k->Draw();

  canvas.SaveAs("Result.pdf");

}


int main(int argc, char **argv) {

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
