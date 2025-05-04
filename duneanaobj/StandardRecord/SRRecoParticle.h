////////////////////////////////////////////////////////////////////////
/// \file    SRRecoParticle.h
/// \brief   A general reconstructed particle container
/// \author  J. Wolcott <jwolcott@fnal.gov>

#ifndef DUNEANAOBJ_SRRECOPARTICLE_H
#define DUNEANAOBJ_SRRECOPARTICLE_H

#include "duneanaobj/StandardRecord/SREnums.h"
#include "duneanaobj/StandardRecord/SRLorentzVector.h"
#include "duneanaobj/StandardRecord/SRVector3D.h"
#include "duneanaobj/StandardRecord/SRPIDScoreBranch.h"

namespace caf
{
  /// \brief Reconstructed particle candidate
  class SRRecoParticle
  {
    private:
      // make the uses of it below more readable
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      static constexpr int kPdgHadronicBlob = 2000000002;   ///< Special PDG code used for a "hadronic blob" (usu. calorimetrically reconstructed), borrowed from GENIE

      bool        primary  = false;                   ///< Is this reco particle a "primary" one (i.e. emanates directly from the reconstructed vertex)?

      int         pdg      = 0;                       ///< PDG code inferred for this particle.
      int         tgtA     = 0;                       ///< Atomic number of nucleus this particle was reconstructed in (useful for, e.g., SAND)

      SRPIDScoreBranch score;                         ///< PID score(s) for this particle, if relevant

      float       E        = NaN;                     ///< Reconstructed energy for this particle [GeV]
      PartEMethod E_method = PartEMethod::kUnknownMethod;   ///< Method used to determine energy for the particle
      SRVector3D  p;                                  ///< Reconstructed momentum for this particle

      SRVector3D  start;                              ///< Reconstructed start point of this particle [cm]
      SRVector3D  end;                                ///< Reconstructed end point of this particle, if that makes sense [cm]

      // todo: would we prefer some kind of "extents" thing so that we can make a decision about containment later?
      //       or should this be the responsibility of the reco module?  (what about stuff that crosses detector boundaries?...)
      bool        contained = false;

      std::vector<TrueParticleID> truth;              ///< Associated SRTrueParticle(s), if relevant (use SRTruthBranch::Particle() with these IDs to grab them)
      std::vector<float>   truthOverlap;              ///< Fractional overlap between this reco particle and true particle
  };

} // caf

#endif //DUNEANAOBJ_SRRECOPARTICLE_H
