#include <TLegend.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TImage.h"
#include "TSystem.h"
#include "TStyle.h"
#include "untuplizer.h"
#include <TClonesArray.h>
#include <fstream>
#include <cmath>
#include <TSystem.h>
#include <string>
#include <sstream>
#include "setNCUStyle.C"
#include <TH2.h>

TCanvas* c1;

void HHbbbbAnalyzerBase(int wM, string st,string st2,double Xsec=1,int SignalBkgNum=0){
	
	//for (int massP=0;massP<1;massP++){
		
		
		
	    
		
		int nPass[10]={0};
		int total=0;
		TH1D* th[30];
		
			th[0]=new TH1D("deltaEta","deltaEta",30,0,3);
			th[1]=new TH1D("Mjj","Mjj",2000,400,4000);
			th[2]=new TH1D("SDMass1","SDMass1",200,0,200);
			th[3]=new TH1D("SDMass2","SDMass2",200,0,200);
			th[4]=new TH1D("PRMass1","PRMass1",200,0,200);
			th[5]=new TH1D("PRMass2","PRMass2",200,0,200);
			th[6]=new TH1D("deltaR1","deltaR1",20,0,1);
			th[7]=new TH1D("deltaR2","deltaR2",20,0,1);
			th[8]=new TH1D("CSV1","CSV1",20,0,1);
			th[9]=new TH1D("CSV2","CSV2",20,0,1);
			th[10]=new TH1D("CSVSum","CSVSum",20,0,2);
			th[11]=new TH1D("CSVMax","CSVMax",20,0,1);
			th[12]=new TH1D("CSVMin","CSVMin",20,0,1);
			th[13]=new TH1D("tau21_1","tau21_1",20,0,1);
			th[14]=new TH1D("tau21_2","tau21_2",20,0,1);
			th[15]=new TH1D("jetPt1","jetPt1",1500,0,1500);
			th[16]=new TH1D("jetPt2","jetPt2",1500,0,1500);
			th[17]=new TH1D("PRMassC1","PRMassC1",600,0,600);
			th[18]=new TH1D("PRMassC2","PRMassC2",600,0,600);
			
			th[19]=new TH1D("FATjetPRmassL2L3Corr","FATjetPRmassL2L3Corr",600,0,600);
			th[20]=new TH1D("FATjetPRmassL2L3Corr_2","FATjetPRmassL2L3Corr_2",600,0,600);
			th[21]=new TH1D("FATjetPRmassL2L3CorrC","FATjetPRmassL2L3CorrC",600,0,600);
			th[22]=new TH1D("FATjetPRmassL2L3CorrC_2","FATjetPRmassL2L3CorrC_2",600,0,600);
			
			th[23]=new TH1D("MjjC","MjjC",2000,400,4000);
			th[24]=new TH1D("Mbb1","Mbb1",600,0,600);
			th[25]=new TH1D("Mbb2","Mbb2",600,0,600);
			th[26]=new TH1D("MbbC1","MbbC1",600,0,600);
			th[27]=new TH1D("MbbC2","MbbC2",600,0,600);
			
			TH1D* cs1=new TH1D("case1","case1",2000,400,6000);
			TH1D* cs2=new TH1D("case2","case2",2000,400,6000);
			TH1D* cs3=new TH1D("case3","case3",2000,400,6000);
			TH1D* cs4=new TH1D("case4","case4",2000,400,6000);
			TH1D* cs5=new TH1D("case5","case5",2000,400,6000);
			TH1D* csS=new TH1D("caseS","caseS",2000,400,6000);
		
			TH2F* th2f=new TH2F("2d","2d",600,0,600,600,0,600);
		for (int w=1;w<wM;w++){
			//cout<<Form("%s%d.root",st.data(),w)<<endl;
		//if(SignalBkgNum==1)f = TFile::Open(Form("%s",st.data()));
		//else 
			TFile *f;
			f = TFile::Open(Form("%s%d.root",st.data(),w));
		if (!f || !f->IsOpen())continue;
		TDirectory * dir;
		//if(SignalBkgNum==1)dir = (TDirectory*)f->Get(Form("%s:/tree",st.data()));
		//else 
			dir = (TDirectory*)f->Get(Form("%s%d.root:/tree",st.data(),w));
		
		cout<<w<<endl;
		
		TTree *tree;
		dir->GetObject("treeMaker",tree);
		
		TreeReader data(tree);
		
		total+=data.GetEntriesFast();
		
		
		
			
			

		
		for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){
			data.GetEntry(jEntry);
			
			Int_t nJet         = data.GetInt("FATnJet");
			TClonesArray* FATjetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
			float*   FATjetPRmass= data.GetPtrFloat("FATjetPRmass");  
			float*   FATjetSDmass= data.GetPtrFloat("FATjetSDmass");
			float*  FATjetCISVV2 = data.GetPtrFloat("FATjetCISVV2"); 
			float* FATjetTau1=data.GetPtrFloat("FATjetTau1");
		    float* FATjetTau2=data.GetPtrFloat("FATjetTau2");
			Int_t* FATnSubSDJet=data.GetPtrInt("FATnSubSDJet");
			vector<float>   *FATsubjetSDCSV = data.GetPtrVectorFloat("FATsubjetSDCSV");
		    vector<float>   *FATsubjetSDPx =  data.GetPtrVectorFloat("FATsubjetSDPx");
		    vector<float>   *FATsubjetSDPy =  data.GetPtrVectorFloat("FATsubjetSDPy");
		    vector<float>   *FATsubjetSDPz =  data.GetPtrVectorFloat("FATsubjetSDPz");
			Float_t*  jetPRmassL2L3Corr = data.GetPtrFloat("FATjetPRmassL2L3Corr");
			
			string fixName ="";if(SignalBkgNum==1)fixName="";
			
		    vector<float>   *FATsubjetSDE =  data.GetPtrVectorFloat(Form("FATsubjetSD%sE",fixName.data()));
			
			if(nJet<1)continue;
			
			vector<int> FatjetPreSelection;
			for(int i=0;i<nJet;i++){
				TLorentzVector* thisHiggs = (TLorentzVector*)FATjetP4->At(i);
				if(thisHiggs->Pt()<200)continue;
				if(fabs(thisHiggs->Eta())>2.4)continue;
				FatjetPreSelection.push_back(i);
			}
			if(FatjetPreSelection.size()<2)continue;
			
			//TH1D* th1=new TH1D("","",,0,);
			
			TLorentzVector* thisHiggs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection[0]);
			TLorentzVector* thatHiggs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection[1]);
			TLorentzVector mjj=*thisHiggs+*thatHiggs;
			csS->Fill(mjj.M()+250-thisHiggs->M()-thatHiggs->M());
			th[24]->Fill(thisHiggs->M());
			th[25]->Fill(thatHiggs->M());
			
			th[0]->Fill(fabs(thisHiggs->Eta()-thatHiggs->Eta()));
			th[1]->Fill(mjj.M());
			th[2]->Fill(FATjetSDmass[FatjetPreSelection[0]]);
			th[3]->Fill(FATjetSDmass[FatjetPreSelection[1]]);
			th[4]->Fill(FATjetPRmass[FatjetPreSelection[0]]);
			th[5]->Fill(FATjetPRmass[FatjetPreSelection[1]]);
			
			TLorentzVector  FATsubjet_1,FATsubjet_2,FATsubjet_3,FATsubjet_4;;
			FATsubjet_1.SetPxPyPzE(FATsubjetSDPx[FatjetPreSelection[0]][0],FATsubjetSDPy[FatjetPreSelection[0]][0],FATsubjetSDPz[FatjetPreSelection[0]][0],FATsubjetSDE[FatjetPreSelection[0]][0]);
			FATsubjet_2.SetPxPyPzE(FATsubjetSDPx[FatjetPreSelection[0]][1],FATsubjetSDPy[FatjetPreSelection[0]][1],FATsubjetSDPz[FatjetPreSelection[0]][1],FATsubjetSDE[FatjetPreSelection[0]][1]);
			FATsubjet_3.SetPxPyPzE(FATsubjetSDPx[FatjetPreSelection[1]][0],FATsubjetSDPy[FatjetPreSelection[1]][0],FATsubjetSDPz[FatjetPreSelection[1]][0],FATsubjetSDE[FatjetPreSelection[1]][0]);
			FATsubjet_4.SetPxPyPzE(FATsubjetSDPx[FatjetPreSelection[1]][1],FATsubjetSDPy[FatjetPreSelection[1]][1],FATsubjetSDPz[FatjetPreSelection[1]][1],FATsubjetSDE[FatjetPreSelection[1]][1]);
				
				
			th[6]->Fill(FATsubjet_1.DeltaR(FATsubjet_2));
			th[7]->Fill(FATsubjet_3.DeltaR(FATsubjet_4));
			
			
			th[8]->Fill(FATjetCISVV2[FatjetPreSelection[0]]);
			th[9]->Fill(FATjetCISVV2[FatjetPreSelection[1]]);
			
			th[10]->Fill(FATjetCISVV2[FatjetPreSelection[0]]+FATjetCISVV2[FatjetPreSelection[1]]);
			double temp=FATjetCISVV2[FatjetPreSelection[0]]>FATjetCISVV2[FatjetPreSelection[1]]?FATjetCISVV2[FatjetPreSelection[0]]:FATjetCISVV2[FatjetPreSelection[1]];
			th[11]->Fill(temp);
			temp=FATjetCISVV2[FatjetPreSelection[0]]<FATjetCISVV2[FatjetPreSelection[1]]?FATjetCISVV2[FatjetPreSelection[0]]:FATjetCISVV2[FatjetPreSelection[1]];
			th[12]->Fill(temp);
			
			
			
			th[13]->Fill(FATjetTau2[FatjetPreSelection[0]]/FATjetTau1[FatjetPreSelection[0]]);
			th[14]->Fill(FATjetTau2[FatjetPreSelection[1]]/FATjetTau1[FatjetPreSelection[1]]);
			
			th[15]->Fill(thisHiggs->Pt());
			//cout<<thisHiggs->Pt()<<endl;
			th[16]->Fill(thatHiggs->Pt());
			

			vector<int> FatjetPreSelection1i,FatjetPreSelection1j;
			for(unsigned int i=0;i<FatjetPreSelection.size();i++){
				TLorentzVector* thisHiggs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection[i]);
				for(unsigned int j=i+1;j<FatjetPreSelection.size();j++){
					TLorentzVector* thatHiggs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection[j]);
				    if(fabs(thisHiggs->Eta()-thatHiggs->Eta())<1.3){
						FatjetPreSelection1i.push_back(FatjetPreSelection[i]);
						FatjetPreSelection1j.push_back(FatjetPreSelection[j]);
					}
				}
				//if(isDeltaEta13)break;
			}
			if(FatjetPreSelection1i.size()<1)continue;
	
			nPass[0]++;
			
			vector<int> FatjetPreSelection2i,FatjetPreSelection2j;
			for(unsigned int i=0;i<FatjetPreSelection1i.size();i++){
				TLorentzVector* thisHiggs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection1i[i]);
				TLorentzVector* thatHiggs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection1j[i]);
				TLorentzVector mjj=*thisHiggs+*thatHiggs;
				//cout<<mjj.M()<<endl;
				if(mjj.M()>1000){
					//cout<<"y"<<endl;
					FatjetPreSelection2i.push_back(FatjetPreSelection1i[i]);
				    FatjetPreSelection2j.push_back(FatjetPreSelection1j[i]);
					
				}
				
				
			}
			if(FatjetPreSelection2i.size()<1)continue;
			nPass[1]++;
			
			vector<int> FatjetPreSelection3i,FatjetPreSelection3j;
			for(unsigned int i=0;i<FatjetPreSelection2i.size();i++){
				
				th[19]->Fill(jetPRmassL2L3Corr[FatjetPreSelection2i[i]]);
				th[20]->Fill(jetPRmassL2L3Corr[FatjetPreSelection2j[i]]);
				th2f->Fill(jetPRmassL2L3Corr[FatjetPreSelection2i[i]],jetPRmassL2L3Corr[FatjetPreSelection2j[i]]);
				
				if(jetPRmassL2L3Corr[FatjetPreSelection2i[i]]>135||jetPRmassL2L3Corr[FatjetPreSelection2i[i]]<105)continue;
				if(jetPRmassL2L3Corr[FatjetPreSelection2j[i]]>135||jetPRmassL2L3Corr[FatjetPreSelection2j[i]]<105)continue;
				//if(FATjetPRmass[FatjetPreSelection2j[i]]>130||FATjetPRmass[FatjetPreSelection2j[i]]<95)continue;
				//if(FATjetPRmass[FatjetPreSelection2i[i]]>150||FATjetPRmass[FatjetPreSelection2i[i]]<90)continue;
				//if(FATjetPRmass[FatjetPreSelection2j[i]]>150||FATjetPRmass[FatjetPreSelection2j[i]]<90)continue;
				
				
				
				FatjetPreSelection3i.push_back(FatjetPreSelection2i[i]);
				FatjetPreSelection3j.push_back(FatjetPreSelection2j[i]);
			}
			if(FatjetPreSelection3i.size()<1)continue;
			nPass[2]++;
			
			vector<int> FatjetPreSelection4i,FatjetPreSelection4j;
			for(unsigned int i=0;i<FatjetPreSelection3i.size();i++){
				if(FATnSubSDJet[FatjetPreSelection3i[i]]<2||FATnSubSDJet[FatjetPreSelection3j[i]]<2)continue;
				TLorentzVector  FATsubjet_1,FATsubjet_2;
				bool thisHiggsBTagTight=0,thisHiggsBTagLoose=0;
				FATsubjet_1.SetPxPyPzE(FATsubjetSDPx[FatjetPreSelection3i[i]][0],FATsubjetSDPy[FatjetPreSelection3i[i]][0],FATsubjetSDPz[FatjetPreSelection3i[i]][0],FATsubjetSDE[FatjetPreSelection3i[i]][0]);
				FATsubjet_2.SetPxPyPzE(FATsubjetSDPx[FatjetPreSelection3i[i]][1],FATsubjetSDPy[FatjetPreSelection3i[i]][1],FATsubjetSDPz[FatjetPreSelection3i[i]][1],FATsubjetSDE[FatjetPreSelection3i[i]][1]);
				if(FATsubjet_1.DeltaR(FATsubjet_2)<0.3 && FATjetCISVV2[FatjetPreSelection3i[i]]<0.244)continue;
				if(FATsubjet_1.DeltaR(FATsubjet_2)>0.3 && (FATsubjetSDCSV[FatjetPreSelection3i[i]][0]>0.244 || FATsubjetSDCSV[FatjetPreSelection3i[i]][1]>0.244))thisHiggsBTagLoose=1;
				if(FATsubjet_1.DeltaR(FATsubjet_2)>0.3 && (FATsubjetSDCSV[FatjetPreSelection3i[i]][0]>0.244 && FATsubjetSDCSV[FatjetPreSelection3i[i]][1]>0.244))thisHiggsBTagTight=1;
				if(FATsubjet_1.DeltaR(FATsubjet_2)<0.3){
					thisHiggsBTagTight=1;
					thisHiggsBTagLoose=1;
				}
				FATsubjet_1.SetPxPyPzE(FATsubjetSDPx[FatjetPreSelection3j[i]][0],FATsubjetSDPy[FatjetPreSelection3j[i]][0],FATsubjetSDPz[FatjetPreSelection3j[i]][0],FATsubjetSDE[FatjetPreSelection3j[i]][0]);
				FATsubjet_2.SetPxPyPzE(FATsubjetSDPx[FatjetPreSelection3j[i]][1],FATsubjetSDPy[FatjetPreSelection3j[i]][1],FATsubjetSDPz[FatjetPreSelection3j[i]][1],FATsubjetSDE[FatjetPreSelection3j[i]][1]);
				TLorentzVector  FATsubjet_3,FATsubjet_4;
				bool thatHiggsBTagTight=0,thatHiggsBTagLoose=0;
				if(FATsubjet_3.DeltaR(FATsubjet_4)<0.3 && FATjetCISVV2[FatjetPreSelection3j[i]]<0.244)continue;
				if(FATsubjet_3.DeltaR(FATsubjet_4)>0.3 && (FATsubjetSDCSV[FatjetPreSelection3j[i]][0]>0.244 || FATsubjetSDCSV[FatjetPreSelection3j[i]][1]>0.244))thatHiggsBTagLoose=1;
				if(FATsubjet_3.DeltaR(FATsubjet_4)>0.3 && (FATsubjetSDCSV[FatjetPreSelection3j[i]][0]>0.244 && FATsubjetSDCSV[FatjetPreSelection3j[i]][1]>0.244))thatHiggsBTagTight=1;
				if(FATsubjet_3.DeltaR(FATsubjet_4)<0.3){
					thatHiggsBTagTight=1;
					thatHiggsBTagLoose=1;
				}
				//if(FATsubjet_3.DeltaR(FATsubjet_4)>0.3)cout<<"Y"<<endl;
				if(thisHiggsBTagLoose==0 || thatHiggsBTagLoose==0 ){
					//cout<<thisHiggsBTagLoose<<","<<thatHiggsBTagLoose<<endl;
					//if(FATsubjet_3.DeltaR(FATsubjet_4)>0.3)cout<<FATsubjetSDCSV[FatjetPreSelection3j[i]][0]<<","<<FATsubjetSDCSV[FatjetPreSelection3j[i]][1]<<endl;
					continue;
					
				}
				if(thisHiggsBTagTight==0 && thatHiggsBTagTight==0) continue;
				FatjetPreSelection4i.push_back(FatjetPreSelection3i[i]);
				FatjetPreSelection4j.push_back(FatjetPreSelection3j[i]);
				
				
			}
			//if(numHiggsBTagLoose<2||numHiggsBTagTight<1)continue;
            if(FatjetPreSelection4i.size()<1)continue;
			nPass[3]++;
			
			//int numHiggsHP=0,numHiggsLP=0;
			
			bool isPassingTau=0;
			for(unsigned int i=0;i<FatjetPreSelection4i.size();i++){
				bool thisHiggsHP=0,thisHiggsLP=0;
				if(FATjetTau2[FatjetPreSelection4i[i]]/FATjetTau1[FatjetPreSelection4i[i]]<0.5)thisHiggsHP=1;
				if(FATjetTau2[FatjetPreSelection4i[i]]/FATjetTau1[FatjetPreSelection4i[i]]<0.75 && FATjetTau2[FatjetPreSelection4i[i]]/FATjetTau1[FatjetPreSelection4i[i]]>0.5)thisHiggsLP=1;
				if(thisHiggsHP)thisHiggsLP=1;
				bool thatHiggsHP=0,thatHiggsLP=0;
			
				
				if(FATjetTau2[FatjetPreSelection4j[i]]/FATjetTau1[FatjetPreSelection4j[i]]<0.5)thatHiggsHP=1;
				if(FATjetTau2[FatjetPreSelection4j[i]]/FATjetTau1[FatjetPreSelection4j[i]]<0.75 && FATjetTau2[FatjetPreSelection4j[i]]/FATjetTau1[FatjetPreSelection4j[i]]>0.5)thatHiggsLP=1;
				if(thatHiggsHP)thatHiggsLP=1;
				
				if(thisHiggsLP==0 || thatHiggsLP==0 )continue;
				if(thisHiggsHP==0 && thatHiggsHP==0) continue;
				
				isPassingTau=1;
			}
			if(isPassingTau==0)continue;
			
  
			nPass[4]++;
			
			TLorentzVector* thisHiggsCs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection4i[0]);
			TLorentzVector* thatHiggsCs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection4j[0]);
			TLorentzVector mjjCs=*thisHiggsCs+*thatHiggsCs;
			cs1->Fill(mjjCs.M());
			
			
			thatHiggsCs ->SetPxPyPzE(thatHiggsCs->Px()*125/jetPRmassL2L3Corr[FatjetPreSelection4j[0]],thatHiggsCs->Py()*125/jetPRmassL2L3Corr[FatjetPreSelection4j[0]],thatHiggsCs->Pz()*125/jetPRmassL2L3Corr[FatjetPreSelection4j[0]],thatHiggsCs->E()*125/jetPRmassL2L3Corr[FatjetPreSelection4j[0]]);
			
			mjjCs=*thisHiggsCs+*thatHiggsCs;
			cs2->Fill(mjjCs.M());
			
			thisHiggsCs ->SetPxPyPzE(thisHiggsCs->Px()*125/jetPRmassL2L3Corr[FatjetPreSelection4i[0]],thisHiggsCs->Py()*125/jetPRmassL2L3Corr[FatjetPreSelection4i[0]],thisHiggsCs->Pz()*125/jetPRmassL2L3Corr[FatjetPreSelection4i[0]],thisHiggsCs->E()*125/jetPRmassL2L3Corr[FatjetPreSelection4i[0]]);
			
			mjjCs=*thisHiggsCs+*thatHiggsCs;
			cs3->Fill(mjjCs.M());
			
			thisHiggsCs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection4i[0]);
			thatHiggsCs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection4j[0]);
			double scaleThis = 125/thisHiggsCs->M();
			double scaleThat = 125/thatHiggsCs->M();
			
			thisHiggsCs ->SetPxPyPzE(thisHiggsCs->Px()*scaleThis,thisHiggsCs->Py()*scaleThis,thisHiggsCs->Pz()*scaleThis,thisHiggsCs->E()*scaleThis);
			thatHiggsCs ->SetPxPyPzE(thatHiggsCs->Px()*scaleThat,thatHiggsCs->Py()*scaleThat,thatHiggsCs->Pz()*scaleThat,thatHiggsCs->E()*scaleThat);
		
			mjjCs=*thisHiggsCs+*thatHiggsCs;
			cs4->Fill(mjjCs.M());
			
			thisHiggsCs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection4i[0]);
			thatHiggsCs = (TLorentzVector*)FATjetP4->At(FatjetPreSelection4j[0]);
			mjjCs=*thisHiggsCs+*thatHiggsCs;
			
			cs5->Fill(mjjCs.M()+250-thisHiggsCs->M()-thatHiggsCs->M());
			
			th[21]->Fill(jetPRmassL2L3Corr[FatjetPreSelection4i[0]]);
			th[22]->Fill(jetPRmassL2L3Corr[FatjetPreSelection4j[0]]);
			
			th[17]->Fill(FATjetPRmass[FatjetPreSelection4i[0]]);
			th[18]->Fill(FATjetPRmass[FatjetPreSelection4j[0]]);
			
			th[26]->Fill(thisHiggsCs->M());
			th[27]->Fill(thatHiggsCs->M());
			th[23]->Fill(mjjCs.M());
		}
		
		
		
		
		}
		
		
	for(int i=0 ;i< 28;i++)th[i]->Scale(1000*Xsec/total);
	
	th2f->Scale(1000*Xsec/total);
	cs1->Scale(1000*Xsec/total);
	cs2->Scale(1000*Xsec/total);
	cs3->Scale(1000*Xsec/total);
	cs4->Scale(1000*Xsec/total);
	cs5->Scale(1000*Xsec/total);
	csS->Scale(1000*Xsec/total);
		
	TFile* outFile = new TFile(Form("root_files/%s.root",st2.data()),"recreate");   
	
	for(int i=0 ;i< 28;i++)th[i]->Write();
	
	cs1->Write();
	cs2->Write();
	cs3->Write();
	cs4->Write();
	cs5->Write();
	csS->Write();

	th2f->Write();
	//cout<<th2f->GetCorrelationFactor();
	outFile->Close();
	
	for(int i=0 ;i<28;i++)th[i]->Clear();
	
	cs1->Clear();
	cs2->Clear();
	cs3->Clear();
	cs4->Clear();
	cs5->Clear();
	csS->Clear();
	th2f->Clear();
	
	//dir->Close();
	//delete f;
}


