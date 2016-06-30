#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

void read24n() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext24.txt");    //Check
    
    Float_t hm,zm;      //Values
    Int_t nlines = 0;
    TFile *f = new TFile("read24.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from read20_3 file","hm:zm");    //Values
    
    while (1) {
        in >> hm >> zm;   //input
        if (!in.good()) break;
        if (nlines < 100) printf("hm=%8f, zm=%8f\n",hm,zm);  //Values
        ntuple->Fill(hm,zm);       //Fill values
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("hm:zm");  //Scan Values
    
    in.close();
    
    f->Write();
    f->Close();
}


//tree -> histogram

void read24m() {
    
    TFile *f = new TFile("read24.root");    //root file name
    TTree *ntuple = (TTree*)f->Get("ntuple");
    
    Float_t hm,zm;  //Values
    
    ntuple->SetBranchAddress("hm",&hm);   //Values
    ntuple->SetBranchAddress("zm",&zm);
    
    //create histogram
    TH1F *higg     = new TH1F("hm","Higgs invariant mass distribution",100,0,300.);
    TH1F *zboson   = new TH1F("zm","Z0 invariant mass distribution",100,0,300.);
    
    //read all entries and fill the histograms
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t q=0;q<nentries;q++) {
        ntuple->GetEntry(q);
        higg->Fill(hm);        //Histogram value
        zboson->Fill(zm);
        }
    
    {
        higg->SetXTitle("m[GeV]");
        higg->SetYTitle("Event");
        zboson->SetXTitle("m[GeV]");
        zboson->SetYTitle("Event");
    }
    
    if (gROOT->IsBatch()) return;
    f->Write();
    new TBrowser();
    ntuple->StartViewer();
    
}

void read24(){
    
    read24n();
    read24m();
}

/*Check function name.
 *Did you run Pythia8 first?
 */



