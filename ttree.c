#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"

//tree -> histogram

void ttreew() {
    
    //create a Tree file tree1.root
    
    //create the file, the Tree and a few branches
    TFile f("ttree.root","recreate");
    TTree t1("t1","a simple Tree with simple variables");
    Float_t px, py, pz;
    Double_t random;
    Int_t ev;
    t1.Branch("px",&px,"px/F");
    t1.Branch("py",&py,"py/F");
    t1.Branch("pz",&pz,"pz/F");
    t1.Branch("random",&random,"random/D");
    t1.Branch("ev",&ev,"ev/I");
    
    //fill the tree
    for (Int_t i=0;i<10000;i++) {
        gRandom->Rannor(px,py);
        pz = px*px + py*py;
        random = gRandom->Rndm();
        ev = i;
        t1.Fill();
    }
    
    //save the Tree header. The file will be automatically closed
    //when going out of the function scope
    t1.Write();
}

void ttreer()
{
    //read the Tree generated by tree1w and fill two histograms
    
    //note that we use "new" to create the TFile and TTree objects !
    //because we want to keep these objects alive when we leave this function.
    TFile *f = new TFile("ttree.root");
    TTree *t1 = (TTree*)f->Get("t1");
    Float_t px, py, pz;
    Double_t random;
    Int_t ev;
    t1->SetBranchAddress("px",&px);
    t1->SetBranchAddress("py",&py);
    t1->SetBranchAddress("pz",&pz);
    t1->SetBranchAddress("random",&random);
    t1->SetBranchAddress("ev",&ev);
    
    //create two histograms
    TH1F *hpx   = new TH1F("hpx","px distribution",100,-3,3);
    TH2F *hpxpy = new TH2F("hpxpy","py vs px",30,-3,3,30,-3,3);
    
    //read all entries and fill the histograms
    Long64_t nentries = t1->GetEntries();
    for (Long64_t i=0;i<nentries;i++) {
        t1->GetEntry(i);
        hpx->Fill(px);
        hpxpy->Fill(px,py);
    }
    
    //we do not close the file. We want to keep the generated histograms
    //we open a browser and the TreeViewer
    if (gROOT->IsBatch()) return;
    new TBrowser();
    t1->StartViewer();
    // in the browser, click on "ROOT Files", then on "tree1.root".
    //     you can click on the histogram icons in the right panel to draw them.
    // in the TreeViewer, follow the instructions in the Help button.
}

void ttree() {
    ttreew();
    ttreer();
}