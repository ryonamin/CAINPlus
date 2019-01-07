#include "RootWriter.h"

// STL
#include <iostream>

// ROOT
#include "TFile.h"
#include "TTree.h"

ClassImp(RootWriter)


RootWriter::RootWriter(const char* outputname) : _e(0) 
{
  _fout = new TFile(outputname,"RECREATE");
  _tree = new TTree("cainEvent","");
  _tree->Branch( "evt"        , &_e._nEvt       , "evt/I"             );
  _tree->Branch( "nParticles" , &_e._nParticles , "nParticles/I"      );
  _tree->Branch( "pdg"        , _e._pdg         , "pdg[nParticles]/I" );
  _tree->Branch( "vtx_x"      , _e._vtx_x       , "vtx_x[nParticles]" );
  _tree->Branch( "vtx_y"      , _e._vtx_y       , "vtx_y[nParticles]" );
  _tree->Branch( "vtx_z"      , _e._vtx_z       , "vtx_z[nParticles]" );
  _tree->Branch( "t"          , _e._t           , "t[nParticles]"     );
  _tree->Branch( "p_x"        , _e._p_x         , "p_x[nParticles]"   );
  _tree->Branch( "p_y"        , _e._p_y         , "p_y[nParticles]"   );
  _tree->Branch( "p_z"        , _e._p_z         , "p_z[nParticles]"   );
  _tree->Branch( "e"          , _e._e           , "e[nParticles]"     );
  _tree->Branch( "s_x"        , _e._s_x         , "s_x[nParticles]"   );
  _tree->Branch( "s_y"        , _e._s_y         , "s_y[nParticles]"   );
  _tree->Branch( "s_z"        , _e._s_z         , "s_z[nParticles]"   );
}

RootWriter::~RootWriter()
{
  _tree->Write();
  _fout->Close();
  delete _fout; // _tree has been associated to _fout and thus be delted at the same time. 
}

void RootWriter::WriteEvent(Event& e)
{
  _e._nEvt = e._nEvt;
  _e._nParticles = e._nParticles;
  for (int ip = 0; ip < e._nParticles; ip++) {
    _e._pdg[ip]   = e._pdg[ip];
    _e._vtx_x[ip] = e._vtx_x[ip];
    _e._vtx_y[ip] = e._vtx_y[ip];
    _e._vtx_z[ip] = e._vtx_z[ip];
    _e._t[ip]     = e._t[ip];
    _e._p_x[ip]   = e._p_x[ip];
    _e._p_y[ip]   = e._p_y[ip];
    _e._p_z[ip]   = e._p_z[ip];
    _e._e[ip]     = e._e[ip];
    _e._s_x[ip]   = e._s_x[ip];
    _e._s_y[ip]   = e._s_y[ip];
    _e._s_z[ip]   = e._s_z[ip];
  }
  _tree->Fill();
}
