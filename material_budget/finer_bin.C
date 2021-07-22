{
        TH1::SetDefaultSumw2();
        TH2::SetDefaultSumw2();


        //TFile * myFile = new TFile("skimmed_pi-_det2_10x10_Beast_FastTrackingEval.root");

        TString name1 = "out_simp_geom_vbd_0.3_0.3_0.3_sPHENIX_FastSimEval";
        TString str_input = name1 + ".root";
        TString str_out = "output_" + name1 + ".root";

        TFile * Fint = new TFile(str_input);


        TTree * myTree = (TTree*) Fint -> Get("tracks");


        float px, py, pz, gpx, gpy, gpz, p, gp, eta;


        myTree -> SetBranchAddress("px",&px);
        myTree -> SetBranchAddress("gpx",&gpx);
        myTree -> SetBranchAddress("py",&py);
        myTree -> SetBranchAddress("gpy",&gpy);
        myTree -> SetBranchAddress("pz",&pz);
        myTree -> SetBranchAddress("gpz",&gpz);

        
        int total_number_of_entries = myTree -> GetEntries();
        
        gStyle->SetOptFit();

        

        TH1F ***hist= new TH1F **[30];

        for(int i = 0; i < 30; i++){
            hist[i] = new TH1F*[8];
                for(int j = 0; j < 8; j++){
                    float axis_ends = 2*(0.02 + (j / 40.));
                    float axis_middle = 2*(j/ 90.);
                    //for formatting axis limits
                    //must change based on the field strength sigma ~ 1/B
                    //for sPHENIX multiply everything by 2
                    if(j>1 && j<7){
                        
                        hist[i][j] = new TH1F(Form("h_%i_%i", i, j), Form("Momentum Resolution. #eta: %f - %f p: %d - %d GeV;(p-gp)/gp;counts", (j)/2., (j)/2.+0.5, (i), (i+1)), 50, -axis_middle, axis_middle );

                    }
                        else{
                           
                            hist[i][j] = new TH1F(Form("h_%i_%i", i, j), Form("Momentum Resolution. #eta: %f - %f p: %d - %d GeV;(p-gp)/gp;counts", (j)/2., (j)/2.+0.5, (i), (i+1)), 50, -axis_ends, axis_ends );

                        }                    
                }
        } 
        

            for( int entry = 0 ; entry < total_number_of_entries ; entry++ ){

                myTree -> GetEntry(entry);

                if( entry%(total_number_of_entries/20) == 0 ){cout << "Event "  << entry << " out of: " << total_number_of_entries << endl;}

                if(px == px){

                        p = sqrt(pow(px,2) + pow(py,2) + pow(pz,2));
                        gp = sqrt(pow(gpx,2) + pow(gpy,2) + pow(gpz,2));
                        eta = TMath::ATanH(pz/p);
                        
                        for(int j=0; j<8; j++){
                            if(eta>=(float)(j)/2. && eta<(float)(j)/2.+0.5){
                                for( int i = 0; i < 30; i++){
                                    if(p >= (float)(i) && p < (float)(i+1)){
                                            hist[i][j]->Fill((p-gp)/gp);
                                    }    
                                }
                            }
                        }

                }
            }

            //TFile * Fout = new TFile(str_out,"recreate");

            TCanvas **c= new TCanvas *[8];
            TF1  **fit = new TF1 *[8];
            double sigmas [8][30];
            double std_errs [8][30];
            for( int j=0; j<8; j++){
                c[j] = new TCanvas(Form("c_%i", j), Form("eta: %f - %f", (j)/2., (j)/2.+0.5));
                c[j]->Divide(5,1);
                //must change based on the field strength sigma ~ 1/B
                //for sPHENIX multiply everything by 2
                float fit_ends = 2*(0.02 + (j / 40.));
                float fit_middle = 2*(j/ 90.);
                //float fit_range_ends = ((1+j)/250.);
                //float fit_range_middle = ((1+j)/550.);
                //for formatting fit limits
                if(j>1 && j<7){
                        
                    fit[j] = new TF1("fit", "gaus", -fit_middle/2., fit_middle/2. );

                }
                
                else{
                           
                    fit[j] = new TF1("fit", "gaus", -fit_ends/2., fit_ends/2. );


                }                 


                for( int i = 0; i < 30; i++){
                    //c[j]->cd(i+1);
                    fit[j] -> SetParameters(0,0,0);
                    if(i>24){
                        c[j]->cd(i-24);
                        hist[i][j]->Fit("fit", "R");
                        }
                    //hist[i][j]->Fit("fit", "R");
                    //TF1 *test_gaus = new TF1("test_gaus", "gaus");
                    //hist[i][j]->Draw();
                    //hist[i][j]->Write(name1 + Form("_hist_%i_%i", i, j));
                    double par0 = fit[j] -> GetParameter(0);
                    double par1 = fit[j] -> GetParameter(1);
                    double std_dev = fit[j] -> GetParameter(2);
                    double std_err = fit[j] -> GetParError(2);
                    //test_gaus->SetParameters(par0,par1,std_dev);
                    //test_gaus->Draw("same");
                    sigmas[j][i] = std_dev * 100;
                    std_errs[j][i] = std_err * 100;
                    
                }
               
            }
}
    