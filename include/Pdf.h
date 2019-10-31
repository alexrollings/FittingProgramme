#include "NeutralVars.h"
#include "NeutralBachelorVars.h"
#include "NeutralBachelorChargeVars.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooSimultaneous.h"

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

  RooAbsReal &N_misId_Bu2Dst0h_D0gamma() { return *N_misId_Bu2Dst0h_D0gamma_; }
  RooFormulaVar &N_Bu_misId_Bu2Dst0h_D0gamma() {
    return *N_Bu_misId_Bu2Dst0h_D0gamma_;
  }
  RooFormulaVar &N_Delta_misId_Bu2Dst0h_D0gamma() {
    return *N_Delta_misId_Bu2Dst0h_D0gamma_;
  }
  RooAbsReal &N_misId_Bu2Dst0h_D0pi0() { return *N_misId_Bu2Dst0h_D0pi0_; }
  RooFormulaVar &N_Bu_misId_Bu2Dst0h_D0pi0() {
    return *N_Bu_misId_Bu2Dst0h_D0pi0_;
  }
  RooFormulaVar &N_Delta_misId_Bu2Dst0h_D0pi0() {
    return *N_Delta_misId_Bu2Dst0h_D0pi0_;
  }
  RooAbsReal &N_misId_MisRec() { return *N_misId_MisRec_; }
  RooFormulaVar &N_Bu_misId_MisRec() { return *N_Bu_misId_MisRec_; }
  RooFormulaVar &N_Delta_misId_MisRec() { return *N_Delta_misId_MisRec_; }
  RooAbsReal &N_misId_Bu2D0h() { return *N_misId_Bu2D0h_; }
  RooFormulaVar &N_Bu_misId_Bu2D0h() { return *N_Bu_misId_Bu2D0h_; }
  RooFormulaVar &N_Delta_misId_Bu2D0h() { return *N_Delta_misId_Bu2D0h_; }
  RooAbsReal &N_misId_PartRec() { return *N_misId_PartRec_; }
  RooFormulaVar &N_Bu_misId_PartRec() {
    return *N_Bu_misId_PartRec_;
  }
  RooFormulaVar &N_Delta_misId_PartRec() {
    return *N_Delta_misId_PartRec_;
  }

  // std::unique_ptr<RooAddPdf> addPdf_;

  virtual RooAbsReal &N_tot_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma() const = 0;
  virtual RooCBShape &pdfBuPartial_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const = 0;
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAddPdf &pdfBuPartial_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0h_D0pi0() const = 0;
  virtual RooAbsReal &N_tot_MisRec() const = 0;
  virtual RooDstD0BG &pdfDelta_MisRec() const = 0;
  virtual RooCruijff &pdfBu_MisRec() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_MisRec() const = 0;
  virtual RooAbsPdf &pdfBu_misId_MisRec() const = 0;
  virtual RooAbsReal &N_tot_Bu2D0h() const = 0;
  virtual RooDstD0BG &pdfDelta_Bu2D0h() const = 0;
  virtual RooCruijff &pdfBu_Bu2D0h() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_Bu2D0h() const = 0;
  virtual RooCruijff &pdfBu_misId_Bu2D0h() const = 0;
  virtual RooAbsReal &N_tot_PartRec() const = 0;
  virtual RooDstD0BG &pdfDelta_PartRec() const = 0;
  virtual RooAbsPdf &pdfBu_PartRec() const = 0;
  virtual RooDstD0BG &pdfDelta_misId_PartRec() const = 0;
  virtual RooCruijff &pdfBu_misId_PartRec() const = 0;

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

  std::unique_ptr<RooAbsReal> N_misId_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Bu_misId_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooFormulaVar> N_Delta_misId_Bu2Dst0h_D0gamma_;
  std::unique_ptr<RooAbsReal> N_misId_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Bu_misId_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooFormulaVar> N_Delta_misId_Bu2Dst0h_D0pi0_;
  std::unique_ptr<RooAbsReal> N_misId_MisRec_;
  std::unique_ptr<RooFormulaVar> N_Bu_misId_MisRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_misId_MisRec_;
  std::unique_ptr<RooAbsReal> N_misId_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_Bu_misId_Bu2D0h_;
  std::unique_ptr<RooFormulaVar> N_Delta_misId_Bu2D0h_;
  std::unique_ptr<RooAbsReal> N_misId_PartRec_;
  std::unique_ptr<RooFormulaVar> N_Bu_misId_PartRec_;
  std::unique_ptr<RooFormulaVar> N_Delta_misId_PartRec_;
};

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
class Pdf : public PdfBase {
  using This_t = Pdf<_neutral, _bachelor, _daughters, _charge>;

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

