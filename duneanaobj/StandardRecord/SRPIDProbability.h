////////////////////////////////////////////////////////////////////////
/// \file    SRPIDProbability.h
/// \brief   Detailed particle ID, hypothesis testing, and energies
/// \author  Pierre Granger (pgranger@fnal.gov)
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRPIDPROBABILITY_H
#define DUNEANAOBJ_SRPIDPROBABILITY_H

#include <vector>
#include <limits>

namespace caf
{
  /// \brief Energy estimators under a specific particle hypothesis
  class SREnergy
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SREnergy() = default;
      virtual ~SREnergy() = default;

      float calo = NaN;                  ///< Calorimetric kinetic energy [GeV]
      float csda = NaN;                  ///< CSDA range-based kinetic energy [GeV]
      float mcs = NaN;                   ///< MCS deflection-based kinetic energy [GeV]
  };

  /// \brief A single particle ID hypothesis (e.g. muon, proton, pion)
  class SRPIDHypothesis
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SRPIDHypothesis() = default;
      virtual ~SRPIDHypothesis() = default;

      int      pdg = 0;                  ///< PDG code for the hypothesis (e.g. 13 for muon)
      float    pid_score = NaN;          ///< Probability score for this species [0 - 1]
      float    chi2 = NaN;               ///< Fit chi2 value under this hypothesis
      SREnergy energy;                   ///< Estimated energy under this hypothesis
  };

  /// \brief Detailed PID classification probabilities and hypothesis-specific energies
  class SRPIDProbability
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SRPIDProbability() = default;
      virtual ~SRPIDProbability() = default;

      std::vector<SRPIDHypothesis>  hyp;              ///< Hypothesis list (PDG, score, chi2, and energy)
      std::vector<float>            primary_scores;   ///< Probability scores for primary vs. secondary (or track-like classifications)

      // Map-like helper methods
      float PIDScore(int pdg) const;
      float Chi2(int pdg) const;
      const SREnergy& Energy(int pdg) const;
  };
}

#endif // DUNEANAOBJ_SRPIDPROBABILITY_H
