#pragma once
#include "Configuration.h"
#include "RooAbsReal.h"
#include "RooFormulaVar.h"
// Templated classes/functions mean that the compiler will automatically create
// a copy
// of the entire class for you for every permutation of template arguments it is
// called
// with. This is handy because often a lot of the code is identical except for a
// few
// details.
// However, everything the compiler needs to do so must be provided in the .h
// file,
// because otherwise it won't actually know how to cater to external callers to
// your
// class/function (unless you explicitly specialize, see below).

template <Bachelor bachelor, Daughters daughters>
class BachelorDaughtersVars {
  
 public:
  // Inline Constructor
  BachelorDaughtersVars(int uniqueId_);
  // Inline Destructor - can both be implemented externally too:
  ~BachelorDaughtersVars() {}
  // Class Human
  // {
  // public:
  //  ~Human(); //Destructor declaration
  // };
  //:: is the scoping operator. Destructor definition/implementation
  // Human::~Human();
  // { // code }
  // Invoked when a class is deleted or goes out of scope: good place to reset
  // variables/release dynamically allocated memory

  using This_t = BachelorDaughtersVars<bachelor, daughters>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId_);

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  RooConstVar &kBR() { return kBR_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...

  // Indicate if only used by one daughters

  int uniqueId_;
  // BR for decay relative to FAV mode (π, Kπ)
  // Can add for different bkgs if necessary 
  RooConstVar kBR_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <> BachelorDaughtersVars<Bachelor::pi, Daughters::kpi>::BachelorDaughtersVars(int uniqueId);
template <> BachelorDaughtersVars<Bachelor::pi, Daughters::kk>::BachelorDaughtersVars(int uniqueId);
template <> BachelorDaughtersVars<Bachelor::pi, Daughters::pipi>::BachelorDaughtersVars(int uniqueId);
template <> BachelorDaughtersVars<Bachelor::pi, Daughters::pik>::BachelorDaughtersVars(int uniqueId);
template <> BachelorDaughtersVars<Bachelor::k, Daughters::kpi>::BachelorDaughtersVars(int uniqueId);
template <> BachelorDaughtersVars<Bachelor::k, Daughters::kk>::BachelorDaughtersVars(int uniqueId);
template <> BachelorDaughtersVars<Bachelor::k, Daughters::pipi>::BachelorDaughtersVars(int uniqueId);
template <> BachelorDaughtersVars<Bachelor::k, Daughters::pik>::BachelorDaughtersVars(int uniqueId);
// Then we can safely put these in the .cpp-file somewhere to be linked later.
