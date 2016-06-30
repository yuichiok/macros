#include "Riostream.h"
void read20() {
    ifstream in;
    in.open("/Users/Yuichi/root/macros/mytext20.txt");
    
    Float_t px,py,pT;
    Int_t nlines = 0;
    TFile *f = new TFile("read20.root","RECREATE");
    TNtuple *ntuple = new TNtuple("ntuple","data from reading20 file","px:py:pT");
    
    while (1) {
        in >> px >> py >> pT;
        if (!in.good()) break;
        if (nlines < 100) printf("px=%8f, py=%8f, pT=%8f\n",px,py,pT);
        ntuple->Fill(px,py,pT);
        nlines++;
    }
    printf(" found %d points\n",nlines);
    ntuple->Scan("px:py:pT");
    
    in.close();
    
    f->Write();
}