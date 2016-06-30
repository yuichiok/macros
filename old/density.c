#include "TCanvas.h"
#include "TPad.h"

#include "TMath.h"

void density()
{
double phi_s, phi_a, a_i, b_i, k1, k2, k3,d_B, x, y;

//ofstream xyphi;
//xyphi.open("xyphi.txt");

a_i= 1;
b_i= 1;
d_B= 0.25;

//gROOT->SetStyle("Plain");
//gStyle->SetPalette(1, 1);

const int NCont = 255; // 50 should suffice, can be set to 255

/*
//For color palettes
const int NRGBs = 5;
double stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
double red[NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
double green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
double blue[NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };
*/

//For grayscale palettes
/*
const int NRGBs = 7;
double stops[NRGBs] = { 0.00, 0.10, 0.25, 0.45, 0.60, 0.75, 1.00 };
double red[NRGBs] = { 1.00, 0.00, 0.00, 0.00, 0.97, 0.97, 0.10 };
double green[NRGBs] = { 1.00, 0.97, 0.30, 0.40, 0.97, 0.00, 0.00 };
double blue[NRGBs] = { 1.00, 0.97, 0.97, 0.00, 0.00, 0.00, 0.00 };
*/

const int NRGBs = 2;
double stops[NRGBs] = { 0.00, 1.00};
double red[NRGBs]   = { 0.00, 1.00};
double green[NRGBs] = { 0.00, 1.00};
double blue[NRGBs]  = { 0.00, 1.00};

TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
gStyle->SetNumberContours(NCont);

TH2F* densityplot= new TH2F("densityplot",";nm;nm", 2000, 0, 4, 2000, 0, 4);
densityplot->SetStats(0);
//densityplot->SetContour(NCont);

for(x= 0; x<= 4; x+= 0.002)
  for(y= 0; y<= 4; y+= 0.002)
  {
  k1= ( (4*TMath::Pi()*y)/(3*d_B) );
  k2= ( (4*TMath::Pi())/(3*d_B) ) * ( (-sqrt(3)/2)*x - (0.5)*y );
  k3= ( (4*TMath::Pi())/(3*d_B) ) * ( (sqrt(3)/2)*x - (0.5)*y );

  phi_s= a_i*cos(k1) + a_i*cos(k2) + a_i*cos(k3);
  phi_a= b_i*sin(k1) + b_i*sin(k2) + b_i*sin(k3);
  
  //xyphi << x << " " << y << " " <<(phi_s*phi_s + phi_a*phi_a) << endl;
  
  densityplot->SetBinContent(500*x,500*y, (phi_s*phi_s + phi_a*phi_a));
  }

TCanvas *c1 = new TCanvas("c1","Density plot",0,0,2000,2000);
TPad *pad1 = new TPad("pad1","",0,0,1,1);
pad1->SetFixedAspectRatio(1);

//densityplot->Draw();
densityplot->Draw("COLZ");
    cout << "Running" << endl;
c1->Print("densityplot.gif",".gif");
c1->Close();

}