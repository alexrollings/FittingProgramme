#pragma once

#include "Pdf.h"

void AddPdfsGammaTotal(Configuration &config,
                      std::vector<Daughters> const &daughtersVec, int id,
                      std::vector<PdfBase *> &pdfs);

void AddPdfsGammaPlus(Configuration &config,
                      std::vector<Daughters> const &daughtersVec, int id,
                      std::vector<PdfBase *> &pdfs);

void AddPdfsGammaMinus(Configuration &config,
                       std::vector<Daughters> const &daughtersVec, int id,
                       std::vector<PdfBase *> &pdfs);

void AddPdfsPi0Total(Configuration &config,
                      std::vector<Daughters> const &daughtersVec, int id,
                      std::vector<PdfBase *> &pdfs);

void AddPdfsPi0Plus(Configuration &config,
                      std::vector<Daughters> const &daughtersVec, int id,
                      std::vector<PdfBase *> &pdfs);

void AddPdfsPi0Minus(Configuration &config,
                       std::vector<Daughters> const &daughtersVec, int id,
                       std::vector<PdfBase *> &pdfs);

std::pair<RooSimultaneous *, std::vector<PdfBase *> > MakeSimultaneousPdf(
    int const id, Configuration &config,
    std::vector<Daughters> const &daughtersVec,
    std::vector<Charge> const &chargeVec);
void MakeMapFittingDataSet(
    PdfBase &pdf, std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
    std::map<std::string, RooDataSet *> &mapFittingDataSet,
    Configuration &config);
