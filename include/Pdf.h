#pragma once
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooSimultaneous.h"
#include "Yields.h"

class PdfBase {
 public:
  void AddToSimultaneousPdf(RooSimultaneous &) const;

  inline int uniqueId() const { return uniqueId_; }
  inline Bachelor bachelor() const { return bachelor_; }
  inline Neutral neutral() const { return neutral_; }
  inline Daughters daughters() const { return daughters_; }
  inline Charge charge() const { return charge_; }

  inline RooArgList &yieldsBu() { return yieldsBu_; }
  inline RooArgList &yieldsBuPartial() { return yieldsBuPartial_; }
  inline RooArgList &yieldsDelta() { return yieldsDelta_; }
  inline RooArgList &functionsBu() { return functionsBu_; }
  inline RooArgList &functionsBuPartial() { return functionsBuPartial_; }
  inline RooArgList &functionsDelta() { return functionsDelta_; }
  inline RooAddPdf &addPdfBu() { return *addPdfBu_; }
  inline RooAddPdf &addPdfBuPartial() { return *addPdfBuPartial_; }
  inline RooAddPdf &addPdfDelta() { return *addPdfDelta_; }

  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_FAVasSUP() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_trueId_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0hst_D0pi0() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0hst_D0gamma() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_FAVasSUP() const = 0;
  virtual RooFormulaVar &N_trueId_MisRec() const = 0;
  virtual RooFormulaVar &N_trueId_Bu2D0h() const = 0;
  virtual RooFormulaVar &N_trueId_PartRec() const = 0;
  virtual RooFormulaVar &N_trueId_Bs2Dst0Kpi() const = 0;
  virtual RooFormulaVar &N_trueId_Bs2D0Kpi() const = 0;

  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooFormulaVar &N_misId_Bd2Dsth() const = 0;
  virtual RooFormulaVar &N_misId_Bu2D0hst() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0hst_D0pi0() const = 0;
  virtual RooFormulaVar &N_misId_Bu2Dst0hst_D0gamma() const = 0;
  virtual RooFormulaVar &N_misId_MisRec() const = 0;
  virtual RooFormulaVar &N_misId_Bu2D0h() const = 0;
  virtual RooFormulaVar &N_misId_PartRec() const = 0;

  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooDstD0BG &pdfDelta_Bd2Dsth() const = 0;
  virtual RooDstD0BG &pdfDelta_Bu2D0hst() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP() const = 0;
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP() const = 0;
  virtual RooDstD0BG &pdfDelta_MisRec() const = 0;
  virtual RooDstD0BG &pdfDelta_Bu2D0h() const = 0;
  virtual RooDstD0BG &pdfDelta_PartRec() const = 0;
  virtual RooAbsPdf &pdfDelta_Bs2Dst0Kpi() const = 0;
  virtual RooAbsPdf &pdfDelta_Bs2D0Kpi() const = 0;

  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_Bd2Dsth() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_Bu2D0hst() const = 0;
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0hst_D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0hst_D0pi0() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_MisRec() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_Bu2D0h() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_PartRec() const = 0;

  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooGaussian &pdfBu_Bd2Dsth() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2D0hst() const = 0;
  virtual RooAddPdf &pdfBu_Bu2Dst0hst_D0gamma() const = 0;
  virtual RooGaussian &pdfBu_Bu2Dst0hst_D0pi0() const = 0;
  virtual RooCBShape &pdfBu_Bu2Dst0h_D0gamma_FAVasSUP() const = 0;
  virtual RooCBShape &pdfBu_Bu2Dst0h_D0pi0_FAVasSUP() const = 0;
  virtual RooCruijff &pdfBu_MisRec() const = 0;
  virtual RooCruijff &pdfBu_Bu2D0h() const = 0;
  virtual RooAbsPdf &pdfBu_PartRec() const = 0;
  virtual RooAbsPdf &pdfBu_Bs2Dst0Kpi() const = 0;
  virtual RooAbsPdf &pdfBu_Bs2D0Kpi() const = 0;

  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooGaussian &pdfBu_misId_Bd2Dsth() const = 0;
  virtual RooGaussian &pdfBu_misId_Bu2D0hst() const = 0;
  virtual RooAddPdf &pdfBu_misId_Bu2Dst0hst_D0gamma() const = 0;
  virtual RooCBShape &pdfBu_misId_Bu2Dst0hst_D0pi0() const = 0;
  virtual RooAbsPdf &pdfBu_misId_MisRec() const = 0;
  virtual RooCruijff &pdfBu_misId_Bu2D0h() const = 0;
  virtual RooCruijff &pdfBu_misId_PartRec() const = 0;

  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfBuPartial_Bu2Dst0h_D0pi0() const = 0;
  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooAbsPdf &pdfBuPartial_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooGaussian &pdfBuPartial_Bd2Dsth() const = 0;
  virtual RooGaussian &pdfBuPartial_Bu2D0hst() const = 0;
  virtual RooGaussian &pdfBuPartial_Bu2Dst0hst_D0gamma() const = 0;
  virtual RooGaussian &pdfBuPartial_Bu2Dst0hst_D0pi0() const = 0;
  virtual RooCBShape &pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP() const = 0;
  virtual RooCruijff &pdfBuPartial_MisRec() const = 0;
  virtual RooCruijff &pdfBuPartial_Bu2D0h() const = 0;
  virtual RooCruijff &pdfBuPartial_PartRec() const = 0;
  virtual RooAbsPdf &pdfBuPartial_Bs2Dst0Kpi() const = 0;
  virtual RooAbsPdf &pdfBuPartial_Bs2D0Kpi() const = 0;

