#include "Riostream.h"
void read20a() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext20_2.txt");
    
    Float_t m;
    Int_t nlines = 0;
    TFile *f = new TFile("read20a.root","RECREATE");
    TNtuple *ntuple = new TNtuple("ntuple","data from reading20a file","m");
    
    while (1) {
        in >> m;
        if (!in.good()) break;
        if (nlines < 100) printf("m=%8f\n",m);
        ntuple->Fill(m);
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("m");
    
    in.close();
    
    f->Write();
}