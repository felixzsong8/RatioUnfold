//This is what i use for unfolding basic leadjetpt ratios, not SCND stuff

{
    gSystem->Load("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/RooUnfold/libRooUnfold");

    // Open ROOT file
    TFile fileLQW("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisWMil.root");
    TFile fileLQZ("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisZMil.root");

    // Retrieve histograms
    TH1F *hRecoW = (TH1F*)fileLQW.Get("LeadRecoJet_inc_pt"); 
    TH1F *hTrueW = (TH1F*)fileLQW.Get("LeadTrueJet_inc_pt");  

    TH1F *hRecoZ = (TH1F*)fileLQZ.Get("LeadRecoJet_inc_pt"); 
    TH1F *hTrueZ = (TH1F*)fileLQZ.Get("LeadTrueJet_inc_pt"); 


     

    if (!hRecoW || !hTrueW) {
        std::cerr << "Error: One or more histograms not found!" << std::endl;
        return;
    }
    if (!hRecoZ || !hTrueZ) {
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
                std::vector<bool> truth_matched(truth_pT->size(), false);
                std::vector<bool> reco_matched(reco_pT->size(), false);
                
                // Fill response matrix with matched reco-truth jets
                for (size_t j = 0; j < reco_pT->size(); j++) {
                    if (reco_pT->at(j) > 0 && truth_pT->at(j) > 0) {
                        responseW.Fill(reco_pT->at(j), truth_pT->at(j));
                        truth_matched[j] = true;
                        reco_matched[j] = true;
                    }
                }

                // Fill missed truth jets
                for (size_t j = 0; j < truth_pT->size(); j++) {
                    if (!truth_matched[j] && truth_pT->at(j) > 0) {
                        responseW.Miss(truth_pT->at(j));
                    }
                }

                // Fill fake reco jets
                for (size_t j = 0; j < reco_pT->size(); j++) {
                    if (!reco_matched[j] && reco_pT->at(j) > 0) {
                        responseW.Fake(reco_pT->at(j));
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
                std::vector<bool> truth_matched(truth_pT->size(), false);
                std::vector<bool> reco_matched(reco_pT->size(), false);

                // Fill response matrix with matched reco-truth jets
                for (size_t j = 0; j < reco_pT->size(); j++) {
                    if (reco_pT->at(j) > 0 && truth_pT->at(j) > 0) {
                        responseZ.Fill(reco_pT->at(j), truth_pT->at(j));
                        truth_matched[j] = true;
                        reco_matched[j] = true;
                    }
                }

                // Fill missed truth jets
                for (size_t j = 0; j < truth_pT->size(); j++) {
                    if (!truth_matched[j] && truth_pT->at(j) > 0) {
                        responseZ.Miss(truth_pT->at(j));
                    }
                }

                // Fill fake reco jets
                for (size_t j = 0; j < reco_pT->size(); j++) {
                    if (!reco_matched[j] && reco_pT->at(j) > 0) {
                        responseZ.Fake(reco_pT->at(j));
                    }
                }
            }
        }
    }
    

    // Perform unfolding
    responseW.UseOverflow(false);
    responseZ.UseOverflow(false);
    //For W
    auto* RW = responseW.HresponseNoOverflow();
    auto* c1 = new TCanvas("c1", "Unfolding Results", 2000, 900);
    RW->SetStats(0);
    RW->Draw("colz");
    RW->SetTitle("Reponse Matrix Colormap for W+jets");
    RW->GetXaxis()->SetTitle("Reco Jet p_{T} [GeV]");
    RW->GetYaxis()->SetTitle("Truth Jet p_{T} [GeV]");
    c1->Draw();
    c1->SaveAs("responseW.png");
    //For Z
    auto* RZ = responseZ.HresponseNoOverflow();
    auto* c2 = new TCanvas("c2", "Unfolding Results", 2000, 900);
    RZ->SetStats(0);
    RZ->Draw("colz");
    RZ->SetTitle("Reponse Matrix Colormap for Z+jets");
    RZ->GetXaxis()->SetTitle("Reco Jet p_{T} [GeV]");
    RZ->GetYaxis()->SetTitle("Truth Jet p_{T} [GeV]");
    c2->Draw();
    c2->SaveAs("responseZ.png");


    // Bin-by-bin unfolding
    RooUnfoldBinByBin unfoldBin_W(&responseW, hRecoW);
    RooUnfoldBinByBin unfoldBin_Z(&responseZ, hRecoZ);
    TH1F *hUnfoldedBin_W = (TH1F*) unfoldBin_W.Hreco();
    TH1F *hUnfoldedBin_Z = (TH1F*) unfoldBin_Z.Hreco();


    // SVD unfolding with regularization parameter k=5
    int kReg = 4;  // Adjust this value to control the regularization strength
    RooUnfoldSvd unfoldSVD_W(&responseW, hRecoW, kReg);
    RooUnfoldSvd unfoldSVD_Z(&responseZ, hRecoZ, kReg);
    TH1F *hUnfoldedSVD_W = (TH1F*) unfoldSVD_W.Hreco();
    TH1F *hUnfoldedSVD_Z = (TH1F*) unfoldSVD_Z.Hreco();

    //Importing test data
    TFile fileLQTW("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisWtest.root");
    TFile fileLQTZ("/Users/felixsong/Desktop/coding-tufts/SeniorThesis/analyze-pythia/analysisZtest.root");
    TH1F *hTrueTW = (TH1F*)fileLQTW.Get("LeadTrueJet_inc_pt"); 
    TH1F *hTrueTZ = (TH1F*)fileLQTZ.Get("LeadTrueJet_inc_pt"); 

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

    

    // Plot results
    TCanvas *canvas_W = new TCanvas("canvasW", "Unfolding Results", 1000, 700);
    canvas_W->SetLogy();
    hUnfoldedBin_W->SetStats(0);
    hUnfoldedSVD_W->SetStats(0);
    hRecoW->SetStats(0);
    hTrueTW->SetStats(0);

    // Draw bin-by-bin unfolding
    hUnfoldedBin_W->SetLineColor(kRed);
    hUnfoldedBin_W->SetLineWidth(2);
    hUnfoldedBin_W->Draw("HIST SAME");

    // Draw SVD unfolding
    hUnfoldedSVD_W->SetLineColor(kMagenta);
    hUnfoldedSVD_W->SetLineWidth(2);
    hUnfoldedSVD_W->Draw("HIST SAME");

    // Draw measured histogram
    hRecoW->SetLineColor(kBlue);
    hRecoW->SetLineWidth(2);
    hRecoW->Draw("HIST SAME");

    // Draw true histogram
    hTrueTW->SetLineColor(kGreen);
    hTrueTW->SetLineWidth(2);
    hTrueTW->Draw("HIST SAME");

    hUnfoldedBin_W->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    hUnfoldedBin_W->GetYaxis()->SetTitle("Events per bin");

    hUnfoldedSVD_W->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    hUnfoldedSVD_W->GetYaxis()->SetTitle("Events per bin");

    hRecoW->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    hRecoW->GetYaxis()->SetTitle("Events per bin");

    hTrueTW->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    hTrueTW->GetYaxis()->SetTitle("Events per bin");

    // Create legend
    TLegend *legend_W = new TLegend(0.65, 0.65, 0.9, 0.9);
    legend_W->AddEntry(hUnfoldedBin_W, "Matrix Unfolded", "l");
    legend_W->AddEntry(hUnfoldedSVD_W, "SVD Unfolded", "l");
    legend_W->AddEntry(hRecoW, "Reco", "l");
    legend_W->AddEntry(hTrueTW, "Truth", "l");
    legend_W->Draw();

    //canvas_W->SetTitle("Unfolding Comparison for W+jets");
    canvas_W->SetTitle("");
    hUnfoldedBin_W->SetTitle("");
    hUnfoldedSVD_W->SetTitle("");
    hRecoW->SetTitle("");
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

    hUnfoldedBin_Z->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    hUnfoldedBin_Z->GetYaxis()->SetTitle("Events per bin");

    hUnfoldedSVD_Z->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    hUnfoldedSVD_Z->GetYaxis()->SetTitle("Events per bin");

    hRecoZ->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    hRecoZ->GetYaxis()->SetTitle("Events per bin");

    hTrueTZ->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    hTrueTZ->GetYaxis()->SetTitle("Events per bin");

    // Create legend
    TLegend *legend_Z = new TLegend(0.65, 0.65, 0.9, 0.9);
    legend_Z->AddEntry(hUnfoldedBin_W, "Matrix Unfolded", "l");
    legend_Z->AddEntry(hUnfoldedSVD_W, "SVD Unfolded", "l");
    legend_Z->AddEntry(hRecoW, "Reco", "l");
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

    
    
    
    // Plot the final ratio to check closeness to 1
    TCanvas* canvasRatio = new TCanvas("canvasRatio", "Final Ratio (Truth/Unfolded)", 1000, 700);
    hFinalRatioBin->SetStats(0);
    hFinalRatioSVD->SetStats(0);

    hFinalRatioBin->SetLineColor(kRed);
    hFinalRatioBin->SetLineWidth(2);
    hFinalRatioBin->SetTitle("Truth divided by unfolded");
    hFinalRatioBin->Draw("HIST");
    
    hFinalRatioSVD->SetLineColor(kBlue);
    hFinalRatioSVD->SetLineWidth(2);
    hFinalRatioSVD->SetTitle("Truth divided by unfolded");
    hFinalRatioSVD->Draw("HIST SAME");
    
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