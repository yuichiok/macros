/* calculate_eff.C

   This routine calculates the ratio (of two histos) with asymmetric errors

                                 Created: July 2008, Avto Kharchilava
*/

void Calculate_eff.C{
    
  Int_t nbins     =   nominator->GetNbinsX();
  Int_t nbins_den = denominator->GetNbinsX();
  //  cout << "nbins = " << nbins << endl;
  if(nbins != nbins_den) {
    cout << ">>> ERROR in calculate: uneaqual # of bins <<<" << endl;
    return 1;
  }

  TH1F *nom=(TH1F*)nominator->Clone();
  TH1F *den=(TH1F*)denominator->Clone();
  nom->Reset();
  den->Reset();
  nom->Sumw2();
  den->Sumw2();

  Double_t x[99999] ={0}; // For a large number of bins ...
  Double_t cont_n[99999] ={0};
  Double_t cont_d[99999] ={0};

  for(Int_t j = 1; j<=nbins; j++){
    x[j] = nominator->GetBinLowEdge(j);
    //    cout << "x[j] = " << x[j] << endl;
    cont_n[j] = nominator->GetBinContent(j);
    cont_d[j] = denominator->GetBinContent(j);
    //    cout << "cont_n[j] = "<<cont_n[j]<<" cont_d[j] = "<<cont_d[j]<<endl;
   };

  // Fill histos with unit w=1 ...
  for(Int_t j=1; j<=nbins; j++){

    for(Int_t i=1; i<=cont_n[j]; i++){ // Divide by 100 just to enlarge errors
      nom->Fill(x[j],1); 
    };

    for(Int_t k=1; k<=cont_d[j]; k++){ // --"--
      den->Fill(x[j],1);
    };
    
  };
  
  result->BayesDivide(nom,den,"w");
}
