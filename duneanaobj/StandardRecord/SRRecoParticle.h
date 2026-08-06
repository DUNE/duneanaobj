////////////////////////////////////////////////////////////////////////
/// \file    SRRecoParticle.h
/// \brief   A general reconstructed particle container
/// \author  J. Wolcott <jwolcott@fnal.gov>
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRRECOPARTICLE_H
#define DUNEANAOBJ_SRRECOPARTICLE_H

#include "duneanaobj/StandardRecord/SREnums.h"
#include "duneanaobj/StandardRecord/SRLorentzVector.h"
#include "duneanaobj/StandardRecord/SRVector3D.h"
#include "duneanaobj/StandardRecord/SRPIDProbability.h"

namespace caf
{
  class SRRecoObjBase;

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

      float       score    = NaN;                     ///< PID score for this particle, if relevant

      float       E        = NaN;                     ///< Reconstructed energy for this particle [GeV] **n.b.: total energy including mass** 
      PartEMethod E_method = PartEMethod::kUnknownMethod;   ///< Method used to determine energy for the particle
      SRVector3D  p;                                  ///< Reconstructed momentum for this particle

      SRVector3D  start;                              ///< Reconstructed start point of this particle [cm]
      SRVector3D  end;                                ///< Reconstructed end point of this particle, if that makes sense [cm]

      // todo: would we prefer some kind of "extents" thing so that we can make a decision about containment later?
      //       or should this be the responsibility of the reco module?  (what about stuff that crosses detector boundaries?...)
      bool        contained = false;
      float       walldist = NaN;                     ///< Closest distance to a detector wall [cm]

      RecoObjType origRecoObjType = RecoObjType::kUnknownRecoObj;  ///< Is this a track or a shower?

      int parent = -1;                                ///< Index of parent SRRecoParticle in the same branch, defaults to -1 if no parent
      std::vector<unsigned int> daughters;             ///< Indices of daughters SRRecoParticles in the same branch

      std::vector<TrueParticleID> truth;              ///< Associated SRTrueParticle(s), if relevant (use SRTruthBranch::Particle() with these IDs to grab them)
      std::vector<float>   truthOverlap;              ///< Fractional overlap between this reco particle and true particle

      SRVector3D  start_dir;                          ///< Reconstructed direction vector at start
      SRVector3D  end_dir;                            ///< Reconstructed direction vector at end
      float       length = NaN;                       ///< Reconstructed path length [cm]

      // Measured energy quantities (independent of particle species hypothesis)
      float       depositions = NaN;                  ///< Total raw energy deposition [GeV]
      float       start_dedx = NaN;                   ///< dE/dx near the start of the path [MeV/cm]

      // Energy estimates under the assigned (best) hypothesis
      float       calo_ke = NaN;                      ///< Assigned calorimetric kinetic energy [GeV]
      float       csda_ke = NaN;                      ///< Assigned CSDA range-based kinetic energy [GeV]
      float       mcs_ke = NaN;                       ///< Assigned MCS deflection-based kinetic energy [GeV]

      // Modular structures
      SRPIDProbability pid_prob;                      ///< Detailed PID classification probabilities and hypothesis energy estimates

      SRRecoBaseID     recoobj;                       ///< Id of the reconstructed object this particle is built on
  };

} // caf

#endif //DUNEANAOBJ_SRRECOPARTICLE_H
