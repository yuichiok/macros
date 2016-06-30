#include "TCanvas.h"
#include "TPad.h"
#include "iostream"
#include "TMath.h"

void myroot11c()
{
    gROOT ->Reset();
    gStyle ->SetOptStat(1001110);
    double x,y;
    TCanvas*c1=new TCanvas("c1");
    TH1S*hista=new TH1S("h2","R distance between jets",100,0.,6.);
    hista->SetXTitle("#Delta R_{jj}");
    hista->SetYTitle("Events");
    ifstream ifsa("./mytext11c.txt");
    while(ifsa>>x)
    hista->Fill(x);
    hista->SetFillColor(4);
    hista->Draw();
    
    cout << "Running" << endl;

}