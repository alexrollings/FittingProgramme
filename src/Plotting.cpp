#include "Plotting.h"

// Function to set the style for all THists
void SetStyle() {
  gStyle->SetTitleFont(132, "XYZ");
  gStyle->SetLabelFont(132, "XYZ");
  gStyle->SetStatFont(132);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetTitleSize(0.05, "XY");
  gStyle->SetLabelSize(0.045, "XY");
  gStyle->SetLegendFont(132);
  gStyle->SetLegendTextSize(0.05);
  gStyle->SetTitleOffset(1.05, "X");
  gStyle->SetTitleOffset(1.2, "Y");
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);
}

void FormatLaTeX(std::string &str) {
  std::replace(str.begin(), str.end(), '#', '\\');
  str = "$" + str + "$";
}

void LaTeXYields(Configuration &config, std::vector<PdfBase *> &pdfs,
                 std::string &outputDir,
                 std::unique_ptr<RooFitResult> &result) {
  Neutral n = config.neutral();
  std::ofstream outfile;
  outfile.open(outputDir + "/results/Yields_" + EnumToString(n) + ".tex");
  outfile << "\\documentclass[12pt, landscape]{article}\n";
  outfile << "\\usepackage[margin=0.1in]{geometry}\n";
  outfile << "\\usepackage{mathtools}\n";
  outfile << "\\usepackage{float}\n";
  outfile << "\\usepackage[table]{xcolor}\n";
  outfile << "\\restylefloat{table}\n";
  outfile << "\\begin{document}\n";
  // outfile << "\\newpage\n";
  // outfile << "\\begin{itemize}\n";
  // if (n == Neutral::gamma) {
  //   outfile << "\t\\item $f_{WN} = "
  //           <<
  //           NeutralVars<Neutral::gamma>::Get(0).bkgFracGlobal_WN().getVal()
  //           << " \\pm "
  //           <<
  //           NeutralVars<Neutral::gamma>::Get(0).bkgFracGlobal_WN().getError()
  //           << "$\n";
  //   outfile << "\t\\item $\\epsilon_{sel}(D\\gamma \\text{ signal}) = "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, n, Bachelor::pi,
  //                           Efficiency::mcEff)
  //           << " \\pm "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma, n, Bachelor::pi,
  //                           Efficiency::mcEffErr)
  //           << "$\n";
  //   outfile << "\t\\item $\\epsilon_{sel}(D\\gamma \\text{ WN}) = "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, n, Bachelor::pi,
  //                           Efficiency::mcEff)
  //           << " \\pm "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, n, Bachelor::pi,
  //                           Efficiency::mcEffErr)
  //           << "$\n";
  //   outfile << "\t\\item $\\epsilon_{sel}(D\\pi^0 \\text{ signal}) = "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, n, Bachelor::pi,
  //                           Efficiency::mcEff)
  //           << " \\pm "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, n, Bachelor::pi,
  //                           Efficiency::mcEffErr)
  //           << "$\n";
  //   outfile << "\t\\item $\\epsilon_{sel}(D\\pi^0 \\text{ WN}) = "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, n, Bachelor::pi,
  //                           Efficiency::mcEff)
  //           << " \\pm "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, n, Bachelor::pi,
  //                           Efficiency::mcEffErr)
  //           << "$\n";
  // } else {
  //   outfile << "\t\\item $f_{WN} = "
  //           << NeutralVars<Neutral::pi0>::Get(0).bkgFracGlobal_WN().getVal()
  //           << " \\pm "
  //           <<
  //           NeutralVars<Neutral::pi0>::Get(0).bkgFracGlobal_WN().getError()
  //           << "$\n";
  //   outfile << "\t\\item $\\epsilon_{sel}(D\\pi^0 \\text{ signal}) = "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, n, Bachelor::pi,
  //                           Efficiency::mcEff)
  //           << " \\pm "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0, n, Bachelor::pi,
  //                           Efficiency::mcEffErr)
  //           << "$\n";
  //   outfile << "\t\\item $\\epsilon_{sel}(D\\pi^0 \\text{ WN}) = "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, n, Bachelor::pi,
  //                           Efficiency::mcEff)
  //           << " \\pm "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0pi0_WN, n, Bachelor::pi,
  //                           Efficiency::mcEffErr)
  //           << "$\n";
  //   outfile << "\t\\item $\\epsilon_{sel}(D\\gamma \\text{ WN}) = "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, n, Bachelor::pi,
  //                           Efficiency::mcEff)
  //           << " \\pm "
  //           << ReturnMCEffs(Mode::Bu2Dst0pi_D0gamma_WN, n, Bachelor::pi,
  //                           Efficiency::mcEffErr)
  //           << "$\n";
  // }
  // outfile << "\t\\item $\\epsilon_{sel}(B^0\\rightarrow D^{*\\pm}\\pi^{\\mp})
  // = "
  //         << ReturnMCEffs(Mode::Bd2Dstpi, n, Bachelor::pi, Efficiency::mcEff)
  //         << " \\pm " <<
  //     ReturnMCEffs(Mode::Bd2Dstpi, n, Bachelor::pi, Efficiency::mcEffErr)
  //         << "$\n";
  // outfile << "\t\\item $\\epsilon_{sel}(B^{\\pm}\\rightarrow D\\rho^{\\pm}) =
  // "
  //         << ReturnMCEffs(Mode::Bu2D0rho, n, Bachelor::pi, Efficiency::mcEff)
  //         << " \\pm " <<
  //     ReturnMCEffs(Mode::Bu2D0rho, n, Bachelor::pi, Efficiency::mcEffErr)
  //         << "$\n";
  // outfile << "\t\\item $\\epsilon_{sel}(B^{\\pm}\\rightarrow (D^*\\rightarrow
  // "
  //            "D\\pi^0)\\rho^{\\pm}) = "
  //         << ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, n, Bachelor::pi,
  //                         Efficiency::mcEff)
  //         << " \\pm " <<
  //     ReturnMCEffs(Mode::Bu2Dst0rho_D0pi0, n, Bachelor::pi,
  //                  Efficiency::mcEffErr)
  //         << "$\n";
  // outfile << "\t\\item $\\epsilon_{sel}(B^{\\pm}\\rightarrow (D^*\\rightarrow
  // "
  //            "D\\gamma)\\rho^{\\pm}) = "
  //         << ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, n, Bachelor::pi,
  //                         Efficiency::mcEff)
  //         << " \\pm " <<
  //     ReturnMCEffs(Mode::Bu2Dst0rho_D0gamma, n, Bachelor::pi,
  //                  Efficiency::mcEffErr)
  //         << "$\n";
  // outfile << "\t\\item $BF(B^0\\rightarrow D^{*\\pm}\\pi^{\\mp}) = (2.74 \\pm
  // "
  //            "0.13) \\times 10^{-3}$\n";
  // outfile << "\t\\item $BF(D^{*\\pm}\\rightarrow D\\pi^{\\pm}) = 0.677 \\pm "
  //            "0.005 $\n";
  // outfile << "\t\\item $BF(B^{\\pm}\\rightarrow D\\rho^{\\pm}) = (1.34 \\pm "
  //            "0.18) \\times 10^{-2}$\n";
  // outfile << "\t\\item $BF(B^{\\pm}\\rightarrow D^*\\rho^{\\pm}) = (9.8 \\pm
  // "
  //            "1.7) \\times 10^{-3}$\n";
  // outfile << "\t\\item $BF(D^*\\rightarrow D\\pi^0) = 0.647 \\pm "
  //            "0.9 $\n";
  // outfile << "\t\\item $BF(D^*\\rightarrow D\\gamma) = 0.353 \\pm "
  //            "0.9 $\n";
  // outfile << "\\end{itemize}\n";
  // outfile << "\\newpage\n";
  for (auto &p : pdfs) {
    Bachelor b = p->bachelor();
    Daughters d = p->daughters();
    Charge c = p->charge();
    outfile << "\\begin{table}[H]\n";
    outfile << "\t\\centering\n";
    outfile << "\t\\footnotesize\n";
    outfile << "\\resizebox{\\textwidth}{!}{%\n";
    if (n == Neutral::gamma) {
      if (config.fitBuPartial() == true) {
        outfile << "\t\\begin{tabular}{|c|c|c|c|c|c|c|c|c|}\n";
        outfile << "\t\\hline\n";
        outfile
            << "\t& $\\epsilon_{cross}$ & N$_{cross}$ & "
               "$\\epsilon_{B(D\\gamma)}$ & "
               "N$_{B(D\\gamma)}$ & $\\epsilon_{\\Delta}$ & N$_{\\Delta}$ & "
               "$\\epsilon_{B(D\\pi^{0})}$ & "
               "N$_{B(D\\pi^{0})}$\\\\ \\hline\n";
      } else {
        outfile << "\t\\begin{tabular}{|c|c|c|c|c|c|c|}\n";
        outfile << "\t\\hline\n";
        outfile << "\t& $\\epsilon_{cross}$ & N$_{cross}$ & "
                   "$\\epsilon_{B(D\\gamma)}$ & "
                   "N$_{B(D\\gamma)}$ & $\\epsilon_{\\Delta}$ & "
                   "N$_{\\Delta}$\\\\ \\hline\n";
      }
      outfile << "\t ";
      if (b == Bachelor::pi) {
        outfile << "\\cellcolor{blue!25}"
                << ReturnLaTeXLabel(Mode::Bu2Dst0pi_D0gamma, c, true);
      } else {
        outfile << "\\cellcolor{orange!50}"
                << ReturnLaTeXLabel(Mode::Bu2Dst0K_D0gamma, c, true);
      }
      outfile << " & ";
      outfile << "$"
              << to_string_with_precision(p->orEffBu2Dst0h_D0gamma().getVal(),
                                          3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_Bu2Dst0h_D0gamma().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Bu2Dst0h_D0gamma().getPropagatedError(*result),
                     0)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(p->buEffBu2Dst0h_D0gamma().getVal(),
                                          3)
              << "$ &";
      outfile << std::fixed << "$"
              << to_string_with_precision(
                     p->N_trueId_Bu_Bu2Dst0h_D0gamma().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Bu_Bu2Dst0h_D0gamma().getPropagatedError(
                         *result),
                     0)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->deltaEffBu2Dst0h_D0gamma().getVal(), 3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_Delta_Bu2Dst0h_D0gamma().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Delta_Bu2Dst0h_D0gamma().getPropagatedError(
                         *result),
                     0)
              << "$ ";
      outfile << "& $"
              << to_string_with_precision(
                     p->buPartialEffBu2Dst0h_D0gamma().getVal(), 3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_BuPartial_Bu2Dst0h_D0gamma().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_BuPartial_Bu2Dst0h_D0gamma()
                         .getPropagatedError(*result),
                     0)
              << "$ \\\\ \\hline\n";
    } else {
      outfile << "\t\\begin{tabular}{|c|c|c|c|c|c|c|}\n";
      outfile << "\t\\hline\n";
      outfile
          << "\t & $\\epsilon_{cross}$ & N$_{cross}$ & $\\epsilon_{B}$ & "
             "N$_{B}$ & $\\epsilon_{\\Delta}$ & N$_{\\Delta}$ \\\\ \\hline\n";
    }
    outfile << "\t ";
    if (b == Bachelor::pi) {
      outfile << "\\cellcolor{blue!25}"
              << ReturnLaTeXLabel(Mode::Bu2Dst0pi_D0pi0, c, true);
    } else {
      outfile << "\\cellcolor{orange!50}"
              << ReturnLaTeXLabel(Mode::Bu2Dst0K_D0pi0, c, true);
    }
    outfile << " & ";
    outfile << "$"
            << to_string_with_precision(p->orEffBu2Dst0h_D0pi0().getVal(), 3)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->N_trueId_Bu2Dst0h_D0pi0().getVal(),
                                        0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Bu2Dst0h_D0pi0().getPropagatedError(*result), 0)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->buEffBu2Dst0h_D0pi0().getVal(), 3)
            << "$ &";
    outfile << std::fixed << "$"
            << to_string_with_precision(
                   p->N_trueId_Bu_Bu2Dst0h_D0pi0().getVal(), 0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Bu_Bu2Dst0h_D0pi0().getPropagatedError(*result),
                   0)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->deltaEffBu2Dst0h_D0pi0().getVal(), 3)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(
                   p->N_trueId_Delta_Bu2Dst0h_D0pi0().getVal(), 0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Delta_Bu2Dst0h_D0pi0().getPropagatedError(
                       *result),
                   0)
            << "$ ";
    if (config.fitBuPartial() == true) {
      outfile << "& $"
              << to_string_with_precision(
                     p->buPartialEffBu2Dst0h_D0pi0().getVal(), 3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_BuPartial_Bu2Dst0h_D0pi0().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_BuPartial_Bu2Dst0h_D0pi0().getPropagatedError(
                         *result),
                     0)
              << "$";
    }
    outfile << "\\\\ \\hline\n";
    if (n == Neutral::gamma) {
      outfile << "\t ";
      if (b == Bachelor::pi) {
        outfile << "\\cellcolor{green!35}"
                << ReturnLaTeXLabel(Mode::Bu2Dst0pi_D0pi0_WN, c, true);
      } else {
        outfile << "\\cellcolor{green!35}"
                << ReturnLaTeXLabel(Mode::Bu2Dst0K_D0pi0_WN, c, true);
      }
      outfile << " & ";
      outfile << "$"
              << to_string_with_precision(p->orEffBu2Dst0h_D0pi0_WN().getVal(),
                                          3)
              << "$ &";
      outfile
          << "$"
          << to_string_with_precision(p->N_trueId_Bu2Dst0h_D0pi0_WN().getVal(),
                                      0)
          << " \\pm "
          << to_string_with_precision(
                 p->N_trueId_Bu2Dst0h_D0pi0_WN().getPropagatedError(*result), 0)
          << "$ &";
      outfile << "$"
              << to_string_with_precision(p->buEffBu2Dst0h_D0pi0_WN().getVal(),
                                          3)
              << "$ &";
      outfile << std::fixed << "$"
              << to_string_with_precision(
                     p->N_trueId_Bu_Bu2Dst0h_D0pi0_WN().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Bu_Bu2Dst0h_D0pi0_WN().getPropagatedError(
                         *result),
                     0)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->deltaEffBu2Dst0h_D0pi0_WN().getVal(), 3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_Delta_Bu2Dst0h_D0pi0_WN().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Delta_Bu2Dst0h_D0pi0_WN().getPropagatedError(
                         *result),
                     0)
              << "$ ";
      if (config.fitBuPartial() == true) {
        outfile << "& $"
                << to_string_with_precision(
                       p->buPartialEffBu2Dst0h_D0pi0_WN().getVal(), 3)
                << "$ &";
        outfile << "$"
                << to_string_with_precision(
                       p->N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN().getVal(), 0)
                << " \\pm "
                << to_string_with_precision(
                       p->N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN()
                           .getPropagatedError(*result),
                       0)
                << "$";
      }
      outfile << "\\\\ \\hline\n";
      outfile << "\t ";
      if (b == Bachelor::pi) {
        outfile << "\\cellcolor{green!35}"
                << ReturnLaTeXLabel(Mode::Bu2Dst0pi_D0gamma_WN, c, true);
      } else {
        outfile << "\\cellcolor{green!35}"
                << ReturnLaTeXLabel(Mode::Bu2Dst0K_D0gamma_WN, c, true);
      }
      outfile << " & ";
      outfile << "$"
              << to_string_with_precision(
                     p->orEffBu2Dst0h_D0gamma_WN().getVal(), 3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_Bu2Dst0h_D0gamma_WN().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Bu2Dst0h_D0gamma_WN().getPropagatedError(
                         *result),
                     0)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->buEffBu2Dst0h_D0gamma_WN().getVal(), 3)
              << "$ &";
      outfile << std::fixed << "$"
              << to_string_with_precision(
                     p->N_trueId_Bu_Bu2Dst0h_D0gamma_WN().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Bu_Bu2Dst0h_D0gamma_WN().getPropagatedError(
                         *result),
                     0)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->deltaEffBu2Dst0h_D0gamma_WN().getVal(), 3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_Delta_Bu2Dst0h_D0gamma_WN().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Delta_Bu2Dst0h_D0gamma_WN().getPropagatedError(
                         *result),
                     0)
              << "$ ";
      if (config.fitBuPartial() == true) {
        outfile << "& $"
                << to_string_with_precision(
                       p->buPartialEffBu2Dst0h_D0gamma_WN().getVal(), 3)
                << "$ &";
        outfile << "$"
                << to_string_with_precision(
                       p->N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN().getVal(), 0)
                << " \\pm "
                << to_string_with_precision(
                       p->N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN()
                           .getPropagatedError(*result),
                       0)
                << "$";
      }
      outfile << "\\\\ \\hline\n";
    } else {
      outfile << "\t ";
      if (b == Bachelor::pi) {
        outfile << "\\cellcolor{blue!25}"
                << ReturnLaTeXLabel(Mode::Bu2Dst0pi_WN, c, true);
      } else {
        outfile << "\\cellcolor{orange!50}"
                << ReturnLaTeXLabel(Mode::Bu2Dst0K_WN, c, true);
      }
      outfile << " & ";
      outfile << "$"
              << to_string_with_precision(p->orEffBu2Dst0h_WN().getVal(), 3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(p->N_trueId_Bu2Dst0h_WN().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Bu2Dst0h_WN().getPropagatedError(*result), 0)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(p->buEffBu2Dst0h_WN().getVal(), 3)
              << "$ &";
      outfile << std::fixed << "$"
              << to_string_with_precision(p->N_trueId_Bu_Bu2Dst0h_WN().getVal(),
                                          0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Bu_Bu2Dst0h_WN().getPropagatedError(*result),
                     0)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(p->deltaEffBu2Dst0h_WN().getVal(), 3)
              << "$ &";
      outfile
          << "$"
          << to_string_with_precision(p->N_trueId_Delta_Bu2Dst0h_WN().getVal(),
                                      0)
          << " \\pm "
          << to_string_with_precision(
                 p->N_trueId_Delta_Bu2Dst0h_WN().getPropagatedError(*result), 0)
          << "$ ";
      outfile << "\\\\ \\hline\n";
    }
    outfile << "\t ";
    if (b == Bachelor::pi) {
      outfile << "\\cellcolor{blue!25}"
              << ReturnLaTeXLabel(Mode::Bd2Dstpi, c, true);
    } else {
      outfile << "\\cellcolor{pink}"
              << ReturnLaTeXLabel(Mode::Bd2DstK, c, true);
    }
    outfile << " & ";
    outfile << "$" << to_string_with_precision(p->orEffBd2Dsth().getVal(), 3)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->N_trueId_Bd2Dsth().getVal(), 0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Bd2Dsth().getPropagatedError(*result), 0)
            << "$ &";
    outfile << "$" << to_string_with_precision(p->buEffBd2Dsth().getVal(), 3)
            << "$ &";
    outfile << std::fixed << "$"
            << to_string_with_precision(p->N_trueId_Bu_Bd2Dsth().getVal(), 0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Bu_Bd2Dsth().getPropagatedError(*result), 0)
            << "$ &";
    outfile << "$" << to_string_with_precision(p->deltaEffBd2Dsth().getVal(), 3)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->N_trueId_Delta_Bd2Dsth().getVal(), 0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Delta_Bd2Dsth().getPropagatedError(*result), 0)
            << "$ ";
    if (config.fitBuPartial() == true) {
      outfile << "& $"
              << to_string_with_precision(p->buPartialEffBd2Dsth().getVal(), 3)
              << "$ &";
      outfile
          << "$"
          << to_string_with_precision(p->N_trueId_BuPartial_Bd2Dsth().getVal(),
                                      0)
          << " \\pm "
          << to_string_with_precision(
                 p->N_trueId_BuPartial_Bd2Dsth().getPropagatedError(*result), 0)
          << "$";
    }
    outfile << "\\\\ \\hline\n";
    outfile << "\t ";
    outfile << "\t ";
    if (b == Bachelor::pi) {
      outfile << "\\cellcolor{green!35}"
              << ReturnLaTeXLabel(Mode::Bu2D0rho, c, true);
    } else {
      outfile << "\\cellcolor{orange!50}"
              << ReturnLaTeXLabel(Mode::Bu2D0Kst, c, true);
    }
    outfile << " & ";
    outfile << "$" << to_string_with_precision(p->orEffBu2D0hst().getVal(), 3)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->N_trueId_Bu2D0hst().getVal(), 0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Bu2D0hst().getPropagatedError(*result), 0)
            << "$ &";
    outfile << "$" << to_string_with_precision(p->buEffBu2D0hst().getVal(), 3)
            << "$ &";
    outfile << std::fixed << "$"
            << to_string_with_precision(p->N_trueId_Bu_Bu2D0hst().getVal(), 0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Bu_Bu2D0hst().getPropagatedError(*result), 0)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->deltaEffBu2D0hst().getVal(), 3)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->N_trueId_Delta_Bu2D0hst().getVal(),
                                        0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Delta_Bu2D0hst().getPropagatedError(*result), 0)
            << "$ ";
    if (config.fitBuPartial() == true) {
      outfile << "& $"
              << to_string_with_precision(p->buPartialEffBu2D0hst().getVal(), 3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_BuPartial_Bu2D0hst().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_BuPartial_Bu2D0hst().getPropagatedError(
                         *result),
                     0)
              << "$";
    }
    outfile << "\\\\ \\hline\n";
    if (b == Bachelor::pi) {
      outfile << "\\cellcolor{green!35}"
              << ReturnLaTeXLabel(Mode::Bu2Dst0rho, c, true);
    } else {
      outfile << "\\cellcolor{orange!50}"
              << ReturnLaTeXLabel(Mode::Bu2Dst0Kst, c, true);
    }
    outfile << " & ";
    outfile << "$" << to_string_with_precision(p->orEffBu2Dst0hst().getVal(), 3)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->N_trueId_Bu2Dst0hst().getVal(), 0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Bu2Dst0hst().getPropagatedError(*result), 0)
            << "$ &";
    outfile << "$" << to_string_with_precision(p->buEffBu2Dst0hst().getVal(), 3)
            << "$ &";
    outfile << std::fixed << "$"
            << to_string_with_precision(p->N_trueId_Bu_Bu2Dst0hst().getVal(), 0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Bu_Bu2Dst0hst().getPropagatedError(*result), 0)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->deltaEffBu2Dst0hst().getVal(), 3)
            << "$ &";
    outfile << "$"
            << to_string_with_precision(p->N_trueId_Delta_Bu2Dst0hst().getVal(),
                                        0)
            << " \\pm "
            << to_string_with_precision(
                   p->N_trueId_Delta_Bu2Dst0hst().getPropagatedError(*result),
                   0)
            << "$ ";
    if (config.fitBuPartial() == true) {
      outfile << "& $"
              << to_string_with_precision(p->buPartialEffBu2Dst0hst().getVal(),
                                          3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_BuPartial_Bu2Dst0hst().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_BuPartial_Bu2Dst0hst().getPropagatedError(
                         *result),
                     0)
              << "$";
    }
    outfile << "\\\\ \\hline\n";
    if (d == Daughters::kk) {
      outfile << "\t ";
      if (b == Bachelor::pi) {
        outfile << "\\cellcolor{blue!25}"
                << ReturnLaTeXLabel(Mode::Lb2Omegacpi_Lcpi0, c, true);
      } else {
        outfile << "\\cellcolor{pink}"
                << ReturnLaTeXLabel(Mode::Lb2OmegacK_Lcpi0, c, true);
      }
      outfile << " & ";
      outfile << "$"
              << to_string_with_precision(p->orEffLb2Omegach_Lcpi0().getVal(),
                                          3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_Lb2Omegach_Lcpi0().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Lb2Omegach_Lcpi0().getPropagatedError(*result),
                     0)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(p->buEffLb2Omegach_Lcpi0().getVal(),
                                          3)
              << "$ &";
      outfile << std::fixed << "$"
              << to_string_with_precision(
                     p->N_trueId_Bu_Lb2Omegach_Lcpi0().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Bu_Lb2Omegach_Lcpi0().getPropagatedError(
                         *result),
                     0)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->deltaEffLb2Omegach_Lcpi0().getVal(), 3)
              << "$ &";
      outfile << "$"
              << to_string_with_precision(
                     p->N_trueId_Delta_Lb2Omegach_Lcpi0().getVal(), 0)
              << " \\pm "
              << to_string_with_precision(
                     p->N_trueId_Delta_Lb2Omegach_Lcpi0().getPropagatedError(
                         *result),
                     0)
              << "$ ";
      if (config.fitBuPartial() == true) {
        outfile << "& $"
                << to_string_with_precision(
                       p->buPartialEffLb2Omegach_Lcpi0().getVal(), 3)
                << "$ &";
        outfile << "$"
                << to_string_with_precision(
                       p->N_trueId_BuPartial_Lb2Omegach_Lcpi0().getVal(), 0)
                << " \\pm "
                << to_string_with_precision(
                       p->N_trueId_BuPartial_Lb2Omegach_Lcpi0()
                           .getPropagatedError(*result),
                       0)
                << "$";
      }
      outfile << "\\\\ \\hline\n";
    }
    outfile << "\t\\end{tabular}\n";
    outfile << "}\n";
    std::string n_str = EnumToLabel(n);
    FormatLaTeX(n_str);
    std::string b_str = EnumToLabel(b);
    FormatLaTeX(b_str);
    std::string d_str = EnumToLabel(d, c);
    FormatLaTeX(d_str);
    std::string c_str = EnumToString(c);
    outfile << "\\caption{Correctly ID'd yields for category: Neutral " << n_str
            << ", Bachelor " << b_str << ", Daughters " << d_str << ", Charge "
            << c_str
            << ". Key: \\colorbox{blue!25}{Floating RRV}; "
               "\\colorbox{green!35}{Gaussian constrained RFV}; "
               "\\colorbox{orange!50}{RFV with floating ratio}; "
               "\\colorbox{pink}{RFV with fixed ratio}.}\n";
    outfile << "\\end{table}\n";
  }
  outfile << "\\end{document}\n";
}

