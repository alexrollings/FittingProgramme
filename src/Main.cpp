#include "ParseArguments.h"
#include <iostream>

int main(int argc, char **argv) {
  std::string polarity("both");
  std::string bach;
  // By letting the ParseArguments object go out of scope it will print a
  // warning if the user specified any unknown options. 
  {//calls destructor when object goes out of scope: Will tell you if anything was not used that was given as a command line argument before continuing
    ParseArguments args(argc, argv);//object instantiated
    
    if (args("help")){
      std::cout << " -----------------------------------------------------\n";
      std::cout << "The following options are possible:\n";
      std::cout << "Options:   \n";
      std::cout << "    -polarity (magnetic polarity) choices {both,up,down} default: " << polarity << "\n";
      std::cout << "    -bach (bachelor particle) choices {k,pi} must be specified.\n";
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
    if (!args("bach", bach)) {
      std::cerr << "Missing mandatory argument: -bach\n";
      return 1;
    }
    std::cout << "bach set to \"" << bach << "\".\n";
  }
  return 0;
}
