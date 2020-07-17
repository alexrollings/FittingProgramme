#include "Params.h"

RooUnblindUniform *MakeBlind(const char *uniqueName, double range,
                             RooAbsReal &paramToBlind) {
  return new RooUnblindUniform(uniqueName, "Blind", uniqueName, range,
                               paramToBlind);
}

RooFormulaVar *MakeLittleAsym(const char *name, RooAbsReal &bigAsym) {
  return new RooFormulaVar(name, "", "(1+@0)/(1-@0)", RooArgSet(bigAsym));
}

double Params::ReturnParamValErr(Mode mode, Neutral neutral, Bachelor bachelor,
                         std::string &parName, Param param) {
  std::string fname =
      "/home/rollings/Bu2Dst0h_scripts/2d_fit/ana_pdfs/results/MC_" +
      EnumToString(mode) + "_" + EnumToString(neutral) + "_" +
      EnumToString(bachelor) + ".root";
  auto file = std::unique_ptr<TFile>(TFile::Open(fname.c_str()));
  auto fitResult = std::unique_ptr<RooFitResult>(
      dynamic_cast<RooFitResult *>(file->FindObjectAny("FitResult")));
  RooArgList constPars = fitResult->constPars();
  RooArgList floatPars = fitResult->floatParsFinal();
  RooAbsArg *absArg = nullptr;
  absArg = constPars.find(parName.c_str());
  if (absArg == nullptr) {
    std::cout << parName << " is not a constant parameter\n";
    absArg = floatPars.find(parName.c_str());
    if (absArg == nullptr) {
      throw std::runtime_error("Cannot find parameter " + parName +
                               " in fit result");
    } else {
      std::cout << parName << " is a floating parameter\n";
    }
  }
  RooRealVar *realVar = dynamic_cast<RooRealVar *>(absArg);
  if (realVar == nullptr) {
    throw std::runtime_error("Canot cast AbsArg to AbsReal for " + parName);
  }
  std::cout << parName << "," << realVar->getVal() << "," << realVar->getError()
            << "\n";
  if (param == Param::val) {
    return realVar->getVal();
  } else {
    return realVar->getError();
  }
}
