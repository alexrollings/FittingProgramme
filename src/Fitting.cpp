#include "RooAbsBinning.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooBifurGauss.h"
#include "RooCategory.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
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
void Plotting(Bachelor bachelor, Daughters daughters, Neutral neutral,
              std::vector<Charge> chargeVec, Configuration &config,
              Categories &categories, RooDataSet const &fullDataSet,
              RooSimultaneous const &simPdf) {

  // --------------- create frame ---------------------

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
      RooFit::Slice(categories.fitting,
                    ComposeFittingCategoryName(bachelor, daughters).c_str()),
      RooFit:: 
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue);

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

  // Shape parameters that are constant across each decay mode
  // Bu2Dst0Hst
  RooRealVar meanBu2Dst0Hst("meanBu2Dst0Hst", "Bu2Dst0Hst mean",
                            5057); //, 5050, 5056);
  RooRealVar sigmaBu2Dst0Hst("sigmaBu2Dst0Hst", "Bu2Dst0Hst sigma",
                             65); //, 63, 67);

  // ButoD0pi
  RooRealVar meanBu2D0H("meanBu2D0H", "Bu2D0H mean", 5508);  //, 5502, 5506);
  RooRealVar sigmaBu2D0H("sigmaBu2D0H", "Bu2D0H sigma", 43); //, 41, 45);

  // Bu2D0Hst
  RooRealVar meanBu2D0Hst("meanBu2D0Hst", "Bu2D0Hst mean",
                          5277); //, 5268, 5278);
  RooRealVar sigmaBu2D0Hst("sigmaBu2D0Hst", "Bu2D0Hst sigma", 66); //, 62, 70);

  // Bu2Dst0pi0_D0gamma
  RooRealVar meanCrossFeed("meanCrossFeed", "Neutral cross feed mean",
                           5294); //, 5286, 5294);
  RooRealVar sigmaCrossFeed("sigmaCrossFeed", "Neutral cross feed sigma",
                            90); //, 87, 93);

  // BdtoDstpi
  RooRealVar meanBd2DstH("meanBd2DstH", "Bd2DstH mean", 5277);  //, 5279, 5267);
  RooRealVar sigmaBd2DstH("sigmaBd2DstH", "Bd2DstH sigma", 66); //, 62, 70);

  // Background pdfs common to both modes
  RooGaussian bu2Dst0HstGaussian("bu2Dst0HstGaussian", "Bu2Dst0Hst gaussian",
                                 config.buMass(), meanBu2Dst0Hst,
                                 sigmaBu2Dst0Hst);
  RooGaussian crossFeedGaussian("crossFeedGaussian",
                                "Neutral cross feed gaussian", config.buMass(),
                                meanCrossFeed, sigmaCrossFeed);
  RooGaussian bu2D0HGaussian("bu2D0HGaussian", "Bu2D0H gaussian",
                             config.buMass(), meanBu2D0H, sigmaBu2D0H);
  RooGaussian bu2D0HstGaussian("bu2D0HstGaussian", "Bu2D0Hst gaussian",
                               config.buMass(), meanBu2D0Hst, sigmaBu2D0Hst);
  RooGaussian bd2DstHGaussian("bd2DstHGaussian", "Bd2DstH gaussian",
                              config.buMass(), meanBd2DstH, sigmaBd2DstH);

  RooArgList commonFunctions;
  commonFunctions.add(bu2Dst0HstGaussian);
  commonFunctions.add(crossFeedGaussian);
  commonFunctions.add(bu2D0HGaussian);
  commonFunctions.add(bu2D0HstGaussian);
  commonFunctions.add(bd2DstHGaussian);

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
      pdfs.emplace_back(new Pdf(Bachelor::pi, Daughters::kpi, config.buMass(),
                                commonFunctions));
      pdfs.emplace_back(new Pdf(Bachelor::k, Daughters::kpi, config.buMass(),
                                commonFunctions));

    } else if (d == Daughters::kk) {

      pdfs.emplace_back(new Pdf(Bachelor::pi, Daughters::kk, config.buMass(),
                                commonFunctions));
      pdfs.emplace_back(new Pdf(Bachelor::k, Daughters::kk, config.buMass(),
                                commonFunctions));

    } else if (d == Daughters::pipi) {

      pdfs.emplace_back(new Pdf(Bachelor::pi, Daughters::pipi, config.buMass(),
                                commonFunctions));
      pdfs.emplace_back(new Pdf(Bachelor::k, Daughters::pipi, config.buMass(),
                                commonFunctions));

    } else {

      pdfs.emplace_back(new Pdf(Bachelor::pi, Daughters::pik, config.buMass(),
                                commonFunctions));
      pdfs.emplace_back(new Pdf(Bachelor::k, Daughters::pik, config.buMass(),
                                commonFunctions));
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(simPdf);
  }

  // --------------- fit  ---------------------

  simPdf.fitTo(fullDataSet);

  // Loop over daughters again to plot correct PDFs
  for (auto &d : daughtersVec) {

    if (d == Daughters::kpi) {

      Plotting(Bachelor::pi, Daughters::kpi, neutral, chargeVec, config,
               categories, fullDataSet, simPdf);
      Plotting(Bachelor::k, Daughters::kpi, neutral, chargeVec, config,
               categories, fullDataSet, simPdf);

    } else if (d == Daughters::kk) {

      Plotting(Bachelor::pi, Daughters::kk, neutral, chargeVec, config,
               categories, fullDataSet, simPdf);
      Plotting(Bachelor::k, Daughters::kk, neutral, chargeVec, config,
               categories, fullDataSet, simPdf);

    } else if (d == Daughters::pipi) {

      Plotting(Bachelor::pi, Daughters::pipi, neutral, chargeVec, config,
               categories, fullDataSet, simPdf);
      Plotting(Bachelor::k, Daughters::pipi, neutral, chargeVec, config,
               categories, fullDataSet, simPdf);

    } else {

      Plotting(Bachelor::pi, Daughters::pik, neutral, chargeVec, config,
               categories, fullDataSet, simPdf);
      Plotting(Bachelor::k, Daughters::pik, neutral, chargeVec, config,
               categories, fullDataSet, simPdf);
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

    // Check categories are assigned correctly
    // for (unsigned int i = 0; i < fullDataSet.numEntries(); i++) {
    //
    //   RooArgSet const *row = fullDataSet.get(i);
    //
    //   std::cout << "For event " << i << ":";
    //
    //   RooRealVar *idBuPtr =
    //       dynamic_cast<RooRealVar
    //       *>(row->find(config.buPdgId().GetName()));
    //   if (idBuPtr == nullptr) {
    //     std::stringstream output;
    //     output << "No value for ID[Bu] for event " << i << ".";
    //     throw std::runtime_error(output.str());
    //   } else {
    //     std::cout << "    Bu PDG ID = " << idBuPtr->getVal() << "\n";
    //   }
    //
    //   RooRealVar *mBuPtr =
    //       dynamic_cast<RooRealVar
    //       *>(row->find(config.buMass().GetName()));
    //   if (mBuPtr == nullptr) {
    //     std::stringstream output;
    //     output << "No value for m[Bu] for event " << i << ".";
    //     throw std::runtime_error(output.str());
    //   } else {
    //     std::cout << "    Bu mass = " << mBuPtr->getVal() << "\n";
    //   }
    //
    //   RooCategory *yearPtr =
    //       dynamic_cast<RooCategory
    //       *>(row->find(categories.year.GetName()));
    //   if (yearPtr == nullptr) {
    //     std::stringstream output;
    //     output << "No category assigned to year for event " << i << ".";
    //     throw std::runtime_error(output.str());
    //   } else {
    //     std::cout << "    year = " << yearPtr->getLabel() << "\n";
    //   }
    //
    //   RooCategory *polarityPtr =
    //       dynamic_cast<RooCategory
    //       *>(row->find(categories.polarity.GetName()));
    //   if (polarityPtr == nullptr) {
    //     std::stringstream output;
    //     output << "No category assigned to polarity for event " << i <<
    //     ".";
    //     throw std::runtime_error(output.str());
    //   } else {
    //     std::cout << "    Polarity = " << polarityPtr->getLabel() <<
    //     "\n";
    //   }
    //
    //   RooCategory *bachelorPtr =
    //       dynamic_cast<RooCategory
    //       *>(row->find(categories.bachelor.GetName()));
    //   if (bachelorPtr == nullptr) {
    //     std::stringstream output;
    //     output << "No category assigned to bachelor for event " << i <<
    //     ".";
    //     throw std::runtime_error(output.str());
    //   } else {
    //     std::cout << "    bachelor = " << bachelorPtr->getLabel() <<
    //     "\n";
    //   }
    //
    //   RooCategory *neutralPtr =
    //       dynamic_cast<RooCategory
    //       *>(row->find(categories.neutral.GetName()));
    //   if (neutralPtr == nullptr) {
    //     std::stringstream output;
    //     output << "No category assigned to neutral for event " << i <<
    //     ".";
    //     throw std::runtime_error(output.str());
    //   } else {
    //     std::cout << "    neutral = " << neutralPtr->getLabel() << "\n";
    //   }
    //
    //   RooCategory *daughtersPtr =
    //       dynamic_cast<RooCategory
    //       *>(row->find(categories.daughters.GetName()));
    //   if (daughtersPtr == nullptr) {
    //     std::stringstream output;
    //     output << "No category assigned to daughters for event " << i <<
    //     ".";
    //     throw std::runtime_error(output.str());
    //   } else {
    //     std::cout << "    daughters = " << daughtersPtr->getLabel() <<
    //     "\n";
    //   }
    //
    //   RooCategory *chargePtr =
    //       dynamic_cast<RooCategory
    //       *>(row->find(categories.charge.GetName()));
    //   if (chargePtr == nullptr) {
    //     std::stringstream output;
    //     output << "No category assigned to charge for event " << i <<
    //     ".";
    //     throw std::runtime_error(output.str());
    //   } else {
    //     std::cout << "    charge = " << chargePtr->getLabel() << "\n";
    //   }
    // }

    Fitting(fullDataSet, config, categories, neutral, daughtersVec, chargeVec);
  }
  return 0;
}
