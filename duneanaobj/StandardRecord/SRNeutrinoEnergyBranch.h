////////////////////////////////////////////////////////////////////////
/// \file    SRNeutrinoEnergyBranch.h
/// \brief   Reconstructed neutrino energies
/// \author  J. Wolcott <jwolcott@fnal.gov>

#ifndef DUNEANAOBJ_SRNEUTRINOENERGYBRANCH_H
#define DUNEANAOBJ_SRNEUTRINOENERGYBRANCH_H

#include <limits>

namespace caf
{

  class SRNeutrinoEnergyBranch
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      float calo        = NaN;  ///< Calorimetric estimate using all hits
      float lep_calo    = NaN;  ///< Lepton (longest track or largest shower) + calorimetric estimate from remaining hits
      float mu_range    = NaN;  ///< Muon (longest track) using the stopping range + calorimetric estimate from the remaining hits
      float mu_mcs      = NaN;  ///< Muon (longest track) using the Multiple Coulomb Scattering (using chi2 fit) + calorimetric estimate from the remaining hits
      float mu_mcs_llhd = NaN;  ///< Muon (longest track) using the Multiple Coulomb Scattering (using LLHD fit) + calorimetric estimate from the remaining hits
      float e_calo      = NaN;  ///< Electron (highest energy shower) + calorimetric estimate from the remaining hits

      float e_had = NaN;  ///< NuE hadronic energy (calorimetric estimate from all non-primary-shower hits)
      float mu_had = NaN;  ///< NuMu hadronic energy (calorimetric estimate from all non-primary-track hits)

      float regcnn   = NaN;  ///< Regression CNN (assumes nue hypothesis)

      //NEW -- GRAIN 
      float part_energy_sum = NaN; ///<Energy estimate using final state particles energy 
  };

} // caf

#endif //DUNEANAOBJ_SRNEUTRINOENERGYBRANCH_H
