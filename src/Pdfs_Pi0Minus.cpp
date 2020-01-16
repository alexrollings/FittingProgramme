#include "Fitting.h"

#include <vector>
#include "Configuration.h"

void AddPdfsPi0Minus(Configuration &config,
                     std::vector<Daughters> const &daughtersVec, int id,
                     std::vector<PdfBase *> &pdfs) {
  for (auto &d : daughtersVec) {
    switch (d) {
      case Daughters::kpi:
        pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                               Charge::minus>::Get(id));
        pdfs.emplace_back(
            &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::minus>::Get(
                id));
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::minus>::Get(id)
            .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::minus>::Get(id)
            .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::minus>::Get(id)
            .CreateBuAddPdf();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::minus>::Get(id)
            .CreateBuAddPdf();
        if (config.fit1D() == false) {
          Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::minus>::Get(
              id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::minus>::Get(id)
              .CreateDeltaAddPdf();
        }
        break;
      case Daughters::kk:
        pdfs.emplace_back(
            &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::minus>::Get(
                id));
        pdfs.emplace_back(
            &Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::minus>::Get(
                id));
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::minus>::Get(id)
            .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::minus>::Get(id)
            .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::minus>::Get(id)
            .CreateBuAddPdf();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::minus>::Get(id)
            .CreateBuAddPdf();
        if (config.fit1D() == false) {
          Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::minus>::Get(id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::minus>::Get(id)
              .CreateDeltaAddPdf();
        }
        break;
      case Daughters::pipi:
        pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                               Charge::minus>::Get(id));
        pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                               Charge::minus>::Get(id));
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::minus>::Get(id)
            .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::minus>::Get(id)
            .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::minus>::Get(id)
            .CreateBuAddPdf();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::minus>::Get(id)
            .CreateBuAddPdf();
        if (config.fit1D() == false) {
          Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::minus>::Get(
              id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::minus>::Get(
              id)
              .CreateDeltaAddPdf();
        }
        break;
      case Daughters::pik:
        pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                               Charge::minus>::Get(id));
        pdfs.emplace_back(
            &Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::minus>::Get(
                id));
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::minus>::Get(id)
            .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::minus>::Get(id)
            .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::minus>::Get(id)
            .CreateBuAddPdf();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::minus>::Get(id)
            .CreateBuAddPdf();
        if (config.fit1D() == false) {
          Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::minus>::Get(
              id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::minus>::Get(id)
              .CreateDeltaAddPdf();
        }
        break;
    }
  }
}
