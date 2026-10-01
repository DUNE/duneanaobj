////////////////////////////////////////////////////////////////////////
/// \file    SRBeamInstrumentation.h
/// \brief   H4-VLE beamline instrumentation for a test-beam trigger
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRBEAMINSTRUMENTATION_H
#define DUNEANAOBJ_SRBEAMINSTRUMENTATION_H

#include <limits>
#include <vector>

#include "duneanaobj/StandardRecord/SRVector3D.h"

namespace caf
{
  /// \brief Beamline instrumentation readings for a single test-beam trigger.
  ///
  /// Taken from `beam::ProtoDUNEBeamEvent`, i.e. the CERN H4-VLE beam line that feeds
  /// ProtoDUNE-SP. These are the quantities that beam-quality and beam-PID selections are
  /// built from: the spectrometer momentum, the time-of-flight, the two Cherenkov counters
  /// and the fiber-monitor multiplicities.
  ///
  /// Entirely separate from the NuMI fields of SRBeamBranch, which describe a neutrino spill.
  class SRBeamInstrumentation
  {
    private:
      // save on typing below
      constexpr static float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      bool valid   = false;  ///< Was a beam event found and (data only) matched to this trigger?
      int  trigger = -1;     ///< Timing-system trigger word

      /// @name Spectrometer momentum
      ///@{
      float P     = NaN;           ///< Momentum used downstream [GeV/c]: #P_raw times the MC correction factor for simulation, equal to #P_raw for data
      float P_raw = NaN;           ///< Leading momentum candidate exactly as read from the beam event, uncorrected [GeV/c]
      std::vector<float> momenta;  ///< All momentum candidates, uncorrected [GeV/c]
      int nmomenta = -1;           ///< Number of entries in #momenta
      ///@}

      /// @name Beamline track projected towards the TPC (leading track only)
      ///@{
      SRVector3D pos;    ///< End point of the projected beamline track [cm]
      SRVector3D dir;    ///< Unit direction at that end point
      int ntracks = -1;  ///< Beamline tracks reconstructed in the fiber monitors
      ///@}

      /// @name Time of flight
      ///@{
      float TOF      = NaN;         ///< Selected time of flight [ns] (ProtoDUNEBeamEvent::GetTOF); the value the PID cuts use
      int   TOF_chan = -1;          ///< Channel combination for #TOF; -1 means no valid TOF
      std::vector<float> TOFs;      ///< All time-of-flight measurements [ns]
      std::vector<int>   TOF_chans; ///< Channel combination for the matching entry of #TOFs
      ///@}

      /// @name Cherenkov counters
      ///@{
      int   C0          = -1;   ///< Low-pressure Cherenkov status
      int   C1          = -1;   ///< High-pressure Cherenkov status
      float C0_pressure = NaN;  ///< Low-pressure Cherenkov pressure
      float C1_pressure = NaN;  ///< High-pressure Cherenkov pressure
      ///@}

      /// @name Fibers struck in the three spectrometer monitors
      ///@{
      int nfibers_p1 = -1;  ///< Monitor XBPF022697, raw active-fiber count
      int nfibers_p2 = -1;  ///< Monitor XBPF022701, raw active-fiber count
      int nfibers_p3 = -1;  ///< Monitor XBPF022702, raw active-fiber count

      /// \brief Exactly one non-glitching fiber in each of the three momentum monitors.
      ///
      /// Stricter than `nfibers_pN == 1`: fibers flagged in the monitor's glitch mask are
      /// discarded before counting. This is the momentum-unambiguity requirement, i.e. the
      /// "reject events with degenerate fiber hits" beam-quality cut.
      bool perfect_momentum = false;
      ///@}

      /// \brief Beamline PID hypotheses, as PDG codes.
      ///
      /// The CERN-calibration selection on time of flight and the two Cherenkov counters, at the
      /// nominal beam momentum. Empty when the inputs are invalid (no TOF channel, or Cherenkov
      /// status -1) or when the nominal momentum is not one of 1, 2, 3, 6, 7 GeV/c.
      ///
      /// \warning Meaningful for data. In simulation the Cherenkov counters are typically not
      /// simulated (status and pressure read back as 0), so any PID derived here is an artefact
      /// of that default rather than a measurement — check #C0/#C1 before trusting it.
      std::vector<int> PDG_candidates;
  };
}

#endif //DUNEANAOBJ_SRBEAMINSTRUMENTATION_H
