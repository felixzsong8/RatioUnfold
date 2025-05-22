
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
#include <vector>
#include <math.h>
#include <dirent.h>


// specify output file name
string outname = "analysisWThirdTest.root";

// specify directory of input files
string inpath = "../pythia-outputs";
// string inpath = "../detector-simul";



// =========================================================================================================================
// Note: This is function used in kinematic calculations
double delta_phi(double phi1, double phi2) 
{
  const double PI=2.0*acos(0.);
  const double TWOPI=2.0*PI;
  
  if (phi1<0) phi1= phi1+TWOPI;
  if (phi2<0) phi2= phi2+TWOPI;

  double PHI=fabs(phi1-phi2);

  return (PHI<=PI)? PHI : TWOPI-PHI;
}
// =========================================================================================================================


// ============================= //
// DEFINE YOUR HISTOGRAMS HERE!! //
// ============================= //


// Binning for pT-related histograms
Float_t ptlead_bins[] = {30.,40.,50.,60.,70.,80.,90.,100.,120.,140.,160.,180.,200.,220.,240.,260.,280.,300.,350.,400.,450.,500.,600.,700.,800.,900.,1000.};
//Float_t ptlead_bins[] = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400};
//Float_t ptlead_bins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 100, 150, 200, 250, 300, 350, 400};
Int_t ptlead_nbin = sizeof(ptlead_bins)/sizeof(Float_t) - 1;

// Declare Root Histograms
TH1F* NumberTrueJet = new TH1F("NumberTrueJet","Number of true jets with threshold above 30 GeV",10, 0, 9);
TH1F* LeadTrueJet_inc_pt = new TH1F("LeadTrueJet_inc_pt","Transverse momentum of the true leading jet when Njet > = 1",ptlead_nbin, ptlead_bins);
TH1F* LeadTrueJet_inc_rap = new TH1F("LeadTrueJet_inc_rap","Rapidity of the true leading jet when Njet > = 1",50, -5.0, 5.0);
TH1F* LeadTrueJet_inc_phi = new TH1F("LeadTrueJet_inc_phi","Azimuthal angle of the true leading jet when Njet > = 1",32, -3.2, 3.2);
TH1F* ScndTrueJet_inc_pt = new TH1F("ScndTrueJet_inc_pt","Transverse momentum of the true second jet when Njet > = 1",ptlead_nbin, ptlead_bins);
TH1F* ScndTrueJet_inc_rap = new TH1F("ScndTrueJet_inc_rap","Rapidity of the true second jet when Njet > = 1",50, -5.0, 5.0);
TH1F* ScndTrueJet_inc_phi = new TH1F("ScndTrueJet_inc_phi","Azimuthal angle of the true second jet when Njet > = 1",32, -3.2, 3.2);
TH1F* TrueDijet_Mjj = new TH1F("TrueDijet_Mjj","Invariant mass of the two leading jets at true level when Njet > = 2",ptlead_nbin, ptlead_bins);
TH1F* TrueDijet_Rjj = new TH1F("TrueDijet_Rjj","Angular distance between the two leading jets at true level when Njet > = 2",50, 0., 10.);
TH1F* TrueDimuon_M = new TH1F("TrueDimuon_M","Invariant mass of the two leading muons at true level",100,50,250);

TH1F* NumberRecoJet = new TH1F("NumberRecoJet","Number of reco jets with threshold above 30 GeV",10, 0, 9);
TH1F* LeadRecoJet_inc_pt = new TH1F("LeadRecoJet_inc_pt","Transverse momentum of the reco leading jet when Njet > = 1",ptlead_nbin, ptlead_bins);
TH1F* LeadRecoJet_inc_rap = new TH1F("LeadRecoJet_inc_rap","Rapidity of the reco leading jet when Njet > = 1",50, -5.0, 5.0);
TH1F* LeadRecoJet_inc_phi = new TH1F("LeadRecoJet_inc_phi","Azimuthal angle of the reco leading jet when Njet > = 1",32, -3.2, 3.2);
TH1F* ScndRecoJet_inc_pt = new TH1F("ScndRecoJet_inc_pt","Transverse momentum of the reco second jet when Njet > = 1",ptlead_nbin, ptlead_bins);
TH1F* ScndRecoJet_inc_rap = new TH1F("ScndRecoJet_inc_rap","Rapidity of the reco second jet when Njet > = 1",50, -5.0, 5.0);
TH1F* ScndRecoJet_inc_phi = new TH1F("ScndRecoJet_inc_phi","Azimuthal angle of the reco second jet when Njet > = 1",32, -3.2, 3.2);
TH1F* RecoDijet_Mjj = new TH1F("RecoDijet_Mjj","Invariant mass of the two leading jets at reco level when Njet > = 2",ptlead_nbin, ptlead_bins);
TH1F* RecoDijet_Rjj = new TH1F("RecoDijet_Rjj","Angular distance between the two leading jets at reco level when Njet > = 2",50, 0., 10.);
TH1F* RecoDimuon_M = new TH1F("RecoDimuon_M","Invariant mass of the two leading muons at reco level",100,50,250);

TH1F* WBoson_pt = new TH1F("WBoson_pt","W vector momentum",300, -20.0, 300.0);
TH1F* ZBoson_pt = new TH1F("ZBoson_pt","Z vector momentum",300, -20.0, 300.0);
TH1F* ZBosonReco_pt = new TH1F("ZBosonReco_pt","Z vector momentum",300, -20.0, 300.0);
TH1F* WBosonReco_pt = new TH1F("WBosonReco_pt","W vector momentum",300, -20.0, 300.0);



