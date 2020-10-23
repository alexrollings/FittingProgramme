#include "ToyFunctions.h"

void ToyTestD1D(std::unique_ptr<RooSimultaneous> &simPdf,
                std::unique_ptr<RooFitResult> &dataFitResult,
                Configuration &config,
                std::vector<Daughters> const &daughtersVec,
                std::vector<Charge> const &chargeVec,
                std::string const &outputDir, int nToys) {
  // Start from 1 as id = 0 is data fit params
  for (int id = 1; id < nToys + 1; ++id) {
    std::cout << "\n\n -------------------------- Running toy #" << id
              << " -------------------------- \n\n";

    if (simPdf == nullptr) {
      // id=0, equivalent to what would be the data fit
      int tmpId = 0;
      auto p = MakeSimultaneousPdf(tmpId, config, daughtersVec, chargeVec);
      simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    }

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<UInt_t> dist;
    UInt_t seed = dist(rng);
    // UInt_t seed = 0x96b725da;
    RooRandom::randomGenerator()->SetSeed(seed);

    double nEvtsPerToy = simPdf->expectedEvents(config.fitting);
    std::unique_ptr<RooDataSet> toyDataSet;
    if (config.fit1D() == false) {
      toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
          RooArgSet(config.buDeltaMass(), config.deltaMass(), config.fitting),
          nEvtsPerToy));
    } else {
      toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
          RooArgSet(config.buDeltaMass(), config.fitting), nEvtsPerToy));
    }
    toyDataSet->SetName(("toyDataSet_" + std::to_string(id)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(id)).c_str(),
                                ("toyDataHist" + std::to_string(id)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
        ("simPdfFit_" + std::to_string(id)).c_str(),
        ("simPdfFit_" + std::to_string(id)).c_str(), config.fitting));

    auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
    simPdfToFit = std::unique_ptr<RooSimultaneous>(p.first);

    std::shared_ptr<RooFitResult> toyFitResult;
    if (config.noFit() == false) {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          RooFit::Offset(true), RooFit::NumCPU(config.nCPU())));
      toyFitResult->SetName("ToyResult");
    }
    if (id == 1) {
      auto pdfs = p.second;
      std::map<Neutral, std::map<Mass, double> > yMaxMap;
      for (auto &p : pdfs) {
        Plotting1D(id, *p, config, *toyAbsData, *simPdfToFit, outputDir,
                   toyFitResult.get(), yMaxMap);
      }
      if (config.noFit() == false) {
        PlotCorrelations(toyFitResult.get(), outputDir, config);
      }
    }

    if (config.noFit() == false) {
      toyFitResult->Print("v");
      std::string dimString = "D1D";
      if (config.fit1D() == true) {
        dimString = "1D";
      }
      std::stringstream filename;
      filename << outputDir << "/results/Result" + dimString + "_"
               << config.ReturnBoxString() << "_" << std::hex << seed
               << ".root";
      TFile outputFile(filename.str().c_str(), "recreate");

      outputFile.cd();
      toyFitResult->Write();
      if (dataFitResult != nullptr) {
        dataFitResult->Write();
      }
      outputFile.Close();
      std::cout << "Results saved to file " << outputFile.GetName() << "\n";
    }
  }
}

void RunToysD1DPdf(std::unique_ptr<RooSimultaneous> &simPdf, TFile &outputFile,
                   Configuration &config,
                   std::unique_ptr<RooFitResult> &dataFitResult,
                   std::vector<Daughters> const &daughtersVec,
                   std::vector<Charge> const &chargeVec,
                   std::string const &outputDir, int id) {
  std::cout << "\n\n -------------------------- Running toy #" << id
            << " -------------------------- \n\n";
  double nEvtsPerToy = simPdf->expectedEvents(config.fitting);
  std::unique_ptr<RooDataSet> toyDataSet;

  if (config.fit1D() == false) {
    toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
        RooArgSet(config.buDeltaMass(), config.deltaMass(), config.fitting),
        nEvtsPerToy));
  } else {
    toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
        RooArgSet(config.buDeltaMass(), config.fitting), nEvtsPerToy));
  }

  toyDataSet->SetName(("toyDataSet_" + std::to_string(id)).c_str());
  auto toyDataHist = std::unique_ptr<RooDataHist>(
      toyDataSet->binnedClone(("toyDataHist_" + std::to_string(id)).c_str(),
                              ("toyDataHist" + std::to_string(id)).c_str()));
  auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

  auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
      ("simPdfFit_" + std::to_string(id)).c_str(),
      ("simPdfFit_" + std::to_string(id)).c_str(), config.fitting));

  auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
  simPdfToFit = std::unique_ptr<RooSimultaneous>(p.first);

  std::shared_ptr<RooFitResult> toyFitResult;
  if (config.noFit() == false) {
    toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
        *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"), RooFit::Offset(true),
        RooFit::NumCPU(config.nCPU())));
    // if (config.neutral() == Neutral::pi0) {
    //   toyFitResult = std::unique_ptr<RooFitResult>(simPdfToFit->fitTo(
    //       *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
    //       RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
    //       RooFit::Offset(true), RooFit::NumCPU(config.nCPU()),
    //       RooFit::ExternalConstraints(
    //           NeutralVars<Neutral::pi0>::Get(id).constraints_argSet())));
    // } else {
    //   toyFitResult = std::unique_ptr<RooFitResult>(simPdfToFit->fitTo(
    //       *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
    //       RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
    //       RooFit::Offset(true), RooFit::NumCPU(config.nCPU()),
    //       RooFit::ExternalConstraints(
    //           NeutralVars<Neutral::gamma>::Get(id).constraints_argSet())));
    // }
    toyFitResult->SetName("ToyResult");
  }
  // if (id == 1) {
  //   auto pdfs = p.second;
  //   std::map<Neutral, std::map<Mass, double> > yMaxMap;
  //   for (auto &p : pdfs) {
  //     Plotting1D(id, *p, config, *toyAbsData, *simPdfToFit, outputDir,
  //                toyFitResult.get(), yMaxMap);
  //   }
  //   if (config.noFit() == false) {
  //     PlotCorrelations(toyFitResult.get(), outputDir, config);
  //   }
  // }
  if (config.noFit() == false) {
    // to make a unique result each time
    toyFitResult->Print("v");
    outputFile.cd();
    toyFitResult->Write();
    dataFitResult->Write();
    outputFile.Close();
    std::cout << toyFitResult->GetName() << " has been saved to file "
              << outputFile.GetName() << "\n";
  }
}

