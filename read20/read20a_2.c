#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

void read20a_2n() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext20_2.txt");    //Check
    
    Float_t m;      //Values
    Int_t nlines = 0;
    TFile *f = new TFile("read20a.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from reading20a file","m");    //Values
    
    while (1) {
        in >> m;
        if (!in.good()) break;
        if (nlines < 100) printf("m=%8f\n",m);  //Values
        ntuple->Fill(m);    //Fill values
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("m");  //Scan Values
    
    in.close();
    
    f->Write();
    f->Close();
}


//tree -> histogram

void read20a_2m() {
    
    TFile *f = new TFile("read20a.root");
    TTree *ntuple = (TTree*)f->Get("ntuple");
    
    Float_t m;  //Values
    
    ntuple->SetBranchAddress("m",&m);   //Values
    
    //create histogram
    TH1F *hm   = new TH1F("hm","Jet mass distribution",100,0,300);
    
    //read all entries and fill the histograms
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t q=0;q<nentries;q++) {
        ntuple->GetEntry(q);
        hm->Fill(m);        //Histogram value
        }
    
    if (gROOT->IsBatch()) return;
    f->Write();
    new TBrowser();
    ntuple->StartViewer();
    
}

void read20a_2(){
    
    read20a_2n();
    read20a_2m();
}

/*Check function name.
 *Did you run Pythia8 first?
 */



