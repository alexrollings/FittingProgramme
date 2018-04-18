#include "Pdf.h"
#include "Configuration.h"

PdfBase::PdfBase(Neutral neutral, Bachelor bachelor, Daughters daughters)
    : neutral_(neutral), bachelor_(bachelor), daughters_(daughters),
      addPdf_(nullptr), yieldSignal_(nullptr), yieldComb_(nullptr),
      yields_(("yields_" + ComposeName(neutral, bachelor, daughters)).c_str()),
      functions_(
          ("functions_" + ComposeName(neutral, bachelor, daughters)).c_str()) {}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdf_, ComposeName(neutral_, bachelor_, daughters_).c_str());
}

