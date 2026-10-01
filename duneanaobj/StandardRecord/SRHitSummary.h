////////////////////////////////////////////////////////////////////////
/// \file    SRHitSummary.h
/// \brief   Hit-level truth composition of a set of reconstructed hits
/// \author  D. Pullia <dariopullia@gmail.com>
///
/// Used both per Pandora slice (caf::SRInteraction::hits) and event-wide
/// (caf::SRInteractionBranch::allhits), so that slicing purity/completeness
/// are simple ratios of the two.
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRHITSUMMARY_H
#define DUNEANAOBJ_SRHITSUMMARY_H

#include <limits>

namespace caf
{
  /// Hit multiplicity and charge attributed to one truth category.
  ///
  /// Integer counts (\ref nhits, \ref nhits_coll) assign each hit wholly to the
  /// category of its *dominant* true contributor, so they sum exactly to the
  /// parent SRHitSummary totals.  The charge quantities instead split each hit
  /// *fractionally* between categories using sim::TrackIDE::energyFrac, which is
  /// the right weighting for energy studies.
  class SRHitCategory
  {
    public:
      // less typing further below
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

      int   nhits           = -1;   ///< Hits (all planes) whose dominant true contributor is this category
      int   nhits_coll      = -1;   ///< As nhits, restricted to the collection plane
      float nhits_frac_coll = NaN;  ///< Charge-fraction-weighted hit count, collection plane (sum of energyFrac)
      float charge_coll     = NaN;  ///< Lifetime-corrected ADC area attributed to this category, collection plane [ADC*tick]
      float E_reco          = NaN;  ///< charge_coll converted to energy [GeV]
  };

  /// Hit-level composition of a set of hits: one Pandora slice, or the whole event.
  ///
  /// The six categories are mutually exclusive and exhaustive, so
  /// beam + beam_daughters + beam_contamination + cosmic + other + unmatched == nhits.
  /// The full beam-induced cascade is beam + beam_daughters.
  class SRHitSummary
  {
    public:
      // less typing further below
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

      int   nhits       = -1;   ///< Total hits in this set, all planes
      int   nhits_coll  = -1;   ///< As nhits, restricted to the collection plane
      float charge_coll = NaN;  ///< Total lifetime-corrected ADC area, collection plane [ADC*tick]
      float E_reco      = NaN;  ///< charge_coll converted to energy [GeV]

      /// False if the slice hits and the hits from HitLabel are different art products.
      /// When false, per-slice counts are not guaranteed to be bounded by the event-wide ones.
      bool  consistent_products = true;

      SRHitCategory beam;               ///< The main (trigger) beam particle only
      SRHitCategory beam_daughters;     ///< All GEANT4 descendants of the main beam particle
      SRHitCategory beam_contamination; ///< Other beam-generator particles (beam halo) and their descendants
      SRHitCategory cosmic;             ///< Cosmic-ray generator
      SRHitCategory other;              ///< Radiologicals and any unrecognised generator
      SRHitCategory unmatched;          ///< No true contributor: noise, or charge below the backtracker's reach
  };

} // caf

#endif //DUNEANAOBJ_SRHITSUMMARY_H
