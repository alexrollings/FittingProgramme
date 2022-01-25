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
      if (config.neutral() == Neutral::pi0) {
        toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
            *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
            RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
            // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
            RooFit::ExternalConstraints(
                GlobalVars::Get(id).constraints_argSet()),
            RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
            RooFit::Minos(kTRUE)));
      } else {
        toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
            *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
            RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
            // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
            RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
            RooFit::Minos(kTRUE)));
      }

      toyFitResult->SetName("ToyResult");
    }
    if (id == 1) {
      auto pdfs = p.second;
      std::map<Neutral, std::map<Mass, double> > yMaxMap;
        std::map<std::string, Int_t> colorMap = MakeColorMap(config);
        PlotLegend(config, colorMap, outputDir);
      for (auto &p : pdfs) {
        Plotting1D(id, *p, config, *toyAbsData, *simPdfToFit, colorMap, outputDir,
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
    if (config.neutral() == Neutral::pi0) {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          RooFit::ExternalConstraints(GlobalVars::Get(id).constraints_argSet()),
          // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
          RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
          RooFit::Minos(kTRUE)));
    } else {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
          RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
          RooFit::Minos(kTRUE)));
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

  for (auto &p : pdfs) {
    std::cout << p->N_trueId_Bu2Dst0h_D0pi0().GetName() << " = "
              << p->N_trueId_Bu2Dst0h_D0pi0().getVal() << "\n";
    std::cout << p->N_misId_Bu2Dst0h_D0pi0().GetName() << " = "
              << p->N_misId_Bu2Dst0h_D0pi0().getVal() << "\n";
    if (p->neutral() == Neutral::gamma) {
      std::cout << p->N_trueId_Bu2Dst0h_D0gamma().GetName() << " = "
                << p->N_trueId_Bu2Dst0h_D0gamma().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0h_D0gamma().GetName() << " = "
                << p->N_misId_Bu2Dst0h_D0gamma().getVal() << "\n";
      std::cout << p->N_trueId_Bu2Dst0h_D0gamma_WN().GetName() << " = "
                << p->N_trueId_Bu2Dst0h_D0gamma_WN().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0h_D0gamma_WN().GetName() << " = "
                << p->N_misId_Bu2Dst0h_D0gamma_WN().getVal() << "\n";
      std::cout << p->N_trueId_Bu2Dst0h_D0pi0_WN().GetName() << " = "
                << p->N_trueId_Bu2Dst0h_D0pi0_WN().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0h_D0pi0_WN().GetName() << " = "
                << p->N_misId_Bu2Dst0h_D0pi0_WN().getVal() << "\n";
    } else {
      std::cout << p->N_trueId_Bu2Dst0h_WN().GetName() << " = "
                << p->N_trueId_Bu2Dst0h_WN().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0h_WN().GetName() << " = "
                << p->N_misId_Bu2Dst0h_WN().getVal() << "\n";
    }
    std::cout << p->N_trueId_Bd2Dsth().GetName() << " = "
              << p->N_trueId_Bd2Dsth().getVal() << "\n";
    std::cout << p->N_trueId_Bu2D0hst().GetName() << " = "
              << p->N_trueId_Bu2D0hst().getVal() << "\n";
    std::cout << p->N_trueId_Bu2Dst0hst().GetName() << " = "
              << p->N_trueId_Bu2Dst0hst().getVal() << "\n";
    if (p->bachelor() == Bachelor::k) {
      std::cout << p->N_misId_Bd2Dsth().GetName() << " = "
                << p->N_misId_Bd2Dsth().getVal() << "\n";
      std::cout << p->N_misId_Bu2D0hst().GetName() << " = "
                << p->N_misId_Bu2D0hst().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0hst().GetName() << " = "
                << p->N_misId_Bu2Dst0hst().getVal() << "\n";
    }
  }

  auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
      ("simPdfFit_" + std::to_string(id)).c_str(),
      ("simPdfFit_" + std::to_string(id)).c_str(), config.fitting));

  auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
  simPdfToFit = std::unique_ptr<RooSimultaneous>(p.first);

  std::shared_ptr<RooFitResult> toyFitResult;
  if (config.noFit() == false) {
    if (config.neutral() == Neutral::pi0) {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
          RooFit::ExternalConstraints(GlobalVars::Get(id).constraints_argSet()),
          RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
          RooFit::Minos(kTRUE)));
    } else {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdfToFit->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
          RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
          RooFit::Minos(kTRUE)));
    }
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
  auto toyPdfs = p.second;
  for (auto &p : toyPdfs) {
    std::cout << p->N_trueId_Bu2Dst0h_D0pi0().GetName() << " = "
              << p->N_trueId_Bu2Dst0h_D0pi0().getVal() << "\n";
    std::cout << p->N_misId_Bu2Dst0h_D0pi0().GetName() << " = "
              << p->N_misId_Bu2Dst0h_D0pi0().getVal() << "\n";
    if (p->neutral() == Neutral::gamma) {
      std::cout << p->N_trueId_Bu2Dst0h_D0gamma().GetName() << " = "
                << p->N_trueId_Bu2Dst0h_D0gamma().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0h_D0gamma().GetName() << " = "
                << p->N_misId_Bu2Dst0h_D0gamma().getVal() << "\n";
      std::cout << p->N_trueId_Bu2Dst0h_D0gamma_WN().GetName() << " = "
                << p->N_trueId_Bu2Dst0h_D0gamma_WN().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0h_D0gamma_WN().GetName() << " = "
                << p->N_misId_Bu2Dst0h_D0gamma_WN().getVal() << "\n";
      std::cout << p->N_trueId_Bu2Dst0h_D0pi0_WN().GetName() << " = "
                << p->N_trueId_Bu2Dst0h_D0pi0_WN().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0h_D0pi0_WN().GetName() << " = "
                << p->N_misId_Bu2Dst0h_D0pi0_WN().getVal() << "\n";
    } else {
      std::cout << p->N_trueId_Bu2Dst0h_WN().GetName() << " = "
                << p->N_trueId_Bu2Dst0h_WN().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0h_WN().GetName() << " = "
                << p->N_misId_Bu2Dst0h_WN().getVal() << "\n";
    }
    std::cout << p->N_trueId_Bd2Dsth().GetName() << " = "
              << p->N_trueId_Bd2Dsth().getVal() << "\n";
    std::cout << p->N_trueId_Bu2D0hst().GetName() << " = "
              << p->N_trueId_Bu2D0hst().getVal() << "\n";
    std::cout << p->N_trueId_Bu2Dst0hst().GetName() << " = "
              << p->N_trueId_Bu2Dst0hst().getVal() << "\n";
    if (p->bachelor() == Bachelor::k) {
      std::cout << p->N_misId_Bd2Dsth().GetName() << " = "
                << p->N_misId_Bd2Dsth().getVal() << "\n";
      std::cout << p->N_misId_Bu2D0hst().GetName() << " = "
                << p->N_misId_Bu2D0hst().getVal() << "\n";
      std::cout << p->N_misId_Bu2Dst0hst().GetName() << " = "
                << p->N_misId_Bu2Dst0hst().getVal() << "\n";
    }
  }
  if (config.noFit() == false) {
    // to make a unique result each time
    toyFitResult->Print();
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
                   std::string const &outputDir, int id, std::mt19937 &generator) {
  std::cout << "\n\n -------------------------- Running toy #" << id
            << " -------------------------- \n\n";
  auto p = MakeSimultaneousPdf(id, config, daughtersVec, chargeVec);
  auto pdfs = p.second;

  std::map<std::string, RooDataSet *> mapDataLabelToy;

  for (auto &p : pdfs) {
    // GenerateToyFromData(mapDataLabelDataSet, mapDataLabelToy, id, *p, config);
    BootstrapData(mapDataLabelDataSet, mapDataLabelToy, id, *p, config, generator);
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
    if (config.neutral() == Neutral::pi0) {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdf->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
          RooFit::ExternalConstraints(GlobalVars::Get(id).constraints_argSet()),
          RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
          RooFit::Minos(kTRUE)));
    } else {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdf->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
          RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
          RooFit::Minos(kTRUE)));
    }
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
  //   std::map<std::string, Int_t> colorMap = MakeColorMap(config);
  //   for (auto &p : pdfs) {
  //     Plotting1D(id, *p, config, *toyAbsData, *simPdf, colorMap, outputDir,
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

