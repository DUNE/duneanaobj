#include "duneanaobj/StandardRecord/StandardRecord.h"

#include <limits>

const float kNaN = std::numeric_limits<float>::signaling_NaN();

namespace caf
{
  StandardRecord::StandardRecord() :
    eRec_FromDep(kNaN),
    Ev_reco(kNaN), Ev_reco_nue(kNaN), Ev_reco_numu(kNaN),
    mvaresult(kNaN), mvanue(kNaN), mvanumu(kNaN),
    cvnnue(kNaN), cvnnumu(kNaN), cvnnutau(kNaN), cvnnc(kNaN),
    reco_q(0),
    Elep_reco(kNaN), theta_reco(kNaN),
    RecoLepEnNue(kNaN), RecoHadEnNue(kNaN), RecoLepEnNumu(kNaN), RecoHadEnNumu(kNaN),
    RecoMethodNue(-1), RecoMethodNumu(-1), TrackMomMethodNumu(-1),
    reco_numu(-1), reco_nue(-1), reco_nc(-1),
    muon_contained(-1), muon_tracker(-1), muon_ecal(-1), muon_exit(-1),
    Ehad_veto(kNaN),
    nue_pid(kNaN), numu_pid(kNaN),
    LongestTrackContNumu(-1),
    Ev(kNaN), Elep(kNaN),
    isCC(-1), nuPDG(0), nuPDGunosc(0), LepPDG(0),
    mode(-1), GENIE_ScatteringMode(-1),
    nP(0), nN(0), nipi0(0), nipip(0), nipim(0), niem(0),
    nikp(0), nikm(0), nik0(0), niother(0), nNucleus(0), nUNKNOWN(0),
    Q2(kNaN), W(kNaN), Y(kNaN), X(kNaN),
    vtx_x(kNaN), vtx_y(kNaN), vtx_z(kNaN),
    det_x(kNaN),
    eP(kNaN), eN(kNaN), ePip(kNaN), ePim(kNaN), ePi0(kNaN), eOther(kNaN),
    eRecoP(kNaN), eRecoN(kNaN), eRecoPip(kNaN), eRecoPim(kNaN), eRecoPi0(kNaN), eRecoOther(kNaN),
    eDepP(kNaN), eDepN(kNaN), eDepPip(kNaN), eDepPim(kNaN), eDepPi0(kNaN), eDepOther(kNaN),
    NuMomX(kNaN), NuMomY(kNaN), NuMomZ(kNaN),
    LepMomX(kNaN), LepMomY(kNaN), LepMomZ(kNaN), LepE(kNaN),
    LepNuAngle(kNaN),
    LepEndpoint{kNaN, kNaN, kNaN},
    run(-1), subrun(-1), event(-1),
    isFD(-1), isFHC(-1),
    CVNResultIsAntineutrino(kNaN),
    CVNResultNue(kNaN), CVNResultNumu(kNaN), CVNResultNutau(kNaN), CVNResultNC(kNaN),
    CVNResult0Protons(kNaN), CVNResult1Protons(kNaN), CVNResult2Protons(kNaN), CVNResultNProtons(kNaN),
    CVNResult0Pions(kNaN), CVNResult1Pions(kNaN), CVNResult2Pions(kNaN), CVNResultNPions(kNaN),
    CVNResult0Pizeros(kNaN), CVNResult1Pizeros(kNaN), CVNResult2Pizeros(kNaN), CVNResultNPizeros(kNaN),
    CVNResult0Neutrons(kNaN), CVNResult1Neutrons(kNaN), CVNResult2Neutrons(kNaN), CVNResultNNeutrons(kNaN),
    RegCNNNueE(kNaN),
    sigma_Ev_reco(kNaN), sigma_Elep_reco(kNaN), sigma_numu_pid(kNaN), sigma_nue_pid(kNaN),
    nwgt_CrazyFlux(0), wgt_CrazyFlux(), xsSyst_wgt(),
    total_xsSyst_cv_wgt(kNaN)
  {
  }

  StandardRecord::~StandardRecord()
  {
  }

} // end namespace caf
////////////////////////////////////////////////////////////////////////
