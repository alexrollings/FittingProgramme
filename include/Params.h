#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Configuration.h"
#include "GlobalVars.h"

enum class Systematic { pdfParameters, boxEfficiencies, pidEfficiency };

class FixedParameter {
 public:
  FixedParameter(std::string const &name, double mean, double std,
                 Systematic systematic)
      : name_(name),
        mean_(mean),
        std_(std),
        systematic_(systematic),
        roo_variable_(name.c_str(), "", mean) {}

  FixedParameter(FixedParameter const &) = delete;
  FixedParameter(FixedParameter &&) = delete;
  FixedParameter &operator=(FixedParameter const &) = delete;
  FixedParameter &operator=(FixedParameter &&) = delete;

  std::string const &name() const { return name_; }
  RooRealVar &roo_variable() { return roo_variable_; }
  double value() const { return roo_variable_.getVal(); }
  double mean() const { return mean_; }
  double std() const { return std_; }
  Systematic systematic() const { return systematic_; }

  // void Randomise() {
  //   roo_variable_.value = mean_ + std_;
  // }  // Do actual random here

 private:
  double mean_, std_;
  std::string const name_;
  Systematic systematic_;
  RooRealVar roo_variable_;
};

class Params {
 private:
  using Key = std::tuple<std::string, std::string, std::string>;

 public:
  using ValueFixed = FixedParameter;
  using ValueFloating = RooRealVar;

  static Params &Get() {
    static Params params;
    return params;
  }

  RooRealVar &CreateFixed(std::string const &name, int uniqueId, Neutral neutral, double mean,
                      double std, Systematic systematic) {
    // Add bachelor daughter charge as empty strings: , "", "", ""
    auto key = std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral));
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    return ConstructFixedParameter(key, var_name, mean, std, systematic);
  }

  RooRealVar &CreateFloating(std::string const &name, int uniqueId, Neutral neutral,
                         double start, double min_value, double max_value) {
    auto key =
        std::make_tuple(name, std::to_string(uniqueId), EnumToString(neutral));
    auto var_name = name + "_" + ComposeName(uniqueId, neutral);
    return ConstructFloatingParameter(key, var_name, start, min_value,
                                      max_value);
  }

  // template <typename Iterator>
  // void RandomiseParameters(Iterator const &systematic_begin,
  //                          Iterator const &systematic_end) {
  //   for (auto &t : fixed_parameters_) {
  //     for (auto i = systematic_begin; i != systematic_end; ++i) {
  //       if (t.second.systematic() == *i) {
  //         t.second.Randomise();
  //         break;
  //       }
  //     }
  //   }
  // }
  //
  // void WriteFixedParametersToFile(std::string const &path) {
  //   std::ofstream of(path);
  //   for (auto &t : fixed_parameters_) {
  //     of << std::get<0>(t.first) << "," << std::get<1>(t.first) << ","
  //        << std::get<2>(t.first) << "," << t.second.value() << "\n";
  //   }
  // }
  //
  // std::map<Key, ValueFixed> const &fixed_parameters() const {
  //   return fixed_parameters_;
  // }

 private:
  RooRealVar &ConstructFixedParameter(Key const &key, std::string const &var_name,
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

  RooRealVar &ConstructFloatingParameter(Key const &key,
                                         std::string const &var_name,
                                         double start, double min_value,
                                         double max_value) {
    std::string var_title = "";
    return floating_parameters_
        .emplace(std::piecewise_construct, key,
                 // Calling RooRealVar constructor (takes all arguments and
                 // forwards them to the constructor). Necessary so as not to
                 // copy any RooFit objects !!!
                 std::forward_as_tuple(var_name.c_str(), var_title.c_str(),
                                       start, min_value, max_value))
        .first->second;
  }

  Params() = default;
  ~Params() = default;
  std::map<Key, ValueFixed> fixed_parameters_;
  std::map<Key, ValueFloating> floating_parameters_;
};
//
// int main(int argc, char **argv) {
//   bool randomise = false;
//   if (argc > 1) {
//     if (std::string(argv[1]) == "randomise") {
//       randomise = true;
//     }
//   }
//   auto &a = Params::Get().CreateFixed("VariableA", Neutral::a, Bachelor::c, 1.0,
//                                       1000, Systematic::pdfParameters);
//   auto &b = Params::Get().CreateFixed("VariableB", Neutral::a, Bachelor::d, 2.0,
//                                       1000, Systematic::pdfParameters);
//   auto &c = Params::Get().CreateFixed("VariableC", Neutral::a, Bachelor::c, 3.0,
//                                       1000, Systematic::boxEfficiencies);
//   auto &d = Params::Get().CreateFixed("VariableD", Neutral::b, 4.0, 1000,
//                                       Systematic::pidEfficiency);
//   std::array<Systematic, 2> categories = {Systematic::pdfParameters,
//                                           Systematic::boxEfficiencies};
//   if (randomise) {
//     Params::Get().RandomiseParameters(categories.begin(), categories.end());
//   }
//   std::cout << a.name << ": " << a.value << "\n";
//   std::cout << b.name << ": " << b.value << "\n";
//   std::cout << c.name << ": " << c.value << "\n";
//   std::cout << d.name << ": " << d.value << "\n";
//   for (auto &t : Params::Get().fixed_parameters()) {
//     std::cout << t.second.name() << ": " << t.second.mean() << " / "
//               << t.second.std() << "\n";
//   }
//   Params::Get().WriteFixedParametersToFile("variables.csv");
//   return 0;
// }
