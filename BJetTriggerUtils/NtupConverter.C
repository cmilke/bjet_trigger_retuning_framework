#define NtupConverter_cxx
#include "NtupConverter.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>

void NtupConverter::Loop(TString outFileName, int nEvtPerFile)
{
//   In a ROOT session, you can do:
//      root> .L NtupConverter.C
//      root> NtupConverter t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

	if (fChain == 0) return;

	TString outname = Form("%s_0.root", outFileName.Data());
	m_outFile = TFile::Open(outname,"RECREATE");

	InitOutputTree();

	Long64_t nentries = fChain->GetEntriesFast();
	int nProcEvts = 0;
	int nFiles = 0;

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		nProcEvts++;

		ResetOutput();

		std::vector<int> goodJetsIdx;
		goodJetsIdx.clear();

		for (unsigned int i = 0; i < jet_ForHybrid->size(); i++) {
			if (jet_ForHybrid->at(i)) goodJetsIdx.push_back(i);
		}

		if (goodJetsIdx.size() > 0) {
			FillOutputTree(goodJetsIdx);
		}
		
		if (nEvtPerFile > 0) {
			if (nProcEvts % nEvtPerFile == 0) {
				m_outTree->Write();
				m_outFile->Write();
				m_outFile->Close();
				
				nFiles++;	
				outname = Form("%s_%d.root", outFileName.Data(), nFiles);
				m_outFile = new TFile(outname, "RECREATE");
				InitOutputTree();
			}
		}
	}

	m_outTree->Write();
	m_outFile->Write();
	m_outFile->Close();
}

