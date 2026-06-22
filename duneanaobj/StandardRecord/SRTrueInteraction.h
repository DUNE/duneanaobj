////////////////////////////////////////////////////////////////////////
/// \file    SRTrueInteraction.h
/// \brief   True neutrino/cosmic (or other top-level particle) interaction
/// \author  J. Wolcott <jwolcott@fnal.gov>  [but mostly copied from NOvA/SBN sources]

#ifndef DUNEANAOBJ_SRTRUEINTERACTION_H
#define DUNEANAOBJ_SRTRUEINTERACTION_H

#include <limits>

#include "duneanaobj/StandardRecord/SREnums.h"
#include "duneanaobj/StandardRecord/SRTrueParticle.h"
#include "duneanaobj/StandardRecord/SRVector3D.h"

// // This is pretty ugly. The proper fix is to get a new version of castxml that
// // is built with at least clang v9.
// // See https://github.com/CastXML/CastXML/issues/178
// #ifndef __castxml__
// #include <string>
// #else
// namespace std{class string{};}
// #endif

// a less ugly hack, works with castxml v0_4_2 and e20, c7 and e26 but not c14
// not needed for castxml v0_5_1.  Now e20, c7, c14 work but not e26

//#ifdef __GNUC__
//#undef _GLIBCXX_HAVE_BUILTIN_IS_CONSTANT_EVALUATED
//#endif

#include <string>

#include <vector>

namespace caf
{

   class SRDialWeights
   {
   public:
     std::vector<float> weights;
   };

   /// \brief True interaction of probe particle with detector.  Usually neutrinos, but occasionally cosmics etc.
   class SRTrueInteraction
   {
     private:
       // just to keep the typing under control below
       static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

     public:
       /// Interaction ID == 'vertexID' from edep-sim (ND) or GENIE record id (FD).
       /// In the ND case, the packing of the VertexID is described in https://github.com/DUNE/2x2_sim/wiki/Production-changes-and-validation-finding
       long int  id       = -1;
       
       /// Index of interaction in GENIE tree.
       /// Note: for ND, check `id` to determine whether
       /// it's the tree for contained nus (<1e9) or rock/hall nus (>1e9)
       long int  genieIdx = -1;

       int   pdg     = 0;         ///< PDG code of probe particle
       int   pdgorig = 0;         ///< Initial (unoscillated) PDG code of probe neutrino (may be different than `pdg` if this file is a 'swap' file)

       bool           iscc      = false;                          ///< CC (true) or NC/interference (false)
       ScatteringMode mode      = ScatteringMode::kUnknownMode;   ///< Interaction mode
       int            targetPDG = 0;                              ///< PDG code of struck target

       /// PDG code of struck nucleon (or, in the case of MEC, struck nucleon-nucleon pair).
       /// For MEC, the codes are: 2000000200 --> nn,  2000000201 --> np,  2000000202 --> pp
       int   hitnuc   = 0;
       float removalE = NaN;        ///< energy expended to remove nucleon from the nucleus, from GENIE

       float       E         = NaN; ///< True energy [GeV]
       SRVector3D  vtx;             ///< Interaction vertex position in detector coord. [cm]
       SRVector3D  momentum;        ///< Neutrino three-momentum
       bool  isvtxcont = false;     ///< Is true vertex is within detector?  If not, might be a rock particle or cosmic

       float time         = NaN;    ///< True interaction time
       float bjorkenX     = NaN;    ///< Bjorken x = (k-k')^2/(2*p.q) = Q^2/(2*Mnuc*q0) [Dimensionless]
       float inelasticity = NaN;    ///< Inelasticity y = (p.q) / (k.p) = q0 / Enu
       float Q2           = NaN;    ///< Invariant four-momentum transfer from lepton to nuclear system, Q^2 = -(nu - lep)^2
       float q0           = NaN;    ///< Energy transferred from lepton to nuclear system (in lab frame)
       float modq         = NaN;    ///< Magnitude of three-momentum transferred from lepton to nuclear system, |q| (in lab frame)
       float W            = NaN;    ///< Hadronic invariant mass W [GeV^2].  "Experimental W" in GENIE parlance, W^2 = M^2 + 2*Mnuc*q0 +|q|^2
       float t            = NaN;    ///< Kinematic t

       // GENIE truth stuff
       bool  ischarm    = false;    ///< Did neutrino scatter from a charmed quark?
       bool  isseaquark = false;    ///< Did neutrino scatter from a sea quark?
       int   resnum     = 0;        ///< Resonance number, straight from GENIE
       float xsec       = NaN;      ///< xsec for thrown interaction, in 1/GeV^2, straight from GENIE

       float genweight = NaN;       ///< Weight, if any, assigned by the generator

       float baseline             = NaN; ///< Distance from decay to interaction [m]
       SRVector3D prod_vtx;              ///< Neutrino production vertex [cm; beam coordinates]
       SRVector3D parent_dcy_mom;        ///< Neutrino parent momentum at decay [GeV; beam coordinates]
       int        parent_dcy_mode = -1;  ///< Parent hadron/muon decay mode
       int        parent_pdg      = 0;   ///< PDG Code of parent particle ID
       float      parent_dcy_E    = NaN; ///< Neutrino parent energy at decay [GeV]
       float      imp_weight      = NaN; ///< Importance weight from flux file

       Generator                   generator = Generator::kUnknownGenerator;  ///< The generator that created this neutrino interaction
       std::vector<unsigned int>   genVersion;                                ///< Version of the generator that created this neutrino interaction

       // fixme: For unknown reasons, deserializing SRTrueInteractions with this branch sometimes (but not always) causes `free: invalid pointer` segfaults.
       //        For the moment, we just disable it, but we need to track down what's going wrong at some point.
//       std::string                 genConfigString;                           ///< String associated with generator configuration. (For GENIE 3+, this is the "Comprehensive Model Configuration".)

       // shortcuts to avoid iterating through the particle stack for these simple quantities
       int        nproton  = 0;    ///< number of (post-FSI) primary protons
       int        nneutron = 0;    ///< number of (post-FSI) primary neutrons
       int        npip     = 0;    ///< number of (post-FSI) primary pi+
       int        npim     = 0;    ///< number of (post-FSI) primary pi-
       int        npi0     = 0;    ///< number of (post-FSI) primary pi0

       int                         nprim = 0;        ///< Number of primary particles (helps SRProxy)
       std::vector<SRTrueParticle> prim;             ///< Primary p.  The lepton always comes first in this vector.
       int                         nprefsi = 0;      ///< How many primary particles there were prior to FSI (helps SRProxy)
       std::vector<SRTrueParticle> prefsi;           ///< Primary particles prior to FSI.
       int                         nsec = 0;         ///< How many secondaries are in this vector? (helps SRProxy)
       std::vector<SRTrueParticle> sec;              ///< Secondary particles.  Note that not *all* secondaries are kept, only those used in the reco branches

       float                       xsec_cvwgt = NaN; ///<  Central value weight for cross section model

       std::vector<SRDialWeights> syst_dials; ///< Reweights. Outer index = dial, inner index (SRDialWeights) = variation for that dial

   };

} // caf

#endif //DUNEANAOBJ_SRTRUEINTERACTION_H
