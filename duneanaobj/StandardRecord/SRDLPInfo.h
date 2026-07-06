////////////////////////////////////////////////////////////////////////
/// \file    SRDLPInfo.h
/// \brief   DLP/SPINE neural network-specific tracking variables and metadata
/// \author  Pierre Granger (pgranger@fnal.gov)
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRDLPINFO_H
#define DUNEANAOBJ_SRDLPINFO_H

#include <vector>
#include <limits>
#include "duneanaobj/StandardRecord/SREnums.h"

namespace caf
{
  class SRDLPInfo
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SRDLPInfo() = default;
      virtual ~SRDLPInfo() = default;

      DLPPid    pid = kDLPUnknown;        ///< DLP-specific classification species
      DLPShape  shape = kDLPUndefined;    ///< DLP-specific semantic shape type
      
      bool      is_valid = false;         ///< Meets quality thresholds
      bool      is_cathode_crosser = false;
      bool      is_time_contained = false;

      float     start_straightness = NaN; ///< Track straightness metric
      float     axial_spread = NaN;
      float     directional_spread = NaN;
      float     cathode_offset = NaN;     ///< Distance to cathode [cm]
      float     vertex_distance = NaN;    ///< Distance to interaction vertex [cm]

  };
}

#endif // DUNEANAOBJ_SRDLPINFO_H
