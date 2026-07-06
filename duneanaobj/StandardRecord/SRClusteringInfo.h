////////////////////////////////////////////////////////////////////////
/// \file    SRClusteringInfo.h
/// \brief   Reconstructed particle clustering and voxel metrics
/// \author  Pierre Granger (pgranger@fnal.gov)
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRCLUSTERINGINFO_H
#define DUNEANAOBJ_SRCLUSTERINGINFO_H

#include <cstdint>

namespace caf
{
  class SRClusteringInfo
  {
    public:
      SRClusteringInfo() = default;
      virtual ~SRClusteringInfo() = default;

      int64_t size = -1;             ///< Number of hits/voxels/points in the cluster
      int64_t num_fragments = -1;    ///< Number of sub-clusters or fragments
  };
}

#endif // DUNEANAOBJ_SRCLUSTERINGINFO_H
