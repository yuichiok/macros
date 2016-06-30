Double_t fitfunc2(Double_t *x, Double_t *par)
{

Double_t fit = par[0]*exp(-0.5*((x[0]-par[1])/0.7)*((x[0]-par[1])/0.7));
return fit;

}

