#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TLorentzVector.h"
#include "TStopwatch.h"
#include "TStyle.h"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/Reader.h"
#include "ntupInfo/bTag.C"
#include "ntupInfo/bTagG.C"
#include "ntupInfo/minibtag.C"

#include "TMVAMulticlass.C"
#include "tools/variable.h"

using std::map;
using std::string;
using std::cerr;
using namespace TMVA;

TString ptVarName="pt";
TString etaVarName="eta";

//control bools here
const bool doPreselection = 0;
const bool drawPtEta      = 0;
const bool checkInputs    = 0;
const bool drawOutput     = 0;
const bool useSingleTeTree= 0;
const bool doTesting      = 1;

int g_binsConf4Weight = 3;

TString g_sigBkg="buc";//b for sig, u and c for bkg
TString g_weightType;
TString g_weightExp;
bool g_noUse_u;
bool g_use_c;
bool g_multiClassification = 1;
bool g_useMaxStat=0;
bool g_mixSamples=true;
bool g_doInclusiveTraining=false;

bool g_correctFraction=1;
float g_weight4=1.;
float g_weight0=1.;
int isGood_flag;

//Basic histograms
TH1D *b_pt   , *c_pt   , *u_pt;
TH1D *b_eta  , *c_eta  , *u_eta;
TH2F *b_pteta, *c_pteta, *u_pteta;

//output pdfs for multiclassification
TH1F *b_pb_tr, *b_pu_tr, *b_pc_tr;
TH1F *u_pb_tr, *u_pu_tr, *u_pc_tr;
TH1F *c_pb_tr, *c_pu_tr, *c_pc_tr;

TH1F *b_pb_te, *b_pu_te, *b_pc_te;
TH1F *u_pb_te, *u_pu_te, *u_pc_te;
TH1F *c_pb_te, *c_pu_te, *c_pc_te;

//output pdfs for binary classification
TH1F *b_bdt_tr, *u_bdt_tr, *c_bdt_tr;
TH1F *b_bdt_te, *u_bdt_te, *c_bdt_te;

//weight histograms
TH1F *b_weight_pteta, *c_weight_pteta;
TH1F *u_weight_pteta; // FLS

TMVA::Reader *g_reader=0;
bool initializeDONE=false;

map<TString,variable> g_map_inputVars;

vector<float> g_inputVariablesTMVA; //for TMVA, must be float
vector<TString> g_s_inputVariables;
bool g_generateTrees=true;
const TString g_mvaString= "BDTG";

TString g_trainName;
float g_jvtCut=-1, g_jvfCut=-2;
unsigned g_puCut=3;
bool g_requireTruthMatch=0;
bool g_apply_cWeight=1;
// FLS : for hybrid tuning
bool g_doHybridTuning = false;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initializeReader() {//void initializeReader(TString mvaName) {
    if (initializeDONE) return;
    TString varFileName="weights/"+g_trainName+".varlist";//TString varFileName="weights/"+mvaName+".varlist";
    ifstream ifs(varFileName.Data());
    string aLine;
    vector<TString> varlist,vartype;
    if (ifs.fail()) {
        cerr<<"Failure when reading a file: "<<varFileName<<endl;
        return;
    }
    else {
        while (getline(ifs,aLine)) {
            //cout<<aLine<<endl;
            TString ts_aLine=aLine.data();
            if (ts_aLine.BeginsWith("#")) continue;
            TString var =aLine.substr(0,aLine.find(","));
            TString type=aLine.substr(aLine.size()-1,aLine.size());
            //cout<<var<<"\t"<<type<<endl;
            varlist.push_back(var);
            vartype.push_back(type);
            //commaVariablesList+="(double)";
            //commaVariablesList+=var;
            //commaVariablesList+=",";
            variable tmp;
            tmp.type_=type;
            g_map_inputVars[var]=tmp;
        }
    }
    g_s_inputVariables=varlist;

    //commaVariablesList=commaVariablesList.substr(0,commaVariablesList.length()-1);

    g_reader = new TMVA::Reader( "!Color:!Silent" );

    TString path2xml = "weights/"+g_trainName+"_"+g_mvaString+".weights.xml";//TString path2xml = "weights/"+mvaName+"_"+g_mvaString+".weights.xml";  //for training and testing+eval
    //TString path2xml = "weights/MV2_ATHv40OKcrossTrain_jvt0641_puCut1_tm0_stat1000k_cStat500k_BdtGrad_bin_cuts200_depth30_nTrees1000_MNS005_c15_BDTG.weights.xml";

    g_inputVariablesTMVA.resize(varlist.size());
    //s_nVars=TString::Format("%d,",varlist.size()).Data();

    if (drawOutput) {
        for (unsigned ivar=0; ivar<varlist.size(); ivar++) {
            g_reader -> AddVariable ( varlist.at(ivar)     , &(g_inputVariablesTMVA.at(ivar))      );
        }  // g_reader -> AddVariable ( ""                , &      );

        std::cout<<"Reading xml file from \t"<<path2xml<<std::endl
            <<"With calling string \t"<<g_mvaString<<std::endl;

        g_reader -> BookMVA(g_mvaString, path2xml);    //g_reader[i] -> BookMVA(methodName,path2xml);
    }

    initializeDONE=true; 
    return;
}

