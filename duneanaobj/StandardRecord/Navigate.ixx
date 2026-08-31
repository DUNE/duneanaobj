#include "duneanaobj/StandardRecord/Navigate.h"
#include "duneanaobj/StandardRecord/SREnums.h"

#include <stdexcept>

namespace caf
{
  template <typename TruthBranchType, typename TrueParticleIDType>
  const typename std::conditional<std::is_same_v<TruthBranchType, SRTruthBranch>, SRTrueParticle, SRTrueParticleProxy>::type *
  FindParticle(const TruthBranchType & truth, const TrueParticleIDType &id)
  {
    if (id.type == TrueParticleID::kUnknown || id.ixn < 0 || id.part < 0)
      return nullptr;

    if (id.type == TrueParticleID::PartType::kPrimary)
      return &truth.nu[id.ixn].prim[id.part];
    else if (id.type == TrueParticleID::PartType::kPrimaryBeforeFSI)
      return &truth.nu[id.ixn].prefsi[id.part];
    else if (id.type == TrueParticleID::PartType::kSecondary)
      return &truth.nu[id.ixn].sec[id.part];
    else
      throw std::domain_error("Unknown PartType: " + std::to_string(id.type));
  }

  template <typename TruthBranchType>
  const typename std::conditional<std::is_same_v<TruthBranchType, SRTruthBranch>, SRTrueInteraction, SRTrueInteractionProxy>::type * 
  FindInteraction(const TruthBranchType & truth,  long int id){
    if (id < 0)
      return nullptr;

    return &truth.nu[id];
  }

  const SRRecoParticle * FindRecoParticle(const StandardRecord & sr, const SRRecoParticleID& id)
  {
    if (!id)
      return nullptr;
    if (id.type == SRRecoParticleID::SRRecoParticleCollectionType::kSPINE)
      return &sr.common.ixn.spine[id.ixn].part.spine[id.ipart];
    else if (id.type == SRRecoParticleID::SRRecoParticleCollectionType::kPandora)
      return &sr.common.ixn.pandora[id.ixn].part.pandora[id.ipart];
    else if (id.type == SRRecoParticleID::SRRecoParticleCollectionType::kPida)
      throw std::domain_error("Not implemented: " + std::to_string(id.type));
    else if (id.type == SRRecoParticleID::SRRecoParticleCollectionType::kSandreco)
      return &sr.common.ixn.sandreco[id.ixn].part.sandreco[id.ipart];
    else
      throw std::domain_error("Unknown SRRecoParticleCollectionType: " + std::to_string(id.type));
  }

  const SRRecoObjBase * FindRecoObjBase(const StandardRecord & sr, const SRRecoBaseID& id)
  {
    if (!id)
      return nullptr;
    if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kFDHDPandoraTrack)
      return &sr.fd.hd.pandora[id.ixn].tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::KFDHDPandoraShower)
      return &sr.fd.hd.pandora[id.ixn].showers[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::KFDHDPandoraPFP)
      return &sr.fd.hd.pandora[id.ixn].pfps[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kFDVDPandoraTrack)
      return &sr.fd.vd.pandora[id.ixn].tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::KFDVDPandoraShower)
      return &sr.fd.vd.pandora[id.ixn].showers[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::KFDVDPandoraPFP)
      return &sr.fd.vd.pandora[id.ixn].pfps[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kFDPDHDPandoraTrack)
      return &sr.fd.pd_hd.pandora[id.ixn].tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::KFDPDHDPandoraShower)
      return &sr.fd.pd_hd.pandora[id.ixn].showers[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::KFDPDHDPandoraPFP)
      return &sr.fd.pd_hd.pandora[id.ixn].pfps[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kFDPDVDPandoraTrack)
      return &sr.fd.pd_vd.pandora[id.ixn].tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::KFDPDVDPandoraShower)
      return &sr.fd.pd_vd.pandora[id.ixn].showers[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::KFDPDVDPandoraPFP)
      return &sr.fd.pd_vd.pandora[id.ixn].pfps[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kNDLArSPINETrack)
      return &sr.nd.lar.spine[id.ixn].tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kNDLArSPINEShower)
      return &sr.nd.lar.spine[id.ixn].showers[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kNDLArPandoraTrack)
      return &sr.nd.lar.pandora[id.ixn].tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kNDLARPandoraShower)
      return &sr.nd.lar.pandora[id.ixn].showers[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kTMSTrack)
      return &sr.nd.tms.ixn[id.ixn].tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kSANDGRAINTrack)
      return &sr.nd.sand.ixn[id.ixn].grain.tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kSANDGRAINShower)
      return &sr.nd.sand.ixn[id.ixn].grain.showers[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kSANDTrackerTrack)
      return &sr.nd.sand.ixn[id.ixn].tracker.tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kSANDTrackerShower)
      return &sr.nd.sand.ixn[id.ixn].tracker.showers[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kSANDECalCluster)
      return &sr.nd.sand.ixn[id.ixn].ecal.clusters[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kGArTrack)
      return &sr.nd.gar.ixn[id.ixn].tracks[id.irecoobj];
    else if (id.type == SRRecoBaseID::SRRecoBaseCollectionType::kGArEcalCluster)
      return &sr.nd.gar.ixn[id.ixn].clusters[id.irecoobj];
    else
      throw std::domain_error("Unknown SRRecoBaseCollectionType: " + std::to_string(id.type));
  }
}
