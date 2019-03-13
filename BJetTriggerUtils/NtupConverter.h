//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 16 03:42:40 2018 by ROOT version 6.04/02
// from TTree bTag_TriggerJets/bTagTriggerJets
// found on file: ../Tuning_rel21/run/flavntuple_20180209_ttbar_step4.root
//////////////////////////////////////////////////////////

#ifndef NtupConverter_h
#define NtupConverter_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class NtupConverter {
	public:
		TTree          *fChain;      //!pointer to the analyzed TTree or TChain
		Int_t fCurrent;              //!current Tree number in a TChain

		// Fixed size dimensions of array or collections stored in the TTree if any.

		// Declaration of leaf types
		Int_t runnb;
		Int_t eventnb;
		Int_t mcchan;
		Double_t mcwg;
		vector<bool>    *jet_ForHybrid;
		vector<int>     *jet_Hadflav;
		vector<int>     *jet_Coneflav;
		vector<float>   *jet_HighestbHadpt;
		vector<float>   *jet_LowestbHadpt;
		vector<float>   *Offjet_Eta;
		vector<float>   *Offjet_Phi;
		vector<float>   *Offjet_pt;
		vector<float>   *Offjet_mv2c10;
		vector<float>   *jet_pt;
		vector<float>   *jet_eta;
		vector<float>   *jet_phi;
		vector<float>   *jet_E;
		vector<float>   *jet_m;
		vector<int>     *jet_truthflav;
		vector<float>   *jet_dRminToB;
		vector<float>   *jet_dRminToC;
		vector<float>   *jet_dRminToT;
		vector<vector<float> > *jet_trk_pt;
		vector<vector<float> > *jet_trk_eta;
		vector<vector<float> > *jet_trk_phi;
		vector<vector<float> > *jet_trk_d0sig;
		vector<vector<float> > *jet_trk_z0sig;
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
		vector<float>   *jet_sv1_Lxy;
		vector<float>   *jet_sv1_L3d;
		vector<float>   *jet_sv1_dR;
		vector<float>   *jet_sv1_sig3d;
		vector<float>   *jet_jf_pb;
		vector<float>   *jet_jf_pc;
		vector<float>   *jet_jf_pu;
		vector<float>   *jet_jf_llr;
		vector<float>   *jet_jf_m;
		vector<float>   *jet_jf_mUncorr;
		vector<float>   *jet_jf_efc;
		vector<float>   *jet_jf_deta;
		vector<float>   *jet_jf_dphi;
		vector<float>   *jet_jf_dRFlightDir;
		vector<float>   *jet_jf_ntrkAtVx;
		vector<int>     *jet_jf_nvtx;
		vector<int>     *jet_jf_nvtx1t;
		vector<int>     *jet_jf_n2t;
		vector<float>   *jet_jf_sig3d;
		//vector<int>     *jet_jf_nvtx1t;
		//vector<int>     *jet_jf_n2t;
		vector<vector<int> > *jet_IP2_Trkgrd;
		vector<vector<int> > *jet_IP3_Trkgrd;
		vector<double>  *jet_mv2c00;
		vector<double>  *jet_mv2c10;
		vector<double>  *jet_mv2c20;

		// List of branches
		TBranch        *b_runnb;      //!
		TBranch        *b_eventnb;      //!
		TBranch        *b_mcchan;      //!
		TBranch        *b_mcwg;      //!
		TBranch        *b_jet_ForHybrid;      //!
		TBranch        *b_jet_Hadflav;      //!
		TBranch        *b_jet_Coneflav;      //!
		TBranch        *b_jet_HighestbHadpt;      //!
		TBranch        *b_jet_LowestbHadpt;      //!
		TBranch        *b_Offjet_Eta;      //!
		TBranch        *b_Offjet_Phi;      //!
		TBranch        *b_Offjet_pt;      //!
		TBranch        *b_Offjet_mv2c10;      //!
		TBranch        *b_jet_pt;      //!
		TBranch        *b_jet_eta;      //!
		TBranch        *b_jet_phi;      //!
		TBranch        *b_jet_E;      //!
		TBranch        *b_jet_m;      //!
		TBranch        *b_jet_truthflav;      //!
		TBranch        *b_jet_dRminToB;      //!
		TBranch        *b_jet_dRminToC;      //!
		TBranch        *b_jet_dRminToT;      //!
		TBranch        *b_jet_trk_pt;      //!
		TBranch        *b_jet_trk_eta;      //!
		TBranch        *b_jet_trk_phi;      //!
		TBranch        *b_jet_trk_d0sig;      //!
		TBranch        *b_jet_trk_z0sig;      //!
		TBranch        *b_jet_ip2d_pb;      //!
		TBranch        *b_jet_ip2d_pc;      //!
		TBranch        *b_jet_ip2d_pu;      //!
		TBranch        *b_jet_ip2d_llr;      //!
		TBranch        *b_jet_ip3d_pb;      //!
		TBranch        *b_jet_ip3d_pc;      //!
		TBranch        *b_jet_ip3d_pu;      //!
		TBranch        *b_jet_ip3d_llr;      //!
		TBranch        *b_jet_sv0_sig3d;      //!
		TBranch        *b_jet_sv0_ntrkj;      //!
		TBranch        *b_jet_sv0_ntrkv;      //!
		TBranch        *b_jet_sv0_n2t;      //!
		TBranch        *b_jet_sv0_m;      //!
		TBranch        *b_jet_sv0_efc;      //!
		TBranch        *b_jet_sv0_normdist;      //!
		TBranch        *b_jet_sv1_ntrkj;      //!
		TBranch        *b_jet_sv1_ntrkv;      //!
		TBranch        *b_jet_sv1_n2t;      //!
		TBranch        *b_jet_sv1_m;      //!
		TBranch        *b_jet_sv1_efc;      //!
		TBranch        *b_jet_sv1_normdist;      //!
		TBranch        *b_jet_sv1_pb;      //!
		TBranch        *b_jet_sv1_pc;      //!
		TBranch        *b_jet_sv1_pu;      //!
		TBranch        *b_jet_sv1_llr;      //!
		TBranch        *b_jet_sv1_Lxy;      //!
		TBranch        *b_jet_sv1_L3d;      //!
		TBranch        *b_jet_sv1_dR;      //!
		TBranch        *b_jet_sv1_sig3d;      //!
		TBranch        *b_jet_jf_pb;      //!
		TBranch        *b_jet_jf_pc;      //!
		TBranch        *b_jet_jf_pu;      //!
		TBranch        *b_jet_jf_llr;      //!
		TBranch        *b_jet_jf_m;      //!
		TBranch        *b_jet_jf_mUncorr;      //!
		TBranch        *b_jet_jf_efc;      //!
		TBranch        *b_jet_jf_deta;      //!
		TBranch        *b_jet_jf_dphi;      //!
		TBranch        *b_jet_jf_dRFlightDir;      //!
		TBranch        *b_jet_jf_ntrkAtVx;      //!
		TBranch        *b_jet_jf_nvtx;      //!
		TBranch        *b_jet_jf_nvtx1t;      //!
		TBranch        *b_jet_jf_n2t;      //!
		TBranch        *b_jet_jf_sig3d;      //!
		//TBranch        *b_jet_jf_nvtx1t;      //!
		//TBranch        *b_jet_jf_n2t;      //!
		TBranch        *b_jet_IP2_Trkgrd;      //!
		TBranch        *b_jet_IP3_Trkgrd;      //!
		TBranch        *b_jet_mv2c00;      //!
		TBranch        *b_jet_mv2c10;      //!
		TBranch        *b_jet_mv2c20;      //!

		NtupConverter(TTree *tree=0);
		virtual ~NtupConverter();
		virtual Int_t    Cut(Long64_t entry);
		virtual Int_t    GetEntry(Long64_t entry);
		virtual Long64_t LoadTree(Long64_t entry);
		virtual void     Init(TTree *tree);
		virtual void     Loop(TString outFileName, int nEvtPerFile);
		virtual Bool_t   Notify();
		virtual void     Show(Long64_t entry = -1);

		///////////////////////////////////////////
		// user defined stuff
		///////////////////////////////////////////

		// methods
		void ResetOutput();
		void InitOutputTree();
		void FillOutputTree(std::vector<int> vecIdx);

		// output (offline-like) tree
		// - the structure is basically the same as the online
		// - some variables are missing in the online tree, so they will be set to default values
		// - different handling of the "ForHybrid" info in the offline: when producing the input for the hybrid tuning only the jets with "ForHybrid==1" are saved
		TTree *m_outTree;
		TFile *m_outFile;

		// variables
		Int_t out_runnb;
		Int_t out_eventnb;
		Int_t out_mcchan;
		Double_t out_mcwg;
		Int_t out_lbn;
		Int_t out_coreFlag;
		Int_t out_larError;
		Int_t out_tileError;
		Int_t out_nPV;
		Double_t out_PVx;
		Double_t out_PVy;
		Double_t out_PVz;
		Double_t out_avgmu;
		Int_t out_actmu;
		Int_t out_nbjets_HadF;
		Int_t out_nbjets_HadI;
		Int_t out_nbjets;
		Int_t out_nbjets_q;
		vector<float>   *out_jet_pt;
		vector<float>   *out_jet_pt_orig;
		vector<float>   *out_jet_eta;
		vector<float>   *out_jet_eta_orig;
		vector<float>   *out_jet_phi;
		vector<float>   *out_jet_phi_orig;
		vector<float>   *out_jet_jf_m;
		vector<float>   *out_jet_jf_efc;
		vector<float>   *out_jet_jf_deta;
		vector<float>   *out_jet_jf_dphi;
		vector<float>   *out_jet_jf_ntrkAtVx;
		vector<int>     *out_jet_jf_nvtx;
		vector<float>   *out_jet_jf_sig3d;
		vector<int>     *out_jet_jf_nvtx1t;
		vector<int>     *out_jet_jf_n2t;
		vector<float>   *out_jet_jf_phi;
		vector<float>   *out_jet_jf_theta;
		vector<float>   *out_jet_jf_mUncorr;
		vector<float>   *out_jet_jf_dRFlightDir;
		Int_t out_njets;
		vector<float>   *out_jet_E;
		vector<float>   *out_jet_m;
		vector<int>     *out_jet_truthflav;
		vector<int>     *out_jet_LabDr_HadF;
		vector<int>     *out_jet_aliveAfterOR;
		vector<int>     *out_jet_aliveAfterORmu;
		vector<int>     *out_jet_truthMatch;
		vector<float>   *out_jet_dRiso;
		vector<float>   *out_jet_JVT;
		vector<float>   *out_jet_JVF;
		vector<float>   *out_jet_ip2d_pb;
		vector<float>   *out_jet_ip2d_pc;
		vector<float>   *out_jet_ip2d_pu;
		vector<double>  *out_jet_ip2d_llr;
		vector<float>   *out_jet_ip3d_pb;
		vector<float>   *out_jet_ip3d_pc;
		vector<float>   *out_jet_ip3d_pu;
		vector<double>  *out_jet_ip3d_llr;
		vector<float>   *out_jet_sv1_sig3d;
		vector<int>     *out_jet_sv1_ntrkj;
		vector<int>     *out_jet_sv1_ntrkv;
		vector<int>     *out_jet_sv1_n2t;
		vector<float>   *out_jet_sv1_m;
		vector<float>   *out_jet_sv1_efc;
		vector<float>   *out_jet_sv1_normdist;
		vector<int>     *out_jet_sv1_Nvtx;
		vector<float>   *out_jet_sv1_deltaR;
		vector<float>   *out_jet_sv1_Lxy;
		vector<float>   *out_jet_sv1_L3d;
		vector<float>   *out_jet_sv1_llr;
		vector<float>   *out_jet_sv1_pu;
		vector<float>   *out_jet_sv1_pc;
		vector<float>   *out_jet_sv1_pb;
		vector<int>     *out_jet_nConst;
		vector<double>  *out_jet_mv2m_pc;
		vector<double>  *out_jet_mv2m_pu;
		vector<double>  *out_jet_mv2m_pb;
		vector<double>  *out_jet_mv2c00;
		vector<double>  *out_jet_mv2c10;
		vector<double>  *out_jet_mv2c10rnn;
		vector<double>  *out_jet_mv2c20;
		vector<double>  *out_jet_mv2c100;
		vector<float>   *out_jet_truthPt;
		vector<int>     *out_jet_GhostL_HadF;
		vector<int>     *out_jet_GhostL_HadI;
		vector<int>     *out_jet_GhostL_q;
		vector<int>     *out_jet_ip3d_ntrk;
		vector<double>  *out_jet_rnnipll_pb;
		vector<double>  *out_jet_rnnipll_pc;
		vector<double>  *out_jet_rnnipll_pu;
		vector<double>  *out_jet_rnnipll_ptau;
		vector<double>  *out_jet_rnnip_pb;
		vector<double>  *out_jet_rnnip_pc;
		vector<double>  *out_jet_rnnip_pu;
		vector<double>  *out_jet_rnnip_ptau;
		vector<double>  *out_jet_mv2c10mu;
		vector<float>   *out_jet_mu_assJet_pt;
		vector<float>   *out_jet_mu_truthflav;
		vector<float>   *out_jet_mu_dR;
		vector<double>  *out_jet_mu_smt;
		vector<float>   *out_jet_mu_pTrel;
		vector<float>   *out_jet_mu_qOverPratio;
		vector<float>   *out_jet_mu_mombalsignif;
		vector<float>   *out_jet_mu_scatneighsignif;
		vector<float>   *out_jet_mu_VtxTyp;
		vector<float>   *out_jet_mu_pt;
		vector<float>   *out_jet_mu_eta;
		vector<float>   *out_jet_mu_phi;
		vector<float>   *out_jet_mu_d0;
		vector<float>   *out_jet_mu_z0;
		vector<float>   *out_jet_mu_parent_pdgid;
		vector<float>   *out_jet_mu_ID_qOverP_var;
		vector<float>   *out_jet_mu_muonType;
		vector<int>     *out_jet_mu_fatjet_nMu;
		vector<float>   *out_jet_mu_fatjet_pTmax_pT;
		vector<float>   *out_jet_mu_fatjet_pTmax_pTrel;
		vector<float>   *out_jet_mu_fatjet_pTmax_pTrelFrac;
		vector<int>     *out_nTrk_vtx1;
		vector<float>   *out_mass_first_vtx;
		vector<float>   *out_e_first_vtx;
		vector<float>   *out_e_frac_vtx1;
		vector<float>   *out_closestVtx_L3D;
		vector<float>   *out_JF_Lxy1;
		vector<float>   *out_vtx1_MaxTrkRapidity;
		vector<float>   *out_vtx1_AvgTrkRapidity;
		vector<float>   *out_vtx1_MinTrkRapidity;
		vector<int>     *out_nTrk_vtx2;
		vector<float>   *out_mass_second_vtx;
		vector<float>   *out_e_second_vtx;
		vector<float>   *out_e_frac_vtx2;
		vector<float>   *out_second_closestVtx_L3D;
		vector<float>   *out_JF_Lxy2;
		vector<float>   *out_vtx2_MaxTrkRapidity;
		vector<float>   *out_vtx2_AvgTrkRapidity;
		vector<float>   *out_vtx2_MinTrkRapidity;
		vector<float>   *out_MaxTrkRapidity;
		vector<float>   *out_MinTrkRapidity;
		vector<float>   *out_AvgTrkRapidity;

};

