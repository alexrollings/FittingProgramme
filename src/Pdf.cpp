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
      prodPdfBu_(nullptr),
      prodPdfBuPartial_(nullptr),
      prodPdfDelta_(nullptr),
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
  // if (Configuration::Get().fitBuPartial() == true) {
  //   simPdf.addPdf(*addPdfBuPartial_,
  //                 CategoryName(Mass::buDeltaPartial).c_str());
  // }
  // if (Configuration::Get().fit1D() == false) {
  //   simPdf.addPdf(*addPdfDelta_, CategoryName(Mass::delta).c_str());
  // }
  simPdf.addPdf(*prodPdfBu_, CategoryName(Mass::buDelta).c_str());
  if (Configuration::Get().fitBuPartial() == true) {
    simPdf.addPdf(*prodPdfBuPartial_,
                  CategoryName(Mass::buDeltaPartial).c_str());
  }
  if (Configuration::Get().fit1D() == false) {
    simPdf.addPdf(*prodPdfDelta_, CategoryName(Mass::delta).c_str());
  }
}

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
Pdf<_neutral, _bachelor, _daughters, _charge>
    &Pdf<_neutral, _bachelor, _daughters, _charge>::Get(int uniqueId) {
  static std::map<int, std::shared_ptr<This_t>> singletons;
  // An iterator to a map is a std::pair<key, value>, so we need to call
  // i->second to get the value
  auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
  if (it == singletons.end()) {
    // If it doesn't, create it as a new unique_ptr by calling emplace, which
    // will forward the pointer to the constructor of std::unique_ptr
    it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId))
             .first;
  }
  return *it->second;
}

// Instantiations
void InstantiatePdfs() {
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::plus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::minus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::total>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::plus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::minus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::total>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::plus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::minus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::total>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::plus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::minus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::total>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::plus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::minus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::total>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::plus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::minus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::total>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::plus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::minus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::total>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::plus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::minus>::Get(-1);
  Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::total>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::plus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::minus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::total>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::plus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::minus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::total>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi, Charge::plus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi, Charge::minus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi, Charge::total>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::plus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::minus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::total>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::plus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::minus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::total>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::plus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::minus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::total>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::plus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::minus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::total>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::plus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::minus>::Get(-1);
  Pdf<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::total>::Get(-1);
}