int RunAnalysis(string sample)
{

    // Load and read the output files from Pythia
    //===========================================

    // Path to input (reco and truth) root files
    string fileIn = "$PWD/../pythia-outputs/" + sample;

    // Load trees and create chain, add the file and create the tree reader
    TString tree = "ParticleTree";
    TChain *cc_tree = new TChain(tree);
    cc_tree->Add(fileIn.c_str());
    TTreeReader treeReader(cc_tree);

    // Load truth variables

        TTreeReaderArray<double> event_weights(treeReader, "event_weights");

        TTreeReaderValue<int> nTop(treeReader, "nTop");
        TTreeReaderValue<int> nNeutrino(treeReader, "nNeutrino");
        TTreeReaderValue<int> nMuonBare(treeReader, "nMuonBare");
        TTreeReaderValue<int> nElectronBare(treeReader, "nElectronBare");
        TTreeReaderValue<int> nMuonDress(treeReader, "nMuonDress");
        TTreeReaderValue<int> nElectronDress(treeReader, "nElectronDress");
        TTreeReaderValue<int> nMuonBorn(treeReader, "nMuonBorn");
        TTreeReaderValue<int> nElectronBorn(treeReader, "nElectronBorn");
        TTreeReaderValue<int> nLightjetBare(treeReader, "nLightjetBare");
        TTreeReaderValue<int> nBjetBare(treeReader, "nBjetBare");
        TTreeReaderValue<int> nJetDress(treeReader, "nJetDress");
        TTreeReaderValue<int> nJetBorn(treeReader, "nJetBorn");
        // TTreeReaderValue<int> nLargeRjetDress(treeReader, "nLargeRjetDress");
        // TTreeReaderValue<int> nLargeRjetBare(treeReader, "nLargeRjetBare");
        // TTreeReaderValue<int> nLargeRjetBorn(treeReader, "nLargeRjetBorn");
        TTreeReaderValue<int> nBoson(treeReader, "nBoson");
        TTreeReaderValue<int> nLightpartonjet(treeReader, "nLightpartonjet");
        TTreeReaderValue<int> nBpartonjet(treeReader, "nBpartonjet");
        TTreeReaderValue<double> Met(treeReader, "Met");
        TTreeReaderValue<double> Met_phi(treeReader, "Met_phi");

        TTreeReaderArray<int> neutrino_PdgId(treeReader, "neutrino_PdgId");
        TTreeReaderArray<int> lightjet_bare_nPart(treeReader, "lightjet_bare_nPart");
        TTreeReaderArray<int> jet_dress_nPart(treeReader, "jet_dress_nPart");
        TTreeReaderArray<int> jet_born_nPart(treeReader, "jet_born_nPart");
        TTreeReaderArray<int> bjet_bare_nPart(treeReader, "bjet_bare_nPart");
        TTreeReaderArray<int> boson_ID(treeReader, "boson_ID");
    
        TTreeReaderArray<float> top_pt(treeReader, "top_pt");
        TTreeReaderArray<float> top_eta(treeReader, "top_eta");
        TTreeReaderArray<float> top_phi(treeReader, "top_phi");
        TTreeReaderArray<float> top_E(treeReader, "top_E");
        TTreeReaderArray<float> neutrino_pt(treeReader, "neutrino_pt");
        TTreeReaderArray<float> neutrino_eta(treeReader, "neutrino_eta");
        TTreeReaderArray<float> neutrino_phi(treeReader, "neutrino_phi");
        TTreeReaderArray<float> neutrino_E(treeReader, "neutrino_E");
        TTreeReaderArray<float> muon_bare_pt(treeReader, "muon_bare_pt");
        TTreeReaderArray<float> muon_bare_eta(treeReader, "muon_bare_eta");
        TTreeReaderArray<float> muon_bare_phi(treeReader, "muon_bare_phi");
        TTreeReaderArray<float> muon_bare_E(treeReader, "muon_bare_E");
        TTreeReaderArray<float> muon_bare_charge(treeReader, "muon_bare_charge");
        TTreeReaderArray<float> muon_dress_pt(treeReader, "muon_dress_pt");
        TTreeReaderArray<float> muon_dress_eta(treeReader, "muon_dress_eta");
        TTreeReaderArray<float> muon_dress_phi(treeReader, "muon_dress_phi");
        TTreeReaderArray<float> muon_dress_E(treeReader, "muon_dress_E");
        TTreeReaderArray<float> muon_dress_charge(treeReader, "muon_dress_charge");
        TTreeReaderArray<float> muon_born_pt(treeReader, "muon_born_pt");
        TTreeReaderArray<float> muon_born_eta(treeReader, "muon_born_eta");
        TTreeReaderArray<float> muon_born_phi(treeReader, "muon_born_phi");
        TTreeReaderArray<float> muon_born_E(treeReader, "muon_born_E");
        TTreeReaderArray<float> muon_born_charge(treeReader, "muon_born_charge");
        TTreeReaderArray<float> electron_bare_pt(treeReader, "electron_bare_pt");
        TTreeReaderArray<float> electron_bare_eta(treeReader, "electron_bare_eta");
        TTreeReaderArray<float> electron_bare_phi(treeReader, "electron_bare_phi");
        TTreeReaderArray<float> electron_bare_E(treeReader, "electron_bare_E");
        TTreeReaderArray<float> electron_bare_charge(treeReader, "electron_bare_charge");
        TTreeReaderArray<float> electron_dress_pt(treeReader, "electron_dress_pt");
        TTreeReaderArray<float> electron_dress_eta(treeReader, "electron_dress_eta");
        TTreeReaderArray<float> electron_dress_phi(treeReader, "electron_dress_phi");
        TTreeReaderArray<float> electron_dress_E(treeReader, "electron_dress_E");
        TTreeReaderArray<float> electron_dress_charge(treeReader, "electron_dress_charge");
        TTreeReaderArray<float> electron_born_pt(treeReader, "electron_born_pt");
        TTreeReaderArray<float> electron_born_eta(treeReader, "electron_born_eta");
        TTreeReaderArray<float> electron_born_phi(treeReader, "electron_born_phi");
        TTreeReaderArray<float> electron_born_E(treeReader, "electron_born_E");
        TTreeReaderArray<float> electron_born_charge(treeReader, "electron_born_charge");
        TTreeReaderArray<float> lightjet_bare_pt(treeReader, "lightjet_bare_pt");
        TTreeReaderArray<float> lightjet_bare_eta(treeReader, "lightjet_bare_eta");
        TTreeReaderArray<float> lightjet_bare_phi(treeReader, "lightjet_bare_phi");
        TTreeReaderArray<float> lightjet_bare_E(treeReader, "lightjet_bare_E");
        TTreeReaderArray<float> jet_dress_pt(treeReader, "jet_dress_pt");
        TTreeReaderArray<float> jet_dress_eta(treeReader, "jet_dress_eta");
        TTreeReaderArray<float> jet_dress_phi(treeReader, "jet_dress_phi");
        TTreeReaderArray<float> jet_dress_E(treeReader, "jet_dress_E");
        TTreeReaderArray<float> bjet_bare_pt(treeReader, "bjet_bare_pt");
        TTreeReaderArray<float> bjet_bare_eta(treeReader, "bjet_bare_eta");
        TTreeReaderArray<float> bjet_bare_phi(treeReader, "bjet_bare_phi");
        TTreeReaderArray<float> bjet_bare_E(treeReader, "bjet_bare_E");
        TTreeReaderArray<float> jet_born_pt(treeReader, "jet_born_pt");
        TTreeReaderArray<float> jet_born_eta(treeReader, "jet_born_eta");
        TTreeReaderArray<float> jet_born_phi(treeReader, "jet_born_phi");
        TTreeReaderArray<float> jet_born_E(treeReader, "jet_born_E");
        TTreeReaderArray<float> largeRjet_bare_pt(treeReader, "largeRjet_bare_pt");
        TTreeReaderArray<float> largeRjet_bare_eta(treeReader, "largeRjet_bare_eta");
        TTreeReaderArray<float> largeRjet_bare_phi(treeReader, "largeRjet_bare_phi");
        TTreeReaderArray<float> largeRjet_bare_E(treeReader, "largeRjet_bare_E");
        TTreeReaderArray<float> largeRjet_dress_pt(treeReader, "largeRjet_dress_pt");
        TTreeReaderArray<float> largeRjet_dress_eta(treeReader, "largeRjet_dress_eta");
        TTreeReaderArray<float> largeRjet_dress_phi(treeReader, "largeRjet_dress_phi");
        TTreeReaderArray<float> largeRjet_dress_E(treeReader, "largeRjet_dress_E");
        TTreeReaderArray<float> largeRjet_born_pt(treeReader, "largeRjet_born_pt");
        TTreeReaderArray<float> largeRjet_born_eta(treeReader, "largeRjet_born_eta");
        TTreeReaderArray<float> largeRjet_born_phi(treeReader, "largeRjet_born_phi");
        TTreeReaderArray<float> largeRjet_born_E(treeReader, "largeRjet_born_E");
        TTreeReaderArray<float> lightpartonjet_pt(treeReader, "lightpartonjet_pt");
        TTreeReaderArray<float> lightpartonjet_eta(treeReader, "lightpartonjet_eta");
        TTreeReaderArray<float> lightpartonjet_phi(treeReader, "lightpartonjet_phi");
        TTreeReaderArray<float> lightpartonjet_E(treeReader, "lightpartonjet_E");
        TTreeReaderArray<float> bpartonjet_pt(treeReader, "bpartonjet_pt");
        TTreeReaderArray<float> bpartonjet_eta(treeReader, "bpartonjet_eta");
        TTreeReaderArray<float> bpartonjet_phi(treeReader, "bpartonjet_phi");
        TTreeReaderArray<float> bpartonjet_E(treeReader, "bpartonjet_E");
        TTreeReaderArray<float> boson_pt(treeReader, "boson_pt");
        TTreeReaderArray<float> boson_eta(treeReader, "boson_eta");
        TTreeReaderArray<float> boson_phi(treeReader, "boson_phi");
        TTreeReaderArray<float> boson_E(treeReader, "boson_E");

        TTreeReaderArray<double> BarekTSplittingScale1_R04(treeReader, "BarekTSplittingScale1_R04");
        TTreeReaderArray<double> BarekTSplittingScale2_R04(treeReader, "BarekTSplittingScale2_R04");
        TTreeReaderArray<double> BarekTSplittingScale3_R04(treeReader, "BarekTSplittingScale3_R04");
        TTreeReaderArray<double> BarekTSplittingScale1_R10(treeReader, "BarekTSplittingScale1_R10");
        TTreeReaderArray<double> BarekTSplittingScale2_R10(treeReader, "BarekTSplittingScale2_R10");
        TTreeReaderArray<double> BarekTSplittingScale3_R10(treeReader, "BarekTSplittingScale3_R10");
        TTreeReaderArray<double> DresskTSplittingScale1_R04(treeReader, "DresskTSplittingScale1_R04");
        TTreeReaderArray<double> DresskTSplittingScale2_R04(treeReader, "DresskTSplittingScale2_R04");
        TTreeReaderArray<double> DresskTSplittingScale3_R04(treeReader, "DresskTSplittingScale3_R04");
        TTreeReaderArray<double> DresskTSplittingScale1_R10(treeReader, "DresskTSplittingScale1_R10");
        TTreeReaderArray<double> DresskTSplittingScale2_R10(treeReader, "DresskTSplittingScale2_R10");
        TTreeReaderArray<double> DresskTSplittingScale3_R10(treeReader, "DresskTSplittingScale3_R10");
        TTreeReaderArray<double> BornkTSplittingScale1_R04(treeReader, "BornkTSplittingScale1_R04");
        TTreeReaderArray<double> BornkTSplittingScale2_R04(treeReader, "BornkTSplittingScale2_R04");
        TTreeReaderArray<double> BornkTSplittingScale3_R04(treeReader, "BornkTSplittingScale3_R04");
        TTreeReaderArray<double> BornkTSplittingScale1_R10(treeReader, "BornkTSplittingScale1_R10");
        TTreeReaderArray<double> BornkTSplittingScale2_R10(treeReader, "BornkTSplittingScale2_R10");
        TTreeReaderArray<double> BornkTSplittingScale3_R10(treeReader, "BornkTSplittingScale3_R10");

    // End truth variables
    

    // Load reco variables

        TTreeReaderValue<int> nMuonReco(treeReader, "nMuonReco");
        TTreeReaderValue<int> nElectronReco(treeReader, "nElectronReco");
        TTreeReaderValue<int> nJetReco(treeReader, "nJetReco");
        TTreeReaderValue<double> RecoMet(treeReader, "RecoMet");
        TTreeReaderValue<double> RecoMet_phi(treeReader, "RecoMet_phi");  


        TTreeReaderArray<float> muon_reco_pt(treeReader, "muon_reco_pt");
        TTreeReaderArray<float> muon_reco_eta(treeReader, "muon_reco_eta");
        TTreeReaderArray<float> muon_reco_phi(treeReader, "muon_reco_phi");
        TTreeReaderArray<float> muon_reco_E(treeReader, "muon_reco_E");
        TTreeReaderArray<float> muon_reco_charge(treeReader, "muon_reco_charge");
        TTreeReaderArray<float> electron_reco_pt(treeReader, "electron_reco_pt");
        TTreeReaderArray<float> electron_reco_eta(treeReader, "electron_reco_eta");
        TTreeReaderArray<float> electron_reco_phi(treeReader, "electron_reco_phi");
        TTreeReaderArray<float> electron_reco_E(treeReader, "electron_reco_E");
        TTreeReaderArray<float> electron_reco_charge(treeReader, "electron_reco_charge");
        TTreeReaderArray<float> jet_reco_pt(treeReader, "jet_reco_pt");
        TTreeReaderArray<float> jet_reco_eta(treeReader, "jet_reco_eta");
        TTreeReaderArray<float> jet_reco_phi(treeReader, "jet_reco_phi");
        TTreeReaderArray<float> jet_reco_E(treeReader, "jet_reco_E");
    // End reco variables

    

    // Control parameter
    bool dosystematics = false;
    int systnum = 0;
    bool electronChannel = false;
    bool muonChannel =  true;



    // Loop over the events to run analysis on the ntuple
    // ==================================================

    while(treeReader.Next())
    {
        

        // Reweight the event if needed
        double wgt = 1.0;
        if (dosystematics) wgt = event_weights[systnum];

        // Fetch object kinematics
        // =======================

        // Get true and reco jets - especially the first 3 most energetic jets
        // -------------------------------------------------------------------
        // Note: Jets are already defined in the ntuple with Antikt4 with Pt>30 GeV and eta<4.9. They don't include neutrinos and prompt leptons

        vector<TLorentzVector> JetTrueContainer;
        vector<TLorentzVector> JetRecoContainer;
        TLorentzVector VecSumAllTrueJets;
        TLorentzVector VecSumAllRecoJets;
        int NjTrue = 0;
        int NjReco = 0;

   

        for (int itjet = 0; itjet<lightjet_bare_E.GetSize(); itjet++)
        {
            // print true jet pT in order
            // myfileT << std::fixed << std::setprecision(2) << jet_true_pt[itjet] << " \n";

            TLorentzVector temptruejet;
            temptruejet.SetPtEtaPhiE(lightjet_bare_pt[itjet], lightjet_bare_eta[itjet], lightjet_bare_phi[itjet], lightjet_bare_E[itjet]);
            JetTrueContainer.push_back(temptruejet);
            VecSumAllTrueJets += temptruejet;
            if ( (lightjet_bare_pt[itjet] > 30. ) && ( fabs(lightjet_bare_eta[itjet]) < 4.4) ) NjTrue++;
        }

        for (int irjet = 0; irjet<jet_reco_pt.GetSize(); irjet++)
        {
            // print reco jet pT in order
            // myfileR << std::fixed << std::setprecision(2) << jet_reco_pt[irjet] << " \n";

            TLorentzVector temprecojet;
            temprecojet.SetPtEtaPhiE(jet_reco_pt[irjet], jet_reco_eta[irjet], jet_reco_phi[irjet], jet_reco_E[irjet]);
            JetRecoContainer.push_back(temprecojet);
            VecSumAllRecoJets += temprecojet;
            if ( (jet_reco_pt[irjet] > 30. ) && ( fabs(jet_reco_eta[irjet]) < 4.4) ) NjReco++;
        }

        TLorentzVector LeadTrueJet;
        TLorentzVector ScndTrueJet;
        TLorentzVector ThrdTrueJet;
        TLorentzVector LeadRecoJet;
        TLorentzVector ScndRecoJet;
        TLorentzVector ThrdRecoJet;


        if (JetTrueContainer.size() > 0) LeadTrueJet = JetTrueContainer[0];
        if (JetTrueContainer.size() > 1) ScndTrueJet = JetTrueContainer[1];
        if (JetTrueContainer.size() > 2) ThrdTrueJet = JetTrueContainer[2];
        if (JetRecoContainer.size() > 0) LeadRecoJet = JetRecoContainer[0];
        if (JetRecoContainer.size() > 1) ScndRecoJet = JetRecoContainer[1];
        if (JetRecoContainer.size() > 2) ThrdRecoJet = JetRecoContainer[2];





        // Get charged lepton kinematics (truth and reco)
        // ----------------------------------------------

        vector<TLorentzVector> ElectronTrueContainer;
        vector<TLorentzVector> ElectronRecoContainer;
        vector<TLorentzVector> MuonTrueContainer;
        vector<TLorentzVector> MuonRecoContainer;

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


        for (int itmuo = 0; itmuo<muon_bare_pt.GetSize(); itmuo++)
        {
            TLorentzVector temptruemuo;
            temptruemuo.SetPtEtaPhiE(muon_bare_pt[itmuo], muon_bare_eta[itmuo], muon_bare_phi[itmuo], muon_bare_E[itmuo]);
            MuonTrueContainer.push_back(temptruemuo);
        }

        for (int irmuo = 0; irmuo<muon_reco_pt.GetSize(); irmuo++)
        {
            TLorentzVector temprecomuo;
            temprecomuo.SetPtEtaPhiE(muon_reco_pt[irmuo], muon_reco_eta[irmuo], muon_reco_phi[irmuo], muon_reco_E[irmuo]);
            MuonRecoContainer.push_back(temprecomuo);
        }


        TLorentzVector Electron1_True;
        TLorentzVector Electron2_True;
        TLorentzVector Electron1_Reco;
        TLorentzVector Electron2_Reco;

        TLorentzVector Muon1_True;
        TLorentzVector Muon2_True;
        TLorentzVector Muon1_Reco;
        TLorentzVector Muon2_Reco;

        if (ElectronTrueContainer.size() > 0) Electron1_True = ElectronTrueContainer[0];
        if (ElectronTrueContainer.size() > 1) Electron2_True = ElectronTrueContainer[1];
        if (ElectronRecoContainer.size() > 0) Electron1_Reco = ElectronRecoContainer[0];
        if (ElectronRecoContainer.size() > 1) Electron2_Reco = ElectronRecoContainer[1];

        if (MuonTrueContainer.size() > 0) Muon1_True = MuonTrueContainer[0];
        if (MuonTrueContainer.size() > 1) Muon2_True = MuonTrueContainer[1];
        if (MuonRecoContainer.size() > 0) Muon1_Reco = MuonRecoContainer[0];
        if (MuonRecoContainer.size() > 1) Muon2_Reco = MuonRecoContainer[1];



        // Calculate vector boson kinematic (truth W, truth and reco Z)
        // ------------------------------------------------------------

        // Note: For truth level, the kinematic of the vector boson is directly taken from the event record, but for reco level
        //       it has to be reconstructed from the decay product at detector level, i.e. from the leptons. Because at detector
        //       level we cannot measure all the degrees of freedom of neutrinos, we cannot reconstruct the 4-vector of W bosons.
        //       We therefore only reconstruct the 4-vector of the Z, and compute will compute later transverse quantities for W
        //       using charged leptons and reco Met.


        TLorentzVector ZBosonTrue;
        TLorentzVector WBosonTrue;
        TLorentzVector DimuonTrue;
        TLorentzVector ZBosonReco;

        if ((*nBoson)>0)
        {
            if (boson_ID[0] == 23) ZBosonTrue.SetPtEtaPhiE(boson_pt[0], boson_eta[0], boson_phi[0], boson_E[0]);
            else if ( fabs(boson_ID[0]) == 24 ) WBosonTrue.SetPtEtaPhiE(boson_pt[0], boson_eta[0], boson_phi[0], boson_E[0]);
        }

        if ( (MuonRecoContainer.size() > 1) && ( Muon1_Reco.Pt() > Electron1_Reco.Pt() ) ) ZBosonReco = Muon1_Reco + Muon2_Reco;
        else if (ElectronRecoContainer.size() > 1 ) ZBosonReco = Electron1_Reco + Electron2_Reco;

        if ( MuonTrueContainer.size() > 1)  DimuonTrue = Muon1_True + Muon2_True;



        // Calculate kinematic variables to cut on or to plot
        // ==================================================


        // Count the number of leptons above veto thresholds
        // -------------------------------------------------

        // Note: We cannot robustly and accurately reconstruct charged leptons below 7 GeV and beyond |eta| 2.4, even
        //       when the trigger was fired by some other object. We set a counter for all charged lepton that pass
        //       these kinematic requirements.


        int nLowMuoTrue = 0;
        int nLowMuoReco = 0;
        int nLowEleTrue = 0;
        int nLowEleReco = 0;

        for (size_t iMuo = 0; iMuo < *nMuonBare; iMuo++)
        {
            if ( (muon_bare_pt[iMuo] >= 7.0) && fabs(muon_bare_eta[iMuo]) < 2.4 ) nLowMuoTrue++ ;
        }

        for (size_t iMuo = 0; iMuo < *nMuonReco; iMuo++)
        {
            if ( (muon_reco_pt[iMuo] >= 7.0) && fabs(muon_reco_eta[iMuo]) < 2.4 ) nLowMuoReco++ ;
        }

        for (size_t iEle = 0; iEle < *nElectronBare; iEle++)
        {
            if ( (electron_bare_pt[iEle] >= 7.0) && fabs(electron_bare_eta[iEle]) < 2.4 ) nLowEleTrue++ ;
        }

        for (size_t iEle = 0; iEle < *nElectronReco; iEle++)
        {
            if ( (electron_reco_pt[iEle] >= 7.0) && fabs(electron_reco_eta[iEle]) < 2.4 ) nLowEleReco++ ;
        }




        // Vector boson kinematic variables
        // --------------------------------

        // W transverse mass (MT)
        // ......................

        float WMTTrue;
        float WMTReco;

        WMTTrue = WBosonTrue.Mt();

        if (MuonRecoContainer.size() > 0  && (Muon1_Reco.Pt() > Electron1_Reco.Pt() ) ) WMTReco = sqrt(2*Muon1_Reco.Pt()*(*RecoMet)*(1.-cos(delta_phi(Muon1_Reco.Phi(),(*RecoMet_phi)))));
        else if (ElectronRecoContainer.size() > 0 ) WMTReco = sqrt(2*Electron1_Reco.Pt()*(*RecoMet)*(1.-cos(delta_phi(Electron1_Reco.Phi(),(*RecoMet_phi)))));


        // W transverse momentum (Pt)
        // ..........................

        float WPtTrue;
        float WPtReco;

        WPtTrue = WBosonTrue.Pt();


        if (MuonRecoContainer.size() > 0 && (Muon1_Reco.Pt() > Electron1_Reco.Pt() ) ) WPtReco = sqrt( (Muon1_Reco.Px()+ (*RecoMet)*cos((*RecoMet_phi)))*(Muon1_Reco.Px()+ (*RecoMet)*cos((*RecoMet_phi))) + (Muon1_Reco.Py()+ (*RecoMet)*sin((*RecoMet_phi)))*(Muon1_Reco.Py()+ (*RecoMet)*sin((*RecoMet_phi)))  );
        else if (ElectronRecoContainer.size() > 0 ) WPtReco = sqrt( (Electron1_Reco.Px()+ (*RecoMet)*cos((*RecoMet_phi)))*(Electron1_Reco.Px()+ (*RecoMet)*cos((*RecoMet_phi))) + (Electron1_Reco.Py()+ (*RecoMet)*sin((*RecoMet_phi)))*(Electron1_Reco.Py()+ (*RecoMet)*sin((*RecoMet_phi)))  );


        // Z invariance mass (Mll)
        // .......................

        float ZMllTrue = ZBosonTrue.M();
        float ZMllReco = ZBosonReco.M();
        float DimuonMassTrue = DimuonTrue.M();


        // Z transverse momentum (Pt)
        // .......................

        float ZPtTrue;
        float ZPtReco;

        ZPtTrue = ZBosonTrue.Pt();
        //if (MuonRecoContainer.size() > 1 && (Muon1_Reco.Pt() > Electron1_Reco.Pt())) ZPtReco = sqrt( (Muon1_Reco.Px() + Muon2_Reco.Px()) * (Muon1_Reco.Px() + Muon2_Reco.Px()) + (Muon1_Reco.Py() + Muon2_Reco.Py()) * (Muon1_Reco.Py() + Muon2_Reco.Py()) );
        //else if (ElectronRecoContainer.size() > 1) ZPtReco = sqrt( (Electron1_Reco.Px() + Electron2_Reco.Px()) * (Electron1_Reco.Px() + Electron2_Reco.Px()) + (Electron1_Reco.Py() + Electron2_Reco.Py()) * (Electron1_Reco.Py() + Electron2_Reco.Py()) );
        ZPtReco = ZBosonReco.Pt();


        // Multijet kinematic variables
        // ----------------------------

        // Dijet invariant mass (Mjj)
        // ......................

        TLorentzVector Dijet_True;
        TLorentzVector Dijet_Reco;

        Dijet_True = LeadTrueJet + ScndTrueJet;
        Dijet_Reco = LeadRecoJet + ScndRecoJet;

        float MjjTrue = Dijet_True.M();
        float MjjReco = Dijet_Reco.M();





        // Angular distance between the two leading jets (Delta Rjj)
        // .........................................................

        float dEtajj_True = 0.;
        float dPhijj_True = 0.;
        float dRjj_True = 0.;
        float dEtajj_Reco = 0.;
        float dPhijj_Reco = 0.;
        float dRjj_Reco = 0.;

        if (JetTrueContainer.size() > 1) dEtajj_True = LeadTrueJet.Eta() - ScndTrueJet.Eta();
        if (JetRecoContainer.size() > 1) dEtajj_Reco = LeadRecoJet.Eta() - ScndRecoJet.Eta();
        if (JetTrueContainer.size() > 1) dPhijj_True = delta_phi(LeadTrueJet.Phi(),ScndTrueJet.Phi());
        if (JetRecoContainer.size() > 1) dPhijj_Reco = delta_phi(LeadRecoJet.Phi(),ScndRecoJet.Phi());
        if (JetTrueContainer.size() > 1) dRjj_True = sqrt( dEtajj_True*dEtajj_True + dPhijj_True*dPhijj_True);
        if (JetRecoContainer.size() > 1) dRjj_Reco = sqrt( dEtajj_Reco*dEtajj_Reco + dPhijj_Reco*dPhijj_Reco);



        // Define flags for event selections
        // ==================================

        // Number of Jets Selections
        // -------------------------

        bool Pass_Incl_1jetTrue = true;
        bool Pass_Excl_1jetTrue = true;
        bool Pass_Incl_2jetTrue = true;
        bool Pass_Excl_2jetTrue = true;
        bool Pass_Incl_3jetTrue = true;

        bool Pass_Incl_1jetReco = true;
        bool Pass_Excl_1jetReco = true;
        bool Pass_Incl_2jetReco = true;
        bool Pass_Excl_2jetReco = true;
        bool Pass_Incl_3jetReco = true;

        if (LeadTrueJet.Pt() > 30. && fabs(LeadTrueJet.Eta()) < 4.4 ) Pass_Incl_1jetTrue = true;
        if (ScndTrueJet.Pt() > 30. && fabs(ScndTrueJet.Eta()) < 4.4 ) Pass_Incl_2jetTrue = true;
        if (ThrdTrueJet.Pt() > 30. && fabs(ThrdTrueJet.Eta()) < 4.4 ) Pass_Incl_3jetTrue = true;
        if (LeadRecoJet.Pt() > 30. && fabs(LeadRecoJet.Eta()) < 4.4 ) Pass_Incl_1jetReco = true;
        if (ScndRecoJet.Pt() > 30. && fabs(ScndRecoJet.Eta()) < 4.4 ) Pass_Incl_2jetReco = true;
        if (ThrdRecoJet.Pt() > 30. && fabs(ThrdRecoJet.Eta()) < 4.4 ) Pass_Incl_3jetReco = true;


        if (Pass_Incl_1jetTrue && !Pass_Incl_2jetTrue) Pass_Excl_1jetTrue = true;
        if (Pass_Incl_1jetReco && !Pass_Incl_2jetReco) Pass_Excl_1jetReco = true;
        if (Pass_Incl_2jetTrue && !Pass_Incl_3jetTrue) Pass_Excl_2jetTrue = true;
        if (Pass_Incl_2jetReco && !Pass_Incl_3jetReco) Pass_Excl_2jetReco = true;


        // Central High Pt Jets
        // --------------------

        bool Pass_CentralHighPtJet_True = true;
        bool Pass_CentralHighPtJet_Reco = true;

        if (LeadTrueJet.Pt() > 100. && fabs(LeadTrueJet.Eta()) < 4.4 ) Pass_CentralHighPtJet_True = true;
        if (LeadRecoJet.Pt() > 100. && fabs(LeadRecoJet.Eta()) < 4.4 ) Pass_CentralHighPtJet_Reco = true;


        // Set fiducial lepton cuts (high-pt)
        // ----------------------------------

        // Note: Don't forget to set the right lepton channel flag in the "Control parameter" section

        bool PassTrueLepton = true;
        bool PassRecoLepton = true;
        bool PassTrueMet = true;
        bool PassRecoMet = true;
        bool PassTrueWboson = true;
        bool PassRecoWboson = true;

        if (muonChannel)
        {
            if ( (nLowEleTrue == 0) &&  (nLowMuoTrue==2) && Muon1_True.Pt() > 25. && fabs(Muon1_True.Eta()) < 2.5) PassTrueLepton = true;
            if ( (nLowEleReco == 0) &&  (nLowMuoReco==2) && Muon1_Reco.Pt() > 25. && fabs(Muon1_Reco.Eta()) < 2.5) PassRecoLepton = true;
        }
        else if (electronChannel)
        {
            if ( (nLowEleTrue == 1) &&  (nLowMuoTrue==0) && Electron1_True.Pt() > 100. && fabs(Electron1_True.Eta()) < 2.5) PassTrueLepton = true;
            if ( (nLowEleReco == 1) &&  (nLowMuoReco==0) && Electron1_Reco.Pt() > 100. && fabs(Electron1_Reco.Eta()) < 2.5) PassRecoLepton = true;
        }


        if ((*Met)>75.) PassTrueMet = true;
        if ((*RecoMet)>75.) PassRecoMet = true;


        if (WMTTrue>40.) PassTrueWboson =  true;
        if (WMTReco>40.) PassRecoWboson =  true;




        // Apply cuts and fill histograms
        // ==============================


        // True-level plots
        // ----------------

        // Request at least 2 jets, 1 central high pt jet, one  high-pt lepton and large Met
        // .................................................................................
        if (PassTrueLepton)
        {
            NumberTrueJet->Fill(NjTrue, wgt);
            if (Pass_Incl_1jetTrue && Pass_CentralHighPtJet_True)
            {
                LeadTrueJet_inc_pt->Fill(LeadTrueJet.Pt(), wgt);
                LeadTrueJet_inc_rap->Fill(LeadTrueJet.Rapidity(), wgt);
                LeadTrueJet_inc_phi->Fill(LeadTrueJet.Phi(), wgt);
                if (NjTrue > 1)
                {   
                    // Fill histograms using the lead jet (or any additional logic you may want)
                    ScndTrueJet_inc_pt->Fill(ScndTrueJet.Pt(), wgt);  // Use Lead jet's Pt for the second jet histogram
                    ScndTrueJet_inc_rap->Fill(ScndTrueJet.Rapidity(), wgt);  // Use Lead jet's Rapidity
                    ScndTrueJet_inc_phi->Fill(ScndTrueJet.Phi(), wgt);  // Use Lead jet's Phi
                }
                TrueDijet_Mjj->Fill(MjjTrue, wgt);
                TrueDijet_Rjj->Fill(dRjj_True, wgt);
                TrueDimuon_M->Fill(DimuonMassTrue, wgt);
                WBoson_pt->Fill(WPtTrue, wgt);
                ZBoson_pt->Fill(ZPtTrue, wgt);
            }
        }


        // Reco-level plots
        // ----------------

        // Request at least 2 jets, 1 central high pt jet, one  high-pt lepton and large Met
        // .................................................................................

        if (PassRecoLepton)
        {
            NumberRecoJet->Fill(NjReco, wgt);

            if (Pass_Incl_1jetReco && Pass_CentralHighPtJet_Reco)
            {
                LeadRecoJet_inc_pt->Fill(LeadRecoJet.Pt(), wgt);
                LeadRecoJet_inc_rap->Fill(LeadRecoJet.Rapidity(), wgt);
                LeadRecoJet_inc_phi->Fill(LeadRecoJet.Phi(), wgt);
                if (NjReco > 1)
                {
                    // Fill histograms using the lead jet (or any additional logic you may want)
                    ScndRecoJet_inc_pt->Fill(ScndRecoJet.Pt(), wgt);  // Use Lead jet's Pt for the second jet histogram
                    ScndRecoJet_inc_rap->Fill(ScndRecoJet.Rapidity(), wgt);  // Use Lead jet's Rapidity
                    ScndRecoJet_inc_phi->Fill(ScndRecoJet.Phi(), wgt);  // Use Lead jet's Phi
                }
                RecoDijet_Mjj->Fill(MjjReco, wgt);
                RecoDijet_Rjj->Fill(dRjj_Reco, wgt);
                RecoDimuon_M->Fill(ZMllReco, wgt);
                ZBosonReco_pt->Fill(ZPtReco, wgt);
                WBosonReco_pt->Fill(WPtReco, wgt);
            }
        }

    } // End loop on events



    return 0;
}



