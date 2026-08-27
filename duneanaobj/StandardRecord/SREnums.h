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
    kNEUT             = 3,
    kCRY              = 4,
    kNuWro            = 5,
    kMARLEY           = 6,
    kCORSIKA          = 7,
    kGEANT            = 8

  };

  /// Methods for reconstructing particle energies.
  enum PartEMethod
  {
    kUnknownMethod,
    kRange,         ///< Amount of material traversed by particle
    kMCS,           ///< Multiple scattering
    kCalorimetry,   ///< Computed from energy deposited in active volumes, possibly with corrections for invisible energy
    kVisibleEnergy, ///< Computed from the number of photons collected with an appropriate calibration for the conversion 
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

  /// \brief Identifies a reconstructed particle by the interaction it belongs to, 
  /// which collection of reconstructed particles it belongs to, and its index 
  /// within that collection.
  class SRRecoParticleID
  {
    public:
      enum SRRecoParticleCollectionType
      {
        kUnknown,
        kSPINE,
        kPandora,
        kPida,
        kSandreco
      };

    int ixn = -1;                                                               ///< Index of SRInteraction in the SRInteractionBranch
    SRRecoParticleCollectionType type = SRRecoParticleCollectionType::kUnknown; ///< Which of the SRRecoParticle collections in SRRecoParticlesBranch this particle lives in
    int ipart = -1;                                                             ///< Index of SRRecoParticle in the specified SRRecoParticlesBranch collection of the SRInteraction

    inline operator bool() const { return !(type == SRRecoParticleCollectionType::kUnknown || ixn < 0 || ipart < 0); }; ///< Returns true if this is a valid ID (i.e. not default/invalid values)
  };

  /// \brief Identifies a reconstructed object by the interaction it belongs to,
  /// which collection of reconstructed objects it belongs to, and its index
  /// within that collection.
  class SRRecoBaseID
  {
    public:
      /// \brief Which collection of low-level reco objects an object lives in.
      /// NB: these values are serialized into CAFs, so they are written out explicitly.
      /// A new entry takes the next unused number regardless of where it sits in this list:
      /// keep it in the block it belongs to, and never renumber an existing one.
      enum SRRecoBaseCollectionType {
          kUnknown             = 0,
          // FD
          kFDHDPandoraTrack    = 1,
          KFDHDPandoraShower   = 2,
          KFDHDPandoraPFP      = 3,
          kFDVDPandoraTrack    = 4,
          KFDVDPandoraShower   = 5,
          KFDVDPandoraPFP      = 6,
          kFDPDHDPandoraTrack  = 7,
          KFDPDHDPandoraShower = 8,
          KFDPDHDPandoraPFP    = 9,
          kFDPDVDPandoraTrack  = 10,
          KFDPDVDPandoraShower = 11,
          KFDPDVDPandoraPFP    = 12,
          // NDLAr
          kNDLArDLPTrack       = 13,
          kNDLArDLPShower      = 14,
          kNDLArPandoraTrack   = 15,
          kNDLARPandoraShower  = 16,
          // TMS
          kTMSTrack            = 17,
          // SAND
          kSANDGRAINTrack      = 18,
          kSANDGRAINShower     = 19,
          kSANDTrackerTrack    = 20,
          kSANDTrackerShower   = 21,
          kSANDECalCluster     = 22,
          // GAr
          kGArTrack            = 23,
          kGArEcalCluster      = 24
      };

    int      ixn   = -1;                                                 ///< Index of SRInteraction in the SRInteractionBranch
    SRRecoBaseCollectionType type = SRRecoBaseCollectionType::kUnknown;  ///< Which of the low-level reco objects collections this object lives in
    int      irecoobj = -1;                                              ///< Index of SRRecoObjBase in the specified reco objects collection of the SRInteraction 

    inline operator bool() const { return !(type == SRRecoBaseCollectionType::kUnknown || ixn < 0 || irecoobj < 0); }; ///< Returns true if this is a valid ID (i.e. not default/invalid values)
  };

  /// \brief Identifies one of SAND's subdetector reco objects 
  /// by which collection within its SRSANDInt it lives in and its index within that collection.
  /// Used primarily to link them together in SRSANDAssn.
  ///
  /// NB: there is deliberately no interaction index here.
  /// SRSANDAssns live inside the SRSANDInt whose objects they associate,
  /// so a constituent is always in the same interaction as the association that refers to it.
  class SRSANDObjID
  {
    public:
      /// \brief Which collection within an SRSANDInt an object lives in.
      /// Note this names a *collection*, not a subdetector:
      /// GRAIN and the tracker each store both tracks and showers,
      /// so the subdetector alone would not be enough to say which container `idx` indexes into.
      enum SubcollectionType
      {
        kUnknown       = -1,
        kGRAINTrack    = 1,
        kGRAINShower   = 2,
        kTrackerTrack  = 3,
        kTrackerShower = 4,
        kECALCluster   = 5,
      };

      SubcollectionType type = kUnknown;  ///< Which collection within the SRSANDInt this object lives in
      int               idx  = -1;        ///< Index of the object in the collection named by `type`

      inline operator bool() const { return !(type == kUnknown || idx < 0); }; ///< Returns true if this is a valid ID (i.e. not default/invalid values)
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


    enum NDRecoMatchType
  {
    kUndeclared = 0, ///< default value
    kSimple = 1,  ///< match performed using Kate Hildebrandt's "simple" matching algorithm
    kUniqueNoTime = 2,  ///< match performed using Quinton Weyrich's NDLArTMSUniqueMatchRecoFiller.cxx, without time
    kUniqueWithTime = 3 ///< match performed using Quinton Weyrich's NDLArTMSUniqueMatchRecoFiller.cxx, with time
  };
  
  /// \brief What is the type of the reconstructed object?
  /// This is used to help with the association of reconstructed particles
  /// to underlying reconstructed objects.
  enum RecoObjType
  {
    kUnknownRecoObj = -1, ///< default value
    kTrack          = 1,  ///< track
    kShower         = 2,  ///< shower
    kHitCollection  = 3,  ///< hit collection (mostly used to garbage collect all remaining hits)
  };

}


#endif //DUNEANAOBJ_SRENUMS_H