void RunToys1DData(TFile &outputFile,
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

  auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);

  std::map<std::string, RooDataSet *> mapFittingToy;
  for (auto &p : pdfs) {
    Generate1DToyFromData(mapDataLabelDataSet, mapFittingToy, id, *p, config);
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
    if (config.neutral() == Neutral::pi0) {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdf->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
          RooFit::ExternalConstraints(GlobalVars::Get(id).constraints_argSet()),
          RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
          RooFit::Minos(kTRUE)));
    } else {
      toyFitResult = std::shared_ptr<RooFitResult>(simPdf->fitTo(
          *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
          RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
          // RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU())));
          RooFit::Offset(kTRUE), RooFit::NumCPU(config.nCPU()),
          RooFit::Minos(kTRUE)));
    }
    // toyFitResult->SetName(("ToyResult_" + std::to_string(id)).c_str());
    toyFitResult->SetName("ToyResult");
  }

  std::cout << "\n\n\n";
  toyDataSet.Print();
  std::cout << "\n\n\n";

  if (id == 1) {
    std::map<Neutral, std::map<Mass, double> > yMaxMap;
    std::map<std::string, Int_t> colorMap = MakeColorMap(config);
    for (auto &p : pdfs) {
      Plotting1D(id, *p, config, *toyAbsData, *simPdf, colorMap, outputDir,
                 toyFitResult.get(), yMaxMap);
    }
    if (config.noFit() == false) {
      PlotCorrelations(toyFitResult.get(), outputDir, config);
    }
  }
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

}

