#include "TCanvas.h"
#include "TPad.h"
#include "iostream"
#include "TMath.h"

void myroot11()
{
    gROOT ->Reset();
    gStyle ->SetOptStat(1001110);
    double x,y;
    TCanvas*c1=new TCanvas("c1");
    TLegend* leg = new TLegend(0.6,0.7,0.9,0.8);
    TH1S*hista=new TH1S("h2","Energy Spectrums",100,0.,50.);
    TH1S*histb=new TH1S("h3","h3",100,0.,50.);
    hista->SetXTitle("Energy [GeV]");
    hista->SetYTitle("Counts");
    
    leg->AddEntry(hista, "Gamma", "f");
    leg->AddEntry(histb, "Stable", "f");
    
    ifstream ifsa("./mytext11a.txt");
    ifstream ifsb("./mytext11b.txt");
    while(ifsa>>x)
    hista->Fill(x);
    while(ifsb>>x)
    histb->Fill(x);
    
    hista->SetFillColor(2);
    histb->SetFillColor(4);
    hista->Draw();
    histb->Draw("same");
    leg->Draw("same");
    
    cout << "Running" << endl;

}