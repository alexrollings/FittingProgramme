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
    initSig_ = 13000;
    Configuration::Get().SetEfficiencies(Mode::Bu2Dst0pi_D0gamma, Bachelor::pi,
                                          orEff_, boxEff_, buDeltaCutEff_,
                                          deltaCutEff_, false);
  } else {
    initSig_ = 3000;
    Configuration::Get().SetEfficiencies(Mode::Bu2Dst0pi_D0pi0, Bachelor::pi,
                                          orEff_, boxEff_, buDeltaCutEff_,
                                          deltaCutEff_, false);
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
    pdfBuDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfBuDelta_" + std::to_string(uniqueId)).c_str(), "",
        NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::Get(uniqueId)
            .pdfBu_Bu2Dst0h_D0gamma(),
        *yieldBuDeltaSignal_));
    pdfDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfDelta_" + std::to_string(uniqueId)).c_str(), "",
        NeutralVars<Neutral::gamma>::Get(uniqueId).pdfDelta_Bu2Dst0h_D0gamma(),
        *yieldDeltaSignal_));
  } else {
    pdfBuDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfBuDelta_" + std::to_string(uniqueId)).c_str(), "",
        NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::Get(uniqueId)
            .pdfBu_Bu2Dst0h_D0pi0(),
        *yieldBuDeltaSignal_));
    pdfDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
        ("pdfDelta_" + std::to_string(uniqueId)).c_str(), "",
        NeutralVars<Neutral::pi0>::Get(uniqueId).pdfDelta_Bu2Dst0h_D0pi0(),
        *yieldDeltaSignal_));
  }
}

void PdfMC::AddToSimultaneousPdf(RooSimultaneous &simPdf) const {
  simPdf.addPdf(*pdfBuDelta_, EnumToString(Mass::buDelta).c_str());
  simPdf.addPdf(*pdfDelta_, EnumToString(Mass::delta).c_str());
}
