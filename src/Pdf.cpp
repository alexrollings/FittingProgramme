#include "Pdf.h"

// Return yield with correct asymmetry definition
template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *Make_N_split(int uniqueId, const char *nameStr,
                            RooAbsReal &N_tot, RooFormulaVar &a_RAW) {
  switch (charge) {
    case Charge::plus:
      switch (daughters) {
        case Daughters::kpi:
          // Want to do all the NAMING with the reconstructed bachelor (category
          // mis ID ends up in), but the physics formulae for the asymmetry
          // depend on the TRUE bachelor of the mode
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::kk:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::pipi:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::pik:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2/@3*@4))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+(@1*@2*@3))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
      }
      break;
    case Charge::minus:
      switch (daughters) {
        case Daughters::kpi:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::kk:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::pipi:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
        case Daughters::pik:
          switch (bachelor) {
            case Bachelor::pi:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2/@3*@4,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_Kpi(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
            case Bachelor::k:
              return new RooFormulaVar(
                  (nameStr +
                   ComposeName(uniqueId, neutral, bachelor, daughters, charge))
                      .c_str(),
                  "@0/(1+pow(@1*@2*@3,-1))",
                  RooArgList(N_tot, a_RAW, GlobalVars::Get(uniqueId).a_Prod(),
                             GlobalVars::Get(uniqueId).a_pi()));
              break;
          }
          break;
      }
      break;
    case Charge::total:
      return new RooFormulaVar(
          (nameStr +
           ComposeName(uniqueId, neutral, bachelor, daughters, charge))
              .c_str(),
          "@0", RooArgList(N_tot));
      break;
  }
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge>
RooFormulaVar *Make_N_trueId(int uniqueId, const char *nameStr,
                             RooAbsReal &N_split) {
  return new RooFormulaVar(
      (nameStr + ComposeName(uniqueId, neutral, bachelor, daughters, charge))
          .c_str(),
      "@0*@1",
      RooArgList(N_split, *GlobalVars::Get(uniqueId).pidEffMap()[MakePidKey(
                              bachelor, Charge::total)]));
}

