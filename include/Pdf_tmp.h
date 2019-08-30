#pragma once
#include <map>
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooSimultaneous.h"

class PdfBase {
 public:
  void AddToSimultaneousPdf(RooSimultaneous &) const;

  inline int uniqueId() const { return uniqueId_; }
  inline Mass mass() const { return mass_; }
  inline Bachelor bachelor() const { return bachelor_; }
  inline Neutral neutral() const { return neutral_; }
  inline Daughters daughters() const { return daughters_; }
  inline Charge charge() const { return charge_; }

  inline RooArgList &yields() { return yields_; }
  inline RooArgList &functions() { return functions_; }
  inline RooAddPdf &addPdf() { return *addPdf_; }

  // std::unique_ptr<RooAddPdf> addPdf_;

  virtual RooAbsReal &N_tot_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfBu_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const = 0;
  virtual RooCBShape &pdfBu_Bu2Dst0h_D0pi0() const = 0;
  virtual RooDstD0BG &pdfDelta_MisRec() const = 0;
  virtual RooCBShape &pdfBu_MisRec() const = 0;
  virtual RooDstD0BG &pdfDelta_Bu2D0h() const = 0;
  virtual RooCruijff &pdfBu_Bu2D0h() const = 0;

  // If a function or a method is defined in the header file, and the class is
  // not a template, it should be inline because otherwise the linker might fail
  // as the function will be present in multiple compiltation unit
  // function needs to be const when you don't change the object when the
  // function is called
  inline std::string CategoryName() const {
    return ComposeFittingName(mass_, neutral_, bachelor_, daughters_,
                              charge_);
  }

 protected:  // Can be accessed by deriving classes
  PdfBase(int uniqueId, Mass mass, Neutral neutral, Bachelor bachelor,
          Daughters daughters, Charge charge);
  virtual ~PdfBase() {}

  int uniqueId_;
  Mass mass_;
  Neutral neutral_;
  Bachelor bachelor_;
  Daughters daughters_;
  Charge charge_;

  RooArgList yields_;
  RooArgList functions_;
  std::unique_ptr<RooAddPdf> addPdf_;
};

template <Mass _mass, Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
class Pdf : public PdfBase {
  using This_t = Pdf<_mass, _neutral, _bachelor, _daughters, _charge>;

 public:
  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId);  // Check if uniqueId already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId, std::make_shared<This_t>(uniqueId))
               .first;
    }
    return *it->second;
  }

  void CreateRooAddPdf();
  void AssignMisIdYields();

  // pdf_Bu2Dst0h_Dst02D0neut are made in another class, but we only deal with
  // PDF in the
  // executable. Give PDF functions to retrieve them
  // It shouldn't be private, it sould be protected then it can be accessed by
  // inheriting classes
  RooFormulaVar &N_misId_Bu2Dst0h_D0gamma() {
    return *N_misId_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_BuDelta_misId_Bu2Dst0h_D0gamma() {
    return *N_BuDelta_misId_Bu2Dst0h_D0gamma_;
  }
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .N_tot_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfBu_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2Dst0h_D0pi0();
  }
  virtual RooCBShape &pdfBu_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0pi0();
  }
  virtual RooDstD0BG &pdfDelta_MisRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_MisRec();
  }
  virtual RooCBShape &pdfBu_MisRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_MisRec();
  }
  virtual RooDstD0BG &pdfDelta_Bu2D0h() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_Bu2D0h();
  }
  virtual RooCruijff &pdfBu_Bu2D0h() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2D0h();
  }

  // Map of PDF objects with a unique ID for each identical PDF (PDF + ID =
  // singleton)
  // This is just a parameter/argument, you can call it anything you want
  Pdf(int whateverId);
  virtual ~Pdf() {}

 private:
  // Declaring a function inside a class of const will not change any of the
  // variables inside of the object
  std::unique_ptr<RooFormulaVar> N_misId_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_BuDelta_misId_Bu2Dst0h_D0gamma_;
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
template <Mass _mass, Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
// How does it know it's the same unique ID when one is uniqueId_ and the other
// uniqueId?
Pdf<_mass, _neutral, _bachelor, _daughters, _charge>::Pdf(int uniqueId)
    : PdfBase(uniqueId, _mass, _neutral, _bachelor, _daughters, _charge) {
  CreateRooAddPdf();
}

