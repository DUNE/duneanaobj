////////////////////////////////////////////////////////////////////////
/// \file    SRNeutrinoEnergyBranch.h
/// \brief   Reconstructed particles
/// \author  J. Wolcott <jwolcott@fnal.gov>

#ifndef DUNEANAOBJ_SRRECOPARTICLESBRANCH_H
#define DUNEANAOBJ_SRRECOPARTICLESBRANCH_H

#include <vector>

#include "duneanaobj/StandardRecord/SRRecoParticle.h"

namespace caf
{

  class SRRecoParticlesBranch
  {
    public:
      int ndlp = 0;  // need these counters for SRProxy
      std::vector<SRRecoParticle> dlp;       ///< Particles reconstructed by DeepLearnPhysics machine learning stack

      int npandora = 0;
      std::vector<SRRecoParticle> pandora;   ///< Particles reconstructed by Pandora

      int npida = 0;
      std::vector<SRRecoParticle> pida;      ///< Particles bearing weights from PIDA algorithm

      int nsandreco = 0;
      std::vector<SRRecoParticle> sandreco;      ///< Particles reconstructed by Sandreco code

  };

} // caf

#endif //DUNEANAOBJ_SRRECOPARTICLESBRANCH_H
