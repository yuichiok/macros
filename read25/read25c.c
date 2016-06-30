#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

void read25cn() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext25c.txt");    //Check
    
    Float_t dRm,dRmbar,dRb,dRbbar;      //Values
    Int_t nlines = 0;
    TFile *f = new TFile("read25c.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from read25c file","dRm:dRmbar:dRb:dRbbar");    //Values
    
    while (1) {
        in >> dRm >> dRmbar >> dRb >> dRbbar;   //input
        if (!in.good()) break;
        if (nlines < 100) printf("dRm=%8f, dRmbar=%8f, dRb=%8f, dRbbar=%8f\n",dRm,dRmbar,dRb,dRbbar);  //Values
        ntuple->Fill(dRm,dRmbar,dRb,dRbbar);       //Fill values
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("dRm:dRmbar:dRb:dRbbar");  //Scan Values
    
    in.close();
    
    f->Write();
    f->Close();
}


//tree -> histogram

void read25cm() {
    
    TFile *f = new TFile("read25c.root");    //root file name
    TTree *ntuple = (TTree*)f->Get("ntuple");
    
    Float_t dRm,dRmbar,dRb,dRbbar;  //Values
    
    ntuple->SetBranchAddress("dRm",&dRm);   //Values
    ntuple->SetBranchAddress("dRmbar",&dRmbar);
    ntuple->SetBranchAddress("dRb",&dRb);
    ntuple->SetBranchAddress("dRbbar",&dRbbar);
    
    //create histogram
    TH1F *mudR     = new TH1F("dRm","dR distribution of mu and jet",100,0.,2 * M_PI);
    TH1F *mubardR   = new TH1F("dRmbar","dR distribution of mubar and jet",100,0.,2 * M_PI);
    TH1F *bdR     = new TH1F("dRb","dR distribution of b and jet",100,0.,2 * M_PI);
    TH1F *bbardR     = new TH1F("dRbbar","dR distribution of bbar and jet",100,0.,2 * M_PI);
    
    //read all entries and fill the histograms
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t q=0;q<nentries;q++) {
        ntuple->GetEntry(q);
        mudR->Fill(dRm);        //Histogram value
        mubardR->Fill(dRmbar);
        bdR->Fill(dRb);
        bbardR->Fill(dRbbar);
        }
    
    {
        mudR->SetXTitle("dR");
        mudR->SetYTitle("Event");
        mubardR->SetXTitle("dR");
        mubardR->SetYTitle("Event");
        bdR->SetXTitle("dR");
        bdR->SetYTitle("Event");
        bbardR->SetXTitle("dR");
        bbardR->SetYTitle("Event");
    }
    
    if (gROOT->IsBatch()) return;
    f->Write();
    new TBrowser();
    ntuple->StartViewer();
    
}

void read25c(){
    
    read25cn();
    read25cm();
}

/*Check function name.
 *Did you run Pythia8 first?
 */



