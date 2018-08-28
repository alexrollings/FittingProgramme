#include <iostream>

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TTree.h"
#include "TTreeReader.h"

#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "ParseArguments.h"

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

void ExtractVarNames(std::vector<Neutral> const &neutralVec,
                     std::vector<Daughters> const &daughtersVec,
                     std::vector<std::string> &varNames) {
  int id = 0;
  GlobalVars &globalVars = GlobalVars::Get(id);

  for (auto &n : neutralVec) {
    for (auto &d : daughtersVec) {
      switch (n) {
        case Neutral::pi0: {
          NeutralVars<Neutral::pi0> &nVars_pi0 =
              NeutralVars<Neutral::pi0>::Get(id);
          varNames.emplace_back(
              nVars_pi0.a0MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varNames.emplace_back(
              nVars_pi0.a1MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varNames.emplace_back(
              nVars_pi0.a2MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          // varNames.emplace_back(nVars_pi0.thresholdDelta_Comb().GetName());
          varNames.emplace_back(nVars_pi0.cDelta_Comb().GetName());
          varNames.emplace_back(nVars_pi0.aDelta_Comb().GetName());
          NeutralBachelorVars<Neutral::pi0, Bachelor::pi> &nbVars_pi_pi0 =
              NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(id);
          varNames.emplace_back(
              nbVars_pi_pi0.a0SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varNames.emplace_back(
              nbVars_pi_pi0.a1SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varNames.emplace_back(
              nbVars_pi_pi0.a2SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          switch (d) {
            case Daughters::kpi: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kpi> &nbdVars_pi0_pi_kpi =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kpi>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_pi_kpi.asym_Bu2Dst0h_Dst02D0pi0().GetName());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::kpi> &nbdVars_pi0_k_kpi =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                               Daughters::kpi>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_k_kpi.asym_Bu2Dst0h_Dst02D0pi0().GetName());
              break;
            }
            case Daughters::kk: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kk> &nbdVars_pi0_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_pi_kk.asym_Bu2Dst0h_Dst02D0pi0().GetName());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::kk> &nbdVars_pi0_k_kk =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_k_kk.asym_Bu2Dst0h_Dst02D0pi0().GetName());
              break;
            }
            case Daughters::pipi: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_pi0_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_pi_pipi.asym_Bu2Dst0h_Dst02D0pi0().GetName());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::pipi>
                  &nbdVars_pi0_k_pipi =
                      NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_k_pipi.asym_Bu2Dst0h_Dst02D0pi0().GetName());
              break;
            }
            case Daughters::pik: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pik> &nbdVars_pi0_pi_pik =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::pik>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_pi_pik.asym_Bu2Dst0h_Dst02D0pi0().GetName());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::pik> &nbdVars_pi0_k_pik =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                               Daughters::pik>::Get(id);
              varNames.emplace_back(
                  nbdVars_pi0_k_pik.asym_Bu2Dst0h_Dst02D0pi0().GetName());
              break;
            }
          }
          break;
        }
        case Neutral::gamma: {
          NeutralVars<Neutral::gamma> &nVars_gamma =
              NeutralVars<Neutral::gamma>::Get(id);
          varNames.emplace_back(
              nVars_gamma.a0MeanBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varNames.emplace_back(
              nVars_gamma.a1MeanBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varNames.emplace_back(
              nVars_gamma.a2MeanBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varNames.emplace_back(
              nVars_gamma.a0MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varNames.emplace_back(
              nVars_gamma.a1MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varNames.emplace_back(
              nVars_gamma.a2MeanBu_Bu2Dst0h_Dst02D0pi0().GetName());
          // varNames.emplace_back(nVars_gamma.thresholdDelta_Comb().GetName());
          varNames.emplace_back(nVars_gamma.cDelta_Comb().GetName());
          varNames.emplace_back(nVars_gamma.aDelta_Comb().GetName());
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi> &nbVars_pi_gamma =
              NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(id);
          varNames.emplace_back(
              nbVars_pi_gamma.a0SigmaBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varNames.emplace_back(
              nbVars_pi_gamma.a1SigmaBu_Bu2Dst0h_Dst02D0gamma().GetName());
          varNames.emplace_back(
              nbVars_pi_gamma.a2SigmaBu_Bu2Dst0h_Dst02D0gamma().GetName());
          NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(id);
          varNames.emplace_back(
              nbVars_pi_gamma.a0SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varNames.emplace_back(
              nbVars_pi_gamma.a1SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          varNames.emplace_back(
              nbVars_pi_gamma.a2SigmaBu_Bu2Dst0h_Dst02D0pi0().GetName());
          switch (d) {
            case Daughters::kpi: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kpi>
                  &nbdVars_gamma_pi_kpi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::kpi>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_pi_kpi.asym_Bu2Dst0h_Dst02D0gamma().GetName());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::kpi>
                  &nbdVars_gamma_k_kpi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                                   Daughters::kpi>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_k_kpi.asym_Bu2Dst0h_Dst02D0gamma().GetName());
              break;
            }
            case Daughters::kk: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kk> &nbdVars_gamma_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_pi_kk.asym_Bu2Dst0h_Dst02D0gamma().GetName());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::kk> &nbdVars_gamma_k_kk =
                  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_k_kk.asym_Bu2Dst0h_Dst02D0gamma().GetName());
              break;
            }
            case Daughters::pipi: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_gamma_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_pi_pipi.asym_Bu2Dst0h_Dst02D0gamma().GetName());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::pipi>
                  &nbdVars_gamma_k_pipi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_k_pipi.asym_Bu2Dst0h_Dst02D0gamma().GetName());
              break;
            }
            case Daughters::pik: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pik>
                  &nbdVars_gamma_pi_pik =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pik>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_pi_pik.asym_Bu2Dst0h_Dst02D0gamma().GetName());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::pik>
                  &nbdVars_gamma_k_pik =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                                   Daughters::pik>::Get(id);
              varNames.emplace_back(
                  nbdVars_gamma_k_pik.asym_Bu2Dst0h_Dst02D0gamma().GetName());
              break;
            }
          }
          break;
        }
      }
    }
  }
}

