/// \author  J. Wolcott <jwolcott@fnal.gov> & F. Akbar <fakbar@ur.rochester.edu>
/// \date    Nov. 2021

#ifndef DUNEANAOBJ_SRNDTRACKASSN_H
#define DUNEANAOBJ_SRNDTRACKASSN_H

#include "duneanaobj/StandardRecord/SRRecoObjBase.h"

#include "duneanaobj/StandardRecord/SRNDLAr.h"
#include "duneanaobj/StandardRecord/SRTMS.h"
#include "duneanaobj/StandardRecord/SRMINERvA.h"
#include "duneanaobj/StandardRecord/SRGAr.h"
#include "duneanaobj/StandardRecord/SREnums.h"

namespace caf
{
  class SRNDTrackAssn : public SRRecoObjBase
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SRNDLArID  larid;     ///< ND-LAr track identifier.  Get the actual SRTrack object using SRNDLAr::Reco<Track>() with this ID, e.g.`sr.nd.lar.Reco<Track>(sr.nd.trkmatch.extrap[1].larid)`
      SRTMSID    tmsid;     ///< TMS track identifier.   Get the actual SRTrack object using SRTMS::Track() with this ID, e.g.`sr.nd.lar.Track(sr.nd.trkmatch.extrap[1].tmsid)`
      SRMINERvAID  minervaid; ///< MINERvA track identifier.
      SRGArID    garid;     ///< GAr track identifier.


      float transdispl  = NaN;     ///< perpendicular distance between the two tracks at longitudinal position of matching point
      float cosangdispl = NaN;     ///< cosine of the angular difference between the two tracks at longitudinal position of matching point
      float matchScore  = NaN;     ///< quantifies how well a LAr and TMS track match each other
      bool trueMatch = false;      ///< whether the LAr and TMS track have the same truth ID or not

      double deltaX = NaN;        ///< how far apart in x the projected end point of the LAr track is to the start point of the TMS track
      double deltaY = NaN;        ///< how far apart in y the projected end point of the LAr track is to the start point of the TMS track
      double deltaThetaX = NaN;   ///< how far apart in x angle the projected end point of the LAr track is to the start point of the TMS track
      double deltaThetaY = NaN;   ///< how far apart in y angle the projected end point of the LAr track is to the start point of the TMS track
      double deltaT = NaN;        ///< time difference between the LAr track and the TMS track
      // The above five quantities are components of the matchScore. I anticipate it will be helpful for troubleshooting to save them

      NDRecoMatchType matchType = caf::NDRecoMatchType::kUndeclared; ///< specifies how the match was performed

      SRTrack trk;                   ///< new track object generated from synthesis of matched parts
  };
}

#endif //DUNEANAOBJ_SRNDTRACKASSN_H
