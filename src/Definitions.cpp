#include "Definitions.h"
//Construct the members of StaticVars
//Add other member variables separated by commas
//Member variables must be constructed on construction of the class
  
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