PdfBase::PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor,
                 Daughters daughters, Charge charge)
    : uniqueId_(uniqueId),
      neutral_(neutral),
      bachelor_(bachelor),
      daughters_(daughters),
      charge_(charge),
      addPdfBu_(nullptr),
      addPdfBuPartial_(nullptr),
      addPdfDelta_(nullptr),
      yieldsBu_(("yieldsBu_" +
                 ComposeName(uniqueId_, neutral, bachelor, daughters, charge))
                    .c_str()),
      yieldsBuPartial_(
          ("yieldsBuPartial_" +
           ComposeName(uniqueId_, neutral, bachelor, daughters, charge))
              .c_str()),
      yieldsDelta_(("yieldsDelta_" + ComposeName(uniqueId_, neutral, bachelor,
                                                 daughters, charge))
                       .c_str()),
      functionsBu_(("functionsBu_" + ComposeName(uniqueId_, neutral, bachelor,
                                                 daughters, charge))
                       .c_str()),
      functionsBuPartial_(
          ("functionsBuPartial_" +
           ComposeName(uniqueId_, neutral, bachelor, daughters, charge))
              .c_str()),
      functionsDelta_(
          ("functionsDelta_" +
           ComposeName(uniqueId_, neutral, bachelor, daughters, charge))
              .c_str()),
      N_split_Bu2Dst0h_D0gamma_(nullptr),
      N_split_Bu2Dst0h_D0pi0_(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0pi0_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0pi0(),
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .a_Bu2Dst0h_D0pi0())),
      N_split_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_split_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_split_MisRec_(Make_N_split<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_split_MisRec_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .N_tot_MisRec(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .a_MisRec())),
      N_split_Bu2D0h_(Make_N_split<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_split_Bu2D0h_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .N_tot_Bu2D0h(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .a_Bu2D0h())),
      N_split_PartRec_(Make_N_split<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_split_PartRec_",
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .N_tot_PartRec(),
          NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
              uniqueId_)
              .a_PartRec())),
      N_split_Bs2Dst0Kpi_(nullptr),
      N_split_Bs2D0Kpi_(nullptr),
      N_trueId_Bu2Dst0h_D0gamma_(nullptr),
      N_trueId_Bu2Dst0h_D0pi0_(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0pi0_", *N_split_Bu2Dst0h_D0pi0_)),
      N_trueId_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_trueId_MisRec_(Make_N_trueId<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_MisRec_", *N_split_MisRec_)),
      N_trueId_Bu2D0h_(Make_N_trueId<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu2D0h_", *N_split_Bu2D0h_)),
      N_trueId_PartRec_(Make_N_trueId<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_PartRec_", *N_split_PartRec_)),
      N_trueId_Bs2Dst0Kpi_(nullptr),
      N_trueId_Bs2D0Kpi_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0gamma_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0pi0_(Make_N_1D<neutral, bachelor, daughters,
                                               charge>(
          uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0pi0_",
          *N_trueId_Bu2Dst0h_D0pi0_,
          NeutralVars<neutral>::Get(uniqueId_).buDeltaCutEffBu2Dst0h_D0pi0())),
      N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_trueId_Delta_MisRec_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Delta_MisRec_", *N_trueId_MisRec_,
          NeutralVars<neutral>::Get(uniqueId_).buDeltaCutEffMisRec())),
      N_trueId_Delta_Bu2D0h_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Delta_Bu2D0h_", *N_trueId_Bu2D0h_,
          NeutralVars<neutral>::Get(uniqueId_).buDeltaCutEffBu2D0h())),
      N_trueId_Delta_PartRec_(Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Delta_PartRec_", *N_trueId_PartRec_,
          NeutralVars<neutral>::Get(uniqueId_).buDeltaCutEffPartRec())),
      N_trueId_Delta_Bs2Dst0Kpi_(nullptr),
      N_trueId_Delta_Bs2D0Kpi_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0gamma_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_trueId_Bu_Bu2Dst0h_D0pi0_(nullptr),
      N_trueId_Bu_MisRec_(nullptr),
      N_trueId_Bu_Bu2D0h_(nullptr),
      N_trueId_Bu_PartRec_(nullptr),
      N_trueId_Bu_Bs2Dst0Kpi_(nullptr),
      N_trueId_Bu_Bs2D0Kpi_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0gamma_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_(nullptr),
      N_trueId_BuPartial_MisRec_(nullptr),
      N_trueId_BuPartial_Bu2D0h_(nullptr),
      N_trueId_BuPartial_PartRec_(nullptr),
      N_trueId_BuPartial_Bs2Dst0Kpi_(nullptr),
      N_trueId_BuPartial_Bs2D0Kpi_(nullptr),
      N_misId_Bu2Dst0h_D0gamma_(nullptr),
      N_misId_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_MisRec_(nullptr),
      N_misId_Bu2D0h_(nullptr),
      N_misId_PartRec_(nullptr),
      N_misId_Delta_Bu2Dst0h_D0gamma_(nullptr),
      N_misId_Delta_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_Delta_MisRec_(nullptr),
      N_misId_Delta_Bu2D0h_(nullptr),
      N_misId_Delta_PartRec_(nullptr),
      N_misId_Bu_Bu2Dst0h_D0gamma_(nullptr),
      N_misId_Bu_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_Bu_MisRec_(nullptr),
      N_misId_Bu_Bu2D0h_(nullptr),
      N_misId_Bu_PartRec_(nullptr),
      N_misId_BuPartial_Bu2Dst0h_D0pi0_(nullptr),
      N_misId_BuPartial_MisRec_(nullptr),
      N_misId_BuPartial_Bu2D0h_(nullptr),
      N_misId_BuPartial_PartRec_(nullptr) {
  // std::cout << "Constructing PDF " << EnumToString(neutral_) << " "
  //           << EnumToString(bachelor_) << " " << EnumToString(daughters_)
  //           << std::endl;
  if (neutral == Neutral::gamma) {
    N_split_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bu2Dst0h_D0gamma_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bu2Dst0h_D0gamma(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bu2Dst0h_D0gamma()));
    N_trueId_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu2Dst0h_D0gamma_",
            *N_split_Bu2Dst0h_D0gamma_));
    N_trueId_Delta_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0gamma_",
            *N_trueId_Bu2Dst0h_D0gamma_,
            NeutralVars<neutral>::Get(uniqueId_)
                .buDeltaCutEffBu2Dst0h_D0gamma()));
  }
  if (daughters == Daughters::pik) {
    N_split_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bu2Dst0h_D0pi0_FAVasSUP_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bu2Dst0h_D0pi0_FAVasSUP(),
            NeutralBachelorDaughtersVars<neutral, bachelor,
                                         Daughters::kpi>::Get(uniqueId_)
                .a_Bu2Dst0h_D0pi0()));
    N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_",
            *N_split_Bu2Dst0h_D0pi0_FAVasSUP_));
    N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP_",
            *N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_,
            NeutralVars<neutral>::Get(uniqueId_)
                .buDeltaCutEffBu2Dst0h_D0pi0_FAVasSUP()));
    if (neutral == Neutral::gamma) {
      N_split_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          Make_N_split<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_split_Bu2Dst0h_D0gamma_FAVasSUP_",
              NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                  uniqueId_)
                  .N_tot_Bu2Dst0h_D0gamma_FAVasSUP(),
              NeutralBachelorDaughtersVars<neutral, bachelor,
                                           Daughters::kpi>::Get(uniqueId_)
                  .a_Bu2Dst0h_D0gamma()));
      N_trueId_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          Make_N_trueId<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu2Dst0h_D0gamma_FAVasSUP_",
              *N_split_Bu2Dst0h_D0gamma_FAVasSUP_));
      N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP_ =
          std::unique_ptr<RooFormulaVar>(
              Make_N_1D<neutral, bachelor, daughters, charge>(
                  uniqueId_, "N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP_",
                  *N_trueId_Bu2Dst0h_D0gamma_FAVasSUP_,
                  NeutralVars<neutral>::Get(uniqueId_)
                      .buDeltaCutEffBu2Dst0h_D0gamma_FAVasSUP()));
    }
  }
  if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
      daughters != Daughters::kpi) {
    N_split_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bs2Dst0Kpi_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bs2Dst0Kpi(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bs2Dst0Kpi()));
    N_trueId_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bs2Dst0Kpi_", *N_split_Bs2Dst0Kpi_));
    N_split_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_split<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_split_Bs2D0Kpi_",
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .N_tot_Bs2D0Kpi(),
            NeutralBachelorDaughtersVars<neutral, bachelor, daughters>::Get(
                uniqueId_)
                .a_Bs2D0Kpi()));
    N_trueId_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_trueId<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bs2D0Kpi_", *N_split_Bs2D0Kpi_));
    N_trueId_Delta_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bs2Dst0Kpi_", *N_trueId_Bs2Dst0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buDeltaCutEffBs2Dst0Kpi()));
    N_trueId_Delta_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Delta_Bs2D0Kpi_", *N_trueId_Bs2D0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .buDeltaCutEffBs2D0Kpi()));
  }
  if (neutral == Neutral::gamma) {
    N_trueId_Bu_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0gamma_",
            *N_trueId_Bu2Dst0h_D0gamma_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaCutEffBu2Dst0h_D0gamma()));
  }
  N_trueId_Bu_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0pi0_", *N_trueId_Bu2Dst0h_D0pi0_,
          NeutralVars<neutral>::Get(uniqueId_).deltaCutEffBu2Dst0h_D0pi0()));
  N_trueId_Bu_MisRec_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_MisRec_", *N_trueId_MisRec_,
          NeutralVars<neutral>::Get(uniqueId_).deltaCutEffMisRec()));
  N_trueId_Bu_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_Bu2D0h_", *N_trueId_Bu2D0h_,
          NeutralVars<neutral>::Get(uniqueId_).deltaCutEffBu2D0h()));
  N_trueId_Bu_PartRec_ = std::unique_ptr<RooFormulaVar>(
      Make_N_1D<neutral, bachelor, daughters, charge>(
          uniqueId_, "N_trueId_Bu_PartRec_", *N_trueId_PartRec_,
          NeutralVars<neutral>::Get(uniqueId_).deltaCutEffPartRec()));
  if (daughters == Daughters::pik) {
    N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP_",
            *N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaCutEffBu2Dst0h_D0pi0_FAVasSUP()));
    if (neutral == Neutral::gamma) {
      N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP_",
              *N_trueId_Bu2Dst0h_D0gamma_FAVasSUP_,
              NeutralVars<neutral>::Get(uniqueId_)
                  .deltaCutEffBu2Dst0h_D0gamma_FAVasSUP()));
    }
  }
  if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
      daughters != Daughters::kpi) {
    N_trueId_Bu_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bs2Dst0Kpi_", *N_trueId_Bs2Dst0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .deltaCutEffBs2Dst0Kpi()));
    N_trueId_Bu_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_Bu_Bs2D0Kpi_", *N_trueId_Bs2D0Kpi_,
            NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                .deltaCutEffBs2D0Kpi()));
  }
  if (Configuration::Get().fitBuPartial() == true) {
    N_trueId_BuPartial_Bu2Dst0h_D0gamma_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0gamma_",
            *N_trueId_Bu2Dst0h_D0gamma_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaPartialCutEffBu2Dst0h_D0gamma()));
    N_trueId_BuPartial_Bu2Dst0h_D0pi0_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0pi0_",
            *N_trueId_Bu2Dst0h_D0pi0_,
            NeutralVars<neutral>::Get(uniqueId_)
                .deltaPartialCutEffBu2Dst0h_D0pi0()));
    N_trueId_BuPartial_MisRec_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_MisRec_", *N_trueId_MisRec_,
            NeutralVars<neutral>::Get(uniqueId_).deltaPartialCutEffMisRec()));
    N_trueId_BuPartial_Bu2D0h_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_Bu2D0h_", *N_trueId_Bu2D0h_,
            NeutralVars<neutral>::Get(uniqueId_).deltaPartialCutEffBu2D0h()));
    N_trueId_BuPartial_PartRec_ = std::unique_ptr<RooFormulaVar>(
        Make_N_1D<neutral, bachelor, daughters, charge>(
            uniqueId_, "N_trueId_BuPartial_PartRec_", *N_trueId_PartRec_,
            NeutralVars<neutral>::Get(uniqueId_).deltaPartialCutEffPartRec()));
    if (daughters == Daughters::pik) {
      N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_ =
          std::unique_ptr<RooFormulaVar>(
              Make_N_1D<neutral, bachelor, daughters, charge>(
                  uniqueId_, "N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP_",
                  *N_trueId_Bu2Dst0h_D0pi0_FAVasSUP_,
                  NeutralVars<neutral>::Get(uniqueId_)
                      .deltaPartialCutEffBu2Dst0h_D0pi0_FAVasSUP()));
    }
    if (Configuration::Get().runADS() == true && bachelor == Bachelor::k &&
        daughters != Daughters::kpi) {
      N_trueId_BuPartial_Bs2Dst0Kpi_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_BuPartial_Bs2Dst0Kpi_",
              *N_trueId_Bs2Dst0Kpi_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .deltaPartialCutEffBs2Dst0Kpi()));
      N_trueId_BuPartial_Bs2D0Kpi_ = std::unique_ptr<RooFormulaVar>(
          Make_N_1D<neutral, bachelor, daughters, charge>(
              uniqueId_, "N_trueId_BuPartial_Bs2D0Kpi_", *N_trueId_Bs2D0Kpi_,
              NeutralBachelorVars<neutral, bachelor>::Get(uniqueId_)
                  .deltaPartialCutEffBs2D0Kpi()));
    }
  }
}

void PdfBase::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*addPdfBu_, CategoryName(Mass::buDelta).c_str());
  if (Configuration::Get().fitBuPartial() == true) {
    simPdf.addPdf(*addPdfBuPartial_,
                  CategoryName(Mass::buDeltaPartial).c_str());
  }
  if (Configuration::Get().fit1D() == false) {
    simPdf.addPdf(*addPdfDelta_, CategoryName(Mass::delta).c_str());
  }
}
