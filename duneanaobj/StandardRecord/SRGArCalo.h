////////////////////////////////////////////////////////////////////////
// \file    SRGArCalo.h
// \brief   Reconstructed GAr calo cluster object
// \author  F. Martinez <f.martinezlopez@qmul.ac.uk>
// \date    Jan. 2023
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRGARCALO_H
#define DUNEANAOBJ_SRGARCALO_H

#include "duneanaobj/StandardRecord/SRVector3D.h"
#include "duneanaobj/StandardRecord/SRTrueParticle.h"

namespace caf
{
  /// Types of GAr calo clusters
  enum CaloClusterType
  {
    kUnknownCluster = 0,
    kECalCluster    = 1,
    kMuIDCluster    = 2
  };

  class SRGArCalo
  {
    public:

      CaloClusterType  cluster_type = CaloClusterType::kUnknownCluster;   ///< Type of GAr calo cluster

      SRVector3D position;                 ///< Calo cluster 3D position [cm]
      float E = -999.;                     ///< Energy corresponding to this cluster [GeV]

      int hits_in_cluster = -999;          ///< Total number of Calo hits in cluster

      int garsoft_calo_id = -999;          ///< GArSoft CaloId for calo cluster

      int garsoft_trk_assn = -999;         ///< GArSoft TrackId associated to calo cluster

      std::vector<TrueParticleID> truth;   ///< Associated SRTrueParticle(s), if relevant (use SRTruthBranch::Particle() with these IDs to grab them)
      std::vector<float>   truthOverlap;   ///< Fractional overlap between this cluster and true particle
  };

}

#endif //DUNEANAOBJ_SRGARCALO_H