  virtual RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooCBShape &pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN() const = 0;
  virtual RooCBShape &pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN() const = 0;
  virtual RooGaussian &pdfBuPartial_misId_Bd2Dsth() const = 0;
  virtual RooGaussian &pdfBuPartial_misId_Bu2D0hst() const = 0;
  virtual RooGaussian &pdfBuPartial_misId_Bu2Dst0hst_D0gamma() const = 0;
  virtual RooAddPdf &pdfBuPartial_misId_Bu2Dst0hst_D0pi0() const = 0;
  virtual RooCruijff &pdfBuPartial_misId_MisRec() const = 0;
  virtual RooCruijff &pdfBuPartial_misId_Bu2D0h() const = 0;
  virtual RooCruijff &pdfBuPartial_misId_PartRec() const = 0;

  // If a function or a method is defined in the header file, and the class is
  // not a template, it should be inline because otherwise the linker might fail
  // as the function will be present in multiple compiltation unit
  // function needs to be const when you don't change the object when the
  // function is called
  inline std::string CategoryName(Mass mass) const {
    return ComposeFittingName(mass, neutral_, bachelor_, daughters_, charge_);
  }

 protected:  // Can be accessed by deriving classes
  PdfBase(int uniqueId, Neutral neutral, Bachelor bachelor, Daughters daughters,
          Charge charge);
  virtual ~PdfBase() {}

  int uniqueId_;
  Neutral neutral_;
  Bachelor bachelor_;
  Daughters daughters_;
  Charge charge_;

  RooArgList yieldsBu_;
  RooArgList yieldsBuPartial_;
  RooArgList yieldsDelta_;
  RooArgList functionsBu_;
  RooArgList functionsBuPartial_;
  RooArgList functionsDelta_;
  std::unique_ptr<RooAddPdf> addPdfBu_;
  std::unique_ptr<RooAddPdf> addPdfBuPartial_;
  std::unique_ptr<RooAddPdf> addPdfDelta_;
};

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
class Pdf : public PdfBase {
  using This_t = Pdf<_neutral, _bachelor, _daughters, _charge>;

