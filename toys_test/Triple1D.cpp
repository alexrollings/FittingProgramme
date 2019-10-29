#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooCategory.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooDstD0BG.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"
#include "RooTreeData.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTreeReader.h"

enum class Mode {
  Bu2Dst0pi_D0gamma,
  Bu2Dst0pi_D0pi0
};
enum class Variable { bu, delta };

std::string EnumToString(Mode mode) {
  switch (mode) {
    case Mode::Bu2Dst0pi_D0gamma:
      return "Bu2Dst0pi_D0gamma";
      break;
    case Mode::Bu2Dst0pi_D0pi0:
      return "Bu2Dst0pi_D0pi0";
      break;
    default:
      return " ";
      break;
  }
}

std::string EnumToString(Variable variable) {
  switch (variable) {
    case Variable::bu:
      return "bu";
      break;
    case Variable::delta:
      return "delta";
      break;
    default:
      return " ";
  }
}

void GetDataMapAndBoxEff(Mode mode, std::string const &deltaBoxLow,
                         std::string const &deltaBoxHigh,
                         std::string const &buBoxLow,
                         std::string const &buBoxHigh, RooRealVar &buMass,
                         RooRealVar &deltaMass,
                         std::map<std::string, RooDataSet *> &mapCategoryDataSet,
                         RooRealVar &boxEff, RooRealVar &deltaCutEff,
                         RooRealVar &buCutEff, RooRealVar &orEff) {
  std::string inputfile_1(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2011_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2011_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_2(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2011_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2011_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_3(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2012_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2012_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_4(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2012_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2012_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_5(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2015_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2015_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_6(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2015_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2015_MagDown_BDT1_BDT2_PID_TM.root");
  std::string inputfile_7(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2016_MagUp/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2016_MagUp_BDT1_BDT2_PID_TM.root");
  std::string inputfile_8(
      "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/" + EnumToString(mode) +
      "_2016_MagDown/"
      "gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" +
      EnumToString(mode) + "_2016_MagDown_BDT1_BDT2_PID_TM.root");
  std::string ttree("BtoDstar0h3_h1h2gammaTuple");

  TChain chain(ttree.c_str());

  chain.Add(inputfile_1.c_str());
  chain.Add(inputfile_2.c_str());
  chain.Add(inputfile_3.c_str());
  chain.Add(inputfile_4.c_str());
  chain.Add(inputfile_5.c_str());
  chain.Add(inputfile_6.c_str());
  chain.Add(inputfile_7.c_str());
  chain.Add(inputfile_8.c_str());

  chain.GetEntry(0);
  TTreeReader reader(&chain);

  TTreeReaderValue<int> Bu_BKGCAT(reader, "Bu_BKGCAT");
  TTreeReaderValue<double> Delta_M(reader, "Delta_M");
  TTreeReaderValue<double> Bu_Delta_M(reader, "Bu_Delta_M");
  TTreeReaderValue<double> D0_M(reader, "D0_M");
  TTreeReaderValue<double> D0h_M(reader, "D0h_M");
  TTreeReaderValue<double> D0_M_DOUBLESW_KP(reader, "D0_M_DOUBLESW_KP");
  TTreeReaderValue<float> BDT1(reader, "BDT1");
  TTreeReaderValue<float> BDT2(reader, "BDT2");
  TTreeReaderValue<double> bach_PIDK_corr(reader, "bach_PIDK_corr");
  TTreeReaderValue<double> D0_FD_ZSIG(reader, "D0_FD_ZSIG");


  TFile file("tree_file.root", "RECREATE");

  TTree *newTree = dynamic_cast<TTree *>(chain.GetTree()->CloneTree(0));
  if (newTree == nullptr) {
    throw std::runtime_error("File did not contain ttree.");
  }

  int i = 0;

  while (reader.Next()) {
    chain.GetEntry(i);
    i++;
    if (*BDT2 > 0.05 && *BDT1 > 0.05 && abs(*D0_M - 1864) < 25 &&
        *Delta_M > 50 && *Delta_M < 190 && *Bu_Delta_M > 4900 &&
        *Bu_Delta_M < 5800 && *bach_PIDK_corr < 12 &&
        abs(*D0_M_DOUBLESW_KP - 1864) > 15 && *D0_FD_ZSIG > 2 &&
        *D0h_M > 4900) {
      newTree->Fill();
    }
  }

  RooDataSet dataset("dataset", "dataset", newTree,
                     RooArgSet(buMass, deltaMass));

  RooDataSet *buDataSet = nullptr;
  buDataSet = dynamic_cast<RooDataSet *>(dataset.reduce(
      ("Delta_M>" + deltaBoxLow + "&&Delta_M<" + deltaBoxHigh).c_str()));
  if (buDataSet == nullptr) {
    throw std::runtime_error("Could not reduce bu data with box cuts.");
  }

  if (mapCategoryDataSet.find(EnumToString(Variable::bu)) ==
      mapCategoryDataSet.end()) {
    mapCategoryDataSet.insert(
        std::make_pair(EnumToString(Variable::bu), buDataSet));
    std::cout << "Created key-value pair for category " +
                     EnumToString(Variable::bu) +
                     " and corresponding dataset for MC of " +
                     EnumToString(mode) + "\n";
    ;

  } else {
    mapCategoryDataSet[EnumToString(Variable::bu)]->append(*buDataSet);
    std::cout << "Appended dataset for MC of " +
                     EnumToString(mode) + " to category " +
                     EnumToString(Variable::bu) + "\n";
  }

  RooDataSet *deltaDataSet = nullptr;
  deltaDataSet = dynamic_cast<RooDataSet *>(
      dataset.reduce(("Bu_Delta_M>" + buBoxLow + "&&Bu_Delta_M<" + buBoxHigh)
          .c_str()));
  if (deltaDataSet == nullptr) {
    throw std::runtime_error("Could not reduce delta data with box cuts.");
  }

  if (mapCategoryDataSet.find(EnumToString(Variable::delta)) ==
      mapCategoryDataSet.end()) {
    mapCategoryDataSet.insert(
        std::make_pair(EnumToString(Variable::delta), deltaDataSet));
    std::cout << "Created key-value pair for category " +
                     EnumToString(Variable::delta) +
                     " and corresponding dataset for MC of " +
                     EnumToString(mode) + "\n";
    ;

  } else {
    mapCategoryDataSet[EnumToString(Variable::delta)]->append(*deltaDataSet);
    std::cout << "Appended dataset for MC of " +
                     EnumToString(mode) + " to category " +
                     EnumToString(Variable::delta) + "\n";
  }

  double nInitial = newTree->GetEntries();
  double nDeltaWindow = newTree->GetEntries(
      ("Delta_M>" + deltaBoxLow + "&&Delta_M<" + deltaBoxHigh).c_str());
  double nBuWindow = newTree->GetEntries(
      ("Bu_Delta_M>" + buBoxLow + "&&Bu_Delta_M<" + buBoxHigh).c_str());
  double nBox = newTree->GetEntries(("Delta_M>" + deltaBoxLow + "&&Delta_M<" +
                                     deltaBoxHigh + "&&Bu_Delta_M>" +
                                     buBoxLow + "&&Bu_Delta_M<" + buBoxHigh)
                                        .c_str());
  double nOr = newTree->GetEntries(
      ("(Delta_M>" + deltaBoxLow + "&&Delta_M<" + deltaBoxHigh +
       ")||(Bu_Delta_M>" + buBoxLow + "&&Bu_Delta_M<" + buBoxHigh + ")")
          .c_str());

  deltaCutEff.setVal(nDeltaWindow / nInitial);
  buCutEff.setVal(nBuWindow / nInitial);
  boxEff.setVal(nBox / nInitial);
  orEff.setVal(nOr / nInitial);

  std::cout << "Set efficiencies for " << EnumToString(mode) << " :\n"
            << "\tDelta Window =\t" << nDeltaWindow / nInitial
            << "\tBu Window =\t" << nBuWindow / nInitial << "\tBox =\t"
            << nBox / nInitial << "\n"
            << "\tDelta OR Bu =\t" << nOr / nInitial << "\n"
            << "\t# events initially =\t" << nInitial << "\n";
}

void SimToy() {
  TApplication app("app", 0, 0);
  RooRandom::randomGenerator()->SetSeed(0);

  int buLow = 4900;
  int buHigh = 5800;
  int deltaLow = 60;
  int deltaHigh = 190;

  int bu_nbins = (buHigh - buLow) / 10;
  int delta_nbins = (deltaHigh - deltaLow) / 2;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_Delta_M", "m[D^{*0}#pi^{#pm}] - m[D^{*0}] + m[D^{*0}]_{PDG}", buLow, buHigh,
                    "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", deltaLow, deltaHigh,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);
  
  // DEFINE INDEX CATEGORIES
  RooCategory fitting("fitting", "fitting");
  fitting.defineType("bu");
  fitting.defineType("delta");

  // DEFINE PDFs
  // Signal
  RooRealVar meanDeltaSig("meanDeltaSig", "Mean of Sig m[Delta]", 145,
			     140, 150);
  RooRealVar sigmaDeltaSig("sigmaDeltaSig", "Sigma of pi Delta Gaussian",
			      8, 0, 15);
  RooGaussian pdfDeltaSig("pdfDeltaSig", "Sig pi Delta PDF", deltaMass,
			     meanDeltaSig, sigmaDeltaSig);

  RooRealVar meanBuSig("meanBuSig", "Mean of Sig m[Bu]", 5280,
			     5275, 5285);
  RooRealVar sigmaBuSig("sigmaBuSig", "Sigma of pi Bu Gaussian",
			      30, 0, 50);
  RooGaussian pdfBuSig("pdfBuSig", "Sig pi Bu PDF", buMass,
			     meanBuSig, sigmaBuSig);

  // ROOADDPDF
  RooRealVar yieldSig("yieldSig", "", 1000, 0, 5000);

  RooArgSet yields;
  yields.add(yieldSig);

  RooArgSet functionsBu;
  functionsBu.add(pdfBuSig);
  RooAddPdf pdfBu("pdfBu", "", functionsBu, yields);

  RooArgSet functionsDelta;
  functionsDelta.add(pdfDeltaSig);
  RooAddPdf pdfDelta("pdfDelta", "", functionsDelta, yields);

  // CONSTRUCT SIMULTANEOUS PDF
  RooSimultaneous simPdf("simPdf", "", fitting);
  simPdf.addPdf(pdfBu, "bu");
  simPdf.addPdf(pdfDelta, "delta");

  std::string buBoxLow = "5240";
  std::string buBoxHigh = "5320";
  std::string deltaBoxLow = "125";
  std::string deltaBoxHigh = "170";

  std::map<std::string, RooDataSet *> mapCategoryDataSet;

  RooRealVar boxEffGamma("boxEffGamma", "boxEffGamma", 1);
  RooRealVar deltaCutEffGamma("deltaCutEffGamma", "deltaCutEffGamma", 1);
  RooRealVar buCutEffGamma("buCutEffGamma", "buCutEffGamma", 1);
  RooRealVar orEffGamma("orEffGamma", "orEffGamma", 1);

  GetDataMapAndBoxEff(Mode::Bu2Dst0pi_D0gamma, deltaBoxLow, deltaBoxHigh, buBoxLow,
                      buBoxHigh, buMass, deltaMass,
                      mapCategoryDataSet,
                      boxEffGamma, deltaCutEffGamma, buCutEffGamma, orEffGamma);

  RooRealVar boxEffPi0("boxEffPi0", "boxEffPi0", 1);
  RooRealVar deltaCutEffPi0("deltaCutEffPi0", "deltaCutEffPi0", 1);
  RooRealVar buCutEffPi0("buCutEffPi0", "buCutEffPi0", 1);
  RooRealVar orEffPi0("orEffPi0", "orEffPi0", 1);

  GetDataMapAndBoxEff(Mode::Bu2Dst0pi_D0pi0, deltaBoxLow, deltaBoxHigh, buBoxLow,
                      buBoxHigh, buMass, deltaMass,
                      mapCategoryDataSet,
                      boxEffPi0, deltaCutEffPi0, buCutEffPi0, orEffPi0);

  RooDataSet combData("combData", "", RooArgSet(buMass, deltaMass),
		      RooFit::Index(fitting),
		      RooFit::Import(mapCategoryDataSet));

  combData.Print();

  // std::unique_ptr<RooFitResult> result = std::unique_ptr<RooFitResult>(
  //     simPdf.fitTo(combData, RooFit::Extended(true),
  //                  RooFit::SplitRange(true),
  //                  RooFit::Save(),
  //                  RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
  //                  RooFit::Offset(true), 
  //                  RooFit::NumCPU(8, 2)));

  // Plot
  std::unique_ptr<RooPlot> frameBu(buMass.frame(
      RooFit::Title("m[D^{*0}#pi^{#pm}] - m[D^{*0}] + m[D^{*0}]_{PDG}")));

  combData.plotOn(frameBu.get(), RooFit::Cut("fitting==fitting::bu"));

  // simPdf.plotOn(frameBu.get(), RooFit::Slice(fitting, "bu"),
	// 	RooFit::ProjWData(fitting, combData));
  // simPdf.plotOn(frameBu.get(), RooFit::Slice(fitting, "bu"),
	// 	RooFit::Components(pdfBuSig.GetName()),
	// 	RooFit::ProjWData(fitting, combData),
	// 	RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta),
	// 	RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));

  std::unique_ptr<RooPlot> frameDelta(deltaMass.frame(RooFit::Title("m[D^{*0}] - m[D^{0}]")));

  combData.plotOn(frameDelta.get(), RooFit::Cut("fitting==fitting::delta"));

  // simPdf.plotOn(frameDelta.get(), RooFit::Slice(fitting, "delta"),
	// 	RooFit::ProjWData(fitting, combData));
  // simPdf.plotOn(frameDelta.get(), RooFit::Slice(fitting, "delta"),
	// 	RooFit::Components(pdfDeltaSig.GetName()),
	// 	RooFit::ProjWData(fitting, combData),
	// 	RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta),
	// 	RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));

  TCanvas canvas("canvas", "canvas", 1000, 400);
  canvas.SetTitle(" ");
  canvas.Divide(2);
  canvas.cd(1);
  canvas.SetLogy();
  gPad->SetLeftMargin(0.15);
  frameBu->GetYaxis()->SetTitleOffset(1.4);
  frameBu->Draw();
  canvas.cd(2);
  gPad->SetLeftMargin(0.15);
  frameDelta->GetYaxis()->SetTitleOffset(1.4);
  frameDelta->Draw();

  canvas.SaveAs("SimpleToy.pdf");

  // result->Print("v");
  app.Run(true);
}

int main() {
  SimToy();
  return 0;
}
