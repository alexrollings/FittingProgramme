#include "Efficiencies.h"
#include <algorithm>
#include <cmath>
#include <experimental/filesystem>
#include <iomanip>
#include <regex>
#include <sstream>

bool fexists(const std::string &name) {
  std::ifstream infile(name);
  return infile.good();
}

std::vector<std::string> SplitLine(std::string const &str) {
  std::stringstream ss;
  ss.str(str);
  std::string tempString;
  std::vector<std::string> stringVector;
  // '' = char
  while (std::getline(ss, tempString, ' ')) {
    stringVector.emplace_back(tempString);
  }
  return stringVector;
}

double ReturnMCEffs(Mode mode, Neutral neutral, Bachelor bachelor,
                    Efficiency eff) {
  std::string txtFileName =
      "/home/rollings/Bu2Dst0h_scripts/mc_efficiencies/txt_new/effs_" +
      EnumToString(mode) + ".txt";
  if (!fexists(txtFileName)) {
    std::cerr
        << "!!!!!!!!!!\nReturnMCEffs: " << txtFileName
        << " doesn't exist: setting eff to 1.0 and error to 0.0.\n!!!!!!!!!!";
    if (eff == Efficiency::mcEff) {
      return 1.0;
    } else if (eff == Efficiency::mcEffErr) {
      return 0.0;
    } else {
      throw std::runtime_error(
          "Can only pass mcEff/mcEffErr enum to ReturnMCEffs\n");
    }
  }
  std::ifstream inFile(txtFileName);
  std::string line;
  // Loop over lines in txt file
  while (std::getline(inFile, line)) {
    // Separate label and value (white space)
    std::vector<std::string> lineVec = SplitLine(line);
    if (lineVec[0] == EnumToString(neutral) &&
        lineVec[1] == EnumToString(bachelor)) {
      if (eff == Efficiency::mcEff) {
        return std::stod(lineVec[2]);
      } else if (eff == Efficiency::mcEffErr) {
        return std::stod(lineVec[3]);
      } else {
        throw std::runtime_error(
            "Can only pass mcEff/mcEffErr enum to ReturnMCEffs\n");
      }
    }
  }
}

// Function to be called in constructor of NVars, in order to construct
// efficiency RCVars
// Anything defined outside the class definition needs the scope :: operator
void ExtractChain(Mode mode, Bachelor bachelor, TChain &chain, bool D02pik) {
  std::cout << "Extracting chain\n";
  namespace fs = std::experimental::filesystem;
  std::string path, ttree;
  switch (Configuration::Get().neutral()) {
    case Neutral::gamma:
      switch (bachelor) {
        case Bachelor::pi:
          if (D02pik == false) {
            path = "/gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/";
          } else {
            path = "/gamma/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/";
          }
          break;
        case Bachelor::k:
          if (D02pik == false) {
            path = "/gamma/bach_K/tmva_stage1/tmva_stage2_loose/to_fit/";
          } else {
            path = "/gamma/bach_K/tmva_stage1/tmva_stage2_loose/to_fit/cross_feed_removed/";
          }
      }
      ttree = "BtoDstar0h3_h1h2gammaTuple";
      break;
    case Neutral::pi0:
      switch (bachelor) {
        case Bachelor::pi:
          path = "/pi0/bach_pi/tmva_stage1/tmva_stage2_loose/to_fit/";
          break;
        case Bachelor::k:
          path = "/pi0/bach_K/tmva_stage1/tmva_stage2_loose/to_fit/";
          break;
      }
      ttree = "BtoDstar0h3_h1h2pi0RTuple";
      break;
  }
  std::string dir = "/data/lhcb/users/rollings/Bu2Dst0h_mc_new_3/";
  std::string modeString = EnumToString(mode);
  std::cout << "Looping over " << dir << "\n";
  for (auto &p : fs::directory_iterator(dir)) {
    std::ostringstream pStream;
    pStream << p;
    std::string subdir = pStream.str();
    std::regex re(".+(" + modeString + "_((201.+)|ReDecay_201.+))");
    std::smatch match;
    if (std::regex_search(subdir, match, re)) {
      std::string decay = match.str(1);
      decay.erase(std::remove(decay.begin(), decay.end(), '"'), decay.end());
      std::string fName;
      if (D02pik == false) {
        fName =
            dir + decay + path + decay + "_PID_TM_Triggers_BDT1_BDT2_MERemoved_Fit.root";
      } else {
        fName = dir + decay + path + decay + "_TM_Triggers_BDT1_BDT2.root";
      }
      if (fexists(fName)) {
        chain.Add(fName.c_str());
        std::cout << "Added " << fName << " to chain\n";
      } else {
        throw std::runtime_error(fName + " does not exist\n");
      }
    }
  }
  // std::cout << chain.GetEntries() << "\n";
  std::cout << "Added files to chain\n";
}

