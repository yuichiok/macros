#include "TCanvas.h"
#include "TPad.h"
#include "iostream"
#include "TMath.h"

void chisq()
{
    TCanvas* c= new TCanvas();
    c->SetGrid();
    
    gStyle->SetOptFit(0111);
    
    //Including Data
    
    TGraphErrors graph("expdata.txt","%lg %lg %lg");
    
    graph.SetTitle("Measurement XYZ and Expectation; length [cm]; Arb.Units");
    
    graph.SetMarkerStyle(20);
    
    graph.DrawClone("AP");
    
    //Fit
    
    TF1 *fit = new TF1("fit","[0]*x+[1]",1,10);
    
    fit->SetParameters(5.5,0.);
    
    graph.Fit("fit");
    
    cout << fit->GetChisquare() << endl;
    
    fit->Draw("same c");
    
    //Legend
    //TLegend leg(0.1,0.7,0.3,0.9,"Legend");
    //leg.SetFillColor(0);
    //graph.SetFillColor(0);
    //leg.AddEntry(&graph,"Exp. Points");
    //leg.AddEntry(&fit,"Fitted Line");
    //leg.Draw("same");
    
    //gPad->Update();
    
    cout << "Running" << endl;
    
    c->Print("LinearGraph.pdf");
    
}