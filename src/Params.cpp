#include "Params.h"

RooUnblindUniform *MakeBlind(const char *uniqueName, double range,
                             RooAbsReal &paramToBlind) {
  // convert const char to string
  std::string blindStr(uniqueName);
  std::string s("_WN");
  // std::cout << "Blinding parameter " << blindStr << "\n";
  if (blindStr.find(s) != std::string::npos) {
    // std::cout << "String contains " << s <<  "\n";
    // find returns starting position of string. Erase removes number of symbols
    // fromthis position
    blindStr.erase(blindStr.find(s), 3);
  } 
  // std::cout << "String to blind with = " << blindStr << "\n";
  return new RooUnblindUniform(uniqueName, "Blind", blindStr.c_str(), range,
                               paramToBlind);
}
RooFormulaVar *MakeLittleAsym(const char *name, RooAbsReal &bigAsym) {
  return new RooFormulaVar(name, "", "(1+@0)/(1-@0)", RooArgSet(bigAsym));
}

void FixedParameter::Randomise(TRandom3 &random) {
  double shifted_value_ = random.Gaus(mean_, std_);
  if (sign_ == Sign::positive) {
    std::cout << "Positive\n";
    std::cout << shifted_value_ << "\n";
    while (shifted_value_ < 0) {
      RooRandom::randomGenerator()->SetSeed(0);
      TRandom3 random(0);
      shifted_value_ = random.Gaus(mean_, std_);
    }
    std::cout << shifted_value_ << "\n";
  } else if (sign_ == Sign::negative) {
    std::cout << "Negative\n";
    std::cout << shifted_value_ << "\n";
    while (shifted_value_ > 0) {
      RooRandom::randomGenerator()->SetSeed(0);
      TRandom3 random(0);
      shifted_value_ = random.Gaus(mean_, std_);
    }
    std::cout << shifted_value_ << "\n";
  } else if (sign_ == Sign::same) {
    std::cout << "Same\n";
    std::cout << shifted_value_ << "\n";
    std::cout << shifted_value_*shifted_value_ << "\n";
    while (shifted_value_*mean_ < 0) {
      RooRandom::randomGenerator()->SetSeed(0);
      TRandom3 random(0);
      shifted_value_ = random.Gaus(mean_, std_);
    }
    std::cout << shifted_value_ << "\n";
  }
  std::smatch match;
  static const std::regex pattern("\\S+Eff\\S+");
  if (std::regex_match(name_, match, pattern)) {
    std::cout << "0 < Efficiency < 1\n";
    std::cout << shifted_value_ << "\n";
    while (shifted_value_ > 1 || shifted_value_ < 0) {
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

double Params::ReturnValErr(Mode mode, Neutral neutral, Bachelor bachelor,
                   std::string const &parName, Param param) {
  std::string bachStr = EnumToString(bachelor);
  if (bachelor == Bachelor::k) {
    bachStr = "K";
  }
  std::string fname =
      "/home/rollings/Bu2Dst0h_scripts/2d_fit/ana_pdfs/results/MC_" +
      EnumToString(neutral) + "_" + EnumToString(mode) + "_" +
      bachStr + ".root";
  auto file = std::unique_ptr<TFile>(TFile::Open(fname.c_str()));
  if (file == nullptr) {
    throw std::runtime_error(fname + " does not exist\n");
  }
  auto fitResult = std::unique_ptr<RooFitResult>(
      dynamic_cast<RooFitResult *>(file->FindObjectAny("FitResult")));
  RooArgList constPars = fitResult->constPars();
  RooArgList floatPars = fitResult->floatParsFinal();
  RooAbsArg *absArg = nullptr;
  absArg = constPars.find(parName.c_str());
  if (absArg == nullptr) {
    absArg = floatPars.find(parName.c_str());
    if (absArg == nullptr) {
      throw std::runtime_error("Cannot find parameter " + parName +
                               " in fit result for bachelor " +
                               EnumToString(bachelor));
    } 
  }
  RooRealVar *realVar = dynamic_cast<RooRealVar *>(absArg);
  if (realVar == nullptr) {
    throw std::runtime_error("Canot cast AbsArg to AbsReal for " + parName);
  }
  // std::cout << parName << "," << realVar->getVal() << "," << realVar->getError()
  //           << "\n";
  if (param == Param::val) {
    return realVar->getVal();
  } else {
    return realVar->getError();
  }
}
