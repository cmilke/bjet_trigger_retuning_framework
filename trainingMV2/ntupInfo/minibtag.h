//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov  6 21:13:49 2014 by ROOT version 5.34/19
// from TTree minibtag/minibtag
// found on file: mars.5.100k.root
//////////////////////////////////////////////////////////

#ifndef minibtag_h
#define minibtag_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>

#include <iostream>
using std::cout;
using std::endl;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class minibtag {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           mcchannel;
   Int_t           evt;
   Double_t        evtweight;
   Int_t           npv;
   Int_t           muAct;
   Int_t           muAvg;
   Int_t           pv0_isOK;
   Double_t        pv0_x;
   Double_t        pv0_y;
   Double_t        pv0_z;
   Int_t           nbjet;
   Int_t           nbjetok;
   Double_t        htjet;
   Double_t        triggerBitsEvt;
   Double_t        plateauBitsEvt;
   Double_t        triggerBitsJet;
   Double_t        plateauBitsJet;
   Int_t           jetidx;

   Int_t           GhostL_q;
   Int_t           GhostL_HadI;
   Int_t           GhostL_HadF;
   Int_t           aliveAfterOR;
   Int_t           truthMatch;
   Float_t         truthPt;
   Float_t         dRiso;
   Float_t         JVF;
   Float_t         JVT;

   Int_t           rank;
   Int_t           originIndex;
   Float_t         caloWidth;
   Float_t         trkWidth;
   Double_t        pt_calib;
   Double_t        eta_calib;
   Double_t        phi_calib;
   Double_t        m_calib;

   Double_t        pt_uCalib;
   Double_t        eta_uCalib;
   Double_t        phi_uCalib;
   Double_t        m_uCalib;

   Double_t        pt;
   Double_t        eta;
   Double_t        phi;
   Double_t        m;
   Double_t        e;
   Double_t        jvf;
   Double_t        drminj;
   Double_t        dphiminj;
   Int_t           isGood;
   Int_t           label;
   Int_t           nlabel;
   Int_t           nlept;
   Double_t        drb;
   Double_t        drc;
   Double_t        drt;
   Double_t        jtp;
   Double_t        sv0;
   Double_t        ip2;
   Double_t        ip3;
   Double_t        sv1;
   Double_t        sv2;
   Double_t        cmb;
   Double_t        jft;
   Double_t        jfc;
   Double_t        smt;
   Double_t        mv1;
   Float_t         mv1c;
   Float_t         mv2c00;
   Float_t         mv2c10;
   Float_t         mv2c20;
   Float_t         mv2c100;
   Float_t         mv2m_pb;
   Float_t         mv2m_pu;
   Float_t         mv2m_pc;
   Float_t         mvb;
   Float_t         gaia_pu;
   Float_t         gaia_pb;
   Float_t         gaia_pc;
   Int_t           ntk_ass;
   Int_t           ntk_ipp;
   Int_t           sv1ntkv;
   Double_t        sv1mass;
   Int_t           sv1n2tv;
   Double_t        sv1efrc;
   Double_t        sv1efrc2;
   Double_t        sv1dR;
   Double_t        sv1norm;
   Double_t        sv1sig3;
   Double_t        sv1_vx_x;
   Double_t        sv1_vx_y;
   Double_t        sv1_vx_z;
   Double_t        sv1_vx_dx;
   Double_t        sv1_vx_dy;
   Double_t        sv1_vx_dz;
   Int_t           dkvtx_n;
   Double_t        dkvtx_x[1];   //[dkvtx_n]
   Double_t        dkvtx_y[1];   //[dkvtx_n]
   Double_t        dkvtx_z[1];   //[dkvtx_n]
   Int_t           dkvtx_pdg[1];   //[dkvtx_n]
   Double_t        smtc2;
   Double_t        gbbnn;
   Double_t        tc2d;
   Double_t        jfc_pu;
   Double_t        jfc_pb;
   Double_t        jfc_pc;
   Double_t        jf_mass;
   Double_t        jf_efrc;
   Double_t        jf_efrc2;
   Double_t        jf_sig3;
   Double_t        jf_dphi;
   Double_t        jf_deta;
   Int_t           jf_nvtx;
   Int_t           jf_nvtx1t;
   Int_t           jf_ntrkv;
   Int_t           jf_n2tv;
   Double_t        jfCharm_deltaeta;
   Double_t        jfCharm_deltaphi;
   Double_t        jfCharm_energyFraction;
   Double_t        jfCharm_mass;
   Double_t        jfCharm_maxSecondaryVertexRho;
   Double_t        jfCharm_maxSecondaryVertexZ;
   Double_t        jfCharm_maxTrackPtRel;
   Double_t        jfCharm_maxTrackRapidity;
   Double_t        jfCharm_meanTrackPtRel;
   Double_t        jfCharm_meanTrackRapidity;
   Double_t        jfCharm_minTrackPtRel;
   Double_t        jfCharm_minTrackRapidity;
   Double_t        jfCharm_significance3d;
   Double_t        jfCharm_subMaxSecondaryVertexRho;
   Double_t        jfCharm_subMaxSecondaryVertexZ;
   Int_t           jfCharm_nSingleTracks;
   Int_t           jfCharm_nTracks;
   Int_t           jfCharm_nTracksAtVtx;
   Int_t           jfCharm_nVTX;
   Int_t           nmuon_ass;
   Int_t           nmuon2_ass;
   Float_t         ip2_pu;
   Float_t         ip2_pb;
   Float_t         ip2_pc;
   Int_t           ip2_isvalid;
   Int_t           ip2_ntk;
   Float_t         ip3_pu;
   Float_t         ip3_pc;
   Float_t         ip3_pb;
   Int_t           ip3_isvalid;
   Int_t           ip3_ntk;
   Int_t           ip3_nDisplacedTrk;
   Int_t           jetprob_ntk;
   Float_t         sv1_pu;
   Float_t         sv1_pc;
   Float_t         sv1_pb;
   Int_t           sv1_isvalid;
   Int_t           sv1_ntk;
   Float_t         sv2_pu;
   Float_t         sv2_pb;
   Int_t           sv2_isvalid;
   Float_t         jf_pu;
   Float_t         jf_pb;
   Float_t         jf_pc;
   Int_t           jf_isvalid;
   Int_t           jf_ntk;
   Int_t           jfc_isvalid;
   Int_t           svp_isvalid;
   Int_t           svp_ntkj;
   Float_t         svp_x;
   Float_t         svp_y;
   Float_t         svp_z;
   Float_t         svp_errx;
   Float_t         svp_erry;
   Float_t         svp_errz;
   Float_t         svp_covxy;
   Float_t         svp_covxz;
   Float_t         svp_covyz;
   Float_t         svp_chi2;
   Int_t           svp_ndof;
   Int_t           svp_tkn;
   Int_t           sv0_isvalid;
   Double_t        sv0mass;
   Int_t           sv0_ntkv;
   Int_t           sv0_ntkj;
   Int_t           sv0_n2t;
   Float_t         sv0_efrc;
   Float_t         sv0_x;
   Float_t         sv0_y;
   Float_t         sv0_z;
   Float_t         sv0_errx;
   Float_t         sv0_erry;
   Float_t         sv0_errz;
   Float_t         sv0_cov_xy;
   Float_t         sv0_cov_xz;
   Float_t         sv0_cov_yz;
   Float_t         sv0_chi2;
   Int_t           sv0_ndof;
   Int_t           sv0_ntk;
   Int_t           smuon_n;
   Int_t           smuon2_n;
   Int_t           smuon2chi2_info;
   Int_t           msvp_isvalid;
   Int_t           msvp_ntkv;
   Int_t           msvp_ntkj;
   Int_t           msvp_n2t;
   Int_t           msvp_nvtx;
   Float_t         msvp_normwdist;
   Int_t           msvp_msvinjet_n;
   Int_t           vkalbadtk_n;
   Int_t           jfvx_n;

   Float_t         ip2_c;
   Float_t         ip3_c;
   Float_t         sv1_c;
   Float_t         jfc_c;
   Float_t         ip2_cu;
   Float_t         ip3_cu;
   Float_t         sv1_cu;
   Float_t         jfc_cu;
   Float_t         jf_dR;
   Float_t         jfCharm_dR;

   Double_t        sv1Lxy;
   Double_t        sv1L3d;
   Double_t        sv1Lxy_wrtPV;
   Double_t        sv1L3d_wrtPV;


   Float_t width;
   Int_t n_trk_sigd0cut;
   Float_t trk3_d0sig;
   Float_t trk3_z0sig;
   Float_t sv_scaled_efc;
   Float_t jf_scaled_efc;


   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_mcchannel;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_evtweight;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_muAct;   //!
   TBranch        *b_muAvg;   //!
   TBranch        *b_pv0_isOK;   //!
   TBranch        *b_pv0_x;   //!
   TBranch        *b_pv0_y;   //!
   TBranch        *b_pv0_z;   //!
   TBranch        *b_nbjet;   //!
   TBranch        *b_nbjetok;   //!
   TBranch        *b_htjet;   //!
   TBranch        *b_triggerBitsEvt;   //!
   TBranch        *b_plateauBitsEvt;   //!
   TBranch        *b_triggerBitsJet;   //!
   TBranch        *b_plateauBitsJet;   //!
   TBranch        *b_jetidx;   //!

   TBranch        *b_GhostL_q;   //!
   TBranch        *b_GhostL_HadI;   //!
   TBranch        *b_GhostL_HadF;   //!
   TBranch        *b_aliveAfterOR;   //!
   TBranch        *b_truthMatch;   //!
   TBranch        *b_truthPt;   //!
   TBranch        *b_dRiso;   //!
   TBranch        *b_JVF;   //!
   TBranch        *b_JVT;   //!

   TBranch        *b_rank;   //!
   TBranch        *b_originIndex;   //!
   TBranch        *b_caloWidth;   //!
   TBranch        *b_trkWidth;   //!

   TBranch        *b_pt_calib;   //!
   TBranch        *b_eta_calib;   //!
   TBranch        *b_phi_calib;   //!
   TBranch        *b_m_calib;   //!

   TBranch        *b_pt_uCalib;   //!
   TBranch        *b_eta_uCalib;   //!
   TBranch        *b_phi_uCalib;   //!
   TBranch        *b_m_uCalib;   //!

   TBranch        *b_pt;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_m;   //!
   TBranch        *b_e;   //!
   TBranch        *b_jvf;   //!
   TBranch        *b_drminj;   //!
   TBranch        *b_dphiminj;   //!
   TBranch        *b_isGood;   //!
   TBranch        *b_label;   //!
   TBranch        *b_nlabel;   //!
   TBranch        *b_nlept;   //!
   TBranch        *b_drb;   //!
   TBranch        *b_drc;   //!
   TBranch        *b_drt;   //!
   TBranch        *b_jtp;   //!
   TBranch        *b_sv0;   //!
   TBranch        *b_ip2;   //!
   TBranch        *b_ip3;   //!
   TBranch        *b_sv1;   //!
   TBranch        *b_sv2;   //!
   TBranch        *b_cmb;   //!
   TBranch        *b_jft;   //!
   TBranch        *b_jfc;   //!
   TBranch        *b_smt;   //!
   TBranch        *b_mv1;   //!
   TBranch        *b_mv1c;   //!
   TBranch        *b_mv2c00;   //!
   TBranch        *b_mv2c10;   //!
   TBranch        *b_mv2c20;   //!
   TBranch        *b_mv2c100;   //!
   TBranch        *b_mv2m_pb;   //!
   TBranch        *b_mv2m_pu;   //!
   TBranch        *b_mv2m_pc;   //!
   TBranch        *b_mvb;   //!
   TBranch        *b_gaia_pu;   //!
   TBranch        *b_gaia_pb;   //!
   TBranch        *b_gaia_pc;   //!
   TBranch        *b_ntk_ass;   //!
   TBranch        *b_ntk_ipp;   //!
   TBranch        *b_sv1ntkv;   //!
   TBranch        *b_sv1mass;   //!
   TBranch        *b_sv1n2tv;   //!
   TBranch        *b_sv1efrc;   //!
   TBranch        *b_sv1efrc2;   //!
   TBranch        *b_sv1dR;   //!
   TBranch        *b_sv1norm;   //!
   TBranch        *b_sv1Lxy;   //!
   TBranch        *b_sv1L3d;   //!
   TBranch        *b_sv1sig3;   //!
   TBranch        *b_sv1_vx_x;   //!
   TBranch        *b_sv1_vx_y;   //!
   TBranch        *b_sv1_vx_z;   //!
   TBranch        *b_sv1Lxy_wrtPV;   //!
   TBranch        *b_sv1L3d_wrtPV;   //!
   TBranch        *b_sv1_vx_dx;   //!
   TBranch        *b_sv1_vx_dy;   //!
   TBranch        *b_sv1_vx_dz;   //!
   TBranch        *b_dkvtx_n;   //!
   TBranch        *b_dkvtx_x;   //!
   TBranch        *b_dkvtx_y;   //!
   TBranch        *b_dkvtx_z;   //!
   TBranch        *b_dkvtx_pdg;   //!
   TBranch        *b_smtc2;   //!
   TBranch        *b_gbbnn;   //!
   TBranch        *b_tc2d;   //!
   TBranch        *b_jfc_pu;   //!
   TBranch        *b_jfc_pb;   //!
   TBranch        *b_jfc_pc;   //!
   TBranch        *b_jf_mass;   //!
   TBranch        *b_jf_efrc;   //!
   TBranch        *b_jf_efrc2;   //!
   TBranch        *b_jf_sig3;   //!
   TBranch        *b_jf_dphi;   //!
   TBranch        *b_jf_deta;   //!
   TBranch        *b_jf_nvtx;   //!
   TBranch        *b_jf_nvtx1t;   //!
   TBranch        *b_jf_ntrkv;   //!
   TBranch        *b_jf_n2tv;   //!
   TBranch        *b_jfCharm_deltaeta;   //!
   TBranch        *b_jfCharm_deltaphi;   //!
   TBranch        *b_jfCharm_energyFraction;   //!
   TBranch        *b_jfCharm_mass;   //!
   TBranch        *b_jfCharm_maxSecondaryVertexRho;   //!
   TBranch        *b_jfCharm_maxSecondaryVertexZ;   //!
   TBranch        *b_jfCharm_maxTrackPtRel;   //!
   TBranch        *b_jfCharm_maxTrackRapidity;   //!
   TBranch        *b_jfCharm_meanTrackPtRel;   //!
   TBranch        *b_jfCharm_meanTrackRapidity;   //!
   TBranch        *b_jfCharm_minTrackPtRel;   //!
   TBranch        *b_jfCharm_minTrackRapidity;   //!
   TBranch        *b_jfCharm_significance3d;   //!
   TBranch        *b_jfCharm_subMaxSecondaryVertexRho;   //!
   TBranch        *b_jfCharm_subMaxSecondaryVertexZ;   //!
   TBranch        *b_jfCharm_nSingleTracks;   //!
   TBranch        *b_jfCharm_nTracks;   //!
   TBranch        *b_jfCharm_nTracksAtVtx;   //!
   TBranch        *b_jfCharm_nVTX;   //!
   TBranch        *b_nmuon_ass;   //!
   TBranch        *b_nmuon2_ass;   //!
   TBranch        *b_ip2_pu;   //!
   TBranch        *b_ip2_pb;   //!
   TBranch        *b_ip2_pc;   //!
   TBranch        *b_ip2_isvalid;   //!
   TBranch        *b_ip2_ntk;   //!
   TBranch        *b_ip3_pu;   //!
   TBranch        *b_ip3_pc;   //!
   TBranch        *b_ip3_pb;   //!
   TBranch        *b_ip3_isvalid;   //!
   TBranch        *b_ip3_ntk;   //!
   TBranch        *b_ip3_nDisplacedTrk;   //!
   TBranch        *b_jetprob_ntk;   //!
   TBranch        *b_sv1_pu;   //!
   TBranch        *b_sv1_pc;   //!
   TBranch        *b_sv1_pb;   //!
   TBranch        *b_sv1_isvalid;   //!
   TBranch        *b_sv1_ntk;   //!
   TBranch        *b_sv2_pu;   //!
   TBranch        *b_sv2_pb;   //!
   TBranch        *b_sv2_isvalid;   //!
   TBranch        *b_jf_pu;   //!
   TBranch        *b_jf_pb;   //!
   TBranch        *b_jf_pc;   //!
   TBranch        *b_jf_isvalid;   //!
   TBranch        *b_jf_ntk;   //!
   TBranch        *b_jfc_isvalid;   //!
   TBranch        *b_svp_isvalid;   //!
   TBranch        *b_svp_ntkj;   //!
   TBranch        *b_svp_x;   //!
   TBranch        *b_svp_y;   //!
   TBranch        *b_svp_z;   //!
   TBranch        *b_svp_errx;   //!
   TBranch        *b_svp_erry;   //!
   TBranch        *b_svp_errz;   //!
   TBranch        *b_svp_covxy;   //!
   TBranch        *b_svp_covxz;   //!
   TBranch        *b_svp_covyz;   //!
   TBranch        *b_svp_chi2;   //!
   TBranch        *b_svp_ndof;   //!
   TBranch        *b_svp_tkn;   //!
   TBranch        *b_sv0_isvalid;   //!
   TBranch        *b_sv0mass;   //!
   TBranch        *b_sv0_ntkv;   //!
   TBranch        *b_sv0_ntkj;   //!
   TBranch        *b_sv0_n2t;   //!
   TBranch        *b_sv0_efrc;   //!
   TBranch        *b_sv0_x;   //!
   TBranch        *b_sv0_y;   //!
   TBranch        *b_sv0_z;   //!
   TBranch        *b_sv0_errx;   //!
   TBranch        *b_sv0_erry;   //!
   TBranch        *b_sv0_errz;   //!
   TBranch        *b_sv0_cov_xy;   //!
   TBranch        *b_sv0_cov_xz;   //!
   TBranch        *b_sv0_cov_yz;   //!
   TBranch        *b_sv0_chi2;   //!
   TBranch        *b_sv0_ndof;   //!
   TBranch        *b_sv0_ntk;   //!
   TBranch        *b_smuon_n;   //!
   TBranch        *b_smuon2_n;   //!
   TBranch        *b_smuon2chi2_info;   //!
   TBranch        *b_msvp_isvalid;   //!
   TBranch        *b_msvp_ntkv;   //!
   TBranch        *b_msvp_ntkj;   //!
   TBranch        *b_msvp_n2t;   //!
   TBranch        *b_msvp_nvtx;   //!
   TBranch        *b_msvp_normwdist;   //!
   TBranch        *b_msvp_msvinjet_n;   //!
   TBranch        *b_vkalbadtk_n;   //!
   TBranch        *b_jfvx_n;   //!
   TBranch        *b_ip2_c;   //!
   TBranch        *b_ip3_c;   //!
   TBranch        *b_sv1_c;   //!
   TBranch        *b_jfc_c;   //!
   TBranch        *b_ip2_cu;   //!
   TBranch        *b_ip3_cu;   //!
   TBranch        *b_sv1_cu;   //!
   TBranch        *b_jfc_cu;   //!
   TBranch        *b_jf_dR;   //!
   TBranch        *b_jfCharm_dR;   //!

   minibtag(TString name="", TTree *tree=0);
   virtual ~minibtag();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     initializeVariables();
   virtual Float_t  log(double a, double b);
};

