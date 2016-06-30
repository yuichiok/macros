from pylab import *
import matplotlib.pyplot as plt
import numpy as np
import ROOT
from ROOT import TMath

# This script follows from examples here:
# http://sdtidbits.blogspot.com/2009/03/curve-fitting-and-plotting-in-python.html


d = np.genfromtxt('decay.txt', delimiter='\t', usecols = 0)

dec = ROOT.TH1F("dec", "Muon Decay ; Number of Counts; Time separation  (nanosecond) ", 22, 0, 11)

#eff_3 = ROOT.TH1F("Eff3", "Efficiency of Panel 3 ; PMT Operating Voltage (Volts); Efficiency", 100, 1560, 1980, 100, 0, 1)
for i in xrange(0,len(d)-1):
    dec.Fill(d[i])

#eff_3.Fill(volt3 , eff3)

#fitting

fit2 = ROOT.TF1("fitter2", "[0] + [1]*TMath::Exp(-x/[2])", 0.2, 10)
fit2.SetParameters(1. , 1. , 2.)

ROOT.gStyle.SetOptFit(1111)
c = ROOT.TCanvas("c1","c1",600, 600)
#dec.SetMarkerStyle(20)
#eff_2.SetMarkerSize(2)
dec.Draw("C")
dec.Fit("fitter2","R" )
fit2.Draw("same C")

#p2 = ROOT.TGraph(100, volt2 , eff2)
#p2.Fit("fitter2")
#p2.Draw("al")

c.Update()
c.Draw()

name = 'decayRateMuon'
c.Print( name + '.png', 'png') 

