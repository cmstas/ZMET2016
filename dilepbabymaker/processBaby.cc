#include "TChain.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"

#include "ScanChain.h"

#include <iostream>

int main(int argc, char **argv) {

  if (argc < 3) {
    std::cout << "USAGE: processBaby <tag> <filename> [<max_num_events>]" << std::endl;
    return 1;
  }

  TString outfileid(argv[1]); 
  TString infile(argv[2]); 

  int max_events = -1;
  if (argc >= 4) max_events = atoi(argv[3]);
  std::cout << "set max number of events to: " << max_events << std::endl;
  
  std::cout<<"running on file: "<<infile.Data()<<std::endl;
  
  TChain *chain = new TChain("Events");
  chain->Add(infile.Data());
  // chain->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/merged_ntuple_2.root");
  // chain->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/merged_ntuple_3.root");
  if (chain->GetEntries() == 0) {
    std::cout << "ERROR: no entries in chain. filename was: " << infile << std::endl;
    return 2;
  }

  //-------------------------------------
  //set name to get comprehensible output -- will need to update these!
  //-------------------------------------
  char* sample;
  //MC
  if (infile.Contains("TTJets_MassiveBinDECAY_TuneZ2star_8TeV"))     sample = Form("ttall_%s",  	 outfileid.Data());
  else if (infile.Contains("TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola")) sample = Form("ttall_msdecays_%s",  	 outfileid.Data());
  else if (infile.Contains("TTJets_HadronicMGDecays_8TeV-madgraph-tauola")) sample = Form("tthad_lmgtau_%s",  	 outfileid.Data());
  else if (infile.Contains("TTJets_FullLeptMGDecays_8TeV-madgraph-tauola")) sample = Form("ttdl_lmgtau_%s",  	 outfileid.Data());
  else if (infile.Contains("TTJets_SemiLeptMGDecays_8TeV-madgraph-tauola")) sample = Form("ttsl_lmgtau_%s",  	 outfileid.Data());
  else if (infile.Contains("TTJets_HadronicMGDecays_8TeV-madgraph")) sample = Form("tthad_lmg_%s",  	 outfileid.Data());
  else if (infile.Contains("TTJets_FullLeptMGDecays_8TeV-madgraph")) sample = Form("ttdl_lmg_%s",  	 outfileid.Data());
  else if (infile.Contains("TTJets_SemiLeptMGDecays_8TeV-madgraph")) sample = Form("ttsl_lmg_%s",  	 outfileid.Data());
  else if (infile.Contains("WbbJetsToLNu"))                          sample = Form("wbbjets_%s",         outfileid.Data());
  else if (infile.Contains("WJetsToLNu_HT-100to200"))                sample = Form("wjets_ht100to200_%s",outfileid.Data());
  else if (infile.Contains("WJetsToLNu_HT-200to400"))                sample = Form("wjets_ht200to400_%s",outfileid.Data());
  else if (infile.Contains("WJetsToLNu_HT-400to600"))                sample = Form("wjets_ht400to600_%s",outfileid.Data());
  else if (infile.Contains("WJetsToLNu_HT-600toInf"))                sample = Form("wjets_ht600toInf_%s",outfileid.Data());
  else if (infile.Contains("WJetsToLNu"))                            sample = Form("wjets_%s",           outfileid.Data());
  else if (infile.Contains("W1JetsToLNu"))                           sample = Form("w1jets_%s",          outfileid.Data());
  else if (infile.Contains("W2JetsToLNu"))                           sample = Form("w2jets_%s",          outfileid.Data());
  else if (infile.Contains("W3JetsToLNu"))                           sample = Form("w3jets_%s",          outfileid.Data());
  else if (infile.Contains("W4JetsToLNu"))                           sample = Form("w4jets_%s",          outfileid.Data());
  else if (infile.Contains("WLNubbar"))                              sample = Form("wlnubb_amcatnlo_%s",         outfileid.Data());
  else if (infile.Contains("DYJetsToLL_M-50_HT-100to200"))           sample = Form("dyjetsll_ht100to200_%s",   outfileid.Data());
  else if (infile.Contains("DYJetsToLL_M-50_HT-200to400"))           sample = Form("dyjetsll_ht200to400_%s",   outfileid.Data());
  else if (infile.Contains("DYJetsToLL_M-50_HT-400to600"))           sample = Form("dyjetsll_ht400to600_%s",   outfileid.Data());
  else if (infile.Contains("DYJetsToLL_M-50_HT-600toInf"))           sample = Form("dyjetsll_ht600toInf_%s",   outfileid.Data());
  else if (infile.Contains("DYJetsToLL"))                            sample = Form("DYtot_%s",           outfileid.Data());
  else if (infile.Contains("DY1JetsToLL"))                           sample = Form("DY1Jtot_%s",         outfileid.Data());
  else if (infile.Contains("DY2JetsToLL"))                           sample = Form("DY2Jtot_%s",         outfileid.Data());
  else if (infile.Contains("DY3JetsToLL"))                           sample = Form("DY3Jtot_%s",         outfileid.Data());
  else if (infile.Contains("DY4JetsToLL"))                           sample = Form("DY4Jtot_%s",         outfileid.Data());
  else if (infile.Contains("ZJetsToNuNu_HT-100to200"))               sample = Form("zinv_ht100to200_%s", outfileid.Data());
  else if (infile.Contains("ZJetsToNuNu_HT-200to400"))               sample = Form("zinv_ht200to400_%s", outfileid.Data());
  else if (infile.Contains("ZJetsToNuNu_HT-400to600"))               sample = Form("zinv_ht400to600_%s", outfileid.Data());
  else if (infile.Contains("ZJetsToNuNu_HT-600toInf"))               sample = Form("zinv_ht600toInf_%s", outfileid.Data());
  else if (infile.Contains("QCD_Pt-5to10") || infile.Contains("QCD_Pt_5to10"))              sample = Form("qcd_pt5to10_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-10to15") || infile.Contains("QCD_Pt_10to15"))            sample = Form("qcd_pt10to15_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-15to30") || infile.Contains("QCD_Pt_15to30"))            sample = Form("qcd_pt15to30_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-30to50") || infile.Contains("QCD_Pt_30to50"))            sample = Form("qcd_pt30to50_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-50to80") || infile.Contains("QCD_Pt_50to80"))            sample = Form("qcd_pt50to80_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-80to120") || infile.Contains("QCD_Pt_80to120"))          sample = Form("qcd_pt80to120_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-120to170") || infile.Contains("QCD_Pt_120to170"))        sample = Form("qcd_pt120to170_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-170to300") || infile.Contains("QCD_Pt_170to300"))        sample = Form("qcd_pt170to300_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-300to470") || infile.Contains("QCD_Pt_300to470"))        sample = Form("qcd_pt300to470_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-470to600") || infile.Contains("QCD_Pt_470to600"))        sample = Form("qcd_pt470to600_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-600to800") || infile.Contains("QCD_Pt_600to800"))        sample = Form("qcd_pt600to800_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-800to1000") || infile.Contains("QCD_Pt_800to1000"))      sample = Form("qcd_pt800to1000_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-1000to1400") || infile.Contains("QCD_Pt_1000to1400"))    sample = Form("qcd_pt1000to1400_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-1400to1800") || infile.Contains("QCD_Pt_1400to1800"))    sample = Form("qcd_pt1400to1800_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-1800to2400") || infile.Contains("QCD_Pt_1800to2400"))    sample = Form("qcd_pt1800to2400_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-1800") || infile.Contains("QCD_Pt_1800"))                sample = Form("qcd_pt1800_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-2400to3200") || infile.Contains("QCD_Pt_2400to3200"))    sample = Form("qcd_pt2400to3200_%s",  outfileid.Data());
  else if (infile.Contains("QCD_Pt-3200") || infile.Contains("QCD_Pt_3200"))                sample = Form("qcd_pt3200_%s",  outfileid.Data());
  else if (infile.Contains("GJet_Pt-15to3000"))                      sample = Form("gjet_pt15to3000_%s",  outfileid.Data());
  else if (infile.Contains("GJets_HT-100to200"))                      sample = Form("gjet_ht100to200_%s",  outfileid.Data());
  else if (infile.Contains("GJets_HT-200to400"))                      sample = Form("gjet_ht200to400_%s",  outfileid.Data());
  else if (infile.Contains("GJets_HT-400to600"))                      sample = Form("gjet_ht400to600_%s",  outfileid.Data());
  else if (infile.Contains("GJets_HT-600toInf"))                      sample = Form("gjet_ht600toInf_%s",  outfileid.Data());
  else if (infile.Contains("TBarToDilepton_tW-channel"))	     sample = Form("singletop_tbarWchanb_2l_%s",  outfileid.Data());
  else if (infile.Contains("TBarToLeptons_s-channel"))		     sample = Form("singletop_tbarschan_l_%s", 	  outfileid.Data());
  else if (infile.Contains("TBarToLeptons_t-channel"))		     sample = Form("singletop_tbartchan_l_%s", 	  outfileid.Data());
  else if (infile.Contains("TBarToThadWlep_tW-channel"))	     sample = Form("singletop_tbarWchan_thWl_%s", outfileid.Data());
  else if (infile.Contains("TBarToTlepWhad_tW-channel"))	     sample = Form("singletop_tbarWchan_tlWh_%s", outfileid.Data());
  else if (infile.Contains("TToDilepton_tW-channel"))	     	     sample = Form("singletop_tWchan_2l_%s", 	  outfileid.Data());
  else if (infile.Contains("TToLeptons_s-channel"))		     sample = Form("singletop_tschan_l_%s", 	  outfileid.Data());
  else if (infile.Contains("TToLeptons_t-channel"))		     sample = Form("singletop_ttchan_l_%s", 	  outfileid.Data());
  else if (infile.Contains("TToThadWlep_tW-channel"))	     	     sample = Form("singletop_tWchan_thWl_%s", 	  outfileid.Data());
  else if (infile.Contains("TToTlepWhad_tW-channel"))	     	     sample = Form("singletop_tWchan_tlWh_%s", 	  outfileid.Data());
  else if (infile.Contains("T_s-channel"))                           sample = Form("singletop_tschan_%s",         outfileid.Data());
  else if (infile.Contains("Tbar_s-channel"))                        sample = Form("singletop_tbarschan_%s",      outfileid.Data());
  else if (infile.Contains("T_t-channel"))                           sample = Form("singletop_ttchan_%s",         outfileid.Data());
  else if (infile.Contains("Tbar_t-channel"))                        sample = Form("singletop_tbartchan_%s",      outfileid.Data());
  else if (infile.Contains("T_tW-channel"))                          sample = Form("singletop_tWchan_%s",         outfileid.Data());
  else if (infile.Contains("Tbar_tW-channel"))                       sample = Form("singletop_tbarWchan_%s",      outfileid.Data());
  else if (infile.Contains("WWJetsTo2L2Nu"))                         sample = Form("ww2l2nujets_%s",     outfileid.Data());
  else if (infile.Contains("ZZJetsTo4L"))                            sample = Form("zz4ljets_%s",        outfileid.Data());
  else if (infile.Contains("ZZJetsTo2L2Nu"))                         sample = Form("zz2l2nujets_%s",     outfileid.Data());
  else if (infile.Contains("ZZJetsTo2L2Q"))                          sample = Form("zz2l2qjets_%s",      outfileid.Data());
  else if (infile.Contains("WZJetsTo3LNu"))                          sample = Form("wz3lnujets_%s",      outfileid.Data());
  else if (infile.Contains("WZJetsTo2L2Q"))                          sample = Form("wz2l2qjets_%s",      outfileid.Data());
  else if (infile.Contains("WZJetsTo2QLNu"))                         sample = Form("wz2qlnujets_%s",     outfileid.Data());
  else if (infile.Contains("WGstarToLNu2E"))                         sample = Form("wglnu2ejets_%s",     outfileid.Data());
  else if (infile.Contains("WGstarToLNu2Mu"))                        sample = Form("wglnu2mujets_%s",    outfileid.Data());
  else if (infile.Contains("WGstarToLNu2Tau"))                       sample = Form("wglnu2taujets_%s",   outfileid.Data());
  else if (infile.Contains("ZZZNoGstarJets"))                        sample = Form("zzzjets_%s",         outfileid.Data());
  else if (infile.Contains("WZZNoGstarJets"))                        sample = Form("wzzjets_%s",         outfileid.Data());
  else if (infile.Contains("WWZNoGstarJets"))                        sample = Form("wwzjets_%s",         outfileid.Data());
  else if (infile.Contains("WWWJets"))                               sample = Form("wwwjets_%s",         outfileid.Data());
  else if (infile.Contains("WWGJets"))                               sample = Form("wwgjets_%s",         outfileid.Data());
  else if (infile.Contains("TBZ"))                                   sample = Form("tbz_%s",             outfileid.Data());
  else if (infile.Contains("TTZJets"))                               sample = Form("ttzjets_%s",         outfileid.Data());
  else if (infile.Contains("TTWJets"))                               sample = Form("ttwjets_%s",         outfileid.Data());
  else if (infile.Contains("TTGJets"))                               sample = Form("ttgjets_%s",         outfileid.Data());
  else if (infile.Contains("TTWWJets"))                              sample = Form("ttwwjets_%s",        outfileid.Data());
  else if (infile.Contains("TTbarH"))                                sample = Form("tth_%s",             outfileid.Data());
  else if (infile.Contains("TTJets_scaleup_TuneZ2star_8TeV"))        sample = Form("tt_scaleup_%s",      outfileid.Data());
  else if (infile.Contains("TTJets_scaledown_TuneZ2star_8TeV"))      sample = Form("tt_scaledw_%s",      outfileid.Data());
  else if (infile.Contains("TTJets_matchingup_TuneZ2star_8TeV"))     sample = Form("tt_matchup_%s",      outfileid.Data());
  else if (infile.Contains("TTJets_matchingdown_TuneZ2star_8TeV"))   sample = Form("tt_matchdw_%s",      outfileid.Data());
  else if (infile.Contains("TTJets_mass178_5_TuneZ2star_8TeV"))      sample = Form("tt_massup_%s",       outfileid.Data());
  else if (infile.Contains("TTJets_mass166_5_TuneZ2star_8TeV"))      sample = Form("tt_massdw_%s",       outfileid.Data());
  else if (infile.Contains("TT_CT10_TuneZ2star_8TeV-powheg"))        sample = Form("tt_powheg_%s",       outfileid.Data());
  else if (infile.Contains("TT_8TeV-mcatnlo"))          	     sample = Form("tt_mcatnlo_%s",      outfileid.Data());
  else if (infile.Contains("TTJets_CT10_8TeV-sherpa"))   	     sample = Form("tt_sherpa_%s",       outfileid.Data());
  else if (infile.Contains("WH_WToLNu_HToBB"))   	             sample = Form("whbb_%s",            outfileid.Data());
  else if (infile.Contains("SMS-T2tt"))                              sample = Form("T2tt_%s",            outfileid.Data());
  else if (infile.Contains("SMS-T2bw"))                              sample = Form("T2bw_%s",            outfileid.Data());
  else if (infile.Contains("SMS-T1tttt_2J_mGl-1500_mLSP-100"))       sample = Form("T1tttt_1500_100_%s", outfileid.Data());
  else if (infile.Contains("SMS-T1tttt_2J_mGl-1200_mLSP-800"))       sample = Form("T1tttt_1200_800_%s", outfileid.Data());
  else if (infile.Contains("SMS-T1qqqq_2J_mGl-1400_mLSP-100"))       sample = Form("T1qqqq_1400_100_%s", outfileid.Data());
  else if (infile.Contains("SMS-T1qqqq_2J_mGl-1000_mLSP-800"))       sample = Form("T1qqqq_1000_800_%s", outfileid.Data());
  else if (infile.Contains("SMS-T1bbbb_2J_mGl-1000_mLSP-900"))       sample = Form("T1bbbb_1000_900_%s", outfileid.Data());
  else if (infile.Contains("SMS-T1bbbb_2J_mGl-1500_mLSP-100"))       sample = Form("T1bbbb_1500_100_%s", outfileid.Data());
  else if (infile.Contains("SMS-T2tt_2J_mStop-850_mLSP-100"))        sample = Form("T2tt_850_100_%s", outfileid.Data());
  else if (infile.Contains("SMS-T2tt_2J_mStop-650_mLSP-325"))        sample = Form("T2tt_650_325_%s", outfileid.Data());
  else if (infile.Contains("SMS-T2tt_2J_mStop-500_mLSP-325"))        sample = Form("T2tt_500_325_%s", outfileid.Data());
  else if (infile.Contains("SMS-T2tt_2J_mStop-425_mLSP-325"))        sample = Form("T2tt_425_325_%s", outfileid.Data());
  else if (infile.Contains("SMS-T2bb_2J_mStop-900_mLSP-100"))        sample = Form("T2bb_900_100_%s", outfileid.Data());
  else if (infile.Contains("SMS-T2bb_2J_mStop-600_mLSP-580"))        sample = Form("T2bb_600_580_%s", outfileid.Data());
  else if (infile.Contains("SMS-T2qq_2J_mStop-1200_mLSP-100"))       sample = Form("T2qq_1200_100_%s", outfileid.Data());
  else if (infile.Contains("SMS-T2qq_2J_mStop-600_mLSP-550"))        sample = Form("T2qq_600_550_%s", outfileid.Data());
  else if (infile.Contains("SMS-T1tttt"))                            sample = Form("T1tttt_%s",          outfileid.Data());
  else if (infile.Contains("SMS-T1qqqq"))                            sample = Form("T1qqqq_%s",          outfileid.Data());
  else if (infile.Contains("SMS-T1bbbb"))                            sample = Form("T1bbbb_%s",          outfileid.Data());
  else if (infile.Contains("SMS-T5ZZ"))                              sample = Form("t5zz_%s",          outfileid.Data());
  else if (infile.Contains("SMS-TChiWZ"))                            sample = Form("tchiwz_%s",        outfileid.Data());
  else if (infile.Contains("SMS-TChiHZ_HToBB_ZToLL"))                sample = Form("tchihz_%s",        outfileid.Data());
  else if (infile.Contains("SMS-TChiZZ"))                            sample = Form("tchizz_%s",        outfileid.Data());

  //Data
  // //single mu-had
  // else if (infile.Contains("MuHad_Run2012A-recover-06Aug2012-v1_AOD"))          sample =  Form("MuHad2012A_recover06Aug2012v1V532_%s",     outfileid.Data());
  // else if (infile.Contains("MuHad_Run2012A-13Jul2012-v1_AOD"))                  sample =  Form("MuHad2012A_13Jul2012v1V532_%s",            outfileid.Data());
  // //single muon
  // else if (infile.Contains("SingleMu_Run2012A-recover-06Aug2012-v1_AOD"))       sample =  Form("SingleMu2012A_recover06Aug2012v1V532_%s",     outfileid.Data());
  // else if (infile.Contains("SingleMu_Run2012A-13Jul2012-v1_AOD"))       	sample =  Form("SingleMu2012A_13Jul2012v1V532_%s",            outfileid.Data());
  // else if (infile.Contains("SingleMu_Run2012B-13Jul2012-v1_AOD"))       	sample =  Form("SingleMu2012B_13Jul2012v1V532_%s",            outfileid.Data());
  // else if (infile.Contains("SingleMu_Run2012C-24Aug2012-v1_AOD"))      		sample =  Form("SingleMu2012C_24Aug2012v1V532_%s",            outfileid.Data());
  // else if (infile.Contains("SingleMu_Run2012C-PromptReco-v2_AOD"))      	sample =  Form("SingleMu2012C_PromptRecov2V532_%s",           outfileid.Data());
  // else if (infile.Contains("SingleMu_Run2012D-PromptReco-v1_AOD"))      	sample =  Form("SingleMu2012D_PromptRecov1V532_%s",           outfileid.Data());
  // //single electron
  // else if (infile.Contains("SingleElectron_Run2012A-recover-06Aug2012-v1_AOD")) sample =  Form("SingleElectron2012A_recover06Aug2012V532_%s", outfileid.Data());
  // else if (infile.Contains("SingleElectron_Run2012A-13Jul2012-v1_AOD"))       	sample =  Form("SingleElectron2012A_13Jul2012v1V532_%s",      outfileid.Data());
  // else if (infile.Contains("SingleElectron_Run2012B-13Jul2012-v1_AOD"))       	sample =  Form("SingleElectron2012B_13Jul2012v1V532_%s",      outfileid.Data());
  // else if (infile.Contains("SingleElectron_Run2012C-24Aug2012-v1_AOD"))      	sample =  Form("SingleElectron2012C_24Aug2012v1V532_%s",      outfileid.Data());
  // else if (infile.Contains("SingleElectron_Run2012C-PromptReco-v2_AOD"))      	sample =  Form("SingleElectron2012C_PromptRecov2V532_%s",     outfileid.Data());
  // else if (infile.Contains("SingleElectron_Run2012D-PromptReco-v1_AOD"))      	sample =  Form("SingleElectron2012D_PromptRecov1V532_%s",     outfileid.Data());
  // //dimuon 
  // else if (infile.Contains("DoubleMu_Run2012A-recover-06Aug2012-v1_AOD")) 	sample =  Form("DoubleMu2012A_recover06Aug2012V532_%s", outfileid.Data());
  // else if (infile.Contains("DoubleMu_Run2012A-13Jul2012-v1_AOD"))     		sample =  Form("DoubleMu2012A_13Jul2012v1V532_%s",            outfileid.Data());
  // else if (infile.Contains("DoubleMu_Run2012B-13Jul2012-v4_AOD"))     		sample =  Form("DoubleMu2012B_13Jul2012v4V532_%s",            outfileid.Data());
  // else if (infile.Contains("DoubleMu_Run2012C-24Aug2012-v1_AOD"))    		sample =  Form("DoubleMu2012C_24Aug2012v1V532_%s",            outfileid.Data());
  // else if (infile.Contains("DoubleMu_Run2012C-PromptReco-v2_AOD"))    		sample =  Form("DoubleMu2012C_PromptRecov2V532_%s",           outfileid.Data());
  // else if (infile.Contains("DoubleMu_Run2012D-PromptReco-v1_AOD"))    		sample =  Form("DoubleMu2012D_PromptRecov1V532_%s",           outfileid.Data());
  // //electron+muon
  // else if (infile.Contains("MuEG_Run2012A-recover-06Aug2012-v1_AOD"))      	sample =  Form("MuEG2012A_recover06Aug2012V532_%s",           outfileid.Data());
  // else if (infile.Contains("MuEG_Run2012A-13Jul2012-v1_AOD"))      		sample =  Form("MuEG2012A_13Jul2012v1V532_%s",      	      outfileid.Data());
  // else if (infile.Contains("MuEG_Run2012B-13Jul2012-v1_AOD"))      		sample =  Form("MuEG2012B_13Jul2012v1V532_%s",      	      outfileid.Data());
  // else if (infile.Contains("MuEG_Run2012C-24Aug2012-v1_AOD"))     		sample =  Form("MuEG2012C_24Aug2012v1V532_%s",     	      outfileid.Data());
  // else if (infile.Contains("MuEG_Run2012C-PromptReco-v2_AOD"))     		sample =  Form("MuEG2012C_PromptRecov2V532_%s",     	      outfileid.Data());
  // else if (infile.Contains("MuEG_Run2012D-PromptReco-v1_AOD"))     		sample =  Form("MuEG2012D_PromptRecov1V532_%s",     	      outfileid.Data());
  // //dielectron
  // else if (infile.Contains("DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD")) sample =  Form("DoubleElectron2012A_recover06Aug2012V532_%s", outfileid.Data());
  // else if (infile.Contains("DoubleElectron_Run2012A-13Jul2012-v1_AOD"))      	sample =  Form("DoubleElectron2012A_13Jul2012v1V532_%s",      outfileid.Data());
  // else if (infile.Contains("DoubleElectron_Run2012B-13Jul2012-v1_AOD"))      	sample =  Form("DoubleElectron2012B_13Jul2012v1V532_%s",      outfileid.Data());
  // else if (infile.Contains("DoubleElectron_Run2012C-24Aug2012-v1_AOD"))     	sample =  Form("DoubleElectron2012C_24Aug2012v1V532_%s",      outfileid.Data());
  // else if (infile.Contains("DoubleElectron_Run2012C-PromptReco-v2_AOD"))     	sample =  Form("DoubleElectron2012C_PromptRecov2V532_%s",     outfileid.Data());
  // else if (infile.Contains("DoubleElectron_Run2012D-PromptReco-v1_AOD"))     	sample =  Form("DoubleElectron2012D_PromptRecov1V532_%s",     outfileid.Data());
  //otherwise
  else sample = Form("unknown_%s", outfileid.Data());

  std::cout<<"sample is "<<sample<<std::endl;
  std::cout<<"outfileid "<<outfileid.Data()<<std::endl;

  //--------------------------------
  // run
  //--------------------------------
  
  babyMaker *looper = new babyMaker();
  looper->ScanChain(chain, sample, max_events); 
  return 0;
}
