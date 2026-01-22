////////////////////////////////////////////////////////////////////////
/// \file    SRBeamBranch.h
/// \brief   Beam-related information
/// \author  J. Wolcott <jwolcott@fnal.gov>  [but mostly copied from NOvA/SBN sources]

#ifndef DUNEANAOBJ_SRBEAMBRANCH_H
#define DUNEANAOBJ_SRBEAMBRANCH_H

#include <cmath>
#include <limits>
#include <vector>

namespace caf
{
  class SRBeamBranch
  {
    private:
      // save on typing below
      constexpr static float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
      /// @name beam variables
      /// @brief Quantities used to characterize the spill-by-spill beam quality.
      ///
      /// These variables store measurements from multiple devices placed along the beam line.
      ///
      /// - **POT (Protons on Target):** Measured by the toroids E:TRTGDT, E:TOR101, and E:TR101D.  
      ///   The POT value is given per pulse and includes a normalization factor of 1e12 so that
      ///   users do not need to apply any additional scaling.
      ///
      /// - **Horn Current:** Determined as a linear combination of four strip-line measurements
      ///   (NSLINA, NSLINB, NSLINC, and NSLIND).  
      ///   The calculation follows the method described in  
      ///   <https://cdcvs.fnal.gov/redmine/projects/novaart/repository/svn/entry/trunk/IFDBSpillInfo/IFDBSpillInfo_module.cc#L685>.
      ///
      /// - **Beam Position (Pre-target):** Measured by the monitors “121” and “TGT”, which provide
      ///   the horizontal and vertical position of the beam, as well as its intensity, in the
      ///   pre-target region for each of the six batches.
      ///
      /// - **Beam Position (On target):** Computed as an intensity-weighted average of the
      ///   measurements from the 121 and TGT monitors.
      ///
      /// - **Beam Width (TGT location):** the MTGTDS device contains the readout voltages of
      ///   horizontal and vertical wires (206 values, 48 horizontal + 48 vertical + additional values). 
      ///   The horizontal and vertical spread of the beam is obtained from a gaussian fit of the voltages
      ///   as function of the wire postion
      ///@{
      bool                 ismc;      ///< data or simulated beam pulse?

      bool                 isgoodpulse         = true;      ///< Was the pot for a pulse good? (only applicable to data)
      unsigned long int    pulsetimesec        = 0;         ///< pulse time in seconds [s]
      unsigned long int    pulsetimensec       = 0;         ///< pulse time in nanoseconds [ns]
      unsigned long int    gpspulsetimesec     = 0;         ///< pulse time from GPS [s]
      unsigned long int    gpspulsetimensec    = 0;         ///< pulse time from GPS [ns]
      signed long long int deltapulsetimensec  = -9999999;  ///< Delta time [ns]
      float                pulsepot            = NaN;       ///< POT as measured by the toroid E:TRTGDT device
      float                potTOR101           = NaN;       ///< POT as measured by the toroid E:TOR101 device
      float                potTR101D           = NaN;       ///< POT as measured by the toroid E:TR101D device
      float                hornI               = NaN;       ///< Horn current [kA]
      float                hornDir             = NaN;       ///< Horn polarity [V]
      float                beamHwidth          = NaN;       ///< Beam horizontal width [mm]
      float                beamVwidth          = NaN;       ///< Beam vertical width [mm]
      std::vector<double>  horizontalposTGT;                ///< horizontal beam position as measured by E:HPTGT device (7 values = 6 batches + 1 mean value) [mm]
      std::vector<double>  horizontalintTGT;                ///< horizontal beam intensity as measured by E:HITGT device (7 values = 6 batches + 1 mean value) []
      std::vector<double>  horizontalpos121;                ///< horizontal beam position as measured by E:HP121 device (7 values = 6 batches + 1 mean value) [mm]
      std::vector<double>  verticalposTGT;                  ///< vertical beam position as measured by E:VPTGT device (7 values = 6 batches + 1 mean value) []
      std::vector<double>  verticalintTGT;                  ///< vertical beam intensity as measured by E:VITGT device (7 values = 6 batches + 1 mean value) [mm]
      std::vector<double>  verticalpos121;                  ///< vertical beam position as measured by E:VP121 device (7 values = 6 batches + 1 mean value) [mm]
      std::vector<double>  multiwireInfo;                   ///< horizontal and vertical readout voltages measured by E:MTGTDS device (216 values) [a.u.]

      bool isFHC() const  { return hornI > 0; };                                 ///< Checks #hornI to see if the polarity is positive --> this is FHC
      bool is0HC() const  { return std::abs(hornI) < 1; };                       ///< Checks #hornI to see if the polarity is zero
      bool isRHC() const  { return hornI < 0; }                                  ///< Checks #hornI to see if the polarity is negative --> this is RHC
      ///@}                                                                                 

  };
}

#endif //DUNEANAOBJ_SRBEAMBRANCH_H
