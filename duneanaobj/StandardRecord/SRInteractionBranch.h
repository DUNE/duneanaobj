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
  struct BeamInstrumentation
  {
    BeamInstrumentation(){std::cout << "Default constructor called for BeamInstrumentation" << std::endl;};  
    BeamInstrumentation(double p, bool valid, int trigger, std::vector<double> tof, std::vector<int> pdg_candidates, std::vector<int> tof_chan, double x, double y, double z, double dirX, double dirY, double dirZ, int nFibersP1, int nFibersP2, int nFibersP3, int nTracks, int nMomenta, int C0, int C1, double C0_pressure, double C1_pressure)
    : beam_inst_P(p), beam_inst_valid(valid), beam_inst_trigger(trigger), beam_inst_TOF(tof), beam_inst_PDG_candidates(pdg_candidates), beam_inst_TOF_Chan(tof_chan), beam_inst_X(x), beam_inst_Y(y), beam_inst_Z(z), beam_inst_dirX(dirX), beam_inst_dirY(dirY), beam_inst_dirZ(dirZ), beam_inst_nFibersP1(nFibersP1), beam_inst_nFibersP2(nFibersP2), beam_inst_nFibersP3(nFibersP3), beam_inst_nTracks(nTracks), beam_inst_nMomenta(nMomenta), beam_inst_C0(C0), beam_inst_C1(C1), beam_inst_C0_pressure(C0_pressure), beam_inst_C1_pressure(C1_pressure)
    {std::cout << "Parameterized constructor called for BeamInstrumentation" << std::endl;};

    double beam_inst_P{-1.0};
    bool beam_inst_valid{false};
    int beam_inst_trigger{-1};
    std::vector<double> beam_inst_TOF{};
    std::vector< int > beam_inst_PDG_candidates{}, beam_inst_TOF_Chan{};
    double beam_inst_X{-1.0}, beam_inst_Y{-1.0}, beam_inst_Z{-1.0};
    double beam_inst_dirX{-1.0}, beam_inst_dirY{-1.0}, beam_inst_dirZ{-1.0};
    int beam_inst_nFibersP1{-1}, beam_inst_nFibersP2{-1}, beam_inst_nFibersP3{-1};
    int beam_inst_nTracks{-1}, beam_inst_nMomenta{-1};
    int beam_inst_C0{-1}, beam_inst_C1{-1};
    double beam_inst_C0_pressure{-1.0}, beam_inst_C1_pressure{-1.0};

  };


  class SRInteractionBranch
  {
    public:
      // prepare object to host beam instrumentation information, to be filled by the user if available
      // BeamInstrumentation beamInstrumentation;

      std::vector<SRInteraction> dlp;       ///< Interactions from Deep Learn Physics machine learning reconstruction
      std::size_t ndlp;

      std::vector<SRInteraction> pandora;   ///< Interactions from Pandora reconstruction
      std::size_t npandora;
      int beamPandoraSliceIndex = -1; ///< Index of the slice identified as the beam slice by the reconstruction (if any)

      std::vector<SRInteraction> sandreco;   ///< Interactions from sadreco reconstruction
      std::size_t nsandreco;

      double beam_inst_P{-1.0};
      bool beam_inst_valid{false};
      int beam_inst_trigger{-1};
      std::vector<double> beam_inst_TOF{};
      std::vector< int > beam_inst_PDG_candidates{}, beam_inst_TOF_Chan{};
      double beam_inst_X{-1.0}, beam_inst_Y{-1.0}, beam_inst_Z{-1.0};
      double beam_inst_dirX{-1.0}, beam_inst_dirY{-1.0}, beam_inst_dirZ{-1.0};
      int beam_inst_nFibersP1{-1}, beam_inst_nFibersP2{-1}, beam_inst_nFibersP3{-1};
      int beam_inst_nTracks{-1}, beam_inst_nMomenta{-1};
      int beam_inst_C0{-1}, beam_inst_C1{-1};
      double beam_inst_C0_pressure{-1.0}, beam_inst_C1_pressure{-1.0};

  };
}

#endif //DUNEANAOBJ_SRNEUTRINOINTERACTIONBRANCH_H