void RunToys2DPdf(std::vector<PdfBase *> &pdfs,
                  std::map<std::string, RooDataSet *> &mapDataLabelData,
                  std::unique_ptr<RooSimultaneous> &simPdf, TFile &outputFile,
                  std::unique_ptr<RooFitResult> &dataFitResult,
                  Configuration &config, std::string const &outputDir,
                  std::vector<Daughters> const &daughtersVec,
                  std::vector<Charge> const &chargeVec, int id) {
  std::cout << "\n\n -------------------------- Running 2D PDF toy #" << id
            << " -------------------------- \n\n";

  std::map<std::string, RooDataSet *> mapDataLabelToy;

  for (auto &p : pdfs) {
    if (config.neutral() == Neutral::pi0) {
      GenerateToyFromPi0Pdf(mapDataLabelToy, mapDataLabelData, id, *p, config,
                            outputDir);
    } else {
      GenerateToyFromGammaPdf(mapDataLabelToy, mapDataLabelData, id, *p, config,
                              outputDir);
    }
  }

  for (auto &m : mapDataLabelToy) {
    m.second->Print();
  }

  std::map<std::string, RooDataSet *> mapFittingToy;
  for (auto &p : pdfs) {
    MakeMapFittingDataSet(*p, mapDataLabelToy, mapFittingToy, config);
  }

  RooDataSet toyDataSet("toyDataSet", "toyDataSet", config.fittingArgSet(),
                        RooFit::Index(config.fitting),
                        RooFit::Import(mapFittingToy));

  auto toyDataHist = std::unique_ptr<RooDataHist>(
      toyDataSet.binnedClone(("toyDataHist_" + std::to_string(id)).c_str(),
                             ("toyDataHist" + std::to_string(id)).c_str()));
  auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

  auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
      ("simPdfFit_" + std::to_string(id)).c_str(),
      ("simPdfFit_" + std::to_string(id)).c_str(), config.fitting));

  auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
  simPdfToFit = std::unique_ptr<RooSimultaneous>(p.first);

  std::shared_ptr<RooFitResult> toyFitResult;
  if (config.noFit() == false) {
    toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
        *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"), RooFit::Offset(true),
        RooFit::NumCPU(config.nCPU())));
    toyFitResult->SetName("ToyResult");
    // toyFitResult->SetName(("ToyResult_" + std::to_string(id)).c_str());
  }

  // if (id == 1) {
  //   auto toyPdfs = p.second;
  //   std::map<Neutral, std::map<Mass, double> > yMaxMap;
  //   for (auto &p : toyPdfs) {
  //     Plotting1D(id, *p, config, *toyAbsData, *simPdfToFit, outputDir,
  //                toyFitResult.get(), yMaxMap);
  //   }
  //   if (config.noFit() == false) {
  //     PlotCorrelations(toyFitResult.get(), outputDir, config);
  //   }
  // }
  if (config.noFit() == false) {
    // to make a unique result each time
    toyFitResult->Print("v");
    outputFile.cd();
    toyFitResult->Write();
    dataFitResult->Write();
    outputFile.Close();
    std::cout << toyFitResult->GetName() << " has been saved to file "
              << outputFile.GetName() << "\n";
  }
}

void RunToys2DData(TFile &outputFile,
                   std::unique_ptr<RooFitResult> &dataFitResult,
                   std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
                   Configuration &config,
                   std::vector<Daughters> const &daughtersVec,
                   std::vector<Charge> const &chargeVec,
                   std::string const &outputDir, int id) {
  std::cout << "\n\n -------------------------- Running toy #" << id
            << " -------------------------- \n\n";
  auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
  auto pdfs = p.second;

  std::map<std::string, RooDataSet *> mapDataLabelToy;

  for (auto &p : pdfs) {
    GenerateToyFromData(mapDataLabelDataSet, mapDataLabelToy, id, *p, config,
                        outputDir);
  }

  auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);

  std::map<std::string, RooDataSet *> mapFittingDataSet;
  std::map<std::string, RooDataSet *> mapFittingToy;
  for (auto &p : pdfs) {
    MakeMapFittingDataSet(*p, mapDataLabelDataSet, mapFittingDataSet, config);
    MakeMapFittingDataSet(*p, mapDataLabelToy, mapFittingToy, config);
  }

  RooDataSet toyDataSet("toyDataSet", "toyDataSet", config.fittingArgSet(),
                        RooFit::Index(config.fitting),
                        RooFit::Import(mapFittingToy));

  auto toyDataHist = std::unique_ptr<RooDataHist>(
      toyDataSet.binnedClone("toyDataHist", "toyDataHist"));
  if (toyDataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }
  auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());
  if (toyAbsData == nullptr) {
    throw std::runtime_error("Could not cast to RooAbsData.");
  }

  std::shared_ptr<RooFitResult> toyFitResult;
  if (config.noFit() == false) {
    toyFitResult = std::shared_ptr<RooFitResult>(
        simPdf->fitTo(*toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                      RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                      RooFit::Offset(true), RooFit::NumCPU(config.nCPU())));
    // toyFitResult->SetName(("ToyResult_" + std::to_string(id)).c_str());
    toyFitResult->SetName("ToyResult");
  }

  RooDataSet dataSet("dataSet", "dataSet", config.fittingArgSet(),
                     RooFit::Index(config.fitting),
                     RooFit::Import(mapFittingDataSet));

  std::cout << "\n\n\n";
  toyDataSet.Print();
  dataSet.Print();
  std::cout << "\n\n\n";

  // if (id == 1) {
  //   for (auto &p : pdfs) {
  //     std::string toyLabel = "toy";
  //     std::string dataLabel = "data";
  //     Plotting2D(dataSet, id, *p, config, outputDir, dataLabel);
  //     Plotting2D(toyDataSet, id, *p, config, outputDir, toyLabel);
  //   }
  //   std::map<Neutral, std::map<Mass, double> > yMaxMap;
  //   for (auto &p : pdfs) {
  //     Plotting1D(id, *p, config, *toyAbsData, *simPdf, outputDir,
  //                toyFitResult.get(), yMaxMap);
  //   }
  //   if (config.noFit() == false) {
  //     PlotCorrelations(toyFitResult.get(), outputDir, config);
  //   }
  // }
  if (config.noFit() == false) {
    // to make a unique result each time
    toyFitResult->Print("v");
    outputFile.cd();
    toyFitResult->Write();
    dataFitResult->Write();
    outputFile.Close();
    std::cout << toyFitResult->GetName() << " has been saved to file "
              << outputFile.GetName() << "\n";
  }
}