const bool g_debugmode=1;
int  g_numOut   =0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<float> evalMultiClass(vector<double> inputs) {//vector<float> evalMultiClass(TString mvaName,vector<double> inputs) {

    // if (inputs.size()!=nVars) {
    //   cerr<<"Number of input variables is inconsistent to initialization.Aborting.."<<endl;
    //   exit(1);
    // }

    for (unsigned i=0; i<inputs.size(); i++) {
        g_inputVariablesTMVA[i] = inputs[i];
        if (g_debugmode and g_numOut<100) cout<<g_s_inputVariables[i]<<"= "<<inputs[i]<<"\t";
    }

    vector<float> outputs;
    if (g_reader) {
        //cout<<"g_multiClassification= "<<g_multiClassification <<endl;  exit(1);
        if (!g_multiClassification) {//binary-class
            outputs.push_back(g_reader->EvaluateMVA( g_mvaString ) );//if (g_mvaString.Contains("bin")) outputs.push_back(g_reader->EvaluateMVA( g_mvaString ) );
            if (g_debugmode and g_numOut<100 ) cout<<"BDT= "<<outputs[0]<<endl;
        }
        else {//multiclass
            outputs = g_reader->EvaluateMulticlass( g_mvaString );
            if (g_debugmode and g_numOut<100 ) cout<<"pb+pu+pc= "<<outputs[0]<<"+"<<outputs[1]<<"+"<<outputs[2]<<"= "<<outputs[0]+outputs[1]+outputs[2]<<endl;
        }
    }
    else {
        cerr<<"MVA tool isn't initilized yet!! Aborting..."<<endl;
        exit(1);
    }

    g_numOut++;
    return outputs;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TString var4weight="PtEta";
float rWeight(double pt, double eta, int label) {

    //pt&eta reweighting
    // reweight to light
    //if (label==0) return g_weight0;// return 1.0;
    // reweight to b
    if (label==5) return g_weight0;// return 1.0;

    const float absEta= fabs(eta);

    //float num= u_pteta->GetBinContent(u_pteta->FindBin(pt/1000.,absEta)); //Kazuya default
    float num= b_pteta->GetBinContent(b_pteta->FindBin(pt/1000.,absEta)); //Kazuya default

    float den=1.0; //Kazuya default

    if (var4weight=="PtEta") {
        if      (label==5) den=b_pteta->GetBinContent(b_pteta->FindBin(pt/1000.,absEta));  //Kazuya defauly
        else if (label==4) den=c_pteta->GetBinContent(c_pteta->FindBin(pt/1000.,absEta)); //Kazuya default
        else if (label==0) den=u_pteta->GetBinContent(u_pteta->FindBin(pt/1000.,absEta)); //Kazuya default

    }
    else if (var4weight=="Pt") {
        if      (label==5) den=b_pt->GetBinContent(b_pt->FindBin(pt/1000.)); //Kazuya default
        else if (label==4) den=c_pt->GetBinContent(c_pt->FindBin(pt/1000.));  //Kazuya default
        else if (label==0) den=u_pt->GetBinContent(u_pt->FindBin(pt/1000.));  //Kazuya default

    }
    float weight=den>0 ? num/den : 0.;

    if     (label==5)b_weight_pteta->Fill(weight);
    else if(label==4)c_weight_pteta->Fill(weight);
    else if(label==0)u_weight_pteta->Fill(weight); // FLS
    else {
        cerr<<"label= "<<label<<"!!! Aborting..."<<endl; exit(1);
    }

    if (label==4) weight*=g_weight4;

    //cout<<"pt, eta, label= "<<pt/1000.<<"\t"<<eta<<"\t"<<label<<"\t w= "<<weight<<endl;  
    if (weight<0) {
        cerr<<"rWeight(): negative weights detected: weight= "<<weight<<", aborting..."<<endl;
        exit(1);
    }
    if (std::isnan(weight) or std::isinf(weight) or weight!=weight) {
        cerr<<"rWeight(): weight is nan or inf!! weight= "<<weight<<endl;
        exit(1);
    }

    return weight;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float fWeight(double pt, double eta, int label) {

    //pt/eta reweighting (FLATTENING WEIGHT)

    const float absEta= fabs(eta);

    float den=1.0;
    if (var4weight=="PtEta") {
        if      (label==5) den=b_pteta->GetBinContent(b_pteta->FindBin(pt/1e3,absEta));
        else if (label==4) den=c_pteta->GetBinContent(c_pteta->FindBin(pt/1e3,absEta));
        else if (label==0) den=u_pteta->GetBinContent(u_pteta->FindBin(pt/1e3,absEta));
    }
    else if (var4weight=="Pt") {
        if      (label==5) den=b_pt->GetBinContent(b_pt->FindBin(pt/1e3));
        else if (label==4) den=c_pt->GetBinContent(c_pt->FindBin(pt/1e3));
        else if (label==0) den=u_pt->GetBinContent(u_pt->FindBin(pt/1e3));
    }

    float weight=den>0 ? 1.0/den : 0.;//if (label!=0) weight *= 0.5;
    if      (label==0) weight *= g_weight0;
    else if (label==4) weight *= g_weight4;

    return weight;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float cWeight(float ip2_pu, float jf_sig3, float sv1_mass) {

    //down-weight bad jets
    bool ip2_isvalid =  0<ip2_pu and ip2_pu<=1;
    bool sv1_isvalid = sv1_mass>0; 
    bool jf_isvalid  = jf_sig3>0;  





    float weight = 1.0;
    if(!ip2_isvalid and !sv1_isvalid and !jf_isvalid) weight=1e-6; //new downgrading procedure




    if (weight<0) {
        cerr<<"cWeight(): negative weights detected: weight= "<<weight<<", aborting..."<<endl;
        exit(1);
    }
    if (std::isnan(weight) or std::isinf(weight) or weight!=weight) {
        cerr<<"cWeight(): weight is nan or inf!! weight= "<<weight<<endl;
        exit(1);
    }
    if (weight==1) isGood_flag=1;
    else isGood_flag=0;


    return weight;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void check_input_values(minibtag* minibtag) {

    if( std::isnan(minibtag->pt       ) or std::isinf(minibtag->pt       ) ) {cerr<<"nan or inf detected: pt       = "<<minibtag->pt       <<endl; exit(1);}
    if( std::isnan(minibtag->eta      ) or std::isinf(minibtag->eta      ) ) {cerr<<"nan or inf detected: eta      = "<<minibtag->eta      <<endl; exit(1);}
    if( std::isnan(minibtag->ip2      ) or std::isinf(minibtag->ip2      ) ) {cerr<<"nan or inf detected: ip2      = "<<minibtag->ip2      <<endl; exit(1);}
    if( std::isnan(minibtag->ip2_c    ) or std::isinf(minibtag->ip2_c    ) ) {cerr<<"nan or inf detected: ip2_c    = "<<minibtag->ip2_c    <<endl; exit(1);}
    if( std::isnan(minibtag->ip2_cu   ) or std::isinf(minibtag->ip2_cu   ) ) {cerr<<"nan or inf detected: ip2_cu   = "<<minibtag->ip2_cu   <<endl; exit(1);}
    if( std::isnan(minibtag->ip3      ) or std::isinf(minibtag->ip3      ) ) {cerr<<"nan or inf detected: ip3      = "<<minibtag->ip3      <<endl; exit(1);}
    if( std::isnan(minibtag->ip3_c    ) or std::isinf(minibtag->ip3_c    ) ) {cerr<<"nan or inf detected: ip3_c    = "<<minibtag->ip3_c    <<endl; exit(1);}
    if( std::isnan(minibtag->ip3_cu   ) or std::isinf(minibtag->ip3_cu   ) ) {cerr<<"nan or inf detected: ip3_cu   = "<<minibtag->ip3_cu   <<endl; exit(1);}
    if( std::isnan(minibtag->sv1ntkv  ) or std::isinf(minibtag->sv1ntkv  ) ) {cerr<<"nan or inf detected: sv1ntkv  = "<<minibtag->sv1ntkv  <<endl; exit(1);}
    if( std::isnan(minibtag->sv1n2tv  ) or std::isinf(minibtag->sv1n2tv  ) ) {cerr<<"nan or inf detected: sv1n2tv  = "<<minibtag->sv1n2tv  <<endl; exit(1);}
    if( std::isnan(minibtag->sv1mass  ) or std::isinf(minibtag->sv1mass  ) ) {cerr<<"nan or inf detected: sv1mass  = "<<minibtag->sv1mass  <<endl; exit(1);}
    if( std::isnan(minibtag->sv1efrc  ) or std::isinf(minibtag->sv1efrc  ) ) {cerr<<"nan or inf detected: sv1efrc  = "<<minibtag->sv1efrc  <<endl; exit(1);}
    if( std::isnan(minibtag->sv1Lxy   ) or std::isinf(minibtag->sv1Lxy   ) ) {cerr<<"nan or inf detected: sv1Lxy   = "<<minibtag->sv1Lxy   <<endl; exit(1);}
    if( std::isnan(minibtag->sv1L3d   ) or std::isinf(minibtag->sv1L3d   ) ) {cerr<<"nan or inf detected: sv1L3d   = "<<minibtag->sv1L3d   <<endl; exit(1);}
    if( std::isnan(minibtag->sv1sig3  ) or std::isinf(minibtag->sv1sig3  ) ) {cerr<<"nan or inf detected: sv1sig3  = "<<minibtag->sv1sig3  <<endl; exit(1);}
    if( std::isnan(minibtag->sv1dR    ) or std::isinf(minibtag->sv1dR    ) ) {cerr<<"nan or inf detected: sv1dR    = "<<minibtag->sv1dR    <<endl; exit(1);}
    if( std::isnan(minibtag->jf_n2tv  ) or std::isinf(minibtag->jf_n2tv  ) ) {cerr<<"nan or inf detected: jf_n2tv  = "<<minibtag->jf_n2tv  <<endl; exit(1);}
    if( std::isnan(minibtag->jf_ntrkv ) or std::isinf(minibtag->jf_ntrkv ) ) {cerr<<"nan or inf detected: jf_ntrkv = "<<minibtag->jf_ntrkv <<endl; exit(1);}
    if( std::isnan(minibtag->jf_nvtx  ) or std::isinf(minibtag->jf_nvtx  ) ) {cerr<<"nan or inf detected: jf_nvtx  = "<<minibtag->jf_nvtx  <<endl; exit(1);}
    if( std::isnan(minibtag->jf_nvtx1t) or std::isinf(minibtag->jf_nvtx1t) ) {cerr<<"nan or inf detected: jf_nvtx1t= "<<minibtag->jf_nvtx1t<<endl; exit(1);}
    if( std::isnan(minibtag->jf_mass  ) or std::isinf(minibtag->jf_mass  ) ) {cerr<<"nan or inf detected: jf_mass  = "<<minibtag->jf_mass  <<endl; exit(1);}
    if( std::isnan(minibtag->jf_efrc  ) or std::isinf(minibtag->jf_efrc  ) ) {cerr<<"nan or inf detected: jf_efrc  = "<<minibtag->jf_efrc  <<endl; exit(1);}
    if( std::isnan(minibtag->jf_sig3  ) or std::isinf(minibtag->jf_sig3  ) ) {cerr<<"nan or inf detected: jf_sig3  = "<<minibtag->jf_sig3  <<endl; exit(1);}
    if( std::isnan(minibtag->jf_dR    ) or std::isinf(minibtag->jf_dR    ) ) {cerr<<"nan or inf detected: jf_dR    = "<<minibtag->jf_dR    <<endl; exit(1);}

    if (std::isnan(minibtag->width)          || std::isinf(minibtag->width)          ) { cerr << "nan or inf detected: width          = " << minibtag->width << endl; exit(1); }
    if (std::isnan(minibtag->n_trk_sigd0cut) || std::isinf(minibtag->n_trk_sigd0cut) ) { cerr << "nan or inf detected: n_trk_sigd0cut = " << minibtag->n_trk_sigd0cut << endl; exit(1); }
    //if (std::isnan(minibtag->trk3_d0sig)     || std::isinf(minibtag->trk3_d0sig)     ) { cerr << "nan or inf detected: trk3_d0sig     = " << minibtag->trk3_d0sig << endl; exit(1); }
    if (std::isnan(minibtag->trk3_z0sig)     || std::isinf(minibtag->trk3_z0sig)     ) { cerr << "nan or inf detected: trk3_z0sig     = " << minibtag->trk3_z0sig << endl; exit(1); }
    if (std::isnan(minibtag->sv_scaled_efc)  || std::isinf(minibtag->sv_scaled_efc)  ) { cerr << "nan or inf detected: sv_scaled_efc  = " << minibtag->sv_scaled_efc << endl; exit(1); }
    if (std::isnan(minibtag->jf_scaled_efc)  || std::isinf(minibtag->jf_scaled_efc)  ) { cerr << "nan or inf detected: jf_scaled_efc  = " << minibtag->jf_scaled_efc << endl; exit(1); }
    return;

}

void copyVars(minibtag *tobeFilled, minibtag *source) {
    /*** some relevant variables ***/
    tobeFilled->label     = source->label     ;
    tobeFilled->phi       = source->phi       ;
    tobeFilled->m         = source->m         ;
    tobeFilled->pt_calib  = source->pt_calib  ;
    tobeFilled->eta_calib = source->eta_calib ;
    tobeFilled->pt_uCalib = source->pt_uCalib ;
    tobeFilled->eta_uCalib= source->eta_uCalib;
    tobeFilled->truthMatch= source->truthMatch;
    tobeFilled->JVT       = source->JVT       ;
    tobeFilled->JVF       = source->JVF       ;
    tobeFilled->mcchannel = source->mcchannel ;
    tobeFilled->muAvg     = source->muAvg     ;
    tobeFilled->isGood    = source->isGood    ;
    tobeFilled->ip2_pu    = source->ip2_pu    ;
    tobeFilled->ip2_pb    = source->ip2_pb    ;
    tobeFilled->ip2_pc    = source->ip2_pc    ;
    tobeFilled->ip3_pu    = source->ip3_pu    ;
    tobeFilled->ip3_pb    = source->ip3_pb    ;
    tobeFilled->ip3_pc    = source->ip3_pc    ;
    tobeFilled->mv2c00    = source->mv2c00;
    tobeFilled->mv2c10    = source->mv2c10;
    tobeFilled->mv2c20    = source->mv2c20;
    tobeFilled->mv2m_pb   = source->mv2m_pb;
    tobeFilled->mv2m_pu   = source->mv2m_pu;
    tobeFilled->mv2m_pc   = source->mv2m_pc;
    /*** Actual MV2 input ***/
    tobeFilled->pt        = source->pt        ;
    tobeFilled->eta       = source->eta       ;
    tobeFilled->ip2       = source->ip2       ;
    tobeFilled->ip2_c     = source->ip2_c     ;
    tobeFilled->ip2_cu    = source->ip2_cu    ;
    tobeFilled->ip3       = source->ip3       ;
    tobeFilled->ip3_c     = source->ip3_c     ;
    tobeFilled->ip3_cu    = source->ip3_cu    ;
    tobeFilled->sv1ntkv   = source->sv1ntkv   ;
    tobeFilled->sv1n2tv   = source->sv1n2tv   ;
    tobeFilled->sv1mass   = source->sv1mass   ;
    tobeFilled->sv1efrc   = source->sv1efrc   ;
    tobeFilled->sv1Lxy    = source->sv1Lxy    ;
    tobeFilled->sv1L3d    = source->sv1L3d    ;
    tobeFilled->sv1sig3   = source->sv1sig3   ;
    tobeFilled->sv1dR     = source->sv1dR     ;
    tobeFilled->jf_n2tv   = source->jf_n2tv   ;
    tobeFilled->jf_ntrkv  = source->jf_ntrkv  ;
    tobeFilled->jf_nvtx   = source->jf_nvtx   ;
    tobeFilled->jf_nvtx1t = source->jf_nvtx1t ;
    tobeFilled->jf_mass   = source->jf_mass   ;
    tobeFilled->jf_efrc   = source->jf_efrc   ;
    tobeFilled->jf_sig3   = source->jf_sig3   ;
    tobeFilled->jf_dR     = source->jf_dR     ;

    tobeFilled->width = source->width;
    tobeFilled->n_trk_sigd0cut = source->n_trk_sigd0cut;
    tobeFilled->trk3_d0sig = source->trk3_d0sig;
    tobeFilled->trk3_z0sig = source->trk3_z0sig;
    tobeFilled->sv_scaled_efc = source->sv_scaled_efc;
    tobeFilled->jf_scaled_efc = source->jf_scaled_efc;
    //added
    tobeFilled->aliveAfterOR = source->aliveAfterOR;
    //added
    //  tobeFilled->evtnum = source->evtnum;


    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TString g_jetCollection;
bool weightPDFexists=false;
map<int,unsigned> max_good;
map<int,unsigned> max_bad;
const bool debug=false;
//const unsigned teMax_inclsv=5e6;  
const unsigned teMax_inclsv=8e6;

void check_available_stat(TTree *tree) {
    if (!tree) {
        cerr<<"tree==0!! Aborting..."<<endl;
        exit(1);
    }
    TString treeName=tree->GetName();

    cout<<"prepareTtEventsFromEvt *** Checking available statistics. "<<endl;
    const TString ip2_pu_name = treeName=="bTag" ? g_jetCollection+"_IP2D_jet_ipxd_pu" : "jet_ip2d_pu"   ;
    const TString jf_sig3_name= treeName=="bTag" ? g_jetCollection+"_jet_jf_sig3d"     : "jet_jf_sig3d"  ;
    const TString sv1_m_name  = treeName=="bTag" ? g_jetCollection+"_SV1_jet_sv1_m"    : "jet_sv1_m"     ;
    const TString jvt_name    = treeName=="bTag" ? g_jetCollection+"_jet_jvt"          : "jet_JVT"       ;
    const TString jvf_name    = treeName=="bTag" ? g_jetCollection+"_jet_jvf"          : "jet_JVF"       ;
    const TString tm_name     = treeName=="bTag" ? g_jetCollection+"_jet_truthMatch"   : "jet_truthMatch";
    const TString label_name  = treeName=="bTag" ? g_jetCollection+"_jet_truthflav"    : "jet_truthflav" ;
    const TString pt_name     = treeName=="bTag" ? g_jetCollection+"_jet_cpt"          : "jet_pt"        ;
    const TString OR_name     = treeName=="bTag" ? g_jetCollection+"_jet_aliveAfterOR" : "jet_aliveAfterOR"        ;



    TString aeta_name= treeName=="bTag" ? g_jetCollection+"_jet_ceta" : "jet_eta" ;
    aeta_name="abs("+aeta_name+")";

    TString cut_str=pt_name+">20e3 && "+aeta_name+"<2.5 && "+OR_name+"==1";//basic cut
    TString pucut_str="";
    if (g_puCut) {
        if (g_puCut==1) //JetEtMiss recommendation
            pucut_str=" && ("+pt_name+">50e3 || "+aeta_name+">2.4 || "+jvt_name+TString::Format(">%.3f",g_jvtCut)+" && "+jvf_name+TString::Format(">%.1f",g_jvfCut)+")";
        else if (g_puCut==2) //apply if pt<50 GeV
            pucut_str=" && ("+pt_name+">50e3 || ("+jvt_name+TString::Format(">%.3f",g_jvtCut)+" && "+jvf_name+TString::Format(">%.1f",g_jvfCut)+") )";
        else if (g_puCut==3) //apply to all jets
            pucut_str=" && ("+jvt_name+TString::Format(">%.3f",g_jvtCut)+" && "+jvf_name+TString::Format(">%.1f",g_jvfCut)+")";



        cut_str+=pucut_str;
    }
    if(g_requireTruthMatch) cut_str+=" && "+tm_name;


    const TString cw_name     ="cWeight("+ip2_pu_name+","+jf_sig3_name+","+sv1_m_name+")==1"; //(old string)



    cut_str+=(g_doInclusiveTraining ? "" : " && "+cw_name);
    TString cut0=cut_str+" && "+label_name+"==0";
    TString cut4=cut_str+" && "+label_name+"==4";
    TStopwatch sw; sw.Start();


    tree->Draw(sv1_m_name+">>h_tmp0",cut0);
    tree->Draw(sv1_m_name+">>h_tmp4",cut4);


    cout<<"prepareTtEventsFromEvt *** Time elapsed for checking available stat: "; sw.Print();


    TH1F *h_tmp0= (TH1F*)gROOT->FindObject("h_tmp0");
    TH1F *h_tmp4= (TH1F*)gROOT->FindObject("h_tmp4");



    cout<<"htp0= "<<h_tmp0<<endl;
    cout<<"htp4= "<<h_tmp4<<endl;


    //take some margin
    cout<<"h_tmp0->GetEntries()= "<<h_tmp0->GetEntries()<<", h_tmp4->GetEntries()"<<"= "<<h_tmp4->GetEntries()<<endl;
    long maxStat0= ((long)((h_tmp0->GetEntries())/1000))*1000;
    long maxStat4= ((long)((h_tmp4->GetEntries())/1000))*1000;
    cout<<"maxStat0= "<<maxStat0<<", maxStat4= "<<maxStat4<<endl;

    const float cfrc=(float)max_good[4]/max_good[0];
    max_good[5]= maxStat0/2; max_good[105]= maxStat0/2;
    max_bad [5]= maxStat0/2; max_bad [105]= maxStat0/2;
    max_good[0]= maxStat0/2; max_good[100]= maxStat0/2;
    max_bad [0]= maxStat0/2; max_bad [100]= maxStat0/2;
    if (maxStat4/2<cfrc*maxStat0/2) {
        max_good[4]= maxStat4/2; max_good[104]= maxStat4/2;
        max_bad [4]= maxStat4/2; max_bad [104]= maxStat4/2;
    }
    else {
        max_good[4]= cfrc*maxStat0/2; max_good[104]= cfrc*maxStat0/2;
        max_bad [4]= cfrc*maxStat0/2; max_bad [104]= cfrc*maxStat0/2;
    }

    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
map<int, TTree*> prepareTtEventsFromEvt(TMVA::Factory *factory, TTree* tree) {

    initializeReader();//read input variables from list file

    TString treeName = tree->GetName();

    bTag  *bTag_treeObj = 0;  
    bTagG *bTagG_treeObj = 0;

    if (treeName == "bTag") { // do a string, not a ptr comparison here
        bTagG_treeObj = new bTagG(tree,g_jetCollection);
    }
    else {
        bTag_treeObj  = new bTag(tree);
    }

    minibtag *tr_bottom=0, *tr_charm=0, *tr_light=0, *te_bottom=0, *te_charm=0, *te_light=0;
    minibtag *te_inclsv=0;

    if (g_generateTrees) {
        tr_bottom = new minibtag("tr_bottom"); te_bottom = new minibtag("te_bottom");
        tr_charm  = new minibtag("tr_charm" ); te_charm  = new minibtag("te_charm" ); 
        tr_light  = new minibtag("tr_light" ); te_light  = new minibtag("te_light" ); 
        te_inclsv = new minibtag("minibtag" ); 
    }

    if (g_useMaxStat) check_available_stat(tree);

    map<int,minibtag*> map_minibtags;
    map_minibtags[  5]= tr_bottom;
    map_minibtags[  4]= tr_charm ;
    map_minibtags[  0]= tr_light ;
    map_minibtags[105]= te_bottom;
    map_minibtags[104]= te_charm ;
    map_minibtags[100]= te_light ;
    map_minibtags[ 15]= te_inclsv;//only for testing

    map<int,unsigned> counters_good;
    map<int,unsigned> counters_bad;
    counters_good[  5]=0; counters_bad[  5]=0;counters_good[  0]=0;counters_bad[  0]=0; counters_good[  4]=0; counters_bad[  4]=0;
    counters_good[105]=0; counters_bad[105]=0;counters_good[100]=0;counters_bad[100]=0; counters_good[104]=0; counters_bad[104]=0;
    unsigned teCounter_inclsv=0; bool te_inclsv_fill_triggered=false;

    unsigned warningCount=0;

    cout<<"prepareTtEventsFromEvt *** Collecting events: "<<endl
        <<"\t  b_trMax_good= "<<max_good[5]    <<",\t b_teMax_good= "<<max_good[105]
        <<",\t b_trMax_bad = "<<max_bad [5]    <<",\t b_teMax_bad = "<<max_bad [105]<<endl
        <<"\t  u_trMax_good= "<<max_good[0]    <<",\t u_teMax_good= "<<max_good[100]
        <<",\t u_trMax_bad = "<<max_bad [0]    <<",\t u_teMax_bad = "<<max_bad [100]<<endl
        <<"\t  c_trMax_good= "<<max_good[4]    <<",\t c_teMax_good= "<<max_good[104]
        <<",\t c_trMax_bad = "<<max_bad [4]    <<",\t c_teMax_bad = "<<max_bad [104]<<endl;

    cout<<"prepareTtEventsFromEvt *** Reading a tree: "<<treeName<<" with entries= "<<tree->GetEntries()<<endl;
    TStopwatch sw; sw.Start();

    /****** EVENT LOOP STARTS ******/
    for (unsigned ievt=0; ievt<tree->GetEntries(); ievt++) {

        int trash=treeName=="bTag" ? bTagG_treeObj ->GetEntry(ievt) : bTag_treeObj->GetEntry(ievt);
        int evtNum= treeName=="bTag" ? bTagG_treeObj->eventnb : bTag_treeObj->eventnb;
        int njets = treeName=="bTag" ? bTagG_treeObj->jet_pt->size() : bTag_treeObj->jet_pt->size();
        if (ievt<10) cout<<"event# "<<ievt<<": njets="<<njets<<endl;

        int mc_ch=-99; float mu_avg=-99.9;

        if(treeName != "bTag_TriggerJets") {
            mc_ch = treeName=="bTag" ? bTagG_treeObj->mcchan : bTag_treeObj->mcchan;
            mu_avg = treeName=="bTag" ? bTagG_treeObj->avgmu  : bTag_treeObj->avgmu;
        }

        //    int    mc_ch = treeName=="bTag" ? bTagG_treeObj->mcchan : bTag_treeObj->mcchan;
        //    float mu_avg = treeName=="bTag" ? bTagG_treeObj->avgmu  : bTag_treeObj->avgmu;



        /****** JET LOOP STARTS ******/
        for (unsigned ijet=0; (int)ijet<njets; ijet++) {

            // select only jets for hybrid tuning
            /*
               bool flag = (g_doHybridTuning && !bTag_treeObj->jet_ForHybrid->at(ijet));
               std::cout<<"DEBUG: RunNumber = "<<mc_ch<<" EvNumber = "<<evtNum<<" jet pt = "<<bTag_treeObj->jet_pt->at(ijet)/1000.<<" truth flav = "<<bTag_treeObj->jet_truthflav->at(ijet)<<" forHyb = "<<bTag_treeObj->jet_ForHybrid->at(ijet)<<" is used = "<<!flag<<std::endl;
               */
            if( g_doHybridTuning && !bTag_treeObj->jet_ForHybrid->at(ijet)) continue;


            //int ttIndex; //for cross validation
            const int ttIndex=evtNum%2;//0 to train, 1 to test when mixing is ON.
            //int ttIndex_initial=evtNum%2;//0 to train, 1 to test when mixing is ON (for cross validation).

            //%%%%%%%%%%%%%%%%%%%%ADDING CROSS-VALIDATION
            //if(ttIndex_initial==0) ttIndex=1; 
            //if(ttIndex_initial==1) ttIndex=0; 

            TLorentzVector v_jet, v_jet_uCalib, v_jet_calib;
            if(treeName=="bTag") {
                v_jet_uCalib.SetPtEtaPhiE( bTagG_treeObj->jet_pt ->at(ijet), bTagG_treeObj->jet_eta ->at(ijet), bTagG_treeObj->jet_phi ->at(ijet), bTagG_treeObj->jet_E ->at(ijet) );
                v_jet_calib .SetPtEtaPhiE( bTagG_treeObj->jet_cpt->at(ijet), bTagG_treeObj->jet_ceta->at(ijet), bTagG_treeObj->jet_cphi->at(ijet), bTagG_treeObj->jet_cE->at(ijet) );
            } else if(treeName=="bTag_TriggerJets") {
                v_jet_calib .SetPtEtaPhiM( bTag_treeObj->jet_pt      ->at(ijet), bTag_treeObj->jet_eta     ->at(ijet), bTag_treeObj->jet_phi-> \
                        at(ijet), bTag_treeObj->jet_m  ->at(ijet) );
                v_jet_uCalib .SetPtEtaPhiM( bTag_treeObj->jet_pt      ->at(ijet), bTag_treeObj->jet_eta     ->at(ijet), bTag_treeObj->jet_phi->	\
                        at(ijet), bTag_treeObj->jet_m  ->at(ijet) );
            } else {
                v_jet_calib .SetPtEtaPhiM( bTag_treeObj->jet_pt      ->at(ijet), bTag_treeObj->jet_eta     ->at(ijet), bTag_treeObj->jet_phi->at(ijet), bTag_treeObj->jet_m  ->at(ijet) );
                v_jet_uCalib.SetPtEtaPhiM( bTag_treeObj->jet_pt_orig ->at(ijet), bTag_treeObj->jet_eta_orig->at(ijet), bTag_treeObj->jet_phi->at(ijet), bTag_treeObj->jet_m  ->at(ijet) );
            }
            //v_jet = trainName.Contains("calib") ? v_jet_calib : v_jet_uCalib;
            v_jet = v_jet_uCalib;//used for training input

            float mv2c00 = -9.; float mv2c20 = -9.;
            int   label  = treeName=="bTag" ? bTagG_treeObj->jet_truthflav->at(ijet) : bTag_treeObj->jet_truthflav->at(ijet);
            //      float mv2c00 = treeName=="bTag" ? bTagG_treeObj->jet_mv2c00   ->at(ijet) : bTag_treeObj->jet_mv2c00->at(ijet);
            float mv2c10 = treeName=="bTag" ? bTagG_treeObj->jet_mv2c10   ->at(ijet) : bTag_treeObj->jet_mv2c10->at(ijet);
            //      float mv2c20 = treeName=="bTag" ? bTagG_treeObj->jet_mv2c20   ->at(ijet) : bTag_treeObj->jet_mv2c20->at(ijet);


            float mv2m_pb(-99.9), mv2m_pu(-99.9), mv2m_pc(-99.9);
            if(treeName != "bTag_TriggerJets") {
                mv2m_pb= treeName=="bTag" ? bTagG_treeObj->jet_mv2m_pb  ->at(ijet) : bTag_treeObj->jet_mv2m_pb->at(ijet);
                mv2m_pu= treeName=="bTag" ? bTagG_treeObj->jet_mv2m_pu  ->at(ijet) : bTag_treeObj->jet_mv2m_pu->at(ijet);
                mv2m_pc= treeName=="bTag" ? bTagG_treeObj->jet_mv2m_pc  ->at(ijet) : bTag_treeObj->jet_mv2m_pc->at(ijet);
            }
            float jvt(99.9), jvf(99.9); int truthMatch(-99);
            if(treeName != "bTag_TriggerJets") {
                jvt    = treeName=="bTag" ? bTagG_treeObj->jet_jvt      ->at(ijet) : bTag_treeObj->jet_JVT->at(ijet);
                jvf    = treeName=="bTag" ? bTagG_treeObj->jet_jvf      ->at(ijet) : bTag_treeObj->jet_JVF->at(ijet);
                truthMatch = treeName=="bTag" ? bTagG_treeObj->jet_truthMatch ->at(ijet) : bTag_treeObj->jet_truthMatch->at(ijet);
            }

            //      float mv2m_pb= treeName=="bTag" ? bTagG_treeObj->jet_mv2m_pb  ->at(ijet) : bTag_treeObj->jet_mv2m_pb->at(ijet);
            //      float mv2m_pu= treeName=="bTag" ? bTagG_treeObj->jet_mv2m_pu  ->at(ijet) : bTag_treeObj->jet_mv2m_pu->at(ijet);
            //      float mv2m_pc= treeName=="bTag" ? bTagG_treeObj->jet_mv2m_pc  ->at(ijet) : bTag_treeObj->jet_mv2m_pc->at(ijet);
            //      float jvt    = treeName=="bTag" ? bTagG_treeObj->jet_jvt      ->at(ijet) : bTag_treeObj->jet_JVT->at(ijet);
            //      float jvf    = treeName=="bTag" ? bTagG_treeObj->jet_jvf      ->at(ijet) : bTag_treeObj->jet_JVF->at(ijet);
            //      int   truthMatch = treeName=="bTag" ? bTagG_treeObj->jet_truthMatch ->at(ijet) : bTag_treeObj->jet_truthMatch->at(ijet);

            bool apply_pu_cut=0;
            if (g_puCut==0) {//Not applying to any jets
                apply_pu_cut=0;
            }
            else if (g_puCut==1) {//JetEtMiss Recommendation
                if(v_jet_calib.Pt()/1e3>50) apply_pu_cut=0;
                else {
                    if(fabs(v_jet_calib.Eta())>2.4) apply_pu_cut=0;
                    else                            apply_pu_cut=1;
                }
            }
            else if (g_puCut==2) {//Apply w/o asking eta but w/ pt only
                if(v_jet_calib.Pt()/1e3>50) apply_pu_cut=0;
                else                        apply_pu_cut=1;
            }
            else if (g_puCut==3) {//Apply all jets w/o asking pt/eta
                apply_pu_cut=1;
            }


            if (g_mixSamples) {
                if(!ttIndex and label==15) continue;
            }
            else {
                if(!te_inclsv_fill_triggered and label==15) continue;
            }
            if (not(v_jet_calib.Pt()/1e3>20 and fabs(v_jet_calib.Eta())<2.5)) continue;//basic cut with calib pt eta
            if (apply_pu_cut and jvt<g_jvtCut) continue;
            if (apply_pu_cut and jvf<g_jvfCut) continue;
            if (g_requireTruthMatch and !truthMatch) continue;

            if (ievt<10)
                cout<<ijet<<"/"<<njets <<": (pt, eta, phi, m)= ("	  <<v_jet.Pt()/1e3<<",\t"  <<v_jet.Eta()<<",\t"
                    <<v_jet.Phi()<<",\t"	  <<v_jet.M()/1e3<<"),\t"
                    <<"label="<<label<<",\t"      <<", MV2c00= "<<mv2c00
                    <<",\t jvf="<<jvf<<",\t"<<"jvt="<<jvt<<",\t"	 
                    <<endl;

            /*********************************************/
            /********** prepare input variables **********/
            /*********************************************/
            if(debug)cout<<"kmdebug: preparing input variables."<<endl;

            float pt  = v_jet.Pt();
            float eta = v_jet.Eta();

            // ****** ip variables ******
            float ip2_pb = treeName=="bTag" ? bTagG_treeObj->jet_IP2D_jet_ipxd_pb->at(ijet) : bTag_treeObj->jet_ip2d_pb->at(ijet);
            float ip2_pu = treeName=="bTag" ? bTagG_treeObj->jet_IP2D_jet_ipxd_pu->at(ijet) : bTag_treeObj->jet_ip2d_pu->at(ijet);
            float ip2_pc = treeName=="bTag" ? bTagG_treeObj->jet_IP2D_jet_ipxd_pc->at(ijet) : bTag_treeObj->jet_ip2d_pc->at(ijet);

            float ip3_pb = treeName=="bTag" ? bTagG_treeObj->jet_IP3D_jet_ipxd_pb->at(ijet) : bTag_treeObj->jet_ip3d_pb->at(ijet);
            float ip3_pu = treeName=="bTag" ? bTagG_treeObj->jet_IP3D_jet_ipxd_pu->at(ijet) : bTag_treeObj->jet_ip3d_pu->at(ijet);
            float ip3_pc = treeName=="bTag" ? bTagG_treeObj->jet_IP3D_jet_ipxd_pc->at(ijet) : bTag_treeObj->jet_ip3d_pc->at(ijet);

            if (not(ip2_pu<10) or ip2_pu<-1 ) {
                ip2_pb=-1;
                ip2_pu=-1;
                ip2_pc=-1;
            }
            float ip2   = ip2_pb>0 and ip2_pu ? log(ip2_pb/ip2_pu) : -20;
            float ip2_c = ip2_pb>0 and ip2_pc ? log(ip2_pb/ip2_pc) : -20;
            float ip2_cu= ip2_pc>0 and ip2_pu ? log(ip2_pc/ip2_pu) : -20;

            if (not(ip3_pu<10) ) {
                ip3_pb=-1;
                ip3_pu=-1;
                ip3_pc=-1;
            }
            float ip3   = ip3_pb>0 and ip3_pu ? log(ip3_pb/ip3_pu) : -20;
            float ip3_c = ip3_pb>0 and ip3_pc ? log(ip3_pb/ip3_pc) : -20;
            float ip3_cu= ip3_pc>0 and ip3_pu ? log(ip3_pc/ip3_pu) : -20;

            // ****** sv1 variables ******
            int   sv1_ntkv = treeName=="bTag" ? bTagG_treeObj->jet_SV1_jet_sv1_ntrkv->at(ijet): bTag_treeObj->jet_sv1_ntrkv->at(ijet);
            int   sv1_n2t  = treeName=="bTag" ? bTagG_treeObj->jet_SV1_jet_sv1_n2t  ->at(ijet): bTag_treeObj->jet_sv1_n2t  ->at(ijet);
            float sv1_mass = treeName=="bTag" ? bTagG_treeObj->jet_SV1_jet_sv1_m    ->at(ijet): bTag_treeObj->jet_sv1_m    ->at(ijet);
            float sv1_efrc = treeName=="bTag" ? bTagG_treeObj->jet_SV1_jet_sv1_efc  ->at(ijet): bTag_treeObj->jet_sv1_efc  ->at(ijet);
            float sv1_sig3 = treeName=="bTag" ? bTagG_treeObj->jet_SV1_jet_sv1_normdist->at(ijet): bTag_treeObj->jet_sv1_sig3d->at(ijet);

            //      float pv_x= treeName=="bTag" ? bTagG_treeObj->PVx: bTag_treeObj->PVx;
            //      float pv_y= treeName=="bTag" ? bTagG_treeObj->PVy: bTag_treeObj->PVy;
            //      float pv_z= treeName=="bTag" ? bTagG_treeObj->PVz: bTag_treeObj->PVz;

            //      bool sv1_vtx_ok = 0;
            //      if (treeName=="bTag") sv1_vtx_ok= not(bTagG_treeObj->jet_SV1_jet_sv1_vtx_x->at(ijet)==0 and bTagG_treeObj->jet_SV1_jet_sv1_vtx_y->at(ijet)==0 and bTagG_treeObj->jet_SV1_jet_sv1_vtx_z->at(ijet)==0);
            //      else                         sv1_vtx_ok= bTag_treeObj->jet_sv1_vtxx->at(ijet).size();

            //      float dx=0, dy=0, dz=0;
            //      TVector3 pv2sv(0,0,0);
            //      TVector3 jetAxis(v_jet.Px(),v_jet.Py(),v_jet.Pz());

            float sv1_Lxy=-100, sv1_L3d=-100; float sv1_dR=-1;
            if(treeName=="bTag_TriggerJets") {
                sv1_Lxy = bTag_treeObj->jet_sv1_Lxy->at(ijet);
                sv1_L3d = bTag_treeObj->jet_sv1_L3d->at(ijet);
                sv1_dR = bTag_treeObj->jet_sv1_dR->at(ijet);
            } else {
                float pv_x= treeName=="bTag" ? bTagG_treeObj->PVx: bTag_treeObj->PVx;
                float pv_y= treeName=="bTag" ? bTagG_treeObj->PVy: bTag_treeObj->PVy;
                float pv_z= treeName=="bTag" ? bTagG_treeObj->PVz: bTag_treeObj->PVz;
                bool sv1_vtx_ok = 0;
                if (treeName=="bTag") sv1_vtx_ok= not(bTagG_treeObj->jet_SV1_jet_sv1_vtx_x->at(ijet)==0 and bTagG_treeObj->jet_SV1_jet_sv1_vtx_y->at(ijet)==0 and bTagG_treeObj->jet_SV1_jet_sv1_vtx_z->at(ijet)==0);
                else                         sv1_vtx_ok= bTag_treeObj->jet_sv1_vtxx->at(ijet).size();

                float dx=0, dy=0, dz=0;
                TVector3 pv2sv(0,0,0);
                TVector3 jetAxis(v_jet.Px(),v_jet.Py(),v_jet.Pz());	

                if (sv1_vtx_ok) {
                    float sv1_vtx_x=0, sv1_vtx_y=0, sv1_vtx_z=0;
                    if (treeName=="bTag") {
                        sv1_vtx_x= bTagG_treeObj->jet_SV1_jet_sv1_vtx_x->at(ijet);
                        sv1_vtx_y= bTagG_treeObj->jet_SV1_jet_sv1_vtx_y->at(ijet);
                        sv1_vtx_z= bTagG_treeObj->jet_SV1_jet_sv1_vtx_z->at(ijet);
                    }
                    else {
                        sv1_vtx_x= bTag_treeObj->jet_sv1_vtxx->at(ijet).at(0);
                        sv1_vtx_y= bTag_treeObj->jet_sv1_vtxy->at(ijet).at(0);
                        sv1_vtx_z= bTag_treeObj->jet_sv1_vtxz->at(ijet).at(0);
                    }
                    dx= sv1_vtx_x - pv_x;
                    dy= sv1_vtx_y - pv_y;
                    dz= sv1_vtx_z - pv_z;
                    pv2sv.SetXYZ(dx,dy,dz);

                    sv1_dR= pv2sv.DeltaR(jetAxis);
                    sv1_Lxy=hypot(dx,dy);
                    sv1_L3d= sqrt(dx*dx + dy*dy + dz*dz);
                }

                if (!sv1_vtx_ok) {
                    sv1_ntkv = -1;
                    sv1_n2t  = -1;
                    sv1_mass = -1e3;
                    sv1_efrc = -1;
                    sv1_sig3 = -100;
                }
            }
            // ****** jet fitter variables ******
            int   jf_n2tv  = treeName=="bTag" ? bTagG_treeObj->jet_jf_n2t     ->at(ijet): bTag_treeObj->jet_jf_n2t     ->at(ijet);
            int   jf_ntrkv = treeName=="bTag" ? bTagG_treeObj->jet_jf_ntrkAtVx->at(ijet): bTag_treeObj->jet_jf_ntrkAtVx->at(ijet);
            int   jf_nvtx  = treeName=="bTag" ? bTagG_treeObj->jet_jf_nvtx    ->at(ijet): bTag_treeObj->jet_jf_nvtx    ->at(ijet);
            int   jf_nvtx1t= treeName=="bTag" ? bTagG_treeObj->jet_jf_nvtx1t  ->at(ijet): bTag_treeObj->jet_jf_nvtx1t  ->at(ijet);

            float jf_mass  = treeName=="bTag" ? bTagG_treeObj->jet_jf_m    ->at(ijet)   : bTag_treeObj->jet_jf_m    ->at(ijet);
            float jf_efrc  = treeName=="bTag" ? bTagG_treeObj->jet_jf_efc  ->at(ijet)   : bTag_treeObj->jet_jf_efc  ->at(ijet);
            float jf_sig3  = treeName=="bTag" ? bTagG_treeObj->jet_jf_sig3d->at(ijet)   : bTag_treeObj->jet_jf_sig3d->at(ijet);
            float jf_deta  = treeName=="bTag" ? bTagG_treeObj->jet_jf_deta ->at(ijet)   : bTag_treeObj->jet_jf_deta ->at(ijet);
            float jf_dphi  = treeName=="bTag" ? bTagG_treeObj->jet_jf_dphi ->at(ijet)   : bTag_treeObj->jet_jf_dphi ->at(ijet);
            float jf_dR    =  jf_mass>0 ? hypot(jf_deta,jf_dphi) : -10;

            if (not(jf_mass>0)) {
                jf_n2tv  =-1;
                jf_ntrkv =-1;
                jf_nvtx  =-1;
                jf_nvtx1t=-1;

                jf_mass  =-1e3;
                jf_efrc  =-1;
                jf_sig3  =-100;
                jf_dR    =-1;
            }
            /*** MVb specific variables ***/
            float width = -1;
            int n_trk_sigd0cut = 0;
            float trk3_d0sig = -100;
            float trk3_z0sig = -100;
            float sv_scaled_efc = -1;
            float jf_scaled_efc = -1;

            if (treeName=="bTag") {
                width = bTagG_treeObj->jet_width->at(ijet);
                n_trk_sigd0cut = bTagG_treeObj->jet_n_trk_sigd0cut->at(ijet);
                trk3_d0sig = bTagG_treeObj->jet_trk3_d0sig->at(ijet);
                trk3_z0sig = bTagG_treeObj->jet_trk3_z0sig->at(ijet);
                sv_scaled_efc = bTagG_treeObj->jet_sv_scaled_efc->at(ijet);
                jf_scaled_efc = bTagG_treeObj->jet_jf_scaled_efc->at(ijet);
            }
            else {
                if (warningCount<10) {
                    Warning("prepareTtEventsFromEvt()", "Cannot fill MVb specific variables from non-\"bTag\" tree type.");
                    warningCount++;
                }
            }


            vector<double> input_vars; input_vars.clear();
            for (unsigned i=0; i<g_s_inputVariables.size(); i++) {
                if      (g_s_inputVariables.at(i)=="pt"      ) input_vars.push_back(pt       );
                else if (g_s_inputVariables.at(i)=="abs(eta)") input_vars.push_back(fabs(eta));

                else if (g_s_inputVariables.at(i)=="ip2"     ) input_vars.push_back(ip2      );
                else if (g_s_inputVariables.at(i)=="ip2_c"   ) input_vars.push_back(ip2_c    );
                else if (g_s_inputVariables.at(i)=="ip2_cu"  ) input_vars.push_back(ip2_cu   );

                else if (g_s_inputVariables.at(i)=="ip3"     ) input_vars.push_back(ip3      );
                else if (g_s_inputVariables.at(i)=="ip3_c"   ) input_vars.push_back(ip3_c    );
                else if (g_s_inputVariables.at(i)=="ip3_cu"  ) input_vars.push_back(ip3_cu   );

                else if (g_s_inputVariables.at(i)=="sv1_ntkv") input_vars.push_back(sv1_ntkv );
                else if (g_s_inputVariables.at(i)=="sv1_n2t" ) input_vars.push_back(sv1_n2t  );
                else if (g_s_inputVariables.at(i)=="sv1_mass") input_vars.push_back(sv1_mass );
                else if (g_s_inputVariables.at(i)=="sv1_efrc") input_vars.push_back(sv1_efrc );
                else if (g_s_inputVariables.at(i)=="sv1_Lxy" ) input_vars.push_back(sv1_Lxy  );
                else if (g_s_inputVariables.at(i)=="sv1_L3d" ) input_vars.push_back(sv1_L3d  );
                else if (g_s_inputVariables.at(i)=="sv1_sig3") input_vars.push_back(sv1_sig3 );
                else if (g_s_inputVariables.at(i)=="sv1_dR"  ) input_vars.push_back(sv1_dR   );

                else if (g_s_inputVariables.at(i)=="jf_n2tv"  ) input_vars.push_back(jf_n2tv  );
                else if (g_s_inputVariables.at(i)=="jf_ntrkv" ) input_vars.push_back(jf_ntrkv );
                else if (g_s_inputVariables.at(i)=="jf_nvtx"  ) input_vars.push_back(jf_nvtx  );
                else if (g_s_inputVariables.at(i)=="jf_nvtx1t") input_vars.push_back(jf_nvtx1t);
                else if (g_s_inputVariables.at(i)=="jf_mass"  ) input_vars.push_back(jf_mass  );
                else if (g_s_inputVariables.at(i)=="jf_efrc"  ) input_vars.push_back(jf_efrc  );
                else if (g_s_inputVariables.at(i)=="jf_sig3"  ) input_vars.push_back(jf_sig3  );
                else if (g_s_inputVariables.at(i)=="jf_dR"    ) input_vars.push_back(jf_dR    );

                else if (g_s_inputVariables.at(i) == "width") input_vars.push_back(width);
                else if (g_s_inputVariables.at(i) == "n_trk_sigd0cut") input_vars.push_back(n_trk_sigd0cut);
                else if (g_s_inputVariables.at(i) == "trk3_d0sig") input_vars.push_back(trk3_d0sig);
                else if (g_s_inputVariables.at(i) == "trk3_z0sig") input_vars.push_back(trk3_z0sig);
                else if (g_s_inputVariables.at(i) == "sv_scaled_efc") input_vars.push_back(sv_scaled_efc);
                else if (g_s_inputVariables.at(i) == "jf_scaled_efc") input_vars.push_back(jf_scaled_efc);

                else {
                    cerr<<"variable: "<<g_s_inputVariables.at(i) <<" is NOT declared, please update the code. Aborting..."<<endl; exit(1);
                }
            }

            /********** weight determination **********/
            if(debug)cout<<"kmdebug: preparing weighting values."<<endl;
            float weight=1.0;
            if (weightPDFexists) {
                if      (g_weightType=="r") weight=rWeight(pt,eta,label);
                else if (g_weightType=="f") weight=fWeight(pt,eta,label);
            }

            const float c_weight= cWeight(ip2_pu,jf_sig3,sv1_mass); 
            const bool isGood= c_weight==1;
            if (g_apply_cWeight) weight*=c_weight;

            TString className;
            if      (label==5)  className= g_multiClassification ? "sig5" : "Signal"     ;
            else if (label==0)  className= g_multiClassification ? "bkg0" : "Background" ;
            else if (label==4)  className= g_multiClassification ? "bkg4" : "Background" ;
            else if (label==15) {}//do nothing
            else if (label==99 || label==-9) { continue; }
            else {
                cerr<<"Unknown label: "<<label<<" is given, please check. Aborting..."<<endl;
                exit(1);
            }

            if (label!=15 
                    and not(className=="Signal" or className=="Background" or className=="sig5" or className=="bkg0" or className=="bkg4")
               ) {
                cerr<<"Unknown class type: \""<<className<<"\", please check, aborting..."<<endl;
                exit(1);
            }

            if(debug)cout<<"kmdebug: checking stat."<<endl;      
            bool forTrainingEvent= g_mixSamples ? ttIndex : true;


            if (g_mixSamples) {//randomly split
                if (g_doInclusiveTraining) {
                    if      ( counters_good[label+100*ttIndex]<max_good[label+100*ttIndex] ) forTrainingEvent=!ttIndex;
                    else if ( counters_bad [label+100*ttIndex]<max_bad [label+100*ttIndex] ) forTrainingEvent=!ttIndex;
                    else if (teCounter_inclsv<teMax_inclsv) {}//for inclusive testing sample
                    else continue;                            // throwing away this event
                }
                else {
                    if (isGood) {
                        if ( counters_good[label+100*ttIndex]<max_good[label+100*ttIndex] ) forTrainingEvent=!ttIndex;
                        else if (teCounter_inclsv<teMax_inclsv) {}//for inclusive testing smaple
                        else continue;                            // throwing away this event
                    }
                    else {
                        if ( counters_bad[label+100*ttIndex]<max_bad[label+100*ttIndex] ) forTrainingEvent=!ttIndex;
                        else if (teCounter_inclsv<teMax_inclsv) {}//for inclusive testing smaple
                        else continue;                            // throwing away this event
                    }
                }
            }
            else {
                if (g_doInclusiveTraining) {
                    if      ( counters_good[label    ]<max_good[label]     ) forTrainingEvent=1;// good for training
                    else if ( counters_bad [label    ]<max_bad [label    ] ) forTrainingEvent=1;// bad for training
                    else if ( counters_good[label+100]<max_good[label+100] ) forTrainingEvent=0;// good for testing 
                    else if ( counters_bad [label+100]<max_bad [label+100] ) forTrainingEvent=0;// bad for testing 
                    else if (!te_inclsv_fill_triggered) continue;                               // throwing away this event
                }
                else {
                    if (isGood) {
                        if      ( counters_good[label    ]<max_good[label]     ) forTrainingEvent=1;// good for training
                        else if ( counters_good[label+100]<max_good[label+100] ) forTrainingEvent=0;// good for testing 
                        else if (!te_inclsv_fill_triggered) continue;                               // throwing away this event
                    }
                    else {
                        if      ( counters_bad[label    ]<max_bad[label    ] ) forTrainingEvent=1;// bad for training
                        else if ( counters_bad[label+100]<max_bad[label+100] ) forTrainingEvent=0;// bad for testing 
                        else if (!te_inclsv_fill_triggered) continue;                             // throwing away this event
                    }
                }
            }

            /********** Main part, assigning the events to tmva factory or TTree**********/
            if (g_generateTrees) {
                int treeIndex=label;
                if (!forTrainingEvent) treeIndex+=100;

                if (!map_minibtags[treeIndex]) {
                    cerr<<"map_minibtags["<<treeIndex<<"]= "<<map_minibtags[treeIndex]<<"!!! Aborting..."<<endl;
                    exit(1);
                }

                /*** some relevant variables ***/
                map_minibtags[treeIndex]->label     = label;
                map_minibtags[treeIndex]->phi       = v_jet.Phi();
                map_minibtags[treeIndex]->m         = v_jet.M();
                map_minibtags[treeIndex]->pt_calib  = v_jet_calib.Pt();
                map_minibtags[treeIndex]->eta_calib = v_jet_calib.Eta();
                map_minibtags[treeIndex]->pt_uCalib = v_jet_uCalib.Pt();
                map_minibtags[treeIndex]->eta_uCalib= v_jet_uCalib.Eta();
                map_minibtags[treeIndex]->truthMatch= truthMatch;
                map_minibtags[treeIndex]->JVT       = jvt;
                map_minibtags[treeIndex]->JVF       = jvf;
                map_minibtags[treeIndex]->mcchannel = mc_ch;
                //	map_minibtags[treeIndex]->evtnum = evtnum;  //AC added
                map_minibtags[treeIndex]->muAvg     = mu_avg;
                map_minibtags[treeIndex]->isGood    = isGood;
                map_minibtags[treeIndex]->ip2_pu    = ip2_pu;
                map_minibtags[treeIndex]->ip2_pb    = ip2_pb;
                map_minibtags[treeIndex]->ip2_pc    = ip2_pc;
                map_minibtags[treeIndex]->ip3_pu    = ip3_pu;
                map_minibtags[treeIndex]->ip3_pb    = ip3_pb;
                map_minibtags[treeIndex]->ip3_pc    = ip3_pc;
                map_minibtags[treeIndex]->mv2c00    = mv2c00;
                map_minibtags[treeIndex]->mv2c10    = mv2c10;
                map_minibtags[treeIndex]->mv2c20    = mv2c20;
                map_minibtags[treeIndex]->mv2m_pb   = mv2m_pb;
                map_minibtags[treeIndex]->mv2m_pu   = mv2m_pu;
                map_minibtags[treeIndex]->mv2m_pc   = mv2m_pc;

                /*** Actual MV2 input ***/
                map_minibtags[treeIndex]->pt = pt;
                map_minibtags[treeIndex]->eta= eta;

                map_minibtags[treeIndex]->ip2      =ip2   ;
                map_minibtags[treeIndex]->ip2_c    =ip2_c ;
                map_minibtags[treeIndex]->ip2_cu   =ip2_cu;

                map_minibtags[treeIndex]->ip3      =ip3   ;
                map_minibtags[treeIndex]->ip3_c    =ip3_c ;
                map_minibtags[treeIndex]->ip3_cu   =ip3_cu;

                map_minibtags[treeIndex]->sv1ntkv =sv1_ntkv;
                map_minibtags[treeIndex]->sv1n2tv =sv1_n2t ;
                map_minibtags[treeIndex]->sv1mass =sv1_mass;
                map_minibtags[treeIndex]->sv1efrc =sv1_efrc;
                map_minibtags[treeIndex]->sv1Lxy  =sv1_Lxy ;
                map_minibtags[treeIndex]->sv1L3d  =sv1_L3d ;
                map_minibtags[treeIndex]->sv1sig3 =sv1_sig3;
                map_minibtags[treeIndex]->sv1dR   =sv1_dR  ;

                map_minibtags[treeIndex]->jf_n2tv  =jf_n2tv  ;
                map_minibtags[treeIndex]->jf_ntrkv =jf_ntrkv ;
                map_minibtags[treeIndex]->jf_nvtx  =jf_nvtx  ;
                map_minibtags[treeIndex]->jf_nvtx1t=jf_nvtx1t;
                map_minibtags[treeIndex]->jf_mass  =jf_mass  ;
                map_minibtags[treeIndex]->jf_efrc  =jf_efrc  ;
                map_minibtags[treeIndex]->jf_sig3  =jf_sig3  ;
                map_minibtags[treeIndex]->jf_dR    =jf_dR    ;


                map_minibtags[treeIndex]->width = width;
                map_minibtags[treeIndex]->n_trk_sigd0cut = n_trk_sigd0cut;
                map_minibtags[treeIndex]->trk3_d0sig = trk3_d0sig;
                map_minibtags[treeIndex]->trk3_z0sig = trk3_z0sig;
                map_minibtags[treeIndex]->sv_scaled_efc = sv_scaled_efc;
                map_minibtags[treeIndex]->jf_scaled_efc = jf_scaled_efc;

                check_input_values(map_minibtags[treeIndex]);

                if (g_mixSamples) {
                    if ( (isGood  and  counters_good[label+100*ttIndex]<max_good[label+100*ttIndex]) or// (isGood  and  counters_good[treeIndex]<max_good[treeIndex]) or
                            (!isGood and  counters_bad [label+100*ttIndex]<max_bad [label+100*ttIndex])   //	(!isGood and  counters_bad [treeIndex]<max_bad [treeIndex])   
                       ) {
                        map_minibtags[treeIndex]->fChain->Fill();
                        if (g_doInclusiveTraining) {
                            if      ( counters_good[label+100*ttIndex]<max_good[label+100*ttIndex] ) counters_good[label+100*ttIndex]++;
                            else if ( counters_bad [label+100*ttIndex]<max_bad [label+100*ttIndex] ) counters_bad [label+100*ttIndex]++;
                        }
                        else{
                            if (isGood) { if ( counters_good[label+100*ttIndex]<max_good[label+100*ttIndex] ) counters_good[label+100*ttIndex]++;}
                            else        { if ( counters_bad [label+100*ttIndex]<max_bad [label+100*ttIndex] ) counters_bad [label+100*ttIndex]++;}
                        }
                    }
                }
                else {
                    //if(not( treeIndex<100 and te_inclsv_fill_triggered))
                    if(not( forTrainingEvent and te_inclsv_fill_triggered )) 
                    {
                        map_minibtags[treeIndex]->fChain->Fill();
                    }
                }

                if ((te_inclsv_fill_triggered and teCounter_inclsv<teMax_inclsv) or (g_mixSamples and teCounter_inclsv<teMax_inclsv)) {


                    if(ttIndex!=1) copyVars(te_inclsv,map_minibtags[treeIndex]);
                    if (ttIndex!=1) te_inclsv->fChain->Fill();
                }
            }
            else {
                if (forTrainingEvent) factory->AddTrainingEvent(className,input_vars,weight);
                else                  factory->AddTestEvent    (className,input_vars,weight);
            }

            if (!g_mixSamples) {
                if (g_doInclusiveTraining) {
                    if      ( counters_good[label    ]<max_good[label    ] ) counters_good[label    ]++;
                    else if ( counters_bad [label    ]<max_bad [label    ] ) counters_bad [label    ]++;
                    else if ( counters_good[label+100]<max_good[label+100] ) counters_good[label+100]++;
                    else if ( counters_bad [label+100]<max_bad [label+100] ) counters_bad [label+100]++;
                }
                else{
                    if (isGood) {
                        if      ( counters_good[label    ]<max_good[label    ] ) counters_good[label    ]++;
                        else if ( counters_good[label+100]<max_good[label+100] ) counters_good[label+100]++;
                    }
                    else {
                        if      ( counters_bad[label    ]<max_bad[label    ] ) counters_bad[label    ]++;
                        else if ( counters_bad[label+100]<max_bad[label+100] ) counters_bad[label+100]++;
                    }
                }
            }
            if ((g_mixSamples or te_inclsv_fill_triggered) and teCounter_inclsv<teMax_inclsv) teCounter_inclsv++;

        }//end of jet loop

        if ( counters_good[  5]==max_good[  5] and 
                counters_good[105]==max_good[105] and
                counters_bad [  5]==max_bad [  5] and
                counters_bad [105]==max_bad [105] and
                counters_good[  0]==max_good[  0] and
                counters_good[100]==max_good[100] and 
                counters_bad [  0]==max_bad [  0] and
                counters_bad [100]==max_bad [100] and
                counters_good[  4]==max_good[  4] and
                counters_good[104]==max_good[104] and
                counters_bad [  4]==max_bad [  4] and
                counters_bad [104]==max_bad [104] and
                teCounter_inclsv==teMax_inclsv
           ) {
            cout<<"prepareTtEventsFromEvt *** All necessary jets are collected. Breaking event loop."<<endl;
            break;
        }

        if(counters_good[5]==max_good[5] and
                counters_bad [5]==max_bad [5] and
                counters_good[0]==max_good[0] and
                counters_bad [0]==max_bad [0] and
                counters_good[4]==max_good[4] and
                counters_bad [4]==max_bad [4] ) te_inclsv_fill_triggered=true;

        if (ievt%(unsigned)1e5==0) {
            cout<<"prepareTtEventsFromEvt *** "<<ievt<<" events processed: collected\t" <<
                (float)(counters_good[  5]+ counters_good[  0]+ counters_good[  4]+ counters_bad[  5]+ counters_bad[  0]+ counters_bad[  4])*100
                /      (max_good     [  5]+ max_good     [  0]+ max_good     [  4]+ max_bad     [  5]+ max_bad     [  0]+ max_bad     [  4]) <<"% for training stat,\t" <<
                (float)(counters_good[105]+ counters_good[100]+ counters_good[104]+ counters_bad[105]+ counters_bad[100]+ counters_bad[104])*100
                /      (max_good     [105]+ max_good     [100]+ max_good     [104] +max_bad     [105]+ max_bad     [100]+ max_bad     [104]) <<"% for testing stat,\t"<<
                (float)teCounter_inclsv/teMax_inclsv*100                                                                                     <<"% for inclusive testing stat. ";
            sw.Print();sw.Start(0);
        }
    }//end of event loop
    sw.Stop(); cout<<"prepareTtEventsFromEvt *** Time cost for event collection: "; sw.Print();

    cout<<"prepareTtEventsFromEvt *** Saving training/testing trees in: "<<gROOT->GetFile()->GetName()<<endl;
    map_minibtags[ 0]->fChain->Write(); map_minibtags[100]->fChain->Write();
    map_minibtags[ 4]->fChain->Write(); map_minibtags[104]->fChain->Write();
    map_minibtags[ 5]->fChain->Write(); map_minibtags[105]->fChain->Write();
    map_minibtags[15]->fChain->Write();

    map<int,TTree*> map_trees;
    map_trees[  5]= tr_bottom->fChain;  map_trees[105]= te_bottom->fChain;
    map_trees[  4]= tr_charm ->fChain;  map_trees[104]= te_charm ->fChain;
    map_trees[  0]= tr_light ->fChain;  map_trees[100]= te_light ->fChain;

    if ( not( counters_good[5]/max_good[5]==1 and counters_good[105]/max_good[105]==1 and 
                counters_bad [5]/max_bad [5]==1 and counters_bad [105]/max_bad [105]==1 and 
                counters_good[0]/max_good[0]==1 and counters_good[100]/max_good[100]==1 and 
                counters_bad [0]/max_bad [0]==1 and counters_bad [100]/max_bad [100]==1 and 
                counters_good[4]/max_good[4]==1 and counters_good[104]/max_good[104]==1 and 
                counters_bad [4]/max_bad [4]==1 and counters_bad [104]/max_bad [104]==1
            ) ) {
        //cout<<"Coud NOT collect all the events required, counter summary: "<<endl<<"\t"
        //	<<"g  5: "<<counters_good[  5]<<"/"<<max_good[  5] <<"\t"      <<"g105: "<<counters_good[105]<<"/"<<max_good[105] <<endl<<"\t"
        //	<<"b  5: "<<counters_bad [  5]<<"/"<<max_bad [  5] <<"\t"      <<"b105: "<<counters_bad [105]<<"/"<<max_bad [105] <<endl<<"\t"
        //	<<"g  0: "<<counters_good[  0]<<"/"<<max_good[  0] <<"\t"      <<"g100: "<<counters_good[100]<<"/"<<max_good[100] <<endl<<"\t"
        //	<<"b  0: "<<counters_bad [  0]<<"/"<<max_bad [  0] <<"\t"      <<"b100: "<<counters_bad [100]<<"/"<<max_bad [100] <<endl<<"\t"
        //	<<"g  4: "<<counters_good[  4]<<"/"<<max_good[  4] <<"\t"      <<"g104: "<<counters_good[104]<<"/"<<max_good[104] <<endl<<"\t"
        //	<<"b  4: "<<counters_bad [  4]<<"/"<<max_bad [  4] <<"\t"      <<"b104: "<<counters_bad [104]<<"/"<<max_bad [104] <<endl
        //	<<"===================================>>> Note: this doesn't abort the process but the training/testing is performed with statistics less than what you requested."<<endl;
    }

    return map_trees;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void outputPDFs(map<int,TTree*> map_trees) {//void outputPDFs(TString trainName,map<int,TTree*> map_trees) {

    cout<<"Start preparing the output distribution histograms."<<endl;


    //initialize reader here
    initializeReader();//initializeReader(trainName);

    if (g_multiClassification) {
        //training histograms                              //testing histograms				   //Projection training trees                       //Projection testing trees			       
        b_pb_tr= new TH1F("b_pb_tr","b_pb_tr",50, 0, 1);  b_pb_te= new TH1F("b_pb_te","b_pb_te",50, 0, 1);	   // map_trees[5]->Project(b_pb_tr->GetName(),"");  // map_trees[-105]->Project(b_pb_te->GetName(),"");
        b_pc_tr= new TH1F("b_pc_tr","b_pc_tr",50, 0, 1);  b_pc_te= new TH1F("b_pc_te","b_pc_te",50, 0, 1);	   // map_trees[5]->Project(b_pc_tr->GetName(),"");  // map_trees[-105]->Project(b_pc_te->GetName(),"");
        b_pu_tr= new TH1F("b_pu_tr","b_pu_tr",50, 0, 1);  b_pu_te= new TH1F("b_pu_te","b_pu_te",50, 0, 1);	   // map_trees[5]->Project(b_pu_tr->GetName(),"");  // map_trees[-105]->Project(b_pu_te->GetName(),"");
        u_pb_tr= new TH1F("u_pb_tr","u_pb_tr",50, 0, 1);  u_pb_te= new TH1F("u_pb_te","u_pb_te",50, 0, 1);	   // map_trees[0]->Project(u_pb_tr->GetName(),"");  // map_trees[-100]->Project(u_pb_te->GetName(),"");
        u_pc_tr= new TH1F("u_pc_tr","u_pc_tr",50, 0, 1);  u_pc_te= new TH1F("u_pc_te","u_pc_te",50, 0, 1);	   // map_trees[0]->Project(u_pc_tr->GetName(),"");  // map_trees[-100]->Project(u_pc_te->GetName(),"");
        u_pu_tr= new TH1F("u_pu_tr","u_pu_tr",50, 0, 1);  u_pu_te= new TH1F("u_pu_te","u_pu_te",50, 0, 1);	   // map_trees[0]->Project(u_pu_tr->GetName(),"");  // map_trees[-100]->Project(u_pu_te->GetName(),"");
        c_pb_tr= new TH1F("c_pb_tr","c_pb_tr",50, 0, 1);  c_pb_te= new TH1F("c_pb_te","c_pb_te",50, 0, 1);	   // map_trees[4]->Project(c_pb_tr->GetName(),"");  // map_trees[-104]->Project(c_pb_te->GetName(),"");
        c_pc_tr= new TH1F("c_pc_tr","c_pc_tr",50, 0, 1);  c_pc_te= new TH1F("c_pc_te","c_pc_te",50, 0, 1);	   // map_trees[4]->Project(c_pc_tr->GetName(),"");  // map_trees[-104]->Project(c_pc_te->GetName(),"");
        c_pu_tr= new TH1F("c_pu_tr","c_pu_tr",50, 0, 1);  c_pu_te= new TH1F("c_pu_te","c_pu_te",50, 0, 1);	   // map_trees[4]->Project(c_pu_tr->GetName(),"");  // map_trees[-104]->Project(c_pu_te->GetName(),"");
    }
    else {
        b_bdt_tr= new TH1F("b_bdt_tr","b_bdt_tr",50, -1, 1);  b_bdt_te= new TH1F("b_bdt_te","b_bdt_te",50, -1, 1);
        c_bdt_tr= new TH1F("c_bdt_tr","c_bdt_tr",50, -1, 1);  c_bdt_te= new TH1F("c_bdt_te","c_bdt_te",50, -1, 1);
        u_bdt_tr= new TH1F("u_bdt_tr","u_bdt_tr",50, -1, 1);  u_bdt_te= new TH1F("u_bdt_te","u_bdt_te",50, -1, 1);
    }

    vector<int> labelindex;
    labelindex.push_back(5); if(!useSingleTeTree) labelindex.push_back(-105);
    labelindex.push_back(0); if(!useSingleTeTree) labelindex.push_back(-100);
    if (g_use_c) {
        labelindex.push_back(4);
        if(!useSingleTeTree) labelindex.push_back(-104);
    }
    if(useSingleTeTree) labelindex.push_back(-111);

    const unsigned nBreakTest = 1e6;

    for (unsigned i_li=0; i_li<labelindex.size(); i_li++ ) {
        const bool testTree= labelindex[i_li]<0;
        TTree* tree= map_trees[labelindex[i_li]];

        cout<<"Start processing "<<(testTree?"testTree ":"trainTree ")<<labelindex[i_li]<<"\t"<<tree->GetName()<<": "<<tree->GetEntries()<<endl;

        int label;
        double pt,eta;
        //double jf_sig3;
        tree->SetBranchAddress("pt",  &pt);
        tree->SetBranchAddress("eta", &eta);
        tree->SetBranchAddress("label", &label);
        //tree->SetBranchAddress("jf_sig3", &jf_sig3);
        for (unsigned ivar=0; ivar<g_s_inputVariables.size(); ivar++) {
            if(g_s_inputVariables[ivar]=="pt") continue;
            if(g_s_inputVariables[ivar]=="eta") continue;
            if(g_s_inputVariables[ivar]=="abs(eta)") continue;

            if      (g_map_inputVars[g_s_inputVariables[ivar]].type_=="F") tree->SetBranchAddress(g_s_inputVariables[ivar], &g_map_inputVars[g_s_inputVariables[ivar]].float_ );
            else if (g_map_inputVars[g_s_inputVariables[ivar]].type_=="I") tree->SetBranchAddress(g_s_inputVariables[ivar], &g_map_inputVars[g_s_inputVariables[ivar]].int_   );
            else if (g_map_inputVars[g_s_inputVariables[ivar]].type_=="D") tree->SetBranchAddress(g_s_inputVariables[ivar], &g_map_inputVars[g_s_inputVariables[ivar]].double_);
            else { cerr<<"Something wrong with variable list. Aborting..."<<endl; exit(1);}
        }//  setBranchAddress();//all input vars

        //event loop starts
        for (unsigned ievt=0; ievt<tree->GetEntries(); ievt++) {
            tree->GetEntry(ievt); //access tree contents in this event

            if (labelindex[i_li]==-111) {//do purification if needed
                //cout<<"label, pt, eta, jf_sig3= "<<label<<"\t"<<pt/1e3<<"\t"<<eta<<"\t"<<g_map_inputVars["jf_sig3"].double_<<endl;
                if (not(g_map_inputVars["jf_sig3"].double_>0)) continue;
                if (ievt==nBreakTest) break;
            }

            float mva_pb=-20, mva_pu=-20, mva_pc=-20;
            if (g_reader) {
                vector<double> input_vars;
                for (unsigned ivar=0; ivar<g_s_inputVariables.size(); ivar++) {
                    if      (g_s_inputVariables[ivar]=="pt" ) input_vars.push_back(pt);
                    else if (g_s_inputVariables[ivar]=="eta") input_vars.push_back(eta);
                    else if (g_s_inputVariables[ivar]=="abs(eta)") input_vars.push_back(fabs(eta));
                    else {
                        if      (g_map_inputVars[g_s_inputVariables[ivar]].type_=="F") input_vars.push_back( g_map_inputVars[g_s_inputVariables[ivar]].float_ );
                        else if (g_map_inputVars[g_s_inputVariables[ivar]].type_=="I") input_vars.push_back( g_map_inputVars[g_s_inputVariables[ivar]].int_   );
                        else if (g_map_inputVars[g_s_inputVariables[ivar]].type_=="D") input_vars.push_back( g_map_inputVars[g_s_inputVariables[ivar]].double_);
                        else { cerr<<"Something wrong with variable list. Aborting..."<<endl; exit(1);}
                    }
                }
                vector<float> output_vars=evalMultiClass(input_vars);//evalMultiClass(trainName,input_vars);
                if (!g_multiClassification) {
                    if (!testTree) {
                        if      (label==5) b_bdt_tr->Fill(output_vars[0]);
                        else if (label==0) u_bdt_tr->Fill(output_vars[0]);
                        else if (label==4) c_bdt_tr->Fill(output_vars[0]);
                    }
                    else {
                        if      (label==5) b_bdt_te->Fill(output_vars[0]);
                        else if (label==0) u_bdt_te->Fill(output_vars[0]);
                        else if (label==4) c_bdt_te->Fill(output_vars[0]);
                    }
                }
                else {
                    mva_pb=output_vars[0], mva_pu=output_vars[1], mva_pc=output_vars[2];
                    if (!testTree) {
                        if      (label==5) {b_pb_tr->Fill(mva_pb); b_pu_tr->Fill(mva_pu); b_pc_tr->Fill(mva_pc);}
                        else if (label==0) {u_pb_tr->Fill(mva_pb); u_pu_tr->Fill(mva_pu); u_pc_tr->Fill(mva_pc);}
                        else if (label==4) {c_pb_tr->Fill(mva_pb); c_pu_tr->Fill(mva_pu); c_pc_tr->Fill(mva_pc);}
                    }
                    else {
                        if      (label==5) {b_pb_te->Fill(mva_pb); b_pu_te->Fill(mva_pu); b_pc_te->Fill(mva_pc);}
                        else if (label==0) {u_pb_te->Fill(mva_pb); u_pu_te->Fill(mva_pu); u_pc_te->Fill(mva_pc);}
                        else if (label==4) {c_pb_te->Fill(mva_pb); c_pu_te->Fill(mva_pu); c_pc_te->Fill(mva_pc);}
                    }
                    //cout<<"pb+pu+pc= "<<mva_pb<<" + "<<mva_pu<<" + "<<mva_pc<<"= "<<mva_pb+mva_pu+mva_pc<<endl;
                }

            }//if (g_reader) {
        }//end of event loop
        }//loop over trees

        cout<<"finish looping over trees."<<endl;

        //SetLineColor
        if (g_multiClassification) {
            b_pb_tr->SetLineColor(kRed); u_pb_tr->SetLineColor(kBlue); c_pb_tr->SetLineColor(kGreen);
            b_pu_tr->SetLineColor(kRed); u_pu_tr->SetLineColor(kBlue); c_pu_tr->SetLineColor(kGreen);
            b_pc_tr->SetLineColor(kRed); u_pc_tr->SetLineColor(kBlue); c_pc_tr->SetLineColor(kGreen);
            b_pb_te->SetLineColor(kRed); u_pb_te->SetLineColor(kBlue); c_pb_te->SetLineColor(kGreen);
            b_pu_te->SetLineColor(kRed); u_pu_te->SetLineColor(kBlue); c_pu_te->SetLineColor(kGreen);
            b_pc_te->SetLineColor(kRed); u_pc_te->SetLineColor(kBlue); c_pc_te->SetLineColor(kGreen);

            b_pb_te->SetMarkerColor(kRed); u_pb_te->SetMarkerColor(kBlue); c_pb_te->SetMarkerColor(kGreen);
            b_pu_te->SetMarkerColor(kRed); u_pu_te->SetMarkerColor(kBlue); c_pu_te->SetMarkerColor(kGreen);
            b_pc_te->SetMarkerColor(kRed); u_pc_te->SetMarkerColor(kBlue); c_pc_te->SetMarkerColor(kGreen);

            b_pb_te->SetMarkerStyle(20); u_pb_te->SetMarkerStyle(20); c_pb_te->SetMarkerStyle(20);
            b_pu_te->SetMarkerStyle(20); u_pu_te->SetMarkerStyle(20); c_pu_te->SetMarkerStyle(20);
            b_pc_te->SetMarkerStyle(20); u_pc_te->SetMarkerStyle(20); c_pc_te->SetMarkerStyle(20);

            b_pb_te->SetMarkerSize(0.5); u_pb_te->SetMarkerSize(0.5); c_pb_te->SetMarkerSize(0.5);
            b_pu_te->SetMarkerSize(0.5); u_pu_te->SetMarkerSize(0.5); c_pu_te->SetMarkerSize(0.5);
            b_pc_te->SetMarkerSize(0.5); u_pc_te->SetMarkerSize(0.5); c_pc_te->SetMarkerSize(0.5);

            b_pb_tr->Sumw2();  u_pb_tr->Sumw2();  c_pb_tr->Sumw2();
            b_pu_tr->Sumw2();  u_pu_tr->Sumw2();  c_pu_tr->Sumw2();
            b_pc_tr->Sumw2();  u_pc_tr->Sumw2();  c_pc_tr->Sumw2();
            b_pb_te->Sumw2();  u_pb_te->Sumw2();  c_pb_te->Sumw2();
            b_pu_te->Sumw2();  u_pu_te->Sumw2();  c_pu_te->Sumw2();
            b_pc_te->Sumw2();  u_pc_te->Sumw2();  c_pc_te->Sumw2();

            //normalization
            b_pb_tr->Scale(1/b_pb_tr->Integral());  u_pb_tr->Scale(1/u_pb_tr->Integral());  c_pb_tr->Scale(1/c_pb_tr->Integral());
            b_pu_tr->Scale(1/b_pu_tr->Integral());  u_pu_tr->Scale(1/u_pu_tr->Integral());  c_pu_tr->Scale(1/c_pu_tr->Integral());
            b_pc_tr->Scale(1/b_pc_tr->Integral());  u_pc_tr->Scale(1/u_pc_tr->Integral());  c_pc_tr->Scale(1/c_pc_tr->Integral());
            b_pb_te->Scale(1/b_pb_te->Integral());  u_pb_te->Scale(1/u_pb_te->Integral());  c_pb_te->Scale(1/c_pb_te->Integral());
            b_pu_te->Scale(1/b_pu_te->Integral());  u_pu_te->Scale(1/u_pu_te->Integral());  c_pu_te->Scale(1/c_pu_te->Integral());
            b_pc_te->Scale(1/b_pc_te->Integral());  u_pc_te->Scale(1/u_pc_te->Integral());  c_pc_te->Scale(1/c_pc_te->Integral());
        }
        else {
            b_bdt_tr->SetLineColor(kRed); u_bdt_tr->SetLineColor(kBlue); c_bdt_tr->SetLineColor(kGreen);
            b_bdt_te->SetLineColor(kRed); u_bdt_te->SetLineColor(kBlue); c_bdt_te->SetLineColor(kGreen);

            b_bdt_te->SetMarkerColor(kRed); u_bdt_te->SetMarkerColor(kBlue); c_bdt_te->SetMarkerColor(kGreen);
            b_bdt_te->SetMarkerStyle(20);   u_bdt_te->SetMarkerStyle(20);    c_bdt_te->SetMarkerStyle(20);
            b_bdt_te->SetMarkerSize(0.5);   u_bdt_te->SetMarkerSize(0.5);    c_bdt_te->SetMarkerSize(0.5);

            b_bdt_tr->Sumw2();  u_bdt_tr->Sumw2();  c_bdt_tr->Sumw2();
            b_bdt_te->Sumw2();  u_bdt_te->Sumw2();  c_bdt_te->Sumw2();

            b_bdt_tr->Scale(1/b_bdt_tr->Integral());  u_bdt_tr->Scale(1/u_bdt_tr->Integral());  c_bdt_tr->Scale(1/c_bdt_tr->Integral());
            b_bdt_te->Scale(1/b_bdt_te->Integral());  u_bdt_te->Scale(1/u_bdt_te->Integral());  c_bdt_te->Scale(1/c_bdt_te->Integral());
        }

        cout<<"Start drawing."<<endl;
        if (drawOutput) {
            TCanvas *c;
            if (g_multiClassification) {
                c = new TCanvas("canvas","canvas",1500,1000);
                c->Divide(3,2);
                c->cd(1);
                b_pb_tr -> Draw("hist");  u_pb_tr -> Draw("histsame"); c_pb_tr -> Draw("histsame");
                b_pb_te -> Draw("esame"); u_pb_te -> Draw("esame");    c_pb_te -> Draw("esame");
                c->cd(2);
                b_pu_tr -> Draw("hist");  u_pu_tr -> Draw("histsame"); c_pu_tr -> Draw("histsame");
                b_pu_te -> Draw("esame"); u_pu_te -> Draw("esame");    c_pu_te -> Draw("esame");
                c->cd(3);
                b_pc_tr -> Draw("hist");  u_pc_tr -> Draw("histsame"); c_pc_tr -> Draw("histsame");
                b_pc_te -> Draw("esame"); u_pc_te -> Draw("esame");    c_pc_te -> Draw("esame");

                c->cd(4); gPad->SetLogy();
                b_pb_tr -> Draw("hist");  u_pb_tr -> Draw("histsame"); c_pb_tr -> Draw("histsame");
                b_pb_te -> Draw("esame"); u_pb_te -> Draw("esame");    c_pb_te -> Draw("esame");
                c->cd(5); gPad->SetLogy();
                b_pu_tr -> Draw("hist");  u_pu_tr -> Draw("histsame"); c_pu_tr -> Draw("histsame");
                b_pu_te -> Draw("esame"); u_pu_te -> Draw("esame");    c_pu_te -> Draw("esame");
                c->cd(6); gPad->SetLogy();
                b_pc_tr -> Draw("hist");  u_pc_tr -> Draw("histsame"); c_pc_tr -> Draw("histsame");
                b_pc_te -> Draw("esame"); u_pc_te -> Draw("esame");    c_pc_te -> Draw("esame");
            }
            else {
                c = new TCanvas("canvas","canvas",1200,900);
                gStyle -> SetOptStat(0);

                double max=b_bdt_tr->GetBinContent(b_bdt_tr->GetMaximumBin());
                max= max<b_bdt_te->GetBinContent(b_bdt_te->GetMaximumBin()) ? b_bdt_te->GetBinContent(b_bdt_te->GetMaximumBin()): max;
                max= max<u_bdt_tr->GetBinContent(u_bdt_tr->GetMaximumBin()) ? u_bdt_tr->GetBinContent(u_bdt_tr->GetMaximumBin()): max;
                max= max<u_bdt_te->GetBinContent(u_bdt_te->GetMaximumBin()) ? u_bdt_te->GetBinContent(u_bdt_te->GetMaximumBin()): max;
                max= max<c_bdt_tr->GetBinContent(c_bdt_tr->GetMaximumBin()) ? c_bdt_tr->GetBinContent(c_bdt_tr->GetMaximumBin()): max;
                max= max<c_bdt_te->GetBinContent(c_bdt_te->GetMaximumBin()) ? c_bdt_te->GetBinContent(c_bdt_te->GetMaximumBin()): max;

                b_bdt_tr->SetMaximum(max*1.2);
                b_bdt_tr -> Draw("hist");  u_bdt_tr -> Draw("histsame"); c_bdt_tr -> Draw("histsame");
                b_bdt_te -> Draw("esame"); u_bdt_te -> Draw("esame");    c_bdt_te -> Draw("esame");

                cout<<b_bdt_tr->GetName()<<": "<<b_bdt_tr->GetEntries()<<"\t"<< u_bdt_tr -> GetName()<<": "<<u_bdt_tr->GetEntries()<<"\t"<< c_bdt_tr -> GetName()<<": "<<c_bdt_tr->GetEntries()<<endl;
                cout<<b_bdt_te->GetName()<<": "<<b_bdt_te->GetEntries()<<"\t"<< u_bdt_te -> GetName()<<": "<<u_bdt_te->GetEntries()<<"\t"<< c_bdt_te -> GetName()<<": "<<c_bdt_te->GetEntries()<<endl;
            }
            if (c) c->SaveAs(g_trainName+".overtrainCheck.eps");//if (c) c->SaveAs(trainName+".overtrainCheck.eps");
        }

        return;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void makePDF(map<int,TTree*> map_trees) {//PDF for weighting

        cout<<"makePDF *** Start preparing the histograms for weighting."<<endl;

        //const double jptbins[] = {20 , 30 , 60 , 140, 300, 500};//*** KM: calibration binning in mistag-calib 2014 (not the same in high pt)
        //const double jptbins[] = {20 , 30, 45 , 60 ,90, 140, 300, 500};//*** KM: calibration binning in mistag-calib 2014 (not the same in high pt)
        //const double jptbins[] = {20 , 30 , 40 , 50 , 60 , 75, 90, 110, 140, 200, 500};//*** KM: calibration binning in PDF-ttbar-calib 2014
        const double jptbins[] = {10,20 , 30 , 40 , 50 , 60 , 75, 90, 110, 140, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 420, 440, 460, 480, 500, 520,540,560,580,600,620,640,660,680,700,720,740,760,780,800,820,840,860,880,900,920,940,960,980,1000,1100,1200,2000 };//*** KM: calibration binning in PDF-ttbar-calib 2014
        const double etabins[] = { 0., 0.7, 1.5, 2.5 };//*** KM: calibration binning in PDF-ttbar-calib 2014
        const int    nptbins   = sizeof(jptbins)/sizeof(jptbins[0]);
        const int    netabins  = sizeof(etabins)/sizeof(etabins[0]);

        //                                  2   2   2   2   2   3   3   3   3   4   4   5   5   7.5  7.5 10  10   15   15   20   25   30   50   50  100  100
        //const double fine_jptbins[] = {20, 22, 24, 26, 28, 30, 33, 36, 39, 42, 46, 50, 55, 60, 67.5, 75, 85, 95, 110, 125, 145, 170, 200, 250, 300, 400, 500};
        const double fine_jptbins[] = {5,10,20 , 30 , 40 , 50 , 60 , 75, 90, 110, 130, 150,170,190,210, 230, 250, 260, 280, 300, 320, 340, 360, 380, 400, 420, 440, 460, 480, 500, 520,540,560,580,600,620,640,660,680,700,720,740,760,780,800,820,840,860,880,900,920,940,960,980,1000,1100,1200,2000 };//*** KM: calibration binning in PDF-ttbar-calib 2014
        const double fine_etabins[] = { 0, 0.25, 0.5,  0.8, 1.2, 1.75, 2.5 };
        //                                 0.25  0.25  0.3  0.4  0.55  0.75
        const int    fine_nptbins   = sizeof(fine_jptbins)/sizeof(fine_jptbins[0]);
        const int    fine_netabins  = sizeof(fine_etabins)/sizeof(fine_etabins[0]);

        // const double trk_jptbins[] = {5, 10, 15, 20 , 30 , 40 , 50 , 60 , 75, 90, 110, 140, 200, 500};//*** KM: calibration binning in PDF-ttbar-calib 2014 + low pt range
        // const double trk_etabins[] = { 0., 0.7, 1.5, 2.5 };                                           //*** KM: calibration binning in PDF-ttbar-calib 2014 + low pt range
        // const int    trk_nptbins   = sizeof(trk_jptbins)/sizeof(trk_jptbins[0]);
        // const int    trk_netabins  = sizeof(trk_etabins)/sizeof(trk_etabins[0]);

        //EM jet for uncalibrated pt/eta pt>10 cos of the label
        //const double uCalib_jptbins[] = {5, 10, 15, 20 , 30 , 40 , 50 , 60 , 75, 90, 110, 140, 200, 500};//*** KM: calibration binning in PDF-ttbar-calib 2014 + low pt range
        const double uCalib_jptbins[] = {5, 10, 15, 20 , 30 , 40 , 50 , 60 , 75, 90, 110, 130, 150, 170, 190, 210, 230, 250, 270, 290, 310, 330, 350, 370, 390, 410, 430, 450, 470, 490, 510, 530, 550, 570, 590, 610, 630, 650, 670, 690, 710, 730, 750, 770, 790, 810, 830, 850, 870, 890, 910, 930, 950, 970, 990, 1010, 1040, 1100, 1200, 1300, 1400, 1600};//*** KM: calibration binning in PDF-ZprimeFlat-calib 2016
        const double uCalib_etabins[] = { 0., 0.7, 1.5, 2.5 };                                           //*** KM: calibration binning in PDF-ttbar-calib 2014 + low pt range
        const int    uCalib_nptbins   = sizeof(uCalib_jptbins)/sizeof(uCalib_jptbins[0]);
        const int    uCalib_netabins  = sizeof(uCalib_etabins)/sizeof(uCalib_etabins[0]);

        // b_pt=    new TH1F("b_pt","b_pt",nptbins-1, &jptbins[0]);
        // c_pt=    new TH1F("c_pt","c_pt",nptbins-1, &jptbins[0]);
        // u_pt=    new TH1F("u_pt","u_pt",nptbins-1, &jptbins[0]);
        if (g_binsConf4Weight==1) {
            b_pteta= new TH2F("b_pteta","b_pteta",fine_nptbins-1, &fine_jptbins[0], fine_netabins-1, &fine_etabins[0]);// b_pteta= new TH2F("b_pteta","b_pteta",100, 0, 500, fine_netabins-1, &fine_etabins[0]);
            c_pteta= new TH2F("c_pteta","c_pteta",fine_nptbins-1, &fine_jptbins[0], fine_netabins-1, &fine_etabins[0]);// c_pteta= new TH2F("c_pteta","c_pteta",100, 0, 500, fine_netabins-1, &fine_etabins[0]);
            u_pteta= new TH2F("u_pteta","u_pteta",fine_nptbins-1, &fine_jptbins[0], fine_netabins-1, &fine_etabins[0]);// u_pteta= new TH2F("u_pteta","u_pteta",100, 0, 500, fine_netabins-1, &fine_etabins[0]);
        }
        // else if (g_binsConf4Weight==2) {
        //   b_pteta= new TH2F("b_pteta","b_pteta",trk_nptbins-1, &trk_jptbins[0], trk_netabins-1, &trk_etabins[0]);
        //   c_pteta= new TH2F("c_pteta","c_pteta",trk_nptbins-1, &trk_jptbins[0], trk_netabins-1, &trk_etabins[0]);
        //   u_pteta= new TH2F("u_pteta","u_pteta",trk_nptbins-1, &trk_jptbins[0], trk_netabins-1, &trk_etabins[0]);
        // }
        else if (g_binsConf4Weight==2 or g_binsConf4Weight==3) {
            b_pteta= new TH2F("b_pteta","b_pteta",uCalib_nptbins-1, &uCalib_jptbins[0], uCalib_netabins-1, &uCalib_etabins[0]);
            c_pteta= new TH2F("c_pteta","c_pteta",uCalib_nptbins-1, &uCalib_jptbins[0], uCalib_netabins-1, &uCalib_etabins[0]);
            u_pteta= new TH2F("u_pteta","u_pteta",uCalib_nptbins-1, &uCalib_jptbins[0], uCalib_netabins-1, &uCalib_etabins[0]);
        }
        else {
            b_pteta= new TH2F("b_pteta","b_pteta",nptbins-1, &jptbins[0], netabins-1, &etabins[0]);
            c_pteta= new TH2F("c_pteta","c_pteta",nptbins-1, &jptbins[0], netabins-1, &etabins[0]);
            u_pteta= new TH2F("u_pteta","u_pteta",nptbins-1, &jptbins[0], netabins-1, &etabins[0]);
        }

        //Projection  // map_trees[5]->Project(b_pt->GetName(),"pt/1000.");  // map_trees[4]->Project(c_pt->GetName(),"pt/1000.");  // map_trees[0]->Project(u_pt->GetName(),"pt/1000.");





        //Old configuration 
        map_trees[5]->Project(b_pteta->GetName(),"abs("+etaVarName+"):"+ptVarName+"/1e3",g_apply_cWeight?"cWeight(ip2_pu,jf_sig3,sv1_mass)==1":"");
        map_trees[0]->Project(u_pteta->GetName(),"abs("+etaVarName+"):"+ptVarName+"/1e3",g_apply_cWeight?"cWeight(ip2_pu,jf_sig3,sv1_mass)==1":"");
        if (g_use_c) map_trees[4]->Project(c_pteta->GetName(),"abs("+etaVarName+"):"+ptVarName+"/1e3",g_apply_cWeight?"cWeight(ip2_pu,jf_sig3,sv1_mass)==1":"");
        TString hi;

        b_pt=b_pteta->ProjectionX("b_pt");b_pt->SetLineColor(kRed);
        c_pt=c_pteta->ProjectionX("c_pt");c_pt->SetLineColor(kGreen);
        u_pt=u_pteta->ProjectionX("u_pt");u_pt->SetLineColor(kBlue);
        b_eta=b_pteta->ProjectionY("b_eta");b_eta->SetLineColor(kRed);
        c_eta=c_pteta->ProjectionY("c_eta");c_eta->SetLineColor(kGreen);
        u_eta=u_pteta->ProjectionY("u_eta");u_eta->SetLineColor(kBlue);



        b_pt->Scale(1/b_pt->Integral());      b_eta->Scale(1/b_eta->Integral());
        c_pt->Scale(1/c_pt->Integral());      c_eta->Scale(1/c_eta->Integral());
        u_pt->Scale(1/u_pt->Integral());      u_eta->Scale(1/u_eta->Integral());
        u_pt-> SetMinimum(0);                 u_eta-> SetMinimum(0);	  
        u_pt-> SetMaximum(0.35);		u_eta-> SetMaximum(0.5);

        b_pteta-> Scale(1/b_pteta->Integral());
        c_pteta-> Scale(1/c_pteta->Integral());
        u_pteta-> Scale(1/u_pteta->Integral());



        if (drawPtEta) {
            TCanvas *c = new TCanvas("canvas","canvas",1200,1000);
            c->Divide(2,4);
            gStyle->SetOptStat(0);

            // TH2F *ratio_ub = (TH2F*)b_pteta->Clone(); TString b_oldName=ratio_ub->GetName(); ratio_ub->SetName(b_oldName+"_ratioUB");ratio_ub->Divide(u_pteta);
            // TH2F *ratio_uc = (TH2F*)c_pteta->Clone(); TString c_oldName=ratio_uc->GetName(); ratio_uc->SetName(c_oldName+"_ratioUC");ratio_uc->Divide(u_pteta);
            TH2F *ratio_ub = (TH2F*)u_pteta->Clone(); TString b_oldName=ratio_ub->GetName(); ratio_ub->SetName(b_oldName+"_ratioUB");ratio_ub->Divide(b_pteta);
            TH2F *ratio_uc = (TH2F*)u_pteta->Clone(); TString c_oldName=ratio_uc->GetName(); ratio_uc->SetName(c_oldName+"_ratioUC");ratio_uc->Divide(c_pteta);
            c->cd(1);  u_pteta -> Draw("colz");
            c->cd(2);  u_pteta -> Draw("colz");
            c->cd(3);  b_pteta -> Draw("colz");
            c->cd(4);  c_pteta -> Draw("colz");
            c->cd(5);  ratio_ub-> Draw("colz");
            c->cd(6);  ratio_uc-> Draw("colz");
            c->cd(7);  u_pt -> Draw(""); b_pt -> Draw("same"); c_pt -> Draw("same");
            c->cd(8);  u_eta-> Draw(""); b_eta-> Draw("same"); c_eta-> Draw("same");

            c->SaveAs("/users/flosterzo/scratch/BJetTrigger/trainingMV2/ptEta.eps");
        }

        weightPDFexists=true;
        return;
    }

    map<TString,unsigned> map_bin;
    map<TString,float>    map_min;
    map<TString,float>    map_max;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void initBinMinMax() {
        TString varName="";

        varName="pt"       ; map_bin[varName]= 60;  map_min[varName]= 0;     map_max[varName]= 30000;
        varName="abs(eta)" ; map_bin[varName]= 65;  map_min[varName]= 0;     map_max[varName]= 2.6;
        varName="ip2"      ; map_bin[varName]= 100; map_min[varName]= -30;   map_max[varName]= 110;
        varName="ip2_c"    ; map_bin[varName]= 100; map_min[varName]= -30;   map_max[varName]= 50;
        varName="ip2_cu"   ; map_bin[varName]= 100; map_min[varName]= -30;   map_max[varName]= 50;
        varName="ip3"      ; map_bin[varName]= 100; map_min[varName]= -30;   map_max[varName]= 110;
        varName="ip3_c"    ; map_bin[varName]= 100; map_min[varName]= -30;   map_max[varName]= 50;
        varName="ip3_cu"   ; map_bin[varName]= 100; map_min[varName]= -30;   map_max[varName]= 50;
        varName="sv1"      ; map_bin[varName]= 60;  map_min[varName]= -10;   map_max[varName]= 20;
        varName="sv1_c"    ; map_bin[varName]= 60;  map_min[varName]= -10;   map_max[varName]= 20;
        varName="sv1_cu"   ; map_bin[varName]= 60;  map_min[varName]= -10;   map_max[varName]= 20;
        varName="sv1_ntkv" ; map_bin[varName]= 22;  map_min[varName]= -2;    map_max[varName]= 20;
        varName="sv1_n2t"  ; map_bin[varName]= 101; map_min[varName]= -1;    map_max[varName]= 100;
        varName="sv1_mass" ; map_bin[varName]= 90;  map_min[varName]= -1000; map_max[varName]= 8000;
        varName="sv1_efrc" ; map_bin[varName]= 100; map_min[varName]= -1.0;  map_max[varName]= 1.0;
        varName="sv1_Lxy"  ; map_bin[varName]= 50;  map_min[varName]= -100;  map_max[varName]= 100;
        varName="sv1_L3d"  ; map_bin[varName]= 100; map_min[varName]= -100;  map_max[varName]= 100;
        varName="sv1_sig3" ; map_bin[varName]= 100; map_min[varName]= -150;  map_max[varName]= 1000;
        varName="sv1_dR"   ; map_bin[varName]= 100; map_min[varName]= -1;    map_max[varName]= 10;
        varName="jfc"      ; map_bin[varName]= 50;  map_min[varName]= -10;   map_max[varName]= 10;
        varName="jf_n2tv"  ; map_bin[varName]= 51;  map_min[varName]= -1;    map_max[varName]= 50;
        varName="jf_nvtx"  ; map_bin[varName]= 11;  map_min[varName]= -1;    map_max[varName]= 10;
        varName="jf_nvtx1t"; map_bin[varName]= 11;  map_min[varName]= -1;    map_max[varName]= 10;
        varName="jf_ntrkv" ; map_bin[varName]= 21;  map_min[varName]= -1;    map_max[varName]= 20;
        varName="jf_efrc"  ; map_bin[varName]= 110; map_min[varName]= -1.1;  map_max[varName]= 1.1;
        varName="jf_mass"  ; map_bin[varName]= 100; map_min[varName]= -1500; map_max[varName]= 10000;
        varName="jf_sig3"  ; map_bin[varName]= 100; map_min[varName]= 0;     map_max[varName]= 100;
        varName="jf_dR"    ; map_bin[varName]= 100; map_min[varName]= -1;     map_max[varName]= 1;


        varName="jet_width";          map_bin[varName] = 50; map_min[varName] = 0;   map_max[varName] = 0.5;
        varName="jet_n_trk_sigd0cut"; map_bin[varName] = 9;  map_min[varName] = -.5; map_max[varName] = 8.5;
        varName="jet_trk3_d0sig";     map_bin[varName] = 50; map_min[varName] = -5;  map_max[varName] = 11;
        varName="jet_trk3_z0sig";     map_bin[varName] = 50; map_min[varName] = -5;  map_max[varName] = 11;
        varName="jet_sv_scaled_efc";  map_bin[varName] = 50; map_min[varName] = 0;   map_max[varName] = 4;
        varName="jet_jf_scaled_efc";  map_bin[varName] = 50; map_min[varName] = 0;   map_max[varName] = 4;

    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void check_inputs(vector<TString> s_variables, map<int,TTree*> map_trees) {
        initBinMinMax();

        TTree* t0= map_trees[0];
        TTree* t4= map_trees[4];
        TTree* t5= map_trees[5];



        //for (unsigned i=0; i<s_variables.size(); i++) cout<<s_variables[i]<<endl;
        const unsigned nCanvas = s_variables.size()>9 ? s_variables.size()/9+1 : 1;
        cout<<"Number of canvases: "<<nCanvas<<endl;
        vector<TCanvas*> c;
        c.resize(nCanvas);

        for (unsigned i=0; i<c.size(); i++) {
            c[i] = new TCanvas("name" +TString::Format("%d",i),
                    "title"+TString::Format("%d",i),
                    1200, 900 );
            c[i]->Divide(3,3);
        }

        for (unsigned logON=0; logON<2; logON++) {
            TString logStr = logON ? "_log" : "";
            for (unsigned iv=0; iv<s_variables.size(); iv++) {
                unsigned c_index=0;
                for (unsigned ic=0; ic<c.size(); ic++) {
                    if (iv<9*(ic+1)){
                        c_index=ic;
                        break;
                    }
                }
                c[c_index]->cd(iv%9+1);      //c[c_index]->SetLogy();

                if (!logON) cout<<iv<<"/"<<s_variables.size()<<"\t"<<s_variables[iv]<<"\t"<<map_bin[s_variables[iv]]<<"\t"<<map_min[s_variables[iv]]<<"\t"<<map_max[s_variables[iv]]<<"\t canvasIdx= "<<c_index<<"\t padIdx= "<<iv%9+1<<endl;

                //TH1F *hb = new TH1F(s_variables[iv]+"_b", s_variables[iv]+"_b", map_bin[s_variables[iv]], map_min[s_variables[iv]], map_max[s_variables[iv]]);
                TH1F *hb = new TH1F(s_variables[iv]+"_b"+logStr, s_variables[iv]+"_b", map_bin[s_variables[iv]], map_min[s_variables[iv]], map_max[s_variables[iv]]);
                TH1F *hu = new TH1F(s_variables[iv]+"_u"+logStr, s_variables[iv]+"_u", map_bin[s_variables[iv]], map_min[s_variables[iv]], map_max[s_variables[iv]]);
                TH1F *hc = new TH1F(s_variables[iv]+"_c"+logStr, s_variables[iv]+"_c", map_bin[s_variables[iv]], map_min[s_variables[iv]], map_max[s_variables[iv]]);

                TString projectionStr = s_variables[iv];
                //TString options       = s_weight+ ( s_cuts!="" ? "*":"") + s_cuts;
                TString options       = g_weightExp;
                //if (projectionStr.EndsWith("mass")) projectionStr+="/1000.";
                //if (projectionStr=="jf_mass") projectionStr+="/1000.";
                t5->Project(hb->GetName(),projectionStr,options);  hb->SetLineColor(kRed);   hb->Scale(1/hb->Integral());
                t0->Project(hu->GetName(),projectionStr,options);  hu->SetLineColor(kBlue);  hu->Scale(1/hu->Integral());
                t4->Project(hc->GetName(),projectionStr,options);  hc->SetLineColor(kGreen); hc->Scale(1/hc->Integral());

                double max = hb->GetMaximum();
                if (max<hc->GetMaximum()) max = hc->GetMaximum();
                if (max<hu->GetMaximum()) max = hu->GetMaximum();
                hb->SetMaximum(max*1.2);
                hb->GetXaxis()->SetTitle(s_variables[iv]);

                if (logON) gPad->SetLogy();
                hb->Draw();
                hc->Draw("same");
                hu->Draw("same");
            }
            for (unsigned i=0; i<c.size(); i++) c[i]->SaveAs(g_trainName+TString::Format(".%d",i)+logStr+".eps");//SaveAs(trainName+TString::Format(".%d",i)+logStr+".eps");
        }
        // for (int i=0; i<c.size(); i++) {
        //   for (int ip=1; ip<=9; ip++) {c[i]->cd(ip);    c[i]->GetSelectedPad()->SetLogy(); /*c[i]->Update();*/ }
        //   c[i]->SaveAs(trainName+TString::Format(".%d",i)+"_log.png");
        // }



    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void MulticlassTrainer( TString trainName, TString inputDir="", TString jetCollection="AntiKt4EMTopoJets") {
        max_good[  5]=0;max_bad[  5]=0;max_good[  0]=0;max_bad[  0]=0;max_good[  4]=0;max_bad[  4]=0;
        max_good[105]=0;max_bad[105]=0;max_good[100]=0;max_bad[100]=0;max_good[104]=0;max_bad[104]=0;

        g_trainName = trainName;
        g_jetCollection=jetCollection;

        if (trainName.Contains("/")) {
            string tmp=trainName.Data();
            trainName=tmp.substr(tmp.rfind("/")+1,tmp.length()-(tmp.rfind("/")+1));
        }

        if (trainName.EndsWith(".varlist")) {
            trainName.ReplaceAll(".varlist","");
        }

        cout<<"***** MulticlassTrainer ***** Run MulticlassTrainer: "<<trainName<<endl;
        if (inputDir.BeginsWith("~")) {
            cerr<<"ROOT is NOT compatible with this shortcut form, please use the full path. Aborting."<<endl;
            return;
        }

        /*** discriminate which trees to be used ***/
        TSystemDirectory dir(inputDir,inputDir);
        TList *files = dir.GetListOfFiles();
        TString firstFileName;
        if (files) {
            TSystemFile *afile;
            TIter next(files);
            while ((afile = (TSystemFile*)next())) {//picks up the first root file
                firstFileName = afile->GetName();
                if (firstFileName.EndsWith(".root")) {
                    break;
                }
            }
        }

        cout<<"***** MulticlassTrainer ***** trying to guess tree name from file " << firstFileName << "\n";

        TFile *tmpfile = TFile::Open(inputDir+"/"+firstFileName,"read");
        TString treeName = "bTag";
        TTree *tmp_tree= (TTree*) tmpfile->Get(treeName);
        if (!tmp_tree) {
            treeName = "bTag_"+jetCollection;
            tmp_tree= (TTree*) tmpfile->Get(treeName);
        }  //cout<<tmp_tree->GetName()<<endl;
        delete files; delete tmp_tree;  delete tmpfile;

        /*** Preparation of the TChain ***/
        TChain * tree = new TChain(treeName);
        cout<<"***** MulticlassTrainer ***** Reading ntuples from: "<<inputDir+"/*.root*"<<endl;
        tree->Add(inputDir+"/*.root*");
        cout<<"***** MulticlassTrainer ***** TreeName: "<<tree->GetName()<<" with "<<tree->GetEntries()<<" events"<<endl;

        /*** Discriminate multi-classification or not ***/
        g_multiClassification = !trainName.Contains("_bin_");

        /*** Determine signal background to train ***/
        if ( trainName.Contains("_cSig_")  ) g_sigBkg="cub";

        /*** Determine bin configuration for the weighting ***/
        if ( trainName.Contains("_finW_")  ) g_binsConf4Weight = 1;
        if ( trainName.Contains("TrackJet")) g_binsConf4Weight = 2;
        if ( trainName.Contains("_uCalib_")) g_binsConf4Weight = 3;

        /********** Reading variables list from txt(.varlist) file **********/
        TString varFileName="weights/"+trainName+".varlist";
        cout<<"***** MulticlassTrainer ***** Opening variable list file: "<<varFileName<<endl;
        ifstream tmp_ifs(varFileName.Data());
        if (tmp_ifs.fail()) {
            cerr<<"Failure when reading a file: "<<varFileName<<endl;
            varFileName="./"+trainName+".varlist";
        }
        ifstream ifs(varFileName.Data());
        string aLine;
        vector<TString> varlist,vartype;
        if (ifs.fail()) {
            cerr<<"Failure when reading a file: "<<varFileName<<endl;
            return;
        }
        else {
            while (getline(ifs,aLine)) {
                //cout<<aLine<<endl;
                TString ts_aLine=aLine.data();
                if (ts_aLine.BeginsWith("#")) continue;
                TString var =aLine.substr(0,aLine.find(","));
                TString type=aLine.substr(aLine.size()-1,aLine.size());
                //cout<<var<<"\t"<<type<<endl;
                if      (var.Contains("_uCalib")) ptVarName="pt_uCalib", etaVarName="eta_uCalib";
                else if (var.Contains("_calib")) 	ptVarName="pt_calib",  etaVarName="eta_calib";
                varlist.push_back(var);
                vartype.push_back(type);
            }
        }//  return;

        // This loads the library
        TMVA::Tools::Instance();

        // to get access to the GUI and all tmva macros
        TString tmva_dir= TString(gRootDir)+"/tmva";
        if(gSystem->Getenv("TMVASYS")) tmva_dir = TString(gSystem->Getenv("TMVASYS"));
        gROOT->SetMacroPath(tmva_dir + "/test/:" + gROOT->GetMacroPath() );
        // gROOT->ProcessLine(".L TMVAMultiClassGui.C+");
        gROOT->ProcessLine(".L TMVAClassification.C+");

        std::cout << std::endl
            << "==> Start "<<(g_multiClassification?"TMVAMulticlass":"TMVAClassification")<< std::endl;

        // Create a new root output file.
        const TString outputDir = "weights/";
        const TString outfileName = outputDir+trainName+".root";
        TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

        TString factoryOption = (TString)"!V:!Silent:!Color:!DrawProgressBar:AnalysisType="+( g_multiClassification ? "multiclass" : "classification");
        TMVA::Factory *factory = new TMVA::Factory( trainName, outputFile, factoryOption );

        /********** Asigning variables to TMVA **********/
        for (unsigned ivar=0; ivar<varlist.size(); ivar++) {
            if      (vartype.at(ivar)=="F") factory->AddVariable(varlist.at(ivar), 'F');
            else if (vartype.at(ivar)=="I") factory->AddVariable(varlist.at(ivar), 'I');
            else if (vartype.at(ivar)=="D") factory->AddVariable(varlist.at(ivar), 'F');
            //cout<<"\t"<<varlist[ivar]<<endl;
        }  //return;
        //factory->AddSpectator("label"); // FLS

        cout<<"***** MulticlassTrainer ***** Training configuration: ";

        TString stat="100k";
        string string2search="_stat";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            string tmpName = s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            stat=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            cout<<"stat= "<<stat;//<<endl;  //return;
        }

        TString goodStat=stat; 
        string2search="_goodStat";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            string tmpName = s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            goodStat=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            cout<<", goodStat= "<<goodStat;//<<endl;  //return;
        }
        TString badStat=goodStat;
        unsigned gStat = goodStat.ReplaceAll("k","000").Atoi();
        max_good[  5]=gStat, max_good[  0]=gStat;
        max_good[105]=gStat, max_good[100]=gStat;

        string2search="_badStat";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            string tmpName = s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            badStat=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            cout<<", badStat= "<<badStat;//<<endl; //return;
        } 
        const unsigned bStat = badStat.ReplaceAll("k","000").Atoi();
        max_bad[  5]=bStat                 , max_bad[0]=bStat;
        max_bad[105]= doTesting ? bStat : 0, max_bad[100]= doTesting ? bStat : 0;
        const float badStatRatio= bStat/gStat;

        string2search="_jvt";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            string tmpName = s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            TString jvtCut=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            if (jvtCut.BeginsWith("0")) jvtCut.ReplaceAll("0","0.");
            g_jvtCut= jvtCut.Atof();
            cout<<", jvtCut= "<<g_jvtCut;//<<endl;
        }  //return;

        string2search="_jvf";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            string tmpName = s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            TString jvtCut=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            if (jvtCut.BeginsWith("0")) jvtCut.ReplaceAll("0","0.");
            g_jvfCut= jvtCut.Atof();
            cout<<", jvfCut= "<<g_jvfCut;//<<endl;
        }  //return;

        string2search="_puCut";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            string tmpName = s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            TString puCut=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            g_puCut= puCut.Atof();
            cout<<", puCut= "<<g_puCut;//<<endl;
        }  //return;

        if (g_jvfCut!=-2 and g_jvtCut!=-1) {
            cerr<<"Requiring both JVT & JVF!! "<<"g_jvfCut= "<<g_jvfCut<<", g_jvtCut= "<< g_jvtCut<<", aborting..."<<endl;
            exit(1);
        }

        // FLS : for hybrid tuning
        string2search = "_HybridTune";
        if(trainName.Contains(string2search)) {
            g_doHybridTuning = true;
        }

        /***** truth matching requirement *****/
        if      (trainName.Contains("_tm1_")) g_requireTruthMatch=1;
        else if (trainName.Contains("_tm0_")) g_requireTruthMatch=0;
        else if (trainName.Contains("_tm_") ) g_requireTruthMatch=1;
        cout<<", requireTruthMatch= "<<g_requireTruthMatch;//<<endl;
        //return;

        /***** randomly mix the samples for train/test *****/
        if      (trainName.Contains("_mix1")) g_mixSamples=true;
        else if (trainName.Contains("_mix0")) g_mixSamples=false;
        else if (trainName.Contains("_mix") ) g_mixSamples=true;
        cout<<", randomMix= "<<g_mixSamples;//<<endl;  

        /***** make inclusively collected samples for train/test *****/
        if      (trainName.Contains("_inclT1")) g_doInclusiveTraining=true;
        else if (trainName.Contains("_inclT") ) g_doInclusiveTraining=true;
        cout<<", doInclusiveTraining= "<<g_doInclusiveTraining;//<<endl;

        /***** use full statistics or not, yet half of stat though... *****/
        if      (trainName.Contains("_maxStat1_")) g_useMaxStat=1;
        else if (trainName.Contains("_maxStat0_")) g_useMaxStat=0;
        else if (trainName.Contains("_maxStat_") ) g_useMaxStat=1;
        cout<<",  useFullStat= "<<g_useMaxStat;//<<endl;

        // ********** statistics configuation **********
        TString cStat="100k"; 
        string2search="_cStat";
        if(trainName.Contains(string2search)) {
            string s_tName= trainName.Data();
            string tmpName= s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            cStat=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            cout<<", cStat= "<<cStat;//<<endl; //return;
        } 

        TString cGoodStat=cStat;
        string2search="_cGoodStat";
        if(trainName.Contains(string2search)) {
            string s_tName= trainName.Data();
            string tmpName= s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            cGoodStat=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            cout<<", cGoodStat= "<<cGoodStat;//<<endl; //return;
        } 
        unsigned cstat = cGoodStat.ReplaceAll("k","000").Atoi();
        max_good[  4]=cstat                , max_bad[  4]=cstat*badStatRatio;
        max_good[104]= doTesting ? cstat: 0, max_bad[104]=doTesting ? cstat*badStatRatio : 0;

        float cFrac=0;
        string2search="_c";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            TString tmp= s_tName.substr(s_tName.rfind(string2search)+2, s_tName.size() - s_tName.rfind(string2search) ).data();
            cFrac= tmp.Atoi()*1e-2;
            g_use_c=cFrac>0;
            cout<<", cFrac= "<<cFrac<<endl;//return;
        }
        if (not(0<=cFrac and cFrac<1)) {
            cerr<<"cFrac="<<cFrac<<" out of range!! Aborting..."<<endl;exit(1);
        }


        if (trainName.Contains("_cOnly")) g_noUse_u = 1;

        /************************************/
        /*** BDT configuration parameters ***/
        /************************************/
        TString depth="3",    nTrees="1000",    mns="5",    nCuts="20",    trf="",    abb="";

        /*** node purity limit configuration ***/
        string2search="_MNS";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            string tmpName = s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            mns=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            if (mns.BeginsWith("0")) {
                string tmp_mns = mns.Data();
                mns = "0."+tmp_mns.substr(1,tmp_mns.length());//mns.ReplaceAll("0","0.");
            }
            //cout<<"mns="<<mns<<endl;
        }

        /*** depth configuration ***/
        string2search="_depth";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            string tmpName = s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            depth=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            //cout<<"depth="<<depth<<endl;
            int int_depth = depth.Atoi();
        }

        // *** nTrees configuration
        string2search="_nTrees";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            string tmpName = s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.length());
            nTrees=s_tName.substr(s_tName.find(string2search)+string2search.length(), tmpName.find("_")).data();
            //cout<<"nTrees="<<nTrees<<endl;
        }

        /*** nCuts configuration ***/
        string2search="_cuts";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            nCuts=s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.size()-(s_tName.find(string2search)+string2search.length())).find("_")).data();
            //cout<<"cuts="<<nCuts<<endl;
        }

        /*** Ada boost beta configuration ***/
        string2search="_abb";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            abb=s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.size()-(s_tName.find(string2search)+string2search.length())).find("_")).data();
            abb = TString::Format("%.2f", 0.01*abb.Atof() );
            //cout<<"abb= "<<abb<<"\t"<<endl;
        }

        /*** variable transformation configuration ***/
        string2search="_trf";
        if(trainName.Contains(string2search)) {
            string s_tName=trainName.Data();
            trf=s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.substr(s_tName.find(string2search)+string2search.length(), s_tName.size()-(s_tName.find(string2search)+string2search.length())).find("_")).data();
            //cout<<"trf= "<<trf<<"\t"<<trf.Length()<<endl;

            if (not(trf.Contains("N") or trf.Contains("D") or trf.Contains("G") or trf.Contains("P") or trf.Contains("b") or trf.Contains("s"))) {
                cout<<"Unrecognized character given for transformation. trf= "<<trf<<" Aborting..."<<endl;
                return;
            }

            vector<TString> trf_components;
            for (int i_trf=0; i_trf < trf.Length(); i_trf++) {
                string s_trf = trf.Data();
                trf_components.push_back(s_trf.substr(i_trf,1));
                //cout<<s_trf.substr(i_trf,1)<<endl;
            }

            trf="";
            for ( unsigned i_trf=0; i_trf<trf_components.size(); i_trf++) {
                TString toAdd="";
                if (trf_components[i_trf]=="G" or trf_components[i_trf]=="D" or trf_components[i_trf]=="N" or trf_components[i_trf]=="P") toAdd= trf_components[i_trf];
                else if (trf_components[i_trf]=="b") 											toAdd= "_Background";
                else if (trf_components[i_trf]=="s") 											toAdd= "_Signal";
                else {
                    cout<<"Unrecognized character found for transformation. Aborting..."<<endl;
                    return;
                }
                if (i_trf<trf_components.size()-1) {
                    if (trf_components[i_trf]=="b" or trf_components[i_trf]=="s") toAdd+="+";
                    else {
                        if (trf_components[i_trf+1]=="N" or trf_components[i_trf+1]=="D" or trf_components[i_trf+1]=="G" or trf_components[i_trf+1]=="P") toAdd+="+";
                    }
                }
                trf += toAdd;
            }
            //cout<<"TRF= "<<trf<<endl;
        }  //return;

        TString weightType = "r";
        g_weightType=weightType;
        if      (trainName.Contains("_f_")       )  weightType= "f";
        else if (trainName.Contains("_r_")       )  weightType= "r";
        else if (trainName.Contains("_fPt_")     ) {weightType= "f"; var4weight="Pt"    ;}
        else if (trainName.Contains("_fPtEta_")  ) {weightType= "f"; var4weight="PtEta" ;}
        else if (trainName.Contains("_rPt_")     ) {weightType= "r"; var4weight="Pt"    ;}
        else if (trainName.Contains("_rPtEta_")  ) {weightType= "r"; var4weight="PtEta" ;}

        //////////////////////////////////////////////////////////////////////////////////////////////////////
        gROOT->cd( outfileName+":/" );
        cout<<"***** MulticlassTrainer ***** Collecting events (jets) for training... "<<endl;

        map<int,TTree*> map_trees=  prepareTtEventsFromEvt(factory, tree);
        //////////////////////////////////////////////////////////////////////////////////////////////////////

        //KM: if no training is needed, terminate: only the transformation from event level ntuple to jet level one.
        if (trainName.Contains("_0tr_")) {outputFile->Close();  return;}

        TString weightExp= trainName.Contains("_noWeight_") ? "": weightType+"Weight("+ptVarName+","+etaVarName+",label)";//set weight 
        if      (trainName.Contains("_cWeight_") ) g_apply_cWeight=1;
        else if (trainName.Contains("_ncWeight_")) g_apply_cWeight=0;

        if (g_apply_cWeight) weightExp+="*cWeight(ip2_pu,jf_sig3,sv1_mass)";  //old configuration

        //if (g_apply_cWeight) weightExp+="*cWeight(ip2_pu,jf_sig3,sv1_mass,jf_mass,jf_efrc,jf_nvtx,jf_nvtx1t,jf_ntrkv,jf_n2tv)"; 
        // if (g_apply_cWeight) weightExp+="*cWeight(ip2_pu,jf_sig3,sv1_mass,sv1_ntkv,sv1_n2t,sv1_sig3,sv1_efrc)"; 



        g_weightExp=weightExp;

        makePDF(map_trees);//for weighting


        if (checkInputs) check_inputs(varlist,map_trees);
        if (drawOutput) outputPDFs(map_trees);
        if(drawPtEta or checkInputs or drawOutput) return;

        cout<<"***** MulticlassTrainer ***** Applying weight function: \'"<<weightExp<<"\'"<<endl;  //return;

        TString className5="sig5", className4="bkg4", className0="bkg0";
        if (!g_multiClassification) {
            if      (g_sigBkg.BeginsWith("b")) className5="Signal"    , className4="Background", className0="Background";
            else if (g_sigBkg.BeginsWith("c")) className5="Background", className4="Signal"    , className0="Background";
            else { cerr<<"Unrecognized string for sigBkg= "<<g_sigBkg<<". Aborting..."<<endl; exit(1); }
            cout<<"***** MulticlassTrainer ***** Adding trees for binary-classification. Sinal and backgrounds: "<<g_sigBkg<<endl;  
        }
        else cout<<"***** MulticlassTrainer ***** Adding trees for multi-classification."<<endl;  

        b_weight_pteta= new TH1F("b_weight","",100,0,10);
        c_weight_pteta= new TH1F("c_weight","",100,0,10);
        u_weight_pteta= new TH1F("u_weight","",100,0,10); // FLS

        const TString train_str = "train";
        const TString test_str  = "test";

        factory->AddTree(map_trees[5],className5,1,"",train_str);  factory->SetWeightExpression(weightExp,className5);
        if (!g_noUse_u) {
            factory->AddTree(map_trees[0],className0,1,"",train_str);  factory->SetWeightExpression(weightExp,className0);
        }
        if (g_use_c) {
            factory->AddTree(map_trees[4],className4,1,"",train_str);  factory->SetWeightExpression(weightExp,className4);
        }

        if (doTesting) {
            factory->AddTree(map_trees[105],className5,1,"",test_str);  //factory->SetWeightExpression(weightExp,className5);
            if (!g_noUse_u) {
                factory->AddTree(map_trees[100],className0,1,"",test_str);  //factory->SetWeightExpression(weightExp,className0);
            }
            if (g_use_c) {
                factory->AddTree(map_trees[104],className4,1,"",test_str);  //factory->SetWeightExpression(weightExp,className4);
            }
        }

        if (g_sigBkg.BeginsWith("c") and  !g_use_c) {
            cerr<<"sigBkg= "<<g_sigBkg<<" contradiction to g_use_c= "<<g_use_c<<". Aborting..."<<endl;
            exit(1);
        }

        TCut preselectionCut="";//can add some selection further
        int        nTrain5= map_trees[5]->GetEntries(preselectionCut), nTrain0= map_trees[0]->GetEntries(preselectionCut), nTrain4= 0;
        if (g_noUse_u) nTrain0= 0;
        if (g_use_c  ) nTrain4= map_trees[4]->GetEntries(preselectionCut);

        if (g_correctFraction) {
            float orig_ufrac = (float)nTrain0/(nTrain0+nTrain4);
            float orig_cfrac = (float)nTrain4/(nTrain0+nTrain4);
            float uFrac= 1 - cFrac;
            g_weight4= cFrac/orig_cfrac;
            g_weight0= uFrac/orig_ufrac;
            //cout<<"g_weight0= "<<g_weight0<<", g_weight4= "<<g_weight4<<endl;
        }

        //Those 3 for multi-classification
        TString s_nTrain5= TString::Format("nTrain_sig5=%d",nTrain5);
        TString s_nTrain0= TString::Format("nTrain_bkg0=%d",nTrain0);
        TString s_nTrain4= TString::Format("nTrain_bkg4=%d",nTrain4);

        //Those 2 for binary classification
        TString s_nTrainS= TString::Format("nTrain_Signal=%d"    , g_sigBkg.BeginsWith("b") ? nTrain5         : nTrain4         );
        TString s_nTrainB= TString::Format("nTrain_Background=%d", g_sigBkg.BeginsWith("b") ? nTrain0+nTrain4 : nTrain0+nTrain5 );

        TString s_doPresel=doPreselection ? ":DoPreselection" : "";//This is automatic preselection by TMVA
        TString basicOption;

        TString splitMode="Random";  //"Block";
        if (g_multiClassification) { basicOption="SplitMode="+splitMode+":NormMode=NumEvents:!V:"+s_nTrain5+":"+s_nTrain0+(g_use_c ? ":"+s_nTrain4 : ""); }
        else                       { basicOption="SplitMode="+splitMode+":NormMode=NumEvents:!V:"+s_nTrainS+":"+s_nTrainB;
            //if (!doTesting) basicOption+="nTest_Signal=0:nTest_Backgournd=0";
        }

        TString boostType = "AdaBoost";
        if      (trainName.Contains("BdtRealAdaBoost")) boostType="RealAdaBoost";
        else if (trainName.Contains("BdtAdaBoostR2")) boostType="AdaBoostR2";
        else if (trainName.Contains("BdtBagging")) boostType="Bagging";
        else if (trainName.Contains("BdtGrad")) boostType="Grad";
        if (g_multiClassification) boostType = "Grad";

        //const TString BdtOption="!H:!V:NTrees=1000:BoostType="+boostType+shrinkage+":UseBaggedBoost:BaggedSampleFraction=0.50:nCuts="+nCuts+":MaxDepth="+depth+s_doPresel;
        const TString bdtName = "BDTG"; // TString bdtName = g_multiClassification ? "BDTG" : "BDT_bin";
        const TString shrinkage    = boostType=="Grad" ? ":Shrinkage=0.10" : "";//0.1 for default
        const TString MinNodeSize  = mns=="5"          ? ""                : ":MinNodeSize="+mns+"%";//0.2%,15% optimal for purification+1%antipurified;
        const TString Ntrees       = nTrees=="800"     ? ""                : ":NTrees="+nTrees;
        const TString transform    = trf==""           ? ""                : ":VarTransform="+trf;
        const TString adaBoostBeta = abb==""           ? ""                : ":AdaBoostBeta="+abb;

        boostType   = boostType=="AdaBoost" ? "" :":BoostType="+boostType;
        depth       = depth=="3"            ? "" :":MaxDepth="+depth;
        nCuts       = nCuts=="20"           ? "" :":nCuts="+nCuts;

        const TString BdtOption="!H:!V"+boostType+shrinkage+Ntrees+nCuts+depth+s_doPresel+adaBoostBeta+MinNodeSize+transform;
        cout<<"***** MulticlassTrainer ***** TMVA training option: "<<endl
            <<"\t"<<basicOption<<endl
            <<"\t"<<BdtOption  <<endl
            <<endl;  //return;



        factory->PrepareTrainingAndTestTree( preselectionCut, basicOption );//CAUTION: weight must be set before this!!
        factory->BookMethod( TMVA::Types::kBDT, bdtName, BdtOption );  
        b_weight_pteta->Write();
        c_weight_pteta->Write();
        u_weight_pteta->Write(); // FLS
        factory->TrainAllMethods();     // ---- Train MVAs using the set of training events
        if (doTesting) {


            factory->TestAllMethods();    // ---- Evaluate all MVAs using the set of test events


            factory->EvaluateAllMethods();// ---- Evaluate and compare performance of all configured MVAs
        }
        outputFile->Close();// Save the output

        cout << "==> Wrote root file: " << outputFile->GetName() << endl
            << "==> TVAVAClassification is done!" <<endl;

        delete factory;

        // Launch the GUI for the root macros
        if (!gROOT->IsBatch()) {
            if (doTesting) gSystem->Load("BDTControlPlots_C.so");
            if (g_multiClassification) TMVA::TMVAMultiClassGui( outfileName.Data() ); 
            //else TMVAGui( outfileName );
            // if (mvaName.Contains("_bin_")) TMVAMultiClassGui( outfileName );
            //TMVAGui( outfileName );
        }

        cout	    << "==> To check the training/testing results, run the command below."<<endl
            <<"root \'"<<(g_multiClassification?"TMVAMultiClassGui":"TMVAGui")<<".C+(\""<<outputFile->GetName()<<"\")\'"<< endl;

        return;
    }
