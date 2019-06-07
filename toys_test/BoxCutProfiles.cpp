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

bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

std::string formatString(std::string s) {
  std::replace(s.begin(), s.end(), '_', '-');
  return s;
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
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.03, "YZ");
  gStyle->SetLabelSize(0.035, "X");
  gStyle->SetTitleOffset(1.5, "X");
  gStyle->SetTitleOffset(1.5, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPadBottomMargin(0.11);
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

  double yieldMin = -1000000.0;
  double yieldMax = 1000000.0;
  double errMin = -1000000.0;
  double errMax = 1000000.0;
  double percErrMin = -1000000.0;
  double percErrMax = 1000000.0;

  for (unsigned int d = 0; d < delta_bins; ++d) {
    for (unsigned int b = 0; b < delta_bins; ++b) {
      std::string resultName =
          "Result_" + delta_low_high[d] + "_" + bu_low_high[b];
      std::string fileName = path + "/1d_results/" + resultName + ".root";
      // Open file
      if (fexists(fileName)) {
        auto file = std::unique_ptr<TFile>(TFile::Open(fileName.c_str()));
        // Extract RooFitResult
        auto result =
            std::unique_ptr<RooFitResult>(dynamic_cast<RooFitResult *>(
                file->FindObjectAny(resultName.c_str())));
        // Check exists
        if (result == nullptr) {
          throw std::runtime_error("Could not extract result from " + fileName);
        } else {
          std::cout << "Extracted result from " << fileName << "\n";
          // Extract tree containing true error
          auto tree = std::unique_ptr<TTree>(
              dynamic_cast<TTree *>(file->FindObjectAny("tree")));
          // Check exists
          if (tree == nullptr) {
            throw std::runtime_error("Could not extract tree from " + fileName);
          } else {
            std::cout << "Extracted tree from " << fileName << "\n";
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
              RooAbsArg *yieldAbsArg = finalPars.find("yieldTotSignal");
              RooRealVar *yieldRealVar =
                  dynamic_cast<RooRealVar *>(yieldAbsArg);
              double yieldVal = yieldRealVar->getVal();

              // Get corrected error from tree
              double yieldErr;
              tree->SetBranchAddress("errYieldTotSignal", &yieldErr);
              tree->GetEntry(0);

              // Replace _ with - in window string for axis labels
              std::string xLabel = formatString(bu_low_high[b]);
              std::string yLabel = formatString(delta_low_high[d]);
              // Fill histograms with x and y axis labelled with box dimensions
              yieldHist.Fill(xLabel.c_str(), yLabel.c_str(),
                             yieldVal);
              errHist.Fill(xLabel.c_str(), yLabel.c_str(),
                           yieldErr);
              double percErr = yieldVal / yieldErr * 100;
              percErrHist.Fill(xLabel.c_str(),
                               yLabel.c_str(),
                               percErr);

              // Set max and min values in order to set z range in TH2s
              // (otherwise starts from 0)
              if (yieldVal > yieldMax) {
                yieldMax = yieldVal;
              }
              if (yieldVal < yieldMin) {
                yieldMin = yieldVal;
              }
              if (yieldErr > errMax) {
                errMax = yieldErr;
              }
              if (yieldErr < errMin) {
                errMin = yieldErr;
              }
              if (percErr > percErrMax) {
                percErrMax = percErr;
              }
              if (percErr < percErrMin) {
                percErrMin = percErr;
              }
            }
          }
        }
      } else {
        std::cout << fileName << " does not exist\n";
      }
    }
  }

  std::cout << "\nQuality of fits:\n"
            << "Unconverged: " << nUnConv / bu_bins * delta_bins * 100 << " %\n"
            << "Forced positive definite: " << nFPD / bu_bins * delta_bins * 100
            << " %\n"
            << "MINOS problems: " << nMINOS / bu_bins * delta_bins * 100
            << " %\n";

  TCanvas yieldCanvas("yieldCanvas", "", 1500, 1000);

  yieldHist.GetXaxis()->SetTitle("(m[B^{#pm}] - m[D^{*0}]) Window MeV/c^{2}");
  yieldHist.GetYaxis()->SetTitle("(m[D^{*0}] - m[D^{0}]) Window MeV/c^{2}");
  yieldHist.GetZaxis()->SetTitle("Signal Yield");
  double yieldRange = yieldMax - yieldMin;
  yieldHist.GetZaxis()->SetRangeUser(yieldMin - yieldRange / 5,
                                     yieldMax + yieldRange / 5);
  yieldHist.SetTitle(" ");
  yieldHist.SetStats(0);
  yieldHist.Draw("colz");

  yieldCanvas.SaveAs((path + "/YieldBoxScan.pdf").c_str());

  TCanvas errCanvas("errCanvas", "", 1500, 1000);

  errHist.GetXaxis()->SetTitle("(m[B^{#pm}] - m[D^{*0}]) Window MeV/c^{2}");
  errHist.GetYaxis()->SetTitle("(m[D^{*0}] - m[D^{0}]) Window MeV/c^{2}");
  errHist.GetZaxis()->SetTitle("Signal Yield Error");
  double errRange = errMax - errMin;
  errHist.GetZaxis()->SetRangeUser(errMin - errRange / 5,
                                   errMax + errRange / 5);
  errHist.SetTitle(" ");
  errHist.SetStats(0);
  errHist.Draw("colz");

  errCanvas.SaveAs((path + "/ErrBoxScan.pdf").c_str());

  TCanvas percErrCanvas("percErrCanvas", "", 1500, 1000);

  percErrHist.GetXaxis()->SetTitle("(m[B^{#pm}] - m[D^{*0}]) Window MeV/c^{2}");
  percErrHist.GetYaxis()->SetTitle("(m[D^{*0}] - m[D^{0}]) Window MeV/c^{2}");
  percErrHist.GetZaxis()->SetTitle("Signal Yield \% Error");
  double percErrRange = percErrMax - percErrMin;
  percErrHist.GetZaxis()->SetRangeUser(percErrMin - percErrRange / 5,
                                       percErrMax + percErrRange / 5);
  percErrHist.SetTitle(" ");
  percErrHist.SetStats(0);
  percErrHist.Draw("colz");

  percErrCanvas.SaveAs((path + "/PercErrBoxScan.pdf").c_str());

  return 1;
}
