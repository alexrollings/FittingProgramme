#include "CommonFunctions.h"

std::string EnumToString(Variable variable) {
  switch (variable) {
    case Variable::bu:
      return "bu";
      break;
    case Variable::delta:
      return "delta";
      break;
    default:
      return "";
  }
}


bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

void AppendFiles(std::vector<std::string> &input) {
  namespace fs = std::experimental::filesystem;
  std::regex re(
      "\\/data\\/lhcb\\/users\\/rollings\\/Bu2Dst0h_mc_new_3\\/"
      "Bu2Dst0pi_D0gamma((_201[0-9]|_ReDecay).*)");
  std::string treeDir("/data/lhcb/users/rollings/Bu2Dst0h_mc_new_3/");
  for (auto &p : fs::directory_iterator(treeDir)) {
    std::smatch sm;
    std::stringstream pathStream;
    pathStream << p;
    std::string pathStr(pathStream.str());
    pathStr.erase(std::remove(pathStr.begin(), pathStr.end(), '"'),
                  pathStr.end());
    if (std::regex_match(pathStr, sm, re)) {
      input.emplace_back(treeDir + "Bu2Dst0pi_D0gamma" + sm[1].str() +
                         "/gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
                         "cross_feed_removed/Bu2Dst0pi_D0gamma" +
                         sm[1].str() +
                         "_TM_Triggers_BDT1_BDT2_MERemoved.root");
    }
  }
}

void SetupTChain(TChain &chain,
                 std::vector<std::string> const &input) {
  std::string tree;
  tree = "BtoDstar0h3_h1h2gammaTuple";
  try {
    chain.SetName(tree.c_str());
    std::cout << "Initialised TChain\n";
  } catch (std::exception &ex) {
    std::cout << "Could not set chain name : " << ex.what() << "!\n";
  }
  for (auto &f : input) {
    if (!fexists(f)) {
      throw std::logic_error(f + " does not exist\n");
    }
    try {
      chain.Add(f.c_str());
      std::cout << "Extracted TTree from " << f << "\n";
    } catch (std::exception &ex) {
      std::cout << "Failed to pass " << f << " to chain: " << ex.what()
                << "!\n";
    }
  }
}

void PlotCorrMatrix(RooFitResult *result, std::string const &outputDir,
                    std::string const &box_bu_low,
                    std::string const &box_bu_high,
                    std::string const &box_delta_low,
                    std::string const &box_delta_high) {
  TCanvas corrCanvas("corrCanvas", "corrCanvas", 1200, 900);
  TH2 *corrHist = result->correlationHist();
  corrHist->SetStats(0);
  corrHist->SetTitle(" ");
  corrCanvas.cd();
  gPad->SetLeftMargin(0.2);
  gPad->SetRightMargin(0.1);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.05);
  corrHist->SetLabelSize(0.04, "XY");
  corrHist->SetLabelSize(0.02, "Z");
  corrHist->Draw("colz");
  corrCanvas.Update();
  corrCanvas.SaveAs((outputDir + "/1d_plots/CorrelationMatrix.pdf" + "_" +
                     box_delta_low + "_" + box_delta_high + "_" + box_bu_low +
                     "_" + box_bu_high + ".pdf")
                        .c_str());
}

