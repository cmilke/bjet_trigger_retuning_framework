//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Dec 15 21:10:36 2014 by ROOT version 5.34/19
// from TTree bTag/bTag
// found on file: group.perf-flavtag.mc14_13TeV.110401.PowhegPythia_nonallhad.merge.AOD.e2928_s1982_s2008_r5787_r5853.BTAGNTUP_v00b_BTAGSTREAM.root
//////////////////////////////////////////////////////////

#ifndef bTag_h
#define bTag_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
using std::vector;

// Fixed size dimensions of array or collections stored in the TTree if any.

class bTag {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runnb;
   Int_t           eventnb;
   Int_t           mcchan;
   Double_t        mcwg;
   Int_t           nPV;
   Double_t        avgmu;
   Double_t        PVx;
   Double_t        PVy;
   Double_t        PVz;
   Int_t           njets;
   Int_t           nbjets;
   Int_t           nbjets_q;
   Int_t           nbjets_HadI;
   Int_t           nbjets_HadF;
   vector<float>   *jet_pt;
   vector<bool>   *jet_ForHybrid;
   vector<float>   *jet_eta;
   vector<float>   *jet_pt_orig;
   vector<float>   *jet_eta_orig;
   vector<float>   *jet_phi;
   vector<float>   *jet_E;
   vector<float>   *jet_m;
   vector<int>     *jet_truthflav;
   vector<int>     *jet_GhostL_q;
   vector<int>     *jet_GhostL_HadI;
   vector<int>     *jet_GhostL_HadF;
   vector<int>     *jet_aliveAfterOR;
   vector<int>     *jet_truthMatch;
   vector<float>   *jet_truthPt;
   vector<float>   *jet_dRiso;
   vector<float>   *jet_JVF;
   vector<float>   *jet_JVT;
   vector<float>   *jet_ip2d_pb;
   vector<float>   *jet_ip2d_pc;
   vector<float>   *jet_ip2d_pu;
   vector<float>   *jet_ip2d_llr;
   vector<float>   *jet_ip3d_pb;
   vector<float>   *jet_ip3d_pc;
   vector<float>   *jet_ip3d_pu;
   vector<float>   *jet_ip3d_llr;
   vector<float>   *jet_sv0_sig3d;
   vector<int>     *jet_sv0_ntrkj;
   vector<int>     *jet_sv0_ntrkv;
   vector<int>     *jet_sv0_n2t;
   vector<float>   *jet_sv0_m;
   vector<float>   *jet_sv0_efc;
   vector<float>   *jet_sv0_normdist;
   vector<vector<float> > *jet_sv0_vtxx;
   vector<vector<float> > *jet_sv0_vtxy;
   vector<vector<float> > *jet_sv0_vtxz;
   vector<int>     *jet_sv1_ntrkj;
   vector<int>     *jet_sv1_ntrkv;
   vector<int>     *jet_sv1_n2t;
   vector<float>   *jet_sv1_m;
   vector<float>   *jet_sv1_efc;
   vector<float>   *jet_sv1_normdist;
   vector<float>   *jet_sv1_pb;
   vector<float>   *jet_sv1_pc;
   vector<float>   *jet_sv1_pu;
   vector<float>   *jet_sv1_llr;
   vector<float>   *jet_sv1_sig3d;
   vector<float>   *jet_sv1_dR; // FLS
   vector<float>   *jet_sv1_Lxy; // FLS
   vector<float>   *jet_sv1_L3d; // FLS
   vector<vector<float> > *jet_sv1_vtxx;
   vector<vector<float> > *jet_sv1_vtxy;
   vector<vector<float> > *jet_sv1_vtxz;
   vector<float>   *jet_jf_pb;
   vector<float>   *jet_jf_pc;
   vector<float>   *jet_jf_pu;
   vector<float>   *jet_jf_llr;
   vector<float>   *jet_jf_m;
   vector<float>   *jet_jf_efc;
   vector<float>   *jet_jf_deta;
   vector<float>   *jet_jf_dphi;
   vector<float>   *jet_jf_ntrkAtVx;
   vector<int>     *jet_jf_nvtx;
   vector<float>   *jet_jf_sig3d;
   vector<int>     *jet_jf_nvtx1t;
   vector<int>     *jet_jf_n2t;
   vector<vector<float> > *jet_jf_chi2;
   vector<vector<float> > *jet_jf_ndf;
   vector<float>   *jet_jfcombnn_pb;
   vector<float>   *jet_jfcombnn_pc;
   vector<float>   *jet_jfcombnn_pu;
   vector<float>   *jet_jfcombnn_llr;
   vector<double>  *jet_sv1ip3d;
   vector<double>  *jet_mv1;
   vector<double>  *jet_mv1c;
   vector<double>  *jet_mv2c00;
   vector<double>  *jet_mv2c10;
   vector<double>  *jet_mv2c20;
   vector<double>  *jet_mv2c100;
   vector<double>  *jet_mv2m_pb;
   vector<double>  *jet_mv2m_pu;
   vector<double>  *jet_mv2m_pc;
   vector<double>  *jet_mvb;
   vector<float>   *bH_pt;
   vector<float>   *bH_eta;
   vector<float>   *bH_phi;
   vector<float>   *bH_Lxy;
   vector<float>   *bH_dRjet;
   vector<int>     *jet_btag_ntrk;
   vector<vector<float> > *jet_trk_pt;
   vector<vector<float> > *jet_trk_eta;
   vector<vector<float> > *jet_trk_theta;
   vector<vector<float> > *jet_trk_phi;
   vector<vector<float> > *jet_trk_chi2;
   vector<vector<float> > *jet_trk_ndf;
   vector<vector<int> > *jet_trk_algo;
   vector<vector<int> > *jet_trk_orig;
   vector<vector<int> > *jet_trk_nBLHits;
   vector<vector<int> > *jet_trk_nsharedBLHits;
   vector<vector<int> > *jet_trk_nsplitBLHits;
   vector<vector<int> > *jet_trk_nPixHits;
   vector<vector<int> > *jet_trk_nsharedPixHits;
   vector<vector<int> > *jet_trk_nsplitPixHits;
   vector<vector<int> > *jet_trk_nSCTHits;
   vector<vector<int> > *jet_trk_expectBLayerHit;
   vector<vector<float> > *jet_trk_d0;
   vector<vector<float> > *jet_trk_z0;
   vector<vector<float> > *jet_trk_d0_truth;
   vector<vector<float> > *jet_trk_z0_truth;
   vector<vector<int> > *jet_trk_ip3d_grade;
   vector<vector<float> > *jet_trk_ip3d_d0;
   vector<vector<float> > *jet_trk_ip3d_z0;
   vector<vector<float> > *jet_trk_ip3d_d0sig;
   vector<vector<float> > *jet_trk_ip3d_z0sig;
   vector<int>     *jet_sv1_ntrk;
   vector<int>     *jet_ip3d_ntrk;
   vector<int>     *jet_jf_ntrk;

