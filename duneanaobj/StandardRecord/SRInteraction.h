////////////////////////////////////////////////////////////////////////
/// \file    SRInteraction.h
/// \brief   Reconstructed top-level particle interaction
/// \author  J. Wolcott <jwolcott@fnal.gov>

#ifndef DUNEANAOBJ_SRINTERACTION_H
#define DUNEANAOBJ_SRINTERACTION_H

#include "duneanaobj/StandardRecord/SRDirectionBranch.h"
#include "duneanaobj/StandardRecord/SRNeutrinoEnergyBranch.h"
#include "duneanaobj/StandardRecord/SRNeutrinoHypothesisBranch.h"
#include "duneanaobj/StandardRecord/SRRecoParticlesBranch.h"

namespace caf
{

  /// Top-level particle interaction.  (Usually neutrinos, but cosmics, etc. can live here too)
  class SRInteraction
  {
    public:
      long int id = -1;

      /// Reconstructed vertex location (if any)
      SRVector3D vtx;

      /// Reconstructed time of the interaction (if any)
      float vtx_time = 0;

      /// Hypotheses for this interaction's parent particle direction
      SRDirectionBranch dir;

      /// Hypotheses for this interaction's neutrino identity
      SRNeutrinoHypothesisBranch nuhyp;

      /// Hypotheses for this interaction's neutrino energy
      SRNeutrinoEnergyBranch Enu;

      /// Collections of reconstructed particles
      SRRecoParticlesBranch part;

      std::vector<std::size_t>    truth;              ///< Indices of SRTrueInteraction(s), if relevant (use this index in SRTruthBranch::nu to get them)
      std::vector<float>   truthOverlap;              ///< Fractional overlap between this reco interaction and each true interaction

      bool preselected = false; ///< Was this interaction preselected?  (Useful for workflows where CAFs are preprocessed / filtered in the process of making concatenated files)

      bool contained() const; ///< Convenience function to check if the interaction is contained in the detector by checking the contained flag of all reco particles
  };

} // caf

#endif //DUNEANAOBJ_SRINTERACTION_H
