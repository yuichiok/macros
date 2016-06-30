#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

//reading part ==========================================================================================
void read25en() {
    ifstream in;
    ifstream inb;
    ifstream inc;
    ifstream ind;
    in.open("/Users/Yuichi/root/macros/mytext25/mytext25a.txt");    //Check
    inb.open("/Users/Yuichi/root/macros/mytext25/mytext25b.txt");
    inc.open("/Users/Yuichi/root/macros/mytext25/mytext25c.txt");
    ind.open("/Users/Yuichi/root/macros/mytext25/mytext25d.txt");
    
    Float_t hm,zm,pT1,pT2,pT3,pT4,y1,y2,y3,y4,jetsizeaf,pTH,pTZ,dpTHZ,dphiHZ;      //Values
    Float_t dpT,dphi,deta,dR,invm;
    Float_t dRm,dRmbar,dRb,dRbbar;
    Float_t mult,pT,phi,y;
    
    Int_t nlines = 0;
    Int_t nlinesb = 0;
    Int_t nlinesc = 0;
    Int_t nlinesd = 0;
    
    TFile *f = new TFile("read25e.root","RECREATE");    //Output name
    TNtuple *ntuple = new TNtuple("ntuple","data from read25 file","hm:zm:pT1:pT2:pT3:pT4:y1:y2:y3:y4:jetsizeaf:pTH:pTZ:dpTHZ:dphiHZ");    //Values
    TNtuple *ntupleb = new TNtuple("ntupleb","data from read25b file","dpT:dphi:deta:dR:invm");
    TNtuple *ntuplec = new TNtuple("ntuplec","data from read25c file","dRm:dRmbar:dRb:dRbbar");
    TNtuple *ntupled = new TNtuple("ntupled","data from read25d file","mult:pT:phi:y");
    
    while (1) {
        in >> hm >> zm >> pT1 >> pT2 >> pT3 >> pT4 >> y1 >> y2 >> y3 >> y4 >> jetsizeaf >> pTH >> pTZ >> dpTHZ >> dphiHZ;   //input
        if (!in.good()) break;
        if (nlines < 100) printf("hm=%8f, zm=%8f, pT1=%8f,pT2=%8f,pT3=%8f,pT4=%8f,y1=%8f,y2=%8f,y3=%8f,y4=%8f,jetsizeaf=%8f,pTH=%8f,pTZ=%8f,dpTHZ=%8f,dphiHZ=%8f\n",hm,zm,pT1,pT2,pT3,pT4,y1,y2,y3,y4,jetsizeaf,pTH,pTZ,dpTHZ,dphiHZ);  //Values
        ntuple->Fill(hm,zm,pT1,pT2,pT3,pT4,y1,y2,y3,y4,jetsizeaf,pTH,pTZ,dpTHZ,dphiHZ);       //Fill values
        nlines++;
    }
    
    while (1) {
        inb >> dpT >> dphi >> deta >> dR >> invm;   //input
        if (!inb.good()) break;
        if (nlinesb < 100) printf("dpT=%8f, dphi=%8f, deta=%8f, dR=%8f, invm=%8f\n",dpT,dphi,deta,dR,invm);  //Values
        ntupleb->Fill(dpT,dphi,deta,dR,invm);       //Fill values
        nlinesb++;
    }
    
    while (1) {
        inc >> dRm >> dRmbar >> dRb >> dRbbar;   //input
        if (!inc.good()) break;
        if (nlinesc < 100) printf("dRm=%8f, dRmbar=%8f, dRb=%8f, dRbbar=%8f\n",dRm,dRmbar,dRb,dRbbar);  //Values
        ntuplec->Fill(dRm,dRmbar,dRb,dRbbar);       //Fill values
        nlinesc++;
    }
    
    while (1) {
        ind >> mult >> pT >> phi >> y;   //input
        if (!ind.good()) break;
        if (nlinesd < 100) printf("mult=%8f,pT=%8f,phi=%8f,y=%8f\n",mult,pT,phi,y);  //Values
        ntupled->Fill(mult,pT,phi,y);       //Fill values
        nlinesd++;
    }
    
    printf(" found %d points\n",nlines);
    printf(" found %d points\n",nlinesb);
    printf(" found %d points\n",nlinesc);
    printf(" found %d points\n",nlinesd);
    
    ntuple->Scan("hm:zm:pT1:pT2:pT3:pT4:y1:y2:y3:y4:jetsizeaf:pTH:pTZ:dpTHZ:dphiHZ");  //Scan Values
    ntupleb->Scan("dpT:dphi:deta:dR:invm");
    ntuplec->Scan("dRm:dRmbar:dRb:dRbbar");
    ntupled->Scan("mult:pT:phi:y");
    
    in.close();
    inb.close();
    inc.close();
    ind.close();
    
    f->Write();
    f->Close();
}


