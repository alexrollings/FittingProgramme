#include "Pdf.h"
#include "Configuration.h"

PdfBase::PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor, Daughters daughters,
                 Charge charge)
    : neutral_(neutral),
      bachelor_(bachelor),
      daughters_(daughters),
      charge_(charge),
      uniqueId_(uniqueId),
      addPdf_(nullptr),
      yieldComb_(
          ("yieldComb_" + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          ("Combinatorial Yield " +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          100, 0, 500),
      lambdaDeltaComb_(("lambdaDeltaComb_" +
                        ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                           .c_str(),
                       ("Delta Combinatorial constant " +
                        ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                           .c_str(),
                       -0.001, -1, 1),
      a0LambdaBuComb_(("a0LambdaBuComb_" +
                       ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                          .c_str(),
                      ("a0 component for Bu Combinatorial constant " +
                       ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                          .c_str(),
                      -0.001, -1, 1),
      lambdaBuComb_(
          ("lambdaBuComb_" + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          ("Bu Combinatorial constant " +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          Configuration::Get(uniqueId).deltaMass(), RooArgSet(a0LambdaBuComb_)),
      pdfDeltaComb_(
          ("pdfDeltaComb_" + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          ("DeltaCombinatorial PDF " +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          Configuration::Get(uniqueId).deltaMass(), lambdaDeltaComb_),
      pdfBuComb_(
          ("pdfBuComb_" + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          ("BuCombinatorial PDF " +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          Configuration::Get(uniqueId).buMass(), lambdaBuComb_),
      pdfComb_(("pdfComb_" + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                   .c_str(),
               ("Combinatorial PDF " +
                ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                   .c_str(),
               pdfDeltaComb_,
               RooFit::Conditional(pdfBuComb_, Configuration::Get(uniqueId).buMass())),
      yields_(("yields_" + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                  .c_str()),
      functions_(
          ("functions_" + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str()) {}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdf_, CategoryName().c_str());
}
