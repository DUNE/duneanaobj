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
      int beamPandoraSliceIndex = -1; ///< Index of the slice identified as the beam slice by the reconstruction (if any)

      std::vector<SRInteraction> sandreco;   ///< Interactions from sadreco reconstruction
      std::size_t nsandreco;
  };
}

#endif //DUNEANAOBJ_SRNEUTRINOINTERACTIONBRANCH_H
