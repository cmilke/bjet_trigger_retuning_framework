#ifndef REJECTIONTOOL_H
#define REJECTIONTOOL_H

#include <TGraphErrors.h>
#include <TGraph.h>
#include <TH1.h>
#include <TH2.h>
#include "TString.h"


class RejectionTool {

public:
  RejectionTool();
  RejectionTool(TGraphErrors* rej, TGraphErrors* cut);
  RejectionTool(TH1 *hsig, TH1 *hbkg, bool reversecut=false);
  RejectionTool(TH2 *hsig, TH2 *hbkg, float start=0, float finish=1e6);
  // to compute efficiency and rejection versus variable X (arguments are actual TH2):
  RejectionTool(TH1 *hsig, TH1 *hbkg, double eff, double cut, double rej, bool reversecut=false);
  RejectionTool(TH1 *hsig, TH1 *hbkg, TGraph *effshape, double eff, bool reversecut=false);

  double  getRej(double eff);
  void    getRej(double eff, double &r, double &err, double &w);
  double* getRejWithErr(double eff);

  TGraphErrors* getRejVsEff();
  TGraphErrors* getRejVsX();
  TGraphErrors* getCutVsX();
  TGraphErrors* getRejFromCutVsX();
  TGraphErrors* getEffVsX();
  TGraphErrors* getEffFromCutVsX();
  TGraph*       getCutVsEff(){return m_cutVsEff;};
  TGraphErrors* divide(RejectionTool *rejTool);
  TGraphErrors* divideVsX(RejectionTool *rejTool);
  TGraphErrors* Draw(Option_t *opt="");

  TGraphErrors* cloneRejVsEff(TString name);
  TGraph*       cloneCutVsEff(TString name);

private:
  TH1* makeCDF1(TH1* input1d);
  TH2* makeCDF2(TH2* input2d);
  void init1D(TH2 *hsig, TH2 *hbkg,float start, float finish);
  void init1D(TH1 *hsig, TH1 *hbkg);
  void init1D_constBin(TH1 *hsig, TH1 *hbkg);
  // to compute efficiency and rejection versus variable X: provide efficiency (for rej plot) 
  // and integrated rejection (for efficiency plot):
  void initRej2D(TH2 *hsig, TH2 *hbkg, double eff);
  void initRej2D(TH2 *hsig, TH2 *hbkg, TGraph *effshape, double eff);
  void initRejAndEffwithCut2D(TH2 *hsig, TH2 *hbkg, double eff);
  void initEff2D(TH2 *hsig, TH2 *hbkg, double rej);
  TGraphErrors* m_rejVsEff;
  TGraph* m_cutVsEff;
  TGraphErrors* m_rejVsX;
  TGraphErrors* m_cutVsX;
  TGraphErrors* m_rejFromCutVsX;
  TGraphErrors* m_effVsX;
  TGraphErrors* m_effFromCutVsX;
  TH1* m_hsig;
  TH1* m_hbkg;
  bool m_reversecut;
};

#endif // REJECTIONTOOL_H
