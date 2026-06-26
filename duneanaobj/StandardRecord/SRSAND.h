////////////////////////////////////////////////////////////////////////
// \file    SRSAND.h
// \brief   SAND reconstruction output 
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
        std::vector<int> ncrossedstations; ///< Number of stations crossed by the track

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
    
        enum class SRIntTarget
        {
            kGraphiteTarget = 0,
            kPlasticTarget  = 1,
            kArgon          = 2,
            kCaloTarget     = 3,
            kInternal       = 4, // passive material inside SAND calo
            kExternal       = 5,
            kOther          = 6
        };

        SRGRAIN grain;      ///< GRAIN reconstruction
        SRTracker tracker;  ///< Tracker reconstruction
        SREcal ecal;        ///< ECAL reconstruction
        SRIntTarget target; ///< Target material of the interaction
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

    };

} // namespace caf

#endif // DUNEANAOBJ_SRSAND_H