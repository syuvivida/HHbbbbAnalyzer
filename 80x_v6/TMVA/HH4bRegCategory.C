//Histogram 
#include <TH1.h>
//#include <TH1F.h>
#include <TH1D.h>
#include <TH2D.h>
#include "TF1.h"
#include <TGraph.h>
//#include <TGraphErrors.h>

//vector ,string ,stream
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
//#include <fstream>
//#include <sstream>

//root feature
//#include <TLegend.h>
//#include <TRandom.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TFile.h>
#include <TClonesArray.h>

//math 
#include <cmath>
//#include <algorithm>

//other including
//#include "setNCUStyle.C"
#include "../untuplizer.h"
//#include "jetEnergyScale.h"


#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

#define  nWidth 5
#define  nBmin 11

#define nMass 3
#define nCat 4

using namespace std;
using namespace TMVA;

float getPUPPIweight(float puppipt, float puppieta ){

double barrleMean[13]={1.16593,1.1533,1.14748,1.14386,1.13825,1.13982,1.14124,1.14252,1.14885,1.15503,1.16188};
double endcapMean[13]={1.32643,1.29727,1.27819,1.25759,1.25419,1.23614,1.22092,1.22342,1.23004,1.22335,1.22874};
double barrlex[13]={325.254,364.602,407.173,452.286,540.273,627.553,714.669,799.949,883.213,1097.31,1310.44,1728.48,1937.44};
double endcapx[13]={300.721,337.376,374.014,408.777,472.758,531.384,589.311,637.263,683.63,804.23,910.163,1081.75,1176.51};
TGraph* tg1=new TGraph(11,barrlex,barrleMean);
TGraph* tg2=new TGraph(11,endcapx,endcapMean);

  float totalWeight=1;
   if( fabs(puppieta)  <= 1.3 ){
	return tg1->Eval(puppipt);
   }
else{
	 return tg2->Eval(puppipt);
}
  // file->Close();
  //return totalWeight;
}

float getPUPPIweightOnRegressed(float puppipt, float puppieta ){

double barrleMean[13]={0.983602,1.01681,1.0416,1.06712,1.09811,1.09607,1.05727,1.07846,1.10783,1.09147,1.12839};
double endcapMean[13]={1.09957,1.1156,1.12732,1.1481,1.16446,1.15879,1.14886,1.15286,1.16249,1.17772,1.17944};
double barrlex[13]={382.737,416.886,450.274,487.441,568.772,665.847,761.498,842.68,919.298,1152.37,1345.38};
double endcapx[13]={355.246,390.192,421.469,449.83,508.275,567.493,624.998,673.756,715.198,830.788,933.179};
TGraph* tg1=new TGraph(11,barrlex,barrleMean);
TGraph* tg2=new TGraph(11,endcapx,endcapMean);

  float totalWeight=1;
   if( fabs(puppieta)  <= 1.3 ){
	return tg1->Eval(puppipt);
   }
else{
	 return tg2->Eval(puppipt);
}
  // file->Close();
  //return totalWeight;
}

float getPUPPIweight_o(float puppipt, float puppieta ){

   TF1* puppisd_corrGEN      = new TF1("puppisd_corrGEN","[0]+[1]*pow(x*[2],-[3])");
  puppisd_corrGEN->SetParameters(
   				 1.00626,
   				 -1.06161,
   				 0.07999,
   				 1.20454
   				 );
  TF1* puppisd_corrRECO_cen = new TF1("puppisd_corrRECO_cen","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)");
  puppisd_corrRECO_cen->SetParameters(
   				      1.05807,
   				      -5.91971e-05,
   				      2.296e-07,
   				      -1.98795e-10,
   				      6.67382e-14,
   				      -7.80604e-18
   				      );

  TF1* puppisd_corrRECO_for = new TF1("puppisd_corrRECO_for","[0]+[1]*x+[2]*pow(x,2)+[3]*pow(x,3)+[4]*pow(x,4)+[5]*pow(x,5)");
  puppisd_corrRECO_for->SetParameters(
   				      1.26638,
   				      -0.000658496,
   				      9.73779e-07,
   				      -5.93843e-10,
   				      1.61619e-13,
   				      -1.6272e-17);

  float genCorr  = 1.;
  float recoCorr = 1.;
  float totalWeight = 1.;

  genCorr =  puppisd_corrGEN->Eval( puppipt );
  if( fabs(puppieta)  <= 1.3 ) recoCorr = puppisd_corrRECO_cen->Eval( puppipt );
  else
    if( fabs(puppieta) > 1.3 ) recoCorr = puppisd_corrRECO_for->Eval( puppipt );

  totalWeight = genCorr * recoCorr;
  // file->Close();
  return totalWeight;
}

