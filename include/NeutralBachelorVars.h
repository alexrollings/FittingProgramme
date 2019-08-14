#pragma once
#include "Configuration.h"
#include "GlobalVars.h"
#include "NeutralVars.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"

// Bachelor

template <Neutral neutral, Bachelor bachelor>
class NeutralBachelorVars {
 public:
  NeutralBachelorVars(int uniqueId_);
  ~NeutralBachelorVars() {}

  using This_t = NeutralBachelorVars<neutral, bachelor>;

  // Get() method of PDF now doesn't always return the same PDF, but the same
  // PDF for the given ID
  static This_t &Get(int uniqueId_) {
    static std::map<int, std::shared_ptr<This_t>> singletons;
    // An iterator to a map is a std::pair<key, value>, so we need to call
    // i->second to get the value
    auto it = singletons.find(uniqueId_);  // Check if uniqueId_ already exists
    if (it == singletons.end()) {
      // If it doesn't, create it as a new unique_ptr by calling emplace, which
      // will forward the pointer to the constructor of std::unique_ptr
      it = singletons.emplace(uniqueId_, std::make_shared<This_t>(uniqueId_))
               .first;
    }
    return *it->second;
  }

  int uniqueId() { return uniqueId_; }
  RooAbsReal &Bu2Dst0h_Dst02D0gamma_sigmaBu() {
    return *Bu2Dst0h_Dst02D0gamma_sigmaBu_;
  }
  RooCBShape &pdf1Bu_Bu2Dst0h_Dst02D0gamma() {
    return pdf1Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooCBShape &pdf2Bu_Bu2Dst0h_Dst02D0gamma() {
    return pdf2Bu_Bu2Dst0h_Dst02D0gamma_;
  }
  RooAddPdf &pdfBu_Bu2Dst0h_Dst02D0gamma() {
    return pdfBu_Bu2Dst0h_Dst02D0gamma_;
  }

 private:
  int uniqueId_;
  std::unique_ptr<RooAbsReal> Bu2Dst0h_Dst02D0gamma_sigmaBu_;
  RooCBShape pdf1Bu_Bu2Dst0h_Dst02D0gamma_;
  RooCBShape pdf2Bu_Bu2Dst0h_Dst02D0gamma_;
  RooAddPdf pdfBu_Bu2Dst0h_Dst02D0gamma_;
};

template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId);
template <>
NeutralBachelorVars<Neutral::pi0, Bachelor::k>::NeutralBachelorVars(
    int uniqueId);
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::pi>::NeutralBachelorVars(
    int uniqueId);
template <>
NeutralBachelorVars<Neutral::gamma, Bachelor::k>::NeutralBachelorVars(
    int uniqueId);
