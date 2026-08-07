#include "duneanaobj/StandardRecord/SRGlobal.h"

namespace caf
{
  SRGlobal::SRGlobal()
  {
    git_shorthash = DUNEANAOBJ_GIT_SHORTHASH;
    version = {DUNEANAOBJ_VERSION_MAJOR, DUNEANAOBJ_VERSION_MINOR,
               DUNEANAOBJ_VERSION_PATCH};
  }

  SRGlobal::~SRGlobal()
  {
  }
}
