#include <fstream>
#include <iostream>

#include "Configuration.h"
#include "NeutralVars.h"
#include "NeutralBachelorVars.h"
#include "ParseArguments.h"
#include "PdfMC.h"

#include "TTreeReader.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include "TLine.h"
#include "TAxis.h"
#include "TH2.h"
#include "TRandom3.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooDataSet.h"
#include "RooSimultaneous.h"
#include "RooFitResult.h"
#include "RooHistPdf.h"
#include "RooDataHist.h"
#include "RooRandom.h"
#include "RooProdPdf.h"

// Check file exists
bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

// Function to set the style for all THists
void SetStyle() {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.04, "XY");
  gStyle->SetLabelSize(0.035, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetLegendTextSize(0.05);
  gStyle->SetTitleOffset(1.0, "X");
  gStyle->SetTitleOffset(1.3, "Y");
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.11);
}

// Function to plot 1D projections - written so that it can be used for both bu
// and delta mass
void PlotComponent(Mass mass, RooRealVar &var, 
                   RooAbsData const &dataSet, RooSimultaneous const &simPdf,
                   std::string const &outputDir,
                   Configuration &config, RooCategory &fittingMC, std::string label) {
  SetStyle();
  int id = 0;
  // Stops ROOT print INFO messages
  gErrorIgnoreLevel = kWarning;

  std::unique_ptr<RooPlot> frame(var.frame(RooFit::Title(" ")));

  dataSet.plotOn(
      frame.get(),
      RooFit::Cut(("fittingMC==fittingMC::" + EnumToString(mass)).c_str()));

  simPdf.plotOn(
      frame.get(), RooFit::Slice(fittingMC, EnumToString(mass).c_str()),
      RooFit::ProjWData(fittingMC, dataSet), RooFit::LineColor(kBlue));

  // Everything to be plotted has to be declared outside of a loop, in the scope
  // of the canvas
  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  pullHist = frame->RooPlot::pullHist();

  dataSet.plotOn(
      frame.get(),
      RooFit::Cut(("fittingMC==fittingMC::" + EnumToString(mass)).c_str()));

  if (mass == Mass::delta) {
    if (config.neutral() == Neutral::gamma) {
      frame->SetXTitle("m[D^{*0}] - m[D^{0}] (MeV/c^{2})");
    } else {
      frame->SetXTitle(
          "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
    }
  } else {
    frame->SetXTitle(("m[D^{*0}" + EnumToLabel(Bachelor::pi) + "^{" +
                      EnumToLabel(Charge::total) + "}" +
                      "] - m[D^{*0}] + m[D^{*0}]_{PDG} (MeV/c^{2})")
                         .c_str());
  }

  // --------------- plot onto canvas ---------------------
  TCanvas canvas(
      ("canvas_" + EnumToString(mass)) 
          .c_str(),
      "canvas", 1200, 1000);

  TPad pad1(("pad1_" + EnumToString(mass)).c_str(), "pad1", 0.0, 0.14, 1.0, 1.0,
            kWhite);
  pad1.Draw();

  TPad pad2(("pad2_" + EnumToString(mass)).c_str(), "pad2", 0.0, 0.02, 1.0,
            0.14, kWhite);
  pad2.Draw();

  TLine zeroLine(var.getMin(), 0, var.getMax(), 0);
  zeroLine.SetLineColor(kRed);
  zeroLine.SetLineStyle(kDashed);

  canvas.cd();
  pad2.cd();
  pullFrame->addPlotable(pullHist /* .get() */, "P");
  pullFrame->SetName(("pullFrame_" + EnumToString(mass)).c_str());
  pullFrame->SetTitle("");
  pullFrame->SetXTitle(" ");
  pullFrame->GetYaxis()->SetTitle(" ");
  // pullFrame->GetYaxis()->SetTitle("Residuals (#sigma)");
  // pullFrame->SetTitleSize(0.2, "Y");
  // pullFrame->SetTitleOffset(0.1, "Y");
  pullFrame->SetLabelSize(0.15, "Y");
  pullFrame->SetLabelOffset(0.02, "Y");
  pullFrame->SetLabelFont(132, "Y");
  pullFrame->Draw();
  zeroLine.Draw("same");

  canvas.cd();
  pad1.cd();
  frame->Draw();

  canvas.Update();
  canvas.SaveAs((outputDir + "/plots/" + EnumToString(config.neutral()) + "_" +
                 EnumToString(mass) + "_" + config.ReturnBoxString() + "_" + label + ".pdf")
                    .c_str());
}

RooDataSet ExtractDataSetFromMC(Configuration &config,
                                std::string const &inputDir, PdfMC &pdf) {
  RooDataSet *inputDataSet = nullptr;
  std::string input =
      inputDir + "/" + EnumToString(config.neutral()) + "_exp_dataset.root";

  if (!fexists(input)) {
    std::string extra = "";
    std::string ttree("BtoDstar0h3_h1h2pi0RTuple");
    if (config.neutral() == Neutral::gamma) {
      extra = "cross_feed_removed/";
      ttree = "BtoDstar0h3_h1h2gammaTuple";
    }
    std::string inputfile_1(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0" +
        EnumToString(config.neutral()) +
        "_2011_MagUp/"
        "" +
        EnumToString(config.neutral()) +
        "/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/" + extra +
        "Bu2Dst0pi_D0" + EnumToString(config.neutral()) +
        "_2011_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_2(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0" +
        EnumToString(config.neutral()) +
        "_2011_MagDown/"
        "" +
        EnumToString(config.neutral()) +
        "/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/" + extra +
        "Bu2Dst0pi_D0" + EnumToString(config.neutral()) +
        "_2011_MagDown_BDT1_BDT2_PID_TM.root");
    std::string inputfile_3(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0" +
        EnumToString(config.neutral()) +
        "_2012_MagUp/"
        "" +
        EnumToString(config.neutral()) +
        "/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/" + extra +
        "Bu2Dst0pi_D0" + EnumToString(config.neutral()) +
        "_2012_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_4(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0" +
        EnumToString(config.neutral()) +
        "_2012_MagDown/"
        "" +
        EnumToString(config.neutral()) +
        "/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/" + extra +
        "Bu2Dst0pi_D0" + EnumToString(config.neutral()) +
        "_2012_MagDown_BDT1_BDT2_PID_TM.root");
    std::string inputfile_5(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0" +
        EnumToString(config.neutral()) +
        "_2015_MagUp/"
        "" +
        EnumToString(config.neutral()) +
        "/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/" + extra +
        "Bu2Dst0pi_D0" + EnumToString(config.neutral()) +
        "_2015_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_6(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0" +
        EnumToString(config.neutral()) +
        "_2015_MagDown/"
        "" +
        EnumToString(config.neutral()) +
        "/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/" + extra +
        "Bu2Dst0pi_D0" + EnumToString(config.neutral()) +
        "_2015_MagDown_BDT1_BDT2_PID_TM.root");
    std::string inputfile_7(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0" +
        EnumToString(config.neutral()) +
        "_2016_MagUp/"
        "" +
        EnumToString(config.neutral()) +
        "/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/" + extra +
        "Bu2Dst0pi_D0" + EnumToString(config.neutral()) +
        "_2016_MagUp_BDT1_BDT2_PID_TM.root");
    std::string inputfile_8(
        "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/"
        "Bu2Dst0pi_D0" +
        EnumToString(config.neutral()) +
        "_2016_MagDown/"
        "" +
        EnumToString(config.neutral()) +
        "/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/" + extra +
        "Bu2Dst0pi_D0" + EnumToString(config.neutral()) +
        "_2016_MagDown_BDT1_BDT2_PID_TM.root");

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

    inputDataSet =
        new RooDataSet("inputDataSet", "inputDataSet", &chain,
                       RooArgSet(config.fullArgSet()));

    RooProdPdf exp2D("exp2D", "",
                     RooArgSet(pdf.pdfBuDeltaExp(), pdf.pdfDeltaExp()));

    RooRandom::randomGenerator()->SetSeed(1);
    TRandom3 random(1);

    double nExp;
    if (config.neutral() == Neutral::gamma) {
      nExp = 10000;
    } else {
      nExp = 2000;
    }

    auto expToy =
        exp2D.generate(config.fittingArgSet(), nExp);

    inputDataSet->append(*expToy);

    TFile dataFile(input.c_str(), "RECREATE");
    inputDataSet->Write("inputDataSet");
    dataFile.Close();
    std::cout << "MC roodataset saved in " << input << "\n";
  } else {
    std::cout << "Extracting roodataset from " << input << "\n";

    TFile inData(input.c_str(), "READ");
    gDirectory->GetObject("inputDataSet", inputDataSet);
    inData.Close();

    if (inputDataSet == nullptr) {
      throw std::runtime_error("Data set does not exist.");
    } else {
      std::cout << "Dataset extracted\n";
    }
  }

  std::string cutString;
  if (config.neutral() == Neutral::gamma) {
    cutString = config.gammaCutString();
  } else {
    cutString = config.pi0CutString();
  }

  auto reducedData = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
      inputDataSet->reduce(config.fittingArgSet(), cutString.c_str())));
  return *reducedData;
}