#endif

#ifdef minibtag_cxx

minibtag::minibtag( TString name, TTree *tree) : fChain(0)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    if (name=="") tree = new TTree("minibtag","");
    else          tree = new TTree(name,"");
  }
  Init(tree);
}

minibtag::~minibtag()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t minibtag::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t minibtag::LoadTree(Long64_t entry)
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

const bool performanceOnly=false;
void minibtag::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   //   cout<<"kmdebug: initialization of tree"<<endl;

   /* fChain->SetBranchAddress("run", &run, &b_run); */
   /* fChain->SetBranchAddress("mcchannel", &mcchannel, &b_mcchannel); */
   /* fChain->SetBranchAddress("evt", &evt, &b_evt); */
   /* fChain->SetBranchAddress("evtweight", &evtweight, &b_evtweight); */
   /* fChain->SetBranchAddress("npv", &npv, &b_npv); */
   /* fChain->SetBranchAddress("muAct", &muAct, &b_muAct); */
   /* fChain->SetBranchAddress("muAvg", &muAvg, &b_muAvg); */
   /* fChain->SetBranchAddress("pv0_isOK", &pv0_isOK, &b_pv0_isOK); */
   /* fChain->SetBranchAddress("pv0_x", &pv0_x, &b_pv0_x); */
   /* fChain->SetBranchAddress("pv0_y", &pv0_y, &b_pv0_y); */
   /* fChain->SetBranchAddress("pv0_z", &pv0_z, &b_pv0_z); */
   /* fChain->SetBranchAddress("nbjet", &nbjet, &b_nbjet); */
   /* fChain->SetBranchAddress("nbjetok", &nbjetok, &b_nbjetok); */
   /* fChain->SetBranchAddress("htjet", &htjet, &b_htjet); */
   /* fChain->SetBranchAddress("triggerBitsEvt", &triggerBitsEvt, &b_triggerBitsEvt); */
   /* fChain->SetBranchAddress("plateauBitsEvt", &plateauBitsEvt, &b_plateauBitsEvt); */
   /* fChain->SetBranchAddress("triggerBitsJet", &triggerBitsJet, &b_triggerBitsJet); */
   /* fChain->SetBranchAddress("plateauBitsJet", &plateauBitsJet, &b_plateauBitsJet); */
   /* fChain->SetBranchAddress("jetidx", &jetidx, &b_jetidx); */
   /* fChain->SetBranchAddress("rank", &rank, &b_rank); */
   /* fChain->SetBranchAddress("originIndex", &originIndex, &b_originIndex); */
   /* fChain->SetBranchAddress("caloWidth", &caloWidth, &b_caloWidth); */
   /* fChain->SetBranchAddress("trkWidth", &trkWidth, &b_trkWidth); */
   /* fChain->SetBranchAddress("pt", &pt, &b_pt); */
   /* fChain->SetBranchAddress("eta", &eta, &b_eta); */
   /* fChain->SetBranchAddress("phi", &phi, &b_phi); */
   /* fChain->SetBranchAddress("m", &m, &b_m); */
   /* fChain->SetBranchAddress("e", &e, &b_e); */
   /* fChain->SetBranchAddress("jvf", &jvf, &b_jvf); */
   /* fChain->SetBranchAddress("drminj", &drminj, &b_drminj); */
   /* fChain->SetBranchAddress("dphiminj", &dphiminj, &b_dphiminj); */
   /* fChain->SetBranchAddress("label", &label, &b_label); */
   /* fChain->SetBranchAddress("nlabel", &nlabel, &b_nlabel); */
   /* fChain->SetBranchAddress("nlept", &nlept, &b_nlept); */
   /* fChain->SetBranchAddress("drb", &drb, &b_drb); */
   /* fChain->SetBranchAddress("drc", &drc, &b_drc); */
   /* fChain->SetBranchAddress("drt", &drt, &b_drt); */
   /* fChain->SetBranchAddress("jtp", &jtp, &b_jtp); */
   /* fChain->SetBranchAddress("sv0", &sv0, &b_sv0); */
   /* fChain->SetBranchAddress("ip2", &ip2, &b_ip2); */
   /* fChain->SetBranchAddress("ip3", &ip3, &b_ip3); */
   /* fChain->SetBranchAddress("sv1", &sv1, &b_sv1); */
   /* fChain->SetBranchAddress("sv2", &sv2, &b_sv2); */
   /* fChain->SetBranchAddress("cmb", &cmb, &b_cmb); */
   /* fChain->SetBranchAddress("jft", &jft, &b_jft); */
   /* fChain->SetBranchAddress("jfc", &jfc, &b_jfc); */
   /* fChain->SetBranchAddress("smt", &smt, &b_smt); */
   /* fChain->SetBranchAddress("mv1", &mv1, &b_mv1); */
   /* fChain->SetBranchAddress("mv1c", &mv1c, &b_mv1c); */
   /* fChain->SetBranchAddress("mv2c00", &mv2c00, &b_mv2c00); */
   /* fChain->SetBranchAddress("mv2c10", &mv2c10, &b_mv2c10); */
   /* fChain->SetBranchAddress("mv2c20", &mv2c20, &b_mv2c20); */
   /* fChain->SetBranchAddress("mvb", &mvb, &b_mvb); */
   /* fChain->SetBranchAddress("gaia_pu", &gaia_pu, &b_gaia_pu); */
   /* fChain->SetBranchAddress("gaia_pb", &gaia_pb, &b_gaia_pb); */
   /* fChain->SetBranchAddress("gaia_pc", &gaia_pc, &b_gaia_pc); */
   /* fChain->SetBranchAddress("ntk_ass", &ntk_ass, &b_ntk_ass); */
   /* fChain->SetBranchAddress("ntk_ipp", &ntk_ipp, &b_ntk_ipp); */
   /* fChain->SetBranchAddress("sv1ntkv", &sv1ntkv, &b_sv1ntkv); */
   /* fChain->SetBranchAddress("sv1mass", &sv1mass, &b_sv1mass); */
   /* fChain->SetBranchAddress("sv1n2tv", &sv1n2tv, &b_sv1n2tv); */
   /* fChain->SetBranchAddress("sv1efrc", &sv1efrc, &b_sv1efrc); */
   /* fChain->SetBranchAddress("dkvtx_n", &dkvtx_n, &b_dkvtx_n); */
   /* fChain->SetBranchAddress("dkvtx_x", &dkvtx_x, &b_dkvtx_x); */
   /* fChain->SetBranchAddress("dkvtx_y", &dkvtx_y, &b_dkvtx_y); */
   /* fChain->SetBranchAddress("dkvtx_z", &dkvtx_z, &b_dkvtx_z); */
   /* fChain->SetBranchAddress("dkvtx_pdg", &dkvtx_pdg, &b_dkvtx_pdg); */
   /* fChain->SetBranchAddress("smtc2", &smtc2, &b_smtc2); */
   /* fChain->SetBranchAddress("gbbnn", &gbbnn, &b_gbbnn); */
   /* fChain->SetBranchAddress("tc2d", &tc2d, &b_tc2d); */
   /* fChain->SetBranchAddress("jfc_pu", &jfc_pu, &b_jfc_pu); */
   /* fChain->SetBranchAddress("jfc_pb", &jfc_pb, &b_jfc_pb); */
   /* fChain->SetBranchAddress("jfc_pc", &jfc_pc, &b_jfc_pc); */
   /* fChain->SetBranchAddress("jf_mass", &jf_mass, &b_jf_mass); */
   /* fChain->SetBranchAddress("jf_efrc", &jf_efrc, &b_jf_efrc); */
   /* fChain->SetBranchAddress("jf_sig3", &jf_sig3, &b_jf_sig3); */
   /* fChain->SetBranchAddress("jf_dphi", &jf_dphi, &b_jf_dphi); */
   /* fChain->SetBranchAddress("jf_deta", &jf_deta, &b_jf_deta); */
   /* fChain->SetBranchAddress("jf_nvtx", &jf_nvtx, &b_jf_nvtx); */
   /* fChain->SetBranchAddress("jf_nvtx1t", &jf_nvtx1t, &b_jf_nvtx1t); */
   /* fChain->SetBranchAddress("jf_ntrkv", &jf_ntrkv, &b_jf_ntrkv); */
   /* fChain->SetBranchAddress("jf_n2tv", &jf_n2tv, &b_jf_n2tv); */
   /* fChain->SetBranchAddress("jfCharm_deltaeta", &jfCharm_deltaeta, &b_jfCharm_deltaeta); */
   /* fChain->SetBranchAddress("jfCharm_deltaphi", &jfCharm_deltaphi, &b_jfCharm_deltaphi); */
   /* fChain->SetBranchAddress("jfCharm_energyFraction", &jfCharm_energyFraction, &b_jfCharm_energyFraction); */
   /* fChain->SetBranchAddress("jfCharm_mass", &jfCharm_mass, &b_jfCharm_mass); */
   /* fChain->SetBranchAddress("jfCharm_maxSecondaryVertexRho", &jfCharm_maxSecondaryVertexRho, &b_jfCharm_maxSecondaryVertexRho); */
   /* fChain->SetBranchAddress("jfCharm_maxSecondaryVertexZ", &jfCharm_maxSecondaryVertexZ, &b_jfCharm_maxSecondaryVertexZ); */
   /* fChain->SetBranchAddress("jfCharm_maxTrackPtRel", &jfCharm_maxTrackPtRel, &b_jfCharm_maxTrackPtRel); */
   /* fChain->SetBranchAddress("jfCharm_maxTrackRapidity", &jfCharm_maxTrackRapidity, &b_jfCharm_maxTrackRapidity); */
   /* fChain->SetBranchAddress("jfCharm_meanTrackPtRel", &jfCharm_meanTrackPtRel, &b_jfCharm_meanTrackPtRel); */
   /* fChain->SetBranchAddress("jfCharm_meanTrackRapidity", &jfCharm_meanTrackRapidity, &b_jfCharm_meanTrackRapidity); */
   /* fChain->SetBranchAddress("jfCharm_minTrackPtRel", &jfCharm_minTrackPtRel, &b_jfCharm_minTrackPtRel); */
   /* fChain->SetBranchAddress("jfCharm_minTrackRapidity", &jfCharm_minTrackRapidity, &b_jfCharm_minTrackRapidity); */
   /* fChain->SetBranchAddress("jfCharm_significance3d", &jfCharm_significance3d, &b_jfCharm_significance3d); */
   /* fChain->SetBranchAddress("jfCharm_subMaxSecondaryVertexRho", &jfCharm_subMaxSecondaryVertexRho, &b_jfCharm_subMaxSecondaryVertexRho); */
   /* fChain->SetBranchAddress("jfCharm_subMaxSecondaryVertexZ", &jfCharm_subMaxSecondaryVertexZ, &b_jfCharm_subMaxSecondaryVertexZ); */
   /* fChain->SetBranchAddress("jfCharm_nSingleTracks", &jfCharm_nSingleTracks, &b_jfCharm_nSingleTracks); */
   /* fChain->SetBranchAddress("jfCharm_nTracks", &jfCharm_nTracks, &b_jfCharm_nTracks); */
   /* fChain->SetBranchAddress("jfCharm_nTracksAtVtx", &jfCharm_nTracksAtVtx, &b_jfCharm_nTracksAtVtx); */
   /* fChain->SetBranchAddress("jfCharm_nVTX", &jfCharm_nVTX, &b_jfCharm_nVTX); */
   /* fChain->SetBranchAddress("nmuon_ass", &nmuon_ass, &b_nmuon_ass); */
   /* fChain->SetBranchAddress("nmuon2_ass", &nmuon2_ass, &b_nmuon2_ass); */
   /* fChain->SetBranchAddress("ip2_pu", &ip2_pu, &b_ip2_pu); */
   /* fChain->SetBranchAddress("ip2_pb", &ip2_pb, &b_ip2_pb); */
   /* fChain->SetBranchAddress("ip2_pc", &ip2_pc, &b_ip2_pc); */
   /* fChain->SetBranchAddress("ip2_isvalid", &ip2_isvalid, &b_ip2_isvalid); */
   /* fChain->SetBranchAddress("ip2_ntk", &ip2_ntk, &b_ip2_ntk); */
   /* fChain->SetBranchAddress("ip3_pu", &ip3_pu, &b_ip3_pu); */
   /* fChain->SetBranchAddress("ip3_pc", &ip3_pc, &b_ip3_pc); */
   /* fChain->SetBranchAddress("ip3_pb", &ip3_pb, &b_ip3_pb); */
   /* fChain->SetBranchAddress("ip3_isvalid", &ip3_isvalid, &b_ip3_isvalid); */
   /* fChain->SetBranchAddress("ip3_ntk", &ip3_ntk, &b_ip3_ntk); */
   /* fChain->SetBranchAddress("jetprob_ntk", &jetprob_ntk, &b_jetprob_ntk); */
   /* fChain->SetBranchAddress("sv1_pu", &sv1_pu, &b_sv1_pu); */
   /* fChain->SetBranchAddress("sv1_pc", &sv1_pc, &b_sv1_pc); */
   /* fChain->SetBranchAddress("sv1_pb", &sv1_pb, &b_sv1_pb); */
   /* fChain->SetBranchAddress("sv1_isvalid", &sv1_isvalid, &b_sv1_isvalid); */
   /* fChain->SetBranchAddress("sv2_pu", &sv2_pu, &b_sv2_pu); */
   /* fChain->SetBranchAddress("sv2_pb", &sv2_pb, &b_sv2_pb); */
   /* fChain->SetBranchAddress("sv2_isvalid", &sv2_isvalid, &b_sv2_isvalid); */
   /* fChain->SetBranchAddress("jf_pu", &jf_pu, &b_jf_pu); */
   /* fChain->SetBranchAddress("jf_pb", &jf_pb, &b_jf_pb); */
   /* fChain->SetBranchAddress("jf_pc", &jf_pc, &b_jf_pc); */
   /* fChain->SetBranchAddress("jf_isvalid", &jf_isvalid, &b_jf_isvalid); */
   /* fChain->SetBranchAddress("jfc_isvalid", &jfc_isvalid, &b_jfc_isvalid); */
   /* fChain->SetBranchAddress("svp_isvalid", &svp_isvalid, &b_svp_isvalid); */
   /* fChain->SetBranchAddress("svp_ntkj", &svp_ntkj, &b_svp_ntkj); */
   /* fChain->SetBranchAddress("svp_x", &svp_x, &b_svp_x); */
   /* fChain->SetBranchAddress("svp_y", &svp_y, &b_svp_y); */
   /* fChain->SetBranchAddress("svp_z", &svp_z, &b_svp_z); */
   /* fChain->SetBranchAddress("svp_errx", &svp_errx, &b_svp_errx); */
   /* fChain->SetBranchAddress("svp_erry", &svp_erry, &b_svp_erry); */
   /* fChain->SetBranchAddress("svp_errz", &svp_errz, &b_svp_errz); */
   /* fChain->SetBranchAddress("svp_covxy", &svp_covxy, &b_svp_covxy); */
   /* fChain->SetBranchAddress("svp_covxz", &svp_covxz, &b_svp_covxz); */
   /* fChain->SetBranchAddress("svp_covyz", &svp_covyz, &b_svp_covyz); */
   /* fChain->SetBranchAddress("svp_chi2", &svp_chi2, &b_svp_chi2); */
   /* fChain->SetBranchAddress("svp_ndof", &svp_ndof, &b_svp_ndof); */
   /* fChain->SetBranchAddress("svp_tkn", &svp_tkn, &b_svp_tkn); */
   /* fChain->SetBranchAddress("sv0_isvalid", &sv0_isvalid, &b_sv0_isvalid); */
   /* fChain->SetBranchAddress("sv0mass", &sv0mass, &b_sv0mass); */
   /* fChain->SetBranchAddress("sv0_ntkv", &sv0_ntkv, &b_sv0_ntkv); */
   /* fChain->SetBranchAddress("sv0_ntkj", &sv0_ntkj, &b_sv0_ntkj); */
   /* fChain->SetBranchAddress("sv0_n2t", &sv0_n2t, &b_sv0_n2t); */
   /* fChain->SetBranchAddress("sv0_efrc", &sv0_efrc, &b_sv0_efrc); */
   /* fChain->SetBranchAddress("sv0_x", &sv0_x, &b_sv0_x); */
   /* fChain->SetBranchAddress("sv0_y", &sv0_y, &b_sv0_y); */
   /* fChain->SetBranchAddress("sv0_z", &sv0_z, &b_sv0_z); */
   /* fChain->SetBranchAddress("sv0_errx", &sv0_errx, &b_sv0_errx); */
   /* fChain->SetBranchAddress("sv0_erry", &sv0_erry, &b_sv0_erry); */
   /* fChain->SetBranchAddress("sv0_errz", &sv0_errz, &b_sv0_errz); */
   /* fChain->SetBranchAddress("sv0_cov_xy", &sv0_cov_xy, &b_sv0_cov_xy); */
   /* fChain->SetBranchAddress("sv0_cov_xz", &sv0_cov_xz, &b_sv0_cov_xz); */
   /* fChain->SetBranchAddress("sv0_cov_yz", &sv0_cov_yz, &b_sv0_cov_yz); */
   /* fChain->SetBranchAddress("sv0_chi2", &sv0_chi2, &b_sv0_chi2); */
   /* fChain->SetBranchAddress("sv0_ndof", &sv0_ndof, &b_sv0_ndof); */
   /* fChain->SetBranchAddress("sv0_ntk", &sv0_ntk, &b_sv0_ntk); */
   /* fChain->SetBranchAddress("smuon_n", &smuon_n, &b_smuon_n); */
   /* fChain->SetBranchAddress("smuon2_n", &smuon2_n, &b_smuon2_n); */
   /* fChain->SetBranchAddress("smuon2chi2_info", &smuon2chi2_info, &b_smuon2chi2_info); */
   /* fChain->SetBranchAddress("msvp_isvalid", &msvp_isvalid, &b_msvp_isvalid); */
   /* fChain->SetBranchAddress("msvp_ntkv", &msvp_ntkv, &b_msvp_ntkv); */
   /* fChain->SetBranchAddress("msvp_ntkj", &msvp_ntkj, &b_msvp_ntkj); */
   /* fChain->SetBranchAddress("msvp_n2t", &msvp_n2t, &b_msvp_n2t); */
   /* fChain->SetBranchAddress("msvp_nvtx", &msvp_nvtx, &b_msvp_nvtx); */
   /* fChain->SetBranchAddress("msvp_normwdist", &msvp_normwdist, &b_msvp_normwdist); */
   /* fChain->SetBranchAddress("msvp_msvinjet_n", &msvp_msvinjet_n, &b_msvp_msvinjet_n); */
   /* fChain->SetBranchAddress("vkalbadtk_n", &vkalbadtk_n, &b_vkalbadtk_n); */
   /* fChain->SetBranchAddress("jfvx_n", &jfvx_n, &b_jfvx_n); */
   /* fChain->SetBranchAddress("ip2_c", &ip2_c, &b_ip2_c); */
   /* fChain->SetBranchAddress("ip3_c", &ip3_c, &b_ip3_c); */
   /* fChain->SetBranchAddress("sv1_c", &sv1_c, &b_sv1_c); */
   /* fChain->SetBranchAddress("jfc_c", &jfc_c, &b_jfc_c); */
   /* fChain->SetBranchAddress("ip2_cu", &ip2_cu, &b_ip2_cu); */
   /* fChain->SetBranchAddress("ip3_cu", &ip3_cu, &b_ip3_cu); */
   /* fChain->SetBranchAddress("sv1_cu", &sv1_cu, &b_sv1_cu); */
   /* fChain->SetBranchAddress("jfc_cu", &jfc_cu, &b_jfc_cu); */
   /* fChain->SetBranchAddress("jf_dR", &jf_dR, &b_jf_dR); */
   /* fChain->SetBranchAddress("jfCharm_dR", &jfCharm_dR, &b_jfCharm_dR); */

   /* fChain->Branch("run",		&run,			"run/I"); */
   fChain->Branch("mcchannel",		&mcchannel,		"mcchannel/I");
   /* fChain->Branch("evt",		&evt,			"evt/I"); */
   /* fChain->Branch("evtweight",		&evtweight,		"evtweight/I"); */
   /* fChain->Branch("npv",		&npv,			"npv/I"); */
   /* fChain->Branch("muAct",		&muAct,			"muAct/I"); */
   fChain->Branch("muAvg",		&muAvg,			"muAvg/I");
   /* fChain->Branch("pv0_isOK",		&pv0_isOK,		"pv0_isOK/I"); */
   /* fChain->Branch("pv0_x",		&pv0_x,			"pv0_x/D"); */
   /* fChain->Branch("pv0_y",		&pv0_y,			"pv0_y/D"); */
   /* fChain->Branch("pv0_z",		&pv0_z,			"pv0_z/D"); */
   /* fChain->Branch("nbjet",		&nbjet,			"nbjet/I"); */
   /* fChain->Branch("nbjetok",		&nbjetok,		"nbjetok/I"); */
   /* fChain->Branch("htjet",		&htjet,			"htjet/D"); */
   /* fChain->Branch("triggerBitsEvt",	&triggerBitsEvt,	"triggerBitsEvt/D"); */
   /* fChain->Branch("plateauBitsEvt",	&plateauBitsEvt,	"plateauBitsEvt/D"); */
   /* fChain->Branch("triggerBitsJet",	&triggerBitsJet,	"triggerBitsJet/D"); */
   /* fChain->Branch("plateauBitsJet",	&plateauBitsJet,	"plateauBitsJet/D"); */
   /* fChain->Branch("jetidx",		&jetidx,		"jetidx/I"); */

   /* fChain->Branch("GhostL_q",		&GhostL_q,		"GhostL_q/I"); */
   /* if (!performanceOnly) { */
   /*   fChain->Branch("GhostL_HadI",	&GhostL_HadI,		"GhostL_HadI/I"); */
   /*   fChain->Branch("GhostL_HadF",	&GhostL_HadF,		"GhostL_HadF/I"); */
   /*   fChain->Branch("aliveAfterOR",	&aliveAfterOR,		"aliveAfterOR/I"); */
   /* } */
   fChain->Branch("truthMatch",		&truthMatch,		"truthMatch/I");
   /* fChain->Branch("truthPt",		&truthPt,		"truthPt/F"); */
   /* fChain->Branch("dRiso",		&dRiso,		"dRiso/I"); */
   fChain->Branch("JVF",		&JVF,		"JVF/F");
   fChain->Branch("JVT",		&JVT,		"JVT/F");
   
   /* fChain->Branch("rank",		&rank,			"rank/I"); */
   /* fChain->Branch("originIndex",	&originIndex,		"originIndex/I"); */
   /* fChain->Branch("caloWidth",		&caloWidth,		"caloWidth/F"); */
   /* fChain->Branch("trkWidth",		&trkWidth,		"trkWidth/F"); */

   fChain->Branch("pt_calib",		&pt_calib,		"pt_calib/D");
   fChain->Branch("eta_calib",		&eta_calib,		"eta_calib/D");
   /* fChain->Branch("phi_calib",		&phi_calib,		"phi_calib/D"); */
   /* fChain->Branch("m_calib",		&m_calib,		"m_calib/D"); */

   fChain->Branch("pt_uCalib",		&pt_uCalib,		"pt_uCalib/D");
   fChain->Branch("eta_uCalib",		&eta_uCalib,		"eta_uCalib/D");
   /* fChain->Branch("phi_uCalib",		&phi_uCalib,		"phi_uCalib/D"); */
   /* fChain->Branch("m_uCalib",		&m_uCalib,		"m_uCalib/D"); */

   fChain->Branch("pt",			&pt,			"pt/D");
   fChain->Branch("eta",		&eta,			"eta/D");
   fChain->Branch("phi",		&phi,			"phi/D");
   fChain->Branch("m",			&m,			"m/D");
   /* fChain->Branch("e",			&e,			"e/D"); */
   /* fChain->Branch("jvf",		&jvf,			"jvf/D"); */
   /* fChain->Branch("drminj",		&drminj,		"drminj/D"); */
   /* fChain->Branch("dphiminj",		&dphiminj,		"dphiminj/D"); */
   fChain->Branch("isGood",		&isGood,		"isGood/I");
   fChain->Branch("label",		&label,			"label/I");
   /* fChain->Branch("nlabel",		&nlabel,		"nlabel/I"); */
   /* fChain->Branch("nlept",		&nlept,			"nlept/I"); */
   /* fChain->Branch("drb",		&drb,			"drb/D"); */
   /* fChain->Branch("drc",		&drc,			"drc/D"); */
   /* fChain->Branch("drt",		&drt,			"drt/D"); */
   /* fChain->Branch("jtp",		&jtp,			"jtp/D"); */
   /* fChain->Branch("sv0",		&sv0,			"sv0/D"); */
   fChain->Branch("ip2",		&ip2,			"ip2/D");
   fChain->Branch("ip3",		&ip3,			"ip3/D");
   /* fChain->Branch("sv1",		&sv1,			"sv1/D"); */
   /* fChain->Branch("sv2",		&sv2,			"sv2/D"); */
   /* fChain->Branch("cmb",		&cmb,			"cmb/D"); */
   /* fChain->Branch("jft",		&jft,			"jft/D"); */
   /* fChain->Branch("jfc",		&jfc,			"jfc/D"); */
   /* fChain->Branch("smt",		&smt,			"smt/D"); */
   /* fChain->Branch("mv1",		&mv1,			"mv1/D"); */
   /* fChain->Branch("mv1c",		&mv1c,			"mv1c/F"); */

   if((TString)tree->GetName()=="minibtag") {
     fChain->Branch("mv2c00",		&mv2c00,		"mv2c00/F");
     fChain->Branch("mv2c10",		&mv2c10,		"mv2c10/F");
     fChain->Branch("mv2c20",		&mv2c20,		"mv2c20/F");
     //fChain->Branch("mv2c100",		&mv2c100,		"mv2c100/F");
     fChain->Branch("mv2m_pb",		&mv2m_pb,		"mv2m_pb/F");
     fChain->Branch("mv2m_pu",		&mv2m_pu,		"mv2m_pu/F");
     fChain->Branch("mv2m_pc",		&mv2m_pc,		"mv2m_pc/F");
   }
   /* fChain->Branch("mvb",		&mvb,			"mvb/F"); */

   /* fChain->Branch("gaia_pu",		&gaia_pu,		"gaia_pu/F"); */
   /* fChain->Branch("gaia_pb",		&gaia_pb,		"gaia_pb/F"); */
   /* fChain->Branch("gaia_pc",		&gaia_pc,		"gaia_pc/F"); */
   /* fChain->Branch("ntk_ass",		&ntk_ass,		"ntk_ass/I"); */
   /* fChain->Branch("ntk_ipp",		&ntk_ipp,		"ntk_ipp/I"); */

   /* fChain->Branch("dkvtx_n",		&dkvtx_n,		"dkvtx_n"); */
   /* fChain->Branch("dkvtx_x",		&dkvtx_x,		"dkvtx_x/D"); */
   /* fChain->Branch("dkvtx_y",		&dkvtx_y,		"dkvtx_y/D"); */
   /* fChain->Branch("dkvtx_z",		&dkvtx_z,		"dkvtx_z/D"); */
   /* fChain->Branch("dkvtx_pdg",		&dkvtx_pdg,		"dkvtx_pdg"); */
   /* fChain->Branch("smtc2",		&smtc2,			"smtc2/D"); */
   /* fChain->Branch("gbbnn",		&gbbnn,			"gbbnn/D"); */
   /* fChain->Branch("tc2d",		&tc2d,			"tc2d/D"); */

   if (!performanceOnly) {
     /* fChain->Branch("jfc_pu",		&jfc_pu,		"jfc_pu/D"); */
     /* fChain->Branch("jfc_pb",		&jfc_pb,		"jfc_pb/D"); */
     /* fChain->Branch("jfc_pc",		&jfc_pc,		"jfc_pc/D"); */
     fChain->Branch("jf_mass",		&jf_mass,		"jf_mass/D");
     fChain->Branch("jf_efrc",		&jf_efrc,		"jf_efrc/D");
     /* fChain->Branch("jf_efrc2",		&jf_efrc2,		"jf_efrc2/D"); */
     fChain->Branch("jf_sig3",		&jf_sig3,		"jf_sig3/D");
     /* fChain->Branch("jf_dphi",		&jf_dphi,		"jf_dphi/D"); */
     /* fChain->Branch("jf_deta",		&jf_deta,		"jf_deta/D"); */
     fChain->Branch("jf_nvtx",		&jf_nvtx,		"jf_nvtx/I");
     fChain->Branch("jf_nvtx1t",		&jf_nvtx1t,		"jf_nvtx1t/I");
     fChain->Branch("jf_ntrkv",		&jf_ntrkv,		"jf_ntrkv/I");
     fChain->Branch("jf_n2tv",		&jf_n2tv,		"jf_n2tv/I");
     /* fChain->Branch("jfCharm_deltaeta",		&jfCharm_deltaeta,	"jfCharm_deltaeta"); */
     /* fChain->Branch("jfCharm_deltaphi",		&jfCharm_deltaphi,	"jfCharm_deltaphi"); */
     /* fChain->Branch("jfCharm_energyFraction",		&jfCharm_energyFraction,	&b_jfCharm_energyFraction); */
     /* fChain->Branch("jfCharm_mass",			&jfCharm_mass,	&b_jfCharm_mass); */
     /* fChain->Branch("jfCharm_maxSecondaryVertexRho",	&jfCharm_maxSecondaryVertexRho,	&b_jfCharm_maxSecondaryVertexRho); */
     /* fChain->Branch("jfCharm_maxSecondaryVertexZ",	&jfCharm_maxSecondaryVertexZ,	&b_jfCharm_maxSecondaryVertexZ); */
     /* fChain->Branch("jfCharm_maxTrackPtRel",		&jfCharm_maxTrackPtRel,	&b_jfCharm_maxTrackPtRel); */
     /* fChain->Branch("jfCharm_maxTrackRapidity",	&jfCharm_maxTrackRapidity,	&b_jfCharm_maxTrackRapidity); */
     /* fChain->Branch("jfCharm_meanTrackPtRel",		&jfCharm_meanTrackPtRel,	&b_jfCharm_meanTrackPtRel); */
     /* fChain->Branch("jfCharm_meanTrackRapidity",	&jfCharm_meanTrackRapidity,	&b_jfCharm_meanTrackRapidity); */
     /* fChain->Branch("jfCharm_minTrackPtRel",		&jfCharm_minTrackPtRel,	&b_jfCharm_minTrackPtRel); */
     /* fChain->Branch("jfCharm_minTrackRapidity",	&jfCharm_minTrackRapidity,	&b_jfCharm_minTrackRapidity); */
     /* fChain->Branch("jfCharm_significance3d",		&jfCharm_significance3d,	&b_jfCharm_significance3d); */
     /* fChain->Branch("jfCharm_subMaxSecondaryVertexRho",&jfCharm_subMaxSecondaryVertexRho,	&b_jfCharm_subMaxSecondaryVertexRho); */
     /* fChain->Branch("jfCharm_subMaxSecondaryVertexZ",	&jfCharm_subMaxSecondaryVertexZ,	&b_jfCharm_subMaxSecondaryVertexZ); */
     /* fChain->Branch("jfCharm_nSingleTracks",		&jfCharm_nSingleTracks,	&b_jfCharm_nSingleTracks); */
     /* fChain->Branch("jfCharm_nTracks",			&jfCharm_nTracks,	&b_jfCharm_nTracks); */
     /* fChain->Branch("jfCharm_nTracksAtVtx",		&jfCharm_nTracksAtVtx,	&b_jfCharm_nTracksAtVtx); */
     /* fChain->Branch("jfCharm_nVTX",			&jfCharm_nVTX,		"jfCharm_nVTX"); */
     /* fChain->Branch("nmuon_ass",		&nmuon_ass,		"nmuon_ass/I"); */
     /* fChain->Branch("nmuon2_ass",		&nmuon2_ass,		"nmuon2_ass/I"); */

     fChain->Branch("ip2_pu",		&ip2_pu,		"ip2_pu/F");
     fChain->Branch("ip2_pb",		&ip2_pb,		"ip2_pb/F");
     fChain->Branch("ip2_pc",		&ip2_pc,		"ip2_pc/F");
     /* fChain->Branch("ip2_isvalid",	&ip2_isvalid,		"ip2_isvalid/I"); */
     /* fChain->Branch("ip2_ntk",		&ip2_ntk,		"ip2_ntk/I"); */

     /* fChain->Branch("ip3_pu",		&ip3_pu,		"ip3_pu/F"); */
     /* fChain->Branch("ip3_pc",		&ip3_pc,		"ip3_pc/F"); */
     /* fChain->Branch("ip3_pb",		&ip3_pb,		"ip3_pb/F"); */
     /* fChain->Branch("ip3_isvalid",	&ip3_isvalid,		"ip3_isvalid/I"); */
     /* fChain->Branch("ip3_ntrk",		&ip3_ntk,		"ip3_ntrk/I"); */
     /* fChain->Branch("ip3_nDisplacedTrk",&ip3_nDisplacedTrk,	"ip3_nDisplacedTrk/I"); */

     /* fChain->Branch("jetprob_ntk",	&jetprob_ntk,		"jetprob_ntk/I"); */
     /* fChain->Branch("sv1_pu",		&sv1_pu,		"sv1_pu/F"); */
     /* fChain->Branch("sv1_pc",		&sv1_pc,		"sv1_pc/F"); */
     /* fChain->Branch("sv1_pb",		&sv1_pb,		"sv1_pb/F"); */
     /* fChain->Branch("sv1_isvalid",	&sv1_isvalid,		"sv1_isvalid/I"); */
     /* fChain->Branch("sv1_ntk",		&sv1_ntk,		"sv1_ntk/I"); */

     fChain->Branch("sv1_ntkv",		&sv1ntkv,		"sv1_ntkv/I");
     fChain->Branch("sv1_mass",		&sv1mass,		"sv1_mass/D");
     fChain->Branch("sv1_n2t",		&sv1n2tv,		"sv1_n2t/I" );//     fChain->Branch("sv1_n2tv",		&sv1n2tv,		"sv1_n2tv/I");
     fChain->Branch("sv1_efrc",		&sv1efrc,		"sv1_efrc/D");
     /* fChain->Branch("sv1_efrc2",	&sv1efrc2,		"sv1_efrc2/D"); */
     fChain->Branch("sv1_dR",	        &sv1dR,	         	"sv1_dR/D");
     
     //fChain->Branch("sv1_norm",		&sv1norm,		"sv1_norm/D");
     fChain->Branch("sv1_Lxy",		&sv1Lxy,		"sv1_Lxy/D" );
     fChain->Branch("sv1_L3d",		&sv1L3d,		"sv1_L3d/D" );
     fChain->Branch("sv1_sig3",		&sv1sig3,		"sv1_sig3/D" );
     /* fChain->Branch("sv1_vx_x",		&sv1_vx_x,		"sv1_vx_x/D" ); */
     /* fChain->Branch("sv1_vx_y",		&sv1_vx_y,		"sv1_vx_y/D" ); */
     /* fChain->Branch("sv1_vx_z",		&sv1_vx_z,		"sv1_vx_z/D" ); */
     /* fChain->Branch("sv1_Lxy_wrtPV",	&sv1Lxy_wrtPV,		"sv1_Lxy_wrtPV/D" ); */
     /* fChain->Branch("sv1_L3d_wrtPV",	&sv1L3d_wrtPV,		"sv1_L3d_wrtPV/D" ); */
     /* fChain->Branch("sv1_vx_dx",	&sv1_vx_dx,		"sv1_vx_dx/D" ); */
     /* fChain->Branch("sv1_vx_dy",	&sv1_vx_dy,		"sv1_vx_dy/D" ); */
     /* fChain->Branch("sv1_vx_dz",	&sv1_vx_dz,		"sv1_vx_dz/D" ); */

     /* fChain->Branch("sv2_pu",		&sv2_pu,		"sv2_pu/F"); */
     /* fChain->Branch("sv2_pb",		&sv2_pb,		"sv2_pb/F"); */
     /* fChain->Branch("sv2_isvalid",	&sv2_isvalid,		"sv2_isvalid/I"); */

     /* fChain->Branch("jf_pu",		&jf_pu,			"jf_pu/F"); */
     /* fChain->Branch("jf_pb",		&jf_pb,			"jf_pb/F"); */
     /* fChain->Branch("jf_pc",		&jf_pc,			"jf_pc/F"); */
     /* fChain->Branch("jf_isvalid",		&jf_isvalid,		"jf_isvalid/I"); */
     /* fChain->Branch("jf_ntk",		&jf_ntk,		"jf_ntk/I"); */
     /* fChain->Branch("jfc_isvalid",	&jfc_isvalid,		"jfc_isvalid/I"); */

     /* fChain->Branch("svp_isvalid",	&svp_isvalid,		"svp_isvalid/I"); */
     /* fChain->Branch("svp_ntkj",		&svp_ntkj,		"svp_ntkj/I"); */
     /* fChain->Branch("svp_x",		&svp_x,			"svp_x/F"); */
     /* fChain->Branch("svp_y",		&svp_y,			"svp_y/F"); */
     /* fChain->Branch("svp_z",		&svp_z,			"svp_z/F"); */
     /* fChain->Branch("svp_errx",		&svp_errx,		"svp_errx/F"); */
     /* fChain->Branch("svp_erry",		&svp_erry,		"svp_erry/F"); */
     /* fChain->Branch("svp_errz",		&svp_errz,		"svp_errz/F"); */
     /* fChain->Branch("svp_covxy",		&svp_covxy,		"svp_covxy/F"); */
     /* fChain->Branch("svp_covxz",		&svp_covxz,		"svp_covxz/F"); */
     /* fChain->Branch("svp_covyz",		&svp_covyz,		"svp_covyz/F"); */
     /* fChain->Branch("svp_chi2",		&svp_chi2,		"svp_chi2/F"); */
     /* fChain->Branch("svp_ndof",		&svp_ndof,		"svp_ndof/I"); */
     /* fChain->Branch("svp_tkn",		&svp_tkn,		"svp_tkn/I"); */

     /* fChain->Branch("sv0_isvalid",	&sv0_isvalid,		"sv0_isvalid/I"); */
     /* fChain->Branch("sv0mass",		&sv0mass,		"sv0mass/D"); */
     /* fChain->Branch("sv0_ntkv",		&sv0_ntkv,		"sv0_ntkv/I"); */
     /* /\* fChain->Branch("sv0_ntkj",		&sv0_ntkj,		"sv0_ntkj/I"); *\/ */
     /* fChain->Branch("sv0_n2t",		&sv0_n2t,		"sv0_n2t/I"); */
     /* fChain->Branch("sv0_efrc",		&sv0_efrc,		"sv0_efrc/F"); */

     /* fChain->Branch("sv0_x",		&sv0_x,			"sv0_x/F"); */
     /* fChain->Branch("sv0_y",		&sv0_y,			"sv0_y/F"); */
     /* fChain->Branch("sv0_z",		&sv0_z,			"sv0_z/F"); */
     /* fChain->Branch("sv0_errx",		&sv0_errx,		"sv0_errx/F"); */
     /* fChain->Branch("sv0_erry",		&sv0_erry,		"sv0_erry/F"); */
     /* fChain->Branch("sv0_errz",		&sv0_errz,		"sv0_errz/F"); */
     /* fChain->Branch("sv0_cov_xy",		&sv0_cov_xy,		"sv0_cov_xy/F"); */
     /* fChain->Branch("sv0_cov_xz",		&sv0_cov_xz,		"sv0_cov_xz/F"); */
     /* fChain->Branch("sv0_cov_yz",		&sv0_cov_yz,		"sv0_cov_yz/F"); */
     /* fChain->Branch("sv0_chi2",		&sv0_chi2,		"sv0_chi2/F"); */
     /* fChain->Branch("sv0_ndof",		&sv0_ndof,		"sv0_ndof/I"); */
     /* fChain->Branch("sv0_ntk",		&sv0_ntk,		"sv0_ntk/I"); */

     /* fChain->Branch("smuon_n",		&smuon_n,		"smuon_n/I"); */
     /* fChain->Branch("smuon2_n",	&smuon2_n,		"smuon2_n/I"); */
     /* fChain->Branch("smuon2chi2_info",	&smuon2chi2_info,	"smuon2chi2_info"); */

     /* fChain->Branch("msvp_isvalid",	&msvp_isvalid,		"msvp_isvalid/I"); */
     /* fChain->Branch("msvp_ntkv",		&msvp_ntkv,		"msvp_ntkv/I"); */
     /* fChain->Branch("msvp_ntkj",		&msvp_ntkj,		"msvp_ntkj/I"); */
     /* fChain->Branch("msvp_n2t",		&msvp_n2t,		"msvp_n2t/I"); */
     /* fChain->Branch("msvp_nvtx",		&msvp_nvtx,		"msvp_nvtx/I"); */
     /* fChain->Branch("msvp_normwdist",	&msvp_normwdist,	"msvp_normwdist/F"); */
     /* fChain->Branch("msvp_msvinjet_n",	&msvp_msvinjet_n,	"msvp_msvinjet_n/I"); */

     /* fChain->Branch("vkalbadtk_n",	&vkalbadtk_n,		"vkalbadtk_n/I"); */
     /* fChain->Branch("jfvx_n",		&jfvx_n,		"jfvx_n/I"); */

     fChain->Branch("ip2_c",		&ip2_c,			"ip2_c/F");
     fChain->Branch("ip3_c",		&ip3_c,			"ip3_c/F");
     /* fChain->Branch("sv1_c",		&sv1_c,			"sv1_c/F"); */
     /* fChain->Branch("jfc_c",		&jfc_c,			"jfc_c/F"); */
     fChain->Branch("ip2_cu",		&ip2_cu,		"ip2_cu/F");
     fChain->Branch("ip3_cu",		&ip3_cu,		"ip3_cu/F");
     /* fChain->Branch("sv1_cu",		&sv1_cu,		"sv1_cu/F"); */
     /* fChain->Branch("jfc_cu",		&jfc_cu,		"jfc_cu/F"); */
     fChain->Branch("jf_dR",		&jf_dR,			"jf_dR/F");
     //fChain->Branch("jfCharm_dR",		&jfCharm_dR,		&b_jfCharm_dR);

     fChain->Branch("width", &width, "width/F");
     fChain->Branch("n_trk_sigd0cut", &n_trk_sigd0cut, "n_trk_sigd0cut/I");
     fChain->Branch("trk3_d0sig", &trk3_d0sig, "trk3_d0sig/F");
     fChain->Branch("trk3_z0sig", &trk3_z0sig, "trk3_z0sig/F");
     fChain->Branch("sv_scaled_efc", &sv_scaled_efc, "sv_scaled_efc/F");
     fChain->Branch("jf_scaled_efc", &jf_scaled_efc, "jf_scaled_efc/F");
   }

   Notify();
}

