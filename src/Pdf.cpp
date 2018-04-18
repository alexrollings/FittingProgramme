#include "Pdf.h"
#include "Configuration.h"

PdfBase::PdfBase(Neutral neutral, Bachelor bachelor, Daughters daughters)
    : neutral_(neutral),
      bachelor_(bachelor),
      daughters_(daughters),
      addPdf_(nullptr),
      yieldSignal_(
          ("yieldSignal_" + ComposeName(neutral, bachelor, daughters)).c_str(),
          ("Signal Yield " + ComposeName(neutral, bachelor, daughters)).c_str(),
          1000, 0, 5000),
      yieldComb_(
          ("yieldComb_" + ComposeName(neutral, bachelor, daughters)).c_str(),
          ("Combinatorial Yield " + ComposeName(neutral, bachelor, daughters))
              .c_str(),
          100, 0, 500),
      lambdaComb_(
          ("lambdaComb_" + ComposeName(neutral, bachelor, daughters)).c_str(),
          ("Combinatorial constant " +
           ComposeName(neutral, bachelor, daughters))
              .c_str(),
          -0.1, -1, 1),
      pdfComb_(
          ("pdfComb_" + ComposeName(neutral, bachelor, daughters)).c_str(),
          ("Combinatorial PDF " + ComposeName(neutral, bachelor, daughters))
              .c_str(),
          Configuration::Get().buMass(), lambdaComb_),
      yields_(("yields_" + ComposeName(neutral, bachelor, daughters)).c_str()),
      functions_(
          ("functions_" + ComposeName(neutral, bachelor, daughters)).c_str()) {}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdf_, ComposeName(neutral_, bachelor_, daughters_).c_str());
}