RooDataSet SpliceData(RooAbsData &data2D, Configuration &config,
                      RooCategory &fittingMC) {
  auto dataBu_tmp = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
      data2D.reduce(("Delta_M>" + std::to_string(config.deltaLow()) +
                         "&&Delta_M<" + std::to_string(config.deltaHigh()))
                            .c_str())));
  if (dataBu_tmp.get() == nullptr) {
    throw std::runtime_error("Could not reduce data2D with delta mass.");
  }
  auto dataBu = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
      dataBu_tmp->reduce(RooArgSet(config.buDeltaMass()))));
  if (dataBu.get() == nullptr) {
    throw std::runtime_error("Could not reduce dataBu_tmp to BuDelta mass.");
  }

  auto dataDelta_tmp = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
      data2D.reduce(("Bu_Delta_M>" + std::to_string(config.buDeltaLow()) +
                         "&&Bu_Delta_M<" + std::to_string(config.buDeltaHigh()))
                            .c_str())));
  if (dataDelta_tmp.get() == nullptr) {
    throw std::runtime_error("Could not reduce data2D with buDelta mass.");
  }
  auto dataDelta = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
      dataDelta_tmp->reduce(RooArgSet(config.deltaMass()))));
  if (dataDelta.get() == nullptr) {
    throw std::runtime_error("Could not reduce dataDelta_tmp to Delta mass.");
  }

  RooDataSet splicedData(
      "splicedData", "", RooArgSet(config.fittingArgSet()),
      RooFit::Index(fittingMC),
      RooFit::Import(EnumToString(Mass::buDelta).c_str(), *dataBu.get()),
      RooFit::Import(EnumToString(Mass::delta).c_str(), *dataDelta.get()));
  return splicedData;
}