  void CreateBuAddPdf();
  void CreateBuPartialAddPdf();
  void CreateDeltaAddPdf();
  void AssignMisIdYields();

  // pdf_Bu2Dst0h_Dst02D0neut are made in another class, but we only deal with
  // PDF in the
  // executable. Give PDF functions to retrieve them
  // It shouldn't be private, it sould be protected then it can be accessed by
  // inheriting classes
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(uniqueId_)
        .N_tot_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfDelta_Bu2Dst0h_D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0gamma();
  }
  virtual RooCBShape &pdfBuPartial_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfDelta_misId_Bu2Dst0h_D0gamma() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0gamma() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0gamma();
  }
  virtual RooAbsReal &N_tot_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(uniqueId_)
        .N_tot_Bu2Dst0h_D0pi0();
  }
  virtual RooAddPdf &pdfDelta_Bu2Dst0h_D0pi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfBu_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2Dst0h_D0pi0();
  }
  virtual RooAddPdf &pdfBuPartial_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBuPartial_Bu2Dst0h_D0pi0();
  }
  virtual RooAddPdf &pdfDelta_misId_Bu2Dst0h_D0pi0() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsPdf &pdfBu_misId_Bu2Dst0h_D0pi0() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2Dst0h_D0pi0();
  }
  virtual RooAbsReal &N_tot_MisRec() const {
    return NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(uniqueId_)
        .N_tot_MisRec();
  }
  virtual RooDstD0BG &pdfDelta_MisRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_MisRec();
  }
  virtual RooCruijff &pdfBu_MisRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_MisRec();
  }
  virtual RooDstD0BG &pdfDelta_misId_MisRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_misId_MisRec();
  }
  virtual RooAbsPdf &pdfBu_misId_MisRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_MisRec();
  }
  virtual RooAbsReal &N_tot_Bu2D0h() const {
    return NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(uniqueId_)
        .N_tot_Bu2D0h();
  }
  virtual RooDstD0BG &pdfDelta_Bu2D0h() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_Bu2D0h();
  }
  virtual RooCruijff &pdfBu_Bu2D0h() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_Bu2D0h();
  }
  virtual RooDstD0BG &pdfDelta_misId_Bu2D0h() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_misId_Bu2D0h();
  }
  virtual RooCruijff &pdfBu_misId_Bu2D0h() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_Bu2D0h();
  }
  virtual RooAbsReal &N_tot_PartRec() const {
    return NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(uniqueId_)
        .N_tot_PartRec();
  }
  virtual RooDstD0BG &pdfDelta_PartRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_).pdfDelta_PartRec();
  }
  virtual RooAbsPdf &pdfBu_PartRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_PartRec();
  }
  virtual RooDstD0BG &pdfDelta_misId_PartRec() const {
    return NeutralVars<_neutral>::Get(uniqueId_)
        .pdfDelta_misId_PartRec();
  }
  virtual RooCruijff &pdfBu_misId_PartRec() const {
    return NeutralBachelorVars<_neutral, _bachelor>::Get(uniqueId_)
        .pdfBu_misId_PartRec();
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
// How does it know it's the same unique ID when one is uniqueId_ and the other
// uniqueId?
Pdf<_neutral, _bachelor, _daughters, _charge>::Pdf(int uniqueId)
    : PdfBase(uniqueId, _neutral, _bachelor, _daughters, _charge) {
  // CreateBuAddPdf();
  // if (Configuration::Get().fit1D() == false) {
  //   CreateDeltaAddPdf();
  // }
}

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
        NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
            .N_Bu_Bu2Dst0h_D0gamma());
    // PdfBase::functionsBu_.add(
    //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
    //         .pdfBu_misId_Bu2Dst0h_D0gamma());
    // PdfBase::yieldsBu_.add(*PdfBase::N_Bu_misId_Bu2Dst0h_D0gamma_);
  }
  PdfBase::functionsBu_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBu_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBu_.add(
      NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
          .N_Bu_Bu2Dst0h_D0pi0());
  // PdfBase::functionsBu_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBu_misId_Bu2Dst0h_D0pi0());
  // PdfBase::yieldsBu_.add(*PdfBase::N_Bu_misId_Bu2Dst0h_D0pi0_);
  // PdfBase::functionsBu_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBu_MisRec());
  // PdfBase::yieldsBu_.add(
  //     NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
  //         .N_Bu_MisRec());
  // PdfBase::functionsBu_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBu_Bu2D0h());
  // PdfBase::yieldsBu_.add(
  //     NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
  //         .N_Bu_Bu2D0h());
  // PdfBase::functionsBu_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBu_PartRec());
  // PdfBase::yieldsBu_.add(
  //     NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
  //         .N_Bu_PartRec());
  // if (_bachelor == Bachelor::k) {
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_misId_MisRec());
  //   PdfBase::yieldsBu_.add(*PdfBase::N_Bu_misId_MisRec_);
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_misId_Bu2D0h());
  //   PdfBase::yieldsBu_.add(*PdfBase::N_Bu_misId_Bu2D0h_);
  //   PdfBase::functionsBu_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBu_misId_PartRec());
  //   PdfBase::yieldsBu_.add(*PdfBase::N_Bu_misId_PartRec_);
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
      NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(
          PdfBase::uniqueId_)
          .N_BuPartial_Bu2Dst0h_D0gamma());
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_misId_Bu2Dst0h_D0gamma());
  // PdfBase::yieldsBuPartial_.add(*PdfBase::N_BuPartial_misId_Bu2Dst0h_D0gamma_);
  PdfBase::functionsBuPartial_.add(
      NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
          .pdfBuPartial_Bu2Dst0h_D0pi0());
  PdfBase::yieldsBuPartial_.add(
      NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(
          PdfBase::uniqueId_)
          .N_BuPartial_Bu2Dst0h_D0pi0());
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_misId_Bu2Dst0h_D0pi0());
  // PdfBase::yieldsBuPartial_.add(*PdfBase::N_BuPartial_misId_Bu2Dst0h_D0pi0_);
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_MisRec());
  // PdfBase::yieldsBuPartial_.add(
  //     NeutralBachelorChargeVars<_neutral, _bachelor,
  //     _charge>::Get(PdfBase::uniqueId_)
  //         .N_BuPartial_MisRec());
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_Bu2D0h());
  // PdfBase::yieldsBuPartial_.add(
  //     NeutralBachelorChargeVars<_neutral, _bachelor,
  //     _charge>::Get(PdfBase::uniqueId_)
  //         .N_BuPartial_Bu2D0h());
  // PdfBase::functionsBuPartial_.add(
  //     NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //         .pdfBuPartial_PartRec());
  // PdfBase::yieldsBuPartial_.add(
  //     NeutralBachelorChargeVars<_neutral, _bachelor,
  //     _charge>::Get(PdfBase::uniqueId_)
  //         .N_BuPartial_PartRec());
  // if (_bachelor == Bachelor::k) {
  //   PdfBase::functionsBuPartial_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBuPartial_misId_MisRec());
  //   PdfBase::yieldsBuPartial_.add(*PdfBase::N_BuPartial_misId_MisRec_);
  //   PdfBase::functionsBuPartial_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBuPartial_misId_Bu2D0h());
  //   PdfBase::yieldsBuPartial_.add(*PdfBase::N_BuPartial_misId_Bu2D0h_);
  //   PdfBase::functionsBuPartial_.add(
  //       NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
  //           .pdfBuPartial_misId_PartRec());
  //   PdfBase::yieldsBuPartial_.add(*PdfBase::N_BuPartial_misId_PartRec_);
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
        NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
            .N_Delta_Bu2Dst0h_D0gamma());
    // PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
    //                                  .pdfDelta_misId_Bu2Dst0h_D0gamma());
    // PdfBase::yieldsDelta_.add(*PdfBase::N_Delta_misId_Bu2Dst0h_D0gamma_);
  }
  PdfBase::functionsDelta_.add(
      NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_Bu2Dst0h_D0pi0());
  PdfBase::yieldsDelta_.add(
      NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
          .N_Delta_Bu2Dst0h_D0pi0());
  // PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                                  .pdfDelta_misId_Bu2Dst0h_D0pi0());
  // PdfBase::yieldsDelta_.add(*PdfBase::N_Delta_misId_Bu2Dst0h_D0pi0_);
  // PdfBase::functionsDelta_.add(
  //     NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_MisRec());
  // PdfBase::yieldsDelta_.add(
  //     NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
  //         .N_Delta_MisRec());
  // PdfBase::functionsDelta_.add(
  //     NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_Bu2D0h());
  // PdfBase::yieldsDelta_.add(
  //     NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
  //         .N_Delta_Bu2D0h());
  // PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                                  .pdfDelta_PartRec());
  // PdfBase::yieldsDelta_.add(
  //     NeutralBachelorChargeVars<_neutral, _bachelor, _charge>::Get(PdfBase::uniqueId_)
  //         .N_Delta_PartRec());
  // if (_bachelor == Bachelor::k) {
  //   PdfBase::functionsDelta_.add(
  //       NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_misId_MisRec());
  //   PdfBase::yieldsDelta_.add(*PdfBase::N_Delta_misId_MisRec_);
  //   PdfBase::functionsDelta_.add(
  //       NeutralVars<_neutral>::Get(PdfBase::uniqueId_).pdfDelta_misId_Bu2D0h());
  //   PdfBase::yieldsDelta_.add(*PdfBase::N_Delta_misId_Bu2D0h_);
  //   PdfBase::functionsDelta_.add(NeutralVars<_neutral>::Get(PdfBase::uniqueId_)
  //                                    .pdfDelta_misId_PartRec());
  //   PdfBase::yieldsDelta_.add(*PdfBase::N_Delta_misId_PartRec_);
  // }

  PdfBase::addPdfDelta_ = std::unique_ptr<RooAddPdf>(new RooAddPdf(
      ("addPdfDelta_" + ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                                    _daughters, _charge))
          .c_str(),
      "", PdfBase::functionsDelta_, PdfBase::yieldsDelta_));
}

