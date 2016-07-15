#include "RooAbsBinning.h"
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TStyle.h"

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Configuration.h"
#include "ParseArguments.h"
#include "Pdf.h"

// ALWAYS pass values by const reference (if possible)
// It is important to pass the same category object !!!!
void Plotting(Pdf &pdf, std::vector<Charge> chargeVec, Configuration &config,
              Categories &categories, RooDataSet const &fullDataSet,
              RooSimultaneous const &simPdf) {

  // -------------- Set Style Attributes ------------------

  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.08, "Z");
  gStyle->SetTitleSize(0.045, "XY");
  gStyle->SetLabelSize(0.04, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(0.95, "Y");
  gStyle->SetTitleOffset(0.9, "Z");
  // gStyle->SetLegendTextSize(0.08);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.11);
  gStyle->SetPadLeftMargin(0.1);

  // --------------- create frame ---------------------

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();

  std::string chargeLabel = EnumToLabel(chargeVec);
  std::string daughtersLabel = EnumToLabel(daughters, chargeVec);
  std::string bachelorLabel = EnumToLabel(bachelor);
  std::string neutralLabel = EnumToLabel(neutral);
  std::string crossFeedLabel = CrossFeedLabel(neutral);
  std::string hstLabel = HstLabel(bachelor);
  std::string missIdLabel = MissIdLabel(bachelor);

  std::unique_ptr<RooPlot> frame(config.buMass().frame(RooFit::Title(
      ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D}" + neutralLabel +
       "#font[132]{]}_{D^{*}}" + bachelorLabel + "^{" + chargeLabel + "}")
          .c_str())));

  // --------- Create histogram of data to plot on top of fit ----------
  // Need to plot a reduced data set

  // TH1F *dataHist = (TH1F *)fullDataSet.createHistogram(
  //     "dataHist", config.buMass(), RooFit::Binning(152));
  // dataHist->SetMarkerColor(1);
  // dataHist->SetMarkerStyle(20);
  // dataHist->SetMarkerSize(1);

  // --------------- plot data and pdfs onto frame ---------------------

  fullDataSet.plotOn(
      frame.get(),
      RooFit::Cut(("fitting==fitting::" +
                   ComposeFittingCategoryName(neutral, bachelor, daughters))
                      .c_str()));

  // .get() gets the raw pointer from underneath the smart pointer

  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::LineColor(kBlue));
  switch (neutral) {
  case Neutral::pi0:
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.signalPi0()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kBlue));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.nonTMSignalPi0()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kBlack));
    break;
  case Neutral::gamma:
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.signalGamma()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kBlue));
    simPdf.plotOn(
        frame.get(),
        RooFit::Slice(
            categories.fitting,
            ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
        RooFit::ProjWData(categories.fitting, fullDataSet),
        RooFit::Components(pdf.nonTMSignalGamma()), RooFit::LineStyle(kDashed),
        RooFit::LineColor(kBlack));
    break;
  }
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.combinatorialExponential()),
      RooFit::LineStyle(kDashed), RooFit::LineColor(kRed + 2));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.crossFeed()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kRed));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2Dst0Hst_D0pi0()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kGreen));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2Dst0Hst_D0gamma()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kMagenta + 3));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2D0H()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kOrange));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bu2D0Hst()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kTeal));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bd2DstH()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kMagenta));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.bd2D0Hst0()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(kYellow));
  simPdf.plotOn(
      frame.get(),
      RooFit::Slice(
          categories.fitting,
          ComposeFittingCategoryName(neutral, bachelor, daughters).c_str()),
      RooFit::ProjWData(categories.fitting, fullDataSet),
      RooFit::Components(pdf.missId()), RooFit::LineStyle(kDashed),
      RooFit::LineColor(9));

  // ------------- Draw Legend --------------

  TH1D *signalHist = new TH1D(
      ("signalHist" + ComposeFittingCategoryName(neutral, bachelor, daughters))
          .c_str(),
      "signalHist", 0, 0, 0);
  signalHist->SetLineColor(kBlue);
  signalHist->SetLineStyle(kDashed);
  signalHist->SetLineWidth(2);

  TH1D *nonTMSignalHist =
      new TH1D(("nonTMSignalHist" +
                ComposeFittingCategoryName(neutral, bachelor, daughters))
                   .c_str(),
               "nonTMSignalHist", 0, 0, 0);
  nonTMSignalHist->SetLineColor(kBlack);
  nonTMSignalHist->SetLineStyle(kDashed);
  nonTMSignalHist->SetLineWidth(2);

  TH1D *crossFeedHist =
      new TH1D(("crossFeedHist" +
                ComposeFittingCategoryName(neutral, bachelor, daughters))
                   .c_str(),
               "crossFeedHist", 0, 0, 0);
  crossFeedHist->SetLineColor(kRed);
  crossFeedHist->SetLineStyle(kDashed);
  crossFeedHist->SetLineWidth(2);

  TH1D *bu2Dst0Hst_D0pi0Hist =
      new TH1D(("bu2Dst0Hst_D0pi0Hist" +
                ComposeFittingCategoryName(neutral, bachelor, daughters))
                   .c_str(),
               "bu2Dst0Hst_D0pi0Hist", 0, 0, 0);
  bu2Dst0Hst_D0pi0Hist->SetLineColor(kGreen);
  bu2Dst0Hst_D0pi0Hist->SetLineStyle(kDashed);
  bu2Dst0Hst_D0pi0Hist->SetLineWidth(2);

  TH1D *bu2Dst0Hst_D0gammaHist =
      new TH1D(("bu2Dst0Hst_D0gammaHist" +
                ComposeFittingCategoryName(neutral, bachelor, daughters))
                   .c_str(),
               "bu2Dst0Hst_D0gammaHist", 0, 0, 0);
  bu2Dst0Hst_D0gammaHist->SetLineColor(kMagenta + 3);
  bu2Dst0Hst_D0gammaHist->SetLineStyle(kDashed);
  bu2Dst0Hst_D0gammaHist->SetLineWidth(2);

  TH1D *bu2D0HHist = new TH1D(
      ("bu2D0HHist" + ComposeFittingCategoryName(neutral, bachelor, daughters))
          .c_str(),
      "bu2D0HHist", 0, 0, 0);
  bu2D0HHist->SetLineColor(kOrange);
  bu2D0HHist->SetLineStyle(kDashed);
  bu2D0HHist->SetLineWidth(2);

  TH1D *bu2D0HstHist =
      new TH1D(("bu2D0HstHist" +
                ComposeFittingCategoryName(neutral, bachelor, daughters))
                   .c_str(),
               "bu2D0HstHist", 0, 0, 0);
  bu2D0HstHist->SetLineColor(kTeal);
  bu2D0HstHist->SetLineStyle(kDashed);
  bu2D0HstHist->SetLineWidth(2);

  TH1D *bd2DstHHist = new TH1D(
      ("bd2DstHHist" + ComposeFittingCategoryName(neutral, bachelor, daughters))
          .c_str(),
      "bd2DstHHist", 0, 0, 0);
  bd2DstHHist->SetLineColor(kMagenta);
  bd2DstHHist->SetLineStyle(kDashed);
  bd2DstHHist->SetLineWidth(2);

  TH1D *bd2D0Hst0Hist =
      new TH1D(("bd2D0Hst0Hist" +
                ComposeFittingCategoryName(neutral, bachelor, daughters))
                   .c_str(),
               "bd2D0Hst0Hist", 0, 0, 0);
  bd2D0Hst0Hist->SetLineColor(kYellow);
  bd2D0Hst0Hist->SetLineStyle(kDashed);
  bd2D0Hst0Hist->SetLineWidth(2);

  TH1D *combinatorialHist =
      new TH1D(("combinatorialHist" +
                ComposeFittingCategoryName(neutral, bachelor, daughters))
                   .c_str(),
               "combinatorialHist", 0, 0, 0);
  combinatorialHist->SetLineColor(kRed + 2);
  combinatorialHist->SetLineStyle(kDashed);
  combinatorialHist->SetLineWidth(2);

  TH1D *missIdHist = new TH1D(
      ("missIdHist" + ComposeFittingCategoryName(neutral, bachelor, daughters))
          .c_str(),
      "missIdHist", 0, 0, 0);
  missIdHist->SetLineColor(9);
  missIdHist->SetLineStyle(kDashed);
  missIdHist->SetLineWidth(2);

  TLegend *legend = new TLegend(0.65, 0.35, 0.97, 0.90);
  // legend->SetHeader("Physics Bachgrounds");
  legend->AddEntry(signalHist, "Signal", "l");
  legend->AddEntry(nonTMSignalHist, "Non-TM Signal", "l");
  legend->AddEntry(
      crossFeedHist,
      ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D^{0}}" + crossFeedLabel +
       "#font[132]{]}_{D^{0}*}" + bachelorLabel + "^{" + chargeLabel + "}")
          .c_str(),
      "l");
  legend->AddEntry(
      bu2Dst0Hst_D0pi0Hist,
      ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D^{0}}" + neutralLabel +
       "#font[132]{]}_{D^{0}*}" + hstLabel + "^{" + chargeLabel + "}")
          .c_str(),
      "l");
  legend->AddEntry(
      bu2Dst0Hst_D0gammaHist,
      ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D^{0}}" + crossFeedLabel +
       "#font[132]{]}_{D^{0}*}" + hstLabel + "^{" + chargeLabel + "}")
          .c_str(),
      "l");
  legend->AddEntry(bu2D0HHist,
                   ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}" +
                    daughtersLabel + "#font[132]{]}_{D^{0}}" + bachelorLabel +
                    "^{" + chargeLabel + "}")
                       .c_str(),
                   "l");
  legend->AddEntry(bu2D0HstHist,
                   ("B^{" + chargeLabel + "}#rightarrow#font[132]{[}" +
                    daughtersLabel + "#font[132]{]}_{D^{0}}" + hstLabel + "^{" +
                    chargeLabel + "}")
                       .c_str(),
                   "l");
  legend->AddEntry(bd2DstHHist,
                   ("B^{0}#rightarrow#font[132]{[}#font[132]{[}" +
                    daughtersLabel + "#font[132]{]}_{D^{0}}#pi^{-}#font["
                                     "132]{]}_{D^{-}*}" +
                    bachelorLabel + "^{+}")
                       .c_str(),
                   "l");
  legend->AddEntry(bd2D0Hst0Hist,
                   ("B^{0}#rightarrow#font[132]{[}" + daughtersLabel +
                    "#font[132]{]}_{D^{0}}" + hstLabel + "^{0}")
                       .c_str(),
                   "l");
  legend->AddEntry(
      missIdHist,
      ("Miss-ID B^{" + chargeLabel + "}#rightarrow#font[132]{[}#font[132]{[}" +
       daughtersLabel + "#font[132]{]}_{D^{0}}" + crossFeedLabel +
       "#font[132]{]}_{D^{0}*}" + missIdLabel + "^{" + chargeLabel + "}")
          .c_str(),
      "l");
  legend->AddEntry(combinatorialHist, "Combinatorial", "l");

  // --------------- plot onto canvas ---------------------

  TCanvas canvas(
      ("simPdf_" + ComposeFittingCategoryName(neutral, bachelor, daughters))
          .c_str(),
      "simPdf", 1500, 900);
  frame->Draw();
  legend->Draw("same");
  // dataHist->Draw("same");

  canvas.SaveAs(("Result_" +
                 ComposeFittingCategoryName(neutral, bachelor, daughters) +
                 ".pdf")
                    .c_str());
}

