//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// File: MyPythia8Simul_main
//
// Purpose:  This is the main code for generating events with pythia 8, as well as
//           storing relevant output variables in Root Trees and histograms. Jets are
//           reconstructed with FastJet. The goal is to produce datasets with all the
//           relevant variables for doing theoretical predictions and sensitivity
//           studies.
//
//    Note: The main() method is used to generate events. It should not be modified
//          by users. General flags setting, histogram definitions and object
//          declarations should be made in the MyAnalysis::init(). The analysis to be
//          run in the loop must be written in void MyAnalysis::analyze(Event& event).
//          Note that the analysis here is only to calculate the physics quantities
//          to store in the Ntuple. Finally, the Pythia settings needed for a specific
//          production are set in MyPythiaSimul.cmnd.
//
//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


//*************************************************************************************
// Include headers
//*************************************************************************************

#include "MyPythia8Simul.h"


using namespace Pythia8;


//*************************************************************************************






//************************************************************************************
// void Usage(const char* exename)
//
// Function to be called giving the list of all flags and key-value pairs defined. 
// Options available are:
//
//      <root_output>    = [your choice of output name] (no need to add .root, this is
//                                                  done in the code)
//
//      <hepmc_output>   = [your choice of hepmc name] (no need to add .dat, this is                                         
//                                                  done in the code)
//  
//************************************************************************************
void Usage(const char* exename) 
{
  cout << "Usage : MyPythia8Simul <inputfile.cmnd> -outroot <root_output> -outhepmc <hepmc_output>" << endl;
  cout << "Look at MyPythia8Simul.cc for valid <key> values." << endl;
}

//*************************************************************************************






//*************************************************************************************
// Initialization Code
//*************************************************************************************
void MyAnalysis::init()
{


  // Initialize counters and other global variables
  // ----------------------------------------------

  // Note: These must be define in MyPythiaSimul.h to be in-scope for all functions


  // Debug flag
  // ..........

  debug = false;


  // Number of events
  // ................

  nEvt = 0;

  // Book Event-based Histograms
  // ---------------------------


  // Book Ntuples
  // ------------

  tree = new TTree("ParticleTree","Particle Data");

  tree->Branch("event_weights",&event_weights);

  tree->Branch("top_pt",&top_pt);
  tree->Branch("top_eta",&top_eta);
  tree->Branch("top_phi",&top_phi);
  tree->Branch("top_E",&top_E);

  tree->Branch("neutrino_pt",&neutrino_pt);
  tree->Branch("neutrino_eta",&neutrino_eta);
  tree->Branch("neutrino_phi",&neutrino_phi);
  tree->Branch("neutrino_E",&neutrino_E);
  tree->Branch("neutrino_PdgId",&neutrino_PdgId);

  tree->Branch("muon_bare_pt",&muon_bare_pt);
  tree->Branch("muon_bare_eta",&muon_bare_eta);
  tree->Branch("muon_bare_phi",&muon_bare_phi);
  tree->Branch("muon_bare_E",&muon_bare_E);
  tree->Branch("muon_bare_charge",&muon_bare_charge);

  tree->Branch("muon_dress_pt",&muon_dress_pt);
  tree->Branch("muon_dress_eta",&muon_dress_eta);
  tree->Branch("muon_dress_phi",&muon_dress_phi);
  tree->Branch("muon_dress_E",&muon_dress_E);
  tree->Branch("muon_dress_charge",&muon_dress_charge);

  tree->Branch("muon_born_pt",&muon_born_pt);
  tree->Branch("muon_born_eta",&muon_born_eta);
  tree->Branch("muon_born_phi",&muon_born_phi);
  tree->Branch("muon_born_E",&muon_born_E);
  tree->Branch("muon_born_charge",&muon_born_charge);

  tree->Branch("electron_bare_pt",&electron_bare_pt);
  tree->Branch("electron_bare_eta",&electron_bare_eta);
  tree->Branch("electron_bare_phi",&electron_bare_phi);
  tree->Branch("electron_bare_E",&electron_bare_E);
  tree->Branch("electron_bare_charge",&electron_bare_charge);

  tree->Branch("electron_dress_pt",&electron_dress_pt);
  tree->Branch("electron_dress_eta",&electron_dress_eta);
  tree->Branch("electron_dress_phi",&electron_dress_phi);
  tree->Branch("electron_dress_E",&electron_dress_E);
  tree->Branch("electron_dress_charge",&electron_dress_charge);

  tree->Branch("electron_born_pt",&electron_born_pt);
  tree->Branch("electron_born_eta",&electron_born_eta);
  tree->Branch("electron_born_phi",&electron_born_phi);
  tree->Branch("electron_born_E",&electron_born_E);
  tree->Branch("electron_born_charge",&electron_born_charge);

  tree->Branch("boson_pt",&boson_pt);
  tree->Branch("boson_eta",&boson_eta);
  tree->Branch("boson_phi",&boson_phi);
  tree->Branch("boson_E",&boson_E);
  tree->Branch("boson_ID",&boson_ID);

  tree->Branch("lightjet_bare_pt",&lightjet_bare_pt);
  tree->Branch("lightjet_bare_eta",&lightjet_bare_eta);
  tree->Branch("lightjet_bare_phi",&lightjet_bare_phi);
  tree->Branch("lightjet_bare_E",&lightjet_bare_E);
  tree->Branch("lightjet_bare_nPart",&lightjet_bare_nPart);

  tree->Branch("jet_dress_pt",&jet_dress_pt);
  tree->Branch("jet_dress_eta",&jet_dress_eta);
  tree->Branch("jet_dress_phi",&jet_dress_phi);
  tree->Branch("jet_dress_E",&jet_dress_E);
  tree->Branch("jet_dress_nPart",&jet_dress_nPart);

  tree->Branch("bjet_bare_pt",&bjet_bare_pt);
  tree->Branch("bjet_bare_eta",&bjet_bare_eta);
  tree->Branch("bjet_bare_phi",&bjet_bare_phi);
  tree->Branch("bjet_bare_E",&bjet_bare_E);
  tree->Branch("bjet_bare_nPart",&bjet_bare_nPart);

  tree->Branch("jet_born_pt",&jet_born_pt);
  tree->Branch("jet_born_eta",&jet_born_eta);
  tree->Branch("jet_born_phi",&jet_born_phi);
  tree->Branch("jet_born_E",&jet_born_E);
  tree->Branch("jet_born_nPart",&jet_born_nPart);

  tree->Branch("largeRjet_bare_pt", &largeRjet_bare_pt);
  tree->Branch("largeRjet_bare_eta",&largeRjet_bare_eta);
  tree->Branch("largeRjet_bare_phi",&largeRjet_bare_phi);
  tree->Branch("largeRjet_bare_E",  &largeRjet_bare_E);

  tree->Branch("largeRjet_dress_pt", &largeRjet_dress_pt);
  tree->Branch("largeRjet_dress_eta",&largeRjet_dress_eta);
  tree->Branch("largeRjet_dress_phi",&largeRjet_dress_phi);
  tree->Branch("largeRjet_dress_E",  &largeRjet_dress_E);

  tree->Branch("largeRjet_born_pt", &largeRjet_born_pt);
  tree->Branch("largeRjet_born_eta",&largeRjet_born_eta);
  tree->Branch("largeRjet_born_phi",&largeRjet_born_phi);
  tree->Branch("largeRjet_born_E",  &largeRjet_born_E);

  tree->Branch("lightpartonjet_pt",&lightpartonjet_pt);
  tree->Branch("lightpartonjet_eta",&lightpartonjet_eta);
  tree->Branch("lightpartonjet_phi",&lightpartonjet_phi);
  tree->Branch("lightpartonjet_E",&lightpartonjet_E);

  tree->Branch("bpartonjet_pt",&bpartonjet_pt);
  tree->Branch("bpartonjet_eta",&bpartonjet_eta);
  tree->Branch("bpartonjet_phi",&bpartonjet_phi);
  tree->Branch("bpartonjet_E",&bpartonjet_E);

  if(BareKtSplittingScales)
  {
    tree->Branch("BarekTSplittingScale1_R04",&BarekTSplittingScale1_R04);
    tree->Branch("BarekTSplittingScale2_R04",&BarekTSplittingScale2_R04);
    tree->Branch("BarekTSplittingScale3_R04",&BarekTSplittingScale3_R04);
    tree->Branch("BarekTSplittingScale1_R10",&BarekTSplittingScale1_R10);
    tree->Branch("BarekTSplittingScale2_R10",&BarekTSplittingScale2_R10);
    tree->Branch("BarekTSplittingScale3_R10",&BarekTSplittingScale3_R10);
  }

  if(DressKtSplittingScales)
  {
    tree->Branch("DresskTSplittingScale1_R04",&DresskTSplittingScale1_R04);
    tree->Branch("DresskTSplittingScale2_R04",&DresskTSplittingScale2_R04);
    tree->Branch("DresskTSplittingScale3_R04",&DresskTSplittingScale3_R04);
    tree->Branch("DresskTSplittingScale1_R10",&DresskTSplittingScale1_R10);
    tree->Branch("DresskTSplittingScale2_R10",&DresskTSplittingScale2_R10);
    tree->Branch("DresskTSplittingScale3_R10",&DresskTSplittingScale3_R10);
  }

  if(BornKtSplittingScales)
  {
    tree->Branch("BornkTSplittingScale1_R04",&BornkTSplittingScale1_R04);
    tree->Branch("BornkTSplittingScale2_R04",&BornkTSplittingScale2_R04);
    tree->Branch("BornkTSplittingScale3_R04",&BornkTSplittingScale3_R04);
    tree->Branch("BornkTSplittingScale1_R10",&BornkTSplittingScale1_R10);
    tree->Branch("BornkTSplittingScale2_R10",&BornkTSplittingScale2_R10);
    tree->Branch("BornkTSplittingScale3_R10",&BornkTSplittingScale3_R10);
  }

  tree->Branch("nTop",&nTop);
  tree->Branch("nNeutrino",&nNeutrino);
  tree->Branch("nMuonBare",&nMuonBare);
  tree->Branch("nElectronBare",&nElectronBare);
  tree->Branch("nMuonDress",&nMuonDress);
  tree->Branch("nElectronDress",&nElectronDress);
  tree->Branch("nMuonBorn",&nMuonBorn);
  tree->Branch("nElectronBorn",&nElectronBorn);
  tree->Branch("nLightjetBare",&nLightjetBare);
  tree->Branch("nJetDress",&nJetDress);
  tree->Branch("nBjetBare",&nBjetBare);
  tree->Branch("nJetBorn",&nJetBorn);
  tree->Branch("nLargeRjetBare",&nLargeRjetBare);
  tree->Branch("nLargeRjetdress",&nLargeRjetDress);
  tree->Branch("nLargeRjetBorn",&nLargeRjetBorn);
  tree->Branch("nLightpartonjet",&nLightpartonjet);
  tree->Branch("nBpartonjet",&nBpartonjet);
  tree->Branch("nBoson",&nBoson);
  tree->Branch("Met",&Met);
  tree->Branch("Met_phi",&Met_phi);

  tree->Branch("glob_TransvSphericity",&glob_TransSpher);
  tree->Branch("glob_TransvThrustMajor",&glob_TransThrustMaj);
  tree->Branch("glob_TransvThrustMinor",&glob_TransThrustMin);
  tree->Branch("glob_TransvThrustMajorWithResidue",&glob_TransThrustMajRes);
  tree->Branch("glob_TransvThrustMinorWithResidue",&glob_TransThrustMinRes);
  tree->Branch("glob_TransvThrustMajorWithSuppress",&glob_TransThrustMajSup);
  tree->Branch("glob_TransvThrustMinorWithSuppress",&glob_TransThrustMinSup);
  tree->Branch("glob_SumMassWithResidue",&glob_SumMassRes);
  tree->Branch("glob_HeavyMassWithResidue",&glob_HeavyMassRes);
  tree->Branch("glob_SumMassWithSuppress",&glob_SumMassSup);
  tree->Branch("glob_HeavyMassWithSuppress",&glob_HeavyMassSup);
  tree->Branch("glob_TotalBroadeningsWithResidue",&glob_TotBroadRes);
  tree->Branch("glob_WideBroadeningsWithResidue",&glob_WideBroadRes);
  tree->Branch("glob_TotalBroadeningsWithSuppress",&glob_TotBroadSup);
  tree->Branch("glob_WideBroadeningsWithSuppress",&glob_WideBroadSup);
  tree->Branch("glob_SuperSpherocity",&glob_SuperSphero);

  // reco branches

  tree->Branch("muon_reco_pt",&muon_reco_pt);
  tree->Branch("muon_reco_eta",&muon_reco_eta);
  tree->Branch("muon_reco_phi",&muon_reco_phi);
  tree->Branch("muon_reco_E",&muon_reco_E);
  tree->Branch("muon_reco_charge",&muon_reco_charge);

  tree->Branch("electron_reco_pt",&electron_reco_pt);
  tree->Branch("electron_reco_eta",&electron_reco_eta);
  tree->Branch("electron_reco_phi",&electron_reco_phi);
  tree->Branch("electron_reco_E",&electron_reco_E);
  tree->Branch("electron_reco_charge",&electron_reco_charge);

  tree->Branch("jet_reco_pt",&jet_reco_pt);
  tree->Branch("jet_reco_eta",&jet_reco_eta);
  tree->Branch("jet_reco_phi",&jet_reco_phi);
  tree->Branch("jet_reco_E",&jet_reco_E);

  tree->Branch("nMuonReco",&nMuonReco);
  tree->Branch("nElectronReco",&nElectronReco);
  tree->Branch("nJetReco",&nJetReco);
  tree->Branch("RecoMet",&RecoMet);
  tree->Branch("RecoMet_phi",&RecoMet_phi);

}

