#include "RejectionTool.h"

#include <math.h>
#include <iostream>
#include <TClass.h>

RejectionTool::RejectionTool() {
  m_hsig = 0;
  m_hbkg = 0;
  m_reversecut = 0;
  m_rejVsEff = 0;
  m_cutVsEff = 0;
}

RejectionTool::RejectionTool(TGraphErrors* rej, TGraphErrors* cut) {
  m_hsig = 0;
  m_hbkg = 0;
  m_reversecut = 0;
  m_rejVsEff = (TGraphErrors*)rej->Clone();
  m_cutVsEff = (TGraphErrors*)cut->Clone();
}

RejectionTool::RejectionTool(TH1 *hsig, TH1 *hbkg, bool reversecut) {
  m_hsig = hsig;
  m_hbkg = hbkg;
  m_reversecut = reversecut;
  TString type = hsig->IsA()->GetName();
  if( type.Contains("TH1") ){
    init1D(hsig, hbkg);
    //init1D_constBin(hsig, hbkg);
  }else{
    std::cout << "Error in RejectionTool::RejectionTool(): Unknown histogram type: " 
              << type << std::endl;
  }
}

RejectionTool::RejectionTool(TH2 *hsig, TH2 *hbkg, float start, float finish) {
  m_reversecut = 0;
  TString type = hsig->IsA()->GetName();
  if( type.Contains("TH2") ) {
    init1D(hsig, hbkg, start, finish);
  }
  else{
    std::cout << "Error in RejectionTool::RejectionTool(): Unknown histogram type: " 
              << type << std::endl;
  }
}

RejectionTool::RejectionTool(TH1 *hsig, TH1 *hbkg, double eff, double cut, double rej, bool reversecut) {
  m_hsig = hsig;
  m_hbkg = hbkg;
  m_reversecut = reversecut;
  TString type = hsig->IsA()->GetName();
  if( type.Contains("TH1") ){
    init1D(hsig, hbkg);
  }else if( type.Contains("TH2") ){
    initRej2D((TH2*)hsig, (TH2*)hbkg, eff);
    initRejAndEffwithCut2D((TH2*)hsig, (TH2*)hbkg, cut);
    initEff2D((TH2*)hsig, (TH2*)hbkg, rej);
  }else{
    std::cout << "Error in RejectionTool::RejectionTool(): Unknown histogram type: " 
              << type << std::endl;
  }
}

RejectionTool::RejectionTool(TH1 *hsig, TH1 *hbkg, TGraph *effshape, double eff, bool reversecut) {
  m_hsig = hsig;
  m_hbkg = hbkg;
  m_reversecut = reversecut;
  TString type = hsig->IsA()->GetName();
  if( type.Contains("TH1") ){
    std::cerr << "You shouldn't end up here" << std::endl;
    exit(0);
  }else if( type.Contains("TH2") ){
    initRej2D((TH2*)hsig, (TH2*)hbkg, effshape, eff);
  }else{
    std::cout << "Error in RejectionTool::RejectionTool(): Unknown histogram type: " 
	      << type << std::endl;
  }
}

TH1* RejectionTool::makeCDF1(TH1* input1d) {
  TString newname=(TString)input1d->GetName()+"_CDF1";
  TH1* cdfu = (TH1*) input1d->Clone(newname);
  cdfu->Scale(1/cdfu->Integral());
  cdfu->ComputeIntegral();
  Double_t* cdf_UcontentArray = cdfu->GetIntegral();
  cdfu->SetContent(cdf_UcontentArray);
  return cdfu;
}

TH2* RejectionTool::makeCDF2(TH2* input2d) {
  //create new pointer to give back
  TString newname=(TString)input2d->GetName()+"_CDF2";
  TH2* cdf2d = (TH2*)input2d->Clone(newname);
  const int xbins = cdf2d->GetNbinsX();
  const int ybins = cdf2d->GetNbinsY();

  //create new pointer to count and set the bin content
  TString tmpname=(TString)input2d->GetName()+"_CDF2tmp";
  TH2* cdf2d_tmp = (TH2*)input2d->Clone(tmpname);
  cdf2d_tmp->Scale(1/cdf2d_tmp->Integral(0, xbins+1, 0, ybins+1 ) );

  //set the bin contents using tmp which is normalized
  for (int i=0; i<(xbins+2)*(ybins+2); i++)
    cdf2d->SetBinContent( i, cdf2d_tmp->Integral( 0, i%(xbins+2), 0 , (int)floor(i/(xbins+2)) ) );

  if (cdf2d_tmp) delete cdf2d_tmp;
  return cdf2d;
}

