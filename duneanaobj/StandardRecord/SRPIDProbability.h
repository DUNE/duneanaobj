////////////////////////////////////////////////////////////////////////
/// \file    SRPIDProbability.h
/// \brief   Detailed particle ID and hypothesis testing probabilities
/// \author  Pierre Granger (pgranger@fnal.gov)
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRPIDPROBABILITY_H
#define DUNEANAOBJ_SRPIDPROBABILITY_H

#include <vector>

namespace caf
{
  class SRPIDProbability
  {
    public:
      SRPIDProbability() = default;
      virtual ~SRPIDProbability() = default;

      std::vector<float> pid_scores;       ///< Species probability scores (e.g. e, mu, pi, p, K, gamma)
      std::vector<int>   pid_pdg;          ///< Associated PDG code for each score in pid_scores
      std::vector<float> primary_scores;   ///< Probability scores for primary vs. secondary
      std::vector<float> chi2_per_pid;     ///< Fit chi2 values under different species hypotheses
      std::vector<int>   chi2_pdg;         ///< Associated PDG code for each chi2 value in chi2_per_pid
  };
}

#endif // DUNEANAOBJ_SRPIDPROBABILITY_H