void PlottingGeneratedToy(Configuration &config, RooDataSet &toyDS, RooDataSet &dataDS,
                RooAddPdf &addPdf, PdfBase &pdf, std::string const &outputDir,
                int id) {
  Neutral neutral = pdf.neutral();
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Charge charge = pdf.charge();
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  auto toyHist = std::unique_ptr<RooDataHist>(toyDS.binnedClone(
      ("toyDataHist_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "toyDataHist"));

  auto toyHist1d = toyHist->createHistogram(
      ("toyHist2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buDeltaMass(), RooFit::Binning(config.buDeltaMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
  if (toyHist1d == nullptr) {
    throw std::runtime_error("\n1D hist of toy returns nullptr\n");
  }
  auto toyHist2d = std::unique_ptr<TH2>(dynamic_cast<TH2F *>(toyHist1d));
  if (toyHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of toy returns nullptr\n");
  }
  toyHist2d->SetTitle("");

  // 2D data plot
  TCanvas canvasToy(
      ("canvasToy_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  toyHist2d->SetStats(0);
  toyHist2d->Draw("colz");
  canvasToy.Update();
  canvasToy.SaveAs((outputDir + "/2d_plots/2dToy_" +
                    ComposeName(id, neutral, bachelor, daughters, charge) +
                    ".pdf")
                       .c_str());

  auto dataHist = std::unique_ptr<RooDataHist>(dataDS.binnedClone(
      ("dataDataHist_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "dataDataHist"));

  auto dataHist1d = dataHist->createHistogram(
      ("dataHist2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buDeltaMass(), RooFit::Binning(config.buDeltaMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
  if (dataHist1d == nullptr) {
    throw std::runtime_error("\n1D hist of data returns nullptr\n");
  }
  auto dataHist2d =
      std::unique_ptr<TH2>(dynamic_cast<TH2F *>(dataHist1d));
  if (dataHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of data returns nullptr\n");
  }
  dataHist2d->SetTitle("");

  // 2D data plot
  TCanvas canvasData(
      ("canvasData_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  dataHist2d->SetStats(0);
  // dataHist2d->SetTitle(
  //     "B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
  //     "pi^{#mp}#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}#pi^{#pm}");
  dataHist2d->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs((outputDir + "/2d_plots/2dData_" +
                     ComposeName(id, neutral, bachelor, daughters, charge) +
                     ".pdf")
                        .c_str());

  auto modelHist1d = addPdf.createHistogram(
      ("modelHist2d_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buDeltaMass(), RooFit::Binning(config.buDeltaMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
  if (modelHist1d == nullptr) {
    throw std::runtime_error("\n1D hist of pdf returns nullptr\n");
  }
  auto modelHist2d =
      std::unique_ptr<TH2>(dynamic_cast<TH2F *>(modelHist1d /* .get() */));
  if (modelHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
  }
  modelHist2d->SetTitle("");

  // Make 2D plot of toy
  // Plot ONLY one component of the toy
  modelHist2d->Scale(toyHist2d->Integral() / modelHist2d->Integral());
  TCanvas canvasModel(
      ("canvasModel_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  modelHist2d->SetStats(0);
  // modelHist2d->SetTitle(
  //     "B^{#pm}#rightarrow#font[132]{[}#font[132]{[}K^{#pm}#"
  //     "pi^{#mp}#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}#pi^{#pm}");
  modelHist2d->Draw("colz");
  modelHist2d->GetZaxis()->SetRangeUser(-0.00001, modelHist2d->GetMaximum());
  canvasModel.Update();
  canvasModel.SaveAs((outputDir + "/2d_plots/2dPdf_" +
                      ComposeName(id, neutral, bachelor, daughters, charge) +
                      ".pdf")
                         .c_str());

  gStyle->SetTitleOffset(1.2, "Z");
  // Make a histogram with the Poisson stats in each data bin
  auto errHist2d = std::unique_ptr<TH2F>(
      new TH2F("errHist2d", "", config.buDeltaMass().getBins(),
               config.buDeltaMass().getMin(), config.buDeltaMass().getMax(),
               config.deltaMass().getBins(), config.deltaMass().getMin(),
               config.deltaMass().getMax()));
  for (int i = 0;
       i < config.buDeltaMass().getBins() * config.deltaMass().getBins(); i++) {
    float n_bin = toyHist2d->GetBinContent(i);
    float err = sqrt(n_bin);
    errHist2d->SetBinContent(i, err);
  }

  // 2D residuals plot (toy - data)/err
  TCanvas canvasResData(
      ("canvasResData" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  canvasResData.cd();
  // auto resHist2d_temp = std::unique_ptr<TObject>(toyHist2d->Clone());
  auto resDataHist2dToy_temp = toyHist2d->Clone();
  if (resDataHist2dToy_temp == nullptr) {
    throw std::runtime_error("\nCould not clone toyHist2d.\n");
  }
  auto resDataHist2dToy = std::unique_ptr<TH2F>(
      dynamic_cast<TH2F *>(resDataHist2dToy_temp /* .get() */));
  if (resDataHist2dToy == nullptr) {
    throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
  }
  resDataHist2dToy->Add(dataHist2d.get(), -1);
  resDataHist2dToy->Divide(errHist2d.get());
  canvasResData.cd();
  resDataHist2dToy->GetZaxis()->SetTitle("Resdual");
  resDataHist2dToy->GetZaxis()->SetRangeUser(-6.0, 6.0);
  resDataHist2dToy->SetStats(0);
  resDataHist2dToy->Draw("colz");
  canvasResData.Update();
  canvasResData.SaveAs((outputDir + "/2d_plots/2dResToyData_" +
                        ComposeName(id, neutral, bachelor, daughters, charge) +
                        ".pdf")
                           .c_str());

  // 2D residuals plot (toy - PDF)/err
  TCanvas canvasRes(
      ("canvasRes" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", 1000, 800);
  canvasRes.cd();
  // auto resHist2d_temp = std::unique_ptr<TObject>(toyHist2d->Clone());
  auto resHist2d_temp = toyHist2d->Clone();
  if (resHist2d_temp == nullptr) {
    throw std::runtime_error("\nCould not clone toyHist2d.\n");
  }
  auto resHist2d =
      std::unique_ptr<TH2F>(dynamic_cast<TH2F *>(resHist2d_temp /* .get() */));
  if (resHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of pdf returns nullptr\n");
  }
  resHist2d->Add(modelHist2d.get(), -1);
  resHist2d->Divide(errHist2d.get());
  canvasRes.cd();
  resHist2d->GetZaxis()->SetTitle("Residual");
  resHist2d->GetZaxis()->SetRangeUser(-6.0, 6.0);
  resHist2d->SetStats(0);
  resHist2d->Draw("colz");
  canvasRes.Update();
  canvasRes.SaveAs((outputDir + "/2d_plots/2dResToyPdf_" +
                    ComposeName(id, neutral, bachelor, daughters, charge) +
                    ".pdf")
                       .c_str());
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

  RooRealVar fracPdfBu_Bu2Dst0h_D0gamma(
      ("fracPdfBu_Bu2Dst0h_D0gamma_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2Dst0h_D0gamma().getVal() /
          (pdf.N_trueId_Bu_Bu2Dst0h_D0gamma().getVal() +
           pdf.N_trueId_BuPartial_Bu2Dst0h_D0gamma().getVal()));
  RooAddPdf pdfBu_tot_Bu2Dst0h_D0gamma(
      ("pdfBu_tot_Bu2Dst0h_D0gamma_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_Bu2Dst0h_D0gamma(), pdf.pdfBuPartial_Bu2Dst0h_D0gamma()),
      fracPdfBu_Bu2Dst0h_D0gamma);
  RooProdPdf pdf2d_Bu2Dst0h_D0gamma(
      ("pdf2d_Bu2Dst0h_D0gamma_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", RooArgSet(pdfBu_tot_Bu2Dst0h_D0gamma, pdf.pdfDelta_Bu2Dst0h_D0gamma()));
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
      ("fracPdfBu_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2Dst0h_D0pi0().getVal() /
          (pdf.N_trueId_Bu_Bu2Dst0h_D0pi0().getVal() +
           pdf.N_trueId_BuPartial_Bu2Dst0h_D0pi0().getVal()));
  RooAddPdf pdfBu_tot_Bu2Dst0h_D0pi0(
      ("pdfBu_tot_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_Bu2Dst0h_D0pi0(), pdf.pdfBuPartial_Bu2Dst0h_D0pi0()),
      fracPdfBu_Bu2Dst0h_D0pi0);
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
      ("fracPdfBu_misId_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu_Bu2Dst0h_D0pi0().getVal() /
          (pdf.N_misId_Bu_Bu2Dst0h_D0pi0().getVal() +
           pdf.N_misId_BuPartial_Bu2Dst0h_D0pi0().getVal()));
  RooAddPdf pdfBu_tot_misId_Bu2Dst0h_D0pi0(
      ("pdfBu_tot_misId_Bu2Dst0h_D0pi0_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_misId_Bu2Dst0h_D0pi0(),
                pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0()),
      fracPdfBu_misId_Bu2Dst0h_D0pi0);
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
        ("fracPdfBu_Bu2Dst0h_D0pi0_D02pik_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik().getVal() /
            (pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_D02pik().getVal() +
             pdf.N_trueId_BuPartial_Bu2Dst0h_D0pi0_D02pik().getVal()));
    pdfBu_tot_Bu2Dst0h_D0pi0_D02pik =
        new RooAddPdf(("pdfBu_tot_Bu2Dst0h_D0pi0_D02pik_" +
                       ComposeName(id, neutral, bachelor, daughters, charge))
                          .c_str(),
                      "",
                      RooArgSet(pdf.pdfBu_Bu2Dst0h_D0pi0_D02pik(),
                                pdf.pdfBuPartial_Bu2Dst0h_D0pi0_D02pik()),
                      *fracPdfBu_Bu2Dst0h_D0pi0_D02pik);
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
      ("fracPdfBu_Bu2Dst0h_D0gamma_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2Dst0h_D0gamma_WN().getVal() /
          (pdf.N_trueId_Bu_Bu2Dst0h_D0gamma_WN().getVal() +
           pdf.N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN().getVal()));
  RooAddPdf pdfBu_tot_Bu2Dst0h_D0gamma_WN(
      ("pdfBu_tot_Bu2Dst0h_D0gamma_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_Bu2Dst0h_D0gamma_WN(),
                pdf.pdfBuPartial_Bu2Dst0h_D0gamma_WN()),
      fracPdfBu_Bu2Dst0h_D0gamma_WN);
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
      ("fracPdfBu_misId_Bu2Dst0h_D0gamma_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu_Bu2Dst0h_D0gamma_WN().getVal() /
          (pdf.N_misId_Bu_Bu2Dst0h_D0gamma_WN().getVal() +
           pdf.N_misId_BuPartial_Bu2Dst0h_D0gamma_WN().getVal()));
  RooAddPdf pdfBu_tot_misId_Bu2Dst0h_D0gamma_WN(
      ("pdfBu_tot_misId_Bu2Dst0h_D0gamma_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_misId_Bu2Dst0h_D0gamma_WN(),
                pdf.pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN()),
      fracPdfBu_misId_Bu2Dst0h_D0gamma_WN);
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
      ("fracPdfBu_Bu2Dst0h_D0pi0_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_WN().getVal() /
          (pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_WN().getVal() +
           pdf.N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN().getVal()));
  RooAddPdf pdfBu_tot_Bu2Dst0h_D0pi0_WN(
      ("pdfBu_tot_Bu2Dst0h_D0pi0_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_Bu2Dst0h_D0pi0_WN(),
                pdf.pdfBuPartial_Bu2Dst0h_D0pi0_WN()),
      fracPdfBu_Bu2Dst0h_D0pi0_WN);
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
      ("fracPdfBu_misId_Bu2Dst0h_D0pi0_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_misId_Bu_Bu2Dst0h_D0pi0_WN().getVal() /
          (pdf.N_misId_Bu_Bu2Dst0h_D0pi0_WN().getVal() +
           pdf.N_misId_BuPartial_Bu2Dst0h_D0pi0_WN().getVal()));
  RooAddPdf pdfBu_tot_misId_Bu2Dst0h_D0pi0_WN(
      ("pdfBu_tot_misId_Bu2Dst0h_D0pi0_WN_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_misId_Bu2Dst0h_D0pi0_WN(),
                 pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN()),
                fracPdfBu_misId_Bu2Dst0h_D0pi0_WN);
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
        ("fracPdfBu_Bu2Dst0h_D0pi0_WN_D02pik_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik().getVal() /
            (pdf.N_trueId_Bu_Bu2Dst0h_D0pi0_WN_D02pik().getVal() +
             pdf.N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN_D02pik().getVal()));
    pdfBu_tot_Bu2Dst0h_D0pi0_WN_D02pik =
        new RooAddPdf(("pdfBu_tot_Bu2Dst0h_D0pi0_WN_D02pik_" +
                       ComposeName(id, neutral, bachelor, daughters, charge))
                          .c_str(),
                      "",
                      RooArgSet(pdf.pdfBu_Bu2Dst0h_D0pi0_WN_D02pik(),
                                pdf.pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik()),
                      *fracPdfBu_Bu2Dst0h_D0pi0_WN_D02pik);
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
      ("fracPdfBu_Bd2Dsth_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bd2Dsth().getVal() /
          (pdf.N_trueId_Bu_Bd2Dsth().getVal() +
           pdf.N_trueId_BuPartial_Bd2Dsth().getVal()));
  RooAddPdf pdfBu_tot_Bd2Dsth(
      ("pdfBu_tot_Bd2Dsth_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_Bd2Dsth(), pdf.pdfBuPartial_Bd2Dsth()),
                fracPdfBu_Bd2Dsth);
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
      ("fracPdfBu_Bu2D0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2D0hst().getVal() /
          (pdf.N_trueId_Bu_Bu2D0hst().getVal() +
           pdf.N_trueId_BuPartial_Bu2D0hst().getVal()));
  RooAddPdf pdfBu_tot_Bu2D0hst(
      ("pdfBu_tot_Bu2D0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_Bu2D0hst(), pdf.pdfBuPartial_Bu2D0hst()),
                fracPdfBu_Bu2D0hst);
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
      ("fracPdfBu_Bu2Dst0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      pdf.N_trueId_Bu_Bu2Dst0hst().getVal() /
          (pdf.N_trueId_Bu_Bu2Dst0hst().getVal() +
           pdf.N_trueId_BuPartial_Bu2Dst0hst().getVal()));
  RooAddPdf pdfBu_tot_Bu2Dst0hst(
      ("pdfBu_tot_Bu2Dst0hst_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "",
      RooArgSet(pdf.pdfBu_Bu2Dst0hst(), pdf.pdfBuPartial_Bu2Dst0hst()),
                fracPdfBu_Bu2Dst0hst);
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
        ("fracPdfBu_Lb2Omegach_Lcpi0_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        pdf.N_trueId_Bu_Lb2Omegach_Lcpi0().getVal() /
            (pdf.N_trueId_Bu_Lb2Omegach_Lcpi0().getVal() +
             pdf.N_trueId_BuPartial_Lb2Omegach_Lcpi0().getVal()));
    pdfBu_tot_Lb2Omegach_Lcpi0 =
        new RooAddPdf(("pdfBu_tot_Lb2Omegach_Lcpi0_" +
                       ComposeName(id, neutral, bachelor, daughters, charge))
                          .c_str(),
                      "",
                      RooArgSet(pdf.pdfBu_Lb2Omegach_Lcpi0(),
                                pdf.pdfBuPartial_Lb2Omegach_Lcpi0()),
                      *fracPdfBu_Lb2Omegach_Lcpi0);
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

  RooRealVar *fracPdfBu_misId_Bd2Dsth = nullptr;
  RooAddPdf *pdfBu_tot_misId_Bd2Dsth = nullptr;
  RooProdPdf *pdf2d_misId_Bd2Dsth = nullptr;
  RooRealVar *N_2d_misId_Bd2Dsth = nullptr;
  RooRealVar *fracPdfBu_misId_Bu2D0hst = nullptr;
  RooAddPdf *pdfBu_tot_misId_Bu2D0hst = nullptr;
  RooProdPdf *pdf2d_misId_Bu2D0hst = nullptr;
  RooRealVar *N_2d_misId_Bu2D0hst = nullptr;
  RooRealVar *fracPdfBu_misId_Bu2Dst0hst = nullptr;
  RooAddPdf *pdfBu_tot_misId_Bu2Dst0hst = nullptr;
  RooProdPdf *pdf2d_misId_Bu2Dst0hst = nullptr;
  RooRealVar *N_2d_misId_Bu2Dst0hst = nullptr;
  RooRealVar *fracPdfBu_Bs2Dst0Kst0 = nullptr;
  RooAddPdf *pdfBu_tot_Bs2Dst0Kst0 = nullptr;
  RooProdPdf *pdf2d_Bs2Dst0Kst0 = nullptr;
  RooRealVar *N_2d_Bs2Dst0Kst0 = nullptr;
  RooRealVar *fracPdfBu_Bs2D0Kst0 = nullptr;
  RooAddPdf *pdfBu_tot_Bs2D0Kst0 = nullptr;
  RooProdPdf *pdf2d_Bs2D0Kst0 = nullptr;
  RooRealVar *N_2d_Bs2D0Kst0 = nullptr;
  if (bachelor == Bachelor::k) {
    fracPdfBu_misId_Bd2Dsth =
        new RooRealVar(("fracPdfBu_misId_Bd2Dsth_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_misId_Bu_Bd2Dsth().getVal() /
                           (pdf.N_misId_Bu_Bd2Dsth().getVal() +
                            pdf.N_misId_BuPartial_Bd2Dsth().getVal()));
    pdfBu_tot_misId_Bd2Dsth = new RooAddPdf(
        ("pdfBu_tot_misId_Bd2Dsth_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        RooArgSet(pdf.pdfBu_misId_Bd2Dsth(), pdf.pdfBuPartial_misId_Bd2Dsth()),
        *fracPdfBu_misId_Bd2Dsth);
    pdf2d_misId_Bd2Dsth = new RooProdPdf(
        ("pdf2d_misId_Bd2Dsth_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", RooArgSet(*pdfBu_tot_misId_Bd2Dsth, pdf.pdfDelta_misId_Bd2Dsth()));
    functions2d.add(*pdf2d_misId_Bd2Dsth);
    N_2d_misId_Bd2Dsth = new RooRealVar(
        ("N_2d_misId_Bd2Dsth_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", pdf.N_misId_Bd2Dsth().getVal() / pdf.orEffBd2Dsth().getVal(), 0,
        1000000);
    yields2d.add(*N_2d_misId_Bd2Dsth);
    fracPdfBu_misId_Bu2D0hst =
        new RooRealVar(("fracPdfBu_misId_Bu2D0hst_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_misId_Bu_Bu2D0hst().getVal() /
                           (pdf.N_misId_Bu_Bu2D0hst().getVal() +
                            pdf.N_misId_BuPartial_Bu2D0hst().getVal()));
    pdfBu_tot_misId_Bu2D0hst =
        new RooAddPdf(("pdfBu_tot_misId_Bu2D0hst_" +
                       ComposeName(id, neutral, bachelor, daughters, charge))
                          .c_str(),
                      "",
                      RooArgSet(pdf.pdfBu_misId_Bu2D0hst(),
                                pdf.pdfBuPartial_misId_Bu2D0hst()),
                      *fracPdfBu_misId_Bu2D0hst);
    pdf2d_misId_Bu2D0hst = new RooProdPdf(
        ("pdf2d_misId_Bu2D0hst_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "",
        RooArgSet(*pdfBu_tot_misId_Bu2D0hst, pdf.pdfDelta_misId_Bu2D0hst()));
    functions2d.add(*pdf2d_misId_Bu2D0hst);
    N_2d_misId_Bu2D0hst = new RooRealVar(
        ("N_2d_misId_Bu2D0hst_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", pdf.N_misId_Bu2D0hst().getVal() / pdf.orEffBu2D0hst().getVal(), 0,
        1000000);
    yields2d.add(*N_2d_misId_Bu2D0hst);
    fracPdfBu_misId_Bu2Dst0hst =
        new RooRealVar(("fracPdfBu_misId_Bu2Dst0hst_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       pdf.N_misId_Bu_Bu2Dst0hst().getVal() /
                           (pdf.N_misId_Bu_Bu2Dst0hst().getVal() +
                            pdf.N_misId_BuPartial_Bu2Dst0hst().getVal()));
    pdfBu_tot_misId_Bu2Dst0hst =
        new RooAddPdf(("pdfBu_tot_misId_Bu2Dst0hst_" +
                       ComposeName(id, neutral, bachelor, daughters, charge))
                          .c_str(),
                      "",
                      RooArgSet(pdf.pdfBu_misId_Bu2Dst0hst(),
                                pdf.pdfBuPartial_misId_Bu2Dst0hst()),
                      *fracPdfBu_misId_Bu2Dst0hst);
    pdf2d_misId_Bu2Dst0hst =
        new RooProdPdf(("pdf2d_misId_Bu2Dst0hst_" +
                        ComposeName(id, neutral, bachelor, daughters, charge))
                           .c_str(),
                       "",
                       RooArgSet(*pdfBu_tot_misId_Bu2Dst0hst,
                                 pdf.pdfDelta_misId_Bu2Dst0hst()));
    functions2d.add(*pdf2d_misId_Bu2Dst0hst);
    N_2d_misId_Bu2Dst0hst = new RooRealVar(
        ("N_2d_misId_Bu2Dst0hst_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", pdf.N_misId_Bu2Dst0hst().getVal() / pdf.orEffBu2Dst0hst().getVal(),
        0, 1000000);
    yields2d.add(*N_2d_misId_Bu2Dst0hst);
    if (daughters == Daughters::pik) {
      fracPdfBu_Bs2Dst0Kst0 =
          new RooRealVar(("fracPdfBu_Bs2Dst0Kst0_" +
                          ComposeName(id, neutral, bachelor, daughters, charge))
                             .c_str(),
                         "",
                         pdf.N_trueId_Bu_Bs2Dst0Kst0().getVal() /
                             (pdf.N_trueId_Bu_Bs2Dst0Kst0().getVal() +
                              pdf.N_trueId_BuPartial_Bs2Dst0Kst0().getVal()));
      pdfBu_tot_Bs2Dst0Kst0 = new RooAddPdf(
          ("pdfBu_tot_Bs2Dst0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", RooArgSet(pdf.pdfBu_Bs2Dst0Kst0(), pdf.pdfBuPartial_Bs2Dst0Kst0()),
          *fracPdfBu_Bs2Dst0Kst0);
      pdf2d_Bs2Dst0Kst0 = new RooProdPdf(
          ("pdf2d_Bs2Dst0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", RooArgSet(*pdfBu_tot_Bs2Dst0Kst0, pdf.pdfDelta_Bs2Dst0Kst0()));
      functions2d.add(*pdf2d_Bs2Dst0Kst0);
      N_2d_Bs2Dst0Kst0 = new RooRealVar(
          ("N_2d_Bs2Dst0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "",
          pdf.N_trueId_Bs2Dst0Kst0().getVal() / pdf.orEffBs2Dst0Kst0().getVal(),
          0, 1000000);
      yields2d.add(*N_2d_Bs2Dst0Kst0);
      fracPdfBu_Bs2D0Kst0 =
          new RooRealVar(("fracPdfBu_Bs2D0Kst0_" +
                          ComposeName(id, neutral, bachelor, daughters, charge))
                             .c_str(),
                         "",
                         pdf.N_trueId_Bu_Bs2D0Kst0().getVal() /
                             (pdf.N_trueId_Bu_Bs2D0Kst0().getVal() +
                              pdf.N_trueId_BuPartial_Bs2D0Kst0().getVal()));
      pdfBu_tot_Bs2D0Kst0 = new RooAddPdf(
          ("pdfBu_tot_Bs2D0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", RooArgSet(pdf.pdfBu_Bs2D0Kst0(), pdf.pdfBuPartial_Bs2D0Kst0()),
          *fracPdfBu_Bs2D0Kst0);
      pdf2d_Bs2D0Kst0 = new RooProdPdf(
          ("pdf2d_Bs2D0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", RooArgSet(*pdfBu_tot_Bs2D0Kst0, pdf.pdfDelta_Bs2D0Kst0()));
      functions2d.add(*pdf2d_Bs2D0Kst0);
      N_2d_Bs2D0Kst0 = new RooRealVar(
          ("N_2d_Bs2D0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", pdf.N_trueId_Bs2D0Kst0().getVal() / pdf.orEffBs2D0Kst0().getVal(),
          0, 1000000);
      yields2d.add(*N_2d_Bs2D0Kst0);
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
  RooProdPdf *pdf2d_Bs2Dst0Kst0;
  RooRealVar *N_2d_trueId_Bs2Dst0Kst0 = nullptr;
  RooProdPdf *pdf2d_Bs2D0Kst0;
  RooRealVar *N_2d_trueId_Bs2D0Kst0 = nullptr;
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
      pdf2d_Bs2Dst0Kst0 = new RooProdPdf(
          ("pdf2d_Bs2Dst0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", RooArgSet(pdf.pdfBu_Bs2Dst0Kst0(), pdf.pdfDelta_Bs2Dst0Kst0()));
      functions2d.add(*pdf2d_Bs2Dst0Kst0);
      N_2d_trueId_Bs2Dst0Kst0 = new RooRealVar(
          ("N_2d_trueId_Bs2Dst0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "",
          pdf.N_trueId_Bs2Dst0Kst0().getVal() / pdf.orEffBs2Dst0Kst0().getVal(),
          0, 1000000);
      yields2d.add(*N_2d_trueId_Bs2Dst0Kst0);
      pdf2d_Bs2D0Kst0 = new RooProdPdf(
          ("pdf2d_Bs2D0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", RooArgSet(pdf.pdfBu_Bs2D0Kst0(), pdf.pdfDelta_Bs2D0Kst0()));
      functions2d.add(*pdf2d_Bs2D0Kst0);
      N_2d_trueId_Bs2D0Kst0 = new RooRealVar(
          ("N_2d_trueId_Bs2D0Kst0_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "", pdf.N_trueId_Bs2D0Kst0().getVal() / pdf.orEffBs2D0Kst0().getVal(),
          0, 1000000);
      yields2d.add(*N_2d_trueId_Bs2D0Kst0);
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

void BootstrapData(
    std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
    std::map<std::string, RooDataSet *> &mapDataLabelToy, int const id,
    PdfBase &pdf, Configuration &config, std::mt19937 &generator) {
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

  auto dataSet = mapDataLabelDataSet[ComposeDataLabelName(neutral, bachelor, daughters,
                                               charge)];
  if (dataSet == nullptr) {
    throw std::runtime_error("DataSet does not exist in mapDataLabelDataSet.");
  }

  RooDataSet *toyData = new RooDataSet(
      ("toyData_" + ComposeDataLabelName(neutral, bachelor, daughters, charge) + "_" +
       std::to_string(id))
          .c_str(),
      ("toyData_" + ComposeDataLabelName(neutral, bachelor, daughters, charge) + "_" +
       std::to_string(id))
          .c_str(),
      config.fittingArgSet());
  Int_t n_entries = dataSet->numEntries();
  std::cout << n_entries << std::endl;
  for (Int_t idx = 0; idx < n_entries; ++idx) {
    std::uniform_int_distribution<Int_t> distr(0, n_entries - 1);
    Int_t event = distr(generator);
    const RooArgSet *eventArgSet = dataSet->get(event);
    if (eventArgSet == nullptr) {
      std::stringstream outStr;
      outStr << "Event " << event
             << " could not be extracted from dataSet.\n";
      throw std::runtime_error(outStr.str());
    }
    toyData->add(*eventArgSet);
  }

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

void GenerateToyFromData(
    std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
    std::map<std::string, RooDataSet *> &mapDataLabelToy, int const id,
    PdfBase &pdf, Configuration &config) {
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

void Generate1DToyFromData(
    std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
    std::map<std::string, RooDataSet *> &mapFittingToy, int const id,
    PdfBase &pdf, Configuration &config) {
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

  RooDataSet *buDeltaDataSet = nullptr;
  buDeltaDataSet = dynamic_cast<RooDataSet *>(
      mapDataLabelDataSet[ComposeDataLabelName(neutral, bachelor, daughters, charge)]->reduce(
          config.buDeltaMass(),
          ("Delta_M>" + std::to_string(config.deltaLow()) + "&&Delta_M<" +
           std::to_string(config.deltaHigh()))
              .c_str()));
  if (buDeltaDataSet == nullptr) {
    throw std::runtime_error("Could not reduce buDelta data.");
  }
  auto buDeltaDataHist =
      std::unique_ptr<RooDataHist>(buDeltaDataSet->binnedClone(
          ("buDeltaDataHist_" +
           ComposeName(id, neutral, bachelor, daughters, charge))
              .c_str(),
          "buDeltaDataHist"));
  if (buDeltaDataHist == nullptr) {
    throw std::runtime_error(
        "Could not extact binned datahist from buDelta data.");
  }
  RooHistPdf buDeltaHistPdf(
      ("buDeltaHistPdf_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "", config.buDeltaMass(), *buDeltaDataHist.get(), 1);
  auto buDeltaToy =
      buDeltaHistPdf.generate(config.buDeltaMass(), buDeltaDataSet->numEntries());
  buDeltaToy->SetName(
      ("buDeltaToy_" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str());
  buDeltaToy->Print();
  if (mapFittingToy.find(ComposeFittingName(Mass::buDelta, neutral, bachelor,
                                            daughters, charge)) ==
      mapFittingToy.end()) {
    mapFittingToy.insert(std::make_pair(
        ComposeFittingName(Mass::buDelta, neutral, bachelor, daughters, charge),
        buDeltaToy));
    std::cout << "Created key-value pair for category " +
                     ComposeFittingName(Mass::buDelta, neutral, bachelor,
                                        daughters, charge) +
                     " and corresponding dataSet\n";
  } else {
    mapFittingToy[ComposeFittingName(Mass::buDelta, neutral, bachelor,
                                     daughters, charge)]
        ->append(*buDeltaToy);
    std::cout << "Appended dataSet to category " +
                     ComposeFittingName(Mass::buDelta, neutral, bachelor,
                                        daughters, charge) +
                     "\n";
  }
  if (config.fitBuPartial() == true) {
    RooDataSet *buDeltaPartialDataSet = nullptr;
    buDeltaPartialDataSet = dynamic_cast<RooDataSet *>(
        mapDataLabelDataSet[ComposeDataLabelName(neutral, bachelor, daughters, charge)]->reduce(
            config.buDeltaMass(),
            ("Delta_M>" + std::to_string(config.deltaPartialLow()) +
             "&&Delta_M<" + std::to_string(config.deltaPartialHigh()))
                .c_str()));
    if (buDeltaPartialDataSet == nullptr) {
      throw std::runtime_error("Could not reduce buDeltaPartial data.");
    }
    auto buDeltaPartialDataHist =
        std::unique_ptr<RooDataHist>(buDeltaPartialDataSet->binnedClone(
            ("buDeltaPartialDataHist_" +
             ComposeName(id, neutral, bachelor, daughters, charge))
                .c_str(),
            "buDeltaPartialDataHist"));
    if (buDeltaPartialDataHist == nullptr) {
      throw std::runtime_error(
          "Could not extact binned datahist from buDeltaPartial data.");
    }
    RooHistPdf buDeltaPartialHistPdf(
        ("buDeltaPartialHistPdf_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", config.buDeltaMass(), *buDeltaPartialDataHist.get(), 1);
    auto buDeltaPartialToy = buDeltaPartialHistPdf.generate(
        config.buDeltaMass(), buDeltaPartialDataSet->numEntries());
    buDeltaPartialToy->SetName(
        ("buDeltaPartialToy_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str());
    if (mapFittingToy.find(ComposeFittingName(Mass::buDeltaPartial, neutral,
                                              bachelor, daughters, charge)) ==
        mapFittingToy.end()) {
      mapFittingToy.insert(
          std::make_pair(ComposeFittingName(Mass::buDeltaPartial, neutral,
                                            bachelor, daughters, charge),
                         buDeltaPartialToy));
      std::cout << "Created key-value pair for category " +
                       ComposeFittingName(Mass::buDeltaPartial, neutral,
                                          bachelor, daughters, charge) +
                       " and corresponding dataSet\n";
    } else {
      mapFittingToy[ComposeFittingName(Mass::buDeltaPartial, neutral, bachelor,
                                       daughters, charge)]
          ->append(*buDeltaPartialToy);
      std::cout << "Appended dataSet to category " +
                       ComposeFittingName(Mass::buDeltaPartial, neutral,
                                          bachelor, daughters, charge) +
                       "\n";
    }
  }
  if (config.fit1D() == false) {
    RooDataSet *deltaDataSet = nullptr;
    deltaDataSet = dynamic_cast<RooDataSet *>(
        mapDataLabelDataSet[ComposeDataLabelName(neutral, bachelor, daughters,
                                                 charge)]
            ->reduce(config.deltaMass(),
                     ("Bu_Delta_M>" + std::to_string(config.buDeltaLow()) +
                      "&&Bu_Delta_M<" + std::to_string(config.buDeltaHigh()))
                         .c_str()));
    if (deltaDataSet == nullptr) {
      throw std::runtime_error("Could not reduce delta data.");
    }
    auto deltaDataHist = std::unique_ptr<RooDataHist>(deltaDataSet->binnedClone(
        ("deltaDataHist_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "deltaDataHist"));
    if (deltaDataHist == nullptr) {
      throw std::runtime_error(
          "Could not extact binned datahist from delta data.");
    }
    RooHistPdf deltaHistPdf(
        ("deltaHistPdf_" +
         ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str(),
        "", config.deltaMass(), *deltaDataHist.get(), 1);
    auto deltaToy =
        deltaHistPdf.generate(config.deltaMass(), deltaDataSet->numEntries());
    deltaToy->SetName(
        ("deltaToy_" + ComposeName(id, neutral, bachelor, daughters, charge))
            .c_str());
    deltaToy->Print();
    if (mapFittingToy.find(ComposeFittingName(Mass::delta, neutral, bachelor,
                                              daughters, charge)) ==
        mapFittingToy.end()) {
      mapFittingToy.insert(std::make_pair(
          ComposeFittingName(Mass::delta, neutral, bachelor, daughters, charge),
          deltaToy));
      std::cout << "Created key-value pair for category " +
                       ComposeFittingName(Mass::delta, neutral, bachelor,
                                          daughters, charge) +
                       " and corresponding dataSet\n";
    } else {
      mapFittingToy[ComposeFittingName(Mass::delta, neutral, bachelor,
                                       daughters, charge)]
          ->append(*deltaToy);
      std::cout << "Appended dataSet to category " +
                       ComposeFittingName(Mass::delta, neutral, bachelor,
                                          daughters, charge) +
                       "\n";
    }
  }
}