//*************************************************************************************






//*************************************************************************************
// Analysis Code
//*************************************************************************************
void MyAnalysis::analyze(Event& event, Event& partonevent, std::vector<double> EventWeights)
{

  // Declare an Analysis Utilities class object
  // ------------------------------------------

  // Note: To be able to access the functions define there

  ANA_utils myUtils;


  // Fill truth particle and jets information
  // ----------------------------------------

  // Set pointers
  // ............

  // Note: In each case, we first need to set a pointer to the vector of TruthPart containing the relevant particles,
  //       and then we call the function using the pointer.

  p_Top_Coll = &Top_Coll;
  p_Vecboson_Coll = &Vecboson_Coll;
  p_PromptLeptonBare_Coll = &PromptLeptonBare_Coll;
  p_LeptonConversion_Coll = &LeptonConversion_Coll;
  p_LeptonDress_Coll = &LeptonDress_Coll;
  p_LeptonBorn_Coll = &LeptonBorn_Coll;
  p_FSRPhoton_Coll = &FSRPhoton_Coll;
  p_DressPhoton_Coll = &DressPhoton_Coll;
  p_Neutrino_Coll = &Neutrino_Coll;
  p_TruthBareSmallRJets_Coll = &TruthBareSmallRJets_Coll;
  p_TruthDressSmallRJets_Coll = &TruthDressSmallRJets_Coll;
  p_TruthBornSmallRJets_Coll = &TruthBornSmallRJets_Coll;
  p_TruthBareLargeRJets_Coll = &TruthBareLargeRJets_Coll;
  p_TruthDressLargeRJets_Coll = &TruthDressLargeRJets_Coll;
  p_TruthBornLargeRJets_Coll = &TruthBornLargeRJets_Coll;
  p_PartonJets_Coll = &PartonJets_Coll;           // Small-R parton jets
  p_BareKtSplittingScale1_R04 = &BareKtSplittingScale1_R04;
  p_BareKtSplittingScale2_R04 = &BareKtSplittingScale2_R04;
  p_BareKtSplittingScale3_R04 = &BareKtSplittingScale3_R04;
  p_BareKtSplittingScale1_R10 = &BareKtSplittingScale1_R10;
  p_BareKtSplittingScale2_R10 = &BareKtSplittingScale2_R10;
  p_BareKtSplittingScale3_R10 = &BareKtSplittingScale3_R10;
  p_DressKtSplittingScale1_R04 = &DressKtSplittingScale1_R04;
  p_DressKtSplittingScale2_R04 = &DressKtSplittingScale2_R04;
  p_DressKtSplittingScale3_R04 = &DressKtSplittingScale3_R04;
  p_DressKtSplittingScale1_R10 = &DressKtSplittingScale1_R10;
  p_DressKtSplittingScale2_R10 = &DressKtSplittingScale2_R10;
  p_DressKtSplittingScale3_R10 = &DressKtSplittingScale3_R10;
  p_BornKtSplittingScale1_R04 = &BornKtSplittingScale1_R04;
  p_BornKtSplittingScale2_R04 = &BornKtSplittingScale2_R04;
  p_BornKtSplittingScale3_R04 = &BornKtSplittingScale3_R04;
  p_BornKtSplittingScale1_R10 = &BornKtSplittingScale1_R10;
  p_BornKtSplittingScale2_R10 = &BornKtSplittingScale2_R10;
  p_BornKtSplittingScale3_R10 = &BornKtSplittingScale3_R10;

  
  // Get Tops
  // ........

  myUtils.Get_Tops(event, p_Top_Coll);

  
  // Get Vector bosons
  // .................

  myUtils.Get_VectorBosons(event, p_Vecboson_Coll);


  // Bare, Dressed, and Born leptons
  // ...............................

  // Note: Need to find the indices of the vector bosons found above. Don't call the function if none are found.

  std::vector<int> vecbosindex;
  for (int vb_i = 0; vb_i < Vecboson_Coll.size(); vb_i++)
  {
    vecbosindex.push_back( (Vecboson_Coll[vb_i]).Index() );
  }

  if (vecbosindex.size() > 0) 
  {
    myUtils.Get_BarePromptLepton(event, vecbosindex, p_PromptLeptonBare_Coll, p_LeptonConversion_Coll, p_FSRPhoton_Coll, p_Neutrino_Coll);
    myUtils.Get_BornPromptLepton(event, vecbosindex, p_LeptonBorn_Coll);
  }

  if (PromptLeptonBare_Coll.size()!=0) myUtils.Get_DressPromptLepton(PromptLeptonBare_Coll,FSRPhoton_Coll, p_LeptonDress_Coll, p_DressPhoton_Coll);

				   

  // True Jets
  // .........

  // Note 1: A list of stable particles not to be clustered in jets must first be defined for truth jets.

  // Note 2: A different function is called for final state particle jets and for pre-hadronization parton jets.

  // Note 3: The Kt Splitting scale flags are defined in the header file.

  // Note 4: For bare jets, we only exclude the bare prompt leptons. For dressed jet, we also exlcude dressing FSR photons. For Born jets,
  //         we exclude prompt photon, all fsr photons, and conversion leptons. In principle conversion leptons should be removed from
  //         dresses jets, but they are not in ATLAS, so they are left here too. 


  // Remove Prompt leptons from any jet definition
  std::vector<int> skippart_born;
  std::vector<int> skippart_bare;
  std::vector<int> skippart_dress;
  for (int i_part = 0; i_part < PromptLeptonBare_Coll.size(); i_part++) 
  {
    skippart_born.push_back((PromptLeptonBare_Coll[i_part]).Index());
    skippart_bare.push_back((PromptLeptonBare_Coll[i_part]).Index());
    skippart_dress.push_back((PromptLeptonBare_Coll[i_part]).Index());
  }

  
  // Particle bare small-R jets
  float jetcut = 30.; // jet pT cut
  myUtils.TrueJetsReco(event, skippart_bare, p_TruthBareSmallRJets_Coll, jetcut, BareKtSplittingScales, p_BareKtSplittingScale1_R04, p_BareKtSplittingScale2_R04, p_BareKtSplittingScale3_R04, 0.4);

  
  // Also remove dressing FSR photons from dressed jet definition
  for (int i_dress = 0; i_dress < DressPhoton_Coll.size(); i_dress++)
  {
    skippart_dress.push_back((DressPhoton_Coll[i_dress]).Index());
  }

  
    // Particle dress small-R jets
  myUtils.TrueJetsReco(event, skippart_dress, p_TruthDressSmallRJets_Coll, jetcut, DressKtSplittingScales, p_DressKtSplittingScale1_R04, p_DressKtSplittingScale2_R04, p_DressKtSplittingScale3_R04, 0.4);


  
  // Remove any photons and conversion leptons for Born jets
  for (int i_fsr = 0; i_fsr < FSRPhoton_Coll.size(); i_fsr++)
  {
    skippart_born.push_back((FSRPhoton_Coll[i_fsr]).Index());
  }

  for (int i_part2 = 0; i_part2 < LeptonConversion_Coll.size(); i_part2++) 
  {
    skippart_born.push_back((LeptonConversion_Coll[i_part2]).Index());
  }


  // Particle born small-R jets
  myUtils.TrueJetsReco(event, skippart_born, p_TruthBornSmallRJets_Coll, jetcut, BornKtSplittingScales, p_BornKtSplittingScale1_R04, p_BornKtSplittingScale2_R04, p_BornKtSplittingScale3_R04, 0.4);


  // Particle bare large-R jets
  myUtils.TrueJetsReco(event, skippart_bare, p_TruthBareLargeRJets_Coll, jetcut, BareKtSplittingScales, p_BareKtSplittingScale1_R10, p_BareKtSplittingScale2_R10, p_BareKtSplittingScale3_R10, 1.0);
  
  // Particle dress large-R jets
  myUtils.TrueJetsReco(event, skippart_dress, p_TruthDressLargeRJets_Coll, jetcut, DressKtSplittingScales, p_DressKtSplittingScale1_R10, p_DressKtSplittingScale2_R10, p_DressKtSplittingScale3_R10, 1.0);
  
  // Particle born large-R jets
  myUtils.TrueJetsReco(event, skippart_born, p_TruthBornLargeRJets_Coll, jetcut, BornKtSplittingScales, p_BornKtSplittingScale1_R10, p_BornKtSplittingScale2_R10, p_BornKtSplittingScale3_R10, 1.0);

  // Parton small-R jets
  myUtils.PartonJetsReco(event, partonevent, p_PartonJets_Coll, jetcut);

  
  // Fill ntuples and histograms
  // ---------------------------

  // Event weights
  // .............

  event_weights = EventWeights;

  // W and Z
  // .......

  nBoson = p_Vecboson_Coll->size();
  if (nBoson != 0)
  {
    for (size_t i = 0; i < p_Vecboson_Coll->size(); i++)
    {
      boson_pt.push_back((Vecboson_Coll[i]).Pt());
      boson_eta.push_back((Vecboson_Coll[i]).Eta());
      double i_phi = (Vecboson_Coll[i]).Phi();
      if (i_phi < 0.) i_phi = (Vecboson_Coll[i]).Phi() + 6.283185307;
      boson_phi.push_back(i_phi);
      boson_E.push_back((Vecboson_Coll[i]).E());
      boson_ID.push_back((Vecboson_Coll[i]).Pdgid());
    }
  }



  // Top quarks
  // ..........

  nTop = p_Top_Coll->size();
  if (nTop != 0)
  {
    for (size_t i = 0; i < p_Top_Coll->size(); i++)
    {
      top_pt.push_back((Top_Coll[i]).Pt());
      top_eta.push_back((Top_Coll[i]).Eta());
      double i_phi = (Top_Coll[i]).Phi();
      if (i_phi < 0.) i_phi = (Top_Coll[i]).Phi() + 6.283185307;	      
      top_phi.push_back(i_phi);
      top_E.push_back((Top_Coll[i]).E());
    }
  }


  // Neutrinos and Met
  // .................

  nNeutrino = p_Neutrino_Coll->size();
  if (nNeutrino != 0)
  {
    for (size_t i = 0; i < p_Neutrino_Coll->size(); i++)
    {
      neutrino_pt.push_back((Neutrino_Coll[i]).Pt());
      neutrino_eta.push_back((Neutrino_Coll[i]).Eta());
      double i_phi = (Neutrino_Coll[i]).Phi();
      if (i_phi < 0.) i_phi = (Neutrino_Coll[i]).Phi() + 6.283185307;	      
      neutrino_phi.push_back(i_phi);
      neutrino_E.push_back((Neutrino_Coll[i]).E());
      neutrino_PdgId.push_back((Neutrino_Coll[i]).Pdgid());
    }
  }

  float sqsum;
  float sum_y=0;
  float sum_x=0;

  float RecoSqSum;
  float RecoSum_x=0;
  float RecoSum_y=0;

  for (auto i : Neutrino_Coll)
  //for (std::vector<double>::iterator i : Neutrino_Coll)
  {
    sum_y += i.Py();
    sum_x += i.Px();
    RecoSum_y += i.Py();
    RecoSum_x += i.Px();
  }

  sqsum = pow(sum_x, 2.0) + pow(sum_y, 2.0);
  Met = sqrt(sqsum);
  Met_phi = atan2(sum_y,sum_x);
  if (Met_phi < 0.) Met_phi = Met_phi + 6.283185307;

  




  // light and b-jets for particle and parton jets
  // .............................................

    // Note: For b-jets, we use the b-quark tag for parton jets, and the b-hadron tag for particle jets.

    // Note: While we keep light and b-jets separate for bare jets, for Born jets we keep them in the same collection

  
  // Bare Small-R light and b-jets for particle jets

  nLightjetBare  = 0;
  nBjetBare      = 0;
  if (p_TruthBareSmallRJets_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_TruthBareSmallRJets_Coll->size(); i++)
    {
      if ((TruthBareSmallRJets_Coll[i]).BHTag())
      {
        bjet_bare_pt.push_back((TruthBareSmallRJets_Coll[i]).Pt());
        bjet_bare_eta.push_back((TruthBareSmallRJets_Coll[i]).Eta());
        bjet_bare_phi.push_back((TruthBareSmallRJets_Coll[i]).Phi());
        bjet_bare_E.push_back((TruthBareSmallRJets_Coll[i]).E());
        bjet_bare_nPart.push_back((TruthBareSmallRJets_Coll[i]).Npart());
        nBjetBare += 1;
      }
      else
      {
        lightjet_bare_pt.push_back((TruthBareSmallRJets_Coll[i]).Pt());
        lightjet_bare_eta.push_back((TruthBareSmallRJets_Coll[i]).Eta());
        lightjet_bare_phi.push_back((TruthBareSmallRJets_Coll[i]).Phi());
        lightjet_bare_E.push_back((TruthBareSmallRJets_Coll[i]).E());
        lightjet_bare_nPart.push_back((TruthBareSmallRJets_Coll[i]).Npart());
        nLightjetBare += 1;
      }
    }
  }

  // Bare large-R jets
  nLargeRjetBare = 0;
  if (p_TruthBareLargeRJets_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_TruthBareLargeRJets_Coll->size(); i++)
    {
      largeRjet_bare_pt.push_back((TruthBareLargeRJets_Coll[i]).Pt());
      largeRjet_bare_eta.push_back((TruthBareLargeRJets_Coll[i]).Eta());
      largeRjet_bare_phi.push_back((TruthBareLargeRJets_Coll[i]).Phi());
      largeRjet_bare_E.push_back((TruthBareLargeRJets_Coll[i]).E());
      nLargeRjetBare += 1;
    }
  }

  
  // Dress small-R jets (include both light and B-jets)
  nJetDress = 0;
  if (p_TruthDressSmallRJets_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_TruthDressSmallRJets_Coll->size(); i++)
      {
      jet_dress_pt.push_back((TruthDressSmallRJets_Coll[i]).Pt());
      jet_dress_eta.push_back((TruthDressSmallRJets_Coll[i]).Eta());
      jet_dress_phi.push_back((TruthDressSmallRJets_Coll[i]).Phi());
      jet_dress_E.push_back((TruthDressSmallRJets_Coll[i]).E());
      jet_dress_nPart.push_back((TruthDressSmallRJets_Coll[i]).Npart());
      nJetDress += 1;
      }
  }

  
  // Dress large-R jets
  nLargeRjetDress = 0;
  if (p_TruthDressLargeRJets_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_TruthDressLargeRJets_Coll->size(); i++)
    {
      largeRjet_dress_pt.push_back((TruthDressLargeRJets_Coll[i]).Pt());
      largeRjet_dress_eta.push_back((TruthDressLargeRJets_Coll[i]).Eta());
      largeRjet_dress_phi.push_back((TruthDressLargeRJets_Coll[i]).Phi());
      largeRjet_dress_E.push_back((TruthDressLargeRJets_Coll[i]).E());
      nLargeRjetDress += 1;
    }
  }

  

  // Born small-R jets (include both light and B-jets)
  nJetBorn = 0;
  if (p_TruthBornSmallRJets_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_TruthBornSmallRJets_Coll->size(); i++)
    {
	    jet_born_pt.push_back((TruthBornSmallRJets_Coll[i]).Pt());
	    jet_born_eta.push_back((TruthBornSmallRJets_Coll[i]).Eta());
	    jet_born_phi.push_back((TruthBornSmallRJets_Coll[i]).Phi());
	    jet_born_E.push_back((TruthBornSmallRJets_Coll[i]).E());
	    jet_born_nPart.push_back((TruthBornSmallRJets_Coll[i]).Npart());
	    nJetBorn += 1;
    }
  }

  
  // Born large-R jets
  nLargeRjetBorn = 0;
  if (p_TruthBornLargeRJets_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_TruthBornLargeRJets_Coll->size(); i++)
    {
      largeRjet_born_pt.push_back((TruthBornLargeRJets_Coll[i]).Pt());
      largeRjet_born_eta.push_back((TruthBornLargeRJets_Coll[i]).Eta());
      largeRjet_born_phi.push_back((TruthBornLargeRJets_Coll[i]).Phi());
      largeRjet_born_E.push_back((TruthBornLargeRJets_Coll[i]).E());
      nLargeRjetBorn += 1;
    }
  }

  

  // Small-R parton light and b-jets  

  nLightpartonjet = 0;
  nBpartonjet = 0;
  if (p_PartonJets_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_PartonJets_Coll->size(); i++)
    {
      if ((PartonJets_Coll[i]).BQTag())
      {
        bpartonjet_pt.push_back((PartonJets_Coll[i]).Pt());
        bpartonjet_eta.push_back((PartonJets_Coll[i]).Eta());
        bpartonjet_phi.push_back((PartonJets_Coll[i]).Phi());
        bpartonjet_E.push_back((PartonJets_Coll[i]).E());
        nBpartonjet += 1;
      }
      else
      {
        lightpartonjet_pt.push_back((PartonJets_Coll[i]).Pt());
        lightpartonjet_eta.push_back((PartonJets_Coll[i]).Eta());
        lightpartonjet_phi.push_back((PartonJets_Coll[i]).Phi());
        lightpartonjet_E.push_back((PartonJets_Coll[i]).E());
        nLightpartonjet += 1;
      }
    }
  }

  // Reco jets
  // .........

    // Note 1: The momentum of each jet is shifted and smeared following 
    //         ATLAS calibration and resolution functions. Angles are smeared too 
    //         but the effect is small because the angular resolution effects are
    //         proportional to the detector fined granularity (multiple scattering
    //         have little effects on jets). We assume that there is no angular shifts
    //         (neglect inter-calorimeter effects) i.e. that we smear eta and phi with 
    //         a Gaussian each centered on 0. In principle a calorimeter cell  
    //         measurement is an energy measurement, so we should be smearing the 
    //         energy and the pseudo-rapidity and then calculate the transverse 
    //         momentum from this smeared energy with pT = E/cosh(eta). However, 
    //         experiments precisely and carefully measure the jet transverse 
    //         momentum resolution expressed as: sigma/pt = N/pt circ+ S/sqrt(pt) circ+ C
    //         where N is the noise term, S the stochastic term, C the constant term
    //         including non-scaling effects like material in front of the calorimeter,
    //         and "circ+" means that the quadratic sum is used. We therefore use this 
    //         smearing using however only the resolution measurement results obtained
    //         for central R=0.4 EM+JES jets (0<|eta|<0.8) for simplicity.  

    // Note 2: Smearing resolution factors are obtained from the ATLAS 8 TeV Jet 
    //         performance paper: https://arxiv.org/pdf/1910.04482.pdf:
    //
    //           eta, phi: approximate quadratic fit to fig 2. a (eta), and b (phi)
    //           pt: N=3.33 GeV, S=0.71 GeV^0.5 and C=0.03

    // Note 3: No efficiency factor is considered because we'll deal only with jets Pt?30 GeV
    //         which are almost fully efficient. 

    // Note 4: For the Reco Met, we start by adding the true jet Px and Py. That will balance
    //         out part of the neutrino, but after calculating all the reco quantities, we 
    //         subtract from the sum, the reco Px and Py. That will restore the Met. If there
    //         no resolution effect on the jet, the Met will be the same as the true, plus the
    //         particles that are not detected (efficiency, acceptance). For example, if a jet
    //         is lost, the truee jet would have been added to the Reco Met, but the reco jet 
    //         would not be subtracted, so that jet would contribute to Reco Met. Note that only
    //         the fiducial part of the acceptance is not removed from Reco Met, which means that
    //         if a jet is not reconstructed because it is too low in Pt, it neverthess leaves
    //         measurable energy in the detector, which is therefore not Met. Resolution is 
    //         properly accounted for this way. 

    // Note 5: Reco jets, because of migration, are not anymore sorted from the highest pt to the
    //         lowest. To this end, reco jets are temporarily stored in a vector TLorentzVector, 
    //         which are then sorted in decreasing pt order, before each quantities get pushed
    //         in their respective vectors. At the end, vectors of reco energy, pt, eta, and phi
    //         will have matching indices sorted in decending pt.       

  vector<TLorentzVector> tempJetRecoContainer;

  nJetReco  = 0;
  for (int i_tjet = 0; i_tjet < lightjet_bare_E.size(); i_tjet++)
  {

    // Fetch truth information
    double JetTrueE = lightjet_bare_E[i_tjet];
    double JetTrueEta = lightjet_bare_eta[i_tjet];
    double JetTruePhi = lightjet_bare_phi[i_tjet];
    double JetTruePt = lightjet_bare_pt[i_tjet];

    TLorentzVector trueJet;
    trueJet.SetPtEtaPhiE(JetTruePt,JetTrueEta,JetTruePhi,JetTrueE);
    double truePx = trueJet.Px();
    double truePy = trueJet.Py();

    // Add truth particle to the Reco Met (reco will be remove later)
    RecoSum_y += truePy;
    RecoSum_x += truePx;

    // Calculate pt-dependent resolution and calibration parameters
    double eta_resol = 0.000000056*JetTruePt*JetTruePt - 0.000112*JetTruePt + 0.06;
    double phi_resol = 0.000000084*JetTruePt*JetTruePt - 0.000168*JetTruePt + 0.09;
    double pt_resol = JetTruePt*sqrt(11.09/(JetTruePt*JetTruePt)+0.504/JetTruePt+0.0009);
    double pt_calib = JetTruePt*(0.00639*sqrt(JetTruePt - 20.) + 0.6);


    // Calculate detector distorted quantities
    double recoEta = gRandom->Gaus(JetTrueEta,eta_resol);
    double recoPhi = gRandom->Gaus(JetTruePhi,phi_resol);
    if (recoPhi < 0.) recoPhi += 6.283185307;
    else if (recoPhi > 6.283185307) recoPhi = recoPhi - 6.283185307;
    double recoPt  = gRandom->Gaus(pt_calib,pt_resol);
    double recoE = recoPt*cosh(recoEta);

    TLorentzVector recoJet;
    recoJet.SetPtEtaPhiE(recoPt,recoEta,recoPhi,recoE);
    double recoPx = recoJet.Px();
    double recoPy = recoJet.Py();

    // Remove non-fiducial jets
    if (fabs(recoEta) > 4.5) continue;

    // Calculate reco impact on Met
    RecoSum_y += (-1)*recoPy;
    RecoSum_x += (-1)*recoPx;
    
    // Don't store too low Pt jets
    if (recoPt<5.) continue;

    // Fill tempJetRecoContainer
    tempJetRecoContainer.push_back(recoJet);

    if (recoPt>jetcut) nJetReco++;
  }
  

  // Sort reco jets in descending pt
  std::sort(tempJetRecoContainer.begin(), tempJetRecoContainer.end(), 
    [](TLorentzVector x, TLorentzVector y) { return x.Pt() > y.Pt(); });


  // Fill reco jet quantities

  for (int i_j = 0; i_j < tempJetRecoContainer.size(); i_j++)
  {
    jet_reco_E.push_back( (tempJetRecoContainer[i_j]).E() );
    jet_reco_pt.push_back( (tempJetRecoContainer[i_j]).Pt() );
    jet_reco_eta.push_back( (tempJetRecoContainer[i_j]).Eta() );
    jet_reco_phi.push_back( (tempJetRecoContainer[i_j]).Phi() );      
  }




  
  // kT Splitting scales

  // Bare
  int nSmallRjetBare = nLightjetBare + nBjetBare;
  if(p_BareKtSplittingScale1_R04->size() != 0)
  {
    for (size_t i = 0; i < p_BareKtSplittingScale1_R04->size(); i++)
    {
      BarekTSplittingScale1_R04.push_back(BareKtSplittingScale1_R04[i]);
    }
  }
  if(p_BareKtSplittingScale2_R04->size() != 0)
  {
    for (size_t i = 0; i < p_BareKtSplittingScale2_R04->size(); i++)
    {
      BarekTSplittingScale2_R04.push_back(BareKtSplittingScale2_R04[i]);
    }
  }
  if(p_BareKtSplittingScale3_R04->size() != 0)
  {
    for (size_t i = 0; i < p_BareKtSplittingScale3_R04->size(); i++)
    {
      BarekTSplittingScale3_R04.push_back(BareKtSplittingScale3_R04[i]);
    }
  }
  
  if(p_BareKtSplittingScale1_R10->size() != 0)
  {
    for (size_t i = 0; i < p_BareKtSplittingScale1_R10->size(); i++)
    {
      BarekTSplittingScale1_R10.push_back(BareKtSplittingScale1_R10[i]);
    }
  }
  if(p_BareKtSplittingScale2_R10->size() != 0)
  {
    for (size_t i = 0; i < p_BareKtSplittingScale2_R10->size(); i++)
    {
      BarekTSplittingScale2_R10.push_back(BareKtSplittingScale2_R10[i]);
    }
  }

  if(p_BareKtSplittingScale3_R10->size() != 0)
  {
    for (size_t i = 0; i < p_BareKtSplittingScale3_R10->size(); i++)
    {
      BarekTSplittingScale3_R10.push_back(BareKtSplittingScale3_R10[i]);
    }
  }

  
  // Dress
  int nSmallRjetDress = nJetDress;
  if(p_DressKtSplittingScale1_R04->size() != 0)
  {
    for (size_t i = 0; i < p_DressKtSplittingScale1_R04->size(); i++)
    {
      DresskTSplittingScale1_R04.push_back(DressKtSplittingScale1_R04[i]);
    }
  }
  if(p_DressKtSplittingScale2_R04->size() != 0)
  {
    for (size_t i = 0; i < p_DressKtSplittingScale2_R04->size(); i++)
    {
      DresskTSplittingScale2_R04.push_back(DressKtSplittingScale2_R04[i]);
    }
  }
  if(p_DressKtSplittingScale3_R04->size() != 0)
  {
    for (size_t i = 0; i < p_DressKtSplittingScale3_R04->size(); i++)
    {
      DresskTSplittingScale3_R04.push_back(DressKtSplittingScale3_R04[i]);
    }
  }
  
  if(p_DressKtSplittingScale1_R10->size() != 0)
  {
    for (size_t i = 0; i < p_DressKtSplittingScale1_R10->size(); i++)
    {
      DresskTSplittingScale1_R10.push_back(DressKtSplittingScale1_R10[i]);
    }
  }
  if(p_DressKtSplittingScale2_R10->size() != 0)
  {
    for (size_t i = 0; i < p_DressKtSplittingScale2_R10->size(); i++)
    {
      DresskTSplittingScale2_R10.push_back(DressKtSplittingScale2_R10[i]);
    }
  }

  if(p_DressKtSplittingScale3_R10->size() != 0)
  {
    for (size_t i = 0; i < p_DressKtSplittingScale3_R10->size(); i++)
    {
      DresskTSplittingScale3_R10.push_back(DressKtSplittingScale3_R10[i]);
    }
  }

  
  // Born
  if(p_BornKtSplittingScale1_R04->size() != 0)
  {
    for (size_t i = 0; i < p_BornKtSplittingScale1_R04->size(); i++)
    {
      BornkTSplittingScale1_R04.push_back(BornKtSplittingScale1_R04[i]);
    }
  }
  
  if(p_BornKtSplittingScale2_R04->size() != 0)
  {
    for (size_t i = 0; i < p_BornKtSplittingScale2_R04->size(); i++)
    {
      BornkTSplittingScale2_R04.push_back(BornKtSplittingScale2_R04[i]);
    }
  }
  
  if(p_BornKtSplittingScale3_R04->size() != 0)
  {
    for (size_t i = 0; i < p_BornKtSplittingScale3_R04->size(); i++)
    {
      BornkTSplittingScale3_R04.push_back(BornKtSplittingScale3_R04[i]);
    }
  }

  if(p_BornKtSplittingScale1_R10->size() != 0)
  {
    for (size_t i = 0; i < p_BornKtSplittingScale1_R10->size(); i++)
    {
      BornkTSplittingScale1_R10.push_back(BornKtSplittingScale1_R10[i]);
    }
  }
  
  if(p_BornKtSplittingScale2_R10->size() != 0)
  {
    for (size_t i = 0; i < p_BornKtSplittingScale2_R10->size(); i++)
    {
      BornkTSplittingScale2_R10.push_back(BornKtSplittingScale2_R10[i]);
    }
  }
  
  if(p_BornKtSplittingScale3_R10->size() != 0)
  {
    for (size_t i = 0; i < p_BornKtSplittingScale3_R10->size(); i++)
    {
      BornkTSplittingScale3_R10.push_back(BornKtSplittingScale3_R10[i]);
    }
  }

    
  // Electrons and muons
  // ...................

  // Bare
  nElectronBare = 0;
  nMuonBare     = 0;
  if (p_PromptLeptonBare_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_PromptLeptonBare_Coll->size(); i++)
    {
      if ((PromptLeptonBare_Coll[i]).Pdgid() == 11 || (PromptLeptonBare_Coll[i]).Pdgid() == -11)
      {
        electron_bare_pt.push_back((PromptLeptonBare_Coll[i]).Pt());
        electron_bare_eta.push_back((PromptLeptonBare_Coll[i]).Eta());
        double i_phi = (PromptLeptonBare_Coll[i]).Phi();
        if (i_phi < 0.) i_phi = (PromptLeptonBare_Coll[i]).Phi() + 6.283185307;	      
        electron_bare_phi.push_back(i_phi);
        electron_bare_E.push_back((PromptLeptonBare_Coll[i]).E());
        electron_bare_charge.push_back((PromptLeptonBare_Coll[i]).Charge());
        nElectronBare += 1;
      }
      if ((PromptLeptonBare_Coll[i]).Pdgid() == 13 || (PromptLeptonBare_Coll[i]).Pdgid() == -13)
      {
        muon_bare_pt.push_back((PromptLeptonBare_Coll[i]).Pt());
        muon_bare_eta.push_back((PromptLeptonBare_Coll[i]).Eta());
        double i_phi = (PromptLeptonBare_Coll[i]).Phi();
        if (i_phi < 0.) i_phi = (PromptLeptonBare_Coll[i]).Phi() + 6.283185307;	      
        muon_bare_phi.push_back(i_phi);	      
        muon_bare_E.push_back((PromptLeptonBare_Coll[i]).E());
        muon_bare_charge.push_back((PromptLeptonBare_Coll[i]).Charge());
        nMuonBare += 1;
      }
    }
  }

  // Dress
  nElectronDress = 0;
  nMuonDress     = 0;
  if (p_LeptonDress_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_LeptonDress_Coll->size(); i++)
    {
      if ((LeptonDress_Coll[i]).Pdgid() == 11 || (LeptonDress_Coll[i]).Pdgid() == -11)
      {
        electron_dress_pt.push_back((LeptonDress_Coll[i]).Pt());
        electron_dress_eta.push_back((LeptonDress_Coll[i]).Eta());
        double i_phi = (LeptonDress_Coll[i]).Phi();
        if (i_phi < 0.) i_phi = (LeptonDress_Coll[i]).Phi() + 6.283185307;	      
        electron_dress_phi.push_back(i_phi);
        electron_dress_E.push_back((LeptonDress_Coll[i]).E());
        electron_dress_charge.push_back((LeptonDress_Coll[i]).Charge());
        nElectronDress += 1;
      }
      if ((LeptonDress_Coll[i]).Pdgid() == 13 || (LeptonDress_Coll[i]).Pdgid() == -13)
      {
        muon_dress_pt.push_back((LeptonDress_Coll[i]).Pt());
        muon_dress_eta.push_back((LeptonDress_Coll[i]).Eta());
        double i_phi = (LeptonDress_Coll[i]).Phi();
        if (i_phi < 0.) i_phi = (LeptonDress_Coll[i]).Phi() + 6.283185307;	      
        muon_dress_phi.push_back(i_phi);	      
        muon_dress_E.push_back((LeptonDress_Coll[i]).E());
        muon_dress_charge.push_back((LeptonDress_Coll[i]).Charge());
        nMuonDress += 1;
      }
    }
  }

  // Born
  nElectronBorn = 0;
  nMuonBorn = 0;
  if (p_LeptonBorn_Coll->size() != 0)
  {
    for (size_t i = 0; i < p_LeptonBorn_Coll->size(); i++)
    {
      if ((LeptonBorn_Coll[i]).Pdgid() == 11 || (LeptonBorn_Coll[i]).Pdgid() == -11)
      {
        electron_born_pt.push_back((LeptonBorn_Coll[i]).Pt());
        electron_born_eta.push_back((LeptonBorn_Coll[i]).Eta());
        double i_phi = (LeptonBorn_Coll[i]).Phi();
        if (i_phi < 0.) i_phi = (LeptonBorn_Coll[i]).Phi() + 6.283185307;	      
        electron_born_phi.push_back(i_phi);
        electron_born_E.push_back((LeptonBorn_Coll[i]).E());
        electron_born_charge.push_back((LeptonBorn_Coll[i]).Charge());
        nElectronBorn += 1;
      }
      if ((LeptonBorn_Coll[i]).Pdgid() == 13 || (LeptonBorn_Coll[i]).Pdgid() == -13)
      {
        muon_born_pt.push_back((LeptonBorn_Coll[i]).Pt());
        muon_born_eta.push_back((LeptonBorn_Coll[i]).Eta());
        double i_phi = (LeptonBorn_Coll[i]).Phi();
        if (i_phi < 0.) i_phi = (LeptonBorn_Coll[i]).Phi() + 6.283185307;	      
        muon_born_phi.push_back(i_phi);	      
        muon_born_E.push_back((LeptonBorn_Coll[i]).E());
        muon_born_charge.push_back((LeptonBorn_Coll[i]).Charge());
        nMuonBorn += 1;
      }
    }
  }



  // Reco electrons and muons
  // ........................

    // Note 1: No resolution smearing is applied to the angle eta and phi because
    //         these parameters are sufficiently precisely measured from fit at
    //         primary vertex. For the electrons, the resolution is applied to the 
    //         total energy, but varies as a function of the pT of the electron. This
    //         pT dependence is obtained from an exponential fit to the resolution
    //         measurement results published by ATLAS with 13 TeV 2015 data. For the 
    //         muons, it is the resolution of the total momentum that is measured (in 
    //         fact it is the resolution of the invariant mass of the dimuon system,
    //         which equal the total momentum resolution up to a factor of srqt(2)). 
    //         It depends on the transverse momentum of the muon. This pT dependence 
    //         is modeled from a linear fit to the ATLAS muon resolution measurement
    //         performed on 13 TeV data. A different fit is obtained for central 
    //         (barrel) and forward (end-cap) muons. 

    // Note 2: Both electrons and muons are assumed to be well calibrated.

    // Note 3: A probability of bremsstrahlung emission is measured for electrons with
    //         ATLAS data. This measurement results has been modeled by a special 
    //         corrected error function as a function of the fraction of energy 
    //         radiated the fraction of initial energy radiated is obtained from a  
    //         random number between 0 and 1, and the the probability for that raditation
    //         to happen is obtained from the model function. Another randome number is 
    //         used to decide if this radiation happens or not. If it does, 1-fBrem is
    //         applied to the reco electron energy to model this lost. 

    // Note 4: The efficiency for tight electrons and medium muons are modeled from 
    //         the measurement results respecively obtained from ATLAS data for these
    //         two particles. Muons are assumed to be constant in pT and depend only
    //         on eta (constant functions in different eta ranges). Electrons reco+id
    //         efficiency is depends on pT. This dependence is modeled from a Cauchy 
    //         cumulative function approximatively fitted to the ATLAS measurement
    //         results also used for the resolution and Bremsstrahlung models. Once the
    //         efficiency for a given leptons is known, a random number is selected and
    //         compared to this efficiency to decide if the lepton is kept or not. If it
    //         passes the test, it is pushed back in the reco vector, otherwise it is lost.

    // Note 5: Reco Met is calculated in the same way as it is for jets. One small exception, 
    //         and electron is not fiducial to the tracker, but still within the boundaries
    //         of the calo, this electron will be visible and will not be considered as Met.

    // Note 6: As for jets, electrons and muons might not be sorted in decreasing pt order
    //         after modeling detector effects. Even if the "disordering" is much smaller
    //         then for jets because resolution effects are much smaller, it is important
    //         to sort leptons properly. We cannot use the exact same method as for jets 
    //         however, because of the charge of the leptons that need to be stored as well
    //         and which is not part of a TLorentzVector. So all reco-level electrons (muons)
    //         are stored in a vector of pair consisting in a TLorentzVector as the first
    //         component, and a float, to hold the charge, as the second component of each
    //         pairs. The vector of pairs is then sorted based on the pt of the first
    //         component of the pair, before the assignment to the vectors of electrons
    //         (muons) quantities (E, pt, eta, phi, and charge) get properly assigned.

  vector< pair<TLorentzVector,float> > tempEleRecoContainer;
  vector< pair<TLorentzVector,float> > tempMuoRecoContainer;

  nElectronReco = 0;
  for (int i_tele = 0; i_tele < electron_bare_E.size(); i_tele++)
  {

    // Fetch truth information
    double EleTrueE = electron_bare_E[i_tele];
    double EleTrueEta = electron_bare_eta[i_tele];
    double EleTruePhi = electron_bare_phi[i_tele];
    double EleTruePt = electron_bare_pt[i_tele];
    float EleTrueChg = electron_bare_charge[i_tele];

    TLorentzVector trueEle;
    trueEle.SetPtEtaPhiE(EleTruePt,EleTrueEta,EleTruePhi,EleTrueE);
    double truePx = trueEle.Px();
    double truePy = trueEle.Py();

    // Add truth particle to the Reco Met (reco will be remove later)
    RecoSum_y += truePy;
    RecoSum_x += truePx;

    // Calculate pt-dependent resolution
    double E_resol = EleTrueE*0.4*exp((-0.75)*log(EleTruePt));

    // Calculate detector distortion
    double recoE = gRandom->Gaus(EleTrueE,E_resol);

    // Calculate Bremsstrahlung fraction
    double fBrem = gRandom->Rndm();
    double probBrem = 0.05*TMath::Gaus(fBrem,0.1,0.05) + 0.01;
    bool doBrem = false;
    double testBrem = gRandom->Rndm();
    
    if (testBrem < probBrem) doBrem = true;
    if (doBrem) recoE *= fBrem;


    // Calculate reco quantities
    double recoEta = EleTrueEta;
    double recoPhi = EleTruePhi;
    double recoPt = recoE/cosh(recoEta);
    
    TLorentzVector recoEle;
    recoEle.SetPtEtaPhiE(recoPt,recoEta,recoPhi,recoE);
    double recoPx = recoEle.Px();
    double recoPy = recoEle.Py();

    // Calculate efficiency and apply
    double EleEff = (1./TMath::Pi())*TMath::ATan( (recoPt+15.)/30. ) + 0.5;
    bool looseEle = false;
    
    double testEle = gRandom->Rndm();
    if (testEle > EleEff) looseEle = true;

    if (looseEle) continue;

    // Remove non-fiducial electrons
    if (fabs(recoEta) > 5.) continue;
    
    // Calculate reco impact on Met
    RecoSum_y += (-1)*recoPy;
    RecoSum_x += (-1)*recoPx;

    // Don't store too low Pt jets
    if (recoPt<5. || fabs(recoEta)>2.5) continue;

    // Charge mis-Id
    bool chargeFlip = false;
    float testFlip = gRandom->Rndm();
    float recoChg = EleTrueChg;
    if (testFlip > 0.98) chargeFlip = true;
    if (chargeFlip) recoChg = (-1.)*EleTrueChg;


    // Fill tempEleRecoContainer
    pair<TLorentzVector,float> elerecpair;
    elerecpair.first = recoEle;
    elerecpair.second = recoChg;
    tempEleRecoContainer.push_back(elerecpair);

    nElectronReco++;
  }

  // Sort reco electrons in descending pt
  std::sort(tempEleRecoContainer.begin(), tempEleRecoContainer.end(), 
	  [](pair<TLorentzVector,float> x, pair<TLorentzVector,float> y) { return (x.first).Pt() > (y.first).Pt(); });


  // Fill reco jet quantities
  for (int i_e = 0; i_e < tempEleRecoContainer.size(); i_e++)
  {
    electron_reco_E.push_back( ( (tempEleRecoContainer[i_e]).first).E() );
    electron_reco_pt.push_back( ( (tempEleRecoContainer[i_e]).first).Pt() );
    electron_reco_eta.push_back( ( (tempEleRecoContainer[i_e]).first).Eta() );
    electron_reco_phi.push_back( ( (tempEleRecoContainer[i_e]).first).Phi() );
    electron_reco_charge.push_back( (tempEleRecoContainer[i_e]).second);
  }




  nMuonReco = 0;
  for (int i_tmuo = 0; i_tmuo < muon_bare_E.size(); i_tmuo++)
  {
    
    // Fetch truth information
    double MuoTrueE = muon_bare_E[i_tmuo];
    double MuoTrueEta = muon_bare_eta[i_tmuo];
    double MuoTruePhi = muon_bare_phi[i_tmuo];
    double MuoTruePt = muon_bare_pt[i_tmuo];
    double MuoTrueChg = muon_bare_charge[i_tmuo];

    TLorentzVector trueMuo;
    trueMuo.SetPtEtaPhiE(MuoTruePt,MuoTrueEta,MuoTruePhi,MuoTrueE);
    double truePx = trueMuo.Px();
    double truePy = trueMuo.Py();

    // Add truth particle to the Reco Met (reco will be remove later)
    RecoSum_y += truePy;
    RecoSum_x += truePx;

    // Calculate pt-dependent resolution
    double E_resol = 0;
    if (fabs(MuoTrueEta)<1.) E_resol = MuoTrueE*sqrt(2)*(0.00008*MuoTruePt+0.012);
    else if (fabs(MuoTrueEta)>1.) E_resol = MuoTrueE*sqrt(2)*(0.0001*MuoTruePt+0.02);

    // Calculate detector distortion
    double recoE = gRandom->Gaus(MuoTrueE,E_resol);

    // Calculate reco quantities
    double recoEta = MuoTrueEta;
    double recoPhi = MuoTruePhi;
    double recoPt = recoE/cosh(recoEta);
    
    TLorentzVector recoMuo;
    recoMuo.SetPtEtaPhiE(recoPt,recoEta,recoPhi,recoE);
    double recoPx = recoMuo.Px();
    double recoPy = recoMuo.Py();

    // Calculate efficiency and apply
    double MuoEff = 0.98;
    if (fabs(recoEta)<0.1) MuoEff = 0.6;

    bool looseMuo = false;
    
    double testMuo = gRandom->Rndm();
    if (testMuo > MuoEff) looseMuo = true;
    if (looseMuo) continue;

    // Remove non-fiducial muons
    if ( fabs(recoEta) > 2.5) continue;

    // Calculate reco impact on Met
    RecoSum_y += (-1)*recoPy;
    RecoSum_x += (-1)*recoPx;

    // Don't store too low Pt jets
    if (recoPt < 5.) continue;

    // Charge mis-Id
    bool chargeFlip = false;
    float testFlip = gRandom->Rndm();
    float recoChg = MuoTrueChg; 
    if (testFlip > 0.98) chargeFlip = true;
    if (chargeFlip) recoChg = (-1.)*MuoTrueChg;


    // Fill tempEleRecoContainer
    pair<TLorentzVector,float> muorecpair;
    muorecpair.first = recoMuo;
    muorecpair.second = recoChg;
    tempMuoRecoContainer.push_back(muorecpair);

    nMuonReco++;

  }


  // Sort reco muoons in descending pt
  std::sort(tempMuoRecoContainer.begin(), tempMuoRecoContainer.end(), 
    [](pair<TLorentzVector,float> x, pair<TLorentzVector,float> y) { return (x.first).Pt() > (y.first).Pt(); });


  // Fill reco jet quantities
  for (int i_m = 0; i_m < tempMuoRecoContainer.size(); i_m++)
  {
    muon_reco_E.push_back( ( (tempMuoRecoContainer[i_m]).first).E() );
    muon_reco_pt.push_back( ( (tempMuoRecoContainer[i_m]).first).Pt() );
    muon_reco_eta.push_back( ( (tempMuoRecoContainer[i_m]).first).Eta() );
    muon_reco_phi.push_back( ( (tempMuoRecoContainer[i_m]).first).Phi() );
    muon_reco_charge.push_back( (tempMuoRecoContainer[i_m]).second);
  }


  
  // Reco Met
  // ........

  RecoSqSum = pow(RecoSum_x, 2.0) + pow(RecoSum_y, 2.0);
  RecoMet = sqrt(RecoSqSum);
  RecoMet_phi = atan2(RecoSum_y,RecoSum_x);
  if (RecoMet_phi < 0.) RecoMet_phi = RecoMet_phi + 6.283185307;
  
  


  // Global variables
  // ................

  std::vector<TLorentzVector> InputPart;
  std::vector<TLorentzVector> InputPart_Cent;
  std::vector<TLorentzVector> InputPart_Fwd;
  std::vector<float> MetVec;
  map<string, double> sphe_var;
  map<string, double> thru_var;
  map<string, double> Cent_Thru_var;
  map<string, double> Cent_UpDownHemisphere_var;
  map<string, double> Cent_corrections;
  double forward_suppression;


  float eta_min = 0;
  float eta_max = 4.9;
  bool skiplepton = true;
  bool include_chglep = true;
  bool include_etmiss = true;


  MetVec.push_back(sum_x);
  MetVec.push_back(sum_y);


  // Find all detectable hadrons
  InputPart = myUtils.FindParticles(event, eta_min, eta_max, skiplepton, skippart_born);

  // Find all central visible particles
  eta_max = 2.5;
  skiplepton = false;
  InputPart_Cent = myUtils.FindParticles(event, eta_min, eta_max, skiplepton, skippart_bare);

  // Find all visible forward particles
  eta_min = 2.5;
  eta_max = 100.;
  InputPart_Fwd = myUtils.FindParticles(event, eta_min, eta_max, skiplepton, skippart_bare);

  // Get pseudo-global variables (up to eta = 4.9)
  sphe_var = myUtils.TransverseSphericity(InputPart, include_chglep, PromptLeptonBare_Coll, include_etmiss, MetVec);
  thru_var = myUtils.TransverseThrust(InputPart, include_chglep, PromptLeptonBare_Coll, include_etmiss, MetVec);


  // Get central global variables
      // Note: The inputs already include the charged lepton so they don't need to be added by hand here => include_chglep = false
  include_chglep = false;
  Cent_Thru_var = myUtils.TransverseThrust(InputPart_Cent, include_chglep, PromptLeptonBare_Coll, include_etmiss, MetVec);


  // Get corrections to central global variables
  Cent_corrections= myUtils.CentralGlobalCorr(InputPart_Cent,  include_chglep, PromptLeptonBare_Coll, include_etmiss, MetVec);
  forward_suppression = myUtils.ForwardSuppressionCorr(InputPart_Fwd, Cent_corrections["QTC"], Cent_corrections["qrap_cent"]);


  // Up and Down hemisphere quantities
  TVector3 CentralThrustAxis;
  CentralThrustAxis.SetXYZ(Cent_Thru_var["TransvThrustAxisX"],Cent_Thru_var["TransvThrustAxisY"],Cent_Thru_var["TransvThrustAxisZ"]);

  Cent_UpDownHemisphere_var = myUtils.CentralUpAndDownHemisphereQuantities(InputPart_Cent, Cent_corrections["QTC"], CentralThrustAxis);


  // Fill ntuple variables
  glob_TransSpher =  sphe_var["TransvSphericity"];
  glob_TransThrustMaj = 1. - thru_var["TransvThrustMaj"];
  glob_TransThrustMin = thru_var["TransvThrustMin"];

  glob_TransThrustMajRes = 1. - Cent_Thru_var["TransvThrustMaj"] + Cent_corrections["Residue"];
  glob_TransThrustMinRes = Cent_Thru_var["TransvThrustMin"] + Cent_corrections["Residue"];
  glob_TransThrustMajSup = 1. - Cent_Thru_var["TransvThrustMaj"] + forward_suppression;
  glob_TransThrustMinSup = Cent_Thru_var["TransvThrustMin"] + forward_suppression;

  glob_SumMassRes = Cent_UpDownHemisphere_var["CentralMass"] + Cent_corrections["Residue"];
  glob_HeavyMassRes = Cent_UpDownHemisphere_var["HeavyMass"] + Cent_corrections["Residue"];
  glob_SumMassSup = Cent_UpDownHemisphere_var["CentralMass"] + forward_suppression;
  glob_HeavyMassSup = Cent_UpDownHemisphere_var["HeavyMass"] + forward_suppression;

  glob_TotBroadRes = Cent_UpDownHemisphere_var["TotBroadenings"] + Cent_corrections["Residue"];
  glob_WideBroadRes = Cent_UpDownHemisphere_var["WideBroadenings"] + Cent_corrections["Residue"];
  glob_TotBroadSup = Cent_UpDownHemisphere_var["TotBroadenings"] + forward_suppression;
  glob_WideBroadSup = Cent_UpDownHemisphere_var["WideBroadenings"] + forward_suppression;

  glob_SuperSphero = Cent_UpDownHemisphere_var["SuperSpherocity"];



  // Fill the analysis tree
  // ......................


  tree->Fill();

 
  // Clear event-based vectors
  // -------------------------

  top_pt.clear();
  top_eta.clear();
  top_phi.clear();
  top_E.clear();

  neutrino_pt.clear();
  neutrino_eta.clear();
  neutrino_phi.clear();
  neutrino_E.clear();
  neutrino_PdgId.clear();

  muon_bare_pt.clear();
  muon_bare_eta.clear();
  muon_bare_phi.clear();
  muon_bare_E.clear();
  muon_bare_charge.clear();

  muon_dress_pt.clear();
  muon_dress_eta.clear();
  muon_dress_phi.clear();
  muon_dress_E.clear();
  muon_dress_charge.clear();

  muon_born_pt.clear();
  muon_born_eta.clear();
  muon_born_phi.clear();
  muon_born_E.clear();
  muon_born_charge.clear();

  electron_bare_pt.clear();
  electron_bare_eta.clear();
  electron_bare_phi.clear();
  electron_bare_E.clear();
  electron_bare_charge.clear();

  electron_dress_pt.clear();
  electron_dress_eta.clear();
  electron_dress_phi.clear();
  electron_dress_E.clear();
  electron_dress_charge.clear();

  electron_born_pt.clear();
  electron_born_eta.clear();
  electron_born_phi.clear();
  electron_born_E.clear();
  electron_born_charge.clear();

  bjet_bare_pt.clear();
  bjet_bare_eta.clear();
  bjet_bare_phi.clear();
  bjet_bare_E.clear();
  bjet_bare_nPart.clear();

  lightjet_bare_pt.clear();
  lightjet_bare_eta.clear();
  lightjet_bare_phi.clear();
  lightjet_bare_E.clear();
  lightjet_bare_nPart.clear();

  jet_dress_pt.clear();
  jet_dress_eta.clear();
  jet_dress_phi.clear();
  jet_dress_E.clear();
  jet_dress_nPart.clear();

  jet_born_pt.clear();
  jet_born_eta.clear();
  jet_born_phi.clear();
  jet_born_E.clear();
  jet_born_nPart.clear();

  largeRjet_bare_pt.clear();
  largeRjet_bare_eta.clear();
  largeRjet_bare_phi.clear();
  largeRjet_bare_E.clear();

  largeRjet_born_pt.clear();
  largeRjet_born_eta.clear();
  largeRjet_born_phi.clear();
  largeRjet_born_E.clear();

  largeRjet_dress_pt.clear();
  largeRjet_dress_eta.clear();
  largeRjet_dress_phi.clear();
  largeRjet_dress_E.clear();

  bpartonjet_pt.clear();
  bpartonjet_eta.clear();
  bpartonjet_phi.clear();
  bpartonjet_E.clear();

  lightpartonjet_pt.clear();
  lightpartonjet_eta.clear();
  lightpartonjet_phi.clear();
  lightpartonjet_E.clear();

  boson_pt.clear();
  boson_eta.clear();
  boson_phi.clear();
  boson_E.clear();
  boson_ID.clear();

  BarekTSplittingScale1_R04.clear();
  BarekTSplittingScale2_R04.clear();
  BarekTSplittingScale3_R04.clear();
  BarekTSplittingScale1_R10.clear();
  BarekTSplittingScale2_R10.clear();
  BarekTSplittingScale3_R10.clear();

  DresskTSplittingScale1_R04.clear();
  DresskTSplittingScale2_R04.clear();
  DresskTSplittingScale3_R04.clear();
  DresskTSplittingScale1_R10.clear();
  DresskTSplittingScale2_R10.clear();
  DresskTSplittingScale3_R10.clear();

  BornkTSplittingScale1_R04.clear();
  BornkTSplittingScale2_R04.clear();
  BornkTSplittingScale3_R04.clear();
  BornkTSplittingScale1_R10.clear();
  BornkTSplittingScale2_R10.clear();
  BornkTSplittingScale3_R10.clear();

  event_weights.clear();

  Top_Coll.clear();
  Vecboson_Coll.clear();
  PromptLeptonBare_Coll.clear();
  LeptonDress_Coll.clear();
  LeptonBorn_Coll.clear();
  LeptonConversion_Coll.clear();
  FSRPhoton_Coll.clear();
  DressPhoton_Coll.clear();
  Neutrino_Coll.clear();

  TruthBareSmallRJets_Coll.clear();
  TruthBornSmallRJets_Coll.clear();
  TruthDressSmallRJets_Coll.clear();
  TruthBareLargeRJets_Coll.clear();
  TruthDressLargeRJets_Coll.clear();
  TruthBornLargeRJets_Coll.clear();

  BareKtSplittingScale1_R04.clear();
  BareKtSplittingScale2_R04.clear();
  BareKtSplittingScale3_R04.clear();
  BareKtSplittingScale1_R10.clear();
  BareKtSplittingScale2_R10.clear();
  BareKtSplittingScale3_R10.clear();
  
  DressKtSplittingScale1_R04.clear();
  DressKtSplittingScale2_R04.clear();
  DressKtSplittingScale3_R04.clear();
  DressKtSplittingScale1_R10.clear();
  DressKtSplittingScale2_R10.clear();
  DressKtSplittingScale3_R10.clear();
  
  BornKtSplittingScale1_R04.clear();
  BornKtSplittingScale2_R04.clear();
  BornKtSplittingScale3_R04.clear();
  BornKtSplittingScale1_R10.clear();
  BornKtSplittingScale2_R10.clear();
  BornKtSplittingScale3_R10.clear();
  PartonJets_Coll.clear();

  vecbosindex.clear();
  skippart_born.clear();
  skippart_bare.clear();
  skippart_dress.clear();
  InputPart.clear();
  InputPart_Cent.clear();
  InputPart_Fwd.clear();
  MetVec.clear();

  muon_reco_pt.clear();
  muon_reco_eta.clear();
  muon_reco_phi.clear();
  muon_reco_E.clear();
  muon_reco_charge.clear();

  electron_reco_pt.clear();
  electron_reco_eta.clear();
  electron_reco_phi.clear();
  electron_reco_E.clear();
  electron_reco_charge.clear();

  jet_reco_pt.clear();
  jet_reco_eta.clear();
  jet_reco_phi.clear();
  jet_reco_E.clear();

}

