#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "TSystem.h"
#include "TFile.h"
#include "TKey.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TPaveText.h"
#include "TLatex.h"
#include "TText.h"
#include "TLegend.h"
#include "TMath.h"
#include "TStopwatch.h"

#include "tools/RejectionTool.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

#include "tools/variable.h"

using std::cout;
using std::cerr;
using std::endl;
using std::map;
using std::vector;
using std::string;

//TString __directory;
const bool doJetEventLoop=1;

static const double jptbins[11] = { 20., 30., 40., 50., 60., 75., 90., 110., 140., 200., 500. };
static const double etabins[5] = { 0., 0.6, 1.2, 1.8, 2.5 };

const int nptbins=sizeof(jptbins)/sizeof(jptbins[0]);
const int netabins=sizeof(etabins)/sizeof(etabins[0]);

void ATLAS_LABEL(Double_t x,Double_t y,Color_t color=1);
void myText(TString txt, float x1, float y1, float x2, float y2, float tsize=0.045);

map<TString,variable> map_inputVars;
map<TString,variable> map_taggedVars;

TMVA::Reader *reader=0;

//strings for projection
string commaVariablesList="";
string s_nVars;

vector<float> inputVariablesTMVA; //for TMVA, must be float
vector<TString> s_inputVariables;

const TString mvaString = "BDTG";

TString g_mvaName;
TString g_mSwitch;

void initializeReader(TString mvaName) {

  TString varFileName="weights/"+mvaName+".varlist";
  ifstream ifs(varFileName.Data());
  string aLine;
  vector<TString> varlist,vartype;
  if (ifs.fail()) {
    cerr<<"Failure when reading a file: "<<varFileName<<endl;
    exit(1);//    return;
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
      commaVariablesList+=var;
      commaVariablesList+=",";
      variable tmp;
      tmp.type_=type;
      map_inputVars[var]=tmp;
    }
  }
  s_inputVariables=varlist;

  commaVariablesList=commaVariablesList.substr(0,commaVariablesList.length()-1);

  reader = new TMVA::Reader( "!Color:!Silent" );
  
  TString path2xml = "weights/"+mvaName+"_"+mvaString+".weights.xml";

  inputVariablesTMVA.resize(varlist.size());
  s_nVars=TString::Format("%d,",(int)varlist.size()).Data();
  
  for (unsigned ivar=0; ivar<varlist.size(); ivar++) {
    reader -> AddVariable ( varlist.at(ivar)     , &(inputVariablesTMVA.at(ivar))      );
  }

  std::cout<<"Reading xml file from \t"<<path2xml<<std::endl
	   <<"With calling string \t"<<mvaString<<std::endl;
  
  reader -> BookMVA(mvaString, path2xml);    //reader[i] -> BookMVA(methodName,path2xml);
}


const bool debugmode=0;
int  numOut   =0;
vector<float> evalMulticlass(vector<double> inputs) {

  // if (inputs.size()!=nVars) {
  //   cerr<<"Number of input variables is inconsistent to initialization.Aborting.."<<endl;
  //   exit(1);
  // }
  
  for (unsigned i=0; i<inputs.size(); i++) {
    inputVariablesTMVA[i] = inputs[i];
    if (debugmode or numOut<100) cout<<s_inputVariables[i]<<"= "<<inputs[i]<<"\t";
  }
  
  vector<float> outputs;
  if (reader) {
    if (g_mvaName.Contains("_bin_")) {//binary-class
      outputs.push_back(reader->EvaluateMVA( mvaString ) );//if (mvaString.Contains("bin")) outputs.push_back(reader->EvaluateMVA( mvaString ) );
      if (debugmode or numOut<100 ) cout<<"BDT= "<<outputs[0]<<endl;
    }
    else {//multiclass
      outputs = reader->EvaluateMulticlass( mvaString );
      if (debugmode or numOut<100 ) cout<<"pb+pu+pc= "<<outputs[0]<<"+"<<outputs[1]<<"+"<<outputs[2]<<"= "<<outputs[0]+outputs[1]+outputs[2]<<endl;
    }
  }
  else {
    cerr<<"MVA tool isn't initilized yet!! Aborting..."<<endl;
    exit(1);
  }
  
  numOut++;
  return outputs;
}

unsigned nPrint=0;
const unsigned maxPrint=100;
float ReadBDTMVXeval ( int nVars, double variable, ...) {

  vector<double> inputVars;
  // variable arguments part///////////////////////
  double letter= variable;
  va_list args;
  va_start( args, variable );
  for(int i=0; i<nVars;i++) {
    letter=va_arg(args,double);
    inputVars.push_back(letter);
  }
  va_end(args);
  ////////////////////////////////////////////////

  if (nPrint==0) {
    for (int i=0; i<nVars; i++) cout<<s_inputVariables[i]<<"\t";
    cout<<endl;
  }
  for (int i=0; i<nVars; i++) {
    if (nPrint<maxPrint) cout<<inputVars[i]<<"\t";    
  }
  
  float mlp = 0;
  vector<float> outputs = evalMulticlass(inputVars);
  float pb=outputs[0], pu=outputs[1], pc=outputs[2];
  if (nPrint<maxPrint) { cout<<"pb+pu+pc= "<<pb<<" + "<<pu<<" + "<<pc<<" = "<<pb+pu+pc<<endl; nPrint++;}
  
  if (pu>0 and pc>0) mlp = log(pb*pb/pc/pu);
  cout<<"ReadBDTMVXeval= "<<mlp<<endl;

  //if(reader) mlp = reader->EvaluateMVA( "TMVAMulticlass" );
  return mlp;
}

map<TString,bool> map_switch;
vector<int> v_skip;
// define taggers here:             #   0   ,   1  ,   2 ,    3     ,   4 ,    5      ,      6         ,  7  ,      8      ,   9     ,   10     ,   11   ,   12   ,   13   ,  14    ,   15      
const string  BTagPerf_TagLName[] = { "IP2D","IP3D","SV1","IP3D+SV1","SV0","JetFitter","IP3D+JetFitter","SV2","SoftMuonTag", "MV1"   , "MV1c"   ,"MV2c00","MV2c10","MV2c20", "MV2m" ,  "MVX"    };//display name for legend
const string  BTagPerf_TagSName[] = { "ip2" ,"ip3" ,"sv1",  "cmb"   ,"sv0",  "jft"    ,  "jfc"         ,"sv2",    "smt"    , "mv1"   , "mv1c"   ,"mv2c00","mv2c10","mv2c20", "mv2m" ,  "MVX"    };//variable name in minibtag
const int     BTagPerf_BinMode[]  = {   0   ,  0   ,  0  ,    0     ,  2  ,   0       ,    5           ,  0  ,      0      ,   7     ,   3      ,   6    ,   6    ,   6    ,   5    ,    3      };
const TString v_varType[]         = {  "D"  , "D"  , "D" ,   "D"    , "D" ,   "D"     ,   "D"          , "D" ,     "D"     ,  "D"    ,  "F"     ,  "F"   ,  "F"   ,  "F"   ,  "F"   ,   "D"     };
//possibility for SetBranchAddress: #   X   ,  X   ,  X  ,    X     ,  X  ,    X      ,    O           ,  X  ,      X      ,   O     ,   O      ,   O    ,   O    ,   O        O    ,    X       
bool skip[]                       = {   1   ,  1   ,  1  ,    1     ,  1  ,    1      ,    1           ,  1  ,      1      ,   1     ,   1      ,   1    ,   1    ,   1    ,   1    ,    0      };
int lcol[]                        = {   6   ,  3   ,  4  ,    1     , 14  ,   30      ,    2           , 48  ,     50      ,kOrange+1,kMagenta+2,  kRed  , kGreen ,  kCyan ,kMagenta,kMagenta-2 };
int  lst[]                        = {   2   ,  2   ,  3  ,    2     ,  3  ,    1      ,    1           ,  1  ,      1      ,  1      ,   4      ,   2    ,   1    ,   5    ,   5    , 1         };//line style
int lwdt[]                        = {   2   ,  2   ,  2  ,    2     ,  2  ,    2      ,    2           ,  2  ,      2      ,  2      ,   2      ,   2    ,   2    ,   2    ,   2    , 2         };//line width
static const int BTagPerf_NTag = sizeof(BTagPerf_TagLName)/sizeof(BTagPerf_TagLName[0]);

vector<unsigned> v_binMode;
vector<unsigned> v_nbins;
vector<float> v_min,v_max;
void set_binMode() {

  float lowEdge3 = g_mvaName.Contains("_cSig_") ? -1.0 : -0.5;

  v_nbins.push_back(  560); v_min.push_back(    -20.);  v_max.push_back(50.); //0: for LR taggers:      // if     (0==bin_mode) { nbins_y = 560, min_y=-20., max_y=50.; }// for LR taggers:
  v_nbins.push_back(  100); v_min.push_back(      0.);  v_max.push_back(10.); //1: for JetProb:		// else if(1==bin_mode) { nbins_y = 100, min_y=  0., max_y=10.; }// for JetProb:   
  v_nbins.push_back( 1000); v_min.push_back(    -50.);  v_max.push_back(300); //2: for SV0:		// else if(2==bin_mode) { nbins_y =1000, min_y=-50., max_y=300; }// for SV0:	     
  v_nbins.push_back( 1000); v_min.push_back(lowEdge3);  v_max.push_back(1.2); //3: for ANN or BDTG:	// else if(3==bin_mode) { nbins_y =5000, min_y= 0.5, max_y=1.2; }// for ANN or BDT:
  v_nbins.push_back( 1000); v_min.push_back(    -10.);  v_max.push_back(15.); //4:log(pb/pu)		// else if(4==bin_mode) { nbins_y =1000, min_y=-10., max_y=15.; }//log(pb/pu)	     
  v_nbins.push_back( 1000); v_min.push_back(    -15.);  v_max.push_back(20.); //5:log(pb*pb/pc/pu)	// else if(5==bin_mode) { nbins_y =1000, min_y=-15., max_y=20.; }//log(pb*pb/pc/pu)
  v_nbins.push_back( 1000); v_min.push_back(    -1. );  v_max.push_back(1. ); //6: binary BDT output
  v_nbins.push_back(10000); v_min.push_back(      0.);  v_max.push_back(1. ); //7: for MV1

  if (g_mvaName.Contains("_bin_")) {v_nbins.push_back(1000); v_min.push_back(-1.1);  v_max.push_back( 1.1);}
  //else                             {v_nbins.push_back(1000); v_min.push_back(-15 );  v_max.push_back( 25 );}
  else                             {v_nbins.push_back(1000); v_min.push_back(-10 );  v_max.push_back( 10 );}
  
  return;
}

//define flavors here:
const string BTagPerf_Flavor[] = { "b", "c", "u" , "t"};
const int    BTagPerf_FlavorLabel[] = {  5 ,  4 ,  0  , 15 };
const int BTagPerf_NFlv = sizeof(BTagPerf_Flavor)/sizeof(BTagPerf_Flavor[0]);
TString flavcut[BTagPerf_NFlv] = { "label==5", "label==4", "label<4", "label==15" };
//TString flavcut[BTagPerf_NFlv] = { "label==5", "label<4", "label<4&&drb>0.8&&drc>0.8&&drt>0.8" };//light purification

// define signals and backgrounds here together with operating points
int tagLabel=5;
vector<string> v_Signal      ;
vector<string> v_Background  ;
vector<double> v_OP          ;
vector<string> v_OPname      ;

