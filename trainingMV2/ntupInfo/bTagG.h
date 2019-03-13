//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar  6 14:37:39 2015 by ROOT version 5.34/19
// from TTree bTag/bTag
// found on file: flavntuple_test.root
//////////////////////////////////////////////////////////

#ifndef bTagG_h
#define bTagG_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
using std::vector;

// Fixed size dimensions of array or collections stored in the TTree if any.

class bTagG {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   vector<int>     *jet_SV1_jet_sv1_ntrkv;
   vector<int>     *jet_SV1_jet_sv1_n2t;
   vector<float>   *jet_SV1_jet_sv1_m;
   vector<float>   *jet_SV1_jet_sv1_efc;
   vector<float>   *jet_SV1_jet_sv1_normdist;
   vector<float>   *jet_SV1_jet_sv1_sig3d;
   vector<float>   *jet_SV1_jet_sv1_pb;
   vector<float>   *jet_SV1_jet_sv1_pc;
   vector<float>   *jet_SV1_jet_sv1_pu;
   vector<double>  *jet_SV1_jet_sv1_llr;
   vector<float>   *jet_SV1_jet_sv1_vtx_x;
   vector<float>   *jet_SV1_jet_sv1_vtx_y;
   vector<float>   *jet_SV1_jet_sv1_vtx_z;
   Int_t           jet_njets;
   vector<float>   *jet_pt;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_E;
   vector<int>     *jet_cleaning;
   vector<int>     *jet_truthMatch;
   vector<float>   *jet_truth_pt;
   vector<float>   *jet_jvf;
   vector<float>   *jet_jvt;
   vector<float>   *jet_cpt;
   vector<float>   *jet_ceta;
   vector<float>   *jet_cphi;
   vector<float>   *jet_cE;
   vector<int>     *jet_truthflav;
   vector<int>     *jet_truthflavExCHad;
   vector<float>   *jet_jf_pb;
   vector<float>   *jet_jf_pc;
   vector<float>   *jet_jf_pu;
   vector<double>  *jet_jf_llr;
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
   vector<double>  *jet_jfcombnn_llr;
   vector<double>  *jet_mv1;
   vector<double>  *jet_mv1c;
   vector<double>  *jet_mv2m_pb;
   vector<double>  *jet_mv2m_pu;
   vector<double>  *jet_mv2m_pc;
   vector<double>  *jet_mv2c00;
   vector<double>  *jet_mv2c10;
   vector<double>  *jet_mv2c20;
   vector<double>  *jet_mv2c100;
   vector<double>  *jet_mvb;
   vector<double>  *jet_multisvbb1;
   vector<double>  *jet_multisvbb2;
   vector<float>   *jet_IP2D_jet_ipxd_pb;
   vector<float>   *jet_IP2D_jet_ipxd_pc;
   vector<float>   *jet_IP2D_jet_ipxd_pu;
   vector<double>  *jet_IP2D_jet_ipxd_llr;
   vector<int>     *jet_IP2D_jet_ipxd_ntrk;
   vector<float>   *jet_IP3D_jet_ipxd_pb;
   vector<float>   *jet_IP3D_jet_ipxd_pc;
   vector<float>   *jet_IP3D_jet_ipxd_pu;
   vector<double>  *jet_IP3D_jet_ipxd_llr;
   vector<int>     *jet_IP3D_jet_ipxd_ntrk;

   std::vector<float> *jet_width;
   std::vector<int>   *jet_n_trk_sigd0cut;
   std::vector<float> *jet_trk3_d0sig;
   std::vector<float> *jet_trk3_z0sig;
   std::vector<float> *jet_sv_scaled_efc;
   std::vector<float> *jet_jf_scaled_efc;

   /* vector<int>     *AntiKt4EMTopoJets_SV1_jet_sv1_ntrkv; */
   /* vector<int>     *AntiKt4EMTopoJets_SV1_jet_sv1_n2t; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_m; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_efc; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_normdist; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_sig3d; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_pb; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_pc; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_pu; */
   /* vector<double>  *AntiKt4EMTopoJets_SV1_jet_sv1_llr; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_vtx_x; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_vtx_y; */
   /* vector<float>   *AntiKt4EMTopoJets_SV1_jet_sv1_vtx_z; */
   /* Int_t           AntiKt4EMTopoJets_njets; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_pt; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_eta; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_phi; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_E; */
   /* vector<int>     *AntiKt4EMTopoJets_jet_cleaning; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jvf; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jvt; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_cpt; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_ceta; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_cphi; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_cE; */
   /* vector<int>     *AntiKt4EMTopoJets_jet_truthflav; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jf_pb; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jf_pc; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jf_pu; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_jf_llr; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jf_m; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jf_efc; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jf_deta; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jf_dphi; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jf_ntrkAtVx; */
   /* vector<int>     *AntiKt4EMTopoJets_jet_jf_nvtx; */
   /* vector<int>     *AntiKt4EMTopoJets_jet_jf_sig3d; */
   /* vector<int>     *AntiKt4EMTopoJets_jet_jf_nvtx1t; */
   /* vector<int>     *AntiKt4EMTopoJets_jet_jf_n2t; */
   /* vector<vector<float> > *AntiKt4EMTopoJets_jet_jf_chi2; */
   /* vector<vector<float> > *AntiKt4EMTopoJets_jet_jf_ndf; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jfcombnn_pb; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jfcombnn_pc; */
   /* vector<float>   *AntiKt4EMTopoJets_jet_jfcombnn_pu; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_jfcombnn_llr; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mv1; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mv1c; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mv2m_pb; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mv2m_pu; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mv2m_pc; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mv2c00; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mv2c10; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mv2c20; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mv2c100; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_mvb; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_multisvbb1; */
   /* vector<double>  *AntiKt4EMTopoJets_jet_multisvbb2; */
   /* vector<float>   *AntiKt4EMTopoJets_IP2D_jet_ipxd_pb; */
   /* vector<float>   *AntiKt4EMTopoJets_IP2D_jet_ipxd_pc; */
   /* vector<float>   *AntiKt4EMTopoJets_IP2D_jet_ipxd_pu; */
   /* vector<double>  *AntiKt4EMTopoJets_IP2D_jet_ipxd_llr; */
   /* vector<int>     *AntiKt4EMTopoJets_IP2D_jet_ipxd_ntrk; */
   /* vector<float>   *AntiKt4EMTopoJets_IP3D_jet_ipxd_pb; */
   /* vector<float>   *AntiKt4EMTopoJets_IP3D_jet_ipxd_pc; */
   /* vector<float>   *AntiKt4EMTopoJets_IP3D_jet_ipxd_pu; */
   /* vector<double>  *AntiKt4EMTopoJets_IP3D_jet_ipxd_llr; */
   /* vector<int>     *AntiKt4EMTopoJets_IP3D_jet_ipxd_ntrk; */

