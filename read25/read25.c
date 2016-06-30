#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

void read25n() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext25.txt");    //Check
    
    Float_t hm,zm,pT1,pT2,pT3,pT4,y1,y2,y3,y4,jetsizeaf,pTH,pTZ,dpTHZ,dphiHZ;      //Values
    Int_t nlines = 0;
    TFile *f = new TFile("read25.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from read25 file","hm:zm:pT1:pT2:pT3:pT4:y1:y2:y3:y4:jetsizeaf:pTH:pTZ:dpTHZ:dphiHZ");    //Values
    
    while (1) {
        in >> hm >> zm >> pT1 >> pT2 >> pT3 >> pT4 >> y1 >> y2 >> y3 >> y4 >> jetsizeaf >> pTH >> pTZ >> dpTHZ >> dphiHZ;   //input
        if (!in.good()) break;
        if (nlines < 100) printf("hm=%8f, zm=%8f, pT1=%8f,pT2=%8f,pT3=%8f,pT4=%8f,y1=%8f,y2=%8f,y3=%8f,y4=%8f,jetsizeaf=%8f,pTH=%8f,pTZ=%8f,dpTHZ=%8f,dphiHZ=%8f\n",hm,zm,pT1,pT2,pT3,pT4,y1,y2,y3,y4,jetsizeaf,pTH,pTZ,dpTHZ,dphiHZ);  //Values
        ntuple->Fill(hm,zm,pT1,pT2,pT3,pT4,y1,y2,y3,y4,jetsizeaf,pTH,pTZ,dpTHZ,dphiHZ);       //Fill values
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("hm:zm:pT1:pT2:pT3:pT4:y1:y2:y3:y4:jetsizeaf:pTH:pTZ:dpTHZ:dphiHZ");  //Scan Values
    
    in.close();
    
    f->Write();
    f->Close();
}


//tree -> histogram

void read25m() {
    
    TFile *f = new TFile("read25.root");    //root file name
    TTree *ntuple = (TTree*)f->Get("ntuple");
    
    Float_t hm,zm,pT1,pT2,pT3,pT4,y1,y2,y3,y4,jetsizeaf,pTH,pTZ,dpTHZ,dphiHZ;  //Values
    
    ntuple->SetBranchAddress("hm",&hm);   //Values
    ntuple->SetBranchAddress("zm",&zm);
    ntuple->SetBranchAddress("pT1",&pT1);
    ntuple->SetBranchAddress("pT2",&pT2);
    ntuple->SetBranchAddress("pT3",&pT3);
    ntuple->SetBranchAddress("pT4",&pT4);
    ntuple->SetBranchAddress("y1",&y1);
    ntuple->SetBranchAddress("y2",&y2);
    ntuple->SetBranchAddress("y3",&y3);
    ntuple->SetBranchAddress("y4",&y4);
    ntuple->SetBranchAddress("jetsizeaf",&jetsizeaf);
    ntuple->SetBranchAddress("pTH",&pTH);
    ntuple->SetBranchAddress("pTZ",&pTZ);
    ntuple->SetBranchAddress("dpTHZ",&dpTHZ);
    ntuple->SetBranchAddress("dphiHZ",&dphiHZ);
    
    //create histogram
    TH1F *higg     = new TH1F("hm","Higgs invariant mass distribution",100,0,300.);
    TH1F *zboson   = new TH1F("zm","Z0 invariant mass distribution",100,0,300.);
    TH1F *bpT   = new TH1F("bpT","b quark pT distribution",100,0,300.);
    TH1F *mpT   = new TH1F("mupT","Muon pT distribution",100,0,300.);
    TH1F *bEta   = new TH1F("bEta","b quark Eta distribution",100,-4.,4.);
    TH1F *mEta   = new TH1F("muEta","Muon Eta distribution",100,-4.,4.);
    TH1F *jets   = new TH1F("jets","Number of jets per events (after muon cut)",15,0.,15.);
    TH1F *pTHhist   = new TH1F("pTH","Higgs boson pT distribution",100,0.,300.);
    TH1F *pTZhist   = new TH1F("pTZ","Z boson pT distribution",100,0.,300.);
    TH1F *dpTHZhist   = new TH1F("dpTHZ","dpT between H and Z",100,-200,200.);
    TH1F *dphiHZhist   = new TH1F("dphiHZ","dphi between H and Z",100,-4.,4.);
    
    //read all entries and fill the histograms
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t q=0;q<nentries;q++) {
        ntuple->GetEntry(q);
        higg->Fill(hm);        //Histogram value
        zboson->Fill(zm);
        bpT->Fill(pT1);
        bpT->Fill(pT2);
        mpT->Fill(pT3);
        mpT->Fill(pT4);
        bEta->Fill(y1);
        bEta->Fill(y2);
        mEta->Fill(y3);
        mEta->Fill(y4);
        jets->Fill(jetsizeaf);
        pTHhist->Fill(pTH);
        pTZhist->Fill(pTZ);
        dpTHZhist->Fill(dpTHZ);
        dphiHZhist->Fill(dphiHZ);
        }
    
    //axis labels
    {
        higg->SetXTitle("m[GeV]");
        higg->SetYTitle("Event");
        zboson->SetXTitle("m[GeV]");
        zboson->SetYTitle("Event");
        bpT->SetXTitle("pT[GeV]");
        bpT->SetYTitle("Event");
        mpT->SetXTitle("pT[GeV]");
        mpT->SetYTitle("Event");
        bEta->SetXTitle("#eta");
        bEta->SetYTitle("Event");
        mEta->SetXTitle("#eta");
        mEta->SetYTitle("Event");
        jets->SetXTitle("Number of Jets");
        jets->SetYTitle("Events");
        pTHhist->SetXTitle("pT [GeV]");
        pTHhist->SetYTitle("Events");
        pTZhist->SetXTitle("pT [GeV]");
        pTZhist->SetYTitle("Events");
        dpTHZhist->SetXTitle("dpT [GeV]");
        dpTHZhist->SetYTitle("Events");
        dphiHZhist->SetXTitle("d#phi");
        dphiHZhist->SetYTitle("Events");
    }
    
    if (gROOT->IsBatch()) return;
    f->Write();
    new TBrowser();
    ntuple->StartViewer();
    
}

void read25(){
    
    read25n();
    read25m();
}

/*Check function name.
 *Did you run Pythia8 first?
 */



