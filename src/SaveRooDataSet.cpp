#include <iostream>
#include <sstream>
#include <stdexcept>

#include "RooArgList.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooFormula.h"
#include "RooFormulaVar.h"
#include "RooRealVar.h"

#include "TFile.h"
#include "TTree.h"

#include "Configuration.h"

std::string dsPath("/home/rollings/ButoDst0X_FIT/roodatasets/");
// std::string dsPath("~/Desktop/FittingProgramme/roodatasets/");

void SaveRooDataSet(std::string const &path, Year myYear, Polarity myPolarity,
                    Bachelor myBachelor, Neutral myNeutral,
                    Daughters myDaughters) {

  // using namespace RooFit;

  // StaticVars::polarityCat() is a function returning a const reference to
  // polarityCat_ stored in StaticVars
  // Then we invoke the RooCategory constructor using this const reference,
  // thereby creating a copy of it using the copy constructor
  // So you end up copying polarityCat_ in StaticVars to your local variable
  // polarityCat
  // We can now overwrite the copied value as it exists only in our local scope
  // We can then pass the values around as we like (e.g. assign to RooDataSet)

  // Static functions are associated to the class not a object (:: not .)
  // Passing arguments by reference calls te copy constructor for RooCategory
  // This ensures a deep copy as it knows how big the class is, therefore it
  // copies the object from its initial memory location to a new one
  // This ensures the original object still exists when the new one goes out of
  // scope (as the destructor would then be called)

  // Declare strings to hold category options
  std::string year;
  std::string polarity;
  std::string bachelor;
  std::string neutral;
  std::string daughters;
  std::string charge;
  std::string fitting;
  std::string ttree;

  // Set fileName and RooCategory options
  year = EnumToString(myYear);

  polarity = EnumToString(myPolarity);

  bachelor = EnumToString(myBachelor);

  neutral = EnumToString(myNeutral);
  if (myNeutral == Neutral::pi0) {
    ttree = "BtoDstar0h3_h1h2pi0RTuple";
  } else if (myNeutral == Neutral::gamma) {
    ttree = "BtoDstar0h3_h1h2gammaTuple";
  }

  daughters = EnumToString(myDaughters);

  fitting = ComposeName(myNeutral, myBachelor, myDaughters);
  // Initialise RooRealVars now neutral has been specified
  Configuration &config = Configuration::Get();
  Configuration::Categories &categories = Configuration::Get().categories();

  // Create DataSet and feed it the ArgSet, which
  // defines how many columns it
  // should have
  TFile dataFile(path.c_str());
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
  TTree *tree = dynamic_cast<TTree *>(dataFile.Get(ttree.c_str()));
  if (tree == nullptr) {
    // exception throws and handles errors. Use them when something UNINTENDED
    // happens.
    throw std::runtime_error("File did not contain a TTree.");
  }

  std::cout << "Loading tree " << ttree << " from file " << path << "\n";

  // Create data set for our ttree variables
  RooDataSet inputDataSet("inputDataSet", "Input Data Set", tree,
                          config.variableArgSet());

  // Create data set to store categories
  RooDataSet extraDataSet("extraDataSet", "Category Data Set",
                          config.categoryArgSet());

  std::cout << "Finished loading tree.\n";

  // Loop over data set, find RooCategory for each event and set it's label
  for (int i = 0; i < inputDataSet.numEntries(); i++) {
    // RooDataSet::get() returns a const pointer to a RooArgSet for event i (why
    // we must use RooArgSet not RooArgList)
    RooArgSet const *row = inputDataSet.get(i);
    // TString has an automatic converter to const char* array. String doesn't.
    // RooAbsArg::find() finds object with name in list. Null pointer returned
    // if the name isn't found
    RooRealVar *idBuPtr =
        dynamic_cast<RooRealVar *>(row->find(config.buPdgId().GetName()));
    if (idBuPtr == nullptr) {
      std::stringstream output;
      output << "No value for ID[Bu] for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    if (idBuPtr->getVal() < 0) {
      charge = "minus";
    } else if (idBuPtr->getVal() > 0) {
      charge = "plus";
    };

    // Adding the categories to RooArgSet added a pointer to the value's memory
    // address. Therefore changing their values changes changes what is stored
    // in catArgSet.
    categories.year.setLabel(year.c_str());
    categories.polarity.setLabel(polarity.c_str());
    categories.bachelor.setLabel(bachelor.c_str());
    categories.neutral.setLabel(neutral.c_str());
    categories.daughters.setLabel(daughters.c_str());
    categories.charge.setLabel(charge.c_str());
    categories.fitting.setLabel(fitting.c_str());

    // Add category labels to 'extra' data set
    extraDataSet.add(config.categoryArgSet());
    // Add here copies the values from rooArgSet
  }

  std::cout << "exited loop" << std::endl;
  // Merge data set containing variables with that containing categories
  inputDataSet.merge(&extraDataSet);

  RooDataSet *plusDataSet =
      dynamic_cast<RooDataSet *>(inputDataSet.reduce("charge==charge::plus"));

  RooDataSet *reducedPlusDataSet = dynamic_cast<RooDataSet *>(plusDataSet->reduce(config.fullArgSet()));
  std::cout << "PlusDataSet contains variables: ";
  reducedPlusDataSet -> printArgs(std::cout);
  std::cout << "\n";
 
  std::string dsPlusFileName =
      ComposeFilename(myYear, myPolarity, myBachelor, myNeutral, myDaughters,
                      Charge::plus) +
      ".root";
  std::cout << "Saving data set to file: " << dsPath + dsPlusFileName << "\n";
  TFile dsPlusFile((dsPath + dsPlusFileName).c_str(), "RECREATE");
  reducedPlusDataSet->Write("inputDataSet");
  dsPlusFile.Close();

  RooDataSet *minusDataSet = dynamic_cast<RooDataSet *>(
      inputDataSet.reduce("charge==charge::minus"));
  //  Charge in the formula it corresponds to the string we have in the
  //  constructor of Categories as RooFit only knows the strings you've given it
  RooDataSet *reducedMinusDataSet =
      dynamic_cast<RooDataSet *>(minusDataSet->reduce(config.fullArgSet()));
  std::cout << "MinusDataSet contains variables: ";
  reducedMinusDataSet -> printArgs(std::cout);
  std::cout << "\n";
  std::string dsMinusFileName =
      ComposeFilename(myYear, myPolarity, myBachelor, myNeutral, myDaughters,
                      Charge::minus) +
      ".root";
  std::cout << "Saving data set to file: " << dsPath + dsMinusFileName << "\n";
  TFile dsMinusFile((dsPath + dsMinusFileName).c_str(), "RECREATE");
  reducedMinusDataSet->Write("inputDataSet");
  dsMinusFile.Close();
}

int main(int argc, char **argv) {

  std::string path = argv[1];
  Year year = StringToEnum<Year>(argv[2]);
  Polarity polarity = StringToEnum<Polarity>(argv[3]);
  Bachelor bachelor = StringToEnum<Bachelor>(argv[4]);
  Neutral neutral = StringToEnum<Neutral>(argv[5]);
  Daughters daughters = StringToEnum<Daughters>(argv[6]);

  SaveRooDataSet(path, year, polarity, bachelor, neutral, daughters);
  return 0;
}

// std::shared_ptr has a built in counter that counts how many 'places' knows
// about its existence. It automatically destroys itself when nobody knows it
// exists
//
// What .add() SHOULD look like for the two cases:
// void RooArgSet::Add(std::shared_ptr<RooAbsArg> ptr);
// void RooDataSet::Add(RooAbsArg const &row);
//
// This IMMEDIATELY makes it clear that RooArgSet will only store a pointer to
// my data, meaning that if I change it, it will also change what RooArgSet
// knows about
// When you pass something as a reference like here for RooDataSet, you expect
// that they will only use it for the duration of the function, and then it's
// completely back in your control after, meaning either they only needed to
// read it once or they've made a copy
