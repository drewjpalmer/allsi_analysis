{
TF1 * f1 = new TF1("f1","x",0,1);
        TCanvas * c1 = new TCanvas("c1","Testing");
        f1 -> Draw();
        c1 -> Print("test.pdf");

}

