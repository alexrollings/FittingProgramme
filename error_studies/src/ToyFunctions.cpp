#include "ToyFunctions.h"

void Plotting2D(Configuration &config, RooDataSet &toyDS,
                RooDataSet &dataDS) {
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  auto toyHist = std::unique_ptr<RooDataHist>(
      toyDS.binnedClone("toyDataHist", "toyDataHist"));

  auto toyHist1d = toyHist->createHistogram(
      "toyHist2d", config.buMass, RooFit::Binning(config.buMass.getBins()),
      RooFit::YVar(config.deltaMass,
                   RooFit::Binning(config.deltaMass.getBins())));
  if (toyHist1d == nullptr) {
    throw std::runtime_error("\n1D hist of toy returns nullptr\n");
  }
  auto toyHist2d =
      std::unique_ptr<TH2>(dynamic_cast<TH2F *>(toyHist1d /* .get() */));
  if (toyHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of toy returns nullptr\n");
  }
  toyHist2d->SetTitle("");


  // 2D data plot
  TCanvas canvasToy("canvasToy", "", 1000, 800);
  toyHist2d->SetStats(0);
  toyHist2d->Draw("colz");
  canvasToy.Update();
  canvasToy.SaveAs((config.outputDir + "/plots/1D/2dToy.pdf").c_str());

  auto dataHist = std::unique_ptr<RooDataHist>(
      dataDS.binnedClone("dataDataHist", "dataDataHist"));

  auto dataHist1d = dataHist->createHistogram(
      "dataHist2d", config.buMass, RooFit::Binning(config.buMass.getBins()),
      RooFit::YVar(config.deltaMass,
                   RooFit::Binning(config.deltaMass.getBins())));
  if (dataHist1d == nullptr) {
    throw std::runtime_error("\n1D hist of data returns nullptr\n");
  }
  auto dataHist2d =
      std::unique_ptr<TH2>(dynamic_cast<TH2F *>(dataHist1d /* .get() */));
  if (dataHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of data returns nullptr\n");
  }
  dataHist2d->SetTitle("");


  // 2D data plot
  TCanvas canvasData("canvasData", "", 1000, 800);
  dataHist2d->SetStats(0);
  dataHist2d->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs((config.outputDir + "/plots/1D/2dData.pdf").c_str());

  gStyle->SetTitleOffset(1.2, "Z");
  // Make a histogram with the Poisson stats in each data bin
  auto errHist2d = std::unique_ptr<TH2F>(
      new TH2F("errHist2d", "", config.buMass.getBins(), config.buMass.getMin(),
               config.buMass.getMax(), config.deltaMass.getBins(),
               config.deltaMass.getMin(), config.deltaMass.getMax()));
  for (int i = 0; i < config.buMass.getBins() * config.deltaMass.getBins();
       i++) {
    float n_bin = toyHist2d->GetBinContent(i);
    float err = sqrt(n_bin);
    errHist2d->SetBinContent(i, err);
  }

  // 2D residuals plot (toy - data)/err
  TCanvas canvasResData("canvasResData", "", 1000, 800);
  canvasResData.cd();
  // auto resHist2d_temp = std::unique_ptr<TObject>(toyHist2d->Clone());
  auto resDataHist2dToy_temp = toyHist2d->Clone();
  if (resDataHist2dToy_temp == nullptr) {
    throw std::runtime_error("\nCould not clone toyHist2d.\n");
  }
  auto resDataHist2dToy =
      std::unique_ptr<TH2F>(dynamic_cast<TH2F *>(resDataHist2dToy_temp /* .get() */));
  if (resDataHist2dToy == nullptr) {
    throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
  }
  resDataHist2dToy->Add(dataHist2d.get(), -1);
  resDataHist2dToy->Divide(errHist2d.get());
  canvasResData.cd();
  resDataHist2dToy->GetZaxis()->SetTitle("Resdual");
  resDataHist2dToy->GetZaxis()->SetRangeUser(-6.0, 6.0);
  resDataHist2dToy->SetStats(0);
  resDataHist2dToy->Draw("colz");
  canvasResData.Update();
  canvasResData.SaveAs((config.outputDir + "/toys/2dResidualsDataToyPi0.pdf").c_str());
}

