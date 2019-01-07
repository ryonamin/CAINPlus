#include "CainWrapper.h"

// STL
#include <iostream>
#include <fstream>

// ROOT
#include "TSystem.h"

// LCIO

int main(int argc, char** argv) {

  // Check input arguments
  std::ifstream inputfile(argv[1]);
  if (!inputfile.is_open()) {
    std::cout << "Input error. " << std::endl;
    std::cout << "Usage : cain+ input.i (option startNevent endNevent)" << std::endl;
    std::abort();
  }
  
  int startNEvent = 0;
  int endNEvent   = 1;
  if (argc==2) {
    std::cout << "startNevent is not specified. default (0) will be used." << std::endl;
    std::cout << "endNevent is not specified. default (1) will be used." << std::endl;
  } else if (argc==3) {
    std::cout << "startNevent is set to be " << argv[2] <<"." << std::endl;
    std::cout << "endNevent is not specified. 1 event will be processed." << std::endl;
    startNEvent = std::atoi(argv[2]);
    endNEvent = startNEvent+1;
  } else if (argc==4) {
    startNEvent = std::atoi(argv[2]);
    endNEvent   = std::atoi(argv[3]);
    if (startNEvent<endNEvent) {
      std::cout << "startNevent is set to be " << argv[2] <<"." << std::endl;
      std::cout << "endNevent is set to be " << argv[3] <<"." << std::endl;
    } else {
      std::cout << "Specified endNEvent is less than (or equal to) startNEvent." << std::endl;
      std::cout << "startNevent is set to be " << argv[2] <<"." << std::endl;
      std::cout << "Only 1 event will be processed." << std::endl;
    }
  }

  CainWrapper *cw = new CainWrapper(argv[1]);
  cw->SetOutputPrefix("cain_");
  TString runid("evt");
  runid += std::to_string(startNEvent);
  runid += "-";
  runid += std::to_string(endNEvent);
  cw->SetRunID(runid.Data());
  cw->RegisterRootFile();
  //cw->RegisterLcioFile();

  for (int ev = startNEvent; ev < endNEvent; ev++) {
    cw->RunCain(ev);

    Event event(ev); // Create empty event object.
    cw->ReadCainOutput(event); // Fill event data
    cw->WriteEvent(event); 
  }
  delete cw;
}
