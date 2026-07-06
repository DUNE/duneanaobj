////////////////////////////////////////////////////////////////////////
/// \file    SRECALCluster.h
/// \brief   Reconstructed ECAL cluster object
/// \author  D. Casazza, L. Di Noto
/// \date    Dec. 2024
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRECALCLUSTER_H
#define DUNEANAOBJ_SRECALCLUSTER_H

#include "duneanaobj/StandardRecord/SRVector3D.h"
#include "duneanaobj/StandardRecord/SRRecoObjBase.h"

namespace caf
{
  class SRECALCluster : public SRRecoObjBase
  {
    public:
      int id; ///< Cluster id 
      SRVector3D position;  ///< Cluster barycenter position weighted on energy [cm]
      SRVector3D var_position; //< Cluster variance of x,y,z position coordinates [cm]
      float time; ///< Cluster time weighted on energy [ns]
      SRVector3D start;      ///< Cluster 3D start point [cm]
      SRVector3D direction;  ///< Cluster directiion versor 
      float E;    ///< Reconstructed energy [MeV] 
      int num_cells; ///< Total number of cells in the cluster

      std::vector<TrueParticleID> truth;              ///< Associated SRTrueParticle(s), if relevant (use SRTruthBranch::Particle() with these IDs to grab them)
      std::vector<float>   truthOverlap;              ///< Fractional overlap between this shower and true particle
  };

}

#endif //DUNEANAOBJ_SRECALCluster_H
