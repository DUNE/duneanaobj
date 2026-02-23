////////////////////////////////////////////////////////////////////////
/// \file    SRSANDDetectorMeta.h
/// \brief   Metadata for the SAND detector, derived from SRDetectorMeta
/// \author  Silvia Repetto / aggiornamento Feb 2026
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRSANDDETECTORMETA_H
#define DUNEANAOBJ_SRSANDDETECTORMETA_H

#include "duneanaobj/StandardRecord/SRMeta.h"
#include "duneanaobj/StandardRecord/SREnums.h"

namespace caf
{
  /// \brief Metadata specific to SAND detector events
  class SRSANDDetectorMeta
  {
    public:
    
      bool enabled = false;  

      int run    = -1;
      int subrun = -1;
      int event  = -1;
      int subevt = -1;

      int triggertype = -1;
      bool triggered = true;

      unsigned long int readoutstart_s  = 0;
      unsigned int      readoutstart_ns = 0;
      unsigned long int readoutend_s    = 0;
      unsigned int      readoutend_ns   = 0;

      double prism_offset = std::numeric_limits<double>::signaling_NaN();

      // Ricostruzione e selezione
      SelectionType selection_type   = kGRAINcontained;
      RecoType      grain_reco_type  = kRealReco;
      RecoType      ecal_reco_type   = kNone;
      RecoType      tracker_reco_type= kSmearing;

      // Scattering mode dell'interazione (QE, DIS, MEC, ecc.)
      ScatteringMode interaction_type = kQE;

      void SetDefaults() {
        interaction_type = caf::kQE;
        selection_type  = caf::kGRAINcontained;
        grain_reco_type = caf::kRealReco;
        ecal_reco_type  = caf::kNone;
        tracker_reco_type = caf::kSmearing;
    }
  };
}

#endif // DUNEANAOBJ_SRSANDDETECTORMETA_H