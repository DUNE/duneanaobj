////////////////////////////////////////////////////////////////////////
/// \file    SRTrack.h
/// \brief   Reconstructed track object
/// \author  J. Wolcott <jwolcott@fnal.gov>
/// \date    Apr. 2023
////////////////////////////////////////////////////////////////////////
#ifndef DUNEANAOBJ_SRRECOOBJBASE_H
#define DUNEANAOBJ_SRRECOOBJBASE_H

#include "duneanaobj/StandardRecord/SRTrueParticle.h"

namespace caf
{

  /// Base class for reco objects (allows a base pointer to be stored in SRRecoParticle)
  // Leave it empty because inherited members are easily overlooked in the derived classes
  class SRRecoObjBase
  {};

} // caf

#endif //DUNEANAOBJ_SRRECOOBJBASE_H
