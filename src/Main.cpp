// Main currently reads in command line options or which data the user wants to fit,
// Loops over all .root files in roodatasets/ that are needed and appends them to the full data set
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <vector>

#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
#include "TFile.h"

#include "Configuration.h"
#include "ParseArguments.h"

// ExtractEnumList() allows user to parse multiple options separated by commas.
// Takes full options string as input and outputs a vector containing each
// specified option as an element

template <typename Enum>
std::vector<Enum> ExtractEnumList(std::string const &s, char delim = ',') {

  std::stringstream ss(s);
  std::vector<Enum> values;
  std::string substring;

  while (std::getline(ss, substring, delim)) {
    values.push_back(StringToEnum<Enum>(substring));
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

using namespace RooFit;

int main(int argc, char **argv) {

  std::vector<Year> yearVec;
  std::vector<Polarity> polarityVec;
  std::vector<Bachelor> bachelorVec;
  Neutral neutral;
  std::vector<Daughter> daughtersVec;
  std::vector<Charge> chargeVec;

  Configuration config(neutral); // Initialise RooRealVars
  Categories categories;         // Initialize categories

  // ADD ARGSET TO CONFIGURATIONS.h/.cpp
  RooArgSet fullArgSet;
  fullArgSet.add(config.buMass());
  fullArgSet.add(config.buPdgId());
  fullArgSet.add(categories.polarity);
  fullArgSet.add(categories.charge);
  fullArgSet.add(categories.daughter);
  fullArgSet.add(categories.bachelor);
  fullArgSet.add(categories.year);
  fullArgSet.add(categories.neutral);

  // fullDataSet to add all data sets we want into
  RooDataSet fullDataSet("dataset", "dataset", fullArgSet);

  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  { // calls destructor when object goes out of scope: Will tell you if anything
    // was not used that was given as a command line argument before continuing
    ParseArguments args(argc, argv); // object instantiated

    std::string yearArg("2011,2012,2015");
    std::string polarityArg("up,down");
    std::string bachelorArg;
    std::string neutralArg;
    std::string daughtersArg("kpi");
    std::string chargeArg("plus,minus");

    if (args("help")) {

      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "The following options are possible:\n";
      std::cout << "\n";
      std::cout << "    -year choice {2011,2012,2015} default: " << yearArg
                << "\n";
      std::cout << "    -polarity choice {up,down} default: " << polarityArg
                << "\n";
      std::cout << "    -bachelor choice {k,pi} must be specified.\n";
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
      // args matches "year" to string given in command like and assigns option
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

      // Bachelor
      if (!args("bachelor", bachelorArg)) {
        std::cerr << "Missing mandatory argument: -bachelor\n";
        return 1;
      }
      try {
        bachelorVec = ExtractEnumList<Bachelor>(bachelorArg);
      } catch (std::invalid_argument) {
        std::cerr << "bachelor assignment failed, please specify: "
                     "-bachelor=[pi,k].\n";
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
        daughtersVec = ExtractEnumList<Daughter>(daughtersArg);
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
  }

  // Loop over all options in order to extract correct roodatasets
  for (unsigned int yCounter = 0; yCounter < yearVec.size(); yCounter++) {
    for (unsigned int pCounter = 0; pCounter < polarityVec.size(); pCounter++) {
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

  // // Check categories are assigned correctly
  // for (unsigned int i = 0; i < fullDataSet.numEntries(); i++) {
  //
  //   RooArgSet const *row = fullDataSet.get(i);
  //
  //   std::cout << "For event " << i << ":";
  //
  //   RooRealVar *idBuPtr =
  //       dynamic_cast<RooRealVar *>(row->find(config.buPdgId().GetName()));
  //   if (idBuPtr == nullptr) {
  //     std::stringstream output;
  //     output << "No value for ID[Bu] for event " << i << ".";
  //     throw std::runtime_error(output.str());
  //   } else {
  //     std::cout << "    Bu PDG ID = " << idBuPtr->getVal() << "\n";
  //   }
  //
  //   RooRealVar *mBuPtr =
  //       dynamic_cast<RooRealVar *>(row->find(config.buMass().GetName()));
  //   if (mBuPtr == nullptr) {
  //     std::stringstream output;
  //     output << "No value for m[Bu] for event " << i << ".";
  //     throw std::runtime_error(output.str());
  //   } else {
  //     std::cout << "    Bu mass = " << mBuPtr->getVal() << "\n";
  //   }
  //
  //   RooCategory *yearPtr =
  //       dynamic_cast<RooCategory *>(row->find(categories.year.GetName()));
  //   if (yearPtr == nullptr) {
  //     std::stringstream output;
  //     output << "No category assigned to year for event " << i << ".";
  //     throw std::runtime_error(output.str());
  //   } else {
  //     std::cout << "    year = " << yearPtr->getLabel() << "\n";
  //   }
  //
  //   RooCategory *polarityPtr =
  //       dynamic_cast<RooCategory *>(row->find(categories.polarity.GetName()));
  //   if (polarityPtr == nullptr) {
  //     std::stringstream output;
  //     output << "No category assigned to polarity for event " << i << ".";
  //     throw std::runtime_error(output.str());
  //   } else {
  //     std::cout << "    Polarity = " << polarityPtr->getLabel() << "\n";
  //   }
  //
  //   RooCategory *bachelorPtr =
  //       dynamic_cast<RooCategory *>(row->find(categories.bachelor.GetName()));
  //   if (bachelorPtr == nullptr) {
  //     std::stringstream output;
  //     output << "No category assigned to bachelor for event " << i << ".";
  //     throw std::runtime_error(output.str());
  //   } else {
  //     std::cout << "    bachelor = " << bachelorPtr->getLabel() << "\n";
  //   }
  //
  //   RooCategory *neutralPtr =
  //       dynamic_cast<RooCategory *>(row->find(categories.neutral.GetName()));
  //   if (neutralPtr == nullptr) {
  //     std::stringstream output;
  //     output << "No category assigned to neutral for event " << i << ".";
  //     throw std::runtime_error(output.str());
  //   } else {
  //     std::cout << "    neutral = " << neutralPtr->getLabel() << "\n";
  //   }
  //
  //   RooCategory *daughterPtr =
  //       dynamic_cast<RooCategory *>(row->find(categories.daughter.GetName()));
  //   if (daughterPtr == nullptr) {
  //     std::stringstream output;
  //     output << "No category assigned to daughter for event " << i << ".";
  //     throw std::runtime_error(output.str());
  //   } else {
  //     std::cout << "    daughter = " << daughterPtr->getLabel() << "\n";
  //   }
  //
  //   RooCategory *chargePtr =
  //       dynamic_cast<RooCategory *>(row->find(categories.charge.GetName()));
  //   if (chargePtr == nullptr) {
  //     std::stringstream output;
  //     output << "No category assigned to charge for event " << i << ".";
  //     throw std::runtime_error(output.str());
  //   } else {
  //     std::cout << "    charge = " << chargePtr->getLabel() << "\n";
  //   }
  // }

  return 0;
}
