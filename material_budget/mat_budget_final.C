void mat_budget_final()
{   
    TH1::SetDefaultSumw2();
    //Reading in TGraphErrors object from the output files from one_eta.C macro

    //function to propogate errors for momentum reolution ratio calulation
    double error_A_over_B(double A,double B, double eA,double eB){return TMath::Sqrt( pow(eA/B,2) + pow(eB*A/B/B,2) );}


    TString name1 = "out_simp_geom_vbd_0.3_0.3_0.3_Beast_FastSimEval";
    TString str_input1 = "output_" + name1 + ".root";
    TString name2 = "out_simp_geom_vbd_0.3_0.3_0.3_sPHENIX_FastSimEval";
    TString str_input2 = "output_" + name2 + ".root";
    TString name3 = "out_simp_geom_vbd_0.05_0.55_0.24_Beast_FastSimEval";
    TString str_input3 = "output_" + name3 + ".root";
    TString name4 = "out_simp_geom_vbd_0.05_0.55_0.24_sPHENIX_FastSimEval";
    TString str_input4 = "output_" + name4 + ".root";

    TFile * file1 = new TFile(str_input1);
    TFile * file2 = new TFile(str_input2);
    TFile * file3 = new TFile(str_input3);
    TFile * file4 = new TFile(str_input4);

    // Get the graphs to put in this macro

    TMultiGraph * graph1 = (TMultiGraph*) file1 -> Get(name1 + "_graph");
    TMultiGraph * graph2 = (TMultiGraph*) file2 -> Get(name2 + "_graph");
    TMultiGraph * graph3 = (TMultiGraph*) file3 -> Get(name3 + "_graph");
    TMultiGraph * graph4 = (TMultiGraph*) file4 -> Get(name4 + "_graph");


    TGraphErrors **tgraphs1 = new TGraphErrors *[8]; 
    TGraphErrors **tgraphs2 = new TGraphErrors *[8]; 
    TGraphErrors **tgraphs3 = new TGraphErrors *[8]; 
    TGraphErrors **tgraphs4 = new TGraphErrors *[8]; 
    for(int i=0; i<8; i++){
        tgraphs1[i] = (TGraphErrors*) file1 -> Get(name1 + Form("_graph_%i", i));
        tgraphs2[i] = (TGraphErrors*) file2 -> Get(name2 + Form("_graph_%i", i));
        tgraphs3[i] = (TGraphErrors*) file3 -> Get(name3 + Form("_graph_%i", i));
        tgraphs4[i] = (TGraphErrors*) file4 -> Get(name4 + Form("_graph_%i", i));
    }
    //TLegend * leg = (TLegend*) file1 -> Get(name1 + "_legend")
    
    gStyle->SetTitleFontSize(0.1);
    //Beast Plot
    TCanvas *c_Beast = new TCanvas("c_Beast", "Momentum resolution with material changes for 3.0T");
    c_Beast->Divide(4,2);
    for(int j=0; j<7; j++){
        c_Beast->cd(j+1);
        tgraphs3[j] -> Draw("APL");
        tgraphs3[j] -> GetYaxis() -> SetTitleOffset(1.2);
        tgraphs3[j] -> GetXaxis() -> SetTitleOffset(1.1);
        tgraphs3[j] -> SetMarkerColor(9);
        tgraphs3[j] -> SetLineColor(9);
        tgraphs3[j] -> SetMarkerStyle(20);
        tgraphs1[j] -> Draw("PLsame");
        tgraphs1[j] -> SetMarkerColor(46);
        tgraphs1[j] -> SetLineColor(46);
        tgraphs1[j] -> SetMarkerStyle(21);
        tgraphs3[j]->GetXaxis()->SetRangeUser(0,30);
        tgraphs3[j] -> SetMaximum((j+1)/3);
        tgraphs3[j]->SetMinimum(0.);
        //TVirtualPad::Pad() -> SetLogy();
        tgraphs3[j]->SetTitle(Form("Momentum Resolution for #eta: %.1f - %.1f;p [GeV/c];dp/p [%]", int(((j)/2.) * 100 + .5)/100., int((((j)/2.) + .5) * 100 + .5)/100.));
        tgraphs3[j]->GetXaxis()->CenterTitle(true);
        tgraphs3[j]->GetXaxis()->SetLabelSize(.04);
        tgraphs3[j]->GetXaxis()->SetTitleSize(.042);
        tgraphs3[j]->GetYaxis()->SetTitleSize(.042);
        tgraphs3[j]->GetYaxis()->SetLabelSize(.04);
        tgraphs3[j]->GetYaxis()->CenterTitle(true);
    }
    //fixing ranges of some plots
    tgraphs3[0] -> SetMaximum(1.);
    tgraphs3[1] -> SetMaximum(1.1);
    tgraphs3[6] -> SetMaximum(4.);
    tgraphs3[2] -> SetMaximum(.7);
    tgraphs3[3] -> SetMaximum(.7);
    //tgraphs3[7] -> SetMaximum(10.);

    TLegend * leg_Beast = new TLegend(0, 0.7, .7, .91);
    leg_Beast->AddEntry(tgraphs1[0], "vbd {0.3; 0.3; 0.3} (Old)" , "p");
    leg_Beast->AddEntry(tgraphs3[0], "vbd {0.05; 0.55; 0.24} (New)" , "p");
    c_Beast->cd(2);
    leg_Beast->Draw();
    leg_Beast->SetHeader("Material Budget for 3.0T Field");




    //sPHENIX plots
    TCanvas *c_sPHENIX = new TCanvas("c_sPHENIX", "Momentum resolution with material changes for 1.4T");
    c_sPHENIX->Divide(4,2);
    for(int j=0; j<7; j++){
        c_sPHENIX->cd(j+1);
        tgraphs4[j] -> Draw("APL");
        tgraphs4[j] -> GetYaxis() -> SetTitleOffset(1.25);
        tgraphs4[j] -> SetMarkerColor(9);
        tgraphs4[j] -> SetLineColor(9);
        tgraphs4[j] -> SetMarkerStyle(20);
        tgraphs2[j] -> Draw("PLsame");
        tgraphs2[j] -> SetMarkerColor(46);
        tgraphs2[j] -> SetLineColor(46);
        tgraphs2[j] -> SetMarkerStyle(21);
        tgraphs4[j]->GetXaxis()->SetRangeUser(0,30);
        tgraphs4[j] -> SetMaximum((j+1)/1.9);
        tgraphs4[j]->SetMinimum(0.);
        //TVirtualPad::Pad() -> SetLogy();
        tgraphs4[j]->SetTitle(Form("Momentum Resolution for #eta: %.1f - %.1f;p [GeV/c];dp/p [%] ", int(((j)/2.) * 100 + .5)/100., int((((j)/2.) + .5) * 100 + .5)/100.));
        tgraphs4[j]->GetXaxis()->CenterTitle(true);
        tgraphs4[j]->GetYaxis()->CenterTitle(true);
    }
    //fixing ranges of some plots
    tgraphs4[0] -> SetMaximum(2.);
    tgraphs4[5] -> SetMaximum(4.);
    tgraphs4[3] -> SetMaximum(1.4);
    tgraphs4[1] -> SetMaximum(2.5);
    tgraphs4[6] -> SetMaximum(8.);
    //tgraphs4[7] -> SetMaximum(25.);

    TLegend * leg_sPHENIX = new TLegend(0, 0.7, .7, .93);
    leg_sPHENIX->AddEntry(tgraphs2[0], "vbd {0.3; 0.3; 0.3} (Old)" , "p");
    leg_sPHENIX->AddEntry(tgraphs4[0], "vbd {0.05; 0.55; 0.24} (New)" , "p");
    c_sPHENIX->cd(2);
    leg_sPHENIX->Draw();
    leg_sPHENIX->SetHeader("Material Budget for 1.4T Field");



    //repeat same as above but with eta_binned_p_res.C macro. finding eta bins instead of momentum

    //Reading in TGraphErrors object from the output files from one_eta.C macro
    
    TString str_input5 = "output_" + name1 + "_eta.root";
    TString str_input6 = "output_" + name2 + "_eta.root";
    TString str_input7 = "output_" + name3 + "_eta.root";
    TString str_input8 = "output_" + name4 + "_eta.root";

    TFile * file5 = new TFile(str_input5);
    TFile * file6 = new TFile(str_input6);
    TFile * file7 = new TFile(str_input7);
    TFile * file8 = new TFile(str_input8);

    // Get the graphs to put in this macro

    //TMultiGraph * graph5 = (TMultiGraph*) file5 -> Get(name1 + "_graph");
    //TMultiGraph * graph6 = (TMultiGraph*) file6 -> Get(name2 + "_graph");
    //TMultiGraph * graph7 = (TMultiGraph*) file7 -> Get(name3 + "_graph");
    //TMultiGraph * graph8 = (TMultiGraph*) file8 -> Get(name4 + "_graph");


    TGraphErrors **tgraphs5 = new TGraphErrors *[6]; 
    TGraphErrors **tgraphs6 = new TGraphErrors *[6]; 
    TGraphErrors **tgraphs7 = new TGraphErrors *[6]; 
    TGraphErrors **tgraphs8 = new TGraphErrors *[6]; 
    for(int i=0; i<6; i++){
        tgraphs5[i] = (TGraphErrors*) file5 -> Get(name1 + Form("_graph_%i_eta", i));
        tgraphs6[i] = (TGraphErrors*) file6 -> Get(name2 + Form("_graph_%i_eta", i));
        tgraphs7[i] = (TGraphErrors*) file7 -> Get(name3 + Form("_graph_%i_eta", i));
        tgraphs8[i] = (TGraphErrors*) file8 -> Get(name4 + Form("_graph_%i_eta", i));
    }
    //TLegend * leg = (TLegend*) file1 -> Get(name1 + "_legend")
    
    //Beast Plot
    TCanvas *c_Beast_eta = new TCanvas("c_Beast_eta", "Momentum resolution with material changes for 3.0T in eta bins");
    c_Beast_eta->Divide(3,2);
    for(int j=0; j<6; j++){
        c_Beast_eta->cd(j+1);
        tgraphs5[j] -> Draw("APL");
        tgraphs5[j] -> GetYaxis() -> SetTitleOffset(1.25);
        tgraphs5[j] -> SetMarkerColor(46);
        tgraphs5[j] -> SetLineColor(46);
        tgraphs5[j] -> SetMarkerStyle(21);
        tgraphs7[j] -> Draw("PLsame");
        tgraphs7[j] -> SetMarkerColor(9);
        tgraphs7[j] -> SetLineColor(9);
        tgraphs7[j] -> SetMarkerStyle(20);
        tgraphs5[j]->GetXaxis()->SetRangeUser(0,4);
        //tgraphs7[j] -> SetMaximum((j+1)/1.5);
        tgraphs5[j]->SetMinimum(0.);
        //TVirtualPad::Pad() -> SetLogy();
        tgraphs5[j]->SetTitle(Form("Momentum Resolution for p: %i - %i [GeV/c];#eta;dp/p [%] ", j*5, (j+1)*5));
        //tgraphs5[j]->GetXaxis()->SetLabelSize(.15);
        tgraphs5[j]->GetXaxis()->CenterTitle(true);
        tgraphs5[j]->GetYaxis()->CenterTitle(true);
    }
    //fixing ranges of some plots
    tgraphs5[3] -> SetMaximum(8.);
    tgraphs5[4] -> SetMaximum(11.);


    TLegend * leg_Beast_eta = new TLegend(0, 0.7, .7, .93);
    leg_Beast_eta->AddEntry(tgraphs5[0], "vbd {0.3; 0.3; 0.3} (Old)" , "p");
    leg_Beast_eta->AddEntry(tgraphs7[0], "vbd {0.05; 0.55; 0.24} (New)" , "p");
    c_Beast_eta->cd(2);
    leg_Beast_eta->Draw();
    leg_Beast_eta->SetHeader("Material Budget for 3.0T Field");




    //sPHENIX plots
    TCanvas *c_sPHENIX_eta = new TCanvas("c_sPHENIX_eta", "Momentum resolution with material changes for 1.4T in eta bins");
    c_sPHENIX_eta->Divide(3,2);
    for(int j=0; j<6; j++){
        c_sPHENIX_eta->cd(j+1);
        tgraphs6[j] -> Draw("APL");
        tgraphs6[j] -> GetYaxis() -> SetTitleOffset(1.25);
        tgraphs6[j] -> SetMarkerColor(46);
        tgraphs6[j] -> SetLineColor(46);
        tgraphs6[j] -> SetMarkerStyle(21);
        tgraphs8[j] -> Draw("PLsame");
        tgraphs8[j] -> SetMarkerColor(9);
        tgraphs8[j] -> SetLineColor(9);
        tgraphs8[j] -> SetMarkerStyle(20);
        tgraphs6[j]->GetXaxis()->SetRangeUser(0,4);
        //tgraphs8[j] -> SetMaximum((j+1)/.6);
        tgraphs6[j]->SetMinimum(0.);
        //TVirtualPad::Pad() -> SetLogy();
        tgraphs6[j]->SetTitle(Form("Momentum Resolution for p: %i - %i [GeV/c];#eta;dp/p [%] ", j*5, (j+1)*5));
        tgraphs6[j]->GetXaxis()->CenterTitle(true);
        tgraphs6[j]->GetYaxis()->CenterTitle(true);
    }
    //fixing ranges of some plots
    tgraphs6[2] -> SetMaximum(20.);
    tgraphs6[3] -> SetMaximum(20.);

    TLegend * leg_sPHENIX_eta = new TLegend(0, 0.7, .7, .93);
    leg_sPHENIX_eta->AddEntry(tgraphs6[0], "vbd {0.3; 0.3; 0.3} (Old)" , "p");
    leg_sPHENIX_eta->AddEntry(tgraphs8[0], "vbd {0.05; 0.55; 0.24} (New)" , "p");
    c_sPHENIX_eta->cd(2);
    leg_sPHENIX_eta->Draw();
    leg_sPHENIX_eta->SetHeader("Material Budget for 1.4T Field");







    // another attempt at quantitiative compare
    TGraphErrors **tgraphscb = new TGraphErrors *[8];
    TGraphErrors **tgraphscs = new TGraphErrors *[8];
    double ex[6] = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5};  
    double ysb[8][6] = {{0}};
    double yss[8][6] = {{0}};
    double yerb[8][6] = {{0}};
    double yers[8][6] = {{0}};
    double xs[6] = {2.5, 7.5, 12.5, 17.5, 22.5, 27.5};

    TCanvas * c_compareb = new TCanvas("Comparing material_budget Beast", "Momentum resolution for New / Old material budget for 3.0T");
    c_compareb -> Divide(4,2);
    TCanvas * c_compares = new TCanvas("Comparing material_budget sPHENIX", "Momentum resolution for New / Old material budget for 1.4T");
    c_compares -> Divide(4,2);


    for(int i = 0; i < 7; i++){
        for(int j=0; j < 6; j++){

 
            double x_val = xs[j];
            double val_newb = tgraphs3[i] -> Eval(x_val);
            double val_oldb = tgraphs1[i] -> Eval(x_val);
            double err_newb = tgraphs3[i] -> GetErrorY(j);
            double err_oldb = tgraphs1[i] -> GetErrorY(j);
            double total_errorb = error_A_over_B( val_newb , val_oldb , err_newb , err_oldb);
            double val_news = tgraphs4[i] -> Eval(x_val);
            double val_olds = tgraphs2[i] -> Eval(x_val);
            double err_news = tgraphs4[i] -> GetErrorY(j);
            double err_olds = tgraphs2[i] -> GetErrorY(j);
            double total_errors = error_A_over_B( val_news , val_olds , err_news , err_olds);

            ysb[i][j] = ( val_newb ) / ( val_oldb );
            yss[i][j] = ( val_news ) / ( val_olds );
            yerb[i][j] = total_errorb;
            yers[i][j] = total_errors;
        

        }   
            
            tgraphscb[i] = new TGraphErrors(6, xs, ysb[i], ex, yerb[i]);
            tgraphscs[i] = new TGraphErrors(6, xs, yss[i], ex, yers[i]);
            

            
            c_compareb -> cd(i+1);
            c_compareb -> SetTitle("Momentum resolution for New / Old material budget for 3.0T");
            tgraphscb[i] -> Draw("APLZ");
            tgraphscb[i] -> GetXaxis() -> SetTitleOffset(1.1);
            tgraphscb[i]->GetXaxis()->SetLabelSize(.031);
            tgraphscb[i]->GetXaxis()->SetTitleSize(.042);
            tgraphscb[i]->GetYaxis()->SetTitleSize(.042);
            tgraphscb[i]->GetYaxis()->SetNdivisions(7);
            tgraphscb[i]->GetYaxis()->SetLabelSize(.031);
            tgraphscb[i] -> SetMarkerColor(9);
            tgraphscb[i] -> SetLineColor(9);
            tgraphscb[i] -> SetMarkerStyle(20);
            tgraphscb[i]->SetTitle(Form("Momentum Resolution for #eta: %.1f - %.1f;p [GeV/c];New/Old Material Budget dp/p ", int(((i)/2.) * 100 + .5)/100., int((((i)/2.) + .5) * 100 + .5)/100.));
            tgraphscb[i]->GetXaxis()->CenterTitle(true);
            tgraphscb[i]->GetYaxis()->CenterTitle(true);
            if (i>1){tgraphscb[i]->SetMaximum(1.04);}
            //tgraphscb[i]->SetMinimum(0);
            tgraphscb[i]->GetXaxis()->SetRangeUser(0,30);
            tgraphscb[i] -> GetYaxis() -> SetTitleOffset(1.2);
            if (i<2){tgraphscb[i] -> SetMinimum(.95);}

            TLine *line = new TLine(0,1,30,1);
            line -> Draw("A");
            line -> SetLineColor(2);
            
        


            c_compares -> cd(i+1);
            c_compares -> SetTitle("Momentum resolution for New / Old material budget for 1.4T");
            tgraphscs[i] -> Draw("APLZ");
            tgraphscs[i] -> SetMarkerColor(9);
            tgraphscs[i] -> SetLineColor(9);
            tgraphscs[i] -> SetMarkerStyle(20);
            tgraphscs[i]->SetTitle(Form("#eta: %.1f - %.1f;p [GeV/c];New/Old Material Budget dp/p ", int(((i)/2.) * 100 + .5)/100., int((((i)/2.) + .5) * 100 + .5)/100.));
            tgraphscs[i]->GetXaxis()->CenterTitle(true);
            tgraphscs[i]->GetYaxis()->CenterTitle(true);
            if (i>1){tgraphscs[i]->SetMaximum(1.02);}
            //tgraphscs[i]->SetMinimum(0);
            tgraphscs[i]->GetXaxis()->SetRangeUser(0,30);
            tgraphscs[i] -> GetYaxis() -> SetTitleOffset(1.5);
            if (i<2){tgraphscs[i] -> SetMinimum(.95);}
            TLine *line = new TLine(0,1,30,1);
            line -> Draw("A");
            line -> SetLineColor(2);
            
        
    }




    //eta quantitative comparison
    TGraphErrors **tgraphscb_eta = new TGraphErrors *[6];
    TGraphErrors **tgraphscs_eta = new TGraphErrors *[6];
    double ey_eta[7] = {.25, .25, .25, .25, .25, .25, .25};  
    double ysb_eta[6][7] = {{0}};
    double yss_eta[6][7] = {{0}};
    double yerb_eta[6][7] = {{0}};
    double yers_eta[6][7] = {{0}};
    double xs_eta[7] = {.25, .75, 1.25, 1.75, 2.25, 2.75, 3.25};

    TCanvas * c_compareb_eta = new TCanvas("Comparing material_budget Beast in eta bins", "Momentum resolution in #eta bins for New / Old material budget for 3.0T");
    c_compareb_eta -> Divide(3,2);
    TCanvas * c_compares_eta = new TCanvas("Comparing material_budget sPHENIX in eta bins", "Momentum resolution in #eta bins for New / Old material budget for 1.4T");
    c_compares_eta -> Divide(3,2);

    for(int i = 0; i < 6; i++){
        for(int j=0; j < 7; j++){


            
        
            
            double x_val_eta = xs_eta[j];
            double val_newb_eta = tgraphs7[i] -> Eval(x_val_eta);
            double val_oldb_eta = tgraphs5[i] -> Eval(x_val_eta);
            double err_newb_eta = tgraphs7[i] -> GetErrorY(j);
            double err_oldb_eta = tgraphs5[i] -> GetErrorY(j);
            double total_errorb_eta = error_A_over_B( val_newb_eta , val_oldb_eta , err_newb_eta , err_oldb_eta);
            double val_news_eta = tgraphs8[i] -> Eval(x_val_eta);
            double val_olds_eta = tgraphs6[i] -> Eval(x_val_eta);
            double err_news_eta = tgraphs8[i] -> GetErrorY(j);
            double err_olds_eta = tgraphs6[i] -> GetErrorY(j);
            double total_errors_eta = error_A_over_B( val_news_eta , val_olds_eta , err_news_eta , err_olds_eta);

            ysb_eta[i][j] = ( val_newb_eta ) / ( val_oldb_eta );
            yss_eta[i][j] = ( val_news_eta ) / ( val_olds_eta );
            yerb_eta[i][j] = total_errorb_eta;
            yers_eta[i][j] = total_errors_eta;
        }
            
            tgraphscb_eta[i] = new TGraphErrors(7, xs_eta, ysb_eta[i], ey_eta, yerb_eta[i]);
            tgraphscs_eta[i] = new TGraphErrors(7, xs_eta, yss_eta[i], ey_eta, yers_eta[i]);

            c_compareb_eta -> cd(i+1);
            c_compareb_eta -> SetTitle("Momentum resolution in #eta bins for New / Old material budget for 3.0T");
            tgraphscb_eta[i] -> Draw("APLZ");
            tgraphscb_eta[i] -> SetMarkerColor(9);
            tgraphscb_eta[i] -> SetLineColor(9);
            tgraphscb_eta[i] -> SetMarkerStyle(20);
            tgraphscb_eta[i]->SetTitle(Form("p: %i - %i [GeV/c];#eta;New/Old Material Budget dp/p ", i*5, (i+1)*5));
            tgraphscb_eta[i]->GetXaxis()->CenterTitle(true);
            tgraphscb_eta[i]->GetYaxis()->CenterTitle(true);
            tgraphscb_eta[i]->GetXaxis()->SetRangeUser(0,3.5);
            tgraphscb_eta[i] -> GetYaxis() -> SetTitleOffset(1.4);

            TLine *line = new TLine(0,1,3.5,1);
            line -> Draw();
            line -> SetLineColor(2);
        


            c_compares_eta -> cd(i+1);
            c_compares_eta -> SetTitle("Momentum resolution in #eta bins for New / Old material budget for 1.4T");
            tgraphscs_eta[i] -> Draw("APLZ");
            tgraphscs_eta[i] -> SetMarkerColor(9);
            tgraphscs_eta[i] -> SetLineColor(9);
            tgraphscs_eta[i] -> SetMarkerStyle(20);
            tgraphscs_eta[i]->SetTitle(Form("p: %i - %i [GeV/c];#eta;New/Old Material Budget dp/p ", i*5, (i+1)*5));
            tgraphscs_eta[i]->GetXaxis()->CenterTitle(true);
            tgraphscs_eta[i]->GetYaxis()->CenterTitle(true);
            tgraphscs_eta[i]->GetXaxis()->SetRangeUser(0,3.5);
            tgraphscs_eta[i] -> GetYaxis() -> SetTitleOffset(1.4);

            TLine *line = new TLine(0,1,3.5,1);
            line -> Draw();
            line -> SetLineColor(2);
        
        
    }
    /*
    //example plots for presentation
    TCanvas * c_example = new TCanvas("c_example", "Beast Example Plot");
    tgraphs3[1] -> Draw("APL");
    tgraphs3[1] -> GetYaxis() -> SetTitleOffset(1.25);
    tgraphs3[1] -> SetMarkerColor(9);
    tgraphs3[1] -> SetLineColor(9);
    tgraphs3[1] -> SetMarkerStyle(20);
    tgraphs1[1] -> Draw("PLsame");
    tgraphs1[1] -> SetMarkerColor(46);
    tgraphs1[1] -> SetLineColor(46);
    tgraphs1[1] -> SetMarkerStyle(21);
    tgraphs3[1]->GetXaxis()->SetRangeUser(0,30);
    tgraphs3[1] -> SetMaximum((1+1)/3);
    tgraphs3[1]->SetMinimum(0.);
    //TVirtualPad::Pad() -> SetLogy();
    tgraphs3[1]->SetTitle(Form("Momentum Resolution for #eta: %f - %f;p [GeV/c];dp/p [%] ", int(((1.)/2.) * 100 + .5)/100., int((((1.)/2.) + .5) * 100 + .5)/100.));
    tgraphs3[1]->GetXaxis()->CenterTitle(true);
    tgraphs3[1]->GetYaxis()->CenterTitle(true);

    TLegend * leg_example = new TLegend(0.02, 0.7, .5, .93);
    leg_example->AddEntry(tgraphs1[1], "vbd {0.3; 0.3; 0.3} (Old)" , "p");
    leg_example->AddEntry(tgraphs3[1], "vbd {0.05; 0.55; 0.24} (New)" , "p");
    leg_example->Draw();
    leg_example->SetHeader("Material Budget for 3.0T Field");


    //eta example plot
    TCanvas * c_example_eta = new TCanvas("c_example_eta", "Beast Example Plot");
    tgraphs7[1] -> Draw("APL");
    tgraphs7[1] -> GetYaxis() -> SetTitleOffset(1.25);
    tgraphs7[1] -> SetMarkerColor(9);
    tgraphs7[1] -> SetLineColor(9);
    tgraphs7[1] -> SetMarkerStyle(20);
    tgraphs5[1] -> Draw("PLsame");
    tgraphs5[1] -> SetMarkerColor(46);
    tgraphs5[1] -> SetLineColor(46);
    tgraphs5[1] -> SetMarkerStyle(21);
    tgraphs7[1]->GetXaxis()->SetRangeUser(0,30);
    tgraphs7[1]->SetMinimum(0.);
    //TVirtualPad::Pad() -> SetLogy();
    tgraphs7[1]->SetTitle(Form("Momentum Resolution for p: %i - %i [GeV/c];#eta;dp/p [%] ", 1*5, (1+1)*5));
    tgraphs7[1]->GetXaxis()->CenterTitle(true);
    tgraphs7[1]->GetYaxis()->CenterTitle(true);
    tgraphs7[1]->SetMaximum(7.);

    TLegend * leg_example_eta = new TLegend(0.02, 0.7, .5, .93);
    leg_example_eta->AddEntry(tgraphs5[1], "vbd {0.3; 0.3; 0.3} (Old)" , "p");
    leg_example_eta->AddEntry(tgraphs7[1], "vbd {0.05; 0.55; 0.24} (New)" , "p");
    leg_example_eta->Draw();
    leg_example_eta->SetHeader("Material Budget for 3.0T Field");

    */
    
    
    //TCanvas * c1 = new TCanvas("c1", "Momentum resolution for old materials 3.0T");
    //graph1 -> Draw("A");
    //TCanvas * c2 = new TCanvas("c2", "Momentum resolution for old materials 1.4T");
    //graph2 -> Draw("A");
    //TCanvas * c3 = new TCanvas("c3", "Momentum resolution for new materials 3.0T");
    //graph3 -> Draw("A");
    //TCanvas * c4 = new TCanvas("c4", "Momentum resolution for new materials 1.4T");
    //graph4 -> Draw("A");

    //TLegend* leg = new TLegend();
    //leg -> Draw();

    
    //draw side by side on same canvas
    //TCanvas *c0 = new TCanvas("c0","Momentum Resolution for new and old material budget in Beast and sPHENIX");
    
    //c0->Divide(2,2);
    //c0 -> cd(1);
    //graph1->SetMinimum(0.1);
    //TVirtualPad::Pad() -> SetLogy();
    //graph1 -> Draw("A");
    //c0 -> cd(2);
    //graph2 -> Draw("A");
    //c0 -> cd(3);
    //graph3 -> Draw("A");
    //c0 -> cd(4);
    //graph4 -> Draw("A");

    //trying overplotting the curves

    //TCanvas *cover = new TCanvas("cover", "overplotted curves", 1200, 800);
    //TMultiGraph *mg1 = new TMultiGraph();
    //mg1->SetTitle("Momentum Resolution in p bins;p [GeV/c];dp/p [%]");

    //mg1->Add(graph1, "PXL");
    //mg1->Add(graph2, "PXL");
    //mg1->Add(graph3, "PXL");
    //mg1->Add(graph4, "PXL");

    //mg1 -> Draw("A");

    //mg1->GetXaxis()->SetRangeUser(0,30);
    //mg1->GetYaxis()->SetRangeUser(0,20);
    //mg1->GetXaxis()->SetNdivisions(7, kTRUE);
    //mg1->GetXaxis()->CenterTitle(true);
    //mg1->GetYaxis()->CenterTitle(true);
    //mg1->SetMinimum(0.);

        


    


    //c_Beast->SaveAs("Beast_results.jpeg");
    //c_sPHENIX->SaveAs("sPHENIX_results.jpeg");
    //plots too low res, .pdf file type throws error

}