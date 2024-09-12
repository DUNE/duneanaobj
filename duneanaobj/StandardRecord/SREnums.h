////////////////////////////////////////////////////////////////////////
// \file    SREnums.h
// \brief   Consolidated headers so that they can be included by Proxy
// \author  J. Wolcott <jwolcott@fnal.gov>
// \date    Mar. 2023
////////////////////////////////////////////////////////////////////////

#ifndef DUNEANAOBJ_SRENUMS_H
#define DUNEANAOBJ_SRENUMS_H

#include <cstddef>
#include <limits>

namespace caf
{
  /// Known detectors in CAFs.
  enum Detector : std::size_t
  {
    kUnknownDet = 0,

    // full NDs in Phase I or Phase II
    kND_LAr  = 1,  ///< 35-module liquid argon TPC  (forms part of movable PRISM detector concept)
    kND_TMS  = 2,  ///< magnetized spectrometer/calorimeter (forms part of movable PRISM detector concept in Phase I)
    kND_SAND = 3,  ///< scintillator tracker and calorimeter, fixed on-axis in beam
    kND_GAr  = 4,  ///< high-pressure gaseous argon TPC (forms part of movable PRISM detector concept in Phase II)

    // ND prototypes (more to add?)
    k2x2     = 5,  ///< ND-LAr prototype
    kMINERvA = 6,  ///< tracker & muon veto for 2x2; repurposed former MINERvA detector components

    // leaving some space for expansion ...

    // full FDs (Phase II modules TBD...)
    kFD_HD = 10,   ///< Horizontal drift (a.k.a. module 1)
    kFD_VD = 11,   ///< Vertical drift (a.k.a. module 2)

    // space for modules 3 and 4...

    // FD prototypes  (we don't have any ProtoDUNE-VD data that will be CAFfed?)
    kProtoDUNE = 15,  ///< Horizontal drift prototype

    _kLastDetector = 24  ///< to use in bitset sizing.  make it big enough that we'll never have to expand it ---> future-proof CAFs
  };


  /// Known generators of neutrino interactions (extend as other generators are used)
  enum Generator
  {
    kUnknownGenerator = 0,
    kGENIE            = 1,
    kGIBUU            = 2,
    kNEUT             = 3
  };

  /// Methods for reconstructing particle energies.
  enum PartEMethod
  {
    kUnknownMethod,
    kRange,         ///< Amount of material traversed by particle
    kMCS,           ///< Multiple scattering
    kCalorimetry,   ///< Observed energy deposited in active volume
  };

  /// \brief Neutrino interaction categories.
  /// Periodically synchronized to GENIE (last update: GENIE 3.04.00) to avoid confusion
  /// (but we don't want a GENIE dependency for the StandardRecord so we maintain our own copy here).
  enum ScatteringMode
  {
    kUnknownMode               = -100,
    kQE                        = 1,
    kSingleKaon                = 2,
    kDIS                       = 3,
    kRes                       = 4,
    kCoh                       = 5,
    kDiffractive               = 6,
    kNuElectronElastic         = 7,
    kInvMuonDecay              = 8,
    kAMNuGamma                 = 9,
    kMEC                       = 10,
    kCohElastic                = 11,
    kInverseBetaDecay          = 12,
    kGlashowResonance          = 13,
    kIMDAnnihilation           = 14,
    kPhotonCoh                 = 15,
    kPhotonRes                 = 16,
    kDarkMatterElastic         = 101,
    kDarkMatterDIS             = 102,
    kDarkMatterElectron        = 103,
  };

  // ----------------------------------------------------------------------
  // now some enums that are used internally so one branch can easily refer to another

  class TrueParticleID
  {
    public:
    
      enum PartType { kUnknown, kPrimary, kPrimaryBeforeFSI, kSecondary };

      int      ixn  = -1;       ///< Index of SRInteraction in the SRTruthBranch
      PartType type = kUnknown; ///< Which of the particle collections this particle lives in
      int      part = -1;       ///< Index of SRParticle in the SRInteraction
  };
  
  class FlashMatch
  {
    private:

      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

    public:
    
      int   id            = -1;  ///< id of the matched flash in SROpticalFlash
      float time          = NaN; ///< time of the matched flash
      float total_pe      = NaN; ///< total pe of the matched flash
      float hypothesis_pe = NaN; ///< hypothesis pe from reconstruction for this interaction
  };

  /// Which reconstruction toolkit was used to reconstruct this FD event?
  enum FD_RECO_STACK
  {
    kUnknownFDReco,
    kPandoraFD
  };

  /// Which reconstruction toolkit was used to reconstruct this ND event?
  enum NDLAR_RECO_STACK
  {
    kUnknownNDLArReco,
    kDeepLearnPhys,
    kPandoraNDLAr
  };

}


#endif //DUNEANAOBJ_SRENUMS_H
