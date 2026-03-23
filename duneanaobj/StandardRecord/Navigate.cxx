#include "duneanaobj/StandardRecord/Navigate.ixx"
#include "duneanaobj/StandardRecord/SREnums.h"
#include "duneanaobj/StandardRecord/SRTrueParticle.h"
#include "duneanaobj/StandardRecord/SRTruthBranch.h"


namespace caf
{
  // instantiate the template for "regular" StandardRecord types.
  // for the SRProxy version, see Proxy/Instantiations.cxx.
  template const SRTrueParticle * FindParticle(const SRTruthBranch & truth, const TrueParticleID & id);

  template const SRTrueInteraction * FindInteraction(const SRTruthBranch & truth,  long int id);

  const SRRecoParticle  * FindRecoParticle(const StandardRecord & sr, const SRRecoParticleID& id);

  const SRRecoObjBase * FindRecoObjBase(const StandardRecord & sr, const SRRecoBaseID& id);
}
