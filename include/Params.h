#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "RooRandom.h"
#include "TRandom3.h"
#include "RooFitResult.h"
#include "TFile.h"

#include "Configuration.h"

// Add dummy parameter: Params::Get().Empty();
// RooRealVar var();
// Enum to ensure parameter > / < 0 when randomising (e.g. tail or widths in
// fit)
enum class Sign { positive, negative, none };
enum class Param { val, err };

class FixedParameter {
 public:
  FixedParameter(std::string const &name, double mean, double std,
                 Systematic systematic, Sign sign)
      : name_(name),
        mean_(mean),
        std_(std),
        systematic_(systematic),
        sign_(sign),
        roo_variable_(new RooRealVar(name.c_str(), "", mean)) {}

  FixedParameter(FixedParameter const &) = delete;
  FixedParameter(FixedParameter &&) = delete;
  FixedParameter &operator=(FixedParameter const &) = delete;
  FixedParameter &operator=(FixedParameter &&) = delete;

  std::string const &name() const { return name_; }
  std::shared_ptr<RooRealVar> roo_variable() { return roo_variable_; }
  double value() const { return roo_variable_->getVal(); }
  double mean() const { return mean_; }
  double std() const { return std_; }
  Systematic systematic() const { return systematic_; }
  Sign sign() const { return sign_; }
  void Randomise(TRandom3 &random); 

 private:
  double mean_, std_;
  std::string const name_;
  Systematic systematic_;
  Sign sign_;
  std::shared_ptr<RooRealVar> roo_variable_;
};

class Params {
 private:
  using Key = std::tuple<std::string, std::string, std::string, std::string,
                         std::string>;

 public:
  using ValueFixed = FixedParameter;
  using ValueFloating = RooRealVar;
  double ReturnValErr(Mode mode, Neutral neutral, Bachelor bachelor,
                         std::string const &parName, Param param);

