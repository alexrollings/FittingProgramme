#include "Pdf.h"
#include "Configuration.h"

PdfBase::PdfBase(Neutral neutral, Bachelor bachelor, Daughters daughters)
    : neutral_(neutral), bachelor_(bachelor), daughters_(daughters),
      addPdf_(nullptr), bu2Dst0H_D0pi0Yield_(nullptr),
      bu2Dst0H_D0gammaYield_(nullptr), nonTmSignalYield_(nullptr),
      bu2Dst0Hst_D0pi0Yield_(nullptr), bu2Dst0Hst_D0gammaYield_(nullptr),
      bu2D0HYield_(nullptr), bu2D0HstYield_(nullptr), bd2DstHYield_(nullptr),
      missIdYield_(nullptr),
      combinatorialConstant_(
          ("combinatorialConstant_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "Combinatorial parameter", 0, -0.00001, 0.00001),
      combinatorial_(new RooExponential(
          ("combinatorial_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "combinatorial exponential", Configuration::Get().buMass(),
          combinatorialConstant_)),
      combinatorialYield_(
          ("combinatorialYield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "combinatorial yield", 10000, 0, 30000),
      yields_(
          ("yields_" + ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str()),
      functions_(("functions_" +
                  ComposeFittingCategoryName(neutral, bachelor, daughters))
                     .c_str()),
      bachelorSF_(),
      daughtersSF_() {}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(
      *addPdf_,
      ComposeFittingCategoryName(neutral_, bachelor_, daughters_).c_str());
}
