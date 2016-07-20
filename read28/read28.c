#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"

//Float_t ptcalc(Float_t px, Float_t py);
//Float_t invariant(Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t);
//void drcalc(Float_t phi1, Float_t phi2, Float_t y1, Float_t y2, Float_t *pdphi, Float_t *pdeta, Float_t *pdR);


//reading part ==========================================================================================
void read28n() {
    ifstream ina;
    ifstream inb;
    ina.open("/Users/Yuichi/root/macros/mytext28/mytext28a.txt");
    inb.open("/Users/Yuichi/root/macros/mytext28/mytext28b.txt");    //Check
    
    //Variables
    Float_t pxb,pyb,pzb,eb,mb,etab,phib;
    Float_t pxbbar,pybbar,pzbbar,ebbar,mbbar,etabbar,phibbar;
    Float_t pxm,pym,pzm,em,mm,etam,phim;
    Float_t pxmbar,pymbar,pzmbar,embar,mmbar,etambar,phimbar;
    Float_t pxh,pyh,pzh,eh,mh,etah,phih;
    Float_t pxz,pyz,pzz,ez,mz,etaz,phiz;
    Float_t pxjet[100],pyjet[100],pzjet[100],ejet[100],mjet[100],etajet[100],phijet[100];
    Int_t nJet;
    Int_t nlinesb = 0;
    
    TFile *f = new TFile("read28.root","RECREATE");
    
    TTree *tree = new TTree("tree","Reconst ntuple");
    
    tree->Branch("pxb",&pxb,"pxb/F");
    tree->Branch("pyb",&pyb,"pyb/F");
    tree->Branch("pzb",&pzb,"pzb/F");
    tree->Branch("eb",&eb,"eb/F");
    tree->Branch("mb",&mb,"mb/F");
    tree->Branch("etab",&etab,"etab/F");
    tree->Branch("phib",&phib,"phib/F");
    
    tree->Branch("pxbbar",&pxbbar,"pxbbar/F");
    tree->Branch("pybbar",&pybbar,"pybbar/F");
    tree->Branch("pzbbar",&pzbbar,"pzbbar/F");
    tree->Branch("ebbar",&ebbar,"ebbar/F");
    tree->Branch("mbbar",&mbbar,"mbbar/F");
    tree->Branch("etabbar",&etabbar,"etabbar/F");
    tree->Branch("phibbar",&phibbar,"phibbar/F");
    
    tree->Branch("pxm",&pxm,"pxm/F");
    tree->Branch("pym",&pym,"pym/F");
    tree->Branch("pzm",&pzm,"pzm/F");
    tree->Branch("em",&em,"em/F");
    tree->Branch("mm",&mm,"mm/F");
    tree->Branch("etam",&etam,"etam/F");
    tree->Branch("phim",&phim,"phim/F");
    
    tree->Branch("pxmbar",&pxmbar,"pxmbar/F");
    tree->Branch("pymbar",&pymbar,"pymbar/F");
    tree->Branch("pzmbar",&pzmbar,"pzmbar/F");
    tree->Branch("embar",&embar,"embar/F");
    tree->Branch("mmbar",&mmbar,"mmbar/F");
    tree->Branch("etambar",&etambar,"etambar/F");
    tree->Branch("phimbar",&phimbar,"phimbar/F");
    
    tree->Branch("pxh",&pxh,"pxh/F");
    tree->Branch("pyh",&pyh,"pyh/F");
    tree->Branch("pzh",&pzh,"pzh/F");
    tree->Branch("eh",&eh,"eh/F");
    tree->Branch("mh",&mh,"mh/F");
    tree->Branch("etah",&etah,"etah/F");
    tree->Branch("phih",&phih,"phih/F");
    
    tree->Branch("pxz",&pxz,"pxz/F");
    tree->Branch("pyz",&pyz,"pyz/F");
    tree->Branch("pzz",&pzz,"pzz/F");
    tree->Branch("ez",&ez,"ez/F");
    tree->Branch("mz",&mz,"mz/F");
    tree->Branch("etaz",&etaz,"etaz/F");
    tree->Branch("phiz",&phiz,"phiz/F");
    
    tree->Branch("nJet",&nJet,"nJet/I");
    
    tree->Branch("pxjet",pxjet,"pxjet[nJet]/F");
    tree->Branch("pyjet",pyjet,"pyjet[nJet]/F");
    tree->Branch("pzjet",pzjet,"pzjet[nJet]/F");
    tree->Branch("ejet",ejet,"ejet[nJet]/F");
    tree->Branch("mjet",mjet,"mjet[nJet]/F");
    tree->Branch("etajet",etajet,"etajet[nJet]/F");
    tree->Branch("phijet",phijet,"phijet[nJet]/F");
    
    for(int iEvent=0; iEvent<10000;++iEvent)
    {
        inb >> pxb >> pyb >> pzb >> eb >> mb >> etab >> phib >> pxbbar >> pybbar >> pzbbar >> ebbar >> mbbar >> etabbar >> phibbar >> pxm >> pym >> pzm >> em >> mm >> etam >> phim >> pxmbar >> pymbar >> pzmbar >> embar >> mmbar >> etambar >> phimbar >> pxh >> pyh >> pzh >> eh >> mh >> etah >> phih >> pxz >> pyz >> pzz >> ez >> mz >> etaz >> phiz >> nJet;
        
        for(int iJet=0; iJet < nJet; ++iJet)
        {
            ina >> pxjet[iJet] >> pyjet[iJet] >> pzjet[iJet] >> ejet[iJet] >> mjet[iJet] >> etajet[iJet] >> phijet[iJet];
        }
        
        tree->Fill();
    }
    
    ina.close();
    inb.close();
    
    f->Write();
    f->Close();delete f;
}

