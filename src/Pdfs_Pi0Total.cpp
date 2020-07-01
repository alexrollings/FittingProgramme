#include "Fitting.h"

#include <vector>
#include "Configuration.h"

void AddPdfsPi0Total(Configuration &config,
                     std::vector<Daughters> const &daughtersVec, int id,
                     std::vector<PdfBase *> &pdfs) {
  for (auto &d : daughtersVec) {
    switch (d) {
      case Daughters::kpi:
        pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                               Charge::total>::Get(id));
        pdfs.emplace_back(
            &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::total>::Get(
                id));
        // Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        // Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::total>::Get(id)
            .CreateBuAddPdf();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::total>::Get(id)
            .CreateBuAddPdf();
        if (config.fit1D() == false) {
          Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::total>::Get(id)
              .CreateDeltaAddPdf();
        }
        break;
      case Daughters::kk:
        pdfs.emplace_back(
            &Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::total>::Get(
                id));
        pdfs.emplace_back(
            &Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::total>::Get(
                id));
        // Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        // Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::total>::Get(id)
            .CreateBuAddPdf();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::total>::Get(id)
            .CreateBuAddPdf();
        if (config.fit1D() == false) {
          Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk, Charge::total>::Get(id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::pi0, Bachelor::k, Daughters::kk, Charge::total>::Get(id)
              .CreateDeltaAddPdf();
        }
        break;
      case Daughters::pipi:
        pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi,
                               Charge::total>::Get(id));
        pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi,
                               Charge::total>::Get(id));
        // Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        // Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::total>::Get(id)
            .CreateBuAddPdf();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::total>::Get(id)
            .CreateBuAddPdf();
        if (config.fit1D() == false) {
          Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
        }
        break;
      case Daughters::pik:
        pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik,
                               Charge::total>::Get(id));
        pdfs.emplace_back(
            &Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::total>::Get(
                id));
        // Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        // Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::total>::Get(id)
            .CreateBuAddPdf();
        Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::total>::Get(id)
            .CreateBuAddPdf();
        if (config.fit1D() == false) {
          Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::pi0, Bachelor::k, Daughters::pik, Charge::total>::Get(id)
              .CreateDeltaAddPdf();
        }
        break;
    }
  }
}
