{
    //comparing simplified geometry fastSim events for 5 disk geometry and equidistant 7 disk geometry

    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();

    TString name1 = "out_simp_geom_vbd_0.05_0.55_0.24_Beast_FastSimEval"; //old Beast
    TString str_input1 = "output_" + name1 + ".root";
    //TString name2 = "out_simp_geom_vbd_0.05_0.55_0.24_sPHENIX_FastSimEval"; //old sPHENIX
    //TString str_input2 = "output_" + name2 + ".root";
    TString name3 = "out_simp_geom_Beast_seven_cone"; //new Beast (7 disk)
    TString str_input3 = "output_" + name3 + ".root";
    //TString name4 = "out_simp_geom_sPHENIX_seven_cone"; //new sPHENIX (7 disk)
    //TString str_input4 = "output_" + name4 + ".root";

    TFile *file1 = new TFile(str_input1);
    //TFile * file2 = new TFile(str_input2);
    TFile *file3 = new TFile(str_input3);
    //TFile * file4 = new TFile(str_input4);

    
    TH1F ***hist1 = new TH1F **[6];
    TH1F ***hist3 = new TH1F **[6];
    TH1F ***histb = new TH1F **[6];
    TCanvas **c_beast = new TCanvas *[6];
    for (int i = 0; i < 6; i++)
    {

        hist1[i] = new TH1F *[8];
        hist3[i] = new TH1F *[8];
        histb[i] = new TH1F *[8];

        c_beast[i] = new TCanvas("c_Beast", "Momentum resolution with seven cones for 3.0T");
        c_Beast[i]->Divide(4, 2);

        for (int j = 0; j < 8; j++)
        {
            c_beast[i]->cd(j + 1);

            hist1[i][j] = (TH1F *)file1->Get(name1 + Form("_hist_%i_%i", i, j));
            hist3[i][j] = (TH1F *)file3->Get(name3 + Form("_hist_%i_%i", i, j));

            histb[i][j] = hist3[i][j]->Divide(hist1[i][j]);
            histb[i][j]->Draw("APL");
        }
    }
    
}
