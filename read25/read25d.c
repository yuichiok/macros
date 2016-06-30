#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

void read25dn() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext25d.txt");    //Check
    
    Float_t mult,pT,phi,y;      //Values
    Int_t nlines = 0;
    TFile *f = new TFile("read25d.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from read25d file","mult:pT:phi:y");    //Values
    
    while (1) {
        in >> mult >> pT >> phi >> y;   //input
        if (!in.good()) break;
        if (nlines < 100) printf("mult=%8f,pT=%8f,phi=%8f,y=%8f\n",mult,pT,phi,y);  //Values
        ntuple->Fill(mult,pT,phi,y);       //Fill values
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("mult:pT:phi:y");  //Scan Values
    
    in.close();
    
    f->Write();
    f->Close();
}


//tree -> histogram

void read25dm() {
    
    TFile *f = new TFile("read25d.root");    //root file name
    TTree *ntuple = (TTree*)f->Get("ntuple");
    
    Float_t mult,pT,phi,y;  //Values
    
    ntuple->SetBranchAddress("mult",&mult);   //Values
    ntuple->SetBranchAddress("pT",&pT);
    ntuple->SetBranchAddress("phi",&phi);
    ntuple->SetBranchAddress("y",&y);
    
    //create histogram
    TH1F *multiplicity     = new TH1F("multiplicity","Jet multiplicities",100,0.,100.);
    TH1F *pTjet     = new TH1F("pTjet","pT of Jets",100,0.,300.);
    TH1F *phijet     = new TH1F("#phijet","#phi of Jets",100,-4.,4.);
    TH1F *etajet     = new TH1F("#Etajet","#eta of Jets",100,-4.,4.);
    
    //read all entries and fill the histograms
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t q=0;q<nentries;q++) {
        ntuple->GetEntry(q);
        multiplicity->Fill(mult);        //Histogram value
        pTjet->Fill(pT);
        phijet->Fill(phi);
        etajet->Fill(y);
        }
    
    {
        multiplicity->SetXTitle("Mult.");
        multiplicity->SetYTitle("Jets");
        pTjet->SetXTitle("pT [GeV]");
        pTjet->SetYTitle("Jets");
        phijet->SetXTitle("#phi");
        phijet->SetYTitle("Jets");
        etajet->SetXTitle("#eta");
        etajet->SetYTitle("Jets");
    }
    
    if (gROOT->IsBatch()) return;
    f->Write();
    new TBrowser();
    ntuple->StartViewer();
    
}

void read25d(){
    
    read25dn();
    read25dm();
}

/*Check function name.
 *Did you run Pythia8 first?
 */



