
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include "TH1F.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TString.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include <vector>
#include <math.h>
#include <dirent.h>


int numEvent = 0;




// delta phi, [-pi,pi]
double delta_phi(double phi1, double phi2) 
{
  const double PI=2.0*acos(0.);
  const double TWOPI=2.0*PI;
  
  if (phi1<0) phi1= phi1+TWOPI;
  if (phi2<0) phi2= phi2+TWOPI;

  double PHI=fabs(phi1-phi2);

  return (PHI<=PI)? PHI : TWOPI-PHI;
}

// ========================================================

// argument sort
// sort indices according to corresponding array element
template<typename T>
std::vector<size_t> argsort(const std::vector<T> &array) {
  std::vector<size_t> indices(array.size());
  std::iota(indices.begin(), indices.end(), 0);
  std::sort(indices.begin(), indices.end(),
      [&array](int left, int right) -> bool {
          return array[left] < array[right];
      });
  return indices;
}

// =======================================================



int MyAnalysis(string sample)
{

  // Load and read the output files from Pythia
  //===========================================

  // Path to input (reco and truth) root files
  string fileIn = "../pythia-outputs/" + sample;
  string fileOut = "$PWD/root-files/" + sample;

  // Load trees and create chain, add the file and create the tree reader
  TString tree = "ParticleTree";
  TChain *cc_tree = new TChain(tree);
  cc_tree->Add(fileIn.c_str());
  TTreeReader treeReader(cc_tree);


  // init number of entries and percentage processed
  Int_t nentries = Int_t(cc_tree->GetEntries());
  int ientry = 0;
  double percent = 0;


  // Load truth variables

    TTreeReaderArray<double> event_weights(treeReader, "event_weights");

    TTreeReaderValue<int> nNeutrino(treeReader, "nNeutrino");
    TTreeReaderValue<int> nElectronBare(treeReader, "nElectronBare");
    TTreeReaderValue<int> nMuonBare(treeReader, "nMuonBare");
    TTreeReaderValue<int> nLightjetBare(treeReader, "nLightjetBare");
    TTreeReaderValue<int> nBoson(treeReader, "nBoson");
    TTreeReaderValue<double> Met(treeReader, "Met");
    TTreeReaderValue<double> Met_phi(treeReader, "Met_phi");

    TTreeReaderArray<int> neutrino_PdgId(treeReader, "neutrino_PdgId");
    TTreeReaderArray<int> lightjet_bare_nPart(treeReader, "lightjet_bare_nPart");
    TTreeReaderArray<int> boson_ID(treeReader, "boson_ID");

    TTreeReaderArray<float> neutrino_pt(treeReader, "neutrino_pt");
    TTreeReaderArray<float> neutrino_eta(treeReader, "neutrino_eta");
    TTreeReaderArray<float> neutrino_phi(treeReader, "neutrino_phi");
    TTreeReaderArray<float> neutrino_E(treeReader, "neutrino_E");
    TTreeReaderArray<float> electron_bare_pt(treeReader, "electron_bare_pt");
    TTreeReaderArray<float> electron_bare_eta(treeReader, "electron_bare_eta");
    TTreeReaderArray<float> electron_bare_phi(treeReader, "electron_bare_phi");
    TTreeReaderArray<float> electron_bare_E(treeReader, "electron_bare_E");
    TTreeReaderArray<float> electron_bare_charge(treeReader, "electron_bare_charge");
    TTreeReaderArray<float> muon_bare_pt(treeReader, "muon_bare_pt");
    TTreeReaderArray<float> muon_bare_eta(treeReader, "muon_bare_eta");
    TTreeReaderArray<float> muon_bare_phi(treeReader, "muon_bare_phi");
    TTreeReaderArray<float> muon_bare_E(treeReader, "muon_bare_E");
    TTreeReaderArray<float> muon_bare_charge(treeReader, "muon_bare_charge");
    TTreeReaderArray<float> lightjet_bare_pt(treeReader, "lightjet_bare_pt");
    TTreeReaderArray<float> lightjet_bare_eta(treeReader, "lightjet_bare_eta");
    TTreeReaderArray<float> lightjet_bare_phi(treeReader, "lightjet_bare_phi");
    TTreeReaderArray<float> lightjet_bare_E(treeReader, "lightjet_bare_E");
    TTreeReaderArray<float> boson_pt(treeReader, "boson_pt");
    TTreeReaderArray<float> boson_eta(treeReader, "boson_eta");
    TTreeReaderArray<float> boson_phi(treeReader, "boson_phi");
    TTreeReaderArray<float> boson_E(treeReader, "boson_E");

    

  // End truth variables
  

  // Load reco variables

    TTreeReaderValue<int> nMuonReco(treeReader, "nMuonReco");
    TTreeReaderValue<int> nElectronReco(treeReader, "nElectronReco");
    TTreeReaderValue<int> nJetReco(treeReader, "nJetReco");
    TTreeReaderValue<double> RecoMet(treeReader, "RecoMet");
    TTreeReaderValue<double> RecoMet_phi(treeReader, "RecoMet_phi");  

    TTreeReaderArray<float> electron_reco_pt(treeReader, "electron_reco_pt");
    TTreeReaderArray<float> electron_reco_eta(treeReader, "electron_reco_eta");
    TTreeReaderArray<float> electron_reco_phi(treeReader, "electron_reco_phi");
    TTreeReaderArray<float> electron_reco_E(treeReader, "electron_reco_E");
    TTreeReaderArray<float> electron_reco_charge(treeReader, "electron_reco_charge");

    TTreeReaderArray<float> muon_reco_pt(treeReader, "muon_reco_pt");
    TTreeReaderArray<float> muon_reco_eta(treeReader, "muon_reco_eta");
    TTreeReaderArray<float> muon_reco_phi(treeReader, "muon_reco_phi");
    TTreeReaderArray<float> muon_reco_E(treeReader, "muon_reco_E");
    TTreeReaderArray<float> muon_reco_charge(treeReader, "muon_reco_charge");

    TTreeReaderArray<float> jet_reco_pt(treeReader, "jet_reco_pt");
    TTreeReaderArray<float> jet_reco_eta(treeReader, "jet_reco_eta");
    TTreeReaderArray<float> jet_reco_phi(treeReader, "jet_reco_phi");
    TTreeReaderArray<float> jet_reco_E(treeReader, "jet_reco_E");

  // End reco variables



  // Define histograms and tree to be produced in output file
  // ========================================================

  // Define output file
  TFile *output = TFile::Open(fileOut.c_str(), "recreate");
  // Define tree
  TTree *outtree = new TTree("tree", "tree");

  int eventNumber;

  // TRUTH  ONLY
  double truthMET, truthMET_phi;
  int nTruthJet, nTruthEle, nTruthMuon;
  std::vector<float> truthJet_pT, truthJet_eta, truthJet_phi, truthJet_E, truthJet_M, truthJet_pX, truthJet_pY, truthJet_pZ;
  std::vector<float> truthMatchJet_pT, truthMatchJet_eta, truthMatchJet_phi, truthMatchJet_E, truthMatchJet_M, truthMatchJet_pX, truthMatchJet_pY, truthMatchJet_pZ;
  std::vector<float> truthEle_pT, truthEle_eta, truthEle_phi, truthEle_E, truthEle_M, truthEle_pX, truthEle_pY, truthEle_pZ, truthEle_charge;
  std::vector<float> truthMatchEle_pT, truthMatchEle_eta, truthMatchEle_phi, truthMatchEle_E, truthMatchEle_M, truthMatchEle_pX, truthMatchEle_pY, truthMatchEle_pZ, truthMatchEle_charge;
  std::vector<float> truthMuon_pT, truthMuon_eta, truthMuon_phi, truthMuon_E, truthMuon_M, truthMuon_pX, truthMuon_pY, truthMuon_pZ, truthMuon_charge;
  std::vector<float> truthMatchMuon_pT, truthMatchMuon_eta, truthMatchMuon_phi, truthMatchMuon_E, truthMatchMuon_M, truthMatchMuon_pX, truthMatchMuon_pY, truthMatchMuon_pZ, truthMatchMuon_charge;

  // RECO ONLY
  double recoMET, recoMET_phi;
  int nRecoJet, nRecoEle, nRecoMuon;
  std::vector<float> recoJet_pT, recoJet_eta, recoJet_phi, recoJet_E, recoJet_M, recoJet_pX, recoJet_pY, recoJet_pZ;
  std::vector<float> recoMatchJet_pT, recoMatchJet_eta, recoMatchJet_phi, recoMatchJet_E, recoMatchJet_M, recoMatchJet_pX, recoMatchJet_pY, recoMatchJet_pZ;
  std::vector<float> recoEle_pT, recoEle_eta, recoEle_phi, recoEle_E, recoEle_M, recoEle_pX, recoEle_pY, recoEle_pZ, recoEle_charge;
  std::vector<float> recoMatchEle_pT, recoMatchEle_eta, recoMatchEle_phi, recoMatchEle_E, recoMatchEle_M, recoMatchEle_pX, recoMatchEle_pY, recoMatchEle_pZ, recoMatchEle_charge;
  std::vector<float> recoMuon_pT, recoMuon_eta, recoMuon_phi, recoMuon_E, recoMuon_M, recoMuon_pX, recoMuon_pY, recoMuon_pZ, recoMuon_charge;
  std::vector<float> recoMatchMuon_pT, recoMatchMuon_eta, recoMatchMuon_phi, recoMatchMuon_E, recoMatchMuon_M, recoMatchMuon_pX, recoMatchMuon_pY, recoMatchMuon_pZ, recoMatchMuon_charge;

  outtree->Branch("eventNumber", &eventNumber);

  // TRUTH BRANCHES //
  outtree->Branch("truthMET", &truthMET);
  outtree->Branch("truthMET_phi", &truthMET_phi);
  outtree->Branch("nTruthJet", &nTruthJet);
  outtree->Branch("nTruthEle", &nTruthEle);
  outtree->Branch("nTruthMuon", &nTruthMuon);

  outtree->Branch("truthJet_pT", &truthJet_pT);
  outtree->Branch("truthJet_eta", &truthJet_eta);
  outtree->Branch("truthJet_phi", &truthJet_phi);
  outtree->Branch("truthJet_E", &truthJet_E);
  outtree->Branch("truthJet_M", &truthJet_M);
  outtree->Branch("truthJet_pX", &truthJet_pX);
  outtree->Branch("truthJet_pY", &truthJet_pY);
  outtree->Branch("truthJet_pZ", &truthJet_pZ);

  outtree->Branch("truthMatchJet_pT", &truthMatchJet_pT);
  outtree->Branch("truthMatchJet_eta", &truthMatchJet_eta);
  outtree->Branch("truthMatchJet_phi", &truthMatchJet_phi);
  outtree->Branch("truthMatchJet_E", &truthMatchJet_E);
  outtree->Branch("truthMatchJet_M", &truthMatchJet_M);
  outtree->Branch("truthMatchJet_pX", &truthMatchJet_pX);
  outtree->Branch("truthMatchJet_pY", &truthMatchJet_pY);
  outtree->Branch("truthMatchJet_pZ", &truthMatchJet_pZ);

  outtree->Branch("truthEle_pT", &truthEle_pT);
  outtree->Branch("truthEle_eta", &truthEle_eta);
  outtree->Branch("truthEle_phi", &truthEle_phi);
  outtree->Branch("truthEle_E", &truthEle_E);
  outtree->Branch("truthEle_M", &truthEle_M);
  outtree->Branch("truthEle_pX", &truthEle_pX);
  outtree->Branch("truthEle_pY", &truthEle_pY);
  outtree->Branch("truthEle_pZ", &truthEle_pZ);
  outtree->Branch("truthEle_charge", &truthEle_charge);

  outtree->Branch("truthMatchEle_pT", &truthMatchEle_pT);
  outtree->Branch("truthMatchEle_eta", &truthMatchEle_eta);
  outtree->Branch("truthMatchEle_phi", &truthMatchEle_phi);
  outtree->Branch("truthMatchEle_E", &truthMatchEle_E);
  outtree->Branch("truthMatchEle_M", &truthMatchEle_M);
  outtree->Branch("truthMatchEle_pX", &truthMatchEle_pX);
  outtree->Branch("truthMatchEle_pY", &truthMatchEle_pY);
  outtree->Branch("truthMatchEle_pZ", &truthMatchEle_pZ);
  outtree->Branch("truthMatchEle_charge", &truthMatchEle_charge);

  outtree->Branch("truthMuon_pT", &truthMuon_pT);
  outtree->Branch("truthMuon_eta", &truthMuon_eta);
  outtree->Branch("truthMuon_phi", &truthMuon_phi);
  outtree->Branch("truthMuon_E", &truthMuon_E);
  outtree->Branch("truthMuon_M", &truthMuon_M);
  outtree->Branch("truthMuon_pX", &truthMuon_pX);
  outtree->Branch("truthMuon_pY", &truthMuon_pY);
  outtree->Branch("truthMuon_pZ", &truthMuon_pZ);
  outtree->Branch("truthMuon_charge", &truthMuon_charge);

  outtree->Branch("truthMatchMuon_pT", &truthMatchMuon_pT);
  outtree->Branch("truthMatchMuon_eta", &truthMatchMuon_eta);
  outtree->Branch("truthMatchMuon_phi", &truthMatchMuon_phi);
  outtree->Branch("truthMatchMuon_E", &truthMatchMuon_E);
  outtree->Branch("truthMatchMuon_M", &truthMatchMuon_M);
  outtree->Branch("truthMatchMuon_pX", &truthMatchMuon_pX);
  outtree->Branch("truthMatchMuon_pY", &truthMatchMuon_pY);
  outtree->Branch("truthMatchMuon_pZ", &truthMatchMuon_pZ);
  outtree->Branch("truthMatchMuon_charge", &truthMatchMuon_charge);

  // RECO BRANCHES //
  outtree->Branch("recoMET", &recoMET);
  outtree->Branch("recoMET_phi", &recoMET_phi);
  outtree->Branch("nRecoJet", &nRecoJet);
  outtree->Branch("nRecoEle", &nRecoEle);
  outtree->Branch("nRecoMuon", &nRecoMuon);

  outtree->Branch("recoJet_pT", &recoJet_pT);
  outtree->Branch("recoJet_eta", &recoJet_eta);
  outtree->Branch("recoJet_phi", &recoJet_phi);
  outtree->Branch("recoJet_E", &recoJet_E);
  outtree->Branch("recoJet_M", &recoJet_M);
  outtree->Branch("recoJet_pX", &recoJet_pX);
  outtree->Branch("recoJet_pY", &recoJet_pY);
  outtree->Branch("recoJet_pZ", &recoJet_pZ);

  outtree->Branch("recoMatchJet_pT", &recoMatchJet_pT);
  outtree->Branch("recoMatchJet_eta", &recoMatchJet_eta);
  outtree->Branch("recoMatchJet_phi", &recoMatchJet_phi);
  outtree->Branch("recoMatchJet_E", &recoMatchJet_E);
  outtree->Branch("recoMatchJet_M", &recoMatchJet_M);
  outtree->Branch("recoMatchJet_pX", &recoMatchJet_pX);
  outtree->Branch("recoMatchJet_pY", &recoMatchJet_pY);
  outtree->Branch("recoMatchJet_pZ", &recoMatchJet_pZ);

  outtree->Branch("recoEle_pT", &recoEle_pT);
  outtree->Branch("recoEle_eta", &recoEle_eta);
  outtree->Branch("recoEle_phi", &recoEle_phi);
  outtree->Branch("recoEle_E", &recoEle_E);
  outtree->Branch("recoEle_M", &recoEle_M);
  outtree->Branch("recoEle_pX", &recoEle_pX);
  outtree->Branch("recoEle_pY", &recoEle_pY);
  outtree->Branch("recoEle_pZ", &recoEle_pZ);
  outtree->Branch("recoEle_charge", &recoEle_charge);

  outtree->Branch("recoMatchEle_pT", &recoMatchEle_pT);
  outtree->Branch("recoMatchEle_eta", &recoMatchEle_eta);
  outtree->Branch("recoMatchEle_phi", &recoMatchEle_phi);
  outtree->Branch("recoMatchEle_E", &recoMatchEle_E);
  outtree->Branch("recoMatchEle_M", &recoMatchEle_M);
  outtree->Branch("recoMatchEle_pX", &recoMatchEle_pX);
  outtree->Branch("recoMatchEle_pY", &recoMatchEle_pY);
  outtree->Branch("recoMatchEle_pZ", &recoMatchEle_pZ);
  outtree->Branch("recoMatchEle_charge", &recoMatchEle_charge);

  outtree->Branch("recoMuon_pT", &recoMuon_pT);
  outtree->Branch("recoMuon_eta", &recoMuon_eta);
  outtree->Branch("recoMuon_phi", &recoMuon_phi);
  outtree->Branch("recoMuon_E", &recoMuon_E);
  outtree->Branch("recoMuon_M", &recoMuon_M);
  outtree->Branch("recoMuon_pX", &recoMuon_pX);
  outtree->Branch("recoMuon_pY", &recoMuon_pY);
  outtree->Branch("recoMuon_pZ", &recoMuon_pZ);
  outtree->Branch("recoMuon_charge", &recoMuon_charge);

  outtree->Branch("recoMatchMuon_pT", &recoMatchMuon_pT);
  outtree->Branch("recoMatchMuon_eta", &recoMatchMuon_eta);
  outtree->Branch("recoMatchMuon_phi", &recoMatchMuon_phi);
  outtree->Branch("recoMatchMuon_E", &recoMatchMuon_E);
  outtree->Branch("recoMatchMuon_M", &recoMatchMuon_M);
  outtree->Branch("recoMatchMuon_pX", &recoMatchMuon_pX);
  outtree->Branch("recoMatchMuon_pY", &recoMatchMuon_pY);
  outtree->Branch("recoMatchMuon_pZ", &recoMatchMuon_pZ);
  outtree->Branch("recoMatchMuon_charge", &recoMatchMuon_charge);




  // Control parameter
  bool dosystematics = false;
  int systnum = 0;


  // Loop over the events to run analysis on the ntuple
  // ==================================================

  while(treeReader.Next())
  {

    numEvent++;

    // print percentage processed
    ientry++;
    if ((20 * ientry) / nentries >= percent)
    {
      cout << "Processed: " << percent * 5 << "%" << endl;
      percent = (20 * ientry) / nentries + 1;
    }

    // Reweight the event if needed
    double wgt = 1.0;


    // Fill containers with truth and reco objects
    // -------------------------------------------

    vector<TLorentzVector> ElectronTrueContainer;
    vector<TLorentzVector> ElectronRecoContainer;
    for (int itele = 0; itele<electron_bare_pt.GetSize(); itele++)
    {
      TLorentzVector temptrueele;
      temptrueele.SetPtEtaPhiE(electron_bare_pt[itele], electron_bare_eta[itele], electron_bare_phi[itele], electron_bare_E[itele]);
      ElectronTrueContainer.push_back(temptrueele);
    }
    for (int irele = 0; irele<electron_reco_pt.GetSize(); irele++)
    {
      TLorentzVector temprecoele;
      temprecoele.SetPtEtaPhiE(electron_reco_pt[irele], electron_reco_eta[irele], electron_reco_phi[irele], electron_reco_E[irele]);
      ElectronRecoContainer.push_back(temprecoele);
    }



    vector<TLorentzVector> MuonTrueContainer;
    vector<TLorentzVector> MuonRecoContainer;
    for (int itmuon = 0; itmuon<muon_bare_pt.GetSize(); itmuon++)
    {
      TLorentzVector temptruemuon;
      temptruemuon.SetPtEtaPhiE(muon_bare_pt[itmuon], muon_bare_eta[itmuon], muon_bare_phi[itmuon], muon_bare_E[itmuon]);
      MuonTrueContainer.push_back(temptruemuon);
    }
    for (int irmuon = 0; irmuon<muon_reco_pt.GetSize(); irmuon++)
    {
      TLorentzVector temprecomuon;
      temprecomuon.SetPtEtaPhiE(muon_reco_pt[irmuon], muon_reco_eta[irmuon], muon_reco_phi[irmuon], muon_reco_E[irmuon]);
      MuonRecoContainer.push_back(temprecomuon);
    }



    vector<TLorentzVector> JetTrueContainer;
    vector<TLorentzVector> JetRecoContainer;
    for (int itjet = 0; itjet<lightjet_bare_pt.GetSize(); itjet++)
    {
      TLorentzVector temptruejet;
      temptruejet.SetPtEtaPhiE(lightjet_bare_pt[itjet], lightjet_bare_eta[itjet], lightjet_bare_phi[itjet], lightjet_bare_E[itjet]);
      JetTrueContainer.push_back(temptruejet);
    }
    for (int irjet = 0; irjet<jet_reco_pt.GetSize(); irjet++)
    {
      TLorentzVector temprecojet;
      temprecojet.SetPtEtaPhiE(jet_reco_pt[irjet], jet_reco_eta[irjet], jet_reco_phi[irjet], jet_reco_E[irjet]);
      JetRecoContainer.push_back(temprecojet);
    }

    eventNumber = numEvent;

    // Copy truth values to output tree
    nTruthEle = *nElectronBare;
    nTruthMuon = *nMuonBare;
    nTruthJet = *nLightjetBare;
    truthMET = *Met;
    truthMET_phi = *Met_phi;

    // Copy reco values to output tree
    nRecoEle = *nElectronReco;
    nRecoMuon = *nMuonReco;
    nRecoJet = *nJetReco;
    recoMET = *RecoMet;
    recoMET_phi = *RecoMet_phi;





    // ****************
    //    Fill trees 
    // ****************

    // jets
    for (int iJet = 0; iJet < JetTrueContainer.size(); iJet++)
    {
      truthJet_pT.push_back(JetTrueContainer[iJet].Pt());
      truthJet_eta.push_back(JetTrueContainer[iJet].Eta());
      truthJet_phi.push_back(JetTrueContainer[iJet].Phi());
      truthJet_E.push_back(JetTrueContainer[iJet].E());
      truthJet_M.push_back(JetTrueContainer[iJet].M());
      truthJet_pX.push_back(JetTrueContainer[iJet].Px());
      truthJet_pY.push_back(JetTrueContainer[iJet].Py());
      truthJet_pZ.push_back(JetTrueContainer[iJet].Pz());
    }
    for (int iJet = 0; iJet < JetRecoContainer.size(); iJet++)
    {
      recoJet_pT.push_back(JetRecoContainer[iJet].Pt());
      recoJet_eta.push_back(JetRecoContainer[iJet].Eta());
      recoJet_phi.push_back(JetRecoContainer[iJet].Phi());
      recoJet_E.push_back(JetRecoContainer[iJet].E());
      recoJet_M.push_back(JetRecoContainer[iJet].M());
      recoJet_pX.push_back(JetRecoContainer[iJet].Px());
      recoJet_pY.push_back(JetRecoContainer[iJet].Py());
      recoJet_pZ.push_back(JetRecoContainer[iJet].Pz());
    }
    // electrons
    for (int iEle = 0; iEle < ElectronTrueContainer.size(); iEle++)
    {
      truthEle_pT.push_back(ElectronTrueContainer[iEle].Pt());
      truthEle_eta.push_back(ElectronTrueContainer[iEle].Eta());
      truthEle_phi.push_back(ElectronTrueContainer[iEle].Phi());
      truthEle_E.push_back(ElectronTrueContainer[iEle].E());
      truthEle_M.push_back(ElectronTrueContainer[iEle].M());
      truthEle_pX.push_back(ElectronTrueContainer[iEle].Px());
      truthEle_pY.push_back(ElectronTrueContainer[iEle].Py());
      truthEle_pZ.push_back(ElectronTrueContainer[iEle].Pz());
      truthEle_charge.push_back(electron_bare_charge[iEle]);
    }
    for (int iEle = 0; iEle < ElectronRecoContainer.size(); iEle++)
    {
      recoEle_pT.push_back(ElectronRecoContainer[iEle].Pt());
      recoEle_eta.push_back(ElectronRecoContainer[iEle].Eta());
      recoEle_phi.push_back(ElectronRecoContainer[iEle].Phi());
      recoEle_E.push_back(ElectronRecoContainer[iEle].E());
      recoEle_M.push_back(ElectronRecoContainer[iEle].M());
      recoEle_pX.push_back(ElectronRecoContainer[iEle].Px());
      recoEle_pY.push_back(ElectronRecoContainer[iEle].Py());
      recoEle_pZ.push_back(ElectronRecoContainer[iEle].Pz());
      recoEle_charge.push_back(electron_reco_charge[iEle]);
    }
    // muons
    for (int iMuon = 0; iMuon < MuonTrueContainer.size(); iMuon++)
    {
      truthMuon_pT.push_back(MuonTrueContainer[iMuon].Pt());
      truthMuon_eta.push_back(MuonTrueContainer[iMuon].Eta());
      truthMuon_phi.push_back(MuonTrueContainer[iMuon].Phi());
      truthMuon_E.push_back(MuonTrueContainer[iMuon].E());
      truthMuon_M.push_back(MuonTrueContainer[iMuon].M());
      truthMuon_pX.push_back(MuonTrueContainer[iMuon].Px());
      truthMuon_pY.push_back(MuonTrueContainer[iMuon].Py());
      truthMuon_pZ.push_back(MuonTrueContainer[iMuon].Pz());
      truthMuon_charge.push_back(muon_bare_charge[iMuon]);
    }
    for (int iMuon = 0; iMuon < MuonRecoContainer.size(); iMuon++)
    {
      recoMuon_pT.push_back(MuonRecoContainer[iMuon].Pt());
      recoMuon_eta.push_back(MuonRecoContainer[iMuon].Eta());
      recoMuon_phi.push_back(MuonRecoContainer[iMuon].Phi());
      recoMuon_E.push_back(MuonRecoContainer[iMuon].E());
      recoMuon_M.push_back(MuonRecoContainer[iMuon].M());
      recoMuon_pX.push_back(MuonRecoContainer[iMuon].Px());
      recoMuon_pY.push_back(MuonRecoContainer[iMuon].Py());
      recoMuon_pZ.push_back(MuonRecoContainer[iMuon].Pz());
      recoMuon_charge.push_back(muon_reco_charge[iMuon]);
    }


    // *******************
    //   OBJECT MATCHING
    // *******************
    
    //// make containers for matched objects
    vector<TLorentzVector> JetTrueContainerMatch;
    vector<TLorentzVector> JetRecoContainerMatch;
    vector<TLorentzVector> ElectronTrueContainerMatch;
    vector<TLorentzVector> ElectronRecoContainerMatch;
    vector<TLorentzVector> MuonTrueContainerMatch;
    vector<TLorentzVector> MuonRecoContainerMatch;

    // run in a loop to match each type of object
    // (there's probably a better way to do this but this is fine for now)
    for (int iMatch = 0; iMatch < 3; iMatch++){
      vector<TLorentzVector> TrueContainer;
      vector<TLorentzVector> RecoContainer;

      if (iMatch == 0){
        TrueContainer = JetTrueContainer;
        RecoContainer = JetRecoContainer;
      }
      else if (iMatch == 1){
        TrueContainer = ElectronTrueContainer;
        RecoContainer = ElectronRecoContainer;
      }
      else if (iMatch == 2){
        TrueContainer = MuonTrueContainer;
        RecoContainer = MuonRecoContainer;
      }


      float maxDeltaR = 0.4;

      // vector to store the deltaR between reco and true s
      std::vector<float> deltaR;

      // loop through s and save the deltaR of each w.r.t. reco 
      for (int ir = 0; ir<RecoContainer.size(); ir++)
      {            
        for (int it = 0; it<TrueContainer.size(); it++)
        {
          double dRap = abs(RecoContainer[ir].Rapidity() - TrueContainer[it].Rapidity());
          double dPhi = delta_phi(RecoContainer[ir].Phi(), TrueContainer[it].Phi());
          double dR_value = sqrt((dRap*dRap) + (dPhi*dPhi));
          deltaR.push_back(dR_value);
        }    
      }

      // make vectors to store the indeces of the match s
      // used to check if the object has already been match
      std::set<int> matchreco;
      std::set<int> matchtrue;
      
      // sort the match_quality vector and find the smallest deltaR
      // arg sort gives the indeces of the sorted vector
      auto indeces = argsort(deltaR);
      for (auto i:indeces){
        // find the indeces of the matched objects
        auto rec = i/TrueContainer.size();
        auto tru = i%TrueContainer.size();

        // check that deltaR is less than max
        // and that deltaR is not a null value
        if (deltaR[i] > maxDeltaR) break;
        if (deltaR[i] != deltaR[i]) continue;

        // if the rec or true object have already been match, go to the next
        if (matchreco.find(rec) != matchreco.end()) continue;
        if (matchtrue.find(tru) != matchtrue.end()) continue;
        
        // construct  objects
        TLorentzVector tempreco;
        TLorentzVector temptrue;
        tempreco = RecoContainer[rec];
        temptrue = TrueContainer[tru];

        // add the index of the matched object to the set (so it can't get used again)
        matchreco.insert(rec);
        matchtrue.insert(tru);

        if (iMatch == 0){
          JetRecoContainerMatch.push_back(tempreco);
          JetTrueContainerMatch.push_back(temptrue);
        }
        else if (iMatch == 1){
          ElectronRecoContainerMatch.push_back(tempreco);
          ElectronTrueContainerMatch.push_back(temptrue);
        }
        else if (iMatch == 2){
          MuonRecoContainerMatch.push_back(tempreco);
          MuonTrueContainerMatch.push_back(temptrue);
        }
      }
    }

    // Fill matched objects
    // jets
    for (int iJet = 0; iJet < JetTrueContainerMatch.size(); iJet++)
    {
      truthMatchJet_pT.push_back(JetTrueContainerMatch[iJet].Pt());
      truthMatchJet_eta.push_back(JetTrueContainerMatch[iJet].Eta());
      truthMatchJet_phi.push_back(JetTrueContainerMatch[iJet].Phi());
      truthMatchJet_E.push_back(JetTrueContainerMatch[iJet].E());
      truthMatchJet_M.push_back(JetTrueContainerMatch[iJet].M());
      truthMatchJet_pX.push_back(JetTrueContainerMatch[iJet].Px());
      truthMatchJet_pY.push_back(JetTrueContainerMatch[iJet].Py());
      truthMatchJet_pZ.push_back(JetTrueContainerMatch[iJet].Pz());
    }
    for (int iJet = 0; iJet < JetRecoContainerMatch.size(); iJet++)
    {
      recoMatchJet_pT.push_back(JetRecoContainerMatch[iJet].Pt());
      recoMatchJet_eta.push_back(JetRecoContainerMatch[iJet].Eta());
      recoMatchJet_phi.push_back(JetRecoContainerMatch[iJet].Phi());
      recoMatchJet_E.push_back(JetRecoContainerMatch[iJet].E());
      recoMatchJet_M.push_back(JetRecoContainerMatch[iJet].M());
      recoMatchJet_pX.push_back(JetRecoContainerMatch[iJet].Px());
      recoMatchJet_pY.push_back(JetRecoContainerMatch[iJet].Py());
      recoMatchJet_pZ.push_back(JetRecoContainerMatch[iJet].Pz());
    }
    // electrons
    for (int iEle = 0; iEle < ElectronTrueContainerMatch.size(); iEle++)
    {
      truthMatchEle_pT.push_back(ElectronTrueContainerMatch[iEle].Pt());
      truthMatchEle_eta.push_back(ElectronTrueContainerMatch[iEle].Eta());
      truthMatchEle_phi.push_back(ElectronTrueContainerMatch[iEle].Phi());
      truthMatchEle_E.push_back(ElectronTrueContainerMatch[iEle].E());
      truthMatchEle_M.push_back(ElectronTrueContainerMatch[iEle].M());
      truthMatchEle_pX.push_back(ElectronTrueContainerMatch[iEle].Px());
      truthMatchEle_pY.push_back(ElectronTrueContainerMatch[iEle].Py());
      truthMatchEle_pZ.push_back(ElectronTrueContainerMatch[iEle].Pz());
      truthMatchEle_charge.push_back(electron_bare_charge[iEle]);
    }
    for (int iEle = 0; iEle < ElectronRecoContainerMatch.size(); iEle++)
    {
      recoMatchEle_pT.push_back(ElectronRecoContainerMatch[iEle].Pt());
      recoMatchEle_eta.push_back(ElectronRecoContainerMatch[iEle].Eta());
      recoMatchEle_phi.push_back(ElectronRecoContainerMatch[iEle].Phi());
      recoMatchEle_E.push_back(ElectronRecoContainerMatch[iEle].E());
      recoMatchEle_M.push_back(ElectronRecoContainerMatch[iEle].M());
      recoMatchEle_pX.push_back(ElectronRecoContainerMatch[iEle].Px());
      recoMatchEle_pY.push_back(ElectronRecoContainerMatch[iEle].Py());
      recoMatchEle_pZ.push_back(ElectronRecoContainerMatch[iEle].Pz());
      recoMatchEle_charge.push_back(electron_reco_charge[iEle]);
    }
    // muons
    for (int iMuon = 0; iMuon < MuonTrueContainerMatch.size(); iMuon++)
    {
      truthMatchMuon_pT.push_back(MuonTrueContainerMatch[iMuon].Pt());
      truthMatchMuon_eta.push_back(MuonTrueContainerMatch[iMuon].Eta());
      truthMatchMuon_phi.push_back(MuonTrueContainerMatch[iMuon].Phi());
      truthMatchMuon_E.push_back(MuonTrueContainerMatch[iMuon].E());
      truthMatchMuon_M.push_back(MuonTrueContainerMatch[iMuon].M());
      truthMatchMuon_pX.push_back(MuonTrueContainerMatch[iMuon].Px());
      truthMatchMuon_pY.push_back(MuonTrueContainerMatch[iMuon].Py());
      truthMatchMuon_pZ.push_back(MuonTrueContainerMatch[iMuon].Pz());
      truthMatchMuon_charge.push_back(muon_bare_charge[iMuon]);
    }
    for (int iMuon = 0; iMuon < MuonRecoContainerMatch.size(); iMuon++)
    {
      recoMatchMuon_pT.push_back(MuonRecoContainerMatch[iMuon].Pt());
      recoMatchMuon_eta.push_back(MuonRecoContainerMatch[iMuon].Eta());
      recoMatchMuon_phi.push_back(MuonRecoContainerMatch[iMuon].Phi());
      recoMatchMuon_E.push_back(MuonRecoContainerMatch[iMuon].E());
      recoMatchMuon_M.push_back(MuonRecoContainerMatch[iMuon].M());
      recoMatchMuon_pX.push_back(MuonRecoContainerMatch[iMuon].Px());
      recoMatchMuon_pY.push_back(MuonRecoContainerMatch[iMuon].Py());
      recoMatchMuon_pZ.push_back(MuonRecoContainerMatch[iMuon].Pz());
      recoMatchMuon_charge.push_back(muon_reco_charge[iMuon]);
    }



    // Fill tree
    outtree->Fill();



    // Clear branches
    // **************
    truthJet_pT.clear();
    truthJet_eta.clear();
    truthJet_phi.clear();
    truthJet_E.clear();
    truthJet_M.clear();
    truthJet_pX.clear();
    truthJet_pY.clear();
    truthJet_pZ.clear();

    truthMatchJet_pT.clear();
    truthMatchJet_eta.clear();
    truthMatchJet_phi.clear();
    truthMatchJet_E.clear();
    truthMatchJet_M.clear();
    truthMatchJet_pX.clear();
    truthMatchJet_pY.clear();
    truthMatchJet_pZ.clear();

    truthEle_pT.clear();
    truthEle_eta.clear();
    truthEle_phi.clear();
    truthEle_E.clear();
    truthEle_M.clear();
    truthEle_pX.clear();
    truthEle_pY.clear();
    truthEle_pZ.clear();
    truthEle_charge.clear();

    truthMatchEle_pT.clear();
    truthMatchEle_eta.clear();
    truthMatchEle_phi.clear();
    truthMatchEle_E.clear();
    truthMatchEle_M.clear();
    truthMatchEle_pX.clear();
    truthMatchEle_pY.clear();
    truthMatchEle_pZ.clear();
    truthMatchEle_charge.clear();

    truthMuon_pT.clear();
    truthMuon_eta.clear();
    truthMuon_phi.clear();
    truthMuon_E.clear();
    truthMuon_M.clear();
    truthMuon_pX.clear();
    truthMuon_pY.clear();
    truthMuon_pZ.clear();
    truthMuon_charge.clear();

    truthMatchMuon_pT.clear();
    truthMatchMuon_eta.clear();
    truthMatchMuon_phi.clear();
    truthMatchMuon_E.clear();
    truthMatchMuon_M.clear();
    truthMatchMuon_pX.clear();
    truthMatchMuon_pY.clear();
    truthMatchMuon_pZ.clear();
    truthMatchMuon_charge.clear();

    recoJet_pT.clear();
    recoJet_eta.clear();
    recoJet_phi.clear();
    recoJet_E.clear();
    recoJet_M.clear();
    recoJet_pX.clear();
    recoJet_pY.clear();
    recoJet_pZ.clear();

    recoMatchJet_pT.clear();
    recoMatchJet_eta.clear();
    recoMatchJet_phi.clear();
    recoMatchJet_E.clear();
    recoMatchJet_M.clear();
    recoMatchJet_pX.clear();
    recoMatchJet_pY.clear();
    recoMatchJet_pZ.clear();

    recoEle_pT.clear();
    recoEle_eta.clear();
    recoEle_phi.clear();
    recoEle_E.clear();
    recoEle_M.clear();
    recoEle_pX.clear();
    recoEle_pY.clear();
    recoEle_pZ.clear();
    recoEle_charge.clear();

    recoMatchEle_pT.clear();
    recoMatchEle_eta.clear();
    recoMatchEle_phi.clear();
    recoMatchEle_E.clear();
    recoMatchEle_M.clear();
    recoMatchEle_pX.clear();
    recoMatchEle_pY.clear();
    recoMatchEle_pZ.clear();
    recoMatchEle_charge.clear();

    recoMuon_pT.clear();
    recoMuon_eta.clear();
    recoMuon_phi.clear();
    recoMuon_E.clear();
    recoMuon_M.clear();
    recoMuon_pX.clear();
    recoMuon_pY.clear();
    recoMuon_pZ.clear();
    recoMuon_charge.clear();

    recoMatchMuon_pT.clear();
    recoMatchMuon_eta.clear();
    recoMatchMuon_phi.clear();
    recoMatchMuon_E.clear();
    recoMatchMuon_M.clear();
    recoMatchMuon_pX.clear();
    recoMatchMuon_pY.clear();
    recoMatchMuon_pZ.clear();
    recoMatchMuon_charge.clear();





  } // end of event loop

  // Write to tree
  outtree->Write();


  // Write and close file
  // --------------------
  output->Close();

  return 0;
}





//================================================================================//
//=============================== Main Function ==================================//
//================================================================================//

int MatchAndClean()
{
  

    // switch between these two options to run over Z or W boson samples
    // cannot run them in the same loop because it'll mess up the event numbers
    string boson = "WZ";
    // string boson = "W";
    
    std::vector<string> samples;
    DIR *dir_ptr;
    struct dirent *diread;
    if ((dir_ptr = opendir("../pythia-outputs")) != nullptr) {
        while ((diread = readdir(dir_ptr)) != nullptr) {
            string sample = diread->d_name;
            if (sample.find(".root") != string::npos){
              if(sample.find(boson) != string::npos)
                samples.push_back(sample);
            }
            
        }
        closedir(dir_ptr);
    }




    // loop over list of files and fill histograms with RunAnalysis
    for (int i = 0; i <samples.size(); i++) 
    {
        cout << "Analysing " << samples[i] << " ..." << endl;
        MyAnalysis(samples[i]);
    }

    return 0;

}