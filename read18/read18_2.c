#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"

//tree -> histogram

void read18_2() {
    
    TFile *f = new TFile("read18.root");
    TTree *ntuple = (TTree*)f->Get("ntuple");
    
    Float_t h, i, j;
    
    ntuple->SetBranchAddress("h",&h);
    ntuple->SetBranchAddress("i",&i);
    ntuple->SetBranchAddress("j",&j);
    
    //create histogram
    TH1F *hpx   = new TH1F("hpx","px distribution",100,0,300);
    
    //read all entries and fill the histograms
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t q=0;q<nentries;q++) {
        ntuple->GetEntry(q);
        hpx->Fill(h);
        }
    
    if (gROOT->IsBatch()) return;
    new TBrowser();
    ntuple->StartViewer();
    
}