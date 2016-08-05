#ifndef TEMPLATELOOPER_h
#define TEMPLATELOOPER_h

#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"

class TChain;

class templateLooper
{
public:

  templateLooper();
  ~templateLooper();
  void ScanChain (TChain * chain,const std::string iter,const std::string sample, const std::string selection);
  void bookHistos( std::string signal_sample );
  void bookHist( std::string name, std::string title, int nbins, float xmin, float xmax );
  void fillHist( std::string obj, std::string var, std::string sel, float value, float weight );
  
private:

  std::map<std::string, TH1F*> mettemplate_hists;
  std::map<std::string, TH1F*> mettemplate_hists_ewk;
  std::map<std::string, TH1F*> event_hists;

  TH2F * h_signalyields_met100to150_ee;
  TH2F * h_signalyields_met100to150_mm;
  TH2F * h_signalyields_met100to150_ll;

  TH2F * h_signalyields_met150to225_ee;
  TH2F * h_signalyields_met150to225_mm;
  TH2F * h_signalyields_met150to225_ll;

  TH2F * h_signalyields_met225to300_ee;
  TH2F * h_signalyields_met225to300_mm;
  TH2F * h_signalyields_met225to300_ll;

  TH2F * h_signalyields_met225toinf_ee;
  TH2F * h_signalyields_met225toinf_mm;
  TH2F * h_signalyields_met225toinf_ll;

  TH2F * h_signalyields_met300toinf_ee;
  TH2F * h_signalyields_met300toinf_mm;
  TH2F * h_signalyields_met300toinf_ll;

};
#endif