void CalcBinomialErr(double eff, double nInit, double &err) {
  if (eff > 1) {
    throw std::logic_error("Cannot have efficiency > 1");
  }
  // std::cout << eff << "\t" << nInit << "\n";
  err = std::sqrt((eff * (1 - eff)) / nInit);
  // std::cout << err << "\n";
};

double ReturnBoxEffs(Mode mode, Bachelor bachelor, Efficiency eff, bool misId) {
  // std::cout << EnumToString(mode) << std::endl;
  std::string dlString = std::to_string(Configuration::Get().deltaLow());
  std::string dhString = std::to_string(Configuration::Get().deltaHigh());
  std::string blString = std::to_string(Configuration::Get().buDeltaLow());
  std::string bhString = std::to_string(Configuration::Get().buDeltaHigh());
  std::string dplString, dphString;
  if (Configuration::Get().fitBuPartial() == true) {
    dplString = std::to_string(Configuration::Get().deltaPartialLow());
    dphString = std::to_string(Configuration::Get().deltaPartialHigh());
  }
  std::string txtFileName;
  if (misId == true) {
    txtFileName = "/data/lhcb/users/rollings/txt_efficiencies/" +
                  EnumToString(Configuration::Get().neutral()) + "_misId_" +
                  EnumToString(mode) + "_as_" + EnumToString(bachelor) + "_" +
                  Configuration::Get().ReturnBoxString() + ".txt";
  } else {
    txtFileName = "/data/lhcb/users/rollings/txt_efficiencies/" +
                  EnumToString(Configuration::Get().neutral()) + "_" +
                  EnumToString(mode) + "_" +
                  Configuration::Get().ReturnBoxString() + ".txt";
  }

  std::string effStr;
  if (eff == Efficiency::deltaEff) {
    // Box eff for delta dimn is eff of buDelta window, and vice versa
    effStr = "buCutEff";
  } else if (eff == Efficiency::deltaEffErr) {
    effStr = "buCutEffErr";
  } else if (eff == Efficiency::buEff) {
    effStr = "deltaCutEff";
  } else if (eff == Efficiency::buEffErr) {
    effStr = "deltaCutEffErr";
  } else if (eff == Efficiency::buPartialEff) {
    effStr = "deltaPartialCutEff";
  } else if (eff == Efficiency::buPartialEffErr) {
    effStr = "deltaPartialCutEffErr";
  } else if (eff == Efficiency::orEff) {
    effStr = "orEff";
  } else if (eff == Efficiency::orEffErr) {
    effStr = "orEffErr";
  } else {
    throw std::runtime_error("Efficiency not recognised.\n");
  }

  // Check if txt file containing efficiencies for particular mode and box dimns
  // exists, if not, calculate eff and save in txt file
  if (!fexists(txtFileName)) {
    bool D02pik;
    if (mode == Mode::Bu2Dst0pi_D0gamma_D02pik ||
        mode == Mode::Bu2Dst0pi_D0pi0_D02pik) {
      D02pik = true;
    }

    std::string ttree;
    if (Configuration::Get().neutral() == Neutral::gamma) {
      ttree = "BtoDstar0h3_h1h2gammaTuple";
    } else {
      ttree = "BtoDstar0h3_h1h2pi0RTuple";
    }
    TChain chain(ttree.c_str());
    if (D02pik == false) {
      ExtractChain(mode, bachelor, chain, D02pik);
    } else {
      if (Configuration::Get().neutral() == Neutral::gamma) {
        // Use K and π bachelor to calculate box effs for FAV->SUP
        ExtractChain(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi, chain,
                     D02pik);
        ExtractChain(Mode::Bu2Dst0K_D0gamma_D02pik, Bachelor::k, chain, D02pik);
      } else {
        ExtractChain(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi, chain, D02pik);
        ExtractChain(Mode::Bu2Dst0K_D0pi0_D02pik, Bachelor::k, chain, D02pik);
      }
    }

    std::string cutStr;
    if (D02pik == false) {
      cutStr = Configuration::Get().ReturnCutString();
    } else {
      cutStr = "abs(D0_M_DOUBLESW_KP-1864)>15";
    }
    cutStr += "&&Bu_Delta_M<" +
              std::to_string(Configuration::Get().buDeltaMass().getMax()) +
              "&&Bu_Delta_M>" +
              std::to_string(Configuration::Get().buDeltaMass().getMin()) +
              "&&Delta_M<" +
              std::to_string(Configuration::Get().deltaMass().getMax()) +
              "&&Delta_M>" +
              std::to_string(Configuration::Get().deltaMass().getMin());

    std::string orString;
    if (Configuration::Get().fitBuPartial() == false) {
      orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                 ")||(Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString +
                 "))";
    } else {
      orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                 ")||(Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString +
                 ")||(Delta_M>" + dplString + "&&Delta_M<" + dphString + "))";
    }
    if (misId == true && bachelor == Bachelor::pi) {
      cutStr += "&&bach_PIDK_corr<12";
    }

    double nInitial = chain.GetEntries(cutStr.c_str());
    std::cout << "nInitial = " << nInitial << "\n";
    double nOr = chain.GetEntries((cutStr + "&&" + orString).c_str());
    std::cout << "nOr = " << nOr << "\n";
    double nBuCut =
        chain.GetEntries((cutStr + "&&" + orString + "&&Bu_Delta_M>" +
                          blString + "&&Bu_Delta_M<" + bhString)
                             .c_str());
    std::cout << "nBuCut = " << nBuCut << "\n";
    double nDeltaCut =
        chain.GetEntries((cutStr + "&&" + orString + "&&Delta_M>" + dlString +
                          "&&Delta_M<" + dhString)
                             .c_str());
    std::cout << "nDeltaCut = " << nDeltaCut << "\n";

    double orEff = nOr / nInitial;
    double buCutEff = nBuCut / nOr;
    double deltaCutEff = nDeltaCut / nOr;

    double orEffErr;
    double buCutEffErr;
    double deltaCutEffErr;

    CalcBinomialErr(orEff, nInitial, orEffErr);
    CalcBinomialErr(buCutEff, nOr, buCutEffErr);
    CalcBinomialErr(deltaCutEff, nOr, deltaCutEffErr);

    std::ofstream outFile;
    outFile.open(txtFileName);
    outFile << "orEff " + std::to_string(orEff) + "\n";
    outFile << "orEffErr " + std::to_string(orEffErr) + "\n";
    outFile << "buCutEff " + std::to_string(buCutEff) + "\n";
    outFile << "buCutEffErr " + std::to_string(buCutEffErr) + "\n";
    outFile << "deltaCutEff " + std::to_string(deltaCutEff) + "\n";
    outFile << "deltaCutEffErr " + std::to_string(deltaCutEffErr) + "\n";

    if (Configuration::Get().neutral() == Neutral::gamma) {
      double nDeltaPartialCut =
          chain.GetEntries((cutStr + "&&" + orString + "&&Delta_M>" +
                            dplString + "&&Delta_M<" + dphString)
                               .c_str());
      std::cout << "nDeltaPartialCut = " << nDeltaPartialCut << "\n";
      double deltaPartialCutEff = nDeltaPartialCut / nOr;
      double deltaPartialCutEffErr;
      CalcBinomialErr(deltaPartialCutEff, nOr, deltaPartialCutEffErr);
      outFile << "deltaPartialCutEff " + std::to_string(deltaPartialCutEff) +
                     "\n";
      outFile << "deltaPartialCutEffErr " +
                     std::to_string(deltaPartialCutEffErr) + "\n";
      if (eff == Efficiency::buPartialEff) {
        return deltaPartialCutEff;
      } else if (eff == Efficiency::buPartialEffErr) {
        return deltaPartialCutEffErr;
      }
    }

    if (eff == Efficiency::deltaEff) {
      return buCutEff;
    } else if (eff == Efficiency::deltaEffErr) {
      return buCutEffErr;
    } else if (eff == Efficiency::buEff) {
      return deltaCutEff;
    } else if (eff == Efficiency::buEffErr) {
      return deltaCutEffErr;
    } else if (eff == Efficiency::orEff) {
      return orEff;
    } else {
      return orEffErr;
    }

  } else {
    //   // If exists, read in from txt file
    std::cout << txtFileName << " exists.\n";
    std::ifstream inFile(txtFileName);
    std::string line;
    // Loop over lines in txt file
    while (std::getline(inFile, line)) {
      // Separate label and value (white space)
      std::vector<std::string> lineVec = SplitLine(line);
      if (lineVec[0] == effStr) {
        std::cout << std::stod(lineVec[1]) << "\n";
        return std::stod(lineVec[1]);
      }
    }
    throw std::runtime_error("Efficiency not found.\n");
  }
}