// Whatever you assign as a template argument MUST BE RESOLVABLE AT COMPILE
// TIME
template <Mass _mass, Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
void Pdf<_mass, _neutral, _bachelor, _daughters,
         _charge>::CreateRooAddPdf() {
  if (_mass == Mass::delta) {
    PdfBase::functions_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_Bu2Dst0h_D0gamma());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_Bu2Dst0h_D0gamma());
    // misId delta mass shape same as non misId
    PdfBase::functions_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_misId_Bu2Dst0h_D0gamma());
    PdfBase::yields_.add(
        PdfBase::N_BuDelta_misId_Bu2Dst0h_D0gamma_);
    PdfBase::functions_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_Bu2Dst0h_D0pi0());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_Bu2Dst0h_D0pi0());
    PdfBase::functions_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_MisRec());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_MisRec());
    PdfBase::functions_.add(
        NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
            .pdfDelta_Bu2D0h());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Delta_Bu2D0h());
  } else {
    PdfBase::functions_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_Bu2Dst0h_D0gamma());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Bu_Bu2Dst0h_D0gamma());
    PdfBase::functions_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_misId_Bu2Dst0h_D0gamma());
    PdfBase::yields_.add(
        PdfBase::N_BuDelta_misId_Bu2Dst0h_D0gamma_);
    PdfBase::functions_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_Bu2Dst0h_D0pi0());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Bu_Bu2Dst0h_D0pi0());
    PdfBase::functions_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_MisRec());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Bu_MisRec());
    PdfBase::functions_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .pdfBu_Bu2D0h());
    PdfBase::yields_.add(
        NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
            .N_Bu_Bu2D0h());
  }

  PdfBase::addPdf_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("pdf_" + ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                            _daughters, _charge))
          .c_str(),
      ("pdf_" + ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                            _daughters, _charge))
          .c_str(),
      PdfBase::functions_, PdfBase::yields_));
}

// Assign miss-ID yields in a separate function after the PDF objects have been
// constructed to avoid cyclic dependancy (deadlock)
template <Mass _mass, Neutral _neutral, Bachelor _bachelor,
          Daughters _daughters, Charge _charge>
