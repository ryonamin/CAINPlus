#include "LcioWriter.h"
#include "Event.h"
// ROOT
#include "TLorentzVector.h"
// LCIO
#include "lcio.h"
#include "IO/LCWriter.h"
#include "IOIMPL/LCFactory.h"
#include "EVENT/LCCollection.h"
#include "IMPL/MCParticleImpl.h" 
#include "IMPL/LCCollectionVec.h"

ClassImp(LcioWriter)

LcioWriter::LcioWriter(const char* outputname)
{
  // open outfile
  _writer = lcio::LCFactory::getInstance()->createLCWriter();
  _writer->open( outputname , lcio::LCIO::WRITE_NEW ) ;
}

LcioWriter::~LcioWriter()
{
  _writer->close() ;
}

void LcioWriter::WriteEvent(Event& e)
{
  IMPL::LCEventImpl *lcioEvent = new IMPL::LCEventImpl();
  int run_number = 1;
  lcioEvent->setRunNumber( run_number );
  lcioEvent->setEventNumber( e._nEvt );

  IMPL::LCCollectionVec* mcpVec = new IMPL::LCCollectionVec(lcio::LCIO::MCPARTICLE);

  for (int ip = 0; ip < e._nParticles; ip++) {
    IMPL::MCParticleImpl* mcp = new IMPL::MCParticleImpl ;
    mcp->setPDG(e._pdg[ip]);
    float charge = 0.;
    if (e._pdg[ip]==11)  charge = -1.;
    if (e._pdg[ip]==-11) charge = 1.;
    mcp->setCharge(charge);
    const double vtxpos[3] = {double(e._vtx_x[ip]),double(e._vtx_y[ip]),double(e._vtx_z[ip])};
    mcp->setVertex(vtxpos);
    mcp->setTime(e._t[ip]);
    const float mom[3] = {e._p_x[ip],e._p_y[ip],e._p_z[ip]};
    mcp->setMomentum(mom);
    TLorentzVector p4(mom[0],mom[1],mom[2],e._e[ip]);
    mcp->setMass(p4.M());
    const float spin[3] = {e._s_x[ip],e._s_y[ip],e._s_z[ip]};
    mcp->setSpin(spin);

    mcpVec->addElement(mcp) ;
  }

  const char* collectionName = "MCParticle";
  lcioEvent->addCollection(mcpVec , collectionName) ;

  _writer->writeEvent( lcioEvent );

  delete lcioEvent;
}
