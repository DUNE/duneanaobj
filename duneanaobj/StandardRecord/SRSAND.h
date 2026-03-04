////////////////////////////////////////////////////////////////////////
// \file    SRSAND.h
// \brief   SAND reconstruction output compatible with SRProxy and ROOT dictionary
// \author  S. Repetto
// \date    Feb. 2026
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRSAND_H
#define DUNEANAOBJ_SRSAND_H

#include "duneanaobj/StandardRecord/SRTrack.h"
#include "duneanaobj/StandardRecord/SRShower.h"
#include "duneanaobj/StandardRecord/SRECALCluster.h"
#include "duneanaobj/StandardRecord/SREnums.h" 

namespace caf
{

    // ==================================================
    // GRAIN reconstruction
    // ==================================================
    class SRGRAIN
    {
    public:
        std::vector<SRTrack> tracks;
        std::size_t ntracks = 0;

        std::vector<SRShower> showers;
        std::size_t nshowers = 0;
    };

    // ==================================================
    // Tracker reconstruction
    // ==================================================
    class SRTracker
    {
    public:
        std::vector<SRTrack> tracks;
        std::size_t ntracks = 0;

        std::vector<SRShower> showers;
        std::size_t nshowers = 0;
    };

    // ==================================================
    // ECAL reconstruction
    // ==================================================
    class SREcal
    {
    public:
        std::vector<SRECALCluster> clusters;
        std::size_t nclusters = 0;
    };

    // ==================================================
    // A SAND reconstructed neutrino interaction
    // ==================================================
    class SRSANDInt
    {
    public:
        SRGRAIN grain;      ///< GRAIN reconstruction
        SRTracker tracker;  ///< Tracker reconstruction
        SREcal ecal;        ///< ECAL reconstruction

        // Ricostruzioni specifiche per questa interazione
        RecoType grain_reco_type   = kRealReco;
        RecoType tracker_reco_type = kSmearing;
        RecoType ecal_reco_type    = kNone;

        void SetRecoDefaults()
        {
            grain_reco_type   = caf::kRealReco;
            tracker_reco_type = caf::kSmearing;
            ecal_reco_type    = caf::kNone;
        }
    };

    // ==================================================
    // SAND reconstruction container
    // ==================================================
    class SRSAND
    {
    public:
        /// Unique identifier for each interaction
        struct ID
        {
            int ixn = -1;  ///< interaction ID
            int idx = -1;  ///< index in container
        };

        std::size_t nixn = 0;
        std::vector<SRSANDInt> ixn; ///< Reconstructed interactions

        // Reconstruction & interaction info — parte di SAND globale
        SelectionType selection_type     = kGRAINcontained;
        ScatteringMode interaction_type  = kQE;

        void SetDefaults()
        {
            selection_type     = caf::kGRAINcontained;
            interaction_type   = caf::kQE;
        }
    };

} // namespace caf

#endif // DUNEANAOBJ_SRSAND_H