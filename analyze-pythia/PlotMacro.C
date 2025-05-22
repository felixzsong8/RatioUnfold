// FinalPlots.C
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================
 TFile fileLQ("$PWD/analysisZ5Mil.root");
 std::string boson = "Z";


  
  // Get the histograms
  // ==================

    // From Leptoquark events
    // ----------------------
  //True Values
  TH1F *NjetTrue_LQ  = (TH1F*)fileLQ.Get("NumberTrueJet");
  TH1F *LeadJetPt_LQ = (TH1F*)fileLQ.Get("LeadTrueJet_inc_pt");
  TH1F *ScndJetPt_LQ = (TH1F*)fileLQ.Get("ScndTrueJet_inc_pt");
  TH1F *DimuMass_LQ  = (TH1F*)fileLQ.Get("TrueDimuon_M");
  //Reco Values
  TH1F *NjetReco_LQ  = (TH1F*)fileLQ.Get("NumberRecoJet");
  TH1F *LeadJetPtReco_LQ = (TH1F*)fileLQ.Get("LeadRecoJet_inc_pt");
  TH1F *ScndJetPtReco_LQ = (TH1F*)fileLQ.Get("ScndRecoJet_inc_pt");
  TH1F *DimuMassReco_LQ  = (TH1F*)fileLQ.Get("RecoDimuon_M");
  //Vector Boson
  TH1F *VectorW = (TH1F*)fileLQ.Get("WBoson_pt");
  TH1F *VectorWReco = (TH1F*)fileLQ.Get("WBosonReco_pt");
  TH1F *VectorZ = (TH1F*)fileLQ.Get("ZBoson_pt");
  TH1F *VectorZReco = (TH1F*)fileLQ.Get("ZBosonReco_pt");

  TH1F* NjetError = (TH1F*) NjetTrue_LQ->Clone();
  TH1F* LeadError = (TH1F*) LeadJetPt_LQ->Clone();
  TH1F* ScndError = (TH1F*) ScndJetPt_LQ->Clone();

  TH1F* NjetRecoError = (TH1F*) NjetReco_LQ->Clone();
  TH1F* LeadRecoError = (TH1F*) LeadJetPtReco_LQ->Clone();
  TH1F* ScndRecoError = (TH1F*) ScndJetPtReco_LQ->Clone();
  
  
  // Divide histograms by bin size when not uniform
  // ==============================================
  //Comment out this section-1 for raw
  
  LeadJetPt_LQ->Scale(1,"width");
  LeadJetPtReco_LQ->Scale(1,"width");
  ScndJetPt_LQ->Scale(1,"width");
  ScndJetPtReco_LQ->Scale(1,"width");
  

  
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
  TCanvas *c8 = new TCanvas("c8","Mll stack plot",800,600);
  TCanvas *c81 = new TCanvas("c81","Mll stack plot",800,600);
  TCanvas *c82 = new TCanvas("c82","Mll stack plot",800,600);

  TCanvas *c9 = new TCanvas("c9","Vector W pt",800,600);
  TCanvas *c10 = new TCanvas("c10","Vector Z pt",800,600);
  
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
  TCanvas *d10 = new TCanvas("d10","Vector Z pt reco",800,600);

  gStyle->SetOptStat(0);

  TCanvas *e1 = new TCanvas("e1","Error for NJetRaw",800,600);
  TCanvas *e2 = new TCanvas("e2","Error for LeadJetPtRaw",800,600);
  TCanvas *e3 = new TCanvas("e3","Error for ScndJetPtRaw",800,600);

  TCanvas *e4 = new TCanvas("e4","Error for Reco NJetRaw",800,600);
  TCanvas *e5 = new TCanvas("e5","Error for Reco LeadJetPtRaw",800,600);
  TCanvas *e6 = new TCanvas("e6","Error for Reco ScndJetPtRaw",800,600);




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

  //True

  TH1F *NjetTrue_LQ_unit  = (TH1F*) NjetTrue_LQ->Clone();
  float NjetTrue_LQ_scale = NjetTrue_LQ_unit->Integral();

  TH1F *LeadJetPt_LQ_unit  = (TH1F*) LeadJetPt_LQ->Clone();
  float LeadJetPt_LQ_scale = LeadJetPt_LQ_unit->Integral();

  TH1F *ScndJetPt_LQ_unit  = (TH1F*) ScndJetPt_LQ->Clone();
  float ScndJetPt_LQ_scale = ScndJetPt_LQ_unit->Integral();
  
  TH1F *DimuMass_LQ_unit  = (TH1F*) DimuMass_LQ->Clone();
  float DimuMass_LQ_scale = DimuMass_LQ_unit->Integral();

  //comment out this section-2 for raw
  
  NjetTrue_LQ_unit->Scale(1./NjetTrue_LQ_scale);
  LeadJetPt_LQ_unit->Scale(1./LeadJetPt_LQ_scale);
  ScndJetPt_LQ_unit->Scale(1./ScndJetPt_LQ_scale);
  DimuMass_LQ_unit->Scale(1./DimuMass_LQ_scale);
  

  //Reco 

  TH1F *NjetReco_LQ_unit  = (TH1F*) NjetReco_LQ->Clone();
  float NjetReco_LQ_scale = NjetReco_LQ_unit->Integral();

  TH1F *LeadJetPtReco_LQ_unit  = (TH1F*) LeadJetPtReco_LQ->Clone();
  float LeadJetPtReco_LQ_scale = LeadJetPtReco_LQ_unit->Integral();

  TH1F *ScndJetPtReco_LQ_unit  = (TH1F*) ScndJetPtReco_LQ->Clone();
  float ScndJetPtReco_LQ_scale = ScndJetPtReco_LQ_unit->Integral();
  
  TH1F *DimuMassReco_LQ_unit  = (TH1F*) DimuMassReco_LQ->Clone();
  float DimuMassReco_LQ_scale = DimuMassReco_LQ_unit->Integral();

  //comment out this section-3 for raw
  
  NjetReco_LQ_unit->Scale(1./NjetReco_LQ_scale);
  LeadJetPtReco_LQ_unit->Scale(1./LeadJetPtReco_LQ_scale);
  ScndJetPtReco_LQ_unit->Scale(1./ScndJetPtReco_LQ_scale);
  DimuMassReco_LQ_unit->Scale(1./DimuMassReco_LQ_scale);
  


  //Cloning Raw data 
  TH1F *NjetTrue_LQ_raw  = (TH1F*) NjetTrue_LQ->Clone();
  TH1F *LeadJetPt_LQ_raw  = (TH1F*) LeadJetPt_LQ->Clone();
  TH1F *ScndJetPt_LQ_raw  = (TH1F*) ScndJetPt_LQ->Clone();

  TH1F *NjetReco_LQ_raw  = (TH1F*) NjetReco_LQ->Clone();
  TH1F *LeadJetPtReco_LQ_raw  = (TH1F*) LeadJetPtReco_LQ->Clone();
  TH1F *ScndJetPtReco_LQ_raw  = (TH1F*) ScndJetPtReco_LQ->Clone();

  TH1F *VectorW_raw  = (TH1F*) VectorW->Clone();
  TH1F *VectorWReco_raw  = (TH1F*) VectorWReco->Clone();
  TH1F *VectorZ_raw  = (TH1F*) VectorZ->Clone();
  TH1F *VectorZReco_raw  = (TH1F*) VectorZReco->Clone();

  
  //Cloning Luminosity normalized Data

  TH1F *NjetTrue_LQ_lum  = (TH1F*) NjetTrue_LQ->Clone();
  TH1F *LeadJetPt_LQ_lum  = (TH1F*) LeadJetPt_LQ->Clone();
  TH1F *ScndJetPt_LQ_lum  = (TH1F*) ScndJetPt_LQ->Clone();

  TH1F *NjetReco_LQ_lum  = (TH1F*) NjetReco_LQ->Clone();
  TH1F *LeadJetPtReco_LQ_lum  = (TH1F*) LeadJetPtReco_LQ->Clone();
  TH1F *ScndJetPtReco_LQ_lum  = (TH1F*) ScndJetPtReco_LQ->Clone();


  
  
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
       //       Normalize to Lum = 1pb so that we have a ratio of cross sect
       //       Let choose to normalize to 100 pb-1 of data => scale_Zmm = 100/83.8 = 1.193
       //
       //       For ttbar: xsect = 3.59pb, Nevents = 2000 => L = 557.1  =>  scale_ttbar = 0.1795
       //       For LQ:    xsect = 0.05pb, Nevents = 2000 => L = 40,000 =>  scale_lq = 0.0025 

  //comment out this section for raw
  
  NjetTrue_LQ_lum->Scale(0.000653);
  LeadJetPt_LQ_lum->Scale(0.000653);
  ScndJetPt_LQ_lum->Scale(0.000653);

  NjetReco_LQ_lum->Scale(0.000653);
  LeadJetPtReco_LQ_lum->Scale(0.000653);
  ScndJetPtReco_LQ_lum->Scale(0.000653);
  
  //Calculating Errors
  for (int i = 0; i <= LeadError->GetNbinsX(); i++) {
    float n1 = LeadError->GetBinContent(i);
    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float combinedRelativeError = err1 * 100;  
    LeadError->SetBinContent(i, combinedRelativeError);
  }

  for (int i = 0; i <= NjetError->GetNbinsX(); i++) {
    float n1 = NjetError->GetBinContent(i);
    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float combinedRelativeError = err1 * 100;  
    NjetError->SetBinContent(i, combinedRelativeError);
  }

  for (int i = 0; i <= ScndError->GetNbinsX(); i++) {
    float n1 = ScndError->GetBinContent(i);
    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float combinedRelativeError = err1 * 100;  
    ScndError->SetBinContent(i, combinedRelativeError);
  }
  //reco values
  for (int i = 0; i <= LeadRecoError->GetNbinsX(); i++) {
    float n1 = LeadRecoError->GetBinContent(i);
    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float combinedRelativeError = err1 * 100;  
    LeadRecoError->SetBinContent(i, combinedRelativeError);
  }

  for (int i = 0; i <= NjetRecoError->GetNbinsX(); i++) {
    float n1 = NjetRecoError->GetBinContent(i);
    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float combinedRelativeError = err1 * 100;  
    NjetRecoError->SetBinContent(i, combinedRelativeError);
  }

  for (int i = 0; i <= ScndRecoError->GetNbinsX(); i++) {
    float n1 = ScndRecoError->GetBinContent(i);
    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    float combinedRelativeError = err1 * 100;  
    ScndRecoError->SetBinContent(i, combinedRelativeError);
  }

  


  //For Z
  /*
  NjetTrue_LQ->Scale(0.000653);
  LeadJetPt_LQ->Scale(0.000653);
  ScndJetPt_LQ->Scale(0.000653);

  NjetReco_LQ->Scale(0.000653);
  LeadJetPtReco_LQ->Scale(0.000653);
  ScndJetPtReco_LQ->Scale(0.000653);
  */

  

  // Create Stack Plots
  // ==================

  THStack* NjetTrue  = new THStack("NjetTrue", "Njets");
  THStack* LeadJetPtTrue  = new THStack("LeadJetPtTrue", "LeadJet Pt true, log-y scale");
  THStack* ScndJetPtTrue  = new THStack("ScndJetPtTrue", "ScndJet Pt true, log-y scale");
  
  
  THStack* NjetReco  = new THStack("NjetReco", "Njets Reco");
  THStack* LeadJetPtReco  = new THStack("LeadJetPtReco", "LeadJet Pt Reco, log-y scale");
  THStack* ScndJetPtReco  = new THStack("ScndJetPtReco", "Scndet Pt Reco, log-y scale");

  THStack* NjetTrue_raw  = new THStack("NjetTrueRaw", "Njets");
  THStack* LeadJetPtTrue_raw  = new THStack("LeadJetPtTrueRaw", "LeadJet Pt true, raw scale");
  THStack* ScndJetPtTrue_raw  = new THStack("ScndJetPtTrueRaw", "ScndJet Pt true, raw scale");

  THStack* NjetReco_raw  = new THStack("NjetRecoRaw", "Njets Reco");
  THStack* LeadJetPtReco_raw  = new THStack("LeadJetPtRecoRaw", "LeadJet Pt Reco, raw scale");
  THStack* ScndJetPtReco_raw  = new THStack("ScndJetPtRecoRaw", "Scndet Pt Reco, raw scale");

  THStack* NjetTrue_lum  = new THStack("NjetTruelum", "Njets");
  THStack* LeadJetPtTrue_lum  = new THStack("LeadJetPtTruelum", "LeadJet Pt true, Normalized Luminosity");
  THStack* ScndJetPtTrue_lum  = new THStack("ScndJetPtTruelum", "ScndJet Pt true, Normalized Luminosity");

  THStack* NjetReco_lum  = new THStack("NjetRecolum", "Njets Reco");
  THStack* LeadJetPtReco_lum  = new THStack("LeadJetPtRecolum", "LeadJet Pt Reco, Normalized Luminosity");
  THStack* ScndJetPtReco_lum  = new THStack("ScndJetPtRecolum", "Scndet Pt Reco, Normalized Luminosity");
  
  THStack* SWVector_raw  = new THStack("SWVector", "W Vector, all events");
  THStack* SZVector_raw  = new THStack("SZVector", "Z Vector, all events");
  THStack* SWVectorReco_raw  = new THStack("SWVectorReco", "W Vector Reco, all events");
  THStack* SZVectorReco_raw  = new THStack("SZVectorReco", "Z Vector Reco, all events");
  
  // Make plots
  // ==========


    // Shape Comparisons between various processes
    // -------------------------------------------

       // Note: The color code is: 1=black, 2=red, 3=green
  
  //True
  // Njets

  

  // Lead Jet Pt

  c2->cd();

  LeadJetPt_LQ_unit->SetTitle(("Tranverse Momentum of true lead jet, all events - " + boson).c_str());
  LeadJetPt_LQ_unit->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPt_LQ_unit->GetYaxis()->SetTitle("Event Count");

  LeadJetPt_LQ_unit->SetMarkerStyle(8);
  LeadJetPt_LQ_unit->SetMarkerColor(3);
  LeadJetPt_LQ_unit->SetLineColor(3);
  LeadJetPt_LQ_unit->SetLineWidth(3);
  LeadJetPt_LQ_unit->Draw("HIST");


  c2->Print("./plots/LeadJetPt_unit.png");
  
  
    // Lead Jet Pt
  

  c5->cd();

  gPad->SetLogy(); // Enable log scale on y-axis

  // Style histograms
  LeadJetPt_LQ->SetLineColor(kRed);
  LeadJetPtReco_LQ->SetLineColor(kGreen);
  LeadJetPt_LQ->SetLineWidth(2);
  LeadJetPtReco_LQ->SetLineWidth(2);

  // Set titles and axis labels (just do this on one histo)
  //LeadJetPt_LQ->SetTitle(("Leading Jet pT - " + boson + ", Log Scale").c_str());
  LeadJetPt_LQ->SetTitle((""));
  LeadJetPt_LQ->GetXaxis()->SetTitle("p_{T}^{leadjet} [GeV]");
  LeadJetPt_LQ->GetYaxis()->SetTitle("Event Count per GeV");

  // Draw the histograms
  LeadJetPt_LQ->Draw("HIST");        // Draw truth first
  LeadJetPtReco_LQ->Draw("HIST SAME"); // Draw reco on same plot

  // Add a legend
  TLegend* legend = new TLegend(0.65, 0.75, 0.88, 0.88);
  legend->AddEntry(LeadJetPt_LQ, "Truth", "l");
  legend->AddEntry(LeadJetPtReco_LQ, "Reco", "l");
  legend->SetBorderSize(0);
  legend->SetFillStyle(0); // Transparent
  legend->Draw();

  // Save the plot
  c5->SaveAs("./plots/LeadJetPt_logy.png");


  c51->cd();

  LeadJetPtTrue_raw->SetTitle(("LeadJetPt Truth distribution - " + boson + " - Raw Scale").c_str());
  LeadJetPt_LQ_raw->SetFillColor(3);
  LeadJetPtTrue_raw->Add(LeadJetPt_LQ_raw, "hist");

  LeadJetPtTrue_raw->Draw();

  LeadJetPtTrue_raw->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtTrue_raw->GetYaxis()->SetTitle("Event Count");

  c51->Print("./plots/LeadJetPt_raw.png");

  //lum
  c52->cd();

  LeadJetPt_LQ_lum->SetFillColor(3);
  LeadJetPt_LQ_lum->SetTitle(("p_{T}^{leadjet} - " + boson).c_str());
  LeadJetPtTrue_lum->Add(LeadJetPt_LQ_lum, "hist");

  LeadJetPtTrue_lum->Draw();

  LeadJetPtTrue_lum->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtTrue_lum->GetYaxis()->SetTitle("Event Count");

  c52->Print("./plots/LeadJetPt_lum.png");

  d2->cd();

  LeadJetPtReco_LQ_unit->SetTitle(("Tranverse momentum of Reco lead jet, all events - " + boson).c_str());
  LeadJetPtReco_LQ_unit->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtReco_LQ_unit->GetYaxis()->SetTitle("Event Count");
  
  
  LeadJetPtReco_LQ_unit->SetMarkerStyle(8);
  LeadJetPtReco_LQ_unit->SetMarkerColor(3);
  LeadJetPtReco_LQ_unit->SetLineColor(3);
  LeadJetPtReco_LQ_unit->SetLineWidth(3);
  LeadJetPtReco_LQ_unit->Draw("HIST");

  d2->Print("./plots/LeadJetPtReco_unit.png");

  d5->cd();

  gPad->SetLogy(); 

  LeadJetPtReco->SetTitle(("Reco LeadJetPt - " + boson + ", Log Scale").c_str());
  LeadJetPtReco_LQ->SetFillColor(3);
  LeadJetPtReco->Add(LeadJetPtReco_LQ, "hist");

  LeadJetPtReco->Draw();

  LeadJetPtReco->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtReco->GetYaxis()->SetTitle("Event Count per bin");

  d5->Print("./plots/LeadJetPtReco_logy.png");

  //raw 
  d51->cd();

  LeadJetPtReco_LQ_raw->SetFillColor(3);
  LeadJetPtReco_raw->SetTitle(("LeadJetPt Reco distribution - " + boson + " - Raw Scale").c_str());
  LeadJetPtReco_raw->Add(LeadJetPtReco_LQ_raw, "hist");

  LeadJetPtReco_raw->Draw("E");

  LeadJetPtReco_raw->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtReco_raw->GetYaxis()->SetTitle("Event Count");

  d51->Print("./plots/LeadJetPtReco_raw.png");
  //lum
  d52->cd();

  LeadJetPtReco_LQ_lum->SetFillColor(3);
  LeadJetPtReco_lum->Add(LeadJetPtReco_LQ_lum, "hist");

  LeadJetPtReco_lum->Draw();

  LeadJetPtReco_lum->GetXaxis()->SetTitle("p_{T}^{leadjet}");
  LeadJetPtReco_lum->GetYaxis()->SetTitle("Event Count");

  d52->Print("./plots/LeadJetPtReco_lum.png");

  
  c1->cd();

  NjetTrue_LQ_unit->SetTitle(("Njets, Normalized over One - " + boson).c_str());
  NjetTrue_LQ_unit->GetXaxis()->SetTitle("Njets");
  NjetTrue_LQ_unit->GetYaxis()->SetTitle("Normalized Event Count");

  NjetTrue_LQ_unit->SetMarkerStyle(8);
  //NjetTrue_LQ_unit->SetMarkerSize(1);
  NjetTrue_LQ_unit->SetMarkerColor(3);
  NjetTrue_LQ_unit->SetLineColor(3);
  NjetTrue_LQ_unit->SetLineWidth(3);
  NjetTrue_LQ_unit->Draw("HIST");

  c1->Print("./plots/NjetTrue_unit.png");
  
  
    // Stack plots
    // -----------

  
  // Njets
  
  c4->cd();

  gPad->SetLogy(); 


  NjetTrue_LQ->SetFillColor(3);
  NjetTrue->Add(NjetTrue_LQ, "hist");

  NjetTrue->Draw();

  NjetTrue->GetXaxis()->SetTitle("Njets, log scale");
  NjetTrue->GetYaxis()->SetTitle("Event Count");
  NjetTrue_LQ->SetTitle(("Njets, log scale - " + boson).c_str());
  c4->Print("./plots/NjetTrue_logy.png");

  //raw 
  c41->cd();

  NjetTrue_LQ_raw->SetFillColor(3);
  NjetTrue_LQ_raw->SetTitle(("Njets - " + boson).c_str());
  NjetTrue_raw->Add(NjetTrue_LQ_raw, "hist");

  NjetTrue_raw->Draw();

  NjetTrue_raw->GetXaxis()->SetTitle("Njets");
  NjetTrue_raw->GetYaxis()->SetTitle("Event Count");

  c41->Print("./plots/NjetTrue_raw.png");

  //lum
  c42->cd();

  NjetTrue_LQ_lum->SetFillColor(3);
  NjetTrue_LQ_lum->SetTitle(("Njets, log scale - " + boson).c_str());
  
  NjetTrue_lum->Add(NjetTrue_LQ_lum, "hist");

  NjetTrue_lum->Draw();

  NjetTrue_lum->GetXaxis()->SetTitle("Njets");
  NjetTrue_lum->GetYaxis()->SetTitle("Event Count");

  c42->Print("./plots/NjetTrue_lum.png");

  //Scnd jet pt
  
  c7->cd();

  ScndJetPt_LQ_unit->SetTitle(("Tranverse Momentum of true scnd jet, all events - " + boson).c_str());
  ScndJetPt_LQ_unit->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPt_LQ_unit->GetYaxis()->SetTitle("Event Count");
  
  ScndJetPt_LQ_unit->SetMarkerStyle(8);
  ScndJetPt_LQ_unit->SetMarkerColor(3);
  ScndJetPt_LQ_unit->SetLineColor(3);
  ScndJetPt_LQ_unit->SetLineWidth(3);
  ScndJetPt_LQ_unit->Draw("HIST");

  c7->Print("./plots/ScndJetPt_unit.png");

  //

  c8->cd();

  gPad->SetLogy(); 

  ScndJetPt_LQ->SetFillColor(3);
  ScndJetPt_LQ->SetTitle(("p_{T}^{scndjet} - " + boson).c_str());
  ScndJetPtTrue->Add(ScndJetPt_LQ, "hist");

  ScndJetPtTrue->Draw();

  ScndJetPtTrue->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtTrue->GetYaxis()->SetTitle("Event Count");

  c8->Print("./plots/ScndJetPt_logy.png");

  //raw
  c81->cd();

  ScndJetPt_LQ_raw->SetFillColor(3);
  ScndJetPtTrue_raw->Add(ScndJetPt_LQ_raw, "hist");

  ScndJetPtTrue_raw->Draw();

  ScndJetPtTrue_raw->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtTrue_raw->GetYaxis()->SetTitle("Event Count");

  c81->Print("./plots/ScndJetPt_raw.png");
  //lum
  c82->cd();

  ScndJetPt_LQ_lum->SetFillColor(3);
  ScndJetPtTrue_lum->Add(ScndJetPt_LQ_lum, "hist");

  ScndJetPtTrue_lum->Draw();

  ScndJetPtTrue_lum->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtTrue_lum->GetYaxis()->SetTitle("Event Count");

  c82->Print("./plots/ScndJetPt_lum.png");

  //vector raw

  c9->cd();

  VectorW_raw->SetFillColor(3);
  VectorW_raw->SetTitle(("Vector W - " + boson).c_str());
  SWVector_raw->Add(VectorW_raw, "hist");

  SWVector_raw->Draw();

  SWVector_raw->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  SWVector_raw->GetYaxis()->SetTitle("Event Count");

  c9->Print("./plots/VectorW_raw.png");

  c10->cd();

  VectorZ_raw->SetFillColor(3);
  VectorZ_raw->SetTitle(("Vector Z - " + boson).c_str());
  SZVector_raw->Add(VectorZ_raw, "hist");

  SZVector_raw->Draw();

  SZVector_raw->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  SZVector_raw->GetYaxis()->SetTitle("Event Count");

  c10->Print("./plots/VectorZ_raw.png");
  
  

  //Reco
  // Njets
  
  d1->cd();

  NjetReco_LQ_unit->SetTitle(("Njets Reco, all events - " + boson).c_str());
  NjetReco_LQ_unit->GetXaxis()->SetTitle("Njets");
  NjetReco_LQ_unit->GetYaxis()->SetTitle("Event Count");

  NjetReco_LQ_unit->SetMarkerStyle(8);
  NjetReco_LQ_unit->SetMarkerColor(3);
  NjetReco_LQ_unit->SetLineColor(3);
  NjetReco_LQ_unit->SetLineWidth(3);
  NjetReco_LQ_unit->Draw("HIST");

  d1->Print("./plots/NjetReco_unit.png");

  

  // Lead Jet Pt
  
  

  
    // Stack plots
    // -----------

  
  // Njets
  
  d4->cd();

  gPad->SetLogy(); 


  NjetReco_LQ->SetFillColor(3);
  NjetReco->Add(NjetReco_LQ, "hist");

  NjetReco->Draw();

  NjetReco->GetXaxis()->SetTitle("Njets");
  NjetReco->GetYaxis()->SetTitle("Event Count");

  d4->Print("./plots/NjetReco_logy.png");

  //raw

  d41->cd();

  NjetReco_LQ_raw->SetFillColor(3);
  NjetReco_raw->Add(NjetReco_LQ_raw, "hist");

  NjetReco_raw->Draw();

  NjetReco_raw->GetXaxis()->SetTitle("Njets");
  NjetReco_raw->GetYaxis()->SetTitle("Event Count");

  d41->Print("./plots/NjetReco_raw.png");

  //lum
  d42->cd();

  NjetReco_LQ_lum->SetFillColor(3);
  NjetReco_lum->Add(NjetReco_LQ_lum, "hist");

  NjetReco_lum->Draw();

  NjetReco_lum->GetXaxis()->SetTitle("Njets");
  NjetReco_lum->GetYaxis()->SetTitle("Event Count");

  d42->Print("./plots/NjetReco_lum.png");

  

    // Lead Jet Pt

  
  

  // Scnd jet pt unit
  
  d7->cd();

  ScndJetPtReco_LQ_unit->SetTitle(("Tranverse momentum of Reco scnd jet, all events - " + boson).c_str());
  ScndJetPtReco_LQ_unit->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtReco_LQ_unit->GetYaxis()->SetTitle("Event Count");
  
  ScndJetPtReco_LQ_unit->SetMarkerStyle(8);
  ScndJetPtReco_LQ_unit->SetMarkerColor(3);
  ScndJetPtReco_LQ_unit->SetLineColor(3);
  ScndJetPtReco_LQ_unit->SetLineWidth(3);
  ScndJetPtReco_LQ_unit->Draw("HIST");

  d7->Print("./plots/ScndJetPtReco_unit.png");
  // Scnd jet reco

  d8->cd();

  gPad->SetLogy(); 

  ScndJetPtReco_LQ->SetFillColor(3);
  ScndJetPtReco->Add(ScndJetPtReco_LQ, "hist");

  ScndJetPtReco->Draw();

  ScndJetPtReco->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtReco->GetYaxis()->SetTitle("Event Count");

  d8->Print("./plots/ScndJetPtReco_logy.png");

  //Raw
  d81->cd();

  ScndJetPtReco_LQ_raw->SetFillColor(3);
  ScndJetPtReco_raw->Add(ScndJetPtReco_LQ_raw, "hist");

  ScndJetPtReco_raw->Draw();

  ScndJetPtReco_raw->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtReco_raw->GetYaxis()->SetTitle("Event Count");

  d81->Print("./plots/ScndJetPtReco_raw.png");

  //lum
  d82->cd();

  ScndJetPtReco_LQ_lum->SetFillColor(3);
  ScndJetPtReco_lum->Add(ScndJetPtReco_LQ_lum, "hist");

  ScndJetPtReco_lum->Draw();

  ScndJetPtReco_lum->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  ScndJetPtReco_lum->GetYaxis()->SetTitle("Event Count");

  d82->Print("./plots/ScndJetPtReco_lum.png");


  //raw vector 

  d9->cd();

  VectorWReco_raw->SetFillColor(3);
  SWVectorReco_raw->Add(VectorWReco_raw, "hist");

  SWVectorReco_raw->Draw();

  SWVectorReco_raw->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  SWVectorReco_raw->GetYaxis()->SetTitle("Event Count");

  d9->Print("./plots/VectorWReco_raw.png");

  d10->cd();

  VectorZReco_raw->SetFillColor(3);
  SZVectorReco_raw->Add(VectorZReco_raw, "hist");

  SZVectorReco_raw->Draw();

  SZVectorReco_raw->GetXaxis()->SetTitle("p_{T}^{scndjet}");
  SZVectorReco_raw->GetYaxis()->SetTitle("Event Count");

  d10->Print("./plots/VectorZReco_raw.png");
  
  //error

  e1->cd();

  LeadError->SetTitle(("Lead Jet Error - " + boson).c_str());
  LeadError->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  LeadError->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  LeadError->SetMarkerStyle(8);
  LeadError->SetMarkerColor(3);
  LeadError->SetLineColor(3);
  LeadError->SetLineWidth(3);
  LeadError->Draw("HIST");

  e1->Print("./plots/LeadError.png");

  e2->cd();
  
  NjetError->SetTitle(("Njets Error - " + boson).c_str());
  NjetError->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  NjetError->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  NjetError->SetMarkerStyle(8);
  NjetError->SetMarkerColor(3);
  NjetError->SetLineColor(3);
  NjetError->SetLineWidth(3);
  NjetError->Draw("HIST");

  e2->Print("./plots/NjetError.png");

  e3->cd();

  ScndError->SetTitle(("Second Jet Error - " + boson).c_str());
  ScndError->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  ScndError->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  ScndError->SetMarkerStyle(8);
  ScndError->SetMarkerColor(3);
  ScndError->SetLineColor(3);
  ScndError->SetLineWidth(3);
  ScndError->Draw("HIST");

  e3->Print("./plots/ScndError.png");

  e4->cd();

  LeadRecoError->SetTitle(("Lead Reco Jet Error - " + boson).c_str());
  LeadRecoError->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  LeadRecoError->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  LeadRecoError->SetMarkerStyle(8);
  LeadRecoError->SetMarkerColor(3);
  LeadRecoError->SetLineColor(3);
  LeadRecoError->SetLineWidth(3);
  LeadRecoError->Draw("HIST");

  e4->Print("./plots/LeadRecoError.png");

  e5->cd();

  NjetRecoError->SetTitle(("Njet Reco Error - " + boson).c_str());
  NjetRecoError->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  NjetRecoError->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  NjetRecoError->SetMarkerStyle(8);
  NjetRecoError->SetMarkerColor(3);
  NjetRecoError->SetLineColor(3);
  NjetRecoError->SetLineWidth(3);
  NjetRecoError->Draw("HIST");

  e5->Print("./plots/NjetRecoError.png");

  e6->cd();

  ScndRecoError->SetTitle(("Scnd Reco Jet Error - " + boson).c_str());
  ScndRecoError->GetXaxis()->SetTitle("p_{T}^{Leadjet}");
  ScndRecoError->GetYaxis()->SetTitle("Uncertainty (percentage)");
  
  ScndRecoError->SetMarkerStyle(8);
  ScndRecoError->SetMarkerColor(3);
  ScndRecoError->SetLineColor(3);
  ScndRecoError->SetLineWidth(3);
  ScndRecoError->Draw("HIST");

  e6->Print("./plots/ScndRecoError.png");
}
