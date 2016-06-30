#include "TStyle.h"
#include "TROOT.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TVector.h"
#include "TLegend.h"
#include <fstream>
#include <iostream>
#include <vector>

void Efficiency()  {
/* efficiency.C

   Example macro to illustrate assymmetric erros (e.g. for efficiencies)
   and fit it with an error function (root's Erf)

                                 Created: Jul 2008, Avto Kharchilava
*/

// ============================================================================
// SETUP
gROOT->Reset();
gROOT->SetStyle("Plain");
gROOT->LoadMacro("d02004style.C"); global_style(); // TMP for style

// Define canvas and its layout here
TCanvas *ceff = new TCanvas("ceff"," ",10,10,800,600);

// Set this to 1 for colored version of the plot, otherwise keep it 0
int color_plot=1;   // 1/0 for color/black&white plots

// Change colors for canvas (D=29), frame (10) and legend (29) here
int canvas_color=19; 
int frame_color=10; 
int legend_color=canvas_color;

// See "d02004style.C" macro for the list of "canvas_style" arguments/defaults
canvas_style(ceff,.12,.04,.04,.11,0,0);   // B&W

if(color_plot) 
canvas_style(ceff,.12,.04,.04,.11,canvas_color,frame_color);

ceff->SetGrid();
ceff->SetTickx();
ceff->SetTicky();

// ============================================================================
// DATA

Int_t nbins = 21;

//Second counter data
Double_t x1[] = {2000,1980,1960,1940,1920,1900,1880,1860,1840,1820,1800,1780,1760,1740,1720,1700,1680,1660,1640,1620,1600};
Double_t c2[] = {1760,1535,1492,1578,583 ,629 ,686 ,800 ,1003,1303,502 ,502 ,502 ,503 ,499 ,502 ,1418,501 ,1692,2478,960 }; // Denominator
Double_t c1[] = {1696,1441,1380,1417,502 ,500 ,502 ,500 ,502 ,502 ,153 ,123 ,95  ,54  ,46  ,32  ,55  ,13  ,21  ,31  ,6   }; // Numerator

TH1F *h1 = new TH1F("h1","h1",nbins,x1[nbins-1]-10,x1[0]+10.);
TH1F *h2 = new TH1F("h2","h2",nbins,x1[nbins-1]-10,x1[0]+10.);

// Pack two example histos with the above arrays ...
for(Int_t j= 0; j <= nbins-1; j++)
{
  h1->Fill(x1[j],c1[j]);
  h2->Fill(x1[j],c2[j]);
};

// ============================================================================
// PLOT
eff = new TGraphAsymmErrors();
eff->SetMarkerColor(kBlue);
eff->SetMarkerStyle(21);

// Calculate efficiency from data
gROOT->LoadMacro("Calculate_eff.C");
calculate(h1, h2, eff);

TH1 *dummyplot = new TH2F("dummyplot","",nbins,x1[nbins-1]-10,x1[0]+10.,100,0.001,1.15);

h1_style(dummyplot,3,1,1, 0,0, 0.01,45.0, 510,510, 8,1,1.2, 0);

if(color_plot) 
h1_style(dummyplot,3,4,1, 0,0, 0.01,45., 510,510, 8,4,1.2, 0);

dummyplot->Draw("");
eff->Draw("psame");
dummyplot->GetXaxis()->SetTitle("Voltage (V)");
dummyplot->GetYaxis()->SetTitle("Efficiency");
dummyplot->GetYaxis()->SetRangeUser(0,1);

// ============================================================================
// FIT
gSystem->Load("libPhysics"); // TMP: need if want to fit
gROOT->LoadMacro("FitEffec.C"); // --"--

// Example of a fit function
TF1 *fiteffec1 = new TF1("fiteffec1",fiteffec,x1[nbins-1]-10,x1[0]+10,4); // Give limits ...
fiteffec1->SetParameters(1,0,0,0); 

eff->Fit(fiteffec1,"REL"); // "RE", "REL"
ceff->Update();

// Print out the plot
ceff->Modified();
ceff->SaveAs("Efficiency_Layer2.gif");
// ============================================================================

}
