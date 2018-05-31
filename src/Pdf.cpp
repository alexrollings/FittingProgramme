#include "Pdf.h"

PdfBase::PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor,
                 Daughters daughters, Charge charge)
    : neutral_(neutral),
      bachelor_(bachelor),
      daughters_(daughters),
      charge_(charge),
      uniqueId_(uniqueId),
      addPdf_(nullptr),
      yield_Comb_(("yield_Comb_" +
                  ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                     .c_str(),
                 ("_Combinatorial Yield " +
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
