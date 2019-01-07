#ifndef __LCIOWRITER_H__
#define __LCIOWRITER_H__
#include "Event.h"
// ROOT
#include "TObject.h"
// LCIO
#include "IO/LCWriter.h"
#include "IMPL/LCEventImpl.h" 
class LcioWriter : public TObject
{
  public:
    LcioWriter(const char* outputname);
    ~LcioWriter();
    void WriteEvent(Event& e);
  private:
    IO::LCWriter* _writer;

  ClassDef(LcioWriter,1)
};

#endif
