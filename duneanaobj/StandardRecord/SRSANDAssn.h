/// \author  J. Wolcott <jwolcott@fnal.gov> & S. Lanzi <samuele.lanzi@cnaf.infn.it>
/// \date    Aug. 2026

#ifndef DUNEANAOBJ_SRNDTRACKASSN_H
#define DUNEANAOBJ_SRNDTRACKASSN_H

#include "duneanaobj/StandardRecord/SRRecoObjBase.h"
#include "duneanaobj/StandardRecord/SRSAND.h"
#include "duneanaobj/StandardRecord/SREnums.h"

namespace caf
{
  class SRSANDAssn : public SRRecoObjBase
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      // idea: we want a sequence of subdetector elements.
      // fill them in the order of reconstructed direction...
      std::vector<SRSANDObjID> constituents;

      SRTrack trk;                   ///< new track object generated from synthesis of matched parts
  };
}

#endif //DUNEANAOBJ_SRNDTRACKASSN_H