Bool_t minibtag::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void minibtag::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t minibtag::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

float minibtag::log(double num, double den) {
  float log=-20;//until Def03 and def06-
  //float log=-30;//def 04-05
  if      (num>0 and den>0) log= TMath::Log(num/den);
  else if (num==-99 or den==-99) log= -99;
  return log;
}

void minibtag::initializeVariables(){
  run			=0;
  mcchannel		=0;
  evt			=0;
  evtweight		=0;
  npv			=0;
  muAct			=0;
  muAvg			=0;
  pv0_isOK		=0;
  pv0_x			=0;
  pv0_y			=0;
  pv0_z			=0;
  nbjet			=0;
  nbjetok		=0;
  htjet			=0;
  triggerBitsEvt	=0;
  plateauBitsEvt	=0;
  triggerBitsJet	=0;
  plateauBitsJet	=0;
  jetidx		=0;

  GhostL_q		=0;
  GhostL_HadI		=0;
  GhostL_HadF		=0;
  aliveAfterOR		=0;
  truthMatch		=0;
  truthPt		=0;
  dRiso			=0;
  JVF			=0;
  JVT			=0;

  rank			=0;
  originIndex		=0;
  caloWidth		=0;
  trkWidth		=0;

  pt_calib		=0;
  eta_calib		=0;
  phi_calib		=0;
  m_calib		=0;

  pt_uCalib		=0;
  eta_uCalib		=0;
  phi_uCalib		=0;
  m_uCalib		=0;

  pt			=0;
  eta			=0;
  phi			=0;
  m			=0;
  e			=0;
  jvf			=0;
  drminj		=0;
  dphiminj		=0;
  isGood		=0;
  label			=0;
  nlabel		=0;
  nlept			=0;
  drb			=0;
  drc			=0;
  drt			=0;
  jtp			=0;
  sv0			=0;
  ip2			=0;
  ip3			=0;
  sv1			=0;
  sv2			=0;
  cmb			=0;
  jft			=0;
  jfc			=0;
  smt			=0;
  mv1			=0;
  mv1c			=0;
  mv2c00		=0;
  mv2c10		=0;
  mv2c20		=0;
  mv2c100		=0;
  mv2m_pb		=0;
  mv2m_pu		=0;
  mv2m_pc		=0;
  mvb			=0;
  gaia_pu		=0;
  gaia_pb		=0;
  gaia_pc		=0;
  ntk_ass		=0;
  ntk_ipp		=0;
  sv1ntkv		=0;
  sv1mass		=0;
  sv1n2tv		=0;
  sv1efrc		=0;
  sv1efrc2		=0;
  sv1dR 		=0;
  sv1norm		=0;
  sv1Lxy		=0;
  sv1L3d		=0;
  sv1sig3		=0;
  sv1_vx_x		=0;
  sv1_vx_y		=0;
  sv1_vx_z		=0;
  sv1Lxy_wrtPV		=0;
  sv1L3d_wrtPV		=0;
  sv1_vx_dx		=0;
  sv1_vx_dy		=0;
  sv1_vx_dz		=0;
  dkvtx_n		=0;
  smtc2			=0;
  gbbnn			=0;
  tc2d			=0;
  jfc_pu		=0;
  jfc_pb		=0;
  jfc_pc		=0;
  jf_mass		=0;
  jf_efrc		=0;
  jf_efrc2		=0;
  jf_sig3		=0;
  jf_dphi		=0;
  jf_deta		=0;
  jf_nvtx		=0;
  jf_nvtx1t		=0;
  jf_ntrkv		=0;
  jf_n2tv		=0;
  jfCharm_deltaeta			=0;
  jfCharm_deltaphi			=0;
  jfCharm_energyFraction		=0;
  jfCharm_mass				=0;
  jfCharm_maxSecondaryVertexRho		=0;
  jfCharm_maxSecondaryVertexZ		=0;
  jfCharm_maxTrackPtRel			=0;
  jfCharm_maxTrackRapidity		=0;
  jfCharm_meanTrackPtRel		=0;
  jfCharm_meanTrackRapidity		=0;
  jfCharm_minTrackPtRel			=0;
  jfCharm_minTrackRapidity		=0;
  jfCharm_significance3d		=0;
  jfCharm_subMaxSecondaryVertexRho	=0;
  jfCharm_subMaxSecondaryVertexZ	=0;
  jfCharm_nSingleTracks			=0;
  jfCharm_nTracks			=0;
  jfCharm_nTracksAtVtx			=0;
  jfCharm_nVTX				=0;
  nmuon_ass		=0;
  nmuon2_ass		=0;
  ip2_pu		=0;
  ip2_pb		=0;
  ip2_pc		=0;
  ip2_isvalid		=0;
  ip2_ntk		=0;
  ip3_pu		=0;
  ip3_pc		=0;
  ip3_pb		=0;
  ip3_isvalid		=0;
  ip3_ntk		=0;
  ip3_nDisplacedTrk     =0;
  jetprob_ntk		=0;
  sv1_pu		=0;
  sv1_pc		=0;
  sv1_pb		=0;
  sv1_isvalid		=0;
  sv1_ntk		=0;
  sv2_pu		=0;
  sv2_pb		=0;
  sv2_isvalid		=0;
  jf_pu			=0;
  jf_pb			=0;
  jf_pc			=0;
  jf_isvalid		=0;
  jf_ntk		=0;
  jfc_isvalid		=0;
  svp_isvalid		=0;
  svp_ntkj		=0;
  svp_x			=0;
  svp_y			=0;
  svp_z			=0;
  svp_errx		=0;
  svp_erry		=0;
  svp_errz		=0;
  svp_covxy		=0;
  svp_covxz		=0;
  svp_covyz		=0;
  svp_chi2		=0;
  svp_ndof		=0;
  svp_tkn		=0;
  sv0_isvalid		=0;
  sv0mass		=0;
  sv0_ntkv		=0;
  sv0_ntkj		=0;
  sv0_n2t		=0;
  sv0_efrc		=0;
  sv0_x			=0;
  sv0_y			=0;
  sv0_z			=0;
  sv0_errx		=0;
  sv0_erry		=0;
  sv0_errz		=0;
  sv0_cov_xy		=0;
  sv0_cov_xz		=0;
  sv0_cov_yz		=0;
  sv0_chi2		=0;
  sv0_ndof		=0;
  sv0_ntk		=0;
  smuon_n		=0;
  smuon2_n		=0;
  smuon2chi2_info	=0;
  msvp_isvalid		=0;
  msvp_ntkv		=0;
  msvp_ntkj		=0;
  msvp_n2t		=0;
  msvp_nvtx		=0;
  msvp_normwdist	=0;
  msvp_msvinjet_n	=0;
  vkalbadtk_n		=0;
  jfvx_n		=0;
  ip2_c			=0;
  ip3_c			=0;
  sv1_c			=0;
  jfc_c			=0;
  ip2_cu		=0;
  ip3_cu		=0;
  sv1_cu		=0;
  jfc_cu		=0;
  jf_dR			=0;
  jfCharm_dR		=0;

  width = 0;
  n_trk_sigd0cut = 0;
  trk3_d0sig = 0;
  trk3_z0sig = 0;
  sv_scaled_efc = 0;
  jf_scaled_efc = 0;

}

#endif // #ifdef minibtag_cxx