void Fitting(RooDataSet &fullDataSet, Configuration &config,
             Categories &categories, std::vector<Neutral> neutralVec,
             std::vector<Daughters> daughtersVec,
             std::vector<Charge> chargeVec) {

  RooSimultaneous simPdf("simPdf", "simPdf", categories.fitting);

  std::vector<std::unique_ptr<Pdf>> pdfs;

  // d is a reference to an element od the vector
  // Downside: don't have direct access to the index
  for (auto &d : daughtersVec) {

    if (d == Daughters::kpi) {

      // emplace_back creates the object in the vector, emplace_back creates the
      // object then moves it into the vector
      // You only have to pass the arguments as if you were constructing the
      // vector type
      // The operators required to do this are not supported by RooFit so we
      // have to use a vector of pointers

      // switch (neutral) {
      // case Neutral::pi0:
      for (auto &n : neutralVec) {

        switch (n) {
        
          case Neutral::pi0:

          pdfs.emplace_back(new Pdf(Neutral::pi0, Bachelor::pi, Daughters::kpi,
                                    config.buMass()));
          pdfs.emplace_back(new Pdf(Neutral::pi0, Bachelor::k, Daughters::kpi,
                                    config.buMass()));
          break;
        
        case Neutral::gamma:
         
          pdfs.emplace_back(new Pdf(Neutral::gamma, Bachelor::pi,
                                    Daughters::kpi, config.buMass()));
          pdfs.emplace_back(new Pdf(Neutral::gamma, Bachelor::k, Daughters::kpi,
                                    config.buMass()));
        
        }
      }
    } else if (d == Daughters::kk) {

      for (auto &n : neutralVec) {

        switch (n) {
        
          case Neutral::pi0:

          pdfs.emplace_back(new Pdf(Neutral::pi0, Bachelor::pi, Daughters::kk,
                                    config.buMass()));
          pdfs.emplace_back(new Pdf(Neutral::pi0, Bachelor::k, Daughters::kk,
                                    config.buMass()));

          break;

        case Neutral::gamma:
        
          pdfs.emplace_back(new Pdf(Neutral::gamma, Bachelor::pi, Daughters::kk,
                                    config.buMass()));
          pdfs.emplace_back(new Pdf(Neutral::gamma, Bachelor::k, Daughters::kk,
                                    config.buMass()));
          break;
        
        }
      }
    } else if (d == Daughters::pipi) {

      for (auto &n : neutralVec) {

        switch (n) {
        
          case Neutral::pi0:

          pdfs.emplace_back(new Pdf(Neutral::pi0, Bachelor::pi, Daughters::pipi,
                                    config.buMass()));
          pdfs.emplace_back(new Pdf(Neutral::pi0, Bachelor::k, Daughters::pipi,
                                    config.buMass()));
          break;

        case Neutral::gamma:
        
          pdfs.emplace_back(new Pdf(Neutral::gamma, Bachelor::pi,
                                    Daughters::pipi, config.buMass()));
          pdfs.emplace_back(new Pdf(Neutral::gamma, Bachelor::k,
                                    Daughters::pipi, config.buMass()));
          break;
        
        }
      }
    } else {
      
      for (auto &n : neutralVec) {
        
        switch (n) {
        
          case Neutral::pi0:

          pdfs.emplace_back(new Pdf(Neutral::pi0, Bachelor::pi, Daughters::pik,
                                    config.buMass()));
          pdfs.emplace_back(new Pdf(Neutral::pi0, Bachelor::k, Daughters::pik,
                                    config.buMass()));

          break;

        case Neutral::gamma:
          
          pdfs.emplace_back(new Pdf(Neutral::gamma, Bachelor::pi,
                                    Daughters::pik, config.buMass()));
          pdfs.emplace_back(new Pdf(Neutral::gamma, Bachelor::k, Daughters::pik,
                                    config.buMass()));
          break;
        
        }
      }
    }
  }

  for (auto &p : pdfs) {
    p->AddToSimultaneousPdf(simPdf);
  }

  // --------------- fit  ---------------------

  // simPdf.fitTo(fullDataSet);
  RooFitResult *result = simPdf.fitTo(fullDataSet, RooFit::Save());

  // Loop over daughters again to plot correct PDFs
  for (auto &p : pdfs) {
    Plotting(*p, chargeVec, config, categories, fullDataSet, simPdf);
  }

  result->Print();
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

// Path to roodatasets
std::string dsPath =
    "/Users/alexandrarollings/Desktop/FittingProgramme/roodatasets/";
// std::string dsPath = "/home/rollings/ButoDst0X_FIT/roodatasets/";

int main(int argc, char **argv) {

  std::vector<Year> yearVec;
  std::vector<Polarity> polarityVec;
  std::vector<Bachelor> bachelorVec;
  std::vector<Neutral> neutralVec;
  std::vector<Daughters> daughtersVec;
  std::vector<Charge> chargeVec;

  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options.
  { // calls destructor when object goes out of scope: Will tell you if
    // anything
    // was not used that was given as a command line argument before
    // continuing
    ParseArguments args(argc, argv); // object instantiated

    std::string yearArg("2011,2012,2015");
    std::string polarityArg("up,down");
    std::string bachelorArg("pi,k");
    std::string neutralArg("pi0,gamma");
    std::string daughtersArg("kpi,kk,pipi,pik");
    std::string chargeArg("plus,minus");

    // We always want to simultaneously fir the pi AND k bachelor modes
    // together
    bachelorVec = ExtractEnumList<Bachelor>(bachelorArg);

    if (args("help")) {

      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "The following options are possible:\n";
      std::cout << "\n";
      std::cout << "    -year choice {2011,2012,2015} default: " << yearArg
                << "\n";
      std::cout << "    -polarity choice {up,down} default: " << polarityArg
                << "\n";
      // std::cout << "    -bachelor choice {k,pi} default: " << bachelorArg
      // <<
      // "\n";
      std::cout << "    -neutral choice {pi0,gamma} default:" << neutralArg
                << "\n";
      std::cout << "    -daughters choice {kpi,kk,pipi,pik} default: "
                << daughtersArg << "\n";
      std::cout << "    -charge choice {plus,minus} default: " << chargeArg
                << "\n";
      std::cout << "\n";
      std::cout << "To specify multiple options, separate them by commas.\n";
      std::cout << " ----------------------------------------------------------"
                   "------------------------------------------------\n";
      std::cout << "\n";
    } else {

      // Year
      // args matches "year" to string given in command like and assigns
      // option
      // parsed to year
      if (!args("year", yearArg)) {
        std::cout << "Using default value -year=[" << yearArg << "].\n";
      }
      try {
        yearVec = ExtractEnumList<Year>(yearArg);
      } catch (std::invalid_argument) {
        std::cerr << "year assignment failed, please specify: "
                     "-year=[2011,2012,2015].\n";
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
      } catch (std::invalid_argument) {
        std::cerr << "charge assignment failed, please specify: "
                     "-charge=[plus,minus].\n";
        return 1;
      }
    }

    Categories categories;
    Configuration config(categories); // Initialise RooRealVars

    RooDataSet fullDataSet("dataset", "dataset", config.fullArgSet());

    // Loop over all options in order to extract correct roodatasets
    for (unsigned int yCounter = 0; yCounter < yearVec.size(); yCounter++) {
      for (unsigned int pCounter = 0; pCounter < polarityVec.size();
           pCounter++) {
        for (unsigned int bCounter = 0; bCounter < bachelorVec.size();
             bCounter++) {
          for (unsigned int dCounter = 0; dCounter < daughtersVec.size();
               dCounter++) {
            for (unsigned int cCounter = 0; cCounter < chargeVec.size();
                 cCounter++) {
              for (unsigned int nCounter = 0; nCounter < neutralVec.size();
                   nCounter++) {
                std::string dsFile =
                    dsPath +
                    ComposeFilename(yearVec[yCounter], polarityVec[pCounter],
                                    bachelorVec[bCounter], neutralVec[nCounter],
                                    daughtersVec[dCounter],
                                    chargeVec[cCounter]) +
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
                    fullDataSet.append(*inputDataSet);
                    std::cout << "Appended to full data set...\n";
                  }
                }
              }
            }
          }
        }
      }
    }

    Fitting(fullDataSet, config, categories, neutralVec, daughtersVec,
            chargeVec);

    //   for (unsigned int i = 0; i < fullDataSet.numEntries(); i++) {
    //
    //     RooArgSet const *row = fullDataSet.get(i);
    //
    //     std::cout << "For event " << i << ":";
    //
    //     RooCategory *neutralPtr =
    //         dynamic_cast<RooCategory
    //         *>(row->find(categories.neutral.GetName()));
    //     if (neutralPtr == nullptr) {
    //       std::stringstream output;
    //       output << "No category assigned to neutral for event " << i << ".";
    //       throw std::runtime_error(output.str());
    //     } else {
    //       std::cout << "    neutral = " << neutralPtr->getLabel() << "\n";
    //       if (neutralPtr->getLabel() == "gamma") {
    //
    //         std::cerr << "Wrong neutral assigned (gamma)\n";
    //         return 1;
    //       }
    //     }
    //   }
    //
  }
  return 0;
}
