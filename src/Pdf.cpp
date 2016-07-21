#include "Pdf.h"
#include "Configuration.h"

PdfBase::PdfBase(Neutral neutral, Bachelor bachelor, Daughters daughters)
    : neutral_(neutral), bachelor_(bachelor), daughters_(daughters),
      addPdf_(nullptr),
      combinatorialConstant_(
          ("combinatorialConstant_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "Combinatorial parameter", 0.1, -1, 1),
      combinatorial_(new RooExponential(
          ("combinatorial_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "combinatorial exponential", Configuration::Get().buMass(),
          combinatorialConstant_)),
      bu2Dst0H_D0pi0Yield_(
          ("bu2Dst0H_D0pi0Yield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "bu2Dst0H_D0pi0 yield", 10000, 0, 30000),
      bu2Dst0H_D0gammaYield_(
          ("bu2Dst0H_D0gammaYield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "bu2Dst0H_D0gamma yield", 10000, 0, 30000),
      nonTmSignalYield_(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "nonTmSignal yield", 10000, 0, 30000),
      bu2Dst0Hst_D0pi0Yield_(
          ("bu2Dst0Hst_D0pi0Yield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "bu2Dst0Hst_D0pi0 yield", 10000, 0, 30000),
      bu2Dst0Hst_D0gammaYield_(
          ("bu2Dst0Hst_D0gammaYield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "bu2Dst0Hst_D0gamma yield", 10000, 0, 30000),
      bu2D0HYield_(("bu2D0HYield_" +
                    ComposeFittingCategoryName(neutral, bachelor, daughters))
                       .c_str(),
                   "bu2D0H yield", 10000, 0, 30000),
      bu2D0HstYield_(("bu2D0HstYield_" +
                      ComposeFittingCategoryName(neutral, bachelor, daughters))
                         .c_str(),
                     "bu2D0Hst yield", 10000, 0, 30000),
      bd2DstHYield_(("bd2DstHYield_" +
                     ComposeFittingCategoryName(neutral, bachelor, daughters))
                        .c_str(),
                    "bd2DstH yield", 10000, 0, 30000),
      missIdYield_(("missIdYield_" +
                    ComposeFittingCategoryName(neutral, bachelor, daughters))
                       .c_str(),
                   "missId yield", 10000, 0, 30000),
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
                     .c_str()) {}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(
      *addPdf_,
      ComposeFittingCategoryName(neutral_, bachelor_, daughters_).c_str());
}