std::map<std::string, Int_t> MakeColorMap(Configuration &config) {
  std::map<std::string, Int_t> colorMap;

  colorMap["Bu2Dst0h_D0gamma"] = TColor::GetColor("#abd9e9");
  colorMap["Bu2Dst0h_D0pi0"] = TColor::GetColor("#4575b4");
  if (config.simpleFit() == false) {
    colorMap["Bu2Dst0h_D0gamma_WN"] = TColor::GetColor("#BDDA8B");
    colorMap["Bu2Dst0h_D0pi0_WN"] = TColor::GetColor("#009e73");
    colorMap["Bu2Dst0h_WN"] = TColor::GetColor("#009e73");
    colorMap["Bd2Dsth"] = TColor::GetColor("#a50026");
    colorMap["Bu2D0hst"] = TColor::GetColor("#fdae61");
  } else {
    colorMap["Bu2Dst0h_D0gamma_WN"] = TColor::GetColor("#a50026");
    colorMap["Bu2Dst0h_D0pi0_WN"] = TColor::GetColor("#a50026");
    colorMap["Bu2Dst0h_WN"] = TColor::GetColor("#a50026");
    colorMap["Bd2Dsth"] = TColor::GetColor("#a50026");
    colorMap["Bu2D0hst"] = TColor::GetColor("#a50026");
  }
  colorMap["Bu2Dst0hst"] = TColor::GetColor("#f46d43");
  colorMap["Lb2Omegach_Lcpi0"] = TColor::GetColor("#e0f3f8");
  colorMap["Bs2Dst0Kst0"] = TColor::GetColor("#ffffbf");
  colorMap["Bs2D0Kst0"] = TColor::GetColor("#fee090");
  colorMap["MisID"] = TColor::GetColor("#cccccc");
  colorMap["misId_Bu2Dst0h_D0gamma"] = TColor::GetColor("#cccccc");
  colorMap["misId_Bu2Dst0h_D0pi0"] = TColor::GetColor("#cccccc");
  colorMap["misId_Bu2Dst0h_D0gamma_WN"] = TColor::GetColor("#cccccc");
  colorMap["misId_Bu2Dst0h_D0pi0_WN"] = TColor::GetColor("#cccccc");
  colorMap["misId_Bu2Dst0h_WN"] = TColor::GetColor("#cccccc");
  colorMap["misId_Bd2Dsth"] = TColor::GetColor("#cccccc");
  colorMap["misId_Bu2D0hst"] = TColor::GetColor("#cccccc");
  colorMap["misId_Bu2Dst0hst"] = TColor::GetColor("#cccccc");
  colorMap["Crossfeed"] = TColor::GetColor("#474642");
  colorMap["Bu2Dst0h_D0pi0_D02pik"] = TColor::GetColor("#474642");
  colorMap["Bu2Dst0h_D0gamma_D02pik"] = TColor::GetColor("#474642");
  colorMap["Bu2Dst0h_D0pi0_WN_D02pik"] = TColor::GetColor("#474642");
  colorMap["Bu2Dst0h_D0gamma_WN_D02pik"] = TColor::GetColor("#474642");
  colorMap["comb"] = TColor::GetColor("#5c5c6a");

  return colorMap;
}

