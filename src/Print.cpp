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
enum class Daughter { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015 };
enum class Neutral { pi0, gamma };

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

//Function takes as input all options parsed via the command line
void LoadDataSet(Polarity myPolarity, Daughter myDaughter, Bachelor myBachelor, Year myYear, Neutral myNeutral) {

  // Initialise RooCategories
  RooCategory polarityCat("polarityCat", "polarityCat");
  polarityCat.defineType("up");
  polarityCat.defineType("down");
  polarityCat.defineType("both");

  RooCategory chargeCat("chargeCat", "chargeCat");
  chargeCat.defineType("minus");
  chargeCat.defineType("plus");

  RooCategory daughterCat("daughterCat", "daughterCat");
  daughterCat.defineType("kpi");
  daughterCat.defineType("kk");
  daughterCat.defineType("pipi");
  daughterCat.defineType("pik");

  RooCategory bachelorCat("bachelorCat", "bachelorCat");
  bachelorCat.defineType("pi");
  bachelorCat.defineType("k");

  RooCategory yearCat("yearCat", "yearCat");
  yearCat.defineType("2011");
  yearCat.defineType("2012");
  yearCat.defineType("2015");

  RooCategory neutralCat("neutralCat", "neutralCat");
  neutralCat.defineType("pi0");
  neutralCat.defineType("gamma");

  // ------------- IGNORE FOR NOW --------------------
  // declare vector to store fileName options
  // std::vector<std::string> polarity_fn;
  // -------------------------------------------------

  // Declare strings to hold category options
  std::string polarity;
  std::string charge;
  std::string daughter;
  std::string bachelor;
  std::string year;
  std::string neutral;

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

  if(myDaughter == Daughter::kpi) {
    daughter = "kpi";
  } else if(myDaughter == Daughter::kk) {
    daughter = "kk";
  } else if(myDaughter == Daughter::pipi) {
    daughter = "pipi";
  } else if(myDaughter == Daughter::pik) {
    daughter = "pik";
  }

  if(myBachelor == Bachelor::pi) {
    bachelor = "pi";
  } else if(myBachelor == Bachelor::k) {
    bachelor = "k";
  }
    
  if(myYear == Year::y2011){
    year = "2011";
  } else if(myYear == Year::y2012){
    year = "2012";
  } else if(myYear == Year::y2015){
    year = "2015";
  }
    
  if(myNeutral == Neutral::pi0) {
    neutral = "pi0";
  } else if(myNeutral == Neutral::gamma) {
    neutral = "gamma";
  }
 
  //Initialise all variable names in nTuples
  std::string nm_m_Bu;
  std::string nm_id_Bu;
  
  if( neutral == "pi0" ){
    nm_m_Bu = "Pi0_Bu_M_DTF_D0Pi0"; 
    nm_id_Bu = "Pi0_Bu_ID";
  } else if( neutral == "gamma"){
    nm_m_Bu = "Gamma_Bu_M_DTF_D0";
    nm_id_Bu = "Gamma_Bu_ID";
  }

  //Initialise any units needed
  std::string mUnit("Mev/c^2");
  std::string pUnit("Mev/c");

  //Initialise all upper and lower limits of variables
  double klow_m_Bu = 4979.;
  double khigh_m_Bu = 5701.;
  double klow_id_Bu = -550.;
  double khigh_id_Bu = 550.;


  //Create RooRealVars: any variables we are interested in (different for pi0 and gamma mode)
  RooRealVar m_Bu(nm_m_Bu.c_str(), "Bu Mass DTF Constrained", klow_m_Bu, khigh_m_Bu,
                  mUnit.c_str());
  RooRealVar id_Bu(nm_id_Bu.c_str(), "Bu PDG ID", klow_id_Bu, khigh_id_Bu, "");

  // Create separate RooArgSets for variables and categories
  RooArgSet varArgSet;
  varArgSet.add(m_Bu);
  varArgSet.add(id_Bu);

  RooArgSet catArgSet;
  catArgSet.add(polarityCat);
  catArgSet.add(chargeCat);
  catArgSet.add(daughterCat);
  catArgSet.add(bachelorCat);
  catArgSet.add(yearCat);
  catArgSet.add(neutralCat);

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
    RooRealVar *ptr_id_Bu = dynamic_cast<RooRealVar *>(row->find(id_Bu.GetName()));
    if (ptr_id_Bu == nullptr) {
      std::stringstream output;
      output << "No value for ID[Bu] for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    if (ptr_id_Bu->getVal() < 0) {
      charge = "minus";
    } else if (ptr_id_Bu->getVal() > 0) {
      charge = "plus";
    };

    // SetRooCategory labels for each event
    polarityCat.setLabel(polarity.c_str());
    chargeCat.setLabel(charge.c_str());
    daughterCat.setLabel(daughter.c_str());
    bachelorCat.setLabel(bachelor.c_str());
    yearCat.setLabel(year.c_str());
    neutralCat.setLabel(neutral.c_str());
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

    RooRealVar *ptr_m_Bu = dynamic_cast<RooRealVar *>(row->find(id_Bu.GetName()));
    if (ptr_m_Bu == nullptr) {
      std::stringstream output;
      output << "No value for m[Bu] for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooRealVar *ptr_id_Bu = dynamic_cast<RooRealVar *>(row->find(id_Bu.GetName()));
    if (ptr_id_Bu == nullptr) {
      std::stringstream output;
      output << "No value for ID[Bu] for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooCategory *ptr_charge =
        dynamic_cast<RooCategory *>(row->find(chargeCat.GetName()));
    if (ptr_charge == nullptr) {
      std::stringstream output;
      output << "No value for the charge for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooCategory *ptr_polarity =
        dynamic_cast<RooCategory *>(row->find(polarityCat.GetName()));
    if (ptr_polarity == nullptr) {
      std::stringstream output;
      output << "No value for the polarity for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooCategory *ptr_daughter =
        dynamic_cast<RooCategory *>(row->find(daughterCat.GetName()));
    if (ptr_daughter == nullptr) {
      std::stringstream output;
      output << "No value for the daughter for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooCategory *ptr_bachelor =
        dynamic_cast<RooCategory *>(row->find(bachelorCat.GetName()));
    if (ptr_bachelor == nullptr) {
      std::stringstream output;
      output << "No value for the bachelor for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooCategory *ptr_year =
        dynamic_cast<RooCategory *>(row->find(yearCat.GetName()));
    if (ptr_year == nullptr) {
      std::stringstream output;
      output << "No value for the year for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    RooCategory *ptr_neutral =
        dynamic_cast<RooCategory *>(row->find(neutralCat.GetName()));
    if (ptr_neutral == nullptr) {
      std::stringstream output;
      output << "No value for the neutral for event " << i << ".";
      throw std::runtime_error(output.str());
    }

    std::cout << "For event " << i << " m[Bu] = " << ptr_m_Bu->getVal()
              << "  year = " << ptr_year->getLabel()
              << "  polarity = " << ptr_polarity->getLabel()
              << "  ID[Bu] = " << ptr_id_Bu->getVal()
              << "  charge = " << ptr_charge->getLabel()
              << "  D0 daughters = " << ptr_daughter->getLabel()
              << "  bachelor = " << ptr_bachelor->getLabel()
              << "  neutral = " << ptr_neutral->getLabel() << "\n";
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
  std::string polarityInput = argv[1];
  std::string daughterInput = argv[2];
  std::string bachelorInput = argv[3];
  std::string yearInput = argv[4];
  std::string neutralInput = argv[5];

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

  if(daughterInput == "kpi") {
    myDaughter = Daughter::kpi;
  } else if(daughterInput == "kk") {
    myDaughter = Daughter::kk;
  } else if(daughterInput == "pipi") {
    myDaughter = Daughter::pipi;
  } else if(daughterInput == "pik") {
    myDaughter = Daughter::pik;
  }

  if(bachelorInput == "pi") {
    myBachelor = Bachelor::pi;
  } else if(bachelorInput == "k") {
    myBachelor = Bachelor::k;
  }
    
  if(yearInput == "2011"){
    myYear = Year::y2011;
  } else if(yearInput == "2012"){
    myYear = Year::y2012;
  } else if(yearInput == "2015"){
    myYear = Year::y2015;
  }
    
  if(neutralInput == "pi0") {
    myNeutral = Neutral::pi0;
  } else if(neutralInput == "gamma") {
    myNeutral = Neutral::gamma;
  }
  
  LoadDataSet(myPolarity, myDaughter, myBachelor, myYear, myNeutral);
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