void PrintEvents(RooDataSet *genData,
                 std::map<std::string, RooDataSet *> &mapDataLabelData,
                 std::map<std::string, RooDataSet *> &mapDataLabelToy,
                 Configuration &config, PdfBase &pdf) {
  Neutral neutral = pdf.neutral();
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Charge charge = pdf.charge();

  genData->Print();
  mapDataLabelData[ComposeDataLabelName(neutral, bachelor, daughters, charge)]
      ->Print();

  std::cout << "# of events in toy DS = " << genData->numEntries() << "\n";
  std::cout << "Generated!" << std::endl;

  RooAbsData *gds = genData->reduce(
      ("(Delta_M>" + std::to_string(config.deltaLow()) + "&&Delta_M<" +
       std::to_string(config.deltaHigh()) + ")||(Bu_Delta_M>" +
       std::to_string(config.buDeltaLow()) + "&&Bu_Delta_M<" +
       std::to_string(config.buDeltaHigh()) + ")")
          .c_str());
  std::cout << "nEvts = " << gds->numEntries() << "\n";
  std::cout << "nEvts in box = "
            << gds->reduce(("(Delta_M>" + std::to_string(config.deltaLow()) +
                            "&&Delta_M<" + std::to_string(config.deltaHigh()) +
                            ")&&(Bu_Delta_M>" +
                            std::to_string(config.buDeltaLow()) +
                            "&&Bu_Delta_M<" +
                            std::to_string(config.buDeltaHigh()) + ")")
                               .c_str())
                   ->numEntries()
            << "\n";

  std::cout << "nEvts in delta = "
            << gds->reduce(("(Bu_Delta_M>" +
                            std::to_string(config.buDeltaLow()) +
                            "&&Bu_Delta_M<" +
                            std::to_string(config.buDeltaHigh()) + ")")
                               .c_str())
                   ->numEntries()
            << "\n";

  std::cout << "nEvts in bu = "
            << gds->reduce(("(Delta_M>" + std::to_string(config.deltaLow()) +
                            "&&Delta_M<" + std::to_string(config.deltaHigh()) +
                            ")")
                               .c_str())
                   ->numEntries()
            << "\n";
  RooAbsData *ds =
      mapDataLabelData[ComposeDataLabelName(neutral, bachelor, daughters,
                                            charge)]
          ->reduce(("(Delta_M>" + std::to_string(config.deltaLow()) +
                    "&&Delta_M<" + std::to_string(config.deltaHigh()) +
                    ")||(Bu_Delta_M>" + std::to_string(config.buDeltaLow()) +
                    "&&Bu_Delta_M<" + std::to_string(config.buDeltaHigh()) +
                    ")")
                       .c_str());
  std::cout << "nEvts = " << ds->numEntries() << "\n";
  std::cout << "nEvts in box = "
            << ds->reduce(("(Delta_M>" + std::to_string(config.deltaLow()) +
                           "&&Delta_M<" + std::to_string(config.deltaHigh()) +
                           ")&&(Bu_Delta_M>" +
                           std::to_string(config.buDeltaLow()) +
                           "&&Bu_Delta_M<" +
                           std::to_string(config.buDeltaHigh()) + ")")
                              .c_str())
                   ->numEntries()
            << "\n";

  std::cout << "nEvts in delta = "
            << ds->reduce(("(Bu_Delta_M>" +
                           std::to_string(config.buDeltaLow()) +
                           "&&Bu_Delta_M<" +
                           std::to_string(config.buDeltaHigh()) + ")")
                              .c_str())
                   ->numEntries()
            << "\n";

  std::cout << "nEvts in bu = "
            << ds->reduce(("(Delta_M>" + std::to_string(config.deltaLow()) +
                           "&&Delta_M<" + std::to_string(config.deltaHigh()) +
                           ")")
                              .c_str())
                   ->numEntries()
            << "\n";

  if (mapDataLabelToy.find(ComposeDataLabelName(
          neutral, bachelor, daughters, charge)) == mapDataLabelToy.end()) {
    mapDataLabelToy.insert(std::make_pair(
        ComposeDataLabelName(neutral, bachelor, daughters, charge), genData));
    std::cout << "Created key-value pair for category " +
                     ComposeDataLabelName(neutral, bachelor, daughters,
                                          charge) +
                     " and corresponding toy\n";
  } else {
    mapDataLabelToy[ComposeDataLabelName(neutral, bachelor, daughters, charge)]
        ->append(*genData);
    std::cout << "Appended toy to category " +
                     ComposeDataLabelName(neutral, bachelor, daughters,
                                          charge) +
                     "\n";
  }
}

void CalculateNEvtsToGenerate(RooArgList &yields2d, double &N_2d) {
  double nYields = yields2d.getSize();
  RooAbsArg *N_AbsArg = nullptr;
  RooAbsReal *N_AbsReal = nullptr;
  for (double i = 0; i < nYields; ++i) {
    std::string N_str = yields2d.at(i)->GetName();
    N_AbsArg = yields2d.find(N_str.c_str());
    if (N_AbsArg == nullptr) {
      throw std::runtime_error("N_AbsArg gives nullptr for " + N_str);
    }
    N_AbsReal = dynamic_cast<RooAbsReal *>(N_AbsArg);
    if (N_AbsReal == nullptr) {
      throw std::runtime_error("Canot cast AbsArg to AbsReal for " + N_str);
    }
    N_2d += N_AbsReal->getVal();
  }
}

