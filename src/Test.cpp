#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "RooMCStudy.h"
#include "RooNumIntConfig.h"
#include "RooPlot.h"
#include "RooRandom.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TLine.h"
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
#include "GlobalVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "ParseArguments.h"
#include "Pdf.h"

// Function to set the style for all THists
void SetStyle() {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.06, "Z");
  gStyle->SetTitleSize(0.03, "XY");
  gStyle->SetLabelSize(0.024, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetLegendTextSize(0.03);
  gStyle->SetTitleOffset(0.9, "X");
  gStyle->SetTitleOffset(1.1, "Y");
  gStyle->SetTitleOffset(0.9, "Z");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.09);
  gStyle->SetPadLeftMargin(0.1);
}


// Function that returns the simultaneous PDF, the class which collects all the
// individual components. It is that that we do all our fitting with
std::pair<RooSimultaneous *, std::vector<PdfBase *> > MakeSimultaneousPdf(
    int const id, Configuration &config, Configuration::Categories &categories,
    std::vector<Neutral> const &neutralVec,
    std::vector<Daughters> const &daughtersVec,
    std::vector<Charge> const &chargeVec) {
  RooSimultaneous *simPdf = new RooSimultaneous(
      ("simPdf_" + std::to_string(id)).c_str(),
      ("simPdf_" + std::to_string(id)).c_str(), categories.fitting);

  std::vector<PdfBase *> pdfs;
  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &n : neutralVec) {
    for (auto &c : chargeVec) {
      switch (n) {
        case Neutral::gamma:
          switch (c) {
            case Charge::total:
              pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                     Daughters::kpi, Charge::total>::Get(id));
              pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                     Daughters::kpi, Charge::total>::Get(id));
              Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                  Charge::total>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                  Charge::total>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                  Charge::total>::Get(id)
                  .CreateBuAddPdf();
              Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                  Charge::total>::Get(id)
                  .CreateBuAddPdf();
              if (Configuration::Get().fit1D() == false) {
                Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                    Charge::total>::Get(id)
                    .CreateDeltaAddPdf();
                Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                    Charge::total>::Get(id)
                    .CreateDeltaAddPdf();
              }
              break;
            case Charge::plus:
              pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                     Daughters::kpi, Charge::plus>::Get(id));
              pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                     Daughters::kpi, Charge::plus>::Get(id));
              Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                  Charge::plus>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                  Charge::plus>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                  Charge::plus>::Get(id)
                  .CreateBuAddPdf();
              Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                  Charge::plus>::Get(id)
                  .CreateBuAddPdf();
              if (Configuration::Get().fit1D() == false) {
                Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                    Charge::plus>::Get(id)
                    .CreateDeltaAddPdf();
                Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                    Charge::plus>::Get(id)
                    .CreateDeltaAddPdf();
              }
              break;
            case Charge::minus:
              pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi,
                                     Daughters::kpi, Charge::minus>::Get(id));
              pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k,
                                     Daughters::kpi, Charge::minus>::Get(id));
              Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .CreateBuAddPdf();
              Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .CreateBuAddPdf();
              if (Configuration::Get().fit1D() == false) {
                Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                    Charge::minus>::Get(id)
                    .CreateDeltaAddPdf();
                Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                    Charge::minus>::Get(id)
                    .CreateDeltaAddPdf();
              }
              break;
          }
          break;
        case Neutral::pi0:
          switch (c) {
            case Charge::total:
              pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                     Charge::total>::Get(id));
              pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                     Charge::total>::Get(id));
              Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                  Charge::total>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                  Charge::total>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                  Charge::total>::Get(id)
                  .CreateBuAddPdf();
              Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                  Charge::total>::Get(id)
                  .CreateBuAddPdf();
              if (Configuration::Get().fit1D() == false) {
                Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                    Charge::total>::Get(id)
                    .CreateDeltaAddPdf();
                Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                    Charge::total>::Get(id)
                    .CreateDeltaAddPdf();
              }
              break;
            case Charge::plus:
              pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                     Charge::plus>::Get(id));
              pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                     Charge::plus>::Get(id));
              Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                  Charge::plus>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::plus>::Get(
                  id)
                  .AssignMisIdYields();
              Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                  Charge::plus>::Get(id)
                  .CreateBuAddPdf();
              Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::plus>::Get(
                  id)
                  .CreateBuAddPdf();
              if (Configuration::Get().fit1D() == false) {
                Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                    Charge::plus>::Get(id)
                    .CreateDeltaAddPdf();
                Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                    Charge::plus>::Get(id)
                    .CreateDeltaAddPdf();
              }
              break;
            case Charge::minus:
              pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                     Charge::minus>::Get(id));
              pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                                     Charge::minus>::Get(id));
              Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .AssignMisIdYields();
              Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .CreateBuAddPdf();
              Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                  Charge::minus>::Get(id)
                  .CreateBuAddPdf();
              if (Configuration::Get().fit1D() == false) {
                Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                    Charge::minus>::Get(id)
                    .CreateDeltaAddPdf();
                Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi,
                    Charge::minus>::Get(id)
                    .CreateDeltaAddPdf();
              }
              break;
          }
          break;
      }
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(*simPdf);
  }

  auto p = std::make_pair(simPdf, pdfs);
  return p;
}

