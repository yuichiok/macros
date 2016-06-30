#include "TCanvas.h"
#include "TPad.h"
#include "iostream"
#include "TMath.h"

void poisson()
{
    //canvas only needed for this documentation
    TCanvas* c1 = new TCanvas("example","",600,400);
    c1->SetFillStyle(1001);
    c1->SetFillColor(kWhite);
    //create one-dimensional TEfficiency object with fixed bin size
    TEfficiency* pEff = new TEfficiency("eff","my efficiency;x;#epsilon",20,0,10);
    TRandom3 rand3;
    bool bPassed;
    double x;
    for(int i=0; i<10000; ++i)
    {
        //simulate events with variable under investigation
        x = rand3.Uniform(10);
        //check selection: bPassed = DoesEventPassSelection(x)
        bPassed = rand3.Rndm() < TMath::Gaus(x,5,4);
        pEff->Fill(bPassed,x);
    }
    pEff->Draw("AP");
    //only for this documentation
    //return c1;
}