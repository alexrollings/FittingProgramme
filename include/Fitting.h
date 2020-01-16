#pragma once

#include "Pdf.h"

void AddPdfsGammaPlus(Configuration &config,
                      std::vector<Daughters> const &daughtersVec, int id,
                      std::vector<PdfBase *> &pdfs);

void AddPdfsGammaMinus(Configuration &config,
                       std::vector<Daughters> const &daughtersVec, int id,
                       std::vector<PdfBase *> &pdfs);
