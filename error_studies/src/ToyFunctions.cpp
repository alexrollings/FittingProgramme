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
  canvasToy.SaveAs((config.outputDir + "/plots/2D/2dToy.eps").c_str());

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
  canvasData.SaveAs((config.outputDir + "/plots/2D/2dData.eps").c_str());

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
  canvasResData.SaveAs((config.outputDir + "/plots/2D/2dResiduals.eps").c_str());
}

void GenerateToyFromData(std::unique_ptr<RooDataSet> &dataSet,
                         std::unique_ptr<RooDataSet> &toyDataSet, int const id,
                         Configuration &config) {
  auto dataHist = std::unique_ptr<RooDataHist>(dataSet->binnedClone(
      ("dataHist_" + std::to_string(id)).c_str(), "dataHist"));
  if (dataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }
  RooHistPdf histPdf(("histPdf_" + std::to_string(id)).c_str(), "",
                     config.fittingArgset, *dataHist.get(), 2);
  toyDataSet = std::unique_ptr<RooDataSet>(
      histPdf.generate(config.fittingArgset, dataSet->numEntries()));
}
