#ifndef DUNEANAOBJ_NAVIGATE_H
#define DUNEANAOBJ_NAVIGATE_H

#include <type_traits>

#include "duneanaobj/StandardRecord/SRTruthBranch.h"
#include "duneanaobj/StandardRecord/SRRecoObjBase.h"
#include "duneanaobj/StandardRecord/StandardRecord.h"

namespace caf
{
  // a bit horrible to forward-declare Proxy types...
  // (we would #include Proxy/FwdDeclare.h, but
  //  gen_srproxy has not yet created it
  //  by the time Navigate.h is first seen)
  template <class T> class Proxy;
  class SRTrueParticle;
  using SRTrueParticleProxy = caf::Proxy<caf::SRTrueParticle>;

  /// Convenience method to find a  particle stored by its ID easily.
  /// Intended to be used with 'regular' StandardRecord objects as well as their SRProxy equivalents.
  /// (The horrible return type construction is so that the return type can be deduced automatically
  ///  and thus avoids having to have the user specify a template parameter for it.)
  template <typename TruthBranchType, typename TrueParticleIDType>
  const typename std::conditional<std::is_same_v<TruthBranchType, SRTruthBranch>,
                                  SRTrueParticle, SRTrueParticleProxy>::type *
    FindParticle(const TruthBranchType & truth, const TrueParticleIDType &id);

  class SRTrueInteraction;
  using SRTrueInteractionProxy = caf::Proxy<caf::SRTrueInteraction>;
  template <typename TruthBranchType>
  const typename std::conditional<std::is_same_v<TruthBranchType, SRTruthBranch>, 
                                  SRTrueInteraction, SRTrueInteractionProxy>::type * 
    FindInteraction(const TruthBranchType & truth,  long int id);

  const SRRecoParticle * FindRecoParticle(const StandardRecord & sr, const SRRecoParticleID& id);
  
  const SRRecoObjBase *FindRecoObjBase(const StandardRecord &sr, const SRRecoBaseID &id);
}
#endif //DUNEANAOBJ_NAVIGATE_H
