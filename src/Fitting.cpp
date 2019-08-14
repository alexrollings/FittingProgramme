#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "RooMCStudy.h"
#include "RooNumIntConfig.h"
#include "RooPlot.h"
#include "RooRandom.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TLine.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTree.h"
#include "TTreeReader.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorDaughtersVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "ParseArguments.h"
#include "Pdf.h"

enum class Toys { single, many, none };

// Function to set the style for all THists
void SetStyle() {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.06, "Z");
  gStyle->SetTitleSize(0.03, "XY");
  gStyle->SetLabelSize(0.024, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetLegendTextSize(0.025);
  gStyle->SetTitleOffset(0.9, "X");
  gStyle->SetTitleOffset(1.1, "Y");
  gStyle->SetTitleOffset(0.9, "Z");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.09);
  gStyle->SetPadLeftMargin(0.1);
}

// Function to plot 1D projections - written so that it can be used for both bu
// and delta mass
void PlotComponent(Variable variable, RooRealVar &var, PdfBase &pdf,
                   RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                   Configuration::Categories &categories, TLegend &legend,
                   TLegend &lumiLegend, std::string const &outputDir,
                   bool fitBool, Configuration &config) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  int id = 0;

  // Stops ROOT print INFO messages
  gErrorIgnoreLevel = kWarning;

  std::unique_ptr<RooPlot> frame(var.frame(RooFit::Title(
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str())));
  
  fullDataSet.plotOn(
      frame.get(),
      RooFit::Cut(("fitting==fitting::" +
                   ComposeFittingName(neutral, bachelor, daughters, charge))
                      .c_str()));

  // Everything to be plotted has to be declared outside of a loop, in the scope
  // of the canvas
  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

    pullHist = frame->RooPlot::pullHist();

    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingName(neutral, bachelor, daughters, charge).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.pdf_Bu2Dst0h_Dst02D0pi0().GetName()),
        RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue),
        RooFit::Precision(1e-3), RooFit::NumCPU(8, 2));

    if (variable == Variable::delta) {
      if (neutral == Neutral::gamma) {
        frame->SetXTitle("m[D*^{0}] - m[D^{0}] (MeV/c^{2})");
      } else {
        frame->SetXTitle(
            "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
      }
    } else {
      frame->SetXTitle(
          ("m[D*^{0}" + EnumToLabel(bachelor) + "] - m[D^{*0}] + m[D^{*0}]_{PDG} (MeV/c^{2})").c_str());
    }

    if (fitBool == true) {
      pullFrame->addPlotable(pullHist /* .get() */, "P");
      pullFrame->SetName(("pullFrame_" + EnumToString(variable) + "_" +
                          ComposeName(id, neutral, bachelor, daughters, charge))
                             .c_str());
      pullFrame->SetTitle("");
    }

  // --------------- plot onto canvas ---------------------

  TCanvas canvas(("canvas_" + EnumToString(variable) + "_" +
                  ComposeName(id, neutral, bachelor, daughters, charge))
                     .c_str(),
                 "canvas", 1200, 1000);

  TPad pad1(("pad1_" + EnumToString(variable) + "_" +
             ComposeName(id, neutral, bachelor, daughters, charge))
                .c_str(),
            "pad1", 0.0, 0.14, 1.0, 1.0, kWhite);
  pad1.Draw();

  TPad pad2(("pad2_" + EnumToString(variable) + "_" +
             ComposeName(id, neutral, bachelor, daughters, charge))
                .c_str(),
            "pad2", 0.0, 0.05, 1.0, 0.15, kWhite);
  pad2.Draw();

  TLine zeroLine(var.getMin(), 0, var.getMax(), 0);
  zeroLine.SetLineColor(kRed);
  zeroLine.SetLineStyle(kDashed);

  if (fitBool == true) {
    // Zero line on error plot.
    // .get() gets the raw pointer from underneath the smart pointer
    // FIX THIS
    // TLegend legend = MakeLegend(id, canvas, pad1, pad2, pdf);

    canvas.cd();
    pad2.cd();
    pullFrame->SetYTitle(" ");
    pullFrame->SetXTitle(" ");
    pullFrame->SetLabelSize(0.2, "Y");
    pullFrame->SetLabelFont(132, "XY");
    pullFrame->SetLabelOffset(100, "X");
    pullFrame->SetTitleOffset(100, "X");
    pullFrame->Draw();
    zeroLine.Draw("same");
  }

  canvas.cd();
  pad1.cd();
  frame->Draw();
  lumiLegend.Draw("same");
  // if (fitBool == true) {
  legend.Draw("same");
  // }
  // dataHist->Draw("same");

  canvas.Update();
  canvas.SaveAs((outputDir + "/" +
                 ComposeName(id, neutral, bachelor, daughters, charge) + "_" +
                 EnumToString(variable) + "Mass.pdf")
                    .c_str());
}

