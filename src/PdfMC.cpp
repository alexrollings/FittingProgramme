#include "PdfMC.h"

PdfMC::PdfMC(int uniqueId)
    : initSig_(),
      boxEff_(("boxEff_" + std::to_string(uniqueId)).c_str(), "", 1),
      orEff_(("orEff_" + std::to_string(uniqueId)).c_str(), "", 1),
      buDeltaCutEff_(("buDeltaCutEff_" + std::to_string(uniqueId)).c_str(), "",
                    1),
      deltaCutEff_(("deltaCutEff_" + std::to_string(uniqueId)).c_str(), "", 1),
      yieldSignal_(nullptr),
      yieldBuDeltaSignal_(nullptr),
      yieldDeltaSignal_(nullptr),
      pdfBuDelta_(nullptr),
      pdfDelta_(nullptr) {
  if (Configuration::Get().neutral() == Neutral::gamma) {
    Configuration::Get().SetEfficiencies(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                                          orEff_, boxEff_, buDeltaCutEff_,
                                          deltaCutEff_, false);
    initSig_ = 13000 * orEff_.getVal();
  } else {
    Configuration::Get().SetEfficiencies(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                                          orEff_, boxEff_, buDeltaCutEff_,
                                          deltaCutEff_, false);
    initSig_ = 3000 * orEff_.getVal();
  }

  yieldSignal_ = std::unique_ptr<RooRealVar>(
      new RooRealVar(("yieldSignal_" + std::to_string(uniqueId)).c_str(), "",
                     initSig_, 0, 20000));
  yieldBuDeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("yieldBuDeltaSignal_" + std::to_string(uniqueId)).c_str(), "",
      "(@0/@1)*@2", RooArgList(deltaCutEff_, orEff_, *yieldSignal_)));
  yieldDeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
      ("yieldDeltaSignal_" + std::to_string(uniqueId)).c_str(), "", "(@0/@1)*@2",
      RooArgList(buDeltaCutEff_, orEff_, *yieldSignal_)));

  if (Configuration::Get().neutral() == Neutral::gamma) {
    yield1BuDeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yield1BuDeltaSignal_" + std::to_string(uniqueId)).c_str(), "",
        "@0*@1",
        RooArgList(*yieldBuDeltaSignal_,
                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                       .Bu2Dst0h_D0gamma_fracPdf1Bu())));
    yield2BuDeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yield2BuDeltaSignal_" + std::to_string(uniqueId)).c_str(), "",
        "@0*(1-@1)",
        RooArgList(*yieldBuDeltaSignal_,
                   NeutralVars<Neutral::gamma>::Get(uniqueId)
                       .Bu2Dst0h_D0gamma_fracPdf1Bu())));
    pdfBuDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfBuDelta_" + std::to_string(uniqueId)).c_str(), "",
        RooArgSet(NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                      .pdf1Bu_Bu2Dst0h_D0gamma(),
                  NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
                      .pdf2Bu_Bu2Dst0h_D0gamma()),
        RooArgSet(*yield1BuDeltaSignal_, *yield2BuDeltaSignal_)));
    yield1DeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yield1DeltaSignal_" + std::to_string(uniqueId)).c_str(), "", "@0*@1",
        RooArgList(*yieldDeltaSignal_, NeutralVars<Neutral::gamma>::Get(uniqueId)
                                           .Bu2Dst0h_D0gamma_fracPdf1Delta())));
    yield2DeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yield2DeltaSignal_" + std::to_string(uniqueId)).c_str(), "",
        "@0*(1-@1)",
        RooArgList(*yieldDeltaSignal_, NeutralVars<Neutral::gamma>::Get(uniqueId)
                                           .Bu2Dst0h_D0gamma_fracPdf1Delta())));
    pdfDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfDelta_" + std::to_string(uniqueId)).c_str(), "",
        RooArgSet(
            NeutralVars<Neutral::gamma>::Get(uniqueId).pdf1Delta_Bu2Dst0h_D0gamma(),
            NeutralVars<Neutral::gamma>::Get(uniqueId)
                .pdf2Delta_Bu2Dst0h_D0gamma()),
        RooArgSet(*yield1DeltaSignal_, *yield2DeltaSignal_)));
  } else {
    yield1BuDeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yield1BuDeltaSignal_" + std::to_string(uniqueId)).c_str(), "",
        "@0*@1",
        RooArgList(*yieldBuDeltaSignal_,
                   NeutralVars<Neutral::pi0>::Get(uniqueId)
                       .Bu2Dst0h_D0pi0_fracPdf1Bu())));
    yield2BuDeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yield2BuDeltaSignal_" + std::to_string(uniqueId)).c_str(), "",
        "@0*(1-@1)",
        RooArgList(*yieldBuDeltaSignal_,
                   NeutralVars<Neutral::pi0>::Get(uniqueId)
                       .Bu2Dst0h_D0pi0_fracPdf1Bu())));
    pdfBuDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfBuDelta_" + std::to_string(uniqueId)).c_str(), "",
        RooArgSet(NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                      .pdf1Bu_Bu2Dst0h_D0pi0(),
                  NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
                      .pdf2Bu_Bu2Dst0h_D0pi0()),
        RooArgSet(*yield1BuDeltaSignal_, *yield2BuDeltaSignal_)));
    yield1DeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yield1DeltaSignal_" + std::to_string(uniqueId)).c_str(), "", "@0*@1",
        RooArgList(*yieldDeltaSignal_, NeutralVars<Neutral::pi0>::Get(uniqueId)
                                           .Bu2Dst0h_D0pi0_fracPdf1Delta())));
    yield2DeltaSignal_ = std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
        ("yield2DeltaSignal_" + std::to_string(uniqueId)).c_str(), "",
        "@0*(1-@1)",
        RooArgList(*yieldDeltaSignal_, NeutralVars<Neutral::pi0>::Get(uniqueId)
                                           .Bu2Dst0h_D0pi0_fracPdf1Delta())));
    pdfDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfDelta_" + std::to_string(uniqueId)).c_str(), "",
        RooArgSet(
            NeutralVars<Neutral::pi0>::Get(uniqueId).pdf1Delta_Bu2Dst0h_D0pi0(),
            NeutralVars<Neutral::pi0>::Get(uniqueId)
                .pdf2Delta_Bu2Dst0h_D0pi0()),
        RooArgSet(*yield1DeltaSignal_, *yield2DeltaSignal_)));
  }
}

void PdfMC::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*pdfBuDelta_, EnumToString(Mass::buDelta).c_str());
  simPdf.addPdf(*pdfDelta_, EnumToString(Mass::delta).c_str());
}
