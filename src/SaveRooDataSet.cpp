#include <iostream>
#include <sstream>
#include <stdexcept>

#include "RooArgList.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooRealVar.h"

#include "TFile.h"
#include "TTree.h"

#include "Definitions.h"

using namespace RooFit;
std::string dsPath("~/ButoDst0X_FIT/roodatasets/");

void SaveRooDataSet(std::string path, Year myYear, Polarity myPolarity,
                    Bachelor myBachelor, Neutral myNeutral,
                    Daughter myDaughter) {

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

  RooCategory yearCat(StaticVars::yearCat());
  RooCategory polarityCat(StaticVars::polarityCat());
  RooCategory bachelorCat(StaticVars::bachelorCat());
  RooCategory neutralCat(StaticVars::neutralCat());
  RooCategory daughterCat(StaticVars::daughterCat());
  RooCategory chargeCat(StaticVars::chargeCat());

  // Declare strings to hold category options
  std::string year;
  std::string polarity;
  std::string bachelor;
  std::string neutral;
  std::string daughter;
  std::string charge;
  std::string ttree;

  // Set fileName and RooCategory options
  if (myYear == Year::y2011) {
    year = "2011";
  } else if (myYear == Year::y2012) {
    year = "2012";
  } else if (myYear == Year::y2015) {
    year = "2015";
  }

  if (myPolarity == Polarity::up) {
    polarity = "up";
  } else if (myPolarity == Polarity::down) {
    polarity = "down";
  }

  if (myBachelor == Bachelor::pi) {
    bachelor = "pi";
  } else if (myBachelor == Bachelor::k) {
    bachelor = "k";
  }

  if (myNeutral == Neutral::pi0) {
    neutral = "pi0";
    ttree = "BtoDstar0h3_h1h2pi0RTuple";
  } else if (myNeutral == Neutral::gamma) {
    neutral = "gamma";
    ttree = "BtoDstar0h3_h1h2gammaTuple";
  }

  if (myDaughter == Daughter::kpi) {
    daughter = "kpi";
  } else if (myDaughter == Daughter::kk) {
    daughter = "kk";
  } else if (myDaughter == Daughter::pipi) {
    daughter = "pipi";
  } else if (myDaughter == Daughter::pik) {
    daughter = "pik";
  }

  // Initialise all variable names in nTuples
  std::string nameBuMass;
  std::string nameBuID;

  if (neutral == "pi0") {
    nameBuMass = "Pi0_Bu_M_DTF_D0Pi0";
    nameBuID = "Pi0_Bu_ID";
  } else if (neutral == "gamma") {
    nameBuMass = "Gamma_Bu_M_DTF_D0";
    nameBuID = "Gamma_Bu_ID";
  }

  // Initialise any units needed
  std::string massUnit("Mev/c^2");
  std::string momentumUnit("Mev/c");

  // Initialise all upper and lower limits of variables
  const double kLowBuMass = 4979.;
  const double kHighBuMass = 5701.;
  const double kLowBuID = -550.;
  const double kHighBuID = 550.;

  // Create RooRealVars: any variables we are interested in (different for pi0
  // and gamma mode)
  RooRealVar mBu(nameBuMass.c_str(), "Bu Mass DTF Constrained", kLowBuMass,
                 kHighBuMass, massUnit.c_str());
  RooRealVar idBu(nameBuID.c_str(), "Bu PDG ID", kLowBuID, kHighBuID, "");

  // Create separate RooArgSets for variables and categories
  RooArgSet varArgSet;
  varArgSet.add(mBu);
  varArgSet.add(idBu);

  RooArgSet catArgSet;
  catArgSet.add(polarityCat);
  catArgSet.add(chargeCat);
  catArgSet.add(daughterCat);
  catArgSet.add(bachelorCat);
  catArgSet.add(yearCat);
  catArgSet.add(neutralCat);

  // Create DataSet and feed it the ArgSet, which defines how many columns it
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
    RooRealVar *idBuPtr = dynamic_cast<RooRealVar *>(row->find(idBu.GetName()));
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

    // SetRooCategory labels for each event
    yearCat.setLabel(year.c_str());
    polarityCat.setLabel(polarity.c_str());
    bachelorCat.setLabel(bachelor.c_str());
    neutralCat.setLabel(neutral.c_str());
    daughterCat.setLabel(daughter.c_str());
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

  RooDataSet* plusDataSet = dynamic_cast<RooDataSet *>(inputDataSet.reduce("chargeCat==chargeCat::plus"));

 
  std::string dsPlusFileName(year + "_" + polarity + "_" + bachelor + "_" +
                         neutral + "_" + daughter + "_plus.root");
  std::cout << "Saving data set to file: " << dsPath + dsPlusFileName << "\n";
  TFile dsPlusFile((dsPath + dsPlusFileName).c_str(), "RECREATE");
  plusDataSet->Write();
  dsPlusFile.Close();

  RooDataSet* minusDataSet = dynamic_cast<RooDataSet *>(inputDataSet.reduce("chargeCat==chargeCat::minus"));
 
  std::string dsMinusFileName(year + "_" + polarity + "_" + bachelor + "_" +
                         neutral + "_" + daughter + "_minus.root");
  std::cout << "Saving data set to file: " << dsPath + dsMinusFileName << "\n";
  TFile dsMinusFile((dsPath + dsMinusFileName).c_str(), "RECREATE");
  minusDataSet->Write();
  dsMinusFile.Close();


}

int main(int argc, char **argv) {
  std::string myPath = argv[1];
  std::string yearInput = argv[2];
  std::string polarityInput = argv[3];
  std::string bachelorInput = argv[4];
  std::string neutralInput = argv[5];
  std::string daughterInput = argv[6];

  Polarity myPolarity;
  Daughter myDaughter;
  Bachelor myBachelor;
  Year myYear;
  Neutral myNeutral;

  if (polarityInput == "up") {
    myPolarity = Polarity::up;
  } else if (polarityInput == "down") {
    myPolarity = Polarity::down;
  }

  if (daughterInput == "kpi") {
    myDaughter = Daughter::kpi;
  } else if (daughterInput == "kk") {
    myDaughter = Daughter::kk;
  } else if (daughterInput == "pipi") {
    myDaughter = Daughter::pipi;
  } else if (daughterInput == "pik") {
    myDaughter = Daughter::pik;
  }

  if (bachelorInput == "pi") {
    myBachelor = Bachelor::pi;
  } else if (bachelorInput == "k") {
    myBachelor = Bachelor::k;
  }

  if (yearInput == "2011") {
    myYear = Year::y2011;
  } else if (yearInput == "2012") {
    myYear = Year::y2012;
  } else if (yearInput == "2015") {
    myYear = Year::y2015;
  }

  if (neutralInput == "pi0") {
    myNeutral = Neutral::pi0;
  } else if (neutralInput == "gamma") {
    myNeutral = Neutral::gamma;
  }

  SaveRooDataSet(myPath, myYear, myPolarity, myBachelor, myNeutral, myDaughter);
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