void RejectionTool::init1D(TH2 *hsig2, TH2 *hbkg2, float start, float finish) {
  const TString newname_sig = (TString)hsig2->GetName()+"_py";
  const TString newname_bkg = (TString)hbkg2->GetName()+"_py";
  if (start==0 and finish==1e6) {
    if      (newname_sig.Contains("VSpt"))  start=20.1, finish=499.9;
    else if (newname_sig.Contains("VSeta")) start=0.1 , finish=2.49;
    else {
      cerr<<"Unknown type of TH2 given, aborting... newname_sig="<<newname_sig<<endl;exit(1);
    }
  }
  TH1* hsig = (TH1*)hsig2->ProjectionY(newname_sig, hsig2->FindBin(start,-100), hsig2->FindBin(finish,100) );
  TH1* hbkg = (TH1*)hbkg2->ProjectionY(newname_bkg, hbkg2->FindBin(start,-100), hbkg2->FindBin(finish,100) );
  m_hsig = hsig;
  m_hbkg = hbkg;
  init1D(hsig,hbkg);
  //init1D_constBin(hsig,hbkg);
}

void RejectionTool::init1D(TH1 *hsig, TH1 *hbkg) {
  int nbins = hsig->GetNbinsX();
  m_rejVsEff = new TGraphErrors(nbins);
  m_cutVsEff = new TGraph(nbins);
  int inf = 0;
  int sup = nbins+1;
  double Isig = hsig->Integral(inf,sup);
  double Ibkg = hbkg->Integral(inf,sup);
  int point = 0;
  for(int cut=inf; cut<sup; cut++) {
    double sig = hsig->Integral(cut,sup);
    double bkg = hbkg->Integral(cut,sup);
    double cutVal = hsig->GetBinLowEdge(cut);
    if(m_reversecut){
      sig = hsig->Integral(inf,cut);
      bkg = hbkg->Integral(inf,cut);
      cutVal = hsig->GetBinLowEdge(cut+1);
    }
    double eff = 0;
    double rej = 0;
    double efferr = 0;
    double rejerr = 0;
    if(Isig != 0){
      eff = sig / Isig;
      efferr = sqrt( eff * ( 1 - eff ) / Isig );
    }
    if(bkg != 0){
      rej = Ibkg / bkg;
      rejerr = sqrt( rej * ( rej - 1 ) / bkg );
    }
    m_rejVsEff->SetPoint(point, eff, rej);
    m_rejVsEff->SetPointError(point, efferr, rejerr);
    m_cutVsEff->SetPoint(point, eff, cutVal);
    point++;
  }
  m_rejVsEff->Sort();
  m_cutVsEff->Sort();
}

void RejectionTool::init1D_constBin(TH1 *hsig, TH1 *hbkg) {
  int nbins = hsig->GetNbinsX();
  m_rejVsEff = new TGraphErrors(nbins);
  m_cutVsEff = new TGraph(nbins);
  int inf = 0;
  int sup = nbins+1;
  double Isig = hsig->Integral(inf,sup);
  double Ibkg = hbkg->Integral(inf,sup);
  int point = 0;
  
  TH1F* hcdf = (TH1F*) makeCDF1(hsig);

  vector<float> MINs;
  vector<unsigned> OPs,BINs;
  for (unsigned i=0;i<100;i++) {
    OPs.push_back(i);
    MINs.push_back(1e4);
    BINs.push_back(0);
  }
  for (unsigned i=0; (int)i<hcdf->GetNbinsX(); i++) {
    for (unsigned j=0; j<OPs.size(); j++) {
      float resid=fabs((float)OPs.at(j)/100. - (1-hcdf->GetBinContent(i)));
      if (resid<MINs.at(j)) {
	BINs.at(j)=i;
	MINs.at(j)=resid;
      }
    }
  }

  int currentBinNum=-1;
  for (unsigned ib=1; ib<BINs.size(); ib++) {
    if ( (OPs.at(ib))%5>0 and currentBinNum==(int)BINs.at(ib)) continue;
    //cout<<OPs.at(ib)<<"\t"<<BINs.at(ib)<<"\t"<<MINs.at(ib)<<endl;
    double sig = hsig->Integral(BINs.at(ib),sup);
    double bkg = hbkg->Integral(BINs.at(ib),sup);
    double cutVal = hsig->GetBinLowEdge(BINs.at(ib));
    if(m_reversecut) {
      sig = hsig->Integral(inf,BINs.at(ib));
      bkg = hbkg->Integral(inf,BINs.at(ib));
      cutVal = hsig->GetBinLowEdge(BINs.at(ib)+1);
    }
    double eff = 0;
    double rej = 0;
    double efferr = 0;
    double rejerr = 0;
    if(Isig != 0){
      eff = sig / Isig;
      efferr = sqrt( eff * ( 1 - eff ) / Isig );
    }
    if(bkg != 0) {
      rej = Ibkg / bkg;
      rejerr = sqrt( rej * ( rej - 1 ) / bkg );
    }

    m_rejVsEff->SetPoint(point, OPs.at(ib)/100., rej);
    //m_rejVsEff->SetPoint(point, eff, rej);
    m_rejVsEff->SetPointError(point, efferr, rejerr);
    m_cutVsEff->SetPoint(point, eff, cutVal);
    point++;
    currentBinNum=BINs.at(ib);
  }
  m_rejVsEff->Sort();
  m_cutVsEff->Sort();
}


