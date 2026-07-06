////////////////////////////////////////////////////////////////////////
/// \file    SREnergyEst.h
/// \brief   Energy estimators (range-based CSDA, deflection-based MCS, calorimetric)
/// \author  Pierre Granger (pgranger@fnal.gov)
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRENERGYEST_H
#define DUNEANAOBJ_SRENERGYEST_H

#include <vector>
#include <limits>

namespace caf
{
  class SREnergyEst
  {
    private:
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      SREnergyEst() = default;
      virtual ~SREnergyEst() = default;

      float calo_ke = NaN;            ///< Calorimetric kinetic energy [GeV]
      float csda_ke = NaN;            ///< CSDA range-based kinetic energy [GeV]
      float mcs_ke = NaN;             ///< MCS deflection-based kinetic energy [GeV]
      float depositions = NaN;        ///< Raw energy deposition sum [GeV]
      float mass = NaN;               ///< Assumed mass for the hypothesis [GeV/c2]
      float start_dedx = NaN;         ///< dE/dx near the start of the path [MeV/cm]

      std::vector<float> csda_ke_per_pid; ///< CSDA kinetic energy per hypothesis [GeV]
      std::vector<float> mcs_ke_per_pid;  ///< MCS kinetic energy per hypothesis [GeV]
  };
}

#endif // DUNEANAOBJ_SRENERGYEST_H
