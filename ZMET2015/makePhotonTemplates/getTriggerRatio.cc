#include "TChain.h"
#include "TCut.h"
#include <iostream>

using namespace std;

void getTriggerRatio()
{

  TChain ch("t");

	ch.Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016B_23sep2016rereco_ph_v*.root"));
	ch.Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016C_23sep2016rereco_ph_v*.root"));
	ch.Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016D_23sep2016rereco_ph_v*.root"));
	ch.Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016E_23sep2016rereco_ph_v*.root"));
	ch.Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016F_23sep2016rereco_ph_v*.root"));
	ch.Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016G_23sep2016rereco_ph_v*.root"));
	ch.Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016H_Prompt_ph_v*.root"));
	ch.Add(Form("/nfs-7/userdata/ZMEToutput/output/ZMETbabies/V08-22-05/data_2016H_Prompt_ph_v*.root"));

	TCut base("evt_type==2&&evt_passgoodrunlist>0&&HLT_Photon165_R9Id90_HE10_IsoM>0&&gamma_pt[0]>200");
	
    int trig_165 = ch.GetEntries(base);
    int trig_22  = ch.GetEntries("(evt_type==2&&evt_passgoodrunlist>0&&HLT_Photon22_R9Id90_HE10_IsoM>0&& gamma_pt[0]>200)*HLT_Photon22_R9Id90_HE10_IsoM"+base);
    int trig_30  = ch.GetEntries("(evt_type==2&&evt_passgoodrunlist>0&&HLT_Photon30_R9Id90_HE10_IsoM>0&& gamma_pt[0]>200)*HLT_Photon30_R9Id90_HE10_IsoM"+base);
    int trig_36  = ch.GetEntries("(evt_type==2&&evt_passgoodrunlist>0&&HLT_Photon36_R9Id90_HE10_IsoM>0&& gamma_pt[0]>200)*HLT_Photon36_R9Id90_HE10_IsoM"+base);
    int trig_50  = ch.GetEntries("(evt_type==2&&evt_passgoodrunlist>0&&HLT_Photon50_R9Id90_HE10_IsoM>0&& gamma_pt[0]>200)*HLT_Photon50_R9Id90_HE10_IsoM"+base);

	cout<<"trig165: "<<trig_165<<endl;
	cout<<"trig22:  "<<trig_22<<endl;
	cout<<"trig30:  "<<trig_30<<endl;
	cout<<"trig36:  "<<trig_36<<endl;
	cout<<"trig50:  "<<trig_50<<endl;
	
	cout<<"scale_22: "<<(float)trig_165/(float)trig_22<<endl;
	cout<<"scale_30: "<<(float)trig_165/(float)trig_30<<endl;
	cout<<"scale_36: "<<(float)trig_165/(float)trig_36<<endl;
	cout<<"scale_50: "<<(float)trig_165/(float)trig_50<<endl;

  return;
}