void PlotComponent(Variable variable, RooRealVar &var, RooDataHist *dataHist,
                   RooSimultaneous &simPdf, RooCategory &fitting,
                   RooAddPdf &sig, RooAbsPdf &bkg, std::string const &outputDir,
                   std::string const &box_bu_low,
                   std::string const &box_bu_high,
                   std::string const &box_delta_low,
                   std::string const &box_delta_high) {
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
      title = "m[D^{*0}#pi] - m[D^{*0}]";
      break;
    case Variable::delta:
      title = "m[D^{*0}] - m[D^{0}]";
      break;
  }

  auto frame =
      std::unique_ptr<RooPlot>(var.frame(RooFit::Title(title.c_str())));

  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(("fitting==fitting::" + EnumToString(variable)).c_str()));
  simPdf.plotOn(
      frame.get(), RooFit::Slice(fitting, EnumToString(variable).c_str()),
      RooFit::ProjWData(fitting, *dataHist), RooFit::LineColor(kBlue));
  pullHist = frame->RooPlot::pullHist();
  simPdf.plotOn(
      frame.get(), RooFit::Slice(fitting, EnumToString(variable).c_str()),
      RooFit::ProjWData(fitting, *dataHist), RooFit::Components(sig.GetName()),
      RooFit::LineColor(kBlue), RooFit::LineStyle(kDashed));
  simPdf.plotOn(
      frame.get(), RooFit::Slice(fitting, EnumToString(variable).c_str()),
      RooFit::ProjWData(fitting, *dataHist), RooFit::Components(bkg.GetName()),
      RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));

  dataHist->plotOn(
      frame.get(),
      RooFit::Cut(("fitting==fitting::" + EnumToString(variable)).c_str()));

  if (pullHist != 0) {
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(("pullFrame_" + EnumToString(variable)).c_str());
    pullFrame->SetTitle("");
  }

  TCanvas canvas(("canvas_" + EnumToString(variable)).c_str(), "", 1200, 1000);

  TPad pad1(("pad1_" + EnumToString(variable)).c_str(), "", 0.0, 0.14, 1.0, 1.0,
            kWhite);
  pad1.Draw();

  TPad pad2(("pad2_" + EnumToString(variable)).c_str(), "", 0.0, 0.05, 1.0,
            0.15, kWhite);
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
  canvas.SaveAs((outputDir + "/1d_plots/" + EnumToString(variable) + "_" +
                 box_delta_low + "_" + box_delta_high + "_" + box_bu_low + "_" +
                 box_bu_high + ".pdf")
                    .c_str());
}

