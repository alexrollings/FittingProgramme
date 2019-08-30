#include "Pdf.h"

PdfBase::PdfBase(int uniqueId, Neutral neutral,
                 Bachelor bachelor, Daughters daughters, Charge charge)
    : neutral_(neutral),
      bachelor_(bachelor),
      daughters_(daughters),
      charge_(charge),
      uniqueId_(uniqueId),
      addPdfBu_(nullptr),
      addPdfDelta_(nullptr),
      yieldsBu_(("yieldsBu_" + ComposeName(uniqueId, neutral, bachelor,
                                       daughters, charge))
                  .c_str()),
      yieldsDelta_(("yieldsDelta_" + ComposeName(uniqueId, neutral, bachelor,
                                       daughters, charge))
                  .c_str()),
      functionsBu_(("functionsBu_" + ComposeName(uniqueId, neutral,
                                             bachelor, daughters, charge))
                     .c_str()),
      functionsDelta_(("functionsDelta_" + ComposeName(uniqueId, neutral,
                                             bachelor, daughters, charge))
                     .c_str()) {}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdfBu_, CategoryName(Mass::buDelta).c_str());
  if (Configuration::Get().fit1D() == false) {
    simPdf.addPdf(*addPdfDelta_, CategoryName(Mass::delta).c_str());
  }
}
