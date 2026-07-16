////////////////////////////////////////////////////////////////////////
/// \file    SRSpineInfo.h
/// \brief   SPINE-specific reconstruction metrics
/// \author  Pierre Granger (pgranger@fnal.gov)
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRSPINEINFO_H
#define DUNEANAOBJ_SRSPINEINFO_H

#include <limits>

namespace caf
{
  class SRSpineInfo
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SRSpineInfo() = default;
      virtual ~SRSpineInfo() = default;

      bool  is_valid = false;             ///< Is the SPINE reconstruction valid for this particle
      float start_straightness = NaN;     ///< Straightness of the track near start
      float axial_spread = NaN;           ///< Axial voxel spread of the particle's cluster
      float directional_spread = NaN;     ///< Directional voxel spread of the particle's cluster
  };
}

#endif // DUNEANAOBJ_SRSPINEINFO_H