void PlotVariables(std::string &inputDir, TChain &chain, TTreeReader &reader,
                   std::string &varName) {
  TTreeReaderValue<double> var(reader, varName.c_str());
  TTreeReaderValue<double> varErr(reader, (varName + "_Err").c_str());
  TTreeReaderValue<double> varPrediction(reader,
                                         (varName + "_Prediction").c_str());
  TTreeReaderValue<double> edm(reader, "EDM");
  TTreeReaderValue<int> covQual(reader, "covQual");
  TTreeReaderValue<int> fitStatus(reader, "fitStatus");

  double varMin, varMax, varErrMax;

  unsigned int j = 0;

  while (reader.Next()) {
    chain.GetEntry(j);
    if (j == 0) {
      varMin = *var;
      varMax = *var;
      varErrMax = *varErr;
    } else {
      if (*var < varMin) {
        varMin = *var;
      } else if (*var > varMax) {
        varMax = *var;
      }
      if (*varErr > varErrMax) {
        varErrMax = *varErr;
      }
    }
    j++;
  }

  TFile histFile((inputDir + "/Hist_" + varName + ".root").c_str(), "recreate");

  TH1D varHist((varName + "_hist").c_str(), (varName + "_hist").c_str(), 40,
               varMin - (varMax - varMin) / 5, varMax + (varMax - varMin) / 5);
  TH1D varErrHist((varName + "_err_hist").c_str(),
                  (varName + "_err_hist").c_str(), 40, 0,
                  varErrMax + varErrMax / 5);
  TH1D varPullHist((varName + "_pull_hist").c_str(),
                   (varName + "_pull_hist").c_str(), 40, -10, 10);
  // number of unconverged, forced positive definite, or MINOS problemed fits
  double nUnConv = 0;
  double nFPD = 0;
  double nMINOS = 0;

  reader.Restart();
  unsigned int i = 0;

  while (reader.Next()) {
    chain.GetEntry(i);
    i++;
    if (*covQual < 2) {
      nUnConv++;
    } else if (*covQual < 3) {
      nFPD++;
    } else if (*fitStatus != 0) {
      nMINOS++;
    } else {
      varHist.Fill(*var);
      varErrHist.Fill(*varErr);
      varPullHist.Fill((*var - *varPrediction) / *varErr);
    }
  }
  std::cout << "\nQuality of fits:\n"
            << "Unconverged: " << nUnConv / chain.GetEntries() * 100 << " %\n"
            << "Forced positive definite: " << nFPD / chain.GetEntries() * 100
            << " %\n"
            << "MINOS problems: " << nMINOS / chain.GetEntries() * 100
            << " %\n";

  TCanvas varCanvas((varName + "Canvas").c_str(), (varName + "Canvas").c_str(),
                    1500, 500);
  varCanvas.Divide(3, 1);
  varCanvas.cd(1);
  histFile.cd();
  varHist.GetXaxis()->SetTitle(varName.c_str());
  varHist.SetTitle("");
  varHist.Draw();
  varHist.Write();
  varCanvas.cd(2);
  varErrHist.GetXaxis()->SetTitle((varName + " Error").c_str());
  varErrHist.SetTitle("");
  varErrHist.Draw();
  varErrHist.Write();
  varCanvas.cd(3);
  varPullHist.GetXaxis()->SetTitle((varName + " Pull").c_str());
  varPullHist.SetTitle("");
  varPullHist.Draw();
  varPullHist.Write();
  varCanvas.SaveAs((inputDir + "/ValErrPull_" + varName + ".pdf").c_str());
}

int main(int argc, char **argv) {
  std::string inputDir;
  std::vector<Neutral> neutralVec;
  std::vector<Daughters> daughtersVec;

  {
    ParseArguments args(argc, argv);  // object instantiated

    std::string neutralArg("pi0,gamma");
    std::string daughtersArg("kpi,kk,pipi,pik");

    if (args("help")) {
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "Type ./PlotToys -inputDir=<toy files directory name> \n"
                << "\n";
      std::cout << "    -neutral=<choice {pi0,gamma} default: " << neutralArg
                << ">\n";
      std::cout << "    -daughters=<choice {kpi,kk,pipi,pik} default: "
                << daughtersArg << ">\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";
      return 1;

    } else {
      if (!args("inputDir", inputDir)) {
        std::cerr << "Directory must be specified (-inputDir=<inputDir>).\n";
        return 1;
      }
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
    }
  }

  std::vector<std::string> varNames;

  ExtractVarNames(neutralVec, daughtersVec, varNames);

  for (unsigned int i = 0; i < varNames.size(); ++i) {
    std::string varName = varNames[i].substr(0, varNames[i].size() - 2);
    std::string tree = varName + "_tree";
    TChain chain(tree.c_str());
    chain.Add((inputDir + "/Tree_" + varName + "_*.root").c_str());
    std::cout << "Plotting for " << chain.GetEntries() << " toys.\n";
    TTreeReader reader(&chain);
    PlotVariables(inputDir, chain, reader, varName);
  }
}
