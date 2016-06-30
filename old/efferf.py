from pylab import *
import matplotlib.pyplot as plt
import numpy as np
import ROOT
from ROOT import TMath

# This script follows from examples here:
# http://sdtidbits.blogspot.com/2009/03/curve-fitting-and-plotting-in-python.html


volt2 = np.genfromtxt('effPan2.txt', delimiter='\t', usecols = 0)
eff2 = np.genfromtxt('effPan2.txt', delimiter='\t', usecols = 1)

volt3 = np.genfromtxt('effPan3.txt', delimiter='\t', usecols = 0)
eff3 = np.genfromtxt('effPan3.txt', delimiter='\t', usecols = 1)
print volt2
print eff2

eff_2 = ROOT.TH1F("Eff2", "Efficiency of Panel 2 ; PMT Operating Voltage (Volts); Efficiency", 100, 1560, 1980)

#eff_3 = ROOT.TH1F("Eff3", "Efficiency of Panel 3 ; PMT Operating Voltage (Volts); Efficiency", 100, 1560, 1980, 100, 0, 1)
for i in xrange(0,len(volt2)):
    eff_2.Fill(volt2[i] , eff2[i])

#eff_3.Fill(volt3 , eff3)

#fitting
#t2 = ROOT.TMath.Erf(volt2)

#fit2 = ROOT.TF1("fitter2", "[0] + [1]*TMath::Erf( [2] * x + [3]) ", 1560, 1980)
fit2 = ROOT.TF1("fitter2", "[0] + [1]*TMath::Erf((x-[2])/[3]) ", 1560, 1980)
fit2.SetParameters(1. , 0.4 , 1680. , 20.)

ROOT.gStyle.SetOptFit(1111)
c = ROOT.TCanvas("c1","c1",600, 600)
eff_2.SetMarkerStyle(20)
#eff_2.SetMarkerSize(2)
eff_2.Draw("P")
eff_2.Fit("fitter2","R" )
fit2.Draw("same C")

#p2 = ROOT.TGraph(100, volt2 , eff2)
#p2.Fit("fitter2")
#p2.Draw("al")

c.Update()
c.Draw()

name = 'EfficiencyPanel2'
c.Print( name + '.png', 'png') 

