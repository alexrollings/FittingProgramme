#pragma once
#include "Configuration.h"
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include <string>

template <Year year>
class YearVars {

 public:
  static YearVars &Get() {
    static YearVars singleton;
    return singleton;
  }

  RooConstVar &pidEff() { return pidEff_; }
  double &pidEffPerYear() { return pidEffPerYear_; }
  double &yieldVal() { return yieldVal_; }
  double &yieldTot() { return yieldTot_; }

 private:
  YearVars(YearVars const &) = delete;
  YearVars(YearVars &&) = delete;
  YearVars &operator=(YearVars const &) = delete;
  YearVars &operator=(YearVars &&) = delete;
  
  RooConstVar pidEff_;
  double pidEffPerYear_;
  double yieldVal_;
  double yieldTot_;

};

template <>
YearVars<Year::y2011>::YearVars();
template <>
YearVars<Year::y2012>::YearVars();
template <>
YearVars<Year::y2015>::YearVars();
template <>
YearVars<Year::y2016>::YearVars();
template <>
YearVars<Year::y2017>::YearVars();
