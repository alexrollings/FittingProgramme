#include "ParseArguments.h"
#include <iostream>

//Save all strings to a list depending on options and loop over all files in data set at the end: nested for loops
int main(int argc, char **argv) {
  std::string polarity("both");
  std::string bachelor;
  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options. 
  {//calls destructor when object goes out of scope: Will tell you if anything was not used that was given as a command line argument before continuing
    ParseArguments args(argc, argv);//object instantiated
    
    if (args("help")){
      std::cout << " -----------------------------------------------------\n";
      std::cout << "The following options are possible:\n";
      std::cout << "Options:   \n";
      std::cout << "    -polarity choices {both,up,down} default: " << polarity << "\n";
      std::cout << "    -bachelor choices {k,pi} must be specified.\n";
    }
    
    if (args("polarity", polarity)) {//first arg = name of arg in command line
      //second arg = parameter: where to store value if value is given
      if (polarity != "up" && polarity != "down" && polarity != "both") {
        std::cerr << "-polarity: expected value in [up/down/both].\n";
        return 1;
      }
    } else {
      std::cout << "-polarity: using default value \"" << polarity << "\".\n";
    }
    if (!args("bachelor", bachelor)) {
      std::cerr << "Missing mandatory argument: -bachelor\n";
      return 1;
    }
    std::cout << "bachelor set to \"" << bachelor << "\".\n";
  }
  
  
  
  
  
  
  
  return 0;
}
