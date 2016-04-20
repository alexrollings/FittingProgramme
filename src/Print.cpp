#include <iostream>

#include "RooArgList.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooRealVar.h"

#include "TFile.h"
#include "TTree.h"

enum class Polarity { up, down, both };

using namespace RooFit;

TString filePath("/data/lhcb/users/rollings/ButoDst0X_DATA_1/");
TString fileName("2011_MagDown/"
                 "2011_MagDown_ButDst0pi_Dst0tD0pi0_D0tkpi_Selections_"
                 "MERemoved.root");
TString ttree("BtoDstar0h3_h1h2pi0RTuple");

// ------------- IGNORE FOR NOW --------------------
// Create function that takes a directory as input then outputs a list of
// fileNames from the directory
// void GetfileNames(std::string directory, std::vector<std::string> &fileNames)
// {
// Ask JOJ best way to do this!
// }
// -------------------------------------------------

void LoadDataSet(Polarity myPolarity) {

  // Initialise RooCategories
  RooCategory polarityCat("polarityCat", "polarityCat");
  polarityCat.defineType("up");
  polarityCat.defineType("down");
  polarityCat.defineType("both");

  // ------------- IGNORE FOR NOW --------------------
  // declare vector to store fileName options
  // std::vector<std::string> polarity_fn;
  // -------------------------------------------------

  std::string polarity;

  // Set fileName and RooCategory options
  if (myPolarity == Polarity::up) {
    // polarity_fn.push_back("MagUp");
    polarity = "up";
  } else if (myPolarity == Polarity::down) {
    // polarity_fn.push_back("MagDown");
    polarity = "down";
  } else if (myPolarity == Polarity::both) {
    // polarity_fn.push_back("MagUp");
    // polarity_fn.push_back("MagDown");
    polarity = "both";
  }

  // Create RooRealVars: any variables we are interested in
  RooRealVar Bu_M("Pi0_Bu_M_DTF_D0Pi0", "Pi0_Bu_M_DTF_D0Pi0", 4979, 5701,
                  "Mev/c^2");

  // Create RooArgSet and add RooAbsArg type variables (could be var's or
  // catagories) that we will need
  RooArgSet ArgSet;
  ArgSet.add(Bu_M);
  ArgSet.add(polarityCat);
  // Create DataSet and feed it the ArgSet, which defines how many columns it
  // should have (therefore need to include categories in ArgSet)
  TFile dataFile(filePath + fileName);
  TTree *tree = (TTree *)dataFile.Get(ttree);
  std::cout << "Loading tree " << ttree << " from file " << filePath + fileName
            << "\n";
  RooDataSet dataSet("dataSet", "dataSet", tree, ArgSet);

  // Loop over data set, find RooCategory for each event and set it's label

  for (int i = 0; i < dataSet.numEntries(); i++) {
    // RooDataSet::get() returns a const pointer to a RooArgSet for event i (why
    // we must use RooArgSet not RooArgList)
    const RooArgSet *row = dataSet.get(i);
    // RooAbsArg::find() finds object with name in list. Null pointer returned
    // if the name isn't found
    RooCategory *_polarity = (RooCategory *)row->find("polarityCat");
    _polarity->setLabel(polarity.c_str());
    RooRealVar *_Bu_M = (RooRealVar *)row->find(Bu_M.GetName());

    std::cout << "For event " << i << " ...  m[Bu] = " << _Bu_M->getVal()
              << " ... polarity = " << _polarity->getLabel() << "\n";
  }

  // ------------- IGNORE FOR NOW --------------------
  // give fileName to second argument of GetfileNames function
  // std::vector<std::string> fileName;

  // for (auto it = fileName.begin(), itEnd = fileName.end(); it != itEnd; ++it)
  // {
  // if((*it).find("filestring")
  // TFile* dataFile = TFile::Open(fullpathandname.c_str());
  // TString ttree("BtoDstar0h3_h1h2pi0RTuple");
  // TTree* myTree = (TTree*)dataFile.Get(ttree);
  // RooDataSet* tempDataSet = new RooDataSet("temp", "temp", inputList, ttree);
  // DataSet.append(*tempDataSet);
  // delete tempDataSet;
  // }
  // -------------------------------------------------
}

int main(int argc, char **argv) {
  TString polarityInput = argv[1];

  Polarity myPolarity;

  if (polarityInput == "up") {
    myPolarity = Polarity::up;
  } else if (polarityInput == "down") {
    myPolarity = Polarity::down;
  }

  LoadDataSet(myPolarity);
  return 0;
}
