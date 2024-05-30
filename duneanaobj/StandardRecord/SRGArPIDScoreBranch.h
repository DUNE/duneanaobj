////////////////////////////////////////////////////////////////////////
/// \file    SRGArPIDScoreBranch.h
/// \brief   Collections of GArSoft PID scores
/// \author  F. Martinez <f.martinezlopez@qmul.ac.uk>

#ifndef DUNEANAOBJ_SRGARPIDSCOREBRANCH_H
#define DUNEANAOBJ_SRGARPIDSCOREBRANCH_H

#include <limits>

namespace caf
{
  class SRGArPIDScoreBranch
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:

      float muon_score        = NaN;      ///< Muon score based on ECAL and MuID activity
      float proton_dEdx_score = NaN;      ///< Proton score based on TPC dE/dx measurement
      float proton_tof_score  = NaN;      ///< Proton score based on ECAL ToF measurement
  };
}

#endif //DUNEANAOBJ_SRGARPIDSCOREBRANCH_H
