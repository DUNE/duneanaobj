#ifndef DUNEANAOBJ_SRGLOBAL_H
#define DUNEANAOBJ_SRGLOBAL_H

#include "duneanaobj/StandardRecord/SRWeightGlobal.h"

#include <array>
#include <string>

namespace caf
{
  class SRGlobal
  {
  public:
    SRGlobal();
    ~SRGlobal();

    SRWeightGlobal wgts;
    std::string git_shorthash;
    std::array<int,3> version;
  };

} // end namespace

#endif // DUNEANAOBJ_SRGLOBAL_H
//////////////////////////////////////////////////////////////////////////////