   /* vector<int>     *AntiKt4LCTopoJets_SV1_jet_sv1_ntrkv; */
   /* vector<int>     *AntiKt4LCTopoJets_SV1_jet_sv1_n2t; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_m; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_efc; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_normdist; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_sig3d; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_pb; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_pc; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_pu; */
   /* vector<double>  *AntiKt4LCTopoJets_SV1_jet_sv1_llr; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_vtx_x; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_vtx_y; */
   /* vector<float>   *AntiKt4LCTopoJets_SV1_jet_sv1_vtx_z; */
   /* Int_t           AntiKt4LCTopoJets_njets; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_pt; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_eta; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_phi; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_E; */
   /* vector<int>     *AntiKt4LCTopoJets_jet_cleaning; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jvf; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jvt; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_cpt; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_ceta; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_cphi; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_cE; */
   /* vector<int>     *AntiKt4LCTopoJets_jet_truthflav; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jf_pb; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jf_pc; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jf_pu; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_jf_llr; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jf_m; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jf_efc; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jf_deta; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jf_dphi; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jf_ntrkAtVx; */
   /* vector<int>     *AntiKt4LCTopoJets_jet_jf_nvtx; */
   /* vector<int>     *AntiKt4LCTopoJets_jet_jf_sig3d; */
   /* vector<int>     *AntiKt4LCTopoJets_jet_jf_nvtx1t; */
   /* vector<int>     *AntiKt4LCTopoJets_jet_jf_n2t; */
   /* vector<vector<float> > *AntiKt4LCTopoJets_jet_jf_chi2; */
   /* vector<vector<float> > *AntiKt4LCTopoJets_jet_jf_ndf; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jfcombnn_pb; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jfcombnn_pc; */
   /* vector<float>   *AntiKt4LCTopoJets_jet_jfcombnn_pu; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_jfcombnn_llr; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mv1; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mv1c; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mv2m_pb; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mv2m_pu; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mv2m_pc; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mv2c00; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mv2c10; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mv2c20; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mv2c100; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_mvb; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_multisvbb1; */
   /* vector<double>  *AntiKt4LCTopoJets_jet_multisvbb2; */
   /* vector<float>   *AntiKt4LCTopoJets_IP2D_jet_ipxd_pb; */
   /* vector<float>   *AntiKt4LCTopoJets_IP2D_jet_ipxd_pc; */
   /* vector<float>   *AntiKt4LCTopoJets_IP2D_jet_ipxd_pu; */
   /* vector<double>  *AntiKt4LCTopoJets_IP2D_jet_ipxd_llr; */
   /* vector<int>     *AntiKt4LCTopoJets_IP2D_jet_ipxd_ntrk; */
   /* vector<float>   *AntiKt4LCTopoJets_IP3D_jet_ipxd_pb; */
   /* vector<float>   *AntiKt4LCTopoJets_IP3D_jet_ipxd_pc; */
   /* vector<float>   *AntiKt4LCTopoJets_IP3D_jet_ipxd_pu; */
   /* vector<double>  *AntiKt4LCTopoJets_IP3D_jet_ipxd_llr; */
   /* vector<int>     *AntiKt4LCTopoJets_IP3D_jet_ipxd_ntrk; */
   Int_t           runnb;
   Int_t           eventnb;
   Int_t           mcchan;
   Double_t        mcwg;
   Int_t           nPV;
   Double_t        avgmu;
   Double_t        PVx;
   Double_t        PVy;
   Double_t        PVz;

   // List of branches
   TBranch        *b_jet_SV1_jet_sv1_ntrkv;   //!
   TBranch        *b_jet_SV1_jet_sv1_n2t;   //!
   TBranch        *b_jet_SV1_jet_sv1_m;   //!
   TBranch        *b_jet_SV1_jet_sv1_efc;   //!
   TBranch        *b_jet_SV1_jet_sv1_normdist;   //!
   TBranch        *b_jet_SV1_jet_sv1_sig3d;   //!
   TBranch        *b_jet_SV1_jet_sv1_pb;   //!
   TBranch        *b_jet_SV1_jet_sv1_pc;   //!
   TBranch        *b_jet_SV1_jet_sv1_pu;   //!
   TBranch        *b_jet_SV1_jet_sv1_llr;   //!
   TBranch        *b_jet_SV1_jet_sv1_vtx_x;   //!
   TBranch        *b_jet_SV1_jet_sv1_vtx_y;   //!
   TBranch        *b_jet_SV1_jet_sv1_vtx_z;   //!
   TBranch        *b_jet_njets;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_cleaning;   //!
   TBranch        *b_jet_truthMatch;   //!
   TBranch        *b_jet_truth_pt;   //!
   TBranch        *b_jet_jvf;   //!
   TBranch        *b_jet_jvt;   //!
   TBranch        *b_jet_cpt;   //!
   TBranch        *b_jet_ceta;   //!
   TBranch        *b_jet_cphi;   //!
   TBranch        *b_jet_cE;   //!
   TBranch        *b_jet_truthflav;   //!
   TBranch        *b_jet_truthflavExCHad;   //!
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
   TBranch        *b_jet_mv1;   //!
   TBranch        *b_jet_mv1c;   //!
   TBranch        *b_jet_mv2m_pb;   //!
   TBranch        *b_jet_mv2m_pu;   //!
   TBranch        *b_jet_mv2m_pc;   //!
   TBranch        *b_jet_mv2c00;   //!
   TBranch        *b_jet_mv2c10;   //!
   TBranch        *b_jet_mv2c20;   //!
   TBranch        *b_jet_mv2c100;   //!
   TBranch        *b_jet_mvb;   //!
   TBranch        *b_jet_multisvbb1;   //!
   TBranch        *b_jet_multisvbb2;   //!
   TBranch        *b_jet_IP2D_jet_ipxd_pb;   //!
   TBranch        *b_jet_IP2D_jet_ipxd_pc;   //!
   TBranch        *b_jet_IP2D_jet_ipxd_pu;   //!
   TBranch        *b_jet_IP2D_jet_ipxd_llr;   //!
   TBranch        *b_jet_IP2D_jet_ipxd_ntrk;   //!
   TBranch        *b_jet_IP3D_jet_ipxd_pb;   //!
   TBranch        *b_jet_IP3D_jet_ipxd_pc;   //!
   TBranch        *b_jet_IP3D_jet_ipxd_pu;   //!
   TBranch        *b_jet_IP3D_jet_ipxd_llr;   //!
   TBranch        *b_jet_IP3D_jet_ipxd_ntrk;   //!

   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_ntrkv;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_n2t;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_m;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_efc;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_normdist;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_sig3d;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_pb;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_pc;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_pu;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_llr;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_vtx_x;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_vtx_y;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_SV1_jet_sv1_vtx_z;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_njets;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_pt;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_eta;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_phi;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_E;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_cleaning;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jvf;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jvt;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_cpt;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_ceta;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_cphi;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_cE;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_truthflav;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_pb;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_pc;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_pu;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_llr;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_m;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_efc;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_deta;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_dphi;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_ntrkAtVx;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_nvtx;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_sig3d;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_nvtx1t;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_n2t;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_chi2;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jf_ndf;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jfcombnn_pb;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jfcombnn_pc;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jfcombnn_pu;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_jfcombnn_llr;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mv1;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mv1c;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mv2m_pb;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mv2m_pu;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mv2m_pc;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mv2c00;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mv2c10;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mv2c20;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mv2c100;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_mvb;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_multisvbb1;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_jet_multisvbb2;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP2D_jet_ipxd_pb;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP2D_jet_ipxd_pc;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP2D_jet_ipxd_pu;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP2D_jet_ipxd_llr;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP2D_jet_ipxd_ntrk;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP3D_jet_ipxd_pb;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP3D_jet_ipxd_pc;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP3D_jet_ipxd_pu;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP3D_jet_ipxd_llr;   //! */
   /* TBranch        *b_AntiKt4EMTopoJets_IP3D_jet_ipxd_ntrk;   //! */

   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_ntrkv;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_n2t;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_m;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_efc;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_normdist;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_sig3d;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_pb;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_pc;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_pu;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_llr;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_vtx_x;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_vtx_y;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_SV1_jet_sv1_vtx_z;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_njets;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_pt;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_eta;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_phi;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_E;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_cleaning;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jvf;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jvt;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_cpt;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_ceta;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_cphi;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_cE;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_truthflav;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_pb;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_pc;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_pu;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_llr;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_m;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_efc;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_deta;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_dphi;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_ntrkAtVx;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_nvtx;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_sig3d;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_nvtx1t;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_n2t;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_chi2;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jf_ndf;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jfcombnn_pb;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jfcombnn_pc;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jfcombnn_pu;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_jfcombnn_llr;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mv1;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mv1c;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mv2m_pb;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mv2m_pu;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mv2m_pc;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mv2c00;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mv2c10;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mv2c20;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mv2c100;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_mvb;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_multisvbb1;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_jet_multisvbb2;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP2D_jet_ipxd_pb;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP2D_jet_ipxd_pc;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP2D_jet_ipxd_pu;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP2D_jet_ipxd_llr;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP2D_jet_ipxd_ntrk;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP3D_jet_ipxd_pb;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP3D_jet_ipxd_pc;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP3D_jet_ipxd_pu;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP3D_jet_ipxd_llr;   //! */
   /* TBranch        *b_AntiKt4LCTopoJets_IP3D_jet_ipxd_ntrk;   //! */