void NtupConverter::FillOutputTree(std::vector<int> vecIdx) {

	// only the relevant variables are filled
	// some are skipped (i.e. they stay with their default value set in the ResetOutput() method

	out_runnb = runnb;
	out_eventnb = eventnb;
	out_mcchan = mcchan;
	out_mcwg = mcwg;

	out_njets = vecIdx.size();
	
	for (unsigned int i = 0; i < vecIdx.size(); i++) {
		int idx = vecIdx.at(i);

		// jet kinematics
		out_jet_pt->push_back(jet_pt->at(idx));
		out_jet_pt_orig->push_back(-1.);
		out_jet_eta->push_back(jet_eta->at(idx));
		out_jet_eta_orig->push_back(-1.);
		out_jet_phi->push_back(jet_phi->at(idx));
		out_jet_E->push_back(-1.);
		out_jet_m->push_back(-1.);

		// other features
		out_jet_truthflav->push_back(jet_truthflav->at(idx));
		out_jet_LabDr_HadF->push_back(-1);
		out_jet_aliveAfterOR->push_back(-1);
		out_jet_aliveAfterORmu->push_back(-1);
		out_jet_truthMatch->push_back(1); // all the trigger jets are truth-matched
		out_jet_dRiso->push_back(-1.);
		out_jet_JVT->push_back(-1.);
		out_jet_JVF->push_back(-1.);
		out_jet_nConst->push_back(-1);
		out_jet_mu_assJet_pt->push_back(-1.);
		out_jet_mu_truthflav->push_back(-1);
		out_jet_mu_dR->push_back(-1.);
		out_jet_mu_smt->push_back(-1.);
		out_jet_mu_pTrel->push_back(-1.);
		out_jet_mu_qOverPratio->push_back(-1.);
		out_jet_mu_mombalsignif->push_back(-1.);
		out_jet_mu_scatneighsignif->push_back(-1.);
		out_jet_mu_VtxTyp->push_back(-1.);
		out_jet_mu_pt->push_back(-1.);
		out_jet_mu_eta->push_back(-1.);
		out_jet_mu_phi->push_back(-1.);
		out_jet_mu_d0->push_back(-1.);
		out_jet_mu_z0->push_back(-1.);
		out_jet_mu_parent_pdgid ->push_back(-1.);
		out_jet_mu_ID_qOverP_var->push_back(-1.);
		out_jet_mu_muonType->push_back(-1.);
		out_jet_mu_fatjet_nMu->push_back(-1);
		out_jet_mu_fatjet_pTmax_pT->push_back(-1.);
		out_jet_mu_fatjet_pTmax_pTrel->push_back(-1.);
		out_jet_mu_fatjet_pTmax_pTrelFrac->push_back(-1.);
		out_nTrk_vtx1->push_back(-1);
		out_mass_first_vtx->push_back(-1.);
		out_e_first_vtx->push_back(-1.);
		out_e_frac_vtx1->push_back(-1.);
		out_closestVtx_L3D->push_back(-1.);
		out_JF_Lxy1->push_back(-1.);
		out_vtx1_MaxTrkRapidity->push_back(-1.);
		out_vtx1_AvgTrkRapidity->push_back(-1.);
		out_vtx1_MinTrkRapidity->push_back(-1.);
		out_nTrk_vtx2->push_back(-1);
		out_mass_second_vtx->push_back(-1.);
		out_e_second_vtx->push_back(-1.);
		out_e_frac_vtx2->push_back(-1.);
		out_second_closestVtx_L3D->push_back(-1.);
		out_JF_Lxy2->push_back(-1.);
		out_vtx2_MaxTrkRapidity->push_back(-1.);
		out_vtx2_AvgTrkRapidity->push_back(-1.);
		out_vtx2_MinTrkRapidity->push_back(-1.);
		out_MaxTrkRapidity->push_back(-1.);
		out_MinTrkRapidity->push_back(-1.);
		out_AvgTrkRapidity->push_back(-1.);

		// jet fitter
		out_jet_jf_m->push_back(jet_jf_m->at(idx));
		out_jet_jf_efc->push_back(jet_jf_efc->at(idx));
		out_jet_jf_deta->push_back(jet_jf_deta->at(idx));
		out_jet_jf_dphi->push_back(jet_jf_dphi->at(idx));
		out_jet_jf_ntrkAtVx->push_back(jet_jf_ntrkAtVx->at(idx));
		out_jet_jf_nvtx->push_back(jet_jf_nvtx->at(idx));
		out_jet_jf_sig3d->push_back(jet_jf_sig3d->at(idx));
		out_jet_jf_nvtx1t->push_back(jet_jf_nvtx1t->at(idx));
		out_jet_jf_n2t->push_back(jet_jf_n2t->at(idx));
		out_jet_jf_mUncorr->push_back(jet_jf_mUncorr->at(idx));
		out_jet_jf_dRFlightDir->push_back(jet_jf_dRFlightDir->at(idx));
		out_jet_jf_phi->push_back(-9999.);
		out_jet_jf_theta->push_back(-9999.);

		// ip2d
		out_jet_ip2d_pb->push_back(jet_ip2d_pb->at(idx));
		out_jet_ip2d_pc->push_back(jet_ip2d_pc->at(idx));
		out_jet_ip2d_pu->push_back(jet_ip2d_pu->at(idx));
		out_jet_ip2d_llr->push_back(jet_ip2d_llr->at(idx));

		// ip3d
		out_jet_ip3d_pb->push_back(jet_ip3d_pb->at(idx));
		out_jet_ip3d_pc->push_back(jet_ip3d_pc->at(idx));
		out_jet_ip3d_pu->push_back(jet_ip3d_pu->at(idx));
		out_jet_ip3d_llr->push_back(jet_ip3d_llr->at(idx));

		// sv1
		out_jet_sv1_sig3d->push_back(jet_sv1_sig3d->at(idx));
		out_jet_sv1_ntrkj->push_back(jet_sv1_ntrkj->at(idx));
		out_jet_sv1_ntrkv->push_back(jet_sv1_ntrkv->at(idx));
		out_jet_sv1_n2t->push_back(jet_sv1_n2t->at(idx));
		out_jet_sv1_m->push_back(jet_sv1_m->at(idx));
		out_jet_sv1_efc->push_back(jet_sv1_efc->at(idx));
		out_jet_sv1_normdist->push_back(jet_sv1_normdist->at(idx));
		out_jet_sv1_Nvtx->push_back(-1);
		out_jet_sv1_deltaR->push_back(jet_sv1_dR->at(idx)); // !!!!
		out_jet_sv1_Lxy->push_back(jet_sv1_Lxy->at(idx));
		out_jet_sv1_L3d->push_back(jet_sv1_L3d->at(idx));
		out_jet_sv1_llr->push_back(jet_sv1_llr->at(idx));
		out_jet_sv1_pu->push_back(-1.);
		out_jet_sv1_pc->push_back(-1.);
		out_jet_sv1_pb->push_back(-1.);

		// mv2c taggers
		out_jet_mv2c00->push_back(-9999.);
		out_jet_mv2c10->push_back(jet_mv2c10->at(idx));
		out_jet_mv2c20->push_back(-9999.);
		out_jet_mv2c10rnn->push_back(-9999.);
		out_jet_mv2c10mu->push_back(-9999.);
		out_jet_mv2c100->push_back(-9999.);

		// other taggers
		out_jet_rnnipll_pb->push_back(-1.);
		out_jet_rnnipll_pc->push_back(-1.);
		out_jet_rnnipll_pu->push_back(-1.);
		out_jet_rnnipll_ptau->push_back(-1.);
		out_jet_rnnip_pb->push_back(-1.);
		out_jet_rnnip_pc->push_back(-1.);
		out_jet_rnnip_pu->push_back(-1.);
		out_jet_rnnip_ptau->push_back(-1.);
	}

	m_outTree->Fill();

	return;
}

