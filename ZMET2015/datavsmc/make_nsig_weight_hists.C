#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"

void make_nsig_weight_hists(TString dir, TString sample) {

  bool dobtagsfs = true;
  
  TChain* t = new TChain("t");
  if( sample == "fullscan" ){
	t->Add(Form("%s/t5zz*.root",dir.Data()));
  }else if( sample == "fullscan_tchiwz" ){
	t->Add(Form("%s/tchiwz*.root",dir.Data()));
  }else if( sample == "vvv" ){
	t->Add(Form("%s/zzz*.root",dir.Data()));
	t->Add(Form("%s/wzz*.root",dir.Data()));
	t->Add(Form("%s/wwz*.root",dir.Data()));

  }else if( sample == "zz" ){
	t->Add(Form("%s/zz2l2nu*.root",dir.Data()));

  }else if( sample == "wz" ){
	t->Add(Form("%s/wz3lnu*.root",dir.Data()));
	
  }else if( sample == "ttv" ){
	t->Add(Form("%s/ttzllnunu*.root",dir.Data()));
	
  }else if( sample == "zjets" ){
	t->Add(Form("%s/dyjets*.root",dir.Data()));
	dobtagsfs = false;
 
  }else if( sample == "zjetsmlm" ){
	t->Add(Form("%s/zjets*.root",dir.Data()));
	dobtagsfs = false;
	
  }else if( sample == "ttbar" ){
	t->Add(Form("%s/tt2lnu*.root",dir.Data()));
	dobtagsfs = false;
	
  }else if( sample == "wz_inc" ){
	t->Add(Form("%s/wz2l2q*.root",dir.Data()));
	t->Add(Form("%s/wz3lnu*.root",dir.Data()));
	dobtagsfs = false;
	
  }else if( sample == "zz_inc" ){
	t->Add(Form("%s/zz2l2nu*.root",dir.Data()));
	t->Add(Form("%s/zz2l2q*.root",dir.Data()));
 	t->Add(Form("%s/zz4l*.root",dir.Data()));
	dobtagsfs = false;

  }else{
  t->Add(Form("%s/%s*.root",dir.Data(),sample.Data()));
  }
  
  TFile* fout = new TFile(Form("nsig_weights_%s.root", sample.Data()),"RECREATE");
  
  // assuming here: 50 GeV binning, m1 from 600-1650, m2 from 100-1550
  TH2D* h_nsig = new TH2D("h_nsig",";mass1 [GeV];mass2 [GeV]",(1600-550)/50,575,1625,(1500-50)/50,75,1525);
  TH2D* h_avg_weight_btagsf = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf");
  TH2D* h_avg_weight_btagsf_heavy_UP = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf_heavy_UP");
  TH2D* h_avg_weight_btagsf_light_UP = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf_light_UP");
  TH2D* h_avg_weight_btagsf_heavy_DN = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf_heavy_DN");
  TH2D* h_avg_weight_btagsf_light_DN = (TH2D*) h_nsig->Clone("h_avg_weight_btagsf_light_DN");

  TH2D* h_avg_weight_isr    = (TH2D*) h_nsig->Clone("h_avg_weight_isr");
  TH2D* h_avg_weight_isr_lo = (TH2D*) h_nsig->Clone("h_avg_weight_isr_lo");
  TH2D* h_avg_weight_isr_hi = (TH2D*) h_nsig->Clone("h_avg_weight_isr_hi");

  if( 	dobtagsfs ){
	t->Draw("mass_LSP:mass_gluino>>h_nsig");
	t->Draw("mass_LSP:mass_gluino>>h_avg_weight_btagsf","(met_pt > -1.)*weight_btagsf" );
	t->Draw("mass_LSP:mass_gluino>>h_avg_weight_btagsf_heavy_UP","(met_pt > -1.)*weight_btagsf_heavy_UP" );
	t->Draw("mass_LSP:mass_gluino>>h_avg_weight_btagsf_light_UP","(met_pt > -1.)*weight_btagsf_light_UP" );
	t->Draw("mass_LSP:mass_gluino>>h_avg_weight_btagsf_heavy_DN","(met_pt > -1.)*weight_btagsf_heavy_DN" );
	t->Draw("mass_LSP:mass_gluino>>h_avg_weight_btagsf_light_DN","(met_pt > -1.)*weight_btagsf_light_DN" );
    
	t->Draw("mass_LSP:mass_gluino>>h_avg_weight_isr"   ,"(met_pt > -1.)*isr_weight" );
	t->Draw("mass_LSP:mass_gluino>>h_avg_weight_isr_lo","(met_pt > -1.)*(isr_weight-isr_unc)" );
	t->Draw("mass_LSP:mass_gluino>>h_avg_weight_isr_hi","(met_pt > -1.)*(isr_weight+isr_unc)" );
  }

  // h_avg_weight_isr->Add(h_avg_weight_isr_lo);
  // h_avg_weight_isr->Add(h_avg_weight_isr_hi);
  
  h_avg_weight_btagsf->Divide(h_nsig);
  h_avg_weight_btagsf_heavy_UP->Divide(h_nsig);
  h_avg_weight_btagsf_light_UP->Divide(h_nsig);
  h_avg_weight_btagsf_heavy_DN->Divide(h_nsig);
  h_avg_weight_btagsf_light_DN->Divide(h_nsig);
  h_avg_weight_isr->Divide(h_nsig);
  
  fout->Write();
  fout->Close();

}
