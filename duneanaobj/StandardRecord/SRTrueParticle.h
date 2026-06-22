////////////////////////////////////////////////////////////////////////
/// \file    SRTrueParticle.h
/// \brief   True particle coming out of a probe particle's interaction w/ detector
/// \author  J. Wolcott <jwolcott@fnal.gov>  [but mostly copied from NOvA/SBN sources]

#ifndef DUNEANAOBJ_SRTRUEPARTICLE_H
#define DUNEANAOBJ_SRTRUEPARTICLE_H

#include <vector>

#include "duneanaobj/StandardRecord/SREnums.h"
#include "duneanaobj/StandardRecord/SRLorentzVector.h"
#include "duneanaobj/StandardRecord/SRVector3D.h"

namespace caf
{

  /// True particle in the particle record.
  /// (Most particles we store come straight from GENIE (so-called "primaries"),
  ///  but occasionally we want info about other intermediaries as well)
  class SRTrueParticle
  {
    private:
      // just to keep the typing under control below
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      int       pdg             = 0;     ///< Particle
      int       G4ID            = -1;    ///< ID of the particle (taken from GEANT4 -- -1 if this particle is not propogated by G4)

      long int  interaction_id  = -1;    ///< True interaction ID (edep-sim 'vertexID' for ND, or GENIe record number for FD) of the source of this particle
      double     time            = NaN;   ///< Generation time at true interaction vertex [ns]

      TrueParticleID  ancestor_id;      ///< The primary particle this particle descended from, if relevant

      SRLorentzVector p;                ///< Momentum at generation point [GeV/c]
      SRVector3D      start_pos;        ///< Particle generation position [cm]
      SRVector3D      end_pos;          ///< Particle end position (decay, interaction, stop) [cm]

      int parent               = -1;       ///< GEANT4 trackID of parent particle from this particle
      std::vector<unsigned int> daughters; ///< GEANT4 trackIDs of daughter particles from this particle

      TrueParticleID parentID;                   ///< SR index reference to parent particle (ixn + type + part index); unset if primary or not found
      std::vector<TrueParticleID> daughtersID;   ///< SR index references to daughter particles

      /// @name GEANT4 process codes.
      ///   The "process" codes are defined here: https://geant4.kek.jp/Reference/11.1.1/G4ProcessType_8hh_source.html
      ///   The "subprocess" codes depend on the value of the "process" code (see previous).  The most relevant ones are:
      ///   - 'transportation': https://geant4.kek.jp/Reference/11.1.1/G4TransportationProcessType_8hh_source.html
      ///   - 'electromagnetic': https://geant4.kek.jp/Reference/11.1.1/G4EmProcessSubType_8hh_source.html
      ///   - 'hadronic': https://geant4.kek.jp/Reference/11.1.1/G4HadronicProcessType_8hh_source.html
      ///   - 'decay': https://geant4.kek.jp/Reference/11.1.1/G4DecayProcessType_8hh_source.html
      ///   - 'general': these are defined in the same file as 'transportation', above
      ///@{

      /// GEANT4 process code for creation or first step process recorded by GEANT4.
      /// <b>BEWARE</b>:  Sometimes this is the creation process and sometimes it is simply the process undergone
      /// in the particle's first saved trajectory step.
      /// (For example, if edep-sim is your upstream G4 simulation,
      ///   it filters trajectory points to a subset that contain 'interesting' processes,
      ///   see EDepSim::PersistencyManager::SelectTrajectoryPoints().
      ///   If the creation process for your particle wasn't one of those,
      ///   then you'll see here the process for the first trajectory point---which might be something
      ///   confusing like 'ionization'---instead!)
      /// Study the values carefully for particles you are interested in if you want to use it!
      unsigned int  first_process    = 0;
      unsigned int  first_subprocess = 0; ///< GEANT4 subprocess code for this particle's creation or first step (see caveat on first_process).
      unsigned int  end_process      = 0;      ///< G4 process code for the particle's end
      unsigned int  end_subprocess   = 0;   ///< G4 subprocess code for the particle's end
      ///@}
  };

} // caf

#endif //DUNEANAOBJ_SRTRUEPARTICLE_H
