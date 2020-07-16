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

#include "Configuration.h"
#include "Fitting.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "Params.h"
#include "ParseArguments.h"
#include "Pdf.h"

#include "Plotting.h"
#include "Fitting.h"

void ToyTestD1D(std::unique_ptr<RooSimultaneous> &simPdf,
                std::unique_ptr<RooFitResult> &dataFitResult,
                Configuration &config,
                std::vector<Daughters> const &daughtersVec,
                std::vector<Charge> const &chargeVec,
                std::string const &outputDir, int nToys);
