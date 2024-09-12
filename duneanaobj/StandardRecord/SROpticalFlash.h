////////////////////////////////////////////////////////////////////////
/// \file    SROpticalFlash.h
/// \brief   A general optical flash container
/// \author  S. Kumaran <s.kumaran@uci.edu>


#ifndef DUNEANAOBJ_SROPTICALFLASH_H
#define DUNEANAOBJ_SROPTICALFLASH_H


namespace caf
{
  /// \brief optical flash candidate
  class SROpticalFlash
  {
    private:
      // make the uses of it below more readable
      static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();
    
    public:
      int    id            = -1;     ///< id of the flash>
      int    tpc_id        = -1;     ///< id of the TPC>
      double time          = NaN;    ///< time of the flash w.r.t. trigger time in s
      double time_width    = NaN;    ///< width of the flash in s
      float  total_pe      = NaN;    ///< total photoelectrons recorded by all the channels
      
  };

} // caf

#endif //DUNEANAOBJ_SROPTICALFLASH_H
