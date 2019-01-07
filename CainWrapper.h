#ifndef __CAINWRAPPER_H__
#define __CAINWRAPPER_H__
#include "Event.h"
// STD
#include <fstream>
// ROOT
#include "TObject.h"
#include "TString.h"
// LCIO 
//#include "lcio.h"
//#include "IO/LCReader.h"
//#include "IO/LCWriter.h"
//#include "IOIMPL/LCFactory.h"
//#include "IMPL/LCTOOLS.h"

class LcioWriter;
class RootWriter;
class Event;

class CainWrapper : public TObject
{
  public :
	CainWrapper(const char* confpath); 
        ~CainWrapper();
        void SetOutputPrefix(const char* in) { _outPrefix = TString(in); };
        void SetRunID(const char* in);
        void RegisterRootFile();
        void RegisterLcioFile();
        void RunCain(int ev);
        void ReadCainOutput(Event& e);
        void WriteEvent(Event& e);
  private : 
        TString       _outPrefix;
        TString       _runId;
        TString       _confPath;
        TString       _confDir;
        TString       _runDir;
        TString       _confTmp;
        std::ifstream _fconfin;
        std::ofstream _fconfot;
        std::ifstream _fcainot;
        LcioWriter*   _lcio;
        RootWriter*   _root;
  ClassDef(CainWrapper,1)

};

#endif