// Plot projections
void Plotting1D(int const id, PdfBase &pdf, Configuration &config,
                Configuration::Categories &categories,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                std::string const &outputDir, bool fitBool,
                std::string &labelString, RooFitResult *result) {
  SetStyle();

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  Variable variable = pdf.variable();

  TLegend legend(0.71, 0.53, 0.85, 0.8);
  // ------------- Draw Legends -------------- //
  auto Bu2Dst0h_Dst02D0gammaHist = std::make_unique<TH1D>(
      ("Bu2Dst0h_Dst02D0gammaHist" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "Bu2Dst0h_Dst02D0gammaHist", 1, 0, 1);
  Bu2Dst0h_Dst02D0gammaHist->SetLineColor(kOrange);
  Bu2Dst0h_Dst02D0gammaHist->SetLineStyle(kDashed);
  Bu2Dst0h_Dst02D0gammaHist->SetLineWidth(2);

  auto blankHist = std::make_unique<TH1D>(
      ("blankHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "blankHist", 1, 0, 1);
  blankHist->SetLineColor(kWhite);
  blankHist->SetLineWidth(2);

  std::stringstream Bu2Dst0h_Dst02D0gammaLegend;
  Bu2Dst0h_Dst02D0gammaLegend
      << "B^{" + EnumToLabel(charge) +
             "}#rightarrow#font[132]{[}#font[132]{[}" +
             EnumToLabel(daughters, charge) +
             "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{0}*}" +
             EnumToLabel(bachelor) + "^{" + EnumToLabel(charge) + "}";

  legend.SetLineColor(kWhite);
  legend.AddEntry(Bu2Dst0h_Dst02D0gammaHist.get(),
                  Bu2Dst0h_Dst02D0gammaLegend.str().c_str(), "l");

  TLegend lumiLegend(0.68, 0.80, 0.85, 0.87);
  lumiLegend.SetTextSize(0.03);
  lumiLegend.SetLineColor(kWhite);
  lumiLegend.AddEntry(blankHist.get(), labelString.c_str(), "l");
  // Blank entry to make space for integration symbol
  lumiLegend.AddEntry(blankHist.get(), " ", "l");

  if (labelString == "TOY") {
    lumiLegend.SetTextSize(0.07);
    legend.SetY1(0.55);
    legend.SetY2(0.7);
    lumiLegend.SetY1(0.7);
    lumiLegend.SetY2(0.8);
    if (neutral == Neutral::gamma) {
      legend.SetY2(0.75);
      lumiLegend.SetY1(0.75);
      // legend.SetY1(0.6);
      // legend.SetY2(0.87);
      // lumiLegend.SetX1(0.15);
      // lumiLegend.SetX2(0.25);
      // lumiLegend.SetY1(0.65);
      // lumiLegend.SetY2(0.8);
    }
  }
  // ---- PLOTTING FOR BU MASS COMPONENT ---- //
  PlotComponent(Variable::bu, config.buDeltaMass(), pdf, fullDataSet, simPdf,
                categories, legend, lumiLegend, outputDir, fitBool, config);
  // ---- PLOTTING FOR DELTA MASS COMPONENT ---- //
  PlotComponent(Variable::delta, config.deltaMass(), pdf, fullDataSet, simPdf,
                categories, legend, lumiLegend, outputDir, fitBool, config);
}

void PlotCorrelations(RooFitResult *result, std::string const &outputDir) {
  TCanvas corrCanvas("corrCanvas", "corrCanvas", 1700, 900);
  TH2 *corrHist = result->correlationHist();
  corrHist->SetStats(0);
  corrHist->SetTitle(" ");
  corrCanvas.cd();
  gStyle->SetLabelSize(0.001, "XY");
  gStyle->SetLabelSize(0.015, "Z");
  gPad->SetLeftMargin(0.3);
  gPad->SetRightMargin(0.2);
  gPad->SetBottomMargin(0.21);
  gPad->SetTopMargin(0.05);
  corrHist->Draw("colz");
  corrCanvas.Update();
  corrCanvas.SaveAs((outputDir + "/CorrelationMatrix.pdf").c_str());
}

// Function that returns the simultaneous PDF, the class which collects all the
// individual components. It is that that we do all our fitting with
std::pair<RooSimultaneous *, std::vector<PdfBase *> > MakeSimultaneousPdf(
    int const id, Configuration &config, Configuration::Categories &categories,
    std::vector<Neutral> const &neutralVec,
    std::vector<Daughters> const &daughtersVec,
    std::vector<Charge> const &chargeVec) {
  RooSimultaneous *simPdf = new RooSimultaneous(
      ("simPdf_" + std::to_string(id)).c_str(),
      ("simPdf_" + std::to_string(id)).c_str(), categories.fitting);

  std::vector<PdfBase *> pdfs;
  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &n : neutralVec) {
    switch (n) {
      case Neutral::gamma:
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi,
                               Charge::total>::Get(id));
        pdfs.emplace_back(&Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi,
                               Charge::total>::Get(id));
        break;
      case Neutral::pi0:
        pdfs.emplace_back(&Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi,
                               Charge::total>::Get(id));
        pdfs.emplace_back(
            &Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi, Charge::total>::Get(
                id));
        break;
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(*simPdf);
  }

  auto p = std::make_pair(simPdf, pdfs);
  return p;
}

// Run 1 toy and make 1D and 2D plots
void RunSingleToy(Configuration &config, Configuration::Categories &categories,
                  std::vector<Neutral> const &neutralVec,
                  std::vector<Daughters> const &daughtersVec,
                  std::vector<Charge> const &chargeVec,
                  std::string const &outputDir, bool fitBool) {
  RooRandom::randomGenerator()->SetSeed(30);
  TRandom3 random(0);
  int id = 0;
  auto p = MakeSimultaneousPdf(id, config, categories, neutralVec, daughtersVec,
                               chargeVec);
  auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);
  std::vector<PdfBase *> pdfs = p.second;

  double nEvtsPerToy = simPdf->expectedEvents(categories.fitting);

  auto toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
      RooArgSet(config.buDeltaMass(), config.deltaMass(), categories.fitting),
      nEvtsPerToy));

  auto toyDataHist = std::unique_ptr<RooDataHist>(
      toyDataSet->binnedClone("toyDataHist", "toyDataHist"));

  auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

  // ShiftN_Dst0h(daughtersVec, neutralVec, id);

  auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
      ("simPdfFit_" + std::to_string(id)).c_str(),
      ("simPdfFit_" + std::to_string(id)).c_str(), categories.fitting));

  simPdfToFit = std::unique_ptr<RooSimultaneous>(
      dynamic_cast<RooSimultaneous *>(simPdf->Clone()));

  std::unique_ptr<RooFitResult> result;

  if (fitBool == true) {
    result = std::unique_ptr<RooFitResult>(simPdfToFit->fitTo(
        *toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"), RooFit::Offset(true),
        RooFit::NumCPU(8, 2)));
  }
  // Label plots to indicate Toy
  std::string lumiString = "TOY";
  for (auto &p : pdfs) {
    Plotting1D(id, *p, config, categories, *toyAbsData, *simPdf, outputDir,
               fitBool, lumiString, result.get());
  }
  if (fitBool == true) {
    result->Print("v");
    PlotCorrelations(result.get(), outputDir);
  }
}

