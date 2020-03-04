#include <fstream>
#include <iostream>

#include "Configuration.h"
#include "NeutralVars.h"
#include "NeutralBachelorVars.h"
#include "ParseArguments.h"

#include "TTreeReader.h"
#include "TFile.h"
#include "RooDataSet.h"
#include "RooSimultaneous.h"
#include "RooFitResult.h"

// Check file exists
bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

RooDataSet ExtractDataSetFromMC(Configuration &config,
                                std::string const &inputDir,
                                RooCategory &fittingMC) {
  RooDataSet *inputDataSet = nullptr;
  std::string input =
      inputDir + "/" + EnumToString(config.neutral()) + "_dataset.root";

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

  auto dataBu_tmp = std::unique_ptr<RooDataSet>(
      dynamic_cast<RooDataSet *>(inputDataSet->reduce(
          (cutString + "&&Delta_M>" + std::to_string(config.deltaLow()) +
           "&&Delta_M<" + std::to_string(config.deltaHigh()))
              .c_str())));
  if (dataBu_tmp.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet with delta mass.");
  }
  auto dataBu = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
      dataBu_tmp->reduce(RooArgSet(config.buDeltaMass()))));
  if (dataBu.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet to BuDelta mass.");
  }

  auto dataDelta_tmp = std::unique_ptr<RooDataSet>(
      dynamic_cast<RooDataSet *>(inputDataSet->reduce(
          (cutString + "&&Bu_Delta_M>" + std::to_string(config.buDeltaLow()) +
           "&&Bu_Delta_M<" + std::to_string(config.buDeltaHigh()))
              .c_str())));
  if (dataDelta_tmp.get() == nullptr) {
    throw std::runtime_error(
        "Could not reduce inputDataSet with buDelta mass.");
  }
  auto dataDelta = std::unique_ptr<RooDataSet>(dynamic_cast<RooDataSet *>(
      dataDelta_tmp->reduce(RooArgSet(config.deltaMass()))));
  if (dataDelta.get() == nullptr) {
    throw std::runtime_error("Could not reduce inputDataSet to Delta mass.");
  }

  RooDataSet combData(
      "combData", "", RooArgSet(config.fittingArgSet()),
      RooFit::Index(fittingMC),
      RooFit::Import(EnumToString(Mass::buDelta).c_str(), *dataBu.get()),
      RooFit::Import(EnumToString(Mass::delta).c_str(), *dataDelta.get()));
  return combData;
}

RooSimultaneous* MakePdf(int const id, Configuration &config, RooCategory &fittingMC, RooDataSet &combData) {

  std::cout << "Making simPdf...\n";

  NeutralVars<Neutral::gamma> nVars(id);
  NeutralBachelorVars<Neutral::gamma, Bachelor::pi> nbVars(id);

  RooRealVar boxEff(("boxEff_" + std::to_string(id)).c_str(),
                    "", 1);
  RooRealVar orEff(("orEff_" + std::to_string(id)).c_str(),
                   "", 1);
  RooRealVar buDeltaCutEff(
      ("buDeltaCutEff_" + std::to_string(id)).c_str(), "", 1);
  RooRealVar deltaCutEff(
      ("deltaCutEff_" + std::to_string(id)).c_str(), "", 1);
  config.SetEfficiencies(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi, orEff, boxEff,
                         buDeltaCutEff, deltaCutEff, false);

  RooRealVar yieldSignal(("yieldSignal" + std::to_string(id)).c_str(), "",
                                14000, 0, 15000);

  RooFormulaVar yieldBuDeltaSignal(
      ("yieldBuDeltaSignal" + std::to_string(id)).c_str(), "", "(@0/@1)*@2",
      RooArgList(deltaCutEff, orEff, yieldSignal));
  RooAddPdf pdfBuDelta("pdfBuDelta", "", nbVars.pdfBu_Bu2Dst0h_D0gamma(),
                       yieldBuDeltaSignal);

  RooFormulaVar yieldDeltaSignal(
      ("yieldDeltaSignal" + std::to_string(id)).c_str(), "", "(@0/@1)*@2",
      RooArgList(buDeltaCutEff, orEff, yieldSignal));
  RooAddPdf pdfDelta("pdfDelta", "", nVars.pdfDelta_Bu2Dst0h_D0gamma(),
                     yieldDeltaSignal);

  RooSimultaneous* simPdf = new RooSimultaneous(("simPdf_" + std::to_string(id)).c_str(), "", fittingMC);
  simPdf->addPdf(pdfBuDelta, EnumToString(Mass::buDelta).c_str());
  simPdf->addPdf(pdfDelta, EnumToString(Mass::delta).c_str());

  std::cout << "Fit simPdf to MC...\n";
  std::unique_ptr<RooFitResult> result =
      std::unique_ptr<RooFitResult>(simPdf->fitTo(
          combData, RooFit::Extended(kTRUE), RooFit::Save(),
                        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                        RooFit::Offset(true), RooFit::NumCPU(8, 2)));
  result->Print();

  return simPdf;
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
  if (config.neutral() == Neutral::pi0) {
    config.deltaMass().setMin(136);
    config.deltaMass().setBins(54);
  }

  std::cout << "Neutral = " << EnumToString(config.neutral()) << "\n";

  // ---------------------------- Categories ----------------------------
  RooCategory fittingMC("fittingMC", "fittingMC");
  fittingMC.defineType(EnumToString(Mass::buDelta).c_str());
  fittingMC.defineType(EnumToString(Mass::delta).c_str());

  // ---------------------------- Make MC dataset 
  // ----------------------------
  RooDataSet combData = ExtractDataSetFromMC(config, inputDir, fittingMC);
  std::cout << "Returned combined dataset\n";

  int const id = 0;
  RooSimultaneous* simPdf = MakePdf(id, config, fittingMC, combData);
  std::cout << "Returned simPdf\n";


  return 0;
}
