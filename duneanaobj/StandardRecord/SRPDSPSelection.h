////////////////////////////////////////////////////////////////////////
/// \file    SRPDSPSelection.h
/// \brief   ProtoDUNE-SP pi+ absorption / charge-exchange event selection
/// \author  D. Pullia <dariopullia@gmail.com>
///
/// Port of the selection in protoduneana's runEventSelection.cc /
/// SelectionDefinitions.h (EventSelection.fcl), which classified each beam
/// event into a category (selection_ID) rather than passing or failing it.
/// It is stored twice: `legacy` reproduces the old chain exactly, quirks
/// included; `improved` runs the same chain with a few agreed fixes. Both
/// read the same inputs, so every difference between them is due to logic.
/// See old_analysis_reference/SELECTION_STEPS.md for the original chain.
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRPDSPSELECTION_H
#define DUNEANAOBJ_SRPDSPSELECTION_H

#include <limits>
#include <vector>

#include "duneanaobj/StandardRecord/SRVector3D.h"

namespace caf
{
  /// Values of SRPDSPSelection::event_class. 1-7 are the old selection_ID.
  enum PDSPEventClass
  {
    kPDSPNotEvaluated  = -1, ///< Selection not run (disabled, or required products missing)
    kPDSPFailPrefilter =  0, ///< Dropped by the old Filter() calls: beam-particle identity / beam-line quality
    kPDSPAbs           =  1, ///< Absorption candidate
    kPDSPCex           =  2, ///< Charge-exchange candidate (pi0-like shower daughter)
    kPDSPRejectedInt   =  3, ///< Pion-like daughter ("other inelastic")
    kPDSPPastFV        =  4, ///< Beam track ends past the fiducial z cut (the fit's "APA2" sideband)
    kPDSPFailBeamCut   =  5, ///< Beam track start/direction not consistent with the beam
    kPDSPNoBeamTrack   =  6, ///< No beam track with calorimetry (includes events with no beam slice)
    kPDSPMichel        =  7  ///< Michel-like activity at the chosen end of the beam track
  };

  /// One direct Pandora daughter of the beam PFParticle, as seen by the selection.
  /// Values are the ones the cuts compared, including the old code's sentinels
  /// (-999 for "missing", -9999 for an empty dE/dx, 9999 / -1 for an empty chi2).
  class SRPDSPSelDaughter
  {
    public:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

      int   pfp_id        = -999;  ///< recob::PFParticle::Self()
      int   nhits_coll    = -999;  ///< Collection-plane hits of the PFParticle
      float track_score   = NaN;   ///< CNN track score, collection plane, charge weighted (-999 if no charge)

      int   track_id      = -999;  ///< Forced track fit (pandora2Track) ID; -999 if none
      int   ncalo_pts     = -999;  ///< Collection-plane calorimetry points of the forced track
      float trunc_dEdx    = NaN;   ///< 16-84% truncated-mean dE/dx [MeV/cm]; -9999 if no valid point
      float chi2_proton   = NaN;   ///< Chi2 against the proton dE/dx template
      int   chi2_ndof     = -999;  ///< Points used in chi2_proton
      bool  is_pion_like  = false; ///< This daughter vetoes the event (class 3)

      int        shower_id     = -999;  ///< Forced shower fit (pandora2Shower) ID; -999 if none
      SRVector3D shower_start;          ///< Shower start [cm]
      float      shower_dist   = NaN;   ///< Beam-track end to shower start [cm]
      float      shower_energy = NaN;   ///< Calorimetric shower energy [MeV]; -999 if no collection calo
      bool       is_pi0_shower = false; ///< This daughter tags the event as charge exchange (class 2)
  };

  /// Outcome of the selection for one implementation (legacy or improved).
  class SRPDSPSelection
  {
    public:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

      int  event_class           = kPDSPNotEvaluated; ///< PDSPEventClass: old selection_ID, or 0 / -1
      int  event_class_inclusive = kPDSPNotEvaluated; ///< Old selection_ID_inclusive: 1 interacting, 2 past FV, 3 fail beam cut, 4 no beam track, 5 Michel; 0 / -1 as event_class
      bool pass_prefilter        = false; ///< Beam-particle identity and beam-line quality (the old Filter() calls)

