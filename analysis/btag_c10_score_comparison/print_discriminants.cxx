#include "../util/titles.hh"

//using _mv2c10_type = double; //use for online mv2c10
using _mv2c10_type = float; //use for offline mv2c10

int _num_bins = 1000;
float _pt_min_cutoff = 55*1000; //= 55 GeV
float _eta_min_cutoff = 2.5; //= 55 GeV

string _ttbar_raw_flavntuple_name = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/flavnutple_test_base.root";
//string _ttbar_raw_flavntuple_name = "/users/cmilke/qualification/bJetTrigger/Tuning_rel21/run/flavnutple_test_modern.root";


void read_discriminants(TFile& data_file, string tree_name, string coneID_name, string discriminant_name) {
    TTreeReader tree_reader(tree_name.c_str(), &data_file);
    TTreeReaderValue< vector<float> > pt_reader(tree_reader, "Offjet_pt");
    TTreeReaderValue< vector<float> > eta_reader(tree_reader, "Offjet_Eta");
    TTreeReaderValue< vector<int> > coneID_vector_reader(tree_reader, coneID_name.c_str());
    //change the below double to float if reading Offjet mv2c10
    TTreeReaderValue< vector<_mv2c10_type> > c10_discriminant_vector_reader(tree_reader, discriminant_name.c_str());

    int event_number = 0;
    while ( tree_reader.Next() ) {
        cout << "Event Number = " << event_number++ << endl;
        //vector<float> pt_vector = *pt_reader;
        //vector<float> eta_vector = *eta_reader;
        vector<int> coneID_vector = *coneID_vector_reader;
        auto c10_discriminant_vector = *c10_discriminant_vector_reader;
        for (int vector_index = 0; vector_index < coneID_vector.size(); vector_index++) {
            //float pt = pt_vector[vector_index];
            //float eta = eta_vector[vector_index];
            //if (pt < _pt_min_cutoff or abs(eta) > _eta_min_cutoff) continue;
            int coneID = coneID_vector[vector_index];
            double c10_discriminant = c10_discriminant_vector[vector_index];
            cout << "       cone ID = " << coneID << " ; MV2c10 = " << c10_discriminant << endl;
        }
    }
}


void record_flavntuple( string flavntuple_name, string event, string level, string jet_branch) {
    TFile flavntuple_file( flavntuple_name.c_str(), "read" );
    read_discriminants(flavntuple_file, "bTag_TriggerJets", "jet_truthflav", jet_branch);
}


void print_discriminants() {
    //record_flavntuple(_ttbar_raw_flavntuple_name, "ttbar", "online", "jet_mv2c10");
    record_flavntuple(_ttbar_raw_flavntuple_name, "ttbar", "offline", "Offjet_mv2c10");
}
