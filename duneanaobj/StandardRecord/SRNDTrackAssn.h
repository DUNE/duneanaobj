/// \author  J. Wolcott <jwolcott@fnal.gov> & F. Akbar <fakbar@ur.rochester.edu>
/// \date    Nov. 2021

#ifndef DUNEANAOBJ_SRNDTRACKASSN_H
#define DUNEANAOBJ_SRNDTRACKASSN_H

#include "duneanaobj/StandardRecord/SRNDLAr.h"
#include "duneanaobj/StandardRecord/SRTMS.h"
#include "duneanaobj/StandardRecord/SRMINERvA.h"
#include "duneanaobj/StandardRecord/SRGAr.h"

namespace caf
{
  class SRNDTrackAssn
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SRNDLArID  larid;     ///< ND-LAr track identifier.  Get the actual SRTrack object using SRNDLAr::Reco<Track>() with this ID, e.g.`sr.nd.lar.Reco<Track>(sr.nd.trkmatch.extrap[1].larid)`
      SRTMSID    tmsid;     ///< TMS track identifier.   Get the actual SRTrack object using SRTMS::Track() with this ID, e.g.`sr.nd.lar.Track(sr.nd.trkmatch.extrap[1].tmsid)`
      SRMINERvAID  minervaid; ///< MINERvA track identifier.
      SRGArID    garid;     ///< GAr track identifier.


      float transdispl  = NaN;     ///< perpendicular distance between the two tracks at longitudinal position of matching point
      float angdispl    = NaN;     ///< angular difference between the two tracks at longitudinal position of matching point

      SRTrack trk;                   ///< new track object generated from synthesis of matched parts
  };
}

#endif //DUNEANAOBJ_SRNDTRACKASSN_H
