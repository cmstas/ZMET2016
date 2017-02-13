#include <iostream>

#include "TH2F.h"
#include "TChain.h"
#include "TFile.h"

using namespace std;

void getTotalEventsSUSY_mt2way()
{

  TChain * ch = new TChain("Events");

  // ch->Add("/hadoop/cms/store/group/snt/run2_25ns/SMS-T5ZZ_mGluino-600To700_mLSP-100To500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15FSPremix-MCRUN2_74_V9-v2/V07-04-11_FS/merged*.root");
  // ch->Add("/hadoop/cms/store/group/snt/run2_25ns/SMS-T5ZZ_mGluino-1000To1250_mLSP-100To1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15FSPremix-MCRUN2_74_V9-v2/V07-04-12_FS/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/run2_25ns/SMS-T5ZZ_mGluino-1200To1350_mLSP-100To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15FSPremix-MCRUN2_74_V9-v2/V07-04-12_FS/merged_ntuple_*.root");
  // ch->Add("/hadoop/cms/store/group/snt/run2_25ns/SMS-T5ZZ_mGluino-1400To1550_mLSP-100To1400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15FSPremix-MCRUN2_74_V9-v2/V07-04-12_FS/merged_ntuple_*.root");

  ch->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-T5ZZ_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/merged_ntuple_*.root");
  ch->Add("/hadoop/cms/store/group/snt/run2_moriond17_fastsim/SMS-T5ZZ_mGluino-1850to2100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/merged_ntuple_*.root");

  //  ch->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-TChiWZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v2/V08-00-09/merged_ntuple_*.root"); 

  // ch->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-T5qqqqVV_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/merged_ntuple_*.root"); 

  // //2016 ZH
  // ch->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-TChiHZ_HToBB_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/merged_ntuple_*.root");

  // //2016 ZZ
  // ch->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2_fastsim/SMS-TChiZZ_ZToLL_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-09/merged_ntuple_*.root");


  cout<<"Creating hist"<<endl;
  
  //=================
  // 2 Sparm Params
  //=================
  TH2F * h_entries = new TH2F("h_entries","h_entries",27,775,2125,39,75,2025);	// binning for T5ZZ
  //TH2F * h_entries = new TH2F("h_entries","h_entries",25,87.5,712.5,31,-5,305);	// binning for TChiWZ
  // TH2F * h_entries = new TH2F("h_entries","h_entries",460,0,2300,460,0,2300); // binning for T5qqqqVV
  // TH2D* h_nsig = new TH2D("h_nsig",";mass1 [GeV];mass2 [GeV]", 65, 387.5, 2012.5, 65, -12.5, 1612.5);
  ch->Draw("sparm_values[1]:sparm_values[0]>>h_entries");
  
  //=================
  // 1 Sparm Param
  //=================
  //TH1D * h_entries = new TH1D("h_entries", "h_entries", 37, 87.5, 1012.5); //binning for TChiZZ  
  //TH1D * h_entries = new TH1D("h_entries", "h_entries", 36, 112.5, 1012.5); //binning for TChiHZ  
  //ch->Draw("sparm_values[0]>>h_entries");


  // int totalentries = 0;
  // int nbins = h_entries->GetNbinsX();
  // int bin_width = h_entries->GetBinLowEdge(2) - h_entries->GetBinLowEdge(3); //assumes equal binning

  // for(int xbinind = 1; xbinind <= nbins; xbinind++ ){
  //     cout<<"Bin: "<<h_entries->GetBinLowEdge(xbinind)<<" entries: "<<h_entries->GetBinContent(xbinind)<<endl;
  //   }
  //2D Histos
  /*for( int xbinind = 0; xbinind < 460; xbinind++ ){
  	for( int ybinind = 0; ybinind < 460; ybinind++ ){
  	  // cout<<Form("Getting ntries for %i | %i",xbinind*50,ybinind*50)<<endl;
  	  int binind = h_entries->FindBin(xbinind*5,ybinind*5);
  	  // int binentries = ch->GetEntries(Form("sparm_values[0]==%i&&sparm_values[1]==%i",xbinind*50,ybinind*50));
  	  // cout<<Form("Entries for %i | %i: %i",xbinind*50,ybinind*50,binentries)<<endl;
  	  // h_entries->SetBinContent(binind, binentries);
  	  // totalentries+=binentries;
  	  cout<<xbinind*5<<" | "<<ybinind*5<<" | "<<h_entries->GetBinContent(binind)<<endl;
  	}
  }*/

  // cout<<"total summed entries   : "<<totalentries<<endl;
  // cout<<"total entries from root: "<<ch->GetEntries()<<endl;

  TFile* fileout = TFile::Open("T5ZZ_entries.root","RECREATE");
  //TFile* fileout = TFile::Open("TChiWZ_ZToLL_entries.root","RECREATE");
  //TFile * fileout = TFile::Open("T5qqqqVV_entries_V08-00-09_FS.root","RECREATE");
  //TFile* fileout = TFile::Open("TChiHZ_HToBB_ZToLL_entries.root","RECREATE");
  //  TFile* fileout = TFile::Open("TChiZZ_ZToLL_entries.root","RECREATE");
  fileout->cd();
  h_entries->Write();
  fileout->Close();
  
  return;
}
