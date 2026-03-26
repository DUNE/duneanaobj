////////////////////////////////////////////////////////////////////////
/// \file    SRTrack.h
/// \brief   Reconstructed track object
/// \author  J. Wolcott <jwolcott@fnal.gov>
/// \date    Apr. 2023
////////////////////////////////////////////////////////////////////////
#ifndef DUNEANAOBJ_SRRECOOBJBASE_H
#define DUNEANAOBJ_SRRECOOBJBASE_H

#include "duneanaobj/StandardRecord/SRTrueParticle.h"
#include "duneanaobj/StandardRecord/SREnums.h"

namespace caf
{

  /// Base class for reco objects (enables navigation between SRRecoParticle and the underlying object it was made from)
  class SRRecoObjBase
  {
    public:
      SRRecoParticleID part; // The particle this object is associated with
  };

} // caf

#endif //DUNEANAOBJ_SRRECOOBJBASE_H