//Historgram part =======================================================================================
/*
void read28m(){
    
    //Variables
    Float_t pxb,pyb,pzb,eb,mb,etab,phib;
    Float_t pxbbar,pybbar,pzbbar,ebbar,mbbar,etabbar,phibbar;
    Float_t pxm,pym,pzm,em,mm,etam,phim;
    Float_t pxmbar,pymbar,pzmbar,embar,mmbar,etambar,phimbar;
    Float_t pxh,pyh,pzh,eh,mh,etah,phih;
    Float_t pxz,pyz,pzz,ez,mz,etaz,phiz;
    Float_t pxjet[100],pyjet[100],pzjet[100],ejet[100],mjet[100],etajet[100],phijet[100];
    Float_t dphib,detab,dRb;
    Float_t dphibbar,detabbar,dRbbar;
    Float_t dphim,detam,dRm;
    Float_t dphimbar,detambar,dRmbar;
    Int_t nJet;
    
    TFile *f = new TFile("read28.root","READ");
    TTree *tree = (TTree*)f->Get("tree");
    
    int nEntry = tree->GetEntries();
    
    //Set branch address
    tree->SetBranchAddress("pxb",&pxb);
    tree->SetBranchAddress("pyb",&pyb);
    tree->SetBranchAddress("pzb",&pzb);
    tree->SetBranchAddress("eb",&eb);
    tree->SetBranchAddress("mb",&mb);
    tree->SetBranchAddress("etab",&etab);
    tree->SetBranchAddress("phib",&phib);
    
    tree->SetBranchAddress("pxbbar",&pxbbar);
    tree->SetBranchAddress("pybbar",&pybbar);
    tree->SetBranchAddress("pzbbar",&pzbbar);
    tree->SetBranchAddress("ebbar",&ebbar);
    tree->SetBranchAddress("mbbar",&mbbar);
    tree->SetBranchAddress("etabbar",&etabbar);
    tree->SetBranchAddress("phibbar",&phibbar);
    
    tree->SetBranchAddress("pxm",&pxm);
    tree->SetBranchAddress("pym",&pym);
    tree->SetBranchAddress("pzm",&pzm);
    tree->SetBranchAddress("em",&em);
    tree->SetBranchAddress("mm",&mm);
    tree->SetBranchAddress("etam",&etam);
    tree->SetBranchAddress("phim",&phim);
    
    tree->SetBranchAddress("pxmbar",&pxmbar);
    tree->SetBranchAddress("pymbar",&pymbar);
    tree->SetBranchAddress("pzmbar",&pzmbar);
    tree->SetBranchAddress("embar",&embar);
    tree->SetBranchAddress("mmbar",&mmbar);
    tree->SetBranchAddress("etambar",&etambar);
    tree->SetBranchAddress("phimbar",&phimbar);
    
    tree->SetBranchAddress("pxh",&pxh);
    tree->SetBranchAddress("pyh",&pyh);
    tree->SetBranchAddress("pzh",&pzh);
    tree->SetBranchAddress("eh",&eh);
    tree->SetBranchAddress("mh",&mh);
    tree->SetBranchAddress("etah",&etah);
    tree->SetBranchAddress("phih",&phih);
    
    tree->SetBranchAddress("pxz",&pxz);
    tree->SetBranchAddress("pyz",&pyz);
    tree->SetBranchAddress("pzz",&pzz);
    tree->SetBranchAddress("ez",&ez);
    tree->SetBranchAddress("mz",&mz);
    tree->SetBranchAddress("etaz",&etaz);
    tree->SetBranchAddress("phiz",&phiz);
    
    tree->SetBranchAddress("nJet",&nJet);
    
    tree->SetBranchAddress("pxjet",pxjet);
    tree->SetBranchAddress("pyjet",pyjet);
    tree->SetBranchAddress("pzjet",pzjet);
    tree->SetBranchAddress("ejet",ejet);
    tree->SetBranchAddress("mjet",mjet);
    tree->SetBranchAddress("etajet",etajet);
    tree->SetBranchAddress("phijet",phijet);
    
    
    //Analysis
    for(int iEntry=0; iEntry<nEntry ;++iEntry)
    {
        //variable
        
        
        //Obtain entry of one event
        tree->GetEntry(iEntry);
        
        
        
        
    }//end iEntry
    
    
}//end read28m()

void read28(){
    
    read28n();
    read28m();
    
}

Float_t ptcalc(Float_t px, Float_t py){
    
    Float_t pt;
    
    pt = sqrt(px*px + py*py);
    
    return pt;
}

Float_t invariant(Float_t m1,Float_t m2,Float_t e1,Float_t e2,Float_t px1,Float_t px2,Float_t py1,Float_t py2,Float_t pz1,Float_t pz2){
    
    Float_t a;
    
    a = sqrt(m1*m1 + m2*m2 + 2*(e1*e2 - px1*px2 - py1*py2 - pz1*pz2));
    
    return a;
}

void drcalc(Float_t phi1, Float_t phi2, Float_t y1, Float_t y2, Float_t *pdphi, Float_t *pdeta, Float_t *pdR){
    
    *pdphi = abs( phi1 - phi2 );
    *pdeta = y1 - y2;
    if(*pdphi > M_PI) *pdphi = 2. * M_PI - *pdphi;
    *pdR = sqrt( (*pdeta) * (*pdeta) + (*pdphi) * (*pdphi) );
    
}*/



/*Check function name.
 *Did you run Pythia8 first?
 */



