/// \author  J. Wolcott <jwolcott@fnal.gov> & S. Lanzi <samuele.lanzi@cnaf.infn.it>
/// \date    Aug. 2026

#ifndef DUNEANAOBJ_SRSANDASSN_H
#define DUNEANAOBJ_SRSANDASSN_H

#include <vector>

#include "duneanaobj/StandardRecord/SREnums.h"
#include "duneanaobj/StandardRecord/SRRecoObjBase.h"
#include "duneanaobj/StandardRecord/SRTrack.h"

namespace caf
{
  /// \brief A group of SAND subdetector reco objects reconstructed to go together
  ///
  /// Lives inside the SRSANDInt whose objects it associates,
  /// so all of its constituents belong to that same SAND reco interaction.
  class SRSANDAssn : public SRRecoObjBase
  {
    public:
      /// \brief The subdetector objects making up this association.
      /// Filled in beginning-to-end order, i.e. following the reconstructed direction.
      std::vector<SRSANDObjID> constituents;

      /// \brief New track object generated from synthesis of the matched constituents.
      ///
      /// Its `start` --> the start point of the first constituent, and its `end` --> the endpoint of the last one.
      /// `len_gcm2` includes range in any dead material between them.
      /// `end` is left at its default (NaN) when the last constituent has no endpoint to derive one from, e.g. an SRECALCluster.
      SRTrack trk;
  };
}

#endif //DUNEANAOBJ_SRSANDASSN_H
