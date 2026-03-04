//
// Created by jeremy on 3/13/23.
//

#ifndef DUNEANAOBJ_SRDETECTORMETABRANCH_H
#define DUNEANAOBJ_SRDETECTORMETABRANCH_H

#include "duneanaobj/StandardRecord/SRMeta.h"

namespace caf
{
  class SRDetectorMetaBranch
  {
    public:
      // Full NDs (Phase I or Phase II)
      SRDetectorMeta nd_lar;   ///< 35-module liquid argon TPC  (forms part of movable PRISM detector concept)
      SRDetectorMeta nd_gar;   ///< high-pressure gaseous argon TPC (forms part of movable PRISM detector concept in Phase II)
      SRDetectorMeta tms;      ///< magnetized spectrometer/calorimeter (forms part of movable PRISM detector concept in Phase I)
      SRDetectorMeta sand;     ///< scintillator tracker and calorimeter, fixed on-axis in beam
      // ND prototypes (more to add?)
      SRDetectorMeta lar2x2;   ///< ND-LAr prototype in NuMI beam  ('lar' prefix b/c you can't start a name with a digit in C++)
      SRDetectorMeta minerva;  ///< tracker & muon veto for 2x2; repurposed former MINERvA detector components

      // full FDs (Phase II modules TBD...)
      SRDetectorMeta fd_hd;    /// Horizontal drift (a.k.a. module 1)
      SRDetectorMeta fd_vd;    /// Vertical drift (a.k.a. module 2)

      // FD prototypes  (add VD ProtoDUNE if/when we CAF it?)
      SRDetectorMeta pd_hd;    /// Horizontal drift prototype

  };
}

#endif //DUNEANAOBJ_SRDETECTORMETABRANCH_H
