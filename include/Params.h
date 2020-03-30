#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <regex>

#include "Configuration.h"
#include "GlobalVars.h"

#include "TRandom3.h"
#include "RooRandom.h"

// Add dummy parameter: Params::Get().Empty();
// RooRealVar var();

class FixedParameter {
 public:
  FixedParameter(std::string const &name, double mean, double std,
                 Systematic systematic)
      : name_(name),
        mean_(mean),
        std_(std),
        systematic_(systematic),
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

  void Randomise(TRandom3 &random) {
    double shifted_value_ = random.Gaus(mean_, std_);
    std::regex re("\\S+_a[A-Z]\\S+");
    std::smatch match;
    if (std::regex_search(name_, match, re)) {
      std::cout << shifted_value_ << "\n";
      while (shifted_value_ < 0) {
        RooRandom::randomGenerator()->SetSeed(0);
        TRandom3 random(0);
        shifted_value_ = random.Gaus(mean_, std_);
      }
      std::cout << shifted_value_ << "\n";
    }
    std::cout << "\t" << name_ << ": " << mean_ << " --> " << shifted_value_
              << "\n";
    roo_variable_->setVal(shifted_value_);
  } 

 private:
  double mean_, std_;
  std::string const name_;
  Systematic systematic_;
  std::shared_ptr<RooRealVar> roo_variable_;
};

class Params {
 private:
  using Key = std::tuple<std::string, std::string, std::string, std::string>;

 public:
  using ValueFixed = FixedParameter;
  using ValueFloating = RooRealVar;

  static Params &Get() {
    static Params params;
    return params;
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId, Neutral neutral, double mean,
                      double std, Systematic systematic) {
    // Add bachelor daughter charge as empty strings: , "", "", ""
    auto key = std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral), "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    return ConstructFixedParameter(key, var_name, mean, std, systematic);
  }

  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, Neutral neutral,
                                             double start, double min_value,
                                             double max_value) {
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), "");
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  std::shared_ptr<RooRealVar> CreateFixed(std::string const &name, int uniqueId,
                                          Neutral neutral, Bachelor bachelor,
                                          double mean, double std,
                                          Systematic systematic) {
    // Add bachelor daughter charge as empty strings: , "", "", ""
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), EnumToString(bachelor));
    auto var_name = name + "_" + ComposeName(uniqueId, neutral, bachelor);
    return ConstructFixedParameter(key, var_name, mean, std, systematic);
  }

  std::shared_ptr<RooRealVar> CreateFloating(std::string const &name,
                                             int uniqueId, Neutral neutral,
                                             Bachelor bachelor, double start,
                                             double min_value,
                                             double max_value) {
    auto key = std::make_tuple(name, std::to_string(uniqueId),
                               EnumToString(neutral), EnumToString(bachelor));
    auto var_name = name + "_" + ComposeName(uniqueId, neutral, bachelor);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  template <typename Iterator>
  void RandomiseParameters(Iterator const &systematic_begin,
                           Iterator const &systematic_end, TRandom3 &random) {
    for (auto &t : fixed_parameters_) {
      for (auto i = systematic_begin; i != systematic_end; ++i) {
        if (t.second.systematic() == *i) {
          std::cout << " \n\n -------------------------------------------- \n\n"
                    << EnumToString(*i) << ": " << t.second.name() 
                    << " \n\n -------------------------------------------- \n\n";
          t.second.Randomise(random);
          break;
        }
      }
    }
  }

  void WriteFixedParametersToFile(std::string const &path, std::vector<Systematic> &systematicVec) {
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
  std::shared_ptr<RooRealVar> ConstructFixedParameter(Key const &key, std::string const &var_name,
                                  double mean, double std,
                                  Systematic systematic) {
    return fixed_parameters_
        .emplace(std::piecewise_construct, key,
                 // Calling FixedParam constructor (takes all arguments and
                 // forwards them to the constructor). Necessary so as not to
                 // copy any RooFit objects !!!
                 std::forward_as_tuple(var_name, mean, std, systematic))
        .first->second.roo_variable();
  }

  std::shared_ptr<RooRealVar> ConstructFloatingParameter(Key const &key,
                                         std::string const &var_name,
                                         double start, double min_value,
                                         double max_value) {
    std::string var_title = "";
    return floating_parameters_
        .emplace(key,
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
