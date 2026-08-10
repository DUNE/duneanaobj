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
    std::string first_git_shorthash;
    std::string first_version;
    std::string latest_git_shorthash;
    std::string latest_version;

    void UpdateVersionInformation();
  };

} // end namespace

#endif // DUNEANAOBJ_SRGLOBAL_H
//////////////////////////////////////////////////////////////////////////////
