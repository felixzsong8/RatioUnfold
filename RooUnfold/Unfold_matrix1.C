//Using this to figure out how to create response matrix for scnd

{
    gSystem->Load("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/RooUnfold/libRooUnfold");

    // Open ROOT file
    TFile fileLQW("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisWMil.root");
    TFile fileLQZ("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisZMil.root");
    TFile fileLQSW("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisWScnd.root");
    TFile fileLQSZ("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisZScnd.root");
    TFile fileLQTW("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisWThird.root");
    TFile fileLQTZ("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisZThird.root");

    // Retrieve histograms
    TH1F *hRecoW = (TH1F*)fileLQW.Get("LeadRecoJet_inc_pt"); 
    TH1F *hTrueW = (TH1F*)fileLQW.Get("LeadTrueJet_inc_pt");  

    TH1F *hRecoZ = (TH1F*)fileLQZ.Get("LeadRecoJet_inc_pt"); 
    TH1F *hTrueZ = (TH1F*)fileLQZ.Get("LeadTrueJet_inc_pt"); 

    //Load data for the leadjetpt n>1
    TH1F *scndReco_W = (TH1F*)fileLQSW.Get("ScndRecoJet_inc_pt"); 
    TH1F *scndTruth_W = (TH1F*)fileLQSW.Get("ScndTrueJet_inc_pt");  
    TH1F *ScndReco_Z = (TH1F*)fileLQSZ.Get("ScndRecoJet_inc_pt"); 
    TH1F *ScndTruth_Z = (TH1F*)fileLQSZ.Get("ScndTrueJet_inc_pt"); 

    TH1F *thirdReco_W = (TH1F*)fileLQTW.Get("ScndRecoJet_inc_pt"); 
    TH1F *thirdTruth_W = (TH1F*)fileLQTW.Get("ScndTrueJet_inc_pt"); 

     

    if (!hRecoW || !hTrueW) {
        std::cerr << "Error: One or more histograms not found!" << std::endl;
        return;
    }
    if (!hRecoZ || !hTrueZ) {
        std::cerr << "Error: One or more histograms not found!" << std::endl;
        return;
    }
    if (!scndReco_W || !scndTruth_W) {
        std::cerr << "Error: One or more histograms not found!" << std::endl;
        return;
    }
    if (!thirdReco_W || !thirdTruth_W) {
        std::cerr << "Error: One or more histograms not found!" << std::endl;
        return;
    }
    /*
    hRecoW->Scale(1,"width");
    hTrueW->Scale(1,"width");
    hRecoZ->Scale(1,"width");
    hTrueZ->Scale(1,"width");
    */
    // Create response matrix
    RooUnfoldResponse responseW(hRecoW, hTrueW);
    RooUnfoldResponse responseZ(hRecoZ, hTrueZ);
    RooUnfoldResponse responseW1(scndReco_W, scndTruth_W);
    RooUnfoldResponse responseW2(thirdReco_W, thirdTruth_W);


    //For W
    for (int fileNum = 1; fileNum <= 10; fileNum++) {
        std::string fileName = "/Users/felixsong/Desktop/coding-tufts/SeniorThesis/match-and-clean/root-files/dataW-" + std::to_string(fileNum) + ".root";
        TFile inputFile(fileName.c_str());

        if (!inputFile.IsOpen()) {
            std::cerr << "Error: Could not open file " << fileName << std::endl;
            continue;
        }

        TTree* tree = (TTree*)inputFile.Get("tree");
        if (!tree) {
            std::cerr << "Error: TTree not found in " << fileName << std::endl;
            continue;
        }

        std::vector<float> *reco_pT = nullptr;
        std::vector<float> *truth_pT = nullptr;

        tree->SetBranchAddress("truthMatchJet_pT", &truth_pT);
        tree->SetBranchAddress("recoMatchJet_pT", &reco_pT);

        Long64_t nEntries = tree->GetEntries();
        std::cout << "Processing " << fileName << " with " << nEntries << " entries." << std::endl;

        for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);

        if (reco_pT && truth_pT) {
            // Always fill responseW (leading jet regardless of njet)
            if (reco_pT->size() > 0 && truth_pT->size() > 0) {
                responseW.Fill(reco_pT->at(0), truth_pT->at(0));
            } else if (truth_pT->size() > 0) {
                responseW.Miss(truth_pT->at(0));
            } else if (reco_pT->size() > 0) {
                responseW.Fake(reco_pT->at(0));
            }

            // If njet > 1 (size > 1), fill responseW1 and responseW2
            if (reco_pT->size() > 1 || truth_pT->size() > 1) {
                // For responseW1: leading jet again, but only for events with njet > 1
                if (reco_pT->size() > 1 && truth_pT->size() > 1) {
                    responseW1.Fill(reco_pT->at(0), truth_pT->at(0));
                } else if (truth_pT->size() > 1) {
                    responseW1.Miss(truth_pT->at(0));
                } else if (reco_pT->size() > 1) {
                    responseW1.Fake(reco_pT->at(0));
                }

                // For responseW2: second jet
                if (reco_pT->size() > 1 && truth_pT->size() > 1) {
                    responseW2.Fill(reco_pT->at(1), truth_pT->at(1));
                } else if (truth_pT->size() > 1) {
                    responseW2.Miss(truth_pT->at(1));
                } else if (reco_pT->size() > 1) {
                    responseW2.Fake(reco_pT->at(1));
                }
            }
        }
    }
    }

    //For Z
    for (int fileNum = 1; fileNum <= 10; fileNum++) {
        std::string fileName = "/Users/felixsong/Desktop/coding-tufts/SeniorThesis/match-and-clean/root-files/dataZ-" + std::to_string(fileNum) + ".root";
        TFile inputFile(fileName.c_str());

        if (!inputFile.IsOpen()) {
            std::cerr << "Error: Could not open file " << fileName << std::endl;
            continue;
        }

        TTree* tree = (TTree*)inputFile.Get("tree");
        if (!tree) {
            std::cerr << "Error: TTree not found in " << fileName << std::endl;
            continue;
        }

        std::vector<float> *reco_pT = nullptr;
        std::vector<float> *truth_pT = nullptr;

        tree->SetBranchAddress("truthMatchJet_pT", &truth_pT);
        tree->SetBranchAddress("recoMatchJet_pT", &reco_pT);

        Long64_t nEntries = tree->GetEntries();
        std::cout << "Processing " << fileName << " with " << nEntries << " entries." << std::endl;

        for (Long64_t i = 0; i < nEntries; i++) {
            tree->GetEntry(i);

            if (reco_pT && truth_pT) {  
                if (reco_pT->size() > 0 && truth_pT->size() > 0) {
                    responseZ.Fill(reco_pT->at(0), truth_pT->at(0));
                }
            }
        }
    }
    

    // Perform unfolding
    responseW.UseOverflow(false);
    responseZ.UseOverflow(false);
    responseW1.UseOverflow(false);
    responseW2.UseOverflow(false);
    //For W
    auto* RW = responseW.HresponseNoOverflow();
    auto* c1 = new TCanvas("c1", "Unfolding Results", 2400, 900);
    c1->SetRightMargin(0.15); // Make room for colormap
    RW->SetStats(0);
    RW->Draw("colz");
    RW->SetTitle("Reponse Matrix Colormap for W+jets");
    RW->GetXaxis()->SetTitle("Reco LeadJet p_{T} [GeV]");
    RW->GetYaxis()->SetTitle("Truth LeadJet p_{T} [GeV]");
    RW->GetXaxis()->SetRangeUser(30,400);
    RW->GetYaxis()->SetRangeUser(30,400);
    c1->Draw();
    c1->SaveAs("responseW.png");
    //For Z
    auto* RZ = responseZ.HresponseNoOverflow();
    auto* c2 = new TCanvas("c2", "Unfolding Results", 2400, 900);
    c2->SetRightMargin(0.15); // Make room for colormap
    RZ->SetStats(0);
    RZ->Draw("colz");
    RZ->SetTitle("Reponse Matrix Colormap for Z+jets");
    RZ->GetXaxis()->SetTitle("Reco LeadJet p_{T} [GeV]");
    RZ->GetYaxis()->SetTitle("Truth LeadJet p_{T} [GeV]");
    RZ->GetXaxis()->SetRangeUser(30,400);
    RZ->GetYaxis()->SetRangeUser(30,400);
    c2->Draw();
    c2->SaveAs("responseZ.png");

    auto* RW1 = responseW1.HresponseNoOverflow();
    auto* c3 = new TCanvas("c3", "Unfolding Results", 2000, 900);
    RW1->SetStats(0);
    RW1->Draw("colz");
    RW1->SetTitle("Reponse Matrix Colormap for leadjetpt w/ n > 1");
    RW1->GetXaxis()->SetTitle("Reco LeadJet p_{T} [GeV]");
    RW1->GetYaxis()->SetTitle("Truth LeadJet p_{T} [GeV]");
    RW1->GetXaxis()->SetRangeUser(30,400);
    RW1->GetYaxis()->SetRangeUser(30,400);
    c3->Draw();
    c3->SaveAs("responseW1.png");
    //For Z
    auto* RW2 = responseW2.HresponseNoOverflow();
    auto* c4 = new TCanvas("c4", "Unfolding Results", 2000, 900);
    RW2->SetStats(0);
    RW2->Draw("colz");
    RW2->SetTitle("Reponse Matrix Colormap for Scndjetpt w/ n > 1");
    RW2->GetXaxis()->SetTitle("Reco ScndJet p_{T} [GeV]");
    RW2->GetYaxis()->SetTitle("Truth ScndJet p_{T} [GeV]");
    RW2->GetXaxis()->SetRangeUser(30,300);
    RW2->GetYaxis()->SetRangeUser(30,300);
    c4->Draw();
    c4->SaveAs("responseW2.png");


    //Importing test data
    TFile fileLQW_test("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisWtest.root");
    TFile fileLQZ_test("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisZtest.root");
    TH1F *hTrueTW = (TH1F*)fileLQW_test.Get("LeadTrueJet_inc_pt"); 
    TH1F *hTrueTZ = (TH1F*)fileLQZ_test.Get("LeadTrueJet_inc_pt"); 
    TH1F *hRecoTW = (TH1F*)fileLQW_test.Get("LeadRecoJet_inc_pt"); 
    TH1F *hRecoTZ = (TH1F*)fileLQZ_test.Get("LeadRecoJet_inc_pt"); 

    // Bin-by-bin unfolding
    RooUnfoldBinByBin unfoldBin_W(&responseW, hRecoTW);
    RooUnfoldBinByBin unfoldBin_Z(&responseZ, hRecoTZ);
    TH1F *hUnfoldedBin_W = (TH1F*) unfoldBin_W.Hreco();
    TH1F *hUnfoldedBin_Z = (TH1F*) unfoldBin_Z.Hreco();


    // SVD unfolding with regularization parameter k=5
    int kReg1 = 10;  // Adjust this value to control the regularization strength
    RooUnfoldSvd unfoldSVD_W(&responseW, hRecoTW, kReg1);
    RooUnfoldSvd unfoldSVD_Z(&responseZ, hRecoTZ, kReg1);
    TH1F *hUnfoldedSVD_W = (TH1F*) unfoldSVD_W.Hreco();
    TH1F *hUnfoldedSVD_Z = (TH1F*) unfoldSVD_Z.Hreco();

    //hTrueTW->Scale(1,"width");
    //hTrueTZ->Scale(1,"width");

    // Compute bin-by-bin ratio of unfolded W/Z
    TH1F* hRatioUnfoldedBin = (TH1F*) hUnfoldedBin_W->Clone("hRatioUnfoldedBin");
    hRatioUnfoldedBin->Divide(hUnfoldedBin_Z);
    
    // Compute bin-by-bin ratio of truth W/Z
    TH1F* hRatioTruth = (TH1F*) hTrueTW->Clone("hRatioTruth");
    hRatioTruth->Divide(hTrueTZ);
    
    // Compute the final ratio (truth/unfolded)
    TH1F* hFinalRatioBin = (TH1F*) hRatioTruth->Clone("hFinalRatioBin");
    hFinalRatioBin->Divide(hRatioUnfoldedBin);

    // Compute SVD unfolding ratio
    TH1F* hRatioUnfoldedSVD = (TH1F*) hUnfoldedSVD_W->Clone("hRatioUnfoldedSVD");
    hRatioUnfoldedSVD->Divide(hUnfoldedSVD_Z);
    
    TH1F* hFinalRatioSVD = (TH1F*) hRatioTruth->Clone("hFinalRatioSVD");
    hFinalRatioSVD->Divide(hRatioUnfoldedSVD);

    //Looking at the leadjetpt n > 1 ratios 
    
    TFile fileLQSW_test("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisWScndTest.root");
    TFile fileLQTW_test("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisWThirdTest.root");
    TH1F *sLeadSW = (TH1F*)fileLQSW_test.Get("LeadTrueJet_inc_pt"); 
    TH1F *sScndW = (TH1F*)fileLQSW_test.Get("ScndTrueJet_inc_pt"); 
    TH1F *sLeadRecoSW = (TH1F*)fileLQSW_test.Get("LeadRecoJet_inc_pt"); 
    TH1F *sScndRecoW = (TH1F*)fileLQSW_test.Get("ScndRecoJet_inc_pt"); 
    TH1F *tLeadSW = (TH1F*)fileLQTW_test.Get("LeadTrueJet_inc_pt"); 
    TH1F *tScndW = (TH1F*)fileLQTW_test.Get("ScndTrueJet_inc_pt"); 
    TH1F *tLeadRecoSW = (TH1F*)fileLQTW_test.Get("LeadRecoJet_inc_pt"); 
    TH1F *tScndRecoW = (TH1F*)fileLQTW_test.Get("ScndRecoJet_inc_pt"); 
    int kReg2 = 3;
    int kReg3 = 8;
    RooUnfoldSvd unfoldSVD_W1(&responseW1, sScndRecoW , kReg2);
    RooUnfoldSvd unfoldSVD_W11(&responseW, sLeadRecoSW , kReg1);
    RooUnfoldSvd unfoldSVD_W2(&responseW2, tScndRecoW, kReg3);
    RooUnfoldSvd unfoldSVD_W21(&responseW1, tLeadRecoSW, kReg2);
    TH1F *hUnfoldedSVD_W1 = (TH1F*) unfoldSVD_W1.Hreco();
    TH1F *hUnfoldedSVD_W2 = (TH1F*) unfoldSVD_W2.Hreco();
    TH1F *hUnfoldedSVD_W11 = (TH1F*) unfoldSVD_W11.Hreco();
    TH1F *hUnfoldedSVD_W21 = (TH1F*) unfoldSVD_W21.Hreco();

    RooUnfoldBinByBin unfoldBin_W1(&responseW1, sScndRecoW);
    RooUnfoldBinByBin unfoldBin_W11(&responseW, sLeadRecoSW);
    RooUnfoldBinByBin unfoldBin_W2(&responseW2, tScndRecoW);
    RooUnfoldBinByBin unfoldBin_W21(&responseW1, tLeadRecoSW);
    TH1F *hUnfoldedBin_W1 = (TH1F*) unfoldBin_W1.Hreco();
    TH1F *hUnfoldedBin_W2 = (TH1F*) unfoldBin_W2.Hreco();
    TH1F *hUnfoldedBin_W11 = (TH1F*) unfoldBin_W11.Hreco();
    TH1F *hUnfoldedBin_W21 = (TH1F*) unfoldBin_W21.Hreco();


    TH1F *hTrueTWS = (TH1F*) sScndW->Clone();
    hTrueTWS->Divide(sLeadSW);

    TH1F* hRatioUnfoldedBinS = (TH1F*) hUnfoldedBin_W1->Clone("hRatioUnfoldedBinS");
    hRatioUnfoldedBinS->Divide(hUnfoldedBin_W11);
    
    // Compute bin-by-bin ratio of test truth W_{n>1} / W_{n>0}
    TH1F* hRatioTruthS = (TH1F*) hTrueTWS->Clone("hRatioTruthS");
    
    // Compute the final bin ratio (truth/unfolded)
    TH1F* hFinalRatioBinS = (TH1F*) hRatioTruthS->Clone("hFinalRatioBinS");
    hFinalRatioBinS->Divide(hRatioUnfoldedBinS);

    // Compute SVD final unfolding ratio (truth/unfolded)
    TH1F* hRatioUnfoldedSVDS = (TH1F*) hUnfoldedSVD_W1->Clone("hRatioUnfoldedSVDS");
    hRatioUnfoldedSVDS->Divide(hUnfoldedSVD_W11);

    TH1F* hFinalRatioSVDS = (TH1F*) hRatioTruthS->Clone("hFinalRatioSVDS");
    hFinalRatioSVDS->Divide(hRatioUnfoldedSVDS);
    ///THIRD
    
    TH1F *hTrueTWT = (TH1F*) tScndW->Clone();
    hTrueTWT->Divide(tLeadSW);

    TH1F* hRatioUnfoldedBinT = (TH1F*) hUnfoldedBin_W2->Clone("hRatioUnfoldedBinT");
    hRatioUnfoldedBinT->Divide(hUnfoldedBin_W21);
    
    // Compute bin-by-bin ratio of test truth W_{n>1} / W_{n>1}
    TH1F* hRatioTruthT = (TH1F*) hTrueTWT->Clone("hRatioTruthT");
    
    // Compute the final bin ratio (truth/unfolded)
    TH1F* hFinalRatioBinT = (TH1F*) hRatioTruthT->Clone("hFinalRatioBinT");
    hFinalRatioBinT->Divide(hRatioUnfoldedBinT);

    // Compute SVD final unfolding ratio (truth/unfolded)
    TH1F* hRatioUnfoldedSVDT = (TH1F*) hUnfoldedSVD_W2->Clone("hRatioUnfoldedSVDT");
    hRatioUnfoldedSVDT->Divide(hUnfoldedSVD_W21);

    TH1F* hFinalRatioSVDT = (TH1F*) hRatioTruthT->Clone("hFinalRatioSVDT");
    hFinalRatioSVDT->Divide(hRatioUnfoldedSVDT);

    

    // Plot results
    TCanvas *canvas_W = new TCanvas("canvasW", "Unfolding Results", 1000, 700);
    canvas_W->SetLogy();
    hUnfoldedBin_W->SetStats(0);
    hUnfoldedSVD_W->SetStats(0);
    hRecoTW->SetStats(0);
    hTrueTW->SetStats(0);

    // Draw bin-by-bin unfolding
    hUnfoldedBin_W->SetLineColor(kRed);
    hUnfoldedBin_W->SetLineWidth(2);
    hUnfoldedBin_W->GetXaxis()->SetRangeUser(30,600); 
    hUnfoldedBin_W->Draw("HIST SAME");

    // Draw SVD unfolding
    hUnfoldedSVD_W->SetLineColor(kBlack);
    hUnfoldedSVD_W->SetLineWidth(2);
    hUnfoldedSVD_W->Draw("HIST SAME");

    // Draw measured histogram
    hRecoTW->SetLineColor(kBlue);
    hRecoTW->SetLineWidth(2);
    hRecoTW->Draw("HIST SAME");

    // Draw true histogram
    hTrueTW->SetLineColor(kGreen);
    hTrueTW->SetLineWidth(2);
    hTrueTW->Draw("HIST SAME");

    hUnfoldedBin_W->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hUnfoldedBin_W->GetYaxis()->SetTitle("Events per bin");

    hUnfoldedSVD_W->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hUnfoldedSVD_W->GetYaxis()->SetTitle("Events per bin");

    hRecoTW->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hRecoTW->GetYaxis()->SetTitle("Events per bin");

    hTrueTW->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hTrueTW->GetYaxis()->SetTitle("Events per bin");

    // Create legend
    TLegend *legend_W = new TLegend(0.65, 0.65, 0.9, 0.9);
    legend_W->AddEntry(hUnfoldedBin_W, "Matrix Unfolded", "l");
    legend_W->AddEntry(hUnfoldedSVD_W, "SVD Unfolded", "l");
    legend_W->AddEntry(hRecoTW, "Reco", "l");
    legend_W->AddEntry(hTrueTW, "Truth", "l");
    legend_W->Draw();

    //canvas_W->SetTitle("Unfolding Comparison for W+jets");
    canvas_W->SetTitle("");
    hUnfoldedBin_W->SetTitle("");
    hUnfoldedSVD_W->SetTitle("");
    hRecoTW->SetTitle("");
    hTrueTW->SetTitle("");
    // Save the plot
    canvas_W->SaveAs("unfolding_comparison_W.png");

    //For Z
    // Plot results
    TCanvas *canvas_Z = new TCanvas("canvasZ", "Unfolding Results", 1000, 700);
    canvas_Z->SetLogy();
    hUnfoldedBin_Z->SetStats(0);
    hUnfoldedSVD_Z->SetStats(0);
    hRecoZ->SetStats(0);
    hTrueTZ->SetStats(0);

    // Draw bin-by-bin unfolding
    hUnfoldedBin_Z->SetLineColor(kRed);
    hUnfoldedBin_Z->SetLineWidth(2);
    hUnfoldedBin_Z->Draw("HIST SAME");

    // Draw SVD unfolding
    hUnfoldedSVD_Z->SetLineColor(kMagenta);
    hUnfoldedSVD_Z->SetLineWidth(2);
    hUnfoldedSVD_Z->Draw("HIST SAME");

    // Draw measured histogram
    hRecoZ->SetLineColor(kBlue);
    hRecoZ->SetLineWidth(2);
    hRecoZ->Draw("HIST SAME");

    // Draw true histogram
    hTrueTZ->SetLineColor(kGreen);
    hTrueTZ->SetLineWidth(2);
    hTrueTZ->Draw("HIST SAME");

    hUnfoldedBin_Z->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hUnfoldedBin_Z->GetYaxis()->SetTitle("Events per bin");

    hUnfoldedSVD_Z->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hUnfoldedSVD_Z->GetYaxis()->SetTitle("Events per bin");

    hRecoZ->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hRecoZ->GetYaxis()->SetTitle("Events per bin");

    hTrueTZ->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hTrueTZ->GetYaxis()->SetTitle("Events per bin");

    // Create legend
    TLegend *legend_Z = new TLegend(0.65, 0.65, 0.9, 0.9);
    legend_Z->AddEntry(hUnfoldedBin_Z, "Matrix Unfolded", "l");
    legend_Z->AddEntry(hUnfoldedSVD_Z, "SVD Unfolded", "l");
    legend_Z->AddEntry(hRecoTZ, "Reco", "l");
    legend_Z->AddEntry(hTrueTZ, "Truth", "l");
    legend_Z->Draw();

    //canvas_Z->SetTitle("Unfolding Comparison for Z+jets");
    canvas_Z->SetTitle("");
    hUnfoldedBin_Z->SetTitle("");
    hUnfoldedSVD_Z->SetTitle("");
    hRecoZ->SetTitle("");
    hTrueTZ->SetTitle("");
    // Save the plot
    canvas_Z->SaveAs("unfolding_comparison_Z.png");

    
    /////////////////
    TCanvas *canvas_W1 = new TCanvas("canvasW1", "Unfolding Results", 1000, 700);
    hUnfoldedBin_W1->SetStats(0);
    hUnfoldedSVD_W1->SetStats(0);
    sScndRecoW->SetStats(0);
    sScndW->SetStats(0);
    canvas_W1->SetLeftMargin(0.15); // Make room for colormap
    // Draw bin-by-bin unfolding
    hUnfoldedBin_W1->SetLineColor(kRed);
    hUnfoldedBin_W1->SetLineWidth(2);
    hUnfoldedBin_W1->GetXaxis()->SetRangeUser(30,1000); 
    hUnfoldedBin_W1->GetYaxis()->SetRangeUser(0,15000); 
    hUnfoldedBin_W1->Draw("HIST");

    // Draw SVD unfolding
    hUnfoldedSVD_W1->SetLineColor(kMagenta);
    hUnfoldedSVD_W1->SetLineWidth(2);
    hUnfoldedSVD_W1->Draw("HIST SAME");

    // Draw measured histogram
    sScndRecoW->SetLineColor(kBlue);
    sScndRecoW->SetLineWidth(2);
    sScndRecoW->Draw("HIST SAME");

    // Draw true histogram
    sScndW->SetLineColor(kGreen);
    sScndW->SetLineWidth(2);
    sScndW->Draw("HIST SAME");

    hUnfoldedBin_W1->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hUnfoldedBin_W1->GetYaxis()->SetTitle("Events per bin");

    hUnfoldedSVD_W1->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hUnfoldedSVD_W1->GetYaxis()->SetTitle("Events per bin");

    sScndRecoW->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    sScndRecoW->GetYaxis()->SetTitle("Events per bin");

    sScndW->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    sScndW->GetYaxis()->SetTitle("Events per bin");

    // Create legend
    TLegend *legend_W1 = new TLegend(0.65, 0.65, 0.9, 0.9);
    legend_W1->AddEntry(hUnfoldedBin_W1, "Matrix Unfolded", "l");
    legend_W1->AddEntry(hUnfoldedSVD_W1, "SVD Unfolded", "l");
    legend_W1->AddEntry(sScndRecoW, "Reco", "l");
    legend_W1->AddEntry(sScndW, "Truth", "l");
    legend_W1->Draw();

    //canvas_W->SetTitle("Unfolding Comparison for W+jets");
    canvas_W1->SetTitle("");
    hUnfoldedBin_W1->SetTitle("");
    hUnfoldedSVD_W1->SetTitle("");
    sScndRecoW->SetTitle("");
    sScndW->SetTitle("");
    // Save the plot
    canvas_W1->SaveAs("unfolding_comparison_W1.png");

    TCanvas *canvas_W2 = new TCanvas("canvasW2", "Unfolding Results", 1000, 700);
    hUnfoldedBin_W2->SetStats(0);
    hUnfoldedSVD_W2->SetStats(0);
    tScndRecoW->SetStats(0);
    tScndW->SetStats(0);
    canvas_W2->SetLeftMargin(0.15); // Make room for colormap


    // Draw bin-by-bin unfolding
    hUnfoldedBin_W2->SetLineColor(kRed);
    hUnfoldedBin_W2->SetLineWidth(2);
    hUnfoldedBin_W2->GetXaxis()->SetRangeUser(30,200); 
    hUnfoldedBin_W2->GetYaxis()->SetRangeUser(0,40000); 
    hUnfoldedBin_W2->Draw("HIST");

    // Draw SVD unfolding
    hUnfoldedSVD_W2->SetLineColor(kMagenta);
    hUnfoldedSVD_W2->SetLineWidth(2);
    hUnfoldedSVD_W2->Draw("HIST SAME");

    // Draw measured histogram
    tScndRecoW->SetLineColor(kBlue);
    tScndRecoW->SetLineWidth(2);
    tScndRecoW->Draw("HIST SAME");

    // Draw true histogram
    tScndW->SetLineColor(kGreen);
    tScndW->SetLineWidth(2);
    tScndW->Draw("HIST SAME");

    hUnfoldedBin_W2->GetXaxis()->SetTitle("ScndJet p_{T} [GeV]");
    hUnfoldedBin_W2->GetYaxis()->SetTitle("Events per bin");

    hUnfoldedSVD_W2->GetXaxis()->SetTitle("ScndJet p_{T} [GeV]");
    hUnfoldedSVD_W2->GetYaxis()->SetTitle("Events per bin");

    tScndRecoW->GetXaxis()->SetTitle("ScndJet p_{T} [GeV]");
    tScndRecoW->GetYaxis()->SetTitle("Events per bin");

    tScndW->GetXaxis()->SetTitle("ScndJet p_{T} [GeV]");
    tScndW->GetYaxis()->SetTitle("Events per bin");

    // Create legend
    TLegend *legend_W2 = new TLegend(0.65, 0.65, 0.9, 0.9);
    legend_W2->AddEntry(hUnfoldedBin_W2, "Matrix Unfolded", "l");
    legend_W2->AddEntry(hUnfoldedSVD_W2, "SVD Unfolded", "l");
    legend_W2->AddEntry(tScndRecoW, "Reco", "l");
    legend_W2->AddEntry(tScndW, "Truth", "l");
    legend_W2->Draw();

    //canvas_W->SetTitle("Unfolding Comparison for W+jets");
    canvas_W2->SetTitle("");
    hUnfoldedBin_W2->SetTitle("");
    hUnfoldedSVD_W2->SetTitle("");
    tScndRecoW->SetTitle("");
    tScndW->SetTitle("");
    // Save the plot
    canvas_W2->SaveAs("unfolding_comparison_W2.png");
    //
    TCanvas* cUnfoldRatio_W = new TCanvas("cUnfoldRatio_W", "Signal Unfolded Ratio", 800, 600);
    cUnfoldRatio_W->SetGrid();

    hRatioUnfoldedBin->SetStats(0);
    hRatioUnfoldedSVD->SetStats(0);
    hRatioTruth->SetStats(0);

    hRatioUnfoldedBin->SetLineColor(kRed+1);
    hRatioUnfoldedBin->SetLineWidth(2);
    hRatioUnfoldedBin->SetMarkerStyle(20);
    hRatioUnfoldedBin->SetMarkerColor(kRed+1);
    hRatioUnfoldedBin->GetXaxis()->SetRangeUser(30, 1000); 
    hRatioUnfoldedBin->GetYaxis()->SetRangeUser(0, 4.5);
    hRatioUnfoldedBin->SetTitle("Signal: (W_{n>1}/W_{n>0}) Unfolded Ratio;p_{T} [GeV];Ratio");
    hRatioUnfoldedBin->GetYaxis()->SetTitle("W_{Unfolded}/Z_{Unfolded}");
    hRatioUnfoldedBin->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");

    hRatioUnfoldedSVD->SetLineColor(kBlue+1);
    hRatioUnfoldedSVD->SetLineWidth(2);
    hRatioUnfoldedSVD->SetMarkerStyle(20);
    hRatioUnfoldedSVD->SetMarkerColor(kBlue+1);

    // Fill-style truth ratio (darker green, filled)
    hRatioTruth->SetLineColor(kGreen+3);     
    hRatioTruth->SetLineWidth(2);
    hRatioTruth->SetMarkerStyle(20);    
    hRatioTruth->SetMarkerColor(kGreen+3);     

    hRatioTruth->GetXaxis()->SetTitle("LeadJet p_{T} [GeV]");
    hRatioTruth->GetYaxis()->SetTitle("W_{Unfolded}/Z_{Unfolded}");

    // Draw in order: fill first, then lines  // Filled first
    hRatioUnfoldedBin->Draw("E1");
    hRatioUnfoldedSVD->Draw("E1 SAME");
    hRatioTruth->Draw("P SAME");

    TLegend* legRatio = new TLegend(0.6, 0.75, 0.88, 0.88);
    legRatio->AddEntry(hRatioUnfoldedBin, "Matrix unfolding", "lep");
    legRatio->AddEntry(hRatioUnfoldedSVD, "SVD unfolding", "lep");
    legRatio->AddEntry(hRatioTruth, "Truth Ratio", "lep");  // 'f' for filled style
    legRatio->Draw();

    cUnfoldRatio_W->SaveAs("unfolding_ratio_W.png");

    // SIGNAL: W_{n>1}/W_{n>0} from unfolded (Bin-by-bin & SVD)
    TCanvas* cUnfoldRatio_S = new TCanvas("cUnfoldRatio_S", "Signal Unfolded Ratio", 800, 600);
    cUnfoldRatio_S->SetGrid();
    hRatioUnfoldedBinS->SetStats(0);
    hRatioUnfoldedSVDS->SetStats(0);
    hRatioTruthS->SetStats(0);


    hRatioUnfoldedBinS->SetLineColor(kRed+1);
    hRatioUnfoldedBinS->SetLineWidth(2);
    hRatioUnfoldedBinS->SetMarkerStyle(20);
    hRatioUnfoldedBinS->SetMarkerColor(kRed+1);
    hRatioUnfoldedBinS->GetXaxis()->SetRangeUser(30,1000); 
    hRatioUnfoldedBinS->SetTitle("Signal: (W_{n>1}/W_{n>0}) Unfolded Ratio;p_{T} [GeV];Ratio");
    hRatioUnfoldedBinS->GetYaxis()->SetTitle("(LeadJetPt_{n>1}/LeadJetPt_{n>0})");
    hRatioUnfoldedBinS->GetXaxis()->SetTitle("LeadJetPt [GeV]");

    hRatioUnfoldedSVDS->SetLineColor(kBlue+1);
    hRatioUnfoldedSVDS->SetLineWidth(2);
    hRatioUnfoldedSVDS->SetMarkerStyle(24);
    hRatioUnfoldedSVDS->SetMarkerColor(kBlue+1);
    
    hRatioTruthS->SetLineColor(kGreen+1);
    hRatioTruthS->SetLineWidth(2);
    hRatioTruthS->SetMarkerStyle(24);
    hRatioTruthS->SetMarkerColor(kGreen+1);

    hRatioUnfoldedBinS->Draw("E1");
    hRatioUnfoldedSVDS->Draw("E1 SAME");
    hRatioTruthS->Draw("P SAME");

    TLegend* legRatioS = new TLegend(0.6, 0.75, 0.88, 0.88);
    legRatioS->AddEntry(hRatioUnfoldedBinS, "Matrix unfolding", "lep");
    legRatioS->AddEntry(hRatioUnfoldedSVDS, "SVD unfolding", "lep");
    legRatioS->AddEntry(hRatioTruthS, "Truth Ratio", "lep");
    legRatioS->Draw();

    cUnfoldRatio_S->SaveAs("unfolding_ratio_W1.png");


    // TEST: W_{n>1}/W_{n>0} from unfolded (Bin-by-bin & SVD)
    TCanvas* cUnfoldRatio_T = new TCanvas("cUnfoldRatio_T", "Test Unfolded Ratio", 800, 600);
    cUnfoldRatio_T->SetGrid();
    hRatioUnfoldedBinT->SetStats(0);
    hRatioUnfoldedSVDT->SetStats(0);
    hRatioTruthT->SetStats(0);

    hRatioUnfoldedBinT->SetLineColor(kRed+1);
    hRatioUnfoldedBinT->SetMarkerColor(kRed+1);
    hRatioUnfoldedBinT->SetLineWidth(2);
    hRatioUnfoldedBinT->SetMarkerStyle(20);
    hRatioUnfoldedBinT->GetXaxis()->SetRangeUser(30,200); 
    hRatioUnfoldedBinT->GetYaxis()->SetRangeUser(0, 10); 
    hRatioUnfoldedBinT->SetTitle("Test: (W_{n>1}/W_{n>0}) Unfolded Ratio;p_{T} [GeV];Ratio");
    hRatioUnfoldedBinT->GetYaxis()->SetTitle("(ScndJetPt_{n>1}/LeadJetPt_{n>1})");
    hRatioUnfoldedBinT->GetXaxis()->SetTitle("ScndJetPt [GeV]");

    hRatioUnfoldedSVDT->SetLineColor(kBlue+1);
    hRatioUnfoldedSVDT->SetLineWidth(2);
    hRatioUnfoldedSVDT->SetMarkerStyle(24);
    hRatioUnfoldedSVDT->SetMarkerColor(kBlue+1);
    
    hRatioTruthT->SetLineColor(kGreen+1);
    hRatioTruthT->SetLineWidth(2);
    hRatioTruthT->SetMarkerStyle(24);
    hRatioTruthT->SetMarkerColor(kGreen+1);

    hRatioUnfoldedBinT->Draw("E1");
    hRatioUnfoldedSVDT->Draw("E1 SAME");
    hRatioTruthT->Draw("P SAME");

    TLegend* legRatioT = new TLegend(0.6, 0.75, 0.88, 0.88);
    legRatioT->AddEntry(hRatioUnfoldedBinT, "Matrix unfolding", "lep");
    legRatioT->AddEntry(hRatioUnfoldedSVDT, "SVD unfolding", "lep");
    legRatioT->AddEntry(hRatioTruthT, "Truth Ratio", "lep");
    legRatioT->Draw();

    cUnfoldRatio_T->SaveAs("unfolding_ratio_W2.png");
    
    // Plot the final ratio to check closeness to 1
    TCanvas* canvasRatio = new TCanvas("canvasRatio", "Final Ratio (Truth/Unfolded)", 1000, 700);
    hFinalRatioBin->SetStats(0);
    hFinalRatioSVD->SetStats(0);

    hFinalRatioBin->SetLineColor(kRed);
    hFinalRatioBin->SetLineWidth(2);
    hFinalRatioBin->SetTitle("Truth divided by unfolded");
    hFinalRatioBin->Draw("LP");
    hFinalRatioBin->GetXaxis()->SetTitle("LeadJetPt [GeV]"); 
    hFinalRatioBin->GetYaxis()->SetTitle("Truth / Unfolded"); 
    
    hFinalRatioSVD->SetLineColor(kBlue);
    hFinalRatioSVD->SetLineWidth(2);
    hFinalRatioSVD->SetTitle("Truth divided by unfolded");
    hFinalRatioSVD->GetXaxis()->SetTitle("LeadJetPt [GeV]"); 
    hFinalRatioSVD->GetYaxis()->SetTitle("Truth / Unfolded"); 
    hFinalRatioSVD->Draw("LP SAME");
    
    TLegend* legendRatio = new TLegend(0.7, 0.7, 0.9, 0.9);
    legendRatio->AddEntry(hFinalRatioBin, "Matrix", "l");
    legendRatio->AddEntry(hFinalRatioSVD, "SVD", "l");
    legendRatio->Draw();

    TLine *line1 = new TLine(hFinalRatioBin->GetXaxis()->GetXmin(), 1, hFinalRatioBin->GetXaxis()->GetXmax(), 1);
    line1->SetLineColor(kRed);
    line1->SetLineStyle(2); // Dashed line
    line1->SetLineWidth(2);
    line1->Draw("same");
    
    canvasRatio->SaveAs("final_ratio.png");

    TCanvas* canvasRatioS = new TCanvas("canvasRatioS", "Final Ratio (Truth/Unfolded)", 1000, 700);
    hFinalRatioBinS->SetStats(0);
    hFinalRatioSVDS->SetStats(0);

    hFinalRatioBinS->SetLineColor(kRed);
    hFinalRatioBinS->SetLineWidth(2);
    hFinalRatioBinS->GetYaxis()->SetRangeUser(0.5,5); 
    hFinalRatioBinS->GetXaxis()->SetRangeUser(30,1000); 
    hFinalRatioBinS->SetTitle("Truth divided by unfolded for Leadjetpt n>1");
    hFinalRatioBinS->Draw("LP");
    
    hFinalRatioSVDS->SetLineColor(kBlue);
    hFinalRatioSVDS->SetLineWidth(2);
    hFinalRatioSVDS->SetTitle("Truth divided by unfolded for Leadjetpt n>1");
    hFinalRatioSVDS->Draw("LP SAME");

    TLegend* legendRatioS = new TLegend(0.7, 0.7, 0.9, 0.9);
    legendRatioS->AddEntry(hFinalRatioBinS, "Matrix", "l");
    legendRatioS->AddEntry(hFinalRatioSVDS, "SVD", "l");
    legendRatioS->Draw();

    TLine *line2 = new TLine(hFinalRatioBinS->GetXaxis()->GetXmin(), 1, hFinalRatioBinS->GetXaxis()->GetXmax(), 1);
    line2->SetLineColor(kRed);
    line2->SetLineStyle(2); // Dashed line
    line2->SetLineWidth(2);
    line2->Draw("same");
    
    canvasRatioS->SaveAs("final_ratioS.png");

    TCanvas* canvasRatioT = new TCanvas("canvasRatioT", "Final Ratio (Truth/Unfolded)", 1000, 700);
    hFinalRatioBinT->SetStats(0);
    hFinalRatioSVDT->SetStats(0);

    hFinalRatioBinT->SetLineColor(kRed);
    hFinalRatioBinT->SetLineWidth(2);
    hFinalRatioBinT->GetXaxis()->SetRangeUser(30,1000);
    hFinalRatioBinT->SetTitle("Truth divided by unfolded for Leadjetpt n>1");
    hFinalRatioBinT->Draw("LP");

    hFinalRatioSVDT->SetLineColor(kBlue);
    hFinalRatioSVDT->SetLineWidth(2);
    hFinalRatioSVDT->SetTitle("Truth divided by unfolded for Leadjetpt n>1");
    hFinalRatioSVDT->Draw("LP SAME");

    TLegend* legendRatioT = new TLegend(0.7, 0.7, 0.9, 0.9);
    legendRatioT->AddEntry(hFinalRatioBinT, "Matrix", "l");
    legendRatioT->AddEntry(hFinalRatioSVDT, "SVD", "l");
    legendRatioT->Draw();

    TLine *line3 = new TLine(hFinalRatioBinT->GetXaxis()->GetXmin(), 1, hFinalRatioBinT->GetXaxis()->GetXmax(), 1);
    line3->SetLineColor(kRed);
    line3->SetLineStyle(2); // Dashed line
    line3->SetLineWidth(2);
    line3->Draw("same");
    
    canvasRatioT->SaveAs("final_ratioT.png");

    delete canvasRatio;
    delete legendRatio;

    // Cleanup
    fileLQW.Close();
    fileLQZ.Close();
    delete canvas_W;
    delete legend_W;
    fileLQZ.Close();
    fileLQZ.Close();
    delete canvas_Z;
    delete legend_Z;

    TFile outFile("unfolding_results.root", "RECREATE");
    
    // Write histograms to the file
    hUnfoldedBin_W->Write("hUnfoldedBin_W");
    hUnfoldedBin_Z->Write("hUnfoldedBin_Z");
    hUnfoldedSVD_W->Write("hUnfoldedSVD_W");
    hUnfoldedSVD_Z->Write("hUnfoldedSVD_Z");

    hRatioUnfoldedBin->Write("hRatioUnfoldedBin");
    hRatioUnfoldedSVD->Write("hRatioUnfoldedSVD");
    hRatioTruth->Write("hRatioTruth");
    hFinalRatioBin->Write("hFinalRatioBin");
    hFinalRatioSVD->Write("hFinalRatioSVD");

    // Close the file
    outFile.Close();

    std::cout << "Histograms saved to unfolding_results.root" << std::endl;

}