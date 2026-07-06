#ifndef DUNEANAOBJ_SRLARTPCINFO_H
#define DUNEANAOBJ_SRLARTPCINFO_H

#include <limits>
#include "duneanaobj/StandardRecord/SREnums.h"

namespace caf
{
  class SRLArTPCInfo
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SRLArTPCInfo() = default;

      LArTPCPid   pid = kLArTPCUnknown;           ///< Assigned particle species
      LArTPCShape shape = kLArTPCUnknownShape;   ///< Semantic shape classification
      bool        is_valid = false;
      bool        is_cathode_crosser = false;
      bool        is_time_contained = false;
      float       start_straightness = NaN;   ///< Track straightness metric
      float       axial_spread = NaN;         ///< Spatial axial spread
      float       directional_spread = NaN;   ///< Angular directional spread
      float       cathode_offset = NaN;       ///< Distance to cathode [cm]
      float       vertex_distance = NaN;      ///< Distance to interaction vertex [cm]
  };
}

#endif // DUNEANAOBJ_SRLARTPCINFO_H
