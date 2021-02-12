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
  double shifted_value_;
  std::smatch match;
  static const std::regex pattern("\\S+Eff\\S+");
  if (std::regex_match(name_, match, pattern)) {
    std::cout << "0 < Efficiency < 1\n";
    // std::cout << shifted_value_ << "\n";
    while (shifted_value_ > 1 || shifted_value_ < 0) {
      RooRandom::randomGenerator()->SetSeed(0);
      TRandom3 random(0);
      if (std_pos_ == std_neg_) {
      shifted_value_ = random.Gaus(mean_, std_pos_);
      } else {
        throw std::runtime_error(
            "Params.cpp line 36: no implementation for asymmetric errors of "
            "efficiencies");
      }
    }
    // std::cout << shifted_value_ << "\n";
  } else {
    int rand_sign_;
    if (sign_ == Sign::positive) {
      rand_sign_ = 1;
    } else if (sign_ == Sign::negative) {
      rand_sign_ = -1;
    } else if (sign_ == Sign::same) {
      if (mean_ < 0) {
        rand_sign_ = -1;
      } else {
        rand_sign_ = 1;
      }
    } else {  // Sign::none
      // Randomly choose +ve/-ve shift
      double tmp_ = random.Gaus(0, 1);
      if (tmp_ < 0) {
        rand_sign_ = -1;
      } else {
        rand_sign_ = 1;
      }
    }
    double std_;
    // If std_pos_ = std_neg_, doesn't matter. If not, choosed correct one
    if (rand_sign_ == 1) {
      std_ = std_pos_;
    } else {
      std_ = std_neg_;
    }
    shifted_value_ = random.Gaus(mean_, std_);
    // If random sign and shifted value are not the same sign, pick again
    if (rand_sign_ * shifted_value_ < 0) {
      while (rand_sign_ * shifted_value_ < 0) {
        RooRandom::randomGenerator()->SetSeed(0);
        TRandom3 random(0);
        shifted_value_ = random.Gaus(mean_, std_);
      }
    }
  }
  // std::cout << "\t" << name_ << ": " << mean_ << " --> " << shifted_value_
  //           << "\n";
  roo_variable_->setVal(shifted_value_);
}

double Params::ReturnValErr(Mode mode, Neutral neutral, Bachelor bachelor,
                   std::string const &parName, Param param) {
  // For Delta PDF of Bs2Dst0Kst0 modes, use signal values (but still retain own
  // parameter name for systematics)
  std::string parNameToRead = parName;
  std::smatch match;
  static const std::regex pattern("(Bs2Dst0Kst0_D0(pi0|gamma))_(\\S+)");
  if (std::regex_match(parName, match, pattern)) {
    std::smatch m;
    static const std::regex re("Bu2Dst0(pi|K)_(\\S+)");
    std::string modeStr = EnumToString(mode);
    if (std::regex_match(modeStr, m, re)) {
      std::stringstream ss_par;
      ss_par << "Bu2Dst0h_D0" << match[2] << "_" << match[3];
      parNameToRead = ss_par.str();
    }
  }
  std::string bachStr = EnumToString(bachelor);
  if (bachelor == Bachelor::k) {
    bachStr = "K";
  }
  std::string fname =
      "/home/rollings/Bu2Dst0h_scripts/2d_fit/ana_pdfs/new/results/MC_" +
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
  absArg = constPars.find(parNameToRead.c_str());
  if (absArg == nullptr) {
    absArg = floatPars.find(parNameToRead.c_str());
    if (absArg == nullptr) {
      // std::cout << fname << "\n";
      // fitResult->Print();
      throw std::runtime_error("Cannot find parameter " + parNameToRead +
                               " in fit result for bachelor " +
                               EnumToString(bachelor));
    } 
  }
  RooRealVar *realVar = dynamic_cast<RooRealVar *>(absArg);
  if (realVar == nullptr) {
    throw std::runtime_error("Canot cast AbsArg to AbsReal for " + parNameToRead);
  }
  // std::cout << parNameToRead << "," << realVar->getVal() << "," << realVar->getError()
  //           << "\n";
  if (param == Param::val) {
    return realVar->getVal();
  } else {
    if (neutral == Neutral::pi0 && parNameToRead == "Bs2Dst0Kst0_D0pi0_sigmaBu") {
      // Cutting tighter on the BDT reduced the disn width by 3 - take this to
      // be systematic
      double mcBdtDifference = 3.;
      return mcBdtDifference; 
    } else {
      return realVar->getError();
    }
  }
}
