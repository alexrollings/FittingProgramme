#pragma once
#include "Plotting.h"
#include "Fitting.h"

#include <random>

void ToyTestD1D(std::unique_ptr<RooSimultaneous> &simPdf,
                std::unique_ptr<RooFitResult> &dataFitResult,
                Configuration &config,
                std::vector<Daughters> const &daughtersVec,
                std::vector<Charge> const &chargeVec,
                std::string const &outputDir, int nToys);
void RunToysD1DPdf(std::unique_ptr<RooSimultaneous> &simPdf, TFile &outputFile,
                   Configuration &config,
                   std::unique_ptr<RooFitResult> &dataFitResult,
                   std::vector<Daughters> const &daughtersVec,
                   std::vector<Charge> const &chargeVec,
                   std::string const &outputDir, int id);
void GenerateToyFromPi0Pdf(
    std::map<std::string, RooDataSet *> &mapDataLabelToy,
    std::map<std::string, RooDataSet *> &mapDataLabelData, int id, PdfBase &pdf,
    Configuration &config, std::string const &outputDir);
void GenerateToyFromGammaPdf(
    std::map<std::string, RooDataSet *> &mapDataLabelToy,
    std::map<std::string, RooDataSet *> &mapDataLabelData, int id, PdfBase &pdf,
    Configuration &config, std::string const &outputDir);
void RunToys2DPdf(std::vector<PdfBase *> &pdfs,
                  std::map<std::string, RooDataSet *> &mapDataLabelData,
                  std::unique_ptr<RooSimultaneous> &simPdf, TFile &outputFile,
                  std::unique_ptr<RooFitResult> &dataFitResult,
                  Configuration &config, std::string const &outputDir,
                  std::vector<Daughters> const &daughtersVec,
                  std::vector<Charge> const &chargeVec, int id);
void GenerateToyFromData(
    std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
    std::map<std::string, RooDataSet *> &mapDataLabelToy, int const id,
    PdfBase &pdf, Configuration &config);
void RunToys2DData(TFile &outputFile,
                   std::unique_ptr<RooFitResult> &dataFitResult,
                   std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
                   Configuration &config,
                   std::vector<Daughters> const &daughtersVec,
                   std::vector<Charge> const &chargeVec,
                   std::string const &outputDir, int id);
void Generate1DToyFromData(
    std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
    std::map<std::string, RooDataSet *> &mapFittingToy, int const id,
    PdfBase &pdf, Configuration &config);
void RunToys1DData(TFile &outputFile,
                   std::unique_ptr<RooFitResult> &dataFitResult,
                   std::map<std::string, RooDataSet *> &mapDataLabelDataSet,
                   Configuration &config,
                   std::vector<Daughters> const &daughtersVec,
                   std::vector<Charge> const &chargeVec,
                   std::string const &outputDir, int id);