   // List of branches
   TBranch        *b_runnb;   //!
   TBranch        *b_eventnb;   //!
   TBranch        *b_mcchan;   //!
   TBranch        *b_mcwg;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_avgmu;   //!
   TBranch        *b_PVx;   //!
   TBranch        *b_PVy;   //!
   TBranch        *b_PVz;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_nbjets;   //!
   TBranch        *b_nbjets_q;   //!
   TBranch        *b_nbjets_HadI;   //!
   TBranch        *b_nbjets_HadF;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_ForHybrid;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_pt_orig;   //!
   TBranch        *b_jet_eta_orig;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_m;   //!
   TBranch        *b_jet_truthflav;   //!
   TBranch        *b_jet_GhostL_q;   //!
   TBranch        *b_jet_GhostL_HadI;   //!
   TBranch        *b_jet_GhostL_HadF;   //!
   TBranch        *b_jet_aliveAfterOR;   //!
   TBranch        *b_jet_truthMatch;   //!
   TBranch        *b_jet_truthPt;   //!
   TBranch        *b_jet_dRiso;   //!
   TBranch        *b_jet_JVF;   //!
   TBranch        *b_jet_JVT;   //!
   TBranch        *b_jet_ip2d_pb;   //!
   TBranch        *b_jet_ip2d_pc;   //!
   TBranch        *b_jet_ip2d_pu;   //!
   TBranch        *b_jet_ip2d_llr;   //!
   TBranch        *b_jet_ip3d_pb;   //!
   TBranch        *b_jet_ip3d_pc;   //!
   TBranch        *b_jet_ip3d_pu;   //!
   TBranch        *b_jet_ip3d_llr;   //!
   TBranch        *b_jet_sv0_sig3d;   //!
   TBranch        *b_jet_sv0_ntrkj;   //!
   TBranch        *b_jet_sv0_ntrkv;   //!
   TBranch        *b_jet_sv0_n2t;   //!
   TBranch        *b_jet_sv0_m;   //!
   TBranch        *b_jet_sv0_efc;   //!
   TBranch        *b_jet_sv0_normdist;   //!
   TBranch        *b_jet_sv0_vtxx;   //!
   TBranch        *b_jet_sv0_vtxy;   //!
   TBranch        *b_jet_sv0_vtxz;   //!
   TBranch        *b_jet_sv1_ntrkj;   //!
   TBranch        *b_jet_sv1_ntrkv;   //!
   TBranch        *b_jet_sv1_n2t;   //!
   TBranch        *b_jet_sv1_m;   //!
   TBranch        *b_jet_sv1_efc;   //!
   TBranch        *b_jet_sv1_normdist;   //!
   TBranch        *b_jet_sv1_pb;   //!
   TBranch        *b_jet_sv1_pc;   //!
   TBranch        *b_jet_sv1_pu;   //!
   TBranch        *b_jet_sv1_llr;   //!
   TBranch        *b_jet_sv1_sig3d;   //!
   TBranch        *b_jet_sv1_dR;   //! // FLS
   TBranch        *b_jet_sv1_Lxy;   //! // FLS
   TBranch        *b_jet_sv1_L3d;   //! // FLS
   TBranch        *b_jet_sv1_vtxx;   //!
   TBranch        *b_jet_sv1_vtxy;   //!
   TBranch        *b_jet_sv1_vtxz;   //!
   TBranch        *b_jet_jf_pb;   //!
   TBranch        *b_jet_jf_pc;   //!
   TBranch        *b_jet_jf_pu;   //!
   TBranch        *b_jet_jf_llr;   //!
   TBranch        *b_jet_jf_m;   //!
   TBranch        *b_jet_jf_efc;   //!
   TBranch        *b_jet_jf_deta;   //!
   TBranch        *b_jet_jf_dphi;   //!
   TBranch        *b_jet_jf_ntrkAtVx;   //!
   TBranch        *b_jet_jf_nvtx;   //!
   TBranch        *b_jet_jf_sig3d;   //!
   TBranch        *b_jet_jf_nvtx1t;   //!
   TBranch        *b_jet_jf_n2t;   //!
   TBranch        *b_jet_jf_chi2;   //!
   TBranch        *b_jet_jf_ndf;   //!
   TBranch        *b_jet_jfcombnn_pb;   //!
   TBranch        *b_jet_jfcombnn_pc;   //!
   TBranch        *b_jet_jfcombnn_pu;   //!
   TBranch        *b_jet_jfcombnn_llr;   //!
   TBranch        *b_jet_sv1ip3d;   //!
   TBranch        *b_jet_mv1;   //!
   TBranch        *b_jet_mv1c;   //!
   TBranch        *b_jet_mv2c00;   //!
   TBranch        *b_jet_mv2c10;   //!
   TBranch        *b_jet_mv2c20;   //!
   TBranch        *b_jet_mv2c100;   //!
   TBranch        *b_jet_mv2m_pb;   //!
   TBranch        *b_jet_mv2m_pu;   //!
   TBranch        *b_jet_mv2m_pc;   //!
   TBranch        *b_jet_mvb;   //!
   TBranch        *b_bH_pt;   //!
   TBranch        *b_bH_eta;   //!
   TBranch        *b_bH_phi;   //!
   TBranch        *b_bH_Lxy;   //!
   TBranch        *b_bH_dRjet;   //!
   TBranch        *b_jet_btag_ntrk;   //!
   TBranch        *b_jet_trk_pt;   //!
   TBranch        *b_jet_trk_eta;   //!
   TBranch        *b_jet_trk_theta;   //!
   TBranch        *b_jet_trk_phi;   //!
   TBranch        *b_jet_trk_chi2;   //!
   TBranch        *b_jet_trk_ndf;   //!
   TBranch        *b_jet_trk_algo;   //!
   TBranch        *b_jet_trk_orig;   //!
   TBranch        *b_jet_trk_nBLHits;   //!
   TBranch        *b_jet_trk_nsharedBLHits;   //!
   TBranch        *b_jet_trk_nsplitBLHits;   //!
   TBranch        *b_jet_trk_nPixHits;   //!
   TBranch        *b_jet_trk_nsharedPixHits;   //!
   TBranch        *b_jet_trk_nsplitPixHits;   //!
   TBranch        *b_jet_trk_nSCTHits;   //!
   TBranch        *b_jet_trk_expectBLayerHit;   //!
   TBranch        *b_jet_trk_d0;   //!
   TBranch        *b_jet_trk_z0;   //!
   TBranch        *b_jet_trk_d0_truth;   //!
   TBranch        *b_jet_trk_z0_truth;   //!
   TBranch        *b_jet_trk_ip3d_grade;   //!
   TBranch        *b_jet_trk_ip3d_d0;   //!
   TBranch        *b_jet_trk_ip3d_z0;   //!
   TBranch        *b_jet_trk_ip3d_d0sig;   //!
   TBranch        *b_jet_trk_ip3d_z0sig;   //!
   TBranch        *b_jet_sv1_ntrk;   //!
   TBranch        *b_jet_ip3d_ntrk;   //!
   TBranch        *b_jet_jf_ntrk;   //!

