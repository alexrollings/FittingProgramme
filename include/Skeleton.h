#include "Configuration.h"
#include "RooSimultaneous.h"

// Remove namespace when Configuration is not duplicate anymore
namespace test {

class Configuration {

public:
  static Configuration &Get() {
    static Configuration singleton;
    return singleton;
  }

  struct Categories {
    RooCategory polarity;
    RooCategory charge;
    RooCategory daughters;
    RooCategory bachelor;
    RooCategory neutral;
    RooCategory year;
    RooCategory fitting;
    Categories();
    Categories(Categories const &) = delete;
    Categories(Categories &&) = delete;
    Categories &operator=(Categories const &) = delete;
    Categories &operator=(Categories &&) = delete;
  };

  RooRealVar &buMass() { return buMass_; }
  RooRealVar &buPdgId() { return buPdgId_; }
  RooArgSet &variableArgSet() { return variableArgSet_; }
  RooArgSet &categoryArgSet() { return categoryArgSet_; }
  RooArgSet &fullArgSet() { return fullArgSet_; }
  Categories &categories() { return categories_; }

private:
  Configuration();
  Configuration(Configuration const &) = delete;
  Configuration(Configuration &&) = delete;
  Configuration &operator=(Configuration const &) = delete;
  Configuration &operator=(Configuration &&) = delete;

  Categories categories_;
  RooRealVar buMass_;
  RooRealVar buPdgId_;
  RooArgSet variableArgSet_;
  RooArgSet categoryArgSet_;
  RooArgSet fullArgSet_;
};

} // End namespace test

// Templated classes/functions mean that the compiler will automatically create a copy
// of the entire class for you for every permutation of template arguments it is called
// with. This is handy because often a lot of the code is identical except for a few
// details.
// However, everything the compiler needs to do so must be provided in the .h file, 
// because otherwise it won't actually know how to cater to external callers to your
// class/function (unless you explicitly specialize, see below).

template <Neutral neutral> class NeutralVars {

  // One template specialization == One entirely separate class in practice
  // These will give two different instances:
  //   NeutralVars<Neutral::gamma>::Get()
  //   NeutralVars<Neutral::pi0>::Get()
  // All happens automatically :-)
  static NeutralVars<neutral> &Get() {
    static NeutralVars<neutral> singleton;
    return singleton;
  }

  RooRealVar &meanCrossFeed() { return meanCrossFeed_; }

private:
  // When we DO need to specialize certain cases, we can still do that (see below)...
  NeutralVars();
  ~NeutralVars() {}

  RooRealVar meanCrossFeed_;
};

// Now we just need to define the constructors separately so the values are
// different


// ...by telling it exactly which specializations we are providing:
template <> NeutralVars<Neutral::gamma>::NeutralVars();
template <> NeutralVars<Neutral::pi0>::NeutralVars();
// Then we can safely put these in the .cpp-file somewhere to be linked later.

// Bachelor

template <Neutral neutral, Bachelor bachelor> class BachelorVars {

  static BachelorVars<neutral, bachelor> &Get() {
    static BachelorVars<neutral, bachelor> singleton;
    return singleton;
  }

  RooRealVar &sigmaCrossFeed() { return sigmaCrossFeed_; }

  void AddToPdf(RooArgList &yields, RooArgList &functions);

private:
  BachelorVars();
  ~BachelorVars() {}

  RooRealVar sigmaCrossFeed_;
  std::unique_ptr<RooAbsPdf> bu2Dst0Hst_D0gamma_;
};

template <> BachelorVars<Neutral::gamma, Bachelor::pi>::BachelorVars();

template <>
void BachelorVars<Neutral::gamma, Bachelor::pi>::AddToPdf(
    RooArgList &yields, RooArgList &functions);

// Pdf

// Remove namespace when not duplicate anymore
namespace test {

template <Neutral neutral, Bachelor bachelor, Daughters daughters> class Pdf {

  static Pdf<neutral, bachelor, daughters> &Get() {
    static Pdf<neutral, bachelor, daughters> singleton;
    return singleton;
  }

  void AddToSimultaneousPdf(RooSimultaneous &simPdf) const;

private:
  Pdf();
  ~Pdf();

  RooRealVar signalYield_;
  RooArgList yields_;
  RooArgList functions_;
};

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
Pdf<neutral, bachelor, daughters>::Pdf()
    : signalYield_(("signal_yield_" +
                    ComposeFittingCategoryName(neutral, bachelor, daughters))
                       .c_str(),
                   "Signal yield", 10000, 0, 30000),
      yields_(), functions_() {

  BachelorVars<neutral, bachelor>::Get().AddToPdf(yields_, functions_);
}


int main() {
  Pdf<Neutral::gamma, Bachelor::kk, Daughters::pik> pdf;
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
void Pdf<neutral, bachelor, daughters>::AddToSimultaneousPdf(
    RooSimultaneous &simPdf) const {
  // simPdf.addPdf(
  //     *addPdf_,
  //     ComposeFittingCategoryName(neutral, bachelor, daughters).c_str());
}

} // End namespace test