void HHbbbbDrawer(int a){
	setNCUStyle();
	
	string st1[20]={
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-1000_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_215300/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-1200_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_215340/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-1400_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_215429/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-1600_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-1600_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_215514/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-2000_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-2000_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_215644/0000/NCUGlobalTuples_",
	/*6*/"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-2500_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-2500_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_215734/0000/NCUGlobalTuples_",
	    "/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-3000_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-3000_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_215815/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-3500_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-3500_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_215903/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-4000_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-4000_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_215944/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/BulkGravToHHBBBBSignal_eleIDjet_CMSSW7412_20151006/BulkGravTohhTohbbhbb_narrow_M-4500_13TeV-madgraph/crab_BulkGravTohhTohbbhbb_narrow_M-4500_13TeV-madgraphMC25ns_eleIDjet_CMSSW7412_20151006/151007_220034/0000/NCUGlobalTuples_",
	/*11*/
		//"/data2/syu/13TeV/BulkGravTohhTohbbhbb/softdrop_BulkGravTohhTohbbhbb_narrow_M-4500_13TeV-madgraph.root",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/crab_QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8MC25ns_eleIDjet_CMSSW7412_20151006/151007_220208/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/crab_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8MC25ns_eleIDjet_CMSSW7412_20151006/151007_220428/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/crab_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8MC25ns_eleIDjet_CMSSW7412_20151006/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/crab_QCD_HT500to7000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8MC25ns_eleIDjet_CMSSW7412_20151006/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/crab_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8MC25ns_eleIDjet_CMSSW7412_20151006/0000/NCUGlobalTuples_",
	/*16*/
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/crab_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8MC25ns_eleIDjet_CMSSW7412_20151006/151007_220114/0000/NCUGlobalTuples_",
	    "/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/crab_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8MC25ns_eleIDjet_CMSSW7412_20151006/151007_220249/0000/NCUGlobalTuples_",
		"/data7/khurana/NCUGlobalTuples/SPRING15_2015_10_12/crab_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8MC25ns_eleIDjet_CMSSW7412_20151006/151007_220339/0000/NCUGlobalTuples_",
	
	};
	
	string  masspoint[10]={"1000","1200","1400","1600","2000","2500","3000","3500","4000","4500"};
	
	TH1D* th1[20];
	if(a==9)for(int i=0;i<10;i++)HHbbbbAnalyzerBase(7,st1[i],masspoint[i],1,1);
	if(a==10)HHbbbbAnalyzerBase(813,st1[10],"QCD100" ,27850000,0);
	if(a==11)HHbbbbAnalyzerBase(516,st1[11],"QCD200" ,1717000,0);
	if(a==12)HHbbbbAnalyzerBase(565,st1[12],"QCD300" ,351300,0);
	if(a==13)HHbbbbAnalyzerBase(496,st1[13],"QCD500" ,31630,0);
	if(a==14)HHbbbbAnalyzerBase(394,st1[14],"QCD700" ,6802,0);
	if(a==15)HHbbbbAnalyzerBase(155,st1[15],"QCD1000",1206,0);
	if(a==16)HHbbbbAnalyzerBase(103,st1[16],"QCD1500",120.4,0);
	if(a==17)HHbbbbAnalyzerBase(71 ,st1[17],"QCD2000",25.24,0);
	
	
	
	
	
	
	
}