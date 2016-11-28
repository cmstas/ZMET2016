#include "update_xsec.cc"

void mergeHadoopFiles(const TString& indir, const TString& outpath) {
  TChain *chain = new TChain("t");
  chain->Add(indir + "/*.root");

  if( !TString(outpath).Contains("data_") ){
  
	ULong64_t nevents_input = get_new_nevents( (string)indir );
	double scale1fb_input   = calculate_new_scale1fb( chain, (string)indir, (string)outpath );

	// 	if( nevents_input != chain->GetEntries("") ){
	
	// 	  //-------------------------------------------------------------
	// 	  // Removes branches to be replaced
	// 	  //-------------------------------------------------------------`
	// 	  chain->SetBranchStatus("*", 1);
	// 	  chain->SetBranchStatus("evt_scale1fb", 0);
	// 	  chain->SetBranchStatus("evt_nEvts", 0);

	// 	  cout << "Merging to file: " << outpath << endl;

	// 	  TFile *out = TFile::Open(outpath.Data(), "RECREATE");
	// 	  TTree *clone;
	// 	  clone = chain->CloneTree(-1, "fast");
	// 	  //  clone->SetMaxTreeSize(5000000000LL); // ~5 GB

	// 	  //-------------------------------------------------------------

	// 	  // "new" branches to overwrite old ones
	// 	  TBranch* b_evt_scale1fb = clone->Branch("evt_scale1fb", &scale1fb_input, "evt_scale1fb/F");
	// 	  TBranch* b_evt_nEvts = clone->Branch("evt_nEvts", &nevents_input, "evt_nEvts/l");
   
	// 	  for(ULong64_t i = 0; i < nevents_input; ++i) {
	// 		clone->GetEntry(i);

	// 		// fill new branches
	// 		b_evt_scale1fb->Fill();
	// 		b_evt_nEvts->Fill();
	// 	  }
	// 	  //-------------------------------------------------------------

	// 	  clone->Write(); 
	// 	  out->Close();
	// 	}  
  }

  chain->SetMaxTreeSize(5000000000LL); //default is 100000000000LL

  std::cout << "Merging files from dir: " << indir << std::endl
			<< "Ouputting to: " << outpath << std::endl;

  // chain->Add(indir + "/*.root");
  chain->Merge(outpath, "fast");
}
