Double_t fitfunc(Double_t *x, Double_t *par)
{

Double_t fit = par[0]*cos(x[0]+par[1]);

return fit;
}

