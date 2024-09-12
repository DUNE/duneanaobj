////////////////////////////////////////////////////////////////////////
// \file    SRNDLAr.h
// \brief   ND-LAr reconstruction output.
// \author  J. Wolcott <jwolcott@fnal.gov>
// \date    Mar. 2023
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRMINERVA_H
#define DUNEANAOBJ_SRMINERVA_H

#include <vector>
#include "duneanaobj/StandardRecord/SRTrack.h"
#include "duneanaobj/StandardRecord/SRShower.h"

namespace caf
{
  /// A MINERvA reconstructed interaction
  class SRMINERvAInt
  {
    public:
      std::vector<caf::SRTrack> tracks;
      std::size_t               ntracks  = 0;

      // I think this is where MINERvA "blobs" should go?
      std::vector<caf::SRShower> showers;
      std::size_t                nshowers  = 0;
  };

  /// The information needed to uniquely identify a MINERvA reco object
  class SRMINERvAID
  {
  public: 
    int        ixn  = -1;            ///< interaction ID
    int        idx  = -1;            ///< index in container
  };

  // just a placeholder for the moment
  class SRMINERvA
  {
    public:
      std::vector<SRMINERvAInt> ixn;       ///< Reconstructed interactions
      std::size_t nixn = 0;

      /// Convenience function for use mainly with SRNDTrackAssn and SRNDShowerAssn.
      /// Given an interaction index and object index, return the associated reco object
      template <typename T>
      const T & Reco(const SRMINERvAID& id);
  };

} // caf

#endif //DUNEANAOBJ_SRMINERVA_H
