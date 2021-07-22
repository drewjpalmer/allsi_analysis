{
	//comparing simplified geometry fastSim events for 5 disk geometry and equidistant 7 disk geometry
	TH1::SetDefaultSumw2();
	gStyle->SetOptStat("");
	TH2::SetDefaultSumw2();
	TString name1 = "out_simp_geom_Beast_result_five_cone"; //old Beast
	TString str_input1 = "output_" + name1 + ".root";
	TString name2 = "out_simp_geom_sPHENIX_result_five_cone"; //old sPHENIX
	TString str_input2 = "output_" + name2 + ".root";
	TString name3 = "out_simp_geom_Beast_result_seven_cone"; //new Beast (7 disk)
	TString str_input3 = "output_" + name3 + ".root";
	TString name4 = "out_simp_geom_sPHENIX_result_seven_cone"; //new sPHENIX (7 disk)
	TString str_input4 = "output_" + name4 + ".root";

	TFile *file1 = new TFile(str_input1);
	TFile *file2 = new TFile(str_input2);
	TFile *file3 = new TFile(str_input3);
	TFile *file4 = new TFile(str_input4);
	
	gStyle->SetOptFit();
	gStyle->SetCanvasDefH(800);
	gStyle->SetCanvasDefW(1500); 
	TH1F ***hist1 = new TH1F **[6];
	TH1F ***hist3 = new TH1F **[6];
	TH1F **sigma1 = new TH1F *[6];
	TH1F **sigma3 = new TH1F *[6];
	TH1F **sigmab = new TH1F *[6];
	TF1 ***myfit1 = new TF1 **[6];
	TF1 ***myfit3 = new TF1 **[6];

	
	TH1F ***hist2 = new TH1F **[6];
	TH1F ***hist4 = new TH1F **[6];
	TH1F **sigma2 = new TH1F *[6];
	TH1F **sigma4 = new TH1F *[6];
	TH1F **sigmas = new TH1F *[6];
	TF1 ***myfit2 = new TF1 **[6];
	TF1 ***myfit4 = new TF1 **[6];

	double std1 [6][8];
	double std2 [6][8];
	double std3 [6][8];
	double std4 [6][8];
	double std1_err [6][8];
	double std2_err [6][8];
	double std3_err [6][8];
	double std4_err [6][8];

	TCanvas *mom_canvas_b = new TCanvas("mom_canvas_b", "Momentum resolution in p bins for 3.0T Beast map");
	mom_canvas_b->Divide(3,2);

	TCanvas *mom_canvas_s = new TCanvas("mom_canvas_s", "Momentum resolution in p bins for 1.4T sPHENIX map");
	mom_canvas_s->Divide(3,2);
	
	for (int i = 0; i < 6; i++){

		hist1[i] = new TH1F *[8];
		hist2[i] = new TH1F *[8];
		hist3[i] = new TH1F *[8];
		hist4[i] = new TH1F *[8];

		myfit1[i] = new TF1 *[8];
		myfit2[i] = new TF1 *[8];
		myfit3[i] = new TF1 *[8];
		myfit4[i] = new TF1 *[8];
		
		sigma1[i] = new TH1F(Form("Sigma1_h_%i", i), "Momentum resolution1", 8, 0, 4); 
		sigma2[i] = new TH1F(Form("Sigma2_h_%i", i), "Momentum resolution2", 8, 0, 4); 
		sigma3[i] = new TH1F(Form("Sigma3_h_%i", i), "Momentum resolution3", 8, 0, 4); 
		sigma4[i] = new TH1F(Form("Sigma4_h_%i", i), "Momentum resolution4", 8, 0, 4); 
		
		for (int j = 0; j < 8; j++){

			hist1[i][j] = (TH1F *)file1->Get(name1 + Form("_hist_%i_%i", i, j));
			myfit1[i][j] = hist1[i][j]->GetFunction("fit");
			std1[i][j] = myfit1[i][j]->GetParameter(2);
			sigma1[i]->SetBinContent(j+1, std1[i][j]);
			std1_err[i][j] = myfit1[i][j]->GetParError(2);
			sigma1[i]->SetBinError(j+1, std1_err[i][j]); 
			
			hist2[i][j] = (TH1F *)file2->Get(name2 + Form("_hist_%i_%i", i, j));
			myfit2[i][j] = hist2[i][j]->GetFunction("fit");
			std2[i][j] = myfit2[i][j]->GetParameter(2);
			sigma2[i]->SetBinContent(j+1, std2[i][j]); 
			std2_err[i][j] = myfit2[i][j]->GetParError(2);
			sigma2[i]->SetBinError(j+1, std2_err[i][j]); 

			hist3[i][j] = (TH1F *)file3->Get(name3 + Form("_hist_%i_%i", i, j));
			myfit3[i][j] = hist3[i][j]->GetFunction("fit"); 
			std3[i][j] = myfit3[i][j]->GetParameter(2); 
			sigma3[i]->SetBinContent(j+1, std3[i][j]); 
			std3_err[i][j] = myfit3[i][j]->GetParError(2);
			sigma3[i]->SetBinError(j+1, std3_err[i][j]); 

			hist4[i][j] = (TH1F *)file4->Get(name4 + Form("_hist_%i_%i", i, j));
			myfit4[i][j] = hist4[i][j]->GetFunction("fit");
			std4[i][j] = myfit4[i][j]->GetParameter(2);
			sigma4[i]->SetBinContent(j+1, std4[i][j]); 
			std4_err[i][j] = myfit4[i][j]->GetParError(2);
			sigma4[i]->SetBinError(j+1, std4_err[i][j]); 

			}

		mom_canvas_b->cd(i+1)->SetGridy();	
		sigmab[i] = (TH1F*)sigma3[i]->Clone(Form("_mom_res_b_%i", i));
		sigmab[i]->Divide(sigma1[i]);
		sigmab[i]->SetTitle(Form("7-disk/5-disk  p: %d - %d GeV;#eta;7-disk / 5-disk Momentum Resolution", (i * 5), ((i * 5) + 5))); 
		sigmab[i]->SetFillColor(41);
		sigmab[i]->SetStats(false);
		sigmab[i]->SetMarkerColor(kBlue);
		sigmab[i]->SetMarkerStyle(5);	
		sigmab[i]->Draw("E3");
		sigmab[i]->Draw("same EX0");
		TLine *lineb = new TLine(0,1,4,1);
           	lineb -> Draw("A");
           	lineb -> SetLineColor(2);	

		mom_canvas_s->cd(i+1)->SetGridy();
		sigmas[i] = (TH1F*)sigma4[i]->Clone(Form("_mom_res_s_%i", i));
		sigmas[i]->Divide(sigma2[i]);
		sigmas[i]->SetTitle(Form("7-disk/5-disk  p: %d - %d GeV;#eta;7-disk / 5-disk Momentum Resolution", (i * 5), ((i * 5) + 5))); 
		sigmas[i]->SetFillColor(41);
		sigmas[i]->SetStats(false);
		sigmas[i]->SetMarkerColor(kBlue);
		sigmas[i]->SetMarkerStyle(5);
		sigmas[i]->Draw("E3");
		sigmas[i]->Draw("same EX0");
		TLine *lines = new TLine(0,1,4,1);
           	lines -> Draw("A");
           	lines -> SetLineColor(2);	
	}
}