void GenerateToyFromGammaPdf(
    std::map<std::string, RooDataSet *> &mapDataLabelToy,
    std::map<std::string, RooDataSet *> &mapDataLabelData, int id, PdfBase &pdf,
    Configuration &config, std::string const &outputDir) {
  std::cout << "Generating toy from gamma PDF\n";
  Neutral neutral = pdf.neutral();
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Charge charge = pdf.charge();
  RooArgList functions2d;
  RooArgList yields2d;

  RooProdPdf pdf2d_Bu2Dst0h_D0gamma(
      ("pdf2d_Bu2Dst0h_D0gamma_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_Bu2Dst0h_D0gamma(), pdf.pdfDelta_Bu2Dst0h_D0gamma()));
  functions2d.add(pdf2d_Bu2Dst0h_D0gamma);
  RooRealVar N_2d_trueId_Bu2Dst0h_D0gamma(
      ("N_2d_trueId_Bu2Dst0h_D0gamma_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu2Dst0h_D0gamma().getVal() /
          pdf.orEffBu2Dst0h_D0gamma().getVal(),
      0, 1000000);
  yields2d.add(N_2d_trueId_Bu2Dst0h_D0gamma);

  RooProdPdf pdf2d_misId_Bu2Dst0h_D0gamma(
      ("pdf2d_misId_Bu2Dst0h_D0gamma_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_misId_Bu2Dst0h_D0gamma(),
                pdf.pdfDelta_misId_Bu2Dst0h_D0gamma()));
  functions2d.add(pdf2d_misId_Bu2Dst0h_D0gamma);
  RooRealVar N_2d_misId_Bu2Dst0h_D0gamma(
      ("N_2d_misId_Bu2Dst0h_D0gamma_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu2Dst0h_D0gamma().getVal() /
          pdf.orEffMisId_Bu2Dst0h_D0gamma().getVal(),
      0, 1000000);
  yields2d.add(N_2d_misId_Bu2Dst0h_D0gamma);

  RooProdPdf *pdf2d_Bu2Dst0h_D0gamma_D02pik = nullptr;
  RooRealVar *N_2d_trueId_Bu2Dst0h_D0gamma_D02pik = nullptr;
  if (daughters == Daughters::pik) {
    pdf2d_Bu2Dst0h_D0gamma_D02pik =
        new RooProdPdf(("pdf2d_Bu2Dst0h_D0gamma_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(pdf.pdfBu_Bu2Dst0h_D0gamma_D02pik(),
                                 pdf.pdfDelta_Bu2Dst0h_D0gamma_D02pik()));
    functions2d.add(*pdf2d_Bu2Dst0h_D0gamma_D02pik);
    N_2d_trueId_Bu2Dst0h_D0gamma_D02pik =
        new RooRealVar(("N_2d_trueId_Bu2Dst0h_D0gamma_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_trueId_Bu2Dst0h_D0gamma_D02pik().getVal() /
                           pdf.orEffBu2Dst0h_D0gamma().getVal(),
                       0, 1000000);
    yields2d.add(*N_2d_trueId_Bu2Dst0h_D0gamma_D02pik);
  }

  RooRealVar fracPdfBu_Bu2Dst0h_D0pi0(
      ("fracPdfBu_Bu2Dst0h_D0pi0" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2Dst0h_D0pi0().getVal() /
          (pdf.N_trueId_Bu_Bu2Dst0h_D0pi0().getVal() +
           pdf.N_trueId_BuPartial_Bu2Dst0h_D0pi0().getVal()));
  RooAddPdf pdfBu_tot_Bu2Dst0h_D0pi0(
      ("pdfBu_tot_Bu2Dst0h_D0pi0" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet((pdf.pdfBu_Bu2Dst0h_D0pi0(), pdf.pdfBuPartial_Bu2Dst0h_D0pi0()),
                fracPdfBu_Bu2Dst0h_D0pi0));
  RooProdPdf pdf2d_Bu2Dst0h_D0pi0(
      ("pdf2d_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdfBu_tot_Bu2Dst0h_D0pi0, pdf.pdfDelta_Bu2Dst0h_D0pi0()));
  functions2d.add(pdf2d_Bu2Dst0h_D0pi0);
  RooRealVar N_2d_trueId_Bu2Dst0h_D0pi0(
      ("N_2d_trueId_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu2Dst0h_D0pi0().getVal() /
          pdf.orEffBu2Dst0h_D0pi0().getVal(),
      0, 1000000);
  yields2d.add(N_2d_trueId_Bu2Dst0h_D0pi0);

  RooRealVar fracPdfBu_misId_Bu2Dst0h_D0pi0(
      ("fracPdfBu_misId_Bu2Dst0h_D0pi0" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu_Bu2Dst0h_D0pi0().getVal() /
          (pdf.N_misId_Bu_Bu2Dst0h_D0pi0().getVal() +
           pdf.N_misId_BuPartial_Bu2Dst0h_D0pi0().getVal()));
  RooAddPdf pdfBu_tot_misId_Bu2Dst0h_D0pi0(
      ("pdfBu_tot_misId_Bu2Dst0h_D0pi0" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet((pdf.pdfBu_misId_Bu2Dst0h_D0pi0(),
                 pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0()),
                fracPdfBu_misId_Bu2Dst0h_D0pi0));
  RooProdPdf pdf2d_misId_Bu2Dst0h_D0pi0(
      ("pdf2d_misId_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdfBu_tot_misId_Bu2Dst0h_D0pi0,
                pdf.pdfDelta_misId_Bu2Dst0h_D0pi0()));
  functions2d.add(pdf2d_misId_Bu2Dst0h_D0pi0);
  RooRealVar N_2d_misId_Bu2Dst0h_D0pi0(
      ("N_2d_misId_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu2Dst0h_D0pi0().getVal() /
          pdf.orEffMisId_Bu2Dst0h_D0pi0().getVal(),
      0, 1000000);
  yields2d.add(N_2d_misId_Bu2Dst0h_D0pi0);

  RooRealVar *fracPdfBu_Bu2Dst0h_D0pi0_D02pik = nullptr;
  RooAddPdf *pdfBu_tot_Bu2Dst0h_D0pi0_D02pik = nullptr;
  RooProdPdf *pdf2d_Bu2Dst0h_D0pi0_D02pik = nullptr;
  RooRealVar *N_2d_trueId_Bu2Dst0h_D0pi0_D02pik = nullptr;
  if (daughters == Daughters::pik) {
    fracPdfBu_Bu2Dst0h_D0pi0_D02pik = new RooRealVar(
        ("fracPdfBu_Bu2Dst0h_D0pi0_D02pik" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik().getVal() /
            (pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik().getVal() +
             pdf.N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik().getVal()));
    pdfBu_tot_Bu2Dst0h_D0pi0_D02pik =
        new RooAddPdf(("pdfBu_tot_Bu2Dst0h_D0pi0_D02pik" +
                       ComposeName(id, neutral, bachelor, daughters, charge))
                          .c_str(),
                      "",
                      RooArgSet((pdf.pdfBu_Bu2Dst0h_D0pi0_D02pik(),
                                 pdf.pdfBuPartial_Bu2Dst0h_D0pi0_D02pik()),
                                *fracPdfBu_Bu2Dst0h_D0pi0_D02pik));
    pdf2d_Bu2Dst0h_D0pi0_D02pik =
        new RooProdPdf(("pdf2d_Bu2Dst0h_D0pi0_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(*pdfBu_tot_Bu2Dst0h_D0pi0_D02pik,
                                 pdf.pdfDelta_Bu2Dst0h_D0pi0_D02pik()));
    functions2d.add(*pdf2d_Bu2Dst0h_D0pi0_D02pik);
    N_2d_trueId_Bu2Dst0h_D0pi0_D02pik =
        new RooRealVar(("N_2d_trueId_Bu2Dst0h_D0pi0_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_trueId_Bu2Dst0h_D0pi0_D02pik().getVal() /
                           pdf.orEffBu2Dst0h_D0pi0().getVal(),
                       0, 1000000);
    yields2d.add(*N_2d_trueId_Bu2Dst0h_D0pi0_D02pik);
  }

  RooRealVar fracPdfBu_Bu2Dst0h_D0gamma_WN(
      ("fracPdfBu_Bu2Dst0h_D0gamma_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2Dst0h_D0gamma_WN().getVal() /
          (pdf.N_trueId_Bu_Bu2Dst0h_D0gamma_WN().getVal() +
           pdf.N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN().getVal()));
  RooAddPdf pdfBu_tot_Bu2Dst0h_D0gamma_WN(
      ("pdfBu_tot_Bu2Dst0h_D0gamma_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet((pdf.pdfBu_Bu2Dst0h_D0gamma_WN(),
                 pdf.pdfBuPartial_Bu2Dst0h_D0gamma_WN()),
                fracPdfBu_Bu2Dst0h_D0gamma_WN));
  RooProdPdf pdf2d_Bu2Dst0h_D0gamma_WN(
      ("pdf2d_Bu2Dst0h_D0gamma_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdfBu_tot_Bu2Dst0h_D0gamma_WN,
                pdf.pdfDelta_Bu2Dst0h_D0gamma_WN()));
  functions2d.add(pdf2d_Bu2Dst0h_D0gamma_WN);
  RooRealVar N_2d_trueId_Bu2Dst0h_D0gamma_WN(
      ("N_2d_trueId_Bu2Dst0h_D0gamma_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu2Dst0h_D0gamma_WN().getVal() /
          pdf.orEffBu2Dst0h_D0gamma_WN().getVal(),
      0, 1000000);
  yields2d.add(N_2d_trueId_Bu2Dst0h_D0gamma_WN);

  RooRealVar fracPdfBu_misId_Bu2Dst0h_D0gamma_WN(
      ("fracPdfBu_misId_Bu2Dst0h_D0gamma_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu_Bu2Dst0h_D0gamma_WN().getVal() /
          (pdf.N_misId_Bu_Bu2Dst0h_D0gamma_WN().getVal() +
           pdf.N_misId_BuPartial_Bu2Dst0h_D0gamma_WN().getVal()));
  RooAddPdf pdfBu_tot_misId_Bu2Dst0h_D0gamma_WN(
      ("pdfBu_tot_misId_Bu2Dst0h_D0gamma_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet((pdf.pdfBu_misId_Bu2Dst0h_D0gamma_WN(),
                 pdf.pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN()),
                fracPdfBu_misId_Bu2Dst0h_D0gamma_WN));
  RooProdPdf pdf2d_misId_Bu2Dst0h_D0gamma_WN(
      ("pdf2d_misId_Bu2Dst0h_D0gamma_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdfBu_tot_misId_Bu2Dst0h_D0gamma_WN,
                pdf.pdfDelta_misId_Bu2Dst0h_D0gamma_WN()));
  functions2d.add(pdf2d_misId_Bu2Dst0h_D0gamma_WN);
  RooRealVar N_2d_misId_Bu2Dst0h_D0gamma_WN(
      ("N_2d_misId_Bu2Dst0h_D0gamma_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu2Dst0h_D0gamma_WN().getVal() /
          pdf.orEffMisId_Bu2Dst0h_D0gamma_WN().getVal(),
      0, 1000000);
  yields2d.add(N_2d_misId_Bu2Dst0h_D0gamma_WN);

  RooProdPdf *pdf2d_Bu2Dst0h_D0gamma_WN_D02pik = nullptr;
  RooRealVar *N_2d_trueId_Bu2Dst0h_D0gamma_WN_D02pik = nullptr;
  if (daughters == Daughters::pik) {
    pdf2d_Bu2Dst0h_D0gamma_WN_D02pik =
        new RooProdPdf(("pdf2d_Bu2Dst0h_D0gamma_WN_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(pdf.pdfBu_Bu2Dst0h_D0gamma_WN_D02pik(),
                                 pdf.pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik()));
    functions2d.add(*pdf2d_Bu2Dst0h_D0gamma_WN_D02pik);
    N_2d_trueId_Bu2Dst0h_D0gamma_WN_D02pik =
        new RooRealVar(("N_2d_trueId_Bu2Dst0h_D0gamma_WN_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_trueId_Bu2Dst0h_D0gamma_WN_D02pik().getVal() /
                           pdf.orEffBu2Dst0h_D0gamma_WN().getVal(),
                       0, 1000000);
    yields2d.add(*N_2d_trueId_Bu2Dst0h_D0gamma_WN_D02pik);
  }

  RooRealVar fracPdfBu_Bu2Dst0h_D0pi0_WN(
      ("fracPdfBu_Bu2Dst0h_D0pi0_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_WN().getVal() /
          (pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_WN().getVal() +
           pdf.N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN().getVal()));
  RooAddPdf pdfBu_tot_Bu2Dst0h_D0pi0_WN(
      ("pdfBu_tot_Bu2Dst0h_D0pi0_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(
          (pdf.pdfBu_Bu2Dst0h_D0pi0_WN(), pdf.pdfBuPartial_Bu2Dst0h_D0pi0_WN()),
          fracPdfBu_Bu2Dst0h_D0pi0_WN));
  RooProdPdf pdf2d_Bu2Dst0h_D0pi0_WN(
      ("pdf2d_Bu2Dst0h_D0pi0_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdfBu_tot_Bu2Dst0h_D0pi0_WN, pdf.pdfDelta_Bu2Dst0h_D0pi0_WN()));
  functions2d.add(pdf2d_Bu2Dst0h_D0pi0_WN);
  RooRealVar N_2d_trueId_Bu2Dst0h_D0pi0_WN(
      ("N_2d_trueId_Bu2Dst0h_D0pi0_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu2Dst0h_D0pi0_WN().getVal() /
          pdf.orEffBu2Dst0h_D0pi0_WN().getVal(),
      0, 1000000);
  yields2d.add(N_2d_trueId_Bu2Dst0h_D0pi0_WN);

  RooRealVar fracPdfBu_misId_Bu2Dst0h_D0pi0_WN(
      ("fracPdfBu_misId_Bu2Dst0h_D0pi0_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu_Bu2Dst0h_D0pi0_WN().getVal() /
          (pdf.N_misId_Bu_Bu2Dst0h_D0pi0_WN().getVal() +
           pdf.N_misId_BuPartial_Bu2Dst0h_D0pi0_WN().getVal()));
  RooAddPdf pdfBu_tot_misId_Bu2Dst0h_D0pi0_WN(
      ("pdfBu_tot_misId_Bu2Dst0h_D0pi0_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet((pdf.pdfBu_misId_Bu2Dst0h_D0pi0_WN(),
                 pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN()),
                fracPdfBu_misId_Bu2Dst0h_D0pi0_WN));
  RooProdPdf pdf2d_misId_Bu2Dst0h_D0pi0_WN(
      ("pdf2d_misId_Bu2Dst0h_D0pi0_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdfBu_tot_misId_Bu2Dst0h_D0pi0_WN,
                pdf.pdfDelta_misId_Bu2Dst0h_D0pi0_WN()));
  functions2d.add(pdf2d_misId_Bu2Dst0h_D0pi0_WN);
  RooRealVar N_2d_misId_Bu2Dst0h_D0pi0_WN(
      ("N_2d_misId_Bu2Dst0h_D0pi0_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu2Dst0h_D0pi0_WN().getVal() /
          pdf.orEffMisId_Bu2Dst0h_D0pi0_WN().getVal(),
      0, 1000000);
  yields2d.add(N_2d_misId_Bu2Dst0h_D0pi0_WN);

  RooRealVar *fracPdfBu_Bu2Dst0h_D0pi0_WN_D02pik = nullptr;
  RooAddPdf *pdfBu_tot_Bu2Dst0h_D0pi0_WN_D02pik = nullptr;
  RooProdPdf *pdf2d_Bu2Dst0h_D0pi0_WN_D02pik = nullptr;
  RooRealVar *N_2d_trueId_Bu2Dst0h_D0pi0_WN_D02pik = nullptr;
  if (daughters == Daughters::pik) {
    fracPdfBu_Bu2Dst0h_D0pi0_WN_D02pik = new RooRealVar(
        ("fracPdfBu_Bu2Dst0h_D0pi0_WN_D02pik" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik().getVal() /
            (pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik().getVal() +
             pdf.N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik().getVal()));
    pdfBu_tot_Bu2Dst0h_D0pi0_WN_D02pik =
        new RooAddPdf(("pdfBu_tot_Bu2Dst0h_D0pi0_WN_D02pik" +
                       ComposeName(id, neutral, bachelor, daughters, charge))
                          .c_str(),
                      "",
                      RooArgSet((pdf.pdfBu_Bu2Dst0h_D0pi0_WN_D02pik(),
                                 pdf.pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik()),
                                *fracPdfBu_Bu2Dst0h_D0pi0_WN_D02pik));
    pdf2d_Bu2Dst0h_D0pi0_WN_D02pik =
        new RooProdPdf(("pdf2d_Bu2Dst0h_D0pi0_WN_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(*pdfBu_tot_Bu2Dst0h_D0pi0_WN_D02pik,
                                 pdf.pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik()));
    functions2d.add(*pdf2d_Bu2Dst0h_D0pi0_WN_D02pik);
    N_2d_trueId_Bu2Dst0h_D0pi0_WN_D02pik =
        new RooRealVar(("N_2d_trueId_Bu2Dst0h_D0pi0_WN_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_trueId_Bu2Dst0h_D0pi0_WN_D02pik().getVal() /
                           pdf.orEffBu2Dst0h_D0pi0_WN().getVal(),
                       0, 1000000);
    yields2d.add(*N_2d_trueId_Bu2Dst0h_D0pi0_WN_D02pik);
  }

  RooRealVar fracPdfBu_Bd2Dsth(
      ("fracPdfBu_Bd2Dsth" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bd2Dsth().getVal() /
          (pdf.N_trueId_Bu_Bd2Dsth().getVal() +
           pdf.N_trueId_BuPartial_Bd2Dsth().getVal()));
  RooAddPdf pdfBu_tot_Bd2Dsth(
      ("pdfBu_tot_Bd2Dsth" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet((pdf.pdfBu_Bd2Dsth(), pdf.pdfBuPartial_Bd2Dsth()),
                fracPdfBu_Bd2Dsth));
  RooProdPdf pdf2d_Bd2Dsth(
      ("pdf2d_Bd2Dsth_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdfBu_tot_Bd2Dsth, pdf.pdfDelta_Bd2Dsth()));
  functions2d.add(pdf2d_Bd2Dsth);
  RooRealVar N_2d_trueId_Bd2Dsth(
      ("N_2d_trueId_Bd2Dsth_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", pdf.N_trueId_Bd2Dsth().getVal() / pdf.orEffBd2Dsth().getVal(), 0,
      1000000);
  yields2d.add(N_2d_trueId_Bd2Dsth);

  RooRealVar fracPdfBu_Bu2D0hst(
      ("fracPdfBu_Bu2D0hst" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2D0hst().getVal() /
          (pdf.N_trueId_Bu_Bu2D0hst().getVal() +
           pdf.N_trueId_BuPartial_Bu2D0hst().getVal()));
  RooAddPdf pdfBu_tot_Bu2D0hst(
      ("pdfBu_tot_Bu2D0hst" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet((pdf.pdfBu_Bu2D0hst(), pdf.pdfBuPartial_Bu2D0hst()),
                fracPdfBu_Bu2D0hst));
  RooProdPdf pdf2d_Bu2D0hst(
      ("pdf2d_Bu2D0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdfBu_tot_Bu2D0hst, pdf.pdfDelta_Bu2D0hst()));
  functions2d.add(pdf2d_Bu2D0hst);
  RooRealVar N_2d_trueId_Bu2D0hst(
      ("N_2d_trueId_Bu2D0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", pdf.N_trueId_Bu2D0hst().getVal() / pdf.orEffBu2D0hst().getVal(), 0,
      1000000);
  yields2d.add(N_2d_trueId_Bu2D0hst);

  RooRealVar fracPdfBu_Bu2Dst0hst(
      ("fracPdfBu_Bu2Dst0hst" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2Dst0hst().getVal() /
          (pdf.N_trueId_Bu_Bu2Dst0hst().getVal() +
           pdf.N_trueId_BuPartial_Bu2Dst0hst().getVal()));
  RooAddPdf pdfBu_tot_Bu2Dst0hst(
      ("pdfBu_tot_Bu2Dst0hst" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet((pdf.pdfBu_Bu2Dst0hst(), pdf.pdfBuPartial_Bu2Dst0hst()),
                fracPdfBu_Bu2Dst0hst));
  RooProdPdf pdf2d_Bu2Dst0hst(
      ("pdf2d_Bu2Dst0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdfBu_tot_Bu2Dst0hst, pdf.pdfDelta_Bu2Dst0hst()));
  functions2d.add(pdf2d_Bu2Dst0hst);
  RooRealVar N_2d_trueId_Bu2Dst0hst(
      ("N_2d_trueId_Bu2Dst0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", pdf.N_trueId_Bu2Dst0hst().getVal() / pdf.orEffBu2Dst0hst().getVal(),
      0, 1000000);
  yields2d.add(N_2d_trueId_Bu2Dst0hst);

  RooRealVar *fracPdfBu_Lb2Omegach_Lcpi0 = nullptr;
  RooAddPdf *pdfBu_tot_Lb2Omegach_Lcpi0 = nullptr;
  RooProdPdf *pdf2d_Lb2Omegach_Lcpi0 = nullptr;
  RooRealVar *N_2d_trueId_Lb2Omegach_Lcpi0 = nullptr;
  if (daughters == Daughters::kk) {
    fracPdfBu_Lb2Omegach_Lcpi0 = new RooRealVar(
        ("fracPdfBu_Lb2Omegach_Lcpi0" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        pdf.N_trueId_Bu_Lb2Omegach_Lcpi0().getVal() /
            (pdf.N_trueId_Bu_Lb2Omegach_Lcpi0().getVal() +
             pdf.N_trueId_BuPartial_Lb2Omegach_Lcpi0().getVal()));
    pdfBu_tot_Lb2Omegach_Lcpi0 = new RooAddPdf(
        ("pdfBu_tot_Lb2Omegach_Lcpi0" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        RooArgSet(
            (pdf.pdfBu_Lb2Omegach_Lcpi0(), pdf.pdfBuPartial_Lb2Omegach_Lcpi0()),
            *fracPdfBu_Lb2Omegach_Lcpi0));
    pdf2d_Lb2Omegach_Lcpi0 =
        new RooProdPdf(("pdf2d_Lb2Omegach_Lcpi0_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(*pdfBu_tot_Lb2Omegach_Lcpi0,
                                 pdf.pdfDelta_Lb2Omegach_Lcpi0()));
    functions2d.add(*pdf2d_Lb2Omegach_Lcpi0);
    N_2d_trueId_Lb2Omegach_Lcpi0 =
        new RooRealVar(("N_2d_trueId_Lb2Omegach_Lcpi0_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_trueId_Lb2Omegach_Lcpi0().getVal() /
                           pdf.orEffLb2Omegach_Lcpi0().getVal(),
                       0, 1000000);
    yields2d.add(*N_2d_trueId_Lb2Omegach_Lcpi0);
  }

  RooAddPdf addPdf2d(
      ("addPdf2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", functions2d, yields2d);
  
  double N_2d = 0.;
  CalculateNEvtsToGenerate(yields2d, N_2d);
  std::cout << N_2d << "\n";
  // N_2d = mapDataLabelData[ComposeDataLabelName(neutral, bachelor,
  // daughters, charge)]
  //     ->numEntries();
  std::cout << "Generating toy dataset..." << std::endl;
  RooDataSet *genData = addPdf2d.generate(
      RooArgSet(config.buDeltaMass(), config.deltaMass()), N_2d);
  genData->SetName(
      ("gen_" + ComposeName(id, neutral, bachelor, daughters, charge)).c_str());
  std::cout << "Generated!" << std::endl;

  PrintEvents(genData, mapDataLabelData, mapDataLabelToy, config, pdf);
}

void GenerateToyFromPi0Pdf(
    std::map<std::string, RooDataSet *> &mapDataLabelToy,
    std::map<std::string, RooDataSet *> &mapDataLabelData, int id, PdfBase &pdf,
    Configuration &config, std::string const &outputDir) {
  std::cout << "Generating toy from π0 PDF\n";
  Neutral neutral = pdf.neutral();
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Charge charge = pdf.charge();
  RooArgList functions2d;
  RooArgList yields2d;
  RooProdPdf pdf2d_Bu2Dst0h_D0pi0(
      ("pdf2d_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdf.pdfBu_Bu2Dst0h_D0pi0(), pdf.pdfDelta_Bu2Dst0h_D0pi0()));
  functions2d.add(pdf2d_Bu2Dst0h_D0pi0);
  RooRealVar N_2d_trueId_Bu2Dst0h_D0pi0(
      ("N_2d_trueId_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu2Dst0h_D0pi0().getVal() /
          pdf.orEffBu2Dst0h_D0pi0().getVal(),
      0, 1000000);
  std::cout << "1" << std::endl;
  yields2d.add(N_2d_trueId_Bu2Dst0h_D0pi0);
  RooProdPdf pdf2d_misId_Bu2Dst0h_D0pi0(
      ("pdf2d_misId_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_misId_Bu2Dst0h_D0pi0(),
                pdf.pdfDelta_misId_Bu2Dst0h_D0pi0()));
  functions2d.add(pdf2d_misId_Bu2Dst0h_D0pi0);
  RooRealVar N_2d_misId_Bu2Dst0h_D0pi0(
      ("N_2d_misId_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu2Dst0h_D0pi0().getVal() /
          pdf.orEffMisId_Bu2Dst0h_D0pi0().getVal(),
      0, 1000000);
  yields2d.add(N_2d_misId_Bu2Dst0h_D0pi0);
  RooProdPdf *pdf2d_Bu2Dst0h_D0pi0_D02pik = nullptr;
  RooRealVar *N_2d_trueId_Bu2Dst0h_D0pi0_D02pik = nullptr;
  if (daughters == Daughters::pik) {
    pdf2d_Bu2Dst0h_D0pi0_D02pik =
        new RooProdPdf(("pdf2d_Bu2Dst0h_D0pi0_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(pdf.pdfBu_Bu2Dst0h_D0pi0_D02pik(),
                                 pdf.pdfDelta_Bu2Dst0h_D0pi0_D02pik()));
    functions2d.add(*pdf2d_Bu2Dst0h_D0pi0_D02pik);
    N_2d_trueId_Bu2Dst0h_D0pi0_D02pik =
        new RooRealVar(("N_2d_trueId_Bu2Dst0h_D0pi0_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_trueId_Bu2Dst0h_D0pi0_D02pik().getVal() /
                           pdf.orEffBu2Dst0h_D0pi0().getVal(),
                       0, 1000000);
    yields2d.add(*N_2d_trueId_Bu2Dst0h_D0pi0_D02pik);
  }
  RooProdPdf pdf2d_Bu2Dst0h_WN(
      ("pdf2d_Bu2Dst0h_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdf.pdfBu_Bu2Dst0h_WN(), pdf.pdfDelta_Bu2Dst0h_WN()));
  functions2d.add(pdf2d_Bu2Dst0h_WN);
  RooRealVar N_2d_trueId_Bu2Dst0h_WN(
      ("N_2d_trueId_Bu2Dst0h_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", pdf.N_trueId_Bu2Dst0h_WN().getVal() / pdf.orEffBu2Dst0h_WN().getVal(),
      0, 1000000);
  yields2d.add(N_2d_trueId_Bu2Dst0h_WN);
  RooProdPdf pdf2d_misId_Bu2Dst0h_WN(
      ("pdf2d_misId_Bu2Dst0h_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_misId_Bu2Dst0h_WN(),
                pdf.pdfDelta_misId_Bu2Dst0h_WN()));
  functions2d.add(pdf2d_misId_Bu2Dst0h_WN);
  RooRealVar N_2d_misId_Bu2Dst0h_WN(
      ("N_2d_misId_Bu2Dst0h_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu2Dst0h_WN().getVal() /
          pdf.orEffMisId_Bu2Dst0h_WN().getVal(),
      0, 1000000);
  yields2d.add(N_2d_misId_Bu2Dst0h_WN);
  RooProdPdf *pdf2d_Bu2Dst0h_D0pi0_WN_D02pik = nullptr;
  RooRealVar *N_2d_trueId_Bu2Dst0h_D0pi0_WN_D02pik = nullptr;
  if (daughters == Daughters::pik) {
    pdf2d_Bu2Dst0h_D0pi0_WN_D02pik =
        new RooProdPdf(("pdf2d_Bu2Dst0h_D0pi0_WN_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(pdf.pdfBu_Bu2Dst0h_D0pi0_WN_D02pik(),
                                 pdf.pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik()));
    functions2d.add(*pdf2d_Bu2Dst0h_D0pi0_WN_D02pik);
    N_2d_trueId_Bu2Dst0h_D0pi0_WN_D02pik =
        new RooRealVar(("N_2d_trueId_Bu2Dst0h_D0pi0_WN_D02pik_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_trueId_Bu2Dst0h_D0pi0_WN_D02pik().getVal() /
                           pdf.orEffBu2Dst0h_D0pi0_WN().getVal(),
                       0, 1000000);
    yields2d.add(*N_2d_trueId_Bu2Dst0h_D0pi0_WN_D02pik);
  }
  RooProdPdf pdf2d_Bd2Dsth(
      ("pdf2d_Bd2Dsth_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdf.pdfBu_Bd2Dsth(), pdf.pdfDelta_Bd2Dsth()));
  functions2d.add(pdf2d_Bd2Dsth);
  RooRealVar N_2d_trueId_Bd2Dsth(
      ("N_2d_trueId_Bd2Dsth_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", pdf.N_trueId_Bd2Dsth().getVal() / pdf.orEffBd2Dsth().getVal(), 0,
      1000000);
  yields2d.add(N_2d_trueId_Bd2Dsth);
  RooProdPdf pdf2d_Bu2D0hst(
      ("pdf2d_Bu2D0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdf.pdfBu_Bu2D0hst(), pdf.pdfDelta_Bu2D0hst()));
  functions2d.add(pdf2d_Bu2D0hst);
  RooRealVar N_2d_trueId_Bu2D0hst(
      ("N_2d_trueId_Bu2D0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", pdf.N_trueId_Bu2D0hst().getVal() / pdf.orEffBu2D0hst().getVal(), 0,
      1000000);
  yields2d.add(N_2d_trueId_Bu2D0hst);
  RooProdPdf pdf2d_Bu2Dst0hst(
      ("pdf2d_Bu2Dst0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdf.pdfBu_Bu2Dst0hst(), pdf.pdfDelta_Bu2Dst0hst()));
  functions2d.add(pdf2d_Bu2Dst0hst);
  RooRealVar N_2d_trueId_Bu2Dst0hst(
      ("N_2d_trueId_Bu2Dst0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", pdf.N_trueId_Bu2Dst0hst().getVal() / pdf.orEffBu2Dst0hst().getVal(),
      0, 1000000);
  yields2d.add(N_2d_trueId_Bu2Dst0hst);
  RooProdPdf *pdf2d_Lb2Omegach_Lcpi0;
  RooRealVar *N_2d_trueId_Lb2Omegach_Lcpi0 = nullptr;
  if (daughters == Daughters::kk) {
    pdf2d_Lb2Omegach_Lcpi0 =
        new RooProdPdf(("pdf2d_Lb2Omegach_Lcpi0_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(pdf.pdfBu_Lb2Omegach_Lcpi0(),
                                 pdf.pdfDelta_Lb2Omegach_Lcpi0()));
    functions2d.add(*pdf2d_Lb2Omegach_Lcpi0);
    N_2d_trueId_Lb2Omegach_Lcpi0 =
        new RooRealVar(("N_2d_trueId_Lb2Omegach_Lcpi0_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_trueId_Lb2Omegach_Lcpi0().getVal() /
                           pdf.orEffLb2Omegach_Lcpi0().getVal(),
                       0, 1000000);
    yields2d.add(*N_2d_trueId_Lb2Omegach_Lcpi0);
  }
  RooProdPdf *pdf2d_misId_Bd2Dsth;
  RooRealVar *N_2d_misId_Bd2Dsth = nullptr;
  RooProdPdf *pdf2d_misId_Bu2D0hst;
  RooRealVar *N_2d_misId_Bu2D0hst = nullptr;
  RooProdPdf *pdf2d_misId_Bu2Dst0hst;
  RooRealVar *N_2d_misId_Bu2Dst0hst = nullptr;
  RooProdPdf *pdf2d_Bs2Dst0Kpi;
  RooRealVar *N_2d_trueId_Bs2Dst0Kpi = nullptr;
  RooProdPdf *pdf2d_Bs2D0Kpi;
  RooRealVar *N_2d_trueId_Bs2D0Kpi = nullptr;
  if (bachelor == Bachelor::k) {
    pdf2d_misId_Bd2Dsth = new RooProdPdf(
        ("pdf2d_misId_Bd2Dsth_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", RooArgSet(pdf.pdfBu_misId_Bd2Dsth(), pdf.pdfDelta_misId_Bd2Dsth()));
    functions2d.add(*pdf2d_misId_Bd2Dsth);
    N_2d_misId_Bd2Dsth = new RooRealVar(
        ("N_2d_misId_Bd2Dsth_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", pdf.N_misId_Bd2Dsth().getVal() / pdf.orEffMisId_Bd2Dsth().getVal(),
        0, 1000000);
    yields2d.add(*N_2d_misId_Bd2Dsth);
    pdf2d_misId_Bu2D0hst = new RooProdPdf(
        ("pdf2d_misId_Bu2D0hst_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        RooArgSet(pdf.pdfBu_misId_Bu2D0hst(), pdf.pdfDelta_misId_Bu2D0hst()));
    functions2d.add(*pdf2d_misId_Bu2D0hst);
    N_2d_misId_Bu2D0hst = new RooRealVar(
        ("N_2d_misId_Bu2D0hst_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        pdf.N_misId_Bu2D0hst().getVal() / pdf.orEffMisId_Bu2D0hst().getVal(), 0,
        1000000);
    yields2d.add(*N_2d_misId_Bu2D0hst);
    pdf2d_misId_Bu2Dst0hst =
        new RooProdPdf(("pdf2d_misId_Bu2Dst0hst_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(pdf.pdfBu_misId_Bu2Dst0hst(),
                                 pdf.pdfDelta_misId_Bu2Dst0hst()));
    functions2d.add(*pdf2d_misId_Bu2Dst0hst);
    N_2d_misId_Bu2Dst0hst =
        new RooRealVar(("N_2d_misId_Bu2Dst0hst_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_misId_Bu2Dst0hst().getVal() /
                           pdf.orEffMisId_Bu2Dst0hst().getVal(),
                       0, 1000000);
    yields2d.add(*N_2d_misId_Bu2Dst0hst);
    if (daughters != Daughters::kpi && Configuration::Get().runADS() == true) {
      pdf2d_Bs2Dst0Kpi = new RooProdPdf(
          ("pdf2d_Bs2Dst0Kpi_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", RooArgSet(pdf.pdfBu_Bs2Dst0Kpi(), pdf.pdfDelta_Bs2Dst0Kpi()));
      functions2d.add(*pdf2d_Bs2Dst0Kpi);
      N_2d_trueId_Bs2Dst0Kpi = new RooRealVar(
          ("N_2d_trueId_Bs2Dst0Kpi_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "",
          pdf.N_trueId_Bs2Dst0Kpi().getVal() / pdf.orEffBs2Dst0Kpi().getVal(),
          0, 1000000);
      yields2d.add(*N_2d_trueId_Bs2Dst0Kpi);
      pdf2d_Bs2D0Kpi = new RooProdPdf(
          ("pdf2d_Bs2D0Kpi_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", RooArgSet(pdf.pdfBu_Bs2D0Kpi(), pdf.pdfDelta_Bs2D0Kpi()));
      functions2d.add(*pdf2d_Bs2D0Kpi);
      N_2d_trueId_Bs2D0Kpi = new RooRealVar(
          ("N_2d_trueId_Bs2D0Kpi_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", pdf.N_trueId_Bs2D0Kpi().getVal() / pdf.orEffBs2D0Kpi().getVal(),
          0, 1000000);
      yields2d.add(*N_2d_trueId_Bs2D0Kpi);
    }
  }
  RooAddPdf addPdf2d(
      ("addPdf2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", functions2d, yields2d);
  
  double N_2d = 0.;
  CalculateNEvtsToGenerate(yields2d, N_2d);
  std::cout << N_2d << "\n";
  // N_2d = mapDataLabelData[ComposeDataLabelName(neutral, bachelor,
  // daughters, charge)]
  //     ->numEntries();
  std::cout << "Generating toy dataset..." << std::endl;
  RooDataSet *genData = addPdf2d.generate(
      RooArgSet(config.buDeltaMass(), config.deltaMass()), N_2d);
  genData->SetName(
      ("gen_" + ComposeName(id, neutral, bachelor, daughters, charge)).c_str());
  std::cout << "Generated!" << std::endl;

  PrintEvents(genData, mapDataLabelData, mapDataLabelToy, config, pdf);
}

void GenerateToyFromData(
    std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
    std::map<std::string, RooDataSet *> &mapDataLabelToy, int const id,
    PdfBase &pdf, Configuration &config, std::string const &outputDir) {
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(1.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  auto dataHist = std::unique_ptr<RooDataHist>(
      mapDataLabelDataSet[ComposeDataLabelName(neutral, bachelor, daughters,
                                               charge)]
          ->binnedClone(("dataHist_" + ComposeDataLabelName(neutral, bachelor,
                                                            daughters, charge))
                            .c_str(),
                        "dataHist"));
  if (dataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }

  RooHistPdf histPdf(
      ("histPdf_" + ComposeDataLabelName(neutral, bachelor, daughters, charge))
          .c_str(),
      "", config.fittingArgSet(), *dataHist.get(), 2);

  auto toyData = histPdf.generate(
      config.fittingArgSet(),
      mapDataLabelDataSet[ComposeDataLabelName(neutral, bachelor, daughters,
                                               charge)]
          ->numEntries());

  if (mapDataLabelToy.find(ComposeDataLabelName(
          neutral, bachelor, daughters, charge)) == mapDataLabelToy.end()) {
    mapDataLabelToy.insert(std::make_pair(
        ComposeDataLabelName(neutral, bachelor, daughters, charge), toyData));
    std::cout << "Created key-value pair for category " +
                     ComposeDataLabelName(neutral, bachelor, daughters,
                                          charge) +
                     " and corresponding toy\n";
  } else {
    mapDataLabelToy[ComposeDataLabelName(neutral, bachelor, daughters, charge)]
        ->append(*toyData);
    std::cout << "Appended toy to category " +
                     ComposeDataLabelName(neutral, bachelor, daughters,
                                          charge) +
                     "\n";
  }
}
