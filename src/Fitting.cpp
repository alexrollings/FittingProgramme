#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "RooHistPdf.h"
#include "RooMCStudy.h"
#include "RooNumIntConfig.h"
#include "RooPlot.h"
#include "RooRandom.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
// #include "TMathText.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TPaveLabel.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTree.h"
#include "TTreeReader.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Configuration.h"
#include "Fitting.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"
#include "ParseArguments.h"
#include "Pdf.h"

#include "Plotting.h"
#include "ToyFunctions.h"

// Function that returns the simultaneous PDF, the class which collects all the
// individual components. It is that that we do all our fitting with
std::pair<RooSimultaneous *, std::vector<PdfBase *> > MakeSimultaneousPdf(
    int const id, Configuration &config,
    std::vector<Daughters> const &daughtersVec,
    std::vector<Charge> const &chargeVec) {
  RooSimultaneous *simPdf = new RooSimultaneous(
      ("simPdf_" + std::to_string(id)).c_str(),
      ("simPdf_" + std::to_string(id)).c_str(), config.fitting);

  std::vector<PdfBase *> pdfs;
  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &c : chargeVec) {
    switch (config.neutral()) {
      case Neutral::gamma:
        switch (c) {
          case Charge::total:
            // Template instantiations are computationally expensive, so we
            // seperate them into different cpp files s.t. they can be compiled
            // in parallel
            AddPdfsGammaTotal(config, daughtersVec, id, pdfs);
            break;
          case Charge::plus:
            AddPdfsGammaPlus(config, daughtersVec, id, pdfs);
            break;
          case Charge::minus:
            AddPdfsGammaMinus(config, daughtersVec, id, pdfs);
            break;
        }
        break;
      case Neutral::pi0:
        switch (c) {
          case Charge::total:
            AddPdfsPi0Total(config, daughtersVec, id, pdfs);
            break;
          case Charge::plus:
            AddPdfsPi0Plus(config, daughtersVec, id, pdfs);
            break;
          case Charge::minus:
            AddPdfsPi0Minus(config, daughtersVec, id, pdfs);
            break;
        }
        break;
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(*simPdf);
  }

  auto p = std::make_pair(simPdf, pdfs);
  return p;
}

void MakeMapFittingDataSet(
    PdfBase &pdf, std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
    std::map<std::string, RooDataSet *> &mapFittingDataSet,
    Configuration &config) {
  Bachelor b = pdf.bachelor();
  Daughters d = pdf.daughters();
  Neutral n = pdf.neutral();
  Charge c = pdf.charge();

  RooDataSet *buDeltaDataSet = nullptr;
  buDeltaDataSet = dynamic_cast<RooDataSet *>(
      mapDataLabelDataSet[ComposeDataLabelName(n, b, d, c)]->reduce(
          ("Delta_M>" + std::to_string(config.deltaLow()) + "&&Delta_M<" +
           std::to_string(config.deltaHigh()))
              .c_str()));
  if (buDeltaDataSet == nullptr) {
    throw std::runtime_error("Could not reduce buDelta data with box cuts.");
  }
  if (mapFittingDataSet.find(ComposeFittingName(Mass::buDelta, n, b, d, c)) ==
      mapFittingDataSet.end()) {
    mapFittingDataSet.insert(std::make_pair(
        ComposeFittingName(Mass::buDelta, n, b, d, c), buDeltaDataSet));
    std::cout << "Created key-value pair for category " +
                     ComposeFittingName(Mass::buDelta, n, b, d, c) +
                     " and corresponding dataSet\n";
  } else {
    mapFittingDataSet[ComposeFittingName(Mass::buDelta, n, b, d, c)]->append(
        *buDeltaDataSet);
    std::cout << "Appended dataSet to category " +
                     ComposeFittingName(Mass::buDelta, n, b, d, c) + "\n";
  }
  if (config.fitBuPartial() == true) {
    RooDataSet *buDeltaPartialDataSet = nullptr;
    buDeltaPartialDataSet = dynamic_cast<RooDataSet *>(
        mapDataLabelDataSet[ComposeDataLabelName(n, b, d, c)]->reduce(
            ("Delta_M>" + std::to_string(config.deltaPartialLow()) +
             "&&Delta_M<" + std::to_string(config.deltaPartialHigh()))
                .c_str()));
    if (buDeltaPartialDataSet == nullptr) {
      throw std::runtime_error(
          "Could not reduce buDeltaPartial data with box cuts.");
    }
    if (mapFittingDataSet.find(ComposeFittingName(
            Mass::buDeltaPartial, n, b, d, c)) == mapFittingDataSet.end()) {
      mapFittingDataSet.insert(
          std::make_pair(ComposeFittingName(Mass::buDeltaPartial, n, b, d, c),
                         buDeltaPartialDataSet));
      std::cout << "Created key-value pair for category " +
                       ComposeFittingName(Mass::buDeltaPartial, n, b, d, c) +
                       " and corresponding dataSet\n";
    } else {
      mapFittingDataSet[ComposeFittingName(Mass::buDeltaPartial, n, b, d, c)]
          ->append(*buDeltaPartialDataSet);
      std::cout << "Appended dataSet to category " +
                       ComposeFittingName(Mass::buDeltaPartial, n, b, d, c) +
                       "\n";
    }
  }
  if (config.fit1D() == false) {
    RooDataSet *deltaDataSet = nullptr;
    deltaDataSet = dynamic_cast<RooDataSet *>(
        mapDataLabelDataSet[ComposeDataLabelName(n, b, d, c)]->reduce(
            ("Bu_Delta_M>" + std::to_string(config.buDeltaLow()) +
             "&&Bu_Delta_M<" + std::to_string(config.buDeltaHigh()))
                .c_str()));
    if (deltaDataSet == nullptr) {
      throw std::runtime_error("Could not reduce delta data with box cuts.");
    }
    if (mapFittingDataSet.find(ComposeFittingName(Mass::delta, n, b, d, c)) ==
        mapFittingDataSet.end()) {
      mapFittingDataSet.insert(std::make_pair(
          ComposeFittingName(Mass::delta, n, b, d, c), deltaDataSet));
      std::cout << "Created key-value pair for category " +
                       ComposeFittingName(Mass::delta, n, b, d, c) +
                       " and corresponding dataSet\n";
    } else {
      mapFittingDataSet[ComposeFittingName(Mass::delta, n, b, d, c)]->append(
          *deltaDataSet);
      std::cout << "Appended dataSet to category " +
                       ComposeFittingName(Mass::delta, n, b, d, c) + "\n";
    }
  }
}

