import ROOT

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

#regions = 'strong'
regions = 'ewk'

f=ROOT.TFile.Open("mlfit_"+regions+".root")
covarMatrix = f.Get("shapes_prefit/overall_total_covar").Clone("covarMatrix")
covarMatrix.SetTitle("Full covariance matrix")
covarMatrix.GetXaxis().SetTitle("")
covarMatrix.GetYaxis().SetTitle("")
covarMatrix.GetZaxis().SetTitle("Covariance (#sigma_{xy})")

corrMatrix = covarMatrix.Clone("corrMatrix")
corrMatrix.SetTitle("Full correlation matrix")
corrMatrix.GetXaxis().SetTitle("")
corrMatrix.GetYaxis().SetTitle("")
corrMatrix.GetZaxis().SetTitle("Correlation (#rho_{xy})")

firstBin=0
for x in range(1, covarMatrix.GetXaxis().GetNbins()+1):
    if regions == 'strong':
        if "SRA_" in corrMatrix.GetXaxis().GetBinLabel(x) and firstBin==0:
            corrMatrix.GetXaxis().SetBinLabel(x, "SRA, b-veto")
            corrMatrix.GetYaxis().SetBinLabel(x, "SRA, b-veto")
            covarMatrix.GetXaxis().SetBinLabel(x, "SRA, b-veto")
            covarMatrix.GetYaxis().SetBinLabel(x, "SRA, b-veto")
            firstBin=1
        elif "SRAb_" in corrMatrix.GetXaxis().GetBinLabel(x) and firstBin==1:
            corrMatrix.GetXaxis().SetBinLabel(x, "SRA, b-tag")
            corrMatrix.GetYaxis().SetBinLabel(x, "SRA, b-tag")
            covarMatrix.GetXaxis().SetBinLabel(x, "SRA, b-tag")
            covarMatrix.GetYaxis().SetBinLabel(x, "SRA, b-tag")
            firstBin=2
        elif "SRB_" in corrMatrix.GetXaxis().GetBinLabel(x) and firstBin==2:
            corrMatrix.GetXaxis().SetBinLabel(x, "SRB, b-veto")
            corrMatrix.GetYaxis().SetBinLabel(x, "SRB, b-veto")
            covarMatrix.GetXaxis().SetBinLabel(x, "SRB, b-veto")
            covarMatrix.GetYaxis().SetBinLabel(x, "SRB, b-veto")
            firstBin=3
        elif "SRBb_" in corrMatrix.GetXaxis().GetBinLabel(x) and firstBin==3:
            corrMatrix.GetXaxis().SetBinLabel(x, "SRB, b-tag")
            corrMatrix.GetYaxis().SetBinLabel(x, "SRB, b-tag")
            covarMatrix.GetXaxis().SetBinLabel(x, "SRB, b-tag")
            covarMatrix.GetYaxis().SetBinLabel(x, "SRB, b-tag")
            firstBin=4
        elif "SRC_" in corrMatrix.GetXaxis().GetBinLabel(x) and firstBin==4:
            corrMatrix.GetXaxis().SetBinLabel(x, "SRC, b-veto")
            corrMatrix.GetYaxis().SetBinLabel(x, "SRC, b-veto")
            covarMatrix.GetXaxis().SetBinLabel(x, "SRC, b-veto")
            covarMatrix.GetYaxis().SetBinLabel(x, "SRC, b-veto")
            firstBin=5
        elif "SRCb_" in corrMatrix.GetXaxis().GetBinLabel(x) and firstBin==5:
            corrMatrix.GetXaxis().SetBinLabel(x, "SRC, b-tag")
            corrMatrix.GetYaxis().SetBinLabel(x, "SRC, b-tag")
            covarMatrix.GetXaxis().SetBinLabel(x, "SRC, b-tag")
            covarMatrix.GetYaxis().SetBinLabel(x, "SRC, b-tag")
            firstBin=6
        else:
            corrMatrix.GetXaxis().SetBinLabel(x, "")
            corrMatrix.GetYaxis().SetBinLabel(x, "")
            covarMatrix.GetXaxis().SetBinLabel(x, "")
            covarMatrix.GetYaxis().SetBinLabel(x, "")

    elif regions == 'ewk':
        if "TChiWZ_" in corrMatrix.GetXaxis().GetBinLabel(x) and firstBin==0:
            corrMatrix.GetXaxis().SetBinLabel(x, "Ewk WZ/ZZ")
            corrMatrix.GetYaxis().SetBinLabel(x, "Ewk WZ/ZZ")
            covarMatrix.GetXaxis().SetBinLabel(x, "Ewk WZ/ZZ")
            covarMatrix.GetYaxis().SetBinLabel(x, "Ewk WZ/ZZ")
            firstBin=1
        elif "TChiHZ_" in corrMatrix.GetXaxis().GetBinLabel(x) and firstBin==1:
            corrMatrix.GetXaxis().SetBinLabel(x, "Ewk HZ")
            corrMatrix.GetYaxis().SetBinLabel(x, "Ewk HZ")
            covarMatrix.GetXaxis().SetBinLabel(x, "Ewk HZ")
            covarMatrix.GetYaxis().SetBinLabel(x, "Ewk HZ")
            firstBin=2
        else:
            corrMatrix.GetXaxis().SetBinLabel(x, "")
            corrMatrix.GetYaxis().SetBinLabel(x, "")
            covarMatrix.GetXaxis().SetBinLabel(x, "")
            covarMatrix.GetYaxis().SetBinLabel(x, "")
            
    for y in range(1, covarMatrix.GetYaxis().GetNbins()+1):
        # force slightly negative bins to be positive for display purposes..
        bin_value = covarMatrix.GetBinContent(x,y)
        if (bin_value < 0. and bin_value > -0.1): bin_value = 0.01
        corrMatrix.SetBinContent(x,y, (bin_value)/((ROOT.TMath.Sqrt(covarMatrix.GetBinContent(x,x)))*(ROOT.TMath.Sqrt(covarMatrix.GetBinContent(y,y)))))