 public:
  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId);

  void CreateBuAddPdf();
  void CreateBuPartialAddPdf();
  void CreateDeltaAddPdf();

  // pdf_Bu2Dst0h_Dst02D0neut are made in another class, but we only deal with
  // PDF in the
  // executable. Give PDF functions to retrieve them
  // It shouldn't be private, it sould be protected then it can be accessed by
  // inheriting classes

  virtual void AssignMisIdYields() {
    Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .AssignMisIdYields();
  }

  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0gamma();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_FAVasSUP() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0gamma_FAVasSUP();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_trueId_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bd2Dsth();
  }
  virtual RooFormulaVar &N_trueId_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2D0hst();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0hst_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0hst_D0gamma();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0hst_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0hst_D0pi0();
  }
  virtual RooFormulaVar &N_trueId_Bu2Dst0h_D0pi0_FAVasSUP() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2Dst0h_D0pi0_FAVasSUP();
  }
  virtual RooFormulaVar &N_trueId_MisRec() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_MisRec();
  }
  virtual RooFormulaVar &N_trueId_Bu2D0h() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bu2D0h();
  }
  virtual RooFormulaVar &N_trueId_PartRec() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_PartRec();
  }
  virtual RooFormulaVar &N_trueId_Bs2Dst0Kpi() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bs2Dst0Kpi();
  }
  virtual RooFormulaVar &N_trueId_Bs2D0Kpi() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_trueId_Bs2D0Kpi();
  }

  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0gamma_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0h_D0pi0_WN() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooFormulaVar &N_misId_Bd2Dsth() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bd2Dsth();
  }
  virtual RooFormulaVar &N_misId_Bu2D0hst() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2D0hst();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0hst_D0gamma() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0hst_D0gamma();
  }
  virtual RooFormulaVar &N_misId_Bu2Dst0hst_D0pi0() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2Dst0hst_D0pi0();
  }
  virtual RooFormulaVar &N_misId_MisRec() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_MisRec();
  }
  virtual RooFormulaVar &N_misId_Bu2D0h() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_Bu2D0h();
  }
  virtual RooFormulaVar &N_misId_PartRec() const {
    return Yields<_neutral, _bachelor, _daughters, _charge>::Get(uniqueId_)
        .N_misId_PartRec();
  }

  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma_WN() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0pi0_WN() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooDstD0BG &pdfDelta_Bd2Dsth() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bd2Dsth();
  }
  virtual RooDstD0BG &pdfDelta_Bu2D0hst() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2D0hst();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP();
  }
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP();
  }
  virtual RooDstD0BG &pdfDelta_MisRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_MisRec();
  }
  virtual RooDstD0BG &pdfDelta_Bu2D0h() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2D0h();
  }
  virtual RooDstD0BG &pdfDelta_PartRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_PartRec();
  }
  virtual RooAbsPdf &pdfDelta_Bs2Dst0Kpi() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_Bs2Dst0Kpi();
  }
  virtual RooAbsPdf &pdfDelta_Bs2D0Kpi() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_Bs2D0Kpi();
  }

  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooDstD0BG &pdfDelta_misId_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooDstD0BG &pdfDelta_misId_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bd2Dsth();
  }
  virtual RooDstD0BG &pdfDelta_misId_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2D0hst();
  }
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0hst_D0gamma();
  }
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0hst_D0pi0();
  }
  virtual RooDstD0BG &pdfDelta_misId_MisRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_misId_MisRec();
  }
  virtual RooDstD0BG &pdfDelta_misId_Bu2D0h() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_misId_Bu2D0h();
  }
  virtual RooDstD0BG &pdfDelta_misId_PartRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_misId_PartRec();
  }

  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma();
  }
  virtual RooCBShape &pdfBu_Bu2Dst0h_D0gamma_FAVasSUP() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma_FAVasSUP();
  }
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooGaussian &pdfBu_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bd2Dsth();
  }
  virtual RooAbsPdf &pdfBu_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2D0hst();
  }
  virtual RooAddPdf &pdfBu_Bu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0hst_D0gamma();
  }
  virtual RooGaussian &pdfBu_Bu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0hst_D0pi0();
  }
  virtual RooCBShape &pdfBu_Bu2Dst0h_D0pi0_FAVasSUP() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0pi0_FAVasSUP();
  }
  virtual RooCruijff &pdfBu_MisRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_MisRec();
  }
  virtual RooCruijff &pdfBu_Bu2D0h() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2D0h();
  }
  virtual RooAbsPdf &pdfBu_PartRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_PartRec();
  }
  virtual RooAbsPdf &pdfBu_Bs2Dst0Kpi() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bs2Dst0Kpi();
  }
  virtual RooAbsPdf &pdfBu_Bs2D0Kpi() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bs2D0Kpi();
  }

  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooGaussian &pdfBu_misId_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bd2Dsth();
  }
  virtual RooGaussian &pdfBu_misId_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2D0hst();
  }
  virtual RooAddPdf &pdfBu_misId_Bu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0hst_D0gamma();
  }
  virtual RooCBShape &pdfBu_misId_Bu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0hst_D0pi0();
  }
  virtual RooAbsPdf &pdfBu_misId_MisRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_MisRec();
  }
  virtual RooCruijff &pdfBu_misId_Bu2D0h() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2D0h();
  }
  virtual RooCruijff &pdfBu_misId_PartRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_PartRec();
  }

  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfBuPartial_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0pi0();
  }
  virtual RooGaussian &pdfBuPartial_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooAbsPdf &pdfBuPartial_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooGaussian &pdfBuPartial_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bd2Dsth();
  }
  virtual RooGaussian &pdfBuPartial_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2D0hst();
  }
  virtual RooGaussian &pdfBuPartial_Bu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0hst_D0gamma();
  }
  virtual RooGaussian &pdfBuPartial_Bu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0hst_D0pi0();
  }
  virtual RooCBShape &pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP();
  }
  virtual RooCruijff &pdfBuPartial_MisRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_MisRec();
  }
  virtual RooCruijff &pdfBuPartial_Bu2D0h() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2D0h();
  }
  virtual RooCruijff &pdfBuPartial_PartRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_PartRec();
  }
  virtual RooAbsPdf &pdfBuPartial_Bs2Dst0Kpi() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bs2Dst0Kpi();
  }
  virtual RooAbsPdf &pdfBuPartial_Bs2D0Kpi() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bs2D0Kpi();
  }

  virtual RooAbsPdf &pdfBuPartial_misId_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooCBShape &pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN();
  }
  virtual RooCBShape &pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN();
  }
  virtual RooGaussian &pdfBuPartial_misId_Bd2Dsth() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bd2Dsth();
  }
  virtual RooGaussian &pdfBuPartial_misId_Bu2D0hst() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2D0hst();
  }
  virtual RooGaussian &pdfBuPartial_misId_Bu2Dst0hst_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2Dst0hst_D0gamma();
  }
  virtual RooAddPdf &pdfBuPartial_misId_Bu2Dst0hst_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2Dst0hst_D0pi0();
  }
  virtual RooCruijff &pdfBuPartial_misId_MisRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_MisRec();
  }
  virtual RooCruijff &pdfBuPartial_misId_Bu2D0h() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_Bu2D0h();
  }
  virtual RooCruijff &pdfBuPartial_misId_PartRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_misId_PartRec();
  }

  // Map of PDF objects with a unique ID for each identical PDF (PDF + ID =
  // singleton)
  // This is just a parameter/argument, you can call it anything you want
  Pdf(int whateverId);
  virtual ~Pdf() {}

 private:
  // Declaring a function inside a class of const will not change any of the
  // variables inside of the object
};

