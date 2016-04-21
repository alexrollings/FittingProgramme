#include <iostream>
#include <sstream>
#include <stdexcept>

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

  RooCategory chargeCat("chargeCat", "chargeCat");
  chargeCat.defineType("minus");
  chargeCat.defineType("plus");

  // ------------- IGNORE FOR NOW --------------------
  // declare vector to store fileName options
  // std::vector<std::string> polarity_fn;
  // -------------------------------------------------

  // Declare strings to hold category options
  std::string polarity;
  std::string charge;

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
  // Put all arguments generally as inputs to function (to make it general to
  // gamma mode)
  RooRealVar Bu_M("Pi0_Bu_M_DTF_D0Pi0", "Pi0_Bu_M_DTF_D0Pi0", 4979, 5701,
                  "Mev/c^2");
  RooRealVar Bu_ID("Pi0_Bu_ID", "Pi0_Bu_ID", -550, 550, "");

  // Create separate RooArgSets for variables and categories
  RooArgSet varArgSet;
  varArgSet.add(Bu_M);
  varArgSet.add(Bu_ID);

  RooArgSet catArgSet;
  catArgSet.add(polarityCat);
  catArgSet.add(chargeCat);

  // Create DataSet and feed it the ArgSet, which defines how many columns it
  // should have
  TFile dataFile(filePath + fileName);
  // ---------------------- CAST STUFF ----------------------
  // Get takes a TObject pointer and casts it as a ttree pointer
  // This makes sense as the dataFile contains a ttree
  // All it does it take an address of a TOBject and force it to be that of a
  // ttree
  // General casts:
  // static_cast - type conversions / up cast pointers (TTree pointer to Object
  // pointer as TTree inherits from object).
  // dynamic_cast - takes a higher inheritance level pointer and tries to
  // conveert it to a lower level pointer. Will fail if the object is not
  // actually a ttree. Returns a null pointer if not (after you use dynamic
  // cast, check pointer isn't null and throw an error if it is).
  // const_cast - strips away a const.
  // reinterpret_cast - takes a ptr and pretends it points to something
  // else but doesn't cast the TYPE of the ptr.
  // --------------------------------------------------------
  TTree *tree = dynamic_cast<TTree *>(dataFile.Get(ttree));
  if (tree == nullptr) {
    // exception throws and handles errors. Use them when something UNINTENDED
    // happens.
    throw std::runtime_error("File did not contain a TTree.");
  }

  std::cout << "Loading tree " << ttree << " from file " << filePath + fileName
            << "\n";

  // Create data set for our ttree variables
  RooDataSet inputDataSet("inputDataSet", "Input Data Set", tree, varArgSet);

  // Create data set to store categories
  RooDataSet extraDataSet("extraDataSet", "Category Data Set", catArgSet);

  // Loop over data set, find RooCategory for each event and set it's label
  for (int i = 0; i < inputDataSet.numEntries(); i++) {
    // RooDataSet::get() returns a const pointer to a RooArgSet for event i (why
    // we must use RooArgSet not RooArgList)
    RooArgSet const *row = inputDataSet.get(i);
    // TString has an automatic converter to const char* array. String doesn't.
    // RooAbsArg::find() finds object with name in list. Null pointer returned
    // if the name isn't found
    RooRealVar *pBu_ID = dynamic_cast<RooRealVar *>(row->find(Bu_ID.GetName()));
    if (pBu_ID == nullptr) {
      std::stringstream output;
      output << "No value for Bu_ID for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    if (pBu_ID->getVal() < 0) {
      charge = "minus";
    } else if (pBu_ID->getVal() > 0) {
      charge = "plus";
    };

    // SetRooCategory labels for each event
    polarityCat.setLabel(polarity.c_str());
    chargeCat.setLabel(charge.c_str());
    // Adding the categories to RooArgSet added a pointer to the value's memory
    // address. Therefore changing their values changes changes what is stored
    // in catArgSet.

    // Add category labels to 'extra' data set
    extraDataSet.add(catArgSet);
    // Add here copies the values from rooArgSet
  }

  // Merge data set containing variables with that containing categories
  inputDataSet.merge(&extraDataSet);

  // Check assignment of categories has worked by looping over the new data set
  // and printng the values for each event
  for (int i = 0; i < inputDataSet.numEntries(); i++) {

    RooArgSet const *row = inputDataSet.get(i);

    RooRealVar *pBu_M = dynamic_cast<RooRealVar *>(row->find(Bu_ID.GetName()));
    if (pBu_M == nullptr) {
      std::stringstream output;
      output << "No value for Bu_M for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooRealVar *pBu_ID = dynamic_cast<RooRealVar *>(row->find(Bu_ID.GetName()));
    if (pBu_ID == nullptr) {
      std::stringstream output;
      output << "No value for Bu_ID for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooCategory *ppolarity =
        dynamic_cast<RooCategory *>(row->find(polarityCat.GetName()));
    if (ppolarity == nullptr) {
      std::stringstream output;
      output << "No value for the polarity for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooCategory *_charge =
        dynamic_cast<RooCategory *>(row->find(chargeCat.GetName()));
    if (pcharge == nullptr) {
      std::stringstream output;
      output << "No value for the charge for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    std::cout << "For event " << i << " ...  m[Bu] = " << pBu_M->getVal()
              << " ... polarity = " << ppolarity->getLabel()
              << " ... Bu_ID = " << pBu_ID->getVal()
              << " ... charge = " << pcharge->getLabel() << "\n";
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