void SaveEffToTree(Configuration &config, TFile &outputFile, TTree &tree,
                   PdfMC &pdf, const int id) {
  double boxEff = pdf.boxEff().getVal();
  double orEff = pdf.orEff().getVal();
  double buDeltaCutEff = pdf.buDeltaCutEff().getVal();
  double deltaCutEff = pdf.deltaCutEff().getVal();
  
  Mode mode;
  if (Configuration::Get().neutral() == Neutral::gamma) {
    mode = Mode::Bu2Dst0pi_D0gamma;
  } else {
    mode = Mode::Bu2Dst0pi_D0pi0;
  }

  outputFile.cd();
  tree.Branch(("orEff_" + EnumToString(mode)).c_str(), &orEff,
              ("orEff_" + EnumToString(mode) + "/D").c_str());
  tree.Branch(("boxEff_" + EnumToString(mode)).c_str(), &boxEff,
              ("boxEff_" + EnumToString(mode) + "/D").c_str());
  tree.Branch(("buDeltaCutEff_" + EnumToString(mode)).c_str(), &buDeltaCutEff,
              ("buDeltaCutEff_" + EnumToString(mode) + "/D").c_str());
  tree.Branch(("deltaCutEff_" + EnumToString(mode)).c_str(), &deltaCutEff,
              ("deltaCutEff_" + EnumToString(mode) + "/D").c_str());
  tree.Fill();
}