template <Neutral _neutral, Bachelor _bachelor, Daughters _daughters,
          Charge _charge>
void Pdf<_neutral, _bachelor, _daughters, _charge>::AssignMisIdYields() {
  switch (_bachelor) {
    case Bachelor::pi:
      PdfBase::N_misId_Bu2Dst0h_D0gamma_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_misId_Bu2Dst0h_D0gamma_" + ComposeName(PdfBase::uniqueId_,
                                                         _neutral, _bachelor,
                                                         _daughters, _charge))
                  .c_str(),
              "@0*(1-@1)",
              RooArgList(Pdf<_neutral, Bachelor::k, _daughters, _charge>::Get(
                             PdfBase::uniqueId_)
                             .N_tot_Bu2Dst0h_D0gamma(),
                         NeutralBachelorVars<_neutral, Bachelor::k>::Get(
                             PdfBase::uniqueId_)
                             .pidEff_Bu2Dst0h_D0gamma())));
      PdfBase::N_misId_Bu2Dst0h_D0pi0_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_misId_Bu2Dst0h_D0pi0_" + ComposeName(PdfBase::uniqueId_,
                                                       _neutral, _bachelor,
                                                       _daughters, _charge))
                  .c_str(),
              "@0*(1-@1)",
              RooArgList(Pdf<_neutral, Bachelor::k, _daughters, _charge>::Get(
                             PdfBase::uniqueId_)
                             .N_tot_Bu2Dst0h_D0pi0(),
                         NeutralBachelorVars<_neutral, Bachelor::k>::Get(
                             PdfBase::uniqueId_)
                             .pidEff_Bu2Dst0h_D0pi0())));
      if (Configuration::Get().fit1D() == true) {
        PdfBase::N_Bu_misId_Bu2Dst0h_D0gamma_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2Dst0h_D0gamma_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "@0*(1-@1)",
                RooArgList(Pdf<_neutral, Bachelor::k, _daughters, _charge>::Get(
                               PdfBase::uniqueId_)
                               .N_tot_Bu2Dst0h_D0gamma(),
                           NeutralBachelorVars<_neutral, Bachelor::k>::Get(
                               PdfBase::uniqueId_)
                               .pidEff_Bu2Dst0h_D0gamma())));
        PdfBase::N_Bu_misId_Bu2Dst0h_D0pi0_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2Dst0h_D0pi0_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "@0*(1-@1)",
                RooArgList(Pdf<_neutral, Bachelor::k, _daughters, _charge>::Get(
                               PdfBase::uniqueId_)
                               .N_tot_Bu2Dst0h_D0pi0(),
                           NeutralBachelorVars<_neutral, Bachelor::k>::Get(
                               PdfBase::uniqueId_)
                               .pidEff_Bu2Dst0h_D0pi0())));
      } else {
        PdfBase::N_Bu_misId_Bu2Dst0h_D0gamma_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2Dst0h_D0gamma_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "(@0/@1)*@2",
                RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .deltaCutEffMisId_Bu2Dst0h_D0gamma(),
                           NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .orEffMisId_Bu2Dst0h_D0gamma(),
                           *PdfBase::N_misId_Bu2Dst0h_D0gamma_)));
        PdfBase::N_Bu_misId_Bu2Dst0h_D0pi0_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2Dst0h_D0pi0_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "(@0/@1)*@2",
                RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .deltaCutEffMisId_Bu2Dst0h_D0pi0(),
                           NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .orEffMisId_Bu2Dst0h_D0pi0(),
                           *PdfBase::N_misId_Bu2Dst0h_D0pi0_)));
      }
      break;
    case Bachelor::k:
      PdfBase::N_misId_Bu2Dst0h_D0gamma_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_misId_Bu2Dst0h_D0gamma_" + ComposeName(PdfBase::uniqueId_,
                                                         _neutral, _bachelor,
                                                         _daughters, _charge))
                  .c_str(),
              "@0*(1-@1)",
              RooArgList(Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                             PdfBase::uniqueId_)
                             .N_tot_Bu2Dst0h_D0gamma(),
                         NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                             PdfBase::uniqueId_)
                             .pidEff_Bu2Dst0h_D0gamma())));
      PdfBase::N_misId_Bu2Dst0h_D0pi0_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_misId_Bu2Dst0h_D0pi0_" + ComposeName(PdfBase::uniqueId_,
                                                       _neutral, _bachelor,
                                                       _daughters, _charge))
                  .c_str(),
              "@0*(1-@1)",
              RooArgList(Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                             PdfBase::uniqueId_)
                             .N_tot_Bu2Dst0h_D0pi0(),
                         NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                             PdfBase::uniqueId_)
                             .pidEff_Bu2Dst0h_D0pi0())));
      PdfBase::N_misId_MisRec_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_misId_MisRec_" + ComposeName(PdfBase::uniqueId_, _neutral,
                                               _bachelor, _daughters, _charge))
                  .c_str(),
              "@0*(1-@1)",
              RooArgList(Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                             PdfBase::uniqueId_)
                             .N_tot_MisRec(),
                         NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                             PdfBase::uniqueId_)
                             .pidEff_MisRec())));
      PdfBase::N_misId_Bu2D0h_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_misId_Bu2D0h_" + ComposeName(PdfBase::uniqueId_, _neutral,
                                               _bachelor, _daughters, _charge))
                  .c_str(),
              "@0*(1-@1)",
              RooArgList(Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                             PdfBase::uniqueId_)
                             .N_tot_Bu2D0h(),
                         NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                             PdfBase::uniqueId_)
                             .pidEff_Bu2D0h())));
      PdfBase::N_misId_PartRec_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_misId_PartRec_" + ComposeName(PdfBase::uniqueId_,
                                                         _neutral, _bachelor,
                                                         _daughters, _charge))
                  .c_str(),
              "@0*(1-@1)",
              RooArgList(Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                             PdfBase::uniqueId_)
                             .N_tot_PartRec(),
                         NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                             PdfBase::uniqueId_)
                             .pidEff_PartRec())));
      if (Configuration::Get().fit1D() == true) {
        PdfBase::N_Bu_misId_Bu2Dst0h_D0gamma_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2Dst0h_D0gamma_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "@0*(1-@1)",
                RooArgList(
                    Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                        PdfBase::uniqueId_)
                        .N_tot_Bu2Dst0h_D0gamma(),
                    NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                        PdfBase::uniqueId_)
                        .pidEff_Bu2Dst0h_D0gamma())));
        PdfBase::N_Bu_misId_Bu2Dst0h_D0pi0_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2Dst0h_D0pi0_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "@0*(1-@1)",
                RooArgList(
                    Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                        PdfBase::uniqueId_)
                        .N_tot_Bu2Dst0h_D0pi0(),
                    NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                        PdfBase::uniqueId_)
                        .pidEff_Bu2Dst0h_D0pi0())));
        PdfBase::N_Bu_misId_MisRec_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_MisRec_" + ComposeName(PdfBase::uniqueId_,
                                                    _neutral, _bachelor,
                                                    _daughters, _charge))
                    .c_str(),
                "@0*(1-@1)",
                RooArgList(
                    Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                        PdfBase::uniqueId_)
                        .N_tot_MisRec(),
                    NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                        PdfBase::uniqueId_)
                        .pidEff_MisRec())));
        PdfBase::N_Bu_misId_Bu2D0h_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2D0h_" + ComposeName(PdfBase::uniqueId_,
                                                    _neutral, _bachelor,
                                                    _daughters, _charge))
                    .c_str(),
                "@0*(1-@1)",
                RooArgList(
                    Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                        PdfBase::uniqueId_)
                        .N_tot_Bu2D0h(),
                    NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                        PdfBase::uniqueId_)
                        .pidEff_Bu2D0h())));
        PdfBase::N_Bu_misId_PartRec_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_PartRec_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "@0*(1-@1)",
                RooArgList(
                    Pdf<_neutral, Bachelor::pi, _daughters, _charge>::Get(
                        PdfBase::uniqueId_)
                        .N_tot_PartRec(),
                    NeutralBachelorVars<_neutral, Bachelor::pi>::Get(
                        PdfBase::uniqueId_)
                        .pidEff_PartRec())));
      } else {
        PdfBase::N_Bu_misId_Bu2Dst0h_D0gamma_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2Dst0h_D0gamma_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "(@0/@1)*@2",
                RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .deltaCutEffMisId_Bu2Dst0h_D0gamma(),
                           NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .orEffMisId_Bu2Dst0h_D0gamma(),
                           *PdfBase::N_misId_Bu2Dst0h_D0gamma_)));
        PdfBase::N_Bu_misId_Bu2Dst0h_D0pi0_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2Dst0h_D0pi0_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "(@0/@1)*@2",
                RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .deltaCutEffMisId_Bu2Dst0h_D0pi0(),
                           NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .orEffMisId_Bu2Dst0h_D0pi0(),
                           *PdfBase::N_misId_Bu2Dst0h_D0pi0_)));
        PdfBase::N_Bu_misId_MisRec_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_MisRec_" + ComposeName(PdfBase::uniqueId_,
                                                    _neutral, _bachelor,
                                                    _daughters, _charge))
                    .c_str(),
                "(@0/@1)*@2",
                RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .deltaCutEffMisId_MisRec(),
                           NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .orEffMisId_MisRec(),
                           *PdfBase::N_misId_MisRec_)));
        PdfBase::N_Bu_misId_Bu2D0h_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_Bu2D0h_" + ComposeName(PdfBase::uniqueId_,
                                                    _neutral, _bachelor,
                                                    _daughters, _charge))
                    .c_str(),
                "(@0/@1)*@2",
                RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .deltaCutEffMisId_Bu2D0h(),
                           NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .orEffMisId_Bu2D0h(),
                           *PdfBase::N_misId_Bu2D0h_)));
        PdfBase::N_Bu_misId_PartRec_ =
            std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
                ("N_Bu_misId_PartRec_" +
                 ComposeName(PdfBase::uniqueId_, _neutral, _bachelor,
                             _daughters, _charge))
                    .c_str(),
                "(@0/@1)*@2",
                RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .deltaCutEffMisId_PartRec(),
                           NeutralBachelorVars<_neutral, _bachelor>::Get(
                               PdfBase::uniqueId_)
                               .orEffMisId_PartRec(),
                           *PdfBase::N_misId_PartRec_)));
      }
      PdfBase::N_Delta_misId_MisRec_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_Delta_misId_MisRec_" + ComposeName(PdfBase::uniqueId_,
                                                     _neutral, _bachelor,
                                                     _daughters, _charge))
                  .c_str(),
              "(@0/@1)*@2",
              RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                             PdfBase::uniqueId_)
                             .buDeltaCutEffMisId_MisRec(),
                         NeutralBachelorVars<_neutral, _bachelor>::Get(
                             PdfBase::uniqueId_)
                             .orEffMisId_MisRec(),
                         *PdfBase::N_misId_MisRec_)));
      PdfBase::N_Delta_misId_Bu2D0h_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_Delta_misId_Bu2D0h_" + ComposeName(PdfBase::uniqueId_,
                                                     _neutral, _bachelor,
                                                     _daughters, _charge))
                  .c_str(),
              "(@0/@1)*@2",
              RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                             PdfBase::uniqueId_)
                             .buDeltaCutEffMisId_Bu2D0h(),
                         NeutralBachelorVars<_neutral, _bachelor>::Get(
                             PdfBase::uniqueId_)
                             .orEffMisId_Bu2D0h(),
                         *PdfBase::N_misId_Bu2D0h_)));
      PdfBase::N_Delta_misId_PartRec_ =
          std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
              ("N_Delta_misId_PartRec_" +
               ComposeName(PdfBase::uniqueId_, _neutral, _bachelor, _daughters,
                           _charge))
                  .c_str(),
              "(@0/@1)*@2",
              RooArgList(NeutralBachelorVars<_neutral, _bachelor>::Get(
                             PdfBase::uniqueId_)
                             .buDeltaCutEffMisId_PartRec(),
                         NeutralBachelorVars<_neutral, _bachelor>::Get(
                             PdfBase::uniqueId_)
                             .orEffMisId_PartRec(),
                         *PdfBase::N_misId_PartRec_)));
      break;
  }
  PdfBase::N_Delta_misId_Bu2Dst0h_D0gamma_ =
      std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_Delta_misId_Bu2Dst0h_D0gamma_" + ComposeName(PdfBase::uniqueId_,
                                                           _neutral, _bachelor,
                                                           _daughters, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
                  .buDeltaCutEffMisId_Bu2Dst0h_D0gamma(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
                  .orEffMisId_Bu2Dst0h_D0gamma(),
              *PdfBase::N_misId_Bu2Dst0h_D0gamma_)));
  PdfBase::N_Delta_misId_Bu2Dst0h_D0pi0_ =
      std::unique_ptr<RooFormulaVar>(new RooFormulaVar(
          ("N_Delta_misId_Bu2Dst0h_D0pi0_" + ComposeName(PdfBase::uniqueId_,
                                                         _neutral, _bachelor,
                                                         _daughters, _charge))
              .c_str(),
          "(@0/@1)*@2",
          RooArgList(
              NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
                  .buDeltaCutEffMisId_Bu2Dst0h_D0pi0(),
              NeutralBachelorVars<_neutral, _bachelor>::Get(PdfBase::uniqueId_)
                  .orEffMisId_Bu2Dst0h_D0pi0(),
              *PdfBase::N_misId_Bu2Dst0h_D0pi0_)));
}
