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

std::string dsPath("/data/lhcb/users/rollings/roodatasets/d1d_fit/");

void SaveRooDataSet(std::string const &path, Year year, Polarity polarity,
                    Bachelor bachelor, Neutral neutral,
                    Daughters daughters) {

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

  // Set fileName and RooCategory options
  std::string ttree;
  if (neutral == Neutral::pi0) {
    ttree = "BtoDstar0h3_h1h2pi0RTuple";
  } else if (neutral == Neutral::gamma) {
    ttree = "BtoDstar0h3_h1h2gammaTuple";
  }

  // Initialise RooRealVars now neutral has been specified
  Configuration &config = Configuration::Get();
  Configuration::Categories &categories = Configuration::Get().categories();
  config.buMass().setMax(6000);
  config.buMass().setMin(4000);
  config.buMass().setBins(400);
  config.buDeltaMass().setMax(6000);
  config.buDeltaMass().setMin(4000);
  config.buDeltaMass().setBins(400);
  config.deltaMass().setMin(0);
  config.deltaMass().setMax(250);
  config.deltaMass().setBins(125);

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

  Charge charge;
  charge = Charge::total;
  // Loop over data set, find RooCategory for each event and set it's label
  for (int i = 0; i < inputDataSet.numEntries(); i++) {
    // RooDataSet::get() returns a const pointer to a RooArgSet for event i (why
    // we must use RooArgSet not RooArgList)
    RooArgSet const *row = inputDataSet.get(i);

    // Adding the categories to RooArgSet added a pointer to the value's memory
    // address. Therefore changing their values changes changes what is stored
    // in catArgSet.
    categories.charge.setLabel("total");
    categories.fitting.setLabel(ComposeFittingName(neutral, bachelor, daughters, charge).c_str());

    // Add category labels to 'extra' data set
    extraDataSet.add(config.categoryArgSet());
    // Add here copies the values from rooArgSet
  }

  std::cout << "exited loop" << std::endl;
  // Merge data set containing variables with that containing categories
  inputDataSet.merge(&extraDataSet);

  std::cout << "Dataset contains variables: ";
  inputDataSet.printArgs(std::cout);
  std::cout << "\n";
 
  std::string dsFileName =
      ComposeFilename(year, polarity, bachelor, neutral, daughters,
                      charge) +
      ".root";
  std::cout << "Saving data set to file: " << dsPath + dsFileName << "\n";
  TFile dsFile((dsPath + dsFileName).c_str(), "RECREATE");
  inputDataSet.Write("inputDataSet");
  dsFile.Close();
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
