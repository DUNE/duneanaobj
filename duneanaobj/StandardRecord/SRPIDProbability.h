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
      std::vector<float> primary_scores;   ///< Probability scores for primary vs. secondary
      std::vector<float> chi2_per_pid;     ///< Fit chi2 values under different species hypotheses
  };
}

#endif // DUNEANAOBJ_SRPIDPROBABILITY_H
