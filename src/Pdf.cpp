#include "Pdf.h"

PdfBase::PdfBase(int uniqueId, Mass mass, Neutral neutral,
                 Bachelor bachelor, Daughters daughters, Charge charge)
    : neutral_(neutral),
      mass_(mass),
      bachelor_(bachelor),
      daughters_(daughters),
      charge_(charge),
      uniqueId_(uniqueId),
      addPdf_(nullptr),
      yields_(("yields_" + ComposeName(uniqueId, mass, neutral, bachelor,
                                       daughters, charge))
                  .c_str()),
      functions_(("functions_" + ComposeName(uniqueId, mass, neutral,
                                             bachelor, daughters, charge))
                     .c_str()) {}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdf_, CategoryName().c_str());
}
