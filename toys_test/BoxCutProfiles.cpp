#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TTreeReader.h"

std::vector<std::string> SplitByComma(std::string const &str) {
  std::stringstream ss;
  ss.str(str);
  std::string tempString;
  std::vector<std::string> stringVector;
  // '' = char
  while (std::getline(ss, tempString, ',')) {
    stringVector.emplace_back(tempString);
  }
  return stringVector;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Pass path to input and output directories, and comma "
                 "separated list of box dimensions in delta and bu, with an _ "
                 "separating the lower and upper bounds.\n";
    return 1;
  }
  std::string path = argv[1];
  std::vector<std::string> delta_low_high = SplitByComma(argv[2]);
  std::vector<std::string> bu_low_high = SplitByComma(argv[3]);

  unsigned int delta_bins = delta_low_high.size();
  unsigned int bu_bins = bu_low_high.size();

  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetTitleSize(0.06, "Z");
  gStyle->SetTitleSize(0.04, "XY");
  gStyle->SetLabelSize(0.03, "Y");
  gStyle->SetLabelSize(0.035, "X");
  gStyle->SetTitleOffset(0.9, "X");
  gStyle->SetTitleOffset(0.9, "Y");
  gStyle->SetTitleOffset(0.9, "Z");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.1);

  TH2D yieldHist("yieldHist", "", bu_bins, 0, bu_bins, delta_bins, 0,
                 delta_bins);
  TH2D errHist("errHist", "", bu_bins, 0, bu_bins, delta_bins, 0, delta_bins);
  TH2D percErrHist("precentageErrHist", "", bu_bins, 0, bu_bins, delta_bins, 0,
                   delta_bins);

  // Check result quality and print out stats
  double nUnConv = 0;
  double nFPD = 0;
  double nMINOS = 0;

  for (unsigned int d = 0; d < delta_bins; ++d) {
    for (unsigned int b = 0; b < delta_bins; ++b) {
      std::string filename = path + "/1d_results/Result_" + delta_low_high[d] +
                             "_" + bu_low_high[b] + ".root";
      // Open file
      auto file = std::unique_ptr<TFile>(TFile::Open(filename.c_str()));
      // Extract RooFitResult
      auto result = std::unique_ptr<RooFitResult>(
          dynamic_cast<RooFitResult *>(file->FindObjectAny(filename.c_str())));
      // Check exists
      if (result == nullptr) {
        throw std::runtime_error("Could not extract result from " + filename);
      } else {
        std::cout << "Extracted result from " << filename << "\n";
        // Extract tree containing true error
        auto tree = std::unique_ptr<TTree>(
            dynamic_cast<TTree *>(file->FindObjectAny("tree")));
        // Check exists
        if (tree == nullptr) {
          throw std::runtime_error("Could not extract tree from " + filename);
        } else {
          std::cout << "Extracted tree from " << filename << "\n";
          // Check fit quality
          double fitStatus = result->status();
          double covQual = result->covQual();
          if (covQual < 2) {
            nUnConv++;
          } else if (covQual < 3) {
            nFPD++;
          } else if (fitStatus != 0) {
            nMINOS++;
          } else {
            // Extract total yield from result
            RooArgList finalPars = result->floatParsFinal();
            auto yieldAbsArg =
                std::unique_ptr<RooAbsArg>(finalPars.find("yieldTotSignal"));
            auto yieldRealVar = std::unique_ptr<RooRealVar>(
                dynamic_cast<RooRealVar *>(yieldAbsArg.get()));
            double yieldVal = yieldRealVar->getVal();

            // Get corrected error from tree
            double yieldErr;
            tree->SetBranchAddress("errYieldTotSignal", &yieldErr);
            tree->GetEntry(0);

            // Fill histograms with x and y axis labelled with box dimensions
            yieldHist.Fill(bu_low_high[b].c_str(),
                           delta_low_high[d].c_str(), yieldVal);
            errHist.Fill(bu_low_high[b].c_str(), delta_low_high[d].c_str(),
                         yieldErr);
            percErrHist.Fill(bu_low_high[b].c_str(), delta_low_high[d].c_str(),
                             yieldVal / yieldErr * 100);
          }
        }
      }
    }
  }

  std::cout << "\nQuality of fits:\n"
            << "Unconverged: " << nUnConv / bu_bins * delta_bins * 100 << " %\n"
            << "Forced positive definite: " << nFPD / bu_bins * delta_bins * 100
            << " %\n"
            << "MINOS problems: " << nMINOS / bu_bins * delta_bins * 100 << " %\n";

  TCanvas yieldCanvas("yieldCanvas", "", 1000, 1000);

  yieldHist.GetXaxis()->SetTitle("(m[B^{#pm}] - m[D^{*0}]) Window MeV/c^{2}");
  yieldHist.GetYaxis()->SetTitle("(m[D^{*0}] - m[D^{0}]) Window MeV/c^{2}");
  yieldHist.GetZaxis()->SetTitle("Yield");
  yieldHist.SetTitle(" ");
  yieldHist.SetStats(0);
  yieldHist.Draw("colz");

  yieldCanvas.SaveAs((path + "YieldBoxScan.pdf").c_str());

  TCanvas errCanvas("errCanvas", "", 1000, 1000);

  errHist.GetXaxis()->SetTitle("(m[B^{#pm}] - m[D^{*0}]) Window MeV/c^{2}");
  errHist.GetYaxis()->SetTitle("(m[D^{*0}] - m[D^{0}]) Window MeV/c^{2}");
  errHist.GetZaxis()->SetTitle("Error");
  errHist.SetTitle(" ");
  errHist.SetStats(0);
  errHist.Draw("colz");

  errCanvas.SaveAs((path + "ErrBoxScan.pdf").c_str());

  TCanvas percErrCanvas("percErrCanvas", "", 1000, 1000);

  percErrHist.GetXaxis()->SetTitle("(m[B^{#pm}] - m[D^{*0}]) Window MeV/c^{2}");
  percErrHist.GetYaxis()->SetTitle("(m[D^{*0}] - m[D^{0}]) Window MeV/c^{2}");
  percErrHist.GetZaxis()->SetTitle("\% Error");
  percErrHist.SetTitle(" ");
  percErrHist.SetStats(0);
  percErrHist.Draw("colz");

  percErrCanvas.SaveAs((path + "percErrBoxScan.pdf").c_str());

  return 1;
}
