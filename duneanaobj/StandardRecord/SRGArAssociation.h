////////////////////////////////////////////////////////////////////////
// \file    SRGArAssociation.h
// \brief   Associations between GAr reco objects
// \author  F. Martinez <f.martinezlopez@qmul.ac.uk>
// \date    Mar. 2024
////////////////////////////////////////////////////////////////////////
#ifndef DUNEANAOBJ_SRGArASSOCIATION_H
#define DUNEANAOBJ_SRGArASSOCIATION_H

namespace caf
{
  class SRGArAssociation
  {
    public:

      float ECAL_total_energy = -999.;     ///< Total energy deposited in ECAL [GeV]
      int   ECAL_n_hits = 0;               ///< Number of hits in ECAL

      float MuID_total_energy = -999.;     ///< Total energy deposited in MuID [GeV]
      int   MuID_n_hits = 0;               ///< Number of hits in MuID

      float ToF_time = -999.;              ///< Arrival time of particle to ECAL [ns]
      float ToF_beta = -999.;              ///< Velocity measured from arrival time and length

      int charge = 0;                      ///< Inferred charge from track direction

      int garsoft_assn_id= -999;           ///< GArSoft AssociationId for object association

      int garsoft_trk_assn = -999;         ///< associated GArSoft TrackId

      std::vector<int> garsoft_ecal_assns; ///< associated GArSoft ECALIds
      size_t n_garsoft_ecal_assns = 0;     ///< number of associated ECal clusters

      std::vector<int> garsoft_muid_assns; ///< associated GArSoft MuIDIds
      size_t n_garsoft_muid_assns = 0;     ///< number of associated MuID clusters
  };

}

#endif //DUNEANAOBJ_SRGArASSOCIATION_H
