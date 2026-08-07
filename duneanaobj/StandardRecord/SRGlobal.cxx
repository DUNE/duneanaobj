#include "duneanaobj/StandardRecord/SRGlobal.h"

namespace caf
{
  SRGlobal::SRGlobal()
  {
    first_git_shorthash = DUNEANAOBJ_GIT_SHORTHASH;
    first_version = DUNEANAOBJ_VERSION;
    latest_git_shorthash = DUNEANAOBJ_GIT_SHORTHASH;
    latest_version = DUNEANAOBJ_VERSION;
  }

  void SRGlobal::UpdateVersionInformation()
  {
    latest_git_shorthash = DUNEANAOBJ_GIT_SHORTHASH;
    latest_version = DUNEANAOBJ_VERSION;
  }

  SRGlobal::~SRGlobal()
  {
  }
}