void RejectionTool::initRej2D(TH2 *hsig, TH2 *hbkg, double eff) {
  int nbinsx = hsig->GetNbinsX();
  int nbinsy = hsig->GetNbinsY();
  m_rejVsX = new TGraphErrors(nbinsx);
  m_cutVsX = new TGraphErrors(nbinsx);
  for(int binx=1; binx<=nbinsx; binx++) {
    double Isig = hsig->Integral(binx, binx, 0, nbinsy+1);
    double Ibkg = hbkg->Integral(binx, binx, 0, nbinsy+1);
    for(int biny=1; biny<nbinsy; biny++) {
      double siginf = hsig->Integral(binx, binx, biny, nbinsy+1);
      double bkginf = hbkg->Integral(binx, binx, biny, nbinsy+1);
      double sigsup = hsig->Integral(binx, binx, biny+1, nbinsy+1);
      double bkgsup = hbkg->Integral(binx, binx, biny+1, nbinsy+1);
      double effinf = 0;
      double rejinf = 0;
      double effsup = 0;
      double rejsup = 0;
      double rej = 0;
      double efferr = 0;
      double rejerr = 0;
      double cuterr = 0;
      //Experimental stuff for pT-dependent benchmarks

      double cut = 999;
      double winf = hsig->GetYaxis()->GetBinCenter(biny);   // signal or not,
      double wsup = hsig->GetYaxis()->GetBinCenter(biny+1); // it should hold the same bin nb

      //////////////////////////////////
      if(Isig != 0) {
	    effinf = siginf / Isig;
	    effsup = sigsup / Isig;
        efferr = sqrt( sigsup*(Isig-sigsup)/Isig )/Isig;
      }
      if(bkginf != 0 && bkgsup != 0) {
	    rejinf = Ibkg / bkginf;
	    rejsup = Ibkg / bkgsup;
	    rejerr = sqrt( rejinf * ( rejinf - 1 ) / bkginf );
	    cuterr = sqrt( rejinf * ( rejinf - 1 ) / bkginf );
      }
      // fill rejection:
      if(effinf >= eff && effsup <= eff) {
	    rej = rejinf;
	    if(effinf != effsup) rej = rejinf + 
				   (rejinf - rejsup)*(eff - effinf)/(effinf - effsup);
	    m_rejVsX->SetPoint(binx-1, hsig->GetXaxis()->GetBinCenter(binx), rej);
	    m_rejVsX->SetPointError(binx-1, hsig->GetXaxis()->GetBinWidth(binx)/2, rejerr);

	    // cut Vs pT
	    cut = winf;
	    // if(effinf != effsup) cut = winf + 
	    // 			   (winf - wsup)*(eff - effinf)/(effinf - effsup);
	    m_cutVsX->SetPoint(binx-1, hsig->GetXaxis()->GetBinCenter(binx), cut);
	    break;
      }
    }
  }
}

