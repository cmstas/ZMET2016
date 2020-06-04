import ROOT, array
import sys, glob, math
ROOT.gROOT.SetBatch(True)
lumi = 35.9
#lumi = 72

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
        hxsec = fxsec.Get("h_xsec_higgsino")
    sigma = hxsec.GetBinContent(hxsec.FindBin(charginomass))
    return sigma

def main():
    version = "limits_TChiZZ_230317"
    dir="./"+version+"/"
#    chargino_masses =[100,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750]
#    chargino_masses =[100,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700]
#    chargino_masses =[100,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950]
    chargino_masses =[125,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950]
    f_xsecgraph = ROOT.TFile.Open("../../dilepbabymaker/xsec_susy_13tev_graphs.root")
    g_xsec_c1n2 = f_xsecgraph.Get("g_xsec_higgsino")

    obs=[]
    exp=[]
    exp2x=[]
    exp3x=[]
    m2s=[]
    m1s=[]
    p1s=[]
    p2s=[]
    x0e=[]
    sigmas = []

    h_obs = ROOT.TH1F("hObs","",37, 87.5, 1012.5)
    h_obs.GetXaxis().SetTitle("m_{#tilde{#chi}^{0}_{1}} [GeV]")
    h_obs.GetYaxis().SetTitle("#sigma limit at 95% CL [pb]")
    h_exp = h_obs.Clone("hExp")
    h_exp1m = h_obs.Clone("hExp1m")
    h_exp2m = h_obs.Clone("hExp2m")
    h_exp1p = h_obs.Clone("hExp1p")
    h_exp2p = h_obs.Clone("hExp2p")

    for i,chargino in enumerate(chargino_masses):
        fn = dir+'limit_TChiZZ_'+str(chargino)+'.root'
        limitsdic = get1Dlimit(fn)
        xsec = get1Dxsec(chargino)
        obs.append(limitsdic['obs']*xsec)
        exp.append(limitsdic['exp']*xsec)
        exp2x.append(limitsdic['exp']*xsec/math.sqrt(2))
        exp3x.append(limitsdic['exp']*xsec/math.sqrt(3))
        m2s.append(limitsdic['m2s']*xsec)
        m1s.append(limitsdic['m1s']*xsec)
        p1s.append(limitsdic['p1s']*xsec)
        p2s.append(limitsdic['p2s']*xsec)
        x0e.append(0.)
        sigmas.append(xsec)
        h_obs.SetBinContent(i+1,obs[i])
        h_exp.SetBinContent(i+1,exp[i])
        h_exp1m.SetBinContent(i+1,m1s[i])
        h_exp1p.SetBinContent(i+1,p1s[i])
        h_exp2m.SetBinContent(i+1,m2s[i])
        h_exp2p.SetBinContent(i+1,p2s[i])
    #TGraphAsymmErrors needs the delta
    for i in range(0,len(exp)):
        m2s[i]=exp[i]-m2s[i]
        m1s[i]=exp[i]-m1s[i]
        p1s[i]=p1s[i]-exp[i]
        p2s[i]=p2s[i]-exp[i]

    chi1n = "#lower[-0.12]{#tilde{#chi}}#lower[0.2]{#scale[0.85]{^{0}}}#kern[-1.3]{#scale[0.85]{_{1}}}"
    chi2n = "#lower[-0.12]{#tilde{#chi}}#lower[0.2]{#scale[0.85]{^{0}}}#kern[-1.]{#scale[0.85]{_{2}}}"
    chi1pm= "#lower[-0.12]{#tilde{#chi}}#lower[0.2]{#scale[0.85]{^{#pm}}}#kern[-1.3]{#scale[0.85]{_{1}}}"
    chii= "#lower[-0.12]{#tilde{#chi}}#lower[0.2]{#scale[0.85]{^{0,#pm}}}#kern[-3.]{#scale[0.85]{_{i}}}"
    chij= "#lower[-0.12]{#tilde{#chi}}#lower[0.2]{#scale[0.85]{^{0,#mp}}}#kern[-3.]{#scale[0.85]{_{j}}}"
    chi10= "#lower[-0.12]{#tilde{#chi}}#lower[0.2]{#scale[0.85]{^{0}}}#kern[-1.3]{#scale[0.85]{_{1}}}"
    xsoft= "X#scale[0.85]{_{soft}}"
    mass_ = "m#kern[0.1]{#lower[-0.12]{_{"
    ppChiChi = "pp #rightarrow "+chii+"#kern[0.6]{"+chij+"}  #rightarrow "+chi10+"#kern[0.3]{"+chi10+"} + "+xsoft+"#rightarrow ZZ#tilde{G}#tilde{G} + "+xsoft
    branching = "BR("+chi10+"#rightarrow Z#tilde{G}) = 100%"
    mChis = mass_+chi2n+"}}} #approx "+mass_+chi1pm+"}}} #approx "+mass_+chi1n+"}}}, "+mass_+"#tilde{G}}}} = 1 GeV"

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
    h = ROOT.TH2F("h","h",68,100,950,1000,0.001,1000)
    h.SetTitle("")
    h.GetXaxis().SetTitle("m_{#tilde{#chi}^{0}_{1}} [GeV]")
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

    # gexp2x = ROOT.TGraph(len(chargino_masses), array.array('d', chargino_masses), array.array('d', exp2x))
    # gexp2x.SetLineStyle(7)
    # gexp2x.SetLineWidth(3)
    # gexp2x.SetLineColor(ROOT.kRed)
    # gexp2x.Draw("L")

    # gexp3x = ROOT.TGraph(len(chargino_masses), array.array('d', chargino_masses), array.array('d', exp3x))
    # gexp3x.SetLineStyle(7)
    # gexp3x.SetLineWidth(3)
    # gexp3x.SetLineColor(ROOT.kOrange+2)
    # gexp3x.Draw("L")

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

    prctex = ROOT.TLatex(0.25,0.83, ppChiChi );
    prctex.SetNDC()
    prctex.SetTextSize(0.032)
    prctex.SetLineWidth(2)
    prctex.SetTextFont(42)
    prctex.Draw()

    prctex2 = ROOT.TLatex(0.25,0.78, branching );
    prctex2.SetNDC()
    prctex2.SetTextSize(0.032)
    prctex2.SetLineWidth(2)
    prctex2.SetTextFont(42)
    prctex2.Draw()

    prctex3 = ROOT.TLatex(0.25,0.73, mChis );
    prctex3.SetNDC()
    prctex3.SetTextSize(0.032)
    prctex3.SetLineWidth(2)
    prctex3.SetTextFont(42)
    prctex3.Draw()

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

    l1 = ROOT.TLegend(0.45, 0.52, 0.9, 0.71)
    l1.SetTextFont(42)
    l1.SetTextSize(0.036)
    l1.SetLineColor(ROOT.kWhite)
    l1.SetShadowColor(ROOT.kWhite)
    l1.SetFillColor(ROOT.kWhite)
