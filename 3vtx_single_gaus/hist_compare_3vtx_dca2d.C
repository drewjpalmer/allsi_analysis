{
	//comparing simplified geometry fastSim events for 5 disk geometry and equidistant 7 disk geometry
	TH1::SetDefaultSumw2();
	gStyle->SetOptStat("");
	TH2::SetDefaultSumw2();
	TString name1 = "out_simp_geom_2vtx_Beast_FastSimEval"; //old Beast
	TString str_input1 = "dca2d_output_" + name1 + ".root";
	TString name2 = "out_simp_geom_2vtx_sPHENIX_FastSimEval"; //old sPHENIX
	TString str_input2 = "dca2d_output_" + name2 + ".root";
	TString name3 = "out_simp_geom_3vtx_Beast_FastSimEval"; //new Beast (3 vtx)
	TString str_input3 = "dca2d_output_" + name3 + ".root";
	TString name4 = "out_simp_geom_3vtx_sPHENIX_FastSimEval"; //new sPHENIX (3 vtx)
	TString str_input4 = "dca2d_output_" + name4 + ".root";

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
	double std12 [6][8];
	double std22 [6][8];
	double std32 [6][8];
	double std42 [6][8];
	double std1_err [6][8];
	double std2_err [6][8];
	double std3_err [6][8];
	double std4_err [6][8];

	TCanvas *mom_canvas_b = new TCanvas("mom_canvas_b", "Transverse DCA resolution in p bins for 3.0T Beast map");
	mom_canvas_b->Divide(3,2);

	TCanvas *mom_canvas_s = new TCanvas("mom_canvas_s", "Transverse DCA resolution in p bins for 1.4T sPHENIX map");
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

		sigma1[i] = new TH1F(Form("Sigma1_h_%i", i), "Momentum resolution1", 7, 0, 3.5); 
		sigma2[i] = new TH1F(Form("Sigma2_h_%i", i), "Momentum resolution2", 7, 0, 3.5); 
		sigma3[i] = new TH1F(Form("Sigma3_h_%i", i), "Momentum resolution3", 7, 0, 3.5); 
		sigma4[i] = new TH1F(Form("Sigma4_h_%i", i), "Momentum resolution4", 7, 0, 3.5); 

		for (int j = 0; j < 7; j++){

			hist1[i][j] = (TH1F *)file1->Get(name1 + Form("_hist_%i_%i", i, j));
			myfit1[i][j] = hist1[i][j]->GetFunction("fit");
			std1[i][j] = myfit1[i][j]->GetParameter(2);
			std12[i][j] = myfit1[i][j]->GetParameter(2);
			if (std1[i][j] < std12[i][j])
			{
				sigma1[i]->SetBinContent(j+1, std1[i][j]);
				std1_err[i][j] = myfit1[i][j]->GetParError(2);
				sigma1[i]->SetBinError(j+1, std1_err[i][j]);
			}
			else
			{	
				sigma1[i]->SetBinContent(j+1, std12[i][j]);
				std1_err[i][j] = myfit1[i][j]->GetParError(2);
				sigma1[i]->SetBinError(j+1, std1_err[i][j]);
			}

			hist2[i][j] = (TH1F *)file2->Get(name2 + Form("_hist_%i_%i", i, j));
			myfit2[i][j] = hist2[i][j]->GetFunction("fit");
			std2[i][j] = myfit2[i][j]->GetParameter(2);
			std22[i][j] = myfit2[i][j]->GetParameter(2);
			if (std2[i][j] < std22[i][j])
			{
				sigma2[i]->SetBinContent(j+1, std2[i][j]);
				std2_err[i][j] = myfit2[i][j]->GetParError(2);
				sigma2[i]->SetBinError(j+1, std2_err[i][j]);
			}
			else
			{	
				sigma2[i]->SetBinContent(j+1, std22[i][j]);
				std2_err[i][j] = myfit2[i][j]->GetParError(2);
				sigma2[i]->SetBinError(j+1, std2_err[i][j]);
			}

			hist3[i][j] = (TH1F *)file3->Get(name3 + Form("_hist_%i_%i", i, j));
			myfit3[i][j] = hist3[i][j]->GetFunction("fit");
			std3[i][j] = myfit3[i][j]->GetParameter(2);
			std32[i][j] = myfit3[i][j]->GetParameter(2);
			if (std3[i][j] < std32[i][j])
			{
				sigma3[i]->SetBinContent(j+1, std3[i][j]);
				std3_err[i][j] = myfit3[i][j]->GetParError(2);
				sigma3[i]->SetBinError(j+1, std3_err[i][j]);
			}
			else
			{	
				sigma3[i]->SetBinContent(j+1, std32[i][j]);
				std3_err[i][j] = myfit3[i][j]->GetParError(2);
				sigma3[i]->SetBinError(j+1, std3_err[i][j]);
			}

			hist4[i][j] = (TH1F *)file4->Get(name4 + Form("_hist_%i_%i", i, j));
			myfit4[i][j] = hist4[i][j]->GetFunction("fit");
			std4[i][j] = myfit4[i][j]->GetParameter(2);
			std42[i][j] = myfit4[i][j]->GetParameter(2);
			if (std4[i][j] < std42[i][j])
			{
				sigma4[i]->SetBinContent(j+1, std4[i][j]);
				std4_err[i][j] = myfit4[i][j]->GetParError(2);
				sigma4[i]->SetBinError(j+1, std4_err[i][j]);
			}
			else
			{	
				sigma4[i]->SetBinContent(j+1, std42[i][j]);
				std4_err[i][j] = myfit4[i][j]->GetParError(2);
				sigma4[i]->SetBinError(j+1, std4_err[i][j]);
			}

		}

		mom_canvas_b->cd(i+1)->SetGridy();	
		sigmab[i] = (TH1F*)sigma3[i]->Clone(Form("_dca2d_res_b_%i", i));
		sigmab[i]->Divide(sigma1[i]);
		sigmab[i]->SetTitle(Form("3-vtx/2-vtx  p: %d - %d GeV;#eta;3-vtx / 2-vtx Transverse DCA Resolution", (i * 5), ((i * 5) + 5))); 
		sigmab[i]->SetFillColor(41);
		sigmab[i]->SetStats(false);
		sigmab[i]->SetMarkerColor(kBlue);
		sigmab[i]->SetMarkerStyle(5);	
		sigmab[i]->Draw("E3");
		sigmab[i]->Draw("same EX0");
		TLine *lineb = new TLine(0,1,3.5,1);
		lineb -> Draw("A");
		lineb -> SetLineColor(2);	

		mom_canvas_s->cd(i+1)->SetGridy();
		sigmas[i] = (TH1F*)sigma4[i]->Clone(Form("_dca2d_res_s_%i", i));
		sigmas[i]->Divide(sigma2[i]);
		sigmas[i]->SetTitle(Form("3-vtx/2-vtx  p: %d - %d GeV;#eta;3-vtx / 2-vtx Transverse DCA Resolution", (i * 5), ((i * 5) + 5))); 
		sigmas[i]->SetFillColor(41);
		sigmas[i]->SetStats(false);
		sigmas[i]->SetMarkerColor(kBlue);
		sigmas[i]->SetMarkerStyle(5);
		sigmas[i]->Draw("E3");
		sigmas[i]->Draw("same EX0");
		TLine *lines = new TLine(0,1,3.5,1);
		lines -> Draw("A");
		lines -> SetLineColor(2);	
	}
}
