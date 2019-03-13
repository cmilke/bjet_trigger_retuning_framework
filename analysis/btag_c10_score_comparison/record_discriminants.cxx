#include "../util/titles.hh"

using _mv2c10_type = double;
//using _mv2c10_type = float;

int _num_bins = 1000;
float _pt_min_cutoff = 55*1000; //= 55 GeV
float _eta_min_cutoff = 2.5; //= 55 GeV
string _slurm_arrays = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/";

//string _ttbar_online_hybrid_retune_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/flavntuple_20181122_ttbar_cheat_step4.root";
//string _ttbar_online_hybrid_retune_alt_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/flavntuple_20181122_ttbar_test_step4.root";
//string _Zprime_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/flavntuple_20181122_Zprime_step4.root";
string _ttbar_online_hybrid_retune_flavntuple_med       = _slurm_arrays + "slurm_20190218_ttbar_41000_med_step4/merged_flavntuple.root";
string _ttbar_online_hybrid_retune_flavntuple_med_copy  = _slurm_arrays + "slurm_20190226_ttbar_41000_med_step4/merged_flavntuple.root";
string _ttbar_online_hybrid_retune_flavntuple_med_copy2 = _slurm_arrays + "slurm_20190227_ttbar_41000_med_step4/merged_flavntuple.root";
string _ttbar_online_hybrid_retune_flavntuple_med_alt1  = _slurm_arrays + "slurm_20190228_ttbar_41000_med_alt1_step4/merged_flavntuple.root";
string _ttbar_online_hybrid_retune_flavntuple_med_alt2  = _slurm_arrays + "slurm_20190228_ttbar_41000_med_alt2_step4/merged_flavntuple.root";
string _ttbar_online_hybrid_retune_flavntuple_med_alt3  = _slurm_arrays + "slurm_20190228_ttbar_41000_med_alt3_step4/merged_flavntuple.root";
//string _ttbar_online_hybrid_retune_flavntuple_med_alt   = _slurm_arrays + "slurm_20190218_ttbar_41000_med_alt1_step4/merged_flavntuple.root";
string _ttbar_online_hybrid_retune_flavntuple_large     = _slurm_arrays + "slurm_20190218_ttbar_41000_large_10pc_step4/merged_flavntuple.root";
string _ttbar_online_hybrid_retune_flavntuple_full      = _slurm_arrays + "slurm_20190218_ttbar_41000_full_step4/merged_flavntuple.root";

//string _ttbar_ftk_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/flavntuple_20190111_ttbar_step1.root";
//string _Zprime_ftk_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/flavntuple_20190111_Zprime_step1.root";

string _ttbar_online_retune_med_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/slurm_20190212_ttbar_41000_med_step4/merged_flavntuple.root";
string _ttbar_online_retune_med_alt_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/slurm_20190212_ttbar_41000_med_step4/merged_flavntuple.root";
string _ttbar_online_retune_large_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/slurm_20190212_ttbar_41000_large_alt1_step4/merged_flavntuple.root";

string _ttbar_online_retune_1234 = _slurm_arrays + "/slurm_20190303_ttbar_41000_500k_step4/merged_flavntuple.root";
string _ttbar_online_retune_1234_med = _slurm_arrays + "/slurm_20190308_ttbar_41000_med_step4/merged_flavntuple.root";
string _ttbar_online_retune_123_4 = _slurm_arrays + "/slurm_20190303_ttbar_41000_500k_alt2_step4/merged_flavntuple.root";
string _ttbar_online_retune_1_23_4 = _slurm_arrays + "/slurm_20190303_ttbar_41000_500k_alt3_step4/merged_flavntuple.root";

string _ttbar_official_tune_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/slurm_20190212_ttbar_41000_full_official/merged_flavntuple.root";
string _ttbar_offline_flavntuple = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/slurm_arrays/slurm_20190212_ttbar_41000_full_offline/merged_flavntuple.root";


