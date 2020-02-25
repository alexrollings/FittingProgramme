#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
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
  out << std::setprecision(5) << value;
  return out.str();
}

void GetBoxEffs(Neutral neutral, Variable variable, float lowerLimit,
                float upperLimit) {
  std::string ttree, cutString;
  std::vector<std::string> input;
  std::vector<std::string> years = {"2011", "2012", "2015", "2016"};
  std::vector<std::string> polarities = {"Up", "Down"};
  std::string path = "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/";

  if (neutral == Neutral::pi0) {
    ttree = "BtoDstar0h3_h1h2pi0RTuple";
    cutString =
        "Bu_Delta_M>5050&&Bu_Delta_M<5500&&Delta_M>136&&Delta_M<190&&BDT1>0.05&"
        "&BDT2>0.05&&Pi0_M<165&&Pi0_M>125&&D0h_M>4900&&D0h_M<5200&&D0_FD_ZSIG>"
        "2";
    for (auto &y : years) {
      for (auto &p : polarities) {
        input.emplace_back(path + "Bu2Dst0pi_D0pi0_" + y + "_Mag" + p +
                           "/pi0/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
                           "Bu2Dst0pi_D0pi0_" +
                           y + "_Mag" + p + "_BDT1_BDT2_PID_TM.root");
      }
    }
  } else {
    ttree = "BtoDstar0h3_h1h2gammaTuple";
    cutString =
        "Bu_Delta_M>5050&&Bu_Delta_M<5500&&Delta_M>60&&Delta_M<190&&BDT1>0.05&"
        "&BDT2>0.05&&D0h_M>4900&&D0h_M<5200&&D0_FD_ZSIG>2";
    for (auto &y : years) {
      for (auto &p : polarities) {
        if (neutral == Neutral::gamma) {
          input.emplace_back(
              path + "Bu2Dst0pi_D0gamma_" + y + "_Mag" + p +
              "/gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
              "cross_feed_removed/Bu2Dst0pi_D0gamma_" +
              y + "_Mag" + p + "_BDT1_BDT2_PID_TM.root");
        } else {
          input.emplace_back(
              path + "Bu2Dst0pi_D0pi0_" + y + "_Mag" + p +
              "/gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
              "cross_feed_removed/Bu2Dst0pi_D0pi0_" +
              y + "_Mag" + p + "_BDT1_BDT2_PID_TM.root");
        }
      }
    }
  }

  TChain chain(ttree.c_str());
  for (auto &i : input) {
    chain.Add(i.c_str());
  }

  double initEntries = chain.GetEntries(cutString.c_str());

  std::string filename = EnumToString(neutral) + "_" + EnumToString(variable) +
                         "_boxEffs.txt";
  std::ofstream txtFile(filename);

  std::string varString;
  float low, high, range, step;
  if (variable == Variable::delta) {
    varString = "Delta_M";
    if (neutral == Neutral::pi0) {
      low = 136;
      range = 5.0;
    } else {
      low = 60;
      range = 10.0;
    }
    high = 190;
    step = 0.05;
  } else {
    varString = "Bu_Delta_M";
    low = 5050;
    high = 5500;
    range = 30.0;
    step = 0.1;
  }

  double eff = chain.GetEntries((cutString + "&&" + varString + ">" +
                                 std::to_string(lowerLimit) + "&&" + varString +
                                 "<" + std::to_string(upperLimit))
                                    .c_str()) /
               initEntries;
  txtFile << to_string_with_precision(lowerLimit) + " " +
                 to_string_with_precision(upperLimit) + ":" +
                 std::to_string(eff) + "\n";

  for (float i = step; i < range; i = i + step) {
    float lowB = lowerLimit - i;
    float highB = upperLimit + i;
    if (lowB < low) {
      lowB = low;
    }
    if (highB > high) {
      highB = high;
    }
    double effB = chain.GetEntries((cutString + "&&" + varString + ">" +
                                    std::to_string(lowB) + "&&" + varString +
                                    "<" + std::to_string(highB))
                                       .c_str()) /
                  initEntries;
    txtFile << to_string_with_precision(lowB) + " " +
                   to_string_with_precision(highB) + ":" +
                   std::to_string(effB) + "\n";
    float lowS = lowerLimit + i;
    float highS = upperLimit - i;
    if (lowS < highS) {
      double effS = chain.GetEntries((cutString + "&&" + varString + ">" +
                                      std::to_string(lowS) + "&&" + varString +
                                      "<" + std::to_string(highS))
                                         .c_str()) /
                    initEntries;
      txtFile << to_string_with_precision(lowS) + " " +
                     to_string_with_precision(highS) + ":" +
                     std::to_string(effS) + "\n";
    }
  }
  txtFile.close();
}

int main(int argc, char **argv) {
  if (argc < 5) {
    std::cerr << "Please enter: <neutral=pi0/gamma/partial> "
                 "<variable=buDelta/delta> <lower limit> <upper limit>"
              << std::endl;
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

  float lowerLimit = atof(argv[3]);
  float upperLimit = atof(argv[4]);

  GetBoxEffs(neutral, variable, lowerLimit, upperLimit);

  return 0;
}
