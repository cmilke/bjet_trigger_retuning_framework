#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "TH1.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"
#include "TLine.h"

#include "tools/RejectionTool.C"
#include "btagRejGraphs.C"

using namespace std;

TH1F *cloneGraph2Hist(TGraphErrors* graph);//#KM converting a graph to a hist
TH1F *interpolatedHist(TH1F *input);
TH1F* interpolatedRoc(TGraphErrors* input) ;
void drawRatios(vector<TH1F*> histVec, TGraphErrors* origGraph, TString yTitle, TString drawOption);//
void loadTaggers2draw(TString listFileName="taggers2draw.list");

double g_graphXmin = 20; 
double g_graphXmax = 500;

vector<int>     v_colors,v_style;
vector<TString> v_taggers,v_show;

void print_usage() {
  cout<<"Usage: "<<"\t"<<"plot(inputFileName, int effTarget=70, string sigBkg=\"bu\", int  curveType=0, bool doRatio=1)"<<endl
      <<"\t"<<"effTarget  : efficiency target to draw                                        "<<endl
      <<"\t"<<"sigBkg     : bu means b as signal u as bkg, only bu or bc is supported so far "<<endl
      <<"\t"<<"curveType  : 0. for rejfromcutvspt  ==> global efficiency plot Rl vs pt	     "<<endl
      <<"\t"<<"           : 1. for rejvspt         ==> flat   efficiency plot Rl vs pt	     "<<endl
      <<"\t"<<"           : 2. for rejvseff        ==> overall rejection vs efficiency plot  "<<endl
      <<"\t"<<"           : 3. for rejfromcutvseta ==> global efficiency plot Rl vs eta	     "<<endl
      <<"\t"<<"           : 4. for rejvseta        ==> flat   efficiency plot Rl vs eta	     "<<endl
      <<"\t"<<"           : 5. for effvspt         ==> global cut eff vs pt		     "<<endl;
}

