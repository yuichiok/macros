Float_t ptcalc(Float_t px, Float_t py);
Float_t invariant(Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t);
void drcalc(Float_t phi1, Float_t phi2, Float_t y1, Float_t y2, Float_t *pdphi, Float_t *pdeta, Float_t *pdR);

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
    Float_t invm,numberrm = 0;
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
    
    
    
    
    
    
    //Histogram
    TH1F *higg          = new TH1F("hm","Higgs invariant mass distribution",100,0,300.);
    TH1F *zboson        = new TH1F("zm","Z0 invariant mass distribution",100,0,300.);
    TH1F *bpT           = new TH1F("bpT","b quark pT distribution",100,0,300.);
    TH1F *mpT           = new TH1F("mupT","Muon pT distribution",100,0,300.);
    TH1F *bEta          = new TH1F("bEta","b quark Eta distribution",100,-4.,4.);
    TH1F *mEta          = new TH1F("muEta","Muon Eta distribution",100,-4.,4.);
    TH1F *pTHhist       = new TH1F("pTH","Higgs boson pT distribution",100,0.,300.);
    TH1F *pTZhist       = new TH1F("pTZ","Z boson pT distribution",100,0.,300.);
    TH1F *dpTHZhist     = new TH1F("dpTHZ","dpT between H and Z",100,-200,200.);
    TH2F *bpTy          = new TH2F("bphiy","b bbar pT vs. Jet #eta",100,-4.,4.,100,0.,300.);
    TH1F *inv           = new TH1F("invm","Di-jet invariant mass distribution (after b bbar cut)",100,0.,250.);
    TH1F *Ebhist        = new TH1F("Eb","Energy of b",100,0.,300.);
    TH1F *Ejethist      = new TH1F("Ejet","Energy of jet",100,0.,300.);
    TH1F *pTbhist       = new TH1F("pTjetb","pT comparison of b and jet",100,0,300.);
    TH1F *pTjethist     = new TH1F("pTjet","pT cof jet",100,0,300.);
    TH2F *jetphiy       = new TH2F("jetphiy","Jet #phi vs. Jet #eta",100,-4.,4.,100,-4.,4.);
    TH2F *jetpTy        = new TH2F("jetpTy","pT vs #eta of jet and b",100,-7.,7.,100,0.,300.);
    
    
    
    
    
    
    for(int iEntry=0; iEntry<nEntry ;++iEntry)
    {
        //cout << "This is " << iEntry << " th event" << string(114,'=') << endl;
        
        //variable
        Float_t pTZ,pTb,pTbbar;
        bool ZCheck = false;
        bool EtabCheck = false;
        bool pTbCheck = false;
        
        //Obtain entry of one event
        tree->GetEntry(iEntry);
        
        //pT calcuation
        pTZ = ptcalc(pxz,pyz);
        pTb = ptcalc(pxb,pyb);
        pTbbar = ptcalc(pxbbar,pybbar);
        
        //Z, b, bbar cut
        if(pTZ>250) ZCheck = true;
        if(abs(etab) <= 2.4 && abs(etabbar) <= 2.4) EtabCheck = true;
        if(pTb >= 20. && pTbbar >= 20.) pTbCheck = true;
        
        
        //if the event satisfy event...
        if(ZCheck == true && EtabCheck == true && pTbCheck == true){
            
            //Jet selection
            int tempp1=0,tempp2=0;
            double tempdR1 = 100.,tempdR2 = 100.;
            for(int p = 0; p < nJet;++p)
            {
                //calculation of dR between b,bbar,mu-,mu+
                drcalc(phijet[p],phib,etajet[p],etab,&dphib,&detab,&dRb);
                drcalc(phijet[p],phibbar,etajet[p],etabbar,&dphibbar,&detabbar,&dRbbar);
                drcalc(phijet[p],phim,etajet[p],etam,&dphim,&detam,&dRm);
                drcalc(phijet[p],phimbar,etajet[p],etambar,&dphimbar,&detambar,&dRmbar);
                
                //cout << "jet" << p << ", dRb = " << dRb << ", dRbbar = " << dRbbar << endl;
                
                //take smallest dR between b and jet
                if(dRb < tempdR1 && (dRm > 0.1 || dRmbar > 0.1)){
                    tempp1 = p;
                    tempdR1 = dRb;
                }
                
                //take smallest dR between bbar and jet
                if(dRbbar < tempdR2 && (dRm > 0.1 || dRmbar > 0.1)){
                    tempp2 = p;
                    tempdR2 = dRbbar;
                }
                
            }//end Jet selection
            
            //number of b and bbar jet coincide
            if(tempp1 == tempp2) numberrm++;
            
            //di-jet invariant mass calculation
            if(tempp1 != tempp2 && tempdR1 < 0.3 && tempdR2 < 0.3){
                
                invm = invariant(mjet[tempp1],mjet[tempp2],ejet[tempp1],ejet[tempp2],pxjet[tempp1],pxjet[tempp2],pyjet[tempp1],pyjet[tempp2],pzjet[tempp1],pzjet[tempp2]);
                
                inv->Fill(invm);
                
            }
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
        }//if Check
        
        //cout << endl;
        
    }//end iEntry
    
    cout << "number of jet coincide with b and bbar = " << numberrm << endl;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}//end read28m()

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
    
}