// ExtractEnumList() allows user to parse multiple options separated by
// commas.
// Takes full options string as input and outputs a vector containing each
// specified option as an element

template <typename Enum>
std::vector<Enum> ExtractEnumList(std::string const &s, char delim = ',') {
  std::stringstream ss(s);
  std::vector<Enum> values;
  std::string substring;

  while (std::getline(ss, substring, delim)) {
    values.emplace_back(StringToEnum<Enum>(substring));
  }

  return values;
}

int main(int argc, char **argv) {
  std::string outputDir;
  std::vector<Year> yearVec;
  std::vector<Polarity> polarityVec;
  std::vector<Bachelor> bachelorVec;
  std::vector<Daughters> daughtersVec;
  std::vector<Charge> chargeVec;
  std::vector<Systematic> systematicVec;
  // Still want to load both charges:plus and minus, we just fit with
  // them differently

  int nToys = 0;
  int nSyst = 1;
  bool pdfD1D = false;
  bool pdf2D = false;
  bool data2D = false;
  bool data1D = false;
  Configuration &config = Configuration::Get();

  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  {  // calls destructor when object goes out of scope: Will tell you if
    // anything
    // was not used that was given as a command line argument before
    // continuing
    ParseArguments args(argc, argv);  // object instantiated

    std::string yearArg("2011,2012,2015,2016,2017,2018");
    std::string polarityArg("up,down");
    std::string bachelorArg("pi,k");
    std::string neutralArg("gamma");
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("total");
    std::string systematicArg("");
    std::string inputArg("");
    int toysArg = 0;
    int nSystArg = 0;
    int nCPUArg;
    float deltaLowArg = 0.0;
    float deltaHighArg = 0.0;
    float deltaPartialLowArg = 0.0;
    float deltaPartialHighArg = 0.0;
    float buDeltaLowArg = 0.0;
    float buDeltaHighArg = 0.0;

    // We always want to simultaneously fir the pi AND k bachelor modes
    // together
    bachelorVec = ExtractEnumList<Bachelor>(bachelorArg);

    if (args("help")) {
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "Type ./Fitting \n"
                << "-inputDir=<Input directory name (where roodatasets, efficiencies, mc fit results are stored)> \n"
                << "-outputDir=<output directory> \n";
      std::cout << "Give box dimensions:\n"
                << "    -dl=#, -dh=#, -bl=#, -bh=# (-dpl=#, -dph=# for gamma "
                   "mode)\n";
      std::cout << "Followed by the possible options (to specify multiple "
                   "options, separate them by commas):\n";
      std::cout << "    -1D, default fit is double 1D\n";
      std::cout << "    -noFit, default is to fit PDF to data\n";
      std::cout << "    -simple, to plot all mis-reconstructed components as "
                   "one color\n";
      std::cout << "    -unblind\n";
      std::cout << "    -year=<choice {2011,2012,2015,2016,2017,2018} default: "
                << yearArg << ">\n";
      std::cout << "    -polarity=<choice {up,down} default: " << polarityArg
                << ">\n";
      // std::cout << "    -bachelor choice {k,pi} default: " << bachelorArg
      // <<
      // "\n";
      std::cout << "    -neutral=<choice {pi0/gamma} default: " << neutralArg
                << ">\n";
      std::cout << "    -daughters=<choice {kpi,kk,pipi,pik} default: "
                << daughtersArg << ">\n";
      std::cout << "    -charge=<choice {plus,minus/total} default: "
                << chargeArg << ">\n";
      std::cout << "    -toys=<# toys>"
                << "\n";
      std::cout << "    -pdfD1D, to run D1D toys generated from D1D PDF\n"
                << "    -pdf2D, to run 2D toys generated from 2D PDF\n"
                << "    -data2D, to run 2D toys generated from RooHistPdf of "
                   "data\n"
                << "    -data1D, to run independent 1D toys generated from "
                   "RooHistPdf of "
                   "data.\n";
      std::cout << "    -systematic=<choice, default: None>"
                << "\n";
      std::cout << "    -nSyst=<# data fits to run for systematic studies>"
                << "\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";

      return 1;
    } else {
      if (!args("toys", toysArg)) {
        std::cout << "Running data fit.\n";
      } else {
        nToys = toysArg;
        config.runToy() = true;
        std::cout << "Running " << nToys << " toys\n";
        if (args("pdfD1D")) {
          pdfD1D = true;
          std::cout << "Toys generated from D1D PDF.\n";
        } else if (args("pdf2D")) {
          pdf2D = true;
          std::cout << "Toys generated from 2D PDF.\n";
        } else if (args("data2D")) {
          data2D = true;
          std::cout << "Toys generated from 2D data.\n";
        } else if (args("data1D")) {
          data1D = true;
          std::cout << "Toys generated from independent 1D data.\n";
        } else {
          std::cerr << "Must specify type of toy to run: pdfD1D, pdf2D, "
                       "data2D, data1D\n";
          return 1;
        }
      }

      if (!args("inputDir", inputArg)) {
        std::cerr << "Input directory must be specified (-inputDir=<path>).\n";
        return 1;
      } else {
        config.inputDir = inputArg;
      }

      if (!args("outputDir", outputDir)) {
        std::cerr << "Specify output directory (-outputDir=<path>).\n";
        return 1;
      }
      if (args("1D")) {
        std::cout << "Running 1D fit.\n";
        config.fit1D() = true;
      }
      if (args("unblind")) {
        std::cout << "Unblinding.\n";
        config.blindFit() = false;
      }
      if (args("noFit")) {
        std::cout << "Will not fit PDF to data, just plot both.\n";
        config.noFit() = true;
      }
      if (args("simple")) {
        std::cout << "Plotting all mis-reconstructed PDFs as one colour.\n";
        config.simpleFit() = true;
      }
      if (args("nCPU", nCPUArg)) {
        std::cout << "Setting nCPU to " << nCPUArg << "\n";
        config.nCPU_ = nCPUArg;
      }
      // Year
      // args matches "year" to string given in command line and assigns
      // option
      // parsed to year
      if (!args("year", yearArg)) {
        std::cout << "Using default value -year=" << yearArg << ".\n";
      }
      try {
        yearVec = ExtractEnumList<Year>(yearArg);
      } catch (std::invalid_argument) {
        std::cerr << "year assignment failed, please specify: "
                     "-year=2011,2012,2015,2016.\n";
        return 1;
      }

      // Polarity
      if (!args("polarity", polarityArg)) {
        std::cout << "Using default value -polarity=" << polarityArg << ".\n";
      }
      try {
        polarityVec = ExtractEnumList<Polarity>(polarityArg);
      } catch (std::invalid_argument) {
        std::cerr << "Polarity assignment failed, please specify: "
                     "-polarity=up,down.\n";
        return 1;
      }

      // Neutral
      if (!args("neutral", neutralArg)) {
        std::cerr << "Using default value -neutral=" << neutralArg << "\n";
      }
      try {
        config.SetNeutral(StringToEnum<Neutral>(neutralArg));
      } catch (std::invalid_argument) {
        std::cerr << "neutral assignment failed, please specify: "
                     "-neutral=pi0/gamma.\n";
        return 1;
      }

      if (!args("daughters", daughtersArg)) {
        std::cout << "Using default value -daughters=" << daughtersArg << ".\n";
      }
      try {
        daughtersVec = ExtractEnumList<Daughters>(daughtersArg);
      } catch (std::invalid_argument) {
        std::cerr << "daughters assignment failed, please specify: "
                     "-daughters=kpi,kk,pipi,pik.\n";
        return 1;
      }
      for (auto &d : daughtersVec) {
        if (d == Daughters::pik) {
          config.runADS() = true;
          std::cout << "Running ADS mode fit\n";
        }
      }

      if (!args("charge", chargeArg)) {
        std::cout << "Using default value -charge=" << chargeArg << ".\n";
      }
      try {
        chargeVec = ExtractEnumList<Charge>(chargeArg);
        std::cout << "Using value -charge=" << chargeArg << ".\n";
      } catch (std::invalid_argument) {
        std::cerr << "charge assignment failed, please specify: "
                     "-charge=plus,minus or -charge=total.\n";
        return 1;
      }
      if (chargeVec.size() > 1) {
        config.splitByCharge() = true;
      }
      if (!args("systematic", systematicArg)) {
        std::cout << "NOT running systematics.\n";
      } else {
        std::cout << "Running systematics.\n";
        config.runSystematics() = true;
        config.nCPU_ = 1;
        try {
          systematicVec = ExtractEnumList<Systematic>(systematicArg);
        } catch (std::invalid_argument) {
          std::cerr << "systematic assignment failed, please specify.\n";
          return 1;
        }
        if (!args("nSyst", nSystArg)) {
          std::cout << "Running 1 systematic fit.\n";
        } else {
          nSyst = nSystArg;
          std::cout << "Running " << nSyst << " systematic fits.\n";
        }
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
      if (config.neutral() == Neutral::gamma) {
        if (!args("dpl", deltaPartialLowArg)) {
          std::cout << "Only fitting Bu mass for gamma delta mass window.\n";
        } else {
          config.SetDeltaPartialLow(deltaPartialLowArg);
          config.fitBuPartial() = true;
          std::cout << "Set value for lower deltaPartial mass box threshold: " +
                           std::to_string(config.deltaPartialLow()) + "\n";
          if (!args("dph", deltaPartialHighArg)) {
            std::cout << "Only fitting Bu mass for gamma delta mass window.\n";
          } else {
            config.SetDeltaPartialHigh(deltaPartialHighArg);
            config.fitBuPartial() = true;
            std::cout
                << "Set value for upper deltaPartial mass box threshold: " +
                       std::to_string(config.deltaPartialHigh()) + "\n";
          }
        }
      }
    }
  }

  if (chargeVec.size() > 1 && daughtersVec.size() > 1 &&
       config.blindFit() == false && config.noFit() == false) {
    std::cerr << "\n\n !!!!!! Cannot run unblinded split by charge fit for "
                 "signal modes "
                 "!!!!!! \n\n";
    return 1;
  }

  // Raise lower mass boundary in delta mass for pi0 plots
  if (config.neutral() == Neutral::pi0) {
    config.buDeltaMass().setMax(5450);
    config.buDeltaMass().setBins(40);
    config.deltaMass().setMin(136);
    config.deltaMass().setBins(54);
    config.deltaMass().SetTitle("m(D^{*0}) - m(D^{0}) - m(#pi^{0}) + m(#pi^{0})_{PDG}");
  }

  // Define categories AFTER neutral and SplitByCharge have been set in
  // Configuration
  config.DefineCategories();

  // Declare simPDF and result before any if statements so that it can be
  // passed to RunToysD1DPdf no matter what
  std::unique_ptr<RooSimultaneous> simPdf;
  std::vector<PdfBase *> pdfs;
  std::unique_ptr<RooFitResult> dataFitResult;

  // if (inputDir != "") {
  std::map<std::string, RooDataSet *> mapDataLabelDataSet;

  // Add up lumi in order to convert into string to go on plots
  // double lumi = 0;
  // double lumiErr = 0;

  // Loop over all options in
  // order to extract correct roodataSets.
  for (auto &y : yearVec) {
    std::string dPidCut;
    if (y == Year::y2011 or y == Year::y2012) {
      dPidCut = "2";
    } else {
      dPidCut = "1";
    }
    // if (y == Year::y2011) {
    //   lumi += 0.98;
    //   lumiErr += 0.02;
    // } else if (y == Year::y2012) {
    //   lumi += 1.99;
    //   lumiErr += 0.02;
    // } else if (y == Year::y2015) {
    //   lumi += 0.28;
    //   lumiErr += 0.01;
    // } else if (y == Year::y2016) {
    //   lumi += 1.65;
    // } else if (y == Year::y2017) {
    //   lumi += 1.7;
    // } else if (y == Year::y2018) {
    //   lumi += 2.19;
    // }
    for (auto &p : polarityVec) {
      for (auto &b : bachelorVec) {
        for (auto &d : daughtersVec) {
          for (auto &c : chargeVec) {
            std::string dsFile =
                config.inputDir + "/roodatasets/" +
                ComposeFilename(y, p, b, config.neutral(), d, c) + ".root";
            std::cout << "Extracting RooDataSet from file: \n";

            if (!fexists(dsFile)) {
              std::cerr << dsFile << " does not exist.\n";
              return 1;
            } else {
              std::cout << dsFile << " exists.\n";
              TFile in(dsFile.c_str(), "READ");
              RooDataSet *inputDataSet;
              gDirectory->GetObject("inputDataSet", inputDataSet);
              if (inputDataSet == nullptr) {
                throw std::runtime_error("Data set does not exist.\n");
              } else {
                std::cout << "inputDataSet extracted: \n";
                inputDataSet->Print();
                RooDataSet *reducedInputDataSet_n =
                    dynamic_cast<RooDataSet *>(inputDataSet->reduce(
                        config.ReturnCutString().c_str()));
                if (reducedInputDataSet_n == nullptr) {
                  throw std::runtime_error(
                      "Could not reduce input w/ neutral cuts dataSet.\n");
                }
                RooDataSet *reducedInputDataSet_b = nullptr;
                if (b == Bachelor::pi) {
                  reducedInputDataSet_b = dynamic_cast<RooDataSet *>(
                      reducedInputDataSet_n->reduce("bach_PIDK<12"));
                } else {
                  reducedInputDataSet_b = dynamic_cast<RooDataSet *>(
                      reducedInputDataSet_n->reduce("bach_PIDK>12"));
                }
                if (reducedInputDataSet_b == nullptr) {
                  throw std::runtime_error(
                      "Could not reduce input dataSet w/ bachelor cuts.\n");
                }
                RooDataSet *reducedInputDataSet_d = nullptr;
                if (d == Daughters::kpi || d == Daughters::pik) {
                  reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                      reducedInputDataSet_b->reduce(
                          config.fittingArgSet(),
                          ("((abs(h1_D_ID)==211&&h1_D_PIDK<-" + dPidCut +
                           ")&&(abs(h2_D_ID)=="
                           "321&&h2_D_PIDK>" +
                           dPidCut +
                           "))||((abs(h1_D_ID)"
                           "==321&&h1_D_PIDK>" +
                           dPidCut +
                           ")&&(abs(h2_D_ID)==211&&h2_D_"
                           "PIDK<-" +
                           dPidCut + "))")
                              .c_str()));
                } else if (d == Daughters::kk) {
                  reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                      reducedInputDataSet_b->reduce(
                          config.fittingArgSet(),
                          ("h1_D_PIDK>" + dPidCut + "&&h2_D_PIDK>" + dPidCut)
                              .c_str()));
                } else {
                  reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                      reducedInputDataSet_b->reduce(
                          config.fittingArgSet(), ("h1_D_PIDK<-" + dPidCut +
                                                   "&&h2_D_PIDK<-" + dPidCut)
                                                      .c_str()));
                }
                if (reducedInputDataSet_d == nullptr) {
                  throw std::runtime_error(
                      "Could not reduce input dataSet w/ daughter cuts.\n");
                }
                // Need to append each year, polarity to dataSet at each key
                // in map, as key labelled by config.neutral(), b, d, c and
                // must be unique.
                if (mapDataLabelDataSet.find(
                        ComposeDataLabelName(config.neutral(), b, d, c)) ==
                    mapDataLabelDataSet.end()) {
                  mapDataLabelDataSet.insert(std::make_pair(
                      ComposeDataLabelName(config.neutral(), b, d, c),
                      reducedInputDataSet_d));
                  std::cout
                      << "Created key-value pair for category " +
                             ComposeDataLabelName(config.neutral(), b, d, c) +
                             " and corresponding dataSet\n";
                } else {
                  mapDataLabelDataSet[ComposeDataLabelName(config.neutral(),
                                                           b, d, c)]
                      ->append(*reducedInputDataSet_d);
                  std::cout
                      << "Appended dataSet to category " +
                             ComposeDataLabelName(config.neutral(), b, d, c) +
                             "\n";
                }
              }
            }
          }
        }
      }
    }
  }

  // id = 0 for data fit
  int id = 0;
  auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
  simPdf = std::unique_ptr<RooSimultaneous>(p.first);
  pdfs = p.second;
  // Apply box cuts and split PDF into mass categories too
  std::map<std::string, RooDataSet *> mapFittingDataSet;
  RooArgSet asymArgSet;
  for (auto &p : pdfs) {
    MakeMapFittingDataSet(*p, mapDataLabelDataSet, mapFittingDataSet, config);
    asymArgSet.add(p->R_piK_Bu2Dst0h_D0pi0());
    if (config.neutral() == Neutral::gamma) {
      asymArgSet.add(p->R_piK_Bu2Dst0h_D0gamma());
    }
  }

  RooDataSet fullDataSet("fullDataSet", "fullDataSet", config.fittingArgSet(),
                         RooFit::Index(config.fitting),
                         RooFit::Import(mapFittingDataSet));

  auto fullDataHist = std::unique_ptr<RooDataHist>(
      fullDataSet.binnedClone("fullDataHist", "fullDataHist"));
  if (fullDataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }
  auto fullAbsData = dynamic_cast<RooAbsData *>(fullDataHist.get());
  if (fullAbsData == nullptr) {
    throw std::runtime_error("Could not cast to RooAbsData.");
  }

  if (config.noFit() == false && config.runSystematics() == false) {
    // Strategy(2) requires evaluation of hessian at every step: can set
    // strategy 0 then call MINOS after to calculate correct errors
    dataFitResult = std::unique_ptr<RooFitResult>(simPdf->fitTo(
        *fullAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
        // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
        // RooFit::Minos(kTRUE)));
        RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
    // if (config.neutral() == Neutral::pi0) {
    //   dataFitResult = std::unique_ptr<RooFitResult>(simPdf->fitTo(
    //       *fullAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
    //       RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
    //       RooFit::Offset(true), RooFit::NumCPU(config.nCPU()),
    //       RooFit::ExternalConstraints(
    //           NeutralVars<Neutral::pi0>::Get(id).constraints_argSet())));
    // } else {
    //   dataFitResult = std::unique_ptr<RooFitResult>(simPdf->fitTo(
    //       *fullAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
    //       RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
    //       RooFit::Offset(true), RooFit::NumCPU(config.nCPU()),
    //       RooFit::ExternalConstraints(
    //           NeutralVars<Neutral::gamma>::Get(id).constraints_argSet())));
    // }
    dataFitResult->SetName("DataFitResult");
  }

  // Have to shift params after creating simPdf
  if (config.runSystematics() == true) {
    std::string systString;
    for (unsigned int i = 0; i < systematicVec.size(); ++i) {
      systString += EnumToString(systematicVec[i]);
      if (i < systematicVec.size() - 1) {
        systString += "_";
      }
    }
    std::string paramFile =
        outputDir + "/results/ParameterInfo_" + systString + ".csv";
    Params::Get().WriteFixedParametersToFile(paramFile, systematicVec);
    for (int s = 1; s < nSyst + 1; ++s) {
      std::cout << "Running systematic " << s << "...\n";
      auto systPair = MakeSimultaneousPdf(s, config, daughtersVec, chargeVec);
      std::cout << "RandomiseParameters:\n";
      std::random_device rd;
      std::default_random_engine rng(rd());
      std::uniform_int_distribution<UInt_t> dist;
      UInt_t seed = dist(rng);
      // UInt_t seed = 0xe5936d8c;
      RooRandom::randomGenerator()->SetSeed(seed);
      TRandom3 random(seed);
      Params::Get().RandomiseParameters(systematicVec.begin(),
                                        systematicVec.end(), random);
      auto systPdf = std::unique_ptr<RooSimultaneous>(systPair.first);
      // auto pdfs = systPair.second;
      auto systResult = std::unique_ptr<RooFitResult>(systPdf->fitTo(
          *fullAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(1), RooFit::Minimizer("Minuit2"),
          RooFit::Offset(true), RooFit::NumCPU(config.nCPU())));
      systResult->SetName("SystResult");
      std::stringstream filename;
      filename << outputDir << "/results/SystResult_"
               << config.ReturnBoxString() << "_" << systString << "_"
               << std::hex << seed << ".root";
      TFile systResultFile(filename.str().c_str(), "recreate");
      systResult->Write();
      systResult->Print("v");
      systResultFile.Close();
    }
  }

  if (config.runToy() == true) {
    // start at id = 1 to reserve 0 for data fit
    for (int id = 1; id < nToys + 1; ++id) {
      std::random_device rd;
      std::default_random_engine rng(rd());
      std::uniform_int_distribution<UInt_t> dist;
      UInt_t seed = dist(rng);
      // UInt_t seed = 0x422d71a;
      RooRandom::randomGenerator()->SetSeed(seed);
      std::stringstream filename;
      if (config.runToy() == true && pdfD1D == true) {
        filename << outputDir << "/results/ResultD1D_"
                 << config.ReturnBoxString() << "_" << std::hex << seed
                 << ".root";
      } else {
        filename << outputDir << "/results/Result2D_"
                 << config.ReturnBoxString() << "_" << std::hex << seed
                 << ".root";
      }
      TFile toyResultFile(filename.str().c_str(), "recreate");
      if (config.runToy() == true && pdfD1D == true) {
        RunToysD1DPdf(simPdf, toyResultFile, config, dataFitResult,
                      daughtersVec, chargeVec, outputDir, id);
      } else if (data2D == true) {
        RunToys2DData(toyResultFile, dataFitResult, mapDataLabelDataSet,
                      config, daughtersVec, chargeVec, outputDir, id);
      } else if (data1D == true) {
        RunToys1DData(toyResultFile, dataFitResult, mapDataLabelDataSet,
                      config, daughtersVec, chargeVec, outputDir, id);
      } else {
        RunToys2DPdf(pdfs, mapDataLabelDataSet, simPdf, toyResultFile,
                     dataFitResult, config, outputDir, daughtersVec,
                     chargeVec, id);
      }
      toyResultFile.Close();
    }
    //   dataFitResult->Print();
  } else {
    // Loop over daughters again to plot correct PDFs

    // Whilst blinding is in place, we need to store y-axis max for FAV
    // mode, to set y-axis max in ADS mode
    std::map<Neutral, std::map<Mass, double> > yMaxMap;
    // LaTeXYields(config, pdfs, outputDir, dataFitResult);
    if (config.runSystematics() == false) {
      if (config.noFit() == false) {
        dataFitResult->Print("v");
      }
      std::map<std::string, Int_t> colorMap = MakeColorMap(config);
      PlotLegend(config, colorMap, outputDir);
      for (auto &p : pdfs) {
        Plotting1D(id, *p, config, fullDataSet, *simPdf, colorMap, outputDir,
                   dataFitResult.get(), yMaxMap);
      }
      if (config.noFit() == false) {
        dataFitResult->Print("v");
        // for (auto &p : pdfs) {
        //   if (p->daughters() == Daughters::kpi) {
        //     if (config.neutral() == Neutral::pi0) {
        //       std::cout << p->N_trueId_Bu2Dst0h_D0pi0().GetName() << " = "
        //                 << p->N_trueId_Bu2Dst0h_D0pi0().getVal() << "\n";
        //       std::cout << p->N_trueId_Bu2Dst0h_WN().GetName() << " = "
        //                 << p->N_trueId_Bu2Dst0h_WN().getVal() << "\n";
        //     } else {
        //       std::cout << p->N_trueId_Bu2Dst0h_D0pi0().GetName() << " = "
        //                 << p->N_trueId_Bu2Dst0h_D0pi0().getVal() << "\n";
        //       std::cout << p->N_trueId_Bu2Dst0h_D0pi0_WN().GetName() << " =
        //       "
        //                 << p->N_trueId_Bu2Dst0h_D0pi0_WN().getVal() <<
        //                 "\n";
        //       std::cout << p->N_trueId_Bu2Dst0h_D0gamma().GetName() << " =
        //       "
        //                 << p->N_trueId_Bu2Dst0h_D0gamma().getVal() << "\n";
        //       std::cout << p->N_trueId_Bu2Dst0h_D0gamma_WN().GetName() << "
        //       = "
        //                 << p->N_trueId_Bu2Dst0h_D0gamma_WN().getVal() <<
        //                 "\n";
        //     }
        //   }
        // std::cout << p->N_trueId_Bu2Dst0h_D0pi0().GetName() << " = "
        //           << p->N_trueId_Bu2Dst0h_D0pi0().getVal() << "\n";
        // std::cout << p->N_misId_Bu2Dst0h_D0pi0().GetName() << " = "
        //           << p->N_misId_Bu2Dst0h_D0pi0().getVal() << "\n";
        // std::cout << p->N_tot_Bu2Dst0h_D0gamma().GetName() << " = "
        //           << p->N_tot_Bu2Dst0h_D0gamma().getVal() << "\n";
        // std::cout << p->N_trueId_Bu2Dst0h_D0gamma().GetName() << " = "
        //           << p->N_trueId_Bu2Dst0h_D0gamma().getVal() << "\n";
        // std::cout << p->N_misId_Bu2Dst0h_D0gamma().GetName() << " = "
        //           << p->N_misId_Bu2Dst0h_D0gamma().getVal() << "\n";
        //   std::cout << p->N_tot_Bu2D0hst().GetName() << " = "
        //             << p->N_tot_Bu2D0hst().getVal() << "\n";
        // if (p->daughters() == Daughters::pik) {
        //   std::cout << p->N_tot_Bu2Dst0h_D0pi0_D02pik().GetName() << " = "
        //             << p->N_tot_Bu2Dst0h_D0pi0_D02pik().getVal() << "\n";
        //   std::cout << p->N_tot_Bu2Dst0h_D0pi0_WN_D02pik().GetName() << " =
        //   "
        //             << p->N_tot_Bu2Dst0h_D0pi0_WN_D02pik().getVal() <<
        //             "\n";
        //   if (p->neutral() == Neutral::gamma) {
        //     std::cout << p->N_tot_Bu2Dst0h_D0gamma_D02pik().GetName() << "
        //     = "
        //               << p->N_tot_Bu2Dst0h_D0gamma_D02pik().getVal() <<
        //               "\n";
        //     std::cout << p->N_tot_Bu2Dst0h_D0gamma_WN_D02pik().GetName()
        //               << " = "
        //               << p->N_tot_Bu2Dst0h_D0gamma_WN_D02pik().getVal()
        //               << "\n";
        //   }
        // }
        // }
        // NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(id)
        //     .Bu2Dst0hst_fracD0pi0_Bu().Print();
        // NeutralBachelorVars<Neutral::gamma, Bachelor::k>::Get(id)
        //     .Bu2Dst0hst_fracD0pi0_Bu().Print();
        PlotCorrelations(dataFitResult.get(), outputDir, config);
        // Save RFR of data and efficiencies to calculate observables with
        // corrected errors
        TFile outputFile((outputDir + "/results/DataResult_" +
                          config.ReturnBoxString() + ".root")
                             .c_str(),
                         "recreate");
        dataFitResult->Write();
        TTree tree("tree", "");
        if (config.neutral() == Neutral::pi0 ||
            config.fitBuPartial() == true) {
          SaveEffToTree(config, outputFile, tree, Mode::Bu2Dst0pi_D0pi0);
        }
        if (config.neutral() == Neutral::gamma) {
          SaveEffToTree(config, outputFile, tree, Mode::Bu2Dst0pi_D0gamma);
          double N_tot_Bu2Dst0pi_D0pi0_D02kpi_val =
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kpi>::Get(id)
                  .N_tot_Bu2Dst0h_D0pi0().getVal();
          double N_tot_Bu2Dst0pi_D0pi0_D02kpi_err =
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kpi>::Get(id)
                  .N_tot_Bu2Dst0h_D0pi0()
                  .getPropagatedError(*dataFitResult);
          std::cout << N_tot_Bu2Dst0pi_D0pi0_D02kpi_val
                    << " " << N_tot_Bu2Dst0pi_D0pi0_D02kpi_err << "\n";
          tree.Branch("N_tot_Bu2Dst0pi_D0pi0_D02kpi_val",
                      &N_tot_Bu2Dst0pi_D0pi0_D02kpi_val,
                      "N_tot_Bu2Dst0pi_D0pi0_D02kpi_val/D");
          tree.Branch("N_tot_Bu2Dst0pi_D0pi0_D02kpi_err",
                      &N_tot_Bu2Dst0pi_D0pi0_D02kpi_err,
                      "N_tot_Bu2Dst0pi_D0pi0_D02kpi_err/D");
          tree.Fill();
        }
        outputFile.cd();
        tree.Write();
      }
    }
  }
  // } else {
  //   if (config.runToy() == false) {
  //     throw std::runtime_error("Must specify input directory to run data fit.");
  //     return 1;
  //   }
  //   std::cout << "Fitting using D1D method, starting from model PDF\n";
  //   ToyTestD1D(simPdf, dataFitResult, config, daughtersVec, chargeVec,
  //              outputDir, nToys);
  // }
  return 0;
}
