#include <iostream>
#include <stdexcept>

#include <TFile.h>
#include <TH1F.h>

using namespace std;

void getReweightScheme(vector <double> &binning, string selection );

void renormhists( TH1F * &h_data, TH1F * &h_rescaleme )
{
  TH1F * h_temp = (TH1F*) h_data->Clone("h_temp");
  
  for( int binind = 0; binind < h_data -> GetNbinsX(); binind++ ){
	if( h_rescaleme -> GetBinContent(binind+1) == 0 ) h_temp -> SetBinContent( binind+1, 0 );
  }

  h_data -> Scale( 1. / h_temp -> GetSumOfWeights() );
  return;
}

void getReweightHTHist_MC( string signalregion )
{

  // TFile * f_data = TFile::Open(Form("../output/V07-04-10/zjetsmlm_%s_novtxweight_hists.root", signalregion.c_str() )   , "READ");
  // TFile * f_phot = TFile::Open(Form("../output/V07-04-10/All_MC_%s_novtxweight_nohtweight_templates.root", signalregion.c_str() ) , "READ");

  // TFile * f_data = TFile::Open(Form("../output/V07-04-13/zjetsmlm_%s_novtxweight_hists.root", signalregion.c_str() )   , "READ");
  // TFile * f_phot = TFile::Open(Form("../output/V07-04-13/All_MC_%s_novtxweight_nohtweight_templates.root", signalregion.c_str() ) , "READ");  

  TFile * f_data = TFile::Open(Form("../output/V08-07-00/zjetsmlm_%s_novtxweight_hists.root", signalregion.c_str() )   , "READ");
  TFile * f_phot = TFile::Open(Form("../output/V08-07-00/All_MC_%s_novtxweight_nohtweight_templates.root", signalregion.c_str() ) , "READ");  

  TH1F * h_data = NULL;
  TH1F * h_data_em = NULL;
  TH1F * h_phot = NULL;

  if( TString(signalregion).Contains("SR_ATLAS") ){
	h_data    = (TH1F*)f_data->Get("h_ll_event_atlas_ht_gt1j_passtrig")->Clone("h_data");  
	h_data_em = (TH1F*)f_data->Get("h_em_event_atlas_ht_gt1j_passtrig")->Clone("h_data_em");  
	h_phot    = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig")->Clone("h_phot");  
  }
  else{
	h_data    = (TH1F*)f_data->Get("h_ll_event_ht_gt1j_passtrig")->Clone("h_data");  
	h_data_em = (TH1F*)f_data->Get("h_em_event_ht_gt1j_passtrig")->Clone("h_data_em");  
	h_phot    = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig")->Clone("h_phot");  
  }

  TH1F * h_phot_22  = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig22" )->Clone("h_phot_22");
  TH1F * h_phot_30  = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig30" )->Clone("h_phot_30");
  TH1F * h_phot_36  = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig36" )->Clone("h_phot_36");
  TH1F * h_phot_50  = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig50" )->Clone("h_phot_50");
  TH1F * h_phot_75  = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig75" )->Clone("h_phot_75");
  TH1F * h_phot_90  = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig90" )->Clone("h_phot_90");
  TH1F * h_phot_120 = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig120")->Clone("h_phot_120");
  TH1F * h_phot_165 = (TH1F*)f_phot->Get("h_ph_event_htgt1jets_passtrig165")->Clone("h_phot_165");

  h_data->Add(h_data_em,-1.);
  
  vector <double> v_bin;
  getReweightScheme( v_bin, signalregion );

  int nbins = v_bin.size()-1;
  
  double bins[nbins+1];

  for( size_t bini = 0; bini < v_bin.size(); bini++ ){
	bins[bini] = v_bin.at(bini);
  }
  
  h_data     = (TH1F*) h_data    ->Rebin(nbins, "h_data_rebinned", bins);
  h_phot     = (TH1F*) h_phot    ->Rebin(nbins, "h_phot_rebinned", bins);
  h_phot_22  = (TH1F*) h_phot_22 ->Rebin(nbins, "h_phot_22_rebinned", bins);
  h_phot_30  = (TH1F*) h_phot_30 ->Rebin(nbins, "h_phot_30_rebinned", bins);
  h_phot_36  = (TH1F*) h_phot_36 ->Rebin(nbins, "h_phot_36_rebinned", bins);
  h_phot_50  = (TH1F*) h_phot_50 ->Rebin(nbins, "h_phot_50_rebinned", bins);
  h_phot_75  = (TH1F*) h_phot_75 ->Rebin(nbins, "h_phot_75_rebinned", bins);
  h_phot_90  = (TH1F*) h_phot_90 ->Rebin(nbins, "h_phot_90_rebinned", bins);
  h_phot_120 = (TH1F*) h_phot_120->Rebin(nbins, "h_phot_120_rebinned", bins);
  h_phot_165 = (TH1F*) h_phot_165->Rebin(nbins, "h_phot_165_rebinned", bins);

  // h_data    ->Rebin(20);
  // h_phot    ->Rebin(20);
  // h_phot_22 ->Rebin(20);
  // h_phot_30 ->Rebin(20);
  // h_phot_36 ->Rebin(20);
  // h_phot_50 ->Rebin(20);
  // h_phot_75 ->Rebin(20);
  // h_phot_90 ->Rebin(20);
  // h_phot_120->Rebin(20);
  // h_phot_165->Rebin(20);

  h_phot->Scale(1./h_phot->GetSumOfWeights());
  h_data->Scale(1./h_data->GetSumOfWeights());

  h_phot_22  -> Scale( 1./ h_phot_22  -> GetSumOfWeights() );
  h_phot_30  -> Scale( 1./ h_phot_30  -> GetSumOfWeights() );
  h_phot_36  -> Scale( 1./ h_phot_36  -> GetSumOfWeights() );
  h_phot_50  -> Scale( 1./ h_phot_50  -> GetSumOfWeights() );
  h_phot_75  -> Scale( 1./ h_phot_75  -> GetSumOfWeights() );
  h_phot_90  -> Scale( 1./ h_phot_90  -> GetSumOfWeights() );
  h_phot_120 -> Scale( 1./ h_phot_120 -> GetSumOfWeights() );
  h_phot_165 -> Scale( 1./ h_phot_165 -> GetSumOfWeights() );
  
  TH1F * h_ht_ratio = (TH1F*) h_data->Clone("h_ht_ratio");
  TH1F * h_ht_ratio_22  = (TH1F*) h_data->Clone("h_ht_ratio_22");
  TH1F * h_ht_ratio_30  = (TH1F*) h_data->Clone("h_ht_ratio_30");
  TH1F * h_ht_ratio_36  = (TH1F*) h_data->Clone("h_ht_ratio_36");
  TH1F * h_ht_ratio_50  = (TH1F*) h_data->Clone("h_ht_ratio_50");
  TH1F * h_ht_ratio_75  = (TH1F*) h_data->Clone("h_ht_ratio_75");
  TH1F * h_ht_ratio_90  = (TH1F*) h_data->Clone("h_ht_ratio_90");
  TH1F * h_ht_ratio_120 = (TH1F*) h_data->Clone("h_ht_ratio_120");
  TH1F * h_ht_ratio_165 = (TH1F*) h_data->Clone("h_ht_ratio_165");

  // renormhists( h_ht_ratio    , h_phot     );
  // renormhists( h_ht_ratio_22 , h_phot_22  );
  // renormhists( h_ht_ratio_30 , h_phot_30  );
  // renormhists( h_ht_ratio_36 , h_phot_36  );
  // renormhists( h_ht_ratio_50 , h_phot_50  );
  // renormhists( h_ht_ratio_75 , h_phot_75  );
  // renormhists( h_ht_ratio_90 , h_phot_90  );
  // renormhists( h_ht_ratio_120, h_phot_120 );
  // renormhists( h_ht_ratio_165, h_phot_165 );

  h_ht_ratio->Divide(h_phot);
  h_ht_ratio_22 -> Divide(h_phot_22 );
  h_ht_ratio_30 -> Divide(h_phot_30 );
  h_ht_ratio_36 -> Divide(h_phot_36 );
  h_ht_ratio_50 -> Divide(h_phot_50 );
  h_ht_ratio_75 -> Divide(h_phot_75 );
  h_ht_ratio_90 -> Divide(h_phot_90 );
  h_ht_ratio_120-> Divide(h_phot_120);
  h_ht_ratio_165-> Divide(h_phot_165);
	   
  string filename = Form("ht_ratio_data_novtx_nohtweight_%s.root", signalregion.c_str() );
  
  TFile * file = TFile::Open( filename.c_str() ,"RECREATE");
  file->cd();
  h_data->Write();
  h_phot->Write();
  h_phot_22 ->Write();
  h_phot_30 ->Write();
  h_phot_36 ->Write();
  h_phot_50 ->Write();
  h_phot_75 ->Write();
  h_phot_90 ->Write();
  h_phot_120->Write();
  h_phot_165->Write();
  h_ht_ratio->Write();
  h_ht_ratio_22 ->Write();
  h_ht_ratio_30 ->Write();
  h_ht_ratio_36 ->Write();
  h_ht_ratio_50 ->Write();
  h_ht_ratio_75 ->Write();
  h_ht_ratio_90 ->Write();
  h_ht_ratio_120->Write();
  h_ht_ratio_165->Write();
  file->Close();

  cout<<"Writing reweighting hists to file: "<<filename.c_str() <<endl;
  return;
}



