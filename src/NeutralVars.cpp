#include "NeutralVars.h"
#include "GlobalVars.h"

// Neutral specializations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    : meanDeltaSignal_(
          ("meanDeltaSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean of Signal m[Delta]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          145, 140, 150),
      a0MeanBuSignal_(
          ("a0MeanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          // 5279, 5275, 5284),
          5101.86875, 4879, 5579),
      //  2600.0, 1600.0, 3600.0),
      a1MeanBuSignal_(
          ("a1MeanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a1 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          2.1375, 0, 10),
      // 31.7, 0, 40),
      a2MeanBuSignal_(
          ("a2MeanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a2 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.0062, -0.01, -0.00001),
      // -0.083, -0.1, 0.1),
      meanBuSignal_(
          ("meanBuSignal" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Mean of Signal m[Bu]" + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBuSignal_, a1MeanBuSignal_ /* , a2MeanBuSignal_ */)),
      lambdaDeltaComb_(
          ("lambdaDeltaComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Delta Combinatorial constant " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.001, -1, -0.00001),
      a0LambdaBuComb_(
          ("a0LambdaBuComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("a0 component for Bu Combinatorial constant " +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          -0.001, -1, -0.00001),
      lambdaBuComb_(
          ("lambdaBuComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("Bu Combinatorial constant " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgSet(a0LambdaBuComb_)),
      pdfDeltaComb_(
          ("pdfDeltaComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("DeltaCombinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().deltaMass(), lambdaDeltaComb_),
      pdfBuComb_(
          ("pdfBuComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
          ("BuCombinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          Configuration::Get().buMass(), lambdaBuComb_),
      pdfComb_(("pdfComb_" + ComposeName(uniqueId, Neutral::gamma)).c_str(),
               ("Combinatorial PDF " + ComposeName(uniqueId, Neutral::gamma))
                   .c_str(),
               pdfDeltaComb_,
               RooFit::Conditional(pdfBuComb_, Configuration::Get().buMass())) {}

template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    : meanDeltaSignal_(
          ("meanDeltaSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of Signal m[Delta]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          135, 130, 140),
      a0MeanBuSignal_(
          ("a0MeanBuSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          // 5279, 5275, 5284),
          5101.86875, 4879, 5579),
          //  2600.0, 1600.0, 3600.0), 
      a1MeanBuSignal_(
          ("a1MeanBuSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a1 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          2.1375, 0, 10),
          // 31.7, 0, 40), 
      a2MeanBuSignal_(
          ("a2MeanBuSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a2 of mean of Signal m[Bu] PDF " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.0062, -0.01, -0.00001),
          // -0.083, -0.1, 0.1), 
      meanBuSignal_(
          ("meanBuSignal" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Mean of Signal m[Bu]" + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(),
          RooArgList(a0MeanBuSignal_, a1MeanBuSignal_/* , a2MeanBuSignal_ */)),
      lambdaDeltaComb_(
          ("lambdaDeltaComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Delta Combinatorial constant " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.001, -1, -0.00001),
      a0LambdaBuComb_(
          ("a0LambdaBuComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("a0 component for Bu Combinatorial constant " +
           ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          -0.001, -1, -0.00001),
      lambdaBuComb_(
          ("lambdaBuComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("Bu Combinatorial constant " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), RooArgSet(a0LambdaBuComb_)),
      pdfDeltaComb_(
          ("pdfDeltaComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("DeltaCombinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().deltaMass(), lambdaDeltaComb_),
      pdfBuComb_(
          ("pdfBuComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
          ("BuCombinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
              .c_str(),
          Configuration::Get().buMass(), lambdaBuComb_),
      pdfComb_(("pdfComb_" + ComposeName(uniqueId, Neutral::pi0)).c_str(),
               ("Combinatorial PDF " + ComposeName(uniqueId, Neutral::pi0))
                   .c_str(),
               pdfDeltaComb_,
               RooFit::Conditional(pdfBuComb_, Configuration::Get().buMass())) {}
