////////////////////////////////////////////////////////////////////////
/// \file    SRPFP.h
/// \brief   Reconstructed pfp object metadata
/// \author  P. Granger <pgranger@fnal.gov>
/// \date    May 2025
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRPFP_H
#define DUNEANAOBJ_SRPFP_H

#include "duneanaobj/StandardRecord/SRVector3D.h"
#include "duneanaobj/StandardRecord/SRTrueParticle.h"

namespace caf
{
  /*
    This is used to store the results of the EMTrkMichelId Score
  */
  struct SRSTEMScore
  {
    SRSTEMScore(){};
    SRSTEMScore(float tscore, float sscore, float escore, float mscore, bool weighted, int plane)
    : track_score(tscore), shower_score(sscore), empty_score(escore), michel_score(mscore),
      charge_weighted(weighted), plane_ID(plane) {};

    float track_score{0};
    float shower_score{0};
    float empty_score{0};
    float michel_score{0};
    bool charge_weighted{false};
    int plane_ID{-1};

    public:
      SRSTEMScore& operator/=(double scalar) {
        track_score /= scalar;
        shower_score /= scalar;
        empty_score /= scalar;
        michel_score /= scalar;
        return *this; // Return a reference to the modified object
      }

      SRSTEMScore operator/(double scalar) {
        track_score /= scalar;
        shower_score /= scalar;
        empty_score /= scalar;
        michel_score /= scalar;
        return SRSTEMScore(track_score, shower_score, empty_score, michel_score, charge_weighted, plane_ID); // Return a reference to the modified object
      }
  };

  class SRPFP
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

      // EM/Track/Michel ID Scores -- see https://doi.org/10.1140/epjc/s10052-022-10791-2
      SRSTEMScore cnn_stem_scores;

      int parent = -1;                                ///< Index of parent SRPFP in the same branch, defaults to -1 if no parent
      std::vector<unsigned int> daughters;             ///< Indices of daughters SRPFP in the same branch

      std::vector<TrueParticleID> truth;              ///< Associated SRTrueParticle(s), if relevant (use SRTruthBranch::Particle() with these IDs to grab them)
      std::vector<float>   truthOverlap;              ///< Fractional overlap between this track and true particle
      
  };

}

#endif //DUNEANAOBJ_SRPFP_H
