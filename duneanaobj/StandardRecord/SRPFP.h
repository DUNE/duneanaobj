////////////////////////////////////////////////////////////////////////
/// \file    SRPFP.h
/// \brief   Reconstructed pfp object metadata
/// \author  P. Granger <pgranger@fnal.gov>
/// \date    May 2025
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRPFP_H
#define DUNEANAOBJ_SRPFP_H

#include "duneanaobj/StandardRecord/SRVector3D.h"
#include "duneanaobj/StandardRecord/SRRecoObjBase.h"

namespace caf
{
  class SRPFP : public SRRecoObjBase
  {
    public:
      // less typing further below
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

      int nhits_U = 0;
      int nhits_V = 0;
      int nhits_W = 0;
      int nhits_3D = 0;

      //LArPfoHierarchyFeatureTool
      float daughter_parent_hit_ratio = NaN;
      float ndaughters_hit_3d = NaN;

      //LArThreeDChargeFeatureTool
      float charge_end_fraction = NaN;
      float charge_fractional_spread = NaN;

      //LArThreeDLinearFitFeatureTool
      float diff_straight_line_mean = NaN;
      float line_length = NaN;
      float max_fit_gap_length = NaN;
      float sliding_linear_fit_rms = NaN;

      //LArThreeDOpeningAngleFeatureTool
      float angle_diff_3d = NaN;

      //LArThreeDPCAFeatureTool
      float secondary_pca_ratio = NaN;
      float tertiary_pca_ratio = NaN;

      //LArThreeDVertexDistanceFeatureTool
      float vertex_distance = NaN;

      //Track/Shower BDT score
      float track_score = NaN;
  };

}

#endif //DUNEANAOBJ_SRPFP_H