//Historgram part =======================================================================================

//tree -> histogram

void read25em() {
    
    TFile *f = new TFile("read25e.root");    //root file name
    TTree *ntuple = (TTree*)f->Get("ntuple");
    TTree *ntupleb = (TTree*)f->Get("ntupleb");
    TTree *ntuplec = (TTree*)f->Get("ntuplec");
    TTree *ntupled = (TTree*)f->Get("ntupled");
    
    Float_t hm,zm,pT1,pT2,pT3,pT4,y1,y2,y3,y4,jetsizeaf,pTH,pTZ,dpTHZ;  //Values
    Float_t dpT,dphi,deta,dR,invm;
    Float_t dRm,dRmbar,dRb,dRbbar;
    Float_t mult,pT,phi,y;
    
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
    
    ntupleb->SetBranchAddress("dpT",&dpT);   //Values from b
    ntupleb->SetBranchAddress("dphi",&dphi);
    ntupleb->SetBranchAddress("deta",&deta);
    ntupleb->SetBranchAddress("dR",&dR);
    ntupleb->SetBranchAddress("invm",&invm);
    
    ntuplec->SetBranchAddress("dRm",&dRm);   //Values from c
    ntuplec->SetBranchAddress("dRmbar",&dRmbar);
    ntuplec->SetBranchAddress("dRb",&dRb);
    ntuplec->SetBranchAddress("dRbbar",&dRbbar);
    
    ntupled->SetBranchAddress("mult",&mult);   //Values from d
    ntupled->SetBranchAddress("pT",&pT);
    ntupled->SetBranchAddress("phi",&phi);
    ntupled->SetBranchAddress("y",&y);
    
    //create histogram
    TH1F *higg     = new TH1F("hm","Higgs invariant mass distribution",100,0,300.);
    TH1F *zboson   = new TH1F("zm","Z0 invariant mass distribution",100,0,300.);
    TH1F *bpT   = new TH1F("bpT","b quark pT distribution",100,0,300.);
    TH1F *mpT   = new TH1F("mupT","Muon pT distribution",100,0,300.);
    TH1F *bEta   = new TH1F("bEta","b quark Eta distribution",100,-4.,4.);
    TH1F *mEta   = new TH1F("muEta","Muon Eta distribution",100,-4.,4.);
    TH1F *jets   = new TH1F("jets","Number of jets per events (after b bbar cut)",15,0.,15.);
    TH1F *pTHhist   = new TH1F("pTH","Higgs boson pT distribution",100,0.,300.);
    TH1F *pTZhist   = new TH1F("pTZ","Z boson pT distribution",100,0.,300.);
    TH1F *dpTHZhist   = new TH1F("dpTHZ","dpT between H and Z",100,-200,200.);
    
    //create histogram b
    TH1F *pT100     = new TH1F("pT100","Di-jet dpT distribution (after cleaning)",100,0.,300.);
    TH1F *phi100     = new TH1F("phi100","Di-jet d#phi distribution (after cleaning)",100,0.,M_PI);
    TH1F *eta     = new TH1F("eta","Di-jet d#eta distribution (after cleaning)",100,-M_PI,M_PI);
    TH1F *R     = new TH1F("R","dR distribution from diJet (after cleaning)",100,0.,2*M_PI);
    TH1F *inv     = new TH1F("invm","Di-jet invariant mass distribution (after b bbar cut)",100,0.,250.);

    //create histogram c
    TH1F *mudR     = new TH1F("dRm","dR distribution of mu and jet",100,0.,2 * M_PI);
    TH1F *mubardR   = new TH1F("dRmbar","dR distribution of mubar and jet",100,0.,2 * M_PI);
    TH1F *bdR     = new TH1F("dRb","dR distribution of b and jet",100,0.,2 * M_PI);
    TH1F *bbardR     = new TH1F("dRbbar","dR distribution of bbar and jet",100,0.,2 * M_PI);
    
    //create histogram d
    TH1F *multiplicity     = new TH1F("multiplicity","Jet multiplicities (after b bbar cut)",100,0.,100.);
    TH1F *pTjet     = new TH1F("pTjet","pT of Jets (after b bbar cut)",100,0.,300.);
    TH1F *phijet     = new TH1F("#phijet","#phi of Jets (after b bbar cut)",100,-4.,4.);
    TH1F *etajet     = new TH1F("#Etajet","#eta of Jets (after b bbar cut)",100,-4.,4.);
    
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
        
    }
    
    Long64_t nentriesb = ntupleb->GetEntries();
    for (Long64_t q=0;q<nentriesb;q++) {
        ntupleb->GetEntry(q);
    
        pT100->Fill(dpT);        //Histogram value b
        phi100->Fill(dphi);
        eta->Fill(deta);
        R->Fill(dR);
        inv->Fill(invm);
    }
    
    Long64_t nentriesc = ntuplec->GetEntries();
    for (Long64_t q=0;q<nentriesc;q++) {
        ntuplec->GetEntry(q);
    
        mudR->Fill(dRm);        //Histogram value c
        mubardR->Fill(dRmbar);
        bdR->Fill(dRb);
        bbardR->Fill(dRbbar);
    }
    
    Long64_t nentriesd = ntupled->GetEntries();
    for (Long64_t q=0;q<nentriesd;q++) {
        ntupled->GetEntry(q);
    
        multiplicity->Fill(mult);        //Histogram value
        pTjet->Fill(pT);
        phijet->Fill(phi);
        etajet->Fill(y);
        
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
        
        pT100->SetXTitle("#DeltapT[GeV]");
        pT100->SetYTitle("Event");
        phi100->SetXTitle("#Delta#phi");
        phi100->SetYTitle("Event");
        eta->SetXTitle("#eta");
        eta->SetYTitle("Event");
        R->SetXTitle("#DeltaR");
        R->SetYTitle("Event");
        inv->SetXTitle("m[GeV]");
        inv->SetYTitle("Event");
        
        mudR->SetXTitle("dR");
        mudR->SetYTitle("Event");
        mubardR->SetXTitle("dR");
        mubardR->SetYTitle("Event");
        bdR->SetXTitle("dR");
        bdR->SetYTitle("Event");
        bbardR->SetXTitle("dR");
        bbardR->SetYTitle("Event");
        
        multiplicity->SetXTitle("Mult.");
        multiplicity->SetYTitle("Jets");
        pTjet->SetXTitle("pT [GeV]");
        pTjet->SetYTitle("Jets");
        phijet->SetXTitle("#phi");
        phijet->SetYTitle("Jets");
        etajet->SetXTitle("#eta");
        etajet->SetYTitle("Jets");
    }
    
    
    cout << "jets->GetBinContent(1) = " << jets->GetBinContent(1) << endl;
    
    
    if (gROOT->IsBatch()) return;
    f->Write();
    new TBrowser();
    ntuple->StartViewer();
    
}

void read25e(){
    
    read25en();
    read25em();
    
}

/*Check function name.
 *Did you run Pythia8 first?
 */



