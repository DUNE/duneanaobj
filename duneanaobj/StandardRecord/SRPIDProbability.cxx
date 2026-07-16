#include "duneanaobj/StandardRecord/SRPIDProbability.h"

namespace caf
{
  float SRPIDProbability::PIDScore(int pdg) const
  {
      for (const auto& h : hyp) {
          if (h.pdg == pdg) return h.pid_score;
      }
      return NaN;
  }

  float SRPIDProbability::Chi2(int pdg) const
  {
      for (const auto& h : hyp) {
          if (h.pdg == pdg) return h.chi2;
      }
      return NaN;
  }

  const SREnergy& SRPIDProbability::Energy(int pdg) const
  {
      for (const auto& h : hyp) {
          if (h.pdg == pdg) return h.energy;
      }
      // Return a static default SREnergy containing NaN values if not found
      static const SREnergy default_energy;
      return default_energy;
  }
}
