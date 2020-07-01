#include "Fitting.h"

#include <vector>
#include "Configuration.h"

void AddPdfsGammaTotal(Configuration &config,
                       std::vector<Daughters> const &daughtersVec, int id,
                       std::vector<PdfBase *> &pdfs) {
  for (auto &d : daughtersVec) {
    switch (d) {
      case Daughters::kpi:
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                               Charge::total>::Get(id));
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                               Charge::total>::Get(id));
        // Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::total>::Get(
        //     id)
        //     .AssignMisIdYields();
        // Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::total>::Get(
            id)
            .CreateBuAddPdf();
        Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::total>::Get(id)
            .CreateBuAddPdf();
        if (config.fitBuPartial() == true) {
          Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::total>::Get(
              id)
              .CreateBuPartialAddPdf();
          Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::total>::Get(
              id)
              .CreateBuPartialAddPdf();
        }
        if (config.fit1D() == false) {
          Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
        }
        break;
      case Daughters::kk:
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk,
                               Charge::total>::Get(id));
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kk,
                               Charge::total>::Get(id));
        // Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        // Pdf<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::total>::Get(id)
            .CreateBuAddPdf();
        Pdf<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::total>::Get(id)
            .CreateBuAddPdf();
        if (config.fitBuPartial() == true) {
          Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::total>::Get(
              id)
              .CreateBuPartialAddPdf();
          Pdf<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::total>::Get(
              id)
              .CreateBuPartialAddPdf();
        }
        if (config.fit1D() == false) {
          Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::gamma, Bachelor::k, Daughters::kk, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
        }
        break;
      case Daughters::pipi:
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
                               Charge::total>::Get(id));
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi,
                               Charge::total>::Get(id));
        // Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi, Charge::total>::Get(
        //     id)
        //     .AssignMisIdYields();
        // Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::total>::Get(
        //     id)
        //     .AssignMisIdYields();
        Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi, Charge::total>::Get(
            id)
            .CreateBuAddPdf();
        Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::total>::Get(
            id)
            .CreateBuAddPdf();
        if (config.fitBuPartial() == true) {
          Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
              Charge::total>::Get(id)
              .CreateBuPartialAddPdf();
          Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::total>::Get(
              id)
              .CreateBuPartialAddPdf();
        }
        if (config.fit1D() == false) {
          Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi,
              Charge::total>::Get(id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
        }
        break;
      case Daughters::pik:
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik,
                               Charge::total>::Get(id));
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::pik,
                               Charge::total>::Get(id));
        // Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::total>::Get(
        //     id)
        //     .AssignMisIdYields();
        // Pdf<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::total>::Get(id)
        //     .AssignMisIdYields();
        Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::total>::Get(
            id)
            .CreateBuAddPdf();
        Pdf<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::total>::Get(id)
            .CreateBuAddPdf();
        if (config.fitBuPartial() == true) {
          Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::total>::Get(
              id)
              .CreateBuPartialAddPdf();
          Pdf<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::total>::Get(
              id)
              .CreateBuPartialAddPdf();
        }
        if (config.fit1D() == false) {
          Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
          Pdf<Neutral::gamma, Bachelor::k, Daughters::pik, Charge::total>::Get(
              id)
              .CreateDeltaAddPdf();
        }
        break;
    }
  }
}
