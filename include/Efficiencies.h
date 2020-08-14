#pragma once
#include "Configuration.h"
#include "TTree.h"
#include "TFile.h"

enum class Efficiency {
  buEff,
  buEffErr,
  deltaEff,
  deltaEffErr,
  buPartialEff,
  buPartialEffErr,
  orEff,
  orEffErr,
  mcEff,
  mcEffErr
};

bool fexists(std::string const &filename);
std::vector<std::string> SplitLine(std::string const &str);
void CalcBinomialErr(double nInit, double nFinal, double &err);
double ReturnMCEffs(Mode mode, Neutral neutral, Bachelor bachelor,
                   Efficiency eff);
void ExtractChain(Mode mode, Bachelor bachelor, TChain &chain, bool D02pik);
double ReturnBoxEffs(Mode mode, Bachelor bachelor, Efficiency efficiency,
                   bool misId);
void SaveEffToTree(Configuration &config, TFile &outputFile, TTree &tree,
                   Mode mode);
