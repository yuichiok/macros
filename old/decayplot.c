#include "TCanvas.h"
#include "TPad.h"
#include "iostream"
#include "TMath.h"

void decayplot()
{
    gROOT->Reset();
    gROOT->SetStyle("Plain");
    
    gStyle->SetCanvasColor(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadColor(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetFrameBorderMode(0);
    
    gStyle->SetTitleColor(1);   // 0
    gStyle->SetTitleBorderSize(1);
    gStyle->SetTitleX(0.10);
    gStyle->SetTitleY(0.94);
    gStyle->SetTitleW(0.5);
    gStyle->SetTitleH(0.06);
    
    gStyle->SetLabelOffset(1e-04);
    gStyle->SetLabelSize(0.04);
    
    gStyle->SetStatColor(0);
    gStyle->SetStatBorderSize(1);
    gStyle->SetStatX(0.40);
    gStyle->SetStatY(0.90);
    gStyle->SetStatW(0.15);
    gStyle->SetStatH(0.10);
    gStyle->SetOptFit(1);
    gStyle->SetErrorX(0.0);
    gStyle->SetOptStat(0);
    
    TCanvas *cdy = new TCanvas("cdy","Flux",200,10,800,600);
    cdy->SetFillColor(0);
    cdy->SetGrid();
    cdy->SetTickx();
    cdy->SetTicky();
    
    TH1F *hr = cdy->DrawFrame(0,0,6,600);
    
    hr->SetYTitle("Flux [/s cm^{2}]");
    hr->SetXTitle("Angle [Degree]");
    
    cdy->GetFrame()->SetFillColor(0);
    cdy->GetFrame()->SetBorderSize(17);
    
    int color_plot=1;
    int canvas_color=19;
    int frame_color=10;
    int legend_color=canvas_color;
    
    Int_t n = 9.;
    
    //data
    Double_t x1[] = {1.,1.5,2.,2.5,3.,3.5,4.,4.5,5.};
    Double_t c1[] = {263.,175.,150.,136.,104.,72.,80.,73.,52.};
    
    //error bar
    Double_t ex[] = {0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25};
    Double_t ec[9];
    
    for(int i=0; i< n; i++)
    {
        ec[i] = sqrt(c1[i]);
    }
    
    //graph
    TGraphErrors *gr1 = new TGraphErrors(n,x1,c1,ex,ec);
    
    //fit
    TF1 *fit = new TF1("fit","[0]+[1]*exp(-x/[2])",0,6);
    fit->SetParameters(57,600.,2.2);
    fit->SetLineColor(2);
    
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerSize(0.5);
    gr1->SetLineColor(2);
    gr1->SetMarkerColor(2);
    
    gr1->Fit("fit");
    
    gr1->SetTitle("Muon Decay");
    gr1->GetXaxis()->SetTitle("Time [#mus]");
    gr1->GetYaxis()->SetTitle("Count per channel [count]");
    gr1->Draw("AP");
    cdy->Update();

    cout << "Running" << endl;
    
}