//*************************************************************************************






//*************************************************************************************
// Finishing Code
//*************************************************************************************
void MyAnalysis::finish()
{

  // Normalize histograms
  // --------------------

  //Double_t norm = lepton_px->GetEntries();
  //lepton_px->Scale(1/norm);


  // Print histograms
  // ----------------


  // Write trees

  tree->Write();

  // Final Print Statements if needed
  // --------------------------------


}

//*************************************************************************************






//*************************************************************************************
// Main Code
//*************************************************************************************
int main(int argc, char* argv[])
{


  //===========================================================================
  // Initialization Phase
  //===========================================================================


  // Safety checks to make sure the code is run properly
  // ---------------------------------------------------

  // Check that correct number of command-line arguments
  // ...................................................

  // if (argc < 2)
  // {
  //   cerr << " Unexpected number of command-line arguments. \n"
  //   << " You are expected to provide at least an input file name. \n"
  //   << " Program stopped! " << endl;
  //   return 1;
  // }


  // Check that the provided file name corresponds to an existing file
  // .................................................................

  // ifstream is(argv[1]);
  // if (!is) {
  //   cerr << " Command-line file " << argv[1] << " was not found. \n"
  //   << " Program stopped! " << endl;
  //   return 1;
  // }


  // Set other running option keys and flags
  // ---------------------------------------


     // Declare StdArg objects with all flags and keys used in command line
     // ...................................................................

  
  StdArg arg(argc,argv);


     // Print the keys and flags used in command line
     // .............................................
 
  cout << "=================== Begin Arguments ===================================================" << endl;
  for (int i=0;i<argc;i++)
    cout << argv[i] << " ";
  cout << endl;
  cout << "=================== End Arguments ===================================================" << endl;
   

     // Enter all possible keys
     // .......................

  arg.keys  << "-outroot" ;
  arg.keys  << "-outhepmc" ;


     // Instantiate variables that will correspond to key values or correspond to flag booleans
     // .......................................................................................

  string root_output    = "OutputHistos";
  string hepmc_output   = "OutputHepMC";


     // Use Process function of StdArg to parse command line and assign input value or bools to variables
     // .................................................................................................
                                                                              
  try 
  { 

    // Process the argument inputed on command line
    // ............................................
    
    arg.Process();


    // Assign value to keys
    // ....................

        // Note: Check if the key has been parsed in command line and if it is, than get the value 
        //       parsed and assign it to the proper variable

    if ( arg.Key("-outroot")   ) root_output      = arg.Get<string>("-outroot");
    if ( arg.Key("-outhepmc")   ) hepmc_output      = arg.Get<string>("-outhepmc");

  } // end try


     // Use the function BadInput of StdArg to report any error on the flags and keys used in command line
     // ..................................................................................................

  catch (StdArg::BadInput) 
  {
    if (argc > 2) cout<< "Input error" <<endl;
    
    // Call usage function in case of error or no parameters
    // .....................................................
    
    Usage(argv[0]);
    return 1;
    
  } // end catch
  

  // Complain if input file not found                                                                                        
  // ................................


  ifstream is(argv[1]);
  if (!is)
  {
    cerr << " Command-line input file " << argv[1] << " was not found. \n"
          << " Program stopped! " << endl;
    return 1;
  }


  // Prepare output file          
  // ...................

  std::string myOutName;
  myOutName = "../pythia-outputs/"+root_output+".root";

  TFile *myfile = TFile::Open(myOutName.c_str(),"recreate");


  std::string myHepMCName;
  myHepMCName = hepmc_output+".dat";




  // Pythia 8 initialization
  // -----------------------


  // Interface for conversion from Pythia8::Event to HepMC event
  // ...........................................................

  HepMC::Pythia8ToHepMC ToHepMC;
  ToHepMC.set_print_inconsistency(false);

  // Specify file where HepMC events will be stored
  // ..............................................

  HepMC::IO_GenEvent ascii_io(myHepMCName, std::ios::out);


  // Declare a pythia object
  // .......................

  Pythia pythia;


  // Specification of Pythia settings
  // ................................

  // Note: These settings are specified in the input file

  pythia.readFile(argv[1]);


  // Initialize Pythia
  // .................

  pythia.init();


  // Analysis initialization
  // -----------------------

  // Declare user analysis class
  // ...........................

  MyAnalysis myAnalysis;
  ANA_utils myUtilAna;


  // Read in number of event
  // .......................

  int nEvent = pythia.mode("Main:numberOfEvents");

  // Some global variables
  // ---------------------

  int nListEvts = 2;


  // Declare Event Variables
  // -----------------------

  // An event record for parton level particles
  // ..........................................

  // Note: Partons will be taken at the end of the parton evolution
  //       i.e. just before the hadronization.

  Event partonLevelEvent;
  partonLevelEvent.init("Parton Level event record", &pythia.particleData);

  
     // Uncertainty band settings
     // .........................

        // Note: The number of weights is set by the dimension of "UncertaintyBandList" in input
        //       file + 1 for the nominal weight. The string stored are the names of the variations
        //       stored in this List.

  int numOfWeights = pythia.info.nWeights();
  std::cout << "N weights = " << numOfWeights << std::endl;
  vector<double> sumOfWeights;
  vector<string> names;
  vector<string> weightStrings = pythia.settings.wvec("UncertaintyBands:List");

  for (int iWeight=0; iWeight < numOfWeights; ++iWeight)
  {
    names.push_back( (iWeight==0)
                      ? "baseline" : myUtilAna.weightLabel(weightStrings[iWeight-1]));
    sumOfWeights.push_back(0.);
  }


     // Histograms for event weight sum
     // ...............................

        // Note: This histograms will keep track of the Sum of weights for all events for all systematic
        //       variations in order to properly normalize the varied samples. These event weight sums can
        //       also be obtained by summing over all events the weights stored in the ntuple.

  TH1D *sumweights = new TH1D("sumw","Event Sum Weights", numOfWeights, 0, numOfWeights);


  // Initialize the analysis
  // -----------------------

     // Note: This where ntuple variables and histograms are defined

  myAnalysis.init();


  //===========================================================================
  // Loop to Generate Events
  //===========================================================================


  // Begin event loop. Generate event. Skip if error
  // -----------------------------------------------

  for (int iEvent = 0; iEvent < nEvent; ++iEvent)
  {
    if (!pythia.next()) continue;

    //std::cout << "Event " << iEvent << std::endl;


    // Get the parton-level event
    // --------------------------

    // Declare an Analysis Utilities class object
    // ------------------------------------------

    // Note: To be able to access the functions define there
    
    ANA_utils myUtilsMain;



    myUtilsMain.getPartonLevelEvent(pythia.event, partonLevelEvent);


    // Display some event info
    // -----------------------

    // List first few events
    // .....................

    if (iEvent < nListEvts)
    {
      //pythia.event.list();
      //partonLevelEvent.list();
    }


    // User Analysis of current event
    // ------------------------------

    std::vector<double> EvtWeights;

    for (int iWeight = 0; iWeight < numOfWeights; ++iWeight)
    {

      // Get weight
      // ..........

      double w = pythia.info.weight(iWeight);


      // Eliminate events with a negative weigth
      // .......................................

      if (w<0. || w>10.)
        {
          w = 0.;
          std::cout << "Negative or too large weight for variation: " << names[iWeight] << std::endl;
        }


      // Add the weight of the current event to the wsum of weights
      // ..........................................................

      sumOfWeights[iWeight]  += w;

      // Store event weights in a vector
      // ...............................

      EvtWeights.push_back(w);

    }


    // Run the analysis
    // ................

    myAnalysis.analyze(pythia.event, partonLevelEvent, EvtWeights);

    EvtWeights.clear();



    // Produce HepMC output
    // --------------------

      // Construct new empty HepMC event and fill it
      // ...........................................

         // Note: Units will be as chosen for HepMC build, but can be changed by
         //       arguments, e.g. GenEvt( HepMC::Units::GEV, HepMC::Units::MM)

    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
    ToHepMC.fill_next_event( pythia, hepmcevt );


      // Write the HepMC event to file. Done with it
      // ...........................................

    ascii_io << hepmcevt;
    delete hepmcevt;


  }   // End of event loop.


  //===========================================================================
  // Control Output and Run Information
  //===========================================================================


  // Pythia Statistics display
  // -------------------------

  pythia.stat();


  // User finishing
  // --------------

  myAnalysis.finish();

     // Fill sum of weight histogram
     // ............................

  for (int iWeight=0; iWeight < numOfWeights; ++iWeight)
  {
    sumweights->SetBinContent(iWeight,sumOfWeights[iWeight]);
  }


  // Write info to file
  // ------------------

  myfile->Write();
  myfile->Close();


  return 0;
}

//*************************************************************************************
