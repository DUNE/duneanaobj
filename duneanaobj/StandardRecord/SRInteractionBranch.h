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
  };
}

#endif //DUNEANAOBJ_SRNEUTRINOINTERACTIONBRANCH_H