// define configurations here:
static const string BTagPerf_ConfName[] = { "std" };
const int BTagPerf_NCnf = sizeof(BTagPerf_ConfName)/sizeof(BTagPerf_ConfName[0]);

void prepare_map_taggedVars() {
  cout<<"prepare_map_taggedVars: "<<"preparing map for tagger variables."<<endl;
  for (int it=0; it<BTagPerf_NTag; it++) {
    if(v_skip[it]) continue;//    if(skip[it]) continue;
    
    //in order to avoid overwrite the address for input variables of MVX
    bool skipFlag=false;
    for (unsigned ii=0; ii<s_inputVariables.size(); ii++) {
      if      (BTagPerf_TagSName[it]==s_inputVariables[ii]) skipFlag=true;
    }
    if (skipFlag) continue;

    variable tmpVar;

    cout<<BTagPerf_TagSName[it]<<"\t"<<v_varType[it]<<endl;

    if (BTagPerf_TagSName[it]=="mv2m") {
      // for (unsigned i=0; i<triout.size(); i++) {
      // 	string tmp=triout.at(i);
      // 	tmpVar.type_=v_varType[it];
      // 	map_taggedVars[BTagPerf_TagSName[it]+tmp]=tmpVar;
      // }
    }
    else {
      //cout<<BTagPerf_TagSName[it]<<"\t"<<v_varType[it]<<endl;
      tmpVar.type_=v_varType[it];
      map_taggedVars[BTagPerf_TagSName[it]]=tmpVar;
    }
  }
}

vector<TString> getListOfKeys(TFile *f0) {
  TList *klist = f0->GetListOfKeys();  
  vector<TString> tmp;tmp.clear();
  for (int ik=0; ik<klist->GetSize();ik++) {
    TKey *key = (TKey*)klist->At(ik);
    tmp.push_back(key->GetName());
  }
  return tmp;
}

bool autoSkipFlaggingDONE=false;
void autoSkipFlagging(TFile *f0) {
  if (autoSkipFlaggingDONE) return;
  autoSkipFlaggingDONE=true;
  vector<TString> nameList = getListOfKeys(f0);
  for(unsigned i=0;i<nameList.size();i++) {
    TString objName=nameList[i];
    //cout<<objName<<endl;
    for (int it=0;it<BTagPerf_NTag;it++) {
      if(objName.Contains(BTagPerf_TagSName[it])) v_skip[it]=false;
    }
  }
}

//bool      load_PbPcPu=false;
const TString mvaLoadPrefix="";

//*** for perf range ***
//const string useCalibPtEta="pt";
const string useCalibPtEta="pt_calib";
//const string useCalibPtEta="pt_uCalib";

//*** for mva evaluation ***
//const string usePtEta="";
const string usePtEta="uCalib";
//const bool usePtEta="calib";

