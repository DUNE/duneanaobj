////////////////////////////////////////////////////////////////////////
// \file    SRSAND.h
// \brief   SAND reconstruction output.
// \author  L.Di Noto
// \date    Jan. 2023
////////////////////////////////////////////////////////////////////////
#ifndef DUNEANAOBJ_SRSAND_H
#define DUNEANAOBJ_SRSAND_H

#include "duneanaobj/StandardRecord/SRTrack.h"
#include "duneanaobj/StandardRecord/SRShower.h"
#include "duneanaobj/StandardRecord/SRRecoParticle.h"


namespace caf
{
  /// A SAND reconstructed neutrino interaction
  class SRSANDInt
  {
    public:
      std::vector<SRTrack> tracks;
      std::size_t          ntracks  = 0;

      std::vector<SRShower> showers;
      std::size_t           nshowers = 0;
  };

  /// SAND reconstruction output
  class SRSAND
  {
    public:
      /// The information needed to uniquely identify a SAND reco object
      struct ID
      {
        int        ixn  = -1;            ///< interaction ID
        int        idx  = -1;            ///< index in container
      };

      std::size_t nixn = 0;
      std::vector<SRSANDInt> ixn;       ///< Reconstructed interactions

    };

}
#endif //DUNEANAOBJ_SRSAND_H
