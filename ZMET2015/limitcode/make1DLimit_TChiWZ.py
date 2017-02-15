import ROOT, array
import sys, glob
ROOT.gROOT.SetBatch(True)
lumi = 36.8

fxsec = None
hxsec = None

def get1Dlimit(fn):
    f = ROOT.TFile.Open(fn)
    tree= f.Get("limit")
    limits = []
    for entry in tree:
        limits.append(entry.limit)
    limitsdic = {'m2s':limits[0],'m1s':limits[1],'exp':limits[2],'p1s':limits[3],'p2s':limits[4],'obs':limits[5]}
    return limitsdic

def get1Dxsec(charginomass):
    global fxsec, hxsec
    if not fxsec or not hxsec:
        fxsec = ROOT.TFile.Open("../../dilepbabymaker/xsec_susy_13tev.root")
        hxsec = fxsec.Get("h_xsec_c1n2")
    sigma = hxsec.GetBinContent(hxsec.FindBin(charginomass)) 
    return sigma
    
def main():
    version = "test_TChiWZ"
    dir="./"+version+"/"
#    chargino_masses =[100,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750] 
    chargino_masses =[100,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700] 
    f_xsecgraph = ROOT.TFile.Open("../../dilepbabymaker/xsec_susy_13tev_graphs.root")
    g_xsec_c1n2 = f_xsecgraph.Get("g_xsec_c1n2")

    obs=[]
    exp=[]
    m2s=[]
    m1s=[]
    p1s=[]
    p2s=[]
    x0e=[]
    sigmas = []
    
    for chargino in chargino_masses:
        fn = dir+'limit_TChiWZ_'+str(chargino)+'_0.root'
        limitsdic = get1Dlimit(fn)
        xsec = get1Dxsec(chargino)
        obs.append(limitsdic['obs']*xsec)
        exp.append(limitsdic['exp']*xsec)
        m2s.append(limitsdic['m2s']*xsec)
        m1s.append(limitsdic['m1s']*xsec)
        p1s.append(limitsdic['p1s']*xsec)
        p2s.append(limitsdic['p2s']*xsec)
        x0e.append(0.)
        sigmas.append(xsec) 
    #TGraphAsymmErrors needs the delta
    for i in range(0,len(exp)):
        m2s[i]=exp[i]-m2s[i]
        m1s[i]=exp[i]-m1s[i]
        p1s[i]=p1s[i]-exp[i]
        p2s[i]=p2s[i]-exp[i]
    
    ROOT.gStyle.SetOptStat(0)
    c1 = ROOT.TCanvas("c1", "", 800, 800)
    c1.cd()
    padt = ROOT.TPad("p_tex", "p_tex", 0.0, 0.0, 1.0, 1.0)
    padt.SetTopMargin(0.1)
    padt.SetBottomMargin(0.1)
    padt.SetRightMargin(0.05)
    padt.SetLeftMargin(0.15)
    padt.SetTickx()
    padt.SetTicky()
    padt.Draw()
    padt.cd()
    padt.SetLogy() 
    h = ROOT.TH2F("h","h",48,100,700,1000,0.001,1000)
    h.SetTitle("")
    h.GetXaxis().SetTitle("m_{#tilde{#chi}^{#pm}_{1}} = m_{#tilde{#chi}^{0}_{2}} [GeV]")
    h.GetYaxis().SetTitle("#sigma limit at 95% CL [pb]")
    h.GetXaxis().SetLabelSize(0.04)
    h.GetYaxis().SetLabelSize(0.04)
    h.GetXaxis().SetTitleSize(0.042)
    h.GetYaxis().SetTitleSize(0.042)
    h.GetXaxis().SetTitleOffset(1.0)
    h.GetYaxis().SetTitleOffset(1.5)
    h.Draw()
    
    gr_s2b = ROOT.TGraphAsymmErrors(len(chargino_masses),array.array('d', chargino_masses),array.array('d', exp),array.array('d', x0e),array.array('d', x0e),array.array('d', m2s),array.array('d', p2s))
    gr_s2b.SetFillColor(ROOT.kYellow)
    gr_s2b.Draw("3")
      
    gr_s1b = ROOT.TGraphAsymmErrors(len(chargino_masses),array.array('d', chargino_masses),array.array('d', exp),array.array('d', x0e),array.array('d', x0e),array.array('d', m1s),array.array('d', p1s))
    gr_s1b.SetFillColor(ROOT.kGreen)
    gr_s1b.Draw("3")
    
    gexp = ROOT.TGraph(len(chargino_masses), array.array('d', chargino_masses), array.array('d', exp))
    gexp.SetLineStyle(7)
    gexp.SetLineWidth(3)
    gexp.SetLineColor(ROOT.kBlack)
    gexp.Draw("L")
    
    gsigmas = ROOT.TGraph(len(chargino_masses), array.array('d', chargino_masses), array.array('d', sigmas))
    gsigmas.SetLineStyle(7)
    gsigmas.SetLineWidth(3)
    gsigmas.SetLineColor(ROOT.kRed)
