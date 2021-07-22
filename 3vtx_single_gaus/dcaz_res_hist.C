{
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();

	//TFile * myFile = new TFile("skimmed_pi-_det2_10x10_Beast_FastTrackingEval.root");

	TString name1 = "out_simp_geom_3vtx_sPHENIX_FastSimEval";
	TString str_input = name1 + ".root";
	TString str_out = "dcaz_output_" + name1 + ".root";

	TFile *Fint = new TFile(str_input);

	TTree *myTree = (TTree *)Fint->Get("tracks");

	float px, py, pz, gpx, gpy, gpz, p, gp, eta, dca2d, pcaz, gvz;

	myTree->SetBranchAddress("px", &px);
	myTree->SetBranchAddress("gpx", &gpx);
	myTree->SetBranchAddress("py", &py);
	myTree->SetBranchAddress("gpy", &gpy);
	myTree->SetBranchAddress("pz", &pz);
	myTree->SetBranchAddress("gpz", &gpz);
	myTree->SetBranchAddress("dca2d", &dca2d);
	myTree->SetBranchAddress("pcaz", &pcaz);
	myTree->SetBranchAddress("gvz", &gvz);

	int total_number_of_entries = myTree->GetEntries();

	gStyle->SetOptFit();
	gStyle->SetCanvasDefH(800);
	gStyle->SetCanvasDefW(1500);

	TH1F ***hist_range = new TH1F **[6];
	TH1F ***hist = new TH1F **[6];

	double fit_width[8][6];
	double axis_range[8][6];


	TH1F *dist = new TH1F("dcaz_dist", "Longitudinal DCA Resolution distibution in momentum: p:counts", 50, -1000., 1000.);


	float test_axis = 50.; //set this and plot so all data are in range	

	for (int i=0; i<6; i++){	

		hist_range[i] = new TH1F *[8];

		for (int j=0; j<8; j++){	

			hist_range[i][j] = new TH1F(Form("h_range_%i_%i", i, j), Form("Longitudinal DCA Resolution. #eta: %.1f - %.1f p: %d - %d GeV;#mum;counts", (j) / 2., (j) / 2. + 0.5, (i * 5), ((i * 5) + 5)), 500, -test_axis*(j+1)*(j+1)*(j+1), test_axis*(j+1)*(j+1)*(j+1));
		}
	}
	for (int entry = 0; entry < total_number_of_entries; entry++)
	{

		myTree->GetEntry(entry);

		if (entry % (total_number_of_entries / 20) == 0)
		{
			cout << "Event " << entry << " out of: " << total_number_of_entries << endl;
		}

		if (px == px)
		{

			p = sqrt(pow(px, 2) + pow(py, 2) + pow(pz, 2));
			gp = sqrt(pow(gpx, 2) + pow(gpy, 2) + pow(gpz, 2));
			eta = TMath::ATanH(pz / p);

			for (int j = 0; j < 8; j++)
			{
				if (eta >= (float)(j) / 2. && eta < (float)(j) / 2. + 0.5)
				{
					for (int i = 0; i < 6; i++)
					{

						if (p >= (float)(i * 5) && p < (float)((i * 5) + 5))
						{
							hist_range[i][j]->Fill((pcaz - gvz) * 10000.);
						}

							fit_width[j][i] = hist_range[i][j]->GetStdDev();
							axis_range[j][i] = fit_width[j][i]*4.;
					}
				}
			}
			dist->Fill((pcaz - gvz) * 10000.);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		hist[i] = new TH1F *[8];

		for (int j = 0; j < 8; j++)
		{

			hist[i][j] = new TH1F(Form("h_%i_%i", i, j), Form("Longitudinal DCA Resolution. #eta: %.1f - %.1f p: %d - %d GeV;#mum;counts", (j) / 2., (j) / 2. + 0.5, (i * 5), ((i * 5) + 5)), 100, -axis_range[j][i], axis_range[j][i]);

		}
	}


	for (int entry = 0; entry < total_number_of_entries; entry++)
	{

		myTree->GetEntry(entry);

		if (entry % (total_number_of_entries / 20) == 0)
		{
			cout << "Event " << entry << " out of: " << total_number_of_entries << endl;
		}

		if (px == px)
		{

			p = sqrt(pow(px, 2) + pow(py, 2) + pow(pz, 2));
			gp = sqrt(pow(gpx, 2) + pow(gpy, 2) + pow(gpz, 2));
			eta = TMath::ATanH(pz / p);

			for (int j = 0; j < 8; j++)
			{
				if (eta >= (float)(j) / 2. && eta < (float)(j) / 2. + 0.5)
				{
					for (int i = 0; i < 6; i++)
					{

						if (p >= (float)(i * 5) && p < (float)((i * 5) + 5))
						{
							hist[i][j]->Fill((pcaz - gvz) * 10000.);
						}

					}
				}
			}

		}
	}



	TFile *Fout = new TFile(str_out, "RECREATE");

	TCanvas **c = new TCanvas *[8];
	TF1 ***fit = new TF1 **[8];

	double sigmas[8][6];
	double std_errs[8][6];


	for (int j = 0; j < 8; j++)
	{
		c[j] = new TCanvas(Form("c_%i", j), Form("eta: %.1f - %.1f", (j) / 2., (j) / 2. + 0.5));
		fit[j] = new TF1 *[6];
		c[j]->Divide(3, 2);
		
		for (int i = 0; i < 6; i++){
			float fit_range = fit_width[j][i];

			fit[j][i] = new TF1("fit", "gaus(0)", -fit_range*1.5, fit_range*1.5);

			c[j]->cd(i + 1);
			fit[j][i]->SetParameters(hist[i][j]->GetMaximum(), 0, fit_range);
			fit[j][i]->SetParLimits(1, -10*j, 10*j);
			fit[j][i]->SetParLimits(0, hist[i][j]->GetMaximum()*.95, hist[i][j]->GetMaximum()*1.05);

			fit[j][i]->SetParLimits(2, fit_range*.5, fit_range*1.5 );

			hist[i][j]->Fit("fit", "R");	
			hist_range[i][j]->Draw();
			hist[i][j]->Write(name1 + Form("_hist_%i_%i", i, j));

			double par0 = fit[j][i]->GetParameter(0);
			double par1 = fit[j][i]->GetParameter(1);
			double std_dev1 = fit[j][i]->GetParameter(2);
			double std_err1 = fit[j][i]->GetParError(2);	
	


		}
	}

	//non binned plots to see the data
	TCanvas * c_dist = new TCanvas("c_dist", "distrbution Graph");
	
	dist->Draw("*H");

	Fout->Close();
}
