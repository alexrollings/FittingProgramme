#pragma once
#include "RooAbsPdf.h"
#include "RooArgList.h"
#include "RooAddPdf.h"
#include "RooExponential.h"
#include "RooSimultaneous.h"
#include "NeutralVars.h" 
#include "BachelorVars.h" 
#include "Configuration.h" 


// Pdf

// Remove namespace when not duplicate anymore

template <Neutral neutral, Bachelor bachelor, Daughters daughters> class Pdf {

public:
  static Pdf<neutral, bachelor, daughters> &Get() {
    static Pdf<neutral, bachelor, daughters> singleton;
    return singleton;
  }

  void AddToSimultaneousPdf(RooSimultaneous &simPdf) const;
  void AddToPdf(RooArgList &yields, RooArgList &functions);

  RooRealVar &combinatorialConstant() { return combinatorialConstant_; }
  std::unique_ptr<RooAbsPdf> &combinatorial() { return combinatorial_; }
  RooRealVar &bu2Dst0H_D0pi0Yield() { return bu2Dst0H_D0pi0Yield_; }
  RooRealVar &bu2Dst0H_D0gammaYield() { return bu2Dst0H_D0gammaYield_; }
  RooRealVar &nonTmSignalYield() { return nonTmSignalYield_; }
  RooRealVar &bu2Dst0Hst_D0pi0Yield() { return bu2Dst0Hst_D0pi0Yield_; }
  RooRealVar &bu2Dst0Hst_D0gammaYield() { return bu2Dst0Hst_D0gammaYield_; }
  RooRealVar &bu2D0HYield() { return bu2D0HYield_; }
  RooRealVar &bu2D0HstYield() { return bu2D0HstYield_; }
  RooRealVar &bd2DstHYield() { return bd2DstHYield_; }
  RooRealVar &missIdYield() { return missIdYield_; }
  RooRealVar &combinatorialYield() { return combinatorialYield_; }
  RooArgList &yields() { return yields_; }
  RooArgList &functions() { return functions_; }

private:
  Pdf();
  ~Pdf();

  RooRealVar combinatorialConstant_;
  std::unique_ptr<RooAbsPdf> combinatorial_;

  RooRealVar bu2Dst0H_D0pi0Yield_;
  RooRealVar bu2Dst0H_D0gammaYield_;
  RooRealVar nonTmSignalYield_;
  RooRealVar bu2Dst0Hst_D0pi0Yield_;
  RooRealVar bu2Dst0Hst_D0gammaYield_;
  RooRealVar bu2D0HYield_;
  RooRealVar bu2D0HstYield_;
  RooRealVar bd2DstHYield_;
  RooRealVar missIdYield_;
  RooRealVar combinatorialYield_;
  RooArgList yields_;
  RooArgList functions_;
  std::unique_ptr<RooAddPdf> addPdf_;
};

