#include "duneanaobj/StandardRecord/StandardRecord.h"

#include "TFile.h"
#include "TTree.h"

using namespace caf;

int main(int argc, char const *argv[]) {

  TFile fout(argv[1], "RECREATE");

  TTree *tout = new TTree("caf", "dummy caf tree");

  StandardRecord *sr = nullptr;

  tout->Branch("StandardRecord", &sr);

  SRParticleTruth NDLArTrack_truth;
  NDLArTrack_truth.trkid = 1;
  NDLArTrack_truth.pdg = 13;
  NDLArTrack_truth.motherpdg = 14;
  NDLArTrack_truth.p = SRLorentzVector(TLorentzVector(1, 2, 3, 4));
  NDLArTrack_truth.motherp = SRLorentzVector(TLorentzVector(0, 0, 5, 5));
  NDLArTrack_truth.start = SRVector3D(0.1, 0.2, 0.3);

  SRTrack NDLArTrack;
  NDLArTrack.start = SRVector3D(1, 2, 3);
  NDLArTrack.end = SRVector3D(4, 5, 6);
  NDLArTrack.dir = SRVector3D(3, 2, 1);
  NDLArTrack.enddir = SRVector3D(6, 5, 4);
  NDLArTrack.Evis = 100;
  NDLArTrack.len_gcm2 = 200;
  NDLArTrack.E = 300;
  NDLArTrack.len_cm = 400;
  NDLArTrack.qual = 500;
  NDLArTrack.truth = NDLArTrack_truth;

  SRParticleTruth NDLArShower_truth;
  NDLArShower_truth.trkid = 4;
  NDLArShower_truth.pdg = 11;
  NDLArShower_truth.motherpdg = 12;
  NDLArShower_truth.p = SRLorentzVector(TLorentzVector(4, 3, 2, 1));
  NDLArShower_truth.motherp = SRLorentzVector(TLorentzVector(0, 0, 6, 6));
  NDLArShower_truth.start = SRVector3D(0.4, 0.5, 0.6);

  SRShower NDLArShower;
  NDLArShower.start = SRVector3D(10, 20, 30);
  NDLArShower.direction = SRVector3D(40, 50, 60);
  NDLArShower.Evis = 10;
  NDLArShower.truth = NDLArShower_truth;

  sr->nd.lar.tracks.push_back(NDLArTrack);
  sr->nd.lar.ntracks = 1;
  sr->nd.lar.showers.push_back(NDLArShower);
  sr->nd.lar.nshowers = 1;

  SRParticleTruth TMSTrack_truth;
  TMSTrack_truth.trkid = 1;
  TMSTrack_truth.pdg = 13;
  TMSTrack_truth.motherpdg = 14;
  TMSTrack_truth.p = SRLorentzVector(TLorentzVector(1, 2, 3, 4));
  TMSTrack_truth.motherp = SRLorentzVector(TLorentzVector(0, 0, 5, 5));
  TMSTrack_truth.start = SRVector3D(0.1, 0.2, 0.3);

  SRTrack TMSTrack;
  TMSTrack.start = SRVector3D(11, 12, 13);
  TMSTrack.end = SRVector3D(14, 15, 16);
  TMSTrack.dir = SRVector3D(-3, -2, -1);
  TMSTrack.enddir = SRVector3D(-6, -5, -4);
  TMSTrack.Evis = 150;
  TMSTrack.len_gcm2 = 250;
  TMSTrack.E = 350;
  TMSTrack.len_cm = 450;
  TMSTrack.qual = 550;
  TMSTrack.truth = TMSTrack_truth;

  sr->nd.tms.tracks.push_back(TMSTrack);
  sr->nd.tms.ntracks = 1;

  sr->nd.ntrkmatch = 1;
  sr->nd.trkmatch.push_back(SRNDTrackAssn{0, 0, 123, 456});

  sr->nd.LArID = 1337;
  sr->nd.TMSID = 7331;
  sr->nd.Residual = 12345;
  sr->nd.cosTheta = 0.12345;

  tout->Fill();

  fout.Write();
  fout.Close();
}