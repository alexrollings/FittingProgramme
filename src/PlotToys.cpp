#include <iostream>

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TTree.h"
#include "TTreeReader.h"

#include "ParseArguments.h"
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"

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

void ExtractVarProperties(std::vector<Neutral> const &neutralVec,
                          std::vector<Daughters> const &daughtersVec,
                          std::vector<std::string> &varNames,
                          std::vector<double> &varPredictions,
                          std::vector<double> &varMin,
                          std::vector<double> &varMax) {
  int id = 0;
  GlobalVars &globalVars = GlobalVars::Get(id);
  varNames.emplace_back(globalVars.ratioDst0KDst0pi().GetName());
  varPredictions.emplace_back(globalVars.ratioDst0KDst0pi_predicted());
  varMin.emplace_back(globalVars.ratioDst0KDst0pi_min());
  varMax.emplace_back(globalVars.ratioDst0KDst0pi_max());

  for (auto &n : neutralVec) {
    for (auto &d : daughtersVec) {
      switch (n) {
        case Neutral::pi0: {
          switch (d) {
            case Daughters::kpi: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kpi> &nbdVars_pi0_pi_kpi =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kpi>::Get(id);
              varNames.emplace_back(nbdVars_pi0_pi_kpi.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_pi_kpi.asym_predicted());
              varMin.emplace_back(nbdVars_pi0_pi_kpi.asym_min());
              varMax.emplace_back(nbdVars_pi0_pi_kpi.asym_max());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::kpi> &nbdVars_pi0_k_kpi =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                               Daughters::kpi>::Get(id);
              varNames.emplace_back(nbdVars_pi0_k_kpi.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_k_kpi.asym_predicted());
              varMin.emplace_back(nbdVars_pi0_k_kpi.asym_min());
              varMax.emplace_back(nbdVars_pi0_k_kpi.asym_max());
              break;
            }
            case Daughters::kk: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::kk> &nbdVars_pi0_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(nbdVars_pi0_pi_kk.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_pi_kk.asym_predicted());
              varMin.emplace_back(nbdVars_pi0_pi_kk.asym_min());
              varMax.emplace_back(nbdVars_pi0_pi_kk.asym_max());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::kk> &nbdVars_pi0_k_kk =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(nbdVars_pi0_k_kk.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_k_kk.asym_predicted());
              varMin.emplace_back(nbdVars_pi0_k_kk.asym_min());
              varMax.emplace_back(nbdVars_pi0_k_kk.asym_max());
              break;
            }
            case Daughters::pipi: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_pi0_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(nbdVars_pi0_pi_pipi.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_pi_pipi.asym_predicted());
              varMin.emplace_back(nbdVars_pi0_pi_pipi.asym_min());
              varMax.emplace_back(nbdVars_pi0_pi_pipi.asym_max());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::pipi>
                  &nbdVars_pi0_k_pipi =
                      NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(nbdVars_pi0_k_pipi.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_k_pipi.asym_predicted());
              varMin.emplace_back(nbdVars_pi0_k_pipi.asym_min());
              varMax.emplace_back(nbdVars_pi0_k_pipi.asym_max());
              break;
            }
            case Daughters::pik: {
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                           Daughters::pik> &nbdVars_pi0_pi_pik =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::pi,
                                               Daughters::pik>::Get(id);
              varNames.emplace_back(nbdVars_pi0_pi_pik.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_pi_pik.asym_predicted());
              varMin.emplace_back(nbdVars_pi0_pi_pik.asym_min());
              varMax.emplace_back(nbdVars_pi0_pi_pik.asym_max());
              NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                           Daughters::pik> &nbdVars_pi0_k_pik =
                  NeutralBachelorDaughtersVars<Neutral::pi0, Bachelor::k,
                                               Daughters::pik>::Get(id);
              varNames.emplace_back(nbdVars_pi0_k_pik.asym().GetName());
              varPredictions.emplace_back(nbdVars_pi0_k_pik.asym_predicted());
              varMin.emplace_back(nbdVars_pi0_k_pik.asym_min());
              varMax.emplace_back(nbdVars_pi0_k_pik.asym_max());
              break;
            }
          }
          break;
        }
        case Neutral::gamma: {
          switch (d) {
            case Daughters::kpi: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kpi>
                  &nbdVars_gamma_pi_kpi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::kpi>::Get(id);
              varNames.emplace_back(nbdVars_gamma_pi_kpi.asym().GetName());
              varPredictions.emplace_back(
                  nbdVars_gamma_pi_kpi.asym_predicted());
              varMin.emplace_back(nbdVars_gamma_pi_kpi.asym_min());
              varMax.emplace_back(nbdVars_gamma_pi_kpi.asym_max());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::kpi>
                  &nbdVars_gamma_k_kpi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                                   Daughters::kpi>::Get(id);
              varNames.emplace_back(nbdVars_gamma_k_kpi.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_k_kpi.asym_predicted());
              varMin.emplace_back(nbdVars_gamma_k_kpi.asym_min());
              varMax.emplace_back(nbdVars_gamma_k_kpi.asym_max());
              break;
            }
            case Daughters::kk: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::kk> &nbdVars_gamma_pi_kk =
                  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(nbdVars_gamma_pi_kk.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_pi_kk.asym_predicted());
              varMin.emplace_back(nbdVars_gamma_pi_kk.asym_min());
              varMax.emplace_back(nbdVars_gamma_pi_kk.asym_max());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::kk> &nbdVars_gamma_k_kk =
                  NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                               Daughters::kk>::Get(id);
              varNames.emplace_back(nbdVars_gamma_k_kk.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_k_kk.asym_predicted());
              varMin.emplace_back(nbdVars_gamma_k_kk.asym_min());
              varMax.emplace_back(nbdVars_gamma_k_kk.asym_max());
              break;
            }
            case Daughters::pipi: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pipi>
                  &nbdVars_gamma_pi_pipi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(nbdVars_gamma_pi_pipi.asym().GetName());
              varPredictions.emplace_back(
                  nbdVars_gamma_pi_pipi.asym_predicted());
              varMin.emplace_back(nbdVars_gamma_pi_pipi.asym_min());
              varMax.emplace_back(nbdVars_gamma_pi_pipi.asym_max());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::pipi>
                  &nbdVars_gamma_k_pipi =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                                   Daughters::pipi>::Get(id);
              varNames.emplace_back(nbdVars_gamma_k_pipi.asym().GetName());
              varPredictions.emplace_back(
                  nbdVars_gamma_k_pipi.asym_predicted());
              varMin.emplace_back(nbdVars_gamma_k_pipi.asym_min());
              varMax.emplace_back(nbdVars_gamma_k_pipi.asym_max());
              break;
            }
            case Daughters::pik: {
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                           Daughters::pik>
                  &nbdVars_gamma_pi_pik =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::pi,
                                                   Daughters::pik>::Get(id);
              varNames.emplace_back(nbdVars_gamma_pi_pik.asym().GetName());
              varPredictions.emplace_back(
                  nbdVars_gamma_pi_pik.asym_predicted());
              varMin.emplace_back(nbdVars_gamma_pi_pik.asym_min());
              varMax.emplace_back(nbdVars_gamma_pi_pik.asym_max());
              NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                           Daughters::pik>
                  &nbdVars_gamma_k_pik =
                      NeutralBachelorDaughtersVars<Neutral::gamma, Bachelor::k,
                                                   Daughters::pik>::Get(id);
              varNames.emplace_back(nbdVars_gamma_k_pik.asym().GetName());
              varPredictions.emplace_back(nbdVars_gamma_k_pik.asym_predicted());
              varMin.emplace_back(nbdVars_gamma_k_pik.asym_min());
              varMax.emplace_back(nbdVars_gamma_k_pik.asym_max());
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
                   std::string &varName, double varPredicted, double varMin,
                   double varMax) {
  TTreeReaderValue<double> var(reader, varName.c_str());
  TTreeReaderValue<double> varErr(reader, (varName + "_Err").c_str());
  TTreeReaderValue<double> edm(reader, "EDM");
  TTreeReaderValue<int> covQual(reader, "covQual");
  TTreeReaderValue<int> fitStatus(reader, "fitStatus");

  TFile histFile((inputDir + "/Hist_" + varName + ".root").c_str(), "recreate");

  TH1D varHist((varName + "_hist").c_str(), (varName + "_hist").c_str(), 40,
               varPredicted - varPredicted * 5,
               varPredicted + varPredicted * 5);
  TH1D varErrHist((varName + "_err_hist").c_str(),
                  (varName + "_err_hist").c_str(), 40, 0,
                  (varMax - varMin) / 20);
  TH1D varPullHist((varName + "_pull_hist").c_str(),
                   (varName + "_pull_hist").c_str(), 40, -10, 10);
  // number of unconverged, forced positive definite, or MINOS problemed fits
  int nUnConv = 0;
  int nFPD = 0;
  int nMINOS = 0;

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
      varPullHist.Fill((*var - varPredicted) / *varErr);
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
  std::vector<double> varPredictions, varMin, varMax;

  ExtractVarProperties(neutralVec, daughtersVec, varNames, varPredictions,
                       varMin, varMax);

  for (unsigned int i = 0; i < varNames.size(); ++i) {
    std::string varName = varNames[i].substr(0, varNames[i].size() - 2);
    std::string tree = varName + "_tree";
    TChain chain(tree.c_str());
    chain.Add((inputDir + "/Tree_" + varName + "_*.root").c_str());
    TTreeReader reader(&chain);
    PlotVariables(inputDir, chain, reader, varName, varPredictions[i], varMin[i],
                  varMax[i]);
  }
}
