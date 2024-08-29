/// \author  J. Wolcott <jwolcott@fnal.gov>
/// \date    Apr. 2023

#ifndef DUNEANAOBJ_SRNDSHOWERASSN_H
#define DUNEANAOBJ_SRNDSHOWERASSN_H

#include "duneanaobj/StandardRecord/SRShower.h"
#include "duneanaobj/StandardRecord/SRNDLAr.h"
#include "duneanaobj/StandardRecord/SRTMS.h"
#include "duneanaobj/StandardRecord/SRMINERvA.h"
#include "duneanaobj/StandardRecord/SRGAr.h"
namespace caf
{
  class SRNDShowerAssn
  {
    public:
      // note: no TMS or GAr right now since we don't have anything to connect to ND-LAr,
      // but the pattern is straightforward to extend if those become useful
      SRNDLArID     larid;      ///< ND-LAr shower identifier.  Get the actual SRShower object using SRNDLAr::Reco<Shower>() with this ID, e.g.`sr.nd.lar.Reco<Shower>(sr.nd.shwmatch.extrap[1].larid)`
      SRMINERvAID minervaid;  ///< MINERvA shower identifier.

      SRShower shw;             ///< new shower object generated from synthesis of matched parts
  };
}

#endif //DUNEANAOBJ_SRNDSHOWERASSN_H
