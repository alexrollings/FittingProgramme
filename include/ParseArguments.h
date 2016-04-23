#pragma once

#include <string>
#include <map>

/// Convenience class to parse input arguments from command line of the form:
///   -<parameter name>=<parameter value>
///
/// After constructing the object values are retrieved with the ()-operator,
///  which will return whether the argument was defined or not:
///
///   ParseArguments args(argc, argv);
///    float a = 3.141592;
///    if (!args("a", a)) {
///      std::cout << "Parameter \"a\" not defined, using default value: "
///                << a << "\n";
///    }

class ParseArguments {

public:
  ParseArguments(int argc, char const *const *argv);
  ~ParseArguments();

  bool operator()(std::string const &arg);
  bool operator()(std::string const &arg, std::string &value);
  bool operator()(std::string const &arg, int &value);
  bool operator()(std::string const &arg, float &value);

private:
  bool GetArg(std::string argName, std::string &argVal);

  std::map<std::string, std::string> args_{};//maps from strings to strings (key to a value)

};
