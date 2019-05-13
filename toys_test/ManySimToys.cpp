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
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooHist.h"
#include "RooPlot.h"
#include "RooPlotable.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"
#include "RooTreeData.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TLine.h"
#include "TPad.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTreeReader.h"

enum class Neutral { pi0, gamma };
enum class Bachelor { pi, k };
enum class Variable { bu, delta };

std::string EnumToString(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "pi0";
      break;
    case Neutral::gamma:
      return "gamma";
      break;
  }
}

std::string EnumToString(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "pi";
      break;
    case Bachelor::k:
      return "k";
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
  }
}

std::string EnumToLabel(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "#pi^{0}";
      break;
    case Neutral::gamma:
      return "#gamma";
      break;
  }
}

std::string EnumToLabel(Bachelor bachelor) {
  switch (bachelor) {
    case Bachelor::pi:
      return "#pi";
      break;
    case Bachelor::k:
      return "K";
      break;
  }
}

std::string FittingName(Neutral neutral, Bachelor bachelor) {
  switch (neutral) {
    case Neutral::pi0:
      switch (bachelor) {
        case Bachelor::pi:
          return "pi0_pi";
          break;
        case Bachelor::k:
          return "pi0_K";
          break;
      }
      break;
    case Neutral::gamma:
      switch (bachelor) {
        case Bachelor::pi:
          return "gamma_pi";
          break;
        case Bachelor::k:
          return "gamma_K";
          break;
      }
      break;
  }
}

void PlotComponent(Neutral neutral, Bachelor bachelor, Variable variable,
                   RooRealVar &var, RooDataHist *dataHist,
                   RooSimultaneous &simPdf, RooCategory &fitting,
                   RooProdPdf &sig, RooProdPdf &bkg,
                   std::string const &outputDir) {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.02);
  gStyle->SetTitleSize(0.08, "Z");
  gStyle->SetTitleSize(0.035, "XY");
  gStyle->SetLabelSize(0.03, "XY");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.5, "Y");
  gStyle->SetTitleOffset(0.95, "Z");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.12);

  std::string title;
  switch (variable) {
    case Variable::bu:
      title = "m[D^{*0}" + EnumToLabel(bachelor) + "]";
      break;
    case Variable::delta:
      switch (neutral) {
        case Neutral::gamma:
          title = "m[D^{*0}]-m[D^{0}]";
          break;
        case Neutral::pi0:
          title = "m[D^{*0}]-m[D^{0}] - m[#pi^{0}]";
          break;
      }
      break;
  }

  auto frame =
      std::unique_ptr<RooPlot>(var.frame(RooFit::Title(title.c_str())));

  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(
          ("fitting==fitting::" + FittingName(neutral, bachelor)).c_str()));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, FittingName(neutral, bachelor).c_str()),
                RooFit::ProjWData(fitting, *dataHist),
                RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, FittingName(neutral, bachelor).c_str()),
                RooFit::ProjWData(fitting, *dataHist),
                RooFit::Components(sig.GetName()), RooFit::LineColor(kBlue),
                RooFit::LineStyle(kDashed));
  simPdf.plotOn(frame.get(),
                RooFit::Slice(fitting, FittingName(neutral, bachelor).c_str()),
                RooFit::ProjWData(fitting, *dataHist),
                RooFit::Components(bkg.GetName()), RooFit::LineColor(kRed),
                RooFit::LineStyle(kDashed));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(
          ("fitting==fitting::" + FittingName(neutral, bachelor)).c_str()));

  if (pullHist != 0) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(("pullFrame_" + FittingName(neutral, bachelor)).c_str());
    pullFrame->SetTitle("");
  }

  TCanvas canvas(("canvas_" + EnumToString(variable) + "_" +
                  FittingName(neutral, bachelor))
                     .c_str(),
                 "", 1200, 1000);

  TPad pad1(
      ("pad1_" + EnumToString(variable) + "_" + FittingName(neutral, bachelor))
          .c_str(),
      "", 0.0, 0.14, 1.0, 1.0, kWhite);
  pad1.Draw();

  TPad pad2(
      ("pad2_" + EnumToString(variable) + "_" + FittingName(neutral, bachelor))
          .c_str(),
      "", 0.0, 0.05, 1.0, 0.15, kWhite);
  pad2.Draw();

  TLine zeroLine(var.getMin(), 0, var.getMax(), 0);
  zeroLine.SetLineColor(kRed);
  zeroLine.SetLineStyle(kDashed);

  canvas.cd();
  pad2.cd();
  pullFrame->SetYTitle(" ");
  pullFrame->SetXTitle(" ");
  pullFrame->SetLabelSize(0.2, "Y");
  pullFrame->SetLabelFont(132, "XY");
  pullFrame->SetLabelOffset(100, "X");
  pullFrame->SetTitleOffset(100, "X");
  pullFrame->Draw();
  zeroLine.Draw("same");

  canvas.cd();
  pad1.cd();
  frame->Draw();
  canvas.Update();
  canvas.SaveAs((outputDir + "/plots/" + FittingName(neutral, bachelor) + "_" +
                 EnumToString(variable) + "Projection.pdf")
                    .c_str());
}

