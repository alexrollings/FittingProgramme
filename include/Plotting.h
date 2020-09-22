#pragma once
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "RooHistPdf.h"
#include "RooMCStudy.h"
#include "RooNumIntConfig.h"
#include "RooPlot.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
// #include "TMathText.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TPaveLabel.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTree.h"
#include "TTreeReader.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

#include "Configuration.h"
#include "Fitting.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"
#include "ParseArguments.h"
#include "Pdf.h"

void SetStyle();
void LaTeXYields(Configuration &config, std::vector<PdfBase *> &pdfs,
                 std::string &outputDir, std::unique_ptr<RooFitResult> &result);
void PlotComponent(
    Mass mass, RooRealVar &var, PdfBase &pdf, RooAbsData const &fullDataSet,
    RooSimultaneous const &simPdf, TLegend &legend, TLegend &labels,
    std::string const &outputDir, Configuration &config,
    std::map<std::string, std::map<std::string, Color_t> > &colorMap,
    std::map<Neutral, std::map<Mass, double> > &yMaxMap);
void Plotting1D(int const id, PdfBase &pdf, Configuration &config,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                std::string const &outputDir, RooFitResult *result,
                std::map<Neutral, std::map<Mass, double> > &yMaxMap);
void Plotting2D(RooDataSet &dataSet, int const id, PdfBase &pdf,
                Configuration &config, std::string const &outputDir,
                std::string const &label);
void PlotCorrelations(RooFitResult *result, std::string const &outputDir,
                      Configuration &config);