map<TString,TH1F*> map_hist1D;
map<TString,TH2F*> map_hist2D;
////////////////////////////////////////////////////////////////////////////////////////////////
void Analysis(TTree *tree) {
  bool debugOption=0;
  const   long nBreakup= -1e4;
  
  //*** histograms booking
  for (int it=0; it<BTagPerf_NTag; it++) {
    if (v_skip[it]) continue;//if (skip[it]) continue;

    for (int iflv=0; iflv<BTagPerf_NFlv; iflv++) {//set_binMode(BTagPerf_BinMode[it],nbins,min,max);
      //unsigned nbins= BTagPerf_TagSName[it]!="mv1" ? v_nbins[BTagPerf_BinMode[it]] : 5000;
      unsigned nbins=v_nbins[v_binMode[it]];//[BTagPerf_BinMode[it]];
      float min     =v_min  [v_binMode[it]];//[BTagPerf_BinMode[it]];  
      float max     =v_max  [v_binMode[it]];//[BTagPerf_BinMode[it]];
      //1D
      TString histName=BTagPerf_Flavor[iflv]+"_"+BTagPerf_TagSName[it];
      map_hist1D[histName] = new TH1F(histName,histName,nbins,min,max);
      
      //2D vs pt
      histName=BTagPerf_Flavor[iflv]+"_"+BTagPerf_TagSName[it]+"_vsPt";
      map_hist2D[histName] = new TH2F(histName,histName,nptbins-1,&jptbins[0],nbins,min,max);
      
      //2D vs eta
      histName=BTagPerf_Flavor[iflv]+"_"+BTagPerf_TagSName[it]+"_vsEta";
      map_hist2D[histName] = new TH2F(histName,histName,netabins-1,&etabins[0],nbins,min,max);
    }
  }

  //*** Setting branch addresses
  //pt, eta
  int label=0,ntk_ass=0;
  double pt=0, eta=0;
  double c_pt=0, c_eta=0;
  double uc_pt=0, uc_eta=0;
  tree->SetBranchAddress("label"  , &label  );
  tree->SetBranchAddress("pt"     , &pt     );
  tree->SetBranchAddress("eta"    , &eta    );

  tree->SetBranchAddress("pt_calib"     , &c_pt     );
  tree->SetBranchAddress("eta_calib"    , &c_eta    );
  tree->SetBranchAddress("pt_uCalib"     , &uc_pt     );
  tree->SetBranchAddress("eta_uCalib"    , &uc_eta    );
  //tree->SetBranchAddress("ntk_ass",&ntk_ass );

  float pb=0, pc=0, pu=0;
  // if (load_PbPcPu) {
  //   tree->SetBranchAddress(mvaLoadPrefix+"pb",&pb );
  //   tree->SetBranchAddress(mvaLoadPrefix+"pc",&pc );
  //   tree->SetBranchAddress(mvaLoadPrefix+"pu",&pu );
  // }

  float mv2m_pb=0, mv2m_pc=0, mv2m_pu=0;

  //tagged variables
  prepare_map_taggedVars(); 
  for (int it=0; it<BTagPerf_NTag; it++) {
    if(v_skip[it]) continue;//if(skip[it]) continue;
    if      (BTagPerf_TagSName[it]=="MVX" ) continue;
    else if (BTagPerf_TagSName[it]=="mv2m") {
      tree->SetBranchAddress("mv2m_pb",&mv2m_pb );
      tree->SetBranchAddress("mv2m_pc",&mv2m_pc );
      tree->SetBranchAddress("mv2m_pu",&mv2m_pu );
    }
    else {
      if      (map_taggedVars[BTagPerf_TagSName[it]].type_=="F") tree->SetBranchAddress(BTagPerf_TagSName[it].data(), &map_taggedVars[BTagPerf_TagSName[it]].float_ );
      else if (map_taggedVars[BTagPerf_TagSName[it]].type_=="I") tree->SetBranchAddress(BTagPerf_TagSName[it].data(), &map_taggedVars[BTagPerf_TagSName[it]].int_   );
      else if (map_taggedVars[BTagPerf_TagSName[it]].type_=="D") tree->SetBranchAddress(BTagPerf_TagSName[it].data(), &map_taggedVars[BTagPerf_TagSName[it]].double_);
    }
  }
  
  //MVX input vars
  for (unsigned ivar=0; ivar<s_inputVariables.size(); ivar++) {
    if(s_inputVariables[ivar]=="pt") continue;
    if(s_inputVariables[ivar]=="pt_calib") continue;
    if(s_inputVariables[ivar]=="pt_uCalib") continue;
    if(s_inputVariables[ivar]=="eta") continue;
    if(s_inputVariables[ivar]=="eta_calib") continue;
    if(s_inputVariables[ivar]=="eta_uCalib") continue;
    if(s_inputVariables[ivar]=="abs(eta)") continue;
    if(s_inputVariables[ivar]=="abs(eta_calib)") continue;
    if(s_inputVariables[ivar]=="abs(eta_uCalib)") continue;
    
    if      (map_inputVars[s_inputVariables[ivar]].type_=="F") tree->SetBranchAddress(s_inputVariables[ivar], &map_inputVars[s_inputVariables[ivar]].float_ );
    else if (map_inputVars[s_inputVariables[ivar]].type_=="I") tree->SetBranchAddress(s_inputVariables[ivar], &map_inputVars[s_inputVariables[ivar]].int_   );
    else if (map_inputVars[s_inputVariables[ivar]].type_=="D") tree->SetBranchAddress(s_inputVariables[ivar], &map_inputVars[s_inputVariables[ivar]].double_);
    else { cerr<<"Something wrong with variable list. Aborting..."<<endl; exit(1);}
  }

  float ipx_pu,ipx_pb,ipx_pc;
  float ipxJf_pu,ipxJf_pb,ipxJf_pc;
  float ipxJfSv_pu,ipxJfSv_pb,ipxJfSv_pc;
  double jf_mass;
  int ip2_isvalid,svp_isvalid;
  
  TStopwatch sw;
  //*** event loop starts **********************************************************************************************
  for (long ievt=0;ievt<tree->GetEntries();ievt++) {
    if      (ievt==0 ) cout<<"Starting JetEventLoop Process: "<<tree->GetEntries()<<" events."<<endl;
    else if (ievt<1e5 and ievt%(long)1e4==0) {cout<<"JetEventLoop: "<<ievt<<" events processed so far:\t"<<(float)100*ievt/tree->GetEntries()<<"%. ";sw.Print();sw.Start(0);}
    else if (ievt<1e6 and ievt%(long)1e5==0) {cout<<"JetEventLoop: "<<ievt<<" events processed so far:\t"<<(float)100*ievt/tree->GetEntries()<<"%. ";sw.Print();sw.Start(0);}
    else if (             ievt%(long)1e6==0) {cout<<"JetEventLoop: "<<ievt<<" events processed so far:\t"<<(float)100*ievt/tree->GetEntries()<<"%. ";sw.Print();sw.Start(0);}
    
    if (ievt==nBreakup) {
      cout<<nBreakup<<" events collected, break up the loop"<<endl;
      break;
    }

    tree->GetEntry(ievt);//access tree contents in this event

    float pt4perf, eta4perf;
    if (useCalibPtEta=="pt_calib") {
      pt4perf  =c_pt;
      eta4perf =c_eta;
    }
    else if (useCalibPtEta=="pt_uCalib") {
      pt4perf  =uc_pt;
      eta4perf =uc_eta;
    }
    else {
      pt4perf  =pt;
      eta4perf =eta;
    }

    if (not(pt4perf>20000. and fabs(eta4perf)<2.5)) continue;
    if (debugOption)cout<<"label,pt,eta= "<<label<<"\t"<<pt4perf/1000.<<"\t"<<eta4perf<<"\t\t";
    
    float mva_pb=-20, mva_pu=-20, mva_pc=-20;
    float output=-100;
    bool isNanOrInf=false;
    if (reader) {
      vector<double> input_vars;
      for (unsigned ivar=0; ivar<s_inputVariables.size(); ivar++) {
	float pt2feed=pt, eta2feed=eta;
	if      (usePtEta=="calib")  pt2feed=c_pt,  eta2feed=c_eta;
	else if (usePtEta=="uCalib") pt2feed=uc_pt, eta2feed=uc_eta;
	// if      (s_inputVariables[ivar]=="pt" ) input_vars.push_back(pt);
	// else if (s_inputVariables[ivar]=="eta") input_vars.push_back(eta);
	// else if (s_inputVariables[ivar]=="abs(eta)") input_vars.push_back(fabs(eta));
	if      (s_inputVariables[ivar]=="pt"             ) input_vars.push_back(pt2feed);
	else if (s_inputVariables[ivar]=="pt_calib"       ) input_vars.push_back(pt2feed);
	else if (s_inputVariables[ivar]=="pt_uCalib"      ) input_vars.push_back(pt2feed);

	else if (s_inputVariables[ivar]=="eta"            ) input_vars.push_back(eta2feed);
	else if (s_inputVariables[ivar]=="eta_calib"      ) input_vars.push_back(eta2feed);
	else if (s_inputVariables[ivar]=="eta_uCalib"     ) input_vars.push_back(eta2feed);

	else if (s_inputVariables[ivar]=="abs(eta)"       ) input_vars.push_back(fabs(eta2feed));
	else if (s_inputVariables[ivar]=="abs(eta_calib)" ) input_vars.push_back(fabs(eta2feed));
	else if (s_inputVariables[ivar]=="abs(eta_uCalib)") input_vars.push_back(fabs(eta2feed));
	else {
	  double input_variable;
	  if      (map_inputVars[s_inputVariables[ivar]].type_=="F") input_variable= map_inputVars[s_inputVariables[ivar]].float_ ;
	  else if (map_inputVars[s_inputVariables[ivar]].type_=="I") input_variable= map_inputVars[s_inputVariables[ivar]].int_   ;
	  else if (map_inputVars[s_inputVariables[ivar]].type_=="D") input_variable= map_inputVars[s_inputVariables[ivar]].double_;
	  else { cerr<<"Something wrong with variable list. Aborting..."<<endl; exit(1);}

	  if (std::isnan(input_variable) or std::isinf(input_variable)) {
	    input_vars.push_back(-1000);
	    isNanOrInf=true;
	    cerr<<"nan/inf is detected for the variable name= "<<s_inputVariables[ivar]<<endl;
	  }
	  else                                                input_vars.push_back(input_variable);
	}
      }

      vector<float> output_vars=evalMulticlass(input_vars);
      if (g_mvaName.Contains("_bin_")) output=output_vars[0];//if (mvaString.Contains("bin")) output=output_vars[0];
      else {
	mva_pb=output_vars[0], mva_pu=output_vars[1], mva_pc=output_vars[2];
	//cout<<"pb+pu+pc= "<<mva_pb<<" + "<<mva_pu<<" + "<<mva_pc<<"= "<<mva_pb+mva_pu+mva_pc<<endl;
      }
    }
    if (isNanOrInf) {
      output=-999;
      if (ievt<10000) cout<<"nan/inf detected, assigning BDT= -999."<<endl;
    }
    
    //*** filling variables into histos ***
    TString s_flav="u";//This means tau falls in 0
    for (int iflv=0; iflv<BTagPerf_NFlv; iflv++) {                             // if      (label==0) s_flav="u";
      if (label==BTagPerf_FlavorLabel[iflv]) s_flav=BTagPerf_Flavor[iflv];     // else if (label==4) s_flav="c";
    }									       // else if (label==5) s_flav="b";

    // if (label==15) {
    //   if(ntk_ass==1 or ntk_ass==3) continue;
    // }
    
    for (int it=0; it<BTagPerf_NTag; it++) {
      if(v_skip[it]) continue;//      if(skip[it]) continue;
      
      float var2fill = 0;
      if (BTagPerf_TagSName[it]=="MVX") {
	if      (g_mvaName.Contains("_bin_") ) var2fill=output;//mvaString.Contains("bin") ) var2fill=output;
	else {
	  if      (tagLabel==5)  {
	    if     (g_mSwitch=="buc" ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pb/(mva_pc+mva_pu))      : -20;
	    else if(g_mSwitch=="bbuc") var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pb*mva_pb/mva_pc/mva_pu) : -20;
	    else if(g_mSwitch=="bu"  ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pb/mva_pu)               : -20;
	    else if(g_mSwitch=="bc"  ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pb/mva_pc)               : -20;
	  }
	  else if (tagLabel==4) {
	    if     (g_mSwitch=="cub" ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pc/(mva_pb+mva_pu))      : -20;
	    else if(g_mSwitch=="ccub") var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pc*mva_pc/mva_pb/mva_pu) : -20;
	    else if(g_mSwitch=="cb"  ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pc/mva_pb)               : -20;
	    else if(g_mSwitch=="cu"  ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pc/mva_pu)               : -20;
	  }
	}
      }
      else {
	if (BTagPerf_TagSName[it]=="mv2m") {
	  float mva_pb=mv2m_pb,mva_pc=mv2m_pc,mva_pu=mv2m_pu;

	  if (ievt<10)cout<<"Debug: pb,pu,pc= "<<mva_pb<<", "<<mva_pu<<", "<<mva_pc<<endl;
	  if      (tagLabel==5)  {
	    if     (g_mSwitch=="buc" ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pb/(mva_pc+mva_pu))      : -20;
	    else if(g_mSwitch=="bbuc") var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pb*mva_pb/mva_pc/mva_pu) : -20;
	    else if(g_mSwitch=="bu"  ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pb/mva_pu)               : -20;
	    else if(g_mSwitch=="bc"  ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pb/mva_pc)               : -20;
	  }
	  else if (tagLabel==4) {
	    if     (g_mSwitch=="cub" ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pc/(mva_pb+mva_pu))      : -20;
	    else if(g_mSwitch=="ccub") var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pc*mva_pc/mva_pb/mva_pu) : -20;
	    else if(g_mSwitch=="cb"  ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pc/mva_pb)               : -20;
	    else if(g_mSwitch=="cu"  ) var2fill= mva_pb>0 and mva_pc>0 and mva_pu>0 ? log(mva_pc/mva_pu)               : -20;
	  }
	}
	else {
	  if      (map_taggedVars[BTagPerf_TagSName[it]].type_=="F") var2fill= map_taggedVars[BTagPerf_TagSName[it]].float_ ;
	  else if (map_taggedVars[BTagPerf_TagSName[it]].type_=="I") var2fill= map_taggedVars[BTagPerf_TagSName[it]].int_   ;
	  else if (map_taggedVars[BTagPerf_TagSName[it]].type_=="D") var2fill= map_taggedVars[BTagPerf_TagSName[it]].double_;
	}
      }
      
      if (debugOption) cout<<"Filling variable: "<<s_flav+"_"+BTagPerf_TagSName[it]<<"\t"<<var2fill<<endl;
      TString histName     = s_flav+"_"+BTagPerf_TagSName[it];
      TString histName_vpt = s_flav+"_"+BTagPerf_TagSName[it]+"_vsPt";
      TString histName_veta= s_flav+"_"+BTagPerf_TagSName[it]+"_vsEta";
      map_hist1D[histName]->Fill(var2fill);
      map_hist2D[histName_vpt ]->Fill(pt4perf/1000,var2fill);
      map_hist2D[histName_veta]->Fill(fabs(eta4perf),var2fill);
    }// tagger loop
  }//end of event loop
  cout<<"Elapsed time for histograming: ";sw.Stop();sw.Print();
  
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void createRejHistos(TString infname = "minibtag.root", TString oufname = "hists", TString usercut="", bool skipProjectionIfDone=true) {
  std::cout<<"reading input tree from file: "<<infname<<std::endl;//__directory+infname<<std::endl;
  TFile* inf = new TFile(infname, "read");// TFile(__directory+infname, "read");
  oufname=oufname+".root"; //oufname+="_"+__directory+".root"; 
  
  std::cout<<"writing histos to file: "<<oufname<<std::endl;
  
  // if (!gSystem->AccessPathName(oufname)) {
  //   cout<<"File: "<<oufname<<" already exists! Skipping projection."<<endl;
  //   return;
  // }
  TFile* ouf = new TFile(oufname, "update");// "recreate");
  if(ouf->IsZombie()) {
    cout<<"File: "<<oufname<<" is zombie, replacing with new file."<<endl;
    //exit(1);
    ouf = new TFile(oufname, "recreate");
  }

  string tit;
  const int icfn = 0;
  // book histos:
  TH1F* hh[BTagPerf_NTag][BTagPerf_NFlv];
  TH2F* hhpt[BTagPerf_NTag][BTagPerf_NFlv];
  TH2F* hheta[BTagPerf_NTag][BTagPerf_NFlv];

  for(int itag=0; itag<BTagPerf_NTag; itag++) {
    map_switch[BTagPerf_TagSName[itag]]= !v_skip[itag];//!skip[itag];
    if(v_skip[itag]) continue;//if(skip[itag]) continue;

    for(int iflv=0; iflv<BTagPerf_NFlv; iflv++) {
      unsigned nbinsY=v_nbins[v_binMode[itag]];
      float Ymin     =v_min  [v_binMode[itag]];
      float Ymax     =v_max  [v_binMode[itag]];
      
      tit="btagperf_" + BTagPerf_Flavor[iflv] + "_" + BTagPerf_TagSName[itag] + "_" + BTagPerf_ConfName[icfn];
      if((TH1F*)ouf->Get(tit.data()) and skipProjectionIfDone) hh[itag][iflv] = 0;//new TH1F(tit.c_str(), tit.c_str(), nbinsX, Ymin., Ymax.);
      else {
	hh[itag][iflv] = new TH1F(tit.c_str(), tit.c_str(), nbinsY, Ymin, Ymax);
	hh[itag][iflv]->Sumw2();
      }
      
      tit="btagperfVSpt_" + BTagPerf_Flavor[iflv] + "_"  + BTagPerf_TagSName[itag] + "_" + BTagPerf_ConfName[icfn];
      if((TH1F*)ouf->Get(tit.data()) and skipProjectionIfDone) hhpt[itag][iflv] = 0;
      else {
	hhpt[itag][iflv] = new TH2F(tit.c_str(), tit.c_str(), nptbins-1,&jptbins[0], nbinsY, Ymin, Ymax);
	hhpt[itag][iflv]->Sumw2();
      }

      tit="btagperfVSeta_" + BTagPerf_Flavor[iflv] + "_" + BTagPerf_TagSName[itag] + "_" + BTagPerf_ConfName[icfn];
      if((TH1F*)ouf->Get(tit.data()) and skipProjectionIfDone) hheta[itag][iflv] = 0;
      else {
	hheta[itag][iflv] = new TH2F(tit.c_str(), tit.c_str(), netabins-1,&etabins[0], nbinsY, Ymin, Ymax);
	hheta[itag][iflv]->Sumw2();
      }

    }//flavor loop
  }//tagger loop
  
  // extract from tree:
  TTree* t = (TTree*)inf->Get("minibtag");//Get("TestTree");
  if(!t) {
    cerr<<"Tree TestTree not found in file: "<<inf->GetName()<<" Aborting."<<endl;
    exit(1);
  }
  
  TString cuts = "pt>20000.&&abs(eta)<2.5&&";

  cuts+=usercut;
  
  bool histogramToBeMade=false;
  for(int itag=0; itag<BTagPerf_NTag; itag++) {
    if(v_skip[itag]) continue;//if(skip[itag]) continue;
    for(int iflv=0; iflv<BTagPerf_NFlv; iflv++) {

      if (!hh[itag][iflv] and !hhpt[itag][iflv] and !hheta[itag][iflv] and skipProjectionIfDone) {
	cout<<"No histogram to be filled for "<<BTagPerf_TagSName[itag]<<", skipping."<<endl;
      }
      else histogramToBeMade=true;

    }//flavor loop
  }//tagger loop
  
  if (histogramToBeMade) {
    if(doJetEventLoop) Analysis(t);

    for(int itag=0; itag<BTagPerf_NTag; itag++) {
      if(v_skip[itag]) continue;//if(skip[itag]) continue;
      string tagsname = BTagPerf_TagSName[itag];
      if      (tagsname=="MVX"    ) { tagsname="ReadBDTMVXeval("+s_nVars+commaVariablesList+")";    }

      std::cout<<"tagger= "<<tagsname<<std::endl;
      for(int iflv=0; iflv<BTagPerf_NFlv; iflv++) {
	TString selection = "("; 
      
	selection+=cuts; 
	selection+=flavcut[iflv]; 
	//selection.Append(")*evtweight");
	selection.Append(")");
	//cout<<"Starting projection: flav= "<<BTagPerf_Flavor[iflv]<<"\t"<<BTagPerf_TagSName[itag]<<endl;

	if (doJetEventLoop) {
	  TString histName     = BTagPerf_Flavor[iflv]+"_"+BTagPerf_TagSName[itag];
	  TString histName_vpt = BTagPerf_Flavor[iflv]+"_"+BTagPerf_TagSName[itag]+"_vsPt";
	  TString histName_veta= BTagPerf_Flavor[iflv]+"_"+BTagPerf_TagSName[itag]+"_vsEta";
	  hh[itag][iflv]   =0;  hh[itag][iflv]   = (TH1F*)map_hist1D[histName     ]->Clone( (TString)"btagperf_"      + BTagPerf_Flavor[iflv] + "_" + BTagPerf_TagSName[itag] + "_" + BTagPerf_ConfName[icfn]);
	  hhpt[itag][iflv] =0;  hhpt[itag][iflv] = (TH2F*)map_hist2D[histName_vpt ]->Clone( (TString)"btagperfVSpt_"  + BTagPerf_Flavor[iflv] + "_" + BTagPerf_TagSName[itag] + "_" + BTagPerf_ConfName[icfn]);
	  hheta[itag][iflv]=0;  hheta[itag][iflv]= (TH2F*)map_hist2D[histName_veta]->Clone( (TString)"btagperfVSeta_" + BTagPerf_Flavor[iflv] + "_" + BTagPerf_TagSName[itag] + "_" + BTagPerf_ConfName[icfn]);
	}
	else {
	  //start projections for each tagger and flavor
	  int nb = 0;

	  // 1D plot:
	  nb = t->Project(hh[itag][iflv]->GetName(), tagsname.c_str(), selection);
	  std::cout<<hh[itag][iflv]->GetName()  <<"\t"<<selection<<"\t"<<nb<<std::endl;
	  
	  // 2D pt  plots:
	  nb = t->Project(hhpt[itag][iflv]->GetName(), (tagsname+":pt/1000.").c_str(), selection);
	  std::cout<<hhpt[itag][iflv]->GetName()<<"\t"<<selection<<"\t"<<nb<<std::endl;
	  
	  // 2D eta plots:      
	  nb = t->Project(hheta[itag][iflv]->GetName(), (tagsname+":abs(eta)").c_str(), selection);
	  std::cout<<hheta[itag][iflv]->GetName()<<"\t"<<selection<<"\t"<<nb<<std::endl;
	}
	// save:
	ouf->WriteTObject(hh[itag][iflv]);
	ouf->WriteTObject(hhpt[itag][iflv]);
	ouf->WriteTObject(hheta[itag][iflv]);
	//}
	
      }// flavor loop
    }// tagger loop
  }//if histogramToBeMade
  
  ouf->Close();
  inf->Close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void createRejGraphs(TString infname = "hists", TString oufname = "graphs") {
  infname=infname+".root";//infname+="_"+__directory+".root";
  oufname=oufname+".root";//oufname+="_"+__directory+".root";
  std::cout<<"reading input histos from file: "<<infname<<std::endl;
  std::cout<<"writing graphs to file: "<<oufname<<std::endl;
  TFile* inf = new TFile(infname, "read");
  TFile* ouf = new TFile(oufname, "recreate");
  string titb, titu;//, titc, tittau;
  // loop on configurations:
  std::cout << inf << std::endl;

  map<float,float> ptRanges;// GeV!!
  ptRanges.insert(std::make_pair( 20.1,  49.9));
  ptRanges.insert(std::make_pair( 50.1, 109.9));
  ptRanges.insert(std::make_pair(110.1, 199.9));
  
  for(int icfn=0; icfn<BTagPerf_NCnf; icfn++) {
    // loop on other taggers:
    for(int itag=0; itag<BTagPerf_NTag; itag++) {
      for(unsigned isig=0; isig<v_Signal.size(); isig++) {
	for(unsigned ibkg=0; ibkg<v_Background.size(); ibkg++) {
	  if(v_skip[itag]) continue;//if(skip[itag]) continue;
	  // 1D plot:
	  titb="btagperf_"+v_Signal[isig]+"_"; titb+=BTagPerf_TagSName[itag]; titb+="_"; titb+=BTagPerf_ConfName[icfn];
	  std::cout << titb << std::endl;
	  TH1F* b = (TH1F*)inf->Get(titb.c_str());
	  // titc="btagperf_c_"; titc+=BTagPerf_TagSName[itag]; titc+="_"; titc+=BTagPerf_ConfName[icfn];
	  // TH1F* c = (TH1F*)inf->Get(titc.c_str());
	  titu="btagperf_"+v_Background[ibkg]+"_"; titu+=BTagPerf_TagSName[itag]; titu+="_"; titu+=BTagPerf_ConfName[icfn];
	  TH1F* u = (TH1F*)inf->Get(titu.c_str());
	  // tittau="btagperf_tau_"; tittau+=BTagPerf_TagSName[itag]; tittau+="_"; tittau+=BTagPerf_ConfName[icfn];
	  // TH1F* tau = (TH1F*)inf->Get(tittau.c_str());
	  RejectionTool* rejT = new RejectionTool(b, u);
	  // RejectionTool* CrejT = new RejectionTool(b, c);
	  // RejectionTool* TaurejT = new RejectionTool(b, tau);

	  //Computing rejection for light jets
	  TString name = "rejvseffT"+BTagPerf_TagSName[itag]+v_Signal[isig]+v_Background[ibkg]+"Std";
	  TGraphErrors* g = rejT->cloneRejVsEff(name);
	  ouf->WriteTObject( g );
	  // compute ratio to REF:
	  // name = "rejvseffT"; name+=BTagPerf_TagSName[itag]; name+="WRTjfc"+v_Signal[isig]+v_Background[ibkg]+"Std";
	  // ouf->WriteTObject( rejT->divide(rejTREF)->Clone(name) );
	  // print rejets:
	  //	  double r, err, w;
	  double err;

	  titb="btagperfVSpt_"+v_Signal[isig]    +"_"+BTagPerf_TagSName[itag]+"_"+BTagPerf_ConfName[icfn];
	  titu="btagperfVSpt_"+v_Background[ibkg]+"_"+BTagPerf_TagSName[itag]+"_"+BTagPerf_ConfName[icfn];
	  for (auto pt_range: ptRanges) {
	    TH2F* bpt2 = (TH2F*)inf->Get(titb.c_str());
	    TH2F* upt2 = (TH2F*)inf->Get(titu.c_str());
	    RejectionTool* rejTptDepROC = new RejectionTool(bpt2, upt2, pt_range.first,pt_range.second);
	    name = "rejvseffT"+BTagPerf_TagSName[itag]+v_Signal[isig]+v_Background[ibkg]+"Std"+"_pt"+TString::Format("%dt",(int)pt_range.first)+TString::Format("%d",(int)(pt_range.second+0.2));
	    TGraphErrors* g_ptDepROC=rejTptDepROC->cloneRejVsEff(name);
	    ouf->WriteTObject( g_ptDepROC );
	    delete rejTptDepROC;
	  }

	  for (unsigned iop=0; iop<v_OP.size(); iop++) {	  // DEBUT DU BESOIN D'OP
	    double ur, uw;
	    rejT->getRej(v_OP[iop]/100., ur, err, uw);
	    std::cout<<v_Background[ibkg]<<"-jet rejection @ "<< v_OPname[iop] <<"% for "<<BTagPerf_TagLName[itag]<<" : "<<ur<<"+-"<<err<<" (w>"<<uw<<")"<<std::endl;

	    // 2D plots:
	    /********************** vs pt performance curves **********************/
	    titb="btagperfVSpt_"+v_Signal[isig]    +"_"+BTagPerf_TagSName[itag]+"_"+BTagPerf_ConfName[icfn];
	    titu="btagperfVSpt_"+v_Background[ibkg]+"_"+BTagPerf_TagSName[itag]+"_"+BTagPerf_ConfName[icfn];
	    TH1F* bpt = (TH1F*)inf->Get(titb.c_str());//This is a little weird but it distinguish weather 1d or 2d later.
	    TH1F* upt = (TH1F*)inf->Get(titu.c_str());//This is a little weird but it distinguish weather 1d or 2d later.

	    RejectionTool* rejTpt = new RejectionTool(bpt, upt, v_OP[iop]/100., uw, ur);
	    name = "rejvspt"+v_OPname[iop]+"T"; name+=BTagPerf_TagSName[itag]; name+=v_Signal[isig]+v_Background[ibkg]+"Std";
	    ouf->WriteTObject( rejTpt->getRejVsX()->Clone(name) );

	    name = "cutvsptfixedeff"+v_OPname[iop]+"T"; name+=BTagPerf_TagSName[itag]; name+=v_Signal[isig]+v_Background[ibkg]+"Std";
	    ouf->WriteTObject( rejTpt->getCutVsX()->Clone(name) );
	    
	    name = "rejfromcutvspt"+v_OPname[iop]+"T"; name+=BTagPerf_TagSName[itag]; name+=v_Signal[isig]+v_Background[ibkg]+"Std";
	    ouf->WriteTObject( rejTpt->getRejFromCutVsX()->Clone(name) );
	    
	    name = "efffromcutvspt"+v_OPname[iop]+"T"; name+=BTagPerf_TagSName[itag]; name+=v_Signal[isig]+v_Background[ibkg]+"Std";
	    ouf->WriteTObject( rejTpt->getEffFromCutVsX()->Clone(name) );
	    
	    name = "effvspt"+v_OPname[iop]+"T"; name+=BTagPerf_TagSName[itag]; name+=v_Signal[isig]+v_Background[ibkg]+"Std";
	    ouf->WriteTObject( rejTpt->getEffVsX()->Clone(name) );

	    /********************** vs eta performance curves **********************/
	    titb="btagperfVSeta_"+v_Signal[isig]    +"_"+BTagPerf_TagSName[itag]+"_"+BTagPerf_ConfName[icfn];
	    titu="btagperfVSeta_"+v_Background[ibkg]+"_"+BTagPerf_TagSName[itag]+"_"+BTagPerf_ConfName[icfn];
	    TH1F* beta = (TH1F*)inf->Get(titb.c_str());//This is a little weird but it distinguish weather 1d or 2d later.
	    TH1F* ueta = (TH1F*)inf->Get(titu.c_str());//This is a little weird but it distinguish weather 1d or 2d later.

	    RejectionTool* rejTeta = new RejectionTool(beta, ueta, v_OP[iop]/100., uw, ur);
	    name = "rejvseta"+v_OPname[iop]+"T"; name+=BTagPerf_TagSName[itag]; name+=v_Signal[isig]+v_Background[ibkg]+"Std";
	    ouf->WriteTObject( rejTeta->getRejVsX()->Clone(name) );
	  
	    name = "rejfromcutvseta"+v_OPname[iop]+"T"; name+=BTagPerf_TagSName[itag]; name+=v_Signal[isig]+v_Background[ibkg]+"Std";
	    ouf->WriteTObject( rejTeta->getRejFromCutVsX()->Clone(name) );
	  
	    name = "efffromcutvseta"+v_OPname[iop]+"T"; name+=BTagPerf_TagSName[itag]; name+=v_Signal[isig]+v_Background[ibkg]+"Std";
	    ouf->WriteTObject( rejTeta->getEffFromCutVsX()->Clone(name) );
	  
	    name = "effvseta"+v_OPname[iop]+"T"; name+=BTagPerf_TagSName[itag]; name+=v_Signal[isig]+v_Background[ibkg]+"Std";
	    ouf->WriteTObject( rejTeta->getEffVsX()->Clone(name) );

	  }	    // FIN DU BESOIN D'OP
	}
      }
    }
    // delete rejTREF;
    // delete rejTpt60REF;
    // delete rejTpt70REF;
  }
  inf->Close();
  ouf->Close();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MyGraphCleaner(TGraph* gr, float truncateAt=1., bool debug=false, bool forceMonotonic=false, bool forceBinToBinMonotonic=false, bool rejectNullErrors=true) {
  if(0==gr) return;
  int npr=0;
  int np = gr->GetN();
  if(debug) std::cout<<"graph "<<gr->GetName()<<" has "<<np<<" points"<<std::endl;
  double eff1,rej1;
  double eff2,rej2;
  int qq = gr->GetPoint(0,eff1,rej1);
  double rejMin = rej1;
  if(forceMonotonic) {
    if(debug) std::cout<<"reference point for monotonic cleaning: "<<eff1<<" "<<rej1<<std::endl;
  }
  int nop = 0;
  for(int i=0;i<np;i++) {
    nop++;
    if(nop>np) break;
    //if(i>(np-npr)) break;
    qq = gr->GetPoint(i,eff2,rej2);
    double ex = gr->GetErrorX(i);
    double ey = gr->GetErrorY(i);
    if(debug) std::cout<<"->examining point "<<i<<" x="<<eff2<<" y="
                       <<rej2<<" ex="<<ex<<" ey="<<ey<<std::endl;
    if(eff2>truncateAt) {
      if(debug) std::cout<<"removing point "<<i<<" of "<<gr->GetName()
			 <<"b/c above truncation: "<<eff2<<std::endl;
      gr->RemovePoint(i);
      i--;
      npr++;
      continue;
    }
    if(rejectNullErrors) {
      if(ex==0&&ey==0) {
	if(debug) std::cout<<"removing point "<<i<<" of "<<gr->GetName()
			   <<"b/c null errors"<<std::endl;
	gr->RemovePoint(i);
        i--;
	npr++;
	continue;
      }
    }
    if(forceMonotonic) {
      if(rej2>rejMin) {
	if(debug) std::cout<<"removing point "<<i<<" of "<<gr->GetName()<<std::endl;
	if(debug) std::cout<<"pt "<<qq<<" "<<i<<" e="<<eff2<<" r="<<rej2
			   <<" previous min="<<rejMin<<std::endl;
	gr->RemovePoint(i);
	i--;
	npr++;
      } else {
        rejMin = rej2;
      }
    }
    if(forceBinToBinMonotonic) {
      if( ( (eff2>eff1)&&(rej2>rej1) ) ||
          ( (eff2<eff1)&&(rej2<rej1) ) ) {
	if(debug) std::cout<<"removing point "<<i<<" of "<<gr->GetName()<<std::endl;
	if(debug) std::cout<<"pt "<<qq<<" "<<i<<" e="<<eff2<<" r="<<rej2
			   <<" eprev="<<eff1<<" rejprev="<<rej1<<std::endl;
	gr->RemovePoint(i);
	i--;
	npr++;
      } else {
        eff1 = eff2;
        rej1 = rej2;
      }
    }
  }
  //gr->Print();
  std::cout<<npr<<"(/"<<np<<") points of "<<gr->GetName()<<" removed."<<std::endl;
  //gr->Sort();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void plotRejEffGraphs(TString infname="graphs", TString signal="b" , TString background="u") {
  infname=infname+".root";//infname+="_"+__directory+".root";
  std::cout<<"reading input graphs from file: "<<infname<<std::endl;
  TString extra("");
  TString type("ATLAS t#bar{t}");
  TString jet("T");

  gROOT->Macro("atlasrootlogon.C");
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
  gStyle->SetPadTickY(0);
  gStyle->SetOptStat(kFALSE);

  TFile *f = TFile::Open(infname);
  autoSkipFlagging(f);

  // Light jet rejection plot
  TGraphErrors* g[BTagPerf_NTag];
  int ifirst = -1;
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;//if(skip[it]) continue;
    if(ifirst==-1) ifirst = it;
    TString hname="rejvseffT"+BTagPerf_TagSName[it]+signal+background+"Std";
    std::cout << hname << std::endl;
    g[it] = (TGraphErrors*)f->Get(hname);
    if(it==2||it==5||it==8) MyGraphCleaner(g[it],0.9); 
    else MyGraphCleaner(g[it]);
    g[it]->SetLineStyle(lst[it]);
    g[it]->SetLineWidth(lwdt[it]);
    g[it]->SetLineColor(lcol[it]);
  }
  
  double mineff = 0.3;
  g[ifirst]->GetXaxis()->SetLimits(mineff,1.);
  g[ifirst]->SetMinimum(1.);
  double ymax = 2.;
  for( int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;//if(skip[it]) continue;
    int n = sizeof(g[it]->GetY())/sizeof(g[it]->GetY()[0]);		 
    double tempymax = TMath::MaxElement(n/*pt slices*/,g[it]->GetY());
    if (tempymax>ymax) ymax=0.5*tempymax;
  }

  ymax = 2000;  //ymax = 20;
  ymax = 30000.;
  g[ifirst]->SetMaximum(ymax);

  TCanvas* c1 = new TCanvas("c1","c1",0,0,600,600);
  c1->SetLogy(1);
  c1->SetGrid();

  g[ifirst]->Draw("ALE");
  g[ifirst]->GetXaxis()->SetTitle(signal+"-jet efficiency");
  for( int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;//if(skip[it]) continue;
    if(ifirst==it) continue;
    g[it]->Draw("LE");
  }

  TPaveText* titX = new TPaveText(0.75,0.4,1.,0.4);
  TText* txtX = titX->AddText(signal+"-jet efficiency");
  txtX->SetTextFont(42); 
  txtX->SetTextSize(0.045); 
  txtX->SetTextColor(kBlack);
  titX->SetBorderSize(0);
  titX->SetFillColor(0);
  //titX->Draw();

  TPaveText* titE = new TPaveText(-0.02,500.,0.03,10000.);
  TText* txtE = titE->AddText( background+" jet rejection");
  txtE->SetTextAngle(90);
  txtE->SetTextFont(42); 
  txtE->SetTextSize(0.045); 
  txtE->SetTextColor(kBlack);
  titE->SetBorderSize(0);
  titE->SetFillColor(0);
  titE->Draw();

  TLegend* lg = new TLegend(0.58,0.60,0.88,0.845);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;//if(skip[it]) continue;
    std::cout << BTagPerf_TagLName[it] << std::endl;    //lg->AddEntry(g[it], (13==it ? __directory : BTagPerf_TagLName[it] ) + extra,"L");    //lg->AddEntry(g[it], (14==it ? __directory : BTagPerf_TagLName[it] ) + extra,"L");    //lg->AddEntry(g[it], (15==it ? __directory : BTagPerf_TagLName[it] ) + extra,"L");
    lg->AddEntry(g[it], BTagPerf_TagLName[it] + extra,"L");
  }
  lg->Draw();

  //ATLAS_LABEL(0.22,0.84);
  //  myText("t#bar{t} simulation, #sqrt{s}=8 TeV",0.3,4.5,0.7,4.5,0.040);
  myText("t#bar{t} simulation, #sqrt{s}=8 TeV",0.3,2.2,0.7,4.5,0.040);
  myText("p_{T}^{jet}>20 GeV, |#eta^{jet}|<2.5",0.3,2.,0.7,2.,0.036);

  c1->Print(signal+"eff"+background+"rej"+".eps");//__directory+".eps");
  c1->Print(signal+"eff"+background+"rej"+".png");//__directory+".png");
 

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//void plotEffCutGraphs(TString infname="graphs", TString dirname=__directory, TString signal="b" , TString background="u") {
void plotEffCutGraphs(TString infname="graphs", TString signal="b" , TString background="u") {
  infname=infname+".root";//infname+="_"+dirname+".root";
  std::cout<<"reading input graphs from file: "<<infname<<std::endl;
  TString extra("");
  TString type("ATLAS t#bar{t}");
  TString jet("T");

  gROOT->Macro("atlasrootlogon.C");
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
  gStyle->SetPadTickY(0);
  gStyle->SetOptStat(kFALSE);

  TFile f(infname, "read");

  static const int BTagPerf_NSlice = nptbins-1;//10/*ptbins*/;
  static const float cutDnLim[BTagPerf_NTag] = { -1,-1,-1,-1.5,0,-0.2,-4, -3., 0,0, 0., -0.1 };
  static const float cutUpLim[BTagPerf_NTag] = { 3,4,4,7.5,0,5,1, +3., 0,0, 1., +0.3 };
  TGraphErrors* g[BTagPerf_NTag][BTagPerf_NSlice];

  TCanvas* c[BTagPerf_NTag];
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    std::cout<<it<<" "<<BTagPerf_TagSName[it]<<" "<<cutDnLim[it]<<" "<<cutUpLim[it]<<std::endl;
    for(int ipt=0;ipt<BTagPerf_NSlice;ipt++) {
      TString hname("effvscutT"); hname.Append(BTagPerf_TagSName[it]); hname.Append(signal+background+"Std");
      hname+="_slice"; hname+=ipt;
      g[it][ipt] = (TGraphErrors*)f.Get(hname);
      //MyGraphCleaner(g[it]);
      g[it][ipt]->SetLineStyle(1);
      g[it][ipt]->SetLineColor(ipt+1);
      if(ipt==9) g[it][ipt]->SetLineColor(ipt+2);
      if(ipt==0) {
        g[it][ipt]->GetXaxis()->SetLimits(cutDnLim[it],cutUpLim[it]);
        g[it][ipt]->SetMinimum(0.45);
        g[it][ipt]->SetMaximum(0.92);
      }
    }

    TString canname("c"); canname+=it;
    c[it] = new TCanvas(canname,canname,0,0,600,600);
    c[it]->SetGrid();
    g[it][0]->Draw("ALE");
    for(int ipt=1;ipt<BTagPerf_NSlice;ipt++) g[it][ipt]->Draw("LE");

    TPaveText* titX = new TPaveText(cutUpLim[it]*0.4, 0.41, cutUpLim[it]*0.9, 0.41);
    TString xxtxt("cut on "); xxtxt.Append(BTagPerf_TagLName[it]);
    TText* txtX = titX->AddText(xxtxt);
    txtX->SetTextFont(42); 
    txtX->SetTextSize(0.045); 
    txtX->SetTextColor(kBlack);
    titX->SetBorderSize(0);
    titX->SetFillColor(0);
    //titX->Draw();

    TPaveText* titE = new TPaveText( cutDnLim[it]-(cutUpLim[it]-cutDnLim[it])*0.12, 0.75, 
                                     cutDnLim[it]-(cutUpLim[it]-cutDnLim[it])*0.12, 0.9);
    TText* txtE = titE->AddText(signal+"-jet efficiency");
    txtE->SetTextAngle(90);
    txtE->SetTextFont(42); 
    txtE->SetTextSize(0.045); 
    txtE->SetTextColor(kBlack);
    titE->SetBorderSize(0);
    titE->SetFillColor(0);
    titE->Draw();

    TLegend* lg = new TLegend(0.63,0.60,0.88,0.845);
    lg->SetBorderSize(0);
    lg->SetFillStyle(0);
    for(int ipt=0;ipt<BTagPerf_NSlice;ipt++) {
      TString ptlab("p_{T} #in ");
      ptlab.Append("["); ptlab+=jptbins[ipt]; ptlab.Append(","); ptlab+=jptbins[ipt+1]; ptlab.Append("]");
      lg->AddEntry(g[it][ipt], ptlab, "L");
    }
    lg->Draw();

    //ATLAS_LABEL(0.22,0.84);
    myText("t#bar{t} simulation, #sqrt{s}=8 TeV",0.35,5.,0.7,5.,0.040);
    //myText("p_{T}^{jet}>20 GeV, |#eta^{jet}|<2.5",0.35,2.,0.7,2.,0.036);

    TString grpname(signal+"effvscut_"); grpname.Append(BTagPerf_TagSName[it]); grpname.Append("_");
    c[it]->Print(grpname+".eps");//c[it]->Print(grpname+dirname+".eps");
    c[it]->Print(grpname+".png");//c[it]->Print(grpname+dirname+".png");
    delete c[it];
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void plotRejPtGraphs(int effi = 60, TString infname="graphs", TString signal="b" , TString background="u") {
  infname=infname+".root";//infname+="_"+__directory+".root";
  std::cout<<"reading input graphs from file: "<<infname<<std::endl;
  TString extra("");
  TString type("ATLAS t#bar{t}");
  TString jet("T");

//   gROOT->Macro("atlasrootlogon.C");
//   gROOT->SetStyle("ATLAS");
//   gROOT->ForceStyle();
//   gStyle->SetPadTickY(0);
//   gStyle->SetOptStat(kFALSE);

  TFile *f = TFile::Open(infname);
  autoSkipFlagging(f);

  TGraphErrors* g[BTagPerf_NTag];
  int ifirst = -1;
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    if(ifirst==-1) ifirst = it;
    TString hname("rejvspt"); hname+=effi; hname.Append("T");
    hname.Append(BTagPerf_TagSName[it]); hname.Append(signal+background+"Std");
    g[it] = (TGraphErrors*)f->Get(hname);
    if(g[it]==0) {
      std::cout<<"Error, graph "<<hname<<" not found."<<std::endl;
      return;
    }
    //if(it==2||it==5) MyGraphCleaner(g[it],0.7); 
    //else MyGraphCleaner(g[it]);
    g[it]->SetLineStyle(lst[it]);
    g[it]->SetLineWidth(lwdt[it]);
    g[it]->SetLineColor(lcol[it]);
  }

  //g[ifirst]->GetXaxis()->SetLimits(0.3,1.);
  g[ifirst]->SetMinimum(1.);
  float ymax = 2.;
  if(70==effi) ymax = 2.;


  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    double tempymax = TMath::MaxElement(nptbins-1/*pt slices*/,g[it]->GetY());
    if (tempymax>ymax) ymax=1.2*tempymax;
  }
  
  g[ifirst]->SetMaximum(ymax);

  TCanvas* c4 = new TCanvas("c4","c4",0,0,600,600);
  c4->SetLogx(1);
  //c4->SetLogy(1);
  //c4->SetGrid();

  g[ifirst]->Draw("ALE");
  g[ifirst]->GetYaxis()->SetTitle(background+" jet rejection");
  g[ifirst]->GetXaxis()->SetTitle("jet p_{T} (GeV)");
  g[ifirst]->GetXaxis()->SetMoreLogLabels();
  g[ifirst]->GetXaxis()->SetNoExponent();
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(ifirst==it) continue;
    if(v_skip[it]) continue;
    g[it]->Draw("LE");
  }

  //  TPaveText* titX = new TPaveText(420.,-ymax*0.1,500.,-ymax*0.1);
  TPaveText* titX = new TPaveText(420.,0.,500.,0.);
  TText* txtX = titX->AddText("jet p_{T} (GeV)");
  txtX->SetTextFont(42); 
  txtX->SetTextSize(0.045); 
  txtX->SetTextColor(kBlack);
  titX->SetBorderSize(0);
  titX->SetFillColor(0);
  //titX->Draw();

  TPaveText* titE = new TPaveText(-70.,ymax*0.5,-70.,ymax*0.8);
  TText* txtE = titE->AddText(background+" jet rejection");
  txtE->SetTextAngle(90);
  txtE->SetTextFont(42); 
  txtE->SetTextSize(0.045); 
  txtE->SetTextColor(kBlack);
  titE->SetBorderSize(0);
  titE->SetFillColor(0);
  //titE->Draw();

  TLegend* lg = new TLegend(0.58,0.60,0.88,0.845);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    lg->AddEntry(g[it], BTagPerf_TagLName[it] + extra,"L");
    //lg->AddEntry(g[it], (BTagPerf_TagLName[it]=="MVX" ? __directory : BTagPerf_TagLName[it] ) + extra,"L");
  }
  lg->Draw();

  //ATLAS_LABEL(0.22,0.84);
  TString sbeffi("#epsilon_{"+signal+"} = "); sbeffi+=effi; sbeffi.Append("%");
  myText(sbeffi, 280.,ymax*0.5,500.,ymax*0.5,0.040);
  myText("t#bar{t} simulation, #sqrt{s}=8 TeV",280.,ymax*0.45,500.,ymax*0.45,0.040);
  myText("p_{T}^{jet}>20 GeV, |#eta^{jet}|<2.5",300.,ymax*0.40,500.,ymax*0.40,0.036);

  TString imgname(background+"rejpt_sig"+signal+"_"); imgname+=effi; imgname.Append("_");
  //imgname+=__directory;
  c4->Print(imgname+".eps");
  c4->Print(imgname+".png");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void plotRejEtaGraphs(int effi = 60, TString infname="graphs", TString signal="b" , TString background="u") {
  infname=infname+".root";//infname+="_"+__directory+".root";
  std::cout<<"reading input graphs from file: "<<infname<<std::endl;
  TString extra("");
  TString type("ATLAS t#bar{t}");
  TString jet("T");

  gROOT->Macro("atlasrootlogon.C");
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
  gStyle->SetPadTickY(0);
  gStyle->SetOptStat(kFALSE);

  TFile *f = TFile::Open(infname);//TFile f(infname, "read");
  autoSkipFlagging(f);

  TGraphErrors* g[BTagPerf_NTag];
  int ifirst = -1;
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    if(ifirst==-1) ifirst = it;
    TString hname("rejvseta"); hname+=effi; hname.Append("T");
    hname.Append(BTagPerf_TagSName[it]); hname.Append(signal+background+"Std");
    g[it] = (TGraphErrors*)f->Get(hname);
    if(g[it]==0) {
      std::cout<<"Error, graph "<<hname<<" not found."<<std::endl;
      return;
    }
    //if(it==2||it==5) MyGraphCleaner(g[it],0.7); 
    //else MyGraphCleaner(g[it]);
    g[it]->SetLineStyle(lst[it]);
    g[it]->SetLineWidth(lwdt[it]);
    g[it]->SetLineColor(lcol[it]);
  }

  //g[ifirst]->GetXaxis()->SetLimits(0.3,1.);
  g[ifirst]->SetMinimum(1.);
  float ymax = 2.;
  if(70==effi) ymax = 2.;


  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    double tempymax = TMath::MaxElement(netabins-1/*eta slices*/,g[it]->GetY());
    if (tempymax>ymax) ymax=1.2*tempymax;
  }
  
  g[ifirst]->SetMaximum(ymax);

  TCanvas* c4 = new TCanvas("c4","c4",0.,0.,500.,500.);
  //c4->SetLogy(1);
  //c4->SetGrid();

  g[ifirst]->Draw("ALE");
  g[ifirst]->GetXaxis()->SetTitle("|#eta^{jet}|");
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    if(ifirst==it) continue;
    g[it]->Draw("LE");
  }

  //  TPaveText* titX = new TPaveText(420.,-ymax*0.1,500.,-ymax*0.1);
  TPaveText* titX = new TPaveText(2.1,-80.,2.5,-80.);
  TText* txtX = titX->AddText("|#eta^{jet}|");
  txtX->SetTextFont(42); 
  txtX->SetTextSize(0.045); 
  txtX->SetTextColor(kBlack);
  titX->SetBorderSize(0);
  titX->SetFillColor(0);
  //titX->Draw();

  TPaveText* titE = new TPaveText(-70.,ymax*0.5,-70.,ymax*0.8);
  TText* txtE = titE->AddText(background+" jet rejection");
  txtE->SetTextAngle(90);
  txtE->SetTextFont(42); 
  txtE->SetTextSize(0.045); 
  txtE->SetTextColor(kBlack);
  titE->SetBorderSize(0);
  titE->SetFillColor(0);
  titE->Draw();

  TLegend* lg = new TLegend(0.58,0.60,0.88,0.845);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    lg->AddEntry(g[it], BTagPerf_TagLName[it] + extra,"L");
    //lg->AddEntry(g[it], (BTagPerf_TagLName[it]=="MVX" ? __directory : BTagPerf_TagLName[it] ) + extra,"L");
  }
  lg->Draw();

  //ATLAS_LABEL(0.22,0.84);
  TString sbeffi("#epsilon_{"+signal+"} = "); sbeffi+=effi; sbeffi.Append("%");
  myText(sbeffi, 1.4,ymax*0.5,2.5,ymax*0.5,0.040);
  myText("t#bar{t} simulation, #sqrt{s}=8 TeV",1.40,ymax*0.45,2.50,ymax*0.45,0.040);
  myText("p_{T}^{jet}>20 GeV, |#eta^{jet}|<2.5",1.50,ymax*0.40,2.50,ymax*0.40,0.036);

  TString imgname(background+"rejeta_sig"+signal+"_"); imgname+=effi; imgname.Append("_");
  //imgname+=__directory;
  c4->Print(imgname+".eps");
  //  c4->Print(imgname+".png");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