      /// @name Step results, evaluated for every event regardless of order or prefilter.
      /// event_class applies them in the order 6, 5, 4, 7, 3, 2, 1.
      ///@{
      bool beam_is_track     = false; ///< Old primary_isBeamType: beam PFP has a track and collection calorimetry
      bool pass_beam_cut     = false; ///< Old passBeamCut: start within N sigma of the beam spot, direction within cos cut
      bool ends_in_fv        = false; ///< Old primary_ends_inAPA3: end z below the fiducial cut
      bool michel_tagged     = false; ///< Old vertex_cut: mean Michel score in the vertex window above the cut
      bool has_pion_daughter = false; ///< Not old has_noPion_daughter
      bool has_pi0_shower    = false; ///< Old has_shower_dist_energy
      ///@}

      /// @name Beam particle choice
      ///@{
      int   nbeam_slices       = -1;    ///< Slices containing a primary PFParticle tagged IsTestBeam
      int   beam_slice         = -1;    ///< Slice index of the chosen PFParticle
      int   beam_pfp_id        = -1;    ///< recob::PFParticle::Self() of the chosen PFParticle
      bool  beam_pfp_is_tagged = false; ///< The chosen PFParticle itself carries IsTestBeam
      float beam_score         = NaN;   ///< Pandora TestBeamScore of the chosen PFParticle
      int   beam_track_id      = -1;    ///< Associated pandoraTrack ID, -1 if none
      ///@}

      /// @name Beam track
      ///@{
      SRVector3D beam_start;       ///< Raw (not SCE-corrected) track endpoint with the smaller z [cm]
      SRVector3D beam_end;         ///< Raw track endpoint with the larger z; the fiducial cut acts on its z [cm]
      float      beam_len = NaN;   ///< Track length [cm]
      int        beam_calo_npts = -1;  ///< Collection-plane calorimetry points
      SRVector3D beam_calo_start;  ///< First calorimetry point in z (SCE-corrected) [cm]
      SRVector3D beam_calo_end;    ///< Last calorimetry point in z (SCE-corrected) [cm]
      float      beam_dx_sigma = NaN;  ///< (calo start x - beam-spot mean) / sigma
      float      beam_dy_sigma = NaN;  ///< (calo start y - beam-spot mean) / sigma
      float      beam_dz_sigma = NaN;  ///< (calo start z - beam-spot mean) / sigma
      float      beam_costheta = NaN;  ///< cos of the angle between calo start->end and the mean beam direction
      float      beam_interacting_energy = NaN; ///< Thin-slice interacting kinetic energy from this calorimetry [MeV]
      ///@}

      /// @name Michel window around the chosen end of the beam track
      ///@{
      float      michel_score = NaN;  ///< Sum of CNN Michel scores of the window hits; -1 if the track failed the volume pre-check
      int        michel_nhits = -1;   ///< Hits in the window
      SRVector3D michel_vtx;          ///< Trajectory point of the hit the window is centred on [cm]
      ///@}

      int ndaughters = -1;                       ///< Direct daughters of the beam PFParticle
      std::vector<SRPDSPSelDaughter> daughters;  ///< One entry per direct daughter
  };

  /// Both implementations of the selection, plus the MC truth category they are compared against.
  class SRPDSPSelectionBranch
  {
    public:
      SRPDSPSelection legacy;    ///< Exact port of the old chain, quirks included
      SRPDSPSelection improved;  ///< Same chain with the agreed fixes

      /// @name MC truth (old new_interaction_topology); unfilled in data
      ///@{
      int        true_event_class        = -1;    ///< 1 Abs, 2 Cex, 3 OtherInel, 4 UpstreamInt, 5 Muons, 6 PionPastFV, 7 Other; -1 data or no true beam
      int        true_beam_pdg           = 0;     ///< PDG of the trigger beam particle
      int        true_beam_g4id          = -1;    ///< GEANT4 TrackId of the trigger beam particle
      SRVector3D true_beam_end;                   ///< True end position (not SCE-shifted) [cm]
      bool       true_beam_pip_inelastic = false; ///< End process is "pi+Inelastic"
      int        true_npi0               = -1;    ///< Direct pi0 daughters created by an inelastic process
      int        true_nchpi_above_thr    = -1;    ///< Direct pi+- daughters above the momentum threshold
      ///@}
  };

} // caf

#endif // DUNEANAOBJ_SRPDSPSELECTION_H
