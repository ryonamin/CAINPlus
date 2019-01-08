#include "CainWrapper.h"
#include "LcioWriter.h"
#include "RootWriter.h"

//STL
#include <iostream>
#include <string>
#include <sys/stat.h>
//ROOT
#include "TObjArray.h"
#include "TObjString.h"
#include "TString.h"
#include "TSystem.h"
#include "TDirectory.h"
// LCIO 
#include "IO/LCWriter.h"
#include "IMPL/LCEventImpl.h" 

ClassImp(CainWrapper)

CainWrapper::CainWrapper(const char* conf) : _confPath(conf),
                                             _confDir(conf),
                                             _lcio(0),
                                             _root(0)
{
   TObjArray* strings = _confPath.Tokenize("/");
   TString confname = static_cast<TObjString*>(strings->Last())->String();
   _confDir.ReplaceAll(confname,"");

}

CainWrapper::~CainWrapper()
{
  if (_lcio) delete _lcio;
  if (_root) delete _root;
}

void CainWrapper::RegisterRootFile()
{
  TString fpath(_confDir);
  fpath += _outPrefix;
  fpath += _runId;
  fpath += ".root";
  _root = new RootWriter(fpath.Data());
}

void CainWrapper::RegisterLcioFile()
{
  TString fpath(_confDir);
  fpath += _outPrefix;
  fpath += _runId;
  fpath += ".slcio";
  _lcio = new LcioWriter(fpath.Data());
}

void CainWrapper::RunCain(int ev)
{
  _confTmp = _confDir;
  _confTmp += "temp_";
  _confTmp += _runId;
  _confTmp += ".i";
  _fconfot.open(_confTmp.Data());
  _fconfin.open(_confPath.Data());
  std::string line;
  while (_fconfin && getline(_fconfin,line)) {
    if (TString(line).Contains("Rand")) {
      TObjArray* strings = TString(line).Tokenize("=");
      TString origvalue =  static_cast<TObjString*>(strings->At(1))->String().Strip(TString::kTrailing,';');
      // odd number more than 1 is required by CAIN.
      _fconfot << TString(line).ReplaceAll(origvalue,std::to_string(2*ev+3)) << std::endl; 
    } else {
      _fconfot << line << std::endl;
    }
  }
  _fconfin.close();
  _fconfot.close();
  std::cout << "Generating event (ev = " << ev << ") ..." << std::endl;
  TString cmd("cain.exe");
  cmd += " < ";
  cmd += _confTmp;
  gSystem->Exec(cmd.Data());
}

void CainWrapper::WriteEvent(Event& e)
{
  if (_lcio) _lcio->WriteEvent(e);
  if (_root) _root->WriteEvent(e);
}

void CainWrapper::ReadCainOutput(Event& e)
{
   TString path(_confDir);
   path += "in_1000.dat";
   _fcainot.open(path);
   std::string line;
   
   getline(_fcainot,line); // Read header line.
   int k, gen;
   float weight, t, x, y, s, energy, px, py, ps, sx, sy, ss;
   std::string name;
   int index(0);
   while( _fcainot >> k >> gen >> name >> weight >> t >> x >> y 
                   >> s >> energy >> px >> py >> ps >> sx >> sy >> ss ) {
     // left-handed to right-handed
     x *= -1.0;
     px *= -1.0;
     sx *= -1.0;
     // m->mm
     t *= 1.0e3;
     x *= 1.0e3;
     y *= 1.0e3;
     s *= 1.0e3;
     // eV->GeV
     px *= 1.0e-9;
     py *= 1.0e-9;
     ps *= 1.0e-9;
     energy *= 1.0e-9;

     int pdg = 22;
     if (k==2) pdg = 11 ;
     if (k==3) pdg = -11 ;
     e._pdg[index] = pdg;
     e._vtx_x[index] = x;
     e._vtx_y[index] = y;
     e._vtx_z[index] = s;
     e._t[index] = t;
     e._e[index] = energy;
     e._p_x[index] = px;
     e._p_y[index] = py;
     e._p_z[index] = ps;
     e._s_x[index] = sx;
     e._s_y[index] = sy;
     e._s_z[index] = ss;

     index++;
   }
   _fcainot.close();

   e._nParticles = index;

}
 
void CainWrapper::SetRunID(const char* in)
{ 
  _runId = TString(in); 
  //_runDir = _confDir;
  //_runDir += _runId;
  //mkdir(_runDir.Data(), S_IRWXU | S_IRWXG | S_IRWXO);
}