void plotRejFromCutPtGraphs(int effi = 60, TString infname="graphs", TString signal="b" , TString background="u") {
  infname=infname+".root";//infname+="_"+__directory+".root";
  std::cout<<"reading input graphs from file: "<<infname<<std::endl;
  TString extra("");
  TString type("ATLAS t#bar{t}");
  TString jet("T");

//   gROOT->Macro("atlasrootlogon.C");
//   gROOT->SetStyle("ATLAS");
//   gROOT->ForceStyle();
//   gStyle->SetPadTickY(0);
//   gStyle->SetOptStat(kFALSE);

  TFile *f = TFile::Open(infname);//TFile f(infname, "read");
  autoSkipFlagging(f);

  TGraphErrors* g[BTagPerf_NTag];
  int ifirst = -1;
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    if(ifirst==-1) ifirst = it;
    TString hname;
    // if (it!=15) { hname="rejfromcutvspt"; hname+=effi; hname.Append("T");}
    // else {hname="rejvsptMeta"; hname+=effi; hname.Append("T");}
    hname="rejfromcutvspt"; hname+=effi; hname.Append("T");

    hname.Append(BTagPerf_TagSName[it]); hname.Append(signal+background+"Std");
    g[it] = (TGraphErrors*)f->Get(hname);
    if(g[it]==0) {
      std::cout<<"Error, graph "<<hname<<" not found."<<std::endl;
      return;
    }
    //if(it==2||it==5) MyGraphCleaner(g[it],0.7); 
    //else MyGraphCleaner(g[it]);
    g[it]->SetLineStyle(lst[it]);
    g[it]->SetLineWidth(lwdt[it]);
    g[it]->SetLineColor(lcol[it]);
  }
  //g[ifirst]->GetXaxis()->SetLimits(0.3,1.);
  g[ifirst]->SetMinimum(1.);
  float ymax = 2.;//2200.;
  if(70==effi) ymax = 2.;//1000.;

  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    double tempymax = TMath::MaxElement(nptbins-1/*pt slices*/,g[it]->GetY());
    if (tempymax>ymax) ymax=1.2*tempymax;
  }

  g[ifirst]->SetMaximum(ymax);

  TCanvas* c4 = new TCanvas("c4","c4",0,0,600,600);
  c4->SetLogx(1);
  //c4->SetLogy(1);
  //c4->SetGrid();

  g[ifirst]->Draw("ALE");
  g[ifirst]->GetYaxis()->SetTitle(background+" jet rejection");
  g[ifirst]->GetXaxis()->SetTitle("jet p_{T} (GeV)");
  g[ifirst]->GetXaxis()->SetMoreLogLabels();
  g[ifirst]->GetXaxis()->SetNoExponent();
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    if(ifirst==it) continue;
    g[it]->Draw("LE");
  }

  double posForPtlabel = 0.;

  TPaveText* titX = new TPaveText(420.,-ymax*posForPtlabel, 500.,-ymax*posForPtlabel);
  TText* txtX = titX->AddText("jet p_{T} (GeV)");
  txtX->SetTextFont(42); 
  txtX->SetTextSize(0.045); 
  txtX->SetTextColor(kBlack);
  titX->SetBorderSize(0);
  titX->SetFillColor(0);
  //titX->Draw();

  TPaveText* titE = new TPaveText(-70.,ymax*0.5,-70.,ymax*0.8);
  TText* txtE = titE->AddText(background+" jet rejection");
  txtE->SetTextAngle(90);
  txtE->SetTextFont(42); 
  txtE->SetTextSize(0.045); 
  txtE->SetTextColor(kBlack);
  titE->SetBorderSize(0);
  titE->SetFillColor(0);
  //titE->Draw();

  TLegend* lg = new TLegend(0.58,0.60,0.88,0.845);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    lg->AddEntry(g[it], BTagPerf_TagLName[it] + extra,"L");
  }
  lg->Draw();

  //ATLAS_LABEL(0.22,0.84);
  TString sbeffi("Fixed cut for a global #epsilon_{"+signal+"} = "); sbeffi+=effi; sbeffi+="%";
  myText(sbeffi, 280.,ymax*0.55,500.,ymax*0.55,0.040);
  myText("t#bar{t} simulation, #sqrt{s}=8 TeV",280.,ymax*0.5,500.,ymax*0.5,0.040);
  myText("p_{T}^{jet}>20 GeV, |#eta^{jet}|<2.5",300.,ymax*0.45,500.,ymax*0.45,0.036);

  TString imgname(background+"rejfromcutpt_sig"+signal+"_"); imgname+=effi; imgname.Append("_");
  //imgname+=__directory;
  c4->Print(imgname+".eps");
  //  c4->Print(imgname+".png");
}

