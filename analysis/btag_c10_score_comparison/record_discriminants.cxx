#include "../util/titles.hh"

using _mv2c10_type = double;

int _num_bins = 1000;
float _pt_min_cutoff = 55*1000; //= 55 GeV
float _eta_min_cutoff = 2.5; //= 55 GeV
string _slurm_arrays = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/";


vector<TH1D*>* make_histograms(string event, string label) {
    string label_title = get_level_title(label);
    string event_title = get_event_title(event);

    vector<TH1D*>* histogram_list = new vector<TH1D*>();
    histogram_list->push_back( new TH1D("bjet_discriminant", (label_title+" MV2c10 Discriminant for "+event_title+" B-Jets").c_str(), _num_bins, -1, 1) );
    histogram_list->push_back( new TH1D("cjet_discriminant", (label_title+" MV2c10 Discriminant for "+event_title+" C-Jets").c_str(), _num_bins, -1, 1) );
    histogram_list->push_back( new TH1D("ljet_discriminant", (label_title+" MV2c10 Discriminant for "+event_title+" Light-Jets").c_str(), _num_bins, -1, 1) );

    return histogram_list;
}


void fill_histograms(TFile& data_file, vector<TH1D*>* histogram_list, string tree_name, string coneID_name, string discriminant_name) {
    TTreeReader tree_reader(tree_name.c_str(), &data_file);
    TTreeReaderValue< vector<float> > pt_reader(tree_reader, "Offjet_pt");
    TTreeReaderValue< vector<float> > eta_reader(tree_reader, "Offjet_Eta");
    TTreeReaderValue< vector<int> > coneID_vector_reader(tree_reader, coneID_name.c_str());
    //change the below double to float if reading Offjet mv2c10
    TTreeReaderValue< vector<_mv2c10_type> > c10_discriminant_vector_reader(tree_reader, discriminant_name.c_str());

    int event_number = 0;
    while ( tree_reader.Next() ) {
        vector<float> pt_vector = *pt_reader;
        vector<float> eta_vector = *eta_reader;
        vector<int> coneID_vector = *coneID_vector_reader;
        auto c10_discriminant_vector = *c10_discriminant_vector_reader;
        for (int vector_index = 0; vector_index < coneID_vector.size(); vector_index++) {
            float pt = pt_vector[vector_index];
            float eta = eta_vector[vector_index];
            if (pt < _pt_min_cutoff or abs(eta) > _eta_min_cutoff) continue;
            int coneID = coneID_vector[vector_index];
            double c10_discriminant = c10_discriminant_vector[vector_index];

            switch (coneID) {
                case 5: histogram_list->at(0)->Fill(c10_discriminant); break;
                case 4: histogram_list->at(1)->Fill(c10_discriminant); break;
                default: histogram_list->at(2)->Fill(c10_discriminant); break;
            }
        }
        //if (event_number++ > 100) break;
    }
}


void save_and_delete_histograms(vector<TH1D*>* histogram_list, string event, string label) {
    histogram_list->at(0)->SaveAs( ("mv2c10_"+event+"_"+label+"_bjet_discriminants.root").c_str() );
    histogram_list->at(1)->SaveAs( ("mv2c10_"+event+"_"+label+"_cjet_discriminants.root").c_str() );
    histogram_list->at(2)->SaveAs( ("mv2c10_"+event+"_"+label+"_ljet_discriminants.root").c_str() );

    delete histogram_list->at(0);
    delete histogram_list->at(1);
    delete histogram_list->at(2);
    delete histogram_list;
}


void record_aod( vector<string>& aod_list, string event, string label) {
    vector<TH1D*>* histogram_list = make_histograms(event, "offline");
    for ( string aod_name : aod_list ) {
        cout << "Reading " << aod_name << endl << endl;
        TFile aod_file( aod_name.c_str(), "read" );
        fill_histograms(aod_file, histogram_list, "CollectionTree", "AntiKt4EMTopoJetsAuxDyn.ConeTruthLabelID", "BTagging_AntiKt4EMTopoAuxDyn.MV2c10_discriminant");
    }
    save_and_delete_histograms(histogram_list, event, label);
}


void record_flavntuple( string flavntuple_name, string event, string label, string jet_branch) {
    vector<TH1D*>* histogram_list = make_histograms(event, label);
    TFile flavntuple_file( flavntuple_name.c_str(), "read" );
    fill_histograms(flavntuple_file, histogram_list, "bTag_TriggerJets", "jet_truthflav", jet_branch);
    save_and_delete_histograms(histogram_list, event, label);
}


void record_discriminants() {
    record_flavntuple(_slurm_arrays+"slurm_20190501_hlt_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_hlt", "jet_mv2c10");
    record_flavntuple(_slurm_arrays+"slurm_20190501_ftkVtx_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_ftkVtx", "jet_mv2c10");
    record_flavntuple(_slurm_arrays+"slurm_20190501_hlt_gutted2_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_hlt_gutted2", "jet_mv2c10");
    record_flavntuple(_slurm_arrays+"slurm_20190501_ftkVtx_gutted2_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_ftkVtx_gutted2", "jet_mv2c10");
    //record_flavntuple(_slurm_arrays+"slurm_20190430_hlt_guttingTest_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_hlt_gutted", "jet_mv2c10");
    //record_flavntuple(_slurm_arrays+"slurm_20190430_ftkVtx_guttingTest_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_ftkVtx_gutted", "jet_mv2c10");
    //record_flavntuple(_slurm_arrays+"slurm_20190426_ftkVtx_tuneTest_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_ftkVtx_wrong", "jet_mv2c10");
    //record_flavntuple(_slurm_arrays+"slurm_20190425_hlt_dRtest_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_hlt_alt", "jet_mv2c10");
    //record_flavntuple(_slurm_arrays+"slurm_20190425_ftkVtx_dRtest_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_ftkVtx_alt", "jet_mv2c10");
    //record_flavntuple(_slurm_arrays+"slurm_20190420_ftk_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_ftk", "jet_mv2c10");
    //record_flavntuple(_slurm_arrays+"slurm_20190420_ftkRefit_ttbar_41000valid1_full_step4/merged_flavntuple.root", "ttbar", "retune_ftkRefit", "jet_mv2c10");
}
