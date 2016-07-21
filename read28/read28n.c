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



