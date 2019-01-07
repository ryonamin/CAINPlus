#!/bin/sh

# Setup ROOT
export PATH=/cvmfs/sft.cern.ch/lcg/contrib/gcc/4.9.3/x86_64-slc6/bin:${PATH}
export LD_LIBRARY_PATH=/cvmfs/sft.cern.ch/lcg/contrib/gcc/4.9.3/x86_64-slc6/lib64:/cvmfs/sft.cern.ch/lcg/contrib/gcc/4.9.3/x86_64-slc6/lib:${LD_LIBRARY_PATH}
source /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/root/6.08.06/bin/thisroot.sh 

# Setup LCIO
export LCIO=/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lcio/v02-12-01
export PATH=${LCIO}/bin:${PATH}
export LD_LIBRARY_PATH=${LCIO}/lib:${LD_LIBRARY_PATH}

# Setup CAIN
export CAINTOP="/home/ilc/yonamine/work/Yosuke/cain243"
export PATH=${CAINTOP}/bin:${PATH}

# Setup CAINPlus
export CAINPLUS=/home/ilc/yonamine/work/Yosuke/Git/CAINPlus
export PATH=${CAINPLUS}/bin:${PATH}
export LD_LIBRARY_PATH=${CAINPLUS}:${LD_LIBRARY_PATH}
