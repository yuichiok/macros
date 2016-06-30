
Double_t fiteffec(Double_t *x, Double_t *par)
{
    Double_t my_erf = (0.5+.01*par[2])+(0.5+.01*par[3])*TMath::Erf(.01*par[0]*x[0]+(-18+par[1]));
    //Double_t my_erf = 1.0/(1.0+TMath::Exp(-x[0]*par[0]+par[1]));    
    return my_erf; 
}
