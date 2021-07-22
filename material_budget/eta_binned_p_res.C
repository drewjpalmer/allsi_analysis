{
TH1::SetDefaultSumw2();
TH2::SetDefaultSumw2();


//TFile * myFile = new TFile("out_simp_geom_vbd_0.3_0.3_0.3_Beast_FastSimEval.root");

TString name1 = "out_simp_geom_vbd_0.3_0.3_0.3_Beast_FastSimEval";
TString str_input = name1 + ".root";
TString str_out = "output_" + name1 + "_eta.root";

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

TH1F ***hist= new TH1F **[6];

for(int i = 0; i < 6; i++){
    hist[i] = new TH1F*[8];
    for(int j = 0; j < 8; j++){
        float axis_ends = (0.02 + (j / 40.));
        float axis_middle = (j/ 90.);
        //for formatting axis limits
        if(j>1 && j<7){
                        
            hist[i][j] = new TH1F(Form("h_%i_%i", i, j), Form("Momentum Resolution. #eta: %f - %f p: %d - %d GeV;(p-gp)/gp;counts", (j)/2., (j)/2.+0.5, (i*5), ((i*5)+5)), 50, -axis_middle, axis_middle );

        }
        else{
                           
            hist[i][j] = new TH1F(Form("h_%i_%i", i, j), Form("Momentum Resolution. #eta: %f - %f p: %d - %d GeV;(p-gp)/gp;counts", (j)/2., (j)/2.+0.5, (i*5), ((i*5)+5)), 50, -axis_ends, axis_ends );

        }                    
    }
} 
        

for( int entry = 0 ; entry < total_number_of_entries ; entry++ ){

    myTree -> GetEntry(entry);

    if(entry%(total_number_of_entries/20) == 0){cout << "Event "  << entry << " out of: " << total_number_of_entries << endl;}

    if(px == px){

        p = sqrt(pow(px,2) + pow(py,2) + pow(pz,2));
        gp = sqrt(pow(gpx,2) + pow(gpy,2) + pow(gpz,2));
        eta = TMath::ATanH(pz/p);
                        
        for(int j=0; j<8; j++){
            if(eta>=(float)(j)/2. && eta<(float)(j)/2.+0.5){
                for( int i = 0; i < 6; i++){
                    if(p >= (float)(i*5) && p < (float)((i*5)+5)){
                                            hist[i][j]->Fill((p-gp)/gp);
                    }    
                }
            }
        }

    }
}
TCanvas **c= new TCanvas *[8];
TF1  **fit = new TF1 *[8];
double sigmas [8][6];
double std_errs [8][6];
for( int j=0; j<8; j++){
    c[j] = new TCanvas(Form("c_%i", j), Form("#eta: %f - %f", (j)/2., (j)/2.+0.5));
    c[j]->Divide(3,2);
    //must change based on the field strength sigma ~ 1/B
    //for sPHENIX multiply everything by 2
    float fit_ends = (0.02 + (j / 40.));
    float fit_middle = (j/ 90.);
    //float fit_range_ends = ((1+j)/250.);
    //float fit_range_middle = ((1+j)/550.);
    //for formatting fit limits

    
    if(j>1 && j<7){
                        
    fit[j] = new TF1("fit", "gaus", -fit_middle/2., fit_middle/2. );

    }

    else{
                           
    fit[j] = new TF1("fit", "gaus", -fit_ends/2., fit_ends/2. );


    } 

    for( int i = 0; i < 6; i++){
        c[j]->cd(i+1);
        fit[j] -> SetParameters(0,0,0);
        hist[i][j]->Fit("fit", "R");
        hist[i][j]->Draw();
        double std_dev = fit[j] -> GetParameter(2);
        double std_err = fit[j] -> GetParError(2);
        sigmas[j][i] = std_dev * 100;
        std_errs[j][i] = std_err * 100;
    }
}
//Creating TGraph for all resolutions (sigmas)
double sigmas_eta [6][8];
double std_errs_eta [6][8];
double p_axis_values [8] = {.25, .75, 1.25, 1.75, 2.25, 2.75, 3.25, 3.75};
TCanvas * c_sigma = new TCanvas("c_sigma", "Momentum Resolution in #eta bins");
TMultiGraph *mg = new TMultiGraph();
mg->SetTitle("Momentum Resolution in eta bins;#eta ;dp/p [%]");
TLegend* leg = new TLegend(0.05, 0.65, .35, .92);

TFile * Fout = new TFile(str_out,"recreate");

for( int j=0; j<6; j++){
    for(int i=0; i<8; i++){
        sigmas_eta[j][i] = sigmas[i][j];
        std_errs_eta[j][i] = std_errs[i][j];

    }
            
    TGraphErrors *graph = new TGraphErrors(8, p_axis_values, sigmas_eta[j], 0 , std_errs_eta[j]);
    graph->SetMarkerColor(j+1);
    graph->SetLineColor(j+1);
    graph->SetMarkerStyle(20+j);
    graph->Write(name1 + Form("_graph_%i_eta", j));

    //graph->SetTitle(Form("#eta: %f - %f", (j)/2., (j)/2.+0.5));
    leg->AddEntry(graph, Form("%i - %i GeV", j*5, (j+1)*5), "p");
    mg->Add(graph, "LP");
}   
mg->Draw("A");
mg->GetXaxis()->SetRangeUser(0,4);
leg->SetNColumns(2);
leg->SetHeader("p Ranges");   //needs to be centered. normal SetHeader doesnt center it
//leg->SetHeader("p Ranges", "c");    doesnt work
leg->Draw();
mg->GetXaxis()->SetNdivisions(8, kTRUE);
mg->GetXaxis()->CenterTitle(true);
mg->GetYaxis()->CenterTitle(true);
mg->SetMinimum(0.);


Fout -> Close();
}