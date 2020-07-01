#include "Pdf.h"

PdfBase::PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor,
                 Daughters daughters, Charge charge)
    : uniqueId_(uniqueId),
      neutral_(neutral),
      bachelor_(bachelor),
      daughters_(daughters),
      charge_(charge),
      addPdfBu_(nullptr),
      addPdfBuPartial_(nullptr),
      addPdfDelta_(nullptr),
      N_misId_Bu2Dst0h_D0gamma_(nullptr),
      N_misId_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_MisRec_(nullptr),
      N_misId_Bu2D0h_(nullptr),
      N_misId_PartRec_(nullptr),
      N_misId_Delta_Bu2Dst0h_D0gamma_(nullptr),
      N_misId_Delta_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_Delta_MisRec_(nullptr),
      N_misId_Delta_Bu2D0h_(nullptr),
      N_misId_Delta_PartRec_(nullptr),
      N_misId_Bu_Bu2Dst0h_D0gamma_(nullptr),
      N_misId_Bu_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_Bu_MisRec_(nullptr),
      N_misId_Bu_Bu2D0h_(nullptr),
      N_misId_Bu_PartRec_(nullptr),
      N_misId_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_BuPartial_MisRec_(nullptr),
      N_misId_BuPartial_Bu2D0h_(nullptr),
      N_misId_BuPartial_PartRec_(nullptr),
      yieldsBu_(("yieldsBu_" +
                 ComposeName(uniqueId_, neutral, bachelor, daughters, charge))
                    .c_str()),
      yieldsBuPartial_(
          ("yieldsBuPartial_" +
           ComposeName(uniqueId_, neutral, bachelor, daughters, charge))
              .c_str()),
      yieldsDelta_(("yieldsDelta_" + ComposeName(uniqueId_, neutral, bachelor,
                                                 daughters, charge))
                       .c_str()),
      functionsBu_(("functionsBu_" + ComposeName(uniqueId_, neutral, bachelor,
                                                 daughters, charge))
                       .c_str()),
      functionsBuPartial_(
          ("functionsBuPartial_" +
           ComposeName(uniqueId_, neutral, bachelor, daughters, charge))
              .c_str()),
      functionsDelta_(
          ("functionsDelta_" +
           ComposeName(uniqueId_, neutral, bachelor, daughters, charge))
              .c_str()) {
  // std::cout << "Constructing PDF " << EnumToString(neutral_) << " "
  //           << EnumToString(bachelor_) << " " << EnumToString(daughters_)
  //           << std::endl;
}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdfBu_, CategoryName(Mass::buDelta).c_str());
  if (Configuration::Get().fitBuPartial() == true) {
    simPdf.addPdf(*addPdfBuPartial_,
                  CategoryName(Mass::buDeltaPartial).c_str());
  }
  if (Configuration::Get().fit1D() == false) {
    simPdf.addPdf(*addPdfDelta_, CategoryName(Mass::delta).c_str());
  }
}
