#include "Pdf.h"

PdfBase::PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor,
                 Daughters daughters, Charge charge)
    : neutral_(neutral),
      bachelor_(bachelor),
      daughters_(daughters),
      charge_(charge),
      uniqueId_(uniqueId),
      addPdf_(nullptr),
      yieldComb_(("yieldComb_" +
                  ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                     .c_str(),
                 ("Combinatorial Yield " +
                  ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                     .c_str(),
                 10000, 0, 15000),
      yields_(("yields_" +
               ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                  .c_str()),
      functions_(("functions_" +
                  ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                     .c_str()) {}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdf_, CategoryName().c_str());
}
