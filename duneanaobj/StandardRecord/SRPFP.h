////////////////////////////////////////////////////////////////////////
/// \file    SRPFP.h
/// \brief   Reconstructed particle flow particle (PFP) metadata
/// \author  P. Granger <pgranger@fnal.gov>
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRPFP_H
#define DUNEANAOBJ_SRPFP_H

#include <limits>
#include "duneanaobj/StandardRecord/SRVector3D.h"
#include "duneanaobj/StandardRecord/SRRecoObjBase.h"

namespace caf
{
  /// \brief Reconstructed Particle Flow Particle (PFP) in the Far Detector
  class SRPFP : public SRRecoObjBase
  {
    public:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

      // Hit counts per view
      int nhits_U = 0;                    ///< Number of hits in the U wire plane
      int nhits_V = 0;                    ///< Number of hits in the V wire plane
      int nhits_W = 0;                    ///< Number of hits in the W wire plane
      int nhits_3D = 0;                   ///< Number of 3D hits/space points

      // LArPfoHierarchyFeatureTool
      float daughter_parent_hit_ratio = NaN; ///< Ratio of hits in daughters vs. parent
      float ndaughters_hit_3d = NaN;      ///< Number of 3D hits in all daughters

      // LArThreeDChargeFeatureTool
      float charge_end_fraction = NaN;    ///< Fraction of charge deposited near the end of the track
      float charge_fractional_spread = NaN; ///< Fractional spread of the charge

      // LArThreeDLinearFitFeatureTool
      float diff_straight_line_mean = NaN; ///< Mean difference from a straight line fit
      float line_length = NaN;            ///< Length of the reconstructed line fit
      float max_fit_gap_length = NaN;     ///< Maximum gap between hits in the fit
      float sliding_linear_fit_rms = NaN; ///< RMS of the sliding linear fit

      // LArThreeDOpeningAngleFeatureTool
      float angle_diff_3d = NaN;          ///< Opening angle/direction difference in 3D

      // LArThreeDPCAFeatureTool
      float secondary_pca_ratio = NaN;    ///< Ratio of secondary to primary principal component axis
      float tertiary_pca_ratio = NaN;     ///< Ratio of tertiary to primary principal component axis

      // LArThreeDVertexDistanceFeatureTool
      float vertex_distance = NaN;        ///< Distance to the reconstructed vertex

      // Track/Shower BDT score
      float track_score = NaN;            ///< BDT classifier score separating tracks from showers [0 - 1]

      // TPC and drift-specific reco metrics (Moved from generic particle level)
      bool  is_cathode_crosser = false;   ///< Does the particle cross the cathode plane?
      bool  is_time_contained = false;    ///< Is the particle time-contained within the drift window?
      float cathode_offset = NaN;         ///< Distance/offset to the cathode [cm]
  };

} // caf

#endif // DUNEANAOBJ_SRPFP_H