void PlotLegend(Configuration &config, std::map<std::string, Int_t> &colorMap,
                std::string const &outputDir) {
  SetStyle();
  // ------------- Draw Legends -------------- //

  TLegend labels(0, 0, 1, 1);

  // TLegend labels(0.14, 0.3, 0.28, 0.9);
  // if (config.runADS() == true && bachelor == Bachelor::k) {
  //   labels.SetY1(0.2);
  // }
  // if (config.simpleFit() == true) {
  //   if (config.runADS() == true && bachelor == Bachelor::k) {
  //     labels.SetY1(0.4);
  //   } else {
  //     labels.SetY1(0.5);
  //   }
  // }
  labels.SetLineColor(kWhite);

  std::string oppCharge = "#mp";
  // if (charge == Charge::plus) {
  //   oppCharge = "-";
  // } else if (charge == Charge::minus) {
  //   oppCharge = "+";
  // } else {
  //   oppCharge = "#mp";
  // }

  auto hist_Bu2Dst0h_D0gamma = std::make_unique<TH1D>(
      "hist_Bu2Dst0h_D0gamma", "hist_Bu2Dst0h_D0gamma", 1, 0, 1);
  hist_Bu2Dst0h_D0gamma->SetLineColor(colorMap["Bu2Dst0h_D0gamma"]);
  hist_Bu2Dst0h_D0gamma->SetLineWidth(20);

  auto hist_Bu2Dst0h_D0pi0 = std::make_unique<TH1D>(
      "hist_Bu2Dst0h_D0pi0", "hist_Bu2Dst0h_D0pi0", 1, 0, 1);
  hist_Bu2Dst0h_D0pi0->SetLineColor(colorMap["Bu2Dst0h_D0pi0"]);
  hist_Bu2Dst0h_D0pi0->SetLineWidth(20);

  auto hist_Bu2Dst0h_D0gamma_WN = std::make_unique<TH1D>(
      "hist_Bu2Dst0h_D0gamma_WN", "hist_Bu2Dst0h_D0gamma_WN", 1, 0, 1);
  hist_Bu2Dst0h_D0gamma_WN->SetLineColor(colorMap["Bu2Dst0h_D0gamma_WN"]);
  hist_Bu2Dst0h_D0gamma_WN->SetLineWidth(20);

  auto hist_Bu2Dst0h_D0pi0_WN = std::make_unique<TH1D>(
      "hist_Bu2Dst0h_D0pi0_WN", "hist_Bu2Dst0h_D0pi0_WN", 1, 0, 1);
  hist_Bu2Dst0h_D0pi0_WN->SetLineColor(colorMap["Bu2Dst0h_D0pi0_WN"]);
  hist_Bu2Dst0h_D0pi0_WN->SetLineWidth(20);

  auto hist_Bu2Dst0h_WN =
      std::make_unique<TH1D>("hist_Bu2Dst0h_WN", "hist_Bu2Dst0h_WN", 1, 0, 1);
  hist_Bu2Dst0h_WN->SetLineColor(colorMap["Bu2Dst0h_WN"]);
  hist_Bu2Dst0h_WN->SetLineWidth(20);

  auto hist_Bu2D0hst =
      std::make_unique<TH1D>("hist_Bu2D0hst", "hist_Bu2D0hst", 1, 0, 1);
  hist_Bu2D0hst->SetLineColor(colorMap["Bu2D0hst"]);
  hist_Bu2D0hst->SetLineWidth(20);

  auto hist_Bd2Dsth =
      std::make_unique<TH1D>("hist_Bd2Dsth", "hist_Bd2Dsth", 1, 0, 1);
  hist_Bd2Dsth->SetLineColor(colorMap["Bd2Dsth"]);
  hist_Bd2Dsth->SetLineWidth(20);

  auto hist_Bu2Dst0hst =
      std::make_unique<TH1D>("hist_Bu2Dst0hst", "hist_Bu2Dst0hst", 1, 0, 1);
  hist_Bu2Dst0hst->SetLineColor(colorMap["Bu2Dst0hst"]);
  hist_Bu2Dst0hst->SetLineWidth(20);

  auto hist_Lb2Omegach_Lcpi0 = std::make_unique<TH1D>(
      "hist_Lb2Omegach_Lcpi0", "hist_Lb2Omegach_Lcpi0", 1, 0, 1);
  hist_Lb2Omegach_Lcpi0->SetLineColor(colorMap["Lb2Omegach_Lcpi0"]);
  hist_Lb2Omegach_Lcpi0->SetLineWidth(20);

  auto hist_Bs2D0Kst0 =
      std::make_unique<TH1D>("hist_Bs2D0Kst0", "hist_Bs2D0Kst0", 1, 0, 1);
  hist_Bs2D0Kst0->SetLineColor(colorMap["Bs2D0Kst0"]);
  hist_Bs2D0Kst0->SetLineWidth(20);

  auto hist_Bs2Dst0Kst0 =
      std::make_unique<TH1D>("hist_Bs2Dst0Kst0", "hist_Bs2Dst0Kst0", 1, 0, 1);
  hist_Bs2Dst0Kst0->SetLineColor(colorMap["Bs2Dst0Kst0"]);
  hist_Bs2Dst0Kst0->SetLineWidth(20);

  auto hist_MisID = std::make_unique<TH1D>("hist_MisID", "hist_MisID", 1, 0, 1);
  hist_MisID->SetLineColor(colorMap["MisID"]);
  hist_MisID->SetLineWidth(20);

  auto hist_D02pik =
      std::make_unique<TH1D>("hist_D02pik", "hist_D02pik", 1, 0, 1);
  hist_D02pik->SetLineColor(colorMap["Crossfeed"]);
  hist_D02pik->SetLineWidth(20);

  auto hist_comb = std::make_unique<TH1D>("hist_comb", "hist_comb", 1, 0, 1);
  hist_comb->SetLineColor(colorMap["comb"]);
  hist_comb->SetLineWidth(20);

  labels.AddEntry(
      hist_Bu2Dst0h_D0pi0.get(),
      ReturnLaTeXLabel(Mode::Bu2Dst0h_D0pi0, Charge::total, false).c_str(),
      "l");
  // " ", "l");
  // if (config.neutral() == Neutral::gamma) {
  labels.AddEntry(
      hist_Bu2Dst0h_D0gamma.get(),
      ReturnLaTeXLabel(Mode::Bu2Dst0h_D0gamma, Charge::total, false).c_str(),
      "l");
  // " ", "l");
  // }
  if (config.simpleFit() == false) {
    // if (config.neutral() == Neutral::gamma) {
    labels.AddEntry(
        hist_Bu2Dst0h_D0pi0_WN.get(),
        ReturnLaTeXLabel(Mode::Bu2Dst0h_D0pi0_WN, Charge::total, false).c_str(),
        "l");
    // " ", "l");
    labels.AddEntry(
        hist_Bu2Dst0h_D0gamma_WN.get(),
        ReturnLaTeXLabel(Mode::Bu2Dst0h_D0gamma_WN, Charge::total, false)
            .c_str(),
        "l");
    // " ", "l");
    // } else {
    //   labels.AddEntry(
    //       hist_Bu2Dst0h_WN.get(),
    //       ReturnLaTeXLabel(Mode::Bu2Dst0h_WN,
    //       Charge::total, false)
    //           .c_str(),
    //       "l");
    // }
    labels.AddEntry(
        hist_Bu2D0hst.get(),
        // " ", "l");
        ReturnLaTeXLabel(Mode::Bu2D0hst, Charge::total, false).c_str(), "l");
    labels.AddEntry(
        hist_Bd2Dsth.get(),
        ReturnLaTeXLabel(Mode::Bd2Dsth, Charge::total, false).c_str(), "l");
    // " ", "l");
  } else {
    labels.AddEntry(hist_Bu2Dst0h_WN.get(), "Mis-Reconstructed", "l");
  }
  labels.AddEntry(
      hist_Bu2Dst0hst.get(),
      ReturnLaTeXLabel(Mode::Bu2Dst0hst, Charge::total, false).c_str(), "l");
  // " ", "l");
  labels.AddEntry(
      hist_Lb2Omegach_Lcpi0.get(),
      ReturnLaTeXLabel(Mode::Lb2Omegach_Lcpi0, Charge::total, false).c_str(),
      "l");
  // " ", "l");
  // if (config.runADS() == true) {
  labels.AddEntry(
      hist_Bs2Dst0Kst0.get(),
      ReturnLaTeXLabel(Mode::Bs2Dst0Kst0, Charge::total, false).c_str(), "l");
  // " ", "l");
  labels.AddEntry(
      hist_Bs2D0Kst0.get(),
      ReturnLaTeXLabel(Mode::Bs2D0Kst0, Charge::total, false).c_str(), "l");
  // " ", "l");
  labels.AddEntry(hist_D02pik.get(), "Crossfeed", "l");
  // labels.AddEntry(hist_D02pik.get(), " ", "l");
  // }
  labels.AddEntry(hist_MisID.get(), "Mis-ID", "l");
  // labels.AddEntry(hist_MisID.get(), " ", "l");
  // if (config.runCombSystematic() == true) {
  labels.AddEntry(hist_comb.get(), "Combinatorial", "l");
  // }

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
          // entry->SetTextColor(kWhite);
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
  TCanvas canvas("LegendCanvas", "", 80, 150);
  TH1D tmpHist("", "", 1, 0, 1);
  // tmpHist.Draw();
  labels.Draw();
  canvas.SaveAs(
      (outputDir + "/plots/legend_" + EnumToString(config.neutral()) + ".pdf")
          .c_str());
}