void Plotting2D(RooRealVar &buMass, RooRealVar &deltaMass,
                RooDataHist *dataHist, RooAddPdf &pdf,
                std::string const &outputDir) {
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  auto dataHist1d = dataHist->createHistogram(
      "dataHist2d", buMass, RooFit::Binning(buMass.getBins()),
      RooFit::YVar(deltaMass, RooFit::Binning(deltaMass.getBins())));
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
  dataHist2d->SetTitle(
      "B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
      "pi^{#mp}#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}#pi^{#pm}");
  dataHist2d->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs((outputDir + "/2d_plots/2dData.pdf").c_str());

  auto modelHist1d = pdf.createHistogram(
      "modelHist2d", buMass, RooFit::Binning(buMass.getBins()),
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

  TCanvas canvasModel("canvasModel", "", 1000, 800);
  modelHist2d->SetStats(0);
  modelHist2d->SetTitle(
      "B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
      "pi^{#mp}#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}#pi^{#pm}");
  modelHist2d->Draw("colz");
  modelHist2d->GetZaxis()->SetRangeUser(-0.00001, modelHist2d->GetMaximum());
  canvasModel.Update();
  canvasModel.SaveAs((outputDir + "/2d_plots/2dPDF.pdf").c_str());

  gStyle->SetTitleOffset(1.2, "Z");
  // Make a histogram with the Poisson stats in each data bin
  auto errHist2d = std::unique_ptr<TH2F>(new TH2F(
      "errHist2d", "", buMass.getBins(), buMass.getMin(), buMass.getMax(),
      deltaMass.getBins(), deltaMass.getMin(), deltaMass.getMax()));
  for (int i = 0; i < buMass.getBins() * deltaMass.getBins(); i++) {
    float n_bin = dataHist2d->GetBinContent(i);
    float err = sqrt(n_bin);
    errHist2d->SetBinContent(i, err);
  }

  // 2D residuals plot (data - PDF)/err
  TCanvas canvasRes("canvasRes", "", 1000, 800);
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
  resHist2d->GetZaxis()->SetTitle("Residual");
  resHist2d->GetZaxis()->SetRangeUser(-6.0, 6.0);
  resHist2d->SetStats(0);
  resHist2d->Draw("colz");
  canvasRes.Update();
  canvasRes.SaveAs((outputDir + "/2d_plots/2dResiduals.pdf").c_str());

  // 1D residuals plot (sum over all 2D bins)
  TCanvas canvasRes1d("canvasRes1d", "", 1000, 800);
  canvasRes1d.cd();
  TH1F resHist1d("resHist1d", "", 130, -6, 6);
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
  canvasRes1d.SaveAs((outputDir + "/2d_plots/1dResiduals.pdf").c_str());
}

std::vector<std::string> SplitLine(std::string const &str) {
  std::stringstream ss;
  ss.str(str);
  std::string tempString;
  std::vector<std::string> stringVector;
  // '' = char
  while (std::getline(ss, tempString, ' ')) {
    stringVector.emplace_back(tempString);
  }
  return stringVector;
}

void CalcBinomialErr(double eff, double nInit, double &err) {
  if (eff > 1) {
    throw std::logic_error("Cannot have efficiency > 1");
  }
  // std::cout << eff << "\t" << nInit << "\n";
  err = std::sqrt((eff * (1 - eff)) / nInit);
  // std::cout << err << "\n";
};

double ReturnBoxEff(Efficiency eff, std::string const &dlString,
                    std::string const &dhString, std::string const &blString,
                    std::string const &bhString) {
  std::string boxStr =
      dlString + "_" + dhString + "_" + blString + "_" + bhString;
  std::string txtFileName =
      "/data/lhcb/users/rollings/toy_studies_old/box_efficiencies/Bu2Dst0pi_D0gamma_" +
      boxStr + ".txt";

  std::string effStr;
  if (eff == Efficiency::buCutEff) {
    // Box eff for delta dimn is eff of buDelta window, and vice versa
    effStr = "buDeltaCutEff";
  } else if (eff == Efficiency::deltaCutEff) {
    effStr = "deltaCutEff";
  } else if (eff == Efficiency::orEff) {
    effStr = "orEff";
  } else {
    effStr = "boxEff";
  }

  if (!fexists(txtFileName)) {
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
      std::cout << "Could net GetEntry(0) from chain: " << ex.what() << "!\n";
    }

    std::string orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                           ")||(Bu_Delta_M>" + blString + "&&Bu_Delta_M<" +
                           bhString + "))";
    std::string boxString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                            ")&&(Bu_Delta_M>" + blString + "&&Bu_Delta_M<" +
                            bhString + "))";

    double nInitial = chain.GetEntries();
    std::cout << "nInitial = " << nInitial << "\n";
    double nOr = chain.GetEntries(orString.c_str());
    std::cout << "nOr = " << nOr << "\n";
    double nBox = chain.GetEntries(boxString.c_str());
    std::cout << "nBox = " << nBox << "\n";
    double nBuCut = chain.GetEntries(
        (orString + "&&Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString)
            .c_str());
    std::cout << "nBuCut = " << nBuCut << "\n";
    double nDeltaCut = chain.GetEntries(
        (orString + "&&Delta_M>" + dlString + "&&Delta_M<" + dhString).c_str());
    std::cout << "nDeltaCut = " << nDeltaCut << "\n";

    double orEff = nOr / nInitial;
    double boxEff = nBox / nOr;
    double buDeltaCutEff = nBuCut / nOr;
    double deltaCutEff = nDeltaCut / nOr;

    double orEffErr;
    double boxEffErr;
    double buDeltaCutEffErr;
    double deltaCutEffErr;

    CalcBinomialErr(orEff, nInitial, orEffErr);
    CalcBinomialErr(boxEff, nOr, boxEffErr);
    CalcBinomialErr(buDeltaCutEff, nOr, buDeltaCutEffErr);
    CalcBinomialErr(deltaCutEff, nOr, deltaCutEffErr);

    std::ofstream outFile;
    outFile.open(txtFileName);
    outFile << "orEff " + std::to_string(orEff) + "\n";
    outFile << "orEffErr " + std::to_string(orEffErr) + "\n";
    outFile << "boxEff " + std::to_string(boxEff) + "\n";
    outFile << "boxEffErr " + std::to_string(boxEffErr) + "\n";
    outFile << "buDeltaCutEff " + std::to_string(buDeltaCutEff) + "\n";
    outFile << "buDeltaCutEffErr " + std::to_string(buDeltaCutEffErr) + "\n";
    outFile << "deltaCutEff " + std::to_string(deltaCutEff) + "\n";
    outFile << "deltaCutEffErr " + std::to_string(deltaCutEffErr) + "\n";

    if (eff == Efficiency::buCutEff) {
      return buDeltaCutEff;
    } else if (eff == Efficiency::deltaCutEff) {
      return deltaCutEff;
    } else if (eff == Efficiency::orEff) {
      return orEff;
    } else {
      return boxEff;
    }

  } else {
    //   // If exists, read in from txt file
    std::cout << txtFileName << " exists.\n";
    std::ifstream inFile(txtFileName);
    std::string line;
    // Loop over lines in txt file
    while (std::getline(inFile, line)) {
      // Separate label and value (white space)
      std::vector<std::string> lineVec = SplitLine(line);
      if (lineVec[0] == effStr) {
        std::cout << std::stod(lineVec[1]) << "\n";
        return std::stod(lineVec[1]);
      }
    }
    throw std::runtime_error("Efficiency not found.\n");
  }
}
