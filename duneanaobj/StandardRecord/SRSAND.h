/// \file    SRSAND.h
/// \brief   SAND reconstruction output
/// \author  S. Repetto, S. Lanzi <samuele.lanzi@cnaf.infn.it>
/// \date    Feb. 2026

#ifndef DUNEANAOBJ_SRSAND_H
#define DUNEANAOBJ_SRSAND_H

#include "duneanaobj/StandardRecord/SRTrack.h"
#include "duneanaobj/StandardRecord/SRShower.h"
#include "duneanaobj/StandardRecord/SRECALCluster.h"
#include "duneanaobj/StandardRecord/SRSANDAssn.h"

namespace caf
{
  /// \brief All objects reconstructed by GRAIN in a spill
  class SRGRAIN
  {
    public:
      std::vector<SRTrack> tracks;
      std::size_t          ntracks{};

      std::vector<SRShower> showers;
      std::size_t           nshowers{};
  };

  /// \brief All objects reconstructed by the tracker in a spill
  class SRTracker
  {
    public:
      std::vector<SRTrack> tracks;
      std::size_t          ntracks{};

      std::vector<SRShower> showers;
      std::size_t           nshowers{};
  };

  /// \brief All clusters reconstructed by the ECAL in a spill
  class SREcal
  {
    public:
      std::vector<SRECALCluster> clusters;
      std::size_t                nclusters{};
  };

  /// \brief A SAND reconstructed neutrino interaction, built by matching objects across the subdetectors
  ///
  /// Index-aligned with the SAND reco interactions in the common branch,
  /// so SRRecoBaseID{ixn, kSANDAssn, irecoobj} resolves to SRSAND::ixn[ixn].trkmatch[irecoobj].
  class SRSANDInt
  {
    public:
      std::vector<SRSANDAssn> trkmatch; ///< Cross-subdetector associations; constituents may come from different subdetectors
      std::size_t             ntrkmatch{};
  };

  /// \brief SAND reconstruction output
  ///
  /// GRAIN, tracker and ECAL are reconstructed independently, each into its own list of objects for the whole spill;
  /// a later matching step combines their objects into the SAND interactions in `ixn`.
  class SRSAND
  {
    public:
      SRGRAIN   grain;   ///< All objects reconstructed by GRAIN in this spill
      SRTracker tracker; ///< All objects reconstructed by the tracker in this spill
      SREcal    ecal;    ///< All clusters reconstructed by the ECAL in this spill

      std::vector<SRSANDInt> ixn; ///< SAND interactions from the cross-subdetector matching
      std::size_t            nixn{};
  };

}

#endif //DUNEANAOBJ_SRSAND_H
