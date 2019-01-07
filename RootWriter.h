#ifndef __ROOTWRITER_H__
#define __ROOTWRITER_H__
#include "TObject.h"
#include "Event.h"

class TFile;
class TTree;
class RootWriter : public TObject
{
  public :
   RootWriter(const char* outputname);
   ~RootWriter();
   void WriteEvent(Event& e);

  private :
   TFile* _fout;
   TTree* _tree;

   Event _e; 

  ClassDef(RootWriter,1)
};

#endif