void plotEffFromCutPtGraphs(int effi = 60, TString infname="graphs", TString signal="b" , TString background="u") {
  infname=infname+".root";//infname+"_"+__directory+".root";
  std::cout<<"reading input graphs from file: "<<infname<<std::endl;
  TString extra("");
  TString type("ATLAS t#bar{t}");
  TString jet("T");

//   gROOT->Macro("atlasrootlogon.C");
//   gROOT->SetStyle("ATLAS");
//   gROOT->ForceStyle();
//   gStyle->SetPadTickY(0);
//   gStyle->SetOptStat(kFALSE);

  TFile *f = TFile::Open(infname);//TFile f(infname, "read");
  autoSkipFlagging(f);

  TGraphErrors* g[BTagPerf_NTag];
  int ifirst = -1;
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    if(ifirst==-1) ifirst = it;
    TString hname("efffromcutvspt"); hname+=effi; hname.Append("T");
    hname.Append(BTagPerf_TagSName[it]); hname.Append(signal+background+"Std");
    g[it] = (TGraphErrors*)f->Get(hname);
    if(g[it]==0) {
      std::cout<<"Error, graph "<<hname<<" not found."<<std::endl;
      return;
    }
    //if(it==2||it==5) MyGraphCleaner(g[it],0.7); 
    //else MyGraphCleaner(g[it]);
    g[it]->SetLineStyle(lst[it]);
    g[it]->SetLineWidth(lwdt[it]);
    g[it]->SetLineColor(lcol[it]);
  }
  //g[ifirst]->GetXaxis()->SetLimits(0.3,1.);
  g[ifirst]->SetMinimum(0.2);
  float ymax = 0.90;
  if(70==effi) ymax = 1.;
  g[ifirst]->SetMaximum(ymax);

  TCanvas* c4 = new TCanvas("c4","c4",0,0,600,600);
  c4->SetLogx(1);
  //c4->SetLogy(1);
  //c4->SetGrid();

  g[ifirst]->Draw("ALE");
  g[ifirst]->GetYaxis()->SetTitle(signal+"-tagging efficiency");
  g[ifirst]->GetXaxis()->SetTitle("jet p_{T} (GeV)");
  g[ifirst]->GetXaxis()->SetMoreLogLabels();
  g[ifirst]->GetXaxis()->SetNoExponent();
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    if(ifirst==it) continue;
    g[it]->Draw("LE");
  }

  TPaveText* titX = new TPaveText(420.,0.05+ymax*0.1,500.,0.05+ymax*0.1);
  TText* txtX = titX->AddText("jet p_{T} (GeV)");
  txtX->SetTextFont(42); 
  txtX->SetTextSize(0.045); 
  txtX->SetTextColor(kBlack);
  titX->SetBorderSize(0);
  titX->SetFillColor(0);
  //titX->Draw();

  TPaveText* titE = new TPaveText(-70.,ymax*0.5,-70.,ymax*0.8);
  TText* txtE = titE->AddText(signal+"-tagging efficiency");
  txtE->SetTextAngle(90);
  txtE->SetTextFont(42); 
  txtE->SetTextSize(0.045); 
  txtE->SetTextColor(kBlack);
  titE->SetBorderSize(0);
  titE->SetFillColor(0);
  //titE->Draw();

  TLegend* lg = new TLegend(0.58,0.60,0.88,0.845);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    lg->AddEntry(g[it], BTagPerf_TagLName[it] + extra,"L");
    //lg->AddEntry(g[it], (BTagPerf_TagLName[it]=="MVX" ? __directory : BTagPerf_TagLName[it] ) + extra,"L");
  }
  lg->Draw();

  //ATLAS_LABEL(0.22,0.84);
  //  TString sbeffi("w_{0} = "); sbeffi+=;
  //  myText(sbeffi, 280.,ymax*0.5,500.,ymax*0.5,0.040);
  TString efffromcutLabel = "Fixed cut for a global #epsilon_{"+signal+"} = "; efffromcutLabel+=effi; efffromcutLabel+="%";
  myText(efffromcutLabel,260.,ymax*0.40,500.,ymax*0.40,0.040);
  myText("t#bar{t} simulation, #sqrt{s}=8 TeV",280.,ymax*0.35,500.,ymax*0.35,0.040);
  myText("p_{T}^{jet}>20 GeV, |#eta^{jet}|<2.5",300.,ymax*0.30,500.,ymax*0.30,0.036);

  TString imgname(signal+"efffromcutpt"); imgname+=effi; imgname.Append("_");
  //imgname+=__directory;
  c4->Print(imgname+".eps");
  //  c4->Print(imgname+".png");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
