#include <regex>
#include <iomanip>
#include <experimental/filesystem>

#include "RooRealVar.h"
#include "RooSimultaneous.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCategory.h"
#include "RooPlotable.h"
#include "RooHist.h"
#include "TTreeReader.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TStyle.h"
#include "TFile.h"
#include "TLine.h"
#include "TPad.h"

enum class Variable { bu, delta };
std::string EnumToString(Variable variable);

enum class Efficiency { deltaCutEff, buCutEff, orEff, boxEff };

void AppendFiles(std::vector<std::string> &input);
void SetupTChain(TChain &chain,
                 std::vector<std::string> const &input);
bool fexists(std::string const &filename);

void PlotCorrMatrix(RooFitResult *result, std::string const &outputDir,
                    std::string const &box_bu_low,
                    std::string const &box_bu_high,
                    std::string const &box_delta_low,
                    std::string const &box_delta_high);
void PlotComponent(Variable variable, RooRealVar &var, RooDataHist *dataHist,
                   RooSimultaneous &simPdf, RooCategory &fitting,
                   RooAddPdf &sig, RooAbsPdf &bkg, std::string const &outputDir,
                   std::string const &box_bu_low,
                   std::string const &box_bu_high,
                   std::string const &box_delta_low,
                   std::string const &box_delta_high);
void Plotting2D(RooRealVar &buMass, RooRealVar &deltaMass,
                RooDataHist *dataHist, RooAddPdf &pdf,
                std::string const &outputDir);

double ReturnBoxEff(Efficiency eff, std::string const &dlString,
                    std::string const &dhString, std::string const &blString,
                    std::string const &bhString);
void CalcBinomialErr(double eff, double nInit, double &err);
std::vector<std::string> SplitLine(std::string const &str);
