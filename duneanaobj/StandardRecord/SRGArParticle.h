////////////////////////////////////////////////////////////////////////
// \file    SRGArParticle.h
// \brief   Reconstructed GAr particle object
// \author  F. Martinez <f.martinezlopez@qmul.ac.uk>
// \date    Mar. 2024
////////////////////////////////////////////////////////////////////////
#ifndef DUNEANAOBJ_SRGARPARTICLE_H
#define DUNEANAOBJ_SRGARPARTICLE_H

#include "duneanaobj/StandardRecord/SRVector3D.h"

namespace caf
{
  class SRGArParticle
  {
    public:

      // GAr reco particle characteristics
      SRVector3D  p;                       ///< Reconstructed momentum of particle [GeV]

      float dEdx_total = -999.;            ///< Total energy deposited in TPC [GeV]
      float dEdx_mean  = -999.;            ///< Truncated mean dE/dx of TPC track [keV/cm]

      float ECAL_total_energy = -999.;     ///< Total energy deposited in ECAL [GeV]
      int   ECAL_n_hits = 0;               ///< Number of hits in ECAL
      float MuID_total_energy = -999.;     ///< Total energy deposited in MuID [GeV]
      int   MuID_n_hits = 0;               ///< Number of hits in MuID

      float ToF_time = -999.;              ///< Arrival time of particle to ECAL [ns]
      float ToF_beta = -999.;              ///< Velocity measured from arrival time and length

      int charge = 0;                      ///< Reconstructed charge of particle

      float muon_score        = -1.0;      ///< Muon score based on ECAL and MuID activity
      float proton_dEdx_score = -1.0;      ///< Proton score based on TPC dE/dx measurement
      float proton_tof_score  = -1.0;      ///< Proton score based on ECAL ToF measurement

      int garsoft_trk_assn = -999;         ///< GArSoft TrackId associated to reco particle
      std::vector<int> garsoft_ecal_assns; ///< GArSoft ECALIds associated to reco particle
      std::vector<int> garsoft_muid_assns; ///< GArSoft MuIDIds associated to reco particle
  };

}

#endif //DUNEANAOBJ_SRGARPARTICLE_H