void RejectionTool::initRej2D(TH2 *hsig, TH2 *hbkg, TGraph *effshape, double localeff) {
  int nbinsx = hsig->GetNbinsX();
  int nbinsy = hsig->GetNbinsY();
  m_rejVsX = new TGraphErrors(nbinsx);
  m_cutVsX = new TGraphErrors(nbinsx);
  double lighteff = 0.;
  double Nlighttagged = 0.;
  for(int binx=1; binx<=nbinsx; binx++) {
    double Isig = hsig->Integral(binx, binx, 0, nbinsy+1);
    double Ibkg = hbkg->Integral(binx, binx, 0, nbinsy+1);
    double eff = effshape->GetY()[binx-1];
    for(int biny=1; biny<nbinsy; biny++) {
      double siginf = hsig->Integral(binx, binx, biny, nbinsy+1);
      double bkginf = hbkg->Integral(binx, binx, biny, nbinsy+1);
      double sigsup = hsig->Integral(binx, binx, biny+1, nbinsy+1);
      double bkgsup = hbkg->Integral(binx, binx, biny+1, nbinsy+1);
      double effinf = 0;
      double rejinf = 0;
      double effsup = 0;
      double rejsup = 0;
      double rej = 0;
      double efferr = 0;
      double rejerr = 0;
      double cuterr = 0;
      //Experimental stuff for pT-dependent benchmarks

      double cut = 999;
      double winf = hsig->GetYaxis()->GetBinCenter(biny);   // signal or not,
      double wsup = hsig->GetYaxis()->GetBinCenter(biny+1); // it should hold the same bin nb

      //////////////////////////////////
      if(Isig != 0) {
	    effinf = siginf / Isig;
	    effsup = sigsup / Isig;
        efferr = sqrt( sigsup*(Isig-sigsup)/Isig )/Isig;
      }
      if(bkginf != 0 && bkgsup != 0) {
	    rejinf = Ibkg / bkginf;
	    rejsup = Ibkg / bkgsup;
	    rejerr = sqrt( rejinf * ( rejinf - 1 ) / bkginf );
	    cuterr = sqrt( rejinf * ( rejinf - 1 ) / bkginf );
      }
      // fill rejection:
      if(effinf >= eff && effsup <= eff) {
	    rej = rejinf;
	    if(effinf != effsup) rej = rejinf + 
				   (rejinf - rejsup)*(eff - effinf)/(effinf - effsup);
	    m_rejVsX->SetPoint(binx-1, hsig->GetXaxis()->GetBinCenter(binx), rej);
	    m_rejVsX->SetPointError(binx-1, hsig->GetXaxis()->GetBinWidth(binx)/2, rejerr);
	    
	    lighteff = 1./rej;
	    Nlighttagged += lighteff*Ibkg;

	    // cut Vs pT
	    cut = winf;
	    if(effinf != effsup) cut = winf + 
				   (winf - wsup)*(eff - effinf)/(effinf - effsup);
	    m_cutVsX->SetPoint(binx-1, hsig->GetXaxis()->GetBinCenter(binx), cut);
	    break;
      }
    }// 2D loop
  }
  std::cout << " MV3: "<< localeff << " : " << 1./(Nlighttagged/hbkg->Integral()) << std::endl;
}

void RejectionTool::initRejAndEffwithCut2D(TH2 *hsig, TH2 *hbkg, double wcut) {
  int nbinsx = hsig->GetNbinsX();
  int nbinsy = hsig->GetNbinsY();
  m_rejFromCutVsX = new TGraphErrors(nbinsx);
  m_effFromCutVsX = new TGraphErrors(nbinsx);
  for(int binx=1; binx<=nbinsx; binx++) {
    double Isig = hsig->Integral(binx, binx, 0, nbinsy+1);
    double Ibkg = hbkg->Integral(binx, binx, 0, nbinsy+1);
    for(int biny=1; biny<nbinsy; biny++) {
      double siginf = hsig->Integral(binx, binx, biny, nbinsy+1);
      double bkginf = hbkg->Integral(binx, binx, biny, nbinsy+1);
      double sigsup = hsig->Integral(binx, binx, biny+1, nbinsy+1);
      double bkgsup = hbkg->Integral(binx, binx, biny+1, nbinsy+1);
      double eff = 0.;
      double effinf = 0;
      double rejinf = 0;
      double effsup = 0;
      double rejsup = 0;
      double rej = 0;
      double efferr = 0;
      double rejerr = 0;
      double winf = hsig->GetYaxis()->GetBinCenter(biny);   // signal or not,
      double wsup = hsig->GetYaxis()->GetBinCenter(biny+1); // it should hold the same bin nb
      double werr = 0;

      if(Isig != 0) {
       	effinf = siginf / Isig;
       	effsup = sigsup / Isig;
	efferr = sqrt( sigsup*(Isig-sigsup)/Isig )/Isig;
      }
      if(bkginf != 0 && bkgsup != 0) {
	rejinf = Ibkg / bkginf;
	rejsup = Ibkg / bkgsup;
	rejerr = sqrt( rejinf * ( rejinf - 1 ) / bkginf );
      }
      // fill rejection:
      if((winf <= wcut && wsup >= wcut) || winf==wcut) {
	rej = rejinf;
	eff = effinf;
	//        effi= effinf;
	// if(rejinf != rejsup) effi = effinf + 
	// 		       (effinf - effsup)*(arej - rejinf)/(rejinf - rejsup);
	if(winf != wsup){
	  rej = rejinf + 
	    (rejinf - rejsup)*(wcut - winf)/(winf - wsup);
	  eff = effinf +
	    (effinf - effsup)*(wcut - winf)/(winf - wsup);
	}
	// if(effinf != effsup){
	//   rej = rejinf + 
	//     (rejinf - rejsup)*(eff - effinf)/(effinf - effsup);
	//	}
	m_rejFromCutVsX->SetPoint(binx-1, hsig->GetXaxis()->GetBinCenter(binx), rej);
	m_rejFromCutVsX->SetPointError(binx-1, hsig->GetXaxis()->GetBinWidth(binx)/2, rejerr);

	m_effFromCutVsX->SetPoint(binx-1, hsig->GetXaxis()->GetBinCenter(binx), eff);
	m_effFromCutVsX->SetPointError(binx-1, hsig->GetXaxis()->GetBinWidth(binx)/2, efferr);
	break;
      }
    }
  }
}

