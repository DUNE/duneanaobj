#include "duneanaobj/StandardRecord/SRNDLAr.h"

namespace caf
{
  template <typename T>
  const T & SRNDLAr::Reco(const SRNDLArID& id)
  {
    static_assert(std::is_same_v<T, SRTrack> || std::is_same_v<T, SRShower>,
                  "Reco() only knows about SRTrack and SRShower!");

    const std::vector<SRNDLArInt> * ints = nullptr;
    if (id.reco == kSPINE)
      ints = &spine;
    else if (id.reco == kPandoraNDLAr)
      ints = &pandora;
    else
      throw std::domain_error("Unknown reco stack: " + std::to_string(id.reco));

    if constexpr(std::is_same_v<T, SRTrack>)
      return (*ints)[id.ixn].tracks[id.idx];
    else if constexpr(std::is_same_v<T, SRShower>)
      return (*ints)[id.ixn].showers[id.idx];
  }

  // explicitly instantiate the template
  template const SRTrack & SRNDLAr::Reco<SRTrack>(const SRNDLArID& id);
  template const SRShower & SRNDLAr::Reco<SRShower>(const SRNDLArID& id);
}