// template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::kpi>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::kk>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::pipi>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::pi, Daughters::pik>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::kpi>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::kk>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::pipi>::Pdf();
// template <> Pdf<Neutral::gamma, Bachelor::k, Daughters::pik>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::kpi>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::kk>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::pipi>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::pi, Daughters::pik>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::kpi>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::kk>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::pipi>::Pdf();
// template <> Pdf<Neutral::pi0, Bachelor::k, Daughters::pik>::Pdf();

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
Pdf<neutral, bachelor, daughters>::Pdf()
    : combinatorialConstant_(
          ("combinatorialConstant_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "Combinatorial parameter", 0.1, -1, 1),
      combinatorial_(new RooExponential(
          ("combinatorial_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "combinatorial exponential", Configuration::Get().buMass(),
          combinatorialConstant_)),
      bu2Dst0H_D0pi0Yield_(
          ("bu2Dst0H_D0pi0Yield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "bu2Dst0H_D0pi0 yield", 10000, 0, 30000),
      bu2Dst0H_D0gammaYield_(
          ("bu2Dst0H_D0gammaYield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "bu2Dst0H_D0gamma yield", 10000, 0, 30000),
      nonTmSignalYield_(
          ("nonTmSignalYield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "nonTmSignal yield", 10000, 0, 30000),
      bu2Dst0Hst_D0pi0Yield_(
          ("bu2Dst0Hst_D0pi0Yield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "bu2Dst0Hst_D0pi0 yield", 10000, 0, 30000),
      bu2Dst0Hst_D0gammaYield_(
          ("bu2Dst0Hst_D0gammaYield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "bu2Dst0Hst_D0gamma yield", 10000, 0, 30000),
      bu2D0HYield_(("bu2D0HYield_" +
                    ComposeFittingCategoryName(neutral, bachelor, daughters))
                       .c_str(),
                   "bu2D0H yield", 10000, 0, 30000),
      bu2D0HstYield_(("bu2D0HstYield_" +
                      ComposeFittingCategoryName(neutral, bachelor, daughters))
                         .c_str(),
                     "bu2D0Hst yield", 10000, 0, 30000),
      bd2DstHYield_(("bd2DstHYield_" +
                     ComposeFittingCategoryName(neutral, bachelor, daughters))
                        .c_str(),
                    "bd2DstH yield", 10000, 0, 30000),
      missIdYield_(("missIdYield_" +
                    ComposeFittingCategoryName(neutral, bachelor, daughters))
                       .c_str(),
                   "missId yield", 10000, 0, 30000),
      combinatorialYield_(
          ("combinatorialYield_" +
           ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str(),
          "combinatorial yield", 10000, 0, 30000),
      yields_(
          ("yields_" + ComposeFittingCategoryName(neutral, bachelor, daughters))
              .c_str()),
      functions_(("functions_" +
                  ComposeFittingCategoryName(neutral, bachelor, daughters))
                     .c_str()),
      addPdf_(nullptr) {

  functions_.add(*(BachelorVars<neutral, bachelor>::Get().bu2Dst0H_D0pi0()));
  functions_.add(*(BachelorVars<neutral, bachelor>::Get().bu2Dst0H_D0gamma()));
  functions_.add(*(BachelorVars<neutral, bachelor>::Get().nonTmSignal()));
  functions_.add(*(BachelorVars<neutral, bachelor>::Get().bu2Dst0Hst_D0pi0()));
  functions_.add(*(BachelorVars<neutral, bachelor>::Get().bu2Dst0Hst_D0gamma()));
  functions_.add(*(BachelorVars<neutral, bachelor>::Get().bu2D0H()));
  functions_.add(*(BachelorVars<neutral, bachelor>::Get().bu2D0Hst()));
  functions_.add(*(BachelorVars<neutral, bachelor>::Get().bd2DstH()));
  functions_.add(*(BachelorVars<neutral, bachelor>::Get().missId()));
  functions_.add(*combinatorial_);
  yields_.add(bu2Dst0H_D0pi0Yield_);
  yields_.add(bu2Dst0H_D0gammaYield_);
  yields_.add(nonTmSignalYield_);
  yields_.add(bu2Dst0Hst_D0pi0Yield_);
  yields_.add(bu2Dst0Hst_D0gammaYield_);
  yields_.add(bu2D0HYield_);
  yields_.add(bu2D0HstYield_);
  yields_.add(bd2DstHYield_);
  yields_.add(missIdYield_);
  yields_.add(combinatorialYield_);

  addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeFittingCategoryName(neutral, bachelor, daughters))
          .c_str(),
      ("pdf_" + ComposeFittingCategoryName(neutral, bachelor, daughters))
          .c_str(),
      functions_, yields_));
}

template <Neutral neutral, Bachelor bachelor, Daughters daughters>
void Pdf<neutral, bachelor, daughters>::AddToSimultaneousPdf(
    RooSimultaneous &simPdf) const {
  simPdf.addPdf(
      *addPdf_,
      ComposeFittingCategoryName(neutral, bachelor, daughters).c_str());
}

