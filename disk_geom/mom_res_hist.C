{
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();

	//TFile * myFile = new TFile("skimmed_pi-_det2_10x10_Beast_FastTrackingEval.root");

	TString name1 = "out_simp_geom_Beast_result_seven_cone";
	TString str_input = name1 + ".root";
	TString str_out = "output_" + name1 + ".root";

	TFile *Fint = new TFile(str_input);

	TTree *myTree = (TTree *)Fint->Get("tracks");

	float px, py, pz, gpx, gpy, gpz, p, gp, eta;

	myTree->SetBranchAddress("px", &px);
	myTree->SetBranchAddress("gpx", &gpx);
	myTree->SetBranchAddress("py", &py);
	myTree->SetBranchAddress("gpy", &gpy);
	myTree->SetBranchAddress("pz", &pz);
	myTree->SetBranchAddress("gpz", &gpz);

	int total_number_of_entries = myTree->GetEntries();

	gStyle->SetOptFit();
	gStyle->SetCanvasDefH(800);
	gStyle->SetCanvasDefW(1500);

	TH1F ***hist = new TH1F **[6];

	//TH1F *dist = new TH1F("momentum_dist", "Momentum Resolution distibution in momentum: p:counts", 50, -8, 8);

	for (int i = 0; i < 6; i++)
	{
		hist[i] = new TH1F *[8];
		for (int j = 0; j < 8; j++)
		{
			//for Beast
			//float axis_ends = (0.02 + (j / 40.));
			//float axis_middle = (j / 90.);
			//for formatting axis limits
			//must change based on the field strength sigma ~ 1/B
			//for sPHENIX, multiply everything by 2
			float axis_ends = 1*(0.02 + (j / 60.));
			float axis_middle = 1*(j / 90.);
			if (j > 1 && j < 7)
			{

				hist[i][j] = new TH1F(Form("h_%i_%i", i, j), Form("Momentum Resolution. #eta: %.1f - %.1f p: %d - %d GeV;(p-gp)/gp;counts", (j) / 2., (j) / 2. + 0.5, (i * 5), ((i * 5) + 5)), 50, -axis_middle, axis_middle);
			}
			else
			{

				hist[i][j] = new TH1F(Form("h_%i_%i", i, j), Form("Momentum Resolution. #eta: %.1f - %.1f p: %d - %d GeV;(p-gp)/gp;counts", (j) / 2., (j) / 2. + 0.5, (i * 5), ((i * 5) + 5)), 50, -axis_ends, axis_ends);
			}
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
							hist[i][j]->Fill((p - gp) / gp);
						}
					}
				}
			}
			//dist->Fill(p);
		}
	}

	TFile *Fout = new TFile(str_out, "RECREATE");

	TCanvas **c = new TCanvas *[8];
	TF1 **fit = new TF1 *[8];
	double sigmas[8][6];
	double std_errs[8][6];


	for (int j = 0; j < 8; j++)
	{
		c[j] = new TCanvas(Form("c_%i", j), Form("eta: %.1f - %.1f", (j) / 2., (j) / 2. + 0.5));
		c[j]->Divide(3, 2);
		//for Beast
		//float fit_ends = (0.02 + (j / 40.));
		//float fit_middle = (j / 90.);
		//must change based on the field strength sigma ~ 1/B
		//for sPHENIX multiply everything by 2
		float fit_ends = 1*(0.015 + (j / 100.));
		float fit_middle = 1*(j / 150.);
		//for formatting fit limits
		if (j > 1 && j < 7)
		{

			fit[j] = new TF1("fit", "gaus", -fit_middle / 2., fit_middle / 2.);
		}

		else
		{

			fit[j] = new TF1("fit", "gaus", -fit_ends / 2., fit_ends / 2.);
		}

		for (int i = 0; i < 6; i++)
		{
			c[j]->cd(i + 1);
			fit[j]->SetParameters(0, 0, 0);
			hist[i][j]->Fit("fit", "R");
			//TF1 *test_gaus = new TF1("test_gaus", "gaus");
			hist[i][j]->Draw();
			hist[i][j]->Write(name1 + Form("_hist_%i_%i", i, j));

			double par0 = fit[j]->GetParameter(0);
			double par1 = fit[j]->GetParameter(1);
			double std_dev = fit[j]->GetParameter(2);
			double std_err = fit[j]->GetParError(2);
			//test_gaus->SetParameters(par0,par1,std_dev);
			//test_gaus->Draw("same");
			sigmas[j][i] = std_dev * 100;
			std_errs[j][i] = std_err * 100;
		}
	}
	double p_axis_values[6] = {2.5, 7.5, 12.5, 17.5, 22.5, 27.5};
	TCanvas *c_sigma = new TCanvas("c_sigma", "Sigmas Graph");
	TMultiGraph *mg = new TMultiGraph();
	mg->SetTitle("Momentum Resolution in p bins;p [GeV/c];dp/p [%]");
	TLegend *leg = new TLegend(0, 0.75, .3, .93);

	for (int j = 0; j < 8; j++)
	{
		//double ey[6] = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5};
		TGraphErrors *graph = new TGraphErrors(6, p_axis_values, sigmas[j], 0, std_errs[j]);
		//TCanvas * c_temp = new TCanvas("temp", "temp");
		graph->SetMarkerColor(j + 1);
		graph->SetLineColor(j + 1);
		graph->SetMarkerStyle(20 + j);
		//graph->Write(name1 + Form("_graph_%i", j));
		//graph->SetTitle(Form("#eta: %f - %f", (j)/2., (j)/2.+0.5));
		leg->AddEntry(graph, Form("#eta: %.1f - %.1f", int(((j) / 2.) * 100 + .5) / 100., int((((j) / 2.) + .5) * 100 + .5) / 100.), "p");
		mg->Add(graph, "PZ");
	}
	//mg->Draw("A");
	mg->GetXaxis()->SetRangeUser(0, 30);
	//const char *gev_bins[6]  = {"0-5 GeV", "5-10 Gev", "10-15 GeV", "15-20 Gev", "20-25 GeV", "25-30 GeV"};
	leg->SetNColumns(2);
	leg->SetHeader("#eta Ranges");
	leg->Draw();
	mg->GetXaxis()->SetNdivisions(7, kTRUE);
	mg->GetXaxis()->CenterTitle(true);
	mg->GetYaxis()->CenterTitle(true);
	mg->SetMinimum(0.);

	//mg->Write(name1 + "_graph");
	//leg->Write(name1 + "_legend");

	//non binned plots to see the data
	//TCanvas * c_dist = new TCanvas("c_dist", "distrbution Graph");
	//dist->Draw("*H");

	Fout->Close();
}
