#include "Plotting.h"

// Function to set the style for all THists
void SetStyle() {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.04, "XY");
  gStyle->SetLabelSize(0.035, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetLegendTextSize(0.05);
  gStyle->SetTitleOffset(1.0, "X");
  gStyle->SetTitleOffset(1.3, "Y");
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.11);
}


// Plot projections
void Plotting1D(int const id, PdfBase &pdf, Configuration &config,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                std::string const &outputDir, RooFitResult *result,
                std::map<Neutral, std::map<Mass, double> > &yMaxMap) {
  SetStyle();

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  auto blankHist = std::make_unique<TH1D>(
      ("blankHist" + ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "blankHist", 1, 0, 1);
  blankHist->SetLineColor(kWhite);
  blankHist->SetLineWidth(2);

  TLegend legend(0.72, 0.75, 0.9, 0.85);

  std::string legendString_1 = "#font[22]{LHCb}";
  std::string legendString_2 = "#font[12]{preliminary}";
  if (config.runToy() == true) {
    legend.SetY2(0.83);
    gStyle->SetLegendTextSize(0.06);
    legendString_1 = "#font[132]{TOY}";
    legendString_2 = " ";
  }
  legend.SetBorderSize(0);
  legend.SetMargin(0);
  legend.SetFillStyle(0);
  legend.AddEntry(blankHist.get(), legendString_1.c_str(), "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), legendString_2.c_str(), "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");
  legend.AddEntry(blankHist.get(), " ", "l");

  std::string decayString = "#font[12]{B^{" + EnumToLabel(charge) +
                            "}#rightarrow#font[132]{[}#font[132]{[}" +
                            EnumToLabel(daughters, charge) +
                            "#font[132]{]}_{D}" + EnumToLabel(neutral) +
                            "#font[132]{]}_{D*}" + EnumToLabel(bachelor) +
                            "^{" + EnumToLabel(charge) + "}}";
  legend.AddEntry(blankHist.get(), decayString.c_str(), "l");

  TList *list = legend.GetListOfPrimitives();
  if (list != nullptr) {
    TObject *entryObj1 = list->At(3);
    if (entryObj1 != nullptr) {
      auto entry1 = dynamic_cast<TLegendEntry *>(entryObj1);
      if (entry1 != nullptr) {
        entry1->SetTextSize(0.035);
      } else {
        throw std::runtime_error(
            "Could not cast entry1 from TObject to TLegendEntry.");
      }
    } else {
      throw std::runtime_error(
          "Could not extract entryObj1 from list in TLegend.");
    }
    TObject *entryObj2 = list->At(9);
    if (entryObj2 != nullptr) {
      auto entry2 = dynamic_cast<TLegendEntry *>(entryObj2);
      if (entry2 != nullptr) {
        entry2->SetTextSize(0.045);
      } else {
        throw std::runtime_error(
            "Could not cast entry2 from TObject to TLegendEntry.");
      }
    } else {
      throw std::runtime_error(
          "Could not extract entryObj2 from list in TLegend.");
    }
  }

  // ------------- Draw Legends -------------- //
  std::map<std::string, std::map<std::string, Color_t> > colorMap;

  colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0gamma"] = kAzure - 4;
  colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0h_D0gamma"] = kRed + 1;
  colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0pi0"] = kAzure + 3;
  colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0h_D0pi0"] = kMagenta - 1;
  colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0gamma_WN"] = kAzure + 4;
  colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0h_D0gamma_WN"] =
      kPink - 7;
  colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0pi0_WN"] = kBlue - 6;
  colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0h_D0pi0_WN"] =
      kMagenta - 10;
  colorMap[EnumToString(Bachelor::pi)]["Bd2Dsth"] = kBlue - 3;
  colorMap[EnumToString(Bachelor::pi)]["misId_Bd2Dsth"] =
      kMagenta + 4;
  colorMap[EnumToString(Bachelor::pi)]["Bu2D0hst"] = kGreen + 2;
  colorMap[EnumToString(Bachelor::pi)]["misId_Bu2D0hst"] =
      kOrange - 3;
  colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0hst_D0pi0"] = kGreen + 4;
  colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0hst_D0pi0"] =
      kOrange + 4;
  colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0hst_D0gamma"] = kBlue + 4;
  colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0hst_D0gamma"] =
    kRed + 3;
  colorMap[EnumToString(Bachelor::k)]["Bu2Dst0h_D0gamma"] =
      colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0h_D0gamma"];
  colorMap[EnumToString(Bachelor::k)]["misId_Bu2Dst0h_D0gamma"] =
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0gamma"];
  colorMap[EnumToString(Bachelor::k)]["Bu2Dst0h_D0pi0"] =
      colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0h_D0pi0"];
  colorMap[EnumToString(Bachelor::k)]["misId_Bu2Dst0h_D0pi0"] =
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0pi0"];
  colorMap[EnumToString(Bachelor::k)]["Bu2Dst0h_D0gamma_WN"] =
      colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0h_D0gamma_WN"];
  colorMap[EnumToString(Bachelor::k)]["misId_Bu2Dst0h_D0gamma_WN"] =
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0gamma_WN"];
  colorMap[EnumToString(Bachelor::k)]["misId_Bu2Dst0h_D0pi0_WN"] =
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0pi0_WN"];
  colorMap[EnumToString(Bachelor::k)]["Bu2Dst0h_D0pi0_WN"] =
      colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0h_D0pi0_WN"];
  colorMap[EnumToString(Bachelor::k)]["Bd2Dsth"] =
      colorMap[EnumToString(Bachelor::pi)]["misId_Bd2Dsth"];
  colorMap[EnumToString(Bachelor::k)]["misId_Bd2Dsth"] =
      colorMap[EnumToString(Bachelor::pi)]["Bd2Dsth"];
  colorMap[EnumToString(Bachelor::k)]["Bu2D0hst"] =
      colorMap[EnumToString(Bachelor::pi)]["misId_Bu2D0hst"];
  colorMap[EnumToString(Bachelor::k)]["misId_Bu2D0hst"] =
      colorMap[EnumToString(Bachelor::pi)]["Bu2D0hst"];
  colorMap[EnumToString(Bachelor::k)]["Bu2Dst0hst_D0pi0"] =
      colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0hst_D0pi0"];
  colorMap[EnumToString(Bachelor::k)]["misId_Bu2Dst0hst_D0pi0"] =
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0hst_D0pi0"];
  colorMap[EnumToString(Bachelor::k)]["Bu2Dst0hst_D0gamma"] =
      colorMap[EnumToString(Bachelor::pi)]["misId_Bu2Dst0hst_D0gamma"];
  colorMap[EnumToString(Bachelor::k)]["misId_Bu2Dst0hst_D0gamma"] =
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0hst_D0gamma"];
  // colorMap["MisRecPi"] = kBlue - 6;
  // colorMap["MisRecK"] = kMagenta - 10;
  // colorMap["Bu2D0pi"] = kBlue + 4;
  // colorMap["Bu2D0K"] = kMagenta - 7;
  // colorMap["PartRecPi"] = kGreen + 3;
  // colorMap["PartRecK"] = kRed + 4;
  // colorMap["Bs2Dst0Kpi"] = kOrange - 3;
  // colorMap["Bs2D0Kpi"] = kOrange + 4;
  // colorMap["Bu2Dst0h_D0gamma_FAVasSUP"] = kGreen + 2;
  // colorMap["Bu2Dst0h_D0pi0_FAVasSUP"] = kGreen - 6;

  TLegend labels(0.14, 0.25, 0.28, 0.9);
  labels.SetLineColor(kWhite);

  std::string oppCharge;
  if (charge == Charge::plus) {
    oppCharge = "-";
  } else if (charge == Charge::minus) {
    oppCharge = "+";
  } else {
    oppCharge = "#mp";
  }

  auto hist_Bu2Dst0pi_D0gamma = std::make_unique<TH1D>(
      ("hist_Bu2Dst0pi_D0gamma" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "hist_Bu2Dst0pi_D0gamma", 1, 0, 1);
  hist_Bu2Dst0pi_D0gamma->SetLineColor(
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0gamma"]);
  hist_Bu2Dst0pi_D0gamma->SetLineWidth(3);
  std::string str_Bu2Dst0pi_D0gamma =
      " #font[12]{B^{" + EnumToLabel(charge) +
      "}#rightarrow#font[132]{[}#font[132]{[}" +
      EnumToLabel(daughters, charge) +
      "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}#pi^{" +
      EnumToLabel(charge) + "}}";

  auto hist_Bu2Dst0pi_D0pi0 = std::make_unique<TH1D>(
      ("hist_Bu2Dst0pi_D0pi0" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "hist_Bu2Dst0pi_D0pi0", 1, 0, 1);
  hist_Bu2Dst0pi_D0pi0->SetLineColor(
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0pi0"]);
  hist_Bu2Dst0pi_D0pi0->SetLineWidth(3);
  std::string str_Bu2Dst0pi_D0pi0 =
      " #font[12]{B^{" + EnumToLabel(charge) +
      "}#rightarrow#font[132]{[}#font[132]{[}" +
      EnumToLabel(daughters, charge) +
      "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{*0}}#pi^{" +
      EnumToLabel(charge) + "}}";

  auto hist_Bu2Dst0pi_D0gamma_WN = std::make_unique<TH1D>(
      ("hist_Bu2Dst0pi_D0gamma_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "hist_Bu2Dst0pi_D0gamma_WN", 1, 0, 1);
  hist_Bu2Dst0pi_D0gamma_WN->SetLineColor(
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0gamma_WN"]);
  hist_Bu2Dst0pi_D0gamma_WN->SetLineWidth(3);
  std::string str_Bu2Dst0pi_D0gamma_WN =
      "Mis. Rec. #font[12]{B^{" + EnumToLabel(charge) +
      "}#rightarrow#font[132]{[}#font[132]{[}" +
      EnumToLabel(daughters, charge) +
      "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}#pi^{" +
      EnumToLabel(charge) + "}}";

  auto hist_Bu2Dst0pi_D0pi0_WN = std::make_unique<TH1D>(
      ("hist_Bu2Dst0pi_D0pi0_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "hist_Bu2Dst0pi_D0pi0_WN", 1, 0, 1);
  hist_Bu2Dst0pi_D0pi0_WN->SetLineColor(
      colorMap[EnumToString(Bachelor::pi)]["Bu2Dst0h_D0pi0_WN"]);
  hist_Bu2Dst0pi_D0pi0_WN->SetLineWidth(3);
  std::string str_Bu2Dst0pi_D0pi0_WN =
      "Mis. Rec. #font[12]{B^{" + EnumToLabel(charge) +
      "}#rightarrow#font[132]{[}#font[132]{[}" +
      EnumToLabel(daughters, charge) +
      "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{*0}}#pi^{" +
      EnumToLabel(charge) + "}}";

  // auto hist_MisRecPi = std::make_unique<TH1D>(
  //     ("hist_MisRecPi" + ComposeName(id, neutral, bachelor, daughters, charge))
  //         .c_str(),
  //     "hist_MisRecPi", 1, 0, 1);
  // hist_MisRecPi->SetLineColor(colorMap["MisRecPi"]);
  // hist_MisRecPi->SetLineWidth(3);
  // std::string str_Bu2D0rho =
  //     " #font[12]{B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}" +
  //     EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}#rho^{" +
  //     EnumToLabel(charge) + "}}";
  // std::string str_Bd2Dstpi =
  //     " #font[12]{B^{0}#rightarrow#font[132]{[}#font[132]{[}" +
  //     EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}#pi^{" +
  //     oppCharge + "}#font[132]{]}_{D^{*" + oppCharge + "}}#pi^{" +
  //     EnumToLabel(charge) + "}}";
  // auto hist_PartRecPi = std::make_unique<TH1D>(
  //     ("hist_PartRecPi" + ComposeName(id, neutral, bachelor, daughters, charge))
  //         .c_str(),
  //     "hist_PartRecPi", 1, 0, 1);
  // hist_PartRecPi->SetLineColor(colorMap["PartRecPi"]);
  // hist_PartRecPi->SetLineWidth(3);
  // std::string str_PartRecPi_D0pi0 =
  //     " #font[12]{B^{" + EnumToLabel(charge) +
  //     "}#rightarrow#font[132]{[}#font[132]{[}" +
  //     EnumToLabel(daughters, charge) +
  //     "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{*0}}#rho^{" +
  //     EnumToLabel(charge) + "}}";
  // std::string str_PartRecPi_D0gamma =
  //     " #font[12]{B^{" + EnumToLabel(charge) +
  //     "}#rightarrow#font[132]{[}#font[132]{[}" +
  //     EnumToLabel(daughters, charge) +
  //     "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}#rho^{" +
  //     EnumToLabel(charge) + "}}";

  auto hist_Bu2Dst0K_D0gamma = std::make_unique<TH1D>(
      ("hist_Bu2Dst0K_D0gamma" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "hist_Bu2Dst0K_D0gamma", 1, 0, 1);
  hist_Bu2Dst0K_D0gamma->SetLineColor(
      colorMap[EnumToString(Bachelor::k)]["Bu2Dst0h_D0gamma"]);
  hist_Bu2Dst0K_D0gamma->SetLineWidth(3);
  std::string str_Bu2Dst0K_D0gamma =
      " #font[12]{B^{" + EnumToLabel(charge) +
      "}#rightarrow#font[132]{[}#font[132]{[}" +
      EnumToLabel(daughters, charge) +
      "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}K^{" +
      EnumToLabel(charge) + "}}";

  auto hist_Bu2Dst0K_D0pi0 = std::make_unique<TH1D>(
      ("hist_Bu2Dst0K_D0pi0" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "hist_Bu2Dst0K_D0pi0", 1, 0, 1);
  hist_Bu2Dst0K_D0pi0->SetLineColor(
      colorMap[EnumToString(Bachelor::k)]["Bu2Dst0h_D0pi0"]);
  hist_Bu2Dst0K_D0pi0->SetLineWidth(3);
  std::string str_Bu2Dst0K_D0pi0 =
      " #font[12]{B^{" + EnumToLabel(charge) +
      "}#rightarrow#font[132]{[}#font[132]{[}" +
      EnumToLabel(daughters, charge) +
      "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{*0}}K^{" +
      EnumToLabel(charge) + "}}";

  auto hist_Bu2Dst0K_D0gamma_WN = std::make_unique<TH1D>(
      ("hist_Bu2Dst0K_D0gamma_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "hist_Bu2Dst0K_D0gamma_WN", 1, 0, 1);
  hist_Bu2Dst0K_D0gamma_WN->SetLineColor(
      colorMap[EnumToString(Bachelor::k)]["Bu2Dst0h_D0gamma_WN"]);
  hist_Bu2Dst0K_D0gamma_WN->SetLineWidth(3);
  std::string str_Bu2Dst0K_D0gamma_WN =
      "Mis. Rec. #font[12]{B^{" + EnumToLabel(charge) +
      "}#rightarrow#font[132]{[}#font[132]{[}" +
      EnumToLabel(daughters, charge) +
      "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}K^{" +
      EnumToLabel(charge) + "}}";

  auto hist_Bu2Dst0K_D0pi0_WN = std::make_unique<TH1D>(
      ("hist_Bu2Dst0K_D0pi0_WN" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      "hist_Bu2Dst0K_D0pi0_WN", 1, 0, 1);
  hist_Bu2Dst0K_D0pi0_WN->SetLineColor(
      colorMap[EnumToString(Bachelor::k)]["Bu2Dst0h_D0pi0_WN"]);
  hist_Bu2Dst0K_D0pi0_WN->SetLineWidth(3);
  std::string str_Bu2Dst0K_D0pi0_WN =
      "Mis. Rec. #font[12]{B^{" + EnumToLabel(charge) +
      "}#rightarrow#font[132]{[}#font[132]{[}" +
      EnumToLabel(daughters, charge) +
      "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{*0}}K^{" +
      EnumToLabel(charge) + "}}";

  // auto hist_MisRecK = std::make_unique<TH1D>(
  //     ("hist_MisRecK" + ComposeName(id, neutral, bachelor, daughters, charge))
  //         .c_str(),
  //     "hist_MisRecK", 1, 0, 1);
  // hist_MisRecK->SetLineColor(colorMap["MisRecK"]);
  // hist_MisRecK->SetLineWidth(3);
  // std::string str_Bu2D0Kst =
  //     " #font[12]{B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}" +
  //     EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}K^{*" +
  //     EnumToLabel(charge) + "}}";
  // std::string str_Bd2DstK =
  //     " #font[12]{B^{0}#rightarrow#font[132]{[}#font[132]{[}" +
  //     EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}#pi^{" +
  //     oppCharge + "}#font[132]{]}_{D^{*" + oppCharge + "}}K^{" +
  //     EnumToLabel(charge) + "}}";
  // auto hist_PartRecK = std::make_unique<TH1D>(
  //     ("hist_PartRecK" + ComposeName(id, neutral, bachelor, daughters, charge))
  //         .c_str(),
  //     "hist_PartRecK", 1, 0, 1);
  // hist_PartRecK->SetLineColor(colorMap["PartRecK"]);
  // hist_PartRecK->SetLineWidth(3);
  // std::string str_PartRecK_D0pi0 =
  //     " #font[12]{B^{" + EnumToLabel(charge) +
  //     "}#rightarrow#font[132]{[}#font[132]{[}" +
  //     EnumToLabel(daughters, charge) +
  //     "#font[132]{]}_{D^{0}}#pi^{0}#font[132]{]}_{D^{*0}}K^{*" +
  //     EnumToLabel(charge) + "}}";
  // std::string str_PartRecK_D0gamma =
  //     " #font[12]{B^{" + EnumToLabel(charge) +
  //     "}#rightarrow#font[132]{[}#font[132]{[}" +
  //     EnumToLabel(daughters, charge) +
  //     "#font[132]{]}_{D^{0}}#gamma#font[132]{]}_{D^{*0}}K^{*" +
  //     EnumToLabel(charge) + "}}";

  // labels.AddEntry(hist_Bu2Dst0pi_D0gamma.get(), str_Bu2Dst0pi_D0gamma.c_str(),
  //                 "l");
  // labels.AddEntry(hist_Bu2Dst0pi_D0pi0.get(), str_Bu2Dst0pi_D0pi0.c_str(), "l");
  // labels.AddEntry(hist_Bu2Dst0pi_D0gamma_WN.get(), str_Bu2Dst0pi_D0gamma_WN.c_str(),
  //                 "l");
  // labels.AddEntry(hist_Bu2Dst0pi_D0pi0_WN.get(), str_Bu2Dst0pi_D0pi0_WN.c_str(),
  //                 "l");
  // // labels.AddEntry(hist_MisRecPi.get(), str_Bu2D0rho.c_str(), "l");
  // // labels.AddEntry(blankHist.get(), str_Bd2Dstpi.c_str(), "l");
  // // labels.AddEntry(hist_PartRecPi.get(), str_PartRecPi_D0pi0.c_str(), "l");
  // // labels.AddEntry(blankHist.get(), str_PartRecPi_D0gamma.c_str(), "l");
  // labels.AddEntry(hist_Bu2Dst0K_D0gamma.get(), str_Bu2Dst0K_D0gamma.c_str(),
  //                 "l");
  // labels.AddEntry(hist_Bu2Dst0K_D0pi0.get(), str_Bu2Dst0K_D0pi0.c_str(), "l");
  // // labels.AddEntry(hist_MisRecK.get(), str_Bu2D0Kst.c_str(), "l");
  // // labels.AddEntry(blankHist.get(), str_Bd2DstK.c_str(), "l");
  // // labels.AddEntry(hist_PartRecK.get(), str_PartRecK_D0pi0.c_str(), "l");
  // // labels.AddEntry(blankHist.get(), str_PartRecK_D0gamma.c_str(), "l");

  // Loop over entries in legend and set size
  TList *labelList = labels.GetListOfPrimitives();
  if (labelList != nullptr) {
    int nLabels = labelList->GetSize();
    for (int i = 0; i < nLabels; ++i) {
      TObject *entryObj = labelList->At(i);
      if (entryObj != nullptr) {
        auto entry = dynamic_cast<TLegendEntry *>(entryObj);
        if (entry != nullptr) {
          entry->SetTextSize(0.04);
        } else {
          throw std::runtime_error(
              "Could not cast entry from TObject to TLegendEntry.");
        }
      } else {
        throw std::runtime_error(
            "Could not extract iter from labelList in TLegend.");
      }
    }
  }

  PlotComponent(Mass::buDelta, config.buDeltaMass(), pdf, fullDataSet, simPdf,
                legend, labels, outputDir, config, colorMap, yMaxMap);
  if (config.fitBuPartial() == true) {
    PlotComponent(Mass::buDeltaPartial, config.buDeltaMass(), pdf, fullDataSet,
                  simPdf, legend, labels, outputDir, config, colorMap, yMaxMap);
  }
  if (config.fit1D() == false) {
    PlotComponent(Mass::delta, config.deltaMass(), pdf, fullDataSet, simPdf,
                  legend, labels, outputDir, config, colorMap, yMaxMap);
  }
}

void Plotting2D(RooDataSet &dataSet, int const id, PdfBase &pdf,
                Configuration &config, std::string const &outputDir,
                std::string const &label) {
  gStyle->SetTitleSize(0.03, "XYZ");
  gStyle->SetLabelSize(0.025, "XYZ");
  gStyle->SetTitleOffset(1, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetTitleOffset(1.5, "Z");
  gStyle->SetPadRightMargin(0.15);

  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();

  auto deltaAbsData = dataSet.reduce(
      ("fitting==fitting::" +
       ComposeFittingName(Mass::delta, neutral, bachelor, daughters, charge))
          .c_str());
  auto deltaDataSet = dynamic_cast<RooDataSet *>(deltaAbsData);
  if (deltaDataSet == nullptr) {
    throw std::runtime_error("Could not cast deltaAbsData to RooDataSet.");
  }

  auto buDeltaAbsData = dataSet.reduce(
      ("fitting==fitting::" +
       ComposeFittingName(Mass::buDelta, neutral, bachelor, daughters, charge))
          .c_str());
  auto buDeltaDataSet = dynamic_cast<RooDataSet *>(buDeltaAbsData);
  if (buDeltaDataSet == nullptr) {
    throw std::runtime_error("Could not cast buDeltaAbsData to RooDataSet.");
  }
  deltaDataSet->append(*buDeltaDataSet);

  if (config.fitBuPartial() == true) {
    auto buDeltaPartialAbsData =
        dataSet.reduce(("fitting==fitting::" +
                        ComposeFittingName(Mass::buDeltaPartial, neutral,
                                           bachelor, daughters, charge))
                           .c_str());
    auto buDeltaPartialDataSet =
        dynamic_cast<RooDataSet *>(buDeltaPartialAbsData);
    if (buDeltaPartialDataSet == nullptr) {
      throw std::runtime_error(
          "Could not cast buDeltaPartialAbsData to RooDataSet.");
    }
    deltaDataSet->append(*buDeltaPartialDataSet);
  }

  auto dataHist = std::unique_ptr<RooDataHist>(deltaDataSet->binnedClone(
      (label + "Hist2d_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      ""));
  if (dataHist == nullptr) {
    throw std::runtime_error("Could not extact binned dataSet.");
  }

  auto dataHist1d = dataHist->createHistogram(
      (label + "Hist2d_" +
       ComposeName(id, neutral, bachelor, daughters, charge))
          .c_str(),
      config.buDeltaMass(), RooFit::Binning(config.buDeltaMass().getBins()),
      RooFit::YVar(config.deltaMass(),
                   RooFit::Binning(config.deltaMass().getBins())));
  if (dataHist1d == nullptr) {
    throw std::runtime_error("\n1D hist of data returns nullptr\n");
  }
  auto dataHist2d =
      std::unique_ptr<TH2>(dynamic_cast<TH2F *>(dataHist1d /* .get() */));
  if (dataHist2d == nullptr) {
    throw std::runtime_error("\n2D hist of data returns nullptr\n");
  }
  dataHist2d->SetTitle("");

  // 2D data plot
  TCanvas canvasData((label + "Canvas_" +
                      ComposeName(id, neutral, bachelor, daughters, charge))
                         .c_str(),
                     "", 1000, 800);
  dataHist2d->SetStats(0);
  if (neutral == Neutral::pi0) {
    dataHist2d->GetYaxis()->SetTitle(
        "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
  }
  dataHist2d->SetTitle(
      ("B^{" + EnumToLabel(charge) + "}#rightarrow#font[132]{[}#font[132]{[}" +
       EnumToLabel(daughters, charge) + "#font[132]{]}_{D^{0}}" +
       EnumToLabel(neutral) + "#font[132]{]}_{D^{*0}}" + EnumToLabel(bachelor) +
       "^{" + EnumToLabel(charge) + "}")
          .c_str());
  dataHist2d->Draw("colz");
  canvasData.Update();
  canvasData.SaveAs((outputDir + "/2d_plots/" +
                     ComposeName(id, neutral, bachelor, daughters, charge) +
                     "_" + label + "2D.pdf")
                        .c_str());
}


void PlotCorrelations(RooFitResult *result, std::string const &outputDir,
                      Configuration &config) {
  TCanvas corrCanvas("corrCanvas", "corrCanvas", 1700, 900);
  TH2 *corrHist = result->correlationHist();
  corrHist->SetStats(0);
  corrHist->SetTitle(" ");
  corrCanvas.cd();
  gStyle->SetLabelSize(0.002, "XY");
  gStyle->SetLabelSize(0.015, "Z");
  gPad->SetLeftMargin(0.3);
  gPad->SetRightMargin(0.2);
  gPad->SetBottomMargin(0.21);
  gPad->SetTopMargin(0.05);
  corrHist->Draw("colz");
  corrCanvas.Update();
  corrCanvas.SaveAs((outputDir + "/plots/CorrelationMatrix_" +
                     config.ReturnBoxString() + ".pdf")
                        .c_str());
}

// Function to plot 1D projections - written so that it can be used for both bu
// and delta mass
void PlotComponent(
    Mass mass, RooRealVar &var, PdfBase &pdf, RooAbsData const &fullDataSet,
    RooSimultaneous const &simPdf, TLegend &legend, TLegend &labels,
    std::string const &outputDir, Configuration &config,
    std::map<std::string, std::map<std::string, Color_t> > &colorMap,
    std::map<Neutral, std::map<Mass, double> > &yMaxMap) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  int id = 0;

  // Stops ROOT print INFO messages
  gErrorIgnoreLevel = kWarning;

  std::unique_ptr<RooPlot> frame(var.frame(RooFit::Title(" ")));

  fullDataSet.plotOn(frame.get(),
                     RooFit::Cut(("fitting==fitting::" +
                                  ComposeFittingName(mass, neutral, bachelor,
                                                     daughters, charge))
                                     .c_str()));

  if (config.noFit() == false) {
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(config.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(config.fitting, fullDataSet),
                  RooFit::LineColor(kBlue));
  }

  // Everything to be plotted has to be declared outside of a loop, in the scope
  // of the canvas
  RooHist *pullHist = nullptr;
  std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

  pullHist = frame->RooPlot::pullHist();

  if (config.noFit() == false) {
    std::vector<const char *> pdfCharVec;
    // Need to add in list of components here rather than just using functions
    // RooArgList as need specific order
    if (mass == Mass::buDelta) {
      if (neutral == Neutral::pi0) {
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0_WN().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0gamma_WN().GetName());
        // pdfCharVec.emplace_back(pdf.pdfBu_Bd2Dsth().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2D0hst().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0hst_D0pi0().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0h_D0pi0_WN().GetName());
        if (bachelor == Bachelor::k) {
          pdfCharVec.emplace_back(
              pdf.pdfBu_misId_Bu2Dst0h_D0gamma_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2D0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0hst_D0pi0().GetName());
        }
      } else {
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0gamma().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0gamma_WN().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0_WN().GetName());
        // pdfCharVec.emplace_back(pdf.pdfBu_Bd2Dsth().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2D0hst().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0hst_D0pi0().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0h_D0pi0_WN().GetName());
        pdfCharVec.emplace_back(
            pdf.pdfBu_misId_Bu2Dst0h_D0gamma_WN().GetName());
        if (bachelor == Bachelor::k) {
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2D0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0hst_D0pi0().GetName());
        }
      }
    } else if (mass == Mass::delta) {
      if (neutral == Neutral::pi0) {
        pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0pi0_WN().GetName());
        // pdfCharVec.emplace_back(pdf.pdfDelta_Bd2Dsth().GetName());
        pdfCharVec.emplace_back(pdf.pdfDelta_Bu2D0hst().GetName());
        pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0gamma_WN().GetName());
        pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(
            pdf.pdfDelta_misId_Bu2Dst0h_D0pi0_WN().GetName());
        if (bachelor == Bachelor::k) {
          pdfCharVec.emplace_back(
              pdf.pdfDelta_misId_Bu2Dst0h_D0gamma_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2D0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2Dst0hst_D0pi0().GetName());
        }
      } else {
        pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0gamma().GetName());
        pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0gamma_WN().GetName());
        pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0pi0_WN().GetName());
        // pdfCharVec.emplace_back(pdf.pdfDelta_Bd2Dsth().GetName());
        pdfCharVec.emplace_back(pdf.pdfDelta_Bu2D0hst().GetName());
        pdfCharVec.emplace_back(
            pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName());
        pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(
            pdf.pdfDelta_misId_Bu2Dst0h_D0pi0_WN().GetName());
        pdfCharVec.emplace_back(
            pdf.pdfDelta_misId_Bu2Dst0h_D0gamma_WN().GetName());
        if (bachelor == Bachelor::k) {
          pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2D0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2Dst0hst_D0pi0().GetName());
        }
      }
    } else {
      pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName());
      pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2Dst0h_D0pi0().GetName());
      pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2Dst0h_D0pi0_WN().GetName());
      // pdfCharVec.emplace_back(pdf.pdfBuPartial_Bd2Dsth().GetName());
      pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2D0hst().GetName());
      pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2Dst0hst_D0pi0().GetName());
      pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2Dst0h_D0gamma_WN().GetName());
      pdfCharVec.emplace_back(
          pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName());
      pdfCharVec.emplace_back(
          pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN().GetName());
      pdfCharVec.emplace_back(
          pdf.pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN().GetName());
        if (bachelor == Bachelor::k) {
          pdfCharVec.emplace_back(pdf.pdfBuPartial_misId_Bu2D0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfBuPartial_misId_Bu2Dst0hst_D0pi0().GetName());
        }
    }
    std::cout << "\n\n\n";
    for (auto &chars : pdfCharVec) {
      std::cout << chars << "\n";
    }
    std::cout << "\n\n\n";
    // To pass to Components in plotOn, need string in the format "pdf1,pdf2,pdf3"
    while (pdfCharVec.size() > 0) {
      std::string totPdfStr = "";
      for (auto &chars : pdfCharVec) {
        totPdfStr.append(chars);
        totPdfStr.append(",");
        std::cout << totPdfStr << "\n";
      }
      // Remove comma from end
      totPdfStr.pop_back();
      // Find decay mode in order to select correct color for component in
      // colorMap
      std::string pdfStr(pdfCharVec[0]); 
      std::regex re("pdf([A-Za-z]+)_(.+)_(pi0|gamma)_.+");
      std::smatch match;
      std::string modeStr;
      if (std::regex_search(pdfStr, match, re)) {
        modeStr = match.str(2);
      } else {
        throw std::runtime_error(
            "Plotting.cpp: Can't find decay mode in pdfString with regex: " +
            pdfStr + "\n");
      }
      std::cout << modeStr << "\n\n\n";
      simPdf.plotOn(frame.get(),
                    RooFit::Slice(config.fitting,
                                  ComposeFittingName(mass, neutral, bachelor,
                                                     daughters, charge)
                                      .c_str()),
                    RooFit::ProjWData(config.fitting, fullDataSet),
                    RooFit::Components(totPdfStr.c_str()), RooFit::DrawOption("F"),
                    RooFit::FillColor(colorMap[EnumToString(bachelor)][modeStr.c_str()]),
                    RooFit::Precision(1e-3), RooFit::NumCPU(config.nCPU()));
      // Remove first pdf string in vector: plot all others w/out this w/ new color 
      pdfCharVec.erase(pdfCharVec.begin());
      // continue until no PDFs left
    }
    simPdf.plotOn(frame.get(),
                  RooFit::Slice(config.fitting,
                                ComposeFittingName(mass, neutral, bachelor,
                                                   daughters, charge)
                                    .c_str()),
                  RooFit::ProjWData(config.fitting, fullDataSet),
                  RooFit::LineColor(kBlue));
  }

  fullDataSet.plotOn(frame.get(),
                     RooFit::Cut(("fitting==fitting::" +
                                  ComposeFittingName(mass, neutral, bachelor,
                                                     daughters, charge))
                                     .c_str()));

  if (mass == Mass::delta) {
    if (neutral == Neutral::gamma) {
      frame->SetXTitle("m[D^{*0}] - m[D^{0}] (MeV/c^{2})");
    } else {
      frame->SetXTitle(
          "m[D^{*0}] - m[D^{0}] - m[#pi^{0}] + m[#pi^{0}]_{PDG} (MeV/c^{2})");
    }
  } else {
    frame->SetXTitle(("m[D^{*0}" + EnumToLabel(bachelor) + "^{" +
                      EnumToLabel(charge) + "}" +
                      "] - m[D^{*0}] + m[D^{*0}]_{PDG} (MeV/c^{2})")
                         .c_str());
  }

  // --------------- plot onto canvas ---------------------

  TCanvas canvas(
      ("canvas_" + ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "canvas", 1200, 1000);

  TPad pad1(
      ("pad1_" + ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "pad1", 0.0, 0.14, 1.0, 1.0, kWhite);
  pad1.Draw();

  TPad pad2(
      ("pad2_" + ComposeName(id, mass, neutral, bachelor, daughters, charge))
          .c_str(),
      "pad2", 0.0, 0.02, 1.0, 0.14, kWhite);
  pad2.Draw();

  TLine zeroLine(var.getMin(), 0, var.getMax(), 0);
  zeroLine.SetLineColor(kRed);
  zeroLine.SetLineStyle(kDashed);

  if (config.noFit() == false) {
    canvas.cd();
    pad2.cd();
    pullFrame->addPlotable(pullHist /* .get() */, "P");
    pullFrame->SetName(("pullFrame_" + ComposeName(id, mass, neutral, bachelor,
                                                   daughters, charge))
                           .c_str());
    pullFrame->SetTitle("");
    pullFrame->SetXTitle(" ");
    pullFrame->GetYaxis()->SetTitle(" ");
    // pullFrame->GetYaxis()->SetTitle("Residuals (#sigma)");
    // pullFrame->SetTitleSize(0.2, "Y");
    // pullFrame->SetTitleOffset(0.1, "Y");
    pullFrame->SetLabelSize(0.15, "Y");
    pullFrame->SetLabelOffset(0.02, "Y");
    pullFrame->SetLabelFont(132, "Y");
    pullFrame->Draw();
    zeroLine.Draw("same");
  }

  canvas.cd();
  pad1.cd();
  if (((bachelor == Bachelor::k && daughters != Daughters::kpi) ||
       daughters == Daughters::pik) &&
      config.blindFit() == true) {
    frame->SetLabelOffset(50, "Y");
    frame->GetYaxis()->SetTickLength(0.);
  }
  frame->Draw();

  double blindMin, blindMax;
  if (mass == Mass::delta) {
    blindMin = var.getMin();
    if (neutral == Neutral::gamma) {
      blindMax = 160;
    } else {
      blindMax = 155;
    }
  } else if (mass == Mass::buDelta) {
    blindMin = 5150;
    if (neutral == Neutral::gamma) {
      blindMax = 5375;
    } else {
      blindMax = 5350;
    }
  } else {
    blindMin = 5150;
    blindMax = 5400;
  }

  if (daughters == Daughters::pik && config.blindFit() == true) {
    frame->SetMinimum(0.001);
    if (bachelor == Bachelor::pi) {
      // frame->SetMaximum(yMaxMap[neutral][mass] * 0.004);
      frame->SetMaximum(yMaxMap[neutral][mass] * 0.01);
    } else {
      // frame->SetMaximum(yMaxMap[neutral][mass] * 0.002);
      frame->SetMaximum(yMaxMap[neutral][mass] * 0.005);
    }
  }
  TPaveLabel blindBox(blindMin, 0.001, blindMax, frame->GetMaximum() - 0.01,
                      "#font[12]{Blind}", "");
  blindBox.SetBorderSize(0);
  blindBox.SetTextSize(0.07);
  // blindBox.SetTextAngle(30);
  blindBox.SetTextColor(kRed + 1);
  blindBox.SetFillColor(10);
  if (daughters == Daughters::pik && config.blindFit() == true &&
      config.splitByCharge() == true) {
    blindBox.Draw("same");
  }
  legend.Draw("same");

  if (mass == Mass::buDelta && daughters == Daughters::kpi) {
    labels.Draw("same");
  }
  // Stores max values for kpi, to set in pik
  if (daughters == Daughters::kpi && bachelor == Bachelor::pi) {
    yMaxMap[neutral][mass] = frame->GetMaximum();
  }

  canvas.Update();
  canvas.SaveAs((outputDir + "/plots/" +
                 ComposeName(id, mass, neutral, bachelor, daughters, charge) +
                 "_" + config.ReturnBoxString() + ".pdf")
                    .c_str());
}