vector<TH1D*>* make_histograms(string event, string level) {
    string level_title = get_level_title(level);
    string event_title = get_event_title(event);

    vector<TH1D*>* histogram_list = new vector<TH1D*>();
    histogram_list->push_back( new TH1D("bjet_discriminant", (level_title+" MV2c10 Discriminant for "+event_title+" B-Jets").c_str(), _num_bins, -1, 1) );
    histogram_list->push_back( new TH1D("cjet_discriminant", (level_title+" MV2c10 Discriminant for "+event_title+" C-Jets").c_str(), _num_bins, -1, 1) );
    histogram_list->push_back( new TH1D("ljet_discriminant", (level_title+" MV2c10 Discriminant for "+event_title+" Light-Jets").c_str(), _num_bins, -1, 1) );

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


void save_and_delete_histograms(vector<TH1D*>* histogram_list, string event, string level) {
    histogram_list->at(0)->SaveAs( ("mv2c10_"+event+"_"+level+"_bjet_discriminants.root").c_str() );
    histogram_list->at(1)->SaveAs( ("mv2c10_"+event+"_"+level+"_cjet_discriminants.root").c_str() );
    histogram_list->at(2)->SaveAs( ("mv2c10_"+event+"_"+level+"_ljet_discriminants.root").c_str() );

    delete histogram_list->at(0);
    delete histogram_list->at(1);
    delete histogram_list->at(2);
    delete histogram_list;
}


void record_flavntuple( string flavntuple_name, string event, string level, string jet_branch) {
    vector<TH1D*>* histogram_list = make_histograms(event, level);
    TFile flavntuple_file( flavntuple_name.c_str(), "read" );
    fill_histograms(flavntuple_file, histogram_list, "bTag_TriggerJets", "jet_truthflav", jet_branch);
    save_and_delete_histograms(histogram_list, event, level);
}


void record_discriminants() {
    //record_flavntuple(_ttbar_ftk_flavntuple_name, "ttbar", "ftk", "jet_mv2c10");
    //record_flavntuple(_Zprime_ftk_flavntuple_name, "Zprime", "ftk", "jet_mv2c10");

    //record_flavntuple(_ttbar_online_hybrid_retune_flavntuple, "ttbar", "online_hybrid_retune", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_hybrid_retune_alt_flavntuple, "ttbar", "online_hybrid_retune_alt", "jet_mv2c10");
    //record_flavntuple(_Zprime_flavntuple_name, "Zprime", "online", "jet_mv2c10");
    
    //record_flavntuple(_ttbar_online_hybrid_retune_flavntuple_large, "ttbar", "online_hybrid_retune_large", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_hybrid_retune_flavntuple_full, "ttbar", "online_hybrid_retune_full", "jet_mv2c10");

    //record_flavntuple(_ttbar_online_hybrid_retune_flavntuple_med, "ttbar", "online_hybrid_retune_med", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_hybrid_retune_flavntuple_med_copy, "ttbar",  "online_hybrid_retune_med_copy1", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_hybrid_retune_flavntuple_med_copy2, "ttbar", "online_hybrid_retune_med_copy2", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_hybrid_retune_flavntuple_med_alt1, "ttbar", "online_hybrid_retune_med_alt1", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_hybrid_retune_flavntuple_med_alt2, "ttbar", "online_hybrid_retune_med_alt2", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_hybrid_retune_flavntuple_med_alt3, "ttbar", "online_hybrid_retune_med_alt3", "jet_mv2c10");

    //record_flavntuple(_ttbar_online_retune_1234, "ttbar", "online_ttbar_retune_1234", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_retune_123_4, "ttbar", "online_ttbar_retune_123_4", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_retune_1_23_4, "ttbar", "online_ttbar_retune_1_23_4", "jet_mv2c10");
    //record_flavntuple(_ttbar_online_retune_1234_med, "ttbar", "online_ttbar_retune_1234_med", "jet_mv2c10");
    record_flavntuple(_ttbar_online_retune_med_flavntuple, "ttbar", "online_retune_med", "jet_mv2c10");
    record_flavntuple(_ttbar_online_retune_med_alt_flavntuple, "ttbar", "online_retune_med_alt", "jet_mv2c10");
    record_flavntuple(_ttbar_online_retune_large_flavntuple, "ttbar", "online_retune_large", "jet_mv2c10");
    
    //record_flavntuple(_ttbar_official_tune_flavntuple_name, "ttbar", "online_official_tune", "jet_mv2c10");

    //record_flavntuple(_ttbar_offline_flavntuple_name, "ttbar", "offline", "Offjet_mv2c10");
    //record_flavntuple(_Zprime_offline_flavntuple_name, "Zprime", "offline", "Offjet_mv2c10");
}
