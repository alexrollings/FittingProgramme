#include "RooRealVar.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TPad.h"
#include "TStyle.h"
#include "TChain.h"
#include "TH1.h"
#include "TTreeReader.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

void PlotVariables(TChain &chain, TTreeReader &reader, std::string &varName,
                   double &varPrediction) {
  TTreeReaderValue<double> var(reader, varName.c_str());
  TTreeReaderValue<double> varErr(reader, (varName + "Err").c_str());
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

  TFile histFile(
      ("/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/results/Hist_" +
       varName + ".root")
          .c_str(),
      "recreate");

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
      varPullHist.Fill((*var - varPrediction) / *varErr);
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
  varCanvas.SaveAs(("/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/"
                    "results/ValErrPull_" +
                    varName + ".pdf")
                       .c_str());
}

int main(int argc, char **argv) {
  std::vector<std::string> varNames;
  std::vector<double> varPredictions;

  varNames.emplace_back("a0Mean");
  varNames.emplace_back("a1Mean");
  varNames.emplace_back("a2Mean");

  double a0MeanBuSignal_init = 5101.86875;
  double a1MeanBuSignal_init = 2.1375;
  double a2MeanBuSignal_init = -0.0062;
  varPredictions.emplace_back(a0MeanBuSignal_init);
  varPredictions.emplace_back(a1MeanBuSignal_init);
  varPredictions.emplace_back(a2MeanBuSignal_init);

  for (unsigned int i = 0; i < varNames.size(); ++i) {
    TChain chain("tree");
    chain.Add(
        "/home/rollings/Bu2Dst0h_2d/FittingProgramme/toys_test/results/"
        "TreeFile_*.root");
    std::cout << "Plotting for " << chain.GetEntries() << " toys.\n";
    TTreeReader reader(&chain);
    PlotVariables(chain, reader, varNames[i], varPredictions[i]);
  }

  return 1;
}