// PdfBase is supposed to be general, so the template variables are not known at
// compile time. Any variables requiring a template in the constructor must
// therefore be initialised in Pdf.
// We initialise the variables in the text of the constructor as a pointer
// because otherwise we get the error of RooFit crashing we re-assigning a
// variable
// We have to do it in the text of the constructor because it's a field of
// PDFBase, not PDF
// Can't make a list of different types. Pdfs have different types because of
// the templating. They all inheret from PDFBase, so we can make a list of
// PDFBase objects
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
Pdf<_neutral, _bachelor, _daughters, _charge>::Pdf(int uniqueId)
    : PdfBase(uniqueId, _neutral, _bachelor, _daughters, _charge) {}

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::CreateBuAddPdf() {
  if (_neutral == Neutral::gamma) {
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_Bu2Dst0h_D0gamma());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_Bu_Bu2Dst0h_D0gamma());
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bu2Dst0h_D0gamma());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Bu_Bu2Dst0h_D0gamma());
    // if (_daughters == Daughters::pik) {
    //   PdfBase::functionsBu_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
    //                                 .pdfBu_Bu2Dst0h_D0gamma_FAVasSUP());
    //   PdfBase::yieldsBu_.add(
    //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
    //           PdfBase::uniqueId_)
    //           .N_trueId_Bu_Bu2Dst0h_D0gamma_FAVasSUP());
    // }
  }
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bu2Dst0h_D0pi0());
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_misId_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_Bu_Bu2Dst0h_D0pi0());
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_Bu2Dst0h_D0gamma_WN());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bu2Dst0h_D0gamma_WN());
  if (_bachelor == Bachelor::k || _neutral == Neutral::gamma) {
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bu2Dst0h_D0gamma_WN());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Bu_Bu2Dst0h_D0gamma_WN());
  }
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bu2Dst0h_D0pi0_WN());
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_misId_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_Bu_Bu2Dst0h_D0pi0_WN());
  // PdfBase::functionsBu_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBu_Bd2Dsth());
  // PdfBase::yieldsBu_.add(
  //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_Bu_Bd2Dsth());
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_Bu2D0hst());
  PdfBase::yieldsBu_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Bu_Bu2D0hst());
  // PdfBase::functionsBu_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBu_Bu2Dst0hst_D0pi0());
  // PdfBase::yieldsBu_.add(
  //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_Bu_Bu2Dst0hst_D0pi0());
  // if (_neutral == Neutral::gamma) {
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_Bu2Dst0hst_D0gamma());
  //   PdfBase::yieldsBu_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_trueId_Bu_Bu2Dst0hst_D0gamma());
  // }
  if (_bachelor == Bachelor::k) {
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_misId_Bd2Dsth());
  //   PdfBase::yieldsBu_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Bu_Bd2Dsth());
    PdfBase::functionsBu_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bu2D0hst());
    PdfBase::yieldsBu_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Bu_Bu2D0hst());
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_misId_Bu2Dst0hst_D0pi0());
  //   PdfBase::yieldsBu_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Bu_Bu2Dst0hst_D0pi0());
  //   if (_neutral == Neutral::gamma) {
  //     PdfBase::functionsBu_.add(
  //         NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //             .pdfBu_misId_Bu2Dst0hst_D0gamma());
  //     PdfBase::yieldsBu_.add(
  //         Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //             PdfBase::uniqueId_)
  //             .N_misId_Bu_Bu2Dst0hst_D0gamma());
  //   }
  }
  // if (_daughters == Daughters::pik) {
  //   PdfBase::functionsBu_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                                 .pdfBu_Bu2Dst0h_D0pi0_FAVasSUP());
  //   PdfBase::yieldsBu_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_trueId_Bu_Bu2Dst0h_D0pi0_FAVasSUP());
  // }
  // PdfBase::functionsBu_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBu_MisRec());
  // PdfBase::yieldsBu_.add(
  //     Yields<_neutral, _bachelor, _daughters,
  //     _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_Bu_MisRec());
  // // PdfBase::functionsBu_.add(
  // //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  // //         .pdfBu_Bu2D0h());
  // // PdfBase::yieldsBu_.add(
  // //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  // //         PdfBase::uniqueId_)
  // //         .N_trueId_Bu_Bu2D0h());
  // PdfBase::functionsBu_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBu_PartRec());
  // PdfBase::yieldsBu_.add(
  //     Yields<_neutral, _bachelor, _daughters,
  //     _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_Bu_PartRec());
  // if (_bachelor == Bachelor::k) {
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_misId_MisRec());
  //   PdfBase::yieldsBu_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Bu_MisRec());
  //   // PdfBase::functionsBu_.add(
  //   //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //   //         .pdfBu_misId_Bu2D0h());
  //   // PdfBase::yieldsBu_.add(
  //   //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //   //         PdfBase::uniqueId_)
  //   //         .N_misId_Bu_Bu2D0h());
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_misId_PartRec());
  //   PdfBase::yieldsBu_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Bu_PartRec());
  //   if (_daughters != Daughters::kpi && Configuration::Get().runADS() ==
  //   true) {
  //     std::cout << "ADS mode: include BS\n";
  //     PdfBase::functionsBu_.add(
  //         NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //             .pdfBu_Bs2Dst0Kpi());
  //     PdfBase::yieldsBu_.add(
  //         Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //             PdfBase::uniqueId_)
  //             .N_trueId_Bu_Bs2Dst0Kpi());
  //     PdfBase::functionsBu_.add(
  //         NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //             .pdfBu_Bs2D0Kpi());
  //     PdfBase::yieldsBu_.add(
  //         Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //             PdfBase::uniqueId_)
  //             .N_trueId_Bu_Bs2D0Kpi());
  //   }
  // }

  PdfBase::addPdfBu_ = std::unique_ptr<RooAddPdf>(
      new RooAddPdf(("addPdfBu_" + ComposeName(PdfBase::uniqueId_, _neutral,
                                               _bachelor, _daughters, _charge))
                        .c_str(),
                    "", PdfBase::functionsBu_, PdfBase::yieldsBu_));
}

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::CreateBuPartialAddPdf() {
  if (_neutral != Neutral::gamma) {
    throw std::runtime_error("Cannt call CreateBuPartialPdf() for pi0 mode.");
  }
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0h_D0gamma());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2Dst0h_D0gamma());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2Dst0h_D0pi0());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_misId_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_BuPartial_Bu2Dst0h_D0pi0());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0h_D0gamma_WN());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2Dst0h_D0gamma_WN());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_misId_Bu2Dst0h_D0gamma_WN());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_BuPartial_Bu2Dst0h_D0gamma_WN());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2Dst0h_D0pi0_WN());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_misId_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_BuPartial_Bu2Dst0h_D0pi0_WN());
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_Bd2Dsth());
  // PdfBase::yieldsBuPartial_.add(
  //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_BuPartial_Bd2Dsth());
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2D0hst());
  PdfBase::yieldsBuPartial_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_BuPartial_Bu2D0hst());
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_Bu2Dst0hst_D0pi0());
  // PdfBase::yieldsBuPartial_.add(
  //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_BuPartial_Bu2Dst0hst_D0pi0());
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_Bu2Dst0hst_D0gamma());
  // PdfBase::yieldsBuPartial_.add(
  //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_BuPartial_Bu2Dst0hst_D0gamma());
  if (_bachelor == Bachelor::k) {
  //   PdfBase::functionsBuPartial_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBuPartial_misId_Bd2Dsth());
  //   PdfBase::yieldsBuPartial_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_BuPartial_Bd2Dsth());
    PdfBase::functionsBuPartial_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBuPartial_misId_Bu2D0hst());
    PdfBase::yieldsBuPartial_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_BuPartial_Bu2D0hst());
  //   PdfBase::functionsBuPartial_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBuPartial_misId_Bu2Dst0hst_D0pi0());
  //   PdfBase::yieldsBuPartial_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_BuPartial_Bu2Dst0hst_D0pi0());
  //     PdfBase::functionsBuPartial_.add(
  //         NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //             .pdfBuPartial_misId_Bu2Dst0hst_D0gamma());
  //     PdfBase::yieldsBuPartial_.add(
  //         Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //             PdfBase::uniqueId_)
  //             .N_misId_BuPartial_Bu2Dst0hst_D0gamma());
  }
  // if (_daughters == Daughters::pik) {
  //   PdfBase::functionsBuPartial_.add(
  //       NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //           .pdfBuPartial_Bu2Dst0h_D0pi0_FAVasSUP());
  //   PdfBase::yieldsBuPartial_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_trueId_BuPartial_Bu2Dst0h_D0pi0_FAVasSUP());
  // }
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_MisRec());
  // PdfBase::yieldsBuPartial_.add(
  //     Yields<_neutral, _bachelor, _daughters,
  //     _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_BuPartial_MisRec());
  // // PdfBase::functionsBuPartial_.add(
  // //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  // //         .pdfBuPartial_Bu2D0h());
  // // PdfBase::yieldsBuPartial_.add(
  // //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  // //         PdfBase::uniqueId_)
  // //         .N_trueId_BuPartial_Bu2D0h());
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_PartRec());
  // PdfBase::yieldsBuPartial_.add(
  //     Yields<_neutral, _bachelor, _daughters,
  //     _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_BuPartial_PartRec());
  // if (_bachelor == Bachelor::k) {
  //   PdfBase::functionsBuPartial_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBuPartial_misId_MisRec());
  //   PdfBase::yieldsBuPartial_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_BuPartial_MisRec());
  //   // PdfBase::functionsBuPartial_.add(
  //   //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //   //         .pdfBuPartial_misId_Bu2D0h());
  //   // PdfBase::yieldsBuPartial_.add(
  //   //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //   //         PdfBase::uniqueId_)
  //   //         .N_misId_BuPartial_Bu2D0h());
  //   PdfBase::functionsBuPartial_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBuPartial_misId_PartRec());
  //   PdfBase::yieldsBuPartial_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_BuPartial_PartRec());
  //   if (_daughters != Daughters::kpi && Configuration::Get().runADS() ==
  //   true) {
  //     std::cout << "ADS mode: include BS\n";
  //     PdfBase::functionsBuPartial_.add(
  //         NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //             .pdfBuPartial_Bs2Dst0Kpi());
  //     PdfBase::yieldsBuPartial_.add(
  //         Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //             PdfBase::uniqueId_)
  //             .N_trueId_BuPartial_Bs2Dst0Kpi());
  //     PdfBase::functionsBuPartial_.add(
  //         NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //             .pdfBuPartial_Bs2D0Kpi());
  //     PdfBase::yieldsBuPartial_.add(
  //         Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //             PdfBase::uniqueId_)
  //             .N_trueId_BuPartial_Bs2D0Kpi());
  //   }
  // }

  PdfBase::addPdfBuPartial_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("addPdfBuPartial_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                                        _daughters, _charge))
          .c_str(),
      "", PdfBase::functionsBuPartial_, PdfBase::yieldsBuPartial_));
}

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::CreateDeltaAddPdf() {
  if (_neutral == Neutral::gamma) {
    PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                     .pdfDelta_Bu2Dst0h_D0gamma());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_trueId_Delta_Bu2Dst0h_D0gamma());
    PdfBase::functionsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bu2Dst0h_D0gamma());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Delta_Bu2Dst0h_D0gamma());
    // if (_daughters == Daughters::pik) {
    //   PdfBase::functionsDelta_.add(
    //       NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
    //           .pdfDelta_Bu2Dst0h_D0gamma_FAVasSUP());
    //   PdfBase::yieldsDelta_.add(
    //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
    //           PdfBase::uniqueId_)
    //           .N_trueId_Delta_Bu2Dst0h_D0gamma_FAVasSUP());
    // }
  }
  PdfBase::functionsDelta_.add(
      NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_Bu2Dst0h_D0pi0());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bu2Dst0h_D0pi0());
  PdfBase::functionsDelta_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfDelta_misId_Bu2Dst0h_D0pi0());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_Delta_Bu2Dst0h_D0pi0());
  PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                   .pdfDelta_Bu2Dst0h_D0gamma_WN());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bu2Dst0h_D0gamma_WN());
  if (_bachelor == Bachelor::k || _neutral == Neutral::gamma) {
    PdfBase::functionsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bu2Dst0h_D0gamma_WN());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Delta_Bu2Dst0h_D0gamma_WN());
  }
  PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                   .pdfDelta_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bu2Dst0h_D0pi0_WN());
  PdfBase::functionsDelta_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfDelta_misId_Bu2Dst0h_D0pi0_WN());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_misId_Delta_Bu2Dst0h_D0pi0_WN());
  // PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                                  .pdfDelta_Bd2Dsth());
  // PdfBase::yieldsDelta_.add(
  //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_Delta_Bd2Dsth());
  PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
                                   .pdfDelta_Bu2D0hst());
  PdfBase::yieldsDelta_.add(
      Yields<_neutral, _bachelor, _daughters, _charge>::Get(PdfBase::uniqueId_)
          .N_trueId_Delta_Bu2D0hst());
  if (_bachelor == Bachelor::k) {
  //   PdfBase::functionsDelta_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfDelta_misId_Bd2Dsth());
  //   PdfBase::yieldsDelta_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Delta_Bd2Dsth());
    PdfBase::functionsDelta_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bu2D0hst());
    PdfBase::yieldsDelta_.add(
        Yields<_neutral, _bachelor, _daughters, _charge>::Get(
            PdfBase::uniqueId_)
            .N_misId_Delta_Bu2D0hst());
  //   PdfBase::functionsDelta_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfDelta_misId_Bu2Dst0hst_D0pi0());
  //   PdfBase::yieldsDelta_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Delta_Bu2Dst0hst_D0pi0());
  //   if (_neutral == Neutral::gamma) {
  //     PdfBase::functionsDelta_.add(
  //         NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //             .pdfDelta_misId_Bu2Dst0hst_D0gamma());
  //     PdfBase::yieldsDelta_.add(
  //         Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //             PdfBase::uniqueId_)
  //             .N_misId_Delta_Bu2Dst0hst_D0gamma());
  //   }
  }
  // if (_daughters == Daughters::pik) {
  //   PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                                    .pdfDelta_Bu2Dst0h_D0pi0_FAVasSUP());
  //   PdfBase::yieldsDelta_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_trueId_Delta_Bu2Dst0h_D0pi0_FAVasSUP());
  // }
  // PdfBase::functionsDelta_.add(
  //     NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_MisRec());
  // PdfBase::yieldsDelta_.add(
  //     Yields<_neutral, _bachelor, _daughters,
  //     _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_Delta_MisRec());
  // // PdfBase::functionsDelta_.add(
  // //     NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_Bu2D0h());
  // // PdfBase::yieldsDelta_.add(
  // //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  // //         PdfBase::uniqueId_)
  // //         .N_trueId_Delta_Bu2D0h());
  // PdfBase::functionsDelta_.add(
  //     NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_PartRec());
  // PdfBase::yieldsDelta_.add(
  //     Yields<_neutral, _bachelor, _daughters,
  //     _charge>::Get(PdfBase::uniqueId_)
  //         .N_trueId_Delta_PartRec());
  // if (_bachelor == Bachelor::k) {
  //   PdfBase::functionsDelta_.add(
  //       NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_misId_MisRec());
  //   PdfBase::yieldsDelta_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Delta_MisRec());
  //   // PdfBase::functionsDelta_.add(
  //   //
  //   NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_misId_Bu2D0h());
  //   // PdfBase::yieldsDelta_.add(
  //   //     Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //   //         PdfBase::uniqueId_)
  //   //         .N_misId_Delta_Bu2D0h());
  //   PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                                    .pdfDelta_misId_PartRec());
  //   PdfBase::yieldsDelta_.add(
  //       Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //           PdfBase::uniqueId_)
  //           .N_misId_Delta_PartRec());
  //   if (_daughters != Daughters::kpi && Configuration::Get().runADS() ==
  //   true) {
  //     std::cout << "ADS mode: include BS\n";
  //     PdfBase::functionsDelta_.add(
  //         NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //             .pdfDelta_Bs2Dst0Kpi());
  //     PdfBase::yieldsDelta_.add(
  //         Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //             PdfBase::uniqueId_)
  //             .N_trueId_Delta_Bs2Dst0Kpi());
  //     PdfBase::functionsDelta_.add(
  //         NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //             .pdfDelta_Bs2D0Kpi());
  //     PdfBase::yieldsDelta_.add(
  //         Yields<_neutral, _bachelor, _daughters, _charge>::Get(
  //             PdfBase::uniqueId_)
  //             .N_trueId_Delta_Bs2D0Kpi());
  //   }
  // }

  PdfBase::addPdfDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("addPdfDelta_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                                    _daughters, _charge))
          .c_str(),
      "", PdfBase::functionsDelta_, PdfBase::yieldsDelta_));
}
