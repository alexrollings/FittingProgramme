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

template <Daughters daughters>
class DaughtersVars {

  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   DaughtersVars<Daughters::gamma>::Get()
  //   DaughtersVars<Daughters::pi0>::Get()
  // All happens automatically :-)
  
 public:
  // Inline Constructor
  DaughtersVars(int uniqueId_);
  // Inline Destructor - can both be implemented externally too:
  ~DaughtersVars() {}
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

  using This_t = DaughtersVars<daughters>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId_) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId_);  // Check if uniqueId_ already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId_, std::make_shared<This_t>(uniqueId_))
               .first;
    }
    return *it->second;
  }

  // If RooShit wasn't so shit we would pass a const reference
  int uniqueId() { return uniqueId_; }
  RooRealVar &R_CP_overRec() { return R_CP_overRec_; }
  RooAbsReal &ratioDst0KDst0pi_overRec() { return *ratioDst0KDst0pi_overRec_; }
  RooRealVar &ratioDst0KDst0pi_misRec () { return ratioDst0KDst0pi_misRec_; }
  const double &daughtersSF() { return daughtersSF_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see
  // below)...

  // Indicate if only used by one daughters

  int uniqueId_;
  RooRealVar R_CP_overRec_;
  std::unique_ptr<RooAbsReal> ratioDst0KDst0pi_overRec_;
  RooRealVar ratioDst0KDst0pi_misRec_;
  const double daughtersSF_;
};

// Now we just need to define the constructors separately so the values are
// different

// ...by telling it exactly which specializations we are providing:
template <> DaughtersVars<Daughters::kpi>::DaughtersVars(int uniqueId);
template <> DaughtersVars<Daughters::kk>::DaughtersVars(int uniqueId);
template <> DaughtersVars<Daughters::pipi>::DaughtersVars(int uniqueId);
template <> DaughtersVars<Daughters::pik>::DaughtersVars(int uniqueId);
// Then we can safely put these in the .cpp-file somewhere to be linked later.