void plot(TString inputFileName="",int effTarget=70, string sigBkg="bu", int  curveType=0, bool doRatio=1) {

  if (curveType==3 or curveType==4) {
    g_graphXmin = 0; 
    g_graphXmax = 2.5;
  }

  loadTaggers2draw();//vector<TString> taggers=loadTaggers2draw();

  if (inputFileName=="") {
    cout<<"input file name not set, please check usage..."<<endl;
    print_usage();
    return;    //exit(1);
  }

  TFile *file = 0;
  file  = TFile::Open(inputFileName,"read");

  cout<<"opening file: "<<file->GetName()<<endl;
  TString targetEff = TString::Format("%dT",effTarget);
  TString plotName;
  if      (curveType==0) plotName = "rejfromcutvspt";
  else if (curveType==1) plotName = "rejvspt";
  else if (curveType==3) plotName = "rejfromcutvseta";
  else if (curveType==4) plotName = "rejvseta";
  else if (curveType==5) plotName = "efffromcutvspt";
  else { targetEff="T";  plotName = "rejvseff";}

  TString plotTitle;
  // if   (curveType==0) plotTitle = sigBkg.substr(0,1)+ TString::Format("-tagging, Global #epsilon = %.2f", (float)effTarget/100);
  if      (curveType==0) plotTitle = sigBkg.substr(0,1)+ TString::Format("-tagging, Global eff = %.2f", (float)effTarget/100);
  else if (curveType==1) plotTitle = sigBkg.substr(0,1)+ TString::Format("-tagging, Flat   eff = %.2f", (float)effTarget/100);
  else if (curveType==3) plotTitle = sigBkg.substr(0,1)+ TString::Format("-tagging, Global eff = %.2f", (float)effTarget/100);
  else if (curveType==4) plotTitle = sigBkg.substr(0,1)+ TString::Format("-tagging, Flat   eff = %.2f", (float)effTarget/100);
  else if (curveType==5) plotTitle = sigBkg.substr(0,1)+ TString::Format("-tagging, Global eff = %.2f", (float)effTarget/100);
  else                   plotTitle = "";
  TString yTitle  = (sigBkg.substr(1,1)!="t"?sigBkg.substr(1,1):"#tau")+"-jet rejection";
  if (curveType==5) yTitle = sigBkg.substr(0,1)+"-jet efficiency";

  vector<TGraphErrors*> graphs;
  for (unsigned it=0; it<v_taggers.size(); it++) {
    cout<<plotName+targetEff+ v_taggers[it] +sigBkg+"Std"<<endl;
    graphs.push_back( (TGraphErrors*) file ->Get(plotName+targetEff+ v_taggers[it] +sigBkg+"Std") );
  }

  if ( graphs.size()==1 ) doRatio=0;
  
  //#KM: just for protection
  for (unsigned i=0; i<graphs.size(); i++) if (!graphs[i]) {cerr<<"graph["<<i<<"] == 0 !!!!!!!!"<<endl; exit(1);}
  
  //TLegend * leg = new TLegend(0.3,0.8,0.95,0.95);
  TLegend * leg = new TLegend(0.4,0.7,0.95,0.95);
  //leg->SetNColumns(3);  leg->SetFillStyle(0);  leg->SetBorderSize(0);  leg->SetMargin(0);
  leg->SetNColumns(2);  leg->SetFillStyle(0);  leg->SetBorderSize(0);  leg->SetMargin(0);
  //leg->SetNColumns(1);  leg->SetFillStyle(0);  leg->SetBorderSize(0);  leg->SetMargin(0);
  
  vector<TString> v_legends;
  for (unsigned it=0; it<v_taggers.size(); it++) {
    if (v_show[it]=="") v_legends.push_back( TString::Format("#color[%d]{%s}", v_colors[it], v_taggers[it].Data() ) );
    else                v_legends.push_back( TString::Format("#color[%d]{%s}", v_colors[it], v_show[it] .Data() ) );
  }

  for (unsigned it=0; it<v_taggers.size(); it++) {
    graphs[it] -> SetLineColor  ( v_colors[it] );
    graphs[it] -> SetLineStyle  ( v_style[it]  );
    graphs[it] -> SetMarkerColor( v_colors[it] );
    graphs[it] -> SetLineWidth  (      2       );
    leg->AddEntry(graphs[it], v_legends[it], "l");
    if(curveType==2) graphs[it] ->SetLineStyle(2);
  }

  double min=graphs[0]->GetHistogram()->GetMinimum();
  double max=graphs[0]->GetHistogram()->GetMaximum();
  if (curveType!=2) {//if (curveType<2) {
    for (unsigned int i=1; i<graphs.size(); i++) {
      if (graphs[i]->GetHistogram()->GetMinimum()<min) min = graphs[i]->GetHistogram()->GetMinimum();
      if (graphs[i]->GetHistogram()->GetMaximum()>max) max = graphs[i]->GetHistogram()->GetMaximum();
    }
    max*=1.2;
    min*=0.8;
  }
  else {
    min=1;
    if      (sigBkg=="bu") max=2e4;
    else if (sigBkg=="bc") max=100;
    else if (sigBkg=="cu") max=2e3;
    else if (sigBkg=="cb") max=30;
  }
  graphs[0]->SetMaximum(max);
  graphs[0]->SetMinimum(min);
  
  //#KM: define pads to draw actual graphs and ratios//////////////////////////
  TCanvas * c;// = new TCanvas("c","c",600,800);
  TPad *c_1;// = new TPad("c_1", "_1", 0.  , 0.4, 1., 1.);
  TPad *c_2;// = new TPad("c_2", "_2", 0.  , 0., 1., 0.4);
  TPad *c_3;
  if (!doRatio) {
    c = new TCanvas("c","c",600,600);
  }
  else {
    c = new TCanvas("c","c",600,800);
    c_1 = new TPad("c_1", "_1", 0.  , 0.4, 1., 1.);
    c_2 = new TPad("c_2", "_2", 0.  , 0., 1., 0.4);
    c_1 -> Draw();
    c_2 -> Draw();
    //TPad *c_3 = new TPad("c_3", "_3", 0.129, 0.399, 0.16, 0.42);
    c_3 = new TPad("c_3", "_3", 0.115, 0.39, 0.16, 0.41);
    //c_3 -> Draw();
    
    c_1 -> SetBottomMargin(0.11);
    c_2 -> SetTopMargin(0.02);
    c_2 -> SetGridx();
    c_2 -> SetGridy();
    c_1 -> cd();
  }
  ////////////////////////////////////////////////////////////////////////////
  TString graphDrawOption0 = curveType!=2 ? "apl": "apc";
  TString graphDrawOption1 = curveType!=2 ? "pl" : "pc" ;   
  TString xTitle = curveType<2 or curveType==5 ? "p_{T} GeV" : "#eta";
  bool xLog      = curveType<2 or curveType==5;   bool yLog = 0;
  if(curveType==2) {
    //     graphDrawOption0 = "ac";
    //     graphDrawOption1 = "c"; 
    if      (sigBkg.substr(0,1)=="b")g_graphXmin = 0.5,    g_graphXmax = 1;  
    else if (sigBkg.substr(0,1)=="c")g_graphXmin = 0.1,    g_graphXmax = 0.4;  
    //g_graphXmin = 0.5,    g_graphXmax = 0.8;
    xTitle = sigBkg.substr(0,1)+(TString)"-jet efficiency";
    xLog=0; yLog=1;
    //if (sigBkg.substr(0,1)=="c") yLog=0;
  }

  //graphs[0]->GetXaxis()->SetLimits(g_graphXmin,g_graphXmax);
  // if (curveType==2) {
  //   // for (unsigned int i=0; i<graphs.size(); i++)
  //   //   if (graphs[i]) MyGraphCleaner(graphs[i]);
  // }
  if (graphs[0]) {                                            graphs[0]->Draw(graphDrawOption0);}
  for (unsigned int i=1; i<graphs.size(); i++) if (graphs[i]) graphs[i]->Draw(graphDrawOption1);
  graphs[0]->Draw(graphDrawOption1);
  graphs[0]->GetXaxis()->SetLimits(g_graphXmin,g_graphXmax);
  
  if (!doRatio) {
    c->SetLogx(xLog);
    c->SetLogy(yLog);
    c->SetGridx();
    c->SetGridy();
  }
  else {
    c_1->SetLogx(xLog);
    c_1->SetLogy(yLog);
    c_1->SetGridx();
    c_1->SetGridy();
  }

  graphs[0]->GetXaxis()->SetTitle(xTitle);
  graphs[0]->SetTitle(plotTitle);
  graphs[0]->GetYaxis()->SetTitle(yTitle);
  graphs[0]->GetXaxis()->SetNoExponent();
  graphs[0]->GetXaxis()->SetMoreLogLabels();
  graphs[0]->GetXaxis()->SetLabelSize(0.04);
  leg->Draw();

  gStyle->SetTitleX(0.3);
  gStyle->SetTitleY(0.99);

  vector<TH1F*> histVec;
  //if (curveType<2) for (unsigned int i=0; i<graphs.size(); i++) histVec . push_back( cloneGraph2Hist( graphs[i]  ) );
  if (curveType!=2) for (unsigned int i=0; i<graphs.size(); i++) histVec . push_back( cloneGraph2Hist( graphs[i]  ) );
  else           {
    for (unsigned int i=0; i<graphs.size(); i++) {
      //histVec . push_back( interpolatedHist( cloneGraph2Hist(graphs[i]) )  );
      histVec . push_back( interpolatedRoc( graphs[i] ));
    }
    vector<TH1F*> histoVec;
    for (unsigned int i=0; i<histVec.size(); i++) {
      histoVec.push_back( (TH1F*)histVec.at(i)->Clone(0));
      if (i==0) {
	histoVec.at(i)->GetXaxis()->SetTitle(xTitle);
	histoVec.at(i)->SetTitle(plotTitle);
	histoVec.at(i)->GetYaxis()->SetTitle(yTitle);
	histoVec.at(i)->GetXaxis()->SetNoExponent();
	histoVec.at(i)->GetXaxis()->SetMoreLogLabels();
	histoVec.at(i)->SetMinimum(1);
	//histoVec.at(i)->Draw("l");
      }
      //else      histoVec.at(i)->Draw("lsame");
    }
    gStyle->SetOptStat(0);
    
    //Text draw happens here
    TLatex tlatex;
    tlatex.SetTextSize(0.04);
    tlatex.DrawLatexNDC(0.2,0.35,"#bf{#it{ATLAS Internal}}");
    tlatex.DrawLatexNDC(0.2,0.30,"#it{t#bar{t}} simulation");
    tlatex.DrawLatexNDC(0.2,0.25,"#sqrt{s} = 13 TeV");
    //tlatex.DrawLatexNDC(0.2,0.25,"#sqrt{s} = 14 TeV");
    if      (inputFileName.Contains("_tm1")) tlatex.DrawLatexNDC(0.2,0.20,"p_{T}^{jet}>20 GeV, |#eta^{jet}| <2.5,  truth matched");
    else if (inputFileName.Contains("_tm0")) tlatex.DrawLatexNDC(0.2,0.20,"p_{T}^{jet}>20 GeV, |#eta^{jet}| <2.5, no truth match");
    else                                     tlatex.DrawLatexNDC(0.2,0.20,"p_{T}^{jet}>20 GeV, |#eta^{jet}| <2.5");

    if      (inputFileName.Contains("_jvf05"))   tlatex.DrawLatexNDC(0.2,0.15,"JVF>0.5");
    else if (inputFileName.Contains("_jvt02"))   tlatex.DrawLatexNDC(0.2,0.15,"JVT>0.2");
    else if (inputFileName.Contains("_jvt0941")) tlatex.DrawLatexNDC(0.2,0.15,"JVT>0.941");
  }
  leg->Draw();

  TString outName = plotName + targetEff + sigBkg;

  if (!doRatio) {
    c->SaveAs("plots/"+outName+".eps");
    c->SaveAs("plots/"+outName+".png");
    c->SaveAs("~/public_html/tmp_plots/"+outName+".png");
    return;
  }

  c_2->cd();
  gStyle->SetOptStat(0);

  TString ratioDrawOption = "e1";
  if (curveType==2) ratioDrawOption="c";
  
  drawRatios(histVec,graphs[0],"ratio to "+v_taggers[0],ratioDrawOption);
  c_2->SetLogx(c_1->GetLogx());

  TLine one(20,1,500,1);
  one.SetLineWidth(2);
  one.Draw();

  c->SaveAs("plots/"+outName+".eps");
  c->SaveAs("plots/"+outName+".png");
  c->SaveAs("plots/"+outName+".pdf");
  c->SaveAs("~/public_html/tmp_plots/"+outName+".pdf");

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*** below just tool functions which is used by top level function. ***/

TH1F *cloneGraph2Hist(TGraphErrors* graph) {//#KM converting a graph to a hist

  Double_t *x_graph  = graph->GetX();
  Double_t *Ex_graph = graph->GetEX();

  Double_t *y_graph  = graph->GetY();
  Double_t *Ey_graph = graph->GetEY();

  Double_t xbins[ graph->GetN() +1 ];

  for (int i=0; i<graph->GetN(); i++) {
    xbins[i] = x_graph[i]-Ex_graph[i];
    //cout<<xbins[i]<<endl;
    if(i==graph->GetN() -1) {
      xbins[i+1] = x_graph[i]+Ex_graph[i];
      //cout<<xbins[i+1]<<endl;
    }
  }

  TString histName = "h_" + (TString)graph->GetName();
  TH1F * hist  = new TH1F( histName, graph->GetTitle(), graph->GetN(), xbins);
  for (int i=1; i<hist->GetNbinsX()+1; i++) {
    hist->SetBinContent(i,y_graph[i-1]);
    hist->SetBinError(i,Ey_graph[i-1]);
  }

  // if (hist->GetBinWidth(hist->GetNbinsX()-1)>0.1)
  //   hist->SetBinContent(hist->GetNbinsX()-1,1.);

  hist->SetLineColor(graph->GetLineColor());
  hist->SetLineWidth(graph->GetLineWidth());
  hist->SetLineStyle(graph->GetLineStyle());
  hist->SetMarkerSize(graph->GetMarkerSize());
  hist->SetMarkerStyle(graph->GetMarkerStyle());
  hist->SetMarkerColor(graph->GetMarkerColor());
  
  return hist;
}

TH1F *interpolatedHist(TH1F *input) {//#KM for rejvseff plot, kind of smoothening
  
  TH1F * hist;
  int   nbins = 50;
  float xmin  = g_graphXmin, xmax  = g_graphXmax;  //float xmin  = 0.5, xmax  = 1;
  hist = new TH1F("int_"+(TString)input->GetName(),"",nbins,xmin,xmax);
  
  for (int i=1; i<nbins+1; i++) {
    float x = xmin + i*(xmax-xmin)/nbins - (xmax-xmin)/nbins/2;
    //cout<<"i= "<<i<<",\t x= "<<x<<",\t y= "<<input->Interpolate(x)<<endl;
    hist->SetBinContent(i,input->Interpolate( x ) );
  }
  hist->SetLineColor  (input->GetLineColor());
  hist->SetLineWidth  (input->GetLineWidth());
  hist->SetMarkerSize (input->GetMarkerSize());
  hist->SetMarkerStyle(input->GetMarkerStyle());
  hist->SetMarkerColor(input->GetMarkerColor());
  
  return hist;
}

TH1F* interpolatedRoc(TGraphErrors* input) {//#ELOI for rejvseff plot, kind of smoothening+ rej error correction
  
  TH1F * hist;
  int   nbins = 50;
  float xmin  = g_graphXmin, xmax  = g_graphXmax;  //float xmin  = 0.5, xmax  = 1;
  hist = new TH1F("int_"+(TString)input->GetName(),"",nbins,xmin,xmax);

  int npoints = input->GetN()/2; // arbitrary point
  /*** determine the # of evaluated u(or c)-jets  ***/
  double rndRej = input->GetY()[npoints];
  double rndRejErr = input->GetErrorY(npoints);
  double nBkgEval = pow(rndRej, 2)*(rndRej - 1) / pow(rndRejErr, 2);
  /*** determine the # of evaluated b-jets  ***/
  double rndEff = input->GetX()[npoints];
  double rndEffErr = input->GetErrorX(npoints);
  double nSigEval = rndEff * (1 - rndEff) / pow(rndEffErr, 2);
  
  double rejAtX = 1;
  double rejAtXErr2 = 0;  // error squared on u-jet rejection
  double effAtXErr = 0;   // error on b-jet efficiency
  double rejAtXErrFromBeffErr = 0; // propagation b-jet efficiency error to the rejection error
  for (int i=1; i<nbins+1; i++) {
    float x = xmin + i*(xmax-xmin)/nbins - (xmax-xmin)/nbins/2;
    rejAtX = input->Eval( x );
    hist->SetBinContent(i, rejAtX );

    rejAtXErr2 = rejAtX * rejAtX * ( rejAtX - 1 ) / nBkgEval ;
    effAtXErr = sqrt ( x * ( 1 - x ) / nSigEval ) ;
    rejAtXErrFromBeffErr = input->Eval( x - effAtXErr / 2) - input->Eval( x + effAtXErr / 2); // put it to 0 for no correction
    hist->SetBinError(i, sqrt ( rejAtXErr2  + rejAtXErrFromBeffErr * rejAtXErrFromBeffErr ) );
  }
  hist->SetLineColor  (input->GetLineColor());
  hist->SetLineWidth  (input->GetLineWidth());
  hist->SetMarkerSize (input->GetMarkerSize());
  hist->SetMarkerStyle(input->GetMarkerStyle());
  hist->SetMarkerColor(input->GetMarkerColor());
  
  return hist;
}

void drawRatios(vector<TH1F*> histVec, TGraphErrors* origGraph, TString yTitle, TString drawOption) {

  Double_t max_y = 0;
  Double_t min_y = 100;

  for (unsigned int i=0; i<histVec.size(); i++) {
    if (i==0) continue;
    else {
      histVec[i]->Divide(histVec[0]);
      if(i==1) {
	histVec[i]->SetTitle("");
	histVec[i]->SetXTitle( origGraph->GetXaxis()->GetTitle() );
	histVec[i]->SetYTitle( yTitle );
	histVec[i]->GetXaxis()->SetLimits       ( origGraph->GetXaxis()->GetXmin(),origGraph->GetXaxis()->GetXmax() );
	histVec[i]->GetXaxis()->SetMoreLogLabels( origGraph->GetXaxis()->GetMoreLogLabels() );
	histVec[i]->GetXaxis()->SetNoExponent   ( origGraph->GetXaxis()->GetNoExponent()    );
	histVec[i]->GetXaxis()->SetTitleSize    ( 0.06 );
	histVec[i]->GetYaxis()->SetTitleSize    ( 0.06 );
	histVec[i]->GetYaxis()->SetTitleOffset  ( 1.2 );
	if (drawOption.Contains("c")) {  // c = smoothed curve 
          TH1F* h1 = (TH1F*)histVec[i]->Clone();
          histVec[i] -> SetLineStyle  ( v_style[i]  );
          histVec[i]->Draw("hist,"+drawOption); // draw central value
          h1->SetFillColor(v_colors[i]);
          h1->SetFillStyle(3023); 
          h1->SetFillColor(v_colors[i]);
          h1->Draw(drawOption+"e4same"); // draw 1 sigma band
        } 
        else { histVec[i]->Draw(drawOption); }
	 
      }
      else {
	if (drawOption.Contains("c")) {  // c = smoothed curve 
          histVec[i] -> SetLineStyle  ( v_style[i]  );
          histVec[i]->DrawCopy("hist,"+drawOption+"same"); // draw central value
          histVec[i]->SetFillColor(v_colors[i]);
          histVec[i]->SetFillStyle(3023);
          histVec[i]->SetFillColor(v_colors[i]);
          histVec[i]->Draw(drawOption+"e4same"); // draw 1 sigma band
        } 
        else histVec[i]->Draw(drawOption+"same");
      }

      if (max_y<histVec[i]->GetMaximum() ) {
	max_y= histVec[i]->GetMaximum();
	histVec[1]->SetMaximum(max_y*1.20);
      }
      if (min_y>histVec[i]->GetMinimum() ) {
	min_y = histVec[i]->GetMinimum();
	histVec[1]->SetMinimum(min_y*0.80);
      }
      
    }
  }

  return;
}

void loadTaggers2draw(TString listFileName) {//vector<TString> loadTaggers2draw(TString listFileName) {
  v_colors.clear();
  v_style.clear();
  v_show.clear();
  v_taggers.clear();

  const map<TString,int> root_colors = {
    {"kWhite"  , kWhite  },    {"kBlack"  , kBlack  },    {"kGray"   , kGray   },
    {"kRed"    , kRed    },    {"kGreen"  , kGreen  },    {"kBlue"   , kBlue   },
    {"kYellow" , kYellow },    {"kMagenta", kMagenta},    {"kCyan"   , kCyan   },
    {"kOrange" , kOrange },    {"kSpring" , kSpring },    {"kTeal"   , kTeal   },
    {"kAzure"  , kAzure  },    {"kViolet" , kViolet },    {"kPink"   , kPink   },
  };

  string filename = listFileName.Data();
  ifstream ifs(filename.data());
  string aLine;
  vector<TString> varlist;
  if (ifs.fail()) {
    cerr<<"Failure when reading a file: "<<listFileName<<endl;
    exit(1);
  }
  else {
    while (getline(ifs,aLine)) {
      //cout<<aLine<<endl;
      TString ts_aLine=aLine.data();
      if (ts_aLine.BeginsWith("#")) continue;
      
      TString var   = aLine.substr(0,aLine.find(","));
      aLine.erase(0,aLine.find(",")+1);
      TString color = aLine.substr(0,(aLine.find(",")!=string::npos?aLine.find(","):-1));
      aLine.erase(0,aLine.find(",")+1);
      TString style = aLine.substr(0,(aLine.find(",")!=string::npos?aLine.find(","):-1));
      aLine.erase(0,aLine.find(",")+1);
      TString show  = aLine.substr(0,(aLine.find(",")!=string::npos?aLine.find(","):-1));

      color.ReplaceAll("\t","");
      style.ReplaceAll("\t","");
      show .ReplaceAll("\t","");

      const int style_code=style.Atoi();
      
      int color_code=0;
      for (auto colors: root_colors) {
	if (color.Contains(colors.first)) {
	  color_code+=colors.second;
	  if(color.Contains("+") or color.Contains("-")) {
	    int color2add=0;
	    string s_color=color.Data();
	    s_color=s_color.substr(s_color.find("+")+1,-1);
	    color2add=stoi(s_color);
	    if (color.Contains("-")) color2add*=-1;
	    color_code+=color2add;
	  }
	}
      }
      //cout<<var<<","<<color<<"="<<color_code<<","<<style<<","<<show<<endl;
      v_taggers.push_back(var);//varlist.push_back(var);
      v_colors.push_back(color_code);
      v_style.push_back(style_code);
      v_show.push_back(show=="0"?"":show);
    }
  }

  return;  //return varlist;
};
