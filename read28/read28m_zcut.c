Float_t ptcalc(Float_t px, Float_t py);
Float_t invariant(Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t);
void drcalc(Float_t phi1, Float_t phi2, Float_t y1, Float_t y2, Float_t *pdphi, Float_t *pdeta, Float_t *pdR);
double cross_sec(double sig_ref, double N, double Nref);

void read28m_zcut(){
    
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
    Float_t invm;
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
    
    
    
    int n = 55;
    double eff[n];
    double cross[n];
    double zcut[n];
    double sigz;
    
    TH1F *inv[n];
    char name[30];
    char title[100];
    
    //analyze for different zcut
    for(int i=0; i<n ; i++){
        
        sprintf(name,"h%d",i*10);
        sprintf(title,"Di-jet invariant mass distribution with ZpT cut %d GeV",i*10);
        
        inv[i] = new TH1F(name,title,100,0.,250.);
        inv[i]->SetXTitle("inv mass [GeV]");
        inv[i]->SetYTitle("Events");
        
        
        
        int znumber = 0;
        double all_Event = 0,selected_Event = 0;
        
        for(int iEntry=0; iEntry<nEntry ;++iEntry)
        {
            //Obtain entry of one event
            tree->GetEntry(iEntry);
            
            //cout << "This is " << iEntry << " th event" << string(114,'=') << endl;
            
            //variable
            Float_t pTZ,pTH,pTb,pTbbar,pTm,pTmbar;
            bool ZCheck = false;
            bool EtabCheck = false;
            bool pTbCheck = false;
            
            //pT calcuation
            pTZ     = ptcalc(pxz,pyz);
            pTH     = ptcalc(pxh,pyh);
            pTb     = ptcalc(pxb,pyb);
            pTbbar  = ptcalc(pxbbar,pybbar);
            pTm     = ptcalc(pxm,pym);
            pTmbar  = ptcalc(pxmbar,pymbar);
            
            
            //Z, b, bbar cut
            if(pTZ > i*10) ZCheck = true;
            if(abs(etab) <= 2.4 && abs(etabbar) <= 2.4) EtabCheck = true;
            if(pTb >= 20. && pTbbar >= 20.) pTbCheck = true;
            
            
            //if the event satisfy event...
            if(ZCheck == true && EtabCheck == true && pTbCheck == true){
                
                ++znumber;
                
                //Jet Analysis=============================================================================================================================================
                
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
                
                //di-jet anlysis
                if(tempp1 != tempp2 && tempdR1 < 0.3 && tempdR2 < 0.3){
                    
                    invm = invariant(mjet[tempp1],mjet[tempp2],ejet[tempp1],ejet[tempp2],pxjet[tempp1],pxjet[tempp2],pyjet[tempp1],pyjet[tempp2],pzjet[tempp1],pzjet[tempp2]);
                    
                    inv[i]->Fill(invm);
                    
                    selected_Event++;
                }
                
                
                //non Jet Analysis=========================================================================================================================================
                
                all_Event++;
                
                
            }//if Check
            
            //cout << endl;
            
        }//end iEntry
        
        zcut[i] = i*10;
        
        //cout << "analysis" << i << ": all = " << all_Event << ", selected = " << selected_Event << endl;
        
        //calculation of cross section
        sigz = cross_sec(11.67,all_Event,100000);
        
        cross[i] = cross_sec(sigz,selected_Event,all_Event);
        
        //calculation of efficiency
        eff[i] = selected_Event/all_Event;
        
        
        
        
    }//end of i<n loop
    
    TCanvas *c1 = new TCanvas("c1","multipads",1000,500);
    gStyle->SetOptStat(1);
    c1->Divide(2,1,0.02,0.02);
    
    //graph cross section
    c1->cd(1);
    TGraph *crossgraph = new TGraph(n,zcut,cross);
    crossgraph->SetTitle("Cross section vs. ZpT cut");
    crossgraph->GetXaxis()->SetTitle("Z pT [GeV]");
    crossgraph->GetYaxis()->SetTitle("Cross Section [fb]");
    crossgraph->GetXaxis()->SetRangeUser(-5.,555.);
    crossgraph->SetLineWidth(2);
    crossgraph->SetLineColor(2);
    crossgraph->SetMarkerStyle(21);
    crossgraph->Draw();
    
    c1->cd(2);
    TGraph *effgraph = new TGraph(n,zcut,eff);
    effgraph->SetTitle("Jet reconstruction efficiency vs. ZpT cut");
    effgraph->GetXaxis()->SetTitle("Z pT [GeV]");
    effgraph->GetYaxis()->SetTitle("Efficiency");
    effgraph->GetXaxis()->SetRangeUser(-5.,555.);
    effgraph->GetYaxis()->SetRangeUser(0.,1.1);
    effgraph->SetLineWidth(2);
    effgraph->SetLineColor(2);
    effgraph->SetMarkerStyle(21);
    effgraph->Draw();
    
    
    
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

double cross_sec(double sig_ref, double N, double Nref){
    
    double sig;
    
    sig = sig_ref * (N / Nref);
    
    return sig;
    
}
