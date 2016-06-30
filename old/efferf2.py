import ROOT

n2 = ROOT.TH1F("n2", "Efficiency of Panels ; Voltage [V]; Efficiency", 100, 1580, 1980)

n2.Sumw2()

d2 = ROOT.TH1F("d2", "Denominator of Panel 2 ; PMT Operating Voltage (Volts); Trip Count", 100, 1580, 1980)

d2.Sumw2()

n3 = ROOT.TH1F("n3", "Numerator of Panel 3 ; PMT Operating Voltage (Volts); Quad Count", 100, 1580, 1980)

n3.Sumw2()

d3 = ROOT.TH1F("d3", "Numerator of Panel 3 ; PMT Operating Voltage (Volts); Quad Count", 100, 1580, 1980)

d3.Sumw2()

volt2 = [1980.,1960.,1940.,1920.,1900.,1880.,1860.,1840.,1820.,1800.,1780.,1760.,1740.,1720.,1700.,1680.,1660.,1640.,1620.,1600.,1580.]

c21 = [413.,406.,410.,405.,391.,376.,365.,365.,323.,253.,228.,176.,130.,108.,65.,45.,29.,25.,20.,14.,7.]

c22 = [499.,501.,503.,496.,499.,501.,503.,503.,500.,500.,502.,499.,503.,501.,504.,501.,504.,500.,503.,503.,502.]

c31 = [498.,493.,502.,497.,498.,496.,491.,483.,484.,454.,442.,396.,375.,293.,214.,166.,121.,95.,80.,51.,33.]

c32 = [501.,496.,504.,503.,501.,499.,503.,498.,504.,498.,498.,498.,506.,499.,496.,501.,501.,503.,502.,497.,500.]

for i in xrange(0,len(volt2)):
    n2.Fill(volt2[i], c21[i])
    d2.Fill(volt2[i], c22[i])
    n3.Fill(volt2[i], c31[i])
    d3.Fill(volt2[i], c32[i])

eff_2 = n2
eff_2.Divide(n2,d2,1.0,1.0,"B")

eff_3 = n3
eff_3.Divide(n3,d3,1.0,1.0,"B")

#Fit

fit1 = ROOT.TF1("fit1", "[0] + [1]*TMath::Erf((x-[2])/[3]) ",1580,1980)
fit2 = ROOT.TF1("fit2", "[0] + [1]*TMath::Erf((x-[2])/[3]) ",1580,1980)

fit1.SetParameters(0.4,0.4,1780.,100.)
fit2.SetParameters(0.,0.5,1710.,100.)


eff_2.Fit("fit1","r")
eff_3.Fit("fit2","r")

fit1.SetLineColor(2)
fit2.SetLineColor(4)

ROOT.gStyle.SetOptFit(1111)
c = ROOT.TCanvas("c1","c1",600, 600)

eff_2.SetMarkerStyle(20)
eff_2.SetMarkerColor(2)
eff_2.SetLineColor(2)

eff_3.SetMarkerStyle(20)
eff_3.SetMarkerColor(4)
eff_3.SetLineColor(4)

eff_2.Draw("E1")
eff_3.Draw("E1 same")
fit2.Draw("same" "c");
fit1.Draw("same" "c");

c.Update()
c.Draw()