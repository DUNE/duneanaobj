////////////////////////////////////////////////////////////////////////
/// \file    StandardRecord.h
/// \brief   The StandardRecord is the primary top-level object in the Common Analysis File trees.
/// \author  C. Backhouse, C. Marshall, C. Wilkinson, and many others.  Overhauled in early 2023 by J. Wolcott <jwolcott@fnal.gov>
////////////////////////////////////////////////////////////////////////
#ifndef DUNEANAOBJ_STANDARDRECORD_H
#define DUNEANAOBJ_STANDARDRECORD_H

#include "duneanaobj/StandardRecord/SRVector3D.h"

#include "duneanaobj/StandardRecord/SRBeamBranch.h"
#include "duneanaobj/StandardRecord/SRDetectorMetaBranch.h"
#include "duneanaobj/StandardRecord/SRCommonRecoBranch.h"
#include "duneanaobj/StandardRecord/SRFDBranch.h"
#include "duneanaobj/StandardRecord/SRNDBranch.h"
#include "duneanaobj/StandardRecord/SRTruthBranch.h"

/// Common Analysis Files
namespace caf
{
  
  /// \brief   The StandardRecord is the primary top-level object in the 
  ///          Common Analysis File trees.   
  class StandardRecord
  {
    public:

      StandardRecord();
      ~StandardRecord();

      std::string duneanaobj_gitshorthash;
      unsigned short duneanaobj_version[3];

      /// Metadata about the detectors
      SRDetectorMetaBranch meta;

      /// Information about the beam configuration and beam pulse for this event
      SRBeamBranch beam;

      /// Truth information
      SRTruthBranch mc;

      /// Reconstructed info expected to be common to all (?) detectors
      SRCommonRecoBranch common;

      /// Reconstructed info unique to the FDs
      SRFDBranch fd;

      /// Reconstructed info unique to the ND complex
      SRNDBranch nd;

  };
  
} // end namespace

#endif // DUNEANAOBJ_STANDARDRECORD_H
//////////////////////////////////////////////////////////////////////////////
