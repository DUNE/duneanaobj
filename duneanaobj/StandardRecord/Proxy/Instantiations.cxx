// This file is the only way BasicTypesProxy.cxx gets compiled at all (the
// srproxy package doesn't include binaries).
#include "SRProxy/BasicTypesProxy.cxx"

#include "duneanaobj/StandardRecord/Proxy/SRProxy.h"
#include "duneanaobj/StandardRecord/Navigate.ixx"
#include "duneanaobj/StandardRecord/SRTrueParticle.h"

// But this also gives us an opportunity to instantiate the template for
// various DUNE-specific enums that would otherwise be missing symbols,
// as well as other templated functions that depend on SRProxy having
// already been constructed by gen_srproxy.
namespace caf
{
  template class Proxy<Detector>;
  template class Proxy<Generator>;
  template class Proxy<PartEMethod>;
  template class Proxy<ScatteringMode>;

  template class Proxy<NDLAR_RECO_STACK>;
  template class Proxy<FD_RECO_STACK>;
  template class Proxy<NDRecoMatchType>;

  template class Proxy<TrueParticleID::PartType>;
  template class Proxy<RecoObjType>;

  template const SRTrueParticleProxy * FindParticle(const SRTruthBranchProxy & truth, const TrueParticleIDProxy & id);
  template const SRTrueInteractionProxy * FindInteraction(const SRTruthBranchProxy & truth,  long int id);
}