#endif

#ifdef NtupConverter_cxx
NtupConverter::NtupConverter(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
        if (tree == 0) {
                TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../Tuning_rel21/run/flavntuple_20180209_ttbar_step4.root");
                if (!f || !f->IsOpen()) {
                        f = new TFile("../Tuning_rel21/run/flavntuple_20180209_ttbar_step4.root");
                }
                f->GetObject("bTag_TriggerJets",tree);

        }
        Init(tree);
}

NtupConverter::~NtupConverter()
{
        if (!fChain) return;
        delete fChain->GetCurrentFile();
}

Int_t NtupConverter::GetEntry(Long64_t entry)
{
// Read contents of entry.
        if (!fChain) return 0;
        return fChain->GetEntry(entry);
}
Long64_t NtupConverter::LoadTree(Long64_t entry)
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

void NtupConverter::Init(TTree *tree)
{
        // The Init() function is called when the selector needs to initialize
        // a new tree or chain. Typically here the branch addresses and branch
        // pointers of the tree will be set.
        // It is normally not necessary to make changes to the generated
        // code, but the routine can be extended by the user if needed.
        // Init() will be called many times when running on PROOF
        // (once per file to be processed).

        // Set object pointer
        jet_ForHybrid = 0;
        jet_Hadflav = 0;
        jet_Coneflav = 0;
        jet_HighestbHadpt = 0;
        jet_LowestbHadpt = 0;
        Offjet_Eta = 0;
        Offjet_Phi = 0;
        Offjet_pt = 0;
        Offjet_mv2c10 = 0;
        jet_pt = 0;
        jet_eta = 0;
        jet_phi = 0;
        jet_E = 0;
        jet_m = 0;
        jet_truthflav = 0;
        jet_dRminToB = 0;
        jet_dRminToC = 0;
        jet_dRminToT = 0;
        jet_trk_pt = 0;
        jet_trk_eta = 0;
        jet_trk_phi = 0;
        jet_trk_d0sig = 0;
        jet_trk_z0sig = 0;
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
        jet_sv1_Lxy = 0;
        jet_sv1_L3d = 0;
        jet_sv1_dR = 0;
        jet_sv1_sig3d = 0;
        jet_jf_pb = 0;
        jet_jf_pc = 0;
        jet_jf_pu = 0;
        jet_jf_llr = 0;
        jet_jf_m = 0;
        jet_jf_mUncorr = 0;
        jet_jf_efc = 0;
        jet_jf_deta = 0;
        jet_jf_dphi = 0;
        jet_jf_dRFlightDir = 0;
        jet_jf_ntrkAtVx = 0;
        jet_jf_nvtx = 0;
        jet_jf_nvtx1t = 0;
        jet_jf_n2t = 0;
        jet_jf_sig3d = 0;
        //jet_jf_nvtx1t = 0;
        //jet_jf_n2t = 0;
        jet_IP2_Trkgrd = 0;
        jet_IP3_Trkgrd = 0;
        jet_mv2c00 = 0;
        jet_mv2c10 = 0;
        jet_mv2c20 = 0;
        // Set branch addresses and branch pointers
        if (!tree) return;
        fChain = tree;
        fCurrent = -1;
        fChain->SetMakeClass(1);

        fChain->SetBranchAddress("runnb", &runnb, &b_runnb);
        fChain->SetBranchAddress("eventnb", &eventnb, &b_eventnb);
        fChain->SetBranchAddress("mcchan", &mcchan, &b_mcchan);
        fChain->SetBranchAddress("mcwg", &mcwg, &b_mcwg);
        fChain->SetBranchAddress("jet_ForHybrid", &jet_ForHybrid, &b_jet_ForHybrid);
        fChain->SetBranchAddress("jet_Hadflav", &jet_Hadflav, &b_jet_Hadflav);
        fChain->SetBranchAddress("jet_Coneflav", &jet_Coneflav, &b_jet_Coneflav);
        fChain->SetBranchAddress("jet_HighestbHadpt", &jet_HighestbHadpt, &b_jet_HighestbHadpt);
        fChain->SetBranchAddress("jet_LowestbHadpt", &jet_LowestbHadpt, &b_jet_LowestbHadpt);
        fChain->SetBranchAddress("Offjet_Eta", &Offjet_Eta, &b_Offjet_Eta);
        fChain->SetBranchAddress("Offjet_Phi", &Offjet_Phi, &b_Offjet_Phi);
        fChain->SetBranchAddress("Offjet_pt", &Offjet_pt, &b_Offjet_pt);
        fChain->SetBranchAddress("Offjet_mv2c10", &Offjet_mv2c10, &b_Offjet_mv2c10);
        fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
        fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
        fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
        fChain->SetBranchAddress("jet_E", &jet_E, &b_jet_E);
        fChain->SetBranchAddress("jet_m", &jet_m, &b_jet_m);
        fChain->SetBranchAddress("jet_truthflav", &jet_truthflav, &b_jet_truthflav);
        fChain->SetBranchAddress("jet_dRminToB", &jet_dRminToB, &b_jet_dRminToB);
        fChain->SetBranchAddress("jet_dRminToC", &jet_dRminToC, &b_jet_dRminToC);
        fChain->SetBranchAddress("jet_dRminToT", &jet_dRminToT, &b_jet_dRminToT);
        fChain->SetBranchAddress("jet_trk_pt", &jet_trk_pt, &b_jet_trk_pt);
        fChain->SetBranchAddress("jet_trk_eta", &jet_trk_eta, &b_jet_trk_eta);
        fChain->SetBranchAddress("jet_trk_phi", &jet_trk_phi, &b_jet_trk_phi);
        fChain->SetBranchAddress("jet_trk_d0sig", &jet_trk_d0sig, &b_jet_trk_d0sig);
        fChain->SetBranchAddress("jet_trk_z0sig", &jet_trk_z0sig, &b_jet_trk_z0sig);
        fChain->SetBranchAddress("jet_ip2d_pb", &jet_ip2d_pb, &b_jet_ip2d_pb);
        fChain->SetBranchAddress("jet_ip2d_pc", &jet_ip2d_pc, &b_jet_ip2d_pc);
        fChain->SetBranchAddress("jet_ip2d_pu", &jet_ip2d_pu, &b_jet_ip2d_pu);
        fChain->SetBranchAddress("jet_ip2d_llr", &jet_ip2d_llr, &b_jet_ip2d_llr);
        fChain->SetBranchAddress("jet_ip3d_pb", &jet_ip3d_pb, &b_jet_ip3d_pb);
        fChain->SetBranchAddress("jet_ip3d_pc", &jet_ip3d_pc, &b_jet_ip3d_pc);
        fChain->SetBranchAddress("jet_ip3d_pu", &jet_ip3d_pu, &b_jet_ip3d_pu);
        fChain->SetBranchAddress("jet_ip3d_llr", &jet_ip3d_llr, &b_jet_ip3d_llr);
        fChain->SetBranchAddress("jet_sv0_sig3d", &jet_sv0_sig3d, &b_jet_sv0_sig3d);
        fChain->SetBranchAddress("jet_sv0_ntrkj", &jet_sv0_ntrkj, &b_jet_sv0_ntrkj);
        fChain->SetBranchAddress("jet_sv0_ntrkv", &jet_sv0_ntrkv, &b_jet_sv0_ntrkv);
        fChain->SetBranchAddress("jet_sv0_n2t", &jet_sv0_n2t, &b_jet_sv0_n2t);
        fChain->SetBranchAddress("jet_sv0_m", &jet_sv0_m, &b_jet_sv0_m);
        fChain->SetBranchAddress("jet_sv0_efc", &jet_sv0_efc, &b_jet_sv0_efc);
        fChain->SetBranchAddress("jet_sv0_normdist", &jet_sv0_normdist, &b_jet_sv0_normdist);
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
        fChain->SetBranchAddress("jet_sv1_Lxy", &jet_sv1_Lxy, &b_jet_sv1_Lxy);
        fChain->SetBranchAddress("jet_sv1_L3d", &jet_sv1_L3d, &b_jet_sv1_L3d);
        fChain->SetBranchAddress("jet_sv1_dR", &jet_sv1_dR, &b_jet_sv1_dR);
        fChain->SetBranchAddress("jet_sv1_sig3d", &jet_sv1_sig3d, &b_jet_sv1_sig3d);
        fChain->SetBranchAddress("jet_jf_pb", &jet_jf_pb, &b_jet_jf_pb);
        fChain->SetBranchAddress("jet_jf_pc", &jet_jf_pc, &b_jet_jf_pc);
        fChain->SetBranchAddress("jet_jf_pu", &jet_jf_pu, &b_jet_jf_pu);
        fChain->SetBranchAddress("jet_jf_llr", &jet_jf_llr, &b_jet_jf_llr);
        fChain->SetBranchAddress("jet_jf_m", &jet_jf_m, &b_jet_jf_m);
        fChain->SetBranchAddress("jet_jf_mUncorr", &jet_jf_mUncorr, &b_jet_jf_mUncorr);
        fChain->SetBranchAddress("jet_jf_efc", &jet_jf_efc, &b_jet_jf_efc);
        fChain->SetBranchAddress("jet_jf_deta", &jet_jf_deta, &b_jet_jf_deta);
        fChain->SetBranchAddress("jet_jf_dphi", &jet_jf_dphi, &b_jet_jf_dphi);
        fChain->SetBranchAddress("jet_jf_dRFlightDir", &jet_jf_dRFlightDir, &b_jet_jf_dRFlightDir);
        fChain->SetBranchAddress("jet_jf_ntrkAtVx", &jet_jf_ntrkAtVx, &b_jet_jf_ntrkAtVx);
        fChain->SetBranchAddress("jet_jf_nvtx", &jet_jf_nvtx, &b_jet_jf_nvtx);
        fChain->SetBranchAddress("jet_jf_nvtx1t", &jet_jf_nvtx1t, &b_jet_jf_nvtx1t);
        fChain->SetBranchAddress("jet_jf_n2t", &jet_jf_n2t, &b_jet_jf_n2t);
        fChain->SetBranchAddress("jet_jf_sig3d", &jet_jf_sig3d, &b_jet_jf_sig3d);
//    fChain->SetBranchAddress("jet_jf_nvtx1t", &jet_jf_nvtx1t, &b_jet_jf_nvtx1t);
//    fChain->SetBranchAddress("jet_jf_n2t", &jet_jf_n2t, &b_jet_jf_n2t);
        fChain->SetBranchAddress("jet_IP2_Trkgrd", &jet_IP2_Trkgrd, &b_jet_IP2_Trkgrd);
        fChain->SetBranchAddress("jet_IP3_Trkgrd", &jet_IP3_Trkgrd, &b_jet_IP3_Trkgrd);
        fChain->SetBranchAddress("jet_mv2c00", &jet_mv2c00, &b_jet_mv2c00);
        fChain->SetBranchAddress("jet_mv2c10", &jet_mv2c10, &b_jet_mv2c10);
        fChain->SetBranchAddress("jet_mv2c20", &jet_mv2c20, &b_jet_mv2c20);
        Notify();
}

Bool_t NtupConverter::Notify()
{
        // The Notify() function is called when a new file is opened. This
        // can be either for a new TTree in a TChain or when when a new TTree
        // is started when using PROOF. It is normally not necessary to make changes
        // to the generated code, but the routine can be extended by the
        // user if needed. The return value is currently not used.

        return kTRUE;
}

void NtupConverter::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
        if (!fChain) return;
        fChain->Show(entry);
}
Int_t NtupConverter::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
        return 1;
}
#endif // #ifdef NtupConverter_cxx