void TMVARegressionApplication( int wMs,int wM, string st,string st2,string option="",TString myMethodList = "" ) 
{
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDEFoam"]         = 0; 
   Use["KNN"]             = 0;
   // 
   // --- Linear Discriminant Analysis
   Use["LD"]		        = 0;
   // 
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   // 
   // --- Neural Network
   Use["MLP"]             = 0; 
   // 
   // --- Support Vector Machine 
   Use["SVM"]             = 0;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 0;
   Use["BDTG"]            = 1;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVARegressionApplication" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   //Float_t var1, var2;
   //reader->AddVariable( "var1", &var1 );
   //reader->AddVariable( "var2", &var2 );
   Float_t pt_AK8MatchedToHbb,eta_AK8MatchedToHbb,nsv_AK8MatchedToHbb,sv0mass_AK8MatchedToHbb,sv1mass_AK8MatchedToHbb,
   nch_AK8MatchedToHbb,nmu_AK8MatchedToHbb,nel_AK8MatchedToHbb,muenfr_AK8MatchedToHbb,emenfr_AK8MatchedToHbb;
   reader->AddVariable( "pt_AK8MatchedToHbb", &pt_AK8MatchedToHbb );
   reader->AddVariable( "eta_AK8MatchedToHbb", &eta_AK8MatchedToHbb );
   reader->AddVariable( "nsv_AK8MatchedToHbb", &nsv_AK8MatchedToHbb );
   reader->AddVariable( "sv0mass_AK8MatchedToHbb", &sv0mass_AK8MatchedToHbb );
   reader->AddVariable( "sv1mass_AK8MatchedToHbb", &sv1mass_AK8MatchedToHbb );
   reader->AddVariable( "nch_AK8MatchedToHbb", &nch_AK8MatchedToHbb );
   reader->AddVariable( "nmu_AK8MatchedToHbb", &nmu_AK8MatchedToHbb );
   reader->AddVariable( "nel_AK8MatchedToHbb", &nel_AK8MatchedToHbb );
   reader->AddVariable( "muenfr_AK8MatchedToHbb", &muenfr_AK8MatchedToHbb );
   reader->AddVariable( "emenfr_AK8MatchedToHbb", &emenfr_AK8MatchedToHbb );

   
   // Spectator variables declared in the training have to be added to the reader, too
   Float_t spec1,spec2;
    reader->AddSpectator( "spec1:=n_pv",  &spec1 );
   reader->AddSpectator( "spec2:=msoftdrop_AK8MatchedToHbb",  &spec2 );

   // --- Book the MVA methods

   TString dir    = "weights/";
   TString prefix = "TMVARegression";

   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = it->first + " method";
         TString weightfile = dir + prefix + "_" + TString(it->first) + ".weights.xml";
         reader->BookMVA( methodName, weightfile ); 
      }
   }
   
     TH1* hists[100];
   Int_t nhists = -1;
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
         TH1* h = new TH1F( it->first.c_str(), TString(it->first) + " method", 100, -100, 600 );
         if (it->second) hists[++nhists] = h;
      }
      nhists++;
   
  //1=signal ,0=QCD ,2=data
	int nameRoot=1;
	if((st2.find("QCD")!= std::string::npos)||
	(st2.find("bGen")!= std::string::npos)||
	(st2.find("bEnriched")!= std::string::npos))nameRoot=0;
	if(st2.find("data")!= std::string::npos)nameRoot=2;
	cout<<"nameRoot = "<<nameRoot<<endl;
	
	//option-----------------------------------------------------------
	
	int JESOption=0;
	
   
   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //   
   TFile *f;
	TTree *tree;
	int nPass[20]={0};
	int total=0;
	double fixScaleNum[2]={0};
	
	TH1D* th1=new TH1D("a","a",150,50,200);	
	
	string massName[nMass]={"Thea","HCorr","Reg"};
	string catName[nCat]={"PP","PF","FP","FF"};
	string tau21Name[3]={"withTau21","woTau21","antiTau21"};
	
	TH1D* th2[nMass][nCat][3];
	TH1D* th3[nMass][nCat][3];
	TH1D* th4[nMass][nCat][3];
	for(int i=0;i<nMass;i++){
		for(int j=0;j<nCat;j++){
			for(int k=0;k<3;k++){
				th2[i][j][k]=(TH1D*)th1->Clone(Form("loose_%s_%s_%s",massName[i].data(),catName[j].data(),tau21Name[k].data()));
				th3[i][j][k]=(TH1D*)th1->Clone(Form("tight_%s_%s_%s",massName[i].data(),catName[j].data(),tau21Name[k].data()));
				th4[i][j][k]=(TH1D*)th1->Clone(Form("tl_%s_%s_%s",massName[i].data(),catName[j].data(),tau21Name[k].data()));
				
				th2[i][j][k]->Sumw2();
				th3[i][j][k]->Sumw2();
				th4[i][j][k]->Sumw2();
			}
		}
	}
	
   
   for (int w=wMs;w<wM;w++){
		if(w%20==0)cout<<w<<endl;
		
		if (nameRoot!=1)f = TFile::Open(Form("%s%d.root",st.data(),w));
		else f = TFile::Open(st.data());
		if (!f || !f->IsOpen())continue;
		
/*TDirectory * dir;
		if (nameRoot!=1)dir = (TDirectory*)f->Get(Form("%s%d.root:/tree",st.data(),w));
		else dir = (TDirectory*)f->Get(Form("%s:/tree",st.data()));
		
		dir->GetObject("treeMaker",tree);
		*/
		tree=(TTree*)f->Get("treeMaker");
		TreeReader data(tree);
		total+=data.GetEntriesFast();
		for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){
			data.GetEntry(jEntry);
			
			
			
			Int_t nVtx        = data.GetInt("nVtx");
			//0. has a good vertex
			if(nVtx<1)continue;
			nPass[0]++;
			
			//1.trigger
			std::string* trigName = data.GetPtrString("hlt_trigName");
		 	vector<bool> &trigResult = *((vector<bool>*) data.GetPtr("hlt_trigResult"));
			bool passTrigger=false;
			for(int it=0; it< data.GetPtrStringSize();it++){
				std::string thisTrig= trigName[it];
				bool results = trigResult[it];
				if( ((thisTrig.find("HLT_PFHT800")!= std::string::npos||
					thisTrig.find("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20")!= std::string::npos
						) && results==1)){
					passTrigger=true;
					break;
				}
			}
			if(!passTrigger && nameRoot==2)continue;
			nPass[1]++;

			const int nAK8Jet=data.GetInt("AK8PuppinJet");
			//2.nJets
			if(nAK8Jet<2)continue;nPass[2]++;
			int* AK8PuppinSubSDJet=data.GetPtrInt("AK8PuppinSubSDJet");
			if(AK8PuppinSubSDJet[0]!=2||AK8PuppinSubSDJet[1]!=2)continue;
			TClonesArray* AK8PuppijetP4 = (TClonesArray*) data.GetPtrTObject("AK8PuppijetP4");
			float*  AK8PuppijetCorrUncUp = data.GetPtrFloat("AK8PuppijetCorrUncUp"); 
			float*  AK8PuppijetCorrUncDown = data.GetPtrFloat("AK8PuppijetCorrUncDown"); 
			TLorentzVector* thisJet ,* thatJet;
			
			
			thisJet=(TLorentzVector*)AK8PuppijetP4->At(0);
			thatJet=(TLorentzVector*)AK8PuppijetP4->At(1);
			
			//3. Pt 
			if(thisJet->Pt()>99998 ||thatJet->Pt()>99998 )continue;
			if(thisJet->Pt()<300)continue;
			if(thatJet->Pt()<300)continue;
			nPass[3]++;
			//4tightId-----------------------------------------
			vector<bool>    &AK8PuppijetPassIDTight = *((vector<bool>*) data.GetPtr("AK8PuppijetPassIDTight"));
			if(AK8PuppijetPassIDTight[0]==0)continue;
			if(AK8PuppijetPassIDTight[1]==0)continue;
			Float_t*  AK8PuppijetCEmEF = data.GetPtrFloat("AK8PuppijetCEmEF");
			Float_t*  AK8PuppijetMuoEF = data.GetPtrFloat("AK8PuppijetMuoEF");
			if(AK8PuppijetMuoEF[0]>0.8)continue;
			if(AK8PuppijetCEmEF[0]>0.9)continue;
			if(AK8PuppijetMuoEF[1]>0.8)continue;
			if(AK8PuppijetCEmEF[1]>0.9)continue;
			nPass[4]++;
			//5. Eta-----------------------------------------
			if(fabs(thisJet->Eta())>2.4)continue;
			if(fabs(thatJet->Eta())>2.4)continue;
			nPass[5]++;
			//6. DEta-----------------------------------------
			float dEta = fabs(thisJet->Eta()-thatJet->Eta());
			if(dEta>1.3)continue;
			nPass[6]++;
			//7. Mjj-----------------------------------------
			//float mjjRed = (*thisJet+*thatJet).M()+250-thisJet->M()-thatJet->M();
			//if(mjjRed<1000)continue;
			nPass[7]++;
			//8. fatjetPRmassL2L3Corr-----------------------------------------
			nPass[8]++;
			//9.-----------------------------------------
		
			
    
			Float_t*  AK8Puppijet_DoubleSV = data.GetPtrFloat("AK8Puppijet_DoubleSV");
			
			
			int looseStat=-1;
			int tightStat=-1;
			int tlStat=-1;
			
			if(AK8Puppijet_DoubleSV[0]>0.3 && AK8Puppijet_DoubleSV[1]>0.3)looseStat=0;
			else if(AK8Puppijet_DoubleSV[0]>0.3 && AK8Puppijet_DoubleSV[1]<0.3)looseStat=1;
			else if(AK8Puppijet_DoubleSV[0]<0.3 && AK8Puppijet_DoubleSV[1]>0.3)looseStat=2;
			else looseStat=3;
			
			if(AK8Puppijet_DoubleSV[0]>0.8 && AK8Puppijet_DoubleSV[1]>0.8)tightStat=0;
			else if(AK8Puppijet_DoubleSV[0]>0.8 && AK8Puppijet_DoubleSV[1]<0.8)tightStat=1;
			else if(AK8Puppijet_DoubleSV[0]<0.3 && AK8Puppijet_DoubleSV[1]>0.8)tightStat=2;
			else if(AK8Puppijet_DoubleSV[0]<0.3 && AK8Puppijet_DoubleSV[1]<0.8)tightStat=3;
			else tightStat=-1;
			
			if(AK8Puppijet_DoubleSV[0]>0.8 && AK8Puppijet_DoubleSV[1]>0.3)tlStat=0;
			else if(AK8Puppijet_DoubleSV[0]>0.8 && AK8Puppijet_DoubleSV[1]<0.3)tlStat=1;
			else if(AK8Puppijet_DoubleSV[0]<0.3 && AK8Puppijet_DoubleSV[1]>0.3)tlStat=2;
			else if(AK8Puppijet_DoubleSV[0]<0.3 && AK8Puppijet_DoubleSV[1]<0.3)tlStat=3;
			else tlStat=-1;
			
			double varTemp[2];
			
			Float_t*  AK8PuppijetSDmass = data.GetPtrFloat("AK8PuppijetSDmass");
			
			Int_t* AK8Puppijet_nSV=data.GetPtrInt("AK8Puppijet_nSV");
			vector<float>   *AK8Puppijet_SVMass  =  data.GetPtrVectorFloat("AK8Puppijet_SVMass");
			int nEle= data.GetInt("nEle");
			int nMu=data.GetInt("nMu");
			Float_t*  AK8PuppijetEleEF = data.GetPtrFloat("AK8PuppijetEleEF");
			//Float_t*  AK8PuppijetMuoEF = data.GetPtrFloat("AK8PuppijetMuoEF");
			Int_t* AK8PuppijetCMulti=data.GetPtrInt("AK8PuppijetCMulti");
			Int_t* AK8PuppijetEleMulti=data.GetPtrInt("AK8PuppijetEleMulti");
			Int_t* AK8PuppijetMuoMulti=data.GetPtrInt("AK8PuppijetMuoMulti");
			
			for(int i=0; i<2;i++){
		
				TLorentzVector* thisAK8Jet ;
				
				if(i==1)thisAK8Jet=thatJet;
				else thisAK8Jet=thisJet;
				
				
				pt_AK8MatchedToHbb=thisAK8Jet->Pt();
				eta_AK8MatchedToHbb=thisAK8Jet->Eta();
				nsv_AK8MatchedToHbb=AK8Puppijet_nSV[i];
				sv0mass_AK8MatchedToHbb=AK8Puppijet_SVMass[i][0];
				sv1mass_AK8MatchedToHbb=AK8Puppijet_SVMass[i][1];
				nmu_AK8MatchedToHbb=AK8PuppijetMuoMulti[i];
				nel_AK8MatchedToHbb=AK8PuppijetEleMulti[i];
				muenfr_AK8MatchedToHbb=AK8PuppijetMuoEF[i];
				nch_AK8MatchedToHbb=AK8PuppijetCMulti[i];
				emenfr_AK8MatchedToHbb=AK8PuppijetEleEF[i];
				spec1=nVtx;
				spec2=AK8PuppijetSDmass[i];
				Float_t val ;
				for (Int_t ih=0; ih<nhists; ih++) {
				TString title = hists[ih]->GetTitle();
				val= (reader->EvaluateRegression( title ))[0];
				}
				varTemp[i]=val;
			}
			
			double PUPPIweight[2]={0};
			PUPPIweight[0]=getPUPPIweight(thisJet->Pt(),thisJet->Eta());
			PUPPIweight[1]=getPUPPIweight(thatJet->Pt(),thatJet->Eta());
			
			double PUPPIweightThea[2]={0};
			PUPPIweightThea[0]=getPUPPIweight_o(thisJet->Pt(),thisJet->Eta());
			PUPPIweightThea[1]=getPUPPIweight_o(thatJet->Pt(),thatJet->Eta());
			
			
			TLorentzVector  thisJetReg, thatJetReg;
			thisJetReg=(*thisJet)*varTemp[0];
			thatJetReg=(*thatJet)*varTemp[1];
			double PUPPIweightOnRegressed[2]={0};			
			PUPPIweightOnRegressed[0]=getPUPPIweightOnRegressed(thisJetReg.Pt(),thisJetReg.Eta());
			PUPPIweightOnRegressed[1]=getPUPPIweightOnRegressed(thatJetReg.Pt(),thatJetReg.Eta());
			
			double mass_j0=0,mass_j1=0;
			
			for(int i=0;i<nMass;i++){
				if(i==0){
					mass_j0=AK8PuppijetSDmass[0]*PUPPIweightThea[0];
					mass_j1=AK8PuppijetSDmass[1]*PUPPIweightThea[1];
				}
				else if (i==1){
					mass_j0=AK8PuppijetSDmass[0]*PUPPIweight[0];
					mass_j1=AK8PuppijetSDmass[1]*PUPPIweight[1];
				}
				else {
					mass_j0=AK8PuppijetSDmass[0]*varTemp[0]*PUPPIweightOnRegressed[0];
					mass_j1=AK8PuppijetSDmass[1]*varTemp[1]*PUPPIweightOnRegressed[1];
				}
				
				if(mass_j1<50)continue;
				if(mass_j0>100 && mass_j0<145)continue;
				
				//cout<<mass_j0<<","<<mass_j1<<",stat="<<looseStat<<","<<tightStat<<endl;
				
				th2[i][looseStat][1]->Fill(mass_j0);
				if(tightStat>=0)th3[i][tightStat][1]->Fill(mass_j0);
				if(tlStat>=0)th4[i][tlStat][1]->Fill(mass_j0);
			}
			
			
			Float_t*  AK8PuppijetTau1 = data.GetPtrFloat("AK8PuppijetTau1");
			Float_t*  AK8PuppijetTau2 = data.GetPtrFloat("AK8PuppijetTau2");
			double puppiTau21[2];
			puppiTau21[0]=(AK8PuppijetTau2[0]/AK8PuppijetTau1[0]),puppiTau21[1]=(AK8PuppijetTau2[1]/AK8PuppijetTau1[1]);
			
			if(puppiTau21[0]>0.6 && puppiTau21[1]<0.6){
				for(int i=0;i<nMass;i++){
				if(i==0){
					mass_j0=AK8PuppijetSDmass[0]*PUPPIweightThea[0];
					mass_j1=AK8PuppijetSDmass[1]*PUPPIweightThea[1];
				}
				else if (i==1){
					mass_j0=AK8PuppijetSDmass[0]*PUPPIweight[0];
					mass_j1=AK8PuppijetSDmass[1]*PUPPIweight[1];
				}
				else {
					mass_j0=AK8PuppijetSDmass[0]*varTemp[0]*PUPPIweightOnRegressed[0];
					mass_j1=AK8PuppijetSDmass[1]*varTemp[1]*PUPPIweightOnRegressed[1];
				}
				
				if(mass_j1<50)continue;
				if(mass_j0>100 && mass_j0<145)continue;
				
				
				th2[i][looseStat][2]->Fill(mass_j0);
				if(tightStat>=0)th3[i][tightStat][2]->Fill(mass_j0);
				if(tlStat>=0)th4[i][tlStat][2]->Fill(mass_j0);
			}
			}
			
			if(puppiTau21[0]>0.6 || puppiTau21[1]>0.6) continue;
			
			
			for(int i=0;i<nMass;i++){
				if(i==0){
					mass_j0=AK8PuppijetSDmass[0]*PUPPIweightThea[0];
					mass_j1=AK8PuppijetSDmass[1]*PUPPIweightThea[1];
				}
				else if (i==1){
					mass_j0=AK8PuppijetSDmass[0]*PUPPIweight[0];
					mass_j1=AK8PuppijetSDmass[1]*PUPPIweight[1];
				}
				else {
					mass_j0=AK8PuppijetSDmass[0]*varTemp[0]*PUPPIweightOnRegressed[0];
					mass_j1=AK8PuppijetSDmass[1]*varTemp[1]*PUPPIweightOnRegressed[1];
				}
				
				if(mass_j1<50)continue;
				if(mass_j0>100 && mass_j0<145)continue;
				
				
				th2[i][looseStat][0]->Fill(mass_j0);
				if(tightStat>=0)th3[i][tightStat][0]->Fill(mass_j0);
				if(tlStat>=0)th4[i][tlStat][0]->Fill(mass_j0);
			}
			
			
		}
	}	
	
	for(int i=0;i<10;i++)cout<<"npass["<<i<<"]="<<nPass[i]<<endl;
   

	TFile* outFile;//= new TFile(Form("PFRatio/%s.root",st2.data()),"recreate");
	outFile= new TFile(Form("PFRatio/%s/%d.root",st2.data(),wMs),"recreate");
	for(int i=0;i<nMass;i++){
		for(int j=0;j<nCat;j++){
			for(int k=0;k<3;k++){
				th2[i][j][k]->Write();
				th3[i][j][k]->Write();
				th4[i][j][k]->Write();
			}
		}
	}
	outFile->Close();
	
	for(int i=0;i<nMass;i++){
		for(int j=0;j<nCat;j++){
			for(int k=0;k<2;k++){
				delete th2[i][j][k];
				delete th3[i][j][k];
				delete th4[i][j][k];
			}
		}
	}
  
   delete reader;
    
   
}