void RejectionTool::initEff2D(TH2 *hsig, TH2 *hbkg, double arej) {
  int nbinsx = hsig->GetNbinsX();
  int nbinsy = hsig->GetNbinsY();
  m_effVsX = new TGraphErrors(nbinsx);
  for(int binx=1; binx<=nbinsx; binx++) {
    double Isig = hsig->Integral(binx, binx, 0, nbinsy+1);
    double Ibkg = hbkg->Integral(binx, binx, 0, nbinsy+1);
    for(int biny=1; biny<nbinsy; biny++) {
      double siginf = hsig->Integral(binx, binx, biny, nbinsy+1);
      double bkginf = hbkg->Integral(binx, binx, biny, nbinsy+1);
      double sigsup = hsig->Integral(binx, binx, biny+1, nbinsy+1);
      double bkgsup = hbkg->Integral(binx, binx, biny+1, nbinsy+1);
      double effinf = 0;
      double rejinf = 0;
      double effsup = 0;
      double rejsup = 0;
      double effi = 0;
      double efferr = 0;
      double rejerr = 0;
      if(Isig != 0) {
	    effinf = siginf / Isig;
	    effsup = sigsup / Isig;
        efferr = sqrt( sigsup*(Isig-sigsup)/Isig )/Isig;
      }
      if(bkginf != 0 && bkgsup != 0) {
	    rejinf = Ibkg / bkginf;
	    rejsup = Ibkg / bkgsup;
	    rejerr = sqrt( rejinf * ( rejinf - 1 ) / bkginf );
      }
      // fill efficiency for the integrated rejection:
      //std::cout<<"arej="<<arej<<" for eff="<<eff<<".rej[]="<<rejinf<<" "<<rejsup<<std::endl;
      if(rejsup >= arej && rejinf <= arej) {
        effi= effinf;
	    if(rejinf != rejsup) effi = effinf + 
	      (effinf - effsup)*(arej - rejinf)/(rejinf - rejsup);
        //std::cout<<"arej="<<arej<<" for eff="<<eff<<".rej[]="<<rejinf<<" "<<rejsup<<std::endl;
        //std::cout<<"--> effinf="<<effinf<<" effsup="<<effsup<<" eff="<<effi<<std::endl;
	    m_effVsX->SetPoint(binx-1, hsig->GetXaxis()->GetBinCenter(binx), effi);
	    m_effVsX->SetPointError(binx-1, hsig->GetXaxis()->GetBinWidth(binx)/2, efferr);
	    break;
      }
    }
  }
}


TGraphErrors *RejectionTool::getRejVsX() {
  return (TGraphErrors*)m_rejVsX->Clone();
}

TGraphErrors *RejectionTool::getCutVsX() {
  return (TGraphErrors*)m_cutVsX->Clone();
}