// Function we use to do the toy study - run many toys and extract pulls for
// each variable of interest
void RunManyToys(Configuration &config, Configuration::Categories &categories,
                 std::vector<Neutral> const &neutralVec,
                 std::vector<Daughters> const &daughtersVec,
                 std::vector<Charge> const &chargeVec,
                 std::string const &outputDir /* , int nToys */) {
  int nToys = 1;

  for (int id = 0; id < nToys; ++id) {
    // Setting the random seed to 0 is a special case which generates a
    // different seed every time you run. Setting the seed to an integer
    // generates toys in a replicable way, in case you need to debug
    // something.
    RooRandom::randomGenerator()->SetSeed(0);
    TRandom3 random(0);
    double randomTag = random.Rndm();

    TFile outputFile(
        (outputDir + "/ResultFile" + std::to_string(randomTag) + ".root")
            .c_str(),
        "recreate");

    std::cout << "\n\n -------------------------- Running toy #" << id+1
              << " -------------------------- \n\n";

    auto p = MakeSimultaneousPdf(id, config, categories, neutralVec,
                                 daughtersVec, chargeVec);
    auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);

    double nEvtsPerToy = simPdf->expectedEvents(categories.fitting);
    auto toyDataSet = std::unique_ptr<RooDataSet>(simPdf->generate(
        RooArgSet(config.buDeltaMass(), config.deltaMass(), categories.fitting),
        nEvtsPerToy));
    toyDataSet->SetName(("toyDataSet_" + std::to_string(id)).c_str());
    auto toyDataHist = std::unique_ptr<RooDataHist>(
        toyDataSet->binnedClone(("toyDataHist_" + std::to_string(id)).c_str(),
                                ("toyDataHist" + std::to_string(id)).c_str()));
    auto toyAbsData = dynamic_cast<RooAbsData *>(toyDataHist.get());

    // ShiftN_Dst0h(daughtersVec, neutralVec, id);

    auto simPdfToFit = std::unique_ptr<RooSimultaneous>(new RooSimultaneous(
        ("simPdfFit_" + std::to_string(id)).c_str(),
        ("simPdfFit_" + std::to_string(id)).c_str(), categories.fitting));

    simPdfToFit = std::unique_ptr<RooSimultaneous>(
        dynamic_cast<RooSimultaneous *>(simPdf->Clone()));

    auto result = std::shared_ptr<RooFitResult>(
        simPdfToFit->fitTo(*toyAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                           RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                           RooFit::Offset(true), RooFit::NumCPU(8, 2)));
    // save names and predictions of all variables we want to calculate
    // pulls for
    result->Print("v");

    outputFile.cd();
    result->SetName(("Result" + std::to_string(randomTag)).c_str());
    result->Print("v");
    result->Write();
    outputFile.Close();

    std::cout << "Result saved in file " << outputDir << "/ResultFile"
              << std::to_string(randomTag) << ".root\n";
  }
}

