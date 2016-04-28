#pragma once
#include "RooCategory.h"

enum class Polarity { up, down, both };
enum class Daughter { kpi, kk, pipi, pik };
enum class Bachelor { pi, k };
enum class Year { y2011, y2012, y2015 };
enum class Neutral { pi0, gamma };

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
};


  //To get static variable call class static vars that has a global function that returns the value that you want. Will always point to the same global place in memory. We want this because we want to construct an object globally and always access the same object. Prefer const expression but this is what you do for things that cannot be const: that cannot be constructed at compile time. Singleton pattern.