void plotEffPtGraphs(int effi = 60, TString infname="graphs", TString signal="b" , TString background="u") {
  infname=infname+".root";//infname+="_"+__directory+".root";
  std::cout<<"reading input graphs from file: "<<infname<<std::endl;
  TString extra("");
  TString type("ATLAS t#bar{t}");
  TString jet("T");

//   gROOT->Macro("atlasrootlogon.C");
//   gROOT->SetStyle("ATLAS");
//   gROOT->ForceStyle();
//   gStyle->SetPadTickY(0);
//   gStyle->SetOptStat(kFALSE);

  TFile *f = TFile::Open(infname);//TFile f(infname, "read");
  autoSkipFlagging(f);

  TGraphErrors* g[BTagPerf_NTag];
  int ifirst = -1;
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    if(ifirst==-1) ifirst = it;
    TString hname("effvspt"); hname+=effi; hname.Append("T");
    hname.Append(BTagPerf_TagSName[it]); hname.Append(signal+background+"Std");
    g[it] = (TGraphErrors*)f->Get(hname);
    if(g[it]==0) {
      std::cout<<"Error, graph "<<hname<<" not found."<<std::endl;
      return;
    }
    //if(it==2||it==5) MyGraphCleaner(g[it],0.7); 
    //else MyGraphCleaner(g[it]);
    g[it]->SetLineStyle(lst[it]);
    g[it]->SetLineWidth(lwdt[it]);
    g[it]->SetLineColor(lcol[it]);
  }
  //g[ifirst]->GetXaxis()->SetLimits(0.3,1.);
  float ymin = 0.0;
  float ymax = 0.9;
  g[ifirst]->SetMinimum(ymin);
  g[ifirst]->SetMaximum(ymax);

  TCanvas* c3 = new TCanvas("c3","c3",0,0,600,600);
  c3->SetLogx(1);
  //c2->SetLogy(1);
  //c2->SetGrid();

  g[ifirst]->Draw("ALE");
  g[ifirst]->GetYaxis()->SetTitle(signal+"-tagging efficiency");
  g[ifirst]->GetXaxis()->SetTitle("jet p_{T} (GeV)");
  g[ifirst]->GetXaxis()->SetMoreLogLabels();
  g[ifirst]->GetXaxis()->SetNoExponent();
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    if(ifirst==it) continue;
    g[it]->Draw("LE");
  }

  TPaveText* titX = new TPaveText(420.,ymin-ymax*0.1,500.,ymin-ymax*0.1);
  TText* txtX = titX->AddText("jet p_{T} (GeV)");
  txtX->SetTextFont(42); 
  txtX->SetTextSize(0.045); 
  txtX->SetTextColor(kBlack);
  titX->SetBorderSize(0);
  titX->SetFillColor(0);
  //titX->Draw();

  TPaveText* titE = new TPaveText(-70.,ymax*0.5,-70.,ymax*0.8);
  TText* txtE = titE->AddText(signal+"-jet efficiency");
  txtE->SetTextAngle(90);
  txtE->SetTextFont(42); 
  txtE->SetTextSize(0.045); 
  txtE->SetTextColor(kBlack);
  titE->SetBorderSize(0);
  titE->SetFillColor(0);
  //titE->Draw();

  TLegend* lg = new TLegend(0.58,0.60,0.88,0.845);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  for(int it=0;it<BTagPerf_NTag;it++) {
    if(v_skip[it]) continue;
    lg->AddEntry(g[it], BTagPerf_TagLName[it] + extra,"L");
    //lg->AddEntry(g[it], (BTagPerf_TagLName[it]=="MVX" ? __directory : BTagPerf_TagLName[it] ) + extra,"L");
  }
  lg->Draw();

  //ATLAS_LABEL(0.22,0.84);
  TString sbeffi("At averaged R_{u} for #epsilon_{"+signal+"} = "); sbeffi+=effi; sbeffi.Append("%");
  myText(sbeffi, 280.,ymax*0.2,500.,ymax*0.2,0.040);
  myText("t#bar{t} simulation, #sqrt{s}=8 TeV",280.,ymax*0.15,500.,ymax*0.15,0.040);
  myText("p_{T}^{jet}>20 GeV, |#eta^{jet}|<2.5",300.,ymax*0.07,500.,ymax*0.07,0.036);

  TString imgname(signal+"effpt"); imgname+=effi; imgname.Append("_");
  //imgname+=__directory;
  c3->Print(imgname+".eps");
  //  c3->Print(imgname+".png");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<TString> getTaggers2Eval() {

  TString fileName="taggers2eval.list";
  ifstream ifs(fileName.Data());
  string aLine;
  vector<TString> taggerlist,namelist;
  if (ifs.fail()) {
    cerr<<"Failure when reading a file: "<<fileName<<"!! Aborting..."<<endl;
    exit(1);
  }
  else {
    while (getline(ifs,aLine)) {
      //cout<<aLine<<endl;
      TString ts_aLine=aLine.data();
      if (ts_aLine.BeginsWith("#")) continue;
      TString tagger =aLine.substr(0,aLine.find(","));
      TString name=aLine.substr(aLine.size()-1,aLine.size());
      //cout<<tagger<<"\t"<<name<<endl;
      taggerlist.push_back(tagger);
      namelist.push_back(name);
    }
  }
  return taggerlist;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void btagRejGraphs(TString inputFile, bool skipProjection = false, bool skipProjectionIfDone=true, TString mvaName="", TString outputPostfix="", TString mSwitch="buc") {
  //__directory = directory;
  g_mvaName=mvaName;
  g_mSwitch=mSwitch;

  v_Signal     .resize(1);
  v_Background .resize(3);
  v_OP         .resize(5);
  v_OPname     .resize(5);
  if (g_mvaName.Contains("_cSig_") or g_mSwitch.BeginsWith("c")) {                                                         // else if (g_mSwitch.BeginsWith("c")) {										     
    tagLabel=4;														   //   tagLabel=4;													     
    string signals[]     = { "c" };                             v_Signal     =vector<string>(signals,    signals+1    );   //   string signals[]     = { "c" };                             v_Signal     =vector<string>(signals,    signals+1    );  
    string backgrounds[] = { "u" , "b" , "t"};                  v_Background =vector<string>(backgrounds,backgrounds+3);   //   string backgrounds[] = { "u" , "b" , "t"};                  v_Background =vector<string>(backgrounds,backgrounds+3);  
    string opNames[]     = { "50", "40" , "30" , "20" , "10" }; v_OPname     =vector<string>(opNames,    opNames+5    );   //   string opNames[]     = { "50", "40" , "30" , "20" , "10" }; v_OPname     =vector<string>(opNames,    opNames+5    );  
    double ops[]         = {  50.,  40. ,  30. ,  20. ,  10. }; v_OP         =vector<double>(ops,        ops+5        );   //   double ops[]         = {  50.,  40. ,  30. ,  20. ,  10. }; v_OP         =vector<double>(ops,        ops+5        );  
  }															   // }                                                                                                                       
  else {
    string signals[]     = { "b" };                             v_Signal     =vector<string>(signals,    signals+1    );
    string backgrounds[] = { "u" , "c" , "t"};			v_Background =vector<string>(backgrounds,backgrounds+3);
    string opNames[]     = { "50", "60" , "70" , "75" , "80" };	v_OPname     =vector<string>(opNames,    opNames+5    );
    double ops[]         = {  50 ,  60. ,  70. ,  75. ,  80. };	v_OP         =vector<double>(ops,        ops+5        );
  }
  
  TString outputDir="";
  if(inputFile.Contains("/")){
    string tmp_str=inputFile.Data();
    outputDir=(tmp_str.erase(tmp_str.rfind("/"),tmp_str.length())).data();
    //cout<<"outputDir= "<<outputDir<<endl;return;
  }


  TString name2add = (mvaName=="" ? "" : mvaName+".") + (g_mvaName.Contains("_bin_")?"":mSwitch+".");
  if (outputPostfix!="") name2add= name2add+outputPostfix+".";
  //cout<<"name2add= "<<name2add<<endl;

  vector<TString> tmp=getTaggers2Eval();

  v_skip.clear();
  v_binMode.clear();
  for (int i=0; i<BTagPerf_NTag; i++) {
    if (BTagPerf_TagLName[i]=="MVX") {
      if (g_mvaName.Contains("_bin_")) {
	if (g_mvaName.Contains("_BdtGrad_")) v_binMode.push_back(8);
	else                                 v_binMode.push_back(BTagPerf_BinMode[i]);
      }
      else                             v_binMode.push_back(8);
    }
    else v_binMode.push_back(BTagPerf_BinMode[i]);
    //v_skip.push_back(skip[i]);
    bool isFound=false;
    for (auto tagger:tmp) {
      if (tagger==BTagPerf_TagSName[i]) {
	isFound= true;
	break;
      }
    }
    v_skip.push_back(!isFound);
  }

  if(!skipProjection) {
    bool doMVA=false;
    for (int i=0; i<BTagPerf_NTag; i++) {
      if (!v_skip[i]) cout<<BTagPerf_TagLName[i]<<endl;
      if (BTagPerf_TagLName[i]=="MVX") {
	if (!v_skip[i]) doMVA=true;
      }
    }

    if (doMVA) {//reader can't be 0!!
      initializeReader(mvaName);
    }

    set_binMode();
    std::cout<<"createRejHistos()"<<std::endl;
    createRejHistos(inputFile,outputDir+"/"+name2add+"hists", "",skipProjectionIfDone);
    std::cout<<"createRejGraphs()"<<std::endl;
    createRejGraphs(outputDir+"/"+name2add+"hists",outputDir+"/"+name2add+"graphs");
    //createMetaOPRejGraphs();
  }
  //std::cout<<"createRejGraphs()"<<std::endl;
  //  createRejGraphs();
  // void plotRejEffGraphs(TString infname="graphs", TString signal="b" , TString background="u")

  // void plotRejPtGraphs(int effi = 60, TString infname="graphs", TString signal="b" , TString background="u")
  // void plotEffPtGraphs(int effi = 60, TString infname="graphs", TString signal="b" , TString background="u") {

  // void plotEffCutGraphs(TString infname="graphs", TString dirname=__directory, TString signal="b" , TString background="u")
  // void plotRejCutGraphs(TString infname="graphs", TString dirname=__directory, TString signal="b" , TString background="u")

  // void plotRejFromCutPtGraphs(int effi = 60, TString infname="graphs", TString signal="b" , TString background="u")
  // void plotEffFromCutPtGraphs(int effi = 60, TString infname="graphs", TString signal="b" , TString background="u")

//    for(int isig=0; isig<v_Signal.size(); isig++) {
//      for(int ibkg=0; ibkg<v_Background.size(); ibkg++) {
//        TString signal = v_Signal[isig];
//        TString background = v_Background[ibkg];
//        std::cout << "signal: " << signal << " background: " << background << std::endl;
  
//        std::cout<<"plotRejEffGraphs()"<<std::endl;
//        plotRejEffGraphs("graphs", signal, background);
//        // //std::cout<<"plotRejEffGraphsPtBins()"<<std::endl;
//        // // //plotRejEffGraphsPtBins();
  
//        std::cout<<"plotRejPtGraphs() @ 60%"<<std::endl;
//        plotRejPtGraphs(60,"graphs", signal, background);
//        std::cout<<"plotRejPtGraphs() @ 70%"<<std::endl;
//        plotRejPtGraphs(70,"graphs", signal, background);
//        std::cout<<"plotRejPtGraphs() @ 80%"<<std::endl;
//        plotRejPtGraphs(80,"graphs", signal, background);
//        std::cout<<"plotRejPtGraphs() @ 90%"<<std::endl;
//        plotRejPtGraphs(90,"graphs", signal, background);
  
//        std::cout<<"plotEffPtGraphs() @ 60%"<<std::endl;
//        plotEffPtGraphs(60,"graphs", signal, background);
//        std::cout<<"plotEffPtGraphs() @ 70%"<<std::endl;
//        plotEffPtGraphs(70,"graphs", signal, background);
//        std::cout<<"plotEffPtGraphs() @ 80%"<<std::endl;
//        plotEffPtGraphs(80,"graphs", signal, background);
//        std::cout<<"plotEffPtGraphs() @ 90%"<<std::endl;
//        plotEffPtGraphs(90,"graphs", signal, background);
  
//        // std::cout << "plotEffCutGraphs()" << std::endl;
//        // plotEffCutGraphs("graphs", __directory, signal, background);
//        // std::cout << "plotRejCutGraphs()" << std::endl;
//        // // plotRejCutGraphs("graphs", __directory, signal, background);
  
//        std::cout<<"plotRejFromCutPtGraphs() @ 60%"<<std::endl;
//        plotRejFromCutPtGraphs(60,"graphs", signal, background);
//        std::cout<<"plotRejFromCutPtGraphs() @ 70%"<<std::endl;
//        plotRejFromCutPtGraphs(70,"graphs", signal, background);
//        std::cout<<"plotRejFromCutPtGraphs() @ 80%"<<std::endl;
//        plotRejFromCutPtGraphs(80,"graphs", signal, background);
//        std::cout<<"plotRejFromCutPtGraphs() @ 90%"<<std::endl;
//        plotRejFromCutPtGraphs(90,"graphs", signal, background);
  
//        std::cout<<"plotEffFromCutPtGraphs() @ 60%"<<std::endl;
//        plotEffFromCutPtGraphs(60,"graphs", signal, background);
//        std::cout<<"plotEffFromCutPtGraphs() @ 70%"<<std::endl;
//        plotEffFromCutPtGraphs(70,"graphs", signal, background);
//        std::cout<<"plotEffFromCutPtGraphs() @ 80%"<<std::endl;
//        plotEffFromCutPtGraphs(80,"graphs", signal, background);
//        std::cout<<"plotEffFromCutPtGraphs() @ 90%"<<std::endl;
//        plotEffFromCutPtGraphs(90,"graphs", signal, background);
//      }
//    }
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void ATLAS_LABEL(Double_t x,Double_t y,Color_t color) {
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
  l.SetNDC();
  l.SetTextFont(72);
  l.SetTextColor(color);
  l.DrawLatex(x,y,"ATLAS Preliminary");
}

void myText(TString txt, float x1, float y1, float x2, float y2, float tsize) {
  TPaveText* paveM = new TPaveText(x1,y1,x2,y2);
  paveM->SetFillStyle(0);
  TText* txtM = paveM->AddText(txt);
  txtM->SetTextFont(42); 
  txtM->SetTextSize(tsize); 
  txtM->SetTextColor(kBlack);
  paveM->SetBorderSize(0);
  paveM->SetFillColor(0);
  paveM->Draw();
}