void Plotting2D(RooDataSet &fullDataSet, int const id, PdfBase &pdf,
               Configuration &config, std::string const &outputDir) {
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  auto buDeltaAbsData = fullDataSet.reduce(
      ("fitting==fitting::" +
       ComposeFittingName(Mass::buDelta, neutral, bachelor, daughters, charge))
          .c_str());
  auto buDeltaDataSet = dynamic_cast<RooDataSet *>(buDeltaAbsData);
  if (buDeltaDataSet == nullptr) {
    throw std::runtime_error("Could not cast buDeltaAbsData to RooDataSet.");
  }

  auto deltaAbsData = fullDataSet.reduce(
      ("fitting==fitting::" +
       ComposeFittingName(Mass::delta, neutral, bachelor, daughters, charge))
          .c_str());
  auto deltaDataSet = dynamic_cast<RooDataSet *>(deltaAbsData);
  if (deltaDataSet == nullptr) {
    throw std::runtime_error("Could not cast deltaAbsData to RooDataSet.");
  }
  deltaDataSet->append(*buDeltaDataSet);

  auto dataHist = std::unique_ptr<RooDataHist>(
      deltaDataSet->binnedClone("dataHist", "dataHist"));
  if (dataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataset.");
  }

  auto dataHist1d = dataHist->createHistogram(
      ("dataHist2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buDeltaMass(), RooFit::Binning(config.buDeltaMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
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
  TCanvas canvasData(
      ("canvasData_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  dataHist2d->SetStats(0);
  if (neutral == Neutral::pi0) {
    dataHist2d->GetYaxis()->SetTitle(
        "m[D^{*0} - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  dataHist2d->SetTitle(
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str());
  dataHist2d->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs((outputDir + "/2d_plots/" +
                     ComposeName(id, neutral, bachelor, daughters, charge) +
                     "_2dData.pdf")
                        .c_str());
}

void Run2DToys(RooDataSet &fullDataSet, Configuration &config,
               Configuration::Categories &categories,
               std::vector<Neutral> const &neutralVec,
               std::vector<Daughters> const &daughtersVec,
               std::vector<Charge> const &chargeVec,
               std::string const &outputDir) {
  int tmpId = 0;
  auto p = MakeSimultaneousPdf(tmpId, config, categories, neutralVec,
                               daughtersVec, chargeVec);
  auto pdfs = p.second;
  for (auto &p : pdfs) {
    int id = 0;
    Plotting2D(fullDataSet, id, *p, config, outputDir);
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

// Check file exists
bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

int main(int argc, char **argv) {
  std::string inputDir = "";
  std::string outputDir;
  std::vector<Year> yearVec;
  std::vector<Polarity> polarityVec;
  std::vector<Bachelor> bachelorVec;
  std::vector<Neutral> neutralVec;
  std::vector<Daughters> daughtersVec;
  std::vector<Charge> chargeVec;
  // Still want to load both charges:plus and minus, we just fit with
  // them differently

  bool fitBool = true;
  int nToys = 0;
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
    std::string neutralArg("gamma,pi0");
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("total");
    int toysArg = 0;
    int deltaLowArg = 0;
    int deltaHighArg = 0;
    int buDeltaLowArg = 0;
    int buDeltaHighArg = 0;

    // We always want to simultaneously fir the pi AND k bachelor modes
    // together
    bachelorVec = ExtractEnumList<Bachelor>(bachelorArg);

    if (args("help")) {
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "Type ./Fitting \n"
                << "-inputDir=<RooDataSets directory name> if fitting to data "
                   "or toy generated from data \n"
                << "-outputDir=<output directory> \n";
      std::cout << "Give box dimensions:\n"
                << "    -dl=#, -dh=#, -bl=#, -bh=#\n";
      std::cout << "Followed by the possible options:\n";
      std::cout << "    -1D, default fit is double 1D\n";
      std::cout << "    -year=<choice {2011,2012,2015,2016} default: "
                << yearArg << ">\n";
      std::cout << "    -polarity=<choice {up,down} default: " << polarityArg
                << ">\n";
      // std::cout << "    -bachelor choice {k,pi} default: " << bachelorArg
      // <<
      // "\n";
      std::cout << "    -neutral=<choice {pi0,gamma} default: " << neutralArg
                << ">\n";
      std::cout << "    -daughters=<choice {kpi,kk,pipi,pik} default: "
                << daughtersArg << ">\n";
      std::cout << "    -charge=<choice {plus/minus/total} default: "
                << chargeArg << ">\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << "    -toys=<# toys>"
                << "\n";
      std::cout << "    Optional: if you want to run toys. If # toys = 1, toys "
                   "will also be plotted.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";

      return 1;
    } else {
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

      if (!args("toys", toysArg)) {
        std::cout << "Running data fit.\n";
      } else {
        nToys = toysArg;
        std::cout << "Running " << nToys << " toys\n";
      }

      if (!args("inputDir", inputDir) && nToys == 0) {
        std::cerr << "Data directory must be specified (-inputDir=<path>).\n";
        return 1;
      } else {
        std::cout << "Generating toy from PDF MC shapes.\n";
      }

      if (!args("outputDir", outputDir)) {
        std::cerr << "Specify output directory (-outputDir=<path>).\n";
        return 1;
      }
      if (args("1D")) {
        std::cout << "Running 1D fit.\n";
        config.fit1D() = true;
      }
      // Year
      // args matches "year" to string given in command line and assigns
      // option
      // parsed to year
      if (!args("year", yearArg)) {
        std::cout << "Using default value -year=[" << yearArg << "].\n";
      }
      try {
        yearVec = ExtractEnumList<Year>(yearArg);
      } catch (std::invalid_argument) {
        std::cerr << "year assignment failed, please specify: "
                     "-year=[2011,2012,2015,2016].\n";
        return 1;
      }

      // Polarity
      if (!args("polarity", polarityArg)) {
        std::cout << "Using default value -polarity=[" << polarityArg << "].\n";
      }
      try {
        polarityVec = ExtractEnumList<Polarity>(polarityArg);
      } catch (std::invalid_argument) {
        std::cerr << "Polarity assignment failed, please specify: "
                     "-polarity=[up,down].\n";
        return 1;
      }

      // Neutral
      if (!args("neutral", neutralArg)) {
        std::cerr << "Using default value -neutral=[" << neutralArg << "]\n";
      }
      try {
        neutralVec = ExtractEnumList<Neutral>(neutralArg);
      } catch (std::invalid_argument) {
        std::cerr << "neutral assignment failed, please specify: "
                     "-neutral=[pi0,gamma].\n";
        return 1;
      }

      if (!args("daughters", daughtersArg)) {
        std::cout << "Using default value -daughters=[" << daughtersArg
                  << "].\n";
      }
      try {
        daughtersVec = ExtractEnumList<Daughters>(daughtersArg);
      } catch (std::invalid_argument) {
        std::cerr << "daughters assignment failed, please specify: "
                     "-daughters=[kpi,kk,pipi,pik].\n";
        return 1;
      }

      if (!args("charge", chargeArg)) {
        std::cout << "Using default value -charge=[" << chargeArg << "].\n";
      }
      try {
        chargeVec = ExtractEnumList<Charge>(chargeArg);
        std::cout << "Using value -charge=[" << chargeArg << "].\n";
      } catch (std::invalid_argument) {
        std::cerr << "charge assignment failed, please specify: "
                     "-charge=[plus,minus] or -charge=[total].\n";
        return 1;
      }
    }
  }

  Configuration::Categories &categories = Configuration::Get().categories();

  // Raise lower mass boundary in delta mass for pi0 plots
  if (neutralVec.size() == 1 && neutralVec[0] == Neutral::pi0) {
    config.deltaMass().setMin(136);
    config.deltaMass().setBins(54);
    config.initYieldFAVSignal() = 15600;
  }

  // Declare simPDF and result before any if statements so that it can be passed
  // to RunD1DToys no matter what
  std::unique_ptr<RooSimultaneous> simPdf;
  std::unique_ptr<RooFitResult> result;

  if (inputDir != "") {
    std::map<std::string, RooDataSet *> mapCategoryDataset;

    // Add up lumi in order to convert into string to go on plots
    double lumi = 0;
    double lumiErr = 0;

    // Loop over all options in
    // order to extract correct roodatasets.
    for (auto &y : yearVec) {
      if (y == Year::y2011) {
        lumi += 0.98;
        lumiErr += 0.02;
      } else if (y == Year::y2012) {
        lumi += 1.99;
        lumiErr += 0.02;
      } else if (y == Year::y2015) {
        lumi += 0.28;
        lumiErr += 0.01;
      } else if (y == Year::y2016) {
        lumi += 1.65;
      } else if (y == Year::y2017) {
        lumi += 1.7;
      } else if (y == Year::y2018) {
        lumi += 2.19;
      }
      for (auto &p : polarityVec) {
        for (auto &b : bachelorVec) {
          for (auto &n : neutralVec) {
            for (auto &d : daughtersVec) {
              for (auto &c : chargeVec) {
                std::string dsFile = inputDir + "/" +
                                     ComposeFilename(y, p, b, n, d, c) +
                                     ".root";
                std::cout << "Extracting RooDataSet from file ... " << dsFile
                          << "\n";

                if (!fexists(dsFile)) {
                  std::cerr << dsFile << " does not exist.\n";
                  return 1;
                } else {
                  std::cout << dsFile << " exists.\n";
                  TFile in(dsFile.c_str(), "READ");
                  RooDataSet *inputDataSet;
                  gDirectory->GetObject("inputDataSet", inputDataSet);
                  if (inputDataSet == nullptr) {
                    throw std::runtime_error("Data set does not exist.");
                  } else {
                    std::cout << "inputDataSet extracted... \n";
                    inputDataSet->Print();
                    RooDataSet *reducedInputDataSet_n = nullptr;
                    if (n == Neutral::pi0) {
                      reducedInputDataSet_n =
                          dynamic_cast<RooDataSet *>(inputDataSet->reduce(
                              config.gammaCutString().c_str()));
                    } else {
                      reducedInputDataSet_n = dynamic_cast<RooDataSet *>(
                          inputDataSet->reduce(config.pi0CutString().c_str()));
                    }
                    if (reducedInputDataSet_n == nullptr) {
                      throw std::runtime_error(
                          "Could not reduce input w/ neutral cuts dataset.");
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
                          "Could not reduce input dataset w/ bachelor cuts.");
                    }
                    RooDataSet *reducedInputDataSet_d = nullptr;
                    if (d == Daughters::kpi || d == Daughters::pik) {
                      reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                          reducedInputDataSet_b->reduce(
                              "(abs(h1_D_ID)==211&&h1_D_PIDK<-2)||(abs(h1_D_ID)"
                              "==321&&h1_D_PIDK>2)&&(abs(h2_D_ID)==211&&h2_D_"
                              "PIDK<-2)||(abs(h2_D_ID)==321&&h2_D_PIDK>2)"));
                    } else if (d == Daughters::kk) {
                      reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                          reducedInputDataSet_b->reduce(
                              "h1_D_PIDK>2&&h2_D_PIDK>2"));
                    } else {
                      reducedInputDataSet_d = dynamic_cast<RooDataSet *>(
                          reducedInputDataSet_b->reduce(
                              "h1_D_PIDK<-2&&h2_D_PIDK<-2"));
                    }
                    if (reducedInputDataSet_d == nullptr) {
                      throw std::runtime_error(
                          "Could not reduce input dataset w/ daughter cuts.");
                    }
                    // ALSO APPLY BOX CUTS HERE
                    RooDataSet *buDeltaInputDataSet = nullptr;
                    buDeltaInputDataSet = dynamic_cast<RooDataSet *>(
                        reducedInputDataSet_d->reduce(
                            config.buDeltaMass(),
                            ("Delta_M>" + std::to_string(config.deltaLow()) +
                             "&&Delta_M<" + std::to_string(config.deltaHigh()))
                                .c_str()));
                    if (buDeltaInputDataSet == nullptr) {
                      throw std::runtime_error(
                          "Could not reduce dataset down to buDeltaMass.");
                    }
                    // Need to append each year, polarity to dataset at each key
                    // in map, as key labelled by n, b, d, c and must be unique.
                    if (mapCategoryDataset.find(
                            ComposeFittingName(Mass::buDelta, n, b, d, c)) ==
                        mapCategoryDataset.end()) {
                      mapCategoryDataset.insert(std::make_pair(
                          ComposeFittingName(Mass::buDelta, n, b, d, c),
                          buDeltaInputDataSet));
                      std::cout
                          << "Created key-value pair for category " +
                                 ComposeFittingName(Mass::buDelta, n, b, d, c) +
                                 " and corresponding dataset\n";
                    } else {
                      mapCategoryDataset[ComposeFittingName(Mass::buDelta, n, b,
                                                            d, c)]
                          ->append(*buDeltaInputDataSet);
                      std::cout
                          << "Appended dataset to category " +
                                 ComposeFittingName(Mass::buDelta, n, b, d, c) +
                                 "\n";
                    }
                    if (config.fit1D() == false) {
                      RooDataSet *deltaInputDataSet = nullptr;
                      deltaInputDataSet = dynamic_cast<RooDataSet *>(
                          reducedInputDataSet_d->reduce(
                              config.deltaMass(),
                              ("Bu_Delta_M>" +
                               std::to_string(config.buDeltaLow()) +
                               "&&Bu_Delta_M<" +
                               std::to_string(config.buDeltaHigh()))
                                  .c_str()));
                      if (deltaInputDataSet == nullptr) {
                        throw std::runtime_error(
                            "Could not reduce dataset down to deltaMass.");
                      }
                      if (mapCategoryDataset.find(
                              ComposeFittingName(Mass::delta, n, b, d, c)) ==
                          mapCategoryDataset.end()) {
                        mapCategoryDataset.insert(std::make_pair(
                            ComposeFittingName(Mass::delta, n, b, d, c),
                            deltaInputDataSet));
                        std::cout
                            << "Created key-value pair for category " +
                                   ComposeFittingName(Mass::delta, n, b, d, c) +
                                   " and corresponding dataset\n";
                      } else {
                        mapCategoryDataset[ComposeFittingName(Mass::delta, n, b,
                                                              d, c)]
                            ->append(*deltaInputDataSet);
                        std::cout
                            << "Appended dataset to category " +
                                   ComposeFittingName(Mass::delta, n, b, d, c) +
                                   "\n";
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    int id = 0;

    RooDataSet fullDataSet("fullDataSet", "fullDataSet", config.fittingArgSet(),
                           RooFit::Index(categories.fitting),
                           RooFit::Import(mapCategoryDataset));

    std::cout << "\n\n\n";
    fullDataSet.Print();
    std::cout << "\n\n\n";

    Run2DToys(fullDataSet, config, categories, neutralVec, daughtersVec,
              chargeVec, outputDir);
  }
  return 0;
}
