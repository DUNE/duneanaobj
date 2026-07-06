////////////////////////////////////////////////////////////////////////
/// \file    SRDLPParticle.h
/// \brief   Detailed SPINE/DLP reconstructed particle container
/// \author  Pierre Granger (pgranger@fnal.gov)
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRDLPPARTICLE_H
#define DUNEANAOBJ_SRDLPPARTICLE_H

#include <vector>
#include <limits>
#include "duneanaobj/StandardRecord/SRVector3D.h"
#include "duneanaobj/StandardRecord/SREnums.h"

namespace caf
{

  class SRDLPParticle
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SRDLPParticle();
      virtual ~SRDLPParticle() = default;

      // Base fields
      int64_t id = -1;                                      ///< Particle ID
      int64_t interaction_id = -1;                          ///< Parent interaction ID
      int64_t pdg_code = 0;                                 ///< PDG code of the particle
      DLPPid pid = kDLPUnknown;                             ///< Assigned particle species
      DLPShape shape = kDLPUndefined;                       ///< Semantic shape type
      bool is_primary = false;                              ///< Primary particle score-based flag
      bool is_contained = false;                            ///< Spatial containment
      bool is_valid = false;                                ///< Particle passes thresholds
      bool is_matched = false;                              ///< Particle matches truth
      bool is_truth = false;                                ///< Particle is a truth object
      bool is_cathode_crosser = false;                      ///< Cathode crosser flag
      bool is_time_contained = false;                       ///< Contained within the drift window

      // Energies & Estimators
      float ke = NaN;                                       ///< Best kinetic energy estimate [MeV]
      float calo_ke = NaN;                                  ///< Calorimetric kinetic energy [MeV]
      double csda_ke = NaN;                                 ///< CSDA kinetic energy [MeV]
      double mcs_ke = NaN;                                  ///< MCS kinetic energy [MeV]
      float depositions_sum = NaN;                          ///< Tagged energy deposited [MeV]
      double length = NaN;                                  ///< Trajectory length [cm]
      double mass = NaN;                                    ///< Assigned mass [MeV/c2]
      double start_dedx = NaN;                              ///< dE/dx at start [MeV/cm]

      // Kinematics and Geometry
      float p = NaN;                                        ///< Momentum magnitude [MeV/c]
      SRVector3D momentum;                                  ///< Momentum 3D vector [MeV/c]
      SRVector3D start_point;                               ///< Start point [cm]
      SRVector3D end_point;                                 ///< End point [cm]
      SRVector3D start_dir;                                 ///< Start direction unit vector
      SRVector3D end_dir;                                   ///< End direction unit vector
      float start_straightness = NaN;                       ///< Trajectory straightness metric
      float axial_spread = NaN;                             ///< Axial spread of the particle
      float directional_spread = NaN;                       ///< Directional spread of the particle
      double cathode_offset = NaN;                          ///< Distance from cathode
      float vertex_distance = NaN;                          ///< Distance from vertex

      // Clustered Hit info
      int64_t size = -1;                                    ///< Number of voxels comprising the particle
      int64_t num_fragments = -1;                           ///< Number of fragments comprising the particle

      // Softmax Score Arrays
      std::vector<float> pid_scores;                        ///< Softmax scores for photon, e, mu, pi, p, K
      std::vector<float> primary_scores;                    ///< Softmax scores for secondary, primary
      std::vector<float> chi2_per_pid;                      ///< Chi2 score per PID hypothesis
      std::vector<float> csda_ke_per_pid;                   ///< CSDA kinetic energy per PID hypothesis
      std::vector<float> mcs_ke_per_pid;                    ///< MCS kinetic energy per PID hypothesis

      // Association Buffers
      std::vector<int32_t> fragment_ids;                    ///< Fragment IDs comprising the particle
      std::vector<int32_t> ppn_ids;                         ///< PPN candidate IDs
      std::vector<int64_t> module_ids;                      ///< Module IDs containing the particle
      std::vector<int64_t> match_ids;                       ///< Truth/reco match particle IDs
      std::vector<float> match_overlaps;                    ///< Fractional overlap with matched objects
  };
} // namespace caf

#endif // DUNEANAOBJ_SRDLPPARTICLE_H
