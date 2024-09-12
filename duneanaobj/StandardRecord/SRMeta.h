////////////////////////////////////////////////////////////////////////
/// \file    SRMeta.h
/// \brief   Metadata about the events in this file.
/// \author  J. Wolcott <jwolcott@fnal.gov>

#ifndef DUNEANAOBJ_SRMETA_H
#define DUNEANAOBJ_SRMETA_H

#include <limits>

#include "duneanaobj/StandardRecord/SREnums.h"

namespace caf
{

  class SRDetectorMeta
  {
    public:
      bool enabled = false;     ///< Does this detector have data present in this event?

      int run    = -1;
      int subrun = -1;
      int event  = -1;
      int subevt = -1;

      /// detector-dependent trigger type for the relevant readout window
      int triggertype = -1;

      unsigned long int readoutstart_s   = 0;   ///< GPS time of trigger readout start, seconds part
      unsigned int      readoutstart_ns  = 0;   ///< GPS time of trigger readout start, nanoseconds part
      unsigned long int readoutend_s     = 0;   ///< GPS time of trigger readout end, seconds part
      unsigned int      readoutend_ns    = 0;   ///< GPS time of trigger readout end, nanoseconds part

      /// For NDs that are part of the PRISM system,
      /// where (in meters relative to the beam center)
      /// was the detector center located for this event?
      double prism_offset = std::numeric_limits<double>::signaling_NaN();

  };

} // caf

#endif //DUNEANAOBJ_SRMETA_H