//================================================================================//
//=============================== Main Function ==================================//
//================================================================================//

int MyAnalysis()
{

    // two options:
    // -----------

    // give a list of files (within pythia-outputs)
    // std::vector<string> samples = {"truth1.root", "truth2.root", "truth3.root"} 

    // or run over all files in pythia-output/ directory
    std::vector<string> samples;
    DIR *dir_ptr;
    struct dirent *diread;
    if ((dir_ptr = opendir(inpath.c_str())) != nullptr) {
        while ((diread = readdir(dir_ptr)) != nullptr) {
            string sample = diread->d_name;
            if (sample.find(".root") != string::npos){
                samples.push_back(sample);
            }
            
        }
        closedir(dir_ptr);
    }

    // print output file name
    std::cout << "Output file name: " << outname << std::endl;

    // Create new file for histograms of analyzed data
    TFile *outFile = TFile::Open(outname.c_str(), "recreate");

    // loop over list of files and fill histograms with RunAnalysis
    for (int i = 0; i <samples.size(); i++) 
    {
        cout << "Analysing " << samples[i] << " ..." << endl;
        RunAnalysis(samples[i]);
    }


    //  Write histograms
    // ----------------

    NumberTrueJet->Write();
    LeadTrueJet_inc_pt->Write();
    LeadTrueJet_inc_rap->Write();
    LeadTrueJet_inc_phi->Write();
    ScndTrueJet_inc_pt->Write();
    ScndTrueJet_inc_rap->Write();
    ScndTrueJet_inc_phi->Write();
    TrueDijet_Mjj->Write();
    TrueDijet_Rjj->Write();
    TrueDimuon_M->Write();
    WBoson_pt->Write();
    ZBoson_pt->Write();

    NumberRecoJet->Write();
    LeadRecoJet_inc_pt->Write();
    LeadRecoJet_inc_rap->Write();
    LeadRecoJet_inc_phi->Write();
    ScndRecoJet_inc_pt->Write();
    ScndRecoJet_inc_rap->Write();
    ScndRecoJet_inc_phi->Write();
    RecoDijet_Mjj->Write();
    RecoDijet_Rjj->Write();
    RecoDimuon_M->Write();
    ZBosonReco_pt->Write();
    WBosonReco_pt->Write();



    // Close output file
    outFile->Close();

    return 0;

}

