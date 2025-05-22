// FinalPlots.C
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================
 TFile fileLQW("$PWD/analysisWScnd.root");
  
  // Get the histograms
  // ==================

    // From Leptoquark events
    // ----------------------
  //W
  //True Values
  TH1F *NjetTrue_LQW  = (TH1F*)fileLQW.Get("NumberTrueJet");
  TH1F *LeadJetPt_LQW = (TH1F*)fileLQW.Get("LeadTrueJet_inc_pt");
  TH1F *ScndJetPt_LQW = (TH1F*)fileLQW.Get("ScndTrueJet_inc_pt");
  //Reco Values
  TH1F *NjetReco_LQW  = (TH1F*)fileLQW.Get("NumberRecoJet");
  TH1F *LeadJetPtReco_LQW = (TH1F*)fileLQW.Get("LeadRecoJet_inc_pt");
  TH1F *ScndJetPtReco_LQW = (TH1F*)fileLQW.Get("ScndRecoJet_inc_pt");

  TH1F *VectorW_W = (TH1F*)fileLQW.Get("WBoson_pt");
  TH1F *VectorWReco_W = (TH1F*)fileLQW.Get("WBosonReco_pt");
  TH1F *VectorZ_W = (TH1F*)fileLQW.Get("ZBoson_pt");
  TH1F *VectorZReco_W = (TH1F*)fileLQW.Get("ZBosonReco_pt");
  //Error
  TH1F* NjetError_W = (TH1F*) NjetTrue_LQW->Clone();
  TH1F* LeadError_W = (TH1F*) LeadJetPt_LQW->Clone();
  TH1F* ScndError_W = (TH1F*) ScndJetPt_LQW->Clone();

  TH1F* NjetRecoError_W = (TH1F*) NjetReco_LQW->Clone();
  TH1F* LeadRecoError_W = (TH1F*) LeadJetPtReco_LQW->Clone();
  TH1F* ScndRecoError_W = (TH1F*) ScndJetPtReco_LQW->Clone();


  TFile fileLQZ("$PWD/analysisZScnd.root");

  //Z
  TH1F *NjetTrue_LQZ  = (TH1F*)fileLQZ.Get("NumberTrueJet");
  TH1F *LeadJetPt_LQZ = (TH1F*)fileLQZ.Get("LeadTrueJet_inc_pt");
  TH1F *ScndJetPt_LQZ = (TH1F*)fileLQZ.Get("ScndTrueJet_inc_pt");
  //Reco Values
  TH1F *NjetReco_LQZ  = (TH1F*)fileLQZ.Get("NumberRecoJet");
  TH1F *LeadJetPtReco_LQZ = (TH1F*)fileLQZ.Get("LeadRecoJet_inc_pt");
  TH1F *ScndJetPtReco_LQZ = (TH1F*)fileLQZ.Get("ScndRecoJet_inc_pt");

  TH1F *VectorW_Z = (TH1F*)fileLQZ.Get("WBoson_pt");
  TH1F *VectorWReco_Z = (TH1F*)fileLQZ.Get("WBosonReco_pt");
  TH1F *VectorZ_Z = (TH1F*)fileLQZ.Get("ZBoson_pt");
  TH1F *VectorZReco_Z = (TH1F*)fileLQZ.Get("ZBosonReco_pt");
  //error
  TH1F* NjetError_Z = (TH1F*) NjetTrue_LQZ->Clone();
  TH1F* LeadError_Z = (TH1F*) LeadJetPt_LQZ->Clone();
  TH1F* ScndError_Z = (TH1F*) ScndJetPt_LQZ->Clone();

  TH1F* NjetRecoError_Z = (TH1F*) NjetReco_LQZ->Clone();
  TH1F* LeadRecoError_Z = (TH1F*) LeadJetPtReco_LQZ->Clone();
  TH1F* ScndRecoError_Z = (TH1F*) ScndJetPtReco_LQZ->Clone();
  
  // Divide histograms by bin size when not uniform
  // ==============================================
  
  //comment out this section-1 for raw
  
  LeadJetPt_LQW->Scale(1,"width");
  LeadJetPtReco_LQW->Scale(1,"width");
  ScndJetPt_LQW->Scale(1,"width");
  ScndJetPtReco_LQW->Scale(1,"width");

  LeadJetPt_LQZ->Scale(1,"width");
  LeadJetPtReco_LQZ->Scale(1,"width");
  ScndJetPt_LQZ->Scale(1,"width");
  ScndJetPtReco_LQZ->Scale(1,"width");

    //Looking at leadjetPt for only jets that have a scnd jet
  //Only use when using analysisWScnd
  //First, take ratio of lead jets that have scnd jet / lead jets, for both truth and reco for W and Z
  TH1F *LeadRatioTruth_LQW = (TH1F*) ScndJetPt_LQW->Clone();
  TH1F *LeadRatioReco_LQW = (TH1F*) ScndJetPtReco_LQW->Clone();
  TH1F *LeadRatioTruth_LQZ = (TH1F*) ScndJetPt_LQZ->Clone();
  TH1F *LeadRatioReco_LQZ = (TH1F*) ScndJetPtReco_LQZ->Clone();

  LeadRatioTruth_LQW->Divide(LeadJetPt_LQW);
  LeadRatioReco_LQW->Divide(LeadJetPtReco_LQW);
  LeadRatioTruth_LQZ->Divide(LeadJetPt_LQZ);
  LeadRatioReco_LQZ->Divide(LeadJetPtReco_LQZ);


  //Next, take ratio of W Truth / W Reco and same for Z

  TH1F *LeadRatioW = (TH1F*) LeadRatioTruth_LQW->Clone();
  LeadRatioW->Divide(LeadRatioReco_LQW);
  TH1F *LeadRatioZ = (TH1F*) LeadRatioTruth_LQZ->Clone();
  LeadRatioZ->Divide(LeadRatioReco_LQZ); 

  // Create Canvas
  // =============
    
  TCanvas *c1 = new TCanvas("c1","Njets shape plot",800,600);
  
  TCanvas *c2 = new TCanvas("c2","Pt lead jets shape plot",800,600);
  TCanvas *c3 = new TCanvas("c3","Mll shape plot",800,600);
  
  TCanvas *c4 = new TCanvas("c4","Njets stack plot",800,600);
  TCanvas *c41 = new TCanvas("c41","Njets stack plot",800,600);
  TCanvas *c42 = new TCanvas("c42","Njets stack plot",800,600);
  TCanvas *c5 = new TCanvas("c5","Pt lead jets stack plot",800,600);
  TCanvas *c51 = new TCanvas("c51","Pt lead jets stack plot",800,600);
  TCanvas *c52 = new TCanvas("c52","Pt lead jets stack plot",800,600);
  TCanvas *c6 = new TCanvas("c6","Mll stack plot",800,600);
  TCanvas *c7 = new TCanvas("c7","Pt scnd jets stack plot",800,600);
  TCanvas *c8 = new TCanvas("c8","Mll s tack plot",800,600);
  TCanvas *c81 = new TCanvas("c81","Mll stack plot",800,600);
  TCanvas *c82 = new TCanvas("c82","Mll stack plot",800,600);
  TCanvas *c9 = new TCanvas("c9","Vector W pt",800,600);

  gStyle->SetOptStat(0);

  TCanvas *d1 = new TCanvas("d1","Njets shape plot",800,600);
  
  TCanvas *d2 = new TCanvas("d2","Pt lead jets shape plot",800,600);
  TCanvas *d3 = new TCanvas("d3","Mll shape plot",800,600);
  
  TCanvas *d4 = new TCanvas("d4","Njets stack plot",800,600);
  TCanvas *d41 = new TCanvas("d41","Njets stack plot",800,600);
  TCanvas *d42 = new TCanvas("d42","Njets stack plot",800,600);
  TCanvas *d5 = new TCanvas("d5","Pt lead jets stack plot",800,600);
  TCanvas *d51 = new TCanvas("d51","Pt lead jets stack plot",800,600);
  TCanvas *d52 = new TCanvas("d52","Pt lead jets stack plot",800,600);
  TCanvas *d6 = new TCanvas("d6","Mll stack plot",800,600);

  TCanvas *d7 = new TCanvas("d7","Pt scnd jets stack plot",800,600);
  TCanvas *d8 = new TCanvas("d8","Mll stack plot",800,600);

  TCanvas *d81 = new TCanvas("d81","Mll stack plot",800,600);
  TCanvas *d82 = new TCanvas("d82","Mll stack plot",800,600);

  TCanvas *d9 = new TCanvas("d9","Vector W pt reco",800,600);

  gStyle->SetOptStat(0);

  TCanvas *e1 = new TCanvas("e1","Error for NJetRaw",800,600);
  TCanvas *e2 = new TCanvas("e2","Error for LeadJetPtRaw",800,600);
  TCanvas *e3 = new TCanvas("e3","Error for ScndJetPtRaw",800,600);

  TCanvas *e4 = new TCanvas("e4","Error for Reco NJetRaw",800,600);
  TCanvas *e5 = new TCanvas("e5","Error for Reco LeadJetPtRaw",800,600);
  TCanvas *e6 = new TCanvas("e6","Error for Reco ScndJetPtRaw",800,600);

  TCanvas *f1 = new TCanvas("f1","Error for NJetRaw",800,600);
  TCanvas *f2 = new TCanvas("f2","Error for LeadJetPtRaw",800,600);
  TCanvas *f3 = new TCanvas("f3","Error for ScndJetPtRaw",800,600);

  TCanvas *f4 = new TCanvas("f4","Error for Reco NJetRaw",800,600);
  TCanvas *f5 = new TCanvas("f5","Error for Reco LeadJetPtRaw",800,600);
  TCanvas *f6 = new TCanvas("f6","Error for Reco ScndJetPtRaw",800,600);

  TCanvas *g6 = new TCanvas("g6","Error for Reco ScndJetPtRaw",800,600);
  TCanvas *g7 = new TCanvas("g7","Error for Reco ScndJetPtRaw",800,600);

  TCanvas *h1 = new TCanvas("h1","Stack",800,600);
  TCanvas *h2 = new TCanvas("h2","Stack",800,600);
  TCanvas *h3 = new TCanvas("h3","Stack",800,600);
  TCanvas *h31 = new TCanvas("h31","Stack",800,600);
  TCanvas *h4 = new TCanvas("h4","Stack",800,600);
  TCanvas *h5 = new TCanvas("h5","Stack",800,600);
  TCanvas *h6 = new TCanvas("h6","Stack",800,600);


  gStyle->SetOptStat(0);



  // Normalize histograms
  // ====================

     // Note 1: To compare shape, we need to normalize histograms to the same integral
     //         (set to 1. for simplicity), but to compare predictions to data, they need
     //         to be normalized to the same luminosity as in data (assume here 100pb-1).
     //         There are therefore two different normalization factors that need to be
     //         calculated.

     // Note 2: We will clone the above histograms to apply without ambiguity to the
     //         normalizations.

  
  
     // Normalize histograms to unit integral
     // -------------------------------------

  //True W
  TH1F *NjetTrue_LQW_unit  = (TH1F*) NjetTrue_LQW->Clone();
  float NjetTrue_LQW_scale = NjetTrue_LQW_unit->Integral();

  TH1F *LeadJetPt_LQW_unit  = (TH1F*) LeadJetPt_LQW->Clone();
  float LeadJetPt_LQW_scale = LeadJetPt_LQW_unit->Integral();

  TH1F *ScndJetPt_LQW_unit  = (TH1F*) ScndJetPt_LQW->Clone();
  float ScndJetPt_LQW_scale = ScndJetPt_LQW_unit->Integral();

  //Reco W
  TH1F *NjetReco_LQW_unit  = (TH1F*) NjetReco_LQW->Clone();
  float NjetReco_LQW_scale = NjetReco_LQW_unit->Integral();

  TH1F *LeadJetPtReco_LQW_unit  = (TH1F*) LeadJetPtReco_LQW->Clone();
  float LeadJetPtReco_LQW_scale = LeadJetPtReco_LQW_unit->Integral();

  TH1F *ScndJetPtReco_LQW_unit  = (TH1F*) ScndJetPtReco_LQW->Clone();
  float ScndJetPtReco_LQW_scale = ScndJetPtReco_LQW_unit->Integral();

  //True Z
  TH1F *NjetTrue_LQZ_unit  = (TH1F*) NjetTrue_LQZ->Clone();
  float NjetTrue_LQZ_scale = NjetTrue_LQZ_unit->Integral();

  TH1F *LeadJetPt_LQZ_unit  = (TH1F*) LeadJetPt_LQZ->Clone();
  float LeadJetPt_LQZ_scale = LeadJetPt_LQZ_unit->Integral();

  TH1F *ScndJetPt_LQZ_unit  = (TH1F*) ScndJetPt_LQZ->Clone();
  float ScndJetPt_LQZ_scale = ScndJetPt_LQZ_unit->Integral();
  
  //Reco Z
  TH1F *NjetReco_LQZ_unit  = (TH1F*) NjetReco_LQZ->Clone();
  float NjetReco_LQZ_scale = NjetReco_LQZ_unit->Integral();

  TH1F *LeadJetPtReco_LQZ_unit  = (TH1F*) LeadJetPtReco_LQZ->Clone();
  float LeadJetPtReco_LQZ_scale = LeadJetPtReco_LQZ_unit->Integral();

  TH1F *ScndJetPtReco_LQZ_unit  = (TH1F*) ScndJetPtReco_LQZ->Clone();
  float ScndJetPtReco_LQZ_scale = ScndJetPtReco_LQZ_unit->Integral();


  //comment out this section-2 for raw
  
  ScndJetPtReco_LQZ_unit->Scale(1./ScndJetPtReco_LQZ_scale);
  LeadJetPtReco_LQZ_unit->Scale(1./LeadJetPtReco_LQZ_scale);
  NjetReco_LQZ_unit->Scale(1./NjetReco_LQZ_scale);
  ScndJetPt_LQZ_unit->Scale(1./ScndJetPt_LQZ_scale);
  LeadJetPt_LQZ_unit->Scale(1./LeadJetPt_LQZ_scale);
  NjetTrue_LQZ_unit->Scale(1./NjetTrue_LQZ_scale);
  ScndJetPtReco_LQW_unit->Scale(1./ScndJetPtReco_LQW_scale);
  LeadJetPtReco_LQW_unit->Scale(1./LeadJetPtReco_LQW_scale);
  NjetReco_LQW_unit->Scale(1./NjetReco_LQW_scale);
  ScndJetPt_LQW_unit->Scale(1./ScndJetPt_LQW_scale);
  LeadJetPt_LQW_unit->Scale(1./LeadJetPt_LQW_scale);
  NjetTrue_LQW_unit->Scale(1./NjetTrue_LQW_scale);
  

  //raw data
  //true W
  TH1F *NjetTrue_LQW_raw  = (TH1F*) NjetTrue_LQW->Clone();
  TH1F *LeadJetPt_LQW_raw  = (TH1F*) LeadJetPt_LQW->Clone();
  TH1F *ScndJetPt_LQW_raw  = (TH1F*) ScndJetPt_LQW->Clone();
  //Reco W
  TH1F *NjetReco_LQW_raw  = (TH1F*) NjetReco_LQW->Clone();
  TH1F *LeadJetPtReco_LQW_raw  = (TH1F*) LeadJetPtReco_LQW->Clone();
  TH1F *ScndJetPtReco_LQW_raw  = (TH1F*) ScndJetPtReco_LQW->Clone();

  //True Z
  TH1F *NjetTrue_LQZ_raw  = (TH1F*) NjetTrue_LQZ->Clone();
  TH1F *LeadJetPt_LQZ_raw  = (TH1F*) LeadJetPt_LQZ->Clone();
  TH1F *ScndJetPt_LQZ_raw  = (TH1F*) ScndJetPt_LQZ->Clone();
  //Reco Z
  TH1F *NjetReco_LQZ_raw  = (TH1F*) NjetReco_LQZ->Clone();
  TH1F *LeadJetPtReco_LQZ_raw  = (TH1F*) LeadJetPtReco_LQZ->Clone();
  TH1F *ScndJetPtReco_LQZ_raw  = (TH1F*) ScndJetPtReco_LQZ->Clone();

  //lum
  //True W
  TH1F *NjetTrue_LQW_lum  = (TH1F*) NjetTrue_LQW->Clone();
  TH1F *LeadJetPt_LQW_lum  = (TH1F*) LeadJetPt_LQW->Clone();
  TH1F *ScndJetPt_LQW_lum  = (TH1F*) ScndJetPt_LQW->Clone();
  //Reco W
  TH1F *NjetReco_LQW_lum  = (TH1F*) NjetReco_LQW->Clone();
  TH1F *LeadJetPtReco_LQW_lum  = (TH1F*) LeadJetPtReco_LQW->Clone();
  TH1F *ScndJetPtReco_LQW_lum  = (TH1F*) ScndJetPtReco_LQW->Clone();

  //True Z
  TH1F *NjetTrue_LQZ_lum  = (TH1F*) NjetTrue_LQZ->Clone();
  TH1F *LeadJetPt_LQZ_lum  = (TH1F*) LeadJetPt_LQZ->Clone();
  TH1F *ScndJetPt_LQZ_lum  = (TH1F*) ScndJetPt_LQZ->Clone();
  //Reco Z
  TH1F *NjetReco_LQZ_lum  = (TH1F*) NjetReco_LQZ->Clone();
  TH1F *LeadJetPtReco_LQZ_lum  = (TH1F*) LeadJetPtReco_LQZ->Clone();
  TH1F *ScndJetPtReco_LQZ_lum  = (TH1F*) ScndJetPtReco_LQZ->Clone();


  TH1F *VectorW_W_raw = (TH1F*) VectorW_W->Clone();
  TH1F *VectorZ_W_raw = (TH1F*) VectorZ_W->Clone();
  TH1F *VectorWReco_W_raw = (TH1F*) VectorWReco_W->Clone();
  TH1F *VectorZReco_W_raw = (TH1F*) VectorZReco_W->Clone();

  TH1F *VectorW_Z_raw = (TH1F*) VectorW_Z->Clone();
  TH1F *VectorZ_Z_raw = (TH1F*) VectorZ_Z->Clone();
  TH1F *VectorWReco_Z_raw = (TH1F*) VectorWReco_Z->Clone();
  TH1F *VectorZReco_Z_raw = (TH1F*) VectorZReco_Z->Clone();


  //Calculating Uncertainty



  //Ratio for Unit

  NjetTrue_LQW_unit->Divide(NjetTrue_LQZ_unit);
  LeadJetPt_LQW_unit->Divide(LeadJetPt_LQZ_unit);
  ScndJetPt_LQW_unit->Divide(ScndJetPt_LQZ_unit);

  NjetReco_LQW_unit->Divide(NjetReco_LQZ_unit);
  LeadJetPtReco_LQW_unit->Divide(LeadJetPtReco_LQZ_unit);
  ScndJetPtReco_LQW_unit->Divide(ScndJetPtReco_LQZ_unit);
  
     // Normalize histograms to data luminosity
     // ---------------------------------------

       // Note: The cross sections are not the same for each processes, and the number
       //       of generated events was arbitrary. This means that the luminosity
       //       corresponding to each channel is not the same. To calculate the weight
       //       to be applied, consider the following example for Zmm:
       //
       //       For W, xsct =  4053.1pb, Nevents = 1,000,000 => L = 246.725 pb-1 
       //       For Z, xsct = 648.0pb, Nevents = 1,000,000 => L = 1,532.210 pb-1
       //       Scale_W = 0.00405, Scale_Z = 0.000653
       //       Let choose to normalize to 100 pb-1 of data => scale_Zmm = 100/83.8 = 1.193
       //
       //       For ttbar: xsect = 3.59pb, Nevents = 2000 => L = 557.1  =>  scale_ttbar = 0.1795
       //       For LQ:    xsect = 0.05pb, Nevents = 2000 => L = 40,000 =>  scale_lq = 0.0025 

  //comment out this sectino-3 for raw (the scale code)
  
  NjetTrue_LQW_lum->Scale(0.00405);
  LeadJetPt_LQW_lum->Scale(0.00405);
  ScndJetPt_LQW_lum->Scale(0.00405);

  NjetReco_LQW_lum->Scale(0.00405);
  LeadJetPtReco_LQW_lum->Scale(0.00405);
  ScndJetPtReco_LQW_lum->Scale(0.00405);

  NjetTrue_LQZ_lum->Scale(0.000653);
  LeadJetPt_LQZ_lum->Scale(0.000653);
  ScndJetPt_LQZ_lum->Scale(0.000653);

  NjetReco_LQZ_lum->Scale(0.000653);
  LeadJetPtReco_LQZ_lum->Scale(0.000653);
  ScndJetPtReco_LQZ_lum->Scale(0.000653);

  


  NjetTrue_LQW->Divide(NjetTrue_LQZ);
  LeadJetPt_LQW->Divide(LeadJetPt_LQZ);
  ScndJetPt_LQW->Divide(ScndJetPt_LQZ);

  NjetReco_LQW->Divide(NjetReco_LQZ);
  LeadJetPtReco_LQW->Divide(LeadJetPtReco_LQZ);
  ScndJetPtReco_LQW->Divide(ScndJetPtReco_LQZ);

  //raw 

  NjetTrue_LQW_raw->Divide(NjetTrue_LQZ_raw);
  LeadJetPt_LQW_raw->Divide(LeadJetPt_LQZ_raw);
  ScndJetPt_LQW_raw->Divide(ScndJetPt_LQZ_raw);

  NjetReco_LQW_raw->Divide(NjetReco_LQZ_raw);
  LeadJetPtReco_LQW_raw->Divide(LeadJetPtReco_LQZ_raw);
  ScndJetPtReco_LQW_raw->Divide(ScndJetPtReco_LQZ_raw);

  VectorW_W_raw->Divide(VectorZ_Z_raw);
  VectorWReco_W_raw->Divide(VectorZReco_Z_raw);

  //lum divide

  NjetTrue_LQW_lum->Divide(NjetTrue_LQZ_lum);
  LeadJetPt_LQW_lum->Divide(LeadJetPt_LQZ_lum);
  ScndJetPt_LQW_lum->Divide(ScndJetPt_LQZ_lum);

  NjetReco_LQW_lum->Divide(NjetReco_LQZ_lum);
  LeadJetPtReco_LQW_lum->Divide(LeadJetPtReco_LQZ_lum);
  ScndJetPtReco_LQW_lum->Divide(ScndJetPtReco_LQZ_lum);

  //correction factor

  TH1F *NjetCor_raw = (TH1F*) NjetTrue_LQW_raw->Clone();
  NjetCor_raw->Divide(NjetReco_LQW_raw);
  TH1F *LeadJetPtCor_raw = (TH1F*) LeadJetPt_LQW_raw->Clone();
  LeadJetPtCor_raw->Divide(LeadJetPtReco_LQW_raw);
  TH1F *ScndJetPtCor_raw = (TH1F*) ScndJetPt_LQW_raw->Clone();
  ScndJetPtCor_raw->Divide(ScndJetPtReco_LQW_raw);

  TH1F *NjetCor_lum = (TH1F*) NjetTrue_LQW_lum->Clone();
  NjetCor_lum->Divide(NjetReco_LQW_lum);
  TH1F *LeadJetPtCor_lum = (TH1F*) LeadJetPt_LQW_lum->Clone();
  LeadJetPtCor_lum->Divide(LeadJetPtReco_LQW_lum);
  TH1F *ScndJetPtCor_lum = (TH1F*) ScndJetPt_LQW_lum->Clone();
  ScndJetPtCor_lum->Divide(ScndJetPtReco_LQW_lum);

  //Calculating error
  //true
  float threshold = 25;
  float thresholdR = 50;

  for (int i = 0; i <= NjetError_W->GetNbinsX(); i++) {
    float n1 = NjetError_W->GetBinContent(i);
    float n2 = NjetError_Z->GetBinContent(i);

    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float err2 = (n2 > 0) ? (1.0 / sqrt(n2)) : 0; 

    float combinedRelativeError = sqrt(err1 * err1 + err2 * err2);  
    NjetError_W->SetBinContent(i, combinedRelativeError * 100);

    if (NjetError_W->GetBinContent(i) > threshold) {
      NjetTrue_LQW_raw->SetBinContent(i, 0);
      NjetTrue_LQW_lum->SetBinContent(i, 0);
      NjetTrue_LQW->SetBinContent(i, 0);
      NjetTrue_LQW_unit->SetBinContent(i, 0);
    }
  }

  for (int i = 0; i <= LeadError_W->GetNbinsX(); i++) {
    float n1 = LeadError_W->GetBinContent(i);
    float n2 = LeadError_Z->GetBinContent(i);

    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float err2 = (n2 > 0) ? (1.0 / sqrt(n2)) : 0; 

    float combinedRelativeError = sqrt(err1 * err1 + err2 * err2);  
    LeadError_W->SetBinContent(i, combinedRelativeError * 100);

    if (LeadError_W->GetBinContent(i) > threshold) {
      LeadJetPt_LQW_raw->SetBinContent(i, 0);
      LeadJetPt_LQW_lum->SetBinContent(i, 0);
      LeadJetPt_LQW->SetBinContent(i, 0);
      LeadJetPt_LQW_unit->SetBinContent(i, 0);
    }
  }

  for (int i = 0; i <= ScndError_W->GetNbinsX(); i++) {
    float n1 = ScndError_W->GetBinContent(i);
    float n2 = ScndError_Z->GetBinContent(i);

    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float err2 = (n2 > 0) ? (1.0 / sqrt(n2)) : 0; 

    float combinedRelativeError = sqrt(err1 * err1 + err2 * err2);  
    ScndError_W->SetBinContent(i, combinedRelativeError * 100);

    if (ScndError_W->GetBinContent(i) > threshold) {
      ScndJetPt_LQW_raw->SetBinContent(i, 0);
      ScndJetPt_LQW_lum->SetBinContent(i, 0);
      ScndJetPt_LQW->SetBinContent(i, 0);
      ScndJetPt_LQW_unit->SetBinContent(i, 0);
    }
  }

    for (int i = 0; i <= NjetRecoError_W->GetNbinsX(); i++) {
    float n1 = NjetRecoError_W->GetBinContent(i);
    float n2 = NjetRecoError_Z->GetBinContent(i);

    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float err2 = (n2 > 0) ? (1.0 / sqrt(n2)) : 0; 

    float combinedRelativeError = sqrt(err1 * err1 + err2 * err2);  
    NjetRecoError_W->SetBinContent(i, combinedRelativeError * 100);

    if (NjetRecoError_W->GetBinContent(i) > thresholdR) {
      NjetReco_LQW_raw->SetBinContent(i, 0);
      NjetReco_LQW_lum->SetBinContent(i, 0);
      NjetReco_LQW->SetBinContent(i, 0);
      NjetReco_LQW_unit->SetBinContent(i, 0);
    }
  }

  for (int i = 0; i <= LeadRecoError_W->GetNbinsX(); i++) {
    float n1 = LeadRecoError_W->GetBinContent(i);
    float n2 = LeadRecoError_Z->GetBinContent(i);

    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float err2 = (n2 > 0) ? (1.0 / sqrt(n2)) : 0; 

    float combinedRelativeError = sqrt(err1 * err1 + err2 * err2);  
    LeadRecoError_W->SetBinContent(i, combinedRelativeError * 100);

    if (LeadRecoError_W->GetBinContent(i) > thresholdR) {
      LeadJetPtReco_LQW_raw->SetBinContent(i, 0);
      LeadJetPtReco_LQW_lum->SetBinContent(i, 0);
      LeadJetPtReco_LQW->SetBinContent(i, 0);
      LeadJetPtReco_LQW_unit->SetBinContent(i, 0);
    }
  }

  for (int i = 0; i <= ScndRecoError_W->GetNbinsX(); i++) {
    float n1 = ScndRecoError_W->GetBinContent(i);
    float n2 = ScndRecoError_Z->GetBinContent(i);

    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float err2 = (n2 > 0) ? (1.0 / sqrt(n2)) : 0; 

    float combinedRelativeError = sqrt(err1 * err1 + err2 * err2);  
    ScndRecoError_W->SetBinContent(i, combinedRelativeError * 100);

    if (ScndRecoError_W->GetBinContent(i) > thresholdR) {
      ScndJetPtReco_LQW_raw->SetBinContent(i, 0);
      ScndJetPtReco_LQW_lum->SetBinContent(i, 0);
      ScndJetPtReco_LQW->SetBinContent(i, 0);
      ScndJetPtReco_LQW_unit->SetBinContent(i, 0);
    }
  }
  //corr cut
  TH1F *NjetCorErr = (TH1F*) NjetRecoError_W->Clone();
  for (int i = 0; i <= NjetCorErr->GetNbinsX(); i++) {
    float n1 = NjetRecoError_W->GetBinContent(i) / 100;
    float n2 = NjetError_W->GetBinContent(i) / 100;

    float combinedRelativeError = n1 * n2;  
    NjetCorErr->SetBinContent(i, combinedRelativeError * 100);

    if (NjetCorErr->GetBinContent(i) > threshold) {
      NjetCor_raw->SetBinContent(i, 0);
    }
  }

  TH1F *LeadCorErr = (TH1F*) LeadRecoError_W->Clone();
  for (int i = 0; i <= LeadCorErr->GetNbinsX(); i++) {
    float n1 = LeadRecoError_W->GetBinContent(i) / 100;
    float n2 = LeadError_W->GetBinContent(i) / 100;

    float combinedRelativeError = n1 * n2;  
    LeadCorErr->SetBinContent(i, combinedRelativeError * 100);

    if (LeadCorErr->GetBinContent(i) > threshold) {
      LeadJetPtCor_raw->SetBinContent(i, 0);
    }
  }

  TH1F *ScndCorErr = (TH1F*) ScndRecoError_W->Clone();
  for (int i = 0; i <= ScndCorErr->GetNbinsX(); i++) {
    float n1 = ScndRecoError_W->GetBinContent(i) / 100;
    float n2 = ScndError_W->GetBinContent(i) / 100;

    float combinedRelativeError = n1 * n2;  
    ScndCorErr->SetBinContent(i, combinedRelativeError * 100);

    if (ScndCorErr->GetBinContent(i) > threshold) {
      ScndJetPtCor_raw->SetBinContent(i, 0);
    }
  }

  //Reconstruct truth
  TFile fileLQTW("$PWD/analysisWtest.root"); //This should be the test data for W
  TFile fileLQTZ("$PWD/analysisZtest.root"); //For Z

  //Reco Values for W
  TH1F *NjetTrue_LQTW  = (TH1F*)fileLQTW.Get("NumberTrueJet");
  TH1F *LeadJetPtTrue_LQTW = (TH1F*)fileLQTW.Get("LeadTrueJet_inc_pt");
  TH1F *ScndJetPtTrue_LQTW = (TH1F*)fileLQTW.Get("ScndTrueJet_inc_pt");

  TH1F *LeadJetPtReco_LQTW = (TH1F*)fileLQTW.Get("LeadRecoJet_inc_pt");

  //Reco Values for Z
  TH1F *NjetTrue_LQTZ  = (TH1F*)fileLQTZ.Get("NumberTrueJet");
  TH1F *LeadJetPtTrue_LQTZ = (TH1F*)fileLQTZ.Get("LeadTrueJet_inc_pt");
  TH1F *ScndJetPtTrue_LQTZ = (TH1F*)fileLQTZ.Get("ScndTrueJet_inc_pt");

  TH1F *LeadJetPtReco_LQTZ = (TH1F*)fileLQTZ.Get("LeadRecoJet_inc_pt");

  LeadJetPtReco_LQTW->Scale(1,"width");
  LeadJetPtReco_LQTZ->Scale(1,"width");
  
  LeadJetPtTrue_LQTW->Scale(1,"width");
  ScndJetPtTrue_LQTW->Scale(1,"width");
  LeadJetPtTrue_LQTZ->Scale(1,"width");
  ScndJetPtTrue_LQTZ->Scale(1,"width");

  LeadJetPtReco_LQTW->Divide(LeadJetPtReco_LQTZ);
  LeadJetPtTrue_LQTW->Divide(LeadJetPtTrue_LQTZ);

  TH1F *unfolded = (TH1F*) LeadJetPtReco_LQTW->Clone();
  for (int i = 0; i < unfolded->GetNbinsX(); i++) {
    float n1 = unfolded->GetBinContent(i) * LeadJetPtCor_raw->GetBinContent(i);
    unfolded->SetBinContent(i, n1);
  }
  TH1F *MeasDivTruth = (TH1F*) unfolded->Clone();
  MeasDivTruth->Divide(LeadJetPtTrue_LQTW);
  

  //Lastly, we have the ratio of Truth / Reco, which is WT/ZT/WR/ZR = WT * ZR / ZT * WR
  //This is comparable to the unfolding correction factor

  TH1F *LeadRatio = (TH1F*) LeadRatioW->Clone();
  LeadRatio->Divide(LeadRatioZ);

  //Now we multiply by test reco and divide by test truth to return 1

  TFile fileLQSW("$PWD/analysisWThirdTest.root"); //This should be the test data for W
  TFile fileLQSZ("$PWD/analysisZThirdTest.root"); //For Z

  //Reco Values for W
  TH1F *LeadJetPtTrue_LQSW = (TH1F*)fileLQSW.Get("LeadTrueJet_inc_pt");
  TH1F *ScndJetPtTrue_LQSW = (TH1F*)fileLQSW.Get("ScndTrueJet_inc_pt");
  TH1F *LeadJetPtReco_LQSW = (TH1F*)fileLQSW.Get("LeadRecoJet_inc_pt");
  TH1F *ScndJetPtReco_LQSW = (TH1F*)fileLQSW.Get("ScndRecoJet_inc_pt");

  //Reco Values for Z
  TH1F *LeadJetPtTrue_LQSZ = (TH1F*)fileLQSZ.Get("LeadTrueJet_inc_pt");
  TH1F *ScndJetPtTrue_LQSZ = (TH1F*)fileLQSZ.Get("ScndTrueJet_inc_pt");
  TH1F *LeadJetPtReco_LQSZ = (TH1F*)fileLQSZ.Get("LeadRecoJet_inc_pt");
  TH1F *ScndJetPtReco_LQSZ = (TH1F*)fileLQSZ.Get("ScndRecoJet_inc_pt");
  
  LeadJetPtTrue_LQSW->Scale(1,"width");
  ScndJetPtTrue_LQSW->Scale(1,"width");
  LeadJetPtReco_LQSW->Scale(1,"width");
  ScndJetPtReco_LQSW->Scale(1,"width");
  LeadJetPtTrue_LQSZ->Scale(1,"width");
  ScndJetPtTrue_LQSZ->Scale(1,"width");
  LeadJetPtReco_LQSZ->Scale(1,"width");
  ScndJetPtReco_LQSZ->Scale(1,"width");
  
  //Test Reco
  ScndJetPtReco_LQSW->Divide(LeadJetPtReco_LQSW);
  ScndJetPtReco_LQSZ->Divide(LeadJetPtReco_LQSZ);
  //Test Truth
  ScndJetPtTrue_LQSW->Divide(LeadJetPtTrue_LQSW);
  ScndJetPtTrue_LQSZ->Divide(LeadJetPtTrue_LQSZ);



  TH1F *unfolded2 = (TH1F*) ScndJetPtReco_LQSW->Clone();
  TH1F *unfolded21 = (TH1F*) ScndJetPtReco_LQSZ->Clone();
  for (int i = 0; i <= unfolded2->GetNbinsX(); i++) {
    float n1 = unfolded2->GetBinContent(i) * LeadRatioW->GetBinContent(i);
    float n2 = unfolded21->GetBinContent(i) * LeadRatioZ->GetBinContent(i);
    unfolded2->SetBinContent(i, n1);
  }
  TH1F *MeasDivTruth2 = (TH1F*) unfolded2->Clone();
  MeasDivTruth2->Divide(ScndJetPtTrue_LQSW);

  
  // Create Stack Plots
  // ==================

  THStack* NjetTrue  = new THStack("NjetTrue", "Njets");
  THStack* LeadJetPtTrue  = new THStack("LeadJetPtTrue", "LeadJet Pt true, log-y scale");
  THStack* ScndJetPtTrue  = new THStack("ScndJetPtTrue", "ScndJet Pt true, log-y scale");

  THStack* NjetReco  = new THStack("NjetReco", "Njets Reco");
  THStack* LeadJetPtReco  = new THStack("LeadJetPtReco", "LeadJet Pt Reco, log-y scale");
  THStack* ScndJetPtReco  = new THStack("ScndJetPtReco", "Scndet Pt Reco, log-y scale");

  THStack* NjetTrue_raw  = new THStack("NjetTrue", "Njets");
  THStack* LeadJetPtTrue_raw  = new THStack("LeadJetPtTrue", "LeadJet Pt true, all events");
  THStack* ScndJetPtTrue_raw  = new THStack("ScndJetPtTrue", "ScndJet Pt true, all events");

  THStack* NjetReco_raw  = new THStack("NjetReco", "Njets Reco");
  THStack* LeadJetPtReco_raw  = new THStack("LeadJetPtReco", "LeadJet Pt Reco, all events");
  THStack* ScndJetPtReco_raw  = new THStack("ScndJetPtReco", "Scndet Pt Reco, all events");

  THStack* NjetTrue_lum  = new THStack("NjetTrue", "Njets");
  THStack* LeadJetPtTrue_lum  = new THStack("LeadJetPtTrue", "LeadJet Pt true, all events");
  THStack* ScndJetPtTrue_lum  = new THStack("ScndJetPtTrue", "ScndJet Pt true, all events");

  THStack* NjetReco_lum  = new THStack("NjetReco", "Njets Reco");
  THStack* LeadJetPtReco_lum  = new THStack("LeadJetPtReco", "LeadJet Pt Reco, all events");
  THStack* ScndJetPtReco_lum  = new THStack("ScndJetPtReco", "Scndet Pt Reco, all events");
  
  THStack* SWVector_raw  = new THStack("SWVector", "W Vector, all events");
  THStack* SZVector_raw  = new THStack("SZVector", "Z Vector, all events");
  THStack* SWVectorReco_raw  = new THStack("SWVectorReco", "W Vector Reco, all events");
  THStack* SZVectorReco_raw  = new THStack("SZVectorReco", "Z Vector Reco, all events");

  //Correction factor stacks

  THStack* Njet_raw  = new THStack("Njet_raw", "Njets Correction Factor");
  THStack* LeadJetPt_raw  = new THStack("LeadJetPt_raw", "LeadJet Pt, Unfolding Correction Factor raw scale");
  THStack* ScndJetPt_raw  = new THStack("ScndJetPt_raw", "Scndet Pt, Correction Factor raw scale");

  THStack* Njet_lum  = new THStack("Njet_lum", "Njets Correction Factor");
  THStack* LeadJetPt_lum  = new THStack("LeadJetPt_lum", "LeadJet Pt, Unfolding Correction Factor lum scale");
  THStack* ScndJetPt_lum  = new THStack("ScndJetPt_lum", "Scndet Pt, Correction Factor lum scale");

  //Recovered truth measurement
  THStack* RecoTruth_leadjetpt  = new THStack("ScndJetPt_lum", "Scndet Pt, Correction Factor lum scale");

  //Measure 2, lead jet w/scnd jet
  THStack* LeadJetRatioTrue_Stack  = new THStack("LeadJetRatioTrue_Stack", "LeadJetPt w/ njet > 2");
  THStack* LeadJetRatioReco_Stack  = new THStack("LeadJetRatioReco_Stack", "LeadJetPt w/ njet > 2");

  THStack* RatioTrue_Stack  = new THStack("RatioTrue_Stack", "LeadJetPt w/ njet > 2");
  THStack* RatioReco_Stack  = new THStack("RatioReco_Stack", "LeadJetPt w/ njet > 2");

  THStack* Ratio_Stack  = new THStack("Ratio_Stack", "LeadJetPt w/ njet > 2");

  // Make plots
  // ==========


    // Shape Comparisons between various processes
    // -------------------------------------------

       // Note: The color code is: 1=black, 2=red, 3=green
  
  //True
  // Njets
  /*
  c1->cd();


  NjetTrue_LQW_unit->GetXaxis()->SetTitle("Njets");
  NjetTrue_LQW_unit->GetYaxis()->SetTitle("True NJet W/Z, unit scale");

  NjetTrue_LQW_unit->SetMarkerStyle(8);
  NjetTrue_LQW_unit->SetMarkerColor(3);
  NjetTrue_LQW_unit->SetLineColor(3);
  NjetTrue_LQW_unit->SetLineWidth(3);
  NjetTrue_LQW_unit->Draw("HIST");

  c1->Print("./plots/NjetTrueRatio_unit.png");

  */

  // Lead Jet Pt
  
  c2->cd();

  LeadJetPt_LQW_unit->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPt_LQW_unit->GetYaxis()->SetTitle("True LeadJetpt W/Z, unit");
  
  LeadJetPt_LQW_unit->SetMarkerStyle(8);
  LeadJetPt_LQW_unit->SetMarkerColor(3);
  LeadJetPt_LQW_unit->SetLineColor(3);
  LeadJetPt_LQW_unit->SetLineWidth(3);
  LeadJetPt_LQW_unit->Draw("HIST");


  c2->Print("./plots/LeadJetPtTrueRatio_unit.png");

  
  /*
    // Stack plots
    // -----------

  
  // Njets
  
  c4->cd();

  gPad->SetLogy(); 

  NjetTrue_LQW->SetFillColor(3);
  NjetTrue->Add(NjetTrue_LQW, "hist");

  NjetTrue->Draw();

  NjetTrue->GetXaxis()->SetTitle("Njets");
  NjetTrue->GetYaxis()->SetTitle("True NJet W/Z, logy scale");


  c4->Print("./plots/NjetTrueRatio_logy.png");
  //raw
  c41->cd();

  NjetTrue_LQW_raw->SetFillColor(3);
  NjetTrue_raw->Add(NjetTrue_LQW_raw, "hist");

  NjetTrue_raw->Draw();

  NjetTrue_raw->GetXaxis()->SetTitle("Njets");
  NjetTrue_raw->GetYaxis()->SetTitle("True NJet W/Z, raw scale");

  c41->Print("./plots/NjetTrueRatio_raw.png");

  //lum
  c42->cd();

  NjetTrue_LQW_lum->SetFillColor(3);
  NjetTrue_lum->Add(NjetTrue_LQW_lum, "hist");

  NjetTrue_lum->Draw();

  NjetTrue_lum->GetXaxis()->SetTitle("Njets");
  NjetTrue_lum->GetYaxis()->SetTitle("True NJet W/Z, lum scale");


  c42->Print("./plots/NjetTrueRatio_lum.png");
  
  */
    // Lead Jet Pt

  
  c5->cd();
  gPad->SetLogy();
  LeadJetPt_LQW->SetFillColor(3);
  LeadJetPtTrue->Add(LeadJetPt_LQW, "hist");
  
  LeadJetPtTrue->SetMinimum(0.01);
  LeadJetPtTrue->SetMaximum(10);
  LeadJetPtTrue->Draw();

  LeadJetPtTrue->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtTrue->GetYaxis()->SetTitle("True LeadJetPt W/Z, logy scale");

  c5->Print("./plots/LeadJetPtTrueRatio_logy.png");


  c51->cd();

  LeadJetPtTrue_raw->SetTitle("Truth LeadJetPt W/Z, Raw Scale");
  //LeadJetPt_LQW_raw->SetFillColor(3);
  LeadJetPtTrue_raw->Add(LeadJetPt_LQW_raw);

  LeadJetPtTrue_raw->Draw("LP");
  LeadJetPtTrue_raw->GetXaxis()->SetRangeUser(30, 400);
  LeadJetPtTrue_raw->SetMaximum(1.2);   // Y-axis upper limit
  LeadJetPtTrue_raw->SetMinimum(0.6);   // Y-axis lower limit
  LeadJetPtTrue_raw->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtTrue_raw->GetYaxis()->SetTitle("(dsigma_{W+1}/dp_{T}^{j})/(dsigma_{Z+1}/dp_{T}^{j})");

  c51->Print("./plots/LeadJetPtTrueRatio_raw.png");

  //lum
  c52->cd();

  //LeadJetPtTrue_lum->SetTitle("Truth LeadJetPt W/Z");
  LeadJetPtTrue_lum->SetTitle("");
  //LeadJetPt_LQW_lum->SetFillColor(3);
  //LeadJetPtTrue_lum->Add(LeadJetPt_LQW_lum, "hist");
  LeadJetPtTrue_lum->Add(LeadJetPt_LQW_lum);
  
  LeadJetPtTrue_lum->Draw("LP");
  LeadJetPtTrue_lum->GetXaxis()->SetRangeUser(30, 400);
  LeadJetPtTrue_lum->SetMaximum(9);   // Y-axis upper limit
  LeadJetPtTrue_lum->SetMinimum(5); 
  LeadJetPtTrue_lum->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtTrue_lum->GetYaxis()->SetTitle("(dsigma_{W+1}/dp_{T}^{j})/(dsigma_{Z+1}/dp_{T}^{j})");

  c52->Print("./plots/LeadJetPtTrueRatio_lum.png");

  //Sncd 
  /*
  c7->cd();

  ScndJetPt_LQW_unit->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPt_LQW_unit->GetYaxis()->SetTitle("True ScndJetpt W/Z, unit scale");
  
  ScndJetPt_LQW_unit->SetMarkerStyle(8);
  ScndJetPt_LQW_unit->SetMarkerColor(3);
  ScndJetPt_LQW_unit->SetLineColor(3);
  ScndJetPt_LQW_unit->SetLineWidth(3);
  ScndJetPt_LQW_unit->Draw("HIST");


  c7->Print("./plots/ScndJetPtTrueRatio_unit.png");


  c8->cd();

  gPad->SetLogy(); 

  ScndJetPt_LQW->SetFillColor(3);
  ScndJetPtTrue->Add(ScndJetPt_LQW, "hist");

  ScndJetPtTrue->Draw();

  ScndJetPtTrue->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtTrue->GetYaxis()->SetTitle("True ScndJetpt W/Z, log scale");

  c8->Print("./plots/ScndJetPtTrueRatio_logy.png");

  c81->cd();

  ScndJetPt_LQW_raw->SetFillColor(3);
  ScndJetPtTrue_raw->Add(ScndJetPt_LQW_raw, "hist");

  ScndJetPtTrue_raw->Draw();

  ScndJetPtTrue_raw->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtTrue_raw->GetYaxis()->SetTitle("True ScndJetpt W/Z, raw scale");

  c81->Print("./plots/ScndJetPtTrueRatio_raw.png");
  //lum
  c82->cd();

  ScndJetPt_LQW_lum->SetFillColor(3);
  ScndJetPtTrue_lum->Add(ScndJetPt_LQW_lum, "hist");

  ScndJetPtTrue_lum->Draw();

  ScndJetPtTrue_lum->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtTrue_lum->GetYaxis()->SetTitle("True ScndJetpt W/Z, lum scale");

  c82->Print("./plots/ScndJetPtTrueRatio_lum.png");
  //vector

  c9->cd();

  VectorW_W_raw->SetFillColor(3);
  SWVector_raw->Add(VectorW_W_raw, "hist");

  SWVector_raw->Draw();

  SWVector_raw->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  SWVector_raw->GetYaxis()->SetTitle("True Boson Vector W/Z, raw scale");

  c9->Print("./plots/VectorWZ_raw.png");



  //Reco
  // Njets
  
  d1->cd();

  
  NjetReco_LQW_unit->GetXaxis()->SetTitle("Njets");
  NjetReco_LQW_unit->GetYaxis()->SetTitle("Reco Njet W/Z, unit scale");

  NjetReco_LQW_unit->SetMarkerStyle(8);
  NjetReco_LQW_unit->SetMarkerColor(3);
  NjetReco_LQW_unit->SetLineColor(3);
  NjetReco_LQW_unit->SetLineWidth(3);
  NjetReco_LQW_unit->Draw("HIST");

  d1->Print("./plots/NjetRecoRatio_unit.png");
  */
  

  // Lead Jet Pt
  
  d2->cd();

  LeadJetPtReco_LQW_unit->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtReco_LQW_unit->GetYaxis()->SetTitle("Reco LeadJetpt W/Z, unit scale");
  
  LeadJetPtReco_LQW_unit->SetMarkerStyle(8);
  LeadJetPtReco_LQW_unit->SetMarkerColor(3);
  LeadJetPtReco_LQW_unit->SetLineColor(3);
  LeadJetPtReco_LQW_unit->SetLineWidth(3);
  LeadJetPtReco_LQW_unit->Draw("HIST");

  d2->Print("./plots/LeadJetPtRecoRatio_unit.png");
  /*
  // Njets
  
  d4->cd();

  gPad->SetLogy(); 
  

  NjetReco_LQW->SetFillColor(3);
  NjetReco->Add(NjetReco_LQW, "hist");

  NjetReco->Draw();

  NjetReco->GetXaxis()->SetTitle("Njets");
  NjetReco->GetYaxis()->SetTitle("Reco Njet W/Z, log scale");

  d4->Print("./plots/NjetRecoRatio_logy.png");

  d41->cd();

  NjetReco_LQW_raw->SetFillColor(3);
  NjetReco_raw->Add(NjetReco_LQW_raw, "hist");

  NjetReco_raw->Draw();

  NjetReco_raw->GetXaxis()->SetTitle("Njets");
  NjetReco_raw->GetYaxis()->SetTitle("Reco Njet W/Z, raw scale");

  d41->Print("./plots/NjetRecoRatio_raw.png");

  //lum
  d42->cd();

  NjetReco_LQW_lum->SetFillColor(3);
  NjetReco_lum->Add(NjetReco_LQW_lum, "hist");

  NjetReco_lum->Draw();

  NjetReco_lum->GetXaxis()->SetTitle("Njets");
  NjetReco_lum->GetYaxis()->SetTitle("Reco Njet W/Z, lum scale");

  d42->Print("./plots/NjetRecoRatio_lum.png");
  */
    // Lead Jet Pt

  
  d5->cd();
  gPad->SetLogy(); 

  LeadJetPtReco_LQW->SetFillColor(3);
  LeadJetPtReco->Add(LeadJetPtReco_LQW, "hist");

  LeadJetPtReco->Draw();

  LeadJetPtReco->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtReco->GetYaxis()->SetTitle("Reco LeadJetpt W/Z, log scale");

  d5->Print("./plots/LeadJetPtRecoRatio_logy.png");

  d51->cd();

  //LeadJetPtReco_raw->SetTitle("Reco LeadJetPt W/Z, Raw Scale");
  //LeadJetPtReco_LQW_raw->SetFillColor(3);
  LeadJetPtReco_raw->Add(LeadJetPtReco_LQW_raw, "hist");

  LeadJetPtReco_raw->Draw("L");
  LeadJetPtReco_raw->GetXaxis()->SetRangeUser(30, 400);
  LeadJetPtReco_raw->SetMaximum(1.2);   // Y-axis upper limit
  LeadJetPtReco_raw->SetMinimum(0.6);   // Y-axis lower limit
  LeadJetPtReco_raw->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtReco_raw->GetYaxis()->SetTitle("(dsigma_{W+1}/dp_{T}^{j})/(dsigma_{Z+1}/dp_{T}^{j})");

  d51->Print("./plots/LeadJetPtRecoRatio_raw.png");
  //lum
  d52->cd();

  LeadJetPtReco_lum->SetTitle("Reco LeadJetPt W/Z");
  LeadJetPtReco_lum->SetTitle("");
  //LeadJetPtReco_LQW_lum->SetFillColor(3);
  LeadJetPtReco_lum->Add(LeadJetPtReco_LQW_lum);

  LeadJetPtReco_lum->Draw("LP");
  LeadJetPtReco_lum->GetXaxis()->SetRangeUser(30, 400);
  LeadJetPtReco_lum->SetMaximum(9);   // Y-axis upper limit
  LeadJetPtReco_lum->SetMinimum(5); 
  LeadJetPtReco_lum->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtReco_lum->GetYaxis()->SetTitle("(dsigma_{W+1}/dp_{T}^{j})/(dsigma_{Z+1}/dp_{T}^{j})");

  d52->Print("./plots/LeadJetPtRecoRatio_lum.png");


  /*
  //scnd
    
  d7->cd();

  ScndJetPtReco_LQW_unit->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtReco_LQW_unit->GetYaxis()->SetTitle("Reco ScndJetpt W/Z, unit scale");
  
  ScndJetPtReco_LQW_unit->SetMarkerStyle(8);
  ScndJetPtReco_LQW_unit->SetMarkerColor(3);
  ScndJetPtReco_LQW_unit->SetLineColor(3);
  ScndJetPtReco_LQW_unit->SetLineWidth(3);
  ScndJetPtReco_LQW_unit->Draw("HIST");

  d7->Print("./plots/ScndJetPtRecoRatio_unit.png");


  d8->cd();
  gPad->SetLogy(); 

  ScndJetPtReco_LQW->SetFillColor(3);
  ScndJetPtReco->Add(ScndJetPtReco_LQW, "hist");

  ScndJetPtReco->Draw();

  ScndJetPtReco->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  ScndJetPtReco->GetYaxis()->SetTitle("Reco ScndJetpt W/Z, log scale");

  d8->Print("./plots/ScndJetPtRecoRatio_logy.png");

  d81->cd();

  ScndJetPtReco_LQW_raw->SetFillColor(3);
  ScndJetPtReco_raw->Add(ScndJetPtReco_LQW_raw, "hist");

  ScndJetPtReco_raw->Draw();

  ScndJetPtReco_raw->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  ScndJetPtReco_raw->GetYaxis()->SetTitle("Reco ScndJetpt W/Z, raw scale");

  d81->Print("./plots/ScndJetPtRecoRatio_raw.png");

  //lum
  d82->cd();

  ScndJetPtReco_LQW_lum->SetFillColor(3);
  ScndJetPtReco_lum->Add(ScndJetPtReco_LQW_lum, "hist");

  ScndJetPtReco_lum->Draw();

  ScndJetPtReco_lum->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  ScndJetPtReco_lum->GetYaxis()->SetTitle("Reco ScndJetpt W/Z, lum scale");

  d82->Print("./plots/ScndJetPtRecoRatio_lum.png");
  //vector

  d9->cd();

  VectorWReco_W_raw->SetFillColor(3);
  SWVectorReco_raw->Add(VectorWReco_W_raw, "hist");
  SWVectorReco_raw->Draw();

  SWVectorReco_raw->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  SWVectorReco_raw->GetYaxis()->SetTitle("Reco Boson Vector W/Z, unit scale");

  d9->Print("./plots/VectorWZReco_raw.png");
    

  //correction graphs
  e1->cd();

  NjetCor_raw->SetFillColor(3);
  Njet_raw->Add(NjetCor_raw, "hist");

  Njet_raw->Draw();

  Njet_raw->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  Njet_raw->GetYaxis()->SetTitle("Reco ScndJetpt W/Z, raw scale");

  e1->Print("./plots/NjetCor_raw.png");
  */
  e2->cd();

  //LeadJetPtCor_raw->SetFillColor(3);
  LeadJetPt_raw->Add(LeadJetPtCor_raw);

  LeadJetPt_raw->Draw("LP");
  LeadJetPt_raw->SetTitle("");
  LeadJetPt_raw->GetXaxis()->SetRangeUser(30, 400);
  LeadJetPt_raw->SetMaximum(1.3);   // Y-axis upper limit
  LeadJetPt_raw->SetMinimum(0.8);   // Y-axis lower limit
  LeadJetPt_raw->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPt_raw->GetYaxis()->SetTitle("Truth/Reco");

  e2->Print("./plots/LeadJetPtCor_raw.png");
  /*
  e3->cd();

  ScndJetPtCor_raw->SetFillColor(3);
  ScndJetPt_raw->Add(ScndJetPtCor_raw, "hist");

  ScndJetPt_raw->Draw();

  ScndJetPt_raw->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  ScndJetPt_raw->GetYaxis()->SetTitle("Reco ScndJetpt W/Z, raw scale");

  e3->Print("./plots/ScndJetPtCor_raw.png");

  //Lum
  e4->cd();

  NjetCor_lum->SetFillColor(3);
  Njet_lum->Add(NjetCor_lum, "hist");

  Njet_lum->Draw();

  Njet_lum->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  Njet_lum->GetYaxis()->SetTitle("Reco ScndJetpt W/Z, lum scale");

  e4->Print("./plots/NjetCor_lum.png");
  */
  e5->cd();

  LeadJetPtCor_lum->SetFillColor(3);
  LeadJetPt_lum->Add(LeadJetPtCor_lum, "hist");

  LeadJetPt_lum->Draw();
  LeadJetPt_lum->GetXaxis()->SetRangeUser(30, 400);
  LeadJetPt_lum->SetMaximum(1.2);   // Y-axis upper limit
  LeadJetPt_lum->SetMinimum(0.8);   // Y-axis lower limit
  LeadJetPt_lum->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPt_lum->GetYaxis()->SetTitle("Reco ScndJetpt W/Z, lum scale");

  e5->Print("./plots/LeadJetPtCor_lum.png");
  /*
  e6->cd();

  ScndJetPtCor_lum->SetFillColor(3);
  ScndJetPt_lum->Add(ScndJetPtCor_lum, "hist");

  ScndJetPt_lum->Draw();

  ScndJetPt_lum->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  ScndJetPt_lum->GetYaxis()->SetTitle("Reco ScndJetpt W/Z, lum scale");

  e6->Print("./plots/ScndJetPtCor_lum.png");
  */

    //error

  f1->cd();

  LeadError_W->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  LeadError_W->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  LeadError_W->SetMarkerStyle(8);
  LeadError_W->SetMarkerColor(3);
  LeadError_W->SetLineColor(3);
  LeadError_W->SetLineWidth(3);
  LeadError_W->Draw("HIST");

  f1->Print("./plots/LeadError.png");

  f2->cd();

  NjetError_W->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  NjetError_W->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  NjetError_W->SetMarkerStyle(8);
  NjetError_W->SetMarkerColor(3);
  NjetError_W->SetLineColor(3);
  NjetError_W->SetLineWidth(3);
  NjetError_W->Draw("HIST");

  f2->Print("./plots/NjetError.png");

  f3->cd();

  ScndError_W->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  ScndError_W->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  ScndError_W->SetMarkerStyle(8);
  ScndError_W->SetMarkerColor(3);
  ScndError_W->SetLineColor(3);
  ScndError_W->SetLineWidth(3);
  ScndError_W->Draw("HIST");

  f3->Print("./plots/ScndError.png");

  f4->cd();

  LeadRecoError_W->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  LeadRecoError_W->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  LeadRecoError_W->SetMarkerStyle(8);
  LeadRecoError_W->SetMarkerColor(3);
  LeadRecoError_W->SetLineColor(3);
  LeadRecoError_W->SetLineWidth(3);
  LeadRecoError_W->Draw("HIST");

  f4->Print("./plots/LeadErrorReco.png");

  f5->cd();

  NjetRecoError_W->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  NjetRecoError_W->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  NjetRecoError_W->SetMarkerStyle(8);
  NjetRecoError_W->SetMarkerColor(3);
  NjetRecoError_W->SetLineColor(3);
  NjetRecoError_W->SetLineWidth(3);
  NjetRecoError_W->Draw("HIST");

  f5->Print("./plots/NjetErrorReco.png");

  f6->cd();

  ScndRecoError_W->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  ScndRecoError_W->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  ScndRecoError_W->SetMarkerStyle(8);
  ScndRecoError_W->SetMarkerColor(3);
  ScndRecoError_W->SetLineColor(3);
  ScndRecoError_W->SetLineWidth(3);
  ScndRecoError_W->Draw("HIST");

  f6->Print("./plots/ScndErrorReco.png");
  

  g6->cd();
  //unfolded->SetTitle("Unfolded ratio, LeadJetPt");
  unfolded->SetTitle("");
  unfolded->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  unfolded->GetYaxis()->SetTitle("Correction Factor * Test_{Reco}");

  unfolded->GetXaxis()->SetRangeUser(30, 400);
  unfolded->SetLineWidth(1);
  unfolded->Draw("LP");

  g6->Print("./plots/Unfolded_leadjetpt.png");

  g7->cd();
  //MeasDivTruth->SetTitle("Measured Div Truth, Million Events, LeadJetPt");
  MeasDivTruth->SetTitle("");
  MeasDivTruth->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  MeasDivTruth->GetYaxis()->SetTitle("Unfolded / Test_{Truth}");
  MeasDivTruth->GetXaxis()->SetRangeUser(30, 400);
  MeasDivTruth->GetYaxis()->SetRangeUser(0.7, 1.3);
  MeasDivTruth->SetLineWidth(1);
  MeasDivTruth->Draw("LP");

  TLine *line2 = new TLine(MeasDivTruth->GetXaxis()->GetXmin(), 1, MeasDivTruth->GetXaxis()->GetXmax(), 1);
  line2->SetLineColor(kRed);
  line2->SetLineStyle(2);
  line2->SetLineWidth(2);
  line2->Draw("same");

  g7->Print("./plots/MeasDivTruth_leadjetpt.png");

  h1->cd();

  // Set line colors for clarity
  LeadRatioTruth_LQW->SetLineColor(kRed);
  LeadRatioTruth_LQZ->SetLineColor(kGreen+2);

  LeadRatioTruth_LQW->SetLineWidth(2);
  LeadRatioTruth_LQZ->SetLineWidth(2);

  // Add histograms to stack
  LeadRatioTruth_LQW->GetXaxis()->SetRangeUser(30, 400);
  //LeadJetRatioTrue_Stack->SetTitle("Truth LeadJetpt W and Z");
  LeadRatioTruth_LQW->SetTitle("");
  LeadRatioTruth_LQW->SetMinimum(0);
  //LeadRatioTruth_LQW->SetMaximum(5);
  LeadRatioTruth_LQW->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadRatioTruth_LQW->GetYaxis()->SetTitle("Leadjetpt_{n>1} / Leadjetpt_{n>0}");
  LeadRatioTruth_LQW->Draw("HIST");
  LeadRatioTruth_LQZ->Draw("HIST SAME");
  

  // Add legend
  TLegend *leg = new TLegend(0.65, 0.7, 0.88, 0.88);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);  // transparent background
  leg->AddEntry(LeadRatioTruth_LQW, "W+jets");
  leg->AddEntry(LeadRatioTruth_LQZ, "Z+jets");
  leg->Draw();

  h1->Print("./plots/RatioLeadJetTrue.png");

  h2->cd();

  // Set line colors for clarity
  LeadRatioReco_LQW->SetLineColor(kRed);
  LeadRatioReco_LQZ->SetLineColor(kGreen+2);
  LeadRatioReco_LQW->GetXaxis()->SetRangeUser(30, 400);
  LeadRatioReco_LQW->SetLineWidth(2);
  LeadRatioReco_LQZ->SetLineWidth(2);
  LeadRatioReco_LQW->SetMinimum(0);
  //LeadRatioReco_LQW->SetMaximum(5);
  //LeadJetRatioReco_Stack->SetTitle("Reco LeadJetpt W and Z");
  LeadRatioReco_LQW->SetTitle("");
  LeadRatioReco_LQW->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadRatioReco_LQW->GetYaxis()->SetTitle("Leadjetpt_{n>1} / Leadjetpt_{n>0}");
  // Draw stack with lines only
  LeadRatioReco_LQW->Draw("HIST");
  LeadRatioReco_LQZ->Draw("HIST SAME");


  // Add legend
  TLegend *leg2 = new TLegend(0.65, 0.7, 0.88, 0.88);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);  // transparent background
  leg2->AddEntry(LeadRatioReco_LQW, "W+jets");
  leg2->AddEntry(LeadRatioReco_LQZ, "Z+jets");
  leg2->Draw();

  h2->Print("./plots/RatioLeadJetReco.png");

  h3->cd();

  // Set line colors for clarity
  LeadRatioW->SetLineColor(kRed);

  LeadRatioW->SetLineWidth(2);
  //RatioTrue_Stack->SetTitle("Truth and Reco Ratios for LeadJetpt w/ n > 1");
  LeadRatioW->SetTitle("");
  LeadRatioW->GetXaxis()->SetRangeUser(30, 400);
  LeadRatioW->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadRatioW->GetYaxis()->SetTitle("W_{Truth} / W_{Reco}");
  LeadRatioW->SetMinimum(0.5);
  LeadRatioW->SetMaximum(1.7);
  // Draw stack with lines only
  LeadRatioW->Draw("HIST");
  

  h3->Print("./plots/RatioLeadJet_W.png");

  h31->cd();

  // Set line colors for clarity
  LeadRatioZ->SetLineColor(kRed);

  LeadRatioZ->SetLineWidth(2);
  //RatioTrue_Stack->SetTitle("Truth and Reco Ratios for LeadJetpt w/ n > 1");
  LeadRatioZ->SetTitle("");
  LeadRatioZ->GetXaxis()->SetRangeUser(30, 400);
  LeadRatioZ->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadRatioZ->GetYaxis()->SetTitle("Z_{Truth} / Z_{Reco}");
  LeadRatioZ->SetMinimum(0.5);
  LeadRatioZ->SetMaximum(1.7);
  // Draw stack with lines only
  LeadRatioZ->Draw("HIST");
  

  h31->Print("./plots/RatioLeadJet_Z.png");

  h4->cd();

  // Set line colors for clarity
  LeadRatio->SetLineColor(kRed);
  LeadRatio->SetLineWidth(2);

  // Add histograms to stack
  LeadRatio->GetXaxis()->SetRangeUser(30, 400);
  LeadRatio->SetMinimum(0.5);
  LeadRatio->SetMaximum(1.7);
  // Draw stack with lines only
  LeadRatio->Draw("LP");
  //Ratio_Stack->SetTitle("Unfolding Correctino factor for LeadJetpt w/ n > 1");
  LeadRatio->SetTitle("");
  LeadRatio->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadRatio->GetYaxis()->SetTitle("Truth_{W} / Reco_{W}");

  h4->Print("./plots/RatioCorrection.png");

  h5->cd();
  //unfolded2->SetTitle("Unfolded2 ratio, LeadJetPt w/ n>1");
  unfolded2->SetTitle("");
  unfolded2->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  unfolded2->GetYaxis()->SetTitle("Correction Factor * Test_{Reco}");
  unfolded2->GetXaxis()->SetRangeUser(30, 400);
  unfolded2->SetLineWidth(1);
  unfolded2->Draw("LP");

  h5->Print("./plots/Unfolded2_leadjetpt.png");

  h6->cd();
  //MeasDivTruth2->SetTitle("Measured Div Truth, Million Events, LeadJetPt w/ n>1");
  MeasDivTruth2->SetTitle("");
  MeasDivTruth2->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  MeasDivTruth2->GetYaxis()->SetTitle("Unfolded / Test_{Truth}");
  MeasDivTruth2->GetXaxis()->SetRangeUser(30, 400);
  MeasDivTruth2->SetLineWidth(1);
  MeasDivTruth2->Draw("LP");

  TLine *line3 = new TLine(MeasDivTruth2->GetXaxis()->GetXmin(), 1, MeasDivTruth2->GetXaxis()->GetXmax(), 1);
  line3->SetLineColor(kRed);
  line3->SetLineStyle(2);
  line3->SetLineWidth(2);
  line3->Draw("same");

  h6->Print("./plots/MeasDivTruth2_leadjetpt.png");


  TFile outFile("BBBunfold.root", "RECREATE");
    
  // Write histograms to the file
  MeasDivTruth->Write("MeasDivTruth");
  unfolded->Write("unfolded");
  LeadJetPtTrue_LQTW->Write("truth");
  LeadError_W->Write("uncertainty");

  // Close the file
  outFile.Close();

  std::cout << "Histograms saved to unfolding_results.root" << std::endl;

}

  