int main(int argc, char **argv) {
  std::string inputDir = "";
  std::string outputDir;

  int nToys = 0;
  Configuration &config = Configuration::Get();
  
  {
    ParseArguments args(argc, argv);
    std::string neutralArg("gamma");
    int toysArg = 1;
    float deltaLowArg = 0.0;
    float deltaHighArg = 0.0;
    float buDeltaLowArg = 0.0;
    float buDeltaHighArg = 0.0;

    if (args("help")) {
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "Type ./FittingMC \n"
                << "-inputDir=<RooDataSets directory name> \n"
                << "-outputDir=<output directory> \n";
      std::cout
          << "Give box dimensions:\n"
          << "    -dl=#, -dh=#, -bl=#, -bh=# \n";
      std::cout << "    -neutral=<pi0/gamma> \n";
      std::cout << "    -toys=<# toys> \n";
    } else {
      if (!args("toys", toysArg)) {
          std::cerr << "Must specify number of toys: -toys=<# toys> \n";
          return 1;
      } else {
        nToys = toysArg;
        config.runToy() = true;
        std::cout << "Running " << nToys << " toys\n";
      }

      if (!args("inputDir", inputDir)) {
          std::cerr << "Data directory where MC roodatasets are stored must be specified (-inputDir=<path>).\n";
          return 1;
        } 

      if (!args("outputDir", outputDir)) {
        std::cerr << "Specify output directory (-outputDir=<path>).\n";
        return 1;
      }
      if (!args("neutral", neutralArg)) {
          std::cerr << "Must specify neutral: -neutral=<pi0/gamma> \n";
          return 1;
      }
      try {
        config.SetNeutral(StringToEnum<Neutral>(neutralArg));
      } catch (std::invalid_argument) {
        std::cerr << "neutral assignment failed, please specify: "
                     "-neutral=<pi0/gamma>\n";
        return 1;
      }
      if (!args("bl", buDeltaLowArg)) {
        std::cout
            << "Using default value for lower buDelta mass box threshold: " +
                   std::to_string(config.buDeltaLow()) + "\n";
      } else {
        config.SetBuDeltaLow(buDeltaLowArg);
        std::cout << "Set value for lower buDelta mass box threshold: " +
                         std::to_string(config.buDeltaLow()) + "\n";
      }
      if (!args("bh", buDeltaHighArg)) {
        std::cout
            << "Using default value for upper buDelta mass box threshold: " +
                   std::to_string(config.buDeltaHigh()) + "\n";
      } else {
        config.SetBuDeltaHigh(buDeltaHighArg);
        std::cout << "Set value for upper buDelta mass box threshold: " +
                         std::to_string(config.buDeltaHigh()) + "\n";
      }
      if (!args("dl", deltaLowArg)) {
        std::cout
            << "Using default value for lower delta mass box threshold: " +
                   std::to_string(config.deltaLow()) + "\n";
      } else {
        config.SetDeltaLow(deltaLowArg);
        std::cout << "Set value for lower delta mass box threshold: " +
                         std::to_string(config.deltaLow()) + "\n";
      }
      if (!args("dh", deltaHighArg)) {
        std::cout
            << "Using default value for upper delta mass box threshold: " +
                   std::to_string(config.deltaHigh()) + "\n";
      } else {
        config.SetDeltaHigh(deltaHighArg);
        std::cout << "Set value for upper delta mass box threshold: " +
                         std::to_string(config.deltaHigh()) + "\n";
      }
    }
  }

  // Raise lower mass boundary in delta mass for pi0 plots
  config.buDeltaMass().setMin(5150);
  config.buDeltaMass().setMax(5400);
  config.buDeltaMass().setBins(50);
  if (config.neutral() == Neutral::pi0) {
    config.deltaMass().setMin(136);
    config.deltaMass().setMax(164);
    config.deltaMass().setBins(28);
  } else {
    config.deltaMass().setMin(110);
    config.deltaMass().setBins(40);
  }

  std::cout << "Neutral = " << EnumToString(config.neutral()) << "\n";

  // ---------------------------- Categories ----------------------------
  RooCategory fittingMC("fittingMC", "fittingMC");
  fittingMC.defineType(EnumToString(Mass::buDelta).c_str());
  fittingMC.defineType(EnumToString(Mass::delta).c_str());

  // ---------------------------- Model ----------------------------
  int const id = 0;
  RooSimultaneous *simPdf = new RooSimultaneous(
      ("simPdf_" + std::to_string(id)).c_str(),
      ("simPdf_" + std::to_string(id)).c_str(), fittingMC);
  auto pdf = &PdfMC::Get(id);
  pdf->AddToSimultaneousPdf(*simPdf);


  // ---------------------------- Make MC dataset 
  // ----------------------------
  RooDataSet data2D = ExtractDataSetFromMC(config, inputDir, *pdf);
  std::cout << "Extracted MC dataset\n";
  RooDataSet splicedData = SpliceData(data2D, config, fittingMC);
  std::cout << "Returned spliced dataset\n";

  auto splicedHist = std::unique_ptr<RooDataHist>(
      splicedData.binnedClone("splicedHist", "splicedHist"));
  if (splicedHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet of data2D.");
  }
  auto splicedAbsData = dynamic_cast<RooAbsData *>(splicedHist.get());
  if (splicedAbsData == nullptr) {
    throw std::runtime_error("Could not cast splicedHist to RooAbsData.");
  }

  std::cout << "Fit simPdf to MC...\n";
  std::unique_ptr<RooFitResult> mcResult = std::unique_ptr<RooFitResult>(
      simPdf->fitTo(*splicedAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                   RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                   RooFit::Offset(true), RooFit::NumCPU(8, 2)));

  if (id == 0) {
    std::string label = "data";
    PlotComponent(Mass::buDelta, config.buDeltaMass(), splicedData, *simPdf,
                  outputDir, config, fittingMC, label);
    PlotComponent(Mass::delta, config.deltaMass(), splicedData, *simPdf, outputDir,
                  config, fittingMC, label);
  }
  mcResult->Print("v");
  // To match PlotToys.cpp
  mcResult->SetName("DataFitResult");

  auto dataHist2D = std::unique_ptr<RooDataHist>(
      data2D.binnedClone("dataHist2D", "dataHist2D"));
  if (dataHist2D == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }
  RooHistPdf histPdf("histPdf", "", config.fittingArgSet(), *dataHist2D.get(), 2);

  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  TH2F *hh_data = (TH2F *)dataHist2D->createHistogram(
      "Bu_Delta_M,Delta_M", config.buDeltaMass().getBins(),
      config.deltaMass().getBins());
  hh_data->SetTitle("");
  TCanvas canvasData("CanvasData", "", 1000, 800);
  hh_data->SetStats(0);
  if (config.neutral() == Neutral::pi0) {
    hh_data->GetYaxis()->SetTitle(
        "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  hh_data->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs(
      (outputDir + "/2d_plots/2dMC_" + EnumToString(config.neutral()) + ".pdf")
          .c_str());

  TH2F *hh_model = (TH2F *)histPdf.createHistogram(
      "hh_model", config.buDeltaMass(),
      RooFit::Binning(config.buDeltaMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
  hh_model->SetTitle("");
  TCanvas canvasModel("CanvasModel", "", 1000, 800);
  hh_model->SetStats(0);
  if (config.neutral() == Neutral::pi0) {
    hh_model->GetYaxis()->SetTitle(
        "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  hh_model->Draw("colz");
  canvasModel.Update();
  canvasModel.SaveAs(
      (outputDir + "/2d_plots/2dPdf_" + EnumToString(config.neutral()) + ".pdf")
          .c_str());

  // start at id = 1 to reserve 0 for MC fit
  for (int id = 1; id < nToys + 1; ++id) {
    RooRandom::randomGenerator()->SetSeed(0);
    TRandom3 random(0);
    double randomTag = random.Rndm();
    auto toy2D =
        histPdf.generate(config.fittingArgSet(), data2D.numEntries());
    toy2D->SetName(("toy2D_" + std::to_string(id)).c_str());
    RooDataSet toyData = SpliceData(*toy2D, config, fittingMC);
    toyData.SetName(("toyData_" + std::to_string(id)).c_str());
    auto toyHist = std::unique_ptr<RooDataHist>(
        toyData.binnedClone("toyHist", "toyHist"));
    if (toyHist == nullptr) {
      throw std::runtime_error("Could not extact binned dataSet of totalData.");
    } else {
      toyHist->SetName(("toyHist_" + std::to_string(id)).c_str());
    }
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyHist.get());
    if (toyAbsData == nullptr) {
      throw std::runtime_error("Could not cast toyHist to RooAbsData.");
    } else {
      toyAbsData->SetName(("toyAbsData_" + std::to_string(id)).c_str());
    }
    RooSimultaneous *simPdf = new RooSimultaneous(
        ("simPdf_" + std::to_string(id)).c_str(),
        ("simPdf_" + std::to_string(id)).c_str(), fittingMC);

    auto pdf = &PdfMC::Get(id);
    pdf->AddToSimultaneousPdf(*simPdf);
    std::unique_ptr<RooFitResult> toyResult = std::unique_ptr<RooFitResult>(
        simPdf->fitTo(*toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                      RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                      RooFit::Offset(true), RooFit::NumCPU(8, 2)));
    toyResult->Print("v");
    toyResult->SetName("ToyResult");
    TFile toyResultFile(
        (outputDir + "/results/Result2D_" + config.ReturnBoxString() + "_" +
         std::to_string(randomTag) + ".root")
            .c_str(),
        "recreate");
    toyResult->Write();
    mcResult->Write();
    TTree tree("tree", "");
    SaveEffToTree(config, toyResultFile, tree, *pdf, id);
    tree.Write();
    toyResultFile.Close();
    if (id == 1) {
      TH2F *hh_toy = (TH2F *)toy2D->createHistogram(
          "Bu_Delta_M,Delta_M", config.buDeltaMass().getBins(),
          config.deltaMass().getBins());
      hh_toy->SetTitle("");
      TCanvas canvasToy("CanvasToy", "", 1000, 800);
      hh_toy->SetStats(0);
      if (config.neutral() == Neutral::pi0) {
        hh_toy->GetYaxis()->SetTitle(
            "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
      }
      hh_toy->Draw("colz");
      canvasToy.Update();
      canvasToy.SaveAs((outputDir + "/2d_plots/2dToy_" +
                        EnumToString(config.neutral()) + ".pdf")
                           .c_str());
      std::string label = "toy";
      PlotComponent(Mass::buDelta, config.buDeltaMass(), toyData, *simPdf,
                    outputDir, config, fittingMC, label);
      PlotComponent(Mass::delta, config.deltaMass(), toyData, *simPdf,
                    outputDir, config, fittingMC, label);
    }
  }

  return 0;
}
