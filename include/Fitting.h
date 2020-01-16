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
