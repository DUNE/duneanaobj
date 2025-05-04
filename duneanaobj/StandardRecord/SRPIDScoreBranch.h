////////////////////////////////////////////////////////////////////////
/// \file    SRPIDScoreBranch.h
/// \brief   Collections of PID score methods
/// \author  F. Martinez <f.martinezlopez@qmul.ac.uk>

#ifndef DUNEANAOBJ_SRPIDSCOREBRANCH_H
#define DUNEANAOBJ_SRPIDSCOREBRANCH_H

#include "duneanaobj/StandardRecord/SRGArPIDScoreBranch.h"

namespace caf
{

  class SRPIDScoreBranch
  {
    public:
      SRGArPIDScoreBranch gsft_pid;

      // other reconstructions can go here: Pandora, DeepLearnPhysics, etc. once we have stuff to fill for them
  };

} // caf

#endif //DUNEANAOBJ_SRPIDSCOREBRANCH_H