// ExtractEnumList() allows user to parse multiple options separated by
// commas.
// Takes full options string as input and outputs a vector containing each
// specified option as an element

template <typename Enum>
std::vector<Enum> ExtractEnumList(std::string const &s, char delim = ',') {
  std::stringstream ss(s);
  std::vector<Enum> values;
  std::string substring;

  while (std::getline(ss, substring, delim)) {
    values.emplace_back(StringToEnum<Enum>(substring));
  }

  return values;
}

// Check file exists
bool fexists(std::string const &filename) {
  std::ifstream infile(filename.c_str());
  return infile.is_open();
}

int main(int argc, char **argv) {
  std::string inputDir, outputDir;
  std::vector<Year> yearVec;
  std::vector<Polarity> polarityVec;
  std::vector<Bachelor> bachelorVec;
  std::vector<Neutral> neutralVec;
  std::vector<Daughters> daughtersVec;
  std::vector<Charge> chargeVec;
  // Still want to load both charges:plus and minus, we just fit with
  // them differently

  Toys toys;
  bool fitBool = true;

  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  {  // calls destructor when object goes out of scope: Will tell you if
    // anything
    // was not used that was given as a command line argument before
    // continuing
    ParseArguments args(argc, argv);  // object instantiated

    std::string yearArg("2011,2012,2015,2016,2017,2018");
    std::string polarityArg("up,down");
    std::string bachelorArg("pi,k");
    std::string neutralArg("gamma,pi0");
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("total");
    std::string toysArg("none");
    int nToys = 1;

    // We always want to simultaneously fir the pi AND k bachelor modes
    // together
    bachelorVec = ExtractEnumList<Bachelor>(bachelorArg);

    if (args("help")) {
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "Type ./Fitting -inputDir=<RooDataSets directory name> \n"
                << "\n";
      std::cout << "-outputDir=<output directory> \n"
                << "\n";
      std::cout << "Followed by the possible options:\n";
      std::cout << "\n";
      std::cout << "    -year=<choice {2011,2012,2015,2016} default: "
                << yearArg << ">\n";
      std::cout << "    -polarity=<choice {up,down} default: " << polarityArg
                << ">\n";
      // std::cout << "    -bachelor choice {k,pi} default: " << bachelorArg
      // <<
      // "\n";
      std::cout << "    -neutral=<choice {pi0,gamma} default: " << neutralArg
                << ">\n";
      std::cout << "    -daughters=<choice {kpi,kk,pipi,pik} default: "
                << daughtersArg << ">\n";
      std::cout << "    -charge=<choice {plus/minus/total} default: " << chargeArg
                << ">\n";
      std::cout << "    -toys=<choice {single, many, none} default: none>"
                << "\n";
      std::cout << "    If toys=many, you can specify -nToys=<#, default = " << nToys << ">"
                << "\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";

      return 1;
    } else {
      if (!args("toys", toysArg)) {
        std::cout << "Using default value -toys=[" << toysArg << "].\n";
        toys = Toys::none;
      } else if (toysArg == "single") {
        toys = Toys::single;
      } else if (toysArg == "many") {
        toys = Toys::many;
      } else if (toysArg == "none") {
        toys = Toys::none;
      } else {
        std::cerr << "Please specify correct toy option: "
                     "-toys=[single,many,none] (optional)\n";
        return 1;
      }

      if (toys == Toys::many) {
        if (!args("nToys", nToys)) {
          std::cout << "Using default and running " << nToys << " toy.\n";
        } else {
          std::cout << "Running " << nToys << " toys.\n";
        }
      }

      if (!args("inputDir", inputDir) && toys == Toys::none) {
        std::cerr << "Data directory must be specified (-inputDir=<path>).\n";
        return 1;
      }
      if (!args("outputDir", outputDir)) {
        std::cout << "Specify output directory (-outputDir=<path>).\n";
        return 1;
      }
      // Year
      // args matches "year" to string given in command line and assigns
      // option
      // parsed to year
      if (!args("year", yearArg)) {
        std::cout << "Using default value -year=[" << yearArg << "].\n";
      }
      try {
        yearVec = ExtractEnumList<Year>(yearArg);
      } catch (std::invalid_argument) {
        std::cerr << "year assignment failed, please specify: "
                     "-year=[2011,2012,2015,2016].\n";
        return 1;
      }

      // Polarity
      if (!args("polarity", polarityArg)) {
        std::cout << "Using default value -polarity=[" << polarityArg << "].\n";
      }
      try {
        polarityVec = ExtractEnumList<Polarity>(polarityArg);
      } catch (std::invalid_argument) {
        std::cerr << "Polarity assignment failed, please specify: "
                     "-polarity=[up,down].\n";
        return 1;
      }

      // Neutral
      if (!args("neutral", neutralArg)) {
        std::cerr << "Using default value -neutral=[" << neutralArg << "]\n";
      }
      try {
        neutralVec = ExtractEnumList<Neutral>(neutralArg);
      } catch (std::invalid_argument) {
        std::cerr << "neutral assignment failed, please specify: "
                     "-neutral=[pi0,gamma].\n";
        return 1;
      }

      if (!args("daughters", daughtersArg)) {
        std::cout << "Using default value -daughters=[" << daughtersArg
                  << "].\n";
      }
      try {
        daughtersVec = ExtractEnumList<Daughters>(daughtersArg);
      } catch (std::invalid_argument) {
        std::cerr << "daughters assignment failed, please specify: "
                     "-daughters=[kpi,kk,pipi,pik].\n";
        return 1;
      }

      if (!args("charge", chargeArg)) {
        std::cout << "Using default value -charge=[" << chargeArg << "].\n";
      }
      try {
        chargeVec = ExtractEnumList<Charge>(chargeArg);
        std::cout << "Using value -charge=[" << chargeArg << "].\n";
      } catch (std::invalid_argument) {
        std::cerr << "charge assignment failed, please specify: "
                     "-charge=[plus,minus] or -charge=[total].\n";
        return 1;
      }
    }
  }

  Configuration &config = Configuration::Get();
  Configuration::Categories &categories = Configuration::Get().categories();

  // Raise lower mass boundary in delta mass for pi0 plots 
  if (neutralVec.size() == 1 && neutralVec[0] == Neutral::pi0) {
    config.deltaMass().setMin(134);
  }

  if (toys == Toys::none) {
    std::map<std::string, RooDataSet *> mapCategoryDataset;

    // Add up lumi in order to convert into string to go on plots
    double lumi = 0;
    double lumiErr = 0;

    // Loop over all options in
    // order to extract correct roodatasets.
    for (auto &y : yearVec) {
      if (y == Year::y2011) {
        lumi += 0.98;
        lumiErr += 0.02;
      } else if (y == Year::y2012) {
        lumi += 1.99;
        lumiErr += 0.02;
      } else if (y == Year::y2015) {
        lumi += 0.28;
        lumiErr += 0.01;
      } else if (y == Year::y2016) {
        lumi += 1.65;
      } else if (y == Year::y2017) {
        lumi += 1.7;
      } else if (y == Year::y2018) {
        lumi += 2.19;
      }
      for (auto &p : polarityVec) {
        for (auto &b : bachelorVec) {
          for (auto &n : neutralVec) {
            for (auto &d : daughtersVec) {
              for (auto &c : chargeVec) {
                std::string dsFile = inputDir + "/" +
                                     ComposeFilename(y, p, b, n, d, c) +
                                     ".root";
                std::cout << "Extracting RooDataSet from file ... " << dsFile
                          << "\n";

                if (!fexists(dsFile)) {
                  std::cerr << dsFile << " does not exist.\n";
                  return 1;
                } else {
                  std::cout << dsFile << " exists.\n";
                  TFile in(dsFile.c_str(), "READ");
                  RooDataSet *inputDataSet;
                  gDirectory->GetObject("inputDataSet", inputDataSet);
                  if (inputDataSet == nullptr) {
                    throw std::runtime_error("Data set does not exist.");
                  } else {
                    std::cout << "inputDataSet extracted... \n";
                    inputDataSet->Print();
                    RooDataSet *reducedInputDataSet_2 = nullptr;
                    if (n == Neutral::pi0) {
                      reducedInputDataSet_2 =
                          dynamic_cast<RooDataSet *>(inputDataSet->reduce(
                              "Bu_Delta_M>5050&&Bu_Delta_M<5800&&Delta_M>50&&Delta_"
                              "M<190&&BDT1>0.05&&BDT2>0.05&&Pi0_M<185&&Pi0_M>"
                              "110"));
                    } else {
                      reducedInputDataSet_2 =
                          dynamic_cast<RooDataSet *>(inputDataSet->reduce(
                              "BDT2>0.05&&BDT2>0.05"));
                    }
                    RooDataSet *reducedInputDataSet_1 = nullptr;
                    if (b == Bachelor::pi) {
                      reducedInputDataSet_1 =
                          dynamic_cast<RooDataSet *>(reducedInputDataSet_2->reduce(
                              "bach_PIDK<12"));
                    } else {
                      reducedInputDataSet_1 =
                          dynamic_cast<RooDataSet *>(reducedInputDataSet_2->reduce(
                              "bach_PIDK>12"));
                    }
                    if (reducedInputDataSet_1 == nullptr) {
                      throw std::runtime_error(
                          "Could not reduce input dataset.");
                    }
                    reducedInputDataSet_1->Print();
                    RooDataSet *reducedInputDataSet = nullptr;
                    if (d == Daughters::kpi || d == Daughters::pik) {
                      reducedInputDataSet = dynamic_cast<RooDataSet *>(
                          reducedInputDataSet_1->reduce(
                              "(abs(h1_D_ID)==211&&h1_D_PIDK<-2)||(abs(h1_D_ID)"
                              "==321&&h1_D_PIDK>2)&&(abs(h2_D_ID)==211&&h2_D_"
                              "PIDK<-2)||(abs(h2_D_ID)==321&&h2_D_PIDK>2)"));
                    } else if (d == Daughters::kk) {
                      reducedInputDataSet =
                          dynamic_cast<RooDataSet *>(reducedInputDataSet_1->reduce(
                              "h1_D_PIDK>2&&h2_D_PIDK>2"));
                    } else {
                      reducedInputDataSet =
                          dynamic_cast<RooDataSet *>(reducedInputDataSet_1->reduce(
                              "h1_D_PIDK<-2&&h2_D_PIDK<-2"));
                    }
                    if (reducedInputDataSet == nullptr) {
                      throw std::runtime_error(
                          "Could not reduce input dataset.");
                    }
                    reducedInputDataSet->Print();
                    // Need to append each year, polarity to dataset at each key
                    // in map, as key labelled by n, b, d, c and must be unique.
                    if (mapCategoryDataset.find(ComposeFittingName(
                            n, b, d, c)) == mapCategoryDataset.end()) {
                      mapCategoryDataset.insert(std::make_pair(
                          ComposeFittingName(n, b, d, c), reducedInputDataSet));
                      std::cout << "Created key-value pair for category " +
                                       ComposeFittingName(n, b, d, c) +
                                       " and "
                                       "dataset " +
                                       EnumToString(y) + "_" + EnumToString(p) +
                                       ".\n";
                    } else {
                      mapCategoryDataset[ComposeFittingName(n, b, d, c)]
                          ->append(*reducedInputDataSet);
                      std::cout << "Appended dataset " + EnumToString(y) +
                                       "_" + EnumToString(p) +
                                       "to category " +
                                       ComposeFittingName(n, b, d, c) + ".\n";
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    int id = 0;

    RooDataSet fullDataSet("fullDataSet", "fullDataSet", config.fittingArgSet(),
                           RooFit::Index(categories.fitting),
                           RooFit::Import(mapCategoryDataset));

    std::cout << "\n\n\n";
    fullDataSet.Print();
    std::cout << "\n\n\n";
    auto fullDataHist = std::unique_ptr<RooDataHist>(
        fullDataSet.binnedClone("fullDataHist", "fullDataHist"));
    if (fullDataHist == nullptr) {
      throw std::runtime_error("Could not extact binned dataset.");
    }
    auto fullAbsData = dynamic_cast<RooAbsData *>(fullDataHist.get());
    if (fullAbsData == nullptr) {
      throw std::runtime_error("Could not cast to RooAbsData.");
    }

    auto p = MakeSimultaneousPdf(id, config, categories, neutralVec,
                                 daughtersVec, chargeVec);
    auto simPdf = std::unique_ptr<RooSimultaneous>(p.first);
    auto pdfs = p.second;

    std::unique_ptr<RooFitResult> result;

    if (fitBool == true) {
      result = std::unique_ptr<RooFitResult>(
          simPdf->fitTo(*fullAbsData, RooFit::Extended(kTRUE), RooFit::Save(),
                        RooFit::Strategy(2), RooFit::Minimizer("Minuit2"),
                        RooFit::Offset(true), RooFit::NumCPU(8, 2)));
    }

    // String for lumi label on 1D projection plots
    std::ostringstream lumiStream, lumiErrStream;
    lumiStream << std::setprecision(2) << lumi;
    lumiErrStream << std::setprecision(2) << lumiErr;
    std::string lumiString = "#int L dt = " + lumiStream.str() + " #pm " +
                             lumiErrStream.str() + " fb^{-1}";
    // Loop over daughters again to plot correct PDFs
    for (auto &p : pdfs) {
      Plotting1D(id, *p, config, categories, fullDataSet, *simPdf,
                 outputDir, fitBool, lumiString, result.get());
    }

    if (fitBool == true) {
      result->Print("v");
      PlotCorrelations(result.get(), outputDir);
    }

  } else {
    if (toys == Toys::single) {
      RunSingleToy(config, categories, neutralVec, daughtersVec, chargeVec,
                   outputDir, fitBool);
    } else if (toys == Toys::many) {
      RunManyToys(config, categories, neutralVec, daughtersVec, chargeVec,
                  outputDir /* , nToys */);
    }
  }

  return 0;
}
