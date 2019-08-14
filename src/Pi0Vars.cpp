#include "GlobalVars.h"
#include "NeutralVars.h"

// Neutral specialisations
// Constructor followed by : ... { is an initialisation list, can also but in
// body of constructor (except for RooFit as RooFit uses singleton classes,
// unless we use pointers
template <>
NeutralVars<Neutral::pi0>::NeutralVars(int uniqueId)
    // -------------------- SIGNAL -------------------- //
    : Bu2Dst0h_Dst02D0gamma_meanDelta_(
          ("Bu2Dst0h_Dst02D0gamma_mean_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "", 1.4233e+02),
      Bu2Dst0h_Dst02D0gamma_sigmaDelta_(
          ("Bu2Dst0h_Dst02D0gamma_sigma_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "", 8.1675e+00),
      Bu2Dst0h_Dst02D0gamma_a1Delta_(
          ("Bu2Dst0h_Dst02D0gamma_a1_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "", 1.5109e+00),
      Bu2Dst0h_Dst02D0gamma_a2Delta_(
          ("Bu2Dst0h_Dst02D0gamma_a2_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "", -5.7023e-01),
      Bu2Dst0h_Dst02D0gamma_n1Delta_(
          ("Bu2Dst0h_Dst02D0gamma_n1_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "", 6.0060e+00),
      Bu2Dst0h_Dst02D0gamma_n2Delta_(
          ("Bu2Dst0h_Dst02D0gamma_n2_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "", 7.8408e+00),
      pdf1Delta_Bu2Dst0h_Dst02D0gamma_(
          ("pdf1_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          Bu2Dst0h_Dst02D0gamma_meanDelta_, Bu2Dst0h_Dst02D0gamma_sigmaDelta_,
          Bu2Dst0h_Dst02D0gamma_a1Delta_, Bu2Dst0h_Dst02D0gamma_n1Delta_),
      pdf2Delta_Bu2Dst0h_Dst02D0gamma_(
          ("pdf2_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "", Configuration::Get().deltaMass(),
          Bu2Dst0h_Dst02D0gamma_meanDelta_, Bu2Dst0h_Dst02D0gamma_sigmaDelta_,
          Bu2Dst0h_Dst02D0gamma_a2Delta_, Bu2Dst0h_Dst02D0gamma_n2Delta_),
      Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_(
          ("Bu2Dst0h_Dst02D0gamma_frac1Pdf_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "", 2.6638e-01),
      pdfDelta_Bu2Dst0h_Dst02D0gamma_(
          ("pdf_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::delta, Neutral::pi0))
              .c_str(),
          "",
          RooArgList(pdf1Delta_Bu2Dst0h_Dst02D0gamma_,
                     pdf2Delta_Bu2Dst0h_Dst02D0gamma_),
          Bu2Dst0h_Dst02D0gamma_frac1PdfDelta_),
      Bu2Dst0h_Dst02D0gamma_meanBu_(
          ("Bu2Dst0h_Dst02D0gamma_mean_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0))
              .c_str(),
          "", 5.2819e+03),
      relativeBuWidth_Bu2Dst0h_Dst02D0gamma_(
          ("relativeBuWidth_Bu2Dst0h_Dst02D0gamma_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0))
              .c_str(),
          "", 0.95),
      Bu2Dst0h_Dst02D0gamma_a1Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a1_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0))
              .c_str(),
          "", 1.6184e+00),
      Bu2Dst0h_Dst02D0gamma_a2Bu_(
          ("Bu2Dst0h_Dst02D0gamma_a2_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0))
              .c_str(),
          "", -1.6623e+00),
      Bu2Dst0h_Dst02D0gamma_n1Bu_(
          ("Bu2Dst0h_Dst02D0gamma_n1_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0))
              .c_str(),
          "", 8.6469e+00),
      Bu2Dst0h_Dst02D0gamma_n2Bu_(
          ("Bu2Dst0h_Dst02D0gamma_n2_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0))
              .c_str(),
          "", 5.2563e+00),
      Bu2Dst0h_Dst02D0gamma_frac1PdfBu_(
          ("Bu2Dst0h_Dst02D0gamma_frac1Pdf_" +
           ComposeName(uniqueId, Variable::buDelta, Neutral::pi0))
              .c_str(),
          "", 6.8457e-01) {}