TGraphErrors *RejectionTool::getRejFromCutVsX() {
  return (TGraphErrors*)m_rejFromCutVsX->Clone();
}

TGraphErrors *RejectionTool::getEffVsX() {
  return (TGraphErrors*)m_effVsX->Clone();
}

TGraphErrors *RejectionTool::getEffFromCutVsX() {
  return (TGraphErrors*)m_effFromCutVsX->Clone();
}


double RejectionTool::getRej(double eff) {
  double r,e,w;
  this->getRej(eff, r, e, w);
  return r;
}


void RejectionTool::getRej(double eff, double &r, double &e, double &w) {
  double *rej = this->getRejWithErr(eff);
  r = rej[0];
  e = rej[1];
  w = rej[2];
  delete [] rej;
}


double *RejectionTool::getRejWithErr(double eff) {
  double *rej = new double[3];
  int np = m_rejVsEff->GetN();
  for(int p=0; p<np-1; p++){
    double effinf, rejinf, rejerrinf, cutinf;
    double effsup, rejsup, rejerrsup, cutsup;
    m_cutVsEff->GetPoint(p, effinf, cutinf);
    m_cutVsEff->GetPoint(p+1, effsup, cutsup);
    m_rejVsEff->GetPoint(p, effinf, rejinf);
    m_rejVsEff->GetPoint(p+1, effsup, rejsup);
    rejerrinf = m_rejVsEff->GetErrorY(p);
    rejerrsup = m_rejVsEff->GetErrorY(p+1);
    if(effinf <= eff && effsup > eff){
      rej[0] = rejinf + (eff - effinf)*(rejinf-rejsup)/(effinf - effsup);
      rej[1] = rejerrinf + (eff - effinf)*(rejerrinf-rejerrsup)/(effinf - effsup);
      rej[2] = cutinf + (eff - effinf)*(cutinf-cutsup)/(effinf - effsup);
      break;
    }
  }
  return rej;
}


TGraphErrors* RejectionTool::getRejVsEff() {
    return (TGraphErrors*)m_rejVsEff->Clone();
}


TGraphErrors *RejectionTool::Draw(Option_t *opt) {
  return (TGraphErrors*)m_rejVsEff->DrawClone(opt);
}


TGraphErrors* RejectionTool::divide(RejectionTool *rejVsEffTool) {
  int npoints = m_rejVsEff->GetN();
  TGraphErrors *g_imp = new TGraphErrors(npoints);
  for(int point=0; point<npoints; point++){
    double eff = 0;
    double rej = 0;
    double efferr = 0;
    double rejerr = 0;
    m_rejVsEff->GetPoint(point, eff, rej);
    efferr = m_rejVsEff->GetErrorX(point);
    rejerr = m_rejVsEff->GetErrorY(point);
    double oldrej = rejVsEffTool->getRej(eff);
    double imp = oldrej!=0?rej/oldrej:0;
    double imperr = oldrej!=0?2*rejerr/oldrej:0;
    g_imp->SetPoint(point, eff, imp);
    g_imp->SetPointError(point, efferr, imperr);
  }
  return (TGraphErrors*)g_imp->Clone();
}

TGraphErrors* RejectionTool::divideVsX(RejectionTool *rejTool) {
  int npoints = m_rejVsX->GetN();
  TGraphErrors* g_imp = new TGraphErrors(npoints);
  TGraphErrors* g_old = rejTool->getRejVsX();
  for(int point=0; point<npoints; point++){
    double eff = 0;
    double rej = 0;
    double efferr = 0;
    double rejerr = 0;
    m_rejVsX->GetPoint(point, eff, rej);
    efferr = m_rejVsX->GetErrorX(point);
    rejerr = m_rejVsX->GetErrorY(point);
    double oldrej = g_old->Eval(eff);
    double imp = oldrej!=0?rej/oldrej:0;
    double imperr = oldrej!=0?2*rejerr/oldrej:0;
    g_imp->SetPoint(point, eff, imp);
    g_imp->SetPointError(point, efferr, imperr);
  }
  return (TGraphErrors*)g_imp->Clone();
}


TGraphErrors* RejectionTool::cloneRejVsEff(TString name) {
  TGraphErrors* tmp = (TGraphErrors*)m_rejVsEff->Clone();
  tmp->SetName(name);
  return tmp;
}


TGraph* RejectionTool::cloneCutVsEff(TString name) {
  TGraph* tmp = (TGraph*)m_cutVsEff->Clone();
  tmp->SetName(name);
  return tmp;
}

