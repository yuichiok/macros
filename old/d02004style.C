/* d02004style.C

   This routine defines a set of functions to setup

         general, canvas and histogram styles

   recommended by D0. "zmumu_1.C" macro illustrates its usage.

                                 Created: January 2003, Avto Kharchilava
                                 Updated: January 2004,      --"--
*/

// ... Global attributes go here ...
void d02004style() {

    
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
    
    gStyle->SetErrorX(0.0);   // Horizontal error bar size
   //   gStyle->SetPaperSize(10.,12.);   // Printout size
}

// ... Canvas attributes ...
void canvas_style(TCanvas *c,
                  float left_margin=0.15,
		  float right_margin=0.05,
		  float top_margin=0.05,
		  float bottom_margin=0.15,
		  int canvas_color=0,
                  int frame_color=0) {

  c->SetLeftMargin(left_margin);
  c->SetRightMargin(right_margin);
  c->SetTopMargin(top_margin);
  c->SetBottomMargin(bottom_margin);
  c->SetFillColor(canvas_color);
  c->SetFrameFillColor(frame_color);

  c->SetBorderMode(0);
  c->SetBorderSize(1);
  c->SetFrameBorderMode(0);
}

// ... 1D histogram attributes; (2D to come) ...
void h1_style(TH1 *h,
	    int line_width=3,
	    int line_color=1,
	    int line_style=1, 
	    int fill_style=1001,
	    int fill_color=50,
	    float y_min=-1111.,
	    float y_max=-1111.,
	    int ndivx=510,
	    int ndivy=510,
	    int marker_style=20,
	    int marker_color=1,
	    float marker_size=1.2,
	    int optstat=0) {

   h->SetLineWidth(line_width);
   h->SetLineColor(line_color);
   h->SetLineStyle(line_style);
   h->SetFillColor(fill_color);
   h->SetFillStyle(fill_style);
   h->SetMaximum(y_max);
   h->SetMinimum(y_min);
   h->GetXaxis()->SetNdivisions(ndivx);
   h->GetYaxis()->SetNdivisions(ndivy);

   h->SetMarkerStyle(marker_style);
   h->SetMarkerColor(marker_color);
   h->SetMarkerSize(marker_size);
   h->SetStats(optstat);

   h->SetLabelFont(62,"X");       // 42
   h->SetLabelFont(62,"Y");       // 42
   h->SetLabelOffset(0.000,"X");  // D=0.005
   h->SetLabelOffset(0.005,"Y");  // D=0.005
   h->SetLabelSize(0.055,"X");
   h->SetLabelSize(0.055,"Y");
   h->SetTitleOffset(0.8,"X");
   h->SetTitleOffset(0.9,"Y");
   h->SetTitleSize(0.06,"X");
   h->SetTitleSize(0.06,"Y");
   h->SetTitle(0);
}
