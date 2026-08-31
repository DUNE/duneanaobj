////////////////////////////////////////////////////////////////////////
/// \file    SRNeutrinoHypothesis.h
/// \brief   Collections of reconstructed neutrino candidates
/// \author  J. Wolcott <jwolcott@fnal.gov>

#ifndef DUNEANAOBJ_SRNEUTRINOHYPOTHESISBRANCH_H
#define DUNEANAOBJ_SRNEUTRINOHYPOTHESISBRANCH_H

#include "duneanaobj/StandardRecord/SRCVNScoreBranch.h"

namespace caf
{

  class SRNeutrinoHypothesisBranch
  {
    public:
      SRCVNScoreBranch cvn;

      // other reconstructions can go here: Pandora, SPINE, etc. once we have stuff to fill for them
  };

} // caf

#endif //DUNEANAOBJ_SRNEUTRINOHYPOTHESISBRANCH_H