// void RunToys2DData(TFile &outputFile,
//                    std::unique_ptr<RooFitResult> &dataFitResult,
//                    std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
//                    Configuration &config,
//                    std::vector<Daughters> const &daughtersVec,
//                    std::vector<Charge> const &chargeVec,
//                    std::string const &config.outputDir, int id) {
//   std::cout << "\n\n -------------------------- Running toy #" << id
//             << " -------------------------- \n\n";
//   auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
//   auto pdfs = p.second;
//
//   std::map<std::string, RooDataSet *> mapDataLabelToy;
//
//   for (auto &p : pdfs) {
//     GenerateToyFromData(mapDataLabelDataSet, mapDataLabelToy, id, *p, config,
//                         config.outputDir);
//   }
//
//   auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);
//
//   std::map<std::string, RooDataSet *> mapFittingDataSet;
//   std::map<std::string, RooDataSet *> mapFittingToy;
//   for (auto &p : pdfs) {
//     MakeMapFittingDataSet(*p, mapDataLabelDataSet, mapFittingDataSet, config);
//     MakeMapFittingDataSet(*p, mapDataLabelToy, mapFittingToy, config);
//   }
//
//   RooDataSet toyDataSet("toyDataSet", "toyDataSet", config.fittingArgSet(),
//                         RooFit::Index(config.fitting),
//                         RooFit::Import(mapFittingToy));
//
//   auto toyDataHist = std::unique_ptr<RooDataHist>(
//       toyDataSet.binnedClone("toyDataHist", "toyDataHist"));
//   if (toyDataHist == nullptr) {
//     throw std::runtime_error("Could not extact binned dataSet.");
//   }
//   auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());
//   if (toyAbsData == nullptr) {
//     throw std::runtime_error("Could not cast to RooAbsData.");
//   }
//
//   std::shared_ptr<RooFitResult> toyFitResult;
//   if (config.noFit() == false) {
//     toyFitResult = std::shared_ptr<RooFitResult>(
//         simPdf->fitTo(*toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
//                       RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
//                       RooFit::Offset(true), RooFit::NumCPU(config.nCPU())));
//     // toyFitResult->SetName(("ToyResult_" + std::to_string(id)).c_str());
//     toyFitResult->SetName("ToyResult");
//   }
//
//   RooDataSet dataSet("dataSet", "dataSet", config.fittingArgSet(),
//                      RooFit::Index(config.fitting),
//                      RooFit::Import(mapFittingDataSet));
//
//   std::cout << "\n\n\n";
//   toyDataSet.Print();
//   dataSet.Print();
//   std::cout << "\n\n\n";
//
//   // if (id == 1) {
//   //   for (auto &p : pdfs) {
//   //     std::string toyLabel = "toy";
//   //     std::string dataLabel = "data";
//   //     Plotting2D(dataSet, id, *p, config, config.outputDir, dataLabel);
//   //     Plotting2D(toyDataSet, id, *p, config, config.outputDir, toyLabel);
//   //   }
//   //   std::map<Neutral, std::map<Mass, double> > yMaxMap;
//   //   std::map<std::string, Int_t> colorMap = MakeColorMap(config);
//   //   for (auto &p : pdfs) {
//   //     Plotting1D(id, *p, config, *toyAbsData, *simPdf, colorMap, config.outputDir,
//   //                toyFitResult.get(), yMaxMap);
//   //   }
//   //   if (config.noFit() == false) {
//   //     PlotCorrelations(toyFitResult.get(), config.outputDir, config);
//   //   }
//   // }
//   if (config.noFit() == false) {
//     // to make a unique result each time
//     toyFitResult->Print("v");
//     outputFile.cd();
//     toyFitResult->Write();
//     dataFitResult->Write();
//     outputFile.Close();
//     std::cout << toyFitResult->GetName() << " has been saved to file "
//               << outputFile.GetName() << "\n";
//   }
// }
