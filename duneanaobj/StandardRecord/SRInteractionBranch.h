////////////////////////////////////////////////////////////////////////
/// \file    SRInteraction.h
/// \brief   Reconstructed (top-level) particle interactions
/// \author  J. Wolcott <jwolcott@fnal.gov>

#ifndef DUNEANAOBJ_SRNEUTRINOINTERACTIONBRANCH_H
#define DUNEANAOBJ_SRNEUTRINOINTERACTIONBRANCH_H

#include <vector>

#include "duneanaobj/StandardRecord/SRInteraction.h"

namespace caf
{
  class SRInteractionBranch
  {
    public:

      std::vector<SRInteraction> dlp;       ///< Interactions from Deep Learn Physics machine learning reconstruction
      std::size_t ndlp;

      std::vector<SRInteraction> pandora;   ///< Interactions from Pandora reconstruction
      std::size_t npandora;

      std::vector<SRInteraction> sandreco;   ///< Interactions from sadreco reconstruction
      std::size_t nsandreco;
      double reco_beam_interactingEnergy = -999.; ///< Reco thin-target interacting energy [MeV] (ProtoDUNE beam track calorimetry)

      /// Hit-level truth composition of *every* hit in the event (the HitLabel collection).
      /// This is the denominator for slice completeness: compare against SRInteraction::hits.
      SRHitSummary allhits;

      /// @name True ionisation energy from SimChannels, collection view, [GeV].
      ///   Independent of hit finding, so these are the ceiling on any hit-based energy estimate.
      ///   NB these are GeV, unlike reco_beam_interactingEnergy above which is MeV.
      ///@{
      float beam_E_true_simch               = -999.;  ///< Main (trigger) beam particle only
      float beam_daughters_E_true_simch     = -999.;  ///< GEANT4 descendants of the main beam particle
      float beam_contamination_E_true_simch = -999.;  ///< Other beam-generator particles and their descendants
      ///@}

      /// @name Slice bookkeeping for slicing-quality studies.
      ///   "beam-tree" below means the main beam particle plus all its GEANT4 descendants.
      ///@{
      int   nslices                    = -1;    ///< Number of recob::Slice in the event
      int   nslices_with_beam_hits     = -1;    ///< Slices containing at least one beam-tree-dominated hit
      int   beam_slice_id              = -1;    ///< recob::Slice key of the slice tagged IsTestBeam (-1 if none)
      int   beam_slice_index           = -1;    ///< Index into `pandora` of that interaction (-1 if none)
      int   best_beam_slice_id         = -1;    ///< recob::Slice key of the slice holding the most beam-tree hits
      float beam_hit_completeness_best = -999.; ///< Beam-tree hits in the best slice / beam-tree hits in the event
      float beam_hit_completeness_beam = -999.; ///< Beam-tree hits in the beam slice / beam-tree hits in the event
      float beam_hit_purity_beam       = -999.; ///< Beam-tree hits in the beam slice / all hits in the beam slice
      ///@}
  };
}

#endif //DUNEANAOBJ_SRNEUTRINOINTERACTIONBRANCH_H
