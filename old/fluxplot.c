#include "TCanvas.h"
#include "TPad.h"
#include "iostream"
#include "TMath.h"

void fluxplot()
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
    
    TCanvas *cfx = new TCanvas("cfx","Flux",200,10,800,600);
    cfx->SetFillColor(0);
    cfx->SetGrid();
    cfx->SetTickx();
    cfx->SetTicky();
    
    TH1F *hr = cfx->DrawFrame(-60,6,60,30);
    
    hr->SetYTitle("Flux [/s cm^{2}]");
    hr->SetXTitle("Angle [Degree]");
    
    cfx->GetFrame()->SetFillColor(0);
    cfx->GetFrame()->SetBorderSize(17);
    
    int color_plot=1;
    int canvas_color=19;
    int frame_color=10;
    int legend_color=canvas_color;
    
    Int_t nbins = 17.;
    Int_t time = 600.;
    
    //data
    Double_t p14 = 0.47; //distance between panel1 and panel4
    Double_t a1 = 0.296; //area of panel1
    Double_t a4 = 0.296; //area of panel4
    
    Double_t x1[] = {-60.,-50.,-40.,-30.,-20.,-15.,-10.,-5.,0.,5.,10.,15.,20.,30.,40.,50.,60.};
    Double_t c1234[] = {1377.,1937.,2645.,3793.,4064.,4298.,4469.,4548.,4733.,4662.,4610.,4714.,4362.,3802.,3047.,2712.,1752.};
    Double_t flux1[17];
    
    //error bar
    Double_t erran[] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
    Double_t errct[17];
    Double_t errfx[17];
    
    Double_t dsq = pow(p14,2);
    
    for(int i=0; i< nbins; i++)
    {
        flux1[i] = ((c1234[i] / time)*dsq) / (a1*a4);
        errct[i] = sqrt(c1234[i]);
        errfx[i] = ((errct[i] / time)*dsq) / (a1*a4);
    }
    
    //Double_t c134[] = {10.4946,14.3204,20.1397,24.1154,28.4854,31.8781,31.656,33.1163,33.4162,32.0669,31.2673,31.0008,29.0795,26.2254,21.489,16.8858,11.272};
    
    TGraphErrors *gr1 = new TGraphErrors(nbins,x1,flux1,erran,errfx);
    //TH1F *h2 = new TH1F("h2","Panel Efficiencies",nbins,x1[nbins-1]-10,x1[0]+10.);
    
    Double_t p2 = TMath::Pi()/60;
    Double_t p22 = TMath::Pi()/120;
    
    TF1 *fit1 = new TF1("fit1", "[0]+[1]*cos([2]*x+[3])",-60,60);
    TF1 *fit2 = new TF1("fit2", "[0]+[1]*pow(cos([2]*x+[3]),2)",-60,60);
    TF1 *fit3 = new TF1("fit3", "[0]*exp(-0.5*((x-[1])/0.7)*((x-[1])/0.7))",-60,60);
    
    
    fit1->SetParameters(15,15,p2,0);
    fit1->SetLineColor(2);
    fit2->SetParameters(0,30,p22,0);
    fit2->SetLineColor(4);
    fit3->SetParameters(30,0);
    
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerSize(0.5);
    gr1->SetLineColor(2);
    gr1->SetMarkerColor(2);
    
    gr1->SetTitle("Muon Flux");
    gr1->GetXaxis()->SetTitle("Angle [Degree]");
    gr1->GetYaxis()->SetTitle("Flux [/s m^{2}]");
    
    //h2->SetMarkerStyle(20);
    //h2->SetLineColor(4);
    //h2->SetMarkerColor(4);
    
    gr1->Fit(fit1);
    gr1->Fit(fit2);
    gr1->Fit(fit3);
    gr1->Draw("AP");
    fit1->Draw("same");
    fit2->Draw("same");
    fit3->Draw("same");
    cfx->Update();
    //h2->Draw("hist e1 same");
    
    
    cout << "Running" << endl;
    
}