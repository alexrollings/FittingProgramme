#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <iomanip> 
#include <experimental/filesystem>
#include <regex>
#include "TChain.h"
#include "TFile.h"

enum class Neutral { pi0, gamma, partial };
enum class Variable { buDelta, delta };

std::string EnumToString(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "pi0";
    case Neutral::gamma:
      return "gamma";
    case Neutral::partial:
      return "partial";
    default:
      return " ";
  }
}

std::string EnumToString(Variable variable) {
  switch (variable) {
    case Variable::buDelta:
      return "buDelta";
    case Variable::delta:
      return "delta";
    default:
      return " ";
  }
}

std::string to_string_with_precision(double value) {
  std::ostringstream out;
  out << std::setprecision(4) << value;
  return out.str();
}

bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

void AppendFiles(Neutral neutral,
                 std::vector<std::string> &input) {
  namespace fs = std::experimental::filesystem;
  std::string mode;
  if (neutral == Neutral::gamma) {
    mode = "Bu2Dst0pi_D0gamma";
  } else {
    mode = "Bu2Dst0pi_D0pi0";
  }
  std::regex re("\\/data\\/lhcb\\/users\\/rollings\\/Bu2Dst0h_mc_new_3\\/" +
                mode + "((_201[0-9]|_ReDecay).*)");
  std::string treeDir("/data/lhcb/users/rollings/Bu2Dst0h_mc_new_3/");
  for (auto &p : fs::directory_iterator(treeDir)) {
    std::smatch sm;
    std::stringstream pathStream;
    pathStream << p;
    std::string pathStr(pathStream.str());
    pathStr.erase(std::remove(pathStr.begin(), pathStr.end(), '"'),
                  pathStr.end());
    if (std::regex_match(pathStr, sm, re)) {
      if (neutral == Neutral::pi0) {
        input.emplace_back(treeDir + mode + sm[1].str() + "/pi0/bach_pi" +
                           "/tmva_stage1/tmva_stage2_loose/to_fit/" + mode +
                           sm[1].str() +
                           "_TM_Triggers_BDT1_BDT2_MERemoved_Fit.root");
      } else {
        input.emplace_back(
            treeDir + mode + sm[1].str() + "/gamma/bach_pi" +
            "/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/" + mode +
            sm[1].str() + "_TM_Triggers_BDT1_BDT2_MERemoved_Fit.root");
      }
    }
  }
}

void SetupTChain(Neutral neutral, TChain &chain,
                 std::vector<std::string> const &input) {
  std::string tree;
  if (neutral == Neutral::pi0) {
    tree = "BtoDstar0h3_h1h2pi0RTuple";
  } else {
    tree = "BtoDstar0h3_h1h2gammaTuple";
  }
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

void GetBoxEffs(Neutral neutral, Variable variable) {
  std::vector<std::string> input;
  AppendFiles(neutral, input);
  if (input.size() == 0) {
    throw std::runtime_error("No input files found\n");
  }
  TChain chain("");
  SetupTChain(neutral, chain, input);
  std::cout << "Returned TChain\n";
  try {
    chain.GetEntry(0);
  } catch (std::exception &ex) {
    std::cout << "Could net GetEntry(0) from chain: " << ex.what() << "!\n";
  }

  double initEntries = chain.GetEntries();

  std::string filename =
      EnumToString(neutral) + "_" + EnumToString(variable) + "_effs.txt";
  std::ofstream txtFile(filename);

  double deltaHigh, deltaLow, buHigh, buLow;
  if (neutral == Neutral::pi0) {
    deltaHigh = 160;
    deltaLow = 136;
    buHigh = 5380;
    buLow = 5180;
  } else if (neutral == Neutral::gamma) {
    deltaHigh = 190;
    deltaLow = 105;
    buHigh = 5380;
    buLow = 5180;
  } else {
    // Don't go higher than 125 to avoid triple counting
    deltaHigh = 125;
    deltaLow = 60;
    buHigh = 5440;
    buLow = 5140;
  }

  if (variable == Variable::delta) {
    double step;
    if (neutral == Neutral::pi0) {
      step = 0.1;
    } else {
      step = 0.5;
    }
    std::vector<std::string> deltaHighVec;
    for (double i = deltaHigh; i > deltaLow; i = i - step) {
      deltaHighVec.emplace_back(to_string_with_precision(i));
    }
    for (auto &dH : deltaHighVec) {
      std::string bL = to_string_with_precision(buLow);
      std::string bH = to_string_with_precision(buHigh);
      std::string dL = to_string_with_precision(deltaLow);
      txtFile << bL + " " + bH + " " + dL + " " + dH + ":" +
                     std::to_string(
                         chain.GetEntries(("Bu_Delta_M>" + bL +
                                           "&&Bu_Delta_M<" + bH + "&&Delta_M>" +
                                           dL + "&&Delta_M<" +
                                           dH).c_str()) /
                         initEntries) +
                     "\n";
    }
  } else {
    std::vector<std::string> buHighVec;
    for (double i = buHigh; i > buLow; --i) {
      buHighVec.emplace_back(to_string_with_precision(i));
    }
    for (auto &bH : buHighVec) {
      std::string dL = to_string_with_precision(deltaLow);
      std::string dH = to_string_with_precision(deltaHigh);
      std::string bL = to_string_with_precision(buLow);
      txtFile << bL + " " + bH + " " + dL + " " + dH + ":" +
                     std::to_string(
                         chain.GetEntries(("Bu_Delta_M>" + bL +
                                           "&&Bu_Delta_M<" + bH + "&&Delta_M>" +
                                           dL + "&&Delta_M<" +
                                           dH).c_str()) /
                         initEntries) +
                     "\n";
    }
  }
  txtFile.close();
}

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "Please enter: <neutral=pi0/gamma/partial> <variable=buDelta/delta>" << std::endl;
    return 1;
  }

  std::string neutralString = argv[1];
  Neutral neutral;

  if (neutralString == "pi0") {
    neutral = Neutral::pi0;
  } else if (neutralString == "gamma") {
    neutral = Neutral::gamma;
  } else if (neutralString == "partial") {
    neutral = Neutral::partial;
  } else {
    std::cerr << "Please enter neutral: pi0/gamma/partial.\n";
    return 1;
  }
  
  std::string variableString = argv[2];
  Variable variable;

  if (variableString == "buDelta") {
    variable = Variable::buDelta;
  } else if (variableString == "delta") {
    variable = Variable::delta;
  } else {
    std::cerr << "Please enter variable: buDelta/delta.\n";
    return 1;
  }

  GetBoxEffs(neutral, variable);

  return 0;
}
