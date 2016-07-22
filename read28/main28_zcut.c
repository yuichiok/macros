#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "Riostream.h"
#include <iostream>

void main28_zcut(){
    
    gROOT->ProcessLine(".x read28n.c");
    gROOT->ProcessLine(".x read28m_zcut.c");
    
}