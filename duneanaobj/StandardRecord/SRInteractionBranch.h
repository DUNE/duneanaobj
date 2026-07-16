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

      std::vector<SRInteraction> spine;       ///< Interactions from SPINE machine learning reconstruction
      std::size_t nspine;

      std::vector<SRInteraction> pandora;   ///< Interactions from Pandora reconstruction
      std::size_t npandora;

      std::vector<SRInteraction> sandreco;   ///< Interactions from sadreco reconstruction
      std::size_t nsandreco;
  };
}

#endif //DUNEANAOBJ_SRNEUTRINOINTERACTIONBRANCH_H
