from ROOT import *


d = TFile('unfoldeddata.root')
g = TFile('qcd_allpt_fixedresponses.root')

lumi = 40.

# Variables
d200 =d.Get('unfolded_0')
d300 =d.Get('unfolded_1')
d400 =d.Get('unfolded_2')
d500 =d.Get('unfolded_3')
d600 =d.Get('unfolded_4')
d700 =d.Get('unfolded_5')
d800 =d.Get('unfolded_6')

# Canvases
a140 =TCanvas("HLT_PFJet140mAK8Gen")
a200 =TCanvas("HLT_PFJet200mAK8Gen")
a260 =TCanvas("HLT_PFJet260mAK8Gen")
a320 =TCanvas("HLT_PFJet320mAK8Gen")
a400 =TCanvas("HLT_PFJet400mAK8Gen")
a450 =TCanvas("HLT_PFJet450mAK8Gen")
a500 =TCanvas("HLT_PFJet500mAK8Gen")

qtrue140 =g.Get("HLT_PFJet140mAK8Gen")
qtrue200 =g.Get("HLT_PFJet200mAK8Gen")
qtrue260 =g.Get("HLT_PFJet260mAK8Gen")
qtrue320 =g.Get("HLT_PFJet320mAK8Gen")
qtrue400 =g.Get("HLT_PFJet400mAK8Gen")
qtrue450 =g.Get("HLT_PFJet450mAK8Gen")
qtrue500 =g.Get("HLT_PFJet500mAK8Gen")

leg1 = TLegend(.6, .6, .8, .8)
leg2 = TLegend(.6, .6, .8, .8)
leg3 = TLegend(.6, .6, .8, .8)
leg4 = TLegend(.6, .6, .8, .8)
leg5 = TLegend(.6, .6, .8, .8)
leg6 = TLegend(.6, .6, .8, .8)
leg7 = TLegend(.6, .6, .8, .8)
alegends = [leg1, leg2, leg3, leg4, leg5, leg6, leg7]

datalist = [d200, d300, d400, d500, d600, d700, d800]
datacanvases= [a140, a200, a260, a320, a400, a450, a500]
MCtruth = [qtrue140, qtrue200, qtrue260, qtrue320, qtrue400, qtrue450, qtrue500]

titles = ["Data: Unfolded Jet Mass PT 140 to 200","Data: Unfolded Jet Mass PT 200 to 260", "Data: Unfolded Jet Mass PT 260 to 320", "Data: Unfolded Jet Mass PT 320 to 400", "Data: Unfolded Jet Mass PT 400 to 450", "Data: Unfolded Jet Mass PT 450 to 500", "Data: Unfolded Jet Mass PT 500 to 1000"]

for i in datacanvases:
    
    index = datacanvases.index(i)
    datacanvases[index].cd()
    datacanvases[index].SetLogy()
    datalist[index].SetTitle(titles[index])
    datalist[index].SetLineColor(2)
    datalist[index].Draw('hist')
    MCtruth[index].SetLineColor(3)
    MCtruth[index].Scale(lumi)
    MCtruth[index].Draw( "hist SAME" )
    alegends[index].AddEntry(MCtruth[index], 'PYTHIA8', 'l')
    alegends[index].AddEntry(datalist[index], 'Unfolded Data', 'l')
    alegends[index].Draw()