#    gsigmas.Draw("L")
    g_xsec_c1n2.SetFillColor(ROOT.kMagenta)
    g_xsec_c1n2.Draw("3 same")
    gobs = ROOT.TGraph(len(chargino_masses), array.array('d', chargino_masses), array.array('d', obs))
    gobs.SetMarkerStyle(ROOT.kFullCircle)
    gobs.SetMarkerSize(1.5)
    gobs.SetMarkerColor(ROOT.kBlue)
    gobs.SetLineWidth(3)
    gobs.SetLineColor(ROOT.kBlue)
    gobs.Draw("L")
   
    prctex = ROOT.TLatex(0.45,0.83, "pp #rightarrow #tilde{#chi}^{#pm}_{1} #tilde{#chi}^{0}_{2}; m_{#tilde{#chi}^{0}_{1}} = 1 GeV");
    prctex.SetNDC()    
    prctex.SetTextSize(0.032)    
    prctex.SetLineWidth(2)
    prctex.SetTextFont(42)    
    prctex.Draw()

    prctex2 = ROOT.TLatex(0.45,0.77, "#tilde{#chi}^{#pm}_{1}#rightarrow W^{#pm} #tilde{#chi}_{1}^{0}, #tilde{#chi}^{0}_{2}#rightarrow Z #tilde{#chi}_{1}^{0}" );    
    prctex2.SetNDC()    
    prctex2.SetTextSize(0.032)    
    prctex2.SetLineWidth(2)
    prctex2.SetTextFont(42)    
    prctex2.Draw()
 
    cmstex = ROOT.TLatex(0.675,0.91, "%.1f fb^{-1} (13 TeV)" % lumi)
    cmstex.SetNDC()
    cmstex.SetTextSize(0.04)
    cmstex.SetLineWidth(2)
    cmstex.SetTextFont(42)
    cmstex.Draw()
    
    cmstexbold = ROOT.TLatex(0.17,0.91, "CMS" )
    cmstexbold.SetNDC()
    cmstexbold.SetTextSize(0.05)
    cmstexbold.SetLineWidth(2)
    cmstexbold.SetTextFont(61)
    cmstexbold.Draw()
    
    cmstexprel = ROOT.TLatex(0.29,0.91, "Preliminary" )
    cmstexprel.SetNDC()
    cmstexprel.SetTextSize(0.03)
    cmstexprel.SetLineWidth(2)
    cmstexprel.SetTextFont(52)
    cmstexprel.Draw()
    
    l1 = ROOT.TLegend(0.45, 0.55, 0.9, 0.74)
    l1.SetTextFont(42)
    l1.SetTextSize(0.036)
    l1.SetLineColor(ROOT.kWhite)
    l1.SetShadowColor(ROOT.kWhite)
    l1.SetFillColor(ROOT.kWhite)
#    l1.SetHeader("#sigma exclusion limit, M_{#tilde{#chi}^{0}_{1}} = 1 GeV")
    l1.AddEntry(gobs , "Observed", "lp")
    l1.AddEntry(gexp , "Expected", "l")
    l1.AddEntry(gr_s1b , "Expected #pm 1 #sigma", "f")
    l1.AddEntry(gr_s2b , "Expected #pm 2 #sigma", "f")
    l1.AddEntry(g_xsec_c1n2 , "Theoretical #sigma_{NLO+NLL}","f")
    l1.Draw()
    '''
    LExp1 = ROOT.TGraphAsymmErrors(2)
    LExp1.SetFillColor(ROOT.kYellow)
    LExp1.SetPoint(0,250+100000,100000)
    LExp1.SetPointError(0,0.,0.,0.15,0.15)
    LExp1.SetPoint(1,100000, 100000)
    LExp1.SetPointError(1,0.,0.,0.15,0.15)
    LExp1.Draw("3")
    
    LExp2 = ROOT.TGraphAsymmErrors(2)
    LExp2.SetFillColor(ROOT.kGreen)
    LExp2.SetPoint(0,100000,100000)
    LExp2.SetPointError(0,0.,0.,0.08,0.08)
    LExp2.SetPoint(1,100000,100000)
    LExp2.SetPointError(1,0.,0.,0.08,0.08)
    LExp2.Draw("L3")
    
    LExp = ROOT.TGraph(2)
    LExp.SetLineColor(ROOT.kBlack)
    LExp.SetLineStyle(7)
    LExp.SetLineWidth(3)
    LExp.SetPoint(0,250+ 3.8*(1050-250)/100, 5-2.08*(5-0)/100*10)
    LExp.SetPoint(1,250+21.2*(1050-250)/100, 5-2.08*(5-0)/100*10)
    LExp.Draw("L")
    ''' 
   #masstex = ROOT.TLatex(0.70,0.79, "H_{T} > 300 GeV" )
    #masstex.SetNDC()
    #masstex.SetTextSize(0.036)
    #masstex.SetLineWidth(2)
    #masstex.SetTextFont(42)
    #masstex.Draw()
    c1.SaveAs("~/public_html/wz1dlimit_ichep2016_test_%s_%s.pdf" % (str(lumi).replace(".","p"),version))


#####################################################################################################
if __name__ == "__main__":
    main()
