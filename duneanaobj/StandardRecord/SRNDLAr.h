////////////////////////////////////////////////////////////////////////
// \file    SRNDLAr.h
// \brief   ND-LAr reconstruction output.
// \author  J. Wolcott <jwolcott@fnal.gov>
// \date    Sept. 2021
////////////////////////////////////////////////////////////////////////
#ifndef DUNEANAOBJ_SRNDLAR_H
#define DUNEANAOBJ_SRNDLAR_H

#include "duneanaobj/StandardRecord/SRTrack.h"
#include "duneanaobj/StandardRecord/SRShower.h"
#include "duneanaobj/StandardRecord/SROpticalFlash.h"

namespace caf
{
  /// A reconstructed interaction in ND-LAr
  class SRNDLArInt
  {
    public:
      std::vector<SRTrack> tracks;
      std::size_t          ntracks  = 0;

      std::vector<SRShower> showers;
      std::size_t           nshowers = 0;
      
      std::vector<FlashMatch> flash;        ///< Attributes of matched flash
      
  };

  /// The information needed to uniquely identify an ND-LAr reco object
  class SRNDLArID
  {
  public:
    NDLAR_RECO_STACK reco = kUnknownNDLArReco;  ///< reco stack
    int        ixn  = -1;            ///< interaction ID
    int        idx  = -1;            ///< index in container
  };

  /// ND-LAr reconstruction output
  class SRNDLAr
  {
    public:
      std::vector<SRNDLArInt> dlp;       ///< Reconstructed interactions from Deep Learn Physics machine-learning reco
      std::size_t ndlp = 0;
      std::vector<SRNDLArInt> pandora;   ///< Reconstructed interactions from Pandora
      std::size_t npandora = 0;
      std::vector<SROpticalFlash> flashes;      ///< Collection of flashes
      std::size_t                 nflashes = 0;
      /// Convenience function for use mainly with SRNDTrackAssn.
      /// Given a specific reco pathway (specified with a SRNDLAr::RECO_STACK value),
      /// an interaction index, and a track index, return the associated reco object
      template <typename T>
      const T & Reco(const SRNDLArID& id);
  };

}
#endif //DUNEANAOBJ_SRNDLAR_H
