////////////////////////////////////////////////////////////////////////
// \file    SRFD.h
// \brief   FD reconstruction output.
// \author  J. Wolcott <jwolcott@fnal.gov>
// \date    Mar. 2023
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRFD_H
#define DUNEANAOBJ_SRFD_H

#include "duneanaobj/StandardRecord/SRShower.h"
#include "duneanaobj/StandardRecord/SRTrack.h"
#include "duneanaobj/StandardRecord/SRLArRecoParticle.h"

namespace caf
{
  /// A FD reconstructed neutrino interaction
  class SRFDInt
  {
    public:
      // these are just placeholders.
      // need to coordinate w/ FD reco folks to put something sensible in here
      std::vector<SRTrack> tracks;
      std::size_t          ntracks  = 0;    // these counters used by SRProxy

      std::vector<SRShower> showers;
      std::size_t           nshowers = 0;

      std::vector<SRLArRecoParticle> lar_particles;
      std::size_t                    nlar_particles = 0;
  };

  /// The information needed to uniquely identify a FD reco object
  struct SRFDID
  {
    FD_RECO_STACK reco = kUnknownFDReco;  ///< reco stack
    int        ixn  = -1;            ///< interaction ID
    int        idx  = -1;            ///< index in container
  };

  class SRFD
  {
    public:

      std::vector<SRFDInt> pandora;       ///< Reconstructed interactions
      std::size_t npandora = 0;

      /// Convenience function:
      /// Given a specific reco pathway (specified with a SRFD::RECO_STACK value),
      /// an interaction index, and a track index, return the associated reco object
      template <typename T>
      const T & Reco(const SRFDID& id);
  };

} // caf

#endif //DUNEANAOBJ_SRFD_H
