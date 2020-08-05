ROOTLIBS = $(shell root-config --libs)
CXXFLAGS = $(shell root-config --cflags)

INCPATH = -I${LCIO}/src/cpp/include -I${LCIO}/include
LIBS = -L${LCIO}/lib -llcio
CXXFLAGS += -std=c++11

OBJS = CainWrapper.o RootWriter.o LcioWriter.o Event.o
INCS = CainWrapper.h RootWriter.h LcioWriter.h Event.h
SRCS = CainWrapper.cc RootWriter.cc LcioWriter.cc Event.cc

all	: ${OBJS} Dict.o

ifeq ("$(wildcard bin)","")
	@mkdir bin 
endif

ifeq (${LCIO},)
	$(error Error due to missing LCIO path)
endif
	g++ ${CXXFLAGS} main.cc ${OBJS} Dict.o ${ROOTLIBS} ${INCPATH} ${LIBS} -o bin/cain+ 

${OBJS}	: ${SRCS} ${INCS} 
	g++ ${CXXFLAGS} ${ROOTLIBS} ${INCPATH} ${LIBS} -c ${SRCS}

Dict.o : ${INCS} LinkDef.h
	rootcint -f Dict.cxx -c ${INCS} ${INCPATH} LinkDef.h 
	g++ ${ROOTLIBS} ${CXXFLAGS} ${INCPATH} -c Dict.cxx

clean :
	rm Dict.cxx Dict.h *~ *.o *.pcm 