   bTag(TTree *tree=0);
   virtual ~bTag();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef bTag_cxx
bTag::bTag(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("group.perf-flavtag.mc14_13TeV.110401.PowhegPythia_nonallhad.merge.AOD.e2928_s1982_s2008_r5787_r5853.BTAGNTUP_v00b_BTAGSTREAM.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("group.perf-flavtag.mc14_13TeV.110401.PowhegPythia_nonallhad.merge.AOD.e2928_s1982_s2008_r5787_r5853.BTAGNTUP_v00b_BTAGSTREAM.root");
      }
      f->GetObject("bTag",tree);

   }
   Init(tree);
}

bTag::~bTag()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t bTag::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t bTag::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void bTag::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jet_pt = 0;
   jet_ForHybrid = 0;
   jet_eta = 0;
   jet_pt_orig = 0; 
   jet_eta_orig = 0;
   jet_phi = 0;
   jet_E = 0;
   jet_m = 0;
   jet_truthflav = 0;
   jet_GhostL_q = 0;
   jet_GhostL_HadI = 0;
   jet_GhostL_HadF = 0;
   jet_aliveAfterOR = 0;
   jet_truthMatch = 0;
   jet_truthPt = 0;
   jet_dRiso = 0;
   jet_JVF = 0;
   jet_JVT = 0;
   jet_ip2d_pb = 0;
   jet_ip2d_pc = 0;
   jet_ip2d_pu = 0;
   jet_ip2d_llr = 0;
   jet_ip3d_pb = 0;
   jet_ip3d_pc = 0;
   jet_ip3d_pu = 0;
   jet_ip3d_llr = 0;
   jet_sv0_sig3d = 0;
   jet_sv0_ntrkj = 0;
   jet_sv0_ntrkv = 0;
   jet_sv0_n2t = 0;
   jet_sv0_m = 0;
   jet_sv0_efc = 0;
   jet_sv0_normdist = 0;
   jet_sv0_vtxx = 0;
   jet_sv0_vtxy = 0;
   jet_sv0_vtxz = 0;
   jet_sv1_ntrkj = 0;
   jet_sv1_ntrkv = 0;
   jet_sv1_n2t = 0;
   jet_sv1_m = 0;
   jet_sv1_efc = 0;
   jet_sv1_normdist = 0;
   jet_sv1_pb = 0;
   jet_sv1_pc = 0;
   jet_sv1_pu = 0;
   jet_sv1_llr = 0;
   jet_sv1_sig3d = 0;
   jet_sv1_dR = 0; // FLS
   jet_sv1_Lxy = 0; // FLS
   jet_sv1_L3d = 0; // FLS
   jet_sv1_vtxx = 0;
   jet_sv1_vtxy = 0;
   jet_sv1_vtxz = 0;
   jet_jf_pb = 0;
   jet_jf_pc = 0;
   jet_jf_pu = 0;
   jet_jf_llr = 0;
   jet_jf_m = 0;
   jet_jf_efc = 0;
   jet_jf_deta = 0;
   jet_jf_dphi = 0;
   jet_jf_ntrkAtVx = 0;
   jet_jf_nvtx = 0;
   jet_jf_sig3d = 0;
   jet_jf_nvtx1t = 0;
   jet_jf_n2t = 0;
   jet_jf_chi2 = 0;
   jet_jf_ndf = 0;
   jet_jfcombnn_pb = 0;
   jet_jfcombnn_pc = 0;
   jet_jfcombnn_pu = 0;
   jet_jfcombnn_llr = 0;
   jet_sv1ip3d = 0;
   jet_mv1 = 0;
   jet_mv1c = 0;
   jet_mv2c00 = 0;
   jet_mv2c10 = 0;
   jet_mv2c20 = 0;
   jet_mv2c100 = 0;
   jet_mv2m_pb = 0;
   jet_mv2m_pu = 0;
   jet_mv2m_pc = 0;
   jet_mvb = 0;
   bH_pt = 0;
   bH_eta = 0;
   bH_phi = 0;
   bH_Lxy = 0;
   bH_dRjet = 0;
   jet_btag_ntrk = 0;
   jet_trk_pt = 0;
   jet_trk_eta = 0;
   jet_trk_theta = 0;
   jet_trk_phi = 0;
   jet_trk_chi2 = 0;
   jet_trk_ndf = 0;
   jet_trk_algo = 0;
   jet_trk_orig = 0;
   jet_trk_nBLHits = 0;
   jet_trk_nsharedBLHits = 0;
   jet_trk_nsplitBLHits = 0;
   jet_trk_nPixHits = 0;
   jet_trk_nsharedPixHits = 0;
   jet_trk_nsplitPixHits = 0;
   jet_trk_nSCTHits = 0;
   jet_trk_expectBLayerHit = 0;
   jet_trk_d0 = 0;
   jet_trk_z0 = 0;
   jet_trk_d0_truth = 0;
   jet_trk_z0_truth = 0;
   jet_trk_ip3d_grade = 0;
   jet_trk_ip3d_d0 = 0;
   jet_trk_ip3d_z0 = 0;
   jet_trk_ip3d_d0sig = 0;
   jet_trk_ip3d_z0sig = 0;
   jet_sv1_ntrk = 0;
   jet_ip3d_ntrk = 0;
   jet_jf_ntrk = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runnb", &runnb, &b_runnb);
   fChain->SetBranchAddress("eventnb", &eventnb, &b_eventnb);
   fChain->SetBranchAddress("mcchan", &mcchan, &b_mcchan);
   fChain->SetBranchAddress("mcwg", &mcwg, &b_mcwg);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("avgmu", &avgmu, &b_avgmu);
   fChain->SetBranchAddress("PVx", &PVx, &b_PVx);
   fChain->SetBranchAddress("PVy", &PVy, &b_PVy);
   fChain->SetBranchAddress("PVz", &PVz, &b_PVz);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("nbjets", &nbjets, &b_nbjets);
   fChain->SetBranchAddress("nbjets_q", &nbjets_q, &b_nbjets_q);
   fChain->SetBranchAddress("nbjets_HadI", &nbjets_HadI, &b_nbjets_HadI);
   fChain->SetBranchAddress("nbjets_HadF", &nbjets_HadF, &b_nbjets_HadF);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_ForHybrid", &jet_ForHybrid, &b_jet_ForHybrid);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_pt_orig", &jet_pt_orig, &b_jet_pt_orig);   
   fChain->SetBranchAddress("jet_eta_orig", &jet_eta_orig, &b_jet_eta_orig);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_E", &jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_m", &jet_m, &b_jet_m);
   fChain->SetBranchAddress("jet_truthflav", &jet_truthflav, &b_jet_truthflav);
   fChain->SetBranchAddress("jet_GhostL_q", &jet_GhostL_q, &b_jet_GhostL_q);
   fChain->SetBranchAddress("jet_GhostL_HadI", &jet_GhostL_HadI, &b_jet_GhostL_HadI);
   fChain->SetBranchAddress("jet_GhostL_HadF", &jet_GhostL_HadF, &b_jet_GhostL_HadF);
   fChain->SetBranchAddress("jet_aliveAfterOR", &jet_aliveAfterOR, &b_jet_aliveAfterOR);
   fChain->SetBranchAddress("jet_truthMatch", &jet_truthMatch, &b_jet_truthMatch);
   fChain->SetBranchAddress("jet_truthPt", &jet_truthPt, &b_jet_truthPt);
   /* fChain->SetBranchAddress("jet_dRiso", &jet_dRiso, &b_jet_dRiso); */
   fChain->SetBranchAddress("jet_JVF", &jet_JVF, &b_jet_JVF);
   fChain->SetBranchAddress("jet_JVT", &jet_JVT, &b_jet_JVT);
   fChain->SetBranchAddress("jet_ip2d_pb", &jet_ip2d_pb, &b_jet_ip2d_pb);
   fChain->SetBranchAddress("jet_ip2d_pc", &jet_ip2d_pc, &b_jet_ip2d_pc);
   fChain->SetBranchAddress("jet_ip2d_pu", &jet_ip2d_pu, &b_jet_ip2d_pu);
   fChain->SetBranchAddress("jet_ip2d_llr", &jet_ip2d_llr, &b_jet_ip2d_llr);
   fChain->SetBranchAddress("jet_ip3d_pb", &jet_ip3d_pb, &b_jet_ip3d_pb);
   fChain->SetBranchAddress("jet_ip3d_pc", &jet_ip3d_pc, &b_jet_ip3d_pc);
   fChain->SetBranchAddress("jet_ip3d_pu", &jet_ip3d_pu, &b_jet_ip3d_pu);
   fChain->SetBranchAddress("jet_ip3d_llr", &jet_ip3d_llr, &b_jet_ip3d_llr);
   /* fChain->SetBranchAddress("jet_sv0_sig3d", &jet_sv0_sig3d, &b_jet_sv0_sig3d); */
   /* fChain->SetBranchAddress("jet_sv0_ntrkj", &jet_sv0_ntrkj, &b_jet_sv0_ntrkj); */
   /* fChain->SetBranchAddress("jet_sv0_ntrkv", &jet_sv0_ntrkv, &b_jet_sv0_ntrkv); */
   /* fChain->SetBranchAddress("jet_sv0_n2t", &jet_sv0_n2t, &b_jet_sv0_n2t); */
   /* fChain->SetBranchAddress("jet_sv0_m", &jet_sv0_m, &b_jet_sv0_m); */
   /* fChain->SetBranchAddress("jet_sv0_efc", &jet_sv0_efc, &b_jet_sv0_efc); */
   /* fChain->SetBranchAddress("jet_sv0_normdist", &jet_sv0_normdist, &b_jet_sv0_normdist); */
   /* fChain->SetBranchAddress("jet_sv0_vtx_x", &jet_sv0_vtxx, &b_jet_sv0_vtxx); */
   /* fChain->SetBranchAddress("jet_sv0_vtx_y", &jet_sv0_vtxy, &b_jet_sv0_vtxy); */
   /* fChain->SetBranchAddress("jet_sv0_vtx_z", &jet_sv0_vtxz, &b_jet_sv0_vtxz); */
   fChain->SetBranchAddress("jet_sv1_ntrkj", &jet_sv1_ntrkj, &b_jet_sv1_ntrkj);
   fChain->SetBranchAddress("jet_sv1_ntrkv", &jet_sv1_ntrkv, &b_jet_sv1_ntrkv);
   fChain->SetBranchAddress("jet_sv1_n2t", &jet_sv1_n2t, &b_jet_sv1_n2t);
   fChain->SetBranchAddress("jet_sv1_m", &jet_sv1_m, &b_jet_sv1_m);
   fChain->SetBranchAddress("jet_sv1_efc", &jet_sv1_efc, &b_jet_sv1_efc);
   fChain->SetBranchAddress("jet_sv1_normdist", &jet_sv1_normdist, &b_jet_sv1_normdist);
   fChain->SetBranchAddress("jet_sv1_pb", &jet_sv1_pb, &b_jet_sv1_pb);
   fChain->SetBranchAddress("jet_sv1_pc", &jet_sv1_pc, &b_jet_sv1_pc);
   fChain->SetBranchAddress("jet_sv1_pu", &jet_sv1_pu, &b_jet_sv1_pu);
   fChain->SetBranchAddress("jet_sv1_llr", &jet_sv1_llr, &b_jet_sv1_llr);
   fChain->SetBranchAddress("jet_sv1_sig3d", &jet_sv1_sig3d, &b_jet_sv1_sig3d);
   fChain->SetBranchAddress("jet_sv1_dR", &jet_sv1_dR, &b_jet_sv1_dR); // FLS
   fChain->SetBranchAddress("jet_sv1_Lxy", &jet_sv1_Lxy, &b_jet_sv1_Lxy); // FLS
   fChain->SetBranchAddress("jet_sv1_L3d", &jet_sv1_L3d, &b_jet_sv1_L3d); // FLS
   fChain->SetBranchAddress("jet_sv1_vtx_x", &jet_sv1_vtxx, &b_jet_sv1_vtxx);
   fChain->SetBranchAddress("jet_sv1_vtx_y", &jet_sv1_vtxy, &b_jet_sv1_vtxy);
   fChain->SetBranchAddress("jet_sv1_vtx_z", &jet_sv1_vtxz, &b_jet_sv1_vtxz);
   /* fChain->SetBranchAddress("jet_jf_pb", &jet_jf_pb, &b_jet_jf_pb); */
   /* fChain->SetBranchAddress("jet_jf_pc", &jet_jf_pc, &b_jet_jf_pc); */
   /* fChain->SetBranchAddress("jet_jf_pu", &jet_jf_pu, &b_jet_jf_pu); */
   /* fChain->SetBranchAddress("jet_jf_llr", &jet_jf_llr, &b_jet_jf_llr); */
   fChain->SetBranchAddress("jet_jf_m", &jet_jf_m, &b_jet_jf_m);
   fChain->SetBranchAddress("jet_jf_efc", &jet_jf_efc, &b_jet_jf_efc);
   fChain->SetBranchAddress("jet_jf_deta", &jet_jf_deta, &b_jet_jf_deta);
   fChain->SetBranchAddress("jet_jf_dphi", &jet_jf_dphi, &b_jet_jf_dphi);
   fChain->SetBranchAddress("jet_jf_ntrkAtVx", &jet_jf_ntrkAtVx, &b_jet_jf_ntrkAtVx);
   fChain->SetBranchAddress("jet_jf_nvtx", &jet_jf_nvtx, &b_jet_jf_nvtx);
   fChain->SetBranchAddress("jet_jf_sig3d", &jet_jf_sig3d, &b_jet_jf_sig3d);
   fChain->SetBranchAddress("jet_jf_nvtx1t", &jet_jf_nvtx1t, &b_jet_jf_nvtx1t);
   fChain->SetBranchAddress("jet_jf_n2t", &jet_jf_n2t, &b_jet_jf_n2t);
   /* fChain->SetBranchAddress("jet_jf_chi2", &jet_jf_chi2, &b_jet_jf_chi2); */
   /* fChain->SetBranchAddress("jet_jf_ndf", &jet_jf_ndf, &b_jet_jf_ndf); */
   /* fChain->SetBranchAddress("jet_jfcombnn_pb", &jet_jfcombnn_pb, &b_jet_jfcombnn_pb); */
   /* fChain->SetBranchAddress("jet_jfcombnn_pc", &jet_jfcombnn_pc, &b_jet_jfcombnn_pc); */
   /* fChain->SetBranchAddress("jet_jfcombnn_pu", &jet_jfcombnn_pu, &b_jet_jfcombnn_pu); */
   /* fChain->SetBranchAddress("jet_jfcombnn_llr", &jet_jfcombnn_llr, &b_jet_jfcombnn_llr); */
   /* fChain->SetBranchAddress("jet_sv1ip3d", &jet_sv1ip3d, &b_jet_sv1ip3d); */
   /* fChain->SetBranchAddress("jet_mv1", &jet_mv1, &b_jet_mv1); */
   /* fChain->SetBranchAddress("jet_mv1c", &jet_mv1c, &b_jet_mv1c); */
   fChain->SetBranchAddress("jet_mv2c00", &jet_mv2c00, &b_jet_mv2c00);
   fChain->SetBranchAddress("jet_mv2c10", &jet_mv2c10, &b_jet_mv2c10);
   fChain->SetBranchAddress("jet_mv2c20", &jet_mv2c20, &b_jet_mv2c20);
   fChain->SetBranchAddress("jet_mv2c100", &jet_mv2c100, &b_jet_mv2c100);
   fChain->SetBranchAddress("jet_mv2m_pb", &jet_mv2m_pb, &b_jet_mv2m_pb);
   fChain->SetBranchAddress("jet_mv2m_pu", &jet_mv2m_pu, &b_jet_mv2m_pu);
   fChain->SetBranchAddress("jet_mv2m_pc", &jet_mv2m_pc, &b_jet_mv2m_pc);
   /* fChain->SetBranchAddress("jet_mvb", &jet_mvb, &b_jet_mvb); */
   /* fChain->SetBranchAddress("bH_pt", &bH_pt, &b_bH_pt); */
   /* fChain->SetBranchAddress("bH_eta", &bH_eta, &b_bH_eta); */
   /* fChain->SetBranchAddress("bH_phi", &bH_phi, &b_bH_phi); */
   /* fChain->SetBranchAddress("bH_Lxy", &bH_Lxy, &b_bH_Lxy); */
   /* fChain->SetBranchAddress("bH_dRjet", &bH_dRjet, &b_bH_dRjet); */
   /* fChain->SetBranchAddress("jet_btag_ntrk", &jet_btag_ntrk, &b_jet_btag_ntrk); */
   /* fChain->SetBranchAddress("jet_trk_pt", &jet_trk_pt, &b_jet_trk_pt); */
   /* fChain->SetBranchAddress("jet_trk_eta", &jet_trk_eta, &b_jet_trk_eta); */
   /* fChain->SetBranchAddress("jet_trk_theta", &jet_trk_theta, &b_jet_trk_theta); */
   /* fChain->SetBranchAddress("jet_trk_phi", &jet_trk_phi, &b_jet_trk_phi); */
   /* fChain->SetBranchAddress("jet_trk_chi2", &jet_trk_chi2, &b_jet_trk_chi2); */
   /* fChain->SetBranchAddress("jet_trk_ndf", &jet_trk_ndf, &b_jet_trk_ndf); */
   /* fChain->SetBranchAddress("jet_trk_algo", &jet_trk_algo, &b_jet_trk_algo); */
   /* fChain->SetBranchAddress("jet_trk_orig", &jet_trk_orig, &b_jet_trk_orig); */
   /* fChain->SetBranchAddress("jet_trk_nBLHits", &jet_trk_nBLHits, &b_jet_trk_nBLHits); */
   /* fChain->SetBranchAddress("jet_trk_nsharedBLHits", &jet_trk_nsharedBLHits, &b_jet_trk_nsharedBLHits); */
   /* fChain->SetBranchAddress("jet_trk_nsplitBLHits", &jet_trk_nsplitBLHits, &b_jet_trk_nsplitBLHits); */
   /* fChain->SetBranchAddress("jet_trk_nPixHits", &jet_trk_nPixHits, &b_jet_trk_nPixHits); */
   /* fChain->SetBranchAddress("jet_trk_nsharedPixHits", &jet_trk_nsharedPixHits, &b_jet_trk_nsharedPixHits); */
   /* fChain->SetBranchAddress("jet_trk_nsplitPixHits", &jet_trk_nsplitPixHits, &b_jet_trk_nsplitPixHits); */
   /* fChain->SetBranchAddress("jet_trk_nSCTHits", &jet_trk_nSCTHits, &b_jet_trk_nSCTHits); */
   /* fChain->SetBranchAddress("jet_trk_expectBLayerHit", &jet_trk_expectBLayerHit, &b_jet_trk_expectBLayerHit); */
   /* fChain->SetBranchAddress("jet_trk_d0", &jet_trk_d0, &b_jet_trk_d0); */
   /* fChain->SetBranchAddress("jet_trk_z0", &jet_trk_z0, &b_jet_trk_z0); */
   /* fChain->SetBranchAddress("jet_trk_d0_truth", &jet_trk_d0_truth, &b_jet_trk_d0_truth); */
   /* fChain->SetBranchAddress("jet_trk_z0_truth", &jet_trk_z0_truth, &b_jet_trk_z0_truth); */
   /* fChain->SetBranchAddress("jet_trk_ip3d_grade", &jet_trk_ip3d_grade, &b_jet_trk_ip3d_grade); */
   /* fChain->SetBranchAddress("jet_trk_ip3d_d0", &jet_trk_ip3d_d0, &b_jet_trk_ip3d_d0); */
   /* fChain->SetBranchAddress("jet_trk_ip3d_z0", &jet_trk_ip3d_z0, &b_jet_trk_ip3d_z0); */
   /* fChain->SetBranchAddress("jet_trk_ip3d_d0sig", &jet_trk_ip3d_d0sig, &b_jet_trk_ip3d_d0sig); */
   /* fChain->SetBranchAddress("jet_trk_ip3d_z0sig", &jet_trk_ip3d_z0sig, &b_jet_trk_ip3d_z0sig); */
   /* fChain->SetBranchAddress("jet_sv1_ntrk", &jet_sv1_ntrk, &b_jet_sv1_ntrk); */
   /* fChain->SetBranchAddress("jet_ip3d_ntrk", &jet_ip3d_ntrk, &b_jet_ip3d_ntrk); */
   /* fChain->SetBranchAddress("jet_jf_ntrk", &jet_jf_ntrk, &b_jet_jf_ntrk); */
   Notify();
}

Bool_t bTag::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void bTag::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t bTag::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef bTag_cxx