  static Params &Get() {
    static Params params;
    return params;
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId,
                                          double mean, double std,
                                          Systematic systematic, Sign sign) {
    // Add bachelor daughter charge as empty strings: , "", "", ""
    auto key = std::make_tuple(name, std::to_string(uniqueId), "", "", "");
    auto var_name = name + "_" + std::to_string(uniqueId);
    return ConstructFixedParameter(key, var_name, mean, std, systematic, sign);
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId,
                                          Neutral neutral, double mean,
                                          double std, Systematic systematic,
                                          Sign sign) {
    // Add bachelor daughter charge as empty strings: , "", "", ""
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), "", "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    return ConstructFixedParameter(key, var_name, mean, std, systematic, sign);
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId,
                                          Neutral neutral, Bachelor bachelor,
                                          double mean, double std,
                                          Systematic systematic, Sign sign) {
    // Add bachelor daughter charge as empty strings: , "", "", ""
    auto key =
        std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral),
                        EnumToString(bachelor), "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral, bachelor);
    return ConstructFixedParameter(key, var_name, mean, std, systematic, sign);
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId,
                                          Neutral neutral, Daughters daughters,
                                          double mean, double std,
                                          Systematic systematic, Sign sign) {
    // Add daughters daughter charge as empty strings: , "", "", ""
    auto key =
        std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral),
                        EnumToString(daughters), "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral, daughters);
    return ConstructFixedParameter(key, var_name, mean, std, systematic, sign);
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId,
                                          Neutral neutral, Bachelor bachelor,
                                          Daughters daughters, double mean,
                                          double std, Systematic systematic,
                                          Sign sign) {
    // Add bachelor daughter charge as empty strings: , "", "", ""
    auto key =
        std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral),
                        EnumToString(bachelor), EnumToString(daughters));
    auto var_name =
        name + "_" + ComposeName(uniqueId, neutral, bachelor, daughters);
    return ConstructFixedParameter(key, var_name, mean, std, systematic, sign);
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId,
                                          Neutral neutral, Charge charge,
                                          double mean, double std,
                                          Systematic systematic, Sign sign) {
    // Add charge daughter charge as empty strings: , "", "", ""
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), EnumToString(charge), "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral, charge);
    return ConstructFixedParameter(key, var_name, mean, std, systematic, sign);
  }

  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, double start,
                                             double min_value,
                                             double max_value) {
    auto key = std::make_tuple(name, std::to_string(uniqueId), "", "", "");
    auto var_name = name + "_" + std::to_string(uniqueId);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, Neutral neutral,
                                             double start, double min_value,
                                             double max_value) {
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), "", "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, Neutral neutral,
                                             Bachelor bachelor, double start,
                                             double min_value,
                                             double max_value) {
    auto key =
        std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral),
                        EnumToString(bachelor), "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral, bachelor);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, Neutral neutral,
                                             Charge charge, double start,
                                             double min_value,
                                             double max_value) {
    auto key =
        std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral),
                        EnumToString(charge), "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral, charge);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, Neutral neutral,
                                             Daughters daughters, double start,
                                             double min_value,
                                             double max_value) {
    auto key =
        std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral),
                        EnumToString(daughters), "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral, daughters);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, Neutral neutral,
                                             Bachelor bachelor, Charge charge,
                                             double start, double min_value,
                                             double max_value) {
    auto key =
        std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral),
                        EnumToString(bachelor), EnumToString(charge));
    auto var_name =
        name + "_" + ComposeName(uniqueId, neutral, bachelor, charge);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  std::shared_ptr<RooRealVar> CreateFloating(
      std::string const &name, int uniqueId, Neutral neutral, Bachelor bachelor,
      Daughters daughters, double start, double min_value, double max_value) {
    auto key =
        std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral),
                        EnumToString(bachelor), EnumToString(daughters));
    auto var_name =
        name + "_" + ComposeName(uniqueId, neutral, bachelor, daughters);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  // Reads in starting value of parameters from MC file, rather than passing to
  // constructor
  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, Neutral neutral,
                                             Mode mode, double min_value,
                                             double max_value) {
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), "", "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    // Use pi bachelor if no bach specified
    double start = ReturnValErr(mode, neutral, Bachelor::pi, name, Param::val);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, Neutral neutral,
                                             Bachelor bachelor, Mode mode,
                                             double min_value,
                                             double max_value) {
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), "", "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    double start = ReturnValErr(mode, neutral, bachelor, name, Param::val);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId,
                                          Neutral neutral, Mode mode,
                                          Systematic systematic, Sign sign) {
    // Add bachelor daughter charge as empty strings: , "", "", ""
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), "", "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    // Use pi bachelor if no bach specified
    double mean = ReturnValErr(mode, neutral, Bachelor::pi, name, Param::val);
    double std = ReturnValErr(mode, neutral, Bachelor::pi, name, Param::err);
    return ConstructFixedParameter(key, var_name, mean, std, systematic, sign);
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId,
                                          Neutral neutral, Bachelor bachelor,
                                          Mode mode, Systematic systematic,
                                          Sign sign) {
    // Add bachelor daughter charge as empty strings: , "", "", ""
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), "", "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    double mean = ReturnValErr(mode, neutral, bachelor, name, Param::val);
    double std = ReturnValErr(mode, neutral, bachelor, name, Param::err);
    return ConstructFixedParameter(key, var_name, mean, std, systematic, sign);
  }

  template <typename Iterator>
  void RandomiseParameters(Iterator const &systematic_begin,
                           Iterator const &systematic_end, TRandom3 &random) {
    for (auto &t : fixed_parameters_) {
      for (auto i = systematic_begin; i != systematic_end; ++i) {
        if (t.second.systematic() == *i) {
          std::cout
              << " \n\n -------------------------------------------- \n\n"
              << EnumToString(*i) << ": " << t.second.name()
              << " \n\n -------------------------------------------- \n\n";
          t.second.Randomise(random);
          break;
        }
      }
    }
  }

  void WriteFixedParametersToFile(std::string const &path,
                                  std::vector<Systematic> &systematicVec) {
    std::ofstream of(path);
    for (auto &t : fixed_parameters_) {
      for (auto s : systematicVec) {
        if (t.second.systematic() == s) {
          of << std::get<0>(t.first) << "," << std::get<2>(t.first) << ","
             << std::get<3>(t.first) << "," << t.second.mean() << ","
             << t.second.std() << "\n";
          std::cout << t.second.name() << "," << t.second.mean() << ","
                    << t.second.std() << "\n";
        }
      }
    }
  }

  std::map<Key, ValueFixed> const &fixed_parameters() const {
    return fixed_parameters_;
  }

 private:
  std::shared_ptr<RooRealVar> ConstructFixedParameter(
      Key const &key, std::string const &var_name, double mean, double std,
      Systematic systematic, Sign sign) {
    return fixed_parameters_
        .emplace(std::piecewise_construct, key,
                 // Calling FixedParam constructor (takes all arguments and
                 // forwards them to the constructor). Necessary so as not to
                 // copy any RooFit objects !!!
                 std::forward_as_tuple(var_name, mean, std, systematic, sign))
        .first->second.roo_variable();
  }

  std::shared_ptr<RooRealVar> ConstructFloatingParameter(
      Key const &key, std::string const &var_name, double start,
      double min_value, double max_value) {
    std::string var_title = "";
    return floating_parameters_
        .emplace(
            key,
            // Calling RooRealVar constructor (takes all arguments and
            // forwards them to the constructor). Necessary so as not to
            // copy any RooFit objects !!!
            std::make_shared<ValueFloating>(var_name.c_str(), var_title.c_str(),
                                            start, min_value, max_value))
        .first->second;
  }

  Params() = default;
  ~Params() = default;
  std::map<Key, ValueFixed> fixed_parameters_;
  std::map<Key, std::shared_ptr<ValueFloating>> floating_parameters_;
};

RooUnblindUniform *MakeBlind(const char *uniqueName, double range,
                             RooAbsReal &paramToBlind);
RooFormulaVar *MakeLittleAsym(const char *uniqueName,
                             RooAbsReal &bigAsym);