void ReturnBoxEffs(Mode mode, Bachelor bachelor,
                   std::map<std::string, double> &map, bool misId) {
  // std::cout << EnumToString(mode) << std::endl;
  std::string dlString = std::to_string(Configuration::Get().deltaLow());
  std::string dhString = std::to_string(Configuration::Get().deltaHigh());
  std::string blString = std::to_string(Configuration::Get().buDeltaLow());
  std::string bhString = std::to_string(Configuration::Get().buDeltaHigh());
  std::string dplString, dphString;
  if (Configuration::Get().fitBuPartial() == true) {
    dplString = std::to_string(Configuration::Get().deltaPartialLow());
    dphString = std::to_string(Configuration::Get().deltaPartialHigh());
  }
  std::string txtFileName;
  if (misId == true) {
    txtFileName =
        "/data/lhcb/users/rollings/txt_efficiencies_old/txt_efficiencies/" +
        EnumToString(Configuration::Get().neutral()) + "_misId_" +
        EnumToString(mode) + "_as_" + EnumToString(bachelor) + "_" +
        Configuration::Get().ReturnBoxString() + ".txt";
  } else {
    txtFileName =
        "/data/lhcb/users/rollings/txt_efficiencies_old/txt_efficiencies/" +
        EnumToString(Configuration::Get().neutral()) + "_" +
        EnumToString(mode) + "_" + Configuration::Get().ReturnBoxString() +
        ".txt";
  }

  // Check if txt file containing efficiencies for particular mode and box dimns
  // exists, if not, calculate eff and save in txt file
  if (Configuration::Get().plotToys() == true || !fexists(txtFileName)) {
    bool D02pik;
    if (mode == Mode::Bu2Dst0pi_D0gamma_D02pik ||
        mode == Mode::Bu2Dst0pi_D0pi0_D02pik) {
      D02pik = true;
    }
    std::string cutString, ttree;

    switch (Configuration::Get().neutral()) {
      case Neutral::gamma:
        if (D02pik == false) {
          cutString = Configuration::Get().ReturnCutString();
        } else {
          cutString = "abs(D0_M_DOUBLESW_KP-1864)>15";
        }
        ttree = "BtoDstar0h3_h1h2gammaTuple";
        break;
      case Neutral::pi0:
        if (D02pik == false) {
          cutString = Configuration::Get().ReturnCutString();
        } else {
          cutString = "abs(D0_M_DOUBLESW_KP-1864)>15";
        }
        ttree = "BtoDstar0h3_h1h2pi0RTuple";
        break;
    }

    TChain chain(ttree.c_str());
    if (D02pik == false) {
      ExtractChain(mode, bachelor, chain, D02pik);
    } else {
      if (Configuration::Get().neutral() == Neutral::gamma) {
        ExtractChain(Mode::Bu2Dst0pi_D0gamma_D02pik, Bachelor::pi, chain,
                     D02pik);
        ExtractChain(Mode::Bu2Dst0K_D0gamma_D02pik, Bachelor::k, chain, D02pik);
      } else {
        ExtractChain(Mode::Bu2Dst0pi_D0pi0_D02pik, Bachelor::pi, chain, D02pik);
        ExtractChain(Mode::Bu2Dst0K_D0pi0_D02pik, Bachelor::k, chain, D02pik);
      }
    }

    std::string orString;
    if (Configuration::Get().fitBuPartial() == false) {
      if (Configuration::Get().fit1D() == false) {
        orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                   ")||(Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString +
                   "))";
      } else {
        orString = "(Delta_M>" + dlString + "&&Delta_M<" + dhString + ")";
      }
    } else {
      if (Configuration::Get().fit1D() == false) {
        orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                   ")||(Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString +
                   ")||(Delta_M>" + dplString + "&&Delta_M<" + dphString + "))";
      } else {
        orString = "((Delta_M>" + dlString + "&&Delta_M<" + dhString +
                   ")||(Delta_M>" + dplString + "&&Delta_M<" + dphString + "))";
      }
    }
    double nOr = chain.GetEntries((cutString + "&&" + orString).c_str());
    if (Configuration::Get().plotToys() == true) {
      double nInitial = chain.GetEntries(cutString.c_str());
      double nBox;
      if (Configuration::Get().fit1D() == false) {
        nBox = chain.GetEntries((cutString + "&&Delta_M>" + dlString +
                                 "&&Delta_M<" + dhString + "&&Bu_Delta_M>" +
                                 blString + "&&Bu_Delta_M<" + bhString)
                                    .c_str());
      } else {
        nBox = 0.;
      }
      double orEff = nOr / nInitial;
      double orEffErr;
      CalcBinomialErr(orEff, nInitial, orEffErr);
      // std::cout << "\n\n\n orEff err = " << orEffErr << "\n\n\n";
      double boxEff = nBox / nInitial;
      double boxEffErr;
      CalcBinomialErr(boxEff, nInitial, boxEffErr);
      // std::cout << "\n\n\n boxEff err = " << boxEffErr << "\n\n\n";
      map.insert(std::pair<std::string, double>("orEff", orEff));
      map.insert(std::pair<std::string, double>("orEffErr", orEffErr));
      map.insert(std::pair<std::string, double>("boxEff", boxEff));
      map.insert(std::pair<std::string, double>("boxEffErr", boxEffErr));
      if (Configuration::Get().fitBuPartial() == true) {
        double nBoxPartial;
        if (Configuration::Get().fit1D() == false) {
          nBoxPartial = chain.GetEntries(
              (cutString + "&&Delta_M>" + dplString + "&&Delta_M<" + dphString +
               "&&Bu_Delta_M>" + blString + "&&Bu_Delta_M<" + bhString)
                  .c_str());
        } else {
          nBoxPartial = 0.;
        }
        double boxPartialEff = nBox / nInitial;
        double boxPartialEffErr;
        CalcBinomialErr(boxPartialEff, nInitial, boxPartialEffErr);
        map.insert(
            std::pair<std::string, double>("boxPartialEff", boxPartialEff));
        map.insert(std::pair<std::string, double>("boxPartialEffErr",
                                                  boxPartialEffErr));
      }
    } else {
      double nBuCut =
          chain.GetEntries((cutString + "&&" + orString + "&&Bu_Delta_M>" +
                            blString + "&&Bu_Delta_M<" + bhString)
                               .c_str());
      double nDeltaCut =
          chain.GetEntries((cutString + "&&" + orString + "&&Delta_M>" +
                            dlString + "&&Delta_M<" + dhString)
                               .c_str());
      double buDeltaCutEff = nBuCut / nOr;
      double deltaCutEff = nDeltaCut / nOr;
      // Binomial expectation value: efficienciy = N_success (binomal: err =
      // sqrt(pq) / N (poisson: err = sqrt(N)) Error: pq / N = sqrt(eff*(1-eff)
      // / N) by propagation or errors
      double buDeltaCutEffErr;
      CalcBinomialErr(buDeltaCutEff, nOr, buDeltaCutEffErr);
      double deltaCutEffErr;
      CalcBinomialErr(deltaCutEff, nOr, deltaCutEffErr);
      // if (D02pik == true) {
      //   std::cout << chain.GetEntries(cutString.c_str()) << "\t" << nBuCut <<
      //   "\t" << nDeltaCut
      //             << "\t" << nOr << "\n";
      // }

      std::ofstream outFile;
      outFile.open(txtFileName);
      outFile << "buDeltaCutEff " + std::to_string(buDeltaCutEff) + "\n";
      outFile << "buDeltaCutEffErr " + std::to_string(buDeltaCutEffErr) + "\n";
      outFile << "deltaCutEff " + std::to_string(deltaCutEff) + "\n";
      outFile << "deltaCutEffErr " + std::to_string(deltaCutEffErr) + "\n";

      map.insert(
          std::pair<std::string, double>("buDeltaCutEff", buDeltaCutEff));
      // map.insert(
      //     std::pair<std::string, double>("buDeltaCutEffErr",
      //     buDeltaCutEffErr));
      map.insert(std::pair<std::string, double>("buDeltaCutEffErr", 0.05));
      map.insert(std::pair<std::string, double>("deltaCutEff", deltaCutEff));
      // map.insert(
      //     std::pair<std::string, double>("deltaCutEffErr", deltaCutEffErr));
      map.insert(std::pair<std::string, double>("deltaCutEffErr", 0.05));

      double nDeltaPartialCut, deltaPartialCutEff, deltaPartialCutEffErr;
      if (Configuration::Get().fitBuPartial() == true) {
        double nDeltaPartialCut =
            chain.GetEntries((cutString + "&&" + orString + "&&Delta_M>" +
                              dplString + "&&Delta_M<" + dphString)
                                 .c_str());
        deltaPartialCutEff = nDeltaPartialCut / nOr;
        double deltaPartialCutEffErr;
        CalcBinomialErr(deltaPartialCutEff, nOr, deltaPartialCutEffErr);
        outFile << "deltaPartialCutEff " + std::to_string(deltaPartialCutEff) +
                       "\n";
        outFile << "deltaPartialCutEffErr " +
                       std::to_string(deltaPartialCutEffErr) + "\n";
        map.insert(std::pair<std::string, double>("deltaPartialCutEff",
                                                  deltaPartialCutEff));
        // map.insert(std::pair<std::string, double>("deltaPartialCutEffErr",
        //                                           deltaPartialCutEffErr));
        map.insert(
            std::pair<std::string, double>("deltaPartialCutEffErr", 0.05));
      }

      outFile.close();
    }
  } else {
    //   // If exists, read in from txt file
    // std::cout << txtFileName << " exists:\n\tReading efficiencies for "
    //           << EnumToString(mode) << "...\n";
    std::ifstream inFile(txtFileName);
    std::string line;
    // Loop over lines in txt file
    while (std::getline(inFile, line)) {
      // Separate label and value (white space)
      std::vector<std::string> lineVec = SplitLine(line);
      // Add to map
      std::size_t found = lineVec[0].find("EffErr");
      if (found != std::string::npos) {
        map.insert(std::pair<std::string, double>(lineVec[0], 0.05));
      } else {
        map.insert(
            std::pair<std::string, double>(lineVec[0], std::stod(lineVec[1])));
      }
    }
    std::vector<std::string> errStrVec = {"deltaCutEffErr", "buDeltaCutEffErr"};
    if (Configuration::Get().fitBuPartial() == true) {
      errStrVec.emplace_back("deltaPartialCutEffErr");
    }
    for (auto &err : errStrVec) {
      if (map.find(err) == map.end()) {
        map.insert(std::pair<std::string, double>(err, 0.05));
      }
    }
    // for (auto elem : map) {
    //   std::cout << elem.first << " " << elem.second << "\n";
    // }
  }
}
