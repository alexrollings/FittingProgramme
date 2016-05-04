#pragma once

#include "RooCategory.h"
#include "RooRealVar.h"

#include <string>

enum class Polarity { up, down, both };
enum class Daughter { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015 };
enum class Neutral { pi0, gamma };

// Initialise any units needed
// Array of chars. Pass to RooRealVar without '.c_str()'
// not *kMassUnit[] ??????
constexpr const char *kMassUnit = "Mev/c^2";
constexpr const char *kMomentumUnit = "Mev/c";
constexpr const char *kNoUnit = "";

constexpr const char *kLabelBuMass = "Bu Mass DTF Constrained";
constexpr const char *kLabelBuID = "Bu PDG ID";

// constexpr guarantees initialisation at compile time
// Initialise upper and lower values for RooRealVars
constexpr double kLowBuMass = 4979.;
constexpr double kHighBuMass = 5701.;
constexpr double kLowBuID = -550.;
constexpr double kHighBuID = 550.;

// Error says I have multiple definitions when I try to declare it here?
// RooRealVar mBu;
// RooRealVar idBu;

RooRealVar mBuInitialiser(std::string neutral);
RooRealVar idBuInitialiser(std::string neutral);

//Singleton = class that can only be instantiated once.
//Make the constructor and destructor private.
//members of struct are public by default and a struct features public inheritance from a base struct (private for class)
struct StaticVars {
public:
  //static ensures the member is shared across all instances of the class: not just the object
  static RooCategory const& polarityCat() {
    return StaticVars::Get().polarityCat_;
  }
  static RooCategory const& chargeCat() {
    return StaticVars::Get().chargeCat_;
  }
  static RooCategory const& daughterCat() {
    return StaticVars::Get().daughterCat_;
  }
  static RooCategory const& bachelorCat() {
    return StaticVars::Get().bachelorCat_;
  }
  static RooCategory const& neutralCat() {
    return StaticVars::Get().neutralCat_;
  }
  static RooCategory const& yearCat() {
    return StaticVars::Get().yearCat_;
  }
  // static RooRealVar const& mBu() {
  //   return StaticVars::Get().mBu_;
  // }
  // static RooRealVar const& idBu() {
  //   return StaticVars::Get().idBu_;
  // }

  // RooRealVar mBuInitialiser(std::string neutral);
  // RooRealVar idBuInitialiser(std::string neutral);

  //Have the function return a const reference to the variable, e.g. category.
  //Need one function for every variable.
  //Get a reference to the variable we have instantiated but we only get the constant reference to the variable therefore we cannot change them.
private:
  StaticVars();
  ~StaticVars() {}
  StaticVars &operator=(StaticVars const &) = delete;
  //Deletes the = operator (which is defined in std)
  //Get() returns a reference to the instantiation StaticVars (it is a function IN the class therefore it can construct the object)
  
  static StaticVars const &Get() {
    static StaticVars singleton;
    return singleton;
  }
  
  
  RooCategory polarityCat_;
  RooCategory chargeCat_;
  RooCategory daughterCat_;
  RooCategory bachelorCat_;
  RooCategory neutralCat_;
  RooCategory yearCat_;

  // RooRealVar mBu_;
  // RooRealVar idBu_;
};


  //To get static variable call class static vars that has a global function that returns the value that you want. Will always point to the same global place in memory. We want this because we want to construct an object globally and always access the same object. Prefer const expression but this is what you do for things that cannot be const: that cannot be constructed at compile time. Singleton pattern.

