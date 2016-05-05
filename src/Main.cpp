#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <vector>

#include "RooDataSet.h"

#include "Configuration.h"
#include "ParseArguments.h"

// ExtractSubString() allows user to parse multiple options separated by commas.
// Takes full options string as input and outputs a vector containing each
// specified option as an element

std::vector<std::string> ExtractSubString(std::string myFullString) {

  std::stringstream ss(myFullString);
  char delim = ',';
  std::string subString;
  std::vector<std::string> subStrings;

  // >> extracts a string from iss
  while (std::getline(ss, subString, delim)) {
    subStrings.push_back(subString);
  }

  return subStrings;
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
  std::string year("2011,2012,2015");
  std::string polarity("up,down");
  std::string bachelor;
  std::string neutral;
  std::string daughters("kpi");
  std::string charge("plus,minus");

  std::vector<std::string> yearVec;
  std::vector<std::string> polarityVec;
  std::vector<std::string> bachelorVec;
  std::vector<std::string> daughtersVec;
  std::vector<std::string> chargeVec;
  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  { // calls destructor when object goes out of scope: Will tell you if anything
    // was not used that was given as a command line argument before continuing
    ParseArguments args(argc, argv); // object instantiated

    if (args("help")) {
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "The following options are possible:\n";
      std::cout << "\n";
      std::cout << "    -year choice {2011,2012,2015} default: " << year
                << "\n";
      std::cout << "    -polarity choice {up,down} default: " << polarity
                << "\n";
      std::cout << "    -bachelor choice {k,pi} must be specified.\n";
      std::cout << "    -neutral choice {pi0,gamma} must be specified.\n";
      std::cout << "    -daughters choice {kpi,kk,pipi,pik} default: "
                << daughters << "\n";
      std::cout << "    -charge choice {plus,minus} default: " << charge
                << "\n";
      std::cout << "\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";
    } else {

      if (args("year", year)) { // args matches "year" to string given in
                                // command like and assigns option parsed to
                                // year
        yearVec = ExtractSubString(year);
        for (unsigned int i = 0; i < yearVec.size(); i++) {
          if (yearVec[i] != "2011" && yearVec[i] != "2012" &&
              yearVec[i] != "2015") {
            std::cerr << "year assignment failed, please specify: "
                         "-year=[2011,2012,2015].\n";
            return 1;
          } else {
            std::cout << "-year = " << yearVec[i] << "\n";
          }
        }
      } else {
        std::cout << "Using default value -year=[" << year << "].\n";
        yearVec = ExtractSubString(year);
      }

      if (args("polarity", polarity)) {
        polarityVec = ExtractSubString(polarity);
        for (unsigned int i = 0; i < polarityVec.size(); i++) {
          if (polarityVec[i] != "up" && polarityVec[i] != "down") {
            std::cerr << "Polarity assignment failed, please specify: "
                         "-polarity=[up,down].\n";
            return 1;
          } else {
            std::cout << "-polarity = " << polarityVec[i] << "\n";
          }
        }
      } else {
        std::cout << "Using default value -polarity=[" << polarity << "].\n";
        polarityVec = ExtractSubString(polarity);
      }

      if (args("bachelor", bachelor)) {
        bachelorVec = ExtractSubString(bachelor);
        for (unsigned int i = 0; i < bachelorVec.size(); i++) {
          if (bachelorVec[i] != "pi" && bachelorVec[i] != "k") {
            std::cerr << "bachelor assignment failed, please specify: "
                         "-bachelor=[pi,k].\n";
            return 1;
          } else {
            std::cout << "-bachelor = " << bachelorVec[i] << "\n";
          }
        }
      } else {
        std::cerr << "Missing mandatory argument: -bachelor\n";
        return 1;
      }

      if (args("neutral", neutral)) {
        if (neutral != "pi0" && neutral != "gamma") {
          std::cerr << "neutral assignment failed, please specify: "
                       "-neutral=[pi0,gamma].\n";
          return 1;
        }
      } else {
        std::cerr << "Missing mandatory argument: -neutral\n";
        return 1;
      }


      if (args("daughters", daughters)) {
        daughtersVec = ExtractSubString(daughters);
        for (unsigned int i = 0; i < daughtersVec.size(); i++) {
          if (daughtersVec[i] != "kpi" && daughtersVec[i] != "kk" &&
              daughtersVec[i] != "pipi" && daughtersVec[i] != "pik") {
            std::cerr << "daughters assignment failed, please specify: "
                         "-daughters=[kpi,kk,pipi,pik].\n";
            return 1;
          } else {
            std::cout << "-daughters = " << daughtersVec[i] << "\n";
          }
        }
      } else {
        std::cout << "Using default value -daughters=[" << daughters << "].\n";
        daughtersVec = ExtractSubString(daughters);
      }

      if (args("charge", charge)) {
        chargeVec = ExtractSubString(charge);
        for (unsigned int i = 0; i < chargeVec.size(); i++) {
          if (chargeVec[i] != "plus" && chargeVec[i] != "minus") {
            std::cerr << "charge assignment failed, please specify: "
                         "-charge=[plus,minus].\n";
            return 1;
          } else {
            std::cout << "-charge = " << chargeVec[i] << "\n";
          }
        }
      } else {
        std::cout << "Using default value -charge=[" << charge << "].\n";
        chargeVec = ExtractSubString(charge);
      }
    }
  }

  RooDataSet *dataset = NULL;
  Configuration config(neutral == "pi0" ? Neutral::pi0 : Neutral::gamma);

  for (unsigned int yCounter = 0; yCounter < yearVec.size(); yCounter++) {
    for (unsigned int pCounter = 0; pCounter < polarityVec.size(); pCounter++) {
      for (unsigned int bCounter = 0; bCounter < bachelorVec.size();
           bCounter++) {
        for (unsigned int dCounter = 0; dCounter < daughtersVec.size();
             dCounter++) {
          for (unsigned int cCounter = 0; cCounter < chargeVec.size();
               cCounter++) {
            std::stringstream dsFile;
            dsFile << dsPath << yearVec[yCounter] << "_"
                   << polarityVec[pCounter] << "_" << bachelorVec[bCounter]
                   << "_" << neutral << "_" << daughtersVec[dCounter] << "_"
                   << chargeVec[cCounter] << ".root";
            std::cout << "Extracting RooDataSet from file ... " << dsFile.str()
                      << "\n";

            if (!fexists(dsFile.str())) {
              std::cerr << dsFile.str() << " does not exists.\n";
              return 1;
            } else {
              std::cout << dsFile.str() << " exists.\n";
              // dataset = RooDataSet::read(dsFile.str().c_str(), config.buMass());
              std::cout << "RooDataSet extracted\n";
              // NEED TO DEFINE mBu PROPERLY
            }
          }
        }
      }
    }
  }

  return 0;
}
