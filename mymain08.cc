// Test program for top topbar background

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Pythia8/Pythia.h"
using namespace Pythia8;

int main() 
{
  // Book histograms.
  Hist e_pT("electron pT distribution", 100, 0., 250);
  Hist mu_pT("muon pT distribution", 100, 0., 250.);
  Hist e_e("electron e distribution", 100, 0., 250);
  Hist mu_e("muon e distribution", 100, 0., 250.); 
  Hist e_mu_invmass("electron - muon invariant mass", 100, 0., 250.); 

  // Generator. Process selection. LHC initialization.
  
  Pythia pythia;

  pythia.readString("Top:qqbar2ttbar = on");
  pythia.readString("Top:gg2ttbar = on");
  
  pythia.readString("PhaseSpace:mHatMin = 100.");
  pythia.readString("PhaseSpace:mHatMax = 5000.");

  pythia.readString("24:onMode = off");
  pythia.readString("24:6:onMode = 2");
  pythia.readString("24:7:onMode = 3");

  //pythia.init( 2212., 2212., 7000.);

  // Open output files
  std::ofstream outFile_4vec;
  std::ofstream outFile_emuinvmass;

  outFile_4vec.open("FourthTau_bgtt_4vec.txt");
  outFile_emuinvmass.open("FourthTau_bgtt_emuinvmass.txt");

  // Begin event loop. Generate event. Skip if error.
  for (int iEvent = 0; iEvent < 10000; ++iEvent) 
  {
    std::vector<int> Lid;
    if (!pythia.next()) continue;
    
    if (iEvent < 1) 
    {
    pythia.info.list(); 
    }

    if (iEvent < 5) 
    {
    pythia.event.list();
    }
  
  double etot=0.;
  double px=0.;
  double py=0.; 
  double pz=0.; 
    
  int ptmaxindex_e=-1;
  int ptmaxindex_mu=-1;
  double ptmax_e=10.;
  double ptmax_mu=10.;
  double phidiff=0.;
  
  bool bcheck=false;
  bool bbarcheck=false;

  // Loop over particles in event.
  for (int i = 0; i < pythia.event.size(); i++)
  {
    if( (fabs(pythia.event[i].id()) == 11 || fabs(pythia.event[i].id()) == 13) && pythia.event[i].status() > 0)
    {
    Lid.push_back(i); 
    }
    
    if(pythia.event[i].id()==5 && pythia.event[pythia.event[i].mother1()].id()==6 && pythia.event[i].pT()>20 && pythia.event[i].eta()<2.5)
    bcheck=true;
    
    if(pythia.event[i].id()==-5 && pythia.event[pythia.event[i].mother1()].id()==-6 && pythia.event[i].pT()>20 && pythia.event[i].eta()<2.5)
    bbarcheck=true;
  }
   
  for(unsigned int j=0; j < Lid.size(); j++)  
  {
    if( fabs(pythia.event[Lid[j]].id())==11 && pythia.event[Lid[j]].pT() > ptmax_e )
    {
    ptmax_e=pythia.event[Lid[j]].pT();
    ptmaxindex_e=j;
    }
    
    if( fabs(pythia.event[Lid[j]].id())==13 && pythia.event[Lid[j]].pT() > ptmax_mu )
    {
    ptmax_mu=pythia.event[Lid[j]].pT();
    ptmaxindex_mu=j;
    }
  }
  
  if(ptmaxindex_e == -1 || ptmaxindex_mu == -1)
  continue;

  phidiff = fabs(pythia.event[Lid[ptmaxindex_e]].phi() - pythia.event[Lid[ptmaxindex_mu]].phi());
  if (phidiff > 3.14159)
  phidiff= 6.28318 - phidiff;
 
  if(ptmaxindex_e != -1 && ptmaxindex_mu != -1 && phidiff < 2 && !bcheck && !bbarcheck)
    {
    px = pythia.event[Lid[ptmaxindex_e]].px() + pythia.event[Lid[ptmaxindex_mu]].px();
    py = pythia.event[Lid[ptmaxindex_e]].py() + pythia.event[Lid[ptmaxindex_mu]].py();
    pz = pythia.event[Lid[ptmaxindex_e]].pz() + pythia.event[Lid[ptmaxindex_mu]].pz();
    etot=pythia.event[Lid[ptmaxindex_e]].e() + pythia.event[Lid[ptmaxindex_mu]].e();
    e_mu_invmass.fill( sqrt(etot*etot - (px*px+py*py+pz*pz)) );

    outFile_4vec << iEvent << " " << Lid.size() << std::endl;
    outFile_4vec << pythia.event[Lid[ptmaxindex_e]].id()<<" "<<pythia.event[Lid[ptmaxindex_e]].px()<<" "<<pythia.event[Lid[ptmaxindex_e]].py()<<" "<<pythia.event[Lid[ptmaxindex_e]].pz()<<" "<<pythia.event[Lid[ptmaxindex_e]].e()<<std::endl;
    outFile_4vec << pythia.event[Lid[ptmaxindex_mu]].id()<<" "<<pythia.event[Lid[ptmaxindex_mu]].px()<<" "<<pythia.event[Lid[ptmaxindex_mu]].py()<<" "<<pythia.event[Lid[ptmaxindex_mu]].pz()<<" "<<pythia.event[Lid[ptmaxindex_mu]].e()<<std::endl;
    outFile_emuinvmass << iEvent << " " << Lid.size() << " " << sqrt(etot*etot - (px*px+py*py+pz*pz)) << std::endl;

    e_pT.fill( pythia.event[Lid[ptmaxindex_e]].pT() );
    e_e.fill( pythia.event[Lid[ptmaxindex_e]].e() );
 
    mu_pT.fill( pythia.event[Lid[ptmaxindex_mu]].pT() );
    mu_e.fill( pythia.event[Lid[ptmaxindex_mu]].e() );
    }

  }// End of event loop. Statistics. Histogram. Done.
    
  cout << endl << "Outputting histograms..." << endl;
  cout << "tau mass: " <<  ParticleDataTable::m0(15) << " GeV" << endl;
  cout << e_pT;
  cout << mu_pT;
  cout << e_e;
  cout << mu_e;
  cout << e_mu_invmass;
  cout << endl << "Done!" << endl;

  outFile_4vec.close();
  outFile_emuinvmass.close();

  pythia.statistics();
  return 0;
}


