#include "ParseArguments.h"
#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
// regex = regular expressions: way of finding a pattern in text
ParseArguments::ParseArguments(int argc, char const *const *argv) {
  static const std::regex pattern("-([a-zA-Z_0-9]+)=?([^ ]*)",
            std::regex_constants::extended);
  //static: not associated to a single object
  //constexpr: evaluated at compile time
  //Regular expression:
  //  -[arg name]=[arg value]
  //  () -> group: anything you want to extract (don't contribute to regex)
  //  [] -> what you expect to see as the 'arg name'
  //  + -> one or more of what is in the squ bracket (one to the left)
  //  * -> 0 or more
  //  ? -> 0/1 of these (don't have to specify a value)
  //  ^ -> NOT white space
  //  . -> any character
  //  \ -> esc character if looking for it in regex
  std::cmatch match;//now we need to 'read' the regex
  for (int i = 1; i < argc; ++i) { //iterate through arguments
    if (std::regex_match(argv[i], match, pattern)) {//for each regex try to match to a string
      if (match.size() == 3) {//without the group () size=0/1
        args_.insert(std::make_pair(match[1], match[2]));//first group is entire string match[0]. second = argn third = argv
      } else {//we want to map our argn into our argv
        args_.insert(std::make_pair(match[1], ""));//"" doesn't have to have argv
      }
    }
  }
}

ParseArguments::~ParseArguments() {
  for (auto &arg : args_) {
    std::cerr << "Warning: unused command line argument \"" << arg.first
              << "\".\n";
  }
}

bool ParseArguments::operator()(std::string const &argName, int &output) {
  std::string argVal;
  if (!GetArg(argName, argVal)) {
    return false;
  }
  try {
    output = std::stoi(argVal);
  } catch (std::invalid_argument err) {
    std::cout << "Warning: invalid integer literal for parameter \"" << argName
              << "\": " << argVal << "\n";
    return false;
  }
  return true;
}

bool ParseArguments::operator()(std::string const &argName, float &output) {
  //takes actual value as argument and returns bool as to whether found it or not: so that you can choose not to give a value.
  std::string argVal;
  if (!GetArg(argName, argVal)) {//Call GetArg and see if it exists
    return false;
  }
  try {
    output = std::stof(argVal);//string to float: convert value to a float
  } catch (std::invalid_argument err) {//catch excepting if pass a value that's not a float: not hard but soft error [ try catch ]
    std::cout << "Warning: invalid float literal in parameter \"" << argName
              << "\": " << argVal << "\n";
    return false;
  }
  return true;
}

bool ParseArguments::operator()(std::string const &argName,
                                std::string &output) {
  if (GetArg(argName, output)) {
    return true;
  }
  return false;
}

bool ParseArguments::operator()(std::string const &argName) {
  std::string dummy;
  return GetArg(argName, dummy);
}
//GetArg extracts parameter values
bool ParseArguments::GetArg(std::string argName, std::string &argVal) {
  auto arg = args_.find(argName);//goes into map. find: does key exist?
  if (arg == args_.end()) {
    return false;//doesn't exist: return false
  }
  argVal = std::move(arg->second);//does exist: move value to second argument of function
  //could be given as return type but we return a bool instead because we allow that it doesn't exist.
  args_.erase(arg);//erases value from map. After you get the value from one argument, erase it. In the destructor check if there are any unused argmuent: print user warning (not necessary)
  return true;
}