void Plotting2D(Neutral neutral, Bachelor bachelor, RooRealVar &buMass,
                RooRealVar &deltaMass, RooDataHist *dataHist,
                RooSimultaneous &simPdf, RooCategory &fitting,
                std::string const &outputDir) {
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  auto dataHist1d = dataHist->createHistogram(
      ("dataHist2d_" + FittingName(neutral, bachelor)).c_str(), buMass,
      RooFit::Binning(buMass.getBins()),
      RooFit::YVar(deltaMass, RooFit::Binning(deltaMass.getBins())),
      RooFit::Cut(
          ("fitting==fitting::" + FittingName(neutral, bachelor)).c_str()));
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
  TCanvas canvasData(("canvasData_" + FittingName(neutral, bachelor)).c_str(),
                     "", 1000, 800);
  dataHist2d->SetStats(0);
  if (neutral == Neutral::pi0) {
    dataHist2d->GetYaxis()->SetTitle(
        "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  dataHist2d->SetTitle(("B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
                        "pi^{#mp}#font[132]{]}_{D^{0}}" +
                        EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" +
                        EnumToLabel(bachelor) + "^{#pm}")
                           .c_str());
  dataHist2d->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs(
      (outputDir + "/plots/" + FittingName(neutral, bachelor) + "_2dData.pdf")
          .c_str());
  auto singlePdf = simPdf.getPdf(FittingName(neutral, bachelor).c_str());
  if (singlePdf == nullptr) {
    throw std::runtime_error("\nSingle pdf empty\n");
  }

  auto modelHist1d = singlePdf->createHistogram(
      ("modelHist2d_" + FittingName(neutral, bachelor)).c_str(), buMass,
      RooFit::Binning(buMass.getBins()),
      RooFit::YVar(deltaMass, RooFit::Binning(deltaMass.getBins())));
  if (modelHist1d == nullptr) {
    throw std::runtime_error("\n1D hist of pdf returns nullptr\n");
  }
  auto modelHist2d =
      std::unique_ptr<TH2>(dynamic_cast<TH2F *>(modelHist1d /* .get() */));
  if (modelHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
  }
  modelHist2d->SetTitle("");

  // Make 2D plot of data
  // Plot ONLY one component of the data
  modelHist2d->Scale(dataHist2d->Integral() / modelHist2d->Integral());

  TCanvas canvasModel(("canvasModel_" + FittingName(neutral, bachelor)).c_str(),
                      "", 1000, 800);
  modelHist2d->SetStats(0);
  if (neutral == Neutral::pi0) {
    modelHist2d->GetYaxis()->SetTitle(
        "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  modelHist2d->SetTitle(("B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
                         "pi^{#mp}#font[132]{]}_{D^{0}}" +
                         EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" +
                         EnumToLabel(bachelor) + "^{#pm}")
                            .c_str());
  modelHist2d->Draw("colz");
  modelHist2d->GetZaxis()->SetRangeUser(-0.00001, modelHist2d->GetMaximum());
  canvasModel.Update();
  canvasModel.SaveAs(
      (outputDir + "/plots/" + FittingName(neutral, bachelor) + "_2dPDF.pdf")
          .c_str());

  gStyle->SetTitleOffset(1.2, "Z");
  // Make a histogram with the Poisson stats in each data bin
  auto errHist2d = std::unique_ptr<TH2F>(
      new TH2F(("errHist2d_" + FittingName(neutral, bachelor)).c_str(), "",
               buMass.getBins(), buMass.getMin(), buMass.getMax(),
               deltaMass.getBins(), deltaMass.getMin(), deltaMass.getMax()));
  for (int i = 0; i < buMass.getBins() * deltaMass.getBins(); i++) {
    float n_bin = dataHist2d->GetBinContent(i);
    float err = sqrt(n_bin);
    errHist2d->SetBinContent(i, err);
  }

  // 2D residuals plot (data - PDF)/err
  TCanvas canvasRes(("canvasRes_" + FittingName(neutral, bachelor)).c_str(), "",
                    1000, 800);
  canvasRes.cd();
  // auto resHist2d_temp = std::unique_ptr<TObject>(dataHist2d->Clone());
  auto resHist2d_temp = dataHist2d->Clone();
  if (resHist2d_temp == nullptr) {
    throw std::runtime_error("\nCould not clone dataHist2d.\n");
  }
  auto resHist2d =
      std::unique_ptr<TH2F>(dynamic_cast<TH2F *>(resHist2d_temp /* .get() */));
  if (resHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
  }
  resHist2d->Add(modelHist2d.get(), -1);
  resHist2d->Divide(errHist2d.get());
  canvasRes.cd();
  if (neutral == Neutral::pi0) {
    resHist2d->GetYaxis()->SetTitle(
        "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  resHist2d->GetZaxis()->SetTitle("Residual");
  resHist2d->GetZaxis()->SetRangeUser(-6.0, 6.0);
  resHist2d->SetStats(0);
  resHist2d->Draw("colz");
  canvasRes.Update();
  canvasRes.SaveAs((outputDir + "/plots/" + FittingName(neutral, bachelor) +
                    "_2dResiduals.pdf")
                       .c_str());

  // 1D residuals plot (sum over all 2D bins)
  TCanvas canvasRes1d(("canvasRes1d_" + FittingName(neutral, bachelor)).c_str(),
                      "", 1000, 800);
  canvasRes1d.cd();
  TH1F resHist1d(("resHist1d_" + FittingName(neutral, bachelor)).c_str(), "",
                 130, -6, 6);
  for (int i = 0; i < buMass.getBins() * deltaMass.getBins(); i++) {
    float n_bin = resHist2d->GetBinContent(i);
    if (n_bin != 0) {
      resHist1d.Fill(n_bin);
    }
  }
  resHist1d.GetXaxis()->SetTitle("Residual");
  resHist1d.GetYaxis()->SetTitle("Entries");
  resHist1d.SetTitle("");
  resHist1d.SetStats(0);
  resHist1d.Draw();
  canvasRes1d.Update();
  canvasRes1d.SaveAs((outputDir + "/plots/" + FittingName(neutral, bachelor) +
                      "_1dResiduals.pdf")
                         .c_str());
}

void GenerateToys(std::string const &outputDir, int nToys, bool toPlot) {

  int bu_low = 5045;
  int bu_high = 5805;
  int delta_low = 80;
  int delta_high = 240;

  int bu_nbins = (bu_high - bu_low) / 5;
  int delta_nbins = (delta_high - delta_low) / 2;

  RooRealVar buMass("Bu_M_DTF_D0", "m[D^{*0}#pi^{#pm}]", bu_low, bu_high,
                    "MeV/c^{2}");
  RooRealVar deltaMass("Delta_M", "m[D^{*0}] - m[D^{0}]", delta_low, delta_high,
                       "MeV/c^{2}");

  buMass.setBins(bu_nbins);
  deltaMass.setBins(delta_nbins);

  // DEFINE INDEX CATEGORIES
  RooCategory fitting("fitting", "fitting");
  fitting.defineType("pi0_pi");
  fitting.defineType("pi0_K");

  // run nToys fits and store the values in the histograms
  for (int i = 0; i < nToys; i++) {
    RooRandom::randomGenerator()->SetSeed(0);
    TRandom3 random(0);
    double randomTag = random.Rndm();

    TFile outputFile(
        (outputDir + "/ResultFile" + std::to_string(randomTag) + ".root")
            .c_str(),
        "recreate");
    // DEFINE pi PDFs
    // SIGNAL
    RooRealVar meanDeltaSignal(("meanDeltaSignal_" + std::to_string(i)).c_str(), "",
                               145, 140, 150);
    RooRealVar a0MeanBuSignal(("a0MeanBuSignal_" + std::to_string(i)).c_str(), "",
                              5101.86875, 4879, 5579);
    RooRealVar a1MeanBuSignal(("a1MeanBuSignal_" + std::to_string(i)).c_str(), "",
                              2.1375, 0, 10);
    RooRealVar a2MeanBuSignal(("a2MeanBuSignal_" + std::to_string(i)).c_str(), "",
                              -0.0062, -0.01, -0.00001);
    RooPolyVar meanBuSignal(
        ("meanBuSignal_" + std::to_string(i)).c_str(), "", deltaMass,
        RooArgList(a0MeanBuSignal, a1MeanBuSignal, a2MeanBuSignal));
    RooRealVar sigmaDeltaSignalPi(("sigmaDeltaSignalPi_" + std::to_string(i)).c_str(), "", 20, 0, 40);
    RooGaussian pdfDeltaSignalPi(("pdfDeltaSignalPi_" + std::to_string(i)).c_str(), "",
                                 deltaMass, meanDeltaSignal,
                                 sigmaDeltaSignalPi);
    RooRealVar sigmaBuSignalPi(("sigmaBuSignalPi_" + std::to_string(i)).c_str(), "",
                               100, 0, 150);
    RooGaussian pdfBuSignalPi(("pdfBuSignalPi_" + std::to_string(i)).c_str(), "", buMass,
                              meanBuSignal, sigmaBuSignalPi);
    RooProdPdf pdfSignalPi(("pdfSignalPi_" + std::to_string(i)).c_str(), "", pdfDeltaSignalPi,
                           RooFit::Conditional(pdfBuSignalPi, buMass));
    // BACKGROUND
    RooRealVar lambdaDeltaCombPi(("lambdaDeltaCombPi_" + std::to_string(i)).c_str(), "",
                                 -0.001, -1, 1);
    RooRealVar a0LambdaBuCombPi(("a0LambdaBuCombPi_" + std::to_string(i)).c_str(), "", -0.001, -1, 1);
    RooPolyVar lambdaBuCombPi(("lambdaBuCombPi_" + std::to_string(i)).c_str(), "",
                              deltaMass, RooArgList(a0LambdaBuCombPi));
    RooExponential pdfDeltaCombPi(("pdfDeltaCombPi_" + std::to_string(i)).c_str(), "",
                                  deltaMass, lambdaDeltaCombPi);
    RooExponential pdfBuCombPi(("pdfBuCombPi_" + std::to_string(i)).c_str(), "", buMass,
                               lambdaBuCombPi);
    RooProdPdf pdfCombPi(("pdfCombPi_" + std::to_string(i)).c_str(), "", pdfDeltaCombPi,
                         RooFit::Conditional(pdfBuCombPi, buMass));
    // ROOADDPDF
    RooRealVar yieldSignalPi(("yieldSignalPi_" + std::to_string(i)).c_str(), "", 50000, 0,
                             100000);
    RooRealVar yieldBackgroundPi(("yieldBackgroundPi_" + std::to_string(i)).c_str(), "",
                                 10000, 0, 50000);

    RooArgSet yieldsPi;
    yieldsPi.add(yieldSignalPi);
    yieldsPi.add(yieldBackgroundPi);
    RooArgSet functionsPi;
    functionsPi.add(pdfSignalPi);
    functionsPi.add(pdfCombPi);

    RooAddPdf pdfPi("pdfPi", "pdf pi", functionsPi, yieldsPi);

    // DEFINE K SIGNAL PDFs
    // SIGNAL
    RooRealVar sigmaRatio(("sigmaRatio_" + std::to_string(i)).c_str(), "", 0.95, 0, 1);
    RooFormulaVar sigmaDeltaSignalK(("sigmaDeltaSignalK_" + std::to_string(i)).c_str(), "", "@0*@1",
                                    RooArgList(sigmaDeltaSignalPi, sigmaRatio));
    RooGaussian pdfDeltaSignalK(("pdfDeltaSignalK_" + std::to_string(i)).c_str(), "",
                                deltaMass, meanDeltaSignal, sigmaDeltaSignalK);
    RooFormulaVar sigmaBuSignalK(("sigmaBuSignalK_" + std::to_string(i)).c_str(), "",
                                 "@0*@1",
                                 RooArgList(sigmaBuSignalPi, sigmaRatio));
    RooGaussian pdfBuSignalK(("pdfBuSignalK_" + std::to_string(i)).c_str(), "", buMass,
                             meanBuSignal, sigmaBuSignalK);
    RooProdPdf pdfSignalK(("pdfSignalK_" + std::to_string(i)).c_str(), "", pdfDeltaSignalK,
                          RooFit::Conditional(pdfBuSignalK, buMass));
    // BACKGROUND
    RooRealVar lambdaDeltaCombK(("lambdaDeltaCombK_" + std::to_string(i)).c_str(), "",
                                -0.001, -1, 1);
    RooRealVar a0LambdaBuCombK(("a0LambdaBuCombK_" + std::to_string(i)).c_str(), "",
                               -0.001, -1, 1);
    RooPolyVar lambdaBuCombK(("lambdaBuCombK_" + std::to_string(i)).c_str(), "", deltaMass,
                             RooArgList(a0LambdaBuCombK));
    RooExponential pdfDeltaCombK(("pdfDeltaCombK_" + std::to_string(i)).c_str(), "",
                                 deltaMass, lambdaDeltaCombK);
    RooExponential pdfBuCombK(("pdfBuCombK_" + std::to_string(i)).c_str(), "", buMass,
                              lambdaBuCombK);
    RooProdPdf pdfCombK(("pdfCombK_" + std::to_string(i)).c_str(), "", pdfDeltaCombK,
                        RooFit::Conditional(pdfBuCombK, buMass));
    // ROOADDPDF
    RooRealVar yieldRatio(("yieldRatio_" + std::to_string(i)).c_str(), "", 0.1, 0, 1);
    RooFormulaVar yieldSignalK(("yieldSignalK_" + std::to_string(i)).c_str(), "", "@0*@1",
                               RooArgList(yieldSignalPi, yieldRatio));
    RooRealVar yieldBackgroundK(("yieldBackgroundK_" + std::to_string(i)).c_str(), "",
                                100, 0, 500);

    RooArgSet yieldsK;
    yieldsK.add(yieldSignalK);
    yieldsK.add(yieldBackgroundK);
    RooArgSet functionsK;
    functionsK.add(pdfSignalK);
    functionsK.add(pdfCombK);

    RooAddPdf pdfK("pdfK", "pdf k", functionsK, yieldsK);

    // CONSTRUCT SIMULTANEOUS PDF
    RooSimultaneous simPdf(("simPdf_" + std::to_string(i)).c_str(),
                           "", fitting);
    simPdf.addPdf(pdfPi, "pi0_pi");
    simPdf.addPdf(pdfK, "pi0_K");

    double nEvtsPerToy = simPdf.expectedEvents(fitting);

    RooDataSet *toyDataSet =
        simPdf.generate(RooArgSet(buMass, deltaMass, fitting), nEvtsPerToy);
    toyDataSet->SetName(("toyDataSet_" + std::to_string(i)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(i)).c_str(),
                                ("toyDataHist" + std::to_string(i)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    meanDeltaSignal.setVal(142);

    RooFitResult *result = 0;
    result = simPdf.fitTo(*toyAbsData, RooFit::Save(true));

    outputFile.cd();
    result->SetName(("Result" + std::to_string(randomTag)).c_str());
    result->Print("v");
    result->Write();
    outputFile.Close();

    std::cout << "Result saved in file " << outputDir << "/ResultFile"
              << std::to_string(randomTag) << ".root\n";

    if (toPlot == true && i == 0) {
      std::cout << "Plotting projections of m[Bu]\n";
      PlotComponent(Neutral::pi0, Bachelor::pi, Variable::bu, buMass,
                    toyDataHist.get(), simPdf, fitting, pdfSignalPi, pdfCombPi,
                    outputDir);
      PlotComponent(Neutral::pi0, Bachelor::k, Variable::bu, buMass,
                    toyDataHist.get(), simPdf, fitting, pdfSignalK, pdfCombK,
                    outputDir);
      std::cout << "Plotting projections of m[Delta]\n";
      PlotComponent(Neutral::pi0, Bachelor::pi, Variable::delta, deltaMass,
                    toyDataHist.get(), simPdf, fitting, pdfSignalPi, pdfCombPi,
                    outputDir);
      PlotComponent(Neutral::pi0, Bachelor::k, Variable::delta, deltaMass,
                    toyDataHist.get(), simPdf, fitting, pdfSignalK, pdfCombK,
                    outputDir);
      std::cout << "Plotting in 2D\n";
      Plotting2D(Neutral::pi0, Bachelor::pi, buMass, deltaMass,
                 toyDataHist.get(), simPdf, fitting, outputDir);
      Plotting2D(Neutral::pi0, Bachelor::k, buMass, deltaMass,
                 toyDataHist.get(), simPdf, fitting, outputDir);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Enter output directory and number of toys. Optional argument to plot toys = plot\n";
    return 1;
  }
  std::string outputDir = argv[1];
  int nToys = std::atoi(argv[2]);
  bool toPlot = false;
  if (argc == 4) {
    std::string plotString = argv[3];
    if (plotString == "plot") {
      toPlot = true;
    } else {
      std::cout << "Not plotting: if desired, specify plot as third argument\n";
    }
  }
  GenerateToys(outputDir, nToys, toPlot);
  return 0;
}
