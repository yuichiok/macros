#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

//import data
void read20_2n() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext20.txt");
    
    Float_t px,py,pT;
    Int_t nlines = 0;
    TFile *f = new TFile("read20.root","RECREATE");
    TNtuple *ntuple = new TNtuple("ntuple","data from reading20 file","px:py:pT");
    
    while (1) {
        in >> px >> py >> pT;
        if (!in.good()) break;
        if (nlines < 100) printf("px=%8f, py=%8f, pT=%8f\n",px,py,pT);
        ntuple->Fill(px,py,pT);
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("px:py:pT");
    
    in.close();
    
    f->Write();
    f->Close();
}


//tree -> histogram

void read20_2m() {
    
    TFile *f = new TFile("read20.root", "UPDATE");
    TTree *ntuple = (TTree*)f->Get("ntuple");
    
    Float_t px, py, pT;
    
    ntuple->SetBranchAddress("px",&px);
    ntuple->SetBranchAddress("py",&py);
    ntuple->SetBranchAddress("pT",&pT);
    
    //create histogram
    TH1F *hpx   = new TH1F("hpx","px distribution",100,-100,100);
    TH1F *hpy   = new TH1F("hpy","py distribution",100,-100,100);
    TH1F *hpT   = new TH1F("hpT","pT distribution",100,0,300);
    TH2F *hpxpy = new TH2F("hpxpy","py vs px",100,-100,100,100,-100,100);
    
    //read all entries and fill the histograms
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t q=0;q<nentries;q++) {
        ntuple->GetEntry(q);
        hpx->Fill(px);
        hpy->Fill(py);
        hpT->Fill(pT);
        hpxpy->Fill(px,py);
        }
    
    if (gROOT->IsBatch()) return;
    f->Write();
    new TBrowser();
    ntuple->StartViewer();
    
}

void read20_2(){
    
    read20_2n();
    read20_2m();
}





