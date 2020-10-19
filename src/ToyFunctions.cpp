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
    // toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
    //     *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
    //     RooFit::Strategy(2), RooFit::Minimizer("Minuit2"), RooFit::Offset(true),
    //     RooFit::NumCPU(config.nCPU())));
    if (config.neutral() == Neutral::pi0) {
      toyFitResult = std::unique_ptr<RooFitResult>(simPdfToFit->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          RooFit::Offset(true), RooFit::NumCPU(config.nCPU()),
          RooFit::ExternalConstraints(
              NeutralVars<Neutral::pi0>::Get(id).constraints_argSet())));
    } else {
      toyFitResult = std::unique_ptr<RooFitResult>(simPdfToFit->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          RooFit::Offset(true), RooFit::NumCPU(config.nCPU()),
          RooFit::ExternalConstraints(
              NeutralVars<Neutral::gamma>::Get(id).constraints_argSet())));
    }
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
    GenerateToyFromPdf(mapDataLabelToy, mapDataLabelData, id, *p, config,
                       outputDir);
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

void GenerateToyFromPdf(std::map<std::string, RooDataSet *> &mapDataLabelToy,
                        std::map<std::string, RooDataSet *> &mapDataLabelData,
                        int id, PdfBase &pdf, Configuration &config,
                        std::string const &outputDir) {
  Neutral neutral = pdf.neutral();
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Charge charge = pdf.charge();
  if (config.neutral() == Neutral::pi0) {
    RooArgList functions2d;
    RooArgList yields2d;
    RooProdPdf pdf2d_Bu2Dst0h_D0pi0(
        ("pdf2d_Bu2Dst0h_D0pi0_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        RooArgSet(pdf.pdfBu_Bu2Dst0h_D0pi0(), pdf.pdfDelta_Bu2Dst0h_D0pi0()));
    functions2d.add(pdf2d_Bu2Dst0h_D0pi0);
    yields2d.add(pdf.N_trueId_Bu2Dst0h_D0pi0());
    RooProdPdf pdf2d_misId_Bu2Dst0h_D0pi0(
        ("pdf2d_misId_Bu2Dst0h_D0pi0_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        RooArgSet(pdf.pdfBu_misId_Bu2Dst0h_D0pi0(),
                  pdf.pdfDelta_misId_Bu2Dst0h_D0pi0()));
    functions2d.add(pdf2d_misId_Bu2Dst0h_D0pi0);
    yields2d.add(pdf.N_misId_Bu2Dst0h_D0pi0());
    // RooProdPdf *pdf2d_Bu2Dst0h_D0pi0_FAVasSUP = nullptr;
    // if (daughters == Daughters::pik) {
    //   pdf2d_Bu2Dst0h_D0pi0_FAVasSUP =
    //       new RooProdPdf(("pdf2d_Bu2Dst0h_D0pi0_FAVasSUP_" +
    //                       ComposeName(id, neutral, bachelor, daughters, charge))
    //                          .c_str(),
    //                      "",
    //                      RooArgSet(pdf.pdfBu_Bu2Dst0h_D0pi0_FAVasSUP(),
    //                                pdf.pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP()));
    //   functions2d.add(*pdf2d_Bu2Dst0h_D0pi0_FAVasSUP);
    //   yields2d.add(pdf.N_trueId_Bu2Dst0h_D0pi0_FAVasSUP());
    // }
    // RooProdPdf pdf2d_MisRec(
    //     ("pdf2d_MisRec_" +
    //      ComposeName(id, neutral, bachelor, daughters, charge))
    //         .c_str(),
    //     "", RooArgSet(pdf.pdfBu_MisRec(), pdf.pdfDelta_MisRec()));
    // functions2d.add(pdf2d_MisRec);
    // yields2d.add(pdf.N_trueId_MisRec());
    // RooProdPdf pdf2d_PartRec(
    //     ("pdf2d_PartRec_" +
    //      ComposeName(id, neutral, bachelor, daughters, charge))
    //         .c_str(),
    //     "", RooArgSet(pdf.pdfBu_PartRec(), pdf.pdfDelta_PartRec()));
    // functions2d.add(pdf2d_PartRec);
    // yields2d.add(pdf.N_trueId_PartRec());
    // RooProdPdf *pdf2d_misId_MisRec;
    // RooProdPdf *pdf2d_misId_PartRec;
    // RooProdPdf *pdf2d_Bs2Dst0Kpi;
    // RooProdPdf *pdf2d_Bs2D0Kpi;
    // if (bachelor == Bachelor::k) {
    //   pdf2d_misId_MisRec = new RooProdPdf(
    //       ("pdf2d_misId_MisRec_" +
    //        ComposeName(id, neutral, bachelor, daughters, charge))
    //           .c_str(),
    //       "", RooArgSet(pdf.pdfBu_misId_MisRec(), pdf.pdfDelta_misId_MisRec()));
    //   functions2d.add(*pdf2d_misId_MisRec);
    //   yields2d.add(pdf.N_misId_MisRec());
    //   pdf2d_misId_PartRec = new RooProdPdf(
    //       ("pdf2d_misId_PartRec_" +
    //        ComposeName(id, neutral, bachelor, daughters, charge))
    //           .c_str(),
    //       "",
    //       RooArgSet(pdf.pdfBu_misId_PartRec(), pdf.pdfDelta_misId_PartRec()));
    //   functions2d.add(*pdf2d_misId_PartRec);
    //   yields2d.add(pdf.N_misId_PartRec());
      // if (daughters != Daughters::kpi &&
      //     Configuration::Get().runADS() == true) {
        // pdf2d_Bs2Dst0Kpi = new RooProdPdf(
        //     ("pdf2d_Bs2Dst0Kpi_" +
        //      ComposeName(id, neutral, bachelor, daughters, charge))
        //         .c_str(),
        //     "", RooArgSet(pdf.pdfBu_Bs2Dst0Kpi(), pdf.pdfDelta_Bs2Dst0Kpi()));
        // functions2d.add(*pdf2d_Bs2Dst0Kpi);
        // yields2d.add(pdf.N_trueId_Bs2Dst0Kpi());
        // pdf2d_Bs2D0Kpi = new RooProdPdf(
        //     ("pdf2d_Bs2D0Kpi_" +
        //      ComposeName(id, neutral, bachelor, daughters, charge))
        //         .c_str(),
        //     "", RooArgSet(pdf.pdfBu_Bs2D0Kpi(), pdf.pdfDelta_Bs2D0Kpi()));
        // functions2d.add(*pdf2d_Bs2D0Kpi);
        // yields2d.add(pdf.N_trueId_Bs2D0Kpi());
    //   }
    // }
    RooAddPdf addPdf2d(
        ("addPdf2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", functions2d, yields2d);
    // Number of events to generate is total of all yields BEFORE
    // splitting
    double nYields = yields2d.getSize();
    double N_2d = 0.;
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
    // N_2d = mapDataLabelData[ComposeDataLabelName(neutral, bachelor, daughters, charge)]
    //     ->numEntries();
    std::cout << "Generating toy dataset..." << std::endl;
    RooDataSet *genData = addPdf2d.generate(
        RooArgSet(config.buDeltaMass(), config.deltaMass()), N_2d);
    genData->SetName(
        ("gen_" + ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str());
    std::cout << "Generated!" << std::endl;
    genData->Print();

    mapDataLabelData[ComposeDataLabelName(neutral, bachelor, daughters, charge)]
        ->Print();

    // double N_2d =
    //     mapDataLabelData[ComposeDataLabelName(neutral, bachelor, daughters,
    //                                           charge)]
    //         // ->reduce(("(Delta_M>" + std::to_string(config.deltaLow()) +
    //         //           "&&Delta_M<" + std::to_string(config.deltaHigh()) +
    //         //           ")||(Bu_Delta_M>" + std::to_string(config.buDeltaLow()) +
    //         //           "&&Bu_Delta_M<" + std::to_string(config.buDeltaHigh()) +
    //         //           ")")
    //         //              .c_str())
    //         ->numEntries();
    // std::cout << "Generating toy dataset with " << N_2d << " events..." << std::endl;
    // Generate 50% more events than needed
    // int nEvtsToGenerate = (int)N_2d * 2;
    // // tmp dataset w/ more events than needed
    // RooDataSet *tmpToy =
    //     addPdf2d.generate(config.fittingArgSet(), nEvtsToGenerate);
    // tmpToy->SetName(
    //     ("tmpToy_" + ComposeName(id, neutral, bachelor, daughters, charge))
    //         .c_str());
    // std::cout << "# of events generated = " << tmpToy->numEntries() << "\n";
    // RooDataSet *boxToy = nullptr;
    // if (tmpToy != nullptr) {
    //   boxToy = dynamic_cast<RooDataSet *>(tmpToy->reduce(
    //       ("(Delta_M>" + std::to_string(config.deltaLow()) + "&&Delta_M<" +
    //        std::to_string(config.deltaHigh()) + ")||(Bu_Delta_M>" +
    //        std::to_string(config.buDeltaLow()) + "&&Bu_Delta_M<" +
    //        std::to_string(config.buDeltaHigh()) + ")")
    //           .c_str()));
    // } else {
    //   throw std::runtime_error("tmpToy is empty.\n");
    // }
    // if (boxToy == nullptr) {
    //   throw std::runtime_error("Could not reduce tmpToy with box cuts.\n");
    // }
    // boxToy->SetName(
    //     ("boxToy_" + ComposeName(id, neutral, bachelor, daughters, charge))
    //         .c_str());
    // std::cout << "# of events left after box cuts = " << boxToy->numEntries()
    //           << "\n";
    // RooDataSet *genData = new RooDataSet(
    //     ("genData_" + ComposeName(id, neutral, bachelor, daughters, charge))
    //         .c_str(),
    //     "", config.fittingArgSet());
    // // Loop ober tmp dataset and sample # of events in data (assumed random
    // // storage of events in DS)
    // for (int i = 0; i < N_2d; ++i) {
    //   if (boxToy->get(i) == nullptr) {
    //     throw std::runtime_error("Could not extract event " +
    //                              std::to_string(i) + " from boxToy.\n");
    //   }
    //   genData->add(*boxToy->get(i));
    // }
    std::cout << "# of events in toy DS = " << genData->numEntries() << "\n";
    std::cout << "Generated!" << std::endl;

    RooAbsData *gds = genData->reduce(("(Delta_M>" + std::to_string(config.deltaLow()) +
                      "&&Delta_M<" + std::to_string(config.deltaHigh()) +
                      ")||(Bu_Delta_M>" + std::to_string(config.buDeltaLow()) +
                      "&&Bu_Delta_M<" + std::to_string(config.buDeltaHigh()) +
                      ")")
                         .c_str());
    std::cout << "nEvts = " << gds->numEntries() << "\n";
    std::cout
        << "nEvts in box = "
        << gds
               ->reduce(("(Delta_M>" + std::to_string(config.deltaLow()) +
                         "&&Delta_M<" + std::to_string(config.deltaHigh()) +
                         ")&&(Bu_Delta_M>" +
                         std::to_string(config.buDeltaLow()) + "&&Bu_Delta_M<" +
                         std::to_string(config.buDeltaHigh()) + ")")
                            .c_str())
               ->numEntries()
        << "\n";

    std::cout << "nEvts in delta = "
              << gds
                     ->reduce(("(Bu_Delta_M>" +
                               std::to_string(config.buDeltaLow()) +
                               "&&Bu_Delta_M<" +
                               std::to_string(config.buDeltaHigh()) + ")")
                                  .c_str())
                     ->numEntries()
              << "\n";

    std::cout << "nEvts in bu = "
              << gds
                     ->reduce(("(Delta_M>" + std::to_string(config.deltaLow()) +
                               "&&Delta_M<" +
                               std::to_string(config.deltaHigh()) + ")")
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
      mapDataLabelToy[ComposeDataLabelName(neutral, bachelor, daughters,
                                           charge)]
          ->append(*genData);
      std::cout << "Appended toy to category " +
                       ComposeDataLabelName(neutral, bachelor, daughters,
                                            charge) +
                       "\n";
    }
  }
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
