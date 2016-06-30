#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

void read20_3n() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext20_3.txt");    //Check
    
    Float_t dR,dphi,dEta;      //Values
    Int_t nlines = 0;
    TFile *f = new TFile("read20_3.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from read20_3 file","dR:dphi:dEta");    //Values
    
    while (1) {
        in >> dR >> dphi >> dEta;
        if (!in.good()) break;
        if (nlines < 100) printf("dR=%8f, dphi=%8f, dEta=%8f\n",dR,dphi,dEta);  //Values
        ntuple->Fill(dR,dphi,dEta);       //Fill values
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("dR:dphi:dEta");  //Scan Values
    
    in.close();
    
    f->Write();
    f->Close();
}


//tree -> histogram

void read20_3m() {
    
    TFile *f = new TFile("read20_3.root");
    TTree *ntuple = (TTree*)f->Get("ntuple");
    
    Float_t dR,dphi,dEta;  //Values
    
    ntuple->SetBranchAddress("dR",&dR);   //Values
    ntuple->SetBranchAddress("dphi",&dphi);
    ntuple->SetBranchAddress("dEta",&dEta);
    
    //create histogram
    TH1F *hR     = new TH1F("dR","dR distribution",100,0,4.);
    TH1F *hphi   = new TH1F("dphi","dphi distribution",100,0,M_PI);
    TH1F *hEta   = new TH1F("dEta","dEta distribution",100,0,5.);
    
    //read all entries and fill the histograms
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t q=0;q<nentries;q++) {
        ntuple->GetEntry(q);
        if(dR>0.3)hR->Fill(dR);        //Histogram value
        if(dphi>0.01)hphi->Fill(dphi);
        if(dEta>0.01)hEta->Fill(dEta);
        }
    
    if (gROOT->IsBatch()) return;
    f->Write();
    new TBrowser();
    ntuple->StartViewer();
    
}

void read20_3(){
    
    read20_3n();
    read20_3m();
}

/*Check function name.
 *Did you run Pythia8 first?
 */



