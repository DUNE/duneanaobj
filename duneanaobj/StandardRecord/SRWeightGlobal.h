#ifndef DUNEANAOBJ_SRWEIGHTGLOBAL_H
#define DUNEANAOBJ_SRWEIGHTGLOBAL_H

#include "duneanaobj/StandardRecord/SRSystParamHeader.h"

#include <vector>

namespace caf
{
  class SRWeightGlobal
  {

  public:
    SRWeightGlobal();
    ~SRWeightGlobal();

    std::vector<SRSystParamHeader> xsec_params;
    std::vector<SRSystParamHeader> flux_params;
  };

} // end namespace

#endif // DUNEANAOBJ_SRWEIGHTGLOBAL_H
//////////////////////////////////////////////////////////////////////////////
