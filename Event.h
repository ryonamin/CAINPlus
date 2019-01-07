#ifndef __EVENT_H__
#define __EVENT_H__

const int NMAXPARTICLES = 50000;

class Event 
{
  public:
   Event(int ev) : _nEvt(ev) {}

   int    _nEvt;
   int    _nParticles;
   int    _pdg[NMAXPARTICLES];
   float  _vtx_x[NMAXPARTICLES];    
   float  _vtx_y[NMAXPARTICLES];
   float  _vtx_z[NMAXPARTICLES];
   float  _t[NMAXPARTICLES];
   float  _p_x[NMAXPARTICLES];
   float  _p_y[NMAXPARTICLES];
   float  _p_z[NMAXPARTICLES];
   float  _e[NMAXPARTICLES];
   float  _s_x[NMAXPARTICLES];
   float  _s_y[NMAXPARTICLES];
   float  _s_z[NMAXPARTICLES];

};
#endif
