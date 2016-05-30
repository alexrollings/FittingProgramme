#include "RooAbsBinning.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooCBShape.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include <fstream>
#include <iostream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Configuration.h"
#include "ParseArguments.h"
#include "Pdf.h"

// ALWAYS pass values by const reference (if possible)
// It is important to pass the same category object !!!!
void Plotting(Pdf &pdf, Neutral neutral,
              std::vector<Charge> chargeVec, Configuration &config,
              Categories &categories, RooDataSet const &fullDataSet,
              RooSimultaneous const &simPdf) {

  // --------------- create frame ---------------------

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();

  std::unique_ptr<RooPlot> frame(config.buMass().frame(RooFit::Title(
      (MakePdfTitle(bachelor, daughters, neutral, chargeVec)).c_str())));

  // --------------- plot data and pdfs onto frame ---------------------

  fullDataSet.plotOn(
      frame.get(), RooFit::Cut(("fitting==fitting::" +
                                ComposeFittingCategoryName(bachelor, daughters))
                                   .c_str()));

  // .get() gets the raw pointer from underneath the smart pointer
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::LineColor(kBlue));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.signal()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.combinatorialExponential()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kViolet));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.crossFeed()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kGreen));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2Dst0Hst_D0pi0()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2Dst0Hst_D0gamma()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2D0H()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kOrange));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2D0Hst()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kTeal));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bd2DstH()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bd2D0Hst0()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));

  // --------------- plot onto canvas ---------------------

  TCanvas canvas(
      ("simPdf_" + ComposeFittingCategoryName(bachelor, daughters)).c_str(),
      "simPdf", 1000, 1000);
  frame->Draw();
  canvas.SaveAs(
      ("Result_" + ComposeFittingCategoryName(bachelor, daughters) + ".pdf")
          .c_str());
}

void Fitting(RooDataSet &fullDataSet, Configuration &config,
             Categories &categories, Neutral neutral,
             std::vector<Daughters> daughtersVec,
             std::vector<Charge> chargeVec) {


  RooSimultaneous simPdf("simPdf", "simPdf", categories.fitting);

  std::vector<std::unique_ptr<Pdf>> pdfs;

  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &d : daughtersVec) {

    if (d == Daughters::kpi) {

      // emplace_back creates the object in the vector, emplace_back creates the
      // object then moves it into the vector
      // You only have to pass the arguments as if you were constructing the
      // vector type
      // The operators required to do this are not supported by RooFit so we
      // have to use a vector of pointers
      pdfs.emplace_back(new Pdf(Bachelor::pi, Daughters::kpi, config.buMass()));
      pdfs.emplace_back(new Pdf(Bachelor::k, Daughters::kpi, config.buMass()));

    } else if (d == Daughters::kk) {

      pdfs.emplace_back(new Pdf(Bachelor::pi, Daughters::kk, config.buMass()));
      pdfs.emplace_back(new Pdf(Bachelor::k, Daughters::kk, config.buMass()));

    } else if (d == Daughters::pipi) {

      pdfs.emplace_back(new Pdf(Bachelor::pi, Daughters::pipi, config.buMass()));
      pdfs.emplace_back(new Pdf(Bachelor::k, Daughters::pipi, config.buMass()));

    } else {

      pdfs.emplace_back(new Pdf(Bachelor::pi, Daughters::pik, config.buMass()));
      pdfs.emplace_back(new Pdf(Bachelor::k, Daughters::pik, config.buMass()));
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(simPdf);
  }

  // --------------- fit  ---------------------

  // simPdf.fitTo(fullDataSet);
  RooFitResult* result = simPdf.fitTo(fullDataSet, RooFit::Save());

  // Loop over daughters again to plot correct PDFs
  for (auto &p : pdfs) {
    Plotting(*p, neutral, chargeVec, config, categories,
             fullDataSet, simPdf);
  }

  result->Print();
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

// Path to roodatasets
std::string dsPath = "/home/rollings/ButoDst0X_FIT/roodatasets/";

int main(int argc, char **argv) {

  std::vector<Year> yearVec;
  std::vector<Polarity> polarityVec;
  std::vector<Bachelor> bachelorVec;
  Neutral neutral;
  std::vector<Daughters> daughtersVec;
  std::vector<Charge> chargeVec;

  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  { // calls destructor when object goes out of scope: Will tell you if
    // anything
    // was not used that was given as a command line argument before
    // continuing
    ParseArguments args(argc, argv); // object instantiated

    std::string yearArg("2011,2012,2015");
    std::string polarityArg("up,down");
    std::string bachelorArg("pi,k");
    std::string neutralArg;
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("plus,minus");

    // We always want to simultaneously fir the pi AND k bachelor modes
    // together
    bachelorVec = ExtractEnumList<Bachelor>(bachelorArg);

    if (args("help")) {

      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "The following options are possible:\n";
      std::cout << "\n";
      std::cout << "    -year choice {2011,2012,2015} default: " << yearArg
                << "\n";
      std::cout << "    -polarity choice {up,down} default: " << polarityArg
                << "\n";
      // std::cout << "    -bachelor choice {k,pi} default: " << bachelorArg
      // <<
      // "\n";
      std::cout << "    -neutral choice {pi0,gamma} must be specified.\n";
      std::cout << "    -daughters choice {kpi,kk,pipi,pik} default: "
                << daughtersArg << "\n";
      std::cout << "    -charge choice {plus,minus} default: " << chargeArg
                << "\n";
      std::cout << "\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";
    } else {

      // Year
      // args matches "year" to string given in command like and assigns
      // option
      // parsed to year
      if (!args("year", yearArg)) {
        std::cout << "Using default value -year=[" << yearArg << "].\n";
      }
      try {
        yearVec = ExtractEnumList<Year>(yearArg);
      } catch (std::invalid_argument) {
        std::cerr << "year assignment failed, please specify: "
                     "-year=[2011,2012,2015].\n";
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
        std::cerr << "Missing mandatory argument: -neutral\n";
        return 1;
      }
      try {
        neutral = StringToEnum<Neutral>(neutralArg);
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
      } catch (std::invalid_argument) {
        std::cerr << "charge assignment failed, please specify: "
                     "-charge=[plus,minus].\n";
        return 1;
      }
    }

    Categories categories;
    Configuration config(neutral, categories); // Initialise RooRealVars

    RooDataSet fullDataSet("dataset", "dataset", config.fullArgSet());

    // Loop over all options in order to extract correct roodatasets
    for (unsigned int yCounter = 0; yCounter < yearVec.size(); yCounter++) {
      for (unsigned int pCounter = 0; pCounter < polarityVec.size();
           pCounter++) {
        for (unsigned int bCounter = 0; bCounter < bachelorVec.size();
             bCounter++) {
          for (unsigned int dCounter = 0; dCounter < daughtersVec.size();
               dCounter++) {
            for (unsigned int cCounter = 0; cCounter < chargeVec.size();
                 cCounter++) {
              std::string dsFile =
                  dsPath +
                  ComposeFilename(yearVec[yCounter], polarityVec[pCounter],
                                  bachelorVec[bCounter], neutral,
                                  daughtersVec[dCounter], chargeVec[cCounter]) +
                  ".root";
              std::cout << "Extracting RooDataSet from file ... " << dsFile
                        << "\n";

              if (!fexists(dsFile)) {
                std::cerr << dsFile << " does not exists.\n";
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
                  fullDataSet.append(*inputDataSet);
                  std::cout << "Appended to full data set...\n";
                }
              }
            }
          }
        }
      }
    }


    Fitting(fullDataSet, config, categories, neutral, daughtersVec, chargeVec);
  }
  return 0;
}
