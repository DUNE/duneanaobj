////////////////////////////////////////////////////////////////////////
/// \file    SRShower.h
/// \brief   Reconstructed shower object
/// \author  J. Wolcott <jwolcott@fnal.gov>
/// \date    Sept. 2021
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRSHOWER_H
#define DUNEANAOBJ_SRSHOWER_H

#include "duneanaobj/StandardRecord/SRVector3D.h"
#include "duneanaobj/StandardRecord/SRTrueParticle.h"

namespace caf
{
  class SRShower
  {
    public:
      // less typing further below
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

      SRVector3D start;      ///< Shower 3D start point [cm]
      SRVector3D direction;  ///< Shower direction (unit vector).

      double time = NaN;     ///< Time of shower formation [ns]
      
      float Evis = -999.;    ///< Visible energy in voxels corresponding to this shower
      
      float qual = NaN;      ///< Reco-specific quality metric (for istance trackScore value) 

      float len_cm   = NaN;  ///< Shower length [cm]. The definition is reco-dependent; consult the documentation of the specific reconstruction algorithm (e.g. Pandora, SPINE) for its exact meaning before use.
      
      float initial_dEdx;    ///< dE/dx value at the shower start
      float conversionGap;   ///< Spatial distance between the photon creation and its conversion into e+e- pair [cm]

      std::vector<TrueParticleID> truth;              ///< Associated SRTrueParticle(s), if relevant (use SRTruthBranch::Particle() with these IDs to grab them)
      std::vector<float>   truthOverlap;              ///< Fractional overlap between this shower and true particle
  };

}

#endif //DUNEANAOBJ_SRSHOWER_H
