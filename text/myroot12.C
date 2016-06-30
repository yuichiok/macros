#include "TCanvas.h"
#include "TPad.h"
#include "iostream"
#include "TMath.h"

void myroot12()
{
    gROOT ->Reset();
    gStyle ->SetOptStat(1001110);
    double x,y;
    TCanvas *c1 = new TCanvas("c1","multipads",900,700);
    c1->Divide(2,2,0,0);
//    TLegend* leg = new TLegend(0.6,0.7,0.9,0.8);
    TH1S*hist1=new TH1S("h1","#Delta pT distribution",100,0.,100.);
    TH1S*hist2=new TH1S("h2","#Delta #phi distribution",100,0.,3.15);
    TH1S*hist3=new TH1S("h3","#Delta R distribution",100,0.,7.);
    TH1S*hist4=new TH1S("h4","Higgs rest mass distribution",100,0.,20.);
    hist1->SetXTitle("pT");
    hist2->SetXTitle("#Delta #phi [rad]");
    hist3->SetXTitle("#Delta R");
    hist4->SetXTitle("Mass [GeV]");
    hist1->SetYTitle("Counts");
    hist2->SetYTitle("Counts");
    hist3->SetYTitle("Counts");
    hist4->SetYTitle("Counts");
    
//    leg->AddEntry(hista, "Gamma", "f");
//    leg->AddEntry(histb, "Stable", "f");
    
    ifstream ifsa("./mytext12dpT150.txt");
    ifstream ifsb("./mytext12dphi150.txt");
    ifstream ifsc("./mytext12dR150.txt");
    ifstream ifsd("./mytext12mHiggs150.txt");
    
    c1->cd(1);
    while(ifsa>>x)
    hist1->Fill(x);
    hist1->Draw();
    c1->cd(2);
    while(ifsb>>x)
    hist2->Fill(x);
    hist2->Draw();
    c1->cd(3);
    while(ifsc>>x)
    hist3->Fill(x);
    hist3->Draw();
    c1->cd(4);
    while(ifsd>>x)
    hist4->Fill(x);
    hist4->Draw();
    
    cout << "Running" << endl;

}