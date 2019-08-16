#include "GlobalVars.h"
#include "NeutralVars.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::gamma>::NeutralVars(int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_meanDelta_(("Bu2Dst0h_Dst02D0gamma_meanDelta_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       "", 1.4233e+02, 135, 150),
      Bu2Dst0h_Dst02D0gamma_sigmaDelta_(("Bu2Dst0h_Dst02D0gamma_sigmaDelta_" +
                                         ComposeName(uniqueId, Neutral::gamma))
                                            .c_str(),
                                        "", 8.1675e+00, 2, 15),
      Bu2Dst0h_Dst02D0gamma_a1Delta_(("Bu2Dst0h_Dst02D0gamma_a1Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     "", 1.5109e+00),
      Bu2Dst0h_Dst02D0gamma_a2Delta_(("Bu2Dst0h_Dst02D0gamma_a2Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     "", -5.7023e-01),
      Bu2Dst0h_Dst02D0gamma_n1Delta_(("Bu2Dst0h_Dst02D0gamma_n1Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     "", 6.0060e+00),
      Bu2Dst0h_Dst02D0gamma_n2Delta_(("Bu2Dst0h_Dst02D0gamma_n2Delta_" +
                                      ComposeName(uniqueId, Neutral::gamma))
                                         .c_str(),
                                     "", 7.8408e+00),
      pdf1Delta_Bu2Dst0h_Dst02D0gamma_(("pdf1Delta_Bu2Dst0h_Dst02D0gamma_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       Bu2Dst0h_Dst02D0gamma_meanDelta_,
                                       Bu2Dst0h_Dst02D0gamma_sigmaDelta_,
                                       Bu2Dst0h_Dst02D0gamma_a1Delta_,
                                       Bu2Dst0h_Dst02D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_Dst02D0gamma_(("pdf2Delta_Bu2Dst0h_Dst02D0gamma_" +
                                        ComposeName(uniqueId, Neutral::gamma))
                                           .c_str(),
                                       "", Configuration::Get().deltaMass(),
                                       Bu2Dst0h_Dst02D0gamma_meanDelta_,
                                       Bu2Dst0h_Dst02D0gamma_sigmaDelta_,
                                       Bu2Dst0h_Dst02D0gamma_a2Delta_,
                                       Bu2Dst0h_Dst02D0gamma_n2Delta_),
      Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_(
          ("Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 2.6638e-01),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(
          ("pdfDelta_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", RooArgList(pdf1Delta_Bu2Dst0h_Dst02D0gamma_,
                         pdf2Delta_Bu2Dst0h_Dst02D0gamma_),
          Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_),
      Bu2Dst0h_Dst02D0gamma_meanBu_(("Bu2Dst0h_Dst02D0gamma_meanBu_" +
                                     ComposeName(uniqueId, Neutral::gamma))
                                        .c_str(),
                                    "", 5.2819e+03, 5270, 5290),
      relativeBuWidth_Bu2Dst0h_Dst02D0gamma_(
          ("relativeBuWidth_Bu2Dst0h_Dst02D0gammaBu_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 0.95),
      Bu2Dst0h_Dst02D0gamma_a1Bu_(("Bu2Dst0h_Dst02D0gamma_a1Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", 1.6184e+00),
      Bu2Dst0h_Dst02D0gamma_a2Bu_(("Bu2Dst0h_Dst02D0gamma_a2Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", -1.6623e+00),
      Bu2Dst0h_Dst02D0gamma_n1Bu_(("Bu2Dst0h_Dst02D0gamma_n1Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", 8.6469e+00),
      Bu2Dst0h_Dst02D0gamma_n2Bu_(("Bu2Dst0h_Dst02D0gamma_n2Bu_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", 5.2563e+00),
      Bu2Dst0h_Dst02D0gamma_frac1PdfBu_(("Bu2Dst0h_Dst02D0gamma_frac1PdfBu_" +
                                         ComposeName(uniqueId, Neutral::gamma))
                                            .c_str(),
                                        "", 6.8457e-01),
      ratioKpi_Bu2Dst0h_Dst02D0gamma_(("ratioKpi_Bu2Dst0h_Dst02D0gamma_" +
                                       ComposeName(uniqueId, Neutral::gamma))
                                          .c_str(),
                                      "", 0.07930, -1, 1),
      orEffBu2Dst0pi_Dst02D0gamma_(("orEffBu2Dst0pi_Dst02D0gamma_" +
                                   ComposeName(uniqueId, Neutral::gamma))
                                      .c_str(),
                                  "", 1),
      boxEffBu2Dst0pi_Dst02D0gamma_(("boxEffBu2Dst0pi_Dst02D0gamma_" +
                                    ComposeName(uniqueId, Neutral::gamma))
                                       .c_str(),
                                   "", 1),
      buDeltaCutEffBu2Dst0pi_Dst02D0gamma_(
          ("buDeltaCutEffBu2Dst0pi_Dst02D0gamma_" +
           ComposeName(uniqueId, Neutral::gamma))
              .c_str(),
          "", 1),
      deltaCutEffBu2Dst0pi_Dst02D0gamma_(("deltaCutEffBu2Dst0pi_Dst02D0gamma_" +
                                         ComposeName(uniqueId, Neutral::gamma))
                                            .c_str(),
                                        "", 1),
      initYieldFAVSignal_(5.1958e+04) {
  SetEfficiencies(Mode::Bu2Dst0pi_D0gamma, orEffBu2Dst0pi_Dst02D0gamma_,
                  boxEffBu2Dst0pi_Dst02D0gamma_,
                  buDeltaCutEffBu2Dst0pi_Dst02D0gamma_,
                  deltaCutEffBu2Dst0pi_Dst02D0gamma_);
}
