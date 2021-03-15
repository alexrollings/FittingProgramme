#pragma once
#include "Configuration.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <experimental/filesystem>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TAxis.h"
#include "TLine.h"
#include "TStyle.h"
#include "TH1.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "RooHist.h"
#include "RooFitResult.h"
#include "RooArgList.h"
#include "RooAbsArg.h"

bool fexists(std::string const &filename);
std::string to_string_with_precision(double value);
void AppendFiles(Mode mode, Configuration &config, std::vector<std::string> &input);
void SetupTChain(Configuration &config, TChain &chain,
                 std::vector<std::string> const &input);
void MakeMapFittingDataSet(
    Configuration &config, RooDataSet &dataset,
    std::map<std::string, RooDataSet *> &mapFittingDataSet);
void MakeCombDataSet(Configuration &config, RooDataSet &dataset,
                     RooDataSet &combData);
void CalcBinomialErr(double eff, double nInit, double &err);
double ReturnBoxEff(Mode mode, Configuration &config, Efficiency eff);
void PlotComponent(RooAbsPdf *totPdf, Configuration &config,
                   std::unique_ptr<RooDataSet> &fullDataSet, Mass mass,
                   std::unique_ptr<RooPlot> &frame,
                   std::unique_ptr<RooPlot> &pullFrame, bool fitBool,
                   bool plotAll);
void PlotOnCanvas(RooAbsPdf *totPdf, Configuration &config,
                  std::unique_ptr<RooDataSet> &fullDataSet, bool fitBool,
                  bool plotAll, std::string const &foutName);
void SaveResult(std::unique_ptr<RooFitResult> &fitResult,
                Configuration &config, std::string const &foutName);