// Plot projections
void Plotting1D(int const id, PdfBase &pdf, Configuration &config,
                RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                std::map<std::string, Int_t> &colorMap,
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

  TLegend legend(0.71, 0.75, 0.89, 0.85);

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
        entry1->SetTextSize(0.04);
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
        entry2->SetTextSize(0.05);
      } else {
        throw std::runtime_error(
            "Could not cast entry2 from TObject to TLegendEntry.");
      }
    } else {
      throw std::runtime_error(
          "Could not extract entryObj2 from list in TLegend.");
    }
  }

  PlotComponent(Mass::buDelta, config.buDeltaMass(), pdf, fullDataSet, simPdf,
                legend, outputDir, config, colorMap, yMaxMap);
  if (config.fitBuPartial() == true) {
    PlotComponent(Mass::buDeltaPartial, config.buDeltaMass(), pdf, fullDataSet,
                  simPdf, legend, outputDir, config, colorMap, yMaxMap);
  }
  if (config.fit1D() == false) {
    PlotComponent(Mass::delta, config.deltaMass(), pdf, fullDataSet, simPdf,
                  legend, outputDir, config, colorMap, yMaxMap);
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

// Function to plot 1D projections - written so that it can be used for both
// bu and delta mass
void PlotComponent(Mass mass, RooRealVar &var, PdfBase &pdf,
                   RooAbsData const &fullDataSet, RooSimultaneous const &simPdf,
                   TLegend &legend, std::string const &outputDir,
                   Configuration &config,
                   std::map<std::string, Int_t> &colorMap,
                   std::map<Neutral, std::map<Mass, double> > &yMaxMap) {
  Bachelor bachelor = pdf.bachelor();
  Daughters daughters = pdf.daughters();
  Neutral neutral = pdf.neutral();
  Charge charge = pdf.charge();
  int id = 0;

  // double initBin;
  // if (daughters == Daughters::pik) {
  //   // initBin = config.buDeltaMass().GetBins();
  //   if (config.neutral() == Neutral::pi0) {
  //     config.buDeltaMass().setBins(32);
  //     config.deltaMass().setBins(36);
  //   } else {
  //     config.buDeltaMass().setBins(36);
  //     config.deltaMass().setBins(52);
  //   }
  // }

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
                  RooFit::LineColor(kBlack));
    }

    // Everything to be plotted has to be declared outside of a loop, in the
    // scope of the canvas
    RooHist *pullHist = nullptr;
    std::unique_ptr<RooPlot> pullFrame(var.frame(RooFit::Title(" ")));

    pullHist = frame->RooPlot::pullHist();
    pullFrame->SetTitle("");
    pullFrame->SetXTitle(" ");
    pullFrame->GetYaxis()->SetTitle("Residual (#sigma)");
    pullFrame->GetYaxis()->CenterTitle();
    pullFrame->SetLabelFont(132, "XY");
    pullFrame->SetTitleFont(132, "XY");
    pullFrame->SetTitleSize(0.20, "Y");
    pullFrame->SetTitleOffset(0.28, "Y");
    pullFrame->SetLabelSize(0.18, "XY");
    pullFrame->SetLabelOffset(0.02, "Y");
    pullFrame->SetLabelOffset(50, "X");
    pullFrame->GetYaxis()->SetNdivisions(6);

    if (config.noFit() == false) {
      std::vector<const char *> pdfCharVec;
      // Need to add in list of components here rather than just using functions
      // RooArgList as need specific order
      if (mass == Mass::buDelta) {
        if (neutral == Neutral::pi0) {
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0().GetName());
          if (config.runADS() == true && bachelor == Bachelor::k &&
              daughters != Daughters::kpi) {
            pdfCharVec.emplace_back(pdf.pdfBu_Bs2Dst0Kst0().GetName());
            pdfCharVec.emplace_back(pdf.pdfBu_Bs2D0Kst0().GetName());
          }
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0gamma_WN().GetName());
          // pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_Bd2Dsth().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2D0hst().GetName());
          if (daughters == Daughters::kk) {
            pdfCharVec.emplace_back(pdf.pdfBu_Lb2Omegach_Lcpi0().GetName());
          }
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName());
          pdfCharVec.emplace_back(
              pdf.pdfBu_misId_Bu2Dst0h_D0pi0_WN().GetName());
          // pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0h_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2D0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bd2Dsth().GetName());
          if (bachelor == Bachelor::k) {
            pdfCharVec.emplace_back(
                pdf.pdfBu_misId_Bu2Dst0h_D0gamma_WN().GetName());
            pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0hst().GetName());
          }
          if (daughters == Daughters::pik) {
            pdfCharVec.emplace_back(
                pdf.pdfBu_Bu2Dst0h_D0pi0_D02pik().GetName());
            // pdfCharVec.emplace_back(
            //     pdf.pdfBu_Bu2Dst0h_D0pi0_WN_D02pik().GetName());
          }
          // if (config.runCombSystematic() == true) {
          pdfCharVec.emplace_back(pdf.pdfBu_comb().GetName());
          // }
        } else {
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0gamma().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0().GetName());
          if (config.runADS() == true && bachelor == Bachelor::k &&
              daughters != Daughters::kpi) {
            pdfCharVec.emplace_back(pdf.pdfBu_Bs2Dst0Kst0().GetName());
            pdfCharVec.emplace_back(pdf.pdfBu_Bs2D0Kst0().GetName());
          }
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0gamma_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_Bd2Dsth().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2D0hst().GetName());
          if (daughters == Daughters::kk) {
            pdfCharVec.emplace_back(pdf.pdfBu_Lb2Omegach_Lcpi0().GetName());
          }
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_Bu2Dst0h_D0pi0().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0h_D0gamma().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0h_D0pi0().GetName());
          pdfCharVec.emplace_back(
              pdf.pdfBu_misId_Bu2Dst0h_D0pi0_WN().GetName());
          pdfCharVec.emplace_back(
              pdf.pdfBu_misId_Bu2Dst0h_D0gamma_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2D0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfBu_misId_Bd2Dsth().GetName());
          if (bachelor == Bachelor::k) {
            pdfCharVec.emplace_back(pdf.pdfBu_misId_Bu2Dst0hst().GetName());
          }
          if (daughters == Daughters::pik) {
            pdfCharVec.emplace_back(
                pdf.pdfBu_Bu2Dst0h_D0pi0_D02pik().GetName());
            pdfCharVec.emplace_back(
                pdf.pdfBu_Bu2Dst0h_D0gamma_D02pik().GetName());
            // pdfCharVec.emplace_back(
            //     pdf.pdfBu_Bu2Dst0h_D0pi0_WN_D02pik().GetName());
            // pdfCharVec.emplace_back(
            //     pdf.pdfBu_Bu2Dst0h_D0gamma_WN_D02pik().GetName());
          }
          // if (config.runCombSystematic() == true) {
          pdfCharVec.emplace_back(pdf.pdfBu_comb().GetName());
          // }
        }
      } else if (mass == Mass::delta) {
        if (neutral == Neutral::pi0) {
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName());
          if (config.runADS() == true && bachelor == Bachelor::k &&
              daughters != Daughters::kpi) {
            pdfCharVec.emplace_back(pdf.pdfDelta_Bs2Dst0Kst0().GetName());
            pdfCharVec.emplace_back(pdf.pdfDelta_Bs2D0Kst0().GetName());
          }
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0pi0_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0gamma_WN().GetName());
          // pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_Bd2Dsth().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2D0hst().GetName());
          if (daughters == Daughters::kk) {
            pdfCharVec.emplace_back(pdf.pdfDelta_Lb2Omegach_Lcpi0().GetName());
          }
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0hst().GetName());
          pdfCharVec.emplace_back(
              pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName());
          pdfCharVec.emplace_back(
              pdf.pdfDelta_misId_Bu2Dst0h_D0pi0_WN().GetName());
          // pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2Dst0h_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2D0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bd2Dsth().GetName());
          if (bachelor == Bachelor::k) {
            pdfCharVec.emplace_back(
                pdf.pdfDelta_misId_Bu2Dst0h_D0gamma_WN().GetName());
            pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2Dst0hst().GetName());
          }
          if (daughters == Daughters::pik) {
            pdfCharVec.emplace_back(
                pdf.pdfDelta_Bu2Dst0h_D0pi0_D02pik().GetName());
            // pdfCharVec.emplace_back(
            //     pdf.pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik().GetName());
          }
          // if (config.runCombSystematic() == true) {
          pdfCharVec.emplace_back(pdf.pdfDelta_comb().GetName());
          // }
        } else {
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0gamma().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0pi0().GetName());
          if (config.runADS() == true && bachelor == Bachelor::k &&
              daughters != Daughters::kpi) {
            pdfCharVec.emplace_back(pdf.pdfDelta_Bs2Dst0Kst0().GetName());
            pdfCharVec.emplace_back(pdf.pdfDelta_Bs2D0Kst0().GetName());
          }
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0pi0_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0h_D0gamma_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_Bd2Dsth().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2D0hst().GetName());
          if (daughters == Daughters::kk) {
            pdfCharVec.emplace_back(pdf.pdfDelta_Lb2Omegach_Lcpi0().GetName());
          }
          pdfCharVec.emplace_back(pdf.pdfDelta_Bu2Dst0hst().GetName());
          pdfCharVec.emplace_back(
              pdf.pdfDelta_misId_Bu2Dst0h_D0gamma().GetName());
          pdfCharVec.emplace_back(
              pdf.pdfDelta_misId_Bu2Dst0h_D0pi0().GetName());
          pdfCharVec.emplace_back(
              pdf.pdfDelta_misId_Bu2Dst0h_D0pi0_WN().GetName());
          pdfCharVec.emplace_back(
              pdf.pdfDelta_misId_Bu2Dst0h_D0gamma_WN().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2D0hst().GetName());
          pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bd2Dsth().GetName());
          if (bachelor == Bachelor::k) {
            pdfCharVec.emplace_back(pdf.pdfDelta_misId_Bu2Dst0hst().GetName());
          }
          if (daughters == Daughters::pik) {
            pdfCharVec.emplace_back(
                pdf.pdfDelta_Bu2Dst0h_D0pi0_D02pik().GetName());
            pdfCharVec.emplace_back(
                pdf.pdfDelta_Bu2Dst0h_D0gamma_D02pik().GetName());
            // pdfCharVec.emplace_back(
            //     pdf.pdfDelta_Bu2Dst0h_D0pi0_WN_D02pik().GetName());
            // pdfCharVec.emplace_back(
            //     pdf.pdfDelta_Bu2Dst0h_D0gamma_WN_D02pik().GetName());
          }
          // if (config.runCombSystematic() == true) {
          pdfCharVec.emplace_back(pdf.pdfDelta_comb().GetName());
          // }
        }
      } else {
        pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2Dst0h_D0gamma().GetName());
        pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2Dst0h_D0pi0().GetName());
        if (config.runADS() == true && bachelor == Bachelor::k &&
            daughters != Daughters::kpi) {
          pdfCharVec.emplace_back(pdf.pdfBuPartial_Bs2Dst0Kst0().GetName());
          pdfCharVec.emplace_back(pdf.pdfBuPartial_Bs2D0Kst0().GetName());
        }
        pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2Dst0h_D0pi0_WN().GetName());
        pdfCharVec.emplace_back(
            pdf.pdfBuPartial_Bu2Dst0h_D0gamma_WN().GetName());
        pdfCharVec.emplace_back(pdf.pdfBuPartial_Bd2Dsth().GetName());
        pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2D0hst().GetName());
        if (daughters == Daughters::kk) {
          pdfCharVec.emplace_back(
              pdf.pdfBuPartial_Lb2Omegach_Lcpi0().GetName());
        }
        pdfCharVec.emplace_back(pdf.pdfBuPartial_Bu2Dst0hst().GetName());
        pdfCharVec.emplace_back(
            pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0().GetName());
        pdfCharVec.emplace_back(
            pdf.pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN().GetName());
        pdfCharVec.emplace_back(
            pdf.pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN().GetName());
        pdfCharVec.emplace_back(pdf.pdfBuPartial_misId_Bu2D0hst().GetName());
        pdfCharVec.emplace_back(pdf.pdfBuPartial_misId_Bd2Dsth().GetName());
        if (bachelor == Bachelor::k) {
          pdfCharVec.emplace_back(
              pdf.pdfBuPartial_misId_Bu2Dst0hst().GetName());
        }
        if (daughters == Daughters::pik) {
          pdfCharVec.emplace_back(
              pdf.pdfBuPartial_Bu2Dst0h_D0pi0_D02pik().GetName());
          // pdfCharVec.emplace_back(
          //     pdf.pdfBuPartial_Bu2Dst0h_D0pi0_WN_D02pik().GetName());
        }
        // if (config.runCombSystematic() == true) {
        pdfCharVec.emplace_back(pdf.pdfBuPartial_comb().GetName());
        // }
      }
      // To pass to Components in plotOn, need string in the format
      // "pdf1,pdf2,pdf3"
      while (pdfCharVec.size() > 0) {
        std::string totPdfStr = "";
        for (auto &chars : pdfCharVec) {
          totPdfStr.append(chars);
          totPdfStr.append(",");
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
          std::cout << modeStr << "\n";
        } else {
          throw std::runtime_error(
              "Plotting.cpp: Can't find decay mode in pdfString with regex: " +
              pdfStr + "\n");
        }
        std::cout << modeStr << "\n\n\n";
        simPdf.plotOn(
            frame.get(),
            RooFit::Slice(
                config.fitting,
                ComposeFittingName(mass, neutral, bachelor, daughters, charge)
                    .c_str()),
            RooFit::ProjWData(config.fitting, fullDataSet),
            RooFit::Components(totPdfStr.c_str()), RooFit::DrawOption("F"),
            RooFit::FillColor(colorMap[modeStr.c_str()]),
            RooFit::Precision(1e-3), RooFit::NumCPU(config.nCPU()));
        // Remove first pdf string in vector: plot all others w/out this w/ new
        // color
        pdfCharVec.erase(pdfCharVec.begin());
        // continue until no PDFs left
      }
      simPdf.plotOn(frame.get(),
                    RooFit::Slice(config.fitting,
                                  ComposeFittingName(mass, neutral, bachelor,
                                                     daughters, charge)
                                      .c_str()),
                    RooFit::ProjWData(config.fitting, fullDataSet),
                    RooFit::LineColor(kBlack));
    }

    fullDataSet.plotOn(frame.get(),
                       RooFit::Cut(("fitting==fitting::" +
                                    ComposeFittingName(mass, neutral, bachelor,
                                                       daughters, charge))
                                       .c_str()));

    if (mass == Mass::delta) {
      if (config.neutral() == Neutral::gamma) {
        frame->SetXTitle("m(D^{*0}) - m(D^{0}) (MeV/c^{2})");
      } else {
        frame->SetXTitle(
            "m(D^{*0}) - m(D^{0}) - m(#pi^{0}) + m(#pi^{0})_{PDG} (MeV/c^{2})");
      }
    } else {
      frame->SetXTitle("m(D^{*0}h) (MeV/c^{2})");
    }

    // --------------- plot onto canvas ---------------------

    TCanvas canvas(("canvas_" +
                    ComposeName(id, mass, neutral, bachelor, daughters, charge))
                       .c_str(),
                   "canvas", 1200, 1000);

    TPad pad1(
        ("pad1_" + ComposeName(id, mass, neutral, bachelor, daughters, charge))
            .c_str(),
        "pad1", 0.0, 0.2, 1.0, 1.0, kWhite);
    pad1.Draw();

    TPad pad2(
        ("pad2_" + ComposeName(id, mass, neutral, bachelor, daughters, charge))
            .c_str(),
        "pad2", 0.0, 0.0, 1.0, 0.2, kWhite);
    pad2.Draw();

    TLine zeroLine(var.getMin(), 0, var.getMax(), 0);
    zeroLine.SetLineColor(kGray + 2);
    zeroLine.SetLineStyle(kDashed);
    TLine upLine(var.getMin(), 3, var.getMax(), 3);
    upLine.SetLineColor(kRed + 2);
    TLine downLine(var.getMin(), -3, var.getMax(), -3);
    downLine.SetLineColor(kRed + 2);

    if (config.noFit() == false) {
      canvas.cd();
      pad2.cd();
      pullFrame->addPlotable(pullHist /* .get() */, "P");
      pullFrame->SetName(
          ("pullFrame_" +
           ComposeName(id, mass, neutral, bachelor, daughters, charge))
              .c_str());
      pullFrame->GetYaxis()->SetRangeUser(-5, 5);
      pullFrame->Draw();
      zeroLine.Draw("same");
      upLine.Draw("same");
      downLine.Draw("same");
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

    frame->SetMinimum(0.001);
    if (daughters == Daughters::pik && config.blindFit() == true) {
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

    // if (mass == Mass::buDelta && daughters == Daughters::kpi) {
    //   labels.Draw("same");
    // }
    // Stores max values for kpi, to set in pik
    if (daughters == Daughters::kpi && bachelor == Bachelor::pi) {
      yMaxMap[neutral][mass] = frame->GetMaximum();
    }

    canvas.Update();
    canvas.SaveAs((outputDir + "/plots/" +
                   ComposeName(id, mass, neutral, bachelor, daughters, charge) +
                   "_" + config.ReturnBoxString() + ".pdf")
                      .c_str());

    // if (daughters == Daughters::pik) {
    //   // config.buDeltaMass().setBins(initBin);
    //   if (config.neutral() == Neutral::pi0) {
    //     config.buDeltaMass().setBins(40);
    //     config.deltaMass().setBins(54);
    //   } else {
    //     config.buDeltaMass().setBins(45);
    //   config.deltaMass().setBins(65);
    //   }
    // }
}
