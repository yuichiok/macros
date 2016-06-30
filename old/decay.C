void decay()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Jan 22 15:43:58 2016) by ROOT version6.05/03
   TCanvas *c1 = new TCanvas("c1", "c1",297,63,737,497);
   c1->Range(-0.7500001,-154.35,6.75,1389.15);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1F *h1__1 = new TH1F("h1__1","Muon Lifetime Plot",100,0,6);
   h1__1->SetBinContent(9,588);
   h1__1->SetBinContent(17,263);
   h1__1->SetBinContent(26,175);
   h1__1->SetBinContent(34,150);
   h1__1->SetBinContent(42,136);
   h1__1->SetBinContent(51,104);
   h1__1->SetBinContent(59,72);
   h1__1->SetBinContent(67,80);
   h1__1->SetBinContent(76,73);
   h1__1->SetBinContent(84,52);
   h1__1->SetBinError(9,588);
   h1__1->SetBinError(17,263);
   h1__1->SetBinError(26,175);
   h1__1->SetBinError(34,150);
   h1__1->SetBinError(42,136);
   h1__1->SetBinError(51,104);
   h1__1->SetBinError(59,72);
   h1__1->SetBinError(67,80);
   h1__1->SetBinError(76,73);
   h1__1->SetBinError(84,52);
   h1__1->SetEntries(10);
   h1__1->SetDirectory(0);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("h1");
   AText->SetTextSize(0.02453333);
   AText = ptstats->AddText("Entries = 10     ");
   AText = ptstats->AddText("#chi^{2} / ndf = 0.2144 / 7");
   AText = ptstats->AddText("p0       =   604 #pm 1014.3 ");
   AText = ptstats->AddText("p1       = 1.095 #pm 1.657 ");
   AText = ptstats->AddText("p2       = 54.23 #pm 69.76 ");
   ptstats->SetOptStat(11);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   h1__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h1__1);
   
   TF1 *PrevFitTMP2 = new TF1("PrevFitTMP","[p0]*exp(-x/[p1])+[p2]",0,6);
   PrevFitTMP2->SetFillColor(19);
   PrevFitTMP2->SetFillStyle(0);
   PrevFitTMP2->SetLineColor(2);
   PrevFitTMP2->SetLineWidth(2);
   PrevFitTMP2->SetChisquare(0.2143934);
   PrevFitTMP2->SetNDF(7);
   PrevFitTMP2->GetXaxis()->SetLabelFont(42);
   PrevFitTMP2->GetXaxis()->SetLabelSize(0.035);
   PrevFitTMP2->GetXaxis()->SetTitleSize(0.035);
   PrevFitTMP2->GetXaxis()->SetTitleFont(42);
   PrevFitTMP2->GetYaxis()->SetLabelFont(42);
   PrevFitTMP2->GetYaxis()->SetLabelSize(0.035);
   PrevFitTMP2->GetYaxis()->SetTitleSize(0.035);
   PrevFitTMP2->GetYaxis()->SetTitleFont(42);
   PrevFitTMP2->SetParameter(0,604.0488);
   PrevFitTMP2->SetParError(0,1014.33);
   PrevFitTMP2->SetParLimits(0,0,0);
   PrevFitTMP2->SetParameter(1,1.094514);
   PrevFitTMP2->SetParError(1,1.656776);
   PrevFitTMP2->SetParLimits(1,0,0);
   PrevFitTMP2->SetParameter(2,54.23354);
   PrevFitTMP2->SetParError(2,69.75684);
   PrevFitTMP2->SetParLimits(2,0,0);
   h1__1->GetListOfFunctions()->Add(PrevFitTMP2);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1__1->SetLineColor(ci);
   h1__1->GetXaxis()->SetTitle("Time [micro sec]");
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetLabelSize(0.035);
   h1__1->GetXaxis()->SetTitleSize(0.035);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetTitle("Counts per PMT ");
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetLabelSize(0.035);
   h1__1->GetYaxis()->SetTitleSize(0.035);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetLabelSize(0.035);
   h1__1->GetZaxis()->SetTitleSize(0.035);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("E");
   
   TPaveText *pt = new TPaveText(0.3373926,0.9263158,0.6626074,0.9810526,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   AText = pt->AddText("Muon Lifetime Plot");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
