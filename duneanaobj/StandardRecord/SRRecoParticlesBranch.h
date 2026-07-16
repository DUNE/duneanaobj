////////////////////////////////////////////////////////////////////////
/// \file    SRRecoParticlesBranch.h
/// \brief   Reconstructed particles associated with an interaction
/// \author  J. Wolcott <jwolcott@fnal.gov>
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRRECOPARTICLESBRANCH_H
#define DUNEANAOBJ_SRRECOPARTICLESBRANCH_H

#include <vector>

#include "duneanaobj/StandardRecord/SRRecoParticle.h"

namespace caf
{

  class SRRecoParticlesBranch
  {
    public:
      int nrecopart = 0;                     ///< Number of particles in the branch
      std::vector<SRRecoParticle> recopart;  ///< Reconstructed particles associated with this interaction
  };

} // caf

#endif //DUNEANAOBJ_SRRECOPARTICLESBRANCH_H
