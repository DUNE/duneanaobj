////////////////////////////////////////////////////////////////////////
// \file    SRGAr.h
// \brief   ND-GAr reconstruction output.
// \author  J. Wolcott <jwolcott@fnal.gov>
// \date    Jan. 2022
////////////////////////////////////////////////////////////////////////
#ifndef DUNEANAOBJ_SRGAR_H
#define DUNEANAOBJ_SRGAR_H

#include "duneanaobj/StandardRecord/SRGArParticle.h"
#include "duneanaobj/StandardRecord/SRGArTrack.h"
#include "duneanaobj/StandardRecord/SRGArECAL.h"

namespace caf
{
  /// An ND-GAr reconstructed neutrino interaction
  class SRGArInt
  {
    public:
      std::vector<SRGArParticle> particles;
      std::size_t                nparticles  = 0;

      std::vector<SRGArTrack> tracks;
      std::size_t             ntracks  = 0;

      std::vector<SRGArECAL> ecalclusters;
      std::size_t            necalclusters = 0;

      std::vector<SRGArECAL> muidclusters;
      std::size_t            nmuidclusters = 0;

      // legacy parametric reco fields

      int nFSP;
      std::vector<int> pdg;
      std::vector<float> ptrue;
      std::vector<float> trkLen;
      std::vector<float> trkLenPerp;
      std::vector<float> partEvReco;
      int gastpc_pi_pl_mult;
      int gastpc_pi_min_mult;
  };

  /// The information needed to uniquely identify a ND-GAr reco object
  class SRGArID
  {
    public:
    
    int        ixn  = -1;            ///< interaction ID
    int        idx  = -1;            ///< index in container
  };

  /// ND-GAr reconstruction output
  class SRGAr
  {
    public:
      std::size_t nixn = 0;
      std::vector<SRGArInt> ixn;       ///< Reconstructed interactions
  };

}
#endif //DUNEANAOBJ_SRGAR_H