   TBranch        *b_runnb;   //!
   TBranch        *b_eventnb;   //!
   TBranch        *b_mcchan;   //!
   TBranch        *b_mcwg;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_avgmu;   //!
   TBranch        *b_PVx;   //!
   TBranch        *b_PVy;   //!
   TBranch        *b_PVz;   //!

   TBranch *b_jet_width; //!
   TBranch *b_jet_n_trk_sigd0cut; //!
   TBranch *b_jet_trk3_d0sig; //!
   TBranch *b_jet_trk3_z0sig; //!
   TBranch *b_jet_sv_scaled_efc; //!
   TBranch *b_jet_jf_scaled_efc; //!

   bTagG(TTree *tree=0,TString jetCollName="AntiKt4EMTopoJets");
   virtual ~bTagG();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree,TString jetCollName);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef bTagG_cxx
bTagG::bTagG(TTree *tree,TString jetCollName) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("flavntuple_test.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("flavntuple_test.root");
      }
      f->GetObject("bTag",tree);

   }
   Init(tree,jetCollName);
}

bTagG::~bTagG()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t bTagG::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t bTagG::LoadTree(Long64_t entry)
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

void bTagG::Init(TTree *tree,TString jetCollName)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jet_SV1_jet_sv1_ntrkv = 0;
   jet_SV1_jet_sv1_n2t = 0;
   jet_SV1_jet_sv1_m = 0;
   jet_SV1_jet_sv1_efc = 0;
   jet_SV1_jet_sv1_normdist = 0;
   jet_SV1_jet_sv1_sig3d = 0;
   jet_SV1_jet_sv1_pb = 0;
   jet_SV1_jet_sv1_pc = 0;
   jet_SV1_jet_sv1_pu = 0;
   jet_SV1_jet_sv1_llr = 0;
   jet_SV1_jet_sv1_vtx_x = 0;
   jet_SV1_jet_sv1_vtx_y = 0;
   jet_SV1_jet_sv1_vtx_z = 0;
   jet_pt = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_E = 0;
   jet_cleaning = 0;
   jet_truthMatch = 0;
   jet_truth_pt = 0;
   jet_jvf = 0;
   jet_jvt = 0;
   jet_cpt = 0;
   jet_ceta = 0;
   jet_cphi = 0;
   jet_cE = 0;
   jet_truthflav = 0;
   jet_truthflavExCHad = 0;
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
   jet_mv1 = 0;
   jet_mv1c = 0;
   jet_mv2m_pb = 0;
   jet_mv2m_pu = 0;
   jet_mv2m_pc = 0;
   jet_mv2c00 = 0;
   jet_mv2c10 = 0;
   jet_mv2c20 = 0;
   jet_mv2c100 = 0;
   jet_mvb = 0;
   jet_multisvbb1 = 0;
   jet_multisvbb2 = 0;
   jet_IP2D_jet_ipxd_pb = 0;
   jet_IP2D_jet_ipxd_pc = 0;
   jet_IP2D_jet_ipxd_pu = 0;
   jet_IP2D_jet_ipxd_llr = 0;
   jet_IP2D_jet_ipxd_ntrk = 0;
   jet_IP3D_jet_ipxd_pb = 0;
   jet_IP3D_jet_ipxd_pc = 0;
   jet_IP3D_jet_ipxd_pu = 0;
   jet_IP3D_jet_ipxd_llr = 0;
   jet_IP3D_jet_ipxd_ntrk = 0;

   jet_width = 0;
   jet_n_trk_sigd0cut = 0;
   jet_trk3_d0sig = 0;
   jet_trk3_z0sig = 0;
   jet_sv_scaled_efc = 0;
   jet_jf_scaled_efc = 0;

   /* AntiKt4EMTopoJets_SV1_jet_sv1_ntrkv = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_n2t = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_m = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_efc = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_normdist = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_sig3d = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_pb = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_pc = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_pu = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_llr = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_vtx_x = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_vtx_y = 0; */
   /* AntiKt4EMTopoJets_SV1_jet_sv1_vtx_z = 0; */
   /* AntiKt4EMTopoJets_jet_pt = 0; */
   /* AntiKt4EMTopoJets_jet_eta = 0; */
   /* AntiKt4EMTopoJets_jet_phi = 0; */
   /* AntiKt4EMTopoJets_jet_E = 0; */
   /* AntiKt4EMTopoJets_jet_cleaning = 0; */
   /* AntiKt4EMTopoJets_jet_jvf = 0; */
   /* AntiKt4EMTopoJets_jet_jvt = 0; */
   /* AntiKt4EMTopoJets_jet_cpt = 0; */
   /* AntiKt4EMTopoJets_jet_ceta = 0; */
   /* AntiKt4EMTopoJets_jet_cphi = 0; */
   /* AntiKt4EMTopoJets_jet_cE = 0; */
   /* AntiKt4EMTopoJets_jet_truthflav = 0; */
   /* AntiKt4EMTopoJets_jet_jf_pb = 0; */
   /* AntiKt4EMTopoJets_jet_jf_pc = 0; */
   /* AntiKt4EMTopoJets_jet_jf_pu = 0; */
   /* AntiKt4EMTopoJets_jet_jf_llr = 0; */
   /* AntiKt4EMTopoJets_jet_jf_m = 0; */
   /* AntiKt4EMTopoJets_jet_jf_efc = 0; */
   /* AntiKt4EMTopoJets_jet_jf_deta = 0; */
   /* AntiKt4EMTopoJets_jet_jf_dphi = 0; */
   /* AntiKt4EMTopoJets_jet_jf_ntrkAtVx = 0; */
   /* AntiKt4EMTopoJets_jet_jf_nvtx = 0; */
   /* AntiKt4EMTopoJets_jet_jf_sig3d = 0; */
   /* AntiKt4EMTopoJets_jet_jf_nvtx1t = 0; */
   /* AntiKt4EMTopoJets_jet_jf_n2t = 0; */
   /* AntiKt4EMTopoJets_jet_jf_chi2 = 0; */
   /* AntiKt4EMTopoJets_jet_jf_ndf = 0; */
   /* AntiKt4EMTopoJets_jet_jfcombnn_pb = 0; */
   /* AntiKt4EMTopoJets_jet_jfcombnn_pc = 0; */
   /* AntiKt4EMTopoJets_jet_jfcombnn_pu = 0; */
   /* AntiKt4EMTopoJets_jet_jfcombnn_llr = 0; */
   /* AntiKt4EMTopoJets_jet_mv1 = 0; */
   /* AntiKt4EMTopoJets_jet_mv1c = 0; */
   /* AntiKt4EMTopoJets_jet_mv2m_pb = 0; */
   /* AntiKt4EMTopoJets_jet_mv2m_pu = 0; */
   /* AntiKt4EMTopoJets_jet_mv2m_pc = 0; */
   /* AntiKt4EMTopoJets_jet_mv2c00 = 0; */
   /* AntiKt4EMTopoJets_jet_mv2c10 = 0; */
   /* AntiKt4EMTopoJets_jet_mv2c20 = 0; */
   /* AntiKt4EMTopoJets_jet_mv2c100 = 0; */
   /* AntiKt4EMTopoJets_jet_mvb = 0; */
   /* AntiKt4EMTopoJets_jet_multisvbb1 = 0; */
   /* AntiKt4EMTopoJets_jet_multisvbb2 = 0; */
   /* AntiKt4EMTopoJets_IP2D_jet_ipxd_pb = 0; */
   /* AntiKt4EMTopoJets_IP2D_jet_ipxd_pc = 0; */
   /* AntiKt4EMTopoJets_IP2D_jet_ipxd_pu = 0; */
   /* AntiKt4EMTopoJets_IP2D_jet_ipxd_llr = 0; */
   /* AntiKt4EMTopoJets_IP2D_jet_ipxd_ntrk = 0; */
   /* AntiKt4EMTopoJets_IP3D_jet_ipxd_pb = 0; */
   /* AntiKt4EMTopoJets_IP3D_jet_ipxd_pc = 0; */
   /* AntiKt4EMTopoJets_IP3D_jet_ipxd_pu = 0; */
   /* AntiKt4EMTopoJets_IP3D_jet_ipxd_llr = 0; */
   /* AntiKt4EMTopoJets_IP3D_jet_ipxd_ntrk = 0; */

   /* AntiKt4LCTopoJets_SV1_jet_sv1_ntrkv = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_n2t = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_m = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_efc = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_normdist = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_sig3d = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_pb = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_pc = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_pu = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_llr = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_vtx_x = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_vtx_y = 0; */
   /* AntiKt4LCTopoJets_SV1_jet_sv1_vtx_z = 0; */
   /* AntiKt4LCTopoJets_jet_pt = 0; */
   /* AntiKt4LCTopoJets_jet_eta = 0; */
   /* AntiKt4LCTopoJets_jet_phi = 0; */
   /* AntiKt4LCTopoJets_jet_E = 0; */
   /* AntiKt4LCTopoJets_jet_cleaning = 0; */
   /* AntiKt4LCTopoJets_jet_jvf = 0; */
   /* AntiKt4LCTopoJets_jet_jvt = 0; */
   /* AntiKt4LCTopoJets_jet_cpt = 0; */
   /* AntiKt4LCTopoJets_jet_ceta = 0; */
   /* AntiKt4LCTopoJets_jet_cphi = 0; */
   /* AntiKt4LCTopoJets_jet_cE = 0; */
   /* AntiKt4LCTopoJets_jet_truthflav = 0; */
   /* AntiKt4LCTopoJets_jet_jf_pb = 0; */
   /* AntiKt4LCTopoJets_jet_jf_pc = 0; */
   /* AntiKt4LCTopoJets_jet_jf_pu = 0; */
   /* AntiKt4LCTopoJets_jet_jf_llr = 0; */
   /* AntiKt4LCTopoJets_jet_jf_m = 0; */
   /* AntiKt4LCTopoJets_jet_jf_efc = 0; */
   /* AntiKt4LCTopoJets_jet_jf_deta = 0; */
   /* AntiKt4LCTopoJets_jet_jf_dphi = 0; */
   /* AntiKt4LCTopoJets_jet_jf_ntrkAtVx = 0; */
   /* AntiKt4LCTopoJets_jet_jf_nvtx = 0; */
   /* AntiKt4LCTopoJets_jet_jf_sig3d = 0; */
   /* AntiKt4LCTopoJets_jet_jf_nvtx1t = 0; */
   /* AntiKt4LCTopoJets_jet_jf_n2t = 0; */
   /* AntiKt4LCTopoJets_jet_jf_chi2 = 0; */
   /* AntiKt4LCTopoJets_jet_jf_ndf = 0; */
   /* AntiKt4LCTopoJets_jet_jfcombnn_pb = 0; */
   /* AntiKt4LCTopoJets_jet_jfcombnn_pc = 0; */
   /* AntiKt4LCTopoJets_jet_jfcombnn_pu = 0; */
   /* AntiKt4LCTopoJets_jet_jfcombnn_llr = 0; */
   /* AntiKt4LCTopoJets_jet_mv1 = 0; */
   /* AntiKt4LCTopoJets_jet_mv1c = 0; */
   /* AntiKt4LCTopoJets_jet_mv2m_pb = 0; */
   /* AntiKt4LCTopoJets_jet_mv2m_pu = 0; */
   /* AntiKt4LCTopoJets_jet_mv2m_pc = 0; */
   /* AntiKt4LCTopoJets_jet_mv2c00 = 0; */
   /* AntiKt4LCTopoJets_jet_mv2c10 = 0; */
   /* AntiKt4LCTopoJets_jet_mv2c20 = 0; */
   /* AntiKt4LCTopoJets_jet_mv2c100 = 0; */
   /* AntiKt4LCTopoJets_jet_mvb = 0; */
   /* AntiKt4LCTopoJets_jet_multisvbb1 = 0; */
   /* AntiKt4LCTopoJets_jet_multisvbb2 = 0; */
   /* AntiKt4LCTopoJets_IP2D_jet_ipxd_pb = 0; */
   /* AntiKt4LCTopoJets_IP2D_jet_ipxd_pc = 0; */
   /* AntiKt4LCTopoJets_IP2D_jet_ipxd_pu = 0; */
   /* AntiKt4LCTopoJets_IP2D_jet_ipxd_llr = 0; */
   /* AntiKt4LCTopoJets_IP2D_jet_ipxd_ntrk = 0; */
   /* AntiKt4LCTopoJets_IP3D_jet_ipxd_pb = 0; */
   /* AntiKt4LCTopoJets_IP3D_jet_ipxd_pc = 0; */
   /* AntiKt4LCTopoJets_IP3D_jet_ipxd_pu = 0; */
   /* AntiKt4LCTopoJets_IP3D_jet_ipxd_llr = 0; */
   /* AntiKt4LCTopoJets_IP3D_jet_ipxd_ntrk = 0; */
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_ntrkv", &jet_SV1_jet_sv1_ntrkv, &b_jet_SV1_jet_sv1_ntrkv);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_n2t", &jet_SV1_jet_sv1_n2t, &b_jet_SV1_jet_sv1_n2t);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_m", &jet_SV1_jet_sv1_m, &b_jet_SV1_jet_sv1_m);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_efc", &jet_SV1_jet_sv1_efc, &b_jet_SV1_jet_sv1_efc);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_normdist", &jet_SV1_jet_sv1_normdist, &b_jet_SV1_jet_sv1_normdist);
   //fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_sig3d", &jet_SV1_jet_sv1_sig3d, &b_jet_SV1_jet_sv1_sig3d);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_pb", &jet_SV1_jet_sv1_pb, &b_jet_SV1_jet_sv1_pb);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_pc", &jet_SV1_jet_sv1_pc, &b_jet_SV1_jet_sv1_pc);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_pu", &jet_SV1_jet_sv1_pu, &b_jet_SV1_jet_sv1_pu);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_llr", &jet_SV1_jet_sv1_llr, &b_jet_SV1_jet_sv1_llr);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_vtx_x", &jet_SV1_jet_sv1_vtx_x, &b_jet_SV1_jet_sv1_vtx_x);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_vtx_y", &jet_SV1_jet_sv1_vtx_y, &b_jet_SV1_jet_sv1_vtx_y);
   fChain->SetBranchAddress(jetCollName+"_SV1_jet_sv1_vtx_z", &jet_SV1_jet_sv1_vtx_z, &b_jet_SV1_jet_sv1_vtx_z);
   fChain->SetBranchAddress(jetCollName+"_njets", &jet_njets, &b_jet_njets);
   fChain->SetBranchAddress(jetCollName+"_jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress(jetCollName+"_jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress(jetCollName+"_jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress(jetCollName+"_jet_E", &jet_E, &b_jet_E);
   fChain->SetBranchAddress(jetCollName+"_jet_cleaning", &jet_cleaning, &b_jet_cleaning);
   fChain->SetBranchAddress(jetCollName+"_jet_truthMatch", &jet_truthMatch, &b_jet_truthMatch);
   fChain->SetBranchAddress(jetCollName+"_jet_truth_pt", &jet_truth_pt, &b_jet_truth_pt);
   fChain->SetBranchAddress(jetCollName+"_jet_jvf", &jet_jvf, &b_jet_jvf);
   fChain->SetBranchAddress(jetCollName+"_jet_jvt", &jet_jvt, &b_jet_jvt);
   fChain->SetBranchAddress(jetCollName+"_jet_cpt", &jet_cpt, &b_jet_cpt);
   fChain->SetBranchAddress(jetCollName+"_jet_ceta", &jet_ceta, &b_jet_ceta);
   fChain->SetBranchAddress(jetCollName+"_jet_cphi", &jet_cphi, &b_jet_cphi);
   fChain->SetBranchAddress(jetCollName+"_jet_cE", &jet_cE, &b_jet_cE);
   fChain->SetBranchAddress(jetCollName+"_jet_truthflav", &jet_truthflav, &b_jet_truthflav);
   fChain->SetBranchAddress(jetCollName+"_jet_truthflavExCHad", &jet_truthflavExCHad, &b_jet_truthflavExCHad);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_pb", &jet_jf_pb, &b_jet_jf_pb);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_pc", &jet_jf_pc, &b_jet_jf_pc);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_pu", &jet_jf_pu, &b_jet_jf_pu);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_llr", &jet_jf_llr, &b_jet_jf_llr);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_m", &jet_jf_m, &b_jet_jf_m);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_efc", &jet_jf_efc, &b_jet_jf_efc);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_deta", &jet_jf_deta, &b_jet_jf_deta);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_dphi", &jet_jf_dphi, &b_jet_jf_dphi);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_ntrkAtVx", &jet_jf_ntrkAtVx, &b_jet_jf_ntrkAtVx);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_nvtx", &jet_jf_nvtx, &b_jet_jf_nvtx);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_sig3d", &jet_jf_sig3d, &b_jet_jf_sig3d);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_nvtx1t", &jet_jf_nvtx1t, &b_jet_jf_nvtx1t);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_n2t", &jet_jf_n2t, &b_jet_jf_n2t);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_chi2", &jet_jf_chi2, &b_jet_jf_chi2);
   fChain->SetBranchAddress(jetCollName+"_jet_jf_ndf", &jet_jf_ndf, &b_jet_jf_ndf);
   fChain->SetBranchAddress(jetCollName+"_jet_jfcombnn_pb", &jet_jfcombnn_pb, &b_jet_jfcombnn_pb);
   fChain->SetBranchAddress(jetCollName+"_jet_jfcombnn_pc", &jet_jfcombnn_pc, &b_jet_jfcombnn_pc);
   fChain->SetBranchAddress(jetCollName+"_jet_jfcombnn_pu", &jet_jfcombnn_pu, &b_jet_jfcombnn_pu);
   fChain->SetBranchAddress(jetCollName+"_jet_jfcombnn_llr", &jet_jfcombnn_llr, &b_jet_jfcombnn_llr);
   fChain->SetBranchAddress(jetCollName+"_jet_mv1", &jet_mv1, &b_jet_mv1);
   fChain->SetBranchAddress(jetCollName+"_jet_mv1c", &jet_mv1c, &b_jet_mv1c);
   fChain->SetBranchAddress(jetCollName+"_jet_mv2m_pb", &jet_mv2m_pb, &b_jet_mv2m_pb);
   fChain->SetBranchAddress(jetCollName+"_jet_mv2m_pu", &jet_mv2m_pu, &b_jet_mv2m_pu);
   fChain->SetBranchAddress(jetCollName+"_jet_mv2m_pc", &jet_mv2m_pc, &b_jet_mv2m_pc);
   fChain->SetBranchAddress(jetCollName+"_jet_mv2c00", &jet_mv2c00, &b_jet_mv2c00);
   fChain->SetBranchAddress(jetCollName+"_jet_mv2c10", &jet_mv2c10, &b_jet_mv2c10);
   fChain->SetBranchAddress(jetCollName+"_jet_mv2c20", &jet_mv2c20, &b_jet_mv2c20);
   fChain->SetBranchAddress(jetCollName+"_jet_mv2c100", &jet_mv2c100, &b_jet_mv2c100);
   fChain->SetBranchAddress(jetCollName+"_jet_mvb", &jet_mvb, &b_jet_mvb);
   fChain->SetBranchAddress(jetCollName+"_jet_multisvbb1", &jet_multisvbb1, &b_jet_multisvbb1);
   fChain->SetBranchAddress(jetCollName+"_jet_multisvbb2", &jet_multisvbb2, &b_jet_multisvbb2);
   fChain->SetBranchAddress(jetCollName+"_IP2D_jet_ipxd_pb", &jet_IP2D_jet_ipxd_pb, &b_jet_IP2D_jet_ipxd_pb);
   fChain->SetBranchAddress(jetCollName+"_IP2D_jet_ipxd_pc", &jet_IP2D_jet_ipxd_pc, &b_jet_IP2D_jet_ipxd_pc);
   fChain->SetBranchAddress(jetCollName+"_IP2D_jet_ipxd_pu", &jet_IP2D_jet_ipxd_pu, &b_jet_IP2D_jet_ipxd_pu);
   fChain->SetBranchAddress(jetCollName+"_IP2D_jet_ipxd_llr", &jet_IP2D_jet_ipxd_llr, &b_jet_IP2D_jet_ipxd_llr);
   fChain->SetBranchAddress(jetCollName+"_IP2D_jet_ipxd_ntrk", &jet_IP2D_jet_ipxd_ntrk, &b_jet_IP2D_jet_ipxd_ntrk);
   fChain->SetBranchAddress(jetCollName+"_IP3D_jet_ipxd_pb", &jet_IP3D_jet_ipxd_pb, &b_jet_IP3D_jet_ipxd_pb);
   fChain->SetBranchAddress(jetCollName+"_IP3D_jet_ipxd_pc", &jet_IP3D_jet_ipxd_pc, &b_jet_IP3D_jet_ipxd_pc);
   fChain->SetBranchAddress(jetCollName+"_IP3D_jet_ipxd_pu", &jet_IP3D_jet_ipxd_pu, &b_jet_IP3D_jet_ipxd_pu);
   fChain->SetBranchAddress(jetCollName+"_IP3D_jet_ipxd_llr", &jet_IP3D_jet_ipxd_llr, &b_jet_IP3D_jet_ipxd_llr);
   fChain->SetBranchAddress(jetCollName+"_IP3D_jet_ipxd_ntrk", &jet_IP3D_jet_ipxd_ntrk, &b_jet_IP3D_jet_ipxd_ntrk);

   fChain->SetBranchAddress(jetCollName + "_jet_width", &jet_width, &b_jet_width);
   fChain->SetBranchAddress(jetCollName + "_jet_n_trk_sigd0cut", &jet_n_trk_sigd0cut, &b_jet_n_trk_sigd0cut);
   fChain->SetBranchAddress(jetCollName + "_jet_trk3_d0sig", &jet_trk3_d0sig, &b_jet_trk3_d0sig);
   fChain->SetBranchAddress(jetCollName + "_jet_trk3_z0sig", &jet_trk3_z0sig, &b_jet_trk3_z0sig);
   fChain->SetBranchAddress(jetCollName + "_jet_sv_scaled_efc", &jet_sv_scaled_efc, &b_jet_sv_scaled_efc);
   fChain->SetBranchAddress(jetCollName + "_jet_jf_scaled_efc", &jet_jf_scaled_efc, &b_jet_jf_scaled_efc);

   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_ntrkv", &AntiKt4EMTopoJets_SV1_jet_sv1_ntrkv, &b_AntiKt4EMTopoJets_SV1_jet_sv1_ntrkv); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_n2t", &AntiKt4EMTopoJets_SV1_jet_sv1_n2t, &b_AntiKt4EMTopoJets_SV1_jet_sv1_n2t); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_m", &AntiKt4EMTopoJets_SV1_jet_sv1_m, &b_AntiKt4EMTopoJets_SV1_jet_sv1_m); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_efc", &AntiKt4EMTopoJets_SV1_jet_sv1_efc, &b_AntiKt4EMTopoJets_SV1_jet_sv1_efc); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_normdist", &AntiKt4EMTopoJets_SV1_jet_sv1_normdist, &b_AntiKt4EMTopoJets_SV1_jet_sv1_normdist); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_sig3d", &AntiKt4EMTopoJets_SV1_jet_sv1_sig3d, &b_AntiKt4EMTopoJets_SV1_jet_sv1_sig3d); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_pb", &AntiKt4EMTopoJets_SV1_jet_sv1_pb, &b_AntiKt4EMTopoJets_SV1_jet_sv1_pb); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_pc", &AntiKt4EMTopoJets_SV1_jet_sv1_pc, &b_AntiKt4EMTopoJets_SV1_jet_sv1_pc); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_pu", &AntiKt4EMTopoJets_SV1_jet_sv1_pu, &b_AntiKt4EMTopoJets_SV1_jet_sv1_pu); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_llr", &AntiKt4EMTopoJets_SV1_jet_sv1_llr, &b_AntiKt4EMTopoJets_SV1_jet_sv1_llr); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_vtx_x", &AntiKt4EMTopoJets_SV1_jet_sv1_vtx_x, &b_AntiKt4EMTopoJets_SV1_jet_sv1_vtx_x); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_vtx_y", &AntiKt4EMTopoJets_SV1_jet_sv1_vtx_y, &b_AntiKt4EMTopoJets_SV1_jet_sv1_vtx_y); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_SV1_jet_sv1_vtx_z", &AntiKt4EMTopoJets_SV1_jet_sv1_vtx_z, &b_AntiKt4EMTopoJets_SV1_jet_sv1_vtx_z); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_njets", &AntiKt4EMTopoJets_njets, &b_AntiKt4EMTopoJets_njets); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_pt", &AntiKt4EMTopoJets_jet_pt, &b_AntiKt4EMTopoJets_jet_pt); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_eta", &AntiKt4EMTopoJets_jet_eta, &b_AntiKt4EMTopoJets_jet_eta); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_phi", &AntiKt4EMTopoJets_jet_phi, &b_AntiKt4EMTopoJets_jet_phi); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_E", &AntiKt4EMTopoJets_jet_E, &b_AntiKt4EMTopoJets_jet_E); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_cleaning", &AntiKt4EMTopoJets_jet_cleaning, &b_AntiKt4EMTopoJets_jet_cleaning); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jvf", &AntiKt4EMTopoJets_jet_jvf, &b_AntiKt4EMTopoJets_jet_jvf); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jvt", &AntiKt4EMTopoJets_jet_jvt, &b_AntiKt4EMTopoJets_jet_jvt); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_cpt", &AntiKt4EMTopoJets_jet_cpt, &b_AntiKt4EMTopoJets_jet_cpt); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_ceta", &AntiKt4EMTopoJets_jet_ceta, &b_AntiKt4EMTopoJets_jet_ceta); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_cphi", &AntiKt4EMTopoJets_jet_cphi, &b_AntiKt4EMTopoJets_jet_cphi); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_cE", &AntiKt4EMTopoJets_jet_cE, &b_AntiKt4EMTopoJets_jet_cE); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_truthflav", &AntiKt4EMTopoJets_jet_truthflav, &b_AntiKt4EMTopoJets_jet_truthflav); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_pb", &AntiKt4EMTopoJets_jet_jf_pb, &b_AntiKt4EMTopoJets_jet_jf_pb); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_pc", &AntiKt4EMTopoJets_jet_jf_pc, &b_AntiKt4EMTopoJets_jet_jf_pc); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_pu", &AntiKt4EMTopoJets_jet_jf_pu, &b_AntiKt4EMTopoJets_jet_jf_pu); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_llr", &AntiKt4EMTopoJets_jet_jf_llr, &b_AntiKt4EMTopoJets_jet_jf_llr); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_m", &AntiKt4EMTopoJets_jet_jf_m, &b_AntiKt4EMTopoJets_jet_jf_m); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_efc", &AntiKt4EMTopoJets_jet_jf_efc, &b_AntiKt4EMTopoJets_jet_jf_efc); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_deta", &AntiKt4EMTopoJets_jet_jf_deta, &b_AntiKt4EMTopoJets_jet_jf_deta); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_dphi", &AntiKt4EMTopoJets_jet_jf_dphi, &b_AntiKt4EMTopoJets_jet_jf_dphi); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_ntrkAtVx", &AntiKt4EMTopoJets_jet_jf_ntrkAtVx, &b_AntiKt4EMTopoJets_jet_jf_ntrkAtVx); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_nvtx", &AntiKt4EMTopoJets_jet_jf_nvtx, &b_AntiKt4EMTopoJets_jet_jf_nvtx); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_sig3d", &AntiKt4EMTopoJets_jet_jf_sig3d, &b_AntiKt4EMTopoJets_jet_jf_sig3d); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_nvtx1t", &AntiKt4EMTopoJets_jet_jf_nvtx1t, &b_AntiKt4EMTopoJets_jet_jf_nvtx1t); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_n2t", &AntiKt4EMTopoJets_jet_jf_n2t, &b_AntiKt4EMTopoJets_jet_jf_n2t); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_chi2", &AntiKt4EMTopoJets_jet_jf_chi2, &b_AntiKt4EMTopoJets_jet_jf_chi2); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jf_ndf", &AntiKt4EMTopoJets_jet_jf_ndf, &b_AntiKt4EMTopoJets_jet_jf_ndf); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jfcombnn_pb", &AntiKt4EMTopoJets_jet_jfcombnn_pb, &b_AntiKt4EMTopoJets_jet_jfcombnn_pb); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jfcombnn_pc", &AntiKt4EMTopoJets_jet_jfcombnn_pc, &b_AntiKt4EMTopoJets_jet_jfcombnn_pc); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jfcombnn_pu", &AntiKt4EMTopoJets_jet_jfcombnn_pu, &b_AntiKt4EMTopoJets_jet_jfcombnn_pu); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_jfcombnn_llr", &AntiKt4EMTopoJets_jet_jfcombnn_llr, &b_AntiKt4EMTopoJets_jet_jfcombnn_llr); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mv1", &AntiKt4EMTopoJets_jet_mv1, &b_AntiKt4EMTopoJets_jet_mv1); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mv1c", &AntiKt4EMTopoJets_jet_mv1c, &b_AntiKt4EMTopoJets_jet_mv1c); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mv2m_pb", &AntiKt4EMTopoJets_jet_mv2m_pb, &b_AntiKt4EMTopoJets_jet_mv2m_pb); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mv2m_pu", &AntiKt4EMTopoJets_jet_mv2m_pu, &b_AntiKt4EMTopoJets_jet_mv2m_pu); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mv2m_pc", &AntiKt4EMTopoJets_jet_mv2m_pc, &b_AntiKt4EMTopoJets_jet_mv2m_pc); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mv2c00", &AntiKt4EMTopoJets_jet_mv2c00, &b_AntiKt4EMTopoJets_jet_mv2c00); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mv2c10", &AntiKt4EMTopoJets_jet_mv2c10, &b_AntiKt4EMTopoJets_jet_mv2c10); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mv2c20", &AntiKt4EMTopoJets_jet_mv2c20, &b_AntiKt4EMTopoJets_jet_mv2c20); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mv2c100", &AntiKt4EMTopoJets_jet_mv2c100, &b_AntiKt4EMTopoJets_jet_mv2c100); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_mvb", &AntiKt4EMTopoJets_jet_mvb, &b_AntiKt4EMTopoJets_jet_mvb); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_multisvbb1", &AntiKt4EMTopoJets_jet_multisvbb1, &b_AntiKt4EMTopoJets_jet_multisvbb1); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_jet_multisvbb2", &AntiKt4EMTopoJets_jet_multisvbb2, &b_AntiKt4EMTopoJets_jet_multisvbb2); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP2D_jet_ipxd_pb", &AntiKt4EMTopoJets_IP2D_jet_ipxd_pb, &b_AntiKt4EMTopoJets_IP2D_jet_ipxd_pb); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP2D_jet_ipxd_pc", &AntiKt4EMTopoJets_IP2D_jet_ipxd_pc, &b_AntiKt4EMTopoJets_IP2D_jet_ipxd_pc); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP2D_jet_ipxd_pu", &AntiKt4EMTopoJets_IP2D_jet_ipxd_pu, &b_AntiKt4EMTopoJets_IP2D_jet_ipxd_pu); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP2D_jet_ipxd_llr", &AntiKt4EMTopoJets_IP2D_jet_ipxd_llr, &b_AntiKt4EMTopoJets_IP2D_jet_ipxd_llr); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP2D_jet_ipxd_ntrk", &AntiKt4EMTopoJets_IP2D_jet_ipxd_ntrk, &b_AntiKt4EMTopoJets_IP2D_jet_ipxd_ntrk); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP3D_jet_ipxd_pb", &AntiKt4EMTopoJets_IP3D_jet_ipxd_pb, &b_AntiKt4EMTopoJets_IP3D_jet_ipxd_pb); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP3D_jet_ipxd_pc", &AntiKt4EMTopoJets_IP3D_jet_ipxd_pc, &b_AntiKt4EMTopoJets_IP3D_jet_ipxd_pc); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP3D_jet_ipxd_pu", &AntiKt4EMTopoJets_IP3D_jet_ipxd_pu, &b_AntiKt4EMTopoJets_IP3D_jet_ipxd_pu); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP3D_jet_ipxd_llr", &AntiKt4EMTopoJets_IP3D_jet_ipxd_llr, &b_AntiKt4EMTopoJets_IP3D_jet_ipxd_llr); */
   /* fChain->SetBranchAddress("AntiKt4EMTopoJets_IP3D_jet_ipxd_ntrk", &AntiKt4EMTopoJets_IP3D_jet_ipxd_ntrk, &b_AntiKt4EMTopoJets_IP3D_jet_ipxd_ntrk); */

   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_ntrkv", &AntiKt4LCTopoJets_SV1_jet_sv1_ntrkv, &b_AntiKt4LCTopoJets_SV1_jet_sv1_ntrkv); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_n2t", &AntiKt4LCTopoJets_SV1_jet_sv1_n2t, &b_AntiKt4LCTopoJets_SV1_jet_sv1_n2t); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_m", &AntiKt4LCTopoJets_SV1_jet_sv1_m, &b_AntiKt4LCTopoJets_SV1_jet_sv1_m); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_efc", &AntiKt4LCTopoJets_SV1_jet_sv1_efc, &b_AntiKt4LCTopoJets_SV1_jet_sv1_efc); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_normdist", &AntiKt4LCTopoJets_SV1_jet_sv1_normdist, &b_AntiKt4LCTopoJets_SV1_jet_sv1_normdist); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_sig3d", &AntiKt4LCTopoJets_SV1_jet_sv1_sig3d, &b_AntiKt4LCTopoJets_SV1_jet_sv1_sig3d); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_pb", &AntiKt4LCTopoJets_SV1_jet_sv1_pb, &b_AntiKt4LCTopoJets_SV1_jet_sv1_pb); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_pc", &AntiKt4LCTopoJets_SV1_jet_sv1_pc, &b_AntiKt4LCTopoJets_SV1_jet_sv1_pc); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_pu", &AntiKt4LCTopoJets_SV1_jet_sv1_pu, &b_AntiKt4LCTopoJets_SV1_jet_sv1_pu); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_llr", &AntiKt4LCTopoJets_SV1_jet_sv1_llr, &b_AntiKt4LCTopoJets_SV1_jet_sv1_llr); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_vtx_x", &AntiKt4LCTopoJets_SV1_jet_sv1_vtx_x, &b_AntiKt4LCTopoJets_SV1_jet_sv1_vtx_x); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_vtx_y", &AntiKt4LCTopoJets_SV1_jet_sv1_vtx_y, &b_AntiKt4LCTopoJets_SV1_jet_sv1_vtx_y); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_SV1_jet_sv1_vtx_z", &AntiKt4LCTopoJets_SV1_jet_sv1_vtx_z, &b_AntiKt4LCTopoJets_SV1_jet_sv1_vtx_z); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_njets", &AntiKt4LCTopoJets_njets, &b_AntiKt4LCTopoJets_njets); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_pt", &AntiKt4LCTopoJets_jet_pt, &b_AntiKt4LCTopoJets_jet_pt); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_eta", &AntiKt4LCTopoJets_jet_eta, &b_AntiKt4LCTopoJets_jet_eta); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_phi", &AntiKt4LCTopoJets_jet_phi, &b_AntiKt4LCTopoJets_jet_phi); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_E", &AntiKt4LCTopoJets_jet_E, &b_AntiKt4LCTopoJets_jet_E); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_cleaning", &AntiKt4LCTopoJets_jet_cleaning, &b_AntiKt4LCTopoJets_jet_cleaning); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jvf", &AntiKt4LCTopoJets_jet_jvf, &b_AntiKt4LCTopoJets_jet_jvf); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jvt", &AntiKt4LCTopoJets_jet_jvt, &b_AntiKt4LCTopoJets_jet_jvt); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_cpt", &AntiKt4LCTopoJets_jet_cpt, &b_AntiKt4LCTopoJets_jet_cpt); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_ceta", &AntiKt4LCTopoJets_jet_ceta, &b_AntiKt4LCTopoJets_jet_ceta); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_cphi", &AntiKt4LCTopoJets_jet_cphi, &b_AntiKt4LCTopoJets_jet_cphi); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_cE", &AntiKt4LCTopoJets_jet_cE, &b_AntiKt4LCTopoJets_jet_cE); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_truthflav", &AntiKt4LCTopoJets_jet_truthflav, &b_AntiKt4LCTopoJets_jet_truthflav); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_pb", &AntiKt4LCTopoJets_jet_jf_pb, &b_AntiKt4LCTopoJets_jet_jf_pb); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_pc", &AntiKt4LCTopoJets_jet_jf_pc, &b_AntiKt4LCTopoJets_jet_jf_pc); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_pu", &AntiKt4LCTopoJets_jet_jf_pu, &b_AntiKt4LCTopoJets_jet_jf_pu); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_llr", &AntiKt4LCTopoJets_jet_jf_llr, &b_AntiKt4LCTopoJets_jet_jf_llr); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_m", &AntiKt4LCTopoJets_jet_jf_m, &b_AntiKt4LCTopoJets_jet_jf_m); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_efc", &AntiKt4LCTopoJets_jet_jf_efc, &b_AntiKt4LCTopoJets_jet_jf_efc); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_deta", &AntiKt4LCTopoJets_jet_jf_deta, &b_AntiKt4LCTopoJets_jet_jf_deta); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_dphi", &AntiKt4LCTopoJets_jet_jf_dphi, &b_AntiKt4LCTopoJets_jet_jf_dphi); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_ntrkAtVx", &AntiKt4LCTopoJets_jet_jf_ntrkAtVx, &b_AntiKt4LCTopoJets_jet_jf_ntrkAtVx); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_nvtx", &AntiKt4LCTopoJets_jet_jf_nvtx, &b_AntiKt4LCTopoJets_jet_jf_nvtx); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_sig3d", &AntiKt4LCTopoJets_jet_jf_sig3d, &b_AntiKt4LCTopoJets_jet_jf_sig3d); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_nvtx1t", &AntiKt4LCTopoJets_jet_jf_nvtx1t, &b_AntiKt4LCTopoJets_jet_jf_nvtx1t); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_n2t", &AntiKt4LCTopoJets_jet_jf_n2t, &b_AntiKt4LCTopoJets_jet_jf_n2t); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_chi2", &AntiKt4LCTopoJets_jet_jf_chi2, &b_AntiKt4LCTopoJets_jet_jf_chi2); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jf_ndf", &AntiKt4LCTopoJets_jet_jf_ndf, &b_AntiKt4LCTopoJets_jet_jf_ndf); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jfcombnn_pb", &AntiKt4LCTopoJets_jet_jfcombnn_pb, &b_AntiKt4LCTopoJets_jet_jfcombnn_pb); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jfcombnn_pc", &AntiKt4LCTopoJets_jet_jfcombnn_pc, &b_AntiKt4LCTopoJets_jet_jfcombnn_pc); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jfcombnn_pu", &AntiKt4LCTopoJets_jet_jfcombnn_pu, &b_AntiKt4LCTopoJets_jet_jfcombnn_pu); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_jfcombnn_llr", &AntiKt4LCTopoJets_jet_jfcombnn_llr, &b_AntiKt4LCTopoJets_jet_jfcombnn_llr); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mv1", &AntiKt4LCTopoJets_jet_mv1, &b_AntiKt4LCTopoJets_jet_mv1); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mv1c", &AntiKt4LCTopoJets_jet_mv1c, &b_AntiKt4LCTopoJets_jet_mv1c); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mv2m_pb", &AntiKt4LCTopoJets_jet_mv2m_pb, &b_AntiKt4LCTopoJets_jet_mv2m_pb); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mv2m_pu", &AntiKt4LCTopoJets_jet_mv2m_pu, &b_AntiKt4LCTopoJets_jet_mv2m_pu); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mv2m_pc", &AntiKt4LCTopoJets_jet_mv2m_pc, &b_AntiKt4LCTopoJets_jet_mv2m_pc); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mv2c00", &AntiKt4LCTopoJets_jet_mv2c00, &b_AntiKt4LCTopoJets_jet_mv2c00); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mv2c10", &AntiKt4LCTopoJets_jet_mv2c10, &b_AntiKt4LCTopoJets_jet_mv2c10); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mv2c20", &AntiKt4LCTopoJets_jet_mv2c20, &b_AntiKt4LCTopoJets_jet_mv2c20); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mv2c100", &AntiKt4LCTopoJets_jet_mv2c100, &b_AntiKt4LCTopoJets_jet_mv2c100); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_mvb", &AntiKt4LCTopoJets_jet_mvb, &b_AntiKt4LCTopoJets_jet_mvb); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_multisvbb1", &AntiKt4LCTopoJets_jet_multisvbb1, &b_AntiKt4LCTopoJets_jet_multisvbb1); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_jet_multisvbb2", &AntiKt4LCTopoJets_jet_multisvbb2, &b_AntiKt4LCTopoJets_jet_multisvbb2); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP2D_jet_ipxd_pb", &AntiKt4LCTopoJets_IP2D_jet_ipxd_pb, &b_AntiKt4LCTopoJets_IP2D_jet_ipxd_pb); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP2D_jet_ipxd_pc", &AntiKt4LCTopoJets_IP2D_jet_ipxd_pc, &b_AntiKt4LCTopoJets_IP2D_jet_ipxd_pc); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP2D_jet_ipxd_pu", &AntiKt4LCTopoJets_IP2D_jet_ipxd_pu, &b_AntiKt4LCTopoJets_IP2D_jet_ipxd_pu); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP2D_jet_ipxd_llr", &AntiKt4LCTopoJets_IP2D_jet_ipxd_llr, &b_AntiKt4LCTopoJets_IP2D_jet_ipxd_llr); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP2D_jet_ipxd_ntrk", &AntiKt4LCTopoJets_IP2D_jet_ipxd_ntrk, &b_AntiKt4LCTopoJets_IP2D_jet_ipxd_ntrk); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP3D_jet_ipxd_pb", &AntiKt4LCTopoJets_IP3D_jet_ipxd_pb, &b_AntiKt4LCTopoJets_IP3D_jet_ipxd_pb); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP3D_jet_ipxd_pc", &AntiKt4LCTopoJets_IP3D_jet_ipxd_pc, &b_AntiKt4LCTopoJets_IP3D_jet_ipxd_pc); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP3D_jet_ipxd_pu", &AntiKt4LCTopoJets_IP3D_jet_ipxd_pu, &b_AntiKt4LCTopoJets_IP3D_jet_ipxd_pu); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP3D_jet_ipxd_llr", &AntiKt4LCTopoJets_IP3D_jet_ipxd_llr, &b_AntiKt4LCTopoJets_IP3D_jet_ipxd_llr); */
   /* fChain->SetBranchAddress("AntiKt4LCTopoJets_IP3D_jet_ipxd_ntrk", &AntiKt4LCTopoJets_IP3D_jet_ipxd_ntrk, &b_AntiKt4LCTopoJets_IP3D_jet_ipxd_ntrk); */
   fChain->SetBranchAddress("runnb", &runnb, &b_runnb);
   fChain->SetBranchAddress("eventnb", &eventnb, &b_eventnb);
   fChain->SetBranchAddress("mcchan", &mcchan, &b_mcchan);
   fChain->SetBranchAddress("mcwg", &mcwg, &b_mcwg);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("avgmu", &avgmu, &b_avgmu);
   fChain->SetBranchAddress("PVx", &PVx, &b_PVx);
   fChain->SetBranchAddress("PVy", &PVy, &b_PVy);
   fChain->SetBranchAddress("PVz", &PVz, &b_PVz);
   Notify();
}

Bool_t bTagG::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void bTagG::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t bTagG::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef bTagG_cxx
