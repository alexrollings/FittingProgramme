#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooAddPdf.h"
#include "RooHistPdf.h"

#include "TStyle.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TAttFill.h"
#include "TLine.h"
#include "TPad.h"
#include "TH1.h"
#include "TH2.h"

#include "Configuration.h"

void Plotting2D(Configuration &config, RooDataSet &toyDS, RooDataSet &dataDS);
void GenerateToyFromData(std::unique_ptr<RooDataSet> &dataSet,
                         std::unique_ptr<RooDataSet> &toyDataSet, int const id,
                         Configuration &config);
