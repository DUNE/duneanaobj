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
    };

    // ==================================================
    // SAND reconstruction container
    // ==================================================
    class SRSAND
    {
    public:
        std::size_t nixn = 0;
        std::vector<SRSANDInt> ixn; ///< Reconstructed interactions

    };

} // namespace caf

#endif // DUNEANAOBJ_SRSAND_H