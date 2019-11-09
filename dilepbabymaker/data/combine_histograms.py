import ROOT as r

f_old = r.TFile("xsec_susy_13tev.root","READ")
f_new = r.TFile("xsec_susy_13tev_run2.root","READ")

f_net = r.TFile("xsec_susy_13tev_final.root","RECREATE")

h_c1n2 = f_old.Get("h_xsec_c1n2").Clone("h_xsec_c1n2")
h_c1n2.SetDirectory(f_net)
h_c1c1 = f_old.Get("h_xsec_c1c1").Clone("h_xsec_c1c1")
h_c1c1.SetDirectory(f_net)
h_higgsino = f_old.Get("h_xsec_higgsino").Clone("h_xsec_higgsino")
h_higgsino.SetDirectory(f_net)
h_gluino = f_new.Get("h_xsec_gluino").Clone("h_xsec_gluino")
h_gluino.SetDirectory(f_net)
h_stop = f_new.Get("h_xsec_stop").Clone("h_xsec_stop")
h_stop.SetDirectory(f_net)
h_squark = f_new.Get("h_xsec_squark").Clone("h_xsec_squark")
h_squark.SetDirectory(f_net)

f_net.Write()
f_old.Close()
f_new.Close()
f_net.Close()