void NtupConverter::ResetOutput() {

	out_runnb = -1;
	out_eventnb = -1;
	out_mcchan = -1;
	out_mcwg = -1.;
	out_lbn = -1;
	out_coreFlag = -1;
	out_larError = -1;
	out_tileError = -1;
	out_nPV = -1;
	out_PVx = -9999.;
	out_PVy = -9999.;
	out_PVz = -9999.;
	out_avgmu = -1.;
	out_actmu = -1;
	out_nbjets_HadF = -1;
	out_nbjets_HadI = -1;
	out_nbjets = -1;
	out_nbjets_q = -1;
	out_jet_pt->clear();
	out_jet_pt_orig->clear();
	out_jet_eta->clear();
	out_jet_eta_orig->clear();
	out_jet_phi->clear();
	out_jet_phi_orig->clear();
	out_jet_jf_m->clear();
	out_jet_jf_efc->clear();
	out_jet_jf_deta->clear();
	out_jet_jf_dphi->clear();
	out_jet_jf_ntrkAtVx->clear();
	out_jet_jf_nvtx->clear();
	out_jet_jf_sig3d->clear();
	out_jet_jf_nvtx1t->clear();
	out_jet_jf_n2t->clear();
	out_jet_jf_phi->clear();
	out_jet_jf_theta->clear();
	out_jet_jf_mUncorr->clear();
	out_jet_jf_dRFlightDir->clear();
	out_njets = 0;
	out_jet_E->clear();
	out_jet_m->clear();
	out_jet_truthflav->clear();
	out_jet_LabDr_HadF->clear();
	out_jet_aliveAfterOR->clear();
	out_jet_aliveAfterORmu->clear();
	out_jet_truthMatch->clear();
	out_jet_dRiso->clear();
	out_jet_JVT->clear();
	out_jet_JVF->clear();
	out_jet_ip2d_pb->clear();
	out_jet_ip2d_pc->clear();
	out_jet_ip2d_pu->clear();
	out_jet_ip2d_llr->clear();
	out_jet_ip3d_pb->clear();
	out_jet_ip3d_pc->clear();
	out_jet_ip3d_pu->clear();
	out_jet_ip3d_llr->clear();
	out_jet_sv1_sig3d->clear();
	out_jet_sv1_ntrkj->clear();
	out_jet_sv1_ntrkv->clear();
	out_jet_sv1_n2t->clear();
	out_jet_sv1_m->clear();
	out_jet_sv1_efc->clear();
	out_jet_sv1_normdist->clear();
	out_jet_sv1_Nvtx->clear();
	out_jet_sv1_deltaR->clear();
	out_jet_sv1_Lxy->clear();
	out_jet_sv1_L3d->clear();
	out_jet_sv1_llr->clear();
	out_jet_sv1_pu->clear();
	out_jet_sv1_pc->clear();
	out_jet_sv1_pb->clear();
	out_jet_nConst->clear();
	out_jet_mv2m_pc->clear();
	out_jet_mv2m_pu->clear();
	out_jet_mv2m_pb->clear();
	out_jet_mv2c00->clear();
	out_jet_mv2c10->clear();
	out_jet_mv2c10rnn->clear();
	out_jet_mv2c20->clear();
	out_jet_mv2c100->clear();
	out_jet_truthPt->clear();
	out_jet_GhostL_HadF->clear();
	out_jet_GhostL_HadI->clear();
	out_jet_GhostL_q->clear();
	out_jet_ip3d_ntrk->clear();
	out_jet_rnnipll_pb->clear();
	out_jet_rnnipll_pc->clear();
	out_jet_rnnipll_pu->clear();
	out_jet_rnnipll_ptau->clear();
	out_jet_rnnip_pb->clear();
	out_jet_rnnip_pc->clear();
	out_jet_rnnip_pu->clear();
	out_jet_rnnip_ptau->clear();
	out_jet_mv2c10mu->clear();
	out_jet_mu_assJet_pt->clear();
	out_jet_mu_truthflav->clear();
	out_jet_mu_dR->clear();
	out_jet_mu_smt->clear();
	out_jet_mu_pTrel->clear();
	out_jet_mu_qOverPratio->clear();
	out_jet_mu_mombalsignif->clear();
	out_jet_mu_scatneighsignif->clear();
	out_jet_mu_VtxTyp->clear();
	out_jet_mu_pt->clear();
	out_jet_mu_eta->clear();
	out_jet_mu_phi->clear();
	out_jet_mu_d0->clear();
	out_jet_mu_z0->clear();
	out_jet_mu_parent_pdgid->clear(); ;
	out_jet_mu_ID_qOverP_var->clear();
	out_jet_mu_muonType->clear();
	out_jet_mu_fatjet_nMu->clear();
	out_jet_mu_fatjet_pTmax_pT->clear();
	out_jet_mu_fatjet_pTmax_pTrel->clear();
	out_jet_mu_fatjet_pTmax_pTrelFrac->clear();
	out_nTrk_vtx1->clear();
	out_mass_first_vtx->clear();
	out_e_first_vtx->clear();
	out_e_frac_vtx1->clear();
	out_closestVtx_L3D->clear();
	out_JF_Lxy1->clear();
	out_vtx1_MaxTrkRapidity->clear();;
	out_vtx1_AvgTrkRapidity->clear();
	out_vtx1_MinTrkRapidity->clear();
	out_nTrk_vtx2->clear();
	out_mass_second_vtx->clear();
	out_e_second_vtx->clear();
	out_e_frac_vtx2->clear();
	out_second_closestVtx_L3D->clear();;
	out_JF_Lxy2->clear();
	out_vtx2_MaxTrkRapidity->clear();;
	out_vtx2_AvgTrkRapidity->clear();
	out_vtx2_MinTrkRapidity->clear();
	out_MaxTrkRapidity->clear();
	out_MinTrkRapidity->clear();
	out_AvgTrkRapidity->clear();

	return;
}

