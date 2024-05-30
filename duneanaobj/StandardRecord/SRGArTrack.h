////////////////////////////////////////////////////////////////////////
// \file    SRGArTrack.h
// \brief   Reconstructed GAr track object
// \author  F. Martinez <f.martinezlopez@qmul.ac.uk>
// \date    Jan. 2023
////////////////////////////////////////////////////////////////////////
#ifndef DUNEANAOBJ_SRGARTRACK_H
#define DUNEANAOBJ_SRGARTRACK_H

#include "duneanaobj/StandardRecord/SRTrack.h"

namespace caf
{
  class SRGArTrack: public SRTrack
  {
    public:

      // GAr track characteristics
      float dQdx_fwd = -999.;           ///< dQ/dx of track in forward fit  [ADC/cm]
      float dQdx_bak = -999.;           ///< dQ/dx of track in backward fit [ADC/cm]

      float p_fwd = -999.;              ///< Reco momentum of track in forward fit  [GeV]
      float p_bak = -999.;              ///< Reco momentum of track in backward fit [GeV]

      float chisq_fwd = -999.;          ///< Kalman fit chi square of track in forward fit
      float chisq_bak = -999.;          ///< Kalman fit chi square of track in backward fit

      float len_cm_fwd = -999.;         ///< Length of track in forward fit  [cm]
      float len_cm_bak = -999.;         ///< Length of track in backward fit [cm]

      float dEdx_fwd  = -999.;          ///< Truncated mean dE/dx in forward fit [keV/cm]
      float dEdx_bak  = -999.;          ///< Truncated mean dE/dx in forward fit [keV/cm]

      float dEdx_total = -999.;         ///< Total energy deposited in TPC [GeV]

      int clusters_in_track = -999;     ///< Total number of TPC clusters in track

      int garsoft_trk_id = -999;        ///< GArSoft TrackId for track

      std::vector<int> pid_fwd;         ///< Parametrised PID of track in forward fit
      std::vector<float> pid_prob_fwd;  ///< Parametrised PID probability vector in forward fit
      std::vector<int> pid_bak;         ///< Parametrised PID of track in backward fit
      std::vector<float> pid_prob_bak;  ///< Parametrised PID probability vector in backward fit

  };

}

#if !defined(__GCCXML__) && !defined(__castxml__)
std::ostream & operator<<(std::ostream & stream, const caf::SRGArTrack & tr);
#endif

#endif //DUNEANAOBJ_SRGARTRACK_H
