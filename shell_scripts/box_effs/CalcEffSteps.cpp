#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <iomanip> 
#include "TChain.h"
#include "TFile.h"

enum class Neutral { pi0, gamma };
enum class Variable { buDelta, delta };

std::string EnumToString(Neutral neutral) {
  switch (neutral) {
    case Neutral::pi0:
      return "pi0";
    case Neutral::gamma:
      return "gamma";
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

void GetBoxEffs(Neutral neutral, Variable variable) {
  std::string ttree, cutString;
  std::vector<std::string> input;
  std::vector<std::string> years = {"2011", "2012", "2015", "2016"};
  std::vector<std::string> polarities = {"Up", "Down"};
  std::string path = "/data/lhcb/users/rollings/Bu2Dst0h_mc_new/";

  std::vector<std::string> buLow = {"5180"};
  std::vector<std::string> deltaLow;
  std::vector<std::string> buHigh;
  std::vector<std::string> deltaHigh;

  if (neutral == Neutral::pi0) {
    ttree = "BtoDstar0h3_h1h2pi0RTuple";
    cutString =
        "Bu_Delta_M>4900&&Bu_Delta_M<5800&&Delta_M>136&&Delta_M<190&&BDT1>0.05&"
        "&BDT2>0.05&&Pi0_M<165&&Pi0_M>125&&D0h_M>4900&&D0_FD_ZSIG>2";
    for (auto &y : years) {
      for (auto &p : polarities) {
        input.emplace_back(path + "Bu2Dst0pi_D0pi0_" + y + "_Mag" + p +
                           "/pi0/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
                           "Bu2Dst0pi_D0pi0_" +
                           y + "_Mag" + p + "_BDT1_BDT2_PID_TM.root");
      }
    }
    deltaLow.emplace_back("136");
  } else {
    ttree = "BtoDstar0h3_h1h2gammaTuple";
    cutString =
        "Bu_Delta_M>4900&&Bu_Delta_M<5800&&Delta_M>60&&Delta_M<190&&BDT1>0.05&"
        "&BDT2>0.05&&D0h_M>4900&&D0_FD_ZSIG>2";
    for (auto &y : years) {
      for (auto &p : polarities) {
        input.emplace_back(
            path + "Bu2Dst0pi_D0gamma_" + y + "_Mag" + p +
            "/gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/"
            "cross_feed_removed/Bu2Dst0pi_D0gamma_" +
            y + "_Mag" + p + "_BDT1_BDT2_PID_TM.root");
      }
    }
    deltaLow.emplace_back("105");
  }

  TChain chain(ttree.c_str());
  for (auto &i : input) {
    chain.Add(i.c_str());
  }

  double initEntries = chain.GetEntries(cutString.c_str());

  std::string filename = EnumToString(neutral) + "_" +
                         EnumToString(variable) + "_effs.txt";
  std::ofstream txtFile(filename);

  if (variable == Variable::delta) {
    buHigh.emplace_back("5380");
    double high, low, step;
    if (neutral == Neutral::pi0) {
      high = 160;
      low = 136;
      step = 0.1;
    } else {
      high = 190;
      low = 105;
      step = 0.5;
    }
    for (double i = high; i > low; i = i - step) {
      deltaHigh.emplace_back(to_string_with_precision(i));
    }
    for (auto &dH : deltaHigh) {
      std::string bL = buLow[0];
      std::string bH = buHigh[0];
      std::string dL = deltaLow[0];
      txtFile << bL + " " + bH + " " + dL + " " + dH + ":" +
                     std::to_string(
                         chain.GetEntries((cutString + "&&Bu_Delta_M>" + bL +
                                           "&&Bu_Delta_M<" + bH + "&&Delta_M>" +
                                           dL + "&&Delta_M<" +
                                           dH).c_str()) /
                         initEntries) +
                     "\n";
    }
  } else {
    for (double i = 5380; i > 5180; --i) {
      buHigh.emplace_back(to_string_with_precision(i));
    }
    if (neutral == Neutral::pi0) {
      deltaHigh.emplace_back("160");
    } else {
      deltaHigh.emplace_back("190");
    }
    for (auto &bH : buHigh) {
      std::string bL = buLow[0];
      std::string dL = deltaLow[0];
      std::string dH = deltaHigh[0];
      txtFile << bL + " " + bH + " " + dL + " " + dH + ":" +
                     std::to_string(
                         chain.GetEntries((cutString + "&&Bu_Delta_M>" + bL +
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
    std::cerr << "Please enter: <neutral=pi0/gamma> <variable=buDelta/delta>" << std::endl;
    return 1;
  }

  std::string neutralString = argv[1];
  Neutral neutral;

  if (neutralString == "pi0") {
    neutral = Neutral::pi0;
  } else if (neutralString == "gamma") {
    neutral = Neutral::gamma;
  } else {
    std::cerr << "Please enter neutral: pi0/gamma.\n";
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