#    l1.SetHeader("#sigma exclusion limit, M_{#tilde{#chi}^{0}_{1}} = 1 GeV")
    # l1.AddEntry(gobs , "Observed 2016", "lp")
    # l1.AddEntry(gexp , "Expected 2016", "l")
    # l1.AddEntry(gexp2x , "Expected 2x lumi", "l")
    # l1.AddEntry(gexp3x , "Expected 3x lumi", "l")
    l1.AddEntry(gobs , "Observed", "l")
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
    c1.SaveAs("~/public_html/TChiZZ_Exclusion_13TeV.pdf")

    ### store histogram versions of limits
    f_out = ROOT.TFile("limits_TChiZZ.root","RECREATE")
    f_out.cd()
    #h_obs.Write()
    #h_exp.Write()
    #h_exp1m.Write()
    #h_exp1p.Write()
    #h_exp2m.Write()
    #h_exp2p.Write()
    g_xsec_c1n2.Write()

    # graphs - need to set titles first
    gexp.SetName("gExp")
    gexp.Write()
    gobs.SetName("gObs")
    gobs.Write()
    gr_s1b.SetName("gExp1pm")
    gr_s1b.Write()
    gr_s2b.SetName("gExp2pm")
    gr_s2b.Write()

    f_out.Close()


#####################################################################################################
if __name__ == "__main__":
    main()