void Pdf<_mass, _neutral, _bachelor, _daughters, _charge>::AssignMisIdYields() {
  switch (_bachelor) {
    case Bachelor::pi:
      // N_misId needs to be shared across by and delta mass: can't define in
      // Pdf.h But can't just put in SpecialisedVars (not specialised by mass)
      // as the whole idea is that cyclic dependancy is only avoided if we
      // construct the yields first in Pdf.h IF ENDIF??? Make Pdf not templated
      // on mass? YES - remove specialisation on mass and make 2 addPdfs
      // (addBuPdfs and addDeltaPdfs) Remove specialisation from point of
      // previous commit (everything working) When specialisation is removed,
      // implement, implement misId yield assignment as bellow
      PdfBase::N_misId_Bu2Dst0h_D0gamma_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_misId_Bu2Dst0h_D0gamma_" +
               ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                           _daughters, _charge))
                  .c_str(),
              "@0*(1-@1)",
              RooArgList(
                  Pdf<_mass, _neutral, Bachelor::k, _daughters, _charge>::Get()
                      .N_tot_Bu2Dst0h_D0gamma(),
                  NeutralBachelorVars<_neutral, _bachelor>::Get()
                      .pidEff_Bu2Dst0h_D0gamma())));
      if (Configuration::Get().fit1D() == true) {
        PdfBase::N_BuDelta_misId_Bu2Dst0h_D0gamma_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_BuDelta_misId_Bu2Dst0h_D0gamma_" +
                 ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "@0*(1-@1)",
                RooArgList(Pdf<_mass, _neutral, Bachelor::k, _daughters,
                               _charge>::Get()
                               .N_tot_Bu2Dst0h_D0gamma(),
                           NeutralBachelorVars<_neutral, _bachelor>::Get()
                               .pidEff_Bu2Dst0h_D0gamma())));
      } else {
        if (_mass == Mass::buDelta) {
          PdfBase::N_BuDelta_misId_Bu2Dst0h_D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("N_BuDelta_misId_Bu2Dst0h_D0gamma_" +
                   ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                               _daughters, _charge))
                      .c_str(),
                  "(@0/@1)*@2",
                  RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get()
                                 .deltaCutEffMisId_Bu2Dst0h_D0gamma(),
                             NeutralBachelorVars<_neutral, _bachelor>::Get()
                                 .orEffMisId_Bu2Dst0h_D0gamma(),
                             pdfBase::N_misId_Bu2Dst0h_D0gamma_)));
        } else {
          PdfBase::N_BuDelta_misId_Bu2Dst0h_D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("N_BuDelta_misId_Bu2Dst0h_D0gamma_" +
                   ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                               _daughters, _charge))
                      .c_str(),
                  "(@0/@1)*@2",
                  RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get()
                                 .buDeltaCutEffMisId_Bu2Dst0h_D0gamma(),
                             NeutralBachelorVars<_neutral, _bachelor>::Get()
                                 .orEffMisId_Bu2Dst0h_D0gamma(),
                             pdfBase::N_misId_Bu2Dst0h_D0gamma_)));
        }
      }
      break;
    case Bachelor::k:
      PdfBase::N_misId_Bu2Dst0h_D0gamma_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_misId_Bu2Dst0h_D0gamma_" +
               ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                           _daughters, _charge))
                  .c_str(),
              "@0*(1-@1)",
              RooArgList(
                  Pdf<_mass, _neutral, Bachelor::pi, _daughters, _charge>::Get()
                      .N_tot_Bu2Dst0h_D0gamma(),
                  NeutralBachelorVars<_neutral, _bachelor>::Get()
                      .pidEff_Bu2Dst0h_D0gamma())));
      if (Configuration::Get().fit1D() == true) {
        PdfBase::N_BuDelta_misId_Bu2Dst0h_D0gamma_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_BuDelta_misId_Bu2Dst0h_D0gamma_" +
                 ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "@0*(1-@1)",
                RooArgList(Pdf<_mass, _neutral, Bachelor::pi, _daughters,
                               _charge>::Get()
                               .N_tot_Bu2Dst0h_D0gamma(),
                           NeutralBachelorVars<_neutral, _bachelor>::Get()
                               .pidEff_Bu2Dst0h_D0gamma())));
      } else {
        if (_mass == Mass::buDelta) {
          PdfBase::N_BuDelta_misId_Bu2Dst0h_D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("N_BuDelta_misId_Bu2Dst0h_D0gamma_" +
                   ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                               _daughters, _charge))
                      .c_str(),
                  "(@0/@1)*@2",
                  RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get()
                                 .deltaCutEffMisId_Bu2Dst0h_D0gamma(),
                             NeutralBachelorVars<_neutral, _bachelor>::Get()
                                 .orEffMisId_Bu2Dst0h_D0gamma(),
                             pdfBase::N_misId_Bu2Dst0h_D0gamma_)));
        } else {
          PdfBase::N_BuDelta_misId_Bu2Dst0h_D0gamma_ =
              std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                  ("N_BuDelta_misId_Bu2Dst0h_D0gamma_" +
                   ComposeName(PdfBase::uniqueId_, _mass, _neutral, _bachelor,
                               _daughters, _charge))
                      .c_str(),
                  "(@0/@1)*@2",
                  RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get()
                                 .buDeltaCutEffMisId_Bu2Dst0h_D0gamma(),
                             NeutralBachelorVars<_neutral, _bachelor>::Get()
                                 .orEffMisId_Bu2Dst0h_D0gamma(),
                             pdfBase::N_misId_Bu2Dst0h_D0gamma_)));
        }
      }
      break;
  }
}