void NtupConverter::InitOutputTree() {

	m_outTree = new TTree("bTag_Jets", "bTag_Jets");
	m_outTree->SetDirectory(m_outFile);

	out_jet_pt = new vector<float>;
	out_jet_pt_orig = new vector<float>;
	out_jet_eta = new vector<float>;
	out_jet_eta_orig = new vector<float>;
	out_jet_phi = new vector<float>;
	out_jet_phi_orig = new vector<float>;
	out_jet_jf_m = new vector<float>;
	out_jet_jf_efc = new vector<float>;
	out_jet_jf_deta = new vector<float>;
	out_jet_jf_dphi = new vector<float>;
	out_jet_jf_ntrkAtVx = new vector<float>;
	out_jet_jf_nvtx = new vector<int>;
	out_jet_jf_sig3d = new vector<float>;
	out_jet_jf_nvtx1t = new vector<int>;
	out_jet_jf_n2t = new vector<int>;
	out_jet_jf_phi = new vector<float>;
	out_jet_jf_theta = new vector<float>;
	out_jet_jf_mUncorr = new vector<float>;
	out_jet_jf_dRFlightDir = new vector<float>;
	out_jet_E = new vector<float>;
	out_jet_m = new vector<float>;
	out_jet_truthflav = new vector<int>;
	out_jet_LabDr_HadF = new vector<int>;
	out_jet_aliveAfterOR = new vector<int>;
	out_jet_aliveAfterORmu = new vector<int>;
	out_jet_truthMatch = new vector<int>;
	out_jet_dRiso = new vector<float>;
	out_jet_JVT = new vector<float>;
	out_jet_JVF = new vector<float>;
	out_jet_ip2d_pb = new vector<float>;
	out_jet_ip2d_pc = new vector<float>;
	out_jet_ip2d_pu = new vector<float>;
	out_jet_ip2d_llr = new vector<double>;
	out_jet_ip3d_pb = new vector<float>;
	out_jet_ip3d_pc = new vector<float>;
	out_jet_ip3d_pu = new vector<float>;
	out_jet_ip3d_llr = new vector<double>;
	out_jet_sv1_sig3d = new vector<float>;
	out_jet_sv1_ntrkj = new vector<int>;
	out_jet_sv1_ntrkv = new vector<int>;
	out_jet_sv1_n2t = new vector<int>;
	out_jet_sv1_m = new vector<float>;
	out_jet_sv1_efc = new vector<float>;
	out_jet_sv1_normdist = new vector<float>;
	out_jet_sv1_Nvtx = new vector<int>;
	out_jet_sv1_deltaR = new vector<float>;
	out_jet_sv1_Lxy = new vector<float>;
	out_jet_sv1_L3d = new vector<float>;
	out_jet_sv1_llr = new vector<float>;
	out_jet_sv1_pu = new vector<float>;
	out_jet_sv1_pc = new vector<float>;
	out_jet_sv1_pb = new vector<float>;
	out_jet_nConst = new vector<int>;
	out_jet_mv2m_pc = new vector<double>;
	out_jet_mv2m_pu = new vector<double>;
	out_jet_mv2m_pb = new vector<double>;
	out_jet_mv2c00 = new vector<double>;
	out_jet_mv2c10 = new vector<double>;
	out_jet_mv2c10rnn = new vector<double>;
	out_jet_mv2c20 = new vector<double>;
	out_jet_mv2c100 = new vector<double>;
	out_jet_truthPt = new vector<float>;
	out_jet_GhostL_HadF = new vector<int>;
	out_jet_GhostL_HadI = new vector<int>;
	out_jet_GhostL_q = new vector<int>;
	out_jet_ip3d_ntrk = new vector<int>;
	out_jet_rnnipll_pb = new vector<double>;
	out_jet_rnnipll_pc = new vector<double>;
	out_jet_rnnipll_pu = new vector<double>;
	out_jet_rnnipll_ptau = new vector<double>;
	out_jet_rnnip_pb = new vector<double>;
	out_jet_rnnip_pc = new vector<double>;
	out_jet_rnnip_pu = new vector<double>;
	out_jet_rnnip_ptau = new vector<double>;
	out_jet_mv2c10mu = new vector<double>;
	out_jet_mu_assJet_pt = new vector<float>;
	out_jet_mu_truthflav = new vector<float>;
	out_jet_mu_dR = new vector<float>;
	out_jet_mu_smt = new vector<double>;
	out_jet_mu_pTrel = new vector<float>;
	out_jet_mu_qOverPratio = new vector<float>;
	out_jet_mu_mombalsignif = new vector<float>;
	out_jet_mu_scatneighsignif = new vector<float>;
	out_jet_mu_VtxTyp = new vector<float>;
	out_jet_mu_pt = new vector<float>;
	out_jet_mu_eta = new vector<float>;
	out_jet_mu_phi = new vector<float>;
	out_jet_mu_d0 = new vector<float>;
	out_jet_mu_z0 = new vector<float>;
	out_jet_mu_parent_pdgid = new vector<float>;
	out_jet_mu_ID_qOverP_var = new vector<float>;
	out_jet_mu_muonType = new vector<float>;
	out_jet_mu_fatjet_nMu = new vector<int>;
	out_jet_mu_fatjet_pTmax_pT = new vector<float>;
	out_jet_mu_fatjet_pTmax_pTrel = new vector<float>;
	out_jet_mu_fatjet_pTmax_pTrelFrac = new vector<float>;
	out_nTrk_vtx1 = new vector<int>;
	out_mass_first_vtx = new vector<float>;
	out_e_first_vtx = new vector<float>;
	out_e_frac_vtx1 = new vector<float>;
	out_closestVtx_L3D = new vector<float>;
	out_JF_Lxy1 = new vector<float>;
	out_vtx1_MaxTrkRapidity = new vector<float>;
	out_vtx1_AvgTrkRapidity = new vector<float>;
	out_vtx1_MinTrkRapidity = new vector<float>;
	out_nTrk_vtx2 = new vector<int>;
	out_mass_second_vtx = new vector<float>;
	out_e_second_vtx = new vector<float>;
	out_e_frac_vtx2 = new vector<float>;
	out_second_closestVtx_L3D = new vector<float>;
	out_JF_Lxy2 = new vector<float>;
	out_vtx2_MaxTrkRapidity = new vector<float>;
	out_vtx2_AvgTrkRapidity = new vector<float>;
	out_vtx2_MinTrkRapidity = new vector<float>;
	out_MaxTrkRapidity = new vector<float>;
	out_MinTrkRapidity = new vector<float>;
	out_AvgTrkRapidity = new vector<float>;

	m_outTree->Branch("runnb", &out_runnb);
	m_outTree->Branch("eventnb", &out_eventnb);
	m_outTree->Branch("mcchan", &out_mcchan);
	m_outTree->Branch("mcwg", &out_mcwg);
	m_outTree->Branch("lbn", &out_lbn);
	m_outTree->Branch("coreFlag", &out_coreFlag);
	m_outTree->Branch("larError", &out_larError);
	m_outTree->Branch("tileError", &out_tileError);
	m_outTree->Branch("nPV", &out_nPV);
	m_outTree->Branch("PVx", &out_PVx);
	m_outTree->Branch("PVy", &out_PVy);
	m_outTree->Branch("PVz", &out_PVz);
	m_outTree->Branch("avgmu", &out_avgmu);
	m_outTree->Branch("actmu", &out_actmu);
	m_outTree->Branch("nbjets_HadF", &out_nbjets_HadF);
	m_outTree->Branch("nbjets_HadI", &out_nbjets_HadI);
	m_outTree->Branch("nbjets", &out_nbjets);
	m_outTree->Branch("nbjets_q", &out_nbjets_q);
	m_outTree->Branch("jet_pt", &out_jet_pt);
	m_outTree->Branch("jet_pt_orig", &out_jet_pt_orig);
	m_outTree->Branch("jet_eta", &out_jet_eta);
	m_outTree->Branch("jet_eta_orig", &out_jet_eta_orig);
	m_outTree->Branch("jet_phi", &out_jet_phi);
	m_outTree->Branch("jet_phi_orig", &out_jet_phi_orig);
	m_outTree->Branch("jet_jf_m", &out_jet_jf_m);
	m_outTree->Branch("jet_jf_efc", &out_jet_jf_efc);
	m_outTree->Branch("jet_jf_deta", &out_jet_jf_deta);
	m_outTree->Branch("jet_jf_dphi", &out_jet_jf_dphi);
	m_outTree->Branch("jet_jf_ntrkAtVx", &out_jet_jf_ntrkAtVx);
	m_outTree->Branch("jet_jf_nvtx", &out_jet_jf_nvtx);
	m_outTree->Branch("jet_jf_sig3d", &out_jet_jf_sig3d);
	m_outTree->Branch("jet_jf_nvtx1t", &out_jet_jf_nvtx1t);
	m_outTree->Branch("jet_jf_n2t", &out_jet_jf_n2t);
	m_outTree->Branch("jet_jf_phi", &out_jet_jf_phi);
	m_outTree->Branch("jet_jf_theta", &out_jet_jf_theta);
	m_outTree->Branch("jet_jf_mUncorr", &out_jet_jf_mUncorr);
	m_outTree->Branch("jet_jf_dRFlightDir", &out_jet_jf_dRFlightDir);
	m_outTree->Branch("njets", &out_njets);
	m_outTree->Branch("jet_E", &out_jet_E);
	m_outTree->Branch("jet_m", &out_jet_m);
	m_outTree->Branch("jet_truthflav", &out_jet_truthflav);
	m_outTree->Branch("jet_LabDr_HadF", &out_jet_LabDr_HadF);
	m_outTree->Branch("jet_aliveAfterOR", &out_jet_aliveAfterOR);
	m_outTree->Branch("jet_aliveAfterORmu", &out_jet_aliveAfterORmu);
	m_outTree->Branch("jet_truthMatch", &out_jet_truthMatch);
	m_outTree->Branch("jet_dRiso", &out_jet_dRiso);
	m_outTree->Branch("jet_JVT", &out_jet_JVT);
	m_outTree->Branch("jet_JVF", &out_jet_JVF);
	m_outTree->Branch("jet_ip2d_pb", &out_jet_ip2d_pb);
	m_outTree->Branch("jet_ip2d_pc", &out_jet_ip2d_pc);
	m_outTree->Branch("jet_ip2d_pu", &out_jet_ip2d_pu);
	m_outTree->Branch("jet_ip2d_llr", &out_jet_ip2d_llr);
	m_outTree->Branch("jet_ip3d_pb", &out_jet_ip3d_pb);
	m_outTree->Branch("jet_ip3d_pc", &out_jet_ip3d_pc);
	m_outTree->Branch("jet_ip3d_pu", &out_jet_ip3d_pu);
	m_outTree->Branch("jet_ip3d_llr", &out_jet_ip3d_llr);
	m_outTree->Branch("jet_sv1_sig3d", &out_jet_sv1_sig3d);
	m_outTree->Branch("jet_sv1_ntrkj", &out_jet_sv1_ntrkj);
	m_outTree->Branch("jet_sv1_ntrkv", &out_jet_sv1_ntrkv);
	m_outTree->Branch("jet_sv1_n2t", &out_jet_sv1_n2t);
	m_outTree->Branch("jet_sv1_m", &out_jet_sv1_m);
	m_outTree->Branch("jet_sv1_efc", &out_jet_sv1_efc);
	m_outTree->Branch("jet_sv1_normdist", &out_jet_sv1_normdist);
	m_outTree->Branch("jet_sv1_Nvtx", &out_jet_sv1_Nvtx);
	m_outTree->Branch("jet_sv1_deltaR", &out_jet_sv1_deltaR);
	m_outTree->Branch("jet_sv1_Lxy", &out_jet_sv1_Lxy);
	m_outTree->Branch("jet_sv1_L3d", &out_jet_sv1_L3d);
	m_outTree->Branch("jet_sv1_llr", &out_jet_sv1_llr);
	m_outTree->Branch("jet_sv1_pu", &out_jet_sv1_pu);
	m_outTree->Branch("jet_sv1_pc", &out_jet_sv1_pc);
	m_outTree->Branch("jet_sv1_pb", &out_jet_sv1_pb);
	m_outTree->Branch("jet_nConst", &out_jet_nConst);
	m_outTree->Branch("jet_mv2m_pc", &out_jet_mv2m_pc);
	m_outTree->Branch("jet_mv2m_pu", &out_jet_mv2m_pu);
	m_outTree->Branch("jet_mv2m_pb", &out_jet_mv2m_pb);
	m_outTree->Branch("jet_mv2c00", &out_jet_mv2c00);
	m_outTree->Branch("jet_mv2c10", &out_jet_mv2c10);
	m_outTree->Branch("jet_mv2c10rnn", &out_jet_mv2c10rnn);
	m_outTree->Branch("jet_mv2c20", &out_jet_mv2c20);
	m_outTree->Branch("jet_mv2c100", &out_jet_mv2c100);
	m_outTree->Branch("jet_truthPt", &out_jet_truthPt);
	m_outTree->Branch("jet_GhostL_HadF", &out_jet_GhostL_HadF);
	m_outTree->Branch("jet_GhostL_HadI", &out_jet_GhostL_HadI);
	m_outTree->Branch("jet_GhostL_q", &out_jet_GhostL_q);
	m_outTree->Branch("jet_ip3d_ntrk", &out_jet_ip3d_ntrk);
	m_outTree->Branch("jet_rnnipll_pb", &out_jet_rnnipll_pb);
	m_outTree->Branch("jet_rnnipll_pc", &out_jet_rnnipll_pc);
	m_outTree->Branch("jet_rnnipll_pu", &out_jet_rnnipll_pu);
	m_outTree->Branch("jet_rnnipll_ptau", &out_jet_rnnipll_ptau);
	m_outTree->Branch("jet_rnnip_pb", &out_jet_rnnip_pb);
	m_outTree->Branch("jet_rnnip_pc", &out_jet_rnnip_pc);
	m_outTree->Branch("jet_rnnip_pu", &out_jet_rnnip_pu);
	m_outTree->Branch("jet_rnnip_ptau", &out_jet_rnnip_ptau);
	m_outTree->Branch("jet_mv2c10mu", &out_jet_mv2c10mu);
	m_outTree->Branch("jet_mu_assJet_pt", &out_jet_mu_assJet_pt);
	m_outTree->Branch("jet_mu_truthflav", &out_jet_mu_truthflav);
	m_outTree->Branch("jet_mu_dR", &out_jet_mu_dR);
	m_outTree->Branch("jet_mu_smt", &out_jet_mu_smt);
	m_outTree->Branch("jet_mu_pTrel", &out_jet_mu_pTrel);
	m_outTree->Branch("jet_mu_qOverPratio", &out_jet_mu_qOverPratio);
	m_outTree->Branch("jet_mu_mombalsignif", &out_jet_mu_mombalsignif);
	m_outTree->Branch("jet_mu_scatneighsignif", &out_jet_mu_scatneighsignif);
	m_outTree->Branch("jet_mu_VtxTyp", &out_jet_mu_VtxTyp);
	m_outTree->Branch("jet_mu_pt", &out_jet_mu_pt);
	m_outTree->Branch("jet_mu_eta", &out_jet_mu_eta);
	m_outTree->Branch("jet_mu_phi", &out_jet_mu_phi);
	m_outTree->Branch("jet_mu_d0", &out_jet_mu_d0);
	m_outTree->Branch("jet_mu_z0", &out_jet_mu_z0);
	m_outTree->Branch("jet_mu_parent_pdgid ", &out_jet_mu_parent_pdgid );
	m_outTree->Branch("jet_mu_ID_qOverP_var", &out_jet_mu_ID_qOverP_var);
	m_outTree->Branch("jet_mu_muonType", &out_jet_mu_muonType);
	m_outTree->Branch("jet_mu_fatjet_nMu", &out_jet_mu_fatjet_nMu);
	m_outTree->Branch("jet_mu_fatjet_pTmax_pT", &out_jet_mu_fatjet_pTmax_pT);
	m_outTree->Branch("jet_mu_fatjet_pTmax_pTrel", &out_jet_mu_fatjet_pTmax_pTrel);
	m_outTree->Branch("jet_mu_fatjet_pTmax_pTrelFrac", &out_jet_mu_fatjet_pTmax_pTrelFrac);
	m_outTree->Branch("nTrk_vtx1", &out_nTrk_vtx1);
	m_outTree->Branch("mass_first_vtx", &out_mass_first_vtx);
	m_outTree->Branch("e_first_vtx", &out_e_first_vtx);
	m_outTree->Branch("e_frac_vtx1", &out_e_frac_vtx1);
	m_outTree->Branch("closestVtx_L3D", &out_closestVtx_L3D);
	m_outTree->Branch("JF_Lxy1", &out_JF_Lxy1);
	m_outTree->Branch("vtx1_MaxTrkRapidity", &out_vtx1_MaxTrkRapidity);
	m_outTree->Branch("vtx1_AvgTrkRapidity", &out_vtx1_AvgTrkRapidity);
	m_outTree->Branch("vtx1_MinTrkRapidity", &out_vtx1_MinTrkRapidity);
	m_outTree->Branch("nTrk_vtx2", &out_nTrk_vtx2);
	m_outTree->Branch("mass_second_vtx", &out_mass_second_vtx);
	m_outTree->Branch("e_second_vtx", &out_e_second_vtx);
	m_outTree->Branch("e_frac_vtx2", &out_e_frac_vtx2);
	m_outTree->Branch("second_closestVtx_L3D", &out_second_closestVtx_L3D);
	m_outTree->Branch("JF_Lxy2", &out_JF_Lxy2);
	m_outTree->Branch("vtx2_MaxTrkRapidity", &out_vtx2_MaxTrkRapidity);
	m_outTree->Branch("vtx2_AvgTrkRapidity", &out_vtx2_AvgTrkRapidity);
	m_outTree->Branch("vtx2_MinTrkRapidity", &out_vtx2_MinTrkRapidity);
	m_outTree->Branch("MaxTrkRapidity", &out_MaxTrkRapidity);
	m_outTree->Branch("MinTrkRapidity", &out_MinTrkRapidity);
	m_outTree->Branch("AvgTrkRapidity", &out_AvgTrkRapidity);

	return;

}
