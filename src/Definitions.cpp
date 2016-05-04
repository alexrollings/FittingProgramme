#include "Definitions.h"
//Construct the members of StaticVars
//Add other member variables separated by commas
//Member variables must be constructed on construction of the class

// Functions to initialise RooRealVars depending on the neutral choice (variable names are different)

RooRealVar mBuInitialiser(std::string neutral){
  
  std::string nameBuMass;
  std::string nameBuID;

  if (neutral == "pi0") { 
    nameBuMass = "Pi0_Bu_M_DTF_D0Pi0";
    
  } else if (neutral == "gamma") {
    nameBuMass = "Gamma_Bu_M_DTF_D0";
  }

  RooRealVar mBu_(nameBuMass.c_str(), kLabelBuMass, kLowBuMass,
               kHighBuMass, kMassUnit);
  
  return mBu_;
}

RooRealVar idBuInitialiser(std::string neutral){

  std::string nameBuMass;
  std::string nameBuID;
  
  if (neutral == "pi0") { 
    nameBuID = "Pi0_Bu_ID";
  } else if (neutral == "gamma") {
    nameBuID = "Gamma_Bu_ID";
  }

  RooRealVar idBu_(nameBuID.c_str(), kLabelBuID, kLowBuID, kHighBuID, kNoUnit);
  
  return idBu_;

}

StaticVars::StaticVars() : polarityCat_("polarityCat","polarityCat"), chargeCat_("chargeCat","chargeCat"), daughterCat_("daughterCat","daughterCat"), bachelorCat_("bachelorCat","bachelorCat"), neutralCat_("neutralCat","neutralCat"), yearCat_("yearCat","yearCat"){
  
  // Initialise RooCategories
  polarityCat_.defineType("up");
  polarityCat_.defineType("down");
  polarityCat_.defineType("both");

  chargeCat_.defineType("minus");
  chargeCat_.defineType("plus");

  daughterCat_.defineType("kpi");
  daughterCat_.defineType("kk");
  daughterCat_.defineType("pipi");
  daughterCat_.defineType("pik");

  bachelorCat_.defineType("pi");
  bachelorCat_.defineType("k");

  yearCat_.defineType("2011");
  yearCat_.defineType("2012");
  yearCat_.defineType("2015");

  neutralCat_.defineType("pi0");
  neutralCat_.defineType("gamma");


}

