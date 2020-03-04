#include <fstream>
#include <iostream>
#include "ParseArguments.h"
#include "Configuration.h"

// Check file exists
bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
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
  
  return 0;
}