void getReweightScheme(vector <double> &binning, string selection )
{

  binning.clear();

  if( TString(selection).Contains("SRA") ){
	binning.push_back(0);
	// binning.push_back(22);
	binning.push_back(33);
	binning.push_back(50);
	binning.push_back(75);
	binning.push_back(90);
	binning.push_back(120);
	binning.push_back(165);
	binning.push_back(200);
	// binning.push_back(450);
	// binning.push_back(500);
	// binning.push_back(600);
	// binning.push_back(700);
	// binning.push_back(800);
	// binning.push_back(900);
	// binning.push_back(1000);
	// binning.push_back(1100);
	// binning.push_back(1200);
	// binning.push_back(1300);
	// binning.push_back(1400);
	// binning.push_back(1500);
	binning.push_back(3000);
  }

  else if( TString(selection).Contains("SRB") ){
	binning.push_back(0);
	// binning.push_back(22);
	binning.push_back(33);
	binning.push_back(50);
	binning.push_back(75);
	binning.push_back(90);
	binning.push_back(120);
	binning.push_back(165);
	binning.push_back(200);
	binning.push_back(300);
	// binning.push_back(450);
	// binning.push_back(500);
	// binning.push_back(600);
	// binning.push_back(700);
	// binning.push_back(800);
	// binning.push_back(900);
	// binning.push_back(1000);
	// binning.push_back(1100);
	// binning.push_back(1200);
	// binning.push_back(1300);
	// binning.push_back(1400);
	// binning.push_back(1500);
	binning.push_back(3000);
  }

  else if( TString(selection).Contains("SR_ATLAS") ){
	binning.push_back(0);
	binning.push_back(33);
	// binning.push_back(36);
	binning.push_back(50);
	binning.push_back(75);
	binning.push_back(90);
	binning.push_back(120);
	binning.push_back(165);
	binning.push_back(200);
	// binning.push_back(300);
	// binning.push_back(400);
	// binning.push_back(500);
  	// binning.push_back(600);
  	// binning.push_back(700);
  	// binning.push_back(800);
  	// binning.push_back(900);
  	// binning.push_back(1000);
  	binning.push_back(3000);
  }


  
  else if( TString(selection).Contains("forward") && TString(selection).Contains("twojets") && !TString(selection).Contains("with2_twojets") ){
	binning.push_back(0);
	// binning.push_back(22);
	binning.push_back(33);
	binning.push_back(36);
	binning.push_back(50);
	binning.push_back(75);
	binning.push_back(90);
	binning.push_back(120);
	binning.push_back(165);
	binning.push_back(300);
	binning.push_back(3000);
  }
  
  else if( TString(selection).Contains("inclusive") && !TString(selection).Contains("3jets_inclusive") ){
	binning.push_back(0);
	// binning.push_back(22);
	binning.push_back(33);
	binning.push_back(36);
	binning.push_back(50);
	binning.push_back(75);
	binning.push_back(90);
	binning.push_back(120);
	binning.push_back(165);
	binning.push_back(300);
	binning.push_back(3000);
  }

  
  else if( TString(selection).Contains("twojets") && !TString(selection).Contains("with2_twojets") ){
	binning.push_back(0);
	// binning.push_back(22);
	binning.push_back(33);
	// binning.push_back(36);
	binning.push_back(50);
	binning.push_back(75);
	binning.push_back(90);
	binning.push_back(120);
	// binning.push_back(165);
	// binning.push_back(250);
	// binning.push_back(300);
	// binning.push_back(350);
	// binning.push_back(400);
	// binning.push_back(450);
	// binning.push_back(500);
	// binning.push_back(600);
	// binning.push_back(700);
	// binning.push_back(800);
	// binning.push_back(900);
	// binning.push_back(1000);
	// binning.push_back(1100);
	// binning.push_back(1200);
	// binning.push_back(1300);
	// binning.push_back(1400);
	// binning.push_back(1500);
	binning.push_back(3000);
  }

  else if( TString(selection).Contains("with2_twojets") ){
	binning.push_back(0);
	// binning.push_back(22);
	// binning.push_back(33);
	// binning.push_back(36);
	binning.push_back(60);
	binning.push_back(120);
	// binning.push_back(165);
	// binning.push_back(250);
	// binning.push_back(300);
	// binning.push_back(350);
	// binning.push_back(400);
	// binning.push_back(450);
	// binning.push_back(500);
	// binning.push_back(600);
	// binning.push_back(700);
	// binning.push_back(800);
	// binning.push_back(900);
	// binning.push_back(1000);
	// binning.push_back(1100);
	// binning.push_back(1200);
	// binning.push_back(1300);
	// binning.push_back(1400);
	// binning.push_back(1500);
	binning.push_back(3000);
  }

  else if( TString(selection).Contains("SR_EWK") ){
	binning.push_back(0);
	binning.push_back(75);
	binning.push_back(100);
	binning.push_back(125);
	binning.push_back(150);
	binning.push_back(200);
	binning.push_back(3000);
  }
  
  else{

  	binning.push_back(0);
	// binning.push_back(22);
	binning.push_back(33);
	// binning.push_back(36);
	binning.push_back(50);
	binning.push_back(75);
	binning.push_back(90);
	binning.push_back(120);
	binning.push_back(165);
	binning.push_back(200);
	binning.push_back(300);
	// binning.push_back(350);
	// binning.push_back(400);
	// binning.push_back(450);
	// binning.push_back(500);
	// binning.push_back(600);
	// binning.push_back(700);
	// binning.push_back(800);
	// binning.push_back(900);
	// binning.push_back(1000);
	// binning.push_back(1100);
	// binning.push_back(1200);
	// binning.push_back(1300);
	// binning.push_back(1400);
	// binning.push_back(1500);
	binning.push_back(3000);
}

  return;
}
