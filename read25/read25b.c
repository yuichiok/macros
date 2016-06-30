#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

//text -> tree
void read25bn() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext25b.txt");    //Check
    
    Float_t dpT,dphi,deta,dR,invm;      //Values
    Int_t nlines = 0;
    TFile *f = new TFile("read25b.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from read25b file","dpT:dphi:deta:dR:invm");    //Values
    
    while (1) {
        in >> dpT >> dphi >> deta >> dR >> invm;   //input
        if (!in.good()) break;
        if (nlines < 100) printf("dpT=%8f, dphi=%8f, deta=%8f, dR=%8f, invm=%8f\n",dpT,dphi,deta,dR,invm);  //Values
        ntuple->Fill(dpT,dphi,deta,dR,invm);       //Fill values

        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("dpT:dphi:deta:dR:invm");  //Scan Values
    
    in.close();
    
    f->Write();
    f->Close();
}

//tree -> histogram
void read25bm() {
    
    TFile *f = new TFile("read25b.root");    //root file name
    TTree *ntuple = (TTree*)f->Get("ntuple");
    
    Float_t dpT,dphi,deta,dR,invm;  //Values
    
    ntuple->SetBranchAddress("dpT",&dpT);   //Values
    ntuple->SetBranchAddress("dphi",&dphi);
    ntuple->SetBranchAddress("deta",&deta);
    ntuple->SetBranchAddress("dR",&dR);
    ntuple->SetBranchAddress("invm",&invm);
    
    //create histogram
    TH1F *pT     = new TH1F("pT","Di-jet dpT distribution (after cleaning)",100,0.,300.);
    TH1F *phi     = new TH1F("phi","Di-jet d#phi distribution (after cleaning)",100,0.,M_PI);
    TH1F *eta     = new TH1F("eta","Di-jet d#eta distribution (after cleaning)",100,-M_PI,M_PI);
    TH1F *R     = new TH1F("R","dR distribution from diJet (after cleaning)",100,0.,2*M_PI);
    TH1F *inv     = new TH1F("invm","Di-jet invariant mass distribution (after b bbar cut)",100,0.,250.);
    
    //read all entries and fill the histograms
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t q=0;q<nentries;q++) {
        ntuple->GetEntry(q);
        pT->Fill(dpT);        //Histogram value
        phi->Fill(dphi);
        eta->Fill(deta);
        R->Fill(dR);
        inv->Fill(invm);
        }
    
    //setting axis label
    {
        pT->SetXTitle("#DeltapT[GeV]");
        pT->SetYTitle("Event");
        phi->SetXTitle("#Delta#phi");
        phi->SetYTitle("Event");
        eta->SetXTitle("#eta");
        eta->SetYTitle("Event");
        R->SetXTitle("#DeltaR");
        R->SetYTitle("Event");
        inv->SetXTitle("m[GeV]");
        inv->SetYTitle("Event");
    }
    
    if (gROOT->IsBatch()) return;
    f->Write();
    new TBrowser();
    ntuple->StartViewer();
    
}

void read25b(){

    read25bn();
    read25bm();
}

/*Check function name.
 *Did you run Pythia8 first?
 */



