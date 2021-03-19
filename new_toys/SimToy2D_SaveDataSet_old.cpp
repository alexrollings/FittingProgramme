#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <random>

#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooCategory.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooDstD0BG.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooPlotable.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooHistPdf.h"
#include "RooRandom.h"
#include "RooTreeData.h"
#include "TApplication.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTreeReader.h"

#include "CommonFunctions.h" 

void GenerateToys(std::string const &outputDir, int nToys, std::string const &dataType) {
  int bu_low = 5050;
  int bu_high = 5500;
  int delta_low = 60;  // 134;
  int delta_high = 190;

  int bu_nbins = (bu_high - bu_low) / 10;
  int delta_nbins = (delta_high - delta_low) / 2;

  // ---------------------------- Fitting Vars ----------------------------
  RooRealVar buMass("Bu_Delta_M", "m[D^{*0}#pi^{#pm}] - m[D^{*0}]", bu_low, bu_high,
                    "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  RooDataSet *dataset = nullptr;
  std::string dsFname = "/data/lhcb/users/rollings/toy_studies_old/mc_datasets/Bu2Dst0pi_D0gamma.root";

  if (!fexists(dsFname)) {
    std::cerr << "Making dataset: " << dsFname << ".\n";
    std::vector<std::string> input;
    AppendFiles(input);
    if (input.size() == 0) {
      throw std::runtime_error("No input files found\n");
    }
    TChain chain("");
    SetupTChain(chain, input);
    std::cout << "Returned TChain\n";
    try {
      chain.GetEntry(0);
    } catch (std::exception &ex) {
      std::cout << "Could not GetEntry(0) from chain: " << ex.what() << "!\n";
    }
    dataset = new RooDataSet("dataset", "dataset", &chain,
                             RooArgSet(buMass, deltaMass));
    TFile dsFile(dsFname.c_str(), "RECREATE");
    dataset->Write("dataset");
    dsFile.Close();
  } else {
    std::cout << dsFname << " exists.\n";
    TFile dsFile(dsFname.c_str(), "READ");
    gDirectory->GetObject("dataset", dataset);
    if (dataset == nullptr) {
      throw std::runtime_error("dataset does not exist.\n");
    } else {
      std::cout << "dataset extracted: \n";
      dataset->Print();
    }
  }

  RooDataHist* dataHist = dataset->binnedClone("dataHist", "dataHist");
  RooHistPdf histPdf("histPdf", "histPdf", RooArgSet(buMass, deltaMass),
                     *dataHist, 2);

  // ---------------------------- PDFs ----------------------------
  //
  // ---------------------------- Signal ----------------------------
  // ---------------------------- Mean ----------------------------
  RooRealVar meanDeltaSignal("meanDeltaSignal", "", 1.4256e+02);  //, 135, 150);
  // ---------------------------- Sigmas ----------------------------
  RooRealVar sigmaDeltaSignal("sigmaDeltaSignal", "", 8.4647e+00);  //, 5, 15);
  // ---------------------------- Tails ----------------------------
  RooRealVar a1DeltaSignal("a1DeltaSignal", "", 1.6783e+00);
  RooRealVar a2DeltaSignal("a2DeltaSignal", "", -5.6685e-01);
  RooRealVar n1DeltaSignal("n1DeltaSignal", "", 4.1125e+00);
  RooRealVar n2DeltaSignal("n2DeltaSignal", "", 4.4286e+00);
  // ---------------------------- PDFs ----------------------------
  RooCBShape pdfDeltaSignal1("pdfDeltaSignal1", "", deltaMass, meanDeltaSignal,
                             sigmaDeltaSignal, a1DeltaSignal, n1DeltaSignal);
  RooCBShape pdfDeltaSignal2("pdfDeltaSignal2", "", deltaMass, meanDeltaSignal,
                             sigmaDeltaSignal, a2DeltaSignal, n2DeltaSignal);
  RooRealVar fracPdf1DeltaSignal("fracPdf1DeltaSignal", "", 2.8510e-01);
  RooAddPdf pdfDeltaSignal("pdfDeltaSignal", "",
                           RooArgSet(pdfDeltaSignal1, pdfDeltaSignal2),
                           fracPdf1DeltaSignal);

  // ---------------------------- π PDFs: Bu ----------------------------
  // ---------------------------- Signal ----------------------------
  // ---------------------------- Mean ----------------------------
  RooRealVar a0MeanBuSignal("a0MeanBuSignal", "", 5.1774e+03);  //, 4500, 5500);
  RooRealVar a1MeanBuSignal("a1MeanBuSignal", "", 8.9919e-01);  //, -10, 10);
  RooRealVar a2MeanBuSignal("a2MeanBuSignal", "", -1.2149e-03);  //, -0.1, 0.1);
  RooPolyVar meanBuSignal(
      "meanBuSignal", "", deltaMass,
      RooArgList(a0MeanBuSignal, a1MeanBuSignal, a2MeanBuSignal));
  // ---------------------------- Sigmas ----------------------------
  RooRealVar a0SigmaBuSignal("a0SigmaBuSignal", "", 2.8951e+02);  //, 300, 400);
  RooRealVar a1SigmaBuSignal("a1SigmaBuSignal", "", -3.4700e+00);  //, -10, 10);
  RooRealVar a2SigmaBuSignal("a2SigmaBuSignal", "", 1.2303e-02);

  RooPolyVar sigma1BuSignal(
      "sigma1BuSignal", "", deltaMass,
      RooArgList(a0SigmaBuSignal, a1SigmaBuSignal, a2SigmaBuSignal));

  RooRealVar sigma21FracBuSignal("sigma21FracBuSignal", "",
                                 4.1625e-01);  //, -1, 1);

  RooFormulaVar sigma2BuSignal("sigma2BuSignal", "", "@0*@1",
                               RooArgSet(sigma1BuSignal, sigma21FracBuSignal));

  // ---------------------------- PDFs ----------------------------
  RooRealVar fracPdf1BuSignal("fracPdf1BuSignal", "", 6.3427e-02);
  RooGaussian pdfBuSignal1("pdfBuSignal1", "", buMass, meanBuSignal,
                           sigma1BuSignal);
  RooGaussian pdfBuSignal2("pdfBuSignal2", "", buMass, meanBuSignal,
                           sigma2BuSignal);
  RooAddPdf pdfBuSignal("pdfBuSignal", "",
                        RooArgSet(pdfBuSignal1, pdfBuSignal2),
                        fracPdf1BuSignal);
  // ---------------------------- π Total PDF ----------------------------
  RooProdPdf pdfSignal("pdfSignal", "", pdfDeltaSignal,
                       RooFit::Conditional(pdfBuSignal, buMass));

  // ---------------------------- Background ----------------------------

  // RooRealVar lambdaDeltaBkg("lambdaDeltaBkg", "", 0.01);//, -0.1, 0.1);
  // RooExponential pdfDeltaBkg("pdfDeltaBkg", "", deltaMass, lambdaDeltaBkg);

  RooRealVar thresholdDeltaBkg("thresholdDeltaBkg", "", 5.8300e+01);
  RooRealVar cDeltaBkg("cDeltaBkg", "", 8.3605e+01);
  RooRealVar aDeltaBkg("aDeltaBkg", "", 2.2537e-01);
  RooRealVar bDeltaBkg("bDeltaBkg", "", -3.5935e-01);
  RooDstD0BG pdfDeltaBkg("pdfDeltaBkg", "", deltaMass, thresholdDeltaBkg,
                         cDeltaBkg, aDeltaBkg, bDeltaBkg);
  // ---------------------------- π/K shared PDFs: Bu
  // ----------------------------
  // RooRealVar lambdaBuBkg("lambdaBuBkg", "", -0.005);//, -0.1, 0.1);
  // RooExponential pdfBuBkg("pdfBuBkg", "", buMass, lambdaBuBkg);

  RooRealVar meanBuBkg("meanBuBkg", "", 5.2499e+03);
  RooRealVar sigmaBuBkg("sigmaBuBkg", "", 7.9054e+01);
  RooGaussian pdfBuBkg("pdfBuBkg", "", buMass, meanBuBkg, sigmaBuBkg);

  // RooRealVar a0Mean1BuBkg("a0Mean1BuBkg", "",
  //                         5.1083e+03);  //, 4500, 5500);
  // RooRealVar a1Mean1BuBkg("a1Mean1BuBkg", "",
  //                         2.4092e+00);  //, -10, 10);
  // RooRealVar a2Mean1BuBkg("a2Mean1BuBkg", "",
  //                         -5.4048e-03);  //, -0.1, 0.1);
  // RooPolyVar mean1BuBkg("mean1BuBkg", "", deltaMass,
  //                       RooArgList(a0Mean1BuBkg, a1Mean1BuBkg,
  //                       a2Mean1BuBkg));
  // RooRealVar a0Mean2BuBkg("a0Mean2BuBkg", "",
  //                         5.0444e+03);  //, -4500, 5500);
  // RooRealVar a1Mean2BuBkg("a1Mean2BuBkg", "",
  //                         2.0779e+00);  //, -10, 10);
  // RooRealVar a2Mean2BuBkg("a2Mean2BuBkg", "",
  //                         -6.3321e-03);  //, -0.1, 0.1);
  // RooPolyVar mean2BuBkg("mean2BuBkg", "", deltaMass,
  //                       RooArgList(a0Mean2BuBkg, a1Mean2BuBkg,
  //                       a2Mean2BuBkg));
  // // ---------------------------- Sigmas ----------------------------
  // RooRealVar a0Sigma1BuBkg("a0Sigma1BuBkg", "", 9.8314e+00);   //, -300,
  // 300); RooRealVar a1Sigma1BuBkg("a1Sigma1BuBkg", "", 5.8179e-01);   //, -10,
  // 10); RooRealVar a2Sigma1BuBkg("a2Sigma1BuBkg", "", -7.5647e-04);  //, -0.1,
  // 0.1); RooPolyVar sigma1BuBkg(
  //     "sigma1BuBkg", "", deltaMass,
  //     RooArgList(a0Sigma1BuBkg, a1Sigma1BuBkg, a2Sigma1BuBkg));
  // RooRealVar sigmaFracBuBkg("sigmaFracBuBkg", "", 8.0270e-01);  //, -0.1,
  // 0.1); RooFormulaVar sigma2BuBkg("sigma2BuBkg", "", "@0*@1",
  //                           RooArgSet(sigma1BuBkg, sigmaFracBuBkg));
  //
  // RooRealVar fracPdf1BuBkg("fracPdf1BuBkg", "", 5.2225e-01);
  // RooGaussian pdfBuBkg1("pdfBuBkg1", "", buMass, mean1BuBkg, sigma1BuBkg);
  // RooGaussian pdfBuBkg2("pdfBuBkg2", "", buMass, mean2BuBkg, sigma2BuBkg);
  // RooAddPdf pdfBuBkg("pdfBuBkg", "", RooArgSet(pdfBuBkg1, pdfBuBkg2),
  //                    fracPdf1BuBkg);
  // // ---------------------------- π Total PDF ----------------------------
  // RooProdPdf pdfBkg("pdfBkg", "", pdfDeltaBkg,
  //                   RooFit::Conditional(pdfBuBkg, buMass));
  RooProdPdf pdfBkg("pdfBkg", "", RooArgSet(pdfDeltaBkg, pdfBuBkg));

  double nSig;
  if (dataType == "pdf") {
    nSig = 40000.0;
  } else {
    nSig = dataset->numEntries();
  }
  // ---------------------------- Yields ----------------------------
  RooRealVar yieldSignal("yieldSignal", "", nSig, -1000000, 1000000);
  RooRealVar yieldBkg("yieldBkg", "", 80000, -1000000, 1000000);
  // RooRealVar fracBkgYield("fracBkgYield", "", 0.8, -5, 5);
  // RooFormulaVar yieldBkg("yieldBkg", "", "@0*@1",
  //                        RooArgSet(yieldSignal, fracBkgYield));

  // ---------------------------- Add PDFs and yields
  // ----------------------------
  RooArgSet yields;
  yields.add(yieldSignal);
  yields.add(yieldBkg);
  RooArgSet functions;
  if (dataType == "pdf") {
    functions.add(pdfSignal);
  } else {
    functions.add(histPdf);
  }
  functions.add(pdfBkg);
  RooAddPdf pdf("pdf", "", functions, yields);

  double nEvtsPerToy = yieldSignal.getVal() + yieldBkg.getVal();
  std::cout << "Generating toy dataset..." << std::endl;

  for (int i = 0; i < nToys; i++) {
    // RooRandom::randomGenerator()->SetSeed(0);
    // TRandom3 random(0);
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<UInt_t> dist;
    UInt_t seed = dist(rng);
    // UInt_t seed = 0xa1c93ad5;
    RooRandom::randomGenerator()->SetSeed(seed);

    // ---------------------------- Generate toy dataSets for bu and delta
    // spearately: save them
    // ----------------------------

    std::stringstream filename;
    filename << outputDir << "/datasets/DataFile_" << std::hex << seed
             << ".root";
    TFile dsFile(filename.str().c_str(), "recreate");

    RooDataSet *buDataSet = pdf.generate(RooArgSet(buMass, deltaMass), nEvtsPerToy);
    std::cout << "Generated!" << std::endl;
    buDataSet->SetName("buDataSet");
    buDataSet->Write("buDataSet");
    buDataSet->Print();

    RooDataSet *deltaDataSet = pdf.generate(RooArgSet(deltaMass, buMass), nEvtsPerToy);
    std::cout << "Generated!" << std::endl;
    deltaDataSet->SetName("deltaDataSet");
    deltaDataSet->Write("deltaDataSet");
    deltaDataSet->Print();
    dsFile.Close();

    // ---------------------------- Generate toy dataSet: CAN'T generate bu
    // and delta separately as doesn't generate whole 2D phase space
    // ----------------------------
    // RooDataSet *toyDataSet =
    //     pdf.generate(RooArgSet(buMass, deltaMass), nEvtsPerToy);
    // std::cout << "Generated!" << std::endl;
    // toyDataSet->Print();

    // std::stringstream filename;
    // filename << outputDir << "/datasets/DataFile_" << std::hex << seed
    //          << ".root";
    // TFile dsFile(filename.str().c_str(), "recreate");
    // toyDataSet->Write("dataset");
    // toyDataSet->Print();
    // dsFile.Close();
    // // std::cout << "Saved " << randomTag<< " dataSet\n";
    //
    // auto toyDataHist = std::unique_ptr<RooDataHist>(
    //     toyDataSet->binnedClone("toyDataHist", "toyDataHist"));
    // auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    // meanDeltaSignal.setVal(142);

    // std::unique_ptr<RooFitResult> result =
    //     std::unique_ptr<RooFitResult>(pdf.fitTo(
    //         *toyAbsData, RooFit::Extended(true), RooFit::SplitRange(true),
    //         RooFit::Save(), RooFit::Strategy(2),
    //         RooFit::Minimizer("Minuit2"), RooFit::Offset(true),
    //         RooFit::NumCPU(8, 2)));

    // ---------------------------- Plot if specified
    // ----------------------------
    // std::cout << "Plotting projections of m[Bu]\n";
    // PlotComponent(Variable::bu, buMass, toyDataHist.get(), pdf, pdfSignal,
    // pdfBkg,
    //               outputDir);
    // std::cout << "Plotting projections of m[Delta]\n";
    // PlotComponent(Variable::delta, deltaMass, toyDataHist.get(), pdf,
    // pdfSignal,
    //               pdfBkg, outputDir);
    // std::cout << "Plotting in 2D\n";
    // if (i == 0) {
    //   Plotting2D(buMass, deltaMass, toyDataHist.get(), pdf, outputDir);
    // }
    // std::cout << "Plotting correlation matrix\n";
    // PlotCorrMatrix(result.get(), outputDir);
    //
    // result->Print("v");
    }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr
        << "Enter output directory, number of toy DataSets to generate and how to generate: mc/pdf\n";
    return 1;
  }
  std::string outputDir = argv[1];
  int nToys = std::atoi(argv[2]);
  std::string dataType = argv[3];
  if (dataType != "mc" && dataType != "pdf") {
    std::cerr << "dataType = mc/pdf\n";
    return 1;
  }
  GenerateToys(outputDir, nToys, dataType);
  return 0;
}