void HH4bRegCategory(int a,int b){

	string st1[40]={
		"/data7/chchen/AK8subjetSDRawFactorNov2016/JetHT/B/skimmed/NCUGlobalTuples_",
		"/data7/chchen/AK8subjetSDRawFactorNov2016/JetHT/C/skimmed/NCUGlobalTuples_",
		"/data7/chchen/AK8subjetSDRawFactorNov2016/JetHT/D/skimmed/NCUGlobalTuples_",
		"/data7/chchen/AK8subjetSDRawFactorNov2016/JetHT/E/skimmed/NCUGlobalTuples_",
		"/data7/chchen/AK8subjetSDRawFactorNov2016/JetHT/F/skimmed/NCUGlobalTuples_",
		"/data7/chchen/AK8subjetSDRawFactorNov2016/JetHT/G/skimmed/NCUGlobalTuples_",
		"/data7/chchen/AK8subjetSDRawFactorNov2016/JetHT/H/skimmed/NCUGlobalTuples_",
	};
	string  fileName[40]={
	"dataB",
	"dataC",
	"dataD",
	"dataE",
	"dataF",
	"dataG",
	"dataH",
	};
	int aa[40]={1045,348,584,497,361,854,24};
	cout<<st1[a]<<b<<".root"<<endl;
	TMVARegressionApplication(b,b+1,st1[a],fileName[a]);	
	
}