canvas=ROOT.TCanvas("canvas", "", 900, 900)
canvas.cd()

corrMatrix.SetTitle("")
#corrMatrix.GetXaxis().SetLabelSize(0.02)
corrMatrix.GetYaxis().SetLabelSize(0.02)
corrMatrix.GetZaxis().SetLabelSize(0.02)
corrMatrix.GetZaxis().SetRangeUser(0,1)
corrMatrix.Draw("colz")

ROOT.gPad.Update()
palette = corrMatrix.FindObject("palette");
palette.SetX2NDC(0.925);


label_top = ROOT.TPaveText(0.8,0.91,0.9,0.94, "brNDC");
label_top.SetBorderSize(0);
label_top.SetFillColor(0);
label_top.SetTextSize(0.038);
label_top.SetTextAlign(31); # align right
label_top.SetTextFont(62);
label_top.AddText("35.9 fb^{-1} (13 TeV)");

label_cms = ROOT.TPaveText(0.1,0.91,0.4,0.94, "brNDC");
label_cms.SetBorderSize(0);
label_cms.SetFillColor(0);
label_cms.SetTextSize(0.038);
label_cms.SetTextAlign(11); # align right
label_cms.SetTextFont(62);
label_cms.AddText("CMS Preliminary");

label_top.Draw("same")
label_cms.Draw("same")

ROOT.gPad.RedrawAxis()

canvas.SaveAs("~/public_html/fullCorrelationMatrix_"+regions+"_Moriond2017.pdf")


canvasCovar=ROOT.TCanvas("canvasCovar", "", 900, 900)
canvasCovar.cd()
ROOT.gPad.SetLogz()

covarMatrix.SetTitle("")
#covarMatrix.GetXaxis().SetLabelSize(0.02)
covarMatrix.GetYaxis().SetLabelSize(0.02)
covarMatrix.GetZaxis().SetLabelSize(0.02)
covarMatrix.GetZaxis().SetRangeUser(5e-3,6e1)
covarMatrix.Draw("colz")

ROOT.gPad.Update()
paletteCov = covarMatrix.FindObject("palette");
paletteCov.SetX2NDC(0.925);

label_top.Draw("same")
label_cms.Draw("same")

ROOT.gPad.RedrawAxis()

canvasCovar.SaveAs("~/public_html/fullCovarianceMatrix_"+regions+"_Moriond2017.pdf")


fout=ROOT.TFile.Open("covarMatrix_35p9ifb_"+regions+"_Moriond2017.root", "RECREATE")
fout.cd()
covarMatrix.Write()
corrMatrix.Write()
fout.Close()

